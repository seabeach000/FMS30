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

#include "mvThread.h" //For CMvMutex

//
// Summary:
//   Base class for both CMvSingleReadAccess and CMvMultiReadAccess. 
// See also:
//    CMvSingleReadAccess, CMvMultipleReadAccess
//
class CMvSyncAccess
{
	
public:
   // Default constructor
	CMvSyncAccess();

   // Desctructor
	virtual ~CMvSyncAccess();

   //
   // Summary:
   //    Call this function to gain access to the resource controlled by the synchronization object.
   // See also:
   //    CMvSingleReadAccess::ReadLock, CMvMultipleReadAccess::ReadLock
   //
	virtual bool ReadLock
      (
      const unsigned long in_ulTimeOut = INFINITE  // Timeout value
      ) = 0;

   //
   // Summary:
   //    Releases a synchronization object.
   // See also:
   //    CMvSingleReadAccess::ReadUnlock, CMvMultipleReadAccess::ReadUnlock
   //
   virtual bool ReadUnlock( ) = 0;

   //
   // Summary:
   //    Call this function to gain access to the resource controlled by the synchronization object.
   // See also:
   //    CMvSingleReadAccess::WriteLock, CMvMultipleReadAccess::WriteLock
   //
   virtual bool WriteLock
      (
      const unsigned long in_ulTimeOut = INFINITE  // Timeout value
      ) = 0;

   //
   // Summary:
   //    Releases a synchronization object. 
   // See also:
   //    CMvSingleReadAccess::WriteUnlock, CMvMultipleReadAccess::WriteUnlock
   //
   virtual bool WriteUnlock( ) = 0;	
};

