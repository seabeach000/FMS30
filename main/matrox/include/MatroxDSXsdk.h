//==============================================================================
//
// (c) Copyright Matrox Electronic Systems Ltd., 2013-2015. All rights reserved. 
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

#pragma once


#ifdef LINUX_PLATFORM
#include "mvLinuxDefinitions.h"
#else
#ifndef _TCHAR
#include "tchar.h"
#endif
#endif

// All applications should use these
#include "MvFlexAPI.h"
#include "MvFlexGuids.h"
#include "mvErrors.h"
#include "mvKernelErrors.h"
#include "mvErrorToString.h"
#include "mvTime.h"
#include "mvAudioTime.h"
#include "mvHResult.h"
#include "mvSmartPtr.h"
#include "MatroxDSXsdkDefinitions.h"

#pragma pack(push, 8)

// Forward declarations
interface IMvWriterStream;
interface IMvTransferStream;
interface IMvCompressedHostNode;
interface IMvTextureNode;
interface IMvRenderingTargetNode;
interface IMvEncoderStreamSettingsCallback;

interface IMvReaderStream;
interface IMvReaderStreamElement;
interface IMvCompressedNodeNotificationForRead;
interface IMvCompressedNodeNotificationForWrite;
interface IMvUniversalClockNotificationCallback;
interface IMvDSXCORENotificationCallback;



//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents a transfer stream in a workflow topology. 
// Remarks:
//    - This interface is used to transfer data between onboard memory and host memory.
//    - Both the input and output of this stream are nodes. However, one is a card node and the other a host node.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvTransferStream : public IMvStream
{
   // Summary:
   //    Gets the input node currently bound to the transfer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If the output node is a host node, then the input node is a card node, and vice-versa.
   //
   virtual HRESULT __stdcall GetInputNode
      (
      uint64_t& out_rui64Timestamp, // Indicates the time that the node was activated.
      IMvNode** out_ppIInputNode    // Pointer that receives the input node interface. 
      ) = 0;

   //
   // Summary:
   //    Modifies the input node currently bound to the transfer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //    - The new input node must have the same resolution and same memory location as the old input node.
   //    - If the output node is a host node, then the input node must be a card node, and vice-versa.
   //
   virtual HRESULT __stdcall SetInputNode
      (
      uint64_t in_ui64Timestamp, // Indicates the time that the modifications are to be made.
      IMvNode* in_pIInputNode    // Pointer to the new input node interface. The pointer will be used at the time
                                 // specified in in_ui64Timestamp.
      ) = 0;

   //
   // Summary:
   //    Gets the output node currently bound to the transfer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If the input node is a host node, then the output node is a card node, and vice-versa.
   //
   virtual HRESULT __stdcall GetOutputNode
      (
      uint64_t& out_rui64Timestamp, // Indicates the time that the node was activated.
      IMvNode** out_ppIOutputNode   // Pointer that receives the output node interface. 
      ) = 0;

   //
   // Summary:
   //    Modifies the output node currently bound to the transfer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //    - The new output node must have the same frame resolution and memory location as the old output node.
   //    - If the input node is a host node, then the output node must be a card node, and vice-versa.
   //
   virtual HRESULT __stdcall SetOutputNode
      (
      uint64_t in_ui64Timestamp, // Indicates the time that the modification are to be made.
      IMvNode* in_pIOutputNode   // Pointer to the new output node interface. The pointer will be used at the time
                                 // specified in in_ui64Timestamp.
      ) = 0;

   
   // Summary:
   //    Gets the current settings of the transfer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // 
   virtual HRESULT __stdcall GetTransferStreamSettings
      (
      uint64_t & out_ui64Timestamp,                      // Indicates the time that the transfer stream settings 
                                                         // were activated.    
      SMvTransferStreamSettings & out_rsStreamSettings   // Structure that receives the transfer stream settings.
      ) = 0;

   // Summary:
   //    Modifies the current settings of the transfer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //
   virtual HRESULT __stdcall SetTransferStreamSettings
      (
      uint64_t in_ui64Timestamp,                            // Indicates the time that the modifications are to be made.
      const SMvTransferStreamSettings in_rsStreamSettings   // Structure of the new transfer stream settings. 
                                                            // The pointer will be used at the time specified in in_ui64Timestamp.
      ) = 0;

   // Summary:
   //    Gets the direction of the transfer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall GetTransferStreamDirection
      (
      EMvTransferDirection * out_pTransferDirection			// Pointer to the EMvTransferSirection enumerator indicating the direction in which the data will be transferred.
      ) = 0;                                                
};



//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides a callback notification to a host node. 
//    This interface passes notification information to the object implementing it.
// Remarks:
//    - Use the IMvHostNode interface to register and unregister the 
//      IMvNodeNotificationCallback interface.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvNodeNotificationCallback : public IUnknown
{
   //
   // Summary:
   //    Notifies when uncompressed data can be sent or retrieved.
   // Return value:
   //    - MV_NOERROR. 
   //
   virtual HRESULT __stdcall NotifyForBufferAccess
      (
      const SMvNodeNotificationCallbackParameters & in_krsNotificationParameters	// Structure containing the parameters of the node notification callback. 
      ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used for registering and unregistering a callback notification on a host node. 
// Remarks:
//    - The user application uses the methods from both IMvNode and IMvHostNode when performing operations on a host node.
//    - This interface is used as the source or destination of a software streams.
//    - The node's contents, such as video and audio data, can be queried or modified by the host for every frame.
//    - Nodes enforce a configurable write-to-read delay in clock ticks that defaults to one frame.
//    - Nodes have a configurable depth in frames allowing the user application to have a certain time to access past
//      node data.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvHostNode : public IMvNode
{
   //
   // Summary:
   //    Registers a callback notification allowing the user application to read data from a host node.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::AddRef method of the in_pINotification parameter is called when the 
   //      notification is registered to prevent the object implementing the IMvNodeNotificationCallback 
   //      interface from being destroyed.
   //    - The callback is called when each video unit is ready to be read. Pointers to the node's data are guaranteed
   //      to be valid for the time indicated by SMvNodeNotificationCallbackParameters::ui64UseBefore. 
   //    - The user application must read the node's data no later than the callback time stamp 
   //      SMvNodeNotificationCallbackParameters::ui64UseBefore.  
   //      Delaying the callback later than ui64UseBefore will cause the next callback call to skip frames.
   //
   virtual HRESULT __stdcall RegisterCallbackForRead
      (
      IMvNodeNotificationCallback * in_pICallback   // Pointer to the node notification callback interface.
      ) = 0;

   //
   // Summary:
   //    Registers a callback notification allowing the user application to write data to a host node.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::AddRef method of the in_pINotification parameter is called when the 
   //      notification is registered to prevent the object implementing the IMvNodeNotificationCallback 
   //      interface from being destroyed.
   //    - The callback is called for each time based unit. Pointers to the node's data are guaranteed to be valid 
   //      for the time indicated by SMvNodeNotificationCallbackParameters::ui64UseBefore.
   //    - The user application must write data to the node no later than the callback time stamp 
   //      SMvNodeNotificationCallbackParameters::ui64UseBefore.  
   //      Delaying the callback later than ui64UseBefore will cause the next callback call to skip frames.
   //
   virtual HRESULT __stdcall RegisterCallbackForWrite
      (
      IMvNodeNotificationCallback * in_pICallback  // Pointer to the node notification callback interface.
      ) = 0;

   //
   // Summary:
   //    Registers a callback notification allowing the user application to write a particular node content type to a host node.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::AddRef method of the in_pINotification parameter is called when the 
   //      notification is registered to prevent the object implementing the IMvNodeNotificationCallback 
   //      interface from being destroyed.
   //    - The callback is called for each time based unit. Pointers to the node's data 
   //      specified by the eContentToProcess are guaranteed to be valid 
   //      for the time indicated by SMvNodeNotificationCallbackParameters::ui64UseBefore.
   //    - The user application must write data to the node no later than the callback time stamp 
   //      SMvNodeNotificationCallbackParameters::ui64UseBefore.  
   //      Delaying the callback later than ui64UseBefore will cause the next callback call to skip frames.
   //
   virtual HRESULT __stdcall RegisterCallbackForWriteEx
      (
      const SMvHostNodeRegistrationInfo & in_krsCallbackInfo   // Structure of the host node callback notification settings.
      ) = 0;

   //
   // Summary:
   //    Unregisters a read callback notification for a host node.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::Release method of the in_pICallback parameter is called when the notification is unregistered to
   //      remove the reference count added by IMvHostNode::RegisterCallbackForRead.
   //    - If a callback is in progress, this method will wait for the callback to complete before unregistering the callback.
   //
   virtual HRESULT __stdcall UnregisterReadCallback
      (
      IMvNodeNotificationCallback * in_pICallback  // Pointer to the node notification callback interface.
      ) = 0;

   //
   // Summary:
   //    Unregisters a write callback notification for a host node.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::Release method of the in_pICallback parameter is called when the notification is unregistered to
   //      remove the reference count added by IMvHostNode::RegisterCallbackForWrite.
   //    - If a callback is in progress, this method will wait for the callback to complete before unregistering the callback.
   //
   virtual HRESULT __stdcall UnregisterWriteCallback
      (
      IMvNodeNotificationCallback * in_pICallback  // Pointer to the node notification callback interface.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents a node containing compressed video data, compressed audio data, 
//    compressed VANC data, or transport stream (TS) muxed buffers in a workflow topology.
// Remarks:
//    - The compressed data is located in host memory.
//    - A compressed host node can only contain one type of data. For example, it can contain only compressed video data.
//    - A compressed host node is used to pass compressed data between two compressed streams.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvCompressedHostNode : public IMvNode
{
   //
   // Summary:
   //    Gets the settings used to create the compressed host node.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetCompressedHostNodeDescription
      (
      SMvCompressedHostNodeSettings & io_rsSettings   // Indicates the settings of the compressed host node. 
      ) = 0;

   //
   // Summary:
   //    Registers a callback notification allowing the user application to read data from a compressed host node.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::AddRef method of the in_pINotificationInterface parameter is called when the 
   //      notification is registered to prevent the object implementing the IMvCompressedNodeNotificationForRead 
   //      interface from being destroyed.
   //    - The callback is called when each video unit is ready to be read. Pointers to the compressed host node's data are guaranteed
   //      to be valid until the user application returns control to the compressed host node. 
   //    - Multiple callback notifications can be registered for reading.
   //
   virtual HRESULT __stdcall RegisterCallbackForRead
      (
      IMvCompressedNodeNotificationForRead * in_pINotificationInterface // Pointer to the compressed node notification callback interface for reading.
      ) = 0;

   //
   // Summary:
   //    Registers a callback notification allowing the user application to write data to a compressed host node.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::AddRef method of the in_pINotificationInterface parameter is called when the 
   //      notification is registered to prevent the object implementing the IMvCompressedNodeNotificationForWrite 
   //      interface from being destroyed.
   //    - The callback is called every time the compressed host node requires a buffer. 
   //    - Only one callback notification can be registered at a time for writing. To register another callback notification for writing, 
   //      the user application must first unregister the current callback notification before it can register another.
   //    - A compressed host node cannot receive compressed data from another source when a callback for write has been registered. 
   //
   virtual HRESULT __stdcall RegisterCallbackForWrite
      (
      IMvCompressedNodeNotificationForWrite * in_pINotificationInterface,           // Pointer to the compressed node notification callback interface for writing.
      uint32_t                                in_ui32MaxBufferSize,                 // Indicates the maximum expected size for the compressed data.
      EMvNodeNotificationDataType             in_eDataType,                         // Indicates the type of data contained in the compressed host node.
      IMvEncoderStreamSettingsCallback *      in_pIMvEncoderStreamSettingsCallback  // Pointer to the encoder stream settings callback interface.
      ) = 0;

   //
   // Summary:
   //    Unregisters a read callback notification for a compressed host node.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::Release method of the in_pINotificationInterface parameter is called when the notification is unregistered to
   //      remove the reference count added by IMvCompressedHostNode::RegisterCallbackForRead.
   //    - If a callback is in progress, this method will wait for the callback to complete before unregistering the callback.
   //
   virtual HRESULT __stdcall UnregisterReadCallback
      (
      IMvCompressedNodeNotificationForRead * in_pINotificationInterface    // Pointer to the compressed node notification callback interface for reading.
      ) = 0;

   //
   // Summary:
   //    Unregisters a write callback notification for a compressed host node.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::Release method is called when the notification is unregistered to
   //      remove the reference count added by IMvCompressedHostNode::RegisterCallbackForWrite.
   //    - If a callback is in progress, this method will wait for the callback to complete before unregistering the callback.
   //
   virtual HRESULT __stdcall UnregisterWriteCallback() = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents a node containing video data, audio data, VANC data that can be 
//    received from an object in a GPU card.
// Remarks:
//    - The node act as an host node but with some added feature for GPU transfers.
//    - This type of node can transfer data from the GPU card into the node.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvTextureNode : public IMvHostNode
{
   //
   // Summary:
   //    Returns the type of rendering API that the node us to synchronize data between the graphic card and the node.
   // Return value:
   //    - Return the rendering API.
   //
   virtual EMvGPUTransferRenderingMode __stdcall GetRenderingMode() = 0;

   //
   // Summary:
   //    Returns the type of transfer API that the node us to communicate with the graphic card.
   // Return value:
   //    - Return the transfer API.
   //
   virtual EMvGPUTransferMode __stdcall GetGPUTransferMode() = 0;

   //
   // Summary:
   //    Returns the type of YUYV byte organization in the ARGB texture.
   // Return value:
   //    - Return the byte organization type.
   //
   virtual EMvComponentSelection __stdcall GetComponentSelection() = 0;

   //
   // Summary:
   //    Returns the buffer that will be used as a source texture fro 3D rendering.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetNodeContent
      (
      uint64_t in_ui64Timeout,      // Maximum timeout in milliseconds to wait for a texture before returning.
      uint64_t in_ui64Timestamp,    // Indicates the time that the data must be fetched from the node.
      void  ** out_ppTexture        // Pointer that will receive the texture. For OpenGL, it is of type GLuint.
                                    // For DirectX11, it is a pointer of type ID3D11ShaderResourceView and an AddRef() 
                                    // has been done on the pointer.
      ) = 0;

   virtual HRESULT __stdcall SignalReadCompletion
      (
      void * in_pTexture
      ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents a node containing video data, audio data, VANC data that can be 
//    transfered into object in a GPU card.
// Remarks:
//    - The node act as an host node but with some added feature for GPU transfers.
//    - This type of node can transfer data from the node to a GPU card.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvRenderingTargetNode : public IMvHostNode
{
   //
   // Summary:
   //    Returns the type of rendering API that the node us to synchronize data between the graphic card and the node.
   // Return value:
   //    - Return the rendering API.
   //
   virtual EMvGPUTransferRenderingMode __stdcall GetRenderingMode() = 0;

   //
   // Summary:
   //    Returns the type of transfer API that the node us to communicate with the graphic card.
   // Return value:
   //    - Return the transfer API.
   //
   virtual EMvGPUTransferMode __stdcall GetGPUTransferMode() = 0;

   //
   // Summary:
   //    Returns the buffer that will be used as a rendering target.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall WaitForRenderingTarget
      (
      uint64_t in_ui64Timeout,   // Maximum timeout in milliseconds to wait for a rendering target before returning.
      void  ** out_ppTarget      // Pointer that will receive the rendering target. For OpenGL, it is of type GLuint.
                                 // For DirectX11, it is a pointer of type ID3D11RenderTargetView and an AddRef() 
                                 // has been done on the pointer.
      ) = 0;

   //
   // Summary:
   //    Send the content of a rendering target to the node.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetNodeContent
      (
      uint64_t in_ui64Timestamp, // Indicates the time that the data must be sent to the node.
      void   * in_pTarget        // Rendering target containing the data to send to the node. The pointer must have been
                                 // received by IMvRenderingTargetNode::WaitForRenderingTarget().
      ) = 0;

   //
   // Summary:
   //    Indicates that the rendering target will not be sent to the node.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CancelNodeContent
      (
      void * in_pTarget    // Rendering target that won't be sent to the node. The pointer must have been
                           // received by IMvRenderingTargetNode::WaitForRenderingTarget().
      ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This structure is an extension of SMvGerericVancPacket, and provides the VANC packet line number.
//
//////////////////////////////////////////////////////////////////////////////////
struct SMvVancPacket : public SMvGenericVancPacket
{
   uint32_t ui32LineNumber;   // Indicates the line number from which the VANC packet was extracted 
                              // or to which the VANC packet will be inserted.
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface available for host nodes allowing VANC data packet manipulation.
// Remarks:
//    - This interface is obtained by querying IMvHostNode for IID_IMvVancDataPackets using IUnknown::QueryInterface().
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvVancDataPackets : public IUnknown
{
   //
   // Summary: 
   //    Enables VANC data packet manipulation.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INCOMPATIBLE_NODE_CONTENT, if node content does not contain keMvNodeContentVanc.
   //    - MV_E_UNSUPPORTED_SURFACE_FORMAT, if the VANC format is other than keMvSurfaceFormatMatroxAncillaryData.
   // Remarks:
   //    - In order to use the IMvVancDataPackets interface, it must be enabled.
   //    - VANC must be handled with the IMvVancDataPackets interface when it is enabled. Otherwise, if the VANC 
   //      surface parameters are not null, the IMvNode::GetNodeContentField(), IMvNode::GetNodeContentFields(), 
   //      and IMvNode::GetNodeContentFrame() methods will fail with MV_E_INVALID_PARAMETER, and no ancillary data 
   //      will be provided to the node notification callback interface (IMvNodeNotificationCallback).
   //
   virtual HRESULT __stdcall EnableVancDataPackets() = 0;
   //
   // Summary: 
   //    Disables VANC data packet manipulation.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INCOMPATIBLE_NODE_CONTENT, if node content does not contain keMvNodeContentVanc.
   // Remarks:
   //    - When the IMvVancDataPackets interface is disabled, trying to manipulate VANC data packets with it will fail with MV_E_NOT_AVAILABLE.
   //
   virtual HRESULT __stdcall DisableVancDataPackets() = 0;

   //
   // Summary:
   //   Gets arrays of VANC packets from a host node.
   // Return value:
   //    - MV_E_NOT_FOUND, if packets are not available at the time specified by in_ui64Timestamp.
   //    - MV_E_ARRAY_TOO_SMALL, if the number of packets available at in_ui64Timestamp exceeds in_ui32ArraySizeF0 or in_ui32ArraySizeF1.
   //    - MV_E_NOT_AVAILABLE, if IMvVancDataPackets is disabled.
   //    - MV_E_INCOMPATIBLE_SCAN_MODE, if the host node's resolution is not interlaced.
   //
   virtual HRESULT __stdcall GetVancPacketsFields
      (
      uint64_t in_ui64Timestamp,          // Indicates the time at which the packets will be extracted from the host node.
      SMvVancPacket* io_paVancPacketsF0,  // Pointer to the array of VANC packets of the first video field.
      uint32_t& io_ui32ArraySizeF0,        // Size of the array of VANC packets for Field 0.
      SMvVancPacket* io_paVancPacketsF1,  // Pointer to the array of VANC packets of the second video field.
      uint32_t& io_ui32ArraySizeF1         // Size of the array of VANC packets for Field 1.
      ) = 0;

   //
   // Summary:
   //   Sends arrays of VANC packets to a host node.
   // Return value:
   //    - MV_E_MAX_VALUE_REACHED, if too many packets are sent before their time stamp expires.
   //    - MV_E_NOT_AVAILABLE, if IMvVancDataPackets is disabled.
   //
   virtual HRESULT __stdcall SetVancPacketsFields
      (
      uint64_t in_ui64Timestamp,          // Indicates the time at which the packets will be inserted in the host node.
      SMvVancPacket* in_paVancPacketsF0,  // Pointer to the array of VANC packets of the first video field.
      uint32_t in_ui32ArraySizeF0,        // Size of the array of VANC packets for Field 0.
      SMvVancPacket* in_paVancPacketsF1,  // Pointer to the array of VANC packets of the second video field.
      uint32_t in_ui32ArraySizeF1         // Size of the array of VANC packets for Field 1.
      ) = 0;

   //
   // Summary:
   //   Gets an array of VANC packets from a host node.
   // Return value:
   //    - MV_E_NOT_FOUND, if packets are not available at the time specified by in_ui64Timestamp.
   //    - MV_E_ARRAY_TOO_SMALL, if the number of packets available at in_ui64Timestamp exceeds in_ui32ArraySize.
   //    - MV_E_NOT_AVAILABLE, if IMvVancDataPackets is disabled.
   //    - MV_E_INCOMPATIBLE_SCAN_MODE, if the host node's resolution is not interlaced.
   //
   virtual HRESULT __stdcall GetVancPacketsField
      (
      uint64_t in_ui64Timestamp,       // Indicates the time at which the packets will be extracted from the host node.
      SMvVancPacket* io_paVancPackets, // Pointer to the array of VANC packets of the video field.
      uint32_t& io_ui32ArraySize       // Size of the array of VANC packets for the field.
      ) = 0;

   //
   // Summary:
   //   Sends an array of VANC packets to a host node.
   // Return value:
   //    - MV_E_MAX_VALUE_REACHED, if too many packets are sent before their time stamp expires.
   //    - MV_E_NOT_AVAILABLE, if IMvVancDataPackets is disabled.
   //    - MV_E_INCOMPATIBLE_SCAN_MODE, if the host node's resolution is not interlaced.
   //
   virtual HRESULT __stdcall SetVancPacketsField
      (
      uint64_t in_ui64Timestamp,       // Indicates the time at which the packets will be inserted in the host node.
      SMvVancPacket* in_paVancPackets, // Pointer to the array of VANC packets of the video field.
      uint32_t in_ui32ArraySize        // Size of the array of VANC packets for the field.
      ) = 0;

   //
   // Summary:
   //   Gets an array of VANC packets from a host node.
   // Return value:
   //    - MV_E_NOT_FOUND, if packets are not available at the time specified by in_ui64Timestamp.
   //    - MV_E_ARRAY_TOO_SMALL, if the number of packets available at in_ui64Timestamp exceeds in_ui32ArraySize.
   //    - MV_E_NOT_AVAILABLE, if IMvVancDataPackets is disabled.
   //    - MV_E_INCOMPATIBLE_SCAN_MODE, if the host node's resolution is not progressive.
   //
   virtual HRESULT __stdcall GetVancPacketsFrame
      (
      uint64_t in_ui64Timestamp,       // Indicates the time at which the packets will be extracted from the host node.
      SMvVancPacket* io_paVancPackets, // Pointer to the array of VANC packets of the video frame.
      uint32_t& io_ui32ArraySize       // Size of the array of VANC packets for the frame.
      ) = 0;

   //
   // Summary:
   //   Sends an array of VANC packets to a host node.
   // Return value:
   //    - MV_E_MAX_VALUE_REACHED, if too many packets are sent before their time stamp expires.
   //    - MV_E_NOT_AVAILABLE, if IMvVancDataPackets is disabled.
   //    - MV_E_INCOMPATIBLE_SCAN_MODE, if the host node's resolution is not progressive.
   //
   virtual HRESULT __stdcall SetVancPacketsFrame
      (
      uint64_t in_ui64Timestamp,       // Indicates the time at which the packets will be inserted in the host node.
      SMvVancPacket* in_paVancPackets, // Pointer to the array of VANC packets of the video frame.
      uint32_t in_ui32ArraySize        // Size of the array of VANC packets for the frame.
      ) = 0;

   //
   // Summary:
   //   Determines the VANC packet type.
   // Return value:
   //   - MV_NOERROR, if successful.
   //
   virtual HRESULT __stdcall GetVancPacketType
      (
      SMvVancPacket* in_pVancPacket,            // Pointer to the VANC packet structure.
      EMvVANCPacketType &out_reVancPacketType   // Indicates the VANC packet type.
      ) = 0;

   //
   // Summary:
   //   Transforms VANC data packets to caption distribution packets.
   // Return value:
   //    - MV_E_NOT_AVAILABLE, if IMvVancDataPackets is disabled.
   //    - MV_E_INCONSISTENCY_DETECTED, if in_pVancPacket is not a caption distribution packet.
   //
   virtual HRESULT __stdcall TransformVancPacketToCaptionDistributionPacket
      (
      SMvVancPacket* in_pVancPacket,				// Pointer to the structure indicating the VANC packet.
      SMvCaptionDistributionPacket *io_pCdpPacket	// Pointer to the structure indicating the caption distribution packets.
      ) = 0;

   //
   // Summary:
   //   Transforms caption distribution packets to VANC data packets.
   // Return value:
   //    - MV_E_NOT_AVAILABLE, if IMvVancDataPackets is disabled.
   //
   virtual HRESULT __stdcall TransformCaptionDistributionPacketToVancPacket
      (
      SMvCaptionDistributionPacket *in_pCdpPacket,	// Pointer to the structure indicating the caption distribution packets.
      uint32_t in_ui32LineNumber,					// Indicates the VANC packet line number to which the caption distribution packet will be inserted.
      SMvVancPacket* io_pVancPacket					// Pointer to the structure indicating the VANC packet.
      ) = 0;

   //
   // Summary:
   //   Transforms VANC data packets to AFD and bar data packets.
   // Return value:
   //    - MV_E_NOT_AVAILABLE, if IMvVancDataPackets is disabled.
   //    - MV_E_INCONSISTENCY_DETECTED, if in_pVancPacket is not an AFD packet.
   //
   virtual HRESULT __stdcall TransformVancPacketToAFDAndBarDataPacket
      (
      SMvVancPacket* in_pVancPacket,			// Pointer to the structure indicating the VANC packet.
      SMvAFDAndBarDataVancPacket*io_pAFDPacket	// Pointer to the structure indicating the AFD and bar data packets.
      ) = 0;

   //
   // Summary:
   //   Transforms AFD and bar data packets to VANC data packets.
   // Return value:
   //    - MV_E_NOT_AVAILABLE, if IMvVancDataPackets is disabled.
   //
   virtual HRESULT __stdcall TransformAFDAndBarDataPacketToVancPacket
      (
      SMvAFDAndBarDataVancPacket *in_pAFDPacket,	// Pointer to the structure indicating the AFD and bar data packets.
      uint32_t in_ui32LineNumber,					// Indicates the VANC packet line number to which the AFD and bar data packet will be inserted.
      SMvVancPacket* io_pVancPacket					// Pointer to the structure indicating the VANC data.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents an encoder stream in a workflow topology.
// Remarks:
//    - This interface is used to compress video, audio, and VANC data.
//    - The input of this stream is a host node, and the output is a compressed host node.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvEncoderStream : public IMvStream
{
   //
   // Summary:
   //   Gets the current settings of the encoder stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetEncoderStreamSettings
      (
      uint64_t& out_rui64Timestamp,						// Indicates the time that the encoder stream settings were activated.
      SMvEncoderStreamSettings& io_rsStreamSettings		// Structure that receives the encoder stream settings.
      ) = 0;

   //
   // Summary:
   //   Modifies the current settings of the encoder stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //
   virtual HRESULT __stdcall SetEncoderStreamSettings
      (
      uint64_t in_ui64Timestamp,						// Indicates the time that the modifications are to be made.
      const SMvEncoderStreamSettings& in_rsNewSettings	// Structure of the new encoder stream settings. The pointer will be used at the time
														// specified in in_ui64Timestamp.
      ) = 0;

   //
   // Summary:
   //   Gets the input host node currently bound to the encoder stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetInputNode
      (
      uint64_t&     out_rui64Timestamp,		// Indicates the time that the host node was activated.
      IMvHostNode** out_ppIInputNode		// Pointer that receives the input host node interface.
      ) = 0;

   //
   // Summary:
   //   Modifies the input host node currently bound to the encoder stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //    - The new input host node must have the same resolution as the old input host node.
   //    - The input host node can be changed even after the encoder stream is started.
   //
   virtual HRESULT __stdcall SetInputNode
      (
      uint64_t     in_ui64Timestamp,	// Indicates the time that the modifications are to be made.
      IMvHostNode* in_pIInputNode		// Pointer to the new input host node interface. The pointer will be used at the time
										// specified in in_ui64Timestamp.
      ) = 0;

   //
   // Summary:
   //   Gets the output compressed host node currently bound to the encoder stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetOutputNode
      (
      uint64_t&               out_rui64Timestamp,	// Indicates the time that the compressed host node was activated.
      IMvCompressedHostNode** out_ppIOutputNode		// Pointer that receives the output compressed host node interface.
      ) = 0;

   //
   // Summary:
   //   Modifies the output compressed host node currently bound to the encoder stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //    - The new output compressed host node must have the same frame resolution and same memory location as the old output compressed host node.
   //    - The output compressed host node can only be changed when the encoder stream is stopped.
   //
   virtual HRESULT __stdcall SetOutputNode
      (
      uint64_t               in_ui64Timestamp,	// Indicates the time that the modifications are to be made.
      IMvCompressedHostNode* in_pIOutputNode	// Pointer to the new output compressed host node interface. The pointer will be used at the time
												// specified in in_ui64Timestamp.
      ) = 0;

   //
   // Summary:
   //    Gets the current codec settings.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetCodecSettings
      (
      uint64_t&                          out_rui64Timestamp,	// Indicates the time that the codec settings were activated.
      IMvEncoderStreamSettingsCallback** out_ppICodecSettings	// Pointer that receives the encoder stream settings callback interface.
      ) = 0;

   //
   // Summary:
   //   Modifies the codec settings. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //    - The codec settings can only be changed before preparing the encoder stream.
   //
   virtual HRESULT __stdcall SetCodecSettings
      (
      uint64_t                           in_ui64Timestamp,	// Indicates the time that the modifications are to be made.
      IMvEncoderStreamSettingsCallback * in_pICodecSettings	// Pointer to the encoder stream settings callback interface. The pointer will be used at the time
															// specified in in_ui64Timestamp.
      ) = 0;

   //
   // Summary:
   //   Starts the encoder stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This method must be called after calling IMvEncoderStream::PrepareStream().
   //
   virtual HRESULT __stdcall StartEncoding
      (
      uint64_t in_ui64Timestamp	// Indicates the time to start encoding.
      ) = 0;

   //
   // Summary:
   //   Stops the encoder stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Because StopEncoding() is asynchronous, sufficient time must be allowed for StopEncoding() to complete its operation 
   //      before calling PrepareStream() again. The recommended time to wait is between 25 and 50 frames. 
   //
   virtual HRESULT __stdcall StopEncoding
      (
      uint64_t in_ui64Timestamp	// Indicates the time to stop encoding.
      ) = 0;

   //
   // Summary:
   //    Configures the encoder stream. 
   // Note:
   //    - The encoder stream is configured with the codec indicated in IMvEncoderStreamSettingsCallback, which is set in IMvEncoderStream::SetCodecSettings().
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This method is synchronous and must be called before calling IMvEncoderStream::StartEncoding().
   //    - Depending on the encoder used, this method can require up to three seconds to complete.
   //
   virtual HRESULT __stdcall PrepareStream() = 0;

};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents a muxer stream in a workflow topology. 
// Remarks:
//    - This interface is used to multiplexe compressed video, audio, and VANC elementary streams into a single 
//      MPEG-2 program transport stream (SPTS) muxed buffer.
//    - Both the input and the output of this stream are compressed host nodes.
//    - The muxer stream can multiplexe compressed video and audio streams, or compressed video, audio, and VANC streams.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvMuxerStream : public IMvStream
{
   //
   // Summary:
   //   Gets the current settings of the muxer stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetMuxerStreamSettings
      (
      uint64_t& out_rui64Timestamp,					// Indicates the time that the muxer stream settings were activated.
      SMvMuxerStreamSettings& io_rsStreamSettings	// Structure that receives the muxer stream settings.
      ) = 0;

   //
   // Summary:
   //   Modifies the current settings of the muxer stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //
   virtual HRESULT __stdcall SetMuxerStreamSettings
      (
      uint64_t in_ui64Timestamp,						// Indicates the time that the modifications are to be made.
      const SMvMuxerStreamSettings& in_rsNewSettings	// Structure of the new muxer stream settings. The pointer will be used at the time
														// specified in in_ui64Timestamp.
      ) = 0;

   //
   // Summary:
   //   Gets the input compressed host node currently bound to the muxer stream containing compressed video.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetVideoInputNode
      (
      uint64_t&     out_rui64Timestamp,			// Indicates the time that the compressed host node was activated.
      IMvCompressedHostNode** out_ppIInputNode	// Pointer that receives the input compressed host node interface.
      ) = 0;

   //
   // Summary:
   //   Modifies the input compressed host node currently bound to the muxer stream containing compressed video. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //    - The new input compressed host node must have the same resolution and same memory location as the old input compressed host node.
   //    - The input compressed host node can only be changed when the encoder stream is stopped (IMvEncoderStream::StopEncoding()).
   //
   virtual HRESULT __stdcall SetVideoInputNode
      (
      uint64_t               in_ui64Timestamp,	// Indicates the time that the modifications are to be made.
      IMvCompressedHostNode* in_pIInputNode		// Pointer to the new input compressed host node interface. The pointer will be used at the time
												// specified in in_ui64Timestamp.
      ) = 0;

   //
   // Summary:
   //   Gets the input compressed host node currently bound to the muxer stream containing compressed audio.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetAudioInputNode
      (
      uint64_t&     out_rui64Timestamp,				// Indicates the time that the compressed host node was activated.
      IMvCompressedHostNode** out_ppIInputNode		// Pointer that receives the input compressed host node interface.
      ) = 0;

   //
   // Summary:
   //   Modifies the input compressed host node currently bound to the muxer stream containing compressed audio.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //    - The new input compressed host node must have the same resolution and same memory location as the old input compressed host node.
   //    - The input compressed host node can only be changed when the encoder stream is stopped (IMvEncoderStream::StopEncoding()).
   //
   virtual HRESULT __stdcall SetAudioInputNode
      (
      uint64_t               in_ui64Timestamp,	// Indicates the time that the modifications are to be made.
      IMvCompressedHostNode* in_pIInputNode		// Pointer to the new input compressed host node interface. The pointer will be used at the time
												// specified in in_ui64Timestamp.
      ) = 0;

   //
   // Summary:
   //   Gets the input compressed host node currently bound to the muxer stream containing compressed VANC. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetVancInputNode
      (
      uint64_t&     out_rui64Timestamp,				// Indicates the time that the compressed host node was activated.
      IMvCompressedHostNode** out_ppIInputNode		// Pointer that receives the input compressed host node interface.
      ) = 0;

   //
   // Summary:
   //   Modifies the input compressed host node currently bound to the muxer stream containing compressed VANC.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //    - The new input compressed host node must have the same resolution and same memory location as the old input compressed host node.
   //    - The input compressed host node can only be changed when the encoder stream is stopped (IMvEncoderStream::StopEncoding()).
   //
   virtual HRESULT __stdcall SetVancInputNode
      (
      uint64_t               in_ui64Timestamp,	// Indicates the time that the modifications are to be made.
      IMvCompressedHostNode* in_pIInputNode		// Pointer to the new input compressed host node interface. The pointer will be used at the time
												// specified in in_ui64Timestamp.
      ) = 0;

   //
   // Summary:
   //   Gets the output compressed host node currently bound to the muxer stream containing a single MPEG-2 program transport stream (SPTS) muxed buffer. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetOutputNode
      (
      uint64_t&               out_rui64Timestamp,	// Indicates the time that the compressed host node was activated.
      IMvCompressedHostNode** out_ppIOutputNode		// Pointer that receives the output compressed host node interface.
      ) = 0;

   //
   // Summary:
   //   Modifies the output compressed host node currently bound to the muxer stream containing a single MPEG-2 program transport stream (SPTS) muxed buffer. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //    - The new output compressed host node must have the same frame resolution and same memory location as the old output compressed host node.
   //    - The output compressed host node can only be changed when the encoder stream is stopped (IMvEncoderStream::StopEncoding()).
   //
   virtual HRESULT __stdcall SetOutputNode
      (
      uint64_t               in_ui64Timestamp,	// Indicates the time that the modifications are to be made.
      IMvCompressedHostNode* in_pIOutputNode	// Pointer to the new output compressed host node interface. The pointer will be used at the time
												// specified in in_ui64Timestamp.
      ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides information abour a transport stream.
// Remarks:
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvDemuxerMPEG2TSDecription : public IUnknown
{
   //
   // Summary:
   //   Gets the number of program stream found in the MPGEG2 transport stream.  
   // Return value:
   //    - An integer for IMvMPEG2TSDecription::GetProgramStreamInformation().
   //
   virtual uint32_t __stdcall GetProgramCount() = 0;

   //
   // Summary:
   //   Gets the information about a specific program stream found in a MPEG-2 transport stream.
   //
   virtual HRESULT  __stdcall GetProgramStreamInformation
      (
      uint32_t in_ui32PSIndex,                  // Indicates the index corresponding to the program stream.
      SMvDemuxerProgramStreamInfo & io_krsInfo  // Structure that receives the program stream information.
      ) = 0;

   //
   // Summary:
   //   Gets the information about a specific elementary stream found in a program stream.
   //
   virtual HRESULT  __stdcall GetElementaryStreamInformation
      (
      uint32_t in_ui32PSIndex,                     // Indicates the index corresponding to the program stream.
      uint32_t in_ui32ESIndex,                     // Indicates the index corresponding to the elementary stream.
      SMvDemuxerElementaryStreamInfo & io_krsInfo  // Structure that receives the elementary stream information.
      ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides a callback notification to inform of demuxer transport stream information changes.
// Remarks:
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvDemuxerStreamCallback : public IUnknown
{
   //
   // Summary:
   //    Notifies when transport stream format has changed.
   // Return value:
   //    - MV_NOERROR. 
   //
   virtual void __stdcall Notify
      (
      IMvDemuxerMPEG2TSDecription * in_pIDescription     // Interface providing the new description.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents a demuxer stream in a workflow topology. 
// Remarks:
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvDemuxerStream : public IMvStream
{
   //
   // Summary:
   //   Gets the input compressed host node currently bound to the demuxer stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetInputNode
      (
      IMvCompressedHostNode** out_ppIInputNode  // Pointer that receives the input compressed host node interface.
      ) = 0;

   // Summary: 
   //    Modifies the input compressed host node currently bound to the demuxer stream.
   // Return value: 
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetInputNode
      (
      IMvCompressedHostNode *in_pInputNode  // Pointer to the new input compressed host node interface.
      ) = 0;
   
   //
   // Summary: 
   //    Gets the currently settings of the demuxer stream.
   // Return value: 
   //    MV_NOERROR,  if completed successfully. 
   //
   virtual HRESULT __stdcall GetDemuxerSettings
      (
      SMvDemuxerStreamSettings &out_rSettings  //Structure of the demuxer stream settings.
      ) = 0;


   //
   // Summary:
   //    Modifies the current settings of the demuxer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   virtual HRESULT __stdcall SetDemuxerSettings
      (
      const SMvDemuxerStreamSettings & in_sSettings    // Structure of the demuxer stream settings.
      ) = 0;

   //
   // Summary:
   //    Registers a callback notification for a streams format detection change.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::AddRef method of the in_pICallback parameter is called when the notification is
   //      registered to prevent the object implementing the IMvDemuxerStreamCallback interface from being
   //      destroyed.
   //
   virtual HRESULT __stdcall RegisterCallbackForDetectionNotification
      (
      IMvDemuxerStreamCallback* in_pICallback // Pointer to the notification callback interface.
      ) = 0;

   //
   // Summary:
   //    Unregisters a callback notification for a streams format detection change.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - The IUnknown::Release method of the in_pICallback parameter is called when the notification is
   //      unregistered to remove the reference count added by the
   //      IMvDemuxerstream::RegisterCallbackForDetectionNotification.
   //
   virtual HRESULT __stdcall UnregisterCallbackForDetectionNotification
      (
      IMvDemuxerStreamCallback* in_pICallback // Pointer to the notification callback interface.
      ) = 0;

   //
   // Summary:
   //    Unregisters a callback notification for a streams format detection change.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - The IUnknown::Release method of the in_pICallback parameter is called when the notification is
   //      unregistered to remove the reference count added by the
   //      IMvDemuxerstream::RegisterCallbackForDetectionNotification.
   //
   virtual HRESULT __stdcall GetTransportStreamInformation
      (
      IMvDemuxerMPEG2TSDecription** out_ppIInfo    // Pointer that receive the interface to the information.
      ) = 0;

   //
   // Summary:
   //    Attach a node to a specific elementary stream of a specific program stream. The node will receive all 
   //    information pertaining to the specified elementary stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //
   virtual HRESULT __stdcall AttachNode
      (
      uint32_t in_ui32ProgramStreamIndex,       // Indicates the index corresponding to the program stream.
      uint32_t in_ui32ElementaryStreamIndex,    // Indicates the index corresponding to the elementary stream.
      IMvCompressedHostNode * in_pINode         // Pointer to the compressed host node interface to attach.
      ) = 0;

   //
   // Summary:
   //    Detach a node from its elementary stream. The node will not receive any data from the demuxer stream anymore.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //
   virtual HRESULT __stdcall DetachNode
      (
      IMvCompressedHostNode * in_pINode   // Pointer to the compressed host node interface to detach.
      ) = 0;

   //
   // Summary:
   //    Return all the nodes that are attached to an elementary stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //
   virtual HRESULT __stdcall GetAttachNodes
      (
      uint32_t & io_ui32AttachedNodeCount,         // In input, maximum number of items in the array out_aAttachedNodes. 
                                                   // Receives the number of item in the array.
      SMvDemuxerAttachedNode out_aAttachedNodes[]  // Pointer to an array of SMvDemuxerAttachedNode.
      ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents an echo stream in a workflow topology. 
// Remarks:
//    - This interface is used to propagate data without altering the data.
//    - Both the input and the output of this stream are nodes. However, one is a host node and the other a compressed host node.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvEchoStream : public IMvStream
{
   //
   // Summary:
   //   Gets the current settings of the echo stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetEchoStreamSettings
      (
      uint64_t& out_rui64Timestamp,					// Indicates the time that the echo stream settings were activated.
      SMvEchoStreamSettings& io_rsStreamSettings	// Structure that receives the echo stream settings.
      ) = 0;

   //
   // Summary:
   //   Modifies the current settings of the echo stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //
   virtual HRESULT __stdcall SetEchoStreamSettings
      (
      uint64_t in_ui64Timestamp,						// Indicates the time that the modifications are to be made.
      const SMvEchoStreamSettings& in_rsNewSettings		// Structure of the new echo stream settings. The pointer will be used at the time
														// specified in in_ui64Timestamp.
      ) = 0;

   //
   // Summary:
   //   Gets the input node currently bound to the echo stream.   
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If the input node is a host node, then the output node must be a compressed host node, and vice-versa.
   //
   virtual HRESULT __stdcall GetInputNode
      (
      uint64_t&   out_rui64Timestamp,	// Indicates the time that the node was activated.
      IMvNode**   out_ppIInputNode		// Pointer that receives the input node interface.
      ) = 0;

   //
   // Summary:
   //   Modifies the input node currently bound to the echo stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //    - The new input node must have the same resolution and same memory location as the old input node.
   //    - The input node can be changed even after the echo stream is started.
   //
   virtual HRESULT __stdcall SetInputNode
      (
      uint64_t    in_ui64Timestamp,		// Indicates the time that the modifications are to be made.
      IMvNode*    in_pIInputNode		// Pointer to the new input node interface. The pointer will be used at the time
										// specified in in_ui64Timestamp.
      ) = 0;

   //
   // Summary:
   //   Gets the output node currently bound to the echo stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If the output node is a host node, then the input node must be a compressed host node, and vice-versa.
   //
   virtual HRESULT __stdcall GetOutputNode
      (
      uint64_t&         out_rui64Timestamp,		// Indicates the time that the node was activated.
      IMvNode**         out_ppIOutputNode		// Pointer that receives the output node interface.
      ) = 0;

   //
   // Summary:
   //   Modifies the output node currently bound to the echo stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //    - The new output node must have the same frame resolution and same memory location as the old output node.
   //    - The output node can only be changed when the echo stream is stopped.
   //
   virtual HRESULT __stdcall SetOutputNode
      (
      uint64_t    in_ui64Timestamp,		// Indicates the time that the modifications are to be made.
      IMvNode*    in_pIOutputNode		// Pointer to the new output node interface. The pointer will be used at the time
										// specified in in_ui64Timestamp.
      ) = 0;

   //
   // Summary:
   //   Starts the echo stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This method must be called after calling IMvEchoStream::PrepareStreamForEcho().
   //
   virtual HRESULT __stdcall StartEchoing
      (
      uint64_t in_ui64Timestamp		// Indicates the time to start echoing.
      ) = 0;

   //
   // Summary:
   //   Stops the echo stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Because StopEchoing() is asynchronous, sufficient time must be allowed for StopEchoing() to complete its operation 
   //      before calling PrepareStreamForEcho() again. The recommended time to wait is between 25 and 50 frames.
   //
   virtual HRESULT __stdcall StopEchoing
      (
      uint64_t in_ui64Timestamp		// Indicates the time to stop echoing.
      ) = 0;

   //
   // Summary:
   //    Configures the echo stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This method is synchronous and must be called before calling IMvEchoStream::StartEchoing().
   //
   virtual HRESULT __stdcall PrepareStreamForEcho() = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Base interface that provides the settings and GUID identifying the encoder used. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvEncoderStreamSettingsCallback : public IUnknown
{
   //
   // Summary:
   //   Gets the GUID identifying the encoder used by the stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetEncoderGuid
      (
      GUID & out_rsEncoderGuid	// Indicates the GUID corresponding to the encoder used.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to obtain the Matrox H.264/AVC hardware encoder settings. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvH264HwVideoSettingsCallback : public IMvEncoderStreamSettingsCallback
{
   //
   // Summary:
   //   Gets the Matrox H.264/AVC hardware encoder settings.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetSettings
      (
         SMvAVCCompressionOptionsV5 & out_rsSettings	// Structure that receives the Matrox H.264/AVC hardware encoder settings.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to obtain the Matrox H.264/AVC QSV encoder settings. 
// Remarks:
//    - To use the Matrox H.264/AVC QSV encoder, your computer must have an Intel processor with integrated QSV.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvH264VideoSettingsCallback : public IMvEncoderStreamSettingsCallback
{
   //
   // Summary:
   //   Gets the Matrox H.264/AVC QSV encoder settings.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetSettings
      (
      SMvH264CompressionOptions & out_rsSettings	// Structure that receives the Matrox H.264/AVC QSV encoder settings.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to obtain the Apple ProRes encoder settings. 
// Remarks:
//    - A license agreement with Apple is required in order to support the ProRes clips in your application. 
//      For more information about using Apple ProRes, please contact your Matrox sales representative.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvProResVideoSettingsCallback : public IMvEncoderStreamSettingsCallback
{
   //
   // Summary:
   //   Gets the Apple ProRes encoder settings.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetSettings
      (
      SMvProResCompressionOptions & out_rsSettings	// Structure that receives the Apple ProRes encoder settings.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to obtain the Matrox H.264/AVC hardware encoder settings. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvM264H264VideoSettingsCallback : public IMvEncoderStreamSettingsCallback
{
   //
   // Summary:
   //   Gets the Matrox H.264/AVC hardware encoder settings.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetSettings
      (
      SMvAVCCompressionOptionsV5 & out_rsSettings	// Structure that receives the Matrox H.264/AVC hardware encoder settings.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to obtain the Matrox AVC-Intra encoder settings. 
// Remarks:
//    - An 8-core system is required to achieve optimal compression performance. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvAVCIntraVideoSettingsCallback : public IMvEncoderStreamSettingsCallback
{
   //
   // Summary:
   //   Gets the Matrox AVC-Intra encoder settings.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetSettings
      (
      SMvAVCIntraCompressionOptions & out_rsSettings	// Structure that receives the Matrox AVC-Intra encoder settings.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to obtain the Matrox MPEG-2 I-frame encoder settings. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvMPEG2IFrameVideoSettingsCallback : public IMvEncoderStreamSettingsCallback
{
   //
   // Summary:
   //   Gets the Matrox MPEG-2 I-frame encoder settings.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetSettings
      (
      SMvMpeg2CompressionOptions & out_rsSettings	// Structure that receives the Matrox MPEG-2 I-frame encoder settings.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to obtain the Avid DNxHD encoder settings. 
// Remarks:
//    - A license agreement with Avid is required in order to support DNxHD clips in your application. 
//      For more information about using DNxHD, please contact your Matrox sales representative.
//      To acquire the DNxHD license agreement, contact Avid Technology at avidDNxHD@avid.com.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvDNxHDVideoSettingsCallback : public IMvEncoderStreamSettingsCallback
{
   //
   // Summary:
   //   Gets the Avid DNxHD encoder settings.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetSettings
      (
      SMvDNxHDCompressionOptions & out_rsSettings	// Structure that receives the Avid DNxHD encoder settings.
      ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to obtain the Matrox MPEG-2 IBP encoder settings.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvMPEG2IBPVideoSettingsCallback : public IMvEncoderStreamSettingsCallback
{
   //
   // Summary:
   //   Gets the Matrox MPEG-2 IBP encoder settings.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetSettings
      (
      SMvMPEG2IBPCompressionOptions & out_rsSettings	// Structure that receives the Matrox MPEG-2 IBP encoder settings.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to obtain the Matrox DV100 encoder settings. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvDV100VideoSettingsCallback : public IMvEncoderStreamSettingsCallback
{
   //
   // Summary:
   //   Gets the Matrox DV100 encoder settings.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetSettings
      (
      SMvDV100CompressionOptions & out_rsSettings	// Structure that receives the Matrox DV100 encoder settings.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to obtain the Matrox MPEG-4 Simple Studio Profile (SStP) encoder settings. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvMPEG4SStPVideoSettingsCallback : public IMvEncoderStreamSettingsCallback
{
   //
   // Summary:
   //   Gets the Matrox MPEG-4 SStP encoder settings.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetSettings
      (
      SMvMPEG4SStPCompressionOptions & out_rsSettings	// Structure that receives the Matrox MPEG-4 SStP encoder settings.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to obtain the Matrox H264 SW2 encoder settings. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvH264SW2VideoSettingsCallback : public IMvEncoderStreamSettingsCallback
{
   virtual HRESULT __stdcall GetSettings
      (
      void  * out_psSettings
      ) = 0;

   virtual HRESULT __stdcall GetPreset
      (
      uint32_t & out_rui32Preset
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to obtain the Matrox M264 encoder settings. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvM264VideoSettingsCallback : public IMvEncoderStreamSettingsCallback
{
   virtual HRESULT __stdcall GetSettings
      (
      void  * out_psSettings
      ) = 0;

   virtual HRESULT __stdcall GetPreset
      (
      uint32_t & out_rui32Preset
      ) = 0;
};
//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to obtain the Matrox AAC audio encoder settings. 
// Remarks:
//    - 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvAACAudioSettingsCallback : public IMvEncoderStreamSettingsCallback
{
   //
   // Summary:
   //   Gets the Matrox AAC audio encoder settings.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetSettings
      (
      SMvAACCompressionOptions & out_rsSettings		// Structure that receives the Matrox AAC audio encoder settings.
      ) = 0;

};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to obtain PCM audio settings.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvPCMAudioSettingsCallback : public IMvEncoderStreamSettingsCallback
{
   //
   // Summary:
   //   Gets the PCM audio settings.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetSettings
      (
      SMvPCMCompressionOptions & out_rsSettings		// Structure that receives the PCM audio settings.
      ) = 0;

};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to obtain the Minnetonka SurCode for Dolby E encoder settings. 
// Remarks:
//    - A license agreement with Minnetonka Audio Software Inc. is required in order to use the 
//      SurCode for Dolby E encoder in your application. For more information about using the 
//      SurCode for Dolby E encoder, please contact your Matrox sales representative. For details on how 
//      to obtain the required license agreement, contact Minnetonka Audio Software at contact@minnetonkaaudio.com.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvMinnetonkaDolbyAudioSettingsCallback : public IMvEncoderStreamSettingsCallback
{

};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to monitor the writer stream for specific events, such as  
//    when a new frame is captured, when a file is opened or closed, or when an error occurred. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvWriterStreamEventCallback : public IUnknown
{
   //
   // Summary:
   //   Allows the user application to enable or disable notifications for writer stream events.  
   // Return value:
   //    - Use MV_TRUE to enable notifications for the writer stream event. 
   //    - Use MV_FALSE to disable notifications for the writer stream event. 
   //
   virtual HRESULT __stdcall EnableNotificationsForEvent
      (
      EMvWriterStreamEvent in_eEvent   // Indicates the writer stream event to monitor.
      ) = 0;
   //
   // Summary:
   //   Notifies the user application of the writer stream event that occurred. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall NotifyWriterStreamEvent
      (
      const SMvWriterStreamEvent & in_krsEvent  // Structure of the writer stream event.
      ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to verify the writer stream's settings. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvWriterStreamValidator : public IUnknown
{
   //
   // Summary:
   //   Gets the errors encountered when validating the writer stream settings.  
   // Remarks:
   //    - Although an error is not returned, use IMvWriterStreamValidator::GetNumberOfValidationWarnings() to verify if any warnings have been encountered.
   // Return value:
   //    - MV_TRUE, if at least one setting was modified. Otherwise, MV_FALSE is returned.
   //
   virtual HRESULT __stdcall GetValidationError
      (
      ) = 0;

   //
   // Summary:
   //   Gets the number of warnings encountered when validating the writer stream settings.  
   // Remarks:
   //    - Use this method to determine if any warnings have been encountered even if IMvWriterStreamValidator::GetValidationError() does not return any errors.
   //
   virtual int32_t __stdcall GetNumberOfValidationWarnings
      (
      ) = 0;

   //
   // Summary:
   //   Gets the warnings encountered when validating the writer stream settings. 
   // Return value:
   //    - MV_E_OUT_OF_RANGE, if the index is out of range.
   //
   virtual HRESULT __stdcall GetWarning
      (
      int32_t in_i32Index  // Indicates the index corresponding to the warning encountered.
      ) = 0;

   //
   // Summary:
   //   Gets the current settings of the writer stream. 
   // Return value:
   //    - MV_TRUE, if at least one setting was modified. Otherwise, MV_FALSE is returned.
   //
   virtual HRESULT __stdcall GetWriterStreamSettings
      (
      SMvWriterStreamSettings& io_rsStreamSettings    // Structure that receives the writer stream settings.
      ) = 0;

   //
   // Summary:
   //   Gets the video, audio, and VANC settings for the node.  
   // Return value:
   //    - MV_TRUE, if at least one setting was modified. Otherwise, MV_FALSE is returned.
   //
   virtual HRESULT __stdcall GetNodeStreamSettings
      (
      SMvNodeSettingsVideo   & io_sVideoSettings,  // Structure that receives the node's video settings.
      SMvNodeSettingsAudio   & io_sAudioSettings,  // Structure that receives the node's audio settings.
      SMvNodeSettingsVanc    & io_sVancSettings    // Structure that receives the node's VANC settings.
      ) = 0;
   
   //
   // Summary:
   //   Gets the video and audio encoder stream settings callback interfaces.  
   // Return value:
   //    - MV_TRUE, if at least one setting was modified. Otherwise, MV_FALSE is returned.
   // 
   virtual HRESULT __stdcall GetEncoderStreamSettingsCallback
      (
      IMvEncoderStreamSettingsCallback ** out_ppIVideoCodecSettings,    // Pointer that receives the video encoder stream settings callback interface.
      IMvEncoderStreamSettingsCallback ** out_ppIAudioCodecSettings     // Pointer that receives the audio encoder stream settings callback interface.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to validate all the writer stream settings using the IMvWriterStreamValidator interface. 
// Remarks:
//    - If there is an error, it will be returned through the IMvWriterStreamValidator interface.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvWriterStreamValidationFactory : public IUnknown
{
   //
   // Summary:
   //   Gets the validation error code from the IMvWriterStreamValidator interface for all the writer stream settings. 
   //
   virtual HRESULT __stdcall GetWriterStreamValidator
      (
      const GUID &                        in_krguidWriterStream,           // GUID used to create the writer stream.
      IMvHostNode *                       in_pIInputNode,                  // Pointer to the host node interface.
      const SMvWriterStreamSettings &     in_krsSettings,                  // Structure of the writer stream settings.
      IMvEncoderStreamSettingsCallback*   in_pIVideoCodecSettings,         // Pointer to the video encoder stream settings callback interface.
      IMvEncoderStreamSettingsCallback*   in_pIAudioCodecSettings,         // Pointer to the audio encoder stream settings callback interface.
      IMvWriterStreamValidator**          out_ppIMvWriterStreamValidator,  // Pointer that receives the writer stream validator interface.
      HRESULT &                           out_hr                           // Error code returned by the writer stream validator interface.
      ) = 0;
   
   //
   // Summary:
   //   Gets the validation error code from the IMvWriterStreamValidator interface for all the writer stream settings. 
   // Remarks:
   //   - This method is used to validate the writer stream settings before the host node is created.
   //
   virtual HRESULT __stdcall GetWriterStreamValidator
      (
      const GUID &                        in_krguidWriterStream,           // GUID used to create the writer stream.
      SMvNodeSettingsVideo&               in_rsNodeVideoSettings,          // Structure of the host node's video settings.
      SMvNodeSettingsAudio&               in_rsNodeAudioSettings,          // Structure of the host node's audio settings.
      SMvNodeSettingsVanc&                in_reNodeVancSettings,           // Structure of the host node's VANC settings.
      const SMvWriterStreamSettings &     in_krsSettings,                  // Structure of the writer stream settings.
      IMvEncoderStreamSettingsCallback*   in_pIVideoCodecSettings,         // Pointer to the video encoder stream settings callback interface.
      IMvEncoderStreamSettingsCallback*   in_pIAudioCodecSettings,         // Pointer to the audio encoder stream settings callback interface.
      IMvWriterStreamValidator**          out_ppIMvWriterStreamValidator,  // Pointer that receives the writer stream validator interface.
      HRESULT &                           out_hr                           // Error code returned by the writer stream validator interface.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to create the encoder stream settings callback interface. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvEncoderStreamSettingsCallbackFactory : public IUnknown
{
   //
   // Summary:
   //   Creates the encoder stream settings callback interface.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateEncoderSettingsCallback
      (
      const GUID &                        in_krEncoderStreamSettingsGUID,	// Indicates the encoder GUID identifier.
      uint32_t                            in_ui32SettingsSize,				// Indicates the size of the encoder settings structure.
      void                              * in_pSettings,						// Pointer to the encoder settings structure.        
      IMvEncoderStreamSettingsCallback ** out_ppIMvCallbackSettings	// Pointer that receives the encoder stream settings callback interface.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents a writer stream in a workflow topology. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvWriterStream : public IMvStream
{
   //
   // Summary:
   //   Gets the current settings of the writer stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetWriterStreamSettings
      (
      SMvWriterStreamSettings& io_rsStreamSettings    // Structure that receives the writer stream settings.
      ) = 0;

   //
   // Summary:
   //   Modifies the current settings of the writer stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetWriterStreamSettings
      (
      const SMvWriterStreamSettings& in_rsNewSettings // Structure of the new writer stream settings.
      ) = 0;

   //
   // Summary:
   //   Gets the input host node currently bound to the writer stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetInputNode
      (
      uint64_t&     out_rui64Timestamp,   // Indicates the time that the host node was activated.
      IMvHostNode** out_ppIInputNode      // Pointer that receives the input host node interface.
      ) = 0;

   //
   // Summary:
   //   Modifies the input host node currently bound to the writer stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //    - The new input host node must have the same resolution and same memory location as the old input host node.
   //    - The input host node can be changed even after the writer stream is started.
   //
   virtual HRESULT __stdcall SetInputNode
      (
      uint64_t     in_ui64Timestamp,   // Indicates the time that the modifications are to be made.
      IMvHostNode* in_pIInputNode      // Pointer to the new input host node interface. The pointer will be used at the time specified in in_ui64Timestamp.
      ) = 0;

   //
   // Summary:
   //   Gets the current video encoder stream settings callback interface.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetVideoCodecSettingsInterface
      (
      IMvEncoderStreamSettingsCallback ** out_ppICodecSettings    // Pointer that receives the video encoder stream settings callback interface.
      ) = 0;

   //
   // Summary:
   //   Modifies the current video encoder stream settings callback interface.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetVideoCodecSettingsInterface
      (
      IMvEncoderStreamSettingsCallback * in_pICodecSettings  // Pointer to the video encoder stream settings callback interface.
      ) = 0;

   //
   // Summary:
   //   Gets the current audio encoder stream settings callback interface.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetAudioCodecSettingsInterface
      (
      IMvEncoderStreamSettingsCallback ** out_ppICodecSettings    // Pointer that receives the audio encoder stream settings callback interface.
      ) = 0;

   //
   // Summary:
   //   Modifies the current audio encoder stream settings callback interface.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetAudioCodecSettingsInterface
      (
      IMvEncoderStreamSettingsCallback * in_pICodecSettings    // Pointer to the audio encoder stream settings callback interface.
      ) = 0;

   //
   // Summary:
   //   Starts the writer stream capture.  
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_ALREADY_IN_USE, if the writer stream is already in progress. 
   // Remarks:
   //    - The file must not already exist. Otherwise, an error will occur.
   //    - To switch capturing to a new file seamlessly, Start() can be called again while the current file is being captured to
   //      allow the writer stream to prepare the next file. However, the writer stream can only prepare one file at a time in advance. (See example 1.)
   //    - To capture to a new file at regular intervals, the user application must wait for the notification keMvWriterStreamEventFileOpened
   //      before calling Start() again. As well, because the writer stream can only prepare one file at a time in advance, it must wait for
   //      the notification keMvWriterStreamEventFileClosed before it can prepare the next file. (See example 2.)
   //    - To capture to more than one file at the same time, create a witer stream for each file type that you would like to capture to. For example,
   //      you can capture to MOV and MXF files at the same time by creating MOV and MXF writer streams.
   // Example:
   //    <CODE>
   //    pJWriterStream->Start(12:00:00, fileA);      
   //    pJWritererStream->Start(12:10:00, fileB);   // Before calling Start(12:10:00, fileB), wait for the notification keMvWriterStreamEventStarted from fileA. Otherwise, MV_E_ALREADY_IN_USE will be returned.
   //    </CODE>
   //
   // Example:
   //    <CODE>
   //    pJWriterStream->Start(12:00:00, fileA);  
   //    pJWriterStream->Start(12:10:00, fileB);   // Before calling Start(12:10:00, fileB), wait for the notification keMvWriterStreamEventStarted from fileA. Otherwise, MV_E_ALREADY_IN_USE will be returned.
   //    pJWriterStream->Start(12:20:00, fileC);   // Before calling Start(12:20:00, fileC), wait for the notification keMvWriterStreamEventStarted from fileB. Otherwise, MV_E_ALREADY_IN_USE will be returned.
   //    </CODE>
   //
   virtual HRESULT __stdcall Start
      (
      uint64_t        in_ui64Timestamp,   // Indicates the time at which the first frame will be captured.
      const wchar_t * in_kwszFilename     // Indicates the file name the writer stream captures data to.
      ) = 0;

   virtual HRESULT __stdcall PrepareCapture
      (
      const wchar_t * in_kwszFilename     // Indicates the file name the writer stream captures data to.
      ) = 0;

   virtual HRESULT __stdcall Capture
      (
      uint64_t        in_ui64Timestamp   // Indicates the time at which the first frame will be captured.
      ) = 0;

   //
   // Summary:
   //   Stops the writer stream capture.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If the time stamp is less than the current time, the writer stream stops immediately.
   //    - Any previously issued command with a time stamp equal to or greater than the stop command's time stamp will be canceled. 
   //
   virtual HRESULT __stdcall Stop
      (
      uint64_t	in_ui64StopTime  // Indicates the time at which to stop the capture.
      ) = 0;

   //
   // Summary:
   //   Registers an event callback for the writer stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::AddRef method of the in_pICallback parameter is called when the event callback is registered 
   //      to prevent the object implementing the IMvWriterStreamEventCallback() interface from being destroyed.
   //
   virtual HRESULT __stdcall RegisterEventCallback
      (
      IMvWriterStreamEventCallback * in_pICallback   // Pointer to the writer stream event callback interface.
      ) = 0;

   //
   // Summary:
   //    Unregisters an event callback for the writer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::Release method of the in_pICallback parameter is called when the event callback is unregistered 
   //      to remove the reference count added by IMvWriterStream::RegisterEventCallback().
   //
   virtual HRESULT __stdcall UnregisterEventCallback
      (
      IMvWriterStreamEventCallback * in_pICallback   // Pointer to the writer stream event callback interface.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to load a writer stream from an .xml file. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvWriterStreamLoaderHelper : public IUnknown
{
   //
   // Summary:
   //   Provides the writer stream with the file name to use when creating an .xml file.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetFilename
      (
      const wchar_t * in_kwszFilename  // File name used by the writer stream to write to the .xml file.
      ) = 0;

   //
   // Summary:
   //   Gets the file name the writer stream will capture to.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetFilename
      (
      wchar_t *         out_wszFilename,  // File name the writer stream will capture to.
      uint16_t          in_ui16MaxLength  // Indicates the maximum number of characters the file name (out_wszFilename) can contain.
      ) = 0;

   //
   // Summary:
   //   Gets the video and audio encoder settings callback interface.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetEncoderStreamSettingsCallback
      (
      IMvEncoderStreamSettingsCallback   ** out_ppIVideoCodecSettings,  // Pointer that receives the video encoder settings callback interface.
      IMvEncoderStreamSettingsCallback   ** out_ppIAudioCodecSettings   // Pointer that receives the audio encoder settings callback interface.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to load a compressed writer stream from an .xml file. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvCompressedWriterStreamLoaderHelper : public IUnknown
{
   //
   // Summary:
   //   Gets the file name the compressed writer stream will capture to.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetFilename
      (
      wchar_t *         out_wszFilename,  // File name the compressed writer stream will capture to.
      uint16_t          in_ui16MaxLength  // Indicates the maximum number of characters the file name (out_wszFilename) can contain.
      ) = 0;

   //
   // Summary:
   //   Gets the GUID that was used to create the compressed writer stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetGUID
      (
      GUID *         out_pGUID   // Pointer to the GUID that was used to create the compressed writer stream.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents a compressed writer stream in a workflow topology. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvCompressedWriterStream : public IMvStream
{
   //
   // Summary:
   //   Modifies the file name the compressed writer stream captures to.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The file must not already exist. Otherwise, an error will occur.
   //
   virtual HRESULT __stdcall SetFilename
      (
      const wchar_t * in_kwszFilename  // Pointer to the string containing the file name the compressed writer stream will use to capture data to.
      ) = 0;

   //
   // Summary:
   //   Gets the current settings of the compressed writer stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetCompressedWriterStreamSettings
      (
      SMvCompressedWriterStreamSettings& io_rsStreamSettings   // Structure that receives the compressed writer stream settings.
      ) = 0;

   //
   // Summary:
   //   Gets the input compressed host node containing compressed audio currently bound to the compressed writer stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetAudioInputNode
      (
      IMvCompressedHostNode** out_ppIAudioInputNode   // Pointer that receives the input compressed host node interface containing compressed audio data.
      ) = 0;

   //
   // Summary:
   //   Gets the input compressed host node containing compressed video currently bound to the compressed writer stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetVideoInputNode
      (
      IMvCompressedHostNode** out_ppIVideoInputNode   // Pointer that receives the input compressed host node interface containing compressed video data.
      ) = 0;

   //
   // Summary:
   //   Modifies the input compressed host node containing compressed audio currently bound to the compressed writer stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The new input compressed host node must have the same resolution and same memory location as the old input compressed host node.
   //
   virtual HRESULT __stdcall SetAudioInputNode
      (
      IMvCompressedHostNode* in_pIAudioInputNode   // Pointer to the new input compressed host node interface containing compressed audio data.
      ) = 0;

   //
   // Summary:
   //   Modifies the input compressed host node containing compressed video currently bound to the compressed writer stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The new input compressed host node must have the same resolution and same memory location as the old input compressed host node.
   //
   virtual HRESULT __stdcall SetVideoInputNode
      (
      IMvCompressedHostNode* in_pIVideoInputNode   // Pointer to the new input compressed host node interface containing compressed video data.
      ) = 0;
};
//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to further configure the writer stream when capturing MOV files. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvMOVWriterStream : public IUnknown
{
   //
   // Summary:
   //   Modifies the next reference file name the MOV writer stream will use when capturing in TDIR mode.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetNextReferenceName
      (
      const wchar_t * in_kwszReferenceFilename  // Reference file name the MOV writer stream will use when capturing in TDIR mode.
      ) = 0;

   //
   // Summary:
   //   Gets the next reference file name the MOV writer stream will use when capturing in TDIR mode.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetNextReferenceName
      (
      wchar_t *         out_wszReferenceFilename,  // Reference file name the MOV writer stream will use when capturing in TDIR mode.
      uint32_t          in_ui32NbOfDestCharacters  // Indicates the number of characters the reference file name (out_wszReferenceFilename) can contain.
      ) = 0;

   //
   // Summary:
   //   Gets the current settings of the MOV writer stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetMOVWriterStreamSettings
      (
      uint64_t& out_rui64Timestamp,                      // Indicates the time that the MOV writer stream settings were activated.
      SMvMOVWriterStreamSettings& io_rsStreamSettings    // Structure that receives the MOV writer stream settings.
      ) = 0;

   //
   // Summary:
   //   Modifies the current settings of the MOV writer stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //
   virtual HRESULT __stdcall SetMOVWriterStreamSettings
      (
      uint64_t in_ui64Timestamp,                            // Indicates the time that the modifications are to be made.
      const SMvMOVWriterStreamSettings& in_krsNewSettings   // Structure of the MOV writer stream.
      ) = 0;

   //
   // Summary:
   //   Gets the default MOV writer stream settings.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetDefaultMOVWriterStreamSettings
      (
      SMvMOVWriterStreamSettings& io_rsDefaultSettings   // Structure that receives the default settings of the MOV writer stream.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to further configure the writer stream when capturing MP4 files.  
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvMP4WriterStream : public IUnknown
{
   //
   // Summary:
   //   Modifies the next reference file name the MP4 writer stream will use when capturing in TDIR mode.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetNextReferenceName
      (
      const wchar_t * in_kwszReferenceFilename  // Reference file name the MP4 writer stream will use when capturing in TDIR mode.
      ) = 0;

   //
   // Summary:
   //   Gets the next reference file name the MP4 writer stream will use when capturing in TDIR mode.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetNextReferenceName
      (
      wchar_t *         out_wszReferenceFilename,  // Reference file name the MP4 writer stream will use when capturing in TDIR mode.
      uint32_t          in_ui32NbOfDestCharacters  // Indicates the number of characters the reference file name (out_wszReferenceFilename) can contain.
      ) = 0;

   //
   // Summary:
   //   Gets the current settings of the MP4 writer stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetMP4WriterStreamSettings
      (
      uint64_t& out_rui64Timestamp,                   // Indicates the time that the MP4 writer stream settings were activated.
      SMvMP4WriterStreamSettings& io_rsStreamSettings // Structure that receives the MP4 writer stream settings.
      ) = 0;

   //
   // Summary:
   //   Modifies the current settings of the MP4 writer stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //
   virtual HRESULT __stdcall SetMP4WriterStreamSettings
      (
      uint64_t in_ui64Timestamp,                            // Indicates the time that the modifications are to be made.
      const SMvMP4WriterStreamSettings& in_krsNewSettings   // Structure of the MP4 writer stream.
      ) = 0;

   //
   // Summary:
   //   Gets the default MP4 writer stream settings.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetDefaultMP4WriterStreamSettings
      (
      SMvMP4WriterStreamSettings& io_rsDefaultSettings   // Structure that receives the default settings of the MP4 writer stream.
      ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to further configure the writer stream when capturing MXF files. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvMXFWriterStream : public IUnknown
{
   //
   // Summary:
   //   Gets the current settings of the MXF writer stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetMXFWriterStreamSettings
      (
      uint64_t& out_rui64Timestamp,                   // Indicates the time that the MXF writer stream settings were activated.
      SMvMXFWriterStreamSettings& io_rsStreamSettings // Structure that receives the MXF writer stream settings.
      ) = 0;

   //
   // Summary:
   //   Modifies the current settings of the MXF writer stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //
   virtual HRESULT __stdcall SetMXFWriterStreamSettings
      (
      uint64_t in_ui64Timestamp,                            // Indicates the time that the modifications are to be made.
      const SMvMXFWriterStreamSettings& in_krsNewSettings   // Structure of the MXF writer stream.
      ) = 0;

   //
   // Summary:
   //   Gets the default MXF writer stream settings.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetDefaultMXFWriterStreamSettings
      (
      SMvMXFWriterStreamSettings& io_rsDefaultSettings   // Structure that receives the default settings of the MXF writer stream.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to further configure the writer stream when capturing P2 MXF files. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvP2MXFWriterStream : public IUnknown
{
   //
   // Summary:
   //   Gets the number of audio channels that will be captured.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetAudioStreamCount
      (
      uint32_t &out_ui32StreamCount    // Indicates the number of audio channels to capture.
      ) = 0;

   //
   // Summary:
   //   Sets the number of audio channels to capture.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_UNSUPPORTED_AUDIO_CHANNEL_TYPE, if the audio channel type is not supported.
   //
   virtual HRESULT __stdcall SetAudioStreamCount
   (
      uint32_t in_ui32StreamCount   // Indicates the number of audio channels to capture.
   ) = 0;

   //
   // Summary:
   //   Indicates the audio data file name the P2 MXF writer stream will use.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall AddAudioStreamName
      (
      uint32_t in_ui32Index,                       // Indicates the index corresponding to an audio channel.
      const wchar_t * in_kwszAudioStreamFilename   // File name containing the audio data for the corresponding audio channel.
      ) = 0;

};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used by the reader stream to indicate when files are ready to be played. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvReaderStreamPreparePlayObserver : public IUnknown
{
   //
   // Summary:
   //   Notifies the reader stream when files are ready to be played.   
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall NotifyPreparePlay
      (
      IMvReaderStream *        in_pIMvReaderStream,         // Pointer to the reader stream interface.
      IMvReaderStreamElement * in_pIMvReaderStreamElement,  // Pointer to the interface containing information about the video and audio files used by the reader stream.
      HRESULT                  in_hr                        // If an error occurs, indicates the corresponding error code.
      ) = 0; 
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used by the reader stream to retrieve information about the video and audio files. 
// Remarks:
//    - The file used can contain video only, or video and audio only.
//    - If the file contains video only, it can be streamed with several audio files.
//    - If the file contains video and audio, the audio data contained in the file does not have to be streamed. A combination of files can be used
//      to provide the audio data. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvReaderStreamElement : public IUnknown
{
   //
   // Summary:
   //   Gets the video file information used by the reader stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - If the video file contains audio, the same file must be used in SMvReaderStreamVideoInformation and SMvReaderStreamAudioInformation.
   //      However, you do not have to stream the audio data.
   //
   virtual HRESULT  __stdcall GetVideoFile
      (
      SMvReaderStreamVideoInformation & out_rsVideoInformation // Structure that receives the video information about the video file to be used by the reader stream.
      ) = 0;

   //
   // Summary:
   //   Gets the number of audio files that will be played back.  
   // Return value:
   //    - An integer for IMvReaderStreamElement::GetAudioFile().
   //
   virtual int32_t __stdcall GetAudioFileCount() = 0;

   //
   // Summary:
   //   Gets the audio file information used by the reader stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - The number of audio channels for each file must be 1, 2, 4, 8, or 16.
   //    - The total number of audio channels must be 1, 2, 4, 8, or 16.
   //    - If total number of audio channels is less than what the host node expects, channels containing silence are added.
   //    - If total number of audio channels is more than what the host node expects, the extra channels are dropped.
   //
   virtual HRESULT  __stdcall GetAudioFile
      (
      int32_t in_i32Index,                                        // Index value for the next audio file to play.
      SMvReaderStreamAudioInformation & out_rsAudioInformation    // Structure that receives the audio information about the audio file to be used by the reader stream.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used by the reader stream to modify the video and audio file information. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvReaderStreamElementSetter : public IMvReaderStreamElement
{
   //
   // Summary:
   //   Modifies the video file information used by the reader stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT  __stdcall SetVideoFile
      (
      const SMvReaderStreamVideoInformation & in_rsVideoInformation  // Structure of the video information about the audio file.
      ) = 0;

   //
   // Summary:
   //   Updates and resets the SMvReaderStreamVideoInformation and SMvReaderStreamAudioInformation structures.  
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall Reset() = 0;

   //
   // Summary:
   //   Modifies the audio file information used by the reader stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT  __stdcall AddAudioFile
      (
      const SMvReaderStreamAudioInformation & in_rsAudioInformation     // Structure of the audio information about the audio file.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to create a reader stream. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvReaderStreamElementFactory : public IUnknown
{
   //
   // Summary:
   //   Gets the reader stream element setter interface.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This method provides a way to create a reader stream element. The user application queries for the IMvReaderStreamElement interface after
   //      providing the IMvReaderStreamElementSetter with the video and audio file information.
   //
   virtual HRESULT __stdcall GetReaderStreamElementSetter  
      (
      IMvReaderStreamElementSetter ** out_ppReaderStreamElementSetter   // Pointer that receives the reader stream element setter interface.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to monitor the reader stream for specific events. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvReaderStreamEventCallback : public IUnknown
{
   //
   // Summary:
   //   Allows the user application to enable or disable notifications for reader stream events.  
   // Return value:
   //    - Use MV_TRUE to enable notifications for the reader stream event.
   //    - Use MV_FALSE to disable notifications for the reader stream event.
   //
   virtual HRESULT __stdcall EnableNotificationsForEvent
      (
      EMvReaderStreamEvent in_eEvent      // Indicates the reader stream event to monitor.
      ) = 0;

   //
   // Summary:
   //   Notifies the user application of the reader stream event that occurred. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall NotifyReaderStreamEvent
      (
      const SMvReaderStreamEvent & in_krsEvent  // Structure of the reader stream event.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents a reader stream in a workflow topology.
// Remarks:
//    - There are no restrictions to the order of the calls. This means that if the reader stream is in one state, 
//      it doesn't have to go into an intermediary state before transitioning to a different state. For example, 
//      if the reader stream is currently playing an element, it is possible to seek without having to stop, pause, 
//      or cancel the current state. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvReaderStream : public IMvStream
{
   //
   // Summary:
   //   Gets the current settings of the reader stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetReaderStreamSettings
      (
      uint64_t& out_rui64Timestamp,                   // Indicates the time that the reader stream settings were activated.
      SMvReaderStreamSettings& io_rsStreamSettings    // Structure that receives the reader stream settings.
      ) = 0;

   //
   // Summary:
   //   Modifies the current settings of the reader stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //
   virtual HRESULT __stdcall SetReaderStreamSettings
      (
      uint64_t in_ui64Timestamp,                         // Indicates the time that the modifications are to be made.
      const SMvReaderStreamSettings& in_rsNewSettings    // Structure of the new reader stream settings.
      ) = 0;

   //
   // Summary:
   //   Gets the output host node currently bound to the reader stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetOutputNode
      (
      uint64_t&     out_rui64Timestamp,   // Indicates the time that the host node was activated.
      IMvHostNode** out_ppIOutputNode     // Pointer that receives the output host node interface.
      ) = 0;

   //
   // Summary:
   //   Modifies the output host node currently bound to the reader stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //    - The new output host node must have the same resolution and same memory location as the old output host node.
   //    - The output host node can be changed even after the reader stream is started.
   //
   virtual HRESULT __stdcall SetOutputNode
      (
      uint64_t     in_ui64Timestamp,   // Indicates the time that the modifications are to be made.
      IMvHostNode* in_pIOutputNode     // Pointer to the new output host node interface. The pointer will be used at the time specified in in_ui64Timestamp.
      ) = 0;

   //
   // Summary:
   //   Prepares the files to play for the reader stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_WRONG_STATE, if a previous PreparePlay() is still being processed. 
   //    - MV_E_INVALID_PARAMETER, if the observer or element is invalid.
   // Remarks:
   //    - This method must be used in conjunction with IMvReaderStream::Play(uint64_t).
   //
   virtual HRESULT __stdcall PreparePlay
      (
      IMvReaderStreamElement *             in_pIElement,                            // Pointer to the reader stream element interface.
      uint64_t                             in_ui64Position,                         // Indicates the starting streaming position within the element.
      IMvReaderStreamPreparePlayObserver * in_pIMvReaderStreamPreparePlayObserver   // Pointer to the interface that observes when the reader stream has prepared the files to play.
      ) = 0;

   //
   // Summary:
   //   Streams video and audio files.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_WRONG_STATE, if PreparePlay() was not called.
   // Remarks:
   //    - This method is used in conjunction with IMvReaderStream::PreparePlay().
   //    - The time stamp should be large enough to allow the reader stream to open files, extract the compressed data, and decompress the data.
   //    - If the reader stream does not receive a new command before it reaches the end of the element, the last frame will be repeated
   //      or a black frame will be played until a new command is received.
   //    - This method can be used to play several elements in sequence. (See example 1.)
   //    - Any previously issued command with a time stamp equal to or greater than the play command's time stamp will be canceled. (See example 2.)
   //    - If the time stamp occurs in the past (for example, zero), the time stamp will be modified so that the
   //      command is executed as soon as possible. If this occurs, the warning MV_W_READERSTREAM_STARTTTIME_ADJUSTED
   //      will be returned. If an error occurs, the error code will be returned instead. 
   //    - When this command is processed, the reader stream always sends the data that the host node expects.
   // Example:
   //    <CODE>
   //    pJReaderStream->PreparePlay(pJElementA, posA, IMvReaderStreamPreparePlayObserver);  
   //    // Wait for IMvReaderStreamPreparePlayObserver to receive a notification from the reader stream indicating when the file is ready to be played. 
   //    pJReaderStream->Play(12:00:00);
   //    pJReaderStream->PreparePlay(pJElementB, posB, IMvReaderStreamPreparePlayObserver);  
   //    // Wait for IMvReaderStreamPreparePlayObserver to receive a notification from the reader stream indicating when the file is ready to be played. 
   //    pJReaderStream->Play(12:10:00);
   //    pJReaderStream->PreparePlay(pJElementC, posC, IMvReaderStreamPreparePlayObserver);  
   //    // Wait for IMvReaderStreamPreparePlayObserver to receive a notification from the reader stream indicating when the file is ready to be played. 
   //    pJReaderStream->Play(12:20:00);
   //    </CODE>
   //
   // Example:
   //    <CODE>
   //    pJReaderStream->PreparePlay(pJElementA, posA, IMvReaderStreamPreparePlayObserver);  
   //    // Wait for IMvReaderStreamPreparePlayObserver to receive a notification from the reader stream indicating when the file is ready to be played. 
   //    pJReaderStream->Play(12:00:00);  // Assume the duration of this element is 20 minutes.
   //    pJReaderStream->PreparePlay(pJElementB, posB, IMvReaderStreamPreparePlayObserver);  
   //    // Wait for IMvReaderStreamPreparePlayObserver to receive a notification from the reader stream indicating when the file is ready to be played. 
   //    pJReaderStream->Play(12:10:00);  // This command truncates the previous play command at 12:00:00.
   //    pJReaderStream->PreparePlay(pJElementC, posC, IMvReaderStreamPreparePlayObserver);  
   //    // Wait for IMvReaderStreamPreparePlayObserver to receive a notification from the reader stream indicating when the file is ready to be played. 
   //    pJReaderStream->Play(12:09:00);  // This command cancels the play command at 12:10:00 and truncates the previous play command at 12:00:00.
   //    </CODE>
   //
   virtual HRESULT __stdcall Play
      (
      uint64_t in_ui64Timestamp // Indicates the time at which the first frame will be output.
      ) = 0;

   //
   // Summary:
   //   Streams video and audio files.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The time stamp should be large enough to allow the reader stream to open files, extract the compressed data, and decompress the data.
   //    - If the reader stream does not receive a new command before it reaches the end of the element, the last frame will be repeated
   //      or a black frame will be played until a new command is received.
   //    - This method can be used to play several elements in sequence. (See example 1.)
   //    - Any previously issued command with a time stamp equal to or greater than the play command's time stamp will be canceled. (See example 2.)
   //    - If the time stamp occurs in the past (for example, zero), the time stamp will be modified so that the
   //      command is executed as soon as possible. If this occurs, the warning MV_W_READERSTREAM_STARTTTIME_ADJUSTED
   //      will be returned. If an error occurs, the error code will be returned instead. 
   //    - When this command is processed, the reader stream always sends the data that the host node expects.
   // Example:
   //    <CODE>
   //    pJReaderStream->Play(pJElementA, posA, 12:00:00);
   //    pJReaderStream->Play(pJElementB, posB, 12:10:00); 
   //    pJReaderStream->Play(pJElementC, posC, 12:20:00);
   //    </CODE>
   //
   // Example:
   //    <CODE>
   //    pJReaderStream->Play(pJElementA, posA, 12:00:00);  // Assume the duration of this element is 20 minutes.
   //    pJReaderStream->Play(pJElementB, posB, 12:10:00);  // This command truncates the previous play command at 12:00:00.
   //    pJReaderStream->Play(pJElementC, posC, 12:09:00);  // This command cancels the play command at 12:10:00 and truncates the previous play command at 12:00:00.
   //    </CODE>
   //
   virtual HRESULT __stdcall Play
      (
      IMvReaderStreamElement * in_pIElement,    // Pointer to the reader stream element interface.
      uint64_t in_ui64Position,                 // Indicates the starting streaming position within the element.
      uint64_t in_ui64Timestamp                 // Indicates the time at which the first frame will be output.
      ) = 0;

   //
   // Summary:
   //   Pauses the reader stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The last frame played will be repeated until a new command is received.
   //    - Any previously issued command with a time stamp equal to or greater than the pause command's time stamp will be canceled. 
   //    - If the time stamp occurs in the past (for example, zero), the time stamp will be modified so that the
   //      command is executed as soon as possible. If this occurs, the warning MV_W_READERSTREAM_STARTTTIME_ADJUSTED
   //      will be returned. If an error occurs, the error code will be returned instead. 
   //
   virtual HRESULT __stdcall Pause
      (
      uint64_t in_ui64Timestamp     // Indicates the time at which the reader stream will pause the streaming.
      ) = 0;

   //
   // Summary:
   //   Stops streaming at a specific time.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - A black frame will be played until a new command is received.
   //    - Any previously issued command with a time stamp equal to or greater than the stop command's time stamp will be canceled.
   //    - If the time stamp occurs in the past (for example, zero), the time stamp will be modified so that the
   //      command is executed as soon as possible. If this occurs, the warning MV_W_READERSTREAM_STARTTTIME_ADJUSTED
   //      will be returned. If an error occurs, the error code will be returned instead.
   //
   virtual HRESULT __stdcall Stop
      (
      uint64_t in_ui64Timestamp      // Indicates the time at which to stop streaming. 
      ) = 0;

   //
   // Summary:
   //   Retrieves a specific frame at a specific time.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Audio and VANC are output according to the reader stream settings.
   //    - The last seek issued will be repeated until a new command is received.
   //    - It is possible to cue multiple seek commands. However, the reader stream can only process the commands in real time.
   //      This means that a seek command may get canceled if another command is to be processed at the same time.
   //    - The reader stream will attempt to execute all seek commands to a maximum of one seek command per frame rate. 
   //      For example, if the frame rate is 25 fps, the reader stream will execute a maximum of 25 seek commands per second.
   //    - If the time stamp occurs in the past (for example, zero), the time stamp will be modified so that the
   //      command is executed as soon as possible. If this occurs, the warning MV_W_READERSTREAM_STARTTTIME_ADJUSTED
   //      will be returned. If an error occurs, the error code will be returned instead. 
   //
   virtual HRESULT __stdcall Seek
      (
      IMvReaderStreamElement * in_pIElement,    // Pointer to the reader stream element interface. 
      uint64_t in_ui64Position,                 // Indicates the starting streaming position within the element.
      uint64_t in_ui64Timestamp                 // Indicates the time at which the frame will be output.
      ) = 0;

   //
   // Summary:
   //   Flushes the transport command that matches the time stamp.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If the time stamp of the cancel command does not match the time stamp of a previously issued command, the 
   //      cancel command will be ignored.
   // 
   virtual HRESULT __stdcall Cancel
      (
      uint64_t in_ui64Timestamp  // Indicates the time stamp of the transport command that will be flushed.
      ) = 0;

   //
   // Summary:
   //   Flushes all the transport commands whose time stamp is equal to or greater than the indicated time stamp.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Any previously issued command with a time stamp equal to or greater than the CancelFrom command's time stamp will be canceled.
   //    - If the time stamp occurs in the past (for example, zero), the time stamp will be modified so that the
   //      command is executed as soon as possible. If this occurs, the warning MV_W_READERSTREAM_STARTTTIME_ADJUSTED
   //      will be returned. If an error occurs, the error code will be returned instead. 
   // 
   virtual HRESULT __stdcall CancelFrom
      (
      uint64_t in_ui64Timestamp     // Indicates the time from which all transport commands will be flushed.
      ) = 0;

   //
   // Summary:
   //   Registers an event callback for the reader stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::AddRef method of the in_pICallback parameter is called when the event callback is registered 
   //      to prevent the object implementing the IMvReaderStreamEventCallback() interface from being destroyed.
   //
   virtual HRESULT __stdcall RegisterEventCallback
      (
      IMvReaderStreamEventCallback * in_pICallback   // Pointer to the reader stream event callback interface.
      ) = 0;

   //
   // Summary:
   //    Unregisters an event callback for the reader stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::Release method of the in_pICallback parameter is called when the event callback is unregistered 
   //      to remove the reference count added by IMvReaderStream::RegisterEventCallback().
   //
   virtual HRESULT __stdcall UnregisterEventCallback
      (
      IMvReaderStreamEventCallback * in_pICallback   // Pointer to the reader stream event callback interface.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to load a reader stream element after loading an .xml file.  
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvReaderStreamHelper : public IUnknown
{
   //
   // Summary:
   //   Provides the reader stream element with the video and audio file information to use when saving to an .xml file.  
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // 
   virtual HRESULT __stdcall SetReaderStreamElementToSaveToXml
      (
      IMvReaderStreamElement * in_pIElement  // Pointer to the reader stream element interface.
      ) = 0;

   //
   // Summary:
   //   Gets the video and audio file information from the reader stream element after loading an .xml file.  
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall GetReaderStreamElementFromXml
      (
      IMvReaderStreamElement ** out_ppIElement  // Pointer that receives the reader stream element interface.
      ) = 0;

};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides the callback notification for asynchronous errors of software streams except the read stream and writer streams. 
//    This interface passes asynchronous errors to the object implementing it.
// Remarks:
//    - Use the IMvSystemTopology interface to register and unregister the
//      IMvSystemTopologyErrorCallback interface.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSystemTopologyErrorCallback : public IUnknown
{
   //
   // Summary:
   //    Receives the new asynchronous error for the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall NotifyAsyncError
      (
         const SMvAsyncErrorInformation& in_krsAsynErrorInfo   // Structure describing the asynchronous error.
      ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides the callback notifications for events generated by the universal clock.
//    This interface passes asynchronous events to the object implementing it.
// Remarks:
//    - Use the IMvSystemTopology interface to register and unregister the
//      IMvUniversalClockNotificationCallback interface.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvUniversalClockNotificationCallback : public IUnknown
{
	//
	// Summary:
	//    Receives the new asynchronous error for the Üniversal Clock.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//
   virtual HRESULT __stdcall NotifyAsyncClockEvent( const SMvUniversalClockNotification & in_krsNotification ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents a specific workflow topology. 
// Remarks:
//    - A topology is made up of a sequence of streams and nodes that accomplishes a configurable set of actions on
//      video, audio, and VANC data.
//    - This interface creates the nodes and streams contained in the topology.
//    - This interface can be queried for detailed information about the topology configuration and can be used to
//      destroy the topology or all its components.
//    - The user application is not aware of host processing items (such as reader streams, transfer streams, and host nodes) 
//      of another application. However, multiple applications can control the same hardware with the
//      topology-based API as long as they do not use the same resources.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSystemTopology : public IUnknown
{
   //
   // Summary:
   //    Destroys the topology on the card along with all its components
   //    (streams and nodes).
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall DestroyTopology() = 0;

   //
   // Summary:
   //    Creates an input stream in the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateInputStream
      (
      const char * in_kszName,                              // Indicates the name of the input stream to create.
      IMvVideoInputConnector* in_pIVideoInputConnectors[],  // Pointer to the array of video input connector interfaces.
      uint32_t in_ui32VideoConnectorsCount,                 // Indicates the number of video input connectors.
      IMvAudioInputConnector* in_apIAudioInputConnectors[],	// Pointer to the array of audio input connector interfaces.
      uint32_t in_ui32AudioInputConnectorsCount,            // Indicates the number of audio input connectors.
      IMvNode* in_pIOutputNode,                             // Pointer to the output node interface that receives the audio, video, and VANC data.
      const SMvResolutionInfo& in_krsResInfo,               // Structure of the resolution settings of the input stream. 
      const SMvInputStreamSettings& in_krsStreamSettings,   // Structure of the input stream settings.
      IMvInputStream **out_ppIInputStream                   // Pointer that receives the created input stream 
                                                            // interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates an input stream using SdiIp connector(s) in the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateInputStreamSdiIp
      (
      const char * in_kszName,                              // Indicates the name of the input stream to create.   
      IMvConnector* in_pISdiIpInputConnectors[],            // Pointer to the array of SdiIp video input connector interfaces.
      IMvConnector* in_pISdiIpAlphaInputConnectors[],       // Pointer to the array of SdiIp alpha input connector interfaces.
      uint32_t in_ui32ConnectorsCount,                      // Indicates the number of SdiIp video input connectors.
      IMvConnector* in_apIAudioInputConnectors[],           // Pointer to the array of audio input connector interfaces.
      uint32_t in_ui32AudioInputConnectorsCount,            // Indicates the number of audio input connectors.
      IMvNode* in_pIOutputNode,                             // Pointer to the output node interface that receives the audio, video, and VANC data.
      const SMvResolutionInfo & in_krsResolution,           // Structure of the resolution settings of the input stream. 
      const SMvInputStreamSettings& in_krsStreamSettings,   // Structure of the input stream settings.
      IMvInputStream **out_ppIInputStream                   // Pointer that receives the created input stream
                                                            // interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates an output stream in the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //   
   virtual HRESULT __stdcall CreateOutputStream
      (
      const char * in_kszName,                               // Indicates the name of the output stream to create.
      IMvNode* in_pIInputNode,                               // Pointer to the input node interface of the output stream.
      const SMvResolutionInfo& in_krsResInfo,                // Structure of the resolution settings of the output stream.
      const SMvOutputStreamSettings& in_krsStreamSettings,   // Structure of the output stream settings.
      IMvVideoOutputConnector* in_pIVideoOutputConnectors[], // Pointer to the array of video output connector interfaces.
      uint32_t in_ui32VideoConnectorsCount,                  // Indicates the number of video output connectors.
      IMvOutputStream **out_ppIOutputStream                  // Pointer that receives the created output stream 
                                                             // interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates an output stream using Sdi connector(s) in the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //   
   virtual HRESULT __stdcall CreateOutputStreamSdi
      (
      const char * in_kszName,                                 // Indicates the name of the output stream to create.
      IMvNode    * in_pIInputNode,                             // Pointer to the input node interface of the output stream.
      const SMvResolutionInfo & in_krsResolution,              // Structure of the resolution settings of the output stream.
      const SMvOutputStreamSettings & in_krsStreamSettings,    // Structure of the output stream settings.
      IMvConnector * in_pISdiOutputConnectors[],               // Pointer to the array of Sdi video output connector interfaces.
      IMvConnector * in_pAlphaOutputConnectors[],              // Pointer to the array of Sdi alpha output connector interfaces.
      uint32_t in_ui32ConnectorsCount,                         // Indicates the number of Sdi video output connectors.
      IMvOutputStream ** out_ppIOutputStream                   // Pointer that receives the created output stream 
                                                               // interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates an output stream using SdiIp connector(s) in the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //   
   virtual HRESULT __stdcall CreateOutputStreamSdiIp
      (
      const char * in_kszName,                                  // Indicates the name of the output stream to create.
      IMvNode    * in_pIInputNode,                              // Pointer to the input node interface of the output stream.
      const SMvResolutionInfo & in_krsResolution,               // Structure of the resolution settings of the output stream.
      const SMvOutputStreamSettings & in_krsStreamSettings,     // Structure of the output stream settings.
      IMvConnector * in_pISdiIpOutputConnectors[],              // Pointer to the array of SdiIp video output connector interfaces.
      IMvConnector * in_pSdiIpAlphaOutputConnectors[],          // Pointer to the array of SdiIp alpha output connector interfaces.
      uint32_t in_ui32ConnectorsCount,                          // Indicates the number of SdiIp video output connectors.
      IMvOutputStream ** out_ppIOutputStream                    // Pointer that receives the created output stream
                                                                // interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates a transform stream in the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - A transform stream can be created between two card nodes or two host nodes.
   //    - When a transform stream is created between two card nodes, the transform stream uses the card's onboard 
   //      scaler to transform the video.
   //    - When a transform stream is created between two host nodes, the video is transformed using the card's CPU 
   //      scaler processing unit, if enabled.
   //    - For more details on creating transform streams between card nodes or host nodes, see the <i>Matrox DSX Topology API User Guide</i>.
   //
   virtual HRESULT __stdcall CreateTransformStream
      (
      const char * in_kszName,                                    // Indicates the name of the transform stream to create.
      IMvNode* in_pIInputNode,                                    // Pointer to the input node interface of the transform stream.
      IMvNode* in_pIOutputNode,                                   // Pointer to the output node interface of the transform stream.
      const SMvTransformStreamSettings& in_rsStreamSettings,      // Structure of the transform stream settings.
      IMvTransformStream** out_ppIStream                          // Pointer that receives the created transform stream
                                                                  // interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates a mixer stream in the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateMixerStream
      (
      const char * in_kszName,                                 // Indicates the name of the mixer stream to create. 
      IMvNode* in_apIInputNodes[],                             // Pointer to the array of input node interfaces of the mixer stream.
      const SMvMixerStreamNodeSettings in_asNodesSettings[],   // Array of settings for the input nodes of the mixer stream.
      uint32_t in_ui32InputNodesCount,                         // Indicates the number of elements in in_apIInputNodes and in_asNodesSettings of the mixer stream.
      IMvNode* in_pIOutputNode,                                // Pointer to the output node interface of the mixer stream.
      IMvNode* in_pIBackgroundNode,                            // Pointer to the background node interface of the mixer stream.
      const SMvMixerStreamSettings& in_rsStreamSettings,       // Structure of the mixer stream settings.
      IMvMixerStream** out_ppIStream                           // Pointer that receives the created mixer stream interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates a transfer stream in the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - The input node settings and the output node settings must be the same. The data is copied without modification.
   //    - In the case where the resolution of a card node is PsF, the VANC data is converted to progressive when transfered 
   //      to a host node (or vice-versa). For more information, see the <i>Matrox DSX Topology API User Guide</i>.
   //    - The transfer stream uses the card's DMA to transfer data between onboard memory and host memory. This means that 
   //      if the input node is a card node, the output node must be a host node, and vice-versa.
   //
   virtual HRESULT __stdcall CreateTransferStream
      (
      const char * in_kszName,                              // Indicates the name of the transfer stream to create.
      IMvNode    * in_pIInputNode,                          // Pointer to the input node interface of the transfer stream.
      IMvNode    * in_pIOutputNode,                         // Pointer to the output node interface of the transfer stream.
      EMvTransferDirection in_eTransferDirection,           // Indicates the direction of the transfer stream. The direction can be from the card memory to host memory, or vice-versa.
      const SMvTransferStreamSettings & in_krsSettings,     // Structure of the transfer stream settings.
      IMvTransferStream ** out_ppNewStream                  // Pointer that receives the created transfer stream interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates an encoder stream in the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateEncoderStream
      (
      const char  * in_kszName,                                // Indicates the name of the encoder stream to create. 
      IMvHostNode * in_pIInputNode,                            // Pointer to the input host node interface of the encoder stream.
      IMvCompressedHostNode * in_pIOutputNode,                 // Pointer to the output compressed host node interface of the encoder stream.
      const SMvEncoderStreamSettings   & in_krsSettings,       // Structure of the encoder stream settings.
      IMvEncoderStreamSettingsCallback * in_pICodecSettings,   // Pointer to the encoder stream settings callback interface.
      IMvEncoderStream ** out_ppNewStream                      // Pointer that receives the created encoder stream interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates a decoder stream in the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateDecoderStream
      (
      const char  * in_kszName,                    // Indicates the name of the decoder stream to create.
      const GUID & in_krguidDecoderStream,         // Indicates the GUID of the codec that will be used to decode the stream.
      IMvCompressedHostNode * in_pIInputNode,      // Pointer to the input compressed host node interface of the decoder stream.
      IMvHostNode * in_pIOutputNode,               // Pointer to the output host node interface of the decoder stream.
      IMvDecoderStream ** out_ppNewStream          // Pointer that receives the created decoder stream interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates a muxer stream in the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateMuxerStream
      (
      const char  * in_kszName,                             // Indicates the name of the muxer stream to create. 
      IMvCompressedHostNode * in_pIVideoNode,               // Pointer to the input compressed host node interface containing compressed video data.
      IMvCompressedHostNode * in_pIAudioNode,               // Pointer to the input compressed host node interface containing compressed audio data.
      IMvCompressedHostNode * in_pIVancNode,                // Pointer to the input compressed host node interface containing compressed VANC data.
      IMvCompressedHostNode * in_pIOutputNode,              // Pointer to the output compressed host node interface containing a single MPEG-2 program transport stream (SPTS) muxed buffer.
      const SMvMuxerStreamSettings   & in_krsSettings,      // Structure of the muxer stream settings.
      IMvMuxerStream ** out_ppNewStream                     // Pointer that receives the created muxer stream interface, if the method is completed successfully.
      ) = 0; 

   //
   // Summary:
   //    Creates a demuxer stream in the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateDemuxerStream
      (
      const char * in_kszName,                           // Indicates the name of the demuxer stream to create.
      const SMvDemuxerStreamSettings & in_krsSettings,   // Structure of the demuxer stream settings.
      IMvCompressedHostNode * in_pIInputNode,            // Pointer to the compressed host node interface containing an MPEG-2 program transport stream muxed buffer.
      IMvDemuxerStream ** out_ppNewStream                // Pointer that receives the created demuxer stream interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates an echo stream in the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateEchoStream
      (
      const char  * in_kszName,                          // Indicates the name of the echo stream to create. 
      IMvNode     * in_pIVideoNode,                      // Pointer to the input node interface of the echo stream.
      IMvNode     * in_pIOutputNode,                     // Pointer to the output node interface of the echo stream.
      const SMvEchoStreamSettings   & in_krsSettings,    // Structure of the echo stream settings.
      IMvEchoStream  ** out_ppNewStream                  // Pointer that receives the created echo stream interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates a writer stream in the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateWriterStream
      (
      const char  * in_kszName,                                   // Indicates the name of the writer stream to create. 
      const GUID & in_krguidWriterStream,                         // Indicates the GUID that will be used to create the writer stream.
      IMvHostNode * in_pIInputNode,                               // Pointer to the input host node interface of the writer stream.
      const SMvWriterStreamSettings & in_krsSettings,             // Structure of the writer stream settings.
      IMvEncoderStreamSettingsCallback* in_pIVideoCodecSettings,  // Pointer to the video encoder stream settings callback interface.
      IMvEncoderStreamSettingsCallback* in_pIAudioCodecSettings,  // Pointer to the audio encoder stream settings callback interface.
      IMvWriterStream ** out_ppNewStream                          // Pointer that receives the created writer stream interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates a compressed writer stream in the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateCompressedWriterStream
      (
      const char                              * in_kszName,                // Indicates the name of the compressed writer stream to create.
      const GUID                              & in_krguidWriterStream,     // Indicates the GUID that will be used to create the compressed writer stream.
      IMvCompressedHostNode                   * in_pIVideoInputNode,       // Pointer to the input compressed host node interface containing compressed video data.
      IMvCompressedHostNode                   * in_pIAudioInputNode,       // Pointer to the input compressed host node interface containing compressed audio data.
      IMvCompressedHostNode                   * in_pIVancInputNode,        // Pointer to the input compressed host node interface containing compressed VANC data. <b>Note</b>: This parameter is currently not supported.
      const SMvCompressedWriterStreamSettings & in_krsSettings,            // Structure of the compressed writer stream settings.
      IMvCompressedWriterStream              ** out_ppNewStream            // Pointer that receives the created compressed writer stream interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates a reader stream in the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateReaderStream
      (
      const char  * in_kszName,                          // Indicates the name of the reader stream to create. 
      IMvHostNode * in_pIOutputNode,                     // Pointer to the output host node interface of the reader stream.
      const SMvReaderStreamSettings & in_krsSettings,    // Structure of the reader stream settings.
      IMvReaderStream ** out_ppNewStream                 // Pointer that receives the created reader stream interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates a de-interlacer stream in the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - An onboard de-interlacer is required to create a de-interlacer stream.
   //
   virtual HRESULT __stdcall CreateDeInterlacerStream
      (
      const char * in_kszName,                                 // Indicates the name of the de-interlacer stream to create.
      IMvNode    * in_pIInputNode,                             // Pointer to the input card node interface of the de-interlacer stream.
      IMvNode    * in_pIOutputNode,                            // Pointer to the output card node interface of the de-interlacer stream.
      const SMvDeInterlacerStreamSettings & in_krsSettings,    // Structure of the de-interlacer stream settings.
      IMvDeInterlacerStream ** out_ppNewStream                 // Pointer that receives the created de-interlacer stream interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates an RTP (Real-time Transport Protocol) sender stream in the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateRTPSenderStream
      (
      const char * in_kszName,                              // Indicates the name of the RTP sender stream to create.
      IMvCompressedHostNode * in_pIInputNode,               // Pointer to the input compressed host node interface of the RTP sender stream.
      const SMvRTPSenderStreamSettings & in_krsSettings,    // Structure of the RTP sender stream settings.
      IMvRTPSenderStream ** out_ppINewStream                // Pointer that receives the created RTP sender stream interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates a node in the topology of a card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Once the card node is created, its setting cannot be changed.
   //    - The maximum number of nodes that can be allocated in all system topologies on a card is limited to the card's onboard memory.
   //
   virtual HRESULT __stdcall CreateCardNode
      (
      const SMvNodeSettings      & in_rsNodeSettings,   // Structure of the card node's settings.
      const SMvNodeSettingsVideo * in_psVideoSettings,  // Pointer to the input card node's video settings.
      const SMvNodeSettingsAudio * in_psAudioSettings,  // Pointer to the input card node's audio settings.
      const SMvNodeSettingsVanc  * in_psVancSettings,   // Pointer to the input card node's VANC settings.
      IMvCardConfiguration       * in_pICardIgnored,    // This parameter is ignored. For possible future use.
      IMvNode                   ** out_ppINode          // Pointer that receives the created node interface, if the 
                                                        // method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates an alias card node in the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Note:
   //    - An alias card node represents a read-only card node that is used to access the data contained in a card node owned by another or the same process.
   //
   virtual HRESULT __stdcall CreateAliasCardNode
      (
      const char        * in_kszName,                 // Pointer to the name of the alias card node.
      IMvNode           * in_pIReferenceNode,         // Pointer to the reference card node containing the data to access from another topology.
      IMvNode          ** out_ppINode                 // Pointer that receives the created node interface, if the 
                                                      // method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates a host node in the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - Once the host node is created, its setting cannot be changed.
   //    - The maximum number of host nodes that can be allocated in all system topologies is limited to the amount of memory that can be allocated to the process.
   //
   virtual HRESULT __stdcall CreateHostNode
      (
      const SMvNodeSettings      & in_rsNodeSettings,    // Structure of the host node's settings.
      const SMvNodeSettingsVideo * in_psVideoSettings,   // Pointer to the input host node's video settings.
      const SMvNodeSettingsAudio * in_psAudioSettings,   // Pointer to the input host node's audio settings.
      const SMvNodeSettingsVanc  * in_psVancSettings,    // Pointer to the input host node's VANC settings.
      IMvHostNode               ** out_ppINode           // Pointer that receives the created host node interface, if the 
                                                         // method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates a shared host node in the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Note:
   //    - The name given to the shared host node will be used to create the shared host memory.
   //    - The main purpose of a shared host node is to access host node data from other processes.
   //
   virtual HRESULT __stdcall CreateHostSharedNode
      (
      const SMvNodeSettings      & in_rsNodeSettings,    // Structure of the host node's settings.
      const SMvNodeSettingsVideo * in_psVideoSettings,   // Pointer to the input host node's video settings.
      const SMvNodeSettingsAudio * in_psAudioSettings,   // Pointer to the input host node's audio settings.
      const SMvNodeSettingsVanc  * in_psVancSettings,    // Pointer to the input host node's VANC settings.
      IMvHostNode               ** out_ppINode           // Pointer that receives the created host node interface, if the 
                                                         // method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates a host node in the system topology that contains compressed data.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - Once the compressed host node is created, its setting cannot be changed.
   //
   virtual HRESULT __stdcall CreateCompressedHostNode
      (
      const SMvCompressedHostNodeSettings & in_krsNodeSettings,   // Structure of the compressed host node's settings.
      IMvCompressedHostNode              ** out_ppINewNode        // Pointer that receives the created compressed host node interface, 
                                                                  // if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates a host node in the system topology that is used to transfer data from host memory to GPU memory.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Once the host node is created, its setting cannot be changed.
   //    - This interface is used to access a 3D texture which is automatically transferred from host memory to GPU memory.
   //
   virtual HRESULT __stdcall CreateTextureNode
      (
      const SMvNodeSettings      & in_krsNodeSettings,      // Structure of the node's settings.
      const SMvNodeSettingsVideo * in_psVideoSettings,      // Pointer to the input host node's video settings.
      const SMvNodeSettingsAudio * in_psAudioSettings,      // Pointer to the input host node's audio settings.
      const SMvNodeSettingsVanc  * in_psVancSettings,       // Pointer to the input host node's VANC settings.
      IMvTextureNode            ** out_ppINode              // Pointer that receives the created texture node interface, 
                                                            // if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates an alias host node in the system topology that is used to transfer data from the node's host memory 
   //    to a texture in GPU memory.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - Once the host node is created, its setting cannot be changed.
   //    - This interface is used to access a texture which is automatically transferred from host memory.
   //    - An alias texture always shares its node content with a host node.
   //
   virtual HRESULT __stdcall CreateAliasTextureNode
      (
      const SMvNodeSettings      & in_krsNodeSettings,   // Structure of the node's settings.
      const SMvNodeSettingsVideo * in_psVideoSettings,   // Pointer to the input host node's video settings.
      const SMvNodeSettingsAudio * in_psAudioSettings,   // Pointer to the input host node's audio settings.
      const SMvNodeSettingsVanc  * in_psVancSettings,    // Pointer to the input host node's VANC settings.
      IMvTextureNode            ** out_ppINode           // Pointer that receives the created texture node interface,
                                                         // if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates a host node in the system topology that is used to transfer data from GPU memory to the node's host 
   //    memory.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - Once the host node is created, its setting cannot be changed.
   //    - This interface is used to access a 3D rendering target which is automatically transferred from GPU 
   //      memory to the node's host memory.
   //
   virtual HRESULT __stdcall CreateRenderingTargetNode
      (
      const SMvNodeSettings      & in_krsNodeSettings,   // Structure of the node's settings.
      const SMvNodeSettingsVideo * in_psVideoSettings,   // Pointer to the input host node's video settings.
      const SMvNodeSettingsAudio * in_psAudioSettings,   // Pointer to the input host node's audio settings.
      const SMvNodeSettingsVanc  * in_psVancSettings,    // Pointer to the input host node's VANC settings.
      IMvRenderingTargetNode    ** out_ppINode           // Pointer that receives the created rendering target node 
                                                         // interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates a host node in the system topology that is used to transfer data from GPU memory to the node's host 
   //    memory. 
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - Once the host node is created, its setting cannot be changed.
   //    - A reference rendering target node always shares its node content with an alias host node.
   //    - The node's memory is shared across all processes.
   //
   virtual HRESULT __stdcall CreateReferenceRenderingTargetNode
      (
      const SMvNodeSettings      & in_krsNodeSettings,   // Structure of the node's settings.
      const SMvNodeSettingsVideo * in_psVideoSettings,   // Pointer to the input host node's video settings.
      const SMvNodeSettingsAudio * in_psAudioSettings,   // Pointer to the input host node's audio settings.
      const SMvNodeSettingsVanc  * in_psVancSettings,    // Pointer to the input host node's VANC settings.
      IMvRenderingTargetNode    ** out_ppINode           // Pointer that receives the created rendering target node 
                                                         // interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates an enumerator listing all streams in the topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateStreamsEnumerator
      (
      IMvStreamsEnumerator** out_ppIStreamsEnumerator // Pointer that receives an enumerator listing all streams 
                                                      // currently used in the topology.
      ) = 0;

   //
   // Summary:
   //    Creates an enumerator listing all nodes in the topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateNodesEnumerator
      (
      IMvNodesEnumerator** out_ppINodesEnumerator  // Pointer that receives the nodes enumerator interface.
      ) = 0;

   //
   // Summary:
   //    Destroys all components in the topology (streams and nodes), but not the topology itself.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall DestroyAllComponents() = 0;

   //
   // Summary:
   //    Gets the topology name.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetName
      (
      char * out_szName,                  // An array of characters that will receive the name of the topology.
      uint32_t in_ui32NbOfDestCharacters  // Indicates the number of characters in out_szName.
      ) = 0;

   //
   // Summary:
   //    Indicates whether or not the current process has access to modify the topology and
   //    its components.   
   // Return value:
   //    - bool: If true, the topology and its components can be modified. 
   // Remarks:
   //    - Modification access is automatically granted to the process creating the topology.
   //    - Modification access can be released with the LeaveControl() method and can be acquired later with the
   //      AcquireControl() method.
   //    - Only one process can control the topology at a time, but any number of processes can query for information
   //      from the topology at any time.
   //
   virtual bool __stdcall IsCurrentlyControlled() = 0;

   //
   // Summary:
   //    Grants access to modify the topology for the current process.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Modification access is automatically granted to the process creating the topology.
   //    - Modification access can be released with the LeaveControl() method.
   //    - Only one process can control the topology at a time, but any number of processes can query for information
   //      from the topology at any time.
   //
   virtual HRESULT __stdcall AcquireControl() = 0;

   //
   // Summary:
   //    Removes modification access to the topology from the current process.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Modification access is automatically granted to the process creating the topology.
   //    - Modification access can be acquired at a later stage with the AcquireControl() method.
   //    - Only one process can control the topology at a time, but any number of processes can query for information
   //      from the topology at any time.
   //
   virtual HRESULT __stdcall LeaveControl() = 0;

   //
   // Summary:
   //    Indicates whether or not the topology still exists on the card. 
   // Return value:
   //    - bool: If true, the topology still exists on the card. 
   // Remarks:
   //    - Because multiple processes can query for information from the topology at any time, make sure that the
   //      topology exists before calling any method from it. Otherwise, if the topology no longer exists, an error 
   //      message will be returned.
   //
   virtual bool __stdcall StillExists() = 0;

   //
   // Summary:
   //    Registers a callback notification for an asynchronous error of software streams except the read stream and writer streams.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::AddRef method of the in_pIErrorCallback parameter is called when the notification is
   //      registered to prevent the object implementing the IMvSystemTopologyErrorCallback interface from being
   //      destroyed.
   //
   virtual HRESULT __stdcall RegisterCallbackForErrorNotification
      (
      IMvSystemTopologyErrorCallback* in_pIErrorCallback // Pointer to the error notification callback interface.
      ) = 0;

   //
   // Summary:
   //    Unregisters a callback notification for an asynchronous error.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - The IUnknown::Release method of the in_pIErrorCallback parameter is called when the notification is
   //      unregistered to remove the reference count added by the
   //      IMvSystemTopology::RegisterCallbackForErrorNotification.
   //
   virtual HRESULT __stdcall UnregisterCallbackForErrorNotification
      (
      IMvSystemTopologyErrorCallback* in_pIErrorCallback // Pointer to the error notification callback interface.
      ) = 0;

   //
   // Summary:
   //    Generates an XML description of a system topology and returns its size.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - This method must be called before IMvSystemTopology::GetTopologyXmlString().
   //
   virtual HRESULT __stdcall BuildTopologyXmlString
      (
      uint32_t & out_rui32XmlTextByteSize    // Size (in bytes) of the null-terminated UTF-8 string representing the XML description that has been generated.
      ) = 0;

   //
   // Summary:
   //    Gets an XML description of a system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - This method must be called after IMvSystemTopology::BuildTopologyXmlString().
   //
   virtual HRESULT __stdcall GetTopologyXmlString
      (
      char * out_pBuffer,                 // Pointer to the buffer that will receive the null-terminated UTF-8 string representing the XML description.
      uint32_t in_ui32XmlTextByteSize     // Indicates the size of the buffer (in bytes).
      ) = 0;

   //
   // Summary:
   //    Gets the system clock interface of the system topology.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall GetClockInterface
      (
      IMvSystemClock ** out_ppClock // Pointer that receives the system clock interface associated with the system topology.
      ) = 0;

   //
   // Summary:
   //    Creates an RTP (Real-time Transport Protocol) receiver stream in the system topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateRTPReceiverStream
      (
      const char * in_kszName,                                 // Indicates the name of the RTP receiver stream to create.
      IMvCompressedHostNode * in_pOutputNode,                  // Pointer to the output compressed host node interface of the RTP receiver stream.
      const SMvRTPReceiverStreamSettings & in_krsSettings,     // Structure of the RTP receiver stream settings.
      IMvRTPReceiverStream ** out_ppINewStream                 // Pointer that receives the created RTP receiver stream interface, if the method is completed successfully.
      ) = 0;

};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates the system topologies for the current process. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSystemTopologyEnumerator : public IUnknown
{
   //
   // Summary:
   //    Updates and resets the internal list of system topology interfaces.
   // Description:
   //    The internal list of system topology interfaces is updated with the most recent values for the current process
   //    and the internal pointer is reset so that the next call to IMvSystemTopologyEnumerator::Next returns the
   //    first system topology interface in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Reset() = 0;

   //
   // Summary:
   //    Gets the next system topology interface.
   // Description:
   //	 The next system topology interface is retrieved from the internal list of system topology interfaces.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Next
      (
      IMvSystemTopology ** out_ppITopology   // Pointer that receives the next system topology interface.
      ) = 0;

   //
   // Summary:
   //    Skips a given number of system topology interfaces.
   // Description:
   //    The internal pointer is changed so that the next call to IMvSystemTopologyEnumerator::Next skips a
   //    given number of system topology interfaces in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Skip
      (
      uint32_t in_ui32Count   // Number of system topology interfaces to skip.
      ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates the cards in the system. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSystemConfigurationCardEnumerator  : public IUnknown
{
   //
   // Summary:
   //    Updates and resets the internal list of card configuration interfaces in the system.
   // Description:
   //    The internal list of card configuration interfaces is updated with the most recent values in the system
   //    and the internal pointer is reset so that the next call to IMvSystemConfigurationCardEnumerator::Next returns the
   //    first card configuration interface in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Reset() = 0;

   //
   // Summary:
   //    Gets the next card configuration interface in the system.
   // Description:
   //	 The next card configuration interface is retrieved from the internal list of card configuration interfaces.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Next
      (
      IMvCardConfiguration ** out_ppICardConfiguration   // Pointer that receives the next card configuration interface.   
      ) = 0;

   //
   // Summary:
   //    Skips a given number of card configuration interfaces in the system.
   // Description:
   //    The internal pointer is changed so that the next call to IMvSystemConfigurationCardEnumerator::Next skips a
   //    given number of card configuration interfaces in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Skip
      (
      uint32_t in_ui32Count      // Number of card configuration interfaces to skip.
      ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to notify the user application that a video surface is being returned to the buffer pool. 
// Remarks:
//    - This interface is used in conjunction with the IMvSurfacePool::AddCompletionObserver() method.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSurfacePoolCallback : public IUnknown
{
   //
   // Summary:
   //    Notifies the user application that a video surface is being returned to the buffer pool.
   //
   virtual void __stdcall ReceiveSurface
      (
      IMvSurface * in_pISurface  // Pointer to the video surface interface.
      ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to notify the user application that an audio sample buffer is being returned to the buffer pool. 
// Remarks:
//    - This interface is used in conjunction with the IMvAudioSamplesPool::AddCompletionObserver() method.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvAudioSamplesPoolCallback : public IUnknown
{
   //
   // Summary:
   //    Notifies the user application that an audio sample buffer is being returned to the buffer pool.
   //
   virtual void __stdcall ReceiveAudioSamples
      (
      IMvAudioSamples * in_pIAudioSamples    // Pointer to the audio samples interface.
      ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to obtain the state of a buffer while it is being used. 
// Remarks:
//    - This interface is used for diagnostic purposes.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvPoolBufferStateCallback : public IUnknown
{
   //
   // Summary:
   //    Receives the state of a buffer while it is being used.
   //
   virtual void __stdcall ReceiveBufferState
      (
      const SMvPoolBufferState & in_krsBufferState    // Structure of the buffer's state when it is not in the buffer pool.
      ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to manage video surfaces in the buffer pool. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSurfacePool : public IUnknown
{
   //
   // Summary:
   //    Gets a video surface from the buffer pool.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_NOT_FOUND, if all buffers in the buffer pool are used.
   // Remarks:
   //    - As soon as a video surface is obtained, it is no longer in the buffer pool. The caller owns
   //      the video surface and the reference count is incremented.
   //    - After this call, the user application must set the video surface's attributes (such as read count, write count, time stamp, and polarity) according to the user application's workflow.
   //
   virtual HRESULT __stdcall GetSurface
      (
      IMvSurface ** out_ppISurface  // Pointer that receives the video surface interface.
      ) = 0;

   //
   // Summary:
   //    Waits for a video surface to be returned to the buffer pool, which is then returned to the user application.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_TIMEOUT, if in_ui32Timeout expires before the video surface is returned to the buffer pool.
   // Remarks:
   //    - As soon as a video surface is obtained, it is no longer in the buffer pool. The caller owns
   //      the video surface and the reference count is incremented.
   //    - After this call, the user application must set the video surface's attributes (such as read count, write count, time stamp, and polarity) according to the user application's workflow.
   //
   virtual HRESULT __stdcall WaitForSurface
      (
      uint32_t in_ui32Timeout,      // Maximum time (in milliseconds) to wait for a video surface.
      IMvSurface ** out_ppISurface  // Pointer that receives the video surface interface.
      ) = 0;
   
   //
   // Summary:
   //    Registers a completion observer notifying the user application when a video surface is returned to the pool.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall AddCompletionObserver
      (
      IMvSurfacePoolCallback * in_pICallback    // Pointer to the video surface pool callback interface.
      ) = 0;

   //
   // Summary:
   //    Unregisters a completion observer notifying the user application when a video surface is returned to the pool.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall RemoveCompletionObserver
      (
      IMvSurfacePoolCallback * in_pICallback    // Pointer to the video surface pool callback interface.
      ) = 0;
   
   //
   // Summary:
   //    Modifies the number of the video surfaces managed by the buffer pool.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall AdjustSize
      (
      uint32_t in_ui32DesiredPoolSize  // Indicates the new number of video surfaces in the buffer pool.
      ) = 0;

   //
   // Summary:
   //    Gets the status number of video surfaces currently managed by the buffer pool.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall GetStatus
      (
      uint32_t * out_ui32TotalManaged,    // Indicates the total number of video surfaces managed by the buffer pool.
      uint32_t * out_ui32Outside,         // Indicates the number of video surfaces that are currently not in the buffer pool.
      uint32_t * out_ui32Inside           // Indicates the number of video surfaces that are currently in the buffer pool.
      ) = 0;

   //
   // Summary:
   //    Receives a list of video surfaces that are currently not in the buffer pool.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - This method is used for diagnostic purposes.
   //
   virtual HRESULT __stdcall ListOutsidePool
      (
      IMvPoolBufferStateCallback * in_pICallback   // Pointer to the callback interface that will receive the video surfaces currently not in the buffer pool.
      ) = 0;

   //
   // Summary:
   //    Gets the name of the video surface pool.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall GetPoolName
      (
      wchar_t * out_wszPoolName,    // An array of characters that will receive the name of the video surface pool.
      uint32_t in_ui32Size          // Indicates the maximum number of characters (in bytes) for out_wszPoolName.
      ) = 0;

   //
   // Summary:
   //    Waits for a list of video surfaces to be ready for reading.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_TIMEOUT, if in_ui32Timeout expires before the video surface is ready for reading.
   // Remarks:
   //    - This method waits for the write completion event of the video surface to be signaled.
   //      For more details, see the <i>Matrox DSX Topology API User Guide</i>.
   //
   virtual HRESULT __stdcall WaitUntilReadyForRead
      (
      IMvSurface      * in_apISurface[],           // Pointer to the array of video surfaces.
      uint32_t          in_ui32Count,              // Indicates the number of video surfaces in the array.
      bool              in_bWaitForAll,            // If true, the method waits for all the video surfaces to be ready for reading.
                                                   // Otherwise, the method waits for any video surface to be ready for reading.
      uint32_t          in_ui32Timeout,            // Maximum time (in milliseconds) to wait for video surfaces to be ready for reading.
      uint32_t        & out_rui32IndexSignaled     // Indicates the index of the first video surface that is ready for reading.
      ) = 0;

   //
   // Summary:
   //    Waits for a video surface to be ready for reading.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_TIMEOUT, if in_ui32Timeout expires before the video surface is ready for reading.
   // Remarks:
   //    - This method waits for the write completion event of the video surface to be signaled.
   //      For more details, see the <i>Matrox DSX Topology API User Guide</i>.
   //
   virtual HRESULT __stdcall WaitUntilReadyForRead
      (
      IMvSurface * in_pSurface,  // Pointer to the video surface interface.
      uint32_t in_ui32Timeout    // Maximum time (in milliseconds) to wait for a video surface to be ready for reading.
      ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to manage audio sample buffers in the buffer pool. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvAudioSamplesPool : public IUnknown
{
   //
   // Summary:
   //    Gets an audio sample buffer from the buffer pool.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_NOT_FOUND, if all buffers in the buffer pool are used.
   // Remarks:
   //    - As soon as an audio sample buffer is obtained, it is no longer in the buffer pool. The caller owns
   //      the audio sample buffer and the reference count is incremented.
   //    - After this call, the user application must set the buffer's attributes (such as read count, write count, time stamp, polarity, and length) according to the user application's workflow.
   //
   virtual HRESULT __stdcall GetAudioSamples
      (
      IMvAudioSamples ** out_ppIAudioSamples    // Pointer that receives the audio sample buffer interface.
      ) = 0;

   //
   // Summary:
   //    Waits for an audio sample buffer to be returned to the buffer pool, which is then returned to the user application.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_TIMEOUT, if in_ui32Timeout expires before the audio sample buffer is returned to the buffer pool.
   // Remarks:
   //    - As soon as an audio sample buffer is obtained, it is no longer in the buffer pool. The caller owns
   //      the audio sample buffer and the reference count is incremented.
   //    - After this call, the user application must set the buffer's attributes (such as read count, write count, time stamp, polarity, and length) according to the user application's workflow.
   //
   virtual HRESULT __stdcall WaitForAudioSamples
      (
      uint32_t in_ui32Timeout,                  // Maximum time (in milliseconds) to wait for an audio sample buffer.
      IMvAudioSamples ** out_ppIAudioSamples    // Pointer that receives the audio sample buffer interface.
      ) = 0;
   
   //
   // Summary:
   //    Registers a completion observer notifying the user application when an audio sample buffer is returned to the pool.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall AddCompletionObserver
      (
      IMvAudioSamplesPoolCallback * in_pICallback  // Pointer to the audio sample buffer pool callback interface.
      ) = 0;

   //
   // Summary:
   //    Unregisters a completion observer notifying the user application when an audio sample buffer is returned to the pool.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall RemoveCompletionObserver
      (
      IMvAudioSamplesPoolCallback * in_pICallback  // Pointer to the audio sample buffer pool callback interface.
      ) = 0;

   //
   // Summary:
   //    Modifies the number of the audio samples managed by the buffer pool.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall AdjustSize
      (
      uint32_t in_ui32DesiredPoolSize  // Indicates the new number of audio sample buffers in the buffer pool.
      ) = 0;

   //
   // Summary:
   //    Gets the status number of audio sample buffers currently managed by the buffer pool.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall GetStatus
      (
      uint32_t * out_ui32TotalManaged,    // Indicates the total number of audio sample buffers managed by the buffer pool.
      uint32_t * out_ui32Outside,         // Indicates the number of audio sample buffers that are currently not in the buffer pool.
      uint32_t * out_ui32Inside           // Indicates the number of audio sample buffers that are currently in the buffer pool.
      ) = 0;

   //
   // Summary:
   //    Receives a list of audio sample buffers that are currently not in the buffer pool.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - This method is used for diagnostic purposes.
   //
   virtual HRESULT __stdcall ListOutsidePool
      (
      IMvPoolBufferStateCallback * in_pICallback   // Pointer to the callback interface that will receive the buffers currently not in the buffer pool.
      ) = 0;
   
   //
   // Summary:
   //    Gets the name of the audio sample buffer pool.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall GetPoolName
      (
      wchar_t * out_wszPoolName,    // An array of characters that will receive the name of the audio sample buffer pool.
      uint32_t in_ui32Size          // Indicates the maximum number of characters (in bytes) for out_wszPoolName.
      ) = 0;

   //
   // Summary:
   //    Waits for a list of audio sample buffers to be ready for reading.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_TIMEOUT, if in_ui32Timeout expires before an audio sample buffer is ready for reading.
   // Remarks:
   //    - This method waits for the write completion event of the audio sample buffer to be signaled.
   //      For more details, see the <i>Matrox DSX Topology API User Guide</i>.
   //
   virtual HRESULT __stdcall WaitUntilReadyForRead
      (
      IMvAudioSamples * in_apIAudioSamples[],      // Pointer to the array of audio sample buffers.
      uint32_t          in_ui32Count,              // Indicates the number of audio sample buffers in the array.
      bool              in_bWaitForAll,            // If true, the method waits for all the audio sample buffers to be ready for reading.
                                                   // Otherwise, the method waits for any audio sample buffer to be ready for reading.
      uint32_t          in_ui32Timeout,            // Maximum time (in milliseconds) to wait for audio sample buffers to be ready for reading.
      uint32_t        & out_rui32IndexSignaled     // Indicates the index of the first audio sample buffer that is ready for reading.
      ) = 0;

   //
   // Summary:
   //    Waits for an audio sample buffer to be ready for reading.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_TIMEOUT, if in_ui32Timeout expires before the audio sample buffer is ready for reading.
   // Remarks:
   //    - This method waits for the write completion event of the audio sample buffer to be signaled.
   //      For more details, see the <i>Matrox DSX Topology API User Guide</i>.
   //
   virtual HRESULT __stdcall WaitUntilReadyForRead
      (
      IMvAudioSamples * in_pAudioSamples,    // Pointer to the audio sample buffer interface.
      uint32_t in_ui32Timeout                // Maximum time (in milliseconds) to wait for an audio sample buffer to be ready for reading.              
      ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides the user application with the methods to access all of the Matrox DSX Topology API  
//    interfaces used to configure the complete setup of the DSX cards that are present in the system. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSystemConfiguration : public IUnknown
{
   //
   // Summary:
   //    Creates an enumerator for the cards in the system.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall CreateCardEnumerator
      (
      IMvSystemConfigurationCardEnumerator ** out_ppIEnumerator   // Pointer that receives the interface that enumerates the cards in the system.
      ) = 0;

   //
   // Summary:
   //    Creates an enumerator for the existing system topologies.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall CreateSystemTopologyEnumerator
      (
      IMvSystemTopologyEnumerator ** out_ppIEnumerator   // Pointer that receives the interface that enumerates the existing system topologies.
      ) = 0;

   //
   // Summary:
   //    Creates a new system topology, the hardware profile is deduced from the clock.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall CreateSystemTopology
      (
      const char         * in_kszName,       // Indicates the name of the system topology to create.
      IMvSystemClock     * in_pIClock,       // Pointer to the system clock interface.
      IMvSystemTopology ** out_ppITopology   // Pointer that receives the created system topology interface, if method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates a new system topology, we have to provide the hardware profile as a IMvCardConfiguration.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall CreateSystemTopologyEx
      (
      const char *            in_kszName,       // Indicates the name of the system topology to create.
      IMvSystemClock *        in_pIClock,       // Pointer to the system clock interface.
      IMvCardConfiguration *  in_pCardConfig,   // Pointer to the card configuration.
      IMvSystemTopology **    out_ppITopology   // Pointer that receives the created system topology interface, if method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Loads all the settings saved in the system topology XML string, which are then used to create a new system topology.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //   - When using OpenGL, the call to this method must be done from the OpenGL rendering thread with the OpenGL context made current.
   //   - When using Direct X, the D3D device must first be given to the system configuration interface using IMvSystemConfiguration::SetRenderingMode().
   //
   virtual HRESULT __stdcall LoadSystemTopologyFromXml
      (
      const char           * in_szXmlText,      // Pointer to a null-terminated UTF-8 string containing an XML description of the system topology.
      IMvCardConfiguration * in_pICard,         // Pointer to the card configuration interface used to create the system topology.
      IMvSystemTopology   ** out_ppITopology    // Pointer that receives the system topology interface.
      ) = 0;

   //
   // Summary:
   //    Create a new Universal Clock, this new resource is accessible through the system configuration object.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall CreateUniversalClock 
      (
      SMvUniversalClockInfo&  in_sUniversClockInfo,      // Information required to initialize the universal clock.
      IMvSystemClock **       out_ppINewUniversalClock   // Pointer that receives the universal clock interface.
      ) = 0;

   //
   // Summary:
   //    Creates an enumerator for the existing host clocks.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall CreateHostClockEnumerator
      (
      IMvSystemClockEnumerator ** out_ppIEnumerator   // Pointer that receives the host clocks enumerator.
      ) = 0;

   //
   // Summary:
   //    Creates a buffer pool containing video surfaces.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if in_rsDesc or out_ppNewPool are NULL. 
	//    - MV_E_UNSUPPORTED, if the requested video surface is not supported and cannot
	//      be allocated.
	//    - MV_E_OUT_OF_MEMORY, if no more memory is available.
   // Remarks:
   //   - Only <i>keMvMemoryLocationHost</i> can be used for in_rsDesc.eMemoryLocation.
   //
   virtual HRESULT __stdcall CreateSurfacePool
      (
      const wchar_t   * in_wszPoolName,               // Indicates the name of the pool to create.
      uint32_t          in_ui32InitialSize,           // Indicates the initial number of video surfaces contained in the pool.
      uint32_t          in_ui32MaxSize,               // Indicates the maximum number of video surfaces that the buffer pool can contain.
      const SMvCreateSurfaceDescription & in_rsDesc,  // Structure describing the video surfaces to allocate.
      EMvScanMode       in_eScanMode,                 // Indicates whether the video is interlaced or progressive.
      bool              in_bClearAllocatedSurfaces,   // If true, all the video surfaces in the pool are cleared.
      IMvSurfacePool ** out_ppNewPool                 // Pointer that receives the created video surface pool interface, if method is completed successfully. 
      ) = 0;

   //
   // Summary:
   //    Creates a buffer pool containing user buffers for video surfaces.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if out_ppNewPool is NULL.
   // Remarks:
   //   - This method is used to manage user buffers for video surfaces that encapsulates a user application allocated host-memory buffer.
   //   - The user buffer reference can be assigned with IMvSurface::AssignUserBufferReference().
   //
   virtual HRESULT __stdcall CreateSurfaceUserBufferPool
      (
      const wchar_t   * in_wszPoolName,      // Indicates the name of the pool to create.
      uint32_t          in_ui32InitialSize,  // Indicates the initial number of user buffers contained in the pool.
      uint32_t          in_ui32MaxSize,      // Indicates the maximum number of user buffers that the pool can contain.
      EMvScanMode       in_eScanMode,        // Indicates whether the video is interlaced or progressive.
      IMvSurfacePool ** out_ppNewPool        // Pointer that receives the created pool interface, if method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates a buffer pool containing audio sample buffers.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if in_rsDesc or out_ppNewPool are NULL. 
	//    - MV_E_UNSUPPORTED, if the requested audio sample buffer is not supported and cannot
	//      be allocated.
	//    - MV_E_OUT_OF_MEMORY, if no more memory is available.
   // Remarks:
   //   - Only <i>keMvMemoryLocationHost</i> can be used for in_rsDesc.eMemoryLocation.
   //
   virtual HRESULT __stdcall CreateAudioSamplesPool
      (
      const wchar_t        * in_wszPoolName,                // Indicates the name of the pool to create.
      uint32_t               in_ui32InitialSize,            // Indicates the initial number of audio sample buffers contained in the pool.
      uint32_t               in_ui32MaxSize,                // Indicates the maximum number of audio sample buffers that the pool can contain.
      const SMvCreateAudioSamplesDescription & in_rsDesc,   // Structure describing the audio sample buffers to allocate.
      IMvAudioSamplesPool ** out_ppNewPool                  // Pointer that receives the created buffer pool interface, if method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates a buffer pool containing user buffers for audio samples.
   // Return value: 
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if out_ppNewPool is NULL.
   // Remarks:
   //   - This method is used to manage user buffers for audio samples that encapsulates a user application allocated host-memory buffer.
   //   - The user buffer reference can be assigned with IMvAudioSamples::AssignUserBufferReference().
   //
   virtual HRESULT __stdcall CreateAudioSamplesUserBufferPool
      (
      const wchar_t        * in_wszPoolName,       // Indicates the name of the pool to create.
      uint32_t               in_ui32InitialSize,   // Indicates the initial number of user buffers contained in the pool.
      uint32_t               in_ui32MaxSize,       // Indicates the maximum number of user buffers that the pool can contain.
      IMvAudioSamplesPool ** out_ppNewPool         // Pointer that receives the created pool interface, if method is completed successfully.
      ) = 0;

   //
	// Summary:
	//    Retrieves the amount of memory (in bytes) that is required to allocate the specified surface.
	// Description:
	//    This method does not allocate this memory for the surface. It is for information purposes only.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_NOT_SUPPORTED, if in_krsDescription is not supported.
	//    - MV_E_FAIL, if a fatal error occurs.
   //
   virtual HRESULT __stdcall GetSurfaceMemoryFootprint
      (
      const SMvCreateSurfaceDescription & in_krsDescription,            // Pointer to the structure describing the surface. The memory 
                                                                        // size computations are based on the surface description.
      uint32_t                          * out_pui32MemorySizeInBytes    // Pointer that will be filled with the memory size in bytes.
      ) = 0; 

   //
	// Summary:
	//    Gets the amount of memory (in bytes) that is required to allocate the specified audio sample buffer.
	// Description:
	//    This method does not allocate memory for the buffer. It is for information purposes only.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if any of the pointers are NULL. 
	//    - MV_E_INVALID_STRUCTURE_SIZE, if the size field of in_krsDescription or in_krsResolutionInfo is not initialized properly. 
	//    - MV_E_UNSUPPORTED_FRAMERATE, if the computation cannot be done using the resolution frame rate. 
	//    - MV_E_UNSUPPORTED_SCANMODE, if the computation cannot be done using the resolution scan mode. 
   //
   virtual HRESULT __stdcall GetAudioSamplesMemoryFootprint
      (
      const SMvCreateAudioSamplesDescription & in_krsDescription,       // Pointer to the structure describing the audio sample buffer. 
                                                                        // The memory size computations are based, in part, on the 
                                                                        // audio sample buffer description.
      const SMvResolutionInfo                & in_krsResolutionInfo,    // Pointer to the resolution in which the audio sample buffer will 
                                                                        // be used. The memory size computations are based, in 
                                                                        // part, on the audio sample buffer description.
      uint32_t * out_pui32MemorySizeInBytesTypeA,                       // Pointer that will be filled with the memory size, in bytes.
                                                                        // If the audio sample buffer dimension is not an integer value 
                                                                        // (any M factor resolution, such as 23.98, 29.97, or 59.94 fps),  
                                                                        // this parameter represents the biggest value that can be allocated.
      uint32_t * out_pui32MemorySizeInBytesTypeB                        // If the audio sample buffer dimension is not an integer value
                                                                        // (any M factor resolution, such as 23.98, 29.97, or 59.94 fps), 
                                                                        // this parameter represents the smallest value that can be allocated. Otherwise, 0 is allocated.
      ) = 0;

   //
   // Summary:
   //   Indicates which rendering API will be used for the GPU nodes.
   // Remarks:
   //   - When OpenGL rendering is used, the method must be called from the rendering thread with the OpenGL context made current.
   //
   virtual HRESULT __stdcall SetRenderingMode
      (
      IMvCardConfiguration      * in_pICard,                // Pointer to the card configuration interface.
      EMvGPUTransferRenderingMode in_eRenderingMode,        // Indicates the rendering mode used.
      EMvComponentSelection       in_eComponentSelection,   // Indicates where the first luma component is located in the texture.
      void                      * in_pD3DDevice             // Pointer to the ID3D11Device object that represents the device created when using DirectX 11.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface required for Universal clock
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSystemClockUniversal : public IUnknown
{
   //
   // Summary:
   //    Get the FrameRate at which the clock operates
   // Return value:
   //    - MV_NOERROR, if no errors occur.
   //    - MV_E_INVALID_STRUCTURE_SIZE, if there is a problem with out_refsMvResolutionInfo
   //
   virtual HRESULT __stdcall GetResolution
      ( 
      SMvResolutionInfo& out_refsMvResolutionInfo        // Structure that receives the clock resolution.
      )= 0;

   //
   // Summary:
   //    Tell us if our clock is synchronized to the time server or not
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_STRUCTURE_SIZE, if there is a problem with out_rsTimeServerStatus
   //
   virtual HRESULT __stdcall GetStatus
      ( 
      SMvUniversalClockStatus& out_rsTimeServerStatus    // Structure that receives the clock status.
      ) = 0;

   //
   // Summary:
   //    Register and unregister to the universal clock error notification
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_ALREADY_ATTACHED, if this object has already registered for this callback.
   //
   virtual HRESULT __stdcall RegisterCallbackForNotification
      (
      IMvUniversalClockNotificationCallback * in_pINotificationCallback    // Pointer to the callback interface that receives on clock events
      ) = 0;

   virtual HRESULT __stdcall UnregisterCallbackForNotification
      (  
      IMvUniversalClockNotificationCallback * in_pINotificationCallback    // Pointer to the callback interface that receives on clock events
      ) = 0;
   
   //
   // Summary:
   //    Get the Time server name OR it's IP Address (as it was given at creation time)
   // Return value:
   //    - MV_NOERROR, if no errors occur.
   //    - MV_E_INVALID_PARAMETER, if the parameter is NULL
   //    - MV_E_NOT_SUPPORTED, if the engine is not in "software mode"
   // Remarks:
   //    - A empty out_szNtpServerAddress means the universal clock is NOT synchronized to any external clock synchronisation source.
   //
   virtual HRESULT __stdcall GetTimeServerName
      (
      int      in_iNtpServerAddressCharCount,                              // Maximum number of characters that out_szNtpServerAddress can contains.
      char *   out_szNtpServerAddress                                      // Pointer to the buffer containing the NTP server name or IP address.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface required for DSX core Seat Notifications
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvDSXCoreSeatNotification : public IUnknown
{
   //IMvDSXCORENotificationCallback
   // Summary:
   //    Register and unregister to the seat error notification
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_ALREADY_ATTACHED, if this object has already registered for this callback.
   //
   virtual HRESULT __stdcall RegisterCallbackForNotification
      (
      IMvDSXCORENotificationCallback * in_pINotificationCallback    // Pointer to the callback interface that receives on clock events
      ) = 0;

   virtual HRESULT __stdcall UnregisterCallbackForNotification
      (
      IMvDSXCORENotificationCallback * in_pINotificationCallback    // Pointer to the callback interface that receives on clock events
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents an RTP (Real-time Transport Protocol) sender stream in the system topology. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvRTPSenderStream : public IMvStream
{
public:
   //
   // Summary:
   //   Gets the Session Description Protocol (SDP) data. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Fields and values are compliant with RFC 4566.
   //
   virtual HRESULT GetSDPData
      (
      uint32_t in_ui32MaxNbOfChars,    // Indicates the maximum number of characters the SDP data can contain.
      char* io_szSDPData,              // Pointer that will receive the SDP data string.
      uint32_t* io_pui32NbOfCharsUsed  // Indicates the number of characters returned to the SDP data string.
      ) = 0;

   //
   // Summary:
   //   Modifies the current Session Description Protocol (SDP) data. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Fields and values must be compliant with RFC 4566.
   //
   virtual HRESULT SetSDPData
      (
      uint32_t in_ui32NbOfChars,    // Indicates the number of characters of the new SDP data string. 
      const char * in_szSDPData     // Contains the new SDP data string.
      ) = 0;

   //
   // Summary:
   //   Gets the current settings of the RTP sender stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT GetRTPSenderStreamSettings
      (
      SMvRTPSenderStreamSettings& io_rsStreamSettings    // Structure that receives the RTP sender stream settings.
      ) = 0;

   //
   // Summary:
   //   Modifies the current settings of the RTP sender stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT SetRTPSenderStreamSettings
      (
      const SMvRTPSenderStreamSettings& in_krsStreamSettings   // Structure of the RTP sender stream settings.
      ) = 0;

   //
   // Summary:
   //   Gets the input compressed host node currently bound to the RTP sender stream.   
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT GetInputNode
      (
      IMvCompressedHostNode** out_ppIInputNode     // Pointer that receives the input compressed host node interface.
      ) = 0;

   //
   // Summary:
   //   Modifies the input compressed host node currently bound to the RTP sender stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT SetInputNode
      (
      IMvCompressedHostNode* in_pIInputNode  // Pointer to the new input compressed host node interface.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents a decoder stream in a workflow topology.
// Remarks:
//    - This interface is used to decompress video, audio, and VANC data.
//    - The input of this stream is a compressed host node, and the output is a host node.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvDecoderStream : public IMvStream
{
   //
   // Summary:
   //   Gets the input compressed host node currently bound to the decoder stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetInputNode
      (
      IMvCompressedHostNode** out_ppIInputNode		// Pointer that receives the input compressed host node interface.
      ) = 0;

   //
   // Summary:
   //   Modifies the input compressed host node currently bound to the decoder stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_WRONG_STATE, if the input compressed host node is changed when the decoder stream is still decoding.
   // Remarks:
   //    - The new input compressed host node must have the same resolution as the old input compressed host node.
   //    - The input compressed host node can only be changed when the decoder stream is stopped.
   //
   virtual HRESULT __stdcall SetInputNode
      (
      IMvCompressedHostNode* in_pIInputNode		// Pointer to the new input compressed host node interface.
      ) = 0;

   //
   // Summary:
   //   Gets the output host node currently bound to the decoder stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetOutputNode
      (
      IMvHostNode** out_ppIOutputNode		// Pointer that receives the output host node interface.
      ) = 0;

   //
   // Summary:
   //   Modifies the output host node currently bound to the decoder stream.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
    //   - MV_E_WRONG_STATE, if the output compressed host node is changed when the decoder stream is still decoding.
   // Remarks:
   //    - The new output host node must have the same resolution and same memory location as the old output host node.
   //    - The output host node can only be changed when the decoder stream is stopped.
   //
   virtual HRESULT __stdcall SetOutputNode
      (
      IMvHostNode* in_pIOutputNode	// Pointer to the new output host node interface. 
      ) = 0;

   //
   // Summary:
   //   Starts the decoder stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Before the decoder stream can be started, a reference frame may be required.
   //
   virtual HRESULT __stdcall StartDecoding
      (
      uint64_t in_ui64EstimatedFirstPresentationTime	// Indicates the time the decoder stream will start. 
      ) = 0;

   //
   // Summary:
   //   Stops the decoder stream. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This method will force the decoder to stop at the specified time.
   //
   virtual HRESULT __stdcall StopDecoding
      (
      uint64_t in_ui64EstimatedLastPresentationTime	// Indicates the time the decoder stream will stop. 
      ) = 0;

   //
   // Summary:
   //    Configures the decoder stream so that it is ready to decode.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This method is synchronous and must be called before calling IMvDecoderStream::StartDecoding().
   //    - Depending on the decoder used, this method can require up to three seconds to complete.
   //
   virtual HRESULT __stdcall PrepareStream() = 0;

   //
   // Summary:
   //    Gets the GUID that was used to create the decoder stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetGUID
      (
      GUID &out_rGUID	// Indicates the GUID of the codec that was used to create the decoder stream.
      ) = 0;

};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents an RTP (Real-time Transport Protocol) receiver   
//    stream in a system topology.      
// Note:
//    - The RTP receiver stream receives RTP packets via UDP (User Datagram Protocol) 
//      and outputs TS (Transport Stream) packets to a compressed host node.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvRTPReceiverStream : public IMvStream
{

   //
   // Summary: 
   //    Gets the output compressed host node currently bound to the RTP receiver stream.
   // Return value: 
   //    MV_NOERROR,  if completed successfully. 
   //
   virtual HRESULT GetOutputNode
      (
      IMvCompressedHostNode **out_ppOutputNode  // Pointer that receives the output compressed host node interface.
      ) = 0;

   //
   // Summary: 
   //    Gets the currently settings of the RTP receiver stream.
   // Return value: 
   //    MV_NOERROR,  if completed successfully. 
   //
   virtual HRESULT GetRTPReceiverSettings
      (
      SMvRTPReceiverStreamSettings &out_rSettings  //Structure of the RTP receiver stream settings.
      ) = 0;

   //
   // Summary: 
   //    Gets the network interface settings to be used by the RTP receiver stream.
   // Return value: 
   //    MV_NOERROR,  if completed successfully. 
   //
   virtual HRESULT GetNetworkInterfaceSettings
      (
      SMvRTPReceiverStreamNetworkSettings &out_rSettings   // Structure containing the settings for initiating a network connection.
      ) = 0;


  //
   // Summary: 
   //    Modifies the output compressed host node currently bound to the RTP receiver stream.
   // Return value: 
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_WRONG_STATE, if the output compressed host node is changed when the RTP receiver stream is streaming data.
   // Remarks: 
   //    This method can only be called when RTP receiver stream is stopped.
   //
   virtual HRESULT SetOutputNode
      (
      IMvCompressedHostNode *in_pOutputNode  // Pointer to the new output comressed host node interface.
      ) = 0;

   //
   // Summary:
   //    Modifies the current settings of the RTP receiver stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_WRONG_STATE, if the settings of the RTP receiver stream are modified when the RTP receiver stream is streaming data.
   // Remarks:
   //    This method can only be called when the RTP receiver stream is stopped.
   //
   virtual HRESULT SetRTPReceiverSettings
      (
      const SMvRTPReceiverStreamSettings & in_sSettings    // Structure of the RTP receiver stream settings.
      ) = 0;

   //
   // Summary:
   //    Starts the RTP receiver stream.
   // Return value:
   //    MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT StartRTPReceiverStream() = 0;

   //
   // Summary:
   //    Stops the RTP receiver stream.
   // Return value:
   //    MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT StopRTPReceiverStream() = 0;

   //
   // Summary:
   //    Allows the RTP receiver stream to establish a connection using Session Announcement Protocol (SAP) data.
   // Return value:
   //    MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT ConnectWithSAP
      (
      const char    *in_szNIC,              // Network interface card address.
      const char    *in_szSAPSessionName,   // Pointer to the string containing the SAP data. This will be used to connect to the remote host.
      uint32_t       in_ui32Timeout          // Indicates the maximum time (in milliseconds) to wait for the RTP receiver stream to connect to the remote host. 
      ) = 0;

   //
   // Summary: 
   //    Allows the RTP receiver stream to establish a connection using the network settings.
   // Return value:
   //    MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT ConnectWithNetworkInterfaceSettings
      (
      const SMvRTPReceiverStreamNetworkSettings & in_psNetworkInterface // Pointer to the structure containing the settings for initiating a network connection.
      ) = 0;

   //
   // Summary:
   //    Allows the RTP receiver stream to establish a connection using Session Description Protocol (SDP) data.
   // Return value:
   //    MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT ConnectWithSdpStringDescription
      (
      const char  *in_szNIC,          // Network interface card address.
      const char  *in_szSDPData       // Pointer to the string containing the SDP data.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides a callback notification for writing compressed data to a compressed host node.
// Remarks:
//    - The compressed data is located in host memory.
//    - Use the IMvCompressedHostNode interface to register and unregister the IMvCompressedNodeNotificationForWrite interface.
//    - Only one IMvCompressedNodeNotificationForWrite interface can be registered for writing to IMvCompressedHostNode.
//////////////////////////////////////////////////////////////////////////////////
interface IMvCompressedNodeNotificationForWrite : public IUnknown
{
public:
   //
   // Summary:
   //    Notifies when compressed data can be sent to a compressed host node.
   // Remarks:
   //    The data must be written before control is returned to the compressed host node.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall NotifyForWrite
      (
      SMvCompressedNodeNotificationData * io_psNotificationData   // Pointer to the structure containing the compressed node notification data.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides a callback notification for reading compressed data from a compressed host node.
// Remarks:
//    - The compressed data is located in host memory.
//    - Use the IMvCompressedHostNode interface to register and unregister the IMvCompressedNodeNotificationForRead interface.
//    - More than one IMvCompressedNodeNotificationForRead interface can be registered for reading from IMvCompressedHostNode.
//////////////////////////////////////////////////////////////////////////////////
interface IMvCompressedNodeNotificationForRead : public IUnknown
{
   //
   // Summary:
   //    Notifies when compressed data is ready to be read from a compressed host node.
   // Remarks:
   //    The data must be read before control is returned to the compressed host node.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall NotifyForRead
      (
      SMvCompressedNodeNotificationData * in_psNotificationData   // Pointer to the structure containing the compressed node notification data.
      ) = 0;
};

#pragma pack(pop)

