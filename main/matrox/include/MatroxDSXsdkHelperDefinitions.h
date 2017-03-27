#pragma once

namespace NMvH
{
   static const unsigned long g_kulFrameRateCount = 9;
   static const unsigned long g_kulAspectRatioCount = 3;
   static const unsigned long g_kulVANCSurfaceFormatcount = 2;

   ///////////////////////////////////////////////////////////
   //  Constant
   ///////////////////////////////////////////////////////////
   static const SMvResolutionInfo g_kasResolution[] =
   {
      // NTSC
      { sizeof(SMvResolutionInfo), 720, 486, 0, keMvAspectRatio_4_3, keMvFrameRateInvalid, keMvScanModeSecondFieldTop },

      // PAL                                
      { sizeof(SMvResolutionInfo), 720, 576, 0, keMvAspectRatio_4_3, keMvFrameRateInvalid, keMvScanModeFirstFieldTop },

      // 720p                               
      { sizeof(SMvResolutionInfo), 1280, 720, 0, keMvAspectRatio_16_9, keMvFrameRateInvalid, keMvScanModeProgressive },

      // 1080i                              
      { sizeof(SMvResolutionInfo), 1920, 1080, 0, keMvAspectRatio_16_9, keMvFrameRateInvalid, keMvScanModeFirstFieldTop },

      // 1080psf                              
      { sizeof(SMvResolutionInfo), 1920, 1080, 0, keMvAspectRatio_16_9, keMvFrameRateInvalid, keMvScanModeProgressiveSegmented },

      // 1080p                              
      { sizeof(SMvResolutionInfo), 1920, 1080, 0, keMvAspectRatio_16_9, keMvFrameRateInvalid, keMvScanModeProgressive },

      // 2K                              
      { sizeof(SMvResolutionInfo), 2048, 1080, 0, keMvAspectRatio_256_135, keMvFrameRateInvalid, keMvScanModeProgressive },

      // 2Kpsf                              
      { sizeof(SMvResolutionInfo), 2048, 1080, 0, keMvAspectRatio_256_135, keMvFrameRateInvalid, keMvScanModeProgressiveSegmented },

      // QuadHD                              
      { sizeof(SMvResolutionInfo), 3840, 2160, 0, keMvAspectRatio_16_9, keMvFrameRateInvalid, keMvScanModeProgressive },

      // 4K                              
      { sizeof(SMvResolutionInfo), 4096, 2160, 0, keMvAspectRatio_256_135, keMvFrameRateInvalid, keMvScanModeProgressive },

      // 4Kpsf                              
      { sizeof(SMvResolutionInfo), 4096, 2160, 0, keMvAspectRatio_256_135, keMvFrameRateInvalid, keMvScanModeProgressiveSegmented },

      // CUSTOM                              
      { sizeof(SMvResolutionInfo), 0, 0, 0, keMvAspectRatio_16_9, keMvFrameRateInvalid, keMvScanModeInvalid },
   };


   static const SMvResolutionInfo g_kasVANCResolution[] =
   {
      // NTSC
      { sizeof(SMvResolutionInfo), 720, 32, 0, keMvAspectRatio_4_3, keMvFrameRateInvalid, keMvScanModeSecondFieldTop },

      // PAL                                
      { sizeof(SMvResolutionInfo), 720, 34, 0, keMvAspectRatio_4_3, keMvFrameRateInvalid, keMvScanModeFirstFieldTop },

      // 720p                               
      { sizeof(SMvResolutionInfo), 1280, 19, 0, keMvAspectRatio_16_9, keMvFrameRateInvalid, keMvScanModeProgressive },

      // 1080i                              
      { sizeof(SMvResolutionInfo), 1920, 30, 0, keMvAspectRatio_16_9, keMvFrameRateInvalid, keMvScanModeFirstFieldTop },

      // 1080psf                              
      { sizeof(SMvResolutionInfo), 1920, 35, 0, keMvAspectRatio_16_9, keMvFrameRateInvalid, keMvScanModeProgressiveSegmented },

      // 1080p                              
      { sizeof(SMvResolutionInfo), 1920, 35, 0, keMvAspectRatio_16_9, keMvFrameRateInvalid, keMvScanModeProgressive },

      // 2K                              
      { sizeof(SMvResolutionInfo), 2048, 1080, 0, keMvAspectRatio_256_135, keMvFrameRateInvalid, keMvScanModeProgressive },

      // 2Kpsf                              
      { sizeof(SMvResolutionInfo), 2048, 1080, 0, keMvAspectRatio_256_135, keMvFrameRateInvalid, keMvScanModeProgressiveSegmented },

      // QuadHD                              
      { sizeof(SMvResolutionInfo), 3840, 2160, 0, keMvAspectRatio_16_9, keMvFrameRateInvalid, keMvScanModeProgressive },

      // 4K                              
      { sizeof(SMvResolutionInfo), 4096, 2160, 0, keMvAspectRatio_256_135, keMvFrameRateInvalid, keMvScanModeProgressive },

      // 4Kpsf                              
      { sizeof(SMvResolutionInfo), 4096, 2160, 0, keMvAspectRatio_256_135, keMvFrameRateInvalid, keMvScanModeProgressiveSegmented },

      // CUSTOM                              
      { sizeof(SMvResolutionInfo), 0, 0, 0, keMvAspectRatio_16_9, keMvFrameRateInvalid, keMvScanModeInvalid },
   };

   static const unsigned long g_kulResolutionCount = sizeof(g_kasResolution) / sizeof(SMvResolutionInfo);


   static const EMvFrameRate g_akeFrameRate[g_kulResolutionCount][g_kulFrameRateCount] =
   {
      // NTSC
      { keMvFrameRate30M, keMvFrameRateInvalid, keMvFrameRateInvalid, keMvFrameRateInvalid, keMvFrameRateInvalid,
      keMvFrameRateInvalid, keMvFrameRateInvalid, keMvFrameRateInvalid, keMvFrameRateInvalid },

      // PAL
      { keMvFrameRate25, keMvFrameRateInvalid, keMvFrameRateInvalid, keMvFrameRateInvalid, keMvFrameRateInvalid,
      keMvFrameRateInvalid, keMvFrameRateInvalid, keMvFrameRateInvalid, keMvFrameRateInvalid },

      // 720p
      { keMvFrameRate50, keMvFrameRate60, keMvFrameRate60M, keMvFrameRateInvalid, keMvFrameRateInvalid,
      keMvFrameRateInvalid, keMvFrameRateInvalid, keMvFrameRateInvalid, keMvFrameRateInvalid },

      // 1080i
      { keMvFrameRate25, keMvFrameRate30M, keMvFrameRate30, keMvFrameRateInvalid, keMvFrameRateInvalid,
      keMvFrameRateInvalid, keMvFrameRateInvalid, keMvFrameRateInvalid, keMvFrameRateInvalid },

      // 1080psf
      { keMvFrameRate24M, keMvFrameRate24, keMvFrameRate25, keMvFrameRate30M, keMvFrameRate30,
      keMvFrameRateInvalid, keMvFrameRateInvalid, keMvFrameRateInvalid, keMvFrameRateInvalid },

      // 1080p
      { keMvFrameRate24M, keMvFrameRate24, keMvFrameRate25, keMvFrameRate30M, keMvFrameRate30,
      keMvFrameRate50, keMvFrameRate60M, keMvFrameRate60, keMvFrameRateInvalid },

      // 2K
      { keMvFrameRate24M, keMvFrameRate24, keMvFrameRate25, keMvFrameRate30M, keMvFrameRate30,
      keMvFrameRate50, keMvFrameRate60M, keMvFrameRate60, keMvFrameRateInvalid },

      // 2Kpsf
      { keMvFrameRate24M, keMvFrameRate24, keMvFrameRate25, keMvFrameRate30M, keMvFrameRate30,
      keMvFrameRateInvalid, keMvFrameRateInvalid, keMvFrameRateInvalid, keMvFrameRateInvalid },

      // QuadHD
      { keMvFrameRate24M, keMvFrameRate24, keMvFrameRate25, keMvFrameRate30M, keMvFrameRate30,
      keMvFrameRate50, keMvFrameRate60M, keMvFrameRate60, keMvFrameRateInvalid },

      // 4K
      { keMvFrameRate24M, keMvFrameRate24, keMvFrameRate25, keMvFrameRate30M, keMvFrameRate30,
      keMvFrameRate50, keMvFrameRate60M, keMvFrameRate60, keMvFrameRateInvalid },

      // 4Kpsf
      { keMvFrameRate24M, keMvFrameRate24, keMvFrameRate25, keMvFrameRate30M, keMvFrameRate30,
      keMvFrameRateInvalid, keMvFrameRateInvalid, keMvFrameRateInvalid, keMvFrameRateInvalid },

      // CUSTOM
      { keMvFrameRate24M, keMvFrameRate24, keMvFrameRate25, keMvFrameRate30M, keMvFrameRate30,
      keMvFrameRate50, keMvFrameRate60M, keMvFrameRate60, keMvFrameRateInvalid },

   };

   static const EMvAspectRatio g_akeAspectRatio[g_kulResolutionCount][g_kulAspectRatioCount] =
   {
      // NTSC
      { keMvAspectRatio_4_3, keMvAspectRatio_16_9, keMvAspectRatioInvalid },

      // PAL
      { keMvAspectRatio_4_3, keMvAspectRatio_16_9, keMvAspectRatioInvalid },

      // 720p
      { keMvAspectRatio_16_9, keMvAspectRatioInvalid, keMvAspectRatioInvalid },

      // 1080i
      { keMvAspectRatio_16_9, keMvAspectRatioInvalid, keMvAspectRatioInvalid },

      // 1080psf
      { keMvAspectRatio_16_9, keMvAspectRatioInvalid, keMvAspectRatioInvalid },

      // 1080p
      { keMvAspectRatio_16_9, keMvAspectRatioInvalid, keMvAspectRatioInvalid },

      // 2K
      { keMvAspectRatio_256_135, keMvAspectRatioInvalid, keMvAspectRatioInvalid },

      // 2Kpsf
      { keMvAspectRatio_256_135, keMvAspectRatioInvalid, keMvAspectRatioInvalid },

      // QuadHD
      { keMvAspectRatio_16_9, keMvAspectRatioInvalid, keMvAspectRatioInvalid },

      // 4K
      { keMvAspectRatio_256_135, keMvAspectRatioInvalid, keMvAspectRatioInvalid },

      // 4Kpsf
      { keMvAspectRatio_256_135, keMvAspectRatioInvalid, keMvAspectRatioInvalid },

      // CUSTOM
      { keMvAspectRatio_4_3, keMvAspectRatio_16_9, keMvAspectRatioInvalid },
   };

#ifdef __GNUC__
   static const wchar_t * g_kszResName[g_kulResolutionCount]  __attribute__ ((unused)) =
   {
      L"NTSC", L"PAL", L"720p", L"1080i", L"1080psf", L"1080p", L"2K", L"2Kpsf", L"QuadHD", L"4K", L"4Kpsf", L"CUSTOM"
   };
#else
   static const wchar_t * g_kszResName[g_kulResolutionCount] =
   {
      L"NTSC", L"PAL", L"720p", L"1080i", L"1080psf", L"1080p", L"2K", L"2Kpsf", L"QuadHD", L"4K", L"4Kpsf", L"CUSTOM"
   };
#endif
   

   static const EMvSurfaceFormat  g_akeVANCSurfaceFormat[g_kulVANCSurfaceFormatcount] =
   {
      keMvSurfaceFormatYUYV422, keMvSurfaceFormatMatroxAncillaryData
   };
}
