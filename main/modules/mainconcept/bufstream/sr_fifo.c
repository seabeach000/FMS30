/* ----------------------------------------------------------------------------
 * File: sr_fifo.c
 *
 * Desc: fifo implementation
 *
 * Copyright (c) 2015 MainConcept GmbH or its affiliates.  All rights reserved.
 *
 * MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.  
 * This software is protected by copyright law and international treaties.  Unauthorized 
 * reproduction or distribution of any portion is prohibited by law.
 * ----------------------------------------------------------------------------
 */

// sampchunk - max-size of read/write chunk in no-copy mode
// sampbegin - get-index
// sampend   - put-index
// sampmax   - full-buffer size

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sr_fifo.h"

//typedef struct fifo_struct fifo_tt;
//fifo_r - methoden are used in reading thread
//fifo_w - methoden are used in writing thread



fifo_tt *fifo_new(uint32_t sampcached, uint32_t sampchunk, size_t sampsize)
{
  fifo_tt *p;
  uint8_t *buf;
  size_t bufsize;

  if(sampcached<sampchunk) return NULL;

  p=(fifo_tt *) malloc(sizeof(fifo_tt));
  if(!p) return NULL;

  if(sampchunk) sampchunk--;

  bufsize=(sampcached+sampchunk)*sampsize;
  buf=(uint8_t *) malloc(bufsize);

  if(!buf)
  {
    free(p);
    return NULL;
  }

  p->sampchunk = sampchunk;
  p->sampbegin = sampchunk;
  p->sampend   = sampchunk;
  p->sampmax   = sampcached+sampchunk;
  p->buf       = buf;
  p->sampsize  = sampsize;
  p->bufsize   = bufsize;
  p->samptoput = 0;
  return p;
}


uint32_t fifo_free(fifo_tt *fifo)
{
  if(fifo)
  {
    if(fifo->buf)
      free(fifo->buf);
    free(fifo);
  }
  return 0;
}


uint32_t fifo_r_filled(fifo_tt *fifo)
{
  uint32_t filled;
  uint32_t sampend  =*(volatile uint32_t *)&fifo->sampend;
  uint32_t sampbegin=*(volatile uint32_t *)&fifo->sampbegin;


  if(sampend < sampbegin)
  {
// wrapped over sampmax in buffer
    filled=(fifo->sampmax-sampbegin)+(sampend-fifo->sampchunk);
  }
  else
  {
    filled=sampend-sampbegin;
  }
  return filled;
}


// {numSamples} MUST be smaller then {sampchunk}
//
uint8_t *fifo_r_sampbuf(fifo_tt *fifo, uint32_t numSamples)
{
  uint32_t sampend=*(volatile uint32_t *)(&fifo->sampend);
  uint32_t sampbegin=fifo->sampbegin;

// local copy
// must be used to avoid unconsistency
// by simultaneous PutSamp and GetSampPtr
  
  if(sampend < sampbegin)
  {
// wrapped over sampmax in buffer
    uint32_t samprest=fifo->sampmax-sampbegin;

    if(numSamples > samprest)
    {
// nessesary to copy chunk-rest
      if(samprest > fifo->sampchunk)
      {
//error!
//printf("samprest(%d)>sampchunk(%d) (numSamples=%d)\n",(int)samprest,(int)fifo->sampchunk,numSamples);
        return NULL;
      }

      memcpy(fifo->buf+(fifo->sampchunk-samprest)*fifo->sampsize,
             fifo->buf+sampbegin*fifo->sampsize,
             samprest*fifo->sampsize);
      fifo->sampbegin=(sampbegin=fifo->sampchunk-samprest);
    }
    else
    goto exit;
  }

  if(sampend < sampbegin+numSamples)
  {
//printf("sampend(%u)<sampbegin(%u)+numSamples(%u)\n",sampend,sampbegin,numSamples);
      return NULL;
  }

exit:
  return fifo->buf+sampbegin*fifo->sampsize;
}


uint32_t fifo_r_remove(fifo_tt *fifo, uint32_t numSamples)
{
  uint32_t sampend=*(volatile uint32_t *)(&fifo->sampend);
  uint32_t sampbegin=fifo->sampbegin;

// local copy of sampend
// must be used to avoid unconsistency
// by simultaneous PutSamp and fifo_r_remove
//
// change sampbegin
// uses sampbegin und sampend
// can't be used simultaneously with GetSampPtr
  
  if(sampend < sampbegin)
  {
    // wrapped over sampmax in buffer
    uint32_t samprest = fifo->sampmax-sampbegin;
    uint32_t filled   = samprest+(sampend-fifo->sampchunk);

    if(filled<numSamples)
    {
      numSamples=filled;
    }

    if(samprest >= numSamples)
    {
      sampbegin+=numSamples;
    }
    else
    {
      sampbegin=fifo->sampchunk+numSamples-samprest;
    }
  }
  else
  {
    uint32_t filled=sampend-sampbegin;
    if(filled<numSamples)
    {
      numSamples=filled;
    }
    sampbegin+=numSamples;
  }

  *(volatile uint32_t *)(&fifo->sampbegin)=sampbegin;
  return numSamples;
}



uint32_t fifo_w_empty(fifo_tt *fifo)
{
  uint32_t sampbegin=*(volatile uint32_t *)(&fifo->sampbegin);
  uint32_t sampend=fifo->sampend;

  if(sampend < sampbegin)
  {
    return sampbegin-sampend;
  }
  else
  {
// free area can be splitted
    return (fifo->sampmax-sampend)+(sampbegin>fifo->sampchunk?sampbegin-fifo->sampchunk:0);
  }
}

// copy src to fifo->buffer and modify fifo->sampend
//
uint32_t fifo_w_sampput(fifo_tt *fifo, uint8_t *src, uint32_t numSamples)
{
  uint32_t sampbegin=*(volatile uint32_t *)(&fifo->sampbegin);
  uint32_t sampend=fifo->sampend;

// local copy
// must be used to avoid unconsistency
// by simultaneous Put and Get

  if(sampend < sampbegin)
  {
// wrapped over sampmax in buffer
// contignuous free area
    uint32_t free=sampbegin-sampend - 1;
    
    if(free<numSamples)
    {
      numSamples=free;
    }

    memcpy(fifo->buf+sampend*fifo->sampsize,src,numSamples*fifo->sampsize);
    sampend+=numSamples;
  }
  else
  {
// free area can be splitted
    uint32_t rest = fifo->sampmax-sampend;
    uint32_t free=rest+(sampbegin>fifo->sampchunk?sampbegin - fifo->sampchunk - 1:0);

    if(free<numSamples)
    {
      numSamples=free;
    }

    if(rest >= numSamples)
    {
      memcpy(fifo->buf+sampend*fifo->sampsize,src,numSamples*fifo->sampsize);
      sampend+=numSamples;
    }
    else
    {
      memcpy(fifo->buf+sampend*fifo->sampsize,
             src,
             rest*fifo->sampsize);
      memcpy(fifo->buf+fifo->sampchunk*fifo->sampsize,
             src+rest*fifo->sampsize,
             (numSamples-rest)*fifo->sampsize);
      sampend=fifo->sampchunk+(numSamples-rest);
    }
  }

  *(volatile uint32_t *)(&fifo->sampend)=sampend;
  return numSamples;
}

void fifo_w_audio_put_8to16(fifo_tt *fifo, uint8_t *psrc, uint32_t samples)
{
  while(samples)
  {
    uint16_t *pdst;
    uint32_t  j,i;
    uint32_t  bytes;

    pdst = (uint16_t *) fifo_w_sampbuf(fifo, samples);
    if(pdst)
    {
      j=samples;
    }
    else
    {
      j=fifo->sampchunk+1;
      pdst = (uint16_t *) fifo_w_sampbuf(fifo, j);
//printf("fifo_w_sampbuf(%d):  %d, %d %d %d\n",bytes, (int)fifo_r_filled(gInAudioFIFO), (int)gInAudioFIFO->sampbegin, (int)gInAudioFIFO->sampend, (int) gInAudioFIFO->sampmax);
    }

    bytes = (uint32_t)(fifo->sampsize/(sizeof(int16_t)))*j;
//printf("fifo_w_sampbuf(%d):  %d, %d %d %d",bytes, (int)fifo_r_filled(gInAudioFIFO), (int)gInAudioFIFO->sampbegin, (int)gInAudioFIFO->sampend, (int) gInAudioFIFO->sampmax);

    for (i = 0; i<bytes; i++)
    {
      *pdst++ = (uint16_t)((*psrc++) + 128) << 8;
    }
    fifo_w_commit (fifo, j);
    samples-=j;
  }
}



uint8_t * fifo_w_sampbuf(fifo_tt *fifo, uint32_t numSamples)
{
  uint32_t sampbegin=*(volatile uint32_t *)(&fifo->sampbegin);
  uint32_t sampend=fifo->sampend;

// local copy
// must be used to avoid unconsistency
// by simultaneous Put and Get

  if(sampend < sampbegin)
  {
    uint32_t free=sampbegin-sampend;
    
    if(free<=numSamples)
    {
//
//here one need to call write()-like callback to make place free
//
      fifo->samptoput=0;
      return NULL;
    }
    fifo->samptoput=sampend;
    return fifo->buf+sampend*fifo->sampsize;
  }
  else
  {
// free area can be splitted
    uint32_t rest = fifo->sampmax-sampend;
    uint32_t free = rest+(sampbegin>fifo->sampchunk?sampbegin-fifo->sampchunk:0);

    if(rest >= numSamples)
    {
      fifo->samptoput=sampend;
      return fifo->buf+sampend*fifo->sampsize;
    }

    if(free<numSamples)
    {
//
//here one need to call write()-like callback to make place free
//
      fifo->samptoput=0;
      return NULL;
    }

    if(fifo->sampchunk > rest)
    {
      fifo->samptoput=fifo->sampchunk-rest;
      return fifo->buf+(fifo->sampchunk-rest)*fifo->sampsize;
    }
    else
    {
//
// Asked to allocate more then fifo->sampchunk
// it is not alway possible
// 
      fifo->samptoput=0;
      return NULL;
    }
  }
}

//todo commit make no numSamples check, it MUST be correct

uint32_t fifo_w_commit(fifo_tt *fifo, uint32_t numSamples)
{
  uint32_t sampend=fifo->sampend;

  if(fifo->samptoput==sampend)
  {
    sampend+=numSamples;
  }
  else
  {
//write-bufer allocated in reserved-chunk area
    if(fifo->samptoput+numSamples < fifo->sampchunk)
    {
      memcpy(fifo->buf+fifo->sampsize*sampend,
             fifo->buf+fifo->sampsize*fifo->samptoput,
             fifo->sampsize*numSamples);
      sampend+=numSamples;
    }
    else
    {
      memcpy(fifo->buf+fifo->sampsize*sampend,
             fifo->buf+fifo->sampsize*fifo->samptoput,
             fifo->sampsize*(fifo->sampchunk-fifo->samptoput));
      sampend=fifo->samptoput+numSamples;
    }
  }


  *(volatile uint32_t *)(&fifo->sampend)=sampend;

  return numSamples;
}
