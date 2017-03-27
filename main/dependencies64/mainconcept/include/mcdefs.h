/**
 @file  mcdefs.h
 @brief definitions and constants for different codecs

 @verbatim
 File: mcdefs.h
 Desc: definitions and constants for different codecs

 Copyright (c) 2015 MainConcept GmbH or its affiliates.  All rights reserved.

 MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.  
 This software is protected by copyright law and international treaties.  Unauthorized 
 reproduction or distribution of any portion is prohibited by law.
 @endverbatim
 **/

#if !defined (__MC_DEFS_INCLUDED__)
#define __MC_DEFS_INCLUDED__

#include "mctypes.h"


/**
 * @name Maximum GOP size limits
 * @{
 **/
#define MAXM               8      ///< Max distance between I/P frames
#define MAXN             128      ///< Max number of frames in Group of Pictures
/** @} */

/**
 * @name MPEG Video types
 * Possible values of @ref mpeg_v_settings::video_type variable
 * @{
 **/
#define MPEG_MPEG1                 0       ///< generic ISO/IEC 11172-1/2
#define MPEG_VCD                   1       ///< MPEG-1 VideoCD
#define MPEG_MPEG2                 2       ///< generic ISO/IEC 13818-1/2
#define MPEG_SVCD                  3       ///< MPEG-2 SuperVCD
#define MPEG_DVD                   4       ///< MPEG-2 DVD-Video
#define MPEG_TS                    5       ///< generic MPEG-2 transport stream, PAT and PMT only
#define MPEG_PVA                   6       ///< PVA stream type, strictly for decoding, do not use for encoding
#define MPEG_NONE                  7       ///< indicates no muxing
#define MPEG_DVB                   8       ///< DVB
#define MPEG_MMV                   9       ///< MPEG-2 MICROMV
#define MPEG_DVHS                  10      ///< DVHS
#define MPEG_ATSC                  11      ///< MPEG-2 ATSC Terrestrial
#define MPEG_ATSCHI                12      ///< MPEG-2 ATSC Terrestrial (high data rate)
#define MPEG_DVD_MPEG1             13      ///< MPEG-1 DVD-Video
#define MPEG_DVD_DVR               14      ///< MPEG-2 DVD-VR
#define MPEG_DVD_DVR_MPEG1         15      ///< MPEG-1 DVD-VR
#define MPEG_DVD_PVR               16      ///< MPEG-2 DVD+VR, not yet implemented!
#define MPEG_DVD_PVR_MPEG1         17      ///< MPEG-1 DVD+VR, not yet implemented!
#define MPEG_HDV_HD1               18      ///< MPEG-2 HDV HD1
#define MPEG_HDV_HD2               19      ///< MPEG-2 HDV HD2
#define MPEG_D10_25                20      ///< D-10 MPEG-2 4:2:2P @ ML (25 MBit)
#define MPEG_D10_30                21      ///< D-10 MPEG-2 4:2:2P @ ML (30 MBit)
#define MPEG_D10_40                22      ///< D-10 MPEG-2 4:2:2P @ ML (40 MBit)
#define MPEG_D10_50                23      ///< D-10 MPEG-2 4:2:2P @ ML (50 MBit)
#define MPEG_CABLELABS             24      ///< CableLabs MPEG-2 MP @ ML (3.18MBit) or MP @ HL (18.1MBit)
#define MPEG_HD_DVD                25      ///< HD DVD
#define MPEG_BD                    26      ///< Blu Ray Disc
#define MPEG_BD_HDMV               27      ///< Blu Ray Disc (Main Video)
#define MPEG_XDCAM_IMX             28      ///< XDCAM IMX
#define MPEG_XDCAM_IMX_25          28      ///< XDCAM IMX MPEG-2 4:2:2P @ ML (25 MBit)
#define MPEG_XDCAM_IMX_30          29      ///< XDCAM IMX MPEG-2 4:2:2P @ ML (30 MBit)
#define MPEG_XDCAM_IMX_40          30      ///< XDCAM IMX MPEG-2 4:2:2P @ ML (40 MBit)
#define MPEG_XDCAM_IMX_50          31      ///< XDCAM IMX MPEG-2 4:2:2P @ ML (50 MBit)
#define MPEG_XDCAM_HD              32      ///< XDCAM HD
#define MPEG_XDCAM_1080_CBR_25     32      ///< XDCAM HD MP \@ H-14 4:2:0 1440x1080 (25 Mbit CBR)
#define MPEG_XDCAM_1080_VBR_17_5   33      ///< XDCAM HD MP \@ HL   4:2:0 1440x1080 (17.5 Mbit VBR)
#define MPEG_XDCAM_1080_VBR_35     34      ///< XDCAM HD MP \@ HL   4:2:0 1440x1080 (35 Mbit VBR)
#define MPEG_XDCAM_540_CBR_12_5    35      ///< XDCAM HD MP \@ H-14 4:2:0 1440x540  (12.5 Mbit CBR)
#define MPEG_XDCAM_540_VBR_8_75    36      ///< XDCAM HD MP \@ HL   4:2:0 1440x540  (8.75 Mbit VBR)
#define MPEG_XDCAM_540_VBR_17_5    37      ///< XDCAM HD MP \@ HL   4:2:0 1440x540  (17.5 Mbit VBR)
#define MPEG_XDCAM_HD_420_1280     38      ///< XDCAM HD MP \@ HL   4:2:0 1280x720  (35 Mbit VBR)
#define MPEG_XDCAM_HD_422_1920     39      ///< XDCAM HD 422P \@ HL 4:2:2 1920x1080 (50 Mbit CBR)
#define MPEG_XDCAM_HD_422_1280     40      ///< XDCAM HD 422P \@ HL 4:2:2 1280x720  (50 Mbit CBR)
#define MPEG_XDCAM_EX              41      ///< XDCAM EX
#define MPEG_XDCAM_EX_1920         41      ///< XDCAM EX MP \@ HL   4:2:0 1920x1080 (35 Mbit VBR)
#define MPEG_XDCAM_EX_1440         42      ///< XDCAM EX MP \@ H-14 4:2:0 1440x1080 (25 Mbit CBR)
#define MPEG_XDCAM_EX_1280         43      ///< XDCAM EX MP \@ HL   4:2:0 1280x720  (35 Mbit VBR)
#define MPEG_AVCHD                 44      ///< AVCHD, muxer and pcm encoder type only!
#define MPEG_1SEG                  45      ///< OneSeg profile
#define MPEG_XDCAM_HD_422_1920_540 46      ///< XDCAM HD 422P \@ HL 4:2:2 1920x540  (25 Mbit CBR), used for slowmotion
#define MPEG_ATT                   47      ///< AT&T specs based on the generic ISO 13818-1 TS
#define MPEG_CABLELABS_HD1         48      ///< CableLabs MPEG-2 MP \@ HL 1280x720 (15MBit)
#define MPEG_CABLELABS_HD2         49      ///< CableLabs MPEG-2 MP \@ HL 1920x1080 (15MBit)
#define MPEG_ATSC_C                50      ///< MPEG-2 ATSC Cable
#define MPEG_DTV                   51      ///< Networked Digital Television
#define MPEG_HLS                   52      ///< HTTP Live Streaming muxer type
#define MPEG_LAST_MPEG_TYPE        52      ///< last MPEG type
/** @} */

/**
 * @name Audio types
 * @{
 **/
#define NO_AUDIO               0       ///<   no audio
#define MPEG_AUDIO_LAYER1      1       ///<    ISO/IEC 11172-3 layer 1
#define MPEG_AUDIO_LAYER2      2       ///<    ISO/IEC 11172-3 layer 2
#define MPEG_AUDIO_LAYER3      3       ///<    ISO/IEC 11172-3 layer 3
#define PCM_AUDIO              4       ///<    Depreciated, for compatibility only, means the same as DVD_LPCM_AUDIO
#define DVD_LPCM_AUDIO         4       ///<    DVD Linear PCM
#define AC3_AUDIO              5       ///<    Dolby digital
#define MPEG2_AAC_AUDIO        6       ///<    MPEG-2 AAC
#define MPEG4_AAC_AUDIO        7       ///<    MPEG-4 AAC
#define DTS_AUDIO              8       ///<    Digital Theater Sound
#define SDDS_AUDIO             9       ///<    Sony Dynamic Digital Sound
#define AES3_302M_AUDIO        10      ///<    AES3 PCM audio as per SMPTE 302M, MPEG-2 transport stream only
#define AES3_331M_AUDIO        11      ///<    AES3 PCM audio as per SMPTE 331M, MXF only
#define AES3_382M_AUDIO        12      ///<    AES3 PCM audio as per SMPTE 382M, MXF only
#define HDMV_LPCM_AUDIO        13      ///<    HDMV LPCM audio, Blu Ray and AVCHD
#define TWOS_LPCM_AUDIO        14      ///<    TWOS LPCM audio, Sony Professional Media Card
#define AMR_AUDIO              15      ///<    AMR audio
#define MPEG4_AAC_AUDIO_PSP    16      ///<    MPEG-4 AAC with Sony Play Station Portable restrictions
#define WMA_AUDIO              17      ///<    WMA audio
#define QT_PCM_AUDIO           18      ///<    QuickTime PCM audio
#define ALAW_AUDIO             19      ///<    A-law audio
#define AIFF_AUDIO             20      ///<    AIFF audio
#define STD_LPCM_AUDIO         21      ///<    Standard unformatted LPCM (big endian) audio
#define ULAW_AUDIO             22      ///<    MU-law audio
#define WAVE_ADPCM_AUDIO       23      ///<    WAVE style ADPCM audio, format tag 2
#define WAVE_IMA_ADPCM_AUDIO   24      ///<    WAVE style IMA ADPCM audio, format tag 17
/** @} */

// stream types reported by mpegin
#define STREAM_ELEMENTARY      0       // audio or video elementary stream
#define STREAM_MPEG1_PROGRAM   1       // mpeg-1 program stream
#define STREAM_MPEG2_PROGRAM   2       // mpeg-2 program stream
#define STREAM_MPEG2_TRANSPORT 3       // mpeg-2 transport stream
#define STREAM_PVA             4       // pva stream
#define STREAM_MXF_XDCAM_HD    5       // XDCAM HD MXF stream
#define STREAM_XDCAM_HD        5       // depreciated
#define STREAM_MXF_XDCAM_IMX   6       // XDCAM IMX MXF stream
#define STREAM_XDCAM_IMX       6       // depreciated
#define STREAM_MP4             7       // MP4 stream
#define STREAM_DMF             8       // DMF stream
#define STREAM_MXF_XDCAM_DV    9
#define STREAM_MXF_GENERIC     10
#define STREAM_MXF_IKEGAMI     11
#define STREAM_MXF_DV          16      // deprecaited
#define STREAM_MXF_JPEG2000    17      // deprecaited
#define STREAM_MXF_P2_DVCPRO   18
#define STREAM_MXF_P2_AVCI     19
#define STREAM_ASF             20      // ASF stream
#define STREAM_MXF_XDCAM_PROXY 21      // XDCAM proxy stream


/**
 * @name Options for the XXXChkSettings functions
 * @{
 **/
#define CHECK_MPEG_ONLY       0x00000001  ///< only do MPEG checks, do not check for VCD/SVCD/DVD compliance
#define CHECK_ALL             0x00000002  ///< do all checks, normally the check functions return after the first error found
/** @} */

/* default sector sizes */
#define VIDEOCD_SECTOR_SIZE   2324     // VideoCD sector size
#define SVCD_SECTOR_SIZE      2324     // Super VideoCD sector size
#define DVD_SECTOR_SIZE       2048     // DVD sector size
#define TS_SECTOR_SIZE        188      // transport stream sector size
#define MAX_SECTOR_SIZE       4096

/* VCD video bitrate */
#define MIN_VCD_VIDEO_BITRATE    1140000
#define MAX_VCD_VIDEO_BITRATE    1151929

/* maximum SVCD video bitrate, Note, this assumes no audio! */
/* If audio is used, subtract the audio bitrate from this   */
/* number, i.e. if the audio is 224 kbps, then the video    */
/* bitrate would be 2422848 bps (2646848 - 224000)          */
#define MAX_SVCD_VIDEO_BITRATE           2646848

/* maximum DVD video bitrate */
#define MAX_DVD_VIDEO_BITRATE            9800000

// maximum MicroMV video bitrate
#define MAX_MMV_VIDEO_BITRATE           12000000

// maximum ATSC video bitrate (normal)
#define MAX_ATSC_VIDEO_BITRATE          19400000

// maximum ATSC video bitrate (high data rate)
#define MAX_ATSC_HIGH_VIDEO_BITRATE     38800000

// maximum HDV HD1 NTSC video bitrate
#define MAX_HDV_HD1_NTSC_VIDEO_BITRATE  19830000

// maximum HDV HD1 PAL video bitrate
#define MAX_HDV_HD1_PAL_VIDEO_BITRATE   19850000

// maximum HDV HD2 video bitrate
#define MAX_HDV_HD2_VIDEO_BITRATE       25000000

// maximum CableLabs video SD bitrate
#define MAX_CABLELABS_VIDEO_SD_BITRATE   3180000

// maximum CableLabs video HD bitrate
#define MAX_CABLELABS_VIDEO_HD_BITRATE  18100000

/* minimum video bitrate */
#define MIN_VIDEO_BITRATE                 192000

/* maximum MPEG2 video bitrates based on profile/level */
/* high profile */
#define MAX_HP_HL_BITRATE              100000000  // high level
#define MAX_HP_H1440_BITRATE            80000000  // high 1440 level
#define MAX_HP_ML_BITRATE               20000000  // main level
#define MAX_HP_LL_BITRATE                      0  // low level, not allowed

/* main profile */
#define MAX_MP_HL_BITRATE               80000000  // high level
#define MAX_MP_H1440_BITRATE            60000000  // high 1440 level
#define MAX_MP_ML_BITRATE               15000000  // main level
#define MAX_MP_LL_BITRATE                4000000  // low level

/* simple profile */
#define MAX_SP_HL_BITRATE                      0  // high level, not allowed
#define MAX_SP_H1440_BITRATE                   0  // high 1440 level, not allowed
#define MAX_SP_ML_BITRATE               15000000  // main level
#define MAX_SP_LL_BITRATE                      0  // low level, not allowed

/* 4:2:2 profile */
#define MAX_422_HL_BITRATE             300000000  // high level
#define MAX_422_H1440_BITRATE                  0  // high 1440 level, not allowed
#define MAX_422_ML_BITRATE              50000000  // main level
#define MAX_422_LL_BITRATE                     0  // low level, not allowed

/* plain maximums for levels */
#define MAX_HIGH_LEVEL_BITRATE         300000000  // high level
#define MAX_HIGH_1440_BITRATE           80000000  // high 1440 level
#define MAX_MAIN_LEVEL_BITRATE          50000000  // main level
#define MAX_LOW_LEVEL_BITRATE            4000000  // low level

/* maximum MPEG1 video bitrates */
//#define MAX_MPEG1_VIDEO_BITRATE  104857200 // in theory, lower bitrates probably work much better
#define MAX_MPEG1_VIDEO_BITRATE  MAX_MP_ML_BITRATE    // MPEG-2 main profile/main level limit?

/* the maximum MPEG-1 constrained parameters bitrate */
#define MAX_MPEG1_CONSTR_BITRATE         1856000

/* mux rates in 50 byte/sec units */
#define VCD_MUX_RATE                 3528       //  1411200 bps
#define SVCD_MUX_RATE                6972       //  2788800 bps
#define DVD_MUX_RATE                25200       // 10080000 bps

#define MAX_DVB_SDTV_MUX_RATE       22500       //  9000000 bps
#define MAX_DVB_HDTV_MUX_RATE       70000       // 28000000 bps

#define MAX_ATSC_MUX_RATE           48481       // 19392400 bps
#define MAX_ATSC_MUX_RATE_BPS    19392658       // exact bitrate
#define MAX_ATSCHI_MUX_RATE         96963       // 38785200 bps
#define MAX_ATSCHI_MUX_RATE_BPS  38785316       // exact bitrate

#define MAX_HD1_NTSC_MUX_RATE       49575       // 19830000 bps
#define MAX_HD1_PAL_MUX_RATE        49625       // 19850000 bps
#define MAX_HD2_MUX_RATE            82500       // 33000000 bps

// for 1 video and 1 audio stream, if additional audio streams
// the maximum can be higher
#define MAX_CABLELABS_SD_MUX_RATE    9375       //  3750000 bps
#define MAX_CABLELABS_HD_MUX_RATE   47500       // 19000000 bps

/**
 * @name Framerates
 * Supported frame rates
 * @{
 **/
#define FRAMERATE0        0       ///< use default frame rate
#define FRAMERATE23       1       ///< 24000/1001       23.976 fps -- NTSC encapsulated film rate
#define FRAMERATE24       2       ///< 24               Standard international cinema film rate
#define FRAMERATE25       3       ///< 25               PAL (625/50) video frame rate
#define FRAMERATE29       4       ///< 30000/1001       29.97 -- NTSC video frame rate
#define FRAMERATE30       5       ///< 30               NTSC drop-frame (525/60) video frame rate
#define FRAMERATE50       6       ///< 50               double frame rate/progressive PAL
#define FRAMERATE59       7       ///< 60000/1001       double frame rate NTSC
#define FRAMERATE60       8       ///< 60               double frame rate drop-frame NTSC
#define FRAMERATE48       9       ///< 48.0 frames per second (DCI)
/** @} */

/* NTSC pulldown flags */
#define PULLDOWN_NONE        0
#define PULLDOWN_23          1    // 23.976/24 played as 29.97/30
#define PULLDOWN_32          2    // 23.976/24 played as 29.97/30
#define PULLDOWN_AUTO        3
#define PULLDOWN_23_PROGSEQ  4    // 23.976/24 played as 59.94/60
#define PULLDOWN_32_PROGSEQ  5    // 23.976/24 played as 59.94/60
/* PAL pulldown flags */
#define PULLDOWN_22          6    // 25 fps played as 50fps
#define PULLDOWN_22_PROGSEQ  7    // 25 fps played as 50fps

/* mux rate computation methods */
#define COMPBITRATE_NONE  0
#define COMPBITRATE_AVG   1
#define COMPBITRATE_MAX   2

/* muxer frame/timestamp combinations */
#define TIMESTAMPS_ALL    0
#define TIMESTAMPS_IPONLY 1
#define TIMESTAMPS_IONLY  2

/* profile IDs, not original MPEG standard value */
#define PROFILE_MULTIVIEW 8  // currently not supported
#define PROFILE_422       7
#define PROFILE_SIMPLE    5
#define PROFILE_MAIN      4
#define PROFILE_SNR       3  // currently not supported
#define PROFILE_SPAT      2  // currently not supported
#define PROFILE_HIGH      1

/* level IDs */
#define LEVEL_LOW         10
#define LEVEL_MAIN         8
#define LEVEL_HIGH1440     6
#define LEVEL_HIGH         4
#define LEVEL_UNSPECIFIED 15


/** \name video start codes 
 * @{
 */
#define PICTURE_START_CODE        0x100L	    /**< \brief  \hideinitializer  */
#define SLICE_MIN_START           0x101L	    /**< \brief  \hideinitializer  */
#define SLICE_MAX_START           0x1AFL	    /**< \brief  \hideinitializer  */
#define USER_START_CODE           0x1B2L	    /**< \brief  \hideinitializer  */
#define SEQ_START_CODE            0x1B3L	    /**< \brief  \hideinitializer  */
#define EXT_START_CODE            0x1B5L	    /**< \brief  \hideinitializer  */
#define SEQ_END_CODE              0x1B7L	    /**< \brief  \hideinitializer  */
#define GOP_START_CODE            0x1B8L	    /**< \brief  \hideinitializer  */
/** \} */

/* system start codes */
#define ISO_END_CODE              0x1B9L
#define PACK_START_CODE           0x1BAL
#define SYSTEM_START_CODE         0x1BBL

#define PROGRAM_STREAM_MAP        0x1BCL
#define PRIVATE_STREAM_1          0x1BDL
#define PADDING_STREAM            0x1BEL
#define PRIVATE_STREAM_2          0x1BFL

#define AUDIO_ELEMENTARY_STREAM   0x1C0L
#define AUDIO_ELEMENTARY_STREAM0  0x1C0L
#define AUDIO_ELEMENTARY_STREAM1  0x1C1L
#define AUDIO_ELEMENTARY_STREAM2  0x1C2L
#define AUDIO_ELEMENTARY_STREAM3  0x1C3L
#define AUDIO_ELEMENTARY_STREAM4  0x1C4L
#define AUDIO_ELEMENTARY_STREAM5  0x1C5L
#define AUDIO_ELEMENTARY_STREAM6  0x1C6L
#define AUDIO_ELEMENTARY_STREAM7  0x1C7L
#define AUDIO_ELEMENTARY_STREAM8  0x1C8L
#define AUDIO_ELEMENTARY_STREAM9  0x1C9L
#define AUDIO_ELEMENTARY_STREAM10 0x1CAL
#define AUDIO_ELEMENTARY_STREAM11 0x1CBL
#define AUDIO_ELEMENTARY_STREAM12 0x1CCL
#define AUDIO_ELEMENTARY_STREAM13 0x1CDL
#define AUDIO_ELEMENTARY_STREAM14 0x1CEL
#define AUDIO_ELEMENTARY_STREAM15 0x1CFL
#define AUDIO_ELEMENTARY_STREAM16 0x1D0L
#define AUDIO_ELEMENTARY_STREAM17 0x1D1L
#define AUDIO_ELEMENTARY_STREAM18 0x1D2L
#define AUDIO_ELEMENTARY_STREAM19 0x1D3L
#define AUDIO_ELEMENTARY_STREAM20 0x1D4L
#define AUDIO_ELEMENTARY_STREAM21 0x1D5L
#define AUDIO_ELEMENTARY_STREAM22 0x1D6L
#define AUDIO_ELEMENTARY_STREAM23 0x1D7L
#define AUDIO_ELEMENTARY_STREAM24 0x1D8L
#define AUDIO_ELEMENTARY_STREAM25 0x1D9L
#define AUDIO_ELEMENTARY_STREAM26 0x1DAL
#define AUDIO_ELEMENTARY_STREAM27 0x1DBL
#define AUDIO_ELEMENTARY_STREAM28 0x1DCL
#define AUDIO_ELEMENTARY_STREAM29 0x1DDL
#define AUDIO_ELEMENTARY_STREAM30 0x1DEL
#define AUDIO_ELEMENTARY_STREAM31 0x1DFL

#define VIDEO_ELEMENTARY_STREAM   0x1E0L
#define VIDEO_ELEMENTARY_STREAM0  0x1E0L
#define VIDEO_ELEMENTARY_STREAM1  0x1E1L
#define VIDEO_ELEMENTARY_STREAM2  0x1E2L
#define VIDEO_ELEMENTARY_STREAM3  0x1E3L
#define VIDEO_ELEMENTARY_STREAM4  0x1E4L
#define VIDEO_ELEMENTARY_STREAM5  0x1E5L
#define VIDEO_ELEMENTARY_STREAM6  0x1E6L
#define VIDEO_ELEMENTARY_STREAM7  0x1E7L
#define VIDEO_ELEMENTARY_STREAM8  0x1E8L
#define VIDEO_ELEMENTARY_STREAM9  0x1E9L
#define VIDEO_ELEMENTARY_STREAM10 0x1EAL
#define VIDEO_ELEMENTARY_STREAM11 0x1EBL
#define VIDEO_ELEMENTARY_STREAM12 0x1ECL
#define VIDEO_ELEMENTARY_STREAM13 0x1EDL
#define VIDEO_ELEMENTARY_STREAM14 0x1EEL
#define VIDEO_ELEMENTARY_STREAM15 0x1EFL

#define ECM_STREAM                0x1F0L
#define EMM_STREAM                0x1F1L
#define ITU_T_H2220_STREAM        0x1F2L
#define ISO_IEC_13522_STREAM      0x1F3L
#define ITU_T_H2221_TYPEA_STREAM  0x1F4L
#define ITU_T_H2221_TYPEB_STREAM  0x1F5L
#define ITU_T_H2221_TYPEC_STREAM  0x1F6L
#define ITU_T_H2221_TYPED_STREAM  0x1F7L
#define ITU_T_H2221_TYPEE_STREAM  0x1F8L
#define ANCILLARY_STREAM          0x1F9L

#define RESERVED_DATA_STREAM0     0x1FAL
#define RESERVED_DATA_STREAM1     0x1FBL
#define RESERVED_DATA_STREAM2     0x1FCL
#define RESERVED_DATA_STREAM3     0x1FDL
#define RESERVED_DATA_STREAM4     0x1FEL

#define PROGRAM_STREAM_DIRECTORY  0x1FFL
#define SYSTEM_START_CODE_MAX     0x1FFL

/* DVD substream defines */
#define PCI_NAVIGATION            0x00
#define DSI_NAVIGATION            0x01

/* subpicture streams */
#define SUBPICTURE_STREAM0        0x20
#define SUBPICTURE_STREAM1        0x21
#define SUBPICTURE_STREAM2        0x22
#define SUBPICTURE_STREAM3        0x23
#define SUBPICTURE_STREAM4        0x24
#define SUBPICTURE_STREAM5        0x25
#define SUBPICTURE_STREAM6        0x26
#define SUBPICTURE_STREAM7        0x27
#define SUBPICTURE_STREAM8        0x28
#define SUBPICTURE_STREAM9        0x29
#define SUBPICTURE_STREAM10       0x2A
#define SUBPICTURE_STREAM11       0x2B
#define SUBPICTURE_STREAM12       0x2C
#define SUBPICTURE_STREAM13       0x2D
#define SUBPICTURE_STREAM14       0x2E
#define SUBPICTURE_STREAM15       0x2F
#define SUBPICTURE_STREAM16       0x30
#define SUBPICTURE_STREAM17       0x31
#define SUBPICTURE_STREAM18       0x32
#define SUBPICTURE_STREAM19       0x33
#define SUBPICTURE_STREAM20       0x34
#define SUBPICTURE_STREAM21       0x35
#define SUBPICTURE_STREAM22       0x36
#define SUBPICTURE_STREAM23       0x37
#define SUBPICTURE_STREAM24       0x38
#define SUBPICTURE_STREAM25       0x39
#define SUBPICTURE_STREAM26       0x3A
#define SUBPICTURE_STREAM27       0x3B
#define SUBPICTURE_STREAM28       0x3C
#define SUBPICTURE_STREAM29       0x3D
#define SUBPICTURE_STREAM30       0x3E
#define SUBPICTURE_STREAM31       0x3F

/* AC3 streams */
#define AC3_STREAM0               0x80
#define AC3_STREAM1               0x81
#define AC3_STREAM2               0x82
#define AC3_STREAM3               0x83
#define AC3_STREAM4               0x84
#define AC3_STREAM5               0x85
#define AC3_STREAM6               0x86
#define AC3_STREAM7               0x87

/* DTS streams */
#define DTS_STREAM0               0x88
#define DTS_STREAM1               0x89
#define DTS_STREAM2               0x8A
#define DTS_STREAM3               0x8B
#define DTS_STREAM4               0x8C
#define DTS_STREAM5               0x8D
#define DTS_STREAM6               0x8E
#define DTS_STREAM7               0x8F

/* SDDS streams */
#define SDDS_STREAM0              0x90
#define SDDS_STREAM1              0x91
#define SDDS_STREAM2              0x92
#define SDDS_STREAM3              0x93
#define SDDS_STREAM4              0x94
#define SDDS_STREAM5              0x95
#define SDDS_STREAM6              0x96
#define SDDS_STREAM7              0x97

/* PCM streams */
#define PCM_STREAM0               0xA0
#define PCM_STREAM1               0xA1
#define PCM_STREAM2               0xA2
#define PCM_STREAM3               0xA3
#define PCM_STREAM4               0xA4
#define PCM_STREAM5               0xA5
#define PCM_STREAM6               0xA6
#define PCM_STREAM7               0xA7

/* other system defines */
#define MIN_MPEG2_AFTER_PACKET_LENGTH  3
#define MIN_MPEG1_AFTER_PACKET_LENGTH  1

#define MAX_MPEG2_AFTER_PACKET_LENGTH  16
#define MAX_MPEG1_AFTER_PACKET_LENGTH  12

#define MPEG1_PACK_HEADER_SIZE         12
#define MPEG2_PACK_HEADER_SIZE         14

#define PACKET_HEADER_SIZE             6

/** \name picture structure 
  * @{
  */

#define TOP_FIELD     1	    /**< \brief  \hideinitializer  */
#define BOTTOM_FIELD  2	    /**< \brief  \hideinitializer  */
#define FRAME_PICTURE 3	    /**< \brief  \hideinitializer  */
/** @} */

/* extension start code IDs */
#define SEQ_ID       1
#define DISP_ID      2
#define QUANT_ID     3
#define SEQSCAL_ID   5
#define PANSCAN_ID   7
#define CODING_ID    8
#define SPATSCAL_ID  9
#define TEMPSCAL_ID 10

/** \name picture coding type 
  * @{
  */
#define I_TYPE 1	    /**< \brief  \hideinitializer  */
#define P_TYPE 2	    /**< \brief  \hideinitializer  */
#define B_TYPE 3	    /**< \brief  \hideinitializer  */
#define D_TYPE 4	    /**< \brief  \hideinitializer  */
/** @} */

/** \name macroblock type 
  * @{
  */
#define MB_INTRA    1	    /**< \brief  \hideinitializer  */
#define MB_PATTERN  2	    /**< \brief  \hideinitializer  */
#define MB_BACKWARD 4	    /**< \brief  \hideinitializer  */
#define MB_FORWARD  8	    /**< \brief  \hideinitializer  */
#define MB_QUANT    16	    /**< \brief  \hideinitializer  */
/** @} */

/** \name motion_type 
  * @{
  */
#define MC_FIELD 1	    /**< \brief  \hideinitializer  */
#define MC_FRAME 2	    /**< \brief  \hideinitializer  */
#define MC_16X8  2	    /**< \brief  \hideinitializer  */
#define MC_DMV   3	    /**< \brief  \hideinitializer  */
/** @} */

/** \name mv_format  
  * @{
  */
#define MV_FIELD 0	    /**< \brief  \hideinitializer  */
#define MV_FRAME 1	    /**< \brief  \hideinitializer  */
/** @} */

/** \name chroma_format  
  * @{
  */
#define CHROMA_UNKNOWN -1   /**< \brief  \hideinitializer  */
#define CHROMA400 0	        /**< \brief  \hideinitializer  */
#define CHROMA420 1	        /**< \brief  \hideinitializer  */
#define CHROMA422 2	        /**< \brief  \hideinitializer  */
#define CHROMA444 3	        /**< \brief  \hideinitializer  */
#define CHROMA211 4	        /**< \brief  \hideinitializer  */
#define CHROMA410 5	        /**< \brief  \hideinitializer  */
#define CHROMA411 6	        /**< \brief  \hideinitializer  */
#define CHROMA810 7	        /**< \brief  \hideinitializer  */
/** @} */

/* muxer flags */
#define SEQHDR_FLAG             0x01
#define GOPHDR_FLAG             0x02
#define SVCD_USER_BLOCK         0x04
#define SEQ_USER_BLOCK          0x08
#define PIC_USER_BLOCK          0x10
#define SPLIT_FILE_FLAG         0x20
#define AU_FLAG                 0x40
#define GOP_USER_BLOCK          0x80


/**
 * @name MPEG Audio mode
 * @{
 **/
#define MPG_MD_STEREO           0			///< Stereo mode
#define MPG_MD_JOINT_STEREO     1			///< Allow joint stereo (intensity stereo) mode
#define MPG_MD_DUAL_CHANNEL     2			///< Dual channel mode
#define MPG_MD_MONO             3			///< Single channel (mono) mode
/** @} */


/**
 * @name MPEG output return codes
 * @{
 **/
#define mpegOutErrNone    0       ///< no error
#define mpegOutCancel     1       ///< user canceled settings
#define mpegOutError      2       ///< undefined error
#define mpegOutDecline    3       ///< unable to use input settings, resolution, audio etc.
#define mpegOutEOFReached 4       ///< returned by SR, when mpegin returns mpegInEOF
/** @} */

/**
 * @name MPEG input return codes
 * @{
 **/
#define mpegInErrNone     0       ///< no error
#define mpegInError       1       ///< undefined error
#define mpegInEOF         2       ///< end of file error
/** @} */

// access modes for mpgvdec and mpgadec
// accurate is only needed if the PTS's of a program stream are not
// contiguous. it is always used when reading an elemental stream
#define ACCESS_ACCURATE   0  // parse entire file when opening
#define ACCESS_FAST       1  // read first/last PTS's and use time stamps for seeking

// for mpegOutVideoDefaults(mpeg_v_settings *set, int video_type, int PAL);
#define VM_NTSC           0
#define VM_PAL            1


/**
 * @name MPEG-1 layer 1 bit rates
 * @{
 **/
#define L1_AUDIOBITRATE32    1			///< 32 kbit/sec
#define L1_AUDIOBITRATE64    2			///< 64 kbit/sec
#define L1_AUDIOBITRATE96    3			///< 96 kbit/sec
#define L1_AUDIOBITRATE128   4			///< 128 kbit/sec
#define L1_AUDIOBITRATE160   5			///< 160 kbit/sec
#define L1_AUDIOBITRATE192   6			///< 192 kbit/sec
#define L1_AUDIOBITRATE224   7			///< 224 kbit/sec
#define L1_AUDIOBITRATE256   8			///< 256 kbit/sec
#define L1_AUDIOBITRATE288   9			///< 288 kbit/sec
#define L1_AUDIOBITRATE320   10			///< 320 kbit/sec
#define L1_AUDIOBITRATE352   11			///< 352 kbit/sec
#define L1_AUDIOBITRATE384   12			///< 384 kbit/sec
#define L1_AUDIOBITRATE416   13			///< 416 kbit/sec
#define L1_AUDIOBITRATE448   14			///< 448 kbit/sec
/** @} */


/**
 * @name MPEG-1 layer 2 bit rates
 * @{
 **/
#define L2_AUDIOBITRATE32    1			///< 32 kbit/sec
#define L2_AUDIOBITRATE48    2			///< 48 kbit/sec
#define L2_AUDIOBITRATE56    3			///< 56 kbit/sec
#define L2_AUDIOBITRATE64    4			///< 64 kbit/sec
#define L2_AUDIOBITRATE80    5			///< 80 kbit/sec
#define L2_AUDIOBITRATE96    6			///< 96 kbit/sec
#define L2_AUDIOBITRATE112   7			///< 112 kbit/sec
#define L2_AUDIOBITRATE128   8			///< 128 kbit/sec
#define L2_AUDIOBITRATE160   9			///< 160 kbit/sec
#define L2_AUDIOBITRATE192   10			///< 192 kbit/sec
#define L2_AUDIOBITRATE224   11			///< 224 kbit/sec
#define L2_AUDIOBITRATE256   12			///< 256 kbit/sec
#define L2_AUDIOBITRATE320   13			///< 320 kbit/sec
#define L2_AUDIOBITRATE384   14			///< 384 kbit/sec
/** @} */


/**
 * @name MPEG-2 LSF layer 1 bit rates
 * @{
 **/
#define LSF_L1_AUDIOBITRATE32    1			///< 32 kbit/sec
#define LSF_L1_AUDIOBITRATE48    2			///< 48 kbit/sec
#define LSF_L1_AUDIOBITRATE56    3			///< 56 kbit/sec
#define LSF_L1_AUDIOBITRATE64    4			///< 64 kbit/sec
#define LSF_L1_AUDIOBITRATE80    5			///< 80 kbit/sec
#define LSF_L1_AUDIOBITRATE96    6			///< 96 kbit/sec
#define LSF_L1_AUDIOBITRATE112   7			///< 112 kbit/sec
#define LSF_L1_AUDIOBITRATE128   8			///< 128 kbit/sec
#define LSF_L1_AUDIOBITRATE144   9			///< 144 kbit/sec
#define LSF_L1_AUDIOBITRATE160   10			///< 160 kbit/sec
#define LSF_L1_AUDIOBITRATE176   11			///< 176 kbit/sec
#define LSF_L1_AUDIOBITRATE192   12			///< 192 kbit/sec
#define LSF_L1_AUDIOBITRATE224   13			///< 224 kbit/sec
#define LSF_L1_AUDIOBITRATE256   14			///< 256 kbit/sec
/** @} */


/**
 * @name MPEG-2 LSF layer 2 bit rates
 * @{
 **/
#define LSF_L2_AUDIOBITRATE8     1			///< 8 kbit/sec
#define LSF_L2_AUDIOBITRATE16    2			///< 16 kbit/sec
#define LSF_L2_AUDIOBITRATE24    3			///< 24 kbit/sec
#define LSF_L2_AUDIOBITRATE32    4			///< 32 kbit/sec
#define LSF_L2_AUDIOBITRATE40    5			///< 40 kbit/sec
#define LSF_L2_AUDIOBITRATE48    6			///< 48 kbit/sec
#define LSF_L2_AUDIOBITRATE56    7			///< 56 kbit/sec
#define LSF_L2_AUDIOBITRATE64    8			///< 64 kbit/sec
#define LSF_L2_AUDIOBITRATE80    9			///< 80 kbit/sec
#define LSF_L2_AUDIOBITRATE96    10			///< 96 kbit/sec
#define LSF_L2_AUDIOBITRATE112   11			///< 112 kbit/sec
#define LSF_L2_AUDIOBITRATE128   12			///< 128 kbit/sec
#define LSF_L2_AUDIOBITRATE144   13			///< 144 kbit/sec
#define LSF_L2_AUDIOBITRATE160   14			///< 160 kbit/sec
/** @} */

// video encoder performance level
#define VIDEO_LEVEL_MIN   0
#define VIDEO_LEVEL_MAX   31


/**
 * @name Bitrate mode
 *Defines for mpeg_v_settings::constant_bitrate value used for both the video encoder and the multiplexer
 * @{
 **/
#define VBR_CONSTANT      1                 ///< constant bitrate (default in all presets)
#define VBR_VARIABLE1     0                 ///< variable bitrate
//#define VBR_VARIABLE2     2   // was never really used
//#define VBR_VARIABLE3     3   // was never really used
#define VBR_CQT           2                 ///< constant quantization (see @ref mpeg_v_settings::mquant_value settings)
#define VBR_CQT_STRICT    3                 ///< strict constant quantization (see @ref mpeg_v_settings::mquant_value settings)
/** @} */


/**
 * @name Extended option defines
 * @brief for opt_flags parameter of @ref h264OutVideoPutFrame, @ref hevcOutVideoPutFrame, etc.
 * @{
 **/
#define OPT_EXT_PARAM_MASK              (0xFFFFF008L)   /**< @brief Mask to all ext parameters (enc_mp2v only) @hideinitializer*/
#define OPT_EXT_PARAM_FRM_ORG           (0x00000008L)   /**< @brief Show original frame @hideinitializer */
// earlier declaration was #define OPT_EXT_PARAM_FRM_ORG           (0x00001000L)  //show original frame
// changed due to conflict with INIT_OPT_CHAPTER_LIST
#define OPT_EXT_CHAPTER_LIST            (0x00001000L)   /**< @brief Chapter list @hideinitializer */
#define OPT_EXT_PARAM_FRM_ENC           (0x00002000L)   /**< @brief Show encoded frame @hideinitializer */
#define OPT_EXT_PARAM_SHOW_ONLY         (0x00004000L)   /**< @brief Don't encode, show only (enc_mp2v only) @hideinitializer */
#define OPT_EXT_PARAM_FRM_PRC           (0x00008000L)   /**< @brief Show preprocessed frame (enc_mp2v only) @hideinitializer */
#define OPT_EXT_PARAM_SEQ_UD            (0x00010000L)   /**< @brief Write GOP user data @hideinitializer */
#define OPT_EXT_PARAM_PIC_UD            (0x00020000L)   /**< @brief Write picture user data @hideinitializer */
#define OPT_EXT_PARAM_SR_DATA           (0x00040000L)   /**< @brief Smart render data @hideinitializer */
#define OPT_EXT_PARAM_RAW_DATA  OPT_EXT_PARAM_SR_DATA   /**< @brief Smart render data (enc_mp2v only) @hideinitializer */
#define OPT_EXT_PARAM_CONTENT           (0x00080000L)   /**< @brief Data about current frame-content (enc_mp2v only) @hideinitializer */
#define OPT_EXT_PARAM_ALPHA_PLANE       (0x00100000L)   /**< @brief Add alpha plane @hideinitializer */
#define OPT_EXT_PARAM_VCSD_DATA         (0x00200000L)   /**< @brief Video content scene detection data (enc_mp2v only) @hideinitializer */
#define OPT_EXT_PARAM_STOP_DATA         (0x00400000L)   /**< @brief Not implemented (enc_mp2v only) @hideinitializer */
#define OPT_EXT_PARAM_FORCE_IDR         (0x00800000L)   /**< @brief For a current frame forces it to be an IDR (enc_avc and enc_hevc only) respecting chapter list and minimal IDR interval @hideinitializer */
#define OPT_EXT_PARAM_TARGET_VBV        (0x01000000L)   /**< @brief Target a specific VBV state within given frame interval @hideinitializer */
#define OPT_EXT_PARAM_CONSTRAIN_VBV     (0x02000000L)   /**< @brief Stay beyond a specific VBV state within given frame interval (enc_mp2v only) @hideinitializer */
#define OPT_EXT_PARAM_FRM_VAM           (0x04000000L)   /**< @brief VAM @hideinitializer */
#define OPT_EXT_PARAM_CPB_DELAY         (0x08000000L)   /**< @brief CPB removal delay value to insert into Picture Timing SEI of correspond IDR @hideinitializer */
#define OPT_EXT_PARAM_TIMESTAMPS        (0x10000000L)   /**< @brief Specify PTS for the frame @hideinitializer */
#define OPT_EXT_PARAM_BITRATE           (0x20000000L)   /**< @brief For changing bitrate "on the fly" (during encoding) (enc_mp2v only) @hideinitializer */
#define OPT_EXT_PARAM_FIELDS_DROPPED    (0x40000000L)   /**< @brief Specify number of dropped fields (e.g. by capture device), used to adjust timecode @hideinitializer */
#define OPT_EXT_PARAM_DISPLAY_MODE      (0x80000000L)   /**< @brief Specify frame display mode (frame, top field-bottom field, etc.), used in VIDEO_PULLDOWN_AUTO mode @hideinitializer */
/** @} */

#define OPT_INSERT_FRAME          (0x00000100L)   /**<@brief @brief Pad skipped frame */
#define OPT_INSERT_KEY_FRAME      (0x00001000L)   /**<@brief @brief Encode current frame as I-frame. Only applies to enc_mp4v. For enc_avc and enc_hevc please use /ref OPT_EXT_PARAM_FORCE_IDR */

// PCM audio defines
#define PCM_1CHANNEL      0
#define PCM_2CHANNEL      1
#define PCM_3CHANNEL      2
#define PCM_4CHANNEL      3
#define PCM_5CHANNEL      4
#define PCM_6CHANNEL      5
#define PCM_7CHANNEL      6
#define PCM_8CHANNEL      7
#define PCM_16CHANNEL     15 // currently AES-3 382 only

#define PCM_EMPHASIS_OFF  0
#define PCM_EMPHASIS_ON   1

#define PCM_MUTE_OFF      0
#define PCM_MUTE_ON       1

#define PCM_16BITS        0
#define PCM_20BITS        1
#define PCM_24BITS        2

#define PCM_NO_DYNAMIC_RANGE_CONTROL  0x80

// AC3 audio defines
#define AC3_CHANNEL_LEFT        0
#define AC3_CHANNEL_CENTER      1
#define AC3_CHANNEL_RIGHT       2
#define AC3_CHANNEL_LEFT_SUR    3
#define AC3_CHANNEL_RIGHT_SUR   4
#define AC3_CHANNEL_LFE         5

#define AC3_AUDIOMODE_DSC   0   // Dolby Surround compatible (Lt,Rt)
#define AC3_AUDIOMODE_1_1   0   // (L,R)        2 channels total
#define AC3_AUDIOMODE_1_0   1   // (C)          1 channel total
#define AC3_AUDIOMODE_2_0   2   // (L,R)        2 channels total
#define AC3_AUDIOMODE_3_0   3   // (L,C,R)      3 channels total
#define AC3_AUDIOMODE_2_1   4   // (L,R,l)      3 channels total
#define AC3_AUDIOMODE_3_1   5   // (L,C,R,l)    4 channels total
#define AC3_AUDIOMODE_2_2   6   // (L,R,l,r)    4 channels total
#define AC3_AUDIOMODE_3_2   7   // (L,C,R,l,r)  5 channels total

#define AC3_BITRATE_64      4
#define AC3_BITRATE_80      5
#define AC3_BITRATE_96      6
#define AC3_BITRATE_112     7
#define AC3_BITRATE_128     8
#define AC3_BITRATE_160     9
#define AC3_BITRATE_192    10
#define AC3_BITRATE_224    11
#define AC3_BITRATE_256    12
#define AC3_BITRATE_320    13
#define AC3_BITRATE_384    14
#define AC3_BITRATE_448    15
#define AC3_BITRATE_512    16
#define AC3_BITRATE_576    17
#define AC3_BITRATE_640    18


// defines for VCD conformance check errors
#define INV_VCD_VID_ERRORS             0x00000100
#define INV_VCD_VID_FRAMERATE          INV_VCD_VID_ERRORS + 0
#define INV_VCD_VID_DEF_HSIZE          INV_VCD_VID_ERRORS + 1
#define INV_VCD_VID_DEF_VSIZE          INV_VCD_VID_ERRORS + 2
#define INV_VCD_VID_CBR                INV_VCD_VID_ERRORS + 3
#define INV_VCD_VID_BITRATE            INV_VCD_VID_ERRORS + 4

#define INV_VCD_AUD_ERRORS             0x00000200
#define INV_VCD_AUD_LAYER              INV_VCD_AUD_ERRORS + 0
#define INV_VCD_AUD_MODE               INV_VCD_AUD_ERRORS + 1
#define INV_VCD_AUD_BITRATE            INV_VCD_AUD_ERRORS + 2
#define INV_VCD_AUD_SAMPLE_RATE        INV_VCD_AUD_ERRORS + 3
#define INV_VCD_AUD_TYPE               INV_VCD_AUD_ERRORS + 4

#define INV_VCD_MUX_ERRORS             0x00000400
#define INV_VCD_MUX_SECTOR_SIZE        INV_VCD_MUX_ERRORS + 0
#define INV_VCD_MUX_PACKETS_PER_PACK   INV_VCD_MUX_ERRORS + 1
#define INV_VCD_MUX_AUDIO1_BSIZE       INV_VCD_MUX_ERRORS + 2
#define INV_VCD_MUX_VIDEO_BSIZE        INV_VCD_MUX_ERRORS + 3
#define INV_VCD_MUX_MUX_RATE           INV_VCD_MUX_ERRORS + 4
#define INV_VCD_MUX_TIMESTAMPS         INV_VCD_MUX_ERRORS + 5
#define INV_VCD_MUX_VBR_MULTIPLEX      INV_VCD_MUX_ERRORS + 6
#define INV_VCD_MUX_NOVCD_MUX          INV_VCD_MUX_ERRORS + 7

// defines for SVCD conformance check errors
#define INV_SVCD_VID_ERRORS            0x00000800
#define INV_SVCD_VID_FRAMERATE         INV_SVCD_VID_ERRORS + 0
#define INV_SVCD_VID_MPEGN             INV_SVCD_VID_ERRORS + 1
#define INV_SVCD_VID_DEF_VSIZE         INV_SVCD_VID_ERRORS + 2
#define INV_SVCD_VID_DEF_HSIZE         INV_SVCD_VID_ERRORS + 3
#define INV_SVCD_VID_MPEGM             INV_SVCD_VID_ERRORS + 4
#define INV_SVCD_VID_PROFILE           INV_SVCD_VID_ERRORS + 5
#define INV_SVCD_VID_LEVEL             INV_SVCD_VID_ERRORS + 6
#define INV_SVCD_VID_DATA_BLOCKS       INV_SVCD_VID_ERRORS + 7
#define INV_SVCD_VID_PSEQ              INV_SVCD_VID_ERRORS + 8
#define INV_SVCD_VID_ARATIO            INV_SVCD_VID_ERRORS + 9
#define INV_SVCD_VID_BITRATE           INV_SVCD_VID_ERRORS + 10
#define INV_SVCD_VID_MAXBITRATE        INV_SVCD_VID_ERRORS + 11
#define INV_SVCD_VID_VBVBUFFER         INV_SVCD_VID_ERRORS + 12

#define INV_SVCD_AUD_ERRORS            0x00001000
#define INV_SVCD_AUD_LAYER             INV_SVCD_AUD_ERRORS + 0
#define INV_SVCD_AUD_EPROTECTION       INV_SVCD_AUD_ERRORS + 1
#define INV_SVCD_AUD_EMPHASIS          INV_SVCD_AUD_ERRORS + 2
#define INV_SVCD_AUD_BITRATE           INV_SVCD_AUD_ERRORS + 3
#define INV_SVCD_AUD_SAMPLE_RATE       INV_SVCD_AUD_ERRORS + 4
#define INV_SVCD_AUD_TYPE              INV_SVCD_AUD_ERRORS + 5

#define INV_SVCD_MUX_ERRORS            0x00002000
#define INV_SVCD_MUX_SECTOR_SIZE       INV_SVCD_MUX_ERRORS + 0
#define INV_SVCD_MUX_PACKETS_PER_PACK  INV_SVCD_MUX_ERRORS + 1
#define INV_SVCD_MUX_AUDIO1_BSIZE      INV_SVCD_MUX_ERRORS + 2
#define INV_SVCD_MUX_AUDIO2_BSIZE      INV_SVCD_MUX_ERRORS + 3
#define INV_SVCD_MUX_VIDEO_BSIZE       INV_SVCD_MUX_ERRORS + 4
#define INV_SVCD_MUX_MUX_RATE          INV_SVCD_MUX_ERRORS + 5
#define INV_SVCD_MUX_SCAN_OFFSETS      INV_SVCD_MUX_ERRORS + 6
#define INV_SVCD_MUX_NOSVCD_MUX        INV_SVCD_MUX_ERRORS + 7

// defines for DVD conformance check errors
#define INV_DVD_VID_ERRORS             0x00004000
#define INV_DVD_VID_FRAMERATE          INV_DVD_VID_ERRORS + 0
#define INV_DVD_VID_MPEGN              INV_DVD_VID_ERRORS + 1
#define INV_DVD_VID_DEF_HSIZE          INV_DVD_VID_ERRORS + 2
#define INV_DVD_VID_DEF_VSIZE          INV_DVD_VID_ERRORS + 3
#define INV_DVD_VID_TRANSFER_CHAR      INV_DVD_VID_ERRORS + 4
#define INV_DVD_VID_COLOR_PRIM         INV_DVD_VID_ERRORS + 5
#define INV_DVD_VID_DEF_DISP_VSIZE     INV_DVD_VID_ERRORS + 6
#define INV_DVD_VID_PROFILE            INV_DVD_VID_ERRORS + 7
#define INV_DVD_VID_LEVEL              INV_DVD_VID_ERRORS + 8
#define INV_DVD_VID_PSEQ               INV_DVD_VID_ERRORS + 9
#define INV_DVD_VID_ARATIO             INV_DVD_VID_ERRORS + 10
#define INV_DVD_VID_BITRATE            INV_DVD_VID_ERRORS + 11
#define INV_DVD_VID_MAXBITRATE         INV_DVD_VID_ERRORS + 12
#define INV_DVD_VID_DEF_DISP_HSIZE     INV_DVD_VID_ERRORS + 13
#define INV_DVD_VID_DEF_HSIZE_HCENTER  INV_DVD_VID_ERRORS + 14
#define INV_DVD_VID_VCENTER            INV_DVD_VID_ERRORS + 15
#define INV_DVD_VID_MATRIX_COEFF       INV_DVD_VID_ERRORS + 16
#define INV_DVD_VID_SEQ_HDR            INV_DVD_VID_ERRORS + 17
#define INV_DVD_VID_MPEG1_DEF_HSIZE    INV_DVD_VID_ERRORS + 18
#define INV_DVD_VID_MPEG1_ARATIO       INV_DVD_VID_ERRORS + 19
#define INV_DVD_VID_MPEG1_DEF_VSIZE    INV_DVD_VID_ERRORS + 20
#define INV_DVD_VID_DVR_DISP_HSIZE     INV_DVD_VID_ERRORS + 21
#define INV_DVD_VID_DVR_HSIZE_HCENTER  INV_DVD_VID_ERRORS + 22
#define INV_DVD_VID_MPEG1_CPARMS       INV_DVD_VID_ERRORS + 23

#define INV_DVD_AUD_ERRORS             0x00008000
#define INV_DVD_AUD_LAYER              INV_DVD_AUD_ERRORS + 0
#define INV_DVD_AUD_EPROTECTION        INV_DVD_AUD_ERRORS + 1
#define INV_DVD_AUD_EMPHASIS           INV_DVD_AUD_ERRORS + 2
#define INV_DVD_AUD_PRIVATEBIT         INV_DVD_AUD_ERRORS + 3
#define INV_DVD_AUD_BITRATE            INV_DVD_AUD_ERRORS + 4
#define INV_DVD_AUD_MODE               INV_DVD_AUD_ERRORS + 5
#define INV_DVD_AUD_SAMPLE_RATE        INV_DVD_AUD_ERRORS + 6
#define INV_DVD_AUD_DVR_PCM_CHANNELS   INV_DVD_AUD_ERRORS + 7
#define INV_DVD_AUD_DVR_PCM_QUANT      INV_DVD_AUD_ERRORS + 8
#define INV_DVD_AUD_DVR_PCM_FREQUENCY  INV_DVD_AUD_ERRORS + 9
#define INV_DVD_AUD_TYPE               INV_DVD_AUD_ERRORS + 10
#define INV_DVD_AUD_ENDIAN             INV_DVD_AUD_ERRORS + 11

#define INV_DVD_MUX_ERRORS              0x00010000
#define INV_DVD_MUX_SECTOR_SIZE         INV_DVD_MUX_ERRORS + 0
#define INV_DVD_MUX_PACKETS_PER_PACK    INV_DVD_MUX_ERRORS + 1
#define INV_DVD_MUX_AUDIO1_BSIZE        INV_DVD_MUX_ERRORS + 2
#define INV_DVD_MUX_AUDIO2_BSIZE        INV_DVD_MUX_ERRORS + 3
#define INV_DVD_MUX_VIDEO_BSIZE         INV_DVD_MUX_ERRORS + 4
#define INV_DVD_MUX_MUX_RATE            INV_DVD_MUX_ERRORS + 5
#define INV_DVD_MUX_ALIGN_SH            INV_DVD_MUX_ERRORS + 6
#define INV_DVD_MUX_PRIVATE2            INV_DVD_MUX_ERRORS + 7
#define INV_DVD_MUX_NODVD_MUX           INV_DVD_MUX_ERRORS + 8
#define INV_DVD_MUX_MPEG1_VIDEO_BSIZE   INV_DVD_MUX_ERRORS + 9
#define INV_DVD_MUX_NODVD_MPEG1_MUX     INV_DVD_MUX_ERRORS + 10
#define INV_DVD_MUX_NODVD_DVR_MUX       INV_DVD_MUX_ERRORS + 11
#define INV_DVD_MUX_NODVD_DVR_MPEG1_MUX INV_DVD_MUX_ERRORS + 12

// defines for DVB conformance check errors
#define INV_DVB_VID_ERRORS             0x00012000
#define INV_DVB_VID_PROFILE            INV_DVB_VID_ERRORS + 0
#define INV_DVB_VID_DEF_VSIZE          INV_DVB_VID_ERRORS + 1
#define INV_DVB_VID_FRAMERATE          INV_DVB_VID_ERRORS + 2
#define INV_DVB_VID_CHROMA             INV_DVB_VID_ERRORS + 3
#define INV_DVB_VID_SEQ_HDR            INV_DVB_VID_ERRORS + 4
#define INV_DVB_VID_ARATIO             INV_DVB_VID_ERRORS + 5
#define INV_DVB_VID_DEF_HSIZE          INV_DVB_VID_ERRORS + 6

#define INV_DVB_AUD_ERRORS             0x00012100
#define INV_DVB_AUD_LAYER              INV_DVB_AUD_ERRORS + 0
#define INV_DVB_AUD_EPROTECTION        INV_DVB_AUD_ERRORS + 1
#define INV_DVB_AUD_EMPHASIS           INV_DVB_AUD_ERRORS + 2
#define INV_DVB_AUD_TYPE               INV_DVB_AUD_ERRORS + 3

#define INV_DVB_MUX_ERRORS             0x00012200
#define INV_DVB_MUX_NODVB_MUX          INV_DVB_MUX_ERRORS + 0
#define INV_DVB_MUX_MUX_RATE           INV_DVB_MUX_ERRORS + 1

// defines for MICROMV conformance check errors
#define INV_MMV_VID_ERRORS             0x00013000
#define INV_MMV_VID_PROFILE            INV_MMV_VID_ERRORS + 0
#define INV_MMV_VID_LEVEL              INV_MMV_VID_ERRORS + 1
#define INV_MMV_VID_MPEGN              INV_MMV_VID_ERRORS + 2
#define INV_MMV_VID_DEF_VSIZE          INV_MMV_VID_ERRORS + 3
#define INV_MMV_VID_FRAMERATE          INV_MMV_VID_ERRORS + 4
#define INV_MMV_VID_MPEGM              INV_MMV_VID_ERRORS + 5
#define INV_MMV_VID_SEQ_HDR            INV_MMV_VID_ERRORS + 6
#define INV_MMV_VID_ARATIO             INV_MMV_VID_ERRORS + 7
#define INV_MMV_VID_DEF_HSIZE          INV_MMV_VID_ERRORS + 8

#define INV_MMV_AUD_ERRORS             0x00013100
#define INV_MMV_AUD_LAYER              INV_MMV_AUD_ERRORS + 0
#define INV_MMV_AUD_EPROTECTION        INV_MMV_AUD_ERRORS + 1
#define INV_MMV_AUD_EMPHASIS           INV_MMV_AUD_ERRORS + 2
#define INV_MMV_AUD_SAMPLE_RATE        INV_MMV_AUD_ERRORS + 3
#define INV_MMV_AUD_BITRATE            INV_MMV_AUD_ERRORS + 4
#define INV_MMV_AUD_TYPE               INV_MMV_AUD_ERRORS + 5

#define INV_MMV_MUX_ERRORS             0x00013200
#define INV_MMV_MUX_NOMMV_MUX          INV_MMV_MUX_ERRORS + 0

// defines for DVHS conformance check errors
#define INV_DVHS_VID_ERRORS            0x00014000
#define INV_DVHS_VID_PROFILE           INV_DVHS_VID_ERRORS + 0
#define INV_DVHS_VID_LEVEL             INV_DVHS_VID_ERRORS + 1
#define INV_DVHS_VID_DEF_VSIZE         INV_DVHS_VID_ERRORS + 2
#define INV_DVHS_VID_FRAMERATE         INV_DVHS_VID_ERRORS + 3
#define INV_DVHS_VID_CHROMA            INV_DVHS_VID_ERRORS + 4
#define INV_DVHS_VID_SEQ_HDR           INV_DVHS_VID_ERRORS + 5
#define INV_DVHS_VID_DEF_HSIZE         INV_DVHS_VID_ERRORS + 6
#define INV_DVHS_VID_ARATIO            INV_DVHS_VID_ERRORS + 7
#define INV_DVHS_VID_PROGSEQ           INV_DVHS_VID_ERRORS + 8

#define INV_DVHS_AUD_ERRORS            0x00014100
#define INV_DVHS_AUD_LAYER             INV_DVHS_AUD_ERRORS + 0
#define INV_DVHS_AUD_EPROTECTION       INV_DVHS_AUD_ERRORS + 1
#define INV_DVHS_AUD_EMPHASIS          INV_DVHS_AUD_ERRORS + 2
#define INV_DVHS_AUD_BITRATE           INV_DVHS_AUD_ERRORS + 3
#define INV_DVHS_PCM_CHANNELS          INV_DVHS_AUD_ERRORS + 4
#define INV_DVHS_PCM_EMPHASIS          INV_DVHS_AUD_ERRORS + 5
#define INV_DVHS_PCM_BITDEPTH          INV_DVHS_AUD_ERRORS + 6
#define INV_DVHS_PCM_FREQUENCY         INV_DVHS_AUD_ERRORS + 7
#define INV_DVHS_AUD_SAMPLE_RATE       INV_DVHS_AUD_ERRORS + 8
#define INV_DVHS_AUD_CMODE             INV_DVHS_AUD_ERRORS + 9
#define INV_DVHS_AUD_TYPE              INV_DVHS_AUD_ERRORS + 10

#define INV_DVHS_MUX_ERRORS            0x00014200
#define INV_DVHS_MUX_NODVHS_MUX        INV_DVHS_MUX_ERRORS + 0
#define INV_DVHS_MUX_MUX_RATE          INV_DVHS_MUX_ERRORS + 1

// defines for ATSC conformance check errors
#define INV_ATSC_VID_ERRORS            0x00015000
#define INV_ATSC_VID_PROFILE           INV_ATSC_VID_ERRORS + 0
#define INV_ATSC_VID_DEF_VSIZE         INV_ATSC_VID_ERRORS + 1
#define INV_ATSC_VID_FRAMERATE         INV_ATSC_VID_ERRORS + 2
#define INV_ATSC_VID_BITRATE           INV_ATSC_VID_ERRORS + 3
#define INV_ATSC_VID_CHROMA            INV_ATSC_VID_ERRORS + 4
#define INV_ATSC_VID_VBVBUFFER         INV_ATSC_VID_ERRORS + 5
#define INV_ATSC_VID_SEQ_HDR           INV_ATSC_VID_ERRORS + 6
#define INV_ATSC_VID_DEF_HSIZE         INV_ATSC_VID_ERRORS + 7
#define INV_ATSC_VID_ARATIO            INV_ATSC_VID_ERRORS + 8
#define INV_ATSC_VID_PROGSEQ           INV_ATSC_VID_ERRORS + 9

#define INV_ATSC_AUD_ERRORS            0x00015100
#define INV_ATSC_AUD_TYPE              INV_ATSC_AUD_ERRORS + 0

#define INV_ATSC_MUX_ERRORS            0x00015200
#define INV_ATSC_MUX_NOATSC_MUX        INV_ATSC_MUX_ERRORS + 0
#define INV_ATSC_MUX_MUX_RATE          INV_ATSC_MUX_ERRORS + 1
#define INV_ATSC_MUX_HI_MUX_RATE       INV_ATSC_MUX_ERRORS + 2

// defines for HDV conformance check errors
#define INV_HDV_VID_ERRORS             0x00016000
#define INV_HDV_VID_PROFILE            INV_HDV_VID_ERRORS + 0
#define INV_HDV_VID_LEVEL              INV_HDV_VID_ERRORS + 1
#define INV_HDV_VID_MPEGN              INV_HDV_VID_ERRORS + 2
#define INV_HDV_VID_DEF_VSIZE          INV_HDV_VID_ERRORS + 3
#define INV_HDV_VID_FRAMERATE          INV_HDV_VID_ERRORS + 4
#define INV_HDV_VID_SEQ_HDR            INV_HDV_VID_ERRORS + 5
#define INV_HDV_VID_ARATIO             INV_HDV_VID_ERRORS + 6
#define INV_HDV_VID_DEF_HSIZE          INV_HDV_VID_ERRORS + 7
#define INV_HDV_VID_PROGSEQ            INV_HDV_VID_ERRORS + 8
#define INV_HDV_VID_VBR                INV_HDV_VID_ERRORS + 9
#define INV_HDV_VID_BITRATE            INV_HDV_VID_ERRORS + 10
#define INV_HDV_VID_CP                 INV_HDV_VID_ERRORS + 11
#define INV_HDV_VID_TC                 INV_HDV_VID_ERRORS + 12
#define INV_HDV_VID_MC                 INV_HDV_VID_ERRORS + 13
#define INV_HDV_VID_SEC                INV_HDV_VID_ERRORS + 14
#define INV_HDV_VID_MPEGM              INV_HDV_VID_ERRORS + 15
#define INV_HDV_VID_CHROMA             INV_HDV_VID_ERRORS + 16

#define INV_HDV_AUD_ERRORS             0x00016100
#define INV_HDV_AUD_LAYER              INV_HDV_AUD_ERRORS + 0
#define INV_HDV_AUD_EPROTECTION        INV_HDV_AUD_ERRORS + 1
#define INV_HDV_AUD_EMPHASIS           INV_HDV_AUD_ERRORS + 2
#define INV_HDV_AUD_SAMPLE_RATE        INV_HDV_AUD_ERRORS + 3
#define INV_HDV_AUD_BITRATE            INV_HDV_AUD_ERRORS + 4
#define INV_HDV_PCM_AUDIO              INV_HDV_AUD_ERRORS + 5
#define INV_HDV_AUD_TYPE               INV_HDV_AUD_ERRORS + 6

#define INV_HDV_MUX_ERRORS             0x00016200
#define INV_HDV_MUX_NOHDV_MUX          INV_HDV_MUX_ERRORS + 0
#define INV_HDV_MUX_HD1_MUX_RATE       INV_HDV_MUX_ERRORS + 1
#define INV_HDV_MUX_HD2_MUX_RATE       INV_HDV_MUX_ERRORS + 2


// defines for CableLabs conformance check errors
#define INV_CLABS_VID_ERRORS           0x00017000
#define INV_CLABS_VID_PROFILE          INV_CLABS_VID_ERRORS + 0
#define INV_CLABS_VID_LEVEL            INV_CLABS_VID_ERRORS + 1
#define INV_CLABS_VID_ARATIO           INV_CLABS_VID_ERRORS + 2
#define INV_CLABS_VID_FRAMERATE        INV_CLABS_VID_ERRORS + 3
#define INV_CLABS_VID_MPEGN            INV_CLABS_VID_ERRORS + 4
#define INV_CLABS_VID_MPEGM            INV_CLABS_VID_ERRORS + 5
#define INV_CLABS_VID_VBR              INV_CLABS_VID_ERRORS + 6
#define INV_CLABS_VID_BITRATE          INV_CLABS_VID_ERRORS + 7
#define INV_CLABS_VID_SEQ_HDR          INV_CLABS_VID_ERRORS + 8
#define INV_CLABS_VID_PIC_STRUCT       INV_CLABS_VID_ERRORS + 9
#define INV_CLABS_VID_DEF_HSIZE        INV_CLABS_VID_ERRORS + 10
#define INV_CLABS_VID_DEF_VSIZE        INV_CLABS_VID_ERRORS + 11

#define INV_CLABS_AUD_ERRORS           0x00017100
#define INV_CLABS_AUD_SAMPLE_RATE      INV_CLABS_AUD_ERRORS + 0
#define INV_CLABS_AUD_CMODE            INV_CLABS_AUD_ERRORS + 1
#define INV_CLABS_AUD_BITRATE          INV_CLABS_AUD_ERRORS + 2

#define INV_CLABS_MUX_ERRORS           0x00017200
#define INV_CLABS_MUX_RATE             INV_CLABS_MUX_ERRORS + 0

// defines for XDCAM HD conformance check errors
#define INV_XDCAM_VID_ERRORS           0x00018000
#define INV_XDCAM_VID_PROFILE          INV_XDCAM_VID_ERRORS + 0
#define INV_XDCAM_VID_LEVEL            INV_XDCAM_VID_ERRORS + 1
#define INV_XDCAM_VID_VBV              INV_XDCAM_VID_ERRORS + 2
#define INV_XDCAM_VID_HORZ             INV_XDCAM_VID_ERRORS + 3
#define INV_XDCAM_VID_DISPHORZ         INV_XDCAM_VID_ERRORS + 4
#define INV_XDCAM_VID_FRAMERATE        INV_XDCAM_VID_ERRORS + 5
#define INV_XDCAM_VID_1080VERT         INV_XDCAM_VID_ERRORS + 6
#define INV_XDCAM_VID_1080DISPVERT     INV_XDCAM_VID_ERRORS + 7
#define INV_XDCAM_VID_540VERT          INV_XDCAM_VID_ERRORS + 8
#define INV_XDCAM_VID_540DISPVERT      INV_XDCAM_VID_ERRORS + 9
#define INV_XDCAM_VID_GOP              INV_XDCAM_VID_ERRORS + 10
#define INV_XDCAM_VID_PROG             INV_XDCAM_VID_ERRORS + 11
#define INV_XDCAM_VID_TOPFIRST         INV_XDCAM_VID_ERRORS + 12
#define INV_XDCAM_VID_CHROMA           INV_XDCAM_VID_ERRORS + 13
#define INV_XDCAM_VID_CBR              INV_XDCAM_VID_ERRORS + 14
#define INV_XDCAM_VID_VBR              INV_XDCAM_VID_ERRORS + 15
#define INV_XDCAM_VID_BITRATE          INV_XDCAM_VID_ERRORS + 16
#define INV_XDCAM_VID_ARATIO           INV_XDCAM_VID_ERRORS + 17

// defines for D10 and XDCAM IMX conformance check errors
#define INV_D10_VID_ERRORS             0x00018500
#define INV_D10_VID_PROFILE            INV_D10_VID_ERRORS + 0
#define INV_D10_VID_LEVEL              INV_D10_VID_ERRORS + 1
#define INV_D10_VID_FRAMERATE          INV_D10_VID_ERRORS + 2
#define INV_D10_VID_GOP                INV_D10_VID_ERRORS + 3
#define INV_D10_VID_CHROMA             INV_D10_VID_ERRORS + 4
#define INV_D10_VID_CBR                INV_D10_VID_ERRORS + 5
#define INV_D10_VID_BITRATE            INV_D10_VID_ERRORS + 6
#define INV_D10_VID_DCPREC             INV_D10_VID_ERRORS + 7
#define INV_D10_VID_PROGSEQ            INV_D10_VID_ERRORS + 8
#define INV_D10_VID_PROGFRAME          INV_D10_VID_ERRORS + 9
#define INV_D10_VID_TOPFIRST           INV_D10_VID_ERRORS + 10
#define INV_D10_VID_REPEATFIRST        INV_D10_VID_ERRORS + 11
#define INV_D10_VID_FRAMEPRED          INV_D10_VID_ERRORS + 12
#define INV_D10_VID_QSCALE             INV_D10_VID_ERRORS + 13
#define INV_D10_VID_INTRAVLC           INV_D10_VID_ERRORS + 14
#define INV_D10_VID_ALTSCAN            INV_D10_VID_ERRORS + 15
#define INV_D10_VID_HORZ               INV_D10_VID_ERRORS + 16
#define INV_D10_VID_NTSCVERT           INV_D10_VID_ERRORS + 17
#define INV_D10_VID_PALVERT            INV_D10_VID_ERRORS + 18


// defines for HD_DVD conformance check errors
#define INV_HD_DVD_VID_ERRORS          0x00019000

// defines for BD_HDMV conformance check errors
#define INV_BD_HDMV_VID_ERRORS         0x00019500

// defines for MPEG conformance check errors
#define INV_MPEG_ERRORS                0x00020000

// defines for MPEG video conformance check errors
#define INV_VID_ERRORS                 INV_MPEG_ERRORS
#define INV_VID_DEF_HORZ_MPEG1         INV_MPEG_ERRORS + 0
#define INV_VID_DEF_VERT_MPEG1         INV_MPEG_ERRORS + 1
#define INV_VID_DEF_HORZ_MPEG2         INV_MPEG_ERRORS + 2
#define INV_VID_DEF_VERT_MPEG2         INV_MPEG_ERRORS + 3
#define INV_VID_DEF_HORZ_LEVEL         INV_MPEG_ERRORS + 4
#define INV_VID_DEF_VERT_LEVEL         INV_MPEG_ERRORS + 5
#define INV_VID_DEF_HV_FR_LEVEL        INV_MPEG_ERRORS + 6
#define INV_VID_ASPECT_RATIO           INV_MPEG_ERRORS + 7
#define INV_VID_FRAME_RATE             INV_MPEG_ERRORS + 8
#define INV_VID_BITRATE                INV_MPEG_ERRORS + 9
#define INV_VID_MAX_BITRATE            INV_MPEG_ERRORS + 10
#define INV_VID_AVG_BITRATE            INV_MPEG_ERRORS + 11
#define INV_VID_MIN_BITRATE            INV_MPEG_ERRORS + 12
#define INV_VID_VBVBUFFER              INV_MPEG_ERRORS + 13
#define INV_VID_CHROMA                 INV_MPEG_ERRORS + 14
#define INV_VID_VIDEO_FORMAT           INV_MPEG_ERRORS + 15
#define INV_VID_COLOR_PRIM             INV_MPEG_ERRORS + 16
#define INV_VID_TRANS_CHAR             INV_MPEG_ERRORS + 17
#define INV_VID_MATRIX_COEFF           INV_MPEG_ERRORS + 18
#define INV_VID_DISP_HORZ              INV_MPEG_ERRORS + 19
#define INV_VID_DISP_VERT              INV_MPEG_ERRORS + 20
#define INV_VID_DC_PREC                INV_MPEG_ERRORS + 21
#define INV_VID_PULLDOWN               INV_MPEG_ERRORS + 22
#define INV_VID_FH_FCODE               INV_MPEG_ERRORS + 23
#define INV_VID_FV_FCODE               INV_MPEG_ERRORS + 24
#define INV_VID_SXF                    INV_MPEG_ERRORS + 25
#define INV_VID_SYF                    INV_MPEG_ERRORS + 26
#define INV_VID_BH_FCODE               INV_MPEG_ERRORS + 27
#define INV_VID_BV_FCODE               INV_MPEG_ERRORS + 28
#define INV_VID_SXB                    INV_MPEG_ERRORS + 29
#define INV_VID_SYB                    INV_MPEG_ERRORS + 30
#define INV_VID_PROFILE                INV_MPEG_ERRORS + 31
#define INV_VID_LEVEL                  INV_MPEG_ERRORS + 32
#define INV_VID_PROFILE_LEVEL          INV_MPEG_ERRORS + 33
#define INV_VID_PROFILE_M              INV_MPEG_ERRORS + 34
#define INV_VID_PROFILE_CHROMA         INV_MPEG_ERRORS + 35
#define INV_VID_CHROMA_PROFILE         INV_MPEG_ERRORS + 36
#define INV_VID_PROFILE_FRATE_RFIRST   INV_MPEG_ERRORS + 37
#define INV_VID_PROF_FRATE_PSEQ_RFIRST INV_MPEG_ERRORS + 38
#define INV_VID_PROFILE_DC_PREC        INV_MPEG_ERRORS + 39
#define INV_VID_LEVEL_FRATE            INV_MPEG_ERRORS + 40
#define INV_VID_DEF_HORZ_PROFILE_LEVEL INV_MPEG_ERRORS + 41
#define INV_VID_DEF_VERT_PROFILE_LEVEL INV_MPEG_ERRORS + 42
#define INV_VID_DEF_HV_FRATE           INV_MPEG_ERRORS + 43
#define INV_VID_TYPE                   INV_MPEG_ERRORS + 44
#define INV_VID_MPEGN                  INV_MPEG_ERRORS + 45
#define INV_VID_MPEGM                  INV_MPEG_ERRORS + 46
#define INV_VID_MPEGN_M                INV_MPEG_ERRORS + 47
#define INV_VID_CONSTRPARMS            INV_MPEG_ERRORS + 48
#define INV_VID_PROG_SEQ_MPEG1         INV_MPEG_ERRORS + 49
#define INV_VID_CHROMA_MPEG1           INV_MPEG_ERRORS + 50
#define INV_VID_DC_PREC_MPEG1          INV_MPEG_ERRORS + 51
#define INV_VID_PULLDOWN_MPEG1         INV_MPEG_ERRORS + 52
#define INV_VID_QSCALE_MPEG1           INV_MPEG_ERRORS + 53
#define INV_VID_IVLC_MPEG1             INV_MPEG_ERRORS + 54
#define INV_VID_ALTSCAN_MPEG1          INV_MPEG_ERRORS + 55
#define INV_VID_CONSTPARMS_MPEG2       INV_MPEG_ERRORS + 56
#define INV_VID_PROG_SEQ_FRAME         INV_MPEG_ERRORS + 57
#define INV_VID_PFRAME_FIELDPIC        INV_MPEG_ERRORS + 58
#define INV_VID_PFRAME_RFIRST          INV_MPEG_ERRORS + 59
#define INV_VID_PFRAME_FRAME_PRED      INV_MPEG_ERRORS + 60
#define INV_VID_PSEQ_RFIRST_TFIRST     INV_MPEG_ERRORS + 61
#define INV_VID_CBRVBR_FIXED_VBV       INV_MPEG_ERRORS + 62
#define INV_VID_FH_FCODE_SXF           INV_MPEG_ERRORS + 63
#define INV_VID_FV_FCODE_SYF           INV_MPEG_ERRORS + 64
#define INV_VID_BH_FCODE_SXB           INV_MPEG_ERRORS + 65
#define INV_VID_BV_FCODE_SYB           INV_MPEG_ERRORS + 66

// defines for MPEG audio conformance check errors
#define INV_AUD_ERRORS                 0x00040000
#define INV_AUD_MODE                   INV_AUD_ERRORS + 0
#define INV_AUD_LAYER                  INV_AUD_ERRORS + 1
#define INV_AUD_PSYCH                  INV_AUD_ERRORS + 2
#define INV_AUD_BITRATE                INV_AUD_ERRORS + 3
#define INV_AUD_EMPHASIS               INV_AUD_ERRORS + 4
#define INV_AUD_PRIVATEBIT             INV_AUD_ERRORS + 5
#define INV_AUD_ERROR_PROT             INV_AUD_ERRORS + 6
#define INV_AUD_COPYRIGHT              INV_AUD_ERRORS + 7
#define INV_AUD_ORIGINAL               INV_AUD_ERRORS + 8
#define INV_AUD_SAMPLE_RATE            INV_AUD_ERRORS + 9

// defines for MPEG muxer conformance check errors
#define INV_MUX_ERRORS                 0x00080000
#define INV_MUX_TYPE                   INV_MUX_ERRORS + 0
#define INV_MUX_PULLDOWN               INV_MUX_ERRORS + 1
#define INV_MUX_PULLDOWN_MPEG1         INV_MUX_ERRORS + 2
#define INV_MUX_COMPUTED_BITRATE       INV_MUX_ERRORS + 3
#define INV_MUX_VCD_PAD                INV_MUX_ERRORS + 4
#define INV_MUX_VCD_PAD_NOVCD          INV_MUX_ERRORS + 5
#define INV_MUX_ALIGN_SH               INV_MUX_ERRORS + 6
#define INV_MUX_RATE                   INV_MUX_ERRORS + 7
#define INV_MUX_SECTOR_SIZE            INV_MUX_ERRORS + 8
#define INV_MUX_PACKETS_PER_PACK       INV_MUX_ERRORS + 9
#define INV_MUX_AVP_DELAY              INV_MUX_ERRORS + 10
#define INV_MUX_AUDIO1_BUFFER_SIZE     INV_MUX_ERRORS + 11
#define INV_MUX_AUDIO2_BUFFER_SIZE     INV_MUX_ERRORS + 12
#define INV_MUX_VIDEO_BUFFER_SIZE      INV_MUX_ERRORS + 13
#define INV_MUX_VBR                    INV_MUX_ERRORS + 14
#define INV_MUX_PEC                    INV_MUX_ERRORS + 15
#define INV_MUX_SCAN_OFFSETS           INV_MUX_ERRORS + 16
#define INV_MUX_SCAN_ALIGN             INV_MUX_ERRORS + 17
#define INV_MUX_PRIVATE2               INV_MUX_ERRORS + 18
#define INV_MUX_PRIVATE2_NODVD         INV_MUX_ERRORS + 19
#define INV_MUX_FRAME_TS               INV_MUX_ERRORS + 20
#define INV_MUX_MAX_FILE_SIZE          INV_MUX_ERRORS + 21
#define INV_MUX_START_TIME             INV_MUX_ERRORS + 22
#define INV_MUX_RESET_CLOCKS           INV_MUX_ERRORS + 23
#define INV_MUX_END_CODES              INV_MUX_ERRORS + 24
#define INV_MUX_BROKEN_LINK            INV_MUX_ERRORS + 25
#define INV_MUX_MPEG1_VID_MPEG2        INV_MUX_ERRORS + 26
#define INV_MPEG_LOW_MUX_RATE          INV_MUX_ERRORS + 27
#define INV_MUX_VBR_TS                 INV_MUX_ERRORS + 28

// defines for PCM audio conformance check errors
#define INV_PCM_ERRORS                 0x00100000
#define INV_PCM_SAMPLE_RATE            INV_PCM_ERRORS + 0
#define INV_PCM_CHANNELS               INV_PCM_ERRORS + 1
#define INV_PCM_MUTE_FLAG              INV_PCM_ERRORS + 2
#define INV_PCM_QUANTIZATION           INV_PCM_ERRORS + 3
#define INV_PCM_EMPHASIS               INV_PCM_ERRORS + 4

// defines for AC3 audio conformance check errors
#define INV_AC3_ERRORS                 0x00120000
#define INV_AC3_SAMPLE_RATE            INV_AC3_ERRORS + 0
#define INV_AC3_AUDIO_TYPE             INV_AC3_ERRORS + 1
#define INV_AC3_AUDIO_CHANNELS         INV_AC3_ERRORS + 2
#define INV_AC3_AUDIO_BITRATE          INV_AC3_ERRORS + 3
#define INV_AC3_AUDIO_CMODE            INV_AC3_ERRORS + 4
#define INV_AC3_AUDIO_COMP             INV_AC3_ERRORS + 5
#define INV_AC3_AUDIO_SECCOMP          INV_AC3_ERRORS + 6
#define INV_AC3_NOT_INSTALLED          INV_AC3_ERRORS + 7
#define INV_AC3_AUDIO_LFEENA           INV_AC3_ERRORS + 8
#define INV_AC3_AUDIO_LFEFILT          INV_AC3_ERRORS + 9
#define INV_AC3_AUDIO_DELAYSUR         INV_AC3_ERRORS + 10
#define INV_AC3_AUDIO_INCHAN           INV_AC3_ERRORS + 11
#define INV_AC3_AUDIO_FL               INV_AC3_ERRORS + 12
#define INV_AC3_AUDIO_FR               INV_AC3_ERRORS + 13
#define INV_AC3_AUDIO_CENT             INV_AC3_ERRORS + 14
#define INV_AC3_AUDIO_LS               INV_AC3_ERRORS + 15
#define INV_AC3_AUDIO_RS               INV_AC3_ERRORS + 16
#define INV_AC3_AUDIO_LFE              INV_AC3_ERRORS + 17


//-- AAC audio defines ----------------------------------------------

/**
 * @name AAC audio conformance check errors
 * @{
 **/
#define INV_AAC_ERRORS                  0x00200000
#define INV_AAC_CHANNELS                INV_AAC_ERRORS +  0
#define INV_AAC_OBJECT_TYPE             INV_AAC_ERRORS +  1
#define INV_AAC_BITRATE                 INV_AAC_ERRORS +  2
#define INV_AAC_MPEG_VERSION            INV_AAC_ERRORS +  3
#define INV_AAC_SAMPLE_RATE             INV_AAC_ERRORS +  4
#define INV_AAC_HEADER_TYPE             INV_AAC_ERRORS +  5
#define INV_AAC_HF_CUTOFF               INV_AAC_ERRORS +  6
#define INV_AAC_VBR                     INV_AAC_ERRORS +  7
#define INV_AAC_HE_SIGNALLING           INV_AAC_ERRORS +  8
#define INV_AAC_HE_VS_SAMPLERATE        INV_AAC_ERRORS +  9
#define INV_AAC_HE_VS_VBR               INV_AAC_ERRORS + 10
#define INV_AAC_HE_V2_CHANNELS          INV_AAC_ERRORS + 11
#define INV_AAC_HE_NO_PROFILE           INV_AAC_ERRORS + 12
#define INV_AAC_BITS_PER_SAMPLE         INV_AAC_ERRORS + 13
#define INV_AAC_SONY_AAC                INV_AAC_ERRORS + 14
#define INV_AAC_CRC_PROTECTION          INV_AAC_ERRORS + 15
/** @} */

/**
 * @name The errors below are applied to Fraunhofer AAC Encoder only
 * @{
 **/
#define INV_MD_DRC_PROFILE              INV_AAC_ERRORS + 50
#define INV_MD_COMP_PROFILE             INV_AAC_ERRORS + 51
#define INV_MD_DRC_TARGET_REF_LEVEL     INV_AAC_ERRORS + 52
#define INV_MD_COMP_TARGET_REF_LEVEL    INV_AAC_ERRORS + 53
#define INV_MD_DRC_EXT                  INV_AAC_ERRORS + 54
#define INV_MD_COMP_EXT                 INV_AAC_ERRORS + 55
#define INV_MD_PROG_REF_LEVEL_PRESENT   INV_AAC_ERRORS + 56
#define INV_MD_PROG_REF_LEVEL           INV_AAC_ERRORS + 57
#define INV_MD_PCE_MIXDOWN_IDX_PRESENT  INV_AAC_ERRORS + 58
#define INV_MD_ETSI_DMX_LVL_PRESENT     INV_AAC_ERRORS + 59
#define INV_MD_CENTER_MIX_LEVEL         INV_AAC_ERRORS + 60
#define INV_MD_SURROUND_MIX_LEVEL       INV_AAC_ERRORS + 61
#define INV_MD_DOLBY_SURROUND_MODE      INV_AAC_ERRORS + 62
#define INV_MD_DRC_PRESENTATION_MODE    INV_AAC_ERRORS + 63
#define INV_MD_DC_FILTER                INV_AAC_ERRORS + 64
#define INV_MD_LFE_LOWPASS_FILTER       INV_AAC_ERRORS + 65
#define INV_MD_SUR_PHASE90              INV_AAC_ERRORS + 66
#define INV_MD_SUR_ATT3DB               INV_AAC_ERRORS + 67

#define INV_AAC_CH_MODE                 INV_AAC_ERRORS + 100
#define INV_AAC_SBR_SIGNALING           INV_AAC_ERRORS + 101
#define INV_AAC_METADATA_MODE           INV_AAC_ERRORS + 102
#define INV_AAC_GRANULE_LENGTH          INV_AAC_ERRORS + 103
#define INV_AAC_QUALITY                 INV_AAC_ERRORS + 104
#define INV_AAC_DASH_SEGMENTATION       INV_AAC_ERRORS + 105
/** @} */

/**
 * @name AAC bitrates
 * @{
 **/
#define AAC_AUDIOBITRATE_CUSTOM 0       ///<   Custom audio bitrate
#define AAC_AUDIOBITRATE_006  1			///<   6 kbits/sec
#define AAC_AUDIOBITRATE_007  2			///<   7 kbits/sec
#define AAC_AUDIOBITRATE_008  3			///<   8 kbits/sec
#define AAC_AUDIOBITRATE_010  4			///<   10 kbits/sec
#define AAC_AUDIOBITRATE_012  5			///<   12 kbits/sec
#define AAC_AUDIOBITRATE_014  6			///<   14 kbits/sec
#define AAC_AUDIOBITRATE_016  7			///<   16 kbits/sec
#define AAC_AUDIOBITRATE_020  8			///<   20 kbits/sec
#define AAC_AUDIOBITRATE_024  9			///<   24 kbits/sec
#define AAC_AUDIOBITRATE_028 10			///<   28 kbits/sec
#define AAC_AUDIOBITRATE_032 11			///<   32 kbits/sec
#define AAC_AUDIOBITRATE_040 12			///<   40 kbits/sec
#define AAC_AUDIOBITRATE_048 13			///<   48 kbits/sec
#define AAC_AUDIOBITRATE_056 14			///<   56 kbits/sec
#define AAC_AUDIOBITRATE_064 15			///<   64 kbits/sec
#define AAC_AUDIOBITRATE_080 16			///<   80 kbits/sec
#define AAC_AUDIOBITRATE_096 17			///<   96 kbits/sec
#define AAC_AUDIOBITRATE_112 18			///<   112 kbits/sec
#define AAC_AUDIOBITRATE_128 19			///<   128 kbits/sec
#define AAC_AUDIOBITRATE_160 20			///<   160 kbits/sec
#define AAC_AUDIOBITRATE_192 21			///<   192 kbits/sec
#define AAC_AUDIOBITRATE_224 22			///<   224 kbits/sec
#define AAC_AUDIOBITRATE_256 23			///<   256 kbits/sec
#define AAC_AUDIOBITRATE_320 24			///<   320 kbits/sec
#define AAC_AUDIOBITRATE_384 25			///<   384 kbits/sec
#define AAC_AUDIOBITRATE_448 26			///<   448 kbits/sec
#define AAC_AUDIOBITRATE_512 27			///<   512 kbits/sec
#define AAC_AUDIOBITRATE_640 28			///<   640 kbits/sec
#define AAC_AUDIOBITRATE_768 29			///<   768 kbits/sec
#define AAC_AUDIOBITRATE_896 30			///<   896 kbits/sec
#define AAC_AUDIOBITRATE_1024 31		///<   1024 kbits/sec
/** @} */

/**
 * @name Number of channels and speaker position
 * @{
 **/
#define AAC_CHANNELS_1_MONO 1						///<   one channel, mono mode, front center speaker
#define AAC_CHANNELS_2_STEREO 2 					///<   two channels, stereo mode, front left-right
#define AAC_CHANNELS_3_FL_FR_FC 3					///<   three channels, front left-right-center
#define AAC_CHANNELS_4_FL_FR_FC_BC 4				///<   four channels, front left-right-center, back center
#define AAC_CHANNELS_5_FL_FR_FC_BL_BR 5				///<   five channels, front left-right-center, back left-right
#define AAC_CHANNELS_6_FL_FR_FC_BL_BR_LF 6			///<   six channels, name is missleading, use @ref AAC_CHANNELS_6_FL_FR_FC_LF_BL_BR instead
#define AAC_CHANNELS_6_FL_FR_FC_LF_BL_BR AAC_CHANNELS_6_FL_FR_FC_BL_BR_LF 	///<   six channels, front left-right-center, subwoofer,back left-right (this is 5.1 surround configuration)
#define AAC_CHANNELS_8_FL_FR_FC_LF_BL_BR_SL_SR 8 	///<   eight channels, front left-right-center, back left-right, side left-right (this is 7.1 surround configuration)
/** @} */

/**
 * @name For backward compatibility reasons
 * @{
 **/
#define AAC_CHANNELS_MONO       AAC_CHANNELS_1_MONO
#define AAC_CHANNELS_STEREO     AAC_CHANNELS_2_STEREO
/** @} */

/**
 * @name Audio channel mode
 * @{
 **/
#define AAC_CH_MODE_AUTO    0             ///< Auto
#define AAC_CH_MODE_7_1_FRONT_CHANNEL 7   ///< 7.1 Front channels audio ( center + left/right front speakers + left/right front center speakers + left/right surround speakers + LFE )
#define AAC_CH_MODE_7_1_BACK_CHANNEL 12   ///< 7.1 Back channels audio ( center + left/right front speakers + left/right rear surround speakers  + left/right surround speakers + LFE )
/** @} */

/**
 * @name Bits per PCM sample at input
 * @{
 **/
#define AAC_BITS_PER_SAMPLE_08  8		///<   8 bits - one byte per sample
#define AAC_BITS_PER_SAMPLE_16 16		///<   16 bits - two bytes per sample
#define AAC_BITS_PER_SAMPLE_24 24		///<   24 bits - three bytes per sample
/** @} */

/**
 * @name Audio object type (mpeg-4 version)
 * @{
 **/
#define AAC_LC                2 ///< use "low complexity" audio object
/**
 * @name The audio object types below are applied to Fraunhofer AAC Encoder only
 * @{
 **/
#define AAC_HEAAC             5 ///< AAC LC + SBR
#define AAC_ER_LC            17 ///< ER AAC LC
#define AAC_PS               29 ///< AAC LC + SBR + PS
#define AAC_MP2_LC          129 ///< virtual AOT MP2 Low Complexity Profile
#define AAC_MP2_SBR         132 ///< virtual AOT MP2 Low Complexity Profile with SBR
#define AAC_SBR_DS          133 ///< virtual AOT for downsampled SBR
/** @} */

/**
 * @name Header type
 * @{
 **/
#define AAC_HEADER_RAW          0 ///< no header
#define AAC_HEADER_ADTS         1 ///< ADTS header
#define AAC_HEADER_LATMLOAS     2 ///< LATM in LOAS header
#define AAC_HEADER_ADIF         3 ///< ADIF header
#define AAC_HEADER_LOAS_NOSMC   4 ///< LOAS (StreamMuxConfig signaled out-of-band) header
#define AAC_HEADER_LATM         5 ///< LATM header
#define AAC_HEADER_LATM_NOSMC   6 ///< LATM (StreamMuxConfig signaled out-of-band) header
/** @} */


/**
 * @name Cut-off frequency (can also be a number between 1000 and 48000, Hz)
 * @{
 **/
#define AAC_CUTOFF_DEFAULT 0		///<   use the default value for given sampling frequency
#define AAC_CUTOFF_NOTUSED 1		///<   cut-off not used, keep all frequencies
/** @} */

/**
 * @name Variable bitrate mode
 * @{
 **/
#define AAC_VBR_NOTUSED		0 ///<  vbr mode not used
#define AAC_VBR_LOW1        1 ///<  low quality vbr mode 1 (worst quality)
#define AAC_VBR_LOW2        2 ///<  low quality vbr mode 2
#define AAC_VBR_LOW3        3 ///<  low quality vbr mode 3
#define AAC_VBR_MEDIUM1		4 ///<  medium quality vbr mode 1
#define AAC_VBR_MEDIUM2		5 ///<  medium quality vbr mode 2
#define AAC_VBR_MEDIUM3		6 ///<  medium quality vbr mode 3
#define AAC_VBR_HIGH1       7 ///<  high quality vbr mode 1
#define AAC_VBR_HIGH2       8 ///<  high quality vbr mode 2
#define AAC_VBR_HIGH3       9 ///<  high quality vbr mode 3 (best quality)
/** @} */

/**
 * @name Bit Rate Modes for Fraunhofer AAC Encoder
 * @{
 **/
#define FHG_AAC_CBR      0 ///< VBR mode is not used
#define FHG_AAC_VBR_1    1 ///< Variable, very low
#define FHG_AAC_VBR_2    2 ///< Variable, low
#define FHG_AAC_VBR_3    3 ///< Variable, medium
#define FHG_AAC_VBR_4    4 ///< Variable, high
#define FHG_AAC_VBR_5    5 ///< Variable, very high
#define FHG_AAC_VBR_6    6 ///< Variable, extremely high
#define FHG_AAC_SFR      7 ///< Superframing
#define FHG_AAC_DABPLUS  8 ///< Superframing + DAB + constraints
#define FHG_AAC_DRMPLUS  9 ///< Superframing + DRM + constraints
#define FHG_AAC_DMB     10 ///<
/** @} */

/**
 * @name HE signaling
 * @{
 **/
#define AAC_HE_NOTUSED                          0 ///< HE not used
#define AAC_HE_IMPLICIT                         1 ///< HE v1 used and implicitly signaled in the bitstream
#define AAC_HE_IMPLICIT_WITH_PS                 2 ///< HE v2 used and implicitly signaled in the bitstream
// #define AAC_HE_EXPLICIT_HIERARCHICAL
// #define AAC_HE_EXPLICIT_BACKWARD_COMPATIBLE
/** @} */

/**
 * @name CRC protection
 * @{
 **/
#define AAC_PROTECT_ADTS_STREAM_NO 0		///<  stream is not protected
#define AAC_PROTECT_ADTS_STREAM_YES 1 		///<  stream is protected
/** @} */

/**
 * @name Temporal Noise Shaping
 * @{
 **/
#define AAC_TNS_NO 0			///<  TNS not used
#define AAC_TNS_YES 1			///<  TNS used
/** @} */

/**
 * @name SBR signaling
 * @{
 **/
#define FHG_AAC_SBR_SIG_IMPLICIT  0 ///< Implicit backward compatible signaling (signaling 1)
#define FHG_AAC_SBR_SIG_EXPL_BC   1 ///< Explicit backward compatible signaling (signaling 2.B.)
#define FHG_AAC_SBR_SIG_EXPL_HIER 2 ///< Explicit hierarchical signaling, non backward compatible (signaling 2.A.)
/** @} */

/**
 * @name Metadata modes
 * @{
 **/
#define FHG_AAC_METADATA_NONE       0 ///< do not embed any metadata
#define FHG_AAC_METADATA_MPEG       1 ///< embed MPEG defined metadata only
#define FHG_AAC_METADATA_MPEG_ETSI  2 ///< embed all metadata (MPEG DRC and ETSI ancillary data)
/** @} */

/**
 * @name Granule length
 * @{
 **/
#define FHG_AAC_GRANULE_960       960 ///< 960 samples
#define FHG_AAC_GRANULE_1024     1024 ///< 1024 samples
/** @} */

/**
 * @name Encoding quality level
 * @{
 **/
#define FHG_AAC_QUAL_FAST           0 ///< Fastest operation, some quality compromises
#define FHG_AAC_QUAL_MEDIUM         1 ///< Good quality, slightly slower operation (default)
#define FHG_AAC_QUAL_HIGH           2 ///< Very good quality, notably slower operation
#define FHG_AAC_QUAL_HIGHEST        3 ///< Highest quality, forces preferred sampling rate
/** @} */

/**
 * @name DRC profile
 * @{
 **/
#define FHG_AAC_DRC_NONE            0 ///< No compression, but active limiter functionality
#define FHG_AAC_DRC_FILMSTANDARD    1 ///< Compression as known in broadcast applications (plus overloaded limiter)
#define FHG_AAC_DRC_FILMLIGHT       2 ///< Compression as known in broadcast applications (plus overloaded limiter)
#define FHG_AAC_DRC_MUSICSTANDARD   3 ///< Compression as known in broadcast applications (plus overloaded limiter)
#define FHG_AAC_DRC_MUSICLIGHT      4 ///< Compression as known in broadcast applications (plus overloaded limiter)
#define FHG_AAC_DRC_SPEECH          5 ///< Compression as known in broadcast applications (plus overloaded limiter)
#define FHG_AAC_DRC_EMBED_EXTERN   -1 ///< Embed externally fed values (mainly used if values were transcoded)
#define FHG_AAC_DRC_NOT_PRESENT    -2 ///< Disable writing gain factor (used for comp_profile only)
/** @} */

/**
 * @name Downmix level
 * @{
 **/
#define FHG_AAC_DMX_GAIN_0_dB       0 ///<
#define FHG_AAC_DMX_GAIN_1_5_dB     1 ///<
#define FHG_AAC_DMX_GAIN_3_dB       2 ///<
#define FHG_AAC_DMX_GAIN_4_5_dB     3 ///<
#define FHG_AAC_DMX_GAIN_6_dB       4 ///<
#define FHG_AAC_DMX_GAIN_7_5_dB     5 ///<
#define FHG_AAC_DMX_GAIN_9_dB       6 ///<
#define FHG_AAC_DMX_GAIN_INF        7 ///<
/** @} */

/**
 * @name Dolby Surround indication
 * @{
 **/
#define FHG_AAC_DSUR_NOT_INDICATED  0 ///< Dolby Surround mode not indicated
#define FHG_AAC_DSUR_NOT_USED       1 ///< 2-ch audio part is not Dolby surround encoded
#define FHG_AAC_DSUR_IS_USED        2 ///< 2-ch audio part is Dolby surround encoded
/** @} */

/**
 * @name DRC presentation mode indication (see ETSI TS 101 154 V1.11.1, section C.5.2.2.3 and C.5.3)
 * @{
 **/
#define FHG_AAC_DRC_PRESENTATION_NOT_INDICATED  0 ///< DRC presentation mode not indicated
#define FHG_AAC_DRC_PRESENTATION_MODE_1         1 ///< DRC presentation mode 1
#define FHG_AAC_DRC_PRESENTATION_MODE_2         2 ///< DRC presentation mode 2
/** @} */

/**
 * @name Channel mode
 * @{
 **/
#define FHG_AAC_CH_MODE_AUTO                 0 ///< auto
#define FHG_AAC_CH_MODE_MONO                 1 ///< 1   channel mono
#define FHG_AAC_CH_MODE_STEREO               2 ///< 2   channel stereo
#define FHG_AAC_CH_MODE_3                    3 ///< 3   channel audio ( center + left/right front                       speaker       )
#define FHG_AAC_CH_MODE_4                    4 ///< 4   channel audio ( center + left/right front +     rear   surround speaker       )
#define FHG_AAC_CH_MODE_5                    5 ///< 5   channel audio ( center + left/right front + left/right surround speaker       )
#define FHG_AAC_CH_MODE_5_1                  6 ///< 5.1 channel audio ( center + left/right front + left/right surround speaker + LFE )
#define FHG_AAC_CH_MODE_7_1                  7 ///< 7.1 channel audio ( center + left/right front + left/right outside front + left/right surround speakers + LFE )
#define FHG_AAC_CH_MODE_7_1_SIDE_CHANNEL     8 ///< 7.1 channel audio ( center + left/right front + left/right side channels + left/right surround speakers + LFE )
#define FHG_AAC_CH_MODE_7_1_REAR_SURROUND    9 ///< 7.1 channel audio ( center + left/right front + left/right rear surround speakers  + left/right surround speakers + LFE )
#define FHG_AAC_CH_MODE_7_1_FRONT_CENTER    10 ///< 7.1 channel audio ( center + left/right front + left/right frontal center speakers + left/right surround speakers + LFE )
#define FHG_AAC_CH_MODE_DUAL_MONO           11 ///< 2   independent channels
#define FHG_AAC_CH_MODE_4TIMES1             12 ///< 4   independent channels
#define FHG_AAC_CH_MODE_6TIMES1             13 ///< 6   independent channels
#define FHG_AAC_CH_MODE_8TIMES1             14 ///< 8   independent channels
#define FHG_AAC_CH_MODE_12TIMES1            15 ///< 12  independent channels
#define FHG_AAC_CH_MODE_2TIMES2             16 ///< 2   stereo channel pairs
#define FHG_AAC_CH_MODE_3TIMES2             17 ///< 3   stereo channel pairs
#define FHG_AAC_CH_MODE_4TIMES2             18 ///< 4   stereo channel pairs
/** @} */

/**
 * @name DASH segmentation
 * @{
 **/
#define FHG_AAC_DASH_SEGMENTATION_DISABLED   0 ///< DASH segmentation is disabled (default value)
#define FHG_AAC_DASH_SEGMENTATION_ENABLED    1 ///< DASH segmentation is enabled
/** @} */

/**
 * @name AAC output return codes
 * @{
 **/
#define aacOutErrNone  0 ///< no error
#define aacOutCancel   1 ///< user canceled settings
#define aacOutError    2 ///< undefined error
#define aacOutDecline  3 ///< unable to use input settings, resolution, audio etc.
/** @} */

//-- WMA audio defines ----------------------------------------------

// defines for WMA audio conformance check errors
#define INV_WMA_ERRORS                  0x00400000
#define INV_WMA_NO_ERROR                INV_WMA_ERRORS +  0
#define INV_WMA_CHANNELS                INV_WMA_ERRORS +  1
#define INV_WMA_SAMPLE_RATE             INV_WMA_ERRORS +  2
#define INV_WMA_BITRATE                 INV_WMA_ERRORS +  3

// defines for WMA bitrates:

#define WMA_AUDIOBITRATE_006  1
#define WMA_AUDIOBITRATE_007  2
#define WMA_AUDIOBITRATE_008  3
#define WMA_AUDIOBITRATE_010  4
#define WMA_AUDIOBITRATE_012  5
#define WMA_AUDIOBITRATE_014  6
#define WMA_AUDIOBITRATE_016  7
#define WMA_AUDIOBITRATE_020  8
#define WMA_AUDIOBITRATE_024  9
#define WMA_AUDIOBITRATE_028 10
#define WMA_AUDIOBITRATE_032 11
#define WMA_AUDIOBITRATE_040 12
#define WMA_AUDIOBITRATE_048 13
#define WMA_AUDIOBITRATE_056 14
#define WMA_AUDIOBITRATE_064 15
#define WMA_AUDIOBITRATE_080 16
#define WMA_AUDIOBITRATE_096 17
#define WMA_AUDIOBITRATE_112 18
#define WMA_AUDIOBITRATE_128 19
#define WMA_AUDIOBITRATE_160 20
#define WMA_AUDIOBITRATE_192 21
#define WMA_AUDIOBITRATE_224 22
#define WMA_AUDIOBITRATE_256 23
#define WMA_AUDIOBITRATE_320 24
#define WMA_AUDIOBITRATE_384 25
#define WMA_AUDIOBITRATE_448 26
#define WMA_AUDIOBITRATE_512 27
#define WMA_AUDIOBITRATE_640 28
#define WMA_AUDIOBITRATE_768 29
#define WMA_AUDIOBITRATE_896 30
#define WMA_AUDIOBITRATE_1024 31

// defines for number of channels and speaker possition:

#define WMA_CHANNELS_1_MONO                 1 // front center speaker
#define WMA_CHANNELS_2_STEREO               2 // front left-right
#define WMA_CHANNELS_3_FL_FR_FC             3 // front left-right-center
#define WMA_CHANNELS_4_FL_FR_FC_BC          4 // front left-right-center, back center
#define WMA_CHANNELS_5_FL_FR_FC_BL_BR       5 // front left-right-center, back left-right
#define WMA_CHANNELS_6_FL_FR_FC_BL_BR_LF    6 // front left-right-center, back left-right, subwoofer

// for backward compatibility reasons:

#define WMA_CHANNELS_MONO       WMA_CHANNELS_1_MONO
#define WMA_CHANNELS_STEREO     WMA_CHANNELS_2_STEREO

// defines for aac output return codes

#define wmaOutErrNone   0   // no error
#define wmaOutCancel    1   // user canceled settings
#define wmaOutError     2   // undefined error
#define wmaOutDecline   3   // unable to use input settings, resolution, audio etc.

//---- MPD Combiner defines------------------------------------------------
/**
 * @name MPD Combiner errors
 * @{
*/
#define mpdCombinerErrNone          0   ///< No error
#define mpdCombinerEmptyInstance    1   ///< Error: empty instance
#define mpdCombinerInvalidNumMpd    2   ///< Error: invalid number of input mpd files
#define mpdCombinerInvalidInputMpd  3   ///< Error: invalid input names of mpd files
#define mpdCombinerErrorMpdRead     4   ///< Error of mpd file reading
#define mpdCombinerErrorMpdCreation 5   ///< Error of mpd file creation
#define mpdCombinerErrorMpdWrite    6   ///< Error of file writing
#define mpdCombinerDifSegmDuration      7   ///< Error: different segment durations in one Adaptation Set
/** @} */

//---- DMF muxer defines --------------------------------------------------
#define DMF_AVI1    0       // AVI container type 1
#define DMF_AVI2    1       // AVI container type 2
#define DMF_MKV     2       // MKV container
#define DMF_DPSMKV  3       // MKV container, DPS style

// DMF muxer conformance check error defines
#define INV_DMF_ERRORS                  0x00095000
#define INV_DMF_NO_ERROR                INV_DMF_ERRORS +  0
#define INV_DMF_MODULE_ID               INV_DMF_ERRORS +  1

//---------------------- MP3 ENCODE ----------------------------------------

// defines for MP3 audio conformance check errors
#define INV_MP3_ERRORS                  0x00410000
#define INV_MP3_NO_ERROR                INV_MP3_ERRORS +  0
#define INV_MP3_CHANNELS                INV_MP3_ERRORS +  1
#define INV_MP3_SAMPLE_RATE             INV_MP3_ERRORS +  2
#define INV_MP3_BITRATE                 INV_MP3_ERRORS +  3
#define INV_MP3_QUALITY                 INV_MP3_ERRORS +  4

#define MP3_CHANNELS_1_MONO                             1 // front center speaker
#define MP3_CHANNELS_2_STEREO                           2 // front left-right
#define MP3_CHANNELS_6_FL_FR_FC_LF_BL_BR                6 // front left-right-center, , subwoofer, back left-right

#define MP3_CHANNELS_MONO       MP3_CHANNELS_1_MONO
#define MP3_CHANNELS_STEREO     MP3_CHANNELS_2_STEREO
#define MP3_CHANNELS_SURROUND   MP3_CHANNELS_6_FL_FR_FC_LF_BL_BR

#define MP3_QUALITY_FAST        0 // encode as it is, no resampling
#define MP3_QUALITY_HIGH        1 // downsample is possible, increases quality

// defines for mp3 output return codes
#define mp3OutErrNone   0   // no error
#define mp3OutCancel    1   // user canceled settings
#define mp3OutError     2   // undefined error
#define mp3OutDecline   3   // unable to use input settings, resolution, audio etc.

/** \defgroup video_dec_mpeg_group MPEG Video Decoder defines
\{
*/
/**\brief parser return code flags

\attention if doing reordering output picture params are related to reordered picture and not to current (in stream) picture

FRAME_BUFFERED_FLAG means: once more frame is available.
\arg first I-frame parced: VALID_FLAG is not set, FRAME_BUFFERED_FLAG is set.
\arg current B-Frame:      VALID_FLAG is set,     FRAME_BUFFERED_FLAG is set.
\arg last Frame: FRAME_BUFFERED_FLAG is set
\arg To peek buffered frames one need to repeat
     PARCE_FRAME-copybyte(NULL,0)-GET_STSTUS sequence
     while FRAME_BUFFERED_FLAG is set or VALID_FLAG is set

*/
enum parse_flags
{
  PARSE_DONE_FLAG   = 0x00000001, /**< last parse operation was OK, current stream state related */
  PARSE_ERR_FLAG    = 0x00000002, /**< error in stream detected */

  SEQ_HDR_FLAG      = 0x00000100, /**<  next flags are related to */
  EXT_CODE_FLAG     = 0x00000200, /**<  current stream state and means parsed */
  GOP_HDR_FLAG      = 0x00000400, /**<  elements of MPEG syntax */
  PIC_HDR_FLAG      = 0x00000800, /**<  elements of MPEG syntax */

  USER_DATA_FLAG    = 0x00001000, /**<  elements of MPEG syntax */
  SEQ_END_FLAG      = 0x00002000, /**<  elements of MPEG syntax */
  SLICE_START_FLAG  = 0x00004000, /**<  elements of MPEG syntax */
  UNKNOWN_CODE_FLAG = 0x00008000, /**<  elements of MPEG syntax */
  START_CODE_FLAG   = 0x00010000, /**<  elements of MPEG syntax */
  SEQ_EXT_HDR_FLAG  = 0x00020000, /**<  elements of MPEG syntax */

  SEQ_HDR_IN_FLAG   = 0x00040000, /**<  signal of appearing SPS in a stream (dec h264) */
  PIC_HDR_IN_FLAG   = 0x00080000, /**<  signal of appearing PPS in a stream (dec h264) */

  PIC_DECODED_FLAG  = 0x00100000, /**<  current picture in stream decoded */
  PIC_FULL_FLAG     = 0x00200000, /**<  output picture is full decoded (seen last makroblock) */
  PIC_VALID_FLAG    = 0x00400000, /**<  output picture is decoded (at least first makroblock) */
  FRAME_BUFFERED_FLAG=0x00800000, /**<  show that there picture in reordering buffer */
  PIC_ERROR_FLAG    = 0x01000000, /**<  output picture has some errors */
  PIC_MV_ERROR_FLAG = 0x02000000, /**<  output picture has motion-vector errors (clipped in decoder) */

  SEI_FLAG          = 0x04000000, /**<  elements of MPEG syntax */
  VID_HDR_FLAG      = 0x08000000, /**<  elements of MPEG syntax */

  INTERNAL_ERROR    = 0x10000000, /**<  out of memory*/
  PIC_REF_ERROR_FLAG= 0x20000000  /**<  output picture has errors on reference pictures. */
};
/** \} */



////////////////////////////////
//
/** \defgroup auxinfo_group Parser auxillery commands
@{
*/
/** \brief auxillery commands*/
enum parse_aux
{
  PARSE_INIT           = 0x00010000, /**<  clear parser-state, save-buffer etc. Call it after seeking \ingroup hevc_aux_cmd */
  PARSE_FRAMES         = 0x00010001, /**<  set video parser to parse frame-header/data, setup output-frame \ingroup hevc_aux_cmd */
  PARSE_OPTIONS        = 0x00010002, /**<  set decoder options \ingroup hevc_aux_cmd */
  PARSE_AUD_HDR        = 0x00010FFF, /**<  set audio parser to parse sample-header/data */

  GET_PARSE_STATE      = 0x00010003, /**<  Get the actual state of the decoder. This is normally done after a copybyte call  */
  GET_SEQ_PARAMSP      = 0x00010004, /**<  Get the sequence header parameters after decoding is done  */
  GET_SEQ_PARAMSPEX    = 0x00010014, /**<  Get the extended video sequence paremeters after decoding is done */
  GET_GOP_PARAMSP      = 0x00010005, /**<  Get group of pictures header after decoding is done  */
  GET_PIC_PARAMSP      = 0x00010006, /**<  Get the picture parameters after decoding is done  */
  GET_PIC              = 0x00010007, /**<   can be sent to both the subpic and video decoders */
  SET_USER_DATA        = 0x00010008, /**<   Add additional data for the next vs->copybyte call. The user data will be attached to the first frames header and returned with this frame. To get this data after a PARSE_FRAME is completed use the GET_USER_DATAP command. This is normally used for time stamp information. */
  GET_USER_DATAP       = 0x00010009, /**<  Retrieve data, which was previously attached to some data by the SET_USER_DATA command.  */
  // use these messages to get video frames from the decoder
  // with a subpic overlayed
  GET_PIC_WITH_SP      = 0x0001000A, /**<   send to get a frame with subpic overlayed */
  PARSE_FRAMES_WITH_SP = 0x0001000B, /**<  set video parser to parse frame-header/data, setup output-frame with subpic overlay */

  PARSE_INIT_AFTER_SEEK= 0x0001000C, /**<    */
  GET_DECODED_PIC_PAR  = 0x0001000D, /**<    */
  GET_DECODED_PIC      = 0x0001000E, /**<    */

  GET_PIC_PARAMSPEX    = 0x0001000F, /**<   get video picture header and coding extension (MPEG2/AVC only) */

  CLEAN_PARSE_STATE    = 0x00010010, /**<   return actual and clear parse state */
  GET_PARSE_SETTINGS   = 0x00010011, /**<   get the parser settings */
  PUT_PARSE_SETTINGS   = 0x00010012, /**<   put the parser settings  */

  GET_PIC_TYPE         = 0x00010013, /**<   Get picture type */
  PARSE_CLOSE          = 0x00010015, /**<   Close decoder */

  GET_OVERLAY          = 0x00010020, /**<   overlay a subpic on a frame */
  GET_LAST_PTS         = 0x00010021, /**<   get the last subpic PTS available */
  GET_PALETTE          = 0x00010022, /**<   get the subpicture palette, using subpic_palette_tt below */
  // can be sent to both the subpic and video decoders
  SET_PALETTE          = 0x00010023, /**<   set the subpicture palette, using subpic_palette_tt below */
  // can be sent to both the subpic and video decoders
  SET_SP_PTS           = 0x00010024, /**<   send the PTS for the current input subpic */
  SET_PIC_PTS          = 0x00010025, /**<   set the PTS of the frame for which a subpic will be requested */
  // with either GET_PIC or GET_OVERLAY
  INIT_FRAME_PARSER    = 0x00010202, /**<   init parser (allocate memory etc.) to be able to decode */
  // stream with seq-header defined parameters

  GET_STREAM_USER_DATA = 0x000101B2, /**<    */
  PARSE_SEQ_HDR        = 0x000101B3, /**<   decode the next data for any header */
//  PARSE_GOP_HDR        = 0x000101B8, //unused
//  SEARCH_PIC_HDR       = 0x00000100, //unused

  GET_SEQ_EXT_PARAMSP  = 0x000101B4, /**<  Get sequence extension header after decoding is done  */

  // extra Dolby Digital decoder commands
  DD_GET_CONFIG_INFO   = 0x00020001, /**<    */
  DD_GET_GEN_INFO      = 0x00020002, /**<    */
  DD_GET_MIX_INFO      = 0x00020003, /**<    */
  DD_GET_PROD_INFO     = 0x00020004, /**<    */
  DD_GET_TIMECODE_INFO = 0x00020005, /**<    */
  DD_GET_ADDBSI_INFO   = 0x00020006, /**<    */
  DD_GET_AUXDATA_INFO  = 0x00020007, /**<    */
  DD_GET_METADATA_INFO = 0x00020008, /**<    */

  PARSE_REINIT         = 0x00030001, /**<   reinitialize wma decoder */
  SET_CPU_NUM          = 0x000101B5, /**<  Sets number of logical CPUs, which can be used in specified SMP mode by the SET_SMP_MODE command  */
  GET_SEI              = 0x000101B6, /**<   Get sei messages after decoding is done. */
  SET_SMP_MODE         = 0x000101B7, /**<  Sets symmetric multiprocessing (SMP) mode of decoding.  */
  GET_SEI_PARAMS       = 0x000101B8, /**<    */
  GET_IN_SEQ_PARAMSP   = 0x000101b9, /**<  Get the sequence header parameters from input elementary stream */
  GET_IN_SEQ_PARAMSPEX = 0x000101ba, /**<  Get the extended video sequence paremeters from input elementary stream */
  SET_NALU_BUF_SIZE    = 0x000101bb, /**<  Set NALU buffer size for parser*/

  DEC_AVC_RESERVED_00010081 = 0x00010081,
  DEC_AVC_RESERVED_00010082 = 0x00010082,
  DEC_AVC_RESERVED_00010083 = 0x00010083,
  DEC_AVC_RESERVED_00010084 = 0x00010084,
  SET_LOOP_FILTER_MODE      = 0x00010085, /**< Set loop filter mode option \hideinitializer */
  DEC_AVC_RESERVED_00010086 = 0x00010086,
  DEC_AVC_RESERVED_00010087 = 0x00010087,
  DEC_AVC_RESERVED_00010088 = 0x00010088,
  DEC_AVC_RESERVED_00010089 = 0x00010089,
  SET_MV_PRECISION          = 0x0001008a, /**< Limits precision of motion vectors option \hideinitializer */
  DEC_AVC_RESERVED_0001008b = 0x0001008b,
  DEC_AVC_RESERVED_0001008c = 0x0001008c,
  DEC_AVC_RESERVED_0001008d = 0x0001008d,
  SET_DECODE_BASE_LAYERS	= 0x0001008e, /**<  Enable/Disable base layers decoding. SVC decoder's stuff   */
  DEC_AVC_RESERVED_0001008f = 0x0001008f,
  DEC_AVC_RESERVED_00010090 = 0x00010090,
  DEC_AVC_RESERVED_00010091 = 0x00010091,
  DEC_AVC_RESERVED_00010092 = 0x00010092,
  SET_MAX_DQT				= 0x00010300, /**< Set maximum allowed D,Q,T layer. SVC decoder's stuff  */
  GET_LAYER_DQT				= 0x00010301, /**< Get the current layer D,Q,T after decoding is done. SVC decoder's stuff  */
  DEC_AVC_RESERVED_00010302 = 0x00010302,
  DEC_AVC_RESERVED_00010303 = 0x00010303,
  DEC_AVC_RESERVED_00010304 = 0x00010304,
  DEC_AVC_RESERVED_00010305 = 0x00010305,
  SET_TEMPORAL_ID			= 0x00010306, /**<    */

  // Analysis API
  ANALYSIS_OPTIONS      = 0x00010093, /**<    */
  ANALYSIS_MB           = 0x00000001, /**<    */
  ANALYSIS_INTRA        = 0x00000002, /**<    */
  ANALYSIS_INTER        = 0x00000004, /**<    */
  ANALYSIS_SCOEFF       = 0x00000008, /**<    */
  ANALYSIS_RESDIFF      = 0x00000010, /**<    */
  ANALYSIS_LEVEL        = 0x00000020, /**<    */
  ANALYSIS_BITSTREAM    = 0x00000040, /**<   coded bitstream extraction */
  ANALYSIS_GET_PIC      = 0x00010094, /**<    */
  ANALYSIS_GET_DPB      = 0x00010095, /**<    */

  VESA_SET_SETTINGS     = 0x00010096, /**<  Set VESA parameters  */
  VESA_GET_SETTINGS     = 0x00010097, /**<  Get VESA parameters  */
  VESA_GET_BUFFERS      = 0x00010098, /**<   Get VESA buffers after decoding is done. */

  SET_BRIGHTNESS        = 0x00010099, /**<    */
  SET_AFFINITY_MASK     = 0x00010100, /**<    */
  GET_GOP_TIME_CODE     = 0x00010101, /**<    */
  GET_SEQ_DISP_EXT      = 0x00010102, /**<    */
  SET_CROPPING_RECT     = 0x00010103, /**<    */
  GET_BRIGHTNESS        = 0x00010104, /**<    */

  HWACC_GET_HW_CAPS		= 0x00200000, /**<   To enumerate hardware acceleration device */
  HWACC_SET_ACC_MODE    = 0x00200001, /**<   Set hardware acceleration mode */
  HWACC_GET_PIC         = 0x00200002, /**<   Get d3d surface after decoding in hardware mode is done.  */

  GET_GOP_ID			= 0x00300002, /**<   AVC,VC1,MPEG4,MPEG2 decoders' stuff */
  GET_PIC_TIMECODE		= 0x00300003, /**<   MPEG2 decoder's stuff */

  GET_PIC_DELAYED		= 0x00300004, /**<  MPEG4 decoder's stuff  */
  GET_DEC_FEATURES		= 0x00300005, /**<   AVC,VC1,MPEG4,MPEG2 decoders' stuff */
  SET_CONTRAST			= 0x00300006, /**<    */
  GET_PIC_GOP_TIMECODE  = 0x00300007  /**<   MPEG2 get GOP time code for the last output picture */
};
/** @} */ //end group
#ifndef __APPLE__
#ifdef __GNUC__
#pragma pack(push,1)
#else
#pragma pack(push)
#pragma pack(1)
#endif
#endif


/** \addtogroup video_dec_mpeg_group
 @{
*/
////////////////////////////////
/** \brief video sequence header. Fields' meaning depend on codec used.

 */
struct SEQ_Params
{
/**
<table>
<tr> <td><b> AVC </b></td>		<td> horizontal size of video. </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> horizontal size of video. </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> horizontal size of video.</td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>

</table>
*/
  int horizontal_size;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> vertical size of video. </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> vertical size of video. </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> vertical size of video.</td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int vertical_size;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.3.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> \arg 0 -  forbidden;	\arg 1 - 1:1 (square) \arg 2 - 12:11 \arg 3 - 10:11 \arg 4 - 16:11 \arg 5 - 40:33 \arg 6 to 14 - reserved \arg 15 - extended pixel aspect ratio</td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int aspect_ratio_information;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.3.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int frame_rate_code;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.3.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int bit_rate_value;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.3.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int vbv_buffer_size;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.3.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int constrained_parameters_flag;

};

/** \name brief video sequence header.  Fields' meaning depend on codec used.
\{
 */
struct SEQ_ParamsEx
{

/**
<table>
<tr> <td><b> AVC </b></td>		<td> horizontal size of video </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> horizontal size of video  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> horizontal size of video </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> horizontal size of video </td> </tr>
</table>
*/
  int horizontal_size;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> vertical size of video </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> vertical size of video  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> vertical size of video </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> vertical size of video </td> </tr>
</table>
*/
  int vertical_size;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> aspect ratio indicator (table E-1)  </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.3.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> defines the value of pixel aspect ratio (see values and their interpretation in SEQ_Params description) </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int aspect_ratio_information;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.3.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int frame_rate_code;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.3.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int bit_rate_value;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.3.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> the decoder counts this value as \code ((first_half_vbv_buffer_size << 3) | latter_half_vbv_buffer_size) *16384; \endcode where first_half_vbv_buffer_size, latter_half_vbv_buffer_size are values from MPEG-4 video object layer bitstream </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int vbv_buffer_size;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> combination of stream's constraint flags (bit 4 - constraint_set3_flag, bit 5 - constraint_set2_flag, ... , bit 7 - constraint_set0_flag)  </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.3.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int constrained_parameters_flag;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> horizontal aspect ratio</td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.3.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> par_width - pixel aspect ratio from video object layer header when  aspect_ratio_information = 15 (extended par)  </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int aspect_ratio_width;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> vertical aspect ratio</td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.3.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> par_height - pixel aspect ratio from video object layer header when  aspect_ratio_information = 15 (extended par)  </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int aspect_ratio_height;
  // Those fields used if frame_rate_code == 0. frame_rate = (double)scale/(double)units.
/**
<table>
<tr> <td><b> AVC </b></td>		<td> Time scale  </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Time scale   </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> vop_time_increment_resolution (number of ticks in one second). </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> Time scale  </td> </tr>
</table>
*/
  int scale;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> Number of units in tick  </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Number units in tick.   </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> fixed_vop_time_increment (represents the number of ticks between two successive frames in the display order). </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> Number units in tick. </td> </tr>
</table>
*/
  int units;

/**
<table>
<tr> <td><b> HEVC </b></td>	<td> Specifies the maximum number of temporal sub-layers that may be present in each CVS referring to the SPS. </td> </tr>
</table>
*/
	int max_sub_layers;
};
/**\}*/

/** \brief video sequnce extension

 ISO/IEC 13818-2 section 6.2.2.3: sequence_extension
 */
struct SEQ_Ext_Params
{
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.2.2.3.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int profile_and_level_indication;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> frame_mbs_only_flag </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.2.2.3.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int progressive_sequence;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> chroma_format_idc flag </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.2.2.3.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int chroma_format;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.2.2.3.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int horizontal_size_extension;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.2.2.3.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int vertical_size_extension;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.2.2.3.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int bit_rate_extension;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.2.2.3.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int vbv_buffer_size_extension;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> LOW_LATENCY_FLAG presenting </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.2.2.3.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int low_delay;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.2.2.3.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int frame_rate_extension_n;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.2.2.3.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int frame_rate_extension_d;
};

/** \brief sequence display extension

 ISO/IEC 13818-2 section 6.3.6: sequence display extension
 */
struct SEQ_Disp_Ext_Params
{
  int video_format; /**< Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.6: sequence display extension */
  int colour_description; /**< Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.6: sequence display extension */
  int colour_primaries; /**< Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.6: sequence display extension */
  int transfer_characteristics; /**< Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.6: sequence display extension */
  int matrix_coefficients; /**< Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.6: sequence display extension */
  int display_horizontal_size; /**< Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.6: sequence display extension */

  int display_vertical_size; /**< Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.6: sequence display extension */
};

////////////////////////////////
//

/** \brief Group of pictures header structure.

 ISO/IEC 13818-2 section 6.2.2.6 Group of pictures header
 */
struct GOP_Params
{
  int drop_flag; /**< Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.2.2.6 Group of pictures header */
  int hour; /**< Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.2.2.6 Group of pictures header */
  int minute; /**< Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.2.2.6 Group of pictures header */
  int sec; /**< Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.2.2.6 Group of pictures header */
  int frame; /**< Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.2.2.6 Group of pictures header */
  int closed_gop; /**< Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.2.2.6 Group of pictures header */
  int broken_link; /**< Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.2.2.6 Group of pictures header */
};

////////////////////////////////
/** \brief user data

In this structure the decoder returns information about user data found in the video stream.
*/
typedef struct
{
  long        data_size; /**< size of user data. */
  uint8_t *   p_buffer; /**< pointer to the memory buffer which contains found user data. */
} UserData_Info;

/** \brief User data buffer info structure

In this structure the decoder returns user data found in video stream.
*/
typedef struct
{
  int                 found_user_data;	/**< number of user data found in video stream. */
  int                 start_code;		/**< start code of syntactic structure (sequence, group of pictures or picture header) where user data was found in the video stream.  */
  UserData_Info **    pp_params;     	/**< array of pointers to the data structures UserData_Info, which contain information about user data found in video stream. */
} UserData_Params;

////////////////////////////////
/** \brief video picture header

ISO/IEC 13818-2 section 6.2.3: picture_header
 */
struct PIC_Params
{
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A  </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.8.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> in case of H-263 stream it's just temporal reference, but for MPEG-4 it represents the  vop_time_increment from the last synchronization point (in clock ticks) </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int temporal_reference;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A  </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.8.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> picture type of current displayed frame </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int picture_coding_type;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A  </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Same meanings as picture_coding_type. Obsolete data field. The  picture_coding_type should be used instead.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> picture type of current displayed frame (obsolete, use picture_coding_type field instead) </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int picture_type;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A  </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.8.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int vbv_delay;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A  </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.8.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int full_pel_forward_vector;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.8.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> vop_fcode_forward, is used for decoding motion vectors </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int forward_f_code;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.8.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int full_pel_backward_vector;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.8.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> vop_fcode_backward, is used for decoding motion vectors </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int backward_f_code;
};

////////////////////////////////
/** \brief video picture header and coding extension

In this structure the decoder returns information about a decoded picture including the coding extension information.

 */
struct PIC_ParamsEx
{
  // picture_header
/**
<table>
<tr> <td><b> AVC </b></td>		<td> POC </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.8.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> in case of H-263 stream it's just temporal reference, but for MPEG-4 it represents the  vop_time_increment from the last synchronization point (in clock ticks) </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/

  int temporal_reference;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> picture type of decoded frame </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.8.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> picture type of decoded frame </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> picture type of decoded frame </td> </tr>
</table>
*/
  int picture_coding_type;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> obsolete, do not use </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Same meanings as picture_coding_type. Obsolete data field. The  picture_coding_type should be used instead.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> obsolete, do not use </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> obsolete, do not use </td> </tr>
</table>
*/
  int picture_type;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.8.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A  </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int vbv_delay;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.8.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A  </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int full_pel_forward_vector;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.8.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> vop_fcode_forward, is used for decoding motion vectors </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int forward_f_code;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.8.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A  </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int full_pel_backward_vector;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.8.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> vop_fcode_backward, is used for decoding motion vectors </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int backward_f_code;

  //  picture_coding_extension() header
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.10.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A  </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int f_code[2][2];
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.10.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A  </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int intra_dc_precision;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> \arg 0 - frame, mbaff or complete fields pair, 	\arg 1- top field, \arg 2-bottom field </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.10.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A  </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int picture_structure;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> top_field_first flag </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.10.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A  </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> top_field_first flag </td> </tr>
</table>
*/
  int top_field_first;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.10.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A  </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int frame_pred_frame_dct;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.10.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A  </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int concealment_motion_vectors;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.10.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A  </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int q_scale_type;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.10.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A  </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int intra_vlc_format;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.10.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A  </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int alternate_scan;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> repeat_first_field flag </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.10.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A  </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> repeat_first_field flag </td> </tr>
</table>
*/
  int repeat_first_field;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.10.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A  </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int chroma_420_type;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> progressive frame </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.10.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> alternate_vertical_scan_flag: indicates the using of alternate vertical scan mode for interlaced frames.  </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int progressive_frame;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.10.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td>  N/A  </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int composite_display_flag;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.10.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int v_axis;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> field or mbaff sequence </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.10.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int field_sequence;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.10.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int sub_carrier;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.10.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int burst_amplitude;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.10.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int sub_carrier_phase;

  // picture_display_extension() header
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.12.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int number_of_frame_center_offsets; /**< \brief  derived */
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.12.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int frame_center_horizontal_offset[3];
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.12.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int frame_center_vertical_offset[3];

  // quant matrix entension
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.11.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> load_intra_quant_mat: is set to '1' if video object layer has intra_quant_mat </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int load_intra_quantizer_matrix;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.11.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> load_nonintra_quant_mat: is set to '1' if video object layer has nonintra_quant_mat </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int load_non_intra_quantizer_matrix;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.11.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int load_chroma_intra_quantizer_matrix;
/**
<table>
<tr> <td><b> AVC </b></td>		<td> N/A </td> </tr>
<tr> <td><b> MPEG-2 </b></td>	<td> Corresponds to the MPEG-1/2 syntax element of the same name and is described in the ISO/IEC 13818-2 section 6.3.11.  </td> </tr>
<tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
<tr> <td><b> VC-1 </b></td>	<td> N/A </td> </tr>
</table>
*/
  int load_chroma_non_intra_quantizer_matrix;
  //  unsigned char quant_matrixes[4][64];
};



////////////////////////////////
/** \brief video picture header and coding extension

In this structure the decoder returns information about a decoded picture including the coding extension information.

 */
struct PIC_Type
{
    int progressive;
    /**
    <table>
    <tr> <td><b> AVC </b></td>		<td> Specifies progressive picture (0 - interlace; 1 - progressive) </td> </tr>
    <tr> <td><b> MPEG-2 </b></td>	<td> N/A </td> </tr>
    <tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
    <tr> <td><b> VC-1 </b></td>	    <td> N/A </td> </tr>
    </table>
     */

    int top_field_first;
    /**
    <table>
    <tr> <td><b> AVC </b></td>		<td> Specifies field order. (1 - Top field is first, 0 - Bottom field is first) </td> </tr>
    <tr> <td><b> MPEG-2 </b></td>	<td> N/A </td> </tr>
    <tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
    <tr> <td><b> VC-1 </b></td>	    <td> N/A </td> </tr>
    </table>
    */

     int picture_type[3];
    /**
    <table>
    <tr> <td><b> AVC </b></td>		<td> Specifies picture types. picture_type[0] for progressive picture, picture_type[1] for first field, picture_type[2] for second field (1 - I, 2- P, 3 - B)</td> </tr>
    <tr> <td><b> MPEG-2 </b></td>	<td> N/A </td> </tr>
    <tr> <td><b> MPEG-4 </b></td>	<td> N/A </td> </tr>
    <tr> <td><b> VC-1 </b></td>	    <td> N/A </td> </tr>
    </table>
    */
};

////////////////////////////////
// video frame info for parser
#if !defined (__FRAME_TT_INCLUDED__)
#define __FRAME_TT_INCLUDED__
/** \brief  video frame info for parser

The frame_tt structure is used to inform the codec about the destination colorspace and buffer.

The decoder fills passed frame_tt data structure: sets pointers to image planes, picture width, height, stride and specifies chroma format by setting the four_cc data field to FOURCC_YV12 (if sequence has 4:2:0 chroma  sampling) or to FOURCC_YV16 (if sequence has 4:2:2 chroma sampling).

*/
typedef struct
{
  uint32_t       width; /**< the number of pixels per row used for output, normally this is the horizontal size */
  uint32_t       height; /**< the number of lines used for output, normally this is the vertical size*/

/**
 for possible FourCC values look at \ref FourCC
 or set 0 for getting access to internal decoded frame buffer without color conversion. The decoder fills passed frame_tt data structure: sets pointers to image planes, picture width, height, stride and specifies chroma format by setting 				the four_cc data field to FOURCC_YV12 (if sequence has 4:2:0 chroma sampling) or to FOURCC_YV16 (if sequence has 4:2:2 chroma sampling).</td>  </tr>
</table>
*/
  uint32_t       four_cc;
  uint32_t       state; /**< state */
  unsigned char *plane[4]; /**< The decoder fills passed frame_tt data structure: sets pointers to image planes, picture width, height, stride and specifies chroma format by setting the four_cc data field to FOURCC_YV12 (if sequence has 4:2:0 chroma  sampling) or to FOURCC_YV16 (if sequence has 4:2:2 chroma sampling).*/
  int32_t        stride[4]; /**< offset for each line in the output planes. Use negative values for upside down images*/
  void         (*done)(void *this_object); /**< \brief */

/** pointer to ext_cc_struct structure.

  This structure is passed to the decoder pointer for external procedure, which will be used for color conversion of decoded pictures to planar format.
If the fourcc data member equals to FOURCC_EXTP, then the ext_cc data member must not be zero and the decoder uses external procedure for color conversion of decoded pictures.
\warning Specifying FOURCC_EXTP without specifying a correctly filled ext_cc data structure is invalid and may result in useless output or even crashes!
*/
  void          *ext_cc;
  int32_t       cc_pix_range;       /**<@brief Pixel range conversion
                                                     <table>
                                                     <tr>
                                                         <th>cc_pix_range</th>
                                                         <th>MPEG2/4 pixels range</th>
                                                     </tr>
                                                     <tr>
                                                         <td>0</td>
                                                         <td>No conversion. Indicates what input stream is full range [0..255] and encoded stream should be full range.</td>
                                                     </tr>
                                                     <tr>
                                                         <td>1</td>
                                                         <td>Conversion to short range [16..235]. Indicates what input stream is full range and encoded stream should be convert to short range.</td>
                                                     </tr>
                                                     <tr>
                                                         <td>2</td>
                                                         <td>Keep short range [16..235]. No conversion, but doesn't allow to go beyond short range when use color resampling (for example when use conversion from 4:2:0 to 4:2:2 format)</td>
                                                     </tr>
                                                     <tr>
                                                         <td>3</td>
                                                         <td>Conversion to full range [0..255]. Indicates what input stream is short range and encoded stream should be convert to full range.</td>
                                                     </tr>
                                                     </table>
                                                     <table>
                                                     <tr>
                                                         <th>cc_pix_range</th>
                                                         <th>H264 pixels range</th>
                                                     </tr>
                                                     <tr>
                                                         <td>0</td>
                                                         <td>No conversion. Depends from VUI-video_full_range_flag.
                                                             <br>If VUI-video_full_range_flag equal to zero then doesn't allow to go beyond short range when use color resampling (for example when use conversion from 4:2:0 to 4:2:2 format)
                                                             <br>default value
                                                         </td>
                                                     </tr>
                                                     <tr>
                                                         <td>1</td>
                                                         <td>Conversion to short range [16..235]. Depends from VUI-video_full_range_flag.
                                                             <br>If VUI-video_full_range_flag equal to 1 this indicates what input stream is full range and encoded stream should be convert to short range;
                                                             <br>If VUI-video_full_range_flag equal to 0 then doesn't allow to go beyond short range when use color resampling (for example when use conversion from 4:2:0 to 4:2:2 format);
                                                         </td>
                                                     </tr>
                                                     <tr>
                                                         <td>2</td>
                                                         <td>Conversion to full range [0..255]. Depends from VUI-video_full_range_flag.
                                                         <br>If VUI-video_full_range_flag equal to 1 then will keep full range.
                                                         <br>If VUI-video_full_range_flag equal to 0 this indicates what input stream is short range and encoded stream should be convert to full range.
                                                         </td>
                                                     </tr>
                                                     <tr>
                                                         <td>3</td>
                                                         <td>Force no conversion</td>
                                                     </tr>
                                                     <tr>
                                                         <td>4</td>
                                                         <td>Force conversion to short range [16..235]. Indicates what input stream is full range and encoded stream should be convert to short range.</td>
                                                     </tr>
                                                     <tr>
                                                         <td>5</td>
                                                         <td>Force keep short range [16..235]. No conversion, but doesn't allow to go beyond short range when use color resampling (for example when use conversion from 4:2:0 to 4:2:2 format)</td>
                                                     </tr>
                                                     <tr>
                                                         <td>6</td>
                                                         <td>Force conversion to full range [0..255]. Indicates what input stream is short range and encoded stream should be convert to full range.</td>
                                                     </tr>
                                                     </table>
                                                     
                                      @hideinitializer*/
  uint32_t       reserved3;
} frame_tt;/**< \brief */
#endif

#define FRAME_EXT_TT_VERSION 1

/**
The frame_ext_tt structure is used to inform the decoder about the destination colorspace and buffers for decoded picture and user data associated with current picture.

*/
typedef struct
{
  uint8_t  version;		/**< version number of the structure. Current version number is equal to 1.*/
  frame_tt frame_data;  /**< the frame_tt structure.*/
  UserData_Params * pic_user_data_params; /**< the UserData_Params structure which is used to receive user data from the decoder associated with current decoded picture. */
} frame_ext_tt;


/**
\brief External color space converter structure

*/
struct ext_cc_struct
{
/**
convert_planes: pointer to external function, which makes color conversion of decoded frame to planar color format. This procedure is called from the decoder, when it receives GET_PIC or GET_PIC_WITH_SP commands. The external procedure should receive following arguments:
 */
/**
\param[in] frame    pointer to frame_tt structure.
\param[in] src		pointers to planes (0 - Y plane, 1 - U plane, 2 - V plane).
\param[in] stride		stride of each plane.
\param[in] chroma_format	chroma format of input frame (1 - 4:2:0, 2 - 4:2:2, 3 - 4:4:4).
\param[in] mode			mode of conversion (0 - progressive, 1 - interlaced, 2 - deinterlace).
\param[in] cpu 			CPU features (like CPUID):

<table>
<tr> <td> FEATURE_CPUID     </td> <td>    	0x00000001 </td> </tr>
<tr> <td> FEATURE_STD_FEATURES  </td> <td>   0x00000002 </td> </tr>
<tr> <td> FEATURE_EXT_FEATURES  </td> <td>   0x00000004 </td> </tr>
<tr> <td> FEATURE_TSC         </td> <td>    	0x00000010 </td> </tr>
<tr> <td> FEATURE_MMX        </td> <td>   	0x00000020 //Pmmx,K6-II/III,PII,PIII,K7 </td> </tr>
<tr> <td> FEATURE_CMOV       </td> <td>      	0x00000040 //PPro,PII,PIII,K7 </td> </tr>
<tr> <td> FEATURE_3DNOW       </td> <td>     	0x00000080 //K6-II/III, Cyrix, K7 </td> </tr>
<tr> <td> FEATURE_3DNOWEXT     </td> <td>    	0x00000100 //K7 </td> </tr>
<tr> <td> FEATURE_MMXEXT       </td> <td>    	0x00000200 //not FP part of SSE (PIII) </td> </tr>
<tr> <td> FEATURE_SSEFP        </td> <td>    	0x00000400 //FP part of SSE (PIII, OS-support) </td> </tr>
<tr> <td> FEATURE_K6_MTRR      </td> <td>    	0x00000800 </td> </tr>
<tr> <td> FEATURE_P6_MTRR      </td> <td>    	0x00001000 </td> </tr>
<tr> <td> FEATURE_SSE2         </td> <td>    	0x00002000 //SSE2 (P4, OS-support) </td> </tr>
<tr> <td> FEATURE_HT           </td> <td>    	0x00004000 //HyperThreading (P4, OS-support) </td> </tr>
<tr> <td> FEATURE_SSE3         </td> <td>    	0x00008000 //SSE3 (Prescott) </td> </tr>
</table>

*/
  int (*convert_planes)(frame_tt *frame, unsigned char *src[], long stride[], long chroma_format, long mode, unsigned long cpu);

  void *reserved1;
  void *reserved2;
  void *reserved3;
};


/** \cond SHOW_ALL */
struct cropping_rect
{
  uint32_t top;
  uint32_t left;
  uint32_t bottom;
  uint32_t right;
};
/** \endcond */
////////////////////////////////
/** \name  video parser frame skip types */
/** @{ */ 
#define SKIP_NONE           0   /**< \brief   decode all frame types  \hideinitializer  */
#define SKIP_B              1   /**< \brief   skip B frames  \hideinitializer  */
#define SKIP_PB             2   /**< \brief   skip P and B frames  \hideinitializer  */
#define SKIP_IPB            3   /**< \brief   skip I, P and B frames  \hideinitializer  */
#define SKIP_NONREF         4   /**< \brief   skip non-reference frames  \hideinitializer  */
#define KEEP_EVERY_N        5   /**< \brief   keep every 'N' frames  \hideinitializer  */
/** @} */

////////////////////////////////
/** \name   video reordering flag  */
/** @{ */ 
#define INTERN_REORDERING_FLAG      0x00000010L  /**< \brief   make frame reordering in the parser  \hideinitializer  */
#define IGNORE_BROKEN_LINK          0x00000020L  /**< \brief   ignore the broken link flag, only use when feeding back-to-back files to the decoder  \hideinitializer  */
#define H264_ASSUME_FRAME_RATE      0x00000040L  /**< \brief   rate in H264 bitstream is a frame rate, not a field rate  \hideinitializer  */
#define DEINTERLACING_FLAG          0x00000100L  /**< \brief   deinterlace video, bitfield bit 8..12  \hideinitializer  */
#define DEINTERLACING_FLAGS         0x00000F00L  /**< \brief   deinterlace video, bitfield bit 8..12  \hideinitializer  */
/** @} */

////////////////////////////////
/** \name   video downscaling flag     */
/** @{ */ 
#define DECODE_FULL_SIZE            0x00000000L  /**< \brief   full size decoding  \hideinitializer  */
#define DECODE_HALF_SIZE            0x00000001L  /**< \brief   horz/vert half size decoding  \hideinitializer  */
#define DECODE_QUARTER_SIZE         0x00000002L  /**< \brief   quarter size decoding  \hideinitializer  */
#define DECODE_HALF_TFONLY          0x00000010L  /**< \brief   Decode only Topfield for interlace/half  \hideinitializer  */
#define DECODE_HALF_BFONLY          0x00000020L /**< \brief   Decode only Bottomfield for interlace/half  \hideinitializer  */
/** @} */

////////////////////////////////
/** \name   video OSD flag  */
/** @{ */ 
#define OSD_FORMAT_FLAGS            0x0001E000L /**< \brief   OSD format, bits 13..16  \hideinitializer  */

#define OSD_PICT_TIMECODE           0x00002000L /**< \brief   Show/hide picture time code, bit 13 (1 - show, 0 - hide )  \hideinitializer  */
#define OSD_PICT_TYPE               0x00004000L /**< \brief   Show/hide picture type, bit 14 (1 - show, 0 - hide )  \hideinitializer  */
#define OSD_GOP_MARKER_BIT          0x00008000L /**< \brief   Show/hide GOP header marker bit, bit 15 (1 - show, 0 - hide )  \hideinitializer  */
#define OSD_GOP_DROP_FLAG           0x00010000L /**< \brief   Show/hide GOP drop flag, bit 16 (1 - show, 0 - hide )      \hideinitializer  */

#define OSD_DISABLE_AUTO_SCALING    0x00020000L /**< \brief   Disable/enable auto OSD scaling OSD, bit 17 (disable - 1, enable - 0)  \hideinitializer  */
#define OSD_SCALE_MASK              0x001C0000L /**< \brief   Scale coefficient for OSD, bits 18..20   \hideinitializer  */
#define OSD_SCALE_START_BIT         0x00000012L /**< \brief   First bit of scale coefficient  \hideinitializer  */

#define POST_PROCESSING_FLAG        0x00200000L /**< \brief  Disable/enable post processing, bit 21  \hideinitializer  */

#define LOW_LATENCY_FLAG            0x00400000L /**< \brief   decode with minimal output delay, bit 22  \hideinitializer  */
#define FLOATING_POINT_IDCT         0x00800000L /**< \brief   Use double precision floating point IDCT, bit 23  \hideinitializer  */
/** @} */

/** \name   smp mode enum  */
/** @{ */
#define SMP_NONE                    0x00000000L /**< \brief   Serial decoding.  \hideinitializer  */
#define SMP_BY_PICTURES             0x00000001L /**< \brief   Parallel decoding by pictures.  \hideinitializer  */
#define SMP_BY_SLICES               0x00000002L /**< \brief   Parallel decoding by slices.  \hideinitializer  */
/** @} */

/** \name  GET_PIC options  */
/** @{ */
#define DEINTERLACE_VERTICAL_SMOOTHING	0x00000200L /**< \brief   Vertical filtering  \hideinitializer  */
#define DEINTERLACE_FIELD_INTERPOLATION	0x00000100L /**< \brief   Top field interpolation  \hideinitializer  */
#define DEINTERLACE_FIELD_SELECT		0x00000200L /**< \brief   Bottom field interpolation  \hideinitializer  */
#define UPSAMPLE_CHROMA					0x00000400L /**< \brief   Deprecated  \hideinitializer  */
#define REORDER_FIELDS					0x00000800L /**< \brief   Changes the order of fields  \hideinitializer  */
/** @} */

/** \} */ //group end
////////////////////////////////
// audio header
/**
 * @name Audio frame header
 * @{
 **/

 /**
  * @brief In this structure the decoder returns information about audio found in audio stream.
  */
struct aud_frame_hdr
{
  unsigned long header;		/**< @brief unparsed header of AudioFrame */
  int ID;
  int layer;
  int protection_bit;
  int bitrate_index;
  int sampling_frequency;		/**< @brief sampling frequency of audio */
  int padding_bit;
  int private_bit;
  int audioMode;         /**< @brief MPEG audio mode encoded in file, one of the MODE_* consts */
  int mode_extension;
  int copyright;
  int original;
  int emphasis;

  unsigned int audioRate;       /**< @brief audio sample rate, either 32000, 44100 or 48000 */
  unsigned int sampleSize;      /**< @brief size in bits of samples, will be 16 */
  int audioBitrate;             /**< @brief MPEG audio bitrate */
  int bytesPerSample;           /**< @brief bytes per audio sample (2 or 4) */
  int audioLayer;               /**< @brief MPEG audio layer encoded in file, 1 or 2 */
  int channels;                 /**< @brief number of channels */
  int samplesInFrame;
  int bytesInFrame;
};
/** @} */

typedef struct
{
  int syncword;
  int id;
  int layer;
  int protection_abs;
  int profile;
  int sampling_freq_idx;
  int private_bit;
  int channel_config;
  int original_copy;
  int home;
  int copyright_id_bit;
  int copyright_id_start;
  int frame_length;
  int adts_buffer_fullness;
  int num_of_rdb;
  int crc_check;
  int rdb_position[4-1];
  int crc_check_rdb;

  unsigned int sampling_frequency;
  unsigned int bits_per_sample;
  unsigned int channels;
} aac_adts_header;


/**
 * @name Audio buffer
 * @{
 **/

/**
  * @brief This structure is used to inform the parser where to put decoded audio data
  */
typedef struct
{
  unsigned char *bfr;			/**< @brief Pointer to a user buffer that will receive the PCM data */
  unsigned long bfr_size;		/**< @brief Size bytes of buffer on input or used buffer on output */
} aud_bfr_tt;
/** @} */

/**
 * @name Old ac3 audio header for compatibility
 * @{
 **/

/**
  * @brief This structure is used to report information about the audio stream.
  */
struct ac3_frame_hdr
{
  unsigned char header[7];		/**< @brief Unparsed header of AudioFrame
								  * @brief Contains the first 7 bytes of the first Dolby Digital header starting with the AC-3 syncword. */

  int fscod;					/**< @brief Sample rate code
								  * @brief Contains the sample rate code as present in the bitstream. Note that half and quarter
								  * (of the rates below) sample rates are also supported.
								  *<table>
								  * <tr><th>value</th><th>meaning</th></tr>
								  * <tr><td>0    </td><td>48 kHz</td></tr>
								  * <tr><td>1    </td><td>44.1 kHz</td></tr>
								  * <tr><td>2    </td><td>32 kHz</td></tr>
								  * <tr><td>3    </td><td>reserved</td></tr>
								  * </table>	*/

  int frmsizecod;				 /**< @brief Frame size code as it is in the bitstream.
								   * See the Frame Size Code Table in the Dolby AC-3 documentation for more details. */

  int acmod;				    /**< @brief Audio coding mode
								   * @brief Contains the audio coding mode as present in the bitstream.
								   * This indicates the number of input channels (along with the lfeon field in the bitstream).
								   *<table>
								  * <tr><th>value</th><th>meaning</th></tr>
								  * <tr><td>0    </td><td>2/0   Dolby Surround compatible (Lt, Rt)</td></tr>
								  * <tr><td>1    </td><td>1/0   C</td></tr>
								  * <tr><td>2    </td><td>2/0   L, R</td></tr>
								  * <tr><td>3    </td><td>3/0   L, C, R</td></tr>
								  * <tr><td>4    </td><td>2/1   L, R, S</td></tr>
								  * <tr><td>5    </td><td>3/1   L, C, R, S</td></tr>
								  * <tr><td>6    </td><td>2/2   L, R, Ls, Rs</td></tr>
								  * <tr><td>7    </td><td>3/2   L, C, R, Ls, Rs</td></tr>
                                  * <tr><td>9    </td><td>2/2/1   L, R, Ls, Rs, Ts</td></tr>
                                  * <tr><td>10   </td><td>3/2/1   L, C, R, Ls, Rs, Ts</td></tr>
                                  * <tr><td>11   </td><td>3/2/1   L, C, R, Ls, Rs, Cvh</td></tr>
                                  * <tr><td>12   </td><td>3/0/2   L, C, R, Lc, Rc</td></tr>
                                  * <tr><td>13   </td><td>2/2/2   L, R, Ls, Rs, Lw, Rw</td></tr>
                                  * <tr><td>14   </td><td>2/2/2   L, R, Ls, Rs, Lvh, Rvh</td></tr>
                                  * <tr><td>15   </td><td>2/2/2   L, R, Ls, Rs, Lsd, Rsd</td></tr>
                                  * <tr><td>16   </td><td>2/2/2   L, R, Ls, Rs, Lrs, Rrs</td></tr>
                                  * <tr><td>17   </td><td>3/2/2   L, C, R, Ls, Rs, Lc, Rc</td></tr>
                                  * <tr><td>18   </td><td>3/2/2   L, C, R, Ls, Rs, Lw, Rw</td></tr>
                                  * <tr><td>19   </td><td>3/2/2   L, C, R, Ls, Rs, Lvh, Rvh</td></tr>
                                  * <tr><td>20   </td><td>3/2/2   L, C, R, Ls, Rs, Lsd, Rsd</td></tr>
                                  * <tr><td>21   </td><td>3/2/2   L, C, R, Ls, Rs, Lrs, Rrs</td></tr>
								  * </table>	*/

  int lfeon;                    /**< @brief LFE channel On
								   * @brief Contains configuration for LFE channel. */

  unsigned int audioRate;       /**< @brief Audio sample rate in Hz (48000, 32000, 24000, etc.) */

  unsigned int sampleSize;      /**< @brief Size in bits of samples, will be 16
								  * @brief Contains the output sample size in bits.
								  * It is set depending on the @ref dd_parser_settings.output_word_size setting.
								  *<table>
								  * <tr><th>value</th><th>meaning</th></tr>
								  * <tr><td>16    </td><td>16 bits per sample</td></tr>
								  * <tr><td>32    </td><td>32 bits per sample</td></tr>
								  * <tr><td>64    </td><td>64 bits per sample</td></tr>
								  * </table>*/

  int audioBitrate;             /**< @brief Audio bitrate, range is 32 .. 640 kbps */

  int bytesPerSample;           /**< @brief Bytes per audio sample
								  * @brief Contains the number of bytes in 1 PCM sample, including all channels. It is computed
								  * as (sampleSize * channels) / 8. This field reflects the actual output of the decoder which
								  * may be different than that indicated by the Dolby Digital bitstream header values. */

  int channels;                 /**< @brief Number of channels
								  * @brief Contains the actual number of output channels. If @ref dd_parser_settings.match_input_mode = 0,
								  * this field is set to @ref dd_parser_settings.output_num_channels. If @ref dd_parser_settings.match_input_mode = 1,
								  * this field is computed from acmod and the lfe if present. Range is 1 .. 8.*/

  int samplesInFrame;			/**< @brief Number of samples in frame
								  * @brief Contains the number of samples in one AC-3 coded frame. The value is fixed at 1536. */

  int bytesInFrame;				/**< @brief Number of bytes in one Dolby Digital coded frame. See the Frame Size Code Table
								  * in the Dolby AC-3 documentation for more details.*/
} ;
/** @} */

/**
 * @name Dolby Digital config information
 * @{
 **/

/**
  * @brief Extra Dolby Digital decoder config info
 */
typedef struct
{
  uint8_t two_channel_limit;        ///< @brief Two channel limit
                                    ///< 0 - 5.1 channel decoder
                                    ///< 1 - 2 channel decoder
  uint8_t karaoke_support;          ///< @brief Karaoke support
                                    ///< 0 - unsupported
                                    ///< 1 - karaoke aware
                                    ///< 2 - karaoke capable
  uint8_t TPNP_support;             ///< @brief TPNP support
                                    ///< 0 - unsupported
                                    ///< 1 - supported
  uint8_t stream_type1_support;     ///< @brief Stream type 1 support
                                    ///< 0 - unsupported
                                    ///< 1 - supported
  uint8_t stream_type2_support;     ///< @brief Stream type 2 support
                                    ///< 0 - unsupported
                                    ///< 1 - supported

  uint32_t delaysamples;            ///< @brief PCM sample delay in decoded output

  uint8_t reserved[7];              ///< @brief 7 bytes are reserved

}  dd_config_info_tt;
/** @} */

/**
 * @name Dolby Digital generated information
 * @{
 **/

/**
  * @brief This structure is used to report information about the audio stream.
 */
typedef struct
{
  int16_t bsid;				/**< @brief Bitstream identification. Range is 0 .. 10 */
  uint16_t sample_rate;		/**< @brief Audio sampling rate in Hz (48000, 32000, 24000, etc.) */
  int16_t streamtype;
  int16_t substreamid;
  int16_t nblksperfrm;
  int16_t acmod;			/**< @brief Audio coding mode
							* @brief Contains the audio coding mode as present in the bitstream.
							* This indicates the number of input channels (along with the lfeon field in the bitstream).
							*<table>
							* <tr><th>value</th><th>meaning</th></tr>
							* <tr><td>0    </td><td>2/0 	Dolby Surround compatible (Lt, Rt)</td></tr>
							* <tr><td>1    </td><td>1/0	C</td></tr>
							* <tr><td>2    </td><td>2/0	L, R</td></tr>
							* <tr><td>3    </td><td>3/0	L, C, R</td></tr>
							* <tr><td>4    </td><td>2/1	L, R, S</td></tr>
							* <tr><td>5    </td><td>3/1	L, C, R, S</td></tr>
							* <tr><td>6    </td><td>2/2	L, R, SL, SR</td></tr>
							* <tr><td>7    </td><td>3/2	L, C, R, SL, SR</td></tr>
							* </table>	*/

  int16_t lfeon;			/**< @brief Low frequency
							* @brief Contains the low frequency effects chan flag. This flag is 1 if the lfe (sub woofer)
							* channel is on, and it is 0 if the lfe channel is off. */

  int16_t compre;			/**< @brief Compression gain word exists. */
  int16_t compr;			/**< @brief Compression gain word. See the Dolby AC-3 documentation for more details. */
  int16_t blkid;
  int16_t frmsizcod;		/**< @brief Frame size code as it is in the bitstream. See the Frame Size Code Table in the Dolby AC-3 documentation for more details. */
  int16_t dialnorm;			/**< @brief Dialogue normalization word. Range is 1 .. 31. */
  int16_t convsync;
  int16_t encinfo;
  int16_t chanmap;

  int16_t reserved[16];

} dd_gen_info_tt;
/** @} */

// DD_GET_MIX_INFO
typedef struct
{
  int16_t dmixmod;
  int16_t cmixlev;
  int16_t surmixlev;
  int16_t ltrtcmixlev;
  int16_t ltrtsurmixlev;
  int16_t lorocmixlev;
  int16_t lorosurmixlev;
  int16_t pgmscl[2];
  int16_t extpgmscl;
  int16_t paninfo[2];
  int16_t panmean[2];
  int16_t lfemixlevcod;
  int16_t premixcmpsel;
  int16_t drcsrc;
  int16_t premixcmpscl;
  int16_t extpgmlscl;
  int16_t extpgmcscl;
  int16_t extpgmrscl;
  int16_t extpgmlsscl;
  int16_t extpgmrsscl;
  int16_t extpgmlfescl;
  int16_t dmixscl;
  int16_t extpgmaux1scl;
  int16_t extpgmaux2scl;

  int16_t reserved[16];

} dd_mix_info_tt;


// DD_GET_PROD_INFO

typedef struct
{
  int16_t audprodie;
  int16_t roomtyp;
  int16_t mixlevel;
  int16_t adconvtyp;

  int16_t reserved[16];

} dd_audprod_info_tt;


typedef struct
{
  int16_t bsmod;
  int16_t copyrightb;
  int16_t origbs;
  int16_t dsurmod;
  int16_t dsurexmod;
  int16_t dheadphonmod;
  int16_t langcod[2];
  dd_audprod_info_tt audprod[2];
  int16_t sourcefsflag;

  int16_t reserved[16];

} dd_prod_info_tt;


// DD_GET_TIMECODE_INFO
typedef struct
{
  int16_t mode;
  int16_t hours;
  int16_t minutes;
  int16_t secs;
  int16_t frames;
  int16_t frame64ths;

  int16_t reserved[16];

} dd_timecode_info_tt;


// DD_GET_ADDBSI_INFO
typedef struct
{
  int16_t num_bytes;
  int8_t add_bsi_data[64];

} dd_addbsi_info_tt;


// DD_GET_AUXDATA_INFO
typedef struct
{
  int16_t num_bits;
  int16_t p_data[1024];

} dd_auxdata_info_tt;

/**
  * @brief Dolby Digital defines
 */
#define DD_MAX_DUALMONO_CHANS   2      /**< @brief Maximum number of dual mono channels */
#define DD_MAX_BLOCKS_PER_FRM   6      /**< @brief Maximum number of blocks per frame */
#define DD_MAX_DEPEN_FRMS       8      /**< @brief Maximum number of dependent frames per program */
/** @} */

/**
  * @brief Bit stream information
 */
typedef struct {

    /**
    * @name DD bitstream information variables
    * @{
    */
    int32_t fscod;                              /**< @brief Sample rate code */
    int32_t frmsizecod;                         /**< @brief Frame size code */
    int32_t bsid;                               /**< @brief Bitstream identification */
    int32_t bsmod;                              /**< @brief Bitstream mode */
    int32_t acmod;                              /**< @brief Audio coding mode */
    int32_t lfeon;                              /**< @brief Low frequency effects channel flag */

    int32_t cmixlev;                            /**< @brief Center mix level */
    int32_t surmixlev;                          /**< @brief Surround mix level */
    int32_t dsurmod;                            /**< @brief Dolby surround mode */
    int32_t dialnorm[DD_MAX_DUALMONO_CHANS];    /**< @brief Dialogue normalization */
    int32_t compre[DD_MAX_DUALMONO_CHANS];      /**< @brief Compression word exists */
    int32_t compr[DD_MAX_DUALMONO_CHANS];       /**< @brief Compression word (sign extended in 32-bit word) */

    int32_t langcode[DD_MAX_DUALMONO_CHANS];    /**< @brief Language code exists */
    int32_t langcod[DD_MAX_DUALMONO_CHANS];     /**< @brief Language code */
    int32_t audprodie[DD_MAX_DUALMONO_CHANS];   /**< @brief Audio production info exists */
    int32_t mixlevel[DD_MAX_DUALMONO_CHANS];    /**< @brief Mixing level */
    int32_t roomtyp[DD_MAX_DUALMONO_CHANS];     /**< @brief Room type */
    int32_t copyrightb;                         /**< @brief Copyright bit */
    int32_t origbs;                             /**< @brief Original bitstream flag */

    int32_t timecod1e;                          /**< @brief Time code 1 exists */
    int32_t timecod1;                           /**< @brief Time code 1 */
    int32_t timecod2e;                          /**< @brief Time code 2 exists */
    int32_t timecod2;                           /**< @brief Time code 2 */
    /** @} */

    /**
    * @name Extended bitstream information 1
    * @{
    */
    int32_t xbsi1e;                             /**< @brief Extra BSI1 info exists */
    int32_t dmixmod;                            /**< @brief Preferred downmix mode */
    int32_t ltrtcmixlev;                        /**< @brief Lt/Rt center mix level */
    int32_t ltrtsurmixlev;                      /**< @brief Lt/Rt surround mix level */
    int32_t lorocmixlev;                        /**< @brief Lo/Ro center mix level */
    int32_t lorosurmixlev;                      /**< @brief Lo/Ro surround mix level */
    /** @} */

    /**
    * @name Extended bitstream information 2 (system data)
    * @{
    */
    int32_t xbsi2e;                             /**< @brief Extra BSI2 info exists */
    int32_t dsurexmod;                          /**< @brief Surround EX mode flag */
    int32_t dheadphonmod;                       /**< @brief Dolby Headphone encoded flag */
    int32_t adconvtyp[DD_MAX_DUALMONO_CHANS];   /**< @brief Advanced converter flag */
    int32_t xbsi2;                              /**< @brief Reserved bsi parameters */
    int32_t encinfo;                            /**< @brief Encoder Information bit */
    /** @} */

    /**
    * @name Additional Bitstream Information
    * @{
    */
    int32_t addbsie;                            /**< @brief Additional BSI exists */
    int32_t addbsil;                            /**< @brief Additional BSI length */
    uint8_t addbsi[64];               /**< @brief Additional BSI data */
    /** @} */

    /**
    * @name DDPlus bitstream information variables
    * @{
    */
    int32_t strmtyp;                                /**< @brief Stream type */
    int32_t substreamid;                            /**< @brief Sub-stream identification */
    int32_t frmsiz;                                 /**< @brief Frame size (in 16-bit words) */
    int32_t fscod2;                                 /**< @brief Sample rate code 2 (halfrate) */
    int32_t numblkscod;                             /**< @brief Blocks per frame code */
    int32_t chanmape;                               /**< @brief Channel map exists flag */
    int32_t chanmap;                                /**< @brief Channel map data */
    int32_t mixmdate;                               /**< @brief Mixing metadata exists flag */
    int32_t lfemixlevcode;                          /**< @brief LFE Mix Level Code exists flag */
    int32_t lfemixlevcod;                           /**< @brief LFE Mix Level Code */
    int32_t pgmscle[DD_MAX_DUALMONO_CHANS];         /**< @brief Program scale factor exists flags */
    int32_t pgmscl[DD_MAX_DUALMONO_CHANS];          /**< @brief Program scale factor */
    int32_t extpgmscle;                             /**< @brief External program scale factor exists flags */
    int32_t extpgmscl;                              /**< @brief External program scale factor exists */
    int32_t mixdef;                                 /**< @brief Mix control type */
    int32_t mixdeflen;                              /**< @brief Length of mixing parameter data field */
    uint8_t mixdata[33];                  /**< @brief Raw mixdata defined by mixdeflen */
    int32_t mixdata2e;                              /**< @brief Mixing data 2 exists */
    int32_t premixcmpsel;                           /**< @brief Premix compression word select */
    int32_t drcsrc;                                 /**< @brief Dynamic range control word source (external or current) */
    int32_t premixcmpscl;                           /**< @brief Premix compression word scale factor */
    int32_t extpgmlscle;                            /**< @brief External program left scale factor exists */
    int32_t extpgmcscle;                            /**< @brief External program center scale factor exists */
    int32_t extpgmrscle;                            /**< @brief External program right scale factor exists */
    int32_t extpgmlsscle;                           /**< @brief External program left surround scale factor exists */
    int32_t extpgmrsscle;                           /**< @brief External program right surround scale factor exists */
    int32_t extpgmlfescle;                          /**< @brief External program LFE scale factor exists */
    int32_t extpgmlscl;                             /**< @brief External program left scale factor */
    int32_t extpgmcscl;                             /**< @brief External program center scale factor */
    int32_t extpgmrscl;                             /**< @brief External program right scale factor */
    int32_t extpgmlsscl;                            /**< @brief External program left surround scale factor */
    int32_t extpgmrsscl;                            /**< @brief External program right surround scale factor */
    int32_t extpgmlfescl;                           /**< @brief External program LFE scale factor */
    int32_t dmixscle;                               /**< @brief Downmix scale factor exists */
    int32_t dmixscl;                                /**< @brief Downmix scale factor */
    int32_t addche;                                 /**< @brief Additional scale factors exist */
    int32_t extpgmaux1scle;                         /**< @brief External program 1st auxiliary channel scale factor exists */
    int32_t extpgmaux1scl;                          /**< @brief External program 1st auxiliary channel scale factor */
    int32_t extpgmaux2scle;                         /**< @brief External program 2nd auxiliary channel scale factor exists */
    int32_t extpgmaux2scl;                          /**< @brief External program 2nd auxiliary channel scale factor */
    int32_t	mixdata3e;		                        /**< @brief Mixing data 3 exists */
    int32_t	spchdat;		                        /**< @brief Speech enhancement processing data */
    int32_t	addspchdate;	                        /**< @brief Additional speech enhancement processing data exists */
    int32_t	spchdat1;		                        /**< @brief Additional Speech enhancement processing attenuation data */
    int32_t spchan1att;                             /**< @brief Speech enhancement processing attenuation data */
    int32_t	addspchdat1e;	                        /**< @brief Additional speech enhancement processing data exists */
    int32_t spchdat2;                               /**< @brief Additional speech enhancement processing data */
    int32_t spchan2att;                             /**< @brief Speech enhancement processing attenuation data */
    int32_t frmmixcfginfoe;                         /**< @brief Frame mixing configuration information exists flag */
    int32_t blkmixcfginfo[DD_MAX_BLOCKS_PER_FRM];   /**< @brief Block mixing configuration information */
    int32_t paninfoe[DD_MAX_DUALMONO_CHANS];        /**< @brief Pan information exists flag */
    int32_t panmean[DD_MAX_DUALMONO_CHANS];         /**< @brief Pan mean angle data */
    int32_t paninfo[DD_MAX_DUALMONO_CHANS];         /**< @brief Pan information */
    int32_t infomdate;                              /**< @brief Information metadata exists flag */
    int32_t sourcefscod;                            /**< @brief Source sample rate code */
    int32_t convsync;                               /**< @brief Converter synchronization flag */
    int32_t blkid;                                  /**< @brief Block identification */
    /** @} */
} dd_bsi_mdat_tt;
/** @} */

/**
  * @brief Audio Block metadata
 */
typedef struct {
    int32_t dynrnge[DD_MAX_DUALMONO_CHANS];		/**< @brief Dynamic range word exists */
    int32_t dynrng[DD_MAX_DUALMONO_CHANS];		/**< @brief Dynamic range word (sign extended in 32-bit word) */
    int32_t skipflde;                           /**< @brief Skip field exists */
    int32_t skiple;                             /**< @brief Skip field length exists */
    int32_t skipl;                              /**< @brief Skip field length (in bytes) */
    uint8_t skipfld[512];             /**< @brief Skip field data */
} dd_audblk_mdat_tt;
/** @} */

/**
  * @brief Auxiliary metadata
 */
typedef struct {
    int32_t auxdatae;                   /**< @brief Auxiliary data exists */
    int32_t auxdatal;                   /**< @brief Auxiliary data length (in bits) */
    uint8_t auxbits[2048];    /**< @brief Auxiliary data */
} dd_auxdata_mdat_tt;
/** @} */

/**
  * @brief This structure is used to report metadata information from the audio stream.
 */
typedef struct {
    int32_t              samples_shift;                                             /**< @brief PCM data shift in samples */
    int32_t              dwnmix_type;                                               /**< @brief Type of downmix performed when decoding */
    int32_t              datarate;                                                  /**< @brief Aggregate datarate for the timeslice */
    dd_bsi_mdat_tt       bsi_mdat;                                                  /**< @brief Bit stream information */
    dd_auxdata_mdat_tt   auxdata_mdat;                                              /**< @brief Auxiliary metadata */
    dd_audblk_mdat_tt    audblk_mdat[DD_MAX_BLOCKS_PER_FRM];                        /**< @brief Audio Block metadata */
    int8_t               bsi_mdat_dep_valid[DD_MAX_DEPEN_FRMS];                     /**< @brief Valid bit stream information flags for dependence frames */
    dd_bsi_mdat_tt       dep_bsi_mdat[DD_MAX_DEPEN_FRMS];                           /**< @brief Bit stream information for dependence frames */
    dd_audblk_mdat_tt    dep_audblk_mdat[DD_MAX_DEPEN_FRMS][DD_MAX_BLOCKS_PER_FRM]; /**< @brief Audio Block metadata for dependence frames */
    int32_t              chanmap;
    uint8_t              reserved[723];
} dd_metadata_info_tt;
/** @} */

/////////////////////////////////////////////////////
// MP3 audio structures and defines

// alias MP3 names for parser auxillery commands
#define MP3D_INITIALIZE             PARSE_INIT
#define MP3D_SEARCH_HEADER      PARSE_AUD_HDR
#define MP3D_GET_HEADER             GET_PIC_PARAMSP
#define MP3D_DECODE_CHUNK           PARSE_FRAMES
#define MP3D_GET_STATUS             GET_PARSE_STATE
#define MP3D_CLEAR_STATUS           CLEAN_PARSE_STATE

// alias MP3 names for status flags
#define MP3D_FLAG_STREAMERROR   PARSE_ERR_FLAG
#define MP3D_FLAG_SUCCESSFUL    PARSE_DONE_FLAG

// MP3 header structure, raw data
typedef struct
{
  int syncword;
  int version;
  int lay;
  int error_protection;
  int bitrate_index;
  int sampling_frequency_index;
  int padding;
  int extension;
  int mode;
  int mode_ext;
  int copyright;
  int original;
  int emphasis;

  int reserved[256-13];

} mp3d_header_bits;

// MP3 header structure, basic stream information
typedef struct
{
  unsigned int layer;
  unsigned int channels;
  unsigned int sampling_frequency;
  unsigned int bitrate;
  unsigned int error_protection_used;

  int reserved[256-5];

} mp3d_header_info;

// MP3 main header structure
typedef struct
{
  mp3d_header_bits header_bits;
  mp3d_header_info header_info;

  int reserved[256];

} mp3d_audio_header;

// MP3 data related to last frame only
typedef struct
{
  unsigned int successful;
  unsigned int channels;
  unsigned int bytes_per_sample;
  unsigned int sampling_frequency;
  unsigned int frame_samples;
  unsigned int bitrate;

  unsigned int samples_clipped;

  int reserved[256-7];

} mp3d_last_frame_info;

// MP3 data related to overall decoding process
typedef struct
{
  unsigned long frames_successful;
  unsigned long frames_erroneus;
  unsigned long bytes_consumed;
  unsigned long bytes_skipped;

  int reserved[256-4*2];

} mp3d_statistics;

// MP3 structure holding all output information
typedef struct
{
  mp3d_statistics             statistics;
  mp3d_last_frame_info    last_frame_info;

  int reserved[256];

} mp3d_output_info;

// MP3 input configuration data
typedef struct
{
  int reserved[256];

} mp3d_config;

// MP3 input optional data
typedef struct
{
  mp3d_output_info* p_output_info;

  int reserved[256-1];

} mp3d_options;

// MP3 input data
typedef struct
{
  mp3d_config config;
  mp3d_options options;

  int reserved[256];

} mp3d_input_info;
// end MP3

/////////////////////////////////////////////////////
// WMA audio structures and defines

// alias WMA names for parser auxillery commands
#define WMAD_INITIALIZE             PARSE_INIT
#define WMAD_DECODE_CHUNK           PARSE_FRAMES
#define WMAD_GET_STATUS             GET_PARSE_STATE
#define WMAD_CLEAR_STATUS           CLEAN_PARSE_STATE
#define WMAD_REINITIALIZE           PARSE_REINIT

// alias WMA names for status flags
#define WMAD_FLAG_STREAMERROR   PARSE_ERR_FLAG
#define WMAD_FLAG_SUCCESSFUL    PARSE_DONE_FLAG

/**
 * @brief WMA output information structure.
 */
typedef struct
{
  /**
  * @name Reserved
  * @{
  **/
  int reserved[256*4];
  /** @} */

} wmad_output_info;

/**
 * @brief WMA PCM ouput format structure.
 */
typedef struct
{
  unsigned long outnSamplesPerSec;          ///<@brief the sampling rate of the output audio stream
  unsigned long outnChannels;               ///<@brief the number of audio channels of the output audio stream
  unsigned long outnChannelMask;            ///<@brief the channel mapping of the output audio stream
  unsigned long outnValidBitsPerSample;     ///<@brief the number of bits per sample of monaural data of the output audio stream
  unsigned long outcbPCMContainerSize;      ///<@brief the number of bytes per sample of monaural data of the output audio stream

  /**
  * @name Reserved
  * @{
  **/
  int reserved[256-5*2];
  /** @} */
} wmad_pcm_format;

/**
 * @brief WMA configuration structure.
 */
typedef struct
{
  unsigned short wFormatTag;            ///<@brief specifies the unique ID of the codec used, must be 0x162 for WMA9
  unsigned short nChannels;             ///<@brief the number of audio channels
  unsigned long  nSamplesPerSec;        ///<@brief the sampling rate of the audio stream
  unsigned long  nAvgBytesPerSec;       ///<@brief the average number of bytes per second of audio stream
  unsigned short nBlockAlign;           ///<@brief the block alignment, or block size, in bytes
  unsigned short nValidBitsPerSample;   ///<@brief the number of bits per sample of monaural data
  unsigned long  nChannelMask;          ///<@brief the channel mapping
  unsigned short wEncodeOpt;            ///<@brief the options used by encoder
  unsigned short wAdvancedEncodeOpt;    ///<@brief the options used by encoder
  unsigned long  dwAdvancedEncodeOpt2;  ///<@brief the options used by encoder
  /**
  * @name Reserved
  * @{
  **/
  int reserved[256 - 4*2 - 3 /* 6*0.5 */ ];
  /** @} */
} wmad_config;

/**
 * @brief WMA options structure.
 */
typedef struct
{
  unsigned int use_pcm_format;      /**<@brief specifies if the output PCM format would be customized
                                                by the user through the pcm_format struct, or PCM would have default settings*/
  wmad_pcm_format pcm_format;       ///<@brief structure that holds optional data for PCM output control

  wmad_output_info* p_output_info;  /**<@brief points to output_info structure through which the decoder provides user
                                                with additional data about the decoding process*/

  /**
  * @name Reserved
  * @{
  **/
  int reserved[256-1-1];
  /** @} */

} wmad_options;

/**
 * @brief WMA input information structure.
 */
typedef struct
{
  wmad_config  config;
  wmad_options options;

  /**
  * @name Reserved
  * @{
  **/
  int reserved[256];
  /** @} */

} wmad_input_info;
// end WMA

////////////////////////////////

/** \addtogroup video_dec_mpeg_group
\{
*/
/** \brief  subpic frame info

The sp_frame_tt structure is used to inform the decoder where to put decoded subpicture data.

 The subpic is an 8bpp lut.
 The bottom 4 bits are the lut entry into the subpic palette.
 Top 4 bits are the contrast ratio k, where:
 \code
    if (k > 0)
    {
      k += 1
      source pixel = ((16 - k) / 16) * source pixel + (k / 16) * subpic pixel
    }
    else
      source pixel = source pixel
 \endcode
*/
typedef struct
{
  unsigned long width;     /**< \brief  width of subpic  */
  unsigned long height;    /**< \brief  heigth of subpic  */
  unsigned char *plane;    /**< \brief  subpic buffer, must be large enough to handle a subpic as large as the main picture  */
  long stride;             /**< \brief  subpic stride  */
  // destination coordinates: 0,0 = upper left of picture
  long dest_x;             /**< \brief  destination x coordinate of subpic in main pic  */
  long dest_y;             /**< \brief  destination y coordinate of subpic in main pic  */
  unsigned long reserved0;
  unsigned long reserved1;
  unsigned long reserved2;
  unsigned long reserved3;
} sp_frame_tt;


/** \brief subpic palette info

The sp_palette_tt structure is used to inform the decoder of the YUV subpicture palette to be used for subpicture decoding.
16 24bpp YUV colors, 0 = reserved, 1 = Y, 2 = U, 3 = V, the DVD way!
*/
typedef struct
{
  unsigned char yuv_palette[16][4];  /**< \brief  subpicture YUV pallette information buffer  */
} sp_palette_tt;


//////////////////////////////////////////////////
/** \brief video frame info for parser with subpic overlay */
typedef struct
{
  unsigned long width;
  unsigned long height;
  unsigned long four_cc;
  sp_frame_tt *sp_frame; /**< \brief  set to non-NULL value to overlay subpic  */
  unsigned char *plane[4]; /**< \brief  subpic planes  */
  long stride[4];  /**< \brief  subpic planes stride  */
  unsigned long reserved0;
  unsigned long reserved1;
  unsigned long reserved2;
  unsigned long reserved3;
} frame_with_sp_tt;


/**< \brief  acceleration modes enumeration */
enum hwacc_modes
{
  ACC_MODE_NONE = 0,
  ACC_MODE_DXVA1 = 1,
  ACC_MODE_DXVA2 = 2,
  ACC_MODE_NVCUVID = 4
};
/** \brief DXVA2 configuration structure */
typedef struct
{
  void*       d3d_device_manager;     /**< \brief IDirect3DDeviceManager9  */
  uint32_t    num_allocated_surfaces; /**< \brief [out] number of allocataed surfaces  */
}dxva2_config_t;

/** \brief DXVA2 configuration structure with color primaries parameters */
typedef struct
{
    void*       d3d_device_manager;     /**< \brief IDirect3DDeviceManager9  */
    uint32_t    num_allocated_surfaces; /**< \brief [out] number of allocataed surfaces  */

    uint32_t /*D3DFORMAT*/ Format;                           // It is not recommended to set any format. By default it is D3DFORMAT(MAKEFOURCC('N', 'V', '1', '2')) and suitable for all HW decoders;
    uint32_t /*DXVA2_ExtendedFormat*/ SampleFormat;          // If not set (zeroed) decoder uses settings from a stream.
    uint64_t /*DXVA2_Frequency*/ InputSampleFreq;
    uint64_t /*DXVA2_Frequency*/ OutputFrameFreq;
    uint32_t UABProtectionLevel;

    uint32_t Reserved[1024];
}dxva2_config_ex_t;

/**\}*/
typedef struct
{
    void*       video_acc;              //IAMVideoAccelerator
    uint32_t    num_allocated_surfaces;
}dxva1_config_t;

typedef struct dxva_surface_s dxva_surface_t;
struct dxva_surface_s
{
  uint32_t (MC_EXPORT_API *addref)(dxva_surface_t *surf);
  uint32_t (MC_EXPORT_API *release)(dxva_surface_t *surf);

  uint32_t    surface_index;
  void*       d3d_surface;        /**< \brief IDirect3DSurface9  */
};

typedef struct {
	dxva1_config_t dxva1_config;
	uint32_t num_config_picture_decode;
	void * config_picture_decode;//DXVA_ConfigPictureDecode *
	uint32_t num_config_alpha_load;
	void * config_alpha_load;//DXVA_ConfigAlphaLoad *
	uint32_t num_config_alpha_combine;
	void * config_alpha_combine;//DXVA_ConfigAlphaCombine *
} dxva1_caps_t;

enum hwacc_dec_method {
	ACC_MODE_DXVA2_NONE = 0,
	ACC_MODE_DXVA2_IDCT,
	ACC_MODE_DXVA2_MoComp,
	ACC_MODE_DXVA2_VLD
};

typedef struct {
	uint32_t d3d_format;//D3DFORMAT(FourCC)
	uint32_t num_config_picture_decode;
	void * config_picture_decode;//DXVA2_ConfigPictureDecode
} dxva2_decoder_format_t;

typedef struct {
	uint32_t mode;//hwacc_dec_method
	uint32_t num_fromats;
	dxva2_decoder_format_t * formats;
} dxva2_decoder_device_caps_t;

enum hwacc_proc_device_type {
	ACC_MODE_DXVA2_UNKNOWN = 0,
	ACC_MODE_DXVA2_BOB,
	ACC_MODE_DXVA2_PROGRESSIVE
};

typedef struct {
	uint32_t d3d_format;//D3DFORMAT(FourCC)
	uint32_t operations;
	uint32_t num_substream_formats;
	uint32_t * substream_formats;
} dxva2_processor_format_t;

typedef struct {
	uint32_t mode;//hwacc_proc_device_type
	uint32_t num_formats;
	dxva2_processor_format_t * formats;
} dxva2_processor_device_caps_t;

typedef struct {
	dxva2_config_t dxva2_config;
	uint32_t num_decoder_devices;
	dxva2_decoder_device_caps_t * decoder_device_caps;
	uint32_t num_processor_devices;
	dxva2_processor_device_caps_t * processor_device_caps;
} dxva2_caps_t;

// time code info
typedef struct
{
	uint32_t DF;       // dropped frame flag
	uint32_t Hour;
	uint32_t Min;
	uint32_t Sec;
	uint32_t Frm;
	uint32_t FP;      // field phase flag in case of 50p/60p
  uint32_t base;    // the rounded timecode base, e.g. 24,25,30,50,60..
                    // note that 720p 50/59.94 fps sometimes has 25/30 base, thus Frm increments only every 2nd frame. odd frames have FP set then
	int32_t reserved[9];
}mc_time_code_t;

// date, time info
typedef struct
{
	uint32_t Year;
	uint32_t Month;
	uint32_t Day;
	uint32_t Hour;
	uint32_t Min;
	uint32_t Sec;
	int32_t  TimeZone;  // +/- in minutes
	uint32_t DayLight;  // day light saving time
  uint32_t MilliSec;
	int32_t reserved[9];
}mc_date_time_t;


// external I/O callbacks for mfimport and demuxers

// called to open an external file
//
// p_app_ptr      - input, the p_app_ptr field from the mc_external_io_t structure
// p_filename     - input, the filename to open
// pp_file_handle - output, handle for the opened file
// return         - 0 if ok, else non-zero

typedef int32_t (*pfn_mc_external_open)(void *p_app_ptr, char *p_filename, void **pp_file_handle);
typedef int32_t (*pfn_mc_external_openW)(void *p_app_ptr, uint16_t *p_filename, void **pp_file_handle);


// called to seek in an external file
//
// p_app_ptr     - input, the p_app_ptr field from the mc_external_io_t structure
// p_file_handle - input, the file handle returned by the open function
// position      - input, the seek position
// return        - 0 if ok, else non-zero

typedef int32_t (*pfn_mc_external_seek)(void *p_app_ptr, void *p_file_handle, int64_t position);


// called to read from an external file
//
// p_app_ptr     - input, the p_app_ptr field from the mc_external_io_t structure
// p_file_handle - input, the file handle returned by the open function
// p_buffer      - input, a buffer for the data
// buffer_size   - input, the number of bytes to read
// return        - number of bytes actually read or 0 to indicate an error occurred

typedef int32_t (*pfn_mc_external_read)(void *p_app_ptr, void *p_file_handle, uint8_t *p_buffer, int32_t buffer_size);


// called to close an external file
//
// NOTE the user must set the file handle to an invalid value before
//      returning. The freed handle may be passed back to this function,
//      the user should check for an invalid value before using the handle
//
// p_app_ptr      - input, the p_app_ptr field from the mc_external_io_t structure
// pp_file_handle - input/output, the file handle returned by the open function
//                  be sure to set this to an invalid value during the close!

typedef void (*pfn_mc_external_close)(void *p_app_ptr, void **pp_file_handle);


typedef struct
{
    pfn_mc_external_open    p_open;
    pfn_mc_external_openW   p_openW;
    pfn_mc_external_seek    p_seek;
    pfn_mc_external_read    p_read;
    pfn_mc_external_close   p_close;

    int64_t                 file_size;     // size of the file in bytes
    void                   *p_app_ptr;     // application defined pointer passed back to the external I/O callbacks

}mc_external_io_t;


//---------------------------------- state information -----------------------------------------

// used to retrieve state information from a component, which
// can be used to initialize the component again to the saved state
//
// set the state_info pointer to NULL to have the state_info_len
// field filled with the size needed for the state_info buffer

typedef struct mc_state_info_s
{
    int32_t state_info_len;                // length of the state information
    void *p_state_info;                    // pointer to the state information

    uint8_t reserved[64];

} mc_state_info_t;

typedef struct mc_video_dec_features_s {
	int struct_size;
	/* major features */
	int smp_modes;
	int max_num_threads;
	int reserved1[10];
	int hwacc_modes;
	int reserved2[40];
	int mcvesa;
	int reserved3[40];
	int loop_filter;
	int postprocessing_filter;
	int reserved4[100];
	/* minor features */
	int brightness_control;
	int contrast_control;
	int error_concealment;
	int reserved5[10];
	int error_resilience;
	int transform_precision;
	int mv_precision;
	int low_latency;
	int osd;
	int get_pic_delayed;
	int chroma_upsampling;
	int deinterlacing_modes;
	int ignore_cropping;
	int reserved6[100];
	/* obsolete features */
	int half_resolution;
	int double_rate;
	int reserved7[100];
} mc_video_dec_features_t;


//---------------------------------- frame colorspace information -----------------------------------------

/** \brief  frame color space information

The frame_colorspace_info_tt structure is used to define frame color space parameters.
*/
typedef struct
{
    uint32_t width;                 ///< Frame width
    uint32_t height;                ///< Frame height
    uint32_t fourcc;                ///< FourCC format
    uint32_t planes;                ///< Number of planes 
    int32_t  stride[4];             ///< Offset for each line in the planes. Use negative values for upside down images.
    int32_t  plane_offset[4];       ///< Offset for the planes
    uint32_t frame_size;            ///< Size of frame buffer
    uint32_t plane_height[4];       ///< Height of plane
    uint32_t reserved[4];
} frame_colorspace_info_tt;

/** \brief  license callback command IDs

The mc_license_command_id enum is used in license GET_RC callback function to request size and copy license data

LICENSE_GET_DATA_SIZE - request to set size of license data
LICENSE_GET_DATA      - request to copy license data to buffer
*/
#ifndef _MC_LICENSE_COMMAND_DEFINED_
#define _MC_LICENSE_COMMAND_DEFINED_
enum mc_license_command_id
{
    LICENSE_GET_DATA_SIZE,
    LICENSE_GET_DATA
};
#endif // _MC_LICENSE_COMMAND_DEFINED_

#ifndef __APPLE__
#pragma pack(pop)
#endif

#endif // #if !defined (__MC_DEFS_INCLUDED__)

