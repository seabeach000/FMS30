/* ----------------------------------------------------------------------------
 File: mctypes.h

 Desc: cross-platform standard data types

 Copyright (c) 2014 MainConcept GmbH or its affiliates.  All rights reserved.

 MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.
 This software is protected by copyright law and international treaties.  Unauthorized
 reproduction or distribution of any portion is prohibited by law.

 ----------------------------------------------------------------------------
 */


#if !defined (__MC_TYPES_INCLUDED__)
#define __MC_TYPES_INCLUDED__

#if defined(__SYMBIAN32__)
#include <e32std.h>
#endif

/* Define helpers to select endianess throughout MC Code */
 #ifndef __APPLE__
/* For now assume all non Apple platforms to be little endian, this might need changing for first non apple little endian platform */
  #define MC_LITTLEENDIAN	1
 #else
/* For Apple platforms use the proper macros of the apple compiler to do the dectection */
  #ifdef __LITTLE_ENDIAN__
   #define MC_LITTLEENDIAN 1
  #else
   #define MC_BIGENDIAN 1
  #endif
 #endif

// used when dll exports symbols to project with different function call type
#if defined(_WIN32) && !defined(__SYMBIAN32__)
#define MC_EXPORT_API	__cdecl
#else
	#if !defined(__SYMBIAN32__)
		#define MC_EXPORT_API
	#else
		#define MC_EXPORT_API	EXPORT_C
	#endif
#endif


/* check for Microsoft IA32/x64 compilers */
 #if (defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_AMD64) || defined(_ARM_))) || defined(__SYMBIAN32__) || defined(_MIPS_)



  #ifdef int8_t
   #undef int8_t
  #endif

  #ifdef int16_t
   #undef int16_t
  #endif

  #ifdef int32_t
   #undef int32_t
  #endif

  #ifdef int64_t
   #undef int64_t
  #endif

  #ifdef uint8_t
   #undef uint8_t
  #endif

  #ifdef uint16_t
   #undef uint16_t
  #endif

  #ifdef uint32_t
   #undef uint32_t
  #endif

  #ifdef uint64_t
   #undef uint64_t
  #endif

  #ifdef INT8_C
   #undef INT8_C
  #endif

  #ifdef INT8_C
   #undef INT8_C
  #endif

  #ifdef INT16_C
   #undef INT16_C
  #endif

  #ifdef INT32_C
   #undef INT32_C
  #endif

  #ifdef INT64_C
   #undef INT64_C
  #endif

  #ifdef UINT8_C
   #undef UINT8_C
  #endif

  #ifdef UINT16_C
   #undef UINT16_C
  #endif

  #ifdef UINT32_C
   #undef UINT32_C
  #endif

  #ifdef UINT64_C
   #undef UINT64_C
  #endif

#ifndef _DIVXINT_H_
#if (_MSC_VER >= 1600)
	#include <stdint.h>
#else
typedef signed char         int8_t;
   typedef signed short        int16_t;
   typedef signed int          int32_t;

   #if !defined(__SYMBIAN32__)
    typedef signed __int64      int64_t;
   #else
    typedef TInt64      		int64_t;
   #endif

   typedef unsigned char       uint8_t;
   typedef unsigned short      uint16_t;
   typedef unsigned int        uint32_t;

   #if !defined(__SYMBIAN32__)
    typedef unsigned __int64    uint64_t;
   #else
    typedef TUint64    			uint64_t;
   #endif

#endif

#endif  // End of Microsoft compiler specific section here


#if ( _MSC_VER >= 1600)

#ifndef _DIVXINT_H_
#include <stdint.h>
#else
  #define INT64_C(x)          x##I64
  #define UINT64_C(x)         x##UI64
#endif

#else
  #define INT8_C(x)           x
  #define INT16_C(x)          x##L
  #define INT32_C(x)          x##L
  #define INT64_C(x)          x##I64

  #define UINT8_C(x)          x##U
  #define UINT16_C(x)         x##U
  #define UINT32_C(x)         x##UL
  #define UINT64_C(x)         x##UI64
#endif

/* calling conventions */
  #ifndef CDECL
   #if !defined(__SYMBIAN32__)
    #define CDECL               __cdecl
   #else
    #define CDECL
   #endif
  #endif


  #ifndef FASTCALL
   #if !defined(__SYMBIAN32__)
    #define FASTCALL            __fastcall
   #else
    #define FASTCALL
   #endif
  #endif

  #ifndef STDCALL
   #if !defined(__SYMBIAN32__)
    #define STDCALL             __stdcall
   #else
    #define STDCALL
   #endif
  #endif

  #ifndef PASCAL
   #if !defined(__SYMBIAN32__)
    #define PASCAL              __stdcall
   #else
    #define PASCAL
   #endif
  #endif

 #elif defined(__GNUC__)

/* calling conventions */
#if defined(__arm__)
	   #define CDECL
	   #define FASTCALL
	   #define STDCALL
	   #define PASCAL
#else

  #ifndef CDECL
   #define CDECL               __attribute__((cdecl))
  #endif

  #if !defined(FASTCALL) && defined(__i386__)
   #define FASTCALL            __attribute__((__stdcall__)) __attribute__((__regparm__(3)))
  #else
   #define FASTCALL
  #endif


  #if !defined(STDCALL) && defined(__i386__)
   #define STDCALL             __attribute__((stdcall))
  #else
   #define STDCALL
  #endif

  #if !defined(PASCAL) && defined(__i386__)
   #define PASCAL              __attribute__((stdcall))
  #else
   #define PASCAL
  #endif

#endif

// To do: add specific GNU compiler support here
  #define __STDC_CONSTANT_MACROS
  #define __STDC_LIMIT_MACROS
  #if !defined(__vxworks)
   #include <stdint.h>
   #include <inttypes.h>
  #endif

 #else

  #error Unknown platform/compiler, please define standard types. __

 #endif

#endif // #if !defined (__MC_TYPES_INCLUDED__)
