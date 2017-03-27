//==============================================================================
//
// (c) Copyright Matrox Electronic Systems Ltd., 2003-2015. All rights reserved. 
//
// This code and information is provided "as is" without warranty of any kind, 
// either expressed or implied, including but not limited to the implied 
// warranties of merchantability and/or fitness for a particular purpose.
//
// Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make 
// changes in specifications and code at any time and without notice. 
// No responsibility is assumed by Matrox Electronic Systems Ltd. for 
// its use; nor for any infringements of patents or other rights of 
// third parties resulting from its use. No license is granted under 
// any patents or patent rights of Matrox Electronic Systems Ltd.
//
//-------------------------------------------------------------------------------


#pragma once

#ifndef LINUX_PLATFORM
#include <windows.h>
#pragma warning(disable : 4201)
#include <mmsystem.h>
#pragma warning(default : 4201)
#endif

#include "MvFlexDefinitionsPublicSDK.h"
#include <list>

//
// forward declarations
//
interface IMvCustomFileSystemIO;
interface IMvMpegStreamMemoryProvider;
interface IMvSurface;
interface IMvAudioSamples;
interface IMvAACCodecConfigDataAccess;
interface IMvOutputStream;
interface IMvTopology;

const unsigned long kulInitialNumberOfElements                 = 5;
const unsigned long kulMvMaxSupportedCodecFormats              = 30; // this is there because we need a size, increase it if you need more
const unsigned long kulMvMaxSupportedUncompressedFormats       = 32;
const unsigned long kulMvMaxSupportedUncompressedResolutions   = 32;
const unsigned long kulMvMaxSupportedCompressedResolutions     = 32;
const uint32_t      kui32MaxNumberOfAudioTracks                = 16;
const uint32_t      kui32MaxConnectorQuadrants                 = 4;

#define AVCINTRA_HEADER_SIZE 512         //by AVCIntra spec.

#define kMvUniversalMediaPosition 0xffffffff

typedef BYTE *MVCHANDLE;
typedef BYTE *MVCPHANDLE;

// Summary:
// Specifies the bit rate encoding option for the MPEG-2 muxer.
// Remarks:
// - If DVB-ASI is used to output the transport stream buffers, use keMvMPEG2MuxerBitRateOptionCBR.
enum EMvMPEG2MuxerBitRateOption
{
   keMvMPEG2MuxerBitRateOptionInvalid, // Invalid value.
   keMvMPEG2MuxerBitRateOptionCBR,     // Constant bit rate (CBR) encoding option in which NULL packets are added to ensure that the bit rate is constant.
   keMvMPEG2MuxerBitRateOptionVBR,     // Variable bit rate (VBR) encoding option in which NULL packets are not added.
   keMvMPEG2MuxerBitRateOptionLast     // End of list indicator.
};

// Summary:
// Specifies the VANC processing type of the MPEG-2 muxer.
// Currently only SCTE 35 streams are supported.
//
enum EMvMPEG2MuxerVancProcessingType
{
   keMvMPEG2MuxerVancProcessingTypeInvalid,  // Invalid value.
   keMvMPEG2MuxerVancProcessingTypeNone,     // No VANC processing is required.
   keMvMPEG2MuxerVancProcessingTypeSCTE35,   // Specifies that SCTE 35 streams are to be processed.
   keMvMPEG2MuxerVancProcessingTypeLast      // End of list indicator.
};

//
// Summary:
//    Describes a picon found in a GFX file.
//
enum EMvPiconID
{
   keMvPiconIDInvalid = 0,    // Invalid value.
   keMvPiconIDDefault,        // The picon found is the default one.
   keMvPiconIDLast            // End of list Indicator.
};

//
// Summary:
//    Specifies the playlist type.
//
// Remarks:
//    - More than one type can be specified by using the bitwise OR operator.
//
enum EMvPlayListType
{
   keMvPlayListTypeInvalid       = 0,  // The first element is 0 and invalid.
   keMvPlayListTypeVideo         = 1,  // Specifies a video-only playlist.
   keMvPlayListTypeAudio         = 2,  // Specifies an audio-only playlist.
   keMvPlayListTypeAVInterleaved = 3   // Specifies an AVI-only playlist.
};

//
// Summary:
//    Specifies the work audio samples type.
//
enum EMvWorkAudioSamplesType
{
   keMvWorkAudioSamplesTypeInvalid                = 0x00000000,   // Invalid work audio samples type.
   keMvWorkAudioSamplesTypeEditRes                = 0x00000001,   // Specifies a standard audio samples type for the current edit resolution.
   keMvWorkAudioSamplesTypeLast                   = 0x00000004,   // End of list indicator.
   keMvWorkAudioSamplesTypeForceDWord             = 0x7FFFFFFF    // Forces the enumerated values to be 32 bits.
};

//
// Summary:
//    Specifies the work surface type.
//
enum EMvWorkSurfaceType
{
   keMvWorkSurfaceTypeInvalid = 0x00000000,              // Invalid value.       
   keMvWorkSurfaceTypeEditResFrameARGBVideo_AllMipmaps,  // Specifies an RGBA-video work surface allocated 
   // at the edit resolution in frames with all mipmaps.
   keMvWorkSurfaceTypeEditResFieldARGBVideo_AllMipmaps,  // Specifies an RGBA-video work surface allocated
   // at the edit resolution in fields with all mipmaps.
   keMvWorkSurfaceTypeEditResARGBVideo_AllMipmaps,       // Specifies an RGBA-video work surface allocated 
   // at the edit resolution with all mipmaps. Will be 
   // allocated in frames or fields depending on the scan 
   // mode of the editing resolution.
   keMvWorkSurfaceTypeEditRes24Z8S,                      // Specifies a depth work surface allocated at the
   // edit resolution with 24 bits of Z and 8 bits of stencil.
   keMvWorkSurfaceTypeAlphaRamp8bits,                    // Specifies a 256x1 alpha 8-bit surface. No mipmaps are allocated.
   keMvWorkSurfaceType1DBorder,                          // Specifies an RGBA-video surface allocated at the 
   // half edit resolution width and a height of 2. No mipmaps are allocated.
   keMvWorkSurfaceTypeLast,                              // End of list indicator.
   keMvWorkSurfaceTypeForceDWord = 0x7FFFFFFF            // Force the enumerated values to be 32 bits.
};

//
// Summary:
//    Specifies whether to capture both video and audio, or video only. 
//
enum EMvVideoAudioBufferType
{
   keMvVideoAudioBufferTypeInvalid,    // Invalid buffer type.
   keMvVideoAudioBufferTypeVideoAudio, // Capture both video and audio.
   keMvVideoAudioBufferTypeVideoOnly,  // Capture video only.
   keMvVideoAudioBufferLast            // End of list indicator.
};

//
// Summary:
//    Specifies whether to save audio as stereo or mono in each track. 
//
enum EMvPCMMovAudioStreamSaveType
{
   kePCMMovAudioStreamSaveTypeInvalid           = 0,  // Invalid value.
   kePCMMovAudioStreamSaveTypeMono              = 1,  // Audio data will be saved as mono in each track.
   kePCMMovAudioStreamSaveTypeStereo            = 2,  // Audio data will be saved as stereo in each track.
   kePCMMovAudioStreamSaveTypeLast                    // End of list indicator.
};

// 
// Summary:
//    Used to set or get codec options.
//
// Remarks:
//    - The last character in the enum specifies the type of parameter to pass when calling 
//      SetCodecOption(), GetCodecOption(), or IsCodecOptionSupported(). For example, 'b' is for bool,
//      'ul' is for unsigned long, and 'st' is for structure.
//
enum EMvCodecOption
{
   keMvCodecOptionInvalid,                               // Invalid value.
   keMvCodecOptionDvFilteringPAL420_b,                   // Sets the DV codec PAL 4:2:0 decode to filter (used when chroma key is applied to the output buffer).
   keMvCodecOptionReturnErrorOnCorruption_b,             // Enables error reporting when the data to decode 
   // is corrupted. By default, the codec handles the 
   // corruption and does not put an error in the output surface.
   keMvCodecOptionMpeg2CompressionOptions_st,            // Used to pass the compression configuration structure for the MPEG-2 codec.
   keMvCodecOptionIbpDecodeLastFrame_b,                  // Indicates if the last IBP frame has to be decoded.
   keMvCodecOptionAspectRatio_e,                         // Sets the aspect ratio if it is different from the usual default for the current settings.
   keMvCodecOptionAACDecompressionOptionInit_st,         // Provides the information necessary to initialize the AAC codec during decompression.
   keMvCodecOptionAACCompressionOptionInit_st,           // Sets the options that will be used by the AAC codec during compression.
   keMvCodecOptionPreroll_ui64,                          // Used to get the preroll of the codec. This is mostly for hardware codecs. It depends on the codec usage (compression or decompression).
   keMvCodecOptionCompletionCallback_pI,                 // Sets the completion callback interface that will be called not when the data is ready, but when the description is valid on the surface.  This is mainly used during compression with VBR mode.
   keMvCodecOptionHWAVCH264DecompressionOptionInit_st,   // Provides the information necessary to initialize the H.264/AVC hardware codec during decompression.
   keMvCodecOptionHWAVCH264CompressionOptionInit_st,     // Provides the information necessary to initialize the H.264/AVC hardware codec during compression.
   keMvCodecOptionGetCompressionPipelineDepth_ui32,      // Indicates the required number of audio samples or frames that must be fed to the encoder before data can be output.
   keMvCodecOptionGetDecompressionPipelineDepth_ui32,    // Indicates the required number of audio samples or frames that must be fed to the decoder before data can be output.
   keMvCodecOptionGetAVCH264CompressionGOPStructure_st,  // Indicates the organization of a compressed GOP (IDR, I, P, B), if there is one.
   keMvCodecOptionGetPropagationDelay_ui64,              // Used to get the propagation delay of the codec.  This is mostly for hardware codecs. It depends on the codec usage (compression or decompression).
   keMvCodecOptionStartPreroll_ui64,                     // Used to get the start preroll of the codec.  This is mostly for hardware codecs. It depends on the codec usage (compression or decompression).  The start preroll needs to be respected for the first frame only while the preroll needs to be respected for every frame (including the first one).
   keMvCodecOptionOptimalNumOfAdvancedPuts_ui32,         // Indicates the optimal number of advanced Puts() relative to Gets().
   keMvCodecOptionMaxPropagationDelayByFrames_ui32,      // Indicates the maximum propagation delay in frame units.
   keMvCodecOptionGetNearestSupportedShuttlingSpeed_st,  // From a given speed, the codec will return what is the nearest speed it can really achieve.
   keMvCodecOptionAVCIntraCompressionOptions_st,         // Provides compression options for the AVC-Intra encoder.
   keMvCodecOptionH264SWDecompressionOptions_st,         // Provides decompression options for the H.264/AVC software decoder.
   keMvCodecOptionProResCompressionOptions_st,           // Provides compression options for the ProRes encoder.
   keMvCodecOptionProResDecompressionOptions_st,         // Provides decompression options for the ProRes decoder.
   keMvCodecOptionMaxCompressedFrameSizeByBytes_ui32,    // Provides the maximum size of a compressed frame from the video encoder.
   keMvCodecOptionDNxHDCompressionOptions_st,            // Provides compression options for the DNxHD encoder.
   keMvCodecOptionDNxHDDecompressionOptions_st,          // Provides decompression options for the DNxHD decoder.
   keMvCodecOptionNTSCClosedCaptionOutputFormat_e,       // Indicates how the codec should output closed caption data when reading NTSC.
   keMvCodecOptionDolbyEDecompressionOptionInit_st,      // Provides decompression options for the Dolby E decoder.
   keMvCodecOptionDolbyECompressionOptionInit_st,        // Provides compression options for the Dolby E encoder.
   keMvCodecOptionDolbyEUserInterface_h,                 // Provides the parent window with a handle to display the Dolby E configuration window.
   keMvCodecOptionDolbyESettings_st,                     // Sets or gets the current Dolby E settings.
   keMvCodecOptionProRes4444CaptureWithAlpha_b,          // Indicates whether or not ProRes 4444 capture will include alpha (alpha is optional).
   KeMvCodecOptionTargetCompressedFrameSizeByBytes_ui32, // Provides the target size of a compressed frame from the video encoder.
   keMvCodecOptionH264CompressionOptions_st,             // Provides compression options for the H.264/AVC software and QSV (Intel Quick Sync Video) encoders.
   keMvCodecOptionMPEG4SStPCompressionOptions_st,        // Provides compression options for the Sony MPEG-4 Simple Studio Profile encoder.
   keMvCodecOptionMPEG4SStPDecompressionOptions_st,      // Provides decompression options for the the Sony MPEG-4 Simple Studio Profile decoder.
   keMvCodecOptionCompletionObserver_pI,                 // Provides a completion observer object to be notified when an operation is completed (e.g. close decompression stream)
   keMvCodecOptionH264SWCompressionOptions_st,           // Provides compression options for the H.264/AVC software encoder.
   keMvCodecOptionM264CompressionOptions_st,             // Provides compression options for the M264 hardware encoder.
   keMvCodecOptionCodecReturnsCompressedFields_b,        // Indicates if the codec returns compressed fields(true) or frames (false)
   keMvCodecOptionExtraH264CompressionOptions_st,        // Gets extra settings from the codec which are not in the regular compression options
   keMvCodecOptionM264DecompressionOptions_st,        // Provides options for the H.264 hardware decoder (SV2).
   keMvCodecOptionForceOutputObserver_pI,                // Provides an observer object to be notified when the all the frames have been output.
   keMvCodecOptionFlushObserver_pI,                      // Provides an observer object to be notified when the all the frames have been output from the decoder after calling Flush()
   keMvCodecOptionAsyncErrorCallback_pI,                 // Provides a callback for asynchronous errors from the codec
   keMvCodecOptionLast                                   // Number of codec options + 1.  End of list indicator.
};


// This macro is used to get the string corresponding to the EMvCodecOption enum value.
#define MV_CODEC_OPTION_ENUM_TO_STRING(eMvCodecOption) \
   ((eMvCodecOption == keMvCodecOptionInvalid) ? ("Invalid") : \
   (eMvCodecOption == keMvCodecOptionDvFilteringPAL420_b) ? ("Dv Filtering for PAL 420") : \
   (eMvCodecOption == keMvCodecOptionReturnErrorOnCorruption_b) ? ("Return error on Corruption") : \
   (eMvCodecOption == keMvCodecOptionMpeg2CompressionOptions_st) ? ("Mpeg2 Compression Options") : \
   (eMvCodecOption == keMvCodecOptionIbpDecodeLastFrame_b) ? ("IBP Decode last frame") : \
   (eMvCodecOption == keMvCodecOptionAspectRatio_e) ? ("Aspect Ratio") : \
   (eMvCodecOption == keMvCodecOptionAACDecompressionOptionInit_st) ? ("AAC Decompression Option (Init)") : \
   (eMvCodecOption == keMvCodecOptionAACCompressionOptionInit_st) ? ("AAC Compression Option (Init)") : \
   (eMvCodecOption == keMvCodecOptionPreroll_ui64) ? ("Preroll") : \
   (eMvCodecOption == keMvCodecOptionCompletionCallback_pI) ? ("Completion Callback") : \
   (eMvCodecOption == keMvCodecOptionHWAVCH264DecompressionOptionInit_st) ? ("AVC/H.264 Decompression Option (Init)") : \
   (eMvCodecOption == keMvCodecOptionHWAVCH264CompressionOptionInit_st) ? ("AVC/H.264 Compression Option (Init)") : \
   (eMvCodecOption == keMvCodecOptionGetCompressionPipelineDepth_ui32) ? ("AAC Compression Pipeline Depth") : \
   (eMvCodecOption == keMvCodecOptionGetDecompressionPipelineDepth_ui32) ? ("AAC Decompression Pipeline Depth") : \
   (eMvCodecOption == keMvCodecOptionGetAVCH264CompressionGOPStructure_st) ? ("AVC/H.264 Compression GOP Structure") : \
   (eMvCodecOption == keMvCodecOptionGetPropagationDelay_ui64) ? ("Propagation Delay") : \
   (eMvCodecOption == keMvCodecOptionStartPreroll_ui64) ? ("Start preroll") : \
   (eMvCodecOption == keMvCodecOptionOptimalNumOfAdvancedPuts_ui32) ? ("Optimal number of puts in advance") : \
   (eMvCodecOption == keMvCodecOptionMaxPropagationDelayByFrames_ui32) ? ("Max propagation delay in frames") : \
   (eMvCodecOption == keMvCodecOptionGetNearestSupportedShuttlingSpeed_st) ? ("Get Nearest supported shuttling speed") : \
   (eMvCodecOption == keMvCodecOptionH264CompressionOptions_st) ? ("H.264 Compression Option") : \
   (eMvCodecOption == keMvCodecOptionCodecReturnsCompressedFields_b) ? ("Returns fields") : \
   (eMvCodecOption == keMvCodecOptionExtraH264CompressionOptions_st) ? ("Get Additional H.264 Compression settings") : \
   (eMvCodecOption == keMvCodecOptionLast) ? ("Last") : \
   ("???"))

//
// Summary:
//    Describes the number of reference frames and the total number of frames in the GOP.
//
struct SMvGroupOfPicturesDescription
{
   uint32_t   size;                            // Size of the structure.
   unsigned long ulNumberOfReferenceFrames;  // Number of I and P frames in the GOP.
   unsigned long ulTotalNumberOfFrames;      // Total number of frames in the GOP.
};

//
// Summary:
//    Describes MPEG-2 sequence header.
//
struct SMvMpeg2SeqHeader
{
   unsigned long    ulHSize;
   unsigned long    ulVSize;
   unsigned long    ulAspectRatio;
   unsigned long    ulFrameRate;
   unsigned long    ulBitRate;
   unsigned long    ulVBVSize;
   unsigned long    ulConstParams;
   unsigned long    ulTableScale;
   unsigned long    ulIQuant;
   unsigned char    aucIQuantTable[64];
   unsigned long    ulNIQuant;
   unsigned char    aucNIQuantTable[64];
};

//
// Summary:
//    Describes MPEG-2 sequence header extension.
//
struct SMvMpeg2SeqExt 
{
   unsigned long ulProfile;
   unsigned long ulLevel;
   unsigned long ulProgSeq;
   unsigned long ulChromaFormat;
   unsigned long ulHSizeExt;
   unsigned long ulVSizeExt;
   unsigned long ulBitRateExt;
   unsigned long ulVBVSizeExt;
   unsigned long ulLowDelay;
};

//
// Summary:
//    Describes MPEG-2 sequence header and sequence extension.
//
struct SMvMpeg2SeqHeaderInfo
{
   uint32_t            size;
   SMvMpeg2SeqHeader   sSeqHeader; 
   SMvMpeg2SeqExt      sSeqExt;    
};


//
// Summary:
//    Describes the information for the available codecs.
//
struct SMvCodecInfo
{
   uint32_t             size;                                                 // Structure size in bytes.
   wchar_t              wszCodecName[256];                                    // Name of the codec.
   GUID                 CodecGUID;                                            // Specifies the unique identifier of the codec.
   unsigned long        ulSupportedFormatCount;                               // Number of valid structures in the array saCodecCapabilities.
   SMvCodecCapabilities saCodecCapabilities[kulMvMaxSupportedCodecFormats];   // Array of structures describing codec capabilities.
};

//
// Summary:
//    Describes the options desired for conversion.
//
struct SMvConversionOptions
{
   uint32_t size;                // Size of the structure.
   BOOL     bUseFiltering;       // Specifies if chrominance filtering is desired when converting an ARGB 
   // surface to YUYV422.
   BOOL     bUseInterpolation;   // Specifies if chrominance interpolation is desired when converting an 
   // YUYV422 or YUAYVA4224 surface to an ARGB surface.
};

//
// Summary:
//    Describes thread pool information.
//
struct SMvThreadPoolInfo
{
   unsigned long   ulNbThreadPool;        // Number of thread pool(s). The maximum thread pool number is three and the minimum is one.
   unsigned long * aulThreadPoolPriority; // Array of priority for each thread pool.
};

// DOM-IGNORE-BEGIN
//
// Summary:
//    For future release.
//
struct SMvAudioEffectCapabilities
{
   uint32_t size;                            // Size of the structure.
   bool     bUseKeyFrames;                   
   GUID     guidEffectGUID;                  
   GUID     guidDefaultParametricEffectGUID; 
   unsigned long ulVersion;                  
};
// DOM-IGNORE-END


//
// Summary:
//    Describes the hardware profile information and the editing resolution.
//
struct SMvEngineProfileInfo
{
   uint32_t                   size;                   // Size of the structure.
   SMvHardwareProfileInfo     sHardwareProfileInfo;   // Describes the hardware profile on which the 
   // Flex Engine is created.
   SMvResolutionInfo          sEditResolution;        // Structure that defines the editing resolution.
};

//
// Summary:
//    Describes the stereo volume/pan gains at the start and end of a video unit (one field or one frame).
// Remarks:
// - The volume gain is a floating point factor of the original volume value. A value of 1.0f will
//   not change the volume. A value of 0.0f will generate silence. A value of 2.0f will multiply by
//   2 the amplitude and thus double the original volume value (+6dB).
// - A volume gain specified in this structure must be superior or equal to 0.0f and inferior to 8.0f (<18dB).
// - Functional Diagram
//
// <CODE>
//       Lin-------o--->(Lin * fLeftToLeft)-----------(+)-----> Lout = Lin*fLeftToLeft + 
//                 |                                   ^               Rin*fRightToLeft
//       Rin---o------->(Rin * fRightToLeft)-----------|
//             |   |
//             |   |
//             |   |
//             |   |--->(Lin * fLeftToRight)-----------|
//             |                                       v
//             |------->(Rin * fRightToRight)---------(+)-----> Rout = Lin*fLeftToRight +
//                                                                     Rin*fRightToRight
// </CODE>

struct SMvAudioMixerInfo
{
   uint32_t Size;                   // Size of the structure.
   float    fLeftToLeftInitial;     // Initial gain of input left channel to send to left channel output.
   float    fLeftToLeftFinal;       // Final gain of input left channel to send to left channel output.    

   float    fLeftToRightInitial;    // Initial gain of input left channel to send to right channel output.     
   float    fLeftToRightFinal;      // Final gain of input left channel to send to right channel output.    

   float    fRightToRightInitial;   // Initial gain of input right channel to send to right channel output.   
   float    fRightToRightFinal;     // Final gain of input right channel to send to right channel output.    

   float    fRightToLeftInitial;    // Initial gain of input right channel to send to left channel output.   
   float    fRightToLeftFinal;      // Final gain of input right channel to send to left channel output.    
};

//
// Summary:
//    Describes the volume gain at the start and end of a video unit (one field or one frame).
// Remarks:
// - The volume gain is a floating point factor of the original volume value. A value of 1.0f will
//   not change the volume. A value of 0.0f will generate silence. A value of 2.0f will multiply by
//   2 the amplitude and thus double the original volume value (+6dB).
//
//
struct SMvAudioMonoVolumeInfo
{
   uint32_t Size;          // Structure size in bytes.
   float    fInitialGain;  // Volume gain at the beginning of the video unit.
   float    fFinalGain;    // Volume gain at the end of the video unit.
};

//
// Summary:
//    Specifies the NTSC closed captioning format used.
//
enum EMvNTSCClosedCaptionFormat
{
   keMvNTSCClosedCaptionFormatInvalid,       // Invalid value.
   keMvNTSCClosedCaptionFormatLine21   = 1,  // Indicates that the NTSC closed caption format will be output as CEA-608 (analog line 21). 
   keMvNTSCClosedCaptionFormatDigital  = 2,  // Indicates that the NTSC closed caption format will be output as SMPTE 334 caption data packet (CDP).
   keMvNTSCClosedCaptionFormatBoth     = 3,  // Indicates that both NTSC closed caption formats CEA-608 (analog line 21) and SMPTE 334 CDP will be output.
   keMvNTSCClosedCaptionFormatLast           // End of list indicator.
};

#define MV_NTSC_CLOSE_CAPTION_FORMAT_ENUM_TO_STRING(eValue) \
   ((eValue == keMvNTSCClosedCaptionFormatInvalid) ? _T("Invalid") : \
    (eValue == keMvNTSCClosedCaptionFormatLine21) ? _T("Line 21") : \
    (eValue == keMvNTSCClosedCaptionFormatDigital) ? _T("Digital") : \
    (eValue == keMvNTSCClosedCaptionFormatBoth) ? _T("Line 21 and digital") : \
    (eValue == keMvNTSCClosedCaptionFormatLast) ? _T("Last") : \
   _T("???"))
#define MV_MXO_ANALOG_NTSC_IRE_LEVEL_ENUM_TO_STRING MV_ANALOG_NTSC_IRE_LEVEL_ENUM_TO_STRING


//
// Summary:
//    Specifies the type of VANC format.
//
enum EMvVANCFormatType
{
   keMvVancFormatTypeInvalid,           // Invalid value.
   keMvVancFormatTypeLegacy,            // Indicates that the YUV422 VANC surface format is used.
   keMvVancFormatTypeMatroxAncillary,   // Indicates that the MatroxAncillaryDataFormat VANC surface format is used.
   keMvVancFormatTypeLast               // End of list indicator.
};

#define MV_VANC_FORMAT_TYPE_ENUM_TO_STRING(eValue) \
   ((eValue == keMvVancFormatTypeInvalid) ? _T("Invalid") : \
    (eValue == keMvVancFormatTypeLegacy) ? _T("YUYV422(Legacy)") : \
    (eValue == keMvVancFormatTypeMatroxAncillary) ? _T("Matrox ancillary") : \
    (eValue == keMvVancFormatTypeLast) ? _T("Last") : \
   _T("???"))
#define MV_MXO_ANALOG_NTSC_IRE_LEVEL_ENUM_TO_STRING MV_ANALOG_NTSC_IRE_LEVEL_ENUM_TO_STRING

//
// Summary:
//    Describes VANC specific playlist initialization settings for the Flex File Reader.
//
struct SMvVANCPlaylistOptions
{
   uint32_t                   size;
   EMvNTSCClosedCaptionFormat eNTSCCaptionsFormat; // Defaults to Line 21.
   EMvVANCFormatType          eVANCFormatType;     // Defaults to legacy.
};

//
// Summary:
//    Describes the playlist initialization settings for the Flex File Reader.
//
struct SMvPlaylistConfiguration
{
   uint32_t       size;                // Specifies the size of the structure in bytes.
   unsigned long  ulWidth;             // Maximum expected resolution width to be present in the playlist.
   // Used by the Flex File Reader to compute memory allocations.
   unsigned long  ulHeight;            // Maximum expected resolution height to be present in the playlist.
   // Used by the Flex File Reader to compute memory allocations.
   unsigned long  ulComponentBitCount; // Maximum expected bit depth to be present in the playlist.
   // Used by the Flex File Reader to compute memory allocations.
   bool           bVideo;              // Specifies whether or not the playlist contains video elements.
   bool           bAudio;              // Specifies whether or not the playlist contains audio elements.
   bool           bVBI;                // Specifies whether or not the playlist contains VBI elements.
   bool           bKey;                // Specifies whether or not the playlist can contain 4:2:2:4 elements, 
   bool           bTimeCode;           // Specifies whether or not the playlist contains time code elements
   // which increases memory usage.
   EMvFrameRate   eFrameRate;          // Frame rate associated with the playlist. All elements must respect 
   // this frame rate.
   EMvScanMode    eScanMode;           // Scan mode associated with the playlist. All elements must respect 
   // this scan mode.
   EMvSurfaceFormat eConsolidationSurfaceFormat;   // Compressed format to return in IMvFlexReader::GetBuffer, 
   // if any is used for consolidation.  When the file's
   // format does not match this value, uncompressed data 
   // is returned.  Using keMvSurfaceFormatInvalid will
   // always return uncompressed video data.
   bool           bSpecifyWhichCodecsToInitialize;  // tells the flex reader that the user application wants to select which codecs it will use below.
   const CLSID*   aclsidCodecsToInitialize[kulMvMaxSupportedCodecFormats]; // Array of CLSIDs containing the list of codecs that the user application
   // expects to use. This will optimize the flex reader codec allocation.
   // Hardware codecs should only be included in this list IF the user application
   // intends to use them. 
   unsigned long  ulCountOfClsidCodecsToInitialize; // number of elements in aclsidCodecsToInitialize.
   SMvVANCPlaylistOptions sVANCOptions; // Options related to VANC and Vbi. Unused if the bVbi flag is set to false.   
};

//
// Summary:
//    Specifies the Flex File Writer capture type. <p> <b>Note:</b> More than one type can be specified by using the bitwise OR operator.
//
enum EMvFlexWriterCaptureType
{
   keTypeInvalid                          = 0x00000000, // Invalid value.
   keTypeVideo                            = 0x00000001, // Capture contains uncompressed video.
   keTypeAudio                            = 0x00000002, // Capture contains audio.
   keTypeVBI                              = 0x00000004, // Capture contains VBI.
   keTypeTimeCode                         = 0x00000008, // Capture contains time code data.
   keFileTypeMPG                          = 0x00000010, // Capture contains MPG data.
   keFileTypeMXF_P2                       = 0x00000020, // Capture contains MXF P2 data.
   keFileTypeMXF_XDCam_DV                 = 0x00000040, // Capture contains MXF XDCAM DV data.
   keFileTypeMXF_XDCam_D10                = 0x00000080, // Capture contains MXF XDCAM D10 data.
   keFileTypeMXF_XDCam_HD                 = 0x00000100, // Capture contains MXF XDCAM HD data.
   keFileTypeMXF_Mpeg2                    = 0x00000400, // Obsoleted. Use keFileTypeMXF_Mpeg2_SparseIndex.
   keFileTypeMXF_Mpeg2_SparseIndex        = 0x00000400, // Capture contains MXF Generic Mpeg2 data which index sparse inside the file.
   keFileTypeMXF_DVCPRO                   = 0x00000800, // Capture contains MXF DVCPro data.
   keFileTypeMXF_AVCIntra                 = 0x00001000, // Capture contains MXF AVCIntra OP1a data.
   keFileTypeMXF_DNxHD                    = 0x00002000, // Capture contains MXF DNxHD OP1a data.
   keVANCTypeLegacy                       = 0x00004000, // VANC format will be YUV422.
   keVANCTypeMatroxAncillary              = 0x00008000, // VANC format will be MatroxAncillaryDataFormat.
   keFileTypeMXF_AS11                     = 0x00010000, // Capture contains AS-11 wrapping.
   keFileTypeMXF_MPEG4SStP                = 0x00020000, // Capture contains MXF MPEG-4 Simple Studio Profile OP1a data.
   keFileTypeMXF_XAVC                     = 0x00040000, // capture contains XAVC data
   keFileTypeAVI                          = 0x00080000, // capture AVI container no matter what the extension is
   keFileTypeGXF                          = 0x00100000, // capture GXF container no matter what the extension is
   keFileTypeMOV                          = 0x00200000, // capture MOV container no matter what the extension is
   keFileTypeMP4                          = 0x00400000, // capture MP4 container no matter what the extension is
   keFileType264                          = 0x00800000, // capture 264 container no matter what the extension is
   keFileTypeWAV32                        = 0x01000000, // 32-bit WAV container
   keFileTypeWAV64                        = 0x02000000, // 64-bit WAV container
};

// DOM-IGNORE-BEGIN
// Internal use only.
enum EMvFlexWriterFileOpenMode
{
   keModeInvalid,
   keModeCreateAlways,
   keModeLast
};
// DOM-IGNORE-END

//
// Summary:
//    Specifies the MPEG-2 IBP frame type.
//
enum EMvIBPFrameType
{
   keMvMPEGIBP_Invalid = 0,   // Invalid value.
   keMvMPEGIBP_I,             // I-Frame.
   keMvMPEGIBP_B,             // B-Frame.
   keMvMPEGIBP_P,             // P-Frame.
   keMvMPEGIBP_OPENED_B,      // B-Frame requiring previous GOP for proper decoding.
   keMvMPEGIBP_Last           // End of list indicator.
};

//
// Summary:
//    Specifies the MPEG-2 multiplexing type.
//
enum EMvMpegstreamMultiplexerType
{
   keMvMPEG1,           // Generic ISO/IEC 11172-1/2.
   keMvVCD,             // Not implemented.
   keMvMPEG2,           // Generic ISO/IEC 13818-1/2.
   keMvSVCD,            // Not implemented.
   keMvDVD,             // Not implemented.
   keMvTS,              // Generic MPEG-2 transport stream, PAT and PMT only.
   keMvMpsReserved1,    // Reserved.
   keMvMpsReserved2,    // Reserved.
   keMvDVB,             // Not implemented.
   keMvMMV,             // Not implemented.
   keMvDVHS,            // Not implemented.
   keMvATSC,            // Not implemented.
   keMvATSCHI,          // Not implemented.
   keMvDVD_MPEG1,       // Not implemented.
   keMvDVD_DVR,         // Not implemented.
   keMvDVD_DVR_MPEG1,   // Not implemented.
   keMvDVD_PVR,         // Not implemented.
   keMvDVD_PVR_MPEG1,   // Not implemented.
   keMvHDV_HD1,         // Not implemented.
   keMvHDV_HD2,         // Not implemented.
   keMvD10_25,          // Not implemented.
   keMvD10_30,          // Not implemented.
   keMvD10_40,          // Not implemented.
   keMvD10_50,          // Not implemented.
   keMvCABLELABS,       // Not implemented.
   keMvHD_DVD,          // Not implemented.
   keMvBD,              // Not implemented.
   keMvBD_HDMV,         // Not implemented.
   keMvXDCAM_IMX,       // Not implemented.
   keMvXDCAM_IMX_25,    // Not implemented.
   keMvXDCAM_IMX_30,    // Not implemented.
   keMvXDCAM_IMX_40,    // Not implemented.
   keMvXDCAM_IMX_50,    // Not implemented.
   keMvXDCAM_HD,        // Not implemented.
   keMvXDCAM_1080_CBR_25,     // XDCAM MP@H-14  (25 Mbit CBR.)
   keMvXDCAM_1080_VBR_17_5,   // XDCAM MP@HL    (17.5 Mbit VBR).
   keMvXDCAM_1080_VBR_35,      // XDCAM MP@HL   (35 Mbit VBR).
   keMvXDCAM_540_CBR_12_5,    // Not implemented.
   keMvXDCAM_540_VBR_8_75,    // Not implemented.
   keMvXDCAM_540_VBR_17_5,    // Not implemented.
   keMvXDCAM_HD_420_1280,     // XDCAM HD MP@HL   4:2:0 1280x720   (35 Mbit VBR).
   keMvXDCAM_HD_422_1920,     // XDCAM HD 422P@HL 4:2:2 1920x1080  (50 Mbit CBR).
   keMvXDCAM_HD_422_1280,     // XDCAM HD 422P@HL 4:2:2 1280x720   (50 Mbit CBR).
   keMvXDCAM_EX_1920,        // XDCAM EX MP@ HL   4:2:0 1920x1080 (35 Mbit VBR).
   keMvXDCAM_EX_1440,        // XDCAM EX MP@ H-14 4:2:0 1440x1080 (25 Mbit CBR).
   keMvXDCAM_EX_1280,        // XDCAM EX MP@ HL   4:2:0 1280x720  (35 Mbit VBR).
   keMvMpegstreamMultiplexerTypeLast // End of list indicator.
};

//
// Summary:
//    Metadata related to a compressed frame inside an MPEG-2 IBP GOP.
//
struct SMvMpegStreamFrame
{
   uint32_t          size;                      // Structure size in bytes.
   unsigned long     ulOffsetInsideGopInBytes;  // Frame offset in bytes inside the GOP buffer.
   unsigned long     ulFrameSizeInBytes;        // Frame size in bytes inside the GOP buffer.
   unsigned long     ulDisplayOrder;            // Frame original display order.
   unsigned long     ulCodedOrder;              // Frame encoded order. May be different from the display order.
   EMvIBPFrameType   eType;                     // Frame type. Either an I, B, or P frame.
   uint64_t          ui64TimeCodeValue;         // Frame time code.
};

//
// Summary:
//    Specifies the MPEG-2 IBP motion estimation parameters.
//
struct SMvMpegStreamMotionData
{
   uint32_t size;               // Structure size in bytes.
   int    iForw_hor_f_code;   // Forward horizontal F code.
   int    iForw_vert_f_code;  // Forward vertical F code.
   int    iSxf;               // Forward search width.
   int    iSyf;               // Forward search height.
   int    iBack_hor_f_code;   // Backward horizontal F code.
   int    iBack_vert_f_code;  // Backward vertical F code.
   int    iSxb;               // Backward search width.
   int    iSyb;               // Backward search height.
};

//
// Summary:
//    Specifies video encoding parameters specific to the MPEG-1 and MPEG-2 IBP formats.
//
struct SMvMpegStreamEncoderSettings
{
   uint32_t          size;                               // Specifies the size of the structure in bytes.
   bool              bWriteSequenceHeaderBeforeEveryGop; // If true, a sequence header will be written before every GOP. Otherwise, it will be 
                                                         // written only at the beginning of the stream.
   EMvSurfaceFormat  eProfileAndLevel;                   // Indicates the IBP-type surface format used to express an MPEG-2 profile and MPEG-2 level.
   unsigned long     ulNumberOfBFramesBetweenIandP;      // Specifies the number of frames between consecutive I and P frames, including reference 
                                                         // frames. If set to 1, then no B frames will be generated. Valid range is [1, 8].
   unsigned long     ulNumberOfFramesBetweenI;           // Specifies the number of frames inside a GOP. The valid range is [1, 128], and the value  
                                                         // must be a multiple of the parameter ulNumberOfBFramesBetweenIandP. 
   unsigned long     ulClosedGopInterval;                // Specifies the distance between closed GOPs (<I>0</I> = every GOP is open, <I>1</I> = every GOP is closed, 
                                                         // <I>n</I> = every <I>n</I>th GOP is closed).
   bool              bConstantBitRate;                   // If true, constant bit rate (CBR) encoding will be used. Otherwise, variable bit rate (VBR) will be used.
   unsigned long     ulConstantBitRate;                  // If the bit rate is constant, this parameter specifies the target number of bits per 
                                                         // second to be generated by the encoder. The following limits should be observed for both 
                                                         // constant bit rate and variable bit rate encoding:<p>
                                                         // - 4:2:2 Profile, High Level = 300 000 000
                                                         // - 4:2:2 Profile, Main Level = 50 000 000
                                                         // - Main Profile, High Level 4:2:0 = 80 000 000
                                                         // - Main Profile, High Level-1440 4:2:0 = 60 000 000
                                                         // - Main Profile, Main Level 4:2:0, MPEG-1 = 15 000 000
   unsigned long     ulMaxBitRateVBROnly;                // If the bit rate is variable, specifies the maximum bit rate. For bit rate limits, 
                                                         // see the description for member ulConstantBitRate.
   unsigned long     ulAvgBitRateVBROnly;                // If the bit rate is variable, specifies the average bit rate. Set this value to 0 
                                                         // for VBR constant quantization.
   unsigned long     ulMinBitRateVBROnly;                // If the bit rate is variable, specifies the minimum bit rate. Set this value to 0 
                                                         // for VBR constant quantization.
   unsigned long     ulMQuant;                           // Macroblock quantization value used in VBR constant quantization. Valid range is [1, 31].
   unsigned long     ulFirstGopStartTimeCodeInFrames;    // Specifies the time code, expressed in frames, encoded into the first GOP header.
   bool              bOffline;                           // If true, quality is maintained at the expense of speed. Otherwise, speed is maintained at the expense of quality.
   unsigned long     ulQFactor;                          // Specifies the desired balance between quality and performance. Valid range is [1, 31]. 0 
                                                         // favors performance, 31 favors quality.
   bool              bZigZagScan;                        // Specifies the entropy scanning pattern defining the order in which quantized DCT (discrete 
                                                         // cosine transform) coefficients are run-length coded. <p> If true, the scan is zig-zag. Otherwise, the scan is alternate. 
                                                         // The default setting is false. Must be true for MPEG-1.
   unsigned long     ulDCPrecision;                      // Specifies the DC coefficient precision in intra-coded macroblocks. Valid range is [8, 10]. Default 
                                                         // value is 9. Value must be 8 for MPEG-1.
   bool              bMotionSearchHalfPel;               // If true, half-pel motion searching is used. Otherwise, false.
   unsigned long     ulMotionSearchType;                 // Specifies the type of motion searching used. Valid range is [0, 15]. 0 disables motion searching and 
                                                         // favors speed, while 15 favors quality.
   SMvMpegStreamMotionData asMotionData[9];              // Motion estimation parameters.

   EMvMPEG2Profile   eMpeg2Profile;                      // Profile for the MPEG-2 compression. Can be Main Profile or 4:2:2 Profile.
   EMvMPEG2Level     eMpeg2Level;                        // Level for the MPEG-2 compression. Can be Main Level, Main Level 4:2:0, High Level, or High Level-1440 4:2:0.

   EMvColorimetry    eColorimery;                        // Colorimetry of the video (MPEG-2 only).

   unsigned long     ulVbvBufferSize;                    // Size of the virtual buffer verifier in 2 KB (2048 bytes).

   bool              bLimitPicSizeFluctuations;          // If true, reduces the picture size variation between frames. Otherwise, false. Applies to CBR encoding only.

   bool              bEnabledHighQualityXDCAM;           // If true, improves the XDCAM HD/HD422 encoding quality by using more CPU processing. In this case, ulQFactor, bZigZagScan,
                                                         // ulDCPrecision, bMotionSearchHalfPel, ulMotionSearchType, asMotionData, ulVbvBufferSize, and bLimitPicSizeFluctuations will be ignored and internally computed 
                                                         // by the encoder. Otherwise, false.

   bool              bTimecodeDropFrameFlag;             // If true, numbers that refer to the frames are dropped to minimize timing error. The default is false.
};

//
// Summary:
//    Specifies audio encoding parameters specific to the MPEG-1 and MPEG-2 IBP formats.
//
struct SMvMpegStreamAudioEncoderSettings
{
   uint32_t             size;             // Structure size in bytes.
   SMvaWaveFormatInfo   sWavFormat;       // Indicates the basic WAV informaion. 
   unsigned short       usMpegAudioLayer; // Indicates the MPEG audio layer, as follows:<p> 1 = Layer 1 <p>2 = Layer 2
   unsigned short       usBitRate;        // Layer 1 bit rates (kbit/sec): 96 (mono only), 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, and 488.<p>
                                          // Layer 2 bit rates (kbit/sec): 32, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, and 384.
};

//
// Summary:
//    Specifies multiplexer encoding parameters specific to the MPEG-1 and MPEG-2 IBP formats.
//
struct SMvMpegStreamMultiplexerEncoderSettings
{
   uint32_t                      size;                // Structure size in bytes.
   
   wchar_t*                      pwchFileName;        // When multiplexing, the encoder generates a file using the specified path.

   // generic multiplexer settings
   EMvMpegstreamMultiplexerType  eType;               // Indicates the multiplexing type.
   bool                          bVBR;                // If true, constant bit rate (CBR) encoding will be used. Otherwise, variable bit rate (VBR) encoding will be used.
   unsigned short                usSectorSize;        // For Program Stream (PS) only. Size of pack in bytes. MPEG-1 = [306, 4096], MPEG-2 = [312, 4096].
   unsigned short                usPacketsPerPack;    // For PS only. Number of Packetized Elementary Stream (PES) packets per pack. MPEG-1 = (usMpegPackSize - 33)/262, MPEG-2 = (usMpegPackSize - 35)/264.
   unsigned short                usSectorDelay;       // Value of the first SCR (system clock reference). Range is [0, 2<sup>31</sup>]. Default is 0.
   unsigned short                usVideoDelay;        // Delay in milliseconds applied to all video streams relative to the first SCR. Range is [0, 1000]. Default is 0.
   unsigned short                usAudioDelay;        // Delay in milliseconds applied to all audio streams relative to the first SCR. Range is [0, 1000]. Default is 0.
   unsigned short                usAudioBufferSize;   // Size in 1024-byte units of the audio buffer in the pack header for all audio streams. Range is [0, 64]; with size%2 == 0. Default is 0.
   unsigned short                usVideoBufferSize;   // Size in 1024-byte units of the video buffer in the pack header for all video streams. Range is [0, 256]; with size%23 == 0. Default is 0.
   unsigned short                usMuxingRate;        // Mux rate in 50-byte units. Range is [0, 32767]. Default is 0 (determined by rate of muxed streams).
   bool                          bAlignSeqHeaders;    // For PS only. If true, sequence headers are aligned to the start of a PES packet.
   bool                          bWritePEC;           // For PS only. If true, a program end code is written at the end of the PS stream settings.
   unsigned short                usVideoID;           // MPEG stream ID written in the PES packet header. If set to 0, encoder will assign a value of 0xE0.
   unsigned short                usVideoPID;          // For Transport Stream (TS) only. Packet ID (PID) of the video stream. If set to 0, PID will be set to 0x810.
   unsigned short                usAudioID;           // MPEG stream ID written in the PES packet header. If set to 0, encoder will assign a value of 0xC0.
   unsigned short                usAudioPID;          // For TS only. PID of the audio stream. If set to 0, PID will be set to 0x814.
};

//
// Summary:
//    The Flex MPEG Stream module initialization structure.
// Description:
//    Describes the type of stream to encode among the following:
//       - Video elementary stream.
//       - Video program stream.
//       - Video transport stream.
//       - Audio-video program stream.
//       - Audio-video transport stream.
//    Some parameters are specific to the encoding type. See each parameter's description for more details.
//
struct SMvMpegStreamInitialize
{
   uint32_t                      size;                      // Specifies the size of the structure in bytes, and should be 
   // sizeof(SMvMpegStreamInitialize), which is used to ensure versioning coherency.
   IMvMpegStreamMemoryProvider*  pIMemoryProvider;          // Pointer that recieves the memory provider interface to be given to the Flex MPEG-2 
   // IBP Encoder. An IUnknown::AddRef call needs to be made. Used only for elementary 
   // video stream capture.
   SMvResolutionInfo             sResolution;               // Specifies the uncompressed video resolution.
   SMvMpegStreamEncoderSettings  sEncoderSettings;          // Specifies the MPEG-2 encoding parameters.
   bool                          bOneGopPerBuffer;          // If true, allows the caller to be asked for a new memory buffer for every GOP. Can be useful, 
   // since it is hard to predict the size of a GOP prior to compression. Used only for 
   // elementary video stream capture.
   bool                                    bAudioEncoderEnabled;  // If true, specifies that the stream will contain compressed audio. Not used if 
   // encoding an elementary video stream.
   SMvMpegStreamAudioEncoderSettings       sAudioEncoderSettings; // Specifies the audio encoder settings. Not used if encoding an elementary video stream.
   bool                                    bMultiplexerEnabled;   // If true, specifies that video and/or audio streams will be packeted into a program or transport 
   // stream. Not used if encoding an elementary video stream.
   SMvMpegStreamMultiplexerEncoderSettings sMultiplexerSettings;  // Specifies the multiplexer settings. Not used if encoding an elementary video stream.
};

//
// Summary:
//    Describes the time code structure.
//
struct SMvTimeCode
{
   uint32_t    size;             // Structure size in bytes.
   uint64_t    ui64Hour;         // Hour value of the time code.
   uint64_t    ui64Minute;       // Minute value of the time code.
   uint64_t    ui64Second;       // Second value of the time code.
   uint64_t    ui64Frame;        // Frame of the time time code.
   bool        bIsStartTimeCode; // If true, the starting time code values are used. <p> If false, the starting time code is 0:0:0:0. <p><b> Note:</b> For Panasonic P2 type files this value does not need to be set
                                 // in consolidation mode since the time code information is always copied from the source file to the destination file during the consolidation process.
};

//
// Summary:
//    The Flex File Writer module initialization structure.
// Remarks:
//   - For all formats except H.264/AVC, you can set guidCodec to GUID_NULL. If you want to encode to an H.264/AVC format, you must specify the appropriate GUID for the codec you want to use to create the file (see the mvcCodecGuids.h file).
//
struct SMvFlexWriterVideoParameters
{
   uint32_t                size;                      // Structure size in bytes.
   EMvSurfaceFormat        eSurfaceFormat;            // Surface format used to specify the capture format.
   unsigned long           ulDiskAccessSizeInBytes;   // Optional size specifying the number of bytes
   // to burst to disk. Set to 0 for default internal value.
   SMvMpegStreamInitialize sMpegStreamInitialize;     // MPEG-Stream-Encoder-specific parameters.
   bool                    bConsolidation;            // GetBuffer surfaces will contain compressed data (true) or uncompressed data (false).
   // Default is false.
   bool                    bExternalDataReference;    // This is only valid when capturing the media data outside of the file's body. Set to false if not used.
   // The Flex Writer will generate an external data file in the same folder as the main file. 
   SMvTimeCode             sTimeCode;                 // Time code structure.
   GUID                    guidCodec;                 // GUID for the codec used to write to the file.
};

//
// Summary:
//    The Flex File Writer module initialization structure.
//
struct SMvFlexWriterAudioParameters
{
   uint32_t             size;             // Structure size in bytes.
   SMvaWaveFormatInfo   SWaveFormatInfo;  // Audio WAV format info structure.
   bool                 bOptimizeMOVAudioPackaging;    // This allows the user to select the type of audio packaging for native MOV capture (non-AVC).
};

//
// Summary:
//    The Flex File Writer module OpenFileEx initialization structure.
//
struct SMvFlexWriterOpenParameters
{
   uint32_t                     size;                                // Structure size in bytes.
   wchar_t                      wszFilename[MAX_PATH];               // File to be the capture target.
   wchar_t                      wszReferenceFileName[MAX_PATH];      // Reference file name For TDIR MOV. For other types, the default will be null.
   EMvFlexWriterCaptureType     eCaptureType;                        // A combination of video/audio/VBI 
                                                                     // flags specifying what type
                                                                     // of data you're capturing inside
                                                                     // the specified file.
   SMvResolutionInfo            sResolution;                         // Resolution of the file to be captured.
   unsigned long                ulStartPositionInsideFile;           // Position, at which to start the
                                                                     // capture inside the specified
                                                                     // file, if the file already exists.
   SMvFlexWriterVideoParameters  sVideoParameters;                   // Video-specific capture parameters.
   SMvFlexWriterAudioParameters  sAudioParameters;                   // Audio-specific capture parameters.
   unsigned long                 ulVBIHeightInLines;                 // Number of lines to be used if 
                                                                     // a VBI capture type is
                                                                     // specified.
   bool                          bTDIR;                              // Specifies, if this is a TDIR
                                                                     // (time delay instant replay) capture.
   double                        dTDIRFlushFrequency;                // Specifies the flush frequency 
                                                                     // in case of a TDIR (time 
                                                                     // delay instant replay) capture.
   CLSID                         clsidFlexAVClip;                    // Specifies the desired Flex Clip Writer to be used in the capture process. 
                                                                     // Used in specific scenarios, such as QuickTime proxy captures. Set to CLSID_NULL by default.
};
//
// Summary:
//    Provides the file headers for some playlist element properties structures.
//
struct SMvElementProperties
{
   IMvCustomFileSystemIO * pICustomFileSystemIO;   // Interface pointer for the file reader file I/O overload.
   uint64_t                ui64FrameDuration;      // Length, in frames, of the element.
   uint64_t                ui64FrameTrimIn;        // First frame of the element in the file.
   uint64_t                ui64FrameTrimOut;       // Last frame of the element in the file.  The value
   // is exclusive, meaning that a trim from 0 to 200
   // will play field 0 to 199.
   bool                    bRemoteTimeDelay;       // Specifies that the file is still being written
   // to and that the file reader must update its
   // internal file header periodically.
   CLSID                   clsidFlexClipReader;    // Class ID of a COM DLL that implements custom file
   // reading.  Set to zero to use Matrox's defaults.
};

//
// Summary:
//    Specifies which slow-motion algorithm to use for a playlist element.
//
enum EMvSlowMotionType
{
   keMvSlowMotionTypeInvalid = 0,   // Invalid value.
   keMvSlowMotionTypeFrameRepeat,   // Indicates that the slow-motion unit will blend the two fields
   // (closest to the requested position in the playlist) together
   // to generate the requested field.  When slow motion is applied
   // on a progressive file, frame blending is performed.
   keMvSlowMotionTypeBlending,      // Indicates that the slow-motion unit will repeat the closest field
   // at the requested position in the playlist.  This enumerated 
   // value has the same effect as keSlowMotionTypeFrameRepeat when
   // slow motion is applied on a progressive frame file.
   keMvSlowMotionTypeFieldRepeat,   // Indicates that the slow-motion unit will repeat the closest frame
   // at the requested position in the playlist.
   keMvSlowMotionTypeLast           // End of list indicator.
};


//
// Summary:
//    Describes the video playlist element properties.
//
struct SMvVideoElementProperties
{
   uint32_t             size;             // Structure size in bytes.
   SMvElementProperties sProperties;      // Common element properties.
   EMvSlowMotionType    eSlowMotionType;  // Specifies what type of slow-motion interpolation algorithm
   // is selected.
   SMvPointF            ptOutputPosition; // Specifies the image position set on the video surface by
   // the file reader.
   unsigned long        ulStreamIDToRead; // Zero-based stream ID to read inside the file.
};


//
// Summary:
//    Describes the audio playlist element properties.
//
struct SMvAudioElementProperties
{
   uint32_t             size;             // Structure size in bytes.
   SMvElementProperties sProperties;      // Common element properties.
   bool                 bHasFadeIn;       // Specifies that the first audio sample buffer of the element
   // has the fade-in attribute set to true.
   bool                 bHasFadeOut;      // Specifies that the last audio sample buffer of the element
   // has the fade-out attribute set to true.
   unsigned long        ulStreamIDToRead; // Zero-based stream ID to read inside the file.
};


//
// Summary:
//    Describes the AVI playlist element properties.
//
struct SMvAVInterleavedElementProperties
{
   uint32_t             size;                   // Structure size in bytes.
   SMvElementProperties sProperties;            // Common element properties.
   EMvSlowMotionType    eSlowMotionType;        // Specifies what type of slow motion algorithm the 
   // File Reader performs.
   SMvPointF            ptOutputPosition;       // Specifies the image position set on the video 
   // surface by the File Reader.
   bool                 bHasFadeIn;             // Specifies that the first audio sample buffer of 
   // the element has the fade-in attribute set to true.
   bool                 bHasFadeOut;            // Specifies that the last audio sample buffer of 
   // the element has the fade-out attribute set to true.
   unsigned long        ulVideoStreamIDToRead;  // Zero-based stream ID to read inside the file.
   unsigned long        ulAudioStreamIDToRead;  // Zero-based stream ID to read inside the file.
};

//
// Summary:
//    Information for a frame that does not go into the surface description. It includes 3:2 pulldown information.
//
//
struct SMvFrameExtraInfo
{
   uint32_t                       size;                           // Structure size in bytes.
   EMvPullDownSequence            ePullDownSequence;              // Type of pulldown sequence.
   EMvFrameOfSequence             eFrameOfSequence;               // Which frame in the sequence.
   EMvDvcproHD720pActiveFrameFlag eDvcproHD720pActiveFrameFlag;   // Additional sequence information for DVCPRO HD 720p.
};

//
// Summary:
//    Defines ways to use the analog video connectors when they can be used for many functions.
//
enum EMvAnalogConnectorsVideoFormat 
{
   keMvAnalogConnectorsVideoFormatInvalid,           // Invalid value.
   keMvAnalogConnectorsVideoFormat_Component,        // Component.
   keMvAnalogConnectorsVideoFormat_CompositeAndY_C,  // Composite and Y/C.
   keMvAnalogConnectorsVideoFormatLast               // End of list indicator.
};


//
// Summary:
// This macro is used to get the string corresponding to the eMvAnalogConnectorsVideoFormat enum value.
//
#define MV_ANALOG_CONNECTORS_VIDEO_FORMAT_ENUM_TO_STRING(eMvAnalogConnectorsVideoFormat) \
   ((eMvAnalogConnectorsVideoFormat == keMvAnalogConnectorsVideoFormatInvalid) ? _T("Invalid") : \
   (eMvAnalogConnectorsVideoFormat == keMvAnalogConnectorsVideoFormat_Component) ? _T("Component") : \
   (eMvAnalogConnectorsVideoFormat == keMvAnalogConnectorsVideoFormat_CompositeAndY_C) ? _T("Composite") : \
   (eMvAnalogConnectorsVideoFormat == keMvAnalogConnectorsVideoFormatLast) ? _T("Last") : \
   _T("???"))
#define MV_MXO_ANALOG_CONNECTORS_VIDEO_FORMAT_ENUM_TO_STRING MV_ANALOG_CONNECTORS_VIDEO_FORMAT_ENUM_TO_STRING

//
// Summary:
//    Defines the possible IRE levels that can be used in analog NTSC video.
//
enum EMvAnalogNTSC_IRELevel 
{
   keMvAnalogNTSC_IRELevel_Invalid,              // Invalid value.
   keMvAnalogNTSC_IRELevel_0,                    // 0 IRE.
   keMvAnalogNTSC_IRELevel_7_5,                  // 7.5 IRE.
   keMvAnalogNTSC_IRELevel_Last                  // End of list indicator.
};

//
// Summary:
// This macro is used to get the string corresponding to the eMvAnalogNTSC_IRELevel enum value.
//
#define MV_ANALOG_NTSC_IRE_LEVEL_ENUM_TO_STRING(eMvAnalogNTSC_IRELevel) \
   ((eMvAnalogNTSC_IRELevel == keMvAnalogNTSC_IRELevel_Invalid) ? _T("Invalid") : \
   (eMvAnalogNTSC_IRELevel == keMvAnalogNTSC_IRELevel_0) ? _T("0") : \
   (eMvAnalogNTSC_IRELevel == keMvAnalogNTSC_IRELevel_7_5) ? _T("7.5") : \
   (eMvAnalogNTSC_IRELevel == keMvAnalogNTSC_IRELevel_Last) ? _T("Last") : \
   _T("???"))
#define MV_MXO_ANALOG_NTSC_IRE_LEVEL_ENUM_TO_STRING MV_ANALOG_NTSC_IRE_LEVEL_ENUM_TO_STRING

//MXO-supported output resolutions.
enum EMvMXOOutputResolution 
{
   keMvMXOOutputResolutionInvalid,                          // Invalid value.
   keMvMXOOutputResolutionCcir601Ntsc720_486Interlace30M,   // CCIR 601 NTSC 720x486i at 29.97 fps.
   keMvMXOOutputResolutionCcir601Pal720_576Interlace25,     // CCIR 601 PAL 720x576i at 25 fps.
   keMvMXOOutputResolutionHDTV1920_1080Interlace30M,        // HDTV 1920x1080i at 29.97 fps.
   keMvMXOOutputResolutionHDTV1920_1080Interlace25,         // HDTV 1920x1080i at 25 fps.
   keMvMXOOutputResolutionHDTV1280_720Progressive60M,       // HTDV 1280x720p at 59.94 fps
   keMvMXOOutputResolutionHDTV1280_720Progressive50,        // HTDV 1280x720p at 50 fps

   keMvMXOOutputResolutionHDV1440_1080Interlace30M,         // HDV 1440x1080i at 29.97 fps.
   keMvMXOOutputResolutionHDV1440_1080Interlace25,          // HDV 1440x1080i at 25 fps.

   keMvMXOOutputResolutionDVCPro960_720Progressive60M,      // DVCPRO 960x720p at 59.94 fps
   keMvMXOOutputResolutionDVCPro960_720Progressive50,       // DVCPRO 960x720p at 50 fps.

   keMvMXOOutputResolutionLast                              // End of list indicator.
};
//
// MXO external DVI input resolutions.
// This enum is defined in mvflexdefinitions.h
enum EMvDVIResolution 
{
   keMvDVIResolutionInvalid,                        // Invalid value.   
   keMvDVIResolutionHDTV1920_1080Progressive50,     // HDTV 1920x1080p at 50 fps.
   keMvDVIResolutionHDTV1920_1080Progressive60M,    // HDTV 1920x1080p at 59.94 fps.
   keMvDVIResolutionHDTV1920_1080Progressive60,     // HDTV 1920x1080p at 60 fps.
   keMvDVIResolution1280x1024Progressive60M,        // 1280x1080p at 59.94 fps.
   keMvDVIResolution1280x1024Progressive60,         // 1280x1080p at 60 fps.
   keMvDVIResolutionLast                            // End of list indicator.
};

//
// Specifies MXO indicators for an Imaging product.
//
enum EMvImagingMXOIndicator
{
   keMvImagingMXOIndicatorInvalid,   // Invalid value.
   keMvImagingMXOIndicator1,         // Imaging MXO Indicator 1.
   KeMvImagingMXOIndicator2,         // Imaging MXO Indicator 2.
   KeMvImagingMXOIndicatorLast       // End of enum.
};
// 
// Specifies MXO public named events for an Imaging product.
// 
enum EMvImagingMXOPublicEvents
{
   keMvImagingMXOPublicEventInterfacePresent,       // Interface present event.
   keMvImagingMXOPublicEventDriverReady,            // Driver ready event.
   keMvImagingMXOPublicEventDriverUnload,           // Driver unload event.
   keMvImagingMXOPublicEventMonitorUnplugged,       // Monitor unplugged event.
   keMvImagingMXOPublicEventMonitorPlugged,         // Monitor plugged event.
   keMvImagingMXOPublicEventDVICableUnplugged,      // DVI cable unplugged event.
   keMvImagingMXOPublicEventDVICablePlugged,        // DVI cable plugged event.
   keMvImagingMXOPublicEventReturnFromSuspend,      // Return from suspend event.
   keMvImagingMXOPublicEventDVIInResChanged,        // DVI In resolution changed.
   keMvImagingMXOPublicEventCount                   // End of list indicator.
};

//
// MXO named events.
//

// Summary:
//    Indicates when the MXO device's power and USB cables are connected.
//
#define MV_MXO_IMAGING_NAMED_EVENT_MXO_INTERFACE_PRESENT      "MV_MXO_IMAGING_INTERFACE_PRESENT"

// Summary:
//    Indicates when the MXO device is ready for use.
//
#define MV_MXO_IMAGING_NAMED_EVENT_MXO_DRIVER_READY           "MV_MXO_IMAGING_DRIVER_READY"

// Summary:
//    Indicates when the MXO device's power and USB cables are disconnected.
//
#define MV_MXO_IMAGING_NAMED_EVENT_MXO_DRIVER_UNLOAD          "MV_MXO_IMAGING_DRIVER_UNLOAD"

// Summary:
//    Indicates when the Monitor's DVI cable is disconnected from the MXO device.
//
#define MV_MXO_IMAGING_NAMED_EVENT_DVI_MONITOR_UNPLUGGED      "MV_MXO_IMAGING_DVI_MONITOR_UNPLUGGED"

// Summary:
//    Indicates when the Monitor's DVI cable is connected to the MXO device.
//
#define MV_MXO_IMAGING_NAMED_EVENT_DVI_MONITOR_PLUGGED        "MV_MXO_IMAGING_DVI_MONITOR_PLUGGED"

// Summary:
//    Indicates when the MXO device's DVI cable is disconnected from the pc.
//
#define MV_MXO_IMAGING_NAMED_EVENT_DVI_CABLE_UNPLUGGED        "MV_MXO_IMAGING_DVI_CABLE_UNPLUGGED"

// Summary:
//    Indicates when the MXO device's DVI cable is connected to the pc.
//
#define MV_MXO_IMAGING_NAMED_EVENT_DVI_CABLE_PLUGGED          "MV_MXO_IMAGING_DVI_CABLE_PLUGGED"

// Summary:
//    Indicates when the MXO device returns from system suspend mode.
//
#define MV_MXO_IMAGING_NAMED_EVENT_RETURN_FROM_SUSPEND        "MV_MXO_IMAGING_RETURN_FROM_SUSPEND"

// Summary:
//    Indicates when the MXO device DVI In resolution changed.
//
#define MV_MXO_IMAGING_NAMED_EVENT_DVIIN_RES_CHANGED        "MV_MXO_IMAGING_DVIIN_RES_CHANGED"


//
// Summary:
// This macro is used to get the string corresponding to the eMvMXOOutputResolution enum value.
//
#define MV_MXO_OUTPUT_RESOLUTION_ENUM_TO_STRING(eMvMXOOutputResolution) \
   ((eMvMXOOutputResolution == keMvMXOOutputResolutionInvalid) ? _T("Invalid") : \
   (eMvMXOOutputResolution == keMvMXOOutputResolutionCcir601Ntsc720_486Interlace30M) ? _T("NTSC") : \
   (eMvMXOOutputResolution == keMvMXOOutputResolutionCcir601Pal720_576Interlace25) ? _T("PAL") : \
   (eMvMXOOutputResolution == keMvMXOOutputResolutionHDTV1920_1080Interlace30M) ? _T("1080i30M") : \
   (eMvMXOOutputResolution == keMvMXOOutputResolutionHDTV1920_1080Interlace25) ? _T("1080i25") : \
   (eMvMXOOutputResolution == keMvMXOOutputResolutionHDTV1280_720Progressive60M) ? _T("720p59.94") : \
   (eMvMXOOutputResolution == keMvMXOOutputResolutionHDTV1280_720Progressive50) ? _T("720p50") : \
   _T("???"))

//
// Summary:
//    Describes the type of device attached to a DVI port.
//
enum EMvDVIPortAttachedDevice
{
   keMvDVIPortAttachedDeviceInvalid,       // Invalid value.
   keMvDVIPortAttachedDeviceMXO,           // MXO device.
   keMvDVIPortAttachedDeviceDVIModule,     // DVI module device.
   keMvDVIPortAttachedDeviceOther,         // Other device (unused).
   keMvDVIPortAttachedDeviceLast           // End of list indicator.
};

//
// Summary:
//    Contains the playback channel of the device attached to a DVI port, as well as its connection info.
//
struct SMvDVIPlaybackChannel
{
   uint32_t                  size;                                    // Structure size in bytes.
   SMvDVIConnectionsIdentifiers  sDVIConnectionsIdentifiers;        // Identifies the graphics card number, device number and control panel identifier.
   EMvVideoIOChannel       eVideoChannel;                           // Specifies the video playback channel.
};

//
// Summary:
//    Provides the channel description for a DVI output port (for example, the resolution, the name 
//       of the graphics card, the display frequency, etc).
//
struct SMvDVIPlaybackChannelDescription
{
   uint32_t                 size;                  // Structure size in bytes.
   unsigned int             uiWidth;               // Indicates the resolution width, in pixels.
   unsigned int             uiHeight;              // Indicates the resolution height, in pixels.
   unsigned int             uiComponentBitCount;   // Indicates the number of bits per component for a pixel.
   unsigned int             uiDisplayFrequency;    // Indicates the refresh rate, in Hz.
   char                     szGraphicCard[128];    // Specifies the name of the graphics card.
   EMvDVIPortAttachedDevice eAttachedDevice;       // Specifies the attached device type [keMvDVIPortAttachedDeviceInvalid if none].
   char                     szDeviceName[128];     // Specifies the attached device name [NULL if none].
   bool                     bIsCorrectBoard;       // Indicates whether the detected device is the device
                                                   // on which the current flex engine hs been created.
   char                     szSerialNumber[128];   // Specifies the serial number of the attached device.
   SMvDVIPlaybackChannel    sDVIPlaybackChannel;   // Describes the DVI playback channel.
};

///////////////////////////////////////////////////////////////////////////////
//
// Begin of AVCIntra codec definitions
//
///////////////////////////////////////////////////////////////////////////////

//
// Summary
//    Describes the Matrox AVC-Intra encoder compression options.
struct SMvAVCIntraCompressionOptions 
{
   uint32_t                   size;                      // Structure size in bytes.
   SMvResolutionInfo          sResolutionInput;          // Input resolution of the codec.
   SMvResolutionInfo          sResolutionOutput;         // Output resolution of the codec.
   EMvAVCIntraProfile         eProfile;                  // Indicates if the Matrox AVC-Intra profile is Class 50 or Class 100.
   bool                       bEncodeAFD;                // If true, indicates that there is AFD information to encode.
   bool                       bEncodeCC;                 // If ture, indicates that there is closed caption information to encode.
   bool                       bEncodeTC;                 // If true, indicates that there is time code information to encode.
   bool                       bForceSynchronousOpen;     // If true, indicates that a synchronous open operation must be forced.
};



///////////////////////////////////////////////////////////////////////////////
//
// End of AVCIntra codec definitions
//
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
//
// Begin of ProRes codec definitions
//
///////////////////////////////////////////////////////////////////////////////

//
// Summary
//             Describes the Apple ProRes compression options.
struct SMvProResCompressionOptions 
{
   uint32_t                   size;                      // Structure size in bytes.
   SMvResolutionInfo          sResolutionInput;          // Indicates the input resolution.
   SMvResolutionInfo          sResolutionOutput;         // Indicates the output resolution.
   EMvProResProfile           eProfile;                  // Indicates the  profie, such as 422 or 422 HQ.
   EMvEncodingScanMode        eEncodingScanMode;         // Indicates whether the encoding will be done in frames or fields. 
   bool                       bForceSynchronousOpen;     // If true, indicates that a synchronous open operation must be forced.
};
//
// Summary
//             Describes the Apple ProRes decompression options.
struct SMvProResDecompressionOptions 
{
   uint32_t                   size;                      // Structure size in bytes..
   SMvResolutionInfo          sResolutionInput;          // Indicates the input resolution.
   SMvResolutionInfo          sResolutionOutput;         // Indicates the output resolution.   
   bool                       bForceSynchronousOpen;     // If true, indicates that a synchronous open operation must be forced.
};



///////////////////////////////////////////////////////////////////////////////
//
// End of ProRes codec definitions
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// Begin of DNxHD codec definitions
//
///////////////////////////////////////////////////////////////////////////////

//
// Summary
//    Describes the Avid DNxHD compression options.
struct SMvDNxHDCompressionOptions 
{
   uint32_t                   size;                      // Structure size in bytes.
   SMvResolutionInfo          sResolutionInput;          // Indicates the input resolution.
   SMvResolutionInfo          sResolutionOutput;         // Indicates the output resolution.
   EMvDNxHDProfile            eProfile;                   // Indicates if the Avid DNxHD profile is VC-3 or DNxHD.
   bool                       bForceSynchronousOpen;     // If true, indicates that a synchronous open operation must be forced.
};
//
// Summary
//    Describes the Avid DNxHD decompression options.
struct SMvDNxHDDecompressionOptions 
{
   uint32_t                   size;                      // Structure size in bytes.
   SMvResolutionInfo          sResolutionInput;          // Indicates the input resolution.
   SMvResolutionInfo          sResolutionOutput;         // Indicates the output resolution.   
   EMvDNxHDProfile            eProfile;                   // Indicates if the Avid DNxHD profile is VC-3 or DNxHD.
   bool                       bForceSynchronousOpen;     // If true, indicates that a synchronous open operation must be forced.
};
///////////////////////////////////////////////////////////////////////////////
//
// End of DNxHD codec definitions
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// Begin of MPEG-4 Simple Studio Profile codec definitions
//
///////////////////////////////////////////////////////////////////////////////

//
// Summary
//    Describes the Matrox MPEG-4 Simple Studio Profile (SStP) compression options.
struct SMvMPEG4SStPCompressionOptions 
{
   uint32_t                   size;                      // Structure size in bytes.
   SMvResolutionInfo          sResolutionInput;          // Indicates the input resolution.
   SMvResolutionInfo          sResolutionOutput;         // Indicates the output resolution.
   EMvMPEG4SStPProfile        eProfile;                  // Indicates the MPEG-4 SStP profile.
   unsigned long              ulComponentBitCount;       // Indicates the number of bits per component of a pixel.
   bool                       bForceSynchronousOpen;     // If true, indicates that a synchronous open operation must be forced.
   bool                       bEnableFastMode;           // If true, increases the speed at which the MPEG-4 SStP video is encoded. This reduces the compression quality by using less CPU processing. The default is false.
};
//
// Summary
//    Describes the Matrox MPEG-4 Simple Studio Profile (SStP) decompression options.
struct SMvMPEG4SStPDecompressionOptions 
{
   uint32_t                   size;                      // Structure size in bytes.
   SMvResolutionInfo          sResolutionInput;          // Indicates the input resolution.
   SMvResolutionInfo          sResolutionOutput;         // Indicates the output resolution.   
   EMvMPEG4SStPProfile        eProfile;                  // Indicates the MPEG-4 SStP profile.
   unsigned long              ulComponentBitCount;       // Indicates the number of bits per component of a pixel. It can be 10- or 12-bit.
   bool                       bForceSynchronousOpen;     // If true, indicates that a synchronous open operation must be forced.
};
///////////////////////////////////////////////////////////////////////////////
//
// End of MPEG-4 Simple Studio Profile codec definitions
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// AAC Codec Definitions
//
///////////////////////////////////////////////////////////////////////////////

//
// Summary:
//    Specifies the valid bit rate mode supported by the Matrox AAC encoder.
//
enum EMvAACBitrateMode
{
   keMvAACBitrateModeInvalid,    // Invalid value.
   keMvAACBitrateModeABR,        // Average bit rate mode.
   keMvAACBitrateModeLast        // End of list indicator.
};

//
// Summary:
//    Specifies the valid profile supported by the Matrox AAC encoder.
//
enum EMvAACProfile
{
   keMvAACProfileInvalid,        // Invalid value.
   keMvAACProfileLC,             // Low Complexity profile.
   keMvAACProfileLast            // End of list indicator.
};

//
// Summary:
//    Specifies the valid noise shaping models supported by the Matrox AAC encoder.
//
enum EMvAACNoiseShapingModel
{
   keMvAACNoiseShapingModelInvalid,    // Invalid value.
   keMvAACNoiseShapingModelSimple,     // Indicates that the Simple Noise Shaping model is used.
   keMvAACNoiseShapingModelAdvanced,   // Indicates that the Advanced Noise Shaping model is used.
   keMvAACNoiseShapingModelLast        // End of list indicator.
};

//
// Summary:
//    Specifies the valid stereo encoding modes supported by the Matrox AAC encoder.
//
enum EMvAACStereoMode
{
   keMvAACStereoModeInvalid,        // Invalid value.
   keMvAACStereoModeMono,           // Indicates mono encoding.
   keMvAACStereoModeLeftRight,      // Indicates left right mode encoding.
   keMvAACStereoModeMidSide,        // Indicates mid side mode encoding.
   keMvAACStereoModeJointStereo,    // Indicates joint stereo mode encoding.
   keMvAACStereoModeLast            // End of list indicator.
};

//
// Summary:
//    Specifies the output format of an AAC stream.
//
enum EMvAACOutputFormat
{
   keMvAACOutputFormatInvalid,      // Invalid value.
   keMvAACOutputFormatRAW,          // The stream will be written without any headers.
   keMvAACOutputFormatADIF,         // The stream will be written with an Advanced Data Interchange Format (ADIF) header.
   keMvAACOutputFormatADTS,         // The stream will be written with Audio Data Transport Stream (ADTS) headers.
   keMvAACOutputFormatLast          // End of list indicator.
};

// Summary:
//    Specifies the encoding mode of the AAC channels. 
// Remarks:
//  - If keMvAACChannelEncodingMode8Channels is used for 7.1 encoding, the LFE track will be encoded as an SCE track.
//
enum EMvAACChannelEncodingMode
{
   keMvAACChannelEncodingModeDefault,       // Indicates that the specified channel configuration uses the default encoding.
   keMvAACChannelEncodingMode7_1Channels,   // Indicates that regular 7.1 encoding is used.
   keMvAACChannelEncodingMode8Channels,     // Indicates that the low frequency element (LFE) is not encoded. Instead it is encoded as a single channel element (SCE).
   keMvAACChannelEncodingModeLast           // End of list indicator.
};

//
// Summary:
//    Specifies the data type used to initialize the Matrox AAC Decoder.
//
enum EMvAACConfigDataType
{
   keMvAACConfigDataTypeInvalid,                   // Invalid value.
   keMvAACConfigDataTypeADIFHeader,                // An Advanced Data Interchange Format (ADIF) header is used to configure the codec.
   keMvAACConfigDataTypeAudioSpecificConfigData,   // An Audio Specific Config block is used to configure the codec.
   keMvAACConfigDataTypeLast                       // End of list indicator.
};

//
// Summary:
//    Describes data used to configure the Matrox AAC codec.
//
struct SMvAACConfigDataStream
{
   uint32_t                size;                   // Structure size in bytes.
   uint32_t                ui32DataLengthInBytes;  // Length of the configuration data in bytes.
   unsigned char*          puchData;               // Pointer to the configuration data.
};

//
// Summary:
//    Describes the necessary information on a stream to be able
//    to produce an AudioSpecificConfig element.
//
struct SMvAACConfigurationInfo
{
   uint32_t                size;                   // Structure size in bytes.
   EMvAACProfile           eAACProfile;            // AAC profile used.
   unsigned long           ulSamplingFrequency;    // Audio sampling frequency in Hz.
   unsigned int            uiNbChannels;           // Number of channels of the audio stream.
};

//
// Summary:
//    Describes data that will be passed to initialize AAC decompression.
//
struct SMvAACDecompressionOptions
{
   uint32_t                      size;             // Structure size in bytes.
   EMvAACConfigDataType          eConfigDataType;  // Type of configuration data.
   IMvAACCodecConfigDataAccess*  pIConfigData;     // Pointer to an object of the interface IMvAACCodecConfigDataAccess.
};

//
// Summary:
//    Describes the options that will be used to initialize the Matrox AAC encoder.
//
struct SMvAACCompressionOptions
{
   uint32_t                   size;                         // Structure size in bytes.
   int                        iInputPCMSampleFrequency;     // Sampling frequency of the input PCM stream.
   int                        iInputPCMNbChannels;          // Number of channels of the input PCM stream.
   unsigned int               uiTargetBitrate;              // Target bit rate in bits/sec.
   EMvAACBitrateMode          eAACBitrateMode;              // Bit rate mode.
   EMvAACProfile              eAACProfile;                  // Encoding profile.
   EMvAACNoiseShapingModel    eAACNoiseShapingModel;        // Noise shaping model.
   EMvAACStereoMode           eAACStereoMode;               // Stereo encoding mode.
   EMvAACOutputFormat         eAACOutputFormat;             // Output format of the stream.
   EMvAACChannelEncodingMode  eAACChannelEncodingMode;       // Channel encoding mode of the stream.   
};

///////////////////////////////////////////////////////////////////////////////
//
// End of AAC Codec Definitions
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// Dolby E Codec Definitions
//
///////////////////////////////////////////////////////////////////////////////
// Dolby E configuration dialog size. These values are the same as those defined in the Minnetonka SDK.
#define DOLBYE_CONFIGURATION_DIALOG_WINDOWWIDTH  731   // Define for Dolby E configuration dialog width.  
#define DOLBYE_CONFIGURATION_DIALOG_WINDOWHEIGHT 520   // Define for Dolby E configuration dialog height.


//
// Summary:
//    Specifies the valid Dolby E configuration indexes supported by the Dolby E codec.
// Description:
//<table>
// Members                                Index    Number of programs     Total number of channels       Program name        Default channel sequence
// ------------------------------------   ------   -------------------    --------------------------     ---------------     -------------------------------------
// KeMvDolbyEConfiguration0_5dot1_2        0        2                      8                             5.1+2               0L, 0C, 0Ls, 1L, 0R, 0LFE, 0Rs, 1R
// KeMvDolbyEConfiguration1_5dot1_2X1      1        3                      8                             5.1+2x1             0L, 0C, 0Ls, 1C, 0R, 0LFE, 0Rs, 2C
// KeMvDolbyEConfiguration2_4_4            2        2                      8                             4 + 4               0L, 0C, 1L, 1C, 0R, 0S, 1R, 1S
// KeMvDolbyEConfiguration3_4_2X           3        3                      8                             4 + 2 x 2           0L, 0C, 1L, 2L, 0R, 0S, 1R, 2R
// KeMvDolbyEConfiguration4_4_2_2X1        4        4                      8                             4 + 2 + 2 x 1       0L, 0C, 1L, 2C, 0R, 0S, 1R, 3C
// KeMvDolbyEConfiguration5_4_4X1          5        5                      8                             4 + 4 x 1           0L, 0C, 1C, 3C, 0R, 0S, 2C, 4C
// KeMvDolbyEConfiguration6_4X2            6        4                      8                             4 x 2               0L, 1L, 2L, 3L, 0R, 1R, 2R, 3R
// KeMvDolbyEConfiguration7_3X2_2X1        7        5                      8                             3 x 2 + 2 x 1       0L, 1L, 2L, 3C, 0R, 1R, 2R, 4C                         
// KeMvDolbyEConfiguration8_2X2_4x1        8        6                      8                             2 x 2 + 4 x 1       0L, 1L, 2C, 4C, 0R, 1R, 3C, 5C 
// KeMvDolbyEConfiguration9_2_6X1          9        7                      8                             2 + 6 x 1           0L, 1C, 3C, 5C, 0R, 2C, 4C, 6C                         
// KeMvDolbyEConfiguration10_8X1           10       8                      8                             8 x 1               0C, 2C, 4C, 6C, 1C, 3C, 5C, 7C
// KeMvDolbyEConfiguration11_5dot1         11       1                      6                             5.1                 0L, 0C, 0Ls, 0R, 0LFE, 0Rs                         
// KeMvDolbyEConfiguration12_4_2           12       2                      6                             4 + 2               0L, 0C, 1L, 0R, 0S, 1R
// KeMvDolbyEConfiguration13_4_2X1         13       3                      6                             4 + 2 x 1           0L, 0C, 1C, 0R, 0S, 2C                         
// KeMvDolbyEConfiguration14_3X2           14       3                      6                             3 x 2               0L, 1L, 2L, 0R, 1R, 2R 
// KeMvDolbyEConfiguration15_2X2_2X1       15       4                      6                             2 x 2 + 2 x 1       0L, 1L, 2C, 0R, 1R, 3C                         
// KeMvDolbyEConfiguration16_2_4X1         16       5                      6                             2 + 4 x 1           0L, 1C, 3C, 0R, 2C, 4C                         
// KeMvDolbyEConfiguration17_6X1           17       6                      6                             6 x 1               0C, 2C, 4C, 1C, 3C, 5C
// KeMvDolbyEConfiguration18_4             18       1                      4                             4                   0L, 0C, 0R, 0S                         
// KeMvDolbyEConfiguration19_2_2           19       2                      4                             2 + 2               0L, 1L, 0R, 1R
// KeMvDolbyEConfiguration20_2_2X1         20       3                      4                             2 + 2 x 1           0L, 1C, 0R, 2C                         
// KeMvDolbyEConfiguration21_4x1           21       4                      4                             4 x 1               0C, 2C, 1C, 3C
// KeMvDolbyEConfigurationLast             -        -                      -                             -                   End of list indicator.  
//</table>
// Remarks:
//   - L = Left
//   - R = Right
//   - C = Center
//   - S = Surround
//   - Ls = Left surround
//   - Rs = Right surround
//   - LFE = Low Frequency Effects
//
enum EMvDolbyEConfiguration
{
   KeMvDolbyEConfiguration0_5dot1_2 = 0,  
   KeMvDolbyEConfiguration1_5dot1_2X1,    
   KeMvDolbyEConfiguration2_4_4,          
   KeMvDolbyEConfiguration3_4_2X,                        
   KeMvDolbyEConfiguration4_4_2_2X1,      
   KeMvDolbyEConfiguration5_4_4X1,                        
   KeMvDolbyEConfiguration6_4X2,          
   KeMvDolbyEConfiguration7_3X2_2X1,                               
   KeMvDolbyEConfiguration8_2X2_4x1,      
   KeMvDolbyEConfiguration9_2_6X1,                               
   KeMvDolbyEConfiguration10_8X1,         
   KeMvDolbyEConfiguration11_5dot1,                              
   KeMvDolbyEConfiguration12_4_2,         
   KeMvDolbyEConfiguration13_4_2X1,                               
   KeMvDolbyEConfiguration14_3X2,        
   KeMvDolbyEConfiguration15_2X2_2X1,                           
   KeMvDolbyEConfiguration16_2_4X1,                              
   KeMvDolbyEConfiguration17_6X1,        
   KeMvDolbyEConfiguration18_4,                                  
   KeMvDolbyEConfiguration19_2_2,        
   KeMvDolbyEConfiguration20_2_2X1,                            
   KeMvDolbyEConfiguration21_4x1,         
   KeMvDolbyEConfigurationLast                              
};

//
// Summary:
//    Describes the options that will be used to initialize the Dolby E encoder.
//
struct SMvDolbyECompressionOptions
{
   uint32_t                size;                      // Structure size in bytes.                     
   EMvFrameRate            eInputFrameRate;           // Indicates the video frame rate associated with the Dolby E stream.
   EMvScanMode             eInputScanMode;            // Indicates the video scan mode associated with the Dolby E stream. 
   EMvAudioDataType        eInputDataType;            // Indicates the supported output compression format.
   EMvDolbyEConfiguration  eDolbyEConfigurationIndex; // Indicates the Dolby E compression configuration.
   HANDLE                  hOpenDone;                 // Sends a signal when the open has occured. The user must create the handle. Can only be used with a valid Dolby E license.
};

//
// Summary:
//    Describes the options that will be used to initialize the Dolby E decoder.
//
struct SMvDolbyEDecompressionOptions
{
   uint32_t                size;                       // Structure size in bytes.  
   EMvAudioDataType        eDataType;                  // Indicates the supported output decompression format.
   bool                    bUseDefaultOutputSequence;  // If true, indicates that the default output sequence is used. Otherwise, false.
   int                     aiOutputSequence[8];        // Array indicating the output sequence. <p> <b> Note:</b> Can only be used if the bUseDefaultOutputSequence is false.
   unsigned int            uiOutputChannelNumber;      // Indicates the number of output channels. This value is used to extract the output channels from the Dolby E decoder to send to the destination output buffer. 
   HANDLE                  hOpenDone;                  // Sends a signal when the open has occured. The user must create the handle. Can only be used with a valid Dolby E license.
};

//
// Summary:
//    Describes the Dolby Digital settings that will be used to initialize the Dolby E encoder. For details on these settings, see the Minnetonka SurCode for Dolby E OEM Encoder Plug-in Interface Specification. 
//
struct SMvDolbyDigitalEncodeParams
{
   uint32_t size;                      // Structure size in bytes. 
   char acProgramDescription[33];      // Array of characters containing the program description.
   int  iSamplingRateIndex;            // Index of the sampling rate. 
   int  iAudioCodingMode;              // Index of the audio coding mode. 
   int  iDataRateIndex;                // Index of the data rate. 
   int  iMaxDataRateIndex;             // Index of the maximum data rate. <b> NOT SUPPORTED IN DOLBY E. </b>
   int  iCenterDownmix;                // Index of the center downmix level.  
   int  iSurroundDownmix;              // Index of the surround downmix level.  
   int  iDynCompress;                  // Index of the compression preset. 
   int  iRfProfile;                    // Index of the profile preset. 
   BOOL bRfOvermodProtection;          // If true, indicates the RF overmodulation protection. 
   int  iDialogNorm;                   // Index of the dialog normalization. 
   int  iBitstreamMode;                // Index of the bit stream mode. 
   BOOL bAudioProdEnabled;             // If true, audio production is enabled. 
   BOOL bCopyrightExists;              // If true, copyright exists. 
   BOOL bIsOriginal;                   // If true, the original Dolby E settings are used. 
   int  iMixingLevel;                  // Index of the mixing level. <p> <b> Note:</b> Not applicable if bAudioProdEnabled is false.
   int  iRoomType;                     // Index of the room type. <p> <b> Note:</b> Not applicable if bAudioProdEnabled is false.
   
   BOOL bPhaseShift;                   // If true, a phase shift of 90 degrees is applied. 
   BOOL bLFEOn;                        // If true, a Low-Frequency Effects (LFE) channel is used. <p> <b> Note:</b> Cannot be enabled if there is no valid LFE channel data present. 
   BOOL bLFEFilter;                    // If true, an LFE low pass filter is used. <p> <b> Note:</b> Applicable only if bLFEOn is true and if there is valid LFE channel data.
   BOOL b3dBAtten;                     // If true, a 3 dB surround attenuation is applied. <p> <b> Note:</b> Not applicable if there are no surround channels.
   BOOL bBandwidthFilter;              // If true, channel bandwidth low pass filter is applied. 
   BOOL bDCFilter;                     // If true, a DC filter is applied. 
   BOOL bRFFilter;                     // If true, an RF pre-emphasis filter is applied.  
   int  iDolbySurround;                // Index of the Dolby surround mode.  
   BOOL bDeemphasis;                   // If true, a de-emphasis filter is applied. <b> NOT SUPPORTED IN DOLBY E. </b>
   
   BOOL bExtendedBitstream;            // If true, an extended bitstream is applied. 
   int iPreferredStereoDownmixMode;    // Index of the preferred downmix mode. <p> <b> Note:</b> Applicable only if bExtendedBitstream is true.
   int iLtRtCenterMixLevel;            // Index of the Lt/Rt center mix level. <p> <b> Note:</b> Applicable only if bExtendedBitstream is true.
   int iLtRtSurroundMixLevel;          // Index of the Lt/Rt surround mix level. <p> <b> Note:</b> Applicable only if bExtendedBitstream is true.
   int iLoRoCenterMixLevel;            // Index of the Lo/Ro center mix level. <p> <b> Note:</b> Applicable only if bExtendedBitstream is true.
   int iLoRoSurroundMixLevel;          // Index of the Lo/Ro surround mix level. <p> <b> Note:</b> Applicable only if bExtendedBitstream is true.
   int iDolbySurroundEXMode;           // Index of the Dolby surround EX mode. <p> <b> Note:</b> Applicable only if bExtendedBitstream is true.
   int iDolbyHeadphoneMode;            // Index of the Dolby headphone mode. <p> <b> Note:</b> Applicable only if bExtendedBitstream is true.
   BOOL bHDCD;                         // If true, input material is HDCD encoded. <p> <b> Note:</b> Applicable only if bExtendedBitstream is true. 
};
//
// Summary:
//   Describes the Dolby E settings that will be used to initialize the Dolby E encoder. For details on these settings, see the Minnetonka SurCode for Dolby E OEM Encoder Plug-in Interface Specification.
//
struct SMvDolbyEEncodeParams
{
   uint32_t size;                        // Structure size in bytes. 
   int      iProgramConfigurationIndex;  // Index of the Dolby E program configuration used in EMvDolbyEConfiguration.
   int      iBitDepthIndex;              // Index of the bit depth format.
   int      iFrameRateIndex;             // Index of the video frame rate.
   int      iOriginalFrameRateIndex;     // Index of the original video frame rate.
   int      iTimecodeHours;              // Time code hours.
   int      iTimecodeMinutes;            // Time code minutes.
   int      iTimecodeSeconds;            // Time code seconds.
   int      iTimecodeFrames;             // Time code frames.
   int      iFrameCount;                 // Frame count. 
   int      iFrameSize;                  // Audio samples in a video frame.
   char     acProgramName[33];           // Arrary of characters containing the program name. For example, 5.1+2, 5.1+2X1, 8X1, etc.
   int      iNnumPrograms;               // Number of programs.
   int      iNumChannelsPerProgram[8];   // Array containing the number of channels per program. For example, the array for 5.1+2 is {6, 2, 0, 0, 0, 0, 0, 0}.
   bool     bDolbyMetadataPresent;       // If true, indicates that Dolby E metadata is present.
   struct SMvDolbyDigitalEncodeParams asDolbyEncoderParams[8]; // Pointer to the array of structures containing the Dolby Digital encoder parameters.
};

//
// Summary:
//   Describes the settings of the Dolby E stream returned by the decoder. For details on these settings, see the Minnetonka SurCode for Dolby E OEM Decoder Plug-in Interface Specification.
//
struct SMvDolbyEEncodeOptions
{
   uint32_t  size;                        // Structure size in bytes.
   int       iProgramConfigurationIndex;  // Index of the Dolby E program configuration used in EMvDolbyEConfiguration. 
   int       iChannelSequence[8];         // Array containing the channel sequence.
   int       iBitDepthIndex;              // Index of the bit depth format.
   int       iFrameRateIndex;             // Index of the video frame rate.
   int       iOriginalFrameRateIndex;     // Index of the original video frame rate.
   int       iTimecodeHours;              // Time code hours.
   int       iTimecodeMinutes;            // Time code minutes.
   int       iTimecodeSeconds;            // Time code seconds.
   int       iTimecodeFrames;             // Time code frames.
   int       iFrameCount;                 // Frame count.
   int       iFrameStartSampleOffset;     // Video frame start offset in samples. 
   int       iFrameSize;                  // Audio samples in a video frame.
   float     fChannelPeakValue[8];        // Array containing meter metadata of the channel's peak value.
   float     fChannelRMSValue[8];         // Array containing meter metadata of the channel's RMS value. 
   char      acProgramName[33];           // Arrary of characters containing the program name. For example, 5.1+2, 5.1+2X1, 8X1, etc.
   int       iNnumPrograms;               // Number of programs.
   int       iNumChannelsPerProgram[8];   // Array containing the number of channels per program. For example, the array for 5.1+2 is {6, 2, 0, 0, 0, 0, 0, 0}.
   BOOL      bDolbyMetadataPresent;       // If true, indicates that Dolby E metadata is present.
   struct SMvDolbyDigitalEncodeParams  asDolbyEncoderParams[8]; // Pointer to the array of structures containing the Dolby Digital encoder parameters.
} ;
///////////////////////////////////////////////////////////////////////////////
//
// End of DOLBYE Codec Definitions
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// Audio Codec Definitions
//
///////////////////////////////////////////////////////////////////////////////

//
// Summary:
//    Describes the format of uncompressed audio data fed to audio compression
//    or obtained through audio decompression.
//
struct SMvAudioCodecIOFormats
{
   uint32_t                size;                   // Structure size in bytes. 
   SMvaWaveFormatInfo      sSupportedFormatInfo;   // Specifies the uncompressed audio sample formats.
};

//
// Summary:
//    Describes the compression capabilities of an audio codec.
//
struct SMvAudioCodecCompressionCapabilities
{
   uint32_t                size;                                        // Structure size in bytes.
   uint32_t                ui32eProfile;                                // Profile to be cast into a specific enumerator describing a profile.
   EMvAudioDataType        eSupportedOutputAudioDataType;               // Enumerator describing the supported output format of compression.
   bool                    bIsTemporalCompression;                      // If true, indicates that streams with temporal compression are supported.
   uint32_t                ui32NbSupportedInputFormats;                 // Number of valid structures in the array asSupportedInputFormats.
   SMvAudioCodecIOFormats  
      asSupportedInputFormats[kulMvMaxSupportedUncompressedFormats];    // Array of structures that contains the supported uncompressed audio codec input formats.
   bool                    bIsBitRateProgrammable;                      // If true, indicates that the bit rate can be programmed.
   uint32_t                ui32MinBitRateInBitsPerSec;                  // Indicates the minimum bit rate supported by compression.
   uint32_t                ui32MaxBitRateInBitsPerSec;                  // Indicates the maximum bit rate supported by compression.
   bool                    bIsCBRSupported;                             // If true, indicates that the encoder supports Constant Bit Rate.
   bool                    bIsVBRSupported;                             // If true, indicates that the encoder supports Variable Bit Rate.
};

//
// Summary:
//    Describes the decompression capabilities of an audio codec.
//
struct SMvAudioCodecDecompressionCapabilities
{
   uint32_t                size;                                        // Structure size in bytes.
   uint32_t                ui32eProfile;                                // Profile to be cast into a specific enumerator describing a profile.
   EMvAudioDataType        eSupportedInputAudioDataType;                // Enumerator describing the supported input format for decompression.
   bool                    bIsTemporalCompression;                      // If true, indicates that streams with temporal compression are supported.
   uint32_t                ui32NbSupportedOutputFormats;                // Number of valid structures in the array asSupportedOutputFormats.
   SMvAudioCodecIOFormats  
      asSupportedOutputFormats[kulMvMaxSupportedUncompressedFormats];   // Array of structures that contains the supported uncompressed audio codec output formats.
};

//
// Summary:
//    Describes the capabilities of an audio codec.
struct SMvAudioCodecInfo
{
   uint32_t                size;                                        // Structure size in bytes.
   wchar_t                 wszCodecName[256];                           // Codec name.
   GUID                    guidCodec;                                   // Specifies the unique identifier of the codec.
   IID                     iidMainSupportedInterface;                   // Specifies the unique identifier of the main interface.
   bool                    bSupportMultipleStreamsConcurrently;         // If true, indicates that the codec can work on multiple streams at the same time or that more than one instance of the codec has to be used.
   bool                    bIsHardwareCodec;                            // If true, indicates that the codec is a hardware codec.
   uint32_t                ui32MultipleInBytesForPitch;                 // Required alignment on memory for user buffer.
   bool                    bIsCompressionSupported;                     // If true, indicates that compression is supported.
   uint32_t                ui32SupportedCompressionCapsCount;           // Number of valid structures in the array asCodecCompressionCapabilities.
   SMvAudioCodecCompressionCapabilities
      asCodecCompressionCapabilities[kulMvMaxSupportedCodecFormats];    // Array of structures describing codec compression capabilities.
   bool                    bIsDecompressionSupported;                   // If true, indicates that decompression is supported.
   uint32_t                ui32SupportedDecompressionCapsCount;         // Number of valid structures in the array asCodecDecompressionCapabilities.
   SMvAudioCodecDecompressionCapabilities                                 
      asCodecDecompressionCapabilities[kulMvMaxSupportedCodecFormats];  // Array of structures describing codec decompression capabilities.
};

///////////////////////////////////////////////////////////////////////////////
//
// END of Audio Codec Definitions
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// Time code Definitions
//
///////////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)

typedef union
{
   uint64_t all;

   struct 
   {
      uint64_t  ucUnitOfFrames    : 4;  // 3:0
      uint64_t  ucTensOfFrames    : 2;  // 5:4

      uint64_t  ucUnitOfSeconds   : 4;  // 9:6
      uint64_t  ucTensOfSeconds   : 3;  // 12:10

      uint64_t  ucUnitOfMinutes   : 4;  // 16:13
      uint64_t  ucTensOfMinutes   : 3;  // 19:17

      uint64_t  ucUnitOfHours     : 4;  // 23:20
      uint64_t  ucTensOfHours     : 2;  // 25:24

      uint64_t  ucDropFrame       : 1;  // 26
      uint64_t  ucColorFrame      : 1;  // 27

      uint64_t  ucPolarityCorrect : 1;  // 28

      uint64_t  ucBinaryGrop0     : 1;  // 29

      uint64_t  ucBinaryGrop1     : 1;  // 30

      uint64_t  ucBinaryGrop2     : 1;  // 31

      uint64_t  ucBinaryGropData1 : 4;  // 35:32
      uint64_t  ucBinaryGropData2 : 4;  // 39:36

      uint64_t  ucBinaryGropData3 : 4;  // 43:40
      uint64_t  ucBinaryGropData4 : 4;  // 47:44

      uint64_t  ucBinaryGropData5 : 4;  // 51:48
      uint64_t  ucBinaryGropData6 : 4;  // 55:52

      uint64_t  ucBinaryGropData7 : 4;  // 59:56
      uint64_t  ucBinaryGropData8 : 4;  // 63:60

   } TimeCode;

} UMvRP188LTCTimeCode;
typedef UMvRP188LTCTimeCode UMvSMPTE12_LTC;


typedef union
{
   uint64_t all;

   struct
   {
      uint64_t  ucUnitOfFrames    : 4;  // 3:0
      uint64_t  ucTensOfFrames    : 2;  // 5:4

      uint64_t  ucUnitOfSeconds   : 4;  // 9:6
      uint64_t  ucTensOfSeconds   : 3;  // 12:10

      uint64_t  ucUnitOfMinutes   : 4;  // 16:13
      uint64_t  ucTensOfMinutes   : 3;  // 19:17

      uint64_t  ucUnitOfHours     : 4;  // 23:20
      uint64_t  ucTensOfHours     : 2;  // 25:24

      uint64_t  ucDropFrame       : 1;  // 26
      uint64_t  ucColorFrame      : 1;  // 27

      uint64_t  ucFieldPhase      : 1;  // 28

      uint64_t  ucBinaryGrop0     : 1;  // 29

      uint64_t  ucBinaryGrop1     : 1;  // 30

      uint64_t  ucBinaryGrop2     : 1;  // 31

      uint64_t  ucBinaryGropData1 : 4;  // 35:32
      uint64_t  ucBinaryGropData2 : 4;  // 39:36

      uint64_t  ucBinaryGropData3 : 4;  // 43:40
      uint64_t  ucBinaryGropData4 : 4;  // 47:44

      uint64_t  ucBinaryGropData5 : 4;  // 51:48
      uint64_t  ucBinaryGropData6 : 4;  // 55:52

      uint64_t  ucBinaryGropData7 : 4;  // 59:56
      uint64_t  ucBinaryGropData8 : 4;  // 63:60

   } TimeCode;

} UMvRP188VITCTimeCode;
typedef UMvRP188VITCTimeCode UMvSMPTE12_VITC;


typedef union
{
   uint64_t all;

   struct
   {
      uint64_t  ucUnitOfFrames    : 4;
      uint64_t  ucTensOfFrames    : 2;
      uint64_t  ucDropFrame       : 1;
      uint64_t  ucColorFrame      : 1; 

      uint64_t  ucUnitOfSeconds   : 4;
      uint64_t  ucTensOfSeconds   : 3;
      uint64_t  ucFieldPhase      : 1;

      uint64_t  ucUnitOfMinutes   : 4;
      uint64_t  ucTensOfMinutes   : 3;
      uint64_t  ucBinaryGrop0     : 1;

      uint64_t  ucUnitOfHours     : 4;
      uint64_t  ucTensOfHours     : 2;
      uint64_t  ucBinaryGrop1     : 1;
      uint64_t  ucBinaryGrop2     : 1;

      uint64_t  ucBinaryGropData1 : 4;  // 35:32
      uint64_t  ucBinaryGropData2 : 4;  // 39:36

      uint64_t  ucBinaryGropData3 : 4;  // 43:40
      uint64_t  ucBinaryGropData4 : 4;  // 47:44

      uint64_t  ucBinaryGropData5 : 4;  // 51:48
      uint64_t  ucBinaryGropData6 : 4;  // 55:52

      uint64_t  ucBinaryGropData7 : 4;  // 59:56
      uint64_t  ucBinaryGropData8 : 4;  // 63:60
   } TimeCode;

} UMvSMPTE331TimeCode;

#pragma pack(pop)

///////////////////////////////////////////////////////////////////////////////
//
// End of Time code Definitions
//
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//
// VANC Data Definitions
//
///////////////////////////////////////////////////////////////////////////////

// Specifies the closed caption type (cc_type). For more details on cc_type, refer to the CEA-708 standard.
enum EMvCCType 
{
   keMvCCTypeNTSCLine21Field1CC = 0,      // Indicates that the contents of cc_type is CEA-608-E line 21 field 1.
   keMvCCTypeNTSCLine21Field2CC = 1,      // Indicates that the contents of cc_type is CEA-608-E line 21 field 2.
   keMVCCTypeDTVCCChannelPacketData = 2,  // Indicates that the contents of cc_type is Digital Television Closed Caption (DTVCC) Channel Packet Data.
   keMvCCTypeDTVCCChannelPacketStart = 3  // Indicates that the contents of cc_type is DTVCC Channel Packet Start.
};

// This macro is used to get the string corresponding to the EMvCCType enum value.
#define MV_CC_TYPE_ENUM_TO_STRING(eValue) \
   ((eValue == keMvCCTypeNTSCLine21Field1CC)    ? ("NTSC Line 21 Field 1") : \
   (eValue == keMvCCTypeNTSCLine21Field2CC) ? ("NTSC Line 21 Field 2") : \
   (eValue == keMVCCTypeDTVCCChannelPacketData) ? ("DTVCC Channel Packet Data") : \
   (eValue == keMvCCTypeDTVCCChannelPacketStart) ? ("DTVCC Channel Packet Start") : \
   ("???"))


union UMvTopOrLeftBar 
{
   //If bTopPresenceFlag is true in SMvBarData, this represents the last line of a horizontal
   //letterbox at the top of the frame.
   uint16_t ui16LineNumberEndOfTopBar;

   //If bLeftPresenceFlag is true in SMvBarData, this represents the last line of a vertical
   //pillarbox on the left side of the frame.
   uint16_t ui16PixelNumberEndOfLeftBar;
};

union UMvBottomOrRightBar 
{
   //If bBottomPresenceFlag is true in SMvBarData, this represents the first line of a horizontal
   //letterbox at the bottom of the frame.
   uint16_t ui16LineNumberStartOfBottomBar;

   //If bRightPresenceFlag is true in SMvBarData, this represents the first line of a vertical
   //pillarbox on the right side of the frame.
   uint16_t ui16PixelNumberStartOfRightBar;
};

//
// Summary:
//    Specifies the stream's AFD (active format description) information. 
struct SMvAFD 
{
   //AFD code. Only the four least significant bits (LSBs) are considered.
   uint8_t ui8AFDCode;

   //If true, the video's aspect ratio is 16:9.
   bool bIs16by9AspectRatio;
};

//
// Summary:
//    Specifies the closed caption type (cc_type) and data (cc_data) if valid. For more details on cc_type and cc_data, refer to the CEA-708 standard.
struct SMvCCConstruct 
{
   //If true, the two closed caption data bytes (cc_data_1 and cc_data_2) are valid.
   bool bCC_Valid;

   //Indicates the closed caption data type (cc_type).
   EMvCCType eCCType;

   //Array containing the two closed caption data bytes (cc_data_1 and cc_data_2).
   uint8_t aui8CCData[2];
};

//
// Summary:
//    Specifies the closed caption service information.
struct SMvCCSVCConstruct 
{
   //Indicates the caption service number. Must be 0 for CEA-608 line 21 data.
   uint8_t ui8CaptionServiceNumber;

   // Array containing the caption service information (SVC) data bytes.
   uint8_t aui8SVC_Data_Byte[6];
};

//
// Summary:
//    Specifies the stream's caption distribution information.
struct SMvCaptionDistributionPacket
{
   // The Caption Distribution Packet (CDP) sequence counter must be 1 more than previous CDP packet. Wrap-around occurs at 16-bits.
   uint16_t    ui16CPDSequenceCounter;

   // Indicates the current frame rate.
   EMvFrameRate eFrameRate;

   // Indicates the current scan mode.
   EMvScanMode  eScanMode;

   // If true, the time code is valid.
   bool         bIsTimeCodeValid;

   // Indicates the time code value.
   UMvSMPTE12_VITC uSMPTE12_VITC_TimeCode;

   // If true, the closed caption data is valid.
   bool        bIsClosedCaptionDataValid;

   // Closed caption information (ccdata_section).

   // Indicates the number of closed caption constucts (CC_Const).
   uint32_t   ui32CC_Count;

   // Array of structures containing all closed caption constructs (CC_Const). Maximum number is 31.
   SMvCCConstruct asCC_Const[31];

   // If true, the closed caption service information is valid (ccsvcinfo_section).
   bool     bIsClosedCaptionServiceInformationValid;

   // If true, indicates the start of a complete set of caption service information.
   bool     bIsSVCInfoStart;

   // If true, indicates a change between two sets of caption service information.
   bool     bIsSVCInfoChange;

   // If true, indicates that the current packet concludes a full set of caption service information.
   bool     bIsSVCInfoComplete;

   // Indicates the number of CCSVC_Constructs present.
   uint32_t ui32SVC_Count;

   // Array of structures containing all the closed caption SVC Constructs (CCSVC_Constructs).
   SMvCCSVCConstruct asCCSVC_Const[15];
};

//
// Summary:
//    Indicates the location of the bar data.
// Remarks:
// - These boolean flags function as pairs (top and bottom, left and right), and cannot be combined in any other way.
//
struct SMvBarData 
{
   bool bTopPresenceFlag;    // If true, the bar data is located in the last line of a horizontal letterbox at the top of the frame.
                             // When this bool is set to true, bBottomPresenceFlag must also be set to true. 
   bool bBottomPresenceFlag; // If true, the bar data is located in the first line of a horizontal letterbox at the bottom of the frame.
                             // When this bool is set to true, bTopPresenceFlag must also be set to true. 
   bool bLeftPresenceFlag;   // If true, the bar data is located in the last pixel of a vertical pillarbox at the left side of the frame.
                             // When this bool is set to true, bRightPresenceFlag must also be set to true. 
   bool bRightPresenceFlag;  // If true, the bar data is located in the first pixel of a vertical pillarbox at the right side of the frame.
                             // When this bool is set to true, bLeftPresenceFlag must also be set to true. 

   //Depending on the value of the boolean flags, this either represents the last line 
   //of a horizontal letterbox at the top of the frame, or the last pixel of a vertical
   //pillarbox at the left side of the frame.
   UMvTopOrLeftBar uTopOrLeftBar;

   //Depending on the value of the boolean flags, this either represents the first line 
   //of a horizontal letterbox at the bottom of the frame, or the first pixel of a vertical
   //pillarbox on the right side of the frame.
   UMvBottomOrRightBar uBottomOrRightBar;
};

//
// Summary:
//    Specifies the stream's AFD (active format description) and bar data descriptors.
struct SMvAFDAndBarDataVancPacket 
{
   //AFD descriptor.
   SMvAFD sAFD;

   //Bar data descriptor.
   SMvBarData sBarData;
};

//
// Summary:
//    Specifies the stream's ancillary data packet format.
struct SMvGenericVancPacket 
{
   //Data ID (excludes parity bits).
   uint8_t ui8DID;

   //Data Block Number (for type 1 ANC packets) 
   //or Secondary Data ID (for type 2 ANC packets) (excludes parity bits).
   uint8_t ui8SDIDorDBN;

   //Data count (excludes parity bits).
   uint8_t ui8DC;

   //User data word (only the 10 LSbs of each UDW are taken into account).
   uint16_t aui16UDW[255];
};

//
// Summary:
//    Specifies the format of the closed captioning.
//
enum EMvCCFormat
{
   keMvCCFormatInvalid,                   // Invalid value.
   keMvCCFormatCEA608Line21_Analog,       // Indicates that the closed caption format is CEA-608 (analog line 21).
   keMvCCFormatCEA608inSMPTE334_Digital,  // Indicates that the closed caption format is CEA-608 (analog line 21) inserted in the CEA-708 section of the caption data packet (CDP) following the SMPTE 334 specification.
   keMvCCFormatNativeSMPTE334_Digital,    // Indicates that the closed caption format is the native CEA-708 in a CDP following the SMPTE 334 specification.
   keMvCCFormatLast                       // End of list indicator.
};

// This macro is used to get the string corresponding to the EMvCCFormat enum value.
#define MV_CC_FORMAT_TO_STRING(eValue) \
   ((eValue == keMvCCFormatInvalid)    ? ("Invalid CC Format") : \
   (eValue == keMvCCFormatCEA608Line21_Analog) ? ("CEA608 Line 21 Analog") : \
   (eValue == keMvCCFormatCEA608inSMPTE334_Digital) ? ("CEA608 SMPTE334 Digital") : \
   (eValue == keMvCCFormatNativeSMPTE334_Digital) ? ("Native SMPTE334 Digital") : \
   ("???"))


//
// Summary:
//    Specifies the type of the VANC packet used. 
// Note:
//    More than one type can be specified by using the bitwise OR operator.
//
enum EMvVANCPacketType 
{
   keMvVANCPacketTypeInvalid = 0,               // Invalid value.
   keMvVANCPacketTypeNone = 0,                  // Reserved.
   keMvVANCPacketTypeUnknown = 1,               // Indicates that an unknown VANC packet is used.
   keMvVANCPacketTypeAFDAndBarData = 2,         // Indicates that AFD and Bar Data VANC packets are used as per SMPTE 2016-3.
   keMvVANCPacketTypeCaptionDistribution = 4,   // Indicates that Caption Distribution Packet (CDP) VANC is used as per SMPTE 334-2. A CDP may contain closed caption, time code, and caption service information (SVC).
   keMvVANCPacketTypeAll = 7,                   // Indicates that aLL VANC packets are used.
   keMvVANCPacketTypeLast = 8                   // End of list indicator.
};

// This macro is used to get the string corresponding to the EMvVANCPacketType enum value.
#define MV_VANC_PACKET_TYPE_ENUM_TO_STRING(eValue) \
   ((eValue == keMvVANCPacketTypeInvalid)    ? ("Invalid") : \
   (eValue == keMvVANCPacketTypeUnknown) ? ("Unknown") : \
   (eValue == keMvVANCPacketTypeAFDAndBarData) ? ("AFD and Bar Data") : \
   (eValue == keMvVANCPacketTypeCaptionDistribution) ? ("CDP") : \
   (eValue == keMvVANCPacketTypeAll) ? ("All packets") : \
   (eValue == keMvVANCPacketTypeLast)        ? ("VANC packet type last") : \
   ("???"))

//
// Summary:
//    Specifies the type of the VANC data to be processed for H.264 compression and decompression. 
// Remarks:
// - This enumerator is used in the SMvH264SWDecompressionOptions and SMvAVCCompressionOptionsV3 structures. 
// - More than one type can be specified by using the bitwise OR operator.
//
enum EMvVANCInformationType 
{
   keMvVANCInformationTypeInvalid = 0,             // Invalid value.
   keMvVANCInformationTypeNone = 0,                // Indicates that no VANC packet types are to be processed.
   keMvVANCInformationTypeUnknown = 1,             // Indicates that the VANC packet contains an unknown data type.
   keMvVANCInformationTypeAFD = 2,                 // Indicates that the VANC packet contains AFD data.
   keMvVANCInformationTypeBarData = 4,             // Indicates that the VANC packet contains bar data.
   keMvVANCInformationTypeClosedCaption = 8,       // Indicates that the VANC packet contains closed caption data.
   keMvVANCInformationTypeCaptionService = 16,     // Indicates that the VANC packet contains caption service information (SVC).
   keMvVANCInformationTypeTimecode = 32,           // Indicates that the VANC packet contains time code data.
   keMvVANCInformationTypeAll = 63,                // Indicates that the VANC packet contains all data types.
   keMvVANCInformationTypeLast = 64                // End of list indicator.
};

// This macro is used to get the string corresponding to the EMvVANCInformationType enum value.
#define MV_VANC_INFORMATION_TYPE_ENUM_TO_STRING(eValue) \
   ((eValue == keMvVANCInformationTypeInvalid)    ? ("keMvVANCInformationTypeInvalid or None") : \
   (eValue == keMvVANCInformationTypeUnknown) ? ("keMvVANCInformationTypeUnknown") : \
   (eValue == keMvVANCInformationTypeAFD) ? ("keMvVANCInformationTypeAFD") : \
   (eValue == keMvVANCInformationTypeBarData) ? ("keMvVANCInformationTypeBarData") : \
   (eValue == keMvVANCInformationTypeClosedCaption) ? ("keMvVANCInformationTypeClosedCaption") : \
   (eValue == keMvVANCInformationTypeCaptionService) ? ("keMvVANCInformationTypeCaptionService") : \
   (eValue == keMvVANCInformationTypeTimecode) ? ("keMvVANCInformationTypeTimecode") : \
   (eValue == keMvVANCInformationTypeAll) ? ("keMvVANCInformationTypeAll") : \
   (eValue == keMvVANCInformationTypeLast)        ? ("keMvVANCInformationTypeLast") : \
   ("???"))



///////////////////////////////////////////////////////////////////////////////
//
// Video Codec Definitions
//
///////////////////////////////////////////////////////////////////////////////


//
// Summary:
//    Describes the compression capabilities of a video codec.
struct SMvVideoCodecCompressionCapabilities
{
   uint32_t                size;                         // Structure size in bytes.
   EMvSurfaceFormat        eSupportedOutputFormat;       // Specifies the compressed supported output surface format.
   uint32_t                ui32eProfile;                 // Profile ID.
   uint32_t                ui32eLevel;                   // Level ID.
   bool                    bIsTemporalCompression;       // If true, indicates that video streams with temporal compression are supported.
   uint32_t                ui32NbSupportedInputFormats;  // Number of valid structures in the array asSupportedInputFormat.
   SMvCodecIOFormats       
      asSupportedInputFormat[kulMvMaxSupportedUncompressedFormats]; // Array of structures that contains the supported uncompressed video codec input formats.
   uint32_t                ui32NbResolutionsSupported;   // Number of valid structures in the array asCodecResolutionSupported.
   SMvCodecResolutions     
      asCodecResolutionSupported[kulMvMaxSupportedUncompressedFormats]; // Array of structures that contains the supported uncompressed video resolutions.
   bool                    bIsBitRateProgrammable;                      // If true, indicates that the bit rates can be programmed.
   uint32_t                ui32MinBitRateInBitsPerSec;                  // Indicates the minimum bit rate in bits per second.
   uint32_t                ui32MaxBitRateInBitsPerSec;                  // Indicates the maximum bit rate in bits per second.
   bool                    bIsCBRSupported;                             // If true, indicates that Constant Bit Rate encoding is supported.
   bool                    bIsVBRSupported;                             // If true, indicates that Variable Bit Rate encoding is supported.
   bool                    bIsClosedCaptionSupported;                   // If true, indicates that closed caption is supported.  
};


//
// Summary:
//    Describes the decompression capabilities of a video codec.
//
struct SMvVideoCodecDecompressionCapabilities
{
   uint32_t                size;                         // Structure size in bytes.
   EMvSurfaceFormat        eSupportedInputFormat;        // Specifies the compressed supported input surface format.
   uint32_t                ui32eProfile;                 // Profile ID.
   uint32_t                ui32eLevel;                   // Level ID.
   bool                    bIsTemporalCompression;       // If true, indicates that video streams with temporal compression are supported.
   uint32_t                ui32NbSupportedOutputFormats; // Number of valid structures in the array asSupportedOutputFormat.
   SMvCodecIOFormats       
      asSupportedOutputFormat[kulMvMaxSupportedUncompressedFormats]; // Array of structures that contains the supported uncompressed video codec output formats.
   uint32_t                ui32NbResolutionsSupported;   // Number of valid structures in the array asCodecResolutionSupported.
   SMvCodecResolutions     
      asCodecResolutionSupported[kulMvMaxSupportedUncompressedFormats]; // Array of structures that contains the supported uncompressed video resolutions.
   bool                    bIsEmbeddedColorCorrectionSupported;         // If true, indicates that embedded color correction is supported.
   bool                    bIsUpscaleToHDSupported;                     // If true, indicates that upscaling to HD is supported.
   bool                    bIsDownscaleToSDSupported;                   // If true, indicates that downscaling to SD is supported.
   bool                    bIsClosedCaptionSupported;                   // If true, indicates that closed caption is supported.
};

//
// Summary:
//    Describes the capabilities of a video codec.
struct SMvVideoCodecInfo
{
   uint32_t                size;                                        // Structure size in bytes.
   wchar_t                 wszCodecName[256];                           // Codec name.
   GUID                    guidCodec;                                   // Specifies the unique identifier of the codec.
   IID                     iidMainSupportedInterface;                   // Specifies the unique identifier of the main interface.
   bool                    bSupportMultipleStreamsConcurrently;         // If true, indicates that the codec can work on multiple streams at the same time or that more than one instance of the codec has to be used.
   bool                    bIsHardwareCodec;                            // If true, indicates that the codec is a hardware codec.
   uint32_t                ui32MultipleInBytesForPitch;                 // Required alignment on memory for user buffer.
   bool                    bIsCompressionSupported;                     // If true, indicates that compression is supported.
   uint32_t                ui32SupportedCompressionCapsCount;           // Number of valid structures in the array asCodecCompressionCapabilities.
   SMvVideoCodecCompressionCapabilities
      asCodecCompressionCapabilities[kulMvMaxSupportedCodecFormats];    // Array of structures describing codec compression capabilities.
   bool                    bIsDecompressionSupported;                   // If true, indicates that decompression is supported.
   uint32_t                ui32SupportedDecompressionCapsCount;         // Number of valid structures in the array asCodecDecompressionCapabilities.
   SMvVideoCodecDecompressionCapabilities                                 
      asCodecDecompressionCapabilities[kulMvMaxSupportedCodecFormats];  // Array of structures describing codec decompression capabilities.
};

//
// Summary:
//    Describes the Matrox H.264/AVC hardware encoder compression options.
struct SMvAVCCompressionOptions
{
   // Size of the structure in bytes.
   uint32_t             size;        

   // Input resolution of the codec (resolution of received uncompressed buffers).
   SMvResolutionInfo    sResolutionInput;                                  
   
   // Output resolution of the codec (resolution of "file" compressed buffers).
   SMvResolutionInfo    sResolutionOutput;                                 
   
   // Indicates the H.264/AVC Profile.
   EMvH264Profile       eProfile;                                          
   
   // Indicates the H.264/AVC Level.
   EMvH264Level         eLevel;                                            
   
   // Requested average bit rate.  For SMvAVCCompressionOptionsV4 and prior, this is the 
   // average data rate.  For SMvAVCCompressionOptionsV5 and later, it is used only for keMvBitRateModelCBR and keMvBitRateModelVBR bit 
   // rate models.
   uint32_t             ui32AverageBitRateInBitsPerSec;                    
   
   // Bit rate mode to use.   For SMvAVCCompressionOptionsV4 and prior, only keMvBitRateModelCBR 
   // and keMvBitRateModelVBR model are valid.
   EMvBitRateModel      eBitRateMode;                                      
   
   // Indicates the GOP structure type to use.
   EMvGOPStructureType  eGOPStructureType;                                 

   // Indicates the distance between two IDR frames.  This must be a multiple of the distance between I-frames.  This is also the GOP size.  This is used in simple GOPs only. Otherwise, it is ignored.
   uint32_t             ui32DistanceBetweenIDRFrames;                      

   // Indicates the distance between two I-frames.  (IDR frames are considered I-frames).  This is used in Simple GOPs only, otherwise, it is ignored.
   uint32_t             ui32DistanceBetweenIFrames;                        

   // Indicates the distance between 2 reference frames (P, I, or IDR).  That number minus one indicates the number of B-frames.  This is used in simple GOPs only. Otherwise, it is ignored.
   uint32_t             ui32DistanceBetweenReferences;                     

   // If true, indicates that a synchronous open operation must be forced.
   bool                 bForceSynchronousOpen;                             
};

//
// Summary:
//    Describes the Matrox H.264/AVC hardware encoder compression options (version 2).
struct SMvAVCCompressionOptionsV2 : public SMvAVCCompressionOptions
{
   // Indicates the colorimetry of the compression.
   EMvColorimetry eColorimetry;

   // Indicates the pixel aspect ratio of the compression.
   SMvFraction    sPixelAspectRatio;

   // If true, indicates that overscan is present. Otherwise, false.
   bool           bOverscan;
   
   // If true, indicates that the compression is performed in an external reference file (.264).
   // The name of this flag is wrong. It is used to indicate if the NAL units generated must be compatible (as best as possible)
   // to the AVC-HD specification.
   bool           bExternalReference;

};

//
// Summary:
//    Describes the Matrox H.264/AVC hardware encoder compression options (version 3).
struct SMvAVCCompressionOptionsV3 : public SMvAVCCompressionOptionsV2
{
   // If true, indicates that the VANC information can be retrieved from external VBI/VANC surfaces. If false, it can only be retrieved from Line 21 of NTSC video.
   // Currently, compression of closed captioning is only supported if it is extracted from VBI surfaces. Extraction from line 21 (NTSC) is not supported.
   // Therefore, this flag must be set to true if eVancInformationTypeToEncode is set.
   bool                       bExpectInputVBISurfaces;             

   //Indicates the model of VANC encoding.
   EMvH264VancModel           eVancModel;                          
   
   //Specifies the information to be encoded.
   //If the type of VANC information is something other than "none" or "time code", the caller must send VBI buffers. Otherwise the 
   //codec will wait for those buffers indefinitely.
   EMvVANCInformationType     eVancInformationTypeToEncode;        
   
   //If true, indicates that the analog closed caption should be encoded (if present) for PAL and NTSC video. Otherwise, false. 
   //If analog and VANC digital data are both present, only VANC digital data will be processed.
   //This flag is not currently being used. It is intended for future use.
   bool                       bEncodeAnalogClosedCaptionIfPresent; 
                                                                   
};

//
// Summary:
//    Describes the Matrox H.264/AVC hardware encoder compression options (version 4), which provides support for additional frame rates.
struct SMvAVCCompressionOptionsV4 : public SMvAVCCompressionOptionsV3
{
   //Specifies the float frame rate, which can be from 1/1.001 up to 120/1.001.
   float fFrameRate;                                              
};

//
// Summary:
//    Describes the Matrox H.264/AVC hardware encoder compression options (version 5).
// Description:
//    This structure derives from the SMvAVCCompressionOptionsV4 structure to add more control over the encoding
//    parameters of the H.264 hardware encoder.
struct SMvAVCCompressionOptionsV5 : SMvAVCCompressionOptionsV4
{
   // Specifies the noise filtering strength that is applied before encoding.  Value range from 0% (no filtering) to 
   // 100% (strongest filtering).  Default value is 0%.
   uint32_t          ui32NoiseFilterStrength;

   // Specifies how frequently the encoder verifies the current data rate while encoding and compares it
   // to your specified target data rate. If a discrepancy exists between the current and target data rates, the current
   // data rate is adjusted as specified by the ui32DataRateAdustment option.  Used only for keMvBitRateModelCBR and 
   // keMvBitRateModelVBR bit rate models. Default value is keMvH264SampleRateLow.
   EMvH264SampleRate eSampleRate;

   // Specifies how quickly the current data rate is adjusted to reach the target data rate. 
   // A gradual adjustment produces smoother transitions than a quick adjustment. Value range from 0% (slowest speed) 
   // to 100% (highest speed). Used only for keMvBitRateModelCBR and keMvBitRateModelVBR bit rate models.
   // Default value is 50%.
   uint32_t          ui32DataRateAdustment;

   // Specifies the video data complexity.  Value range from from 0 (very complex) to 255 (Not complex at all).  Used 
   // only for keMvBitRateModelVBR bit rate model. Default value is 14.
   // <b>Note:</b> The default value is applicable to a wide range of video complexity, but is unsuitable for low complexity and 
   // very high complexity video.  The encoder will not be able to obtain the requested data rate resulting in lower 
   // or higher values than expected.
   uint32_t          ui32VideoComplexity;

   // Specifies the minimum data rate in percentage of the average data rate.  Value range from 0% to 100%.  For good 
   // general results, use 25% of the average data rate.  Used only for keMvBitRateModelVBR bit rate model. 
   uint32_t          ui32VbrMinDataRate;

   // Specifies the maximum data rate in percentage of the average data rate.  Value range from 100% to 800%.  For
   // good general results, use 300% when average data rate is over 3Mb/seconds otherwise compute the percentage to 
   // make the maximum data rate be 3Mb/seconds (without going go over 800%). Used only for keMvBitRateModelVBR bit rate 
   // model. 
   uint32_t          ui32VbrMaxDataRate;

   // Specifies the quality of the encoding.  This will give a video compression with constant quality but with unpredictable
   // data rate as it will completely depend on video data. Value range from 0 (lowest quality) to 100 (highest quality).
   // Used only for keMvBitRateModelConstantQuality bit rate model.
   uint32_t          ui32QualityFactor;
};


//
// Summary:
//    Describes the Matrox H.264/AVC encoding options for software-based encoding, or hardware-accelerated encoding using Intel Quick Sync Video (QSV).
// 
struct SMvH264CompressionOptions
{
   // Size of the structure.
   uint32_t                ui32Size;

   // Input resolution of the encoder (resolution of received uncompressed buffers).
   SMvResolutionInfo       sResolutionInput;                                  

   // Output resolution of the encoder (resolution of "file" compressed buffers).
   SMvResolutionInfo       sResolutionOutput;                                 

   // H.264/AVC Profile.
   EMvH264Profile          eProfile;                                          

   // H.264/AVC Level.
   EMvH264Level            eLevel;    

   // Distance between two IDR frames in terms of number of I-frames. For example, <p>
   // if ui16IdrInterval = 0, then every I-frame is an IDR-frame, and <p>
   // if ui16IdrInterval = 1, then every other I-frame is an IDR-frame, and so on.
   uint16_t                ui16IdrInterval;

   // Indicates the distance between two I-frames (IDR frames are considered I-frames).
   uint32_t                ui32GopPictureSize;             

   // Indicates the distance between two reference frames (P, I, or IDR).
   uint32_t                ui32DistanceBetweenReferences;

   // Specifies the desired behavior of the encoder in terms of quality and speed. It exposes a
   // trade-off between these two characteristics. Values range from 0 to 2 as follows: <p>
   // 0: Best quality <p>
   // 1: Balanced <p>
   // 2: Best speed
   uint8_t                 ui8TargetUsage;

   // Bit rate mode to use.
   EMvBitRateModel         eBitRateMode;      

   // Indicates the target bit rate in bits per second. For constant bit rate (CBR) and variable bit rate (VBR) modes.
   uint32_t                ui32TargetBitRateInBitsPerSec;

   // Indicates the maximum bit rate in bits per second. For VBR mode only.
   uint32_t                ui32VbrMaxBitRateInBitsPerSec;

   // For constant quality encoding only.
   // Quantization parameter for I-frames. Values are between 0 and 51.
   uint16_t                ui16QPI;

   // For constant quality encoding only.
   // Quantization parameter for B-frames. Values are between 0 and 51.
   uint16_t                ui16QPB;

   // For constant quality encoding only.
   // Quantization Parameter for P-frames. Values are between 0 and 51.
   uint16_t                ui16QPP;

   // If true, indicates that VANC data should be processed and that the codec expects VANC surfaces.
   bool                    bProcessVANCData;

   // Indicates the model of VANC encoding.
   EMvH264VancModel        eVancModel;                          

   // Specifies the type of VANC data to be encoded. <p>
   // If the type of VANC data is something other than "none" or "time code", the caller must send VBI buffers. 
   // Otherwise, the encoder will wait for those buffers indefinitely.
   EMvVANCInformationType  eVancInformationTypeToEncode;

   // If true, indicates that the de-interlacer will be used.
   bool                    bUseDeinterlacer;
};

// Configures the H.264/AVC software encoder preset.
// Note:
// - Used in SMvH264SWCompressionOptionsHeader.
enum EMvH264SWCodecPreset
{
   keMvH264SWCodecPresetInvalid,       // Invalid value.
   keMvH264SWCodecPresetGeneric,       // Indicates a generic all-purpose H.264 software encoder preset.
   keMvH264SWCodecPresetAVCUltra,      // Indicates a Panasonic AVC Ultra software encoder preset.
   keMvH264SWCodecPresetXAVC,          // Indicates a Sony XAVC software encoder preset.
   keMvH264SWCodecPresetLast           // End of list indicator.
};

//Enumeration used in the SMvH264SWAVCUltraCompressionOptions structure to configure the H.264/AVC software encoder
enum EMvH264SWCodecTargetUsage
{
   keMvH264SWCodecTargetUsageInvalid,
   keMvH264SWCodecTargetUsageDefault,      // Default values
   keMvH264SWCodecTargetUsageBestSpeed,     // Faster but lower quality
   keMvH264SWCodecTargetUsageLast
};

// enumeration in SMvH264SWAVCUltraCompressionOptions structure to select the preset for H.264 AVC Ultra
enum EMvAVCUltraProfile
{
   keMvAVCUltraProfileInvalid  = 0,
   keMvAVCUltraProfileLongG25,     // Panasonic LongG 25
   keMvAVCUltraProfileLast
};

// Selects the preset for H.264 Sony XAVC compression.
// Note:
//    Used in SMvH264SWXAVCCompressionOptions.
enum EMvXAVCProfile
{
   keMvXAVCProfileInvalid  = 0,  // Invalid value.
   keMvXAVCProfileLongGOP25,     // Indicates that the preset is Sony XAVC LongGOP 25.
   keMvXAVCProfileLongGOP35,     // Indicates that the preset is Sony XAVC LongGOP 35.
   keMvXAVCProfileLongGOP50,     // Indicates that the preset is Sony XAVC LongGOP 50.
   keMvXAVCProfileHDIntra100CBG,    // Indicates that the preset is Sony XAVC HD Intra Class 100.
   keMvXAVCProfile4KIntra300CBG, // Indicates that the preset is Sony XAVC 4K Intra Class 300 CBG.
   keMvXAVCProfile4KIntra480CBG, // Indicates that the preset is Sony XAVC 4K Intra Class 480 CBG.
   keMvXAVCProfile4KIntra300VBR, // Indicates that the preset is Sony XAVC 4K Intra Class 300 VBR.
   keMvXAVCProfile4KIntra480VBR, // Indicates that the preset is Sony XAVC 4K Intra Class 480 VBR.
   keMvXAVCProfileLast           // End of list indicator.
};

//
// Summary:
//    Describes a header for the H.264/AVC software codec compression options.
// Note:
//    This structure will be derived from the H.264/AVC software codec compression options structures.
//    That is, SMvH264SWAVCUltraCompressionOptions, SMvH264SWXAVCCompressionOptions, or SMvH264SWGenericCompressionOptions. This means that 
//    the ui32size parameter must be set to the size of the structure from which this structure is derived, not to the size of the header 
//    structure (this structure).
struct SMvH264SWCompressionOptionsHeader 
{   
   uint32_t             ui32size;            // Structure size in bytes of the structure from which this structure is derived (see note).   
   EMvH264SWCodecPreset ePreset;             // H.264 SW Codec preset
   SMvResolutionInfo    sResolutionInput;    // Input resolution of the encoder (resolution of received uncompressed buffers).
   SMvResolutionInfo    sResolutionOutput;   // Output resolution of the encoder (resolution of "file" compressed buffers).
 

   SMvH264SWCompressionOptionsHeader()
   {
      ui32size = sizeof(SMvH264SWCompressionOptionsHeader);
      ePreset = keMvH264SWCodecPresetInvalid;
      ZeroMemory(&sResolutionInput, sizeof(sResolutionInput));
      ZeroMemory(&sResolutionOutput, sizeof(sResolutionOutput));
   }

   bool isInputResolutionScanModeInterlaced()
   {
      if (ui32size == sizeof(SMvH264SWCompressionOptionsHeader))
      {
         return false;
      }
      else
      {
         return sResolutionInput.eScanMode == keMvScanModeFirstFieldTop ||
            sResolutionInput.eScanMode == keMvScanModeSecondFieldTop ||
            sResolutionInput.eScanMode == keMvScanModeInterlacedFieldsInAFrame;
      }
   }
   void setInputResolutionScanMode(EMvScanMode in_eScanMode)
   {
      if (in_eScanMode > keMvScanModeInvalid && in_eScanMode < keMvScanModeLast)
      {
         sResolutionInput.eScanMode = in_eScanMode;
      }
   }
};

//
// Summary:
//    Describes the H.264/AVC software generic codec compression options.
// Note:
//    This structure derives from the SMvH264SWCompressionOptionsHeader. The preset used should be 
//    SMvH264SWCompressionOptionsHeader::ePrest=keMvH264SWCodecPresetGeneric.
struct SMvH264SWGenericCompressionOptions : public SMvH264SWCompressionOptionsHeader
{
   // Indicates the H.264/AVC profile.
   EMvH264Profile          eProfile;                                          

   // Indicates the H.264/AVC level.
   EMvH264Level            eLevel;    

   // If this value is 0 only the first frame is IDR, if it is 1 every I-frame is IDR, etc.
   uint32_t                ui32IdrFrequency;

   // Indicates the distance between two I-frames (IDR frames are considered I-frames).
   uint32_t                ui32GopPictureSize;             

   // Indicates the distance between two reference frames (P, I, or IDR).
   uint32_t                ui32DistanceBetweenReferences;

   // Indicates the bit rate mode to use.
   EMvBitRateModel         eBitRateMode;      

   // Indicates the target bit rate in bits per second. For constant bit rate (CBR) and variable bit rate (VBR) modes.
   uint32_t                ui32TargetBitRateInBitsPerSec;
   
   // Indicates the maximum bit rate in bits per second. For VBR mode only.
   uint32_t                ui32VbrMaxBitRateInBitsPerSec;

   // For constant quality encoding only.
   // Quantization parameter for I-frames. Values are between 0 and 51.
   uint32_t                ui32QPI;

   // For constant quality encoding only.
   // Quantization parameter for B-frames. Values are between 0 and 51.
   uint32_t                ui32QPB;

   // For constant quality encoding only.
   // Quantization Parameter for P-frames. Values are between 0 and 51.
   uint32_t                ui32QPP;

   SMvH264SWGenericCompressionOptions()
   {
      ui32size = sizeof(SMvH264SWGenericCompressionOptions);
      eProfile = keMvH264ProfileInvalid;
      eLevel = keMvH264ProfileLevelInvalid;
      ui32IdrFrequency = 0;
      ui32GopPictureSize = 0;
      ui32DistanceBetweenReferences = 0;
      eBitRateMode = keMvBitRateModelInvalid;
      ui32TargetBitRateInBitsPerSec = 0;
      ui32VbrMaxBitRateInBitsPerSec = 0;
      ui32QPI = 0;
      ui32QPB = 0;
      ui32QPP = 0;
      ePreset = keMvH264SWCodecPresetGeneric;
   }

   bool operator==(SMvH264SWGenericCompressionOptions& sOpt2)
   {
      return ui32size == sOpt2.ui32size
         && eProfile == sOpt2.eProfile
         && eLevel == sOpt2.eLevel
         && ui32IdrFrequency == sOpt2.ui32IdrFrequency
         && ui32GopPictureSize == sOpt2.ui32GopPictureSize
         && ui32DistanceBetweenReferences == sOpt2.ui32DistanceBetweenReferences
         && eBitRateMode == sOpt2.eBitRateMode
         && ui32TargetBitRateInBitsPerSec == sOpt2.ui32TargetBitRateInBitsPerSec
         && ui32VbrMaxBitRateInBitsPerSec == sOpt2.ui32VbrMaxBitRateInBitsPerSec
         && ui32QPI == sOpt2.ui32QPI
         && ui32QPB == sOpt2.ui32QPB
         && ui32QPP == sOpt2.ui32QPP
         && ePreset == sOpt2.ePreset
         && sResolutionInput.eAspectRatio == sOpt2.sResolutionInput.eAspectRatio
         && sResolutionInput.eFrameRate == sOpt2.sResolutionInput.eFrameRate
         && sResolutionInput.eScanMode == sOpt2.sResolutionInput.eScanMode
         && sResolutionInput.size == sOpt2.sResolutionInput.size
         && sResolutionInput.ulComponentBitCount == sOpt2.sResolutionInput.ulComponentBitCount
         && sResolutionInput.ulHeight == sOpt2.sResolutionInput.ulHeight
         && sResolutionInput.ulWidth == sOpt2.sResolutionInput.ulWidth
         && sResolutionOutput.eAspectRatio == sOpt2.sResolutionOutput.eAspectRatio
         && sResolutionOutput.eFrameRate == sOpt2.sResolutionOutput.eFrameRate
         && sResolutionOutput.eScanMode == sOpt2.sResolutionOutput.eScanMode
         && sResolutionOutput.size == sOpt2.sResolutionOutput.size
         && sResolutionOutput.ulComponentBitCount == sOpt2.sResolutionOutput.ulComponentBitCount
         && sResolutionOutput.ulHeight == sOpt2.sResolutionOutput.ulHeight
         && sResolutionOutput.ulWidth == sOpt2.sResolutionOutput.ulWidth;
   }

};

//
// Summary:
//    Describes the H.264/AVC software Panasonic AVC Ultra codec compression options.
// Description:
//    This structure derives from the SMvH264SWCompressionOptionsHeader. The preset used should be 
//    SMvH264SWCompressionOptionsHeader::ePreset=keMvH264SWCodecPresetAVCUltra.
struct SMvH264SWAVCUltraCompressionOptions : public SMvH264SWCompressionOptionsHeader
{
   
   // Specifies the Panasonic AVC Ultra preset to use.
   EMvAVCUltraProfile eAVCUltraProfile; 

   // Specifies the desired behavior of the encoder in terms of quality and speed. It exposes a
   // trade-off between these two characteristics. That is, if the speed is increased, the quality is reduced.
   EMvH264SWCodecTargetUsage  eTargetUsage; 

   SMvH264SWAVCUltraCompressionOptions()
   {
      ui32size = sizeof(SMvH264SWAVCUltraCompressionOptions);
      eAVCUltraProfile = keMvAVCUltraProfileInvalid;
      eTargetUsage = keMvH264SWCodecTargetUsageInvalid;
      ePreset = keMvH264SWCodecPresetAVCUltra;
   }

};

//
// Summary:
//    Describes the H.264/AVC software Sony XAVC codec compression options.
// Note:
//    This structure derives from the SMvH264SWCompressionOptionsHeader. The preset used should be 
//    SMvH264SWCompressionOptionsHeader::ePreset=keMvH264SWCodecPresetXAVC.
struct SMvH264SWXAVCCompressionOptions : public SMvH264SWCompressionOptionsHeader
{
   EMvXAVCProfile eXAVCProfile;  // Specifies the Sony XAVC preset to use.

   SMvH264SWXAVCCompressionOptions()
   {
      ui32size = sizeof(SMvH264SWXAVCCompressionOptions);
      eXAVCProfile = keMvXAVCProfileInvalid;
      ePreset = keMvH264SWCodecPresetXAVC;
   }

   bool operator==(SMvH264SWXAVCCompressionOptions& sOpt2)
   {
      return ui32size == sOpt2.ui32size
         && ePreset == sOpt2.ePreset
         && eXAVCProfile == sOpt2.eXAVCProfile
         && sResolutionInput.eAspectRatio == sOpt2.sResolutionInput.eAspectRatio
         && sResolutionInput.eFrameRate == sOpt2.sResolutionInput.eFrameRate
         && sResolutionInput.eScanMode == sOpt2.sResolutionInput.eScanMode
         && sResolutionInput.size == sOpt2.sResolutionInput.size
         && sResolutionInput.ulComponentBitCount == sOpt2.sResolutionInput.ulComponentBitCount
         && sResolutionInput.ulHeight == sOpt2.sResolutionInput.ulHeight
         && sResolutionInput.ulWidth == sOpt2.sResolutionInput.ulWidth
         && sResolutionOutput.eAspectRatio == sOpt2.sResolutionOutput.eAspectRatio
         && sResolutionOutput.eFrameRate == sOpt2.sResolutionOutput.eFrameRate
         && sResolutionOutput.eScanMode == sOpt2.sResolutionOutput.eScanMode
         && sResolutionOutput.size == sOpt2.sResolutionOutput.size
         && sResolutionOutput.ulComponentBitCount == sOpt2.sResolutionOutput.ulComponentBitCount
         && sResolutionOutput.ulHeight == sOpt2.sResolutionOutput.ulHeight
         && sResolutionOutput.ulWidth == sOpt2.sResolutionOutput.ulWidth;
   }

};

//
// Summary:
//    Enumeration used in the SMvM264CompressionOptionsHeader structure to configure the M264 encoder.
enum EMvM264CompressionPreset
{
   keMvM264CompressionPresetInvalid,
   keMvM264CompressionPresetGeneric,      // Generic, all purpose H.264
   keMvM264CompressionPresetXAVC,         // Sony XAVC
   keMvM264CompressionPresetLast
};

//
// Summary:
//    Describes a header for the M264 encoder compression options.
// Description:
//    This structure will be derived by the M264 compression options structures.
//    The ui32size parameter should be set to the size of the derived structure, not to the size of the header structure (this structure).
struct SMvM264CompressionOptionsHeader
{
   uint32_t                  ui32size;                 // Structure size in bytes.
   EMvM264CompressionPreset  ePreset;                  // M264 compression preset
   SMvResolutionInfo         sResolutionInput;         // Resolution of received uncompressed buffers.
   SMvResolutionInfo         sResolutionOutput;        // Resolution of compressed stream.
   EMvHardwareProfile        eHardwareProfileType;     // Indicates which hardware profile to use.
   uint32_t                  ulHardwareProfileIndex;   // Specifies the index of the hardware profile to use.

   SMvM264CompressionOptionsHeader()
   {
      ui32size = sizeof(SMvM264CompressionOptionsHeader);
      ePreset = keMvM264CompressionPresetInvalid;
      ZeroMemory(&sResolutionInput, sizeof(sResolutionInput));
      ZeroMemory(&sResolutionOutput, sizeof(sResolutionOutput));
      eHardwareProfileType = keMvHardwareProfileInvalid;
      ulHardwareProfileIndex = 0;
   }
};

//
// Summary:
//    Describes the M264 generic compression options.
// Description:
//    This structure derives from the SMvM264CompressionOptionsHeader. The preset used should be keMvM264CompressionPresetGeneric.
struct SMvM264GenericCompressionOptions : public SMvM264CompressionOptionsHeader
{
   // H.264/AVC Profile.
   EMvH264Profile          eProfile;

   // H.264/AVC Level.
   EMvH264Level            eLevel;

   // Indicates the distance between two IDR or I frames, must be a multiple of ui32DistanceBetweenReferences or, (multiple of ui32DistanceBetweenReferences) + 1.
   uint32_t                ui32GopPictureSize;

   //Indicated the frequency IDR frames are inserted (0: Only first frame, 1: every frame, etc)
   uint32_t                ui32IdrFrequency;

   // Indicates the distance between two reference frames (P, I, or IDR), maximum value is 8.
   uint32_t                ui32DistanceBetweenReferences;

   // Indicates the entropy coding mode
   EMvEntropyCodingMode    eEntropyCodingMode;

   // Bit rate mode to use.
   EMvBitRateModel         eBitRateMode;

   // Indicates the target bit rate in bits per second. For constant bit rate (CBR) and variable bit rate (VBR) modes.
   uint32_t                ui32TargetBitRateInBitsPerSec;
   
   // Indicates the maximum bit rate in bits per second. For VBR mode only.
   uint32_t                ui32VbrMaxBitRateInBitsPerSec;

   // For constant quality encoding only.
   // Quantization parameter. Values are between -12 and 51.
   int32_t                 i32QP;

   // Number of slices to be used in encode sequence. 0 is auto. SD and HD 1-12, QuadHD 2-16
   uint32_t                ui32NbSlices;

   // Coded Picture Buffer (CPB) size in bits for the Hypothetical Reference Decoder (HRD).
   // Setting to 0 will use default value. Must be aligned to 64 bits.
   // Not implemented yet. Setting this will have no effect.
   uint32_t                ui32CPBSizeInBits;

   SMvM264GenericCompressionOptions()
   {
      ui32size = sizeof(SMvM264GenericCompressionOptions);
      eProfile = keMvH264ProfileInvalid;
      eLevel = keMvH264ProfileLevelInvalid;
      ui32GopPictureSize = 0;
      ui32IdrFrequency = 0;
      ui32DistanceBetweenReferences = 0;
      eEntropyCodingMode = keMvEntropyCodingInvalid;
      eBitRateMode = keMvBitRateModelInvalid;
      ui32TargetBitRateInBitsPerSec = 0;
      ui32VbrMaxBitRateInBitsPerSec = 0;
      i32QP = 0;
      ePreset = keMvM264CompressionPresetGeneric;
      ui32NbSlices = 0;
      ui32CPBSizeInBits = 0;
   }

   bool operator==(SMvM264GenericCompressionOptions& sOpt2)
   {
      return ui32size == sOpt2.ui32size
         && eProfile == sOpt2.eProfile
         && eLevel == sOpt2.eLevel
         && ui32GopPictureSize == sOpt2.ui32GopPictureSize
         && ui32IdrFrequency == sOpt2.ui32IdrFrequency
         && ui32DistanceBetweenReferences == sOpt2.ui32DistanceBetweenReferences
         && eEntropyCodingMode == sOpt2.eEntropyCodingMode
         && eBitRateMode == sOpt2.eBitRateMode
         && ui32TargetBitRateInBitsPerSec == sOpt2.ui32TargetBitRateInBitsPerSec
         && ui32VbrMaxBitRateInBitsPerSec == sOpt2.ui32VbrMaxBitRateInBitsPerSec
         && i32QP == sOpt2.i32QP
         && ePreset == sOpt2.ePreset
         && ui32NbSlices == sOpt2.ui32NbSlices
         && ui32CPBSizeInBits == sOpt2.ui32CPBSizeInBits
         && sResolutionInput.eAspectRatio == sOpt2.sResolutionInput.eAspectRatio
         && sResolutionInput.eFrameRate == sOpt2.sResolutionInput.eFrameRate
         && sResolutionInput.eScanMode == sOpt2.sResolutionInput.eScanMode
         && sResolutionInput.size == sOpt2.sResolutionInput.size
         && sResolutionInput.ulComponentBitCount == sOpt2.sResolutionInput.ulComponentBitCount
         && sResolutionInput.ulHeight == sOpt2.sResolutionInput.ulHeight
         && sResolutionInput.ulWidth == sOpt2.sResolutionInput.ulWidth
         && sResolutionOutput.eAspectRatio == sOpt2.sResolutionOutput.eAspectRatio
         && sResolutionOutput.eFrameRate == sOpt2.sResolutionOutput.eFrameRate
         && sResolutionOutput.eScanMode == sOpt2.sResolutionOutput.eScanMode
         && sResolutionOutput.size == sOpt2.sResolutionOutput.size
         && sResolutionOutput.ulComponentBitCount == sOpt2.sResolutionOutput.ulComponentBitCount
         && sResolutionOutput.ulHeight == sOpt2.sResolutionOutput.ulHeight
         && sResolutionOutput.ulWidth == sOpt2.sResolutionOutput.ulWidth;
   }
};


//
// Summary:
//    Describes the M264 XAVC compression options.
// Description:
//    This structure derives from the SMvM264CompressionOptionsHeader. The preset used should be keMvM264CompressionPresetXAVC.
struct SMvM264XAVCCompressionOptions : public SMvM264CompressionOptionsHeader
{
   EMvXAVCProfile eXAVCProfile;  // Specifies the Sony XAVC preset to use.

   SMvM264XAVCCompressionOptions()
   {
      ui32size = sizeof(SMvM264XAVCCompressionOptions);
      eXAVCProfile = keMvXAVCProfileInvalid;
      ePreset = keMvM264CompressionPresetXAVC;
   }

   bool operator==(SMvM264XAVCCompressionOptions& sOpt2)
   {
      return ui32size == sOpt2.ui32size
         && eXAVCProfile == sOpt2.eXAVCProfile
         && ePreset == sOpt2.ePreset
         && sResolutionInput.eAspectRatio == sOpt2.sResolutionInput.eAspectRatio
         && sResolutionInput.eFrameRate == sOpt2.sResolutionInput.eFrameRate
         && sResolutionInput.eScanMode == sOpt2.sResolutionInput.eScanMode
         && sResolutionInput.size == sOpt2.sResolutionInput.size
         && sResolutionInput.ulComponentBitCount == sOpt2.sResolutionInput.ulComponentBitCount
         && sResolutionInput.ulHeight == sOpt2.sResolutionInput.ulHeight
         && sResolutionInput.ulWidth == sOpt2.sResolutionInput.ulWidth
         && sResolutionOutput.eAspectRatio == sOpt2.sResolutionOutput.eAspectRatio
         && sResolutionOutput.eFrameRate == sOpt2.sResolutionOutput.eFrameRate
         && sResolutionOutput.eScanMode == sOpt2.sResolutionOutput.eScanMode
         && sResolutionOutput.size == sOpt2.sResolutionOutput.size
         && sResolutionOutput.ulComponentBitCount == sOpt2.sResolutionOutput.ulComponentBitCount
         && sResolutionOutput.ulHeight == sOpt2.sResolutionOutput.ulHeight
         && sResolutionOutput.ulWidth == sOpt2.sResolutionOutput.ulWidth;
   }
};

//
// Summary:
//    Describes the H.264/AVC hardware codec compression GOP structure.
struct SMvAVCCompressionGOPStructureOption
{
   uint32_t             size;                          // Structure size in bytes.
   bool                 bIsStructured;                 // If true, indicates that the distance-related parameters in this structure are valid and that the GOP is structured.
   uint32_t             ui32DistanceBetweenIDRFrames;  // Indicates the distance between 2 IDR frames. This is also the GOP size.
   uint32_t             ui32DistanceBetweenIFrames;    // Indicates the distance between 2 I-frames (IDR frames are considered I-frames).
   uint32_t             ui32DistanceBetweenReferences; // Indicates the distance between 2 reference frames (P, I, or IDR). This value minus one indicates the number of B-frames.
};

//
// Summary:
//    Describes the H.264/AVC hardware codec decompression options.
struct SMvAVCDecompressionOptions
{
   uint32_t             size;                                              // Structure size in bytes.
   SMvResolutionInfo    sResolutionInput;                                  // Input resolution of the codec.
   SMvResolutionInfo    sResolutionOutput;                                 // Output resolution of the codec.
   EMvGOPStructureType  eGOPStructureType;                                 // Indicates the GOP structure type that was used to create the stream.
   uint32_t             ui32GOPSizeInFrames;                               // Indicates the GOP size of the given stream.
   uint32_t             ui32DistanceBetweenReferencesInFrames;             // Indicates the distance between references in the given stream.
   uint32_t             ui32AverageBitRateInBitsPerSec;                    // Indicates the average bit rate of the stream.
   float                fPlaySpeed;                                        // Indicates the original play speed of the stream.
   bool                 bForceSynchronousOpen;                             // If true, indicates that a synchronous open operation should be forced.
};

//
// Summary
//    Describes the H.264/AVC software decoder decompression options.
struct SMvH264SWDecompressionOptions 
{
   uint32_t                   size;                      //Structure size in bytes.   
   SMvResolutionInfo          sResolutionInput;          //Structure containing the input resolution.
   SMvResolutionInfo          sResolutionOutput;         //Structure containing the output resolution. 

   // Indicates the type of VANC data to decode (such as closed caption, AFD, bar data, or time code).
   EMvVANCInformationType     eVANCInformationType;      
                                                         
   bool                       bIgnorePutMediaPositions;  //If true, indicates that the put media positions are not valid and should be ignored.
   bool                       bForceSynchronousOpen;     //If true, indicates that a synchronous open operation should be forced.
   bool                       bUseVANCSurfaces;          //If true, indicates that VANC surfaces should be generated.
};

//
// Summary:
//    Describes the streams to be decoded by the H.264/AVC software decoder.
struct SMvH264SWCodecMaxPropagationDelayByFramesOption
{
   uint32_t             size;  // Structure size in bytes.

   //input params

   uint32_t             in_ui32MaxNumOfStreamsInParallel;   //Indicates the maximum number of streams to be decoded in parallel.
   SMvCodecResolutions  in_sMaxResolution;                  //Indicates the maximum resolution of the streams to be decoded.
   EMvFrameRate         in_eMaxFrameRate;                   //Indicates the maximum frame rate of the streams to be decoded.

   //output params

   uint32_t             out_ui32MaxPropagationDelayByFrames; //Indicates the maximum propagation delay, in terms of frames,
   //to be added to the playback time stamps.
   //The output buffer size should be greater than this value
   //in order to compensate for the delay.
};

struct SMvGetNearestSupportedShuttlingSpeed
{
   uint32_t    size;                           // Structure size in bytes.
   uint32_t    in_ui32GOPSizeInFrames;          // GOP size in frames of the data to decode.
   uint32_t    in_ui32DistanceBetweenReferencesInFrames; // Distance between references in frames.
   EMvGOPStructureType in_eGOPStructureType;   // GOP structure type of the stream.
   uint32_t    in_ui32AverageBitRateInBitsPerSec; // Averate bit rate in bits per seconds of the stream.
   double      in_dblAskedShuttlingSpeed;      // Asked shuttling speed.
   double      out_dblSupportedShuttlingSpeed; // Returned supported shuttling speed.
};

//
// Summary:
//    Describes muxer option settings that are required by the Flex Transport Stream Encoder.
struct SMvTSEncoderMuxerOptionSettings
{
   uint32_t                   size;                         // Structure size in bytes.
   uint16_t                   ui16ProgramPID;               // Specifies the packet ID of the program.
   uint16_t                   ui16VideoPID;                 // Specifies the packet ID of the video.
   uint16_t                   ui16AudioPID;                 // Specifies the packet ID of the audio.       
   uint16_t                   ui16PCRPID;                   // Specifies the packet ID of the Program Clock Reference (PCR).
   EMvMPEG2MuxerBitRateOption eMPEG2MuxerBitRateOption;     // Specifies the bit rate encoding option for the MPEG-2 transport stream. 
   bool                       bProcessSCTE35;               // If true, the muxer inserts SCTE 35 splice information.
   uint16_t                   ui16SpliceInfoSectionPID;     // Specifies the packet ID of the splice information section.
};

//
// Summary:
//    Describes the structure used to set the M264 decoder options.
struct SMvM264DecompressionOptions
{   
   uint32_t                    ui32size;                 // Structure size in bytes.   
   SMvResolutionInfo           sResolutionInput;         // Resolution of the input compressed stream.
   SMvResolutionInfo           sResolutionOutput;        // Desired resolution of the uncompressed frame.
   EMvHardwareProfile          eHardwareProfileType;     // Indicates which hardware profile to use.
   uint32_t                    ulHardwareProfileIndex;   // Specifies the index of the hardware profile to use.
};


///////////////////////////////////////////////////////////////////////////////
//
// END of Video Codec Definitions
//
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
// Matrox MPEG-2 Transport Stream Muxer Definitions
/////////////////////////////////////////////////////////

//
// Summary:
//    Describes the video codec types that are supported by the Matrox MPEG-2 Transport Stream Muxer.
//
enum EMvVideoCodecType
{
   keVideoCodecTypeInvalid           = 0,    // Invalid value.
   keVideoCodecTypeH264,                     // H.264/AVC.
   keVideoCodecTypeLast                      // End of list indicator.
};

//
// Summary:
//    Describes the audio codec types that are supported by the Matrox MPEG-2 Transport Stream Muxer.
//
enum EMvAudioCodecType
{
   keAudioCodecTypeInvalid = 0,  // Invalid value.
   keAudioCodecTypeAAC,          // AAC.   
   keAudioCodecTypeLast          // End of list indicator.
};


//
// Summary:
//    Describes the Matrox MPEG-2 Transport Stream Muxer settings.

struct SMvMPEG2TSMuxerSettings
{
   uint32_t                      size;                      //Structure size in bytes.
   SMvResolutionInfo             sVideoResolution;          //Video resolution.
   EMvChannelType                eAudioChannelType;         //Audio channel type (mono, stero, etc.).
   EMvVideoCodecType             eVideoCodecType;           //Video codec type (H.264/AVC).
   EMvAudioCodecType             eAudioCodecType;           //Audio codec type (AAC).
   uint32_t                      ui32VideoBitRate;          //Average video bit rate.          
   uint32_t                      ui32VideoMaxBitRate;       //Maximum video bit rate.
   uint32_t                      ui32AudioBitRate;          //Audio bit rate.         
   uint32_t                      ui32AudioMaxBitRate;       //Audio maximum bit rate.
   uint16_t                      ui16ProgramPID;            //Program PID (13-bit).
   uint16_t                      ui16VideoPID;              //Video packet ID (13-bit).
   uint16_t                      ui16AudioPID;              //Audio packet ID (13-bit).
   uint16_t                      ui16PCRPID;                //Program Clock Reference (PCR) packet ID (13-bit).
   EMvMPEG2MuxerBitRateOption    eMPEG2MuxerBitRateOption;  //Encoding option for the MPEG-2 transport stream.
   bool                          bProcessSCTE35;            //If true, the muxer inserts SCTE 35 splice information.
   EMvH264Profile                eH264Profile;              //Profile of the H.264 encoding video.
   uint16_t                      ui16SpliceInfoSectionPID;  //Packet ID (13-bit) of the splice.
};


///////////////////////////////////////////////////////////////////////////////
//
// IP Definitions
//
///////////////////////////////////////////////////////////////////////////////
#ifndef LINUX_PLATFORM
#ifndef s_addr
#pragma once

//
// IPv4 Internet address
// This is an 'on-wire' format structure.
//
typedef struct in_addr {
   union {
      struct { UCHAR s_b1,s_b2,s_b3,s_b4; } S_un_b;
      struct { USHORT s_w1,s_w2; } S_un_w;
      ULONG S_addr;
   } S_un;
#define s_addr  S_un.S_addr /* can be used for most tcp & ip code */
#define s_host  S_un.S_un_b.s_b2    // host on imp
#define s_net   S_un.S_un_b.s_b1    // network
#define s_imp   S_un.S_un_w.s_w2    // imp
#define s_impno S_un.S_un_b.s_b4    // imp #
#define s_lh    S_un.S_un_b.s_b3    // logical host
} IN_ADDR, *PIN_ADDR, FAR *LPIN_ADDR;

#endif // #ifndef s_addr
#else //LINUX_PLATFORM
#include <netinet/in.h> 
#endif 

struct SMvIPOutputSession
{
   uint32_t          size;                               // Structure size in bytes.
   struct in_addr    sDestinationAddress;                // Destination address, use our_inet_addr(MULTICAST_ADDR_SOCKET) for instance.
   bool              bMulticast;                         // A boolean value to indicate if the session is unicast (false) or multicast (true).
   wchar_t           wszSessionName[256];                // The name of the session. This is required for the client to connect to the server.
   unsigned short    usRTSPPort;                         // The port number used by the RTSP server. If the value is 0, the default value used will be 554. 
   // The reason why we let the application specify the port number is because a user may want to choose a different port for a specific reason.
   unsigned short    usRTPVideoPort;                     // The port number of the video RTP stream.
   unsigned short    usRTPAudioPort;                     // The port number of the audio RTP stream. The audio port number should be >= usRTPVideoPort + 2.
   uint32_t          ui32EstimatedVideoBitRatePerSecond; // Estimation in bits/sec of the video stream bit rate. A value of 1000 indicates 1 Kb/second.
   uint32_t          ui32EstimatedAudioBitRatePerSecond; // Estimation in bits/sec of the audio stream bit rate. A value of 1000 indicates 1 Kb/second.
   uint64_t          ui64Reserved[9];                    // Ignored.
};

//Structure to use when opening an IP streaming server session for H.264 video.
struct SMvIPOutputSessionH264Information
{
   uint32_t          size;                               // Structure size in bytes.
   BYTE *            pSPS;                               // Pointer to the SPS NAL Unit. May or may not contain the 00 00 00 01 marker.
   unsigned long     ulSPSSizeInBytes;                   // SPS size.
   BYTE *            pPPS;                               // Pointer to the SPS NAL Unit. May or may not contain the 00 00 00 01 marker.
   unsigned long     ulPPSSizeInBytes;                   // PPS size.
};


struct SMvIPInputSession
{
   uint32_t          size;                               // Structure size in bytes.
   wchar_t           wszComputerName[256];               // The name of the computer. This is required for the client to connect to the server.
   bool              bMulticast;                         // A boolean value to indicate if the session is unicast (false) or multicast (true).
   wchar_t           wszSessionName[256];                // The name of the session. This is required for the client to connect to the server.
   unsigned short    usRTSPPort;                         // The port number used by the RTSP server. If the value is 0, the default value used will be 554. 
   uint64_t          ui64Reserved[8];                    // Ignored.
};

//
// Summary:
//    Describes the read ahead status of the Flex File Reader.
struct SMvFlexReaderStatus
{
   uint32_t          size;                               // Structure size in bytes.
   uint64_t          ui64NumberOfPreparedPositions;      // Current number of prepared positions.
   uint64_t          ui64NextPosition;                   // Position returned next time GetBuffer is called.
   uint64_t          ui64LastPositionCued;               // Last position scheduled to be read from disk.
   uint64_t          ui64LastPositionReceived;           // Last position already read from disk.
   uint64_t          ui64PlaylistDuration;               // Duration of the playlist. <p> 0 if there is no playlist, or if the playlist is empty.
   uint64_t          ui64Mode;                           // Mode of the Flex File Reader. <p> 0:Invalid; 1:Seek; 2:Play; 3:Step; 4:Shuttling
   uint64_t          ui64Reserved[6];                    // Ignored.
};

//Specifies the type of aspect ratio conversion to perform when downscaling from HD to SD (16:9 to 4:3).
enum EMvAspectRatioConversionForHDToSD 
{
   keMvAspectRatioConversionForHDToSDInvalid,      // Invalid value.
   keMvAspectRatioConversionForHDToSD_LetterBox,   // Letterbox.
   keMvAspectRatioConversionForHDToSD_Anamorphic,  // Anamorphic.
   keMvAspectRatioConversionForHDToSD_CenterCut,   // Center cut.
   keMvAspectRatioConversionForHDToSDLast          // End of list indicator.
};


// This macro is used to get the string corresponding to the eMvAspectRatioHDToSD enum value.
#define MV_MXO_ASPECT_RATIO_HD_TO_SD_ENUM_TO_STRING(eMvAspectRatioHDToSD) \
   ((eMvAspectRatioHDToSD == keMvAspectRatioConversionForHDToSDInvalid) ? _T("Invalid") : \
   (eMvAspectRatioHDToSD == keMvAspectRatioConversionForHDToSD_LetterBox) ? _T("Letter box") : \
   (eMvAspectRatioHDToSD == keMvAspectRatioConversionForHDToSD_Anamorphic) ? _T("Anamorphic") : \
   (eMvAspectRatioHDToSD == keMvAspectRatioConversionForHDToSD_CenterCut) ? _T("Center cut") : \
   (eMvAspectRatioHDToSD == keMvAspectRatioConversionForHDToSDLast) ? _T("Last") : \
   _T("???"))

enum EMvConvertDVIScalingMethod
{
   keMvConvertDVIScalingMethod_Invalid,            // Invalid value.
   keMvConvertDVIScalingMethod__1_1_Pixel_Mapping, // 1:1 pixel mapping (no scaling).
   keMvConvertDVIScalingMethod_STF_Horizontal,     // Scale to fit horizontally (letterbox).
   keMvConvertDVIScalingMethod_STF_Vertical,       // Scale to fit vertically (pillarbox).
   keMvConvertDVIScalingMethod__Anamorphic,        // Anamorphic (don't preserve aspect ratio).
   keMvConvertDVIScalingMethod__Custom,            // Custom scaling.
   keMvConvertDVIScalingMethod_Last                // End of list indicator.
};

// Specifies the type of aspect ratio conversion to perform when outputting a non-standard aspect ratio.
enum EMvAspectRatioConversionCustomScaling
{
   keMvAspectRatioConversionCustomScalingInvalid,        // Invalid value.
   keMvAspectRatioConversionCustomScaling_ResizeToFit,   // Resize to fit.
   keMvAspectRatioConversionCustomScaling_MaintainRatio, // Maintain aspect ratio.
   keMvAspectRatioConversionCustomScalingLast            // End of list indicator.
};


// This macro is used to get the string corresponding to the eMvAspectRatioCustomScaling enum value.
#define MV_MXO_ASPECT_RATIO_CUSTOM_SCALING_ENUM_TO_STRING(eMvAspectRatioCustomScaling) \
   ((eMvAspectRatioCustomScaling == keMvAspectRatioConversionCustomScalingInvalid) ? _T("Invalid") : \
   (eMvAspectRatioCustomScaling == keMvAspectRatioConversionCustomScaling_ResizeToFit) ? _T("Resize to fit") : \
   (eMvAspectRatioCustomScaling == keMvAspectRatioConversionCustomScaling_MaintainRatio) ? _T("Maintain ratio") : \
   (eMvAspectRatioCustomScaling == keMvAspectRatioConversionCustomScalingLast) ? _T("Last") : \
   _T("???"))

// Summary:
//    Specifies the AES/EBU audio pair connector group.
enum EMvAesEbuGroup
{
   keMvAesEbuGroupInvalid, // Invalid value.
   keMvAesEbuGroupA,       // The AES/EBU audio pair connector is part of group A.
   keMvAesEbuGroupB,       // The AES/EBU audio pair connector is part of group B.
   keMvAesEbuGroupLast     // End of list indicator.
};

#define MV_AES_EBU_GROUP_ENUM_TO_STRING(eGroup) \
   ((eGroup == keMvAesEbuGroupInvalid) ? "Invalid" : \
   (eGroup == keMvAesEbuGroupA) ? "Group A" : \
   (eGroup == keMvAesEbuGroupB) ? "Group B" : \
   (eGroup == keMvAesEbuGroupLast) ? "Last" : \
   "???")


//
// Summary:
//    Describes the type of audio.
//
enum EMvAudioType
{
   keMvAudioTypeInvalid,         // Invalid value.
   keMvAudioTypeAesEbu,          // The audio is AES/EBU.
   keMvAudioTypeEmbedded,        // The audio is SDI embedded
   keMvAudioTypeSdiEmbedded = keMvAudioTypeEmbedded,
   keMvAudioTypeSdiIpEmbedded,   // The audio is SDIIP 
   keMvAudioTypeLast             // End of list indicator.
};

//
// Summary:
//    Describes the type of node content.
//
// Remarks:
//    The values can be used with a logical AND/OR operator.
//
enum EMvNodeContent
{
   keMvNodeContentInvalid = 0,         // Invalid value.
   keMvNodeContentVideo = 1,           // The node contains video data only.
   keMvNodeContentAudio = 2,           // Binary value used to test if the node contains audio data.
   keMvNodeContentVideoAudio = 3,      // The node contains audio and video data.
   keMvNodeContentVanc = 4,            // Binary value used to test if the node contains VANC data.
   keMvNodeContentVideoVanc = 5,       // Binary value used to test if the node contains video and VANC data.
   keMvNodeContentAudioVanc = 6,       // Binary value used to test if the node contains audio and VANC data.
   keMvNodeContentVideoAudioVanc = 7,  // The node contains audio, video, and VANC data.
   keMvNodeContentMPEG2_TS = 8,        // Binary value used to test if the node contains MPEG2 transport stream data.
   keMvNodeContentLast                 // End of list indicator.
};

#define MV_NODE_CONTENT_ENUM_TO_STRING(eNodeContent) \
   ((eNodeContent == keMvNodeContentInvalid)       ? _T("Invalid") : \
   (eNodeContent == keMvNodeContentVideo)          ? _T("Video") : \
   (eNodeContent == keMvNodeContentAudio)          ? _T("Audio") : \
   (eNodeContent == keMvNodeContentVideoAudio)     ? _T("Video and Audio") : \
   (eNodeContent == keMvNodeContentVanc)           ? _T("Vanc") : \
   (eNodeContent == keMvNodeContentVideoVanc)      ? _T("Video and Vanc") : \
   (eNodeContent == keMvNodeContentAudioVanc)      ? _T("Audio and Vanc") : \
   (eNodeContent == keMvNodeContentVideoAudioVanc) ? _T("Video, Audio and Vanc") : \
   (eNodeContent == keMvNodeContentMPEG2_TS)       ? _T("MPEG2 TS") : \
   (eNodeContent == keMvNodeContentVideoAudio)     ? _T("Last") : \
   _T("???"))

//
// Summary:
//    Specifies the type of stream that an interface represents.
//
enum EMvStreamType
{
   keMvStreamTypeInvalid,           // Invalid value.
   keMvStreamTypeInputStream,       // Indicates that the interface represents an input stream. The IMvInputStream interface is used to interact with this type of stream.
   keMvStreamTypeOutputStream,      // Indicates that the interface represents an output stream. The IMvOutputStream interface is used to interact with this type of stream.
   keMvStreamTypeTransformStream,   // Indicates that the interface represents a transform stream. The IMvTransformStream interface is used to interact with this type of stream.
   keMvStreamTypeMixerStream,       // Indicates that the interface represents a mixer stream. The IMvMixerStream interface is used to interact with this type of stream.
   keMvStreamTypeDeInterlacerStream,// Indicates that the interface represents a de-interlacer stream. The IMvDeInterlacerStream interface is used to interact with this type of stream.
   keMvStreamTypeTransferStream,    // Indicates that the interface represents a transfer stream. The IMvTransferStream interface is used to interact with this type of stream.
   keMvStreamTypeWriterStream,      // Indicates that the interface represents a writer stream. The IMvWriterStream interface is used to interact with this type of stream.
   keMvStreamTypeReaderStream,      // Indicates that the interface represents a reader stream. The IMvReaderStream interface is used to interact with this type of stream.
   keMvStreamTypeEncoderStream,     // Indicates that the interface represents an encoder stream. The IMvEncoderStream interface is used to interact with this type of stream.
   keMvStreamTypeMuxerStream,       // Indicates that the interface represents an muxer stream. The IMvMuxerStream interface is used to interact with this type of stream.
   keMvStreamTypeRTPSenderStream,   // Indicates that the interface represents an RTP sender stream. The IMvRTPSenderStream interface is used to interact with this type of stream.
   keMvStreamTypeCompressedWriterStream,  // Indicates that the interface represents a compressed writer stream. The IMvCompressedWriterStream interface is used to interact with this type of stream.
   keMvStreamTypeEchoStream,        // Indicates that the interface represents an echo sender stream. The IMvEchoStream interface is used to interact with this type of stream.
   keMvStreamTypeDecoderStream,     // Indicates that the interface represents a decoder stream. The IMvDecoderStream interface is used to interact with this type of stream.
   keMvStreamTypeRTPReceiverStream, // Indicates that the interface represents an RTP receiver stream. The IMvRTPReceiverStream interface is used to interact with this type of stream.
   keMvStreamTypeDemuxerStream,     // Indicates that the interface represents a demuxer stream. The IMvDemuxerStream interface is used to interact with this type of stream.
   keMvStreamTypeLast               // End of list indicator.
};


//
// Summary:
//    Describes the AES/EBU audio output pair connector settings.
//
struct SMvAesEbuAudioOutputPairConnectorSettings
{
   uint32_t ui32Size;               // Structure size in bytes.
   bool bMuteOutputAesEbuPair;      // If true, the AES/EBU audio output pair is muted. 
   IMvOutputStream *pOutputStream;  // Pointer to the output stream that provides the audio data to output.
   EMvAudioPair eSourceAudioPair;   // Indicates an audio pair selected from the output stream.
};

//
// Summary:
//    Describes the audio output stream settings.
// Remarks:
// - This structure is part of the SMvOutputStreamSettings structure.
//
struct SMvAudioOutputStreamSettings
{
   bool bEnableAudioMixer;                   // If true, the in-line audio mixer is enabled.
   bool bAuxPhaseInvert;                     // If true, the in-line audio mixer's auxiliary input phase is inverted before being mixed.
   double adAuxVolume[16];                   // Indicates the volume that the in-line audio mixer applies to specific auxiliary audio input channels.  
                                             // The volume is changed using a multiplication factor that ranges from 0 to 2 and is applied at the next zero-crossing.
   double adLineVolume[16];                  // Indicates the volume that the in-line audio mixer applies to specific line audio input channels.  
                                             // The volume is changed using a multiplication factor that ranges from 0 to 2 and is applied at the next zero-crossing.
   double dAuxMasterVolume;                  // Indicates the volume that the in-line audio mixer applies to all the auxiliary audio input channels.
                                             // The master volume is changed gradually on all the audio channels at the same time. 
                                             // The volume is changed using a multiplication factor that ranges from 0 to 2.
   double dLineMasterVolume;                 // Indicates the volume that the in-line audio mixer applies to all the line audio input channels.  
                                             // The master volume is changed gradually on all the audio channels at the same time.  
                                             // The volume is changed using a multiplication factor that ranges from 0 to 2.
   EMvAudioMixerSourceSelection eAuxSourceSelection; // Indicates the audio to use for the auxiliary input of the in-line audio mixer.
                                             // The audio selected for the auxiliary input is mixed with the audio line input of the in-line audio mixer.  For X.mio2 Plus only.
};

//
// Summary:
//    Describes the input stream's audio settings.
// Remarks:
// - This structure is part of the SMvInputStreamSettings structure.
// - The audio pair is not muted on the mechanical bypass mode on topology-based hardware.
//
struct SMvAudioInputStreamSettings
{
   bool abCapturePairMute[8]; // If true, the selected audio pair is muted in the node connected to the input stream.
                              // This means that the selected audio pair will be muted in a capture or passthrough topology.<p>
                              // Refer to the <i>Matrox DSX Topology API User Guide</i> to verify if your DSX hardware supports this parameter.
                              // <b>Note:</b> Can only mute the audio from SDI and AES/EBU input connectors.
};

//
// Summary:
//    Describes the video input stream settings.
// Remarks:
// - This structure is part of the SMvInputStreamSettings structure.
//
struct SMvVideoInputStreamSettings
{
   double dBrightness;           // Indicates the brightness value.  The range is from -92.5 to 92.5.
   double dLumaGain;             // Indicates the luma gain value.  The range is from 0 to 2.
   double dHue;                  // Indicates the hue value.  The range is from 0 to 360.
   double dSaturation;           // Indicates the saturation value.  The range is from 0 to 2.
   bool bAllowSuperBlack;        // If true, allows an input video signal that is below 7.5 IRE.
   bool bAllowSuperWhite;        // If true, allows an input video signal that is above 100 IRE.
   bool bEnableChromaClipping;   // If true, clips over-saturated chroma levels in the active portion of the input video signal.
   bool bUpscaleKeyLuma;         // If true, upscales the luminance range of the input key signal from 16-235 to 0-255.
                                    // If the video's input stream is connected to a node containing YUV 4:2:2, bUpscaleKeyLuma is ignored.
   bool bInvertKeyLuma;          // If true, inverts the luminance part of the key signal and inverts the key value.
                                    // If the video's input stream is connected to a node containing YUV 4:2:2, bInvertKeyLuma is ignored.
   bool bApplyKeyLumaOffset;     // If true, applies an offset to the luminance values so that the inverted 
                                    // result falls within the 0-255 range. The offset can only be applied if 
                                    // the luminance part of the key signal is inverted (bInvertKeyLuma = true), and the luminance range of the 
                                    // key signal is upscaled (bUpscaleKeyLuma = true).
                                    // If the video's input stream is connected to a node containing YUV 4:2:2, bApplyKeyLumaOffset is ignored.
};

//
// Summary:
//    Describes the video's output stream settings.
// Remarks:
// - This structure is part of the SMvOutputStreamSettings structure.
//
struct SMvVideoOutputStreamSettings
{
   bool bAllowSuperBlack;              // If true, allows an output video signal that is below 7.5 IRE.
   bool bAllowSuperWhite;              // If true, allows an output video signal that is above 100 IRE.
   bool bEnableChromaClipping;         // If true, clips over-saturated chroma levels in the active portion of the output video signal.
   bool bDownscaleKeyLuma;             // If true, downscales the luminance range of the output key signal from 0-255 to 16-235.
                                          // If the video's output stream is connected to a node containing YUV 4:2:2, bDownscaleKeyLuma is ignored.
   bool bInvertKeyLuma;                // If true, inverts the luminance part of the output key signal and inverts the key value.
                                          // If the video's output stream is connected to a node containing YUV 4:2:2, bInvertKeyLuma is ignored.
   bool bApplyKeyLumaOffset;           // If true, applies an offset to the luminance values so that the inverted result 
                                          // falls within the 16-235 range. The offset can only be applied if the
                                          // luminance part of the key signal is inverted (bInvertKeyLuma = true), and the luminance range of the 
                                          // key signal is downscaled (bDownscaleKeyLuma = true).
                                          // If the video's output stream is connected to a node containing YUV 4:2:2, bApplyKeyLumaOffset is ignored.
   bool bEnableEdgeSharpeningFilter;   // If true, enables an edge sharpening filter to the digital output video. The filter reduces
                                       // ringing artifacts that appear as a result of high amplitude transitions in the digital signal.
   bool bEnableVideoMixer;             // If true, enables the in-line video mixer.
   bool bIsVideoShaped;                // If true and the video mixer is enabled, the video signal to the in-line video mixer from the auxiliary input (video from the output stream's node) 
                                          // is already multiplied by its alpha plane.
   uint64_t ui64AdvancedDelayInNanoTime; // Indicates the delay (in nanotime) that will be applied to an output stream's input. The value must be frame aligned.
                                         // The advanced delay must be less than the node depth minus the node's write-to-read delay minus three frames. That is, <p>
                                         // <i> Advance delay < node depth - node's write-to-read delay - 3 frames </i>
   EMvVideoMixerVancSource           eVideoMixerVancSource;          // Indicates the source for the vertical ancillary data. Only valid if the video mixer is enabled (bEnableVideoMixer = true)
   EMvVideoMixerAudioAndHancSource   eVideoMixerAudioAndHancSource;  // Indicates the source for the audio and horizontal ancillary data. Only valid if the video mixer is enabled (bEnableVideoMixer = true)
   bool bEnableMechanicalBypass;       //If true, the mechanical bypass is activated. For more information on the mechanical bypass input to output connections depending on the card, see the <i>Matrox DSX Topology API User Guide</i>.
};

//
// Summary:
//    Indicates the status of an input audio pair connector.
//
struct SMvAudioPairStatus
{
   uint32_t               ui32Size;       // Structure size in bytes.
   bool                   bIsPairPresent; // If true, audio data is present in the input signal.
   EMvAudioBitsPerSample  eBitsPerSample; // Indicates the number of bits per audio sample.
   EMvEAChannelStatusInfo eStatusInfo;    // Indicates the audio data format present in the input signal.
};

//
// Summary:
//    Enumerates each Sfp on the card.
//
enum EMvSfpLabel
{
   keMvSfpLabelInvalid = 0,
   keMvSfpLabelA,
   keMvSfpLabelB,
   keMvSfpLabelC,
   keMvSfpLabelD,
   keMvSfpLabelE,
   keMvSfpLabelF,
   keMvSfpLabelG,
   keMvSfpLabelH,
   keMvSfpLabelI,
   keMvSfpLabelJ,
   keMvSfpLabelK,
   keMvSfpLabelL,
   keMvSfpLabelM,
   keMvSfpLabelN,
   keMvSfpLabelO,
   keMvSfpLabelP,
   keMvSfpLabelLast
};

#define MV_SFP_LABEL_ENUM_TO_STRING(eLabel) \
   ((eLabel == keMvSfpLabelInvalid) ? ("Invalid") : \
   (eLabel == keMvSfpLabelLast)    ? ("Last") : \
   (eLabel == keMvSfpLabelA)       ? ("SFP A") : \
   (eLabel == keMvSfpLabelB)       ? ("SFP B") : \
   (eLabel == keMvSfpLabelC)       ? ("SFP C") : \
   (eLabel == keMvSfpLabelD)       ? ("SFP D") : \
   (eLabel == keMvSfpLabelE)       ? ("SFP E") : \
   (eLabel == keMvSfpLabelF)       ? ("SFP F") : \
   (eLabel == keMvSfpLabelG)       ? ("SFP G") : \
   (eLabel == keMvSfpLabelH)       ? ("SFP H") : \
   (eLabel == keMvSfpLabelI)       ? ("SFP I") : \
   (eLabel == keMvSfpLabelJ)       ? ("SFP J") : \
   (eLabel == keMvSfpLabelK)       ? ("SFP K") : \
   (eLabel == keMvSfpLabelL)       ? ("SFP L") : \
   (eLabel == keMvSfpLabelM)       ? ("SFP M") : \
   (eLabel == keMvSfpLabelN)       ? ("SFP N") : \
   (eLabel == keMvSfpLabelO)       ? ("SFP O") : \
   (eLabel == keMvSfpLabelP)       ? ("SFP P") : \
   ("???"))

//
// Summary:
//    Describes the SdiIp input connector settings.
//
struct SMvSdiIpInputConnectorSettings
{
   uint32_t ui32Size;                           // Structure size in bytes.
   uint32_t ui32MulticastFilterIPv4Address;     // Multicast IPv4 address (Dst IPv4 in an IP Reception).
   uint16_t ui16LocalUDPPort;                   // Local UDP port (Dst UDP port in an IP Reception).
   uint32_t ui32DistantIPv4Address;             // Distant IPv4 address (Src IPv4 in an IP Reception). Not used in Multicast.
   uint16_t ui16DistantUDPport;                 // Distant UDP port (Src UDP port in an IP Reception). Not used in Multicast.
};

//
// Summary:
//    Describes the SdiIp output connector settings.
//
struct SMvSdiIpOutputConnectorSettings
{
   uint32_t ui32Size;                  // Structure size in bytes.
   double dLineBufferHorizonalDelay;   // Sets the SDI line buffer delay in pixels. For digital video only. The range is -256 to 256.
   double dHorizontalFrameDelay;       // Controls the horizontal frame delay on the SDI output circuit in seconds. 
                                       // The output delay is a combination of dHorizontalFrameDelay, ui32VerticalFrameDelay, 
                                       // and dLineBufferHorizonalDelay, if dLineBufferHorizonalDelay is supported on your hardware.<p>
                                       // For SD, the granularity is 0.5 pixel (approximately 37.037 nanoseconds), and the range is from zero to (Htotal - 0.5) * 74.074 x 10<sup>-9</sup>. Where Htotal is the total horizontal width in pixels. <p>
                                       // For 720p at 24, 25, 30, 50, or 60 fps and 1080p at 24, 25, or 30 fps, the granularity is 1 pixel (approximately 13.468 nanoseconds), and the range is from zero to (Htotal - 1) * 13.468 x 10<sup>-9</sup>.<p> 
                                       // For 720p at 23.98, 29.97, or 59.94 fps and 1080p at 23.98 or 29.97 fps, the granularity is 1 pixel (approximately 13.481 nanoseconds), and the range is from zero to (Htotal - 1) * 13.481 x 10<sup>-9</sup>.<p> 
                                       // For 1080p at 50 or 60 fps, the granularity is 1 pixel (approximately 6.734 nanoseconds), and the range is from zero to (Htotal - 1) * 6.734 x 10<sup>-9</sup>.<p> 
                                       // For 1080p at 59.94 fps, the granularity is 1 pixel (approximately 6.740 nanoseconds), and the range is from zero to (Htotal - 1) * 6.740 x 10<sup>-9</sup>.<p> 
                                       // Refer to the following table for Htotal values and approximate duration of a pixel at different resolutions.<p> 
                                       // <b>Note:</b> The exact duration of a pixel (in seconds) can be calculated as follows: 1 / (frame rate * Htotal * Vtotal), where Vtotal is the total vertical height in pixels.
   uint32_t ui32VerticalFrameDelay;    // Controls the vertical delay on the SDI output circuit in lines.
                                       // The output delay is a combination of dHorizontalFrameDelay, ui32VerticalFrameDelay,
                                       // and dLineBufferHorizonalDelay, if dLineBufferHorizonalDelay is supported on your hardware.
                                       // The range is from zero to Vtotal minus 1. Refer to the following table for Vtotal values at different resolutions.<p>
                                       // <b>Note:</b> The exact duration of a line (in seconds) can be calculated as follows: 1 / (frame rate * Vtotal)
   bool bEnableSMPTE352;               // If true, enables SMPTE 352 packets.
   bool bEnableEmbeddedAudio;                      // If true, enables the embedded audio.
   EMvAudioBitsPerSample aePairBitsPerSample[8];   // Number of bits per audio sample, one value per audio pair.
   bool abPairIsPCMAudio[8];                       // If true, the pair is marked as Pulse-code modulation (PCM) audio in the channel status. One per audio pair.
   bool bActivateDBN;                              // If true, generates the embedded audio Data Block Number (DBN) in Standard 
                                                   // Definition (SD). This control has no effect in 
                                                   // High Definition (HD) because HD always contains embedded audio DBN.
                                                   // Equipment with HD/SD support will not decode audio properly unless DBN in audio packets is activated.
                                                   // Older equipment will not work properly if DBN in audio data packets is activated
                                                   // to the extent that the video may be corrupted.  
                                                   // If the video is corrupted, do not use embedded audio DBN. 
   uint32_t ui32RTPSyncSourceIdentifier;  // RTP Synchronization Source Identifier
   uint32_t ui32TypeOfServiceDSCP;        // Type of Service (ToS): Differentiated Service Code Point (DSCP). Range is [0..63] (6 bits)
   uint32_t ui32TypeOfServiceECN;         // Type of Service (ToS): Explicit Congestion Notification (ECN) [0..3] (2 bits)
   uint32_t ui32TimeToLiveInSeconds;      // Time to live (TTL) of the packets.
   uint16_t ui16LocalUDPPort;             // Local UDP port (Src UDP port in an IP Transmission).
   uint32_t ui32DistantIPv4Address;       // Distant IPv4 address (Dst IPv4 in an IP Transmission).
   uint16_t ui16DistantUDPport;           // Distant UDP port (Dst UDP port in an IP Transmission).
};

//
// Summary:
//    Describes the SfpIp settings.
//
struct SMvSfpIpSettings
{
   uint32_t ui32Size;                     // Structure size in bytes.
   uint32_t ui32IPv4Address;              // Static IPv4 address.
   bool     bEnableVirtualLAN;            // If true, enables the Virtual LAN.
   uint32_t ui32VirtualLANTagPCP;         // Virtual LAN tag: Priority Code Point (PCP). Range is [0..7] (3 bits)
   bool     bEnableVirtualLANTagDEI;      // Virtual LAN tag: Drop Eligible Indicator (DEI)
   uint32_t ui32VirtualLANTagVID;         // Virtual LAN tag: Identifier (VID). Range is [0..4095] (12 bits)
};

//
// Summary:
//    Describes the SfpIp input status.
//
struct SMvSfpIpStatus
{
   uint32_t ui32Size;                     // Structure size in bytes.
   bool     bModulePresent;               // Indicates if a Sfp module is present on Sfp cage.
   bool     bSignalPresent;               // Indicates if a IP signal is present on the Sfp module.
   bool     bTransmitError;               // Indicates a Transmission error on the IP.
};

//
// Summary:
//    Describes the SfpIp capabilities.
//
struct SMvSfpIpCapabilities
{
   uint32_t ui32Size;                        // Structure size in bytes.
   uint32_t ui32OutputStreamSdiIPmaxCount;   // Indicates the amount of SdiIp Outputs available on the Sfp.
   uint32_t ui32InputStreamSdiIPmaxCount;    // Indicates the amount of SdiIp Inputs available on the Sfp.
};

//
// Summary:
//    Describes the SdiIp input status.
//
struct SMvSdiIpConnectorStatus
{
   uint32_t          ui32Size;                     // Structure size in bytes.
   SMvResolutionInfo sDetectedResolution;          // Describes the resolution detected in the input signal.
   bool              bIsSdiSignalPresent;          // If true, video data is present in the input signal.
   bool              bIsInputFlyWheelLocked;       // If true, the input flywheel is locked.
   bool              bIsSMPTE352PayloadIdValid;    // If true, the SMPTE 352 payload ID is valid.
   USMPTE352Id       uSMPTE352PayloadId;           // Returns the SMPTE 352 payload ID.
   bool              bIsIPPacketPresent;           // If true, IP packets are present in the signal.
   bool              bIsMacAddressMatch;           // If true, Mac addresses on IP packets match Mac addresses on SdiIp input connector.
   bool              bIsIPv4AddressMatch;          // If true, IPv4 addresses on IP packets match IPv4 addresses on SdiIp input connector settings.
   bool              bIsUDPPortMatch;              // If true, UDP ports on IP packets match UDP ports on SdiIp input connector settings.
   uint32_t          ui32RTPSyncSourceIdentifier;  // Indicates the RTP Synchronization Source Identifier.
   bool              bIsHwInputOverflow;           // Indicates an overflow error on the hardware IP packets processing module.
};

//
// Summary:
//    Describes the genlock settings.
// Description:
//<table>
// Resolution              Vtotal (in pixels)    Htotal (in pixels)    Approximate duration of a pixel (in seconds)
// -------------------     -------------------   ------------------    ---------------------------------------------
// NTSC                    525                   858                   74.074 x 10<sup>-9</sup>
// PAL                     625                   864                   74.074 x 10<sup>-9</sup>
// 720p at 23.98 fps       750                   4125                  13.481 x 10<sup>-9</sup>
// 720p at 24 fps          750                   4125                  13.468 x 10<sup>-9</sup>
// 720p at 25 fps          750                   3960                  13.468 x 10<sup>-9</sup>
// 720p at 29.97 fps       750                   3300                  13.481 x 10<sup>-9</sup>
// 720p at 30 fps          750                   3300                  13.468 x 10<sup>-9</sup>
// 720p at 50 fps          750                   1980                  13.468 x 10<sup>-9</sup>
// 720p at 59.94 fps       750                   1650                  13.481 x 10<sup>-9</sup>
// 720p at 60 fps          750                   1650                  13.468 x 10<sup>-9</sup>
// 1080i at 25 fps         1125                  2640                  13.468 x 10<sup>-9</sup>
// 1080i at 29.97 fps      1125                  2200                  13.481 x 10<sup>-9</sup>
// 1080i at 30 fps         1125                  2200                  13.468 x 10<sup>-9</sup>
// 1080PsF at 23.98 fps    1125                  2750                  13.481 x 10<sup>-9</sup>
// 1080PsF at 24 fps       1125                  2750                  13.468 x 10<sup>-9</sup>
// 1080PsF at 25 fps       1125                  2640                  13.468 x 10<sup>-9</sup>
// 1080PsF at 29.97 fps    1125                  2200                  13.481 x 10<sup>-9</sup>
// 1080PsF at 30 fps       1125                  2200                  13.468 x 10<sup>-9</sup>
// 1080p at 23.98 fps      1125                  2750                  13.481 x 10<sup>-9</sup>
// 1080p at 24 fps         1125                  2750                  13.468 x 10<sup>-9</sup>
// 1080p at 25 fps         1125                  2640                  13.468 x 10<sup>-9</sup>
// 1080p at 29.97 fps      1125                  2200                  13.481 x 10<sup>-9</sup>
// 1080p at 30 fps         1125                  2200                  13.468 x 10<sup>-9</sup>
// 1080p at 50 fps         1125                  2640                  6.734 x 10<sup>-9</sup>
// 1080p at 59.94 fps      1125                  2200                  6.740 x 10<sup>-9</sup>
// 1080p at 60 fps         1125                  2200                  6.734 x 10<sup>-9</sup>
// </table>
//
struct SMvGenlockSettings
{
   uint32_t ui32Size;                  // Structure size in bytes.
   double dHorizontalDelay;            // Controls the horizontal delay on the genlock circuit in seconds. The genlock delay is a combination of dHorizontalDelay and ui32VerticalDelayInLines. <p>
                                       // For SD, the granularity is 0.5 pixel (approximately 37.037 nanoseconds), and the range is from zero to (Htotal - 0.5) * 74.074 x 10<sup>-9</sup>. Where Htotal is the total horizontal width in pixels. <p>
                                       // For 720p at 24, 25, 30, 50, or 60 fps and 1080p at 24, 25, or 30 fps, the granularity is 1 pixel (approximately 13.468 nanoseconds), and the range is from zero to (Htotal - 1) * 13.468 x 10<sup>-9</sup>.<p> 
                                       // For 720p at 23.98, 29.97, or 59.94 fps and 1080p at 23.98 or 29.97 fps, the granularity is 1 pixel (approximately 13.481 nanoseconds), and the range is from zero to (Htotal - 1) * 13.481 x 10<sup>-9</sup>.<p> 
                                       // For 1080p at 50 or 60 fps, the granularity is 1 pixel (approximately 6.734 nanoseconds), and the range is from zero to (Htotal - 1) * 6.734 x 10<sup>-9</sup>.<p> 
                                       // For 1080p at 59.94 fps, the granularity is 1 pixel (approximately 6.740 nanoseconds), and the range is from zero to (Htotal - 1) * 6.740 x 10<sup>-9</sup>.<p> 
                                       // Refer to the following table for Htotal values and approximate duration of a pixel at different resolutions.<p> 
                                       // <b>Note:</b> The exact duration of a pixel (in seconds) can be calculated as follows: 1 / (frame rate * Htotal * Vtotal), where Vtotal is the total vertical height in pixels.
   uint32_t ui32VerticalDelayInLines;  // Controls the vertical delay on the genlock circuit in lines.
                                       // The output delay is a combination of dHorizontalDelay and ui32VerticalDelayInLines.
                                       // The range is from zero to Vtotal minus 1. Refer to the following table for Vtotal values at different resolutions.<p>
                                       // <b>Note:</b> The exact duration of a line (in seconds) can be calculated as follows: 1 / (frame rate * Vtotal)
   bool bEnableFlywheel;               // If true, enables the flywheel.
   double dFlywheelMaxUnlockTime;      // Indicates the maximum time (in seconds) that the flywheel remains unlocked before entering free running mode.
                                          // The range is from zero to 3600 seconds.
   double dFlywheelMaxRecoveryTime;    // Indicates the maximum time (in seconds) for the flywheel to resynchronize to the input signal.
                                          // The range is from zero to 3600 seconds
   SMvResolutionInfo sResolution;      // Indicates the genlock resolution.
   EMvGenlockSource eGenlockSource;    // Indicates the genlock source.
   uint32_t ui32SourceIndex;           // Indicates the connector index when the genlock source is set to keGenlockSourceSDIVideo.
   bool bEnableTermination;            // If true, activates the electrical termination of the genlock input (REF IN).
   bool bEnableGenlockClockOffset;     // If true, activates the manual control of the genlock clock speed.
   double dGenlockClockOffsetPPM;      // If bEnableGenlockClockOffset is set to true, this parameter controls the genlock clock speed, which is defined in parts
                                          // per million (PPM). A positive value will increase the speed of the clock, while a negative value will decrease the speed. 
                                          // The granularity is approximately 0.003 PPM and the valid range is -160.0 PPM to +160.0 PPM. <p>
                                          // <b>Note:</b> When the clock speed is modified, it is strongly recommended that your DSX card be monitored and 
                                          // controlled constantly to make sure it follows the external clock.
};

//
// Summary:
//    Describes the genlock input status.
//
struct SMvGenlockInputStatus
{
   uint32_t ui32Size;                              // Structure size in bytes.
   EMvGenlockState eGenlockState;                  // Indicates the state of the genlock circuit.
   SMvResolutionInfo sDetectedResolution;          // Indicates the auto-detected genlock resolution.
   EMvTerminationStatus  eTerminationSwitchStatus; // Indicates the status of the genlock input termination switch.
};

//
// Summary:
//    Describes the blackburst input status.
//
struct SMvBlackburstStatus
{
   uint32_t ui32Size;                              // Structure size in bytes.
   bool bBlackburstSignalPresent;                  // If true, a blackburst signal is detected.
   SMvResolutionInfo sBlackburstResolution;        // Indicates the auto-detected blackburst resolution.
};

//
// Summary:
//    Describes the input stream settings.
//
struct SMvInputStreamSettings
{
   uint32_t ui32Size;                                       // Structure size in bytes.
   SMvVideoInputStreamSettings sVideoInputStreamSettings;   // Indicates the video input stream settings.
   EMvInputStreamMode eInputStreamMode;                     // Indicates the time base correction applied to the input stream.
   SMvAudioInputStreamSettings sAudioInputStreamSettings;   // Indicates the audio input stream settings.
   EMvQuadrant                 aeVideoConnectorPosition[kui32MaxConnectorQuadrants];  // Indicates the quadrant of a UHD image
                                                            // to which an SDI input connector corresponds. Only valid on hardware 
                                                            // that supports UHD resolutions.
};

//
// Summary:
//    Describes the settings of one layer of the mixer stream.
//
struct SMvMixerStreamNodeSettings
{
   uint32_t ui32Size;         // Structure size in bytes.
   double dNodeTransparency;  // Indicates the transparency that will be applied on the node's image.  
                                 // The range is from zero (completely transparent) to one (completely opaque).
   SMvPointF ptNodePosition;  // Indicates the coordinates where the node's image will be placed.
                                 // The range is from -4096 to 4096 for both the X and Y axis.
   bool bUseAlpha;            // If true, uses the node's image alpha.
   bool bIsVideoShaped;       // If true, the node's video is already multiplied by its alpha.
   uint64_t ui64AdvancedDelayInNanoTime; // Indicates the delay (in nanotime) that will be applied to a mixer stream's layer. The value must be frame aligned. 
                                             // The advanced delay must be less than the node depth
                                             // minus the node's write-to-read delay minus three frames. That is, <p> 
                                             // <i> Advance delay < node depth - node's write-to-read delay - 3 frames </i>
   bool bChromaFilterARGB;     // If true, applies a chroma filter when converting an ARGB layer to YUV color space. 
                               // Applies only to ARGB layers. 
};

//
// Summary:
//    Enumerates the mixer stream's compositing mode.
//
enum EMvCompositingMode
{
   keMvCompositingModeInvalid,      // Invalid value.
   keMvCompositingModeUpStream,     // Indicates that the mixer stream will compose layers without a background.  
                                       // The resulting image will be composed on a background later.
   keMvCompositingModeDownStream,   // Indicates that the mixer stream will compose layers over a background.  The 
                                       // resulting image is the final result that will be viewed on a monitor.
   keMvCompositingModeLast          // End of list indicator.
};

#define MV_COMPOSITING_MODE_ENUM_TO_STRING(eMode) \
   ((eMode == keMvCompositingModeInvalid) ? _T("Invalid") : \
   (eMode == keMvCompositingModeUpStream) ? _T("Upstream") : \
   (eMode == keMvCompositingModeDownStream) ? _T("Downstream") : \
   (eMode == keMvCompositingModeLast) ? _T("Last") : \
   _T("???"))

//
// Summary:
//    Describes the mixer stream's settings.
//
struct SMvMixerStreamSettings
{
   uint32_t              ui32Size;              // Structure size in bytes.
   EMvNodeContent        eNodeContentToProcess; // Indicates the type of data in the stream to process. For example, video data only, VANC data only, or 
                                                // any other data combination.
   bool                  bProcessAudio;         // If true, the mixer stream selects an audio from one of its input layers.
   uint32_t              ui32AudioSelect;       // Indicates the audio layer to apply to the mixer stream's output. The value ranges from
                                                // zero (background) to the number of layers. Can only be applied if bProcessAudio is set to true.
                                                // If eCompositingMode is set to keMvCompositingModeUpStream, zero cannot be used as an audio layer.
   bool                  bProcessVanc;          // If true, the mixer stream selects a VANC from one of its input layers.
   uint32_t              ui32VancSelect;        // Indicates the VANC layer to apply to the mixer stream's output. The value ranges from
                                                // zero (background) to the number of layers. Can only be applied if bProcessAudio is set to true.
                                                // If eCompositingMode is set to keMvCompositingModeUpStream, zero cannot be used as a VANC layer.
   EMvCompositingMode    eCompositingMode;      // Indicates the type of composition that the mixer stream performs on the video.
   EMvColor              eBackgroundColor;      // Indicates the color of the background. Can only be applied if eCompositingMode is set to keMvCompositingModeDownStream
                                                // and eBackgroundHandling is set to keMvBackgroundHandlingColor.
   EMvBackgroundHandling eBackgroundHandling;   // Indicates whether a color or background will be used. Use keMvBackgroundHandlingColor to indicate that a color will be used
                                                // and keMvBackgroundHandlingWaitAndCopy to indicate that a background will be used.
                                                // Can only be applied if eCompositingMode is set to keMvCompositingModeDownStream.
   bool                  bIsOutputVideoShaped;  // If true, the mixer stream generates a video that is already multiplied by its alpha.
                                                // Can only be applied if eCompositingMode is set to keMvCompositingModeUpStream.
   bool                  bBackgroundChromaFilterARGB;  // If true, applies a chroma filtering when converting an ARGB background to YUV color space. 
                                                       // Applies only if eBackgroundHandling is keMvBackgroundHandlingWaitAndCopy and the node was created with a video surface format
                                                       // (SMvNodeSettingsVideo::eSurfaceFormat) of keMvSurfaceFormatARGBGraphic. 
   uint64_t              ui64BackgroundNodeAdvancedDelayInNanoTime;  // Indicates the delay (in nanotime) that will be applied to a mixer stream's background. The value must be frame aligned.
                                                                     // The advanced delay must be less than the node depth minus the node's write-to-read delay minus three frames. That is, <p> 
                                                                     // <i> Advance delay < node depth - node's write-to-read delay - 3 frames </i>

};

//
// Summary:
//    Describes the node's audio settings.
//
struct SMvNodeSettingsAudio
{
   uint32_t ui32Size;               // Structure size in bytes.
   EMvChannelType eChannelType;     // Type of channels supported (for example, mono, stereo, etc.).
   EMvAudioDataType eDataType;      // Type of audio data samples (for example, PCM, float, etc.).
   uint32_t ui32BitsPerSample;      // Bits per sample for the format type. This value represents the container size.
                                    // This field must be greater than or equal to ui32ValidBitsPerSample.
   uint32_t ui32ValidBitsPerSample; // Valid bits per sample for the format type. This value represents the data size within the container. 
                                    // This field must be less than or equal to ui32BitsPerSample.
};

//
// Summary:
//    Describes the node's VANC settings.
//
struct SMvNodeSettingsVanc
{
   uint32_t ui32Size;               // Structure size in bytes.
   uint32_t ui32ComponentBitCount;  // The bits per component of the VANC surface that is kept.  The value must be 10 bits 
                                       // when eVancFormat is set to keMvSurfaceFormatYUYV422 and 16 bits
                                       // when eVancFormat is set to keMvSurfaceFormatMatroxAncillaryData.
   EMvSurfaceFormat eVancFormat;    // Indicates the VANC data format of the node.  Only keMvSurfaceFormatYUYV422
                                       // and keMvSurfaceFormatMatroxAncillaryData are valid for indicating the VANC data format.
};

//
// Summary:
//    Describes the node's settings.
// Description:
//<table>
//   Type of stream to which node is connected       <i> xmin </i>       <i> x </i>  
// -----------------------------------------     -----------------   --------------
// Input stream                                  2 <sup>a</sup>      4           
// Output stream                                 1                   3           
// Transform stream (input)                      1 <sup>b</sup>      3 <sup>c</sup>        
// Transform stream (output)                     1 <sup>d</sup>      3           
// Mixer stream (output)                         1                   3           
// De-interlacer stream (input)                  1                   3           
// De-interlacer stream (output)                 1                   3           
// Transfer stream (input) <sup>e</sup>          1                   3           
// Transfer stream (output) <sup>e</sup>         1                   3           
// </table>
// Remarks:
// - <sup>a</sup> For Matrox X.mio3 and DSX LE4, xmin is 1 when the system clock is derived from an input or a genlock source that is genlocked to an SDI input or a black burst source.  
//   If a black burst source is used, all the SDI inputs must be V-sync aligned to the black burst V-sync with a tolerance of 650 µs.
// - <sup>b</sup> xmin is 4 in the case of a 3:2 pulldown or frame rate change from 50, 59.94, or 60 fps to 25, 29.97, or 30 fps.
// - <sup>c</sup> x is 4 when the resolution is changed from interlaced video with a frame rate of 25, 29.97, or 30 fps to progressive video with a frame rate of 50, 59.94, or 60 fps.
// - <sup>d</sup> xmin is 2 for a UHD resolution with a frame rate of 50, 59.94, or 60 fps.
// - <sup>e</sup> If two transfer streams use the same host node, the write-to-read delay must be at least 3 frames.
//
struct SMvNodeSettings
{
   uint32_t ui32Size;                        // Structure size in bytes.
   char szName[32];                          // Indicates the name that will be given to the node.
   EMvNodeContent eNodeContent;              // Indicates the type of content in the node.
   uint64_t ui64WriteToReadDelayInNanoTime;  // Indicates the delay (in nanotime) between a stream putting data into 
                                                // the node and another stream retrieving data from the node.  
                                                // The write-to-read delay must be at least <i> xmin </i> frames, and less than or equal to the node depth
                                                // (ui32Depth) minus <i> x </i> frames. That is, <p>
                                                // <i> xmin frames <= ui64WriteToReadDelayInNanoTime <= ui32Depth - x frames </i> <p>
                                                // The values of <i> xmin </i> and <i> x </i> depend on the type of stream to which the node is connected. 
                                                // The following table contains the values for <i> xmin </i> and <i> x </i>.
   uint32_t ui32Depth;                       // Indicates the maximum number of frames that will be kept in the node at any time. 
                                                // The node depth must be greater than or equal to 
                                                // the write-to-read delay (ui64WriteToReadDelayInNanoTime) plus <i> x </i> frames. That is, <p>
                                                // <i> ui32Depth >= ui64WriteToReadDelayInNanoTime + x frames </i> <p>
                                                // The value of <i> x </i> depends on the type of stream to which the node is connected. 
                                                // The following table contains the values for <i> x </i>.
                                                //
};

//
// Summary:
//    Describes the type of data contained in the node and where the node's memory is located.
//
enum EMvNodeType
{
   keMvNodeTypeInvalid,             // Invalid value.
   keMvNodeTypeCard,                // Indicates that the node contains uncompressed data in the card's onboard memory. 
                                    // The IMvNode interface is used to interact with this type of node.
   keMvNodeTypeHost,                // Indicates that the node contains uncompressed data in host memory.  
                                    // The IMvHostNode interface is used to interact with this type of node.
   keMvNodeTypeCompressedHost,      // Indicates that the node contains compressed data in host memory.  
                                    // The IMvCompressedHostNode interface is used to interact with this type of node.
   keMvNodeTypeSharedHost,          // Indicates that the node contains uncompressed data in shared host memory.  
                                    // The IMvHostNode interface is used to interact with this type of node.
   keMvNodeTypeAliasCard,           // Indicates that the node contains uncompressed read-only data in the card's shared onboard memory. 
                                    // The IMvNode interface is used to interact with this type of node.
   keMvNodeTypeTextureGpu,          // Indicates that the node contains host data that can be used as a texture in 
                                    // the GPU. The IMvTextureNode interface is used to interact with this type of node.
   keMvNodeTypeRenderingTargetGpu,  // Indicates that the node contains host data that can be used as a rendering
                                    // target in the GPU. The IMvRenderingTargetNode interface is used to interact 
                                    // with this type of node.
   keMvNodeTypeLast                 // End of list indicator.
};

#define MV_NODE_TYPE_ENUM_TO_STRING(eNodeType) \
   ((eNodeType == keMvNodeTypeInvalid)            ? "Invalid" : \
    (eNodeType == keMvNodeTypeCard)               ? "Card" : \
    (eNodeType == keMvNodeTypeHost)               ? "Host" : \
    (eNodeType == keMvNodeTypeCompressedHost)     ? "Compressed host" : \
    (eNodeType == keMvNodeTypeSharedHost)         ? "Shared host" : \
    (eNodeType == keMvNodeTypeTextureGpu)         ? "Texture GPU" : \
    (eNodeType == keMvNodeTypeRenderingTargetGpu) ? "Rendering target GPU" : \
    _T("???"))

//
// Summary:
//    Describes the node's video settings.
//
struct SMvNodeSettingsVideo
{
   uint32_t ui32Size;                  // Structure size in bytes.
   SMvResolutionInfo sResInfo;         // Indicates the resolution information of the node.
   EMvSurfaceFormat eSurfaceFormat;    // Indicates the surface format of the node.
   EMvColorimetry eColorimetry;        // Indicates the colorimetry of the node.
};

//
// Summary:
//    Describes the output stream settings.
//
struct SMvOutputStreamSettings
{
   uint32_t ui32Size;                                       // Indicates the structure size in bytes.
   SMvAudioOutputStreamSettings sAudioOutputStreamSettings; // Indicates the audio settings of the output stream.
   SMvVideoOutputStreamSettings sVideoOutputStreamSettings; // Indicates the video settings of the output stream.
   EMvQuadrant                  aeVideoConnectorPosition[kui32MaxConnectorQuadrants];  // Indicates the quadrant of a UHD image
                                                            // to which an SDI output connector corresponds. Only valid on hardware 
                                                            // that supports UHD resolutions.
};

//
// Summary:
//    Describes the video's transform stream settings.
// Remarks:
// - This structure is part of the SMvTransformStreamSettings structure.

struct SMvVideoTransformSettings
{
   EMvVideoTransformType eVideoTransformType;   // Indicates the type of video scaling done by the transform stream.
   SMvRect sInputRect;                          // Indicates which part of the image obtained from the input node of 
                                                   // the transform stream to scale.
   SMvRect sOutputRect;                         // If eVideoTransformType is set to keMvVideoTransformTypeRegion, a rectangular area from the 
                                                   // transform stream's input node is scaled to the size of a rectangular area in the transform stream's output node.
                                                   // The size of the output node video content is the same as the output node's resolution. The rest of the image is black. <p>
                                                   // If eVideoTransformType is set to keMvVideoTransformTypeResize, a rectangular area from the
                                                   // transform stream's input node is scaled to the size of an output rectangle in the transform stream's output node.
                                                   // Each frame sent to the output node is resized independently of other frames and independently of the node's resolution. 
                                                   // The resized frames must be in a lower resolution than the output node's resolution.
   uint64_t ui64InputNodeAdvancedDelayInNanoTime; // Indicates the delay (in nanotime) that will be applied to a transform stream's input.
                                                  // The value must be frame aligned both at the input and the output.
                                                  // The advanced delay must be less than the node depth minus the node's write-to-read delay minus three frames. That is, <p> 
                                                  // <i> Advance delay < node depth - node's write-to-read delay - 3 frames </i>
   EMvTransformProcessing eProcessFields;      // Indicates how the transform stream processes data.
   bool bVerticalFilterManualControl;          // If true, the vertical filter sharpness control is done manually instead of automatically.
                                                   // It is recommended to manually control the vertical filter when downscaling, to reduce aliasing without blurring the image.  
   uint32_t ui32VerticalFilterManualValue;     // When vertical filter control is manual, indicates the selected sharpness control value.
                                                   // Range is 0 to 9. Typical value is "3". A value of "0" disables filtering. Lower values will generate sharper images,
                                                   // higher values will generate softer images. 
   EMvTransformFilterCoefficients eTransformFilterCoefficients; // Selects the transform filter coefficients. Default value is keMvTransformFilterCoeffStandard.
};

//
// Summary:
//    Describes the SDI video input connector settings.
//
struct SMvSdiVideoInputConnectorSettings
{
   bool bEnable3GLevelB;      // Selects which 3G level to use when the input is 1080p @ 50 fps, 59.94 fps, or 60 fps. <p>
                              // If true, enables SMPTE 425M (3G) Level B mapping. <p>
                              // If false, enables SMPTE 425M (3G) Level A mapping. <p> 
                              // Uses a parameter of type EMvOnOff.
};

//
// Summary:
//    Describes the SDI input connector settings.
//
struct SMvSdiInputConnectorSettings
{
   uint32_t ui32Size;                                 // Structure size in bytes.
   SMvSdiVideoInputConnectorSettings sVideoSettings;  // Structure of the SDI video input connector settings.
};

//
// Summary:
//    Describes the SDI video output connector settings.
// Remarks:
// - This structure is part of the SMvSdiOutputConnectorSettings structure.
// Description:
//<table>
// Resolution              Vtotal (in pixels)    Htotal (in pixels)    Approximate duration of a pixel (in seconds)
// -------------------     -------------------   ------------------    ---------------------------------------------
// NTSC                    525                   858                   74.074 x 10<sup>-9</sup>
// PAL                     625                   864                   74.074 x 10<sup>-9</sup>
// 720p at 23.98 fps       750                   4125                  13.481 x 10<sup>-9</sup>
// 720p at 24 fps          750                   4125                  13.468 x 10<sup>-9</sup>
// 720p at 25 fps          750                   3960                  13.468 x 10<sup>-9</sup>
// 720p at 29.97 fps       750                   3300                  13.481 x 10<sup>-9</sup>
// 720p at 30 fps          750                   3300                  13.468 x 10<sup>-9</sup>
// 720p at 50 fps          750                   1980                  13.468 x 10<sup>-9</sup>
// 720p at 59.94 fps       750                   1650                  13.481 x 10<sup>-9</sup>
// 720p at 60 fps          750                   1650                  13.468 x 10<sup>-9</sup>
// 1080i at 25 fps         1125                  2640                  13.468 x 10<sup>-9</sup>
// 1080i at 29.97 fps      1125                  2200                  13.481 x 10<sup>-9</sup>
// 1080i at 30 fps         1125                  2200                  13.468 x 10<sup>-9</sup>
// 1080PsF at 23.98 fps    1125                  2750                  13.481 x 10<sup>-9</sup>
// 1080PsF at 24 fps       1125                  2750                  13.468 x 10<sup>-9</sup>
// 1080PsF at 25 fps       1125                  2640                  13.468 x 10<sup>-9</sup>
// 1080PsF at 29.97 fps    1125                  2200                  13.481 x 10<sup>-9</sup>
// 1080PsF at 30 fps       1125                  2200                  13.468 x 10<sup>-9</sup>
// 1080p at 23.98 fps      1125                  2750                  13.481 x 10<sup>-9</sup>
// 1080p at 24 fps         1125                  2750                  13.468 x 10<sup>-9</sup>
// 1080p at 25 fps         1125                  2640                  13.468 x 10<sup>-9</sup>
// 1080p at 29.97 fps      1125                  2200                  13.481 x 10<sup>-9</sup>
// 1080p at 30 fps         1125                  2200                  13.468 x 10<sup>-9</sup>
// 1080p at 50 fps         1125                  2640                  6.734 x 10<sup>-9</sup>
// 1080p at 59.94 fps      1125                  2200                  6.740 x 10<sup>-9</sup>
// 1080p at 60 fps         1125                  2200                  6.734 x 10<sup>-9</sup>
// </table>
//
struct SMvSdiVideoOutputConnectorSettings
{
   double dLineBufferHorizonalDelay;   // Sets the SDI line buffer delay in pixels. For digital video only. The range is -256 to 256.
   double dHorizontalFrameDelay;       // Controls the horizontal frame delay on the SDI output circuit in seconds. 
                                       // The output delay is a combination of dHorizontalFrameDelay, ui32VerticalFrameDelay, 
                                       // and dLineBufferHorizonalDelay, if dLineBufferHorizonalDelay is supported on your hardware.<p>
                                       // For SD, the granularity is 0.5 pixel (approximately 37.037 nanoseconds), and the range is from zero to (Htotal - 0.5) * 74.074 x 10<sup>-9</sup>. Where Htotal is the total horizontal width in pixels. <p>
                                       // For 720p at 24, 25, 30, 50, or 60 fps and 1080p at 24, 25, or 30 fps, the granularity is 1 pixel (approximately 13.468 nanoseconds), and the range is from zero to (Htotal - 1) * 13.468 x 10<sup>-9</sup>.<p> 
                                       // For 720p at 23.98, 29.97, or 59.94 fps and 1080p at 23.98 or 29.97 fps, the granularity is 1 pixel (approximately 13.481 nanoseconds), and the range is from zero to (Htotal - 1) * 13.481 x 10<sup>-9</sup>.<p> 
                                       // For 1080p at 50 or 60 fps, the granularity is 1 pixel (approximately 6.734 nanoseconds), and the range is from zero to (Htotal - 1) * 6.734 x 10<sup>-9</sup>.<p> 
                                       // For 1080p at 59.94 fps, the granularity is 1 pixel (approximately 6.740 nanoseconds), and the range is from zero to (Htotal - 1) * 6.740 x 10<sup>-9</sup>.<p> 
                                       // Refer to the following table for Htotal values and approximate duration of a pixel at different resolutions.<p> 
                                       // <b>Note:</b> The exact duration of a pixel (in seconds) can be calculated as follows: 1 / (frame rate * Htotal * Vtotal), where Vtotal is the total vertical height in pixels.
   uint32_t ui32VerticalFrameDelay;    // Controls the vertical delay on the SDI output circuit in lines.
                                       // The output delay is a combination of dHorizontalFrameDelay, ui32VerticalFrameDelay,
                                       // and dLineBufferHorizonalDelay, if dLineBufferHorizonalDelay is supported on your hardware.
                                       // The range is from zero to Vtotal minus 1. Refer to the following table for Vtotal values at different resolutions.<p>
                                       // <b>Note:</b> The exact duration of a line (in seconds) can be calculated as follows: 1 / (frame rate * Vtotal)
   bool bEnable3GLevelB;               // Selects which 3G level to use when the output is 1080p at 50 fps, 59.94 fps, or 60 fps. 
                                       // If true, enables SMPTE 425M (3G) Level B mapping. Otherwise, enables SMPTE 425M (3G) Level A mapping. 
   bool bEnableSMPTE352;               // If true, enables SMPTE 352 packets.
   double dAlphaLineBufferHorizonalDelay;   // Sets the SDI Alpha line buffer delay in pixels.  The range is -256 to 256.
                                       // This control applies only to the alpha channel on an output with video and alpha.
                                       // The alpha channel output delay is a combination of dHorizontalFrameDelay, ui32VerticalFrameDelay, 
                                       // and dAlphaLineBufferHorizonalDelay, if dAlphaLineBufferHorizonalDelay is supported on your hardware.
   bool bInterleavePixels;             // If true, enables outputting UHD resolutions by setting the proper SMPTE ST 352 IDs to images that have been divided using the 2-sample 
                                       // interleave division method (as per SMPTE ST 425-5).

};

//
// Summary:
// Describes the embedded SDI audio output connector settings.
// Remarks:
// - This structure is part of the SMvSdiOutputConnectorSettings structure.
//
struct SMvSdiEmbeddedAudioOutputConnectorSettings
{
   bool bEnableEmbeddedAudio;                      // If true, enables the embedded audio.
   EMvAudioBitsPerSample aePairBitsPerSample[8];   // Number of bits per audio sample, one value per audio pair.
   bool abPairIsPCMAudio[8];                       // If true, the pair is marked as Pulse-code modulation (PCM) audio in the channel status. One per audio pair.
   bool bActivateDBN;                              // If true, generates the embedded audio Data Block Number (DBN) in Standard 
                                                   // Definition (SD). This control has no effect in 
                                                   // High Definition (HD) because HD always contains embedded audio DBN.
                                                   // Equipment with HD/SD support will not decode audio properly unless DBN in audio packets is activated.
                                                   // Older equipment will not work properly if DBN in audio data packets is activated
                                                   // to the extent that the video may be corrupted.  
                                                   // If the video is corrupted, do not use embedded audio DBN. 
};

//
// Summary:
//    Describes the SDI output connector settings.
//
struct SMvSdiOutputConnectorSettings
{
   uint32_t ui32Size;                                          // Structure size in bytes.
   SMvSdiVideoOutputConnectorSettings sVideoSettings;          // Structure of the SDI video output connector settings.
   SMvSdiEmbeddedAudioOutputConnectorSettings sAudioSettings;  // Structure of the embedded SDI audio output connector settings.
};

//
// Summary:
//    Specifies which SMPTE 2016-1 AFD code is applied.
// Description:
//<table>
// Members                                             Aspect ratio and AFD code     Image                    Description
// --------------------------------------------------  -------------------------     -------------------      -----------------------------------------------------------
// keMvAFDCode_4_3_Undefined                           0 0000                                                 Indicates an undefined value.
// keMvAFDCode_4_3_Letter16_9ImageAtTop                0 0010                        <image AFD_0_0010>       Indicates an image with a 16:9 aspect ratio as letterbox at the top of a 4:3 coded frame. 
// keMvAFDCode_4_3_Letter14_9ImageAtTop                0 0011                        <image AFD_0_0011>       Indicates an image with a 14:9 aspect ratio as letterbox at the top of a 4:3 coded frame. 
// keMvAFDCode_4_3_LetterImageGreater16_9              0 0100                        <image AFD_0_0100>       Indicates an image with an aspect ratio greater than 16:9 as a vertically centered letterbox in a 4:3 coded frame.
// keMvAFDCode_4_3_FullFrame4_3Preferred               0 1000                        <image AFD_0_1000>       Indicates a full frame image with an aspect ratio that is the same as the 4:3 coded frame. This is the preferred coding for a full frame 4:3 image. 
// keMvAFDCode_4_3_FullFrame4_3                        0 1001                        <image AFD_0_1000>       Indicates a full frame image with an aspect ratio that is the same as the 4:3 coded frame.
// keMvAFDCode_4_3_Letterbox16_9ImageCentered          0 1010                        <image AFD_0_1010>       Indicates an image with a 16:9 aspect ratio as a vertically centered letterbox in a 4:3 coded frame with all image areas protected. <p> This code is used with images that may not fill the frame vertically, but where all areas of the image should be displayed (for example, an image where cropping is not permitted) and can only be adequately displayed in letterbox format.
// keMvAFDCode_4_3_Letterbox14_9ImageCentered          0 1011                        <image AFD_0_1011>       Indicates an image with a 14:9 aspect ratio as a vertically centered letterbox in a 4:3 coded frame. 
// keMvAFDCode_4_3_FullFrame4_3Image14_9Center         0 1101                        <image AFD_0_1101>       Indicates an image with a 4:3 aspect ratio and with an alternative 14:9 center in a 4:3 coded frame.
// keMvAFDCode_4_3_Letterbox16_9Image14_9Center        0 1110                        <image AFD_0_1110>       Indicates an image with a 16:9 aspect ratio and with an alternative 14:9 center as a vertically centered letterbox in a 4:3 coded frame.
// keMvAFDCode_4_3_Letterbox16_9Image4_3Center         0 1111                        <image AFD_0_1111>       Indicates an image with a 16:9 aspect ratio and with an alternative 4:3 center as a vertically centered letterbox in a 4:3 coded frame.
// keMvAFDCode_16_9_Undefined                          1 0000                                                 Indicates an undefined value.
// keMvAFDCode_16_9_Full16_9Image                      1 0010                        <image AFD_1_1000>       Indicates a full frame image with an aspect ratio that is the same as the 16:9 coded frame. This code is not used in North America. 
// keMvAFDCode_16_9_Pillar14_9ImageCentered            1 0011                        <image AFD_1_1011>       Indicates an image with a 14:9 aspect ratio as a horizontally centered pillarbox image in a 16:9 coded frame. This code is not used in North America. 
// keMvAFDCode_16_9_LetterImageGreater16_9             1 0100                        <image AFD_1_0100>       Indicates an image with an aspect ratio greater than 16:9 as a vertically centered letterbox in a 16:9 coded frame.
// keMvAFDCode_16_9_Full16_9ImagePreferred             1 1000                        <image AFD_1_1000>       Indicates a full frame image with an aspect ratio that is the same as the 16:9 coded frame. This is the preferred coding for a full frame 16:9 image.
// keMvAFDCode_16_9_Pillar4_3ImageCentered             1 1001                        <image AFD_1_1001>       Indicates an image with a 4:3 aspect ratio as a horizontally centered pillarbox image in a 16:9 coded frame. 
// keMvAFDCode_16_9_Full16_9ImageAreasProtected        1 1010                        <image AFD_1_1010>       Indicates a full frame image with a 16:9 aspect ratio and with all image areas protected. <p> This code is used with images that may not fill the frame vertically, but where all areas of the image should be displayed (for example, an image where cropping is not permitted) and can only be adequately displayed in letterbox format.
// keMvAFDCode_16_9_Pillar14_9ImageCenteredPreferred   1 1011                        <image AFD_1_1011>       Indicates an image with a 14:9 aspect ratio as a horizontally centered pillarbox image in a 16:9 coded frame. This is the preferred coding for a horizontally centered 14:9 pillarbox image.
// keMvAFDCode_16_9_Pillar4_3Image14_9Center           1 1101                        <image AFD_1_1101>       Indicates an image with a 4:3 aspect ratio and with an alternative 14:9 center as a horizontally centered pillarbox image in a 16:9 coded frame.
// keMvAFDCode_16_9_Full16_9Image14_9Center            1 1110                        <image AFD_1_1110>       Indicates an image with a 16:9 aspect ratio and with an alternative 14:9 center in a 16:9 coded frame. 
// keMvAFDCode_16_9_Full16_9Image4_3Center             1 1111                        <image AFD_1_1111>       Indicates an image with a 16:9 aspect ratio and with an alternative 4:3 center in a 16:9 coded frame.
// </table>
// Remarks:
//   - The first bit in the aspect ratio and AFD code column indicates the aspect ratio (0 indicates an aspect ratio of 4:3 while 1 indicates an aspect ratio of 16:9), and the remaining bits indicate the AFD code.
//   - The alternative center refers to an area of essential picture information. The areas outside this center may be cropped without significant loss to the viewer. 

enum EMvAFDCode
{
   keMvAFDCode_4_3_Undefined                          = 0x0,
   keMvAFDCode_4_3_Letter16_9ImageAtTop               = 0x2,
   keMvAFDCode_4_3_Letter14_9ImageAtTop               = 0x3,
   keMvAFDCode_4_3_LetterImageGreater16_9             = 0x4,
   keMvAFDCode_4_3_FullFrame4_3Preferred              = 0x8,  
   keMvAFDCode_4_3_FullFrame4_3                       = 0x9, 
   keMvAFDCode_4_3_Letterbox16_9ImageCentered         = 0xA,
   keMvAFDCode_4_3_Letterbox14_9ImageCentered         = 0xB,     
   keMvAFDCode_4_3_FullFrame4_3Image14_9Center        = 0xD, 
   keMvAFDCode_4_3_Letterbox16_9Image14_9Center       = 0xE,
   keMvAFDCode_4_3_Letterbox16_9Image4_3Center        = 0xF, 

   keMvAFDCode_16_9_Undefined                         = 0x10,
   keMvAFDCode_16_9_Full16_9Image                     = 0x12,
   keMvAFDCode_16_9_Pillar14_9ImageCentered           = 0x13,     
   keMvAFDCode_16_9_LetterImageGreater16_9            = 0x14, 
   keMvAFDCode_16_9_Full16_9ImagePreferred            = 0x18, 
   keMvAFDCode_16_9_Pillar4_3ImageCentered            = 0x19,      
   keMvAFDCode_16_9_Full16_9ImageAreasProtected       = 0x1A,
   keMvAFDCode_16_9_Pillar14_9ImageCenteredPreferred  = 0x1B, 
   keMvAFDCode_16_9_Pillar4_3Image14_9Center          = 0x1D,    
   keMvAFDCode_16_9_Full16_9Image14_9Center           = 0x1E,
   keMvAFDCode_16_9_Full16_9Image4_3Center            = 0x1F, 
};

#define MV_AFD_CODE_ENUM_TO_STRING(eValue) \
   ((eValue == keMvAFDCode_4_3_Undefined) ? _T("(0000) 4:3 - Undefined") : \
   (eValue == keMvAFDCode_4_3_Letter16_9ImageAtTop) ? _T("(0010) 4:3 - Letterbox 16:9, at top") : \
   (eValue == keMvAFDCode_4_3_Letter14_9ImageAtTop) ? _T("(0011) 4:3 - Letterbox 14:9, at top") : \
   (eValue == keMvAFDCode_4_3_LetterImageGreater16_9) ? _T("(0100) 4:3 - Letterbox, aspect ratio > 16:9") : \
   (eValue == keMvAFDCode_4_3_FullFrame4_3Preferred) ? _T("(1000) 4:3 - Full 4:3 (PREFER)") : \
   (eValue == keMvAFDCode_4_3_FullFrame4_3) ? _T("(1001) 4:3 - Full 4:3") : \
   (eValue == keMvAFDCode_4_3_Letterbox16_9ImageCentered) ? _T("(1010) 4:3 - Letterbox 16:9, centered") : \
   (eValue == keMvAFDCode_4_3_Letterbox14_9ImageCentered) ? _T("(1011) 4:3 - Letterbox 14:9, centered") : \
   (eValue == keMvAFDCode_4_3_FullFrame4_3Image14_9Center) ? _T("(1101) 4:3 - Full 4:3, 14:9 center") : \
   (eValue == keMvAFDCode_4_3_Letterbox16_9Image14_9Center) ? _T("(1110) 4:3 - Letterbox 16:9, 14:9 center") : \
   (eValue == keMvAFDCode_4_3_Letterbox16_9Image4_3Center) ? _T("(1111) 4:3 - Letterbox 16:9, 4:3 center") : \
   (eValue == keMvAFDCode_16_9_Undefined) ? _T("(0000) 16:9 - Undefined") : \
   (eValue == keMvAFDCode_16_9_Full16_9Image) ? _T("(0010) 16:9 - Full 16:9") : \
   (eValue == keMvAFDCode_16_9_Pillar14_9ImageCentered) ? _T("(0011) 16:9 - Pillarbox 14:9, centered") : \
   (eValue == keMvAFDCode_16_9_LetterImageGreater16_9) ? _T("(0100) 16:9 - Letterbox, aspect ratio > 16:9") : \
   (eValue == keMvAFDCode_16_9_Full16_9ImagePreferred) ? _T("(1000) 16:9 - Full 16:9 (PREFER)") : \
   (eValue == keMvAFDCode_16_9_Pillar4_3ImageCentered) ? _T("(1001) 16:9 - Pillarbox 4:3, centered") : \
   (eValue == keMvAFDCode_16_9_Full16_9ImageAreasProtected) ? _T("(1010) 16:9 - Full 16:9, image areas protected") : \
   (eValue == keMvAFDCode_16_9_Pillar14_9ImageCenteredPreferred) ? _T("(1011) 16:9 - Pillarbox 14:9, centered (PREFER)") : \
   (eValue == keMvAFDCode_16_9_Pillar4_3Image14_9Center) ? _T("(1101) 16:9 - Pillarbox 4:3, 14:9 Center") : \
   (eValue == keMvAFDCode_16_9_Full16_9Image14_9Center) ? _T("(1110) 16:9 - Full frame, 14:9 center") : \
   (eValue == keMvAFDCode_16_9_Full16_9Image4_3Center) ? _T("(1111) 16:9 - Full frame, 4:3 center") : \
   _T("???"))

//
// Summary:
//   Describes the VANC settings of the transform stream.
// Remarks:
// - This structure is part of the SMvTransformStreamSettings structure.
// - The members of this structure are applied only if the VANC data format (EMvSurfaceFormat) of the transform stream's 
//   input and output nodes use keMvSurfaceFormatMatroxAncillaryData.
//
struct SMvVancConvertingTransformSettings
{
   bool bClipAllVancPackets;              // If true, removes all VANC packets.
   bool bConvertDigitalCEA608ToAnalog;    // If true, converts Matrox Ancillary Data VANC format to line 21.
   bool bConvertAnalogCEA608ToDigital;    // If true, converts Line 21 to Matrox Ancillary Data VANC format.
   bool bInsertBarDataUsingDestRect;      // If true, uses SMvTransformStreamSettings::sVideoTransformSettings::sOutputRect to set the output node's bar data.
   bool bInsertAFDCode;                   // If true, uses eAFDCodeAndAspectRatio to set the output node's AFD code.
   EMvAFDCode eAFDCodeAndAspectRatio;     // If bInsertAFDCode is true, indicates the AFD code value to use.
};

//
// Summary:
//    Describes the transform stream settings.
//
struct SMvTransformStreamSettings
{
   uint32_t ui32Size;                                                   // Structure size in bytes.
   SMvVideoTransformSettings sVideoTransformSettings;                   // Indicates the transform stream's video settings.
   SMvVancConvertingTransformSettings sVancConvertingTransformSettings; // Indicates the transform stream's VANC settings.
   bool bProcessAudio;                                                  // If true, the transform stream processes the input node's audio.
   EMvNodeContent eNodeContentToProcess;                                // Indicates the type of data in the stream to process. For example, video data only, VANC data only, or 
                                                                        // any other data combination.
};

//
// Summary:
//    Describes the video's de-interlacer stream settings.

struct SMvDeInterlacerStreamSettings
{
   uint32_t ui32Size;                             // Structure size in bytes.
   bool     bShowMotionVectors;                   // If true, the output of the de-interlacer stream will show the motion 
                                                  // vector of the de-interlacing process.
   uint32_t ui32IncreaseMotionSensitivity;        // Increases motion sensitivity. Defaut value is 0, range is 0 to 7.
   uint32_t ui32DecreaseAntiAliasingEdgeSensitivity;  // Decreases Anti-Aliasing Edge Sensitivity. Default value is 0, range 0 to 9.
   bool     bShowAntiAliasingEdgeMap;             // If true, the output of the de-interlacer stream will show the anti-aliasing edge map. Default value is false.
   bool     bProcessVanc;                         // If true, the de-interlacer stream processes the input node's ancillary data.
   bool     bConvertAnalogCEA608ToDigital;        // If true, converts Line 21 to Matrox Ancillary Data VANC format.
   bool     bProcessAudio;                        // If true, the de-interlacer stream processes the input node's audio.
   uint64_t ui64InputNodeAdvancedDelayInNanoTime; // Indicates the delay (in nanotime) that will be applied to a de-interlacer stream's input.
                                                  // The value must be frame aligned both at the input and the output.
                                                  // The advanced delay must be less than the node depth minus the node's
                                                  // write-to-read delay minus three frames. That is, <p> 
                                                  // <i> Advance delay < node depth - node's write-to-read delay - 3 frames </i>
   EMvNodeContent eNodeContentToProcess;          // Indicates the type of data in the stream to process. For example, video data only, VANC data only, or 
                                                  // any other data combination.
};


//
// Summary:
//    Indicates the GPI (General Purpose Interface) input pin that triggers a watchdog and/or the GPI output pin to activate when a watchdog is triggered.
//
enum EMvGeneralPurposePin
{
   keMvGeneralPurposePinInvalid, // Invalid value.
   keMvGeneralPurposePin1,       // GPI input pin 1 (labeled GPIO-1).
   keMvGeneralPurposePin2,       // GPI input pin 2 (labeled GPIO-2).
   keMvGeneralPurposePin3,       // GPI input pin 3 (labeled GPIO-3).
   keMvGeneralPurposePin4,       // GPI input pin 4 (labeled GPIO-4).
   keMvGeneralPurposePin5,       // GPI input pin 5 (labeled GPIO-5).
   keMvGeneralPurposePin6,       // GPI input pin 6 (labeled GPIO-6).
   keMvGeneralPurposePin7,       // GPI output pin 1 (labeled GPIO-7).
   keMvGeneralPurposePin8,       // GPI output pin 2 (labeled GPIO-8).
   keMvGeneralPurposePinLast     // End of list indicator.
};

#define MV_GENERAL_PURPOSE_PIN_ENUM_TO_STRING(eValue) \
   ((eValue == keMvGeneralPurposePinInvalid) ? _T("Invalid") : \
   (eValue == keMvGeneralPurposePin1) ? _T("Pin 1") : \
   (eValue == keMvGeneralPurposePin2) ? _T("Pin 2") : \
   (eValue == keMvGeneralPurposePin3) ? _T("Pin 3") : \
   (eValue == keMvGeneralPurposePin4) ? _T("Pin 4") : \
   (eValue == keMvGeneralPurposePin5) ? _T("Pin 5") : \
   (eValue == keMvGeneralPurposePin6) ? _T("Pin 6") : \
   (eValue == keMvGeneralPurposePin7) ? _T("Pin 7") : \
   (eValue == keMvGeneralPurposePin8) ? _T("Pin 8") : \
   (eValue == keMvGeneralPurposePinLast) ? _T("Last") : \
   _T("???"))

//
// Summary:
//    Describes the type of GPI (General Purpose Interface) signal that will activate the GPI input and/or output pin as specified in EMvGeneralPurposePin.
//
enum EMvTriggerType
{
   keMvTriggerTypeInvalid,       // Invalid value.
   keMvTriggerTypeFallingEdge,   // The GPI pin is activated when a falling edge is detected.
   keMvTriggerTypeRisingEdge,    // The GPI pin is activated when a rising edge is detected.
   keMvTriggerTypeLowLevel,      // The GPI pin is activated when a low level is detected.
   keMvTriggerTypeHighLevel,     // The GPI pin is activated when a high level is detected.
   keMvTriggerTypeLast           // End of list indicator.
};

#define MV_TRIGGER_TYPE_ENUM_TO_STRING(eValue) \
   ((eValue == keMvTriggerTypeInvalid) ? _T("Invalid") : \
   (eValue == keMvTriggerTypeFallingEdge) ? _T("Falling edge") : \
   (eValue == keMvTriggerTypeRisingEdge) ? _T("Rising edge") : \
   (eValue == keMvTriggerTypeLowLevel) ? _T("Low level") : \
   (eValue == keMvTriggerTypeHighLevel) ? _T("High level") : \
   (eValue == keMvTriggerTypeLast) ? _T("Last") : \
   _T("???"))

//
// Summary:
//    Describes the settings that can trigger a watchdog.
// Remarks:
// - The watchdog feature is not supported on DSX LE3.
//
struct SMvWatchdogSettings
{
   uint32_t ui32size;                                    // Structure size in bytes.
   bool     bForceTopology;                              // If true, the watchdog is triggered immediately. 
                                                         // If false, allows bEnableTimeout and/or eGeneralPurposeInputPin to trigger a watchdog.
   bool     bEnableTimeout;                              // If true, dWatchDogTimeOutInSeconds is activated.
   double   dWatchDogTimeOutInSeconds;                   // Indicates the amount of time in seconds that needs to elapse before the watchdog is triggered.
   EMvGeneralPurposePin eGeneralPurposeInputPin;         // Indicates which GPI input pin triggers a watchdog. If you do not want to use a GPI input pin, set eGeneralPurposeInputPin 
                                                         // to keMvGeneralPurposePinInvalid. This will also cause eGeneralPurposeInputPinTriggerType to be ignored.
   EMvTriggerType eGeneralPurposeInputPinTriggerType;    // Indicates the type of GPI signal that will activate eGeneralPurposeInputPin.
   EMvGeneralPurposePin eGeneralPurposeOutputPin;        // Indicates which GPI output pin to activate when a watchdog is triggered. If you do not want to use a GPI output pin, set eGeneralPurposeOutputPin 
                                                         // to keMvGeneralPurposePinInvalid. This will also cause eGeneralPurposeOutputPinTriggerType to be ignored.
   EMvTriggerType eGeneralPurposeOutputPinTriggerType;   // Indicates the type of GPI signal that eGeneralPurposeOutputPin will generate.
   uint64_t ui64GeneralPurposeOutputPinPulseInNanoTime;  // If eGeneralPurposeOutputPinTriggerType is set to keMvTriggerTypeFallingEdge or keMvTriggerTypeRisingEdge, indicates the duration of the pulse (in nanotime) on the GPI output pin. Otherwise, not used.
};

//
// Summary:
//    Specifies which node image to save to the card's permanent memory.
//
struct SMvNodeContent
{
   uint32_t ui32Size;         // Structure size in bytes.
   uint64_t ui64Timestamp;    // Indicates the time stamp of the node image to save to the card's permanent memory.
};

//
// Summary:
//    Specifies the type of DSX system clock.
// Remarks:
// - For more information on which DSX cards support these DSX system clock types, see the <i>Matrox DSX Topology API User Guide</i>.
//
enum EMvSystemClockType
{
   keMvSystemClockTypeInvalid,      // Invalid value. 
   keMvSystemClockTypeGenlock,      // Specifies that the DSX system clock is ticking at the speed of the genlock of the card.
   keMvSystemClockTypeInput,        // Specifies that the DSX system clock is ticking at the speed of an input connector.
   keMvSystemClockTypeRendering,    // Specifies that the DSX system clock is ticking at a speed that is a multiple of the genlock clock. 
                                    // The possible values are one, two, four, or eight times the speed of the genlock clock.
   keMvSystemClockTypeUniversal,    // Specifies that the DSX system clock is ticking at the speed of a hardware independant clock.
                                    // The speed is decided based on the resolution passed upon creation.
                                    // It is optionnally synchronized on a NTP server.
   keMvSystemClockTypeLast          // End of list indicator.
};


#define MV_SYSTEM_CLOCK_TYPE_ENUM_TO_STRING(eValue) \
   ((eValue == keMvSystemClockTypeInvalid)   ? "Invalid"   : \
    (eValue == keMvSystemClockTypeGenlock)   ? "Genlock"   : \
    (eValue == keMvSystemClockTypeInput)     ? "Input"     : \
    (eValue == keMvSystemClockTypeRendering) ? "Rendering" : \
    (eValue == keMvSystemClockTypeUniversal) ? "Universal" : \
    (eValue == keMvSystemClockTypeLast)      ? "Last"      : \
    ("???"))

//
// Summary:
//    Indicates which asynchronous event was generated.
//
enum EMvEventReportSource
{
   keMvEventReportSourceInvalid,             // Invalid value.
   keMvEventReportSourceDefaultsWritten,     // Indicates that the default state has been saved to permanent memory.
   keMvEventReportSourceDefaultsCleared,     // Indicates that the default state has been cleared from permanent memory.
   keMvEventReportSourceNodeContentWritten,  // Indicates that the node's content has been saved to permanent memory.
   keMvEventReportSourceWatchdogTriggered,   // Indicates that a watchdog has been triggered.
   keMvEventReportSourceSetSettingsFailed,   // Indicates that a setting was sent late.
   keMvEventReportSourceLast                 // End of list indicator.
};

//
// Summary:
//    Describes the asynchronous event that was generated.
//
struct SMvEventReportInfo
{
   uint32_t             size;           // Structure size in bytes.
   EMvEventReportSource eSource;        // Indicates which asynchronous event was generated.
   IMvTopology *        pITopology;     // Pointer to the topology interface. This pointer is used if eSource is keMvEventReportSourceNodeContentWritten or keMvEventReportSourceWatchdogTriggered.
                                        // Otherwise, the pointer is not used. The IUnknown::AddRef() method of the pITopology parameter is called when the asynchronous event is generated
                                        // to prevent the object implementing the IMvTopology interface from being destroyed.
   IUnknown *           pIObject;       // If eSource is keMvEventReportSourceNodeContentWritten, the pointer is to the IMvNode interface.
                                        // The IUnknown::AddRef() method of the pIObject parameter is called when the asynchronous event is generated
                                        // to prevent the object implementing the IMvNode interface from being destroyed. <p>
                                        // If eSource is keMvEventReportSourceWatchdogTriggered, the pointer is to the IMvWatchdog interface. 
                                        // The IUnknown::AddRef() method of the pIObject parameter is called when the asynchronous event is generated
                                        // to prevent the object implementing the IMvWatchdog interface from being destroyed. <p>
                                        // Otherwise this field is set to NULL.
   HRESULT              hrErrorCode;    // An error code concerning the event.
};

//
// Summary:
//    Specifies the number of connectors on the card.
//
struct SMvConnectorsGeneralDescription
{
   uint32_t size;                                  // Structure size in bytes.
   uint32_t ui32SDIInputConnectorsCount;           // Indicates the number of SDI input connectors on the card.
   uint32_t ui32SDIOutputConnectorsCount;          // Indicates the number of SDI output connectors on the card.
   uint32_t ui32AesEbuAudioInputConnectorsCount;   // Indicates the number of AES/EBU input connectors on the card.
   uint32_t ui32AesEbuAudioOutputConnectorsCount;  // Indicates the number of AES/EBU output connectors on the card.
   uint32_t ui32AnalogAudioInputConnectorsCount;   // Indicates the number of analog audio input connectors on the card.
   uint32_t ui32AnalogAudioOutputConnectorsCount;  // Indicates the number of analog audio output connectors on the card.
   uint32_t ui32AnalogVideoInputConnectorsCount;   // Indicates the number of analog video input connectors on the card.
   uint32_t ui32AnalogVideoOutputConnectorsCount;  // Indicates the number of analog video output connectors on the card.
};

//
// Summary:
//    Enumerates the PCI standard of the card.
//
enum EMvPciStandard
{
   keMvPciStandardInvalid,    // Invalid value   
   keMvPciStandardPci,        // Indicates that the card has a PCI communication bus.
   keMvPciStandardPciX,       // Indicates that the card has a PCI-X communication bus.
   keMvPciStandardPciExpress, // Indicates that the card has a PCI Express communication bus.
   keMvPciStandardPciExpressGen2, // Indicates that the card has a PCI Express 2.0 communication bus.
   keMvPciStandardPciLast     // End of list indicator.
};

#define MV_PCI_STANDARD_ENUM_TO_STRING(eValue) \
   ((eValue == keMvPciStandardInvalid)    ? _T("Invalid") : \
   (eValue == keMvPciStandardPci)         ? _T("PCI") : \
   (eValue == keMvPciStandardPciX)        ? _T("PCI-X") : \
   (eValue == keMvPciStandardPciExpress)  ? _T("PCI-E") : \
   (eValue == keMvPciStandardPciExpressGen2)  ? _T("PCI-E Gen2") : \
   (eValue == keMvPciStandardPciLast)     ? _T("Last") : \
   _T("???"))

//
// Summary:
//    Enumerates the PCI bus width.
//
// Remarks:
//    - For PCI Express, values 1, 2, 4, 8, 12, 16, and 32 are valid.
//    - For the others PCI buses, values 32 and 64 are valid.
//
enum EMvPciBusWidth
{
   keMvPciBusWidthInvalid, // Invalid value.
   keMvPciBusWidth1  = 1,  // Indicates that the bus width is PCIe x1.
   keMvPciBusWidth2  = 2,  // Indicates that the bus width is PCIe x2.
   keMvPciBusWidth4  = 4,  // Indicates that the bus width is PCIe x4.
   keMvPciBusWidth8  = 8,  // Indicates that the bus width is PCIe x8.
   keMvPciBusWidth12 = 12, // Indicates that the bus width is PCIe x12.
   keMvPciBusWidth16 = 16, // Indicates that the bus width is PCIe x16.
   keMvPciBusWidth32 = 32, // Indicates that the bus width is PCI 32 bits and PCIe x32.
   keMvPciBusWidth64 = 64, // Indicates that the bus width is PCI 64 bits.
   keMvPciBusWidthLast     // End of list indicator.
};

//
// Summary:
//    Enumerates the PCI bus frequency.
//
enum EMvPciBusFrequency
{
   keMvPciBusFrequencyInvalid,   // Invalid value.
   keMvPciBusFrequency33,        // Indicates that the bus speed is 33 MHz.
   keMvPciBusFrequency66,        // Indicates that the bus speed is 66 MHz.
   keMvPciBusFrequency100,       // Indicates that the bus speed is 100 MHz.
   keMvPciBusFrequency133,       // Indicates that the bus speed is 133 MHz.
   keMvPciBusFrequency2500,      // Indicates that the bus speed is 2.5 GHz.
   keMvPciBusFrequency5000,      // Indicates that the bus speed is 5.0 GHz.
   keMvPciBusFrequencyLast       // End of list indicator.
};

#define MV_PCI_BUS_FREQUENCY_ENUM_TO_STRING(eValue) \
   ((eValue == keMvPciBusFrequencyInvalid) ? _T("Invalid") : \
   (eValue == keMvPciBusFrequency33)       ? _T("33 MHz") : \
   (eValue == keMvPciBusFrequency66)       ? _T("66 MHz") : \
   (eValue == keMvPciBusFrequency100)      ? _T("100 MHz") : \
   (eValue == keMvPciBusFrequency133)      ? _T("133 MHz") : \
   (eValue == keMvPciBusFrequency2500)     ? _T("2.5 GHz") : \
   (eValue == keMvPciBusFrequency5000)     ? _T("5.0 GHz") : \
   (eValue == keMvPciBusFrequencyLast)     ? _T("Last") : \
   _T("???"))

//
// Summary:
//    Describes the complete PCI bus information for a card.
//
struct SMvPciBusInfo
{
   uint32_t               size;        // Structure size in bytes.
   EMvPciStandard         eStandard;   // Indicates the PCI standard.
   EMvPciBusFrequency     eFrequency;  // Indicates the bus frequency.
   EMvPciBusWidth         eWidth;      // Indicates the bus width.
                                          // For PCI Express, it represents the number of lanes.
                                          // For other PCI standards, it is 32 or 64 bits.
};

//
// Summary:
//    Describes the general hardware information for a card.
//
struct SMvGeneralHardwareInformation 
{
   uint32_t                        size;                      // Structure size in bytes.
   EMvHardwareSerie                eHardwareSerieDetected;    // Indicates the hardware series.
   uint32_t                        ui32BoardVariation;        // Indicates the card variation.
   uint32_t                        ui32FpgasVersion[4];       // Indicates the FPGA's version.
   uint32_t                        ui32FirmwareVersion;       // Indicates the firmware version. 
   char                            szSerialNumber[32];        // Indicates the serial number.
   char                            szVariationName[32];       // Indicates the serial number.
   uint32_t                        ui32OemID;                 // Indicates the OEM ID.
   char                            szProgDate[32];            // Indicates the date that the card was programmed.
   uint32_t                        ui32EEPromVersion;         // Indicates the EEProm version.
                                                              // The most significant 16 bits indicates the major version.
                                                              // The least significant 16 bits indicates the minor version.
   SMvPciBusInfo                   sBusSpeedInformation;      // Indicates the PCI bus speed information.
   uint32_t                        ui32MemorySizeInMegaBytes; // Indicates the on board memory size in MB.
   SMvConnectorsGeneralDescription sConnectorsDescription;    // Structure containing information about the different connectors on the card.
   EMvHardwareProfile              eHardwareProfileType;      // Indicates the hardware profile.
   uint32_t                        ulHardwareProfileIndex;    // Indicates the hardware index. 
};

//
// Summary:
//    Describes the settings used to configure the Memory Manager.
//
struct SMvMemoryManagerConfiguration
{
   uint32_t    size;                         // Structure size in bytes.
   uint32_t    ui32MaxSizeToAllocateInMB;    // Maximum amount of memory to allocate for file reading and writing.
   uint32_t    ui32TimeOutInMilliSecond;     // If the maximum size has been reached, indicates the amount of time to wait for memory to be released.
   uint32_t    ui32Reserved[14];             // Reserved for future use.
};

//
// Summary:
//    Describes the action that the Memory Manager is required to fill if bNeedAResponse is true.
//
enum EMvMemoryManagerAction
{
   kEMvMemoryManagerInvalid,        // Invalid value.
   kEMvMemoryManagerWait,           // Wait for memory to be freed. 
   kEMvMemoryManagerFail,           // Do not wait, fail instead.
   kEMvMemoryManagerAllocate,       // Try to allocate memory beyond the maximum value as specified by ui64SizeRequiredInBytes in SMvMemoryManagerNotification.
   kEMvMemoryManagerLast            // End of list indicator.
};
//
// Summary:
//    Describes the action required by the Memory Manager.
//
struct SMvMemoryManagerNotification
{
   uint32_t                size;                         // Structure size in bytes.
   uint32_t                ui32MaxSizeToAllocateInMB;    // Maximum memory to allocate for file reading and writing.
   uint32_t                ui32TimeOutInMilliSecond;     // If the maximum has been reached, indicates the amount of time to wait before taking action.
   uint64_t                ui64SizeAllocatedInBytes;     // Indicates the total memory currently allocated.
   uint64_t                ui64SizeRequiredInBytes;      // If the maximum has been reached, indicates the amount of additional memory to be allocated.
   HRESULT                 hResult;                      // Indicates the error code. This can be a warning.
   bool                    bNeedAResponse;               // If true, the user application returns the action that the Memory Manager is required to fill in eActionToTake.
   EMvMemoryManagerAction  eActionToTake;                // If bNeedAResponse is true, indicates the action to perform.
};

//
// Summary:
//    Describes the status of the Memory Manager.
//
struct SMvMemoryManagerStatus
{
   uint32_t    size;                         // Structure size in bytes.
   uint32_t    ui32MaxSizeToAllocateInMB;    // Indicates the maximum memory to allocate for file reading and writing.
   uint32_t    ui32CurrentlyUsedInMB;        // Indicates the total memory currently allocated.
   uint32_t    ui32MaxSizeAllocatedInMB;     // Indicates the maximum memory that is reached at any point in time.
   uint32_t    ui32TimeOutInMilliSecond;     // If more memory is needed, indicates the amount of time to wait before taking action.
};

//
// Summary:
//    Describes the time code settings.
//
struct SMvTimeCodeSettings
{
   uint32_t ui32Size;           // Structure size in bytes.
   EMvTimeCodeSource eSource;   // Specifies the time code source.
};

//
// Summary:
//    Describes the analog linear time code settings.
//
struct SMvALTCSettings
{
   uint32_t ui32Size;            // Structure size in bytes.
   EMvALTCSamplingClock eClock;  // Specifies the sampling clock.
};

//
// Summary:
//    Describes the time code information.
// Description:
//
// <P ALIGN=Center> <b> Time code values </b>
// <table>                                     
// Bits     Description 
// -----    ---------------------------------------
// 3:0      Units of frames. 
// 5:4      Tens of frames.
// 9:6      Units of seconds. 
// 12:10    Tens of seconds.
// 16:13    Units of minutes. 
// 19:17    Tens of minutes.
// 23:20    Units of hours.
// 25:24    Tens of hours.
// 26       Drop frame flag.
// 27       Color frame flag. 
// 28       Polarity correction flag. LTC (linear time code) only. <p> Field identification flag. VITC (vertical interval time code) only.
// 29       Binary group 0 flag.
// 30       Binary group 1 flag.
// 31       Binary group 2 flag.
// 35:32    First binary group value.
// 39:36    Second binary group value. 
// 43:40    Third binary group value.
// 47:44    Fourth binary group value. 
// 51:48    Fifth binary group value.
// 55:52    Sixth binary group value.
// 59:56    Seventh binary group value.
// 63:60    Eighth binary group value.
// </table>
//
// <P ALIGN=Center> <b> VITC status values </b>
// <table>
// Bits     VITC Description
// -----    -----------------------------------
//  0       When the value is 1, a VITC is present in the last vblank.
//  1       When the value is 1, a VITC CRC error was found.
//  2       When the value is 1, the time code is new (it is not a repeated time code).
//  3       When the value is 1, a time code was missed and replaced by a newer one.
// </table>
// <P ALIGN=Center> <b> LTC status values </b>
// <table>
// Bits     LTC Description
// -----    -----------------------------------
//  0       Speed variation, always 1 for now.
//  1       Forward when the value is 1, reverse when the value is 0.
//  2       When the value is 1, the time code is new (it is not a repeated time code).
//  3       When the value is 1, a time code was missed and replaced by a newer one.
// </table>

struct SMvTimeCodeInformation
{
   uint32_t size;             // Structure size in bytes.
   uint64_t ui64Timestamp;    // Time stamp of the requested time code in nanotime.
   uint64_t ui64TimeCode;     // Time code associated with the time stamp.
   unsigned long ulStatus;    // Status of the time code.
   
};

// Describes the time code information from the input stream. <p>
// Refer to the SMvIOExtraInfo structure for the SMPTE 12M-2 (previously SMPTE RP188) LTC/VITC values.
struct SMvInputTimeCodeInformation
{
   uint32_t size;                        // Structure size in bytes.
   uint64_t ui64RP188_LTCValue;          // Indicates the SMPTE 12M-2 LTC (linear time code) value. 
   bool     bRP188_LTCPresent;           // If true, indicates that the SMPTE 12M-2 LTC is present in the input video stream.
   uint64_t ui64RP188_VITCValue;         // Indicates the SMPTE 12M-2 VITC (vertical interval time code) value. 
   bool     bRP188_VITCPresent;          // If true, indicates that the SMPTE 12M-2 VITC is present in the input video stream.
   uint64_t ui64Analog_LTCValue;         // Indicates the SMPTE 12M-1 analog LTC (linear time code) value. 
   bool     bAnalog_LTCPresent;          // If true, indicates that the SMPTE 12M-1 analog LTC is present.
};

//
// Summary:
//    Describes the Flex Tunnel to DirectShow settings.
//
struct SMvFlexTunnelToDirectShowDescription
{
   uint32_t ui32Size;                       // Indicates the structure size in bytes.
   wchar_t wszTunnelName[512];              // Indicates the name of the Flex tunnel.
   uint32_t ui32TunnelLength;               // Indicates the length of the Flex tunnel (number of buffers). <p> The minimum Flex tunnel length to create is:<p>
                                            // - 30 for frame rates less than or equal to 30 fps.<p>
                                            // - 60 for frame rates greater than 30 fps.
   SMvResolutionInfo sResolutionInfo;       // Indicates the resolution of the Flex tunnel.<p> Only 8-bit resolution component bit count can be used.
   EMvSurfaceFormat  eSurfaceFormat;        // Indicates the surface format of the Flex tunnel. <p> Only keMvSurfaceFormatYUYV422 can be used as the surface format.
   EMvChannelType    eAudioChannelType;     // Indicates the audio channel type of the Flex tunnel. <p> Only keChannelTypeStereo can be used as the audio channel type.
};


// Summary:
//  Specifies the location of VANC data in a file.
//

enum EMvVANCLocation 
{
   keMvVANCLocationDefault,      // Indicates that the VANC data is placed in the default location for capture, or to indicates to read VANC data from default location for playbacks.
   keMvVANCLocationEssence =1,   // Indicates that the VANC data is placed in the video essence for capture, or to indicates to read VANC data from essence for playbacks.
   keMvVANCLocationWrapper =2,   // Indicates that the VANC data is placed in the file wrapper for capture, or to indicates to read VANC data from wrapper for playbacks.
   keMvVANCLocationBoth    =3,   // Indicates that the VANC data is placed in both the video essence and the file wrapper for capture. Does not apply for playbacks.
   keMvVANCLocationLast          // End of list indicator.
};

//
// Summary:
//    Describes the descriptive metadata framework types.
//
enum EMvDMType
{
   keMvFrameworkInvalid = 0,        // Indicates an invalid value.
   keMvAS03Framework,               // Indicates the AS-03 descriptive metadata framework.
   keMvAS10Framework,               // Indicates the AS-10 descriptive metadata framework.
   keMvAS11CoreFramework,           // Indicates the AS-11 core metadata framework element scheme.
   keMvAS11SegmentationFramework,   // Indicates the AS-11 segmentation metadata framework element scheme.
   keMvAS11UKDPPFramework,          // Indicates the AS-11 UK Digital Production Partnership (DPP) metadata framework element scheme.
   keMvAS12Framework,               // Indicates the AS-12 descriptive metadata framework.
   keMvFrameworkLast                // End of list indicator.
};


#define MV_VANC_LOCATION_ENUM_TO_STRING(eValue) \
   ((eValue == keMvVANCLocationDefault) ? _T("Default Location") : \
   (eValue == keMvVANCLocationEssence) ? _T("VANC in Essence") : \
   (eValue == keMvVANCLocationWrapper) ? _T("VANC in Wrapper") : \
   (eValue == keMvVANCLocationBoth) ? _T("VANC in Essence and Wrapper") : \
   _T("???") )

// Summary:
// Specifies the action to be taken by the Flex File Reader when a position takes a long time to be retrieved from disk.
enum EMvPositionNotReadyAction
{
   keMvPosNotReadyActionKeepWaiting,            // Instructs the Flex File Reader to keep waiting for the data to arrive.
   keMvPosNotReadyTimeOut,                      // Causes an MV_E_FAILED_TO_RETRIEVE_POSITION_FROM_DISK to be returned.
   keMvPosNotReadyProceed,                      // Black frame/silence will be returned. Buffers will contain the warning MV_W_FAILED_TO_RETRIEVE_POSITION_FROM_DISK.
   keMvPosNotReadyLast                          // End of list indicator.
};

#define MV_MPEG2_MUXER_BITRATE_OPTION_TO_STRING(eValue) \
   ((eValue == keMvMPEG2MuxerBitRateOptionCBR) ? _T("Constant Bit Rate") : \
   (eValue == keMvMPEG2MuxerBitRateOptionVBR) ? _T("Variable Bit Rate") : \
   _T("???") )

// Summary:
// Describes the encoding options for the Matrox MPEG-2 Transport Stream.
struct SMvTSEncoderOptions
{
   uint32_t          ui32Size;                  // Structure size in bytes.
   EMvCodecOption    eVideoCodecOption;         // Indicates the video codec option.
   MVCHANDLE         mvchVideoOptionSettings;   // Indicates the video option settings.
   EMvCodecOption    eAudioCodecOption;         // Indicates the audio codec option.
   MVCHANDLE         mvchAudioOptionSettings;   // Indicates the audio option settings.
   bool              bProcessVanc;              // If true, VANC data is processed.
};

////
// Summary:
//    Describes the surface format and component bit count of an input buffer to be used for compression.
//

struct SMvBufferOption
{
   uint32_t          ui32Size;                           // Size of the structure in bytes.
   EMvSurfaceFormat  eSurfaceFormat;                     // Surface format of the buffer.
   uint32_t          ui32ComponentBitCount;              // Bits per component of the buffer.
};

// Summary:
//  Specifies where the time code is located.
// Remarks:
// - Applies to MXF files only.
//

enum EMvTimecodeLocation
{
   keMvTimecodeLocationDefault = 0, // Indicates that the time code is in the default location. For AS-11, the default location is keMvTimecodeLocationMXFHeader. Otherwise, the default location is keMvTimecodeLocationMXFTrack.
   keMvTimecodeLocationEssence = 1, // Indicates that the time code is located in the video essence. 
   keMvTimecodeLocationMXFTrack = 2, // Indicates that the time code is located in the frame-wrapped system element.
   keMvTimecodeLocationMXFHeader = 3, // Indicates that the time code is located in the metadata.
   keMvTimecodeLocationLast // End of list indicator.
};

#define MV_TIMECODE_LOCATION_ENUM_TO_STRING(eValue) \
   ((eValue == keMvTimecodeLocationDefault) ? _T("Default Location") : \
   (eValue == keMvTimecodeLocationEssence) ? _T("TC in Essence") : \
   (eValue == keMvTimecodeLocationMXFTrack) ? _T("TC in System Items") : \
   (eValue == keMvTimecodeLocationMXFHeader) ? _T("TC in Header") : \
   _T("???") )

// Summary:
//  Specifies the v210 support option for the reader and writer.
// Remarks:
// - If the support option is keMvFlexSupportDefault, the reader and writer receives YUV 4:2:2 8- or 10-bit buffers as usual.
// - If the support option is keMvFlexSupportV210IfPossible and the capture or playback file supports native v210, the reader and writer will receive v210 buffers.
//
enum EMvFlexV210SupportOption
{
   keMvFlexSupportDefault          = 0,   // Indicates that the reader and writer will supply YUV 4:2:2 8- or 10-bit buffers as usual, regarless of whether or not native v210 is supported.
   keMvFlexSupportV210IfPossible   = 1,   // Indicates that if the codec supports the native v210 input format, the reader and writer will supply v210 buffers. 
   keMvFlexSupportLast                    // End of list indicator.
};

//
// Summary: describes a h.264 supplemental enhancement information payload
//
struct SMvSEIPayload
{
   uint32_t m_ui32Size;
   uint8_t* m_pui8Data;
   uint32_t m_ui32PayloadSize;
   uint32_t m_ui32PayloadType;
};

enum EMvSEIPayloadType
{
   keMvSEIPayloadPicTiming = 1,
   keMvSEIPayloadUserDataRegistered = 4,
   keMvSEIPayloadUserDataUnregistered = 5
};
//
// Summary:
//    Describes the kind of notification regarding the connection status.
//
enum EMvDSXCORENotificationType
{
   keMvDSXCORENotificationDisconnected,         // The DSX Core has become disconnected
   keMvDSXCORENotificationReconnected,          // The DSX Core has reestablished it's connection to the server
   keMvDSXCORENotificationExpiringSoon          // The DSX core has coming within a given threshold from being released on grounds that the lease will expire
};

//
// Summary:
//    Describes the asynchronous event that occurred.
//
struct SMvDSXCORENotification
{
   EMvDSXCORENotificationType      eNotificationType;   // Indicate the type of notification.
};

//
// Summary:
//    Specifies the type of elementary stream.
//
enum EMvMPEG2TSElementaryStreamType
{
   keMvMPEG2TSElementaryStreamTypeInvalid,
   keMvMPEG2TSElementaryStreamTypeOther,     // Elementary stream contains other type of data. There is no specific
                                             // information available for this type of elementary stream.
   keMvMPEG2TSElementaryStreamTypeH264Video, // Elementary stream contains H.264 video. Use 
                                             // IMvMPEG2TSDescription::GetElementaryStreamH264VideoDescription() to 
                                             // have specific information on the content of the stream.
   keMvMPEG2TSElementaryStreamTypeAudioPCM,  // Elementary stream contains uncompressed PCM audio data. Use 
                                             // IMvMPEG2TSDescription::GetElementaryStreamAudioPCMDescription() to
                                             // have specific information on the content of the stream.
   keMvMPEG2TSElementaryStreamTypeSMPTE2038, // Elementary stream contains SMPTE 2038 VANc data. There is no specific
                                             // information available for this type of elementary stream.
   keMvMPEG2TSElementaryStreamTypeLast,
};

#define MV_MPEG2_TS_ELEMENTARY_STREAM_TYPE_ENUM_TO_STRING(eValue) \
   ((eValue == keMvMPEG2TSElementaryStreamTypeInvalid) ? _T("Invalid") : \
   (eValue == keMvMPEG2TSElementaryStreamTypeOther) ? _T("Other") : \
   (eValue == keMvMPEG2TSElementaryStreamTypeH264Video) ? _T("H264 Video") : \
   (eValue == keMvMPEG2TSElementaryStreamTypeAudioPCM) ? _T("PCM Audio") : \
   (eValue == keMvMPEG2TSElementaryStreamTypeSMPTE2038) ? _T("Smpte 2038 VANC") : \
   _T("???") )

//
// Summary:
//    Describes the MPEG-2 elementary stream.
// Remarks:
//    - This is the generic description that is common to all elementary streams. To have more specific description,
//      check the field SMvMPEG2TSElementaryStreamDesc::eType that specifies which specific information that can be 
//      retrieved.
//
struct SMvMPEG2TSElementaryStreamDesc
{
   uint32_t  ui32size;              // Structure size in bytes.
   uint32_t  ui32PID;               // Elementary stream PID.
   uint8_t   ui8ID;                 // Elementary stream ID.
   uint8_t   ui8StreamType;         // Stream type as specified in the PMT or PSM. If the PMT or PSM is not present this field may be 0.
                                    // (See specification ISO/IEC 13818-1 "Stream type assignments").
   EMvMPEG2TSElementaryStreamType eType; // Specified the type of elementary stream Depending on the value, the 
                                    // application can use more precise method to determine the specific setting of
                                    // the elementary stream. All elementary stream answer the basic call to
                                    // IMvMPEG2TSDescription::GetElementaryStreamDescription(). But for more precise 
                                    // information the application must use the the enum value. See 
                                    // EMvMPEG2TSElementaryStreamType for more information.
   uint32_t  ui32DescriptorLength;  // Length in bytes of the field pui8Descriptor.
   uint8_t * pui8Descriptor;        // Descriptor present in the PMT or PSM for this stream.
};

//
// Summary:
//    Describes the MPEG-2 program.
//
struct SMvMPEG2TSProgramDesc
{
   uint32_t          ui32size;              // Structure size in bytes.
   uint32_t          ui32ProgramNumber;     // Program number as specified in the PMT.
   uint32_t          ui32PID;               // Network PID if program_number is 0, else program map PID.
   uint32_t          ui32PCR_PID;           // PID that carries the PCR for this program.
   uint32_t          ui32StreamCount;       // Number of elementary streams in this program.
   uint32_t          ui32DescriptorLength;  // Length in bytes of the field pui8Descriptor.
   uint8_t *         pui8Descriptor;        // Descriptor present in the PMT or PSM.
   SMvResolutionInfo sResolution;           // Specifies the resolution of the first supported video elementary stream.
};

//
// Summary:
//    Describes the MPEG-2 elementary stream containing H.264 video data.
//
struct SMvMPEG2TSElementaryStreamH264VideoDesc
{
   uint32_t          ui32size;               // Structure size in bytes.
   EMvH264Profile    eH264Profile;           // Specifies the H.264 profile.
   EMvH264Level      eH264Level;             // Specifies the H.264 level.
   uint32_t          ui32AvgBitRate;         // Specifies the average data rate in bits/sec.
   bool              bIsVbr;                 // If true, specifies that the data rate is variable. Otherwise the data
                                             // is constant.
   SMvResolutionInfo sResolution;            // Specifies the resolution of the video data.
};

//
// Summary:
//    Describes the MPEG-2 elementary stream containing LPCM audio data.
//
struct SMvMPEG2TSElementaryStreamPCMAudioDesc
{
   uint32_t           ui32size;              // Structure size in bytes.
   SMvaWaveFormatInfo sWaveFormat;           // Audio sample description.
};


