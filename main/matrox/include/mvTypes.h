//////////////////////////////////////////////////////////////////////////////////
//
//  (c) Copyright Matrox Electronic Systems Ltd., 2003-2015. All rights reserved. 
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

//////////////////////////////////////////////////////////////////////////////////
// Defines ANSI C/C++ missing types for Mac and PC for ring0 and ring3 layers
//////////////////////////////////////////////////////////////////////////////////

#if defined(__APPLE_CC__)
   #define MAC_PLATFORM
#endif

#if defined(MAC_PLATFORM)

//typedef unsigned long ULONG;

// ANSI exact-width integer types are in stdint.h
#include <stdint.h>
#include <IOKit/IOReturn.h>

#define MAKE_MVHRESULTERROR(code) iokit_vendor_specific_err(((code) & 0x3FFF) | 0x3000)   // Only 14 bits available for the error code, so error codes 0x8000 to 0x8FFF are mapped to 0x3000 to 0x3FFF
#define MAKE_MVHRESULTWARNING(code) iokit_vendor_specific_err((code))                     // All warnings are in the range 0x0000 to 0x2100

namespace com_matrox_vpg_SDK
{
   typedef IOReturn HRESULT;
} // namespace com_matrox_vpg_SDK

#elif defined(LINUX_PLATFORM)

// ANSI C/C++ defines are into types.h
#ifdef __cplusplus
extern "C" {
#endif

//
// These include files are the same as the ones found
// in the kernel, i.e. <linux/stddef.h> and <linux/types.h>,
// but they were patched (in the mvkUtilityLinux lib) in 
// order to compile in C++.
//
// This modification patches compilation problems with the Linux
// Kernel version starting at 2.6.20 with g++.  Not needed for
// user level.
//
#ifdef __KERNEL__
   #include "mvkLinuxKernelstddef.h"
   #include "mvkLinuxKerneltypes.h"
#else
   #include <stdint.h>
   #define __STDC_FORMAT_MACROS // Required for PRIx64 macros...
   #include <inttypes.h>        // Required for PRIx64 macros...
#endif

#ifdef __cplusplus
}
#endif

#define __ptr64
#define FAR

//
// Define the Macro which will create the HRESULT
//
#define _FACMVPG   0x999

#define MAKE_MVHRESULTERROR(code) MAKE_HRESULT( 1, _FACMVPG, code )
#define MAKE_MVHRESULTWARNING(code) MAKE_HRESULT( 0, _FACMVPG, code )

#elif defined(UB_PLATFORM)
   #include "_mvmTypes.h" 

#else  // defined(LINUX_PLATFORM)

//
// Define the Macro which will create the HRESULT
//
#define _FACMVPG   0x999

#define MAKE_MVHRESULTERROR(code) MAKE_HRESULT( 1, _FACMVPG, code )
#define MAKE_MVHRESULTWARNING(code) MAKE_HRESULT( 0, _FACMVPG, code )

// 64-bit format specifier (C99 standard, but not defined by VC++).
#if !defined(PRIu64)
#define PRIu64       "I64u"
#endif
#if !defined(PRIx64)
#define PRIx64       "I64x"
#endif
#if !defined(PRIX64)
#define PRIX64       "I64X"
#endif
#if !defined(PRId64)
#define PRId64       "I64d"
#endif
#if !defined(PRIi64)
#define PRIi64       "I64i"
#endif

#ifndef MV_ANSI_TYPES
#define MV_ANSI_TYPES

// ANSI C/C++ not defined into VC++
#if defined(_MSC_VER) && (_MSC_VER >= 1600) //only on VS2010 and up

// This get rid of all the warning macro redefinition INT8_MIN, INT16_MIN, ... 
// Microsoft say it should be ficed in the next major revision of VS.
// This is the recommended work around from Microsoft.
// http://connect.microsoft.com/VisualStudio/feedback/details/621653/including-stdint-after-intsafe-generates-warnings
#pragma warning (push)
#pragma warning (disable : 4005) 

#include <stdint.h>

#pragma warning (push)
#pragma warning (default : 4005)

#else


typedef __int8 int8_t;              // Signed 8-bit integer value.
typedef __int16 int16_t;            // Signed 16-bit integer value.
typedef __int32 int32_t;            // Signed 32-bit integer value.
typedef __int64 int64_t;            // Signed 64-bit integer value.

typedef unsigned __int8 uint8_t;    // Unsigned 8-bit integer value.
typedef unsigned __int16 uint16_t;  // Unsigned 16-bit integer value.
typedef unsigned __int32 uint32_t;  // Unsigned 32-bit integer value.
typedef unsigned __int64 uint64_t;  // Unsigned 64-bit integer value.

#endif // _MSC_VER

#ifndef _WCHAR_T_DEFINED
typedef uint16_t wchar_t;           // Unicode character.  Unsigned 16-bit value.
#define _WCHAR_T_DEFINED
#endif // _WCHAR_T_DEFINED

#endif // MV_ANSI_TYPES
#endif // defined(MAC_PLATFORM)
