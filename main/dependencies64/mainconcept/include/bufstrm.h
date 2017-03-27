/**
@file: bufstrm.h
@brief Stream base class (used by encoders, decoders and muxers)

@verbatim
File: bufstrm.h
Desc: Stream base class (used by encoders, decoders and muxers)
 
 Copyright (c) 2015 MainConcept GmbH or its affiliates.  All rights reserved.

 MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.  
 This software is protected by copyright law and international treaties.  Unauthorized 
 reproduction or distribution of any portion is prohibited by law.
@endverbatim
 **/

#if !defined (__BUFSTREAM_API_INCLUDED__)
#define __BUFSTREAM_API_INCLUDED__

#include "mctypes.h"

// comment this out to use non-UNICODE functions
// in a UNICODE project. Meant for Windows platforms
// if commented out, leave _BS_MAX_PATH defined as 2048
#ifdef _UNICODE
#define _BS_UNICODE
#define _BS_MAX_PATH  32768
#else
#define _BS_MAX_PATH  2048
#endif


#define BS_OK       (0)                 /**< Success return code @hideinitializer*/
#define BS_IO_ERROR (1)                 /**< I/O error return code @hideinitializer*/
#define BS_ERROR    (-1)                /**< General error return code @hideinitializer*/


#define BS_FLAGS_DST 0x00000001         /**< Owns AuxInfo channel, currently unused @hideinitializer*/
#define BS_FLAGS_ACT 0x00000002         /**< Currently unused @hideinitializer*/


typedef struct bufstream bufstream_tt;  /**< The bufstream object */

typedef uint32_t(MC_EXPORT_API * auxinfo_t) (bufstream_tt *bs, uint32_t offs, uint32_t info_ID, void *info_ptr, uint32_t info_size);
typedef uint32_t(MC_EXPORT_API * copybytes_t) (bufstream_tt *bs, uint8_t *ptr, uint32_t numSamples);
typedef void (MC_EXPORT_API * done_t) (bufstream_tt *bs, int32_t Abort);
typedef uint32_t(MC_EXPORT_API * usable_bytes_t) (bufstream_tt *bs);
typedef uint8_t* (MC_EXPORT_API * request_t) (bufstream_tt *bs, uint32_t numbytes);
typedef uint32_t(MC_EXPORT_API * confirm_t) (bufstream_tt *bs, uint32_t numbytes);
typedef uint32_t(MC_EXPORT_API * chunksize_t) (bufstream_tt *bs);
typedef uint32_t(MC_EXPORT_API * split_t) (bufstream_tt *bs);
typedef void (MC_EXPORT_API * free_t) (bufstream_tt *bs);

struct bufstream
{
/**
 @brief Reports how many bytes can be put into or read from buffer.

 Mainly used if a call to request(chunk size or less) fails to see how many bytes remain in the bufstream object.

 @param[in] bs             - Pointer to bufstream object
 @return Number of usable bytes
*/
  usable_bytes_t usable_bytes;

/**
 @brief Requests a buffer with at least numbytes available bytes.

 The number of bytes requested should be <= the bufstream object chunk size. This call may fail if the number of
 bytes requested is larger than the chunk size. If the number of bytes requested is <= the chunk size the call
 is guaranteed to succeed unless the buffer does not have chunk size space or bytes available.
 Once a number of bytes (can be less than requested) are put into or read from the requested buffer, they can be
 finalized using the confirm() call.

 @param[in] bs                   - Pointer to bufstream object
 @param[in] numbytes             - The number of bytes requested
 @return Pointer to the buffer or NULL if request fails.
*/
  request_t request;

/**
 @brief Informs the bufstream object of bytes put into (or read from) the requested buffer.
 
 Confirms that numbytes bytes were put into (or read from) the buffer returned by the last request() call.

 @param[in] bs                   - Pointer to bufstream object
 @param[in] numbytes             - The number of bytes put into (or read from) the buffer
 @return Number of bytes confirmed
*/
  confirm_t confirm;

/**
 @brief Put (or get) numbytes bytes into (or from) from bufsteam object.
 @param[in] bs                   - Pointer to bufstream object
 @param[in] ptr                  - Pointer to source buffer
 @param[in] numSamples           - Number of samples
 @return Number of bytes copied
*/
  copybytes_t copybytes;

/**
 @brief Gets the chunk-size of the bufstream object in buffer mode.
 
 Returns the chunk size used when the buffered bufstream object was created.

 @param[in] bs                   - Pointer to bufstream object
 @return Chunk size used to setup the bufstream object
*/
  chunksize_t chunksize;

/**
@brief Used to send data structures and information to a component or bufstream object

For example a video encoder could send video access unit information to an attached muxer. Some messages are
used in bufstream objects as well.

@param[in] bs             - Pointer to bufstream object
@param[in] offs           - Values depends on info_ID message
@param[in] info_ID        - Auxinfo message ID, some ID's are defined in auxinfo.h (aux_ID enum), some are defined in component headers
@param[in] info_ptr       - Pointer to passed data, data depends on info_ID message
@param[in] info_size      - Size of passed data, data size depends on info_ID message
@return BS_OK if successful else an error code
*/
  auxinfo_t auxinfo;

/**
 @brief Call to switch output to a new file.

 If available, currently only implemented in buf_file.c in output mode, else this field is NULL

 @param[in] bs             - Pointer to bufstream object
 @return BS_OK if successful else an error code
*/
  split_t split;

/**
 @brief Call to close a bufstream object.
 
 Recommended way to close a bufstream object is to use the close_bufstream() macro below.

 @param[in] bs             - Pointer to bufstream object
 @param[in] Abort          - Set to 1 to just close bufstream without any pending processing
*/
  done_t done;

/**
 @brief Call to free a bufstream object.
 
 Recommended way to free a bufstream object is to use the close_bufstream() macro below.

 @param[in] bs             - Pointer to bufstream object
*/
  free_t free;

  struct drive_struct *drive_ptr;                       /**< Used by the auxinfo receiver to store information, a muxer might store a stream object pointer in this field */

  uint32_t  (MC_EXPORT_API * drive) (bufstream_tt *bs, uint32_t info_ID, void *info_ptr, uint32_t info_size);  /**< Currently unused */

  uint32_t flags;                                       /**< Currently unused, set once during creation/initialization, but unused after */
  uint32_t (MC_EXPORT_API * state) (bufstream_tt *bs);  /**< Currently unused */

  struct impl_stream* Buf_IO_struct;                    /**< Information storage pointer defined by each bufstream implementation */
};


/**
 @brief Recommended way to close and free a bufstream object

 bs = NULL; is very important!
 It forces usage of close_bufstream()-macro on pointer-variables and produce Compiler-error
 on static/stack/part_of_struct allocated objects

 @param[in] bs             - Pointer to bufstream object
 @param[in] abort          - Set to 1 to just close bufstream without any pending processing
*/
#define close_bufstream(bs, abort) \
do { bs->done(bs, abort); bs->free(bs); bs = NULL; } while(0)


#endif // #if !defined (__BUFSTREAM_API_INCLUDED__)

