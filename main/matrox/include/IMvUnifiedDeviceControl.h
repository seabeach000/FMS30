//==========================================================================;
//
// (c) Copyright Matrox Electronic Systems Ltd., 2002. All rights reserved.
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
//==========================================================================;
//                    IMvUnifiedDeviceControl.H
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             Today
//   Operating System:       WinXP
//   Author:                 DirectShow team
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;


#ifndef IMVUNIFIEDDEVICECONTROL_H
#define IMVUNIFIEDDEVICECONTROL_H


/** 
* The Unified Device control interface is used to select the device control and 
* do other device control functions.
* @interface 
*/

interface IMvUnifiedDeviceControl : public IUnknown
{
public:

   /**
   * Sets the Active Device Control.
   *  
   *
   * <br><b>Remarks:</b>
   * <ul><i><li>This function is called once a Device Control description is obtained 
   *        <li>from the enumeration (using the IMvEnumExtDevice). 
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if completed successfully.
   *     <li>MV_E_ALREADY_IN_USE, if Device is already in use.
   *     <li>MV_E_NOT_AVAILABLE, if Device does not exist on system.
   * </ul>
   * @param <i>SMvDeviceControlDescriptor * in_psDeviceDescriptor</i>: Device Control Descriptor describing which Device Control module should be active.
   */
   virtual HRESULT __stdcall SetActiveDevice( SMvDeviceControlDescriptor * in_psDeviceDescriptor ) = 0;

   /**
   * Closes the active Device Control.
   *  
   *
   * <br><b>Remarks:</b>
   * <ul><i><li>This function should be called to close the currently set active device
   *        <li>control.
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if completed successfully.
   *     <li>MV_E_FAIL, if Device was never opened.
   * </ul>
   */
   virtual HRESULT __stdcall CloseActiveDevice() = 0;

   /**
   * Used to get a handle on the active device. This handle can be monitored to know when the 
   * current device is no longer available.
   *  
   *
   * <br><b>Remarks:</b>
   * <ul><i><li>
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if completed successfully.
   *     <li>MV_E_NOT_AVAILABLE, if Device was never opened.
   * </ul>
   * @param <i>HANDLE * out_pHandle</i>: Handle to the device control.
   */
   virtual HRESULT __stdcall GetDeviceHandle( HANDLE * out_pHandle ) = 0;

   /**
   * Used to prepare the deck for a print to device or capture from device.  The call to this
   * method will cue the deck to 5 seconds prior to the in-point and begin to play the deck. 
   * Once the deck is cued, the event passed as a parameter will get signaled.
   *  
   *
   * <br><b>Remarks:</b>
   * <ul><i><li>
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if completed successfully.
   *     <li>MV_E_NOT_AVAILABLE, if Device was never opened.
   * </ul>
   * @param <i>HANDLE * out_pHandle</i>: Handle to the event that gets signaled once deck is prepared.
   */
   virtual HRESULT __stdcall PrepareEditOperation(HANDLE * out_pHandle) = 0;
   
   /**
   * Used to start the edit operation.  Immediately after this is called, the GetSystemClockAtInpoint
   * may be called to know what time to Run the graph at.
   *  
   *
   * <br><b>Remarks:</b>
   * <ul><i><li>
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if completed successfully.
   *     <li>MV_E_NOT_AVAILABLE, if Device was never opened.
   * </ul>
   */
   virtual HRESULT __stdcall StartEditOperation() = 0;

   /**
   * Used to stop an edit operation.
   *  
   *
   * <br><b>Remarks:</b>
   * <ul><i><li>
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if completed successfully.
   *     <li>MV_E_NOT_AVAILABLE, if Device was never opened.
   * </ul>
   */
   virtual HRESULT __stdcall StopEditOperation() = 0;

   /**
   * Used to distinguish device control for edit mode or for transport commands.
   *  
   *
   * <br><b>Remarks:</b>
   * <ul><i><li>
   * </i></ul>
   * 
   * <b>Return type:</b>
   * <ul><li>HRESULT
   * </ul>
   * <b>Return values:</b> 
   * <ul><li>MV_NOERROR, if completed successfully.
   *     <li>MV_E_NOT_AVAILABLE, if Device was never opened.
   * </ul>
   * @param <i>bool in_bEditMode</i>: Bool to set Editing mode.
   */
   virtual HRESULT __stdcall SetEditingMode(bool in_bEditMode) = 0;
   
   /**
   * Used to get the error code of the last device error.
   * 
   * <b>Return type:</b>
   * <ul><li>uint32_t
   * </ul>
   * <b>Return values:</b> 
   * <ul><li>0 if no error.
   *     <li>error code otherwise.
   * </ul>
   */
   virtual uint32_t __stdcall GetDeviceLastError() = 0;

   //HRESULT StopPrintToDevice( ) = 0;

};

#endif //IMVUNIFIEDDEVICECONTROL_H

