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

//Author:   Anthony Malizia
//Date:     February 2004

#pragma once

#include <Windows.h>
#include <cstddef>

// Functor used to delete scalar objects.
template<class T>
class TMvDeleteScalar
{
public:
   // Operator ()
   void operator()(T* in_pData) const { delete in_pData; }
};

// Functor used to delete an array of objects.
template<class T>
class TMvDeleteArray
{
public:
   // Operator ()
   void operator()(T* in_pData) const { delete [] in_pData; }
};

//
// Summary:
//    A smart pointer that manages the lifetime of an object allocated on the heap by counting the 
//    number of references that exists to that object.
// Example:
// <CODE>
// class CSomething
// {
// public:
//    void Foo() {}
//    virtual ~CSomething() {}
// };
//
// class CDerivedThing : public CSomething
// {
// };
//
// void f()
// { 
//    TMvRefCountPtr<CSomething> spoSomething2;
//    { 
//       TMvRefCountPtr<CSomething> spoSomething(new CSomething);
//       spoSomething2 = spoSomething;
//    }
//    spoSomething2->Foo();
// }
// </CODE>
// When spoSomething2 goes out of scope, the number of references to the object that spoSomething2 
// points to (and that spoSomething pointed to) will go to zero, and the object will be deleted.
// This smart pointer can be used safely in STL containers such as std::vector\<TMvRefCountPtr\<CSomething> >.
//
// Example:
// You can use TMvRefCountPtr with arrays by changing the second template parameter to TMvDeleteArray.
// <CODE>
// TMvRefCountPtr<CSomething, TMvDeleteArray<CSomething> > spaoSomethings(new CSomething[10]);   
// </CODE>
// When spaoSomethings is no longer referenced, operator delete [] will be
// called to free the array and call appropriate destructors.
//
template<class T, class DEL = TMvDeleteScalar<T> >
class TMvRefCountPtr
{
public:
   //
   // Summary
   //    Creates a smart pointer that points to null.
   // Example:
   //    <CODE>
   //    TMvRefCountPtr<CSomething> spoSomething;
   //    </CODE>
   TMvRefCountPtr() : m_plCount(NULL), m_pData(NULL) 
   {
   }

   //
   // Summary
   //    Creates a smart pointer that points to the object that in_pData points to. The reference 
   //    count to that object becomes one.
   // Example:
   //    <CODE>
   //    TMvRefCountPtr<CSomething> spoSomething(new CSomething);
   //    </CODE>
   explicit TMvRefCountPtr(T* in_pData) : m_plCount(new long(1)), 
      m_pData(in_pData) 
   {
   }

   //
   // Summary
   //    Creates a smart pointer that points to the same object that another smart pointer points 
   //    to.  The reference count to that object is incremented by one.
   // Example:
   //    <CODE>
   //    TMvRefCountPtr<CSomething> spoSomething1(new CSomething);
   //    TMvRefCountPtr<CSomething> spoSomething2(spoSomething1);
   //    </CODE>
   TMvRefCountPtr(const TMvRefCountPtr& in_rkspOther) : 
      m_plCount(in_rkspOther.Inc()), m_pData(in_rkspOther.GetPtr()) 
   {
   }

   //
   // Summary
   //    Creates a smart pointer that points to the same object that another smart pointer points 
   //    to, but at different levels in a class hierarchy.  The reference count to that object is 
   //    incremented by one.
   // Example:
   //    <CODE>
   //    TMvRefCountPtr<CDerivedThing> spoDerivedThing(new CDerivedThing);
   //    TMvRefCountPtr<CSomething> spoSomething(spoDerivedThing); 
   //    </CODE>
   //    This is legal since CSomething is a base class of CDerivedThing, and CSomething has a 
   //    virtual destructor.
   template<class O>
   TMvRefCountPtr(const TMvRefCountPtr<O, DEL>& in_rkspOther) : 
      m_plCount(in_rkspOther.Inc()), m_pData(in_rkspOther.GetPtr()) 
   {
   }

   // Destructor of a smart pointer.  The reference count to its object is
   // decremented by one, if the count goes to zero, the object is deleted.
   ~TMvRefCountPtr() 
   { 
      Dec(); 
   }

   //
   // Summary:
   //    Allows a smart pointer to point to the same object that another smart pointer points to, 
   //    while making sure that the reference count of the object it originally pointed to is 
   //    decremented by one and the reference count to the new object it points to is incremented 
   //    by one.  If the reference count to the object it originally pointed to goes to zero, that
   //    object is deleted.
   // Example:
   //    <CODE>
   //    TMvRefCountPtr<CSomething> spoSomething1(new CSomething); //first object
   //    TMvRefCountPtr<CSomething> spoSomething2(new CSomething); //second object
   //    spoSomething1 = spoSomething2;   
   //    </CODE>
   //    Now spoSomething1 points to the second object, and the first object is deleted because no 
   //    one refers to it any longer.
   TMvRefCountPtr& operator=(const TMvRefCountPtr& in_rkspOther) 
   { 
      if (this == &in_rkspOther) 
         return *this; 
      Dec(); 
      m_plCount = in_rkspOther.Inc(); 
      m_pData = in_rkspOther.GetPtr(); 
      return *this; 
   }

   //
   // Summary:
   //    Allows a smart pointer to point to the same object that another smart pointer points to, 
   //    but at different levels in a class hierarchy.  The reference counts to the objects in 
   //    question are adjusted appropriately.
   //Example:
   //    <CODE>
   //    TMvRefCountPtr<CSomething> spoSomething(new CSomething);
   //    TMvRefCountPtr<CDerivedThing> spoDerivedThing(new CDerivedThing);
   //    spoSomething = spoDerivedThing;
   //    </CODE>
   //    Now spoSomething now points to the object that is actually of type CDerivedThing.  The 
   //    object if type CSomething that it pointed to is deleted because there are no longer any 
   //    references to it.
   //
   template<class O>
   TMvRefCountPtr& operator=(const TMvRefCountPtr<O, DEL>& in_rkspOther) 
   { 
      Dec(); 
      m_plCount = in_rkspOther.Inc(); 
      m_pData = in_rkspOther.GetPtr(); 
      return *this; 
   }

   //
   // Summary:
   //    Allows to test for null.
   // Example:
   //    <CODE>
   //    TMvRefCountPtr<CSomething> spoSomething;
   //    if (!spoSomething)
   //    {
   //       //this part of code would always be reached with this example
   //    }
   //    </CODE>
   //
   bool operator !() const 
   { 
      return (m_pData == NULL); 
   }

   //
   // Summary:
   //    Allows to access the object that the smart pointer points to.
   // Example:
   //    <CODE>
   //    TMvRefCountPtr<CSomething> spoSomething(new CSomething);
   //    (*spoSomething).Foo();
   //    </CODE>
   //
   T& operator*() const 
   { 
      return *m_pData; 
   }

   //
   // Summary:
   //    Allows to access the object that the smart pointer points to.
   // Example:
   //    <CODE>
   //    TMvRefCountPtr<CSomething> spoSomething(new CSomething);
   //    spoSomething->Foo();
   //    </CODE>
   //
   T* operator->() const 
   { 
      return m_pData; 
   }

   //
   // Summary:
   //    Allows to access the object that the smart pointer points to.
   // Example:
   //    <CODE>
   //    TMvRefCountPtr<CSomething, TMvDeleteArray<CSomething> > spaoSomethings(new CSomething[10]);   
   //    spaoSomethings[0] = oOtherThing;
   //    </CODE>
   T& operator[](ptrdiff_t in_iIndex) const
   {
      return m_pData[in_iIndex];
   }

   //
   // Summary:
   //    Returns a pointer to the object that the smart pointer points to.  This should be avoided 
   //    because someone could keep a reference to the object, but the smart pointer's reference 
   //    count would not reflect this fact.
   // Example:
   //    <CODE>
   //    void f(CSomething* in_poSomething) 
   //    { 
   //       if (in_poSomething) 
   //          in_poSomething->Foo(); 
   //    }
   //
   //    void g()
   //    {
   //       TMvRefCountPtr<CSomething> spoSomething(new CSomething);
   //       f(spoSomething.GetPtr());
   //    }
   //    </CODE>
   //
   T* GetPtr() const 
   { 
      return m_pData; 
   }

   //
   // Summary:
   //    Returns the reference count to the object that the smart pointer points to.  This could be 
   //    useful for debugging purposes.
   //
   long GetCount() const 
   { 
      if (m_plCount) 
         return *m_plCount; 
      return 0; 
   }

private:
   volatile long* Inc() const 
   { 
      if (m_plCount) 
         InterlockedIncrement(m_plCount);
      return m_plCount; 
   }

   void Dec() 
   { 
      if (m_plCount && InterlockedDecrement(m_plCount) == 0) 
      { 
         m_ofnDelete(m_pData);  //call functor to delete the object
         m_pData = NULL; 
         delete m_plCount; 
         m_plCount = NULL; 
      } 
   }

   const DEL m_ofnDelete;        //instance of specified delete functor type
   mutable volatile long* m_plCount;
   T* m_pData;

   //template<class O>
   friend class TMvRefCountPtr;  //<O, DEL>
};

//Allows to compare two smart pointers to see if they both point to the same
//object.
//Example:
//TMvRefCountPtr<CDerivedThing> spoDerivedThing(new CDerivedThing);
//TMvRefCountPtr<CSomething> spoSomething(spoDerivedThing);
//if (spoDerivedThing == spoSomething)
//{
//   //this part of code would always be reached with this example
//}
template<class L, class R, class DEL>
bool operator==(const TMvRefCountPtr<L, DEL>& in_rkspLeft, 
   const TMvRefCountPtr<R, DEL>& in_rkspRight)
{
   return (in_rkspLeft.GetPtr() == in_rkspRight.GetPtr());
}

//Allows to compare two smart pointers to see if they point to different
//objects.
//Example:
//TMvRefCountPtr<CDerivedThing> spoDerivedThing(new CDerivedThing);
//TMvRefCountPtr<CSomething> spoSomething(new CDerivedThing);
//if (spoDerivedThing != spoSomething)
//{
//   //this part of code would always be reached with this example
//}
template<class L, class R, class DEL>
bool operator!=(const TMvRefCountPtr<L, DEL>& in_rkspLeft, 
   const TMvRefCountPtr<R, DEL>& in_rkspRight)
{
   return (in_rkspLeft.GetPtr() != in_rkspRight.GetPtr());
}
