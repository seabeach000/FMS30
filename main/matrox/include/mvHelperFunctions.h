#ifndef MVHELPERFUNCTIONS_H
#define MVHELPERFUNCTIONS_H


#include "mvDefinitions.h"

namespace NMvHelper
{
   // Resolution related arrays
   extern "C" const SMvResolutionInfo g_kasResolution[];
   extern "C" const unsigned long     g_kulResolutionCount;
   static     const unsigned long     g_kulFrameRateCount = 9;
   static     const unsigned long     g_kulAspectRatioCount = 3;
   extern "C"       EMvFrameRate      g_akeFrameRate[][g_kulFrameRateCount];
   extern "C"       EMvAspectRatio    g_akeAspectRatio[][g_kulAspectRatioCount];
   extern "C" const wchar_t            * g_kszResName[];

   extern "C" const SMvResolutionInfo g_kasVANCResolution[];
   static     const unsigned long     g_kulVANCSurfaceFormatcount = 2;
   extern "C"       EMvSurfaceFormat  g_akeVANCSurfaceFormat[g_kulVANCSurfaceFormatcount];

   int EMvFrameRateToValue(EMvFrameRate in_eValue);
   int EMvFrameRateToScale(EMvFrameRate in_eValue);
   double EMvFrameRateToDouble(EMvFrameRate in_eFrameRate);

   EMvAudioPlaybackChannel GetAudioPlaybackChannel(EMvVideoIOChannel in_eChannel);
   EMvAudioCaptureChannel  GetAudioCaptureChannel(EMvVideoIOChannel in_eChannel);
   EMvColorimetry          GetColorimetryFromResolution(const SMvResolutionInfo & in_rsResolution);
   EMvVideoIOChannel       GetVideoChannelFromIndex(int in_iIndex);
   int                     GetIndexFromVideoChannel(EMvVideoIOChannel in_eChannel);

   bool           IsSurfaceFormatWithKey(EMvSurfaceFormat in_eFormat);
   bool           IsNTSC(SMvResolutionInfo & in_rsResolution);
   bool           IsNTSCIFF(SMvResolutionInfo & in_rsResolution);
   bool           IsNTSCProgressive(SMvResolutionInfo & in_rsResolution);
   bool           IsPAL(SMvResolutionInfo & in_rsResolution);
   bool           IsPALIFF(SMvResolutionInfo & in_rsResolution);
   bool           IsPALProgressive(SMvResolutionInfo & in_rsResolution);
   bool           Is720p(SMvResolutionInfo & in_rsResolution, EMvFrameRate in_eFrameRate = keMvFrameRateInvalid);
   bool           Is1080i(SMvResolutionInfo & in_rsResolution, EMvFrameRate in_eFrameRate = keMvFrameRateInvalid);
   bool           Is1080i_1440x1080(SMvResolutionInfo & in_rsResolution, EMvFrameRate in_eFrameRate = keMvFrameRateInvalid);
   bool           Is1080p(SMvResolutionInfo & in_rsResolution, EMvFrameRate in_eFrameRate = keMvFrameRateInvalid);
   bool           Is1080psf(SMvResolutionInfo & in_rsResolution, EMvFrameRate in_eFrameRate = keMvFrameRateInvalid);
   bool           IsSameFrameRate (SMvResolutionInfo & in_rsResolution, EMvFrameRate in_eFrameRate);
   bool           IsSameFrameRateFamily (SMvResolutionInfo & in_rsResolution, EMvFrameRate in_eFrameRate);
   bool           IsCompatibleFrameRate(EMvFrameRate in_eFrameRate1, EMvFrameRate in_eFrameRate2);
   bool           IsChannelTypeValid(EMvChannelType in_eChannelType);
   bool           IsMemoryLocationInHost(EMvMemoryLocation in_eMemoryLocation);

   bool           GetPALResolution(SMvResolutionInfo * io_psRes);
   bool           GetNTSCResolution(SMvResolutionInfo * io_psRes);
   bool           Get1080iResolution(SMvResolutionInfo * io_psRes, EMvFrameRate eFramerate = keMvFrameRate30M);
   bool           Get720pResolution(SMvResolutionInfo * io_psRes, EMvFrameRate eFramerate = keMvFrameRate60M);
   bool           CompareResolutions(SMvResolutionInfo& in_rsResolutionInfo1, SMvResolutionInfo& in_rsResolutionInfo2);

   const wchar_t   VideoChannelToChar(EMvVideoIOChannel in_eValue);
   const wchar_t * ColorimetryToString(EMvColorimetry in_eValue);
   const wchar_t * SurfaceFormatToString(EMvSurfaceFormat in_eValue);
   const wchar_t * SurfaceTypeToString(EMvSurfaceType in_eValue);
   const wchar_t * MemoryLocationToString(EMvMemoryLocation in_eValue);
   const wchar_t * PolarityToString(EMvPolarity in_eValue);
   const wchar_t * ImageOriginToString(EMvImageOrigin in_eValue);
   const wchar_t * BoolToString(bool in_bValue);
   const wchar_t * FilterModeToString(EMvFilterMode in_eValue);
   const wchar_t * VideoIOChannelToString(EMvVideoIOChannel in_eValue);
   const wchar_t * AudioCaptureChannelToString(EMvAudioCaptureChannel in_eValue);
   const wchar_t * AudioPlaybackChannelToString(EMvAudioPlaybackChannel in_eValue);
   const wchar_t * FrameRateToString(EMvFrameRate in_eValue);
   const wchar_t * ScanModeToString(EMvScanMode in_eValue);
   const wchar_t * AspectRatioToString(EMvAspectRatio in_eValue);
   const wchar_t * AudioDataTypeToString(EMvAudioDataType in_eValue);
   const wchar_t * PixelRatioToString(EMvPixelRatio in_eValue);
   void ResolutionToString(const SMvResolutionInfo & in_rsResolution, wchar_t * out_pwszString, unsigned int in_uiLength);
   const wchar_t * HardwareProfileToString(const EMvHardwareProfile in_eProfile);
   const wchar_t * HardwareSerieToString(const EMvHardwareSerie in_eValue);
   const wchar_t * CaptureAudioSourceToString(EMvCaptureAudioSource in_eValue);
   const wchar_t * GenlockSourceToString(EMvGenlockSource in_eGenlockSource);
   const wchar_t * VancPacketTypeToString(uint8_t in_ui8DID, uint8_t in_ui8SDID);
   bool VancPacketTypeToStringEx(uint8_t in_ui8Line, uint8_t in_ui8DID, uint8_t in_ui8SDID, wchar_t* out_pwszString, unsigned int in_uiMaxLengthInWChars);

   unsigned long  HeightFromCrompressionFormat(EMvSurfaceFormat in_eFormat, unsigned long in_ulHeight);
   unsigned long  AudioSamplesCountFromFrameRate(SMvResolutionInfo & in_rsRes);
   EMvPolarity    GetPolarityFromResolution(SMvResolutionInfo & in_rsRes);
   void           StreamingSizeFromResolution(int & out_iStreamingSize, SMvResolutionInfo & in_rsResolution);
   void           GetIOResFromERes(SMvResolutionInfo & out_rsIORes, SMvResolutionInfo & in_rsERes);
   void           AdjustLiveWindowSize(SMvResolutionInfo & in_rsResolution, int & io_rWidth, int & in_rHeight);

   double         GetPixelAspectRatio(SMvResolutionInfo & in_sResInfo);

   unsigned long  GetFieldBasedLineIdxFromVancSurfaceBasedLineIdx(unsigned long in_ulLineFromBeginningOfVancSurface, unsigned long in_ulVancWidth, unsigned long in_ulVancHeight, EMvPolarity in_ePolarity);    

   unsigned long FindGCD(unsigned long num1, unsigned long num2);
   unsigned long FindLCM(unsigned long num1, unsigned long num2);
}

#endif //MVHELPERFUNCTIONS_H