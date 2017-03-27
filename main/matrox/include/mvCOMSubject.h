//$Archive: /VP/END-USER/DLLS/mvCommonMechanisms/inc/mvCOMSubject.h $
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


#ifndef mvCOMSubject_h_h
#define mvCOMSubject_h_h

#include "mvSubject.h"
#include "mvSubjectIF.h"

/**
* The COM subject is the entity that needs to be observed. You can attach or detach 
* IMvObservers to it, which it maintains in a std::list. It contains the trigger 
* point Notify() which starts off the whole Notification.
* The COM Subject uses the functionality of the CMvSubject while
* providing an interface IMvSubject.
* You should derive your COM that is “Observed” (or another one that knows when 
* to Notify) from CMvCOMSubject,
*/
class MV_DECLSPEC_DLLEXPORT CMvCOMSubject :  public IMvSubject, private CMvSubject
{
public:
	CMvCOMSubject( const ESyncMemoryAccessUsage in_eSyncAcess = keSingleReadAcess );
	virtual ~CMvCOMSubject( );

	virtual HRESULT __stdcall AttachObserver( IMvObserver* in_pIObserver );
	virtual HRESULT __stdcall DetachObserver( IMvObserver* in_pIObserver );

	unsigned int Notify( const IMvObservationCondition* in_pIObservationCondition, const CMvSubjectContext* in_poSubjectContext );

};

#endif
