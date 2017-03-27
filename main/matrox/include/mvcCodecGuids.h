#pragma once

#ifdef LINUX_PLATFORM
   #include "mvLinuxGuidDef.h"
#else
   #include <guiddef.h>
#endif

//----------------------------------------------------
// old   mvcAVCIntra DLL GUID (not used any more)
//----------------------------------------------------
// {5668AD2E-AA95-4992-A545-730921C2A07F}
//DEFINE_GUID(CLSID_MvcAVCIntra, 
//            0x5668ad2e, 0xaa95, 0x4992, 0xa5, 0x45, 0x73, 0x9, 0x21, 0xc2, 0xa0, 0x7f);


//----------------------------------------------------
// mvcAVCIntra DLL GUID
// Used for the Matrox AVC-Intra encoder.
//----------------------------------------------------
// {E91E87A1-851C-4bd0-AF98-4C10D24890C3}
DEFINE_GUID(CLSID_MvcAVCIntra, 
            0xe91e87a1, 0x851c, 0x4bd0, 0xaf, 0x98, 0x4c, 0x10, 0xd2, 0x48, 0x90, 0xc3);


//----------------------------------------------------
// mvcProRes DLL GUID
// Used for the Apple ProRes codec.
//----------------------------------------------------
// {CF359856-8AC0-4a95-9A1F-9E1146714EE6}
DEFINE_GUID(CLSID_MvcProRes, 
            0xcf359856, 0x8ac0, 0x4a95, 0x9a, 0x1f, 0x9e, 0x11, 0x46, 0x71, 0x4e, 0xe6);


//----------------------------------------------------
// mvcRLE DLL GUID
// Used for the Matrox RLE decoder.
//----------------------------------------------------

// {D9D93B9C-F568-4504-B267-167DA80A73A2}
DEFINE_GUID(CLSID_MvcRLE, 
            0xd9d93b9c, 0xf568, 0x4504, 0xb2, 0x67, 0x16, 0x7d, 0xa8, 0xa, 0x73, 0xa2);

//----------------------------------------------------
// mvcDv DLL GUID
// Used for the Matrox DV codec.
//----------------------------------------------------
// {B117CE09-7056-4932-A560-913753DE9493}
DEFINE_GUID(CLSID_MvcDv, 
            0xb117ce09, 0x7056, 0x4932, 0xa5, 0x60, 0x91, 0x37, 0x53, 0xde, 0x94, 0x93);

//----------------------------------------------------
// mvcDv100 DLL GUID
// Used for the Matrox DVCPRO HD codec.
//----------------------------------------------------
// {2150AD42-606E-47c5-85C9-D2855680A0E7}
DEFINE_GUID(CLSID_MvcDv100, 
            0x2150ad42, 0x606e, 0x47c5, 0x85, 0xc9, 0xd2, 0x85, 0x56, 0x80, 0xa0, 0xe7);

//----------------------------------------------------
// mvcD10 DLL GUID
// Used for the Matrox D10, MPEG-2 I-frame, and Offline HD codecs.
//----------------------------------------------------
// {B6E36F9D-7800-476a-BC3E-E2ABEC3FFB5B}
DEFINE_GUID(CLSID_MvcD10,
            0xb6e36f9d, 0x7800, 0x476a, 0xbc, 0x3e, 0xe2, 0xab, 0xec, 0x3f, 0xfb, 0x5b);

//----------------------------------------------------
// mvcIBP DLL GUID
// Used for the Matrox MPEG-2 IBP decoder.
//----------------------------------------------------
// {787F9C21-C4B6-45d2-81B7-6329382CE51E}
DEFINE_GUID(CLSID_MvcIBP, 
            0x787f9c21, 0xc4b6, 0x45d2, 0x81, 0xb7, 0x63, 0x29, 0x38, 0x2c, 0xe5, 0x1e);

//----------------------------------------------------
// mvcMJpeg DLL GUID
// Used for the Matrox M-JPEG decoder.
//----------------------------------------------------
// {39457FF4-33C4-4afe-8F1E-F158201B45D2}
DEFINE_GUID(CLSID_MvcMJpeg, 
            0x39457ff4, 0x33c4, 0x4afe, 0x8f, 0x1e, 0xf1, 0x58, 0x20, 0x1b, 0x45, 0xd2);

//----------------------------------------------------
// mvMpegStream DLL GUID
// Used for the Flex MPEG IBP Encoder.
//----------------------------------------------------
// {E51F118D-CC47-4326-B046-84D0756A9610}
DEFINE_GUID(CLSID_MvMpegStream, 
            0xe51f118d, 0xcc47, 0x4326, 0xb0, 0x46, 0x84, 0xd0, 0x75, 0x6a, 0x96, 0x10);


//----------------------------------------------------
// MvcAACCodec DLL GUID
// Used for the Matrox AAC audio codec.
//----------------------------------------------------
// {5C2587E0-8DA9-4651-9E55-F5EE9709E616}
DEFINE_GUID(CLSID_MvcAACCodec, 
            0x5c2587e0, 0x8da9, 0x4651, 0x9e, 0x55, 0xf5, 0xee, 0x97, 0x9, 0xe6, 0x16);

// ----------------------------------------------------
// MvcH264SWCodec DLL GUID
// Used for the Matrox H.264/AVC software decoder.
// This class ID is recommended for use instead of CLSID_MvcH264SWCodec.
//----------------------------------------------------
// {0F6009D2-A846-4405-87AE-59625578C138}
DEFINE_GUID(CLSID_MvcH264SWDecoder,
            0xf6009d2, 0xa846, 0x4405, 0x87, 0xae, 0x59, 0x62, 0x55, 0x78, 0xc1, 0x38);

#define CLSID_MvcH264SWCodec CLSID_MvcH264SWDecoder

//----------------------------------------------------
// Used for the Matrox H.264/AVC software decoder 2.
// This class ID is for future use.
//----------------------------------------------------
// {63DECB69-2B78-4D8B-8473-A408FC1ABE65}
DEFINE_GUID(CLSID_MvcH264SWDecoder2,
   0x63decb69, 0x2b78, 0x4d8b, 0x84, 0x73, 0xa4, 0x8, 0xfc, 0x1a, 0xbe, 0x65);

//----------------------------------------------------
// MvfAVCH264HardwareCodec DLL GUID
// Used for the Matrox H.264/AVC hardware codec.
//----------------------------------------------------
// {B03B7970-CE07-4632-B28E-435D59B8CD19}
DEFINE_GUID(CLSID_MvfAVCH264HardwareCodec, 
            0xb03b7970, 0xce07, 0x4632, 0xb2, 0x8e, 0x43, 0x5d, 0x59, 0xb8, 0xcd, 0x19);

//----------------------------------------------------
// mvcDNxHDCodec DLL GUID
// Used for the Avid DNxHD codec.
//----------------------------------------------------
// {A401ADB0-EB07-406C-BAAC-6A4D96BF2B7F}
DEFINE_GUID(CLSID_MvcDNxHDCodec, 
            0xa401adb0, 0xeb07, 0x406c, 0xba, 0xac, 0x6a, 0x4d, 0x96, 0xbf, 0x2b, 0x7f);
//----------------------------------------------------
// mvcDolbyECodec DLL GUID
// Used for the Minnetonka SurCode for Dolby E codec.
//----------------------------------------------------
// {16822E9F-58AE-489e-9400-84D9C820FBC3}
DEFINE_GUID(CLSID_MvcDolbyECodec, 
   0x16822e9f, 0x58ae, 0x489e, 0x94, 0x0, 0x84, 0xd9, 0xc8, 0x20, 0xfb, 0xc3);

//----------------------------------------------------
// mvcH264SWEncoder DLL GUID
// Used for the Matrox H.264/AVC software encoder.
//----------------------------------------------------
// {70CEB890-1BEC-42F6-B44B-C8C7A61B0705}
DEFINE_GUID(CLSID_MvcH264SWEncoder, 
         0x70ceb890, 0x1bec, 0x42f6, 0xb4, 0x4b, 0xc8, 0xc7, 0xa6, 0x1b, 0x7, 0x5);

//----------------------------------------------------
// mvcH264QSVEncoder DLL GUID 
// Used for the Matrox H.264/AVC QSV (Intel Quick Sync Video) encoder.
//----------------------------------------------------
// {52803747-8AD4-4711-9594-F763A7259502}
DEFINE_GUID(CLSID_MvcH264QSVEncoder, 
   0x52803747, 0x8ad4, 0x4711, 0x95, 0x94, 0xf7, 0x63, 0xa7, 0x25, 0x95, 0x2);

//----------------------------------------------------
// mvcMPEG4SStPCodec DLL GUID
// Used for the Sony MPEG-4 SStP codec.
//----------------------------------------------------
// {76BF6AB0-2117-430C-9516-8F37ABA634E9}
DEFINE_GUID(CLSID_MvcMPEG4SStPCodec, 
   0x76bf6ab0, 0x2117, 0x430c, 0x95, 0x16, 0x8f, 0x37, 0xab, 0xa6, 0x34, 0xe9);

//----------------------------------------------------
// mvcH264SWEncoder DLL GUID
// Used for the Matrox H.264/AVC software encoder.
//----------------------------------------------------
// {1625E760-E297-442D-A3FF-E3236F24180C}
DEFINE_GUID(CLSID_MvH264SWEncoder2, 
   0x1625e760, 0xe297, 0x442d, 0xa3, 0xff, 0xe3, 0x23, 0x6f, 0x24, 0x18, 0xc);

//----------------------------------------------------
// mvcM264Codec DLL GUID
// Used for the Matrox H.264 Hardware Encoder (M264).
//----------------------------------------------------
// {6e8a39cb-61f6-4686-9f6c-04ab7e9b3860}
DEFINE_GUID(CLSID_MvM264Encoder,
   0x6e8a39cb, 0x61f6, 0x4686, 0x9f, 0x6c, 0x04, 0xab, 0x7e, 0x9b, 0x38, 0x60);

//----------------------------------------------------
// mvcH264Sv2Codec DLL GUID
// Used for the Matrox H.264 Hardware Decoder (M264).
//----------------------------------------------------
// {A99DB4C7-F468-4CB8-BF77-D10A17F95984}
DEFINE_GUID(CLSID_MvM264Decoder, 
   0xa99db4c7, 0xf468, 0x4cb8, 0xbf, 0x77, 0xd1, 0x0a, 0x17, 0xf9, 0x59, 0x84);
