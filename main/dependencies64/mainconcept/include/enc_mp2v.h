/**
@file enc_mp2v.h
@brief MPEG-1/2 Video Encoder API

@verbatim
File: enc_mp2v.h
Desc: MPEG-1/2 Video Encoder API

 Copyright (c) 2015 MainConcept GmbH or its affiliates.  All rights reserved.

 MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.  
 This software is protected by copyright law and international treaties.  Unauthorized 
 reproduction or distribution of any portion is prohibited by law.
@endverbatim
 **/


#if !defined (__ENC_MP2V_API_INCLUDED__)
#define __ENC_MP2V_API_INCLUDED__

#include "mcapiext.h"
#include "mcprofile.h"

#include "bufstrm.h"
#include "mcdefs.h"

typedef struct mpeg_v_encoder mpegvenc_tt;

#if defined (__GNUC__)
#pragma pack(push,1)
#else
#pragma pack(push)
#pragma pack(1)
#endif

/**
 * @name Motion Data Structure
 * @{
 */

 /**
 * @brief These parameters are used to configure the motion estimation.
 */
typedef struct motion_data
{
  int32_t forw_hor_f_code;      /**<@brief Forward horizontal vector range  */
  int32_t forw_vert_f_code;     /**<@brief Forward vertical vector range    */
  int32_t sxf;                  /**<@brief Forward horizontal search range  */
  int32_t syf;                  /**<@brief Forward vertical search range    */
  int32_t back_hor_f_code;      /**<@brief Backward horizontal vector range */
  int32_t back_vert_f_code;     /**<@brief Backward vertiacal vector range  */
  int32_t sxb;                  /**<@brief Backward horizontal search range */
  int32_t syb;                  /**<@brief Backward vertical search range   */
} motion_t;
/** @} */

/**
 * @name Settings Structure
 * @{
 */
 /**
 * @brief These parameters are used to configure the encoder.
 */

struct mpeg_v_settings
{

/**
 * @name Coding model parameters
 * @{
 */
  int32_t   video_type;                           /**<@brief Type of video stream (one of @ref MPEG_MPEG1 "presets") */
  int32_t   video_pulldown_flag;                  /**<@brief Pulldown / telecine mode */
  int32_t   constrparms;                          /**<@brief Constrained parameters flag (MPEG-1 only) */
  int32_t   N;                                    /**<@brief Max. number of frames in Group of Pictures */
  int32_t   M;                                    /**<@brief Distance between reference frames */
  int32_t   drop_frame_tc;                        /**<@brief Use "Drop Frame" timecode notation in GOP */
  int32_t   tc0;                                  /**<@brief Timecode of first frame */
  int32_t   ClosedGOP_Interval;                   /**<@brief How often to generate closed GOP, 0 = disabled*/
  int32_t   deinterlacing_mode;                   /**<@brief One of the @ref DEINTERLACE_NONE "deinterlace" values */
  int32_t   ignore_frame_interval;                /**<@brief Set to 1000 to ignore each 1000-th frame */
  int32_t   features_flags;                       /**<@brief Different @ref FEATURE_AUTO_GOP_FAST "Features Flags"*/
  int32_t   fieldpic;                             /**<@brief Use field pictures, not supported */
/**@}*/
/**
 * @name Sequence specific data (sequence header)
 * @{
 */
  int32_t   aspectratio;                          /**<@brief Aspect ratio information (pel or display) */
  int32_t   frame_rate_code;                      /**<@brief This field specifies the @ref FRAMERATE0 "frame rate code" */
  double    frame_rate;                           /**<@brief This field specifies the actual frame rate */
  double    bit_rate;                             /**<@brief Bits per second */
  double    max_bit_rate;                         /**<@brief Maximum bit rate for variable bitrate mode */
  int32_t   mquant_limit;                         /**<@brief Max limitation for macroblock quantization */
  int32_t   vbv_buffer_size;                      /**<@brief Size of VBV buffer (* 16 kbit) */
  int32_t   constant_bitrate;                     /**<@brief Constant bitrate flag defines bitrate mode, should be one of (@ref VBR_CONSTANT "bitrate modes")*/
  int32_t   mquant_value;                         /**<@brief Macroblock quantization value */
  int32_t   write_sh;                             /**<@brief Write a sequence header every GOP */
  int32_t   write_sec;                            /**<@brief Write a sequence end code */
/**@}*/
/**
 * @name Sequence specific data (sequence extension)
 * @{
 */
  int32_t   profile;                              /**<@brief Syntax / parameter constraints */
  int32_t   level;                                /**<@brief Syntax / parameter constraints */
  int32_t   prog_seq;                             /**<@brief Progressive sequence */
  int32_t   chroma_format;                        /**<@brief Chroma format */
/**@}*/
/**
 * @name Advanced gop parameters
 * @{
 */
  int32_t   min_N;                                /**<@brief Minimum GOP length, used together with AUTO_GOP features to avoid consecutive I frames */
/**@}*/

/**
 * @name Motion data
 * @{
 */
  motion_t  motion_data[MAXM];                    /**<@brief Motion estimation parameters */

  uint8_t   adaptive_quant_mode;                  /**<@brief = 0 -> old school (complexity based MB quantization) else -> combinations of AQM_Brightness, AQM_Contrast and AQM_Detail */
  int8_t    adaptive_quant_strength[3];           /**<@brief -100 .. +100, intensity values for AQM_Brightness, AQM_Contrast and AQM_Detail */

  uint32_t  reserved09;                           /**<@brief */
  uint32_t  reserved10;                           /**<@brief */
/**@}*/
/**
 * @name Sequence specific data (sequence display extension)
 * @{
 */
  int32_t  video_format;                          /**<@brief Component, PAL, NTSC, SECAM or MAC */
  int32_t  color_primaries;                       /**<@brief Source primary chromaticity coordinates */
  int32_t  transfer_characteristics;              /**<@brief Opto-electronic transfer char. (gamma) */
  int32_t  matrix_coefficients;                   /**<@brief Eg,Eb,Er / Y,Cb,Cr matrix coefficients */
  int32_t  display_horizontal_size;               /**<@brief Horizontal display size */
  int32_t  display_vertical_size;                 /**<@brief Vertical display size */
  int32_t  write_sde;                             /**<@brief Write a sequence display extension every GOP, SVCD = 0! */

  int32_t  prefiltering;                          /**<@brief Blurs video out, useful for complex content with low bitrate (=0 -> disabled) suitable values 1..15 */

  int32_t  target_size_restriction;               /**<@brief Triggers frame target size planer (-50 .. +50 percent, 0 = no restriction) */

  int32_t  user_iquant;                           /**<@brief Use non-default (user-defined) quant. matrices for intra blocks*/
  int32_t  user_niquant;                          /**<@brief Use non-default (user-defined) quant. matrices for non intra blocks*/
/**@}*/
 /**
 * @name Picture specific data (picture coding extension)
 * @{
 */
  int32_t  dc_prec;                               /**<@brief DC coefficient precision for intra coded blocks */
  int32_t  topfirst;                              /**<@brief Display top field first */

  int32_t  frame_pred_dct_tab[3];                 /**<@brief Frame/field prediction/dct table (I,P,B) */
  int32_t  conceal_tab[3];                        /**<@brief Use concealment motion vectors (I,P,B) */
  int32_t  qscale_tab[3];                         /**<@brief Linear/non-linear quantizaton table */
  int32_t  intravlc_tab[3];                       /**<@brief Intra vlc format (I,P,B,current) */
  int32_t  altscan_tab[3];                        /**<@brief Alternate scan (I,P,B,current) */
  int32_t  repeatfirst;                           /**<@brief Repeat first field after second field */
  int32_t  prog_frame;                            /**<@brief Progressive frame */

  int32_t  reserved11[8];                         /**< */
/**@}*/
/**
 * @name Rate control vars
 * @{
 */
  int32_t  fixed_vbv_delay;                       /**<@brief Force a 0xffff vbv_delay */
  int32_t  min_frame_percent;                     /**<@brief Initial VBV-fullness in %, or (0x80000000 | vbv_fullness_in_bits) */
  int32_t  pad_frame_percent;                     /**<@brief Padding amount for variable bitrate mode to reach a minimum data rate */

  uint8_t  intra_q[64];                           /**<@brief User-defined quantization tab. for intra blocks */
  uint8_t  inter_q[64];                           /**<@brief User-defined quantization tab. for non-intra blocks */
  uint8_t  chroma_intra_q[64];                    /**<@brief User-defined quantization tab. for intra blocks */
  uint8_t  chroma_inter_q[64];                    /**<@brief User-defined quantization tab. for non-intra blocks */

  uint8_t  motion_search_type;                    /**<@brief Type of motion search to do, one of SEARCH_* constants */
  uint32_t frame_alignement_power_two;            /**<@brief Alignment of frame, 0..10; 0 = none, 1:2, 2:4, 3:8, 4:16, 5:32, 6:64 ... 10:1024 */

  int32_t  embed_SVCD_user_blocks;                /**<@brief Put blank SVCD scan offset blocks in the video stream */
  double   avg_bit_rate;                          /**<@brief Average bit rate for variable bitrate mode */
  double   min_bit_rate;                          /**<@brief Minmum bit rate for variable bitrate mode */
  int32_t  calc_quality;                          /**<@brief Calculate psnr */

  int32_t  write_settings_info;                   /**<@brief Put into stream config parameters*/

  int32_t  rate_control_mode;                     /**<@brief Unused */
  int32_t  qt_noise_sensitivity;                  /**<@brief Controls ratio between intra and inter blocks (the higher the more inter blocks) */
  int32_t  num_threads;                           /**<@brief Number of threads*/
/**@}*/
/**
 * @name Picture display extension
 * @{
 */
  int32_t  write_pde;                             /**<@brief Write picture display extension */
  int32_t  frame_centre_horizontal_offset;        /**<@brief */
  int32_t  frame_centre_vertical_offset;          /**<@brief */
/**@}*/
/**
 * @name Suggested frame size for specific MPEG types
 * @{
 */
  int32_t  def_horizontal_size;                   /**<@brief Horizontal resolution */
  int32_t  def_vertical_size;                     /**<@brief Vertical resolution */
  /**@}*/
};
/** @} */

/**
 * @name Feature Flags defines
 * @brief These flags can be set within the features_flags encoder parameter.
 * @{
 */
/**
 * @name GOP defines
 * @brief Automatically create new GOPs when appropriate, according to the source content and manage layout of GOP when necessary
 * @{
 */

#define FEATURE_AUTO_GOP_FAST      (0x00000010L) /**<@brief Allow P->I reassigning if appropiate (no time penality, recommended for online encoding) @hideinitializer*/
#define FEATURE_AUTO_GOP_VCSD      (0x00000020L) /**<@brief Allow GOP planning according to scene position (refined, but time consuming) @hideinitializer*/
#define FEATURE_AUTO_GOP_SCD       (0x00000800L) /**<@brief Scene change detection based on frame's histogram changing (similar to VCSD but faster) @hideinitializer*/
#define FEATURE_ALL_GOPS_SHORT     (0x00000040L) /**<@brief All GOPs will be short, i.e. starting with I(0). @hideinitializer*/
#define FEATURE_FIRST_GOP_NOSHORT  (0x00000080L) /**<@brief The first encoded GOP will be a full gop including the B Frames at startup @hideinitializer*/
/**@}*/

#define FEATURE_NR_WHOLE_STREAM    (0x00000100L) /**<@brief Use the qt_noise_sensitivity setting as a noise reduction value for the entire stream @hideinitializer*/


#define FEATURE_NON_CLAMPED_CC     (0x00000200L) /**<@brief Old define, see FEATURE_CLAMPED_DST and FEATURE_CLAMPED_SRC @hideinitializer*/
#define FEATURE_CLAMPED_DST        (0x00000200L) /**<@brief Indicates that encoded stream should have short range of pixel, use with FEATURE_CLAMPED_SRC, see table
                                                     <table>
                                                     <tr>
                                                         <th>FEATURE_CLAMPED_SRC</th>
                                                         <th>FEATURE_CLAMPED_DST</th>
                                                         <th>Encoded pixels range</th>
                                                     </tr>
                                                     <tr>
                                                         <td>0</td>
                                                         <td>0</td>
                                                         <td>No conversion. Indicates what input stream is full range [0..255] and encoded stream should be full range.</td>
                                                     </tr>
                                                     <tr>
                                                         <td>0</td>
                                                         <td>1</td>
                                                         <td>Conversion to short range [16..235]. Indicates what input stream is full range and encoded stream should be convert to short range.</td>
                                                     </tr>
                                                     <tr>
                                                         <td>1</td>
                                                         <td>1</td>
                                                         <td>Keep short range [16..235]. No conversion, but doesn't allow to go beyond short range when use color resampling (for example when convert from 4:2:0 to 4:2:2 format)</td>
                                                     </tr>
                                                     <tr>
                                                         <td>1</td>
                                                         <td>0</td>
                                                         <td>Conversion to full range [0..255]. Indicates what input stream is short range and encoded stream should be convert to full range.</td>
                                                     </tr>
                                                     </table>
                                                     @hideinitializer*/
#define FEATURE_CLAMPED_SRC        (0x00001000L) /**<@brief Indicates that encoded stream should have full range of pixel, use with FEATURE_CLAMPED_DST, see table
                                                     <table>
                                                     <tr>
                                                     <th>FEATURE_CLAMPED_SRC</th>
                                                     <th>FEATURE_CLAMPED_DST</th>
                                                     <th>Encoded pixels range</th>
                                                     </tr>
                                                     <tr>
                                                     <td>0</td>
                                                     <td>0</td>
                                                     <td>No conversion. Indicates what input stream is full range [0..255] and encoded stream should be full range.</td>
                                                     </tr>
                                                     <tr>
                                                     <td>0</td>
                                                     <td>1</td>
                                                     <td>Conversion to short range [16..235]. Indicates what input stream is full range and encoded stream should be convert to short range.</td>
                                                     </tr>
                                                     <tr>
                                                     <td>1</td>
                                                     <td>1</td>
                                                     <td>Keep short range [16..235]. No conversion, but doesn't allow to go beyond short range when use color resampling (for example when convert from 4:2:0 to 4:2:2 format)</td>
                                                     </tr>
                                                     <tr>
                                                     <td>1</td>
                                                     <td>0</td>
                                                     <td>Conversion to full range [0..255]. Indicates what input stream is short range and encoded stream should be convert to full range.</td>
                                                     </tr>
                                                     </table>
                                                     @hideinitializer*/

#define FEATURE_VIDEO_IN           (0x00000400L) /**<@brief Use video-in source if exist (some special HW accelerated builds), use new API to control the Video-Source @hideinitializer*/

// This flag is obsolete, encoder is detached from application by default. To disable this, use FEATURE_MT_OFF.
// #define FEATURE_ENCODING_THREAD    (0x00001000L) /**< run encoding separated from application (obsolete) */
#define FEATURE_FORCE_VOBUV        (0x00010000L) /**<@brief Use VOBU-verifier on non DVD profiles @hideinitializer*/
#define FEATURE_MT_OFF             (0x00020000L) /**<@brief Turn off multithreading @hideinitializer*/
#define FEATURE_PERF_ONLINE        (0x00040000L) /**<@brief Perfomance online. Set when @ref PERF_ONLINE has been called in the function @ref mpegOutVideoPerformance @hideinitializer*/

/**
 * @name Field order defines
 * @brief Default field-dominance for whole video-sequence {0,0}-undefined, {1,0} top-first, {0,1}-bottom first, {1,1}-progressive
 * @{
 */
#define FEATURE_TOP_FIELD_FIRST    (0x00100000L) /**<@brief Top field is first @hideinitializer */
#define FEATURE_BOT_FIELD_FIRST    (0x00200000L) /**<@brief Bottom field is first @hideinitializer */
/**@}*/
#define FEATURE_FIXED_FRAME_SIZE   (0x01000000L) /**<@brief Every frame is coded with constant size of bits (bps/fps) @hideinitializer*/
#define FEATURE_SMPTE_328M         (0x02000000L) /**<@brief Place SMPTE 328M data in the stream @hideinitializer*/

#define FEATURE_MIN_VBV_ACTIVITY   (0x04000000L) /**<@brief  Minimize VBV activity in CBR mode, useful for transport stream muxing with tight conditions this will limit the minimum quantization values under some conditions with the aim of never coming close to a VBV underflow @hideinitializer*/
/** @} */

/**
 * @name User Quantization Matrix Flags
 * @brief These flags can be set within the user_iquant and user_niquant encoder parameters.
 * @{
 */
#define USE_LUMA_QUANT_MATRIX      (0x00000001L) /**<@brief Use luma quantization matrix @hideinitializer */
#define USE_CHROMA_QUANT_MATRIX    (0x00000002L) /**<@brief Use chroma quantization matrix @hideinitializer */
/**@}*/

/**
 * @name Frame structure
 * @brief This structure used to configure frame settings
 * @{
 */
typedef struct tag_frame_v_tt
{
  uint8_t     *pSource;                                                        /**<@brief Pointer to buffet */
  int32_t     lSrcLineSize;                                                    /**<@brief Line size */
  uint32_t    ulSrcWidth;                                                      /**<@brief Picture width */
  uint32_t    ulSrcHeight;                                                     /**<@brief Picture height */
  uint32_t    ulColorSpaceFourcc;                                              /**<@brief Color space */
  uint32_t    ulOptFlags;
  void        *pUserData;                                                      /**<@brief User data for app, maybe used in UnlockCallback */
  void        (MC_EXPORT_API *pUnlockCallback)(struct tag_frame_v_tt *pData);  /**<@brief Callback, will be called after frame is processed */
} frame_v_tt, *pframe_v_tt;
/**@}*/

#pragma pack(pop)

/**
 * @name Motion Search Types
 * These types can be used for the motion_search_type encoder parameter.
 * @{
 */
#define SEARCH_FASTEST      0
#define SEARCH_HALF_PEL     1
#define SEARCH_MODE_A       2
#define SEARCH_MODE_B       4
#define SEARCH_MODE_C       8
#define SEARCH_RIGOROUS    16
#define SEARCH_DIAMOND     17
/** @} */

/**
 * @name Ratecontrol Modes
 * These modes can be used for the rate_control_mode encoder parameter.
 * @{
 */
#define RC_MODE_FAST        0   /**<@brief Fast ratecontrol mode. Not used anymore, will be redirected to RC_MODE_1*/
#define RC_MODE_1           1   /**<@brief General ratecontrol mode.*/
#define RC_MODE_LAST        2   /**<@brief Not used*/
#define RC_MODE_128       128   /**<@brief Not used*/
/** @} */

/**
 * @name Deinterlacing modes
 * Possible values of mpeg_v_settings::deinterlacing_mode field
 * @{
 */
#define DEINTERLACE_NONE            0 /**<@brief Disable deinterlacing @hideinitializer*/
#define DEINTERLACE_ON              1 /**<@brief Enable deinterlacing @hideinitializer*/
#define DEINTERLACE_AUTO            1 /**<@brief Enable deinterlacing use first field interpolate the other @hideinitializer*/
#define DEINTERLACE_USETOPFIELD     2 /**<@brief Enable deinterlacing use top field @hideinitializer*/
#define DEINTERLACE_USEBOTTOMFIELD  3 /**<@brief Enable deinterlacing use bottom field @hideinitializer*/
#define DEINTERLACE_USEBOTHFIELDS   4 /**<@brief Enable deinterlacing blend fields @hideinitializer*/
/**@}*/



/**
 * @name Performance Modes
 * @brief These modes are used with the @ref mpegOutVideoPerformance function.
 * @{
 */
#define PERF_OFFLINE    0   /**<@brief Offline performance mode. Maintain quality at the expense of speed. Despite its name this flag shall be used on fast PCs. In this configuration mode the number of iterations (re-encodes) per frame is not limited. This will consume computation power and time but generally results in good image quality.*/
#define PERF_ONLINE     1   /**<@brief Online performance mode. Maintain speed at the expense of quality. In this mode the encoder limits the number of iterations and re-encodes to 5. This may lead to decreased video quality but can be useful in streaming scenarios where constant data flow is required. Also it is helpful on CPUs with low computation power.*/
#define PERF_MOTIONAREA 2   /**<@brief Motionarea performance mode. Set search area only. This flag will limit the search range and search algorithm of the encoder for faster performance at reduced image quality.*/
/** @} */

#if defined (__cplusplus)
extern "C" {
#endif

/**
 * Call this function to fill an mpeg_v_settings structure with default values based on a video type and PAL flag.
 * @param[out] set        - a pointer to a mpeg_v_settings structure to be initialized
 * @param[in]  video_type - type used for loading default values (e.g. MPEG_DVD)
 * @param[in]  PAL        - video format, 1 = PAL, 0 = NTSC
 * @return                - returns type describing character string or NULL if video type is not supported.
 *
 * @code
 * struct mpeg_v_settings set = {0};
 *
 * mpegOutVideoDefaults(&set, MPEG_DVD, VM_PAL);
 * @endcode
 */
char * MC_EXPORT_API mpegOutVideoDefaults(struct mpeg_v_settings *set, int32_t video_type, int32_t PAL);

/**
 * Call this function to change the performance-related part of an mpeg_v_settings structure.
 * @param[out] set        - a pointer to a mpeg_v_settings structure to be changed
 * @param[in]  mode       - can be \ref PERF_OFFLINE, \ref PERF_ONLINE or \ref PERF_MOTIONAREA
 * @param[in]  level      - performance/quality level
 *							if offline, the desired quality 0 .. 31 (highest quality)
 *							if online, the available CPU performance (0..31)
 *							if search area the search range, calculated by the frame size (>= 0)
 * @param[in]  reserved   - reserved (set to 0)
 * @return NONE
 * @note This function should be called immediately before calling mpegOutVideoNew.
 *
 * @code
 * struct mpeg_v_settings set = {0};
 *
 * mpegOutVideoDefaults(&set, MPEG_DVD, VM_PAL);
 *
 * ... changing resolution etc. ...
 *
 * mpegOutVideoPerformance(&set, PERF_OFFLINE, 16);
 * @endcode
 */
void MC_EXPORT_API mpegOutVideoPerformance(struct mpeg_v_settings *set, int32_t mode, int32_t level, int32_t reserved);


#define INSTANCE_OPT_ACC_OFF 0x00000001

/**
 * Call this function to create an mpegvenc_tt video encoding object which is used in other video encoding calls.
 * @param[in] get_rc     - pointer to set of callbacks used for memory allocation, printing messages etc.
 * @param[in] set        - a pointer to a filled in mpeg_v_settings structure
 * @param[in] options    - option flags (INSTANCE_OPT_ACC_OFF disable search for hardware accelerated MPEG encoder)
 * @param[in] cpu        - enable/disable CPU optimization mode\n
 *                         1 - up to MMX mode           \n
 *                         2 - up to 3DNOW mode         \n
 *                         3 - up to SSE mode           \n
 *                         4 - up to AMD 3DNOWEXT mode  \n
 *                         5 - up to SSE2 mode          \n
 *                         0xFFFFFFFF - autodetect available optimization mode \n
 *                         In other cases CPU optimization will be disabled (Plain C/C++ will be used)
 *
 * @param[in] frame0     - first frame number to encode
 * @param[in] nframes    - number of frames to encode, can be 0 for streaming mode
 * @return a pointer to a mpegvenc_tt object if successful, NULL if unsuccessful
 *
 * @code
 * ...
 * mpegvenc_tt *instance = mpegOutVideoNew(get_rc, &set, 0, 0xFFFFFFFF, 0, 0);
 * @endcode
 */
mpegvenc_tt * MC_EXPORT_API mpegOutVideoNew(void                         *(MC_EXPORT_API *get_rc)(const char* name),
                                            const struct mpeg_v_settings *set,
                                            int32_t                       options,
                                            int32_t                       cpu,
                                            int32_t                       frame0,
                                            int32_t                       nframes);


/**
 * Call this function to put sequence header to the stream.
 * @param[in] instance      - a pointer to a mpegvenc_tt object created with a mpegOutVideoNew call
 * @param[in] pbuffer       - a pointer to memory where sequence header and extention will be stored
 * @param[in,out] buf_size  - [in] pbuffer's memory size, [out] sequence header length stored in pbuffer
 * @return negative value on error.
 */
int MC_EXPORT_API mpegOutVideoGetSeqHeader(mpegvenc_tt *instance, unsigned char *pbuffer, int *buf_size );

/**
 * Call this function to free an mpegvenc_tt object created with the mpegOutVideoNew function.
 * @param[in] instance  - a pointer to a mpegvenc_tt object created with a mpegOutVideoNew call
 * @return none
 */
void MC_EXPORT_API mpegOutVideoFree(mpegvenc_tt *instance);




#define INIT_OPT_EXTERN_FRM_BUF 0x00000001
#define INIT_OPT_NR_FILT        0x00000002
#define INIT_OPT_AUTHENT        0x00000010

#if defined (RC_2VBR)
 #define INIT_OPT_VBR_TWO_PASSES  0x00000800
 #define INIT_OPT_VBR_ANALYSE     0x00000900
 #define INIT_OPT_VBR_ENCODING    0x00000F00
 #define INIT_OPT_VBR_PASSES_MASK 0x00000F00
#endif

#define INIT_OPT_VBR_EXT_STORAGE 0x00000100 /**< Must be not disabled by RC_2VBR to keep binary compatibility */


#if !defined (__FRAME_TT_INCLUDED__)
#define __FRAME_TT_INCLUDED__
typedef struct
{
  uint32_t       width;
  uint32_t       height;
  uint32_t       four_cc;
  uint32_t       state;
  unsigned char *plane[4];
  int32_t        stride[4];
  void           (MC_EXPORT_API *done)(void *this_object);
  void          *reserved1;
  uint32_t       reserved2;
  uint32_t       reserved3;
} frame_tt;
#endif


/**
 * @name AU report structure
 * @{
 */
 /**
 * @brief The parameters exported about encoded frame or stream_end-state the structure is owned by encoder and valid during done() call only, application must copy the necessary data from this structure
 */
typedef struct au_report_struct
{
  uint32_t support_flags;               /**<@brief Flag to show filled fields in this structure */
  void    *application_pointer;         /**<@brief Not handled by encoder (stored only) */
  uint32_t application_parameter;       /**<@brief Not handled by encoder (stored only) */

  uint32_t vbv_state;                   /**<@brief State of vbv-buffer, bits */
  int32_t  video_in_frame;              /**<@brief Size of video-payload, bits */
  int32_t  bits_in_frame;               /**<@brief Size of frame in stream (headers + video + padding + etc.) */
  int32_t  pict_type;                   /**<@brief 1:I, 2:P, 3:B */
  int32_t  temp_ref, temp_ref_I;        /**<@brief Temporal reference and temporal reference of I-frame in this GOP */
  int32_t  c_frame_nr, c_frame_nr_I;    /**<@brief Frame number in coded video, last I-frame number in coded video */

// can be used to create quality-bar, worstness = avg_quant*enc_comp;
// suggest to use (scala 0..100) 100/(1+log(avg_quant*enc_comp))
  int32_t  avg_quant;   /**<@brief 1..62(MPEG1,MPEG2) or 112(MPEG2)  average quantization, depends on the bit rate and content of the video-stream */
  int32_t  avg_comp;    /**<@brief 1..2048 average frame-complexity (usually near 350) */
  int32_t  enc_comp;    /**<@brief 1..2048 average misprediction-complexity (usually: P:150, B:60) */
  int32_t  avg_quality; /**<@brief 0..48 average estimated quality (dB, relative to frame-complexity) */

} au_report_tt;
/**@}*/

#define INIT_OPT_START_PAR        0x00002000

/**
 * @name Start parameters
 * @{
 */
struct opt_startup_par
{
  int32_t  reserved0;
  int32_t  reserved1;
  int32_t  temp_ref_0; /**<@brief temp_ref of frame0-frame (i.e. 0-means start new GOP) */
  int32_t  temp_ref_I; /**<@brief temp_ref of I-frame in continued GOP */
  uint32_t vbv_state;
  int32_t  reserved[3];
  frame_tt reference_frame;
};
/**@}*/
#define INIT_OPT_CHAPTER_LIST    0x00001000
/**
 * @name Chapter position structure
 * @{
 */
struct chapter_position
{
  int32_t frame_nr;
  int32_t flags;
};
/**@}*/
#define CHAPTER_OPEN_GOP       (0x00000001L)
#define CHAPTER_SHORT_GOP      (0x00000002L)
#define CHAPTER_FRAME_NR       (0x00000004L) /**<@brief Change the timecode at this point of the stream to the timecode corresponding to the given frame_nr @hideinitializer*/
#define CHAPTER_FRAME_NR_MASK  (0xFFFFFF00L)
#define CHAPTER_REARRANGE_GOPS (0x00000010L) /**<@brief Rearrange preceding GOPs for getting gop length as equal as possible @hideinitializer*/
#define CHAPTER_END_OF_LIST    (~0L)



/**
 * @name User data options
 * @{
 */
#define INIT_OPT_UD_FIRST_SEQHDR       0x00010000        /**<@brief Put user data after the first sequence hdr @hideinitializer*/
#define INIT_OPT_UD_ALL_SEQHDR         0x00020000        /**<@brief Put user data after all sequence hdrs @hideinitializer*/
/**@}*/

/**
 * @name Smart renderer options
 * @{
 */
#define INIT_OPT_SR_ON                 0x40000000        /**<@brief For internal use only  @hideinitializer*/

#define INIT_OPT_FAST_SR               0x10000000        /**<@brief Do fast smartrendering (SR copy), if SR is possible @hideinitializer*/
/**@}*/
//////////////////////////////////////
//// future modes, not yet implemented
#define INIT_OPT_FAST_SR_REQUANT       0x20000000        /**<@brief NOT IMPLEMENTED YET !!! @hideinitializer*/
//////////////////////////////////////

/**
* Call this function to initialize the video encoder for an encoding session. An existing bufstream object must be passed to this function, the video encoder will output the encoded data to the bufstream object.
*
* @param[in] instance      -  a pointer to a mpegvenc_tt object created with a mpegOutVideoNew call
* @param[in] videoobs      -  a pointer to a bufstream_tt object for the compressed data output stream
* @param[in] options_flags - @li INIT_OPT_EXTERN_FRM_BUF - use external frame buffer (I420 and YV12 only)
*                            @li INIT_OPT_NR_FILT - use preprocessing filter
*                            @li INIT_OPT_VBR_TWO_PASSES - use for internal metadata 2-pass encoding
*                            @li INIT_OPT_VBR_ANALYSE - init for analyze pass (see chapter ?-pass Encoding?
*                            @li INIT_OPT_VBR_ENCODING - init for encoding pass (dito)
*                            @li INIT_OPT_CHAPTER_LIST - use to set chapter marks (starts a new GOP)
*                            @li INIT_OPT_UD_FIRST_SEQHDR - put user data after the first sequence hdr
*                            @li INIT_OPT_UD_ALL_SEQHDR - put user data after all sequence headers
* @param[in] opt_ptr       - array of pointer for options set in option_flags
*
* @return mpegOutErrNone if successful, mpegOutError if an error occurs
*/
#if defined (API_EXT_PARAM_LIST)
// API-extension to give metadata-stream-pointer to encoder
int32_t MC_EXPORT_API mpegOutVideoInit(mpegvenc_tt *instance, bufstream_tt *videobs, int32_t options_flags, void **opt_ptr = 0);
#else
int32_t MC_EXPORT_API mpegOutVideoInit(mpegvenc_tt *instance, bufstream_tt *videobs, int32_t options_flags);
#endif


/**
 * Call to finish encoding session, set abort non-zero if encoding is being aborted
 * @param[in] instance   - a pointer to a mpegvenc_tt object created with a mpegOutVideoNew call
 * @param[in] abort      - flag to control the finish (0: normal finish, 1: abort)
 * @return   @ref mpegOutErrNone if successful, @ref mpegOutError if not
 */
int32_t MC_EXPORT_API mpegOutVideoDone(mpegvenc_tt *instance, int32_t abort);


/**
* Call to flush encoder, set abort non-zero if encoding is being aborted
* @param[in] instance   - a pointer to a mpegvenc_tt object created with a mpegOutVideoNew call
* @param[in] abort      - flag to control the finish (0: normal finish, 1: abort)
* @return   @ref mpegOutErrNone if successful, @ref mpegOutError if not
*/
int32_t MC_EXPORT_API mpegOutVideoFlush(mpegvenc_tt *instance, int32_t abort);

/**
 * @name Visual Content Scene Detection (VCSD)
 * @{
 */
/* enumeration of different detected content-types */
#define VCSD_FLAGS_NONE    0x00000000            /**<@brief No content-change was detected @hideinitializer*/
#define VCSD_FLAGS_SCENE   0x00000001            /**<@brief This frame starts a new scene (cut) @hideinitializer*/
#define VCSD_FLAGS_CUT     VCSD_FLAGS_SCENE      /**<@brief This frame starts a new scene (cut) @hideinitializer*/
#define VCSD_FLAGS_FLASH   0x00000002            /**<@brief This frame has content speciality, next frame is similar to previous frame @hideinitializer*/
/* will be more if implemented */
#define VCSD_FLAGS_MASK    0x0000000F            /**<@brief Mask of content-type enumeration @hideinitializer*/

#define VCSD_FLAGS_TC_CUT  0x00000100            /**<@brief This frame has timecode discontinuity, probably there is content change too @hideinitializer*/


#define VCSD_STATUS_NONE    0                    /**<@brief Handle as usual stream @hideinitializer*/
#define VCSD_STATUS_SC0     1                    /**<@brief This place is prefferable to start GOP @hideinitializer*/
#define VCSD_STATUS_SC1     2                    /**<@brief Try to place GOP here @hideinitializer*/
#define VCSD_STATUS_CHAPTER 3                    /**<@brief Force to start new closed GOP @hideinitializer*/
/**@}*/

/**
 * @name Online frame skipping options
 * @{
 */
#define OPT_SKIP_MASK   (0x00000007L)
#define OPT_SKIP_1_B    (1)
#define OPT_SKIP_2_B    (2)
#define OPT_SKIP_ALL_B  (3)
#define OPT_SKIP_ALL_PB (4)
#define OPT_SKIP_ABORT_VBV_UNDERFLOW (5)        /**<@brief Encoder aborts at vbv underflow @hideinitializer*/
#define OPT_SKIP_ABORT (6)                      /**<@brief Encoder aborts once encoder plans to skip a frame @hideinitializer*/
#define OPT_SKIP_NEVER (7)                      /**<@brief Disables online skip decision, only skips frames if requantization fails to avoid vbv underflow @hideinitializer*/
// cant be greater or equal 8
/**@}*/

/* field-dominance for current frame */
/* {0,0}-undefined, {1,0} top-first, {0,1}-bottom first, {1,1}-progressive */
#define OPT_TOP_FIELD_FIRST    (0x00000010L) /**<@brief Top field is first @hideinitializer*/
#define OPT_BOT_FIELD_FIRST    (0x00000020L) /**<@brief Bottom field is first @hideinitializer*/

// #define OPT_INSERT_FRAME (0x00000100L) // see mcdefs.h
#define OPT_LINE_FILTER  (0x00000200L)
#define OPT_INV_AUTO_GOP (0x00000400L) /**<@brief Invert of automatic GOP placement feature @hideinitializer*/

// For all extended option define flags OPT_EXT_PARAM_... please see "mcdefs.h" now.

#if defined (API_EXT_PARAM_LIST)

/**
 * @name Extended parameters structure
 * @{
 */
/**
 * @brief Filled by application to request frame-level features
 */
typedef struct
{
  uint32_t  flags; /**<@brief Flags marking filled fields in this structure */

  void     *application_pointer;   /**<@brief Not handled by encoder (stored only) */
  uint32_t  application_parameter; /**<@brief Not handled by encoder (stored only) */

  void      (MC_EXPORT_API *application_report)(au_report_tt *au_state); /**<@brief Called by encoder after AccessUnit containing this frame is stored */

  int32_t   reserved[128-6]; /**<@brief reserved, must be zero'ed */
} ext_param_content_tt;
/**@}*/

/**
 * @name Target VBV data structure
 * @{
 */
/**
 * @brief Configure target VBV data
 */
typedef struct tag_target_VBV_data
{
  uint32_t API_version;                           /**<@brief Used to detect version and size of struct in future */
  uint32_t VBV_bits;                              /**<@brief VBV number of bits to have withing specified number of frames */
  uint32_t frames_togo;                           /**<@brief Number of frames till VBV state specified above should be reached */
} target_VBV_data_tt;
/**@}*/

/**
 * @name Constrain VBV data structure
 * @{
 */
/**
 * @brief Configure constrain VBV data
 */
typedef struct tag_constrain_VBV_data
{
  uint32_t API_version;                           /**<@brief Used to detect version and size of struct in future */
  uint32_t VBV_bits;                              /**<@brief VBV number of bits to have withing specified number of frames */
  uint32_t frames_togo;                           /**<@brief Number of frames till VBV state spec */
  uint16_t percentage;                            /**<@brief Assumed variation percentage for framesize during bitrate planning */
} constrain_VBV_data_tt;
/**@}*/

/**
 * @name VSCD data structure
 * @{
 */
/**
 * @brief Configure VSCD data
 */
typedef struct tag_VCSD_data
{
  uint32_t  API_version;                                          /**<@brief Used to make API backwards compatible */
  void      (MC_EXPORT_API *app_callback)(struct tag_VCSD_data*); /**<@brief Callback to application from encoder */
  void     *app_ptr;                                              /**<@brief From application, just cached in encoder */
  uint32_t  app_info;                                             /**<@brief From application, just cached in encoder */

  uint32_t  input_flags;                                          /**<@brief Content flags known at the of frame-submit */
  uint32_t  reserved0[3];

  uint32_t  VCSD_status;                                          /**<@brief Suggested level of handling (VCSD_STATUS_XXXX)*/
  uint32_t  chapter_flags;                                        /**<@brief The same content as used in chapter-list, if status is VCSD_STATUS_CHAPTER */
  uint32_t  output_flags;                                         /**<@brief Flags set by VCSD */
  uint32_t  confidence0;                                          /**<@brief Confidence fields set by VCSD */

  uint32_t  reserved1[4];
} VCSD_data_tt;
/**@}*/

/**
 * @name VSCD data structure
 * @{
 */
/**
 * @brief Configure VSCD data
 */
typedef struct
{
  uint32_t reserved1;
  uint32_t reserved2;
  uint32_t vbv_state;		/**<@brief VBV state */
  uint32_t reserved3;
} stop_data_tt;
/**@}*/

/**
 * @name Raw frame structure
 * @{
 */
/**
 * @brief Configure frame settings
 */
typedef struct
{
  uint32_t raw_data_flags;        /**<@brief Flags */
  uint32_t reserved2;
  unsigned char *raw_frame_data;  /**<@brief Pointer to buffer */
  uint32_t raw_frame_size;        /**<@brief Size of frame */
  uint32_t vbv_state;			  /**<@brief VBV state */
  uint32_t reserved3;
  uint32_t reserved4;
  uint32_t reserved5;
} raw_frame_data_tt;
/**@}*/


#define RAW_DATA_FLAGS_FIFO_DIRECT (0x01000000)
#define RAW_FRAME_GUARD 1024
#define RAW_IGNORE_FAST_SR         (0x80000000)  /**<@brief Ignore fast sr mode for specific frame @hideinitializer*/


#define FRM_STATE_FILLED      (0x0020)
#define FRM_STATE_DONE        (0x0100)
#define UD_STATE_DONE         (0x0100)

#if defined (API_UD)

/**
 * @name Raw frame structure
 * @{
 */
/**
 * @brief Configure frame settings
 */
typedef struct tag_user_data_tt
{
  uint32_t       state;                                              /**<@brief State of user data */
  void           (MC_EXPORT_API *done)(struct tag_user_data_tt *p);
  uint32_t       udata_len;                                          /**<@brief Length user data */
  unsigned char *udata;                                              /**<@brief Pointer to user data */
} user_data_tt;
/**@}*/
#endif

/**
 * @name Sample information structure
 * @{
 */
/**
 * @brief Configure Sample information
 */
typedef struct
{
  int64_t  rtStart;             /**<@brief Start time of a sample */
  int64_t  rtStop;              /**<@brief Stop time of a sample */
  int32_t  skipped_frames;      /**<@brief Skipped frames */
  uint32_t flags;               /**<@brief flags */
} sample_info_t;
/**@}*/

/**
 * @name Bit rate information structure
 * @{
 */
/**
 * @brief Configure Bit rate information
 */

typedef struct
{
  int32_t MaxBitrate;           /**<@brief Max Bit rate */
  int32_t AvgBitrate;           /**<@brief Average bit rate */
  int32_t MinBitrate;           /**<@brief Min bit rate */
} bitrate_info_t;
/**@}*/
#endif // API_EXT_PARAM_LIST

/**
 * @brief Call to encode video
 * @param[in] instance    - pointer to mpegvenc_tt object
 * @param[in] pb_src      - buffer contained picture for encoding
 * @param[in] stride      - stride of source picture
 * @param[in] width       - width of source picture
 * @param[in] height      - height of source picture
 * @param[in] fourcc      - source picture colorspace
 * @param[in] opt_flags   - options flags
 * @param[in] ext_info    - pointer to options
 * @return   @ref mpegOutErrNone if successful, @ref mpegOutError if not
 */

#if defined (API_EXT_PARAM_LIST)
// API-extension to give additional parameter-pointer to encoder
int32_t MC_EXPORT_API mpegOutVideoPutFrame(mpegvenc_tt    *instance,
                                           unsigned char  *pb_src,
                                           int32_t         stride,
                                           uint32_t        width,
                                           uint32_t        height,
                                           uint32_t        fourcc,
                                           uint32_t        opt_flags,
                                           void          **ext_info = 0);
#else
int32_t MC_EXPORT_API mpegOutVideoPutFrame(mpegvenc_tt   *instance,
                                           unsigned char *pb_src,
                                           int32_t        stride,
                                           uint32_t       width,
                                           uint32_t       height,
                                           uint32_t       fourcc,
                                           uint32_t       opt_flags);
#endif


/**
 * Call this function to encode a frame of FOURCC_BGR4 video.
 * @param[in] instance    - pointer to a mpegvenc_tt object created with a mpegOutVideoNew call
 * @param[in] videoBuffer - a pointer to the source RGB4 video frame buffer
 * @return   @ref mpegOutErrNone if successful, @ref mpegOutError if not
 * @note This call is the same as calling mpegOutVideoPutFrame specifying the FOURCC_BGR4 colorspace.
 */
int32_t MC_EXPORT_API mpegOutVideoPut(mpegvenc_tt *instance, unsigned char *videoBuffer);



/**
 * Call this function to get the maximum bitrate achieved during the last encoding session.
 * @param[in] instance   - a pointer to a mpegvenc_tt object created with a mpegOutVideoNew call
 * @return   maximum bitrate achieved in bits/second if successful 0 if unsuccessful
 */
int32_t MC_EXPORT_API mpegOutVideoGetMaxBitrate(mpegvenc_tt *instance);



/**
 * @brief call to encode video
 * @param[in] instance   - pointer to mpegvenc_tt object
 * @param[in] pframe_v   - pointer to @ref pframe_v_tt picture
 * @return   @ref mpegOutErrNone if successful, @ref mpegOutError if not
 */
#if defined (API_EXT_PARAM_LIST)
// API-extension to give additional parameter-pointer to encoder
int32_t MC_EXPORT_API mpegOutVideoPutFrameV(mpegvenc_tt *instance, pframe_v_tt pframe_v, void **ext_info);
#else
int32_t MC_EXPORT_API mpegOutVideoPutFrameV(mpegvenc_tt *instance, pframe_v_tt pframe_v);
#endif


// Call this function to check whether the video settings are valid. The general MPEG compliance checks are done first and then the Format checks are done (if the mpeg type is one of those types). 
// Use the CHECK_MPEG_ONLY flag in the options parameter to turn off the Format compliance checks (only do the general MPEG compliance checks).
// If the get_rc parameter is non-NULL, any error messages are sent to the err_printf function.
// If the options parameter does not contain CHECK_ALL, the function returns when the first non compliant value is found (the remainder of the settings are not checked). 
// If the options parameter does contain CHECK_ALL, all the checks are performed, an error message is sent to the err_printf callback for every error found and the error code of the first error found is returned.
// The Format conformance checks will return an error code less than INV_MPEG_ERROR and can be ignored if desired. 
// The settings may not produce a valid Format stream, but they will still produce a valid MPEG stream and the encoder will accept them. This can be useful for producing non-standard Format streams.
/**
 * @param[in] get_rc  - a pointer to a get_rc function. Use it to provide an err_printf callback to get error messages
 * @param[in] set     - a pointer to a filled in mpeg_v_settings structure
 * @param[in] options - one or more of the CHECK_* defines
 * @param[in] app     - reserved, set to NULL
 * @return @ref mpegOutErrNone if successful, @ref mpegOutError if not
 */
int32_t MC_EXPORT_API mpegOutVideoChkSettings(void *(MC_EXPORT_API *get_rc)(const char* name), const struct mpeg_v_settings *set, uint32_t options, void *app);


APIEXTFUNC MC_EXPORT_API mpegOutVideoGetAPIExt(uint32_t func);

#if defined (__cplusplus)
}
#endif

/** @} */

#endif // #if !defined (__ENC_MP2V_API_INCLUDED__)

