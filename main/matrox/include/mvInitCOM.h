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

#pragma once

#ifdef LINUX_PLATFORM
   #include "mvLinuxDefinitions.h"

class CMvInitCOM
{
public:
   //
   // Summary:
   //    
   //
   CMvInitCOM(DWORD in_dwCoInit = 0)
   {
   }

   //
   // Summary:
   //    Default destructor.
   //
   ~CMvInitCOM()
   {
   }

   //
   // Summary:
   //    Returns the constructor error code.
   //
   operator HRESULT() 
   {
      return 0;
   }
};


#else

#define _WIN32_DCOM
#include <objbase.h>

//
// Summary:
//    Initializes the COM for the current module.
//
class CMvInitCOM
{
public:
   //
   // Summary:
   //    
   //
   CMvInitCOM(DWORD in_dwCoInit = COINIT_APARTMENTTHREADED) : m_hr(CoInitializeEx(NULL, in_dwCoInit))
   {
   }

   //
   // Summary:
   //    Default destructor.
   //
   ~CMvInitCOM()
   {
      if (SUCCEEDED(m_hr))
         CoUninitialize();
   }

   //
   // Summary:
   //    Returns the constructor error code.
   //
   operator HRESULT() 
   {
      return m_hr;
   }

private:
   // Dummy copy constructor.
   CMvInitCOM(const CMvInitCOM&);

   // Dummy assignment operator.
   CMvInitCOM& operator=(const CMvInitCOM&);

   // Constructor error code.
   HRESULT m_hr;
};

//Example use
//unsigned int ThreadCode(void*)
//{
//   CMvInitCOM oInit;
//   if (FAILED(oInit))
//      return 0xBAD;
//   
//   //more code that uses COM
//
//   return 0;
//}
#endif

