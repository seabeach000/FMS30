/*

(c) Copyright Matrox Electronic Systems Ltd., 2011. All rights reserved. 

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

#ifndef LINUX_PLATFORM
typedef long HRESULT;
#else
#include <sys/types.h>
typedef int32_t HRESULT; // long is 64-bit on Linux 64-bit so we must define HRESULT as int32_t instead
#endif

#include "mvErrors.h"
#include <set>

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This class adds functionality to standard HRESULT variables. It 
//    automatically calls ASSERT(SUCCEEDED(hr)) on the return value of a 
//    call returning an HRESULT, printing out the HRESULT string 
//    description in the assertion dialog.
// Remarks:
//    - To avoid any overhead in Release code, the assertion is defined to
// nothing when in Release builds.
//    - **BE CAREFUL**: When passing a CMvHResult instead of an HRESULT as
// parameter to a function taking a HRESULT& or HRESULT* as output parameter, 
// you MUST call AssertIfError() manually after the function call to verify 
// the error status of the function.
//
//    - TO USE IN A PROJECT:
// 1) include this file (mvHResult.h)
// 2) link with mvUtility.lib
//
//////////////////////////////////////////////////////////////////////////
class CMvHResult
{
public:
   //
   // Summary:
   //    Default constructor
   // Remarks:
   //    - Initializes to MV_NOERROR by default
   //    - Will call ASSERT(SUCCEEDED(in_hrInitialValue)) internally
   //
   CMvHResult(HRESULT in_hrInitialValue = MV_NOERROR);

   //
   // Summary:
   //    Constructor
   // Remarks:
   //    - This constructor takes a variable number of arguments, as indicated by the in_iNbOfIgnores parameter
   //    - Will add all the optional HRESULT parameters to an internal list of exclusions for when we assert the success of a test.
   //         Ex: 
   //             CMvHRESULT ohr(MV_NOERROR,2,MV_E_END_OF_ENUM,MV_E_NOT_FOUND);
   //             ohr = MV_E_END_OF_ENUM;   //Will not call ASSERT(SUCCEEDED(MV_E_END_OF_ENUM)) since this value was excluded upon construction
   //    - Will call ASSERT(SUCCEEDED(in_hrInitialValue)) internally (provided the value is not in the list of exclusions)
   //
   CMvHResult(HRESULT in_hrInitialValue, int in_iNbOfIgnores, ... /*List of HRESULT values to ignore*/);
   
   //
   // Summary:
   //    Destructor
   //
   ~CMvHResult();

   //
   // Summary:
   //    Copy constructor
   // Remarks:
   //    - Excluded HRESULT values from the rvalue object (in_rohr) will also be excluded on the newly created object (this)
   //    - Will call ASSERT(SUCCEEDED(in_rohr.m_hr)) internally (provided the value is not in the list of exclusions)
   //
   CMvHResult(const CMvHResult& in_rohr);

   //
   // Summary:
   //    Assignation operator
   // Remarks:
   //    - Excluded HRESULT values from the rvalue object (in_rohr) will also be excluded on the lvalue object (this)
   //    - Will call ASSERT(SUCCEEDED(in_rohr.m_hr)) internally (provided the value is not in the list of exclusions)
   //
   HRESULT& operator=(const CMvHResult &in_rohr);

   //
   // Summary:
   //    Assignation operator
   // Remarks:
   //    - Will call ASSERT(SUCCEEDED(in_rohr.m_hr)) internally (provided the value is not in the list of exclusions)
   //
   HRESULT& operator=(const HRESULT &in_rhr);

   //
   // Summary:
   //    Conversion operator to HRESULT&
   // Remarks:
   //    - WON'T call ASSERT(SUCCEEDED(HRESULT)) on the new value.
   //    - User must call the AssertIfError() method on the object in order
   // to validate the new value.
   //
   operator HRESULT&();

   //
   // Summary:
   //    Address-of operator
   // Remarks:
   //    - WON'T call ASSERT(SUCCEEDED(HRESULT)) on the new value.
   //    - User must call the AssertIfError() method on the object in order
   // to validate the new value.
   //
   HRESULT* operator&();

   //
   // Summary:
   //    This method explicitly calls ASSERT(SUCCEEDED()) on internal HRESULT 
   //    value.
   // Remarks:
   //    - This method will do nothing if the internal HRESULT value is in the list of exclusions
   //
   void AssertIfError();

   //
   // Summary:
   //    This method is used to modify internal HRESULT value without 
   //    calling ASSERT(SUCCEEDED()) on the new value.
   // Remarks:
   //    - This is useful when an error value is expected during normal
   // execution of the program.
   //
   HRESULT& AssignNoAssert(const HRESULT &in_rhr);

   //
   // Summary:
   //    Tests the internal HRESULT for success
   // Return value:
   //    - true if internal HRESULT is not an error code
   //    - false if internal HRESULT is an error code
   //
   bool DidSucceed();
   
   //
   // Summary:
   //    Tests the internal HRESULT for failure
   // Return value:
   //    - true if internal HRESULT is an error code
   //    - false if internal HRESULT is not an error code
   //
   bool DidFail();

private:
   void _AssertWithFilenameAndLineIfPossible();

   HRESULT m_hr;
   // define this as a pointer to prevent the allocator to be called for nothing 99% of the time.
   // Even if the CMvHResult is allocated on the stack, std::set will call its allocator
   // which allocates on the heap.
   std::set<HRESULT> *m_psethrIgnoreList;
};

