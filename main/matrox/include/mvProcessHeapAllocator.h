/*

(c) Copyright Matrox Electronic Systems Ltd., 2003. All rights reserved. 

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

#pragma once

#include <new>
#include <Windows.h>

#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max

#include <limits>


class CMvWin32ProcessHeap
{
public:
   CMvWin32ProcessHeap() : m_hHeap(::GetProcessHeap()) {}

   void* Allocate(size_t in_sizeBytes) { return ::HeapAlloc(m_hHeap, 0, in_sizeBytes); }
   void Free(void* in_p) { ::HeapFree(m_hHeap, 0, in_p); }

private:
   HANDLE m_hHeap;
};

template<class T> class TMvProcessHeapAllocator;

// specialize for void:
template<> class TMvProcessHeapAllocator<void> 
{
public:
   typedef void*        pointer;
   typedef const void*  const_pointer;
   // reference to void members are impossible.
   typedef void         value_type;
   template<class U> struct rebind { typedef TMvProcessHeapAllocator<U> other; };
};

template<class T> class TMvProcessHeapAllocator 
{
public:
   typedef size_t    size_type;
   typedef ptrdiff_t difference_type;
   typedef T*        pointer;
   typedef const T*  const_pointer;
   typedef T&        reference;
   typedef const T&  const_reference;
   typedef T         value_type;
   template <class U> struct rebind { typedef TMvProcessHeapAllocator<U> other; };

   TMvProcessHeapAllocator() throw() {}
   TMvProcessHeapAllocator(const TMvProcessHeapAllocator&) throw() {}
   template <class U> TMvProcessHeapAllocator(const TMvProcessHeapAllocator<U>&) throw() {}
   ~TMvProcessHeapAllocator() throw() {}

   pointer address(reference x) const { return &x; }
   const_pointer address(const_reference x) const { return &x; }

   pointer allocate(size_type n) { return allocate(n, 0); }
   pointer allocate(size_type n, TMvProcessHeapAllocator<void>::const_pointer) { return reinterpret_cast<pointer>(m_oWin32Heap.Allocate(n * sizeof(T))); }
   void deallocate(pointer p, size_type) { m_oWin32Heap.Free(p); }

   size_type max_size() const throw() { return (std::numeric_limits<size_type>::max() / sizeof(T)); }

   void construct(pointer p, const T& val) { new(static_cast<void*>(p)) T(val); }
   void destroy(pointer p) { p->~T(); }

private:
   CMvWin32ProcessHeap m_oWin32Heap;
};


// Returns true if storage allocated by allocator a1 can be deallocated by allocator a2 and vice-versa.
// If the allocator should be used with STL containers, the above is required. Thus, this function should always return true.
template <class T1, class T2>
bool operator==(const TMvProcessHeapAllocator<T1>&, const TMvProcessHeapAllocator<T2>&) throw()
{
   return true;
}

// Returns true if storage allocated by allocator a1 cannot be deallocated by allocator a2 and vice-versa.
// If the allocator should be used with STL containers, the opposite of the above is required. Thus, this function should always return false.
template <class T1, class T2>
bool operator!=(const TMvProcessHeapAllocator<T1>&, const TMvProcessHeapAllocator<T2>&) throw()
{
   return false;
}

#pragma pop_macro("min")
#pragma pop_macro("max")
