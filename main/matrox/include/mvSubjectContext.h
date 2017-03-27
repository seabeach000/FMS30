//$Archive: /VP/END-USER/DLLS/mvCommonMechanisms/inc/mvSubjectContext.h $
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


#ifndef mvSubjectContext_h_h
#define mvSubjectContext_h_h

#include "mvDefinitions.h"

/**
* The Subject Context is the object, which will be passed to the Observers 
* during notification. In general, it is what the CMvObservers need to be aware of.
* It should contain all the information about the changes that was made, in order 
* for them to take appropriate action. In some cases, the Subject Context can be 
* the Subject itself, so the Observers are given the Subject.
* You should derive, from this class, all the entitiy(es) that describes the 
* pertinent changes to the CmvSubject. It should be everything your Observers
* need to be aware of.
* 06/10/2003: The object was made the virtual to enable polymorphism
* Furtheremore, the constructor/destructor have been made inline so that people will not
* have to link with the whole DLL just for this object.
*/
class MV_DECLSPEC_DLLEXPORT CMvSubjectContext
{
public:
	CMvSubjectContext() {};
	virtual ~CMvSubjectContext() {};
};

#endif
