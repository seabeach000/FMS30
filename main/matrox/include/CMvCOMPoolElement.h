//$Archive: /VP/COMMON/LIBS/mvUtility/inc/CMvCOMPoolElement.h $
//==========================================================================;
//
// (c) Copyright Matrox Electronic Systems Ltd., 2003. All rights reserved.
//
// This code and information is provided "as is" without warranty of any kind,
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
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#pragma once

//==========================================================================;
// Header files
//==========================================================================;
#include "mvBaseCOM.h"

//==========================================================================;
// Forward declarations
//==========================================================================;
class CMvPoolManager;


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is the base class of the objects that can be used as pool elements.
// Remarks:
//    - While any objects that implements IUnknown can be used as a pool element, using one that does
//      not inherit from CMvPoolElement will cause memory leaks. 
//
//////////////////////////////////////////////////////////////////////////
class CMvCOMPoolElement :  public CMvUnknown
{
private :
   //==========================================================================;
   // Private operations
   //==========================================================================;

   // Dummy copy constructor.
   CMvCOMPoolElement(CMvCOMPoolElement &);

   // Dummy assignation operator
   void operator=(CMvCOMPoolElement &);

   //==========================================================================;
   // Private attributes
   //==========================================================================;

   bool m_bIsInThePool;    // Element is in the pool.

protected:
   //==========================================================================;
   // Protected operations
   //==========================================================================;

   //
   // Summary:
   //    Destructor.
   //
   virtual ~CMvCOMPoolElement()
   {
   }

   //==========================================================================;
   // Protected attributes
   //==========================================================================;


   //
   // Summary:
   //    The pool manager of the element.
   //
   CMvPoolManager * m_poPoolManager;

public:
   //==========================================================================;
   // Public operations
   //==========================================================================;

   //
   // Summary:
   //    This is the constructor of the base class.
   //
   CMvCOMPoolElement
      (
      const wchar_t * in_wszName,  // Name of the object, should be received from the inherited class
                                   // constructor.  Can be set to NULL, but this is not recommended, 
                                   // since this will lower the quantity of information that the COM
                                   // base class will output in case of memory leaks.
      IUnknown * in_pIUnk        // Pointer to the owner object, can be set to NULL.  Should be 
                                 // received from the inherited class constructor.
      );

   //
   // IUnknown interface
   //
   MVDECLARE_IUNKNOWN

   //
   // Summary:
   //    Decrement the internal reference count.
   // Description:
   //    When the ref count of an object reaches 1, the object is put back in the pool manager's list.
   // Return value:
   //    Returns the decremented reference count.
   //
   STDMETHODIMP_(unsigned long) NonDelegatingRelease();

   //
   // Summary:
   //    Increment the internal reference count.
   // Return value:
   //    Returns the incremented reference count.
   //
   STDMETHODIMP_(unsigned long) NonDelegatingAddRef();

   //
   // Summary:
   //    This method initializes the internal manager pointer.
   // Remarks:
   //    - This is the manager where the object is returned to.
   //
   void __stdcall SetManager
      (
      CMvPoolManager * io_pIManager // Pointer to the pool manager responsible for this pool element.
      );

   //
   // Summary:
   //    This method is used call by the pool manager when the element is return to the pool.
   // Remarks:
   //    - Overload this method so that the object can de-initialize itself before returning to the 
   //      pool.
   //
   virtual void __stdcall OnReturnToPool();

   //
   // Summary:
   //    This method is used call by the pool manager when the element is get out of the pool.
   // Remarks:
   //    - Overload this method so that the object can initialize itself.
   //      pool.
   //
   virtual void __stdcall OnLeaveFromPool();
};
