/*

(c) Copyright Matrox Electronic Systems Ltd., 2009. All rights reserved. 

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

// THIS MODULE IS NOT COMPATIBLE WITH LINUX

#pragma once

//#ifndef LINUX_PLATFORM
    #include "mvfPoolManagerAPI.h"
    #include "mvHelperClassesAPI.h"
//#else
//#endif

class CMvVirtualMemoryElement : public CMvPoolElement, public IMvVirtualMemoryElement
{
public:
   // Constructor
   CMvVirtualMemoryElement( unsigned long in_ulSizeInBytes );

   // Destructor
   virtual ~CMvVirtualMemoryElement();

   MVDECLARE_IUNKNOWN;

   //
   // NonDelegatingQueryInterface
   //
   STDMETHODIMP NonDelegatingQueryInterface(REFIID in_rIID, void** out_ppv);

   virtual HRESULT __stdcall GetPointerAndSize(
      void** out_pBuffer, 
      unsigned long& io_rulSizeInBytes);

private:
   CMvVirtualMemoryElement();
   CMvVirtualMemoryElement(CMvVirtualMemoryElement &);
   void operator=(CMvVirtualMemoryElement &);

   void* m_pBuffer;
   unsigned long m_ulSizeInBytes;
};

class CMvVirtualMemoryAllocator : public CMvLightUnknown, public IMvPoolAllocator
{
public:
   CMvVirtualMemoryAllocator(
      wchar_t * in_pwszName, 
      unsigned long in_ulSizeInBytesOfEachElement) 
      : CMvLightUnknown(in_pwszName, NULL)
         , m_ulSizeInBytesOfEachElement(in_ulSizeInBytesOfEachElement){};

      virtual ~CMvVirtualMemoryAllocator() {};

      //
      // interface IUnknown 
      //
      MVDECLARE_IUNKNOWN;

      //
      // interface IMvPoolAllocator
      //
      unsigned long __stdcall GetSize();

      HRESULT __stdcall Allocate(IUnknown ** io_pIElement);

private:
   CMvVirtualMemoryAllocator(CMvVirtualMemoryAllocator&) : CMvLightUnknown(NULL, NULL){}
   void operator=(CMvVirtualMemoryAllocator&){}
   CMvVirtualMemoryAllocator() : CMvLightUnknown(NULL, NULL){}
   unsigned long m_ulSizeInBytesOfEachElement;
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//
// CMvVirtualMemoryPoolManager
//
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

class CMvVirtualMemoryPoolManager : public CMvPoolManager
{
public:
   static IMvPoolManager * CreatePoolManager(
      const wchar_t  * in_pwszName,
      unsigned long    in_ulInitialCount,
      unsigned long    in_ulSizeInBytesOfEachElement);

   virtual ~CMvVirtualMemoryPoolManager() {};

protected:
   CMvVirtualMemoryPoolManager(
      const wchar_t    * in_pwszName,
      unsigned long      in_ulInitialCount,
      IMvPoolAllocator * in_pIPoolAllocator)
      : CMvPoolManager(in_pwszName, in_ulInitialCount, in_pIPoolAllocator) {};
};

//#endif
