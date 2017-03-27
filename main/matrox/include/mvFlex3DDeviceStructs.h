// $Archive: /VP/FLEXVIDEO/LIBS/MVFFLEX3DDEVICEAPI/Inc/mvFlex3DDeviceStructs.h $

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
//                         mvfFlex3DDevice_structs.h
//----------------------------------------------------------------
//   Birth Date:       December 2002
//   Operating System: WindowsXP
//   Author:           Luc Poirier
//----------------------------------------------------------------
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada 
//----------------------------------------------------------------

#ifndef _MVFLEX3DDEVICE_STRUCTS_INCLUDED_2002_12_12_MONTREAL_
#define _MVFLEX3DDEVICE_STRUCTS_INCLUDED_2002_12_12_MONTREAL_

#ifdef LINUX_PLATFORM
   #include "mvLinuxDefinitions.h"
#endif

#include "mvDefinitions.h"


//
// Forward declaration 
//
enum EMvHardwareProfile;

interface IMvSurface;


///
/// \defgroup define_def #define
///
/// @{
///


//
// FVF
//
// Flexible vertex format bits
//
#define keMvFVF_XYZ              0x002
#define keMvFVF_XYZRHW           0x004
#define keMvFVF_XYZB1            0x006
#define keMvFVF_XYZB2            0x008
#define keMvFVF_XYZB3            0x00a
#define keMvFVF_XYZB4            0x00c
#define keMvFVF_XYZB5            0x00e

#define keMvFVFNormal            0x010
#define keMvFVFReserved1         0x020
#define keMvFVFDiffuse           0x040
#define keMvFVFSpecular          0x080

#define keMvFVFTexcountMask      0xf00
#define keMvFVFTexcountShift     8
#define keMvFVFTex0              0x000
#define keMvFVFTex1              0x100
#define keMvFVFTex2              0x200
#define keMvFVFTex3              0x300
#define keMvFVFTex4              0x400
#define keMvFVFTex5              0x500
#define keMvFVFTex6              0x600
#define keMvFVFTex7              0x700
#define keMvFVFTex8              0x800

#define keMvFVFTextureFormat2 0         // Two floating point values
#define keMvFVFTextureFormat1 3         // One floating point value
#define keMvFVFTextureFormat3 1         // Three floating point values
#define keMvFVFTextureFormat4 2         // Four floating point values
#define keMvFVFTexCoordSize3(CoordIndex) (keMvFVFTextureFormat3 << (CoordIndex*2 + 16))
#define keMvFVFTexCoordSize2(CoordIndex) (keMvFVFTextureFormat2)
#define keMvFVFTexCoordSize4(CoordIndex) (keMvFVFTextureFormat4 << (CoordIndex*2 + 16))
#define keMvFVFTexCoordSize1(CoordIndex) (keMvFVFTextureFormat1 << (CoordIndex*2 + 16))

//
// EMvTextureArgument
//

// selectors
#define keMvTADiffuse                 0x00000000
#define keMvTACurrent                 0x00000001
#define keMvTATexture                 0x00000002
#define keMvTATFactor                 0x00000003
#define keMvTASpecular                0x00000004
#define keMvTATemp                    0x00000005
// modifiers
#define keMvTAComplement              0x00000010
#define keMvTAAlphaReplicate          0x00000020

//
// Clear flags
//
#define keMvClearTarget            0x00000001l  // Clears target surface
#define keMvClearZBuffer           0x00000002l  // Clears z buffer
#define keMvClearStencil           0x00000004l  // Clears stencil planes 

// 
// Color selector 
// 
#define keMvColorWriteEnableRed     (1L<<0)
#define keMvColorWriteEnableGreen   (1L<<1)
#define keMvColorWriteEnableBlue    (1L<<2)
#define keMvColorWriteEnableAlpha   (1L<<3)

//
// Bias to apply to the texture coordinate set to apply a wrap to.
//
#define keMvRSWrapBias              128UL

//
// Flags to construct the WRAP render states 
//
#define keMvWrapU   0x00000001L
#define keMvWrapV   0x00000002L
#define keMvWrapW   0x00000004L

// 
// Flags to construct the WRAP render states for 1D thru 4D texture coordinates 
//
#define keMvWrapCoord0   0x00000001L    // same as D3DWRAP_U
#define keMvWrapCoord1   0x00000002L    // same as D3DWRAP_V
#define keMvWrapCoord2   0x00000004L    // same as D3DWRAP_W
#define keMvWrapCoord3   0x00000008L

//
// These bits could be ORed together to use with D3DRS_CLIPPLANEENABLE
//
#define keMvClipPlane0 (1 << 0)
#define keMvClipPlane1 (1 << 1)
#define keMvClipPlane2 (1 << 2)
#define keMvClipPlane3 (1 << 3)
#define keMvClipPlane4 (1 << 4)
#define keMvClipPlane5 (1 << 5)



/// @}

//
// \defgroup enum_def Enumerations definition 
//
// @{
//

//
// Summary:
//	   Number of bytes used by the indices.
//
enum EMvIndexSize
{
   keMvIndex16 = 101, // 16-bits indices
   keMvIndex32 = 102  // 32-bits indices
};

//
// Summary:
//	   Special flags for the lock.
// 
enum EMvLock
{
   keMvLockDiscard     = 0x00002000L,  // The application discards the entire vertex or index buffer.
                                          // A pointer to a new memory area is returned so that the 
                                          // dynamic memory access (DMA) and rendering from the 
                                          // previous area do not stall.
   keMvLockNoOverwrite = 0x00001000L,  // The application promises not to overwrite any data in the 
                                          // vertex and index buffers. Specifying this flag allows 
                                          // the driver to return immediately and continue rendering, 
                                          // using this buffer. If this flag is not used, the driver 
                                          // must finish rendering before returning from locking.
   keMvLockReadOnly    = 0x00000010L   // The application will not write to the buffer. This enables 
                                          // resources stored in non-native formats to save the 
                                          // recompression step when unlocking.
};

//
// Summary:
//    Special flags for the vertex/index buffer.
//
enum EMvUsage
{
   keMvUsageDynamic    = 0x00000200L,  // Sets to indicate that the vertex buffer requires dynamic
                                          // memory use, enabling the drivers to decide where to place this buffer. 
                                          // In general, static vertex buffers are placed in video 
                                          // memory and dynamic vertex buffers are placed in 
                                          // accelerated graphics port (AGP) memory. (NOT SUPPORTED).
   keMvUsagePoints     = 0x00000040L,  // Sets to indicate when to use the vertex buffer for drawing points
   keMvUsageWriteOnly  = 0x00000008L   // Indicates that the application can only write to the 
                                          // vertex buffer. This flag enables the driver to choose
                                          // the best memory location for efficient rendering and write
                                          // operations. Attempts to read from a vertex buffer that is 
                                          // created with this capability will fail. Buffers created 
                                          // with keMvMemoryLocationHost that do not specify 
                                          // keMvUsageWriteOnly might suffer a severe performance penalty.
};

//
// Summary:
//    State block types.
//
enum EMvStateBlockType
{
   keMvStateBlockTypeAll = 1,          // Capture all of the current device state.
   keMvStateBlockTypeForceDWORD = 0xffffffff
};

//
// Summary:
//    Primitive types.
//
enum EMvPrimitiveType
{
   keMvPTPointList = 1,       // Renders the vertices as a collection of isolated points. This value 
                                 // is unsupported for indexed primitives.
   keMvPTLineList = 2,        // Renders the vertices as a list of isolated straight line segments. 
                                 // Calls using this primitive type fail if the count is odd, or less 
                                 // than two
   keMvPTLineStrip = 3,       // Renders the vertices as a single polyline. Calls using this primitive 
                                 // type fail if the count is less than two.
   keMvPTTriangleList = 4,    // Renders the specified vertices as a sequence of isolated triangles. 
                                 // Each group of three vertices defines a separate triangle.
   keMvPTTriangleStrip = 5,   // Renders the vertices as a triangle strip. The backface-culling flag 
                                 // is automatically flipped on even-numbered triangles.
   keMvPTTriangleFan = 6,     // Renders the vertices as a triangle fan.
   keMvPTFORCEDWORD = 0x7fffffff
};

//
// Summary:
//    Defines device render states.
//
enum EMvRenderStateType
{
   keMvRSZEnable = 7,            // Enable/disable the z-buffer
   keMvRSFillMode = 8,
   keMvRSShadeMode = 9,
   //keMvRSPlaneWriteMask = 13, // not supported
 
   keMvRSZWriteEnable = 14, //
   keMvRSAlphaTestEnable = 15,
   keMvRSLastPixel = 16,
   keMvRSSrcBlend = 19,
   keMvRSDestBlend = 20,
   keMvRSCullMode = 22,
   keMvRSZFunc = 23,
   keMvRSAlphaRef = 24,
   keMvRSAlphaFunc = 25,
   keMvRSDitherEnable = 26,
   keMvRSAlphaBlendEnable = 27,
   keMvRSFogEnable = 28,
   keMvRSSpecularEnable = 29,
   keMvRSFogColor = 34,
   keMvRSFogTableMode = 35,
   keMvRSFogStart = 36,
   keMvRSFogEnd = 37,
   keMvRSFogDensity = 38,
   keMvRSRangeFogEnable = 48,
   keMvRSStencilEnable = 52,
   keMvRSStencilFail = 53,
   keMvRSStencilZFail = 54,
   keMvRSStencilPass = 55,
   keMvRSStencilFunc = 56,
   keMvRSStencilRef = 57,
   keMvRSStencilMask = 58,
   keMvRSStencilWriteMask = 59,
   keMvRSTextureFactor = 60,
   keMvRSWrap0 = 128,
   keMvRSWrap1 = 129,
   keMvRSWrap2 = 130,
   keMvRSWrap3 = 131,
   keMvRSWrap4 = 132,
   keMvRSWrap5 = 133,
   keMvRSWrap6 = 134,
   keMvRSWrap7 = 135,
   keMvRSClipping = 136,
   keMvRSLighting = 137,
   keMvRSAmbient = 139,
   keMvRSFogVertexMode = 140,
   keMvRSColorVertex = 141,
   keMvRSLocalViewer = 142,
   keMvRSNormalizeNormals = 143,
   keMvRSDiffuseMaterialSource = 145,
   keMvRSSpecularMaterailSource = 146,
   keMvRSAmbientMaterialSource = 147,
   keMvRSEmissiveMaterialSource = 148,
   keMvRSVertexBlend = 151,
   keMvRSClipPlaneEnable = 152,
   keMvRSPointSize = 154,
   keMvRSPointSizeMin  = 155,
   keMvRSPointSpriteEnable = 156,
   keMvRSPointScaleEnable = 157,
   keMvRSPointScaleA  = 158,
   keMvRSPointScaleB  = 159,
   keMvRSPointScaleC  = 160,
   keMvRSAAFragmentCollectEnable = 161,   // Enable/disable fragment collection
   keMvRSMultisampleMask = 162,
   keMvRSPatchedGEStyle = 163,
   keMvRSDebugMonitorToken = 165,
   keMvRSPointSizeMax  = 166,
   keMvRSIndexedVertexBlendEnable = 167,
   keMvRSColorWriteEnable = 168,
   keMvRSTweenFactor = 170,
   keMvRSBlendOp = 171,
   keMvRSPositionDegree = 172,
   keMvRSNormalDegree = 173,
   keMvRSScissorTestEnable = 174,

//////////////////////////////////////////////////////////////////////////
// RENDERSTATE NOT SUPPORTED
/*
   keMvRSSlopeScaleDepthBias = 175,
   keMvRSAntialiasedLineEnable = 176,
   keMvRSMinTessellationLevel = 178,
   keMvRSMaxTessellationLevel = 179,
   keMvRSAdaptiveTessX  = 180,
   keMvRSAdaptiveTessY  = 181,
   keMvRSAdaptiveTessZ  = 182,
   keMvRSAdaptiveTessW  = 183,
   keMvRSEnableAdaptiveTessellation = 184,
   keMvRSTwoSidedStencilMode = 185,
   keMvRSCCWStencilFail  = 186,
   keMvRSCCWStencilZFail  = 187,
   keMvRSCCWStencilPass  = 188,
   keMvRSCCWStencilFunc  = 189,
   keMvRSColorWriteEnable1 = 190,
   keMvRSColorWriteEnable2 = 191,
   keMvRSColorWirteEnable3 = 192,
   keMvRSBlendFactor = 193,
   keMvRSSRGBWriteEnable = 194,
   keMvRSDepthBias = 195,
   keMvRSWrap8 = 198,
   keMvRSWrap9 = 199,
   keMvRSWrap10 = 200,
   keMvRSWrap11 = 201,
   keMvRSWrap12 = 202,
   keMvRSWrap13 = 203,
   keMvRSWrap14 = 204,
   keMvRSWrap15 = 205,
   keMvRSSepareteAlphaBlendEnable = 206,
   keMvRSSrcBlendAlpha = 207,
   keMvRSDestBlendAlpha = 208,
   keMvRSBlendOpAlpha = 209,
*/
//////////////////////////////////////////////////////////////////////////
   keMvRSFORCE_DWORD = 0x7fffffff
};

//
// Summary:
//    Defines the sampler state types.
//
enum EMvSamplerStateType {
   keMvSampAddressU      = 13,
   keMvSampAddressV      = 14,
   keMvSampAddressW      = 25,
   keMvSampBorderColor   = 15,
   keMvSampMagFilter     = 16,
   keMvSampMinFilter     = 17,
   keMvSampMipFilter     = 18,
   keMvSampMipMapLODBias = 19,
   keMvSampMaxMipLevel   = 20,
   keMvSampMaxAnisotropy = 21,
   keMvSampFORCE_DWORD   = 0x7fffffff
};

//
// Summary:
//    Defines texture stage states. 
//
enum EMvTextureStageStateType
{
   keMvTSSColorOp        =  1, /* D3DTEXTUREOP - per-stage blending controls for color channels */
   keMvTSSColorArg1      =  2, /* D3DTA_* (texture arg) */
   keMvTSSColorArg2      =  3, /* D3DTA_* (texture arg) */
   keMvTSSAlphaOp        =  4, /* D3DTEXTUREOP - per-stage blending controls for alpha channel */
   keMvTSSAlphaArg1      =  5, /* D3DTA_* (texture arg) */
   keMvTSSAlphaArg2      =  6, /* D3DTA_* (texture arg) */
   keMvTSSBumpEnvMat00   =  7, /* float (bump mapping matrix) */
   keMvTSSBumpEnvMat01   =  8, /* float (bump mapping matrix) */
   keMvTSSBumpEnvMat10   =  9, /* float (bump mapping matrix) */
   keMvTSSBumpEnvMat11   = 10, /* float (bump mapping matrix) */
   keMvTSSTexCoordIndex  = 11,
   keMvTSSBumpEnvLScale  = 22, /* float scale for bump map luminance */
   keMvTSSBumpEnvLOffset = 23, /* float offset for bump map luminance */
   keMvTSSTextureTransformFlags = 24, /* D3DTEXTURETRANSFORMFLAGS controls texture transform */
   keMvTSSColorArg0      = 26, /* D3DTA_* third arg for triadic ops */
   keMvTSSAlphaArg0      = 27, /* D3DTA_* third arg for triadic ops */
   keMvTSSResultArg      = 28, /* D3DTA_* arg for result (CURRENT or TEMP) */
   keMvTSSFORCE_DWORD   = 0x7fffffff /* force 32-bit size enum */
};

#define keMvTSSTCIPassthru                             0x00000000
#define keMvTSSTCICameraSpaceNormal                    0x00010000
#define keMvTSSTCICameraSpacePosition                  0x00020000
#define keMvTSSTCICameraSpaceReflectionVector          0x00030000
#define keMvTSSTCISphereMap                            0x00040000


//
// Summary:
//    Defines constants that describe the supported texture-addressing modes.
//
enum EMvfTextureAddress
{
    keMvTAddressWrap       = 1,  // Tile the texture at every integer junction. For example, for "u" values 
                                    // between 0 and 3, the texture is repeated three times; no mirroring
                                    // is performed. 
    keMvTAddressMirror     = 2,  // Similar to keMvTAddressWrap, except that the texture is flipped at 
                                    // every integer junction. For u values between 0 and 1, for example,
                                    // the texture is addressed normally; between 1 and 2, the texture is 
                                    // flipped (mirrored); between 2 and 3, the texture is normal again, 
                                    // and so on.
    keMvTAddressClamp      = 3,  // Texture coordinates outside the range [0.0, 1.0] are set to the texture
                                    // color at 0.0 or 1.0, respectively. 
    keMvTAddressBorder     = 4,  // Texture coordinates outside the range [0.0, 1.0] are set to the border color.
    keMvTAddressMirrorOnce = 5,  // Similar to keMvTAddressMirror and keMvTAddressClamp. Takes the absolute
                                    // value of the texture coordinate (thus, mirroring around 0), and then 
                                    //clamps to the maximum value. It is most commonly used for volume textures, 
                                    // where it is not necessary to support the full D3DTADDRESS_MIRRORONCE 
                                    // texture-addressing mode, but the data is symmetric around the one axis.
    keMvTAddress_FORCEDWORD = 0x7fffffff
};


// Summary:
//    Defines constants that describe transformation state values. 
//
enum EMvTransformStateType {
   keMvTSView = 2,         // Identifies the transformation matrix being set as the view transformation 
                              // matrix. The default value is NULL (the identity matrix). 
   keMvTSProjection = 3,   // Identifies the transformation matrix being set as the projection transformation
                              // matrix. The default value is NULL (the identity matrix). 
   keMvTSWorld = 256,      // Identifies the transformation matrix being set as the world(0) transformation 
                              // matrix. The default value is NULL (the identity matrix). 
   keMvTSTexture0 = 16,    // Identifies the transformation matrix being set for the specified texture stage. 
   keMvTSTexture1 = 17,    // Identifies the transformation matrix being set for the specified texture stage. 
   keMvTSTexture2 = 18,    // Identifies the transformation matrix being set for the specified texture stage. 
   keMvTSTexture3 = 19,    // Identifies the transformation matrix being set for the specified texture stage. 
   keMvTSTexture4 = 20,    // Identifies the transformation matrix being set for the specified texture stage. 
   keMvTSTexture5 = 21,    // Identifies the transformation matrix being set for the specified texture stage. 
   keMvTSTexture6 = 22,    // Identifies the transformation matrix being set for the specified texture stage. 
   keMvTSTexture7 = 23,    // Identifies the transformation matrix being set for the specified texture stage. 
   keMvTSFORCE_DWORD = 0x7fffffff
};

#define keMvTSWorldMatrix(index) (EMvTransformStateType)(index + 256) // Identifies the transformation matrix being set as the world(index) transformation matrix. The default value is NULL (the identity matrix). 

//
// Summary:
//    Defines the supported blend mode. 
//
enum EMvBlend
{
   keMvBlendZero = 1,
   keMvBlendOne = 2,
   keMvBlendSrcColor = 3,
   keMvBlendInvSrcColor = 4,
   keMvBlendSrcAlpha = 5,
   keMvBlendInvSrcAlpha = 6,
   keMvBlendDestAlpha = 7,
   keMvBlendInvDestAlpha = 8,
   keMvBlendDestColor = 9,
   keMvBlendInvDestColor = 10,
   keMvBlendSrcAlphaSat = 11,
   keMvBlendBothSrcAlpha = 12,
   keMvBlendBothInvSrcAlpha = 13,
   keMvBlendBlendFactor = 14,
   keMvBlendInvBlendFactor = 15,
   keMvBlendFORCE_DWORD = 0x7fffffff
};

//
// Summary:
//    Defines the supported culling modes.
//
enum EMvCull
{
   keMvCullNone = 1,
   keMvCullCW = 2,
   keMvCullCCW = 3,
   keMvCullFORCE_DWORD = 0x7fffffff
};

//
// Summary:
//    Defines the supported compare functions.
//
enum EMvCompareFunction
{
   keMvCmpNever = 1,
   keMvCmpLess = 2,
   keMvCmpEqual = 3,
   keMvCmpLessEqual = 4,
   keMvCmpGreater = 5,
   keMvCmpNotEqual = 6,
   keMvCmpGreaterEqual = 7,
   keMvCmpAlways = 8,
   keMvCmpFORCE_DWORD = 0x7fffffff
};

//
// Summary:
//    Defines constants describing the fill mode.
//
enum EMvFillMode
{
   keMvFillPoint = 1,      // Fill points. 
   keMvFillWireframe = 2,  // Fill wireframes.
   keMvFillSolid = 3,      // Fill solids. 
   keMvFillFORCE_DWORD = 0x7fffffff
};

//
// Summary:
//    Defines constants that describe the fog mode.
//
enum EMvFogMode
{
   keMvFogNone = 0,
   keMvFogExp = 1,
   keMvFogExp2 = 2,
   keMvFogLinear = 3,
   keMvFogFORCE_DWORD = 0x7fffffff
};

//
// Summary:
//    Defines constants that describe depth-buffer formats.
//
enum EMvZBufferType
{
    keMvZBufferFalse            = 0, // Disable depth buffering.
    keMvZBufferTrue             = 1, // Enable z-buffering.
    keMvZBufferUseWBuffer       = 2, // Enable w-buffering. (NOT SUPPORTED)
    keMvZBufferFORCE_DWORD      = 0x7fffffff  //force 32-bit size enum
};

//
// Summary:
//    Defines the light type. 
//
enum EMvLightType
{
   keMvLightPoint = 1,        // This type of light is a point source which radiates light in all  
                                 // directions from a position in space
   keMvLightSpot = 2,         // This type of light is a spotlight source whose illumniatinon is 
                                 // limisted to a cone. It has a direction and several other 
                                 // parameters that determine the shape of the coneit produces.
   keMvLightDirectional = 3,  // This type of light is a directional source, which is equivalent 
                                 // to using a point source at an infinite distance.
   keMvLightFORCE_DWORD = 0x7fffffff
};

//
// Summary:
//    Defines the shade mode.
//
enum EMvShadeMode
{
   keMvShadeFlat = 1,
   keMvShadeGouraud = 2,
   keMvShadeFORCE_DWORD = 0x7fffffff
};

//
// Summary:
//   Defines texture filtering modes for a texture stage
//
enum EMvTextureFilterType
{
   keMvTexFNone = 0,          // Mipmapping disabled. The rasterizer should use the magnification filter instead.
   keMvTexFPoint = 1,         // Point filtering used as a texture magnification/minification filter. 
                                 // The texel with coordinates nearest to the desired pixel value is used. 
                                 // Near-point mipmap filtering is used between mipmap levels. The rasterizer 
                                 // uses the color from the texel of the nearest mipmap texture. 
   keMvTexFLinear = 2,        // Bilinear interpolation filtering used as a texture magnification/minification 
                                 // filter. A weighted average of the 2x2 area of texels surrounding
                                 // the desired pixel is used. The triliniear mipmap interpolation filter is used 
                                 // between mipmap levels. The rasterizer linearly interpolates pixel color, 
                                 // using the texels of the two nearest mipmap textures.
   keMvTexFAnisotropic = 3,   // Anisotropic texture filtering used as a texture magnification/minification 
                                 // filter. Compensates for distortion caused by the angle difference between
                                 // the texture polygon and the plane of the screen. 
   keMvTexFFORCE_DWORD = 0x7fffffff
};

//
// Summary:
//    Defines the location at which a color or color component must be accessed for lighting calculations.
//
enum EMvMaterialColorSource
{
   keMvMCSMaterial = 0,
   keMvMCSColor1 = 1,
   keMvMCSColor2 = 2,
   keMvMCSFORCE_DWORD = 0x7fffffff
};

//
// Summary:
//    Defines flags used to control the number or matrices that the system applies when performing 
//    multimatrix vertex blending.
//
enum EMvVertexBlendFlags {
   keMvVBFDisable = 0,
   keMvVBF1Weights = 1,
   keMvVBF2Weights = 2,
   keMvVBF3Weights = 3,
   keMvVBFTweening = 255,
   keMvVBF0Weights = 256
};

//
// Summary:
//    Defines texture-stage state values.
//  
enum EMvTextureTransformFlags
{
    keMvTTFFDisable         = 0,    // Texture coordinates are passed directly.
    keMvTTFFCount1          = 1,    // Rasterizer should expect 1-D texture coordinates.
    keMvTTFFCount2          = 2,    // Rasterizer should expect 2-D texture coordinates.
    keMvTTFFCount3          = 3,    // Rasterizer should expect 3-D texture coordinates.
    keMvTTFFCount4          = 4,    // Rasterizer should expect 4-D texture coordinates.
    keMvTTFFProjected       = 256,  // Texcoords to be divided by COUNT-th element.
    keMvTTFFFORCE_DWORD     = 0x7fffffff
};


//
// Summary:
//    Defines the supported blending operation.
//
enum EMvBlendOperation
{
   keMvBlendOpAdd = 1,
   keMvBlendOpSubtract = 2,
   keMvBlendOpRevSubtract = 3,
   keMvBlendOpMin = 4,
   keMvBlendOpMax = 5,
   keMvBlendOpFORCE_DWORD = 0x7fffffff
};

//
// Summary:
//    Defines per-stage texture-blending operations
//
enum EMvTextureOperation
{
   keMvTOpDisable = 1,
   keMvTOpSelectArg1 = 2,
   keMvTOpSelectArg2 = 3,
   keMvTOpModulate = 4,
   keMvTOpModulate2X = 5,
   keMvTOpModulate4X = 6,
   keMvTOpAdd = 7,
   keMvTOpAddSigned = 8,
   keMvTOpAddSigned2X = 9,
   keMvTOpSubtract = 10,
   keMvTOpAddSmooth = 11,
   keMvTOpBlendDiffuseAlpha = 12,
   keMvTOpBlendTextureAlpha = 13,
   keMvTOpBlendFactorAlpha = 14,
   keMvTOpBlendTextureAlphaPM = 15,
   keMvTOpBlendCurrentAlpha = 16,
   keMvTOpPreModulate = 17,
   keMvTOpModulateAlphaAddColor  = 18,
   keMvTOpModulateColorAddAlpha  = 19,
   keMvTOpModulateInvAlphaAddColor  = 20,
   keMvTOpModulateInvColorAddAlpha  = 21,
   keMvTOpBumpEnvMap = 22,
   keMvTOpBumpEnvMapLuminance = 23,
   keMvTOpDotProduct3 = 24,
   keMvTOpMultiplyAdd = 25,
   keMvTOpLERP = 26,
   keMvTOpFORCE_DWORD = 0x7fffffff
};

//////////////////////////////////////////////////////////////////////////
// V E R T E X   D E C L A R A T I O N
//////////////////////////////////////////////////////////////////////////

// Vertex shader declaration

//
// Summary:
//    Vertex element semantics
//
enum EMvDeclUsage
{
    keMvDeclUsagePosition = 0,  // Position data. (keMvDeclUsagePosition with UsageIndex = 0 ) specifies
                                    // un-transformed position in fixed function vertex processing and 
                                    // the n-patch tessellator. (keMvDeclUsagePosition with UsageIndex = 1)
                                    // specifies un-transformed position in the fixed function vertex shader
                                    // for skinning.
    keMvDeclUsageBlendWeight,   // Blending weight data. (keMvDeclUsageBlendWeight with UsageIndex = 0) 
                                    // specifies the blend weights in fixed function vertex processing.
    keMvDeclUsageBlendIndices,  // Blending indices data. (keMvDeclUsageBlendIndices with UsageIndex = 0) 
                                    // specifies matrix indices for fixed function vertex processing using
                                    // indexed pa letted skinning.
    keMvDeclUsageNormal,        // Vertex normal data. (keMvDeclUsageNormal with UsageIndex = 0) specifies
                                    // vertex normals for fixed function vertex processing and the n-patch
                                    // tessellator. (keMvDeclUsageNormal with UsageIndex = 1) specifies 
                                    // vertex normals for fixed function vertex processing for skinning.
    keMvDeclUsagePSize,         // Point size data. (keMvDeclUsagePSize with UsageIndex = 0) specifies the
                                    // point-size attribute used by the rasterizer setup engine to 
                                    // expand a point into a quad for the point-sprite functionality.
    keMvDeclUsageTexCoord,      // Texture coordinate data. (keMvDeclUsageTexCoord, n) specifies texture 
                                    // coordinates in fixed function vertex processing and in pixel shaders
                                    // prior to pixel shader v3.0. These can be used to pass user defined data.
    keMvDeclUsageTangent,       // Vertex tangent data.
    keMvDeclUsageBinormal,      // Vertex binormal data.
    keMvDeclUsageTessFactor,    // Single positive floating point value. (keMvDeclUsageTessFactor with 
                                    // UsageIndex = 0) specifies the tessellation factor, which is used in the 
                                    // tessellation unit to control the rate of tessellation.
    keMvDeclUsagePositionT,     // Vertex data contains transformed position data. When a declaration 
                                    // containing this is set, the pipeline does not perform vertex processing.
    keMvDeclUsageColor,         // Vertex data contains diffuse or specular color. (keMvDeclUsageColor 
                                    // with UsageIndex = 0) specifies the diffuse color in the fixed 
                                    // function vertex shader and pixel shaders prior to pixel shader v3.0. 
                                    // (keMvDeclUsageColor with UsageIndex = 1) specifies the specular color
                                    // in the fixed function vertex shader and pixel shaders prior to 
                                    // pixel shader v3.0.
    keMvDeclUsageFog,           // Vertex data contains fog data. (keMvDeclUsageFog with UsageIndex = 0) 
                                    // specifies a fog blend value used after pixel shading finishes.
    keMvDeclUsageDepth,         // Vertex data contains depth data.
    keMvDeclUsageSample         // Vertex data contains sampler data. (keMvDeclUsageSample with UsageIndex = 0) 
                                    // specifies the displacement value to look up.
};

#define keMvMaxDeclUsage        keMvDeclUsageSample
#define keMvMaxDeclUsageIndex   15
#define keMvMaxDeclLength       64 // does not include "end" marker vertex element

//
// Summary:
//    Vertex element tesselation method
//
enum EMvDeclMethod
{
    keMvDeclMethodDefault = 0,
    keMvDeclMethodPartialU,
    keMvDeclMethodPartialV,
    keMvDeclMethodCrossUV,              // Normal
    keMvDeclMethodUV,
    keMvDeclMethodLookUp,               // Lookup a displacement map
    keMvDeclMethodLookUpPresampled      // Lookup a pre-sampled displacement map
};

#define keMvMaxDeclMethod keMvDeclMethodLOOKUPPRESAMPLED

//
// Summary:
//    Vertex element data type
//
enum EMvDeclType
{
    keMvDeclTypeFloat1    =  0,  // 1D float expanded to (value, 0., 0., 1.)
    keMvDeclTypeFloat2    =  1,  // 2D float expanded to (value, value, 0., 1.)
    keMvDeclTypeFloat3    =  2,  // 3D float expanded to (value, value, value, 1.)
    keMvDeclTypeFloat4    =  3,  // 4D float
    keMvDeclTypeD3DColor  =  4,  // Input is in D3DCOLOR format (ARGB) expanded to (R, G, B, A)
    keMvDeclTypeUByte4    =  5,  // 4D unsigned byte
    keMvDeclTypeShort2    =  6,  // 2D signed short expanded to (value, value, 0., 1.)
    keMvDeclTypeShort4    =  7,  // 4D signed short
    keMvDeclTypeUnused    = 17   // When the type field in a decl is unused.
};

#define keMvMaxDeclType      keMvDeclTypeUnused

//
// Summary:
//    This is used to initialize the last vertex element in a vertex declaration
//    array
//
#define keMvDeclEnd() {0xFF,0,keMvDeclTypeUnused,0,0,0} // Last element in a vertex declaration.

// Maximum supported number of texture coordinate sets
#define kulMvMaxTexCoord   8

// @}


//
// \defgroup struct_def Structures definition
//
// @{

//
// Summary:
//    Encapsulates an unsigned long representation of an ARGB/YCbCrA color.
//
struct SMvColor
{
public:
   union UMvColor
   {
      unsigned long ulColor; // Unsigned long representation of an ARGB/YUVA color.

      struct SMvARGB
      {
         unsigned char uchBlue;   // Blue component
         unsigned char uchGreen;  // Green component
         unsigned char uchRed;    // Red component
         unsigned char uchAlpha;  // Alpha component
      } sMvARGB;

      struct SMvACrYCb
      {
         unsigned char uchCb;     // Cb component
         unsigned char uchY;      // Y component
         unsigned char uchCr;     // Cr component
         unsigned char uchAlpha;  // Alpha component
      } sMvACrYCb;
   } uMvColor; // Union of all the components.

   //
   // Summary:
   //    Destructor.
   //
   ~SMvColor(void){}

   //
   // Summary:
   //    Default constructor.
   //    Initialize to transparent black (0x00000000).
   //
   SMvColor(void)
   {
      uMvColor.ulColor = 0x0;
   }

   // 
   // Constructor.
   //
   SMvColor(unsigned long in_ulColor   // Specifies the value of the color.
      )
   {
      uMvColor.ulColor = in_ulColor;
   }

   // 
   // Summary:
   //    Constructor.
   //
   SMvColor(EMvColor in_eColor   // Value of the color, represented as an EMvColor.
      )
   {
      switch(in_eColor)
      {
      case keMvColorBlack:
         uMvColor.ulColor = 0xFF101010;
         break;
      case keMvColorWhite:
         uMvColor.ulColor = 0xFFEBEBEB;
         break;
      case keMvColorRed:
         uMvColor.ulColor = 0xFFEB1010;
         break;
      case keMvColorGreen:
         uMvColor.ulColor = 0xFF10EB10;
         break;
      case keMvColorBlue:
         uMvColor.ulColor = 0xFF1010EB;
         break;
      case keMvColorSuperBlack:
      default:
         uMvColor.ulColor = 0xFF000000;
      }
   }

   //
   // Summary:
   //    4 components constructor.
   // 
   SMvColor(
      unsigned char in_uchAlpha,    // Specifies the value of the alpha component.
      unsigned char in_uchRedOrCr,  // Specifies the value of the red or Cr component.
      unsigned char in_uchGreenOrY, // Specifies the value of the green or Y component.
      unsigned char in_uchBlueOrCb  // Specifies the value of the blue or Cb component.
      )
   {
      uMvColor.sMvARGB.uchAlpha = in_uchAlpha;
      uMvColor.sMvARGB.uchRed   = in_uchRedOrCr;
      uMvColor.sMvARGB.uchGreen = in_uchGreenOrY;
      uMvColor.sMvARGB.uchBlue  = in_uchBlueOrCb;
   }

   //
   // Summary:
   //    3 components constructor.  Sets the alpha to opaque.
   //
   SMvColor(
      unsigned char in_uchRedOrCr,  // Specifies the value of the red or Cr component.
      unsigned char in_uchGreenOrY, // Specifies the value of the green or Y component.
      unsigned char in_uchBlueOrCb  // Specifies the value of the blue or Cb component.
      )
   {
      uMvColor.sMvARGB.uchAlpha = 255;
      uMvColor.sMvARGB.uchRed   = in_uchRedOrCr;
      uMvColor.sMvARGB.uchGreen = in_uchGreenOrY;
      uMvColor.sMvARGB.uchBlue  = in_uchBlueOrCb;
   }

   // 
   // Summary:
   //    4 floating-point components constructor.
   //
   SMvColor(
      float in_fAlpha,     // Value of the alpha component in float.
      float in_fRedOrCr,   // Value of the red or Cr component in float.
      float in_fGreenOrY,  // Value of the green or Y component in float.
      float in_fBlueOrCb   // Value of the blue or Cb component in float.
      )
   {
      uMvColor.sMvARGB.uchAlpha = (unsigned char)((in_fAlpha * 255.0f));
      uMvColor.sMvARGB.uchRed   = (unsigned char)(16.0f + (in_fRedOrCr  * 219.0f));
      uMvColor.sMvARGB.uchGreen = (unsigned char)(16.0f + (in_fGreenOrY * 219.0f));
      uMvColor.sMvARGB.uchBlue  = (unsigned char)(16.0f + (in_fBlueOrCb * 219.0f));
   }

   //
   // Summary:
   //    3 floating-point components constructor.  Sets the alpha to opaque.
   //
   SMvColor(
      float in_fRedOrCr,   // Specifies the value of the red or Cr component in float.
      float in_fGreenOrY,  // Specifies the value of the green or Y component in float.
      float in_fBlueOrCb   // Specifies the value of the blue or Cb component in float.
      )
   {
      uMvColor.sMvARGB.uchAlpha = 255;
      uMvColor.sMvARGB.uchRed   = (unsigned char)(16.0f + (in_fRedOrCr  * 219.0f));
      uMvColor.sMvARGB.uchGreen = (unsigned char)(16.0f + (in_fGreenOrY * 219.0f));
      uMvColor.sMvARGB.uchBlue  = (unsigned char)(16.0f + (in_fBlueOrCb * 219.0f));
   }
};

//
// Summary:
//    Structure used to encapsulate a floating-point representation of an ARGB color.
//
struct SMvColorF
{
public:
   float fRed;    // Float representing the red component.
   float fGreen;  // Float representing the green component.
   float fBlue;   // Float representing the blue component.
   float fAlpha;  // Float representing the alpha component.

   //
   // Summary:
   //    Default constructor.
   //    Sets the color to black transparent (0.0f, 0.0f, 0.0f, 0.0f).
   //
   SMvColorF()
   {
      fRed   = 0;
      fGreen = 0;
      fBlue  = 0;
      fAlpha = 0;
   }

   // 
   //    Constructor
   //
   SMvColorF(
      float in_fAlpha,  // Value to be used as the alpha of the color.
      float in_fRed,    // Value to be used as the red of the color.
      float in_fGreen,  // Value to be used as the green of the color.
      float in_fBlue    // Value to be used as the blue of the color.
      )
   {
      fRed   = in_fRed;
      fGreen = in_fGreen;
      fBlue  = in_fBlue;
      fAlpha = in_fAlpha;
   }

};

//
// Summary:
//    Encapsulates a write mask.
//
struct SMvMask
{
public:
   unsigned long ulMask; // Write mask.

   //
   //    Constructor.
   //
   SMvMask(unsigned long in_ulMask  // Value to use as the write mask.
      )
   {
      ulMask = in_ulMask;
   }

   //
   // Summary:
   //    Default constructor. 
   //    Sets the mask to an opaque black, which means that no mask will be applied.
   //
   SMvMask()
   {
      ulMask = 0xFFFFFFFF;
   }
};

//
// Summary:
//    Vector with 3 components (X,Y,Z)
//
struct SMvVector3 
{
   float fx; // X component
   float fy; // Y component
   float fz; // Z component
};

//
// Summary:
//    Vector with 4 components (X,Y,Z,W)
//
struct SMvVector4
{
   float fx; // X component
   float fy; // Y component
   float fz; // Z component
   float fw; // W component
};

//
// Summary:
//    Device creation information.
//
struct SMvCreateDeviceDescription
{
   uint32_t                  Size;                         // Structure size, in bytes.
   EMvHardwareProfile      eHardwareProfileType;         // Indicates on which hardware profile the Flex Engine should be created.
   unsigned long           ulHardwareProfileIndex;       // Identifies the index of the hardware profile on which Flex Engine should initialize.
   SMvResolutionInfo       sEditResolution;              // Defines the editing resolution.
};

//
// Summary:
//    Light properties
//
struct SMvLight
{
   EMvLightType eType;     // Specifies the light source type.
   SMvColorF sDiffuse;     // Specifies the diffuse color emitted by the light.
   SMvColorF sSpecular;    // Specifies the specular color emitted by the light.
   SMvColorF sAmbient;     // Specifies the ambient color emitted by the light.
   SMvVector3 sPosition;   // Specifies the position of the light in world space, specified by a #SMvVector3 structure. 
                              // This member has no meaning for directional lights and is ignored in that case.
   SMvVector3 sDirection;  // Specifies the direction that the light is pointing in world space, specified by a 
                              // #SMvVector3 structure. This member is only meaningful for directional lights and spotlights. 
                              // This vector should have a nonzero length, but does not need to be normalized. 
   float fRange;           // Specifies the distance beyond which the light has no effect. The maximum allowable value 
                              // for this member is the square root of FLT_MAX. This member does not 
                              // affect directional lights. 
   float fFalloff;         // Specifies the decrease in illumination between a spotlight's inner cone (the angle specified
                              // by theta) and the outer edge of the outer cone (the angle specified by phi). 
                              // The falloff effect on the lighting is subtle. Furthermore, a small performance 
                              // penalty is incurred by shaping the falloff curve. For these reasons, most developers set this value to 1.0.
   float fAttenuation0;    // Specifies how the light intensity changes over distance. Attenuation
                              // values are ignored for directional lights. This member represents an 
                              // attenuation constant.  Valid values for this member range from 0.0 to
                              // infinity. For non-directional lights, the three attenuation values should
                              // not be set to 0.0 at the same time.
   float fAttenuation1;    // Specifies how the light intensity changes over distance. Attenuation values are ignored 
                              // for directional lights. Valid values for this member range from 0.0 to infinity. For  
                              // non-directional lights, the three attenuation values should not be set to 0.0 at the same time.
   float fAttenuation2;    // Speciifies how the light intensity changes over distance. Attenuation 
                              // values are ignored for directional lights. This member represents an 
                              // attenuation constant.  Valid values for this member range from 0.0 to 
                              // infinity. For non-directional lights, the three attenuation values should
                              // not be set to 0.0 at the same time.
   float fTheta;           // Specifies the angle of a spotlight's inner cone (in radians), that is, the fully illuminated 
                              // spotlight cone. The values allowed range between 0 and the angle specified by Phi.
   float fPhi;             // Specifies the angle of the outer edge of the spotlight's outer cone (in radians). 
                              // Points outside this cone are not lit by the spotlight. This value must
                              // be between 0 and pi. 
};

//
// Summary:
//    Material properties.
//
struct SMvMaterial
{
   SMvColorF sDiffuse;  // Specifies the diffuse color of the material.
   SMvColorF sAmbient;  // Specifies the ambient color of the material.
   SMvColorF sSpecular; // Specifies the specular color of the material.
   SMvColorF sEmissive; // Specifies the emissive color of the material.
   float fPower;        // Floating-point value specifying the sharpness of specular highlights. 
                           // The higher the value, the sharper the highlight.
};

//
// Summary:
//    Matrix abstraction.
//
struct SMvMatrix 
{
   union UMvMatrix
   {
      struct SMvMatrixElement
      {
         float        _11, _12, _13, _14;
         float        _21, _22, _23, _24;
         float        _31, _32, _33, _34;
         float        _41, _42, _43, _44;
      }sMvMatrixElement;
      float m[4][4];
   }uMvMatrix;
};

//
// Summary:
//    Defines input vertex data to the pipeline. 
//
// Remarks:
//    Vertex data is defined using an array of SMvVertexElement structures.  This array must always
//    end with #keMvDeclEnd.
//
struct SMvVertexElement
{
   unsigned short ushStream;     // Specifies the stream number this field is to be read from.
   unsigned short ushOffset;     // Specifies the offset, in bytes, that this field is being read from.
   unsigned char  uchType;       // Specifies the vertex element data type. See #EMvDeclMethod
   unsigned char  uchMethod;     // Specifies the vertex element tesselation method. See #EMvDeclMethod.
   unsigned char  uchUsage;      // Defines the intended use of the data. For more information, 
                                    // see #EMvDeclUsage.
   unsigned char  uchUsageIndex; // Modifies the usage data to allow the user to specify multiple 
                                    // usage types.
};

//
// Summary:
//    Describes a vertex buffer.
//
struct SMvVertexBufferDesc
{
   unsigned long     ulUsage;          // Combination of one or more flags specifying the use of 
                                          // this buffer.
   EMvMemoryLocation eMemoryLocation;  // Specifies the memory location of the buffer.
   unsigned int      uiLength;         // Specifies the lenght of the vertex buffer in bytes.
   unsigned long     ulFVF;            // FVF that describes the format of this vertex buffer.
};

//
// Summary:
//    Describes an index buffer.
//
struct SMvIndexBufferDesc 
{
   EMvIndexSize         eIndexSize;       // Indicates whether the index size is 16 bits or 32 bits.
   unsigned long        ulUsage;          // Combination of one or more flags specifying the use of
                                             // this buffer.
   EMvMemoryLocation    eMemoryLocation;  // Specifies the memory location of the buffer.
   unsigned int         uiLength;         // Size of the buffer in bytes.
};

//
// Summary:
//    Specifies the view matrix properties
//
struct SMvViewDesc
{
   uint32_t             size;               // Specifies the size of the structure, for versioning.
   SMvVector3         sViewerPosition;    // Viewer position.
   SMvVector3         sViewerDirection;   // Specifies the direction in which the viewer is looking.
   SMvVector3         sViewerUp;          // Specifies the "up" direction in the current world.
};

//
// Summary:
//    Specifies the projection matrix properties
//
struct SMvProjectionDesc
{
   uint32_t              size;     // Specifies the size of the structure, for versioning.
   float               fFovY;    // Specifies the field of view in the y-direction in radians
   float               fAspect;  // Specifies the aspect ratio, defined as view space height divided by width.
   float               fNearZ;   // Specifies the z-value of the near view-plane.
   float               fFarZ;    // Specifies the z-value of the far view-plane.
};

//
// Summary:
//    Viewport properties
//
// Remarks:
//    The ulX, ulY, ulWidth, and ulHeight members describe the position and dimensions of the viewport on 
//    the render target surface. Usually, applications render to the entire target surface; when 
//    rendering on a 640x480 surface, these members should be 0, 0, 640, and 480, respectively. The 
//    fMinZ and fMaxZ are typically set to 0.0 and 1.0 but can be set to other values to achieve 
//    specific effects. For example, you might set them both to 0.0 to force the system to render 
//    objects to the foreground of a scene, or both to 1.0 to force the objects into the background. 
//
struct SMvViewport
{
   uint32_t              size;     // Size of the structure, for versioning.
   unsigned long       ulX;      // Pixel x-coordinate of the upper-left corner of the viewport on the
                                    // render target surface. Unless you want to render to a subset of 
                                    //the surface, this member can be set to 0. 
   unsigned long       ulY;      // Pixel y-coordinate of the upper-left corner of the viewport on the 
                                    // render target surface. Unless you want to render to a subset of 
                                    // the surface, this member can be set to 0. 
   unsigned long       ulWidth;  // Specifies the width of the clip volume in pixels. This member should 
                                    // be set to the width of the render target surface, 
                                    // unless you are rendering only to a subset of the surface.
   unsigned long       ulHeight; // Specifies the height  of the clip volume in pixels. This member should 
                                    // be set to the height of the render target surface, unless you are 
                                    // rendering only to a subset of the surface, t. 
   float               fMinZ;    // Describes the minimum depth value of the clip volume in which a scene is to be rendered. Most applications set this value to 0.0.
                                    // Clipping is performed after applying the projection matrix.
   float               fMaxZ;    // Describes the maximum depth value of the clip volume in which a scene is to be rendered. Most applications set this value to 1.0.
                                    // Clipping is performed after applying the projection matrix. 
};

//
// SMvFlex3DCaps
//
struct SMvFlex3DCaps
{
   unsigned long ulMaxTextureWidth;
   unsigned long ulMaxTextureHeight;
   unsigned long ulMaxVolumeExtent;
   unsigned long ulMaxTextureRepeat;
   unsigned long ulMaxTextureAspectRatio;
   unsigned long ulMaxAnisotropy;
   float         fMaxVertexW;
   float         fGuardBandLeft;
   float         fGuardBandTop;
   float         fGuardBandRight;
   float         fGuardBandBottom;
   float         fExtentsAdjust;
   unsigned long ulMaxTextureBlendStages;
   unsigned long ulMaxSimultaneousTextures;
   unsigned long ulVertexProcessingCaps;
   unsigned long ulMaxActiveLights;
   unsigned long ulMaxUserClipPlanes;
   unsigned long ulMaxVertexBlendMatrices;
   unsigned long ulMaxVertexBlendMatrixIndex;
   float         fMaxPointSize;
   unsigned long ulMaxPrimitiveCount;
   unsigned long ulMaxVertexIndex;
   unsigned long ulMaxStreams;
   unsigned long ulMaxStreamStride;
   unsigned long ulVertexShaderVersion;
   unsigned long ulMaxVertexShaderConst;
   unsigned long ulPixelShaderVersion;
   float         fPixelShader1xMaxValue;
   unsigned long ulNumSimultaneousRTs;
   unsigned long ulMaxVShaderInstructionsExecuted;
   unsigned long ulMaxPShaderInstructionsExecuted;
};

/// @}



#endif

