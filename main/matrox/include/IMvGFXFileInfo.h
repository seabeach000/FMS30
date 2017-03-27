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
//                    IMVGFXFILEINFO.H
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

#pragma once

//
// Summary:
//    Retrieves GFX file information.
//
interface IMvGFXFileInfo : public IUnknown
{
public:

   //
   // Summary:
   //    Opens a GFX file.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_FILE_FORMAT, if the file has an invalid format.
   //    - HRESULT error code, if the operation fails.
   //
   virtual HRESULT __stdcall OpenGFX
      (
      const wchar_t * in_pwszFileName  // Pointer to the path and file name of the GFX file to open.
      ) = 0;

   //
   // Summary:
   //    Retrieves GFX file information.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the SMvGFXFileInfo pointer is NULL or invalid.
   //    - MV_E_INVALID_HANDLE, if no GFX file is successfully opened.
   //    - HRESULT error code, if the operation fails.
   //
   virtual HRESULT __stdcall GetGFXFileInfo
      (
      SMvGFXFileInfo * io_psmvGFXFileInfo    // Pointer to the SMvGFXFileInfo file info structure. 
      ) = 0;


   //
   // Summary:
   //    Retrieves a GFX element description.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the SMvGFXElementDescription pointer is NULL or invalid.
   //    - MV_E_INVALID_HANDLE, if no GFX file is successfully opened.
   //    - HRESULT error code, if the operation fails.
   //
   virtual HRESULT __stdcall GetElementDescription
      (
      unsigned long              in_ulIndex,                // Index of the element.
      SMvGFXElementDescription * out_psElementDescription   // Pointer to the SMvGFXElementDescription structure. 
      ) = 0;

   //
   // Summary:
   //    Closes the GFX file.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CloseGFX() = 0;

};
