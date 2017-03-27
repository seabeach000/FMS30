//$Archive: /VP/END-USER/DLLS/mvCommonMechanisms/inc/mvSubjectIF.h $
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

#ifndef mvSubjectIFOfObservationMechanism_h_h
#define mvSubjectIFOfObservationMechanism_h_h

#include "mvObserverIF.h"

#ifdef LINUX_PLATFORM
   #include "mvLinuxDefinitions.h"
#else
	#include <initguid.h> //For DEFINE_GUID
	#include <unknwn.h> //For IUnknown
	#include <winerror.h> //For HRESULT
#endif

// {A64662FC-C6C8-4F19-B88B-B674E2B44BF2}
DEFINE_GUID(IID_IMvSubject, 
			0xa64662fc, 0xc6c8, 0x4f19, 0xb8, 0x8b, 0xb6, 0x74, 0xe2, 0xb4, 0x4b, 0xf2);

/**
* Interface to the subject. This is only used if the subject is a COM and wishes to expose the subject
* function as an interface.
*/
interface IMvSubject : public IUnknown
{
public:
	virtual HRESULT __stdcall AttachObserver( IMvObserver* in_pIObserver ) = 0;
	virtual HRESULT __stdcall DetachObserver( IMvObserver* in_pIObserver ) = 0;
};

#endif
