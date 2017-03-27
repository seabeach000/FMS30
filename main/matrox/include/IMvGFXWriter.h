//==========================================================================;
//
// (c) Copyright Matrox Electronic Systems Ltd., 2002. All rights reserved.
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
//                    IMVGFXWRITER.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             Today
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;



#ifndef IMVGFXWRITER_H
#define IMVGFXWRITER_H


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Controls the Flex GFX File Writer module
// Remarks:
//    PICON must be added AFTER all the elements have been added. 
//
//////////////////////////////////////////////////////////////////////////
interface IMvGFXWriter : public IUnknown 
{
public:

   //
   // Summary:
   //    Creates and opens a GFX file.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if any of the pointer parameters is NULL. 
   //    - MV_E_INVALID_PARAMETER, if the in_ulVersion parameter is set to 0. 
   //    - MV_E_INVALID_STRUCTURE_SIZE, if the Size field of the in_psGFXResolutionInfo parameter 
   //      does not have the right value. 
   //    - Microsoft file access errors. 
   virtual HRESULT __stdcall CreateGFX
      (
      wchar_t              * in_pwszFileName,         // Pointer to a zero terminated wchar_t string
                                                         // containing the full filename and path of 
                                                         // the file to create.
      const GUID           * in_pksGFXTypeGuid,       // Pointer to a GUID describing the type of 
                                                         // GFX to create. The value can be any of
                                                         // the CLSID_GFXType(typename) GUIDs 
                                                         // defined the in mvFlexGuidsPublicSDK.h header
                                                         // file.
      unsigned long          in_ulVersion,            // Specifies the version of the GFX which is determined
                                                         // by the effect creator.
      SMvGFXResolutionInfo * in_psGFXResolutionInfo   // Pointer to a variable of type 
                                                         // SMvGFXResolutionInfo which describes 
                                                         // the intended editing resolution
                                                         // of the GFX file.
      ) = 0;

   //
   // Summary:
   //    Closes the GFX file.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   virtual HRESULT __stdcall CloseGFX() = 0;

   //
   // Summary:
   //    Writes the data from the specified GFX element to the file.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the in _pISurface pointer is NULL. 
   //    - MV_E_OUT_OF_RANGE, if there already is at least one PICON added in the file. 
   //    - MV_E_OUT_OF_MEMORY, if the maximum number of element is reached. 
   //    - Microsoft file access errors. 
   // Remarks:
   //    - Elements must be added before any PICONs are added.
   virtual HRESULT __stdcall AddElement
      (
      IMvSurface      * in_pISurface,              // Pointer to the surface that will be filled 
                                                      // with the element data.
      EMvMemoryLocation in_eDestinationLocation,   // Indicates the memory location of the target element.
      EMvGFXElementType in_eType                   // Element type.
      ) = 0;

   //
   // Summary:
   //    Reads the data from the specified GFX PICON to a bitmap.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the in _pvMemory pointer is NULL. 
   //    - MV_E_INVALID_PARAMETER, if the in_ulPiconID is 0. 
   //    - Microsoft file access errors. 
   // Remarks:
   //    - Elements must be added before any PICONs.
   virtual HRESULT __stdcall AddPicon
      (
      unsigned long      in_ulPiconID,          // Specifies the ID associated with the PICON.
      BITMAPINFOHEADER * in_psBitmapInfoHeader, // Pointer to a variable of type BITMAPINFOHEADER 
                                                   // that contains the PICON description.
      void             * in_pvMemory            // Memory pointer that contains the PICON image.
      ) = 0;

   //
   // Summary:
   //    Adds a link to another GFX.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if any of the pointer parameters are set to NULL.
   //    - MV_E_INVALID_PARAMETER, if a pointer is invalid.
   //    - Microsoft file access errors. 
   virtual HRESULT __stdcall AddLinkedGFX
      (
      wchar_t     * in_pwszGFXFilename,   // Filename of the linked GFX.
      const CLSID * in_pksGFXType         // Specifies the GFX type.
      ) = 0;
};

#endif //IMVGFXWRITER_H




