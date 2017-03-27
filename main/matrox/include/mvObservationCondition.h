//$Archive: /VP/END-USER/DLLS/mvCommonMechanisms/inc/mvObservationCondition.h $
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


#ifndef mvObservationCondition_h_h
#define mvObservationCondition_h_h

#include "mvBaseCOM.h" //For interface and IUnknown

#include "mvObservationConditionIF.h"

/**
* This object is the condition, which must be met in order for the Observers to 
* be notified. Class that derive from this must implement the 
* operator==( CmvObservationCondition&). It is passed to the Notify function of 
* the CmvObserver, which calls the operator== in order to know if it contains 
* the right condition. If so, it calls SubNotify().
*/
class MV_DECLSPEC_DLLEXPORT CMvObservationCondition : 
	public CMvLightUnknown, public IMvObservationCondition
{
	
public:
	CMvObservationCondition();
	virtual ~CMvObservationCondition ();

	//
	// interface IUnknown
	//
	MVDECLARE_IUNKNOWN;

	virtual int __stdcall GetConditionID() const {return 0;} // returns 0 by default
	
private:
	//To remove Warnings
   CMvObservationCondition (CMvObservationCondition &):CMvLightUnknown(NULL,NULL){}
   void operator=( CMvObservationCondition &){}

};

#endif
