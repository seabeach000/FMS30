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

#include "mvSyncAccess.h" //For CMvSyncAccess
#include "mvThread.h" //For CMvMutex
#include "mvSharedMemory.h"


//
// Summary:
//    Mutex class that derives from the base class CMvSyncAccess. 
// Description:
//    If a name is provided in the constructor, it becomes shared across multiple process.  If not, 
//    it will only be for the current process. Unlike the the CMvSingleReadAccess, CMvMultipleReadAccess 
//    allows multiple threads to possess a ReadLock(). Thus, many threads would be able to read at 
//    the same time. For both objects, only one thread may be in possession of a WriteLock().
// Remarks:
//    - CMvMultipleReadAccess will use not only a CMvMutex, but also a memory mapped file and a 
//      CMvEvent. 
//
class CMvMultipleReadAccess : public CMvSyncAccess
{
	
public:
   //
   // Summary:
   //    Default constructor.
   //
	CMvMultipleReadAccess
      (
      const char* szName = NULL  // Name of the synchronization object to share.
      );

   //
   // Summary:
   //    Destructor.
   //
	~CMvMultipleReadAccess();

   //
   // Summary:
   //    Call this function to gain access to the resource controlled by the synchronization object.
   // Description:
   //    The type of access is of type READ, which means no modification to the object must be done 
   //    when in a possession of such a Lock.
   //
   //    If the ReadLock() succeeds, the thread now owns the object. If the synchronization object
   //    is unavailable, ReadLock() will wait for the synchronization object to become signaled 
   //    up to the number of milliseconds specified in the in_uiTimeOut parameter. If the 
   //    synchronization object did not become signaled in the specified amount of time,
   //    ReadLock() returns failure. Many threads can be in possession of a ReadLock() of a 
   //    CMvMultipleReadAccess at one time. 
   // Return value:
   //    Nonzero, if the function was successful; 0 otherwise.
   //
	bool ReadLock
      (
      const unsigned long in_ulTimeOut = INFINITE  // Specifies the amount of time to wait for the 
                                                   // synchronization object to be available 
                                                   // (signaled). If INFINITE, Lock will wait until
                                                   // the object is signaled before returning.
      );

   //
   // Summary:
   //    Releases a synchronization object. 
   // Return value:
   //    Nonzero if the function was successful, 0 otherwise. 
   //
	bool ReadUnlock( );

   //
   // Summary:
   //    Call this function to gain access to the resource controlled by the synchronization object.
   // Description:
   //    The type of access is of type Write, which means modifications to the object must be done
   //    when in possession of such a Lock.
   //
   //    If WriteLock() succeeds, the thread owns the object and no thread will be able to 
   //    successfully own a Read or Write Lock on that object. If the synchronization object is 
   //    unavailable, WriteLock() waits for the synchronization object to become signaled up to the
   //    number of milliseconds specified in the in_uiTimeOut parameter. If the synchronization
   //    object did not become signaled in the specified amount of time, WriteLock() returns failure. 
   // Return value:
   //    Nonzero if the function was successful; 0 otherwise. 
   //
	bool WriteLock
      (
      const unsigned long in_ulTimeOut = INFINITE  // Specifies the amount of time to wait for the 
                                                   // synchronization object to be available
                                                   // (signaled). If INFINITE, Lock will wait until
                                                   // the object is signaled before returning.
      );

   //
   // Summary:
   //    Releases a synchronization object. 
   // Return Value:
   //    Nonzero if the function was successful; otherwise 0. 
   //
	bool WriteUnlock( );

   //
   // Summary:
   //    Return the number of read lock that have been requested.
   // Return Value:
   //    Number of read lock. 
   //
	unsigned int GetReadersCount();

private:
	CMvSharedMemory	*m_pSharedMemory;     // Shared memory to write to / read from.
	CMvEvent*		m_poEvent;           // Indicate that there is more then one read count.  The 
                                          // write lock thread goes to sleep on this event until 
                                          // the reader count is 0.
	CMvMutex*		m_poMutex;           // Mutex to handle wirter lock.
	unsigned int*	m_puiReadersCount;   // Number of read lock.

	unsigned int	m_uiReadersCountForLocalProcess; // 
};
