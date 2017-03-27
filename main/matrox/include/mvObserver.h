//$Archive: /VP/END-USER/DLLS/mvCommonMechanisms/inc/mvObserver.h $
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


#ifndef mvObserver_h_h
#define mvObserver_h_h

#include "mvObservationConditionIF.h" // For IMvObservationCondition
//#include "mvSubjectContext.h" //For CMvSubjectContext
#include "mvObserverIF.h"

#ifndef LINUX_PLATFORM
   #pragma warning( disable : 4702 ) //Disable "unreachable code" warning
#endif

#include <list> //STL list

#ifndef LINUX_PLATFORM
   #pragma warning( default : 4702 )
#endif

#include "mvSyncAccess.h" //For CMvSyncAccess


/**
* The Observer is the object that observes and will be notified. You can add or
* remove conditions (IMvObservationCondition), which, as their name implies, are
* conditions that must be met in order for them to be notified. It keeps the list 
* of conditions in a std::list. It contains the function Notify() which checks if 
* the condition given by the Subject is met in the list of attached conditions of 
* the Observer. If so, it calls the pure virtual SubNotify() that should be 
* implement by your object.
* You should derive your class that needs to observe the Subject from this one. 
* Furthermore, if you want to allow multiple types of Observers, you can make your
* derived class a Base Class for other Observers. In the function SubNotify(), you
* could dynamically cast the SubjectContext into the appropriate object and then 
* pass it to a pure virtual function, implemented in the derived class.
* For example, the Error Manager has a class CAsyncErrorObserver. To observe an 
* error, someone has to derive a class from this object. It implements SubNotify()
* that casts the Subject Context into an CmvErrorStack and passes it to the 
* function Notify, which the derived class must implement.
*/
class MV_DECLSPEC_DLLEXPORT CMvObserver : public IMvObserver
{	
public:
	CMvObserver( const ESyncMemoryAccessUsage in_eSyncAcess = keSingleReadAcess );
	virtual ~CMvObserver();

public:
	bool AddCondition( IMvObservationCondition* in_pIObservationCondition );
	bool RemoveCondition( IMvObservationCondition* in_pIObservationCondition );
	
protected:
	virtual void SubNotify( const IMvObservationCondition* in_pIObservationCondition, const CMvSubjectContext* in_poSubjectContext ) = 0;
	
private:
	//Notify(): Function called when the Subject has started a notification
	void __stdcall Notify( const IMvObservationCondition* in_pIObservationCondition, const class CMvSubjectContext* in_poSubjectContext, bool* out_pbWasNotified );

	//IsReady(): Function called by the subject when the observer is added to the subject.
	//The subject's "AttachObserver" will fail if the observer's IsReady() fails.
	virtual bool __stdcall IsReady();
	
private:
	std::list <IMvObservationCondition*>* m_poConditionList;

	CMvSyncAccess* m_poSyncAccess;
	
};

#endif
