/*

(c) Copyright Matrox Electronic Systems Ltd., 1997. All rights reserved. 

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

#ifdef LINUX_PLATFORM
   #include "mvLinuxDefinitions.h"
#else
   #include <Windows.h> //For HANDLE and CreateFileMapping
   
   #ifndef ASSERT
      #include <crtDbg.h>
      #include <assert.h> // this defines the lower case assert
      #define ASSERT _ASSERTE
   #endif
#endif

#include "mvSharedMemory.h"
#include <string>

//
// Summary:
//    A template class implementing an array of a fixed size, that is shared across processes.
// Remarks:
//    - Uses shared memory.
//    - Because of shared memory, pointers cannot be stored properly since a pointer in one process 
//      may not mean anything in another.
//    - Only direct data can be stored.
template <class ITEMTYPE>
class TMvInterProcessArray
{
	
public:
   //
   // Summary:
   //    Constructs a TMvInterProcessArray linked to the MemoryName. 
   //
	TMvInterProcessArray
      (
      const char       * in_szMemoryName,    // String specifying the name of the mapping object.
                                                // In order for a two instance of this class to
                                                // shared the same data, the string passed must be 
                                                // the same. The name can contain any character
                                                // except the backslash character (\).
      const unsigned int in_uiMaxNbOfItems   // An integer indicating the maximum number of 
                                                // elements the array will be able to contain. 
                                                // Every instance of an array that would have
                                                // access to the same data should be created with
                                                // the same number of elements. Otherwise, the 
                                                // instance with a smaller size will not be able
                                                // to read indexes beyond that size.
      );

   //
   // Summary:
   //    Destructor.
	~TMvInterProcessArray( );

	//
	// Summary:
	//    Decrements the number of elements in this array by one. 
	// Return value:
   //    The new number of elements.
	unsigned int DecrementCount( );

   //
   // Summary:
   //    Returns the value at a given index. 
   // Return value:
   //    The array element currently at this index. 
   // Remarks:
   //    - Passing a value greater than or equal to the value returned by GetCount will result in
   //      NULL being returned (and a failed assertion in Debug). Type topic text here.
	ITEMTYPE GetAt
      (
      const unsigned int in_uiIndex    // An integer index that is greater than or equal to 0 and 
                                       // less than the value returned by GetCount.
      ) const;

   //
   // Summary:
   //    Returns the value at a given index.
   // Return value:
   //    The array element currently at this index.
   // Remarks:
   //    - Passing a value greater than or equal to the value returned by GetCount() will result in 
   //      NULL being returned (and a failed assertion in Debug).
	ITEMTYPE& operator[]
      (
      const unsigned int in_uiIndex    // An integer index that is greater than or equal to 0 and 
                                       // less than the value returned by GetCount().
      );

   //
   // Summary:
   //    Returns the value at a given index.
   // Return value:
   //    The array element currently at this index.
   // Remarks:
   //    - Passing a value greater than or equal to the value returned by GetCount() will result in
   //      NULL being returned (and a failed assertion in Debug).
	const ITEMTYPE& operator[]
      (
      const unsigned int in_uiIndex    // An integer index that is greater than or equal to 0 and
                                       // less than the value returned by GetCount(). 
      ) const;

   //
   // Summary:
   //    Gets the number of elements in this array 
   // Return value:
   //    Returns the size of the array. 
   // Remarks:
   //    - Since indexes are zero-based, the size is 1 greater than the largest index. 
   //    - This number of elements is actually controlled by the user itself, it is not adjusted by 
   //      the object. In other words, calling SetAt() will not increment the count.
	unsigned int GetCount( ) const;

   //
   // Summary:
   //    Increments the number of elements in this array by one. 
   // Return value:
   //    The new number of elements.
	unsigned int IncrementCount( );

   //
   // Summary:
   //    Sets the value for a given index; array is not allowed to grow. 
   // Remarks:
   //    - Sets the array element at the specified index. SetAt() will not cause the array to grow 
   //      as the size is fixed for this object. 
   //    - You must ensure that your index value represents a valid position in the array. If it is
   //      out of bounds, then the debug version of the library asserts. 
	void SetAt
      (
      const unsigned int in_uiIndex,      // An integer index that is greater than or equal to 0 
                                             // and less than the value returned by GetCount().
      const ITEMTYPE     in_newElement    // The new element value to be stored at the specified 
                                             // position.
      );

   //
   // Summary:
   //    Sets the number of elements in this array. 
   // Remarks:
   //    - A call to GetCount() will return the value received by SetCount().
   //    - If the new value given is greater than the array's max number of items, the call fails 
   //      and ASSERTS. The user should call this function if he has modified the number of 
   //      elements, and GetCount() is used somewhere on the array. 
	void SetCount
      (
      const unsigned int in_uiuiNumberOfElements   // The new array size (number of elements).
      );

   //
   // Summary:
   //    Returns the complete inter-process array. 
   // Return value:
   //    A pointer to the shared array.
	ITEMTYPE* GetArray();
	

private:
   // Array of element.
	ITEMTYPE*            m_atSharedArray;
	
   // Pointer to the shared memory object.
	CMvSharedMemory*     m_pSharedMemory;
	
   // Number of elements in the array.
	unsigned int*        m_puiSharedElementCount;
	
   // Indicates physically how many elements could be put in the array.
	const unsigned int   m_kuiMaxNumberOfElement;

private:
   // To remove Warnings
	void operator=( TMvInterProcessArray<ITEMTYPE> &){}
};


/////////////////Implementation//////////////////////////////
/////////////////Implementation//////////////////////////////
/////////////////Implementation//////////////////////////////
/////////////////Implementation//////////////////////////////
/////////////////Implementation//////////////////////////////
/////////////////Implementation//////////////////////////////
/////////////////Implementation//////////////////////////////
//DOM-IGNORE-BEGIN


/**
 * TMvInterProcessArray (const char* in_szMemoryName, const unsigned int in_uiMaxNbOfItems)
 * Constructs a TMvInterProcessArray linked to the MemoryName.
 * Parameters:
 * in_szMemoryName:
 * String specifying the name of the mapping object. In order for a two instance of this class to shared the same data, the string passed must be the same. The name can contain any character except the backslash character (\).
 * in_uiMaxNbOfItems:
 * An integer indicating the maximum number of elements the array will be able to contain. Every instance of an array that would have access to the same data should be created with the same number of elements. Otherwise, the instance with a smaller size will not be able to read indexes beyond that size.
 */
template <class ITEMTYPE>
TMvInterProcessArray<ITEMTYPE>::TMvInterProcessArray
	( 
	const char* in_szMemoryName, 
	const unsigned int in_uiMaxNbOfItems 
	) : 
	m_atSharedArray( NULL ), 
	m_pSharedMemory( NULL ), 
	m_puiSharedElementCount( NULL ),
	m_kuiMaxNumberOfElement (in_uiMaxNbOfItems)
{
	bool 	bInitialAllocation = false;
	
	//Construct the name of the Array. Add a prefix to be sure
	//it does not confilct with other name of memory mapped file.
	std::string	strMemoryName = "TMvInterProcessArray";
	strMemoryName.append(in_szMemoryName);
	
	m_pSharedMemory = (CMvSharedMemory *) new CMvSharedMemory((sizeof(ITEMTYPE) * in_uiMaxNbOfItems) + sizeof(unsigned int), strMemoryName, bInitialAllocation);
	
	if (m_pSharedMemory)
	{
		m_puiSharedElementCount = (unsigned int*) m_pSharedMemory->GetPointer();
	}

	ASSERT(m_puiSharedElementCount != NULL);

	//Array must point after the first element, since we keep the count
	//in the first element
	m_atSharedArray = (ITEMTYPE*) (m_puiSharedElementCount+1); 
}

template <class ITEMTYPE>
TMvInterProcessArray<ITEMTYPE>::~TMvInterProcessArray( )
{
	if (m_pSharedMemory)
	{
		delete m_pSharedMemory;
	}
	m_pSharedMemory =  NULL;
}

/**
 * unsigned int GetCount( ) const;
 * Gets the number of elements in this array
 * Remarks:
 * Returns the size of the array. Since indexes are zero-based, the size is 1 greater than the largest index. This number of elements is actually controlled by the user itself, it is not adjusted by the object. In other words, calling SetAt will not increment the count. The reason for that is that there would be no way to know the count is being decreased.
 */
template <class ITEMTYPE>
void TMvInterProcessArray<ITEMTYPE>::SetCount( const unsigned int in_uiNumberOfElements )
{
	ASSERT (m_kuiMaxNumberOfElement >= in_uiNumberOfElements);

	*m_puiSharedElementCount = in_uiNumberOfElements;
}

/**
 * unsigned int GetCount( ) const;
 * Gets the number of elements in this array
 * Remarks:
 * Returns the size of the array. Since indexes are zero-based, the size is 1 greater than the largest index. This number of elements is actually controlled by the user itself, it is not adjusted by the object. In other words, calling SetAt will not increment the count. The reason for that is that there would be no way to know the count is being decreased.
 */
template <class ITEMTYPE>
unsigned int TMvInterProcessArray<ITEMTYPE>::GetCount( ) const
{
	return *m_puiSharedElementCount;
}

/**
 * ITEMTYPE GetAt( unsigned int in_uiIndex ) const;
 * Returns the value at a given index.
 * Return Value:
 * The array element currently at this index.
 * Parameters:
 * in_uiIndex:
 * An integer index that is greater than or equal to 0 and less than the value returned by GetCount.
 * Remarks: Passing a value greater than or equal to the value returned by GetCount will result in NULL being returned (and a failed assertion in Debug).
 */
template <class ITEMTYPE>
ITEMTYPE TMvInterProcessArray<ITEMTYPE>::GetAt( const unsigned int in_uiIndex ) const
{
	ASSERT (m_kuiMaxNumberOfElement > in_uiIndex);

	return m_atSharedArray[in_uiIndex];
}

template <class ITEMTYPE>
ITEMTYPE& TMvInterProcessArray<ITEMTYPE>::operator[]( const unsigned int in_uiIndex )
{
	ASSERT (m_kuiMaxNumberOfElement > in_uiIndex);

	return m_atSharedArray[in_uiIndex];
}

template <class ITEMTYPE>
const ITEMTYPE& TMvInterProcessArray<ITEMTYPE>::operator[]( const unsigned int in_uiIndex ) const
{
	ASSERT (m_kuiMaxNumberOfElement > in_uiIndex);

	return m_atSharedArray[in_uiIndex];
}


/**
 * void SetAt( unsigned int in_uiIndex, ITEMTYPE in_newElement );
 * Sets the value for a given index; array not allowed to grow.
 * Parameters:
 * in_uiIndex:
 * An integer index that is greater than or equal to 0 and less than the value returned by GetCount.
 * in_newElement:
 * The new element value to be stored at the specified position.
 * Remarks:
 * Sets the array element at the specified index. SetAt will not cause the array to grow as the size is fixed for this object.
 * You must ensure that your index value represents a valid position in the array. If it is out of bounds, then the Debug version of the library asserts.
 */
template <class ITEMTYPE>
void TMvInterProcessArray<ITEMTYPE>::SetAt( const unsigned int in_uiIndex, const ITEMTYPE in_newElement )
{
	ASSERT (m_kuiMaxNumberOfElement > in_uiIndex);

	m_atSharedArray[in_uiIndex] = in_newElement;
}

/**
 * unsigned int DecrementCount ();
 * Decrements the number of elements in this array.
 * Return Value:
 * The new number of elements
 */
template <class ITEMTYPE>
unsigned int TMvInterProcessArray<ITEMTYPE>::DecrementCount( )
{
	ASSERT (*m_puiSharedElementCount > 0);

	*m_puiSharedElementCount --;

	return *m_puiSharedElementCount;
}


/**
 * unsigned int IncrementCount ();
 * Increments the number of elements in this array.
 * Return Value:
 * The new number of elements
 */
template <class ITEMTYPE>
unsigned int TMvInterProcessArray<ITEMTYPE>::IncrementCount( )
{
	ASSERT (m_kuiMaxNumberOfElement > *m_puiSharedElementCount);

	*m_puiSharedElementCount ++;

	return *m_puiSharedElementCount;
}

/**
* Return a pointer to the array
*/
template <class ITEMTYPE>
ITEMTYPE* TMvInterProcessArray<ITEMTYPE>::GetArray()
{
	return m_atSharedArray;
}

//DOM-IGNORE-END
