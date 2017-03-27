// $Archive: /VP/FLEXVIDEO/LIBS/MVFFLEX3DDEVICEAPI/Inc/mvFlex3DDeviceAccessApi.h $

//==============================================================================
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
//-------------------------------------------------------------------------------

//----------------------------------------------------------------
//                         MvFlex3DDeviceAccessApi.h
//----------------------------------------------------------------
//   Birth Date:       June 2007
//   Operating System: WindowsXP
//   Author:           Simon Dompierre
//----------------------------------------------------------------
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada 
//----------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////
///
/// \mainpage Flex 3D Device Access API
/// <HR>
/// \section intro Introduction
///
/// \section copyright Legal information
/// 
/// <B> &copy; Copyright Matrox Electronic Systems Ltd., 2003. All rights reserved. </B>
///
/// This code and information is provided "as is" without warranty of any kind, 
/// either expressed or implied, including but not limited to the implied 
/// warranties of merchantability and/or fitness for a particular purpose.
///
/// Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make 
/// changes in specifications and code at any time and without notice. 
/// No responsibility is assumed by Matrox Electronic Systems Ltd. for 
/// its use; nor for any infringements of patents or other rights of 
/// third parties resulting from its use. No license is granted under 
/// any patents or patent rights of Matrox Electronic Systems Ltd. 
///
//////////////////////////////////////////////////////////////////////////

#ifndef _MvFLEX3DDEVICE_ACCESS_IF_INCLUDED_
#define _MvFLEX3DDEVICE_ACCESS_IF_INCLUDED_

#ifdef _WIN32
#include <d3d9.h>
#include "windows.h"
#include "unknwn.h"
#else
#include "mvLinuxDefinitions.h"
#endif

//
// Summary:
//    Callback interface that notifies the caller of a required action that needs to be implemented due to a change in the Direct3D device.
//
interface IMvFlex3DDeviceAccessCallback : public IUnknown
{
   //
   // Summary:
   //    Notifies the caller that the Direct3D resources can now be re-allocated.
   // Description:
   //    This method notifies that the Direct3D devices previously obtained have been reset or changed, and that the resources can be re-allocated.
   //    It also implies that the device can be re-obtained if it was returned.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_FAIL, if an unexpected error occurs.
   virtual HRESULT __stdcall NotifyDirect3DDeviceReallocateResources() = 0;

   //
   // Summary:
   //    Notifies the caller that the Direct3D resources need to be released. 
   // Description:
   //    This method notifies that the Direct3D devices previously obtained have been reset or changed, and that the allocated resources need to be released.
   //    When notified, the user application must release all Direct3D surfaces.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_FAIL, if an unexpected error occurs.
   virtual HRESULT __stdcall NotifyDirect3DDeviceReleaseResources() = 0;

   //
   // Summary:
   //    Notifies the caller that the Direct3D devices need to be returned.
   // Description:
   //    This method notifies that the Direct3D devices previously obtained need to be returned through the IMvFlex3DDeviceAccess interface. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_FAIL, if an unexpected error occurs.
   virtual HRESULT __stdcall NotifyDirect3DReturnDevice() = 0;


   //
   // Summary:
   //    Notifies the caller that the Direct3D devices is now available.
   // Description:
   //    This method notifies that the Direct3D device is now available and can be obtained.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_FAIL, if an unexpected error occurs.
   virtual HRESULT __stdcall NotifyDirect3DDeviceAvailable() = 0;

};




//
// Summary:
//    Interface that provides access to control the Flex3DDevice.
//
interface IMvFlex3DDeviceAccess : public IUnknown
{
   //
   // Summary:
   //    Returns the Direct3D device currently in use, and also accepts a callback interface to notify the caller if the Direct3D device changes.
   // Description:
   //    This method returns the Direct3D device currently in use, and also accepts a callback interface
   //    because the Direct3D device may need to be recreated if the transport resolution changes.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if a pointer is NULL.
   //    - MV_E_FAIL, if an unexpected error occurs.
   virtual HRESULT __stdcall GetDirect3DDevice
      (
      IDirect3DDevice9                 ** out_ppIDirect3DDevice,                       // Pointer to the IDirect3DDevice9 interface.
      IMvFlex3DDeviceAccessCallback * in_pIMvFlex3DDeviceAccessCallback   // Pointer to the IMvFlex3DDeviceAccessCallback interface.
      ) = 0;

   //
   // Summary:
   //    Indicates that the Direct3D device is no longer in use by the caller, and that notification of changes from the callback interface are no longer needed. 
   // Description:
   //    This method ensures that the callback interface IMvFlex3DDeviceAccessCallback will no longer be called on Direct3D changes.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if a pointer is NULL.
   //    - MV_E_FAIL, if an unexpected error occurs.
   // Remarks:
   //    - This method should only be called if the IDirect3DDevice9 interface will no longer be used, and has been released by the caller.
   virtual HRESULT __stdcall ReturnDirect3DDevice
      (
      IMvFlex3DDeviceAccessCallback * in_pIMvFlex3DDeviceAccessCallback   // Pointer to the IMvFlex3DDeviceAccessCallback interface.
      ) = 0;

   //
   // Summary:
   //    Get exclusive access to the Direct3D device.
   // Description:
   //    This call will lock access to the Direct3D device, and prevent other applications from accessing it until EndExclusiveAccess is called.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_FAIL, if an unexpected error occurs.
   virtual HRESULT __stdcall BeginExclusiveAccess() = 0;

   //
   // Summary:
   //    End exclusive access to the Direct3D device.
   // Description:
   //    This call will unlock access to the Direct3D device, and allow other applications to access it until another BeginExclusiveAccess is called.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_FAIL, if an unexpected error occurs.
   virtual HRESULT __stdcall EndExclusiveAccess() = 0;

   //
   // Summary:
   //    Allow the caller to request a one-time only notification to indicate that GetDirect3DDevice can be called.
   // Description:
   //    This method allows the caller to request a one-time only notification to indicate that GetDirect3DDevice can be called.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if a pointer is NULL.
   //    - MV_E_FAIL, if an unexpected error occurs.
   virtual HRESULT __stdcall RequestDeviceAvailableNotification
   (
      IMvFlex3DDeviceAccessCallback * in_pIMvFlex3DDeviceAccessCallback   // Pointer to the IMvFlex3DDeviceAccessCallback interface.
   ) = 0;
};

//
// Summary:
//    Interface that provides access to the Direct3DSurface interface.
//
interface IMvSurfaceAccess : public IUnknown
{
   //
   // Summary:
   //    Returns the Direct3DSurface interface for a specific surface.
   // Description:
   //    This method returns the Direct3DSurface interface for a specific surface.  
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if a pointer is NULL.
   //    - MV_E_FAIL, if an unexpected error occurs.
   virtual HRESULT __stdcall GetDirect3DSurface
      (
      IDirect3DSurface9                 ** out_ppIDirect3DSurface                       // Pointer to the IDirect3DSurface9 interface.
      ) = 0;

   //
   // Summary:
   //    Indicates that the Direct3D surface is no longer in use by the caller, and that notification of changes from the callback interface are no longer needed.
   // Description:
   //    This method ensures that the callback interface IMvFlex3DDeviceAccessCallback will no longer be called on Direct3D changes.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_FAIL, if an unexpected error occurs.
   // Remarks:
   //    - This method should only be called if the IDirect3DSurface9 interface will no longer be used, and has been released by the caller.
   virtual HRESULT __stdcall ReturnDirect3DSurface() = 0;
};

#endif //_MvFLEX3DDEVICEACCESS_IF_INCLUDED_

