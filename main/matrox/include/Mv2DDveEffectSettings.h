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

#include "mvBaseCOM.h"


//
// Summary:
//    Sets the parameters used by the 2D DVE effect. 
//
interface IMv2DDveEffectSettings : public IUnknown
{

   //
   // Summary:
   //    Describes the types of softness that can be applied to the source clip. 
   //
   enum EMvSoftnessType
   {
      keMvSoftnessType_Linear,            // Linear softness            
      keMvSoftnessType_MatroxNonLinear1,  // Customized softness curve (non-linear) similar to the Matrox 3D DVE effect (IMvDveEffectSettings).
      keMvSoftnessType_Last               // End of list indicator.
   };

   //
   // Summary:
   //    Sets the amount of horizontal (x-axis) scaling to apply to the source clip. 
   // Description:
   //    <table>
   //    Parameter  Valid range      Granularity  Default value  Dependency 
   //    ---------  ---------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +2000.0]  Not limited  1.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fScalingFactorX is outside the specified range. 
   //
   virtual HRESULT __stdcall SetHorizontalScalingFactor
      (
      float in_fScalingFactorX   // Specifies the horizontal scaling value. 
      ) = 0;

   //
   // Summary:
   //    Sets the amount of vertical (y-axis) scaling to apply to the source clip. 
   // Description:
   //    <table>
   //    Parameter  Valid range      Granularity  Default value  Dependency 
   //    ---------  ---------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +2000.0]  Not limited  1.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fScalingFactorY is outside the specified range. 
   //
   virtual HRESULT __stdcall SetVerticalScalingFactor
      (
      float in_fScalingFactorY   // Specifies the vertical scaling value.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of horizontal (x-axis) softness to apply to the source clip.
   // Description: 
   //    Softness is applied to the scaled region of the source clip only, and is defined as the percentage of pixels to be softened from the border to the center. 
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  0.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fSoftnessAmount is outside the specified range. 
   // Remarks:
   //    - A value of 1.0 for the parameter in_fSoftnessAmount means that the pixels at the center are 100% opaque, and the pixels on the border are 0% opaque.   
   //
   virtual HRESULT __stdcall SetHorizontalSoftnessAmount
      (
      float in_fSoftnessAmount      // Specifies the horizontal softness value.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of vertical (y-axis) softness to apply to the source clip.
   // Description:
   //    Softness is applied to the scaled region of the source clip only, and is defined as the percentage of pixels to be softened from the border to the center. 
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  0.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fSoftnessAmount is outside the specified range. 
   // Remarks
   //    - A value of 1.0 for the parameter in_fSoftnessAmount means that the pixels at the center are 100% opaque, and the pixels on the border are 0% opaque.   
   //
   virtual HRESULT __stdcall SetVerticalSoftnessAmount
      (
      float in_fSoftnessAmount      // Specifies the vertical softness value.
      ) = 0;

   //
   // Summary:
   //    Sets the amount of additional sharpness to apply to the source clip.
   // Description:
   //    Sets the amount of additional sharpness to apply to the source clip. It is defined as a percentage with (0%) being the most blurry 
   //    value and 100% the sharpest value.
   //    <table>
   //    Parameter  Valid range   Granularity  Default value  Dependency 
   //    ---------  ------------  -----------  -------------  ----------
   //    %PAR0%     [+0.0, +1.0]  Not limited  0.5            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fSharpnessAmount is outside the specified range. 
   // Remarks
   //
   virtual HRESULT __stdcall SetSharpnessAmount
      (
      float in_fSharpnessAmount      // Specifies the sharpness amount.
      ) = 0;

   //
   // Summary:
   //    Sets the type of softness to apply to the source clip. 
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter in_fSoftnessAmount is outside the specified range. 
   // Remarks:
   //    - The Matrox 3D DVE effect (IMvDveEffectSettings) uses a softness curve similar to keMvSoftnessType_MatroxNonLinear1. 
   //
   virtual HRESULT __stdcall SetSoftnessType
      (
      IMv2DDveEffectSettings::EMvSoftnessType in_eSoftnessType    // Specifies the value that determines the type of softness to apply.
      ) = 0;       

   //
   // Summary:
   //    Sets the destination of the translated source clip by specifying the displacement values of the x and y coordinates. 
   // Description:
   //    <table>
   //    Parameter  Valid range                      Granularity  Default value  Dependency 
   //    ---------  -------------------------------  -----------  -------------  ----------
   //    %PAR0%     Any 16-bit floating point value  Not limited  0.0            None 
   //    %PAR1%     Any 16-bit floating point value  Not limited  0.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if one of the parameters is outside the specified range. 
   //
   virtual HRESULT __stdcall SetDestinationTranslation
      (
      float in_fXDisplacement,   // Specifies the x-coordinate displacement value in pixels.
      float in_fYDisplacement    // Specifies the y-coordinate displacement value in pixels.
      ) = 0;

   //
   // Summary:
   //    Sets the x and y coordinates of the anchor point, which defines the origin of the scaling operation.
   // Description:
   //    <table>
   //    Parameter  Valid range                      Granularity  Default value  Dependency 
   //    ---------  -------------------------------  -----------  -------------  ----------
   //    %PAR0%     Any 16-bit floating point value  Not limited  0.0            None 
   //    %PAR1%     Any 16-bit floating point value  Not limited  0.0            None 
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if a parameter is outside its specified range. 
   // Remarks:
   //    - Anchor point values can be sub-pixel precise.
   virtual HRESULT __stdcall SetAnchorPoint
      (
      float in_fAnchorX,   // Specifies the x-coordinate of the anchor point, located at the center of the video clip according to Flex behavior.
      float in_fAnchorY    // Specifies the y-coordinate of the anchor point, located at the center of the video clip according to Flex behavior.
      ) = 0;

   //
   // Summary:
   //    Sets the region of the source clip on which the 2D DVE effect will be applied.
   // Description:
   //     The region specified as the crop area is defined by the number of pixels to remove from each side of the source clip.
   //    <table>
   //    Parameter  Valid range                  Granularity  Default value       Dependency 
   //    ---------  ---------------------------  -----------  ------------------  ----------------------------
   //    %PAR0%     Left [0, SourceWidth],<p>    1            0, meaning no crop  Left+Right < SourceWidth,<p> 
   //                Right [0, SourceWidth],<p>                                    Top+Bottom < SourceHeight
   //                Top [0, SourceHeight],<p>      
   //                Bottom [0, SourceHeight]
   //    </table>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the pointer is NULL. 
   // Remarks:
   //    - Values that contain fractional parts will be truncated by the effect. 
   //
   virtual HRESULT __stdcall SetCropArea
      (
      SMvRectF * in_poSCropArea  // Pointer that specifies the region of the source clip to use.
      ) = 0;

   //
   // Summary:
   //    Updates the 2D DVE effect settings according to the parameters set by other 2D DVE methods. 
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - This method ensures the integrity of the effect settings, and must be called whenever 2D DVE effect settings are modified.
   // 
   virtual HRESULT __stdcall Update() = 0;
        
   //
   // Summary:
   //    Interface version
   //
   static const unsigned long ms_kulmvc2DDveVersion = 1;
};
