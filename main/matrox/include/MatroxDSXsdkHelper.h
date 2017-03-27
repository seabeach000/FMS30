///////////////////////////////////////////////////////////
//  MatroxDSXsdkHelper.h
//  Implementation of some helper functions 
//  Created on:      25-Jun-2014 5:54:22 PM
//  Original author: cfischer
//
//  Description:
//  This class implements some helper functions used by sample applications
//
///////////////////////////////////////////////////////////

#pragma once
#include "MatroxDSXsdkHelperDefinitions.h"
#include <mvcCodecGuids.h>
#include <mvErrors.h>
#include <mvAudioTime.h>
#include <math.h> // ceil

namespace NMvH {
   ////////////////////////////////////////////////////////////////////////////////////////////
   // Function name   : FramesPerSecond
   // Description     : converts frame rate enumeration value to corresponding uint64_t value
   ////////////////////////////////////////////////////////////////////////////////////////////
   inline uint64_t FramesPerSecond( EMvFrameRate in_eRate )
   {
      uint64_t ui64Frames = 0;

      switch( in_eRate )
      {
      case keMvFrameRate24:
         ui64Frames = 24;
         break;
      case keMvFrameRate24M:
         ui64Frames = 24;
         break;
      case keMvFrameRate25:
         ui64Frames = 25;
         break;
      case keMvFrameRate30:
         ui64Frames = 30;
         break;
      case keMvFrameRate30M:
         ui64Frames = 30;
         break;
      case keMvFrameRate50:
         ui64Frames = 50;
         break;
      case keMvFrameRate60:
         ui64Frames = 60;
         break;
      case keMvFrameRate60M:
         ui64Frames = 60;
         break;
      default:
         break;
      }
      ASSERT( ui64Frames > 0 );
      return ui64Frames;
   }

   ////////////////////////////////////////////////////////////////////////////////////////////
   // Function name   : IsScanMode_Progressive_Or_PsF_Or_IFF
   // Description     : returns true if scan mode is progressive, progressive segmented or interlaced fields in a frame
   ////////////////////////////////////////////////////////////////////////////////////////////
   inline bool IsScanMode_Progressive_Or_PsF_Or_IFF(EMvScanMode in_eMvScanMode)
   {
      if (in_eMvScanMode == keMvScanModeProgressive)
         return true;
      if (in_eMvScanMode == keMvScanModeProgressiveSegmented) // or psf
         return true;
      if (in_eMvScanMode == keMvScanModeInterlacedFieldsInAFrame) // or IFF
         return true;
      return false;
   }
   ////////////////////////////////////////////////////////////////////////////////////////////
   // Function name   : IsScanMode_Progressive_Or_PsF
   // Description     : returns true if scan mode is progressive or progressive segmented
   ////////////////////////////////////////////////////////////////////////////////////////////
   inline bool IsScanMode_Progressive_Or_PsF(EMvScanMode in_eMvScanMode)
   {
      if (in_eMvScanMode == keMvScanModeProgressive)
         return true;
      if (in_eMvScanMode == keMvScanModeProgressiveSegmented) // or psf
         return true;
      return false;
   }

   inline EMvColorimetry GetColorimetryFromResolution(const SMvResolutionInfo & in_rsResolution)
   {
      if(in_rsResolution.ulWidth > 720)
         return keMvColorimetryITUR_BT_709;
      return keMvColorimetryITUR_BT_601;
   }

   inline int EMvFrameRateToValue(EMvFrameRate in_eValue)
   {
      int iValue;


      switch(in_eValue)
      {
      case keMvFrameRate24:         iValue = 24;      break;
      case keMvFrameRate24M:        iValue = 24000;   break;
      case keMvFrameRate25:         iValue = 25;      break;
      case keMvFrameRate30:         iValue = 30;      break;
      case keMvFrameRate30M:        iValue = 30000;   break;
      case keMvFrameRate50:         iValue = 50;      break;
      case keMvFrameRate60:         iValue = 60;      break;
      case keMvFrameRate60M:        iValue = 60000;   break;
      case keMvFrameRateVariable:   iValue = 30;      break;
      default:                      iValue = 30000;   break;
      }

      return iValue;
   }

   inline int EMvFrameRateToScale(EMvFrameRate in_eValue)
   {
      int iValue;


      switch(in_eValue)
      {
      case keMvFrameRate24:         iValue = 1;       break;
      case keMvFrameRate24M:        iValue = 1001;    break;
      case keMvFrameRate25:         iValue = 1;       break;
      case keMvFrameRate30:         iValue = 1;       break;
      case keMvFrameRate30M:        iValue = 1001;    break;
      case keMvFrameRate50:         iValue = 1;       break;
      case keMvFrameRate60:         iValue = 1;       break;
      case keMvFrameRate60M:        iValue = 1001;    break;
      case keMvFrameRateVariable:   iValue = 1;       break;
      default:                      iValue = 1001;    break;
      }

      return iValue;
   }

   inline double EMvFrameRateToDouble(EMvFrameRate in_eFrameRate)
   {
      double dFrameRateValue = 0.0;

      switch(in_eFrameRate)
      {
      case keMvFrameRate24:
         dFrameRateValue = 24.0;
         break;
      case keMvFrameRate24M:
         dFrameRateValue = 24.0 * (1000.0 / 1001.0);
         break;
      case keMvFrameRate25:
         dFrameRateValue = 25.0;
         break;
      case keMvFrameRate30:
         dFrameRateValue = 30.0;
         break;
      case keMvFrameRate30M:
         dFrameRateValue = 30.0 * (1000.0 / 1001.0);
         break;
      case keMvFrameRate50:
         dFrameRateValue = 50.0;
         break;
      case keMvFrameRate60:
         dFrameRateValue = 60.0;
         break;
      case keMvFrameRate60M:
         dFrameRateValue = 60.0 * (1000.0 / 1001.0);
         break;
      default:
         dFrameRateValue = 0.0;
         break;
      }

      return dFrameRateValue;
   }

   inline EMvVideoIOChannel GetVideoChannelFromIndex(int in_iIndex)
   {
      EMvVideoIOChannel eVideoChannel;

      switch(in_iIndex)
      {
      case 0:
         eVideoChannel = keVideoIOChannelA;
         break;
      case 1:
         eVideoChannel = keVideoIOChannelB;
         break;
      case 2:
         eVideoChannel = keVideoIOChannelC;
         break;
      case 3:
         eVideoChannel = keVideoIOChannelD;
         break;
      case 4:
         eVideoChannel = keVideoIOChannelE;
         break;
      case 5:
         eVideoChannel = keVideoIOChannelF;
         break;
      case 6:
         eVideoChannel = keVideoIOChannelLast;
         break;
      default:
         eVideoChannel = keVideoIOChannelInvalid;
         break;
      }

      return eVideoChannel;
   }

   inline int GetIndexFromVideoChannel(EMvVideoIOChannel in_eVideoChannel)
   {
      switch(in_eVideoChannel)
      {
      case keVideoIOChannelA:
         return 0;
      case keVideoIOChannelB:
         return 1;
      case keVideoIOChannelC:
         return 2;
      case keVideoIOChannelD:
         return 3;
      case keVideoIOChannelE:
         return 4;
      case keVideoIOChannelF:
         return 5;
      case keVideoIOChannelG:
         return 6;
      case keVideoIOChannelH:
         return 7;
      case keVideoIOChannelLast:
         return 8;
      default:
         break;
      }

      return -1;
   }

   inline const wchar_t VideoChannelToChar(EMvVideoIOChannel in_eValue)
   {
      switch(in_eValue)
      {
      case keVideoIOChannelA: return L'A';
      case keVideoIOChannelB: return L'B';
      case keVideoIOChannelC: return L'C';
      case keVideoIOChannelD: return L'D';
      case keVideoIOChannelE: return L'E';
      case keVideoIOChannelF: return L'F';
      case keVideoIOChannelG: return L'G';
      case keVideoIOChannelH: return L'H';
      default:                break;
      }

      return L'?';
   }

   inline EMvAudioPlaybackChannel GetAudioPlaybackChannel(EMvVideoIOChannel in_eChannel)
   {
      EMvAudioPlaybackChannel eAudioChannel = keAudioPlaybackChannelInvalid;

      switch(in_eChannel)
      {
      case keVideoIOChannelA:
         eAudioChannel = keAudioPlaybackChannel0;
         break;
      case keVideoIOChannelB:
         eAudioChannel = keAudioPlaybackChannel1;
         break;
      case keVideoIOChannelC:
         eAudioChannel = keAudioPlaybackChannel2;
         break;
      case keVideoIOChannelD:
         eAudioChannel = keAudioPlaybackChannel3;
         break;
      case keVideoIOChannelE:
         eAudioChannel = keAudioPlaybackChannel4;
         break;
      case keVideoIOChannelF:
         eAudioChannel = keAudioPlaybackChannel5;
         break;
      case keVideoIOChannelG:
         eAudioChannel = keAudioPlaybackChannel6;
         break;
      case keVideoIOChannelH:
         eAudioChannel = keAudioPlaybackChannel7;
         break;
      default:
         break;
      }

      return eAudioChannel;
   }

   inline EMvAudioCaptureChannel GetAudioCaptureChannel(EMvVideoIOChannel in_eChannel)
   {
      EMvAudioCaptureChannel eAudioChannel = keAudioCaptureChannelInvalid;

      switch(in_eChannel)
      {
      case keVideoIOChannelA:
         eAudioChannel = keAudioCaptureChannel0;
         break;
      case keVideoIOChannelB:
         eAudioChannel = keAudioCaptureChannel1;
         break;
      case keVideoIOChannelC:
         eAudioChannel = keAudioCaptureChannel2;
         break;
      case keVideoIOChannelD:
         eAudioChannel = keAudioCaptureChannel3;
         break;
      case keVideoIOChannelE:
         eAudioChannel = keAudioCaptureChannel4;
         break;
      case keVideoIOChannelF:
         eAudioChannel = keAudioCaptureChannel5;
         break;
      case keVideoIOChannelG:
         eAudioChannel = keAudioCaptureChannel6;
         break;
      case keVideoIOChannelH:
         eAudioChannel = keAudioCaptureChannel7;
         break;
      default:
         break;
      }

      return eAudioChannel;
   }

   inline bool IsSameFrameRate(SMvResolutionInfo & in_rsResolution, EMvFrameRate in_eFrameRate)
   {
      if(in_eFrameRate == keMvFrameRateInvalid)
         return false;
      if(in_rsResolution.eFrameRate == in_eFrameRate)
         return true;

      return false;
   }

   inline bool IsSameFrameRateFamily(SMvResolutionInfo & in_rsResolution, EMvFrameRate in_eFrameRate)
   {
      switch(in_eFrameRate)
      {
      case keMvFrameRate24M:
      case keMvFrameRate30M:
      case keMvFrameRate60M:
         if((in_rsResolution.eFrameRate == keMvFrameRate24M) ||
            (in_rsResolution.eFrameRate == keMvFrameRate30M) ||
            (in_rsResolution.eFrameRate == keMvFrameRate60M))
         {
            return true;
         }
         return false;
         break;
      case keMvFrameRate25:
      case keMvFrameRate50:
         if((in_rsResolution.eFrameRate == keMvFrameRate25) ||
            (in_rsResolution.eFrameRate == keMvFrameRate50))
         {
            return true;
         }
         return false;
         break;
      case keMvFrameRate24:
      case keMvFrameRate30:
      case keMvFrameRate60:
         if((in_rsResolution.eFrameRate == keMvFrameRate24) ||
            (in_rsResolution.eFrameRate == keMvFrameRate30) ||
            (in_rsResolution.eFrameRate == keMvFrameRate60))
         {
            return true;
         }
         return false;
         break;
      default: //keMvFrameRateInvalid, keMvFrameRateVariable or keMvFrameRateLast
         break;
      }
      ASSERT(!L"Frame rate invalid!");
      return false;
   }

   inline bool IsCompatibleFrameRate(EMvFrameRate in_eFrameRate1, EMvFrameRate in_eFrameRate2)
   {
      bool bCompatible = false;

      // Check for M factor
      if((in_eFrameRate1 == keMvFrameRate24) ||
         (in_eFrameRate1 == keMvFrameRate25) ||
         (in_eFrameRate1 == keMvFrameRate30) ||
         (in_eFrameRate1 == keMvFrameRate50) ||
         (in_eFrameRate1 == keMvFrameRate60))
      {
         if((in_eFrameRate2 == keMvFrameRate24) ||
            (in_eFrameRate2 == keMvFrameRate25) ||
            (in_eFrameRate2 == keMvFrameRate30) ||
            (in_eFrameRate2 == keMvFrameRate50) ||
            (in_eFrameRate2 == keMvFrameRate60))
         {
            bCompatible = true;
         }
      }
      else if((in_eFrameRate1 == keMvFrameRate24M) ||
         (in_eFrameRate1 == keMvFrameRate30M) ||
         (in_eFrameRate1 == keMvFrameRate60M))
      {
         if((in_eFrameRate2 == keMvFrameRate24M) ||
            (in_eFrameRate2 == keMvFrameRate30M) ||
            (in_eFrameRate2 == keMvFrameRate60M))
         {
            bCompatible = true;
         }
      }

      // Check for Europe vs Americas
      if(bCompatible)
      {
         if((in_eFrameRate1 == keMvFrameRate25) ||
            (in_eFrameRate1 == keMvFrameRate50))
         {
            if((in_eFrameRate2 != keMvFrameRate25) &&
               (in_eFrameRate2 != keMvFrameRate50))
            {
               bCompatible = false;
            }
         }
         else if((in_eFrameRate2 == keMvFrameRate25) ||
            (in_eFrameRate2 == keMvFrameRate50))
         {
            if((in_eFrameRate1 != keMvFrameRate25) &&
               (in_eFrameRate1 != keMvFrameRate50))
            {
               bCompatible = false;
            }
         }
      }

      return bCompatible;
   }

   inline bool IsSurfaceFormatWithKey(EMvSurfaceFormat in_eFormat)
   {
      return (in_eFormat == keMvSurfaceFormatMpegIFrame422ProfileMainLevel_WithAlpha ||
         in_eFormat == keMvSurfaceFormatMpegIFrame422ProfileHighLevel_WithAlpha ||
         in_eFormat == keMvSurfaceFormatYUAYVA4224) ? true : false;
   }

   inline bool IsNTSC(SMvResolutionInfo & in_rsResolution)
   {
      if(
         (in_rsResolution.size != sizeof(in_rsResolution))
         ||
         ((in_rsResolution.ulHeight != 486) && (in_rsResolution.ulHeight != 480) && (in_rsResolution.ulHeight != 512))
         ||
         (in_rsResolution.ulWidth != 720)
         ||
         (in_rsResolution.eFrameRate != keMvFrameRate30M)
         ||
         (in_rsResolution.eScanMode != keMvScanModeSecondFieldTop)
         )
      {
         return false;
      }

      return true;
   }

   inline  bool IsNTSCIFF(SMvResolutionInfo & in_rsResolution)
   {
      if(
         (in_rsResolution.size != sizeof(in_rsResolution))
         ||
         ((in_rsResolution.ulHeight != 486) && (in_rsResolution.ulHeight != 480) && (in_rsResolution.ulHeight != 512))
         ||
         (in_rsResolution.ulWidth != 720)
         ||
         (in_rsResolution.eFrameRate != keMvFrameRate30M)
         ||
         (in_rsResolution.eScanMode != keMvScanModeInterlacedFieldsInAFrame)
         )
      {
         return false;
      }

      return true;
   }

   inline bool IsNTSCProgressive(SMvResolutionInfo & in_rsResolution)
   {
      if(
         (in_rsResolution.size != sizeof(in_rsResolution))
         ||
         ((in_rsResolution.ulHeight != 486) && (in_rsResolution.ulHeight != 480) && (in_rsResolution.ulHeight != 512))
         ||
         (in_rsResolution.ulWidth != 720)
         ||
         (in_rsResolution.eFrameRate != keMvFrameRate30M)
         ||
         (in_rsResolution.eScanMode != keMvScanModeProgressive)
         )
      {
         return false;
      }

      return true;
   }

   inline bool IsPAL(SMvResolutionInfo & in_rsResolution)
   {
      if(
         (in_rsResolution.size != sizeof(in_rsResolution))
         ||
         ((in_rsResolution.ulHeight != 576) && (in_rsResolution.ulHeight != 608))
         ||
         (in_rsResolution.ulWidth != 720)
         ||
         (in_rsResolution.eFrameRate != keMvFrameRate25)
         ||
         (in_rsResolution.eScanMode != keMvScanModeFirstFieldTop)
         )
      {
         return false;
      }

      return true;
   }

   inline bool IsPALIFF(SMvResolutionInfo & in_rsResolution)
   {
      if(
         (in_rsResolution.size != sizeof(in_rsResolution))
         ||
         ((in_rsResolution.ulHeight != 576) && (in_rsResolution.ulHeight != 608))
         ||
         (in_rsResolution.ulWidth != 720)
         ||
         (in_rsResolution.eFrameRate != keMvFrameRate25)
         ||
         (in_rsResolution.eScanMode != keMvScanModeInterlacedFieldsInAFrame)
         )
      {
         return false;
      }

      return true;
   }

   inline bool IsPALProgressive(SMvResolutionInfo & in_rsResolution)
   {
      if(
         (in_rsResolution.size != sizeof(in_rsResolution))
         ||
         ((in_rsResolution.ulHeight != 576) && (in_rsResolution.ulHeight != 608))
         ||
         (in_rsResolution.ulWidth != 720)
         ||
         (in_rsResolution.eFrameRate != keMvFrameRate25)
         ||
         (in_rsResolution.eScanMode != keMvScanModeProgressive)
         )
      {
         return false;
      }

      return true;
   }

   inline bool Is720p(SMvResolutionInfo & in_rsResolution, EMvFrameRate in_eFrameRate)
   {
      if(in_eFrameRate != keMvFrameRateInvalid)
      {
         if(!IsSameFrameRate(in_rsResolution, in_eFrameRate))
         {
            return false;
         }
      }
      if(
         (in_rsResolution.size != sizeof(in_rsResolution))
         ||
         (in_rsResolution.ulHeight != 720)
         ||
         (in_rsResolution.ulWidth != 1280)
         ||
         (in_rsResolution.eAspectRatio != keMvAspectRatio_16_9)
         ||
         (
         (in_rsResolution.eFrameRate != keMvFrameRate50)
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate60)
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate60M)
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate24M)  // HDV
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate25)   // HDV
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate30M)  // HDV

         )
         ||
         (in_rsResolution.eScanMode != keMvScanModeProgressive)
         )
      {
         return false;
      }

      return true;
   }

   inline bool Is1080i(SMvResolutionInfo & in_rsResolution, EMvFrameRate in_eFrameRate)
   {
      if(in_eFrameRate != keMvFrameRateInvalid)
      {
         if(!IsSameFrameRate(in_rsResolution, in_eFrameRate))
         {
            return false;
         }
      }
      if(
         (in_rsResolution.size != sizeof(in_rsResolution))
         ||
         (in_rsResolution.ulHeight != 1080)
         ||
         (in_rsResolution.ulWidth != 1920)
         ||
         (in_rsResolution.eAspectRatio != keMvAspectRatio_16_9)
         ||
         (
         (in_rsResolution.eFrameRate != keMvFrameRate24)
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate24M)
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate25)
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate30)
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate30M)
         )
         ||
         (in_rsResolution.eScanMode != keMvScanModeFirstFieldTop)
         )
      {
         return false;
      }

      return true;
   }

   inline bool Is1080i_1440x1080(SMvResolutionInfo & in_rsResolution, EMvFrameRate in_eFrameRate)
   {
      if(in_eFrameRate != keMvFrameRateInvalid)
      {
         if(!IsSameFrameRate(in_rsResolution, in_eFrameRate))
         {
            return false;
         }
      }
      if(
         (in_rsResolution.size != sizeof(in_rsResolution))
         ||
         (in_rsResolution.ulHeight != 1080)
         ||
         (in_rsResolution.ulWidth != 1440)
         ||
         (in_rsResolution.eAspectRatio != keMvAspectRatio_16_9)
         ||
         (
         (in_rsResolution.eFrameRate != keMvFrameRate24)
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate24M)
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate25)
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate30)
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate30M)
         )
         ||
         (in_rsResolution.eScanMode != keMvScanModeFirstFieldTop)
         )
      {
         return false;
      }

      return true;
   }

   inline bool Is1080p(SMvResolutionInfo & in_rsResolution, EMvFrameRate in_eFrameRate)
   {
      if(in_eFrameRate != keMvFrameRateInvalid)
      {
         if(!IsSameFrameRate(in_rsResolution, in_eFrameRate))
         {
            return false;
         }
      }
      if(
         (in_rsResolution.size != sizeof(in_rsResolution))
         ||
         (in_rsResolution.ulHeight != 1080)
         ||
         (in_rsResolution.ulWidth != 1920)
         ||
         (in_rsResolution.eAspectRatio != keMvAspectRatio_16_9)
         ||
         (
         (in_rsResolution.eFrameRate != keMvFrameRate24)
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate24M)
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate25)
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate30)
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate30M)
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate50)
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate60M)
         )
         ||
         (in_rsResolution.eScanMode != keMvScanModeProgressive)
         )
      {
         return false;
      }

      return true;
   }

   inline bool Is1080psf(SMvResolutionInfo & in_rsResolution, EMvFrameRate in_eFrameRate)
   {
      if(in_eFrameRate != keMvFrameRateInvalid)
      {
         if(!IsSameFrameRate(in_rsResolution, in_eFrameRate))
         {
            return false;
         }
      }
      if(
         (in_rsResolution.size != sizeof(in_rsResolution))
         ||
         (in_rsResolution.ulHeight != 1080)
         ||
         (in_rsResolution.ulWidth != 1920)
         ||
         (in_rsResolution.eAspectRatio != keMvAspectRatio_16_9)
         ||
         (
         (in_rsResolution.eFrameRate != keMvFrameRate24)
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate24M)
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate25)
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate30)
         &&
         (in_rsResolution.eFrameRate != keMvFrameRate30M)
         )
         ||
         (in_rsResolution.eScanMode != keMvScanModeProgressiveSegmented)
         )
      {
         return false;
      }

      return true;
   }

   inline unsigned long HeightFromCrompressionFormat(EMvSurfaceFormat in_eFormat, unsigned long in_ulHeight)
   {
      switch(in_eFormat)
      {
      case keMvSurfaceFormatARGBGraphic:
      case keMvSurfaceFormatRGBGraphic:
      case keMvSurfaceFormatARGBVideo:
      case keMvSurfaceFormatRGBVideo:
      case keMvSurfaceFormatYUYV422:
      case keMvSurfaceFormatYUAYVA4224:
      case keMvSurfaceFormatA:
      case keMvSurfaceFormatDepthStencil:
      case keMvSurfaceFormatDuDv:
      case keMvSurfaceFormatDuDvL:
      case keMvSurfaceFormatDvCam_420:
      case keMvSurfaceFormatD12_1080_3to2_422:
      case keMvSurfaceFormatD12_1080_4to3_422:
      case keMvSurfaceFormatD12_720_4to3_422_Fr1:
      case keMvSurfaceFormatD12_720_4to3_422_Fr2:
      case keMvSurfaceFormatD12_720p50_4to3_422_Fr1:
      case keMvSurfaceFormatD12_720p50_4to3_422_Fr2:
      case keMvSurfaceFormatMpegIBPMainProfileMainLevel_420:
      case keMvSurfaceFormatMpegIBPMainProfileHighLevel_420:
      case keMvSurfaceFormatMpegIBP422ProfileMainLevel_422:
      case keMvSurfaceFormatMpegIBP422ProfileHighLevel_422:
      case keMvSurfaceFormatMpegIFrameMainProfileHighLevel_420:
      case keMvSurfaceFormatMpegIFrame422ProfileHighLevel_422:
      case keMvSurfaceFormatMpegIFrame422ProfileHighLevel_WithAlpha:
      case keMvSurfaceFormatRLE:
      case keMvSurfaceFormatEffectPatternData:
      case keMvSurfaceFormatMJpegBaseline_422:
      case keMvSurfaceFormatMJpegLossless_422:
      case keMvSurfaceFormatHDOffline:
      default:
         break;

      case keMvSurfaceFormatDvCam_411:
      case keMvSurfaceFormatDvCPro_411:
      case keMvSurfaceFormatDv50_422:
      case keMvSurfaceFormatMpegIFrameMainProfileMainLevel_420:
      case keMvSurfaceFormatMpegIFrame422ProfileMainLevel_422:
      case keMvSurfaceFormatMpegIFrame422ProfileMainLevel_WithAlpha:
         if(in_ulHeight == 486)
         {
            in_ulHeight = 480;
         }
         break;

      case keMvSurfaceFormatMpegD10_422:
         if(in_ulHeight == 486)
         {
            in_ulHeight = 512;
         }
         else if(in_ulHeight == 576)
         {
            in_ulHeight = 608;
         }
         break;
      }

      return in_ulHeight;
   }

   inline unsigned long AudioSamplesCountFromFrameRate(SMvResolutionInfo & in_rsRes)
   {
      unsigned long AudioSamplesCount;

      AudioSamplesCount = 48000 * EMvFrameRateToScale(in_rsRes.eFrameRate) / EMvFrameRateToValue(in_rsRes.eFrameRate);

      if(in_rsRes.eScanMode == keMvScanModeFirstFieldTop || in_rsRes.eScanMode == keMvScanModeSecondFieldTop)
      {
         AudioSamplesCount /= 2;
      }

      AudioSamplesCount++;

      return AudioSamplesCount;
   }

   inline EMvPolarity GetPolarityFromResolution(SMvResolutionInfo & in_rsRes)
   {
      if
         (
         in_rsRes.eScanMode == keMvScanModeProgressive
         ||
         in_rsRes.eScanMode == keMvScanModeProgressiveSegmented
         )
      {
         return keMvPolarityProgressiveFrame;
      }
      else
      {
         return keMvPolarityFirstField;
      }
   }

   inline double GetPixelAspectRatio(SMvResolutionInfo & in_sResInfo)
   {
      if(in_sResInfo.ulWidth == 720)
      {
         if(in_sResInfo.ulHeight == 480 || in_sResInfo.ulHeight == 486)
         {
            if(in_sResInfo.eAspectRatio == keMvAspectRatio_4_3)
            {
               // Frame Size = 720x486
               // Aspect Ratio = 4:3
               // Numerator = 486 * 4 = 1944
               // Denominator = 720 * 3 = 2160
               // PixelAspectRatio = 1944/2160 = 0.9
               return 0.9;
            }
            else
            {
               // Frame Size = 720x486
               // Aspect Ratio = 16:9
               // Numerator = 486 * 16 = 7776
               // Denominator = 720 * 9 = 6480
               // PixelAspectRatio = 7776/6480 = 1.2
               return 1.2;
            }
         }

         if(in_sResInfo.ulHeight == 576)
         {
            if(in_sResInfo.eAspectRatio == keMvAspectRatio_4_3)
            {
               // Frame Size = 720x576
               // Aspect Ratio = 4:3
               // Numerator = 576 * 4 = 2304
               // Denominator = 720 * 3 = 2160
               // PixelAspectRatio = 2304/2160 = 1.067
               return 1.067;
            }
            else
            {
               // Frame Size = 720x576
               // Aspect Ratio = 16:9
               // Numerator = 576 * 16 = 9216
               // Denominator = 720 * 9 = 6480
               // PixelAspectRatio = 9216/6480 = 1.422
               return 1.422;
            }
         }
      }

      if(in_sResInfo.ulWidth == 1440 && in_sResInfo.ulHeight == 1080)
      {
         // Frame Size = 1440x1080
         // Aspect Ratio = 16:9
         // Numerator = 1080 * 16 = 17280
         // Denominator = 1440 * 9 = 12960
         // PixelAspectRatio = 17280/12960 = 1.333
         return 1.333;
      }


      // Frame Size = 1920x1080
      // Aspect Ratio = 16:9
      // Numerator = 1080 * 16 = 17280
      // Denominator = 1920 * 9 = 17280
      // PixelAspectRatio = 17280/17280 = 1.0
      // or
      // Frame Size = 1280x720
      // Aspect Ratio = 16:9
      // Numerator = 720 * 16 = 11520
      // Denominator = 1920 * 9 = 11520
      // PixelAspectRatio = 11520/11520 = 1.0
      return 1.0;
   }

   inline bool GetPALResolution(SMvResolutionInfo * io_psRes)
   {
      if((io_psRes == NULL) || (io_psRes->size != sizeof(SMvResolutionInfo)))
         return false;

      io_psRes->eAspectRatio = keMvAspectRatio_4_3;
      io_psRes->eFrameRate = keMvFrameRate25;
      io_psRes->eScanMode = keMvScanModeFirstFieldTop;
      io_psRes->ulComponentBitCount = 8;
      io_psRes->ulHeight = 576;
      io_psRes->ulWidth = 720;

      return true;
   }

   inline bool GetNTSCResolution(SMvResolutionInfo * io_psRes)
   {
      if((io_psRes == NULL) || (io_psRes->size != sizeof(SMvResolutionInfo)))
         return false;

      io_psRes->eAspectRatio = keMvAspectRatio_4_3;
      io_psRes->eFrameRate = keMvFrameRate30M;
      io_psRes->eScanMode = keMvScanModeSecondFieldTop;
      io_psRes->ulComponentBitCount = 8;
      io_psRes->ulHeight = 486;
      io_psRes->ulWidth = 720;

      return true;
   }

   inline bool Get1080iResolution(SMvResolutionInfo * io_psRes, EMvFrameRate eFramerate)
   {
      if((io_psRes == NULL) || (io_psRes->size != sizeof(SMvResolutionInfo)))
         return false;

      io_psRes->eAspectRatio = keMvAspectRatio_16_9;
      io_psRes->eFrameRate = eFramerate;
      io_psRes->eScanMode = keMvScanModeFirstFieldTop;
      io_psRes->ulComponentBitCount = 8;
      io_psRes->ulHeight = 1080;
      io_psRes->ulWidth = 1920;

      return true;
   }

   inline bool Get720pResolution(SMvResolutionInfo * io_psRes, EMvFrameRate eFramerate)
   {
      if((io_psRes == NULL) || (io_psRes->size != sizeof(SMvResolutionInfo)))
         return false;

      io_psRes->eAspectRatio = keMvAspectRatio_16_9;
      io_psRes->eFrameRate = eFramerate;
      io_psRes->eScanMode = keMvScanModeProgressive;
      io_psRes->ulComponentBitCount = 8;
      io_psRes->ulHeight = 720;
      io_psRes->ulWidth = 1280;

      return true;
   }

   inline bool IsChannelTypeValid(EMvChannelType in_eChannelType)
   {
      if(in_eChannelType != keChannelTypeInvalid
         && in_eChannelType < keChannelTypeLast
         && !(
         in_eChannelType != 1    // We support only even channel types except for mono, which is odd
         && (in_eChannelType % 2)
         ))
      {
         return true;
      }
      return false;
   }

   inline bool IsMemoryLocationInHost(EMvMemoryLocation in_eMemoryLocation)
   {
      return ((in_eMemoryLocation == keMvMemoryLocationHost) || (in_eMemoryLocation == keMvMemoryLocationUser)) ? true : false;
   }

   inline bool IsStreamingCodec(GUID* in_pguidCodec)
   {
      if(*in_pguidCodec == CLSID_MvcAVCIntra
         || *in_pguidCodec == CLSID_MvcProRes
         || *in_pguidCodec == CLSID_MvcH264SWDecoder
         || *in_pguidCodec == CLSID_MvcH264SWDecoder2
         || *in_pguidCodec == CLSID_MvcDNxHDCodec
         || *in_pguidCodec == CLSID_MvfAVCH264HardwareCodec
         || *in_pguidCodec == CLSID_MvcH264SWEncoder
         || *in_pguidCodec == CLSID_MvcH264QSVEncoder
         || *in_pguidCodec == CLSID_MvcMPEG4SStPCodec)
         return true;
      return false;
   }

   inline bool IsStreamingCodec(EMvSurfaceFormat in_eSurfaceFormat)
   {
      switch(in_eSurfaceFormat)
      {
      case keMvSurfaceFormatAVC:
      case keMvSurfaceFormatAVCIntra:
      case keMvSurfaceFormatAVCIntraClass50:
      case keMvSurfaceFormatAVCIntraClass100:
      case keMvSurfaceFormatProRes:
      case keMvSurfaceFormatDNxHD:
      case keMvSurfaceFormatMPEG4SStP:
         return true;
      default:
         // remove compilation warning [-Wswitch] for all enumeration value not handled in switch
         break;
      }
      return false;
   }

   inline bool IsStandardCodec(GUID* in_pguidCodec)
   {
      if(*in_pguidCodec == CLSID_MvcRLE
         || *in_pguidCodec == CLSID_MvcDv
         || *in_pguidCodec == CLSID_MvcDv100
         || *in_pguidCodec == CLSID_MvcD10
         || *in_pguidCodec == CLSID_MvcIBP
         || *in_pguidCodec == CLSID_MvcMJpeg
         || *in_pguidCodec == CLSID_MvMpegStream)
         return true;
      return false;
   }

   inline bool IsStandardCodec(EMvSurfaceFormat in_eSurfaceFormat)
   {
      switch(in_eSurfaceFormat)
      {
      case keMvSurfaceFormatDvCam_411:
      case keMvSurfaceFormatDvCam_420:
      case keMvSurfaceFormatDvCPro_411:
      case keMvSurfaceFormatDv50_422:
      case keMvSurfaceFormatD12_1080_3to2_422:
      case keMvSurfaceFormatD12_1080_4to3_422:
      case keMvSurfaceFormatD12_720_4to3_422_Fr1:
      case keMvSurfaceFormatD12_720_4to3_422_Fr2:
      case keMvSurfaceFormatMpegIBPMainProfileMainLevel_420:
      case keMvSurfaceFormatMpegIBPMainProfileHighLevel_420:
      case keMvSurfaceFormatMpegIBP422ProfileMainLevel_422:
      case keMvSurfaceFormatMpegIBP422ProfileHighLevel_422:
      case keMvSurfaceFormatMpegIFrameMainProfileMainLevel_420:
      case keMvSurfaceFormatMpegIFrameMainProfileHighLevel_420:
      case keMvSurfaceFormatMpegIFrame422ProfileMainLevel_422:
      case keMvSurfaceFormatMpegIFrame422ProfileHighLevel_422:
      case keMvSurfaceFormatMpegD10_422:
      case keMvSurfaceFormatRLE:
      case keMvSurfaceFormatMJpegBaseline_422:
      case keMvSurfaceFormatMJpegLossless_422:
      case keMvSurfaceFormatHDOffline:
      case keMvSurfaceFormatMpegIFrame422ProfileMainLevel_WithAlpha:
      case keMvSurfaceFormatMpegIFrame422ProfileHighLevel_WithAlpha:
      case keMvSurfaceFormatD12_720p50_4to3_422_Fr1:
      case keMvSurfaceFormatD12_720p50_4to3_422_Fr2:
      case keMvSurfaceFormatRLEAnimation:
      case keMvSurfaceFormatRLEAnimation_WithAlpha:
         return true;
      default:
         // remove compilation warning [-Wswitch] for all enumeration value not handled in switch
         break;
      }
      return false;
   }

   inline HRESULT GetSourcePosInDestinationRect(SMvResolutionInfo &in_rsInputResolutionInfo,
      SMvRect           &out_rsSrcRect,
      bool              &out_rbUseSrcRect,
      SMvResolutionInfo &in_rsOutputResolutionInfo,
      SMvRect           &out_rsDstRect,
      bool              &out_rbUseDstRect)
   {
      HRESULT hr = MV_NOERROR;

      out_rbUseSrcRect = false;
      out_rbUseDstRect = false;
      if(in_rsInputResolutionInfo.size != sizeof(SMvResolutionInfo))
         return MV_E_INVALID_PARAMETER;

      if(in_rsOutputResolutionInfo.size != sizeof(SMvResolutionInfo))
         return MV_E_INVALID_PARAMETER;

      out_rsSrcRect.lLeft = 0;
      out_rsSrcRect.lTop = 0;
      out_rsSrcRect.lRight = in_rsInputResolutionInfo.ulWidth;
      out_rsSrcRect.lBottom = in_rsInputResolutionInfo.ulHeight;
      if((in_rsInputResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || in_rsInputResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) && (!IsScanMode_Progressive_Or_PsF_Or_IFF(in_rsOutputResolutionInfo.eScanMode)))
         out_rsSrcRect.lBottom /= 2;

      out_rsDstRect.lLeft = 0;
      out_rsDstRect.lTop = 0;
      out_rsDstRect.lRight = in_rsOutputResolutionInfo.ulWidth;
      out_rsDstRect.lBottom = in_rsOutputResolutionInfo.ulHeight;
      if(in_rsOutputResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || in_rsOutputResolutionInfo.eScanMode == keMvScanModeSecondFieldTop)
         out_rsDstRect.lBottom /= 2;

      // Get pixel aspect ratios and aspect ratios.
      double dDestPAR = GetPixelAspectRatio(in_rsOutputResolutionInfo);
      double dSourcePAR = GetPixelAspectRatio(in_rsInputResolutionInfo);
      double dDestAR = dDestPAR * double(in_rsOutputResolutionInfo.ulWidth) / in_rsOutputResolutionInfo.ulHeight;
      double dSourceAR = dSourcePAR * double(in_rsInputResolutionInfo.ulWidth) / in_rsInputResolutionInfo.ulHeight;

      // Special Case: 720x480 to 720x486. We specify the same rect height so it won't scale the image
      if(out_rsDstRect.lRight == 720 && out_rsSrcRect.lRight == 720 && out_rsDstRect.lBottom == 486 && out_rsSrcRect.lBottom == 480)
      {
         out_rsDstRect.lTop = 2;
         out_rsDstRect.lBottom = 482;
         out_rbUseDstRect = true;
      }
      else if(out_rsDstRect.lRight == 720 && out_rsSrcRect.lRight == 720 && out_rsDstRect.lBottom == 480 && out_rsSrcRect.lBottom == 486)
      {
         out_rsSrcRect.lTop = 2;
         out_rsSrcRect.lBottom = 482;
         out_rbUseSrcRect = true;
      }
      else if(out_rsDstRect.lRight == 720 && out_rsSrcRect.lRight == 720 && out_rsDstRect.lBottom == 243 && out_rsSrcRect.lBottom == 240)
      {
         out_rsDstRect.lTop = 1;
         out_rsDstRect.lBottom = 241;
         out_rbUseDstRect = true;
      }
      else if(out_rsDstRect.lRight == 720 && out_rsSrcRect.lRight == 720 && out_rsDstRect.lBottom == 240 && out_rsSrcRect.lBottom == 243)
      {
         out_rsSrcRect.lTop = 1;
         out_rsSrcRect.lBottom = 241;
         out_rbUseSrcRect = true;
      }
      else if(in_rsInputResolutionInfo.eAspectRatio == in_rsOutputResolutionInfo.eAspectRatio)
      {
         if(memcmp(&(out_rsSrcRect), &(out_rsDstRect), sizeof(SMvRect)))
            out_rbUseDstRect = true;
         return hr;
      }
      else if(dSourceAR > dDestAR)
      {
         unsigned long ulOutputHeight = in_rsOutputResolutionInfo.ulHeight;
         if(in_rsOutputResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || in_rsOutputResolutionInfo.eScanMode == keMvScanModeSecondFieldTop)
            ulOutputHeight /= 2;

         // Source is going to be letter boxed in destination.  
         // Adjusted height of the rectangle.
         int iHeight = int((ulOutputHeight*dDestAR) / dSourceAR + 0.5);
         iHeight -= (iHeight % 8);
         out_rsDstRect.lTop = (unsigned int)(ulOutputHeight - iHeight) / 2;
         int iAlign = int(out_rsDstRect.lTop % 8);
         if(iAlign)
            out_rsDstRect.lTop += (8 - iAlign);
         out_rsDstRect.lBottom = (unsigned int)(out_rsDstRect.lTop + iHeight);
         out_rbUseDstRect = true;
      }
      else //if(dSourceAR < dDestAR)
      {
         // Source is going to be pillar boxed in destination.
         // Calculate destination width.
         int iWidth = int((in_rsOutputResolutionInfo.ulHeight*dDestAR) / dSourceAR + 0.5);
         out_rsDstRect.lLeft = (unsigned int)(in_rsOutputResolutionInfo.ulWidth - iWidth) / 2;
         out_rsDstRect.lRight = (unsigned int)(out_rsDstRect.lLeft + iWidth);
         out_rbUseDstRect = true;
      }

      return hr;
   }

   inline void GetARFraction(EMvAspectRatio in_eAR, uint32_t& io_ui32Numerator, uint32_t& io_ui32Denominator)
   {
      switch(in_eAR)
      {
      case(keMvAspectRatio_4_3) :
         io_ui32Numerator = 4;
         io_ui32Denominator = 3;
         break;
      case(keMvAspectRatio_16_9) :
         io_ui32Numerator = 16;
         io_ui32Denominator = 9;
         break;
      case(keMvAspectRatio_256_135) :
         io_ui32Numerator = 256;
         io_ui32Denominator = 135;
         break;
      default:
         // should not reach default case
         ASSERT(false);
         break;
      }
   }

   inline void ValidateResolution(SMvResolutionInfo &io_rsValidatedResolutionInfo)
   {
      if(io_rsValidatedResolutionInfo.size != sizeof(SMvResolutionInfo))
         return;

      if(io_rsValidatedResolutionInfo.ulWidth == 1280 && io_rsValidatedResolutionInfo.ulHeight == 1080)
      {
         io_rsValidatedResolutionInfo.ulWidth = 1920;
      }

      if(io_rsValidatedResolutionInfo.ulWidth == 1440 && io_rsValidatedResolutionInfo.ulHeight == 1080)
      {
         io_rsValidatedResolutionInfo.ulWidth = 1920;
      }

      if(io_rsValidatedResolutionInfo.ulWidth == 704 && io_rsValidatedResolutionInfo.ulHeight == 480)
      {
         io_rsValidatedResolutionInfo.ulWidth = 720;
         io_rsValidatedResolutionInfo.ulHeight = 486;
      }

      if(io_rsValidatedResolutionInfo.ulWidth == 720 && io_rsValidatedResolutionInfo.ulHeight == 480)
         io_rsValidatedResolutionInfo.ulHeight = 486;
      if(io_rsValidatedResolutionInfo.ulWidth == 720 && io_rsValidatedResolutionInfo.ulHeight == 512)
         io_rsValidatedResolutionInfo.ulHeight = 486;
      if(io_rsValidatedResolutionInfo.ulWidth == 720 && io_rsValidatedResolutionInfo.ulHeight == 608)
         io_rsValidatedResolutionInfo.ulHeight = 576;

      // proxy size?
      if(io_rsValidatedResolutionInfo.ulWidth < 720 && io_rsValidatedResolutionInfo.ulHeight < 480 && io_rsValidatedResolutionInfo.eFrameRate == keMvFrameRate30M)
      {
         io_rsValidatedResolutionInfo.ulWidth = 720;
         io_rsValidatedResolutionInfo.ulHeight = 486;
      }

      if(io_rsValidatedResolutionInfo.ulWidth < 720 && io_rsValidatedResolutionInfo.ulHeight < 576 && io_rsValidatedResolutionInfo.eFrameRate == keMvFrameRate25)
      {
         io_rsValidatedResolutionInfo.ulWidth = 720;
         io_rsValidatedResolutionInfo.ulHeight = 576;
      }

      if(io_rsValidatedResolutionInfo.ulWidth < 1280 && io_rsValidatedResolutionInfo.ulHeight < 720 && io_rsValidatedResolutionInfo.eFrameRate == keMvFrameRate60M)
      {
         io_rsValidatedResolutionInfo.ulWidth = 1280;
         io_rsValidatedResolutionInfo.ulHeight = 720;
      }

      if(io_rsValidatedResolutionInfo.ulWidth < 1280 && io_rsValidatedResolutionInfo.ulHeight < 720 && io_rsValidatedResolutionInfo.eFrameRate == keMvFrameRate50)
      {
         io_rsValidatedResolutionInfo.ulWidth = 1280;
         io_rsValidatedResolutionInfo.ulHeight = 720;
      }

      // input is NTSC progressive
      if(io_rsValidatedResolutionInfo.ulWidth == 720 && io_rsValidatedResolutionInfo.ulHeight == 486)
         if(IsScanMode_Progressive_Or_PsF_Or_IFF(io_rsValidatedResolutionInfo.eScanMode) && io_rsValidatedResolutionInfo.eFrameRate == keMvFrameRate30M)
            io_rsValidatedResolutionInfo.eScanMode = keMvScanModeSecondFieldTop;

      // input is PAL progressive
      if(io_rsValidatedResolutionInfo.ulWidth == 720 && io_rsValidatedResolutionInfo.ulHeight == 576)
         if(IsScanMode_Progressive_Or_PsF_Or_IFF(io_rsValidatedResolutionInfo.eScanMode) && io_rsValidatedResolutionInfo.eFrameRate == keMvFrameRate25)
            io_rsValidatedResolutionInfo.eScanMode = keMvScanModeFirstFieldTop;

      // input is 1080 P, PsF or IFF with frame rate 25, 30 or 30M
      if(io_rsValidatedResolutionInfo.ulWidth == 1920 && io_rsValidatedResolutionInfo.ulHeight == 1080)
      {
         // for PsF ==> FFT;
         if(io_rsValidatedResolutionInfo.eScanMode == keMvScanModeProgressiveSegmented)
            if(io_rsValidatedResolutionInfo.eFrameRate == keMvFrameRate30M || io_rsValidatedResolutionInfo.eFrameRate == keMvFrameRate30 || io_rsValidatedResolutionInfo.eFrameRate == keMvFrameRate25)
               io_rsValidatedResolutionInfo.eScanMode = keMvScanModeFirstFieldTop;

         // for IFF ==> FFT
         if(io_rsValidatedResolutionInfo.eScanMode == keMvScanModeInterlacedFieldsInAFrame)
            if(io_rsValidatedResolutionInfo.eFrameRate == keMvFrameRate30M || io_rsValidatedResolutionInfo.eFrameRate == keMvFrameRate30 || io_rsValidatedResolutionInfo.eFrameRate == keMvFrameRate25)
               io_rsValidatedResolutionInfo.eScanMode = keMvScanModeFirstFieldTop;
      }
   }

   inline void ValidateResolution(SMvResolutionInfo &io_rsResolutionInfo, SMvResolutionInfo &out_rsValidatedResolutionInfo)
   {
      if(io_rsResolutionInfo.size != sizeof(SMvResolutionInfo))
         return;

      if(io_rsResolutionInfo.ulWidth == 1280 && io_rsResolutionInfo.ulHeight == 1080)
      {
         io_rsResolutionInfo.ulWidth = 1920;
      }

      if(io_rsResolutionInfo.ulWidth == 1440 && io_rsResolutionInfo.ulHeight == 1080)
      {
         io_rsResolutionInfo.ulWidth = 1920;
      }

      if(io_rsResolutionInfo.ulWidth == 704 && io_rsResolutionInfo.ulHeight == 480)
      {
         io_rsResolutionInfo.ulWidth = 720;
         io_rsResolutionInfo.ulHeight = 486;
      }
      else if(io_rsResolutionInfo.ulWidth == 720 && io_rsResolutionInfo.ulHeight == 480)
      {
         io_rsResolutionInfo.ulHeight = 486;
      }
      else if(io_rsResolutionInfo.ulWidth == 720 && io_rsResolutionInfo.ulHeight == 512)
      {
         io_rsResolutionInfo.ulHeight = 486;
      }
      else if(io_rsResolutionInfo.ulWidth == 720 && io_rsResolutionInfo.ulHeight == 608)
      {
         io_rsResolutionInfo.ulHeight = 576;
      }

      out_rsValidatedResolutionInfo = io_rsResolutionInfo;

      ValidateResolution(out_rsValidatedResolutionInfo);
   }

   inline void AdjustForPSFResolution(SMvResolutionInfo & io_rsResolution)
   {
      if(io_rsResolution.ulHeight == 1080 &&
         io_rsResolution.ulWidth == 1920 &&
         io_rsResolution.eScanMode == keMvScanModeProgressive &&
         io_rsResolution.eFrameRate < keMvFrameRate50)
      {
         io_rsResolution.eScanMode = keMvScanModeProgressiveSegmented;
      }
   }

   inline bool IsEqualMemoryLocation(EMvMemoryLocation in_eInputLocation, EMvMemoryLocation in_eOutputLocation)
   {
      if(in_eInputLocation == keMvMemoryLocationUser)
         in_eInputLocation = keMvMemoryLocationHost;
      if(in_eOutputLocation == keMvMemoryLocationUser)
         in_eOutputLocation = keMvMemoryLocationHost;
      return (in_eInputLocation == in_eOutputLocation);
   }

   inline EMvH264Level ComputeMinH264Level(
      uint16_t       in_ui16Height,
      uint16_t       in_ui16Width,
      EMvH264Profile in_eProfile,
      float          in_fFrameRate,
      uint32_t       in_ui32TargetBitRateInBitsPerSec)
   {
      uint32_t ui32MBNumber = (in_ui16Height / 16) * (in_ui16Width / 16);
      uint32_t ui32MBperSec = (uint32_t)(ceil(ui32MBNumber * in_fFrameRate));
      uint32_t ui32BitRateInKbitsPerSec = in_ui32TargetBitRateInBitsPerSec / 1000;
      EMvH264Level eLevel = keMvH264ProfileLevelInvalid;

      if(in_eProfile != keMvH264ProfileHigh) // Main or Baseline profile
      {
         if((ui32MBNumber <= 99) && (ui32MBperSec <= 1485) && (ui32BitRateInKbitsPerSec <= 64))
            eLevel = keMvH264ProfileLevel1;
         else if((ui32MBNumber <= 99) && (ui32MBperSec <= 1485) && (ui32BitRateInKbitsPerSec <= 128))
            eLevel = keMvH264ProfileLevel1b;
         else if((ui32MBNumber <= 396) && (ui32MBperSec <= 3000) && (ui32BitRateInKbitsPerSec <= 192))
            eLevel = keMvH264ProfileLevel11;
         else if((ui32MBNumber <= 396) && (ui32MBperSec <= 6000) && (ui32BitRateInKbitsPerSec <= 384))
            eLevel = keMvH264ProfileLevel12;
         else if((ui32MBNumber <= 396) && (ui32MBperSec <= 11880) && (ui32BitRateInKbitsPerSec <= 768))
            eLevel = keMvH264ProfileLevel13;
         else if((ui32MBNumber <= 396) && (ui32MBperSec <= 11880) && (ui32BitRateInKbitsPerSec <= 2000))
            eLevel = keMvH264ProfileLevel2;
         else if((ui32MBNumber <= 792) && (ui32MBperSec <= 19800) && (ui32BitRateInKbitsPerSec <= 4000))
            eLevel = keMvH264ProfileLevel21;
         else if((ui32MBNumber <= 1620) && (ui32MBperSec <= 20250) && (ui32BitRateInKbitsPerSec <= 4000))
            eLevel = keMvH264ProfileLevel22;
         else if((ui32MBNumber <= 1620) && (ui32MBperSec <= 40500) && (ui32BitRateInKbitsPerSec <= 10000))
            eLevel = keMvH264ProfileLevel3;
         else if((ui32MBNumber <= 3600) && (ui32MBperSec <= 108000) && (ui32BitRateInKbitsPerSec <= 14000))
            eLevel = keMvH264ProfileLevel31;
         else if((ui32MBNumber <= 5120) && (ui32MBperSec <= 216000) && (ui32BitRateInKbitsPerSec <= 20000))
            eLevel = keMvH264ProfileLevel32;
         else if((ui32MBNumber <= 8192) && (ui32MBperSec <= 245760) && (ui32BitRateInKbitsPerSec <= 20000))
            eLevel = keMvH264ProfileLevel4;
         else if((ui32MBNumber <= 8192) && (ui32MBperSec <= 245760) && (ui32BitRateInKbitsPerSec <= 50000))
            eLevel = keMvH264ProfileLevel41;
         else if((ui32MBNumber <= 8704) && (ui32MBperSec <= 522240) && (ui32BitRateInKbitsPerSec <= 50000))
            eLevel = keMvH264ProfileLevel42;
         else if((ui32MBNumber <= 22080) && (ui32MBperSec <= 589824) && (ui32BitRateInKbitsPerSec <= 135000))
            eLevel = keMvH264ProfileLevel5;
         else if((ui32MBNumber <= 36864) && (ui32MBperSec <= 983040) && (ui32BitRateInKbitsPerSec <= 240000))
            eLevel = keMvH264ProfileLevel51;
      }
      else // High profile
      {
         if((ui32MBNumber <= 99) && (ui32MBperSec <= 1485) && (ui32BitRateInKbitsPerSec <= 80))
            eLevel = keMvH264ProfileLevel1;
         else if((ui32MBNumber <= 99) && (ui32MBperSec <= 1485) && (ui32BitRateInKbitsPerSec <= 160))
            eLevel = keMvH264ProfileLevel1b;
         else if((ui32MBNumber <= 396) && (ui32MBperSec <= 3000) && (ui32BitRateInKbitsPerSec <= 240))
            eLevel = keMvH264ProfileLevel11;
         else if((ui32MBNumber <= 396) && (ui32MBperSec <= 6000) && (ui32BitRateInKbitsPerSec <= 480))
            eLevel = keMvH264ProfileLevel12;
         else if((ui32MBNumber <= 396) && (ui32MBperSec <= 11880) && (ui32BitRateInKbitsPerSec <= 960))
            eLevel = keMvH264ProfileLevel13;
         else if((ui32MBNumber <= 396) && (ui32MBperSec <= 11880) && (ui32BitRateInKbitsPerSec <= 2500))
            eLevel = keMvH264ProfileLevel2;
         else if((ui32MBNumber <= 792) && (ui32MBperSec <= 19800) && (ui32BitRateInKbitsPerSec <= 5000))
            eLevel = keMvH264ProfileLevel21;
         else if((ui32MBNumber <= 1620) && (ui32MBperSec <= 20250) && (ui32BitRateInKbitsPerSec <= 5000))
            eLevel = keMvH264ProfileLevel22;
         else if((ui32MBNumber <= 1620) && (ui32MBperSec <= 40500) && (ui32BitRateInKbitsPerSec <= 12500))
            eLevel = keMvH264ProfileLevel3;
         else if((ui32MBNumber <= 3600) && (ui32MBperSec <= 108000) && (ui32BitRateInKbitsPerSec <= 17500))
            eLevel = keMvH264ProfileLevel31;
         else if((ui32MBNumber <= 5120) && (ui32MBperSec <= 216000) && (ui32BitRateInKbitsPerSec <= 25000))
            eLevel = keMvH264ProfileLevel32;
         else if((ui32MBNumber <= 8192) && (ui32MBperSec <= 245760) && (ui32BitRateInKbitsPerSec <= 25000))
            eLevel = keMvH264ProfileLevel4;
         else if((ui32MBNumber <= 8192) && (ui32MBperSec <= 245760) && (ui32BitRateInKbitsPerSec <= 62500))
            eLevel = keMvH264ProfileLevel41;
         else if((ui32MBNumber <= 8704) && (ui32MBperSec <= 522240) && (ui32BitRateInKbitsPerSec <= 62500))
            eLevel = keMvH264ProfileLevel42;
         else if((ui32MBNumber <= 22080) && (ui32MBperSec <= 589824) && (ui32BitRateInKbitsPerSec <= 168750))
            eLevel = keMvH264ProfileLevel5;
         else if((ui32MBNumber <= 36864) && (ui32MBperSec <= 983040) && (ui32BitRateInKbitsPerSec <= 300000))
            eLevel = keMvH264ProfileLevel51;
      }

      return eLevel;
   }

   inline float ConvertEMvFrameRateToFloat(EMvFrameRate in_eFrameRate)
   {
      float fValue;

      switch(in_eFrameRate)
      {
      case keMvFrameRate24:         fValue = 24.0;             break;
      case keMvFrameRate24M:        fValue = (float)(24000.0 / 1001.0);   break;
      case keMvFrameRate25:         fValue = 25.0;             break;
      case keMvFrameRate30:         fValue = 30.0;             break;
      case keMvFrameRate30M:        fValue = (float)(30000.0 / 1001.0);   break;
      case keMvFrameRate50:         fValue = 50.0;             break;
      case keMvFrameRate60:         fValue = 60.0;             break;
      case keMvFrameRate60M:        fValue = (float)(60000.0 / 1001.0);   break;
      default:                      fValue = (float)(30000.0 / 1001.0);   break;
      }

      return fValue;
   }

   inline void CopySurfaceDescriptionToCreateSurfaceDescription(SMvSurfaceDescription &in_sDesc, SMvCreateSurfaceDescription &out_sCreateDesc)
   {
      out_sCreateDesc.size = sizeof(SMvCreateSurfaceDescription);
      out_sCreateDesc.ulWidth = in_sDesc.ulWidth;
      out_sCreateDesc.ulHeight = in_sDesc.ulHeight;
      out_sCreateDesc.ulDepth = in_sDesc.ulDepth;
      out_sCreateDesc.ulComponentBitCount = in_sDesc.ulComponentBitCount;
      out_sCreateDesc.ulMipmapCount = in_sDesc.ulMipmapCount;
      out_sCreateDesc.eFormat = in_sDesc.eFormat;
      out_sCreateDesc.eType = in_sDesc.eType;
      out_sCreateDesc.eMemoryLocation = in_sDesc.eMemoryLocation;
      out_sCreateDesc.ePolarity = in_sDesc.ePolarity;
      out_sCreateDesc.eImageOrigin = in_sDesc.eImageOrigin;
      out_sCreateDesc.eColorimetry = in_sDesc.eColorimetry;
      out_sCreateDesc.ptDestinationPosition = in_sDesc.ptDestinationPosition;
      out_sCreateDesc.bUseAlpha = in_sDesc.bUseAlpha;
      out_sCreateDesc.bIsVideoShaped = in_sDesc.bIsVideoShaped;
   }

   inline void CopyResolutionToCreateSurfaceDescription(SMvResolutionInfo &in_sResInfo, SMvCreateSurfaceDescription &out_sCreateDesc)
   {
      out_sCreateDesc.size = sizeof(SMvCreateSurfaceDescription);
      out_sCreateDesc.ulWidth = in_sResInfo.ulWidth;
      out_sCreateDesc.ulHeight = in_sResInfo.ulHeight;
      if(in_sResInfo.eScanMode == keMvScanModeFirstFieldTop || in_sResInfo.eScanMode == keMvScanModeSecondFieldTop)
         out_sCreateDesc.ulHeight /= 2;
      out_sCreateDesc.ulDepth = 1;
      out_sCreateDesc.ulComponentBitCount = in_sResInfo.ulComponentBitCount;
      out_sCreateDesc.ulMipmapCount = 0;
      out_sCreateDesc.eFormat = keMvSurfaceFormatYUYV422;
      out_sCreateDesc.eType = keMvSurfaceType2D;
      out_sCreateDesc.eMemoryLocation = keMvMemoryLocationHost;
      switch(in_sResInfo.eScanMode)
      {
      case keMvScanModeFirstFieldTop:
      case keMvScanModeSecondFieldTop:
      {
         out_sCreateDesc.ePolarity = keMvPolarityFirstField;
         break;
      }
      case keMvScanModeInterlacedFieldsInAFrame:
      {
         out_sCreateDesc.ePolarity = keMvPolarityInterlacedFieldsInAFrame;
         break;
      }
      case keMvScanModeProgressive:
      case keMvScanModeProgressiveSegmented:
      default:
      {
         out_sCreateDesc.ePolarity = keMvPolarityProgressiveFrame;
         break;
      }
      }
      out_sCreateDesc.eImageOrigin = keMvImageOriginTopLeft;
      out_sCreateDesc.eColorimetry = GetColorimetryFromResolution(in_sResInfo);
      out_sCreateDesc.ptDestinationPosition.fX = 0.0f;
      out_sCreateDesc.ptDestinationPosition.fY = 0.0f;
      out_sCreateDesc.bUseAlpha = false;
      out_sCreateDesc.bIsVideoShaped = false;
   }

   inline void CopyAudioSamplesDescriptionToCreateAudioSamplesDescription(SMvAudioSamplesDescription &in_sDesc, SMvCreateAudioSamplesDescription &out_sCreateDesc)
   {
      out_sCreateDesc.size = sizeof(SMvCreateAudioSamplesDescription);
      out_sCreateDesc.sWaveFormat = in_sDesc.sWaveFormat;
      out_sCreateDesc.bHasFadeIn = in_sDesc.bHasFadeIn;
      out_sCreateDesc.bHasFadeOut = in_sDesc.bHasFadeOut;
      out_sCreateDesc.eMemoryLocation = in_sDesc.eMemoryLocation;
      out_sCreateDesc.ePolarity = in_sDesc.ePolarity;
      out_sCreateDesc.ulMaxBufferSize = 2002 * in_sDesc.sWaveFormat.eChannelType * 4;
   }

   inline void CopyResolutionToCreateAudioSamplesDescription(SMvResolutionInfo &in_sResInfo, EMvChannelType in_eChannelType, EMvAudioBitsPerSample in_eValidAudioBitsPerSample, SMvCreateAudioSamplesDescription &out_sCreateDesc)
   {
      EMvAudioBitsPerSample eAudioBitsPerSample = keAudioBitsPerSample16;
      if(in_eValidAudioBitsPerSample > keAudioBitsPerSample16)
         eAudioBitsPerSample = keAudioBitsPerSample32;
      unsigned long ulSampleCount = static_cast<unsigned long>(MvGetAudioSamplesFromReferencedVideoUnits(1, 0, in_sResInfo));

      out_sCreateDesc.size = sizeof(SMvCreateAudioSamplesDescription);
      out_sCreateDesc.sWaveFormat.size = sizeof(SMvaWaveFormatInfo);
      out_sCreateDesc.bHasFadeIn = false;
      out_sCreateDesc.bHasFadeOut = false;
      out_sCreateDesc.eMemoryLocation = keMvMemoryLocationHost;
      switch(in_sResInfo.eScanMode)
      {
      case keMvScanModeFirstFieldTop:
      case keMvScanModeSecondFieldTop:
      {
         out_sCreateDesc.ePolarity = keMvPolarityFirstField;
         break;
      }
      case keMvScanModeInterlacedFieldsInAFrame:
      {
         out_sCreateDesc.ePolarity = keMvPolarityInterlacedFieldsInAFrame;
         break;
      }
      case keMvScanModeProgressive:
      case keMvScanModeProgressiveSegmented:
      default:
      {
         out_sCreateDesc.ePolarity = keMvPolarityProgressiveFrame;
         break;
      }
      }
      out_sCreateDesc.sWaveFormat.eChannelType = in_eChannelType;
      out_sCreateDesc.sWaveFormat.eDataType = keAudioDataTypePCM;
      out_sCreateDesc.sWaveFormat.ulSamplesPerSec = 48000; // 48 kHz audio
      out_sCreateDesc.sWaveFormat.ulValidBitsPerSample = in_eValidAudioBitsPerSample;
      out_sCreateDesc.sWaveFormat.ulBitsPerSample = eAudioBitsPerSample;
      out_sCreateDesc.ulMaxBufferSize = ulSampleCount * in_eChannelType * 4;
   }
}
