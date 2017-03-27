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
//                    IMvExtTransport.H
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


#ifndef IMVEXTTRANSPORT_H
#define IMVEXTTRANSPORT_H


/** 
* The IMvExtTransport interface controls the transport on a VCR or camcorder. It derives
* from IAMExtTransport which is the Microsoft interface for controlling the transport
* on a VCR or camcorder.
* @interface 
*/

interface IMvExtTransport : public IAMExtTransport
{
public:

   /**
   * Requests the status of the controlled device
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
   * </ul>
   * @param <i>SMvProtocolCommand * out_psMvProtocolCommand</i>: Contains all the status information.
   */
   virtual HRESULT __stdcall GetAllStatus(SMvProtocolCommand * out_psMvProtocolCommand) = 0;

   /**
   * Sends a direct command to the controlled device
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
   * </ul>
   * @param <i>SMvProtocolCommand * io_psMvProtocolCommand</i>: Contains all the status information.
   */
   virtual HRESULT __stdcall SendCommand(SMvProtocolCommand * io_psMvProtocolCommand) = 0;
   
   /**
   * Requests the system time at which the VTR will reach the inpoint.
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
   * </ul>
   * @param <i>SMvDigiVTRSynchro * out_psMvDigiVTRSynchro</i>: Contains all the status information.
   */
   virtual HRESULT __stdcall GetSystemClockAtInpoint(SMvDigiVTRSynchro * out_psMvDigiVTRSynchro ) = 0;

   /**
   * Requests the system time and the position of the VTR.
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
   * </ul>
   * @param <i>SMvDigiVTRSynchro * out_psMvDigiVTRSynchro</i>: Contains all the status information.
   */
   virtual HRESULT __stdcall GetTimestampTimecode(SMvDigiVTRSynchro * out_psMvDigiVTRSynchro ) = 0;

   /**
   * Puts the device in the requested mode.
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
   * </ul>
   * @param <i>unsigned long ulMode</i>: The mode of the device.
   * @param <i>long lValue</i>: Value associated with seek, shuttle, and variable speed modes.
   */
   virtual HRESULT __stdcall put_Mode(unsigned long in_ulMode, long in_lValue) = 0;

   /**
   * Returns the capabilities of the transport.
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
   * </ul>
   * @param <i>unsigned long in_ulCapability</i>: Specifies the capability to check.
   * @param <i>long  *out_plValue</i>: Pointer to a variable that receives a long integer.
   * @param <i>double *out_pdblValue</i>: Pointer to a variable that receives a type double.
   */
   virtual HRESULT __stdcall GetTransportCapability(unsigned long in_ulCapability,
                                                    long  *out_plValue,
                                                    double *out_pdblValue) = 0;


   /**
   * Returns additional device information.
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
   * </ul>
   * @param <i>SMvAdditionalExtDeviceInfo * out_psDeviceInfo</i>: Additional Info.
   */
   virtual HRESULT __stdcall GetAdditionalExtTransportInfo( SMvAdditionalExtDeviceInfo * out_psDeviceInfo ) = 0;

  /**
   * Sets device fast cue mode ON or OFF (internal cue).  
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
   * </ul>
   * @param <i>bool in_bFastCueMode</i>: State of fast cue mode.
   */
   virtual HRESULT __stdcall UseDeviceInternalCueMode(bool in_bInternalCueMode) = 0;

   /**
   * Sets device time format.  
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
   * </ul>
   * @param <i>WROD in_wTimeFormat</i>: 0 = 30ND, 1 = 30D, 2 = 25, 3 = 24.
   */
   virtual HRESULT __stdcall SetTimeFormat(WORD in_wTimeFormat) = 0;

   // Edit functions supported by device for print to tape.  If the device doesn't support edits, a Record command
   // must be sent to device.  A large mark in offset is usually required in this case.  A different mark out offset is
   // probably needed in this case also.  In auto edit mode, we set the mark in, mark out and preroll values on the device
   // and the device should take care of the edit.  In this case mark in and mark out should be accurate and we don't need any
   // offset.  In basic edit mode, we play the device and send an edit on and an edit off when we reach the mark in and mark out.
   // In this case a start and end offset could be required, but should have the same values.
   // User must set the edit mode of the device according to what the device supports.  We cannot query the 
   // device to know if edits are supported.  We can only detect what is supported by trying it out.
   virtual HRESULT __stdcall SetDeviceEditFunctionality(EMvDeviceEditFunctionality in_eEditFunctionsSupportedByDevice) = 0;
   virtual HRESULT __stdcall GetDeviceEditFunctionality(EMvDeviceEditFunctionality *out_peEditFunctionsSupportedByDevice) = 0;
};

#endif //IMVEXTTRANSPORT_H

