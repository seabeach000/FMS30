//$Archive: /VP/COMMON/LIBS/MVUTILITY/inc/mvThread.h $
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

#ifdef	LINUX_PLATFORM
  #include "mvLinuxDefinitions.h"
  #include "mvlinuxthread.h"
#else	// LINUX_PLATFORM

#include <windows.h> //for HANDLE, CRITICAL_SECTION, THREAD_PRIORITY_NORMAL, INFINITE, ...
#include <string>

#define MV_MAX_THREAD_NAME_SIZE 128

#if (defined(_MSC_VER)/* && _MSC_VER <= 1300*/)
// Functions are declared using exception specifications, which Visual C++ 
// accepts but does not implement. Code with exception specifications that are
// ignored during compilation may need to be recompiled and linked to be reused
// in future versions supporting exception specifications.
#pragma warning( disable : 4290 )
#endif


class CMvHandleSyncObject;

bool WaitForAll
      (
      CMvHandleSyncObject* in_aoSyncObjects[],
      int in_iNum,
      unsigned long in_ulTimeOut = INFINITE
      );

int WaitForAny
      (
      CMvHandleSyncObject* in_aoSyncObjects[],
      int in_iNum,
      unsigned long in_ulTimeOut = INFINITE
      );

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Base class for exception objects.
// Remarks:
//    - All exceptions in mvUtility derive from this class.
//
//////////////////////////////////////////////////////////////////////////
class CMvBaseException
{
public:
   //
   // Summary:
   //    Constructor without exception reason string.
   //
   CMvBaseException() {}

   //
   // Summary:
   //    Constructor with exception reason string.
   //
   explicit CMvBaseException(const std::string& in_strExceptionReason)
      : m_strReason(in_strExceptionReason) {}

   //
   // Summary:
   //    Returns the exception reason string (or empty string if it was not set).
   //
   const std::string& GetExceptionReason() const { return m_strReason; }

   //
   // Summary:
   //    Destructor.
   //
   virtual ~CMvBaseException() {}

private:
   std::string m_strReason;   // Error code
};

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    The base class of all synchronization objects (objects which support Wait()).
// Remarks:
//    - Objects derived from this class that support Release() can be used with CMvAutoLock. 
//
//////////////////////////////////////////////////////////////////////////
class CMvSynchronizationObject
{
public:
   // Default destructor.
   virtual ~CMvSynchronizationObject() {}

   //
   // Summary:
   //    Wait on this object for up to a certain time-out in milliseconds.
   // Return value:
   //    Returns true if the wait was successful, returns false if the time-out occurred before the 
   //    object was available.
   // Remarks:
   //    - If the time-out period is not specified, the wait is infinite.
   //
   virtual bool Wait
      (
      unsigned long in_ulTimeOut = INFINITE     // Time out period in milliseconds.
      ) throw() = 0;

   //
   // Summary:
   //    Most objects that were successfully "waited-on" need to be released before an other wait 
   //    can succeed.
   // Remarks:
   //    - Some objects cannot be released (like CMvEvent, CMvThread, and CMvThreadRedirector).
   //
   virtual void Release() throw() = 0;
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is the type of exception that can be thrown by the methods of CMvAutoLock objects.
// See also:
//    CMvBaseException
//
//////////////////////////////////////////////////////////////////////////
class CMvAutoLockException : public CMvBaseException
{
public:
   // Build a CMvAutoLockException by initializing properly the CMvBaseException base class
   explicit CMvAutoLockException(const std::string& in_strExceptionReason)
      : CMvBaseException(in_strExceptionReason) {}
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This class use a CMvSynchronizationObject to lock on construction and unlock on
//    destruction.
// Description:
//    When objects of this type get destroyed, they automatically release their associated 
//    synchronization object.
// Remarks:
//    - Any object that derives from CMvSynchronizationObject and implements
//      the Release method can be passed to CMvAutoLock objects such as CMvCriticalSection, CMvMutex,
//      and CMvSemaphore.
//
//////////////////////////////////////////////////////////////////////////
class CMvAutoLock
{
public:
   //
   // Summary:
   //    Constructor calls in_poSyncObject->Wait().
   //
   explicit CMvAutoLock(CMvSynchronizationObject * in_poSyncObject, bool* out_pbIsWaitAbandoned = NULL);

   //
   // Summary:
   //    Destructor calls Release() on the in_poSyncObject that was passed in the constructor.
   //
   ~CMvAutoLock();

private:
   //
   // Summary:
   //    Object to use for locking mechanism.
   //
   CMvSynchronizationObject * m_poSyncObject;
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is the type of exception that can be thrown by the methods of CMvCriticalSection objects.
// See also:
//    CMvBaseException
//
//////////////////////////////////////////////////////////////////////////
class CMvCriticalSectionException : public CMvBaseException
{
public:
   // Build a CMvCriticalSectionException by initializing properly the CMvBaseException base class
   explicit CMvCriticalSectionException(const std::string& in_strExceptionReason)
      : CMvBaseException(in_strExceptionReason) {}
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This class encapsulate a Win32 critical section.
// Remarks:
//    - When objects of this type get destroyed, they automatically release their associated
//      synchronization object.
//    - Any object that derives from CMvSynchronizationObject and implements the Release method can 
//      be passed to CMvAutoLock objects such as CMvCriticalSection, CMvMutex, and CMvSemaphore.
//
//////////////////////////////////////////////////////////////////////////
class CMvCriticalSection : public CMvSynchronizationObject
{
public:
   //
   // Summary:
   //    Default constructor.
   //
   CMvCriticalSection();

   //
   // Summary:
   //    Default destructor.
   //
   virtual ~CMvCriticalSection();

   //
   // Summary:
   //    Waits on this object until it becomes available. The time-out in milliseconds is optional.
   //
   bool Wait(unsigned long in_ulTimeOut = INFINITE) throw(CMvCriticalSectionException);

   //
   // Summary:
   //    Object becomes available.
   //
   void Release() throw();

private:
   // Critical section to handle.
   CRITICAL_SECTION m_oCriticalSection;
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is the type of exception that can be thrown by the methods of CMvHandleSyncObject 
//    objects (and from objects that derive from CMvHandleSyncObject that use its methods).
// See also:
//    CMvBaseException.
//
//////////////////////////////////////////////////////////////////////////
class CMvHandleSyncObjectException : public CMvBaseException
{
public:
   // Build a CMvHandleSyncObjectException by initializing properly the CMvBaseException base class
   explicit CMvHandleSyncObjectException(const std::string& in_strExceptionReason)
      : CMvBaseException(in_strExceptionReason) {}
};

class CMvWaitAbandonnedException : public CMvHandleSyncObjectException
{
public:
   explicit CMvWaitAbandonnedException(const std::string& in_strExceptionReason)
      : CMvHandleSyncObjectException(in_strExceptionReason){}
};

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    The base class of all synchronization objects that are implemented using Win32 handles.
// Description:
//    All objects derived from this class can be passed to WaitForAll() or WaitforAny() functions. 
//
//    An object of this type can be created by passing a Win32 handle (like a Win32 event handle),
//    so that this handle can be used with other objects found in this library.
//
//////////////////////////////////////////////////////////////////////////
class CMvHandleSyncObject : public CMvSynchronizationObject
{
public:
   //
   // Summary:
   //    Default constructor.
   //
   CMvHandleSyncObject();

   //
   // Summary:
   //    Creates a synchronization object from a Win32 handle.
   // Description:
   //    This can be useful in cases where only a Win32 event is given to you and you want to use 
   //    it with a CMvMutex object in a call to WaitForAll().  A duplicate handle is created
   //    internally, so you must still call the Win32 CloseHandle() function with the original
   //    handle when you no longer need to refer to it
   //
   explicit CMvHandleSyncObject(HANDLE in_hObject);

   //
   // Summary:
   //    Calls the Win32 CloseHandle() function its internal Win32 handle.
   //
   virtual ~CMvHandleSyncObject();

   //
   // Summary:
   //    Wait on this object for up to a certain time-out in milliseconds.
   // Description:
   //    If you do not specify a time-out, the wait is infinite.
   // Return value:
   //    Returns true if the wait was successful, returns false if the time-out occurred before the
   //    object was available.
   //
   bool Wait(unsigned long in_ulTimeOut = INFINITE) throw(CMvHandleSyncObjectException);

   //
   // Summary:
   //    Most objects that were successfully "waited-on" need to be released before an other wait
   //    can succeed.
   // Remarks:
   //    - Some objects cannot be released such as CMvEvent, CMvThread, and CMvThreadRedirector.
   //
   void Release() throw(CMvHandleSyncObjectException);

   //
   // Summary:
   //    Waits for all CMvHandleSyncObject (and derived) objects to become available.
   // Description:
   //    This is a wrapper to the Win32 WaitForMultipleObjects (with bWaitAll set to TRUE) function
   //    that works with CMvHandleSyncObject (and derived) objects.
   // Return value:
   //   Returns true if successful, false if the time-out occurred.
   //
   friend bool WaitForAll
      (
      CMvHandleSyncObject* in_aoSyncObjects[],
      int in_iNum,
      unsigned long in_ulTimeOut
      );

   //
   // Summary:
   //    Waits for any CMvHandleSyncObject (and derived) objects to become available.
   // Description:
   //    This is a wrapper to the Win32 WaitForMultipleObjects (with bWaitAll set to FALSE) 
   //    function that works with CMvHandleSyncObject (and derived) objects.
   // Return value:
   //    Returns the index into the array of the first object that became available,
   //    or -1 if the time-out occurred.
   //
   friend int WaitForAny
      (
      CMvHandleSyncObject* in_aoSyncObjects[],
      int in_iNum,
      unsigned long in_ulTimeOut
      );

protected:
   // Copy constructor
   CMvHandleSyncObject(const CMvHandleSyncObject& in_oObject);

   // Assignement operator
   CMvHandleSyncObject& operator=(const CMvHandleSyncObject& in_oObject);

   // Synchroniation object to handle.
   HANDLE m_hObject;
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is the type of exception that can be thrown by the methods of CMvMutex objects.
// See also:
//    CMvHandleSyncObjectException
//
//////////////////////////////////////////////////////////////////////////
class CMvMutexException : public CMvHandleSyncObjectException
{
public:
   // Build a CMvMutexException by initializing properly the CMvHandleSyncObjectException base class
   explicit CMvMutexException(const std::string& in_strExceptionReason)
      : CMvHandleSyncObjectException(in_strExceptionReason) {}
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    A wrapper for Win32 mutex.
//
//////////////////////////////////////////////////////////////////////////
class CMvMutex : public CMvHandleSyncObject
{
public:
   //
   // Summary:
   //    Creates a mutex.
   //
   CMvMutex();

   //
   // Summary:
   //    Creates a named mutex.
   //
   explicit CMvMutex(const std::string& in_strName);

   //
   // Summary:
   //    Release the object so that it becomes available.
   //
   void Release() throw(CMvMutexException);
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is the type of exception that can be thrown by the methods of CMvSemaphore objects. 
// See also:
//    CMvHandleSyncObjectException
//
//////////////////////////////////////////////////////////////////////////
class CMvSemaphoreException : public CMvHandleSyncObjectException
{
public:
   // Build a CMvSemaphoreException by initializing properly the CMvHandleSyncObjectException base class
   explicit CMvSemaphoreException(const std::string& in_strExceptionReason)
      : CMvHandleSyncObjectException(in_strExceptionReason) {}
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    A wrapper for Win32 semaphores.
// Description:
//    Behaves very much like a mutex except that there can be more than one successful wait on it 
//    (up to a predetermined count) without having any releases.
//
//////////////////////////////////////////////////////////////////////////
class CMvSemaphore : public CMvHandleSyncObject
{
public:
   //
   // Summary:
   //    Creates a semaphore with an initial count of possible successful waits that can be made
   //    (i.e. that would not block) and a maximum possible count.
   // Remarks: 
   //    - Initial count must be greater than or equal to zero and less than or equal to maximum count.
   //    - Maximum count is only defined in Windows API and is therefore IGNORED IN LINUX.
   //    - Trying to release a semaphore that had already reached its maximum count specified
   //      when the semaphore was created would cause a CMvSemaphoreException to be thrown.
   //    
   explicit CMvSemaphore(long in_lInitialCount, long in_lMaxCount);

   //
   // Summary:
   //    Creates a named semaphore with an initial count of possible successful waits that can be made
   //    (i.e. that would not block) and a maximum possible count.
   // Remarks:
   //    - Not implemented in Linux
   //    - Refer to CMvSemaphore::CMvSemaphore(long in_lInitialCount, long in_lMaxCount)
   //
   CMvSemaphore(const std::string& in_strName, long in_lInitialCount, long in_lMaxCount);

   //
   // Summary:
   //    Increments the count by one of successful waits that can be made.
   // Description:
   //    If the count becomes greater than zero, the object becomes available.
   //
   void Release() throw(CMvSemaphoreException);
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is the type of exception that can be thrown by the methods of CMvEvent objects.
// See also:
//    CMvHandleSyncObjectException
//
//////////////////////////////////////////////////////////////////////////
class CMvEventException : public CMvHandleSyncObjectException
{
public:
   // Build a CMvEventException by initializing properly the CMvHandleSyncObjectException base class
   explicit CMvEventException(const std::string& in_strExceptionReason)
      : CMvHandleSyncObjectException(in_strExceptionReason) {}
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    A wrapper for Win32 events.
//
//////////////////////////////////////////////////////////////////////////
class CMvEvent : public CMvHandleSyncObject
{
public:
   //
   // Summary:
   //    Creates a manual reset event by default.
   //
   explicit CMvEvent
      (
      bool in_bManualReset = true   // False to create an auto-reset event.
      );

   //
   // Summary:
   //    Creates a named manual reset event by default.
   //
   explicit CMvEvent
      (
      const std::string& in_strName,   // Event's name
      bool in_bManualReset = true      // False to create a named auto-reset event.
      );

   //
   // Summary:
   //    Sets the event.
   //
   void Set() throw(CMvEventException);

   //
   // Summary:
   //    Resets event.
   //
   void Reset() throw(CMvEventException);
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is the type of exception that can be thrown by the methods of CMvThread objects.
// See also:
//    CMvHandleSyncObjectException
//
//////////////////////////////////////////////////////////////////////////
class CMvThreadException : public CMvHandleSyncObjectException
{
public:
   // Build a CMvThreadException by initializing properly the CMvHandleSyncObjectException base class
   explicit CMvThreadException(const std::string& in_strExceptionReason)
      : CMvHandleSyncObjectException(in_strExceptionReason) {}
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    A wrapper for Win32 threads.
// Remarks:
//    - It is safe to call C run-time library functions from these threads.
//
//////////////////////////////////////////////////////////////////////////
class CMvThread : public CMvHandleSyncObject
{
public:
   //
   // Summary:
   //    Creates a thread object that can do nothing until Create() is called.
   //
   CMvThread();

   // Destructor
   virtual ~CMvThread();

   // Defining the prototype of the user thread function.
   typedef unsigned int (__stdcall *PFNTHREAD_FUNCTION)(void* in_pThreadParameter);

   //
   // Summary:
   //    Creates a thread that will call the function passed to it along with a void* data parameter.
   // Description:
   //    By default, the thread will not be suspended.  By default, the stack will use the default 
   //    stack size defined by the OS (1MB on Windows XP).  The stack size is in bytes.
   //
   void Create
      (
      PFNTHREAD_FUNCTION in_pfnThreadProc,                        // Pointer to the function that the thread will call
      void *             in_pThreadParameter,                     // Pointer to data to be passed to the thread function
      bool               in_bSuspended = false,                   // False to execute thread right away (default)   
      unsigned int       in_uiStackSize = ms_kuiDefaultStackSize, // Thread stack size (0 for OS default)   
      bool               in_bUseSecurityAttribute = false         // False to not use a security attribute (default)
      ) 
      throw(CMvThreadException);

   //
   // Summary:
   //    Sets a mask that tells Windows on which CPU/s this thread can run on (using the Win32
   //    SetThreadAffinityMask()).
   //
   void SetAffinityMask(unsigned int in_uiAffinityMask) throw(CMvThreadException);

   //
   // Summary:
   //    Suspends the thread (using the Win32 SuspendThread()).
   //
   void Suspend() throw(CMvThreadException);

   //
   // Summary:
   //    Resumes the thread (using the Win32 ResumeThread()).
   //
   void Resume() throw(CMvThreadException);

   //
   // Summary:
   //    Changes the threads priority (using the Win32 SetThreadPriority()).
   //
   void SetPriority(int in_iPriority = THREAD_PRIORITY_NORMAL) throw(CMvThreadException);

   //
   // Summary:
   //    Gets the return value of the thread's associated function.
   // Remarks:
   //    - Call this once the thread has completed.
   //
   unsigned int GetExitCode() const throw(CMvThreadException);

   //
   // Summary:
   //    Gets the operating system thread ID
   // Remarks:
   //    - Call this once the thread has been created.
   //
   unsigned int GetThreadID() {return m_uiThreadID;}

   // Stack size for threads is not an exact science and really depends how the created thread is going to be used.
   // Matrox experiences show that in 64 bits operating system, stack size needs to be bigger for code that is built
   // in 32 bits and 64 bits.  That is why the suggested default is different depending on the targeted platform.
   // Stack overflows can occur at any time if the Stack size is not adjusted properly.
#ifdef WIN64
   // Default stack size for the new threads
   static const unsigned int ms_kuiDefaultStackSize = 512 * 1024;  // 512KB
#else
   // Default stack size for the new threads
   static const unsigned int ms_kuiDefaultStackSize = 128 * 1024;  // 128KB
#endif
   //
   // Summary:
   //    Set the public name of the thread.
   // Remarks:
   //    - This should be called by client, or for sample code only.
   //    - Not for internal Matrox threads... (there are other ways...).
   //
   void SetPublicThreadName(const char* in_kszThreadName);

private:
   // Thread Name
   char         m_szPublicThreadName[MV_MAX_THREAD_NAME_SIZE];

protected:

   // Summary:
   //    Internal use only.  Will set the name to the Public Thread Name.
   virtual void _setThreadName();

   unsigned int m_uiThreadID; // Operating system thread ID.
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is the type of exception that can be thrown by the methods of CMvCOMThread objects.
// See also:
//    CMvThreadException
//
//////////////////////////////////////////////////////////////////////////
class CMvCOMThreadException : public CMvThreadException
{
public:
   // Build a CMvCOMThreadException by initializing properly the CMvThreadException base class
   explicit CMvCOMThreadException(const std::string& in_strExceptionReason)
      : CMvThreadException(in_strExceptionReason) {}
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    A wrapper for Win32 threads.
//
//////////////////////////////////////////////////////////////////////////
class CMvCOMThread : public CMvThread
{
public:
   // Default constructor
   CMvCOMThread();
      
   //
   // Summary:
   //    Creates a thread that will call the function passed to it along with a void* data parameter.
   // Description:
   //    By default, the thread will not be suspended.  By default, the stack will use the default 
   //    stack size defined by the OS (1MB on Windows XP).  The stack size is in bytes.
   // Remarks: 
   //    Call ::CoInitialize for COM initialization before calling the user thread function.
   //
   void Create
      (
      PFNTHREAD_FUNCTION in_pfnThreadProc,                  // Pointer to the function that the thread will call
      void *       in_pThreadParameter,                     // Pointer to data to be passed to the thread function
      bool         in_bSuspended = false,                   // False to execute thread right away (default)
      unsigned int in_uiStackSize = ms_kuiDefaultStackSize, // Thread stack size
      bool         in_bMultithreadedCOM = false             // Flags to used with the CoInitiliazeEx call. 
      ) 
      throw(CMvHandleSyncObjectException, CMvEventException, CMvThreadException, CMvCOMThreadException);

protected:
   PFNTHREAD_FUNCTION m_pfnUserProc;   // Function that the thread will call.
   void   * m_pUserThreadParameter;    // Context data.
   bool     m_bMultithreadedCOM;       // Apartment thread or not.
   bool     m_bCOMInit;                // Indicates if the ::CoInitialize succeeded.
   CMvEvent m_oThreadStarted;          // Signaled when the thread is started.
   CMvEvent m_oThreadAcknowledged;     // The derived class signal this event for the read to start
                                          // the call to the user function thread.

   //
   // Summary:
   //    Internal function thread.
   static unsigned int __stdcall COMThreadProc(void* in_pThreadParameter);
};

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is a template class that creates a thread that calls an object's method instead of 
//    calling a function.
// Remarks:
//    - Same as CMvThread except for Create().
// see also:
//    CMvThread 
//////////////////////////////////////////////////////////////////////////
template<class T>
class CMvThreadRedirector : public CMvThread
{
public:
   CMvThreadRedirector();

   //
   // Summary:
   //    Creates a thread that will call an object of type T through a method that returns an
   //    unsigned int.
   // Description:
   //    By default, the thread will not be suspended.  By default, the stack will use the default
   //    stack size defined by the OS (1MB on Windows XP).  The stack size is in bytes.
   //
   void Create
      (
      T *          in_poObject, 
      unsigned int (T::*in_pfnMemberFunction)(), 
      bool         in_bSuspended = false, 
      unsigned int in_uiStackSize = ms_kuiDefaultStackSize
      ) 
      throw(CMvThreadException);

protected:
   T * m_poObject;	// Pointer to the object that the thread will call
   unsigned int (T::*m_pfnMemberFunction)();	// Pointer to the member function to call the object with
   static unsigned int __stdcall ThreadFunction(void* in_pThreadParameter);

private:
   void Create
      (
      PFNTHREAD_FUNCTION in_pfnThreadProc,                        // Pointer to the function that the thread will call
      void             * in_pThreadParameter,                     // Pointer to data to be passed to the thread function
      bool               in_bSuspended = false,                   // False to execute thread right away (default)   
      unsigned int       in_uiStackSize = ms_kuiDefaultStackSize  // Thread stack size (0 for OS default)
      );
};

// Default constructor.
template<class T>
inline CMvThreadRedirector<T>::CMvThreadRedirector() : 
   CMvThread(), m_poObject(NULL), m_pfnMemberFunction(NULL) 
{
}

// Creates the thread.
template<class T>
inline void CMvThreadRedirector<T>::Create
   (
   T *          in_poObject,                    
   unsigned int (T::*in_pfnMemberFunction)(),   
   bool         in_bSuspended,                  
   unsigned int in_uiStackSize                  
   ) 
   throw(CMvThreadException)
{
   if (in_poObject == NULL || in_pfnMemberFunction == NULL)
   {
      throw CMvThreadException("CMvThreadRedirector<T>::Create -> invalid parameters");
   }

   m_poObject = in_poObject;
   m_pfnMemberFunction = in_pfnMemberFunction;
   CMvThread::Create(CMvThreadRedirector<T>::ThreadFunction, this, in_bSuspended, in_uiStackSize);
}

// Internal thread function
template<class T>
inline unsigned int __stdcall CMvThreadRedirector<T>::ThreadFunction(void* in_pThreadParameter)
{
   CMvThreadRedirector<T>* poThis = reinterpret_cast<CMvThreadRedirector<T>*>(in_pThreadParameter);
   return ((poThis->m_poObject)->*(poThis->m_pfnMemberFunction))();
}

#endif // #else LINUX_PLATFORM
