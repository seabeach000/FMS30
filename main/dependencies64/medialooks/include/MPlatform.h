

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Apr 16 11:28:39 2015
 */
/* Compiler settings for ..\..\Include\IDL\MPlatform.idl:
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

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __MPlatform_h__
#define __MPlatform_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMAttributes_FWD_DEFINED__
#define __IMAttributes_FWD_DEFINED__
typedef interface IMAttributes IMAttributes;
#endif 	/* __IMAttributes_FWD_DEFINED__ */


#ifndef __IMNode_FWD_DEFINED__
#define __IMNode_FWD_DEFINED__
typedef interface IMNode IMNode;
#endif 	/* __IMNode_FWD_DEFINED__ */


#ifndef __IMCallback_FWD_DEFINED__
#define __IMCallback_FWD_DEFINED__
typedef interface IMCallback IMCallback;
#endif 	/* __IMCallback_FWD_DEFINED__ */


#ifndef __IMPreview_FWD_DEFINED__
#define __IMPreview_FWD_DEFINED__
typedef interface IMPreview IMPreview;
#endif 	/* __IMPreview_FWD_DEFINED__ */


#ifndef __IMFrame_FWD_DEFINED__
#define __IMFrame_FWD_DEFINED__
typedef interface IMFrame IMFrame;
#endif 	/* __IMFrame_FWD_DEFINED__ */


#ifndef __IMFrames_FWD_DEFINED__
#define __IMFrames_FWD_DEFINED__
typedef interface IMFrames IMFrames;
#endif 	/* __IMFrames_FWD_DEFINED__ */


#ifndef __IMProps_FWD_DEFINED__
#define __IMProps_FWD_DEFINED__
typedef interface IMProps IMProps;
#endif 	/* __IMProps_FWD_DEFINED__ */


#ifndef __IMPersist_FWD_DEFINED__
#define __IMPersist_FWD_DEFINED__
typedef interface IMPersist IMPersist;
#endif 	/* __IMPersist_FWD_DEFINED__ */


#ifndef __IMObject_FWD_DEFINED__
#define __IMObject_FWD_DEFINED__
typedef interface IMObject IMObject;
#endif 	/* __IMObject_FWD_DEFINED__ */


#ifndef __IMFormat_FWD_DEFINED__
#define __IMFormat_FWD_DEFINED__
typedef interface IMFormat IMFormat;
#endif 	/* __IMFormat_FWD_DEFINED__ */


#ifndef __IMAudioTrack_FWD_DEFINED__
#define __IMAudioTrack_FWD_DEFINED__
typedef interface IMAudioTrack IMAudioTrack;
#endif 	/* __IMAudioTrack_FWD_DEFINED__ */


#ifndef __IMAudio_FWD_DEFINED__
#define __IMAudio_FWD_DEFINED__
typedef interface IMAudio IMAudio;
#endif 	/* __IMAudio_FWD_DEFINED__ */


#ifndef __IMReceiver_FWD_DEFINED__
#define __IMReceiver_FWD_DEFINED__
typedef interface IMReceiver IMReceiver;
#endif 	/* __IMReceiver_FWD_DEFINED__ */


#ifndef __IMSenders_FWD_DEFINED__
#define __IMSenders_FWD_DEFINED__
typedef interface IMSenders IMSenders;
#endif 	/* __IMSenders_FWD_DEFINED__ */


#ifndef __IMFile_FWD_DEFINED__
#define __IMFile_FWD_DEFINED__
typedef interface IMFile IMFile;
#endif 	/* __IMFile_FWD_DEFINED__ */


#ifndef __IMItem_FWD_DEFINED__
#define __IMItem_FWD_DEFINED__
typedef interface IMItem IMItem;
#endif 	/* __IMItem_FWD_DEFINED__ */


#ifndef __IMPlaylist_FWD_DEFINED__
#define __IMPlaylist_FWD_DEFINED__
typedef interface IMPlaylist IMPlaylist;
#endif 	/* __IMPlaylist_FWD_DEFINED__ */


#ifndef __IMBreaks_FWD_DEFINED__
#define __IMBreaks_FWD_DEFINED__
typedef interface IMBreaks IMBreaks;
#endif 	/* __IMBreaks_FWD_DEFINED__ */


#ifndef __IMScheduler_FWD_DEFINED__
#define __IMScheduler_FWD_DEFINED__
typedef interface IMScheduler IMScheduler;
#endif 	/* __IMScheduler_FWD_DEFINED__ */


#ifndef __IMDevice_FWD_DEFINED__
#define __IMDevice_FWD_DEFINED__
typedef interface IMDevice IMDevice;
#endif 	/* __IMDevice_FWD_DEFINED__ */


#ifndef __IMPlugins_FWD_DEFINED__
#define __IMPlugins_FWD_DEFINED__
typedef interface IMPlugins IMPlugins;
#endif 	/* __IMPlugins_FWD_DEFINED__ */


#ifndef __IMPlugin_FWD_DEFINED__
#define __IMPlugin_FWD_DEFINED__
typedef interface IMPlugin IMPlugin;
#endif 	/* __IMPlugin_FWD_DEFINED__ */


#ifndef __IMElement_FWD_DEFINED__
#define __IMElement_FWD_DEFINED__
typedef interface IMElement IMElement;
#endif 	/* __IMElement_FWD_DEFINED__ */


#ifndef __IMElements_FWD_DEFINED__
#define __IMElements_FWD_DEFINED__
typedef interface IMElements IMElements;
#endif 	/* __IMElements_FWD_DEFINED__ */


#ifndef __IMScenes_FWD_DEFINED__
#define __IMScenes_FWD_DEFINED__
typedef interface IMScenes IMScenes;
#endif 	/* __IMScenes_FWD_DEFINED__ */


#ifndef __IMStreams_FWD_DEFINED__
#define __IMStreams_FWD_DEFINED__
typedef interface IMStreams IMStreams;
#endif 	/* __IMStreams_FWD_DEFINED__ */


#ifndef __IMWriter_FWD_DEFINED__
#define __IMWriter_FWD_DEFINED__
typedef interface IMWriter IMWriter;
#endif 	/* __IMWriter_FWD_DEFINED__ */


#ifndef __IMDeckControl_FWD_DEFINED__
#define __IMDeckControl_FWD_DEFINED__
typedef interface IMDeckControl IMDeckControl;
#endif 	/* __IMDeckControl_FWD_DEFINED__ */


#ifndef __IMConfig_FWD_DEFINED__
#define __IMConfig_FWD_DEFINED__
typedef interface IMConfig IMConfig;
#endif 	/* __IMConfig_FWD_DEFINED__ */


#ifndef __IMFactory_FWD_DEFINED__
#define __IMFactory_FWD_DEFINED__
typedef interface IMFactory IMFactory;
#endif 	/* __IMFactory_FWD_DEFINED__ */


#ifndef __IMSync_FWD_DEFINED__
#define __IMSync_FWD_DEFINED__
typedef interface IMSync IMSync;
#endif 	/* __IMSync_FWD_DEFINED__ */


#ifndef __IMSource_FWD_DEFINED__
#define __IMSource_FWD_DEFINED__
typedef interface IMSource IMSource;
#endif 	/* __IMSource_FWD_DEFINED__ */


#ifndef __IMSource_I_FWD_DEFINED__
#define __IMSource_I_FWD_DEFINED__
typedef interface IMSource_I IMSource_I;
#endif 	/* __IMSource_I_FWD_DEFINED__ */


#ifndef __IMFrame_I_FWD_DEFINED__
#define __IMFrame_I_FWD_DEFINED__
typedef interface IMFrame_I IMFrame_I;
#endif 	/* __IMFrame_I_FWD_DEFINED__ */


#ifndef __IMFrames_I_FWD_DEFINED__
#define __IMFrames_I_FWD_DEFINED__
typedef interface IMFrames_I IMFrames_I;
#endif 	/* __IMFrames_I_FWD_DEFINED__ */


#ifndef __IMDevice_I_FWD_DEFINED__
#define __IMDevice_I_FWD_DEFINED__
typedef interface IMDevice_I IMDevice_I;
#endif 	/* __IMDevice_I_FWD_DEFINED__ */


#ifndef __IMObject_I_FWD_DEFINED__
#define __IMObject_I_FWD_DEFINED__
typedef interface IMObject_I IMObject_I;
#endif 	/* __IMObject_I_FWD_DEFINED__ */


#ifndef __IMSender_I_FWD_DEFINED__
#define __IMSender_I_FWD_DEFINED__
typedef interface IMSender_I IMSender_I;
#endif 	/* __IMSender_I_FWD_DEFINED__ */


#ifndef __IMReceiver_I_FWD_DEFINED__
#define __IMReceiver_I_FWD_DEFINED__
typedef interface IMReceiver_I IMReceiver_I;
#endif 	/* __IMReceiver_I_FWD_DEFINED__ */


#ifndef __IMEvents_FWD_DEFINED__
#define __IMEvents_FWD_DEFINED__
typedef interface IMEvents IMEvents;
#endif 	/* __IMEvents_FWD_DEFINED__ */


#ifndef __MFactory_FWD_DEFINED__
#define __MFactory_FWD_DEFINED__

#ifdef __cplusplus
typedef class MFactory MFactory;
#else
typedef struct MFactory MFactory;
#endif /* __cplusplus */

#endif 	/* __MFactory_FWD_DEFINED__ */


#ifndef __MFrame_FWD_DEFINED__
#define __MFrame_FWD_DEFINED__

#ifdef __cplusplus
typedef class MFrame MFrame;
#else
typedef struct MFrame MFrame;
#endif /* __cplusplus */

#endif 	/* __MFrame_FWD_DEFINED__ */


#ifndef __MFrames_FWD_DEFINED__
#define __MFrames_FWD_DEFINED__

#ifdef __cplusplus
typedef class MFrames MFrames;
#else
typedef struct MFrames MFrames;
#endif /* __cplusplus */

#endif 	/* __MFrames_FWD_DEFINED__ */


#ifndef __MNode_FWD_DEFINED__
#define __MNode_FWD_DEFINED__

#ifdef __cplusplus
typedef class MNode MNode;
#else
typedef struct MNode MNode;
#endif /* __cplusplus */

#endif 	/* __MNode_FWD_DEFINED__ */


#ifndef __MProxy_FWD_DEFINED__
#define __MProxy_FWD_DEFINED__

#ifdef __cplusplus
typedef class MProxy MProxy;
#else
typedef struct MProxy MProxy;
#endif /* __cplusplus */

#endif 	/* __MProxy_FWD_DEFINED__ */


#ifndef __MPacker_FWD_DEFINED__
#define __MPacker_FWD_DEFINED__

#ifdef __cplusplus
typedef class MPacker MPacker;
#else
typedef struct MPacker MPacker;
#endif /* __cplusplus */

#endif 	/* __MPacker_FWD_DEFINED__ */


#ifndef __MSync_FWD_DEFINED__
#define __MSync_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSync MSync;
#else
typedef struct MSync MSync;
#endif /* __cplusplus */

#endif 	/* __MSync_FWD_DEFINED__ */


#ifndef __MSenders_FWD_DEFINED__
#define __MSenders_FWD_DEFINED__

#ifdef __cplusplus
typedef class MSenders MSenders;
#else
typedef struct MSenders MSenders;
#endif /* __cplusplus */

#endif 	/* __MSenders_FWD_DEFINED__ */


#ifndef __MPreview_FWD_DEFINED__
#define __MPreview_FWD_DEFINED__

#ifdef __cplusplus
typedef class MPreview MPreview;
#else
typedef struct MPreview MPreview;
#endif /* __cplusplus */

#endif 	/* __MPreview_FWD_DEFINED__ */


#ifndef __MFile_FWD_DEFINED__
#define __MFile_FWD_DEFINED__

#ifdef __cplusplus
typedef class MFile MFile;
#else
typedef struct MFile MFile;
#endif /* __cplusplus */

#endif 	/* __MFile_FWD_DEFINED__ */


#ifndef __MItem_FWD_DEFINED__
#define __MItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class MItem MItem;
#else
typedef struct MItem MItem;
#endif /* __cplusplus */

#endif 	/* __MItem_FWD_DEFINED__ */


#ifndef __MPlaylist_FWD_DEFINED__
#define __MPlaylist_FWD_DEFINED__

#ifdef __cplusplus
typedef class MPlaylist MPlaylist;
#else
typedef struct MPlaylist MPlaylist;
#endif /* __cplusplus */

#endif 	/* __MPlaylist_FWD_DEFINED__ */


#ifndef __MLive_FWD_DEFINED__
#define __MLive_FWD_DEFINED__

#ifdef __cplusplus
typedef class MLive MLive;
#else
typedef struct MLive MLive;
#endif /* __cplusplus */

#endif 	/* __MLive_FWD_DEFINED__ */


#ifndef __MRenderer_FWD_DEFINED__
#define __MRenderer_FWD_DEFINED__

#ifdef __cplusplus
typedef class MRenderer MRenderer;
#else
typedef struct MRenderer MRenderer;
#endif /* __cplusplus */

#endif 	/* __MRenderer_FWD_DEFINED__ */


#ifndef __MElement_FWD_DEFINED__
#define __MElement_FWD_DEFINED__

#ifdef __cplusplus
typedef class MElement MElement;
#else
typedef struct MElement MElement;
#endif /* __cplusplus */

#endif 	/* __MElement_FWD_DEFINED__ */


#ifndef __MMixer_FWD_DEFINED__
#define __MMixer_FWD_DEFINED__

#ifdef __cplusplus
typedef class MMixer MMixer;
#else
typedef struct MMixer MMixer;
#endif /* __cplusplus */

#endif 	/* __MMixer_FWD_DEFINED__ */


#ifndef __MComposer_FWD_DEFINED__
#define __MComposer_FWD_DEFINED__

#ifdef __cplusplus
typedef class MComposer MComposer;
#else
typedef struct MComposer MComposer;
#endif /* __cplusplus */

#endif 	/* __MComposer_FWD_DEFINED__ */


#ifndef __MWriter_FWD_DEFINED__
#define __MWriter_FWD_DEFINED__

#ifdef __cplusplus
typedef class MWriter MWriter;
#else
typedef struct MWriter MWriter;
#endif /* __cplusplus */

#endif 	/* __MWriter_FWD_DEFINED__ */


/* header files for imported files */
#include "basetsd.h"
#include "unknwn.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_MPlatform_0000_0000 */
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
    {	eMVF_Custom	= 0,
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


extern RPC_IF_HANDLE __MIDL_itf_MPlatform_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_MPlatform_0000_0000_v0_0_s_ifspec;

#ifndef __IMAttributes_INTERFACE_DEFINED__
#define __IMAttributes_INTERFACE_DEFINED__

/* interface IMAttributes */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMAttributes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F366001-473F-4ad5-A5C2-428FE0C8E03E")
    IMAttributes : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AttributesGetCount( 
            /* [out] */ int *_pnCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AttributesGetByIndex( 
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsName,
            /* [out] */ BSTR *_pbsValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AttributesRemove( 
            /* [in] */ BSTR _bsName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AttributesRemoveAll( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AttributesStringSet( 
            /* [in] */ BSTR _bsName,
            /* [in] */ BSTR _bsValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AttributesBoolSet( 
            /* [in] */ BSTR _bsName,
            /* [in] */ BOOL _bValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AttributesIntSet( 
            /* [in] */ BSTR _bsName,
            /* [in] */ int _nValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AttributesDoubleSet( 
            /* [in] */ BSTR _bsName,
            /* [in] */ double _dblValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AttributesHave( 
            /* [in] */ BSTR _bsName,
            /* [out] */ BOOL *_pbHave,
            /* [out] */ BSTR *_pbsValueOrDefault) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AttributesStringGet( 
            /* [in] */ BSTR _bsName,
            /* [out] */ BSTR *_pbsValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AttributesIntGet( 
            /* [in] */ BSTR _bsName,
            /* [out] */ int *_pnValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AttributesBoolGet( 
            /* [in] */ BSTR _bsName,
            /* [out] */ BOOL *_pbValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AttributesDoubleGet( 
            /* [in] */ BSTR _bsName,
            /* [out] */ double *_pdblValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AttributesMultipleSet( 
            /* [in] */ BSTR _bsAttributesList,
            /* [in] */ eMUpdateType _eUpdateType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AttributesSave( 
            /* [out] */ BSTR *_pbsAttributesList) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AttributesClone( 
            /* [out] */ IMAttributes **_ppClone) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AttributesSet( 
            /* [in] */ IMAttributes *_pAttributesList,
            /* [in] */ eMUpdateType _eUpdateType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AttributesInfoGetCount( 
            /* [out] */ int *_pnCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AttributesInfoGetByIndex( 
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AttributesInfoGet( 
            /* [in] */ BSTR _bsName,
            /* [in] */ eMInfoType _eType,
            /* [out] */ BSTR *_pbsInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AttributesValuesInfoGet( 
            /* [in] */ BSTR _bsName,
            /* [in] */ BSTR _bsValue,
            /* [in] */ BSTR _bsType,
            /* [out] */ BSTR *_pbsInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMAttributesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMAttributes * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMAttributes * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMAttributes * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesGetCount )( 
            IMAttributes * This,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesGetByIndex )( 
            IMAttributes * This,
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsName,
            /* [out] */ BSTR *_pbsValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesRemove )( 
            IMAttributes * This,
            /* [in] */ BSTR _bsName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesRemoveAll )( 
            IMAttributes * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesStringSet )( 
            IMAttributes * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ BSTR _bsValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesBoolSet )( 
            IMAttributes * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ BOOL _bValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesIntSet )( 
            IMAttributes * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ int _nValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesDoubleSet )( 
            IMAttributes * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ double _dblValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesHave )( 
            IMAttributes * This,
            /* [in] */ BSTR _bsName,
            /* [out] */ BOOL *_pbHave,
            /* [out] */ BSTR *_pbsValueOrDefault);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesStringGet )( 
            IMAttributes * This,
            /* [in] */ BSTR _bsName,
            /* [out] */ BSTR *_pbsValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesIntGet )( 
            IMAttributes * This,
            /* [in] */ BSTR _bsName,
            /* [out] */ int *_pnValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesBoolGet )( 
            IMAttributes * This,
            /* [in] */ BSTR _bsName,
            /* [out] */ BOOL *_pbValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesDoubleGet )( 
            IMAttributes * This,
            /* [in] */ BSTR _bsName,
            /* [out] */ double *_pdblValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesMultipleSet )( 
            IMAttributes * This,
            /* [in] */ BSTR _bsAttributesList,
            /* [in] */ eMUpdateType _eUpdateType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesSave )( 
            IMAttributes * This,
            /* [out] */ BSTR *_pbsAttributesList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesClone )( 
            IMAttributes * This,
            /* [out] */ IMAttributes **_ppClone);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesSet )( 
            IMAttributes * This,
            /* [in] */ IMAttributes *_pAttributesList,
            /* [in] */ eMUpdateType _eUpdateType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesInfoGetCount )( 
            IMAttributes * This,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesInfoGetByIndex )( 
            IMAttributes * This,
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesInfoGet )( 
            IMAttributes * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ eMInfoType _eType,
            /* [out] */ BSTR *_pbsInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesValuesInfoGet )( 
            IMAttributes * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ BSTR _bsValue,
            /* [in] */ BSTR _bsType,
            /* [out] */ BSTR *_pbsInfo);
        
        END_INTERFACE
    } IMAttributesVtbl;

    interface IMAttributes
    {
        CONST_VTBL struct IMAttributesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMAttributes_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMAttributes_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMAttributes_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMAttributes_AttributesGetCount(This,_pnCount)	\
    ( (This)->lpVtbl -> AttributesGetCount(This,_pnCount) ) 

#define IMAttributes_AttributesGetByIndex(This,_nIndex,_pbsName,_pbsValue)	\
    ( (This)->lpVtbl -> AttributesGetByIndex(This,_nIndex,_pbsName,_pbsValue) ) 

#define IMAttributes_AttributesRemove(This,_bsName)	\
    ( (This)->lpVtbl -> AttributesRemove(This,_bsName) ) 

#define IMAttributes_AttributesRemoveAll(This)	\
    ( (This)->lpVtbl -> AttributesRemoveAll(This) ) 

#define IMAttributes_AttributesStringSet(This,_bsName,_bsValue)	\
    ( (This)->lpVtbl -> AttributesStringSet(This,_bsName,_bsValue) ) 

#define IMAttributes_AttributesBoolSet(This,_bsName,_bValue)	\
    ( (This)->lpVtbl -> AttributesBoolSet(This,_bsName,_bValue) ) 

#define IMAttributes_AttributesIntSet(This,_bsName,_nValue)	\
    ( (This)->lpVtbl -> AttributesIntSet(This,_bsName,_nValue) ) 

#define IMAttributes_AttributesDoubleSet(This,_bsName,_dblValue)	\
    ( (This)->lpVtbl -> AttributesDoubleSet(This,_bsName,_dblValue) ) 

#define IMAttributes_AttributesHave(This,_bsName,_pbHave,_pbsValueOrDefault)	\
    ( (This)->lpVtbl -> AttributesHave(This,_bsName,_pbHave,_pbsValueOrDefault) ) 

#define IMAttributes_AttributesStringGet(This,_bsName,_pbsValue)	\
    ( (This)->lpVtbl -> AttributesStringGet(This,_bsName,_pbsValue) ) 

#define IMAttributes_AttributesIntGet(This,_bsName,_pnValue)	\
    ( (This)->lpVtbl -> AttributesIntGet(This,_bsName,_pnValue) ) 

#define IMAttributes_AttributesBoolGet(This,_bsName,_pbValue)	\
    ( (This)->lpVtbl -> AttributesBoolGet(This,_bsName,_pbValue) ) 

#define IMAttributes_AttributesDoubleGet(This,_bsName,_pdblValue)	\
    ( (This)->lpVtbl -> AttributesDoubleGet(This,_bsName,_pdblValue) ) 

#define IMAttributes_AttributesMultipleSet(This,_bsAttributesList,_eUpdateType)	\
    ( (This)->lpVtbl -> AttributesMultipleSet(This,_bsAttributesList,_eUpdateType) ) 

#define IMAttributes_AttributesSave(This,_pbsAttributesList)	\
    ( (This)->lpVtbl -> AttributesSave(This,_pbsAttributesList) ) 

#define IMAttributes_AttributesClone(This,_ppClone)	\
    ( (This)->lpVtbl -> AttributesClone(This,_ppClone) ) 

#define IMAttributes_AttributesSet(This,_pAttributesList,_eUpdateType)	\
    ( (This)->lpVtbl -> AttributesSet(This,_pAttributesList,_eUpdateType) ) 

#define IMAttributes_AttributesInfoGetCount(This,_pnCount)	\
    ( (This)->lpVtbl -> AttributesInfoGetCount(This,_pnCount) ) 

#define IMAttributes_AttributesInfoGetByIndex(This,_nIndex,_pbsName)	\
    ( (This)->lpVtbl -> AttributesInfoGetByIndex(This,_nIndex,_pbsName) ) 

#define IMAttributes_AttributesInfoGet(This,_bsName,_eType,_pbsInfo)	\
    ( (This)->lpVtbl -> AttributesInfoGet(This,_bsName,_eType,_pbsInfo) ) 

#define IMAttributes_AttributesValuesInfoGet(This,_bsName,_bsValue,_bsType,_pbsInfo)	\
    ( (This)->lpVtbl -> AttributesValuesInfoGet(This,_bsName,_bsValue,_bsType,_pbsInfo) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMAttributes_INTERFACE_DEFINED__ */


#ifndef __IMNode_INTERFACE_DEFINED__
#define __IMNode_INTERFACE_DEFINED__

/* interface IMNode */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMNode;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F366002-473F-4ad5-A5C2-428FE0C8E03E")
    IMNode : public IMAttributes
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NodeNameGet( 
            /* [out] */ BSTR *_pbsName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NodeNameSet( 
            /* [in] */ BSTR _bsName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NodeValueGet( 
            /* [out] */ BSTR *_pbsValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NodeValueSet( 
            /* [in] */ BSTR _bsValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NodePathGet( 
            /* [out] */ BSTR *_bsPath,
            /* [in] */ IMNode *_pRoot) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NodeParentGet( 
            /* [out] */ IMNode **_ppParent) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NodeDetach( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NodeGetCount( 
            /* [out] */ int *_pnCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NodeGetByIndex( 
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsName,
            /* [out] */ IMNode **_ppNode) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NodeAdd( 
            /* [in] */ BSTR _bsPath,
            /* [in] */ BSTR _bsValue,
            /* [out] */ IMNode **_ppNode) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NodeGet( 
            /* [in] */ BSTR _bsPath,
            /* [in] */ BOOL _bCreateNew,
            /* [out] */ IMNode **_ppNode) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NodeRemove( 
            /* [in] */ BSTR _bsPath) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NodeRemoveAll( 
            /* [in] */ BOOL _bRemoveAttributes) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NodeParse( 
            /* [in] */ BSTR _pbsXMLString,
            /* [in] */ BOOL _bUpdateName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NodeSave( 
            /* [out] */ BSTR *_pbsXMLString) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NodeClone( 
            /* [out] */ IMNode **_ppClone) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NodeSet( 
            /* [in] */ IMNode *_pNodeSet,
            /* [in] */ eMUpdateType _eUpdateType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NodeInfoGet( 
            /* [in] */ BSTR _bsInfoType,
            /* [out] */ BSTR *_pbsDecription) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMNodeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMNode * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMNode * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMNode * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesGetCount )( 
            IMNode * This,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesGetByIndex )( 
            IMNode * This,
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsName,
            /* [out] */ BSTR *_pbsValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesRemove )( 
            IMNode * This,
            /* [in] */ BSTR _bsName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesRemoveAll )( 
            IMNode * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesStringSet )( 
            IMNode * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ BSTR _bsValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesBoolSet )( 
            IMNode * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ BOOL _bValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesIntSet )( 
            IMNode * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ int _nValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesDoubleSet )( 
            IMNode * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ double _dblValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesHave )( 
            IMNode * This,
            /* [in] */ BSTR _bsName,
            /* [out] */ BOOL *_pbHave,
            /* [out] */ BSTR *_pbsValueOrDefault);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesStringGet )( 
            IMNode * This,
            /* [in] */ BSTR _bsName,
            /* [out] */ BSTR *_pbsValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesIntGet )( 
            IMNode * This,
            /* [in] */ BSTR _bsName,
            /* [out] */ int *_pnValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesBoolGet )( 
            IMNode * This,
            /* [in] */ BSTR _bsName,
            /* [out] */ BOOL *_pbValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesDoubleGet )( 
            IMNode * This,
            /* [in] */ BSTR _bsName,
            /* [out] */ double *_pdblValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesMultipleSet )( 
            IMNode * This,
            /* [in] */ BSTR _bsAttributesList,
            /* [in] */ eMUpdateType _eUpdateType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesSave )( 
            IMNode * This,
            /* [out] */ BSTR *_pbsAttributesList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesClone )( 
            IMNode * This,
            /* [out] */ IMAttributes **_ppClone);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesSet )( 
            IMNode * This,
            /* [in] */ IMAttributes *_pAttributesList,
            /* [in] */ eMUpdateType _eUpdateType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesInfoGetCount )( 
            IMNode * This,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesInfoGetByIndex )( 
            IMNode * This,
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesInfoGet )( 
            IMNode * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ eMInfoType _eType,
            /* [out] */ BSTR *_pbsInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesValuesInfoGet )( 
            IMNode * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ BSTR _bsValue,
            /* [in] */ BSTR _bsType,
            /* [out] */ BSTR *_pbsInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NodeNameGet )( 
            IMNode * This,
            /* [out] */ BSTR *_pbsName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NodeNameSet )( 
            IMNode * This,
            /* [in] */ BSTR _bsName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NodeValueGet )( 
            IMNode * This,
            /* [out] */ BSTR *_pbsValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NodeValueSet )( 
            IMNode * This,
            /* [in] */ BSTR _bsValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NodePathGet )( 
            IMNode * This,
            /* [out] */ BSTR *_bsPath,
            /* [in] */ IMNode *_pRoot);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NodeParentGet )( 
            IMNode * This,
            /* [out] */ IMNode **_ppParent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NodeDetach )( 
            IMNode * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NodeGetCount )( 
            IMNode * This,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NodeGetByIndex )( 
            IMNode * This,
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsName,
            /* [out] */ IMNode **_ppNode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NodeAdd )( 
            IMNode * This,
            /* [in] */ BSTR _bsPath,
            /* [in] */ BSTR _bsValue,
            /* [out] */ IMNode **_ppNode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NodeGet )( 
            IMNode * This,
            /* [in] */ BSTR _bsPath,
            /* [in] */ BOOL _bCreateNew,
            /* [out] */ IMNode **_ppNode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NodeRemove )( 
            IMNode * This,
            /* [in] */ BSTR _bsPath);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NodeRemoveAll )( 
            IMNode * This,
            /* [in] */ BOOL _bRemoveAttributes);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NodeParse )( 
            IMNode * This,
            /* [in] */ BSTR _pbsXMLString,
            /* [in] */ BOOL _bUpdateName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NodeSave )( 
            IMNode * This,
            /* [out] */ BSTR *_pbsXMLString);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NodeClone )( 
            IMNode * This,
            /* [out] */ IMNode **_ppClone);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NodeSet )( 
            IMNode * This,
            /* [in] */ IMNode *_pNodeSet,
            /* [in] */ eMUpdateType _eUpdateType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NodeInfoGet )( 
            IMNode * This,
            /* [in] */ BSTR _bsInfoType,
            /* [out] */ BSTR *_pbsDecription);
        
        END_INTERFACE
    } IMNodeVtbl;

    interface IMNode
    {
        CONST_VTBL struct IMNodeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMNode_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMNode_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMNode_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMNode_AttributesGetCount(This,_pnCount)	\
    ( (This)->lpVtbl -> AttributesGetCount(This,_pnCount) ) 

#define IMNode_AttributesGetByIndex(This,_nIndex,_pbsName,_pbsValue)	\
    ( (This)->lpVtbl -> AttributesGetByIndex(This,_nIndex,_pbsName,_pbsValue) ) 

#define IMNode_AttributesRemove(This,_bsName)	\
    ( (This)->lpVtbl -> AttributesRemove(This,_bsName) ) 

#define IMNode_AttributesRemoveAll(This)	\
    ( (This)->lpVtbl -> AttributesRemoveAll(This) ) 

#define IMNode_AttributesStringSet(This,_bsName,_bsValue)	\
    ( (This)->lpVtbl -> AttributesStringSet(This,_bsName,_bsValue) ) 

#define IMNode_AttributesBoolSet(This,_bsName,_bValue)	\
    ( (This)->lpVtbl -> AttributesBoolSet(This,_bsName,_bValue) ) 

#define IMNode_AttributesIntSet(This,_bsName,_nValue)	\
    ( (This)->lpVtbl -> AttributesIntSet(This,_bsName,_nValue) ) 

#define IMNode_AttributesDoubleSet(This,_bsName,_dblValue)	\
    ( (This)->lpVtbl -> AttributesDoubleSet(This,_bsName,_dblValue) ) 

#define IMNode_AttributesHave(This,_bsName,_pbHave,_pbsValueOrDefault)	\
    ( (This)->lpVtbl -> AttributesHave(This,_bsName,_pbHave,_pbsValueOrDefault) ) 

#define IMNode_AttributesStringGet(This,_bsName,_pbsValue)	\
    ( (This)->lpVtbl -> AttributesStringGet(This,_bsName,_pbsValue) ) 

#define IMNode_AttributesIntGet(This,_bsName,_pnValue)	\
    ( (This)->lpVtbl -> AttributesIntGet(This,_bsName,_pnValue) ) 

#define IMNode_AttributesBoolGet(This,_bsName,_pbValue)	\
    ( (This)->lpVtbl -> AttributesBoolGet(This,_bsName,_pbValue) ) 

#define IMNode_AttributesDoubleGet(This,_bsName,_pdblValue)	\
    ( (This)->lpVtbl -> AttributesDoubleGet(This,_bsName,_pdblValue) ) 

#define IMNode_AttributesMultipleSet(This,_bsAttributesList,_eUpdateType)	\
    ( (This)->lpVtbl -> AttributesMultipleSet(This,_bsAttributesList,_eUpdateType) ) 

#define IMNode_AttributesSave(This,_pbsAttributesList)	\
    ( (This)->lpVtbl -> AttributesSave(This,_pbsAttributesList) ) 

#define IMNode_AttributesClone(This,_ppClone)	\
    ( (This)->lpVtbl -> AttributesClone(This,_ppClone) ) 

#define IMNode_AttributesSet(This,_pAttributesList,_eUpdateType)	\
    ( (This)->lpVtbl -> AttributesSet(This,_pAttributesList,_eUpdateType) ) 

#define IMNode_AttributesInfoGetCount(This,_pnCount)	\
    ( (This)->lpVtbl -> AttributesInfoGetCount(This,_pnCount) ) 

#define IMNode_AttributesInfoGetByIndex(This,_nIndex,_pbsName)	\
    ( (This)->lpVtbl -> AttributesInfoGetByIndex(This,_nIndex,_pbsName) ) 

#define IMNode_AttributesInfoGet(This,_bsName,_eType,_pbsInfo)	\
    ( (This)->lpVtbl -> AttributesInfoGet(This,_bsName,_eType,_pbsInfo) ) 

#define IMNode_AttributesValuesInfoGet(This,_bsName,_bsValue,_bsType,_pbsInfo)	\
    ( (This)->lpVtbl -> AttributesValuesInfoGet(This,_bsName,_bsValue,_bsType,_pbsInfo) ) 


#define IMNode_NodeNameGet(This,_pbsName)	\
    ( (This)->lpVtbl -> NodeNameGet(This,_pbsName) ) 

#define IMNode_NodeNameSet(This,_bsName)	\
    ( (This)->lpVtbl -> NodeNameSet(This,_bsName) ) 

#define IMNode_NodeValueGet(This,_pbsValue)	\
    ( (This)->lpVtbl -> NodeValueGet(This,_pbsValue) ) 

#define IMNode_NodeValueSet(This,_bsValue)	\
    ( (This)->lpVtbl -> NodeValueSet(This,_bsValue) ) 

#define IMNode_NodePathGet(This,_bsPath,_pRoot)	\
    ( (This)->lpVtbl -> NodePathGet(This,_bsPath,_pRoot) ) 

#define IMNode_NodeParentGet(This,_ppParent)	\
    ( (This)->lpVtbl -> NodeParentGet(This,_ppParent) ) 

#define IMNode_NodeDetach(This)	\
    ( (This)->lpVtbl -> NodeDetach(This) ) 

#define IMNode_NodeGetCount(This,_pnCount)	\
    ( (This)->lpVtbl -> NodeGetCount(This,_pnCount) ) 

#define IMNode_NodeGetByIndex(This,_nIndex,_pbsName,_ppNode)	\
    ( (This)->lpVtbl -> NodeGetByIndex(This,_nIndex,_pbsName,_ppNode) ) 

#define IMNode_NodeAdd(This,_bsPath,_bsValue,_ppNode)	\
    ( (This)->lpVtbl -> NodeAdd(This,_bsPath,_bsValue,_ppNode) ) 

#define IMNode_NodeGet(This,_bsPath,_bCreateNew,_ppNode)	\
    ( (This)->lpVtbl -> NodeGet(This,_bsPath,_bCreateNew,_ppNode) ) 

#define IMNode_NodeRemove(This,_bsPath)	\
    ( (This)->lpVtbl -> NodeRemove(This,_bsPath) ) 

#define IMNode_NodeRemoveAll(This,_bRemoveAttributes)	\
    ( (This)->lpVtbl -> NodeRemoveAll(This,_bRemoveAttributes) ) 

#define IMNode_NodeParse(This,_pbsXMLString,_bUpdateName)	\
    ( (This)->lpVtbl -> NodeParse(This,_pbsXMLString,_bUpdateName) ) 

#define IMNode_NodeSave(This,_pbsXMLString)	\
    ( (This)->lpVtbl -> NodeSave(This,_pbsXMLString) ) 

#define IMNode_NodeClone(This,_ppClone)	\
    ( (This)->lpVtbl -> NodeClone(This,_ppClone) ) 

#define IMNode_NodeSet(This,_pNodeSet,_eUpdateType)	\
    ( (This)->lpVtbl -> NodeSet(This,_pNodeSet,_eUpdateType) ) 

#define IMNode_NodeInfoGet(This,_bsInfoType,_pbsDecription)	\
    ( (This)->lpVtbl -> NodeInfoGet(This,_bsInfoType,_pbsDecription) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMNode_INTERFACE_DEFINED__ */


#ifndef __IMCallback_INTERFACE_DEFINED__
#define __IMCallback_INTERFACE_DEFINED__

/* interface IMCallback */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F366005-473F-4ad5-A5C2-428FE0C8E03E")
    IMCallback : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnEvent( 
            /* [in] */ LONGLONG llCallbackUserData,
            /* [in] */ BSTR bsName,
            /* [in] */ BSTR bsEventName,
            /* [in] */ BSTR bsEventParam,
            /* [in] */ IUnknown *pEventObject) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnFrame( 
            /* [in] */ LONGLONG llCallbackUserData,
            /* [in] */ BSTR bsName,
            /* [in] */ IUnknown *pMFrame) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMCallback * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMCallback * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnEvent )( 
            IMCallback * This,
            /* [in] */ LONGLONG llCallbackUserData,
            /* [in] */ BSTR bsName,
            /* [in] */ BSTR bsEventName,
            /* [in] */ BSTR bsEventParam,
            /* [in] */ IUnknown *pEventObject);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnFrame )( 
            IMCallback * This,
            /* [in] */ LONGLONG llCallbackUserData,
            /* [in] */ BSTR bsName,
            /* [in] */ IUnknown *pMFrame);
        
        END_INTERFACE
    } IMCallbackVtbl;

    interface IMCallback
    {
        CONST_VTBL struct IMCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMCallback_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMCallback_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMCallback_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMCallback_OnEvent(This,llCallbackUserData,bsName,bsEventName,bsEventParam,pEventObject)	\
    ( (This)->lpVtbl -> OnEvent(This,llCallbackUserData,bsName,bsEventName,bsEventParam,pEventObject) ) 

#define IMCallback_OnFrame(This,llCallbackUserData,bsName,pMFrame)	\
    ( (This)->lpVtbl -> OnFrame(This,llCallbackUserData,bsName,pMFrame) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMCallback_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_MPlatform_0000_0003 */
/* [local] */ 

typedef HRESULT (WINAPI *PFOnEvent)(LONGLONG llCallbackUserData, BSTR bsChannelID, BSTR bsEventName, BSTR bsEventParam, IUnknown* pEventObject );
typedef HRESULT (WINAPI *PFOnFrame)(LONGLONG llCallbackUserData, BSTR bsChannelID, IUnknown* pMFrame );


extern RPC_IF_HANDLE __MIDL_itf_MPlatform_0000_0003_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_MPlatform_0000_0003_v0_0_s_ifspec;

#ifndef __IMPreview_INTERFACE_DEFINED__
#define __IMPreview_INTERFACE_DEFINED__

/* interface IMPreview */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMPreview;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F366160-473F-4ad5-A5C2-428FE0C8E03E")
    IMPreview : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PreviewEnable( 
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ BOOL _bEnableAudio,
            /* [in] */ BOOL _bEnableVideo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PreviewWindowSet( 
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ LONGLONG _hWndParent) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PreviewFullScreen( 
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ BOOL _bFullScreen,
            /* [in] */ int _nDisplay) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PreviewIsFullScreen( 
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ BOOL *_pbFullScreen,
            /* [in] */ int *_pnDisplay) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PreviewAudioVolumeSet( 
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ int _nChannel,
            /* [in] */ double _dblAttenuationdB) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PreviewAudioVolumeGet( 
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ int _nChannel,
            /* [out] */ double *_pdblAttenuationdB) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PreviewSetCursor( 
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ eMCursorType _eCursor) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PreviewIsEnabled( 
            /* [in] */ BSTR _bsChannelID,
            /* [out] */ BOOL *_pbEnabledAudio,
            /* [out] */ BOOL *_pbEnabledVideo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PreviewWindowSetVB6( 
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ LONG _hWndParent) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMPreviewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMPreview * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMPreview * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMPreview * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PreviewEnable )( 
            IMPreview * This,
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ BOOL _bEnableAudio,
            /* [in] */ BOOL _bEnableVideo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PreviewWindowSet )( 
            IMPreview * This,
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ LONGLONG _hWndParent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PreviewFullScreen )( 
            IMPreview * This,
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ BOOL _bFullScreen,
            /* [in] */ int _nDisplay);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PreviewIsFullScreen )( 
            IMPreview * This,
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ BOOL *_pbFullScreen,
            /* [in] */ int *_pnDisplay);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PreviewAudioVolumeSet )( 
            IMPreview * This,
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ int _nChannel,
            /* [in] */ double _dblAttenuationdB);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PreviewAudioVolumeGet )( 
            IMPreview * This,
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ int _nChannel,
            /* [out] */ double *_pdblAttenuationdB);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PreviewSetCursor )( 
            IMPreview * This,
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ eMCursorType _eCursor);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PreviewIsEnabled )( 
            IMPreview * This,
            /* [in] */ BSTR _bsChannelID,
            /* [out] */ BOOL *_pbEnabledAudio,
            /* [out] */ BOOL *_pbEnabledVideo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PreviewWindowSetVB6 )( 
            IMPreview * This,
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ LONG _hWndParent);
        
        END_INTERFACE
    } IMPreviewVtbl;

    interface IMPreview
    {
        CONST_VTBL struct IMPreviewVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMPreview_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMPreview_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMPreview_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMPreview_PreviewEnable(This,_bsChannelID,_bEnableAudio,_bEnableVideo)	\
    ( (This)->lpVtbl -> PreviewEnable(This,_bsChannelID,_bEnableAudio,_bEnableVideo) ) 

#define IMPreview_PreviewWindowSet(This,_bsChannelID,_hWndParent)	\
    ( (This)->lpVtbl -> PreviewWindowSet(This,_bsChannelID,_hWndParent) ) 

#define IMPreview_PreviewFullScreen(This,_bsChannelID,_bFullScreen,_nDisplay)	\
    ( (This)->lpVtbl -> PreviewFullScreen(This,_bsChannelID,_bFullScreen,_nDisplay) ) 

#define IMPreview_PreviewIsFullScreen(This,_bsChannelID,_pbFullScreen,_pnDisplay)	\
    ( (This)->lpVtbl -> PreviewIsFullScreen(This,_bsChannelID,_pbFullScreen,_pnDisplay) ) 

#define IMPreview_PreviewAudioVolumeSet(This,_bsChannelID,_nChannel,_dblAttenuationdB)	\
    ( (This)->lpVtbl -> PreviewAudioVolumeSet(This,_bsChannelID,_nChannel,_dblAttenuationdB) ) 

#define IMPreview_PreviewAudioVolumeGet(This,_bsChannelID,_nChannel,_pdblAttenuationdB)	\
    ( (This)->lpVtbl -> PreviewAudioVolumeGet(This,_bsChannelID,_nChannel,_pdblAttenuationdB) ) 

#define IMPreview_PreviewSetCursor(This,_bsChannelID,_eCursor)	\
    ( (This)->lpVtbl -> PreviewSetCursor(This,_bsChannelID,_eCursor) ) 

#define IMPreview_PreviewIsEnabled(This,_bsChannelID,_pbEnabledAudio,_pbEnabledVideo)	\
    ( (This)->lpVtbl -> PreviewIsEnabled(This,_bsChannelID,_pbEnabledAudio,_pbEnabledVideo) ) 

#define IMPreview_PreviewWindowSetVB6(This,_bsChannelID,_hWndParent)	\
    ( (This)->lpVtbl -> PreviewWindowSetVB6(This,_bsChannelID,_hWndParent) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMPreview_INTERFACE_DEFINED__ */


#ifndef __IMFrame_INTERFACE_DEFINED__
#define __IMFrame_INTERFACE_DEFINED__

/* interface IMFrame */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMFrame;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F366000-473F-4ad5-A5C2-428FE0C8E03E")
    IMFrame : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FrameAVPropsGet( 
            /* [out] */ M_AV_PROPS *_pProps) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FrameAVPropsSet( 
            /* [in] */ M_AV_PROPS *_pProps) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FrameTimeGet( 
            /* [out] */ M_TIME *_pTime) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FrameTimeSet( 
            /* [in] */ M_TIME *_pTime) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FrameAudioGetBytes( 
            /* [out] */ LONG *_pcbSize,
            /* [out] */ LONGLONG *_ppbAudio) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FrameVideoGetBytes( 
            /* [out] */ LONG *_pcbSize,
            /* [out] */ LONGLONG *_ppbVideo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FrameVideoGetHbitmap( 
            /* [out] */ LONGLONG *_pcpHBitmap) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FrameVideoSaveToFile( 
            /* [in] */ BSTR _bsFileName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FrameAudioSaveToFile( 
            /* [in] */ BSTR _bsFileName,
            /* [in] */ BOOL _bAppend) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FrameDataGetByIndex( 
            /* [in] */ int _nIndex,
            /* [out] */ LONG *_pnDataFCC,
            /* [out] */ LONG *_pcbANCData,
            /* [out] */ LONGLONG *_ppbANCData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FrameDataGet( 
            /* [in] */ LONG _nDataFCC,
            /* [out] */ LONG *_pcbANCData,
            /* [out] */ LONGLONG *_ppbANCData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FrameDataSet( 
            /* [in] */ LONG _nDataFCC,
            /* [in] */ LONG _cbANCData,
            /* [in] */ LONGLONG _pbANCData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FrameClone( 
            /* [out] */ IMFrame **_ppCloneFrame,
            /* [in] */ eMFrameClone _eCloneType,
            /* [in] */ eMFCC _fccPixelFormat) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FrameCut( 
            /* [in] */ int _nField,
            /* [in] */ RECT *_pRect,
            /* [out] */ IMFrame **_ppFrameRes) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FrameConvert( 
            /* [in] */ M_VID_PROPS *_pVidPropsDest,
            /* [out] */ IMFrame **_ppFrameRes,
            /* [in] */ BSTR _bsPropsList) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FrameOverlay( 
            /* [in] */ IMFrame *_pFrameOver,
            /* [in] */ int _nPosX,
            /* [in] */ int _nPosY,
            /* [in] */ double _dblAlpha,
            /* [in] */ BSTR _bsPropsList) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FrameRelease( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMFrameVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMFrame * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMFrame * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMFrame * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameAVPropsGet )( 
            IMFrame * This,
            /* [out] */ M_AV_PROPS *_pProps);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameAVPropsSet )( 
            IMFrame * This,
            /* [in] */ M_AV_PROPS *_pProps);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameTimeGet )( 
            IMFrame * This,
            /* [out] */ M_TIME *_pTime);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameTimeSet )( 
            IMFrame * This,
            /* [in] */ M_TIME *_pTime);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameAudioGetBytes )( 
            IMFrame * This,
            /* [out] */ LONG *_pcbSize,
            /* [out] */ LONGLONG *_ppbAudio);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameVideoGetBytes )( 
            IMFrame * This,
            /* [out] */ LONG *_pcbSize,
            /* [out] */ LONGLONG *_ppbVideo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameVideoGetHbitmap )( 
            IMFrame * This,
            /* [out] */ LONGLONG *_pcpHBitmap);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameVideoSaveToFile )( 
            IMFrame * This,
            /* [in] */ BSTR _bsFileName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameAudioSaveToFile )( 
            IMFrame * This,
            /* [in] */ BSTR _bsFileName,
            /* [in] */ BOOL _bAppend);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameDataGetByIndex )( 
            IMFrame * This,
            /* [in] */ int _nIndex,
            /* [out] */ LONG *_pnDataFCC,
            /* [out] */ LONG *_pcbANCData,
            /* [out] */ LONGLONG *_ppbANCData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameDataGet )( 
            IMFrame * This,
            /* [in] */ LONG _nDataFCC,
            /* [out] */ LONG *_pcbANCData,
            /* [out] */ LONGLONG *_ppbANCData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameDataSet )( 
            IMFrame * This,
            /* [in] */ LONG _nDataFCC,
            /* [in] */ LONG _cbANCData,
            /* [in] */ LONGLONG _pbANCData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameClone )( 
            IMFrame * This,
            /* [out] */ IMFrame **_ppCloneFrame,
            /* [in] */ eMFrameClone _eCloneType,
            /* [in] */ eMFCC _fccPixelFormat);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameCut )( 
            IMFrame * This,
            /* [in] */ int _nField,
            /* [in] */ RECT *_pRect,
            /* [out] */ IMFrame **_ppFrameRes);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameConvert )( 
            IMFrame * This,
            /* [in] */ M_VID_PROPS *_pVidPropsDest,
            /* [out] */ IMFrame **_ppFrameRes,
            /* [in] */ BSTR _bsPropsList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameOverlay )( 
            IMFrame * This,
            /* [in] */ IMFrame *_pFrameOver,
            /* [in] */ int _nPosX,
            /* [in] */ int _nPosY,
            /* [in] */ double _dblAlpha,
            /* [in] */ BSTR _bsPropsList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameRelease )( 
            IMFrame * This);
        
        END_INTERFACE
    } IMFrameVtbl;

    interface IMFrame
    {
        CONST_VTBL struct IMFrameVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMFrame_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMFrame_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMFrame_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMFrame_FrameAVPropsGet(This,_pProps)	\
    ( (This)->lpVtbl -> FrameAVPropsGet(This,_pProps) ) 

#define IMFrame_FrameAVPropsSet(This,_pProps)	\
    ( (This)->lpVtbl -> FrameAVPropsSet(This,_pProps) ) 

#define IMFrame_FrameTimeGet(This,_pTime)	\
    ( (This)->lpVtbl -> FrameTimeGet(This,_pTime) ) 

#define IMFrame_FrameTimeSet(This,_pTime)	\
    ( (This)->lpVtbl -> FrameTimeSet(This,_pTime) ) 

#define IMFrame_FrameAudioGetBytes(This,_pcbSize,_ppbAudio)	\
    ( (This)->lpVtbl -> FrameAudioGetBytes(This,_pcbSize,_ppbAudio) ) 

#define IMFrame_FrameVideoGetBytes(This,_pcbSize,_ppbVideo)	\
    ( (This)->lpVtbl -> FrameVideoGetBytes(This,_pcbSize,_ppbVideo) ) 

#define IMFrame_FrameVideoGetHbitmap(This,_pcpHBitmap)	\
    ( (This)->lpVtbl -> FrameVideoGetHbitmap(This,_pcpHBitmap) ) 

#define IMFrame_FrameVideoSaveToFile(This,_bsFileName)	\
    ( (This)->lpVtbl -> FrameVideoSaveToFile(This,_bsFileName) ) 

#define IMFrame_FrameAudioSaveToFile(This,_bsFileName,_bAppend)	\
    ( (This)->lpVtbl -> FrameAudioSaveToFile(This,_bsFileName,_bAppend) ) 

#define IMFrame_FrameDataGetByIndex(This,_nIndex,_pnDataFCC,_pcbANCData,_ppbANCData)	\
    ( (This)->lpVtbl -> FrameDataGetByIndex(This,_nIndex,_pnDataFCC,_pcbANCData,_ppbANCData) ) 

#define IMFrame_FrameDataGet(This,_nDataFCC,_pcbANCData,_ppbANCData)	\
    ( (This)->lpVtbl -> FrameDataGet(This,_nDataFCC,_pcbANCData,_ppbANCData) ) 

#define IMFrame_FrameDataSet(This,_nDataFCC,_cbANCData,_pbANCData)	\
    ( (This)->lpVtbl -> FrameDataSet(This,_nDataFCC,_cbANCData,_pbANCData) ) 

#define IMFrame_FrameClone(This,_ppCloneFrame,_eCloneType,_fccPixelFormat)	\
    ( (This)->lpVtbl -> FrameClone(This,_ppCloneFrame,_eCloneType,_fccPixelFormat) ) 

#define IMFrame_FrameCut(This,_nField,_pRect,_ppFrameRes)	\
    ( (This)->lpVtbl -> FrameCut(This,_nField,_pRect,_ppFrameRes) ) 

#define IMFrame_FrameConvert(This,_pVidPropsDest,_ppFrameRes,_bsPropsList)	\
    ( (This)->lpVtbl -> FrameConvert(This,_pVidPropsDest,_ppFrameRes,_bsPropsList) ) 

#define IMFrame_FrameOverlay(This,_pFrameOver,_nPosX,_nPosY,_dblAlpha,_bsPropsList)	\
    ( (This)->lpVtbl -> FrameOverlay(This,_pFrameOver,_nPosX,_nPosY,_dblAlpha,_bsPropsList) ) 

#define IMFrame_FrameRelease(This)	\
    ( (This)->lpVtbl -> FrameRelease(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMFrame_INTERFACE_DEFINED__ */


#ifndef __IMFrames_INTERFACE_DEFINED__
#define __IMFrames_INTERFACE_DEFINED__

/* interface IMFrames */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMFrames;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F365000-473F-4ad5-A5C2-428FE0C8E03E")
    IMFrames : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FramesMakeLocal( 
            /* [in] */ IMFrame *_ppFrame,
            /* [out] */ IMFrame **_ppFrameLocal,
            /* [in] */ BOOL _bMakeRef) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FramesCreate( 
            /* [in] */ int _cbVideoSize,
            /* [in] */ BSTR _bsProps,
            /* [out] */ IMFrame **_ppFrame) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FramesCreateFromMem( 
            /* [in] */ M_VID_PROPS *_pVidProps,
            /* [in] */ LONGLONG _pbVideo,
            /* [out] */ IMFrame **_ppFrame,
            /* [in] */ BSTR _bsPropsList) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FramesCreateFromFile( 
            /* [in] */ BSTR _bsFileName,
            /* [out] */ IMFrame **_ppFrame,
            /* [in] */ BSTR _bsPropsList) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FramesCreateFromHBITMAP( 
            /* [in] */ LONGLONG _hBitmap,
            /* [out] */ IMFrame **_ppFrame,
            /* [in] */ BSTR _bsPropsList) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FramesCreateFromSurface( 
            /* [in] */ IUnknown *_pSurface,
            /* [out] */ IMFrame **_ppFrame,
            /* [in] */ BSTR _bsPropsList) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMFramesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMFrames * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMFrames * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMFrames * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FramesMakeLocal )( 
            IMFrames * This,
            /* [in] */ IMFrame *_ppFrame,
            /* [out] */ IMFrame **_ppFrameLocal,
            /* [in] */ BOOL _bMakeRef);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FramesCreate )( 
            IMFrames * This,
            /* [in] */ int _cbVideoSize,
            /* [in] */ BSTR _bsProps,
            /* [out] */ IMFrame **_ppFrame);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FramesCreateFromMem )( 
            IMFrames * This,
            /* [in] */ M_VID_PROPS *_pVidProps,
            /* [in] */ LONGLONG _pbVideo,
            /* [out] */ IMFrame **_ppFrame,
            /* [in] */ BSTR _bsPropsList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FramesCreateFromFile )( 
            IMFrames * This,
            /* [in] */ BSTR _bsFileName,
            /* [out] */ IMFrame **_ppFrame,
            /* [in] */ BSTR _bsPropsList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FramesCreateFromHBITMAP )( 
            IMFrames * This,
            /* [in] */ LONGLONG _hBitmap,
            /* [out] */ IMFrame **_ppFrame,
            /* [in] */ BSTR _bsPropsList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FramesCreateFromSurface )( 
            IMFrames * This,
            /* [in] */ IUnknown *_pSurface,
            /* [out] */ IMFrame **_ppFrame,
            /* [in] */ BSTR _bsPropsList);
        
        END_INTERFACE
    } IMFramesVtbl;

    interface IMFrames
    {
        CONST_VTBL struct IMFramesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMFrames_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMFrames_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMFrames_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMFrames_FramesMakeLocal(This,_ppFrame,_ppFrameLocal,_bMakeRef)	\
    ( (This)->lpVtbl -> FramesMakeLocal(This,_ppFrame,_ppFrameLocal,_bMakeRef) ) 

#define IMFrames_FramesCreate(This,_cbVideoSize,_bsProps,_ppFrame)	\
    ( (This)->lpVtbl -> FramesCreate(This,_cbVideoSize,_bsProps,_ppFrame) ) 

#define IMFrames_FramesCreateFromMem(This,_pVidProps,_pbVideo,_ppFrame,_bsPropsList)	\
    ( (This)->lpVtbl -> FramesCreateFromMem(This,_pVidProps,_pbVideo,_ppFrame,_bsPropsList) ) 

#define IMFrames_FramesCreateFromFile(This,_bsFileName,_ppFrame,_bsPropsList)	\
    ( (This)->lpVtbl -> FramesCreateFromFile(This,_bsFileName,_ppFrame,_bsPropsList) ) 

#define IMFrames_FramesCreateFromHBITMAP(This,_hBitmap,_ppFrame,_bsPropsList)	\
    ( (This)->lpVtbl -> FramesCreateFromHBITMAP(This,_hBitmap,_ppFrame,_bsPropsList) ) 

#define IMFrames_FramesCreateFromSurface(This,_pSurface,_ppFrame,_bsPropsList)	\
    ( (This)->lpVtbl -> FramesCreateFromSurface(This,_pSurface,_ppFrame,_bsPropsList) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMFrames_INTERFACE_DEFINED__ */


#ifndef __IMProps_INTERFACE_DEFINED__
#define __IMProps_INTERFACE_DEFINED__

/* interface IMProps */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMProps;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F366020-473F-4ad5-A5C2-428FE0C8E03E")
    IMProps : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PropsSet( 
            /* [in] */ BSTR _bsPropName,
            /* [in] */ BSTR _bsPropValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PropsGet( 
            /* [in] */ BSTR _bsPropName,
            /* [out] */ BSTR *_pbsPropValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PropsGetCount( 
            /* [in] */ BSTR _bsNodeName,
            /* [out] */ int *_pnCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PropsGetByIndex( 
            /* [in] */ BSTR _bsNodeName,
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsPropName,
            /* [out] */ BSTR *_pbsPropValue,
            /* [out] */ BOOL *_pbNode) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PropsRemove( 
            /* [in] */ BSTR _bsPropName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PropsInfoGet( 
            /* [in] */ BSTR _bsPropName,
            /* [in] */ eMInfoType _eType,
            /* [out] */ BSTR *_pbsInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PropsOptionGetCount( 
            /* [in] */ BSTR _bsPropName,
            /* [out] */ int *_pnOptionCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PropsOptionGetByIndex( 
            /* [in] */ BSTR _bsPropName,
            /* [in] */ int _nOptionIdx,
            /* [out] */ BSTR *_pbsOptionValue,
            /* [out] */ BSTR *_pbsHelp) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PropsOptionSetByIndex( 
            /* [in] */ BSTR _bsPropName,
            /* [in] */ int _nOptionInx) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PropsOptionGet( 
            /* [in] */ BSTR _bsPropName,
            /* [out] */ int *_pnOptionIdx,
            /* [out] */ BSTR *_pbsOptionValue,
            /* [out] */ BSTR *_pbsHelp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMPropsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMProps * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMProps * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMProps * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PropsSet )( 
            IMProps * This,
            /* [in] */ BSTR _bsPropName,
            /* [in] */ BSTR _bsPropValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PropsGet )( 
            IMProps * This,
            /* [in] */ BSTR _bsPropName,
            /* [out] */ BSTR *_pbsPropValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PropsGetCount )( 
            IMProps * This,
            /* [in] */ BSTR _bsNodeName,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PropsGetByIndex )( 
            IMProps * This,
            /* [in] */ BSTR _bsNodeName,
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsPropName,
            /* [out] */ BSTR *_pbsPropValue,
            /* [out] */ BOOL *_pbNode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PropsRemove )( 
            IMProps * This,
            /* [in] */ BSTR _bsPropName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PropsInfoGet )( 
            IMProps * This,
            /* [in] */ BSTR _bsPropName,
            /* [in] */ eMInfoType _eType,
            /* [out] */ BSTR *_pbsInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PropsOptionGetCount )( 
            IMProps * This,
            /* [in] */ BSTR _bsPropName,
            /* [out] */ int *_pnOptionCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PropsOptionGetByIndex )( 
            IMProps * This,
            /* [in] */ BSTR _bsPropName,
            /* [in] */ int _nOptionIdx,
            /* [out] */ BSTR *_pbsOptionValue,
            /* [out] */ BSTR *_pbsHelp);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PropsOptionSetByIndex )( 
            IMProps * This,
            /* [in] */ BSTR _bsPropName,
            /* [in] */ int _nOptionInx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PropsOptionGet )( 
            IMProps * This,
            /* [in] */ BSTR _bsPropName,
            /* [out] */ int *_pnOptionIdx,
            /* [out] */ BSTR *_pbsOptionValue,
            /* [out] */ BSTR *_pbsHelp);
        
        END_INTERFACE
    } IMPropsVtbl;

    interface IMProps
    {
        CONST_VTBL struct IMPropsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMProps_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMProps_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMProps_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMProps_PropsSet(This,_bsPropName,_bsPropValue)	\
    ( (This)->lpVtbl -> PropsSet(This,_bsPropName,_bsPropValue) ) 

#define IMProps_PropsGet(This,_bsPropName,_pbsPropValue)	\
    ( (This)->lpVtbl -> PropsGet(This,_bsPropName,_pbsPropValue) ) 

#define IMProps_PropsGetCount(This,_bsNodeName,_pnCount)	\
    ( (This)->lpVtbl -> PropsGetCount(This,_bsNodeName,_pnCount) ) 

#define IMProps_PropsGetByIndex(This,_bsNodeName,_nIndex,_pbsPropName,_pbsPropValue,_pbNode)	\
    ( (This)->lpVtbl -> PropsGetByIndex(This,_bsNodeName,_nIndex,_pbsPropName,_pbsPropValue,_pbNode) ) 

#define IMProps_PropsRemove(This,_bsPropName)	\
    ( (This)->lpVtbl -> PropsRemove(This,_bsPropName) ) 

#define IMProps_PropsInfoGet(This,_bsPropName,_eType,_pbsInfo)	\
    ( (This)->lpVtbl -> PropsInfoGet(This,_bsPropName,_eType,_pbsInfo) ) 

#define IMProps_PropsOptionGetCount(This,_bsPropName,_pnOptionCount)	\
    ( (This)->lpVtbl -> PropsOptionGetCount(This,_bsPropName,_pnOptionCount) ) 

#define IMProps_PropsOptionGetByIndex(This,_bsPropName,_nOptionIdx,_pbsOptionValue,_pbsHelp)	\
    ( (This)->lpVtbl -> PropsOptionGetByIndex(This,_bsPropName,_nOptionIdx,_pbsOptionValue,_pbsHelp) ) 

#define IMProps_PropsOptionSetByIndex(This,_bsPropName,_nOptionInx)	\
    ( (This)->lpVtbl -> PropsOptionSetByIndex(This,_bsPropName,_nOptionInx) ) 

#define IMProps_PropsOptionGet(This,_bsPropName,_pnOptionIdx,_pbsOptionValue,_pbsHelp)	\
    ( (This)->lpVtbl -> PropsOptionGet(This,_bsPropName,_pnOptionIdx,_pbsOptionValue,_pbsHelp) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMProps_INTERFACE_DEFINED__ */


#ifndef __IMPersist_INTERFACE_DEFINED__
#define __IMPersist_INTERFACE_DEFINED__

/* interface IMPersist */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMPersist;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F366030-473F-4ad5-A5C2-428FE0C8E03E")
    IMPersist : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PersistSaveToFile( 
            /* [in] */ BSTR _bsObject,
            /* [in] */ BSTR _bsFileName,
            /* [in] */ BSTR _bsSaveParam) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PersistSaveToString( 
            /* [in] */ BSTR _bsObject,
            /* [out] */ BSTR *_pbsXMLDesc,
            /* [in] */ BSTR _bsSaveParam) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PersistLoad( 
            /* [in] */ BSTR _bsObject,
            /* [in] */ BSTR _bsXMLDescOrFile,
            /* [in] */ BSTR _bsLoadParam) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMPersistVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMPersist * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMPersist * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMPersist * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PersistSaveToFile )( 
            IMPersist * This,
            /* [in] */ BSTR _bsObject,
            /* [in] */ BSTR _bsFileName,
            /* [in] */ BSTR _bsSaveParam);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PersistSaveToString )( 
            IMPersist * This,
            /* [in] */ BSTR _bsObject,
            /* [out] */ BSTR *_pbsXMLDesc,
            /* [in] */ BSTR _bsSaveParam);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PersistLoad )( 
            IMPersist * This,
            /* [in] */ BSTR _bsObject,
            /* [in] */ BSTR _bsXMLDescOrFile,
            /* [in] */ BSTR _bsLoadParam);
        
        END_INTERFACE
    } IMPersistVtbl;

    interface IMPersist
    {
        CONST_VTBL struct IMPersistVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMPersist_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMPersist_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMPersist_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMPersist_PersistSaveToFile(This,_bsObject,_bsFileName,_bsSaveParam)	\
    ( (This)->lpVtbl -> PersistSaveToFile(This,_bsObject,_bsFileName,_bsSaveParam) ) 

#define IMPersist_PersistSaveToString(This,_bsObject,_pbsXMLDesc,_bsSaveParam)	\
    ( (This)->lpVtbl -> PersistSaveToString(This,_bsObject,_pbsXMLDesc,_bsSaveParam) ) 

#define IMPersist_PersistLoad(This,_bsObject,_bsXMLDescOrFile,_bsLoadParam)	\
    ( (This)->lpVtbl -> PersistLoad(This,_bsObject,_bsXMLDescOrFile,_bsLoadParam) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMPersist_INTERFACE_DEFINED__ */


#ifndef __IMObject_INTERFACE_DEFINED__
#define __IMObject_INTERFACE_DEFINED__

/* interface IMObject */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F366100-473F-4ad5-A5C2-428FE0C8E03E")
    IMObject : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectNameSet( 
            /* [in] */ BSTR _bsName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectNameGet( 
            /* [out] */ BSTR *_pbsName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectStart( 
            /* [in] */ IUnknown *_pSource) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectClose( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectStateGet( 
            /* [out] */ eMState *_peState) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectCallbackSet( 
            /* [in] */ IMCallback *_pCallback,
            /* [in] */ LONGLONG _llCallbackUserData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectCallbackSetFunc( 
            /* [in] */ LONGLONG _lpPFOnEvent,
            /* [in] */ LONGLONG _lpPFOnFrame,
            /* [in] */ LONGLONG _llCallbackUserData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectCommandExecute( 
            /* [in] */ BSTR _bsCommand,
            /* [in] */ BSTR _bsParam,
            /* [in] */ IUnknown *_pParamUnk,
            /* [out] */ BSTR *_pbsReturn) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectVirtualSourceCreate( 
            /* [in] */ BOOL _bCreate,
            /* [in] */ BSTR _bsName,
            /* [in] */ BSTR _bsParam) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectFrameGet( 
            /* [out] */ IMFrame **_ppFrame,
            /* [in] */ BSTR _bsParam) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectGetInternal( 
            /* [in] */ BSTR _bsType,
            /* [out] */ IUnknown **_ppObject) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMObject * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMObject * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectNameSet )( 
            IMObject * This,
            /* [in] */ BSTR _bsName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectNameGet )( 
            IMObject * This,
            /* [out] */ BSTR *_pbsName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectStart )( 
            IMObject * This,
            /* [in] */ IUnknown *_pSource);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectClose )( 
            IMObject * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectStateGet )( 
            IMObject * This,
            /* [out] */ eMState *_peState);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectCallbackSet )( 
            IMObject * This,
            /* [in] */ IMCallback *_pCallback,
            /* [in] */ LONGLONG _llCallbackUserData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectCallbackSetFunc )( 
            IMObject * This,
            /* [in] */ LONGLONG _lpPFOnEvent,
            /* [in] */ LONGLONG _lpPFOnFrame,
            /* [in] */ LONGLONG _llCallbackUserData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectCommandExecute )( 
            IMObject * This,
            /* [in] */ BSTR _bsCommand,
            /* [in] */ BSTR _bsParam,
            /* [in] */ IUnknown *_pParamUnk,
            /* [out] */ BSTR *_pbsReturn);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectVirtualSourceCreate )( 
            IMObject * This,
            /* [in] */ BOOL _bCreate,
            /* [in] */ BSTR _bsName,
            /* [in] */ BSTR _bsParam);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectFrameGet )( 
            IMObject * This,
            /* [out] */ IMFrame **_ppFrame,
            /* [in] */ BSTR _bsParam);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectGetInternal )( 
            IMObject * This,
            /* [in] */ BSTR _bsType,
            /* [out] */ IUnknown **_ppObject);
        
        END_INTERFACE
    } IMObjectVtbl;

    interface IMObject
    {
        CONST_VTBL struct IMObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMObject_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMObject_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMObject_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMObject_ObjectNameSet(This,_bsName)	\
    ( (This)->lpVtbl -> ObjectNameSet(This,_bsName) ) 

#define IMObject_ObjectNameGet(This,_pbsName)	\
    ( (This)->lpVtbl -> ObjectNameGet(This,_pbsName) ) 

#define IMObject_ObjectStart(This,_pSource)	\
    ( (This)->lpVtbl -> ObjectStart(This,_pSource) ) 

#define IMObject_ObjectClose(This)	\
    ( (This)->lpVtbl -> ObjectClose(This) ) 

#define IMObject_ObjectStateGet(This,_peState)	\
    ( (This)->lpVtbl -> ObjectStateGet(This,_peState) ) 

#define IMObject_ObjectCallbackSet(This,_pCallback,_llCallbackUserData)	\
    ( (This)->lpVtbl -> ObjectCallbackSet(This,_pCallback,_llCallbackUserData) ) 

#define IMObject_ObjectCallbackSetFunc(This,_lpPFOnEvent,_lpPFOnFrame,_llCallbackUserData)	\
    ( (This)->lpVtbl -> ObjectCallbackSetFunc(This,_lpPFOnEvent,_lpPFOnFrame,_llCallbackUserData) ) 

#define IMObject_ObjectCommandExecute(This,_bsCommand,_bsParam,_pParamUnk,_pbsReturn)	\
    ( (This)->lpVtbl -> ObjectCommandExecute(This,_bsCommand,_bsParam,_pParamUnk,_pbsReturn) ) 

#define IMObject_ObjectVirtualSourceCreate(This,_bCreate,_bsName,_bsParam)	\
    ( (This)->lpVtbl -> ObjectVirtualSourceCreate(This,_bCreate,_bsName,_bsParam) ) 

#define IMObject_ObjectFrameGet(This,_ppFrame,_bsParam)	\
    ( (This)->lpVtbl -> ObjectFrameGet(This,_ppFrame,_bsParam) ) 

#define IMObject_ObjectGetInternal(This,_bsType,_ppObject)	\
    ( (This)->lpVtbl -> ObjectGetInternal(This,_bsType,_ppObject) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMObject_INTERFACE_DEFINED__ */


#ifndef __IMFormat_INTERFACE_DEFINED__
#define __IMFormat_INTERFACE_DEFINED__

/* interface IMFormat */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMFormat;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F366105-473F-4ad5-A5C2-428FE0C8E03E")
    IMFormat : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FormatVideoGetCount( 
            /* [in] */ eMFormatType _eFormatType,
            /* [out] */ int *_pnCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FormatVideoGetByIndex( 
            /* [in] */ eMFormatType _eFormatType,
            /* [in] */ int _nIndex,
            /* [out] */ M_VID_PROPS *_pVidProps,
            /* [out] */ BSTR *_pbsName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FormatVideoSet( 
            /* [in] */ eMFormatType _eFormatType,
            /* [in] */ M_VID_PROPS *_pVidProps) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FormatVideoGet( 
            /* [in] */ eMFormatType _eFormatType,
            /* [out] */ M_VID_PROPS *_pVidProps,
            /* [out] */ int *_pnIndex,
            /* [out] */ BSTR *_pbsName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FormatAudioGetCount( 
            /* [in] */ eMFormatType _eFormatType,
            /* [out] */ int *_pnCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FormatAudioGetByIndex( 
            /* [in] */ eMFormatType _eFormatType,
            /* [in] */ int _nIndex,
            /* [out] */ M_AUD_PROPS *_pAudProps,
            /* [out] */ BSTR *_pbsName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FormatAudioSet( 
            /* [in] */ eMFormatType _eFormatType,
            /* [in] */ M_AUD_PROPS *_pAudProps) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FormatAudioGet( 
            /* [in] */ eMFormatType _eFormatType,
            /* [out] */ M_AUD_PROPS *_pAudProps,
            /* [out] */ int *_pnIndex,
            /* [out] */ BSTR *_pbsName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMFormatVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMFormat * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMFormat * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMFormat * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FormatVideoGetCount )( 
            IMFormat * This,
            /* [in] */ eMFormatType _eFormatType,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FormatVideoGetByIndex )( 
            IMFormat * This,
            /* [in] */ eMFormatType _eFormatType,
            /* [in] */ int _nIndex,
            /* [out] */ M_VID_PROPS *_pVidProps,
            /* [out] */ BSTR *_pbsName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FormatVideoSet )( 
            IMFormat * This,
            /* [in] */ eMFormatType _eFormatType,
            /* [in] */ M_VID_PROPS *_pVidProps);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FormatVideoGet )( 
            IMFormat * This,
            /* [in] */ eMFormatType _eFormatType,
            /* [out] */ M_VID_PROPS *_pVidProps,
            /* [out] */ int *_pnIndex,
            /* [out] */ BSTR *_pbsName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FormatAudioGetCount )( 
            IMFormat * This,
            /* [in] */ eMFormatType _eFormatType,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FormatAudioGetByIndex )( 
            IMFormat * This,
            /* [in] */ eMFormatType _eFormatType,
            /* [in] */ int _nIndex,
            /* [out] */ M_AUD_PROPS *_pAudProps,
            /* [out] */ BSTR *_pbsName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FormatAudioSet )( 
            IMFormat * This,
            /* [in] */ eMFormatType _eFormatType,
            /* [in] */ M_AUD_PROPS *_pAudProps);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FormatAudioGet )( 
            IMFormat * This,
            /* [in] */ eMFormatType _eFormatType,
            /* [out] */ M_AUD_PROPS *_pAudProps,
            /* [out] */ int *_pnIndex,
            /* [out] */ BSTR *_pbsName);
        
        END_INTERFACE
    } IMFormatVtbl;

    interface IMFormat
    {
        CONST_VTBL struct IMFormatVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMFormat_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMFormat_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMFormat_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMFormat_FormatVideoGetCount(This,_eFormatType,_pnCount)	\
    ( (This)->lpVtbl -> FormatVideoGetCount(This,_eFormatType,_pnCount) ) 

#define IMFormat_FormatVideoGetByIndex(This,_eFormatType,_nIndex,_pVidProps,_pbsName)	\
    ( (This)->lpVtbl -> FormatVideoGetByIndex(This,_eFormatType,_nIndex,_pVidProps,_pbsName) ) 

#define IMFormat_FormatVideoSet(This,_eFormatType,_pVidProps)	\
    ( (This)->lpVtbl -> FormatVideoSet(This,_eFormatType,_pVidProps) ) 

#define IMFormat_FormatVideoGet(This,_eFormatType,_pVidProps,_pnIndex,_pbsName)	\
    ( (This)->lpVtbl -> FormatVideoGet(This,_eFormatType,_pVidProps,_pnIndex,_pbsName) ) 

#define IMFormat_FormatAudioGetCount(This,_eFormatType,_pnCount)	\
    ( (This)->lpVtbl -> FormatAudioGetCount(This,_eFormatType,_pnCount) ) 

#define IMFormat_FormatAudioGetByIndex(This,_eFormatType,_nIndex,_pAudProps,_pbsName)	\
    ( (This)->lpVtbl -> FormatAudioGetByIndex(This,_eFormatType,_nIndex,_pAudProps,_pbsName) ) 

#define IMFormat_FormatAudioSet(This,_eFormatType,_pAudProps)	\
    ( (This)->lpVtbl -> FormatAudioSet(This,_eFormatType,_pAudProps) ) 

#define IMFormat_FormatAudioGet(This,_eFormatType,_pAudProps,_pnIndex,_pbsName)	\
    ( (This)->lpVtbl -> FormatAudioGet(This,_eFormatType,_pAudProps,_pnIndex,_pbsName) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMFormat_INTERFACE_DEFINED__ */


#ifndef __IMAudioTrack_INTERFACE_DEFINED__
#define __IMAudioTrack_INTERFACE_DEFINED__

/* interface IMAudioTrack */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMAudioTrack;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F366111-473F-4ad5-A5C2-428FE0C8E03E")
    IMAudioTrack : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TrackLoudnessGet( 
            /* [out] */ M_AUDIO_TRACK_LOUDNESS *_pAudioLoudnessOrg,
            /* [out] */ M_AUDIO_TRACK_LOUDNESS *_pAudioLoudnessOut) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TrackModeSet( 
            /* [in] */ eMAudioTrackMode _eMode,
            /* [in] */ int _nAddToTrack,
            /* [in] */ double _dblAddGain) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TrackModeGet( 
            /* [out] */ eMAudioTrackMode *_peMode,
            /* [out] */ int *_pnAddToTrack,
            /* [out] */ double *_pdblAddGain) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TrackIsVirtual( 
            /* [out] */ BOOL *_pbVirtual,
            /* [out] */ int *_pnSourceTrack,
            /* [out] */ BSTR *_pbsChannelsSet) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TrackChannelsGet( 
            /* [out] */ int *_pnInputChannels,
            /* [out] */ int *_pnOutputChannelIdx,
            /* [out] */ int *_pnOutputChannels) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TrackChannelsSet( 
            /* [in] */ int _nOutputChannels) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TrackOrderSet( 
            /* [in] */ int _nOrder) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TrackOrderGet( 
            /* [out] */ int *_pnOrder) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TrackChannelOrderSet( 
            /* [in] */ BOOL _bInput,
            /* [in] */ int _nChannelIdx,
            /* [in] */ int _nOrder) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TrackChannelOrderGet( 
            /* [in] */ BOOL _bInput,
            /* [in] */ int _nChannelIdx,
            /* [out] */ int *_pnOrder) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TrackGainSet( 
            /* [in] */ int _nChannel,
            /* [in] */ double _dblGain,
            /* [in] */ double _dblTimeForChange) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TrackGainGet( 
            /* [in] */ int _nChannel,
            /* [out] */ double *_pdblGain) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TrackMuteSet( 
            /* [in] */ int _nChannel,
            /* [in] */ BOOL _bMute,
            /* [in] */ double _dblTimeForChange) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TrackMuteGet( 
            /* [in] */ int _nChannel,
            /* [out] */ BOOL *_pbMute) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMAudioTrackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMAudioTrack * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMAudioTrack * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMAudioTrack * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TrackLoudnessGet )( 
            IMAudioTrack * This,
            /* [out] */ M_AUDIO_TRACK_LOUDNESS *_pAudioLoudnessOrg,
            /* [out] */ M_AUDIO_TRACK_LOUDNESS *_pAudioLoudnessOut);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TrackModeSet )( 
            IMAudioTrack * This,
            /* [in] */ eMAudioTrackMode _eMode,
            /* [in] */ int _nAddToTrack,
            /* [in] */ double _dblAddGain);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TrackModeGet )( 
            IMAudioTrack * This,
            /* [out] */ eMAudioTrackMode *_peMode,
            /* [out] */ int *_pnAddToTrack,
            /* [out] */ double *_pdblAddGain);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TrackIsVirtual )( 
            IMAudioTrack * This,
            /* [out] */ BOOL *_pbVirtual,
            /* [out] */ int *_pnSourceTrack,
            /* [out] */ BSTR *_pbsChannelsSet);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TrackChannelsGet )( 
            IMAudioTrack * This,
            /* [out] */ int *_pnInputChannels,
            /* [out] */ int *_pnOutputChannelIdx,
            /* [out] */ int *_pnOutputChannels);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TrackChannelsSet )( 
            IMAudioTrack * This,
            /* [in] */ int _nOutputChannels);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TrackOrderSet )( 
            IMAudioTrack * This,
            /* [in] */ int _nOrder);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TrackOrderGet )( 
            IMAudioTrack * This,
            /* [out] */ int *_pnOrder);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TrackChannelOrderSet )( 
            IMAudioTrack * This,
            /* [in] */ BOOL _bInput,
            /* [in] */ int _nChannelIdx,
            /* [in] */ int _nOrder);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TrackChannelOrderGet )( 
            IMAudioTrack * This,
            /* [in] */ BOOL _bInput,
            /* [in] */ int _nChannelIdx,
            /* [out] */ int *_pnOrder);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TrackGainSet )( 
            IMAudioTrack * This,
            /* [in] */ int _nChannel,
            /* [in] */ double _dblGain,
            /* [in] */ double _dblTimeForChange);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TrackGainGet )( 
            IMAudioTrack * This,
            /* [in] */ int _nChannel,
            /* [out] */ double *_pdblGain);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TrackMuteSet )( 
            IMAudioTrack * This,
            /* [in] */ int _nChannel,
            /* [in] */ BOOL _bMute,
            /* [in] */ double _dblTimeForChange);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TrackMuteGet )( 
            IMAudioTrack * This,
            /* [in] */ int _nChannel,
            /* [out] */ BOOL *_pbMute);
        
        END_INTERFACE
    } IMAudioTrackVtbl;

    interface IMAudioTrack
    {
        CONST_VTBL struct IMAudioTrackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMAudioTrack_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMAudioTrack_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMAudioTrack_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMAudioTrack_TrackLoudnessGet(This,_pAudioLoudnessOrg,_pAudioLoudnessOut)	\
    ( (This)->lpVtbl -> TrackLoudnessGet(This,_pAudioLoudnessOrg,_pAudioLoudnessOut) ) 

#define IMAudioTrack_TrackModeSet(This,_eMode,_nAddToTrack,_dblAddGain)	\
    ( (This)->lpVtbl -> TrackModeSet(This,_eMode,_nAddToTrack,_dblAddGain) ) 

#define IMAudioTrack_TrackModeGet(This,_peMode,_pnAddToTrack,_pdblAddGain)	\
    ( (This)->lpVtbl -> TrackModeGet(This,_peMode,_pnAddToTrack,_pdblAddGain) ) 

#define IMAudioTrack_TrackIsVirtual(This,_pbVirtual,_pnSourceTrack,_pbsChannelsSet)	\
    ( (This)->lpVtbl -> TrackIsVirtual(This,_pbVirtual,_pnSourceTrack,_pbsChannelsSet) ) 

#define IMAudioTrack_TrackChannelsGet(This,_pnInputChannels,_pnOutputChannelIdx,_pnOutputChannels)	\
    ( (This)->lpVtbl -> TrackChannelsGet(This,_pnInputChannels,_pnOutputChannelIdx,_pnOutputChannels) ) 

#define IMAudioTrack_TrackChannelsSet(This,_nOutputChannels)	\
    ( (This)->lpVtbl -> TrackChannelsSet(This,_nOutputChannels) ) 

#define IMAudioTrack_TrackOrderSet(This,_nOrder)	\
    ( (This)->lpVtbl -> TrackOrderSet(This,_nOrder) ) 

#define IMAudioTrack_TrackOrderGet(This,_pnOrder)	\
    ( (This)->lpVtbl -> TrackOrderGet(This,_pnOrder) ) 

#define IMAudioTrack_TrackChannelOrderSet(This,_bInput,_nChannelIdx,_nOrder)	\
    ( (This)->lpVtbl -> TrackChannelOrderSet(This,_bInput,_nChannelIdx,_nOrder) ) 

#define IMAudioTrack_TrackChannelOrderGet(This,_bInput,_nChannelIdx,_pnOrder)	\
    ( (This)->lpVtbl -> TrackChannelOrderGet(This,_bInput,_nChannelIdx,_pnOrder) ) 

#define IMAudioTrack_TrackGainSet(This,_nChannel,_dblGain,_dblTimeForChange)	\
    ( (This)->lpVtbl -> TrackGainSet(This,_nChannel,_dblGain,_dblTimeForChange) ) 

#define IMAudioTrack_TrackGainGet(This,_nChannel,_pdblGain)	\
    ( (This)->lpVtbl -> TrackGainGet(This,_nChannel,_pdblGain) ) 

#define IMAudioTrack_TrackMuteSet(This,_nChannel,_bMute,_dblTimeForChange)	\
    ( (This)->lpVtbl -> TrackMuteSet(This,_nChannel,_bMute,_dblTimeForChange) ) 

#define IMAudioTrack_TrackMuteGet(This,_nChannel,_pbMute)	\
    ( (This)->lpVtbl -> TrackMuteGet(This,_nChannel,_pbMute) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMAudioTrack_INTERFACE_DEFINED__ */


#ifndef __IMAudio_INTERFACE_DEFINED__
#define __IMAudio_INTERFACE_DEFINED__

/* interface IMAudio */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMAudio;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F366110-473F-4ad5-A5C2-428FE0C8E03E")
    IMAudio : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AudioSplitStringGet( 
            /* [out] */ BSTR *_pbsSplitString,
            /* [out] */ int *_pnChannels) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AudioSplitStringSet( 
            /* [in] */ BSTR _bsSplitString) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AudioTracksSetCount( 
            /* [in] */ int _nTracks) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AudioTracksGetCount( 
            /* [out] */ int *_pnTracks) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AudioTrackGetByIndex( 
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsDesc,
            /* [out] */ IMAudioTrack **_ppTrack) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AudioChannelsPerTrackSet( 
            /* [in] */ int _nChannelsPerTrack) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AudioChannelsPerTrackGet( 
            /* [out] */ int *_pnChannelsPerTrackSet) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AudioTrackAdd( 
            /* [in] */ int _nSourceTrack,
            /* [in] */ BSTR _bsUseChannels,
            /* [in] */ BSTR _bsDesc,
            /* [out] */ IMAudioTrack **_ppTrack) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AudioTrackRemove( 
            /* [in] */ IMAudioTrack *_pTrack) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMAudioVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMAudio * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMAudio * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMAudio * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AudioSplitStringGet )( 
            IMAudio * This,
            /* [out] */ BSTR *_pbsSplitString,
            /* [out] */ int *_pnChannels);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AudioSplitStringSet )( 
            IMAudio * This,
            /* [in] */ BSTR _bsSplitString);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AudioTracksSetCount )( 
            IMAudio * This,
            /* [in] */ int _nTracks);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AudioTracksGetCount )( 
            IMAudio * This,
            /* [out] */ int *_pnTracks);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AudioTrackGetByIndex )( 
            IMAudio * This,
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsDesc,
            /* [out] */ IMAudioTrack **_ppTrack);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AudioChannelsPerTrackSet )( 
            IMAudio * This,
            /* [in] */ int _nChannelsPerTrack);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AudioChannelsPerTrackGet )( 
            IMAudio * This,
            /* [out] */ int *_pnChannelsPerTrackSet);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AudioTrackAdd )( 
            IMAudio * This,
            /* [in] */ int _nSourceTrack,
            /* [in] */ BSTR _bsUseChannels,
            /* [in] */ BSTR _bsDesc,
            /* [out] */ IMAudioTrack **_ppTrack);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AudioTrackRemove )( 
            IMAudio * This,
            /* [in] */ IMAudioTrack *_pTrack);
        
        END_INTERFACE
    } IMAudioVtbl;

    interface IMAudio
    {
        CONST_VTBL struct IMAudioVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMAudio_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMAudio_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMAudio_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMAudio_AudioSplitStringGet(This,_pbsSplitString,_pnChannels)	\
    ( (This)->lpVtbl -> AudioSplitStringGet(This,_pbsSplitString,_pnChannels) ) 

#define IMAudio_AudioSplitStringSet(This,_bsSplitString)	\
    ( (This)->lpVtbl -> AudioSplitStringSet(This,_bsSplitString) ) 

#define IMAudio_AudioTracksSetCount(This,_nTracks)	\
    ( (This)->lpVtbl -> AudioTracksSetCount(This,_nTracks) ) 

#define IMAudio_AudioTracksGetCount(This,_pnTracks)	\
    ( (This)->lpVtbl -> AudioTracksGetCount(This,_pnTracks) ) 

#define IMAudio_AudioTrackGetByIndex(This,_nIndex,_pbsDesc,_ppTrack)	\
    ( (This)->lpVtbl -> AudioTrackGetByIndex(This,_nIndex,_pbsDesc,_ppTrack) ) 

#define IMAudio_AudioChannelsPerTrackSet(This,_nChannelsPerTrack)	\
    ( (This)->lpVtbl -> AudioChannelsPerTrackSet(This,_nChannelsPerTrack) ) 

#define IMAudio_AudioChannelsPerTrackGet(This,_pnChannelsPerTrackSet)	\
    ( (This)->lpVtbl -> AudioChannelsPerTrackGet(This,_pnChannelsPerTrackSet) ) 

#define IMAudio_AudioTrackAdd(This,_nSourceTrack,_bsUseChannels,_bsDesc,_ppTrack)	\
    ( (This)->lpVtbl -> AudioTrackAdd(This,_nSourceTrack,_bsUseChannels,_bsDesc,_ppTrack) ) 

#define IMAudio_AudioTrackRemove(This,_pTrack)	\
    ( (This)->lpVtbl -> AudioTrackRemove(This,_pTrack) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMAudio_INTERFACE_DEFINED__ */


#ifndef __IMReceiver_INTERFACE_DEFINED__
#define __IMReceiver_INTERFACE_DEFINED__

/* interface IMReceiver */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMReceiver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F366140-473F-4ad5-A5C2-428FE0C8E03E")
    IMReceiver : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReceiverChannelAdd( 
            /* [in] */ IUnknown *_pSender,
            /* [out][in] */ BSTR *_pbsChannelID,
            /* [in] */ BSTR _bsXMLParam) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReceiverChannelAddByName( 
            /* [in] */ BSTR _bsSenderName,
            /* [out][in] */ BSTR *_pbsChannelID,
            /* [in] */ BSTR _bsXMLParam) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReceiverChannelRemove( 
            /* [in] */ BSTR _bsChannelID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReceiverChannelGetCount( 
            /* [out] */ int *_pnCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReceiverChannelGetByIndex( 
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsChannelID,
            /* [out] */ BSTR *_pbsSenderName,
            /* [out] */ BSTR *_pbsTransName,
            /* [out] */ BSTR *_pbsXMLParam) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReceiverPutFrame( 
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ IMFrame *_pFrame) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReceiverPutFlush( 
            /* [in] */ BSTR _bsChannelID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReceiverPutEOS( 
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ BOOL _bRemoveChannel) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMReceiverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMReceiver * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMReceiver * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMReceiver * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReceiverChannelAdd )( 
            IMReceiver * This,
            /* [in] */ IUnknown *_pSender,
            /* [out][in] */ BSTR *_pbsChannelID,
            /* [in] */ BSTR _bsXMLParam);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReceiverChannelAddByName )( 
            IMReceiver * This,
            /* [in] */ BSTR _bsSenderName,
            /* [out][in] */ BSTR *_pbsChannelID,
            /* [in] */ BSTR _bsXMLParam);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReceiverChannelRemove )( 
            IMReceiver * This,
            /* [in] */ BSTR _bsChannelID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReceiverChannelGetCount )( 
            IMReceiver * This,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReceiverChannelGetByIndex )( 
            IMReceiver * This,
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsChannelID,
            /* [out] */ BSTR *_pbsSenderName,
            /* [out] */ BSTR *_pbsTransName,
            /* [out] */ BSTR *_pbsXMLParam);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReceiverPutFrame )( 
            IMReceiver * This,
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ IMFrame *_pFrame);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReceiverPutFlush )( 
            IMReceiver * This,
            /* [in] */ BSTR _bsChannelID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReceiverPutEOS )( 
            IMReceiver * This,
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ BOOL _bRemoveChannel);
        
        END_INTERFACE
    } IMReceiverVtbl;

    interface IMReceiver
    {
        CONST_VTBL struct IMReceiverVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMReceiver_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMReceiver_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMReceiver_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMReceiver_ReceiverChannelAdd(This,_pSender,_pbsChannelID,_bsXMLParam)	\
    ( (This)->lpVtbl -> ReceiverChannelAdd(This,_pSender,_pbsChannelID,_bsXMLParam) ) 

#define IMReceiver_ReceiverChannelAddByName(This,_bsSenderName,_pbsChannelID,_bsXMLParam)	\
    ( (This)->lpVtbl -> ReceiverChannelAddByName(This,_bsSenderName,_pbsChannelID,_bsXMLParam) ) 

#define IMReceiver_ReceiverChannelRemove(This,_bsChannelID)	\
    ( (This)->lpVtbl -> ReceiverChannelRemove(This,_bsChannelID) ) 

#define IMReceiver_ReceiverChannelGetCount(This,_pnCount)	\
    ( (This)->lpVtbl -> ReceiverChannelGetCount(This,_pnCount) ) 

#define IMReceiver_ReceiverChannelGetByIndex(This,_nIndex,_pbsChannelID,_pbsSenderName,_pbsTransName,_pbsXMLParam)	\
    ( (This)->lpVtbl -> ReceiverChannelGetByIndex(This,_nIndex,_pbsChannelID,_pbsSenderName,_pbsTransName,_pbsXMLParam) ) 

#define IMReceiver_ReceiverPutFrame(This,_bsChannelID,_pFrame)	\
    ( (This)->lpVtbl -> ReceiverPutFrame(This,_bsChannelID,_pFrame) ) 

#define IMReceiver_ReceiverPutFlush(This,_bsChannelID)	\
    ( (This)->lpVtbl -> ReceiverPutFlush(This,_bsChannelID) ) 

#define IMReceiver_ReceiverPutEOS(This,_bsChannelID,_bRemoveChannel)	\
    ( (This)->lpVtbl -> ReceiverPutEOS(This,_bsChannelID,_bRemoveChannel) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMReceiver_INTERFACE_DEFINED__ */


#ifndef __IMSenders_INTERFACE_DEFINED__
#define __IMSenders_INTERFACE_DEFINED__

/* interface IMSenders */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMSenders;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F366155-473F-4ad5-A5C2-428FE0C8E03E")
    IMSenders : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SendersGetCount( 
            /* [out] */ int *_pnCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SendersGetByIndex( 
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsName,
            /* [out] */ M_VID_PROPS *_pVidProps,
            /* [out] */ M_AUD_PROPS *_pAudProps) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SendersGet( 
            /* [in] */ BSTR _bsName,
            /* [out] */ IUnknown **_ppSender) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMSendersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMSenders * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMSenders * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMSenders * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SendersGetCount )( 
            IMSenders * This,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SendersGetByIndex )( 
            IMSenders * This,
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsName,
            /* [out] */ M_VID_PROPS *_pVidProps,
            /* [out] */ M_AUD_PROPS *_pAudProps);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SendersGet )( 
            IMSenders * This,
            /* [in] */ BSTR _bsName,
            /* [out] */ IUnknown **_ppSender);
        
        END_INTERFACE
    } IMSendersVtbl;

    interface IMSenders
    {
        CONST_VTBL struct IMSendersVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMSenders_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMSenders_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMSenders_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMSenders_SendersGetCount(This,_pnCount)	\
    ( (This)->lpVtbl -> SendersGetCount(This,_pnCount) ) 

#define IMSenders_SendersGetByIndex(This,_nIndex,_pbsName,_pVidProps,_pAudProps)	\
    ( (This)->lpVtbl -> SendersGetByIndex(This,_nIndex,_pbsName,_pVidProps,_pAudProps) ) 

#define IMSenders_SendersGet(This,_bsName,_ppSender)	\
    ( (This)->lpVtbl -> SendersGet(This,_bsName,_ppSender) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMSenders_INTERFACE_DEFINED__ */


#ifndef __IMFile_INTERFACE_DEFINED__
#define __IMFile_INTERFACE_DEFINED__

/* interface IMFile */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMFile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F366170-473F-4ad5-A5C2-428FE0C8E03E")
    IMFile : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FileNameSet( 
            /* [in] */ BSTR _bsFile,
            /* [in] */ BSTR _bsParam) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FileNameGet( 
            /* [out] */ BSTR *_pbsFile) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FileInOutSet( 
            /* [in] */ double _dblIn,
            /* [in] */ double _dblOut) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FileInOutGet( 
            /* [out] */ double *_pdblIn,
            /* [out] */ double *_pdblOut,
            /* [out] */ double *_pdblDuration) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FilePosSet( 
            /* [in] */ double _dblPos,
            /* [in] */ double _dblPreroll) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FilePosGet( 
            /* [out] */ double *_pdblFilePos) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FilePlayStart( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FilePlayPause( 
            /* [in] */ double _dblSeconds) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FilePlayStop( 
            /* [in] */ double _dblSeconds) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FileStateGet( 
            /* [out] */ eMState *_peState,
            /* [out] */ double *_pdblTimeRemain) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FileRateSet( 
            /* [in] */ double _dblRate) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FileRateGet( 
            /* [out] */ double *_pdblRate) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FileFrameGet( 
            /* [in] */ double _dblPos,
            /* [in] */ double _dblPreroll,
            /* [out] */ IMFrame **_ppFrame) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FileInOutSetTC( 
            /* [in] */ M_TIMECODE *_pTCIn,
            /* [in] */ M_TIMECODE *_pTCOut) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FileInOutGetTC( 
            /* [out] */ M_TIMECODE *_pTCIn,
            /* [out] */ M_TIMECODE *_pTCOut,
            /* [out] */ BOOL *_pbOutSpecified) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FilePosSetTC( 
            /* [in] */ M_TIMECODE *_pTC) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FilePosGetTC( 
            /* [out] */ M_TIMECODE *_pTC) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FileFrameGetByTC( 
            /* [in] */ M_TIMECODE *_pTC,
            /* [out] */ IMFrame **_ppFrame) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMFileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMFile * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMFile * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMFile * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FileNameSet )( 
            IMFile * This,
            /* [in] */ BSTR _bsFile,
            /* [in] */ BSTR _bsParam);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FileNameGet )( 
            IMFile * This,
            /* [out] */ BSTR *_pbsFile);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FileInOutSet )( 
            IMFile * This,
            /* [in] */ double _dblIn,
            /* [in] */ double _dblOut);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FileInOutGet )( 
            IMFile * This,
            /* [out] */ double *_pdblIn,
            /* [out] */ double *_pdblOut,
            /* [out] */ double *_pdblDuration);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilePosSet )( 
            IMFile * This,
            /* [in] */ double _dblPos,
            /* [in] */ double _dblPreroll);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilePosGet )( 
            IMFile * This,
            /* [out] */ double *_pdblFilePos);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilePlayStart )( 
            IMFile * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilePlayPause )( 
            IMFile * This,
            /* [in] */ double _dblSeconds);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilePlayStop )( 
            IMFile * This,
            /* [in] */ double _dblSeconds);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FileStateGet )( 
            IMFile * This,
            /* [out] */ eMState *_peState,
            /* [out] */ double *_pdblTimeRemain);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FileRateSet )( 
            IMFile * This,
            /* [in] */ double _dblRate);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FileRateGet )( 
            IMFile * This,
            /* [out] */ double *_pdblRate);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FileFrameGet )( 
            IMFile * This,
            /* [in] */ double _dblPos,
            /* [in] */ double _dblPreroll,
            /* [out] */ IMFrame **_ppFrame);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FileInOutSetTC )( 
            IMFile * This,
            /* [in] */ M_TIMECODE *_pTCIn,
            /* [in] */ M_TIMECODE *_pTCOut);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FileInOutGetTC )( 
            IMFile * This,
            /* [out] */ M_TIMECODE *_pTCIn,
            /* [out] */ M_TIMECODE *_pTCOut,
            /* [out] */ BOOL *_pbOutSpecified);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilePosSetTC )( 
            IMFile * This,
            /* [in] */ M_TIMECODE *_pTC);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilePosGetTC )( 
            IMFile * This,
            /* [out] */ M_TIMECODE *_pTC);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FileFrameGetByTC )( 
            IMFile * This,
            /* [in] */ M_TIMECODE *_pTC,
            /* [out] */ IMFrame **_ppFrame);
        
        END_INTERFACE
    } IMFileVtbl;

    interface IMFile
    {
        CONST_VTBL struct IMFileVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMFile_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMFile_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMFile_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMFile_FileNameSet(This,_bsFile,_bsParam)	\
    ( (This)->lpVtbl -> FileNameSet(This,_bsFile,_bsParam) ) 

#define IMFile_FileNameGet(This,_pbsFile)	\
    ( (This)->lpVtbl -> FileNameGet(This,_pbsFile) ) 

#define IMFile_FileInOutSet(This,_dblIn,_dblOut)	\
    ( (This)->lpVtbl -> FileInOutSet(This,_dblIn,_dblOut) ) 

#define IMFile_FileInOutGet(This,_pdblIn,_pdblOut,_pdblDuration)	\
    ( (This)->lpVtbl -> FileInOutGet(This,_pdblIn,_pdblOut,_pdblDuration) ) 

#define IMFile_FilePosSet(This,_dblPos,_dblPreroll)	\
    ( (This)->lpVtbl -> FilePosSet(This,_dblPos,_dblPreroll) ) 

#define IMFile_FilePosGet(This,_pdblFilePos)	\
    ( (This)->lpVtbl -> FilePosGet(This,_pdblFilePos) ) 

#define IMFile_FilePlayStart(This)	\
    ( (This)->lpVtbl -> FilePlayStart(This) ) 

#define IMFile_FilePlayPause(This,_dblSeconds)	\
    ( (This)->lpVtbl -> FilePlayPause(This,_dblSeconds) ) 

#define IMFile_FilePlayStop(This,_dblSeconds)	\
    ( (This)->lpVtbl -> FilePlayStop(This,_dblSeconds) ) 

#define IMFile_FileStateGet(This,_peState,_pdblTimeRemain)	\
    ( (This)->lpVtbl -> FileStateGet(This,_peState,_pdblTimeRemain) ) 

#define IMFile_FileRateSet(This,_dblRate)	\
    ( (This)->lpVtbl -> FileRateSet(This,_dblRate) ) 

#define IMFile_FileRateGet(This,_pdblRate)	\
    ( (This)->lpVtbl -> FileRateGet(This,_pdblRate) ) 

#define IMFile_FileFrameGet(This,_dblPos,_dblPreroll,_ppFrame)	\
    ( (This)->lpVtbl -> FileFrameGet(This,_dblPos,_dblPreroll,_ppFrame) ) 

#define IMFile_FileInOutSetTC(This,_pTCIn,_pTCOut)	\
    ( (This)->lpVtbl -> FileInOutSetTC(This,_pTCIn,_pTCOut) ) 

#define IMFile_FileInOutGetTC(This,_pTCIn,_pTCOut,_pbOutSpecified)	\
    ( (This)->lpVtbl -> FileInOutGetTC(This,_pTCIn,_pTCOut,_pbOutSpecified) ) 

#define IMFile_FilePosSetTC(This,_pTC)	\
    ( (This)->lpVtbl -> FilePosSetTC(This,_pTC) ) 

#define IMFile_FilePosGetTC(This,_pTC)	\
    ( (This)->lpVtbl -> FilePosGetTC(This,_pTC) ) 

#define IMFile_FileFrameGetByTC(This,_pTC,_ppFrame)	\
    ( (This)->lpVtbl -> FileFrameGetByTC(This,_pTC,_ppFrame) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMFile_INTERFACE_DEFINED__ */


#ifndef __IMItem_INTERFACE_DEFINED__
#define __IMItem_INTERFACE_DEFINED__

/* interface IMItem */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F366172-473F-4ad5-A5C2-428FE0C8E03E")
    IMItem : public IMFile
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ItemTypeGet( 
            /* [out] */ eMItemType *_peType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ItemStartTimeSet( 
            /* [in] */ M_DATETIME *_pStartTime,
            /* [in] */ eMStartType _eStartType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ItemTimesGet( 
            /* [out] */ M_DATETIME *_pStartTime,
            /* [out] */ M_DATETIME *_pStopTime,
            /* [out] */ eMStartType *_peStartType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ItemPlayTimeGet( 
            /* [out] */ double *_pdblPlayTime) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ItemCommandSet( 
            /* [in] */ BSTR _bsCommand,
            /* [in] */ BSTR _bsParam,
            /* [in] */ IUnknown *_pTargetObject) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ItemCommandGet( 
            /* [out] */ BSTR *_pbsCommand,
            /* [out] */ BSTR *_pbsParam,
            /* [out] */ IUnknown **_ppTargetObject) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ItemInnerGet( 
            /* [out] */ IUnknown **_ppInnerObject) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ItemCommandExecute( 
            /* [in] */ IUnknown *_pSourceObject) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ItemPosGet( 
            /* [out] */ double *_pdblPlayPos,
            /* [out] */ int *_pnPlaylistIndex) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMItem * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMItem * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMItem * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FileNameSet )( 
            IMItem * This,
            /* [in] */ BSTR _bsFile,
            /* [in] */ BSTR _bsParam);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FileNameGet )( 
            IMItem * This,
            /* [out] */ BSTR *_pbsFile);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FileInOutSet )( 
            IMItem * This,
            /* [in] */ double _dblIn,
            /* [in] */ double _dblOut);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FileInOutGet )( 
            IMItem * This,
            /* [out] */ double *_pdblIn,
            /* [out] */ double *_pdblOut,
            /* [out] */ double *_pdblDuration);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilePosSet )( 
            IMItem * This,
            /* [in] */ double _dblPos,
            /* [in] */ double _dblPreroll);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilePosGet )( 
            IMItem * This,
            /* [out] */ double *_pdblFilePos);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilePlayStart )( 
            IMItem * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilePlayPause )( 
            IMItem * This,
            /* [in] */ double _dblSeconds);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilePlayStop )( 
            IMItem * This,
            /* [in] */ double _dblSeconds);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FileStateGet )( 
            IMItem * This,
            /* [out] */ eMState *_peState,
            /* [out] */ double *_pdblTimeRemain);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FileRateSet )( 
            IMItem * This,
            /* [in] */ double _dblRate);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FileRateGet )( 
            IMItem * This,
            /* [out] */ double *_pdblRate);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FileFrameGet )( 
            IMItem * This,
            /* [in] */ double _dblPos,
            /* [in] */ double _dblPreroll,
            /* [out] */ IMFrame **_ppFrame);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FileInOutSetTC )( 
            IMItem * This,
            /* [in] */ M_TIMECODE *_pTCIn,
            /* [in] */ M_TIMECODE *_pTCOut);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FileInOutGetTC )( 
            IMItem * This,
            /* [out] */ M_TIMECODE *_pTCIn,
            /* [out] */ M_TIMECODE *_pTCOut,
            /* [out] */ BOOL *_pbOutSpecified);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilePosSetTC )( 
            IMItem * This,
            /* [in] */ M_TIMECODE *_pTC);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FilePosGetTC )( 
            IMItem * This,
            /* [out] */ M_TIMECODE *_pTC);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FileFrameGetByTC )( 
            IMItem * This,
            /* [in] */ M_TIMECODE *_pTC,
            /* [out] */ IMFrame **_ppFrame);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ItemTypeGet )( 
            IMItem * This,
            /* [out] */ eMItemType *_peType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ItemStartTimeSet )( 
            IMItem * This,
            /* [in] */ M_DATETIME *_pStartTime,
            /* [in] */ eMStartType _eStartType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ItemTimesGet )( 
            IMItem * This,
            /* [out] */ M_DATETIME *_pStartTime,
            /* [out] */ M_DATETIME *_pStopTime,
            /* [out] */ eMStartType *_peStartType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ItemPlayTimeGet )( 
            IMItem * This,
            /* [out] */ double *_pdblPlayTime);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ItemCommandSet )( 
            IMItem * This,
            /* [in] */ BSTR _bsCommand,
            /* [in] */ BSTR _bsParam,
            /* [in] */ IUnknown *_pTargetObject);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ItemCommandGet )( 
            IMItem * This,
            /* [out] */ BSTR *_pbsCommand,
            /* [out] */ BSTR *_pbsParam,
            /* [out] */ IUnknown **_ppTargetObject);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ItemInnerGet )( 
            IMItem * This,
            /* [out] */ IUnknown **_ppInnerObject);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ItemCommandExecute )( 
            IMItem * This,
            /* [in] */ IUnknown *_pSourceObject);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ItemPosGet )( 
            IMItem * This,
            /* [out] */ double *_pdblPlayPos,
            /* [out] */ int *_pnPlaylistIndex);
        
        END_INTERFACE
    } IMItemVtbl;

    interface IMItem
    {
        CONST_VTBL struct IMItemVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMItem_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMItem_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMItem_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMItem_FileNameSet(This,_bsFile,_bsParam)	\
    ( (This)->lpVtbl -> FileNameSet(This,_bsFile,_bsParam) ) 

#define IMItem_FileNameGet(This,_pbsFile)	\
    ( (This)->lpVtbl -> FileNameGet(This,_pbsFile) ) 

#define IMItem_FileInOutSet(This,_dblIn,_dblOut)	\
    ( (This)->lpVtbl -> FileInOutSet(This,_dblIn,_dblOut) ) 

#define IMItem_FileInOutGet(This,_pdblIn,_pdblOut,_pdblDuration)	\
    ( (This)->lpVtbl -> FileInOutGet(This,_pdblIn,_pdblOut,_pdblDuration) ) 

#define IMItem_FilePosSet(This,_dblPos,_dblPreroll)	\
    ( (This)->lpVtbl -> FilePosSet(This,_dblPos,_dblPreroll) ) 

#define IMItem_FilePosGet(This,_pdblFilePos)	\
    ( (This)->lpVtbl -> FilePosGet(This,_pdblFilePos) ) 

#define IMItem_FilePlayStart(This)	\
    ( (This)->lpVtbl -> FilePlayStart(This) ) 

#define IMItem_FilePlayPause(This,_dblSeconds)	\
    ( (This)->lpVtbl -> FilePlayPause(This,_dblSeconds) ) 

#define IMItem_FilePlayStop(This,_dblSeconds)	\
    ( (This)->lpVtbl -> FilePlayStop(This,_dblSeconds) ) 

#define IMItem_FileStateGet(This,_peState,_pdblTimeRemain)	\
    ( (This)->lpVtbl -> FileStateGet(This,_peState,_pdblTimeRemain) ) 

#define IMItem_FileRateSet(This,_dblRate)	\
    ( (This)->lpVtbl -> FileRateSet(This,_dblRate) ) 

#define IMItem_FileRateGet(This,_pdblRate)	\
    ( (This)->lpVtbl -> FileRateGet(This,_pdblRate) ) 

#define IMItem_FileFrameGet(This,_dblPos,_dblPreroll,_ppFrame)	\
    ( (This)->lpVtbl -> FileFrameGet(This,_dblPos,_dblPreroll,_ppFrame) ) 

#define IMItem_FileInOutSetTC(This,_pTCIn,_pTCOut)	\
    ( (This)->lpVtbl -> FileInOutSetTC(This,_pTCIn,_pTCOut) ) 

#define IMItem_FileInOutGetTC(This,_pTCIn,_pTCOut,_pbOutSpecified)	\
    ( (This)->lpVtbl -> FileInOutGetTC(This,_pTCIn,_pTCOut,_pbOutSpecified) ) 

#define IMItem_FilePosSetTC(This,_pTC)	\
    ( (This)->lpVtbl -> FilePosSetTC(This,_pTC) ) 

#define IMItem_FilePosGetTC(This,_pTC)	\
    ( (This)->lpVtbl -> FilePosGetTC(This,_pTC) ) 

#define IMItem_FileFrameGetByTC(This,_pTC,_ppFrame)	\
    ( (This)->lpVtbl -> FileFrameGetByTC(This,_pTC,_ppFrame) ) 


#define IMItem_ItemTypeGet(This,_peType)	\
    ( (This)->lpVtbl -> ItemTypeGet(This,_peType) ) 

#define IMItem_ItemStartTimeSet(This,_pStartTime,_eStartType)	\
    ( (This)->lpVtbl -> ItemStartTimeSet(This,_pStartTime,_eStartType) ) 

#define IMItem_ItemTimesGet(This,_pStartTime,_pStopTime,_peStartType)	\
    ( (This)->lpVtbl -> ItemTimesGet(This,_pStartTime,_pStopTime,_peStartType) ) 

#define IMItem_ItemPlayTimeGet(This,_pdblPlayTime)	\
    ( (This)->lpVtbl -> ItemPlayTimeGet(This,_pdblPlayTime) ) 

#define IMItem_ItemCommandSet(This,_bsCommand,_bsParam,_pTargetObject)	\
    ( (This)->lpVtbl -> ItemCommandSet(This,_bsCommand,_bsParam,_pTargetObject) ) 

#define IMItem_ItemCommandGet(This,_pbsCommand,_pbsParam,_ppTargetObject)	\
    ( (This)->lpVtbl -> ItemCommandGet(This,_pbsCommand,_pbsParam,_ppTargetObject) ) 

#define IMItem_ItemInnerGet(This,_ppInnerObject)	\
    ( (This)->lpVtbl -> ItemInnerGet(This,_ppInnerObject) ) 

#define IMItem_ItemCommandExecute(This,_pSourceObject)	\
    ( (This)->lpVtbl -> ItemCommandExecute(This,_pSourceObject) ) 

#define IMItem_ItemPosGet(This,_pdblPlayPos,_pnPlaylistIndex)	\
    ( (This)->lpVtbl -> ItemPosGet(This,_pdblPlayPos,_pnPlaylistIndex) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMItem_INTERFACE_DEFINED__ */


#ifndef __IMPlaylist_INTERFACE_DEFINED__
#define __IMPlaylist_INTERFACE_DEFINED__

/* interface IMPlaylist */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMPlaylist;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F366175-473F-4ad5-A5C2-428FE0C8E03E")
    IMPlaylist : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PlaylistGetCount( 
            /* [out] */ int *_pnCount,
            /* [out] */ double *_pdblTotalDuration) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PlaylistGetByIndex( 
            /* [in] */ int _nIndex,
            /* [out] */ double *_pdblFileOffset,
            /* [out] */ BSTR *_pbsPath,
            /* [out] */ IMItem **_ppPlaylistItem) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PlaylistAdd( 
            /* [in] */ IUnknown *_pExternOrRef,
            /* [in] */ BSTR _bsPath,
            /* [in] */ BSTR _bsParam,
            /* [out][in] */ int *_pnIndex,
            /* [out] */ IMItem **_ppPlaylistItem) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PlaylistCommandAdd( 
            /* [in] */ BSTR _bsCommand,
            /* [in] */ BSTR _bsParam,
            /* [in] */ IUnknown *_pTargetObject,
            /* [out][in] */ int *_pnIndex,
            /* [out] */ IMItem **_ppPlaylistItem) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PlaylistRemove( 
            /* [in] */ IMItem *pFile) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PlaylistRemoveByIndex( 
            /* [in] */ int _nIndex,
            /* [in] */ int _nExtraRemove) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PlaylistReorder( 
            /* [in] */ int _nIndex,
            /* [in] */ int _nIndexAdd) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PlaylistPosSet( 
            /* [in] */ int _nIndex,
            /* [in] */ double _dblFileOrListTime,
            /* [in] */ double _dblPreroll) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PlaylistPosGet( 
            /* [out] */ int *_pnIndex,
            /* [out] */ int *_pnNextIndex,
            /* [out] */ double *_pdblFileTime,
            /* [out] */ double *_pdblListTime) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PlaylistBackgroundSet( 
            /* [in] */ IUnknown *_pExternOrRef,
            /* [in] */ BSTR _bsPath,
            /* [in] */ BSTR _bsParam,
            /* [out] */ IMItem **_ppPlaylistItem) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PlaylistBackgroundGet( 
            /* [out] */ BSTR *_pbsPath,
            /* [out] */ IMItem **_ppPlaylistItem) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PlaylistGetByOffset( 
            /* [in] */ double _dblTimeOffset,
            /* [out] */ int *_pnIndex,
            /* [out] */ double *_pdblFileTime,
            /* [out] */ BSTR *_pbsPath,
            /* [out] */ IMItem **_ppPlaylistItem) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMPlaylistVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMPlaylist * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMPlaylist * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMPlaylist * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PlaylistGetCount )( 
            IMPlaylist * This,
            /* [out] */ int *_pnCount,
            /* [out] */ double *_pdblTotalDuration);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PlaylistGetByIndex )( 
            IMPlaylist * This,
            /* [in] */ int _nIndex,
            /* [out] */ double *_pdblFileOffset,
            /* [out] */ BSTR *_pbsPath,
            /* [out] */ IMItem **_ppPlaylistItem);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PlaylistAdd )( 
            IMPlaylist * This,
            /* [in] */ IUnknown *_pExternOrRef,
            /* [in] */ BSTR _bsPath,
            /* [in] */ BSTR _bsParam,
            /* [out][in] */ int *_pnIndex,
            /* [out] */ IMItem **_ppPlaylistItem);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PlaylistCommandAdd )( 
            IMPlaylist * This,
            /* [in] */ BSTR _bsCommand,
            /* [in] */ BSTR _bsParam,
            /* [in] */ IUnknown *_pTargetObject,
            /* [out][in] */ int *_pnIndex,
            /* [out] */ IMItem **_ppPlaylistItem);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PlaylistRemove )( 
            IMPlaylist * This,
            /* [in] */ IMItem *pFile);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PlaylistRemoveByIndex )( 
            IMPlaylist * This,
            /* [in] */ int _nIndex,
            /* [in] */ int _nExtraRemove);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PlaylistReorder )( 
            IMPlaylist * This,
            /* [in] */ int _nIndex,
            /* [in] */ int _nIndexAdd);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PlaylistPosSet )( 
            IMPlaylist * This,
            /* [in] */ int _nIndex,
            /* [in] */ double _dblFileOrListTime,
            /* [in] */ double _dblPreroll);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PlaylistPosGet )( 
            IMPlaylist * This,
            /* [out] */ int *_pnIndex,
            /* [out] */ int *_pnNextIndex,
            /* [out] */ double *_pdblFileTime,
            /* [out] */ double *_pdblListTime);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PlaylistBackgroundSet )( 
            IMPlaylist * This,
            /* [in] */ IUnknown *_pExternOrRef,
            /* [in] */ BSTR _bsPath,
            /* [in] */ BSTR _bsParam,
            /* [out] */ IMItem **_ppPlaylistItem);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PlaylistBackgroundGet )( 
            IMPlaylist * This,
            /* [out] */ BSTR *_pbsPath,
            /* [out] */ IMItem **_ppPlaylistItem);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PlaylistGetByOffset )( 
            IMPlaylist * This,
            /* [in] */ double _dblTimeOffset,
            /* [out] */ int *_pnIndex,
            /* [out] */ double *_pdblFileTime,
            /* [out] */ BSTR *_pbsPath,
            /* [out] */ IMItem **_ppPlaylistItem);
        
        END_INTERFACE
    } IMPlaylistVtbl;

    interface IMPlaylist
    {
        CONST_VTBL struct IMPlaylistVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMPlaylist_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMPlaylist_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMPlaylist_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMPlaylist_PlaylistGetCount(This,_pnCount,_pdblTotalDuration)	\
    ( (This)->lpVtbl -> PlaylistGetCount(This,_pnCount,_pdblTotalDuration) ) 

#define IMPlaylist_PlaylistGetByIndex(This,_nIndex,_pdblFileOffset,_pbsPath,_ppPlaylistItem)	\
    ( (This)->lpVtbl -> PlaylistGetByIndex(This,_nIndex,_pdblFileOffset,_pbsPath,_ppPlaylistItem) ) 

#define IMPlaylist_PlaylistAdd(This,_pExternOrRef,_bsPath,_bsParam,_pnIndex,_ppPlaylistItem)	\
    ( (This)->lpVtbl -> PlaylistAdd(This,_pExternOrRef,_bsPath,_bsParam,_pnIndex,_ppPlaylistItem) ) 

#define IMPlaylist_PlaylistCommandAdd(This,_bsCommand,_bsParam,_pTargetObject,_pnIndex,_ppPlaylistItem)	\
    ( (This)->lpVtbl -> PlaylistCommandAdd(This,_bsCommand,_bsParam,_pTargetObject,_pnIndex,_ppPlaylistItem) ) 

#define IMPlaylist_PlaylistRemove(This,pFile)	\
    ( (This)->lpVtbl -> PlaylistRemove(This,pFile) ) 

#define IMPlaylist_PlaylistRemoveByIndex(This,_nIndex,_nExtraRemove)	\
    ( (This)->lpVtbl -> PlaylistRemoveByIndex(This,_nIndex,_nExtraRemove) ) 

#define IMPlaylist_PlaylistReorder(This,_nIndex,_nIndexAdd)	\
    ( (This)->lpVtbl -> PlaylistReorder(This,_nIndex,_nIndexAdd) ) 

#define IMPlaylist_PlaylistPosSet(This,_nIndex,_dblFileOrListTime,_dblPreroll)	\
    ( (This)->lpVtbl -> PlaylistPosSet(This,_nIndex,_dblFileOrListTime,_dblPreroll) ) 

#define IMPlaylist_PlaylistPosGet(This,_pnIndex,_pnNextIndex,_pdblFileTime,_pdblListTime)	\
    ( (This)->lpVtbl -> PlaylistPosGet(This,_pnIndex,_pnNextIndex,_pdblFileTime,_pdblListTime) ) 

#define IMPlaylist_PlaylistBackgroundSet(This,_pExternOrRef,_bsPath,_bsParam,_ppPlaylistItem)	\
    ( (This)->lpVtbl -> PlaylistBackgroundSet(This,_pExternOrRef,_bsPath,_bsParam,_ppPlaylistItem) ) 

#define IMPlaylist_PlaylistBackgroundGet(This,_pbsPath,_ppPlaylistItem)	\
    ( (This)->lpVtbl -> PlaylistBackgroundGet(This,_pbsPath,_ppPlaylistItem) ) 

#define IMPlaylist_PlaylistGetByOffset(This,_dblTimeOffset,_pnIndex,_pdblFileTime,_pbsPath,_ppPlaylistItem)	\
    ( (This)->lpVtbl -> PlaylistGetByOffset(This,_dblTimeOffset,_pnIndex,_pdblFileTime,_pbsPath,_ppPlaylistItem) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMPlaylist_INTERFACE_DEFINED__ */


#ifndef __IMBreaks_INTERFACE_DEFINED__
#define __IMBreaks_INTERFACE_DEFINED__

/* interface IMBreaks */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMBreaks;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F366177-473F-4ad5-A5C2-428FE0C8E03E")
    IMBreaks : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE BreaksGetCount( 
            /* [out] */ int *_pnCount,
            /* [out] */ double *_pdblTotalDuration) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE BreaksGetByIndex( 
            /* [in] */ int _nIndex,
            /* [out] */ double *_pdblBreakTime,
            /* [out] */ BSTR *_pbsPath,
            /* [out] */ IMItem **_ppBreakItem) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE BreaksAdd( 
            /* [in] */ double _dblTime,
            /* [in] */ IUnknown *_pExternOrRef,
            /* [in] */ BSTR _bsPath,
            /* [in] */ BSTR _bsParam,
            /* [out] */ IMItem **_ppBreakItem) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE BreaksCommandAdd( 
            /* [in] */ double _dblTime,
            /* [in] */ BSTR _bsCommand,
            /* [in] */ BSTR _bsParam,
            /* [in] */ IUnknown *_pTargetObject,
            /* [out] */ IMItem **_ppBreakItem) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE BreaksRemove( 
            /* [in] */ IMItem *_pBreakItem) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE BreaksRemoveByIndex( 
            /* [in] */ int _nIndex,
            /* [in] */ int _nExtraRemove) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE BreaksTimeSet( 
            /* [in] */ int _nIndex,
            /* [in] */ double _dblNewTime) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMBreaksVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMBreaks * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMBreaks * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMBreaks * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *BreaksGetCount )( 
            IMBreaks * This,
            /* [out] */ int *_pnCount,
            /* [out] */ double *_pdblTotalDuration);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *BreaksGetByIndex )( 
            IMBreaks * This,
            /* [in] */ int _nIndex,
            /* [out] */ double *_pdblBreakTime,
            /* [out] */ BSTR *_pbsPath,
            /* [out] */ IMItem **_ppBreakItem);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *BreaksAdd )( 
            IMBreaks * This,
            /* [in] */ double _dblTime,
            /* [in] */ IUnknown *_pExternOrRef,
            /* [in] */ BSTR _bsPath,
            /* [in] */ BSTR _bsParam,
            /* [out] */ IMItem **_ppBreakItem);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *BreaksCommandAdd )( 
            IMBreaks * This,
            /* [in] */ double _dblTime,
            /* [in] */ BSTR _bsCommand,
            /* [in] */ BSTR _bsParam,
            /* [in] */ IUnknown *_pTargetObject,
            /* [out] */ IMItem **_ppBreakItem);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *BreaksRemove )( 
            IMBreaks * This,
            /* [in] */ IMItem *_pBreakItem);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *BreaksRemoveByIndex )( 
            IMBreaks * This,
            /* [in] */ int _nIndex,
            /* [in] */ int _nExtraRemove);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *BreaksTimeSet )( 
            IMBreaks * This,
            /* [in] */ int _nIndex,
            /* [in] */ double _dblNewTime);
        
        END_INTERFACE
    } IMBreaksVtbl;

    interface IMBreaks
    {
        CONST_VTBL struct IMBreaksVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMBreaks_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMBreaks_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMBreaks_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMBreaks_BreaksGetCount(This,_pnCount,_pdblTotalDuration)	\
    ( (This)->lpVtbl -> BreaksGetCount(This,_pnCount,_pdblTotalDuration) ) 

#define IMBreaks_BreaksGetByIndex(This,_nIndex,_pdblBreakTime,_pbsPath,_ppBreakItem)	\
    ( (This)->lpVtbl -> BreaksGetByIndex(This,_nIndex,_pdblBreakTime,_pbsPath,_ppBreakItem) ) 

#define IMBreaks_BreaksAdd(This,_dblTime,_pExternOrRef,_bsPath,_bsParam,_ppBreakItem)	\
    ( (This)->lpVtbl -> BreaksAdd(This,_dblTime,_pExternOrRef,_bsPath,_bsParam,_ppBreakItem) ) 

#define IMBreaks_BreaksCommandAdd(This,_dblTime,_bsCommand,_bsParam,_pTargetObject,_ppBreakItem)	\
    ( (This)->lpVtbl -> BreaksCommandAdd(This,_dblTime,_bsCommand,_bsParam,_pTargetObject,_ppBreakItem) ) 

#define IMBreaks_BreaksRemove(This,_pBreakItem)	\
    ( (This)->lpVtbl -> BreaksRemove(This,_pBreakItem) ) 

#define IMBreaks_BreaksRemoveByIndex(This,_nIndex,_nExtraRemove)	\
    ( (This)->lpVtbl -> BreaksRemoveByIndex(This,_nIndex,_nExtraRemove) ) 

#define IMBreaks_BreaksTimeSet(This,_nIndex,_dblNewTime)	\
    ( (This)->lpVtbl -> BreaksTimeSet(This,_nIndex,_dblNewTime) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMBreaks_INTERFACE_DEFINED__ */


#ifndef __IMScheduler_INTERFACE_DEFINED__
#define __IMScheduler_INTERFACE_DEFINED__

/* interface IMScheduler */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMScheduler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F366178-473F-4ad5-A5C2-428FE0C8E03E")
    IMScheduler : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SchedulerGetCount( 
            /* [out] */ int *_pnCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SchedulerGetByIndex( 
            /* [in] */ int _nIndex,
            /* [out] */ M_DATETIME *_pTime,
            /* [out] */ BSTR *_pbsCommand,
            /* [out] */ IMItem **_ppTask) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SchedulerGetByTime( 
            /* [in] */ M_DATETIME *_pCheckTime,
            /* [out] */ M_DATETIME *_pTaskTime,
            /* [out] */ BSTR *_pbsCommand,
            /* [out] */ IMItem **_ppTask) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SchedulerGetNext( 
            /* [in] */ BOOL _bAllTasks,
            /* [in] */ int _nIndex,
            /* [out] */ M_DATETIME *_pTaskTime,
            /* [out] */ BSTR *_pbsCommand,
            /* [out] */ IMItem **_ppTask) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SchedulerCommandAdd( 
            /* [in] */ M_DATETIME *_pTime,
            /* [in] */ BSTR _bsCommand,
            /* [in] */ BSTR _bsParam,
            /* [in] */ IUnknown *_pSourceOrTargetObject,
            /* [out] */ IMItem **_ppTask) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SchedulerAdd( 
            /* [in] */ M_DATETIME *_pTime,
            /* [in] */ IUnknown *_pExternOrRef,
            /* [in] */ BSTR _bsPath,
            /* [in] */ BSTR _bsParam,
            /* [out] */ IMItem **_ppTask) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SchedulerRemove( 
            /* [in] */ IMItem *_pTask) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SchedulerRemoveByIndex( 
            /* [in] */ int _nIndex,
            /* [in] */ int _nExtraRemove) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SchedulerStatGet( 
            /* [in] */ IMItem *_pTask,
            /* [out] */ M_DATETIME *_pTimeExecute,
            /* [out] */ int *_pnExecutionCount) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMSchedulerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMScheduler * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMScheduler * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMScheduler * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SchedulerGetCount )( 
            IMScheduler * This,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SchedulerGetByIndex )( 
            IMScheduler * This,
            /* [in] */ int _nIndex,
            /* [out] */ M_DATETIME *_pTime,
            /* [out] */ BSTR *_pbsCommand,
            /* [out] */ IMItem **_ppTask);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SchedulerGetByTime )( 
            IMScheduler * This,
            /* [in] */ M_DATETIME *_pCheckTime,
            /* [out] */ M_DATETIME *_pTaskTime,
            /* [out] */ BSTR *_pbsCommand,
            /* [out] */ IMItem **_ppTask);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SchedulerGetNext )( 
            IMScheduler * This,
            /* [in] */ BOOL _bAllTasks,
            /* [in] */ int _nIndex,
            /* [out] */ M_DATETIME *_pTaskTime,
            /* [out] */ BSTR *_pbsCommand,
            /* [out] */ IMItem **_ppTask);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SchedulerCommandAdd )( 
            IMScheduler * This,
            /* [in] */ M_DATETIME *_pTime,
            /* [in] */ BSTR _bsCommand,
            /* [in] */ BSTR _bsParam,
            /* [in] */ IUnknown *_pSourceOrTargetObject,
            /* [out] */ IMItem **_ppTask);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SchedulerAdd )( 
            IMScheduler * This,
            /* [in] */ M_DATETIME *_pTime,
            /* [in] */ IUnknown *_pExternOrRef,
            /* [in] */ BSTR _bsPath,
            /* [in] */ BSTR _bsParam,
            /* [out] */ IMItem **_ppTask);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SchedulerRemove )( 
            IMScheduler * This,
            /* [in] */ IMItem *_pTask);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SchedulerRemoveByIndex )( 
            IMScheduler * This,
            /* [in] */ int _nIndex,
            /* [in] */ int _nExtraRemove);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SchedulerStatGet )( 
            IMScheduler * This,
            /* [in] */ IMItem *_pTask,
            /* [out] */ M_DATETIME *_pTimeExecute,
            /* [out] */ int *_pnExecutionCount);
        
        END_INTERFACE
    } IMSchedulerVtbl;

    interface IMScheduler
    {
        CONST_VTBL struct IMSchedulerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMScheduler_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMScheduler_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMScheduler_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMScheduler_SchedulerGetCount(This,_pnCount)	\
    ( (This)->lpVtbl -> SchedulerGetCount(This,_pnCount) ) 

#define IMScheduler_SchedulerGetByIndex(This,_nIndex,_pTime,_pbsCommand,_ppTask)	\
    ( (This)->lpVtbl -> SchedulerGetByIndex(This,_nIndex,_pTime,_pbsCommand,_ppTask) ) 

#define IMScheduler_SchedulerGetByTime(This,_pCheckTime,_pTaskTime,_pbsCommand,_ppTask)	\
    ( (This)->lpVtbl -> SchedulerGetByTime(This,_pCheckTime,_pTaskTime,_pbsCommand,_ppTask) ) 

#define IMScheduler_SchedulerGetNext(This,_bAllTasks,_nIndex,_pTaskTime,_pbsCommand,_ppTask)	\
    ( (This)->lpVtbl -> SchedulerGetNext(This,_bAllTasks,_nIndex,_pTaskTime,_pbsCommand,_ppTask) ) 

#define IMScheduler_SchedulerCommandAdd(This,_pTime,_bsCommand,_bsParam,_pSourceOrTargetObject,_ppTask)	\
    ( (This)->lpVtbl -> SchedulerCommandAdd(This,_pTime,_bsCommand,_bsParam,_pSourceOrTargetObject,_ppTask) ) 

#define IMScheduler_SchedulerAdd(This,_pTime,_pExternOrRef,_bsPath,_bsParam,_ppTask)	\
    ( (This)->lpVtbl -> SchedulerAdd(This,_pTime,_pExternOrRef,_bsPath,_bsParam,_ppTask) ) 

#define IMScheduler_SchedulerRemove(This,_pTask)	\
    ( (This)->lpVtbl -> SchedulerRemove(This,_pTask) ) 

#define IMScheduler_SchedulerRemoveByIndex(This,_nIndex,_nExtraRemove)	\
    ( (This)->lpVtbl -> SchedulerRemoveByIndex(This,_nIndex,_nExtraRemove) ) 

#define IMScheduler_SchedulerStatGet(This,_pTask,_pTimeExecute,_pnExecutionCount)	\
    ( (This)->lpVtbl -> SchedulerStatGet(This,_pTask,_pTimeExecute,_pnExecutionCount) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMScheduler_INTERFACE_DEFINED__ */


#ifndef __IMDevice_INTERFACE_DEFINED__
#define __IMDevice_INTERFACE_DEFINED__

/* interface IMDevice */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMDevice;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F366180-473F-4ad5-A5C2-428FE0C8E03E")
    IMDevice : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeviceGetCount( 
            /* [in] */ BOOL _bTypesEnum,
            /* [in] */ BSTR _bsType,
            /* [out] */ int *_pnCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeviceGetByIndex( 
            /* [in] */ BOOL _bTypesEnum,
            /* [in] */ BSTR _bsType,
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsNameOrType,
            /* [out] */ BSTR *_pbsXMLDesc) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeviceSet( 
            /* [in] */ BSTR _bsType,
            /* [in] */ BSTR _bsName,
            /* [in] */ BSTR _bsParam) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeviceGet( 
            /* [in] */ BSTR _bsType,
            /* [out] */ BSTR *_pbsName,
            /* [out] */ BSTR *_pbsParam,
            /* [out] */ int *_pnIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeviceShowProps( 
            /* [in] */ BSTR _bsType,
            /* [in] */ BSTR _bsPropsType,
            /* [in] */ LONGLONG _lWndHandle) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMDeviceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMDevice * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMDevice * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMDevice * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeviceGetCount )( 
            IMDevice * This,
            /* [in] */ BOOL _bTypesEnum,
            /* [in] */ BSTR _bsType,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeviceGetByIndex )( 
            IMDevice * This,
            /* [in] */ BOOL _bTypesEnum,
            /* [in] */ BSTR _bsType,
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsNameOrType,
            /* [out] */ BSTR *_pbsXMLDesc);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeviceSet )( 
            IMDevice * This,
            /* [in] */ BSTR _bsType,
            /* [in] */ BSTR _bsName,
            /* [in] */ BSTR _bsParam);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeviceGet )( 
            IMDevice * This,
            /* [in] */ BSTR _bsType,
            /* [out] */ BSTR *_pbsName,
            /* [out] */ BSTR *_pbsParam,
            /* [out] */ int *_pnIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeviceShowProps )( 
            IMDevice * This,
            /* [in] */ BSTR _bsType,
            /* [in] */ BSTR _bsPropsType,
            /* [in] */ LONGLONG _lWndHandle);
        
        END_INTERFACE
    } IMDeviceVtbl;

    interface IMDevice
    {
        CONST_VTBL struct IMDeviceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMDevice_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMDevice_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMDevice_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMDevice_DeviceGetCount(This,_bTypesEnum,_bsType,_pnCount)	\
    ( (This)->lpVtbl -> DeviceGetCount(This,_bTypesEnum,_bsType,_pnCount) ) 

#define IMDevice_DeviceGetByIndex(This,_bTypesEnum,_bsType,_nIndex,_pbsNameOrType,_pbsXMLDesc)	\
    ( (This)->lpVtbl -> DeviceGetByIndex(This,_bTypesEnum,_bsType,_nIndex,_pbsNameOrType,_pbsXMLDesc) ) 

#define IMDevice_DeviceSet(This,_bsType,_bsName,_bsParam)	\
    ( (This)->lpVtbl -> DeviceSet(This,_bsType,_bsName,_bsParam) ) 

#define IMDevice_DeviceGet(This,_bsType,_pbsName,_pbsParam,_pnIndex)	\
    ( (This)->lpVtbl -> DeviceGet(This,_bsType,_pbsName,_pbsParam,_pnIndex) ) 

#define IMDevice_DeviceShowProps(This,_bsType,_bsPropsType,_lWndHandle)	\
    ( (This)->lpVtbl -> DeviceShowProps(This,_bsType,_bsPropsType,_lWndHandle) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMDevice_INTERFACE_DEFINED__ */


#ifndef __IMPlugins_INTERFACE_DEFINED__
#define __IMPlugins_INTERFACE_DEFINED__

/* interface IMPlugins */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMPlugins;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F366190-473F-4ad5-A5C2-428FE0C8E03E")
    IMPlugins : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PluginsGetCount( 
            /* [out] */ int *_pnCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PluginsGetByIndex( 
            /* [in] */ int _nIndex,
            /* [out] */ IUnknown **_pPlugin,
            /* [out] */ LONGLONG *_pllCallbackUserData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PluginsAdd( 
            /* [in] */ IUnknown *_pPlugin,
            /* [in] */ LONGLONG _llCallbackUserData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PluginsRemove( 
            /* [in] */ IUnknown *_pPlugin) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PluginsAddVB6( 
            /* [in] */ IUnknown *_pPlugin,
            /* [in] */ LONG _lCallbackUserData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PluginsGetByIndexVB6( 
            /* [in] */ int _nIndex,
            /* [out] */ IUnknown **_pPlugin,
            /* [out] */ LONG *_pllCallbackUserData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PluginsReorder( 
            /* [in] */ IUnknown *_pPlugin,
            /* [in] */ int _nOrderChange) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMPluginsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMPlugins * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMPlugins * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMPlugins * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PluginsGetCount )( 
            IMPlugins * This,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PluginsGetByIndex )( 
            IMPlugins * This,
            /* [in] */ int _nIndex,
            /* [out] */ IUnknown **_pPlugin,
            /* [out] */ LONGLONG *_pllCallbackUserData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PluginsAdd )( 
            IMPlugins * This,
            /* [in] */ IUnknown *_pPlugin,
            /* [in] */ LONGLONG _llCallbackUserData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PluginsRemove )( 
            IMPlugins * This,
            /* [in] */ IUnknown *_pPlugin);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PluginsAddVB6 )( 
            IMPlugins * This,
            /* [in] */ IUnknown *_pPlugin,
            /* [in] */ LONG _lCallbackUserData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PluginsGetByIndexVB6 )( 
            IMPlugins * This,
            /* [in] */ int _nIndex,
            /* [out] */ IUnknown **_pPlugin,
            /* [out] */ LONG *_pllCallbackUserData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *PluginsReorder )( 
            IMPlugins * This,
            /* [in] */ IUnknown *_pPlugin,
            /* [in] */ int _nOrderChange);
        
        END_INTERFACE
    } IMPluginsVtbl;

    interface IMPlugins
    {
        CONST_VTBL struct IMPluginsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMPlugins_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMPlugins_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMPlugins_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMPlugins_PluginsGetCount(This,_pnCount)	\
    ( (This)->lpVtbl -> PluginsGetCount(This,_pnCount) ) 

#define IMPlugins_PluginsGetByIndex(This,_nIndex,_pPlugin,_pllCallbackUserData)	\
    ( (This)->lpVtbl -> PluginsGetByIndex(This,_nIndex,_pPlugin,_pllCallbackUserData) ) 

#define IMPlugins_PluginsAdd(This,_pPlugin,_llCallbackUserData)	\
    ( (This)->lpVtbl -> PluginsAdd(This,_pPlugin,_llCallbackUserData) ) 

#define IMPlugins_PluginsRemove(This,_pPlugin)	\
    ( (This)->lpVtbl -> PluginsRemove(This,_pPlugin) ) 

#define IMPlugins_PluginsAddVB6(This,_pPlugin,_lCallbackUserData)	\
    ( (This)->lpVtbl -> PluginsAddVB6(This,_pPlugin,_lCallbackUserData) ) 

#define IMPlugins_PluginsGetByIndexVB6(This,_nIndex,_pPlugin,_pllCallbackUserData)	\
    ( (This)->lpVtbl -> PluginsGetByIndexVB6(This,_nIndex,_pPlugin,_pllCallbackUserData) ) 

#define IMPlugins_PluginsReorder(This,_pPlugin,_nOrderChange)	\
    ( (This)->lpVtbl -> PluginsReorder(This,_pPlugin,_nOrderChange) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMPlugins_INTERFACE_DEFINED__ */


#ifndef __IMPlugin_INTERFACE_DEFINED__
#define __IMPlugin_INTERFACE_DEFINED__

/* interface IMPlugin */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMPlugin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5F366195-473F-4ad5-A5C2-428FE0C8E03E")
    IMPlugin : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnMediaReceive( 
            /* [in] */ LONGLONG _llCallbackUserData,
            /* [in] */ IUnknown *_pSender,
            /* [in] */ IMFrame *_pFrame,
            /* [out] */ IMFrame **_ppFrameRes) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnMediaEnd( 
            /* [in] */ LONGLONG _llCallbackUserData,
            /* [in] */ IUnknown *_pSender,
            /* [in] */ DWORD _dwFlags) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnMediaFlush( 
            /* [in] */ LONGLONG _llCallbackUserData,
            /* [in] */ IUnknown *_pSender,
            /* [in] */ DWORD _dwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMPluginVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMPlugin * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMPlugin * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMPlugin * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnMediaReceive )( 
            IMPlugin * This,
            /* [in] */ LONGLONG _llCallbackUserData,
            /* [in] */ IUnknown *_pSender,
            /* [in] */ IMFrame *_pFrame,
            /* [out] */ IMFrame **_ppFrameRes);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnMediaEnd )( 
            IMPlugin * This,
            /* [in] */ LONGLONG _llCallbackUserData,
            /* [in] */ IUnknown *_pSender,
            /* [in] */ DWORD _dwFlags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnMediaFlush )( 
            IMPlugin * This,
            /* [in] */ LONGLONG _llCallbackUserData,
            /* [in] */ IUnknown *_pSender,
            /* [in] */ DWORD _dwFlags);
        
        END_INTERFACE
    } IMPluginVtbl;

    interface IMPlugin
    {
        CONST_VTBL struct IMPluginVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMPlugin_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMPlugin_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMPlugin_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMPlugin_OnMediaReceive(This,_llCallbackUserData,_pSender,_pFrame,_ppFrameRes)	\
    ( (This)->lpVtbl -> OnMediaReceive(This,_llCallbackUserData,_pSender,_pFrame,_ppFrameRes) ) 

#define IMPlugin_OnMediaEnd(This,_llCallbackUserData,_pSender,_dwFlags)	\
    ( (This)->lpVtbl -> OnMediaEnd(This,_llCallbackUserData,_pSender,_dwFlags) ) 

#define IMPlugin_OnMediaFlush(This,_llCallbackUserData,_pSender,_dwFlags)	\
    ( (This)->lpVtbl -> OnMediaFlush(This,_llCallbackUserData,_pSender,_dwFlags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMPlugin_INTERFACE_DEFINED__ */


#ifndef __IMElement_INTERFACE_DEFINED__
#define __IMElement_INTERFACE_DEFINED__

/* interface IMElement */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("082DA299-EEC4-4EF1-841E-3A280E7D0383")
    IMElement : public IMAttributes
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ElementParentGet( 
            /* [out] */ IMElement **_ppParent) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ElementParentSet( 
            /* [in] */ IMElement *_pParent) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ElementBoolSet( 
            /* [in] */ BSTR _bsAttributeName,
            /* [in] */ BOOL _bValue,
            /* [in] */ double _dblTimeForChange) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ElementDoubleSet( 
            /* [in] */ BSTR _bsAttributeName,
            /* [in] */ double _dblValue,
            /* [in] */ double _dblTimeForChange) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ElementStringSet( 
            /* [in] */ BSTR _bsAttributeName,
            /* [in] */ BSTR _bsValue,
            /* [in] */ double _dblTimeForChange) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ElementMultipleSet( 
            /* [in] */ BSTR _bsAttributesList,
            /* [in] */ double _dblTimeForChange) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ElementSet( 
            /* [in] */ BSTR _bsElementType,
            /* [in] */ BSTR _bsXMLDescription,
            /* [in] */ double _dblTimeForChange) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ElementMediaSet( 
            /* [in] */ IUnknown *_pExternOrRef,
            /* [in] */ BSTR _bsPath,
            /* [in] */ BSTR _bsParam,
            /* [in] */ double _dblTimeForChange) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ElementTypeGet( 
            /* [out] */ BSTR *_pbsElementType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ElementGet( 
            /* [out] */ BSTR *_pbsElementType,
            /* [out] */ BSTR *_pbsXMLDescription) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ElementReorder( 
            /* [in] */ int _nAddIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ElementInvoke( 
            /* [in] */ BSTR _bsCommand,
            /* [in] */ BSTR _bsParam,
            /* [in] */ double _dblTimeForChange) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ElementDetach( 
            /* [in] */ double _dblTimeForChange) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ElementAbsolutePosGet( 
            /* [out] */ double *_pdblXPos,
            /* [out] */ double *_pdblYPos,
            /* [out] */ double *_pdblWidth,
            /* [out] */ double *_pdblHeight) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ElementAbsolutePosSet( 
            /* [in] */ double _dblXPos,
            /* [in] */ double _dblYPos,
            /* [in] */ double _dblWidth,
            /* [in] */ double _dblHeight) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ElementInfoGet( 
            /* [in] */ BSTR _bsInfoType,
            /* [out] */ BSTR *_pbsDecription) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMElement * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMElement * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMElement * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesGetCount )( 
            IMElement * This,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesGetByIndex )( 
            IMElement * This,
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsName,
            /* [out] */ BSTR *_pbsValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesRemove )( 
            IMElement * This,
            /* [in] */ BSTR _bsName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesRemoveAll )( 
            IMElement * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesStringSet )( 
            IMElement * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ BSTR _bsValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesBoolSet )( 
            IMElement * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ BOOL _bValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesIntSet )( 
            IMElement * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ int _nValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesDoubleSet )( 
            IMElement * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ double _dblValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesHave )( 
            IMElement * This,
            /* [in] */ BSTR _bsName,
            /* [out] */ BOOL *_pbHave,
            /* [out] */ BSTR *_pbsValueOrDefault);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesStringGet )( 
            IMElement * This,
            /* [in] */ BSTR _bsName,
            /* [out] */ BSTR *_pbsValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesIntGet )( 
            IMElement * This,
            /* [in] */ BSTR _bsName,
            /* [out] */ int *_pnValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesBoolGet )( 
            IMElement * This,
            /* [in] */ BSTR _bsName,
            /* [out] */ BOOL *_pbValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesDoubleGet )( 
            IMElement * This,
            /* [in] */ BSTR _bsName,
            /* [out] */ double *_pdblValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesMultipleSet )( 
            IMElement * This,
            /* [in] */ BSTR _bsAttributesList,
            /* [in] */ eMUpdateType _eUpdateType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesSave )( 
            IMElement * This,
            /* [out] */ BSTR *_pbsAttributesList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesClone )( 
            IMElement * This,
            /* [out] */ IMAttributes **_ppClone);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesSet )( 
            IMElement * This,
            /* [in] */ IMAttributes *_pAttributesList,
            /* [in] */ eMUpdateType _eUpdateType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesInfoGetCount )( 
            IMElement * This,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesInfoGetByIndex )( 
            IMElement * This,
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesInfoGet )( 
            IMElement * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ eMInfoType _eType,
            /* [out] */ BSTR *_pbsInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesValuesInfoGet )( 
            IMElement * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ BSTR _bsValue,
            /* [in] */ BSTR _bsType,
            /* [out] */ BSTR *_pbsInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ElementParentGet )( 
            IMElement * This,
            /* [out] */ IMElement **_ppParent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ElementParentSet )( 
            IMElement * This,
            /* [in] */ IMElement *_pParent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ElementBoolSet )( 
            IMElement * This,
            /* [in] */ BSTR _bsAttributeName,
            /* [in] */ BOOL _bValue,
            /* [in] */ double _dblTimeForChange);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ElementDoubleSet )( 
            IMElement * This,
            /* [in] */ BSTR _bsAttributeName,
            /* [in] */ double _dblValue,
            /* [in] */ double _dblTimeForChange);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ElementStringSet )( 
            IMElement * This,
            /* [in] */ BSTR _bsAttributeName,
            /* [in] */ BSTR _bsValue,
            /* [in] */ double _dblTimeForChange);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ElementMultipleSet )( 
            IMElement * This,
            /* [in] */ BSTR _bsAttributesList,
            /* [in] */ double _dblTimeForChange);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ElementSet )( 
            IMElement * This,
            /* [in] */ BSTR _bsElementType,
            /* [in] */ BSTR _bsXMLDescription,
            /* [in] */ double _dblTimeForChange);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ElementMediaSet )( 
            IMElement * This,
            /* [in] */ IUnknown *_pExternOrRef,
            /* [in] */ BSTR _bsPath,
            /* [in] */ BSTR _bsParam,
            /* [in] */ double _dblTimeForChange);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ElementTypeGet )( 
            IMElement * This,
            /* [out] */ BSTR *_pbsElementType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ElementGet )( 
            IMElement * This,
            /* [out] */ BSTR *_pbsElementType,
            /* [out] */ BSTR *_pbsXMLDescription);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ElementReorder )( 
            IMElement * This,
            /* [in] */ int _nAddIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ElementInvoke )( 
            IMElement * This,
            /* [in] */ BSTR _bsCommand,
            /* [in] */ BSTR _bsParam,
            /* [in] */ double _dblTimeForChange);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ElementDetach )( 
            IMElement * This,
            /* [in] */ double _dblTimeForChange);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ElementAbsolutePosGet )( 
            IMElement * This,
            /* [out] */ double *_pdblXPos,
            /* [out] */ double *_pdblYPos,
            /* [out] */ double *_pdblWidth,
            /* [out] */ double *_pdblHeight);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ElementAbsolutePosSet )( 
            IMElement * This,
            /* [in] */ double _dblXPos,
            /* [in] */ double _dblYPos,
            /* [in] */ double _dblWidth,
            /* [in] */ double _dblHeight);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ElementInfoGet )( 
            IMElement * This,
            /* [in] */ BSTR _bsInfoType,
            /* [out] */ BSTR *_pbsDecription);
        
        END_INTERFACE
    } IMElementVtbl;

    interface IMElement
    {
        CONST_VTBL struct IMElementVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMElement_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMElement_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMElement_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMElement_AttributesGetCount(This,_pnCount)	\
    ( (This)->lpVtbl -> AttributesGetCount(This,_pnCount) ) 

#define IMElement_AttributesGetByIndex(This,_nIndex,_pbsName,_pbsValue)	\
    ( (This)->lpVtbl -> AttributesGetByIndex(This,_nIndex,_pbsName,_pbsValue) ) 

#define IMElement_AttributesRemove(This,_bsName)	\
    ( (This)->lpVtbl -> AttributesRemove(This,_bsName) ) 

#define IMElement_AttributesRemoveAll(This)	\
    ( (This)->lpVtbl -> AttributesRemoveAll(This) ) 

#define IMElement_AttributesStringSet(This,_bsName,_bsValue)	\
    ( (This)->lpVtbl -> AttributesStringSet(This,_bsName,_bsValue) ) 

#define IMElement_AttributesBoolSet(This,_bsName,_bValue)	\
    ( (This)->lpVtbl -> AttributesBoolSet(This,_bsName,_bValue) ) 

#define IMElement_AttributesIntSet(This,_bsName,_nValue)	\
    ( (This)->lpVtbl -> AttributesIntSet(This,_bsName,_nValue) ) 

#define IMElement_AttributesDoubleSet(This,_bsName,_dblValue)	\
    ( (This)->lpVtbl -> AttributesDoubleSet(This,_bsName,_dblValue) ) 

#define IMElement_AttributesHave(This,_bsName,_pbHave,_pbsValueOrDefault)	\
    ( (This)->lpVtbl -> AttributesHave(This,_bsName,_pbHave,_pbsValueOrDefault) ) 

#define IMElement_AttributesStringGet(This,_bsName,_pbsValue)	\
    ( (This)->lpVtbl -> AttributesStringGet(This,_bsName,_pbsValue) ) 

#define IMElement_AttributesIntGet(This,_bsName,_pnValue)	\
    ( (This)->lpVtbl -> AttributesIntGet(This,_bsName,_pnValue) ) 

#define IMElement_AttributesBoolGet(This,_bsName,_pbValue)	\
    ( (This)->lpVtbl -> AttributesBoolGet(This,_bsName,_pbValue) ) 

#define IMElement_AttributesDoubleGet(This,_bsName,_pdblValue)	\
    ( (This)->lpVtbl -> AttributesDoubleGet(This,_bsName,_pdblValue) ) 

#define IMElement_AttributesMultipleSet(This,_bsAttributesList,_eUpdateType)	\
    ( (This)->lpVtbl -> AttributesMultipleSet(This,_bsAttributesList,_eUpdateType) ) 

#define IMElement_AttributesSave(This,_pbsAttributesList)	\
    ( (This)->lpVtbl -> AttributesSave(This,_pbsAttributesList) ) 

#define IMElement_AttributesClone(This,_ppClone)	\
    ( (This)->lpVtbl -> AttributesClone(This,_ppClone) ) 

#define IMElement_AttributesSet(This,_pAttributesList,_eUpdateType)	\
    ( (This)->lpVtbl -> AttributesSet(This,_pAttributesList,_eUpdateType) ) 

#define IMElement_AttributesInfoGetCount(This,_pnCount)	\
    ( (This)->lpVtbl -> AttributesInfoGetCount(This,_pnCount) ) 

#define IMElement_AttributesInfoGetByIndex(This,_nIndex,_pbsName)	\
    ( (This)->lpVtbl -> AttributesInfoGetByIndex(This,_nIndex,_pbsName) ) 

#define IMElement_AttributesInfoGet(This,_bsName,_eType,_pbsInfo)	\
    ( (This)->lpVtbl -> AttributesInfoGet(This,_bsName,_eType,_pbsInfo) ) 

#define IMElement_AttributesValuesInfoGet(This,_bsName,_bsValue,_bsType,_pbsInfo)	\
    ( (This)->lpVtbl -> AttributesValuesInfoGet(This,_bsName,_bsValue,_bsType,_pbsInfo) ) 


#define IMElement_ElementParentGet(This,_ppParent)	\
    ( (This)->lpVtbl -> ElementParentGet(This,_ppParent) ) 

#define IMElement_ElementParentSet(This,_pParent)	\
    ( (This)->lpVtbl -> ElementParentSet(This,_pParent) ) 

#define IMElement_ElementBoolSet(This,_bsAttributeName,_bValue,_dblTimeForChange)	\
    ( (This)->lpVtbl -> ElementBoolSet(This,_bsAttributeName,_bValue,_dblTimeForChange) ) 

#define IMElement_ElementDoubleSet(This,_bsAttributeName,_dblValue,_dblTimeForChange)	\
    ( (This)->lpVtbl -> ElementDoubleSet(This,_bsAttributeName,_dblValue,_dblTimeForChange) ) 

#define IMElement_ElementStringSet(This,_bsAttributeName,_bsValue,_dblTimeForChange)	\
    ( (This)->lpVtbl -> ElementStringSet(This,_bsAttributeName,_bsValue,_dblTimeForChange) ) 

#define IMElement_ElementMultipleSet(This,_bsAttributesList,_dblTimeForChange)	\
    ( (This)->lpVtbl -> ElementMultipleSet(This,_bsAttributesList,_dblTimeForChange) ) 

#define IMElement_ElementSet(This,_bsElementType,_bsXMLDescription,_dblTimeForChange)	\
    ( (This)->lpVtbl -> ElementSet(This,_bsElementType,_bsXMLDescription,_dblTimeForChange) ) 

#define IMElement_ElementMediaSet(This,_pExternOrRef,_bsPath,_bsParam,_dblTimeForChange)	\
    ( (This)->lpVtbl -> ElementMediaSet(This,_pExternOrRef,_bsPath,_bsParam,_dblTimeForChange) ) 

#define IMElement_ElementTypeGet(This,_pbsElementType)	\
    ( (This)->lpVtbl -> ElementTypeGet(This,_pbsElementType) ) 

#define IMElement_ElementGet(This,_pbsElementType,_pbsXMLDescription)	\
    ( (This)->lpVtbl -> ElementGet(This,_pbsElementType,_pbsXMLDescription) ) 

#define IMElement_ElementReorder(This,_nAddIndex)	\
    ( (This)->lpVtbl -> ElementReorder(This,_nAddIndex) ) 

#define IMElement_ElementInvoke(This,_bsCommand,_bsParam,_dblTimeForChange)	\
    ( (This)->lpVtbl -> ElementInvoke(This,_bsCommand,_bsParam,_dblTimeForChange) ) 

#define IMElement_ElementDetach(This,_dblTimeForChange)	\
    ( (This)->lpVtbl -> ElementDetach(This,_dblTimeForChange) ) 

#define IMElement_ElementAbsolutePosGet(This,_pdblXPos,_pdblYPos,_pdblWidth,_pdblHeight)	\
    ( (This)->lpVtbl -> ElementAbsolutePosGet(This,_pdblXPos,_pdblYPos,_pdblWidth,_pdblHeight) ) 

#define IMElement_ElementAbsolutePosSet(This,_dblXPos,_dblYPos,_dblWidth,_dblHeight)	\
    ( (This)->lpVtbl -> ElementAbsolutePosSet(This,_dblXPos,_dblYPos,_dblWidth,_dblHeight) ) 

#define IMElement_ElementInfoGet(This,_bsInfoType,_pbsDecription)	\
    ( (This)->lpVtbl -> ElementInfoGet(This,_bsInfoType,_pbsDecription) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMElement_INTERFACE_DEFINED__ */


#ifndef __IMElements_INTERFACE_DEFINED__
#define __IMElements_INTERFACE_DEFINED__

/* interface IMElements */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMElements;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("082DA298-EEC4-4EF1-841E-3A280E7D0383")
    IMElements : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ElementsGetCount( 
            /* [out] */ int *_pnCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ElementsGetByIndex( 
            /* [in] */ int _nIndex,
            /* [out] */ IMElement **_ppChildElement) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ElementsGetByID( 
            /* [in] */ BSTR _bsElementID,
            /* [out] */ IMElement **_ppChildElement) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ElementsAdd( 
            /* [in] */ BSTR _bsNewElementID,
            /* [in] */ BSTR _bsElementType,
            /* [in] */ BSTR _bsElementProps,
            /* [out] */ IMElement **_ppChildElement,
            /* [in] */ double _dblTimeForChange) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ElementsMediaAdd( 
            /* [in] */ BSTR _bsNewElementID,
            /* [in] */ IUnknown *_pExternOrRef,
            /* [in] */ BSTR _bsPath,
            /* [in] */ BSTR _bsParam,
            /* [out] */ IMElement **_ppChildElement,
            /* [in] */ double _dblTimeForChange) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMElementsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMElements * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMElements * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMElements * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ElementsGetCount )( 
            IMElements * This,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ElementsGetByIndex )( 
            IMElements * This,
            /* [in] */ int _nIndex,
            /* [out] */ IMElement **_ppChildElement);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ElementsGetByID )( 
            IMElements * This,
            /* [in] */ BSTR _bsElementID,
            /* [out] */ IMElement **_ppChildElement);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ElementsAdd )( 
            IMElements * This,
            /* [in] */ BSTR _bsNewElementID,
            /* [in] */ BSTR _bsElementType,
            /* [in] */ BSTR _bsElementProps,
            /* [out] */ IMElement **_ppChildElement,
            /* [in] */ double _dblTimeForChange);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ElementsMediaAdd )( 
            IMElements * This,
            /* [in] */ BSTR _bsNewElementID,
            /* [in] */ IUnknown *_pExternOrRef,
            /* [in] */ BSTR _bsPath,
            /* [in] */ BSTR _bsParam,
            /* [out] */ IMElement **_ppChildElement,
            /* [in] */ double _dblTimeForChange);
        
        END_INTERFACE
    } IMElementsVtbl;

    interface IMElements
    {
        CONST_VTBL struct IMElementsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMElements_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMElements_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMElements_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMElements_ElementsGetCount(This,_pnCount)	\
    ( (This)->lpVtbl -> ElementsGetCount(This,_pnCount) ) 

#define IMElements_ElementsGetByIndex(This,_nIndex,_ppChildElement)	\
    ( (This)->lpVtbl -> ElementsGetByIndex(This,_nIndex,_ppChildElement) ) 

#define IMElements_ElementsGetByID(This,_bsElementID,_ppChildElement)	\
    ( (This)->lpVtbl -> ElementsGetByID(This,_bsElementID,_ppChildElement) ) 

#define IMElements_ElementsAdd(This,_bsNewElementID,_bsElementType,_bsElementProps,_ppChildElement,_dblTimeForChange)	\
    ( (This)->lpVtbl -> ElementsAdd(This,_bsNewElementID,_bsElementType,_bsElementProps,_ppChildElement,_dblTimeForChange) ) 

#define IMElements_ElementsMediaAdd(This,_bsNewElementID,_pExternOrRef,_bsPath,_bsParam,_ppChildElement,_dblTimeForChange)	\
    ( (This)->lpVtbl -> ElementsMediaAdd(This,_bsNewElementID,_pExternOrRef,_bsPath,_bsParam,_ppChildElement,_dblTimeForChange) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMElements_INTERFACE_DEFINED__ */


#ifndef __IMScenes_INTERFACE_DEFINED__
#define __IMScenes_INTERFACE_DEFINED__

/* interface IMScenes */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMScenes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("082DA302-EEC4-4EF1-841E-3A280E7D0383")
    IMScenes : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ScenesGetCount( 
            /* [out] */ int *_pnCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ScenesGetByIndex( 
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsSceneID,
            /* [out] */ IMElements **_ppScene) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ScenesGet( 
            /* [in] */ BSTR _bsSceneID,
            /* [out] */ IMElements **_ppScene) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ScenesAdd( 
            /* [in] */ BSTR _bsXMLDescOrPathName,
            /* [out][in] */ BSTR *_pbsSceneID,
            /* [out] */ IMElements **_ppScene) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ScenesRemove( 
            /* [in] */ BSTR _bsSceneID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ScenesActiveGet( 
            /* [out] */ BSTR *_pbsSceneID,
            /* [out] */ int *_pnIndex,
            /* [out] */ IMElements **_ppScene) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ScenesActiveSet( 
            /* [in] */ BSTR _bsSceneID,
            /* [in] */ BSTR _bsParameters) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ScenesElementGetByPos( 
            /* [in] */ double _dblPosX,
            /* [in] */ double _dblPosY,
            /* [in] */ BOOL _bHiddenReturn,
            /* [out] */ IMElement **_ppElement) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMScenesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMScenes * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMScenes * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMScenes * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ScenesGetCount )( 
            IMScenes * This,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ScenesGetByIndex )( 
            IMScenes * This,
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsSceneID,
            /* [out] */ IMElements **_ppScene);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ScenesGet )( 
            IMScenes * This,
            /* [in] */ BSTR _bsSceneID,
            /* [out] */ IMElements **_ppScene);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ScenesAdd )( 
            IMScenes * This,
            /* [in] */ BSTR _bsXMLDescOrPathName,
            /* [out][in] */ BSTR *_pbsSceneID,
            /* [out] */ IMElements **_ppScene);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ScenesRemove )( 
            IMScenes * This,
            /* [in] */ BSTR _bsSceneID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ScenesActiveGet )( 
            IMScenes * This,
            /* [out] */ BSTR *_pbsSceneID,
            /* [out] */ int *_pnIndex,
            /* [out] */ IMElements **_ppScene);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ScenesActiveSet )( 
            IMScenes * This,
            /* [in] */ BSTR _bsSceneID,
            /* [in] */ BSTR _bsParameters);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ScenesElementGetByPos )( 
            IMScenes * This,
            /* [in] */ double _dblPosX,
            /* [in] */ double _dblPosY,
            /* [in] */ BOOL _bHiddenReturn,
            /* [out] */ IMElement **_ppElement);
        
        END_INTERFACE
    } IMScenesVtbl;

    interface IMScenes
    {
        CONST_VTBL struct IMScenesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMScenes_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMScenes_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMScenes_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMScenes_ScenesGetCount(This,_pnCount)	\
    ( (This)->lpVtbl -> ScenesGetCount(This,_pnCount) ) 

#define IMScenes_ScenesGetByIndex(This,_nIndex,_pbsSceneID,_ppScene)	\
    ( (This)->lpVtbl -> ScenesGetByIndex(This,_nIndex,_pbsSceneID,_ppScene) ) 

#define IMScenes_ScenesGet(This,_bsSceneID,_ppScene)	\
    ( (This)->lpVtbl -> ScenesGet(This,_bsSceneID,_ppScene) ) 

#define IMScenes_ScenesAdd(This,_bsXMLDescOrPathName,_pbsSceneID,_ppScene)	\
    ( (This)->lpVtbl -> ScenesAdd(This,_bsXMLDescOrPathName,_pbsSceneID,_ppScene) ) 

#define IMScenes_ScenesRemove(This,_bsSceneID)	\
    ( (This)->lpVtbl -> ScenesRemove(This,_bsSceneID) ) 

#define IMScenes_ScenesActiveGet(This,_pbsSceneID,_pnIndex,_ppScene)	\
    ( (This)->lpVtbl -> ScenesActiveGet(This,_pbsSceneID,_pnIndex,_ppScene) ) 

#define IMScenes_ScenesActiveSet(This,_bsSceneID,_bsParameters)	\
    ( (This)->lpVtbl -> ScenesActiveSet(This,_bsSceneID,_bsParameters) ) 

#define IMScenes_ScenesElementGetByPos(This,_dblPosX,_dblPosY,_bHiddenReturn,_ppElement)	\
    ( (This)->lpVtbl -> ScenesElementGetByPos(This,_dblPosX,_dblPosY,_bHiddenReturn,_ppElement) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMScenes_INTERFACE_DEFINED__ */


#ifndef __IMStreams_INTERFACE_DEFINED__
#define __IMStreams_INTERFACE_DEFINED__

/* interface IMStreams */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMStreams;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("69429619-9BC2-45D9-AFE9-F42F18C38CBF")
    IMStreams : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StreamsGetCount( 
            /* [out] */ int *_pnCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StreamsGetByIndex( 
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsStreamID,
            /* [out] */ IMItem **_ppStream) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StreamsGet( 
            /* [in] */ BSTR _bsStreamID,
            /* [out] */ int *_pnIndex,
            /* [out] */ IMItem **_ppStream) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StreamsAdd( 
            /* [in] */ BSTR _bsStreamID,
            /* [in] */ IUnknown *_pExternOrRef,
            /* [in] */ BSTR _bsPath,
            /* [in] */ BSTR _bsParam,
            /* [out] */ IMItem **_ppItem,
            /* [in] */ double _dblTimeForChange) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StreamsRemove( 
            /* [in] */ IMItem *_pStream,
            /* [in] */ double _dblTimeForChange) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StreamsRemoveByIndex( 
            /* [in] */ int _nIndex,
            /* [in] */ int _nExtraRemove,
            /* [in] */ double _dblTimeForChange) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StreamsReorder( 
            /* [in] */ IMItem *_pStream,
            /* [in] */ int _nIndexAdd,
            /* [in] */ double _dblTimeForChange) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StreamsBackgroundSet( 
            /* [in] */ IUnknown *_pExternOrRef,
            /* [in] */ BSTR _bsPath,
            /* [in] */ BSTR _bsParam,
            /* [out] */ IMItem **_ppItemsItem,
            /* [in] */ double _dblTimeForChange) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE StreamsBackgroundGet( 
            /* [out] */ BSTR *_pbsPath,
            /* [out] */ IMItem **_ppItemsItem) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMStreamsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMStreams * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMStreams * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMStreams * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StreamsGetCount )( 
            IMStreams * This,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StreamsGetByIndex )( 
            IMStreams * This,
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsStreamID,
            /* [out] */ IMItem **_ppStream);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StreamsGet )( 
            IMStreams * This,
            /* [in] */ BSTR _bsStreamID,
            /* [out] */ int *_pnIndex,
            /* [out] */ IMItem **_ppStream);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StreamsAdd )( 
            IMStreams * This,
            /* [in] */ BSTR _bsStreamID,
            /* [in] */ IUnknown *_pExternOrRef,
            /* [in] */ BSTR _bsPath,
            /* [in] */ BSTR _bsParam,
            /* [out] */ IMItem **_ppItem,
            /* [in] */ double _dblTimeForChange);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StreamsRemove )( 
            IMStreams * This,
            /* [in] */ IMItem *_pStream,
            /* [in] */ double _dblTimeForChange);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StreamsRemoveByIndex )( 
            IMStreams * This,
            /* [in] */ int _nIndex,
            /* [in] */ int _nExtraRemove,
            /* [in] */ double _dblTimeForChange);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StreamsReorder )( 
            IMStreams * This,
            /* [in] */ IMItem *_pStream,
            /* [in] */ int _nIndexAdd,
            /* [in] */ double _dblTimeForChange);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StreamsBackgroundSet )( 
            IMStreams * This,
            /* [in] */ IUnknown *_pExternOrRef,
            /* [in] */ BSTR _bsPath,
            /* [in] */ BSTR _bsParam,
            /* [out] */ IMItem **_ppItemsItem,
            /* [in] */ double _dblTimeForChange);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *StreamsBackgroundGet )( 
            IMStreams * This,
            /* [out] */ BSTR *_pbsPath,
            /* [out] */ IMItem **_ppItemsItem);
        
        END_INTERFACE
    } IMStreamsVtbl;

    interface IMStreams
    {
        CONST_VTBL struct IMStreamsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMStreams_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMStreams_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMStreams_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMStreams_StreamsGetCount(This,_pnCount)	\
    ( (This)->lpVtbl -> StreamsGetCount(This,_pnCount) ) 

#define IMStreams_StreamsGetByIndex(This,_nIndex,_pbsStreamID,_ppStream)	\
    ( (This)->lpVtbl -> StreamsGetByIndex(This,_nIndex,_pbsStreamID,_ppStream) ) 

#define IMStreams_StreamsGet(This,_bsStreamID,_pnIndex,_ppStream)	\
    ( (This)->lpVtbl -> StreamsGet(This,_bsStreamID,_pnIndex,_ppStream) ) 

#define IMStreams_StreamsAdd(This,_bsStreamID,_pExternOrRef,_bsPath,_bsParam,_ppItem,_dblTimeForChange)	\
    ( (This)->lpVtbl -> StreamsAdd(This,_bsStreamID,_pExternOrRef,_bsPath,_bsParam,_ppItem,_dblTimeForChange) ) 

#define IMStreams_StreamsRemove(This,_pStream,_dblTimeForChange)	\
    ( (This)->lpVtbl -> StreamsRemove(This,_pStream,_dblTimeForChange) ) 

#define IMStreams_StreamsRemoveByIndex(This,_nIndex,_nExtraRemove,_dblTimeForChange)	\
    ( (This)->lpVtbl -> StreamsRemoveByIndex(This,_nIndex,_nExtraRemove,_dblTimeForChange) ) 

#define IMStreams_StreamsReorder(This,_pStream,_nIndexAdd,_dblTimeForChange)	\
    ( (This)->lpVtbl -> StreamsReorder(This,_pStream,_nIndexAdd,_dblTimeForChange) ) 

#define IMStreams_StreamsBackgroundSet(This,_pExternOrRef,_bsPath,_bsParam,_ppItemsItem,_dblTimeForChange)	\
    ( (This)->lpVtbl -> StreamsBackgroundSet(This,_pExternOrRef,_bsPath,_bsParam,_ppItemsItem,_dblTimeForChange) ) 

#define IMStreams_StreamsBackgroundGet(This,_pbsPath,_ppItemsItem)	\
    ( (This)->lpVtbl -> StreamsBackgroundGet(This,_pbsPath,_ppItemsItem) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMStreams_INTERFACE_DEFINED__ */


#ifndef __IMWriter_INTERFACE_DEFINED__
#define __IMWriter_INTERFACE_DEFINED__

/* interface IMWriter */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMWriter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("082DA400-EEC4-4EF1-841E-3A280E7D0383")
    IMWriter : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE WriterNameSet( 
            /* [in] */ BSTR _bsName,
            /* [in] */ BSTR _bsProps) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE WriterNameGet( 
            /* [out] */ BSTR *_pbsName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE WriterSkip( 
            /* [in] */ double _dblSkipTime) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMWriterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMWriter * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMWriter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMWriter * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *WriterNameSet )( 
            IMWriter * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ BSTR _bsProps);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *WriterNameGet )( 
            IMWriter * This,
            /* [out] */ BSTR *_pbsName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *WriterSkip )( 
            IMWriter * This,
            /* [in] */ double _dblSkipTime);
        
        END_INTERFACE
    } IMWriterVtbl;

    interface IMWriter
    {
        CONST_VTBL struct IMWriterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMWriter_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMWriter_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMWriter_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMWriter_WriterNameSet(This,_bsName,_bsProps)	\
    ( (This)->lpVtbl -> WriterNameSet(This,_bsName,_bsProps) ) 

#define IMWriter_WriterNameGet(This,_pbsName)	\
    ( (This)->lpVtbl -> WriterNameGet(This,_pbsName) ) 

#define IMWriter_WriterSkip(This,_dblSkipTime)	\
    ( (This)->lpVtbl -> WriterSkip(This,_dblSkipTime) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMWriter_INTERFACE_DEFINED__ */


#ifndef __IMDeckControl_INTERFACE_DEFINED__
#define __IMDeckControl_INTERFACE_DEFINED__

/* interface IMDeckControl */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMDeckControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7F366131-473F-4ad5-A5C2-428FE0C8E03E")
    IMDeckControl : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckOpen( 
            /* [in] */ BOOL _bTimecodeIsDropFrame,
            /* [out] */ eMBMDDeckControlError *_pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckClose( 
            /* [in] */ BOOL _bStandbyOn) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckGetCurrentState( 
            /* [out] */ eMBMDDeckControlMode *_pMode,
            /* [out] */ eMBMDDeckControlVTRControlState *_pVtrControlState,
            /* [out] */ long *_pFlags) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckSetStandby( 
            /* [in] */ BOOL _bStandbyOn) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckSendCommand( 
            /* [in] */ long _lInBufferSize,
            /* [in] */ LONGLONG _pInBuffer,
            /* [out] */ long *_pOutDataSize,
            /* [in] */ LONGLONG _ppOutBuffer,
            /* [in] */ long outBufferSize,
            /* [out] */ eMBMDDeckControlError *_pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckSendCommand_I( 
            /* [in] */ long _lInBufferSize,
            /* [size_is][in] */ BYTE *_pInBuffer,
            /* [out] */ long *_pOutDataSize,
            /* [size_is][size_is][out] */ BYTE **_ppOutBuffer,
            /* [in] */ long outBufferSize,
            /* [out] */ eMBMDDeckControlError *_pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckPlay( 
            /* [out] */ eMBMDDeckControlError *_pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckStop( 
            /* [out] */ eMBMDDeckControlError *_pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckTogglePlayStop( 
            /* [out] */ eMBMDDeckControlError *_pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckEject( 
            /* [out] */ eMBMDDeckControlError *_pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckGoToTimecode( 
            /* [in] */ M_TIMECODE _timecode,
            /* [out] */ eMBMDDeckControlError *_pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckFastForward( 
            /* [in] */ BOOL _bViewTape,
            /* [out] */ eMBMDDeckControlError *_pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckRewind( 
            /* [in] */ BOOL _bViewTape,
            /* [out] */ eMBMDDeckControlError *_pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckStepForward( 
            /* [out] */ eMBMDDeckControlError *_pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckStepBack( 
            /* [out] */ eMBMDDeckControlError *_pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckJog( 
            /* [in] */ double _dblRate,
            /* [out] */ eMBMDDeckControlError *_pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckShuttle( 
            /* [in] */ double _dblRate,
            /* [out] */ eMBMDDeckControlError *_pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckGetTimecodeString( 
            /* [out] */ BSTR *_pCurrentTimeCode,
            /* [out] */ eMBMDDeckControlError *_pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckGetTimecode( 
            /* [out] */ M_TIMECODE *_pCurrentTimeCode,
            /* [out] */ eMBMDDeckControlError *_pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckSetPreroll( 
            /* [in] */ long _lPrerollSeconds) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckGetPreroll( 
            /* [out] */ long *_pPrerollSeconds) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckSetCaptureOffset( 
            /* [in] */ long _lCaptureOffsetFields) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckGetCaptureOffset( 
            /* [out] */ long *_pCaptureOffsetFields) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckSetExportOffset( 
            /* [in] */ long _lExportOffsetFields) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckGetExportOffset( 
            /* [out] */ long *_pExportOffsetFields) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckGetManualExportOffset( 
            /* [out] */ long *_pDeckManualExportOffsetFields) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckStartExport( 
            /* [in] */ long _lInTimecode,
            /* [in] */ long _lOutTimecode,
            /* [in] */ long _lExportModeOps,
            /* [out] */ eMBMDDeckControlError *_pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckStartCapture( 
            /* [in] */ BOOL _bUseVITC,
            /* [in] */ long _lInTimecode,
            /* [in] */ long _lOutTimecode,
            /* [out] */ eMBMDDeckControlError *_pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckGetDeviceID( 
            /* [out] */ long *_pDeviceId,
            /* [out] */ eMBMDDeckControlError *_pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckAbort( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckCrashRecordStart( 
            /* [out] */ eMBMDDeckControlError *_pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeckCrashRecordStop( 
            /* [out] */ eMBMDDeckControlError *_pError) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMDeckControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMDeckControl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMDeckControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMDeckControl * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckOpen )( 
            IMDeckControl * This,
            /* [in] */ BOOL _bTimecodeIsDropFrame,
            /* [out] */ eMBMDDeckControlError *_pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckClose )( 
            IMDeckControl * This,
            /* [in] */ BOOL _bStandbyOn);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckGetCurrentState )( 
            IMDeckControl * This,
            /* [out] */ eMBMDDeckControlMode *_pMode,
            /* [out] */ eMBMDDeckControlVTRControlState *_pVtrControlState,
            /* [out] */ long *_pFlags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckSetStandby )( 
            IMDeckControl * This,
            /* [in] */ BOOL _bStandbyOn);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckSendCommand )( 
            IMDeckControl * This,
            /* [in] */ long _lInBufferSize,
            /* [in] */ LONGLONG _pInBuffer,
            /* [out] */ long *_pOutDataSize,
            /* [in] */ LONGLONG _ppOutBuffer,
            /* [in] */ long outBufferSize,
            /* [out] */ eMBMDDeckControlError *_pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckSendCommand_I )( 
            IMDeckControl * This,
            /* [in] */ long _lInBufferSize,
            /* [size_is][in] */ BYTE *_pInBuffer,
            /* [out] */ long *_pOutDataSize,
            /* [size_is][size_is][out] */ BYTE **_ppOutBuffer,
            /* [in] */ long outBufferSize,
            /* [out] */ eMBMDDeckControlError *_pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckPlay )( 
            IMDeckControl * This,
            /* [out] */ eMBMDDeckControlError *_pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckStop )( 
            IMDeckControl * This,
            /* [out] */ eMBMDDeckControlError *_pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckTogglePlayStop )( 
            IMDeckControl * This,
            /* [out] */ eMBMDDeckControlError *_pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckEject )( 
            IMDeckControl * This,
            /* [out] */ eMBMDDeckControlError *_pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckGoToTimecode )( 
            IMDeckControl * This,
            /* [in] */ M_TIMECODE _timecode,
            /* [out] */ eMBMDDeckControlError *_pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckFastForward )( 
            IMDeckControl * This,
            /* [in] */ BOOL _bViewTape,
            /* [out] */ eMBMDDeckControlError *_pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckRewind )( 
            IMDeckControl * This,
            /* [in] */ BOOL _bViewTape,
            /* [out] */ eMBMDDeckControlError *_pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckStepForward )( 
            IMDeckControl * This,
            /* [out] */ eMBMDDeckControlError *_pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckStepBack )( 
            IMDeckControl * This,
            /* [out] */ eMBMDDeckControlError *_pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckJog )( 
            IMDeckControl * This,
            /* [in] */ double _dblRate,
            /* [out] */ eMBMDDeckControlError *_pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckShuttle )( 
            IMDeckControl * This,
            /* [in] */ double _dblRate,
            /* [out] */ eMBMDDeckControlError *_pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckGetTimecodeString )( 
            IMDeckControl * This,
            /* [out] */ BSTR *_pCurrentTimeCode,
            /* [out] */ eMBMDDeckControlError *_pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckGetTimecode )( 
            IMDeckControl * This,
            /* [out] */ M_TIMECODE *_pCurrentTimeCode,
            /* [out] */ eMBMDDeckControlError *_pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckSetPreroll )( 
            IMDeckControl * This,
            /* [in] */ long _lPrerollSeconds);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckGetPreroll )( 
            IMDeckControl * This,
            /* [out] */ long *_pPrerollSeconds);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckSetCaptureOffset )( 
            IMDeckControl * This,
            /* [in] */ long _lCaptureOffsetFields);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckGetCaptureOffset )( 
            IMDeckControl * This,
            /* [out] */ long *_pCaptureOffsetFields);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckSetExportOffset )( 
            IMDeckControl * This,
            /* [in] */ long _lExportOffsetFields);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckGetExportOffset )( 
            IMDeckControl * This,
            /* [out] */ long *_pExportOffsetFields);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckGetManualExportOffset )( 
            IMDeckControl * This,
            /* [out] */ long *_pDeckManualExportOffsetFields);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckStartExport )( 
            IMDeckControl * This,
            /* [in] */ long _lInTimecode,
            /* [in] */ long _lOutTimecode,
            /* [in] */ long _lExportModeOps,
            /* [out] */ eMBMDDeckControlError *_pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckStartCapture )( 
            IMDeckControl * This,
            /* [in] */ BOOL _bUseVITC,
            /* [in] */ long _lInTimecode,
            /* [in] */ long _lOutTimecode,
            /* [out] */ eMBMDDeckControlError *_pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckGetDeviceID )( 
            IMDeckControl * This,
            /* [out] */ long *_pDeviceId,
            /* [out] */ eMBMDDeckControlError *_pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckAbort )( 
            IMDeckControl * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckCrashRecordStart )( 
            IMDeckControl * This,
            /* [out] */ eMBMDDeckControlError *_pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeckCrashRecordStop )( 
            IMDeckControl * This,
            /* [out] */ eMBMDDeckControlError *_pError);
        
        END_INTERFACE
    } IMDeckControlVtbl;

    interface IMDeckControl
    {
        CONST_VTBL struct IMDeckControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMDeckControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMDeckControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMDeckControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMDeckControl_DeckOpen(This,_bTimecodeIsDropFrame,_pError)	\
    ( (This)->lpVtbl -> DeckOpen(This,_bTimecodeIsDropFrame,_pError) ) 

#define IMDeckControl_DeckClose(This,_bStandbyOn)	\
    ( (This)->lpVtbl -> DeckClose(This,_bStandbyOn) ) 

#define IMDeckControl_DeckGetCurrentState(This,_pMode,_pVtrControlState,_pFlags)	\
    ( (This)->lpVtbl -> DeckGetCurrentState(This,_pMode,_pVtrControlState,_pFlags) ) 

#define IMDeckControl_DeckSetStandby(This,_bStandbyOn)	\
    ( (This)->lpVtbl -> DeckSetStandby(This,_bStandbyOn) ) 

#define IMDeckControl_DeckSendCommand(This,_lInBufferSize,_pInBuffer,_pOutDataSize,_ppOutBuffer,outBufferSize,_pError)	\
    ( (This)->lpVtbl -> DeckSendCommand(This,_lInBufferSize,_pInBuffer,_pOutDataSize,_ppOutBuffer,outBufferSize,_pError) ) 

#define IMDeckControl_DeckSendCommand_I(This,_lInBufferSize,_pInBuffer,_pOutDataSize,_ppOutBuffer,outBufferSize,_pError)	\
    ( (This)->lpVtbl -> DeckSendCommand_I(This,_lInBufferSize,_pInBuffer,_pOutDataSize,_ppOutBuffer,outBufferSize,_pError) ) 

#define IMDeckControl_DeckPlay(This,_pError)	\
    ( (This)->lpVtbl -> DeckPlay(This,_pError) ) 

#define IMDeckControl_DeckStop(This,_pError)	\
    ( (This)->lpVtbl -> DeckStop(This,_pError) ) 

#define IMDeckControl_DeckTogglePlayStop(This,_pError)	\
    ( (This)->lpVtbl -> DeckTogglePlayStop(This,_pError) ) 

#define IMDeckControl_DeckEject(This,_pError)	\
    ( (This)->lpVtbl -> DeckEject(This,_pError) ) 

#define IMDeckControl_DeckGoToTimecode(This,_timecode,_pError)	\
    ( (This)->lpVtbl -> DeckGoToTimecode(This,_timecode,_pError) ) 

#define IMDeckControl_DeckFastForward(This,_bViewTape,_pError)	\
    ( (This)->lpVtbl -> DeckFastForward(This,_bViewTape,_pError) ) 

#define IMDeckControl_DeckRewind(This,_bViewTape,_pError)	\
    ( (This)->lpVtbl -> DeckRewind(This,_bViewTape,_pError) ) 

#define IMDeckControl_DeckStepForward(This,_pError)	\
    ( (This)->lpVtbl -> DeckStepForward(This,_pError) ) 

#define IMDeckControl_DeckStepBack(This,_pError)	\
    ( (This)->lpVtbl -> DeckStepBack(This,_pError) ) 

#define IMDeckControl_DeckJog(This,_dblRate,_pError)	\
    ( (This)->lpVtbl -> DeckJog(This,_dblRate,_pError) ) 

#define IMDeckControl_DeckShuttle(This,_dblRate,_pError)	\
    ( (This)->lpVtbl -> DeckShuttle(This,_dblRate,_pError) ) 

#define IMDeckControl_DeckGetTimecodeString(This,_pCurrentTimeCode,_pError)	\
    ( (This)->lpVtbl -> DeckGetTimecodeString(This,_pCurrentTimeCode,_pError) ) 

#define IMDeckControl_DeckGetTimecode(This,_pCurrentTimeCode,_pError)	\
    ( (This)->lpVtbl -> DeckGetTimecode(This,_pCurrentTimeCode,_pError) ) 

#define IMDeckControl_DeckSetPreroll(This,_lPrerollSeconds)	\
    ( (This)->lpVtbl -> DeckSetPreroll(This,_lPrerollSeconds) ) 

#define IMDeckControl_DeckGetPreroll(This,_pPrerollSeconds)	\
    ( (This)->lpVtbl -> DeckGetPreroll(This,_pPrerollSeconds) ) 

#define IMDeckControl_DeckSetCaptureOffset(This,_lCaptureOffsetFields)	\
    ( (This)->lpVtbl -> DeckSetCaptureOffset(This,_lCaptureOffsetFields) ) 

#define IMDeckControl_DeckGetCaptureOffset(This,_pCaptureOffsetFields)	\
    ( (This)->lpVtbl -> DeckGetCaptureOffset(This,_pCaptureOffsetFields) ) 

#define IMDeckControl_DeckSetExportOffset(This,_lExportOffsetFields)	\
    ( (This)->lpVtbl -> DeckSetExportOffset(This,_lExportOffsetFields) ) 

#define IMDeckControl_DeckGetExportOffset(This,_pExportOffsetFields)	\
    ( (This)->lpVtbl -> DeckGetExportOffset(This,_pExportOffsetFields) ) 

#define IMDeckControl_DeckGetManualExportOffset(This,_pDeckManualExportOffsetFields)	\
    ( (This)->lpVtbl -> DeckGetManualExportOffset(This,_pDeckManualExportOffsetFields) ) 

#define IMDeckControl_DeckStartExport(This,_lInTimecode,_lOutTimecode,_lExportModeOps,_pError)	\
    ( (This)->lpVtbl -> DeckStartExport(This,_lInTimecode,_lOutTimecode,_lExportModeOps,_pError) ) 

#define IMDeckControl_DeckStartCapture(This,_bUseVITC,_lInTimecode,_lOutTimecode,_pError)	\
    ( (This)->lpVtbl -> DeckStartCapture(This,_bUseVITC,_lInTimecode,_lOutTimecode,_pError) ) 

#define IMDeckControl_DeckGetDeviceID(This,_pDeviceId,_pError)	\
    ( (This)->lpVtbl -> DeckGetDeviceID(This,_pDeviceId,_pError) ) 

#define IMDeckControl_DeckAbort(This)	\
    ( (This)->lpVtbl -> DeckAbort(This) ) 

#define IMDeckControl_DeckCrashRecordStart(This,_pError)	\
    ( (This)->lpVtbl -> DeckCrashRecordStart(This,_pError) ) 

#define IMDeckControl_DeckCrashRecordStop(This,_pError)	\
    ( (This)->lpVtbl -> DeckCrashRecordStop(This,_pError) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMDeckControl_INTERFACE_DEFINED__ */


#ifndef __IMConfig_INTERFACE_DEFINED__
#define __IMConfig_INTERFACE_DEFINED__

/* interface IMConfig */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("082DA430-EEC4-4EF1-841E-3A280E7D0383")
    IMConfig : public IMAttributes
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConfigTypesGetCount( 
            /* [out] */ int *_pnCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConfigTypesGetByIndex( 
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsSubType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConfigGetCount( 
            /* [in] */ BSTR _bsType,
            /* [out] */ int *_pnCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConfigGetByIndex( 
            /* [in] */ BSTR _bsType,
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConfigSet( 
            /* [in] */ BSTR _bsType,
            /* [in] */ BSTR _bsName,
            /* [out] */ IMAttributes **_ppConfigProps) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConfigGet( 
            /* [in] */ BSTR _bsType,
            /* [out] */ BSTR *_pbsName,
            /* [out] */ IMAttributes **_ppConfigProps) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConfigShowProps( 
            /* [in] */ BSTR _bsType,
            /* [in] */ BSTR _bsPropsType,
            /* [in] */ LONGLONG _lWndHandle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConfigSetAll( 
            /* [in] */ BSTR _bsAttributesLineOrXML) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ConfigGetAll( 
            /* [in] */ BOOL _bAttributesLine,
            /* [out] */ BSTR *_pbsAttributesLineOrXML) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMConfig * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMConfig * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesGetCount )( 
            IMConfig * This,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesGetByIndex )( 
            IMConfig * This,
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsName,
            /* [out] */ BSTR *_pbsValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesRemove )( 
            IMConfig * This,
            /* [in] */ BSTR _bsName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesRemoveAll )( 
            IMConfig * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesStringSet )( 
            IMConfig * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ BSTR _bsValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesBoolSet )( 
            IMConfig * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ BOOL _bValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesIntSet )( 
            IMConfig * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ int _nValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesDoubleSet )( 
            IMConfig * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ double _dblValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesHave )( 
            IMConfig * This,
            /* [in] */ BSTR _bsName,
            /* [out] */ BOOL *_pbHave,
            /* [out] */ BSTR *_pbsValueOrDefault);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesStringGet )( 
            IMConfig * This,
            /* [in] */ BSTR _bsName,
            /* [out] */ BSTR *_pbsValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesIntGet )( 
            IMConfig * This,
            /* [in] */ BSTR _bsName,
            /* [out] */ int *_pnValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesBoolGet )( 
            IMConfig * This,
            /* [in] */ BSTR _bsName,
            /* [out] */ BOOL *_pbValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesDoubleGet )( 
            IMConfig * This,
            /* [in] */ BSTR _bsName,
            /* [out] */ double *_pdblValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesMultipleSet )( 
            IMConfig * This,
            /* [in] */ BSTR _bsAttributesList,
            /* [in] */ eMUpdateType _eUpdateType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesSave )( 
            IMConfig * This,
            /* [out] */ BSTR *_pbsAttributesList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesClone )( 
            IMConfig * This,
            /* [out] */ IMAttributes **_ppClone);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesSet )( 
            IMConfig * This,
            /* [in] */ IMAttributes *_pAttributesList,
            /* [in] */ eMUpdateType _eUpdateType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesInfoGetCount )( 
            IMConfig * This,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesInfoGetByIndex )( 
            IMConfig * This,
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesInfoGet )( 
            IMConfig * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ eMInfoType _eType,
            /* [out] */ BSTR *_pbsInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttributesValuesInfoGet )( 
            IMConfig * This,
            /* [in] */ BSTR _bsName,
            /* [in] */ BSTR _bsValue,
            /* [in] */ BSTR _bsType,
            /* [out] */ BSTR *_pbsInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigTypesGetCount )( 
            IMConfig * This,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigTypesGetByIndex )( 
            IMConfig * This,
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsSubType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigGetCount )( 
            IMConfig * This,
            /* [in] */ BSTR _bsType,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigGetByIndex )( 
            IMConfig * This,
            /* [in] */ BSTR _bsType,
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigSet )( 
            IMConfig * This,
            /* [in] */ BSTR _bsType,
            /* [in] */ BSTR _bsName,
            /* [out] */ IMAttributes **_ppConfigProps);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigGet )( 
            IMConfig * This,
            /* [in] */ BSTR _bsType,
            /* [out] */ BSTR *_pbsName,
            /* [out] */ IMAttributes **_ppConfigProps);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigShowProps )( 
            IMConfig * This,
            /* [in] */ BSTR _bsType,
            /* [in] */ BSTR _bsPropsType,
            /* [in] */ LONGLONG _lWndHandle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigSetAll )( 
            IMConfig * This,
            /* [in] */ BSTR _bsAttributesLineOrXML);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ConfigGetAll )( 
            IMConfig * This,
            /* [in] */ BOOL _bAttributesLine,
            /* [out] */ BSTR *_pbsAttributesLineOrXML);
        
        END_INTERFACE
    } IMConfigVtbl;

    interface IMConfig
    {
        CONST_VTBL struct IMConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMConfig_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMConfig_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMConfig_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMConfig_AttributesGetCount(This,_pnCount)	\
    ( (This)->lpVtbl -> AttributesGetCount(This,_pnCount) ) 

#define IMConfig_AttributesGetByIndex(This,_nIndex,_pbsName,_pbsValue)	\
    ( (This)->lpVtbl -> AttributesGetByIndex(This,_nIndex,_pbsName,_pbsValue) ) 

#define IMConfig_AttributesRemove(This,_bsName)	\
    ( (This)->lpVtbl -> AttributesRemove(This,_bsName) ) 

#define IMConfig_AttributesRemoveAll(This)	\
    ( (This)->lpVtbl -> AttributesRemoveAll(This) ) 

#define IMConfig_AttributesStringSet(This,_bsName,_bsValue)	\
    ( (This)->lpVtbl -> AttributesStringSet(This,_bsName,_bsValue) ) 

#define IMConfig_AttributesBoolSet(This,_bsName,_bValue)	\
    ( (This)->lpVtbl -> AttributesBoolSet(This,_bsName,_bValue) ) 

#define IMConfig_AttributesIntSet(This,_bsName,_nValue)	\
    ( (This)->lpVtbl -> AttributesIntSet(This,_bsName,_nValue) ) 

#define IMConfig_AttributesDoubleSet(This,_bsName,_dblValue)	\
    ( (This)->lpVtbl -> AttributesDoubleSet(This,_bsName,_dblValue) ) 

#define IMConfig_AttributesHave(This,_bsName,_pbHave,_pbsValueOrDefault)	\
    ( (This)->lpVtbl -> AttributesHave(This,_bsName,_pbHave,_pbsValueOrDefault) ) 

#define IMConfig_AttributesStringGet(This,_bsName,_pbsValue)	\
    ( (This)->lpVtbl -> AttributesStringGet(This,_bsName,_pbsValue) ) 

#define IMConfig_AttributesIntGet(This,_bsName,_pnValue)	\
    ( (This)->lpVtbl -> AttributesIntGet(This,_bsName,_pnValue) ) 

#define IMConfig_AttributesBoolGet(This,_bsName,_pbValue)	\
    ( (This)->lpVtbl -> AttributesBoolGet(This,_bsName,_pbValue) ) 

#define IMConfig_AttributesDoubleGet(This,_bsName,_pdblValue)	\
    ( (This)->lpVtbl -> AttributesDoubleGet(This,_bsName,_pdblValue) ) 

#define IMConfig_AttributesMultipleSet(This,_bsAttributesList,_eUpdateType)	\
    ( (This)->lpVtbl -> AttributesMultipleSet(This,_bsAttributesList,_eUpdateType) ) 

#define IMConfig_AttributesSave(This,_pbsAttributesList)	\
    ( (This)->lpVtbl -> AttributesSave(This,_pbsAttributesList) ) 

#define IMConfig_AttributesClone(This,_ppClone)	\
    ( (This)->lpVtbl -> AttributesClone(This,_ppClone) ) 

#define IMConfig_AttributesSet(This,_pAttributesList,_eUpdateType)	\
    ( (This)->lpVtbl -> AttributesSet(This,_pAttributesList,_eUpdateType) ) 

#define IMConfig_AttributesInfoGetCount(This,_pnCount)	\
    ( (This)->lpVtbl -> AttributesInfoGetCount(This,_pnCount) ) 

#define IMConfig_AttributesInfoGetByIndex(This,_nIndex,_pbsName)	\
    ( (This)->lpVtbl -> AttributesInfoGetByIndex(This,_nIndex,_pbsName) ) 

#define IMConfig_AttributesInfoGet(This,_bsName,_eType,_pbsInfo)	\
    ( (This)->lpVtbl -> AttributesInfoGet(This,_bsName,_eType,_pbsInfo) ) 

#define IMConfig_AttributesValuesInfoGet(This,_bsName,_bsValue,_bsType,_pbsInfo)	\
    ( (This)->lpVtbl -> AttributesValuesInfoGet(This,_bsName,_bsValue,_bsType,_pbsInfo) ) 


#define IMConfig_ConfigTypesGetCount(This,_pnCount)	\
    ( (This)->lpVtbl -> ConfigTypesGetCount(This,_pnCount) ) 

#define IMConfig_ConfigTypesGetByIndex(This,_nIndex,_pbsSubType)	\
    ( (This)->lpVtbl -> ConfigTypesGetByIndex(This,_nIndex,_pbsSubType) ) 

#define IMConfig_ConfigGetCount(This,_bsType,_pnCount)	\
    ( (This)->lpVtbl -> ConfigGetCount(This,_bsType,_pnCount) ) 

#define IMConfig_ConfigGetByIndex(This,_bsType,_nIndex,_pbsName)	\
    ( (This)->lpVtbl -> ConfigGetByIndex(This,_bsType,_nIndex,_pbsName) ) 

#define IMConfig_ConfigSet(This,_bsType,_bsName,_ppConfigProps)	\
    ( (This)->lpVtbl -> ConfigSet(This,_bsType,_bsName,_ppConfigProps) ) 

#define IMConfig_ConfigGet(This,_bsType,_pbsName,_ppConfigProps)	\
    ( (This)->lpVtbl -> ConfigGet(This,_bsType,_pbsName,_ppConfigProps) ) 

#define IMConfig_ConfigShowProps(This,_bsType,_bsPropsType,_lWndHandle)	\
    ( (This)->lpVtbl -> ConfigShowProps(This,_bsType,_bsPropsType,_lWndHandle) ) 

#define IMConfig_ConfigSetAll(This,_bsAttributesLineOrXML)	\
    ( (This)->lpVtbl -> ConfigSetAll(This,_bsAttributesLineOrXML) ) 

#define IMConfig_ConfigGetAll(This,_bAttributesLine,_pbsAttributesLineOrXML)	\
    ( (This)->lpVtbl -> ConfigGetAll(This,_bAttributesLine,_pbsAttributesLineOrXML) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMConfig_INTERFACE_DEFINED__ */


#ifndef __IMFactory_INTERFACE_DEFINED__
#define __IMFactory_INTERFACE_DEFINED__

/* interface IMFactory */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F367000-473F-4ad5-A5C2-428FE0C8E03E")
    IMFactory : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ObjectCreate( 
            /* [in] */ BSTR _bsName,
            /* [out] */ IUnknown **_ppObject) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MFileCreate( 
            /* [out] */ IMFile **_ppFile,
            /* [in] */ BSTR _bsProps) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MLiveCreate( 
            /* [out] */ IMDevice **_ppLive,
            /* [in] */ BSTR _bsProps) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MPlaylistCreate( 
            /* [out] */ IMPlaylist **_ppPlaylist,
            /* [in] */ BSTR _bsProps) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MMixerCreate( 
            /* [out] */ IMObject **_ppMixer,
            /* [in] */ BSTR _bsProps) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MComposerCreate( 
            /* [out] */ IMObject **_ppComposer,
            /* [in] */ BSTR _bsProps) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MPreviewCreate( 
            /* [out] */ IMPreview **_ppPreview,
            /* [in] */ BSTR _bsProps) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MRendererCreate( 
            /* [out] */ IMDevice **_ppRenderer,
            /* [in] */ BSTR _bsProps) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MProxyCreate( 
            /* [out] */ IMReceiver **_ppProxy,
            /* [in] */ BSTR _bsProps) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MWriterCreate( 
            /* [out] */ IMWriter **_ppWriter,
            /* [in] */ BSTR _bsProps) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMFactory * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMFactory * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMFactory * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ObjectCreate )( 
            IMFactory * This,
            /* [in] */ BSTR _bsName,
            /* [out] */ IUnknown **_ppObject);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *MFileCreate )( 
            IMFactory * This,
            /* [out] */ IMFile **_ppFile,
            /* [in] */ BSTR _bsProps);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *MLiveCreate )( 
            IMFactory * This,
            /* [out] */ IMDevice **_ppLive,
            /* [in] */ BSTR _bsProps);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *MPlaylistCreate )( 
            IMFactory * This,
            /* [out] */ IMPlaylist **_ppPlaylist,
            /* [in] */ BSTR _bsProps);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *MMixerCreate )( 
            IMFactory * This,
            /* [out] */ IMObject **_ppMixer,
            /* [in] */ BSTR _bsProps);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *MComposerCreate )( 
            IMFactory * This,
            /* [out] */ IMObject **_ppComposer,
            /* [in] */ BSTR _bsProps);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *MPreviewCreate )( 
            IMFactory * This,
            /* [out] */ IMPreview **_ppPreview,
            /* [in] */ BSTR _bsProps);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *MRendererCreate )( 
            IMFactory * This,
            /* [out] */ IMDevice **_ppRenderer,
            /* [in] */ BSTR _bsProps);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *MProxyCreate )( 
            IMFactory * This,
            /* [out] */ IMReceiver **_ppProxy,
            /* [in] */ BSTR _bsProps);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *MWriterCreate )( 
            IMFactory * This,
            /* [out] */ IMWriter **_ppWriter,
            /* [in] */ BSTR _bsProps);
        
        END_INTERFACE
    } IMFactoryVtbl;

    interface IMFactory
    {
        CONST_VTBL struct IMFactoryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMFactory_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMFactory_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMFactory_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMFactory_ObjectCreate(This,_bsName,_ppObject)	\
    ( (This)->lpVtbl -> ObjectCreate(This,_bsName,_ppObject) ) 

#define IMFactory_MFileCreate(This,_ppFile,_bsProps)	\
    ( (This)->lpVtbl -> MFileCreate(This,_ppFile,_bsProps) ) 

#define IMFactory_MLiveCreate(This,_ppLive,_bsProps)	\
    ( (This)->lpVtbl -> MLiveCreate(This,_ppLive,_bsProps) ) 

#define IMFactory_MPlaylistCreate(This,_ppPlaylist,_bsProps)	\
    ( (This)->lpVtbl -> MPlaylistCreate(This,_ppPlaylist,_bsProps) ) 

#define IMFactory_MMixerCreate(This,_ppMixer,_bsProps)	\
    ( (This)->lpVtbl -> MMixerCreate(This,_ppMixer,_bsProps) ) 

#define IMFactory_MComposerCreate(This,_ppComposer,_bsProps)	\
    ( (This)->lpVtbl -> MComposerCreate(This,_ppComposer,_bsProps) ) 

#define IMFactory_MPreviewCreate(This,_ppPreview,_bsProps)	\
    ( (This)->lpVtbl -> MPreviewCreate(This,_ppPreview,_bsProps) ) 

#define IMFactory_MRendererCreate(This,_ppRenderer,_bsProps)	\
    ( (This)->lpVtbl -> MRendererCreate(This,_ppRenderer,_bsProps) ) 

#define IMFactory_MProxyCreate(This,_ppProxy,_bsProps)	\
    ( (This)->lpVtbl -> MProxyCreate(This,_ppProxy,_bsProps) ) 

#define IMFactory_MWriterCreate(This,_ppWriter,_bsProps)	\
    ( (This)->lpVtbl -> MWriterCreate(This,_ppWriter,_bsProps) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMFactory_INTERFACE_DEFINED__ */


#ifndef __IMSync_INTERFACE_DEFINED__
#define __IMSync_INTERFACE_DEFINED__

/* interface IMSync */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMSync;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F366025-473F-4ad5-A5C2-428FE0C8E03E")
    IMSync : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SyncSetCount( 
            /* [in] */ int _nSyncCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SyncGetCount( 
            /* [out] */ int *_pnSyncCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnableBreaksControl( 
            BOOL _bEnable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsEnabledBreaksControl( 
            BOOL *_pbEnabled) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SkipFrames( 
            BOOL _bSkip) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMSyncVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMSync * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMSync * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMSync * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SyncSetCount )( 
            IMSync * This,
            /* [in] */ int _nSyncCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SyncGetCount )( 
            IMSync * This,
            /* [out] */ int *_pnSyncCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnableBreaksControl )( 
            IMSync * This,
            BOOL _bEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsEnabledBreaksControl )( 
            IMSync * This,
            BOOL *_pbEnabled);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SkipFrames )( 
            IMSync * This,
            BOOL _bSkip);
        
        END_INTERFACE
    } IMSyncVtbl;

    interface IMSync
    {
        CONST_VTBL struct IMSyncVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMSync_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMSync_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMSync_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMSync_SyncSetCount(This,_nSyncCount)	\
    ( (This)->lpVtbl -> SyncSetCount(This,_nSyncCount) ) 

#define IMSync_SyncGetCount(This,_pnSyncCount)	\
    ( (This)->lpVtbl -> SyncGetCount(This,_pnSyncCount) ) 

#define IMSync_EnableBreaksControl(This,_bEnable)	\
    ( (This)->lpVtbl -> EnableBreaksControl(This,_bEnable) ) 

#define IMSync_IsEnabledBreaksControl(This,_pbEnabled)	\
    ( (This)->lpVtbl -> IsEnabledBreaksControl(This,_pbEnabled) ) 

#define IMSync_SkipFrames(This,_bSkip)	\
    ( (This)->lpVtbl -> SkipFrames(This,_bSkip) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMSync_INTERFACE_DEFINED__ */


#ifndef __IMSource_INTERFACE_DEFINED__
#define __IMSource_INTERFACE_DEFINED__

/* interface IMSource */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CD799F70-3FD4-4237-92D4-D187B588D999")
    IMSource : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SourceFrameGet( 
            /* [in] */ REFERENCE_TIME _rtMaxWait,
            /* [out] */ IMFrame **_ppFrame,
            /* [in] */ int _nFlags) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SourceFrameGetEx( 
            /* [out][in] */ LONGLONG *_plUserData,
            /* [in] */ REFERENCE_TIME _rtMaxWait,
            /* [out] */ IMFrame **_ppFrame,
            /* [in] */ int _nFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMSource * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMSource * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMSource * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SourceFrameGet )( 
            IMSource * This,
            /* [in] */ REFERENCE_TIME _rtMaxWait,
            /* [out] */ IMFrame **_ppFrame,
            /* [in] */ int _nFlags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SourceFrameGetEx )( 
            IMSource * This,
            /* [out][in] */ LONGLONG *_plUserData,
            /* [in] */ REFERENCE_TIME _rtMaxWait,
            /* [out] */ IMFrame **_ppFrame,
            /* [in] */ int _nFlags);
        
        END_INTERFACE
    } IMSourceVtbl;

    interface IMSource
    {
        CONST_VTBL struct IMSourceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMSource_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMSource_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMSource_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMSource_SourceFrameGet(This,_rtMaxWait,_ppFrame,_nFlags)	\
    ( (This)->lpVtbl -> SourceFrameGet(This,_rtMaxWait,_ppFrame,_nFlags) ) 

#define IMSource_SourceFrameGetEx(This,_plUserData,_rtMaxWait,_ppFrame,_nFlags)	\
    ( (This)->lpVtbl -> SourceFrameGetEx(This,_plUserData,_rtMaxWait,_ppFrame,_nFlags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMSource_INTERFACE_DEFINED__ */


#ifndef __IMSource_I_INTERFACE_DEFINED__
#define __IMSource_I_INTERFACE_DEFINED__

/* interface IMSource_I */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMSource_I;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CD799F77-3FD4-4237-92D4-D187B588D999")
    IMSource_I : public IMSource
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SourceInit( 
            /* [out][in] */ LONGLONG *_plUserData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SourceClose( 
            /* [in] */ LONGLONG _lUserData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SourceRefAdd( 
            /* [in] */ DWORD _dwProcessID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SourceRefRemove( 
            /* [in] */ DWORD _dwProcessID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SourceHaveRefs( 
            /* [out] */ LONGLONG *_phWaitHandle) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMSource_IVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMSource_I * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMSource_I * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMSource_I * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SourceFrameGet )( 
            IMSource_I * This,
            /* [in] */ REFERENCE_TIME _rtMaxWait,
            /* [out] */ IMFrame **_ppFrame,
            /* [in] */ int _nFlags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SourceFrameGetEx )( 
            IMSource_I * This,
            /* [out][in] */ LONGLONG *_plUserData,
            /* [in] */ REFERENCE_TIME _rtMaxWait,
            /* [out] */ IMFrame **_ppFrame,
            /* [in] */ int _nFlags);
        
        HRESULT ( STDMETHODCALLTYPE *SourceInit )( 
            IMSource_I * This,
            /* [out][in] */ LONGLONG *_plUserData);
        
        HRESULT ( STDMETHODCALLTYPE *SourceClose )( 
            IMSource_I * This,
            /* [in] */ LONGLONG _lUserData);
        
        HRESULT ( STDMETHODCALLTYPE *SourceRefAdd )( 
            IMSource_I * This,
            /* [in] */ DWORD _dwProcessID);
        
        HRESULT ( STDMETHODCALLTYPE *SourceRefRemove )( 
            IMSource_I * This,
            /* [in] */ DWORD _dwProcessID);
        
        HRESULT ( STDMETHODCALLTYPE *SourceHaveRefs )( 
            IMSource_I * This,
            /* [out] */ LONGLONG *_phWaitHandle);
        
        END_INTERFACE
    } IMSource_IVtbl;

    interface IMSource_I
    {
        CONST_VTBL struct IMSource_IVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMSource_I_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMSource_I_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMSource_I_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMSource_I_SourceFrameGet(This,_rtMaxWait,_ppFrame,_nFlags)	\
    ( (This)->lpVtbl -> SourceFrameGet(This,_rtMaxWait,_ppFrame,_nFlags) ) 

#define IMSource_I_SourceFrameGetEx(This,_plUserData,_rtMaxWait,_ppFrame,_nFlags)	\
    ( (This)->lpVtbl -> SourceFrameGetEx(This,_plUserData,_rtMaxWait,_ppFrame,_nFlags) ) 


#define IMSource_I_SourceInit(This,_plUserData)	\
    ( (This)->lpVtbl -> SourceInit(This,_plUserData) ) 

#define IMSource_I_SourceClose(This,_lUserData)	\
    ( (This)->lpVtbl -> SourceClose(This,_lUserData) ) 

#define IMSource_I_SourceRefAdd(This,_dwProcessID)	\
    ( (This)->lpVtbl -> SourceRefAdd(This,_dwProcessID) ) 

#define IMSource_I_SourceRefRemove(This,_dwProcessID)	\
    ( (This)->lpVtbl -> SourceRefRemove(This,_dwProcessID) ) 

#define IMSource_I_SourceHaveRefs(This,_phWaitHandle)	\
    ( (This)->lpVtbl -> SourceHaveRefs(This,_phWaitHandle) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMSource_I_INTERFACE_DEFINED__ */


#ifndef __IMFrame_I_INTERFACE_DEFINED__
#define __IMFrame_I_INTERFACE_DEFINED__

/* interface IMFrame_I */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMFrame_I;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F367777-473F-4ad5-A5C2-428FE0C8E03E")
    IMFrame_I : public IMFrame
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetProcessID( 
            /* [out] */ DWORD *_pdwProcessID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetID( 
            /* [out] */ LONGLONG *_plFrameID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AudioGet( 
            /* [out] */ DWORD *_pcbAudio,
            /* [size_is][size_is][out] */ BYTE **_ppbAudio) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE VideoGet( 
            /* [out] */ DWORD *_pcbVideo,
            /* [size_is][size_is][out] */ BYTE **_ppbVideo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE VideoGetOffset( 
            /* [out] */ LONG *_plOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AudioSet( 
            /* [in] */ DWORD _cbAudio,
            /* [size_is][in] */ BYTE *_pbAudio) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFrameProps( 
            /* [out] */ M_TIME *_pTime,
            /* [out] */ M_AV_PROPS *_pProps,
            /* [out] */ DWORD *_pcbVideo,
            /* [out] */ DWORD *_pcbAudio) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFramePropsAll( 
            /* [out] */ M_TIME *_pTime,
            /* [out] */ M_AV_PROPS *_pProps,
            /* [out] */ DWORD *_pcbAudio,
            /* [out] */ BYTE **_ppbAudio,
            /* [out] */ DWORD *_pcbVideo,
            /* [out] */ BYTE **_ppbVideo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ANCDataGet_I( 
            /* [in] */ DWORD _dwDataFCC,
            /* [out] */ DWORD *_pcbANCData,
            /* [size_is][size_is][out] */ BYTE **_ppbANCData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ANCDataCopyFrom_I( 
            /* [in] */ IMFrame_I *_pSource,
            /* [in] */ int _nCopyType) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMFrame_IVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMFrame_I * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMFrame_I * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMFrame_I * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameAVPropsGet )( 
            IMFrame_I * This,
            /* [out] */ M_AV_PROPS *_pProps);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameAVPropsSet )( 
            IMFrame_I * This,
            /* [in] */ M_AV_PROPS *_pProps);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameTimeGet )( 
            IMFrame_I * This,
            /* [out] */ M_TIME *_pTime);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameTimeSet )( 
            IMFrame_I * This,
            /* [in] */ M_TIME *_pTime);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameAudioGetBytes )( 
            IMFrame_I * This,
            /* [out] */ LONG *_pcbSize,
            /* [out] */ LONGLONG *_ppbAudio);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameVideoGetBytes )( 
            IMFrame_I * This,
            /* [out] */ LONG *_pcbSize,
            /* [out] */ LONGLONG *_ppbVideo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameVideoGetHbitmap )( 
            IMFrame_I * This,
            /* [out] */ LONGLONG *_pcpHBitmap);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameVideoSaveToFile )( 
            IMFrame_I * This,
            /* [in] */ BSTR _bsFileName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameAudioSaveToFile )( 
            IMFrame_I * This,
            /* [in] */ BSTR _bsFileName,
            /* [in] */ BOOL _bAppend);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameDataGetByIndex )( 
            IMFrame_I * This,
            /* [in] */ int _nIndex,
            /* [out] */ LONG *_pnDataFCC,
            /* [out] */ LONG *_pcbANCData,
            /* [out] */ LONGLONG *_ppbANCData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameDataGet )( 
            IMFrame_I * This,
            /* [in] */ LONG _nDataFCC,
            /* [out] */ LONG *_pcbANCData,
            /* [out] */ LONGLONG *_ppbANCData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameDataSet )( 
            IMFrame_I * This,
            /* [in] */ LONG _nDataFCC,
            /* [in] */ LONG _cbANCData,
            /* [in] */ LONGLONG _pbANCData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameClone )( 
            IMFrame_I * This,
            /* [out] */ IMFrame **_ppCloneFrame,
            /* [in] */ eMFrameClone _eCloneType,
            /* [in] */ eMFCC _fccPixelFormat);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameCut )( 
            IMFrame_I * This,
            /* [in] */ int _nField,
            /* [in] */ RECT *_pRect,
            /* [out] */ IMFrame **_ppFrameRes);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameConvert )( 
            IMFrame_I * This,
            /* [in] */ M_VID_PROPS *_pVidPropsDest,
            /* [out] */ IMFrame **_ppFrameRes,
            /* [in] */ BSTR _bsPropsList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameOverlay )( 
            IMFrame_I * This,
            /* [in] */ IMFrame *_pFrameOver,
            /* [in] */ int _nPosX,
            /* [in] */ int _nPosY,
            /* [in] */ double _dblAlpha,
            /* [in] */ BSTR _bsPropsList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameRelease )( 
            IMFrame_I * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetProcessID )( 
            IMFrame_I * This,
            /* [out] */ DWORD *_pdwProcessID);
        
        HRESULT ( STDMETHODCALLTYPE *GetID )( 
            IMFrame_I * This,
            /* [out] */ LONGLONG *_plFrameID);
        
        HRESULT ( STDMETHODCALLTYPE *AudioGet )( 
            IMFrame_I * This,
            /* [out] */ DWORD *_pcbAudio,
            /* [size_is][size_is][out] */ BYTE **_ppbAudio);
        
        HRESULT ( STDMETHODCALLTYPE *VideoGet )( 
            IMFrame_I * This,
            /* [out] */ DWORD *_pcbVideo,
            /* [size_is][size_is][out] */ BYTE **_ppbVideo);
        
        HRESULT ( STDMETHODCALLTYPE *VideoGetOffset )( 
            IMFrame_I * This,
            /* [out] */ LONG *_plOffset);
        
        HRESULT ( STDMETHODCALLTYPE *AudioSet )( 
            IMFrame_I * This,
            /* [in] */ DWORD _cbAudio,
            /* [size_is][in] */ BYTE *_pbAudio);
        
        HRESULT ( STDMETHODCALLTYPE *GetFrameProps )( 
            IMFrame_I * This,
            /* [out] */ M_TIME *_pTime,
            /* [out] */ M_AV_PROPS *_pProps,
            /* [out] */ DWORD *_pcbVideo,
            /* [out] */ DWORD *_pcbAudio);
        
        HRESULT ( STDMETHODCALLTYPE *GetFramePropsAll )( 
            IMFrame_I * This,
            /* [out] */ M_TIME *_pTime,
            /* [out] */ M_AV_PROPS *_pProps,
            /* [out] */ DWORD *_pcbAudio,
            /* [out] */ BYTE **_ppbAudio,
            /* [out] */ DWORD *_pcbVideo,
            /* [out] */ BYTE **_ppbVideo);
        
        HRESULT ( STDMETHODCALLTYPE *ANCDataGet_I )( 
            IMFrame_I * This,
            /* [in] */ DWORD _dwDataFCC,
            /* [out] */ DWORD *_pcbANCData,
            /* [size_is][size_is][out] */ BYTE **_ppbANCData);
        
        HRESULT ( STDMETHODCALLTYPE *ANCDataCopyFrom_I )( 
            IMFrame_I * This,
            /* [in] */ IMFrame_I *_pSource,
            /* [in] */ int _nCopyType);
        
        END_INTERFACE
    } IMFrame_IVtbl;

    interface IMFrame_I
    {
        CONST_VTBL struct IMFrame_IVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMFrame_I_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMFrame_I_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMFrame_I_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMFrame_I_FrameAVPropsGet(This,_pProps)	\
    ( (This)->lpVtbl -> FrameAVPropsGet(This,_pProps) ) 

#define IMFrame_I_FrameAVPropsSet(This,_pProps)	\
    ( (This)->lpVtbl -> FrameAVPropsSet(This,_pProps) ) 

#define IMFrame_I_FrameTimeGet(This,_pTime)	\
    ( (This)->lpVtbl -> FrameTimeGet(This,_pTime) ) 

#define IMFrame_I_FrameTimeSet(This,_pTime)	\
    ( (This)->lpVtbl -> FrameTimeSet(This,_pTime) ) 

#define IMFrame_I_FrameAudioGetBytes(This,_pcbSize,_ppbAudio)	\
    ( (This)->lpVtbl -> FrameAudioGetBytes(This,_pcbSize,_ppbAudio) ) 

#define IMFrame_I_FrameVideoGetBytes(This,_pcbSize,_ppbVideo)	\
    ( (This)->lpVtbl -> FrameVideoGetBytes(This,_pcbSize,_ppbVideo) ) 

#define IMFrame_I_FrameVideoGetHbitmap(This,_pcpHBitmap)	\
    ( (This)->lpVtbl -> FrameVideoGetHbitmap(This,_pcpHBitmap) ) 

#define IMFrame_I_FrameVideoSaveToFile(This,_bsFileName)	\
    ( (This)->lpVtbl -> FrameVideoSaveToFile(This,_bsFileName) ) 

#define IMFrame_I_FrameAudioSaveToFile(This,_bsFileName,_bAppend)	\
    ( (This)->lpVtbl -> FrameAudioSaveToFile(This,_bsFileName,_bAppend) ) 

#define IMFrame_I_FrameDataGetByIndex(This,_nIndex,_pnDataFCC,_pcbANCData,_ppbANCData)	\
    ( (This)->lpVtbl -> FrameDataGetByIndex(This,_nIndex,_pnDataFCC,_pcbANCData,_ppbANCData) ) 

#define IMFrame_I_FrameDataGet(This,_nDataFCC,_pcbANCData,_ppbANCData)	\
    ( (This)->lpVtbl -> FrameDataGet(This,_nDataFCC,_pcbANCData,_ppbANCData) ) 

#define IMFrame_I_FrameDataSet(This,_nDataFCC,_cbANCData,_pbANCData)	\
    ( (This)->lpVtbl -> FrameDataSet(This,_nDataFCC,_cbANCData,_pbANCData) ) 

#define IMFrame_I_FrameClone(This,_ppCloneFrame,_eCloneType,_fccPixelFormat)	\
    ( (This)->lpVtbl -> FrameClone(This,_ppCloneFrame,_eCloneType,_fccPixelFormat) ) 

#define IMFrame_I_FrameCut(This,_nField,_pRect,_ppFrameRes)	\
    ( (This)->lpVtbl -> FrameCut(This,_nField,_pRect,_ppFrameRes) ) 

#define IMFrame_I_FrameConvert(This,_pVidPropsDest,_ppFrameRes,_bsPropsList)	\
    ( (This)->lpVtbl -> FrameConvert(This,_pVidPropsDest,_ppFrameRes,_bsPropsList) ) 

#define IMFrame_I_FrameOverlay(This,_pFrameOver,_nPosX,_nPosY,_dblAlpha,_bsPropsList)	\
    ( (This)->lpVtbl -> FrameOverlay(This,_pFrameOver,_nPosX,_nPosY,_dblAlpha,_bsPropsList) ) 

#define IMFrame_I_FrameRelease(This)	\
    ( (This)->lpVtbl -> FrameRelease(This) ) 


#define IMFrame_I_GetProcessID(This,_pdwProcessID)	\
    ( (This)->lpVtbl -> GetProcessID(This,_pdwProcessID) ) 

#define IMFrame_I_GetID(This,_plFrameID)	\
    ( (This)->lpVtbl -> GetID(This,_plFrameID) ) 

#define IMFrame_I_AudioGet(This,_pcbAudio,_ppbAudio)	\
    ( (This)->lpVtbl -> AudioGet(This,_pcbAudio,_ppbAudio) ) 

#define IMFrame_I_VideoGet(This,_pcbVideo,_ppbVideo)	\
    ( (This)->lpVtbl -> VideoGet(This,_pcbVideo,_ppbVideo) ) 

#define IMFrame_I_VideoGetOffset(This,_plOffset)	\
    ( (This)->lpVtbl -> VideoGetOffset(This,_plOffset) ) 

#define IMFrame_I_AudioSet(This,_cbAudio,_pbAudio)	\
    ( (This)->lpVtbl -> AudioSet(This,_cbAudio,_pbAudio) ) 

#define IMFrame_I_GetFrameProps(This,_pTime,_pProps,_pcbVideo,_pcbAudio)	\
    ( (This)->lpVtbl -> GetFrameProps(This,_pTime,_pProps,_pcbVideo,_pcbAudio) ) 

#define IMFrame_I_GetFramePropsAll(This,_pTime,_pProps,_pcbAudio,_ppbAudio,_pcbVideo,_ppbVideo)	\
    ( (This)->lpVtbl -> GetFramePropsAll(This,_pTime,_pProps,_pcbAudio,_ppbAudio,_pcbVideo,_ppbVideo) ) 

#define IMFrame_I_ANCDataGet_I(This,_dwDataFCC,_pcbANCData,_ppbANCData)	\
    ( (This)->lpVtbl -> ANCDataGet_I(This,_dwDataFCC,_pcbANCData,_ppbANCData) ) 

#define IMFrame_I_ANCDataCopyFrom_I(This,_pSource,_nCopyType)	\
    ( (This)->lpVtbl -> ANCDataCopyFrom_I(This,_pSource,_nCopyType) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMFrame_I_INTERFACE_DEFINED__ */


#ifndef __IMFrames_I_INTERFACE_DEFINED__
#define __IMFrames_I_INTERFACE_DEFINED__

/* interface IMFrames_I */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMFrames_I;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F367778-473F-4ad5-A5C2-428FE0C8E03E")
    IMFrames_I : public IMFrames
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE FramesCreate_I( 
            /* [in] */ int _cbVideoSize,
            /* [in] */ int _cbAudioSize,
            /* [in] */ BSTR _bsProps,
            /* [out] */ IMFrame_I **_ppFrame) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FramesClone_I( 
            /* [in] */ IMFrame *_pFrame,
            /* [out] */ IMFrame_I **_ppFrameClone,
            /* [in] */ eMFrameClone _eCloneType,
            /* [in] */ eMFCC _fccPixelFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FramesConvert_I( 
            /* [in] */ IMFrame *_pFrameSrcL_F1,
            /* [in] */ IMFrame *_pFrameSrcR_F2,
            /* [in] */ M_VID_PROPS *_pVidPropsDest,
            /* [out] */ IMFrame **_ppFrameDest,
            /* [in] */ BSTR _bsPropsList) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AllocBuffer( 
            /* [in] */ DWORD _cbSize,
            /* [out] */ LONGLONG *_ppBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReleaseBuffer( 
            /* [in] */ LONGLONG _pBuffer) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMFrames_IVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMFrames_I * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMFrames_I * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMFrames_I * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FramesMakeLocal )( 
            IMFrames_I * This,
            /* [in] */ IMFrame *_ppFrame,
            /* [out] */ IMFrame **_ppFrameLocal,
            /* [in] */ BOOL _bMakeRef);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FramesCreate )( 
            IMFrames_I * This,
            /* [in] */ int _cbVideoSize,
            /* [in] */ BSTR _bsProps,
            /* [out] */ IMFrame **_ppFrame);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FramesCreateFromMem )( 
            IMFrames_I * This,
            /* [in] */ M_VID_PROPS *_pVidProps,
            /* [in] */ LONGLONG _pbVideo,
            /* [out] */ IMFrame **_ppFrame,
            /* [in] */ BSTR _bsPropsList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FramesCreateFromFile )( 
            IMFrames_I * This,
            /* [in] */ BSTR _bsFileName,
            /* [out] */ IMFrame **_ppFrame,
            /* [in] */ BSTR _bsPropsList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FramesCreateFromHBITMAP )( 
            IMFrames_I * This,
            /* [in] */ LONGLONG _hBitmap,
            /* [out] */ IMFrame **_ppFrame,
            /* [in] */ BSTR _bsPropsList);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FramesCreateFromSurface )( 
            IMFrames_I * This,
            /* [in] */ IUnknown *_pSurface,
            /* [out] */ IMFrame **_ppFrame,
            /* [in] */ BSTR _bsPropsList);
        
        HRESULT ( STDMETHODCALLTYPE *FramesCreate_I )( 
            IMFrames_I * This,
            /* [in] */ int _cbVideoSize,
            /* [in] */ int _cbAudioSize,
            /* [in] */ BSTR _bsProps,
            /* [out] */ IMFrame_I **_ppFrame);
        
        HRESULT ( STDMETHODCALLTYPE *FramesClone_I )( 
            IMFrames_I * This,
            /* [in] */ IMFrame *_pFrame,
            /* [out] */ IMFrame_I **_ppFrameClone,
            /* [in] */ eMFrameClone _eCloneType,
            /* [in] */ eMFCC _fccPixelFormat);
        
        HRESULT ( STDMETHODCALLTYPE *FramesConvert_I )( 
            IMFrames_I * This,
            /* [in] */ IMFrame *_pFrameSrcL_F1,
            /* [in] */ IMFrame *_pFrameSrcR_F2,
            /* [in] */ M_VID_PROPS *_pVidPropsDest,
            /* [out] */ IMFrame **_ppFrameDest,
            /* [in] */ BSTR _bsPropsList);
        
        HRESULT ( STDMETHODCALLTYPE *AllocBuffer )( 
            IMFrames_I * This,
            /* [in] */ DWORD _cbSize,
            /* [out] */ LONGLONG *_ppBuffer);
        
        HRESULT ( STDMETHODCALLTYPE *ReleaseBuffer )( 
            IMFrames_I * This,
            /* [in] */ LONGLONG _pBuffer);
        
        END_INTERFACE
    } IMFrames_IVtbl;

    interface IMFrames_I
    {
        CONST_VTBL struct IMFrames_IVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMFrames_I_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMFrames_I_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMFrames_I_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMFrames_I_FramesMakeLocal(This,_ppFrame,_ppFrameLocal,_bMakeRef)	\
    ( (This)->lpVtbl -> FramesMakeLocal(This,_ppFrame,_ppFrameLocal,_bMakeRef) ) 

#define IMFrames_I_FramesCreate(This,_cbVideoSize,_bsProps,_ppFrame)	\
    ( (This)->lpVtbl -> FramesCreate(This,_cbVideoSize,_bsProps,_ppFrame) ) 

#define IMFrames_I_FramesCreateFromMem(This,_pVidProps,_pbVideo,_ppFrame,_bsPropsList)	\
    ( (This)->lpVtbl -> FramesCreateFromMem(This,_pVidProps,_pbVideo,_ppFrame,_bsPropsList) ) 

#define IMFrames_I_FramesCreateFromFile(This,_bsFileName,_ppFrame,_bsPropsList)	\
    ( (This)->lpVtbl -> FramesCreateFromFile(This,_bsFileName,_ppFrame,_bsPropsList) ) 

#define IMFrames_I_FramesCreateFromHBITMAP(This,_hBitmap,_ppFrame,_bsPropsList)	\
    ( (This)->lpVtbl -> FramesCreateFromHBITMAP(This,_hBitmap,_ppFrame,_bsPropsList) ) 

#define IMFrames_I_FramesCreateFromSurface(This,_pSurface,_ppFrame,_bsPropsList)	\
    ( (This)->lpVtbl -> FramesCreateFromSurface(This,_pSurface,_ppFrame,_bsPropsList) ) 


#define IMFrames_I_FramesCreate_I(This,_cbVideoSize,_cbAudioSize,_bsProps,_ppFrame)	\
    ( (This)->lpVtbl -> FramesCreate_I(This,_cbVideoSize,_cbAudioSize,_bsProps,_ppFrame) ) 

#define IMFrames_I_FramesClone_I(This,_pFrame,_ppFrameClone,_eCloneType,_fccPixelFormat)	\
    ( (This)->lpVtbl -> FramesClone_I(This,_pFrame,_ppFrameClone,_eCloneType,_fccPixelFormat) ) 

#define IMFrames_I_FramesConvert_I(This,_pFrameSrcL_F1,_pFrameSrcR_F2,_pVidPropsDest,_ppFrameDest,_bsPropsList)	\
    ( (This)->lpVtbl -> FramesConvert_I(This,_pFrameSrcL_F1,_pFrameSrcR_F2,_pVidPropsDest,_ppFrameDest,_bsPropsList) ) 

#define IMFrames_I_AllocBuffer(This,_cbSize,_ppBuffer)	\
    ( (This)->lpVtbl -> AllocBuffer(This,_cbSize,_ppBuffer) ) 

#define IMFrames_I_ReleaseBuffer(This,_pBuffer)	\
    ( (This)->lpVtbl -> ReleaseBuffer(This,_pBuffer) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMFrames_I_INTERFACE_DEFINED__ */


#ifndef __IMDevice_I_INTERFACE_DEFINED__
#define __IMDevice_I_INTERFACE_DEFINED__

/* interface IMDevice_I */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMDevice_I;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F367A40-473F-4ad5-A5C2-428FE0C8E03E")
    IMDevice_I : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsOwnDevice( 
            /* [in] */ BSTR _bsType,
            /* [in] */ BSTR _bsName,
            /* [in] */ BSTR _bsMoniker) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDevices( 
            /* [out] */ BSTR *_pbsXMLDevices,
            /* [out] */ BSTR *_pbsXMLCurrent) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetDeviceOrProps( 
            /* [in] */ BSTR _bsType,
            /* [in] */ BSTR _bsDeviceDesc,
            /* [out] */ BSTR *_pbsUpdatedDesc) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ShowDeviceProps( 
            /* [in] */ BSTR _bsType,
            /* [in] */ BSTR _bsPropsType,
            /* [in] */ LONGLONG _lWndHandle) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMDevice_IVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMDevice_I * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMDevice_I * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMDevice_I * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsOwnDevice )( 
            IMDevice_I * This,
            /* [in] */ BSTR _bsType,
            /* [in] */ BSTR _bsName,
            /* [in] */ BSTR _bsMoniker);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDevices )( 
            IMDevice_I * This,
            /* [out] */ BSTR *_pbsXMLDevices,
            /* [out] */ BSTR *_pbsXMLCurrent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetDeviceOrProps )( 
            IMDevice_I * This,
            /* [in] */ BSTR _bsType,
            /* [in] */ BSTR _bsDeviceDesc,
            /* [out] */ BSTR *_pbsUpdatedDesc);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ShowDeviceProps )( 
            IMDevice_I * This,
            /* [in] */ BSTR _bsType,
            /* [in] */ BSTR _bsPropsType,
            /* [in] */ LONGLONG _lWndHandle);
        
        END_INTERFACE
    } IMDevice_IVtbl;

    interface IMDevice_I
    {
        CONST_VTBL struct IMDevice_IVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMDevice_I_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMDevice_I_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMDevice_I_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMDevice_I_IsOwnDevice(This,_bsType,_bsName,_bsMoniker)	\
    ( (This)->lpVtbl -> IsOwnDevice(This,_bsType,_bsName,_bsMoniker) ) 

#define IMDevice_I_GetDevices(This,_pbsXMLDevices,_pbsXMLCurrent)	\
    ( (This)->lpVtbl -> GetDevices(This,_pbsXMLDevices,_pbsXMLCurrent) ) 

#define IMDevice_I_SetDeviceOrProps(This,_bsType,_bsDeviceDesc,_pbsUpdatedDesc)	\
    ( (This)->lpVtbl -> SetDeviceOrProps(This,_bsType,_bsDeviceDesc,_pbsUpdatedDesc) ) 

#define IMDevice_I_ShowDeviceProps(This,_bsType,_bsPropsType,_lWndHandle)	\
    ( (This)->lpVtbl -> ShowDeviceProps(This,_bsType,_bsPropsType,_lWndHandle) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMDevice_I_INTERFACE_DEFINED__ */


#ifndef __IMObject_I_INTERFACE_DEFINED__
#define __IMObject_I_INTERFACE_DEFINED__

/* interface IMObject_I */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMObject_I;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F366A00-473F-4ad5-A5C2-428FE0C8E03E")
    IMObject_I : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ IUnknown *_pReceiverOrSender) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetInterface( 
            /* [in] */ IUnknown *_pReceiverOrSender,
            /* [in] */ BOOL _bNoEOS) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMediaProps( 
            /* [out] */ M_VID_PROPS *_pVidProps,
            /* [out] */ M_AUD_PROPS *_pAudProps) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetState( 
            /* [out] */ eMState *_peState,
            /* [out] */ IUnknown **_ppReceiverOrSender) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInternalInterface( 
            /* [in] */ BSTR _bsType,
            /* [out] */ IUnknown **_ppObject) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMObject_IVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMObject_I * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMObject_I * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMObject_I * This);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IMObject_I * This,
            /* [in] */ IUnknown *_pReceiverOrSender);
        
        HRESULT ( STDMETHODCALLTYPE *Close )( 
            IMObject_I * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetInterface )( 
            IMObject_I * This,
            /* [in] */ IUnknown *_pReceiverOrSender,
            /* [in] */ BOOL _bNoEOS);
        
        HRESULT ( STDMETHODCALLTYPE *GetMediaProps )( 
            IMObject_I * This,
            /* [out] */ M_VID_PROPS *_pVidProps,
            /* [out] */ M_AUD_PROPS *_pAudProps);
        
        HRESULT ( STDMETHODCALLTYPE *GetState )( 
            IMObject_I * This,
            /* [out] */ eMState *_peState,
            /* [out] */ IUnknown **_ppReceiverOrSender);
        
        HRESULT ( STDMETHODCALLTYPE *GetInternalInterface )( 
            IMObject_I * This,
            /* [in] */ BSTR _bsType,
            /* [out] */ IUnknown **_ppObject);
        
        END_INTERFACE
    } IMObject_IVtbl;

    interface IMObject_I
    {
        CONST_VTBL struct IMObject_IVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMObject_I_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMObject_I_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMObject_I_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMObject_I_Init(This,_pReceiverOrSender)	\
    ( (This)->lpVtbl -> Init(This,_pReceiverOrSender) ) 

#define IMObject_I_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#define IMObject_I_SetInterface(This,_pReceiverOrSender,_bNoEOS)	\
    ( (This)->lpVtbl -> SetInterface(This,_pReceiverOrSender,_bNoEOS) ) 

#define IMObject_I_GetMediaProps(This,_pVidProps,_pAudProps)	\
    ( (This)->lpVtbl -> GetMediaProps(This,_pVidProps,_pAudProps) ) 

#define IMObject_I_GetState(This,_peState,_ppReceiverOrSender)	\
    ( (This)->lpVtbl -> GetState(This,_peState,_ppReceiverOrSender) ) 

#define IMObject_I_GetInternalInterface(This,_bsType,_ppObject)	\
    ( (This)->lpVtbl -> GetInternalInterface(This,_bsType,_ppObject) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMObject_I_INTERFACE_DEFINED__ */


#ifndef __IMSender_I_INTERFACE_DEFINED__
#define __IMSender_I_INTERFACE_DEFINED__

/* interface IMSender_I */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMSender_I;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F367A05-473F-4ad5-A5C2-428FE0C8E03E")
    IMSender_I : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SenderChannelAdd( 
            /* [in] */ IUnknown *_pReceiver,
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ BSTR _bsXMLParam,
            /* [out] */ BOOL *_pbSenderRunning) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SenderChannelRemove( 
            /* [in] */ BSTR _bsChannelID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SenderChannelGetCount( 
            /* [out] */ int *_pnCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SenderChannelGetByIndex( 
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsChannelID,
            /* [out] */ BSTR *_pbsXMLParam) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SenderGetName( 
            /* [out] */ BSTR *_pbsName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SenderGetMediaProps( 
            /* [out] */ M_VID_PROPS *_pVidProps,
            /* [out] */ M_AUD_PROPS *_pAudProps) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SenderCallbackAdd( 
            /* [in] */ IUnknown *_pCallback,
            /* [in] */ LONGLONG _llCallbackUserData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SenderCallbackRemove( 
            /* [in] */ IUnknown *_pCallback) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMSender_IVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMSender_I * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMSender_I * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMSender_I * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SenderChannelAdd )( 
            IMSender_I * This,
            /* [in] */ IUnknown *_pReceiver,
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ BSTR _bsXMLParam,
            /* [out] */ BOOL *_pbSenderRunning);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SenderChannelRemove )( 
            IMSender_I * This,
            /* [in] */ BSTR _bsChannelID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SenderChannelGetCount )( 
            IMSender_I * This,
            /* [out] */ int *_pnCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SenderChannelGetByIndex )( 
            IMSender_I * This,
            /* [in] */ int _nIndex,
            /* [out] */ BSTR *_pbsChannelID,
            /* [out] */ BSTR *_pbsXMLParam);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SenderGetName )( 
            IMSender_I * This,
            /* [out] */ BSTR *_pbsName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SenderGetMediaProps )( 
            IMSender_I * This,
            /* [out] */ M_VID_PROPS *_pVidProps,
            /* [out] */ M_AUD_PROPS *_pAudProps);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SenderCallbackAdd )( 
            IMSender_I * This,
            /* [in] */ IUnknown *_pCallback,
            /* [in] */ LONGLONG _llCallbackUserData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SenderCallbackRemove )( 
            IMSender_I * This,
            /* [in] */ IUnknown *_pCallback);
        
        END_INTERFACE
    } IMSender_IVtbl;

    interface IMSender_I
    {
        CONST_VTBL struct IMSender_IVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMSender_I_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMSender_I_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMSender_I_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMSender_I_SenderChannelAdd(This,_pReceiver,_bsChannelID,_bsXMLParam,_pbSenderRunning)	\
    ( (This)->lpVtbl -> SenderChannelAdd(This,_pReceiver,_bsChannelID,_bsXMLParam,_pbSenderRunning) ) 

#define IMSender_I_SenderChannelRemove(This,_bsChannelID)	\
    ( (This)->lpVtbl -> SenderChannelRemove(This,_bsChannelID) ) 

#define IMSender_I_SenderChannelGetCount(This,_pnCount)	\
    ( (This)->lpVtbl -> SenderChannelGetCount(This,_pnCount) ) 

#define IMSender_I_SenderChannelGetByIndex(This,_nIndex,_pbsChannelID,_pbsXMLParam)	\
    ( (This)->lpVtbl -> SenderChannelGetByIndex(This,_nIndex,_pbsChannelID,_pbsXMLParam) ) 

#define IMSender_I_SenderGetName(This,_pbsName)	\
    ( (This)->lpVtbl -> SenderGetName(This,_pbsName) ) 

#define IMSender_I_SenderGetMediaProps(This,_pVidProps,_pAudProps)	\
    ( (This)->lpVtbl -> SenderGetMediaProps(This,_pVidProps,_pAudProps) ) 

#define IMSender_I_SenderCallbackAdd(This,_pCallback,_llCallbackUserData)	\
    ( (This)->lpVtbl -> SenderCallbackAdd(This,_pCallback,_llCallbackUserData) ) 

#define IMSender_I_SenderCallbackRemove(This,_pCallback)	\
    ( (This)->lpVtbl -> SenderCallbackRemove(This,_pCallback) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMSender_I_INTERFACE_DEFINED__ */


#ifndef __IMReceiver_I_INTERFACE_DEFINED__
#define __IMReceiver_I_INTERFACE_DEFINED__

/* interface IMReceiver_I */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMReceiver_I;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F367A10-473F-4ad5-A5C2-428FE0C8E03E")
    IMReceiver_I : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MediaReceive( 
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ IUnknown *_pSender,
            /* [in] */ IMFrame_I *_pFrame) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MediaEnd( 
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ IUnknown *_pSender,
            /* [in] */ DWORD _dwFlags) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MediaFlush( 
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ IUnknown *_pSender,
            /* [in] */ DWORD _dwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMReceiver_IVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMReceiver_I * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMReceiver_I * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMReceiver_I * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *MediaReceive )( 
            IMReceiver_I * This,
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ IUnknown *_pSender,
            /* [in] */ IMFrame_I *_pFrame);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *MediaEnd )( 
            IMReceiver_I * This,
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ IUnknown *_pSender,
            /* [in] */ DWORD _dwFlags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *MediaFlush )( 
            IMReceiver_I * This,
            /* [in] */ BSTR _bsChannelID,
            /* [in] */ IUnknown *_pSender,
            /* [in] */ DWORD _dwFlags);
        
        END_INTERFACE
    } IMReceiver_IVtbl;

    interface IMReceiver_I
    {
        CONST_VTBL struct IMReceiver_IVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMReceiver_I_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMReceiver_I_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMReceiver_I_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMReceiver_I_MediaReceive(This,_bsChannelID,_pSender,_pFrame)	\
    ( (This)->lpVtbl -> MediaReceive(This,_bsChannelID,_pSender,_pFrame) ) 

#define IMReceiver_I_MediaEnd(This,_bsChannelID,_pSender,_dwFlags)	\
    ( (This)->lpVtbl -> MediaEnd(This,_bsChannelID,_pSender,_dwFlags) ) 

#define IMReceiver_I_MediaFlush(This,_bsChannelID,_pSender,_dwFlags)	\
    ( (This)->lpVtbl -> MediaFlush(This,_bsChannelID,_pSender,_dwFlags) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMReceiver_I_INTERFACE_DEFINED__ */



#ifndef __MPLATFORMLib_LIBRARY_DEFINED__
#define __MPLATFORMLib_LIBRARY_DEFINED__

/* library MPLATFORMLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MPLATFORMLib;

#ifndef __IMEvents_DISPINTERFACE_DEFINED__
#define __IMEvents_DISPINTERFACE_DEFINED__

/* dispinterface IMEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID_IMEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("4F365161-473F-4ad5-A5C2-428FE0C8E03E")
    IMEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IMEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IMEventsVtbl;

    interface IMEvents
    {
        CONST_VTBL struct IMEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IMEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MFactory;

#ifdef __cplusplus

class DECLSPEC_UUID("4F365100-473F-4ad5-A5C2-428FE0C8E03E")
MFactory;
#endif

EXTERN_C const CLSID CLSID_MFrame;

#ifdef __cplusplus

class DECLSPEC_UUID("4F365160-473F-4ad5-A5C2-428FE0C8E03E")
MFrame;
#endif

EXTERN_C const CLSID CLSID_MFrames;

#ifdef __cplusplus

class DECLSPEC_UUID("4F365165-473F-4ad5-A5C2-428FE0C8E03E")
MFrames;
#endif

EXTERN_C const CLSID CLSID_MNode;

#ifdef __cplusplus

class DECLSPEC_UUID("4F365099-473F-4ad5-A5C2-428FE0C8E03E")
MNode;
#endif

EXTERN_C const CLSID CLSID_MProxy;

#ifdef __cplusplus

class DECLSPEC_UUID("4985960B-08F5-4C7A-B439-3255A8A8E9E4")
MProxy;
#endif

EXTERN_C const CLSID CLSID_MPacker;

#ifdef __cplusplus

class DECLSPEC_UUID("4985960F-08F5-4C7A-B439-3255A8A8E9E4")
MPacker;
#endif

EXTERN_C const CLSID CLSID_MSync;

#ifdef __cplusplus

class DECLSPEC_UUID("49859610-08F5-4C7A-B439-3255A8A8E9E4")
MSync;
#endif

EXTERN_C const CLSID CLSID_MSenders;

#ifdef __cplusplus

class DECLSPEC_UUID("A8C0EEAA-0E52-4F1F-AFCC-BBCB26587B73")
MSenders;
#endif

EXTERN_C const CLSID CLSID_MPreview;

#ifdef __cplusplus

class DECLSPEC_UUID("4985960C-08F5-4C7A-B439-3255A8A8E9E4")
MPreview;
#endif

EXTERN_C const CLSID CLSID_MFile;

#ifdef __cplusplus

class DECLSPEC_UUID("34CE4E44-20ED-4811-A3A2-80738A171F20")
MFile;
#endif

EXTERN_C const CLSID CLSID_MItem;

#ifdef __cplusplus

class DECLSPEC_UUID("34CE4E46-20ED-4811-A3A2-80738A171F20")
MItem;
#endif

EXTERN_C const CLSID CLSID_MPlaylist;

#ifdef __cplusplus

class DECLSPEC_UUID("34CE4E54-20ED-4811-A3A2-80738A171F20")
MPlaylist;
#endif

EXTERN_C const CLSID CLSID_MLive;

#ifdef __cplusplus

class DECLSPEC_UUID("84494D2B-A9ED-482C-A147-03F6675342C3")
MLive;
#endif

EXTERN_C const CLSID CLSID_MRenderer;

#ifdef __cplusplus

class DECLSPEC_UUID("1417F704-2CFA-44E5-8517-20BF16016761")
MRenderer;
#endif

EXTERN_C const CLSID CLSID_MElement;

#ifdef __cplusplus

class DECLSPEC_UUID("34CE4E74-20ED-4811-A3A2-80738A171F20")
MElement;
#endif

EXTERN_C const CLSID CLSID_MMixer;

#ifdef __cplusplus

class DECLSPEC_UUID("34CE4E64-20ED-4811-A3A2-80738A171F20")
MMixer;
#endif

EXTERN_C const CLSID CLSID_MComposer;

#ifdef __cplusplus

class DECLSPEC_UUID("34CE4E64-30ED-4811-A3A2-80738A171F20")
MComposer;
#endif

EXTERN_C const CLSID CLSID_MWriter;

#ifdef __cplusplus

class DECLSPEC_UUID("C691860F-9C67-4D10-A275-2061E94F3B39")
MWriter;
#endif
#endif /* __MPLATFORMLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


