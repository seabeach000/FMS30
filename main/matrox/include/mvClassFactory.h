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
#ifdef LINUX_PLATFORM
    #include "mvLinuxDefinitions.h"
#else
    #include <windows.h>
#endif
#include "mvFactoryTemplate.h"

class CMvClassFactory :
   public IClassFactory
{
public:
   CMvClassFactory(const CMvFactoryTemplate *in_poTemplate);
   ~CMvClassFactory(void);

   STDMETHODIMP QueryInterface(REFIID in_rIID,
                               void **out_ppv);
   STDMETHODIMP_(unsigned long) AddRef();
   STDMETHODIMP_(unsigned long) Release();
   STDMETHODIMP CreateInstance(LPUNKNOWN in_pIUnkOuter,
                               REFIID in_rsIID,
                               void **out_ppv);
   STDMETHODIMP LockServer(BOOL in_bLock);

   static BOOL IsLocked()
   {
      return ms_i32LockedCount;
   }

private:
   const CMvFactoryTemplate *const m_pkoTemplate;
   long        m_lRef;
   static int32_t ms_i32LockedCount;
   CMvClassFactory(const CMvClassFactory&);  // no implementation
   void operator=(const CMvClassFactory&); // no implementation
};
