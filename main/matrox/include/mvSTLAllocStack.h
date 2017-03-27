//==========================================================================;
//
// (c) Copyright Matrox Electronic Systems Ltd., 2002. All rights reserved.
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
//   Birth Date:             Jan 8, 2004
//   Operating System:       WinXP
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#pragma once

#include <memory>
#include <limits>

#pragma push_macro("max")
#ifdef max
#undef max
#endif

#ifndef ASSERT
   #define ASSERT assert
#endif

#pragma warning(push)
#pragma warning(push)
#pragma warning (disable:4512)
#pragma warning (disable:4100)

///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This template is almost the same as the TMvSTLAlloc template but it is dedicated to memory 
//    allocation on the stack.
// Description:
//    It is very efficient to work with a stack allocator instead of the
//    default allocator (that does "new" and "delete").  Tests showed that it increased the speed 
//    by 50% in all cases and by more than 60% on small remove and add operations.
// Example:
//    The following example will use "T = TMvSmartPtr<IUnknown>" object with containers and 
//    "allocator" is the default STL allocator.
//
//    Standard declaration:
//    <CODE>
//    list< TMvSmartPtr<IUnknown> > listpJUnk;
//    </CODE>
//
//    Declaration with our stack allocator:
//    <CODE>
//    const size_t  sizeStackSize = 4048;
//    unsigned char auchStack[sizeStackSize];
//
//    TMvSTLAllocStack < TMvSmartPtr<IUnknown> > stlAllocStack(auchStack, sizeStackSize);
//
//    std::list< TMvSmartPtr<IUnknown>, TMvSTLAllocStack< TMvSmartPtr<IUnknown> > > listOnTheStack( stlAllocStack );
//    </CODE>
//
//    The mechanism is the same for all the STL containers; refer to TMvSTLAlloc for more examples.
//
///////////////////////////////////////////////////////////////////////////////
template <typename T>
class TMvSTLAllocStack 
{
private:

   // Forward declaration
   struct MemoryInfo;

public:

   // Typedefs
   typedef size_t    size_type;
   typedef ptrdiff_t difference_type;
   typedef T*        pointer;
   typedef const T*  const_pointer;
   typedef T&        reference;
   typedef const T&  const_reference;
   typedef T         value_type;

   // Constructors
   TMvSTLAllocStack() throw()
      :
   mpMemInfo( new MemoryInfo )
   {
      //char temp[128];
      //sprintf(temp, "Stack Allocator:; Allocation:;%u \n", sizeof(MemoryInfo));
      //OutputDebugString(temp);
   }

   TMvSTLAllocStack( unsigned char* pStack, size_t nMaxBytes ) throw()
      :
   mpMemInfo( new MemoryInfo( pStack, nMaxBytes ) )
   {
      //char temp[128];
      //sprintf(temp, "Stack Allocator:; Allocation:;%u \n", sizeof(MemoryInfo));
      //OutputDebugString(temp);
   }

   TMvSTLAllocStack( const TMvSTLAllocStack& sa ) throw()
      :
   mpMemInfo( sa.mpMemInfo )
   {
      ++mpMemInfo->mRefCount;
   }

#if _MSC_VER >= 1300 // VC6 can't handle template members
   template <typename U>
      TMvSTLAllocStack( const TMvSTLAllocStack<U>& sa ) throw()
      :
   mpMemInfo( (TMvSTLAllocStack<T>::MemoryInfo*)( sa.mpMemInfo ) )
   {
      ++mpMemInfo->mRefCount;
   }
#endif

   TMvSTLAllocStack& operator=( const TMvSTLAllocStack& sa )
   {
      mpMemInfo = sa.mpMemInfo;
      ++mpMemInfo->mRefCount;
      return *this;
   }

   // Destructor
   ~TMvSTLAllocStack() throw()
   {
      ASSERT( mpMemInfo != NULL );
      if( --mpMemInfo->mRefCount == 0 )
      {
         delete mpMemInfo;
         //char temp[128];
         //sprintf(temp, "Stack Allocator:; Deallocation:;%u \n", sizeof(MemoryInfo));
         //OutputDebugString(temp);
      }
   }

   // Utility functions
   pointer address( reference r ) const
   {
      return &r;
   }   

   size_type max_size() const
   {
      return std::numeric_limits<size_t>::max() / sizeof(T);
   }

   // In-place construction
   void construct( pointer p, const_reference c )
   {
      // placement new operator
      new( reinterpret_cast<void*>(p) ) T(c);
   }

   // In-place destruction
   void destroy( pointer p )
   {
      // call destructor directly
      (p)->~T();
   }

   // Rebind to allocators of other types
   template <typename U>
   struct rebind
   {
      typedef TMvSTLAllocStack<U> other;
   };

   // Allocate raw memory
   pointer allocate( size_type n, const void* = NULL )
   {
      ASSERT( mpMemInfo->mpStack != NULL );
      void* pRaw = mpMemInfo->mpStack + mpMemInfo->mBytesAllocated;
      mpMemInfo->mBytesAllocated += ( n * sizeof(T) );

      if( mpMemInfo->mBytesAllocated + 1 > mpMemInfo->mMaxBytes )
         throw std::bad_alloc();

      return pointer(pRaw);
   }

   // Free raw memory.
   // Note that C++ standard defines this function as
   // deallocate( pointer p, size_type). Because Visual C++ 6.0
   // compiler doesn't support template rebind, Dinkumware uses
   // void* hack.
   void deallocate( void*, size_type )
   {
      // No need to free stack memory
   }

   // Non-standard Dinkumware hack for Visual C++ 6.0 compiler.
   // VC 6 doesn't support template rebind.
   char* _Charalloc( size_type nBytes )
   {
      ASSERT( mpMemInfo->mpStack != NULL );
      char* pRaw = reinterpret_cast<char*>( mpMemInfo->mpStack ) + 
         mpMemInfo->mBytesAllocated;
      mpMemInfo->mBytesAllocated += nBytes;

      if( mpMemInfo->mBytesAllocated + 1 > mpMemInfo->mMaxBytes )
         throw std::bad_alloc();

      return pRaw;
   }

   const MemoryInfo* GetMemInfo() const
   {
      return mpMemInfo;
   }

private:

   struct MemoryInfo
   {
      unsigned char* mpStack;
      size_t         mBytesAllocated; //Keeping the size_t types to be conform with stl
      size_t         mMaxBytes;
      size_t         mRefCount;

      MemoryInfo()
         :
      mpStack( NULL ),
         mBytesAllocated( 0 ),
         mMaxBytes( 0 ),
         mRefCount( 1 )
      {
      }

      MemoryInfo( unsigned char* pStack, size_t nMaxBytes )
         :
      mpStack( pStack ),
         mBytesAllocated( 0 ),
         mMaxBytes( nMaxBytes ),
         mRefCount( 1 )
      {
      }

   };

private:

   MemoryInfo* mpMemInfo;

#if _MSC_VER >= 1300 // VC6 can't handle template friends
   // Grant all specializations access to mpMemInfo.
   // This is required for the template copy ctor to have access.
   template <typename U> friend class TMvSTLAllocStack;
#endif

};

// Comparison
template <typename T1>
bool operator==( const TMvSTLAllocStack<T1>& lhs, const TMvSTLAllocStack<T1>& rhs) throw()
{
   return lhs.GetMemInfo() == rhs.GetMemInfo();
}

template <typename T1>
bool operator!=( const TMvSTLAllocStack<T1>& lhs, const TMvSTLAllocStack<T1>& rhs) throw()
{
   return lhs.GetMemInfo() != rhs.GetMemInfo();
}

#pragma warning(pop)
#pragma warning(pop)

#pragma pop_macro("max")

