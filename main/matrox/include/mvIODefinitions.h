///////////////////////////////////////////////////////////////////////////////////
//
//  (c) Copyright Matrox Electronic Systems Ltd., 2001. All rights reserved. 
//
//  This software code is subject to the terms and conditions outlined 
//  in the non-disclosure agreement between Matrox and your company. 
//  By accessing this code or using it in any way, you indicate your 
//  acceptance of such terms and conditions.
//
//  All code and information is provided "as is" without warranty of any kind, 
//  either expressed or implied, including but not limited to the implied 
//  warranties of merchantability and/or fitness for a particular purpose.
//
//  Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make 
//  changes in specifications and code at any time and without notice. 
//  No responsibility is assumed by Matrox Electronic Systems Ltd. for 
//  its use; nor for any infringements of patents or other rights of 
//  third parties resulting from its use. No license is granted under 
//  any patents or patent rights of Matrox Electronic Systems Ltd.
//
//////////////////////////////////////////////////////////////////////////////////

#pragma once 

#include "mvTypes.h"

#ifdef MAC_PLATFORM
namespace com_matrox_vpg_SDK
{
#endif

//*************************************************************************************//
//**                          ENUMERATIONS                                           **//
//*************************************************************************************//

//
// Summary:
//    Describes the resolution's aspect ratio.
//
enum EMvAspectRatio
{
   keMvAspectRatioInvalid, // Invalid value.
   keMvAspectRatio_4_3,    // Indicates that the resolution has an aspect ratio of 4:3.
   keMvAspectRatio_16_9,   // Indicates that the resolution has an aspect ratio of 16:9.
   keMvAspectRatio_2_1,    // Indicates that the resolution has an aspect ratio of 2:1.   
   keMvAspectRatio_256_135,// Indicates that the resolution has an aspect ratio of 256:135.   
   keMvAspectRatioLast     // End of list indicator.
};
// This macro is used to get the string of the enum value eMvAspectRatio
#define MV_ASPECT_RATIO_ENUM_TO_STRING(eMvAspectRatio) \
	((eMvAspectRatio == keMvAspectRatioInvalid) ? ("Invalid") : \
	(eMvAspectRatio == keMvAspectRatio_4_3) ? ("4:3") : \
	(eMvAspectRatio == keMvAspectRatio_16_9) ? ("16:9") : \
   (eMvAspectRatio == keMvAspectRatio_2_1) ? ("2:1") :\
   (eMvAspectRatio == keMvAspectRatio_256_135) ? ("256:135") :\
	(eMvAspectRatio == keMvAspectRatioLast) ? ("Last") : \
	("???"))
#define MV_MXO_ASPECT_RATIO_ENUM_TO_STRING MV_ASPECT_RATIO_ENUM_TO_STRING

//
// Summary:
//    Specifies the pixel aspect ratio.
//
enum EMvPixelAspectRatio
{
   keMvPixelAspectRatioInvalid,           // Invalid value.
   keMvPixelAspectRatioCustom,            // Custom pixel aspect ratio specified by the user.
   keMvPixelAspectRatioSquare,            // Aspect ratio for HD television standards.
   keMvPixelAspectRatio_NTSC_4_3,         // Aspect ratio for 4:3 NTSC.
   keMvPixelAspectRatio_NTSC_16_9,        // Aspect ratio for 16:9 NTSC.
   keMvPixelAspectRatio_PAL_4_3,          // Aspect ratio for 4:3 PAL.
   keMvPixelAspectRatio_PAL_16_9,         // Aspect ratio for 16:9 PAL.
   keMvPixelAspectRatio_960x720_16_9,     // Aspect ratio for DVCPRO HD 720p.
   keMvPixelAspectRatio_1280x1080_16_9,   // Aspect ratio for DVCPRO HD 1080i at 59.94 fps. 
   keMvPixelAspectRatio_1440x1080_16_9,   // Aspect ratio for DVCPRO HD 1080i at 50 fps and HDV.
   keMvPixelAspectRatioLast               // End of list indicator.
};

//
// Summary:
//    Enumerates the audio data types that can be used.
//
enum EMvAudioDataType
{
   keAudioDataTypeInvalid           = 0,  // Invalid value.
   keAudioDataTypePCM               = 1,  // The audio data type is Pulse Code Modulation (PCM).
   keAudioDataTypeIEEEFLoat         = 2,  // The audio data type is an IEEE floating point value.
   keAudioDataTypeMatroxMultiFormat = 3,  // The audio data type is not interpreted and contains raw bits.
   keAudioDataTypeAAC               = 4,  // The audio data type is AAC.
   keAudioDataTypeLast                    // End of list indicator.
};
// This macro is used to get the string of the enum value EMvAudioDataType.
#define MV_AUDIO_DATA_TYPE_ENUM_TO_STRING(eAudioDataType) \
   ((eAudioDataType == keAudioDataTypeInvalid)           ? ("Invalid") : \
   (eAudioDataType == keAudioDataTypePCM)                ? ("PCM") : \
   (eAudioDataType == keAudioDataTypeIEEEFLoat)          ? ("IEEEFLoat") : \
   (eAudioDataType == keAudioDataTypeMatroxMultiFormat)  ? ("MatroxMultiFormat") : \
   (eAudioDataType == keAudioDataTypeAAC)                ? ("AAC") : \
   (eAudioDataType == keAudioDataTypeLast)               ? ("Last") : \
   ("???"))

//
// Summary:
//    Describes the channel type of an audio buffer.
//
enum EMvChannelType
{
   keChannelTypeInvalid	 = 0,    // Invalid value.
   keChannelTypeMono     = 1,    // Mono channel (one channel only).
   keChannelTypeStereo   = 2,    // Stereo channel (two interleaved channels).
   keChannelType1Track   = 1,    // Same as keChannelTypeMono.
   keChannelType2Tracks  = 2,    // Same as keChannelTypeStereo.
   keChannelType4Tracks  = 4,    // Four interleaved audio tracks.
   keChannelType6Tracks  = 6,    // Six interleaved audio tracks. Added for AES/EBU and embbeded audio mixed capture.
   keChannelType8Tracks  = 8,    // Eight interleaved audio tracks.
   keChannelType10Tracks = 10,   // Ten interleaved audio tracks. Added for AES/EBU and embbeded audio mixed capture.
   keChannelType12Tracks = 12,   // Twelve interleaved audio tracks. Added for AES/EBU and embbeded audio mixed capture.
   keChannelType14Tracks = 14,   // Fourteen interleaved audio tracks. Added for AES/EBU and embbeded audio mixed capture.
   keChannelType16Tracks = 16,   // Sixteen interleaved audio tracks.
   keChannelType32Tracks = 32,   // Thirty two interleaved audio tracks.
   keChannelTypeLast             // End of list indicator.
};

//
// Summary:
//    Specifies the colorimetry standard of a surface.
//
enum EMvColorimetry
{
   keMvColorimetryInvalid,       // Invalid value.
   keMvColorimetryITUR_BT_601,   // Indicates that the colorimetry standard is ITUR-BT-601.
                                    // This is the standard used for SD (standard definition) video
                                    // resolutions.
   keMvColorimetryITUR_BT_709,   // Indicates that the colorimetry standard is ITUR-BT-709.
                                    // This is the standard used for HD (high definition) video
                                    // resolutions.
   keMvColorimetryLast           // End of list indicator.
};
// This macro is used to get the string of the enum value EMvColorimetry
#define MV_COLORIMETRY_ENUM_TO_STRING(eColorimetry) \
   ((eColorimetry == keMvColorimetryInvalid)    ? ("Invalid") : \
   (eColorimetry == keMvColorimetryITUR_BT_601) ? ("ITUR_BT_601") : \
   (eColorimetry == keMvColorimetryITUR_BT_709) ? ("ITUR_BT_709") : \
   (eColorimetry == keMvColorimetryLast)        ? ("Last") : \
   ("???"))

//
// Summary:
//    Describes the face types of a cube surface.
//
enum EMvFaceType
{
   keMvFaceTypeInvalid             = 0x00000000,   // Invalid value.
   keMvFaceTypeFront	              = 0x00000001,   // Front face of cube surface. This is the only 
                                                      // face type that is valid for 2D and 3D 
                                                      // surfaces.
   keMvFaceTypeBack                = 0x00000002,   // Back face of cube surface. 
   keMvFaceTypeLeft                = 0x00000003,   // Left face of cube surface.
   keMvFaceTypeRight               = 0x00000004,   // Right face of cube surface.
   keMvFaceTypeBottom              = 0x00000005,   // Bottom face of cube surface.
   keMvFaceTypeTop                 = 0x00000006,   // Top face of cube surface. 
   keMvFaceTypeLast		           = 0x00000007,   // End of list indicator.
   keMvCopyEngineIDForceDWord      = 0x7FFFFFFF    // Forces the enumerated values to 32 bits.
};

//
// Summary:
//    Describes the number of frames per second.
//
enum EMvFrameRate
{
   keMvFrameRateInvalid,   // Invalid value.
   keMvFrameRate24,        // Indicates that the frame rate is 24 frames per second.
   keMvFrameRate24M,       // Indicates that the frame rate is 23.98 frames per second (24/1.001).
   keMvFrameRate25,        // Indicates that the frame rate is 25 frames per second.
   keMvFrameRate30,        // Indicates that the frame rate is 30 frames per second.
   keMvFrameRate30M,       // Indicates that the frame rate is 29.97 frames per second (30/1.001).
   keMvFrameRate50,        // Indicates that the frame rate is 50 frames per second.
   keMvFrameRate60,        // Indicates that the frame rate is 60 frames per second.
   keMvFrameRate60M,       // Indicates that the frame rate is 59.94 frames per second (60/1.001).
   keMvFrameRateVariable,  // Indicates that the frame rate is variable. This flag is only valid for
                              // the input resolution and enables the Varicam frame detection 
                              // circuit.
   keMvFrameRateLast	      // End of list indicator.
};
// This macro is used to get the string of the enum value eMvFrameRate.
#define MV_FRAME_RATE_ENUM_TO_STRING(eMvFrameRate) \
	((eMvFrameRate == keMvFrameRateInvalid) ? ("Invalid") : \
	(eMvFrameRate == keMvFrameRate24) ? ("24") : \
	(eMvFrameRate == keMvFrameRate24M) ? ("23.98") : \
	(eMvFrameRate == keMvFrameRate25) ? ("25") : \
	(eMvFrameRate == keMvFrameRate30) ? ("30") : \
	(eMvFrameRate == keMvFrameRate30M) ? ("29.97") : \
	(eMvFrameRate == keMvFrameRate50) ? ("50") : \
	(eMvFrameRate == keMvFrameRate60) ? ("60") : \
	(eMvFrameRate == keMvFrameRate60M) ? ("59.94") : \
	(eMvFrameRate == keMvFrameRateVariable) ? ("Variable") : \
	(eMvFrameRate == keMvFrameRateLast) ? ("Last") : \
	("???"))
#define MV_MXO_FRAME_RATE_ENUM_TO_STRING MV_FRAME_RATE_ENUM_TO_STRING

//
// Summary:
//    Indicates the different hardware profile types.
//    <B>WARNING!</B> When adding a profile, add it at the <B>end</B> of the table, just before keMvHardwareProfileLast.
//
enum EMvHardwareProfile
{
   keMvHardwareProfileInvalid        = 0x00000000,   // Invalid value.
   keMvHardwareProfileSoftwareOnly   = 0x00000001,   // Only the software services are provided.
   keMvHardwareProfileDSX1000        = 0x00000002,   // X.io card and X.effects card.
   keMvHardwareProfileDSX1000IO      = 0x00000003,   // X.io card only.
   keMvHardwareProfileDSX1000FX      = 0x00000004,   // X.effects card only.
   keMvHardwareProfileDSXmio         = 0x00000005,   // X.mio2 card only.
   keMvHardwareProfileDSXmiofx       = 0x00000006,   // X.mio2 card and X.effects card.
   keMvHardwareProfileHelper         = 0x00000007,   // Only the helper services are provided.
   keMvHardwareProfileDSX1000DX      = 0x00000008,   // X.io card and GPU FX card.
   keMvHardwareProfileDSXmioDX       = 0x00000009,   // X.mio2 card and GPU FX card.
   keMvHardwareProfileDSXle          = 0x0000000A,   // DSX LE card only.
   keMvHardwareProfileDXBoardOnly    = 0x0000000B,   // GPU FX card only.
   keMvHardwareProfileDSXleDX        = 0x0000000C,   // DSX LE card and GPU FX card.
   keMvHardwareProfileDSXopen        = 0x0000000D,   // X.open card only.
   keMvHardwareProfileDSXopenDX      = 0x0000000E,   // X.open card and GPU FX card.
   keMvHardwareProfileDSXopenfx      = 0x0000000F,   // X.open card and X.effects card.
   keMvHardwareProfileRTX2           = 0x00000010,   // RT.X2 card only.
   keMvHardwareProfileRTX2DX         = 0x00000011,   // RT.X2 card and GPU FX card.
   keMvHardwareProfileDSXsd          = 0x00000012,   // DSX.SD card only.
   keMvHardwareProfileDSXsdDX        = 0x00000013,   // DSX.SD card and GPU FX card. 
   keMvHardwareProfileMXO            = 0x00000014,   // MXO external box. This profile is only for FlexChannelTester.  It doesn't have any output channel.
   keMvHardwareProfileMXODXwGPUPb    = 0x00000015,   // MXO external box and GPU FX card with GPU playback support.
   keMvHardwareProfileReserved16     = 0x00000016,   // 
   keMvHardwareProfileReserved17     = 0x00000017,   // 
   keMvHardwareProfileDSXlefx        = 0x00000018,   // DSX LE card and X.effects card.
   keMvHardwareProfileDSXmioDXwGPUPb = 0x00000019,   // X.io card and GPU FX card with GPU playback support.
   keMvHardwareProfileMXOwGPUPb      = 0x0000001A,   // MXO external box with GPU playback support.
   keMvHardwareProfileDSXAVCio       = 0x0000001B,   // X.AVCio card only.
   keMvHardwareProfileDSXAVCioDX     = 0x0000001C,   // X.AVCio card and GPU FX card.
   keMvHardwareProfileMXO2           = 0x0000001D,   // MXO2 external box.  
   keMvHardwareProfileMXO2DX         = 0x0000001E,   // MXO2 external box and GPU FX card. 
   keMvHardwareProfileMAX            = 0x0000001F,   // MAX card only.
   keMvHardwareProfileX264           = 0x0000001F,   // X.264 card only.
   keMvHardwareProfileX264io         = 0x00000020,   // X.264io card only.
   keMvHardwareProfileX264ioDX       = 0x00000021,   // X.264io card and GPU FX card.
   keMvHardwareProfileReserved22     = 0x00000022,   // 
   keMvHardwareProfileX264ioASI      = 0x00000023,   // X.264io/ASI card only.
   keMvHardwareProfileDSXmio2plus    = 0x00000024,   // X.mio2 Plus card only.
   keMvHardwareProfileDSXle3         = 0x00000025,   // DSX LE3 card only.
   keMvHardwareProfileDSXle3DX       = 0x00000026,   // DSX LE3 card and GPU FX card.
   keMvHardwareProfileMAXDX          = 0x00000027,   // X264 card and GPU FX card.
   keMvHardwareProfileDSXmio3        = 0x00000028,   // X.mio3 card.
   keMvHardwareProfileDSXLE4         = 0x00000029,   // DSX LE4 card.
   keMvHardwareProfileDSXCore        = 0x0000002A,   // 
   keMvHardwareProfileM264           = 0x0000002B,   // M264 card
   keMvHardwareProfileLast,                          // End of list indicator.
   keMvHardwareProfileForceDWord     = 0x7FFFFFFF    // Forces the enumerated values to be 32 bits.
};
// This macro is used to get the string of the enum value EMvColorimetry
#define MV_HARDWARE_PROFILE_ENUM_TO_STRING(eHWProfile) \
   (eHWProfile == keMvHardwareProfileInvalid          ? ("Invalid") : \
   (eHWProfile == keMvHardwareProfileSoftwareOnly)    ? ("Software") : \
   (eHWProfile == keMvHardwareProfileDSX1000)         ? ("DS.X1000") : \
   (eHWProfile == keMvHardwareProfileDSX1000IO)       ? ("DS.X1000 IO") : \
   (eHWProfile == keMvHardwareProfileDSX1000FX)       ? ("DS.X1000 Fx") : \
   (eHWProfile == keMvHardwareProfileDSXmio)          ? ("DS.Xmio") : \
   (eHWProfile == keMvHardwareProfileDSXmiofx)        ? ("DS.Xmio FX") : \
   (eHWProfile == keMvHardwareProfileHelper)          ? ("Helper") : \
   (eHWProfile == keMvHardwareProfileDSX1000DX)       ? ("DS.X1000 DX") : \
   (eHWProfile == keMvHardwareProfileDSXmioDX)        ? ("DS.Xmio DX") : \
   (eHWProfile == keMvHardwareProfileDSXle)           ? ("DS.Xle") : \
   (eHWProfile == keMvHardwareProfileDXBoardOnly)     ? ("DX Board Only") : \
   (eHWProfile == keMvHardwareProfileDSXleDX)         ? ("DS.Xle DX") : \
   (eHWProfile == keMvHardwareProfileDSXopen)         ? ("X.open") : \
   (eHWProfile == keMvHardwareProfileDSXopenDX)       ? ("X.open DX") : \
   (eHWProfile == keMvHardwareProfileDSXopenfx)       ? ("X.open fx") : \
   (eHWProfile == keMvHardwareProfileRTX2)            ? ("RT.X2") : \
   (eHWProfile == keMvHardwareProfileRTX2DX)          ? ("RT.X2 DX") : \
   (eHWProfile == keMvHardwareProfileDSXsd)           ? ("DS.Xsd") : \
   (eHWProfile == keMvHardwareProfileDSXsdDX)         ? ("DS.Xsd DX") : \
   (eHWProfile == keMvHardwareProfileMXO)             ? ("MXO") : \
   (eHWProfile == keMvHardwareProfileMXODXwGPUPb)     ? ("MXO DX with GPUPb") : \
   (eHWProfile == keMvHardwareProfileReserved16)      ? ("X.Key") : \
   (eHWProfile == keMvHardwareProfileReserved17)      ? ("X.Key DX") : \
   (eHWProfile == keMvHardwareProfileDSXlefx)         ? ("DS.Xle FX") : \
   (eHWProfile == keMvHardwareProfileDSXmioDXwGPUPb)  ? ("DS.XMio DX with GPUPb") : \
   (eHWProfile == keMvHardwareProfileMXOwGPUPb)       ? ("MXO with GPUPb") : \
   (eHWProfile == keMvHardwareProfileDSXAVCio)        ? ("DS.XAVCio") : \
   (eHWProfile == keMvHardwareProfileDSXAVCioDX)      ? ("DS.XAVCio DX") : \
   (eHWProfile == keMvHardwareProfileMXO2)            ? ("MXO2") : \
   (eHWProfile == keMvHardwareProfileMXO2DX)          ? ("MXO2 DX") : \
   (eHWProfile == keMvHardwareProfileMAX)             ? ("MAX") : \
   (eHWProfile == keMvHardwareProfileX264)            ? ("X264") : \
   (eHWProfile == keMvHardwareProfileMAXDX)           ? ("MAX DX") : \
   (eHWProfile == keMvHardwareProfileX264io)          ? ("X264io") : \
   (eHWProfile == keMvHardwareProfileX264ioDX)        ? ("X264io DX") : \
   (eHWProfile == keMvHardwareProfileReserved22)      ? ("Reserved") : \
   (eHWProfile == keMvHardwareProfileX264ioASI)       ? ("Reserved") : \
   (eHWProfile == keMvHardwareProfileDSXmio2plus)     ? ("DS.Xmio2 plus") : \
   (eHWProfile == keMvHardwareProfileDSXle3)          ? ("DS.Xle3") : \
   (eHWProfile == keMvHardwareProfileDSXmio3)         ? ("DS.Xmio3") : \
   (eHWProfile == keMvHardwareProfileDSXLE4)          ? ("DS.Xle4") : \
   (eHWProfile == keMvHardwareProfileLast)            ? ("Last") : \
   (eHWProfile == keMvHardwareProfileDSXCore)         ? ("DSXCore") : \
   (eHWProfile == keMvHardwareProfileM264)            ? ("M264") : \
   ("???"))

//
// Summary:
//    Specifies how the image data is stored in the surface and the location of its origin.
//
enum EMvImageOrigin
{
   keMvImageOriginInvalid,    // Invalid value.
   keMvImageOriginTopLeft,    // Indicates that the image data is stored top-down in the surface and
                                 // its origin is the upper left corner. 
   keMvImageOriginBottomLeft, // Indicates that the image data is stored bottom-up in the surface 
                                 // and its origin is the lower left corner.
   keMvImageOriginLast        // End of list indicator.
};

//
// Summary:
//    Specifies the memory location of a surface.
//
enum EMvMemoryLocation
{
   keMvMemoryLocationInvalid,       // Invalid value.
   keMvMemoryLocationHost,          // Indicates that the surface is in the host (system) memory.
   keMvMemoryLocationGraphicIn,     // Indicates that the surface is in the local memory of the  
                                       // graphics engine, and will be used to input video through 
                                       // the Video Input Port (VIP). 
   keMvMemoryLocationGraphicOut,    // Indicates that the surface is in the local memory of the
                                       // graphics engine, and will be used to output video through 
                                       // the Digital Video Output (DVO) port.
   keMvMemoryLocationGraphic,       // Indicates that the surface is in the local memory of the
                                       // graphics engine, and will not be used to input video 
                                       // through the VIP or output video through the DVO port.
   keMvMemoryLocationIOBoard,       // Indicates that the surface is in the local memory of a 
                                       // DSX card with I/O capabilities.
   keMvMemoryLocationUser,          // Indicates that the memory buffer has been allocated by the 
                                       // user, and the surface has been allocated with the method 
                                       // CreateUserDataSurface.
   keMvMemoryLocationHostForGPU,    // Indicates that the surface is in the host (system) memory, but
                                       // can be accessed by the GPU (GPU FX card only).
   keMvMemoryLocationGraphicDXIn,   // Indicates that the surface is in the local memory of the
                                       // graphics engine of the GPU FX card.  This memory will be 
                                       // used to input video to the DSX card.  It can be used as 
                                       // a texture, but not as a render target.
   keMvMemoryLocationGraphicDXOut,  // Indicates that the surface is in the local memory of the
                                       // graphics engine of the GPU FX card.  This memory will be 
                                       // used to output video from the DSX card.  It can be used as 
                                       // a render target and as a texture (but the latter is not 
                                       // recommended).
   keMvMemoryLocationGraphicDX,     // Indicates that the surface is in the local memory of the
                                       // graphics engine of the GPU FX card.  It can be used as a
                                       //  texture and render target.
   keMvMemoryLocationLast           // End of list indicator.
};
// This macro is used to get the string of the enum value EMvMemoryLocation.
#define MV_MEMORY_LOCATION_ENUM_TO_STRING(eMemoryLocation) \
   ((eMemoryLocation == keMvMemoryLocationInvalid)     ? ("Invalid") : \
   (eMemoryLocation == keMvMemoryLocationHost)         ? ("Host") : \
   (eMemoryLocation == keMvMemoryLocationGraphicIn)    ? ("GraphicIn") : \
   (eMemoryLocation == keMvMemoryLocationGraphicOut)   ? ("GraphicOut") : \
   (eMemoryLocation == keMvMemoryLocationGraphic)      ? ("Graphic") : \
   (eMemoryLocation == keMvMemoryLocationIOBoard)      ? ("IOBoard") : \
   (eMemoryLocation == keMvMemoryLocationUser)         ? ("User") : \
   (eMemoryLocation == keMvMemoryLocationHostForGPU)   ? ("HostForGPU") : \
   (eMemoryLocation == keMvMemoryLocationGraphicDXIn)  ? ("GraphicDXIn") : \
   (eMemoryLocation == keMvMemoryLocationGraphicDXOut) ? ("GraphicDXOut") : \
   (eMemoryLocation == keMvMemoryLocationGraphicDX)    ? ("GraphicDX") : \
   (eMemoryLocation == keMvMemoryLocationLast)         ? ("Last") : \
   ("???"))

//
// Summary:
//    Specifies the polarity of a surface. 
//
enum EMvPolarity
{
   keMvPolarityInvalid,                   // Invalid value.
   keMvPolarityFirstField,                // Indicates that the surface is a first field.
   keMvPolaritySecondField,               // Indicates that the surface is a second field.
   keMvPolarityInterlacedFieldsInAFrame,  // Indicates that the surface is a frame containing two interlaced fields.
   keMvPolarityProgressiveFrame,          // Indicates that the surface is a progressive frame.
   keMvPolarityBackToBackFieldsInAFrame,  // Indicates that the surface is a frame containing two back-to-back fields.
   keMvPolarityLast                       // End of list indicator.
};
// This macro is used to get the string of the enum value EMvPolarity.
#define MV_POLARITY_ENUM_TO_STRING(ePolarity) \
   ((ePolarity == keMvPolarityInvalid)                 ? ("Invalid") : \
   (ePolarity == keMvPolarityFirstField)               ? ("FirstField") : \
   (ePolarity == keMvPolaritySecondField)              ? ("SecondField") : \
   (ePolarity == keMvPolarityInterlacedFieldsInAFrame) ? ("InterlacedFieldsInAFrame") : \
   (ePolarity == keMvPolarityProgressiveFrame)         ? ("ProgressiveFrame") : \
   (ePolarity == keMvPolarityBackToBackFieldsInAFrame) ? ("BackToBackFieldsInAFrame") : \
   (ePolarity == keMvPolarityLast)                     ? ("Last") : \
   ("???"))

//
// Summary:
//    Indicates whether the video is interlaced or progressive. 
// Remarks:
//  - For interlaced video, the field containing the top line is also indicated.
//
enum EMvScanMode
{
   keMvScanModeInvalid,                // Invalid value.
   keMvScanModeFirstFieldTop,          // Indicates that the video is interlaced and that the first 
                                          // field contains the top line (for example, PAL video).
   keMvScanModeSecondFieldTop,         // Indicates that the video is interlaced and that the second 
                                          // field contains the top line (for example, NTSC video).
   keMvScanModeProgressive,            // Indicates that the video is progressive (not interlaced).
   keMvScanModeProgressiveSegmented,   // Indicates that the video is PsF (Progressive Segmented Frame).
   keMvScanModeInterlacedFieldsInAFrame,  // Indicates that the video contains two fields that are interlaced into a frame.
   keMvScanModeLast                    // End of list indicator.
};
// This macro is used to get the string of the enum value eMvScanMode.
#define MV_SCAN_MODE_ENUM_TO_STRING(eMvScanMode) \
	((eMvScanMode == keMvScanModeInvalid) ? ("Invalid") : \
	(eMvScanMode == keMvScanModeFirstFieldTop) ? ("First field top line") : \
	(eMvScanMode == keMvScanModeSecondFieldTop) ? ("Second field top line") : \
	(eMvScanMode == keMvScanModeProgressive) ? ("Progressive") : \
   (eMvScanMode == keMvScanModeProgressiveSegmented) ? ("PsF") : \
   (eMvScanMode == keMvScanModeInterlacedFieldsInAFrame) ? ("IFF") : \
	(eMvScanMode == keMvScanModeLast) ? ("Last") : \
	("???"))
#define MV_MXO_SCAN_MODE_ENUM_TO_STRING MV_SCAN_MODE_ENUM_TO_STRING

//
// Summary:
//    Describes the pixel organization of a surface.
//
enum EMvSurfaceFormat
{
   keMvSurfaceFormatInvalid,     // Invalid value.
   keMvSurfaceFormatARGBGraphic, // This type of surface usually holds graphics.  Each pixel is 
                                 // composed of four components in the following order: alpha, red, green, and blue. 
                                 // The bit depth of this surface is 4 x 
                                 // ComponentBitCount. Can be allocated in host and graphics 
                                 // engine memory. Black is 0, white is 255.

   keMvSurfaceFormatRGBGraphic,  // Same as ARGB surface, but without the alpha component. The bit 
                                 // depth of this surface is 3 x ComponentBitCount. Can be 
                                 // allocated in host memory only. Black is 0, white is 255.

   keMvSurfaceFormatARGBVideo,   // This type of surface usually holds graphics. Each pixel is 
                                 // composed of four components in the following order: alpha, red, green, and blue. 
                                 // The bit depth of this surface is 4 x 
                                 // ComponentBitCount. Can be allocated in host and graphics 
                                 // engine memory. Black is 16, white is 235. Can contain super 
                                 // white and/or super black.

   keMvSurfaceFormatRGBVideo,    // Same as ARGB surface, but without the alpha component. The bit 
                                 // depth of this surface is 3 x ComponentBitCount. Can be 
                                 // allocated in host memory only. Black is 16, white is 235.
                                 // Can contain super white and/or super black.

   keMvSurfaceFormatYUYV422,     // Also called YUY2, this type of surface holds video or ancillary data.  
                                 // For each two pixels, the data organization is YU YV. The bit depth of
                                 // this surface is 2 x ComponentBitCount. Can be allocated in 
                                 // host memory, I/O local memory, and graphics engine 
                                 // memory.

   keMvSurfaceFormatYUAYVA4224,  // This type of surface holds video. For each two pixels, the data 
                                 // organization is YUA YVA. The bit depth of this surface is 3 x
                                 // ComponentBitCount. Can be allocated in host memory only.

   keMvSurfaceFormatA,     // This type of surface holds alpha information only. The bit depth of 
                           // this surface is 1 x ComponentBitCount. Can be allocated in host and 
                           // graphics engine memory.

   keMvSurfaceFormatDepthStencil,   // This type of surface holds a Z-buffer and a Stencil-buffer 
                                    // required for some 3D processing. This surface can be 
                                    // allocated only with a ComponentBitCount of 8. Each pixel has
                                    // 24 bits of Z and 8 bits of Stencil. Can be allocated in 
                                    // graphics engine memory only.

   keMvSurfaceFormatDuDv,  // This type of surface is used by the bump mapping (distortion) effects. 

   keMvSurfaceFormatDuDvL, // This type of surface is used by the bump mapping (distortion) effects 
                           // using luminance. 

   keMvSurfaceFormatDvCam_411,   // This type of surface contains NTSC YUV411 video data compressed 
                                 // by a DV codec at 25 Mb/sec. 

   keMvSurfaceFormatDvCam_420,   // This type of surface contains PAL YUV420 video data compressed 
                                 // by a DV codec at 25 Mb/sec.

   keMvSurfaceFormatDvCPro_411,  // This type of surface contains NTSC or PAL YUV411 video data 
                                 // compressed by a DV codec at 25 Mb/sec.

   keMvSurfaceFormatDv50_422,    // This type of surface contains YUV422 video data compressed by a 
                                 // DV codec at 50 Mb/sec.

   keMvSurfaceFormatD12_1080_3to2_422,       // This type of surface contains DV100 data for resolution
                                             // 1080i at 23.98 fps and 29.97 fps (scaling ratio of 2/3).

   keMvSurfaceFormatD12_1080_4to3_422,       // This type of surface contains DV100 data for resolution
                                             // 1080i at 50 fps (scaling ratio of 3/4).

   keMvSurfaceFormatD12_720_4to3_422_Fr1,    // This type of surface contains DV100 data for resolution
                                             // 720p at 23.98 fps, 29.97 fps, and 59.94 fps (scaling ratio
                                             // of 3/4) frame 0, 2, 4, ...

   keMvSurfaceFormatD12_720_4to3_422_Fr2,    // This type of surface contains DV100 data for resolution
                                             // 720p at 23.98 fps, 29.97 fps, and 59.94 fps (scaling ratio
                                             // of 3/4) frame 1, 3, 5, ...

   keMvSurfaceFormatMpegIBPMainProfileMainLevel_420,     // This type of surface contains YUV420 video 
                                                         // data compressed by an MPEG codec. The 
                                                         // surface can be an I, B, or P-frame. The 
                                                         // specific information of this MPEG surface
                                                         // is described by the MPEG_IBP_Specific structure 
                                                         // in the surface description. This surface 
                                                         // supports SD (standard definition) video 
                                                         // resolutions.

   keMvSurfaceFormatMpegIBPMainProfileHighLevel_420,     // This type of surface contains YUV420 video
                                                         // data compressed by an MPEG codec. The surface
                                                         // can be an I, B, or P-frame. The specific 
                                                         // information of this MPEG surface is described
                                                         // by the MPEG_IBP_Specific structure in the
                                                         // surface description. This surface supports
                                                         // HD (high definition) video resolutions.

   keMvSurfaceFormatMpegIBP422ProfileMainLevel_422,      // This type of surface contains YUV422 video
                                                         // data compressed by an MPEG codec. The surface
                                                         // can be an I, B, or P-frame. The specific 
                                                         // information of this MPEG surface is described
                                                         // by the MPEG_IBP_Specific structure in the 
                                                         // surface description. This surface supports
                                                         // SD video resolutions.

   keMvSurfaceFormatMpegIBP422ProfileHighLevel_422,      // This type of surface contains YUV422 video 
                                                         // data compressed by an MPEG codec. The
                                                         // surface can be an I, B, or P-frame. The
                                                         // specific information of this MPEG surface
                                                         // is described by the MPEG_IBP_Specific structure
                                                         // in the surface description. This surface 
                                                         // supports HD video resolutions.

   keMvSurfaceFormatMpegIFrameMainProfileMainLevel_420,  // This type of surface contains YUV422 video
                                                         // data compressed by an MPEG codec. The surface
                                                         // is an I-frame that supports SD video resolutions.

   keMvSurfaceFormatMpegIFrameMainProfileHighLevel_420,  // This type of surface contains YUV422 video
                                                         // data compressed by an MPEG codec. The surface
                                                         // is an I-frame that supports HD video resolutions.

   keMvSurfaceFormatMpegIFrame422ProfileMainLevel_422,   // This type of surface contains data of type
                                                         // MPEG-2 I-frame 422 Profile @ Main Level (SD resolutions).
                                                         
   keMvSurfaceFormatMpegIFrame422ProfileHighLevel_422,   // This type of surface contains data of type
                                                         // MPEG-2 I-frame 422 Profile @ High
                                                         // Level (HD resolutions).

   keMvSurfaceFormatMpegD10_422,                         // This type of surface contains YUV422 video data 
                                                         // compressed by an MPEG-D10 codec. The surface is an 
                                                         // I-frame.

   keMvSurfaceFormatRLE,                                 // This type of surface contains a bitmap compressed by a 
                                                         // run-length encoding (RLE) algorithm. The 
                                                         // ComponentBitCount can be 8, 10, or 16.
 
   keMvSurfaceFormatEffectPatternData,    // This type of surface contains raw data that is used to 
                                          // store private effect data associated with a GFX 
                                          // (Matrox effect pattern) file.

   keMvSurfaceFormatMJpegBaseline_422,    // This type of surface contains YUV422 video data 
                                          // compressed by a Motion-JPEG lossy (baseline) codec. 

   keMvSurfaceFormatMJpegLossless_422,    // This type of surface contains YUV422 video data 
                                          // compressed by a Motion-JPEG lossless 
                                          // (uncompressed quality) codec. 

   keMvSurfaceFormatHDOffline,   // This type of surface contains data for the HD offline codec. 

   keMvSurfaceFormatAYUV4444,    // This type of surface contains AYUV4444 video data. Each pixel 
                                 // is composed of four components in the following order: alpha, Y, U, and V. 
                                 // The bit depth of this surface is 4 x ComponentBitCount. 
                                 // Can be allocated in host memory (any profile) and graphics engine 
                                 // memory (GPU FX card only). 

   keMvSurfaceFormatDigiserverVBI,     // This type of surface contains Matrox DigiServer VBI 
                                       // information. Used to maintain backward compatibility
                                       // with DigiServer VBI files.

   keMvSurfaceFormatMpegIFrame422ProfileMainLevel_WithAlpha,   // This type of surface contains data 
                                                               // of type MPEG-2 I-frame 422 Profile 
                                                               // @ Main Level (SD resolution) with alpha.
                                                           
   keMvSurfaceFormatMpegIFrame422ProfileHighLevel_WithAlpha,   // This type of surface contains data
                                                               // of type MPEG-2 I-frame 422 Profile
                                                               // @ High Level (HD resolution)
                                                               // with alpha.

   keMvSurfaceFormatAlphaLuminance,    // This type of surface holds alpha and luminance information
                                       // and is used for 3D effect processing. The component bit
                                       // count supported for this surface is 8 bits. Can be
                                       // allocated in graphics engine memory only.
   keMvSurfaceFormatBGRAGraphic,	// This type of surface usually holds graphics.  Each pixel is 
									// composed of four components in the following order: blue, green, red, and alpha. 
									// The bit depth of this surface is 4 x 
									// ComponentBitCount. Can be allocated in host and graphics 
									// engine memory. Black is 0, white is 255.    
   keMvSurfaceFormatBGRAVideo,		// This type of surface usually holds graphics. Each pixel is 
									// composed of four components in the following order: blue, green, red, and alpha. 
									// The bit depth of this surface is 4 x 
									// ComponentBitCount. Can be allocated in host and graphics 
									// engine memory. Black is 16, white is 235. Can contain super 
									// white and/or super black.     

   keMvSurfaceFormatFlexAVClip,        // This type of surface contains compressed data used by the 
                                       // Flex Clip Reader/Writer.

   keMvSurfaceFormatD12_720p50_4to3_422_Fr1,    // This type of surface contains DV100 data for 
                                                // resolution 720p at 25 fps and 50 fps (scaling 
                                                // ratio of  3/4) frame 0, 2, 4, ...

   keMvSurfaceFormatD12_720p50_4to3_422_Fr2,    // This type of surface contains DV100 data for 
                                                // resolution 720p at 25 fps and 50 fps (scaling 
                                                // ratio of  3/4) frame 1, 3, 5, ...

   keMvSurfaceFormatAVCIntraClass50,            // This type of surface contains AVC-Intra Class 50 data.
   keMvSurfaceFormatAVCIntraClass100,           // This type of surface contains AVC-Intra Class 100 data.
   keMvSurfaceFormatAVCIntra,                   // This type of surface contains AVC-Intra Class 50 or Class 100 data.

   keMvSurfaceFormatProRes,                  // This type of surface contains ProRes 422 (standard or HQ) data.
   
   keMvSurfaceFormatAVC,                        // This type of surface contains AVC data.

   keMvSurfaceFormatRLEAnimation,               // This type of surface contains video data compressed by 
                                                //Apple RLE. It will be decoded to RGB.

   keMvSurfaceFormatRLEAnimation_WithAlpha,     // This type of surface contains video data compressed by 
                                                //Apple RLE 32-bit. It will be decoded to ARGB.

   keMvSurfaceFormatA2R10G10B10Graphic,         // This type of surface holds ARGB graphics. Each pixel is 
                                                // composed of four components in the following order: alpha, red, green, and blue. 
                                                // The bit depth of this surface is 32 bits. Alpha 
                                                // has two bits, and the R, G, and B components each have 10 bits. 
                                                // Can be allocated in host memory. 
                                                // Use this format for graphic card surfaces.

   keMvSurfaceFormatA2R10G10B10Video,           // This type of surface holds ARGB video. Each pixel is 
                                                // composed of four components in the following order: alpha, red, green, and blue. 
                                                // The bit depth of this surface is 32 bits. Alpha 
                                                // has two bits, and the R, G, and B components each have 10 bits. 
                                                // Can be allocated in host and in I/O local memory. 
                                                // R, G, and B values should be between 0x040 and 0x3AC, and must 
                                                // never be lower than 0x04 or higher than 0x3FC.
                                                // Use this format for SDI RGB dual-link surfaces.

   keMvSurfaceFormatMatroxAncillaryData,        // This type of surface holds digital ancillary data.
                                                // Can be allocated in host memory only. <b>Note:</b> This surface format is for topology-based DSX cards only.

   keMvSurfaceFormatV210,                       // This type of surface holds YUV 10-bit data in the v210 format.
   
   keMvSurfaceFormat2VUY,        // This type of surface holds video in the 2vuy 8 bit Mac format. For each 
                                 // two pixels, the data organization is YU YV. The bit depth of
                                 // this surface is 2 x 8 bits. Can be allocated in 
                                 // host memory only. Only valid in the Matrox SDK for Mac.
   keMvSurfaceFormatMpeg2Transport,  // This type of surface contains MPEG-2 transport stream data. 
                                 // It can contain any number of audio and/or video streams, optionally 
                                 // compressed. It must follow the ISO 13818-1 specification.

   keMvSurfaceFormatDNxHD,       // This type of surface contains Avid DNxHD data.

   keMvSurfaceFormatDNxHD_WithAlpha,       // This type of surface contains Avid DNxHD data with alpha.

   keMvSurfaceFormatSMPTE436Data, // This type of surface holds SMPTE 436 data. Can be ANC packets or VBI lines.

   keMvSurfaceFormatABGRGraphic,  // This type of surface holds ABGR graphics. Each pixel is composed of four components in 
                                 // the following order: red, green, blue, and alpha.The bit depth of this surface is 16-bit.  
                                 // Can be allocated in host and graphics engine memory. Black is 0, white is 65535.

   keMvSurfaceFormatMPEG4SStP,       // This type of surface contains MPEG-4 Simple Studio Profile (SStP) data.


   keMvSurfaceFormatLast                        // End of list indicator.
};

// This macro is used to get the string of the enum value EMvSurfaceFormat.
#define MV_SURFACE_FORMAT_ENUM_TO_STRING(eSurfaceFormat) \
   ((eSurfaceFormat == keMvSurfaceFormatInvalid)     ? ("Invalid") : \
   (eSurfaceFormat == keMvSurfaceFormatLast)                   ? ("Last") : \
   (eSurfaceFormat == keMvSurfaceFormatARGBGraphic)  ? ("ARGBGraphic") : \
   (eSurfaceFormat == keMvSurfaceFormatRGBGraphic)   ? ("RGBGraphic") : \
   (eSurfaceFormat == keMvSurfaceFormatARGBVideo)    ? ("ARGBVideo") : \
   (eSurfaceFormat == keMvSurfaceFormatRGBVideo)     ? ("RGBVideo") : \
   (eSurfaceFormat == keMvSurfaceFormatYUYV422)      ? ("YUYV422") : \
   (eSurfaceFormat == keMvSurfaceFormatYUAYVA4224)   ? ("YUAYVA4224") : \
   (eSurfaceFormat == keMvSurfaceFormatA)            ? ("A") : \
   (eSurfaceFormat == keMvSurfaceFormatDepthStencil) ? ("DepthStencil") : \
   (eSurfaceFormat == keMvSurfaceFormatDuDv)         ? ("DuDv") : \
   (eSurfaceFormat == keMvSurfaceFormatDuDvL)        ? ("DuDvL") : \
   (eSurfaceFormat == keMvSurfaceFormatDvCam_411)    ? ("DvCam_411") : \
   (eSurfaceFormat == keMvSurfaceFormatDvCam_420)    ? ("DvCam_420") : \
   (eSurfaceFormat == keMvSurfaceFormatDvCPro_411)   ? ("DvCPro_411") : \
   (eSurfaceFormat == keMvSurfaceFormatDv50_422)     ? ("Dv50_422") : \
   (eSurfaceFormat == keMvSurfaceFormatD12_1080_3to2_422)    ? ("D12_1080_3to2_422") : \
   (eSurfaceFormat == keMvSurfaceFormatD12_1080_4to3_422)    ? ("D12_1080_4to3_422") : \
   (eSurfaceFormat == keMvSurfaceFormatD12_720_4to3_422_Fr1) ? ("D12_720_4to3_422_Fr1") : \
   (eSurfaceFormat == keMvSurfaceFormatD12_720_4to3_422_Fr2) ? ("D12_720_4to3_422_Fr2") : \
   (eSurfaceFormat == keMvSurfaceFormatMpegIBPMainProfileMainLevel_420)    ? ("MpegIBPMainProfileMainLevel_420") : \
   (eSurfaceFormat == keMvSurfaceFormatMpegIBPMainProfileHighLevel_420)    ? ("MpegIBPMainProfileHighLevel_420") : \
   (eSurfaceFormat == keMvSurfaceFormatMpegIBP422ProfileMainLevel_422)     ? ("MpegIBP422ProfileMainLevel_422") : \
   (eSurfaceFormat == keMvSurfaceFormatMpegIBP422ProfileHighLevel_422)     ? ("MpegIBP422ProfileHighLevel_422") : \
   (eSurfaceFormat == keMvSurfaceFormatMpegIFrameMainProfileMainLevel_420) ? ("MpegIFrameMainProfileMainLevel_420") : \
   (eSurfaceFormat == keMvSurfaceFormatMpegIFrameMainProfileHighLevel_420) ? ("MpegIFrameMainProfileHighLevel_420") : \
   (eSurfaceFormat == keMvSurfaceFormatMpegIFrame422ProfileMainLevel_422)  ? ("MpegIFrame422ProfileMainLevel_422") : \
   (eSurfaceFormat == keMvSurfaceFormatMpegIFrame422ProfileHighLevel_422)  ? ("MpegIFrame422ProfileHighLevel_422") : \
   (eSurfaceFormat == keMvSurfaceFormatMpegD10_422)       ? ("MpegD10_422") : \
   (eSurfaceFormat == keMvSurfaceFormatRLE)               ? ("RLE") : \
   (eSurfaceFormat == keMvSurfaceFormatEffectPatternData) ? ("EffectPatternData") : \
   (eSurfaceFormat == keMvSurfaceFormatMJpegBaseline_422) ? ("MJpegBaseline_422") : \
   (eSurfaceFormat == keMvSurfaceFormatMJpegLossless_422) ? ("MJpegLossless_422") : \
   (eSurfaceFormat == keMvSurfaceFormatHDOffline)         ? ("HDOffline") : \
   (eSurfaceFormat == keMvSurfaceFormatAYUV4444)          ? ("AYUV4444") : \
   (eSurfaceFormat == keMvSurfaceFormatDigiserverVBI)     ? ("DigiserverVBI") : \
   (eSurfaceFormat == keMvSurfaceFormatMpegIFrame422ProfileMainLevel_WithAlpha) ? ("MpegIFrame422ProfileMainLevel_WithAlpha") : \
   (eSurfaceFormat == keMvSurfaceFormatMpegIFrame422ProfileHighLevel_WithAlpha) ? ("MpegIFrame422ProfileHighLevel_WithAlpha") : \
   (eSurfaceFormat == keMvSurfaceFormatAlphaLuminance)                          ? ("AlphaLuminance") : \
   (eSurfaceFormat == keMvSurfaceFormatBGRAGraphic)                             ? ("BGRAGraphic") : \
   (eSurfaceFormat == keMvSurfaceFormatBGRAVideo)                               ? ("BGRAVideo") : \
   (eSurfaceFormat == keMvSurfaceFormatFlexAVClip)                              ? ("FlexAVClip") : \
   (eSurfaceFormat == keMvSurfaceFormatD12_720p50_4to3_422_Fr1)                 ? ("D12_720p50_4to3_422_Fr1") : \
   (eSurfaceFormat == keMvSurfaceFormatD12_720p50_4to3_422_Fr2)                 ? ("D12_720p50_4to3_422_Fr2") : \
   (eSurfaceFormat == keMvSurfaceFormatAVCIntraClass50)        ? ("AVCIntraClass50") : \
   (eSurfaceFormat == keMvSurfaceFormatAVCIntraClass100)       ? ("AVCIntraClass100") : \
   (eSurfaceFormat == keMvSurfaceFormatAVCIntra)               ? ("AVCIntra") : \
   (eSurfaceFormat == keMvSurfaceFormatAVC)                    ? ("AVC") : \
   (eSurfaceFormat == keMvSurfaceFormatProRes)                 ? ("ProRes") : \
   (eSurfaceFormat == keMvSurfaceFormatRLEAnimation)           ? ("RLEAnimation") : \
   (eSurfaceFormat == keMvSurfaceFormatRLEAnimation_WithAlpha) ? ("RLEAnimation_WithAlpha") : \
   (eSurfaceFormat == keMvSurfaceFormatA2R10G10B10Graphic) ? ("A2R10G10B10Graphic") : \
   (eSurfaceFormat == keMvSurfaceFormatA2R10G10B10Video) ? ("A2R10G10B10Video") : \
   (eSurfaceFormat == keMvSurfaceFormatMatroxAncillaryData) ? ("MatroxAncillaryData") : \
   (eSurfaceFormat == keMvSurfaceFormatV210) ? ("V210") : \
   (eSurfaceFormat == keMvSurfaceFormat2VUY) ? ("2VUY") : \
   (eSurfaceFormat == keMvSurfaceFormatMpeg2Transport) ? ("Mpeg2Transport") : \
   (eSurfaceFormat == keMvSurfaceFormatDNxHD) ? ("DNxHD") : \
   (eSurfaceFormat == keMvSurfaceFormatABGRGraphic) ? ("ABGRGraphic"):\
   (eSurfaceFormat == keMvSurfaceFormatDNxHD_WithAlpha) ? ("DNxHD_WithAlpha") : \
   (eSurfaceFormat == keMvSurfaceFormatMPEG4SStP) ? ("MPEG4SStP") : \
   ("???"))

//
// Summary:
//    Specifies the surface type.
//
enum EMvSurfaceType
{
   keMvSurfaceTypeInvalid, // Invalid value.
   keMvSurfaceType2D,      // The surface has two dimensions. 
   keMvSurfaceType3D,      // The surface has three dimensions. Also known as volume surface.
   keMvSurfaceTypeCube,    // The surface contains six sub-surfaces that form a cube. Used for special 3D texturing techniques.
   keMvSurfaceType2DMultisample_2,  // The surface has two dimensions and a multi-sample level of 2.
   keMvSurfaceType2DMultisample_3,  // The surface has two dimensions and a multi-sample level of 3.
   keMvSurfaceType2DMultisample_4,  // The surface has two dimensions and a multi-sample level of 4.
   keMvSurfaceType2DMultisample_5,  // The surface has two dimensions and a multi-sample level of 5.
   keMvSurfaceType2DMultisample_6,  // The surface has two dimensions and a multi-sample level of 6.
   keMvSurfaceType2DMultisample_7,  // The surface has two dimensions and a multi-sample level of 7.
   keMvSurfaceType2DMultisample_8,  // The surface has two dimensions and a multi-sample level of 8.
   keMvSurfaceType2DMultisample_9,  // The surface has two dimensions and a multi-sample level of 9.
   keMvSurfaceType2DMultisample_10, // The surface has two dimensions and a multi-sample level of 10.
   keMvSurfaceType2DMultisample_11, // The surface has two dimensions and a multi-sample level of 11.
   keMvSurfaceType2DMultisample_12, // The surface has two dimensions and a multi-sample level of 12.
   keMvSurfaceType2DMultisample_13, // The surface has two dimensions and a multi-sample level of 13.
   keMvSurfaceType2DMultisample_14, // The surface has two dimensions and a multi-sample level of 14.
   keMvSurfaceType2DMultisample_15, // The surface has two dimensions and a multi-sample level of 15.
   keMvSurfaceType2DMultisample_16, // The surface has two dimensions and a multi-sample level of 16.
   keMvSurfaceTypeLast     // End of list indicator.
};

//
// Summary:
//    Describes the paths through which the video stream can pass.
//
enum EMvVideoIOChannel
{
   keVideoIOChannelInvalid,     // Invalid value.
   keVideoIOChannelA = 0x001,   // Describes the first video path.
   keVideoIOChannelB = 0x002,   // Describes the second video path.
   keVideoIOChannelC = 0x004,   // Describes the third video path.
   keVideoIOChannelD = 0x008,   // Describes the fourth video path.
   keVideoIOChannelE = 0x010,   // Describes the fifth video path.
   keVideoIOChannelF = 0x020,   // Describes the sixth video path.
   keVideoIOChannelG = 0x040,   // Describes the seventh video path.
   keVideoIOChannelH = 0x080,   // Describes the eighth video path.
   keVideoIOChannelLast = 0x81 // End of list indicator.
};
#define MAX_NB_VIDEOIOCHANNEL 9

//
// Summary:
//    Specifies which VITC is of interest.
//
enum EMvVITCSelection
{
   keMvVITCInvalid, // Invalid value.
   keMvVITC1,       // VITC1.
   keMvVITC2,       // VITC2.
   keMvVITCLast     // End of list indicator.
};
   
//
// Summary:
//    Specifies the aspect ratio conversion method.
//
enum EMvAspectRatioConversion
{
   keMvAspectRatioConversionInvalid,            // Invalid value.
   keMvAspectRatioConversionLetterOrPillarBox,  // Letterbox or pillarbox conversion. This preserves the aspect ratio by adding black bars.
   keMvAspectRatioConversionCenterCut,          // Center cut conversion. This preserves the aspect ratio by evenly cropping the original image.
   keMvAspectRatioConversionAnamorphic,         // Anamorphic conversion (aspect ratio is not preserved).
   keMvAspectRatioConversionLast                // End of list indicator.
};
   
//
// Summary:
//    Describes the genlock source.
//
enum EMvGenlockSource
{
   keGenlockSourceInvalid                 = 0x00,  // Invalid value.
   keGenlockSourceInternal                = 0x01,  // Internal reference genlock source. 
   keGenlockSourceBlackBurst              = 0x02,  // Broadcast-quality analog black burst genlock source, such as from an external sync generator. 
   keGenlockSourceSDIVideo                = 0x04,  // SDI video input genlock source. 
   keGenlockSourceBlackBurstPoorQuality   = 0x08,  // Consumer-quality analog black burst genlock source, such as from an analog source VTR. 
   keGenlockSourceAnalogVideo             = 0x10,  // Analog video input genlock source.
   keGenlockSourceDVIVideo                = 0x20,  // DVI video input genlock source.
   keGenlockSourceHDMIVideo               = 0x40,  // HDMI video input genlock source.
   keGenlockSourceAll                     = keGenlockSourceInvalid  // All defined values.
   |  keGenlockSourceInternal
   |  keGenlockSourceBlackBurst
   |  keGenlockSourceSDIVideo
   |  keGenlockSourceBlackBurstPoorQuality
   |  keGenlockSourceAnalogVideo
   |  keGenlockSourceDVIVideo
   |  keGenlockSourceHDMIVideo,
   
   keGenlockSourceLast                    = keGenlockSourceAll+1 // End of list indicator.
};

enum EMvHDMI3DVideoFormatEnum
{
   HDMI_3D_VIDEO_FORMAT_FRAME_PACKING,
   HDMI_3D_VIDEO_FORMAT_FIELD_ALTERNATIVE,
   HDMI_3D_VIDEO_FORMAT_LINE_ALTERNATIVE,
   HDMI_3D_VIDEO_FORMAT_SIDE_BY_SIDE_FULL,
   HDMI_3D_VIDEO_FORMAT_L_PLUS_DEPTH,
   HDMI_3D_VIDEO_FORMAT_L_PLUS_DEPTH_PLUS_GRAPHICS_PLUS_GRAPHICS_DEPTH,
   HDMI_3D_VIDEO_FORMAT_TOP_AND_BOTTOM,
   HDMI_3D_VIDEO_FORMAT_RESERVED1,
   HDMI_3D_VIDEO_FORMAT_SIDE_BY_SIDE_HALF,
   HDMI_3D_VIDEO_FORMAT_RESERVED2,
   HDMI_3D_VIDEO_FORMAT_RESERVED3,
   HDMI_3D_VIDEO_FORMAT_RESERVED4,
   HDMI_3D_VIDEO_FORMAT_RESERVED5,
   HDMI_3D_VIDEO_FORMAT_RESERVED6,
   HDMI_3D_VIDEO_FORMAT_RESERVED7,
   HDMI_3D_VIDEO_FORMAT_NOT_IN_USE,
   HDMI_3D_FORMAT_COUNT
};

//
// Summary:
//    Enumerates the time code sources that can be used.
//
enum EMvTimeCodeSource
{
   keMvTimeCodeSourceInvalid,		// Invalid value.
   keMvTimeCodeSourceLTC,			// Indicates that the time code is obtained from the LTC input.
   keMvTimeCodeSourceBlackBurst,	// Indicates that the time code is obtained from the black burst reference input.
   keMvTimeCodeSourceLast,			// End of list indicator.
};

//
// Summary:
//    Enumerates the analog linear time code sampling clock that can be used.
//
enum EMvALTCSamplingClock
{
   keMvALTCSamplingClockInvalid,  // Invalid value.
   keMvALTCSamplingClockDisabled, // Indicates that the sampling of ALTC is disabled.
   keMvALTCSamplingClockGenlock,  // Indicates that the sampling clock is the genlock clock.
   keMvALTCSamplingClockInput,    // Indicates that the sampling clock is the input clock.
                                     // An input stream and a video signal with proper resolution
                                     // must be present for the input clock to work properly.
   keMvALTCSamplingClockLast,     // End of list indicator.
};

//*********************************************************************************//
//**                                     STRUCTURES                              **//
//*********************************************************************************//

//
// Summary:
//    Describes a buffer's audio data format. 
//
struct SMvaWaveFormatInfo
{
   uint32_t         size;                 // Structure size in bytes. 
   EMvChannelType	  eChannelType;         // Type of channels supported (mono, stereo, etc.). 
   EMvAudioDataType eDataType;            // Type of audio data samples (PCM, float etc.). 
   uint32_t	  ulSamplesPerSec;      // Sample rate, in samples per second (hertz). 
   uint32_t	  ulBitsPerSample;      // Bits per sample for the data type. This is the container 
                                             // size of the data if the actual data size is different from
                                             // the container size. This field must be equal to or greater than 
                                             // ulValidBitsPerSample. 
   uint32_t	  ulValidBitsPerSample; // Valid bits per sample for the data type. This is the 
                                             // actual size of the data inside the container. This 
                                             // field must be equal to or less than ulBitsPerSample.
};

//
// Summary:
//    Describes the audio data composition of the buffer.
//
struct SMvAudioSamplesDescription
{
   uint32_t					size;             // Structure size in bytes. 
   EMvPolarity				ePolarity;        // The polarity of the corresponding video frame. 
   EMvMemoryLocation    eMemoryLocation;  // Indicates in which memory location the surface has been allocated. 
   bool						bHasFadeIn;       // If true, indicates that the buffer contains an audio fade-in. 
   bool						bHasFadeOut;      // If true, indicates that the buffer contains an audio fade-out. 
   SMvaWaveFormatInfo	sWaveFormat;      // Structure containing wave format information for the audio buffer. 
};

//
// Summary:
//    Describes a resolution's settings.
//
struct SMvResolutionInfo
{
   uint32_t       size;                // Structure size in bytes.
   uint32_t       ulWidth;             // Resolution width in pixels.
   uint32_t       ulHeight;            // Resolution height in pixels.
   uint32_t       ulComponentBitCount; // Number of bits per component of a pixel.
   EMvAspectRatio eAspectRatio;        // Resolution aspect ratio of the output monitor. 
   EMvFrameRate   eFrameRate;          // Number of frames per second.
   EMvScanMode    eScanMode;           // Indicates whether the video is interlaced or progressive. For interlaced video, the field containing the top line is also indicated.
};

//
// Summary:
//    Describes basic information about a hardware profile.
//
struct SMvHardwareProfileInfo
{
   uint32_t           size;                        // Structure size in bytes.
   EMvHardwareProfile eHardwareProfileType;        // Indicates which hardware profile to use to create the Flex Engine.
   uint32_t      ulHardwareProfileIndex;      // Specifies the index of the hardware profile to use.
   wchar_t            wszHardwareProfileName[256]; // Name of the specified hardware profile.
};

//
// Summary:
//    Used to get information on how to access a locked surface.
//
struct SMvLockSurfaceDescription
{
   uint32_t      size;                 // Structure size in bytes.
   uint32_t ulWidth;              // Usable width of the surface in pixels.
   uint32_t ulHeight;             // Usable height of the surface in pixels.
   uint32_t ulDepth;              // Depth of the locked surface.
   uint32_t ulRowPitchInBytes;    // Indicates in bytes the true width of the memory buffer that
                                          // holds the surface.
   uint32_t ulSlicePitchInBytes;  // Indicates in bytes the offset from the beginning of the memory
                                          // buffer of one slice to the beginning of the memory buffer 
                                          // of the next deepest slice. Only a "3D" surface type will report a slice pitch other than zero.
   void 			* pBuffer;            // Pointer to the beginning of the memory where the surface data is located.
};

//
// Summary:
//    Describes the coordinates of a two-dimensional point.
//
struct SMvPointF
{
   float fX;   // X coordinate of the point.
   float fY;   // Y coordinate of the point.
};

//
// Summary:
//    Temporal compression formats related information.
//
struct SMvTemporalCompressionInfo
{
   uint32_t size;             // Structure size in bytes.
   bool     bDependsOnValid;  // If true, bDependsOn is known. Otherwise, bDependsOn is ignored.
   bool     bDependsOn;       // If true, the current sample needs a tier sample in order to be reconstructed. Used in temporal compression scenarios. 
   bool     bDependedOnValid; // If true, bDependedOn is known. Otherwise, bDependedOn is ignored.
   bool     bDependedOn;      // If true, a tier sample needs the current sample in order to be reconstructed. Used in temporal compression scenarios. 
   bool     bRandomAccess;    // If true, the current sample position is accessible in a random access scenario.
};

//
// Summary:
//    Specifies all information that describes a surface.
//
struct SMvSurfaceDescription
{
   uint32_t          size;                   // Structure size in bytes.
   uint32_t     ulWidth;                // Usable width of the surface in pixels.
   uint32_t     ulHeight;               // Usable height of the surface in pixels.
   uint32_t     ulDepth;                // Indicates the depth of the surface in pixels. Only a 3D surface type can have a depth greater than one.
   uint32_t     ulWidthInBytes;         // Usable width of the surface in bytes.
   uint32_t     ulRowPitchInBytes;      // Indicates in bytes the true width of the memory buffer that holds the surface.
   uint32_t     ulSlicePitchInBytes;    // Indicates in bytes the offset from the beginning of the memory buffer of one slice to the beginning of the
                                                // memory buffer of the next deepest slice. Only a 3D surface type will report a slice pitch other than zero.
   uint32_t     ulComponentBitCount;    // Indicates the number of bits per component of a pixel.
   uint32_t     ulMipmapCount;          // Indicates how many mipmaps this surface has.
   uint32_t     ulBufferSizeInBytes;    // Indicates in bytes the size of the memory buffer that holds the surface. 
   EMvColorimetry    eColorimetry;           // Specifies the color range standard used in this surface.
   EMvSurfaceFormat  eFormat;                // Indicates the format of the surface.
   EMvSurfaceType    eType;                  // Indicates the surface type (2D, 3D, Cube, etc.).
   EMvMemoryLocation eMemoryLocation;        // Indicates in which memory location the surface has been allocated.
   EMvPolarity       ePolarity;              // Indicates the polarity of the surface. Not applicable for a compressed surface format.
   EMvImageOrigin    eImageOrigin;           // Indicates the orientation of the surface.
   SMvPointF         ptDestinationPosition;  // Point that specifies how to position the surface in the destination of an effect or a compositor.
   bool              bIsSurfaceOfTopLine;    // If true, the first line of the field surface is displayed as the first line of the frame.
   bool              bUseAlpha;              // If true, uses the alpha of the surface in the effect.
   bool              bIsVideoShaped;         // If true, indicates that the video is already multiplied by the alpha plane.
   bool              bIsAligned;             // If true, indicates that the surface memory buffer is aligned to 128 bytes and 16 pixels.
   SMvTemporalCompressionInfo sTemporalCompressionInfo; // Information specific to temporal compression formats.
};

//
// Summary:
//    Used to allocate an audio container that encapsulates a host-memory buffer that is provided by the user application. 
//    This structure should only be used with IMvAudioSamples::AssignUserBufferReference().
//
struct SMvUserBufferAudioSamplesDescription
{
   uint32_t           size;            // Structure size in bytes.
   void             * pBuffer;         // Pointer to the user allocated buffer.
   uint32_t      ulBufferSize;    // Size of valid data in the user-allocated buffer.
   uint32_t      ulBufferSizeMax; // Maximum size available for the user-allocated buffer.
   EMvPolarity        ePolarity;       // Indicates the polarity of the corresponding video frame.
   bool               bHasFadeIn;      // If true, indicates that the buffer contains an audio fade-in.
   bool               bHasFadeOut;     // If true, indicates that the buffer contains an audio fade-out.
   SMvaWaveFormatInfo sWaveFormat;     // Structure containing wave format information of the audio buffer.
};

//
// Summary:
//    Used to allocate a surface that encapsulates a host-memory buffer already allocated by the user.
//
struct SMvUserBufferSurfaceDescription
{
   uint32_t          size;                   // Structure size in bytes.
   uint32_t     ulWidth;                // Usable width of the surface in pixels.
   uint32_t     ulHeight;               // Usable height of the surface in pixels.
   uint32_t     ulDepth;                // Indicates the depth of the surface in pixels. Only a "3D" surface type 
                                             // can have a depth greater than one.
   uint32_t     ulRowPitchInBytes;      // Indicates the true width, in bytes, of the memory 
                                                // buffer that holds the surface.
   uint32_t     ulSlicePitchInBytes;    // Indicates in bytes the offset from the beginning of 
                                                // the memory buffer of one slice to the beginning of 
                                                // the memory buffer of the next deepest slice. Only
                                                // a "3D" surface type will report 
                                                // a slice pitch other than zero.
   uint32_t     ulComponentBitCount;    // Indicates the number of bits per component of a pixel.
   uint32_t     ulBufferSizeInBytes;    // Indicates the size, in bytes, of the memory buffer 
                                                // that holds the surface. 
   void            * pBuffer;                // Pointer to the beginning of the memory where the surface data is.
   EMvSurfaceFormat  eFormat;                // Indicates the format of the surface.
   EMvSurfaceType    eType;                  // Indicates the surface type (2D, 3D, Cube, etc.).
   EMvPolarity       ePolarity;              // Indicates the polarity of the surface. Not applicable 
                                                // for a compressed surface format.
   EMvImageOrigin    eImageOrigin;           // Indicates the orientation of the surface.
   EMvColorimetry    eColorimetry;	         // Specifies the color range standard used in this surface.
   SMvPointF         ptDestinationPosition;  // Point that specifies how to position the surface in 
                                                // the destination of an effect or a compositor.
   bool              bUseAlpha;              // If true, the alpha of the surface must be taken
                                                // into account by the effect.
   bool              bIsVideoShaped;         // If true, indicates that the video is shaped. Shaped video
                                                // means that the video has been pre-multiplied by the
                                                // alpha plane.
   SMvTemporalCompressionInfo sTemporalCompressionInfo; // Information specific to temporal compression formats.
};

// Summary:
//    Describes VANC data in a host-memory user buffer already allocated by the user.
//
//struct SMvUserBufferVancDescription
//{
//    uint32_t          size;                   // Structure size in bytes.
//    uint32_t     ulComponentBitCount;    // Number of bits per component of a pixel.
//    uint32_t     ulBufferSizeInBytes;    // The size, in bytes, of the memory buffer 
//                                              // that holds the data. 
//    void            * pBuffer;                // Pointer to the beginning of the memory where the data is located.
//    EMvSurfaceFormat  eFormat;                // Format of the surface.
//};

//
// Summary:
//    Describes the extra input/output information.
// Description:
// 
// <b> SMPTE 12M-2 LTC/VITC values </b>
// <table>
// Bits     Description
// -----    -----------------------------------
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
// 28       Polarity correction flag (LTC only).<p> Field flag (VITC only).
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
// Remarks:
// - The SMPTE 12M-2 LTC/VITC, SMPTE 12M-1 LTC, and the input audio sample count are supported only on certain Matrox DSX hardware. 
//   See the <i>Matrox DSX.sdk User Guide</i> and/or the <i>Matrox DSX Topology API User Guide</i> for more information. 
//
struct SMvIOExtraInfo   
{
   uint32_t  size;                        // Structure size in bytes.
   uint64_t  ui64RP188_LTCValue;          // Indicates the SMPTE 12M-2 (previously SMPTE RP188) LTC (linear time code) value. 
   bool      bRP188_LTCPresent;           // If true, SMPTE 12M-2 LTC is present. <p> For a surface being captured, 
                                          // the LTC is found in the input video stream. <p> For a surface to be output, 
                                          // the LTC will be inserted into the output video stream. 
   uint64_t  ui64RP188_VITCValue;         // Indicates the SMPTE 12M-2 VITC (vertical interval time code) value. 
   bool      bRP188_VITCPresent;          // If true, SMPTE 12M-2 VITC is present. <p> For a surface being captured, 
                                          // the VITC is found in the input video stream. <p> For a surface to be output, 
                                          // the VITC will be inserted into the output video stream. 
   uint64_t  ui64LTCValue;                // Indicates the SMPTE 12M-1 analog LTC.<p> 
                                          // SMPTE 12M-1 LTC bit description is the same as the SMPTE 12M-2 LTC description above. 
   bool      bLTCPresent;                 // If true, SMPTE 12M-1 analog LTC is present. <p> For a surface being 
                                          // captured, the LTC is found in the input video stream. <p> Outputting this LTC is not supported. 
   uint32_t  ui32InputAudioSampleCount;   // Indicates the number of audio samples received with a video buffer. 
   bool      bInputAudioCountValid;       // If true, the input audio sample count is valid. 
};

   
#ifdef MAC_PLATFORM
};  // namespace com_matrox_vpg_SDK
#endif

