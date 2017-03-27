//==============================================================================
//
// (c) Copyright Matrox Electronic Systems Ltd., 2003. All rights reserved. 
//
// This code and information is provided "as is" without warranty of any kind, 
// either expressed or implied, including but not limited to the implied 
// warranties of merchantability and/or fitness for a particular purpose.
//
// All code and information is provided "as is" without warranty of any kind, 
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
//------------------------------------------------------------------------------
//                         mvdMGF2.h
//----------------------------------------------------------------
//   Birth Date:       May 31  2004
//   Operating System: Windows XP
//   Author:           Mario Rousseau
//----------------------------------------------------------------
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada 
//----------------------------------------------------------------

#ifndef _MVD_MGF2_H_
#define _MVD_MGF2_H_

#include "mvdDef.h"

struct SMvdMGF2Header
{
  GUID   guidFileTypeID; 
  DWORD  dwVersionID;
  DWORD  dwHeaderSize;
  DWORD  dwPrivateDataSize;
};

struct SMvMGF2Info 
{  
   uint32_t Size;                     // Size of current structure.
   unsigned long ulElementSizeLow;    // Size of the data element (in bytes). This is the low part
   unsigned long ulElementSizeHigh;   // Size of the data element (in bytes). This is the high part (4G)
   unsigned long ulTotalWidth;        // Width of the file in pixels
   unsigned long ulTotalHeight;       // Height of the file in lines
   unsigned long ulPitch;             // Line picth of the file in bytes
   unsigned long ulComponentBitCount; // Components Y,U,V,A size (8 or 10 bits)

   EMvSurfaceFormat eSurfaceFormat;   // Surface data format (YUVA 4224 or YUV 422)
   EMvPixelRatio ePixelRatio;         // Pixel aspect ratio
   EMvImageOrigin  eImageOrigin;      // Origine of the file  
};

struct SMvdMGF2ElementInfo
{
  LONGLONG llOffset;
  SMvMGF2Info sParam;
}; 

#endif
