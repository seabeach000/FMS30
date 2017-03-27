
//==============================================================================
//
// (c) Copyright Matrox Electronic Systems Ltd., 2003. All rights reserved. 
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

#include "mvIODefinitions.h"

#ifdef MAC_PLATFORM
namespace com_matrox_vpg_SDK
{
#endif

const unsigned long kulMaxValueCompressionInputFormat    = 4;
const unsigned long kulMaxValueDecompressionOutputFormat = 4;
const unsigned long kulMaxValueResolution                = 6;

//
// Summary:
//    Allocates an audio sample container. This structure contains the initial values the object should have upon creation. 
// 
struct SMvCreateAudioSamplesDescription
{
   uint32_t                   size;             // Structure size in bytes.
   unsigned long              ulMaxBufferSize;  // Size of buffer to allocate.
   EMvPolarity                ePolarity;        // Indicates the polarity of the surface. 
   EMvMemoryLocation          eMemoryLocation;  // Indicates in which memory location the surface must be allocated. 
   bool                       bHasFadeIn;       // If true, the buffer contains fade-in.
   bool                       bHasFadeOut;      // If true, the buffer contains fade-out. 
   SMvaWaveFormatInfo         sWaveFormat;      // Structure containing wave format information of the audio buffer.
}; 

//
// Summary:
//    Used to allocate a surface. 
// 
struct SMvCreateSurfaceDescription
{
   uint32_t                   size;                      // Structure size in bytes. 
   unsigned long              ulWidth;                   // Defines the width (in pixels) of the surface to allocate. 
   unsigned long              ulHeight;                  // Defines the height (in pixels) of the surface to allocate. 
   unsigned long              ulDepth;                   // Defines the depth (in pixels) of the surface to allocate.
                                                            // Must be set to 1 except for 3D surface type. 
   unsigned long              ulComponentBitCount;       // Indicates the number of bits per component of a pixel. 
   unsigned long              ulMipmapCount;             // Indicates how many mipmaps this surface has. A surface 
                                                            // always has a minimum of one mipmap level. If the mipmap 
                                                            // count specified is zero, all possible mipmaps will be 
                                                            // generated up to a mipmap of 1x1. 
   EMvSurfaceFormat           eFormat;                   // Indicates the format of the surface to allocate. 
   EMvSurfaceType             eType;                     // Indicates the type of the surface (such as 2D, 3D, and Cube). 
   EMvMemoryLocation          eMemoryLocation;           // Indicates in which memory location the surface should be allocated. 
   EMvPolarity                ePolarity;                 // Indicates the polarity of the surface. 
   EMvImageOrigin             eImageOrigin;              // Indicates the orientation of the surface. 
   EMvColorimetry             eColorimetry;              // Specifies the color range standard used in this surface. 
   SMvPointF                  ptDestinationPosition;     // Point that specifies how to position the surface in the 
                                                            // destination of an effect or a compositor. 
   bool                       bUseAlpha;                 // If true, the alpha of the surface is taken 
                                                            // into account by the effect. 
   bool                       bIsVideoShaped;            // If true, the video has been pre-multiplied by the 
                                                            // alpha plane. 
   SMvTemporalCompressionInfo sTemporalCompressionInfo;  // Structure containing information specific to temporal compression formats.
};

//
// Summary:
//    Specifies all information that defines Playback environment.
//
struct SMvPlaybackChannelSettings
{
   SMvResolutionInfo sOutputChannelResolution;        // resolution present on the output cable
   EMvSurfaceFormat  eOutputFormat;                   // Indicates the format of the surface.
   EMvAspectRatioConversion eAspectRatioConversion;   // Indicating the aspect ratio conversion method when scaling is required
};

struct SMvPlaybackEngineSettings
{
   SMvResolutionInfo   sOutputStreamResolution;    // Surface resolution for this stream.
   EMvSurfaceFormat    eStreamFormat;              // Surface format for this stream.
   uint32_t            ui32NumberOfVideoOutputs;
   uint32_t            ui32NumberOfAudioTracks;
   EMvPixelAspectRatio eStreamPixelAspectRatio;    // Stream pixel aspect ratio
   double              dCustomPixelAspectRatio;    // If keMvPixelAspectRatioCustom is the pixel aspect ratio,
                                                      // you can set the custom value using this parameter, otherwise
                                                      // set this parameter to 0.0
   EMvVITCSelection    eVITCTarget;
};

//
// Summary:
//    Specifies all information that defines capture environment.
//
struct SMvCaptureEngineSettings
{
   SMvResolutionInfo sInputChannelResolution;         // Resolution present on the input cable.
   EMvSurfaceFormat  eInputFormat;                    // Format of the input cable.
   bool              bEnablePassthrough;              // Enable pass-through on corresponding output, false means no pass-through.
   int32_t           i32StreamIndexToMonitor;         // Index of the stream that the pass-through will monitor.  Use -1 to monitor the input cable.
   uint32_t          ui32NumberOfVideoInputStreams;
   uint32_t          ui32NumberOfAudioTracks;
   EMvVITCSelection  eVITCSource;
};

struct SMvCaptureStreamSettings
{
   SMvResolutionInfo   sInputStreamResolution;        // resolution presented though the buffer supplied
   EMvSurfaceFormat    eFormat;                       // Indicates the format of the surface.
   EMvPixelAspectRatio eStreamPixelAspectRatio;       // Stream pixel aspect ratio
   double              dCustomPixelAspectRatio;       // If keMvPixelAspectRatioCustom is the pixel aspect ratio,
                                                      // you can set the custom value using this parameter, otherwise
                                                      // set this parameter to 0.0
   EMvAspectRatioConversion eAspectRatioConversion;   // Indicating the aspect ratio conversion method when scaling is required
};
   
//
// Summary:
//    Specifies all information about the input signal
//
struct SMvVideoInputStatus
{
   uint32_t          size;
   bool              bIsVideoPresent;
   bool              bInputResolutionMismatch;
   bool              bCopyProtected;
   bool              bAutoDetectInputValid;
   SMvResolutionInfo sAutoDetectInputResolution;
};

//
// Summary:
//    Specifies all information that defines Live Mixer environment.
//
struct SMvLiveMixerEngineSettings
{
   SMvResolutionInfo sOutputChannelResolution;  // Resolution present on the output cable (must be the same as on the corresponding input cable).
   EMvSurfaceFormat  eOutputFormat;             // Surface format of overlay stream.
};


//
// Summary:
//    Ancillary data identifier.
//
struct SMvANCDataIdentifier		
{
   uint8_t ui8DID;      // Data Identifier (DID)		
   uint8_t ui8SDID;     // Secondary Data Identifier (SDID) or a Data Block Number (DBN)
};

#ifdef MAC_PLATFORM
};  // namespace com_matrox_vpg_SDK
#endif
