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
//                    IMVMGFREADER.H
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

#ifndef IMVMGFREADER_H
#define IMVMGFREADER_H


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Used to read MGF file data.
// Description:
//    To get data from an MGF file, do the following:
//    - Open the file.
//    - Call GetMGFMFileInfo() to get the file's information, such as its dimension, surface format,
//      and pitch.
//    - Create a IMvSurface based on the information,
//    - Call the ReadBuffer() function with the surface.
//    - Close the file.
//
//////////////////////////////////////////////////////////////////////////
interface IMvMGFReader : public IUnknown
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
   //    Gets the media file information of the MGF file.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_FAIL, if failed. 
   virtual HRESULT __stdcall GetMGFFileInfo
      (
      SMvMGFFileInfo * out_psMGFFileInfo  // Pointer to the SMvMGFFileInfo structure containing
                                          // file information.
      ) = 0;

   //
   // Summary:
   //    Reads the data from the MGF file to a surface.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - HRESULT error code, if the function reported an error. 
   // Remarks:
   //    - The surface must be properly allocated based on the file's information. 
   virtual HRESULT __stdcall ReadBuffer
      (
      IMvSurface * io_pIMvSurface   // Pointer to the output data surface.
      ) = 0;

   //
   // Summary:
   //    Closes the MGF file.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_FAIL, if failed. 
   virtual HRESULT __stdcall Close() = 0;

};

#endif //IMVMGFREADER_H