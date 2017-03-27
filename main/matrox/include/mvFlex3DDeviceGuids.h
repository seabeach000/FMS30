// $Archive: /VP/FLEXVIDEO/LIBS/MVFFLEX3DDEVICEAPI/Inc/mvFlex3DDeviceGuids.h $

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
//                         mvfFlex3DDevice_GUIDS.h
//----------------------------------------------------------------
//   Birth Date:       Decmber 2002
//   Operating System: WindowsXP
//   Author:           Luc Poirier
//----------------------------------------------------------------
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada 
//----------------------------------------------------------------
// This make possible to define the GUID without redefining the structures.

#ifdef __DECLARE_ASSOC__
   #ifdef __MXVFX_MXGL_IDS_H_GUID__
      #undef __MXVFX_MXGL_IDS_H_GUID__
   #endif
#endif


#ifndef  __MXVFX_MXGL_IDS_H_GUID__
#define  __MXVFX_MXGL_IDS_H_GUID__



#ifndef OUR_GUID_ENTRY
	#define OUR_GUID_ENTRY(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
	DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8);
#endif

///////////////////////////////////////////////////////////////////////////

// Flex 3D Device Access Callback GUID
// {817505C8-9247-4eca-8157-7B0CCA844630}
DEFINE_GUID(IID_IMvFlex3DDeviceAccessCallback, 
            0x817505c8, 0x9247, 0x4eca, 0x81, 0x57, 0x7b, 0xc, 0xca, 0x84, 0x46, 0x30);


// Flex 3D Device Access GUID
// {DA606C58-46A5-4e8b-848C-45F0638AAB2D}
DEFINE_GUID(IID_IMvFlex3DDeviceAccess, 
            0xda606c58, 0x46a5, 0x4e8b, 0x84, 0x8c, 0x45, 0xf0, 0x63, 0x8a, 0xab, 0x2d);

// Surface Access GUID
// {67DC7AD0-B77A-4ad5-B5A0-39E135B63611}
DEFINE_GUID(IID_IMvSurfaceAccess, 
            0x67dc7ad0, 0xb77a, 0x4ad5, 0xb5, 0xa0, 0x39, 0xe1, 0x35, 0xb6, 0x36, 0x11);

#endif



