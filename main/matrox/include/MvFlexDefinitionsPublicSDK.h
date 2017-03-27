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

#ifdef LINUX_PLATFORM
   #include "mvLinuxDefinitions.h"
#endif

#include "mvDefinitions.h"
#include <string>

#include "mvIOFlexDefinitions.h"

const float g_kfPi = 3.1415926535897932384626433832795f;

const unsigned short kusFlexClipReaderMaxNumberOfVideoInStream = 16;
const unsigned short kusFlexClipReaderMaxNumberOfAudioInStream = 16;
const unsigned short kusFlexClipReaderMaxNumberOfVBIInStreams  = 16;


// worst case is one second @ 60 fps
const unsigned short kusFlexClipReaderMaxNumberOfFramesPerReadCommand = 150; //We increased audio pipeline size to read 2s for 4k, so we need more.

//
// forward declarations
//
interface IMvInformationCallback;
interface IMvSurface;
interface IMvAudioSamples;


//
// Summary:
//    Describes a fractional number (Numerator/Denominator).
//
struct SMvFraction
{
   int32_t iNumerator;      // Fraction's numerator.
   int32_t iDenominator;    // Fraction's denominator.
};

#ifndef MAC_PLATFORM
//
// Summary:
//    Describes the effect capabilities.
//
struct SMvEffectCapabilities
{
   uint32_t size;                                  // Structure size in bytes.
   GUID     EffectGUID;                            // Specifies the unique identifier of an effect.
   wchar_t  wszInternalName[64];                   // Specifies the name of the effect.
   bool     bIsFilterSupported;                    // If true, indicates that the effect is a filter.
   bool     bIsPixelBasedFilter;                   // If true, indicates that the filter effect is pixel based.
   bool     bIsDownstreamFilterOptimized;          // If true, indicates that the downstream filter method is supported.
   bool     bIsTransitionSupported;                // If true, indicates that the effect is a transition.
   bool     bIsDownstreamTransitionOptimized;      // If true, indicates that the downstream transition method is supported.
   bool     bHasEffectKey;                         // If true, indicates that the effect has an effect key that is not OPAQUE.
   bool     bIsHostAccelerated;                    // If true, indicates that the effect is host-based (implemented by the CPU).
   bool     bIsGraphicEngineAccelerated;           // If true, indicates that the effect is hardware-based (implemented by the GPU).
   bool     bIsShapedInputsSupported;              // If true, indicates that the effect supports shaped images at the input.
   bool     bIsUnshapedInputsSupported;            // If true, indicates that the effect supports unshaped images at the input.
   bool     bIsShapedOutputSupported;              // If true, indicates that the effect supports shaped images at the output.
   bool     bIsUnshapedOutputSupported;            // If true, indicates that the effect supports unshaped images at the output.
   bool     bIsMipmapNeededOnInput;                // If true, indicates that the effect needs an input surface with mipmaps.
   bool     bIsGraphicOutMemoryNeededOnOutput;     // If true, indicates that the effect needs an output surface allocated in the pool keMvMemoryLocationGraphicOut.
};
#endif

// 1394 device state.
enum EMv1394DeviceState
{
   ke1394DeviceStateInvalid,
   ke1394DeviceStatePause,
   ke1394DeviceStatePlay,
   ke1394DeviceStateStop,
   ke1394DeviceStateForward,
   ke1394DeviceStatePlayForward,
   ke1394DeviceStateReverse,
   ke1394DeviceStatePlayReverse,
   ke1394DeviceStateSeek,
   ke1394DeviceStateRecord,
   ke1394DeviceStateRecordPause,
   ke1394DeviceStateLast
};

//
// Summary:
//    Describes an installed 1394 device.
//
struct SMv1394DeviceDescription
{
   uint32_t       size;                         // Structure size in bytes.
   unsigned long  ulDeviceID;                   // ID of the device.
   wchar_t        wszOutputFriendlyName[256];   // Name of the device.
   bool           bAvailable;                   // If true, the device is available.
   bool           bDeviceDV;                    // If true, indicates a DV device.
}; 
//
// Summary:
//    Describes the 1394 device information.
//
struct SMv1394DeviceInformation
{
   uint32_t         size;                         // Structure size in bytes.
   SMv1394DeviceDescription sDescription;		  // Structure of the 1394 device description.      
   bool bMediaPresent;							  // If true, media is present.
}; 
//
// Summary:
//    Describes the 1394 record parameters.
//
struct SMv1394RecordParameters  
{
   uint32_t size;							// Structure size in bytes.
   uint64_t ui64RecordDelayInNanoTime;		// Indicates the record delay in nanotime.
   uint64_t ui64StopDelayInNanoTime;		// Indicates the stop delay in nanotime.
   int      iSeekPrerollInFrame;			// 
   bool     bDropFrame;						// If true, the frame is to be dropped.
};
//
// Summary:
//    Used to set the options of the 1394 writer to do a print to tape.
//
struct SMvFlex1394WriterOptions
{
   uint32_t                size;             // Structure size in bytes.
   EMvSurfaceFormat        eSurfaceFormat;   // Indicates the format of the surface.
   SMvResolutionInfo       sResolution;      // Specifies all information that defines the resolution of the 1394 device.
};


//
// Summary:
//    Specifies 1394 capture options.
//
struct SMvFlex1394ReaderOptions
{
   uint32_t                size;          // Structure size in bytes.
   unsigned long           ulNumOfPairs;  // Number of pairs a user wants to capture for audio.
   SMvResolutionInfo       sResolution;   // 
};

//
// Summary:
//    Specifies the zigzag type for MPEG-2 compression. 
//
enum EMvMpeg2ZigZagType
{
   keMvMpeg2ZigZagTypeInvalid,      // Invalid zigzag type.
   keMvMpeg2ZigZagTypeRegular,      // This is the regular zigzag scanning of the AC coefficient in a Discrete Cosine Transform (DCT) block 
                                    // as defined by ISO/IEC 13818-2 in figure 7-2.  This is the setting used 
                                    // when encoding D10 data (keMvSurfaceFormatMpegD10_422). 
   keMvMpeg2ZigZagTypeAlternate,    // This is the alternate zigzag scanning of the AC coefficient in a DCT block 
                                       // as defined by ISO/IEC 13818-2 in figure 7-3. This is the value that 
                                       // should be used when a high data rate is requested in I-frame compression.
                                       // It will likely provide higher quality compression for the same data rate
                                       // than the regular zigzag.
   keMvMpeg2ZigZagTypeLast          // End of list indicator.
};

//
// Summary:
//    Specifies the rounding type for MPEG-2 compression.
//
enum EMvMpeg2RoundingType
{
   keMvMpeg2RoundingTypeInvalid,       // Invalid rounding type.
   keMvMpeg2RoundingTypeMpeg2,         // The value of the AC coefficients of the DCT block are divided by the
                                          // quantization step size and rounded to the nearest whole number to
                                          // produce the quantization coefficient as defined in Annex D of ISO/IEC
                                          // 11172-2 in section D.6.3.4
   keMvMpeg2RoundingTypeMatroxCustom,  // The value of the AC coefficients of the DCT block are divided by the
                                          // quantization step size and rounded to the lowest whole number to 
                                          // produce the quantization coefficient. This rounding type has
                                          // proven to yield less artifacts for a given data rate under most 
                                          // video content, and is the default value used by the Matrox MPEG-2 codec.
   keMvMpeg2RoundingTypeLast           // End of list indicator.
};

//
// Summary:
//    Specifies the DC precision for MPEG-2 I-frame compression.
//
enum EMvMpeg2DCPrecision
{
   keMvMpeg2DCPrecisionInvalid,  // Invalid DC precision.
   keMvMpeg2DCPrecision8bits,    // DC precision of the intra block is set to 8 bits as defined in the
                                    // ISO/IEC 13818-2 in section 7.2.1. This is the default DC precision 
                                    // setting in the Matrox MPEG-2 I-frame (4:2:2 Profile @ Main Level) video
                                    // codec. Using a higher value is likely to increase the DC content at the 
                                    // expense of the AC content in the encoded stream and produce a compressed 
                                    // stream of lower quality for the same data rate
   keMvMpeg2DCPrecision9bits,    // DC precision of the intra block is set to 9 bits as defined in the
                                    // ISO/IEC 13818-2 in section 7.2.1.
   keMvMpeg2DCPrecision10bits,   // DC precision of the intra block is set to 10 bits as defined in the
                                    // ISO/IEC 13818-2 in section 7.2.1.  This is the setting used 
                                    // when encoding D10 data (keMvSurfaceFormatMpegD10_422).
   keMvMpeg2DCPrecision11bits,   // DC precision of the intra block is set to 11 bits as defined in the
                                    // ISO/IEC 13818-2 in section 7.2.1.
   keMvMpeg2DCPrecisionLast      // End of list indicator.
};

//
// Summary:
//    Describes the MPEG-2 compression options before encoding data.
//
struct SMvMpeg2CompressionOptions
{
   uint32_t             size;                // Size of the structure (for version control).
   unsigned long        ulBitRate;           // Bit rate expressed in bits/seconds.
                                                // For SD resolutions, the range is between 10,000,000 and 50,000,000 (10 Mbits and 50 Mbits). Default is 10,000,000.
                                                // For HD resolutions, the range is between 50,000,000 and 300,000,000 (50 Mbits and 300 Mbits). Default is 50,000,000.
   EMvFrameRate         eFrameRate;          // Specifies the frame rate at which the data will be encoded. Default is keMvFrameRate30M.
   EMvMpeg2ZigZagType   eMpeg2ZigZag;        // Specifies the 'ZigZag' type used to encode the data. Default is keMvMpeg2ZigZagTypeAlternate.
                                                // This flag is ignored when encoding D10 (keMvSurfaceFormatMpegD10_422) and is set automatically to 
                                                // keMvMpeg2ZigZagTypeRegular as defined in the SMPTE 356 specification.
   EMvMpeg2RoundingType eRounding;           // Specifies the Rounding type used to encode the data. Default is keMvMpeg2RoundingTypeCustom.
   EMvMpeg2DCPrecision  eDCPrecision;        // Specifies the DC precision used to encode the data. Default is keMvMpeg2DCPrecision8bits.
                                                // This flag is ignored when encoding D10 (keMvSurfaceFormatMpegD10_422) and is set automatically to 
                                                // keMvMpeg2DCPrecision10bits as defined in the SMPTE 356 specification.
   bool                 bForceDCTFrame;      // If true, the DCT type will always be forced to frame DCT. If false, the 
                                                // DCT type is computed by the codec. In some cases, with computer 
                                                // generated graphics, this would yield less artifacts for a given
                                                // data rate. The default is true. <b> Note: </b>The DCT type computation is used 
                                                // to set whether the macro block is frame DCT coded or field DCT 
                                                // coded as defined by ISO/IEC 13818-2 in section 6.3.17.1. 
   EMvSurfaceFormat     eMpeg2SurfaceFormat; // Specifies the format type of the MPEG-2 surface.
};

//
// Summary:
//    Specifies the different MPEG-2 profiles. 
//
enum EMvMPEG2Profile
{
   keMvMPEG2ProfileInvalid = 0 ,			// Invalid value.
   keMvMPEG2Profile_Simple ,				// Indicates that the MPEG-2 profile is Simple.
   keMvMPEG2Profile_Main ,					// Indicates that the MPEG-2 profile is Main.
   keMvMPEG2Profile_SNRScalable ,			// Indicates that the MPEG-2 profile is SNR scalable.
   keMvMPEG2Profile_SpatiallyScalable ,		// Indicates that the MPEG-2 profile is spatially scalable.
   keMvMPEG2Profile_High ,					// Indicates that the MPEG-2 profile is High.
   keMvMPEG2Profile_422 ,					// Indicates that the MPEG-2 profile is 4:2:2.
   keMvMPEG2Profile_Last					// End of list indicator.
};

//
// Summary:
//    Specifies different MPEG-2 levels. 
//
enum EMvMPEG2Level
{
   keMvMPEG2LevelInvalid = 0 ,		// Invalid value.
   keMvMPEG2Level_Low ,				// Indicates that the MPEG-2 level is Low.
   keMvMPEG2Level_Main ,			// Indicates that the MPEG-2 level is Main.
   keMvMPEG2Level_High1440 ,		// Indicates that the MPEG-2 level is High Level-1440 4:2:0.
   keMvMPEG2Level_High ,			// Indicates that the MPEG-2 level is High.
   keMvMPEG2Level_Last				// End of list indicator.
};


//
// Summary:
//    Describes the H.264 profile ID.
//
enum EMvH264Profile
{
   keMvH264ProfileInvalid,                                     // Not initialized. Invalid value. 
   keMvH264ProfileBaseline           = 66,                     // H.264/AVC Baseline profile.
   keMvH264ProfileMain               = 77,                     // H.264/AVC Main profile.
   keMvH264ProfileHigh               = 100,                    // H.264/AVC High profile.
   keMvH264ProfileHigh10             = 110,                    // H.264/AVC High10 profile (AVC-Intra Class 50).
   keMvH264ProfileHigh422            = 122,                    // H.264/AVC High422 profile (AVC-Intra Class 100).
   keMvH264ProfileLast                                         // End of list indicator.
};

// This macro is used to get the string corresponding to the EMvH264Profile enum value.
#define MV_H264_PROFILE_ENUM_TO_STRING(eMvH264Profile) \
   ((eMvH264Profile == keMvH264ProfileInvalid) ? ("Invalid") : \
   (eMvH264Profile == keMvH264ProfileBaseline) ? ("Baseline") : \
   (eMvH264Profile == keMvH264ProfileMain) ? ("Main") : \
   (eMvH264Profile == keMvH264ProfileHigh) ? ("High") : \
   (eMvH264Profile == keMvH264ProfileHigh10) ? ("High10") : \
   (eMvH264Profile == keMvH264ProfileHigh422) ? ("High422") : \
   (eMvH264Profile == keMvH264ProfileLast) ? ("Last") : \
   ("???"))

//
// Summary:
//    Describes the H.264 level ID.
//
enum EMvH264Level
{
   keMvH264ProfileLevelInvalid,                 // Not initialized.  Invalid value.
   keMvH264ProfileLevel1b   = 9,                // Level  1.b.
   keMvH264ProfileLevel1    = 10,               // Level 1.       
   keMvH264ProfileLevel11   = 11,               // Level 1.1.
   keMvH264ProfileLevel12   = 12,               // Level 1.2.
   keMvH264ProfileLevel13   = 13,               // Level 1.3.

   keMvH264ProfileLevel2    = 20,               // Level 2.
   keMvH264ProfileLevel21   = 21,               // Level 2.1.
   keMvH264ProfileLevel22   = 22,               // Level 2.2.

   keMvH264ProfileLevel3    = 30,               // Level 3.
   keMvH264ProfileLevel31   = 31,               // Level 3.1.
   keMvH264ProfileLevel32   = 32,               // Level 3.2.

   keMvH264ProfileLevel4    = 40,               // Level 4.0.
   keMvH264ProfileLevel41   = 41,               // Level 4.1.
   keMvH264ProfileLevel42   = 42,               // Level 4.2.

   keMvH264ProfileLevel5    = 50,               // Level 5.
   keMvH264ProfileLevel51   = 51,               // Level 5.1.
   keMvH264ProfileLevel52   = 52,               // Level 5.2.
   keMvH264ProfileLevelLast                     // End of list indicator.
};

// This macro is used to get the string corresponding to the EMvH264Profile enum value.
#define MV_H264_LEVEL_ENUM_TO_STRING(eMvH264Level) \
   ((eMvH264Level == keMvH264ProfileLevelInvalid) ? ("Invalid") : \
   (eMvH264Level == keMvH264ProfileLevel1b)  ? ("Level 1.b") : \
   (eMvH264Level == keMvH264ProfileLevel1)  ? ("Level 1") : \
   (eMvH264Level == keMvH264ProfileLevel11) ? ("Level 1.1") : \
   (eMvH264Level == keMvH264ProfileLevel12) ? ("Level 1.2") : \
   (eMvH264Level == keMvH264ProfileLevel13) ? ("Level 1.3") : \
   (eMvH264Level == keMvH264ProfileLevel2)  ? ("Level 2") : \
   (eMvH264Level == keMvH264ProfileLevel21) ? ("Level 2.1") : \
   (eMvH264Level == keMvH264ProfileLevel22) ? ("Level 2.2") : \
   (eMvH264Level == keMvH264ProfileLevel3)  ? ("Level 3") : \
   (eMvH264Level == keMvH264ProfileLevel31) ? ("Level 3.1") : \
   (eMvH264Level == keMvH264ProfileLevel32) ? ("Level 3.2") : \
   (eMvH264Level == keMvH264ProfileLevel4)  ? ("Level 4") : \
   (eMvH264Level == keMvH264ProfileLevel41) ? ("Level 4.1") : \
   (eMvH264Level == keMvH264ProfileLevel42) ? ("Level 4.2") : \
   (eMvH264Level == keMvH264ProfileLevel5)  ? ("Level 5") : \
   (eMvH264Level == keMvH264ProfileLevel51) ? ("Level 5.1") : \
   (eMvH264Level == keMvH264ProfileLevel52) ? ("Level 5.2") : \
   (eMvH264Level == keMvH264ProfileLevelLast) ? ("Last") : \
   ("???"))


//
// Summary:
//    Describes the Matrox H.264/AVC VANC model.
//
enum EMvH264VancModel
{
   keMvH264VancModelInvalid,                                     // Not initialized. Invalid value. 
   keMvH264VancModelANSI_SCTE_128_ETSI_TS_101_154,               // Indicates that the VANC model is ANSI/SCTE 128 and ETSI TS 101 154. 
   keMvH264VancModelAVCIntra,                                    // Indicates that the VANC model is AVC-Intra.
   keMvH264VancModelAVC_HD,                                      // Indicates that the VANC model is AVC-HD
   keMvH264VancModelLast                                         // End of list indicator.
};

// This macro is used to get the string corresponding to the EMvH264Profile enum value.
#define MV_H264_VANC_MODEL_ENUM_TO_STRING(eMvH264VancModel) \
   ((eMvH264VancModel == keMvH264VancModelInvalid) ? ("Invalid") : \
   (eMvH264VancModel == keMvH264VancModelANSI_SCTE_128_ETSI_TS_101_154) ? ("keMvH264VancModelANSI_SCTE_128_ETSI_TS_101_154") : \
   (eMvH264VancModel == keMvH264VancModelAVCIntra) ? ("keMvH264VancModelAVCIntra") : \
   (eMvH264VancModel == keMvH264VancModelAVC_HD) ? ("keMvH264VancModelAVC_HD") : \
   (eMvH264VancModel == keMvH264VancModelLast) ? ("Last") : \
   ("???"))


//
// Summary:
//    Describes the entropy coding
//
enum EMvEntropyCodingMode
{
   keMvEntropyCodingInvalid,         // Invalid value.
   keMvEntropyCodingCAVLC,           // CAVLC
   keMvEntropyCodingCABAC,           // CABAC
   keMvEntropyCodingLast             // End of list indicator.
};

// This macro is used to get the string corresponding to the EMvEntropyCodingType enum value.
#define MV_ENTROPY_CODING_TYPE_ENUM_TO_STRING(eMvEntropyCodingMode) \
   ((eMvEntropyCodingMode == keMvEntropyCodingInvalid) ? ("Invalid") : \
   (eMvEntropyCodingMode == keMvEntropyCodingCAVLC)    ? ("CAVLC") : \
   (eMvEntropyCodingMode == keMvEntropyCodingCABAC)    ? ("CABAC") : \
   (eMvEntropyCodingMode == keMvEntropyCodingLast)     ? ("Last") : \
   ("???"))

//
// Summary:
//    Describes the bit rate control model.
//
enum EMvBitRateModel
{
   keMvBitRateModelInvalid,         // Invalid value.
   keMvBitRateModelCBR,             // Constant bit rate control.
   keMvBitRateModelVBR,             // Variable bit rate control.
   keMvBitRateModelConstantQuality, // Constant quantization parameter encoding.
   keMvBitRateModelLast             // End of list indicator.
};

// This macro is used to get the string corresponding to the EMvBitRateModel enum value.
#define MV_BITRATE_MODEL_ENUM_TO_STRING(eMvBitRateModel) \
   ((eMvBitRateModel == keMvBitRateModelInvalid) ? ("Invalid") : \
   (eMvBitRateModel == keMvBitRateModelCBR)      ? ("CBR") : \
   (eMvBitRateModel == keMvBitRateModelVBR)      ? ("VBR") : \
   (eMvBitRateModel == keMvBitRateModelConstantQuality) ? ("Const. Quality") : \
   (eMvBitRateModel == keMvBitRateModelLast)     ? ("Last") : \
   ("???"))

//
// Summary:
//    Specifies how frequently the Matrox H.264/AVC hardware encoder verifies the current data rate.
//
enum EMvH264SampleRate
{
   keMvH264SampleRateInvalid,    // Not initialized.  Invalid value.
   keMvH264SampleRateLow,        // The rate at which the quality sampling is done is low.
   keMvH264SampleRateHigh,       // The rate at which the quality sampling is done is high.
   keMvH264SampleRateLast        // End of list indicator.
};

// This macro is used to get the string corresponding to the EMvH264SampleRate enum value.
#define MV_H264_SAMPLE_RATE_ENUM_TO_STRING(eSampleRate) \
   ((eSampleRate == keMvH264SampleRateInvalid) ? ("Invalid") : \
    (eSampleRate == keMvH264SampleRateLow)     ? ("Low") : \
    (eSampleRate == keMvH264SampleRateHigh)    ? ("High") : \
    (eSampleRate == keMvH264SampleRateLast)    ? ("Last") : \
    ("???"))

//
// Summary:
//    Describes the GOP structure type.
enum EMvGOPStructureType
{
   keMvGOPStructureTypeInvalid,      // Not initialized. Invalid value.
   keMvGOPStructureTypeSimple,       // Simple GOP model. Same as the MPEG-2 GOP structure.
   keMvGOPStructureTypeAdvanced,     // AVC/H.264 advanced GOP model.
   keMvGOPStructureTypeLast          // End of list indicator.
};

// This macro is used to get the string corresponding to the EMvGOPStructureType enum value.
#define MV_GOP_STRUCTURE_TYPE_ENUM_TO_STRING(eMvGOPStructureType) \
   ((eMvGOPStructureType == keMvGOPStructureTypeInvalid) ? ("Invalid") : \
   (eMvGOPStructureType == keMvGOPStructureTypeSimple)   ? ("Simple") : \
   (eMvGOPStructureType == keMvGOPStructureTypeAdvanced) ? ("Advanced") : \
   (eMvGOPStructureType == keMvGOPStructureTypeLast)     ? ("Last") : \
   ("???"))

//
// Summary:
//    Specifies the Apple ProRes profile.    
//
enum EMvProResProfile
{
   keMvProResProfileInvalid,              // Invalid value.
   keMvProResProfile422,                  // Indicates that the profile is Apple ProRes 422.
   keMvProResProfile422HQ,                // Indicates that the profile is Apple ProRes 422 (HQ).
   keMvProResProfile422LT,                // Indicates that the profile is Apple ProRes 422 (LT).
   keMvProResProfile422Proxy,             // Indicates that the profile is Apple ProRes 422 (Proxy).
   keMvProResProfile4444,                 // Indicates that the profile is Apple ProRes 4444.
   keMvProResProfileLast                  // End of list indicator.
};

//
// Summary:
// This macro is used to get the string corresponding to the EMvAVCIntraProfile enum value.
//
#define MV_PRORES_PROFILE_ENUM_TO_STRING(eMvProResProfile) \
   ((eMvProResProfile == keMvProResProfileInvalid) ? ("Invalid") : \
   (eMvProResProfile == keMvProResProfile422) ? ("ProRes422") : \
   (eMvProResProfile == keMvProResProfile422HQ) ? ("ProRes422HQ") : \
   (eMvProResProfile == keMvProResProfile422LT) ? ("ProRes422LT") : \
   (eMvProResProfile == keMvProResProfile422Proxy) ? ("ProRes422Proxy") : \
   (eMvProResProfile == keMvProResProfile4444) ? ("ProRes4444") : \
   (eMvProResProfile == keMvProResProfileLast) ? ("Last") : \
   ("???"))


//
// Summary:
//    Specifies the Avid DNxHD profile.    
//
enum EMvDNxHDProfile
{
   keMvDNxHDProfileInvalid,              // Invalid value.
   keMvDNxHDProfile36,                   // Indicates that the Avid DNxHD profile is 36.
   keMvDNxHDProfile145,                  // Indicates that the Avid DNxHD profile is 145.
   keMvDNxHDProfile220,                  // Indicates that the Avid DNxHD profile is 220, 8-bit. 
   keMvDNxHDProfile220x,                 // Indicates that the Avid DNxHD profile is 220, 10-bit.
   keMvDNxHDProfileLast                  // End of list indicator.
};

// Summary:
// This macro is used to get the string corresponding to the EMvAVCIntraProfile enum value.
//
#define MV_DNXHD_PROFILE_ENUM_TO_STRING(eMvDNxHDProfile) \
   ((eMvDNxHDProfile == keMvDNxHDProfileInvalid) ? ("Invalid") : \
    (eMvDNxHDProfile == keMvDNxHDProfile36)  ? ("DNxHD36") : \
    (eMvDNxHDProfile == keMvDNxHDProfile145) ? ("DNxHD145") : \
    (eMvDNxHDProfile == keMvDNxHDProfile220) ? ("DNxHD220") : \
    (eMvDNxHDProfile == keMvDNxHDProfile220x) ? ("DNxHD220x") : \
    (eMvDNxHDProfile == keMvDNxHDProfileLast)? ("Last") : \
    ("???"))


//
// Summary:
//    Specifies the MPEG-4 SStP profile.    
//
enum EMvMPEG4SStPProfile
{
   keMvMPEG4SStPProfileInvalid,              // Invalid value.
   keMvMPEG4SStPProfile422LT,                // Indicates that the MPEG-4 SStP profile is 4:2:2 Lite.
   keMvMPEG4SStPProfile422SQ,                // Indicates that the MPEG-4 SStP profile is 4:2:2 SQ.
   keMvMPEG4SStPProfile444SQ,                // Indicates that the MPEG-4 SStP profile is 4:4:4 SQ. (Not supported yet.)
   keMvMPEG4SStPProfile444HQ,                // Indicates that the MPEG-4 SStP profile is 4:4:4 HQ. (Not supported yet.)
   keMvMPEG4SStPProfileLast                  // End of list indicator.
};

// Summary:
// This macro is used to get the string corresponding to the EMvMPEG4SStPProfile enum value.
//
#define MV_MPEG4SStP_PROFILE_ENUM_TO_STRING(eMvMPEG4SStPProfile) \
   ((eMvMPEG4SStPProfile == keMvMPEG4SStPProfileInvalid) ? ("Invalid") : \
   (eMvMPEG4SStPProfile == keMvMPEG4SStPProfile422LT)  ? ("MPEG-4 SStP 4:2:2 Lite") : \
   (eMvMPEG4SStPProfile == keMvMPEG4SStPProfile422SQ)  ? ("MPEG-4 SStP 4:2:2 SQ") : \
   (eMvMPEG4SStPProfile == keMvMPEG4SStPProfile444SQ)  ? ("MPEG-4 SStP 4:4:4 SQ") : \
   (eMvMPEG4SStPProfile == keMvMPEG4SStPProfile444HQ)  ? ("MPEG-4 SStP 4:4:4 HQ") : \
   (eMvMPEG4SStPProfile == keMvMPEG4SStPProfileLast)? ("Last") : \
   ("???"))

//
// Summary:
//    Specifies the encoding scan mode.
enum EMvEncodingScanMode
{
   keMvEncodingScanModeInvalid,      // Not initialized.  Invalid value.
   keMvEncodingScanModeFrame,        // Encoding will be done in frames.
   keMvEncodingScanModeFields,        // Encoding will be done in fields.
   keMvEncodingScanModeMixed,        // Encoding will be done in frames and fields.
   keMvEncodingScanModeLast          // End of list indicator.
};

// This macro is used to get the string corresponding to the EMvEncodingScanMode enum value.
#define MV_ENCODING_SCAN_MODE_ENUM_TO_STRING(eMvEncodingScanMode) \
   ((eMvEncodingScanMode == keMvEncodingScanModeInvalid) ? ("Invalid") : \
   (eMvEncodingScanMode == keMvEncodingScanModeFrame)    ? ("Frame") : \
   (eMvEncodingScanMode == keMvEncodingScanModeFields)   ? ("Fields") : \
   (eMvEncodingScanMode == keMvEncodingScanModeMixed)    ? ("Mixed") : \
   (eMvEncodingScanMode == keMvEncodingScanModeLast)     ? ("Last") : \
   ("???"))

//
// Summary:
//    Specifies the Matrox AVC-Intra profile.    
//
enum EMvAVCIntraProfile
{
   keMvAVCIntraProfileInvalid,               // Invalid value.
   keMvAVCIntraProfileClass50,               // Indicates that the Matrox AVC-Intra profile is Class 50.
   keMvAVCIntraProfileClass100,              // Indicates that the Matrox AVC-Intra profile is Class 100.
   keMvAVCIntraProfileLast                   // End of list indicator.
};

//
// Summary:
// This macro is used to get the string corresponding to EMvAVCIntraProfile enum value.
//
#define MV_AVCINTRA_PROFILE_ENUM_TO_STRING(eMvAVCIntraProfile) \
   ((eMvAVCIntraProfile == keMvAVCIntraProfileInvalid) ? ("Invalid") : \
   (eMvAVCIntraProfile == keMvAVCIntraProfileClass50) ? ("AVCIntra Class50") : \
   (eMvAVCIntraProfile == keMvAVCIntraProfileClass100) ? ("AVCIntra Class100") : \
   (eMvAVCIntraProfile == keMvAVCIntraProfileLast) ? ("Last") : \
   ("???"))

////////////////////////////////////////////////////////////////////////////

//
// Summary:
//    Describes the input and output surfaces for the codecs.
// 
struct SMvCodecIOFormats
{
   uint32_t        	size;                // Size of the structure in bytes. 
   EMvSurfaceFormat  eSupportedFormat;    // Specifies the uncompressed supported surface format.
   unsigned long     ulComponentBitCount; // Indicates the number of bits per component.
};

//
// Summary:
//    Describes the various resolutions that a codec can handle.
// 
struct SMvCodecResolutions
{
   uint32_t        	size;       // Size of the structure in bytes.
   unsigned long     ulWidth;    // Width of the resolution supported.
   unsigned long     ulHeight;   // Height of the resolution supported.
};

//
// Summary:
//    Describes the capabilities obtained from the software codecs.
// 
struct SMvCodecCapabilities
{
   uint32_t            size;                                // Size of the structure in bytes.
   EMvSurfaceFormat    eCodecSurfaceFormat;                 // Surface format of the compressed data supported.  All of the capabilities reported are for this surface type.
   SMvCodecIOFormats   saSupportedCompressionInputFormat[kulMaxValueCompressionInputFormat];       // Array of structures of the various uncompressed format supported at the
                                                                                                      // input for compression.  Currently only 8-bit YUV 4:2:2 is supported.
   SMvCodecIOFormats   saSupportedDecompressionOutputFormat[kulMaxValueDecompressionOutputFormat]; // Array of structures of the various uncompressed format supported at the output 
                                                                                                      // for decompression.  Currently only 8-bit YUV 4:2:2 is supported.
   SMvCodecResolutions saCodecResolutionSupported[kulMaxValueResolution];  // Array of structures of the various resolutions that the surface format supports.
                                                                              // It could be 720x480, 720x486, 720x576, 1280x720, 1920x1080, or other.
                                                                              // This is useful to determine if a codec supports HD or not.
   unsigned long       ulNbCompressionInputSupported;       // Number of valid structures in the array saSupportedCompressionInputFormat.
   unsigned long       ulNbDecompressionOutputSupported;    // Number of valid structures in the array saSupportedDecompressionOutputFormat.
   unsigned long       ulNbResolutionSupported;             // Number of valid structures in the array saCodecResolutionSupported.
   unsigned long       ulMultipleInBytesForPitch;           // Indicates the multiple of bytes the pitch should be when using USER buffers.
   unsigned long       ulMinBitRateInBitsPerSec;            // Minimum bit rate expressed in bits per second. For example, the MPEG-2 4:2:2 Profile @ <b> Main Level </b>
                                                               // minimum bit rate is 10000000 bits per second. This is the minimum bit rate that you can program 
                                                               // in the codec at the compression time.
   unsigned long       ulMaxBitRateInBitsPerSec;            // Maximum bit rate expressed in bits per second. For example, the MPEG-2 4:2:2 Profile @ <b> Main Level </b>
                                                               // maximum bit rate is 50000000 bits per second. This is the maximum bit rate that you can program 
                                                               // in the codec at the compression time.
   bool                bIsUpscaletoHDSupported;             // 
   bool                bIsBitRateProgrammable;              // If true, the bit rate is programmable through the IMvCodec::SetCodecOption method.
   bool                bIsCompressionSupported;             // If true, the specified codec can compress data.
   bool                bIsDecompressionSupported;           // If true, the specified codec can decompress data.
   bool                bIsEmbeddedColorCorrectionSupported; // If true, indicated that embedded color correction is supported. Color correction effect settings can be sent to the codec. 
   bool                bIsCBRSupported;                     // If true, indicates that Constant Bit Rate encoding is supported.
   bool                bIsVBRSupported;                     // If true, indicates that Variable Bit Rate encoding is supported. 
   bool                bIsCCDecodeSupported;                // If true, indicates that closed caption decoding is supported for backward compatibility.
   bool                bIsCCEncodeSupported;                // If true, indicates that closed caption encoding is supported for backward compatibility.
};

//
// Summary:
//    Contains the calculated VU meter result and Peak meter result for a mono channel of an audio buffer.
//    Refer to the IMvVuMeter interface.
//
struct SMvAudioVuMeterValueMono
{
   uint32_t size;          // Structure size in bytes. Should be set by the application before calling the VU meter.
   float    fVuResult;     // VU meter result. Calculated according to ANSI S1.4 "Specification for Sound Level 
                              // Meters". The unit is dBFS (dB Full Scale). The maximum value is 0 dBFS (full scale).
                              // Any value below full scale is negative (-3 dBFS means 3 dB below full scale).
   float    fPeakResult;   // Peak result. Returns the amplitude of the loudest sample in the buffer. The unit is
                              // dBFS (dB Full Scale). The maximum value is 0 dBFS (full scale). Any value below 
                              // full scale is negative (-3 dBFS means 3 dB below full scale).
   bool     bClipped;      // If any sample in the buffer has reached the full scale, then this flag is set to true.  By default it's false.
};

//
// Summary:
//    Contains the calculated VU meter result and Peak meter result for a stereo audio buffer. 
//    Refer to the IMvVuMeter interface.
//
struct SMvAudioVuMeterValueStereo
{
   uint32_t                 size;            // Structure size in bytes. Should be set by the application before calling the VU meter.
   SMvAudioVuMeterValueMono sVuResultLeft;   // VU meter results, left channel.
   SMvAudioVuMeterValueMono sVuResultRight;  // VU meter results, right channel.
};

//
// Summary:
//    Specifies the type of pulldown sequence. 
//
enum EMvPullDownSequence
{
   keSequence_Invalid =0,  // Invalid value.
   keSequence_3_2,         // Normal pulldown sequence.
   keSequence_Advanced,    // Advanced pulldown sequence.
   keSequence_720_30M,     // 720p30M 1:2 output sequence.
   keSequence_720_24M,     // 720p24M 2:3 output sequence.
   keSequence_720_50,      // 720p50 output sequence.
   keSequence_720_25,      // 720p25 output sequence.
   keSequence_Last         // End of list indicator.
};


//
// Summary:
//    Indicates the 3:2 pulldown sequence of telecine material.
//
enum EMvFrameOfSequence
{
   keFrame_Invalid=0,   // Invalid value.
   keFrame_1st,         // A Frame.
   keFrame_2nd,         // B Frame.
   keFrame_3rd,         // X Frame.
   keFrame_4th,         // C Frame.
   keFrame_5th,         // D Frame.
   keFrame_Last         // End of list indicator.
};

//
// Summary:
//    Indicates the 720p Active Frame flag.
//
enum EMvDvcproHD720pActiveFrameFlag
{
   keKeepFrame_Invalid=0,  // Invalid value.
   keKeepFrameNone,        // Keep no frames.
   keKeepFrameFirstOnly,   // Keep first frame only.
   keKeepFrameSecondOnly,  // Keep second frame only.
   keKeepFrameBoth,        // Keep both frames.
   keKeepFrame_Last        // End of list indicator.
};

//
// Summary:
//    Describes the Flex Clip Reader open command parameter.
//
struct SMvFlexClipReaderOpen
{
   uint32_t size;                     // Structure size in bytes.
   wchar_t awchFileName[MAX_PATH];  // Filename to open by the Clip Reader.
};


//
// Summary:
//    Describes Flex file infomation parameters for truncation position checking.
//
struct SMvFlexPositionsInquiry
{
   uint32_t size;                      // Structure size in bytes.
   uint64_t ui64PosToCheck;            // Input frame location.
   uint64_t ui64PosReturned1;          // Output frame location 1.
   uint64_t ui64PosReturned2;          // Output frame location 2.
};


//
// Summary:
//    Describes the Flex Clip Reader read command parameter.
// Remarks:
// - There may be more than one read command for a given position.
// - Each command can have a different 
//   video or audio ID.
//
struct SMvFlexClipReaderReadCommand
{
   uint32_t size;                           // Structure size in bytes.

   uint64_t ui64ReadBeginPositionInFrames;         // First video frame to read.
   uint64_t ui64ReadEndPositionInclusiveInFrames;  // Last video frame to read.
   uint64_t ui64ReadBeginPositionInSamples;        // First audio sample to read.
   uint64_t ui64ReadEndPositionInclusiveInSamples; // Last audio sample to read.

   bool bReadVideo;                       // Video stream is to be read.
   bool bReadAudio;                       // Audio stream is to be read.
   bool bReadVBI;                         // VBI stream is to be read.
   
   unsigned long  ulVideoStreamToRead;    // Specifies which video stream to read.
   unsigned long  ulAudioStreamToRead;    // Specifies which audio stream to read.
   unsigned long  ulVBIStreamToRead;      // Specifies which VBI stream to read.

   IMvSurface* apIVideoSurfaces[kusFlexClipReaderMaxNumberOfFramesPerReadCommand];  // List of 
                  // uncompressed surfaces - each array member points to another array of video 
                  // surfaces. There must be enough surfaces in here to satisfy the entire read task.

   IMvAudioSamples* pIAudioSamples;    // List of uncompressed audio samples - each audio samples 
                                          // buffer has to be large enough for the entire read task. 
                                          // Once it's signaled, it's the caller's responsibility to 
                                          // split it across each frame.

   IMvSurface* apIVBISurfaces[kusFlexClipReaderMaxNumberOfFramesPerReadCommand];    // List of 
                  // uncompressed VBI surfaces - each array member points to another array of VBI 
                  // surfaces. There must be enough surfaces in here to satisfy the entire read task.

   bool bProcessedVbi;  // Flag that must be set to true by the Clip Reader if bReadVBI is set to true
                        // and the Clip Reader supports VBI. Clips that do not support VBI
                        // don't have to do anything with this flag, since it is false by default.

   bool              bUseIndividualAudioStream; // If set to true, the allocated audio sample buffers are 
                                                // in the apIAudioSamples instead of pIAudioSamples

   IMvAudioSamples * apIAudioSamples[kusFlexClipReaderMaxNumberOfAudioInStream];    // For the support of unmatched audio tracks. For readers that can 
                                          // supply seperated audio stream info. Each entry corresponds to the
                                          // individual stream of audio. Superceeding the pIAudioSamples which 
                                          // contains all the multiplexed tracks of audio in one single stream.
                                          // List of uncompressed audio samples - each audio samples 
                                          // buffer has to be large enough for the entire read task. 
                                          // Once it's signaled, it's the caller's responsibility to 
                                          // split it across each frame.

};

//
// Summary:
//	  Specifies which filler key to use when capturing to an MXF file.
//
enum EMvClipOptionMxfFillLabel
{
   keMvClipOptionMxfFillLabelInvalid,  // Invalid value.
   keMvClipOptionMxfFillLabel2002,     // Indicates that the MXF fill label uses the old RP210 version number.
   keMvClipOptionMxfFillLabel2004,     // Indicates that the MXF fill label uses the correct RP210 version number.
   keMvClipOptionMxfFillLabelLast      // End of list indicator.
};

//
// Summary:
//	  Specifies the track to which the closed caption track information is to be saved when capturing to an MOV or MP4 file.
//
enum EMvClipOptionMOVVANCTrackOption
{
   keMvClipOptionMOVVANCTrackOptionInvalid,	// Invalid value.
   keMvClipOptionMOVVANCTrackOptionC608,	   // Indicates that the closed caption information is to be saved to a CEA-608 track in the file.
   keMvClipOptionMOVVANCTrackOptionC708,	   // Indicates that the closed caption information is to be saved to a CEA-708 track in the file.
   keMvClipOptionMOVVANCTrackOptionLast		// End of list indicator.
};


//
// Summary: 
//	  This structure is passed to the IMvFlexMpegClipReader::Open method and is used to generate MPEG-2 
//	  IBP index files. It contains an index file name for video and an index file name for audio.
// Remarks:
// - Index file generation may not be realtime, and should be performed offline prior to playing back the source MPEG-2 file.
// - Once generated, index files can be re-used to speed up subsequent access to the source MPEG-2 file. To do this, the caller 
//	 must keep track of the file names specified by the video and audio parameters.  
//
struct SMvFlexMpegClipReaderOpen
{
   uint32_t size;

   bool bRecreateIndexFiles;					// Specifies whether or not to generate index files when IMvFlexMpegClipReader::Open is called.

   wchar_t awchIndexFileNameVideo[MAX_PATH];	// Specifies an index file name for video. If NULL, no index file is generated/re-used.
   wchar_t awchIndexFileNameAudio[MAX_PATH];	// Specifies an index file name for audio. If NULL, no index file is generated/re-used.

   IMvInformationCallback *pIMvInformationCallback;
};

//
// Summary:
//	  Structure that is passed to the Flex File Writer when capturing video and audio material to Panasonic P2 <I>.mxf</I> files 
//    (one video <I>.mxf</I> file and two or more associated mono audio <I>.mxf</I> files).
// Description:
//	  In Matrox DSX, when capturing Panasonic P2 material to <I>.mxf</I> files, separate Flex File Writers are used for each video 
//	  and audio track captured. Because each instance of the Flex File Writer is independent of the other, information will be 
//	  missing when capturing P2 clips with one video track and multiple mono audio tracks. This structure must be passed to the Flex 
//	  File Writer to add the missing information, and ensure compatibility with most Panasonic P2 devices and applications.
// Remarks:
// - When capturing material to a P2 <I>.mxf</I> file, use the method IMvFlexWriter::SetClipOption 
//   to pass the structure SMvFlexWriterMxfP2CaptureExtraInfo to the Flex File Writer. Make sure to set the parameter ulTotalAudioTrackNums to 2, 4, or 8, 
//   ulSamplesPerSec to 48000, and the parameter ulAudioTrackId to 1 or 2 (if ulTotalAudioTrackNums is set to 2), 1, 2, 3, or 4 (if ulTotalAudioTrackNums is set to 4), 
//   or 1, 2, 3, 4, 5, 6, 7, or 8 (if ulTotalAudioTrackNums is set to 8). To create the 16-byte GUIDs, use the Windows <i><b>CoCreateGuid()</b></i> method.
//
struct SMvFlexWriterMxfP2CaptureExtraInfo
{
   uint32_t size;                         // Structure size in bytes.

   unsigned long ulTotalAudioTrackNums;   // Specifies the total number of mono audio tracks to be captured. Currently the maximum value is 8.
   unsigned long ulSamplesPerSec;			// Specifies the sampling rate (samples per second) for the capture.
   unsigned long ulAudioTrackId;			   // Specifies the ID of the audio track to be captured.

   GUID guidMaterialPackageUID;           // Specifies the 16-byte UID of the Material Package.
   GUID aguidSourcePackageUID[33];        // Specifies the 16-byte UID for the video and audio of the Source Package in an array containing elements that are defined as follows:
                                          // <p> [0] for video. <p> [1] and [2] for two audio tracks. <p> [1], [2], [3], and [4] for four audio tracks. <p> [1], [2], ... , [8] for eight audio tracks.
};

//////////////////////////////////////////////////////////////////////////
//
// DSX.SDK Media Reader / Writer definitions
//
//////////////////////////////////////////////////////////////////////////

//
// Summary:
//    Specifies the Flex Media Reader/Writer track type.
//
// Remarks:
//    - The Flex Media Reader/Writer supports elementary video tracks or elementary audio tracks.
//
enum EMvMediaTrackType
{
   eMediaTrackTypeUnknown,
   eMediaTrackTypeVideo,
   eMediaTrackTypeAudio
};

//////////////////////////////////////////////////////////////////////////

//
// Summary:
//    Specifies the Flex Media Reader/Writer audio endianess.
//
// Remarks:
//    - The audio is big or little endian, or if not a known type will be set to unknown.
//
enum EMvAudioEndianType
{
   eAudioEndianUnknown,
   eAudioEndianBig,
   eAudioEndianLittle
};

enum  EMvAudioEssenceType
{
   keAudioInvalid = 0,
   keAudioGCSound,
   keAudioWave,
   keAudioAES3,
   keAudioAIFF,
   keAudioAAC,
   keAudioLast
};

//
// Summary:
//    Describes the Flex Media Reader/Writer audio buffer format.
//
// Remarks:
//    - Describes individual tracks. Tracks must contain a constant buffer description across the length of the track.
//    - ui32BitsPerSample will be set to 32-bit when capturing Matrox 24-bit in a 32-bit buffer PCM audio. The application 
//       can use the 24 MSB when playing back this buffer type using Matrox hardware.
//
struct SMvAudioMediaDescription
{
   uint32_t size;                   // Structure size in bytes. 
   uint32_t ui32SamplesPerSecond;   // Sample rate, in samples per second (hertz). 
   uint32_t ui32BytesPerPacket;     // In uncompressed audio a packet is equal to one sample size. 
                                    // In compressed audio a packet is made of indivisible compressed data.
   uint32_t ui32SamplesPerPacket;   // The number of samples in each packet. 
                                    // 1 for uncompressed, >= 1 for compressed (ex: 1024 for AAC).
   uint32_t ui32ChannelsPerSample;  // Type of channel for example, mono, stereo etc. 
   uint32_t ui32BitsPerSample;      // Bits per sample for the format type. This is the container 
                                    // size of the data if the actual data size is different from
                                    // the container size. This field must be equal or larger than 
                                    // the ulValidBitsPerSample. 
   EMvAudioDataType     eAudioDataType;   // Matrox audio data type. Set to keAudioDataTypeInvalid if audio type is not Matrox-compatible.
   EMvAudioEndianType   eAudioEndianType; // Audio endian type. Set to eAudioEndianBig or eAudioEndianLittle if MediaReader can determine the type, otherwise eAudioEndianUnknown
};

//
// Summary:
//    Contains the audio and video information of a track inside a media file.
//
// Remarks:
//    - This information is relevant at the track level. 
//
struct SMvMediaClipTrackInfo
{
   uint32_t                   size;                      // Structure size in bytes.
   EMvMediaTrackType          eTrackType;                // Specifies if this is a video or audio track property.
   uint32_t                   ui32TrackID;               // Specifies the video track index associated with this description.
   uint32_t                   ui32DataFormatFourcc;      // Data format fourcc. Media Writer: a value of 0 means the media writer will attempt to determine
                                                         // the fourcc based on the Matrox surface format.
   uint32_t                   ui32VendorFourcc;          // Vendor fourcc. Media Writer: a value of 0 means the media writer will set the vendor id to Matrox.
   wchar_t                    awchDescription[MAX_PATH]; // String description associated with the track.
   uint64_t                   ui64SampleCount;           // Specifies the number of samples (video or audio) contained in the current track. Media Writer: set to 0.
   SMvAudioMediaDescription   sAudioMediaDesc;           // Specifies the audio information. Valid when referencing an audio track.
   SMvResolutionInfo          sVideoResolution;          // Specifies the track's video resolution. Valid when referencing a video track.
   EMvColorimetry             eVideoColorimetry;         // Specifies the video colorimetry standard. Valid when referencing a video track.
   EMvSurfaceFormat           eVideoFormat;              // Matrox video compression type if applicable. If the compression type is not recognized by Matrox,
                                                         // this field will be set to keMvSurfaceFormatFlexAVClip. Valid when referencing a video track.
   bool                       bHasDependencyIndex;       // For capture only, will enable Sync Box, dependency box. Set to false by default.
   bool                       bHasCompositionTimeIndex;  // For capture only, will enable composition time box. Set to false by default.
   bool                       bHasSampleSizeIndex;       // For capture only, will enable sample size box. Set to false by default.
   char                       achEssenceCodingUID[16];   // Used for MXF Essense Descriptor coding UID.
};

//
// Summary:
//    Extended sample description used by the Flex Media Writer.
//
struct SMvSampleDescriptionExtensionProperty
{
   uint32_t          size;             // Structure size in bytes.
   EMvMediaTrackType eTrackType;       // Video, audio.
   uint32_t          ui32TrackID;      // Video track#, audio track#.
   uint32_t          ui32FourccID;     // Description extension type.
   uint8_t*          pui8Buffer;       // Data.
   uint32_t          ui32BufferSize;   // Data size.
};

//
// Summary:
//    structure used for Getting audio track info 
//
struct SMvAudioStreamProperties
{
  uint32_t        size;                   // Structure size in bytes.
  uint32_t        ui32StreamNumber;       // Zero based incrementing stream number corresponding to the track in the file
  uint32_t        ui32TrackBlockAlign;    // Block align, size per sample in bytes
  uint32_t        ui32ValidBitsPerSample; // The actual sampled bit depth 
  uint32_t        ui32BitsPerSample;		// container bit depth 
  uint32_t        ui32ChannelCount;       // Count of number of channel of the current stream
  uint32_t        ui32SamplesPerSec; 
  uint32_t        ui32ChannelIndexStart;	// The channel number (zero based) of the first channel of a stream
  EMvAudioEndianType   eEndianType; 
  EMvAudioEssenceType  eAudioEssenceType; // WAVE/ AIFF / AAC etc

};


//
// Summary:
//    Describes the amount of space that is reserved before the end of the disk is reached (for capture).
//
struct SMvReserveSpaceForEndOfDisk
{
   uint32_t             size;                                     // Indicates the structure size (in bytes).
   SMvResolutionInfo    sResolution;                              // Indicates the resolution information.
   uint64_t             ui64ReserveSpaceForEndOfDiskCheck;        // Indicates the amount of disk space to reserve before the end of the disk is reached.
};


