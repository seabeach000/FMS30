//////////////////////////////////////////////////////////////////////////////////
//
//  (c) Copyright Matrox Electronic Systems Ltd., 2003. All rights reserved. 
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

#include "mvIODefinitions.h"

#ifdef MAC_PLATFORM
namespace com_matrox_vpg_SDK
{
#endif


// DOM-IGNORE-BEGIN
// Extracted from the HQ System clock specification
// LUT Info:                    SD/HD    Scan modes         Frame rates    Nb Infos
const unsigned int kauiClockLUT  [2] [keMvScanModeLast] [keMvFrameRateLast] [3] =
{  
   // SD Tables
   {
      // keMvScanModeInvalid
      {
      //  D    E   TRIPLE_DUR
         {0,   0,    0},  // keMvFrameRateInvalid
         {0,   0,    0},  // keMvFrameRate24
         {0,   0,    0},  // keMvFrameRate24M
         {0,   0,    0},  // keMvFrameRate25
         {0,   0,    0},  // keMvFrameRate30
         {0,   0,    0},  // keMvFrameRate30M
         {0,   0,    0},  // keMvFrameRate50
         {0,   0,    0},  // keMvFrameRate60
         {0,   0,    0},  // keMvFrameRate60M
         {0,   0,    0}   // keMvFrameRateVariable
      },
      // keMvScanModeFirstFieldTop
      {
      //  D    E           TRIPLE_DUR
         {0,   0,             0},      // keMvFrameRateInvalid
         {0,   0,             0},      // keMvFrameRate24
         {0,   0,             0},      // keMvFrameRate24M
         {4,   270000 + 432,  150000}, // keMvFrameRate25      // Since the number of lines are not odd for every field,
         {4,   0,             125000}, // keMvFrameRate30      // we must add the number of pixel of half of a line
         {4,   225225 + 429,  125125}, // keMvFrameRate30M     
         {0,   0,             0},      // keMvFrameRate50      
         {0,   0,             0},      // keMvFrameRate60
         {0,   0,             0},      // keMvFrameRate60M
         {0,   0,             0}       // keMvFrameRateVariable
      },
      // keMvScanModeSecondFieldTop
      {
      //  D    E           TRIPLE_DUR
         {0,   0,             0},      // keMvFrameRateInvalid
         {0,   0,             0},      // keMvFrameRate24
         {0,   0,             0},      // keMvFrameRate24M
         {4,   270000 + 432,  150000}, // keMvFrameRate25      // Since the number of lines are not odd for every field,
         {4,   0,             125000}, // keMvFrameRate30      // we must add the number of pixel of half of a line
         {4,   225225 + 429,  125125}, // keMvFrameRate30M     
         {0,   0,             0},      // keMvFrameRate50      
         {0,   0,             0},      // keMvFrameRate60
         {0,   0,             0},      // keMvFrameRate60M
         {0,   0,             0}       // keMvFrameRateVariable
      },
      // keMvScanModeProgressive
      {
      //  D    E     TRIPLE_DUR
         {0,   0,       0},      // keMvFrameRateInvalid
         {10,  309375,  125000}, // keMvFrameRate24
         {10,  309375,  125125}, // keMvFrameRate24M
         {8,   270000,  150000}, // keMvFrameRate25
         {8,   0,       125000}, // keMvFrameRate30
         {8,   225225,  125125}, // keMvFrameRate30M     
         {4,   270000,  150000}, // keMvFrameRate50
         {4,   0,       125000}, // keMvFrameRate60
         {4,   225225,  125125}, // keMvFrameRate60M     
         {0,   0,       0}       // keMvFrameRateVariable
      },
      // keMvScanModeProgressiveSegmented
      {
      //  D    E          TRIPLE_DUR
         {0,   0,             0},  // keMvFrameRateInvalid
         {0,   0,             0},  // keMvFrameRate24
         {0,   0,             0},  // keMvFrameRate24M
         {8,   270000,        150000}, // keMvFrameRate25
         {8,   0,             125000},  // keMvFrameRate30
         {8,   225225 + 429,  125125}, // keMvFrameRate30M     
         {0,   0,             0},  // keMvFrameRate50
         {0,   0,             0},  // keMvFrameRate60
         {0,   0,             0},  // keMvFrameRate60M
         {0,   0,             0}   // keMvFrameRateVariable
      },
      // keMvScanModeInterlacedFieldsInAFrame
      {
         //  D    E          TRIPLE_DUR
         {0,   0,             0},  // keMvFrameRateInvalid
         {0,   0,             0},  // keMvFrameRate24
         {0,   0,             0},  // keMvFrameRate24M
         {8,   270000,        150000}, // keMvFrameRate25
         {8,   0,             125000},  // keMvFrameRate30
         {8,   225225 + 429,  125125}, // keMvFrameRate30M     
         {0,   0,             0},  // keMvFrameRate50
         {0,   0,             0},  // keMvFrameRate60
         {0,   0,             0},  // keMvFrameRate60M
         {0,   0,             0}   // keMvFrameRateVariable
      }
   },
   // HD Tables
   {
      // keMvScanModeInvalid
      {
      //  D    E     TRIPLE_DUR
         {0,   0,       0},  // keMvFrameRateInvalid
         {0,   0,       0},  // keMvFrameRate24
         {0,   0,       0},  // keMvFrameRate24M
         {0,   0,       0},  // keMvFrameRate25
         {0,   0,       0},  // keMvFrameRate30
         {0,   0,       0},  // keMvFrameRate30M
         {0,   0,       0},  // keMvFrameRate50
         {0,   0,       0},  // keMvFrameRate60
         {0,   0,       0},  // keMvFrameRate60M
         {0,   0,       0}   // keMvFrameRateVariable
      },
      // keMvScanModeFirstFieldTop
      {
      //  D    E           TRIPLE_DUR
         {0,   0,             0},         // keMvFrameRateInvalid
         {5,   309375 + 1375, 125000},    // keMvFrameRate24            // This is not a real supported resolution, it is used by the I/O drivers in Psf mode
         {5,   309375 + 1375, 125125},    // keMvFrameRate24M           // This is not a real supported resolution, it is used by the I/O drivers in Psf mode
         {4,   371250 + 1320, 150000},    // keMvFrameRate25            // Since the number of lines are not odd for every field,
         {4,   309375 + 1100, 125000},    // keMvFrameRate30            // we must add the number of pixel of half of a line
         {4,   309375 + 1100, 125125},    // keMvFrameRate30M        
         {0,   0,             0},         // keMvFrameRate50
         {0,   0,             0},         // keMvFrameRate60
         {0,   0,             0},         // keMvFrameRate60M
         {0,   0,             0}          // keMvFrameRateVariable
      },
      // keMvScanModeSecondFieldTop
      {
      //  D    E           TRIPLE_DUR
         {0,   0,             0},         // keMvFrameRateInvalid
         {5,   309375 + 1375, 125000},    // keMvFrameRate24            // This is not a real supported resolution, it is used by the I/O drivers in Psf mode
         {5,   309375 + 1375, 125125},    // keMvFrameRate24M           // This is not a real supported resolution, it is used by the I/O drivers in Psf mode
         {4,   371250 + 1320, 150000},    // keMvFrameRate25            // Since the number of lines are not odd for every field,
         {4,   309375 + 1100, 125000},    // keMvFrameRate30            // we must add the number of pixel of half of a line
         {4,   309375 + 1100, 125125},    // keMvFrameRate30M
         {0,   0,             0},         // keMvFrameRate50
         {0,   0,             0},         // keMvFrameRate60
         {0,   0,             0},         // keMvFrameRate60M
         {0,   0,             0}          // keMvFrameRateVariable
      },
      // keMvScanModeProgressive
      {
      //  D    E     TRIPLE_DUR
         {0,   0,        0},        // keMvFrameRateInvalid
         {10,  309375,   125000},   // keMvFrameRate24
         {10,  309375,   125125},   // keMvFrameRate24M
         {8,   371250,   150000},   // keMvFrameRate25
         {8,   309375,   125000},   // keMvFrameRate30
         {8,   309375,   125125},   // keMvFrameRate30M
         {4,   371250,   150000},   // keMvFrameRate50
         {4,   309375,   125000},   // keMvFrameRate60
         {4,   309375,   125125},   // keMvFrameRate60M
         {0,   0,        0}         // keMvFrameRateVariable
      },
      // keMvScanModeProgressiveSegmented
      {
      //  D    E          TRIPLE_DUR
         {0,   0,             0},      // keMvFrameRateInvalid
         {10,  309375 + 1375, 125000}, // keMvFrameRate24
         {10,  309375 + 1375, 125125}, // keMvFrameRate24M
         {8,   371250 + 1320, 150000}, // keMvFrameRate25            // Since the number of lines are not odd for every field,
         {8,   309375 + 1100, 125000}, // keMvFrameRate30            // we must add the number of pixel of half of a line
         {8,   309375 + 1100, 125125}, // keMvFrameRate30M
         {0,   0,             0},      // keMvFrameRate50
         {0,   0,             0},      // keMvFrameRate60
         {0,   0,             0},      // keMvFrameRate60M
         {0,   0,             0}       // keMvFrameRateVariable
      },
      // keMvScanModeInterlacedFieldsInAFrame
      {
         //  D    E          TRIPLE_DUR
         {0,   0,             0},      // keMvFrameRateInvalid
         {10,  309375 + 1375, 125000}, // keMvFrameRate24
         {10,  309375 + 1375, 125125}, // keMvFrameRate24M
         {8,   371250 + 1320, 150000}, // keMvFrameRate25            // Since the number of lines are not odd for every field,
         {8,   309375 + 1100, 125000}, // keMvFrameRate30            // we must add the number of pixel of half of a line
         {8,   309375 + 1100, 125125}, // keMvFrameRate30M
         {0,   0,             0},      // keMvFrameRate50
         {0,   0,             0},      // keMvFrameRate60
         {0,   0,             0},      // keMvFrameRate60M
         {0,   0,             0}       // keMvFrameRateVariable
      }
   }
};

// DOM-IGNORE-END

//!ignore me! This is to document properly the methods
inline uint64_t MvRound(uint64_t in_ui64Numerator, uint64_t in_ui64Denominator);
inline uint64_t MvGetNanoTimeForSample(uint64_t in_ui64Sample, const SMvResolutionInfo& in_rsResolutionInfo);
inline uint64_t MvGetSampleForNanoTime(uint64_t in_ui64NanoTime, const SMvResolutionInfo& in_rsResolutionInfo);
inline uint64_t MvGetNextSampleNanoTime(uint64_t in_ui64CurrentTime, const SMvResolutionInfo& in_rsResolutionInfo);
inline uint64_t MvGetNanoTimeForSystemClockTicks(uint64_t in_uiNbTicks, const SMvResolutionInfo& in_rsResolutionInfo);
inline uint64_t MvGetSystemClockTicksForNanoTime(uint64_t in_ui64NanoTime, const SMvResolutionInfo& in_rsResolutionInfo);
inline uint64_t MvGetClockTicksForSample(uint64_t in_ui64Sample, const SMvResolutionInfo& in_rsResolutionInfo);
inline uint64_t MvGetSampleForClockTicks(uint64_t in_ui64ClockTicks, const SMvResolutionInfo& in_rsResolutionInfo);
inline uint64_t MvGetNextSampleClockTicks(uint64_t in_ui64CurrentClockTicks, const SMvResolutionInfo& in_rsResolutionInfo);

////////////////////////////////////////////////////////////////////
//
// Summary:
//    Similar to the ANSI ceil function, but for integers.
//
////////////////////////////////////////////////////////////////////
inline uint64_t MvRound(uint64_t in_ui64Numerator, uint64_t in_ui64Denominator)
{
   return (in_ui64Numerator % in_ui64Denominator) ? ((in_ui64Numerator + in_ui64Denominator) / in_ui64Denominator) : (in_ui64Numerator / in_ui64Denominator);
};

////////////////////////////////////////////////////////////////////
//
// Summary:
//    Returns the nanotime value for the specified sample value and resolution.
//
////////////////////////////////////////////////////////////////////
inline uint64_t MvGetNanoTimeForSample(uint64_t in_ui64Sample, const SMvResolutionInfo& in_rsResolutionInfo)
{
   unsigned int uiSDHD = ((in_rsResolutionInfo.ulHeight == 486) || (in_rsResolutionInfo.ulHeight == 576)) ? 0 : 1;
   unsigned int uiD = kauiClockLUT[uiSDHD][in_rsResolutionInfo.eScanMode][in_rsResolutionInfo.eFrameRate][0];
   unsigned int uiTD = kauiClockLUT[uiSDHD][in_rsResolutionInfo.eScanMode][in_rsResolutionInfo.eFrameRate][2];

   if((uiD == 0) || (uiTD == 0))
      return 0;

   return (MvRound(in_ui64Sample * uiD * uiTD, 3));
};

////////////////////////////////////////////////////////////////////
//
// Summary:
//    Returns the sample value for the specified nanotime value and resolution.
// Remarks:
//    - If the specified nanotime value is between two sample values, the smallest sample value is returned.
//
////////////////////////////////////////////////////////////////////
inline uint64_t MvGetSampleForNanoTime(uint64_t in_ui64NanoTime, const SMvResolutionInfo& in_rsResolutionInfo)
{
   unsigned int uiSDHD = ((in_rsResolutionInfo.ulHeight == 486) || (in_rsResolutionInfo.ulHeight == 576)) ? 0 : 1;
   unsigned int uiD = kauiClockLUT[uiSDHD][in_rsResolutionInfo.eScanMode][in_rsResolutionInfo.eFrameRate][0];
   unsigned int uiTD = kauiClockLUT[uiSDHD][in_rsResolutionInfo.eScanMode][in_rsResolutionInfo.eFrameRate][2];

   if((uiD == 0) || (uiTD == 0))
      return 0;

   return (((3 * in_ui64NanoTime) / uiTD) / uiD);
};

////////////////////////////////////////////////////////////////////
//
// Summary:
//    Returns the nanotime value of the sample following the specified nanotime.
//
////////////////////////////////////////////////////////////////////
inline uint64_t MvGetNextSampleNanoTime(uint64_t in_ui64CurrentTime, const SMvResolutionInfo& in_rsResolutionInfo)
{
   return MvGetNanoTimeForSample((MvGetSampleForNanoTime(in_ui64CurrentTime, in_rsResolutionInfo) + 1), in_rsResolutionInfo);
};


//////////////////////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Returns the nanotime for the number of system clock ticks.
// Remarks:
//    - There are many clock ticks per sample.
//    - DO NOT get the duration for one tick and multiply by the "nb" you want, use the macro with "nb"
//////////////////////////////////////////////////////////////////////////////////////////////////
inline uint64_t MvGetNanoTimeForSystemClockTicks(uint64_t in_uiNbTicks, const SMvResolutionInfo& in_rsResolutionInfo)
{
   unsigned int uiSDHD = ((in_rsResolutionInfo.ulHeight == 486) || (in_rsResolutionInfo.ulHeight == 576)) ? 0 : 1;
   unsigned int uiTD = kauiClockLUT[uiSDHD][in_rsResolutionInfo.eScanMode][in_rsResolutionInfo.eFrameRate][2];

   if(uiTD == 0)
      return 0;

   return (MvRound(in_uiNbTicks * uiTD, 3));
};

////////////////////////////////////////////////////////////////////
//
// Summary:
//    Returns the clock ticks for the passed nanotime
// Remarks:
//    - There are many clock ticks per sample and it is different for every resolution
//    - DO NOT get the duration by playing with ticks 
//      use the proper macro
////////////////////////////////////////////////////////////////////
inline uint64_t MvGetSystemClockTicksForNanoTime(uint64_t in_ui64NanoTime, const SMvResolutionInfo& in_rsResolutionInfo)
{
    unsigned int uiSDHD = ((in_rsResolutionInfo.ulHeight == 486) || (in_rsResolutionInfo.ulHeight == 576)) ? 0 : 1;
    unsigned int uiD = kauiClockLUT[uiSDHD][in_rsResolutionInfo.eScanMode][in_rsResolutionInfo.eFrameRate][0];
    unsigned int uiTD = kauiClockLUT[uiSDHD][in_rsResolutionInfo.eScanMode][in_rsResolutionInfo.eFrameRate][2];

    if((uiD == 0) || (uiTD == 0))
        return 0;

    return (((3 * in_ui64NanoTime) / uiTD) );
};

////////////////////////////////////////////////////////////////////
//
// Summary:
//    Returns the clock tick for the passed sample
//
////////////////////////////////////////////////////////////////////
inline uint64_t MvGetClockTicksForSample(uint64_t in_ui64Sample, const SMvResolutionInfo& in_rsResolutionInfo)
{
   unsigned int uiSDHD = ((in_rsResolutionInfo.ulHeight == 486) || (in_rsResolutionInfo.ulHeight == 576)) ? 0 : 1;
   unsigned int uiD = kauiClockLUT[uiSDHD][in_rsResolutionInfo.eScanMode][in_rsResolutionInfo.eFrameRate][0];
   unsigned int uiTD = kauiClockLUT[uiSDHD][in_rsResolutionInfo.eScanMode][in_rsResolutionInfo.eFrameRate][2];

   if((uiD == 0) || (uiTD == 0))
      return 0;

   return (in_ui64Sample * uiD);
};

////////////////////////////////////////////////////////////////////
//
// Summary:
//    Returns the sample for the passed clock tick
//
////////////////////////////////////////////////////////////////////
inline uint64_t MvGetSampleForClockTicks(uint64_t in_ui64ClockTicks, const SMvResolutionInfo& in_rsResolutionInfo)
{
   unsigned int uiSDHD = ((in_rsResolutionInfo.ulHeight == 486) || (in_rsResolutionInfo.ulHeight == 576)) ? 0 : 1;
   unsigned int uiD = kauiClockLUT[uiSDHD][in_rsResolutionInfo.eScanMode][in_rsResolutionInfo.eFrameRate][0];
   unsigned int uiTD = kauiClockLUT[uiSDHD][in_rsResolutionInfo.eScanMode][in_rsResolutionInfo.eFrameRate][2];

   if((uiD == 0) || (uiTD == 0))
      return 0;

   return (in_ui64ClockTicks / uiD);
};

////////////////////////////////////////////////////////////////////
//
// Summary:
//    Returns the clock ticks for the next sample.
//
////////////////////////////////////////////////////////////////////
inline uint64_t MvGetNextSampleClockTicks(uint64_t in_ui64CurrentClockTicks, const SMvResolutionInfo& in_rsResolutionInfo)
{
   return MvGetClockTicksForSample((MvGetSampleForClockTicks(in_ui64CurrentClockTicks, in_rsResolutionInfo) + 1), in_rsResolutionInfo);
};

#ifdef MAC_PLATFORM
};  // namespace com_matrox_vpg_SDK
#endif

