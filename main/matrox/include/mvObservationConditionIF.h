//$Archive: /VP/END-USER/DLLS/mvCommonMechanisms/inc/mvObservationConditionIF.h $
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


#ifndef mvObservationConditionIF_h_h
#define mvObservationConditionIF_h_h

#include "mvDefinitions.h"

#ifdef LINUX_PLATFORM
   #include "mvLinuxDefinitions.h"
#else
   #include "mvDefinitions.h" // For MV_DECLSPEC_x macros
   #include <unknwn.h> //For IUnknown
#endif   

/**
 * Interface for the CMvObservationCondition. It exposes the one functions that 
 * will be called by the Observer. This is the operator == to know if the condition
 * is met. With this interface, the Observer does not have to include the 
 * 'CMvObservationCondition' header directly. Therefore, classes that derive 
 * from observer do not have to include 'CMvObservationCondition' and hence 
 * do not have to include the 'mvBaseCom.h' which is what we are trying to avoid.
 */
interface IMvObservationCondition : public IUnknown
{
	
public:
	virtual bool __stdcall operator==( const IMvObservationCondition& in_rObservationCondition ) const = 0;
	virtual int __stdcall GetConditionID() const = 0;
};

#endif
