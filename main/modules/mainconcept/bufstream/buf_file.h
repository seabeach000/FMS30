/* ----------------------------------------------------------------------------
 * File: buf_file.h
 *
 * Desc: Buffered stream file IO
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

// Configuration Option
// sometime can improve performance on Win32-platform
//#define WIN32IO

#ifdef WIN32IO
 #ifdef __GNUC__
   #warning WIN32IO activated, -fomit-frame-pointer must be disabled
 #else
   #pragma message("WIN32IO activated")
 #endif
 #include <windows.h>
#endif

// used init_file_buf_xxx only if you know what you doing!
// it is usable to construct different filters, pipes, etc
// but can be dangerous if used by application
//

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _BS_UNICODE

int32_t init_file_buf_write(bufstream_tt *bs,
                            const wchar_t *bs_filename,
                            uint32_t bufsize,
                            void (*DisplayError)(char *txt));

int32_t init_file_buf_write_flushable(bufstream_tt *bs,
                                      const wchar_t *bs_filename,
                                      uint32_t bufsize,
                                      void (*DisplayError)(char *txt));

int32_t init_file_buf_write_existing(bufstream_tt *bs,
                                     const wchar_t *bs_filename,
                                     uint32_t bufsize,
                                     void (*DisplayError)(char *txt));

int32_t init_file_buf_read(bufstream_tt *bs,
                           const wchar_t *bs_filename,
                           uint32_t bufsize,
                           void (*DisplayError)(char *txt));
#else

int32_t init_file_buf_write(bufstream_tt *bs,
                            const char *bs_filename,
                            uint32_t bufsize,
                            void (*DisplayError)(char *txt));

int32_t init_file_buf_write_flushable(bufstream_tt *bs,
                                      const char *bs_filename,
                                      uint32_t bufsize,
                                      void (*DisplayError)(char *txt));

int32_t init_file_buf_write_existing(bufstream_tt *bs,
                                     const char *bs_filename,
                                     uint32_t bufsize,
                                     void (*DisplayError)(char *txt));

int32_t init_file_buf_read( bufstream_tt *bs,
                            const char *bs_filename,
                            uint32_t bufsize,
                            void (*DisplayError)(char *txt));
#endif





// open_file_buf_XXXX() - close_file_buf() are designed to be used
// by "normal" application to replace fopen-fclose pair
//

#ifdef _BS_UNICODE

bufstream_tt *open_file_buf_write(const wchar_t *bs_filename,
                                  uint32_t bufsize,
                                  void (*DisplayError)(char *txt));

// opens a file so it can be flushed
bufstream_tt *open_file_buf_write_flushable(const wchar_t *bs_filename,
                                            uint32_t bufsize,
                                            void (*DisplayError)(char *txt));

bufstream_tt *open_file_buf_write_existing(const wchar_t *bs_filename,
                                           uint32_t bufsize,
                                           void (*DisplayError)(char *txt));

bufstream_tt *open_file_buf_read(const wchar_t *bs_filename,
                                 uint32_t bufsize,
                                 void (*DisplayError)(char *txt));
#else

bufstream_tt *open_file_buf_write(const char *bs_filename,
                                  uint32_t bufsize,
                                  void (*DisplayError)(char *txt));

// opens a file so it can be flushed
bufstream_tt *open_file_buf_write_flushable(const char *bs_filename,
                                            uint32_t bufsize,
                                            void (*DisplayError)(char *txt));

bufstream_tt *open_file_buf_write_existing(const char *bs_filename,
                                           uint32_t bufsize,
                                           void (*DisplayError)(char *txt));

bufstream_tt *open_file_buf_read(const char *bs_filename,
                                 uint32_t bufsize,
                                 void (*DisplayError)(char *txt));
#endif


void close_file_buf(bufstream_tt* bs, int32_t Abort);

#ifdef __cplusplus
}
#endif
