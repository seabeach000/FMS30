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

*/

// mvComponentRegister.h
// October 2004

#pragma once

#ifdef LINUX_PLATFORM

// These macros are not needed in Linux
#define MV_COMPONENT_REGISTER_APARTMENT_THREADED
#define MV_COMPONENT_REGISTER_MULTI_THREADED
#define MV_COMPONENT_REGISTER 
#define MV_COMPONENT_UNREGISTER
#define MV_COMPONENT_UNREGISTER_APARTMENT_THREADED
#define MV_COMPONENT_UNREGISTER_MULTI_THREADED

#else

// define CoInitializeEx.
#define _WIN32_DCOM
#include <objbase.h>

#ifndef ASSERT
   #define ASSERT
#endif

//
// Summary:
//    APARTMENT_THREADED initialize of the DSX.sdk.
//
#define MV_COMPONENT_REGISTER_APARTMENT_THREADED \
{  \
	HRESULT hr; \
	hr = CoInitializeEx( NULL, COINIT_APARTMENTTHREADED );   \
   ASSERT(SUCCEEDED(hr));  \
}

//
// Summary:
//    MULTI_THREADED initialize of the DSX.sdk.
//
#define MV_COMPONENT_REGISTER_MULTI_THREADED \
{  \
	HRESULT hr; \
	hr = CoInitializeEx( NULL, COINIT_MULTITHREADED );   \
   ASSERT(SUCCEEDED(hr));  \
}

//
// Summary:
//    Initializes the application to use the DSX.sdk.
//
#define MV_COMPONENT_REGISTER MV_COMPONENT_REGISTER_APARTMENT_THREADED

//
// Summary:
//    Stops the application from using the DSX.sdk.
//
#define MV_COMPONENT_UNREGISTER \
{  \
   CoUninitialize(); \
}

//
// Summary:
//    APARTMENT_THREADED de-initialize of the DSX.sdk.
//
#define MV_COMPONENT_UNREGISTER_APARTMENT_THREADED    MV_COMPONENT_UNREGISTER

//
// Summary:
//    MULTI_THREADED de-initialize of the DSX.sdk.
//
#define MV_COMPONENT_UNREGISTER_MULTI_THREADED        MV_COMPONENT_UNREGISTER

#endif // LINUX_PLATFORM

