/**
@file: enc_avc.h
@brief AVC/H.264 Encoder API

@verbatim
File: enc_avc.h
Desc: AVC/H.264 Encoder API

Copyright (c) 2014 MainConcept GmbH or its affiliates.  All rights reserved.

MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.
This software is protected by copyright law and international treaties.  Unauthorized
reproduction or distribution of any portion is prohibited by law.
@endverbatim
 **/

#if !defined (__ENC_AVC_API_INCLUDED__)
#define __ENC_AVC_API_INCLUDED__

#include "mctypes.h"
#include "mcprofile.h"
#include "mcapiext.h"
#include "mcdefs.h"

#include "bufstrm.h"

#include "enc_avc_def.h"
#include "v_frame.h"


typedef struct h264_v_encoder  h264venc_tt;
typedef struct h264_v_settings h264_v_settings_tt;

typedef enum
{
    SHOW_BREF_FRAMES = 1              /**<@brief  If set, the encoder outputs B reference frames with pict_type == 4 (default pict_type == 3 for B and B referenced frames)  */
} CUSTOM_FLAGS;

#pragma pack(push,1)

/**
 * @name Settings Structure
 * @{
 **/

 /**
 *@brief These parameters are used to configure the encoder.
 */
struct h264_v_settings
{
  int32_t   profile_id;                 /**<@brief This field specifies the profile used to encode, it should be one of the preset defines */
  int32_t   level_id;                   /**<@brief This field specifies the level_id (times ten) used to maintain conformance of encoded file. */

  int32_t   idr_interval;               /**<@brief GOP length */
  int32_t   reordering_delay;           /**<@brief Maximum distance between two P frames */
  int32_t   use_b_slices;               /**<@brief Obsolete. */
  int32_t   interlace_mode;             /**<@brief @ref H264_PROGRESSIVE, @ref H264_INTERLACED or @ref H264_MBAFF */

  int32_t   def_horizontal_size;        /**<@brief This field specifies the width of the encoded video. */
  int32_t   def_vertical_size;          /**<@brief This field specifies the height of the encoded video. */

  double    frame_rate;                 /**<@brief This field specifies the frame rate of the encoded video. */


 /**
 * @name Motion search settings
 * @{
 **/
  int32_t   num_reference_frames;       /**<@brief  This field specifies the number of reference frames used. */
  int32_t   search_range;               /**<@brief  This field specifies the motion vector range */
  int32_t   rd_optimization;            /**<@brief  Rate-distortion optimization */
  int32_t   max_l0_active;              /**<@brief  Maximum index of reference frames in list0 */
  int32_t   max_l1_active;              /**<@brief  Maximum index of reference frames in list1 */
  /** @} */

 /**
 * @name Quantization parameters
 * @{
 **/
  int32_t   quant_pI;                   /**<@brief  Quantization parameter */
  int32_t   quant_pP;                   /**<@brief  Quantization parameter */
  int32_t   quant_pB;                   /**<@brief  Quantization parameter */
/** @} */

 /**
 * @name Bit rate stuff
 * @{
 **/
  int32_t   bit_rate_mode;              /**<@brief  @ref H264_CBR, @ref H264_CQT, @ref H264_VBR or @ref H264_TQM */
  int32_t   bit_rate_buffer_size;       /**<@brief  VBV buffer size */
  int32_t   bit_rate;                   /**<@brief  Average bitrate; if 0, use quantization parameters */
  int32_t   max_bit_rate;               /**<@brief  Maximum bitrate, used in VBR mode */
/** @} */

/**
 * @name Prediction
 * @{
 **/
  int32_t   inter_search_shape;         /**<@brief  @ref H264_INTERSEARCH_16x16 (use only 16x16 block size) or @ref H264_INTERSEARCH_8x8 (use block size down to 8x8) */
/** @} */

 /**
 * @name Coding mode
 * @{
 **/
  int32_t   entropy_coding_mode;        /**<@brief  @ref H264_CAVLC or @ref H264_CABAC */

  int32_t   use_hadamard_transform;     /**<@brief  0: SAD is used, 1: SATD is used, 2: SATD is used only on reference frames */
/** @} */

  ////////// vui parameters
  int32_t   sar_width;                  /**<@brief  Sample aspect ratio: horizontal size in arbitrary units */
  int32_t   sar_height;                 /**<@brief  Sample aspect ratio: vertical size in arbitrary units */

  int32_t   video_format;               /**<@brief  1: PAL, 2: NTSC */
  int32_t   video_full_range;           /**<@brief  (currently) not used. (See @ref h264_v_settings::convert_pixel_range)*/

  int32_t   num_units_in_tick;          /**<@brief  Timing info use together with time_scale */
  int32_t   time_scale;                 /**<@brief  Timing info use together with num_units_in_tick (fps = time_scale/num_units_in_tick) */

/**
 * @name Advanced settings
 * @{
 **/
  int32_t   vbv_buffer_fullness;        /**<@brief  Initial vbv-fullness */
  int32_t   vbv_buffer_fullness_trg;    /**<@brief  Final vbv-fullness */
  int32_t   vbv_buffer_units;           /**<@brief  Units of vbv-fullness and buffer size */
                                        /**<@brief  0 - old school (vbv_size in bytes, vbv_fullnesses in %%) */
                                        /**<@brief  1 - all parameters are in bits */
                                        /**<@brief  2 - new style (vbv_size in bits, vbv_fullnesses in 90 kHz clocks) */
  int32_t   cpb_removal_delay;          /**<@brief  CPB removal delay for the first picture (needed for segment merging) */

  int32_t   reserved_1[3];

  int32_t   bit_rate_scale;             /**<@brief  External setting of bit_rate_scale (avoids recalculation of bitrate) */
  int32_t   cpb_size_scale;             /**<@brief  External setting of cpb_size_scale (avoids recalculation of bitrate) */

  int32_t   max_frame_size[4];          /**<@brief  Maximum frames size for I, P, B-reference and B frames */
  int32_t   hrd_maintain;               /**<@brief  0 = hrd model disabled, 1 = hrd model enabled */
  int32_t   min_frame_size[4];          /**<@brief  Min frames size for I, P, B-reference, B frames */
  int32_t   hrd_low_delay;              /**<@brief  0 = low delay hrd disabled, 1 = low delay hrd enabled */
  int32_t   smooth_factor;              /**<@brief  Quantizer curve compression smooth factor, 0 = disabled */
  int32_t   hrd_preview;                /**<@brief  Quality feature, turned on by default. Encoder performs preliminary analisys on defined frame window. Frame window is set by the means of @ref h264_v_settings::encoding_buffering and should be at least 3 seconds and be less or equal to @ref h264_v_settings::buffering. Frames are delivered with expected delay in this case. */
/** @} */

/**
* @name Cropping offset parameters
* @{
**/
  int32_t   frame_crop_left_offset;     /**<@brief  Cropping offset from the left side of a picture, pixels */
  int32_t   frame_crop_right_offset;    /**<@brief  Cropping offset from the right side of a picture, pixels. @ref frame_crop_left_offset "More..."  */
  int32_t   frame_crop_top_offset;      /**<@brief  Cropping offset from the top of a picture, pixels. @ref frame_crop_left_offset "More..."  */
  int32_t   frame_crop_bottom_offset;   /**<@brief  Cropping offset from the bottom of a picture, pixels. @ref frame_crop_left_offset "More..."  */
/** @} */

  int32_t   reserved_1_1[8];

/**
 * @name In-loop filter
 * @{
 **/
  int32_t   use_deblocking_filter;      /**<@brief  Indicates whether to use deblocking for smoothing video frames */
  int32_t   deblocking_alphaC0_offset;  /**<@brief  Specifies the offset used in accessing alpha deblocking filter table */
  int32_t   deblocking_beta_offset;     /**<@brief  Specifies the offset used in accessing beta deblocking filter table */
  int32_t   reserved_2_1[3];
  int32_t   adaptive_deblocking;        /**<@brief  Adaptive deblocking filter */

  int32_t   reserved_2[380];
/** @} */
 /**
 * @name Type issues
 * @{
 **/
  int32_t   video_type;                 /**<@brief  It is just an encoder preset, which is used for example in @ref h264OutVideoDefaultSettings(). */
  int32_t   video_pulldown_flag;        /**<@brief  This field specifies the NTSC pulldown generated in the video stream, it should only be used if the input (original) video frame rate is 23.976 or 24 frames per second. */

  int32_t   reserved_3[30];
/** @} */
/**
 * @name Additional vui parameters
 * @{
 **/
  int32_t   overscan_appropriate_flag;      /**<@brief  Indicates whether the cropped decoded pictures output are suitable for display using overscan. */
  int32_t   colour_primaries;               /**<@brief  Indicates the chromaticity coordinates of the source primaries */
                                            /**<@brief  0 - Auto.                         */
                                            /**<@brief  1 - ITU-R Rec. BT.709-5.          */
                                            /**<@brief  2 - Unspecified (Auto).           */
                                            /**<@brief  3 - Reserved (Auto).              */
                                            /**<@brief  4 - ITU-R Rec. BT.470-6 System M. */
                                            /**<@brief  5 - ITU-R Rec. BT.601-6 625.      */
                                            /**<@brief  6 - ITU-R Rec. BT.601-6 525.      */
                                            /**<@brief  7 - SMPTE 240M.                   */
                                            /**<@brief  8 - Generic film (colour filters using Illuminant C). */
                                            /**<@brief  9 - Rec. ITU-R BT.2020.           */
                                            /**<@brief  10..255 - Reserved (Auto).        */

  int32_t   transfer_characteristics;       /**<@brief  Indicates transfer characteristics of the source primaries, defines formula for the gamma correction that wasn't implemented yet in UCC. */
                                            /**<@brief  0 - Auto.                    */
                                            /**<@brief  1 - BT.709-5.                */
                                            /**<@brief  2 - Unspecified(Auto).       */
                                            /**<@brief  3 - Reserved(Auto).          */
                                            /**<@brief  4 - BT.470-6 System M.       */
                                            /**<@brief  5 - BT.470-6 System B G.     */
                                            /**<@brief  6 - BT.709-5.                */
                                            /**<@brief  7 - SMPTE 240M.              */
                                            /**<@brief  8 - Linear.                  */
                                            /**<@brief  9..13 - Reserved(Auto).      */
                                            /**<@brief  14 - Rec. ITU-R BT.2020.     */
                                            /**<@brief  15 .. 255 - Reserved(Auto).  */


  int32_t   matrix_coefficients;            /**<@brief  Indicates matrix coefficients of the source primaries */
                                            /**<@brief  0 - Auto.                    */
                                            /**<@brief  1 - BT.709-5 System 1125.    */
                                            /**<@brief  2 - Unspecified(Auto).       */
                                            /**<@brief  3 - Reserved(Auto).          */
                                            /**<@brief  4..6 - BT.709-5 System 1250. */
                                            /**<@brief  7 - SMPTE 240M.              */
                                            /**<@brief  9 - Rec. ITU-R BT.2020 non-constant luminance system. */
                                            /**<@brief  10..255 - Reserved(Auto).    */


  int32_t   extended_sar;               /**<@brief  Enable extended sample aspect ratio.       */
                                        /**<@brief  1 - write real sample aspect ratio always. */
                                        /**<@brief  0 - round sample aspect ratio to the nearest table value from specification if the difference is less than 2%. */
  int32_t   reserved_3_0[65];
/** @} */
 /**
 * @name File/stream issues
 * @{
 **/
  int32_t   stream_type;                /**<@brief  @ref H264_STREAM_TYPE_I, @ref H264_STREAM_TYPE_I_SEI or @ref H264_STREAM_TYPE_II */
  int32_t   frame_mbs_mode;             /**<@brief  Obsolete */

  int32_t   reserved_3_1[6];

  int32_t   bit_depth_luma;             /**<@brief These field specify the bit depth of encoded luminance samples. */
  int32_t   bit_depth_chroma;           /**<@brief These field specify the bit depth of encoded chrominance samples. */
  int32_t   chroma_format;              /**<@brief @ref H264_CHROMA_420 or @ref H264_CHROMA_422 or @ref H264_CHROMA_444 */

  int32_t   reserved_3_2[12];

  int32_t   pic_init_qp;                /**<@brief This field is corresponding to field pic_init_qp_minus26 in PPS. By default it has value of 26 and there is no significant reason to change it. Parameter is available via API only. */
  int32_t   pic_init_qs;                /**<@brief This field is corresponding to field pic_init_qs_minus26 in PPS. As long as the encoder doesn't support SI and SP slices this field affects only PPS. Parameter is available via API only. */

  uint32_t  vui_presentation;           /**<@brief  Configuration of VUI header */
                                        /**<@brief  0 - old school / auto mode */
                                        /**<@brief  1 - customized configuration, depending on following flags/bits: */
                                        /**<@brief  0x002 - aspect_ratio_info_present_flag */
                                        /**<@brief  0x004 - overscan_info_present_flag (not supported) */
                                        /**<@brief  0x008 - video_signal_type_present_flag */
                                        /**<@brief  0x010 - colour_description_present_flag */
                                        /**<@brief  0x020 - chroma_loc_info_present_flag (not supported) */
                                        /**<@brief  0x040 - timing_info_present_flag */
                                        /**<@brief  0x080 - nal_hrd_parameters_present_flag */
                                        /**<@brief  0x100 - vcl_hrd_parameters_present_flag */
                                        /**<@brief  0x200 - pic_struct_present_flag */
                                        /**<@brief  0x400 - bitstream_restriction_flag */

  int32_t   write_au_delimiters;        /**<@brief  Write access unit delimiters */
  int32_t   write_seq_end_code;         /**<@brief  Write sequence end code */
  int32_t   write_timestamps;           /**<@brief  Write picture timecode in PT SEI (0 - don't write, 1 - write timecode with ClockTS format with optional fields, 2 - write timecode with ClockTS format with full_time_stamp_flag */
  int32_t   timestamp_offset;           /**<@brief  Frame offset (in number of frames) for timestamps (default = 0) */
  int32_t   drop_frame_timecode;        /**<@brief  Use NTSC drop frame timecode notation for 29.97 and 59.94 target frame rates */
  int32_t   write_single_sei_per_nalu;  /**<@brief  Writes single SEI message per NAL unit */
  int32_t   write_seq_par_set;          /**<@brief  Behaviour of writing sequence parameter set (default = 0) */
                                        /**<@brief  0 - old school (SPS once per IDR) */
                                        /**<@brief  1 - SPS once per I-frame */
  int32_t   write_pic_par_set;          /**<@brief  Behaviour of writing picture parameter set (default = 0) */
                                        /**<@brief  0 - old school (PPS once per IDR) */
                                        /**<@brief  1 - PPS once per I picture */
                                        /**<@brief  2 - PPS once per picture */

  int32_t   log2_max_poc;               /**<@brief  Allows to specify custom log2_max_pic_order_cnt_lsb_minus4 value */
                                        /**<@brief  Valid range is 4..16, default - 8 */
  int32_t   log2_max_frame_num;         /**<@brief  Allows to specify custom log2_max_frame_num_minus4 value */
                                        /**<@brief  Valid range is 4..16, default - 8 */

  int32_t   pic_order_cnt_type;         /**<@brief  Allows to specify custom pic_order_cnt_type value */
                                        /**<@brief  Valid values are 0 (default) and 2 */

  int32_t   pic_order_present_flag;     /**<@brief  Controls pic_order_present_flag value in PPS (e.g. for SBTVD-T) */

  int32_t   fixed_frame_rate;           /**<@brief  Controls fixed_frame_rate_flag in VUI */
  int32_t   frame_based_timing;         /**<@brief  Controls time_scale / num_units_in_tick ration in VUI (field or frame rate) */
  int32_t   frame_packing_arrangement_mode; /**<@brief 0 = don`t write, 1 = checkerboard, 2 = column based interleaving, 3 = row based interleaving, 4 = side-by-side packing arrangement , 5 = top-bottom packing arrangement */
  int32_t   stream_creation_product_info;   /**<@brief 0 = don`t write, 1 = LL component, 2 = DS component*/
  int32_t   write_pic_timing_sei;       /**<@brief  Writes pic_timing SEI message */
  int32_t   write_settings_info;        /**<@brief  0 = don`t write, 1 = write settings on first IDR only, 2 = write settings on every IDR */
  int32_t   frame_num_gaps_allowed_flag;/**<@brief  sets gaps_in_frame_num_value_allowed_flag for decoder to create "dummy" decoded frames to fill gap */
  CUSTOM_FLAGS custom_bit_flags;        /**<@brief  Set of flags for customer needs */

  int32_t   reserved_4[110];
/** @} */

/**
 * @name Scene detection
 * @{
 **/
  int32_t   vcsd_mode;                  /**<@brief  Visual content scene detection, 0: OFF, 1: IDR (see vcsd_mode_flags) */
  int32_t   vcsd_sensibility;           /**<@brief  Obsolete */
/** @} */

/**
 * @name Advanced settings
 * @{
 **/
  int32_t   slice_mode;                 /**<@brief  Currently only fixed number of slices per picture is implemented */
  int32_t   slice_arg;                  /**<@brief  Number of slices per picture */

  int32_t   b_slice_reference;          /**<@brief  Use b slices as reference too (b -> B) */
  int32_t   b_slice_pyramid;            /**<@brief  Pyramidal GOP structure  (...bBb...) */

  int32_t   cb_offset;                  /**<@brief  Chroma quality offset (-X -> increase quality, +X -> decrease quality) */
  int32_t   cr_offset;                  /**<@brief  Chroma quality offset (-X -> increase quality, +X -> decrease quality) */

  int32_t   me_subpel_mode;             /**<@brief  @ref H264_FULL_PEL, @ref H264_HALF_PEL, @ref H264_QUARTER_PEL or @ref H264_QUARTER_PEL_ON_REF */
  int32_t   me_weighted_p_mode;         /**<@brief  Whether to use explicit WP for P-frames or not */
  int32_t   me_weighted_b_mode;         /**<@brief  (currently) not used */

  int32_t   enable_fast_intra_decisions;/**<@brief  Enables fast intra decisions (0 - no fast intra decisions, 1 - fast intra decisions are enabled, 2 - fast intra decisions are enabled only on non-reference) */
  int32_t   enable_fast_inter_decisions;/**<@brief  Enables fast inter decisions (0 - no fast inter decisions, 1 - fast inter decisions are enabled, 2 - fast inter decisions are enabled only on non-reference) */

  int32_t   pic_ar_x;                   /**<@brief  Picture aspect ratio: horizontal size */
  int32_t   pic_ar_y;                   /**<@brief  Picture aspect ratio: vertical size */

  int32_t   calc_quality;               /**<@brief  0 - Not calculate any metrics, 1 - Calculate PSNR metrics, 2 - Calculate SSIM metrics, 3 - Calculate PSNR and SSIM metrics */
  int32_t   cpu_opt;                    /**<@brief  CPU optimization */
  int32_t   num_threads;                /**<@brief  Number of threads */
  int32_t   live_mode;                  /**<@brief  Online or offline mode (not yet implemented) */
  int32_t   buffering;                  /**<@brief  Maximum number of seconds to buffer */

  int32_t   min_quant;                  /**<@brief  Minimum quantization parameter */
  int32_t   max_quant;                  /**<@brief  Maximum quantization parameter */

  int32_t   max_slice_size;             /**<@brief  Maximum slice size in bits, set to 0 if you do not need it */

  int32_t   min_qp_delta;               /**<@brief  Lowest value for slice_qp_delta */
  int32_t   max_qp_delta;               /**<@brief  Highest value for slice_qp_delta */

  int32_t   reserved_5[1];

  int32_t   encoding_buffering;         /**<@brief  Maximum number of seconds to buffer encoding queue. Should be less or equal to @ref h264_v_settings::buffering */

  int32_t   low_delay;                  /**<@brief  Low delay mode (not yet implemented) */

  int32_t   air_mode;                   /**<@brief  Adaptive intra refresh mode */

  int32_t   detach_thread;              /**<@brief  Run core in a new thread or not */

  int32_t   constrained_intra_pred;     /**<@brief  Constrained intra prediction for improving error resilience */

  int32_t   air_split_frequency;        /**<@brief  Frequency of intra lines for adaptive air mode split */

  int32_t   air_qp_offset;              /**<@brief  QP offset for adaptive intra mode lines */

  int32_t   convert_pixel_range;        /**<@brief  Type of pixel range conversion algorithm */

  int32_t   deinterlacing_mode;        /**<@brief  Deinterlace source stream */

  int32_t   num_parallel_pics;         /**<@brief  Number of pictures for parallel encoding */

  int32_t   reserved_5_1[280];
/** @} */

/**
 * @name Advanced GOP settings
 * @{
 **/
  int32_t   min_idr_interval;           /**<@brief  Min GOP length */
  int32_t   adaptive_b_frames;          /**<@brief  Use adaptive B-frames placement or not */
  int32_t   idr_frequency;              /**<@brief  0 means only first frame is IDR, 1 means every I-frame is IDR, etc. */
  int32_t   field_order;                /**<@brief  0 - TFF, 1- BFF */
  int32_t   fixed_i_position;           /**<@brief  Constant I frame position */
  int32_t   isolated_gops;              /**<@brief  Allows to limit referencing to frames from the previous GOP, may be useful when idr_frequency != 1 */
  int32_t   leading_b_frames;           /**<@brief  Allows B-frames before an I-frame in display order in open GOP (isolated_gops should be set to 0) */
  int32_t   hierar_p_frames;            /**<@brief  GOP structure with hierarchically coded P frames (for temporal scalability with out using B frames) (not yet supported) */

  int32_t   reserved_6[46];
/** @} */

/**
 * @name Advanced me settings
 * @{
 **/
  int32_t   fast_multi_ref_me;          /**<@brief  Enables fast decisions for multi-ref ME */
  int32_t   fast_sub_block_me;          /**<@brief  Enables fast decisions for sub-block ME */
  int32_t   allow_out_of_pic_mvs;       /**<@brief  Enables Motion Vectors out of picture boundaries */
  int32_t   constrained_ref_list;       /**<@brief  Use constrained reference picture list */
  int32_t   motion_search_pattern;      /**<@brief  Motion search pattern @ref H264_DIAMOND, @ref H264_HEX_HORZ, @ref H264_HEX_HORZ_FLAT, @ref H264_HEX_VERT and @ref H264_HEX_VERT_FLAT*/
  int32_t   reserved_7[95];
/** @} */

/**
 * @name Advanced intra settings
 * @{
 **/
  int32_t   enable_intra_big;           /**<@brief  Allows to use 16x16 intra prediction modes in intra slices */
  int32_t   enable_intra_8x8;           /**<@brief  Allows to use 8x8 intra prediction modes in intra slices */
  int32_t   enable_intra_4x4;           /**<@brief  Allows to use 4x4 intra prediction modes in intra slices */
  int32_t   enable_intra_pcm;           /**<@brief  Allows to use PCM intra prediction modes in intra slices */

  int32_t   enable_inter_big;           /**<@brief  Allows to use 16x16 intra prediction modes in inter slices */
  int32_t   enable_inter_8x8;           /**<@brief  Allows to use 8x8 intra prediction modes in inter slices */
  int32_t   enable_inter_4x4;           /**<@brief  Allows to use 4x4 intra prediction modes in inter slices */
  int32_t   enable_inter_pcm;           /**<@brief  Allows to use PCM intra prediction modes in inter slices */

  int32_t   reserved_8[92];
/** @} */

/**
 * @name Advanced RDO (Rate Distortion Optimization) settings
 * @{
 **/
  int32_t   fast_rd_optimization;       /**<@brief  Allows fast RDO */
  int32_t   quant_mode;                 /**<@brief  Quantization optimization mode */
  int32_t   grain_mode;                 /**<@brief  Granular noise optimization mode, not used any more */
  int32_t   grain_opt_strength;         /**<@brief  Scalable film grain optimization [0..100], use 0 to turn it off */

  int32_t   reserved_9[90];
/** @} */
  int32_t   adaptive_quant_strength[8]; /**<@brief  Adaptive quantization strength [-100..100] or every mode (@ref H264_AQUANT_MODE_BRIGHTNESS, @ref H264_AQUANT_MODE_CONTRAST, @ref H264_AQUANT_MODE_COMPLEXITY), last 5 strengths are not used at the moment */

/**
 * @name Psycho-visual enhancement
 * @{
 **/
  int32_t   denoise_strength_y;         /**<@brief  Denoise strength for luma [0..100] */
  int32_t   denoise_strength_c;         /**<@brief  Denoise strength for chroma [0..100] */

  int32_t   black_norm_level;           /**<@brief  Black normalization level, any luma less than or equal to black_norm_level will be set to 16 */

  int32_t   pulse_reduction;            /**<@brief  Key frame pulsing reduction */

  int32_t   reserved_9_1[127];          /**<@brief  */
/** @} */

/**
 * @name Alpha plane
 * @{
 **/
  int32_t   aux_format_idc;
  int32_t   bit_depth_aux;
  uint32_t  alpha_incr_flag;
  uint32_t  alpha_opaque_value;
  uint32_t  alpha_transparent_value;

  int32_t   reserved_9_2[100];
/** @} */

  ////////// seq_scaling_list_present_flag equal[i] to 1 specifies that the syntax structure
  ////////// for scaling list i is present in the sequence parameter set (and not in the picture parameter set)
  uint32_t  seq_scaling_matrix_present_flag;

  uint32_t  seq_scaling_list_present_flag[8];

 /**
 * @name Scaling lists
 * @{
 **/
  uint8_t   intra_y_4x4_scaling_list[16];
  uint8_t   intra_cb_4x4_scaling_list[16];
  uint8_t   intra_cr_4x4_scaling_list[16];
  uint8_t   inter_y_4x4_scaling_list[16];
  uint8_t   inter_cb_4x4_scaling_list[16];
  uint8_t   inter_cr_4x4_scaling_list[16];
  uint8_t   intra_y_8x8_scaling_list[64];
  uint8_t   inter_y_8x8_scaling_list[64];
/** @} */

  int32_t   reserved_10[128];

/**
 * @name GPU encoder stuff
 * @{
 **/

  int32_t   device_idx;        /**<@brief  GPU device index to run encoder on */
  int32_t   input_format;      /**<@brief  NVCUVID Decoder format */
/** @} */

  int32_t   reserved_11[267];
};

/** @} */


#pragma pack(pop)



#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Fills @ref h264_v_settings structure with preset default values according to resolution, frame rate and interlace mode
 * @param[in] video_type     encoder preset
 * @param[in] width          specifies width of the encoded video
 * @param[in] height         specifies height of the encoded video
 * @param[in] frame_rate     specifies the frame rate of the encoded video
 * @param[in] pic_struct     specifies the picture structure of the encoded video: @ref H264_PROGRESSIVE, @ref H264_INTERLACED or @ref H264_MBAFF
 * @param[in] get_rc         the get_rc callback to provide an err_printf callback to get error messages
 * @param[out] set           destination for encoder settings
  *@param[out] string_ptr    pointer to string with encoder preset description
 * @return Returns @ref H264ERROR_NONE, @ref H264ERROR_FAILED or @ref H264ERROR_PARAM_ADJUSTED
 */
int32_t MC_EXPORT_API h264OutVideoDefaultSettings(int32_t                  video_type,
                                                  int32_t                  width,
                                                  int32_t                  height,
                                                  double                   frame_rate,
                                                  int32_t                  pic_struct,
                                                  void * (MC_EXPORT_API   *get_rc)(const char* name),
                                                  h264_v_settings_tt      *set,
                                                  const char             **string_ptr);

/**
 * @brief Changes performance-related part of @ref h264_v_settings structure
 * @param[in] set       - encoder settings to adjust
 * @param[in] mode      - performance mode (irrelevant for now)
 * @param[in] level     - performance level, from @ref H264_PERF_FASTEST to @ref H264_PERF_BEST_Q
 */
void MC_EXPORT_API h264OutVideoPerformance(struct h264_v_settings * set,
                                           int32_t                  mode,
                                           int32_t                  level,
                                           int32_t                  reserved);


#define INSTANCE_OPT_ACC_OFF 0x00000001

/**
 * @brief Creates a new H264-Video-Encoder instance.
 * @param[in] get_rc
 * @param[in] set
 */
h264venc_tt * MC_EXPORT_API h264OutVideoNew(void *                         (MC_EXPORT_API * get_rc)(const char* name),
                                            const struct h264_v_settings * set,
                                            int32_t                        options,
                                            int32_t                        CPU,
                                            int32_t                        frame0,
                                            int32_t                        nframes);

/**
 * @brief Destroys the H264-Video-Encoder instance.
 * @param[in] instance the video encoder instance.
 */
void MC_EXPORT_API h264OutVideoFree(h264venc_tt * instance);


#define INIT_OPT_AUTHENT         0x00000010

//////////////////// multi-pass API ////////////////////
#ifdef RC_2VBR
  #define INIT_OPT_VBR_PASS2_PARAM 0x00000400	/**<@brief Enables 2-pass encoding with internal metadata storage */
  #define INIT_OPT_VBR_TWO_PASSES  0x00000800	/**<@brief Enables 2-pass encoding eith external metadata storage */
  #define INIT_OPT_VBR_ANALYSE     0x00000900	/**<@brief Quick first encoding pass performing only analysis */
  #define INIT_OPT_VBR_ENCODING    0x00000F00
  #define INIT_OPT_VBR_PASSES_MASK 0x00000F00
  #define INIT_OPT_VBR_EXT_STORAGE 0x00000100
#endif

/**
 * @name Pass2 settings Structure
 * @{
 **/
 /**
 * @brief These parameters are used to configure the second pass.
 */
struct h264_pass2_parameters
{
  int32_t start;
  int32_t count;

  int32_t reserved[10];
};
/** @} */

#define INIT_OPT_CHAPTER_LIST   0x00001000		/**<@brief This option can be passed via opt_ptr in @ref h264OutVideoInit to force I-Frames at certain points in the stream. */

//////////////////// chapterlist API ////////////////////
#if defined (CHAPTER_POINTS_SUPPORTED)
#define CHAPTER_FRAME_NR       (0x00000004L) 	/**<@brief Change the timecode at this point of the stream to the timecode corresponding to the given frame_nr */
#define CHAPTER_FRAME_NR_MASK  (0xFFFFFF00L)	/**<@brief */
#define CHAPTER_REARRANGE_GOPS (0x00000010L) 	/**<@brief rearrange preceding GOPs for getting gop length as equal as possible */
#define CHAPTER_FORCE_IDR      (0x00000020L) 	/**<@brief put IDR at the start of the chapter even if idr_frequency is 0 */
#define CHAPTER_END_OF_LIST    (~0L)

struct h264_chapter_position
{
  int32_t frame_nr;
  int32_t flags;
};
#endif // #if defined (CHAPTER_POINTS_SUPPORTED)

#define INIT_OPT_SET_PREVIEW   0x00002000

/**
 * @brief Call to initialize encoding settings.
 * @param[in] instance the video encoder instance.
 * @param[in] videobs bitstream object for writing data. Must be initialized before.
 * @param[in] options flags
 * @param[in] options pointers
 * @return Return one of defined errors (@ref H264ERROR_NONE or @ref H264ERROR_FAILED)
 */
int32_t MC_EXPORT_API h264OutVideoInit(h264venc_tt *      instance,
                                       struct bufstream * videobs,
                                       uint32_t           options_flags,
                                       void **            opt_ptr);


/**
 * @brief Call to finish encoding session.
 * @param[in] instance the video encoder instance.
 * @param[in] abort If abort equals 0, finish any leftover video and clean up, else just clean up.
 */
int32_t MC_EXPORT_API h264OutVideoDone(h264venc_tt * instance, int32_t abort);

// For all extended option define flags OPT_EXT_PARAM_... please see "mcdefs.h" now.

/**
 * @name Target VBV data structure
 * @{
 **/
 /**
 * @brief These parameters are used to define target VBV settings
 */
typedef struct tag_h264_target_VBV_data
{
  uint32_t API_version;  /**< Used to detect version and size of struct in future */
  uint32_t vbv_fullness; /**< VBV fullness (in %) to achieve within specified number of frames */
  uint32_t frames_togo;  /**< Number of frames till VBV state specified above should be reached */

  uint32_t reserved[13];

} h264_target_VBV_data_tt;
/** @} */

//////////////////// user data API ////////////////////
#if defined (AVC_UD_SUPPORTED)
typedef struct h264_user_data
{
  uint32_t        type;         // 1 = registered, 2 = unregistered (other values are reserved for future)
  uint32_t        size;         // size of the user data
  unsigned char  *data;         // user data
  uint32_t        lock;         // if 0, data/pointer can be destroyed again
  void           *next;         // pointer to @ref h264_user_data structure (0 = no more data)
  uint32_t       reserved[15];

} h264_user_data_tt;
#endif // #if defined (AVC_UD_SUPPORTED)

/**
 * @name Alpha plane data structure
 * @{
 **/
 /**
 * @brief These parameters are used to define target VBV settings
 */
typedef struct h264_alpha_plane_data
{
  int32_t   aux_format_idc;               /**< -1 = no sps_extension (SD : not sure that we need this here, should be already handled in core)
                                                1 = auxiliary coded pictures should be multiplied
                                                2 = auxiliary coded pictures should not be multiplied
                                                3 = usage of auxiliary coded pictures is unspecified */
  int32_t   bit_depth_aux;                /**<  bit depth of the sample array of the auxiliary coded picture */
  uint32_t  alpha_incr_flag;              /**<  s. 7.4.2.1.2 */
  uint32_t  alpha_opaque_value;           /**<  s. 7.4.2.1.2 */
  uint32_t  alpha_transparent_value;      /**<  s. 7.4.2.1.2 */

  uint8_t * data;                         /**<  alpha plane data */

} h264_alpha_plane_data_tt;
/** @} */

//////////////////// smartrender API ////////////////////
/**
 * @name Smart renderer mode flags
 * @{
 **/
#define SR_MODE_MASK           (0xFFFF0000L)
#define SR_MODE_AUTO           (0x00000000L)
#define SR_MODE_COPY           (0x00010000L)
#define SR_MODE_FULL           (0x00020000L)
#define SR_MODE_SMART          (0x00030000L)
/** @} */

/**
 * @name Smart renderer data type flags
 * @{
 **/
#define SR_DATA_TYPE_MASK      (0x0000FFFFL)
#define SR_DATA_TYPE_PAYLOAD   (0x00000001L)
#define SR_DATA_TYPE_AVC_INTRA (0x00000009L)
#define SR_DATA_TYPE_ORG_FRAME (0x00000002L)
//#define SR_DATA_TYPE_META      (0x00000100L) // Unsupported mode.
/** @} */


/**
 * @name Smart renderer data structure
 * @{
 **/
 /**
 * @brief These parameters are used by smart renderer
 */
typedef struct h264_sr_data
{
  uint32_t    data_flags;    /**< describes mode flags and data type */
  uint32_t    data_size;     /**< the size of data in bytes */
  void *      data;          /**< pointer to the data */
  void *      next;          /**< pointer to additional data */
  uint32_t    reserved[12];

} h264_sr_data_tt;
/** @} */

/**
 * @brief Call to encode one video frame.
 * @param[in] instance the video encoder instance.
 * @param[in] pbSrc pointer to the frame buffer to be encoded.
 * @param[in] stride of source frame
 * @param[in] width of source frame
 * @param[in] height of source frame
 * @param[in] source colorspace
 * @param[in] options flags
 * @param[in] extended info
 * @return    Return one of defined errors (@ref H264ERROR_NONE .. @ref H264ERROR_AVC_INTRA_SKIPPED_FRAME)
 */
int32_t MC_EXPORT_API h264OutVideoPutFrame(h264venc_tt *   instance,
                                           uint8_t *       pb_src,
                                           int32_t         src_line_size,
                                           int32_t         src_width,
                                           int32_t         src_height,
                                           uint32_t        fourcc,
                                           uint32_t        opt_flags,
                                           void **         ext_info);

/**
 * @brief Call to encode one video frame. Similar to above method.
 * @param[in] instance the video encoder instance.
 * @param[in] pframe_v the frame to be encoded..
 * @param[in] options flags
 * @param[in] extended info
 * @return    Return one of defined errors (@ref H264ERROR_NONE .. @ref H264ERROR_AVC_INTRA_SKIPPED_FRAME)
 */
int32_t MC_EXPORT_API h264OutVideoPutFrameV(h264venc_tt *    instance,
                                            video_frame_tt * pframe_v,
                                            uint32_t         opt_flags,
                                            void **          ext_info);

/**
 * @brief Gets maximal achieved bitrate during encoding session.
 * @param[in] instance the video encoder instance.
 * @remark This function is not supported for now
 */
int32_t MC_EXPORT_API h264OutVideoGetMaxBitrate(h264venc_tt * instance);


/**
 * @brief Call to change settings on-the-fly.
 * @param[in] instance the video encoder instance.
 * @param[in] set the encoder settings.
 * @remarks This is only possible for some specific settings like bitrate.
 * @return    Return one of defined errors (@ref H264ERROR_NONE or @ref H264ERROR_FAILED)
 */
int32_t MC_EXPORT_API h264OutVideoUpdateSettings(h264venc_tt *                  instance,
                                                 const struct h264_v_settings * set);


/**
 * @brief Checks encoder settings for any conformance invalidation.
 * @param[in] get_rc the get_rc callback to provide an err_printf callback to get error messages that can be localized.
 * @param[in] set the encoder settings.
 * @param[in] options use @ref H264_CHECK_AND_ADJUST to adjust settings to be conform.
 * @param[in] app
 * @return Returns one of  defined errors (@ref H264ERROR_NONE or @ref H264ERROR_FAILED)
 */
int32_t MC_EXPORT_API h264OutVideoChkSettings(void *                   (MC_EXPORT_API * get_rc)(const char* name),
                                              struct h264_v_settings * set,
                                              uint32_t                 options,
                                              void *                   app);


/**
 * @brief Gets current vbv state (vbv buffer fullness in %) during encoding session.
 * @param[in] instance the video encoder instance.
 * @return Returns fullness of coded picture buffer
 */
int32_t MC_EXPORT_API h264OutVideoGetVBVState(h264venc_tt * instance);


/**
 * @brief Returns buffer with parameter sets and its length
 * @param[in] instance the video encoder instance.
 * @param[in] set the encoder settings.
 * @param[in] buffer buffer which will be used for writing of parameter sets, buffer can be NULL, in this case the encoder just calculates and returns length required to store parameter sets.
 * @param[in,out] length a length of the buffer, initially should contain the actual length of the buffer, when the function returns length will contain the actual number of bytes written into the buffer
 * @return Returns one of defined errors (@ref H264ERROR_NONE or @ref H264ERROR_FAILED)
 * @remarks If function returns @ref H264ERROR_FAILED and returns -1 in length it means that some internal error is happened.
 */
int32_t MC_EXPORT_API h264OutVideoGetParSets(h264venc_tt *            instance,
                                             struct h264_v_settings * set,
                                             uint8_t *                buffer,
                                             int32_t *                length);


/**
 * @brief Flushes encoder queue
 * @param[in] instance the video encoder instance.
 * @param[in] abort flag.
 * @return Returns one of defined errors (@ref H264ERROR_NONE or @ref H264ERROR_FAILED)
 **/
int32_t MC_EXPORT_API h264OutVideoFlush(h264venc_tt * instance, int32_t abort);


APIEXTFUNC  MC_EXPORT_API h264OutVideoGetAPIExt(uint32_t func);


#ifdef __cplusplus
}
#endif

/** @} */

#endif // #if !defined (__ENC_AVC_API_INCLUDED__)

