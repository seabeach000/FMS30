//==========================================================================;
//
// (c) Copyright Matrox Electronic Systems Ltd., 2005. All rights reserved.
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
//==========================================================================;
//                    mvFLexDefinitionsQT.h
//==========================================================================;
// @module  Matrox Video
//==========================================================================;
//   Birth Date:             August 15 2006  
//   Operating System:       WinXP
//   Author:                 François Dagenais
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#ifndef _FLEX_MVFLEXDEFINITIONSQT_H
#define _FLEX_MVFLEXDEFINITIONSQT_H

//
// Summary:
//    Holds the information related to one codec type returned by the keMvFlexQTClipWriterOptions_CodecTypesList
//    option.
//
struct SMvFlexQTClipWriterCodecTypeInfo
{
   long  lCodecTypeCode;   // FourCharCode stored as a long representing the code of the codec type. 
                              // This is the code that should be passed to the 
                              // keMvFlexQTClipWriterOptions_CodecType option of the QuickTime Clip Writer.
   char  szName[32];       // NULL terminated string containing the name of the codec type.
};

//
// Summary:
//    Constants representing the most common compression types. Use with the 
//    keMvFlexQTClipWriterOptions_CodecType option (see EMvFlexQTClipWriterOptions).
//
enum EMvFlexQTClipWriterCodecTypes
{
   keMvFlexQTClipWriterCodecType_Raw         = 'raw ',   // Raw data. No compression will be done.
   keMvFlexQTClipWriterCodecType_Cinepak     = 'cvid',   // Cinepak compression
   keMvFlexQTClipWriterCodecType_H261        = 'h261',   // H261 compression
   keMvFlexQTClipWriterCodecType_H263        = 'h263',   // H263 compression
   keMvFlexQTClipWriterCodecType_DVCNTSC     = 'dvc ',   // DV - NTSC and DVCPRO NTSC compression. This
                                                            // codec type will output data in NTSC 
                                                            // (720x480). If the source size is different 
                                                            // it will resize it.
   keMvFlexQTClipWriterCodecType_DVCPAL      = 'dvcp',   // DVC PAL compression. This codec type will
                                                            // output data in PAL (720x576). If the 
                                                            // source size is different it will resize it.
   keMvFlexQTClipWriterCodecType_Sorenson    = 'SVQ1',   // Sorenson compression.
   keMvFlexQTClipWriterCodecType_Sorenson3   = 'SVQ3',   // Sorenson3 compression.
   keMvFlexQTClipWriterCodecType_Indeo4      = 'IV41',   // Indeo4 compression.
   keMvFlexQTClipWriterCodecType_MPEG4       = 'mp4v',   // MPEG4 video compression.
   keMvFlexQTClipWriterCodecType_H264        = 'avc1',    // H264 compression.
   keMvFlexQTClipWriterCodecType_RLE         = 'rle ',    // Animation. Can specify YUYV422 or YUAYVA4224
   keMvFlexQTClipWriterCodecType_DNx_Alpha   = 'AVdn'     // Avid DNx with alpha. Can specify YUYV422 or YUAYVA4224
};
// Summary:
//    Specifies the formats available for encoding DNxHD using QuickTime.
//
enum EMvQTDNxHDResolution   
{
   keQTDNxHDResolutionInvalid,               // Invalid value.
   keQTDNxHD_1080i60M_220_8bit,              // 1080i/59.94 fps, DNxHD 220, 8-bit
   keQTDNxHD_1080i60M_145_8bit,              // 1080i/59.94 fps, DNxHD 145, 8-bit
   keQTDNxHD_1080i50_185_8bit,               // 1080i/50 fps, DNxHD 185, 8-bit
   keQTDNxHD_1080i50_120_8bit,               // 1080i/50 fps, DNxHD 120, 8-bit
   keQTDNxHD_1080p25_185_8bit,               // 1080p/25 fps, DNxHD 185, 8-bit
   keQTDNxHD_1080p25_120_8bit,               // 1080p/25 fps, DNxHD 120, 8-bit
   keQTDNxHD_1080p25_36_8bit,                // 1080p/25 fps, DNxHD 36, 8-bit
   keQTDNxHD_1080p24M_175_8bit,              // 1080p/23.976 fps, DNxHD 175, 8-bit
   keQTDNxHD_1080p24M_115_8bit,              // 1080p/23.976 fps, DNxHD 115, 8-bit
   keQTDNxHD_1080p24M_36_8bit,               // 1080p/23.976 fps, DNxHD 36, 8-bit
   keQTDNxHD_1080p24_175_8bit,               // 1080p/24 fps, DNxHD 175, 8-bit
   keQTDNxHD_1080p24_115_8bit,               // 1080p/23.976 fps, DNxHD 115, 8-bit
   keQTDNxHD_1080p24_36_8bit,                // 1080p/24 fps, DNxHD 36, 8-bit
   keQTDNxHD_720p60M_220_8bit,               // 720p/59.94 fps, DNxHD 220, 8-bit
   keQTDNxHD_720p60M_145_8bit,               // 720p/59.94 fps, DNxHD 145, 8-bit
   keQTDNxHD_720p24M_90_8bit,                // 720p/23.976 fps, DNxHD 90, 8-bit
   keQTDNxHD_720p24M_60_8bit,                // 720p/23.976 fps, DNxHD 60, 8-bit
   keQTDNxHD_720p30M_110_8bit,               // 720p/29.97 fps, DNxHD 110, 8-bit
   keQTDNxHD_720p30M_75_8bit,                // 720p/29.97 fps, DNxHD 75, 8-bit
   keQTDNxHD_720p25_60_8bit,                 // 720p/25 fps, DNxHD 60, 8-bit
   keQTDNxHD_1080i60M_TR145_8bit,            // 1080i/59.94 fps thin raster (1440 x 1080), DNxHD 145, 8-bit
   keQTDNxHD_1080i50_TR120_8bit,             // 1080i/50 fps thin raster (1440 x 1080), DNxHD 120, 8-bit
   keQTDNxHD_720p50_185_8bit,                // 720p/50 fps, DNxHD 185, 8-bit
   keQTDNxHD_720p50_120_8bit,                // 720p/50 fps, DNxHD 120, 8-bit
   keQTDNxHDResolutionLast                   // End of list indicator.
};

// Summary:
// This macro is used to get the string corresponding to the EMvQTDNxHDResolution enum value.
//
#define MV_DNXHD_RESOLUTION_ENUM_TO_STRING(eMvQTDNxHDResolution) \
   ((eMvQTDNxHDResolution == keQTDNxHD_1080i60M_220_8bit) ? ("1080i/59.94 fps, DNxHD 220, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_1080i60M_145_8bit)  ? ("1080i/59.94 fps, DNxHD 145, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_1080i50_185_8bit) ? ("1080i/50 fps, DNxHD 185, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_1080i50_120_8bit) ? ("1080i/50 fps, DNxHD 120, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_1080p25_185_8bit) ? ("1080p/25 fps, DNxHD 185, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_1080p25_120_8bit)? ("1080p/25 fps, DNxHD 120, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_1080p25_36_8bit)  ? ("1080p/25 fps, DNxHD 36, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_1080p24M_175_8bit) ? ("1080p/23.976 fps, DNxHD 175, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_1080p24M_115_8bit) ? ("1080p/23.976 fps, DNxHD 115, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_1080p24M_36_8bit) ? ("1080p/23.976 fps, DNxHD 36, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_1080p24_175_8bit)? ("1080p/24 fps, DNxHD 175, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_1080p24_115_8bit)  ? ("1080p/24 fps, DNxHD 115, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_1080p24_36_8bit) ? ("1080p/24 fps, DNxHD 36, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_720p60M_220_8bit) ? ("720p/59.94 fps, DNxHD 220, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_720p60M_145_8bit) ? ("720p/59.94 fps, DNxHD 145, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_720p24M_90_8bit)? ("720p/23.976 fps, DNxHD 90, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_720p24M_60_8bit)  ? ("720p/23.976 fps, DNxHD 60, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_720p30M_110_8bit) ? ("720p/29.97 fps, DNxHD 110, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_720p30M_75_8bit) ? ("720p/29.97 fps, DNxHD 75, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_720p25_60_8bit) ? ("720p/25 fps, DNxHD 60, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_1080i60M_TR145_8bit)? ("1080i/59.94 fps thin raster (1440 x 1080), DNxHD 145, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_1080i50_TR120_8bit) ? ("1080i/50 fps thin raster (1440 x 1080), DNxHD 120, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_720p50_185_8bit) ? ("720p/50 fps, DNxHD 185, 8-bit") : \
   (eMvQTDNxHDResolution == keQTDNxHD_720p50_120_8bit)? ("720p/50 fps, DNxHD 120, 8-bit") : \
   ("???"))

//
// Summary:
//    Specifies the alpha component of the DNxHD encoding using QuickTime.
//
enum EMvQTDNxHDAlpha
{
   keQTDNxHDNoAlpha,             // Indicates that the DNxHD encoding does not contain alpha.
   keQTDNxHDCompressedAlpha,     // Indicates that the DNxHD encoding contains compressed alpha.
   keQTDNxHDUncompressedAlpha    // Indicates that the DNxHD encoding contains uncompressed alpha.
};
//
// Summary:
//    Specifies the options for encoding DNxHD with alpha using QuickTime.
//
struct SMvQTDNxHDCompressorOptions 
{
   uint32_t                   size;                   // Size of the structure in bytes.
   EMvQTDNxHDResolution       eResolution;            // Indicates the DNxHD encoding format.
   EMvQTDNxHDAlpha            eAlpha;                 // Indicates the alpha component of the DNxHD encoding. 
};
//
// Summary:
//    Used to determine if we should check if the current capture is DV PAL since it requires special processing
//
enum EMvVideoCaptureFormat
{
   keMvVideoCaptureFormatUnknown,
   keMvVideoCaptureFormatDVPAL,
   keMvVideoCaptureFormatOther
};

inline bool IsCodecTypeWithAlpha( long in_lCodecType)
{
   if ((in_lCodecType == keMvFlexQTClipWriterCodecType_RLE) || (in_lCodecType == keMvFlexQTClipWriterCodecType_DNx_Alpha))
      return true;
   return false;
}

#endif   // _FLEX_MVFLEXDEFINITIONSQT_H