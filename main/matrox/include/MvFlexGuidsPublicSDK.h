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

#ifndef  __MvFlexGuidsPublicSDK_h_h0AB95510B7AE439497787E62586A519E
#define  __MvFlexGuidsPublicSDK_h_h0AB95510B7AE439497787E62586A519E


#ifdef LINUX_PLATFORM
   #include "mvLinuxGuidDef.h"
#else
   #include "guiddef.h"
#endif


//////////////////////////////////////////////////////////////////////////////////
// Flex Clock
//////////////////////////////////////////////////////////////////////////////////

// {8A53BE68-99E6-435b-ABBC-FFA7B7ED3383}
DEFINE_GUID(IID_IMvClock, 
            0x8a53be68, 0x99e6, 0x435b, 0xab, 0xbc, 0xff, 0xa7, 0xb7, 0xed, 0x33, 0x83);

//////////////////////////////////////////////////////////////////////////////////
// Flex AV Content
//////////////////////////////////////////////////////////////////////////////////

// {E7906166-30F4-4f30-AE1E-2FCFAE969330}
DEFINE_GUID(IID_IMvAVContent, 
            0xe7906166, 0x30f4, 0x4f30, 0xae, 0x1e, 0x2f, 0xcf, 0xae, 0x96, 0x93, 0x30);


//////////////////////////////////////////////////////////////////////////
// AVContent pool manager interfaces
//////////////////////////////////////////////////////////////////////////

// {8B54BCFF-FE27-4068-8B31-33B9D17B3450}
DEFINE_GUID(IID_IMvAVContentCompletionObserver,
			0x8b54bcff, 0xfe27, 0x4068, 0x8b, 0x31, 0x33, 0xb9, 0xd1, 0x7b, 0x34, 0x50);

// {DE31B6F8-6A95-41f7-92E7-18B5B935CD57}
DEFINE_GUID(IID_IMvAVContentReceiver, 
            0xde31b6f8, 0x6a95, 0x41f7, 0x92, 0xe7, 0x18, 0xb5, 0xb9, 0x35, 0xcd, 0x57);



//////////////////////////////////////////////////////////////////////////////////
// Flex Surface
//////////////////////////////////////////////////////////////////////////////////

// {6DAB69A7-9F9B-401f-A0CF-E411F2A680A7}
DEFINE_GUID(IID_IMvSurface, 
            0x6dab69a7, 0x9f9b, 0x401f, 0xa0, 0xcf, 0xe4, 0x11, 0xf2, 0xa6, 0x80, 0xa7);

//////////////////////////////////////////////////////////////////////////////////
// Flex Audio Samples
//////////////////////////////////////////////////////////////////////////////////


// {20B1F28E-A524-4997-A768-F4FF6342363E}
DEFINE_GUID(IID_IMvAudioSamples, 
            0x20b1f28e, 0xa524, 0x4997, 0xa7, 0x68, 0xf4, 0xff, 0x63, 0x42, 0x36, 0x3e);

//////////////////////////////////////////////////////////////////////////////////
// Flex Surface container
//////////////////////////////////////////////////////////////////////////////////

// {7A75A879-51F9-4e7d-BAC0-3283764AF1D8}
DEFINE_GUID(IID_IMvContainer, 
            0x7a75a879, 0x51f9, 0x4e7d, 0xba, 0xc0, 0x32, 0x83, 0x76, 0x4a, 0xf1, 0xd8);


//////////////////////////////////////////////////////////////////////////////////
// Flex Hardware Profile Enumerator interface
//////////////////////////////////////////////////////////////////////////////////

// {69B61FDF-531D-4272-8362-288DD7E4F5EA}
DEFINE_GUID(IID_IMvHardwareProfileEnumerator, 
            0x69b61fdf, 0x531d, 0x4272, 0x83, 0x62, 0x28, 0x8d, 0xd7, 0xe4, 0xf5, 0xea);

//////////////////////////////////////////////////////////////////////////////////
// IMvEffectEnumerator interface
//////////////////////////////////////////////////////////////////////////////////

// {CF2556AF-02C8-42f4-B86C-67835F10CFE1}
DEFINE_GUID(IID_IMvEffectEnumerator, 
            0xcf2556af, 0x2c8, 0x42f4, 0xb8, 0x6c, 0x67, 0x83, 0x5f, 0x10, 0xcf, 0xe1);

//////////////////////////////////////////////////////////////////////////
// Setting manager custom type
//////////////////////////////////////////////////////////////////////////

// {E9615F53-9222-4254-ADD7-7DB710543AD0}
DEFINE_GUID(IID_IMvEffectSettingsPool, 
            0xe9615f53, 0x9222, 0x4254, 0xad, 0xd7, 0x7d, 0xb7, 0x10, 0x54, 0x3a, 0xd0);

// {14BB86EA-36BC-4a50-AC90-B23645BFA538}
DEFINE_GUID(IID_IMvEffectSettings, 
            0x14bb86ea, 0x36bc, 0x4a50, 0xac, 0x90, 0xb2, 0x36, 0x45, 0xbf, 0xa5, 0x38);

// {F161C61B-F40C-44e1-B1EE-037CC641F39E}
DEFINE_GUID(SMTYPE_EffectList, 
            0xf161c61b, 0xf40c, 0x44e1, 0xb1, 0xee, 0x3, 0x7c, 0xc6, 0x41, 0xf3, 0x9e);


// Effect settings IIDs

// {8462424C-9F0C-4991-88A0-2E45FB136C71}
DEFINE_GUID(IID_IMvCompositorSettings, 
            0x8462424c, 0x9f0c, 0x4991, 0x88, 0xa0, 0x2e, 0x45, 0xfb, 0x13, 0x6c, 0x71);

// {5C3E3B6D-0415-4683-98CE-A9C495E7AEF6}
DEFINE_GUID(IID_IMvHardwareCompositorSettings, 
   0x5c3e3b6d, 0x415, 0x4683, 0x98, 0xce, 0xa9, 0xc4, 0x95, 0xe7, 0xae, 0xf6);

// {6AF0F733-B7C6-43C8-9BA4-F7AB06DB308A}
DEFINE_GUID(IID_IMvAudioMixerEffectSettings, 
            0x6af0f733, 0xb7c6, 0x43c8, 0x9b, 0xa4, 0xf7, 0xab, 0x6, 0xdb, 0x30, 0x8a);

// {23AB2286-887A-4a9f-BDBD-D67BE13A0BA7}
DEFINE_GUID(IID_IMvColorCorrectionEffectSettings, 
            0x23ab2286, 0x887a, 0x4a9f, 0xbd, 0xbd, 0xd6, 0x7b, 0xe1, 0x3a, 0xb, 0xa7);

// {C80C230E-5BD0-4cf1-8AC3-0F9313C9B44D}
DEFINE_GUID(IID_IMvSelectiveColorCorrectionEffectSettings, 
            0xc80c230e, 0x5bd0, 0x4cf1, 0x8a, 0xc3, 0xf, 0x93, 0x13, 0xc9, 0xb4, 0x4d);

// {8A766C03-A2C9-4491-B190-76F4895D0A50}
DEFINE_GUID(IID_IMvChromaKeyEffectSettings, 
            0x8a766c03, 0xa2c9, 0x4491, 0xb1, 0x90, 0x76, 0xf4, 0x89, 0x5d, 0xa, 0x50);

// {15FC5031-FE56-4AF7-B46C-72CCBC480C99}
DEFINE_GUID(IID_IMvChromaKeyShadowEffectSettings, 
            0x15fc5031, 0xfe56, 0x4af7, 0xb4, 0x6c, 0x72, 0xcc, 0xbc, 0x48, 0x0c, 0x99);

// {9910C0C6-0A8A-44AB-B58B-C96C07C6624A}
DEFINE_GUID(IID_IMvLumaKeyEffectSettings, 
            0x9910c0c6, 0x0a8a, 0x44ab, 0xb5, 0x8b, 0xc9, 0x6c, 0x07, 0xc6, 0x62, 0x4a);

// {7BC423DE-36E3-418a-A61F-066CE3B34D3C}
DEFINE_GUID(IID_IMvWipesEffectSettings, 
            0x7bc423de, 0x36e3, 0x418a, 0xa6, 0x1f, 0x6, 0x6c, 0xe3, 0xb3, 0x4d, 0x3c);

// {854D3B16-3B55-4cd9-8273-59C69CCCCF1E}
DEFINE_GUID(IID_IMvDveEffectSettings, 
            0x854d3b16, 0x3b55, 0x4cd9, 0x82, 0x73, 0x59, 0xc6, 0x9c, 0xcc, 0xcf, 0x1e);

// {F3E34868-5621-4018-B5D9-820BF4C5A55A}
DEFINE_GUID(IID_IMvShadowEffectSettings, 
            0xf3e34868, 0x5621, 0x4018, 0xb5, 0xd9, 0x82, 0xb, 0xf4, 0xc5, 0xa5, 0x5a);

// {0DC6CC6D-B27E-46c2-8EB7-6D3A55B509AE}
DEFINE_GUID(IID_IMvAnamorphicEffectSettings, 
            0xdc6cc6d, 0xb27e, 0x46c2, 0x8e, 0xb7, 0x6d, 0x3a, 0x55, 0xb5, 0x9, 0xae);

// {B74FAEB0-1F74-46a2-815E-C37E701856B2}
DEFINE_GUID(IID_IMvMaskEffectSettings, 
            0xb74faeb0, 0x1f74, 0x46a2, 0x81, 0x5e, 0xc3, 0x7e, 0x70, 0x18, 0x56, 0xb2);

// {6032E9FD-41A5-4099-A7E6-36EEEE1AADD4}
DEFINE_GUID(IID_IMvPageCurlEffectSettings, 
            0x6032e9fd, 0x41a5, 0x4099, 0xa7, 0xe6, 0x36, 0xee, 0xee, 0x1a, 0xad, 0xd4);

// {248DDE49-4A8D-4b70-A0FC-5F6A5C8363C1}
DEFINE_GUID(IID_IMvSoftFocusEffectSettings, 
            0x248dde49, 0x4a8d, 0x4b70, 0xa0, 0xfc, 0x5f, 0x6a, 0x5c, 0x83, 0x63, 0xc1);

// {EB4FEC98-78E8-4ab1-9E46-ABA07B5BF5F1}
DEFINE_GUID(IID_IMvPositionerEffectSettings, 
            0xeb4fec98, 0x78e8, 0x4ab1, 0x9e, 0x46, 0xab, 0xa0, 0x7b, 0x5b, 0xf5, 0xf1);

// {B80C3472-C6A7-4ad4-B395-787139B7D83E}
DEFINE_GUID(IID_IMvMaterialSlabEffectSettings, 
            0xb80c3472, 0xc6a7, 0x4ad4, 0xb3, 0x95, 0x78, 0x71, 0x39, 0xb7, 0xd8, 0x3e);

// {A43ACDE3-BA51-4483-A75E-3D8A2F5D76EA}
DEFINE_GUID(IID_IMvDissolveEffectSettings, 
            0xa43acde3, 0xba51, 0x4483, 0xa7, 0x5e, 0x3d, 0x8a, 0x2f, 0x5d, 0x76, 0xea);

// {69BD7D05-990C-444c-B3B7-9BC7AD32A4ED}
DEFINE_GUID(IID_IMvfClipperEffectSettings, 
            0x69bd7d05, 0x990c, 0x444c, 0xb3, 0xb7, 0x9b, 0xc7, 0xad, 0x32, 0xa4, 0xed);

// {CC8993F3-0C0A-4ce6-B7E9-D792956B1EC2}
DEFINE_GUID(IID_IMv4CornerPinEffectSettings, 
            0xcc8993f3, 0xc0a, 0x4ce6, 0xb7, 0xe9, 0xd7, 0x92, 0x95, 0x6b, 0x1e, 0xc2);

// {0073AA9A-DE07-401d-A10A-A2611D57C9E4}
DEFINE_GUID(IID_IMvLensFlareEffectSettings, 
            0x73aa9a, 0xde07, 0x401d, 0xa1, 0xa, 0xa2, 0x61, 0x1d, 0x57, 0xc9, 0xe4);

// {6DD99830-794D-467d-8A20-B70832AFAE73}
DEFINE_GUID(IID_IMvSampleSoftwareEffectSettings, 
            0x6dd99830, 0x794d, 0x467d, 0x8a, 0x20, 0xb7, 0x8, 0x32, 0xaf, 0xae, 0x73);

// {0CE01630-FFE0-48d1-8783-46F1DA321864}
DEFINE_GUID(IID_IMvDeinterlaceEffectSettings, 
            0xce01630, 0xffe0, 0x48d1, 0x87, 0x83, 0x46, 0xf1, 0xda, 0x32, 0x18, 0x64);

// {E34BDDCC-D61A-4c4e-A1B7-F64C65800FB5}
DEFINE_GUID(IID_IMvMaskMosaicEffectSettings, 
			0xe34bddcc, 0xd61a, 0x4c4e, 0xa1, 0xb7, 0xf6, 0x4c, 0x65, 0x80, 0xf, 0xb5);

// {EAC5A109-947C-45d6-B55D-D7DB66036C41}
DEFINE_GUID(IID_IMvMaskBlurEffectSettings, 
            0xeac5a109, 0x947c, 0x45d6, 0xb5, 0x5d, 0xd7, 0xdb, 0x66, 0x3, 0x6c, 0x41);

// {0775933E-A354-4714-BDA6-D28B79D63E41}
DEFINE_GUID(IID_IMvAPTEffectSettings, 
            0x775933e, 0xa354, 0x4714, 0xbd, 0xa6, 0xd2, 0x8b, 0x79, 0xd6, 0x3e, 0x41);
           
// {FF5C52A0-120B-48bf-957A-92871FF1E1ED}
DEFINE_GUID(IID_IMv2DDveEffectSettings, 
            0xff5c52a0, 0x120b, 0x48bf, 0x95, 0x7a, 0x92, 0x87, 0x1f, 0xf1, 0xe1, 0xed);

// {63E2DEE7-20BB-472a-8440-12CB73614EB8}
DEFINE_GUID(IID_IMvVolumetricLightEffectSettings, 
            0x63e2dee7, 0x20bb, 0x472a, 0x84, 0x40, 0x12, 0xcb, 0x73, 0x61, 0x4e, 0xb8);
            
// {DAB92710-F6F3-4be5-95D8-54B79C8935C7}
DEFINE_GUID(IID_IMvTrackMatteEffectSettings, 
            0xdab92710, 0xf6f3, 0x4be5, 0x95, 0xd8, 0x54, 0xb7, 0x9c, 0x89, 0x35, 0xc7);

// {27AFAB44-4B57-4522-8AF9-605704D6C5B2}
DEFINE_GUID(IID_IMvDifferenceMatteEffectSettings, 
            0x27afab44, 0x4b57, 0x4522, 0x8a, 0xf9, 0x60, 0x57, 0x4, 0xd6, 0xc5, 0xb2);

// {EE07823B-A7E5-48a9-AAF1-A736C9BB5922}
DEFINE_GUID(IID_IMvMultiCamEffectSettings, 
            0xee07823b, 0xa7e5, 0x48a9, 0xaa, 0xf1, 0xa7, 0x36, 0xc9, 0xbb, 0x59, 0x22);

// {AC42519E-5F34-46a1-BD80-BD38085B6B19}
DEFINE_GUID(IID_ImvcUpscaleToHDEffectSettings, 
0xac42519e, 0x5f34, 0x46a1, 0xbd, 0x80, 0xbd, 0x38, 0x8, 0x5b, 0x6b, 0x19);

// {8EDF5560-C90F-4a2e-96A5-D501121F6129}
DEFINE_GUID(IID_IMvCrystallizeEffectSettings, 
            0x8edf5560, 0xc90f, 0x4a2e, 0x96, 0xa5, 0xd5, 0x1, 0x12, 0x1f, 0x61, 0x29);

// {1C6B7514-A2D9-44e4-9D42-A061FBF4CCD9}
DEFINE_GUID(IID_IMvOldMovieEffectSettings, 
            0x1c6b7514, 0xa2d9, 0x44e4, 0x9d, 0x42, 0xa0, 0x61, 0xfb, 0xf4, 0xcc, 0xd9);

// {08515C51-034C-4549-9898-453D47BD6E7C}
DEFINE_GUID(IID_IMvImpressionistEffectSettings, 
            0x8515c51, 0x34c, 0x4549, 0x98, 0x98, 0x45, 0x3d, 0x47, 0xbd, 0x6e, 0x7c);

// {F482F267-A269-473e-B116-DA25AEE7A332}
DEFINE_GUID(IID_IMvSwirlEffectSettings, 
            0xf482f267, 0xa269, 0x473e, 0xb1, 0x16, 0xda, 0x25, 0xae, 0xe7, 0xa3, 0x32);

// {285D5F14-D2AA-4c81-90A8-0CFAF6286527}
DEFINE_GUID(IID_IMvRippleEffectSettings, 
            0x285d5f14, 0xd2aa, 0x4c81, 0x90, 0xa8, 0xc, 0xfa, 0xf6, 0x28, 0x65, 0x27);

// {24FB7CFF-4C9B-4430-A3D7-C23524590F7A}
DEFINE_GUID(IID_IMvCubeEffectSettings, 
            0x24fb7cff, 0x4c9b, 0x4430, 0xa3, 0xd7, 0xc2, 0x35, 0x24, 0x59, 0xf, 0x7a);

// {481484BC-F99A-4739-81A9-A0962F1803FB}
DEFINE_GUID(IID_IMvTimecodeEffectSettings, 
            0x481484bc, 0xf99a, 0x4739, 0x81, 0xa9, 0xa0, 0x96, 0x2f, 0x18, 0x3, 0xfb);

// {BB7F1D74-BE87-4541-B540-6A9295773847}
DEFINE_GUID(IID_IMvAdvancedMaskEffectSettings, 
            0xbb7f1d74, 0xbe87, 0x4541, 0xb5, 0x40, 0x6a, 0x92, 0x95, 0x77, 0x38, 0x47);

// {6E73FB5A-C6DF-4289-A69F-A832D6E4CBDE}
DEFINE_GUID(IID_IMv3DSphereEffectSettings, 
            0x6e73fb5a, 0xc6df, 0x4289, 0xa6, 0x9f, 0xa8, 0x32, 0xd6, 0xe4, 0xcb, 0xde);

// {D184B0E0-9319-467e-93FF-9E00BA47AD18}
DEFINE_GUID(IID_IMvExplosionEffectSettings, 
            0xd184b0e0, 0x9319, 0x467e, 0x93, 0xff, 0x9e, 0x0, 0xba, 0x47, 0xad, 0x18);

//////////////////////////////////////////////////////////////////////////
// Effect CLSIDs
//////////////////////////////////////////////////////////////////////////

// {F5A9CB36-486F-4f15-8ACA-D28819D83476}
DEFINE_GUID(CLSID_MvDveEffect, 
            0xf5a9cb36, 0x486f, 0x4f15, 0x8a, 0xca, 0xd2, 0x88, 0x19, 0xd8, 0x34, 0x76);

// {834FEB2A-3038-444b-BF06-2B704C2A6010}
DEFINE_GUID(CLSID_MvTrackMatteEffect, 
            0x834feb2a, 0x3038, 0x444b, 0xbf, 0x6, 0x2b, 0x70, 0x4c, 0x2a, 0x60, 0x10);

// {5D580179-E539-40fa-9E9F-6D57D885F65F}
DEFINE_GUID(CLSID_MvDifferenceMatteEffect, 
            0x5d580179, 0xe539, 0x40fa, 0x9e, 0x9f, 0x6d, 0x57, 0xd8, 0x85, 0xf6, 0x5f);

// {DBD793A5-A094-46b0-91DE-2ED767D715F0}
DEFINE_GUID(CLSID_MvMultiCamEffect, 
            0xdbd793a5, 0xa094, 0x46b0, 0x91, 0xde, 0x2e, 0xd7, 0x67, 0xd7, 0x15, 0xf0);

// {7B323B19-A857-4751-96CD-B2017E6A3B1A}
DEFINE_GUID(CLSID_MvShadowEffect, 
            0x7b323b19, 0xa857, 0x4751, 0x96, 0xcd, 0xb2, 0x1, 0x7e, 0x6a, 0x3b, 0x1a);

// {9985913D-0A61-4308-9D18-A6A3EDB2DE18}
DEFINE_GUID(CLSID_MvAnamorphicEffect, 
            0x9985913d, 0xa61, 0x4308, 0x9d, 0x18, 0xa6, 0xa3, 0xed, 0xb2, 0xde, 0x18);

// {6E3A52B5-AAB0-4d44-B776-E212B41E2C9E}
DEFINE_GUID(CLSID_MvMaskEffect, 
            0x6e3a52b5, 0xaab0, 0x4d44, 0xb7, 0x76, 0xe2, 0x12, 0xb4, 0x1e, 0x2c, 0x9e);

// {B4CD6FCF-0DCC-4a73-B84F-FCD5B877122E}
DEFINE_GUID(CLSID_MvPageCurlEffect,
            0xb4cd6fcf, 0xdcc, 0x4a73, 0xb8, 0x4f, 0xfc, 0xd5, 0xb8, 0x77, 0x12, 0x2e);

// {14943A1A-0D1A-4f48-95BB-E003FBE50866}
DEFINE_GUID(CLSID_MvBlurEffect, 
            0x14943a1a, 0xd1a, 0x4f48, 0x95, 0xbb, 0xe0, 0x3, 0xfb, 0xe5, 0x8, 0x66);

// {41DC553E-4A99-4358-BB71-47E8A55383F6}
DEFINE_GUID(CLSID_MvSoftFocusEffect, 
            0x41dc553e, 0x4a99, 0x4358, 0xbb, 0x71, 0x47, 0xe8, 0xa5, 0x53, 0x83, 0xf6);

// {7265DB5E-65F2-4ebd-B2BD-65808612BAD6}
DEFINE_GUID(CLSID_Mv3DShapesEffect, 
            0x7265db5e, 0x65f2, 0x4ebd, 0xb2, 0xbd, 0x65, 0x80, 0x86, 0x12, 0xba, 0xd6);

// {44ED2F51-F9C4-4c89-8571-7FAC582DD639}
DEFINE_GUID(CLSID_MvPositionerEffect, 
            0x44ed2f51, 0xf9c4, 0x4c89, 0x85, 0x71, 0x7f, 0xac, 0x58, 0x2d, 0xd6, 0x39);

// {FFA2EE4B-A126-492a-A0C8-E3AB7C1E195A}
DEFINE_GUID(CLSID_MvMaterialSlabEffect, 
            0xffa2ee4b, 0xa126, 0x492a, 0xa0, 0xc8, 0xe3, 0xab, 0x7c, 0x1e, 0x19, 0x5a);

// {3C625E94-384B-43f3-AE72-C65305D706A1}
DEFINE_GUID(CLSID_MvDissolveEffect, 
            0x3c625e94, 0x384b, 0x43f3, 0xae, 0x72, 0xc6, 0x53, 0x5, 0xd7, 0x6, 0xa1);

// {6ED36128-05A8-4551-84A5-BD84C698CBB3}
DEFINE_GUID(CLSID_MvColorCorrectionEffect, 
            0x6ed36128, 0x5a8, 0x4551, 0x84, 0xa5, 0xbd, 0x84, 0xc6, 0x98, 0xcb, 0xb3);

// {F2C7AE2E-B882-4319-A3B4-5FAAE39BF432}
DEFINE_GUID(CLSID_MvSelectiveColorCorrectionEffect, 
            0xf2c7ae2e, 0xb882, 0x4319, 0xa3, 0xb4, 0x5f, 0xaa, 0xe3, 0x9b, 0xf4, 0x32);

// {7567F746-549E-482c-8D83-7D77E292252F}
DEFINE_GUID(CLSID_MvChromaKeyEffect,
            0x7567f746, 0x549e, 0x482c, 0x8d, 0x83, 0x7d, 0x77, 0xe2, 0x92, 0x25, 0x2f);

// {4EDDC4A0-F5F6-4C37-AA76-B231C79ABA4C}
DEFINE_GUID(CLSID_MvChromaKeyShadowEffect,
            0x4eddc4a0, 0xf5f6, 0x4c37, 0xaa, 0x76, 0xb2, 0x31, 0xc7, 0x9a, 0xba, 0x4c);

// {A9CC31A8-8D01-4871-9271-83E6A8FF1585}
DEFINE_GUID(CLSID_MvLumaKeyEffect,
            0xa9cc31a8, 0x8d01, 0x4871, 0x92, 0x71, 0x83, 0xe6, 0xa8, 0xff, 0x15, 0x85);

// {811E0F9C-C374-44af-8A28-6B5FCC5D1506}
DEFINE_GUID(CLSID_MvWipesEffect, 
            0x811e0f9c, 0xc374, 0x44af, 0x8a, 0x28, 0x6b, 0x5f, 0xcc, 0x5d, 0x15, 0x6);

// {992CACF6-9CBF-4E86-8F7F-04A7D264BCE9}
DEFINE_GUID(CLSID_MvaAudioMixer, 
            0x992cacf6, 0x9cbf, 0x4e86, 0x8f, 0x7f, 0x4, 0xa7, 0xd2, 0x64, 0xbc, 0xe9);

// {F405C842-B680-496d-96B0-79F90B766EB4}
DEFINE_GUID(CLSID_IMvCompositor, 
            0xf405c842, 0xb680, 0x496d, 0x96, 0xb0, 0x79, 0xf9, 0xb, 0x76, 0x6e, 0xb4);

// {D600CF14-EADB-492a-B354-B1C471F4A60B}
DEFINE_GUID(CLSID_MvfClipper, 
            0xd600cf14, 0xeadb, 0x492a, 0xb3, 0x54, 0xb1, 0xc4, 0x71, 0xf4, 0xa6, 0xb);

// {FEDD554D-B886-4ec3-ACBB-A4B1EC02BA95}
DEFINE_GUID(CLSID_Mv4CornerPinEffect, 
            0xfedd554d, 0xb886, 0x4ec3, 0xac, 0xbb, 0xa4, 0xb1, 0xec, 0x2, 0xba, 0x95);

// {DFDCD9CC-3BC1-469d-A3AF-173C67C5E288}
DEFINE_GUID(CLSID_MvLensFlareEffect, 
            0xdfdcd9cc, 0x3bc1, 0x469d, 0xa3, 0xaf, 0x17, 0x3c, 0x67, 0xc5, 0xe2, 0x88);

// {BDD55EAE-C6AD-4ea4-BE6E-C6D3261C714C}
DEFINE_GUID(CLSID_MvSampleSoftwareEffect, 
            0xbdd55eae, 0xc6ad, 0x4ea4, 0xbe, 0x6e, 0xc6, 0xd3, 0x26, 0x1c, 0x71, 0x4c);

// {AAB649D1-14EE-4be1-846E-7E33F75CD791}
DEFINE_GUID(CLSID_MvDeinterlaceEffect, 
            0xaab649d1, 0x14ee, 0x4be1, 0x84, 0x6e, 0x7e, 0x33, 0xf7, 0x5c, 0xd7, 0x91);

// {B99CD90C-38D6-4f5c-9D57-70F0854C37A3}
DEFINE_GUID(CLSID_MvMaskMosaicEffect, 
			0xb99cd90c, 0x38d6, 0x4f5c, 0x9d, 0x57, 0x70, 0xf0, 0x85, 0x4c, 0x37, 0xa3);

// {CB07EFA4-6AAB-4eb5-9241-1E3F874E64F8}
DEFINE_GUID(CLSID_MvMaskBlurEffect, 
            0xcb07efa4, 0x6aab, 0x4eb5, 0x92, 0x41, 0x1e, 0x3f, 0x87, 0x4e, 0x64, 0xf8);

// {EEE5ADCF-B3EE-447a-8E05-853FDE4F6F37}
DEFINE_GUID(CLSID_MvAPTEffect, 
            0xeee5adcf, 0xb3ee, 0x447a, 0x8e, 0x5, 0x85, 0x3f, 0xde, 0x4f, 0x6f, 0x37);

// {28A85F6C-3D37-4ae9-AEC5-964DA04674FC}
DEFINE_GUID(CLSID_Mv2DDveEffect, 
            0x28a85f6c, 0x3d37, 0x4ae9, 0xae, 0xc5, 0x96, 0x4d, 0xa0, 0x46, 0x74, 0xfc);

// {97222A26-797E-4575-9BBC-FD51978596D3}
DEFINE_GUID(CLSID_MvVolumetricLightEffect, 
            0x97222a26, 0x797e, 0x4575, 0x9b, 0xbc, 0xfd, 0x51, 0x97, 0x85, 0x96, 0xd3);

// {45173E3B-7A94-4ab3-A83D-D043D7ADB7C4}
DEFINE_GUID(CLSID_mvcUpscaleToHDEffect, 
            0x45173e3b, 0x7a94, 0x4ab3, 0xa8, 0x3d, 0xd0, 0x43, 0xd7, 0xad, 0xb7, 0xc4);

// {81C738B6-F4D6-4103-B679-A71A3CB8ADDB}
DEFINE_GUID(CLSID_MvCrystallizeEffect, 
            0x81c738b6, 0xf4d6, 0x4103, 0xb6, 0x79, 0xa7, 0x1a, 0x3c, 0xb8, 0xad, 0xdb);

// {CF13B4B6-E135-4455-90B0-FCA0EF0D449A}
DEFINE_GUID(CLSID_MvOldMovieEffect, 
            0xcf13b4b6, 0xe135, 0x4455, 0x90, 0xb0, 0xfc, 0xa0, 0xef, 0xd, 0x44, 0x9a);

// {042FC9B7-2B8F-4e12-9EE9-221B2ECE271E}
DEFINE_GUID(CLSID_MvImpressionistEffect, 
            0x42fc9b7, 0x2b8f, 0x4e12, 0x9e, 0xe9, 0x22, 0x1b, 0x2e, 0xce, 0x27, 0x1e);

// {687F30D8-AF40-4c23-B7E1-EA4D97DAB3A6}
DEFINE_GUID(CLSID_MvSwirlEffect, 
            0x687f30d8, 0xaf40, 0x4c23, 0xb7, 0xe1, 0xea, 0x4d, 0x97, 0xda, 0xb3, 0xa6);

// {B1246603-6E6A-4d8e-B322-0DB96B51A1E8}
DEFINE_GUID(CLSID_MvRippleEffect, 
            0xb1246603, 0x6e6a, 0x4d8e, 0xb3, 0x22, 0xd, 0xb9, 0x6b, 0x51, 0xa1, 0xe8);

// {0A033A7B-EC85-467c-9999-257A47F33669}
DEFINE_GUID(CLSID_MvCubeEffect, 
            0xa033a7b, 0xec85, 0x467c, 0x99, 0x99, 0x25, 0x7a, 0x47, 0xf3, 0x36, 0x69);

// {1DB360A4-33D5-466b-9A21-A5F751A87E28}
DEFINE_GUID(CLSID_MvTimecodeEffect, 
            0x1db360a4, 0x33d5, 0x466b, 0x9a, 0x21, 0xa5, 0xf7, 0x51, 0xa8, 0x7e, 0x28);

// {CCA21425-E553-44ea-9DE9-9734F70471DC}
DEFINE_GUID(CLSID_MvAdvancedMaskEffect, 
            0xcca21425, 0xe553, 0x44ea, 0x9d, 0xe9, 0x97, 0x34, 0xf7, 0x4, 0x71, 0xdc);

// {565F5171-4748-4f27-B056-697D9214C907}
DEFINE_GUID(CLSID_Mv3DSphereEffect, 
            0x565f5171, 0x4748, 0x4f27, 0xb0, 0x56, 0x69, 0x7d, 0x92, 0x14, 0xc9, 0x7);

// {5068814C-A4AD-459e-AF94-F69F546F798C}
DEFINE_GUID(CLSID_MvExplosionEffect, 
            0x5068814c, 0xa4ad, 0x459e, 0xaf, 0x94, 0xf6, 0x9f, 0x54, 0x6f, 0x79, 0x8c);

//////////////////////////////////////////////////////////////////////////
//
//    GFX type GUIDs
//
//////////////////////////////////////////////////////////////////////////

// {CFC245CB-3504-4efc-92BC-C48C9D8A2129}
DEFINE_GUID(CLSID_GFXTypeLensFlare, 
            0xcfc245cb, 0x3504, 0x4efc, 0x92, 0xbc, 0xc4, 0x8c, 0x9d, 0x8a, 0x21, 0x29);

// {F2BFBEDC-4A79-4b27-960B-E98B5B715713}
DEFINE_GUID(CLSID_GFXTypeGlareTexture, 
            0xf2bfbedc, 0x4a79, 0x4b27, 0x96, 0xb, 0xe9, 0x8b, 0x5b, 0x71, 0x57, 0x13);

// {CAB5A5F0-86C2-4a15-89C4-DEB0E82D0E31}
DEFINE_GUID(CLSID_GFXTypeNoise, 
            0xcab5a5f0, 0x86c2, 0x4a15, 0x89, 0xc4, 0xde, 0xb0, 0xe8, 0x2d, 0xe, 0x31);

// {400231CB-7024-48e0-953B-0E4601426A61}
DEFINE_GUID(CLSID_GFXTypeMaterial, 
            0x400231cb, 0x7024, 0x48e0, 0x95, 0x3b, 0xe, 0x46, 0x1, 0x42, 0x6a, 0x61);

// {80051395-4EAE-455e-B558-801EFC85277F}
DEFINE_GUID(CLSID_GFXTypeLight, 
            0x80051395, 0x4eae, 0x455e, 0xb5, 0x58, 0x80, 0x1e, 0xfc, 0x85, 0x27, 0x7f);

// {E0066B3A-CC4D-4522-840A-5D53435D8B9A}
DEFINE_GUID(CLSID_GFXTypeMask, 
            0xe0066b3a, 0xcc4d, 0x4522, 0x84, 0xa, 0x5d, 0x53, 0x43, 0x5d, 0x8b, 0x9a);

// {AFEEA52D-F907-424d-9BA1-0997516A203A}
DEFINE_GUID(CLSID_GFXTypeOrganicWipe, 
            0xafeea52d, 0xf907, 0x424d, 0x9b, 0xa1, 0x9, 0x97, 0x51, 0x6a, 0x20, 0x3a);

// {D031F6F2-E8DB-43cb-87E3-DF51EEB06D26}
DEFINE_GUID(CLSID_GFXTypeExplosion, 
            0xd031f6f2, 0xe8db, 0x43cb, 0x87, 0xe3, 0xdf, 0x51, 0xee, 0xb0, 0x6d, 0x26);

// {AEBBA014-CEF0-4161-A629-D5A18D2D3CFC}
DEFINE_GUID(CLSID_GFXTypeTextureGradient, 
            0xaebba014, 0xcef0, 0x4161, 0xa6, 0x29, 0xd5, 0xa1, 0x8d, 0x2d, 0x3c, 0xfc);

// {994BA07B-75EF-4412-BC7E-71C8FD23B142}
DEFINE_GUID(CLSID_GFXTypeDataGradient, 
            0x994ba07b, 0x75ef, 0x4412, 0xbc, 0x7e, 0x71, 0xc8, 0xfd, 0x23, 0xb1, 0x42);


// {8F965A01-F1C9-4a93-B4BE-0DA22527A3B4}
DEFINE_GUID(CLSID_GFXTypeUVMap, 
            0x8f965a01, 0xf1c9, 0x4a93, 0xb4, 0xbe, 0xd, 0xa2, 0x25, 0x27, 0xa3, 0xb4);
            
// {B2033596-94D2-492e-9143-F116EA015687}
DEFINE_GUID(CLSID_GFXTypeDust, 
            0xb2033596, 0x94d2, 0x492e, 0x91, 0x43, 0xf1, 0x16, 0xea, 0x1, 0x56, 0x87);

// {D623E0CE-91FD-4359-9F7B-4B99CE203D0A}
DEFINE_GUID(CLSID_GFXTypeStreak, 
            0xd623e0ce, 0x91fd, 0x4359, 0x9f, 0x7b, 0x4b, 0x99, 0xce, 0x20, 0x3d, 0xa);

// {5287E39D-D15F-49b7-BEC6-38655FA41DD1}
DEFINE_GUID(CLSID_GFXTypeBrush, 
            0x5287e39d, 0xd15f, 0x49b7, 0xbe, 0xc6, 0x38, 0x65, 0x5f, 0xa4, 0x1d, 0xd1);

//////////////////////////////////////////////////////////////////////////////////
// IMvGenlockControl interface
//////////////////////////////////////////////////////////////////////////////////

// {6606511B-F483-42FC-A4BB-164BD5680FDE}
DEFINE_GUID(IID_IMvGenlockControl, 
            0x6606511b, 0xf483, 0x42fc, 0xa4, 0xbb, 0x16, 0x4b, 0xd5, 0x68, 0xf, 0xde);

//////////////////////////////////////////////////////////////////////////////////
// IMvIODeviceControl interface
//////////////////////////////////////////////////////////////////////////////////

// {13CADA40-9CD8-41A8-AFC7-C168B4064E3E}
DEFINE_GUID(IID_IMvIODeviceControl, 
            0x13cada40, 0x9cd8, 0x41a8, 0xaf, 0xc7, 0xc1, 0x68, 0xb4, 0x6, 0x4e, 0x3e);

//////////////////////////////////////////////////////////////////////////
// IMvVuMeter object - COM object
//////////////////////////////////////////////////////////////////////////
// {DC7DF872-008E-4C42-BFE7-6F60ACD8BC5B}
DEFINE_GUID(CLSID_IMvVuMeter, 
            0xdc7df872, 0x8e, 0x4c42, 0xbf, 0xe7, 0x6f, 0x60, 0xac, 0xd8, 0xbc, 0x5b);

//////////////////////////////////////////////////////////////////////////
// IMvVuMeter interface - for audio VuMeter access (public)
//////////////////////////////////////////////////////////////////////////
// {AED7551C-34A1-47CF-9E62-7E8A2B81027E}
DEFINE_GUID(IID_IMvVuMeter, 
            0xaed7551c, 0x34a1, 0x47cf, 0x9e, 0x62, 0x7e, 0x8a, 0x2b, 0x81, 0x2, 0x7e);

//////////////////////////////////////////////////////////////////////////////////
// IMvHardwareInformation interface
//////////////////////////////////////////////////////////////////////////////////

// {E21BD3A3-0B5F-491b-B5DD-2404DEA03C5E}
DEFINE_GUID(CLSID_MvHardwareInformation, 
            0xe21bd3a3, 0xb5f, 0x491b, 0xb5, 0xdd, 0x24, 0x4, 0xde, 0xa0, 0x3c, 0x5e);

// {E9496200-52DB-4D9C-860E-FF2D245072F4}
DEFINE_GUID(IID_IMvHardwareInformation, 
            0xe9496200, 0x52db, 0x4d9c, 0x86, 0xe, 0xff, 0x2d, 0x24, 0x50, 0x72, 0xf4);

//////////////////////////////////////////////////////////////////////////////////
// Flex Clip
//////////////////////////////////////////////////////////////////////////////////

// {8D0EAB68-D91A-4342-A786-B8198699C7BA}
DEFINE_GUID(IID_IMvFlexClipReader, 
            0x8d0eab68, 0xd91a, 0x4342, 0xa7, 0x86, 0xb8, 0x19, 0x86, 0x99, 0xc7, 0xba);

// {7BEC82E1-F216-44bb-B15D-AAAC1649F89B}
DEFINE_GUID(IID_IMvFlexClipWriter, 
            0x7bec82e1, 0xf216, 0x44bb, 0xb1, 0x5d, 0xaa, 0xac, 0x16, 0x49, 0xf8, 0x9b);
// {5E2F241B-61AB-4683-89DB-F54360EC1F45}
DEFINE_GUID(IID_IMvFlexClipWriter2, 
            0x5e2f241b, 0x61ab, 0x4683, 0x89, 0xdb, 0xf5, 0x43, 0x60, 0xec, 0x1f, 0x45);

// {D81789F4-5645-45a3-AFFF-D917D9E02523}
DEFINE_GUID(IID_IMvFlexClipFactory, 
            0xd81789f4, 0x5645, 0x45a3, 0xaf, 0xff, 0xd9, 0x17, 0xd9, 0xe0, 0x25, 0x23);

// {F75D3E6C-3861-4fa1-B8A3-E39EBE999932}
DEFINE_GUID(IID_IMvClipReaderOptions, 
            0xf75d3e6c, 0x3861, 0x4fa1, 0xb8, 0xa3, 0xe3, 0x9e, 0xbe, 0x99, 0x99, 0x32);

//////////////////////////////////////////////////////////////////////////////////
// Flex Clip Reader (Supported file formats)
//////////////////////////////////////////////////////////////////////////////////
// {FEB51D36-59E1-4881-AAB0-C4AA87F76503}
DEFINE_GUID(CLSID_MvdAVIClipReader, 
   0xfeb51d36, 0x59e1, 0x4881, 0xaa, 0xb0, 0xc4, 0xaa, 0x87, 0xf7, 0x65, 0x3);

// {737E5048-3449-4d13-8D95-26E052E1D490}
DEFINE_GUID(CLSID_MvdStreamsClipReader, 
   0x737e5048, 0x3449, 0x4d13, 0x8d, 0x95, 0x26, 0xe0, 0x52, 0xe1, 0xd4, 0x90);

// {C2C73FD9-5256-43E4-AA27-BD01DF551519}
DEFINE_GUID(CLSID_MvdStreamsLXFClipReader, 
0xc2c73fd9, 0x5256, 0x43e4, 0xaa, 0x27, 0xbd, 0x1, 0xdf, 0x55, 0x15, 0x19);

// {B1A4435C-7386-4D9C-B814-05CC84DC36FA}
DEFINE_GUID(CLSID_MvdStreamsTSClipReader, 
0xb1a4435c, 0x7386, 0x4d9c, 0xb8, 0x14, 0x5, 0xcc, 0x84, 0xdc, 0x36, 0xfa);

// {CF72B249-E848-4e07-9DB6-AAE0F04ABCB9} // embedded in ClipAVI
DEFINE_GUID(CLSID_MvdMXFClipReader2, 
   0xcf72b249, 0xe848, 0x4e07, 0x9d, 0xb6, 0xaa, 0xe0, 0xf0, 0x4a, 0xbc, 0xb9);

// {2A05340A-9AC9-42a1-BAAB-AB1C44F372AB}
DEFINE_GUID(CLSID_MvdWAVClipReader, 
   0x2a05340a, 0x9ac9, 0x42a1, 0xba, 0xab, 0xab, 0x1c, 0x44, 0xf3, 0x72, 0xab);

// {0B0F99E4-DF40-4ca8-99DD-C477E2BDEA9F}
DEFINE_GUID(CLSID_MvdGFXClipReader , 
   0xb0f99e4, 0xdf40, 0x4ca8, 0x99, 0xdd, 0xc4, 0x77, 0xe2, 0xbd, 0xea, 0x9f);

// {AF3F2D1D-F701-4053-ACF4-960BD105CBA2}
DEFINE_GUID(CLSID_MvdMGFClipReader            , 
   0xaf3f2d1d, 0xf701, 0x4053, 0xac, 0xf4, 0x96, 0xb, 0xd1, 0x5, 0xcb, 0xa2);

// {BCC4F897-F8C0-4342-A78E-554BCCA33F70}
DEFINE_GUID(CLSID_MvMGFFileInfo, 
   0xbcc4f897, 0xf8c0, 0x4342, 0xa7, 0x8e, 0x55, 0x4b, 0xcc, 0xa3, 0x3f, 0x70);

// {FE89744E-070A-4abf-B604-739E4471DE23}
DEFINE_GUID(CLSID_MvGFXFileInfo, 
   0xfe89744e, 0x70a, 0x4abf, 0xb6, 0x4, 0x73, 0x9e, 0x44, 0x71, 0xde, 0x23);

// {F000589D-4BE5-40f4-9EA8-9A82305B8E3D}
DEFINE_GUID(CLSID_MvFlexASFClip, 
         0xf000589d, 0x4be5, 0x40f4, 0x9e, 0xa8, 0x9a, 0x82, 0x30, 0x5b, 0x8e, 0x3d);

// {EA42B0D8-2A64-42de-81A1-E9957AE50ABB}
DEFINE_GUID(CLSID_MvFlexQTClip, 
            0xea42b0d8, 0x2a64, 0x42de, 0x81, 0xa1, 0xe9, 0x95, 0x7a, 0xe5, 0xa, 0xbb);

// {9C14B17B-AE28-4d84-A6C2-F1590894EFF2}
DEFINE_GUID(CLSID_MvdISOClipReader, 
            0x9c14b17b, 0xae28, 0x4d84, 0xa6, 0xc2, 0xf1, 0x59, 0x8, 0x94, 0xef, 0xf2);

// {5DCB14C2-D380-4881-B78F-9BFD63CE4A4E}
DEFINE_GUID(CLSID_MvFlexSampleClip, 
            0x5dcb14c2, 0xd380, 0x4881, 0xb7, 0x8f, 0x9b, 0xfd, 0x63, 0xce, 0x4a, 0x4e);

//////////////////////////////////////////////////////////////////////////////////
// Flex Clip Reader Options (Supported options)
//////////////////////////////////////////////////////////////////////////////////

// {4B128206-58BE-4d0c-A9DF-5BC645F8A008}
DEFINE_GUID(GUID_ClipReaderOption_CueSize, 
            0x4b128206, 0x58be, 0x4d0c, 0xa9, 0xdf, 0x5b, 0xc6, 0x45, 0xf8, 0xa0, 0x8);

// {2A1300E1-E5AE-4d8c-9AD3-2BCEE8823943}
DEFINE_GUID(GUID_ClipReaderOption_SetNTSCCaptionsFormat, 
            0x2a1300e1, 0xe5ae, 0x4d8c, 0x9a, 0xd3, 0x2b, 0xce, 0xe8, 0x82, 0x39, 0x43);


// {676394D6-C820-4e5a-AD11-F75E0F76EBB0}
DEFINE_GUID(GUID_ClipReaderOption_ProcessTimecode, 
            0x676394d6, 0xc820, 0x4e5a, 0xad, 0x11, 0xf7, 0x5e, 0xf, 0x76, 0xeb, 0xb0);

// {92EA05D5-D051-43EC-A49B-3191D29F09BC}
DEFINE_GUID(GUID_ClipReaderOption_AudioStreamIdentifier, 
            0x92ea05d5, 0xd051, 0x43ec, 0xa4, 0x9b, 0x31, 0x91, 0xd2, 0x9f, 0x9, 0xbc);

// {3475C20F-D67A-490B-A4EA-5CB81CA6A179}
DEFINE_GUID(GUID_ClipReaderOption_TimeCodeLocation, 
            0x3475c20f, 0xd67a, 0x490b, 0xa4, 0xea, 0x5c, 0xb8, 0x1c, 0xa6, 0xa1, 0x79);

// {28FFF39E-6CDC-4558-B511-6599D52B3899}
DEFINE_GUID(GUID_ClipReaderOption_VANCLocation, 
0x28fff39e, 0x6cdc, 0x4558, 0xb5, 0x11, 0x65, 0x99, 0xd5, 0x2b, 0x38, 0x99);


// {F26F9BE8-7FBB-4ED8-B19E-E288FD57378A}
DEFINE_GUID(GUID_ClipReaderOption_MovDurationFromtkhd,
   0xf26f9be8, 0x7fbb, 0x4ed8, 0xb1, 0x9e, 0xe2, 0x88, 0xfd, 0x57, 0x37, 0x8a);

//////////////////////////////////////////////////////////////////////////////////
// Flex Clip Writer Options (Supported options)
#define _USE_GUIDS_FOR_CLIP_OPTIONS_
//////////////////////////////////////////////////////////////////////////////////

// {E4D22F06-388D-4496-9CAB-40F10C0F3C16}
// Description: EMvClipOptionMxfFillLabel: Indicates which fill label to use when generating an MXF file.
DEFINE_GUID(GUID_MvWriterClipOptionMxfFillLabel, 
0xe4d22f06, 0x388d, 0x4496, 0x9c, 0xab, 0x40, 0xf1, 0xc, 0xf, 0x3c, 0x16);

// {8E244841-2171-4c5c-A9FE-0A3EE4C0E746}
// Description: SMvFlexWriterMxfP2CaptureExtraInfo: Description of information needed to generate P2 type files.
DEFINE_GUID(GUID_MvWriterClipOptionMxfAddExtraInfoForP2, 
0x8e244841, 0x2171, 0x4c5c, 0xa9, 0xfe, 0xa, 0x3e, 0xe4, 0xc0, 0xe7, 0x46);

// {DA2AF05B-7388-42b9-B7F6-0BC848EC454F}
// Description: FOURCC: FourCC put in the file to identify the brand.  Normally set to 'JUNK'.
DEFINE_GUID(GUID_MvWriterClipOptionISOBrandCode, 
0xda2af05b, 0x7388, 0x42b9, 0xb7, 0xf6, 0xb, 0xc8, 0x48, 0xec, 0x45, 0x4f);

// {E161DA23-17E5-42e7-8B1E-521EFD87B897}
//Description:This GUID is for MOV/MP4/MXF streaming/late delivery support, the user will have to call SetClipOption with this GUID
// and preset file duration in frames before capture.This is only supported for AVC/AAC files.
DEFINE_GUID(GUID_MvWriterClipOptionPresetFileDurationInFramesForStreamingFile, 
            0xe161da23, 0x17e5, 0x42e7, 0x8b, 0x1e, 0x52, 0x1e, 0xfd, 0x87, 0xb8, 0x97);

// {28378EFE-C7DE-4EFB-AB98-EE3C9AF41C0C}
//Description: This GUID is for MOV files, it allows user to choose whether or not including clap atom in MOV files. 
DEFINE_GUID(GUID_MvWriterClipOptionIncludeClapAtomOption, 
0x28378efe, 0xc7de, 0x4efb, 0xab, 0x98, 0xee, 0x3c, 0x9a, 0xf4, 0x1c, 0xc);

// {6227EE80-21FA-4EA1-8735-9497A3748989}
//Description: This GUID is for MOV files, it allows user to choose whether or not including CC track in MOV files. 
DEFINE_GUID(GUID_MvWriterClipOptionMOVVancTrackOption, 
0x6227ee80, 0x21fa, 0x4ea1, 0x87, 0x35, 0x94, 0x97, 0xa3, 0x74, 0x89, 0x89);

// {D4B25059-8B49-47DE-BA41-7F6E8BBF4856}
DEFINE_GUID(GUID_MvWriterClipOptionReserveSpaceForEndOfDiskCheck, 
   0xd4b25059, 0x8b49, 0x47de, 0xba, 0x41, 0x7f, 0x6e, 0x8b, 0xbf, 0x48, 0x56);

// ASF writer
// {FFE122A7-CE7B-4e91-9AB1-A20E93B9F8B3}
// Description: SMvfFlexASFClipWriterOptionsVideoCodecConfig: Configures which video codec will be used.
DEFINE_GUID(GUID_MvFlexASFClipWriterOptionsVideoCodecConfig,
0xffe122a7, 0xce7b, 0x4e91, 0x9a, 0xb1, 0xa2, 0xe, 0x93, 0xb9, 0xf8, 0xb3);

// {DD930A6F-67F7-459d-93E9-50319618220C}
// Description: SMvfFlexASFClipWriterOptionsVideoCodecConfig: Add another video stream which has different video codec option.
DEFINE_GUID(GUID_MvFlexASFClipWriterAddOptionsVideoCodecConfig, 
            0xdd930a6f, 0x67f7, 0x459d, 0x93, 0xe9, 0x50, 0x31, 0x96, 0x18, 0x22, 0xc);

// {09CAB921-617F-4a7c-8B46-06E196772494}
// Description: SMvfFlexASFClipWriterOptionsAudioCodecConfig: Add another audio stream which has different audio codec option.
DEFINE_GUID(GUID_MvFlexASFClipWriterAddOptionsAudioCodecConfig, 
            0x9cab921, 0x617f, 0x4a7c, 0x8b, 0x46, 0x6, 0xe1, 0x96, 0x77, 0x24, 0x94);


// {DCDA3BB9-B491-44d7-B261-781B872177B6}
// Description: SMvfFlexASFClipWriterOptionsAudioCodecConfig: Configures which audio codec will be used.
DEFINE_GUID(GUID_MvFlexASFClipWriterOptionsAudioCodecConfig,
0xdcda3bb9, 0xb491, 0x44d7, 0xb2, 0x61, 0x78, 0x1b, 0x87, 0x21, 0x77, 0xb6);

// {F2A6B743-2264-45de-93C7-BCF36D928DF2}
DEFINE_GUID(GUID_MvFlexASFClipWriterOptionsVideoAudioFrameIndexing, 
            0xf2a6b743, 0x2264, 0x45de, 0x93, 0xc7, 0xbc, 0xf3, 0x6d, 0x92, 0x8d, 0xf2);

// {E79FA90F-F62B-4435-9615-A700D17E0D7D}
DEFINE_GUID(GUID_MvFlexASFClipWriterOptionsSkipFrameOnLowMemory, 
   0xe79fa90f, 0xf62b, 0x4435, 0x96, 0x15, 0xa7, 0x0, 0xd1, 0x7e, 0xd, 0x7d);

// {8C7A3E73-233A-4b00-936A-5FC3A087F06C}
// Description: bool: Tells the codec that the source is live and it must encode as fast as possible (it may drop frames).
DEFINE_GUID(GUID_MvFlexASFClipWriterOptionsIsSourceLive,
0x8c7a3e73, 0x233a, 0x4b00, 0x93, 0x6a, 0x5f, 0xc3, 0xa0, 0x87, 0xf0, 0x6c);


// QuickTime Clip
// {8ADC488A-D7FA-4c69-A3E5-D33C8A40FACC}
// Description: EMvFrameRate: Frame rate at which the resulting QuickTime movie file should be played.
DEFINE_GUID(GUID_MvFlexQTClipWriterOptionsFrameRate, 
0x8adc488a, 0xd7fa, 0x4c69, 0xa3, 0xe5, 0xd3, 0x3c, 0x8a, 0x40, 0xfa, 0xcc);

// {FF743AE2-72B1-4de0-BEA6-5B6042A6D63A}
// Description: bool: Enable/Disable frame reordering when compression video data. If set to true, the decode order 
// of the frames will be different from the display order. This operation may produce a better compression.  
// Note that not all compression formats support this option.
DEFINE_GUID(GUID_MvFlexQTClipWriterOptionsAllowFrameReordering, 
0xff743ae2, 0x72b1, 0x4de0, 0xbe, 0xa6, 0x5b, 0x60, 0x42, 0xa6, 0xd6, 0x3a);

// {D766868E-3EC7-4c2b-8C9D-C2BE7E4F4F62}
// Description: bool: Enable/Disable temporal compression when compressing video data. If set to true, frames will 
// be compressed based on the previous frames. Note that not all compression formats support this option.
DEFINE_GUID(GUID_MvFlexQTClipWriterOptionsAllowTemporalCompression, 
            0xd766868e, 0x3ec7, 0x4c2b, 0x8c, 0x9d, 0xc2, 0xbe, 0x7e, 0x4f, 0x4f, 0x62);

// {420537C8-809A-4fc1-9821-AD0901619362}
// Description: bool: Enable/Disable frame time changes by the compressor. If set to true, the compressor will 
// combine similar adjacent frames into one frame with a duration equal to the sum of the duration of the two frames.
DEFINE_GUID(GUID_MvFlexQTClipWriterOptionsAllowFrameTimeChange, 
0x420537c8, 0x809a, 0x4fc1, 0x98, 0x21, 0xad, 0x9, 0x1, 0x61, 0x93, 0x62);

// {69681083-627E-4388-947E-E1771A1103C3}
// Description: int32_t: Average data rate of the resulting QuickTime movie file. The value is expressed in bytes 
// per second.  Setting a data rate of zero indicates that the quality setting will determine the size of 
// compressed data.
DEFINE_GUID(GUID_MvFlexQTClipWriterOptionsAverageDataRate, 
0x69681083, 0x627e, 0x4388, 0x94, 0x7e, 0xe1, 0x77, 0x1a, 0x11, 0x3, 0xc3);

// {1EBDD80A-1932-49f6-BA30-AE0E7314733C}
// Description: int32_t: Maximum number of frames that can be kept into memory before emiting one frame. 
// Set to -1 if you do not want any limit.
DEFINE_GUID(GUID_MvFlexQTClipWriterOptionsMaxFrameDelayCount, 
0x1ebdd80a, 0x1932, 0x49f6, 0xba, 0x30, 0xae, 0xe, 0x73, 0x14, 0x73, 0x3c);

// {2FCEA8B4-0215-4a41-88EC-84B411EB28AC}
// Description: int32_t: Maximum interval between each key frame. If set to 0, all frames will be key frames.
DEFINE_GUID(GUID_MvFlexQTClipWriterOptionsMaxKeyFrameInterval, 
0x2fcea8b4, 0x215, 0x4a41, 0x88, 0xec, 0x84, 0xb4, 0x11, 0xeb, 0x28, 0xac);

// {B74A808A-CFEC-497b-8CDE-B3EBF965FDAB}
// Description: int32_t: Maximum interval between each partial key frame.
DEFINE_GUID(GUID_MvFlexQTClipWriterOptionsMaxPartialSyncFrameInterval, 
0xb74a808a, 0xcfec, 0x497b, 0x8c, 0xde, 0xb3, 0xeb, 0xf9, 0x65, 0xfd, 0xab);

// {0D6AF8F5-BCCB-4a14-B59A-EAF0D213EC4E}
// Description: uint32_t: CPU time budget in microseconds for each frame sent to the codec. This option may be 
// ignored by the codec. If set to 0, the codec will try to compress the data as fast as possible. If set to  
// 0xFFFFFFFF, no limit will be set.
DEFINE_GUID(GUID_MvFlexQTClipWriterOptionsCPUTimeBudget, 
0xd6af8f5, 0xbccb, 0x4a14, 0xb5, 0x9a, 0xea, 0xf0, 0xd2, 0x13, 0xec, 0x4e);

// {3A02DB00-56F2-4a35-8826-8496A4E0DCD8}
// Description: unsigned long: Interval between each update of the movie's information in the file. The value is 
// expressed in seconds of data written in the file. If set to 0, the movie will only be updated when the clip 
// will be closed.
DEFINE_GUID(GUID_MvFlexQTClipWriterOptionsFileUpdateInterval, 
0x3a02db00, 0x56f2, 0x4a35, 0x88, 0x26, 0x84, 0x96, 0xa4, 0xe0, 0xdc, 0xd8);

// {FA94F037-D120-4ca8-A6BF-349CEA6AC0E5}
// Description: unsigned long: Quality of the video data compression. The value is expressed as an integer going between 
// 0 and 1024 (inclusive) where 0 is the minimum quality and 1024 is a lossless compression.
DEFINE_GUID(GUID_MvFlexQTClipWriterOptionsQuality, 
0xfa94f037, 0xd120, 0x4ca8, 0xa6, 0xbf, 0x34, 0x9c, 0xea, 0x6a, 0xc0, 0xe5);

// {9480342B-BD30-48ef-BFF1-0B0CE12CC436}
// Description: long: Four char code representing the desired codec type. Refer to EMvFlexQTClipWriterCodecTypes  
// for the most common values.
DEFINE_GUID(GUID_MvFlexQTClipWriterOptionsCodecType, 
0x9480342b, 0xbd30, 0x48ef, 0xbf, 0xf1, 0xb, 0xc, 0xe1, 0x2c, 0xc4, 0x36);

// {46482BD0-2334-4d2e-B4F5-70BF37FFA6C1}
// Description: bool: Enable/Disable the creation of a «Flattened?QuickTime movie file when the clip is closed.  
// Flattening to a new QuickTime movie file can improve the playback performances of the QuickTime movie file.  
// It is also strongly recommended to flatten the QuickTime movie to a new file after truncating and adding new  
// data to an existing movie.
DEFINE_GUID(GUID_MvFlexQTClipWriterOptionsGenerateFlattenedFile, 
0x46482bd0, 0x2334, 0x4d2e, 0xb4, 0xf5, 0x70, 0xbf, 0x37, 0xff, 0xa6, 0xc1);

// {09D60398-AB54-48db-A068-C82237D6500C}
// Description: NULL terminated string of wchar_t: File name of the QuickTime movie file generated during the 
// flattening operation.  This option is ignored if flattening is disabled.
DEFINE_GUID(GUID_MvFlexQTClipWriterOptionsFlattenedFileName, 
0x9d60398, 0xab54, 0x48db, 0xa0, 0x68, 0xc8, 0x22, 0x37, 0xd6, 0x50, 0xc);

// {40E5BBFC-30EC-4643-8EC5-0BF7325E74E2}
// Description: bool: Enable/Disable the deletion of the source file during flattening operation. If set to true,  
// the file created/opened during the call to IMvFlexClipWriter::Open() will be deleted once the flattened QuickTime 
// movie file will be generated.
DEFINE_GUID(GUID_MvFlexQTClipWriterOptionsFlatteningDeleteSrcFile, 
0x40e5bbfc, 0x30ec, 0x4643, 0x8e, 0xc5, 0xb, 0xf7, 0x32, 0x5e, 0x74, 0xe2);

// {1EEB9FB1-B100-45b3-BDA0-4276B86595FC}
// Description: SMvFlexQTClipWriterCodecTypeInfo[]: -- READONLY -- Returns an array of SMvFlexQTClipWriterCodecTypeInfo  
// containing the supported codec types.  Before trying to retrieve this option's value, you should get the number  
// of items in the list (using the option GUID_MvFlexQTClipWriterOptionsCodecTypesListCount) and allocate enough space. 
// The size passed to the option should be "sizeof(SMvFlexQTClipWriterCodecTypeInfo) * ItemCount".
DEFINE_GUID(GUID_MvFlexQTClipWriterOptionsCodecTypesList, 
0x1eeb9fb1, 0xb100, 0x45b3, 0xbd, 0xa0, 0x42, 0x76, 0xb8, 0x65, 0x95, 0xfc);

// {46EAC151-4126-4643-83E6-918068BF287E}
// Description: long: -- READONLY -- Returns the number of codec types returned by the option
// GUID_MvFlexQTClipWriterOptionsCodecTypesList.
DEFINE_GUID(GUID_MvFlexQTClipWriterOptionsCodecTypesListCount, 
0x46eac151, 0x4126, 0x4643, 0x83, 0xe6, 0x91, 0x80, 0x68, 0xbf, 0x28, 0x7e);

// {B204D96E-E988-422e-A3DC-CF0BC11A4EC8}
// Description: int32_t: Total size of compressed data in bytes per second that the codec output must not exceed.
DEFINE_GUID(GUID_MvFlexQTClipWriterOptionsLimitDataRate, 
0xb204d96e, 0xe988, 0x422e, 0xa3, 0xdc, 0xcf, 0xb, 0xc1, 0x1a, 0x4e, 0xc8);

// {FC5D9CCA-75E5-4b2f-A82A-C33860000C15}
// Description: SMvWaveFormat: Defines the audio format of the file.
DEFINE_GUID(GUID_MvFlexQTClipWriterOptionsSetWaveFormat, 
0xfc5d9cca, 0x75e5, 0x4b2f, 0xa8, 0x2a, 0xc3, 0x38, 0x60, 0x0, 0xc, 0x15);

// {179A3E23-BB50-494E-AD9D-D1B42D3BA0FE}
DEFINE_GUID(GUID_MvFlexQTClipWriterOptionsSetAACInfo, 
0x179a3e23, 0xbb50, 0x494e, 0xad, 0x9d, 0xd1, 0xb4, 0x2d, 0x3b, 0xa0, 0xfe);

// {ABF9604C-5814-483D-8A71-C21F00738D4C}
// Description: Before setting this option, GUID_MvFlexQTClipWriterOptionsCodecType has to be already set up, else it will return error MV_E_INVALID_CODEC_GUID. This option is now only for keMvFlexQTClipWriterCodecType_DNx_Alpha
DEFINE_GUID(GUID_MvFlexQTClipWriterOptionsCodecSettings, 
   0xabf9604c, 0x5814, 0x483d, 0x8a, 0x71, 0xc2, 0x1f, 0x0, 0x73, 0x8d, 0x4c);

// {7488A6D1-3483-435D-8B54-979E27F6DB9E}
// Description: GUID_MvFlexQTClipWriterOptionsMaxSurfaceQueueSize defines the maximum number of buffers sending to the compressor. When it reaches this number, the buffer will be sent when there is a compressed buffer get out of the compressor.
// Default number is 24. If this number is set to -1, the size will be unlimited.
DEFINE_GUID(GUID_MvFlexQTClipWriterOptionsMaxSurfaceQueueSize, 
   0x7488a6d1, 0x3483, 0x435d, 0x8b, 0x54, 0x97, 0x9e, 0x27, 0xf6, 0xdb, 0x9e);

//////////////////////////////////////////////////////////////////////////////////
// Flex Writer options
////////////////////////////////////////////////////////////////////////////////////
// {5286F7D6-1DA5-4F91-923F-EA48BA8F8026}
DEFINE_GUID(GUID_MvWriterOptionVANCLocation, 
0x5286f7d6, 0x1da5, 0x4f91, 0x92, 0x3f, 0xea, 0x48, 0xba, 0x8f, 0x80, 0x26);

// {E0031FF8-779B-4403-BD68-B056D8E4568A}
//Description: GUID_MvFlexWriterBufferSupplyOption:For PreRes4444 capture, the buffer option(surface format and component bit) FlexWriter will supply
DEFINE_GUID(GUID_MvFlexWriterBufferSupplyOption, 
   0xe0031ff8, 0x779b, 0x4403, 0xbd, 0x68, 0xb0, 0x56, 0xd8, 0xe4, 0x56, 0x8a);


//////////////////////////////////////////////////////////////////////////////////
//Flex Writer PCM Mov Audio Stream Save Type
//////////////////////////////////////////////////////////////////////////////////
// {62D29E20-C3CE-4dd9-81F9-95B2D3AAEE1A}
//Description: GUID_MvFlexWriterPCMMovAudioStreamSaveType:for PCM Mov audio Either Stereo or Mono in per stream
DEFINE_GUID(GUID_MvFlexWriterPCMMovAudioStreamSaveType, 
            0x62d29e20, 0xc3ce, 0x4dd9, 0x81, 0xf9, 0x95, 0xb2, 0xd3, 0xaa, 0xee, 0x1a);


//////////////////////////////////////////////////////////////////////////////////
//Flex Writer reseting initial timecode value
//////////////////////////////////////////////////////////////////////////////////
// {B1CBA5AA-3F86-411D-8E62-93D6D39C110C}
DEFINE_GUID(GUID_MvFlexWriterOptionResetInitialTimecode, 
0xb1cba5aa, 0x3f86, 0x411d, 0x8e, 0x62, 0x93, 0xd6, 0xd3, 0x9c, 0x11, 0xc);





//////////////////////////////////////////////////////////////////////////////////
// Flex Media Reader/Writer properties
//////////////////////////////////////////////////////////////////////////////////

DEFINE_GUID(CLSID_MvFileIOAccessSizeInBytesProperty, 
            0x198a528f, 0xbc01, 0x4041, 0xac, 0x1a, 0x4, 0xc3, 0xa8, 0xd0, 0xd0, 0xb6);

// {D5257643-8429-4c68-A95B-2050155475B1}
DEFINE_GUID(CLSID_MvSampleDescriptionExtensionProperty, 
            0xd5257643, 0x8429, 0x4c68, 0xa9, 0x5b, 0x20, 0x50, 0x15, 0x54, 0x75, 0xb1);

// {E2CB054A-A1F7-4a96-BFAB-BF59BC7D7891}
DEFINE_GUID(CLSID_StreamBitMapInfoHeader, 
0xe2cb054a, 0xa1f7, 0x4a96, 0xbf, 0xab, 0xbf, 0x59, 0xbc, 0x7d, 0x78, 0x91);

// {E723E2DF-B372-45d0-AB23-46C507DE16A4}
DEFINE_GUID(CLSID_MvMaxVideoRegionsProperty, 
            0xe723e2df, 0xb372, 0x45d0, 0xab, 0x23, 0x46, 0xc5, 0x7, 0xde, 0x16, 0xa4); // needs a uint32_t argument

// {6A33EDBE-0910-4579-8125-349521125AE1}
DEFINE_GUID(CLSID_MvMaxAudioRegionsProperty, 
            0x6a33edbe, 0x910, 0x4579, 0x81, 0x25, 0x34, 0x95, 0x21, 0x12, 0x5a, 0xe1); // needs a uint32_t argument

/////////////////////////////////////////////////////////////////////////////////
// IMvOutputControl
/////////////////////////////////////////////////////////////////////////////////
// {8DAC30E6-5D06-4f9a-B606-32E5D8F1EB99}
DEFINE_GUID(IID_IMvOutputControl, 
            0x8dac30e6, 0x5d06, 0x4f9a, 0xb6, 0x6, 0x32, 0xe5, 0xd8, 0xf1, 0xeb, 0x99);

//////////////////////////////////////////////////////////////////////////
// Flex Mpeg clip reader - IMvFlexMpegClipReader
//////////////////////////////////////////////////////////////////////////

// {D52D6608-3D52-49b3-A9D8-8EE894CBAEA2}
DEFINE_GUID(CLSID_MvFlexMpegClipReader, 
            0xd52d6608, 0x3d52, 0x49b3, 0xa9, 0xd8, 0x8e, 0xe8, 0x94, 0xcb, 0xae, 0xa2);

//////////////////////////////////////////////////////////////////////////
// Flex Mpeg clip reader factory - IMvFlexMpegClipReaderFactory
//////////////////////////////////////////////////////////////////////////

// {BEA0953F-28B9-4b05-AA93-D5984AD5D343}
DEFINE_GUID(IID_IMvFlexMpegClipReaderFactory, 
            0xbea0953f, 0x28b9, 0x4b05, 0xaa, 0x93, 0xd5, 0x98, 0x4a, 0xd5, 0xd3, 0x43);

//////////////////////////////////////////////////////////////////////////
// Flex Mpeg clip reader - IMvFlexMpegClipReader
//////////////////////////////////////////////////////////////////////////

// {93BB73B6-6F7D-451f-8F80-8BF77EE8B479}
DEFINE_GUID(IID_IMvFlexMpegClipReader, 
            0x93bb73b6, 0x6f7d, 0x451f, 0x8f, 0x80, 0x8b, 0xf7, 0x7e, 0xe8, 0xb4, 0x79);

// {471D165F-FB2E-483F-84DC-5D15F9E948F8}
DEFINE_GUID(GUID_MvFlexWriterAudioWaveFormatInfo, 
   0x471d165f, 0xfb2e, 0x483f, 0x84, 0xdc, 0x5d, 0x15, 0xf9, 0xe9, 0x48, 0xf8);

//////////////////////////////////////////////////////////////////////////////////
// Flex VANC Packet Observer
//////////////////////////////////////////////////////////////////////////////////
// {4FE5F6D0-2914-4128-92BC-C145A0A7EE59}
DEFINE_GUID(IID_IMvsVancPacketObserver, 
   0x4fe5f6d0, 0x2914, 0x4128, 0x92, 0xbc, 0xc1, 0x45, 0xa0, 0xa7, 0xee, 0x59);

//////////////////////////////////////////////////////////////////////////////////
// Flex Writer V210 option
//////////////////////////////////////////////////////////////////////////////////
// {536BA5D0-52B4-45B6-8E5A-0AC5C5BDFB31}

// {536BA5D0-52B4-45B6-8E5A-0AC5C5BDFB31}
DEFINE_GUID(GUID_MvFlexWriterV210SupportOption, 
            0x536ba5d0, 0x52b4, 0x45b6, 0x8e, 0x5a, 0xa, 0xc5, 0xc5, 0xbd, 0xfb, 0x31);
//////////////////////////////////////////////////////////////////////////////////
// Flex Reader V210 support option
//////////////////////////////////////////////////////////////////////////////////
// {43E98F89-7794-4B93-9B1E-3E887B62164F}

// {43E98F89-7794-4B93-9B1E-3E887B62164F}
DEFINE_GUID(GUID_MvFlexReaderV210SupportOption, 
            0x43e98f89, 0x7794, 0x4b93, 0x9b, 0x1e, 0x3e, 0x88, 0x7b, 0x62, 0x16, 0x4f);

// {09CD21C0-50A3-4F2C-A1A9-D23AB4E316F4}
//Description:This GUID is for MXF consolidation to set video origin value and number of frames to consolidate, the user will 
// have to call SetClipOption with this GUID before capture.
DEFINE_GUID(GUID_MvWriterClipOptionFileVideoDurationInfo, 
            0x9cd21c0, 0x50a3, 0x4f2c, 0xa1, 0xa9, 0xd2, 0x3a, 0xb4, 0xe3, 0x16, 0xf4);

//Description: This GUID is for MOV/MP4/264(MOV) files, it allows user to specify the container type instead of relying on the extension. 
// {7CEDC84D-5D44-404B-B123-9CF4375F1410}
DEFINE_GUID(GUID_MvWriterClipOptionContainerTypeOption,
   0x7cedc84d, 0x5d44, 0x404b, 0xb1, 0x23, 0x9c, 0xf4, 0x37, 0x5f, 0x14, 0x10);


#endif // __MvFlexGuidsPublicSDK_h_h

