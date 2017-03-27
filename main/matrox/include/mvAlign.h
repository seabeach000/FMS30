/*

(c) Copyright Matrox Electronic Systems Ltd., 2003. All rights reserved. 

This code and information is provided "as is" without warranty of any kind, 
either expressed or implied, including but not limited to the implied 
warranties of merchantability and/or fitness for a particular purpose.

Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make 
changes in specifications and code at any time and without notice. 
No responsibility is assumed by Matrox Electronic Systems Ltd. for 
its use; nor for any infringements of patents or other rights of 
third parties resulting from its use. No license is granted under 
any patents or patent rights of Matrox Electronic Systems Ltd.

April 2003

*/

#pragma once

#include <stddef.h> // for ptrdiff_t definition

const int kiDefaultAlignment = 16;

//
// Summary:
//    This inline function takes the given pointer and aligns it to the nearest required boundary,
//    defined by kiDefaultAlignment.
// Remarks:
//    - It's possible to override the boundary if desired.  You need to include mvAlign.h 
//      (or mvUtility.h) to use this function.
//
inline void* AlignPointer
   (
   void * in_pPointerToAlign,                // Pointer that you want to align.
   int    in_iAlignment = kiDefaultAlignment // Boundary in bytes in which you want the alignment done.
   )
{
   return reinterpret_cast<void*>((reinterpret_cast<ptrdiff_t>(in_pPointerToAlign) + in_iAlignment-1) & ~(in_iAlignment-1));
}
