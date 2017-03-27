#pragma once

#include "mvThread.h"
#include "mvTypes.h"
#include <string>

#ifdef	MAC_PLATFORM
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#endif	

#ifdef	LINUX_PLATFORM
#include "mvShmPOSIX.h"
#include "mvNamedSemPOSIX.h"
#endif	

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This is the type of exception that can be thrown by the methods of CMvSharedMemory 
//    objects (and from objects that derive from CMvSharedMemory that use its methods).
// See also:
//    CMvBaseException.
//
//////////////////////////////////////////////////////////////////////////
class CMvSharedMemoryException : public CMvBaseException
{
public:
   // Build a CMvSharedMemoryException by initializing properly the CMvBaseException base class
   explicit CMvSharedMemoryException(const std::string& in_strExceptionReason)
      : CMvBaseException(in_strExceptionReason) {}
};

class CMvSharedMemory : public CMvSynchronizationObject
{
public:
	CMvSharedMemory(uint32_t in_size, const std::string& in_strName, bool &out_bInitialAllocation, bool* out_pbIsWaitAbandoned = NULL);
	~CMvSharedMemory();
	
public:
   bool Wait(unsigned long in_ulTimeOut = INFINITE);
   void Release();
	
	BYTE*			GetPointer();
	uint32_t	GetSize();
	
private:
	uint32_t		m_size;
	std::string	m_key;
	
#ifdef LINUX_PLATFORM
	std::shared_ptr<CMvNamedSemPOSIX> 	m_pMutex;
	std::shared_ptr<CMvShmPOSIX> 			m_hSharedMemory;
#else
	CMvMutex* m_pMutex;
	HANDLE m_hSharedMemory;
        BYTE*  m_pSharedMemory;
        bool _CreateNamedMember(bool &out_bInitialAllocation, bool* out_pbIsWaitAbandoned);
#endif
};
