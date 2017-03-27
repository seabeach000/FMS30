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

#include "mvUnknown.h"

typedef CMvUnknown* (CALLBACK *PFNNewCOMObject)(IUnknown *in_pIUnkOuter,
                                                HRESULT  *out_phr);

typedef void (CALLBACK *PFNInitRoutine)(bool in_bIsLoading,
                                        const CLSID *in_psClsID);


typedef HRESULT (CALLBACK *PFNRegistrationRoutine)(bool in_bIsLoading,
                                                   const CLSID *in_psClsID);

class CMvFactoryTemplate
{
public:
   const wchar_t          *m_pkwszName;
   const CLSID            *m_pksClsID;
   PFNNewCOMObject         m_pfnNew;
   PFNInitRoutine          m_pfnInit;
   PFNRegistrationRoutine  m_pfnRegistration;

   BOOL IsClassID(REFCLSID in_rsClsID) const
   {
      return (IsEqualCLSID(*m_pksClsID, in_rsClsID));
   };

   CMvUnknown *CreateInstance(IUnknown *in_pIUnk, 
                              HRESULT  *out_phr) const 
   {
      return m_pfnNew(in_pIUnk, out_phr);
   };

};
