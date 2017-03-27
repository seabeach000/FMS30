//==============================================================================
//
// (c) Copyright Matrox Electronic Systems Ltd., 2009. All rights reserved. 
//
// This code and information is provided "as is" without warranty of any kind, 
// either expressed or implied, including but not limited to the implied 
// warranties of merchantability and/or fitness for a particular purpose.
//
// All code and information is provided "as is" without warranty of any kind, 
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
//===============================================================================
#pragma once


#ifdef LINUX_PLATFORM
   #include "mvLinuxGuidDef.h"
#else
   #include <initguid.h>
   #include <windows.h>
   #include <guiddef.h>
#endif


#include "mvBaseCOM.h"
#include "mvThread.h"

#include "CMvCOMPoolElement.h"
#include "mvSTLAlloc.h"
#include "mvTypes.h"

// {2CC855C7-7E91-4a41-B5EE-2ED6E1872C78}
DEFINE_GUID(IID_IMvVirtualMemoryElement, 
            0x2cc855c7, 0x7e91, 0x4a41, 0xb5, 0xee, 0x2e, 0xd6, 0xe1, 0x87, 0x2c, 0x78);

interface IMvVirtualMemoryElement : public IUnknown
{
   virtual HRESULT __stdcall GetPointerAndSize(void** out_pBuffer, unsigned long& io_rulSizeInBytes) = 0;
};
