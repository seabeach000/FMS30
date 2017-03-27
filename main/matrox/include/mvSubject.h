//$Archive: /VP/END-USER/DLLS/mvCommonMechanisms/inc/mvSubject.h $
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


#ifndef mvSubject_h_h
#define mvSubject_h_h

#include "mvObserverIF.h"

#ifndef	LINUX_PLATFORM
#pragma warning( disable : 4702 ) //Disable "unreachable code" warning
#endif
#include <list> //STL list
#include <vector> //STL vector
#ifndef	LINUX_PLATFORM
#pragma warning( default : 4702 )
#endif

#include "mvSyncAccess.h" //For CMvSyncAccess

/**
* The subject is the entity that needs to be observed. You can attach or detach 
* IMvObservers to it, which it maintains in a std::list. It contains the trigger 
* point Notify() which starts off the whole Notification.
* You should derive the class that is "Observed" (or another one that knows when 
* to Notify) from CmvSubject,
*/
class MV_DECLSPEC_DLLEXPORT CMvSubject
{
public:
	CMvSubject( const ESyncMemoryAccessUsage in_eSyncAcess = keSingleReadAcess );
	virtual ~CMvSubject( );

	virtual HRESULT __stdcall AttachObserver( IMvObserver* in_pIObserver );
	virtual HRESULT __stdcall DetachObserver( IMvObserver* in_pIObserver );

	unsigned int Notify( const IMvObservationCondition* in_pIObservationCondition, const class CMvSubjectContext* in_poSubjectContext );

private:
	std::list <IMvObserver*>* m_pIObserverList;
	std::vector <IMvObserver*>* m_papIObserverVector;

	struct sCurrentNotification 
	{
		bool bEmptyAndReadyForRecycling;
		unsigned int uiCurrentObserverIndex;
	};
	std::vector <sCurrentNotification>* m_pasCurrentNotificationVector; 

	CMvSyncAccess* m_poSyncAccess;

	IMvObserver* m_pICurrentlyNotifiedObserver;
	bool m_bNeedToReInitializeIterator;
};

#endif
