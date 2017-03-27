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

#ifndef LINUX_PLATFORM
#include <objbase.h>

// Ignore the warning because there is a conflict between stdint.h and intsafe.h
#pragma warning (push)
#pragma warning (disable: 4005)
#include <stdint.h>
#pragma warning (pop)
#endif

class CMvUnknown :
   public INonDelegatingUnknown
{
private:
   const LPUNKNOWN m_pkIUnknown;
   CMvUnknown(const CMvUnknown&);  // no implementation
   void operator=(const CMvUnknown&); // no implementation

protected:
   volatile int32_t m_i32Ref;
   

public:
   CMvUnknown(bool            bAddToObjectManager, 
              const wchar_t   *in_pwszName,
              IUnknown        *in_pIUnk,
              HRESULT         *out_phr);

   CMvUnknown(const wchar_t   *in_pwszName,
              IUnknown        *in_pIUnk,
              HRESULT         *out_phr);

   CMvUnknown(const wchar_t   *in_pwszName,
              IUnknown        *in_pIUnk);

   virtual ~CMvUnknown(void);

   const LPUNKNOWN GetOwner()
   {
     return m_pkIUnknown;
   }

   virtual STDMETHODIMP NonDelegatingQueryInterface(REFIID in_rIID, void ** out_ppv);
   virtual STDMETHODIMP_(unsigned long) NonDelegatingAddRef();
   virtual STDMETHODIMP_(unsigned long) NonDelegatingRelease();
   
   unsigned long m_ulCookie;
};
