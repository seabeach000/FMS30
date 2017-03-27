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

const uint64_t kaui64AudioSeq30MFrame[5][5] =
{
   //[remainder][reference]
   {    0,    0,    0,    0,    0},    // 0 frame remainder
   { 1602, 1601, 1602, 1601, 1602},    // 1-frame remainder
   { 3203, 3203, 3203, 3203, 3204},    // 2-frame remainder  
   { 4805, 4804, 4805, 4805, 4805},    // 3-frame remainder
   { 6406, 6406, 6407, 6406, 6407}     // 4-frame remainder
};

const uint64_t kaui64AudioSeq30MField[5][5] = 
{
   //[remainder][reference ]
   {    0,    0,    0,    0,    0},    // 0 field remainder
   {  801,  801,  800,  801,  801},    // 1-field remainder
   { 1602, 1601, 1601, 1602, 1602},    // 2-field remainder  
   { 2402, 2402, 2402, 2403, 2403},    // 3-field remainder
   { 3203, 3203, 3203, 3204, 3203}     // 4-field remainder
};

const uint64_t kaui64AudioSeq60MField[5][5] = 
{
   //[remainder][reference ]
   {    0,    0,    0,    0,    0},    // 0 field remainder
   {  400,  401,  400,  401,  400},    // 1-field remainder
   {  801,  801,  801,  801,  800},    // 2-field remainder  
   { 1201, 1202, 1201, 1201, 1201},    // 3-field remainder
   { 1602, 1602, 1601, 1602, 1601}     // 4-field remainder
};

// DOM-IGNORE-END

//!ignore me! Declaration and implementation must be separate for Doc-O-Matic to work properly.
inline uint64_t MvGetNanoTimeFromAudioSamples(uint64_t in_ui64AudioSamples, SMvAudioSamplesDescription & in_rsAudioSamplesDescription);
inline uint64_t MvGetAudioSamplesFromNanoTime(uint64_t in_ui64NanoTime, SMvAudioSamplesDescription & in_rsAudioSamplesDescription);
inline uint64_t MvGetReferencedVideoUnitsFromAudioSamples(uint64_t in_ui64AudioSamples, int64_t in_i64RefVideoUnit, const SMvResolutionInfo& in_rsResolutionInfo, uint64_t in_ui64FrameRateNum=1,uint64_t in_ui64FrameRateDenum=1);
inline uint64_t MvGetAudioSamplesFromReferencedVideoUnits(uint64_t in_ui64VideoUnit, int64_t in_i64RefVideoUnit, const SMvResolutionInfo& in_rsResolutionInfo,  uint64_t in_ui64FrameRateNum=1,uint64_t in_ui64FrameRateDenum=1);
inline uint64_t MvGetReferencedVideoFramesFromAudioSamples(uint64_t in_ui64AudioSamples, int64_t in_i64RefVideoFrame, EMvFrameRate in_eVideoFrameRate,  uint64_t in_ui64FrameRateNum=1,uint64_t in_ui64FrameRateDenum=1);
inline uint64_t MvGetAudioSamplesFromReferencedVideoFrames(uint64_t in_ui64VideoFrame, int64_t in_i64RefVideoFrame, EMvFrameRate in_eVideoFrameRate, uint64_t in_ui64FrameRateNum=1,uint64_t in_ui64FrameRateDenum=1);
inline uint64_t MvGetVideoUnitFromAudioSamples(uint64_t in_ui64AudioSamples, const SMvResolutionInfo& in_rsResolutionInfo,  uint64_t in_ui64FrameRateNum=1,uint64_t in_ui64FrameRateDenum=1);
inline uint64_t MvGetAudioSamplesFromVideoUnit(uint64_t in_ui64VideoUnit, const SMvResolutionInfo& in_rsResolutionInfo,  uint64_t in_ui64FrameRateNum=1,uint64_t in_ui64FrameRateDenum=1);

/////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Obtains the corresponding nano-time for x amount of audio samples.
//
/////////////////////////////////////////////////////////////////////////////////
inline uint64_t MvGetNanoTimeFromAudioSamples
   (
   uint64_t                     in_ui64AudioSamples,           // Number of samples.
   SMvAudioSamplesDescription & in_rsAudioSamplesDescription   // Sample's format for nanotime computation.
   )
{
   return ((in_ui64AudioSamples * ( uint64_t )10000000  ) / in_rsAudioSamplesDescription.sWaveFormat.ulSamplesPerSec);
}

/////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Obtains the corresponding sample for x amount of nano-time.
//
/////////////////////////////////////////////////////////////////////////////////
inline uint64_t MvGetAudioSamplesFromNanoTime
   (
   uint64_t                     in_ui64NanoTime,               // Nanotime to convert.
   SMvAudioSamplesDescription & in_rsAudioSamplesDescription   // Sample's format for nanotime computation.
   )
{
   return (((in_ui64NanoTime + (uint64_t)1) * in_rsAudioSamplesDescription.sWaveFormat.ulSamplesPerSec)/(uint64_t)10000000 );
}

/////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Returns the audio sample count needed for the specified video unit value.
//
// Example:
//    You can use this function to evaluate how many audio samples you need for "d" video units of
//    duration at a specific clock time expressed in the same video units. To do so you set 
//    in_ui64VideoUnit = d and pass your clock time to in_i64RefVideoUnit.
//
//       SampleLength = MvGetAudioSamplesFromReferencedVideoUnits(d, YourClockTime, sResolutionInfo)
//
//    In this example the duration is static and the reference in the audio sequence is dynamic 
//    (YourClockTime). Since this function applies a modulo "sequence length" to the reference,
//    successive calls with your next clock time will return the sample values contained in the
//    audio sequence.
//
//    In NTSC at 29.97 fps, with duration = 1 frame
//    <CODE>
//    MvGetAudioSamplesFromReferencedVideoUnits(1, 0, sResolutionInfo) = 1602
//    MvGetAudioSamplesFromReferencedVideoUnits(1, 1, sResolutionInfo) = 1601
//    MvGetAudioSamplesFromReferencedVideoUnits(1, 2, sResolutionInfo) = 1602
//    MvGetAudioSamplesFromReferencedVideoUnits(1, 3, sResolutionInfo) = 1601
//    MvGetAudioSamplesFromReferencedVideoUnits(1, 4, sResolutionInfo) = 1602
//    MvGetAudioSamplesFromReferencedVideoUnits(1, 5, sResolutionInfo) = 1602, and so forth...
//    </CODE>
//
// Example:
//    You can use this function to evaluate a position in audio samples for a "p" position in video
//    units with a reference in the audio sequence. Supposing that we want to start at the first
//    position of the audio sequence, set in_ui64VideoUnit = p and in_i64RefVideoUnit = 0;
//
//       SamplePosition = MvGetAudioSamplesFromReferencedVideoUnits(p, 0, sResolutionInfo)
//
//    In this example the position is dynamic and the reference in the audio sequence is static.
//
//    In NTSC at 29.97 fps, with reference = 0
//    <CODE>
//    MvGetAudioSamplesFromReferencedVideoUnits(1, 0, sResolutionInfo) = 1602
//    MvGetAudioSamplesFromReferencedVideoUnits(2, 0, sResolutionInfo) = 3203
//    MvGetAudioSamplesFromReferencedVideoUnits(3, 0, sResolutionInfo) = 4805
//    MvGetAudioSamplesFromReferencedVideoUnits(4, 0, sResolutionInfo) = 6406
//    </CODE>
//
//    In NTSC at 29.97 fps, with reference = 1 (start forward in sequence)
//    <CODE>
//    MvGetAudioSamplesFromReferencedVideoUnits(1, 1, sResolutionInfo) = 1601
//    MvGetAudioSamplesFromReferencedVideoUnits(2, 1, sResolutionInfo) = 3203
//    MvGetAudioSamplesFromReferencedVideoUnits(3, 1, sResolutionInfo) = 4804
//    MvGetAudioSamplesFromReferencedVideoUnits(4, 1, sResolutionInfo) = 6406
//    </CODE>
//
// Remarks:
//    - Used to maintain the proper audio sequence for 23.98, 29.97, and 59.94 fps video frequencies.
//    - Changing the reference in an audio sequence will return different values for 29.97 and 59.94 fps only.
//
/////////////////////////////////////////////////////////////////////////////////
inline uint64_t MvGetAudioSamplesFromReferencedVideoUnits
   (
   uint64_t                 in_ui64VideoUnit,   // Position or duration in video units.
   int64_t                  in_i64RefVideoUnit, // Reference in video units in the audio sequence. 
                                                   // This reference tells only where to start in the 
                                                   // audio sequence. Both negative and positive
                                                   // reference are supported. Values greater than 
                                                   // the sequence length are "moduloed". 
                                                   // (in_i64RefVideoUnit % (sequence length)) 
                                                   // This parameter is used for 29.97 and 59.94 fps only.
   const SMvResolutionInfo& in_rsResolutionInfo, // SMvResolutionInfo structure containing resolution 
                                                   // information.
    uint64_t in_ui64FrameRateNum,
	uint64_t in_ui64FrameRateDenum				  // Variable frame rate value.
   )
{
   uint64_t ui64Samples = 0;
   switch(in_rsResolutionInfo.eFrameRate)
   {
   case keMvFrameRateVariable:
	  if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode divided by 2
         ui64Samples = in_ui64VideoUnit * ((48000*in_ui64FrameRateDenum)/in_ui64FrameRateNum) / 2;  
      else
         ui64Samples = in_ui64VideoUnit * ((48000*in_ui64FrameRateDenum)/in_ui64FrameRateNum);       // where 2000 = 48000/24
	   break;
   case keMvFrameRate24:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode divided by 2
         ui64Samples = in_ui64VideoUnit * 2000 / 2;   // where 2000 = 48000/24
      else
         ui64Samples = in_ui64VideoUnit * 2000;       // where 2000 = 48000/24
      break;
   case keMvFrameRate24M:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode divided by 2
      {
         ui64Samples = in_ui64VideoUnit * 1001;       // where 1001 = 48000/(24 * 1000/1001 ) / 2
      }
      else
      {
         ui64Samples = in_ui64VideoUnit * 2002;       // where 2002 = 48000/(24 * 1000/1001 )
      }
      break;
   case keMvFrameRate25:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode divided by 2
         ui64Samples = in_ui64VideoUnit * 1920 / 2;   // where 1920 = 48000/25
      else
         ui64Samples = in_ui64VideoUnit * 1920;       // where 1920 = 48000/25
      break;
   case keMvFrameRate30:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode divided by 2
         ui64Samples = in_ui64VideoUnit * 1600 / 2;   // where 1600 = 48000/30
      else
         ui64Samples = in_ui64VideoUnit * 1600;       // where 1600 = 48000/30
      break;
   case keMvFrameRate30M:  // this is 29.97 rate in frame or fields, we need to do special calculations for sequence
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) 
      {
         int64_t iRefIndex = in_i64RefVideoUnit%5;
         if(iRefIndex < 0)
         {
            iRefIndex = 5 + iRefIndex;
         }
         ui64Samples = (( in_ui64VideoUnit / 5 ) * 4004 ) + kaui64AudioSeq30MField[in_ui64VideoUnit%5][iRefIndex];
      }
      else
      {
         int64_t iRefIndex = in_i64RefVideoUnit%5;
         if(iRefIndex < 0)
         {
            iRefIndex = 5 + iRefIndex;
         }
         ui64Samples = (( in_ui64VideoUnit / 5 ) * 8008 ) + kaui64AudioSeq30MFrame[in_ui64VideoUnit%5][iRefIndex];
      }
      break;
   case keMvFrameRate50:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode divided by 2
         ui64Samples = in_ui64VideoUnit * 960 / 2;    // where 960 = 48000/50
      else
         ui64Samples = in_ui64VideoUnit * 960;        // where 960 = 48000/50
      break;
   case keMvFrameRate60:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode divided by 2
         ui64Samples = in_ui64VideoUnit * 800 / 2;    // where 800 = 48000/60
      else
         ui64Samples = in_ui64VideoUnit * 800;        // where 800 = 48000/60
      break;
   case keMvFrameRate60M: // this is 59.98 rate in frame or fields, we need to do special calculations for sequence
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) 
      {
         int64_t iRefIndex = in_i64RefVideoUnit%5;
         if(iRefIndex < 0)
         {
            iRefIndex = 5 + iRefIndex;
         }
         ui64Samples = (( in_ui64VideoUnit / 5 ) * 2002 ) + kaui64AudioSeq60MField[in_ui64VideoUnit%5][iRefIndex];
      }
      else
      {
         int64_t iRefIndex = in_i64RefVideoUnit%5;
         if(iRefIndex < 0)
         {
            iRefIndex = 5 + iRefIndex;
         }
         ui64Samples = (( in_ui64VideoUnit / 5 ) * 4004 ) + kaui64AudioSeq30MField[in_ui64VideoUnit%5][iRefIndex]; //60M FRAME shares the same LUT as 30M Field
      }
      break;
   default:
      break;
   }
   return ui64Samples;
}

/////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Returns the video unit value corresponding to the specified audio sample count.
//
// Remarks:
//    - Used to maintain the proper audio sequence for 23.98, 29.97, and 59.94 fps video frequencies.
//    - When the frame rate is 29.97 or 59.94 fps, one audio sample can make a difference depending on the position 
//      in the audio sequence. For example, in NTSC at 29.97 fps MvGetReferencedVideoUnitsFromAudioSamples(1601, 0, sResolutionInfo) 
//      will return 0, because the first frame must contain 1602 samples. That is, 1 sample is missing to complete the frame. 
//      However, MvGetReferencedVideoUnitsFromAudioSamples(1601, 1, sResolutionInfo) will
//      return 1 frame because a frame duration at a reference of 1 in the audio sequence is expected to be 1601.
// 
/////////////////////////////////////////////////////////////////////////////////
inline uint64_t MvGetReferencedVideoUnitsFromAudioSamples
   (
   uint64_t                 in_ui64AudioSamples,   // Position or duration in audio samples.
   int64_t                  in_i64RefVideoUnit,    // Reference in video units in the audio 
                                                      // sequence. This reference tells only where
                                                      // to start in the audio sequence. Both 
                                                      // negative and positive reference are 
                                                      // supported. Values greater than the sequence
                                                      // length are "moduloed". 
                                                      // (in_i64RefVideoUnit % (sequence length)) 
                                                      // This parameter is used for 29.97 and 59.94 fps only.
   const SMvResolutionInfo& in_rsResolutionInfo,    // SMvResolutionInfo structure containing resolution information.
    uint64_t in_ui64FrameRateNum,
	uint64_t in_ui64FrameRateDenum					// Variable frame rate value.
   )
{
   uint64_t ui64VideoUnit = 0;
   uint32_t ui32SampleRate = 48000;
   switch(in_rsResolutionInfo.eFrameRate)
   {

   case keMvFrameRateVariable:
	  if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop)
      {
         ui64VideoUnit = (( (in_ui64AudioSamples *in_ui64FrameRateNum)/in_ui64FrameRateDenum) * 2) / ui32SampleRate;  // 24 frame rate.
      }
      else
      {
         ui64VideoUnit = (( (in_ui64AudioSamples *in_ui64FrameRateNum)/in_ui64FrameRateDenum))/ ui32SampleRate;       // 24 frame rate.
      }
	   break;
   case keMvFrameRate24:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop)
      {
         ui64VideoUnit = (in_ui64AudioSamples * (24 * 2)) / ui32SampleRate;  // 24 frame rate.
      }
      else
      {
         ui64VideoUnit = (in_ui64AudioSamples * (24))/ ui32SampleRate;       // 24 frame rate.
      }
      break;
   case keMvFrameRate24M:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop)      // we are in field mode multiplied by 2
      {
         ui64VideoUnit = (in_ui64AudioSamples / 1001);                     // sequence is 1001 samples/field @ 48KHz
      }
      else
      {
         ui64VideoUnit = (in_ui64AudioSamples / 2002);                     // sequence is 2002 samples/frame @ 48KHz
      }
      break;
   case keMvFrameRate25:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop)      // we are in field mode multiplied by 2
         ui64VideoUnit = (in_ui64AudioSamples * (25 * 2)) / ui32SampleRate;  // 25 frame rate.
      else
         ui64VideoUnit = (in_ui64AudioSamples * (25)) / ui32SampleRate;      // 25 frame rate.
      break;
   case keMvFrameRate30:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop)      // we are in field mode multiplied by 2
         ui64VideoUnit = (in_ui64AudioSamples * (30 * 2)) / ui32SampleRate;  // 30 frame rate.
      else
         ui64VideoUnit = (in_ui64AudioSamples * (30)) / ui32SampleRate;      // 30 frame rate.
      break;
   case keMvFrameRate30M: 
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop)      
      {
         // set reference position in sequence
         int64_t iRefIndex = in_i64RefVideoUnit%5; 
         if(iRefIndex < 0)
         {
            iRefIndex = 5 + iRefIndex;    // adjust index for negative references
         }

         // Sequence is made of 5 fields. The durations of those fields @ ref zero are:
         // 801 - 801 - 800 - 801 - 801 (in samples)
         uint64_t ui645FieldSequence = ( in_ui64AudioSamples / 4004 );           // The amount of complete 5 fields sequences...
         uint64_t ui645FieldSequenceInSamples = ( ui645FieldSequence * 4004 );   // ...converted back into samples

         // Find the number of fields of the unfinished sequence (remainder)
         uint64_t ui64RemainderInSamples = in_ui64AudioSamples - ui645FieldSequenceInSamples;

         uint64_t ui64RemainderInFields = 0;

         if (ui64RemainderInSamples >= kaui64AudioSeq30MField[4][iRefIndex])
         {
            ui64RemainderInFields = 4;
         }
         else if (ui64RemainderInSamples >= kaui64AudioSeq30MField[3][iRefIndex])
         {
            ui64RemainderInFields = 3;
         }
         else if (ui64RemainderInSamples >= kaui64AudioSeq30MField[2][iRefIndex])
         {
            ui64RemainderInFields = 2;
         }
         else if (ui64RemainderInSamples >= kaui64AudioSeq30MField[1][iRefIndex])
         {
            ui64RemainderInFields = 1;
         }

         ui64VideoUnit = ui645FieldSequence * 5 + ui64RemainderInFields;
      }
      else
      {
         // set reference position in sequence
         int64_t iRefIndex = in_i64RefVideoUnit%5; 
         if(iRefIndex < 0)
         {
            iRefIndex = 5 + iRefIndex;             // adjust index for negative references
         }

         // Sequence is made of 5 frames. The durations of those frames @ ref zero are:
         // 1602 - 1601 - 1602 - 1601 - 1602 (in samples)
         uint64_t ui645FrameSequence = ( in_ui64AudioSamples / 8008 );           // The amount of complete 5 frames sequences...
         uint64_t ui645FrameSequenceInSamples = ( ui645FrameSequence * 8008 );   // ...converted back into samples

         // Find the number of frames of the unfinished sequence (remainder)
         uint64_t ui64RemainderInSamples = in_ui64AudioSamples - ui645FrameSequenceInSamples;
         uint64_t ui64RemainderInFrames = 0;

         if (ui64RemainderInSamples >= kaui64AudioSeq30MFrame[4][iRefIndex])
         {
            ui64RemainderInFrames = 4;
         }
         else if (ui64RemainderInSamples >= kaui64AudioSeq30MFrame[3][iRefIndex])
         {
            ui64RemainderInFrames = 3;
         }
         else if (ui64RemainderInSamples >= kaui64AudioSeq30MFrame[2][iRefIndex])
         {
            ui64RemainderInFrames = 2;
         }
         else if (ui64RemainderInSamples >= kaui64AudioSeq30MFrame[1][iRefIndex])
         {
            ui64RemainderInFrames = 1;
         }

         ui64VideoUnit = ui645FrameSequence * 5 + ui64RemainderInFrames;
      }
      break;
   case keMvFrameRate50:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode multiplied by 2
         ui64VideoUnit = (in_ui64AudioSamples * (50 * 2 )) / ui32SampleRate; // 50 frame rate.
      else
         ui64VideoUnit = (in_ui64AudioSamples * (50)) / ui32SampleRate; // 50 frame rate.
      break;
   case keMvFrameRate60:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode multiplied by 2
         ui64VideoUnit = (in_ui64AudioSamples * (60 * 2)) / ui32SampleRate; // 60 frame rate.
      else
         ui64VideoUnit = (in_ui64AudioSamples  * (60)) / ui32SampleRate; // 60 frame rate.
      break;
   case keMvFrameRate60M: // this is 59.94 rate in frame or fields
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) 
      {
         // set reference position in sequence
         int64_t iRefIndex = in_i64RefVideoUnit%5; 
         if(iRefIndex < 0)
         {
            iRefIndex = 5 + iRefIndex;             // adjust index for negative references
         }

         // Sequence is made of 5 fields. The durations of those fields @ ref zero are:
         // 400 - 401 - 400 - 400 - 401 (in samples)
         uint64_t ui645FieldSequence = ( in_ui64AudioSamples / 2002 );           // The amount of complete 5 fields sequences...
         uint64_t ui645FieldSequenceInSamples = ( ui645FieldSequence * 2002 );   // ...converted back into samples

         // Find the number of fields of the unfinished sequence (remainder)
         uint64_t ui64RemainderInSamples = in_ui64AudioSamples - ui645FieldSequenceInSamples;

         uint64_t ui64RemainderInFields = 0;

         if (ui64RemainderInSamples >= kaui64AudioSeq60MField[4][iRefIndex])
         {
            ui64RemainderInFields = 4;
         }
         else if (ui64RemainderInSamples >= kaui64AudioSeq60MField[3][iRefIndex])
         {
            ui64RemainderInFields = 3;
         }
         else if (ui64RemainderInSamples >= kaui64AudioSeq60MField[2][iRefIndex])
         {
            ui64RemainderInFields = 2;
         }
         else if (ui64RemainderInSamples >= kaui64AudioSeq60MField[1][iRefIndex])
         {
            ui64RemainderInFields = 1;
         }

         ui64VideoUnit = ui645FieldSequence * 5 + ui64RemainderInFields;
      }
      else
      {
         // set reference position in sequence
         int64_t iRefIndex = in_i64RefVideoUnit%5; 
         if(iRefIndex < 0)
         {
            iRefIndex = 5 + iRefIndex;             // adjust index for negative references
         }

         // Sequence is made of 5 frames. The durations of those frames @ ref zero are:
         // 801 - 801 - 800 - 801 - 801 (in samples)
         uint64_t ui645FrameSequence = ( in_ui64AudioSamples / 4004 );           // The amount of complete 5 frames sequences...
         uint64_t ui645FrameSequenceInSamples = ( ui645FrameSequence * 4004 );   // ...converted back into samples

         // Find the number of frames of the unfinished sequence (remainder)
         uint64_t ui64RemainderInSamples = in_ui64AudioSamples - ui645FrameSequenceInSamples;
         uint64_t ui64RemainderInFrames = 0;

         // 60M frames is identical to 30M fields table
         if (ui64RemainderInSamples >= kaui64AudioSeq30MField[4][iRefIndex])
         {
            ui64RemainderInFrames = 4;
         }
         else if (ui64RemainderInSamples >= kaui64AudioSeq30MField[3][iRefIndex])
         {
            ui64RemainderInFrames = 3;
         }
         else if (ui64RemainderInSamples >= kaui64AudioSeq30MField[2][iRefIndex])
         {
            ui64RemainderInFrames = 2;
         }
         else if (ui64RemainderInSamples >= kaui64AudioSeq30MField[1][iRefIndex])
         {
            ui64RemainderInFrames = 1;
         }

         ui64VideoUnit = ui645FrameSequence * 5 + ui64RemainderInFrames;
      }
      break;
   default:
      break;
   }
   return ui64VideoUnit;
}

/////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Returns the audio sample count needed for the specified video frames.
//
// Example:
//    You can use this function to evaluate how many audio samples you need for "d" video frames of
//    duration at a specific video frame reference. To do so you set 
//    in_ui64VideoFrame = d and pass your video frame reference in in_i64RefVideoFrame.
//
//       SampleLength = MvGetAudioSamplesFromReferencedVideoFrames(d, YourFrameReference, eVideoFrameRate)
//
//    In this example the duration is static and the reference in the audio sequence is dynamic 
//    (YourFrameReference). Since this function applies a modulo "sequence length" to the reference,
//    successive calls with your next video frame reference will return the sample values contained in the
//    audio sequence.
//
//    In NTSC at 29.97 fps, with duration = 1 frame
//    <CODE>
//    MvGetAudioSamplesFromReferencedVideoFrames(1, 0, eVideoFrameRate) = 1602
//    MvGetAudioSamplesFromReferencedVideoFrames(1, 1, eVideoFrameRate) = 1601
//    MvGetAudioSamplesFromReferencedVideoFrames(1, 2, eVideoFrameRate) = 1602
//    MvGetAudioSamplesFromReferencedVideoFrames(1, 3, eVideoFrameRate) = 1601
//    MvGetAudioSamplesFromReferencedVideoFrames(1, 4, eVideoFrameRate) = 1602
//    MvGetAudioSamplesFromReferencedVideoFrames(1, 5, eVideoFrameRate) = 1602, and so forth...
//    </CODE>
//
// Example:
//    You can use this function to evaluate a position in audio samples for a "p" position in video
//    frames with a reference in the audio sequence. Supposing that we want to start at the first
//    position of the audio sequence, set in_ui64VideoFrame = p and in_i64RefVideoFrame = 0;
//
//       SamplePosition = MvGetAudioSamplesFromReferencedVideoFrames(p, 0, eVideoFrameRate)
//
//    In this example the position is dynamic and the reference in the audio sequence is static.
//
//    In NTSC at 29.97 fps, with reference = 0
//    <CODE>
//    MvGetAudioSamplesFromReferencedVideoFrames(1, 0, eVideoFrameRate) = 1602
//    MvGetAudioSamplesFromReferencedVideoFrames(2, 0, eVideoFrameRate) = 3203
//    MvGetAudioSamplesFromReferencedVideoFrames(3, 0, eVideoFrameRate) = 4805
//    MvGetAudioSamplesFromReferencedVideoFrames(4, 0, eVideoFrameRate) = 6406
//    </CODE>
//
//    In NTSC at 29.97 fps, with reference = 1 (start forward in sequence)
//    <CODE>
//    MvGetAudioSamplesFromReferencedVideoFrames(1, 1, eVideoFrameRate) = 1601
//    MvGetAudioSamplesFromReferencedVideoFrames(2, 1, eVideoFrameRate) = 3203
//    MvGetAudioSamplesFromReferencedVideoFrames(3, 1, eVideoFrameRate) = 4804
//    MvGetAudioSamplesFromReferencedVideoFrames(4, 1, eVideoFrameRate) = 6406
//    </CODE>
//
// Remarks:
//    - Used to maintain the proper audio sequence for 23.98, 29.97, and 59.94 fps video frequencies.
//    - Changing the reference in an audio sequence will return different values for 29.97 and 59.94 fps only.
//
/////////////////////////////////////////////////////////////////////////////////
inline uint64_t MvGetAudioSamplesFromReferencedVideoFrames
   (
   uint64_t     in_ui64VideoFrame,     // Position or duration in video frames.
   int64_t      in_i64RefVideoFrame,   // Reference in video frames into the audio sequence. 
                                       // This reference tells only where to start in the 
                                       // audio sequence. Both negative and positive
                                       // references are supported. Values greater than 
                                       // the sequence length are "moduloed". 
                                       // (in_i64RefVideoFrame % (sequence length)) 
                                       // This parameter is used for 29.97 and 59.94 fps only.
   EMvFrameRate in_eVideoFrameRate,    // Video frame rate. 
   uint64_t in_ui64FrameRateNum,
   uint64_t in_ui64FrameRateDenum	   // Variable frame rate value.	
   )
{
   uint64_t ui64Samples = 0;
   switch (in_eVideoFrameRate)
   {
   case keMvFrameRateVariable:
      ui64Samples = in_ui64VideoFrame * ((48000*in_ui64FrameRateDenum)/in_ui64FrameRateNum);       // where 2000 = 48000/24
      break;
   case keMvFrameRate24:
      ui64Samples = in_ui64VideoFrame * 2000;       // where 2000 = 48000/24
      break;
   case keMvFrameRate24M:
      ui64Samples = in_ui64VideoFrame * 2002;       // where 2002 = 48000/(24 * 1000/1001 )
      break;
   case keMvFrameRate25:
      ui64Samples = in_ui64VideoFrame * 1920;       // where 1920 = 48000/25
      break;
   case keMvFrameRate30:
      ui64Samples = in_ui64VideoFrame * 1600;       // where 1600 = 48000/30
      break;
   case keMvFrameRate30M:  // this is 29.97 rate in frames, we need to do special calculations for sequence
      {
         int64_t iRefIndex = in_i64RefVideoFrame%5;
         if(iRefIndex < 0)
         {
            iRefIndex = 5 + iRefIndex;
         }
         ui64Samples = (( in_ui64VideoFrame / 5 ) * 8008 ) + kaui64AudioSeq30MFrame[in_ui64VideoFrame%5][iRefIndex];
      }
      break;
   case keMvFrameRate50:
      ui64Samples = in_ui64VideoFrame * 960;        // where 960 = 48000/50
      break;
   case keMvFrameRate60:
      ui64Samples = in_ui64VideoFrame * 800;        // where 800 = 48000/60
      break;
   case keMvFrameRate60M: // this is 59.98 rate in frames, we need to do special calculations for sequence
      {
         int64_t iRefIndex = in_i64RefVideoFrame%5;
         if(iRefIndex < 0)
         {
            iRefIndex = 5 + iRefIndex;
         }
         ui64Samples = (( in_ui64VideoFrame / 5 ) * 4004 ) + kaui64AudioSeq30MField[in_ui64VideoFrame%5][iRefIndex]; //60M FRAME shares the same LUT as 30M Field
      }
      break;
   default:
      break;
   }
   return ui64Samples;
}

/////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Returns the video frames corresponding to the specified audio sample count.
//
// Remarks:
//    - Used to maintain the proper audio sequence for 23.98, 29.97, and 59.94 fps video frequencies.
//    - When the frame rate is 29.97 or 59.94 fps, one audio sample can make a difference depending on the position 
//      in the audio sequence. For example, in NTSC at 29.97 fps MvGetReferencedVideoFramesFromAudioSamples(1601, 0, eVideoFrameRate) 
//      will return 0, because the first frame must contain 1602 samples. That is, 1 sample is missing to complete the frame. 
//      However, MvGetReferencedVideoFramesFromAudioSamples(1601, 1, eVideoFrameRate) will
//      return 1 frame because a frame duration at a reference of 1 in the audio sequence is expected to be 1601.
// 
/////////////////////////////////////////////////////////////////////////////////
inline uint64_t MvGetReferencedVideoFramesFromAudioSamples
   (
   uint64_t     in_ui64AudioSamples,   // Position or duration in audio samples.
   int64_t      in_i64RefVideoFrame,   // Reference in video frames into the audio 
                                       // sequence. This reference tells only where
                                       // to start in the audio sequence. Both 
                                       // negative and positive references are 
                                       // supported. Values greater than the sequence
                                       // length are "moduloed". 
                                       // (in_i64RefVideoFrame % (sequence length)) 
                                       // This parameter is used for 29.97 and 59.94 fps only.
   EMvFrameRate in_eVideoFrameRate,     // Video frame rate. 
   uint64_t in_ui64FrameRateNum,
   uint64_t in_ui64FrameRateDenum	   // Variable frame rate value.
   )
{
   uint64_t ui64VideoUnit = 0;
   uint32_t ui32SampleRate = 48000;
   switch (in_eVideoFrameRate)
   {
   case keMvFrameRateVariable:
      ui64VideoUnit = ( ((in_ui64AudioSamples *in_ui64FrameRateNum)/in_ui64FrameRateDenum))/ ui32SampleRate;       // 24 frame rate.
      break;
   case keMvFrameRate24:
      ui64VideoUnit = (in_ui64AudioSamples * (24))/ ui32SampleRate;       // 24 frame rate.
      break;
   case keMvFrameRate24M:
      ui64VideoUnit = (in_ui64AudioSamples / 2002);                     // sequence is 2002 samples/frame @ 48KHz
      break;
   case keMvFrameRate25:
      ui64VideoUnit = (in_ui64AudioSamples * (25)) / ui32SampleRate;      // 25 frame rate.
      break;
   case keMvFrameRate30:
      ui64VideoUnit = (in_ui64AudioSamples * (30)) / ui32SampleRate;      // 30 frame rate.
      break;
   case keMvFrameRate30M: 
      {
         // set reference position in sequence
         int64_t iRefIndex = in_i64RefVideoFrame%5; 
         if(iRefIndex < 0)
         {
            iRefIndex = 5 + iRefIndex;             // adjust index for negative references
         }

         // Sequence is made of 5 frames. The durations of those frames @ ref zero are:
         // 1602 - 1601 - 1602 - 1601 - 1602 (in samples)
         uint64_t ui645FrameSequence = ( in_ui64AudioSamples / 8008 );           // The amount of complete 5 frames sequences...
         uint64_t ui645FrameSequenceInSamples = ( ui645FrameSequence * 8008 );   // ...converted back into samples

         // Find the number of frames of the unfinished sequence (remainder)
         uint64_t ui64RemainderInSamples = in_ui64AudioSamples - ui645FrameSequenceInSamples;
         uint64_t ui64RemainderInFrames = 0;

         if (ui64RemainderInSamples >= kaui64AudioSeq30MFrame[4][iRefIndex])
         {
            ui64RemainderInFrames = 4;
         }
         else if (ui64RemainderInSamples >= kaui64AudioSeq30MFrame[3][iRefIndex])
         {
            ui64RemainderInFrames = 3;
         }
         else if (ui64RemainderInSamples >= kaui64AudioSeq30MFrame[2][iRefIndex])
         {
            ui64RemainderInFrames = 2;
         }
         else if (ui64RemainderInSamples >= kaui64AudioSeq30MFrame[1][iRefIndex])
         {
            ui64RemainderInFrames = 1;
         }

         ui64VideoUnit = ui645FrameSequence * 5 + ui64RemainderInFrames;
      }
      break;
   case keMvFrameRate50:
      ui64VideoUnit = (in_ui64AudioSamples * (50)) / ui32SampleRate; // 50 frame rate.
      break;
   case keMvFrameRate60:
      ui64VideoUnit = (in_ui64AudioSamples  * (60)) / ui32SampleRate; // 60 frame rate.
      break;
   case keMvFrameRate60M: // this is 59.94 rate in frames
      {
         // set reference position in sequence
         int64_t iRefIndex = in_i64RefVideoFrame%5; 
         if(iRefIndex < 0)
         {
            iRefIndex = 5 + iRefIndex;             // adjust index for negative references
         }

         // Sequence is made of 5 frames. The durations of those frames @ ref zero are:
         // 801 - 801 - 800 - 801 - 801 (in samples)
         uint64_t ui645FrameSequence = ( in_ui64AudioSamples / 4004 );           // The amount of complete 5 frames sequences...
         uint64_t ui645FrameSequenceInSamples = ( ui645FrameSequence * 4004 );   // ...converted back into samples

         // Find the number of frames of the unfinished sequence (remainder)
         uint64_t ui64RemainderInSamples = in_ui64AudioSamples - ui645FrameSequenceInSamples;
         uint64_t ui64RemainderInFrames = 0;

         // 60M frames is identical to 30M fields table
         if (ui64RemainderInSamples >= kaui64AudioSeq30MField[4][iRefIndex])
         {
            ui64RemainderInFrames = 4;
         }
         else if (ui64RemainderInSamples >= kaui64AudioSeq30MField[3][iRefIndex])
         {
            ui64RemainderInFrames = 3;
         }
         else if (ui64RemainderInSamples >= kaui64AudioSeq30MField[2][iRefIndex])
         {
            ui64RemainderInFrames = 2;
         }
         else if (ui64RemainderInSamples >= kaui64AudioSeq30MField[1][iRefIndex])
         {
            ui64RemainderInFrames = 1;
         }

         ui64VideoUnit = ui645FrameSequence * 5 + ui64RemainderInFrames;
      }
      break;
   default:
      break;
   }
   return ui64VideoUnit;
}

/////////////////////////////////////////////////////////////////////////////////
// MvGetAudioSamplesFromFrame: Obtains the corresponding sample count for x amount of video unit (eRes). - support 48KHz only
//
// ***** WARNING! *****
// THIS FUNCTION IS OBSOLETE NOT ACCURATE. WILL BE REMOVED IN THE FUTURE.
// YOU MUST USE MvGetAudioSamplesFromReferencedVideoUnits() INSTEAD.
// *****
//
/////////////////////////////////////////////////////////////////////////////////
inline uint64_t MvGetAudioSamplesFromVideoUnit(uint64_t in_ui64VideoUnit, const SMvResolutionInfo& in_rsResolutionInfo,  uint64_t in_ui64FrameRateNum,uint64_t in_ui64FrameRateDenum)
{
   uint64_t ui64Samples = 0;
   switch(in_rsResolutionInfo.eFrameRate)
   {
   case keMvFrameRateVariable:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode divided by 2
         ui64Samples = in_ui64VideoUnit * ((48000*in_ui64FrameRateDenum)/in_ui64FrameRateNum) / 2; // where 2000 = 48000/24
      else
         ui64Samples = in_ui64VideoUnit * ((48000*in_ui64FrameRateDenum)/in_ui64FrameRateNum); // where 2000 = 48000/24
      break;

   case keMvFrameRate24:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode divided by 2
         ui64Samples = in_ui64VideoUnit * 2000 / 2; // where 2000 = 48000/24
      else
         ui64Samples = in_ui64VideoUnit * 2000; // where 2000 = 48000/24
      break;
   case keMvFrameRate24M:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode divided by 2
         ui64Samples = in_ui64VideoUnit * 2002 / 2; // where 2002 = 48000/(24 * 1000/1001 )
      else
         ui64Samples = in_ui64VideoUnit * 2002; // where 2002 = 48000/(24 * 1000/1001 )
      break;
   case keMvFrameRate25:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode divided by 2
         ui64Samples =in_ui64VideoUnit * 1920 / 2; // where 1920 = 48000/25
      else
         ui64Samples = in_ui64VideoUnit * 1920; // where 1920 = 48000/25
      break;
   case keMvFrameRate30:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode divided by 2
         ui64Samples = in_ui64VideoUnit * 1600 / 2; // where 1600 = 48000/30
      else
         ui64Samples = in_ui64VideoUnit * 1600; // where 1600 = 48000/30
      break;
   case keMvFrameRate30M: // ntsc frame
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we need to do special calculations for NTSC
         ui64Samples = ( ( in_ui64VideoUnit / 10 ) * 8008 ) + ( ( ( ( in_ui64VideoUnit % 10 ) * 8008 ) + 5 ) / 10 );
      else
         ui64Samples = ( ( in_ui64VideoUnit / 5 ) * 8008 ) + ( ( ( ( in_ui64VideoUnit % 5 ) * 16016 ) + 5 ) / 10 );
      break;
   case keMvFrameRate50:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode divided by 2
         ui64Samples = in_ui64VideoUnit * 960 / 2; // where 960 = 48000/50
      else
         ui64Samples = in_ui64VideoUnit * 960; // where 960 = 48000/50
      break;
   case keMvFrameRate60:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode divided by 2
         ui64Samples = in_ui64VideoUnit * 800 / 2; // where 800 = 48000/60
      else
         ui64Samples = in_ui64VideoUnit * 800; // where 800 = 48000/60
      break;
   case keMvFrameRate60M: // this is 59.98 rate in frame or fields
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we need to do special calculations for sequence
         ui64Samples = ( ( in_ui64VideoUnit / 20 ) * 8008 ) + ( ( ( ( in_ui64VideoUnit % 20 ) * 4004 ) + 5 ) / 10 );
      else
         ui64Samples = ( ( in_ui64VideoUnit / 10 ) * 8008 ) + ( ( ( ( in_ui64VideoUnit % 10 ) * 8008 ) + 5 ) / 10 );
      break;
   default:
      break;
   }
   return ui64Samples;
}

/////////////////////////////////////////////////////////////////////////////////
// MvGetFrameFromAudioSamples: Obtains the corresponding frame count (video unit) from x amount of audio Samples. - support 48KHz only
//
// ***** WARNING! *****
// THIS FUNCTION IS OBSOLETE NOT ACCURATE. WILL BE REMOVED IN THE FUTURE.
// YOU MUST USE MvGetReferencedVideoUnitsFromAudioSamples() INSTEAD.
// *****
//
/////////////////////////////////////////////////////////////////////////////////
inline uint64_t MvGetVideoUnitFromAudioSamples(uint64_t in_ui64AudioSamples, const SMvResolutionInfo& in_rsResolutionInfo,  uint64_t in_ui64FrameRateNum,uint64_t in_ui64FrameRateDenum)
{
   uint64_t ui64VideoUnit = 0;
   uint32_t ui32SampleRate = 48000;
   switch(in_rsResolutionInfo.eFrameRate)
   {
  case keMvFrameRateVariable:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode multiplied by 2
         ui64VideoUnit = (((in_ui64AudioSamples *in_ui64FrameRateNum)/in_ui64FrameRateDenum) * 2) / ui32SampleRate; // 24 frame rate.
      else
         ui64VideoUnit = (((in_ui64AudioSamples *in_ui64FrameRateNum)/in_ui64FrameRateDenum))/ ui32SampleRate; // 24 frame rate.
      break;
   case keMvFrameRate24:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode multiplied by 2
         ui64VideoUnit = (in_ui64AudioSamples * (24 * 2)) / ui32SampleRate; // 24 frame rate.
      else
         ui64VideoUnit = (in_ui64AudioSamples * (24))/ ui32SampleRate; // 24 frame rate.
      break;
   case keMvFrameRate24M:
      // in all 1000/1001 mode, we need to add 1 sample so the calculation we get is rounded to the correct integer.
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode multiplied by 2
         ui64VideoUnit = ((in_ui64AudioSamples+1)*(24 * 2 * 1000)) / (ui32SampleRate * 1001); // 24M frame rate = (24 * 2 * 1000/1001)
      else
         ui64VideoUnit = ((in_ui64AudioSamples+1) * (24 * 1000)) / (ui32SampleRate * 1001); // 24M frame rate = (24 * 1000/1001)
      break;
   case keMvFrameRate25:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode multiplied by 2
         ui64VideoUnit = (in_ui64AudioSamples * (25 * 2)) / ui32SampleRate; // 25 frame rate.
      else
         ui64VideoUnit = (in_ui64AudioSamples * (25)) / ui32SampleRate; // 25 frame rate.
      break;
   case keMvFrameRate30:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode multiplied by 2
         ui64VideoUnit = (in_ui64AudioSamples * (30 * 2)) / ui32SampleRate; // 30 frame rate.
      else
         ui64VideoUnit = (in_ui64AudioSamples * (30)) / ui32SampleRate; // 30 frame rate.
      break;
   case keMvFrameRate30M: // ntsc frame
      // in all 1000/1001 mode, we need to add 1 sample so the calculation we get is rounded to the correct integer.
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode multiplied by 2
      {
         // Sequence is made of 5 fields. The durations of those fields are:
         // 801 - 801 - 800 - 801 - 801 (in samples)
         uint64_t ui645FieldSequence = ( in_ui64AudioSamples / 4004 );           // The amount of complete 5 fields sequences...
         uint64_t ui645FieldSequenceInSamples = ( ui645FieldSequence * 4004 );   // ...converted back into samples

         // Find the number of fields of the unfinished sequence (remainder)
         uint64_t ui64RemainderInSamples = in_ui64AudioSamples - ui645FieldSequenceInSamples;
         uint64_t ui64RemainderInFields = 0;

         if (ui64RemainderInSamples >= 3203)
         {
            ui64RemainderInFields = 4;
         }
         else if (ui64RemainderInSamples >= 2402)
         {
            ui64RemainderInFields = 3;
         }
         else if (ui64RemainderInSamples >= 1602)
         {
            ui64RemainderInFields = 2;
         }
         else if (ui64RemainderInSamples >= 801)
         {
            ui64RemainderInFields = 1;
         }

         ui64VideoUnit = ui645FieldSequence * 5 + ui64RemainderInFields;
      }
      else
      {
         // Sequence is made of 5 frames. The durations of those frames are:
         // 1602 - 1601 - 1602 - 1601 - 1602 (in samples)
         uint64_t ui645FrameSequence = ( in_ui64AudioSamples / 8008 );           // The amount of complete 5 frames sequences...
         uint64_t ui645FrameSequenceInSamples = ( ui645FrameSequence * 8008 );   // ...converted back into samples

         // Find the number of frames of the unfinished sequence (remainder)
         uint64_t ui64RemainderInSamples = in_ui64AudioSamples - ui645FrameSequenceInSamples;
         uint64_t ui64RemainderInFrames = 0;

         if (ui64RemainderInSamples >= 6406)
         {
            ui64RemainderInFrames = 4;
         }
         else if (ui64RemainderInSamples >= 4805)
         {
            ui64RemainderInFrames = 3;
         }
         else if (ui64RemainderInSamples >= 3203)
         {
            ui64RemainderInFrames = 2;
         }
         else if (ui64RemainderInSamples >= 1602)
         {
            ui64RemainderInFrames = 1;
         }

         ui64VideoUnit = ui645FrameSequence * 5 + ui64RemainderInFrames;
      }
      break;
   case keMvFrameRate50:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode multiplied by 2
         ui64VideoUnit = (in_ui64AudioSamples * (50 * 2 )) / ui32SampleRate; // 50 frame rate.
      else
         ui64VideoUnit = (in_ui64AudioSamples * (50)) / ui32SampleRate; // 50 frame rate.
      break;
   case keMvFrameRate60:
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode multiplied by 2
         ui64VideoUnit = (in_ui64AudioSamples * (60 * 2)) / ui32SampleRate; // 60 frame rate.
      else
         ui64VideoUnit = (in_ui64AudioSamples  * (60)) / ui32SampleRate; // 60 frame rate.
      break;
   case keMvFrameRate60M: // this is 59.94 rate in frame or fields
      // in all 1000/1001 mode, we need to add 1 sample so the calculation we get is rounded to the correct integer.
      if(in_rsResolutionInfo.eScanMode == keMvScanModeFirstFieldTop || 
         in_rsResolutionInfo.eScanMode == keMvScanModeSecondFieldTop) // we are in field mode multiply by 2
         ui64VideoUnit = ((in_ui64AudioSamples+1) * (60 * 2 * 1000)) / (ui32SampleRate * 1001); // 60M frame rate = (60 * 2 * 1000/1001)
      else
      {
         // Sequence is made of 5 frames. The durations of those frames are:
         // 801 - 801 - 800 - 801 - 801 (in samples)
         uint64_t ui64FrameSequence = in_ui64AudioSamples / 4004;          // The amount of complete 5 frames sequences...
         uint64_t ui645FrameSequenceInSamples = ui64FrameSequence * 4004;   // ...converted back into samples

         // Find the number of frames of the unfinished sequence (remainder)
         uint64_t ui64RemainderInSamples = in_ui64AudioSamples - ui645FrameSequenceInSamples;
         uint64_t ui64RemainderInFrames = 0;

         if (ui64RemainderInSamples >= 3203)
         {
            ui64RemainderInFrames = 4;
         }
         else if (ui64RemainderInSamples >= 2402)
         {
            ui64RemainderInFrames = 3;
         }
         else if (ui64RemainderInSamples >= 1602)
         {
            ui64RemainderInFrames = 2;
         }
         else if (ui64RemainderInSamples >= 801)
         {
            ui64RemainderInFrames = 1;
         }

         ui64VideoUnit = (ui64FrameSequence * 5) + ui64RemainderInFrames;
      }
      break;
   default:
      break;
   }
   return ui64VideoUnit;
}

#ifdef MAC_PLATFORM
};  // namespace com_matrox_vpg_SDK
#endif

