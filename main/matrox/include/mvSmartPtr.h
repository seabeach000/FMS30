//==========================================================================;
//
// (c) Copyright Matrox Electronic Systems Ltd., 1997. All rights reserved. 
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
//--------------------------------------------------------------------------;

//
// The class is to simplify the operation of interfaces .
// There are similar classes in ATL and MFC.
// With this smart pointer class, you don't need to call AddRef() 
// and Release() for the interface pointer.
//
// Usage: 
// e.g. IMediaChunk
//
// CMvSmartPtr< IMediaChunk >  m_pJMC ;
// m_pJMC -> SetEU( eu );
//   
// CMvSmartPtr< IMediaChunk >  pJMC1;
//
// pIMC1 = m_pJMC ;
//
// Note: Don't call Release function in this way:
// pJtr -> Release(). It will release the interface , but the smart pointer
// will still have a non-NULL value for its interface pointer.  If we 
// try to use the smart pointer , we'll get an access violation.
// Call in this way: pJtr.Release().  it will release the interface pointer and
// set it to NULL.


#pragma once

#include "mvThread.h"
#include "mvBaseCOM.h"

#ifndef LINUX_PLATFORM
   #include <crtDbg.h>
   #include <assert.h> // this defines the lower case assert
   #ifndef ASSERT
      #define ASSERT _ASSERTE
   #endif
#endif


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is the type of exception that can be thrown by the methods of the TMvSmartPtr and 
//    TMVSmartQPtr objects.  See CMvBaseException for more details.
// Remarks:
//    - All the operators are implemented to make the smart pointer behave like a normal interface 
//      pointer.
//    - These operators are: ->, !, &, *, =, == and T*.
//    - Any error will throw a CMvSmartPointerException. 
//
//////////////////////////////////////////////////////////////////////////
class CMvSmartPointerException : public CMvBaseException
{
public:
   // Constructor
   explicit CMvSmartPointerException(const std::string& in_strExceptionReason)
      : CMvBaseException(in_strExceptionReason) {}
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is the basic smart pointer template.
//
//////////////////////////////////////////////////////////////////////////
template < class T >
class TMvSmartPtr 
{
public:

   // Constructor
   TMvSmartPtr( )
   {
      m_ptInterface = NULL ;
   }

   //
   // Summary:
   //    Constructor calls in_ptInterface->AddRef() and keeps interface pointer.
   TMvSmartPtr
      (
      T * in_ptInterface   // COM pointer to handle.
      )
   {
      m_ptInterface = NULL ; 

      if( in_ptInterface != NULL )
      {
         in_ptInterface -> AddRef();
      }

      m_ptInterface = in_ptInterface ;
   }
      
   //
   // Summary:
   //    Constructor calls in_ptInterface->AddRef() and keeps interface pointer.
   TMvSmartPtr
      (
      const TMvSmartPtr< T >  & in_reftInterface   // reference to the COM pointer to handle.
      )
   {
      m_ptInterface = NULL ; 

      if( in_reftInterface.m_ptInterface != NULL )
      {
         in_reftInterface.m_ptInterface -> AddRef();
      }

      m_ptInterface = in_reftInterface.m_ptInterface ;
   }

   //
   // Summary:
   //    Destructor calls Release() on the internal interface that was passed in the constructor.
   //
   virtual ~TMvSmartPtr( )
   {
      Release();
   }

   //
   // Summary:
   //    Replaces the current pointer with the new one passed as parameter without doing an 
   //    AddRef().  The old one is released.
   //
   T* AssignNew
      (
      T * in_ptInterface   // New COM pointer to handle.
      )
   {
      if( m_ptInterface != NULL )
      {
         m_ptInterface -> Release();
         m_ptInterface = NULL ;
      }

      // We assign the newly created interface directly, without AddRef-ing
      // beacause its RefCount is already set to 1, and we are tbe the only
      // ones keeping the pointer on that interface.
      m_ptInterface = in_ptInterface ;

      return m_ptInterface ;
   }

   //
   // Summary:
   //    Release the internal pointer.
   //
   void Release( )
   {
      if( m_ptInterface != NULL )
      {
         m_ptInterface -> Release();
      }

      m_ptInterface = NULL ;
   }

   //
   // Summary:
   //    Returns the internal pointer.
   //      
   virtual operator T*( ) const 
   {
      return  m_ptInterface ;
   }

   //
   // Summary:
   //    Returns the internal pointer as an object.
   virtual T& operator*( )
   {
      if( m_ptInterface == NULL )
      {
         ASSERT( false ) ;
         throw CMvSmartPointerException("TMvSmartPtr::operator* -> Internal pointer is NULL!");
      }
      return *m_ptInterface ;
   }

   //
   // Summary:
   //    Return the address of the internal variable containning the internal pointer.
   //
   virtual T** operator&( )
   {
      if( m_ptInterface != NULL )
      {
         ASSERT( false ) ;
         throw CMvSmartPointerException("TMvSmartPtr::operator* -> Internal pointer will be overriden!");
      }
      return &m_ptInterface ;
   }
   
   //
   // Summary:
   //    Access the internal pointer
   //
   virtual T* operator->( )
   {
      if( m_ptInterface == NULL )
      {
         ASSERT( false ) ;
         throw CMvSmartPointerException("TMvSmartPtr::operator* -> Internal pointer is NULL!");
      }
      return m_ptInterface ;
   }

   //
   // Summary:
   //    Assign a new pointer.  The old pointer is released and the new one is "AddRefed".
   //
   virtual T* operator=( T* in_ptInterface )
   {
      if( in_ptInterface != NULL )
      {
         in_ptInterface -> AddRef( );
      }
      
      if( m_ptInterface != NULL )
      {
         m_ptInterface -> Release();
         m_ptInterface = NULL ;
      }
      
      m_ptInterface = in_ptInterface ;

      return m_ptInterface ;
   }

   //
   // Summary:
   //    NOT operator to replace (m_pTInterface == NULL)
   //
	virtual bool operator!( )
   {
      return (m_ptInterface == NULL);
   }

   //
   // Summary:
   //    Compare internal pointers.
   //
	virtual bool operator==(T* in_ptInterface)
	{
		return (m_ptInterface == in_ptInterface);
	}

   //
   // Summary:
   //    Assign a new pointer in a diffent way.
   //
   T* operator=( const TMvSmartPtr< T > &in_reftInterface )
   {
      return operator=( in_reftInterface.m_ptInterface );
   }
   
protected:
   T *	m_ptInterface;  // any interface.   
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This template is derived from the TMvSmartPtr template, it only adds the possibility to get 
//    another type interface pointer from a received interface.
//
//////////////////////////////////////////////////////////////////////////
template < class T, const IID* piid >
class TMvSmartQPtr : public TMvSmartPtr<T>
{

public:

   //
   // Summary:
   //    Default constructor.  Internal pointer is NULL.
	TMvSmartQPtr()
	{
	}

   //
   // Summary:
   //    Constructor calls in_ptInterface->AddRef() and keeps interface pointer.
	TMvSmartQPtr(T* in_ptInterface)
      : TMvSmartPtr<T>(in_ptInterface)
	{
	}

   //
   // Summary:
   //    Copy constructor.
   //
	TMvSmartQPtr(const TMvSmartQPtr<T,piid>& in_reftInterface)
      : TMvSmartPtr<T>(in_reftInterface.m_ptInterface)
	{
	}
   
   //
   // Summary:
   //    Constructor queries template interface T on the received IUnknown pointer.  Constructor 
   //    calls in_pIUnk->AddRef() and keeps the template interface pointer T.
   TMvSmartQPtr(IUnknown *in_pIUnk)
	{
		if (in_pIUnk != NULL)
		{
         T * pINewInterface=NULL;
         
			HRESULT hr = in_pIUnk->QueryInterface(*piid, (void **)&pINewInterface);
         			
         if (SUCCEEDED(hr))
         {
            TMvSmartPtr<T>::m_ptInterface = pINewInterface;
         }
         else
         {
            ASSERT( false ) ;
            throw CMvSmartPointerException("TMvSmartQPtr::TMvSmartQPtr -> Interface not supported.");
         }
		}
		else
		{
         ASSERT( false ) ;
         throw CMvSmartPointerException("TMvSmartQPtr::TMvSmartQPtr -> Invalid interface pointer");
		}
	}
   
   //
   // Summary:
   //    Constructor queries template interface T on the received IUnknown pointer.  Constructor 
   //    calls in_pIUnk->AddRef() and keeps the template interface pointer T.  Error is returned 
   //    in io_phr.
   TMvSmartQPtr(IUnknown *in_pIUnk, HRESULT *io_phr)
   {
      if (in_pIUnk != NULL)
      {
         T * pINewInterface=NULL;
         
         *io_phr = in_pIUnk->QueryInterface( *piid, (void **)&pINewInterface );
         
         if (SUCCEEDED(*io_phr))
         {
            TMvSmartPtr<T>::m_ptInterface = pINewInterface;
         }			
      }
      else
      {
         *io_phr = E_POINTER;
      }
   }

#ifndef LINUX_PLATFORM
   //
   // Summary:
   //    Enables QueryInterface on a smart pointer without providing the IID linked to the interface.
	template <class Q>
	void QueryInterface(Q** in_ppNewInterface)
	{
		ASSERT(in_ppNewInterface != NULL && *in_ppNewInterface == NULL);
		HRESULT hr = m_ptInterface->QueryInterface(__uuidof(Q), (void**)in_ppNewInterface);
      if FAILED(hr)
      {
         ASSERT( false ) ;
         throw CMvSmartPointerException("TMvSmartQPtr::QueryInterface -> Interface not supported.");
      }
	}
#endif
};

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Encapsulates a smart pointer in an STL template
//////////////////////////////////////////////////////////////////////////
template < class T >
class TMvSmartContrainerForSTL
{
public:
   //
   // Summary:
   //    Default constructor.  Encapsulated pointer is NULL.
   TMvSmartContrainerForSTL()
   {};
   
   //
   // Summary:
   //    Initializes the encapsulated pointer.
   TMvSmartContrainerForSTL(TMvSmartPtr <T> & in_rJPointer)
      : m_pJPointer (in_rJPointer)
   {};
      
   TMvSmartPtr <T> m_pJPointer;    // Specifies the encapsulated smart pointer.
};



