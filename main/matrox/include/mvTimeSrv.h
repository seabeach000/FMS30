/*

(c) Copyright Matrox Electronic Systems Ltd., 1997. All rights reserved. 

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
#else
   #include "windows.h"
   #include "mvtypes.h"
#endif


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Singleton Class for performance timing
// Remarks:
//    - Only one instance is used for the whole module using this class
//
//////////////////////////////////////////////////////////////////////////
class CMvPerfTimer
{
public:
   //
   // Summary:
   //    This method is used to get access to the object by returning a pointer to it.
   // Description:
   //    On the first call to this method, the object gets created on the stack and will last until
   //    the process is terminated. This is the reason why this method is declared as static.
   //
	static CMvPerfTimer *GetTimerClass();

   //
   // Summary:
   //    This method will stall the execution of the caller for specified delay in uSec.
   //
	void Wait
      (
      unsigned long in_ulDelay      // Specifies the delay in uSec.
      );

   //
   // Summary:
   //    This method returns the current time in uSec based on the CPU tic counter and the CPU
   //    frequency.
   //
	uint64_t GetTime();

   //
   // Summary:
   //    This method returns the current time in nSec from the last boot.
   //
   uint64_t GetTimeNano();

   //
   // Summary:
   //    This method returns the number of CPU ticks from the last boot.
   //
   uint64_t GetTickCount();

   //
   // Summary:
   //    This method is used internally to measure the CPU frequency in MHz and is public for the
   //    client to verify if needed the accuracy of the timer services.
   //
	uint64_t GetProcessorSpeed();

protected:
    //Protected constructor to fail the object creation with new or direct declaration
	CMvPerfTimer();

private:
   // Comptue processor speed.
   uint64_t InitializeProcessorSpeed();

    //Variable to keep the CPU speed once measured.
	uint64_t m_ui64CPUSpeed;
};
