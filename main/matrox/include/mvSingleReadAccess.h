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

#include "mvThread.h"
#include "mvSyncAccess.h" //For CMvSyncAccess

//
// Summary:
//    Mutex class that derives from the base class CMvSyncAccess.
// Description:
//    If a name is provided in the constructor, it becomes across. If not, it will only be for the 
//    current process. CMvSingleReadAccess only allows one thread in possession of a ReadLock().
//    However, for both objects, only one thread may be in possession of  WriteLock(). 
// Remarks:
//    - The CMvSingleReadAccess class uses CMvMutex internally. 
//
class CMvSingleReadAccess : public CMvSyncAccess
{
	
public:
   //
   // Summary:
   //    Default constructor.
   //
	CMvSingleReadAccess
      (
      const char * szName = NULL  // Name of the synchronization object to share.
      );

   //
   // Summary:
   //    Destructor.
   //
	~CMvSingleReadAccess();

   //
   // Summary:
   //    Call this function to gain access to the resource controlled by the synchronization object.
   // Description:
   //    The type of access is of type read, which means no modification to the object must be done 
   //    when in a possession of such a Lock.
   //
   //    If ReadLock() succeeds, the thread now owns the object. If the synchronization object is
   //    unavailable, ReadLock() waits for the synchronization object to become signaled up to the
   //    number of milliseconds specified in the in_uiTimeOut parameter. If the synchronization 
   //    object did not become signaled in the specified amount of time, ReadLock() returns failure.
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
   //    Nonzero if the function was successful; 0 otherwise. 
   //
	bool ReadUnlock( );

   //
   // Summary:
   //    Call this function to gain access to the resource controlled by the synchronization object.
   // Description:
   //    The type of access is of type write, which means modifications to the object must be done 
   //    when in a possession of such a Lock.
   //
   //    If WriteLock() succeeds, the thread now owns the object and no thread will be able to
   //    successfully own a Read or Write lock on that object. If the synchronization object is 
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
   // Return value:
   //    Nonzero if the function was successful; 0 otherwise.
   //
	bool WriteUnlock( );

private:
	CMvMutex * m_poMutex;   // Operating system Mutex to handle.
	
};
