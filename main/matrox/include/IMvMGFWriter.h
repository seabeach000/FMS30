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
//                    
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             2003
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;
//
//Yufei He.
//June.12 2003 .


#ifndef IMVMGFWRITER_H
#define IMVMGFWRITER_H
#include "MvFlexAPI.h"
//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Used to create MGF files. The MGF file format is the only graphics format supported by DSX.
//
//////////////////////////////////////////////////////////////////////////
interface IMvMGFWriter : public IUnknown
{
public:
   //
   // Summary:
   //    Opens an MGF file.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - HRESULT error code, if the operation failed to create a file. 
   // Remarks:
   //    - A new MGF file is always created. Append is not supported. 
   virtual HRESULT __stdcall OpenFile
      (
      const wchar_t * in_pwszFileName, // Pointer to the MGF file name. Its extension must be .mgf.
      SMvResolutionInfo in_smvRes      // The resolution of the MGF file.
      ) = 0 ;

   //
   // Summary:
   //    Closes an MGF file.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - HRESULT error code, if the operation failed to close the file. 
   virtual HRESULT __stdcall Close() = 0 ;

   //
   // Summary:
   //    Adds a buffer to the MGF file.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - HRESULT error code, if the operation failed to add the buffer. 
   // Remarks:
   //    - The MGF file gets the surface format from the Flex surface being written. 
   //    - Only YUVA and YUV data is supported. For RGBA and other graphics data, the user must
   //      convert the data to a Flex surface using the buffer engine. 
   //    - The memory allocated for each line of graphics must be enough to accommodate a line 
   //      width that is a multiple of 16 pixels. For example, if the width of an MGF file is 10
   //      pixels, the memory must still be enough for 16 pixels. 
   //    - Memory allocated for a line should be multiple of 128 bytes. 
    virtual HRESULT __stdcall AddBuffer
       (
       IMvSurface * in_pIMvSurface  // Input surface to write to the MGF file.
       ) = 0 ;

    virtual HRESULT __stdcall SetFileObserver(IMvFlexFileHandleObserver *in_pIFileObserver) = 0;
};

#endif //IMVMGFWRITER_H




