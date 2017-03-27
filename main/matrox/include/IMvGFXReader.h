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
//                    IMVGFXREADER.H
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


#ifndef IMVGFXREADER_H
#define IMVGFXREADER_H


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Controls the Flex GFX File Reader module.
//
//////////////////////////////////////////////////////////////////////////
interface IMvGFXReader : public IUnknown 
{
public:
   //
   // Summary:
   //    Closes the GFX file.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   virtual HRESULT __stdcall CloseGFX() = 0;

   //
   // Summary:
   //    Reads the data from the specified GFX element of the file to a surface.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_HANDLE, if the file is not opened properly. 
   //    - MV_E_INVALID_POINTER, if the out_pISurface pointer is NULL. 
   //    - MV_E_INVALID_PARAMETER, if the in_ulIndex is invalid. 
   //    - MV_E_INVALID_FILE_FORMAT, if the file is not of the proper GFX file format. 
   // Remarks:
   //    - The out_pISurface pointer is allocated by the application using the Flex Engine surface
   //      creation methods.  The application uses the IMvGFXReader::GetElementDescription() methods
   //      to know what the surface creation parameters are. 
   virtual HRESULT __stdcall GetElement
      (
      unsigned long in_ulIndex,  // Index of the element in the GFX file.
      IMvSurface * io_pISurface  // Pointer to the surface that will be filled with the element data.
      ) = 0;

   //
   // Summary:
   //    Retrieves the media information pertaining to a specific element in the GFX file.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_HANDLE, if the file is not opened properly. 
   //    - MV_E_INVALID_POINTER, if the out_psElementdescription pointer is NULL. 
   //    - MV_E_INVALID_STRUCTURE_SIZE, if the Size field  of the structure does not contain the 
   //      right value. 
   //    - MV_E_INVALID_PARAMETER, if the in_ulIndex is invalid. 
   virtual HRESULT __stdcall GetElementDescription
      (
      unsigned long              in_ulIndex,                // Index of the element in the GFX file.
      SMvGFXElementDescription * out_psElementDescription   // Pointer to a variable of type 
                                                               // SMvGFXElementDescription that is 
                                                               // filled by the element description 
                                                               // specified by the in_ulIndex 
                                                               // parameter.
      ) = 0;

   //
   // Summary:
   //    Gets the media file information of the GFX file.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_HANDLE, if the file is not opened properly. 
   //    - MV_E_INVALID_POINTER, if the out_psGFXFileInfo pointer is NULL. 
   //    - MV_E_INVALID_STRUCTURE_SIZE, if the Size of field the structure does not contain the
   //      right value. 
   virtual HRESULT __stdcall GetGFXFileInfo
      (
      SMvGFXFileInfo * out_psGFXFileInfo  // Pointer to a variable of type SMvGFXFileInfo that will
                                             // be filled by the media file information.
      ) = 0;

   //
   // Summary:
   //    Reads the data from a specified GFX PICON in the file to a bitmap.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_HANDLE, if the file is not opened properly. 
   //    - MV_E_INVALID_POINTER, if the out_pvMemory pointer is NULL. 
   //    - MV_E_INVALID_PARAMETER, if the in_ulPiconID is invalid. 
   //    - MV_E_INVALID_FILE_FORMAT, if the file is not of the proper GFX file format. 
   //    - MV_E_NOT_FOUND, if the in_ulPiconID parameter value indicates a PICON that does not
   //      exist in the file. 
   // Remarks:
   //    - The out_pvMemory pointer is allocated by the application using information returned by
   //      the IMvGFXReader::GetPiconDescription() method. 
   virtual HRESULT __stdcall GetPicon
      (
      unsigned long in_ulPiconID,   // Specifies the PICON image to retrieve.
      void        * out_pvMemory    // Points to the memory location that will receive the PICON image.
      ) = 0;

   //
   // Summary:
   //    Retrieves the media information pertaining to a specific PICON in the GFX file.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_HANDLE, if the file is not opened properly. 
   //    - MV_E_INVALID_POINTER, if the out_psBitmapInfoHeader pointer is NULL. 
   //    - MV_E_INVALID_STRUCTURE_SIZE, if the field Size of the structure does not contain the 
   //      right value. 
   //    - MV_E_INVALID_PARAMETER, if the in_ulPiconID is invalid. 
   //    - MV_E_INVALID_FILE_FORMAT, the file is not of the proper GFX file format. 
   //    - MV_E_NOT_FOUND, if the in_ulPiconID parameter value indicates a PICON that does not 
   //      exist in the file. 
   virtual HRESULT __stdcall GetPiconDescription
      (
      unsigned long      in_ulPiconID,          // Specify the PICON image to retrieve.
      BITMAPINFOHEADER * out_psBitmapInfoHeader // Pointer to a variable of type BITMAPINFOHEADER 
                                                   // that will be filled by the PICON description 
                                                   // specified by the in_ulPiconID parameter.
      ) = 0;

   //
   // Summary:
   //    Gets the linked GFX information in the GFX file.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_HANDLE, if the file is not opened properly.
   //    - MV_E_INVALID_POINTER, if the out_psLinkedGFXInfo pointer is NULL.
   //    - MV_E_INVALID_STRUCTURE_SIZE, if the field Size of the structure does not contain the 
   //      right value.
   //    - MV_E_INVALID_PARAMETER, if the in_ulIndex pointer is invalid. 
   //    - MV_E_INVALID_FILE_FORMAT, the file is not of the proper GFX file format. 
   //    - MV_E_NOT_FOUND, if the in_ulPiconID parameter value indicate a PICON that do not exist
   //      in the file.
   virtual HRESULT __stdcall GetLinkedGFX
      (
      unsigned long      in_ulIndex,         // Specify which linked GFX to retrieve.
      SMvLinkedGFXInfo * out_psLinkedGFXInfo // Pointer to a variable of type SMvLinkedGFXInfo that
                                                // is filled by the linked GFX description.
      ) = 0;

   //
   // Summary:
   //    Opens a GFX file.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_FILE_NOT_FOUND, if the file name is not found at the specified location. 
   //    - MV_E_INVALID_FILE_FORMAT, if the file is not in the proper GFX file format. 
   virtual HRESULT __stdcall OpenGFX
      (
      const wchar_t * in_pwszFileName  // Pointer to a zero-terminated wchar_t string containing 
                                          // the full filename and path of the GFX file to open.
      ) = 0;
};

#endif //IMVGFXREADER_H




