//==============================================================================
//
// (c) Copyright Matrox Electronic Systems Ltd., 2011. All rights reserved. 
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
#include <list>
#include "mvHResult.h"


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This template class is used to manage pool of non-COM objects. It
//    is really simple in its implementation, as it dynamically allocates 
//    elements as needed, and has to be called back to return elements to
//    its internal list. 
// Remarks:
//    - This pool is intended to be used only where the moment of creation
//      and deletion of elements is well defined. For all other uses, use
//      CMvPoolElement and CMvPoolManager from mvfPoolManagerAPI.h.
//    - Elements that go out of the pool are not monitored, and as such
//      have to either be deleted by the caller or returned to the pool
//      via the TMvSimplePool::ReturnElement method after use, or they
//      will leak.
//
//////////////////////////////////////////////////////////////////////////
template <class T>
class TMvSimplePool
{
public:
   // Default constructor
   TMvSimplePool(){}

   // Destructor - will delete any element left in its internal list.
   ~TMvSimplePool()
   {
      CMvAutoLock oLock(&m_csListProtect);
      typename std::list<T*>::iterator it = m_listElements.begin();
      while(it != m_listElements.end())
      {
         delete (*it);
         it = m_listElements.erase(it);
      }
   }

   //
   // Summary:
   //    This method returns an element of its internal list via out_pptElement
   //    if any are available or else, allocates a new one.
   //
   HRESULT GetElement(T** out_pptElement)
   {
      CMvHResult ohr;

      if(!out_pptElement)
      {
         ohr = MV_E_INVALID_POINTER;
      }

      if(ohr.DidSucceed())
      {
         m_csListProtect.Wait();
         if(m_listElements.empty())
         {
            m_csListProtect.Release();
            T* pt = new T;
            if(pt)
            {
               *out_pptElement = pt;
            }
            else
            {
               ohr = MV_E_OUT_OF_MEMORY;
            }
         }
         else
         {
            *out_pptElement = m_listElements.front();
            m_listElements.pop_front();
            m_csListProtect.Release();
         }
      }
      return ohr;
   }

   //
   // Summary:
   //    This method must be called in order to return an element to the
   //    pool.
   //
   HRESULT ReturnElement(T* in_ptElement)
   {
      CMvHResult ohr;
      if(!in_ptElement)
      {
         ohr = MV_E_INVALID_POINTER;
      }

      if(ohr.DidSucceed())
      {
         CMvAutoLock oLock(&m_csListProtect);
         m_listElements.push_back(in_ptElement);
      }
      return ohr;
   }

private:
   // Prevent copy
   TMvSimplePool(const TMvSimplePool<T>&){}
   TMvSimplePool<T>& operator=(const TMvSimplePool<T>&){}

   CMvCriticalSection m_csListProtect;
   std::list<T*> m_listElements;
};
