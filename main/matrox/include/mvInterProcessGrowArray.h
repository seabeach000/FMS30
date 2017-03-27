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

#include <string>

#include "mvSharedMemory.h"

//
// Summary:
//    A template class implementing an array of variable size, that is shared across processes.
// Remarks:
//    - It basically employs the same concept as TMvInterProcessArray, but the array grows 
//      dynamically (through SetSize() or any calls accessing an index that is not mapped to shared 
//      memory. 
template <class ITEMTYPE>
class TMvInterProcessGrowArray
{

	
public:
   //
   // Summary:
   //    Constructs a TMvInterProcessArrayGrow linked to the MemoryName.
	TMvInterProcessGrowArray
      (
      const char       * in_szMemoryName,    // String specifying the name of the mapping object. 
                                             // In order for two instances of this class to share 
                                             // the same data, the string passed must be the same.
                                             // The name can contain any character except the 
                                             // backslash character (\).

      const unsigned int in_uiInitialMappedFileSize,  // An integer indicating the initial size of
                                                      // elements the array will contain. The number
                                                      // of elements contained may vary afterwards. 

      const unsigned int in_uiNumberToIncreaseMappedFile = 20  // An integer indicating how much the
                                       // size should increase if ever SetAt() or GetAt() is called 
                                       // with an index beyond GetSize(). On any calls accessing an
                                       // index that is beyond that index, in_uiNumberToIncreaseMappedFile
                                       // is added to the index specified in the function (SetAt(),
                                       // GetAt()) to determine the new size of the array.
      );

   //
   // Summary:
   //    Destructor.
	~TMvInterProcessGrowArray( );

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
      );

   //
   // Summary:
   //    Returns the value at a given index.
   // Return value:
   //    The array element currently at this index.
   // Remarks:
   //    - Passing a value greater than or equal to the value returned by GetCount() will result in 
   //      NULL being returned (and a failed assertion in Debug).
	ITEMTYPE & operator[]
      (
      const unsigned int in_uiIndex    // An integer index that is greater than or equal to 0 and 
                                       // less than the value returned by GetCount().
      );

   //
   // Summary:
   //    Sets the value for a given index; array is allowed to grow.
   // Remarks:
	//    - Sets the array element at the specified index. SetAt will cause the array to grow. If the 
   //      index specified is greater or equal to the current size, the array will grow (as if a
   //      SetSize has been called) to a size of the sum of the in_uiNbOfItemsToGrow specified in
   //      the constructor and in_uiIndex.
	void SetAt
      (
      const unsigned int in_uiIndex,   // An integer index that is greater than or equal to 0 and 
                                          // less than or equal to the value returned by GetUpperBound.
      const ITEMTYPE in_newElement     // The new element value to be stored at the specified position.
      );

   //
   // Summary:
   //    Sets the number of elements in this array.
   // Remarks:
	//    - Any calls to SetCount() will return that value. If the new value given is greater than 
   //      the array's max number of items, the call fails and assert.
	void SetCount
      (
      const unsigned int in_uiNumberOfElements  // The new array size (number of elements).
      );

   //
   // Summary:
   //    Sets the maximum number of elements to be contained in this array and re-maps the memory to that file.  
   // Remarks
   //    - If the new size is smaller than the old size, then the array is truncated. All unused 
   //      memory is released.
   //    - If the new size is greater than the old size, then any instance will be able to access
   //      the indexes of the new size.
   //    - Use this function to set the size of your array. If you do not use SetSize(), adding 
   //      elements to your array with SetAt() causes it to be frequently re-mapped.
   void SetSize
      (
      const unsigned int in_uiNewSize  // The new maximum number of elements. 
      );

   //
   // Summary:
   //    Gets the number of elements in this array
   // Remarks:
   //    - Since indexes are zero-based, the size is 1 greater than the largest index. The size may
   //      be changed by any instance of the same array by SetAt() SetSize() calls or constructing
   //      a new array with a in_uiInitialNbOfItems greater than the current size.
	unsigned int GetCount( ) const;

   //
   // Summary:
   //    Increments the number of elements in this array by one.
   // Return value:
   //    The new number of elements.
	unsigned int IncrementCount( );
	
   //
   // Summary:
   //    Decrements the number of elements in this array by one.
   // Return value:
   //    The new number of elements.
	unsigned int DecrementCount( );

   //
   // Summary:
   //    Gets the max number of elements allocated.
   // Remarks:
   //    - Array can grow by calling SetSize() or any calls exceeding the index, and thus have 
   //      grown the size like SetAt() and GetAt().
   //
	unsigned int GetSize( ) const;

   //
   // Summary:
   //    Returns the complete inter-process array. 
   // Return value:
   //    A pointer to the shared array.
	ITEMTYPE* GetArray();

protected:
   // Helper method to map a shared memory pointer.
	void _MapSharedMemory ();
	
private:
   // Array of element.
	ITEMTYPE*            m_atSharedArray;
	
   // Handle to the shared memory mapping the array element.
	CMvSharedMemory*     m_pSharedMemory;
	
   // Number of elements in the array.
	unsigned int*        m_puiSharedElementCount;
	
   // Shared memory name.
	std::string          m_strMemoryName;
	
   // Indicates physically how many elements could be put in the array.
	unsigned int         m_uiMaxNumberOfElementsInMappedFile;

   // Indicates the memory size increment when the array is grown.
	const unsigned int   m_kuiNumberToIncreaseMappedFile;

private:
		//To remove Warnings
	void operator=( TMvInterProcessGrowArray<ITEMTYPE> &){}
	
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
 * Basically the same concept as CMvIPArray but the array would grow dynamically (through GetSize and SetAt calls). This would cause its size to be shared across process also. The Array will support the following calls
 */
template <class ITEMTYPE>
TMvInterProcessGrowArray<ITEMTYPE>::TMvInterProcessGrowArray
	(
	const char* in_szMemoryName, 
	const unsigned int in_uiInitialMaxNumberOfElementsInMappedFile, 
	const unsigned int in_uiNumberToIncreaseMappedFile 
	) : 
	m_atSharedArray( NULL ), 
	m_pSharedMemory( NULL ), 
	m_puiSharedElementCount( NULL ), 
	m_uiMaxNumberOfElementsInMappedFile( in_uiInitialMaxNumberOfElementsInMappedFile ),
	m_kuiNumberToIncreaseMappedFile ( in_uiNumberToIncreaseMappedFile )
{
	//Construct the name of the Array. Add a prefix to be sure
	//it does not confilct with other name of memory mapped file.
	m_strMemoryName = "TMvInterProcessGrowArray";
	m_strMemoryName.append(in_szMemoryName);

	_MapSharedMemory();

	ASSERT(m_pSharedMemory);
	ASSERT(m_puiSharedElementCount);
}

template <class ITEMTYPE>
TMvInterProcessGrowArray<ITEMTYPE>::~TMvInterProcessGrowArray( )
{
	if (m_pSharedMemory)
	{
		delete m_pSharedMemory;
		m_pSharedMemory = NULL;
	}
}

/**
 * void SetCount(const unsigned int in_uiNumberOfElements);
 * Sets the number of elements in this array.
 * Parameters:
 * in_uiNumberOfElements:
 * The new array size (number of elements).
 * Remarks:
 * Sets the number of elements in the array. Any calls to SetCount () will return that value. If the new value given is greater than the array's max number of items, the call fails and assertS.
 */
template <class ITEMTYPE>
void TMvInterProcessGrowArray<ITEMTYPE>::SetCount( const unsigned int in_uiNumberOfElements )
{
	//There is no limit to the count. We don't assert like in the fixed array
	*m_puiSharedElementCount = in_uiNumberOfElements;	
}

/**
 * unsigned int GetCount( ) const;
 * Gets the number of elements in this array
 * Remarks:
 * Returns the size of the array. Since indexes are zero-based, the size is 1 greater than the largest index. The size may be changed by any instance of the same array by SetAt() SetSize() calls or constructing a new array with a in_uiInitialNbOfItems greater than the current size.
 */
template <class ITEMTYPE>
unsigned int TMvInterProcessGrowArray<ITEMTYPE>::GetCount( ) const
{
	return *m_puiSharedElementCount;
}



/**
 * ITEMTYPE GetAt( unsigned int in_uiIndex );
 * Returns the value at a given index.
 * Return Value:
 * The array element currently at this index.
 * Parameters:
 * in_uiIndex:
 * An integer index that is greater than or equal to 0 and less than the value returned by GetCount.
 * Remarks: Passing a value greater than or equal to the value returned by GetCount will result in NULL being returned (and a failed assertion in Debug).
 */
template <class ITEMTYPE>
ITEMTYPE TMvInterProcessGrowArray<ITEMTYPE>::GetAt( const unsigned int in_uiIndex )
{
	if (in_uiIndex >= m_uiMaxNumberOfElementsInMappedFile)
	{
		//If the index is bigger than the current number of elements the
		//memory can hold, we increase the memory to the index plus
		//the "Number of elements" to grow the array, specified in the constructor
		m_uiMaxNumberOfElementsInMappedFile = 1 + in_uiIndex + m_kuiNumberToIncreaseMappedFile;

		_MapSharedMemory();
	}
	
	return m_atSharedArray[in_uiIndex];
}

template <class ITEMTYPE>
ITEMTYPE& TMvInterProcessGrowArray<ITEMTYPE>::operator[]( const unsigned int in_uiIndex )
{
	if (in_uiIndex >= m_uiMaxNumberOfElementsInMappedFile)
	{
		//If the index is bigger than the current number of elements the
		//memory can hold, we increase the memory to the index plus
		//the "Number of elements" to grow the array, specified in the constructor
		m_uiMaxNumberOfElementsInMappedFile = 1 + in_uiIndex + m_kuiNumberToIncreaseMappedFile;

		_MapSharedMemory();
	}

	return m_atSharedArray[in_uiIndex];
}

/**
 * void SetAt( unsigned int in_uiIndex, ITEMTYPE in_newElement );
 * Sets the value for a given index; array is allowed to grow.
 * Parameters:
 * in_uiIndex:
 * An integer index that is greater than or equal to 0 and less than or equal to the value returned by GetUpperBound.
 * in_newElement:
 * The new element value to be stored at the specified position.
 * Remarks:
 * Sets the array element at the specified index. SetAt will cause the array to grow.. If the index specified is greater or equal to the current size, the array will grow (as if a SetSize has been called) to a size of the sum of the in_uiNbOfItemsToGrow specified in the constructor and in_uiIndex.
 */
template <class ITEMTYPE>
void TMvInterProcessGrowArray<ITEMTYPE>::SetAt( const unsigned int in_uiIndex, const ITEMTYPE in_newElement )
{
	if (in_uiIndex >= m_uiMaxNumberOfElementsInMappedFile)
	{
		//If the index is bigger than the current number of elements the
		//memory can hold, we increase the memory to the index plus
		//the "Number of elements" to grow the array, specified in the constructor
		m_uiMaxNumberOfElementsInMappedFile = 1 + in_uiIndex + m_kuiNumberToIncreaseMappedFile;

		_MapSharedMemory();
	}

	m_atSharedArray[in_uiIndex] = in_newElement;
}

/**
 * unsigned int IncrementCount ();
 * Increments the number of elements in this array.
 * Return Value:
 * The new number of elements
 */
template <class ITEMTYPE>
unsigned int TMvInterProcessGrowArray<ITEMTYPE>::IncrementCount( )
{
	*m_puiSharedElementCount ++;

	return *m_puiSharedElementCount;
}

/**
 * unsigned int DecrementCount ();
 * Decrements the number of elements in this array.
 * Return Value:
 * The new number of elements
 */
template <class ITEMTYPE>
unsigned int TMvInterProcessGrowArray<ITEMTYPE>::DecrementCount( )
{
	ASSERT (*m_puiSharedElementCount > 0);

	*m_puiSharedElementCount --;

	return *m_puiSharedElementCount;
}


/**
 * void SetSize(const unsigned int in_uiNewSize );
 * Sets the max number of elements to be contained in this array. Remaps the memory to that file.
 * Parameters:
 * in_uiNewSize:
 * The new max number of elements.
 * Remark:
 * If the new size is smaller than the old size, then the array is truncated. All unused memory is released.
 * If the new size is greater than the old size, then any instance will be able to access the indexes of the new size.
 * Use this function to set the size of your array before you begin using the array. If you do not use SetSize, adding elements to your array with SetAt causes it to be frequently ReMapped
 */
template <class ITEMTYPE>
void TMvInterProcessGrowArray<ITEMTYPE>::SetSize( const unsigned int in_uiNewSize )
{
	if (!in_uiNewSize)
	{
		ASSERT(FALSE);
		return;

	}

	m_uiMaxNumberOfElementsInMappedFile = in_uiNewSize;

	_MapSharedMemory();
}

template <class ITEMTYPE>
unsigned int TMvInterProcessGrowArray<ITEMTYPE>::GetSize( ) const
{
	return m_uiMaxNumberOfElementsInMappedFile;
}

template <class ITEMTYPE>
void TMvInterProcessGrowArray<ITEMTYPE>::_MapSharedMemory ()
{
	if (m_pSharedMemory)
	{
		delete m_pSharedMemory;
	}
	
	bool	bInitialAllocation = false;
	
	m_puiSharedElementCount = NULL;
	m_atSharedArray = NULL;
	
	m_pSharedMemory = (CMvSharedMemory *) new CMvSharedMemory((sizeof(ITEMTYPE) * m_uiMaxNumberOfElementsInMappedFile) + sizeof(unsigned int), m_strMemoryName, bInitialAllocation);

	if (m_pSharedMemory)
	{
		m_puiSharedElementCount = (unsigned int *) m_pSharedMemory->GetPointer();

		//Array must point after the first element, since we keep the count
		//in the first element
		m_atSharedArray = (ITEMTYPE*) (m_puiSharedElementCount+1); 
	}
}

/**
* Return a pointer to the array
*/
template <class ITEMTYPE>
ITEMTYPE* TMvInterProcessGrowArray<ITEMTYPE>::GetArray()
{
	return m_atSharedArray;
}

//DOM-IGNORE-END

