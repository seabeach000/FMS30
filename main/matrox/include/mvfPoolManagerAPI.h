#ifndef MVF_POOL_MANAGER_API_H
#define MVF_POOL_MANAGER_API_H

//==============================================================================
//
// (c) Copyright Matrox Electronic Systems Ltd., 2003. All rights reserved. 
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
   #include "mvLinuxGuidDef.h"
#else
   #include <windows.h>
   #include <guiddef.h>
#endif

#include <deque>

#include "mvBaseCOM.h"
#include "mvThread.h"

#include "CMvCOMPoolElement.h"
#include "mvSTLAlloc.h"
#include "mvTypes.h"

//////////////////////////////////////////////////////////////////////////
//       G U I D S
//////////////////////////////////////////////////////////////////////////

// {F75CB080-7EE6-4e8f-BCAC-5F5F521EEE7E}
DEFINE_GUID(IID_IMvPoolManager, 
   0xf75cb080, 0x7ee6, 0x4e8f, 0xbc, 0xac, 0x5f, 0x5f, 0x52, 0x1e, 0xee, 0x7e);

// {78F8FEB4-2C7F-4828-BB40-8748F61B53DE}
DEFINE_GUID(IID_IMvPoolManager2, 
            0x78f8feb4, 0x2c7f, 0x4828, 0xbb, 0x40, 0x87, 0x48, 0xf6, 0x1b, 0x53, 0xde);

// {F794C056-F11F-4f63-9980-F02C581F101E}
DEFINE_GUID(IID_IMvPoolAllocator, 
			0xf794c056, 0xf11f, 0x4f63, 0x99, 0x80, 0xf0, 0x2c, 0x58, 0x1f, 0x10, 0x1e);


//////////////////////////////////////////////////////////////////////////
//     I N T E R F A C E S
//////////////////////////////////////////////////////////////////////////

interface IMvPoolManager;
interface IMvPoolAllocator;


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is the interface exposed by the pool manager object.
// Remarks:
//    - It is used to retrieve and return pool element objects.
//    - To obtain a pool element, the user application must call GetElement().
//    - To send back the element to the pool, the user-application must call PoolElement->Release().
//      (If the user application performed more AddRef on the PoolElement, it wont return to the
//      pool until all the AddRefs are "released").
//
//////////////////////////////////////////////////////////////////////////
interface IMvPoolManager: public IUnknown
{
   //
   // Summary:
   //    This method is used to get a free element from the pool.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - Error message from the IMvPoolAllocator object if the creation failed.
   // Remarks:
   //    - If there is no element left, another one will be created.
   //    - Returned element reference count is increased by one.
   //    - Pool manager reference count is increased by one.

   virtual HRESULT __stdcall GetElement
      (
      IUnknown ** io_ppIElement  // Address of a pointer that will receive the pool element retrieved.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is the interface exposed by the pool manager object.
// Remarks:
//    - It is used to retrieve and return pool element objects.
//    - To obtain a pool element, the user application must call GetElement().
//    - To send back the element to the pool, the user-application must call PoolElement->Release().
//      (If the user application performed more AddRef on the PoolElement, it wont return to the
//      pool until all the AddRefs are "released").
//    - It allows getting status of the pool.
//
//////////////////////////////////////////////////////////////////////////
interface IMvPoolManager2: public IMvPoolManager
{
   //
   // Summary:
   //    This method is used to get the number of used elements in the pool.
   // Return value:
   //    The number of used elements.
   virtual uint32_t __stdcall GetUsedCount() = 0;

   //
   // Summary:
   //    This method is used to get the maximum number of used elements in the pool.
   // Return value:
   //    The number of used elements.
   virtual uint32_t __stdcall GetMaxUsedCount() = 0;

   //
   // Summary:
   //    This method is used to get the number of free elements in the pool.
   // Return value:
   //    The number of used elements.
   virtual uint32_t __stdcall GetFreeCount() = 0;
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Objects that can be used to allocate pool elements must implement this interface.
// Description:
//    It is used by the pool manager to allocate pool elements.  There is no base class for this 
//    interface, it is the responsibility of the user application to implement it.
//
//////////////////////////////////////////////////////////////////////////
interface IMvPoolAllocator: public IUnknown
{
   //
   // Summary:
   //    This is the interface that needs to be implemented by the objects that are used to allocate
   //    pool elements.
   // Return value:
   //    User-defined
   // Remarks:
   //    - It is important that the allocation does not CAST from the allocated class to the 
   //      IUnknown interface.  Call the object's QueryInterface() methods and then release the 
   //      pointer to the object.
   virtual HRESULT __stdcall Allocate
      (
      IUnknown ** io_pIElement   // Address of a pointer that will receive the created element.
      ) = 0;

   //!IGNORE!
   virtual unsigned long __stdcall GetSize() { return 0; }
};


//////////////////////////////////////////////////////////////////////////
// I M P L E M E N T A T I O N   C L A S S E S
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This class implement the pool manager that is used to handle free pool elements.
// Description:
//    This class is the core of the pool manager: it is responsible for managing a dynamic list of
//    all the unused pool elements.  At its creation, this class must fill the dynamic list with a 
//    number of pool elements. 
// Remarks :
//    - This class implements the interface IMvPoolManager.
//    - When the user application requests a pool element, the manager must first check if there 
//      are any left; if yes, it removes one from the list and gives it to the user-application, 
//      if not, it creates one and returns it.  All the returned element reference counts are 
//      increased by one by the GetElement() method (from the IMvPoolManager interface). 
//    - When the user application gives back a pool element, the manager must put it back in the
//      list. At destruction time, the manager must release every pool elements in the list. 
//////////////////////////////////////////////////////////////////////////
class CMvPoolManager : public IMvPoolManager2 , public CMvLightUnknown
{

#ifndef LINUX_PLATFORM

   // Internal definition to simplify the code
   typedef TMvSTLAlloc< IUnknown *> dequepIUnknownAlloc;

   // Internal definition to simplify the code
   typedef std::deque<IUnknown*, dequepIUnknownAlloc> dequepIUnknown;

#else // !LINUX_PLATFORM

   // For linux, use the default allocator
   // as it does the same job as our custom one
   // for the other platforms
   typedef std::deque<IUnknown*> dequepIUnknown;
   
#endif // !LINUX_PLATFORM

private:
   // Dummy copy constructor.
   CMvPoolManager(CMvPoolManager &):CMvLightUnknown(NULL, NULL){}

   // Dummy assignation operator
   void operator=(CMvPoolManager &){}

public:
   //
   // Summary:
   //    Constructor.
   CMvPoolManager( const wchar_t    * in_pwszName,          // Name to identify this pool manager.
                                                               // This string will be passed down to
                                                               // the CMvLightUnknown constructor.
                   unsigned long      in_ulInitialCount,    // Number of pool elements that must be
                                                               // created initially.
                   IMvPoolAllocator * in_pIPoolAllocator,   // Pointer to the pool element allocator. 
                                                               // If set to NULL, the pool manager
                                                               // will not work correctly.
				   bool in_bDerived = false );

   // Default destructor
   virtual ~CMvPoolManager();

   //
   // IUNKNOWN
   //

   MVDECLARE_IUNKNOWN

   // Override the QueryInterface to add interface.
   STDMETHODIMP NonDelegatingQueryInterface(REFIID in_rIID, void **out_ppv);

   //
   // IMvPoolManager
   //

   // Return a free element.
   virtual HRESULT __stdcall GetElement(IUnknown ** io_ppIElement);

   // 
   // IMvPoolManager2
   virtual uint32_t __stdcall GetUsedCount();
   virtual uint32_t __stdcall GetMaxUsedCount();
   virtual uint32_t __stdcall GetFreeCount();


   //
   // Class implementation
   //

   // Put an element in the free list.
   virtual HRESULT __stdcall ReturnElement(IUnknown * in_pIElement);

protected:

   bool           m_bDerived;       // Internal debugging variable.
   wchar_t        m_wstrName[256];  // Name of the pool manager
   unsigned long  m_ulUnitSize;     // Size in byte of one element
   unsigned long  m_ulInitialCount; // Initial number of elements to allocate on creation.

   //////////////////////////////////////////////////////////////////////////
   // We need a critical section to synchroniz access to the deque.
   CMvCriticalSection m_csDeqElements;

   //////////////////////////////////////////////////////////////////////////
   // Count of outstanding elements. We moved this to the base class,
   // because we already have an atomic add/removal of elements
   unsigned long m_ulUsedCount;

   //////////////////////////////////////////////////////////////////////////
   // Maximum Count of outstanding elements. 
   unsigned long m_ulMaxUsedCount;

   // deque are faster than vector when we only add and remove from the end (back) of the vector list
   dequepIUnknown m_deqElements;

   // Pointer to an IMvPoolAllocator interface that can allocate pool elements.
   IMvPoolAllocator * m_pIPoolAllocator;

   // Allocate a new element.
   HRESULT _AllocateNewElement(IUnknown ** io_ppIElement);
};


//-----------------------------------------------------------------------
// class CMvPoolElement
//-----------------------------------------------------------------------
class CMvPoolElement : public CMvCOMPoolElement
{
public:
   // Default constructor
   CMvPoolElement(const wchar_t *in_wszName, IUnknown *in_pIUnk);

   // Default destructor
   virtual ~CMvPoolElement(){};

};

#endif // MVF_POOL_MANAGER_API_H
