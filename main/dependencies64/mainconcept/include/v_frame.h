/**
@file: v_frame.h
@brief Frame structures used for example by MC H.264 or HEVC encoders

@verbatim
File: v_frame.h
Desc: Frame structures used for example by MC H.264 or HEVC encoders

 Copyright (c) 2015 MainConcept GmbH or its affiliates.  All rights reserved.
 
 MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.  
 This software is protected by copyright law and international treaties.  Unauthorized 
 reproduction or distribution of any portion is prohibited by law.
@endverbatim
 **/

#ifndef __V_FRAME_H__
#define __V_FRAME_H__

/**
 * @name Frame Structure
 * @{
 **/
 
/**
 *@brief Frame structure used for example by MC H.264 encoder
 */
typedef struct video_frame_tag
{
    struct 
    {
        uint8_t        *plane;    /**< Pointer to the data plane */
        int32_t        stride;    /**< Line size of frame        */
        int32_t        width;     /**< Width of frame            */
        int32_t        height;    /**< Height of frame           */
    } src[4];

    uint32_t           four_cc;   /**< Colorspace                */
    uint32_t           options;   /**< Options                   */

    void            *application_instance_data;
    void           (*unlock)(struct video_frame_tag *p_data);
} video_frame_tt, *p_video_frame_tt;
/** @} */


/**
 *@brief Frame structure used for source and preview, for example used by MC HEVC encoder
 */
typedef struct video_out_frame_tag
{
    uint8_t*                plane[4];       /**< Pointer to the data planes     */

    int32_t                 width;          /**< Width of frame                 */
    int32_t                 height;         /**< Height of frame                */
    int32_t                 stride[4];      /**< Line size of frame             */

    uint32_t                four_cc;        /**< Colorspace                     */
    int32_t                 layer;          /**< Layer number id        */

    uint32_t  state;                        /**< Frame state                    */

    void (*done)(void * this_object);       /**< Pointer to callback function   */

    void *    reserved1;                    /**< Reserved                       */
    int32_t   temp_id;                      /**< Temporal sub-layer id          */
    uint32_t  reserved3;                    /**< Reserved                       */

} video_out_frame_tt, *p_video_out_frame_tt;
/** @} */


////////// different frame states
#define FRM_STATE_FILLED     (0x0020)               /**< (0x0020) */
#define FRM_STATE_DONE       (0x0100)               /**< (0x0100) */
#define FRM_STATE_LOCKED     (0x1000)               /**< (0x1000) */

#define FRM_BUF_SUBSTITUTE   (0x0004)               /**< Use framebuffer as encoded frame, use to syncronize with previous MPEG-segment */
#define FRM_BUF_DEINTERLACED (0x0008)               /**< (0x0008) */
#define FRM_BUF_INSERT       (0x0010)               /**< (0x0010) */
#define FRM_BUF_FILLED      FRM_STATE_FILLED        /**< (0x0020) */
#define FRM_BUF_DELAY_ERASE  (0x0040)               /**< (0x0040) */
#define FRM_BUF_ENCODED      (0x0080)               /**< (0x0080) */
#define FRM_BUF_DONE        FRM_STATE_DONE          /**< (0x0100) */
#define FRM_BUF_RAW_COPIED   (0x0100)               /**< Encoded raw-framebuffer was copied (i.e. not recoded) */
#define FRM_BUF_LOCKED      FRM_STATE_LOCKED        /**< (0x1000) */


#endif // __V_FRAME_H__
