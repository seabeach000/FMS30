//$Archive: /VP/END-USER/DLLS/mvAsyncEventManager/inc/mvAsyncEventManagerIF.h $

//==============================================================================
//
// (c) Copyright Matrox Electronic Systems Ltd., 2003. All rights reserved. 
//
// This code and information is provided "as is" without warranty of any kind, 
// either expressed or implied, including but not limited to the implied 
// warranties of merchantability and/or fitness for a particular purpose.
//
// Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make 
// changes in specifications and code at any time and without notice. 
// No responsibility is assumed by Matrox Electronic Systems Ltd. for 
// its use; nor for any infringements of patents or other rights of 
// third parties resulting from its use. No license is granted under 
// any patents or patent rights of Matrox Electronic Systems Ltd.
//
//-------------------------------------------------------------------------------

#ifndef IMvAsyncEventManager_h_h
#define IMvAsyncEventManager_h_h

#include <initguid.h> //For DEFINE_GUID
#include <unknwn.h>   //For IUnknown
#include <winerror.h> //For HRESULT

#include "mvObserverIF.h"

#include "mvThread.h" //For CMvHandleSyncObject

#ifndef DEFINED_ASYNC_EVENT_MANAGER_GUID
#define DEFINED_ASYNC_EVENT_MANAGER_GUID
// {D05E0C5D-15D2-4F9B-B677-F1AF59197462}
DEFINE_GUID(CLSID_IMvAsyncEventManager, 
         0xd05e0c5d, 0x15d2, 0x4f9b, 0xb6, 0x77, 0xf1, 0xaf, 0x59, 0x19, 0x74, 0x62);
#endif

// {B2C374CD-8770-41B9-87D4-0376FEE66C89}
DEFINE_GUID(IID_IMvAsyncEventManager, 
         0xb2c374cd, 0x8770, 0x41b9, 0x87, 0xd4, 0x3, 0x76, 0xfe, 0xe6, 0x6c, 0x89);

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This interface handles the addition and removal of observers for all event 
//       types: punctual, time span, and graph. It also handles the registration 
//       of hardware events with the Asynchronous Event Manager.
//////////////////////////////////////////////////////////////////////////
interface IMvAsyncEventManager : public IUnknown
{
   
public:


   //
   //DOM-IGNORE-BEGIN
   //    - The type of event observed (graph, punctual, time span) depends on the
   //       class from which the given observer is derived:
   //       * CMvPunctualEventManager for punctual events.
   //       * CMvTimeSpanEventObserver for time span events.
   //       * CMvGraphEventObserver for graph events.
   //DOM-IGNORE-END
   //
   // Summary:
   //    Adds a new event observer to the Asynchronous Event Manager.
   // Return value:
   //    - MV_NOERROR if the observer is added successfully.
   //    - MV_E_INVALID_PARAMETER if the observer is NULL.
   //    - MV_E_FAIL if the observer cannot be added.
   // Remarks:
   //    - The only time an observer cannot be added is when a user tries to add a 
   //       graph observer without having set a graph ID.
   //    - In graph events, all events are observed for a single graph specified by 
   //       the graph ID in its constructor. On the other hand, in punctual and time 
   //       span events, any number of different events may be observed since new 
   //       events can be added by the observer methods.
   virtual HRESULT __stdcall AddAsyncEventObserver
      ( 
      IMvObserver* io_pIAsyncEventObserver // A pointer to the observer that will 
                                             // be notified the next time the observed 
                                             // event occurs. 
                                             
      ) = 0;

   //
   // Summary:
   //    Removes an observer from the Asynchronous Event Manager.
   // Return value:
   //    - MV_NOERROR if the observer is removed successfully.
   //    - MV_E_INVALID_PARAMETER if the observer is NULL.
   //    - MV_E_FAIL if the observer could not be removed (i.e. not found).
   virtual HRESULT __stdcall RemoveAsyncEventObserver
      ( 
      IMvObserver* io_pIAsyncEventObserver // A pointer to the observer to remove.
      ) = 0;

   //
   // Summary:
   //    Registers a punctual event with the Asynchronous Event Manager.
   // Return value:
   //    - MV_NOERROR if the event is registered successfully.
   //    - MV_E_INVALID_PARAMETER if one of the parameters is NULL.
   // Remarks:
   //    - An application observing an event should make sure the event is registered 
   //       first, and should use the ID returned at registration.
   //    - If two applications register with the same in_szPunctualEvent, then 
   //       out_piEventID is filled with the same ID.
   virtual HRESULT __stdcall RegisterPunctualEvent
      ( 
      const char* in_szPunctualEvent,  // Name of the event to register.
      int* out_piEventID               // Pointer to the value that will be filled 
                                          // with the ID of the event. The ID is 
                                          // unique for each named event.
      ) = 0;

   //
   // Summary:
   //    Unregisters the punctual event associated with an ID.
   // Return value:
   //    - MV_NOERROR if the event is unregistered successfully.
   //    - MV_E_INVALID_PARAMETER if no event with the specified ID is found.
   // Remarks:
   //    - The event will be unregistered and will stop notifying observers 
   //       only when all register calls have been paired with an unregister call.
   virtual HRESULT __stdcall UnregisterPunctualEvent
      ( 
      const int in_iEventID // The ID of the event to unregister. This ID was 
                              // retrieved during registration.
      ) = 0;

   //
   // Summary:
   //    This method is for Matrox internal purposes only. 
   //    Registers a time span event with the Asynchronous Event Manager.
   // Return value:
   //    - MV_NOERROR if the event is registered successfully.
   //    - MV_E_INVALID_PARAMETER if one of the parameters is NULL 
   //    - MV_E_FAIL if one of the three named events matches or partially 
   //       matches a group of other registered events.
   // Remarks:
   //    - Any application observing an event should make sure it is registered 
   //       first, and should use the ID returned at registration.
   //    - If two applications register with the same event name, the out_piEventID 
   //       is filled with the same ID.
   virtual HRESULT __stdcall RegisterTimeSpanEvent
      ( 
      const char* in_szStartEvent, // Name of the event that should be set at the 
                                      // start of the time span event.
      const char* in_szStopEvent,  // Name of the event that should be set at the 
                                      // stop of the time span event.
      const char* in_szStillEvent, // Name of the event that should be set during 
                                      // the start and stop event.
                                      // The observers will take appropriate 
                                      // action depending on the amount of time the 
                                      // event is taking.
      int* out_piEventID           // Pointer to the value that will be filled with 
                                      // the ID of the event. The ID is unique for 
                                      // each group of the three named event passed.
      ) = 0;

   //
   // Summary:
   //    This method is for Matrox internal purposes only.
   //       Unregisters the time span event associated with an ID. 
   // Return value:
   //    - MV_NOERROR if the event is unregistered successfully.
   //    - MV_E_INVALID_PARAMETER if no event with the specified ID is found.
   // Remarks:
   //    - The event will be unregistered and will stop notifying observers only when all 
   //       register calls have been paired with an unregister call.
   virtual HRESULT __stdcall UnregisterTimeSpanEvent
      ( 
      const int in_iEventID // The ID of the event to unregister. This ID was retrieved 
                              // during registration.
      ) = 0;

};

#endif

