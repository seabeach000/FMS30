//==============================================================================
//
// (c) Copyright Matrox Electronic Systems Ltd., 2003-2015. All rights reserved. 
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

#pragma once

#include "mvBaseCOM.h"
#include "MvFlexDefinitionsPublicSDK.h"

//
// forward declaration
//
interface IMvFlexEngine;
interface IMvFlexClipReader;
interface IMvFlexClipWriter;
interface IMvFlexMpegClipReader;

struct SMvAudioVideoFileInfo;

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides services to access the system clock.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvClock : public IUnknown
{
   //
   // Summary:
   //    Gets an event handle on which a thread can be blocked to monitor system pace. This event 
   //    handle can be used as the origin for operation scheduling based on the system time.
   // Return value:
   //    - MV_NOERROR, if no errors occur.
   //    - MV_E_INVALID_PARAMETER, if the parameter is NULL.
   // Remarks:
   //    - The caller must make sure that no thread is still waiting on the event before releasing 
   //      the IMvClock interface.
   virtual HRESULT __stdcall GetClockEvent
      (
      HANDLE * out_phEvent // Pointer that receives the event completion handle.
      ) = 0;

   //
   // Summary:
   //    Gets a 64-bit system time value that is expressed in nanotime unites - 1 nanotime unit is equivalent to 100 ns    
   // Return value:
   //    - MV_NOERROR, if no errors occur.
   //    - MV_E_INVALID_PARAMETER, if the parameter is NULL.
   virtual HRESULT __stdcall GetTime
      (
      uint64_t * out_pui64Time   // Pointer that receives the system time of the surface in nanotime.
      ) = 0;

   //
   // Summary:
   //    Registers an event to be pulsed at the specified 64-bit system time value.    
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if a parameter is invalid.
   virtual HRESULT  __stdcall RegisterForNotification
       (
       uint64_t in_ui64NotificationTime, 
       HANDLE in_hEvent
       ) = 0;

   //
   // Summary:
   //    Registers an event to be pulsed starting at the specified 64-bit system time value, and periodically at a specified video resolution.    
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if a parameter is invalid.
   virtual HRESULT  __stdcall RegisterForPeriodicNotification
       (
       uint64_t in_ui64NotificationStartTime, // Specifies the time at which the notification will start.  If the time 
                                                 // is too late, the notification starts at the earliest possible time.
       SMvResolutionInfo* in_psMvResolution,  // Specifies the video unit frequency at which the in_hEvent event is 
                                                 // pulsed.  If this parameter is NULL, the in_hEvent event is pulsed 
                                                 // at each clock ticks (which is about a quarter of a video unit).
       HANDLE in_hEvent                       // Specifies the event to pulse periodically.
       ) = 0;

   //
   // Summary:
   //    Un-registers a previously-registered periodic pulse event.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter is invalid.
   virtual HRESULT  __stdcall UnRegisterForPeriodicNotification
       (
       HANDLE in_hEvent
       ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides the methods necessary to perform synchronized operations on audio 
//    sample buffers and video surfaces.
// Remarks:
//    This interface can be obtained with the QueryInterface() function on an IMvSurface or 
//    IMvAudioSamples interface.  
//////////////////////////////////////////////////////////////////////////////////
interface IMvAVContent : public IUnknown
{
   //
   // Summary:
   //    Attaches a custom data object to a buffer.
   // Description:
   //    The custom data object is used to associate any information to the buffer. Zero, one, or
   //    more custom data objects can be attached to the buffer at the same time. The GUID is used
   //    to distinguish the different custom data types.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if one of the input parameters is NULL. 
   // Remarks:
   //    - The buffer automatically calls IUnknown::AddRef() through pICustomObject when the 
   //      custom data object is attached, and IUnknown::Release() when the custom data object is
   //      detached. The custom data object will be destroyed by a subsequent DetachCustomObject() 
   //      call with the same GUID, a subsequent call to Flush(), or when the buffer object is
   //      released. 
   virtual HRESULT __stdcall AttachCustomObject
      (   
      const GUID * in_pCustomObjectGUID,  // Pointer to the globally unique identifier (GUID) that
                                             // identifies the custom data object to attach.
      IUnknown   * in_pICustomObject      // Pointer to the IUnknown interface to attach to 
                                             // the buffer.
      ) = 0;

   //
   // Summary:
   //    Detaches a custom data object from the buffer. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the input parameter is NULL. 
   //    - MV_E_NOT_FOUND, if no custom data of the type specified by the GUID is attached to the
   //      buffer. 
   // Remarks:
   //    - All custom data objects still attached to the buffer will be detached automatically at 
   //      the destruction of the buffer. The buffer automatically calls IUnknown::AddRef()
   //      through pICustomObject when the custom data object is attached, and it calls 
   //      IUnknown::Release(), when the custom data object is detached. 
   virtual HRESULT __stdcall DetachCustomObject
      (
      const GUID * in_pCustomObjectGUID   // Pointer to the globally unique identifier (GUID) that
                                          // identifies the custom data object to detach.
      ) = 0;

   //
   // Summary:
   //    Retrieves custom data objects attached to the buffer.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if one or two parameters are NULL. 
   //    - MV_E_NOT_FOUND, if no custom data of the type specified by the GUID is attached to the
   //      buffer. 
   // Remarks:
   //    - This method automatically calls IUnknown::AddRef() through pICustomObject. It's the 
   //      user's responsibility to call IUnknown::Release() when the custom data object is no 
   //      longer needed. 
   virtual HRESULT __stdcall GetCustomObject
      (   
      const GUID  * in_pCustomObjectGUID, // Pointer to the globally unique identifier (GUID) that 
                                             // identifies the custom data object to be retrieved.
      IUnknown   ** out_ppICustomObject   // Pointer that receives the desired IUnknown interface's
                                             // pointer.
      ) = 0;

   //
   // Summary:
   //    Returns the buffer to its unused state.
   // Description:
   //    The followings steps are executed: 
   //    - Removes all attached custom data objects.
   //    - Releases surface alias references (if any) and invalidates the user buffer description.
   //    - Resets all of the synchronization values.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_FAIL, if the buffer can't be reset. 
   //    - MV_E_AVCONTENT_IN_USE, if the read count and/or the write count is not zero.
   virtual HRESULT __stdcall Flush ( ) = 0;

   //
   // Summary:
   //    Retrieves the access type of the alias.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter is NULL. 
   // Remarks:
   //    - If it is not an alias, the alias access type returned is keMvAliasAccessTypeInvalid.
   virtual HRESULT __stdcall GetAliasType
      (
      EMvAliasAccessType * out_peAliasType   // Pointer that receives the alias access type.
      ) = 0;

   //
   // Summary:
   //    Retrieves the reference IMvAVContent interface pointer of the alias.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter is NULL. 
   // Remarks:
   //    - If IMvAVContent is not an alias, the reference interface pointer returned is NULL.
   //    - This method automatically calls IUnknown::AddRef() through out_ppIReference. It's the 
   //      user's responsibility to call IUnknown::Release() when the reference IMvAVContent interface
   //      is no longer needed. 
   virtual HRESULT __stdcall GetAliasReference 
      (
      IMvAVContent ** out_ppIReference // Pointer that receives the IMvAVContent interface pointer
                                       // of the reference.
      ) = 0;

   //
   // Summary:
   //    Retrieves the elapsed time (in micro seconds) of the object's last write process to its 
   //    attached buffer.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_MARKWRITE_ERROR, if the MarkWriteStartTime() and/or MarkWriteStopTime() methods 
   //      weren't called properly. 
   // Remarks:
   //    - To obtain a valid elapsed time, the processing modules must use the MarkWriteStartTime()
   //      and MarkWriteStopTime() methods. The elapsed time returned is the difference between the 
   //      first start time and the last stop time. 
   //    - The start and stop times are reset when the Flush() or ResetSynchronization() methods 
   //      are called. 
   virtual HRESULT __stdcall GetElapsedTime
      ( 
      uint64_t * out_pui64ElapsedTime  // Pointer to a 64-bit value that gives the elapsed time in 
                                          // microseconds.
      ) = 0;  

   //
   // Summary:
   //    Retrieves the elapsed time (in microseconds) of one intermediate time of the object's 
   //    last write process to its attached buffer. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_INDEX, if the in_ulIntermediateTimingIndex parameter is not valid. 
   //    - MV_E_MARKWRITE_ERROR, if the MarkWriteStartTime() and/or MarkWriteStopTime() methods 
   //      weren't called properly. 
   // Remarks:
   //    - The intermediate timings are reset when the Flush() or ResetSynchronization() methods
   //      are called. 
   //    - The method GetNumberOfIntermediateTimings() is used to determine the amount of intermediate
   //      timings. 
   virtual HRESULT __stdcall GetIntermediateElapsedTime
      ( 
      unsigned long in_ulIntermediateTimingIndex,  // Zero-based index value of the requested 
                                                      // intermediate value.
      uint64_t     * out_pui64ElapsedTime          // Pointer to a 64-bit value that contains the
                                                      // elapsed time in microseconds.
      ) = 0;  
   
   //
   // Summary:
   //    Retrieves one intermediate start time (in microseconds) for the last write process.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_INDEX, if the in_ulIntermediateTimingIndex parameter is not valid. 
   //    - MV_E_MARKWRITE_ERROR, if the MarkWriteStartTime() and/or MarkWriteStopTime() methods 
   //      weren't called properly.   
   // Remarks:
   //    - The start time returned is the elapsed time, in microseconds, between the last system 
   //      bootup and the intermediate mark write start time.
   //    - The intermediate timings are reset when the Flush() or ResetSynchronization() methods 
   //      are called.  
   virtual HRESULT __stdcall GetIntermediateStartTimeInMicroSeconds
      ( 
      unsigned long in_ulIntermediateTimingIndex,  // Zero-based index value of the requested
                                                      // intermediate value.
      uint64_t    * out_pui64StartTime // Pointer to a 64-bit value that contains the elapsed time
                                          // (in microseconds)  between the last system bootup
                                          // and the mark write start time.
      ) = 0;  

   //
   // Summary:
   //    Retrieves the intermediate start time (in CPU ticks) for the last write process. 
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_INDEX, if the in_ulIntermediateTimingIndex parameter is not valid. 
   //    - MV_E_MARKWRITE_ERROR, if the MarkWriteStartTime() and/or MarkWriteStopTime() methods 
   //      were not called properly.
   // Remarks:
   //    - The start time returned is the number of CPU ticks from the last system bootup and the
   //      intermediate mark write start time.
   //    - The intermediate timings are reset when the Flush() or ResetSynchronization() method is 
   //      called. 
   virtual HRESULT __stdcall GetIntermediateStartTimeInTicks
      (
      unsigned long in_ulIntermediateTimingIndex,  // Zero-based index value of the requested 
                                                      // intermediate value.
      uint64_t    * out_pui64StartTime    // Pointer to a 64-bit value that gives the elapsed time in
                                             // ticks, from the last system bootup to the time that the
                                             // last MarkWriteStartTime operation has been performed.
      ) = 0; 

   //
   // Summary:
   //    Retrieves one intermediate stop time (in microseconds) for the last write process. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_INDEX, if the in_ulIntermediateTimingIndex parameter is not valid.
   //    - MV_E_MARKWRITE_ERROR, if the MarkWriteStartTime() and/or MarkWriteStopTime() methods 
   //      weren't called properly. 
   // Remarks:
   //    - The stop time returned is the elapsed time (in microseconds) between the last system
   //      bootup and the the time the last MarkWriteStopTime operation is performed.
   //    - The intermediate timings are reset when the Flush() or ResetSynchronization() methods 
   //      are called.  
   virtual HRESULT __stdcall GetIntermediateStopTimeInMicroSeconds
      ( 
      unsigned long in_ulIntermediateTimingIndex,  // Zero-based index value of the requested
                                                      // intermediate stop timing.
      uint64_t    * out_pui64StopTime  // Pointer to a 64-bit value that gives the  elapsed time in
                                          // microseconds, between the last system bootup and 
                                          // the mark write stop time.
      ) = 0;  

   //
   // Summary:
   //    Retrieves the stop time (in CPU ticks) for the last write process.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_INDEX, if the in_ulIntermediateTimingIndex parameter is not valid. 
   //    - MV_E_MARKWRITE_ERROR, if the MarkWriteStartTime() and/or MarkWriteStopTime() methods
   //      were not called properly. 
   // Remarks:
   //    - The stop time returned is the number of CPU ticks from the last system bootup and the 
   //      intermediate mark write start time.
   //    - The intermediate timings are reset when the Flush() or ResetSynchronization() methods
   //      are called. 
   virtual HRESULT __stdcall GetIntermediateStopTimeInTicks
      ( 
      unsigned long in_ulIntermediateTimingIndex,  // Zero-based index value of the requested
                                                      // intermediate value.
      uint64_t    * out_pui64StopTime  // Pointer to a 64-bit value that contains the elapsed time in
                                          // ticks, from the last system bootup to the time that the 
                                          // last MarkWriteStopTime operation was performed.
      ) = 0; 

   //
   // Summary:
   //    Retrieves the error code associated with the buffer.
   // Remarks:
   //    - A processing unit can associate an error code to a buffer. Only the first error
   //      that occurred is retained and propagated. The synchronization object is signaled to 
   //      allow fast error catching. 
   //    - This method gives access to the error reporting mechanism in a buffer.
   virtual HRESULT __stdcall GetLastError
      (  
      HRESULT * out_phrResult // Pointer to an HRESULT that is filled in the error code.
      ) = 0;

   //
   // Summary:
   //    Returns the number of intermediate timings that where computed for the completion of the
   //    write event.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - The intermediate timings are reset when the Flush() or ResetSynchronization() methods 
   //      are called. 
   virtual HRESULT __stdcall GetNumberOfIntermediateTimings
      (  
      unsigned long * out_pulNbIntermediateTimings // Pointer to an unsigned long value that 
                                                   // contains the number of intermediate timings.
      ) = 0;

   //
   // Summary:
   //    Retrieves the handle of the event that will be signaled when the buffer has been read by all the
   //    units that were called for reading.
   // Remarks:
   //    - The caller must make sure that there is no thread waiting on the event before releasing
   //      the buffer. 
   virtual HRESULT __stdcall GetReadCompletionEvent
      (  
      HANDLE * out_phEvent // Pointer that receives the completion event handle.
      ) = 0;

   //
   // Summary:
   //    Gets the number of read operations that will occur.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter is NULL. 
   virtual HRESULT __stdcall GetReadCount 
      (  
      unsigned long * out_pulReadCount // Pointer that receives the read count of the buffer.
      ) = 0;

   //
   // Summary:
   //    Retrieves the start time (in microseconds) for the last write process. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_MARKWRITE_ERROR, if the MarkWriteStartTime() and/or MarkWriteStopTime() methods
   //      were not called properly.   
   // Remarks:
   //    - The processing modules must have used the IMvAVContent::MarkWriteStartTime() and 
   //      IMvAVContent::MarkWriteStopTime() methods to obtain a valid start time. The start time
   //      returned is the elapsed time, in microseconds, between the last system bootup and the
   //      mark write start time.
   //    - The mark start and stop time are reset when the Flush() or ResetSynchronization() 
   //      methods are called.  
   virtual HRESULT __stdcall GetStartTimeInMicroSeconds
      (
      uint64_t * out_pui64StartTime // Pointer to a 64-bit value that gives the elapsed time (in 
                                    // microseconds) between the last system bootup and the time the 
                                    // last MarkWriteStartTime operation was performed
      ) = 0;  

   //
   // Summary:
   //    Retrieves the start time (in CPU ticks) for the last write process.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_MARKWRITE_ERROR, if the MarkWriteStartTime() and/or MarkWriteStopTime() methods 
   //      weren't called properly. 
   // Remarks:
   //    - The processing modules must have used the IMvAVContent::MarkWriteStartTime() and 
   //      IMvAVContent::MarkWriteStopTime() methods to obtain a valid start time ticks count.
   //      The start time returned is the number of CPU ticks from the last system bootup to the
   //      time the last MarkWriteStartTime operation is performed.
   //    - The mark start and stop times are reset when the Flush() or ResetSynchronization() method
   //      is called. 
   virtual HRESULT __stdcall GetStartTimeInTicks
      (
      uint64_t * out_pui64StartTime // Pointer to a 64-bit value that gives the elapsed time in 
                                       // ticks, from the last system bootup to the time that the 
                                       // last MarkWriteStartTime operation has been performed.
      ) = 0;  

   //
   // Summary:
   //    Retrieves the stop time (in microseconds) of the last write process. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_MARKWRITE_ERROR, if the MarkWriteStartTime() and/or MarkWriteStopTime() methods 
   //      were not called properly. 
   // Remarks:
   //    - The processing modules must have used the IMvAVContent::MarkWriteStartTime() and 
   //      IMvAVContent::MarkWriteStopTime() methods to obtain a valid stop time. The stop time
   //      returned is the elapsed time, in microseconds, between the last system bootup and the
   //      mark write stop time.
   //    - The mark start and stop times are reset when the Flush() or ResetSynchronization()
   //      methods are called.  
   virtual HRESULT __stdcall GetStopTimeInMicroSeconds
      (
      uint64_t * out_pui64StopTime  // Pointer to a 64-bit value that gives the elapsed time (in
                                       // microseconds) between the last system bootup and the time 
                                       // that the last MarkWriteStopTime operation is performed.
      ) = 0; 

   //
   // Summary:
   //    Retrieves the stop time (in CPU ticks) for the last write process.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_MARKWRITE_ERROR, if the MarkWriteStartTime() and/or MarkWriteStopTime() methods 
   //      weren't called properly. 
   // Remarks:
   //    - The processing modules must have used the IMvAVContent::MarkWriteStartTime() and
   //      IMvAVContent::MarkWriteStopTime() methods to obtain a valid stop time ticks count. 
   //      The stop time returned is the number of CPU ticks from the last system bootup to the 
   //      time that the last MarkWriteStopTime operation has been performed.
   //    - The mark start and stop times are reset when the Flush() or ResetSynchronization() 
   //      methods are called. 
   virtual HRESULT __stdcall GetStopTimeInTicks
      (
      uint64_t * out_pui64StopTime  // Pointer to a 64-bit value that gives the elapsed time in 
                                    // ticks, from the last system bootup to the time that the 
                                    // last MarkWriteStopTime operation has been performed.
      ) = 0;   

   //
   // Summary:
   //    Retrieves the time stamp information associated with the buffer. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter is NULL. 
   // Remarks:
   //    - It is used to sequence operations in the stream. The time stamp is expressed in nanotime,
   //      where 1 nanotime is 100 nanoseconds.
   virtual HRESULT __stdcall GetTimeStampInfo 
      (  
      uint64_t * out_pui64Time   // Pointer that receives the system time of the buffer in nanotime (see remarks).
      ) = 0;

   //
   // Summary:
   //    Retrieves the handle of the event that will be signaled when all the units that were called for writing are 
   //    finished writing to the buffer.
   // Remarks:
   //    - The caller must make sure that there is no thread waiting on the event before releasing
   //      the buffer. 
   virtual HRESULT __stdcall GetWriteCompletionEvent
      (
      HANDLE * out_phEvent // Pointer that receives the completion event handle.
      ) = 0;

   //
   // Summary:
   //    Gets the number of a write operations that will occur.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter is NULL.
   virtual HRESULT __stdcall GetWriteCount 
      (  
      unsigned long * out_pulWriteCount   // Pointer that receives the write count of the buffer.
      ) = 0;

   //
   // Summary:
   //    Increments the number of read operations to be completed on a buffer by one.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_FAIL, if the count could not be incremented. 
   virtual HRESULT __stdcall IncrementReadCount( ) = 0;

   //
   // Summary:
   //    Increments the number of write operations to be completed on a buffer by one.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_FAIL, if the count could not be incremented. 
   // Remarks:
   //    - This method will fail if used with a ReadOnly Alias.
   virtual HRESULT __stdcall IncrementWriteCount ( ) = 0;

   //
   // Summary:
   //    Indicates whether or not the object is ready for reading.
   // Return value:
   //    - If true, the object is ready for reading. Otherwise, false. 
   // Remarks:
   //    - A thread switch can occur in this method. For performance reasons, this method must not be polled. 
   virtual bool    __stdcall IsReadyForRead ( ) = 0;

   //
   // Summary:
   //    Marks the write process start time on the object.    
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   virtual HRESULT __stdcall MarkWriteStartTime ( ) = 0;

   //
   // Summary:
   //    Stops the timer that is used to compute the write process time on the object. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The method GetElapsedTime() can be used to retrieve the elapsed time between the start
   //      and stop times.
   virtual HRESULT __stdcall MarkWriteStopTime ( ) = 0;

   //
   // Summary:
   //    Sets the synchronization of the buffer to an unused state.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_FAIL, if it was unable to reset the synchronization. 
   //    - MV_E_AVCONTENT_IN_USE, if the read count and/or the write count is not zero.
   virtual HRESULT __stdcall ResetSynchronization ( ) = 0;

   //
   // Summary:
   //    Sets the error code associated with the buffer.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_FAIL, if the error code could not be set. 
   virtual HRESULT __stdcall SetLastError
      (  
      HRESULT in_hrResult  // Specifies the error code to associate with the buffer.
      ) = 0;

   //
   // Summary:
   //    Modifies the time stamp operation associated with the buffer. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - It is used to sequence operations in the stream. The time stamp is expressed in nanotime,  
   //      where 1 nanotime is 100 nanoseconds.
   virtual HRESULT __stdcall SetTimeStampInfo
      (  
      uint64_t * in_pui64Time // Pointer to the specified system time of the buffer in nanotime.
      ) = 0;

   //
   // Summary:
   //    Signals the completion of a read operation on a buffer.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_FAIL, if it was unable to signal the read operation.
   // Remarks:
   //    - This method decreases the read count of each read operation that has been completed on a buffer by one.
   //      When the read count reaches 0, the read completion event is signaled.
   virtual HRESULT __stdcall SignalReadCompletion  ( ) = 0;

   //
   // Summary:
   //    Signals the completion of a write operation on a buffer.
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_E_FAIL, if unable to signal the write operation.  
   // Remarks:
   //    - This will decrement the write count by one. When the write count reaches 0, the write
   //      completion event is signaled.
   //    - Once a buffer is written to, it becomes ready for reading.
   virtual HRESULT __stdcall SignalWriteCompletion ( ) = 0;

   //
   // Summary:
   //    Modifies the name of the buffer for debugging purposes.
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_E_FAIL, if an error occurred. 
   virtual HRESULT __stdcall SetName ( const wchar_t* in_pwchName ) = 0;

   //
   // Summary:
   //    Retrieves the name of the buffer for debugging purposes.
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_E_FAIL, if an error occurred.  
   // Remarks:
   //    - The default name is the string value of the pointer to the buffer.
   virtual HRESULT __stdcall GetName ( wchar_t* out_pwchName, const uint32_t in_ui32NumberOfCharsInDestString ) = 0;

   //
   // Summary:
   //    Sets a read error code associated with the buffer.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_FAIL, if the error code could not be set. 
   // Remarks:
	//    - A processing unit can associate an error code to a buffer because of a failed read operation. 
	//      Only the last error that occurred is retained and propagated. The synchronization object is signaled to 
	//      allow fast error catching. 
	//    - This method gives access to the error reporting mechanism of a buffer.
   virtual HRESULT __stdcall SetLastReadError
      (  
      HRESULT in_hrResult  // Specifies the error code to associate with the buffer.
      ) = 0;

   //
   // Summary:
   //    Sets a write error code associated with the buffer.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_FAIL, if the error code could not be set.
   // Remarks:
	//    - A processing unit can associate an error code to a buffer because of a failed write operation. 
	//      Only the last error that occurred is retained and propagated. The synchronization object is signaled to 
	//      allow fast error catching. 
	//    - This method gives access to the error reporting mechanism of a buffer.
   virtual HRESULT __stdcall SetLastWriteError
      (  
      HRESULT in_hrResult  // Specifies the error code to associate with the buffer.
      ) = 0;

	//
	// Summary:
	//    Retrieves the read error code associated with the buffer.
	// Remarks:
	//    - A processing unit can associate an error code to a buffer because of a failed read operation. 
	//      Only the last error that occurred is retained and propagated. The synchronization object is signaled to 
	//      allow fast error catching. 
	//    - This method gives access to the error reporting mechanism of a buffer.
	virtual HRESULT __stdcall GetLastReadError
		(  
		HRESULT * out_phrResult  // Specifies the error code to associate with the buffer.
		) = 0;

	//
	// Summary:
	//    Retrieves the write error code associated with the buffer.
	// Remarks:
	//    - A processing unit can associate an error code to a buffer because of a failed write operation. 
	//      Only the last error that occurred is retained and propagated. The synchronization object is signaled to 
	//      allow fast error catching. 
	//    - This method gives access to the error reporting mechanism of a buffer.
	virtual HRESULT __stdcall GetLastWriteError
		(  
		HRESULT * out_phrResult  // Specifies the error code to associate with the buffer.
		) = 0;
};

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Used by the A/V Content Pool Manager to notify a 'user' that an AVContent has just been 
//    completed.
// Remarks:
//    - This interface must be implemented by the user.
//////////////////////////////////////////////////////////////////////////
interface IMvAVContentCompletionObserver : public IUnknown
{
   //
   // Summary:
   //    Allows an external object to examine the AVContent upon its completion.
   // Return value:
   //    - Should not return any errors. 
   // Remarks:
   //    - The external module may keep the AVContent by calling AddReference() on it, and then process
   //      and release it asynchronously. 
   //    - This function may be called simultaneously by many threads. The external module MUST be
   //      prepared to handle this case in its implementation. 
   //    - The external module MUST NOT alter the AVContent, it is only allowed to examine 
   //      it. It especially MUST NOT call the IMvAVContent::Flush() method. The module calling 
   //      OnAVContentCompletion() will take care of properly recycling the AVContent. 
   virtual HRESULT __stdcall OnAVContentCompletion
      (
      IMvAVContent * in_pIAVContent // Pointer to the AVContent that was just completed.    
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Used by the A/V Content Pool Manager to notify a 'user' that an AVContent is now available.
// Remarks:
//    - This interface must be implemented by the user for use as a callback.
//
//////////////////////////////////////////////////////////////////////////

interface IMvAVContentReceiver : public IUnknown
{
   //
   // Summary:
   //    This method is called by the A/V Content Pool Manager to give an available AVContent to a 
   //    'user' that has requested an AVContent. 
   // Return value:
   //    - This method should not return AVContent.
   // Remarks:
   //    - If the module receiving the AVContent wants to keep it, it must do an AddRef() on it. 
   virtual HRESULT __stdcall ReceiveAVContent
      (
      IMvAVContent * in_pIAVContent // Pointer to the AVContent that is now available.
      ) = 0;
};



//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Allows you to perform operations on a specific video surface.
// Remarks:
//    - This interface supports the following query interfaces: IID_IMvAVContent
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSurface : public IMvAVContent
{
   //
   // Summary:
   //    Assigns the reference surface to a surface alias.
   // Description:
   //    The surface alias inherits all the properties of the reference surface. The memory buffer 
   //    contained in the reference surface is also shared with the surface alias. This method can 
   //    only be called on alias surfaces.
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_E_INVALID_PARAMETER, if the input parameters is NULL.  
   //    - MV_E_NOT_SUPPORTED, if the surface is not a surface alias or if the reference surface
   //      specified is an alias surface.  
   // Remarks:
   //    - The alias and the reference surfaces have separate synchronization objects that are 
   //      linked internally. Each time a component increments the synchronization read or write
   //      count of the alias, the read count of the reference surface is automatically incremented.
   //      Each SignalReadCompletion operation performed on the alias automatically calls the 
   //      SignalReadCompletion() method on the reference. Also, each SignalWriteCompletion 
   //      operation performed on the alias automatically calls the SignalWriteCompletion() method
   //      on the reference.  
   //    - If the alias access type is read-only, the write completion on the alias event will be
   //      signaled automatically when the write completion event of the reference is signaled.  
   //    - It is possible to change the alias reference by calling this method more than once. 
   //      However, the alias must be flushed before assigning a new reference.  
   //    - The reference surface must be usable at the assignment. Therefore, an empty user buffer
   //      or an unset alias cannot be assigned as the reference of an alias. Once a user buffer has 
   //      been set with AssignUserBufferReference and has been assigned as the reference of an 
   //      alias it cannot be changed using AssignUserBufferReference() until it has been flushed.
   //    - It is possible to assign an alias on an alias, as long as the reference alias has a 
   //      valid reference attached to it.  
   virtual HRESULT __stdcall AssignAliasReference
      ( 
      IMvSurface       * in_pIReferenceSurface, // Address of an IMvSurface interface that is the
                                                   // reference of the surface alias.
      EMvAliasAccessType in_eAccessType         // Access type required for the alias. If the alias 
                                                   // is not intended to be written to any modules,
                                                   // the access type "ReadOnly" must be used.
                                                   // Otherwise, "ReadWrite" access type should
                                                   // be used.
      ) = 0;

   //
   // Summary:
   //    Assigns the reference surface to a surface alias.
   // Description:
   //    The surface alias inherits all the properties of the reference surface, except for the 
   //    specified resolution scan mode. The memory buffer contained in the reference surface is
   //    also shared with the surface alias. This method can only be called on alias surfaces.
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //    - MV_E_INVALID_PARAMETER, if one of the input parameter is invalid.  
   //    - MV_E_NOT_SUPPORTED, if the surface is not a surface alias or if the reference surface
   //      specified is an alias surface.  
   // Remarks:
   //    - The alias and the reference surfaces have separate synchronization objects that are 
   //      linked internally. Each time a component increments the synchronization read or write
   //      count of the alias, the read count of the reference surface is automatically incremented.
   //      Each SignalReadCompletion operation performed on the alias automatically calls the
   //      SignalReadCompletion() method on the reference. Also, each SignalWriteCompletion 
   //      operation performed on the alias automatically calls the SignalWriteCompletion() method
   //      on the reference.  
   //    - If the alias access type is read-only, the write completion on the alias event will be
   //      signaled automatically when the write completion event of the reference is signaled.  
   //    - It is possible to change the alias reference by calling this method more than once.
   //      However, the alias must be flushed before assigning a new reference.  
   //    - The reference surface must be usable at the assignment. Therefore, an empty user buffer
   //      or an unset alias can not be assigned as a reference of an alias. However, a user buffer
   //      that has been set with AssignUserBufferReference can be assigned as a reference of an
   //      alias, even if the data pointer is not determined yet. In this case, the data pointer 
   //      must be properly set with another AssignUserBufferReference() method call before doing
   //      any read operation on the reference or on its aliases.  
   //    - It is possible to assign an alias on an alias, as long as the reference alias has
   //      valid reference attached to it.  
   virtual HRESULT __stdcall AssignAliasReferenceEx
      ( 
      IMvSurface       * in_pIReferenceSurface, // Address of an IMvSurface interface that is the 
                                                   // reference of the surface alias.
      EMvAliasAccessType in_eAccessType,        // Access type required for the alias. If the alias
                                                   // is not intended to be written to any modules,
                                                   // the access type 'ReadOnly' must be used.
                                                   // Otherwise, 'ReadWrite' access type should be used.
      EMvScanMode        in_eResolutionScanMode // Scan mode of the resolution in which the surface
                                                   // is intended to be used. Internally, this scan
                                                   // mode is used to determine the bIsSurfaceOfTopLine
                                                   // parameter of SMvSurfaceDescription.
      ) = 0;

   //
   // Summary:
   //    Assigns a host-memory buffer already allocated to a user buffer surface. 
   // Return value:
   //    - MV_NOERROR, if completed succesfully. 
   //    - MV_E_INVALID_PARAMETER, if in_psDescription is NULL. 
   //    - MV_E_NOT_SUPPORTED, if the surface is not a user buffer surface. 
   // Remarks:
   //    - It is possible to change the user buffer reference by calling this method more than once. 
   virtual HRESULT __stdcall AssignUserBufferReference
      (
      SMvUserBufferSurfaceDescription * in_psDescription // Pointer to the description of the buffer
                                                         // to encapsulate. 
      ) = 0;

   //
   // Summary:
   //    Clears the surface with the specified color and alpha values.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_NOT_SUPPORTED, if the clear operation cannot be performed on this type of surface. 
   //    - MV_E_MODULE_BUSY, if a previous Clear() call with the same thread pool ID is not yet 
   //      completed. This limitation is for host and user surface memory location only. 
   //    - MV_E_POINTER_NOT_ALIGNED, if the surface data pointer is not properly aligned. 
   virtual HRESULT __stdcall Clear
      (
      EMvColor      in_eColor,            // Predefined color value used to clear the surface.
      float         in_fAlphaValue,       // Alpha value used to clear the alpha component of the
                                             // surface. Used only when the surface has an alpha 
                                             // channel. The valid range is [0, 1] 
                                             // inclusive, where 0 is transparent and 1 is opaque.
      unsigned long in_ulThreadPoolIndex  // Index of the thread pool to use to process the 
                                             // operation. This is used only when the operation 
                                             // is done by the CPU.
      ) = 0;

   //
   // Summary:
   //    Modifies the alpha usage of the surface.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   virtual HRESULT __stdcall ChangeAlphaUsage
      (
      bool in_bAlphaUsage  // If true, the alpha of the surface is valid. Otherwise, the
                           // alpha values are overridden with opaque values.
      ) = 0;

   //
   // Summary:
   //    Modifies the colorimetry standard of the surface.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the standard specified is not a valid one. 
   virtual HRESULT __stdcall ChangeColorimetry
      (
      EMvColorimetry in_eColorimetry   // Specifies the new colorimetry standard of the surface.
      ) = 0;

   //
   // Summary:
   //    Modifies the destination position associated with the surface.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Field-based surface only: The vertical position must be an even value. This method will 
   //      convert an odd vertical position to an even vertical position.
   virtual HRESULT __stdcall ChangeDestinationPosition
      (
      SMvPointF * in_psDestinationPosition   // Pointer to the SMvPointF structure that specifies
                                             // the new destination position of the surface. 
      ) = 0;

   //
   // Summary:
   //    Modifies the format of the surface.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the format specified is not valid. 
   //    - MV_E_NOT_SUPPORTED, if the format of the surface cannot be changed to the new surface 
   //      format. For example, a KeMvSurfaceFormatDuDv format cannot be changed to a Z format. 
   // Remarks:
   //    The following format changes are supported: 
   //    - ARGBGraphic to ARGBVideo 
   //    - RGBGraphic to RGBVideo 
   virtual HRESULT __stdcall ChangeFormat
      (
      EMvSurfaceFormat in_eFormat   // Specifies the new surface format.
      ) = 0;

   //
   // Summary:
   //    Modifies the polarity of the surface.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the polarity specified is not valid. 
   //    - MV_E_NOT_SUPPORTED, if the polarity of the surface cannot be changed to the new polarity.
   //      For example, a field surface cannot be changed to frame surface unless it was originally
   //      allocated as a frame. 
   // Remarks:
   //    - The following polarity changes for surfaces in the host or in the I/O memory are supported:
   //    <table>
   //    From               To First  To Second  To Interlaced  To Progressive
   //                        Field     Field      Frame          Frame
   //    -----------------  --------  ---------  -------------  --------------
   //    First Field        Y         Y          Y (note 1)     Y (note 1)
   //    Second Field       Y         Y          Y (note 1)     Y (note 1)
   //    Interlaced Frame   Y         Y          Y              Y
   //    Progressive Frame  Y         Y          Y              Y
   //    </table>
   //    Note 1: A field can be changed to a frame only if the surface was originally allocated as a frame.<p>
   //    - The following supported polarity changes for surfaces in the graphics memory are supported:
   //    <table>
   //    From               To First  To Second  To Interlaced  To Progressive 
   //                        Field     Field      Frame          Frame
   //    -----------------  --------  ---------  -------------  --------------
   //    First Field        Y         Y          N              N
   //    Second Field       Y         Y          N              N
   //    Interlaced Frame   N         N          N              N
   //    Progressive Frame  N         N          N              N
   //    </table> 
   virtual HRESULT __stdcall ChangePolarity 
      (
      EMvPolarity in_ePolarity   // Specifies the new polarity. 
      ) = 0;

   //
   // Summary:
   //    Modifies the data size of a user buffer.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_NOT_SUPPORTED, if the surface is not a user buffer surface. 
   //    - MV_E_REFERENCE_NOT_ASSIGNED, if the user buffer reference has not yet been assigned to
   //      the surface.  
   // Remarks:
   //    - This method can be called only on user buffer surfaces.
   //    - It is possible to change the user buffer data size by calling this method more than once. 
   //    - There's no validation done on the buffer size. The caller must make sure that the new 
   //      buffer size is valid and will not result in an access violation. 
   virtual HRESULT __stdcall ChangeUserBufferDataSize 
      (
      unsigned long in_ulBufferSize // Specifies the new valid size of the user buffer.
      ) = 0;

   //
   // Summary:
   //    Modifies the data size of a surface.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_BUFFER_SIZE_MISMATCH, if the requested size exceeds the allocated size.
   //    - MV_E_REFERENCE_NOT_ASSIGNED, if the user buffer reference has not yet been assigned.
   //    - MV_E_NOT_SUPPORTED, if the surface type prevents data size changes. 
   // Remarks:
   //    - This method can be called only on a surface with format keMvSurfaceFormatMpeg2Transport.
   //    - There's no validation done on the buffer size. The caller must make sure that the new 
   //      buffer size is valid and will not result in an access violation. 
   virtual HRESULT __stdcall ChangeSurfaceDataSize
      (
      unsigned long in_ulBufferSizeInBytes   // Indicates the new memory size in bytes.  The size must be less than or equal 
                                             // to the allocated size of the memory buffer.
      ) = 0;

   //
   // Summary:
   //    Modifies the shape attribute of the video that determines whether or
   //    not the video contained in the surface is shaped.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   virtual HRESULT __stdcall ChangeVideoShape
      (
      bool in_bIsVideoShaped  // If true, the video contained in the surface is shaped. Otherwise, the video is not shaped.
      ) = 0;

   //
   // Summary:
   //    Modifies a surface description without reallocating the associated memory.
   // Description:
   //    This method provides a way to reuse a surface for other uses without needing to allocate
   //    a new one. Apart from the allocated size and memory location, this method completely 
   //    ignores the former surface description, so it must be called before any other operation 
   //    on the surface (before a ChangePolarity call for instance). 
   //    The only restrictions are as follows:
   //    - The new surface description needs to be in the same memory location.
   //    - This method will return an error if called on an alias.
   //    - The new surface description must describe a buffer that is less than, or equal to the 
   //      size of the old buffer. For example, a 32x32 surface cannot be changed to accomodate a
   //      64x64 surface. But, a 64x64 surface can be changed to accomodate a 128x16 surface.
   //    - Only surfaces originally allocated in host memory or in the IO onboard memory, as well as
   //      user buffers can have their description changed. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_NOT_SUPPORTED, if any of the values in the surface description are not supported or
   //      if the method is called on an alias.
   //    - MV_E_UNSUPPORTED_MEMORY_LOCATION, if the surface description is not 
   //      keMvMemoryLocationHost or keMvMemoryLocationIOBoard or if the new memory location is not
   //      in the same location as the originally allocated one. 
   //    - MV_E_BUFFER_SIZE_MISMATCH, if the new surface description would result in a surface size
   //      bigger than the size allocated at creation time. 
   //    - MV_E_INVALID_STRUCTURE_SIZE, if the field size is invalid. 
   // Remarks:
   //    - The field size of the structure must be set before calling the method. 
   virtual HRESULT __stdcall ChangeSurfaceDescription
      (
      SMvCreateSurfaceDescription * in_psDescription  // 
      ) = 0;

   //
   // Summary:
   //    Retrieves the copy engine that is used to copy from one surface to another.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if one of the parameters is NULL. 
   // Remarks:
   //    - If there's no copy engine available to perform a copy operation between the two specified
   //      surfaces, the method will return MV_NOERROR and the out_peCopyEngineID will be filled 
   //      with the invalid type kEMvCopyEngineID_Invalid.
   virtual HRESULT __stdcall GetCopyEngineID
      (
      IMvSurface      * in_pISurfaceSource,  // The source surface IMvSurface interface used for 
                                                // the copy operation.
      EMvCopyEngineID * out_peCopyEngineID   // Pointer to the variable that will receive the copy 
                                                // engine ID.
      ) = 0;

   //
   // Summary:
   //    Retrieves the CRC (Cyclic Redundancy Check) value associated with the surface.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if one of the parameter is NULL. 
   // Remarks:
   //    -  This information can be used for data integrity validation.
   virtual HRESULT __stdcall GetCRC
      (
      unsigned long * out_pulCRC    // Pointer that will receive the CRC value.
      ) = 0;

   //
   // Summary:
   //    This method is obsolete.  Use IMvSurface::GetIOExtraInfo instead.
   //
   virtual HRESULT __stdcall GetLTCInfo
      (
      uint64_t * out_pui64LTC    
      ) = 0;

   //
   // Summary:
   //    This method is obsolete.  Use IMvSurface::SetIOExtraInfo instead.
   //
   virtual HRESULT __stdcall SetLTCInfo
      (
      uint64_t in_ui64LTC     
      ) = 0;

   //
   // Summary:
   //    Retrieves the extra input/output information associated with the surface.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter is NULL.
   //    - MV_E_INVALID_STRUCTURE_SIZE, if the structure size is wrong. 
   virtual HRESULT __stdcall GetIOExtraInfo
      (
      SMvIOExtraInfo * out_psExtraInfo // Pointer that will receive the extra input/output information structure.
      ) = 0;

   //
   // Summary:
   //    Modifies the extra input/output information associated with the surface.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter is NULL. 
   //    - MV_E_INVALID_STRUCTURE_SIZE, if the structure size is wrong. 
   virtual HRESULT __stdcall SetIOExtraInfo
      (
      SMvIOExtraInfo * in_psExtraInfo  // Pointer to the extra input/output information structure.
      ) = 0;

   //
   // Summary:
   //    Modifies the extra input/output information associated with the surface. The information will be verified and set properly.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the parameter is NULL. 
   //    - MV_E_INVALID_STRUCTURE_SIZE, if the structure size is wrong. 
   // Remarks:
   // - At this time, only the Field_flg bit of VITC time code for interlaced video is checked
   virtual HRESULT __stdcall SetIOExtraInfoConform
      (
      SMvIOExtraInfo * in_psExtraInfo  // Pointer to the extra input/output information structure.
      ) = 0;

   //
   // Summary:
   //    Retrieves the information about the surface.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_STRUCTURE_SIZE, if the field Size is invalid. 
   // Remarks:
   //    - The field size of the structure must be filled before calling the method. 
   virtual HRESULT __stdcall GetSurfaceDescription
      (
      SMvSurfaceDescription * io_psDescription  // Pointer to the SMvSurfaceDescription structure
                                                   // that will be filled with the surface
                                                   // description. 
      ) = 0;

   //
   // Summary:
   //    Gets the surface memory pointer.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the mipmap level or the face type is invalid. 
   //    - MV_E_INVALID_STRUCTURE_SIZE, if the field size of the structure does not contain the
   //      right value. 
   // Remarks:
   //    - After retrieving a surface memory pointer, you can access the surface memory until a 
   //      corresponding Unlock() method is called. When the surface is unlocked, the pointer to 
   //      the surface memory is invalid. 
   //    - The field size of the structure must be filled before calling the method. 
   virtual HRESULT __stdcall Lock
      (
      unsigned long               in_ulMipmapLevel,   // Indicates the mipmap level. Must be zero unless
                                                         // a specific mipmap level is required.
      EMvFaceType                 in_eType,           // Indicates the face type. Should be keMvFaceTypeFront
                                                         // unless a specific face of a cube is 
                                                         // required.
      SMvLockSurfaceDescription * out_pDesc           // Pointer to the SMvLockSurfaceDescription 
                                                         // structure that will be filled with the 
                                                         // lock surface description.
      ) = 0;

   //
   // Summary:
   //    Notifies that the direct surface memory manipulations are completed.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the mipmap level or the face type is invalid. 
   virtual HRESULT __stdcall Unlock
      ( 
      unsigned long in_ulMipmapLevel,  // Indicates the mipmap level. Should be zero unless a specific
                                          // mipmap level is required.
      EMvFaceType   in_eFaceType       // Indicates the face type. Must be keMvFaceTypeFront unless a
                                          // specific face of a cube is required.
      ) = 0;

   //
   // Summary:
   //    Modifies the media position and duration associated with the surface's group of pictures (GOP).
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the media duration is greater than the maximum allowed group of
   //      pictures size. 
   // Remarks:
   //    - The maximum GOP size is currently set to 512 frames.
   //    - This information is only used when the surface wraps a GOP.
   //    - The in_ulMediaDuration parameter and in_ulArraySize parameter from SetGroupOfPicturesFrameInfos must be the same.
   virtual HRESULT __stdcall SetGroupOfPicturesInfos
      (
      uint64_t      in_ui64MediaPosition,    // Indicates the media position (in frames) of the GOP.
      unsigned long in_ulMediaDuration       // Indicates the media duration (in frames) of the GOP.
      ) = 0;

   // Summary:
   //    Modifies the information for each frame in the group of pictures (GOP).
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_STRUCTURE_SIZE, if one of the input array's SMvGroupOfPicturesFrame size member is unexpected.
   //    - MV_E_INVALID_PARAMETER, if the array size is zero or the array size is larger than the maximum allowed GOP size.
   // Remarks:
   //    - The maximum GOP size is currently set to 512 frames.
   //    - This information is only used when the surface wraps a GOP.
   //    - The caller should do one set for the entire duration of the GOP. For example, if the GOP contains 15 frames,
   //      in_ulArraySize must be 15.
   virtual HRESULT __stdcall SetGroupOfPicturesFrameInfos
      (
      SMvGroupOfPicturesFrame * in_psArray,     // Pointer to the array describing each frame.
      unsigned long             in_ulArraySize  // Indicates the number of frames in the array.
      ) = 0;

   // Summary:
   //    Gets the media position and duration associated with the surface's group of pictures (GOP).
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if one of the input parameter is NULL.
   // Remarks:
   //    - This information is only used when the surface wraps a GOP.
   virtual HRESULT __stdcall GetGroupOfPicturesInfos
      (
      uint64_t       * out_pui64MediaPosition,  // Pointer to the media position of the GOP (in frames).
      unsigned long  * out_pulMediaDuration     // Pointer to the media duration of the GOP (in frames).
      ) = 0;

   // Summary:
   //    Gets the information for each frame in the group of pictures (GOP).
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_PARAMETER_ARRAY_TOO_BIG, if the input array size is larger than the GOP's media duration (in frames).
   // Remarks:
   //    - This information is only used when the surface wraps a GOP.
   //    - The caller must know the GOP's frame count before calling this method. The array size of this method must be less than or equal to
   //      the GOP size (in_ulArraySize) specified in SetGroupOfPicturesFrameInfos. For example, if the GOP size is 15, the user application must 
   //      call SetGroupOfPicturesFrameInfos with in_ulArraySize set to 15. When GetGroupOfPicturesFrameInfos is called, in_ulArraySize (for GetGroupOfPicturesFrameInfos) must  
   //      be less than or equal to 15.
   virtual HRESULT __stdcall GetGroupOfPicturesFrameInfos
      ( 
      SMvGroupOfPicturesFrame * io_pArray,      // Pointer to the array describing each frame.
      unsigned long             in_ulArraySize  // Indicates the number of frames in the array.
      ) = 0;

   // Summary:
   //    Defines which region of a reference surface the alias surface displays.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_REFERENCE_NOT_ASSIGNED, if no reference has been assigned to this alias.
   //    - MV_E_INCOMPATIBLE_WIDTH, if region width exceeds reference surface width.
   //    - MV_E_INCOMPATIBLE_HEIGHT, if region height exceeds reference height.
   //    - MV_E_INVALID_POLARITY, if original reference surface polarity is not 
   //          first field, second field, or progressive frame.
   //    - MV_E_INVALID_PARAMETER, if one of the parameters is not valid.
   //    - MV_E_ORIGIN_NOT_ALIGNED_WITH_FORMAT_GRANULARITY, if origin horizontal coordinate 
   //          does not respect the granularity of the surface format (i.e. YUV422 always 
   //          requires groups of 2 pixels).
   //    - MV_E_NOT_SUPPORTED, if this method is called on a surface which is not an alias or if a
   //          combination of parameters is not supported.
   //    - MV_E_NONZERO_HORIZONTAL_OFFSET_NOT_SUPPORTED_FOR_IO, if this method is called
   //          on an IO surface, horizontal coordinate of the origin must be 0.
   //    - MV_E_UNSUPPORTED_COMPRESSION_TYPE, if this method is called on a surface of
   //          compressed format.
   //    - MV_E_UNSUPPORTED_COMPONENT_BIT_COUNT, if the component bit count of the surface is
   //          not compatible with the current configuration.
   //    - MV_E_UNSUPPORTED_SURFACE_FORMAT, if the surface format is not compatible
   //          with the current configuration.
   // Remarks:
   //    - This method will return an error if called on a surface which is not an alias.
   //    - At all times, the region must be contained within the limits of the reference surface.
   //    - Asked origin offset must respect format granularity (for instance, YUAYVA 8-bit surfaces
   //      must have 16 pixel groups only)
   //    - For IO surfaces, horizontal origin offset must always be 0.
   //    - For IO surfaces, the requested width (in_ulWidth) must always be a full line.
   //    - There are some hardware specific limitations to the origin that can be passed to this
   //          method. Refer to the <i>Matrox DSX.sdk User Guide</i> for more information about your hardware.
   virtual HRESULT __stdcall SetAliasRegion
      (
      SMvPoint in_ptOriginInPixels, // Indicates the origin in pixels from the upper left corner of the reference surface.
      unsigned long in_ulWidth,     // Indicates the width in pixels of the region.
      unsigned long in_ulHeight     // Indicates the height in pixels of the region.
      ) = 0;

   // Summary:
   //    Modifies the temporal compression to be changed.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_POINTER, if in_psInfo is NULL.
   //    - MV_E_INVALID_STRUCTURE_SIZE, if the size of in_psInfo is detected as being invalid.
   // Remarks:
   //    - The caller can retrieve the surface's temporal compression by calling GetSurfaceDescription.
   virtual HRESULT __stdcall ChangeTemporalCompressionInfo
      (
      SMvTemporalCompressionInfo* in_psInfo  // Pointer to the structure containing the new temporal compression information.
      ) = 0;

   //
   // Summary:
   //    Modifies the surface's internal scan mode.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_REFERENCE_NOT_ASSIGNED, if the surface is an alias or user buffer, it must have a reference assigned to it before the scan mode is changed.
   //    - MV_E_UNSUPPORTED_MEMORY_LOCATION, if the surface memory is unexpectedly not available.
   virtual HRESULT __stdcall ChangeScanMode
      (
      EMvScanMode in_eScanMode // Specifies the scan mode.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Allows the management of an audio sample container. The container encapsulates an audio data 
//    buffer and all related information. 
// Remarks:
//    - This interface supports the following query interfaces: IID_IMvAVContent. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvAudioSamples : public IMvAVContent
{
   //
   // Summary:
   //    Assigns the reference audio sample container to an audio sample container alias. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the input parameter is NULL. 
   //    - MV_E_NOT_SUPPORTED, if the surface is not a surface alias (created with CreateSurfaceAlias()). 
   // Remarks:
   //    - The container alias inherits all the properties of the reference container. The memory 
   //      contained in the reference surface is also shared with the surface alias. This method can
   //      be called only on alias audio samples.
   //    - The alias and the reference container have separate synchronization objects that are 
   //      linked internally. Each time a component increments the synchronization read count of the
   //      alias, the read or write count of the reference container is automatically incremented.
   //      Each SignalReadCompletion operation performed on the alias automatically calls the
   //      SignalReadCompletion() method on the reference. Also, each SignalWriteCompletion 
   //      operation performed on the alias automatically calls the SignalWriteCompletion() method
   //      on the reference. 
   //    - If the alias access type is ReadOnly (keMvAliasAccessTypeReadOnly), the write completion on the alias event will be 
   //      signaled automatically when the write completion event of the reference is signaled. 
   //    - It is possible to change the alias reference by calling this method more than once.
   //      However, the alias must be flushed before assigning a new reference. 
   //    - The reference audio samples buffer must be usable at the time of assignment. Therefore,
   //      an empty user buffer or an unset alias cannot be assigned as the reference of an alias.
   //      Once a user buffer has been set with AssignUserBufferReference and has been assigned as the  
   //      reference of an alias it cannot be changed using AssignUserBufferReference() until it has been flushed.
   //    - It is possible to assign an alias on an alias, as long as the reference alias has a valid
   //      reference attached to it.  
   virtual HRESULT __stdcall AssignAliasReference
      (
      IMvAudioSamples  * in_pIReferenceAudioSamples,  // Pointer to the IMvAudioSamples interface
                                                      // that is the reference of the audio sample
                                                      // container alias.
      EMvAliasAccessType in_eAccessType   // Access type required for the alias. Use keMvAliasAccessTypeReadOnly if the alias is not 
                                          // intended to be written to any modules. Otherwise, use keMvAliasAccessTypeReadWrite. 
       ) = 0;

   //
   // Summary:
   //    Assigns a host-memory buffer previously allocated to a user buffer audio sample.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if in_psDescription is NULL. 
   //    - MV_E_NOT_SUPPORTED, if the container is not a user buffer container. 
   // Remarks:
   //    - This method can be called only on user buffer audio samples.
   //    - It is possible to change the user buffer reference by calling this method more than once. 
   virtual HRESULT __stdcall AssignUserBufferReference
      (
      SMvUserBufferAudioSamplesDescription * in_psDescription  // Pointer to the structure of the user buffer audio samples description to encapsulate. 
      ) = 0;

   //
   // Summary:
   //    Modifies the polarity of the audio samples.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the polarity specified is not a valid one. 
   //    - MV_E_NOT_SUPPORTED, if the polarity of the surface cannot be changed to the desired 
   //      polarity. For example, a field surface cannot be recycled into a frame. 
   // Remarks:
   //    - The supported polarity changes for surfaces in host or I/O memory are as follows:
   //<table>
   // From               To First  To Second  To Interlaced    To Progressive
   //                     Field     Field      Frame (note 2)   Frame (note 2)
   // -----------------  --------  ---------  ---------------  ---------------
   // FirstField         Y         Y          Y (note 1)       Y (note 1)
   // SecondField        Y         Y          Y (note 1)       Y (note 1)
   // InterlacedFrame    Y         Y          Y                Y
   // ProgressiveFrame   Y         Y          Y                Y
   // </table>
   // Note 1: A field can be changed to a frame only if the audio samples were originally allocated as a
   //         frame.<p>
   // Note 2: When capturing audio using the DSX hardware, only the difference between 'FirstField' and 'SecondField' values
   //         are significant. All other values are ignored. 
   virtual HRESULT __stdcall ChangePolarity
      (
      EMvPolarity in_ePolarity   // Specifies the new polarity wanted. 
      ) = 0;
   
   //
   // Summary:
   //    Modifies the wave format of the audio samples.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the container for the buffer pointer is NULL or the container
   //      for the length is NULL. 
   // Remarks:
   //    - The byte length of the buffer is not changed when calling ChangeWaveFormat(). This means that 
   //      when a 16-track, 24 in 32-bit audio sample buffer with a length of 800 samples (51200 bytes) is
   //      changed into an 8-track, 24 in 32-bit audio sample buffer, the length of 51200 bytes stays the
   //      same but processes 1600 samples.
   virtual HRESULT __stdcall ChangeWaveFormat
      (
      SMvaWaveFormatInfo * in_psWaveFormat // Pointer to the SMvaWaveFormatInfo structure that
                                          // specifies the new wave format wanted.
      )=0;

   //
   // Summary:
   //    Sets the audio samples to zero.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_FAIL, if an internal error occurs. 
   // Remarks:
   //    - <b>This method DOES NOT handle synchronization properly.  The IMvAVContent::SignalWriteCompletion()
   //      method is not called at the end of the execution.</b>
   //
   virtual HRESULT __stdcall Clear () = 0;
   
   //
   // Summary:
   //    Gets information about the audio sample container/buffer. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_STRUCTURE_SIZE, if the field size of the structure does not contain the
   //      right value. 
   // Remarks:
   //    - SMvAudioSamplesDescription::size must be filled before calling the method. 
   virtual HRESULT __stdcall GetAudioSamplesDescription 
      ( 
      SMvAudioSamplesDescription * io_psDescription   // Pointer to the SMvAudioSamplesDescription 
                                                      // structure that is filled with the audio
                                                      // sample container description. 
      ) = 0;  

   //
   // Summary:
   //    Gets the audio sample buffer pointer and the length of valid data.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the container for the buffer pointer is NULL or the
   //      container for the length is NULL. 
   // Remarks:
   //    - The length returned is the length of the valid data for the corresponding pointer. This
   //      value can be zero if there is no valid data in this buffer. 
   virtual HRESULT __stdcall GetBufferAndLength
      (
      void         ** out_ppBuffer, // Pointer that receives the buffer's pointer. 
      unsigned long * out_pulLength // Pointer to the size (in bytes) of valid data in the buffer.
      ) = 0;

   //
   // Summary:
   //    Gets the maximum valid length of the data pointer.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the container for the maximum length is NULL. 
   // Remarks:
   //    - The length returned is the maximum length available for writing. 
   virtual HRESULT __stdcall GetMaxLength
      (
      unsigned long * out_pulMaxLength // Pointer to the maximum size (in bytes) of the allocated buffer.
      ) = 0;

   //
   // Summary:
   //    Gets the valid data length of the buffer in samples using the valid buffer length and
   //    format information already contained in the object.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the container for the buffer pointer is NULL or the container
   //      for the length is NULL. 
   // Remarks:
   //    - The length returned is the length of the valid data for the corresponding pointer. This
   //      value can be zero if there is no valid data in this buffer. 
   virtual HRESULT __stdcall GetValidBufferLengthInSamples 
      (
      unsigned long * out_ulLengthInSamples  // Pointer to the length of valid data in samples. 
      )= 0;
   
   //
   // Summary:
   //    Sets the fade-in status on the audio sample container.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - When using the Matrox DSX.sdk API, the fade-in is applied with IMvFlexEngine::CopyAudioSamples. 
   virtual HRESULT __stdcall SetFadeIn 
      (
      bool in_bHasFadeIn   // If true, applies the fade-in when the audio sample buffer is copied.
      ) = 0;

   //
   // Summary:
   //    Sets the fade-out status on the audio sample container.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - When using the Matrox DSX.sdk API, the fade-out is applied with IMvFlexEngine::CopyAudioSamples. 
   virtual HRESULT __stdcall SetFadeOut
      (
      bool in_bHasFadeOut  // If true, applies the fade-out when the audio sample buffer is copied.
      ) = 0;

   //
   // Summary:
   //    Sets the length of valid data for the buffer pointer.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if the length is larger than the maximum length. 
   // Remarks:
   //    - The length of valid data must not be larger than the maximum allocated buffer length. 
   virtual HRESULT __stdcall SetLength 
      (
      unsigned long in_ulLength  // Indicates the length of valid data (in bytes) for the buffer pointer.
      )= 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates the available hardware (as a hardware profile) on the DSX system.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvHardwareProfileEnumerator : public IUnknown
{
   //
   // Summary:
   //    Gets the next available hardware profile installed on the system. 
   // Description:
   //    The field bIsAvailable of SMvEnumHardwareProfileInfo indicates whether or not the hardware profile is available. A 
   //    hardware profile is not available when another process is using it. A software-only profile 
   //    is always available.
   // Return value:
   //    - MV_NOERROR, if properly filled. 
   //    - MV_E_END_OF_ENUM, if there is no more hardware profile information to enumerate. 
   //    - MV_E_INVALID_STRUCTURE_SIZE, if the structure size of out_psEnumHardwareProfileInfo is not initialized properly. 
   virtual HRESULT __stdcall Next
      ( 
      unsigned long in_ulNbEnumHardwareProfileInfoRequested,   // Number of entries in the card information array.
      SMvEnumHardwareProfileInfo out_psEnumHardwareProfileInfo[], // Pointer to the array of structures that contains information on enumerated hardware profiles.
      unsigned long * out_pulEnumHardwareProfileInfoFetched // Pointer to the number of entries that have been filled in the array.
      ) = 0;

   //
   // Summary:
   //    Resets the internal counter to the first hardware profile.
   // Description:
   //    The internal pointer is reset so that the next call to IMvHardwareProfileEnumerator::Next returns the first hardware 
   //    profile in the internal list.
   // Return value:
   //    - Always returns MV_NOERROR. 
   virtual HRESULT __stdcall Reset () = 0;

   //
   // Summary:
   //    Skips a given number of hardware profiles.
   // Description:
   //    The internal pointer is changed so that the next call to IMvHardwareProfileEnumerator::Next skips a given number of hardware 
   //    profiles in the internal list.
   // Return value:
   //    - Always returns MV_NOERROR. 
   virtual HRESULT __stdcall Skip
      (
      unsigned long in_ulCount   // Number of hardware profiles to skip.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates all effects installed on the system.
//
//////////////////////////////////////////////////////////////////////////////////

interface IMvEffectEnumerator: public IUnknown
{
   //
   // Summary:
   //    Gets the next available effect installed on the system.
   // Description:
   // The next effect installed on the system is retrieved from the internal list of effects.
   // Return value:
   //    - MV_NOERROR, if properly filled. 
   //    - MV_E_END_OF_ENUM, if there is no more effect information to enumerate. 
   //    - MV_E_INVALID_STRUCTURE_SIZE, if the structure size of out_psEffectCapabilities is not initialized properly. 
   virtual HRESULT __stdcall Next
      ( 
      unsigned long in_ulNbEffectCapsRequested, // Number of entries in the effect information structure.
      SMvEffectCapabilities * out_pDEffectCaps, // Pointer to the array of structures describing the effect capabilities.
      unsigned long * out_pulEffectCapsFetched  // Pointer to the number of entries that have been filled in the array of structures.
      ) = 0;

   //
   // Summary:
   //    Resets the internal counter to the first effect found on the system.
   // Description:
   //    The internal pointer is reset so that the next call to IMvEffectEnumerator::Next returns the first effect found on the system.
   // Return value:
   //    - Always returns MV_NOERROR. 
   virtual HRESULT __stdcall Reset () = 0;

   //
   // Summary:
   //    Skips a given number of effects.
   // Description:
   //    The internal pointer is changed so that the next call to IMvEffectEnumerator::Next skips a given number of effects in the internal list.
   // Return value:
   //    - Always returns MV_NOERROR. 
   virtual HRESULT __stdcall Skip 
      (
      unsigned long in_ulCount   // Number of effects to skip.
      ) = 0;

};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Controls all parameters and services on the input and output devices for audio and video.
// Remarks:
//    This interface can be obtained through the IMvInputOutput::GetIODeviceInterface and IMvInputOutputIndependent::GetIODeviceInterface. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvIODeviceControl : public IUnknown
{
   //
   // Summary:
   //    Controls all video input parameters.
   // Return value:
   //    - Returns an error if the command fails.
   virtual HRESULT __stdcall ControlVideoInput
      (
      EMvIOCommand            in_eIOCommand,    // Specifies the control command to set or retrieve.
      EMvVideoInputParameter  in_eInputParam,   // Specifies the input parameter to set or retrieve.
      void*                   io_pParam,        // Points to a parameter that contains values to 
                                                   // set or retrieve. Can be either an SMvIORange pointer 
                                                   // for keIOCommandGetRange or a value pointer as
                                                   // described in EMvVideoInputParameter.
      unsigned int            in_uiSizeOfParam, // Specifies the size of the passed parameter.
      EMvVideoIOChannel       in_eChannel       // Specifies the control channel to set or retrieve.
      ) = 0;

   //
   // Summary:
   //    Controls all video output parameters.
   // Return value:
   //    - Returns an error if the command fails, or if there are bad parameters. 
   
   virtual HRESULT __stdcall ControlVideoOutput
      (
      EMvIOCommand            in_eIOCommand,    // Specifies the control command to set or retrieve.
      EMvVideoOutputParameter in_eOutputParam,  // Specifies the output parameter to set or retrieve.
      void*                   io_pParam,        // Points to a parameter that contains values to
                                                   // set or retrieve. Can be either an SMvIORange pointer
                                                   // for keIOCommandGetRange or a value pointer as
                                                   // described in EMvVideoOutputParameter.
      unsigned int            in_uiSizeOfParam, // Specifies the size of the passed parameter.
      EMvVideoIOChannel       in_eChannel       // Specifies the control channel to set or retrieve.
      ) = 0;

   //
   // Summary:
   //    Controls the video source at the input. 
   // Return value:
   //    - Returns an error if the command fails.
   virtual HRESULT __stdcall ControlVideoSource
      (
      EMvIOCommand      in_eIOCommand,       // Specifies the control command to set or retrieve. 
                                                // keIOCommandGetRange is not supported with video source
                                                // control. The supported source types are available
                                                // with a GetIOInfo() call.
      EMvVideoSignal*   in_peVideoSource,    // Specifies the video source to set or retrieve.
      unsigned int*     io_puiSourceIndex,   // Specifies the index of the source type. Reserved for
                                                // future use. Set it to NULL.
      EMvVideoIOChannel in_eChannel          // Specifies the control channel to set or retrieve.
      ) = 0;

   //
   // Summary:
   //    Retrieves  information on various I/O items.
   // Return value:
   //    - Returns an error if the command fails.
   // Description:
   //    This table indicates the type of parameters to pass depending on the requested information:
   //    <table>
   //    EMvIOInfo              Structure pointer     Channel
   //    ---------------------  --------------------  -------------------------
   //    keIOInfoVideo          SMvVideoIOInfo        EMvVideoIOChannel
   //    keIOInfoGenlock        SMvGenlockInfo        n/a
   //    keIOInfoAudio          SMvAudioIOInfo        EMvAudioIOChannel
   //    keIOInfoEmbeddedAudio  SMvEmbeddedAudioInfo  EMvEmbeddedAudioIOChannel
   //    keIOInfoAudioCapture   SMvAudioCaptureInfo   EMvAudioCaptureChannel
   //    keIOInfoMisc           SMvMiscInfo           n/a
   //    </table>
   virtual HRESULT __stdcall GetIOInfo
      (
      EMvIOInfo      in_eIOInfo,       // Specifies the information to retrieve.
      void*          out_pParam,       // Points to the structure that will be filled with 
                                          // information. See the table to determine which
                                          // pointer to pass here.
      unsigned int   in_uiSizeOfParam, // Specifies the size of the passed structure.
      unsigned int   in_uiChannel      // Specifies the control channel on which the information is retrieved. 
                                          // See the table to determine which channel to pass here.
      ) = 0;

   //
   // Summary:
   //    Retrieves the status ofvarious I/O items.
   // Return value:
   //    - Returns an error if the command fails.
   // Remarks:
   //    - To get a valid extraction format status, a group and pair must be extracted into an 
   //      embedded audio channel first with the ControlEmbeddedAudioExtraction() function.
   // Description:
   //    This table indicates the type of parameters to pass depending on the requested information:
   //    <table>
   //    EMvIOStatus                              Parameter pointer             Channel
   //    ---------------------------------------  ----------------------------  -------------------------
   //    keIOStatusVideo                          SMvVideoStatus                EMvVideoIOChannel
   //    keIOStatusGenlock                        SMvGenlockStatus              n/a
   //    keIOStatusEmbeddedAudio                  SMvEmbeddedAudioStatus        n/a 
   //    keIOStatusEmbbededAudioExtractionFormat  EMvAudioBitsPerSample         EMvEmbeddedAudioIOChannel
   //    keIOStatusAudioTimeBase                  SMvAudioTimeBaseStatus        n/a
   //    keIOStatusAesEbuAudio                    SMvAesEbuAudioStatus          n/a 
   //    keIOStatusAesEbuChannelStatus            SMvDigitalAudioChannelStatus  EMvAesEbuAudioIOChannel
   //    keIOStatusDVI                            SMvDviStatus                  n/a
   //    </table>
   virtual HRESULT __stdcall GetIOStatus
      (
      EMvIOStatus    in_eIOStatus,     // Specifies the status of the I/O item. 
      void*          out_pParam,       // Points to a structure or enumeration that will be filled
                                          // with information. See the table to determine 
                                          // which pointer to pass here.
      unsigned int   in_uiSizeOfParam, // Specifies the size of the structure passed.
      unsigned int   in_uiChannel      // Specifies the control channel on which the information is retrieved. See the
                                          // table to determine which channel to pass here.
      ) = 0;

   //
   // Summary:
   //    Registers to a specific notification.
   // Return value:
   //    - Returns an error if the command fails.
   // Remarks:
   //    - These notifications are signaled every time there is a change in the IODevice. More 
   //      than one process can register to the same notification. After the return of the call, 
   //      the process must call OpenEvent() on the returned event name. After having been signaled,
   //      a process can get the corresponding status of the IODevice with the GetIOStatus() 
   //      function. 
   // Description:
   //    This table indicates the type of parameters to pass depending on the requested registration:
   //    <table>
   //    EMvIOEvent              Corresponding IOStatus
   //    ----------------------  -----------------------
   //    keIOEventGenlock        keIOStatusGenlock 
   //    keIOEventVideo          keIOStatusVideo 
   //    keIOEventAudioTimeBase  keIOStatusAudioTimeBase 
   //    keIOEventEmbeddedAudio  keIOStatusEmbeddedAudio
   //    keIOEventWatchDog       n/a
   //    keIOEventAesEbuAudio    keIOStatusAesEbuAudio and keIOStatusAesEbuChannelStatus
   //    keIOEventDVI            keIOStatusDVI
   //    </table>
   virtual HRESULT __stdcall RegisterForNotification
      (
      EMvIOEvent     in_eIOEvent,      // Specifies the event type to register to.
      void*          in_pParam,        // Reserved for future use. Set to NULL. 
      unsigned int   in_uiSizeOfParam, // Reserved for future use. Set to NULL.
      char*          out_pstrEventName // This string is filled with the name of the event to wait on.
      ) = 0;

   //
   // Summary:
   //    Unregisters a registered event.
   // Return value:
   //    - Returns an error if the command fails.
   virtual HRESULT __stdcall UnRegisterForNotification
      (
      EMvIOEvent in_eIOEvent  // Specifies the event type to unregister.
      ) = 0;

   //
   // Summary:
   //    Controls all analog audio input parameters.
   // Return value:
   //    - Returns an error if the command fails.
   virtual HRESULT __stdcall ControlAnalogAudioInput
      (
      EMvIOCommand                 in_eIOCommand,     // Specifies the control command to set or retrieve.
      EMvAnalogAudioInputParameter in_eInputParam,    // Specifies the input parameter to set or retrieve.
      void*                        io_pParam,         // Pointer to a parameter that contains values
                                                         // to set or retrieve. Can be either an 
                                                         // SMvIORange pointer for keIOCommandGetRange
                                                         // or a value pointer as described in
                                                         // EMvAnalogAudioInputParameter.
      unsigned int                 in_uiSizeOfParam,  // Specifies the size of the passed parameter.
      EMvAudioIOChannel            in_eChannel        // Specifies the control channel to set or retrieve.
      ) = 0;

   //
   // Summary:
   //    Controls all analog audio output parameters.
   // Return value:
   //    - Returns an error if the command fails. 
   // Remarks:
   //    - The output impedance parameter controls the impedance of the balanced connectors for
   //      both the left and right channels at the same time, so any EMvAudioIOChannel is accepted.   
   virtual HRESULT __stdcall ControlAnalogAudioOutput
      (
      EMvIOCommand                  in_eIOCommand,    // Specifies the control command to set or retrieve.
      EMvAnalogAudioOutputParameter in_eOutputParam,  // Specifies the output parameter to set or retrieve.
      void*                         io_pParam,        // Pointer to a parameter that contains values 
                                                         // to set or retrieve. Can be either an SMvIORange
                                                         // pointer for keIOCommandGetRange or a
                                                         // value pointer as described in
                                                         // EMvAnalogAudioOutputParameter.
      unsigned int                  in_uiSizeOfParam, // Specifies the size of the passed parameter.
      EMvAudioIOChannel             in_eChannel       // Specifies the control channel to set or retrieve.
      ) = 0;

   //
   // Summary:
   //    Controls all analog audio sources.
   // Description:
   //     The method selects the analog audio stream type that is input to the hardware. 
   // Return value:
   //    - Returns an error if the command fails.
   virtual HRESULT __stdcall ControlAnalogAudioSource
      (
      EMvIOCommand         in_eIOCommand,       // Specifies the control command to set or retrieve.
                                                   // keIOCommandGetRange is not supported with
                                                   // analog audio source control. The supported source types are
                                                   // available with a GetIOInfo() call.
      EMvAnalogAudioSource in_eAudioSource,     // Specifies the type of source to control.
      unsigned int*        io_puiSourceIndex,   // Specifies the index of the source type. Reserved
                                                   // for future use, set it to NULL.
      void*                io_pParam,           // Points to a parameter that contains values to 
                                                   // set or retrieve. Can be either an SMvIORange
                                                   // pointer for keIOCommandGetRange or a value
                                                   // pointer as described in EMvAnalogAudioSource.
      unsigned int         in_uiSizeOfParam     // Specifies the size of the passed parameter.
      ) = 0;

   //
   // Summary:
   //    Selects the embedded audio input groups and pairs that are extracted from the SDI input
   //    stream. 
   // Return value:
   //    - Returns an error if the command fails.
   // Remarks:
   //    - You can extract the same group/pair on more than one channel at the same time.   
   virtual HRESULT __stdcall ControlEmbeddedAudioExtraction
      (
      EMvIOCommand              in_eIOCommand,  // Specifies the control command to set or retrieve.
                                                   // keIOCommandGetRange is not supported with 
                                                   // embedded audio extraction control. The supported source types
                                                   // are available with a GetIOInfo call.
      EMvEmbeddedAudioPair*     io_pePair,      // Points to an enum EMvEmbeddedAudioPair that 
                                                   // contains values to set or retrieve.
      EMvEmbeddedAudioGroup*    io_peGroup,     // Points to an enum EMvEmbeddedAudioGroup that
                                                   // contains values to set or retrieve.
      EMvEmbeddedAudioIOChannel in_eChannel     // Specifies the embedded channel to control.
      ) = 0;

   //
   // Summary:
   //    Selects the embedded audio output groups that are inserted in the SDI output stream. 
   // Return value:
   //    - Returns an error if the command fails. 
   // Remarks:
   //    - Channels are inserted in tandem (AB or CD) in the same group. Channels A and C are always
   //      inserted in pair 1 and channels B and D are always inserted in pair 2. You cannot select
   //      the same group for channels AB and CD. 
   virtual HRESULT __stdcall ControlEmbeddedAudioInsertion
      (
      EMvIOCommand              in_eIOCommand,  // Specifies the control command to set or retrieve.
                                                   // keIOCommandGetRange is not supported with
                                                   // embedded audio insertion control. The supported source types 
                                                   // are available with a GetIOInfo() call.
      EMvEmbeddedAudioGroup*    io_peGroup,     // Points to an enum EMvEmbeddedAudioGroup that 
                                                   // contains values to set or retrieve.
      EMvEmbeddedAudioIOChannel in_eChannel     // Specifies the embedded channel to control.
      ) = 0;

   //
   // Summary:
   //    Controls the embedded audio output parameters.
   // Return value:
   //    - Returns an error if the command fails. 
   // Remarks:
   //    - keEmbAudParamGeneralInsertion controls all embedded audio channels at the same time. To
   //      control audio insertion for an individual channel, use keEmbAudParamInsertionControl. 
   //    - keEmbAudParamOutputFormat controls all embedded audio channels at the same time. There is 
   //      no control for an individual channel. 
   virtual HRESULT __stdcall ControlEmbeddedAudioOutput
      (
      EMvIOCommand               in_eIOCommand, // Specifies the control command to set or retrieve.

      EMvEmbeddedAudioOutputParameter in_eOutputParam,   // Specifies the output parameter to set
                                                         // or retrieve.
      void * io_pParam,    // Points to a parameter that contains values to set or retrieve. Can be 
                           // either an SMvIORange pointer for keIOCommandGetRange or a value 
                           // pointer as described in EMvEmbeddedAudioOutputParameter.
      unsigned int              in_uiSizeOfParam,  // Specifies the size of the passed parameter.
      EMvEmbeddedAudioIOChannel in_eChannel        // Specifies the embedded channel to control.
      ) = 0;

   //
   // Summary:
   //    Selects the source to capture on the desired channel. 
   // Return value:
   //    - Returns an error if the command fails.
   virtual HRESULT __stdcall ControlCaptureAudioSource
      (
      EMvIOCommand            in_eIOCommand,       // Specifies the control command to set or retrieve.
                                                      // keIOCommandGetRange is not supported with 
                                                      // CaptureAudioSource control. The supported source types 
                                                      // are available with a GetIOInfo() call.
      EMvCaptureAudioSource * io_peCaptureSource,  // Specifies the parameter to set or retrieve.
      EMvAudioCaptureChannel  in_eChannel          // Specifies the capture channel to control.
      ) = 0;

   //
   // Summary:
   //    Controls all digital audio parameters.
   // Return value:
   //    - Returns an error if the command fails.
   virtual HRESULT __stdcall ControlDigitalAudio
      (
      EMvIOCommand				   in_eIOCommand,    // Specifies the control command to set or retrieve.
      EMvDigitalAudioParameter   in_eDigitalParam, // Specifies the digital parameter to set or retrieve.
      void*						      io_pParam,        // Pointer to a parameter that contains values 
                                                      // to set or retrieve. Can be either an
                                                      // SMvIORange pointer for keIOCommandGetRange 
                                                      // or a value pointer as described in
                                                      // EMvDigitalAudioParameter.
      unsigned int					in_uiSizeOfParam  // Specifies the size of the passed parameter.
      ) = 0;

   //
   // Summary:
   //    Selects the output source for a particular AES/EBU output.
   // Return value:
   //    - Returns an error if the command fails. 
   virtual HRESULT __stdcall ControlAesEbuAudioInsertion
      (
      EMvIOCommand in_eIOCommand,   // Specifies the control command to set or retrieve.
                                    // keIOCommandGetRange is not supported with AES/EBU audio insertion control.
                                    // The supported source types are available with a GetIOInfo()
                                    // call.
      void*                   io_pParam,  // Points to a parameter that contains values
                                          // to set or retrieve. It can either be an SMvIORange pointer 
                                          // for keIOCommandGetRange or a value pointer. For an X.linkHD, this
                                          // parameter should be an EMvAudioPath pointer.
      unsigned int            in_uiSizeOfParam,    // Specifies the size of the passed parameter.
      void*                   io_pParam2, // Points to a parameter that contains values to set or 
                                          // retrieve. Can be either an SMvIORange pointer for 
                                          // keIOCommandGetRange or a value pointer. For 
                                          // an X.linkHD, this parameter is not used and should be 
                                          // NULL.
      unsigned int            in_uiSizeOfParam2,   // Specifies the size of the passed parameter.
      EMvAesEbuAudioIOChannel in_eChannel          // Specifies the AES/EBU channel used.
      ) = 0;

   //
   // Summary:
   //    Controls the AES/EBU audio output parameters.
   // Return value:
   //    - Returns an error if the command fails. 
   virtual HRESULT __stdcall ControlAesEbuAudioOutput
      (
      EMvIOCommand in_eIOCommand,   // Specifies the control command to set or retrieve.
                                    // keIOCommandGetRange is not supported with AES/EBU audio output control.
                                    // The supported source types are available with a GetIOInfo() 
                                    // call.
      EMvAesEbuAudioOutputParameter in_eOutputParam,  // Specifies the AES/EBU audio output 
                                                      // parameter to set or retrieve.

      void * io_pParam, // Pointer to a parameter that contains values to set or retrieve. Can be either 
                        // an SMvIORange pointer for keIOCommandGetRange or a value pointer as 
                        // described in EMvAesEbuAudioOutputParameter.

      unsigned int                  in_uiSizeOfParam, // Specifies the size of the passed parameter.
      EMvAesEbuAudioIOChannel       in_eChannel       // Specifies the AES/EBU channel used.
      ) = 0;

   //
   // Summary:
   //    Controls all HDMI audio output parameters.
   // Return value:
   //    - Returns an error if the command fails. 
   // Remarks:
   virtual HRESULT __stdcall ControlHdmiAudioOutput
      (
      EMvIOCommand                  in_eIOCommand,    // Specifies the control command to set or retrieve.
      EMvHdmiAudioOutputParameter   in_eOutputParam,  // Specifies the output parameter to set or retrieve.
      void*                         io_pParam,        // Pointer to a parameter that contains values 
                                                      // to set or retrieve. Can be either an SMvIORange
                                                      // pointer for keIOCommandGetRange or a
                                                      // value pointer as described in
                                                      // EMvHdmiAudioOutputParameter.
      unsigned int                  in_uiSizeOfParam, // Specifies the size of the passed parameter.
      EMvHdmiAudioIOChannel         in_eChannel       // Specifies the control channel to set or retrieve.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Controls the effect settings for every effect.
//
//////////////////////////////////////////////////////////////////////////
interface IMvEffectSettings 
: public IUnknown
{
   //
   // Summary:
   //    Returns the version of the effect settings.
   // Return value:
   //    - Version of the effect settings. 
   virtual uint32_t __stdcall GetVersion(void) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Controls genlock parameters and services. 
// Remarks:
//    This interface can be obtained via the IMvInputDevices interface and is only available after 
//    the resolution has been determined. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvGenlockControl : public IUnknown
{
   //
   // Summary:
   //    Used to get the supported genlock source(s).
   // Return value:
   //    - Returns an error if the command fails.
   virtual HRESULT __stdcall GetSupportedGenlockSources
      (
      EMvGenlockSource * out_peSupportedGenlockSources   // Returns a bitwise enumeration of all 
                                                         //supported genlock source(s).
      ) = 0;

   //
   // Summary:
   //    Controls all parameters to configure genlock sources.
   // Return value:
   //    - Returns an error if the command fails.
   virtual HRESULT __stdcall ControlGenlockSource
      (
      EMvIOCommand      in_eIOCommand,       // Specifies the control command to set or get.
                                                // keIOCommandGetRange is not supported with source
                                                // control, the supported source types are available
                                                // with a GetSupportedGenlockSources call.
      EMvGenlockSource* in_peGenlockSource,  // Specifies the genlock source to set or get.
      unsigned int*     io_puiSourceIndex    // Specifies the index of the source.
      ) = 0;

   //
   // Summary:
   //    Controls all parameters to configure genlock parameters.
   // Return value:
   //    - Returns an error if the command fails.
   virtual HRESULT __stdcall ControlGenlock
      (
      EMvIOCommand         in_eIOCommand,    // Specifies the control command to set or get.
      EMvGenlockParameter  in_eGenlockParam, // Specifies the genlock parameter to set or get.
      void*                io_pParam,        // Pointer to a parameter that contains values to set
                                                // or to get. Can be either an SMvIORange pointer 
                                                // for keIOCommandGetRange or a value pointer as
                                                // described in EMvGenlockParameter.
      unsigned int         in_uiSizeOfParam  // Specifies the size of the passed parameter.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    The application must query the VU meter interface to get access to the object.
//
//////////////////////////////////////////////////////////////////////////
interface IMvVuMeter : public IUnknown
{
   //
   // Summary:
   //    Instructs the VU meter module to calculate the metering values and return the results in 
   //    the output structure.
   // Return value:
   // - MV_NOERROR, if operation is successful. 
   // - MV_E_INVALID_PARAMETER, if buffer is NULL. 
   // - MV_E_INVALID_PARAMETER, if the buffer size is 0. 
   // - MV_E_INPUT_FORMAT_NOT_SUPPORTED, if the buffer format is not the list of known formats for 
   //   the VU meter. 
   // Remarks:
   // - Compatible with 16-bit stereo audio samples only. 
   // - The results of the VU meter calculations are returned in the output structure. 
   // - The application must allocate the output structure. 
   virtual HRESULT __stdcall ProcessVuMeterValueStereo
      (
      IMvAudioSamples*              in_pIAudioSamples,   // Input audio samples to process.
      SMvAudioVuMeterValueStereo*   io_psOutputVuValue   // Output VU-metering value including
                                                            // clipping and peak information.
      )=0;

   //
   // Summary:
   //    Instructs the VU meter module to calculate the metering values and return the results in 
   //    the output structure array.
   // Return value:
   // - MV_NOERROR, if operation is successful. 
   // - MV_E_INVALID_POINTER, if the buffer size is NULL. 
   // - MV_E_INVALID_PARAMETER, if the buffer size is 0. 
   // - MV_E_INVALID_PARAMETER, if in_ulVuMeterValueArraySize does not match the number of tracks 
   //   in the audio sample. 
   // - MV_E_INPUT_FORMAT_NOT_SUPPORTED, if the buffer format is not the list of known formats for 
   //   the VU meter. 
   // - MV_E_UNSUPPORTED_MEMORY_LOCATION, if the memory location is neither the host nor the user. 
   // Remarks:
   // - Compatible with 16-bit stereo audio samples, and the following 24-bit audio samples: mono,
   //   stereo, 4-track, 8-track, and 16-track. 
   // - The results of the VU meter calculation are returned in the output structure. 
   // - The application must allocate the output structure. 
   virtual HRESULT __stdcall ProcessVuMeterValue
      (
      IMvAudioSamples*           in_pIAudioSamples,         // Input audio samples to process.
      SMvAudioVuMeterValueMono*  io_psOutputVuValueArray,   // Output VU-metering value array, 
                                                               // including clipping and peak 
                                                               // information.
      unsigned long              in_ulVuMeterValueArraySize // The number of VU-metering value in
                                                               // array, corresponding to the number
                                                               // of tracks in the audio sample.
      )=0;

   //
   // Summary:
   //    Resets the internal value (previous results) of the VU meter to zero.
   // Return value:
   // - MV_NOERROR. The method is always successful. 
   // Remarks:
   // - The VU meter calculation is based on the current data and the feedback from the data of the 
   //   last 1/3 of the second. This method should be called when playback is interrupted (stopped,
   //   paused, etc.) or when there are time lapses between buffers (that is, no buffers for a time
   //   period) so that the results are more accurate.
   // - It is the caller's (application's) responsibility to clear the internal values at the
   //   appropriate moment so that the results of the VU meter are accurate. 
   // - The VU meter assumes that all buffers are continuous. 
   virtual HRESULT __stdcall ResetVuMeterValue()=0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Allows the application to obtain miscellaneous information on the available Matrox
//    DSX-compatible hardware. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvHardwareInformation : public IUnknown
{
   //
   // Summary:
   //    Initializes the COM object on the selected hardware profile.
   // Return value:
   //    - Returns an error if the command fails.
   // Remarks:
   //    - The needed hardware profile can be found using the IMvHardwareProfileEnumerator
   //      interface that can be queried from this interface.
   virtual HRESULT __stdcall Initialize
      (
      EMvHardwareProfile in_eHardwareProfileType,  // Specifies the hardware profile type that must
                                                      // be used to initialize the COM. 
      unsigned long      in_ulHardwareProfileIndex // Specifies the index of the hardware profile type. 
      ) = 0;

   //
   // Summary:
   //    Retrieves the device count of the selected hardware profile. 
   // Return value:
   //    - Returns an error if the command fails.
   virtual HRESULT __stdcall GetDeviceCount
      (
      unsigned long* in_pulDeviceCount // Pointer to an unsigned long that will receive the number
                                          // of hardware components that can supply information.
      ) = 0;

   //
   // Summary:
   //    Retrieves the device temperature sensor count.
   // Return value:
   //    - MV_NOERROR always.
   virtual HRESULT __stdcall GetNumberOfTemperatureSensors
      (
      unsigned long  in_ulDeviceIndex,                // Specifies the device index on which to get
                                                         // information (starting from zero).
      unsigned long* in_pulNumberOfTemperatureSensors // Returns the number of temperature sources.
      ) = 0;

   //
   // Summary:
   //    Retrieves the temperature information of a specific sensor.
   // Return value:
   //    - Returns an error if the command fails.
   virtual HRESULT __stdcall GetTemperatureInformation
      (
      unsigned long  in_ulDeviceIndex, // Specifies the device index on which to get information 
                                          // (starting from zero).
      unsigned long  in_ulSensorIndex, // Specifies the index of the temperature sensor to get 
                                          // information on (starting from zero).
      void*          io_pParam,        // Points to a SMvTemperatureInformation structure that will
                                          // be filled with temperature information.
      unsigned long  in_ulSizeOfParam  // Specifies the size of a passed structure.
      ) = 0;

   //
   // Summary:
   //    Retrieves the name of the temperature sensor notification event.
   // Return value:
   //    - Returns an error if the command fails.
   virtual HRESULT __stdcall GetTemperatureNotification
      (
      unsigned long  in_ulDeviceIndex,       // Specifies the device index on which to get
                                                // information (starting from zero).
      unsigned long  in_ulSensorIndex,       // The temperature sensor index to receive the
                                                // associated event (starting from zero).
      char*          out_szNotificationName  // This string is filled with the name of the event
                                                // to wait on.
      ) = 0;

   //
   // Summary:
   //    Retrieves the device's non-temperature information.
   // Return value:
   //    - Returns an error if the command fails. It returns an
   //      unsupported error if the parameter name does not exist on the device.
   virtual HRESULT __stdcall GetInformation
      (
      unsigned long           in_ulDeviceIndex,    // Specifies the device index on which to get 
                                                      // information (starting from zero).
      EMvInformationParameter in_eParameterInfo,   // Specifies the name of the parameter to retrieve.

      void * io_pParam,    // Pointer to a structure that will be filled with the expected 
                           // information.  The structure depends on the in_eParameterInfo 
                           // parameter.  
                           // - Power information structure SMvPowerInformation for
                           //   keInformationParameterPowerStatus.
                           // - Hardware flavor information for keInformationParameterHardwareFlavor.
                           // - X.link status information for keInformationParameterXlinkStatus.
                           // - Fan status information for keInformationParameterFanStatus.
                           // - Hardware information for keInformationParameterHardwareStatus.
                           // - Information structure SMvInformationParameter for all other
                           //   parameters.
                           // - Hardware flavor structure SMvHardwareFlavorInformation.
                           // - Cable ID structure SMvCableID.
                           // - Memory status structure SMvMemStatus for 
                           //   keInformationParameterMemoryStatus.
                           // - SMvInformationParameter for keInformationParameterMemorySize and 
                           //   keInformationParameterPciBusInfo.

      unsigned long in_ulSizeOfParam   // Size of the structure pointed to by io_pParam.
      ) = 0;

   //
   // Summary:
   //    Retrieves the non-temperature notification count of a device.
   // Return value:
   //    - MV_NOERROR always.
   virtual HRESULT __stdcall GetNumberOfNotifications
      (
      unsigned long  in_ulDeviceIndex,             // Specifies the device index on which to get 
                                                      // information (starting from zero).
      unsigned long* in_pulNumberOfNotifications   // Returns the number of notifications available 
                                                      // for this device index.
      ) = 0;

   //
   // Summary:
   //    Retrieves the non-temperature notification information.
   // Return value:
   //    - Returns an error if the command fails.
   virtual HRESULT __stdcall GetNotification
      (
      unsigned long     in_ulDeviceIndex,       // Specifies the device index on which to get
                                                   // information (starting from zero).
      unsigned long     in_ulNotificationIndex, // The notification index to receive the associated 
                                                   // information (starting from zero).
      SMvNotification*  out_psNotification      // Gives a pointer to a structure that will be 
                                                   // filled with the notification information.
      ) = 0;

   //
   // Summary:
   //    Generates a Matrox Dongle Information File (.MDIF) to field upgrade a user's DSX card.
   // Description:
   //	   This method generates a Matrox Dongle Information File (.MDIF) to field upgrade a user's 
   //    DSX card. The .MDIF file contains information read from the card's dongle, a built-in 
   //    hardware device that specifies the model and capabilities of a user's card. To perform 
   //    an upgrade, the .MDIF file is sent to Matrox and verified. Once verified, Matrox will send 
   //    back a Matrox Dongle Upgrade File (.MDUF) that the user needs to perform the upgrade. For 
   //    more information, see methods IMvHardwareInformation::UpgradeMDUF and 
   //    IMvHardwareInformation::ResetDongleToFactoryDefault.
   // Return value:
   //    - Returns an error if the command fails.
   // See Also:
   //    IMvHardwareInformation, GenerateSelectedDongleMDIF, UpgradeMDUF, UpgradeSelectedDongleMDUF, 
   //    ResetDongleToFactoryDefault, ResetSelectedDongleToFactoryDefault
   //    
   virtual HRESULT __stdcall GenerateMDIF
      (
      unsigned long in_ulDeviceIndex,        // Specifies the device index, starting from zero, 
                                                // on the DSX card where the dongle is located.
      wchar_t     * in_pwszDirectory,        // Specifies the directory where the .MDIF is to be stored.
      wchar_t     * out_pwszFilename,        // Provides the filename for the .MDIF file.
      size_t        in_szFilenameSizeInWord  // Expresses the size of the .MDIF in terms of the number 
                                                // of characters in the filename.
      ) = 0;

   //
   // Summary:
   //    Generates a Matrox Dongle Information File (.MDIF) for the specified dongle to field upgrade 
   //    a user's DSX card.
   // Description:
   //	   This method generates a Matrox Dongle Information File (.MDIF) for the specified dongle to field 
   //    upgrade a user's DSX card. The .MDIF file contains information read from the card's dongle, a built-in 
   //    hardware device that specifies the model and capabilities of a user's card. To perform 
   //    an upgrade, the .MDIF file is sent to Matrox and verified. Once verified, Matrox will send 
   //    back a Matrox Dongle Upgrade File (.MDUF) that the user needs to perform the upgrade. For 
   //    more information, see methods IMvHardwareInformation::UpgradeSelectedDongleMDUF and 
   //    IMvHardwareInformation::ResetSelectedDongleToFactoryDefault.
   // Return value:
   //    - Returns an error if the command fails.
   // See Also:
   //    IMvHardwareInformation, GenerateMDIF, UpgradeMDUF, UpgradeSelectedDongleMDUF, 
   //    ResetDongleToFactoryDefault, ResetSelectedDongleToFactoryDefault
   //    
   virtual HRESULT __stdcall GenerateSelectedDongleMDIF
      (
      unsigned long     in_ulDeviceIndex,       // Specifies the device index, starting from zero, 
                                                   // on the DSX card where the dongle is located.
      EMvDongleSelect   in_eDongleSelect,       // Specifies the dongle.
      wchar_t         * in_pwszDirectory,       // Specifies the directory where the .MDIF is to be stored.
      wchar_t         * out_pwszFilename,       // Provides the filename for the .MDIF file.
      size_t            in_szFilenameSizeInWord // Expresses the size of the .MDIF in terms of the number 
                                                   // of characters in the filename.
      ) = 0;

   //
   // Summary:
   //    Uses a Matrox Dongle Upgrade File (.MDUF) to perform a field upgrade of a user's DSX card.
   // Description:
   //    This method uses the Matrox Dongle Upgrade File (.MDUF) to perform a field upgrade of a user's 
   //    DSX card. This file contains the information needed to upgrade the card to the desired model 
   //    requested by the user when sending the Matrox Dongle Information File (.MDIF). After receiving 
   //    and verifying the .MDIF, Matrox will send the .MDUF file to complete the upgrade. For more information, 
   //    see the methods IMvHardwareInformation::GenerateMDIF() and IMvHardwareInformation::ResetDongleToFactoryDefault().
   // Return value:
   //    - Returns an error if the command fails.
   // Remarks:
   //    - Before performing the upgrade, the card must be set to its original factory default settings using IMvHardwareInformation::ResetDongleToFactoryDefault().
   // See Also:
   //    IMvHardwareInformation, GenerateMDIF, GenerateSelectedDongleMDIF, UpgradeSelectedDongleMDUF, 
   //    ResetDongleToFactoryDefault, ResetSelectedDongleToFactoryDefault
   //
   virtual HRESULT __stdcall UpgradeMDUF
      (
      unsigned long in_ulDeviceIndex,        // Specifies the device index, starting from zero,
                                                // on the DSX card where the dongle is located.
      wchar_t     * in_pwszFilename          // Specifies the filename and directory where the 
                                                // .MDUF is located on the user's hard drive.
      ) = 0;

   //
   // Summary:
   //    Uses a Matrox Dongle Upgrade File (.MDUF) to perform a field upgrade for the specified dongle 
   //    of a user's DSX card.
   // Description:
   //    This method uses the Matrox Dongle Upgrade File (.MDUF) to perform a field upgrade for the specified dongle 
   //    of a user's DSX card. This file contains the information needed to upgrade the card to the desired model 
   //    requested by the user when sending the Matrox Dongle Information File (.MDIF). After receiving 
   //    and verifying the .MDIF, Matrox will send the .MDUF file to complete the upgrade. For more information, 
   //    see methods IMvHardwareInformation::GenerateSelectedDongleMDIF and 
   //    IMvHardwareInformation::ResetSelectedDongleToFactoryDefault.
   // Return value:
   //    - Returns an error if the command fails.
   //See Also:
   //    IMvHardwareInformation, GenerateMDIF, GenerateSelectedDongleMDIF, UpgradeMDUF, 
   //    ResetDongleToFactoryDefault, ResetSelectedDongleToFactoryDefault
   //
   virtual HRESULT __stdcall UpgradeSelectedDongleMDUF
      (
      unsigned long     in_ulDeviceIndex,    // Specifies the device index, starting from zero,
                                                // on the DSX card where the dongle is located.
      EMvDongleSelect   in_eDongleSelect,    // Specifies the dongle.
      wchar_t         * in_pwszFilename      // Specifies the filename and directory where the 
                                                // .MDUF is located on the user's hard drive.
      ) = 0;

   //
   // Summary:
   //    Resets a previously upgraded DSX card to its factory default settings.
   // Description:
   //    If a DSX card has previously been upgraded, this method will reset the card to its pre-upgrade 
   //    factory default settings. For more information, see methods IMvHardwareInformation::GenerateMDIF 
   //    and IMvHardwareInformation::UpgradeMDUF.
   // Return value:
   //    - Returns an error if the command failed.
   //See Also:
   //    IMvHardwareInformation, GenerateMDIF, GenerateSelectedDongleMDIF, UpgradeMDUF, 
   //    UpgradeSelectedDongleMDUF, ResetSelectedDongleToFactoryDefault
   //
   virtual HRESULT __stdcall ResetDongleToFactoryDefault
      (
      unsigned long in_ulDeviceIndex         // Specifies the device index, starting from zero,
                                                // on the DSX card where the dongle is located.
      ) = 0;

   //
   // Summary:
   //    Resets a previously upgraded dongle of a DSX card to its factory default settings.
   // Description:
   //    If a dongle of a DSX card has previously been upgraded, this method will reset the dongle to its pre-upgrade 
   //    factory default settings. For more information, see methods IMvHardwareInformation::GenerateSelectedDongleMDIF 
   //    and IMvHardwareInformation::UpgradeSelectedDongleMDUF.
   // Return value:
   //    - Returns an error if the command failed.
   //See Also:
   //    IMvHardwareInformation, GenerateMDIF, GenerateSelectedDongleMDIF, UpgradeMDUF, 
   //    UpgradeSelectedDongleMDUF, ResetDongleToFactoryDefault
   //
   virtual HRESULT __stdcall ResetSelectedDongleToFactoryDefault
      (
      unsigned long     in_ulDeviceIndex,     // Specifies the device index, starting from zero,
                                                // on the DSX card where the dongle is located.
      EMvDongleSelect   in_eDongleSelect     // Specifies which dongle to reset. 
      ) = 0;

   //
   // Summary:
   //    Retreive the current configuration of the X.Rio module
   // Description:
   //    This method will return the last configuration set by method SetModuleIOTopology(). It may
   //    not be the configuration the module is currently using. 
   // Return value:
   //    - Returns an error if the command failed.
   virtual HRESULT __stdcall GetModuleIOTopology
      (
      unsigned long in_ulDeviceIndex,                    // Specifies the device index, starting from zero,
                                                            // on the DSX card where the dongle is located.
      SMvRIOConfigurationInfo * out_psRIOConfiguration   // Gives a pointer to a structure that will be 
      ) = 0;                                                // filled with the configuration information.

   //
   // Summary:
   //    Sets the configuration of the X.Rio module. The new configuration will be changed on next system restart.
   // Description:
   //    This method changes the module configuration. The valid configuration are: 4 inputs and 0 output,
   //    2 inputs and 2 outputs or 0 inputs and 4 outputs. The new configuration will be changed on next
   //    system restart. 
   // Return value:
   //    - Returns an error if the command failed.
   virtual HRESULT __stdcall SetModuleIOTopology
      (
      unsigned long in_ulDeviceIndex,                    // Specifies the device index, starting from zero,
                                                            // on the DSX card where the dongle is located.
      SMvRIOConfigurationInfo * in_psRIOConfiguration    // Gives a pointer to a structure containing 
      ) = 0;                                                // the new configuration information.

};

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This interface sets the volume for the audio mixer.
//
//////////////////////////////////////////////////////////////////////////
interface IMvAudioMixerEffectSettings 
: public IUnknown
{
   //
   // Summary:
   //    This method sets the volume of the left channel source that will be mixed to the left 
   //    channel destination.
   // Description:
   //    For both parameters:
   //    Default value: 1.0 (0dB).
   //    Valid range:
   //       - For 16-bit audio data: [0.0, 7.999] multiplication factor (equivalent to 
   //         [-infinite, 18] dB). A value below 1.0 is attenuation, and a value above 1.0 is gain. 
   //       - For 24 bit audio data: Not restricted, full range 32 bit float. However, the usefull 
   //         range is 0.0 to 8.0. A value below 1.0 is attenuation, and a value above 1.0 is gain.
   //         Negative volumes will invert (180 degree phase inversion), which can cause 
   //         unpredictable results (signal cancellation). 
   //    Granularity:
   //       - For 16-bit audio data: Limited to 16 high order bits of the mantissa (approx. 0.0001
   //         steps in multiplication factor or 0.001dB steps around 0dB). 
   //       - For 24-bit audio data: Full precision 32 bit float (approx. 1 x 10 exp -7 steps in
   //         multiplication factor or 1 x 10 exp -6 dB around 0dB ). 
   //    Dependency:
   //       - The volume will be linearly interpolated (from one sample to the other) from the
   //         in_fInitial to the in_fFinal. 
   // Return value:
   //    - MV_NOERROR, if succeeded. 
   //    - MV_E_INVALID_PARAMETER, if one of the parameter is out of range.  
   virtual HRESULT __stdcall SetVolumeLeftToLeft
      (
      float in_fInitial,   // Volume to be applied to the left channel at the beginning of the
                              // segment (first sample). The volume is a multiplying factor. 
      float in_fFinal      // Volume to be applied to the left channel at the end of the segment 
                              // (last sample).
      ) = 0;

   //
   // Summary:
   //    This method sets the volume of right channel source that will be mixed to the right
   //    channel destination. 
   // Description:
   //    For both parameters:
   //    Default value: 1.0 (0dB)
   //    Valid range:
   //       - For 16-bit audio data: [0.0, 7.999] multiplication factor (equivalent to
   //         [-infinite, 18] dB). A value below 1.0 is attenuation, and a value above 1.0 is gain. 
   //       - For 24-bit audio data: Not restricted, full range 32 bit float. However, the usefull 
   //         range is 0.0 to 8.0. A value below 1.0 is attenuation, and a value above 1.0 is gain.
   //         Negative volumes will invert (180 degree phase inversion), this can cause 
   //         unpredictable results (signal cancellation). 
   //    Granularity:
   //       - For 16-bit audio data: Limited to 16 high order bits of the mantissa (approx. 0.0001
   //         steps in multiplication factor or 0.001dB steps around 0dB). 
   //       - For 24-bit audio data: Full precision 32 bit float (approx. 1 x 10 exp -7 steps in 
   //         multiplication factor or 1 x 10 exp -6 dB around 0dB ). 
   //    Dependency:
   //       - The volume will be linearly interpolated (from one sample to the other) from the 
   //         in_fInitial to the in_fFinal.
   // Return value:
   //    - MV_NOERROR, if succeeded. 
   //    - MV_E_INVALID_PARAMETER, if one of the parameter is out of range. 
   virtual HRESULT __stdcall SetVolumeRightToRight
      (
      float in_fInitial,   // Volume to be applied to the right channel at the beginning of the 
                              // segment (first sample). The volume is a multiplying factor.
      float in_fFinal      // Volume to be applied to the right channel at the end of the segment 
                              // (last sample).
      ) = 0;

   //
   // Summary:
   //    This method sets the volume of left channel source that will be mixed to the right channel
   //    destination. 
   // Description:For both parameters:
   //    Default value: 1.0 (0dB)
   //    Valid range:
   //       - For 16-bit audio data: [0.0, 7.999] multiplication factor (equivalent to 
   //         [-infinite, 18] dB). A value below 1.0 is attenuation, and a value above 1.0 is gain. 
   //       - For 24-bit audio data: Not restricted, full range 32 bit float. However, the usefull
   //         range is 0.0 to 8.0. A value below 1.0 is attenuation, and a value above 1.0 is gain. 
   //         Negative volumes will invert (180 degree phase inversion), which can cause 
   //         unpredictable results (signal cancellation). 
   //    Granularity:
   //       - For 16-bit audio data: Limited to 16 high order bits of the mantissa (approx. 0.0001 
   //         steps in multiplication factor or 0.001dB steps around 0dB). 
   //       - For 24 bit audio data: Full precision 32 bit float (approx. 1 x 10 exp -7 steps in 
   //         multiplication factor or 1 x 10 exp -6 dB around 0dB ). 
   //    Dependency:
   //       - The volume will be linearly interpolated (from one sample to the other) from the
   //         in_fInitial to the in_fFinal.
   // Return value:
   //    - MV_NOERROR, if succeeded. 
   //    - MV_E_INVALID_PARAMETER, if one of the parameter is out of range. 
   virtual HRESULT __stdcall SetVolumeLeftToRight
      (
      float in_fInitial,   // Volume to be applied to the left channel at the beginning of the 
                              // segment (first sample). The volume is a multiplying factor. 
      float in_fFinal      // Volume to be applied to the left channel at the end of the segment
                              // (last sample).
      ) = 0;

   //
   // Summary:
   //    Sets the volume of the right channel source that will be mixed to the left channel
   //    destination. 
   // Description:
   //    For both parameters:
   //    Default value: 1.0 (0dB)
   //    Valid range:
   //       - For 16-bit audio data: [0.0, 7.999] multiplication factor (equivalent to
   //         [-infinite, 18] dB). A value below 1.0 is attenuation, and a value above 1.0 is gain. 
   //       - For 24-bit audio data: Not restricted, full range 32 bit float. However, the usefull
   //         range is 0.0 to 8.0. A value below 1.0 is attenuation, and a value above 1.0 is gain.
   //         Negative volumes will invert (180 degree phase inversion), this can cause 
   //         unpredictable results (signal cancellation). 
   //    Granularity:
   //       - For 16-bit audio data: Limited to 16 high order bits of the mantissa (approx. 0.0001 
   //         steps in multiplication factor or 0.001dB steps around 0dB). 
   //       - For 24-bit audio data: Full precision 32 bit float (approx. 1 x 10 exp -7 steps in 
   //         multiplication factor or 1 x 10 exp -6 dB around 0dB ). 
   //    Dependency:
   //       - The volume will be linearly interpolated (from one sample to the other) from the 
   //         in_fInitial to the in_fFinal.
   // Return value:
   //    - MV_NOERROR, if succeeded. 
   //    - MV_E_INVALID_PARAMETER, if one of the parameters is out of range. 
   virtual HRESULT __stdcall SetVolumeRightToLeft
      (
      float in_fInitial,   // Volume to be applied to the right channel at the beginning of the
                              // segment (first sample). The volume is a multiplying factor. 
      float in_fFinal      // Volume to be applied to the right channel at the end of the segment
                              // (last sample).
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Creates a Flex Clip Reader or Flex Clip Writer
//    object.
//
//////////////////////////////////////////////////////////////////////////
interface IMvFlexClipFactory : public IUnknown
{
   //
   // Summary:
   //    Instantiates a Flex Clip Reader object and returns the IMvFlexClipReader interface.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - Before returning the IMvFlexClipReader interface its reference count should be incremented.
   //    - This method is implemented by the OEM developer and called by Flex modules to create the OEM's Flex Clip Reader.
   //    - The Flex Clip Reader should boost the priority of its worker threads to the specified thread priority using the provided Flex Engine interface.
   virtual HRESULT __stdcall CreateFlexClipReader(
      IMvFlexEngine*       in_pIFlexEngine,              // Points to the Flex Engine interface that is passed to the constructed Flex Clip Reader
      unsigned long        in_ulThreadPriority,          // Thread priority that is passed to the constructed Flex Clip Reader
      IMvFlexClipReader**  out_ppIFlexClipReader         // Points to the address of the created Flex Clip Reader object
   ) = 0;

   //
   // Summary:
   //    Instantiates a Flex Clip Writer object and returns the IMvFlexClipWriter interface.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - Before returning the IMvFlexClipWriter interface its reference count should be incremented.
   //    - This method is implemented by the OEM developer and called by Flex modules to create the OEM's Flex Clip Writer.
   //    - The Flex Clip Reader should boost the priority of its worker threads to the specified thread priority using the provided Flex Engine interface.
   virtual HRESULT __stdcall CreateFlexClipWriter(
      IMvFlexEngine*       in_pIFlexEngine,              // Points to the Flex Engine interface that will be passed to the constructed Flex Clip Writer
      unsigned long        in_ulThreadPriority,          // Thread priority that is passed to the constructed Flex Clip Writer
      IMvFlexClipWriter**  out_ppIFlexClipWriter         // Points to address of the created Flex Clip Writer object
   ) = 0;

 
};

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Reads video and/or audio data from a Flex Clip Reader object.
//
//////////////////////////////////////////////////////////////////////////
interface IMvFlexClipReader : public IUnknown
{
   //
   // Summary:
   //    Opens the file.
   //
   // Remarks:
   //    - The implementation needs to support Open/Close sequences, even if no Read operation is carried out.
   //    - The Flex Reader can cache a Flex Clip Reader following a Close command so that the next Open command occurs faster.
   virtual HRESULT __stdcall Open( 
      SMvFlexClipReaderOpen *io_psClipReaderOpen         // Filename to open.
      ) = 0;

   //
   // Summary:
   //    Closes the file.
   //
   // Remarks:
   //    - The implementation needs to support Open/Close sequences, even if no Read operation is carried out.
   //    - The Flex Reader can cache a Flex Clip Reader following a Close command so that the next Open command occurs faster.
   virtual HRESULT __stdcall Close() = 0;

   //
   // Summary:
   //    Retrieves video and audio information
   //
   // Remarks:
   //    - The GetAVFileInfo is called by Flex modules to determine the audio and video contents of a file opened by the Flex Clip Reader.
   //    - The surface format found in the SMvAudioVideoFileInfo structure should be either keMvSurfaceFormatYUYV422 or keMvSurfaceFormatYUAYVA4224. This is the 
   //      format used to exchange data between the Flex Clip Reader and other Flex modules.
   //    - Exposing an uncompressed surface format as a data exchange type between the Flex Clip Reader and other Flex modules abstracts custom compression formats
   //      that are understood by the Flex Clip Reader and that other Flex modules do not natively understand.
   virtual HRESULT __stdcall GetAVFileInfo( 
      SMvAudioVideoFileInfo *out_psmvAVFileInfo          // Points to a structure containing the audio and video information needed to control the Flex Clip Reader.
   ) = 0;

   //
   // Summary:
   //    Retrieves the surface format needed for the Read command
   //
   // Remarks:
   //    - The surface format returned should be either keMvSurfaceFormatYUYV422 or keMvSurfaceFormatYUAYVA4224, it should match the GetAVFileInfo's SMvAudioVideoFileInfo
   //      surface format.
   //    - The playback surface format reflects the type of surfaces the Flex Reader passes to  the Flex Clip Reader
   //      in a Read command.
   virtual HRESULT __stdcall GetPlaybackFormat( 
      EMvSurfaceFormat *out_peFormat                     // Points to the surface format needed for the Read command.
   ) = 0;

   //
   // Summary:
   //    Reads the audio and/or video data specified in the SMvFlexClipReaderReadCommand parameter.
   //
   // Remarks:
   //    - The Read command can be asynchronous or synchronous. An asynchronous command yields better performance depending on the technology behind the custom
   //      Flex Clip Reader implementation.
   //    - The Flex Clip Reader is not a memory provider. The surfaces and samples passed in the SMvFlexClipReaderReadCommand are allocated by the caller.
   //    - The reference count of the surfaces and samples passed in the SMvFlexClipReaderReadCommand is incremented by the caller. The surfaces and samples are released when the Reader is done.
   //    - The IMvAVContent write count of the surfaces and samples passed in the SMvFlexClipReaderReadCommand is incremented by the caller. The surfaces and samples are released when the Reader is done.
   //    - The Flex Clip Reader should call IMVContent::MarkWriteStartTime and IMVAVContent::MarkWriteStopTime on the surfaces and samples passed.
   //    - VBI interleaved playback is currently not supported. It is present in the API for future considerations.
   virtual HRESULT __stdcall Read( 
      SMvFlexClipReaderReadCommand *in_psReadCommand     // Flex Clip Reader read command containing the video surfaces and/or audio samples, as well as the stream IDs to read
                                                         // and the position boundaries in frames and in samples.
   ) = 0;
};

//
// Summary:
//    This is an interface used to retrieve options from the Flex Clip Reader.
// Remarks:   
//    This optional interface is available from IMvFlexClipReader interface, if it is implemented by the Flex Clip Reader object.
//
interface IMvClipReaderOptions : public IUnknown
{
	//
	// Summary:
   //    This is an interface used to configure options on the Flex Clip Reader.	
   //
	// Remarks:
	//    - Clip Option calls are synchronous.
	//    - The Flex Clip Reader should validate the option GUID and return an error if it doesn't support that particular option.
   //
   virtual HRESULT __stdcall GetClipOption(
      void * io_pvOptionValue ,
      unsigned long in_ulOptionSize,
      const GUID* in_pkguidOptionGuid
      ) = 0;

   //
   // Summary:
   //    Sets the specified clip option on the Flex Clip Reader.
   //
   // Remarks:
   //    - Clip Option calls are synchronous.
   //    - The Flex Clip Reader should validate the option GUID and return an error if it doesn't support that particular option.
   //
   virtual HRESULT __stdcall SetClipOption(
      void * io_pvOptionValue,
      unsigned long in_ulOptionSize,
      const GUID* in_pkguidOptionGuid
      ) = 0;

   //
   // Summary:
   //    Checks if the specified clip option is supported on the Flex Clip Reader.
   //
   // Remarks:
   //    - Clip Option calls are synchronous.
   //
   virtual bool __stdcall IsClipOptionSupported( 
      const GUID * in_pkguidOptionGuid                  
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This interface writes video and/or audio data to a Flex Clip Writer object.
//
//////////////////////////////////////////////////////////////////////////
interface IMvFlexClipWriter : public IUnknown
{
   //
   // Summary:
   //    Opens the Flex Clip Writer with the specified parameters.
   //
   // Remarks:
   //    - The implementation needs to support Open/Close sequences, even if no Write was done on the object.
   //    - The Open command is synchronous.
   //    - Following a successful Open call the Flex Clip Writer can expect to be called with Write.
   virtual HRESULT __stdcall Open( 
      wchar_t* in_pwchFileName                           // Filename to open.
   ) = 0;

   //
   // Summary:
   //    Tell the Flex Clip Writer that we're done writing and it can close the file.
   //
   // Remarks:
   //    - The implementation needs to support Open/Close sequences, even if no Write was done on the object.
   //    - The Close command is serialized with the Write command. Once Close has been called the Flex Clip Writer 
   //      can assume that no more  call to Write will be made.
   //    - The Close call should not fail.
   //    - Before closing the file the Flex Clip Writer needs to guarantee that all Write commands will be honoured.
   //    - The Close command is synchronous. Following a Close the caller expects that the captured file is complete
   //      and available for reading.
   virtual HRESULT __stdcall Close() = 0;

   //
   // Summary:
   //    Asks the Flex Clip Writer to write audio and/or video data to the file.
   //
   // Remarks:
   //    - The Flex Clip Writer should validate that the input surfaces and samples are ready to be read before processing them (IMvAVContent::IsReadyForRead).
   //    - The surfaces and samples passed in the Write have had their reference count incremented by the caller. When the Flex Clip Writer is done with 
   //      these surfaces and samples it needs to release them.
   //    - The surfaces and samples passed in the Write have had their IMvAVContent read count incremented by the caller. When the Flex Clip Writer is 
   //      done with these surfaces and samples it needs to call IMvAVContent::SignalReadCompletion on them.
   //    - The Write can be asynchronous or synchronous.
   //    - The Write command's granularity is one frame. If the resolution is interlaced then the two fields will be interlaced inside the frame surface.
   //      The audio samples buffer contains one frame worth of samples. The number of audio samples per frame is determined by the application.
   //    - VBI interleaved capture is currently not supported. It's present in the API for future considerations.
   virtual HRESULT __stdcall Write( 
      IMvSurface* in_pIVideoSurface,                     // video frame surface to write
      IMvSurface* in_pIVBISurface,                       // VBI surface to Write. Currently unused.
      IMvAudioSamples* in_pIAudioSamples                 // Audio samples to Write.
   ) = 0;

   //
   // Summary:
   //    Retrieves the specified clip option from the Flex Clip Writer.
   //
   // Remarks:
   //    - Clip Option calls are synchronous.
   //    - Clip options are opaque types that are propagated from the Flex Writer interface all the way down to the Flex Clip Writer. 
   //      This allows the application to control encoding parameters that are specific to the Flex Clip Writer being used without the need for the Flex layer to interpret them.
   //    - The Flex Clip Writer should validate the option ID and return an error if it doesn't support that particular option.
   virtual HRESULT __stdcall GetClipOption( 
      void* io_pvOptionValue,                            // value to set the option to
      unsigned long in_ulOptionSize,                     // size of the value parameter's type. 
                                                         // For example, if io_pvOptionValue points to a structure, then in_ulOptionSize is the structure size.
      const GUID * in_pkguidOptionGuid                        // identifier telling which value to get
   ) = 0;

   //
   // Summary:
   //    Sets the specified clip option on the Flex Clip Writer.
   //
   // Remarks:
   //    - Clip Option calls are synchronous.
   //    - Clip options are opaque types that are propagated from the Flex Writer interface all the way down to the Flex Clip Writer. 
   //      This allows the application to control encoding parameters that are specific to the Flex Clip Writer being used without the need for the Flex layer to interpret them.
   //      For example this method can be used to specify which codec the Flex Clip Writer should use, its datarate, etc.
   //    - The Flex Clip Writer should validate the option ID and return an error if it doesn't support that particular option.
   virtual HRESULT __stdcall SetClipOption( 
      void* in_pvOptionValue,                            // value to set the option to
      unsigned long in_ulOptionSize,                     // size of the value parameter's type. 
      const GUID * in_pkguidOptionGuid                        // identifier telling which value to get
   ) = 0;

   //
   // Summary:
   //    Checks if the specified clip option is supported on the Flex Clip Writer.
   //
   // Remarks:
   //    - Clip Option calls are synchronous.
   //    - Clip options are opaque types that are propagated from the Flex Writer interface all the way down to the Flex Clip Writer. 
   //      This allows the application to control encoding parameters that are specific to the Flex Clip Writer being used without the need for the Flex layer to interpret them.
   virtual HRESULT __stdcall IsClipOptionSupported( 
      const GUID * in_pkguidOptionGuid,                       // identifier telling which value to get
      bool* out_pbSupported                              // flags containing the result
   ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
// 
//Summary:
//    This interface adds the SetWriterResolution method to the Flex Clip Writer.
//   
//Remarks:
//    - When calling CreateFlexClipWriter, the Flex Clip Writer resolution is not provided, but instead the 
//      Flex Engine profile resolution is used, which might be different from the one set in the user application.
//    - Therefore, after calling CreateFlexClipWriter, the FlexClipWriter object needs to call QueryInterface to get IMvFlexClipWriter2, 
//      and then call SetWriterResolution to provide the correct resolution to the Flex Clip Writer.
//     
//////////////////////////////////////////////////////////////////////////////////
interface IMvFlexClipWriter2 : public IMvFlexClipWriter
{
   virtual HRESULT __stdcall SetWriterResolution(
      SMvResolutionInfo* in_psResolution                 //The resolution to be passed from the user application to the Flex Clip Writer.
   ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//Summary:
//    Adds frame indexing to a Windows Media (.wmv or .asf) file.
//Remarks:
//    Frame indexing is required to support frame-accurate trimming, seeking, and editing.
//    The frame indexing is added to the header of the input file, and a separate index is added for the video
//    and audio streams.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
interface IMvFlexASFClipIndexer : public IUnknown
{
   ////////////////////////////////////////////////////////////////////////////////////////////////////////// 
   // Summary:
   //	 Adds frame indexing to the header of a specified Windows Media (.wmv or .asf) file for video and/or
   //	 audio. 
   //////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual HRESULT __stdcall CreateFrameIndex(
      wchar_t* in_pwchFileName,                 // Pointer to the file to which you want to add frame indexing.
      bool in_bVideo,                           // Specifies whether or not to add a frame index for the video stream.
      bool in_bAudio                            // Specifies whether or not to add a frame index for the audio stream. 
   ) = 0;

};

//////////////////////////////////////////////////////////////////////////////////
// 
// Summary: 
//	  Creates a Flex MPEG-2 IBP Clip Reader object.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvFlexMpegClipReaderFactory : public IUnknown
{
   virtual HRESULT __stdcall CreateMpegClipReader(
      IMvFlexEngine*          in_pIFlexEngine,
      unsigned long           in_ulThreadPriority,
      IMvFlexMpegClipReader** out_ppIFlexMpegClipReader ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
// 
// Summary:
//	  Reads video and/or audio data from a Flex MPEG-2 IBP Clip Reader object.
// Remarks:
//	  - This interface is similar to IMvFlexClipReader, but is intended for generating and using MPEG-2 IBP index files.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvFlexMpegClipReader : public IUnknown
{
   // 
   // Summary:
   //	 Opens the file and generates new, or uses existing, MPEG-2 IBP index files.
   // Remarks:
   //	 - If the structure SMvFlexMpegClipReaderOpen specifies true for the parameter bRecreateIndexFiles, MPEG-2 IBP index files will be generated.     
   //     
   virtual HRESULT __stdcall Open( SMvFlexClipReaderOpen *in_psClipReaderOpen, SMvFlexMpegClipReaderOpen* in_psMpegClipReaderOpen ) = 0;

   // 
   // Summary: 
   //	 Closes the file.
   // Remarks:
   //    - This method calls the base class implementation. No MPEG-specific processing is performed.  
   //
   virtual HRESULT __stdcall Close() = 0;

   // 
   // Summary:
   //    Returns video and audio information.
   // Remarks:
   //    - This method is not required to generate or use MPEG-2 IBP index files.
   //
   virtual HRESULT __stdcall GetAVFileInfo( SMvAudioVideoFileInfo *out_psmvAVFileInfo ) = 0;

   // 
   // Summary:
   //    Reads the audio and/or video data specified in the SMvFlexClipReaderReadCommand parameter.
   // Remarks:
   //	 - This method calls the base class implementation. No MPEG-specific processing is performed.
   //	 - This method is not required to generate or use MPEG-2 IBP index files.
   virtual HRESULT __stdcall Read( SMvFlexClipReaderReadCommand *in_psReadCommand ) = 0;

   // 
   // Summary:
   //    Get the audio stream info per stream.
   // Remarks:
   //	 - in_ui32Stream should be non zero, and less than or equal to SMvAudioVideoFileInfo::ui32PhysicalAudioTracksCount.
   virtual HRESULT __stdcall GetAudioStreamInfo(uint32_t in_ui32Stream, SMvAudioStreamProperties * out_pStreamProperty) = 0;

};
