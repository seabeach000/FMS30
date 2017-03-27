/**
@file: enc_avc_def.h
@brief AVC/H.264 Encoder API defines

@verbatim
File: enc_avc_def.h
Desc: AVC/H.264 Encoder API defines

Copyright (c) 2014 MainConcept GmbH or its affiliates.  All rights reserved.

MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.
This software is protected by copyright law and international treaties.  Unauthorized
reproduction or distribution of any portion is prohibited by law.
@endverbatim
 **/


#if !defined (__ENC_AVC_DEF_INCLUDED__)
#define __ENC_AVC_DEF_INCLUDED__

/**
@def H264_VIDEO_TYPES
@name Video type defines
@{
**/

#define H264_BASELINE                 0        /**< @brief  Baseline Profile @hideinitializer*/
#define H264_CIF                      1        /**< @brief  similar to MPEG1 VideoCD @hideinitializer*/
#define H264_MAIN                     2        /**< @brief  similar to ISO/IEC 13818-1/2 @hideinitializer*/
#define H264_SVCD                     3        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_D1                       4        /**< @brief  similar to MPEG2 DVD @hideinitializer */
#define H264_HIGH                     5        /**< @brief  High Profile 1920x1080i @hideinitializer */
#define H264_DVD                      6        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_HD_DVD                   7        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_BD                       8        /**< @brief  Blu-ray Disc @hideinitializer */
#define H264_BD_HDMV                  9        /**< @brief  Blu-ray Disc (Main Video) @hideinitializer */
#define H264_PSP                     10        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 Sony PSP @hideinitializer */
#define H264_HDTV_720p               11        /**< @brief  1280x720p @hideinitializer */
#define H264_HDTV_1080i              12        /**< @brief  1440x1080i @hideinitializer */
#define H264_iPOD                    13        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_AVCHD                   14        /**< @brief  AVCHD @hideinitializer */
#define H264_iPOD_640x480            15        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_1SEG                    16        /**< @brief  1seg compatible @hideinitializer */
#define H264_INTRA_HIGH_10           17        /**< @brief   @hideinitializer */
#define H264_INTRA_CLASS_50          18        /**< @brief  H.264 intra frame coding (Class 50) @hideinitializer */
#define H264_INTRA_CLASS_100         19        /**< @brief  H.264 intra frame coding (Class 100) @hideinitializer */
#define H264_PSP_480x270             20        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_PSP_640x480             21        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DIVX                    22        /**< @brief  @hideinitializer */
#define H264_FLASH_LOWRES            23        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_FLASH_HIGHRES           24        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_3GP                     25        /**< @brief  3GP @hideinitializer */
#define H264_SILVERLIGHT             26        /**< @brief  Microsoft Silverlight Profile @hideinitializer */
#define H264_DVB_SD                  27        /**< @brief  ETSI TS 101 154 V1.9.1, paragraph 5.6 @hideinitializer */
#define H264_DVB_HD                  28        /**< @brief  ETSI TS 101 154 V1.9.1, paragraph 5.7 @hideinitializer */
#define H264_IPTV_480i               30        /**< @brief  IPTVFJ STD-0004 [Appendix A] @hideinitializer */
#define H264_IPTV_720p               31        /**< @brief  IPTVFJ STD-0004 [Appendix A] @hideinitializer */
#define H264_IPTV_1080i              32        /**< @brief  IPTVFJ STD-0004 [Appendix A] @hideinitializer */
#define H264_INTRA_CLASS_50_RP2027   33        /**< @brief  RP2027 H.264 intra frame coding (Class 50) @hideinitializer */
#define H264_INTRA_CLASS_100_RP2027  34        /**< @brief  RP2027 H.264 intra frame coding (Class 100) @hideinitializer */
#define H264_iPAD                    35        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_PIFF                    36        /**< @brief  fragmented MP4 PIFF (as part of ISOFF), not yet supported @hideinitializer */
#define H264_IIS_SMOOTHSTREAMING     37        /**< @brief  fragmented MP4 IIS Smooth Streaming Transport Protocol, treat like @ref H264_SILVERLIGHT for now @hideinitializer */
#define H264_DPS_L1                  39        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_L2                  40        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_L3                  41        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_L4                  42        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_L5                  43        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_L6                  44        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_L7                  45        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_L8                  46        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_L9                  47        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_TPT                 48        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_HEMT_L1             49        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_HEMT_L2             50        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_HEMT_L3             51        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_HEMT_L4             52        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_HEMT_L5             53        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_HEMT_L6             54        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_HEMT_L7             55        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_HEMT_L8             56        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_HEMT_L9             57        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_HEMT_L10            58        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_HEMT_L11            59        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_LEM_L1              60        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_LEM_L2              61        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_DPS_LEM_L3              62        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_HD_DVD_BD_MV            64        /**< @brief  Redundant HD DVD & BD MV (external script needed to convert to target application) @hideinitializer */
#define H264_ULTRAVIOLET_PD_L1       65        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_ULTRAVIOLET_PD_L2       66        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_ULTRAVIOLET_PD_L3       67        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_ULTRAVIOLET_SD_L1       68        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_ULTRAVIOLET_SD_L2       69        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_ULTRAVIOLET_HD_L1       70        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_ULTRAVIOLET_HD_L2       71        /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_INTRA_CLASS_200_RP2027  72        /**< @brief  RP2027-2012 H.264 intra frame coding (Class 200) @hideinitializer */
#define H264_AVCHD_20                75        /**< @brief  AVCHD 2.0 1080/50p 1080/60p @hideinitializer */
#define H264_DASH264                 76        /**< @brief  DASH264 @hideinitializer */
#define H264_LONG_GOP_422_CLASS_G50  78        /**< @brief  Panasonic AVC-LongG 4:2:2 Classes G50 (50 Mbps) @hideinitializer */
#define H264_LONG_GOP_422_CLASS_G25  79        /**< @brief  Panasonic AVC-LongG 4:2:2 Classes G25 (25 Mbps) @hideinitializer */
#define H264_LONG_GOP_420_CLASS_G12  80        /**< @brief  Panasonic AVC-LongG 4:2:0 Classes G12 (12 Mbps) @hideinitializer */
#define H264_LONG_GOP_420_CLASS_G6   81        /**< @brief  Panasonic AVC-LongG 4:2:0 Classes G6 (6 Mbps) @hideinitializer */
#define H264_INTRA_CLASS_200         82        /**< @brief  H.264 intra frame coding (Class 200) @hideinitializer */
#define H264_XAVC_4K                      83   /**< @brief  SONY XAVC Long GOP 4K Profile for M4 and XD Style (MP4 and MXF file formats) @hideinitializer */
#define H264_XAVC_HD_MP4                  84   /**< @brief  SONY XAVC Long GOP HD Profile for M4 Style (MP4 file format) @hideinitializer */
#define H264_XAVC_HD_MXF                  85   /**< @brief  SONY XAVC Long GOP HD Profile for XD Style (MXF file format) @hideinitializer */
#define H264_XAVC_HD_INTRA_VBR            86   /**< @brief  SONY XAVC HD Intra VBR Profile for M4 Style (MP4 file format) @hideinitializer */
#define H264_XAVC_HD_INTRA_CLASS_50_CBG   87   /**< @brief  SONY XAVC HD Intra CBG Profile Class 50 for XD Style (MXF file format) @hideinitializer */
#define H264_XAVC_HD_INTRA_CLASS_100_CBG  88   /**< @brief  SONY XAVC HD Intra CBG Profile Class 100 for XD Style (MXF file format) @hideinitializer */
#define H264_XAVC_HD_INTRA_CLASS_200_CBG  89   /**< @brief  SONY XAVC HD Intra CBG Profile Class 200 for XD Style (MXF file format) @hideinitializer */
#define H264_XAVC_4K_INTRA_CLASS_100_CBG  90   /**< @brief  SONY XAVC 4K Intra CBG Class 100 for XD Style (MXF file format) @hideinitializer */
#define H264_XAVC_4K_INTRA_CLASS_300_CBG  91   /**< @brief  SONY XAVC 4K Intra CBG Class 300 for XD Style (MXF file format) @hideinitializer */
#define H264_XAVC_4K_INTRA_CLASS_480_CBG  92   /**< @brief  SONY XAVC 4K Intra CBG Class 480 for XD Style (MXF file format) @hideinitializer */
#define H264_XAVC_4K_INTRA_CLASS_100_VBR  93   /**< @brief  SONY XAVC 4K Intra VBR Class 100 for XD Style (MXF file format) @hideinitializer */
#define H264_XAVC_4K_INTRA_CLASS_300_VBR  94   /**< @brief  SONY XAVC 4K Intra VBR Class 300 for XD Style (MXF file format) @hideinitializer */
#define H264_XAVC_4K_INTRA_CLASS_480_VBR  95   /**< @brief  SONY XAVC 4K Intra VBR Class 480 for XD Style (MXF file format) @hideinitializer */
#define H264_HLS_CELL_L1                  96   /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_HLS_CELL_L2                  97   /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_HLS_CELL_L3                  98   /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_HLS_WIFI_L1                  99   /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_HLS_WIFI_L2                 100   /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_HLS_WIFI_L3                 101   /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_HLS_WIFI_L4                 102   /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_HLS_WIFI_L5                 103   /**< @brief  is deprecated and will be removed in Codec SDK version 11.0 @hideinitializer */
#define H264_P2_2K_INTRA_422             104   /**< @brief  Panasonic 2K Intra 4:2:2 Profile*/
#define H264_P2_4K_INTRA_422             105   /**< @brief  Panasonic 4K Intra 4:2:2 Profile*/
#define H264_P2_HD_INTRA_422             106   /**< @brief  Panasonic HD Intra 4:2:2 Profile*/
#define H264_HLS_L1                      119   /**< @brief  HTTP Live Streaming over cellular network                     Level 1:   200kb @hideinitializer */
#define H264_HLS_L2                      120   /**< @brief  HTTP Live Streaming over cellular network/ATV                 Level 2:   400kb @hideinitializer */
#define H264_HLS_L3                      121   /**< @brief  HTTP Live Streaming over Wi-Fi network/ cellular network/ ATV Level 3:   800kb @hideinitializer */
#define H264_HLS_L4                      122   /**< @brief  HTTP Live Streaming over Wi-Fi network/ cellular network/ ATV Level 4:  1200kb @hideinitializer */
#define H264_HLS_L5                      123   /**< @brief  HTTP Live Streaming over Wi-Fi network/ ATV                   Level 5:  2200kb @hideinitializer */
#define H264_HLS_L6                      124   /**< @brief  HTTP Live Streaming over Wi-Fi network/ ATV                   Level 6:  3300kb @hideinitializer */
#define H264_HLS_L7                      125   /**< @brief  HTTP Live Streaming over Wi-Fi network/ ATV                   Level 7:  5000kb @hideinitializer */
#define H264_HLS_L8                      126   /**< @brief  HTTP Live Streaming over Wi-Fi network/ ATV                   Level 8:  6500kb @hideinitializer */
#define H264_HLS_L9                      127   /**< @brief  HTTP Live Streaming over Wi-Fi network/ ATV                   Level 9:  8600kb @hideinitializer */

#define H264_LAST_H264_TYPE              131   /**< @brief  @hideinitializer */
/** @}*/

/**
@def SETTINGS_UNKNOWN_PARAMETERS
@name h264OutVideoDefaultSettings unknown parameters
@{
**/
#define H264_UNDEFINED_PIC_STRUCT                          -1   /**< @brief  undefined picture structure @hideinitializer */
#define H264_UNDEFINED_FRAME_WIDTH                          0   /**< @brief  undefined frame width @hideinitializer */
#define H264_UNDEFINED_FRAME_HEIGHT                         0   /**< @brief  undefined frame height@hideinitializer */
#define H264_UNDEFINED_FPS                                  0   /**< @brief  undefined frame rate @hideinitializer */
/** @}*/

/**
@def VSCD_MODES
@name Scene change detection modes
@{
**/
#define VCSD_MODE_OFF        0        /**< @brief  no scene detection @hideinitializer */
#define VCSD_MODE_IDR        1        /**< @brief  set IDR on scene change @hideinitializer */
/** @}*/

/**
@def PULLDOWN_FLAGS
@name Pulldown flags
@{
**/
#define VIDEO_PULLDOWN_NONE  0        /**< @brief  no pulldown @hideinitializer */
#define VIDEO_PULLDOWN_23    1        /**< @brief  23.976/24 played as 29.97/30 @hideinitializer */
#define VIDEO_PULLDOWN_32    2        /**< @brief  23.976/24 played as 29.97/30 @hideinitializer **/
#define VIDEO_PULLDOWN_23_P  4        /**< @brief  23.976/24 played as 59.94/60 @hideinitializer */
#define VIDEO_PULLDOWN_32_P  5        /**< @brief  23.976/24 played as 59.94/60 @hideinitializer */
#define VIDEO_PULLDOWN_AUTO  6        /**< @brief  adaptive mode, use @ref OPT_EXT_PARAM_DISPLAY_MODE to specify display mode for every frame @hideinitializer */
#define VIDEO_PULLDOWN_22    7        /**< @brief  every frame is displayed twice @hideinitializer */
#define VIDEO_PULLDOWN_33    8        /**< @brief  every frame is displayed three times @hideinitializer */
/** @}*/

/**
@def H264_PROFILE_TYPES
@name Profile type defines
@{
**/
#define H264PROFILE_BASELINE                                0   /**< @brief  Baseline Profile @hideinitializer */
#define H264PROFILE_MAIN                                    1   /**< @brief  Main Profile @hideinitializer */
#define H264PROFILE_EXTENDED                                2   /**< @brief  Extended Profile (not supported by now) @hideinitializer */
#define H264PROFILE_HIGH                                    3   /**< @brief  High Profile @hideinitializer */
#define H264PROFILE_HIGH_10                                 4   /**< @brief  High 10 Profile @hideinitializer */
#define H264PROFILE_HIGH_422                                5   /**< @brief  High 4:2:2 Profile @hideinitializer */
#define H264PROFILE_HIGH_444                                6   /**< @brief  NOT USED FOR NOW @hideinitializer */
/** @}*/

/**
@def CHROMA_FORMATS
@name Chroma format defines
@{
**/
#define H264_CHROMA_400                                     1   /**< @brief   currently not supported @hideinitializer */
#define H264_CHROMA_420                                     2   /**< @brief   4:2:0 colour sampling @hideinitializer */
#define H264_CHROMA_422                                     3   /**< @brief   4:2:2 colour sampling @hideinitializer */
#define H264_CHROMA_444                                     4   /**< @brief   4:4:4 colour sampling @hideinitializer */
/** @}*/

/**
@def STREAM_TYPES
@name Stream types defines
@{
**/
#define H264_STREAM_TYPE_I                                  0   /**< @brief  VCL NALUs + filler data @hideinitializer */
#define H264_STREAM_TYPE_I_SEI                              1   /**< @brief  VCL NALUs + filler data + SEI messages @hideinitializer */
#define H264_STREAM_TYPE_II                                 2   /**< @brief  all NALU types @hideinitializer */
#define H264_STREAM_TYPE_II_NO_SEI                          3   /**< @brief  all NALU types except SEI @hideinitializer */
/** @}*/

/**
@def VUI_CONFIG
@name VUI configuration flags
@{
**/
#define H264_VUI_PRESENTATION_AUTO                 0x00000000   /**< @brief 0x000 - Configures the video usability information appearing in the SPS header automatically (depending on the other encoder settings)  @hideinitializer */
#define H264_VUI_PRESENTATION_CUSTOMIZE            0x00000001   /**< @brief 0x001 - Enable combination of the following flags for configure the video usability information appearing in the SPS header@hideinitializer */
#define H264_VUI_ASPECT_RATIO_INFO_PRESENT_FLAG    0x00000002   /**< @brief 0x002 - aspect_ratio_info_present_flag @hideinitializer */
#define H264_VUI_OVERSCAN_INFO_PRESENT_FLAG        0x00000004   /**< @brief 0x004 - overscan_info_present_flag @hideinitializer */
#define H264_VUI_VIDEO_SIGNAL_TYPE_PRESENT_FLAG    0x00000008   /**< @brief 0x008 - video_signal_type_present_flag @hideinitializer */
#define H264_VUI_COLOUR_DESCRIPTION_PRESENT_FLAG   0x00000010   /**< @brief 0x010 - colour_description_present_flag (video_signal_type_present_flag should be enabled as well) @hideinitializer */
#define H264_VUI_CHROMA_LOC_INFO_PRESENT_FLAG      0x00000020   /**< @brief 0x020 - chroma_loc_info_present_flag (not supported) @hideinitializer */
#define H264_VUI_TIMING_INFO_PRESENT_FLAG          0x00000040   /**< @brief 0x040 - timing_info_present_flag @hideinitializer */
#define H264_VUI_NAL_HRD_PARAMETERS_PRESENT_FLAG   0x00000080   /**< @brief 0x080 - nal_hrd_parameters_present_flag @hideinitializer */
#define H264_VUI_VCL_HRD_PARAMETERS_PRESENT_FLAG   0x00000100   /**< @brief 0x100 - vcl_hrd_parameters_present_flag @hideinitializer */
#define H264_VUI_PIC_STRUCT_PRESENT_FLAG           0x00000200   /**< @brief 0x200 - pic_struct_present_flag @hideinitializer */
#define H264_VUI_BISTREAM_RESTRICTION_FLAG         0x00000400   /**< @brief 0x400 - bitstream_restriction_flag @hideinitializer */
/** @}*/

/**
@def VIDEO_STANDARDS
@name Video standard defines
@{
**/
#define H264_NTSC                                           0   /**< @brief   NTSC format @hideinitializer */
#define H264_PAL                                            1   /**< @brief   PAL format @hideinitializer */
/** @}*/

/**
@def VIDEO_FORMATS
@name Video format defines
@{
**/
#define H264_VF_AUTO                                        -1   /**< @brief   @hideinitializer */
#define H264_VF_COMPONENT                                   0   /**< @brief   @hideinitializer */
#define H264_VF_PAL                                         1   /**< @brief   @hideinitializer */
#define H264_VF_NTSC                                        2   /**< @brief   @hideinitializer */
#define H264_VF_SECAM                                       3   /**< @brief   @hideinitializer */
#define H264_VF_MAC                                         4   /**< @brief   @hideinitializer */
#define H264_VF_UNSPECIFIED                                 5   /**< @brief   @hideinitializer */
/** @}*/

/**
@def INTERLACED_MODES
@name Interlaced mode defines
@{
**/
#define H264_PROGRESSIVE                                    0   /**< @brief  progressive @hideinitializer */
#define H264_INTERLACED                                     1   /**< @brief  interlaced - encode every frame as 2 field pictures @hideinitializer */
#define H264_MBAFF                                          2   /**< @brief  interlaced - macroblock-adaptive frame-field coding @hideinitializer */
/** @}*/


/**
@def FIELD_ORDER
@name Field order defines
**/
#define H264_TOPFIELD_FIRST                                 0   /**< @brief   @hideinitializer */
#define H264_BOTTOMFIELD_FIRST                              1   /**< @brief   @hideinitializer */
/** @}*/

/**
@def RATE_CONTROL_MODES
@name Bit rate control mode defines
**/
#define H264_CBR                                            0   /**< @brief  Constant bit rate @hideinitializer */
#define H264_CQT                                            1   /**< @brief  Constant quantization @hideinitializer */
#define H264_VBR                                            2   /**< @brief  Variable bit rate @hideinitializer */
#define H264_TQM                                            3   /**< @brief  Target quality mode @hideinitializer */
#define H264_INTRARC                                        4   /**< @brief  Special mode for Intra-only presets @hideinitializer */
/** @}*/

/**
@def HRD_BUFFER_UNITS
@name HRD buffer units defines
@{
**/
#define H264_HRD_UNIT_BYTE_PERCENT                          0   /**< @brief   @hideinitializer */
#define H264_HRD_UNIT_BIT                                   1   /**< @brief   @hideinitializer */
#define H264_HRD_UNIT_BIT_90K                               2   /**< @brief   @hideinitializer */
/** @}*/

/**
@def ADAPTIVE_QUANTIZATION_MODES
@name Adaptive quantization mode defines
@{
**/
#define H264_AQUANT_MODE_BRIGHTNESS                         0   /**< @brief   @hideinitializer */
#define H264_AQUANT_MODE_CONTRAST                           1   /**< @brief   @hideinitializer */
#define H264_AQUANT_MODE_COMPLEXITY                         2   /**< @brief   @hideinitializer */
/** @}*/

/**
@def VBV_UNITS
@name VBV units defines
@{
**/
#define H264_VBV_Units_Percents                             0   /**< @brief   @hideinitializer */
#define H264_VBV_Units_Bits                                 1   /**< @brief   @hideinitializer */
#define H264_VBV_Units_Time                                 2   /**< @brief   @hideinitializer */
/** @}*/

/**
@def ENTROPY_CODING
@name Entropy coding mode defines
@{
**/
#define H264_CAVLC                                          0 /**< @brief  Contex-adaptive variable-length coding @hideinitializer */
#define H264_CABAC                                          1 /**< @brief  Contex-adaptive binary arithmetic coding @hideinitializer */
/** @}*/

/**
@def CPU_TYPE
@name CPU type defines
@{
**/
#define H264_CPU_OPT_AUTO                                   0   /**< @brief   @hideinitializer */
#define H264_CPU_OPT_UNKNOWN                                1   /**< @brief   @hideinitializer */
#define H264_CPU_OPT_MMX                                    2   /**< @brief   @hideinitializer */
#define H264_CPU_OPT_MMX_EXT                                3   /**< @brief   @hideinitializer */
#define H264_CPU_OPT_SSE                                    4   /**< @brief   @hideinitializer */
#define H264_CPU_OPT_SSE2                                   5   /**< @brief   @hideinitializer */
#define H264_CPU_OPT_SSE3                                   6   /**< @brief   @hideinitializer */
#define H264_CPU_OPT_SSE4                                   7   /**< @brief   @hideinitializer */
#define H264_CPU_OPT_AVX                                    8   /**< @brief   @hideinitializer */
#define H264_CPU_OPT_AVX2                                   9   /**< @brief   @hideinitializer */
/** @}*/

/**
@def INTER_SEARCH
@name Inter search defines
@{
**/
#define H264_INTERSEARCH_16x16  0   /**< @brief   @hideinitializer */
#define H264_INTERSEARCH_8x8    1   /**< @brief   @hideinitializer */
/** @}*/

/**
@def SUBPEL
@name Subpixel mode defines
@{
**/
#define H264_FULL_PEL           0                             /**< @brief  only full pixel position will be examined @hideinitializer */
#define H264_HALF_PEL           1                             /**< @brief  half-pixels positions will be added to the search @hideinitializer */
#define H264_QUARTER_PEL        2                             /**< @brief  both half and quarter pixel positions will be added @hideinitializer */
#define H264_QUARTER_PEL_ON_REF 3                             /**< @brief  both half and quarter pixel positions will be added for reference pictures, no quarter pixel positions for non-reference pictures @hideinitializer */

/** @}*/

/**
@def TIME_STAMP
@name Time stamp
@{
**/
#define H264_TIMESTAMP_100NS    0                             /**< @brief  DirectShow style, 100 ns units (10 Mhz clock) @hideinitializer */
#define H264_TIMESTAMP_27MHZ    1                             /**< @brief  MPEG style, 27 Mhz clock @hideinitializer */
/** @}*/

/**
@def DISPLAY_MODE
@name Display mode defines
**/
#define H264_DISPLAY_FRAME      0                             /**< @brief  display as progressive frame @hideinitializer */
#define H264_DISPLAY_TF         1                             /**< @brief  top field @hideinitializer */
#define H264_DISPLAY_BF         2                             /**< @brief  bottom field @hideinitializer */
#define H264_DISPLAY_TF_BF      3                             /**< @brief  top field, bottom field @hideinitializer */
#define H264_DISPLAY_BF_TF      4                             /**< @brief  bottom field, top field @hideinitializer */
#define H264_DISPLAY_TF_BF_TF   5                             /**< @brief  top field, bottom field, top field @hideinitializer */
#define H264_DISPLAY_BF_TF_BF   6                             /**< @brief  bottom field, top field, bottom field @hideinitializer */
#define H264_DISPLAY_DOUBLE     7                             /**< @brief  display frame twice @hideinitializer */
#define H264_DISPLAY_TRIPLE     8                             /**< @brief  display frame three times @hideinitializer */
/** @}*/

/**
@def USER_DATA_TYPES
@name User data type defines (h264_user_data_tt's type)
@{
**/
#define H264_UD_REGISTERED      1                             /**< @brief  user data registered by ITU-T Rec. T.35 SEI message @hideinitializer */
#define H264_UD_UNREGISTERED    2                             /**< @brief  user data unregistered SEI message @hideinitializer */
/** @}*/

/**
@def AIR_MODES
@name Adaptive intra refresh modes
@{
**/
#define H264_AIR_OFF            0                             /**< @brief  do not use AIR (default) @hideinitializer */
#define H264_AIR_SLOW           1                             /**< @brief  1 (SD) or 2 (HD) rows of intra macroblocks in every P frame @hideinitializer */
#define H264_AIR_MEDIUM         2                             /**< @brief  2 (SD) or 4 (HD) rows of intra macroblocks in every P frame @hideinitializer */
#define H264_AIR_FAST           3                             /**< @brief  3 (SD) or 6 (HD) rows of intra macroblocks in every P frame @hideinitializer */
#define H264_AIR_SPLIT          4                             /**< @brief Adjust intra_line_offset for this mode  @hideinitializer */
/** @}*/

/**
@def ME_SEARCH_MODES
@name Motion search algorithms
@{
**/
#define H264_DIAMOND          0                             /**< @brief Diamond shaped search algorithm with 9 points to check @hideinitializer */
#define H264_HEX_HORZ         1                             /**< @brief Thick horizontal hexagonal motion search algorithm, 7 points to check @hideinitializer */
#define H264_HEX_HORZ_FLAT    2                             /**< @brief Flat horizontal hexagonal motion search algorithm, 7 points to check @hideinitializer */
#define H264_HEX_VERT         3                             /**< @brief Thick vertical hexagonal motion search algorithm, 7 points to check @hideinitializer */
#define H264_HEX_VERT_FLAT    4                             /**< @brief Flat vertical hexagonal motion search algorithm, 7 points to check @hideinitializer */
/** @}*/

////////// defines for h264 conformance check

/**
@def CHK_OPTIONS
@name Options for the XXXChkSettings functions
@{
**/
#define H264_CHECK_AND_ADJUST   0x00000001   /**< @brief   @hideinitializer */
#define H264_CHECK_FOR_LEVEL    0x00000002   /**< @brief   @hideinitializer */
#define H264_CHECK_GET_MEMSIZE  0x00000004   /**< @brief   @hideinitializer */
/** @}*/

/**
* @name Deinterlacing modes
* Possible values of @ref h264_v_settings::deinterlacing_mode field
* @{
*/
#define H264_DEINTERLACE_NONE            0 /**<@brief Disable deinterlacing @hideinitializer*/
#define H264_DEINTERLACE_ON              1 /**<@brief Enable deinterlacing @hideinitializer*/
#define H264_DEINTERLACE_AUTO            1 /**<@brief Enable deinterlacing use first field interpolate the other @hideinitializer*/
#define H264_DEINTERLACE_USETOPFIELD     2 /**<@brief Enable deinterlacing use top field @hideinitializer*/
#define H264_DEINTERLACE_USEBOTTOMFIELD  3 /**<@brief Enable deinterlacing use bottom field @hideinitializer*/
#define H264_DEINTERLACE_USEBOTHFIELDS   4 /**<@brief Enable deinterlacing blend fields @hideinitializer*/
/**@}*/

/**
@def PERFORMANCE_OPTIONS
@name Options for the h264OutVideoPerformance function
@{
**/
#define H264_PERF_FASTEST       0                             /**< @brief  fastest @hideinitializer */
#define H264_PERF_BALANCED      9                             /**< @brief  recommended default value @hideinitializer */
#define H264_PERF_BEST_Q        15                            /**< @brief  best quality @hideinitializer */
/** @}*/

// options for the h264CudaOutVideoPerformance function
#define H264_GPU_PERF_FASTEST   0
#define H264_GPU_PERF_FAST      4
#define H264_GPU_PERF_QUALITY   8
#define H264_GPU_PERF_BEST_Q    12

/**
@def FPAM_MODES
@name Defines for Frame packing arrangement mode definition
@{
**/
#define H264_FPAM_DONT_WRITE            0                   /**< @brief Don`t write frame packing arrangement SEI messages @hideinitializer */
#define H264_FPAM_CHECKBOARD            1                   /**< @brief Checkboard @hideinitializer */
#define H264_FPAM_COLUMN_INTERLEAVING   2                   /**< @brief Column based interleaving @hideinitializer */
#define H264_FPAM_ROW_INTERLEAVING      3                   /**< @brief Row based interleaving @hideinitializer */
#define H264_FPAM_SIDE_BY_SIDE          4                   /**< @brief Side-by-Side packing arrangement @hideinitializer */
#define H264_FPAM_TOP_BOTTOM            5                   /**< @brief Top-Bottom packing arrangement @hideinitializer */
/** @}*/

/**
@def PRODUCT_INFO
@name Defines for Stream creation product info
**/
#define H264_NO_MESSAGE_IN_SEI          0                  /**< @brief  @hideinitializer */
#define H264_LL_MESSAGE_IN_SEI          1                  /**< @brief  @hideinitializer */
#define H264_DS_MESSAGE_IN_SEI          2                  /**< @brief  @hideinitializer */

/** @}*/

/**
@def ERRORS
@name ERROR_defines. Error codes for new API settings is to added to the end of this list.
@{
**/
////////// general
#define H264ERROR_NONE                                  0   /**< @brief   @hideinitializer No error*/
#define H264ERROR_FAILED                                1   /**< @brief   @hideinitializer General error*/
#define H264ERROR_NOT_SUPPORTED                         2   /**< @brief   @hideinitializer Attempt to use an unsupported function*/
#define H264ERROR_PARAM_UNKNOWN                         3   /**< @brief   @hideinitializer Unknown parameter*/
#define H264ERROR_PARAM_ADJUSTED                        4   /**< @brief   @hideinitializer Parameter adjusted by validator*/
#define H264ERROR_AVC_INTRA_SKIPPED_FRAME               5   /**< @brief   @hideinitializer */

// h264_v_settings_tt error codes
typedef enum param_set_errors_e
{
    Error_param_set  = 0,
    Error_profile_id = 1,
    Error_level_id,
    Error_idr_interval,
    Error_reordering_delay,
    Error_interlace_mode,
    Error_def_horizontal_size,
    Error_def_vertical_size,
    Error_frame_rate,
    Error_num_reference_frames,
    Error_search_range,
    Error_rd_optimization,
    Error_max_l0_active,
    Error_max_l1_active,
    Error_quant_pI,
    Error_quant_pP,
    Error_quant_pB,
    Error_bit_rate_mode,
    Error_bit_rate_buffer_size,
    Error_bit_rate,
    Error_max_bit_rate,
    Error_inter_search_shape,
    Error_entropy_coding_mode,
    Error_use_hadamard_transform,
    Error_sar_width,
    Error_sar_height,
    Error_video_format,
    Error_video_full_range,
    Error_num_units_in_tick,
    Error_time_scale,
    Error_vbv_fullness,
    Error_vbv_fullness_trg,
    Error_vbv_units,
    Error_cpb_removal_delay,
    Error_br_scale,
    Error_cpb_size_scale,
    Error_max_frame_size,
    Error_hrd_maintain,
    Error_min_frame_size,
    Error_hrd_low_delay,
    Error_smooth_factor,
    Error_hrd_preview,
    Error_use_deblocking_filter,
    Error_deblocking_alphac0_offset,
    Error_deblocking_beta_offset,
    Error_adaptive_deblocking,
    Error_video_type,
    Error_video_pulldown,
    Error_overscan_appropriate_flag,
    Error_colour_primaries,
    Error_transfer_characteristics,
    Error_matrix_coefficients,
    Error_extended_sar,
    Error_stream_type,
    Error_bit_depth_luma,
    Error_bit_depth_chroma,
    Error_chroma_format,
    Error_pic_init_qp,
    Error_pic_init_qs,
    Error_vui_presentation,
    Error_write_au_delimiters,
    Error_write_seq_end_code,
    Error_write_timestamps,
    Error_timestamp_offset,
    Error_drop_frame_timecode,
    Error_write_single_sei_per_nalu,
    Error_write_seq_par_set,
    Error_write_pic_par_set,
    Error_log2_max_poc,
    Error_log2_max_frame_num,
    Error_pic_order_cnt_type,
    Error_pic_order_present_flag,
    Error_fixed_frame_rate,
    Error_frame_based_timing,
    Error_frame_packing_arrangement,
    Error_stream_creation_product_info,
    Error_write_pic_timing_sei,
    Error_write_settings_info,
    Error_frame_num_gaps_allowed_flag,
    Error_vcsd_mode,
    Error_slice_mode,
    Error_slice_arg,
    Error_b_slice_ref,
    Error_b_slice_pyramid,
    Error_cb_offset,
    Error_cr_offset,
    Error_subpel_mode,
    Error_weighted_p_mode,
    Error_weighted_b_mode,
    Error_fast_intra,
    Error_fast_inter,
    Error_pic_ar_x,
    Error_pic_ar_y,
    Error_calc_quality,
    Error_cpu_opt,
    Error_num_threads,
    Error_live_modeE,
    Error_buffering,
    Error_max_quant,
    Error_min_quant,
    Error_max_slice_size,
    Error_encoding_buffering,
    Error_air_mode,
    Error_detach_thread,
    Error_constrained_intra_pred,
    Error_air_split_frequency,
    Error_air_qp_offset,
    Error_convert_pixel_range,
    Error_deinterlacing_mode,
    Error_min_idr_interval,
    Error_adaptive_b_frames,
    Error_idr_frequency,
    Error_field_order,
    Error_fixed_i_position,
    Error_isolated_gops,
    Error_leading_b,
    Error_fast_multi_ref_me,
    Error_fast_sub_block_me,
    Error_allow_out_of_pic_mvs,
    Error_constrained_ref_list,
    Error_enable_intra_big,
    Error_enable_intra_8x8,
    Error_enable_intra_4x4,
    Error_enable_intra_pcm,
    Error_enable_inter_big,
    Error_enable_inter_8x8,
    Error_enable_inter_4x4,
    Error_enable_inter_pcm,
    Error_fast_rd_optimization,
    Error_quant_mode,
    Error_grain_mode,
    Error_grain_opt_strength,
    Error_adaptive_quant_strength,
    Error_denoise_strength_y,
    Error_black_norm_level,
    Error_denoise_strength_c,
    Error_pulse_reduction,
    Error_aux_format_idc,
    Error_bit_depth_aux,
    Error_alpha_incr_flag,
    Error_alpha_opaque_value,
    Error_alpha_transparent_value,
    Error_seq_scaling_matrix_present_flag,
    Error_seq_scaling_list_present_flag,
    Error_intra_y_4x4_scaling_list,
    Error_intra_cb_4x4_scaling_list,
    Error_intra_cr_4x4_scaling_list,
    Error_inter_y_4x4_scaling_list,
    Error_inter_cb_4x4_scaling_list,
    Error_inter_cr_4x4_scaling_list,
    Error_intra_y_8x8_scaling_list,
    Error_inter_y_8x8_scaling_list,
    Error_num_parallel_pics,
    Error_enable_fast_intra_decisions,
    Error_enable_fast_inter_decisions,
    Error_crop_params,
    Error_motion_search_pattern,
    Error_param_set_last
} param_set_errors_t;

// Table A1 Error codes
typedef enum table_a1_error_e
{
    Level_err_table_a1     = 0, /**< @brief @hideinitializer */
    Level_err_mb_proc_rate = 1, /**< @brief @hideinitializer */
    Level_err_frame_size,
    Level_err_dpb,
    Level_err_br,
    Level_err_cpb,
    Level_err_search_range
} table_a1_error_t;


// Primary check errors
typedef enum primary_check_errors_e
{
    Primary_check_error = 0,  /**< @brief @hideinitializer */
    Invalid_picture_mode = 1, /**< @brief @hideinitializer */
    Invalid_resolution,
    Invalid_frame_rate
}primary_check_errors_t;


/*
*  Flags to disable certain 4x4 intra prediction modes. DC mode cannot be disabled.
*/
#define H264_4x4_ENABLED      0x00000001 /**<@brief Enable 4x4 intra prediction modes usage */
#define H264_DISABLE_4x4_V    0x00000002 /**<@brief Disable vertical 4x4 intra prediction mode */
#define H264_DISABLE_4x4_H    0x00000004 /**<@brief Disable horizontal 4x4 intra prediction mode */
#define H264_DISABLE_4x4_DDL  0x00000010 /**<@brief Disable diagonal down left 4x4 intra prediction mode */
#define H264_DISABLE_4x4_DDR  0x00000020 /**<@brief Disable diagonal down right 4x4 intra prediction mode */
#define H264_DISABLE_4x4_VR   0x00000040 /**<@brief Disable vertical right 4x4 intra prediction mode */
#define H264_DISABLE_4x4_HD   0x00000080 /**<@brief Disable horizontal down 4x4 intra prediction mode */
#define H264_DISABLE_4x4_VL   0x00000100 /**<@brief Disable vertical left 4x4 intra prediction mode */
#define H264_DISABLE_4x4_HU   0x00000200 /**<@brief Disable horizontal up 4x4 intra prediction mode */

/*
*  Flags to disable certain 8x8 intra prediction modes. DC mode cannot be disabled.
*/
#define H264_8x8_ENABLED      0x00000001 /**<@brief Enable 8x8 intra prediction modes usage */
#define H264_DISABLE_8x8_V    0x00000002 /**<@brief Disable vertical 8x8 intra prediction mode */
#define H264_DISABLE_8x8_H    0x00000004 /**<@brief Disable horizontal 8x8 intra prediction mode */
#define H264_DISABLE_8x8_DDL  0x00000010 /**<@brief Disable diagonal down left 8x8 intra prediction mode */
#define H264_DISABLE_8x8_DDR  0x00000020 /**<@brief Disable diagonal down right 8x8 intra prediction mode */
#define H264_DISABLE_8x8_VR   0x00000040 /**<@brief Disable vertical right 8x8 intra prediction mode */
#define H264_DISABLE_8x8_HD   0x00000080 /**<@brief Disable horizontal down 8x8 intra prediction mode */
#define H264_DISABLE_8x8_VL   0x00000100 /**<@brief Disable vertical left 8x8 intra prediction mode */
#define H264_DISABLE_8x8_HU   0x00000200 /**<@brief Disable horizontal up 8x8 intra prediction mode */

/*
*  Flags to disable certain 16x16 intra prediction modes. DC mode cannot be disabled.
*/

#define H264_16x16_ENABLED    0x00000001 /**<@brief Enable 16x16 intra prediction modes usage */
#define H264_DISABLE_16x16_V  0x00000002 /**<@brief Disable vertical 16x16 intra prediction mode */
#define H264_DISABLE_16x16_H  0x00000004 /**<@brief Disable horizontal 16x16 intra prediction mode */
#define H264_DISABLE_16x16_P  0x00000010 /**<@brief Disable plane 16x16 intra prediction mode */

#endif // #if !defined (__ENC_AVC_DEF_INCLUDED__)

