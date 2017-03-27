#ifndef MV_STL_ALLOC_H
#define MV_STL_ALLOC_H

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
//   Birth Date:             Jan 6, 2004
//   Operating System:       WinXP
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#pragma once

#include <memory>
#include <limits>

#ifndef LINUX_PLATFORM

   #pragma push_macro("max")
   #ifdef max
      #undef max
   #endif // max

   #pragma warning(push)
   #pragma warning(push)
   #pragma warning (disable:4512)
   #pragma warning (disable:4100)

   #ifdef MV_DEBUG_STL_ALLOCATOR_MEMORY
      #pragma message("MV_DEBUG_STL_ALLOCATOR_MEMORY defined")
   #endif // MV_DEBUG_STL_ALLOCATOR_MEMORY

   #ifndef ASSERT
      #include <crtDbg.h>
      #include <assert.h> // this defines the lower case assert
      #define ASSERT _ASSERTE
   #endif

#endif // !LINUX_PLATFORM


///////////////////////////////////////////////////////////////////////////////
//
// Number of block allocated every shot
const unsigned long kulMvSTLAllocDefaultPreAllocationBlockCount = 1;

//extern "C"   unsigned long g_ulMemBlockAllocate;
//
//extern "C"   unsigned long g_ulMemBlockRelease;


///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This template was added to optimize memory allocation and de-allocation of STL containers 
//    (vector, deque, list, map, etc.).
// Description:
//    This template replaces the default STL memory allocator which does not implement a memory 
//    cache and does constantly "new" and "delete" when doing operations on containers (push_back, 
//    pop_front, insert, etc.).
//
//    This template allocates memory but never frees it; it puts the free memory into an internal
//    cache for reuse without re-allocating memory.  It also enables memory allocation by block,
//    that means you can force the allocator to allocate a large block of memory every time there's 
//    a need for it, and let it work inside this large block.
//
//    This description does not show how to call the TMvSTLAlloc template because the STL containers
//    call it internally.  However, it will show how to use it with the common STL containers.
//    Basically, all you have to do to use it is to change the declaration of the STL containers 
//    in the header files where you are using them.
//
// When to use it:
//       If you use an STL container that removes or adds items frequently you should use our 
//       allocation template, the speed gain can be more than 50% (tested on a P4 2.4GHz) and you
//       will not do any "new" and "delete" which should be avoided at all costs when doing video 
//       and audio streaming.
//
//       However, if you use a STL container statically, like when you build a list once and never
//       add or remove items frequently, you won't have any gain since a cache allocation mechanism
//       is useless in that case.
//
// STL on the stack:
//       If you want to use an STL component on the stack (declaring and using an STL component 
//       inside a scope) you will need to use the TMvSTLAllocStack template, which is dedicated to 
//       this particular case.
//
//    Following examples will use " T = TMvSmartPtr<IUnknown> " object with containers and 
//    "allocator" is the default STL allocator. 
//    
// Examples:
//    Vector: Template < class T, class Allocator = allocator > class vector;
//
//       Standard declaration:
//          <CODE>
//          vector< TMvSmartPtr<IUnknown> > vecpJUnk;
//          </CODE>
//
//       Declaration with our allocator:
//          <CODE>
//          vector< TMvSmartPtr<IUnknown>, TMvSTLAlloc< TMvSmartPtr<IUnknown> > > vecpJUnk;
//          </CODE>
//
//       Declaration  with our allocator and a defined block size of 8:
//          <CODE>
//          TMvSTLAlloc< TMvSmartPtr<IUnknown> > stlAllocpJUnk(8);
//
//          vector< TMvSmartPtr<IUnknown>, TMvSTLAlloc< TMvSmartPtr<IUnknown> > > vecpJUnk(stlAllocpJUnk);
//          </CODE>
//
// Examples:
//    Deque: Template < class T, class Allocator = allocator > class deque;
//
//       Standard declaration:
//          <CODE>
//          deque< TMvSmartPtr<IUnknown> > deqpJUnk;
//          </CODE>
//
//       Declaration with our allocator:
//          <CODE>
//          deque< TMvSmartPtr<IUnknown>, TMvSTLAlloc< TMvSmartPtr<IUnknown> > > deqpJUnk;
//          </CODE>
//
//       Declaration  with our allocator and a defined block size of 8:
//          <CODE>
//          TMvSTLAlloc< TMvSmartPtr<IUnknown> > stlAllocpJUnk(8);
//
//          deque< TMvSmartPtr<IUnknown>, TMvSTLAlloc< TMvSmartPtr<IUnknown> > > deqpJUnk(stlAllocpJUnk);
//          </CODE>
//
// Examples:
//    List: Template < class T, class Allocator = allocator > class list;
//
//          Standard declaration:
//          <CODE>
//          list< TMvSmartPtr<IUnknown> > listpJUnk;
//          </CODE>
//
//          Declaration with our allocator:
//          <CODE>
//          list< TMvSmartPtr<IUnknown>, TMvSTLAlloc< TMvSmartPtr<IUnknown> > > listpJUnk;
//          </CODE>
//
//          Declaration  with our allocator and a defined block size of 8:
//          <CODE>
//          TMvSTLAlloc< TMvSmartPtr<IUnknown> > stlAllocpJUnk(8);
//
//          list< TMvSmartPtr<IUnknown>, TMvSTLAlloc< TMvSmartPtr<IUnknown> > > listpJUnk(stlAllocpJUnk);
//          </CODE>
//
// Examples:
//    Map: Template < class Key, class T, class Compare = less<Key>, class Allocator = allocator > class map;
//
//       Standard declaration:
//          <CODE>
//          map< int, TMvSmartPtr<IUnknown> > mappJUnk;
//          </CODE>
//
//       Declaration with our allocator:
//          <CODE>
//          map< int, TMvSmartPtr<IUnknown>, less<int>, TMvSTLAlloc< TMvSmartPtr<IUnknown> > > mappJUnk;
//          </CODE>
//
//       Declaration  with our allocator and a defined block size of 8:
//          <CODE>
//          TMvSTLAlloc< TMvSmartPtr<IUnknown> > stlAllocpJUnk(8);
//
//          map< int, TMvSmartPtr<IUnknown>, less<int>, TMvSTLAlloc< TMvSmartPtr<IUnknown> > > mappJUnk(stlAllocpJUnk);
//          </CODE>
//
///////////////////////////////////////////////////////////////////////////////
template <typename T> class TMvSTLAlloc 
{   
   class CMvMemBlock
   {
      CMvMemBlock *m_pPrev;   /* Previous node in the list */
      CMvMemBlock *m_pNext;   /* Next node in the list */     
      void        *m_pMem;    /* Pointer to memory block */     
      size_t       m_sizeAllocated; /* Size allocated. Keeping the size_t type to be conform to the stl */
      bool         m_bFreeMemory;   /* Block has to free the memory */

   public:

      /* Constructor - initialise the object's pointers */
      CMvMemBlock(void  *in_pMem,
                  size_t in_sizeAllocated,
                  bool   in_bFreeMemory):
         m_pPrev(NULL),
         m_pNext(NULL),
         m_pMem(in_pMem),
         m_sizeAllocated(in_sizeAllocated),
         m_bFreeMemory(in_bFreeMemory)
      {
         //g_ulMemBlockAllocate++;
      };

      ~CMvMemBlock()
      {
         //g_ulMemBlockRelease++;
         if(m_bFreeMemory)
            delete [] reinterpret_cast<byte*>(m_pMem);   
         
      };

      /* Return the previous node before this one */
      CMvMemBlock *Prev() const { return m_pPrev; };
      /* Return the next node after this one */
      CMvMemBlock *Next() const { return m_pNext; };
      /* Set the previous node before this one */
      void SetPrev(CMvMemBlock *p) { m_pPrev = p; };
      /* Set the next node after this one */
      void SetNext(CMvMemBlock *p) { m_pNext = p; };
      /* Get the pointer to the object for this node */
      void  *GetData() const { return m_pMem; };      
      size_t GetSize() const { return m_sizeAllocated; };
      void FreeMemory(bool in_bFree){ m_bFreeMemory = in_bFree; };
   };

   class CMvMemBlockCache
   {                     
      CMvMemBlock   *m_pMvMemListUsed;
      CMvMemBlock   *m_pMvMemListFree;

   public:
      const unsigned long m_kulPreAllocationCount;

   private:
#ifdef MV_DEBUG_STL_ALLOCATOR_MEMORY
      unsigned long m_ulMemoryAllocatedInBytes;
#endif // MV_DEBUG_STL_ALLOCATOR_MEMORY

   public:
      CMvMemBlockCache(const unsigned long in_kulPreAllocationCount):
         m_pMvMemListUsed(NULL),
         m_pMvMemListFree(NULL),
         m_kulPreAllocationCount(in_kulPreAllocationCount)
         {
#ifdef MV_DEBUG_STL_ALLOCATOR_MEMORY
            m_ulMemoryAllocatedInBytes = 0;
#endif // MV_DEBUG_STL_ALLOCATOR_MEMORY
         }

         ~CMvMemBlockCache()
         {
            if(m_pMvMemListFree)
            {
               CMvMemBlock *pBlockToDelete = NULL;
               CMvMemBlock *pBlockCurrent  = m_pMvMemListFree;          
               do
               {
                  pBlockToDelete = pBlockCurrent;
                  pBlockCurrent  = pBlockCurrent->Next();
                  delete pBlockToDelete;
               }            
               while(pBlockCurrent);
            }
            if(m_pMvMemListUsed)
            {
               CMvMemBlock *pBlockToDelete = NULL;
               CMvMemBlock *pBlockCurrent  = m_pMvMemListUsed;
               do
               {
                  pBlockToDelete = pBlockCurrent;
                  pBlockCurrent  = pBlockCurrent->Next();
                  pBlockToDelete->FreeMemory(false);
                  delete pBlockToDelete;
               }
               while(pBlockCurrent);
            }
				
          // ASSERT(m_pMvMemListUsed == NULL);
         }

         void AddToFreeList(CMvMemBlock *in_pBlock)
         {
            // Find last block in free list
            if(m_pMvMemListFree)
            {
               CMvMemBlock *pBlockCurrent = m_pMvMemListFree;          
               while(pBlockCurrent->Next() != NULL)
               {
                  pBlockCurrent = pBlockCurrent->Next();
               }

               // Insert after last block
               pBlockCurrent->SetNext(in_pBlock);
               in_pBlock->SetPrev(pBlockCurrent);
               in_pBlock->SetNext(NULL);
            }
            else
            {
               m_pMvMemListFree = in_pBlock;
               in_pBlock->SetPrev(NULL);
               in_pBlock->SetNext(NULL);
            }
         }

         void AddToUsedList(CMvMemBlock *in_pBlock)
         {
            if(m_pMvMemListUsed)
            {
               // Find last block
               CMvMemBlock *pBlockCurrent = m_pMvMemListUsed;          
               while(pBlockCurrent->Next() != NULL)
               {
                  pBlockCurrent = pBlockCurrent->Next();
               }

               // Insert after last block
               pBlockCurrent->SetNext(in_pBlock);
               in_pBlock->SetPrev(pBlockCurrent);
               in_pBlock->SetNext(NULL);
            }
            else
            {
               m_pMvMemListUsed = in_pBlock;
               in_pBlock->SetPrev(NULL);
               in_pBlock->SetNext(NULL);
            }
         }

         CMvMemBlock* GetMemBlock(size_t in_size)
         {
            CMvMemBlock *pBlock = NULL;

            if(m_pMvMemListFree)
            {
               CMvMemBlock *pBlockCurrent = m_pMvMemListFree;
               bool bFound = false;
               // Get first valid block
               do            
               {
                  if(pBlockCurrent->GetSize() == in_size)
                  {
                     bFound = true;
                  }
                  else
                  {
                     // Move to next
                     pBlockCurrent = pBlockCurrent->Next();
                  }               
               }
               while(!bFound && pBlockCurrent);

               if(bFound)
               {            
                  pBlock = pBlockCurrent;

                  // Remove from free list
                  // Alone
                  if( (pBlockCurrent->Prev() == NULL) &&
                     (pBlockCurrent->Next() == NULL) )
                  {                
                     m_pMvMemListFree = NULL;                  
                  }
                  // Head
                  else if(pBlockCurrent->Prev() == NULL)
                  {
                     (pBlockCurrent->Next())->SetPrev(NULL);
                     m_pMvMemListFree = pBlockCurrent->Next();                  
                  }
                  // Last
                  else if(pBlockCurrent->Next() == NULL)
                  {
                     (pBlockCurrent->Prev())->SetNext(NULL);                                  
                  }
                  // Middle
                  else
                  {
                     (pBlockCurrent->Next())->SetPrev(pBlockCurrent->Prev());
                     (pBlockCurrent->Prev())->SetNext(pBlockCurrent->Next());                  
                  }
               }
            }

            // Allocate new memory?
            if(pBlock == NULL)
            {
               // Preallocation
               byte        *pbMemory  = new byte[in_size * m_kulPreAllocationCount];                  
               CMvMemBlock *pNewBlock = NULL;

#ifdef MV_DEBUG_STL_ALLOCATOR_MEMORY
               m_ulMemoryAllocatedInBytes += (unsigned long)((in_size * m_kulPreAllocationCount));
#endif // MV_DEBUG_STL_ALLOCATOR_MEMORY

               for(unsigned long i = 0; i < m_kulPreAllocationCount; i++)
               {
                  if(i == 0)
                  {
                     // First block, it has to free the memory
                     pNewBlock = new CMvMemBlock(reinterpret_cast<void*>(pbMemory), in_size, true);

                     // Returned block is the first one created
                     pBlock = pNewBlock;                    
                  }
                  else
                  {
                     // Subsequent block, do not free memory and store into cache
                     pNewBlock = new CMvMemBlock(reinterpret_cast<void*>(pbMemory), in_size, false);
                     // Store to cache
                     AddToFreeList(pNewBlock);
                  }

                  // Move to next pre-allocation block                     
                  pbMemory += in_size;
               }            
            }

            if(pBlock)
            {
               // Store returned memory to used list
               AddToUsedList(pBlock);
            }

            return pBlock;
         };

         void FreeMemBlock(void *in_pMem)
         {
            bool bFound = false;
            CMvMemBlock *pBlockCurrent = NULL;
            if(m_pMvMemListUsed)
            {
               // Find last block
               pBlockCurrent = m_pMvMemListUsed;                        
               do
               {
                  if(pBlockCurrent->GetData() == in_pMem)
                  {
                     bFound = true;
                  }
                  else
                  {
                     pBlockCurrent = pBlockCurrent->Next();
                  }             
               }
               while(!bFound && pBlockCurrent);         
            }
            if(bFound)
            {
               // Alone
               if( (pBlockCurrent->Prev() == NULL) &&
                  (pBlockCurrent->Next() == NULL) )
               {                
                  m_pMvMemListUsed = NULL;                  
                  AddToFreeList(pBlockCurrent);
               }
               // Head
               else if(pBlockCurrent->Prev() == NULL)
               {
                  (pBlockCurrent->Next())->SetPrev(NULL);
                  m_pMvMemListUsed = pBlockCurrent->Next();                  
                  AddToFreeList(pBlockCurrent);
               }
               // Last
               else if(pBlockCurrent->Next() == NULL)
               {
                  (pBlockCurrent->Prev())->SetNext(NULL);                                  
                  AddToFreeList(pBlockCurrent);
               }
               // Middle
               else
               {
                  (pBlockCurrent->Next())->SetPrev(pBlockCurrent->Prev());
                  (pBlockCurrent->Prev())->SetNext(pBlockCurrent->Next());                  
                  AddToFreeList(pBlockCurrent);
               }
            }
            else
            {
               // Block was not allocated with this allocator. It must be the
               // first block created by the STL container, which was allocated by a 
               // proxy allocator on the stack.
               // Just free the memory. No block is associated with it anymore.
               if(in_pMem)
                  delete [] reinterpret_cast<byte*>(in_pMem);
            }
         }

#ifdef MV_DEBUG_STL_ALLOCATOR_MEMORY
         unsigned long GetMemoryAllocatedInBytes() { return m_ulMemoryAllocatedInBytes; };
#endif // MV_DEBUG_STL_ALLOCATOR_MEMORY
   };

public:
   // Public data for copy contrustor
   CMvMemBlockCache  m_mvMemBlockCache;

public:

   // Typedefs
   typedef size_t    size_type;
   typedef intptr_t difference_type;
   typedef T*        pointer;
   typedef const T*  const_pointer;
   typedef T&        reference;
   typedef const T&  const_reference;
   typedef T         value_type;

public:

   // Constructors
   TMvSTLAlloc() throw()
      :m_mvMemBlockCache(kulMvSTLAllocDefaultPreAllocationBlockCount) // Use default preallocation
   {
#ifdef MV_DEBUG_STL_ALLOCATOR_MEMORY
      m_ulAllocatedMemoryCount = 0;
#endif // MV_DEBUG_STL_ALLOCATOR_MEMORY
   }

   TMvSTLAlloc(unsigned long in_ulPreAllocationCount) throw()
      :m_mvMemBlockCache(in_ulPreAllocationCount)
   {
#ifdef MV_DEBUG_STL_ALLOCATOR_MEMORY
      m_ulAllocatedMemoryCount = 0;
#endif // MV_DEBUG_STL_ALLOCATOR_MEMORY
   }      

   TMvSTLAlloc( const TMvSTLAlloc& in_krefCopy) throw()
      :m_mvMemBlockCache(in_krefCopy.m_mvMemBlockCache.m_kulPreAllocationCount)
   {
#ifdef MV_DEBUG_STL_ALLOCATOR_MEMORY
      m_ulAllocatedMemoryCount = 0;
#endif // MV_DEBUG_STL_ALLOCATOR_MEMORY
   }

   template <typename U>
      TMvSTLAlloc( const TMvSTLAlloc<U>& in_krefCopy) throw()
      :m_mvMemBlockCache(in_krefCopy.m_mvMemBlockCache.m_kulPreAllocationCount)
   {
#ifdef MV_DEBUG_STL_ALLOCATOR_MEMORY
      m_ulAllocatedMemoryCount = 0;
#endif // MV_DEBUG_STL_ALLOCATOR_MEMORY
   }

   TMvSTLAlloc& operator=( const TMvSTLAlloc& )
   {
      return *this;
   }

   // Destructor
   ~TMvSTLAlloc() throw()
   {
#ifdef MV_DEBUG_STL_ALLOCATOR_MEMORY
      if (m_ulAllocatedMemoryCount != 0 )
      {
         char temp[128];
         sprintf(temp, "Allocator:; %u \n", m_ulAllocatedMemoryCount);
         OutputDebugString(temp);
      }
#endif // MV_DEBUG_STL_ALLOCATOR_MEMORY
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
      typedef TMvSTLAlloc<U> other;
   };

   // Allocate raw memory
   pointer allocate( size_type n, const void* = NULL )
   {       
      // Get memory allocated before and after...
#ifdef MV_DEBUG_STL_ALLOCATOR_MEMORY
      unsigned long ulAllocatedMemoryBefore = m_mvMemBlockCache.GetMemoryAllocatedInBytes();
#endif // MV_DEBUG_STL_ALLOCATOR_MEMORY
      pointer p = pointer(m_mvMemBlockCache.GetMemBlock(n * sizeof(T))->GetData());
      if( p == NULL )
         throw std::bad_alloc();
#ifdef MV_DEBUG_STL_ALLOCATOR_MEMORY
      unsigned long ulAllocatedMemoryAfter = m_mvMemBlockCache.GetMemoryAllocatedInBytes();
      if ( ulAllocatedMemoryAfter - ulAllocatedMemoryBefore > 0 )
      {
         m_ulAllocatedMemoryCount += ulAllocatedMemoryAfter - ulAllocatedMemoryBefore;
      }
#endif // MV_DEBUG_STL_ALLOCATOR_MEMORY
      return p;
   }

   // Free raw memory.
   // Note that C++ standard defines this function as
   // deallocate( pointer p, size_type). Because Visual C++ 6.0
   // compiler doesn't support template rebind, Dinkumware uses
   // void* hack.
   void deallocate( void* p, size_type )
   {
      m_mvMemBlockCache.FreeMemBlock(p);
   }

   // Non-standard Dinkumware hack for Visual C++ 6.0 compiler.
   // VC 6 doesn't support template rebind.
   char* _Charalloc( size_type nBytes )
   {
#ifdef MV_DEBUG_STL_ALLOCATOR_MEMORY
      unsigned long ulAllocatedMemoryBefore = m_mvMemBlockCache.GetMemoryAllocatedInBytes();
#endif // MV_DEBUG_STL_ALLOCATOR_MEMORY
      char* p = reinterpret_cast<char*>( m_mvMemBlockCache.GetMemBlock(nBytes)->GetData() );
      if( p == NULL )
         throw std::bad_alloc();
#ifdef MV_DEBUG_STL_ALLOCATOR_MEMORY
      unsigned long ulAllocatedMemoryAfter = m_mvMemBlockCache.GetMemoryAllocatedInBytes();
      if ( ulAllocatedMemoryAfter - ulAllocatedMemoryBefore > 0 )
      {
         m_ulAllocatedMemoryCount += (ulAllocatedMemoryAfter - ulAllocatedMemoryBefore);
      }
#endif // MV_DEBUG_STL_ALLOCATOR_MEMORY
      return p;
   }

private:

   // No data

protected:
#ifdef MV_DEBUG_STL_ALLOCATOR_MEMORY
   unsigned long m_ulAllocatedMemoryCount;  
#endif // MV_DEBUG_STL_ALLOCATOR_MEMORY
};

// Comparison
template <typename T1, typename T2>
bool operator==( const TMvSTLAlloc<T1>&,
                const TMvSTLAlloc<T2>& ) throw()
{
   return true;
}

template <typename T1, typename T2>
bool operator!=( const TMvSTLAlloc<T1>&,
                const TMvSTLAlloc<T2>& ) throw()
{
   return false;
}

#ifndef LINUX_PLATFORM
   #pragma warning(pop)
   #pragma warning(pop)

   #pragma pop_macro("max")
#endif // !LINUX_PLATFORM

#endif // MV_STL_ALLOC_H
