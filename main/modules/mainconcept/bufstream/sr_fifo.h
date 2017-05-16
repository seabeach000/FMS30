/* ----------------------------------------------------------------------------
 * File: sr_fifo.h
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

#include <mctypes.h>

typedef struct fifo_struct fifo_tt;

#ifdef __cplusplus
extern "C" {
#endif

fifo_tt  *fifo_new (uint32_t sampcached, uint32_t sampchunk, size_t sampsize);
uint32_t  fifo_free(fifo_tt *fifo);

uint32_t  fifo_r_filled (fifo_tt *fifo);
uint32_t  fifo_r_sampget(fifo_tt *fifo, uint8_t *src, uint32_t numSamples);
uint8_t  *fifo_r_sampbuf(fifo_tt *fifo, uint32_t numSamples);
uint32_t  fifo_r_remove (fifo_tt *fifo, uint32_t numSamples);

uint32_t  fifo_w_empty  (fifo_tt *fifo);
uint32_t  fifo_w_sampput(fifo_tt *fifo, uint8_t *src, uint32_t numSamples);
uint8_t  *fifo_w_sampbuf(fifo_tt *fifo, uint32_t numSamples);
uint32_t  fifo_w_commit (fifo_tt *fifo, uint32_t numSamples);

#ifdef __cplusplus
}
#endif

// i put structure-definition here for debugging purpose only.
// it MUST be moved to sr_fifo.c 
//

struct fifo_struct
{
  uint8_t *buf;
  size_t   bufsize;
  size_t   sampsize;
  uint32_t sampchunk;

  uint32_t sampbegin;
  uint32_t sampend;
  uint32_t sampmax;
  uint32_t samptoput;
};
