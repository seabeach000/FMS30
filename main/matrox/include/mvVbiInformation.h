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

#ifndef MVVBIINFORMATION_H
#define MVVBIINFORMATION_H

#include "mvTypes.h"
#include "mvDefinitions.h"


const uint32_t kulVbiOffsetDelta = 1;

//
// Summary:
//    Used to return the value of the VBI starting line and the total number of lines for both fields.
//
struct SMvVbiSettings
{
   uint32_t       size;          // Structure size in bytes.
   uint32_t  ulStartLine;   // The number of the VBI starting line of the first field.
   uint32_t  ulTotalLines;  // The total number of VBI lines for both fields.
};


const SMvVbiSettings kasMvVbiRange[8] = 
{
   // NTSC
   { sizeof(SMvVbiSettings),  7, 32 },

   // PAL                                
   { sizeof(SMvVbiSettings),  6, 34 },

   // 720p                               
   { sizeof(SMvVbiSettings),  7, 19 },

   // 1080i                              
   { sizeof(SMvVbiSettings),  6, 30 },

   // 1080i with 1440                              
   { sizeof(SMvVbiSettings),  6, 30 },

   // 1080psf                              
   { sizeof(SMvVbiSettings),  6, 30 },

   // 1080psf with 1440                             
   { sizeof(SMvVbiSettings),  6, 30 },

   // 1080p, 2K, QuadHD, 4k                            
   { sizeof(SMvVbiSettings),  7, 35 }
};

// ----------------------------------------------------------------------------
// Function name   : MvGetVbiSettings
// Description     : 
// ----------------------------------------------------------------------------
bool inline MvGetVbiSettings(SMvResolutionInfo & i_rsRes, SMvVbiSettings & io_rMvVbiSettings)
{
   if ((i_rsRes.ulWidth == 720) && 
       (i_rsRes.ulHeight == 486 || i_rsRes.ulHeight == 480 || i_rsRes.ulHeight == 512))
   {
      io_rMvVbiSettings = kasMvVbiRange[0];  // NTSC
   }
   else if ((i_rsRes.ulWidth == 720) && 
            (i_rsRes.ulHeight == 576 || i_rsRes.ulHeight == 608))
   {
      io_rMvVbiSettings = kasMvVbiRange[1];  // PAL
   }
   else if ((i_rsRes.ulWidth == 1280) && 
            (i_rsRes.ulHeight == 720) && 
            (i_rsRes.eScanMode == keMvScanModeProgressive))
   {
      io_rMvVbiSettings = kasMvVbiRange[2];  // 720p
   }
   else if ((i_rsRes.ulWidth == 1920) && 
            (i_rsRes.ulHeight == 1080) &&
            (i_rsRes.eScanMode == keMvScanModeFirstFieldTop || i_rsRes.eScanMode == keMvScanModeSecondFieldTop))
   {
      io_rMvVbiSettings = kasMvVbiRange[3];  // 1080i
   }
   else if ((i_rsRes.ulWidth == 1440) && 
            (i_rsRes.ulHeight == 1080) &&
            (i_rsRes.eScanMode == keMvScanModeFirstFieldTop || i_rsRes.eScanMode == keMvScanModeSecondFieldTop))
   {
      io_rMvVbiSettings = kasMvVbiRange[4];  // 1080i with 1440x1080
   }
   else if ((i_rsRes.ulWidth == 1920) && 
            (i_rsRes.ulHeight == 1080) &&
            (i_rsRes.eScanMode == keMvScanModeProgressiveSegmented || i_rsRes.eScanMode == keMvScanModeInterlacedFieldsInAFrame))
   {
      io_rMvVbiSettings = kasMvVbiRange[5];  // 1080psf
   }
   else if ((i_rsRes.ulWidth == 1440) && 
            (i_rsRes.ulHeight == 1080) &&
            (i_rsRes.eScanMode == keMvScanModeProgressive || i_rsRes.eScanMode == keMvScanModeProgressiveSegmented || i_rsRes.eScanMode == keMvScanModeInterlacedFieldsInAFrame))
   {
      io_rMvVbiSettings = kasMvVbiRange[6];  // 1080psf with 1440x1080
   }
   else if (((i_rsRes.ulWidth == 1920 && i_rsRes.ulHeight == 1080) ||
             (i_rsRes.ulWidth == 2048 && i_rsRes.ulHeight == 1024) ||
             (i_rsRes.ulWidth == 2048 && i_rsRes.ulHeight == 1080) ||
             (i_rsRes.ulWidth == 3840 && i_rsRes.ulHeight == 2160) ||
             (i_rsRes.ulWidth == 4096 && i_rsRes.ulHeight == 2048) ||
             (i_rsRes.ulWidth == 4096 && i_rsRes.ulHeight == 2160)) &&
             (i_rsRes.eScanMode == keMvScanModeProgressive))
   {
      io_rMvVbiSettings = kasMvVbiRange[7];  // 1080p, 2K, QuadHD, 4k
   }
   else
   {
      // Return false and default to NTSC value
      io_rMvVbiSettings = kasMvVbiRange[0];  // NTSC
      return false;
   }
   return true;
}

//this method translates the line number based on the local vbi buffer
//to the one based on the global frame buffer.
//The vbi-based line number starts from 0, relative to the beginning of the vbi buffer.
//the frame-based line number starts from 1, with consideration of the polarity.

bool  inline   MvGetLineNumberFromVbiToFrame(
   uint32_t& io_ulFrameBasedLineNumber, 
   uint32_t& i_ulVbiBasedLineNumber,
   SMvResolutionInfo& i_rsRes,
   EMvPolarity   i_ePolarity
   )
{
   bool bStatus = true;
   
   SMvVbiSettings sVbiSettings = {sizeof(SMvVbiSettings)};
   bStatus = MvGetVbiSettings(i_rsRes,sVbiSettings);
   if (bStatus)
   {
      //HD
      if (i_rsRes.ulWidth > 720)
      {
         switch(i_rsRes.ulHeight)
         {
         case 720:         //720p
            if (i_rsRes.ulWidth == 1280 && i_rsRes.eScanMode == keMvScanModeProgressive)
            {
               io_ulFrameBasedLineNumber = i_ulVbiBasedLineNumber + sVbiSettings.ulStartLine;
            }
            else
            {
               bStatus = false;
            }
            break;

         case 1080:           //1080i/p
            if (i_rsRes.ulWidth == 1920)
            {
               if (i_rsRes.eScanMode == keMvScanModeProgressive)
               {
                  if (i_ePolarity == keMvPolarityProgressiveFrame)
                  {
                     io_ulFrameBasedLineNumber = i_ulVbiBasedLineNumber + sVbiSettings.ulStartLine;
                  }
                  else
                  {
                     //_ASSERT(!"Invalid polarity!");
                     bStatus = false;
                  }
               }
               else
               {
                  if (i_ePolarity == keMvPolarityFirstField)
                  {
                     io_ulFrameBasedLineNumber = i_ulVbiBasedLineNumber + sVbiSettings.ulStartLine;
                  }
                  else
                  {
                     if (i_ePolarity == keMvPolaritySecondField)
                     {
                        //1125 -> 563 and 562 per fields as per smpte274
                        io_ulFrameBasedLineNumber = 563 + i_ulVbiBasedLineNumber + sVbiSettings.ulStartLine;
                     }
                     else
                     {
                        //_ASSERT(!"Invalid polarity!");
                        bStatus = false;
                     }
                  }
               }
            }
            else
            {
               //_ASSERT(!"Invalid resolution!");
               bStatus = false;
            }
            break;

         default:
            //_ASSERT(!"Invalid resolution!");
            bStatus = false;
         }

      }
      else
      //SD (NTSC or PAL)
      {
         if (i_rsRes.eScanMode == keMvScanModeProgressive || i_rsRes.ulWidth != 720)
         {
            //_ASSERT(!"Invalid resolution!");
            bStatus = false;
         }
         else
         {
            switch(i_rsRes.ulHeight)
            {
            case 486:         //NTSC
               if (i_ePolarity == keMvPolarityFirstField)
               {
                  io_ulFrameBasedLineNumber = 7+i_ulVbiBasedLineNumber;
               }
               else
               {
                  if (i_ePolarity == keMvPolaritySecondField)
                  {
                     io_ulFrameBasedLineNumber = 269 + i_ulVbiBasedLineNumber;
                  }
                  else
                  {
                     //_ASSERT(!"Invalid polarity!");
                     bStatus = false;
                  }
               }
               break;
            case 576:
               if (i_ePolarity == keMvPolarityFirstField)
               {
                  io_ulFrameBasedLineNumber = 6+i_ulVbiBasedLineNumber;
               }
               else
               {
                  if (i_ePolarity == keMvPolaritySecondField)
                  {
                     io_ulFrameBasedLineNumber = 319 + i_ulVbiBasedLineNumber;
                  }
                  else
                  {
                     //_ASSERT(!"Invalid polarity!");
                     bStatus = false;
                  }
               }
               break;         //PAL
            default:
               //_ASSERT(!"Invalid resolution!");
               bStatus = false;
            }
         }

      }
   }
   else
   {
      //_ASSERT(!"Failed to get the vbi settings!");
   }

   return bStatus;
}



//this method translates the line number based on the local vbi buffer

bool  inline   MvGetLineNumberFromFrameToVbi(
   uint32_t& io_ulVbiBasedLineNumber,
   uint32_t& i_ulFrameBasedLineNumber,    
   SMvResolutionInfo& i_rsRes,
   EMvPolarity   i_ePolarity
   )
{
   bool bStatus = true;

   SMvVbiSettings sVbiSettings = {sizeof(SMvVbiSettings)};
   bStatus = MvGetVbiSettings(i_rsRes,sVbiSettings);
   if (bStatus)
   {
      //HD
      if (i_rsRes.ulWidth > 720)
      {
         switch(i_rsRes.ulHeight)
         {
         case 720:         //720p
            if (i_rsRes.ulWidth == 1280 && i_rsRes.eScanMode == keMvScanModeProgressive)
            {
               if (i_ulFrameBasedLineNumber >= sVbiSettings.ulStartLine && i_ulFrameBasedLineNumber < sVbiSettings.ulStartLine + sVbiSettings.ulTotalLines )
               {
                  io_ulVbiBasedLineNumber = i_ulFrameBasedLineNumber - sVbiSettings.ulStartLine;
               }
               else
               {
                  bStatus = false;
               }
               
            }
            else
            {
               //_ASSERT(!"Invalid resolution!");
               bStatus = false;
            }
            break;

         case 1080:           //1080i/p
            if (i_rsRes.ulWidth == 1920)
            {
               if (i_rsRes.eScanMode == keMvScanModeProgressive)
               {
                  if (i_ePolarity == keMvPolarityProgressiveFrame)
                  {
                     if (i_ulFrameBasedLineNumber >= sVbiSettings.ulStartLine && i_ulFrameBasedLineNumber < sVbiSettings.ulStartLine + sVbiSettings.ulTotalLines )
                     {
                        io_ulVbiBasedLineNumber = i_ulFrameBasedLineNumber - sVbiSettings.ulStartLine;
                     }
                     else
                     {
                        bStatus = false;
                     }                     
                     
                  }
                  else
                  {
                     //_ASSERT(!"Invalid polarity!");
                     bStatus = false;
                  }
               }
               else
               {
                  if (i_ePolarity == keMvPolarityFirstField)
                  {
                     if (i_ulFrameBasedLineNumber >= sVbiSettings.ulStartLine && i_ulFrameBasedLineNumber < sVbiSettings.ulStartLine + sVbiSettings.ulTotalLines /2 )
                     {
                        io_ulVbiBasedLineNumber = i_ulFrameBasedLineNumber - sVbiSettings.ulStartLine;
                     }
                     else
                     {
                        bStatus = false;
                     }                                          
                  }
                  else
                  {
                     if (i_ePolarity == keMvPolaritySecondField)
                     {
                        //1125 -> 563 and 562 per fields as per smpte274
                        if (i_ulFrameBasedLineNumber >= sVbiSettings.ulStartLine + 563 && i_ulFrameBasedLineNumber < sVbiSettings.ulStartLine + 563 + sVbiSettings.ulTotalLines /2)
                        {
                           io_ulVbiBasedLineNumber = i_ulFrameBasedLineNumber - 563 - sVbiSettings.ulStartLine;
                        }
                        else
                        {
                           bStatus = false;
                        }
                        
                     }
                     else
                     {
                        //_ASSERT(!"Invalid polarity!");
                        bStatus = false;
                     }
                  }
               }
            }
            else
            {
               //_ASSERT(!"Invalid resolution!");
               bStatus = false;
            }
            break;

         default:
            //_ASSERT(!"Invalid resolution!");
            bStatus = false;
         }

      }
      else
         //SD (NTSC or PAL)
      {
         if (i_rsRes.eScanMode == keMvScanModeProgressive || i_rsRes.ulWidth != 720)
         {
            //_ASSERT(!"Invalid resolution!");
            bStatus = false;
         }
         else
         {
            switch(i_rsRes.ulHeight)
            {
            case 486:         //NTSC
               if (i_ePolarity == keMvPolarityFirstField)
               {
                  if (i_ulFrameBasedLineNumber >= 7 && i_ulFrameBasedLineNumber <= 21)
                  {
                     io_ulVbiBasedLineNumber = i_ulFrameBasedLineNumber - 7;
                  }
                  else
                  {
                     bStatus = false;
                  }
                  
               }
               else
               {
                  if (i_ePolarity == keMvPolaritySecondField)
                  {
                     if (i_ulFrameBasedLineNumber >= 269 && i_ulFrameBasedLineNumber <= 284)
                     {
                        io_ulVbiBasedLineNumber = i_ulFrameBasedLineNumber - 269;
                     }
                     else
                     {
                        bStatus = false;
                     }                     
                  }
                  else
                  {
                     //_ASSERT(!"Invalid polarity!");
                     bStatus = false;
                  }
               }
               break;
            case 576:
               if (i_ePolarity == keMvPolarityFirstField)
               {
                  if (i_ulFrameBasedLineNumber >= 6 && i_ulFrameBasedLineNumber <= 22)
                  {
                     io_ulVbiBasedLineNumber = i_ulFrameBasedLineNumber - 6;
                  }
                  else
                  {
                     bStatus = false;
                  }
                  
               }
               else
               {
                  if (i_ePolarity == keMvPolaritySecondField)
                  {
                     if (i_ulFrameBasedLineNumber >= 319 && i_ulFrameBasedLineNumber < 335)
                     {
                        io_ulVbiBasedLineNumber = i_ulFrameBasedLineNumber - 319;
                     }
                     else
                     {
                        bStatus = false;
                     }
                     
                  }
                  else
                  {
                     //_ASSERT(!"Invalid polarity!");
                     bStatus = false;
                  }
               }
               break;         //PAL
            default:
               //_ASSERT(!"Invalid resolution!");
               bStatus = false;
            }
         }

      }
   }
   else
   {
      //_ASSERT(!"Failed to get the vbi settings!");
   }

   if (bStatus == true)
   {
      if (io_ulVbiBasedLineNumber >= sVbiSettings.ulTotalLines)
      {
         bStatus = false;
      }            
   }

   return bStatus;
}
#endif // MVVBIINFORMATION_H

