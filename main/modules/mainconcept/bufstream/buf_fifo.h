/* ----------------------------------------------------------------------------
 * File: buf_fifo.h
 *
 * Desc: Buffered FIFO declaration
 *
 * Copyright (c) 2015 MainConcept GmbH or its affiliates.  All rights reserved.
 *
 * MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.  
 * This software is protected by copyright law and international treaties.  Unauthorized 
 * reproduction or distribution of any portion is prohibited by law.
 *
 * ----------------------------------------------------------------------------
 */
#include <bufstrm.h>
#include "sr_fifo.h"

typedef struct fifo_buf_struct fifo_stream_tt;

struct fifo_buf_struct
{
  bufstream_tt  input;  // used on place of init_file_buf_write
  bufstream_tt  output; // used on place of init_file_buf_read
  fifo_tt      *fifo;
};


#ifdef __cplusplus
extern "C" {
#endif

void free_fifo_buf(fifo_stream_tt *buf_fifo);
fifo_stream_tt *new_fifo_buf(uint32_t buf_size, uint32_t chunk_size);

#ifdef __cplusplus
}
#endif
