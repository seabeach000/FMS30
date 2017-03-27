/* ----------------------------------------------------------------------------
 * File: buf_fifo.c
 *
 * Desc: Buffered FIFO implementation
 *
 * Copyright (c) 2015 MainConcept GmbH or its affiliates.  All rights reserved.
 *
 * MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.  
 * This software is protected by copyright law and international treaties.  Unauthorized 
 * reproduction or distribution of any portion is prohibited by law.
 * ----------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buf_fifo.h"


// use fifo for stream part, and feed auxinfo unchanged
struct impl_stream
{
  fifo_stream_tt impl;
};


static uint32_t fifow_usable_bytes(bufstream_tt *bs)
{
  return fifo_w_empty(bs->Buf_IO_struct->impl.fifo);
}


static uint32_t fifor_usable_bytes(bufstream_tt *bs)
{
  return fifo_r_filled(bs->Buf_IO_struct->impl.fifo);
}


//request the buffer with at least numbytes-bytes
static uint8_t *fifow_request(bufstream_tt *bs, uint32_t numbytes)
{
  return fifo_w_sampbuf(bs->Buf_IO_struct->impl.fifo, numbytes);
}


static uint8_t *fifor_request(bufstream_tt *bs, uint32_t numbytes)
{
  return fifo_r_sampbuf(bs->Buf_IO_struct->impl.fifo, numbytes);
}


//confirm numbytes-bytes filled in in requested after last "request"-call
static uint32_t fifow_confirm(bufstream_tt *bs, uint32_t numbytes)
{
  return fifo_w_commit(bs->Buf_IO_struct->impl.fifo, numbytes);
}


static uint32_t fifor_confirm(bufstream_tt *bs, uint32_t numbytes)
{
  return fifo_r_remove (bs->Buf_IO_struct->impl.fifo, numbytes);
}


//put/get numbytes-bytes into/from bufsteam
// fifo_w_sampput/fifo_r_sampget
static uint32_t fifow_copybytes(bufstream_tt *bs, uint8_t *ptr, uint32_t numbytes)
{
  return fifo_w_sampput(bs->Buf_IO_struct->impl.fifo, ptr, numbytes);
}


static uint32_t fifor_copybytes(bufstream_tt *bs, uint8_t *ptr, uint32_t numbytes)
{
  uint8_t *p;
  p=fifo_r_sampbuf(bs->Buf_IO_struct->impl.fifo, numbytes);
  if(!p) return 0;
  memcpy(ptr,p,numbytes);
  return fifo_r_remove (bs->Buf_IO_struct->impl.fifo, numbytes);
}


// maximal chunk-size in buffer-mode (i.e. for "request"-call)
static uint32_t fifow_chunksize(bufstream_tt *bs)
{
  return bs->Buf_IO_struct->impl.fifo->sampchunk;
}


static uint32_t fifor_chunksize(bufstream_tt *bs)
{
  return bs->Buf_IO_struct->impl.fifo->sampchunk;
}


//inform bufstream about some additional info - for example
// to inform MUXer about encoding-units
static uint32_t fifow_auxinfo(bufstream_tt *bs, uint32_t offs, uint32_t info_ID, void *info_ptr, uint32_t info_size)
{
  return bs->Buf_IO_struct->impl.output.auxinfo(&bs->Buf_IO_struct->impl.output,
                                         offs, info_ID, info_ptr, info_size);
}


static uint32_t fifor_auxinfo(bufstream_tt *bs, uint32_t offs, uint32_t info_ID, void *info_ptr, uint32_t info_size)
{
  if (!bs || !offs || !info_ID || !info_ptr || !info_size){}; // remove compile warning
  return BS_OK;
}


static void fifow_done  (bufstream_tt *bs, int32_t Abort)
{
  if (!bs || !Abort){} // remove compile warning
}


static void fifor_done  (bufstream_tt *bs, int32_t Abort)
{
  if (!bs || !Abort){} // remove compile warning
}


void free_fifo_buf(fifo_stream_tt *buf_fifo)
{
  if(buf_fifo)
  {
    fifo_free(buf_fifo->fifo);
    free(buf_fifo);
  }
}


fifo_stream_tt *new_fifo_buf(uint32_t buf_size,  uint32_t chunk_size)
{
  bufstream_tt *bs;
  struct impl_stream *buf_fifo;

  buf_fifo=(struct impl_stream*)malloc(sizeof(struct impl_stream));

  if(buf_fifo)
  {
    buf_fifo->impl.fifo=fifo_new(buf_size, chunk_size, 1);

    bs = &buf_fifo->impl.input;

    bs->usable_bytes = fifow_usable_bytes;
    bs->request  = fifow_request;
    bs->confirm  = fifow_confirm;
    bs->copybytes= fifow_copybytes;
    bs->split    = NULL;
    bs->chunksize= fifow_chunksize;
    bs->free     = NULL; //fw_free;
    bs->auxinfo  = fifow_auxinfo;
    bs->done     = fifow_done;
    bs->drive_ptr= NULL;
    bs->drive    = NULL;

    bs->state    = NULL;
    bs->flags    = BS_FLAGS_DST;
    bs->Buf_IO_struct = buf_fifo;

    bs = &buf_fifo->impl.output;

    bs->usable_bytes = fifor_usable_bytes;
    bs->request  = fifor_request;
    bs->confirm  = fifor_confirm;
    bs->copybytes= fifor_copybytes;
    bs->split    = NULL;
    bs->chunksize= fifor_chunksize;
    bs->free     = NULL; //fr_free;
    bs->auxinfo  = fifor_auxinfo;
    bs->done     = fifor_done;
    bs->drive_ptr= NULL;
    bs->drive    = NULL;

    bs->state    = NULL;
    bs->flags    = 0;
    bs->Buf_IO_struct = buf_fifo;
  }
  return(fifo_stream_tt *)buf_fifo;
}
