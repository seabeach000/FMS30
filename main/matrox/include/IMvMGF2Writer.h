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
//   Birth Date:             2004
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;
//
//Mario Rousseau
//May 31 2004


#ifndef IMVMGF2WRITER_H
#define IMVMGF2WRITER_H

#include "mvdMGF2.h"
#include "MvFlexAPI.h"
//
// Summary:
//    Used to create MGF version 2 files.
//
interface IMvMGF2Writer : public IUnknown
{
public:
   //
   // Summary:
   //    Opens an MGF version 2 file.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - HRESULT error code, if the operation failed to create a file.
   // Remarks:
   //    A new MGF file is always created. Append is not supported.
   //
   virtual HRESULT __stdcall OpenFile
      (
      const wchar_t * in_pwszFileName,    // Pointer to the MGF file name. Its extension must be .MGF.
      const SMvMGF2ImageInfo & in_rksInfo // The reference to the information structure.
      ) = 0;

   //
   // Summary:
   //    Closes an MGF version 2 file.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - HRESULT error code, if the operation failed to close the file.
   virtual HRESULT __stdcall Close() = 0;

   //
   // Summary:
   //    Adds a buffer to the MGF file version 2. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - HRESULT error code, if the operation failed to add the buffer.
   // Remarks:
   //    - The buffer represents a Flex surface. The MGF file gets the data from the buffer. 
   //    - Only one buffer of YUVA or YUV data is supported.
   //    - The memory allocated for each line of graphics must be enough to accommodate a 
   //      line width that is a multiple of 16 pixels. For example, if the width of an MGF file is 10 
   //      pixels, the memory must still be enough for 16 pixels.
   //    - Memory allocated for a line should be multiple of 128 bytes.
   virtual HRESULT __stdcall AddBuffer
      (
      IMvSurface * in_pIMvSurface   // Input surface to write to the file.
      ) = 0;

   virtual HRESULT __stdcall SetFileObserver(IMvFlexFileHandleObserver *in_pIFileObserver) = 0;
};

#endif //IMVMGF2WRITER_H




