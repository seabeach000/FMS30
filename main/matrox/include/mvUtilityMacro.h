// $Archive: /VP/FLEXVIDEO/LIBS/MVFUTILITY/inc/mvUtilityMacro.h $

//==============================================================================
//
// (c) Copyright Matrox Electronic Systems Ltd., 2003. All rights reserved. 
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
//-------------------------------------------------------------------------------
//	created:	   2003/3/14    10:08
//	filename: 	g:\vssx\vp\flexvideo\libs\mvutility\inc\mvutilitymacro.h
//	author:		Luc Poirier
//===============================================================================
//
// This file contains macros and inline function that can be used
// to replace repetitive code.
//
//==============================================================================


#pragma once

#ifndef _MVUTILITYMACRO_H_F50A1DD5_EF57_4bce_ADB1_D50DD7A35B3D_H31D1_
#define _MVUTILITYMACRO_H_F50A1DD5_EF57_4bce_ADB1_D50DD7A35B3D_H31D1_

#include <stdio.h>

#define MvSafeRelease(OBJ_) \
   { if(OBJ_) {(OBJ_)->Release(); (OBJ_) = NULL; } }

#define MvSafeDelete(OBJ_) \
   { if(OBJ_) {delete (OBJ_); (OBJ_) = NULL; } }

#define MvSafeCloseHandle(OBJ_) \
   { if(OBJ_) {CloseHandle (OBJ_); (OBJ_) = NULL; } }

#define MvSafeDeleteArray(OBJ_) \
   { if(OBJ_) {delete[] (OBJ_); (OBJ_) = NULL; } }

#define MvSafeInit(_x_)        (_x_) = NULL


#if _MSC_VER < 1400 && !defined(sprintf_s)
#define sprintf_s(_STR_, _SIZE_, _FORMAT_, _PARAM1_, _PARAM2_, _PARAM3_) sprintf(_STR_, _FORMAT_, _PARAM1_, _PARAM2_, _PARAM3_);
#endif

//////////////////////////////////////////////////////////////////////////
// DEBUG MACROS
//////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
   #ifndef LINUX_PLATFORM
      #define MvAssert(_x_)                                                  \
      if(!(_x_))                                                             \
      {                                                                      \
         char sz_msgASSERT[256];                                                       \
         sprintf_s(sz_msgASSERT, 256, "%s\n%s (%d)", TEXT(#_x_), TEXT(__FILE__), __LINE__);   \
         MessageBox(NULL, sz_msgASSERT, "ASSERT", MB_ICONERROR);                       \
         __debugbreak(); \
      }
   #else
      #define MvAssert(_x_) \
      if(!(_x_)) \
      {                                                                      \
         char sz_msgASSERT[256];                                                       \
         printf(sz_msgASSERT, 256, "%s\n%s (%d)", TEXT(#_x_), TEXT(__FILE__), __LINE__);    \
      }
   #endif
#else
#define MvAssert(_x_)  ((void)0)
#endif

namespace MvUtilityMacro
{
	// MvLog
}

#endif
