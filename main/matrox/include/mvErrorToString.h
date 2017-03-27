//////////////////////////////////////////////////////////////////////////////////
//
//  (c) Copyright Matrox Electronic Systems Ltd., 2007. All rights reserved.
//
//  This software code is subject to the terms and conditions outlined
//  in the non-disclosure agreement between Matrox and your company.
//  By accessing this code or using it in any way, you indicate your
//  acceptance of such terms and conditions.
//
//  All code and information is provided "as is" without warranty of any kind,
//  either expressed or implied, including but not limited to the implied
//  warranties of merchantability and/or fitness for a particular purpose.
//
//  Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make
//  changes in specifications and code at any time and without notice.
//  No responsibility is assumed by Matrox Electronic Systems Ltd. for
//  its use; nor for any infringements of patents or other rights of
//  third parties resulting from its use. No license is granted under
//  any patents or patent rights of Matrox Electronic Systems Ltd.
//
//////////////////////////////////////////////////////////////////////////////////

#pragma once
extern "C"
{

   //////////////////////////////////////////////////////////////////////////
   //
   // Summary:
   //    Convert an error code to a string
   // Description:
   //    When an error occurs, it is possible to past the error code to this function and the
   //    function returns a string which describes the error.
   //
   //////////////////////////////////////////////////////////////////////////

   const wchar_t * mvErrorToString(int in_iError);
}
