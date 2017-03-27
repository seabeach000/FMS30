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

#ifndef __AFX_H__
#ifndef __WXLIST__
//
// Description
//    A POSITION represents (in some fashion that's opaque) a cursor
//    on the list that can be set to identify any element.  NULL is
//    a valid value and several operations regard NULL as the position
//    "one step off the end of the list".  (In an n element list there
//    are n+1 places to insert and NULL is that "n+1-th" value).
//    The POSITION of an element in the list is only invalidated if
//    that element is deleted.  Move operations may mean that what
//    was a valid POSITION in one list is now a valid POSITION in
//    a different list.
//
//    Some operations which at first sight are illegal are allowed as
//    harmless no-ops.  For instance RemoveHead is legal on an empty
//    list and it returns NULL.  This allows an atomic way to test if
//    there is an element there, and if so, get it.  The two operations
//    AddTail and RemoveHead thus implement a MONITOR (See Hoare's paper).
//
//    Single element operations return POSITIONs, non-NULL means it worked.
//    whole list operations return a BOOL.  TRUE means it all worked.
//
//    This definition is the same as the POSITION type for MFCs, so we must
//    avoid defining it twice.
//
struct __POSITION { int unused; };
typedef __POSITION* POSITION;
#endif
#endif

#include "mvBaseCOM.h"
#include "mvThread.h"

#ifndef ASSERT
   #include <crtDbg.h>
   #include <assert.h> // this defines the lower case assert
   #define ASSERT _ASSERTE
#endif

const int DEFAULTCACHESIZE = 10;    /* Default node object cache size */

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    The CMvBaseList class implements an abstract list.
// Description:
//    Each node knows a pointer to it's adjacent nodes and also a pointer to the object that it 
//    looks after. All of these pointers can be retrieved or set through member functions.
// Remarks:
//    - It takes the code of CBaseList implemented in the DirectShow.
//    - CMvBaseList is not a thread safe list.
//    - The application should use CMvGenericList instead in order to support multiple threading.
//    - Making these classes inherit from CMvBaseList does nothing functionally but it allows us to 
//      check there are no memory leaks in debug builds. 
//
//////////////////////////////////////////////////////////////////////////
class CMvBaseList 
{

public:

   //
   // Summary:
   //    Element of the list
   //
   class CMvNode
   {
      CMvNode * m_pPrev;    // Previous node in the list.
      CMvNode * m_pNext;    // Next node in the list.
      void    * m_pObject;  // Pointer to the object.

    public:

      // Initialize the object's pointers
      CMvNode()
      {
      };


      /* Return the previous node before this one */
      CMvNode *Prev() const { return m_pPrev; };


      /* Return the next node after this one */
      CMvNode *Next() const { return m_pNext; };


      /* Set the previous node before this one */
      void SetPrev(CMvNode *p) { m_pPrev = p; };


      /* Set the next node after this one */
      void SetNext(CMvNode *p) { m_pNext = p; };


      /* Get the pointer to the object for this node */
      void *GetData() const { return m_pObject; };


      /* Set the pointer to the object for this node */
      void SetData(void *p) { m_pObject = p; };
   };

   //
   // Summary:
   //   To prevent reallocating nodes.
   //
   class CMvNodeCache
   {
   public:

      // constructor
      CMvNodeCache(INT iCacheSize)
         : m_iCacheSize(iCacheSize)
         , m_iUsed(0)
         , m_pHead(NULL)
      {};

      // Destructor
      ~CMvNodeCache()
      {
         CMvNode *pNode = m_pHead;
         while (pNode)
         {
            CMvNode *pCurrent = pNode;
            pNode = pNode->Next();
            delete pCurrent;
         }
      };
      
      // Add an element to the cache
      void AddToCache(CMvNode *pNode)
      {
         if (m_iUsed < m_iCacheSize)
         {
            pNode->SetNext(m_pHead);
            m_pHead = pNode;
            m_iUsed++;
         }
         else
         {
            delete pNode;
         }
      };
      
      // Get an element from the cache
      CMvNode *RemoveFromCache()
      {
         CMvNode *pNode = m_pHead;
         
         if (pNode != NULL)
         {
            m_pHead = pNode->Next();
            m_iUsed--;
            ASSERT(m_iUsed >= 0);
         }
         else
         {
            ASSERT(m_iUsed == 0);
         }
         
         return pNode;
        };

   private:
      INT m_iCacheSize; // 
      INT m_iUsed;      // 
      CMvNode *m_pHead; // 
   };

protected:

    CMvNode * m_pFirst;    // Pointer to first node in the list.
    CMvNode * m_pLast;     // Pointer to the last node in the list.
    int       m_Count;     // Number of nodes currently in the list.

private:

    CMvNodeCache m_Cache;  // Cache of unused node pointers.

private:

   //
   // Summary:
   //    Default copy constructor and assignment operator for all list classes.
   // Description:
   //    They are in the private class declaration section so that anybody trying to pass a list
   //    object by value will generate a compile time error of "cannot access the private member 
   //    function". If these were not here then the compiler will create default constructors
   //    and assignment operators which when executed first take a copy of all member variables and 
   //    then during destruction delete them all. This must not be done for any heap allocated data.
   CMvBaseList(const CMvBaseList &refList);

   //
   // Summary:
   //    Default copy constructor and assignment operator for all list classes.
   // Description:
   //    They are in the private class declaration section so that anybody trying to pass a list
   //    object by value will generate a compile time error of "cannot access the private member 
   //    function". If these were not here then the compiler will create default constructors
   //    and assignment operators which when executed first take a copy of all member variables and 
   //    then during destruction delete them all. This must not be done for any heap allocated data.
   CMvBaseList &operator=(const CMvBaseList &refList);

public:

   //
   // Summary:
   //    Constructor with descriptive list name for debugging.
   CMvBaseList
      (
      LPCWSTR pName,
      INT iItems
      );

   //
   // Summary:
   //    Constructor with descriptive list name for debugging.
   CMvBaseList
      (
      LPCWSTR pName
      );

   //
   // Summary:
   //    Destructor.
   ~CMvBaseList();

   //
   // Summary:
   //    Remove all the nodes from the list.
   void RemoveAll();

   //
   // Summary:
   //    Retrieves the position of the first item of the list.
   POSITION GetHeadPositionI() const;

   //
   // Summary:
   //    Retrieves the position of the last item of the list.
   POSITION GetTailPositionI() const;

   //
   // Summary:
   //    Retrieves the number of items in the list.
   int GetCountI() const;

protected:
   //
   // Summary:
   //    Return the pointer to the object at rp.
   // Description:
   //    - Update rp to the next node in *this but make it NULL if it was at the end of *this.
   //    - This is a wart retained for backwards compatibility.
   //    - GetPrev is not implemented.
   //    - Use Next, Prev and Get separately.
   //
   void *GetNextI(POSITION& rp) const;


   //
   // Summary:
   //    Return a pointer to the object at p.
   // Remarks:
   //    - Asking for the object at NULL will return NULL harmlessly.
   //
   void *GetI(POSITION p) const;

public:
   //
   // Summary:
   //    Retrieves the next position in the list.
   // Description:
   // Return value:
   //    - Return the next / prev position in *this.
   //    - Return NULL when going past the end/start.
   // Remarks:
   //    - Next(NULL) is same as GetHeadPosition().
   //    - Prev(NULL) is same as GetTailPosition().
   //    - An n element list therefore behaves like a n+1 element cycle with NULL at the start/end.
   //
   //    !!WARNING!! - This handling of NULL is DIFFERENT from GetNext.
   //
   //    Some reasons are:
   //    1. For a list of n items there are n+1 positions to insert
   //       These are conveniently encoded as the n POSITIONs and NULL.
   //    2. If you are keeping a list sorted (fairly common) and you
   //       search forward for an element to insert before and don't
   //       find it you finish up with NULL as the element before which
   //       to insert.  You then want that NULL to be a valid POSITION
   //       so that you can insert before it and you want that insertion
   //       point to mean the (n+1)-th one that doesn't have a POSITION.
   //       (symmetrically if you are working backwards through the list).
   //    3. It simplifies the algebra which the methods generate.
   //       e.g. AddBefore(p,x) is identical to AddAfter(Prev(p),x)
   //       in ALL cases.  All the other arguments probably are reflections
   //       of the algebraic point.
   //
   POSITION Next(POSITION pos) const
   {
      if (pos == NULL)
      {
         return (POSITION) m_pFirst;
      }

      CMvNode *pn = (CMvNode *) pos;

      return (POSITION) pn->Next();
   }

   //
   // Summary:
   //    Retrieves the previous position in the list.
   // See:
   //   Next
   //
   POSITION Prev(POSITION pos) const
   {
      if (pos == NULL)
      {
         return (POSITION) m_pLast;
      }

      CMvNode *pn = (CMvNode *) pos;

      return (POSITION) pn->Prev();
    }


protected:
   //
   // Summary:
   //    Return the first position in *this which holds the given pointer.
   // Remarks:
   //    Return NULL if the pointer was not not found.
   //
   POSITION FindI( void * pObj) const;

    // ??? Should there be (or even should there be only)
    // ??? POSITION FindNextAfter(void * pObj, POSITION p)
    // ??? And of course FindPrevBefore too.
    // ??? List.Find(&Obj) then becomes List.FindNextAfter(&Obj, NULL)


   //
   // Summary:
   //    Remove the first node in *this (deletes the pointer to its object from the list, does not 
   //    free the object itself).
   // Return value:
   //    - Return the pointer to its object.
   // Remarks:
   //    - If *this was already empty it will harmlessly return NULL.
   //
   void *RemoveHeadI();

   //
   // Summary:
   //    Remove the last node in *this (deletes the pointer to its object from the list, does not 
   //    free the object itself).
   // Return value:
   //    - Return the pointer to its object.
   // Remarks:
   //    - If *this was already empty it will harmlessly return NULL.
   //
   void *RemoveTailI();


   //
   // Summary:
   //    Remove the node identified by p from the list (deletes the pointer to its object from the 
   //    list, does not free the object itself).
   // Return value:
   //    - Return the pointer to the object removed.
   // Remarks:
   //    - Asking to Remove the object at NULL will harmlessly return NULL.
   //
   void *RemoveI(POSITION p);

   //
   // Summary:
   //    Add single object *pObj to become a new last element of the list.
   // Return value:
   //    - Return the new tail position, NULL if it fails.
   // Remarks:
   //    - If you are adding a COM objects, you might want AddRef it first.  Other existing 
   //      POSITIONs in *this are still valid
   //
   POSITION AddTailI(void * pObj);

public:

   //
   // Summary:
   //    Appends another list to the end of this list. 
   // Description:
   //    Add all the elements in *pList to the tail of *this. This duplicates all the nodes 
   //    in *pList (i.e. duplicates all its pointers to objects).  It does not duplicate the objects.
   // Return value:
   //    - Return TRUE if it all worked, FALSE if it didn't.
   // Remarks:
   //    - If you are adding a list of pointers to a COM object into the list it's a good idea to 
   //      AddRef them all  it when you AddTail it.
   //    - If the method fails some elements may have been added.
   //    - Existing POSITIONs in *this are still valid
   //    - If you actually want to MOVE the elements, use MoveToTail instead.
   //
   BOOL AddTail(CMvBaseList *pList);


   //
   // Summary:
   //    Add single object to become a new first element of the list.
   // Description:
   //    Add all the elements in *pList to the tail of *this. This duplicates all the nodes 
   //    in *pList (i.e. duplicates all its pointers to objects).  It does not duplicate the objects.
   // Return value:
   //    - Return the new head position, NULL if it fails.
   // Remarks:
   //    - Existing POSITIONs in *this are still valid
   //    - Mirror image of AddHead
   //
   protected:
   POSITION AddHeadI(void * pObj);
   public:

   //
   // Summary:
   //    Inserts another list at the front of this list.
   // Description:
   //    Add all the elements in *pList to the head of *this.
   // Return value:
   //    - Return TRUE if it all worked, FALSE if it didn't.
   // Remarks:
   //    - Same warnings apply as for AddTail.
   //    - If it fails some of the objects may have been added.
   //    - If you actually want to MOVE the elements, use MoveToHead instead.
   //
   BOOL AddHead(CMvBaseList *pList);


   //
   // Summary:
   //    Add the object *pObj to *this after position p in *this.
   // Description:
   //    AddAfter(NULL,x) adds x to the start - equivalent to AddHead
   // Return value:
   //    - Return the position of the object added, NULL if it failed.
   // Remarks:
   //    - Existing POSITIONs in *this are undisturbed, including p.
   //    - Mirror image of AddAfter
   //
   protected:
   POSITION AddAfterI(POSITION p, void * pObj);
   public:

   //
   // Summary:
   //    Inserts a list after the specified position.
   // Description:
   //    Add the list *pList to *this after position p in *this.  AddAfter(NULL,x) adds x to the 
   //    start - equivalent to AddHead
   // Return value:
   //    - Return TRUE if it all worked, FALSE if it didn't.
   // Remarks:
   //    - If it fails, some of the objects may be added
   //    - Existing POSITIONs in *this are undisturbed, including p.
   //    - AddAfter(p,x) is equivalent to AddBefore(Next(p),x) even in cases where p is NULL or 
   //      Next(p) is NULL.  Similarly for mirror images etc.  This may make it easier to argue 
   //      about programs.
   //
   BOOL AddAfter(POSITION p, CMvBaseList *pList);


   //
   // Summary:
   //    Add the object *pObj to this-List after position p in *this.
   // Description:
   //    AddBefore(NULL,x) adds x to the end - equivalent to AddTail
   // Return value:
   //    - Return the position of the new object, NULL if it fails
   // Remarks:
   //    - Existing POSITIONs in *this are undisturbed, including p.
   //    - Mirror image of AddBefore
   //
   protected:
   POSITION AddBeforeI(POSITION p, void * pObj);
   public:

   //
   // Summary:
   //    Inserts a list before the specified position. 
   // Description:
   //    Add the list *pList to *this before position p in *this. AddAfter(NULL,x) adds x to the
   //    start - equivalent to AddHead
   // Return value:
   //    - Return TRUE if it all worked, FALSE if it didn't.
   // Remarks:
   //    - If it fails, some of the objects may be added
   //    - Existing POSITIONs in *this are undisturbed, including p.
   //    - AddAfter(p,x) is equivalent to AddBefore(Next(p),x) even in cases where p is NULL or 
   //      Next(p) is NULL.  Similarly for mirror images etc.  This may make it easier to argue 
   //      about programs.
   //
   BOOL AddBefore(POSITION p, CMvBaseList *pList);

   //
   // Summary:
   //    Splits the list and appends the head portion to the tail of another list.
   // Description:
   //    The following operations do not copy any elements.
   //    They move existing blocks of elements around by switching pointers.
   //    They are fairly efficient for long lists as for short lists.
   //    (Alas, the Count slows things down).
   //
   //    They split the list into two parts.
   //    One part remains as the original list, the other part
   //    is appended to the second list.  There are eight possible
   //    variations:
   //    Split the list {after/before} a given element
   //    keep the {head/tail} portion in the original list
   //    append the rest to the {head/tail} of the new list.
   //
   //    Since After is strictly equivalent to Before Next
   //    we are not in serious need of the Before/After variants.
   //    That leaves only four.
   //
   //    If you are processing a list left to right and dumping
   //    the bits that you have processed into another list as
   //    you go, the Tail/Tail variant gives the most natural result.
   //    If you are processing in reverse order, Head/Head is best.
   //
   //    By using NULL positions and empty lists judiciously either
   //    of the other two can be built up in two operations.
   //
   //    The definition of NULL (see Next/Prev etc) means that
   //    degenerate cases include
   //       "move all elements to new list"
   //       "Split a list into two lists"
   //       "Concatenate two lists"
   //       (and quite a few no-ops)
   //
   //    !!WARNING!! The type checking won't buy you much if you get list
   //    positions muddled up - e.g. use a POSITION that's in a different
   //    list and see what a mess you get!
   //
   //    Split *this after position p in *this. Retain as *this the tail portion of the original *this.
   //    Add the head portion to the tail end of *pList
   // Return value:
   //    - Return TRUE if it all worked, FALSE if it didn't.
   // Example:
   //    <CODE>foo->MoveToTail(foo->GetHeadPosition(), bar);</CODE>
   //       - Moves one element from the head of foo to the tail of bar
   //    <CODE>foo->MoveToTail(NULL, bar);</CODE>
   //       - Is a no-op, returns NULL
   //    <CODE>foo->MoveToTail(foo->GetTailPosition, bar);</CODE>
   //       - Concatenates foo onto the end of bar and empties foo.
   // Remarks:
   //    - A better except excessively long name might be
   //      MoveElementsFromHeadThroughPositionToOtherTail
   //
   BOOL MoveToTail(POSITION pos, CMvBaseList *pList);


   //
   // Summary:
   //    Splits the list and inserts the tail portion at the head of another list.
   // Description:
   //    Split *this before position p in *this. Retain in *this the head portion of the original 
   //    *this. Add the tail portion to the start (i.e. head) of *pList.
   // Examples:
   //    <CODE>foo->MoveToHead(foo->GetTailPosition(), bar);</CODE>
   //       - Moves one element from the tail of foo to the head of bar
   //    <CODE>foo->MoveToHead(NULL, bar);</CODE>
   //       - Is a no-op, returns NULL
   //    <CODE>foo->MoveToHead(foo->GetHeadPosition, bar);</CODE>
   //       - Concatenates foo onto the start of bar and empties foo.
   // Remarks:
   //    - Mirror image.
   //
   BOOL MoveToHead(POSITION pos, CMvBaseList *pList);

   //
   // Summary:
   //    Reverses the order of the list. 
   //
   void Reverse();

   //
   // Summary:
   //    Set cursor to the position of each element of list in turn.
   //
   #define TRAVERSELIST(list, cursor)        \
   for ( cursor = (list).GetHeadPosition()   \
      ; cursor!=NULL                         \
      ; cursor = (list).Next(cursor)         \
      )


   //
   // Summary:
   //    set cursor to the position of each element of list in turn in reverse order
   //
   #define REVERSETRAVERSELIST(list, cursor) \
   for ( cursor = (list).GetTailPosition()   \
      ; cursor!=NULL                         \
      ; cursor = (list).Prev(cursor)         \
      )
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    The CMvGenericList class is a template class, which derives from CMvBaseList. 
// Description:
//    The CMvGenericList class uses critical section in each function so that one thread can
//    access it at a time, and it has a simpler API than the CMvBaseList class.
//
//////////////////////////////////////////////////////////////////////////
template<class OBJECT> class CMvGenericList : public CMvBaseList
{
public:
   //
   // Summary:
   //    Constructor with the list name for debugging, and the max number of the cash nodes.
   //
   CMvGenericList(LPCWSTR pName, INT iItems)
      : CMvBaseList(pName, iItems)
   {
      m_pCriticalSection=new CMvCriticalSection();

   };

   //
   // Summary:
   //    Constructor with the list name for debugging. The max number of the cash nodes is set to 
   //    the default value; 10.
   //
   CMvGenericList(LPCWSTR pName)
      : CMvBaseList(pName)
   {
      m_pCriticalSection=new CMvCriticalSection();
   };

   //
   // Summary:
   //    Destructor.
   //
	~CMvGenericList()
	{
		if(m_pCriticalSection)
			delete m_pCriticalSection;
	};

   //
   // Summary:
   //    Retrieves the position of the first item in the list.
   //
   POSITION GetHeadPosition() const
	{ 
	   CMvAutoLock lock(m_pCriticalSection);
		return (POSITION)m_pFirst; 
	}

   //
   // Summary:
   //    Retrieves the position of the last item of the list.
   //
   POSITION GetTailPosition() const 
	{ 	
		CMvAutoLock lock(m_pCriticalSection);
		return (POSITION)m_pLast; 
	}

   //
   // Summary:
   //    Retrieves the number of items in the list.
   //
   int GetCount() const 
	{ 
		CMvAutoLock lock(m_pCriticalSection);
		return m_Count; 
	}

   //
   // Summary:
   //    Retrieves the item at the specified position, and advances the position.
   //
   OBJECT *GetNext(POSITION& rp) const 
	{ 
		CMvAutoLock lock(m_pCriticalSection);
		return (OBJECT *) GetNextI(rp); 
	}

   //
   // Summary:
   //    Retrieves the item at the specified position, and then sets rp to the POSITION value 
   //    of the previous entry in the list.
   //
	OBJECT *GetPrev(POSITION& rp) const 
	{ 
		CMvAutoLock lock(m_pCriticalSection);
		OBJECT* oData=(OBJECT*)GetI(rp);
		rp=Prev(rp); 
		return oData;
	}

   //
   // Summary:
   //    Retrieves the item at the specified position.
   //
   OBJECT *Get(POSITION p) const 
	{ 
		CMvAutoLock lock(m_pCriticalSection);
		return (OBJECT *) GetI(p);
	}

   //
   // Summary:
   //    Retrieves the item at the head of the list.
   //
   OBJECT *GetHead() const  
	{ 
		CMvAutoLock lock(m_pCriticalSection);
		return Get(GetHeadPosition()); 
	}

   //
   // Summary:
   //    Removes the first item in the list.
   //
   OBJECT *RemoveHead() 
	{ 
		CMvAutoLock lock(m_pCriticalSection);
		return (OBJECT *) RemoveHeadI(); 
	}

   //
   // Summary:
   //    Removes the last item in the list.
   //
   OBJECT *RemoveTail()
	{ 
		CMvAutoLock lock(m_pCriticalSection);
		return (OBJECT *) RemoveTailI(); 
	}

   //
   // Summary:
   //    Removes the item at the specified position.
   //
   OBJECT *Remove(POSITION p) 
	{ 
		CMvAutoLock lock(m_pCriticalSection);
		return (OBJECT *) RemoveI(p); 
	}
    
   //
   // Summary:
   //    Inserts an item before the specified position.
   //
	POSITION AddBefore(POSITION p, OBJECT * pObj)
	{ 
		CMvAutoLock lock(m_pCriticalSection);
		return AddBeforeI(p, pObj); 
	}

   //
   // Summary:
   //    Inserts an item after the specified position.
   //
   POSITION AddAfter(POSITION p, OBJECT * pObj)  
	{ 
		CMvAutoLock lock(m_pCriticalSection);
		return AddAfterI(p, pObj); 
	}

   //
   // Summary:
   //    Adds an item to the front of the list.
   //
   POSITION AddHead(OBJECT * pObj) 
	{ 
		CMvAutoLock lock(m_pCriticalSection);
		return AddHeadI(pObj); 
	}

   //
   // Summary:
   //    Appends an item to the end of the list.
   //
   POSITION AddTail(OBJECT * pObj)  
	{ 
		CMvAutoLock lock(m_pCriticalSection);
		return AddTailI(pObj); 
	}

   //
   // Summary:
   //    Appends the object (pList) to the end of the internal list.
   //
   BOOL AddTail(CMvGenericList<OBJECT> *pList)
   { 
		CMvAutoLock lock(m_pCriticalSection);
		return CMvBaseList::AddTail((CMvBaseList *) pList);
	}


   //
   // Summary:
   //    Adds the object (pList) to the front of the internal list.
   //
   BOOL AddHead(CMvGenericList<OBJECT> *pList)
   { 
      CMvAutoLock lock(m_pCriticalSection);
		return CMvBaseList::AddHead((CMvBaseList *) pList); 
	}


   //
   // Summary:
   //    Inserts a list after the specified position.
   //
   BOOL AddAfter(POSITION p, CMvGenericList<OBJECT> *pList)
   { 
	   CMvAutoLock lock(m_pCriticalSection);
		return CMvBaseList::AddAfter(p, (CMvBaseList *) pList); 
	};


   //
   // Summary:
   //    Inserts a list before the specified position.
   //
   BOOL AddBefore(POSITION p, CMvGenericList<OBJECT> *pList)
   { 
      CMvAutoLock lock(m_pCriticalSection);
      return CMvBaseList::AddBefore(p, (CMvBaseList *) pList); 
	};


   //
   // Summary:
   //    Retrieves the first position that holds the specified item.
   //
   POSITION Find( OBJECT * pObj) const 
	{ 
		CMvAutoLock lock(m_pCriticalSection);
		return FindI(pObj); 
	}

private:
	CMvCriticalSection * m_pCriticalSection;  // Multithread access

};
