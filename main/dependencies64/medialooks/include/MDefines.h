

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Apr 30 12:54:31 2015
 */
/* Compiler settings for ..\..\Include\IDL\MDefines.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __MDefines_h__
#define __MDefines_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

/* header files for imported files */
#include "basetsd.h"
#include "unknwn.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_MDefines_0000_0000 */
/* [local] */ 

typedef LONGLONG REFERENCE_TIME;


#ifndef PIC_PROPS_DEFINED
#define PIC_PROPS_DEFINED
typedef struct PIC_PROPS
    {
    int fccType;
    int nWidth;
    int nHeight;
    int nRowWidth;
    } 	PIC_PROPS;

#endif
#ifndef M_DEFINES_INCLUDED
#define M_DEFINES_INCLUDED
typedef /* [v1_enum] */ 
enum eMState
    {	eMS_Error	= -1,
	eMS_Closed	= 0,
	eMS_Stopped	= ( eMS_Closed + 1 ) ,
	eMS_Paused	= ( eMS_Stopped + 1 ) ,
	eMS_Running	= ( eMS_Paused + 1 ) ,
	eMS_Break	= ( eMS_Running + 1 ) 
    } 	eMState;

typedef struct M_DATETIME
    {
    int nYear;
    int nMonth;
    int nDay;
    int nHour;
    int nMinute;
    int nSecond;
    int nMilliseconds;
    } 	M_DATETIME;

typedef /* [v1_enum] */ 
enum eMTimecodeFlags
    {	eMTCF_NonDropFrame	= 0,
	eMTCF_DropFrame	= 1,
	eMTCF_Rate_24	= 0x10,
	eMTCF_Rate_25	= 0x20,
	eMTCF_Rate_30_DF	= 0x41,
	eMTCF_Rate_30	= 0x40,
	eMTCF_Rate	= 0xff0,
	eMTCF_Progressive_Even_Frame	= 0x100,
	eMTCF_Progressive_Odd_Frame	= 0x200,
	eMTCF_Rate_50	= 0x120,
	eMTCF_Rate_60_DF	= 0x141,
	eMTCF_Rate_60	= 0x140,
	eMTCF_Rate_50_Even	= 0x220,
	eMTCF_Rate_60_DF_Even	= 0x241,
	eMTCF_Rate_60_Even	= 0x240,
	eMTCF_SrcTC	= 0x1000,
	eMTCF_SrcTC_DropFrame	= 0x1001,
	eMTCF_SrcTC_Rate_24	= 0x1010,
	eMTCF_SrcTC_Rate_25	= 0x1020,
	eMTCF_SrcTC_Rate_30_DF	= 0x1041,
	eMTCF_SrcTC_Rate_30	= 0x1040,
	eMTCF_SrcTC_Progressive_Even_Frame	= 0x1100,
	eMTCF_SrcTC_Progressive_Odd_Frame	= 0x1200,
	eMTCF_SrcTC_Rate_50	= 0x1120,
	eMTCF_SrcTC_Rate_60_DF	= 0x1141,
	eMTCF_SrcTC_Rate_60	= 0x1140,
	eMTCF_SrcTC_Rate_50_Even	= 0x1220,
	eMTCF_SrcTC_Rate_60_DF_Even	= 0x1241,
	eMTCF_SrcTC_Rate_60_Even	= 0x1240,
	eMTCF_UserTC	= 0x2000,
	eMTCF_UserTC_DropFrame	= 0x2001,
	eMTCF_UserTC_Rate_24	= 0x2010,
	eMTCF_UserTC_Rate_25	= 0x2020,
	eMTCF_UserTC_Rate_30_DF	= 0x2041,
	eMTCF_UserTC_Rate_30	= 0x2040,
	eMTCF_UserTC_Progressive_Even_Frame	= 0x2100,
	eMTCF_UserTC_Progressive_Odd_Frame	= 0x2200,
	eMTCF_UserTC_Rate_50	= 0x2120,
	eMTCF_UserTC_Rate_60_DF	= 0x2141,
	eMTCF_UserTC_Rate_60	= 0x2140,
	eMTCF_UserTC_Rate_50_Even	= 0x2220,
	eMTCF_UserTC_Rate_60_DF_Even	= 0x2241,
	eMTCF_UserTC_Rate_60_Even	= 0x2240,
	eMTCF_LocalTimeTC	= 0x10000,
	eMTCF_Invalid	= 0x80000000
    } 	eMTimecodeFlags;

typedef struct M_TIMECODE
    {
    int nHours;
    int nMinutes;
    int nSeconds;
    int nFrames;
    eMTimecodeFlags eTCFlags;
    int nExtraCounter;
    } 	M_TIMECODE;

typedef /* [v1_enum] */ 
enum eMFCC
    {	eMFCC_Default	= 0,
	eMFCC_r210	= 0x30313272,
	eMFCC_v210	= 0x30313276,
	eMFCC_I420	= 0x30323449,
	eMFCC_YV12	= 0x32315659,
	eMFCC_NV12	= 0x3231564e,
	eMFCC_YUY2	= 0x32595559,
	eMFCC_HDYC	= 0x43594448,
	eMFCC_YVYU	= 0x55595659,
	eMFCC_UYVY	= 0x59565955,
	eMFCC_RGB24	= 0xe436eb7d,
	eMFCC_RGB32	= 0xe436eb7e,
	eMFCC_ARGB32	= 0x773c9ac0,
	eMFCC_RGB8	= 0xe436eb7a,
	eMFCC_GPU_YUV422	= 0x65ffaf79,
	eMFCC_GPU_RGB444	= 0x65ffaf80
    } 	eMFCC;

typedef /* [v1_enum] */ 
enum eMScaleType
    {	eMST_Default	= 0,
	eMST_None	= ( eMST_Default + 1 ) ,
	eMST_LetterBox	= ( eMST_None + 1 ) ,
	eMST_Crop	= ( eMST_LetterBox + 1 ) ,
	eMST_NoScale	= ( eMST_Crop + 1 ) 
    } 	eMScaleType;

typedef /* [v1_enum] */ 
enum eMInterlace
    {	eMI_Default	= 0,
	eMI_Field1First	= 0x1,
	eMI_Field2First	= 0x2,
	eMI_Progressive	= 0x3,
	eMI_Inverse	= 0x4,
	eMI_OneField	= 0x5,
	eMI_DeinterlaceF1	= 0x100,
	eMI_DeinterlaceF2	= 0x200
    } 	eMInterlace;

typedef /* [v1_enum] */ 
enum eM3DFormat
    {	eM3D_None	= 0,
	eM3D_Auto	= 0x1,
	eM3D_SideBySide	= 0x200,
	eM3D_TopAndBottom	= 0x400,
	eM3D_Tile	= 0x800,
	eM3D_FullFlag	= 0x1000,
	eM3D_FullSideBySide	= 0x1200,
	eM3D_FullTopAndBottom	= 0x1400
    } 	eM3DFormat;

typedef /* [v1_enum] */ 
enum eMVideoFormat
    {	
	eMVF_Custom	= 0,
	eMVF_NTSC	= ( eMVF_Custom + 1 ) ,
	eMVF_NTSC_2398	= ( eMVF_NTSC + 1 ) ,
	eMVF_NTSC_16x9	= ( eMVF_NTSC_2398 + 1 ) ,
	eMVF_PAL	= ( eMVF_NTSC_16x9 + 1 ) ,
	eMVF_PAL_16x9	= ( eMVF_PAL + 1 ) ,
	eMVF_HD720_50p	= ( eMVF_PAL_16x9 + 1 ) ,
	eMVF_HD720_5994p	= ( eMVF_HD720_50p + 1 ) ,
	eMVF_HD720_60p	= ( eMVF_HD720_5994p + 1 ) ,
	eMVF_HD1080_2398p	= ( eMVF_HD720_60p + 1 ) ,
	eMVF_HD1080_24p	= ( eMVF_HD1080_2398p + 1 ) ,
	eMVF_HD1080_25p	= ( eMVF_HD1080_24p + 1 ) ,
	eMVF_HD1080_2997p	= ( eMVF_HD1080_25p + 1 ) ,
	eMVF_HD1080_30p	= ( eMVF_HD1080_2997p + 1 ) ,
	eMVF_HD1080_50i	= ( eMVF_HD1080_30p + 1 ) ,
	eMVF_HD1080_5994i	= ( eMVF_HD1080_50i + 1 ) ,
	eMVF_HD1080_60i	= ( eMVF_HD1080_5994i + 1 ) ,
	eMVF_HD1080_50p	= ( eMVF_HD1080_60i + 1 ) ,
	eMVF_HD1080_5994p	= ( eMVF_HD1080_50p + 1 ) ,
	eMVF_HD1080_60p	= ( eMVF_HD1080_5994p + 1 ) ,
	eMVF_2K_2398p	= ( eMVF_HD1080_60p + 1 ) ,
	eMVF_2K_24p	= ( eMVF_2K_2398p + 1 ) ,
	eMVF_2K_25p	= ( eMVF_2K_24p + 1 ) ,
	eMVF_4K_UHD_50i	= ( eMVF_2K_25p + 1 ) ,
	eMVF_4K_UHD_5994i	= ( eMVF_4K_UHD_50i + 1 ) ,
	eMVF_4K_UHD_60i	= ( eMVF_4K_UHD_5994i + 1 ) ,
	eMVF_4K_UHD_2398p	= ( eMVF_4K_UHD_60i + 1 ) ,
	eMVF_4K_UHD_24p	= ( eMVF_4K_UHD_2398p + 1 ) ,
	eMVF_4K_UHD_25p	= ( eMVF_4K_UHD_24p + 1 ) ,
	eMVF_4K_UHD_2997p	= ( eMVF_4K_UHD_25p + 1 ) ,
	eMVF_4K_UHD_30p	= ( eMVF_4K_UHD_2997p + 1 ) ,
	eMVF_4K_DCI_2398p	= ( eMVF_4K_UHD_30p + 1 ) ,
	eMVF_4K_DCI_24p	= ( eMVF_4K_DCI_2398p + 1 ) ,
	eMVF_4K_DCI_25p	= ( eMVF_4K_DCI_24p + 1 ) ,
	eMVF_Disabled	= ( eMVF_4K_DCI_25p + 1 ) ,
	eMVF_3D_SbS_720_50p	= ( eMVF_HD720_50p + 0x200 ) ,
	eMVF_3D_SbS_720_5994p	= ( eMVF_HD720_5994p + 0x200 ) ,
	eMVF_3D_SbS_720_60p	= ( eMVF_HD720_60p + 0x200 ) ,
	eMVF_3D_SbS_1080_2398p	= ( eMVF_HD1080_2398p + 0x200 ) ,
	eMVF_3D_SbS_1080_24p	= ( eMVF_HD1080_24p + 0x200 ) ,
	eMVF_3D_SbS_1080_25p	= ( eMVF_HD1080_25p + 0x200 ) ,
	eMVF_3D_SbS_1080_2997p	= ( eMVF_HD1080_2997p + 0x200 ) ,
	eMVF_3D_SbS_1080_30p	= ( eMVF_HD1080_30p + 0x200 ) ,
	eMVF_3D_SbS_1080_50i	= ( eMVF_HD1080_50i + 0x200 ) ,
	eMVF_3D_SbS_1080_5994i	= ( eMVF_HD1080_5994i + 0x200 ) ,
	eMVF_3D_SbS_1080_60i	= ( eMVF_HD1080_60i + 0x200 ) ,
	eMVF_3D_SbS_1080_50p	= ( eMVF_HD1080_50p + 0x200 ) ,
	eMVF_3D_SbS_1080_5994p	= ( eMVF_HD1080_5994p + 0x200 ) ,
	eMVF_3D_SbS_1080_60p	= ( eMVF_HD1080_60p + 0x200 ) ,
	eMVF_3D_TnB_720_50p	= ( eMVF_HD720_50p + 0x400 ) ,
	eMVF_3D_TnB_720_5994p	= ( eMVF_HD720_5994p + 0x400 ) ,
	eMVF_3D_TnB_720_60p	= ( eMVF_HD720_60p + 0x400 ) ,
	eMVF_3D_TnB_1080_2398p	= ( eMVF_HD1080_2398p + 0x400 ) ,
	eMVF_3D_TnB_1080_24p	= ( eMVF_HD1080_24p + 0x400 ) ,
	eMVF_3D_TnB_1080_25p	= ( eMVF_HD1080_25p + 0x400 ) ,
	eMVF_3D_TnB_1080_2997p	= ( eMVF_HD1080_2997p + 0x400 ) ,
	eMVF_3D_TnB_1080_30p	= ( eMVF_HD1080_30p + 0x400 ) ,
	eMVF_3D_TnB_1080_50p	= ( eMVF_HD1080_50p + 0x400 ) ,
	eMVF_3D_TnB_1080_5994p	= ( eMVF_HD1080_5994p + 0x400 ) ,
	eMVF_3D_TnB_1080_60p	= ( eMVF_HD1080_60p + 0x400 ) ,
	eMVF_3D_Full_SbS_1080_2398p	= ( eMVF_HD1080_2398p + 0x1200 ) ,
	eMVF_3D_Full_SbS_1080_24p	= ( eMVF_HD1080_24p + 0x1200 ) ,
	eMVF_3D_Full_SbS_1080_25p	= ( eMVF_HD1080_25p + 0x1200 ) ,
	eMVF_3D_Full_SbS_1080_2997p	= ( eMVF_HD1080_2997p + 0x1200 ) ,
	eMVF_3D_Full_SbS_1080_30p	= ( eMVF_HD1080_30p + 0x1200 ) ,
	eMVF_3D_Full_SbS_1080_50i	= ( eMVF_HD1080_50i + 0x1200 ) ,
	eMVF_3D_Full_SbS_1080_5994i	= ( eMVF_HD1080_5994i + 0x1200 ) ,
	eMVF_3D_Full_SbS_1080_60i	= ( eMVF_HD1080_60i + 0x1200 ) ,
	eMVF_3D_Full_SbS_720_50p	= ( eMVF_HD720_50p + 0x1200 ) ,
	eMVF_3D_Full_SbS_720_5994p	= ( eMVF_HD720_5994p + 0x1200 ) ,
	eMVF_3D_Full_SbS_720_60p	= ( eMVF_HD720_60p + 0x1200 ) ,
	eMVF_3D_Full_TnB_1080_2398p	= ( eMVF_HD1080_2398p + 0x1400 ) ,
	eMVF_3D_Full_TnB_1080_24p	= ( eMVF_HD1080_24p + 0x1400 ) ,
	eMVF_3D_Full_TnB_1080_25p	= ( eMVF_HD1080_25p + 0x1400 ) ,
	eMVF_3D_Full_TnB_1080_2997p	= ( eMVF_HD1080_2997p + 0x1400 ) ,
	eMVF_3D_Full_TnB_1080_30p	= ( eMVF_HD1080_30p + 0x1400 ) ,
	eMVF_3D_Full_TnB_1080_50i	= ( eMVF_HD1080_50i + 0x1400 ) ,
	eMVF_3D_Full_TnB_1080_5994i	= ( eMVF_HD1080_5994i + 0x1400 ) ,
	eMVF_3D_Full_TnB_1080_60i	= ( eMVF_HD1080_60i + 0x1400 ) ,
	eMVF_3D_Full_TnB_720_50p	= ( eMVF_HD720_50p + 0x1400 ) ,
	eMVF_3D_Full_TnB_720_5994p	= ( eMVF_HD720_5994p + 0x1400 ) ,
	eMVF_3D_Full_TnB_720_60p	= ( eMVF_HD720_60p + 0x1400 ) 
    } 	eMVideoFormat;

typedef struct M_VID_PROPS
    {
    eMVideoFormat eVideoFormat;
    eMFCC fccType;
    int nWidth;
    int nHeight;
    int nRowBytes;
    eMInterlace eInterlace;
    short nAspectX;
    short nAspectY;
    double dblRate;
    eMScaleType eScaleType;
    eM3DFormat e3DFormat;
    } 	M_VID_PROPS;

typedef struct M_VID_PROPS_EX
    {
    eMVideoFormat eVideoFormat;
    eMFCC fccType;
    int nWidth;
    int nHeight;
    int nRowBytes;
    eMInterlace eInterlace;
    short nAspectX;
    short nAspectY;
    double dblRate;
    eMScaleType eScaleType;
    eM3DFormat e3DFormat;
    LONGLONG m_llAudioSamples;
    long m_arrPlanesRowBytes[ 4 ];
    long m_arrPlanesOffset[ 4 ];
    } 	M_VID_PROPS_EX;

typedef struct M_AUD_PROPS
    {
    int nChannels;
    int nSamplesPerSec;
    int nBitsPerSample;
    int nTrackSplitBits;
    } 	M_AUD_PROPS;

typedef /* [v1_enum] */ 
enum eMFormatType
    {	eMFT_Input	= 0,
	eMFT_Convert	= 1,
	eMFT_Override	= 2,
	eMFT_Output	= 3
    } 	eMFormatType;

typedef /* [v1_enum] */ 
enum eMFrameFlags
    {	eMFF_None	= 0,
	eMFF_Break	= 1,
	eMFF_Last	= 2,
	eMFF_Dup	= 0x11,
	eMFF_Pause	= 0x21,
	eMFF_Last_Dup	= 0x13,
	eMFF_Last_Pause	= 0x23,
	eMFF_Live	= 0x100,
	eMFF_Net	= 0x200,
	eMFF_Reverse	= 0x1000,
	eMFF_Main_Mask	= 0xffff,
	eMFF_Intra	= 0x10000,
	eMFF_Predicted	= 0x20000,
	eMFF_Bidir_Predicted	= 0x30000,
	eMFF_S_GMC_VOP_MPEG4	= 0x40000,
	eMFF_Switching_Intra	= 0x50000,
	eMFF_Switching_Predicted	= 0x60000,
	eMFF_BI	= 0x70000,
	eMFF_Type_Mask	= 0xf0000,
	eMFF_Break_Last	= 3,
	eMFF_Live_Break	= 0x101,
	eMFF_Live_Last	= 0x102,
	eMFF_Live_Break_Last	= 0x103,
	eMFF_Net_Break	= 0x201,
	eMFF_Net_Last	= 0x202,
	eMFF_Net_Break_Last	= 0x203,
	eMFF_Break_Intra	= 0x10001,
	eMFF_Break_Predicted	= 0x20001,
	eMFF_Break_Bidir_Predicted	= 0x30001,
	eMFF_Break_S_GMC_VOP_MPEG4	= 0x40001,
	eMFF_Break_Switching_Intra	= 0x50001,
	eMFF_Break_Switching_Predicted	= 0x60001,
	eMFF_Break_BI	= 0x70001,
	eMFF_Net_Intra	= 0x10200,
	eMFF_Net_Predicted	= 0x20200,
	eMFF_Net_Bidir_Predicted	= 0x30200,
	eMFF_Net_S_GMC_VOP_MPEG4	= 0x40200,
	eMFF_Net_Switching_Intra	= 0x50200,
	eMFF_Net_Switching_Predicted	= 0x60200,
	eMFF_Net_BI	= 0x70200,
	eMFF_Net_Break_Intra	= 0x10201,
	eMFF_Net_Break_Predicted	= 0x20201,
	eMFF_Net_Break_Bidir_Predicted	= 0x30201,
	eMFF_Net_Break_S_GMC_VOP_MPEG4	= 0x40201,
	eMFF_Net_Break_Switching_Intra	= 0x50201,
	eMFF_Net_Break_Switching_Predicted	= 0x60201,
	eMFF_Net_Break_BI	= 0x70201
    } 	eMFrameFlags;

typedef struct M_TIME
    {
    REFERENCE_TIME rtStartTime;
    REFERENCE_TIME rtEndTime;
    M_TIMECODE tcFrame;
    eMFrameFlags eFFlags;
    } 	M_TIME;

typedef /* [v1_enum] */ 
enum eMANCFlags
    {	eMAF_None	= 0,
	eMAF_AL_Valid	= 0x2
    } 	eMANCFlags;

typedef struct M_AUDIO_LOUDNESS
    {
    float arrVUMeter[ 32 ];
    float arrVUPeaks[ 32 ];
    float arrRMS[ 32 ];
    float arrEBUMode_M[ 32 ];
    float arrEBUMode_S[ 32 ];
    float arrEBUMode_I[ 32 ];
    float arrPeaks_QPPM[ 32 ];
    float arrPeaks_TPL[ 32 ];
    int nValidChannels;
    int nValidTracks;
    int nTracksSplitBit;
    } 	M_AUDIO_LOUDNESS;

typedef struct M_ANC_DATA
    {
    eMANCFlags eFlags;
    M_AUDIO_LOUDNESS audOriginal;
    M_AUDIO_LOUDNESS audOutput;
    } 	M_ANC_DATA;

typedef struct M_AV_PROPS
    {
    M_VID_PROPS vidProps;
    M_AUD_PROPS audProps;
    M_ANC_DATA ancData;
    BOOL bLocked;
    } 	M_AV_PROPS;

typedef struct M_AV_PROPS_EX
    {
    M_VID_PROPS_EX vidProps;
    M_AUD_PROPS audProps;
    M_ANC_DATA ancData;
    BOOL bLocked;
    } 	M_AV_PROPS_EX;

typedef struct M_AUDIO_TRACK_LOUDNESS
    {
    float arrVUMeter[ 32 ];
    float arrVUPeaks[ 32 ];
    float arrRMS[ 32 ];
    float arrEBUMode_M;
    float arrEBUMode_S;
    float arrEBUMode_I;
    float arrPeaks_QPPM;
    float arrPeaks_TPL;
    int nValidChannels;
    } 	M_AUDIO_TRACK_LOUDNESS;

typedef /* [v1_enum] */ 
enum eMAudioTrackMode
    {	eMAT_Disabled	= 0,
	eMAT_Enabled	= ( eMAT_Disabled + 1 ) ,
	eMAT_Exclusive	= ( eMAT_Enabled + 1 ) ,
	eMAT_Mix_Exclusive	= ( eMAT_Exclusive + 1 ) ,
	eMAT_Enabled_AddTo	= ( eMAT_Mix_Exclusive + 1 ) ,
	eMAT_Disabled_AddTo	= ( eMAT_Enabled_AddTo + 1 ) 
    } 	eMAudioTrackMode;

typedef /* [v1_enum] */ 
enum eMItemType
    {	eMPIT_File	= 0,
	eMPIT_Live	= ( eMPIT_File + 1 ) ,
	eMPIT_Playlist	= ( eMPIT_Live + 1 ) ,
	eMPIT_Command	= ( eMPIT_Playlist + 1 ) 
    } 	eMItemType;

typedef /* [v1_enum] */ 
enum eMStartType
    {	eMST_Off	= 0,
	eMST_Auto	= ( eMST_Off + 1 ) ,
	eMST_Specified	= ( eMST_Auto + 1 ) 
    } 	eMStartType;

typedef /* [v1_enum] */ 
enum eMCursorType
    {	eMCT_ARROW	= 32512,
	eMCT_IBEAM	= 32513,
	eMCT_WAIT	= 32514,
	eMCT_CROSS	= 32515,
	eMCT_UPARROW	= 32516,
	eMCT_SIZE	= 32640,
	eMCT_ICON	= 32641,
	eMCT_SIZENWSE	= 32642,
	eMCT_SIZENESW	= 32643,
	eMCT_SIZEWE	= 32644,
	eMCT_SIZENS	= 32645,
	eMCT_SIZEALL	= 32646,
	eMCT_NO	= 32648,
	eMCT_HAND	= 32649,
	eMCT_APPSTARTING	= 32650
    } 	eMCursorType;

typedef /* [v1_enum] */ 
enum eMMoveOption
    {	eMMO_Cursor	= 0,
	eMMO_Done	= 0x1,
	eMMO_Start	= 0x2,
	eMMO_Right	= 0x4,
	eMMO_Left	= 0x8,
	eMMO_Start_Right	= 0x6,
	eMMO_Start_Left	= 0xa,
	eMMO_Done_Right	= 0x5,
	eMMO_Done_Left	= 0x9
    } 	eMMoveOption;

typedef /* [v1_enum] */ 
enum eMUpdateType
    {	eMUT_AddNew	= 0,
	eMUT_Update	= 1,
	eMUT_ClearDest	= 2
    } 	eMUpdateType;

typedef /* [v1_enum] */ 
enum eMInfoType
    {	eMIT_Help	= 0,
	eMIT_Type	= ( eMIT_Help + 1 ) ,
	eMIT_Default	= ( eMIT_Type + 1 ) ,
	eMIT_Values	= ( eMIT_Default + 1 ) ,
	eMIT_Min	= ( eMIT_Values + 1 ) ,
	eMIT_Max	= ( eMIT_Min + 1 ) ,
	eMIT_Node	= ( eMIT_Max + 1 ) 
    } 	eMInfoType;

typedef /* [v1_enum] */ 
enum eMFrameClone
    {	eMFC_Props	= 0,
	eMFC_Video	= 0x1,
	eMFC_VideoRef	= 0x2,
	eMFC_Audio	= 0x10,
	eMFC_VideoRef_Audio	= 0x12,
	eMFC_Data	= 0x100,
	eMFC_Obj	= 0x200,
	eMFC_Data_Audio	= 0x110,
	eMFC_ObjData_Audio	= 0x310,
	eMFC_Reference	= 0x312,
	eMFC_Full	= 0x311
    } 	eMFrameClone;

typedef /* [v1_enum] */ 
enum eMBMDDeckControlError
    {	eMDCE_NoError	= 0x6e6f6572,
	eMDCE_pModeError	= 0x6d6f6572,
	eMDCE_MissedInPointError	= 0x6d696572,
	eMDCE_DeckTimeoutError	= 0x64746572,
	eMDCE_CommandFailedError	= 0x63666572,
	eMDCE_DeviceAlreadyOpenedError	= 0x64616c6f,
	eMDCE_FailedToOpenDeviceError	= 0x66646572,
	eMDCE_InLocalModeError	= 0x6c6d6572,
	eMDCE_EndOfTapeError	= 0x65746572,
	eMDCE_UserAbortError	= 0x75616572,
	eMDCE_NoTapeInDeckError	= 0x6e746572,
	eMDCE_NoVideoFromCardError	= 0x6e766663,
	eMDCE_NoCommunicationError	= 0x6e636f6d,
	eMDCE_BufferTooSmallError	= 0x6274736d,
	eMDCE_BadChecksumError	= 0x63686b73,
	eMDCE_UnknownError	= 0x756e6572
    } 	eMBMDDeckControlError;

typedef /* [v1_enum] */ 
enum eMBMDDeckControlMode
    {	eMDCM_NotOpened	= 0x6e746f70,
	eMDCM_VTRControlMode	= 0x76747263,
	eMDCM_ExportMode	= 0x6578706d,
	eMDCM_CaptureMode	= 0x6361706d
    } 	eMBMDDeckControlMode;

typedef /* [v1_enum] */ 
enum eMBMDDeckControlVTRControlState
    {	eMDCS_pMode	= 0x6e76636d,
	eMDCS_Playing	= 0x76747270,
	eMDCS_Recording	= 0x76747272,
	eMDCS_Still	= 0x76747261,
	eMDCS_ShuttleForward	= 0x76747366,
	eMDCS_ShuttleReverse	= 0x76747372,
	eMDCS_JogForward	= 0x76746a66,
	eMDCS_JogReverse	= 0x76746a72,
	eMDCS_Stopped	= 0x7674726f
    } 	eMBMDDeckControlVTRControlState;

typedef /* [v1_enum] */ 
enum eMBMDDeckControlEvent
    {	eMDCE_AbortedEvent	= 0x61627465,
	eMDCE_PrepareForExportEvent	= 0x70666565,
	eMDCE_ExportCompleteEvent	= 0x65786365,
	eMDCE_PrepareForCaptureEvent	= 0x70666365,
	eMDCE_CaptureCompleteEvent	= 0x63636576
    } 	eMBMDDeckControlEvent;

#endif // M_DEFINES_INCLUDED


extern RPC_IF_HANDLE __MIDL_itf_MDefines_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_MDefines_0000_0000_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


