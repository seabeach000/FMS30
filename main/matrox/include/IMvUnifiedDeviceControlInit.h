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
//                    IMvUnifiedDeviceControlInit.h
//==========================================================================;
// @module  Matrox Video DirectShow
//==========================================================================;
//   Birth Date:             June 2004
//   Operating System:       WinXP
//   Author:                 Francesco De Luca
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;


#ifndef IMVUNIFIEDDEVICECONTROLINIT2_H
#define IMVUNIFIEDDEVICECONTROLINIT2_H


/**
* Interface exposed on Unified Device Control Module.  This is an internal interaface
* to initialize the Unified Device Control Module with whatever it needs from outside. 
* So far it needs the IMvClock inetface.
* @interface 
*/
interface IMvUnifiedDeviceControlInit2 : public IUnknown
{
public:

   /**
   * Set the IMvClock interface.  
   * 
   *
   * <br><b>Remark:</b>
   * <ul><i><li>The UIF will call this method on the UDC after it has created it.
   *        <li>
   * </i></ul>
   *
   * <b>Return Type:</b>
   * <ul><li>HRESULT</ul>
   *
   * <b>Return Values:</b> 
   * <ul><li>MV_NOERROR:     Succeeded.
   * </ul>
   * @param IMvClock * in_pIMvClock: Flex Clock interface.    
   */
   virtual HRESULT __stdcall  SetIMvClock( IMvClock * in_pIMvClock) = 0;

   /**
   * Set the input resolution.  
   * 
   *
   * <br><b>Remark:</b>
   * <ul><i><li>The UIF will call this method on the UDC after it has created it.
   *        <li>
   * </i></ul>
   *
   * <b>Return Type:</b>
   * <ul><li>HRESULT</ul>
   *
   * <b>Return Values:</b> 
   * <ul><li>MV_NOERROR:     Succeeded.
   * </ul>
   * @param SMvResolutionInfo * in_psResolutionInfoInput: Input Resolution.    
   * @param SMvResolutionInfo * in_psResolutionInfoOUtput: Output Resolution.    
   */
   virtual HRESULT __stdcall  SetIOResolutions( SMvResolutionInfo * in_psResolutionInfoInput, 
                                                      SMvResolutionInfo * in_psResolutionInfoOutput) = 0;

};

#endif //IMVUNIFIEDDEVICECONTROLINIT2_H