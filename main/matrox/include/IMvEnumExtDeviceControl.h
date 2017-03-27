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
//                    IMvEnumExtDeviceControl.H
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


#ifndef IMVENUMEXTDEVICECONTROL_H
#define IMVENUMEXTDEVICECONTROL_H


/** 
* Used to enumerate the external devices currently connected to the system.
* @interface 
*/

interface IMvEnumExtDeviceControl : public IUnknown
{
public:

   /**
   * Creates another enumerator that contains the same enumeration state as the 
   * current one. Using this function, a client can record a particular point in 
   * the enumeration sequence and then return to that point at a later time. The
   * new enumerator supports the same interface as the original one.
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
   * @param <i>IMvEnumExtDeviceControl** out_ppIMvEnumExtDeviceControl</i>: Device Control Descriptor describing which Device Control module should be active.
   */
   virtual HRESULT __stdcall Clone( IMvEnumExtDeviceControl** out_ppIMvEnumExtDeviceControl ) = 0;

   /**
   * The Next method retrieves a specified number of items in the enumeration sequence.
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
   * @param <i>unsigned long in_ulElements</i>:  Unsigned long integer value that specifies the number of SMvDeviceControlDescriptor structures being requested. 
   * @param <i>SMvDeviceControlDescriptor * out_pasMvDeviceControlDescriptor</i>: Array of size in_ulElements that is filled with the SMvDeviceControlDescriptor structures.
   * @param <i>unsigned long & out_refulElementsReturned</i>:  Pointer to a variable that receives the actual number of items retrieved.
   */
   virtual HRESULT __stdcall Next( unsigned long in_ulElements, SMvDeviceControlDescriptor * out_pasMvDeviceControlDescriptor, unsigned long & out_refulElementsReturned ) = 0;

   /**
   * Resets the enumeration to the beginning.
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
   */
   virtual HRESULT __stdcall Reset() = 0;

   /**
   * Skips over the next specified number of elements in the enumeration sequence.
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
   * @param <i>const unsigned long in_ulElementsToSkip</i>:  Number of items to skip in the enumeration.
   */
   virtual HRESULT __stdcall Skip( const unsigned long  in_ulElementsToSkip ) = 0;

};

#endif //IMVENUMEXTDEVICECONTROL_H

