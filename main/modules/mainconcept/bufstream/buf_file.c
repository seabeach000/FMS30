/* ----------------------------------------------------------------------------
 * File: buf_file.c
 *
 * Desc: Buffered stream file IO
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
#ifdef UNDER_CE
#define WIN32IO
#endif

#ifdef WIN32IO
  #include <windows.h>
#else
  #if !defined(__APPLE__) && !defined(__linux__) && !defined(__native_client__) && !defined(__QNX__)
    #include <io.h>
  #else
    #include <unistd.h>
  #endif
  #include <fcntl.h>
  #include <sys/stat.h>
  #include <sys/types.h>
#endif

#include <auxinfo.h>
#include "../mc_os_common.h"
#include "buf_file.h"

#define DVD_SECTOR_SIZE       2048     // DVD sector size     

#define MAX_SECTORS           50400    // make enough room for ~7 hours worth
#define MAX_CELLS             999      // the most cells we will handle, should be plenty!

#define MAX_AUDIO_STREAMS     8
#define MAX_SUBPIC_STREAMS    32

struct vob_nav_info
{
  int32_t base_idx;                    // base index into the nav_sector array for this vob
  int32_t total_nv_sectors;            // total nav sectors in this VOB
  int32_t end_PTM;                     // PTM end time for this VOB
#ifdef _BS_UNICODE
  wchar_t filename[_BS_MAX_PATH];      // filename of this VOB
#else
  char filename[_BS_MAX_PATH];         // filename of this VOB
#endif
  struct vob_nav_info *next;           // pointer to the next structure
  struct vob_nav_info *prev;           // pointer to the prev structure
};


struct synci_info
{
  int32_t synci_idx;
  int32_t *synci_sectors;
};


//implementation structure
struct impl_stream
{
#ifdef WIN32IO
  HANDLE io;
#else
  FILE *io;
#endif
  uint8_t *bfr;
  uint32_t idx;       // read-write index
  uint32_t bfr_size;  // allocated size
  uint32_t bfr_count; // filled size (for read)
  uint32_t chunk_size;
  uint64_t bytecount;
  uint64_t file_size;
  int32_t filenumber;
#ifdef _BS_UNICODE
  wchar_t filename[_BS_MAX_PATH];
  wchar_t basename[_BS_MAX_PATH];
  wchar_t baseext[1024];
#else
  char filename[_BS_MAX_PATH];
  char basename[_BS_MAX_PATH];
  char baseext[1024];
#endif

  // dvd stuff
  int32_t do_nav_info;                     // flag to embed nav info
  int32_t abort_nav_info;                  // abort flag
  int32_t *nav_sectors;                    // nav sector numbers
  int32_t *sector_times;                   // nav sector lengths in time
  int32_t *sector_flags;                   // sector flags
  int32_t nav_sector_idx;                  // index into the above
  struct vob_nav_info *vob_info;           // nav info pointer
  struct vob_nav_info *cur_vob_info;       // current nav info pointer
  int32_t fixup_synci_sector;

  struct synci_info asynci[MAX_AUDIO_STREAMS];
  int32_t num_audio_streams;
  struct synci_info spsynci[MAX_SUBPIC_STREAMS];
  int32_t num_subpic_streams;
  int32_t do_hli_ptm_time;
  int32_t *cell_sectors;                   // nav sector numbers
  int32_t num_cells;

  uint8_t extra_byte;
  uint8_t extra_byte_present;
};


static uint32_t fw_split(bufstream_tt *bs);
static void doVOBNavInfo(bufstream_tt *bs, struct vob_nav_info *vob_info);


// fw => write to file
// fr => read from file
static uint32_t fw_usable_bytes(bufstream_tt *bs)
{
  struct impl_stream* p = bs->Buf_IO_struct;
  return p->bfr_size-p->idx;
}

static uint32_t fr_usable_bytes(bufstream_tt *bs)
{
  struct impl_stream* p = bs->Buf_IO_struct;
  return p->bfr_count-p->idx;
}


//request the buffer with at least numbytes-bytes
static uint8_t *fw_request(bufstream_tt *bs, uint32_t numbytes)
{
  struct impl_stream* p = bs->Buf_IO_struct;

  if (numbytes > p->bfr_size)
    return NULL;

  if(p->idx+numbytes <= p->bfr_size)
    return p->bfr+p->idx;

  if(p->idx)
  {
#ifdef WIN32IO
    DWORD n;
    WriteFile(p->io, p->bfr, p->idx, &n, NULL);
#else
    uint32_t n;
    n = (uint32_t) fwrite(p->bfr, sizeof(uint8_t), p->idx, p->io);
#endif
    if(n != p->idx)
    {
      return NULL;
    }
  }

  p->idx=0;
  return p->bfr;
}


static uint32_t  fr_confirm(bufstream_tt *bs, uint32_t numbytes)
{
  bs->Buf_IO_struct->idx       += numbytes;
  bs->Buf_IO_struct->bytecount += numbytes;
  return numbytes;
}


static uint8_t *fr_request_swap_endian(bufstream_tt *bs, uint32_t numbytes)
{
  struct impl_stream* p = bs->Buf_IO_struct;
  uint32_t i, j, c;
  uint8_t byt, *ptr;

  if(p->idx+numbytes <= p->bfr_count)
    return p->bfr + p->idx;

  if(p->idx == p->bfr_count)
  {
    p->idx=0;
    p->bfr_count=0;
  }

  if(p->idx+numbytes > p->bfr_size)
  {
    memcpy(p->bfr, p->bfr + p->idx, p->bfr_count - p->idx);
    p->bfr_count -= p->idx;
    p->idx=0;
  }

  ptr = p->bfr + p->bfr_count;
  c = p->bfr_size - p->bfr_count;
  if(p->extra_byte_present)
  {
    ptr[0] = p->extra_byte;
    ptr++;
    p->bfr_count++;
    p->extra_byte_present = 0;
    p->bytecount++;
    c--;
  }

#ifdef WIN32IO
  ReadFile(p->io, ptr, c, (DWORD*)&i, NULL);
#else 
  i = (uint32_t) fread(ptr, sizeof(uint8_t), c, p->io);
#endif

  if(i % 2)
    j = 0;

  for(j = 0; j < (i & 0xFFFFFFFE); j += 2)
  {
    byt = ptr[j];
    ptr[j] = ptr[j + 1];
    ptr[j + 1] = byt;
  }
  p->bfr_count += i;

  if((i == c) && (c % 2))
  {
    ptr += (i - 1);
#ifdef WIN32IO
    ReadFile(p->io, &p->extra_byte, 1, (DWORD*)&i, NULL);
#else
    i = (uint32_t) fread(&p->extra_byte, sizeof(uint8_t), 1, p->io);
#endif
    if(i == 1)
    {
      byt = ptr[0];
      ptr[0] = p->extra_byte;
      p->extra_byte = byt;
      p->extra_byte_present = 1;
    }
  }

  if(p->idx + numbytes <= p->bfr_count)
    return p->bfr + p->idx;
  else
    return NULL;
}


static uint8_t *fr_request(bufstream_tt *bs, uint32_t numbytes)
{
  struct impl_stream* p = bs->Buf_IO_struct;

  if(p->idx+numbytes <= p->bfr_count)
    return p->bfr + p->idx;

  if(p->idx == p->bfr_count)
  {
    p->idx=0;
    p->bfr_count=0;
  }

  if(p->idx+numbytes > p->bfr_size)
  {
    memcpy(p->bfr, p->bfr + p->idx, p->bfr_count - p->idx);
    p->bfr_count -= p->idx;
    p->idx=0;
  }

#ifdef WIN32IO
  {
    DWORD i;
    ReadFile(p->io, p->bfr + p->bfr_count, p->bfr_size - p->bfr_count, &i, NULL);
    p->bfr_count += i;
  }
#else
  p->bfr_count += (uint32_t) fread(p->bfr + p->bfr_count, sizeof(uint8_t), p->bfr_size - p->bfr_count, p->io);
#endif

  if(p->idx + numbytes <= p->bfr_count)
    return p->bfr + p->idx;
  else
    return NULL;
}


//confirm numbytes-bytes filled in in requested after last "request"-call
static uint32_t fw_confirm(bufstream_tt *bs, uint32_t numbytes)
{
  bs->Buf_IO_struct->idx       += numbytes;
  bs->Buf_IO_struct->bytecount += numbytes;
  return numbytes;
}


//put/get numbytes-bytes into/from bufsteam
// fifo_w_sampput/fifo_r_sampget
static uint32_t fw_copybytes(bufstream_tt *bs, uint8_t *ptr, uint32_t numbytes)
{
  struct impl_stream* p = bs->Buf_IO_struct;
#ifdef WIN32IO
  DWORD n;
#else
  uint32_t n;
#endif

  if(p->idx)
  {
#ifdef WIN32IO
    WriteFile(p->io, p->bfr, p->idx, &n, NULL);
#else
    n = (uint32_t) fwrite(p->bfr, sizeof(uint8_t), p->idx, p->io);
#endif
    if(n != p->idx)
    {
      p->idx=0;
      return 0;
    }
    p->idx=0;
  }

#ifdef WIN32IO
  WriteFile(p->io, ptr, numbytes, &n, NULL);
#else
  n = (uint32_t) fwrite(ptr, sizeof(uint8_t), numbytes, p->io);
#endif
  bs->Buf_IO_struct->bytecount += n;

  if(n != numbytes)
  {
    return 0;
  }

  return numbytes;
}


static uint32_t fr_copybytes_swap_endian(bufstream_tt *bs, uint8_t *ptr, uint32_t numbytes)
{
  struct impl_stream* p = bs->Buf_IO_struct;
  uint8_t byt, *local_ptr = ptr;
  uint32_t c, i, j;

  if(p->bfr_count != p->idx)
  {
    if(p->idx+numbytes <= p->bfr_count)
    {
      memcpy(local_ptr,p->bfr+p->idx,numbytes);
      p->idx += numbytes;
      p->bytecount +=numbytes;
      return numbytes;
    }
    else
    {
      memcpy(local_ptr,p->bfr+p->idx,p->bfr_count-p->idx);
      local_ptr += p->bfr_count - p->idx;
      c = numbytes - (p->bfr_count - p->idx);
      p->bytecount += p->bfr_count - p->idx;

      p->idx=0;
      p->bfr_count=0;

      if(p->extra_byte_present)
      {
        local_ptr[0] = p->extra_byte;
        local_ptr++;
        p->extra_byte_present = 0;
        p->bytecount++;
        c--;
      }
#ifdef WIN32IO
      ReadFile(p->io, local_ptr, c, (DWORD*)&i, NULL);
#else
      i = (uint32_t) fread(local_ptr, sizeof(uint8_t), c, p->io);
#endif
      if(i % 2)
        j = 0;

      for(j = 0; j < (i & 0xFFFFFFFE); j += 2)
      {
        byt = local_ptr[j];
        local_ptr[j] = local_ptr[j + 1];
        local_ptr[j + 1] = byt;
      }
      p->bytecount +=i;
      if((i == c) && (c % 2))
      {
        local_ptr += (i - 1);
        c = 0;
#ifdef WIN32IO
        ReadFile(p->io, &p->extra_byte, 1, (DWORD*)&i, NULL);
#else
        i = (uint32_t) fread(&p->extra_byte, sizeof(uint8_t), 1, p->io);
#endif
        if(i == 1)
        {
          byt = local_ptr[0];
          local_ptr[0] = p->extra_byte;
          p->extra_byte = byt;
          p->extra_byte_present = 1;
        }
      }
      else
        c-=i;
      return numbytes-c;
    }
  }
  else
  {
    p->idx=0;
    p->bfr_count=0;

    c = numbytes;
    if(p->extra_byte_present)
    {
      local_ptr[0] = p->extra_byte;
      local_ptr++;
      p->extra_byte_present = 0;
      p->bytecount++;
      c--;
    }

#ifdef WIN32IO
    ReadFile(p->io, local_ptr, c, (DWORD*)&i, NULL);
#else
    i = (uint32_t) fread(local_ptr, sizeof(uint8_t), c, p->io);
#endif
    if(i % 2)
      j = 0;

    for(j = 0; j < (i & 0xFFFFFFFE); j += 2)
    {
      byt = local_ptr[j];
      local_ptr[j] = local_ptr[j + 1];
      local_ptr[j + 1] = byt;
    }
    p->bytecount +=i;

    if((i == c) && (c % 2))
    {
      local_ptr += (i - 1);
      c = 0;
#ifdef WIN32IO
      ReadFile(p->io, &p->extra_byte, 1, (DWORD*)&i, NULL);
#else
      i = (uint32_t) fread(&p->extra_byte, sizeof(uint8_t), 1, p->io);
#endif
      if(i == 1)
      {
        byt = local_ptr[0];
        local_ptr[0] = p->extra_byte;
        p->extra_byte = byt;
        p->extra_byte_present = 1;
      }
    }
    else
      c-=i;
    return numbytes - c;
  }
}


static uint32_t fr_copybytes(bufstream_tt *bs, uint8_t *ptr, uint32_t numbytes)
{
  struct impl_stream* p = bs->Buf_IO_struct;

  if(p->bfr_count != p->idx)
  {
    if(p->idx+numbytes <= p->bfr_count)
    {
      memcpy(ptr,p->bfr+p->idx,numbytes);
      p->idx += numbytes;
      p->bytecount +=numbytes;
      return numbytes;
    }
    else
    {
      int32_t c,i;
      memcpy(ptr,p->bfr+p->idx,p->bfr_count-p->idx);
      c = numbytes - (p->bfr_count - p->idx);
      p->bytecount += p->bfr_count - p->idx;

      p->idx=0;
      p->bfr_count=0;

#ifdef WIN32IO
      ReadFile(p->io, ptr + numbytes - c, c, (DWORD*)&i, NULL);
#else
      i = (uint32_t) fread(ptr + numbytes - c, sizeof(uint8_t), c, p->io);
#endif
      p->bytecount +=i;
      c-=i;
      return numbytes-c;
    }
  }
  else
  {
    int32_t n;

    p->idx=0;
    p->bfr_count=0;

#ifdef WIN32IO
    ReadFile(p->io, ptr, numbytes, (DWORD*)&n, NULL);
#else
    n = (uint32_t) fread(ptr, sizeof(uint8_t), numbytes, p->io);
#endif
    p->bytecount +=n;

    return n;
  }
}


// maximum chunk-size in buffer-mode (i.e. for "request"-call)
static uint32_t fw_chunksize(bufstream_tt *bs)
{
  return bs->Buf_IO_struct->chunk_size;
}


static uint32_t fr_chunksize(bufstream_tt *bs)
{
  return bs->Buf_IO_struct->chunk_size;
}


static int32_t flush_buf(bufstream_tt *bs)
{

#ifdef WIN32IO
  if(!FlushFileBuffers(bs->Buf_IO_struct->io))
#else
  if(fflush(bs->Buf_IO_struct->io))
#endif
    return BS_ERROR;

  return BS_OK;
}


//inform bufstream about some additional info - for example
// to inform MUXer about encoding-units
static uint32_t fw_auxinfo(bufstream_tt *bs, uint32_t offs, uint32_t info_ID, void *info_ptr, uint32_t info_size)
{
  struct synci_info *synci;
  struct dvd_synci_info *sync_info;
  struct dvd_sector_info *p;
  struct dvd_ptm_info *p1;
  uint64_t *ptr;
  int32_t *ptr1;
#ifdef _BS_UNICODE
  wchar_t *ptr2;
#else
  char *ptr2;
#endif

  switch(info_ID)
  {
    case DVD_DO_NAV_INFO:
      if(!bs->Buf_IO_struct->do_nav_info)
      {
        bs->Buf_IO_struct->nav_sectors = (int32_t*) malloc(sizeof(int32_t)  * MAX_SECTORS);
        if(bs->Buf_IO_struct->nav_sectors)
        {
          bs->Buf_IO_struct->sector_times = (int32_t*) malloc(sizeof(int32_t)  * MAX_SECTORS);
          if(bs->Buf_IO_struct->sector_times)
          {
            bs->Buf_IO_struct->sector_flags = (int32_t*) malloc(sizeof(int32_t)  * MAX_SECTORS);
            if(bs->Buf_IO_struct->sector_flags)
            {
              bs->Buf_IO_struct->vob_info = (struct vob_nav_info*)malloc(sizeof(struct vob_nav_info));
              if(bs->Buf_IO_struct->vob_info)
              {
                bs->Buf_IO_struct->cell_sectors = (int32_t*) malloc(sizeof(int32_t)  * MAX_CELLS);
                if(bs->Buf_IO_struct->cell_sectors)
                {
                  memset(&bs->Buf_IO_struct->nav_sectors[0], 0, sizeof(int32_t)  * MAX_SECTORS);
                  memset(&bs->Buf_IO_struct->sector_times[0], 0, sizeof(int32_t)  * MAX_SECTORS);
                  memset(&bs->Buf_IO_struct->sector_flags[0], 0, sizeof(int32_t)  * MAX_SECTORS);
                  memset(&bs->Buf_IO_struct->cell_sectors[0], 0, sizeof(int32_t)  * MAX_CELLS);
                  bs->Buf_IO_struct->vob_info->base_idx = 0;
                  bs->Buf_IO_struct->vob_info->total_nv_sectors = 0;
                  bs->Buf_IO_struct->vob_info->end_PTM = 0;
#ifdef _BS_UNICODE
                  wcscpy(bs->Buf_IO_struct->vob_info->filename, bs->Buf_IO_struct->filename);
#else
                  strcpy(bs->Buf_IO_struct->vob_info->filename, bs->Buf_IO_struct->filename);
#endif
                  bs->Buf_IO_struct->vob_info->next = NULL;
                  bs->Buf_IO_struct->vob_info->prev = NULL;
                  bs->Buf_IO_struct->cur_vob_info = bs->Buf_IO_struct->vob_info;
                  bs->Buf_IO_struct->do_nav_info = 1;
                }
                else
                {
                  free(bs->Buf_IO_struct->nav_sectors);
                  bs->Buf_IO_struct->nav_sectors = NULL;
                  free(bs->Buf_IO_struct->sector_times);
                  bs->Buf_IO_struct->sector_times = NULL;
                  free(bs->Buf_IO_struct->sector_flags);
                  bs->Buf_IO_struct->sector_flags = NULL;
                  free(bs->Buf_IO_struct->vob_info);
                  bs->Buf_IO_struct->vob_info = NULL;
                }
              }
              else
              {
                free(bs->Buf_IO_struct->nav_sectors);
                bs->Buf_IO_struct->nav_sectors = NULL;
                free(bs->Buf_IO_struct->sector_times);
                bs->Buf_IO_struct->sector_times = NULL;
                free(bs->Buf_IO_struct->sector_flags);
                bs->Buf_IO_struct->sector_flags = NULL;
              }
            }
            else
            {
              free(bs->Buf_IO_struct->nav_sectors);
              bs->Buf_IO_struct->nav_sectors = NULL;
              free(bs->Buf_IO_struct->sector_times);
              bs->Buf_IO_struct->sector_times = NULL;
            }
          }
          else
          {
            free(bs->Buf_IO_struct->nav_sectors);
            bs->Buf_IO_struct->nav_sectors = NULL;
          }
        }
      }
      break;

    case DVD_DO_ASYNCI_INFO:
      if(bs->Buf_IO_struct->do_nav_info)
      {
        if(bs->Buf_IO_struct->num_audio_streams >= MAX_AUDIO_STREAMS)
          return (uint32_t)BS_ERROR;

        synci = &bs->Buf_IO_struct->asynci[bs->Buf_IO_struct->num_audio_streams];

        synci->synci_sectors = (int32_t*) malloc(sizeof(int32_t)  * MAX_SECTORS);
        if(!synci->synci_sectors)
          return (uint32_t)BS_ERROR;

        memset(synci->synci_sectors, 0, MAX_SECTORS * 4);
        synci->synci_idx = 0;
        bs->Buf_IO_struct->num_audio_streams++;
        return bs->Buf_IO_struct->num_audio_streams - 1;
      }
      break;

    case DVD_DO_SPSYNCI_INFO:
      if(bs->Buf_IO_struct->do_nav_info)
      {
        if(bs->Buf_IO_struct->num_subpic_streams >= MAX_SUBPIC_STREAMS)
          return (uint32_t)BS_ERROR;

        synci = &bs->Buf_IO_struct->spsynci[bs->Buf_IO_struct->num_subpic_streams];

        synci->synci_sectors = (int32_t*) malloc(sizeof(int32_t)  * MAX_SECTORS);
        if(!synci->synci_sectors)
          return (uint32_t)BS_ERROR;

        memset(synci->synci_sectors, 0, MAX_SECTORS * 4);
        synci->synci_idx = 0;
        bs->Buf_IO_struct->num_subpic_streams++;
        return bs->Buf_IO_struct->num_subpic_streams - 1;
      }
      break;

    case DVD_ASYNCI_INFO:
      if(bs->Buf_IO_struct->do_nav_info && info_ptr && (info_size == sizeof(struct dvd_synci_info)))
      {
        sync_info = (struct dvd_synci_info*)info_ptr;
        if(sync_info->stream_num < bs->Buf_IO_struct->num_audio_streams)
        {
          synci = &bs->Buf_IO_struct->asynci[sync_info->stream_num];
          if(synci->synci_sectors)
          {
            if(synci->synci_idx < MAX_SECTORS)
              synci->synci_sectors[synci->synci_idx++] = sync_info->sector_offset;
          }
        }
      }
      break;

    case DVD_SPSYNCI_INFO:
      if(bs->Buf_IO_struct->do_nav_info && info_ptr && (info_size == sizeof(struct dvd_synci_info)))
      {
        sync_info = (struct dvd_synci_info*)info_ptr;
        if(sync_info->stream_num < bs->Buf_IO_struct->num_subpic_streams)
        {
          synci = &bs->Buf_IO_struct->spsynci[sync_info->stream_num];
          if(synci->synci_sectors)
          {
            if(synci->synci_idx < MAX_SECTORS)
              synci->synci_sectors[synci->synci_idx++] = sync_info->sector_offset;
          }
        }
      }
      break;

    case DVD_SECTOR_NUM:
      if(bs->Buf_IO_struct->do_nav_info)
      {
        p = (struct dvd_sector_info*)info_ptr;

        if(bs->Buf_IO_struct->nav_sector_idx < MAX_SECTORS)
        {
          bs->Buf_IO_struct->nav_sectors[bs->Buf_IO_struct->nav_sector_idx] = p->sector_num;
          bs->Buf_IO_struct->sector_times[bs->Buf_IO_struct->nav_sector_idx] = p->sector_length;
          bs->Buf_IO_struct->sector_flags[bs->Buf_IO_struct->nav_sector_idx] = p->flags;
          bs->Buf_IO_struct->nav_sector_idx++;
          bs->Buf_IO_struct->cur_vob_info->total_nv_sectors++;
        }
      }
      break;

    case DVD_CELL_CHANGE:
      bs->Buf_IO_struct->cell_sectors[bs->Buf_IO_struct->num_cells++] = bs->Buf_IO_struct->nav_sector_idx;
      break;

    case DVD_PTM_TIME:
      if(bs->Buf_IO_struct->do_nav_info)
      {
        p1 = (struct dvd_ptm_info*)info_ptr;

        bs->Buf_IO_struct->cur_vob_info->end_PTM = p1->PTM_time;
      }
      break;

    case DVD_DO_HLI_PTM_TIME:
      if(bs->Buf_IO_struct->do_nav_info)
      {
        bs->Buf_IO_struct->do_hli_ptm_time = 1;
      }
      break;

    case DVD_ABORT_NAV_INFO:
      bs->Buf_IO_struct->abort_nav_info = 1;
      break;

    case DVD_FIXUP_SYNCI:
      if(bs->Buf_IO_struct->do_nav_info)
        bs->Buf_IO_struct->fixup_synci_sector = (int32_t) offs;
      break;

    case BYTECOUNT_INFO:
      {
        ptr = (uint64_t*)info_ptr;
        if(ptr && (info_size == sizeof(uint64_t)))
          *ptr = bs->Buf_IO_struct->bytecount;
      }
      break;

    case FLUSH_BUFFER:
      flush_buf(bs);
      break;

    case SPLIT_OUTPUT:
      bs->split(bs);
      break;

    case FILENUMBER_INFO:
      {
        ptr1 = (int32_t*)info_ptr;
        if(ptr1 && (info_size == sizeof(int32_t) ))
          *ptr1 = bs->Buf_IO_struct->filenumber;
      }
      break;

    case FILENAME_INFO:
      {
#ifdef _BS_UNICODE
        ptr2 = (wchar_t*)info_ptr;
        if(ptr2 && (info_size > wcslen(bs->Buf_IO_struct->filename) * 2))
          wcscpy(ptr2, bs->Buf_IO_struct->filename);
#else
        ptr2 = (char*)info_ptr;
        if(ptr2 && (info_size > strlen(bs->Buf_IO_struct->filename)))
          strcpy(ptr2, bs->Buf_IO_struct->filename);
#endif
        else
          return (uint32_t)BS_ERROR;
      }
      break;
  }
  return (uint32_t)BS_OK;
}


static uint32_t fr_auxinfo(bufstream_tt *bs, uint32_t offs, uint32_t info_ID, void *info_ptr, uint32_t info_size)
{
  if (offs){}; // remove compile warning
  switch(info_ID)
  {
    case SWAP_ENDIAN:
      bs->request  = fr_request_swap_endian;
      bs->copybytes= fr_copybytes_swap_endian;
      break;
    case BYTECOUNT_INFO:
      {
        uint64_t *ptr = (uint64_t*)info_ptr;
        if(ptr && (info_size == sizeof(uint64_t)))
          *ptr = bs->Buf_IO_struct->bytecount;
      }
      break;
    case FILESIZE_INFO:
      {
        uint64_t *ptr = (uint64_t*)info_ptr;
        if(ptr && (info_size == sizeof(uint64_t)))
          *ptr = bs->Buf_IO_struct->file_size;
      }
      break;
  }
  return BS_OK;
}


static void fw_done(bufstream_tt *bs, int32_t Abort)
{
  
  struct impl_stream* p = bs->Buf_IO_struct;
  int32_t i;

  if (Abort){}; // remove compile warning

#ifdef WIN32IO
  DWORD n;
  WriteFile(p->io, p->bfr, p->idx, &n, NULL);
  CloseHandle(p->io);
#else
  fwrite(p->bfr, sizeof(uint8_t), p->idx, p->io);
  fclose(p->io);
#endif

  if(p->do_nav_info)
  {
    if(!p->abort_nav_info)
    {
      doVOBNavInfo(bs, p->vob_info);
      p->cur_vob_info = p->vob_info;
      while(p->cur_vob_info->next)
      {
        doVOBNavInfo(bs, p->cur_vob_info->next);
        p->cur_vob_info = p->cur_vob_info->next;
      }
    }

    while(p->cur_vob_info->prev)
    {
      p->cur_vob_info = p->cur_vob_info->prev;
      free(p->cur_vob_info->next);
    }
    if(p->vob_info)
      free(p->vob_info);
    if(p->nav_sectors)
      free(p->nav_sectors);
    if(p->cell_sectors)
      free(p->cell_sectors);
    if(p->sector_times)
      free(p->sector_times);
    if(p->sector_flags)
      free(p->sector_flags);
    for(i = 0; i < MAX_AUDIO_STREAMS; i++)
    {
      if(p->asynci[i].synci_sectors)
        free(p->asynci[i].synci_sectors);
    }
    for(i = 0; i < MAX_SUBPIC_STREAMS; i++)
    {
      if(p->spsynci[i].synci_sectors)
        free(p->spsynci[i].synci_sectors);
    }
  }
  free(p->bfr);
  free(p);
  bs->Buf_IO_struct = NULL;
}


static void fr_done(bufstream_tt *bs, int32_t Abort)
{
  struct impl_stream* p = bs->Buf_IO_struct;

  if (Abort){}; // remove compile warning

#ifdef WIN32IO
  CloseHandle(p->io);
#else
  fclose(p->io);
#endif
  free(p->bfr);
  free(p);
  bs->Buf_IO_struct = NULL;
}


static void fw_free(bufstream_tt *bs)
{
  if(bs->Buf_IO_struct)
    bs->done(bs,0);

  free(bs);
}


static void fr_free(bufstream_tt *bs)
{
  if(bs->Buf_IO_struct)
    bs->done(bs,0);

  free(bs);
}


static uint32_t fw_split(bufstream_tt *bs)
{
  struct impl_stream* p = bs->Buf_IO_struct;
#ifdef _BS_UNICODE
  wchar_t *ptr;
#else
  char *ptr;
#endif

#ifdef WIN32IO
  DWORD n;
  WriteFile(p->io, p->bfr, p->idx, &n, NULL);
  CloseHandle(p->io);
#else
  fwrite(p->bfr, sizeof(uint8_t), p->idx, p->io);
  fclose(p->io);
  p->io = NULL;
#endif


  p->bfr_count  = 0;
  p->idx        = 0;

#ifdef _BS_UNICODE
  if(!wcslen(p->basename))
  {
    wcscpy(p->basename, p->filename);
    ptr = wcsrchr(p->basename, '.');
    if(ptr)
    {
      wcscpy(p->baseext, ptr);
      wcscpy(ptr, L"");
    }
  }

  if(p->filenumber < 0)
    return (uint32_t)BS_ERROR; // limit to 2^31 files?
  else if(p->filenumber >= 1000000000)
    swprintf(p->filename, _BS_MAX_PATH, L"%s%010d%s", p->basename, p->filenumber + 1, p->baseext);
  else if(p->filenumber >= 100000000)
    swprintf(p->filename, _BS_MAX_PATH, L"%s%09d%s", p->basename, p->filenumber + 1, p->baseext);
  else if(p->filenumber >= 10000000)
    swprintf(p->filename, _BS_MAX_PATH, L"%s%08d%s", p->basename, p->filenumber + 1, p->baseext);
  else if(p->filenumber >= 1000000)
    swprintf(p->filename, _BS_MAX_PATH, L"%s%07d%s", p->basename, p->filenumber + 1, p->baseext);
  else if(p->filenumber >= 100000)
    swprintf(p->filename, _BS_MAX_PATH, L"%s%06d%s", p->basename, p->filenumber + 1, p->baseext);
  else if(p->filenumber >= 10000)
    swprintf(p->filename, _BS_MAX_PATH, L"%s%05d%s", p->basename, p->filenumber + 1, p->baseext);
  else if(p->filenumber >= 1000)
    swprintf(p->filename, _BS_MAX_PATH, L"%s%04d%s", p->basename, p->filenumber + 1, p->baseext);
  else
    swprintf(p->filename, _BS_MAX_PATH, L"%s%03d%s", p->basename, p->filenumber + 1, p->baseext);
#else
  if(!strlen(p->basename))
  {
    strcpy(p->basename, p->filename);
    ptr = strrchr(p->basename, '.');
    if(ptr)
    {
      strcpy(p->baseext, ptr);
      ptr[0] = 0;
    }
  }

  if(p->filenumber < 0)
    return BS_ERROR; // limit to 2^31 files?
  else if(p->filenumber >= 1000000000)
    sprintf(p->filename, "%s%010d%s", p->basename, p->filenumber + 1, p->baseext);
  else if(p->filenumber >= 100000000)
    sprintf(p->filename, "%s%09d%s", p->basename, p->filenumber + 1, p->baseext);
  else if(p->filenumber >= 10000000)
    sprintf(p->filename, "%s%08d%s", p->basename, p->filenumber + 1, p->baseext);
  else if(p->filenumber >= 1000000)
    sprintf(p->filename, "%s%07d%s", p->basename, p->filenumber + 1, p->baseext);
  else if(p->filenumber >= 100000)
    sprintf(p->filename, "%s%06d%s", p->basename, p->filenumber + 1, p->baseext);
  else if(p->filenumber >= 10000)
    sprintf(p->filename, "%s%05d%s", p->basename, p->filenumber + 1, p->baseext);
  else if(p->filenumber >= 1000)
    sprintf(p->filename, "%s%04d%s", p->basename, p->filenumber + 1, p->baseext);
  else
    sprintf(p->filename, "%s%03d%s", p->basename, p->filenumber + 1, p->baseext);
#endif

#ifdef WIN32IO
 #ifdef _BS_UNICODE
  p->io = CreateFileW(p->filename,
 #else
  p->io = CreateFile(p->filename,
 #endif
                         GENERIC_WRITE, FILE_SHARE_READ,
                         NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
                         NULL);
  if(p->io == INVALID_HANDLE_VALUE)
#else
 #ifdef _BS_UNICODE
  p->io = _wfopen(p->filename, L"wb");
 #else
  #if !defined(__QNX__)
   p->io = fopen(p->filename, "wb");
  #else
   p->io = fopen64(p->filename, "wb");
  #endif
 #endif
  if(!p->io)
#endif
  {
    return (uint32_t)BS_ERROR;
  }
  p->filenumber++;
  p->bytecount = 0;

  if(p->do_nav_info)
  {
    p->cur_vob_info->next = (struct vob_nav_info*)malloc(sizeof(struct vob_nav_info));
    if(p->cur_vob_info->next)
    {
      p->cur_vob_info->next->base_idx = p->nav_sector_idx;
      p->cur_vob_info->next->total_nv_sectors = 0;
      p->cur_vob_info->next->end_PTM = 0;
#ifdef _BS_UNICODE
      wcscpy(p->cur_vob_info->next->filename, p->filename);
#else
      strcpy(p->cur_vob_info->next->filename, p->filename);
#endif
      p->cur_vob_info->next->next = NULL;
      p->cur_vob_info->next->prev = p->cur_vob_info;
      p->cur_vob_info = p->cur_vob_info->next;
    }
  }
  return (uint32_t)0;
}


static int32_t init_write_common(bufstream_tt *bs, uint32_t bufsize)
{
  bs->Buf_IO_struct->bfr = (uint8_t*)malloc(bufsize);
  if(!bs->Buf_IO_struct->bfr)
  {
#ifdef WIN32IO
    CloseHandle(bs->Buf_IO_struct->io);
#else
    fclose(bs->Buf_IO_struct->io);
#endif
    free(bs->Buf_IO_struct);
    return BS_ERROR;
  }

  bs->Buf_IO_struct->bfr_size           = bufsize;
  bs->Buf_IO_struct->bfr_count          = 0;
  bs->Buf_IO_struct->chunk_size         = bufsize;
  bs->Buf_IO_struct->idx                = 0;
  bs->Buf_IO_struct->bytecount          = 0;
  bs->Buf_IO_struct->extra_byte         = 0;
  bs->Buf_IO_struct->extra_byte_present = 0;

  bs->Buf_IO_struct->filenumber  = 0;
  bs->Buf_IO_struct->basename[0] = 0;
  bs->Buf_IO_struct->baseext[0]  = 0;

  bs->Buf_IO_struct->do_nav_info     = 0;
  bs->Buf_IO_struct->abort_nav_info  = 0;
  bs->Buf_IO_struct->nav_sectors     = NULL;
  bs->Buf_IO_struct->cell_sectors    = NULL;
  bs->Buf_IO_struct->num_cells       = 0;
  bs->Buf_IO_struct->sector_times    = NULL;
  bs->Buf_IO_struct->sector_flags    = NULL;
  bs->Buf_IO_struct->nav_sector_idx  = 0;
  bs->Buf_IO_struct->vob_info        = NULL;
  bs->Buf_IO_struct->cur_vob_info    = NULL;
  bs->Buf_IO_struct->fixup_synci_sector = 0;
  bs->Buf_IO_struct->do_hli_ptm_time = 0;

  memset(bs->Buf_IO_struct->asynci, 0, sizeof(bs->Buf_IO_struct->asynci));
  bs->Buf_IO_struct->num_audio_streams = 0;
  memset(bs->Buf_IO_struct->spsynci, 0, sizeof(bs->Buf_IO_struct->spsynci));
  bs->Buf_IO_struct->num_subpic_streams = 0;

  bs->usable_bytes = fw_usable_bytes;
  bs->request      = fw_request;
  bs->confirm      = fw_confirm;
  bs->copybytes    = fw_copybytes;
  bs->split        = fw_split;
  bs->chunksize    = fw_chunksize;
  bs->free         = fw_free;
  bs->auxinfo      = fw_auxinfo;
  bs->done         = fw_done;
  bs->drive_ptr    = NULL;
  bs->drive        = NULL;

  bs->state        = NULL;
  bs->flags        = BS_FLAGS_DST;
  return BS_OK;
}


#ifdef _BS_UNICODE
int32_t init_file_buf_write(bufstream_tt *bs,
                            const wchar_t* bs_filename,
                            uint32_t bufsize, 
                            void (*DisplayError)(char *txt))
#else
int32_t init_file_buf_write(bufstream_tt *bs,
                            const char *bs_filename,
                            uint32_t bufsize, 
                            void (*DisplayError)(char *txt))
#endif
{
  if (DisplayError){};  // remove compile warning

  bs->Buf_IO_struct = (struct impl_stream*)malloc(sizeof(struct impl_stream));
  if(!bs->Buf_IO_struct || !bs_filename)
  {
    return BS_ERROR;
  }
#ifdef WIN32IO
  bs->Buf_IO_struct->io = 
 #ifdef _BS_UNICODE
      CreateFileW(bs_filename, 
 #else
      CreateFile(bs_filename, 
 #endif
                 GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS,
                 FILE_ATTRIBUTE_NORMAL,
                 NULL);
  if(bs->Buf_IO_struct->io == INVALID_HANDLE_VALUE)
#else
 #ifdef _BS_UNICODE
   bs->Buf_IO_struct->io = _wfopen(bs_filename, L"wb");
 #else
  #if !defined(__QNX__)
   bs->Buf_IO_struct->io = fopen(bs_filename, "wb");
  #else
   bs->Buf_IO_struct->io = fopen64(bs_filename, "wb");
  #endif
 #endif
  if(!bs->Buf_IO_struct->io)
#endif
  {
    free(bs->Buf_IO_struct);
    return BS_ERROR;
  }

#ifdef _BS_UNICODE
  wcscpy(bs->Buf_IO_struct->filename, bs_filename);
#else
  strcpy(bs->Buf_IO_struct->filename, bs_filename);
#endif

  return init_write_common(bs, bufsize);
}


// same as init_file_buf_write except the fopen call is with a 'c'
// so the stream can be flushed

#ifdef _BS_UNICODE
int32_t init_file_buf_write_flushable(bufstream_tt *bs,
                                      const wchar_t* bs_filename,
                                      uint32_t bufsize,
                                      void (*DisplayError)(char *txt))
#else
int32_t init_file_buf_write_flushable(bufstream_tt *bs,
                                      const char *bs_filename,
                                      uint32_t bufsize,
                                      void (*DisplayError)(char *txt))
#endif
{
  if (DisplayError){};  // remove compile warning

  bs->Buf_IO_struct = (struct impl_stream*)malloc(sizeof(struct impl_stream));
  if(!(bs->Buf_IO_struct) || !bs_filename)
  {
    return BS_ERROR;
  }
#ifdef WIN32IO
  bs->Buf_IO_struct->io = 
 #ifdef _BS_UNICODE
      CreateFileW(bs_filename, 
 #else
      CreateFile(bs_filename, 
 #endif
                 GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS,
                 FILE_ATTRIBUTE_NORMAL,
                 NULL);
  if(bs->Buf_IO_struct->io == INVALID_HANDLE_VALUE)
#else
 #ifdef _BS_UNICODE
  bs->Buf_IO_struct->io = _wfopen(bs_filename, L"wbc");
 #else
  #if !defined(__QNX__)
    bs->Buf_IO_struct->io = fopen(bs_filename, "wbc");
  #else
    bs->Buf_IO_struct->io = fopen64(bs_filename, "wbc");
  #endif
 #endif
  if(!(bs->Buf_IO_struct->io))
#endif
  {
    free(bs->Buf_IO_struct);
    return BS_ERROR;
  }

#ifdef _BS_UNICODE
  wcscpy(bs->Buf_IO_struct->filename, bs_filename);
#else
  strcpy(bs->Buf_IO_struct->filename, bs_filename);
#endif

  return init_write_common(bs, bufsize);
}


// same as init_file_buf_write except is does not reset the file pointer to 0

#ifdef _BS_UNICODE
int32_t init_file_buf_write_existing(bufstream_tt *bs,
                                     const wchar_t* bs_filename,
                                     uint32_t bufsize,
                                     void (*DisplayError)(char *txt))
#else
int32_t init_file_buf_write_existing(bufstream_tt *bs,
                                     const char *bs_filename,
                                     uint32_t bufsize, 
                                     void (*DisplayError)(char *txt))
#endif
{
  if (DisplayError){};  // remove compile warning

  bs->Buf_IO_struct = (struct impl_stream*)malloc(sizeof(struct impl_stream));
  if(!(bs->Buf_IO_struct) || !bs_filename)
  {
    return BS_ERROR;
  }
#ifdef WIN32IO
  bs->Buf_IO_struct->io = 
 #ifdef _BS_UNICODE
      CreateFileW(bs_filename, 
 #else
      CreateFile(bs_filename, 
 #endif
                 GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS,
                 FILE_ATTRIBUTE_NORMAL,
                 NULL);
  if(bs->Buf_IO_struct->io == INVALID_HANDLE_VALUE)
#else
 #ifdef _BS_UNICODE
  if((bs->Buf_IO_struct->io = _wfopen(bs_filename, L"r+b")) == 0)
    if((bs->Buf_IO_struct->io = _wfopen(bs_filename, L"wb")) == 0)
 #else
  #if !defined(__QNX__)
  bs->Buf_IO_struct->io = fopen(bs_filename, "r+b");
  if(!(bs->Buf_IO_struct->io))
    bs->Buf_IO_struct->io = fopen(bs_filename, "wb");
  #else
  bs->Buf_IO_struct->io = fopen64(bs_filename, "r+b");
  if(!(bs->Buf_IO_struct->io))
	bs->Buf_IO_struct->io = fopen64(bs_filename, "wb");
  #endif
 #endif
	if(!(bs->Buf_IO_struct->io))
#endif
    {
      free (bs->Buf_IO_struct);
      return BS_ERROR;
    }

#ifdef WIN32IO
  if(SetFilePointer(bs->Buf_IO_struct->io, 0, NULL, FILE_BEGIN) == 0xFFFFFFFF)
#else
  if(fseek(bs->Buf_IO_struct->io, 0,SEEK_SET))
#endif
  {
#ifdef WIN32IO
    CloseHandle(bs->Buf_IO_struct->io);
#else
    fclose(bs->Buf_IO_struct->io);
#endif
    free (bs->Buf_IO_struct);
    return BS_ERROR;
  }

#ifdef _BS_UNICODE
  wcscpy(bs->Buf_IO_struct->filename, bs_filename);
#else
  strcpy(bs->Buf_IO_struct->filename, bs_filename);
#endif

  return init_write_common(bs, bufsize);
}


#ifdef _BS_UNICODE
int32_t init_file_buf_read(bufstream_tt *bs,
                           const wchar_t* bs_filename,
                           uint32_t bufsize,
                           void (*DisplayError)(char *txt))
#else
int32_t init_file_buf_read(bufstream_tt *bs,
                           const char *bs_filename,
                           uint32_t bufsize,
                           void (*DisplayError)(char *txt))
#endif
{
#ifndef WIN32IO
 #if !defined(__APPLE__) && !defined(__linux__) && !defined(__native_client__) && !defined(__QNX__)
  struct _stati64 stat_data;
 #else
  #if defined(__QNX__)
  struct stat64 stat_data;
  #else
  struct stat stat_data;
  #endif
 #endif
  int32_t fde;
#endif

  if (DisplayError){};  // remove compile warning
//
// One can add Autocontinue-option here i.e. auto open splitted file
// and continue from split-point seamless
//

  bs->Buf_IO_struct = (struct impl_stream*)malloc(sizeof(struct impl_stream));
  if(!(bs->Buf_IO_struct) || !bs_filename)
  {
    return BS_ERROR;
  }

#ifdef WIN32IO
  bs->Buf_IO_struct->io = 
 #ifdef _BS_UNICODE
      CreateFileW(bs_filename,
 #else 
      CreateFile(bs_filename,
 #endif
                 GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
                 FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN,
                 NULL);
  if(bs->Buf_IO_struct->io == INVALID_HANDLE_VALUE)
#else
 #ifdef _BS_UNICODE
    bs->Buf_IO_struct->io = _wfopen(bs_filename, L"rb");
 #else
  #if !defined(__QNX__)
    bs->Buf_IO_struct->io = fopen(bs_filename, "rb");
  #else
    bs->Buf_IO_struct->io = fopen64(bs_filename, "rb");
  #endif
 #endif
  if(!(bs->Buf_IO_struct->io))
#endif
  {
    free(bs->Buf_IO_struct);
    return BS_ERROR;
  }

#ifdef WIN32IO
  BY_HANDLE_FILE_INFORMATION file_info;

  if(!GetFileInformationByHandle(bs->Buf_IO_struct->io, &file_info))
  {
    CloseHandle(bs->Buf_IO_struct->io);
    free(bs->Buf_IO_struct);
    return BS_ERROR;
  }

  bs->Buf_IO_struct->file_size = ((uint64_t)file_info.nFileSizeHigh << 32) | file_info.nFileSizeLow;
#else

 #ifdef _BS_UNICODE
  fde = _wstati64(bs_filename, &stat_data);
 #else
  #if !defined(__APPLE__) && !defined(__linux__) && !defined(__native_client__) && !defined(__QNX__)
  fde = _stati64(bs_filename, &stat_data);
  #else
   #if defined(__QNX__)
  fde = stat64(bs_filename, &stat_data);
   #else
  fde = stat(bs_filename,&stat_data);
   #endif
  #endif
 #endif

  if(fde < 0)
  {
    fclose(bs->Buf_IO_struct->io);
    free(bs->Buf_IO_struct);
    return BS_ERROR;
  }

  bs->Buf_IO_struct->file_size = stat_data.st_size;
#endif

  bs->Buf_IO_struct->bfr = (uint8_t*)malloc(bufsize);
  if(!(bs->Buf_IO_struct->bfr))
  {
#ifdef WIN32IO
    CloseHandle(bs->Buf_IO_struct->io);
#else
    fclose(bs->Buf_IO_struct->io);
#endif
    free(bs->Buf_IO_struct);
    return BS_ERROR;
  }

  bs->Buf_IO_struct->bfr_size           = bufsize;
  bs->Buf_IO_struct->bfr_count          = 0;
  bs->Buf_IO_struct->chunk_size         = bufsize;
  bs->Buf_IO_struct->idx                = 0;
  bs->Buf_IO_struct->bytecount          = 0;
  bs->Buf_IO_struct->extra_byte         = 0;
  bs->Buf_IO_struct->extra_byte_present = 0;

  bs->usable_bytes = fr_usable_bytes;
  bs->request  = fr_request;
  bs->confirm  = fr_confirm;
  bs->copybytes= fr_copybytes;
  bs->split    = NULL;
  bs->chunksize= fr_chunksize;
  bs->free     = fr_free;
  bs->auxinfo  = fr_auxinfo;
  bs->done     = fr_done;
  bs->drive_ptr= NULL;
  bs->drive    = NULL;

  bs->state      = 0;
  bs->flags      = 0;
  return BS_OK;
}


void exit_file_buf_read(bufstream_tt *bs,
                        int32_t Abort)
{
  bs->done(bs, Abort);
}


#ifdef _BS_UNICODE
bufstream_tt *open_file_buf_write(const wchar_t* bs_filename,
                                  uint32_t bufsize,
                                  void (*DisplayError)(char *txt))
#else
bufstream_tt *open_file_buf_write(const char *bs_filename,
                                  uint32_t bufsize,
                                  void (*DisplayError)(char *txt))
#endif
{
  bufstream_tt *p;
  p=(bufstream_tt*)malloc(sizeof(bufstream_tt));
  if(p)
  {
    if(BS_OK != init_file_buf_write(p, bs_filename, bufsize, DisplayError))
    {
      free(p);
      p = NULL;
    }
  }
  return p;
}


#ifdef _BS_UNICODE
bufstream_tt *open_file_buf_write_flushable(const wchar_t* bs_filename,
                                            uint32_t bufsize,
                                            void (*DisplayError)(char *txt))
#else
bufstream_tt *open_file_buf_write_flushable(const char *bs_filename,
                                            uint32_t bufsize,
                                            void (*DisplayError)(char *txt))
#endif
{
  bufstream_tt *p;
  p=(bufstream_tt*)malloc(sizeof(bufstream_tt));
  if(p)
  {
    if(BS_OK != init_file_buf_write_flushable(p, bs_filename, bufsize, DisplayError))
    {
      free(p);
      p = NULL;
    }
  }
  return p;
}


#ifdef _BS_UNICODE
bufstream_tt *open_file_buf_write_existing(const wchar_t* bs_filename,
                                           uint32_t bufsize,
                                           void (*DisplayError)(char *txt))
#else
bufstream_tt *open_file_buf_write_existing(const char *bs_filename,
                                           uint32_t bufsize,
                                           void (*DisplayError)(char *txt))
#endif
{
  bufstream_tt *p;
  p=(bufstream_tt*)malloc(sizeof(bufstream_tt));
  if(p)
  {
    if(BS_OK != init_file_buf_write_existing(p, bs_filename, bufsize, DisplayError))
    {
      free(p);
      p = NULL;
    }
  }
  return p;
}


#ifdef _BS_UNICODE
bufstream_tt *open_file_buf_read(const wchar_t* bs_filename,
                                 uint32_t bufsize,
                                 void (*DisplayError)(char *txt))
#else
bufstream_tt *open_file_buf_read(const char *bs_filename,
                                 uint32_t bufsize,
                                 void (*DisplayError)(char *txt))
#endif
{
  bufstream_tt *p;
  p=(bufstream_tt*)malloc(sizeof(bufstream_tt));
  if(p)
  {
    if(BS_OK != init_file_buf_read(p, bs_filename, bufsize, DisplayError))
    {
      free(p);
      p = NULL;
    }
  }
  return p;
}


void close_file_buf(bufstream_tt* bs,
                    int32_t Abort)
{
  bs->done(bs, Abort);
  bs->free(bs);
}

#define VOBU_E_PTM_OFFSET     61
#define HLI_E_PTM_OFFSET      147
#define VOBU_EA_OFFSET        1039
#define VOB_V_E_PTM_OFFSET    1079
#define SRI_OFFSET            1265
#define SYNCI_OFFSET          1433


#define TIME240    10800000       
#define TIME120     5400000       
#define TIME60      2700000
#define TIME20       900000
#define TIME15       675000       
#define TIME14       630000
#define TIME13       585000
#define TIME12       540000
#define TIME11       495000
#define TIME10       450000
#define TIME9        405000
#define TIME8        360000
#define TIME7        315000
#define TIME6        270000
#define TIME5        225000
#define TIME4        180000
#define TIME3        135000
#define TIME2         90000
#define TIME1         45000


static int32_t doFWDI1_15(bufstream_tt *bs, int32_t idx, int32_t time_val, int32_t last_cell_idx, uint8_t *buffer, int32_t sri_offset)
{
  int32_t i, j, k;
  int32_t pred_exists = 0;
  int32_t *sector_nums = bs->Buf_IO_struct->nav_sectors;
  int32_t *sector_times = bs->Buf_IO_struct->sector_times;
  int32_t *sector_flags = bs->Buf_IO_struct->sector_flags;

  j = idx;
  k = 0;
  while((k < time_val) && (j <= last_cell_idx))
    k += sector_times[j++];

  if(k >= time_val)
  {
    j--;
    if(sector_flags[j] & SECTOR_FLAG_HAS_VIDEO)
      i = 0x80000000;
    else
      i = 0;
    i |= ((sector_nums[j] - sector_nums[idx]) & 0x3FFFFFFF);
    pred_exists = j;
  }
  else
    i = 0x3FFFFFFF;
  buffer[SRI_OFFSET + sri_offset]     = (uint8_t) ((i & 0xff000000) >> 24);
  buffer[SRI_OFFSET + sri_offset + 1] = (uint8_t) ((i & 0x00ff0000) >> 16);
  buffer[SRI_OFFSET + sri_offset + 2] = (uint8_t) ((i & 0x0000ff00) >>  8);
  buffer[SRI_OFFSET + sri_offset + 3] = (uint8_t) ( i & 0x000000ff);

  return pred_exists;
}


static int32_t doFWDI20_240(bufstream_tt *bs, int32_t idx, int32_t time_val, int32_t last_cell_idx, uint8_t *buffer, int32_t sri_offset, int32_t pexists)
{
  int32_t i, j, k;
  int32_t pred_exists = 0;
  int32_t *sector_nums = bs->Buf_IO_struct->nav_sectors;
  int32_t *sector_times = bs->Buf_IO_struct->sector_times;
  int32_t *sector_flags = bs->Buf_IO_struct->sector_flags;

  j = idx;
  k = 0;
  while((k < time_val) && (j <= last_cell_idx))
    k += sector_times[j++];

  if(k >= time_val)
  {
    j--;
    i = 0;
    if(sector_flags[j] & SECTOR_FLAG_HAS_VIDEO)
      i = 0x80000000;

    for(k = j - 1; k > idx; k--)
    {
      if(sector_flags[k] & SECTOR_FLAG_HAS_VIDEO)
      {
        i |= 0x40000000;
        break;
      }
    }

    i |= ((sector_nums[j] - sector_nums[idx]) & 0x3FFFFFFF);
    pred_exists = j;
  }
  else
  {
    i = 0x3FFFFFFF;
    if(pexists)
    {
      for(k = pexists + 1; k <= last_cell_idx; k++)
      {
        if(sector_flags[k] & SECTOR_FLAG_HAS_VIDEO)
        {
          i |= 0x40000000;
          break;
        }
      }
    }
  }

  buffer[SRI_OFFSET + sri_offset]     = (uint8_t) ((i & 0xff000000) >> 24);
  buffer[SRI_OFFSET + sri_offset + 1] = (uint8_t) ((i & 0x00ff0000) >> 16);
  buffer[SRI_OFFSET + sri_offset + 2] = (uint8_t) ((i & 0x0000ff00) >>  8);
  buffer[SRI_OFFSET + sri_offset + 3] = (uint8_t) ( i & 0x000000ff);

  return pred_exists;
}


static int32_t doBWDI1_15(bufstream_tt *bs, int32_t idx, int32_t time_val, int32_t first_cell_idx, uint8_t *buffer, int32_t sri_offset)
{
  int32_t i, j, k;
  int32_t pred_exists = 0;
  int32_t *sector_nums = bs->Buf_IO_struct->nav_sectors;
  int32_t *sector_times = bs->Buf_IO_struct->sector_times;
  int32_t *sector_flags = bs->Buf_IO_struct->sector_flags;

  j = idx - 1;
  k = 0;
  while((k < time_val) && (j >= first_cell_idx))
    k += sector_times[j--];

  if(k >= time_val)
  {
    j++;
    if(sector_flags[j] & SECTOR_FLAG_HAS_VIDEO)
      i = 0x80000000;
    else
      i = 0;
    i |= ((sector_nums[idx] - sector_nums[j]) & 0x3FFFFFFF);
    pred_exists = j;
  }
  else
    i = 0x3FFFFFFF;

  buffer[SRI_OFFSET + sri_offset]     = (uint8_t) ((i & 0xff000000) >> 24);
  buffer[SRI_OFFSET + sri_offset + 1] = (uint8_t) ((i & 0x00ff0000) >> 16);
  buffer[SRI_OFFSET + sri_offset + 2] = (uint8_t) ((i & 0x0000ff00) >>  8);
  buffer[SRI_OFFSET + sri_offset + 3] =  (uint8_t) (i & 0x000000ff);

  return pred_exists;
}


static int32_t doBWDI20_240(bufstream_tt *bs, int32_t idx, int32_t time_val, int32_t first_cell_idx, uint8_t *buffer, int32_t sri_offset, int32_t pexists)
{
  int32_t i, j, k;
  int32_t pred_exists = 0;
  int32_t *sector_nums = bs->Buf_IO_struct->nav_sectors;
  int32_t *sector_times = bs->Buf_IO_struct->sector_times;
  int32_t *sector_flags = bs->Buf_IO_struct->sector_flags;

  j = idx - 1;
  k = 0;
  while((k < time_val) && (j >= first_cell_idx))
    k += sector_times[j--];

  if(k >= time_val)
  {
    j++;
    i = 0;
    if(sector_flags[j] & SECTOR_FLAG_HAS_VIDEO)
      i = 0x80000000;

    for(k = j + 1; k < idx; k++)
    {
      if(sector_flags[k] & SECTOR_FLAG_HAS_VIDEO)
      {
        i |= 0x40000000;
        break;
      }
    }

    i |= ((sector_nums[idx] - sector_nums[j]) & 0x3FFFFFFF);
    pred_exists = j;
  }
  else
  {
    i = 0x3FFFFFFF;
    if(pexists)
    {
      for(k = first_cell_idx; k < pexists; k++)
      {
        if(sector_flags[k] & SECTOR_FLAG_HAS_VIDEO)
        {
          i |= 0x40000000;
          break;
        }
      }
    }
  }

  buffer[SRI_OFFSET + sri_offset]     = (uint8_t) ((i & 0xff000000) >> 24);
  buffer[SRI_OFFSET + sri_offset + 1] = (uint8_t) ((i & 0x00ff0000) >> 16);
  buffer[SRI_OFFSET + sri_offset + 2] = (uint8_t) ((i & 0x0000ff00) >>  8);
  buffer[SRI_OFFSET + sri_offset + 3] = (uint8_t) ( i & 0x000000ff);

  return pred_exists;
}


static void doVOBNavInfo(bufstream_tt *bs, struct vob_nav_info *vob_info)
{
  uint8_t buffer[DVD_SECTOR_SIZE];
  int32_t i, j, k, l, current_idx, first_idx, last_idx, pred_exists;
  int32_t first_cell_idx, last_cell_idx, cell_idx;
#ifdef UNDER_CE
  LARGE_INTEGER position;
  HANDLE hFile = NULL;
#else // UNDER_CE
  int64_t position;
  int32_t fp;
#endif // UNDER_CE
  int32_t *sector_nums = bs->Buf_IO_struct->nav_sectors;
  //int32_t *sector_times = bs->Buf_IO_struct->sector_times;
  int32_t *sector_flags = bs->Buf_IO_struct->sector_flags;

#ifdef UNDER_CE
  if((hFile = CreateFile(vob_info->filename, FILE_ALL_ACCESS, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
#else // UNDER_CE
 #if !defined(__APPLE__) && !defined(__linux__) && !defined(__native_client__) && !defined(__QNX__)
  #if defined(_BS_UNICODE)
   if((fp = _wopen(vob_info->filename, _O_RDWR | _O_BINARY)) == -1)
  #else
   if((fp = _open(vob_info->filename, _O_RDWR | _O_BINARY)) == -1)
  #endif
 #else
   if((fp= _wopen(vob_info->filename,O_RDWR,0777 )) == -1)
 #endif
#endif // UNDER_CE

    return;

  first_idx = vob_info->base_idx;
  current_idx = vob_info->base_idx;
  last_idx = vob_info->total_nv_sectors + vob_info->base_idx - 1;
  cell_idx = 0;
  if(bs->Buf_IO_struct->num_cells > 1)
  {
    first_cell_idx = bs->Buf_IO_struct->cell_sectors[0];
    last_cell_idx = bs->Buf_IO_struct->cell_sectors[1] - 1;
    cell_idx = 1;
  }
  else
  {
    first_cell_idx = first_idx;
    last_cell_idx = last_idx;
  }

  while(current_idx <= last_idx)
  {
    if(bs->Buf_IO_struct->num_cells > 1)
    {
      if((cell_idx < bs->Buf_IO_struct->num_cells) && 
         (current_idx >= bs->Buf_IO_struct->cell_sectors[cell_idx]))
      {
        first_cell_idx = bs->Buf_IO_struct->cell_sectors[cell_idx];
        if(cell_idx < bs->Buf_IO_struct->num_cells - 1)
          last_cell_idx = bs->Buf_IO_struct->cell_sectors[cell_idx + 1] - 1;
        else
          last_cell_idx = last_idx;
        cell_idx++;
      }
    }

  // seek to the sector we need to modify
#ifdef UNDER_CE
	position.QuadPart = (int64_t)sector_nums[current_idx] * DVD_SECTOR_SIZE;
	if(FALSE == SetFilePointer(hFile, position.LowPart, &position.HighPart, FILE_BEGIN)) 
#else // UNDER_CE
	position = (int64_t)sector_nums[current_idx] * DVD_SECTOR_SIZE;
        #if !defined(__APPLE__) && !defined(__linux__) && !defined(__native_client__) && !defined(__QNX__)
		if(_lseeki64(fp, position, SEEK_SET) == -1L)
	#else
		#if defined(__QNX__)
			if(lseek64(fp,position,SEEK_SET)==-1L)
		#else
			if(lseek(fp,position,SEEK_SET)==-1L)
		#endif
	#endif
#endif //UNDER_CE
	{
#ifdef UNDER_CE
		CloseHandle(hFile);
#else // UNDER_CE
        #if !defined(__APPLE__) && !defined(__linux__) && !defined(__native_client__) && !defined(__QNX__)
		  _close(fp);
	#else
		  close(fp);
	#endif
#endif // UNDER_CE      
	  return;
    }

  // read in the sector we need to modify
#ifdef UNDER_CE
	if((FALSE == ReadFile(hFile, (void*)&buffer[0], DVD_SECTOR_SIZE, (LPDWORD)&i, NULL)) || (i != DVD_SECTOR_SIZE)){
		CloseHandle(hFile);
		return;
	}
#else // UNDER_CE
        #if !defined(__APPLE__) && !defined(__linux__) && !defined(__native_client__) && !defined(__QNX__)
		i = _read(fp, (void*)&buffer[0], DVD_SECTOR_SIZE);
	#else
		i = read(fp,(void*)&buffer[0],DVD_SECTOR_SIZE);
	#endif
#endif //UNDER_CE

#ifndef UNDER_CE
    if(i != DVD_SECTOR_SIZE)
    {
#if !defined(__APPLE__) && !defined(__linux__) && !defined(__native_client__) && !defined(__QNX__)
	  _close(fp);
#else
	  close(fp);
#endif
      return;
    }
#endif // UNDER_CE

  // go back so we can write it back out below
#ifdef UNDER_CE
	if(FALSE == SetFilePointer(hFile, position.LowPart, &position.HighPart, FILE_BEGIN)) 
#else // UNDER_CE
 	#if !defined(__APPLE__) && !defined(__linux__) && !defined(__native_client__) && !defined(__QNX__)
		if(_lseeki64(fp, position, SEEK_SET) == -1L)
	#else
		#ifdef __QNX__
			if(lseek64(fp,position,SEEK_SET)==-1L)
		#else
			if(lseek(fp,position,SEEK_SET)==-1L)
		#endif
	#endif
#endif // UNDER_CE
    {
#ifdef UNDER_CE
	CloseHandle(hFile);
#else // UNDER_CE
 	#if !defined(__APPLE__) && !defined(__linux__) && !defined(__native_client__) && !defined(__QNX__)
		  _close(fp);
	#else
		  close(fp);
	#endif
#endif // UNDER_CE
      return;
    }

    if(bs->Buf_IO_struct->do_hli_ptm_time)
    {
    // update the HLI_E_PTM time
      buffer[HLI_E_PTM_OFFSET + 0] = (uint8_t) ((vob_info->end_PTM & 0xff000000) >> 24);
      buffer[HLI_E_PTM_OFFSET + 1] = (uint8_t) ((vob_info->end_PTM & 0x00ff0000) >> 16);
      buffer[HLI_E_PTM_OFFSET + 2] = (uint8_t) ((vob_info->end_PTM & 0x0000ff00) >>  8);
      buffer[HLI_E_PTM_OFFSET + 3] = (uint8_t) ( vob_info->end_PTM & 0x000000ff);

    // update the BTN_SL_E_PTM time
      buffer[HLI_E_PTM_OFFSET + 4] = (uint8_t) ((vob_info->end_PTM & 0xff000000) >> 24);
      buffer[HLI_E_PTM_OFFSET + 5] = (uint8_t) ((vob_info->end_PTM & 0x00ff0000) >> 16);
      buffer[HLI_E_PTM_OFFSET + 6] = (uint8_t) ((vob_info->end_PTM & 0x0000ff00) >>  8);
      buffer[HLI_E_PTM_OFFSET + 7] = (uint8_t) ( vob_info->end_PTM & 0x000000ff);
    }

    // update the SML_PBI VOB_V_E_PTM value
    buffer[VOB_V_E_PTM_OFFSET + 0] = (uint8_t) ((vob_info->end_PTM & 0xff000000) >> 24);
    buffer[VOB_V_E_PTM_OFFSET + 1] = (uint8_t) ((vob_info->end_PTM & 0x00ff0000) >> 16);
    buffer[VOB_V_E_PTM_OFFSET + 2] = (uint8_t) ((vob_info->end_PTM & 0x0000ff00) >>  8);
    buffer[VOB_V_E_PTM_OFFSET + 3] = (uint8_t) ( vob_info->end_PTM & 0x000000ff);


  /* VOBU_SRI FWDI Video */
    if((current_idx + 1 <= last_cell_idx) &&
       (sector_flags[current_idx + 1] & SECTOR_FLAG_HAS_VIDEO))
      i = 0x80000000 | ((sector_nums[current_idx + 1] - sector_nums[current_idx]) & 0x3FFFFFFF);
    else
      i = 0xBFFFFFFF;
    buffer[SRI_OFFSET + 0] = (uint8_t) ((i & 0xff000000) >> 24);
    buffer[SRI_OFFSET + 1] = (uint8_t) ((i & 0x00ff0000) >> 16);
    buffer[SRI_OFFSET + 2] = (uint8_t) ((i & 0x0000ff00) >>  8);
    buffer[SRI_OFFSET + 3] = (uint8_t) ( i & 0x000000ff);


  /* VOBU_SRI FWDI Next */
    if(current_idx + 1 <= last_cell_idx)
    {
      if(sector_flags[current_idx + 1] & SECTOR_FLAG_HAS_VIDEO)
        i = 0x80000000;
      else
        i = 0;
      i |= ((sector_nums[current_idx + 1] - sector_nums[current_idx]) & 0x3FFFFFFF);
    }
    else
      i = 0x3FFFFFFF;
    buffer[SRI_OFFSET + 80] = (uint8_t) ((i & 0xff000000) >> 24);
    buffer[SRI_OFFSET + 81] = (uint8_t) ((i & 0x00ff0000) >> 16);
    buffer[SRI_OFFSET + 82] = (uint8_t) ((i & 0x0000ff00) >>  8);
    buffer[SRI_OFFSET + 83] = (uint8_t) ( i & 0x000000ff);


  /* VOBU_SRI FWDI 1 */
    doFWDI1_15(bs, current_idx, TIME1, last_cell_idx, buffer, 76);

  /* VOBU_SRI FWDI 2 */
    doFWDI1_15(bs, current_idx, TIME2, last_cell_idx, buffer, 72);

  /* VOBU_SRI FWDI 3 */
    doFWDI1_15(bs, current_idx, TIME3, last_cell_idx, buffer, 68);

  /* VOBU_SRI FWDI 4 */
    doFWDI1_15(bs, current_idx, TIME4, last_cell_idx, buffer, 64);

  /* VOBU_SRI FWDI 5 */
    doFWDI1_15(bs, current_idx, TIME5, last_cell_idx, buffer, 60);

  /* VOBU_SRI FWDI 6 */
    doFWDI1_15(bs, current_idx, TIME6, last_cell_idx, buffer, 56);

  /* VOBU_SRI FWDI 7 */
    doFWDI1_15(bs, current_idx, TIME7, last_cell_idx, buffer, 52);

  /* VOBU_SRI FWDI 8 */
    doFWDI1_15(bs, current_idx, TIME8, last_cell_idx, buffer, 48);

  /* VOBU_SRI FWDI 9 */
    doFWDI1_15(bs, current_idx, TIME9, last_cell_idx, buffer, 44);

  /* VOBU_SRI FWDI 10 */
    doFWDI1_15(bs, current_idx, TIME10, last_cell_idx, buffer, 40);

  /* VOBU_SRI FWDI 11 */
    doFWDI1_15(bs, current_idx, TIME11, last_cell_idx, buffer, 36);

  /* VOBU_SRI FWDI 12 */
    doFWDI1_15(bs, current_idx, TIME12, last_cell_idx, buffer, 32);

  /* VOBU_SRI FWDI 13 */
    doFWDI1_15(bs, current_idx, TIME13, last_cell_idx, buffer, 28);

  /* VOBU_SRI FWDI 14 */
    doFWDI1_15(bs, current_idx, TIME14, last_cell_idx, buffer, 24);

  /* VOBU_SRI FWDI 15 */
    pred_exists = doFWDI1_15(bs, current_idx, TIME15, last_cell_idx, buffer, 20);

  /* VOBU_SRI FWDI 20 */
    pred_exists = doFWDI20_240(bs, current_idx, TIME20, last_cell_idx, buffer, 16, pred_exists);

  /* VOBU_SRI FWDI 60 */
    pred_exists = doFWDI20_240(bs, current_idx, TIME60, last_cell_idx, buffer, 12, pred_exists);

  /* VOBU_SRI FWDI 120 */
    pred_exists = doFWDI20_240(bs, current_idx, TIME120, last_cell_idx, buffer, 8, pred_exists);

  /* VOBU_SRI FWDI 240 */
    doFWDI20_240(bs, current_idx, TIME240, last_cell_idx, buffer, 4, pred_exists);


  /* VOBU_SRI BWDI Video */
    j = current_idx - 1;
    while((j >= first_cell_idx) &&
          (!(sector_flags[j] & SECTOR_FLAG_HAS_VIDEO)))
      j--;

    if(j >= first_cell_idx)
      i = 0x80000000 | ((sector_nums[current_idx] - sector_nums[j]) & 0x3FFFFFFF);
    else
      i = 0xBFFFFFFF;
    buffer[SRI_OFFSET + 164] = (uint8_t) ((i & 0xff000000) >> 24);
    buffer[SRI_OFFSET + 165] = (uint8_t) ((i & 0x00ff0000) >> 16);
    buffer[SRI_OFFSET + 166] = (uint8_t) ((i & 0x0000ff00) >>  8);
    buffer[SRI_OFFSET + 167] = (uint8_t) ( i & 0x000000ff);


  /* VOBU_SRI BWDI Previous */
    if(current_idx - 1 >= first_cell_idx)
    {
      if(sector_flags[current_idx - 1] & SECTOR_FLAG_HAS_VIDEO)
        i = 0x80000000;
      else
        i = 0;
      i |= ((sector_nums[current_idx] - sector_nums[current_idx - 1]) & 0x3FFFFFFF);
    }
    else
      i = 0x3FFFFFFF;
    buffer[SRI_OFFSET + 84] = (uint8_t) ((i & 0xff000000) >> 24);
    buffer[SRI_OFFSET + 85] = (uint8_t) ((i & 0x00ff0000) >> 16);
    buffer[SRI_OFFSET + 86] = (uint8_t) ((i & 0x0000ff00) >>  8);
    buffer[SRI_OFFSET + 87] = (uint8_t) ( i & 0x000000ff);


  /* VOBU_SRI BWDI 1 */
    doBWDI1_15(bs, current_idx, TIME1, first_cell_idx, buffer, 88);

  /* VOBU_SRI BWDI 2 */
    doBWDI1_15(bs, current_idx, TIME2, first_cell_idx, buffer, 92);

  /* VOBU_SRI BWDI 3 */
    doBWDI1_15(bs, current_idx, TIME3, first_cell_idx, buffer, 96);

  /* VOBU_SRI BWDI 4 */
    doBWDI1_15(bs, current_idx, TIME4, first_cell_idx, buffer, 100);

  /* VOBU_SRI BWDI 5 */
    doBWDI1_15(bs, current_idx, TIME5, first_cell_idx, buffer, 104);

  /* VOBU_SRI BWDI 6 */
    doBWDI1_15(bs, current_idx, TIME6, first_cell_idx, buffer, 108);

  /* VOBU_SRI BWDI 7 */
    doBWDI1_15(bs, current_idx, TIME7, first_cell_idx, buffer, 112);

  /* VOBU_SRI BWDI 8 */
    doBWDI1_15(bs, current_idx, TIME8, first_cell_idx, buffer, 116);

  /* VOBU_SRI BWDI 9 */
    doBWDI1_15(bs, current_idx, TIME9, first_cell_idx, buffer, 120);

  /* VOBU_SRI BWDI 10 */
    doBWDI1_15(bs, current_idx, TIME10, first_cell_idx, buffer, 124);

  /* VOBU_SRI BWDI 11 */
    doBWDI1_15(bs, current_idx, TIME11, first_cell_idx, buffer, 128);

  /* VOBU_SRI BWDI 12 */
    doBWDI1_15(bs, current_idx, TIME12, first_cell_idx, buffer, 132);

  /* VOBU_SRI BWDI 13 */
    doBWDI1_15(bs, current_idx, TIME13, first_cell_idx, buffer, 136);

  /* VOBU_SRI BWDI 14 */
    doBWDI1_15(bs, current_idx, TIME14, first_cell_idx, buffer, 140);

  /* VOBU_SRI BWDI 15 */
    pred_exists = doBWDI1_15(bs, current_idx, TIME15, first_cell_idx, buffer, 144);

  /* VOBU_SRI BWDI 20 */
    pred_exists = doBWDI20_240(bs, current_idx, TIME20, first_cell_idx, buffer, 148, pred_exists);

  /* VOBU_SRI BWDI 60 */
    pred_exists = doBWDI20_240(bs, current_idx, TIME60, first_cell_idx, buffer, 152, pred_exists);

  /* VOBU_SRI BWDI 120 */
    pred_exists = doBWDI20_240(bs, current_idx, TIME120, first_cell_idx, buffer, 156, pred_exists);

  /* VOBU_SRI BWDI 240 */
    doBWDI20_240(bs, current_idx, TIME240, first_cell_idx, buffer, 160, pred_exists);


    l = 0;
    for(k = 0; k < bs->Buf_IO_struct->num_audio_streams; k++)
    {
      struct synci_info *synci = &bs->Buf_IO_struct->asynci[k];

      i = synci->synci_sectors[current_idx];
      if(i < 0)
      {
        j = 0x80;
        i = -i;
      }
      else
        j = 0;

      if(bs->Buf_IO_struct->fixup_synci_sector)
      {
        if(!j && sector_nums[current_idx] + i > bs->Buf_IO_struct->fixup_synci_sector)
          i--;
      }

      if((i > 0x7FFF) || (i <= 0))
        i = 0x7FFF;

      buffer[SYNCI_OFFSET + l++] = (uint8_t) (((i & 0x00007f00) >> 8) | j);
      buffer[SYNCI_OFFSET + l++] = (uint8_t) (  i & 0x000000ff);
    }

    l = 16;
    for(k = 0; k < bs->Buf_IO_struct->num_subpic_streams; k++)
    {
      struct synci_info *synci = &bs->Buf_IO_struct->spsynci[k];

      if(current_idx < synci->synci_idx)
        i = synci->synci_sectors[current_idx];
      else
        i = sector_nums[current_idx];

      if(i < sector_nums[current_idx])
      {
        j = current_idx;
        while((i < sector_nums[j]) && (j > first_idx))
          j--;
        j++;

        i = (sector_nums[current_idx] - sector_nums[j]) | 0x80000000;
      }
      else
        i = 0x7FFFFFFF;

      buffer[SYNCI_OFFSET + l++] = (uint8_t) ((i & 0xff000000) >> 24);
      buffer[SYNCI_OFFSET + l++] = (uint8_t) ((i & 0x00ff0000) >> 16);
      buffer[SYNCI_OFFSET + l++] = (uint8_t) ((i & 0x0000ff00) >>  8);
      buffer[SYNCI_OFFSET + l++] = (uint8_t) ( i & 0x000000ff);
    }

  // write out the modified sector
#ifdef UNDER_CE
	WriteFile(hFile, (void*)&buffer[0], DVD_SECTOR_SIZE, (LPDWORD)&i, NULL);
#else // UNDER_CE
 	#if !defined(__APPLE__) && !defined(__linux__) && !defined(__native_client__) && !defined(__QNX__)
		i = _write(fp, (void*)&buffer[0], DVD_SECTOR_SIZE);
	#else
		i = write(fp,(void*)&buffer[0],DVD_SECTOR_SIZE);
	#endif
#endif // UNDER_CE
    if(i != DVD_SECTOR_SIZE)
    {

#ifdef UNDER_CE
	CloseHandle(hFile);
#else // UNDER_CE
 	#if !defined(__APPLE__) && !defined(__linux__) && !defined(__native_client__) && !defined(__QNX__)
		  _close(fp);
	#else
		  close(fp);
	#endif
#endif // UNDER_CE
      return;
    }

    current_idx++;
  }

#ifdef UNDER_CE
	CloseHandle(hFile);
#else // UNDER_CE
 	#if !defined(__APPLE__) && !defined(__linux__) && !defined(__native_client__) && !defined(__QNX__)
	  _close(fp);
	#else
	  close(fp);
	#endif
#endif // UNDER_CE
}
