//$Archive: /VP/END-USER/DLLS/mvCommonMechanisms/inc/mvObserverIF.h $
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


#ifndef IMvObserverOfObservationMechanism_h_h
#define IMvObserverOfObservationMechanism_h_h


#include "mvObservationConditionIF.h" // For IMvObservationCondition
//Note: do not include subjectcontext

enum ESyncMemoryAccessUsage
{
	keNoSyncAcess,		//No Syncrhonization object will be constructed to manage the list.
	keSingleReadAcess,	//A CMvSingleReadAccess object will be constructed to manage the list.
	keMultiReadAcess	//A CMvMultiReadAccess object will be constructed to manage the list.
};

/**
 * Interface for the CMvObserver. It exposes the one functions that 
 * will be called by the Subject. These are:
 * 1) The first Notify that is called by the Observation Mechanism for all observers.
 * Note: It does not derive from IUnknown since we do not want to 
 * implement any AddRef or Release.
 */
interface IMvObserver
{
	friend class CMvSubject;
private:
	//Notify(): Function called when the Subject has started a notification
	virtual void __stdcall Notify( const IMvObservationCondition* in_pIObservationCondition, const class CMvSubjectContext* in_poSubjectContext, bool* out_pbWasNotified ) = 0;

	//IsReady(): Function called by the subject when the observer is added to the subject.
	//The subject's "AttachObserver" will fail if the observer's IsReady() fails.
	virtual bool __stdcall IsReady() = 0;
	
	#ifdef LINUX_PLATFORM
public:	
	   virtual ~IMvObserver() {};
	#endif
	
};

#endif
