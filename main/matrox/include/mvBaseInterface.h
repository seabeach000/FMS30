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

#ifdef LINUX_PLATFORM
   #include "mvLinuxDefinitions.h"
#else
   #include <windows.h>
   #define GetInterface(_x_, _y_) MvGetInterface(_x_, _y_)
#endif

STDAPI MvGetInterface(IUnknown *in_pIUnk, void **out_ppv);

//
// We have to ensure that we DON'T use a max macro, since these will typically   
// lead to one of the parameters being evaluated twice.  Since we are worried    
// about concurrency, we can't afford to access the m_i32Ref twice since we can't  
// afford to run the risk that its value having changed between accesses.        
//
namespace InternalBaseCom
{
   template<class T> inline static T NonDelegatingMax( const T & a, const T & b )
   {
      return a > b ? a : b;
   }
}

#ifndef INONDELEGATINGUNKNOWN_DEFINED
DECLARE_INTERFACE(INonDelegatingUnknown)
{
    virtual HRESULT __stdcall NonDelegatingQueryInterface(THIS_ REFIID, LPVOID *) PURE;
    virtual unsigned long __stdcall NonDelegatingAddRef(THIS) PURE;
    virtual unsigned long __stdcall NonDelegatingRelease(THIS) PURE;

    // The Linux g++ compiler needs a virtual desctructor here.
    #ifdef LINUX_PLATFORM
       virtual ~INonDelegatingUnknown() {};
    #endif
};
#define INONDELEGATINGUNKNOWN_DEFINED
#endif

#ifndef MVDECLARE_IUNKNOWN
#define MVDECLARE_IUNKNOWN                                        \
    inline virtual HRESULT __stdcall QueryInterface(REFIID riid, void **ppv) {      \
        return GetOwner()->QueryInterface(riid,ppv);            \
    };                                                          \
    inline virtual unsigned long __stdcall AddRef() {              \
        return GetOwner()->AddRef();                            \
    };                                                          \
    inline virtual unsigned long __stdcall Release() {             \
        return GetOwner()->Release();                           \
    }
#endif


typedef INonDelegatingUnknown *PNDUNKNOWN;

#ifndef LINUX_PLATFORM
   #pragma warning(push)
   #pragma warning( disable : 4100 )
#elif __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wself-assign"
#endif

#ifdef _DEBUG

//-----------------------------------------------------------------------
// MvAddRef
//-----------------------------------------------------------------------
inline long MvAddRef(IUnknown *in_pObj,
                     unsigned long in_ePackage = 0,
                     wchar_t  *in_pwszString = NULL)
{
   // To remove the warning until we really call the LOG manager
   in_ePackage = in_ePackage;

   if(in_pwszString)
   {
      OutputDebugStringW(in_pwszString);
   }

   if(in_pObj)
   {
      return in_pObj->AddRef();
   }
   return 0;
}

//-----------------------------------------------------------------------
// MvRelease
//-----------------------------------------------------------------------
inline long MvRelease(IUnknown *in_pObj,
                    unsigned long in_ePackage = 0,
                    wchar_t  *in_pwszString = NULL)
{
   // To remove the warning until we really call the LOG manager
   in_ePackage = in_ePackage;

   if(in_pwszString)
   {
      OutputDebugStringW(in_pwszString);
   }

   if(in_pObj)
   {
      return in_pObj->Release();
   }
   return 0;
}

//-----------------------------------------------------------------------
// MvSafeRelease
//-----------------------------------------------------------------------
inline long MvSafeRelease(IUnknown **in_ppObj,
                          unsigned long in_ePackage = 0,
                          wchar_t  *in_pwszString = NULL)
{
   // To remove the warning until we really call the LOG manager
   in_ePackage = in_ePackage;

   if(in_pwszString)
   {
      OutputDebugStringW(in_pwszString);
   }

   if(*in_ppObj)
   {
      long lRet = (*in_ppObj)->Release();
      *in_ppObj = NULL;
      return lRet;
   }
   return 0;
}

//-----------------------------------------------------------------------
// MvQueryInterface
//-----------------------------------------------------------------------
inline HRESULT MvQueryInterface(IUnknown *in_pObj,
                           REFIID    in_rIID,
                           void    **out_ppv,
                           unsigned long in_ePackage = 0,
                           wchar_t  *in_pwszString = NULL)
{
   // To remove the warning until we really call the LOG manager
   in_ePackage = in_ePackage;

   if(in_pwszString)
   {
      OutputDebugStringW(in_pwszString);
   }

   if(in_pObj)
   {
      return in_pObj->QueryInterface(in_rIID, out_ppv);
   }
   return 0;
}

#else // #ifdef _DEBUG

//-----------------------------------------------------------------------
// MvAddRef
//-----------------------------------------------------------------------
inline long MvAddRef(IUnknown *in_pObj,
                unsigned long in_ePackage = 0,
                wchar_t  *in_pwszString = NULL)
{
   return in_pObj->AddRef();
}

//-----------------------------------------------------------------------
// MvRelease
//-----------------------------------------------------------------------
inline long MvRelease(IUnknown *in_pObj,
                      unsigned long in_ePackage = 0,
                      wchar_t  *in_pwszString = NULL)
{
   return in_pObj->Release();
}

//-----------------------------------------------------------------------
// MvSafeRelease
//-----------------------------------------------------------------------
inline long MvSafeRelease(IUnknown **in_ppObj,
                          unsigned long in_ePackage = 0,
                          wchar_t  *in_pwszString = NULL)
{
   if(*in_ppObj)
   {
      long lRet = (*in_ppObj)->Release();
      *in_ppObj = NULL;
      return lRet;
   }
   return 0;
}


//-----------------------------------------------------------------------
// MvQueryInterface
//-----------------------------------------------------------------------
inline HRESULT MvQueryInterface(IUnknown *in_pObj,
                                REFIID    in_rIID,
                                void    **out_ppv,
                                unsigned long in_ePackage = 0,
                                wchar_t  *in_pwszString = NULL)
{
   return in_pObj->QueryInterface(in_rIID, out_ppv);
}

#endif // #ifdef _DEBUG

#ifndef LINUX_PLATFORM
   #pragma warning( pop )
#elif __clang__
  #pragma clang diagnostic pop
#endif


