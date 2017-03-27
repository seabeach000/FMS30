//////////////////////////////////////////////////////////////////////////////////
//
//  (c) Copyright Matrox Electronic Systems Ltd., 2013-2015. All rights reserved. 
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
//
//  File Name     : mvLinuxTypes.h
//  Description   : Windows type used under Linux
//
//  Author        : Matrox Video Products Group
//  Creation Date : January, 2007
//
//////////////////////////////////////////////////////////////////////////////////

#ifndef MVLINUXTYPES_H
#define MVLINUXTYPES_H

//-------------------------------------------------------------------
// Define used for the Interrupt Request Level (IRQL)
//-------------------------------------------------------------------
#define PASSIVE_LEVEL      0
#define DISPATCH_LEVEL     2
#define DEVICE_LEVEL       (DISPATCH_LEVEL + 1)

//-------------------------------------------------------------------
// Windows NT definitions used in Linux
//-------------------------------------------------------------------
#ifndef	FALSE
	#define FALSE              0
#endif
#ifndef	TRUE	
	#define TRUE               1
#endif	

//-------------------------------------------------------------------
// Windows NT types used in Linux
//-------------------------------------------------------------------
typedef void *             PVOID;
typedef uint8_t            UCHAR;
typedef UCHAR              KIRQL;
typedef unsigned int       uint32;

#ifndef __INTEL_COMPILER
   typedef int64_t           __int64;
#endif

//-------------------------------------------------------------------
// Windows NT functions used in Linux
//-------------------------------------------------------------------
#define _stricmp  strcasecmp
#define _snprintf snprintf

//
// ULONG_PTR is 32 bits on 32-bit platforms and 64 bits on
// 64-bit platform, which is same as 'unsigned long' in Linux
//
#ifndef ULONG_PTR
	typedef unsigned long      ULONG_PTR;
#endif
typedef ULONG_PTR          KAFFINITY;

//-------------------------------------------------------------------
// Windows NT enumarations used in Linux
//-------------------------------------------------------------------
typedef enum _MEMORY_CACHING_TYPE_ORIG {
   MmFrameBufferCached = 2
} MEMORY_CACHING_TYPE_ORIG;

typedef enum _MEMORY_CACHING_TYPE {
   MmNonCached = FALSE,
   MmCached = TRUE,
   MmWriteCombined = MmFrameBufferCached,
   MmHardwareCoherentCached,
   MmNonCachedUnordered,
   MmUSWCCached,
   MmMaximumCacheType
} MEMORY_CACHING_TYPE;

#endif
