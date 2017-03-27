//$Archive: /VP/COMMON/LIBS/MVUTILITY/inc/mvManagerAccess.h $
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

#pragma once

#ifdef LINUX_PLATFORM
#include "mvLinuxDefinitions.h"
#else
#include <Windows.h> //For HANDLE and CreateFileMapping

#ifndef ASSERT
#include <crtDbg.h>
#include <assert.h> // this defines the lower case assert
#define ASSERT _ASSERTE
#endif
#endif

#include "_mvManagerIntitializerIF.h"     // For IMvManagerInitializer

#include "mvMessageManagerIF.h"           // For IMvMessageManager
#include "_mvSettingsManagerIF.h"         // For IMvSettingsManager
#include "_mvSettingsManager2IF.h"        // For IMvSettingsManager2
#include "_mvReadOnlySettingsManagerIF.h" // For IMvReadOnlySettingsManager
#include "_mvMessageManagerInternalIF.h"  // For IMvMessageManagerInternal


// ---------------------------------------------------------------------------------------------------------------------
template<typename IMvManager> 
static inline void __stdcall InitializeIMvSettingsManager(const GUID & in_krIID, IMvManager ** out_ppIMvManager)
{
   HRESULT hr = NOERROR;
   IMvManagerInitializer * pISettingsManagerInitializer = NULL;
   IMvManager * pIMvManager = NULL;

   // CoCreate Settings Manager
   hr = CoCreateInstance
      (
      CLSID_IMvSettingsManager, 
      NULL, 
      CLSCTX_INPROC_SERVER,  
      IID_IMvManagerInitializer, 
      (void**)&pISettingsManagerInitializer
      );

   if (SUCCEEDED(hr))
   {
      hr = pISettingsManagerInitializer->QueryInterface(in_krIID, (void**)&pIMvManager);
   }
   else
   {
#ifdef	LINUX_PLATFORM
      ASSERT(false);
#else		
      bool bFailToCoCreateSettingsManager = false;
      assert(bFailToCoCreateSettingsManager);
      UNREFERENCED_PARAMETER(bFailToCoCreateSettingsManager);
#endif		
   }
   /////////////////////////////////////////////////////////////////////
   // Then, intialize them so that they can be aware of each other
   // Afterwards, you don't need the IMvManagerInitializer interfaces
   /////////////////////////////////////////////////////////////////////

   if (pISettingsManagerInitializer)
   {
      pISettingsManagerInitializer->Initialize();
      pISettingsManagerInitializer->Release();
   }

   *out_ppIMvManager = pIMvManager;
}


// ---------------------------------------------------------------------------------------------------------------------
template<typename IMvManager>
static inline void __stdcall InitializeIMvMessageManager(const GUID & in_krIID, IMvManager ** out_ppIMvManager)
{
   HRESULT hr = NOERROR;
   IMvManagerInitializer* pIMessageManagerInitializer	= NULL;
   IMvManager * pIMvManager = NULL;

   //CoCreate Message Manager
   hr = CoCreateInstance
      (
      CLSID_IMvMessageManager, 
      NULL, 
      CLSCTX_INPROC_SERVER,  
      IID_IMvManagerInitializer, 
      (void**)&pIMessageManagerInitializer);

   if(SUCCEEDED(hr))
   { 
      hr = pIMessageManagerInitializer->QueryInterface(in_krIID, (void**)&pIMvManager);
   }
   else
   {
#ifdef	LINUX_PLATFORM
      ASSERT(false);
#else		
      bool bFailToCoCreateMessagesManager = false;
      assert(bFailToCoCreateMessagesManager);
      UNREFERENCED_PARAMETER(bFailToCoCreateMessagesManager);
#endif		
   }

   /////////////////////////////////////////////////////////////////////
   // Then, intialize them so that they can be aware of each other
   // Afterwards, you don't need the IMvManagerInitializer interfaces
   /////////////////////////////////////////////////////////////////////

   if (pIMessageManagerInitializer)
   {
      pIMessageManagerInitializer->Initialize();
      pIMessageManagerInitializer->Release();
   }

   *out_ppIMvManager = pIMvManager;
}


// From interface IMvCentralManager
// ---------------------------------------------------------------------------------------------------------------------
inline void __stdcall GetIMvMessageManager(IMvMessageManager ** out_ppIMvMessageManager)
{
   InitializeIMvMessageManager<IMvMessageManager>(IID_IMvMessageManager, out_ppIMvMessageManager);
}


//From interface IMvCentralManagerInternal
// ---------------------------------------------------------------------------------------------------------------------
inline void __stdcall GetIMvMessageManagerInternal(IMvMessageManagerInternal ** out_ppIMvMessageManagerInternal)
{
   InitializeIMvMessageManager<IMvMessageManagerInternal>(IID_IMvMessageManagerInternal, out_ppIMvMessageManagerInternal);
}


// ---------------------------------------------------------------------------------------------------------------------
inline void __stdcall GetIMvSettingsManager(IMvSettingsManager ** out_ppIMvSettingsManager)
{
   InitializeIMvSettingsManager<IMvSettingsManager>(IID_IMvSettingsManager, out_ppIMvSettingsManager);
}


// ---------------------------------------------------------------------------------------------------------------------
inline void __stdcall GetIMvReadOnlySettingsManager(IMvReadOnlySettingsManager ** out_pIMvReadOnlySettingsManager)
{
   InitializeIMvSettingsManager<IMvReadOnlySettingsManager>(IID_IMvReadOnlySettingsManager, out_pIMvReadOnlySettingsManager);
}


// ---------------------------------------------------------------------------------------------------------------------
inline void __stdcall GetIMvSettingsManager2(IMvSettingsManager2 ** out_ppIMvSettingsManager2)
{
   InitializeIMvSettingsManager<IMvSettingsManager2>(IID_IMvSettingsManager2, out_ppIMvSettingsManager2);
}