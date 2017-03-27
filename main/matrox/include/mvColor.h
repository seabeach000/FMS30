//==============================================================================
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
//===============================================================================
#pragma once

#ifdef LINUX_PLATFORM
	#include "mvLinuxDefinitions.h"
#else
	#include <windows.h>
	#include <unknwn.h>
#endif

#include <math.h>
#include "mvFlex3DDeviceStructs.h"
#include "mvDefinitions.h"

// RGB-YCBCR SD Video
#define g_kfRVideoYSD      0.299000f
#define g_kfGVideoYSD      0.587000f
#define g_kfBVideoYSD      0.114000f

#define g_kfRVideoCbSD     0.172588f
#define g_kfGVideoCbSD     0.338827f
#define g_kfBVideoCbSD     0.511416f

#define g_kfRVideoCrSD     0.511416f
#define g_kfGVideoCrSD     0.428247f
#define g_kfBVideoCrSD     0.083169f

#define g_kfYVideoSD       1.000000f
#define g_kfCrRVideoSD     1.370705f
#define g_kfCrGVideoSD     0.698196f
#define g_kfCbBVideoSD     1.732446f
#define g_kfCbGVideoSD     0.336455f

// RGB-YCBCR SD Graphic
#define g_kfRGraphicYSD    0.256788f
#define g_kfGGraphicYSD    0.504129f
#define g_kfBGraphicYSD    0.097906f

#define g_kfRGraphicCbSD   0.148223f
#define g_kfGGraphicCbSD   0.290993f
#define g_kfBGraphicCbSD   0.439216f

#define g_kfRGraphicCrSD   0.439216f
#define g_kfGGraphicCrSD   0.367788f
#define g_kfBGraphicCrSD   0.071427f

#define g_kfYGraphicSD     1.164384f
#define g_kfCrRGraphicSD   1.596027f
#define g_kfCrGGraphicSD   0.812968f
#define g_kfCbBGraphicSD   2.017232f
#define g_kfCbGGraphicSD   0.391762f

// RGB-YCBCR HD Video
#define g_kfRVideoYHD      0.212600f
#define g_kfGVideoYHD      0.715200f
#define g_kfBVideoYHD      0.072200f

#define g_kfRVideoCbHD     0.117188f
#define g_kfGVideoCbHD     0.394228f
#define g_kfBVideoCbHD     0.511416f

#define g_kfRVideoCrHD     0.511416f
#define g_kfGVideoCrHD     0.464522f
#define g_kfBVideoCrHD     0.046894f

#define g_kfYVideoHD       1.000000f
#define g_kfCrRVideoHD     1.539648f
#define g_kfCrGVideoHD     0.457675f
#define g_kfCbBVideoHD     1.814180f
#define g_kfCbGVideoHD     0.183143f

// RGB-YCBCR HD Graphic
#define g_kfRGraphicYHD    0.182586f
#define g_kfGGraphicYHD    0.614231f
#define g_kfBGraphicYHD    0.062007f

#define g_kfRGraphicCbHD   0.100644f
#define g_kfGGraphicCbHD   0.338572f
#define g_kfBGraphicCbHD   0.439216f

#define g_kfRGraphicCrHD   0.439216f
#define g_kfGGraphicCrHD   0.398942f
#define g_kfBGraphicCrHD   0.040274f

#define g_kfYGraphicHD     1.164384f
#define g_kfCrRGraphicHD   1.792741f
#define g_kfCrGGraphicHD   0.532909f
#define g_kfCbBGraphicHD   2.112402f
#define g_kfCbGGraphicHD   0.213249f

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This helper class allows to add conversion functionalities over the 
//    SMvColor used to represent color.
//
//////////////////////////////////////////////////////////////////////////
class CMvColor : public SMvColor
{
public:
   // Summary:
   //    Creates a default CMvColor object initialized with an RGBA transparent black color.
   CMvColor()
		: SMvColor()
	{
	}

   // Summary:
   //    Creates a CMvColor object initialized with the given color.
   CMvColor (
				 unsigned long in_ulColor   // Specifies the color in the format 0xAARRGGBB or 0xAACrYYCb.
            )
		: SMvColor(in_ulColor)
	{
	}

   // Summary:
   //    Creates a CMvColor object initialized with the given enumerated color into an internal ARGB representation.
   CMvColor (
				 EMvColor in_eColor         // Specifies the RGBA color through the EMvColor enumerator.
            )
		: SMvColor(in_eColor)
	{
	}

   // Summary:
   //    Creates a CMvColor object initialized with the given ARGB values.
   CMvColor (
				 unsigned char in_uchAlpha, // Specifies the alpha value.
				 unsigned char in_uchRed,   // Specifies the Red value.
				 unsigned char in_uchGreen, // Specifies the Green value.
				 unsigned char in_uchBlue   // Specifies the Blue value.
            )
		: SMvColor(in_uchAlpha, in_uchRed, in_uchGreen, in_uchBlue)
	{
	}

   // Summary:
   //    Creates a CMvColor object initialized with the given RGB values.  The alpha component is opaque.
   CMvColor (
				 unsigned char in_uchRed,   // Specifies the Red value.
				 unsigned char in_uchGreen, // Specifies the Green value.
				 unsigned char in_uchBlue   // Specifies the Blue value.
            )
		: SMvColor(in_uchRed, in_uchGreen, in_uchBlue)
	{
	}


   // Summary:
   //    Creates a CMvColor object initialized with the given RGB values.  RGB values are assumed to be in the 
   //    0 to 1 range, and are converted to the 16-235 range.  The alpha value is also assumed to be in the 0-1 
   //    range and is mapped to 0-255 internal values.
   CMvColor (
				 float in_fAlpha,  // Specifies the Alpha value.
				 float in_fRed,    // Specifies the Red value.
				 float in_fGreen,  // Specifies the Green value.
				 float in_fBlue    // Specifies the Blue value.
            )
		: SMvColor(in_fAlpha, in_fRed, in_fGreen, in_fBlue)
	{
	}

   // Summary:
   //    Creates a CMvColor object initialized with the given RGB values.  RGB values are assumed to be in the 
   //    0 to 1 range and are converted to the 16-235 range.  The alpha component is opaque.
   CMvColor (
				 float in_fRed,   // Specifies the Red value.
				 float in_fGreen, // Specifies the Green value.
				 float in_fBlue   // Specifies the Blue value.
            )
		: SMvColor(in_fRed, in_fGreen, in_fBlue)
	{
	}

   // Summary:
   //    Destroys the CMvColor helper object.
   virtual ~CMvColor()
	{
	}

   //
   // Public member functions
   //

   // Summary:
   //    Converts ARGB internal format into ACrYCb internal format, specifying whether the RGB components form an RGB-Video or RGB-Graphic, 
   //    and specifying the colorimetry of the ACrYCb.
   void ConvertARGBToACrYCb (
									  EMvColorRange in_eColorRange,   // Color range of the RGB (Graphic or Video).
									  EMvColorimetry in_eColorimetry  // Colorimetry to use for the conversion.
                            )
	{
		float fTmpY  = 0;
		float fTmpCb = 0;
		float fTmpCr = 0;

		// Luma and Chroma
		switch(in_eColorimetry) {
		case keMvColorimetryITUR_BT_601:
			{
				switch(in_eColorRange) {
				case keMvColorRangeRgbGraphic:
					// Y
					fTmpY = g_kfRGraphicYSD * static_cast<float>(uMvColor.sMvARGB.uchRed);
					fTmpY = fTmpY + (g_kfGGraphicYSD * static_cast<float>(uMvColor.sMvARGB.uchGreen));
					fTmpY = fTmpY + (g_kfBGraphicYSD * static_cast<float>(uMvColor.sMvARGB.uchBlue)) + 16;            
					// Cb
					fTmpCb = (-1) * g_kfRGraphicCbSD * static_cast<float>(uMvColor.sMvARGB.uchRed);
					fTmpCb = fTmpCb + ((-1) * g_kfGGraphicCbSD * static_cast<float>(uMvColor.sMvARGB.uchGreen));
					fTmpCb = fTmpCb + (g_kfBGraphicCbSD * static_cast<float>(uMvColor.sMvARGB.uchBlue)) + 128;
					// Cr
					fTmpCr = g_kfRGraphicCrSD * static_cast<float>(uMvColor.sMvARGB.uchRed);
					fTmpCr = fTmpCr + ((-1) * g_kfGGraphicCrSD * static_cast<float>(uMvColor.sMvARGB.uchGreen));
					fTmpCr = fTmpCr + ((-1) * g_kfBGraphicCrSD * static_cast<float>(uMvColor.sMvARGB.uchBlue)) + 128;
					break;
				case keMvColorRangeRgbVideo:
					// Y
					fTmpY = static_cast<float>(g_kfRVideoYSD * uMvColor.sMvARGB.uchRed);
					fTmpY = fTmpY + (g_kfGVideoYSD * static_cast<float>(uMvColor.sMvARGB.uchGreen));
					fTmpY = fTmpY + (g_kfBVideoYSD * static_cast<float>(uMvColor.sMvARGB.uchBlue));
					// Cb
					fTmpCb = ((-1) * g_kfRVideoCbSD * static_cast<float>(uMvColor.sMvARGB.uchRed));
					fTmpCb = fTmpCb + ((-1) * g_kfGVideoCbSD * static_cast<float>(uMvColor.sMvARGB.uchGreen));
					fTmpCb = fTmpCb + (g_kfBVideoCbSD * static_cast<float>(uMvColor.sMvARGB.uchBlue)) + 128;
					// Cr
					fTmpCr = g_kfRVideoCrSD * static_cast<float>(uMvColor.sMvARGB.uchRed);
					fTmpCr = fTmpCr + ((-1) * g_kfGVideoCrSD * static_cast<float>(uMvColor.sMvARGB.uchGreen));
					fTmpCr = fTmpCr + ((-1) * g_kfBVideoCrSD * static_cast<float>(uMvColor.sMvARGB.uchBlue)) + 128;
					break;
				default:
					break;
				}
			}
			break;
		case keMvColorimetryITUR_BT_709:
			{
				switch(in_eColorRange) {
				case keMvColorRangeRgbGraphic:
					// Y
					fTmpY = g_kfRGraphicYHD * static_cast<float>(uMvColor.sMvARGB.uchRed);
					fTmpY = fTmpY + (g_kfGGraphicYHD * static_cast<float>(uMvColor.sMvARGB.uchGreen));
					fTmpY = fTmpY + (g_kfBGraphicYHD * static_cast<float>(uMvColor.sMvARGB.uchBlue)) + 16;            
					// Cb
					fTmpCb = (-1) * g_kfRGraphicCbHD * static_cast<float>(uMvColor.sMvARGB.uchRed);
					fTmpCb = fTmpCb + ((-1) * g_kfGGraphicCbHD * static_cast<float>(uMvColor.sMvARGB.uchGreen));
					fTmpCb = fTmpCb + (g_kfBGraphicCbHD * static_cast<float>(uMvColor.sMvARGB.uchBlue)) + 128;
					// Cr
					fTmpCr = g_kfRGraphicCrHD * static_cast<float>(uMvColor.sMvARGB.uchRed);
					fTmpCr = fTmpCr + ((-1) * g_kfGGraphicCrHD * static_cast<float>(uMvColor.sMvARGB.uchGreen));
					fTmpCr = fTmpCr + ((-1) * g_kfBGraphicCrHD * static_cast<float>(uMvColor.sMvARGB.uchBlue)) + 128;
					break;
				case keMvColorRangeRgbVideo:
					// Y
					fTmpY = static_cast<float>(g_kfRVideoYHD * uMvColor.sMvARGB.uchRed);
					fTmpY = fTmpY + (g_kfGVideoYHD * static_cast<float>(uMvColor.sMvARGB.uchGreen));
					fTmpY = fTmpY + (g_kfBVideoYHD * static_cast<float>(uMvColor.sMvARGB.uchBlue));
					// Cb
					fTmpCb = ((-1) * g_kfRVideoCbHD * static_cast<float>(uMvColor.sMvARGB.uchRed));
					fTmpCb = fTmpCb + ((-1) * g_kfGVideoCbHD * static_cast<float>(uMvColor.sMvARGB.uchGreen));
					fTmpCb = fTmpCb + (g_kfBVideoCbHD * static_cast<float>(uMvColor.sMvARGB.uchBlue)) + 128;
					// Cr
					fTmpCr = g_kfRVideoCrHD * static_cast<float>(uMvColor.sMvARGB.uchRed);
					fTmpCr = fTmpCr + ((-1) * g_kfGVideoCrHD * static_cast<float>(uMvColor.sMvARGB.uchGreen));
					fTmpCr = fTmpCr + ((-1) * g_kfBVideoCrHD * static_cast<float>(uMvColor.sMvARGB.uchBlue)) + 128;
					break;
				default:
					break;
				}
			}
			break;
		default:
			break;
		}

		// Cr/Y/Cb values
		uMvColor.sMvACrYCb.uchCr = static_cast<unsigned char>(fTmpCr);
		uMvColor.sMvACrYCb.uchY  = static_cast<unsigned char>(fTmpY);
		uMvColor.sMvACrYCb.uchCb = static_cast<unsigned char>(fTmpCb);
	}

   // Summary:
   //    Converts ACrYCb internal format into ARGB internal format specifying if the RGB components are an RGB-Video or RGB-Graphic, 
   //    and specifying the colorimetry of the ACrYCb.
   void ConvertACrYCbToARGB (
									  EMvColorRange in_eColorRange,   // Color range of the RGB (Graphic or Video).
									  EMvColorimetry in_eColorimetry  // Colorimetry to use for the conversion.
                            )
	{
		float fTmpRed   = 0;
		float fTmpGreen = 0;
		float fTmpBlue  = 0;

		// Red, Green and Blue
		switch(in_eColorimetry) {
		case keMvColorimetryITUR_BT_601:
			{
				switch(in_eColorRange) {
				case keMvColorRangeRgbGraphic:
					// Red
					fTmpRed = g_kfYGraphicSD * static_cast<float>(uMvColor.sMvACrYCb.uchY - 16);
					fTmpRed = fTmpRed + g_kfCrRGraphicSD * static_cast<float>(uMvColor.sMvACrYCb.uchCr - 128);
					// Green
					fTmpGreen = g_kfYGraphicSD * static_cast<float>(uMvColor.sMvACrYCb.uchY - 16);
					fTmpGreen = fTmpGreen + ((-1) * g_kfCrGGraphicSD * static_cast<float>(uMvColor.sMvACrYCb.uchCr - 128));
					fTmpGreen = fTmpGreen + ((-1) * g_kfCbGGraphicSD * static_cast<float>(uMvColor.sMvACrYCb.uchCb - 128));
					// Blue
					fTmpBlue = g_kfYGraphicSD * static_cast<float>(uMvColor.sMvACrYCb.uchY - 16);
					fTmpBlue = fTmpBlue + (g_kfCbBGraphicSD * static_cast<float>(uMvColor.sMvACrYCb.uchCb - 128));
					break;
				case keMvColorRangeRgbVideo:
					// Red
					fTmpRed = g_kfYVideoSD * static_cast<float>(uMvColor.sMvACrYCb.uchY);
					fTmpRed = uMvColor.sMvARGB.uchRed + (g_kfCrRVideoSD * static_cast<float>(uMvColor.sMvACrYCb.uchCr - 128));
					// Green
					fTmpGreen = g_kfYVideoSD * static_cast<float>(uMvColor.sMvACrYCb.uchY);
					fTmpGreen = fTmpGreen + ((-1) * g_kfCrGVideoSD * static_cast<float>(uMvColor.sMvACrYCb.uchCr - 128));
					fTmpGreen = fTmpGreen + ((-1) * g_kfCbGVideoSD * static_cast<float>(uMvColor.sMvACrYCb.uchCb - 128));
					// Blue
					fTmpBlue = g_kfYVideoSD * static_cast<float>(uMvColor.sMvACrYCb.uchY);
					fTmpBlue = fTmpBlue + (g_kfCbBVideoSD * static_cast<float>(uMvColor.sMvACrYCb.uchCb - 128));
					break;
				default:
					break;
				}
			}
			break;
		case keMvColorimetryITUR_BT_709:
			{
				switch(in_eColorRange) {
				case keMvColorRangeRgbGraphic:
					// Red
					fTmpRed = g_kfYGraphicHD * static_cast<float>(uMvColor.sMvACrYCb.uchY - 16);
					fTmpRed = fTmpRed + g_kfCrRGraphicHD * static_cast<float>(uMvColor.sMvACrYCb.uchCr - 128);
					// Green
					fTmpGreen = g_kfYGraphicHD * static_cast<float>(uMvColor.sMvACrYCb.uchY - 16);
					fTmpGreen = fTmpGreen + ((-1) * g_kfCrGGraphicHD * static_cast<float>(uMvColor.sMvACrYCb.uchCr - 128));
					fTmpGreen = fTmpGreen + ((-1) * g_kfCbGGraphicHD * static_cast<float>(uMvColor.sMvACrYCb.uchCb - 128));
					// Blue
					fTmpBlue = g_kfYGraphicHD * static_cast<float>(uMvColor.sMvACrYCb.uchY - 16);
					fTmpBlue = fTmpBlue + (g_kfCbBGraphicHD * static_cast<float>(uMvColor.sMvACrYCb.uchCb - 128));
					break;
				case keMvColorRangeRgbVideo:
					// Red
					fTmpRed = g_kfYVideoHD * static_cast<float>(uMvColor.sMvACrYCb.uchY);
					fTmpRed = uMvColor.sMvARGB.uchRed + (g_kfCrRVideoHD * static_cast<float>(uMvColor.sMvACrYCb.uchCr - 128));
					// Green
					fTmpGreen = g_kfYVideoHD * static_cast<float>(uMvColor.sMvACrYCb.uchY);
					fTmpGreen = fTmpGreen + ((-1) * g_kfCrGVideoHD * static_cast<float>(uMvColor.sMvACrYCb.uchCr - 128));
					fTmpGreen = fTmpGreen + ((-1) * g_kfCbGVideoHD * static_cast<float>(uMvColor.sMvACrYCb.uchCb - 128));
					// Blue
					fTmpBlue = g_kfYVideoHD * static_cast<float>(uMvColor.sMvACrYCb.uchY);
					fTmpBlue = fTmpBlue + (g_kfCbBVideoHD * static_cast<float>(uMvColor.sMvACrYCb.uchCb - 128));
					break;
				default:
					break;
				}
			}
			break;
		default:
			break;
		}
	}

   //
   // Operators
   //

   // Summary:
   //    Operator equal to allow assigning the SMvColor structure to a CMvColor helper object.
   CMvColor operator= (
							  const SMvColor &in_rkoColor  // SMvColor structure that will be used to reinitalize the CMvColor object.
                      )
	{
		uMvColor = in_rkoColor.uMvColor;

		return (*this);
	}

   //
   // Get and Set Methods.
   //

   // Summary:
   //    Returns the SMvColor internal structure.
   SMvColor GetColor()
	{
		return *(dynamic_cast<SMvColor*> (this));
	}

   // Summary:
   //    Change the internal color using a given SMvColor structure.
   void     SetColor (
							 SMvColor *in_psColor // SMvColor structure that will be used to reinitalize the CMvColor object.
                     )
	{
		*(dynamic_cast<SMvColor*> (this)) = *in_psColor;
	}

};