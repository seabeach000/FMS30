// $Archive: /VP/FLEXVIDEO/LIBS/mvfFlex3DDeviceApi/Inc/mvFlex3DDeviceErrors.h $

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

//-------------------------------------------------------------------------------
//	created:    2003.02.07
//	filename:   mvfFlex3dDeviceErrors.h
//	author:     Luc Poirier
//===============================================================================

#ifndef _MVFLEX3DDEVICEERRORS_INCLUDED_2003_02_07_MONTREAL_
#define _MVFLEX3DDEVICEERRORS_INCLUDED_2003_02_07_MONTREAL_

#pragma once

//
// Device errors
//
#define MV_E_DEVICE_CREATION_FAILED         MAKE_HRESULT(1, 0xF3D, 0x1)
#define MV_E_SURFACE_CREATION_FAILED        MAKE_HRESULT(1, 0xF3D, 0x2)
#define MV_E_VERTEXBUFFER_CREATION_FAILED   MAKE_HRESULT(1, 0xF3D, 0x3)
#define MV_E_INDEXBUFFER_CREATION_FAILED    MAKE_HRESULT(1, 0xF3D, 0x4)
#define MV_E_ALREADY_IN_BEGINSCENE          MAKE_HRESULT(1, 0xF3D, 0x5)
#define MV_E_NOT_IN_BEGINSCENE              MAKE_HRESULT(1, 0xF3D, 0x6)
#define MV_E_CREATEPIXELSHADER_FAILED       MAKE_HRESULT(1, 0xF3D, 0x7)
#define MV_E_CREATEVERTEXDECLARATION_FAILED MAKE_HRESULT(1, 0xF3D, 0x8)
#define MV_E_CREATEVERTEXSHADER_FAILED      MAKE_HRESULT(1, 0xF3D, 0x9)
#define MV_E_CREATESTATEBLOCK_FAILED        MAKE_HRESULT(1, 0xF3D, 0x10)
#define MV_E_TRANSFORMSTATETYPE_INVALID     MAKE_HRESULT(1, 0xF3D, 0x11)
#define MV_E_SURFACE_NOT_FOUND              MAKE_HRESULT(1, 0xF3D, 0x12)
#define MV_E_VERTEXBUFFER_OVERFLOW          MAKE_HRESULT(1, 0xF3D, 0x13)
#define MV_E_INDEXBUFFER_OVERFLOW           MAKE_HRESULT(1, 0xF3D, 0x14)
#define MV_E_INVALID_DEVICE_GUID            MAKE_HRESULT(1, 0xF3D, 0x15)
#define MV_E_DEVICE_IS_LOST                 MAKE_HRESULT(1, 0xF3D, 0x16)
#define MV_E_DEVICE_IS_LOST_CRITICAL        MAKE_HRESULT(1, 0xF3D, 0x17)

#define MV_E_SURFACE_FORMAT_NOT_SUPPORTED   MAKE_HRESULT(1, 0xF3D, 0x200)
#define MV_E_SURFACE_TYPE_NOT_SUPPORTED     MAKE_HRESULT(1, 0xF3D, 0x201)

//
// DDI error
//
#define MV_E_CONNECT_DRIVER_FAILED          MAKE_HRESULT(1, 0xF3D, 0x103)
#define MV_E_RESET_DRIVER_FAILED            MAKE_HRESULT(1, 0xF3D, 0x104)
#define MV_E_RELEASE_DRIVER_FAILED          MAKE_HRESULT(1, 0xF3D, 0x105) 
#define MV_E_GET_PDEV_FAILED                MAKE_HRESULT(1, 0xF3D, 0x106)
#define MV_E_MAPMEMORY_FAILED               MAKE_HRESULT(1, 0xF3D, 0x107)
#define MV_E_BLT_FAILED                     MAKE_HRESULT(1, 0xF3D, 0x108)
#define MV_E_DESTROYDDLOCAL_FAILED          MAKE_HRESULT(1, 0xF3D, 0x109)
#define MV_E_CONTEXTDESTROY_FAILED          MAKE_HRESULT(1, 0xF3D, 0x10A)
#define MV_E_CONTEXTCREATE_FAILED           MAKE_HRESULT(1, 0xF3D, 0x10B)
#define MV_E_DESTROYSURFACE_FAILED          MAKE_HRESULT(1, 0xF3D, 0x10C)
#define MV_E_LOCK_FAILED                    MAKE_HRESULT(1, 0xF3D, 0x10D)
#define MV_E_UNLOCK_FAILED                  MAKE_HRESULT(1, 0xF3D, 0x10E)
#define MV_E_CREATESURFACEEX_FAILED         MAKE_HRESULT(1, 0xF3D, 0x10F)
#define MV_E_CREATESURFACE_FAILED           MAKE_HRESULT(1, 0xF3D, 0x110)
#define MV_E_CANCREATESURFACE_FAILED        MAKE_HRESULT(1, 0xF3D, 0x111)
#define MV_E_UNLOCKD3DBUFFER_FAILED         MAKE_HRESULT(1, 0xF3D, 0x112)
#define MV_E_LOCKD3DBUFFER_FAILED           MAKE_HRESULT(1, 0xF3D, 0x113)
#define MV_E_DESTROYD3DBUFFER_FAILED        MAKE_HRESULT(1, 0xF3D, 0x114)
#define MV_E_CREATED3DBUFFER_FAILED         MAKE_HRESULT(1, 0xF3D, 0x115)
#define MV_E_CANCREATED3DBUFFER_FAILED      MAKE_HRESULT(1, 0xF3D, 0x116)
#define MV_E_DRAWPRIMITIVES2_FAILED         MAKE_HRESULT(1, 0xF3D, 0x117)
#define MV_E_VALIDATETEXTURESTAGESTATE_FAILED MAKE_HRESULT(1, 0xF3D, 0x118)
#define MV_E_GETAVAILABLEDRIVERMEMORY_FAILED MAKE_HRESULT(1, 0xF3D, 0x119)
#define MV_E_OUTOFMEMORYDESCRIPTORS         MAKE_HRESULT(1, 0xF3D, 0x11A)

#endif

