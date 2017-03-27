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
//                    IMVMGFFILEINFO.H
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

#ifndef IMVMGFFILEINFO_H
#define IMVMGFFILEINFO_H

#include "mvdMGF2.h"


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Retrieves Matrox Graphics File (MGF) information.
//
//////////////////////////////////////////////////////////////////////////
interface IMvMGFFileInfo : public IUnknown
{
public:

   //
   // Summary:
   //    Opens an MGF file.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - HRESULT error code, if the file is not a valid MGF file. 
   virtual HRESULT __stdcall OpenFile
      (
      wchar_t * in_pwszFileName  // Pointer to the path and file name of the file to open.
      ) = 0;

   //
   // Summary:
   //    Retrieves the file information about an MGF file.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_FAIL, if failed. 
   virtual HRESULT __stdcall GetMGFFileInfo
      (
      SMvMGFFileInfo * out_psMGFFileInfo  // Pointer to the SMvMGFFileInfo structure containing the
                                          // file information.
      ) = 0;

   //
   // Summary:
   //    Retrieves the file information about an MGF file version 2.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_FAIL, if failed. 
   virtual HRESULT __stdcall GetMGF2FileInfo
      (
      SMvMGF2FileInfo * out_psMGFFileInfo // Pointer to the SMvMGF2FileInfo structure containing
                                          // the file information.
      ) = 0;
 
   //
   // Summary:
   //    Retrieves the MGF file version.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_FAIL, if failed. 
   virtual HRESULT __stdcall GetMGFversion
      (
      unsigned int * out_puiVersion // Pointer to the file version value.
      ) = 0;

   //
   // Summary:
   //    Closes the MGF file.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_FAIL, if failed. 
   virtual HRESULT __stdcall Close() = 0;
};



#endif //IMVMGFFILEINFO_H




