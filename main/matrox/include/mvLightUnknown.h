//==============================================================================
//
// (c) Copyright Matrox Electronic Systems Ltd., 2003-2015. All rights reserved. 
//
// This code and information is provided "as is" without warranty of any kind, 
// either expressed or implied, including but not limited to the implied 
// warranties of merchantability and/or fitness for a particular purpose.
//
// All code and information is provided "as is" without warranty of any kind, 
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
//===============================================================================

#pragma once
#ifndef LINUX_PLATFORM
#ifndef _WCHAR_T_DEFINED
#error/Zc:wchar_t must be used in your project properties
#endif
#ifndef _NATIVE_WCHAR_T_DEFINED
#error/Zc:wchar_t must be used in your project properties
#endif
#endif //LINUX_PLATFORM

#include "mvBaseInterface.h"
#include "mvUnknown.h"

#ifndef	LINUX_PLATFORM
#include <objbase.h>
#endif

#include "mvDefinitions.h"

class MV_DECLSPEC_DLLEXPORT CMvLightUnknown :
   public INonDelegatingUnknown
{
private:
   const LPUNKNOWN m_pkIUnknown;
   CMvLightUnknown(const CMvLightUnknown&);  // no implementation
   void operator=(const CMvLightUnknown&); // no implementation
   
protected:
   int32_t m_i32Ref;
   virtual ~CMvLightUnknown(void);

public:
   CMvLightUnknown(const wchar_t * in_pwszName, IUnknown * in_pIUnk, HRESULT * out_phr);
   CMvLightUnknown(const wchar_t * in_pwszName, IUnknown * in_pIUnk);

   const LPUNKNOWN GetOwner()
   {
      return m_pkIUnknown;
   }

   virtual STDMETHODIMP NonDelegatingQueryInterface(REFIID in_rIID, void ** out_ppv);
   virtual STDMETHODIMP_(unsigned long) NonDelegatingAddRef();
   virtual STDMETHODIMP_(unsigned long) NonDelegatingRelease();
};
