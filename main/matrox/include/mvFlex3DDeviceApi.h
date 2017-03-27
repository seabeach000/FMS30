// $Archive: /VP/FLEXVIDEO/LIBS/MVFFLEX3DDEVICEAPI/Inc/mvFlex3DDeviceApi.h $

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
//                         MvFlex3DDevice_IF.h
//----------------------------------------------------------------
//   Birth Date:       December 2002
//   Operating System: WindowsXP
//   Author:           Luc Poirier
//----------------------------------------------------------------
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada 
//----------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////
///
/// \mainpage Flex 3D Device API
/// <HR>
/// \section intro Introduction
/// The new Flex architecture provides all the functionality required on the DS.X1000 and is 
/// designed open enough to be easily extended to support future hardware. The 3D acceleration 
/// of video effects is handled by a new module, built from the ground up, that aims at maximizing 
/// ease of coding, performance and integration with the whole Flex infrastructure.
/// <BR><BR> 
/// Matrox Video Products group has spent great time and resources evangelizing its partners about 
/// the difficulties of integrating 3D acceleration to video editing. Standard 3D API's, such as 
/// Direct3D and OpenGL, are simply not designed to handle video, and they simply don't support 
/// features that are central to realtime video editing, such as buffer synchronization, 
/// interlacing compensation, and YUV color-space rendering.
/// <BR><BR> 
/// This new 3D API presented herein, tries to provide the best of both worlds, i.e. an interface 
/// that resembles closely to a standard API, namely Direct3D 9.0, and that integrates tightly with 
/// the rest of the Flex infrastructure, providing all the missing features specific to video editing.
/// <BR><BR> 
/// This document presents the different interfaces related to the <B>Flex 3D Device API</B>. These interfaces 
/// provide the following functionalities:
/// <BR>
/// - Graphic 3D device creation
/// <BR>
/// - Graphic 3D device state control
/// <BR>
/// - 3D scene setup control (view, projection and world transformations)
/// <BR>
/// - Video surface management (colorfill, copy, mipmap generation, etc.)
/// <BR>
/// - Rendering of 3D primitives made up of vertices
/// <BR>
/// - Texture mapping of video streams
/// <BR>
/// - Vertex shaders
/// <BR>
/// - Pixel shaders
/// <BR>
///
/// \section ToI Additional information
/// - \ref shaderdoc
/// - \ref antialiasing
/// - \ref synchro
/// - \ref devicecaps
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


#ifndef _MvFLEX3DDEVICE_IF_INCLUDED_2002_12_12_MONTREAL_
#define _MvFLEX3DDEVICE_IF_INCLUDED_2002_12_12_MONTREAL_

#ifdef _WIN32
   #include "windows.h"
   #include "unknwn.h"
#else
   #include "mvLinuxDefinitions.h"
#endif

#include "mvDefinitions.h"
#include "mvFlex3DDeviceStructs.h"
#include "mvFlex3DDeviceGuids.h"
#include "mvFlex3DDeviceErrors.h"
#include "mvMatrix.h"
#include "mvColor.h"
#include "mvVector3.h"
#include "mvVector4.h"


//
// Forward declaration 
//
interface IMvFlex3DDevice;
interface IMvFlex3DVertexBuffer;
interface IMvFlex3DIndexBuffer;
interface IMvFlex3DVertexDeclaration;
interface IMvFlex3DVertexShader;
interface IMvFlex3DPixelShader;
interface IMvFlex3DStateBlock;
interface IMvFlex3DHelpers;
interface IMvEffectSettings;
struct    SMvEffectCapabilities;

//
// Summary:
//    Main interface for controlling the 3D device. 
// Description:   
//    It exposes all the methods required to create, render and shade primitives. 
//    It shockingly resembles to the IDirect3DDevice9 interface, but is more oriented toward video edition
//    and manipulation.
//
interface IMvFlex3DDevice : public IUnknown
{
public:
   //
   // Summary:
   //    Begins a scene.
   //    This method must be called before doing primitives rendering.
   // Return Value:
   //   - MV_NOERROR, if the method succeeds.
   //   - MV_E_INVALID_CALL, if BeginScene is called while already in a BeginScene / EndScene pair. 
   //         This happens only when BeginScene is called twice without first calling EndScene.
   // Remarks:
   //    IMvFlex3DDevice::BeginScene causes the Flex graphic engine to check its internal 
   //      data structures and the availability and validity of rendering surfaces. It also sets 
   //      an internal flag to signal that a scene is in progress. After you begin a scene, you 
   //      can call the various rendering methods to render the primitives or individual 
   //      vertices that make up the objects in the scene. Attempts to call rendering methods when 
   //      a scene is not in progress fail.
   //
   virtual HRESULT __stdcall BeginScene() = 0;

   //
   // Summary:
   //    Marks the starting point of Flex surface synchronization and provides the Matrox Flex 3D Device driver with the 
   //    synchronization objects of surfaces used as input and output by the 3D device operation(s) to
   //    follow.
   // Return value:
   //    - MV_NOERROR, if the method succeeds.
   //    - MV_E_INVALID_CALL, if the method fails.  This happens only when BeginSynchronizedAccess() 
   //         is called twice without first calling EndSyncrhonizedAccess().
   // Remarks:
   //       The Matrox Flex 3D Device driver implements surface synchronization by managing the synchronization 
   //       objects of input/output surfaces used by a specific graphic engine operation. Hence, 
   //       for proper effect sequencing, it is imperative that every Flex operation making use 
   //       of the Flex graphic engine begins with a BeginSynchronizedAccess() and ends with a 
   //       EndSynchronizedAccess() call.
   //
   virtual HRESULT __stdcall BeginSynchronizedAccess(
      IMvSurface    **in_apISurfacesInput,            // Pointer to an array of surfaces used as input by this effect.
      unsigned long   in_ulNumSurfacesInput,          // Number of surfaces contained in the array of input surfaces.
      IMvSurface    **in_apISurfacesEffectPattern,    // Pointer to an array of surfaces used as effect pattern by 
                                                         // this effect.  Can be set to NULL.
      unsigned long   in_ulNumSurfacesEffectPattern,  // Number of surfaces contained in the array of effect 
                                                         // pattern surfaces.
      IMvSurface     *in_pISurfaceBackground,         // Pointer to a surface used as the background by this effect.
                                                         // Can be set to NULL.
      IMvSurface    **in_apISurfacesOutput,           // Pointer to an array of surfaces used as output by this effect.
      unsigned long   in_ulNumSurfacesOutput          // Number of surfaces contained in the array of output surfaces.
      ) = 0;

   //
   // Summary:
   //    Clears the viewport, or a set of rectangles in the viewport, to a specified RGBA color, clears the depth buffer, and erases the stencil buffer
   // Return Value:
   //    - MV_NOERROR, if the method succeeds.
   //    - MV_E_INVALID_CALL, if the method fails.
   //
   virtual HRESULT __stdcall Clear(
      unsigned long      in_ulCount,      // Number of rectangles in the array at in_pkaoRects. If you set in_pkaoRects 
                                             // to NULL, this parameter must be set to 0. 
      const RECT        *in_pkarcRects,   // Pointer to an array of Rect structures that describe the rectangles to 
                                             // clear. Set a rectangle to the dimensions of the rendering target to clear the 
                                             // entire surface. Each rectangle uses screen coordinates that correspond to points 
                                             // on the render target surface. Coordinates are clipped to the bounds of the 
                                             // viewport rectangle. This parameter can be set to NULL to indicate that the 
                                             // entire viewport rectangle is to be cleared.
      unsigned long      in_ulFlags,      // Flags that indicate which surfaces should be cleared. 
                                             // This parameter can be any combination of the following flags, but at least 
                                             // one flag must be used:
                                             // <p><I>keMvClearStencil</I>: Clear the stencil buffer to the value in the 
                                             // in_ulStencil parameter. 
                                             // <p><I>keMvClearTarget</I>: Clear the render target to the color in the 
                                             // in_pksColor parameter. 
                                             // <p><I>keMvClearZBuffer</I>: Clear the depth buffer to the value in the
                                             // in_fZ parameter. 
      const SMvColor     in_ksColor,      // A color value to which the render target surface is cleared.
      float              in_fZ,           // New z value that this method stores in the depth buffer. This parameter can be 
                                             // in the range from 0.0 through 1.0 (for z-based or w-based depth buffers). A 
                                             // value of 0.0 represents the nearest distance to the viewer, and 1.0 the farthest 
                                             // distance. 
      unsigned long      in_ulStencil     // Integer value to store in each stencil-buffer entry. This parameter can 
                                             // be in the range from 0 through 2^n-1, where n is the bit depth of the stencil 
                                             // buffer. 
      ) = 0;

   //
   // Summary:
   //    Creates an index buffer.
   // Return Value:
   //    - MV_NOERROR, if the method succeeds.
   //    - MV_E_INVALID_CALL, if the method fails.
   //    - MV_E_OUT_OF_MEMORY, if Flex3DDevice could not allocate enough memory to complete the call.
   // Remarks:
   //    - The use of index buffers enables Flex3D to avoid unnecessary data copying and to place the
   //          buffer in the optimal memory type for the expected usage. 
   //    - To use index buffers, create an index buffer, lock it, fill it with indices, unlock it, 
   //          pass it to IMvFlex3DDevice::SetIndices, set up the vertices, set up the vertex shader 
   //          or legacy fixed-function pipeline, and call IMvFlex3DDevice::DrawIndexedPrimitive for 
   //          rendering
   //
   virtual HRESULT __stdcall CreateIndexBuffer(
      unsigned int            in_uiLength,         // Size of the index buffer, in bytes.
      unsigned long           in_ulUsage,          // Usage can be 0, which indicates no usage value. However, if usage is 
                                                      // desired, use a combination of one or more #EMvUsage constants.
      EMvIndexSize              in_eIndexSize,     // Member of the #EMvIndexSize enumerated type, describing the format of 
                                                      // the index buffer.
      EMvMemoryLocation       in_eMemoryLocation,  // Member of the EMvMemoryLocation enumerated type, describing a valid
                                                      // memory class into which to place the index buffer. Valid types are 
                                                      // keMvMemoryLocationHost and keMvMemoryLocationGraphic.
      IMvFlex3DIndexBuffer **out_ppIIndexBuffer,   // Address of a pointer to an IMvFlex3DIndexBuffer interface, 
                                                      // representing the created index buffer resource.
      HANDLE                 *in_pHandle           // Reserved. Set this parameter to NULL.
      ) = 0;

   //
   // Summary:
   //    Creates a pixel shader.
   // Return Value:
   //    - MV_NOERROR, if the method succeeds.
   //    - MV_E_INVALID_CALL, if the method fails.
   // Remarks:
   //    - More information about \ref shaderdoc.
   //
   virtual HRESULT __stdcall CreatePixelShader(
      const unsigned long      *in_pkulFunction,      // Pointer to the pixel shader function token array, specifying the 
                                                         // blending operations. This value cannot be NULL.
      IMvFlex3DPixelShader      **out_ppIPixelShader  // Pointer to the returned pixel shader interface.
      ) = 0;

   // 
   // Summary:
   //    Creates a new state block that contains the values for all device states, vertex-related states, 
   //    or pixel-related states.
   // Return Value:
   //    - MV_NOERROR, if the method succeeds.
   //    - MV_E_INVALID_CALL, if the method fails.
   //
   virtual HRESULT __stdcall CreateStateBlock(
      EMvStateBlockType        in_eStateBlockType, // Type of state data that the method should capture. This parameter 
                                                      // can be set to a value defined in the EMvStateBlockType enumerated type.
      IMvFlex3DStateBlock    **out_ppIStateBlock   // Pointer to a state block interface
      ) = 0;

   //
   // Summary:
   //    Creates a vertex buffer.
   // Return Value:
   //    - MV_NOERROR, if the method succeeds.
   //    - MV_E_INVALID_CALL, if the method fails.
   // Remarks:
   //    The IMvFlex3DDevice interface supports rendering of primitives using vertex data stored 
   //    in vertex buffer objects. Vertex buffers are created from the IMvFlex3DDevice, and are 
   //    usable only with the IMvFlex3DDevice object from which they are created.
   //
   virtual HRESULT __stdcall CreateVertexBuffer(
      unsigned int              in_uiLength,          // Size of the vertex buffer, in bytes. For flexible vertex format (FVF) vertex 
                                                         // buffers, Length must be large enough to contain at least one vertex, but it 
                                                         // need not be a multiple of the vertex size. Length is not validated for non-FVF 
                                                         // buffers. See Remarks.
      unsigned long             in_ulUsageFlags,      // Usage can be 0, which indicates no usage value. However, if usage is 
                                                         // desired, use a combination of one or more #EMvUsage constants.
      unsigned long             in_ulFVF,             // Combination of EMvFVF, a usage specifier that describes the vertex format of 
                                                         // the vertices in this buffer. If this parameter is set to a valid FVF code, the 
                                                         // created vertex buffer is an FVF vertex buffer (see Remarks). Otherwise, if this 
                                                         // parameter is set to zero, the vertex buffer is a non-FVF vertex buffer.
      EMvMemoryLocation         in_eMemoryLocation,   // Member of the EMvMemoryLocation enumerated type, describing a valid 
                                                         // memory class into which to place the resource. Valid types are 
                                                         // keMvMemoryLocationHost and keMvMemoryLocationGraphic.
      IMvFlex3DVertexBuffer  **ppIVertexBuffer,       // Address of a pointer to an IMvFlex3DVertexBuffer interface, 
                                                         // representing the created vertex buffer resource.
      HANDLE                   *pHandle               // Reserved. Set this parameter to NULL.
      ) = 0;

   //
   // Summary:
   //    Creates a vertex shader declaration from the device and the vertex elements.
   // Return value:
   //    - MV_NOERROR, if the method succeeds.
   //    - MV_E_INVALID_CALL, if the method fails.
   //
   virtual HRESULT __stdcall CreateVertexDeclaration(
      const SMvVertexElement        *in_pksVertexElements,  // An array of vertex elements.
      IMvFlex3DVertexDeclaration      **out_ppIDecl         // Pointer to a pointer that returns the created vertex shader 
                                                               // declaration.
      ) = 0;

   //
   // Summary:
   //    Creates a vertex shader from a token array (vertex shader bytecode).
   // Return value:
   //    - MV_NOERROR, if the method succeeds.
   //    - MV_E_INVALID_CALL, if the method fails.
   // Remarks:
   //    - More information about \ref shaderdoc.
   //
   virtual HRESULT __stdcall CreateVertexShader(
      const unsigned long      *in_pkulFunction,   // Pointer to the vertex shader function token array. This parameter 
                                                      // defines the operations to apply to each vertex.
      IMvFlex3DVertexShader  **out_ppIVertexShader // Pointer to the returned vertex shader interface
      ) = 0;

   //
   // Summary:
   //    Fills a surface with a solid color.
   // Return Values:
   //    - MV_NOERROR, if the method succeeds.
   //    - MV_E_INVALID_CALL, if the method fails.
   //
   virtual HRESULT __stdcall ColorFill(
      IMvSurface       *in_pISurface,        // Surface to fill.
      EMvFaceType       in_eFace,            // Face of the surface to fill.
      const RECT        *in_pkrcRect,        // Region in the surface to fill.
      const SMvColor    in_ksColor,          // Color to use to fill the surface.
      const SMvMask     in_ksColorWriteMask  // Write mask to use with the color fill.
      ) = 0;

   //
   // Summary:
   //    Renders the specified geometric primitive, based on indexing into an array of vertices.
   // Return Value:
   //    - MV_NOERROR, if the method succeeds.
   //    - MV_E_INVALID_CALL, if the method fails.
   // Remarks:
   //    - This method draws indexed primitives from the current set of data input streams.
   //    - in_uiMinIndex and all the indices in the index stream are relative to the in_uiBaseVertexIndex.
   //    - The in_uiMinIndex and in_uiNumVertices parameters specify the range of vertex indices used 
   //          for each IMvFlex3DDevice::DrawIndexedPrimitive call. These are used to optimize vertex 
   //          processing of indexed primitives by processing a sequential range of vertices prior to 
   //          indexing into these vertices. It is invalid for any indices used during this call to 
   //          reference any vertices outside of this range.
   //    - IMvFlex3DDevice::DrawIndexedPrimitive fails if no index array is set.
   //    - The keMvPTPointList member of the #EMvPrimitiveType enumerated type is not supported and 
   //          is not a valid type for this method.
   //    - When using the legacy fixed function 3D pipeline, you must add a call to 
   //          IMvFlex3DDevice::SetFVF before you make any Draw calls.
   //
   virtual HRESULT __stdcall DrawIndexedPrimitive (
      EMvPrimitiveType in_ePrimitiveType,       // Member of the #EMvPrimitiveType enumerated type, describing the 
                                                   // type of primitive to render. See Remarks.
      unsigned int      in_uiBaseVertexIndex,   // Offset from the start of the index buffer to the first vertex index.
      unsigned int      in_uiMinIndex,          // Minimum vertex index for vertices used during this call.
      unsigned int      in_uiNumVertices,       //Number of vertices used during this call, starting from 
                                                   // BaseVertexIndex + MinIndex. 
      unsigned int      in_uiStartIndex,        // Location in the index array to start reading vertices.
      unsigned int      in_uiPrimitiveCount     // Number of primitives to render. The number of vertices used is a 
                                                   // function of the primitive count and the primitive type. The maximum 
                                                   // number of primitives allowed is 2147483647.
      ) = 0;

   //
   // Summary:
   //    Renders the specified geometric primitive with data specified by a user memory pointer.
   // Return Value:
   //   - MV_NOERROR, if the method succeeds.
   //   - MV_E_INVALID_CALL, if the method fails.
   // Remarks:
   //   - This method is intended for use in applications that are unable to store their vertex data 
   //          in vertex buffers. 
   //   - This method supports only a single vertex stream, which must be declared as stream 0. 
   //   - Following any IMvFlex3DDevice::DrawIndexedPrimitiveUP call, the stream 0 settings, 
   //          referenced by IMvFlex3DDevice::GetStreamSource, are set to NULL. Also, the index buffer 
   //          setting for IMvFlex3DDevice::SetIndices is set to NULL.
   //   - The vertex data passed to IMvFlex3DDevice::DrawIndexedPrimitiveUP does not need to persist 
   //          after the call. Matrox Flex3D completes its access to that data prior to returning from 
   //          the call.
   //   - When using the legacy fixed function 3D pipeline, you must add a call to 
   //          IMvFlex3DDevice::SetFVF before you make any Draw calls.
   //
   virtual HRESULT __stdcall DrawIndexedPrimitiveUP(
      EMvPrimitiveType      in_ePrimitiveType,           // Member of the #EMvPrimitiveType enumerated type, describing the type 
                                                            // of primitive to render.
      unsigned int          in_uiMinVertexIndex,         // Minimum vertex index, relative to zero (the start of 
                                                            // in_pkvVertexStreamZeroData), for vertices used during this call.
      unsigned int          in_uiNumVertexIndices,       // Number of vertices used during this call, starting from 
                                                            // in_uiMinVertexIndex.
      unsigned int          in_uiPrimitiveCount,         // Number of primitives to render. The number of indices used is a 
                                                            // function of the primitive count and the primitive type. The maximum 
                                                            // number of primitives allowed is 2147483647.
      const void           *in_pkvIndexData,             // User memory pointer to the index data.
      EMvIndexSize         in_eIndexSize,                // Member of the EMvIndexSize enumerated type, describing the format of the 
                                                            // index data.
      const void           *in_pkvVertexStreamZeroData,  // User memory pointer to vertex data to use for 
                                                            // vertex stream 0.
      unsigned int          in_uiVertexStreamZeroStride  // Stride between data for each vertex, in bytes.
                                                            
      ) = 0;

   //
   // Summary:
   //    Renders a sequence of nonindexed, geometric primitives of the specified 
   //    type from the current set of data input streams.
   // Return Value:
   //    - MV_NOERROR, if the method succeeds.
   //    - MV_E_INVALID_CALL, if the method fails.
   // Remarks:
   //    - IMvFlex3DDevice::DrawPrimitive should not be called with a single triangle at a time.
   //    - When using the legacy fixed function 3D pipeline, you must add a call to 
   //    - IMvFlex3DDevice::SetFVF before you make any Draw calls.
   //
   virtual HRESULT __stdcall DrawPrimitive (
      EMvPrimitiveType in_ePrimitiveType,    // Member of the #EMvPrimitiveType enumerated type, describing the type
                                                // of primitive to render.
      unsigned int      in_uiStartVertex,    // Index of the first vertex to load. Beginning at in_uiStartVertex 
                                                // the correct number of vertices will be read out of the vertex buffer.
      unsigned int      in_uiPrimitiveCount  // Number of primitives to render. The maximum number of primitives 
                                                // allowed is 2147483647.
                                                // in_uiPrimitiveCount is the number of primitives as determined by 
                                                // the primitive type. If it is a line list, each primitive has two 
                                                // vertices. If it is a triangle list, each primitive has three vertices.
      ) = 0;

   //
   // Summary:
   //    Renders data specified by a user memory pointer as a sequence of geometric 
   //    primitives of the specified type.
   // Return value:
   //    - MV_NOERROR, if the method succeeds.
   //    - MV_E_INVALID_CALL, if the method fails.
   // Remarks:
   //    - This method is intended for use in applications that are unable to store their vertex data 
   //          in vertex buffers. This method supports only a single vertex stream. The effect of this 
   //          call is to use the provided vertex data pointer and stride for vertex stream 0. It is 
   //          invalid to have the declaration of the current vertex shader refer to vertex streams other 
   //          than stream 0.
   //    - Following any IMvFlex3DDevice::DrawPrimitiveUP call, the stream 0 settings, referenced by 
   //          IMvFlex3DDevice::GetStreamSource, are set to NULL. 
   //
   virtual HRESULT __stdcall DrawPrimitiveUP(
      EMvPrimitiveType  in_ePrimitiveType,            // Member of the #EMvPrimitiveType enumerated type, describing the type 
                                                         // of primitive to render.
      unsigned int       in_uiPrimitiveCount,         // Number of primitives to render. The maximum number of primitives 
                                                         // allowed 2147483647.
      const void        *in_pkvVertexStreamZeroData,  // User memory pointer to vertex data to use for vertex stream 0.
      unsigned int       in_uiVertexStreamZeroStride  // Stride between data for each vertex, in bytes.
      ) = 0;

   //
   // Summary:
   //    Ends a scene that was begun by calling the IMvFlex3DDevice::BeginScene method.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method is called without first calling BeginScene().
   //
   //    - When this method succeeds, the scene has been queued up for rendering by the Matrox Flex 3D 
   //          Device driver. This is not a synchronous method, so the scene is not guaranteed to have 
   //          completed rendering when this method returns.
   // Remarks:
   //    - When scene rendering begins successfully, you must call this method before you can call 
   //          the IMvFlex3DDevice::BeginScene method to start rendering another scene. If a prior call 
   //          to IMvFlex3DDevice::BeginScene method fails, the scene did not begin and this method 
   //          should not be called.
   //
   virtual HRESULT __stdcall EndScene() = 0;

   //
   // Summary:
   //    Sends a special notification to the Matrox Flex 3D Device driver, that tells it that all Flex 3D calls made since 
   //    the last BeingEffect() call belonged to a single Flex 3D effect.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   // Remarks:
   //    - The Matrox Flex 3D Device driver implements surface synchronization by managing the synchronization objects 
   //          of all surfaces used by a specific effect. Hence, for proper effect sequencing, it is 
   //          imperative that every Flex 3D effect begins with a BeginSynchronizedAccess() and ends with 
   //          a EndSynchronizedAccess() call.
   //
   virtual HRESULT __stdcall EndSynchronizedAccess() = 0;

   //
   // Summary:
   //    Returns the amount of available graphic memory, in bytes.
   // Return Value:
   //    - The function returns the amount of available graphic memory, in bytes.
   //
   //    - Due to graphic memory management considerations, such as alignment, it might not be possible 
   //          to allocate a resource as big as the total available graphic memory. Hence, a graphic 
   //          memory allocation call may fail, even if the size of the resource to be allocated is 
   //          smaller than the value returned by this function.
   //
   virtual unsigned int __stdcall GetAvailableGraphicMemInBytes() = 0;

   //
   // Summary:
   //    Retrieves the coefficients of a user-defined clipping plane for the device.
   //
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if value in ui_inIndex exceeds the maximum clipping plane index supported 
   //         by the device, or if the array at out_pafPlane is not large enough to contain four 
   //         floating-point values
   // Remarks:
   //    - The coefficients that this method reports take the form of the general plane equation. If
   //          the values in the array at out_pafPlane were labeled A, B, C, and D in the order that they 
   //          appear in the array, they would fit into the general plane equation:
   //    - <B>Ax + By + Cz + Dw = 0</B>
   //    - A point with homogeneous coordinates (x, y, z, w) is visible in the half space of the plane 
   //          if Ax + By + Cz + Dw >= 0. Points that exist on or behind the clipping plane are clipped 
   //          from the scene.
   //    - The plane equation used by this method exists in world space and is set by a previous call 
   //          to the IMvFlex3DDevice::SetClipPlane method.
   //
   virtual HRESULT __stdcall GetClipPlane(
      unsigned long   in_ulIndex,   // Index of the clipping plane for which the plane equation coefficients 
                                       // are retrieved.
      float          *out_pafPlane  // Pointer to a four-element array of values that represent the coefficients 
                                       // of the clipping plane in the form of the general plane equation. See Remarks.
      ) = 0;

   //
   // Summary:
   //    Gets the depth-stencil surface currently associated with the IMvFlex3DDevice object.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   // Remarks:
   //    - Calling this method will increase the internal reference count on the IMvSurface interface. 
   //          Failure to call IUnknown::Release() when finished using this IMvSurface interface 
   //          results in a memory leak.
   //
   virtual HRESULT __stdcall GetDepthStencilSurface(IMvSurface **out_ppISurface  // Address of a pointer to an IMvSurface interface, representing 
                                                                                    // the returned depth-stencil surface.
      ) = 0;

   //
   // Summary:
   //    Retrieves the capabilities of the rendering device.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   // Remarks:
   //    - See \ref devicecaps for more details.
   //
   virtual HRESULT __stdcall GetDeviceCaps(SMvFlex3DCaps *out_psCaps // Pointer to a SMvfFlex3DCaps structure, describing the device.
      ) = 0;

   //
   // Summary:
   //    Get the fixed vertex function declaration.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall GetFVF(unsigned long *out_pulFVF  // A unsigned long pointer to the fixed function vertex type.
      ) = 0;

   //
   // Summary:
   //    Retrieves index data.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   // Remarks:
   //    - Calling this method will increase the internal reference count on the IMvFlex3DIndexBuffer 
   //          interface. Failure to call IUnknown::Release when finished using this IMvFlex3DIndexBuffer 
   //          interface results in a memory leak.
   //
   virtual HRESULT __stdcall GetIndices(IMvFlex3DIndexBuffer **out_ppIIndexData  // Address of a pointer to an IMvFlex3DIndexBuffer 
                                                                                    // interface, representing the returned index data.
      ) = 0;

   //
   // Summary:
   //    Retrieves a set of lighting properties that this device uses.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall GetLight (
      unsigned long   in_ulIndex,   // Zero-based index of the lighting property set to retrieve. This method will 
                                       // fail if a lighting property has not been set for this index by calling 
                                       // the IMvFlex3DDevice::SetLight method.
      SMvLight      *out_psLight    // Pointer to a SMvfLight structure that is filled with the retrieved 
                                       // lighting-parameter set.
      ) = 0;


   //
   // Summary:
   //    Retrieves the activity status (enabled or disabled) for a set of lighting parameters within 
   //    the Flex 3D device.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall GetLightEnable (
      unsigned long   in_ulIndex,   // Zero-based index of the set of lighting parameters that are the target of 
                                       // this method.
      bool           *out_pbEnable  // Pointer to a boolean variable to fill with the status of the 
                                       // specified lighting parameters. After the call, a nonzero value at this address 
                                       // indicates that the specified lighting parameters are enabled; a value of 0 
                                       // indicates that they are disabled.
      ) = 0;

   //
   // Summary:
   //    Retrieves the current material properties for the device.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall GetMaterial(SMvMaterial *out_psMaterial // Pointer to a SMvfMaterial structure to fill with the 
                                                                     // currently set material properties.
      ) = 0;

   //
   // Summary:
   //    Retrieves the currently set pixel shader.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall GetPixelShader(IMvFlex3DPixelShader **out_ppIPixelShader  // Pointer to a pixel shader interface.
      ) = 0;

   //
   // Summary:
   //    Get a floating-point shader constant.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall GetPixelShaderConstantF (
      unsigned int    in_uiStartRegister, // Register number that will contain the first constant value.
      float          *out_pfConstantData, // Pointer to an array of constants.
      unsigned int    in_uiVector4fCount  // Number of four float vectors in the array of constants.
      ) = 0;

   //
   // Summary:
   //    Retrieves a render-state value for the Flex 3D device.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall GetRenderState (
      EMvRenderStateType   in_eState,     // Device state variable that is being queried. This parameter can be any member 
                                             // of the EMvRenderStateType enumerated type.
      unsigned long        *out_pulValue  // Pointer to a variable that receives the value of the queried 
                                             // render state variable when the method returns.
      ) = 0;

   //
   // Summary:
   //    Retrieves the current render target surface.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //    - MV_E_NOT_FOUND if there's no render target available for the given index.
   // Remarks:
   //    - Calling this method will increase the internal reference count on the IMvSurface 
   //          interface. Failure to call IUnknown::Release() when finished using this IMvSurface 
   //          interface results in a memory leak.
   //
   virtual HRESULT __stdcall GetRenderTarget(IMvSurface    **out_ppIRenderTarget // Address of a pointer to an IMvSurface interface, 
                                                                                    // representing the returned render target surface for this device.
      ) = 0;

   //
   // Summary:
   //    Retrieves a sampler-state value for a sampler.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall GetSamplerState(
      unsigned long         in_ulSampler, // The sampler stage index.
      EMvSamplerStateType  in_eType,      // This parameter can be any member of the EMvSamplerStateType enumerated type.
      unsigned long        *out_pulValue  // State value to get. The meaning of this value is determined by the 
                                             // in_eType parameter.
      ) = 0;

   //
   // Summary:
   //    Get the scissor rectangle, used as 2D rectangular clipping region.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall GetScissorRect(const RECT *out_pkrcScissor // Returns a pointer to the RECT structure, which defines the rendering 
   // area within the render target if scissor test is enabled.
      ) = 0;

   //
   // Summary:
   //    Retrieves a vertex buffer bound to the specified data stream.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   // Remarks:
   //    - Calling this method will increase the internal reference count on the IMvFlex3DVertexBuffer 
   //          interface. Failure to call IUnknown::Release() when finished using this 
   //          IMvFlex3DVertexBuffer interface results in a memory leak.
   //
   virtual HRESULT __stdcall GetStreamSource(
      unsigned int              in_uiStreamNumber,    // Specifies the data stream, in the range from 0 to the maximum 
                                                         // number of streams minus one. 
      IMvFlex3DVertexBuffer  **out_ppIStreamData,     // Address of a pointer to the returned vertex buffer bound to the 
                                                         // specified data stream. 
      unsigned int             *out_puiOffsetInBytes, // Pointer containing the offset from the beginning of the stream to 
                                                         // the beginning of the vertex data. The offset is measured in bytes. 
                                                         // See Remarks. 
      unsigned int             *out_puiStride         // Pointer to a returned stride of the component, in bytes. See Remarks.
      ) = 0;

   //
   // Summary:
   //    Retrieves the surface assigned as texture for a stage of the Flex 3D device.
   //
   // \param in_ulStage [in] 
   // \param out_ppITexture [out, retval] 
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   // Remarks:
   //    - Calling this method will increase the internal reference count on the IMvSurface interface. 
   //
   virtual HRESULT __stdcall GetTexture(
      unsigned long    in_ulStage,     // Stage identifier of the texture to retrieve. Stage identifiers are zero-based. 
                                          // The Flex 3D device can have up to eight set textures, so the maximum value allowed 
                                          // for in_ulStage is 7.
      IMvSurface    **out_ppITexture   // Address of a pointer to an IMvSurface interface, representing 
                                          // the returned texture.
      ) = 0;

   //
   // Summary:
   //    Retrieves a state value for an assigned texture.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall GetTextureStageState (
      unsigned long              in_ulStage,    // Stage identifier of the texture for which the state is retrieved. Stage 
                                                   // identifiers are zero-based. The Flex 3D Device can have up to eight set textures, 
                                                   // so the maximum value allowed for in_ulStage is 7.
      EMvTextureStageStateType  in_eType,       // Texture state to retrieve. This parameter can be any member of the 
                                                   // EMvTextureStageStateType enumerated type.
      unsigned long             *out_pulValue   // Pointer a variable to fill with the retrieved state value. 
                                                   // The meaning of the retrieved value is determined by the in_eType parameter.
      ) = 0;

   //
   // Summary:
   //    Retrieves a single device transformation-related state.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   // Remarks:
   //    Even if more than one world matrix can be set on the device, only the first world matrix 
   //          can be retrived by GetTransform().
   //
   virtual HRESULT __stdcall GetTransform (
      EMvTransformStateType   in_eState,     // Transform state variable that is being modified. This parameter can be any 
                                                // member of the EMvTransformStateType enumerated type.
      SMvMatrix              *out_psMatrix   // Pointer to a SMvfMatrix structure, describing the returned transform state.
      ) = 0;

   //
   // Summary:
   //    Get a vertex shader declaration. 
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall GetVertexDeclaration(IMvFlex3DVertexDeclaration **out_ppIDecl   // Pointer to an IMvFlex3DVertexDeclaration object that is returned.
      ) = 0;

   //
   // Summary:
   //    Retrieves the currently set vertex shader.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall GetVertexShader(IMvFlex3DVertexShader  **out_ppIVertexShader // Pointer to a vertex shader interface.
      ) = 0;

   //
   // Summary:
   //    Get a floating-point shader constant.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall GetVertexShaderConstantF(
      unsigned int    in_uiStartRegister, // Register number that will contain the first constant value.
      float          *out_pfConstantData, // Pointer to an array of constants.
      unsigned int    in_uiVector4fCount  // Number of four float vectors in the array of constants.
      ) = 0;

   //
   // Summary:
   //    Retrieves the viewport parameters currently set for the device.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall GetViewport(SMvViewport *out_psViewport // Pointer to a SMvfViewport structure, representing the returned viewport.
      ) = 0;

   //
   // Summary:
   //    Enables or disables a set of lighting parameters within a device.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   // Remarks:
   //    - If the value in in_ulLightIndex is outside the range of the light property sets assigned
   //          within the device, the LightEnable creates a white directional light source located at 
   //          the origin and pointing at (0,0,1).
   //
   virtual HRESULT __stdcall LightEnable(
      unsigned long  in_ulLightIndex,  // Zero-based index of the set of lighting parameters that are the 
                                          // target of this method.
      bool           in_bEnable        // Value that indicates if the set of lighting parameters are being 
                                          // enabled or disabled. Set this parameter to true to enable lighting with 
                                          // the parameters at the specified index, or false to disable it.
      ) = 0;


   //
   // Summary:
   //    Multiplies a device's world, view, or projection matrix by a specified matrix.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   // Remarks:
   //    - The multiplication order is in_pksMatrix times in_eState.
   //    - After using this call, the matrix returned by GetTransform will not be valid.
   //
   virtual HRESULT __stdcall MultiplyTransform(
      EMvTransformStateType   in_eState,     // Identifies which device matrix is to be modified.
      const SMvMatrix        *in_pksMatrix   // Pointer to a SMvfMatrix structure that modifies the current transformation.
      ) = 0;

   //
   // Summary:
   //    Starts the rendering.  This method must be called when all the commands have been sent to the 
   //    Flex 3D Device.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   // Remarks:
   //    - When in_bResolveFragmentBuffer is set to TRUE, the drawing engine will look at its fragment
   //          buffer and will resolve them all.   To enable the collection of fragments, the render 
   //          state keMvRSAAFragmentCollectEnable must be set to TRUE.
   //
   virtual HRESULT __stdcall Present(bool in_bResolveFragmentBuffer  // in_bResolveFragmentBuffer Must be set to TRUE to enable the fragment antialiasing.  See remarks.
      ) = 0;

   //
   // Summary:
   //    Generates all texture sublevels down to 1 x 1 pixels.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall RenderMipmaps(
      EMvFaceType    in_eFaceType,  // Face to which mipmap generation is requested. Must be keMvfFaceTypeFront 
                                       // unless mipmap generation is required for a face of a cube. 
      IMvSurface    *io_pISurface   // Pointer to the interface of the surface for which mipmaps are 
                                       // to be generated.
      ) = 0;

   //
   // Summary:
   //    Sets the coefficients of a user-defined clipping plane for the device.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the value in in_ulIndex exceeds the maximum clipping plane index 
   //         supported by the device or that the array at in_pkafPlane is not large enough to contain 
   //         four floating-point values.
   // Remarks:
   //    - The coefficients that this method sets take the form of the general plane equation. If the 
   //          values in the array at in_pkafPlane were labeled A, B, C, and D in the order that they 
   //          appear in the array, they would fit into the general plane equation:
   //    - <B>Ax + By + Cz + Dw = 0</B>
   //    - A point with homogeneous coordinates (x, y, z, w) is visible in the half space of the plane 
   //          if Ax + By + Cz + Dw >= 0. Points that exist behind the clipping plane are clipped 
   //          from the scene.
   //    - When the fixed function pipeline is used the plane equations are assumed to be in world 
   //          space. When the programmable pipeline is used the plane equations are assumed to be in 
   //          the clipping space (the same space as output vertices).
   //    - This method does not enable the clipping plane equation being set. To enable a clipping 
   //          plane, set the corresponding bit in the value applied to the keMvRSClipPlaneEnable 
   //          render state.
   //
   virtual HRESULT __stdcall SetClipPlane(
      unsigned long   in_ulIndex,   // Index of the clipping plane for which the plane equation coefficients are 
                                       // to be set.
      const float    *in_pkafPlane  // Pointer to an address of a four-element array of values that represent 
                                       // the clipping plane coefficients to be set, in the form of the general plane 
                                       // equation. See Remarks.
      ) = 0;

   //
   // Sumary:
   //    Sets all the default render states, texture stage states and sampler states.
   // Return value: 
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall SetDefaultStates() = 0; 

   //
   // Summary:
   //    Sets the depth stencil surface.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall SetDepthStencilSurface(IMvSurface *in_pISurface  // Address of a pointer to an IMvSurface interface, representing the depth 
                                                                                 // stencil surface. Setting this to NULL disables the depth stencil operation and 
                                                                                 // releases the previous depth stencil buffer.
      ) = 0;

   //
   // Summary:
   //    Set the current vertex stream declaration.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall SetFVF(unsigned long in_ulFVF  // A unsigned long containing the fixed function vertex type.
      ) = 0;

   //
   // Summary:
   //    Sets index data to be used to index the device streams
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall SetIndices(IMvFlex3DIndexBuffer  *in_pIIndexData // Pointer to an IMvFlex3DIndexBuffer interface, representing the 
                                                                                 // index data to be set.
      ) = 0;

   //
   // Summary:
   //    Assigns a set of lighting properties for the Flex 3D device.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall SetLight(
      unsigned long      in_ulIndex,   // Zero-based index of the set of lighting properties to set. If a set of 
                                          // lighting properties exists at this index, it is overwritten by the new properties 
                                          // specified in in_psLight.
      const SMvLight   *in_psLight     // Pointer to a SMvfLight structure, containing the lighting parameters to set.
      ) = 0;

   //
   // Summary:
   //    Sets the material properties for the device.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall SetMaterial(const SMvMaterial *in_pksMaterial // Pointer to a SMvfMaterial structure, describing the material properties to set.
      ) = 0;

   //
   // Summary:
   //    Sets the current pixel shader to a previously created pixel shader.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall SetPixelShader(IMvFlex3DPixelShader *in_pIPixelShader  // Pixel shader interface to set as active pixel shader.
      ) = 0;

   //
   // Summary:
   //    Set a floating-point shader constant.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall SetPixelShaderConstantF(
      unsigned int    in_uiStartRegister, // Register number that will contain the first constant value. 
      const float    *in_pkfConstantData, // Pointer to an array of constants. 
      unsigned int    in_uiVector4fCount  // Number of four float vectors in the array of constants.
      ) = 0;

   //
   // Summary:
   //    Sets a single device render-state parameter.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall SetRenderState(
      EMvRenderStateType  in_eState,   // Device state variable that is being modified. This parameter can be any 
                                          // member of the EMvRenderStateType enumerated type.
      unsigned long        in_ulValue  // New value for the device render state to be set. The meaning of this 
                                          // parameter is dependent on the value specified for in_eState.
      ) = 0;

   //
   // Summary:
   //    Sets a new color buffer for the device to use as destination for rendering.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   // Remarks:
   //    - The IMvSurface must have been created as a render target, i.e. that the surface 
   //          EMvMemoryLocation must be EMvMemoryLocationGraphicOut or EMvMemoryLocationGraphic.  
   //          The surface format must be EMvSurfaceFormatARGB, EMvSurfaceFormatRGB or
   //          EMvSurfaceFormatAVYU444.
   //    - <B>Calling Present() without first calling at least once SetRenderState will put the Flex
   //          3D Device in an unstable an unusable state.</B>
   //
   virtual HRESULT __stdcall SetRenderTarget(
      unsigned long   in_ulMipmapLevel,   // Mipmap level to set as render target. Should be zero unless rendering 
                                             // to a specific mipmap level is required.
      EMvFaceType    in_eFaceType,        // Face desired. Should be keMvfFaceFront unless a specific face of 
                                             // a cube is required.
      IMvSurface    *in_pISurface         // Pointer to a new color buffer. If NULL, the existing color buffer is 
                                             // retained. If this parameter is other than NULL, the reference count on the new 
                                             // render target is incremented. The Flex 3D device must always be associated with 
                                             // a color buffer.
      ) = 0;

   //
   // Summary:
   //    Sets the sampler state value.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall SetSamplerState(
      unsigned long        in_ulSampler,  // The sampler stage index.
      EMvSamplerStateType in_eType,       // This parameter can be any member of the EMvSamplerStateType enumerated type.
      unsigned long        in_ulValue     // State value to set. The meaning of this value is determined by the 
                                             // in_eType parameter.
      ) = 0;

   //
   // Summary:
   //    Set the scissor rectangle to be used as a 2D rectangular clipping region.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall SetScissorRect(const RECT    *in_pkrcScissor  // Pointer to a RECT structure that defines the rendering area 
                                                                              // within the render target if scissor test is enabled.
      ) = 0;

   //
   // Summary:
   //    Binds a vertex buffer to a device data stream.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   // Remarks:
   //    - When a flexible vertex format (FVF) vertex shader is used, the stride of the vertex stream 
   //          must match the vertex size, computed from the FVF. When a declaration is used, the stride 
   //          should be greater than or equal to the stream size computed from the declaration.
   //    - When an application no longer holds a reference to this interface, the interface will 
   //          automatically be freed.
   //
   virtual HRESULT __stdcall SetStreamSource(
      unsigned int             in_uiStreamNumber,  // Specifies the data stream, in the range from 0 to the maximum number 
                                                      // of streams -1.
      IMvFlex3DVertexBuffer  *in_pIStreamData,     // Pointer to an vertex buffer to bind to the specified data stream. 
      unsigned int             in_uiOffsetInBytes, // Offset from the beginning of the stream to the beginning of 
                                                      // the vertex data, in bytes. 
      unsigned int             in_uiStride         // Stride of the component, in bytes. See Remarks.
      ) = 0;

   //
   // Summary:
   //    Assigns a texture to a stage for the Flex 3D device.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall SetTexture(
      unsigned long   in_ulStage,   // Stage identifier to which the texture is set. Stage identifiers are 
                                       // zero-based. The Flex 3D device can have up to eight textures, so the maximum 
                                       // value allowed for in_ulStage is 7.
      IMvSurface    *in_pITexture   // Pointer to an IMvSurface interface, representing the texture being set. 
                                       // For complex textures, such as mipmaps and cube textures, this parameter must 
                                       // point to the top-level surface.
      ) = 0;


   //
   // Summary:
   //    Sets the state value for the currently assigned texture.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall SetTextureStageState(
      unsigned long              in_ulStage, // Stage identifier of the texture for which the state value is set. Stage 
                                                // identifiers are zero-based. The Flex 3D device can have up to eight set textures, 
                                                // so the maximum value allowed for in_ulStage is 7.
      EMvTextureStageStateType  in_eType,    // Texture state to set. This parameter can be any member of the 
                                                // EMvTextureStageStateType enumerated type.
      unsigned long              in_ulValue  // State value to set. The meaning of this value is determined by the in_eType 
                                                 // parameter.
      ) = 0;

   //
   // Summary:
   //    Sets a single device transformation-related state.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall SetTransform(
      EMvTransformStateType   in_eState,     // Device-state variable that is being modified.
      const SMvMatrix        *in_pksMatrix   // Pointer to a SMvfMatrix structure that modifies the current transformation.
      ) = 0;

   //
   // Summary:
   //    Set a vertex shader declaration.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall SetVertexDeclaration(IMvFlex3DVertexDeclaration *in_pIVertexDecl   // Pointer to a vertex declaration object, which contains the vertex declaration.
      ) = 0;

   //
   // Summary:
   //    Sets a vertex shader.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   // Remarks:
   //    - To set a fixed-function vertex shader (after having set a programmable vertex shader), call 
   //          IMvFlex3DDevice::SetVertexShader(NULL) to release the programmable shader, and then call 
   //          IMvFlex3DDevice::SetFVF with the fixed-function vertex format.
   //
   virtual HRESULT __stdcall SetVertexShader(IMvFlex3DVertexShader *in_pIVertexShader  // Vertex shader interface
      ) = 0;

   //
   // Summary:
   //    Set a floating-point shader constant.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall SetVertexShaderConstantF(
      unsigned int    in_uiStartRegister, // Register number that will contain the first constant value. 
      const float    *in_pkfConstantData, // Pointer to an array of constants.
      unsigned int    in_uiVector4fCount  // Number of four float vectors in the array of constants.
      ) = 0;

   //
   // Summary:
   //    Sets the viewport parameters for the device.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if in_pksViewport is invalid, or if in_pksViewport describes a region 
   //         that cannot exist within the render target surface.
   //
   virtual HRESULT __stdcall SetViewport(const SMvViewport *in_pksViewport // Pointer to a SMvfViewport structure, specifying the viewport to set.
      ) = 0;

   //
   // Summary:
   //    Reports the device's ability to render the current texture-blending operations and arguments 
   //    in a single pass.
   //
   // \param out_pulNumPasses [out, retval] Pointer to a value to fill with the number of rendering 
   //                         passes needed to complete the desired effect through multipass rendering.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_CONFLICTINGTEXTUREFILTER
   //    - MV_E_TOOMANYOPERATIONS
   //    - MV_E_UNSUPPORTEDALPHAARG
   //    - MV_E_UNSUPPORTEDALPHAOPERATION
   //    - MV_E_UNSUPPORTEDCOLORARG
   //    - MV_E_UNSUPPORTEDCOLOROPERATION
   //    - MV_E_UNSUPPORTEDFACTORVALUE
   //    - MV_E_UNSUPPORTEDTEXTUREFILTER
   //    - MV_E_WRONGTEXTUREFORMAT
   // 
   // Remarks:
   //    - The IMvFlex3DDevice::ValidateDevice method uses the current render states, textures, and 
   //       texture-stage states to perform validation at the time of the call. Changes to these 
   //       factors after the call invalidate the previous result, and the method must be called again 
   //       before rendering a scene.
   //
   virtual HRESULT __stdcall ValidateDevice(unsigned long *out_pulNumPasses) = 0;

   //
   // Summary:
   //    Copies one surface to another, using a write mask.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall CopySurfaceMask(
      IMvSurface             *in_pISurfaceSource,        // Source surface.
      const SMvRect          *in_pkrcSource,             // Region of the source to copy.  Can be set to NULL to use the whole surface.
      IMvSurface             *in_pISurfaceDestination,   // Destination surface.
      const SMvRect          *in_pkrcDestination,        // Region in the destination surface that will receive the data.  Can be 
                                                            // set to NULL to use the whole surface.
      const SMvMask           in_ksColorWriteMask,       // Color write mask.
      EMvFilterMode           in_eFilterMode             // Filter mode, must be set to EMvFilterMode::keMvFilterModeNormal.
      ) = 0;


   //
   // Summary:
   //    Retrieves the interface IMvFlex3DHelpers
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall GetHelpers(IMvFlex3DHelpers** out_ppIHelpers  // Helpers object.
      ) = 0;

   
   //
   // Summary:
   //    Tries to reset the device after a device_lost error message.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_DEVICE_IS_LOST if the device cannot be reset at this time.
   //    - MV_E_DEVICE_IS_LOST_CRITICAL if the device is critically dead.  
   //
   virtual HRESULT __stdcall ResetDevice() = 0;
};

//////////////////////////////////////////////////////////////////////////
//
//
// Summary:
//    Effects helpers.
//    This interface helps the user to handle correctly the surfaces and provides 
//    methods that are used often.  This is a toolbox for the user.  This interface
//    must be released when it is not needed anymore.
//
// 
//
//////////////////////////////////////////////////////////////////////////
interface IMvFlex3DHelpers : public IUnknown
{
   //
   // Summary:
   //    This method sets the surface that will be considered as the texture for the computations.
   // 
   // \param in_pISurface 
   // \param in_psSurfaceDescription 
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall SetTexture(      
      IMvSurface*            in_pISurface,            // Texture that will be used for the computations, until changed.
      SMvSurfaceDescription* in_psSurfaceDescription  // Surface description of the texture.  If set to NULL, the method will do a GetSurfaceDescription, 
                                                         // so this parameter is optional.  It is, in fact, provided only as a potential optimization, 
                                                         // if the effect itself already had to do a GetSurfaceDescription.
      ) = 0;

   //
   // Summary:
   //    This method sets the surface that will be considered as the rendertarget for the computations.
   // Return Value: 
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall SetRenderTarget(      
      IMvSurface*            in_pISurface,            // Rendertarget that will be used for the computations, until changed.
      SMvSurfaceDescription* in_psSurfaceDescription  // Surface description of the rendertarget.  If set to NULL, the method 
                                                         // will do a GetSurfaceDescription, so this parameter is optional.  
                                                         // It is, in fact, provided only as a potential optimization, if the 
                                                         // effect itself already had to do a GetSurfaceDescription.
      ) = 0;

   //
   // Summary:
   //    Adjust the texel centering.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall SetTexelCentering(
      float in_fTexelCenterU, // U adjustment (default 0.5).
      float in_fTexelCenterV  // V adjustment (default 0.5).
      ) = 0;

   //
   // Summary:
   //    This method computes the U,V compensations that need to be applied to the mesh to avoid 
   //    field-inversion when rendering the texture (set by SetTexture) to the rendertarget 
   //    (set by SetRenderTarget).  We offer different versions of this method, depending of what
   //    information the user has.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall ComputeCompensation( 
      CMvMatrix*           in_poTransformMatrix,   // Transform Matrix
      float*               out_pfCompensateValueU, // U compensation.
      float*               out_pfCompensateValueV  // V compensation.
      ) = 0;

   virtual HRESULT __stdcall ComputeCompensation( 
      CMvVector3*          in_poHead,              // Vector indicating the orientation of the texture (point toward "up").
      CMvVector3*          in_poEnd,               // Origin of the head vector.
      CMvVector3*          in_poNormal,            // Normal of the surface that will receive the texture.
      CMvMatrix*           in_poTransformMatrix,   // Transform Matrix
      float*               out_pfCompensateValueU, // U compensation.
      float*               out_pfCompensateValueV  // V compensation.
      ) = 0;

   virtual HRESULT __stdcall ComputeCompensation(
      CMvVector3*         in_poHead,               // Vector indicating the orientation of the texture (point toward "up").
      bool                in_bIsSurfaceInverted,   // True if the surface that receive the texture is upside-down.
      float*              out_pfCompensateValueU,  // U compensation.
      float*              out_pfCompensateValueV   // V compensation.
      ) = 0;

   //
   // Summary:
   //    This method computes the mesh width, the mesh height and the compensation matrix that need
   //    to be used to render full screen the texture (set by SetTexture) to the rendertarget 
   //    (set by SetRenderTarget), using pretransformed vertices (XYZW).
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall ComputePretransformedMeshProperties(
      SMvRectF*              in_psCrop,            // Cropping information.
      int                    in_bConsumePosition,  // If set to true, consume the position from the texture (set by SetTexture): 
                                                      // the mesh will be translated by the good amount of pixel.  If set to false, 
                                                      // it propagate the position information to the rendertarget (set by SetRenderTarget).
      SMvRectF*              out_psMeshAttributes  // Left, right, top, bottom coordinates of the mesh in pretransformed space.
      ) = 0;

   //
   // Summary:
   //    This method computes the mesh width, the mesh height and the compensation matrix that need
   //    to be used to render full screen the texture (set by SetTexture) to the rendertarget 
   //    (set by SetRenderTarget), using untransformed vertices (XYZ).
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall ComputeUntransformedMeshProperties(
      SMvRectF*              in_psCrop,                  // Cropping information.
      int                    in_bConsumePosition,        // If set to true, consume the position from the texture (set by SetTexture): the mesh 
                                                            // will be translated by the good amount of pixel.  If set to false, it propagate 
                                                            // the position information to the rendertarget (set by SetRenderTarget).
      float*                 out_pfMeshWidth,            // Width of the mesh.
      float*                 out_pfMeshHeight,           // Height of the mesh.
      CMvMatrix*             out_poFinalAdjustmentMatrix // Adjustement matrix.  Must be used with the world matrix.
      ) = 0;

   //
   // Summary:
   //    This method computes the usable region of the texture (set by SetTexture), taking into 
   //    account the allocated dimension of the surface, the requested dimension of the surface 
   //    and the cropping information.  This method should always be used, even when no cropping is needed.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall ComputeUsableRegion( 
      SMvRectF*       in_psCrop,          // Cropping information.
      SMvRectF*       out_psUsableRegion  // Usable region of the texture (uv coordinates).
      ) = 0;

   //
   // Summary:
   //    This method computes the U coordinate associated to a X position for a 
   //    given mesh width and usable region.
   // Return value:
   //    - U coordinate.
   //
   virtual float __stdcall FindU( 
      float      in_fx,             // X position.
      SMvRectF  *in_psUsableRegion, // Usable region of the texture.
      float      in_fMeshWidth      // Total width of the texture.
      ) = 0;

   //
   // Summary:
   //    This method computes the V coordinate associated to a Y position for a 
   //    given mesh height and usable region.
   // Return value:
   //    - V coordinate.
   //
   virtual float __stdcall FindV( 
      float      in_fy,             // Y position.
      SMvRectF  *in_psUsableRegion, // Usable region of the texture.
      float      in_fMeshHeight     // Total width of the texture.
      ) = 0;

   //
   // Summary:
   //    This method fills the unusable region of the texture (set by SetTexture) by repeating
   //    the border line/column of the usable region.
   // Return value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall FillUnusableRegion(      
      SMvRectF*      in_psCrop,              // Crop area of the texture.
      unsigned long  in_ulNbPixelsToRepeat   // Number of time that we must repeat the border pixel.
      ) = 0;

   //
   // Summary:
   //    This method releases the texture (set by SetTexture) and the rendertarget 
   //    (set by SetRenderTarget), and reset the texel centering.
   // 
   //
   virtual void __stdcall Reset() = 0;

   
   //
   // Summary:
   //    This method checks the parameters that the effect received and validates them all.  It will 
   //    check that the surfaces are in the good memory location and that they are compatibles.  It will 
   //    check if the number of patterns received is correct. Use this method to validate the parameter 
   //    you received in your UpstreamFilter method.
   // Return Value:
   //    - MV_NOERROR, if everything is correct.
   //    - MV_E_NO_INPUT_SURFACE if no input surfaces are present and the effect needs a least one surface.
   //    - MV_E_NOT_ENOUGH_INPUT_SURFACES if there is not enough input surfaces.
   //    - MV_E_NO_INPUT_CONTAINER if no effect patterns are present and the effect needs a least one effect pattern. 
   //    - MV_E_NOT_ENOUGH_INPUT_CONTAINER if there is not enough effect patterns.
   //    - MV_E_INVALID_PARAMETER if one parameter has an invalid value.
   //    - MV_E_SURFACE_FORMAT_MISMATCH if the input surface format does not match the output surface format.
   //    - MV_E_OUTPUT_FORMAT_NOT_SUPPORTED if the output surface format is not supported.
   //    - MV_E_UNSUPPORTED_INPUT_WIDTH_HEIGHT if the input is larger than the editing resolution
   //
   //
   virtual HRESULT __stdcall UpstreamFilterValidation(
      SMvEffectCapabilities *in_psCapabilities,                   // Capabilities of the effect. 
      IMvSurface            *in_apIInputSurface[],                // Array of input surfaces.
      unsigned long          in_ulNbInputSurface,                 // Number of surfaces in in_apIInputSurface.
      unsigned long          in_ulMinNbInputSurfaceNeeded,        // Minimum number of input surfaces needed for this effect.
      IMvSurface            *in_apIEffectPatternSurface[],        // Array of effect pattern surfaces.
      unsigned long          in_ulNbEffectPatternSurface,         // Number of surfaces in in_apIEffectPatternSurface.
      unsigned long          in_ulMinNbEffectPatternSurfaceNeeded,// Minimum number of effect pattern surfaces needed for this effect.
      IMvSurface            *in_pIOutputSurface,                  // Output surface.
      IMvEffectSettings     *in_pIEffectSettings                  // Effect settings.
      ) = 0;            

   //
   // Summary:
   //    This method checks the parameters that the effect received and validates them all.  It will 
   //    check that the surfaces are in the good memory location and that they are compatibles.  It will 
   //    check if the number of patterns received is correct. Use this method to validate the parameter 
   //    you received in your DownstreamFilter method.
   // Return Value:
   //    - MV_NOERROR, if everything is correct.
   //    - MV_E_NO_INPUT_SURFACE if no input surfaces are present and the effect needs a least one surface.
   //    - MV_E_NOT_ENOUGH_INPUT_SURFACES if there is not enough input surfaces.
   //    - MV_E_NO_INPUT_CONTAINER if no effect patterns are present and the effect needs a least one effect pattern. 
   //    - MV_E_NOT_ENOUGH_INPUT_CONTAINER if there is not enough effect patterns.
   //    - MV_E_INVALID_PARAMETER if one parameter has an invalid value.
   //    - MV_E_SURFACE_FORMAT_MISMATCH if the input surface format does not match the output surface format.
   //    - MV_E_OUTPUT_FORMAT_NOT_SUPPORTED if the output surface format is not supported.
   //    - MV_E_UNSUPPORTED_INPUT_WIDTH_HEIGHT if the input is larger than the editing resolution
   //
   //
   virtual HRESULT __stdcall DownstreamFilterValidation(
      SMvEffectCapabilities *in_psCapabilities,                   // Capabilities of the effect.
      IMvSurface            *in_apIInputSurface[],                // Array of input surfaces.
      unsigned long          in_ulNbInputSurface,                 // Number of surfaces in in_apIInputSurface.
      unsigned long          in_ulMinNbInputSurfaceNeeded,        // Minimum number of input surfaces needed for this effect.
      IMvSurface            *in_apIEffectPatternSurface[],        // Array of effect pattern surfaces.
      unsigned long          in_ulNbEffectPatternSurface,         // Number of surfaces in in_apIEffectPatternSurface.
      unsigned long          in_ulMinNbEffectPatternSurfaceNeeded,// Minimum number of effect pattern surfaces needed for this effect.
      IMvSurface            *in_pIBackgroundSurface,              // Background surface.
      EMvBackgroundHandling  in_eBackgroundHandling,              // Background handling mode.
      IMvSurface            *in_pIOutputSurface,                  // Output surface.
      IMvEffectSettings     *in_pIEffectSettings                  // Effect settings.
      ) = 0;

   //
   // Summary:
   //    This method checks the parameters that the effect received and validates them all.  It will 
   //    check that the surfaces are in the good memory location and that they are compatibles.  It will 
   //    check if the number of patterns received is correct. Use this method to validate the parameter 
   //    you received in your UpstreamTransition method.
   // Return Value:
   //    - MV_NOERROR, if everything is correct.
   //    - MV_E_NO_INPUT_SURFACE if no input surfaces are present and the effect needs a least one surface.
   //    - MV_E_NOT_ENOUGH_INPUT_SURFACES if there is not enough input surfaces.
   //    - MV_E_NO_INPUT_CONTAINER if no effect patterns are present and the effect needs a least one effect pattern. 
   //    - MV_E_NOT_ENOUGH_INPUT_CONTAINER if there is not enough effect patterns.
   //    - MV_E_INVALID_PARAMETER if one parameter has an invalid value.
   //    - MV_E_SURFACE_FORMAT_MISMATCH if the input surface format does not match the output surface format.
   //    - MV_E_OUTPUT_FORMAT_NOT_SUPPORTED if the output surface format is not supported.
   //    - MV_E_UNSUPPORTED_INPUT1_WIDTH_HEIGHT if the input 1 is larger than the editing resolution
   //    - MV_E_UNSUPPORTED_INPUT2_WIDTH_HEIGHT if the input 2 is larger than the edition resolution
   //
   virtual HRESULT __stdcall UpstreamTransitionValidation(
      SMvEffectCapabilities *in_psCapabilities,                   // Capabilities of the effect.
      IMvSurface            *in_pIInputSurfaceA,                  // Surface A of the transition.
      IMvSurface            *in_pIInputSurfaceB,                  // Surface B of the transition.
      IMvSurface            *in_apIEffectPatternSurface[],        // Array of effect pattern surfaces.
      unsigned long          in_ulNbEffectPatternSurface,         // Number of surfaces in in_apIEffectPatternSurface.
      unsigned long          in_ulMinNbEffectPatternSurfaceNeeded,// Minimum number of effect pattern surfaces needed for this effect.
      IMvSurface            *in_pIOutputSurface,                  // Output surface.
      IMvEffectSettings     *in_pIEffectSettings                  // Effect settings.
      ) = 0;

   //
   // Summary:
   //    This method checks the parameters that the effect received and validates them all.  It will 
   //    check that the surfaces are in the good memory location and that they are compatibles.  It will 
   //    check if the number of patterns received is correct. Use this method to validate the parameter 
   //    you received in your DownstreamTransition method.
   // Return Value:
   //   - MV_NOERROR, if everything is correct.
   //   - MV_E_NO_INPUT_SURFACE if no input surfaces are present and the effect needs a least one surface.
   //   - MV_E_NOT_ENOUGH_INPUT_SURFACES if there is not enough input surfaces.
   //   - MV_E_NO_INPUT_CONTAINER if no effect patterns are present and the effect needs a least one effect pattern. 
   //   - MV_E_NOT_ENOUGH_INPUT_CONTAINER if there is not enough effect patterns.
   //   - MV_E_INVALID_PARAMETER if one parameter has an invalid value.
   //   - MV_E_SURFACE_FORMAT_MISMATCH if the input surface format does not match the output surface format.
   //   - MV_E_OUTPUT_FORMAT_NOT_SUPPORTED if the output surface format is not supported.
   //   - MV_E_UNSUPPORTED_INPUT1_WIDTH_HEIGHT if the input 1 is larger than the editing resolution
   //   - MV_E_UNSUPPORTED_INPUT2_WIDTH_HEIGHT if the input 2 is larger than the editing resolution
   // 
   //
   virtual HRESULT __stdcall DownstreamTransitionValidation(
      SMvEffectCapabilities *in_psCapabilities,                   // Capabilities of the effect.
      IMvSurface            *in_pIInputSurfaceA,                  // Surface A of the transition.
      IMvSurface            *in_pIInputSurfaceB,                  // Surface B of the transition.
      IMvSurface            *in_apIEffectPatternSurface[],        // Array of effect pattern surfaces. 
      unsigned long          in_ulNbEffectPatternSurface,         // Number of surfaces in in_apIEffectPatternSurface.
      unsigned long          in_ulMinNbEffectPatternSurfaceNeeded,// Minimum number of effect pattern surfaces needed for this effect.
      IMvSurface            *in_pIBackgroundSurface,              // Background surface.
      EMvBackgroundHandling  in_eBackgroundHandling,              // Background handling mode.
      IMvSurface            *in_pIOutputSurface,                  // Output surface.
      IMvEffectSettings     *in_pIEffectSettings                  // Effect settings.
      ) = 0;

   //
   // Summary:
   //    This method will set the synchro correctly on all the surfaces that it receives as parameters.
   //    It will also set the error on the output surface.
   // Return Value:
   //    - MV_NOERROR, if everything is correct.
   //    - MV_E_FAIL, if something went wrong.
   // 
   //
   virtual HRESULT __stdcall SetLastErrorAndSignalCompletion(
      IMvSurface    *in_apIInputSurface[],         // Array of input surfaces.
      unsigned long  in_ulNbInputSurface,          // Number of surfaces in in_apIInputSurface.
      IMvSurface    *in_apIEffectPatternSurface[], // Array of effect pattern surfaces.
      unsigned long  in_ulNbEffectPatternSurface,  // Number of surfaces in in_apIEffectPatternSurface.
      IMvSurface    *in_pIBackgroundSurface,       // Background surface.
      IMvSurface    *in_pIOutputSurface,           // Output surface.
      HRESULT        in_hr                         // HRESULT to set in the output surface.
      ) = 0;

   //
   // Summary:
   //    This method will set the error on the output surface.
   // Return value:
   //   - MV_NOERROR, if everything is correct.
   //   - MV_E_FAIL, if something went wrong.
   //
   virtual HRESULT __stdcall SetLastError(
      IMvSurface    *in_pIOutputSurface,  // Output surface.
      HRESULT        in_hr                // HRESULT to set in the output surface.
      ) = 0;

};


//
// Summary:
//    Vertex buffer interface.
//    This interface allows the user to manipulate a vertex buffer.  Vertex buffer are used to store FVF or
//    non-FVF vertices. 
//
interface IMvFlex3DVertexBuffer : public IUnknown
{ 
public:
   //
   // Summary:
   //    Locks a range of vertex data and obtains a pointer to the vertex buffer memory.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall Lock(
      unsigned long    in_ulOffsetToLock, // Offset into the vertex data to lock, in bytes. Lock the entire vertex 
                                             // buffer by specifying 0 for both parameters, SizeToLock and OffsetToLock
      unsigned long    in_ulSizeToLock,   // Size of the vertex data to lock, in bytes. Lock the entire vertex buffer by 
                                             // specifying 0 for both parameters, SizeToLock and OffsetToLock
      void           **out_ppData,        // pointer to a memory buffer containing the returned vertex data
      unsigned long    in_ulFlags         // Combination of zero or more locking flags that describe the type of lock to 
                                             // perform.
      ) = 0;

   //
   // 
   // Unlocks the vertex buffer data.
   // 
   // \return MV_NOERROR if the method succeeds.
   // \return	MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall Unlock() = 0;

   //
   // Summary:
   //    Retrieves a description of the vertex buffer resource.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall GetDesc(SMvVertexBufferDesc *out_poDesc // Pointer to a SMvVertexBufferDesc structure, describing the vertex buffer.
      ) = 0;
};

//
// Summary:
//    Index buffer interface.
//    This interface allows the user to manipulate an index buffer.  An index buffer is used to hold 
//    16-bits or 32-bits indices.  Those indices are used to references vertices in a vertex buffer, and
//    are used with DrawIndexedPrimitives and DrawIndexedPrimitivesUP.  Call SetIndices to bind an index
//    buffer with the device.
//
interface IMvFlex3DIndexBuffer : public IUnknown
{ 
public:
   //
   // Summary:
   //    Locks a range of index data and obtains a pointer to the index buffer memory.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall Lock(
      unsigned long in_ulOffsetToLock, // Offset into the index data to lock, in bytes. Lock the entire index buffer
                                          // by specifying 0 for both parameters, SizeToLock and OffsetToLock
      unsigned long in_ulSizeToLock,   // Size of the index data to lock, in bytes. Lock the entire index buffer by 
                                          // specifying 0 for both parameters, SizeToLock and OffsetToLock
      void **out_ppData,               // pointer to a memory buffer containing the returned index data
      unsigned long in_ulFlags         // Combination of zero or more locking flags that describe the type of lock to 
                                          // perform.
      ) = 0;

   // 
   // Summary:
   //    Unlocks the index buffer data.
   // Return Value: 
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall Unlock() = 0;

   //
   // Summary:
   //    Retrieves a description of the index buffer resource.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails.
   //
   virtual HRESULT __stdcall GetDesc(SMvIndexBufferDesc *out_poDesc  // Pointer to a SMvIndexBufferDesc structure, describing the index buffer.
      ) = 0;
};

//
// Summary:
//    Vertex declaration interface.
//    This interface encapsulates the functionality of a vertex declaration.
//    A vertex declaration is a way of programming the graphic chip DMA. It expresses the data layout in the
//    vertex buffers binded to the device.
//
interface IMvFlex3DVertexDeclaration : public IUnknown
{
public:
};

//
// Summary:
//    Vertex shader interface.
//    This interface encapsulates the functionality of a vertex shader.
//    More information about \ref shaderdoc.
//
interface IMvFlex3DVertexShader : public IUnknown
{
public:
};


//
// \interface IMvFlex3DPixelShader
// Summary:
//   Pixel shader interface.
//   This interface encapsulates the functionality of a pixel shader.
//   More information about \ref shaderdoc.
//
interface IMvFlex3DPixelShader : public IUnknown
{
public:
};

//
// Summary:
//    State block interface.
//    This interface controls the state block.  It can be used to load/save
//    a set of renderstate.
//
interface IMvFlex3DStateBlock : public IUnknown
{ 
public:
   //
   // Summary:
   //    Apply the state block to the current device state.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails while in record mode.
   //
   virtual HRESULT __stdcall Apply() = 0; 

   //
   // Summary:
   //    Capture the device's current state.
   // Return Value:
   //    - MV_NOERROR if the method succeeds.
   //    - MV_E_INVALID_CALL if the method fails because the capture cannot be done in record mode.
   //
   virtual HRESULT __stdcall Capture() = 0;
};


//////////////////////////////////////////////////////////////////////////
/// \page shaderdoc Pixel and Vertex Shaders
/// \section Introduction
/// 
/// 
/// 
/// 
/// 
/// 

//////////////////////////////////////////////////////////////////////////
/// \page antialiasing Fragment Antialiasing (FAA-16x)
/// \section Introduction
/// 
/// FAA-16x is the only technology that is capable of providing true 16-sample antialiasing for the 
/// highest-quality antialiased rendering with minimal performance impact. FAA-16x intelligently 
/// antialiases only the edge pixels of triangles and applies 16x super-sampling to them, while leaving 
/// internal textures sharp and unblurred. As edge pixels typically make up only a small fraction of the 
/// pixels in a scene, FAA-16x is able to offer this superior quality with a very small performance penalty.
/// 
/// \section howto How to use it?
/// To use the FAA-16x, you must:
/// - be using a zbuffer, cleared to 1.0f;
/// - be using the z function <= (less or equal);
/// - activate the fragment collection (keMvRSAAFragmentCollectEnable set to TRUE);
/// - render your opaque triangles;
/// - call IMvFlex3DDevice::Present(TRUE), which resolve the fragment and generate the antialiasing.
/// 
/// 

//////////////////////////////////////////////////////////////////////////
/// \page synchro Synchronization
/// \section Introduction
/// 
/// \section howto How to use it?
/// 
/// 

//////////////////////////////////////////////////////////////////////////
/// \page devicecaps Device Capabilities
/// \section Introduction
/// This is the list of the capabilities of the Flex 3D Device.  Those capabilities flags are based on
/// DirectX device caps structure and flags.
/// \section Caps
/// - D3DCAPS_READ_SCANLINE
/// \section Caps2
/// - D3DCAPS2_FULLSCREENGAMMA
/// \section DevCaps
/// - D3DDEVCAPS_EXECUTESYSTEMMEMORY  
/// - D3DDEVCAPS_EXECUTEVIDEOMEMORY   
/// - D3DDEVCAPS_TLVERTEXSYSTEMMEMORY 
/// - D3DDEVCAPS_TLVERTEXVIDEOMEMORY  
/// - D3DDEVCAPS_TEXTUREVIDEOMEMORY   
/// - D3DDEVCAPS_DRAWPRIMTLVERTEX     
/// - D3DDEVCAPS_CANRENDERAFTERFLIP   
/// - D3DDEVCAPS_TEXTURENONLOCALVIDMEM
/// - D3DDEVCAPS_DRAWPRIMITIVES2      
/// - D3DDEVCAPS_DRAWPRIMITIVES2EX    
/// - D3DDEVCAPS_HWTRANSFORMANDLIGHT  
/// - D3DDEVCAPS_HWRASTERIZATION   
/// \section PrimitiveMiscCaps
/// - D3DPMISCCAPS_MASKZ              
/// - D3DPMISCCAPS_CULLNONE           
/// - D3DPMISCCAPS_CULLCW             
/// - D3DPMISCCAPS_CULLCCW            
/// - D3DPMISCCAPS_COLORWRITEENABLE   
/// - D3DPMISCCAPS_TSSARGTEMP         
/// - D3DPMISCCAPS_BLENDOP            
/// \section RasterCaps
/// - D3DPRASTERCAPS_DITHER              
/// - D3DPRASTERCAPS_FOGVERTEX           
/// - D3DPRASTERCAPS_FOGTABLE            
/// - D3DPRASTERCAPS_ANISOTROPY          
/// - D3DPRASTERCAPS_WFOG                
/// - D3DPRASTERCAPS_ZFOG                
/// - D3DPRASTERCAPS_COLORPERSPECTIVE    
/// - D3DPRASTERCAPS_SCISSORTEST         
/// \section ZCmpCaps
/// - D3DPCMPCAPS_NEVER       
/// - D3DPCMPCAPS_LESS        
/// - D3DPCMPCAPS_EQUAL       
/// - D3DPCMPCAPS_LESSEQUAL   
/// - D3DPCMPCAPS_GREATER     
/// - D3DPCMPCAPS_NOTEQUAL    
/// - D3DPCMPCAPS_GREATEREQUAL
/// - D3DPCMPCAPS_ALWAYS      
/// \section SrcBlendCaps
/// - D3DPBLENDCAPS_ZERO            
/// - D3DPBLENDCAPS_ONE             
/// - D3DPBLENDCAPS_SRCCOLOR        
/// - D3DPBLENDCAPS_INVSRCCOLOR     
/// - D3DPBLENDCAPS_SRCALPHA        
/// - D3DPBLENDCAPS_INVSRCALPHA     
/// - D3DPBLENDCAPS_DESTALPHA       
/// - D3DPBLENDCAPS_INVDESTALPHA    
/// - D3DPBLENDCAPS_DESTCOLOR       
/// - D3DPBLENDCAPS_INVDESTCOLOR    
/// - D3DPBLENDCAPS_SRCALPHASAT     
/// - D3DPBLENDCAPS_BOTHSRCALPHA    
/// - D3DPBLENDCAPS_BOTHINVSRCALPHA 
/// \section DestBlendCaps
/// - D3DPBLENDCAPS_ZERO            
/// - D3DPBLENDCAPS_ONE             
/// - D3DPBLENDCAPS_SRCCOLOR        
/// - D3DPBLENDCAPS_INVSRCCOLOR     
/// - D3DPBLENDCAPS_SRCALPHA        
/// - D3DPBLENDCAPS_INVSRCALPHA     
/// - D3DPBLENDCAPS_DESTALPHA       
/// - D3DPBLENDCAPS_INVDESTALPHA    
/// - D3DPBLENDCAPS_DESTCOLOR       
/// - D3DPBLENDCAPS_INVDESTCOLOR    
/// - D3DPBLENDCAPS_SRCALPHASAT     
/// - D3DPBLENDCAPS_BOTHSRCALPHA    
/// - D3DPBLENDCAPS_BOTHINVSRCALPHA 
/// \section AlphaCmpCaps
/// - D3DPCMPCAPS_NEVER       
/// - D3DPCMPCAPS_LESS        
/// - D3DPCMPCAPS_EQUAL       
/// - D3DPCMPCAPS_LESSEQUAL   
/// - D3DPCMPCAPS_GREATER     
/// - D3DPCMPCAPS_NOTEQUAL    
/// - D3DPCMPCAPS_GREATEREQUAL
/// - D3DPCMPCAPS_ALWAYS      
/// \section ShadeCaps
/// - D3DPSHADECAPS_COLORGOURAUDRGB   
/// - D3DPSHADECAPS_SPECULARGOURAUDRGB
/// - D3DPSHADECAPS_ALPHAGOURAUDBLEND 
/// - D3DPSHADECAPS_FOGGOURAUD        
/// \section TextureCaps
/// - D3DPTEXTURECAPS_PERSPECTIVE       
/// - D3DPTEXTURECAPS_ALPHA             
/// - D3DPTEXTURECAPS_TEXREPEATNOTSCALEDBYSIZE
/// - D3DPTEXTURECAPS_PROJECTED         
/// - D3DPTEXTURECAPS_CUBEMAP           
/// - D3DPTEXTURECAPS_VOLUMEMAP         
/// - D3DPTEXTURECAPS_MIPMAP            
/// - D3DPTEXTURECAPS_MIPVOLUMEMAP      
/// - D3DPTEXTURECAPS_MIPCUBEMAP        
/// \section TextureFilterCaps (2D, 3D, volume)
/// - D3DPTFILTERCAPS_MINFPOINT         
/// - D3DPTFILTERCAPS_MINFLINEAR        
/// - D3DPTFILTERCAPS_MINFANISOTROPIC   
/// - D3DPTFILTERCAPS_MIPFPOINT         
/// - D3DPTFILTERCAPS_MIPFLINEAR        
/// - D3DPTFILTERCAPS_MAGFPOINT         
/// - D3DPTFILTERCAPS_MAGFLINEAR        
/// - D3DPTFILTERCAPS_MAGFANISOTROPIC   
/// \section TextureAddressCaps (2D, volume)
/// - D3DPTADDRESSCAPS_WRAP          
/// - D3DPTADDRESSCAPS_MIRROR        
/// - D3DPTADDRESSCAPS_CLAMP         
/// - D3DPTADDRESSCAPS_BORDER        
/// - D3DPTADDRESSCAPS_INDEPENDENTUV 
/// - D3DPTADDRESSCAPS_MIRRORONCE    
/// \section LineCaps
/// - D3DLINECAPS_TEXTURE     
/// - D3DLINECAPS_ZTEST       
/// - D3DLINECAPS_BLEND       
/// - D3DLINECAPS_ALPHACMP    
/// - D3DLINECAPS_FOG         
/// \section StencilCaps
/// - D3DSTENCILCAPS_KEEP      
/// - D3DSTENCILCAPS_ZERO      
/// - D3DSTENCILCAPS_REPLACE   
/// - D3DSTENCILCAPS_INCRSAT   
/// - D3DSTENCILCAPS_DECRSAT   
/// - D3DSTENCILCAPS_INVERT    
/// - D3DSTENCILCAPS_INCR      
/// - D3DSTENCILCAPS_DECR      
/// \section FVFCaps
/// - D3DFVFCAPS_TEXCOORDCOUNTMASK 8
/// - D3DFVFCAPS_PSIZE             
/// \section TextureOpCaps
/// - D3DTEXOPCAPS_DISABLE                  
/// - D3DTEXOPCAPS_SELECTARG1               
/// - D3DTEXOPCAPS_SELECTARG2               
/// - D3DTEXOPCAPS_MODULATE                 
/// - D3DTEXOPCAPS_MODULATE2X               
/// - D3DTEXOPCAPS_MODULATE4X               
/// - D3DTEXOPCAPS_ADD                      
/// - D3DTEXOPCAPS_ADDSIGNED                
/// - D3DTEXOPCAPS_ADDSIGNED2X              
/// - D3DTEXOPCAPS_SUBTRACT                 
/// - D3DTEXOPCAPS_ADDSMOOTH                
/// - D3DTEXOPCAPS_BLENDDIFFUSEALPHA        
/// - D3DTEXOPCAPS_BLENDTEXTUREALPHA        
/// - D3DTEXOPCAPS_BLENDFACTORALPHA         
/// - D3DTEXOPCAPS_BLENDTEXTUREALPHAPM      
/// - D3DTEXOPCAPS_BLENDCURRENTALPHA        
/// - D3DTEXOPCAPS_PREMODULATE              
/// - D3DTEXOPCAPS_MODULATEALPHA_ADDCOLOR   
/// - D3DTEXOPCAPS_MODULATECOLOR_ADDALPHA   
/// - D3DTEXOPCAPS_MODULATEINVALPHA_ADDCOLOR
/// - D3DTEXOPCAPS_MODULATEINVCOLOR_ADDALPHA
/// - D3DTEXOPCAPS_BUMPENVMAP               
/// - D3DTEXOPCAPS_BUMPENVMAPLUMINANCE      
/// - D3DTEXOPCAPS_DOTPRODUCT3              
/// - D3DTEXOPCAPS_MULTIPLYADD              
/// - D3DTEXOPCAPS_LERP                     
/// \section VertexProcessingCaps
/// - D3DVTXPCAPS_TEXGEN              
/// - D3DVTXPCAPS_MATERIALSOURCE7     
/// - D3DVTXPCAPS_DIRECTIONALLIGHTS   
/// - D3DVTXPCAPS_POSITIONALLIGHTS    
/// - D3DVTXPCAPS_LOCALVIEWER         
/// - D3DVTXPCAPS_TWEENING            
/// \section DeclTypes
/// - D3DDTCAPS_UBYTE4    
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
/// \interface IUnknown
/// IUnknown interface.  Supports IUnknown::AddRef, IUnknown::Release and IUnknown::QueryInterface.
//////////////////////////////////////////////////////////////////////////

///
/// \defgroup interface_def Interface definitions
///
///@{
/// @}


#endif

