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

#pragma once

#include "MvFlexAPIPublicSDK.h"
#include "MvFlexDefinitions.h"
#include "mvVbiInformation.h"

//
// F O R W A R D   D E C L A R A T I O N
//
interface IMvSettingsManager;
interface IMvFlexEngine;
interface IMvFlex3DDevice;
interface IMvAudioMixer;
interface IMvCodec;
interface IMvFlexWriter;
interface IMvFlexReader;
interface IMvEffect;
interface IMvCompositor;
interface IMvInputOutput;
interface IMvInputOutputIndependent;
interface IMvXScalerHD;
interface IMvSlowMotion;
interface IMvDVAudio;
interface IMvAVContentPoolManager;
interface IMvCustomFileSystemIO;
interface IMvAudioVoiceOverMixerControl;
interface IMvPlayListCreator;
interface IMvPlayList;
interface IMvPlayListElement;
interface IMvFrameProperties;
interface IMvFlex1394Writer;
interface IMvFlex1394Reader;
interface IMvMpegStreamGop;
interface IMvMXOControl;
interface IMvDisplayManager;
interface IMvFlexAsynchronousErrorNotification;
interface IMvMediaReader;
interface IMvMediaWriter;
interface IMvIPInputOutput;
interface IMvVancPacketExtractor;
interface IMvVancPacketInserter;
interface IMvVancConverter;
interface IMvTSEncoder;
interface IMvMPEG2TSMuxer;
interface IMvSdiVideoInputConnector;
interface IMvAesEbuAudioInputPairConnector;
interface IMvSdiVideoOutputConnector;
interface IMvAesEbuAudioOutputPairConnector;
interface IMvCardConfiguration;
interface IMvOutputStream;
interface IMvdResourceManager;
interface IMvWatchdog;
interface IMvCardUpgrade;
interface IMvGpuTransfer;
interface IMvFlexTunnelToDirectShowManager;
interface IMvFlexTunnelToDirectShow;
interface IMvSystemClock;
interface IMvSystemClockEnumerator;
interface IMvMPEG2TSDemuxer;
interface IMvMPEG2TSDemuxerNotification;
interface IMvConnectorsEnumerator;
interface IMvSfpIp;
interface IMvSfpIpEnumerator;
interface IMvSfpIpNotificationCallback;
interface IMvSdiIpInputConnectorsEnumerator;
interface IMvSdiIpOutputConnectorsEnumerator;
interface IMvDSXCORENotificationCallback;
interface IMvfDSXCoreLicenseManager;
struct SMvColor;

// from mvddef.h
struct SMvAudioVideoFileInfo;


//////////////////////////////////////////////////////////////////////////////////
// C O N S T S
//////////////////////////////////////////////////////////////////////////////////
const unsigned long g_kulMaxInputSurfaces = 128;


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Allows the management of a pool of multiple surfaces. 
// Remarks:
//    - This interface is obtained at the creation of a surface container with the 
//      IMvFlexEngine::CreateSurfaceContainer method.
//    - This interface is derived from the IMvSurface interface but none of the interface's methods are 
//      supported. They all return the error code: MV_E_NOT_SUPPORTED_BY_SURFACE_CONTAINER.
//    - This interface is derived from the IMvAVContent interface but only the methods related to custom 
//      object are supported: GetCustomObject(), AttachCustomObject(), DetachCustomObject() and Flush().
//      All the other IMvAVContent methods return the error code : MV_E_NOT_SUPPORTED_BY_SURFACE_CONTAINER.
//    - When the container is released, the IMvContainer::RemoveAll() and IMvAVContent ::Flush() methods
//      are called automatically.
//
//////////////////////////////////////////////////////////////////////////
interface IMvContainer : public IMvSurface
{
	//
	// Summary:
	//    Returns the object count in the container.
	// Return value:
	//    - Number of objects in the container.
	//
	virtual unsigned long __stdcall  GetObjectCount () = 0;

	//
	// Summary:
	//    Returns the object from the container list.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_POINTER, one of the pointer's parameters is NULL.
	//    - MV_E_INVALID_PARAMETER, index is invalid.
	// Remarks:
	//    - The object's reference count has already been incremented by the method.
	//
	virtual HRESULT __stdcall GetObject
		(
		int           in_iIndex,     // Index of the object element in the container's list of objects.
		IMvSurface ** out_ppIObject  // Pointer that receives the object's address.
		) = 0;

	//
	// Summary:
	//    Adds an object at the end of the container list.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if one of the pointer's parameters is NULL.
	//    - MV_E_FAIL, if failed.  
	// Remarks:
	//    - The container increments the object's reference count until it is removed from the list.
	//
	virtual HRESULT __stdcall AddObject
		(
		IMvSurface * in_pIObject   // The object to add at the end of the container's list.
		) = 0;

	//
	// Summary:
	//    Removes all objects from the container list.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if failed.  
	// Remarks:
	//    - The container removes all of the object's references when the list is cleared.
	virtual HRESULT __stdcall RemoveAll() = 0;

};

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Main interface used to control and query the AV Content pool manager.  It is used to add or
//    remove elements from the pool.
//
//////////////////////////////////////////////////////////////////////////
interface IMvAVContentPoolManager : public IUnknown
{
	//
	// Summary:
	//    Registers AVContent with the A/V Content Pool Manager.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if the pointer is NULL or if it is not a valid pointer to  AVContent.
	// Remarks:
	//    - When the method returns, the AVContent is managed by the A/V Content Pool Manager, but it is 
	//      considered outside the pool (already in use).
	//    - From the caller's point of view, the AVContent is now the same as if it was obtained by an 
	//      GetAVContent() method call or received by an IMvAVContentReceiver interface object.
	//    - When the caller releases its references on the AVContent, it will return to the A/V Content 
	//      Pool and be available for another caller. The AVContent is considered as already used (outside
	//      of the pool) when the method returns.
	virtual HRESULT __stdcall LinkAVContent
		(
		IMvAVContent* in_pIAVContent  // Pointer to AVContent that will be registered by the manager.   
		) = 0;

	//
	// Summary:
	//    Synchronously retrieves an AVContent from the A/V Content Pool. This call is non-blocking.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if the pointer is NULL or if it is not a valid pointer to a AVContent.
	//    - MV_E_OUT_OF_MEMORY, if the pool is empty, or if all the AVContent is not available.
	// Remarks:
	//    - This method will fail if the pool is empty, or if no AVContent is currently available.
	virtual HRESULT __stdcall GetAVContent
		(
		IMvAVContent** out_ppIAVContent  // Pointer that will receive the AVContent.  
		) = 0;

	//
	// Summary:
	//    Synchronously retrieves an AVContent from the A/V Content Pool. This call is blocking.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if the pointer is NULL or if it is not a valid pointer to  AVContent.
	//    - MV_E_OUT_OF_MEMORY, if the pool does not manage any AVContent.
	// Remarks:
	//    - This method will fail if the pool does not manage any AVContent, but if it does manage some 
	//      AVContent, this call will block and wait until an AVContent become available.
	virtual HRESULT __stdcall WaitForAVContent
		(
		IMvAVContent** out_ppIAVContent  // Pointer that will receive the AVContent.    
		) = 0;

	//
	// Summary:
	//    Requests to permanently remove AVContent from the A/V Content Pool.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if the pointer is NULL or if it is not a valid pointer.
	//    - MV_E_OUT_OF_MEMORY, if the pool is empty.
	// Remarks:
	//    - When AVContent is available, the supplied IMvAVContentReceiver interface is called with
	//      that AVContent.
	//    - The receiver can be called at any moment, either synchronously from within the thread 
	//      currently performing the RequestToUnlinkAVContent() method call, or asynchronously from 
	//      another thread. The receiver MUST be prepared to handle both situations. In all cases,
	//      there are NO guaranties that the RequestToUnlinkAVContent method call will have returned
	//      when the receiver is called.
	//    - The received AVContent is no longer managed by the A/V Content Pool. If the receiver doesn't 
	//      do an AddRef() to keep it, it will be destroyed.
	//    - If the Pool is empty, the method fails.
	virtual HRESULT __stdcall RequestToUnlinkAVContent
		(
		IMvAVContentReceiver* in_pIAVContentReceiver // Interface that will be called to give AVContent
		// as soon as it becomes available.
		) = 0;

	//
	// Summary:
	//    Requests AVContent for temporary use. The AVContent will return to the pool automaticaly
	//    when it is no longer used.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if the pointer is NULL or if it is not a valid pointer.
	//    - MV_E_OUT_OF_MEMORY, if the pool is empty.
	// Remarks:
	//    - When AVContent is available, the supplied IMvAVContentReceiver interface is called with
	//      that AVContent.
	//    - The receiver can be called at any moment, either synchronously from within the thread that's 
	//      currently performing the RequestToUseAVContent method call, or asynchronously from another 
	//      thread. The receiver MUST be prepared to handle both situations. In all cases, there are NO 
	//      guaranties that the RequestToUseAVContent method call will have returned when the receiver 
	//      is called.
	//    - When the AVContent is released (or if the receiver doesn't keep it), the AVContent returns 
	//      automatically to the A/V Content Pool and when its read completion event is signaled, it is
	//      sent to the Completion Observer (if any), flushed, and recycled.
	//    - The method fails if the A/V Content Pool is empty.
	virtual HRESULT __stdcall RequestToUseAVContent
		(
		IMvAVContentReceiver* in_pIAVContentReceiver // Interface that will be called to give AVContent
		// as soon as it becomes available.  
		) = 0;

	//
	// Summary:
	//    Returns the number of AVContent that is managed by the pool manager.
	// Return value:
	//    - Values representing the total number of managed AVContent.
	virtual unsigned long __stdcall GetNumberOfLinkedAVContent() = 0;

   //
   // Summary:
   //    This can be called to send diagnostic logs to the Matrox Debugging Tool 
   //    (mvValidationToolForClients.exe). Logs will enumerate a list of all the 
   //    AVContents currently out of the pool with details as to why they do not 
   //    come back to the pool.
   //    Logs must have been enabled for the pool via the EnableLogging method
   //    prior to calling this method.
   // Return value:
   //    MV_NOERROR
   // Remarks:
   //    AVContents return to their pool if the following conditions are met:
   //    1) Their COM Reference count came down to 1 (the last count being owned by the pool)
   //    2) Their Read Count came down to 0 and their Read completion event got signaled
   //    3) Their Write Count came down to 0 and their Write completion event got signaled
   // Note:
   //    If the Read or Write count of an AVContent was never increased to 1 in the
   //    first place, its Read/Write completion event WILL NOT BE SIGNALED. As such, the
   //    AVContent will not return to its pool.
	virtual HRESULT __stdcall LogInformation() = 0;

	//
	// Summary:
	//    Returns current status of the pool manager.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_FAIL, if an error occurred
	virtual HRESULT __stdcall GetPoolManagerStatus
		(
		unsigned long & io_rulTotalNumberOfAVContentsManagedByPool,
		unsigned long & io_rulNumberOfAVContentsCurrentlyOutsidePool,
		unsigned long & io_rulNumberOfAVContentsCurrentlyInPool,
		unsigned long & io_rulNumberOfPendingReceivers
		) = 0;

	//
	// Summary:
	//    Returns the names of surfaces currently out of the pool manager.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_FAIL, if an error occurred
	virtual HRESULT __stdcall GetNameListOfAVContentsOutsidePool
		(
		std::list<std::wstring>& io_listwszAVContentsCurrentlyOutsidePool
		) = 0;

	//
	// Summary:
	//    Synchronously retrieves an AVContent from the A/V Content Pool. This call is blocking.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if the pointer is NULL or if it is not a valid pointer to  AVContent.
	//    - MV_E_OUT_OF_MEMORY, if the pool does not manage any AVContent.
	//    - MV_E_TIME_OUT, if an AVContent was not made available during the time specified by in_ulTimeout.
	// Remarks:
	//    - This method will fail if the pool does not manage any AVContent, but if it does manage some 
	//      AVContent, this call will block and wait until an AVContent become available or until 
	//      in_ulTimeout milliseconds elapsed.
	virtual HRESULT __stdcall WaitForAVContentWithTimeout
		(
		IMvAVContent** out_ppIAVContent,  // Pointer that will receive the AVContent. 
		unsigned long  in_ulTimeout       // Maximum timeout in milliseconds to wait for an AVContent before returning.
		) = 0;

   //
   // Summary:
   //    Enables or disables logging of activities for the current pool
   // Return value:
   //    - MV_NOERROR, if completed successfully
   // Remarks:
   //    - Logs generated by this command are sent to the Matrox debugging tool 
   //      (mvValidationToolForClients.exe) packaged with the DSX.SDK
   virtual HRESULT __stdcall EnableLogging
      (
      bool  in_bEnable // If true, enables logging for this pool.
      ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to create a Flex Engine on a hardware profile.
//////////////////////////////////////////////////////////////////////////////////
interface IMvFlexEngineCreator : public IUnknown
{
	//
	// Summary:
	//    Creates and initializes an asynchronous Flex Engine for a specific hardware profile. 
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_ALREADY_INITIALIZED, if a Flex Engine is already in use for the specified profile.
	//    - MV_E_MAX_FLEXENGINE_REACHED, if the maximum number of Flex Engines that can be created at
	//      the same time has been reached.
	//    - MV_E_PROFILE_NOT_FOUND, if the specified hardware profile is not installed.
	//    - MV_E_FAIL, if failed.
	// Remarks:
	//    - All available hardware profiles can be enumerated with the IMvHardwareProfileEnumerator interface.

	virtual HRESULT __stdcall  CreateAsynchronousEngine
		(
		EMvHardwareProfile  in_eHardwareProfileType,    // Indicates which hardware profile to use to create the Flex Engine.
		unsigned long       in_ulHardwareProfileIndex,  // Specifies the index of the hardware profile to use.
		SMvResolutionInfo * in_psEditResolution,        // Pointer to the editing resolution structure of the Flex Engine. 
		unsigned long       in_ulThreadPriority,        // Base priority of Flex threads (not affecting CPU-intensive tasks).
		IMvFlexEngine    ** out_ppIFlexEngine           // Pointer that receives the created IMvFlexEngine interface.
		) = 0;

   //
	// Summary:
	//    This method is now deprecated. It gives the same result as if IMvFlexEngineCreator::CreateAsynchronousEngine() was called.
   // Note:
   //    This method is now deprecated. It still works, but it will give the same result as if
   //    CreateAsynchronousEngine was called and will generate a compile time warning.
   // Return value:
   //    - see CreateAsynchronousEngine
	
   virtual HRESULT __stdcall  CreateAsynchronousEngineWithThreadingControl
		(
		EMvHardwareProfile  in_eHardwareProfileType,    // Indicates which hardware profile to use to create the Flex Engine. 
		unsigned long       in_ulHardwareProfileIndex,  // Specifies the index of the hardware profile to use. 
		SMvResolutionInfo * in_psEditResolution,        // Pointer to the editing resolution structure of the Flex Engine. 
		unsigned long       in_ulThreadPriority,        // Base priority of Flex threads (not affecting CPU-intensive tasks).
		unsigned long       in_ulIgnored,               // IGNORED.
		unsigned long       in_ulIgnored2,               // IGNORED.
		IMvFlexEngine    ** out_ppIFlexEngine           // Pointer that receives the created IMvFlexEngine interface.
		) = 0;    
#pragma deprecated(CreateAsynchronousEngineWithThreadingControl)
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides the user application with the methods to gain access to all of the Flex modules and components.
// Remarks:
//    The Create_X methods internally call ::CoCreateInstance() for the interface specified. Therefore,
//    multiple instances can be created. The Get_X_Interface methods return a reference to the COM
//    interface already created by the Flex Engine. The supported query interfaces are: 
//    IMvCodecEnumerator using IID_ImvcodecEnumerator and IMvEffectEnumerator using IID_IMvEffectEnumerator.
//////////////////////////////////////////////////////////////////////////////////
interface IMvFlexEngine : public IUnknown
{
	//
	// Summary:
	//    Applies a separate volume for each track in a multi-track audio sample.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if in_pISrcBuffer, or in_pIDestBuffer = NULL 
	//    - MV_E_BUFFER_FORMAT_MISMATCH, if the channel type of the source audio sample does not 
	//      match channel type of destination audio sample. 
	//    - MV_E_INVALID_PARAMETER, if channel type of the source audio sample does not match
	//      in_kulVolumeArraySize.> 
	//    - MV_E_INVALID_PARAMETER, if in_psVolumeArray = NULL or in_kulVolumeArraySize = 0. 
	// Remarks:
	//    - This method consumes the auto-fades specified in the source audio sample. 
	//    - Auto-fades specified in the destination buffers are ignored. 
	//    - The ApplyVolume method's implementation will perform an IMvAudioSamples::SetLength on 
	//      the destination buffer in_ppIDestBuffer once its asynchronous processing is completed.
	//      You will need to take special precautions if the source buffer in_pISrcBuffer and the 
	//      destination buffer in_pIOutputBuffer are not the same length. 
	virtual HRESULT _stdcall ApplyVolume
		(
		IMvAudioSamples        * in_pSrcBuffer,         // Pointer to the source multi-track audio
		// sample.
		IMvAudioSamples        * in_pDestBuffer,        // Pointer to the destination multi-track 
		// audio sample.
		SMvAudioMonoVolumeInfo * in_psVolumeArray,      // Pointer to an array of SmvAudioMonoVolumeInfo
		// structures containing volume settings
		// for each track.
		const unsigned long      in_kulVolumeArraySize, // Number of SmvAudioMonoVolumeInfo structures 
		// in volume array.
		unsigned long            in_ulIgnored           // IGNORED.
		) = 0;

	//
	// Summary:
	//    Copies the audio data of an audio sample buffer to another audio sample buffer.  
	//       It also applies auto fade if requested.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if one or more parameters are invalid.
	// Remarks:
	//    - Audio output only accepts 32-bit audio samples at 48 KHz. The number of valid bits (16,
	//      20 or 24) contained in a 32-bit sample is left-justified. In other words, an audio sample
	//      located in I/O memory can always be seen as a 24-bit inside 32-bit audio sample.
	//    - Copying 16-bit or 24-bit audio samples from host to I/O memory (or vice-versa) is not supported.
	//    - Here are the supported copy operations and the processors used depending on the memory 
	//      location of the source and destination audio samples: 
	// <table>
	// Source     Actual        Source       Destination   Actual        Destination   Processor   Notes
	//  Memory     source        valid Bits   memory        destination   Valid Bits    used        
	//  Location   \sample                    Location      \sample                                 
	//             size (bits)                              size (bits)                             
	// ---------  ------------  -----------  ------------  ------------  ------------  ----------  ----------------------------------------------------------
	// Host       16            16           Host          16            16            CPU         Pure copy only.
	// Host       32            16, 20, 24   Host          32            16, 20, 24    CPU         Pure copy only. Cannot perform any conversions. Since the
	//                                                                                              valid bits of an audio sample are left-justified, the bit
	//                                                                                              rate of source sample and destination sample have no
	//                                                                                              importance for the copy operation.
	// Host       24            24           Host          24            24            CPU         Pure copy only.
	// Host       16            16           Host          32            24            CPU         To convert a 16-bit sample to a 32-bit sample, uses a
	//                                                                                              24-bit destination sample.
	// Host       32            24           Host          16            16            CPU         To convert a 32-bit sample (uses 24-bits as the source
	//                                                                                              \sample) into a 16-bit sample. 
	//
	// Host       24            24           Host          24            32            CPU         To convert a 24-bit sample (uses 24-bits as the source
	//                                                                                              \sample) into a 32-bit sample.
	// Host       24            32           Host          24            24            CPU         To convert a 32-bit sample (uses 24-bits as the source
	//                                                                                              \sample) into a 24-bit sample.
	// Host       32            Don't care   IO            32            Don't care    IO DMA      Pure 32-bit copy only. Number of audio tracks in the source
	//                                                                                              \and destination samples must be the same.
	// IO         32            Don't care   Host          32            Don't care    IO DMA      Pure 32-bit copy only. Number of audio tracks in the source
	//                                                                                              and destination samples must be the same.
	// </table>
	//
	virtual HRESULT __stdcall CopyAudioSamples
		(
		IMvAudioSamples * in_pIAudioSamplesSource,      // Pointer to the source audio samples interface.
		IMvAudioSamples * in_pIAudioSamplesDestination, // Pointer to the destination audio samples interface.
		unsigned long     in_ulIgnored                  // IGNORED.
		) = 0;

	//
	// Summary:
	//    Converts two mono audio samples to one stereo audio sample.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if one or more parameters are invalid. 
	virtual HRESULT __stdcall CopyAudioSamplesMonoToStereo
		(
		IMvAudioSamples  *in_pIAudioSamplesSourceLeft,  // Pointer to the Left source (mono) audio samples.
		IMvAudioSamples  *in_pIAudioSamplesSourceRight, // Pointer to the Right source (mono) audio samples.
		IMvAudioSamples  *in_pIAudioSamplesDestination, // Pointer to the destination (stereo) buffer.
		unsigned long     in_ulIgnored                  // IGNORED.
		) = 0;

	//
	// Summary:
	//    Converts a stereo audio sample to two mono audio samples.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if one or more parameters are invalid.
	virtual HRESULT __stdcall CopyAudioSamplesStereoToMono
		(
		IMvAudioSamples  *in_pIAudioSamplesSource,            // Pointer to the source (stereo) audio samples.
		IMvAudioSamples  *in_pIAudioSamplesDestinationLeft,   // Pointer to left destination (mono) audio samples.
		IMvAudioSamples  *in_pIAudioSamplesDestinationRight,  // Pointer to right destination (mono) audio samples.
		unsigned long     in_ulIgnored                  // IGNORED. 
		) = 0;

	//
	// Summary:
	//    Converts 4, 8, or 16 mono audio samples to one multi-track audio sample containing 4, 8,
	//    or 16 tracks.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if in_ppISrcBufferArray, or in_pIDestBuffer = NULL. 
	//    - MV_E_BUFFER_FORMAT_MISMATCH, if the channel type of the destination buffer does not match
	//      in_kulSrcArraySize.
	//    - MV_E_INVALID_PARAMETER, if in_kulSrcArraySize < 2. 
	//    - MV_E_INVALID_PARAMETER, if in_kulSrcArraySize does not match in_kulVolumeArraySize. 
	//    - MV_E_INVALID_PARAMETER, if in_psVolumeArray = NULL and in_kulVolumeArraySize > 0. 
	// Remarks:
	//    - If in_psVolumeArray = NULL, no volumes are applied in the destination buffer.
	//    - This method consumes the auto-fades specified in the source audio samples.
	//    - Auto-fades specified in the destination buffer are ignored.
	virtual HRESULT _stdcall CopyAudioSamplesMonoToMux
		(
		IMvAudioSamples       ** in_ppISrcBufferArray,  // Pointer to the source array of mono audio
		// samples 
		const unsigned long      in_kulSrcArraySize,    // Number of mono sources contained in the 
		// specified source array.
		IMvAudioSamples        * in_pIDestBuffer,       // Pointer to the destination multi-track 
		// audio sample.
		SMvAudioMonoVolumeInfo * in_psVolumeArray,      // Pointer to an array of SmvAudioMonoVolumeInfo
		// structures containing volume settings for
		// all mono audio samples in the specified
		// source array.
		const unsigned long      in_kulVolumeArraySize, // Number of SmvAudioMonoVolumeInfo structures
		// in volume array.
		unsigned long            in_ulIgnored                  // IGNORED.
		) = 0;

	//
	// Summary:
	//    Converts 2, 4, or 8 stereo audio samples to one multi-track audio sample containing 4, 8,
	//    or 16 tracks.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_POINTER, if in_ppISrcBufferArray, or in_pIDestBuffer = NULL
	//    - MV_E_BUFFER_FORMAT_MISMATCH, if the channel type of the destination buffer does not match 
	//      in_kulSrcArraySize * 2.
	//    - MV_E_INVALID_PARAMETER, if in_kulSrcArraySize < 2.
	//    - MV_E_INVALID_PARAMETER, if kulVolumeArraySize does not match in_kulSrcArraySize * 2.
	//    - MV_E_INVALID_PARAMETER, if in_psVolumeArray = NULL while in_kulVolumeArraySize > 0.
	// Remarks:
	//    - If you need to apply volume on the sources, you must set two SmvAudioMonoVolumeInfo
	//      structures for each stereo entry.
	//    - If in_psVolumeArray = NULL, no volumes are applied in the destination audio sample.
	//    - This method consumes the auto fades specified in the source audio sample.
	//    - Auto-fades specified in the destination buffers are ignored.
	virtual HRESULT _stdcall CopyAudioSamplesStereoToMux
		(
		IMvAudioSamples       ** in_ppISrcBufferArray,  // Pointer to the source array of stereo audio 
		// samples 
		const unsigned long      in_kulSrcArraySize,    // Number of stereo sources contained in the 
		// specified source array.
		IMvAudioSamples        * in_pIDestBuffer,       // Pointer to the destination multi-track 
		// audio sample.
		SMvAudioMonoVolumeInfo * in_psVolumeArray,      // Pointer to an array of SmvAudioMonoVolumeInfo
		// structures containing volume settings for
		// all audio samples in the specified source
		// array. The first SmvAudioMonoVolumeInfo
		// structure in the array specifies a left
		// channel whereas the second entry specifies 
		// a right channel.
		const unsigned long      in_kulVolumeArraySize, // Number of SmvAudioMonoVolumeInfo structures 
		// in volume array.
		unsigned long            in_ulIgnored                  // IGNORED.
		) = 0;

	//
	// Summary:
	//    Converts one multi-track audio sample to 4, 8, or 16 mono audio samples.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_POINTER, if in_pISrcBuffer, or in_ppIDestBufferArray = NULL
	//    - MV_E_BUFFER_FORMAT_MISMATCH, if the channel type of the source audio sample does not
	//      match in_kulDestArraySize.
	//    - MV_E_UNSUPPORTED_DATA_TYPE, if the data type of the source audio sample is not PCM data.
	//    - MV_E_INVALID_PARAMETER, if the channel type of the source audio sample does not match 
	//      in_kulVolumeArraySize.
	//    - MV_E_INVALID_PARAMETER, if in_psVolumeArray = NULL or in_kulVolumeArraySize = 0.
	// Remarks:
	//    - This method will consume the auto-fades specified in the source audio sample.
	//    - Auto-fades specified in the destination audio sample are ignored.
	virtual HRESULT _stdcall CopyAudioSamplesMuxToMono
		(
		IMvAudioSamples        * in_pISrcBufferArray,   // Pointer to the source multi-track audio 
		// sample.
		IMvAudioSamples       ** in_ppIDestBuffer,      // Pointer to the destination array of mono
		// audio samples.
		unsigned long            in_kulDestArraySize,   // Number of mono audio sample destinations 
		// contained in the specified destination 
		// array.
		SMvAudioMonoVolumeInfo * in_psVolumeArray,      // Pointer to an array of SmvAudioMonoVolumeInfo
		// structures containing volume settings
		// for all mono audio samples in the
		// specified destination array.
		const unsigned long      in_kulVolumeArraySize, // Number of SmvAudioMonoVolumeInfo structures
		// in volume array.
		unsigned long            in_ulIgnored                  // IGNORED.
		) = 0;

	//
	// Summary:
	//    Converts one multi-track audio sample to 2, 4, or 8 stereo audio samples.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_POINTER, if in_ppISrcBufferArray, or in_pIDestBuffer = NULL
	//    - MV_E_BUFFER_FORMAT_MISMATCH, if the channel type of the source audio sample does not 
	//      match in_kulDestArraySize / 2.
	//    - MV_E_OUTPUT_FORMAT_NOT_SUPPORTED, if the channel type of one destination is not stereo.
	//    - MV_E_INVALID_PARAMETER, if in_kulDestArraySize does not match in_kulVolumeArraySize * 2.
	//    - MV_E_INVALID_PARAMETER, if in_psVolumeArray = NULL while in_kulVolumeArraySize > 0.
	// Remarks:
	//    - If in_psVolumeArray = NULL, no volume are applied in the destination buffer.
	//    - This method consumes the auto-fades specified in the source audio sample.
	//    - Auto-fades specified in the destination buffers are ignored.
	virtual HRESULT _stdcall CopyAudioSamplesMuxToStereo
		(
		IMvAudioSamples        * in_pISrcBufferArray,   // Pointer to the source multi-track audio
		// sample.
		IMvAudioSamples       ** in_ppIDestBuffer,      // Pointer to the destination array of stereo 
		// audio samples.
		unsigned long            in_kulDestArraySize,   // Number of stereo audio sample destinations 
		// contained in the specified destination 
		// array.
		SMvAudioMonoVolumeInfo * in_psVolumeArray,      // Pointer to an array of SmvAudioMonoVolumeInfo
		// structures containing volume settings
		// for all audio samples in the specified 
		// destination array. The first 
		// SmvAudioMonoVolumeInfo structure in the 
		// array specifies a left channel whereas
		// the second entry specifies a right
		// channel.
		const unsigned long      in_kulVolumeArraySize, // Number of SmvAudioMonoVolumeInfo structures
		// in volume array.
		unsigned long            in_ulIgnored                  // IGNORED.
		) = 0;

	//
	// Summary:
	//    Copies the content of a source surface bounded by a source rectangle to a destination 
	//       surface at the destination point.
	// Description:
	//    Copies the content of a source surface bounded by a source rectangle to a destination
	//    surface at the destination point. If the two rectangles are different, a stretch is done
	//    according to the filtering specified. Color conversion will be performed if necessary.
	//    De-interlacing or interlacing will be performed if necessary according to the polarity 
	//    of the surfaces.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if any of the parameters are invalid. This error will also be 
	//      returned if the rectangles are not within the surface size.
	//    - MV_E_LOCATION_NOT_SUPPORTED, if there's no processor or DMA available to copy from the
	//      source memory location to the destination memory location.
	//    - MV_E_STRETCH_NOT_SUPPORTED, if the copy implies a stretch that is not supported. 
	//    - MV_E_COLORCONVERSION_NOT_SUPPORTED, if the copy implies a color/format conversion that 
	//      is not supported.
	//    - MV_E_IMAGEORIGINCONVERSION_NOT_SUPPORTED, if the copy implies an unsupported conversion
	//      between two surfaces having different image origins.
	//    - MV_E_POLARITYCONVERSION_NOT_SUPPORTED, if the copy implies a de-interlace or interlace 
	//      operation that is not supported.
	//    - MV_E_MODULE_BUSY, if a previous CopySurface() method call with the same thread pool ID 
	//      is not completed yet. This limitation is for host-CPU copy only.
	//    - MV_E_NOT_READY_FOR_READ, if the source surface is not ready for a read operation. This 
	//      limitation is for host-CPU copy only.
	//    - MV_E_COPY_RECTANGLES_MISMATCH, if there's a mismatch in the rectangle parameters between 
	//       the source and destination surfaces.
	//    - MV_E_COPY_FORMATS_COMBINATION_NOT_SUPPORTED, if the source and destination surface format
	//      combination is not supported by the CopySurface() method.
	//    - MV_E_POINTER_NOT_ALIGNED, if any of the surface data pointers are not properly aligned. 
	// Remarks:
	//    - Rectangles are exclusive right/bottom. For example, if you want to copy the first 486 
	//      lines and the first 720 columns of the surface, the source rectangle must be : 
	//      (0,0)-(720,486). 
	//    - In the <i>Matrox DSX.sdk User Guide</i>, the chapter "Flex Engine Implementation" includes diagrams
	//      that summarize the video processing units and the video surface operations that can be executed 
	//      within and between the processing units.
	virtual HRESULT __stdcall CopySurface
		(
		IMvSurface  * in_pISurfaceSource,      // Address of the IMvSurface interface that is the 
		                                       // source of the copy operation.
		SMvRect     * in_prcSource,            // Address of a SMvRect structure that defines the 
		                                       // upper left and lower right points of the 
		                                       // rectangle on the source surface. If NULL, the 
		                                       // entire source is used.
		IMvSurface  * in_pISurfaceDestination, // Address of the IMvSurface interface that is the 
		                                       // destination of the copy operation.
		SMvRect     * in_prcDestination,       // Address of the SMvRect structure that defines the
		                                       // upper left and lower right points of the
		                                       // rectangle on the destination surface to copy to.
		                                       // If NULL, the entire destination is used.
		EMvFilterMode in_eFilterMode,          // Filter mode type that defines the filtering that's
		                                       // to be used if the 2 rectangles are not the same
		                                       // size.
		unsigned long in_ulPoolThreadID        // Index of the thread pool to use. This is used only
		                                       // when the copy is done by the CPU.
		) = 0; 

	//
	// Summary:
	//    Copies the content of a source surface to a destination surface that has a different
	//    resolution.
	// Description:
	//    Supported conversions are:
	//    <TABLE>
	//    Input resolution  Output resolution
	//    ----------------  -----------------
	//    NTSC              HDV or 1080
	//    PAL               HDV or 1080
	//    HDV               1080, NTSC, or PAL
	//    1080i             HDV, NTSC, or PAL
	//    </TABLE>
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_FORMAT_NOT_SUPPORTED, if the format of both surfaces is not YUYV422. 
	//    - MV_E_INVALID_POLARITY, if the polarity of both surfaces does not match. 
	//    - MV_E_UNSUPPORTED_MEMORY_LOCATION, if both surfaces are not located in host memory. 
	//    - MV_E_INCOMPATIBLE_COMPONENT_BIT_COUNT, if the component bit count of both surfaces is not
	//      8 when copying from HDV to NTSC or PAL. 
	//    - MV_E_INCOMPATIBLE_WIDTH, if the widths of the source and destination surfaces are 
	//      incompatible. 
	//    - MV_E_INCOMPATIBLE_HEIGHT, if the heights of the source and destination surfaces are 
	//      incompatible. 
	//    - MV_E_UNSUPPORTED_INPUT_WIDTH_HEIGHT, if the requested input width or height is not
	//      supported. 
	// Remarks:
	//    - The surface format for both the source and destination surfaces must be YUYV422. 
	//    - Both the source and destination surfaces must be in host memory. 
	//    - The polarity for both the source and destination surfaces must match. 
	//    - When performing an NTSC or PAL to 1080i or HDV copy, 10 bits for destination is not
	//      supported. 
	//    - When performing an HDV to NTSC or PAL copy, 10 bits for source and destination is not 
	//      supported. 
	//    - CPU processor is used for the copy. 
	//    - The functionality for pillarbox or letterbox bar color is not implemented yet. 
	//
	virtual HRESULT __stdcall CopySurfaceToNewResolution
		(
		IMvSurface   * in_pISurfaceSource,           // Address of the IMvSurface interface that is
		                                             // the source of the copy operation.
		EMvAspectRatio in_eAspectRatioSource,        // The aspect ratio value for source.
		IMvSurface   * io_pISurfaceDestination,      // Address of the IMvSurface interface that is
		                                             // the destination of the copy operation.
		EMvAspectRatio in_eAspectRatioDestination,   // The aspect ratio value for the destination.
		SMvColor     * in_rsColor                    // Address of the SMvColor structure that 
                                                   // contains the color for the pillarbox or letterbox bars.
		) = 0; 

	//
	// Summary:
	//    Copies the content of a source surface to a destination surface that has a different
	//    resolution and scan mode.
	// Description:
	//    Supported conversions:
	//    <TABLE>
	//    Input resolution  Output resolution
	//    ----------------  -----------------
	//    NTSC              HDV or 1080
	//    PAL               HDV or 1080
	//    HDV               1080, NTSC or PAL
	//    1080i             HDV, NTSC or PAL
	//    </TABLE>
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_FORMAT_NOT_SUPPORTED, if the format of both surfaces is not YUYV 4:2:2. 
	//    - MV_E_INVALID_POLARITY, if the polarity of both surfaces does not match. 
	//    - MV_E_UNSUPPORTED_MEMORY_LOCATION, if both surfaces are not located in host memory. 
	//    - MV_E_INCOMPATIBLE_COMPONENT_BIT_COUNT, if the component bit count of both surfaces is not
	//      8 when copying from HDV to NTSC or PAL. 
	//    - MV_E_INCOMPATIBLE_WIDTH, if the widths of the source and destination surfaces are 
	//      incompatible. 
	//    - MV_E_INCOMPATIBLE_HEIGHT, if the heights of the source and destination surfaces are 
	//      incompatible. 
	//    - MV_E_UNSUPPORTED_INPUT_WIDTH_HEIGHT, if the requested input width or height is not
	//      supported. 
	//    - MV_E_MODULE_BUSY, if a previous CopySurfaceToNewResolutionEx() method call with the same thread pool ID 
	//      is not completed yet. This limitation applies only if the Flex Engine is created using the 
	//      IMvFlexEngineCreator::CreateEngine method.
	// Remarks:
	//    - The surface format for both the source and destination surfaces must be YUYV 4:2:2. 
	//    - Both the source and destination surfaces must be in host memory. 
	//    - The polarity for both the source and destination surfaces must match. 
	//    - When performing a copy from NTSC or PAL to 1080i or HDV, 10 bits for the destination is not
	//      supported. 
	//    - When performing a copy from HDV to NTSC or PAL, 10 bits for the source and the destination are not 
	//      supported. 
	//    - CPU processor is used for the copy. 
	//    - The functionality for pillarbox or letterbox bar color is not implemented yet. 
	//
	virtual HRESULT __stdcall CopySurfaceToNewResolutionEx
		(
		IMvSurface   * in_pISurfaceSource,           // Address of the IMvSurface interface that is
		// the source of the copy operation.
		EMvAspectRatio in_eAspectRatioSource,        // The aspect ratio value for the source.
		IMvSurface   * io_pISurfaceDestination,      // Address of the IMvSurface interface that is
		// the destination of the copy operation.
		EMvAspectRatio in_eAspectRatioDestination,   // The aspect ratio value for the destination.
		SMvColor     * in_rsColor,                   // Address of the SMvColor structure that 
		// contains the color for the pillar.
		unsigned long  in_ulThreadPoolIndex          // Index of the thread pool to use. This is used 
		// only with a synchronous Flex Engine.
		) = 0; 

	//
	// Summary:
	//    De-interlaces and resizes the content of a source surface to be sent to a destination surface. 
	// Description:
	//    Only supported on X.mio2/S and MXO2 hardware. Supported conversions:
	//    <TABLE>
	//    Input resolution  Output resolution
	//    ----------------  -----------------
	//    NTSC              720p or 1080i
	//    PAL               720p or 1080i
	//    720p              1080i, NTSC, or PAL
	//    1080i             720p, NTSC, or PAL
	//    </TABLE>
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_FORMAT_NOT_SUPPORTED, if the format of both surfaces is not YUYV 4:2:2. 
	//    - MV_E_INVALID_POLARITY, if the polarity of both surfaces does not match. 
	//    - MV_E_UNSUPPORTED_MEMORY_LOCATION, if both surfaces are not in I/O memory. 
	//    - MV_E_INCOMPATIBLE_WIDTH, if the widths of the source and destination surfaces are 
	//      incompatible. 
	//    - MV_E_INCOMPATIBLE_HEIGHT, if the heights of the source and destination surfaces are 
	//      incompatible. 
	//    - MV_E_UNSUPPORTED_INPUT_WIDTH_HEIGHT, if the requested input width or height is not
	//      supported. 
	// Remarks:
	//    - The surface format for both the source and destination surfaces must be YUYV 4:2:2. 
	//    - Both the source and destination surfaces must be in I/O memory. 
	//    - The polarity of the source surface must be keMvPolarityInterlacedFieldsInAFrame, and the polarity of the 
	//       destination surface must be keMvPolarityFirstField, keMvPolaritySecondField, or keMvPolarityProgressiveFrame. 
	//    - The processor on the hardware is used for this operation. 
	//
	virtual HRESULT __stdcall DeInterlaceCrossConvertSurfaces
		(
		IMvSurface   * in_pISurfaceSource,          // Address of the IMvSurface interface that is
		// the source of the de-interlace and scale operation.
		SMvRect     * in_prcSource,                 // Address of a SMvRect structure that defines the 
		// upper left and lower right points of the 
		// rectangle on the source surface. If NULL, the 
		// entire source is used.
		EMvScanMode    in_eFieldDominaceSource,      // The scan mode value for the source.
		IMvSurface   * io_pISurfaceDestination,      // Address of the IMvSurface interface that is
		// the destination of the operation.
		SMvRect     * in_prcDestination,       // Address of the SMvRect structure that defines the
		// upper left and lower right points of the
		// rectangle on the destination surface.
		// If NULL, the entire destination is used.
		EMvScanMode    in_eFieldDominaceDestination, // The scan mode value for the destination.
		EMvPolarity    in_eProcessingPolarity,       // The field polarity value to consider in the processing.
		SMvBarColor  * in_rsBarColor,                // Address of the SMvBarColor structure that 
		// contains the color for the pillarbox or letterbox bars.
		unsigned long  in_ulThreadPoolIndex          // Index of the thread pool to use. This is used 
		// only with a synchronous Flex Engine.
		) = 0; 

   //
   // Summary:
   //    Resizes the content of a source surface to be sent to a destination surface. 
   // Description:
   //    - Only supported on X.mio2/D hardware.
   //    - The following table shows the configuration to get the best possible results:
   //    <TABLE>
   //    Input resolution  Output resolution  Filter Configuration(in_eFilterConfig)  Scaler Configuration(in_eScalerConfig)
   //    ----------------  -----------------  --------------------------------------  --------------------------------------
   //    486p              NTSC               keMvScalerFilterConfigVAfterWSharpness  keMvScalerConfigProcessPOut
   //    486p              720p               keMvScalerFilterConfigVBefore           keMvScalerConfigNormal
   //    486p              1080i              keMvScalerFilterConfigVBefore           keMvScalerConfigProcessPOut
   //    486p              1080p              keMvScalerFilterConfigVBefore           keMvScalerConfigNormal
   //
   //    576p              PAL                keMvScalerFilterConfigVAfterWSharpness  keMvScalerConfigProcessPOut
   //    576p              720p               keMvScalerFilterConfigVBefore           keMvScalerConfigNormal
   //    576p              1080i              keMvScalerFilterConfigVBefore           keMvScalerConfigProcessPOut
   //    576p              1080p              keMvScalerFilterConfigVBefore           keMvScalerConfigNormal
   //
   //    720p              486p               keMvScalerFilterConfigVBefore           keMvScalerConfigNormal
   //    720p              576p               keMvScalerFilterConfigVBefore           keMvScalerConfigNormal
   //    720p              1080i              keMvScalerFilterConfigVBefore           keMvScalerConfigProcessPOut
   //    720p              1080p              keMvScalerFilterConfigVBefore           keMvScalerConfigNormal
   //
   //    1080p             486p               keMvScalerFilterConfigVBefore           keMvScalerConfigNormal
   //    1080p             576p               keMvScalerFilterConfigVBefore           keMvScalerConfigNormal
   //    1080p             720p               keMvScalerFilterConfigVBefore           keMvScalerConfigNormal
   //    1080p             1080i              keMvScalerFilterConfigVBefore           keMvScalerConfigProcessPOut
   //    </TABLE>
   //
   //    - If the input resolution is interlaced, you must call IMvFlexEngine::DeInterlaceSurfaces 
   //      to convert it to a progressive resolution.
   //    - You may need to call CrossConvertSurfaces twice in some cases to get the proper conversion:
   //    <TABLE>
   //    Desired conversion  CrossConvertSurfaces Step 1   CrossConvertSurfaces Step 2
   //    ------------------  ---------------------------   ---------------------------
   //    720p to NTSC        720p to 486p                  486p to NTSC
   //    720p to PAL         720p to 576p                  576p to PAL
   //    1080p to NTSC       1080p to 486p                 486p to NTSC
   //    1080p to PAL        1080p to 576p                 576p to PAL
   //    <TABLE>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_FORMAT_NOT_SUPPORTED, if the format of both surfaces is not YUYV 4:2:2. 
   //    - MV_E_INVALID_POLARITY, if the polarity of both surfaces does not match. 
   //    - MV_E_UNSUPPORTED_MEMORY_LOCATION, if both surfaces are not in I/O memory. 
   //    - MV_E_INCOMPATIBLE_WIDTH, if the widths of the source and destination surfaces are 
   //      incompatible. 
   //    - MV_E_INCOMPATIBLE_HEIGHT, if the heights of the source and destination surfaces are 
   //      incompatible. 
   //    - MV_E_UNSUPPORTED_INPUT_WIDTH_HEIGHT, if the requested input width or height is not
   //      supported. 
   // Remarks:
   //    - The surface format for both the source and destination surfaces must be YUYV 4:2:2. 
   //    - Both the source and destination surfaces must be in I/O memory. 
   //    - The processor on the hardware is used for this operation. 
   //
   virtual HRESULT __stdcall CrossConvertSurfaces
      (
      IMvSurface           *  in_pISurfaceSource,           // Address of the IMvSurface interface that is
                                                               // the source of the scale operation.
      SMvRect              *  in_prcSource,                 // Address of the SMvRect structure that defines the 
                                                               // upper left and lower right points of the 
                                                               // rectangle on the source surface. If NULL, the 
                                                               // entire source is used.
      IMvSurface           *  io_pISurfaceDestination,      // Address of the IMvSurface interface that is
                                                               // the destination of the operation.
      SMvRect              *  in_prcDestination,            // Address of the SMvRect structure that defines the
                                                               // upper left and lower right points of the
                                                               // rectangle on the destination surface.
                                                               // If NULL, the entire destination is used.
      SMvBarColor          *  in_rsBarColor,                // Address of the SMvBarColor structure that 
                                                               // contains the color for the pillarbox or letterbox bars.
      EMvScalerFilterConfig   in_eFilterConfig,             // Selects the vertical anti-aliasing filter configuration for the scaler.
                                                               // Refer to the description section to select the proper value.
      EMvScalerConfig         in_eScalerConfig,             // Selects the scaler configuration.
                                                               // Refer to the description section to select the proper value.
      unsigned long           in_ulFilterSharpnessControl,  // If in_eFilterConfig is set to "keMvScalerFilterConfigVAfterWSharpness",
                                                               // this parameter selects the sharpness of the vertical filter.
                                                               // This parameter should be user selectable.
                                                               // The range for this parameter is 1 (no filtering) to 10 (maximum filtering). 
      unsigned long           in_ulThreadPoolIndex          // Index of the thread pool to use. This is used 
      // only with a synchronous Flex Engine.
      ) = 0; 

   //
   // Summary:
   //    De-interlaces a source surface (field) to be sent to a destination surface (frame). 
   // Description:
   //    Only supported on X.mio2/D hardware. Supported conversions:
   //    <TABLE>
   //    Input resolution  Output resolution
   //    ----------------  -----------------
   //    NTSC              486p
   //    PAL               576p
   //    1080i             1080p
   //    </TABLE>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if pointer parameters are NULL.
   //    - MV_E_DEVICE_NOT_PRESENT, if no scaler is present on the hardware profile controlled.
   //    - MV_E_FAIL, if the parameter surfaces are invalid.
   //    - MV_E_INVALID_POLARITY, if the polarity of both input surfaces is not keMvPolarityInterlacedFieldsInAFrame. 
   //    - MV_E_OUT_OF_MEMORY, if the context is invalid.
   // Remarks:
   //    - The surface format for the source and destination surfaces must be YUYV 4:2:2. 
   //    - The source and destination surfaces must be in the I/O memory. 
   //    - The polarity for the source surface must be keMvPolarityInterlacedFieldsInAFrame, and the polarity of the 
   //      destination surface must be be keMvPolarityProgressiveFrame. 
   //    - The processor on the hardware is used for this operation.
   //    - The processing polarity must be keMvPolarityFirstField or keMvPolaritySecondField.
   //    - The neighbour source surface must be the surface before the current one if the 
   //      processing polarity is first field.
   //    - The neighbour source surface must be the surface after the current one if the 
   //      processing polarity is second field.
   //    - The neighbour source surface must be (NULL) if the current field
   //      is first or last in a stream.
   //

   virtual HRESULT __stdcall DeInterlaceSurfaces(  
      IMvSurface        *  in_pISurfaceSourceCurrent,    // Address of the IMvSurface interface that is
                                                         // the source of the de-interlace operation.         
      IMvSurface        *  in_pISurfaceSourceNeighbour,  // Address of the IMvSurface interface that is
                                                         // the neighbour of the source of the de-interlace operation. 
                                                         // The neighbour is the previous surface compared to the current when
                                                         // the processing polarity is first field, and it is the next surface 
                                                         // when the processing polarity is second field. Must be NULL when
                                                         // processing the first or last field in a stream as defined by "in_eDeInterlaceCase"
      EMvScanMode          in_eFieldDominaceSource,      // The scan mode value for the source.
      IMvSurface        *  in_pISurfaceDestination,      // Address of the IMvSurface interface that is
                                                         // the destination of the operation.
      EMvPolarity          in_eProcessingPolarity,       // The field polarity value to consider in the processing.
      IUnknown          *  in_pIDIContext,               // Address of the IUnknown interface of the de-interlacer context.
      EMvDeInterlaceCase   in_eDeInterlaceCase,          // The position of the current field in the stream (first, last, or in between).
      unsigned long        in_ulThreadPoolIndex          // Index of the thread pool to use. This is used 
                                                         // only with a synchronous Flex Engine.
      ) = 0;

   //
   // Summary:
   //    Allocates context in onboard memory for de-interlacing a buffer using DeInterlaceSurfaces().
   // Description:
   //    Only supported on X.mio2/D hardware. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_PARAMETER, if out_ppIDeInterlacerContext is NULL.
   //    - MV_E_OUT_OF_MEMORY, if the onboard memory allocation failed.
   //    - MV_E_DEVICE_NOT_PRESENT, if the onboard memory manager driver is not present.
   //    - MV_E_NOT_SUPPORTED, if the call is performed on unsupported hardware.
   // Remarks:
   //    - The context object is provided with a reference count of 1. You must release the 
   //      interface once you are done with it.
   //
   virtual HRESULT __stdcall CreateDeInterlacerContext
      (
      IUnknown ** out_ppIDeInterlacerContext  // Address of the IUnknown interface of the de-interlacer context.
      ) = 0; 


   //
	// Summary:
	//    Combines video and key surfaces.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if any of the parameters are invalid. This error is also 
	//      returned if the rectangles are not within the surface size.
	//    - MV_E_LOCATION_NOT_SUPPORTED, if there's no processor or DMA available to copy from the
	//      source memory location to the destination memory location.
	//    - MV_E_COLORCONVERSION_NOT_SUPPORTED, if the copy implies a color/format conversion that is
	//      not supported. 
	//    - MV_E_IMAGEORIGINCONVERSION_NOT_SUPPORTED, if the copy implies an unsupported conversion
	//      between two surfaces having different image origins.
	//    - MV_E_POLARITYCONVERSION_NOT_SUPPORTED, if the copy implies a de-interlace or interlace 
	//      operation that is not supported.
	//    - MV_E_MODULE_BUSY, if a previous CombineVideoAndKeySurfaces() method call with the same 
	//      thread pool ID is not completed yet. This limitation is for host-CPU copy only.
	//    - MV_E_NOT_READY_FOR_READ, if the source surface is not ready for a read operation. This
	//      limitation is for host-CPU copy only.
	//    - MV_E_COPY_FORMATS_COMBINATION_NOT_SUPPORTED, if the source and destination surface format
	//      combination is not supported by the CombineVideoAndKeySurfaces() method. 
	//    - MV_E_POINTER_NOT_ALIGNED, if any of the surface data pointers are not properly aligned. 
	virtual HRESULT __stdcall CombineVideoAndKeySurfaces
		(
		IMvSurface     *in_pIVideoSurfaceSource,  // Address of the IMvSurface interface that is the
		                                          // video source of the combine operation.
		IMvSurface     *in_pIKeySurfaceSource,    // Address of the IMvSurface interface that is the
		                                          // key source of the combine operation.
		IMvSurface     *io_pISurfaceDestination,  // Address of the IMvSurface interface that is the 
		                                          // destination of the combine operation.
		unsigned long  in_ulThreadPoolIndex       // Index of the thread pool to use. This is used 
		                                          // only when the copy is done by the CPU.
		) = 0;

	//
	// Summary:
	//    Extracts video and key surfaces. 
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if any of the parameters are invalid. This error will also be
	//      returned if the rectangles are not within the surface size.
	//    - MV_E_LOCATION_NOT_SUPPORTED, if there's no processor or DMA available to copy from the
	//      source memory location to the destination memory location.
	//    - MV_E_COLORCONVERSION_NOT_SUPPORTED, if the copy implies a color/format conversion that
	//      is not supported. 
	//    - MV_E_IMAGEORIGINCONVERSION_NOT_SUPPORTED, if the copy implies an unsupported conversion 
	//      between two surfaces that have a different image origin.
	//    - MV_E_POLARITYCONVERSION_NOT_SUPPORTED, if the copy implies a de-interlace or interlace
	//      operation that is not supported.
	//    - MV_E_MODULE_BUSY, if a previous ExtractVideoAndKeySurfaces() method call with the same
	//      thread pool ID is not completed yet. This limitation is for host-CPU copy only.
	//    - MV_E_NOT_READY_FOR_READ, if the source surface is not ready for a read operation. This 
	//      limitation is for host-CPU copy only.
	//    - MV_E_COPY_FORMATS_COMBINATION_NOT_SUPPORTED, if the source and destination surface format
	//      combination is not supported by the ExtractVideoAndKeySurfaces() method. 
	//    - MV_E_POINTER_NOT_ALIGNED, if any of the surface data pointers are not properly aligned. 
	virtual HRESULT __stdcall ExtractVideoAndKeySurfaces
		(
		IMvSurface     *in_pISurfaceSource,             // Address of the IMvSurface interface that is
		                                                // the source of the extract operation.
		IMvSurface     *io_pIVideoSurfaceDestination,   // Address of the IMvSurface interface that is
		                                                // the video destination of the extract
		                                                // operation.
		IMvSurface     *io_pIKeySurfaceDestination,     // Address of the IMvSurface interface that
		                                                // is the key destination of the extract
		                                                // operation.
		unsigned long  in_ulThreadPoolIndex             // Index of the thread pool to use. This is 
		                                                // used only when the copy is done by the CPU.
		) = 0;

	//
	// Summary:
	//    Creates a codec enumerated with the IMvCodecEnumerator interface.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if the codec can't be created.
	virtual HRESULT __stdcall CreateCodec
		(
		GUID      * in_pCodecGUID, // Pointer to the GUID of the codec to create.
		IMvCodec ** out_ppICodec   // Pointer that receives the created IMvCodec pointer.
		) = 0; 


	//
	// Summary:
	//    Creates a codec enumerated with the IMvVideoCodecEnumerator or
	//    IMvAudioCodecEnumerator interfaces.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if the codec can't be created.
	// Comment:
	//      
	virtual HRESULT __stdcall CreateCodecEx
		(
		GUID      * in_pCodecGUID, // Pointer to the GUID of the codec to create.
		IUnknown** out_ppICodecUnknown   // Pointer that receives the created IMvCodec pointer.
		) = 0; 



	//
	// Summary:
	//    Creates a Flex effect enumerated with the IMvEffectEnumerator interface.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if the effect can't be created.
	// Remarks:
	//    - This method can be called more than once with the same effect GUID to create multiple
	//      instances of the same effect. 
	virtual HRESULT __stdcall CreateEffect
		(
		GUID      *  in_pEffectGUID,  // Pointer to the GUID of the effect to create.
		IMvEffect ** out_ppIEffect,   // Pointer that receives the created IMvEffect pointer.
      const SMvResolutionInfo * in_psResInfo = NULL // Pointer to the resolution to be used by the effect. If NULL, it uses the resolution of the FlexEngine.
		) = 0;

	//
	// Summary:
	//    Instantiates a Flex File Writer object and returns the IMvFlexWriter interface.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_POINTER, if the Flex Engine pointer sent by the factory is NULL.
	//    - MV_E_OUT_OF_MEMORY, if a memory allocation failed.
	virtual HRESULT __stdcall CreateFlexWriter
		(
		IMvFlexWriter ** out_ppIFlexWriter  // IMvFlexWriter interface pointer.
		) = 0;

	//
	// Summary:
	//    Instantiates a Flex File Reader object and returns the IMvFlexReader interface.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_POINTER, the input pointer is NULL.
	//    - MV_E_FLEXREADER_CREATION_FAILED.
	//    - MV_E_OUT_OF_MEMORY.
	// Remarks:
	//    - An AddRef call is done on the interface. The Flex Engine does not keep a copy of the
	//      interface.
	//    - Multiple calls to this function can be made to instantiate multiple Flex File Reader objects. 
	//      The number of Flex File Reader objects that can be instantiated is not explicitly limited.
	virtual HRESULT __stdcall CreateFlexReader
		(
		IMvFlexReader ** out_ppIFlexReader  // IMvFlexReader interface pointer.
		) = 0;

	//
	// Summary:
	//    Allocates an audio sample buffer based on the specified audio sample description and returns
	//    the IMvAudioSamples interface.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if in_psDescription or out_ppIAudioSamplesare NULL. 
	//    - MV_E_UNSUPPORTED, if the requested audio samples description is not supported and cannot
	//      be allocated.
	//    - MV_E_OUT_OF_MEMORY, if no more memory is available.
	virtual HRESULT __stdcall CreateAudioSamples
		(
		SMvCreateAudioSamplesDescription * in_psDescription,     // Pointer to the description of the
		                                                         // audio samples to allocate. 
		IMvAudioSamples                 ** out_ppIAudioSamples   // Pointer that receives the 
		                                                         // allocated IMvAudioSamples
		                                                         // interface pointer.
		) = 0;

	//
	// Summary:
	//    Allocates an audio sample alias and returns the IMvAudioSamples interface.
	// Description:
	//    An audio samples alias does not allocate memory but
	//    has its own synchronization object. An audio sample alias is used to reference the data of
	//    another audio sample buffer. This reference can be assigned with the AssignAliasReference()
	//    method of the IMvAudioSamples interface.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if the out_ppIAudioSamples is NULL.
	virtual HRESULT __stdcall CreateAudioSamplesAlias
		(
		IMvAudioSamples ** out_ppIAudioSamples // Pointer that receives the allocated IMvAudioSamples interface pointer.
		) = 0;

	//
	// Summary:
	//    Creates an audio sample that will be used to encapsulate a previously allocated host-memory buffer.
	// Description:
	//    The user buffer reference can be assigned with the AssignUserBufferReference() method of the
	//    IMvAudioSamples interface.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if out_ppIMvAudioSamples is NULL. 
	virtual HRESULT __stdcall CreateAudioSamplesForUserBuffer
		(
		IMvAudioSamples ** out_ppIAudioSamples // Pointer that receives the allocated IMvAudioSamples interface pointer.
		) = 0;

	//
	// Summary:
	//    Allocates a surface based on the specified surface description and returns the IMvSurface
	//    interface.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if in_psDescription or out_ppISurfaceare are NULL. 
	//    - MV_E_UNSUPPORTED, if the requested surface description is not supported and can't be 
	//      allocated.
	//    - MV_E_OUT_OF_MEMORY, if no more memory is available.
	//
	virtual HRESULT __stdcall CreateSurface
		(
		SMvCreateSurfaceDescription * in_psDescription, // Pointer to the description of the surface to allocate. 
		IMvSurface                 ** out_ppISurface    // Pointer that receives the allocated IMvSurface interface pointer.
		) = 0; 

	//
	// Summary:
	//    Allocates a Flex surface based on the specified surface description and resolution scan
	//    mode and returns the IMvSurface interface.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_PARAMETER, if in_psDescription or out_ppISurface are NULL. 
	//    - MV_E_UNSUPPORTED, if the requested surface description is not supported and can't be
	//      allocated. 
	//    - MV_E_OUT_OF_MEMORY, if no more memory is available. 
	virtual HRESULT __stdcall CreateSurfaceEx
		(
		SMvCreateSurfaceDescription *in_psDescription,        // Pointer to the description of the surface to allocate.
		EMvScanMode                  in_eResolutionScanMode,  // Scan mode of the resolution in which the surface is to 
                                                            // be used. Internally, this scan mode is used to determine 
                                                            // the bIsSurfaceOfTopLine parameter of SMvSurfaceDescription.
		IMvSurface                 **out_ppISurface           // Pointer that receives the allocated IMvSurface interface 
                                                            // pointer.
		) = 0;      

	//
	// Summary:
	//    Allocates a surface based on the specified surface description, size of the memory buffer (in bytes), and resolution scan
	//    mode, and returns the IMvSurface interface.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_PARAMETER, if in_psDescription or out_ppISurface is NULL. 
	//    - MV_E_UNSUPPORTED, if the requested surface description is not supported and can't be
	//      allocated. 
	//    - MV_E_OUT_OF_MEMORY, if no more memory is available. 
	//    - MV_E_BUFFER_SIZE_MISMATCH, if the supplied size cannot hold the description passed.
	virtual HRESULT __stdcall CreateFixedSizeSurface
		(
		SMvCreateSurfaceDescription *in_psDescription,        // Pointer to the description of the surface to allocate. 
		unsigned long                ulBufferSizeInBytes,     // Indicates in bytes the size of the memory buffer.
		EMvScanMode                  in_eResolutionScanMode,  // Scan mode of the resolution in which the surface is
		                                                      // intended to be used. Internally, this scan mode is used
		                                                      // to determine the bIsSurfaceOfTopLine parameter of 
                                                            // SMvSurfaceDescription.
		IMvSurface                 **out_ppISurface           // Pointer that receives the allocated IMvSurface interface 
                                                            // pointer.
		) = 0;      

	//
	// Summary:
	//    Allocates a surface alias and return the IMvSurface interface.
	// Description:
	//    A surface alias doesn't allocate memory, but it has its own synchronization object. It's
	//    used to reference the data of another surface. This reference can be assigned with the 
	//    method AssignAliasReference() method of the IMvSurface interface.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if the out_ppISurface is NULL.
	virtual HRESULT __stdcall CreateSurfaceAlias
		(
		IMvSurface ** out_ppISurface  // Pointer that receives the allocated IMvSurface interface pointer.
		) = 0;

	//
	// Summary:
	//    Creates a surface container that can be used to encapsulate a list of surfaces.
	// Description:
	//    An IMvContainer object is used to pass multiple surfaces to modules, such as the CODEC
	//    module (in MPEG-IBP) and the GFX File Manager.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if out_ppIContainer is NULL. 
	virtual HRESULT __stdcall CreateSurfaceContainer
		(
		IMvContainer ** out_ppIContainer // Pointer that receives the allocated IMvContainer interface pointer.
		) = 0;

	//
	// Summary:
	//    Creates a surface that can be used to encapsulate a previously allocated host-memory buffer.
	// Description:
	//    The user buffer reference can be assigned with the AssignUserBufferReference() method
	//    of the IMvSurface interface.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if out_ppIMvSurface is NULL. 
	virtual HRESULT __stdcall CreateSurfaceForUserBuffer
		( 
		IMvSurface ** out_ppISurface  // Pointer that receives the allocated IMvSurface interface pointer.
		) = 0;

	//
	// Summary:
	//    Creates a surface that can be used to encapsulate a previously allocated host-memory buffer.
	// Description:
	//    The caller can specify the scan mode in which the surface is to be used. The
	//    user buffer reference can be assigned with the AssignUserBufferReference() method of the 
	//    IMvSurface interface.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_PARAMETER, if out_ppIMvSurface is NULL or in_eResolutionScanMode is invalid. 
	virtual HRESULT __stdcall CreateSurfaceForUserBufferEx
		( 
		EMvScanMode   in_eResolutionScanMode,  // Scan mode of the resolution in which the surface is to be used. 
                                             // Internally, this scan mode is used to determine the bIsSurfaceOfTopLine
                                             // parameter of SMvSurfaceDescription.
		IMvSurface ** out_ppISurface           // Pointer that receives the allocated IMvSurface interface pointer.
		) = 0;

	//
	// Summary:
	//    Creates an A/V Content Pool Manager.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_POINTER, if the pointer is NULL
	//    - MV_E_OUT_OF_MEMORY, if the creation failed. 
	virtual HRESULT __stdcall CreateAVContentPoolManager
		(
		unsigned long in_ulThreadPoolPriority, // Priority of the waiting thread inside the pool  manager that is used to
		                                       // do the clean up.

		IMvAVContentCompletionObserver * in_pIAVContentCompletionObserver, // Pointer to an object that
		                        // will be registered as an error observer and called when an error has occurred on an
		                        // AVContent.  This parameter can be NULL if there is no need to be notified about error.
		                        // The observer MUST NOT be the same object as the owner, because it creates a circular
		                        // dependency in COM, and results in memory leaks because some reference count will
		                        // never reach 0.  

		const wchar_t in_wszPoolName[],  // String that contains the user-friendly name of the pool.  This  is used when
		                                 // logging is enabled to help differentiate the many  pools that can be running
		                                 // at the same time. (for example, L"InputSurfacePool").

		IMvAVContentPoolManager ** out_ppIAVContentPoolManager // Pointer that will receive an A/V Content Pool
		                                                       // Manager object.
		) = 0;

	//
	// Summary:
	//    Copies the audio data of an audio sample buffer to another audio sample buffer with the option of having an 
   //    offset in the source and destination sample buffers.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if one or some parameters are invalid.
	// Remarks:
	//    - The destination audio sample buffer must have the same format as the source audio sample buffer in order
   //      for this method to work.
	//    - This method does not convert between different audio formats. To convert between different audio formats,
   //      use the CopyAudioSamples() method.
	//    - The DuplicateAudioSamples method's implementation will perform an IMvAudioSamples::SetLength on the 
   //      in_pIAudioSamplesDestination buffer once its asynchronous processing is completed. You will need to take 
   //      special precautions if you pass the same target audio samples buffer to more than one DuplicateAudioSamples
   //      call. The audio samples target buffer size will be temporarily adjusted after each DuplicateAudioSamples 
   //      method's asynchronous processing is completed and set to be equal to the size of the audio samples target 
   //      buffer, including the specified offset, from the previously completed DuplicateAudioSamples call. To avoid 
   //      the implications of this behavior on any subsequent asynchronous processing you should first call 
	//      DuplicateAudioSamples to perform all required duplications for a given audio samples buffer target, and 
   //      then assign an alias on the target audio samples buffer and perform a SetLength call on the alias. The 
   //      length of the alias audio samples buffer won't be modified by the DuplicateAudioSamples call, therefore 
   //      the length can be set to reflect the total number of samples that need to be duplicated.

	virtual HRESULT _stdcall DuplicateAudioSamples
		(
		IMvAudioSamples * in_pISrcBuffer,         // Pointer to the source audio sample buffer interface.
		unsigned long     in_ulSrcOffset,         // Offset in bytes of the source audio sample buffer to copy.
		IMvAudioSamples * in_pIDestBuffer,        // Pointer to the destination audio samples interface.
		unsigned long     in_ulDestOffset,        // Offset in bytes of the destination audio sample buffer to copy to.
		unsigned long     in_ulSizeToDuplicate,   // Size of the buffer to copy.
		unsigned long     in_ulThreadPoolIndex    // Index of the thread pool to use.
		) = 0;

	//
	// Summary:
	//    Retrieves the audio mixer component interface that provides audio mixing services.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_DEVICE_NOT_PRESENT, if there's no audio mixer present on the hardware profile controlled
	//      by the Flex Engine.
	// Remarks:
	//    - Calling this method increases the internal reference count on the IMvAudioMixer interface.
	virtual HRESULT __stdcall GetAudioMixerInterface
		(
		IMvAudioMixer **out_ppIAudioMixer   // Pointer that will be initialized with the IMvAudioMixer interface pointer.
		) = 0;

	//
	// Summary:
	//    Gets the amount of memory, in bytes, that is required to allocate the specified audio samples surface.
	// Description:
	//    This method does not allocate memory for the surface. It is for information purposes only.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if any of the pointer addresses are NULL. 
	//    - MV_E_INVALID_STRUCTURE_SIZE, if the size field of the SMvCreateAudioSamplesDescription 
	//      parameter or the SMvResolutionInfo parameter is not initialized properly. 
	//    - MV_E_UNSUPPORTED_FRAMERATE, if the computation cannot be done using the resolution frame rate. 
	//    - MV_E_UNSUPPORTED_SCANMODE, if the computation cannot be done using the resolution scan mode. 
	virtual HRESULT __stdcall GetAudioSamplesMemoryFootprint
		(
		const SMvCreateAudioSamplesDescription * in_psDescription,  // Pointer to the description of the audio samples surface. 
                                                            // The memory size computations are based, in part, on the 
                                                            // audio samples surface description.
		const SMvResolutionInfo * in_psResolutionInfo,        // Pointer to the resolution in which the audio samples will 
                                                            // be used. The memory size computations are based, in 
                                                            // part, on the audio samples surface description.
		unsigned long     * out_pulMemorySizeInBytesTypeA,    // Pointer that will be filled with the memory size, in bytes.
															               // If the audio samples dimension is not an integer value 
                                                            // (any M factor resolution, such as 23.98, 29.97, or 59.94 fps),  
                                                            // this parameter represents the biggest value that can be allocated.
		unsigned long     * out_pulMemorySizeInBytesTypeB     // If the audio samples dimension is not an integer value
                                                            // (any M factor resolution, such as 23.98, 29.97, or 59.94 fps), 
                                                            // this parameter represents the smallest value that can be allocated. Otherwise, 0 is allocated.
		) = 0;

	//
	// Summary:
	//    Retrieves the system clock interface that is used to time stamp audio samples and video  surfaces for buffer synchronization.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_DEVICE_NOT_PRESENT, if there's no clock present on the hardware profile controlled 
	//      by the Flex Engine.
	// Remarks:
	//    - Calling this method increases the internal reference count on the IMvClock interface.
	virtual HRESULT __stdcall GetClockInterface
		(
		IMvClock ** out_ppIClock   // Pointer that will be initialized with the IMvClock interface pointer.
		) = 0;

	//
	// Summary:
	//    Retrieves the video compositor component interface that is required to perform multiple video layer compositing.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_DEVICE_NOT_PRESENT, if there's no compositor present on the hardware profile 
	//      controlled by the Flex Engine. 
	// Remarks:
	//    - Calling this method increases the internal reference count on the IMvCompositor interface. 
	virtual HRESULT __stdcall GetCompositorInterface
		(
		IMvCompositor ** out_ppICompositor  // Pointer that will be initialized with the IMvCompositor interface pointer.
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvDVAudio interface that processes deshuffling/muxing of audio from a DV frame.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_DEVICE_NOT_PRESENT, if there's no DVAudio module present on the hardware profile
	//      controlled by the Flex Engine.
	// Remarks:
	//    - Calling this method increases the internal reference count on the IMvDVAudio interface.
	virtual HRESULT __stdcall GetDVAudioInterface
		(
		IMvDVAudio ** out_ppIDVAudio  // Pointer that will be initialized with the IMvDVAudio interface pointer.
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvFrameProperties interface that is used to insert information onto
	//    or retrieve information from DV compressed frames. 
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_DEVICE_NOT_PRESENT, if no DV modules are present.
	//    - MV_E_INVALID_PARAMETER, if the input parameter is NULL.
	// Remarks:
	//    - Calling this method increases the internal reference count on the IMvFrameProperties interface.
	virtual HRESULT __stdcall GetFramePropertiesInterface
		(
		IMvFrameProperties ** out_ppIFrameProperties // Pointer that will be initialized with the IMvFrameProperties 
                                                   // interface pointer.
		) = 0;

	//
	// Summary:
	//    Gets information about the current resolution and the hardware profile controlled by 
	//    the Flex Engine.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_STRUCTURE_SIZE, if the field size of the structure does not contain the 
	//      right value. 
	// Remarks:
	//    - The field size of the structure must be filled before calling the method.
	virtual HRESULT __stdcall GetEngineProfileInfo
		(
		SMvEngineProfileInfo * io_psEngineProfileInfo   // Pointer to SMvEngineProfileInfo structure that will be filled 
                                                      // with the Flex Engine's profile information.  
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvFlex3DDevice interface of the Flex 3D device.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_DEVICE_NOT_PRESENT, if there's no Flex 3D device present on the hardware profile 
	//      controlled by the Flex Engine.
	// Remarks:
	//    - Calling this method increases the internal reference count on the IMvFlex3DDevice interface.
	virtual HRESULT __stdcall GetFlex3DDeviceInterface
		(
		IMvFlex3DDevice ** out_ppIFlex3DDevice // Pointer that will be initialized with the IMvFlex3DDevice interface 
                                             // pointer.
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvHardwareInformation interface that provides information about the system hardware. 
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_DEVICE_NOT_PRESENT, if there's no hardware information device present on the hardware
	//      profile controlled by the Flex Engine.
	// Remarks:
	//    - Can be used by the developer to monitor system hardware events and to display system hardware information
   //      in the user application.
	//    - Calling this method increases the internal reference count on the IMvHardwareInformation interface.   
	virtual HRESULT __stdcall GetHardwareInformationInterface
		(
		IMvHardwareInformation ** out_ppIHardwareInformation  // Pointer that will be initialized with the 
                                                            // IMvHardwareInformation interface pointer.
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvInputOutputIndependent interface that controls the
	//    input and output channels of buffer-based hardware that has I/O capabilities.
	// Return value:
	//    - MV_NOERROR if completed successfully.
	//    - MV_E_DEVICE_NOT_PRESENT, if there's no input/output device present on the hardware profile
	//      controlled by the Flex Engine.
	// Remarks:
	//    - Calling this method increases the internal reference count for the 
	//      IMvInputOutputIndependent interface.
	virtual HRESULT __stdcall GetInputOutputIndependentInterface
		(
		IMvInputOutputIndependent** out_ppIInputOutputIndependent   // Pointer that receives the 
                                                                  // IMvInputOutputIndependent interface.
	 	) = 0;

	//
	// Summary:
	//    Retrieves the interface that controls the input and output channels of the legacy X.io card.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_DEVICE_NOT_PRESENT, if there's no input/output device present on the hardware 
	//      profile controlled by the Flex Engine.
	// Remarks:
	//    - Calling this method increases the internal reference count on the IMvInputOutput interface.
	virtual HRESULT __stdcall GetInputOutputInterface
		(
		IMvInputOutput ** out_ppIInputOutput   // Pointer that will be initialized with the IMvInputOutput interface 
                                             // pointer.
		) = 0;  

	//
	// Summary:
	//    Retrieves the IMvPlayListCreator interface of the playlist creator.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_DEVICE_NOT_PRESENT, if there's no playlist creator module controlled by the Flex
	//      Engine. 
	// Remarks:
	//    - Calling this method increases the internal reference count on the IMvPlayListCreator
	//      interface. 
	virtual HRESULT __stdcall GetPlayListCreatorInterface
		(
		IMvPlayListCreator ** out_ppICreator   // Pointer that is initialized with the IMvPlayListCreator
		// interface pointer.
		) = 0;  

	//
	// Summary:
	//    Retrieves the IMvSlowMotion interface that performs image-interpolated slow and fast motion effects on a 
   //    video stream.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_DEVICE_NOT_PRESENT, if there's no slow motion device present on the hardware profile
	//      controlled by the Flex Engine.
	// Remarks:
	//    - Calling this method increases the internal reference count on the IMvSlowMotion interface.
	virtual HRESULT __stdcall GetSlowMotionInterface
		(
		IMvSlowMotion ** out_ppISlowMotion  // Pointer that will be initialized with the IMvSlowMotion interface pointer.
		) = 0;

	//
	// Summary:
	//    Retrieves the amount of memory in bytes that's required to allocate the specified surface.
	// Description:
	//    This method does not allocate this memory for the surface. It is for information purposes only.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_NOT_SUPPORTED, if the specified surface create description is not supported.
	//    - MV_E_FAIL, if a fatal error occurs.
	virtual HRESULT __stdcall GetSurfaceMemoryFootprint
		(
		const SMvCreateSurfaceDescription *in_psDescription,  // Pointer to the description of the surface. The memory 
                                                            // size computations are based on the surface description.
		unsigned long               *out_pulMemorySizeInBytes // Pointer that will be filled with the memory size in bytes.
		) = 0; 

	//
	// Summary:
	//    Gets a pointer to the interface of the work audio samples specified by the type and the index.
	// Description:
	//    Work audio samples are used only by the audio mixer and audio effects. The Flex Engine 
	//    keeps a list of all the allocated work audio samples. This method creates a new work audio
	//    sample only if the required work audio sample type is not already created. If it's already
	//    created, a reference to this audio sample is returned. All work audio samples can be shared
	//    by the audio mixer and effects.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if the requested index is invalid or higher than the number of
	//      work audio samples available.
	//    - MV_E_OUT_OF_MEMORY, if no memory is available.
	// Remarks:
	//    - Calling this method increases the internal reference count on the IMvAudioSamples interface. When work
   //      audio samples are no longer needed, use IMvFlexEngine::ReleaseWorkAudioSamples(). 
	virtual HRESULT __stdcall GetWorkAudioSamples
		(
		EMvWorkAudioSamplesType in_eWorkSurfaceType,    // Type of the desired work audio sample. 
		unsigned long           in_ulAudioSamplesIndex, // Index of the desired work audio sample. By specifying an 
                                                      // index greater than zero, more than one work audio sample of the 
		IMvAudioSamples      ** out_ppIMvAudioSamples   // Pointer that receives the desired IMvAudioSamples interface 
                                                      // pointer.
		) = 0;

	//
	// Summary:
	//    Gets a pointer to the interface of the work surface specified by the type and the index.
	// Description:
	//    Work surfaces are intended to be used only by the graphic engine effects. The Flex Engine
	//    keeps a list of all the previously allocated work surfaces. This method creates a new work
	//    surface only if the required work surface type is not already created. If it's already 
	//    created, a reference to this surface will be returned. Hence, all work surfaces can be
	//    shared by the graphic engine effects.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if the requested index is invalid or higher than the number of
	//      work surfaces available.
	//    - MV_E_OUT_OF_MEMORY, if no memory is available.
	// Remarks:
	//    - Calling this method increases the internal reference count on the IMvSurface interface. When a work surface
   //      is no longer needed, use IMvFlexEngine::ReleaseWorkSurface(). 
	virtual HRESULT __stdcall GetWorkSurface
		(
		EMvWorkSurfaceType in_eWorkSurfaceType,   // Type of the desired work surface. 
		unsigned long      in_ulSurfaceIndex,     // Index of the desired work surface. By specifying an index greater 
                                                // than zero, more than one work surface of the same type can be retrieved.
		IMvSurface      ** out_ppISurface         // Pointer that receives the desired IMvSurface interface pointer.
		) = 0;

	//
	// Summary:
	//    Gets the number of previously allocated work surfaces of a specified type.
	// Description:
	//    This method doesn't allocate memory for work surfaces. The method is to be used by a test/validation application.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if the requested type of work surface is invalid.
	virtual HRESULT __stdcall GetWorkSurfaceAllocatedCount
		(
		EMvWorkSurfaceType in_eWorkSurfaceType,   // Type of the desired work surface. 
		unsigned long    * out_pulAllocatedCount  // Number of work surfaces (of the type specified) previously allocated.
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvXScalerHD interface that controls the X.scaler module.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_DEVICE_NOT_PRESENT, if there's no X.scaler module present on the hardware profile
	//      controlled by the Flex Engine.
	// Remarks:
	//    - Calling this method increases the internal reference count on the IMvXScalerHD interface.
	virtual HRESULT __stdcall GetXScalerHDInterface
		(
		IMvXScalerHD ** out_ppIXScalerHD    // Pointer that will be initialized with the IMvXScalerHD interface pointer.
		) = 0;

	//
	// Summary:
	//    Called by an effect to release work audio samples that are no longer needed.
	// Description:
	//    The work audio samples were obtained using the IMvFlexEngine::GetWorkAudioSamples() method.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if the audio samples pointer is NULL.
	//    - MV_E_NOT_FOUND, if the audio samples weren't found in the work audio samples list
	//      maintained by the Flex Engine.
	virtual HRESULT __stdcall ReleaseWorkAudioSamples
		(
		IMvAudioSamples * in_pIAudioSamples // Pointer to the work audio samples (IMvAudioSamples interface) to be released.
		) = 0;

	//
	// Summary:
	//    Called by an effect to release a work surface that is no longer needed.
	// Description:
	//    The work surface was obtained using the IMvFlexEngine::GetWorkSurface() method.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if the surface pointer is NULL.
	//    - MV_E_NOT_FOUND, if the surface wasn't found in the work surface list maintained by the
	//      Flex Engine.
	virtual HRESULT __stdcall ReleaseWorkSurface 
		(
		IMvSurface * in_pISurface  // Pointer to the work surface (IMvSurface interface) to be released.
		) = 0;

	//
	// Summary:
	//    Specifies the conversion quality to apply when color conversion is required by a copy
	//    operation.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if the parameter is NULL.
	//    - MV_E_INVALID_STRUCTURE_SIZE, if the field size of the structure does not contain the
	//      correct value.
	// Remarks:
	//    - Field Size of the structure must be filled before calling the method.
	virtual HRESULT __stdcall SetConversionOptions 
		(
		SMvConversionOptions * io_psConversionOptions   // Pointer to the SMvConversionOptions structure that specifies 
                                                      // the conversion quality desired. 
		) = 0;

	//
	// Summary:
	//    Modifies the caller thread priority.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if the thread priority can't be modified.
	//    - MVF_INVALID_PARAMETER, if the thread priority specified is lower than 16 or higher than 31. 
	virtual HRESULT __stdcall SetThreadPriority 
		(
		unsigned long in_ulThreadPriority   // Desired thread priority to assign to the caller thread. The value must 
                                          // be between 16 and 31, where 31 represents the highest priority.
		) = 0;

	//
	// Summary:
	//    Instantiates a Flex 1394 Reader object and returns the IMvFlex1394Reader interface.
	// Return Value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, the input pointer is NULL.
	//    - MV_E_OUT_OF_MEMORY.
	// Remarks:
	//    - An AddRef call is made to the interface. The Flex Engine does not keep a copy of the
	//      interface.
	virtual HRESULT __stdcall CreateFlex1394Reader
		(
		SMv1394DeviceDescription * in_psDescription,       // SMv1394DeviceDescription pointer to describe the device.
		EMvVideoAudioBufferType    in_eVABufferType,       // EMvVideoAudioBufferType parameter to determine if the 
                                                         // captured file contains both video and audio or video only.
		IMvFlex1394Reader       ** out_ppIFlex1394Reader   // IMvFlex1394Reader interface pointer.
		) = 0;

	//
	// Summary:
	//    Instantiates a Flex 1394 Writer object and returns the IMvFlex1394Writer interface.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, the input pointer is NULL.
	//    - MV_E_OUT_OF_MEMORY, if a memory allocation failed.
	// Remarks:
	//    - An AddRef call is made to the interface. The Flex Engine does not keep a copy of the
	//      interface.
	virtual HRESULT __stdcall CreateFlex1394Writer
		(
		SMv1394DeviceDescription * in_psDescription,       // SMv1394DeviceDescription to describe the device.
		EMvVideoAudioBufferType    in_eVABufferType,       // EMvVideoAudioBufferType parameter to determine if the 
                                                         // captured file contains both video and audio or video only.
		IMvFlex1394Writer       ** out_ppIFlex1394Writer   // IMvFlex1394Writer interface pointer.
		) = 0;

	//
	// Summary:
	//    Calling this method will return IMvMXOControl, the interface that controls the MXO.
	// Return value:
	//    - MV_NOERROR, if the method is successful.
	//    - MV_E_DEVICE_NOT_PRESENT, if there's no MXO present on the hardware profile
	//      controlled by the Flex Engine.
	// Remarks:
	//    - Calling this method increases the internal reference count on IMvMXOControl.
	virtual HRESULT __stdcall GetMXOControlInterface
		(
		IMvMXOControl ** out_ppIMvMXOControl    // Returns a pointer to IMvMXOControl.
		) = 0;


	//
	// Summary:
	//    Executes the equivalent of the SetEvent function of the Microsoft 
	//    Windows API. It sets the specified event object to the signaled state.
	// Return value:
	//    - If the function is successful, the return value is nonzero.
	//    - If the function fails, the return value is zero. 
	//      To get extended error information, call GetLastError.
	// Remarks:
	//    - See MSDN SetEvent for more information.
	virtual BOOL __stdcall SetEvent
		(
		IN HANDLE in_hEvent    // Handle to the event object.
		) = 0;


	//
	// Summary:
	//    Executes the equivalent of the ResetEvent function of the Microsoft 
	//    Windows API. It sets the specified event object to the non-signaled state.
	// Return value:
	//    - If the function is successful, the return value is nonzero.
	//    - If the function fails, the return value is zero. 
	//      To get extended error information, call GetLastError
	// Remarks:
	//    - See MSDN ResetEvent for more information.
	virtual BOOL __stdcall ResetEvent
		(
		IN HANDLE in_hEvent    // Handle to the event object.
		) = 0;

	//
	// Summary:
	//    Executes the equivalent of the OpenEvent function of the Microsoft 
	//    Windows API. It opens an existing named event object.
	// Return value:
	//    - If the function is successful, the return value is a handle to the event object.
	//    - If the function fails, the return value is NULL. 
	//      To get extended error information, call GetLastError.
	// Remarks:
	//    - See MSDN OpenEvent for more information.
	virtual HANDLE __stdcall OpenEvent
		(
		IN DWORD dwDesiredAccess,  // Access to the event object.
		IN BOOL bInheritHandle,    // If true, processes created by this process will inherit the handle.
		IN char* szName            // Pointer to a null-terminated string that names the event to be opened. Name
                                 // comparisons are case sensitive.
		) = 0;

	//
	// Summary:
	//    Executes the equivalent of the CloseHandle function of the Microsoft 
	//    Windows API. It closes an object handle that has been created with the CreateEvent or OpenEvent of the
   //    Flex Engine.
	// Return value:
	//    - If the function is successful, the return value is nonzero.
	//    - If the function fails, the return value is zero. 
	//      To get extended error information, call GetLastError
	// Remarks:
	//    - This Flex API function must be called when the Event was previously created or opened using CreateEvent or
   //      OpenEvent. 
	//    - See MSDN CloseHandle for more information.
	virtual BOOL __stdcall CloseEvent
		(
		IN HANDLE in_hEvent    // Handle to the event object.
		) = 0;


	//
	// Summary:
	//    Executes the equivalent of the CreateEvent function of the Microsoft 
	//    Windows API. It creates or opens a named or unnamed event object.
	// Return value:
	//    - If the function is successful, the return value is a handle to the event object.
	//    - If the function fails, the return value is NULL. 
	//      To get extended error information, call GetLastError.
	// Remarks:
	//    - See MSDN CreateEvent for more information.
	virtual HANDLE __stdcall CreateEvent
		(
		IN LPSECURITY_ATTRIBUTES lpEventAttributes,  // Pointer to a SECURITY_ATTRIBUTES structure. If this parameter is
                                                   // NULL, the handle cannot be inherited by child processes.
		IN BOOL bManualReset,   // If true, the function creates a manual-reset event object, which requires the use of 
                              // the ResetEvent function to set the event state to nonsignaled. <p>If false, the 
                              // function creates an auto-reset event object, and the system automatically resets the 
                              // event state to not signaled after a single waiting thread has been released.
		IN BOOL bInitialState,  // If true, the initial state of the event object is signaled; otherwise, it is 
                              // nonsignaled.
		IN char* szName         // Indicates the name of the event object. The name is limited to 
                              // MVK_MAX_IOCTL_EVENTNAME_SIZE characters. Name comparison is case sensitive. If szName 
                              // is NULL, the event object is created without a name.
		) = 0;


	//
	// Summary:
	//    Executes the equivalent of the WaitForSingleObject function of the Microsoft 
	//    Windows API. It waits until the specified object is in the signaled state or the timeout interval elapses.
	// Return value:
	//    - If the function is successful, the return value indicates the event that caused the function to return. It
   //      can be one of the following values.
	//        - 0x0 - The state of the specified object is signaled.
	//        - WAIT_TIMEOUT - 0x00000102L - The timeout interval elapsed, and the object's state is nonsignaled.
	//    - If the function fails, it returns ((DWORD)0xffffffff). To get extended error information, call GetLastError.      
	// Remarks:
	//    - See MSDN WaitForSingleObject for more information.
	virtual DWORD __stdcall WaitForSingleObject
		(
		IN HANDLE hHandle,      // A handle to the event object.
		IN DWORD dwMilliseconds // The timeout interval, in milliseconds. If dwMilliseconds is INFINITE, the function's 
                              // timeout interval never elapses.
		) = 0;

	//
	// Summary:
	//    Executes the equivalent of the WaitForMultipleObjects function of the Microsoft 
	//    Windows API. It waits until one or all of the specified objects are in the signaled state or the timeout
   //    interval elapses.
	// Return value:
	//    - If the function is successful, the return value indicates the event that caused the function to return. It
   //      can be one of the following values.
	//        - 0x0 - If bWaitAll is true and all the events have been signaled.
	//        - The index (zero based) of the event that has been signaled using the array lpHandles.
	//        - WAIT_TIMEOUT - 0x00000102L - The timeout interval elapsed, and the object's state is nonsignaled.   
	//    - If the function fails, it returns ((DWORD)0xffffffff). To get extended error information, call GetLastError.
	// Remarks:
	//    - See MSDN WaitForMultipleObjects for more information.
	virtual DWORD __stdcall WaitForMultipleObjects
		(
		IN DWORD nCount,            // The number of object handles in the array pointed to by lpHandles.
		IN const HANDLE* lpHandles, // An array of event handles.
		IN BOOL bWaitAll,           // If true, the function returns when the state of all objects in the lpHandles array
                                  // is signaled.
		IN DWORD dwMilliseconds     // The timeout interval, in milliseconds. If dwMilliseconds is infinite, the
                                  // function's timeout interval never elapses.
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvDisplayManager interface that is used to configure and control 
	//    output on the display card's GPU.
	// Return value:
	//    - MV_NOERROR if completed successfully.
	//    - MV_E_DEVICE_NOT_PRESENT, if IMvDisplayManager can't be detected by the Flex Engine.
	// Remarks:
	//    - Calling this method increases the internal reference count on the IMvDisplayManager interface.
	virtual HRESULT __stdcall GetDisplayManagerInterface
		(
		IMvDisplayManager ** out_ppIDisplayManager   // Pointer that will be initialized with the IMvDisplayManager 
                                                   // interface pointer.
		) = 0;

	//
	// Summary:
	//    Combines video and key surfaces, and specifies whether or not the luminance range of the alpha information is
   //    to be expanded.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if any of the parameters are invalid. This error is also 
	//      returned if the rectangles are not within the surface size.
	//    - MV_E_LOCATION_NOT_SUPPORTED, if there's no processor or DMA available to copy from the
	//      source memory location to the destination memory location.
	//    - MV_E_COLORCONVERSION_NOT_SUPPORTED, if the copy implies a color/format conversion that is
	//      not supported. 
	//    - MV_E_IMAGEORIGINCONVERSION_NOT_SUPPORTED, if the copy implies an unsupported conversion
	//      between two surfaces having different image origins.
	//    - MV_E_POLARITYCONVERSION_NOT_SUPPORTED, if the copy implies a deinterlace or interlace 
	//      operation that is not supported.
	//    - MV_E_MODULE_BUSY, if a previous CombineVideoAndKeySurfacesEx() method call with the same 
	//      thread pool ID is not completed yet. This limitation is for host-CPU copy only.
	//    - MV_E_NOT_READY_FOR_READ, if the source surface is not ready for a read operation. This
	//      limitation is for host-CPU copy only.
	//    - MV_E_COPY_FORMATS_COMBINATION_NOT_SUPPORTED, if the source and destination surface format
	//      combination is not supported by the CombineVideoAndKeySurfacesEx() method. 
	//    - MV_E_POINTER_NOT_ALIGNED, if any of the surface data pointers are not properly aligned. 
	virtual HRESULT __stdcall CombineVideoAndKeySurfacesEx
		(
		IMvSurface     *in_pIVideoSurfaceSource,  // Address of the IMvSurface interface that is the video source of the 
                                                // combine operation.
		IMvSurface     *in_pIKeySurfaceSource,    // Address of the IMvSurface interface that is the key source of the 
                                                // combine operation.
		IMvSurface     *io_pISurfaceDestination,  // Address of the IMvSurface interface that is the destination of the 
                                                // combine operation.
		unsigned long  in_ulThreadPoolIndex,      // Index of the thread pool to use. This is used only when the copy is 
                                                // done by the CPU.
		bool           in_bIsAlphaScalingNeeded   // If true, the luminance range of the alpha information is to be 
                                                // explanded from 16-235 to 0-255.
		) = 0;

	//
	// Summary:
	//    Return the interface required to create a server and/or a client session.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if one or some parameters are invalid. 
	//    - MV_E_NOT_SUPPORTED, if the Flex Engine doesn't support Video over IP.
	virtual HRESULT __stdcall GetIPInputOutputInterface
		(
		IMvIPInputOutput **out_ppIMvIPInputOutput
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvVancPacketExtractor interface that extracts VANC packet information from a VANC surface.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_DEVICE_NOT_PRESENT, if the VANC packet extractor could not be created.
	// Remarks:
	//    - Calling this method increases the internal reference count on the IMvVancPacketExtractor interface.
	virtual HRESULT __stdcall GetVancPacketExtractorInterface
		(
		IMvVancPacketExtractor ** out_ppIVancPacketExtractor  // Pointer that will be initialized with the
                                                            // IMvVancPacketExtractor interface pointer.
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvVancPacketInserter interface that inserts VANC packet information in a VANC surface.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_DEVICE_NOT_PRESENT, if the VANC packet inserter could not be created.
	// Remarks:
	//    - Calling this method increases the internal reference count on the IMvVancPacketInserter interface.
	virtual HRESULT __stdcall GetVancPacketInserterInterface
		(
		IMvVancPacketInserter ** out_ppIVancPacketInserter // Pointer that will be initialized with the
                                                         // IMvVancPacketInserter interface pointer.
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvVancConverter interface that converts VANC packets from one video standard/resolution to
   //    another.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_DEVICE_NOT_PRESENT, if the VANC converter could not be created.
	// Remarks:
	//    - Calling this method increases the internal reference count on the IMvVancConverter interface.
	virtual HRESULT __stdcall GetVancConverterInterface
		(
		IMvVancConverter ** out_ppIVancConverter // Pointer that will be initialized with the IMvVancConverter
		                                         // interface pointer.
		) = 0;

	//
	// Summary:
	//    Instantiates a Flex Media Reader object and returns the IMvMediaReader interface.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if out_ppIMediaReader is NULL.
	virtual HRESULT __stdcall CreateMediaReader
		(
		IMvMediaReader** out_ppIMediaReader // Pointer that will store the media reader interface output parameter.
		) = 0;

	//
	// Summary:
	//    Instantiates a Flex Media Writer object and returns the IMvMediaWriter interface.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if out_ppIMediaWriter is NULL.
	virtual HRESULT __stdcall CreateMediaWriter
		(
		IMvMediaWriter** out_ppIMediaWriter // Pointer that will store the media writer interface output parameter.
		) = 0;

	//
	// Summary:
	//    Instantiates a Flex Transport Stream Encoder object and returns the IMvTSEncoder interface.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if out_ppITSEncoder is NULL.
	virtual HRESULT __stdcall CreateTSEncoder
		(
		IMvTSEncoder** out_ppITSEncoder // Pointer that receives the IMvTSEncoder interface pointer.
		) = 0;


	//
	// Summary:
	//    Instantiates a Matrox MPEG-2 Transport Stream Muxer object and returns the IMvMPEG2TSMuxer interface.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if out_ppITSEncoder is NULL.
	virtual HRESULT __stdcall CreateMPEG2TSMuxer
		(
		IMvMPEG2TSMuxer** out_ppIMPEG2TSMuxer // Pointer that receives the IMvMPEG2TSMuxer interface pointer.
		) = 0;

   //
   // Summary:
   //    Instantiates a Matrox MPEG-2 Transport Stream Muxer object and returns the IMvMPEG2TSMuxer interface.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if out_ppITSEncoder is NULL.
   virtual HRESULT __stdcall CreateMPEG2TSDemuxer
      (
      IMvMPEG2TSDemuxer** out_ppIMPEG2TSDemuxer // Pointer that receives the IMvMPEG2TSMuxer interface pointer.
      ) = 0;

   //
   // Summary:
   //    Retrieves the interface that configures the I/O and hardware-related operations for topology-based hardware.
   // Return value:
   //    - MV_NOERROR, if completed successfully
   //    - MV_E_INVALID_POINTER, if out_ppICardConfiguration is NULL.
   //    - MV_E_NOT_SUPPORTED, if this interface is not supported by the current hardware profile.
   virtual HRESULT __stdcall GetCardConfigurationInterface
      (
      IMvCardConfiguration** out_ppICardConfiguration // Pointer that will be initailized with the IMvCardConfiguration
                                                      // interface pointer.
      ) = 0;

   //
   // Summary:
   //    Instantiates a Flex GPU Transfer object and returns the IMvGpuTransfer interface.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_UNSUPPORTED_GPU_CARD, if the detected graphic card is not supported.
   //    - MV_E_INVALID_POINTER, if out_ppINewInterface is NULL.
   virtual HRESULT __stdcall CreateGpuTransferInterface
      (
      const SMvResolutionInfo & in_krsResolution,     // Resolution at which the Flex GPU transfer will work.
      IMvGpuTransfer         ** out_ppINewInterface   // Pointer that will be initialized with the IMvGpuTransfer
                                                      // interface pointer. 
      ) = 0;

   //
   // Summary:
   //    Instantiates a Flex GPU Transfer object and returns the IMvGpuTransfer interface.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_UNSUPPORTED_GPU_CARD, if the detected graphic card is not supported.
   //    - MV_E_INVALID_POINTER, if out_ppINewInterface is NULL.
   virtual HRESULT __stdcall CreateGpuTransferInterfaceEx
      (
      const SMvGPUTranferSettings & in_krsSettings,   // Settings used by the Flex GPU Transfer module.
      IMvGpuTransfer         ** out_ppINewInterface   // Pointer that will be initialized with the IMvGpuTransfer
                                                      // interface pointer. 
      ) = 0;

	//
	// Summary:
	//    Instantiates a Flex Tunnel to DirectShow Manager object and returns the IMvFlexTunnelToDirectShowManager interface.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if out_ppITunnelManager is NULL.
	// Remarks:
	virtual HRESULT __stdcall CreateFlexTunnelToDirectShowManager
		(
		IMvFlexTunnelToDirectShowManager ** out_ppITunnelManager    // Pointer that will be initialized with the
                                                                  // IMvFlexTunnelToDirectShowManager interface pointer.
		) = 0;

};


////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Hardware and software Flex Compositors must implement this interface.
//
////////////////////////////////////////////////////////////////////////////
interface IMvCompositorRenderer
: public IUnknown
{
	//
	// Summary:
	//    Performs a compositor operation in upstream mode.
	//
	virtual HRESULT __stdcall UpstreamCompose(
		IMvSurface           *io_pIOutputSurface,          // An output surface in which to render.
		unsigned long         in_ulLayerCount,             // A number of input surfaces passed in an array in order for
                                                         // the effect to render.
		IMvSurface           *in_apIInputSurfaceArray[],   // An array of pointers in which to retrieve the input surfaces.
		IMvEffectSettings    *in_apICompositorSettings[]   // An array of pointers to the effect (compositor) settings 
                                                         // necessary to compose each layer.
	) = 0;

	//
	// Summary:
	//    Performs a compositor operation in downstream mode.
	//
	virtual HRESULT __stdcall DownstreamCompose(
      IMvSurface            *io_pIOutputSurface,            // An output surface in which to render.
      unsigned long          in_ulLayerCount,               // A number of input surfaces passed in an array in order
                                                            // for the effect to render.
      IMvSurface            *in_apIInputSurfaceArray[],     // An array of pointers in which to retrieve the input
                                                            // surfaces.
      IMvEffectSettings 	 *in_apICompositorSettings[],    // An array of pointers to the effect (compositor) settings
                                                            // necessary to compose each layer
      IMvSurface            *in_pIBackgroundSurface,        // The background surface of the composition.
      EMvColor		           in_eColor,                     // Color associated with the background.
      EMvBackgroundHandling  in_eBackgroundHandling         // Flags indicating how the effect must handle the background.   
		) = 0; 
};        

////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Exposes methods that are called to create an effect instance. Each new 
//    effect should implement this interface so that the Flex Engine can 
//    instantiate the effect.
//
////////////////////////////////////////////////////////////////////////////
interface IMvEffectRendererFactory 
: public IUnknown
{
	//
	// Summary:
	//    Called to create an IMvEffect object that is associated with one or more instances of hardware-based and/or
   //    host-based effects.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - A valid error code.
	virtual HRESULT __stdcall CreateEffectRenderer(
		IMvFlexEngine *in_pIFlexEngine,                 // Pointer to a valid IMvFlexEngine interface.  The effect uses this 
                                                      // interface to retrieve SMvfEngineProfileInfo and, in the case of 
                                                      // a hardware-based effect, a pointer to Flex3D Device.
		unsigned long  in_ulNbHostEffect,               // Number of host-based effects to create.
		unsigned long *in_aulHostEffectPriorities,      // Array containing in_ulNbHostEffect priorities, one for each 
                                                      // host-based effect that will be created.
		IMvEffect    **out_pIEffect,                    // Pointer to a pointer that receives the created IMvEffect.
      const SMvResolutionInfo * in_psResInfo = NULL   // Resolution to be used by the effect
		) = 0;

	//
	// Summary:
	//    Called to retrieve the capabilities of the current effect.
	// Return value:
	//    - S_OK, if completed succressfully.
	//    - A valid Flex error code.
	virtual HRESULT __stdcall GetEffectCapabilities(
		IMvFlexEngine        *in_pIFlexEngine,    // 
		SMvEffectCapabilities *io_pCapabilities   //
		) = 0;      
};

////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Hardware and software Flex effects must implement this interface.
//
////////////////////////////////////////////////////////////////////////////
interface IMvEffectRenderer
: public IUnknown
{
	//
	// Summary:
	//    Performs a filter operation in upstream mode.
	//
	virtual HRESULT __stdcall UpstreamFilter(
		IMvSurface           *io_pIOutputSurface,       // An output surface in which to render.
		unsigned long         in_ulInputSurfaceCount,   // A number of input surfaces passed in an array in order for 
                                                      // the effect to render.
		IMvSurface           *in_apIInputSurfaceArray[],// An array pointer in which to retrieve the input surface.
		IMvEffectSettings    *in_pIEffectSettings,      // A pointer to the effect settings necessary to render the effect.
		IMvContainer         *in_pIEffectPattern        // A pointer to IMvContainer that holds additional data needed 
                                                      // by the effect.  Can be NULL if not needed.
		) = 0;

	//
	// Summary:
	//    Performs a transition operation in upstream mode.
	//
	virtual HRESULT __stdcall UpstreamTransition(
		IMvSurface        *io_pIOutputSurface,    // An output surface in which to render.
		IMvSurface        *in_pISurfaceA,         // A pointer to the input surface A
		IMvSurface        *in_pISurfaceB,         // A pointer to the input surface B.
		IMvEffectSettings *in_pIEffectSettings,   // A pointer to the effect settings necessary to render the effect.
		IMvContainer      *in_pIEffectPattern     // A pointer to IMvContainer that holds additional data needed by
		                                          // the effect.  Can be NULL if not needed.
		) = 0;

	//
	// Summary:
	//    Performs a filter operation in downstream mode.
	//
	virtual HRESULT __stdcall DownstreamFilter(
		IMvSurface           *io_pIOutputSurface,       // The output surface in which to render.
		unsigned long         in_ulInputSurfaceCount,   // The number of input surfaces passed in the array 
		                                                // in order for the effect to render.
		IMvSurface           *in_apIInputSurfaceArray[],// The array pointer in which to retrieve the input surface.
		IMvEffectSettings    *in_pIEffectSettings,      // Pointer to the effect settings necessary to 
		                                                // render the effect.
		IMvContainer         *in_pIEffectPattern,       // Pointer to an IMvContainer that holds additional 
		                                                // data needed by the effect.  Can be NULL if not needed.
		IMvSurface           *in_pIBackgroundSurface,   // The background surface in which to render.
		EMvColor              in_eColor,                // Color associated with the background.
		EMvBackgroundHandling in_eBackgroundHandling,   // Flags indicating how the effect must handle the background.
		IMvEffectSettings    *in_pICompositorSettings   // Pointer to the compositor settings.
		) = 0;

	//
	// Summary:
	//    Performs a transition operation in downstream mode.
	//
	virtual HRESULT __stdcall DownstreamTransition(
		IMvSurface             *io_pIOutputSurface,     // The output surface in which to render.
		IMvSurface             *in_pISurfaceA,          // A pointer to the input surface A.
		IMvSurface             *in_pISurfaceB,          // A pointer to the input surface B.
		IMvEffectSettings      *in_pIEffectSettings,    // Pointer to the effect settings necessary to render the effect.
		IMvContainer           *in_pIEffectPattern,     // Pointer to an IMvContainer that holds additional data needed
                                                      // by the effect. Can be NULL if not needed.
		IMvSurface             *in_pIBackgroundSurface, // The background surface in which to render.
		EMvColor                in_eColor,              // Color associated with the background.
		EMvBackgroundHandling   in_eBackgroundHandling, // Flags indicating how the effect must handle the background.
		IMvEffectSettings      *in_pICompositorSettings // Pointer to the compositor settings.


		) = 0;

	// 
	// Summary:
	//    Generates the GFX (effect pattern) data that is ready to be written into a file.
	// Remarks:
	//    This method is used depending on the effect that is being implemented. It is not always required.
	virtual HRESULT __stdcall PreprocessEffectPattern
		(
		IMvContainer  * in_pInData,   // Container that holds the data that will be used to generate the GFX.
		IMvContainer ** out_ppOutData // Container that holds the data that will be written in the GFX.


		) = 0;
};

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This interface is the public interface when using the mixer. It has the thread pool information
//    and manages a pool of Effect Settings.
//
//////////////////////////////////////////////////////////////////////////
interface IMvAudioMixer : public IUnknown
{
	//
	// Summary:
	//    Called to mix input tracks of audio into 1 output track of audio using CPU with host memory 
	//    at a specific thread pool index.
	// Return value:
	//    - MV_NOERROR, if everything went fine.
	//    - HRESULT error code, if something went wrong.
	// Remarks:
	//    - This method calls the Audio Mixer object running at the corresponding pool index. 
	//    - The Mix method's implementation will perform an IMvAudioSamples::SetLength on the 
	//      destination buffer in_pIOutputBuffer once its asynchronous processing is completed. You 
	//      will need to take special precautions if the source buffer in_apIInputBufferarray and the 
	//      destination buffer in_pIOutputBuffer are not the same length. 
	virtual HRESULT __stdcall Mix
		(
		IMvAudioSamples**   in_apIInputBufferArray,  // Array of input buffers.
		unsigned long       in_ulTrackCount,         // Number of input tracks (number of elements in the Effect Settings 
                                                   // and input buffer array). 
		IMvAudioSamples*    io_pIOutputBuffer,       // Output buffer.
		IMvEffectSettings** in_apIMixerSettings,     // Array of Effect Settings that are Mixer Effect.
		unsigned long       in_ulPoolIndex           // The pool index - that translates to thread priority - of the 
                                                   // operation to run at.
		)=0;
};

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that manages a pool of effect settings and provides the unused ones.
// Remarks:
//    - This interface can be obtained with a QueryInterface(IID_IMvEffectSettingsPool) on the  
//      interface IMvEffect, ImvCompositor, or IMvAudioMixer. 
//
//////////////////////////////////////////////////////////////////////////
interface IMvEffectSettingsPool
: public IUnknown
{
	//
	// Summary:
	//    Returns unused effect settings.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if one of the pointer's parameters is NULL 
	//    - MV_E_FAIL, if failed. 
	virtual HRESULT __stdcall GetEffectSettings
		(
		IMvEffectSettings ** io_ppIEffectSettings    // Pointer that receives the address of the requested effect settings.
		)=0;
}; 

//////////////////////////////////////////////////////////////////////////
// JUNK
typedef void *IMvaAudioEffect_KeyFrame; // place holder for something we define later.
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates all codecs installed on the system. This interface can be obtained from the 
//    IMvFlexEngine interface.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvCodecEnumerator: public IUnknown
{
	//
	// Summary:
	//    Gets the next available codec installed on the system.
	// Description:
	// The next codec installed on the system is retrieved from the internal list of codecs.
	// Return value:
	//    - MV_NOERROR, if properly filled. 
	//    - MV_E_END_OF_ENUM, if there is no more codec information to enumerate. 
	//    - MV_E_INVALID_STRUCTURE_SIZE, if the structure size of pInfo is not initialized properly.
	virtual HRESULT __stdcall Next 
		( 
		unsigned long   in_ulNbCodecInfoRequested,   // Number of entries in the codec information structure.
		SMvCodecInfo  * out_psCodecInfo,             // Pointer to the array of structures describing the codec
                                                   // information.
		unsigned long * out_pulCodecInfoFetched      // Pointer to the number of entries that have been filled in the
                                                   // array of structures.
		) = 0;

	//
	// Summary:
	//    Resets the internal counter to the first codec found on the system.
	// Description:
	//    The internal pointer is reset so that the next call to IMvCodecEnumerator::Next returns the first codec found
   //    on the system.
	// Return value:
	//    - Always returns MV_NOERROR. 
	virtual HRESULT __stdcall Reset () = 0;

	//
	// Summary:
	//    Skips a given number of codecs.
	// Description:
	//    The internal pointer is reset so that the next call to IMvCodecEnumerator::Next skips a given number of codecs
   //    in the internal list.
	// Return value:
	//    - Always returns MV_NOERROR. 
	virtual HRESULT __stdcall Skip
		(
		unsigned long in_ulCount   // Number of codecs to skip.
		) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    The interface for the Group of Pictures Descriptor
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvGroupOfPicturesDescriptor
: public IUnknown
{
	//
	// Summary:
	//    Provides the description of the Group of Pictures.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if a pointer is invalid. 
	// Remarks:
	//    - This call is synchronous. 
	virtual HRESULT __stdcall GetDescription
		(
		SMvGroupOfPicturesDescription * in_pGOPDescription    // Pointer to a destination structure that receives the 
                                                            // description.
		)=0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Used to compress and decompress data.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvCodec 
: public IUnknown
{
	//
	// Summary:
	//    Receives one YUV 8-bit frame-based buffer and compresses it using the codec specified by 
	//    the surface format of the destination buffer.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_MODULE_BUSY, if thread re-entrance is detected. 
	//    - MV_E_INVALID_POINTER, if any pointer is invalid. 
	//    - MV_E_AVCONTENT_IN_USE, if the source surface is not ready to read. 
	//    - MV_E_INVALID_PARAMETER, if any of the Flex surface parameters are invalid according to 
	//      the type of operation. 
	// Remarks:
	//    - This call is asynchronous but the initialization (validation of parameters) is performed 
	//      in the calling thread. 
	virtual HRESULT __stdcall CompressFrame
		(
		IMvSurface  * in_pIMvSurfaceSrc, // Pointer to the source Flex surface.
		IMvSurface  * in_pIMvSurfaceDst, // Pointer to the destination Flex surface.
		unsigned long in_ulIgnored      // IGNORED.
		) = 0;

	//
	// Summary:
	//    Decodes the data in the source buffer into one YUV 8-bit frame-based buffer. The decoder 
	//    used is specified by the source buffer surface format.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_MODULE_BUSY, if thread re-entrance is detected. 
	//    - MV_E_INVALID_POINTER, if any pointer is invalid. 
	//    - MV_E_AVCONTENT_IN_USE, if the source surface is not ready to read. 
	//    - MV_E_INVALID_PARAMETER, if any of the Flex surface parameters are invalid according to 
	//      the type of operation. 
	// Remarks:
	//    - This call is asynchronous but the initialization (validation of parameters) is done in
	//      the calling thread. 
	virtual HRESULT __stdcall DecompressFrame
		(
		IMvSurface  * in_pIMvSurfaceSrc, // Pointer to the source Flex surface.
		IMvSurface  * in_pIMvSurfaceDst, // Pointer to the destination Flex surface.
		unsigned long in_ulIgnored      // IGNORED.
		) = 0;

	//
	// Summary:
	//    This method receives two YUV 8-bit field-based buffers and compresses them using the codec
	//    specified by the destination buffer surface format.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_MODULE_BUSY, if thread re-entrance is detected. 
	//    - MV_E_INVALID_POINTER, if any pointer is invalid. 
	//    - MV_E_AVCONTENT_IN_USE, if the source surface is not ready to read. 
	//    - MV_E_INVALID_PARAMETER, if any of the Flex surface parameters are invalid according to 
	//      the type of operation. 
	// Remarks:
	//    - This call is asynchronous but the initialization (validation of parameters) is performed
	//      in the calling thread. 
	virtual HRESULT __stdcall CompressFields
		(
		IMvSurface  * in_pIMvSurfaceSrc,    // Pointer to the source Flex surface.
		IMvSurface  * in_pIMvSurfaceSrc2,   // Pointer to the source Flex surface.
		IMvSurface  * in_pIMvSurfaceDst,    // Pointer to the destination Flex surface.
		unsigned long in_ulIgnored          // IGNORED.
		) = 0;

	//
	// Summary:
	//    Decodes the data in the source buffer into two YUV 8-bit field-based buffers.  The decoder 
	//    used is specified by the source buffer surface format.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_MODULE_BUSY, if thread re-entrance is detected. 
	//    - MV_E_INVALID_POINTER, if any pointer is invalid. 
	//    - MV_E_AVCONTENT_IN_USE, if the source surface is not ready to read. 
	//    - MV_E_INVALID_PARAMETER, if any of the Flex surface parameters are invalid according to 
	//      the type of operation. 
	// Remarks:
	//    - This call is asynchronous but the initialization (validation of parameters) is done in 
	//      the calling thread. 
	virtual HRESULT __stdcall DecompressFields
		(
		IMvSurface  * in_pIMvSurfaceSrc,    // Pointer to the source Flex surface.
		IMvSurface  * in_pIMvSurfaceDst,    // Pointer to the destination Flex surface.
		IMvSurface  * in_pIMvSurfaceDst2,   // Pointer to the destination Flex surface.
		unsigned long in_ulIgnored          // IGNORED.
		) = 0;

	//
	// Summary:
	//    Retrieves the value of one of the codec options.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_SUPPORTED, if option is not supported by the codec. 
	virtual HRESULT __stdcall GetCodecOption
		(
		MVCHANDLE      out_pmvchOptionValue,   // Pointer to the value of the option.
		EMvCodecOption in_eCodecOption,        // Enumerator that specifies which option that we want to query.
		unsigned long  in_ulIgnored            // IGNORED.
		) = 0;

	//
	// Summary:
	//    Sets the value of one of the codec options.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_SUPPORTED, if option is not supported by the codec. 
	//    - MV_E_INVALID_PARAMETER, if option value is invalid. 
	virtual HRESULT __stdcall SetCodecOption
		(
		MVCHANDLE      in_pmvchOptionValue, // Pointer to the value of the option.
		EMvCodecOption in_eCodecOption,     // Enumerator that specifies which option you want to set.
		unsigned long  in_ulIgnored         // IGNORED.
		) = 0;

	//
	// Summary:
	//    Checks if a certain option is supported by the codec.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	virtual HRESULT __stdcall IsCodecOptionSupported
		(
		EMvCodecOption in_eCodecOption,  // Enumerator that specifies which option you want to validate.
		bool         * out_pbSupported,  // Pointer to bool that validates support.
		unsigned long  in_ulIgnored      // IGNORED.
		) = 0;

	//
	// Summary:
	//    Called to get the description from a GOP (Group of pictures).
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if any pointer is invalid. 
	//    - MV_E_INVALID_PARAMETER, if any of the Flex surface parameters are invalid according to
	//      the type of operation. 
	//    - MV_E_INVALID_GOP, if any problems occurred when scanning the GOP. 
	// Remarks:
	//    - This call is synchronous. 
	virtual HRESULT __stdcall CreateGroupOfPicturesDescription
		(
		IMvGroupOfPicturesDescriptor ** in_ppIMvSrcGroupOfPicturesDescriptor,   // Pointer to a location that will 
                                                                              // contain a compressed GOP data 
                                                                              // descriptor pointer when the 
		                                                                        // method returns.
		IMvSurface                    * in_pIMvSrcGroupOfPictures,  // Pointer to a source Flex surface containing the 
		                                                            // compressed GOP data.
		unsigned char                 * in_pHeader,     // Pointer to a buffer containing at least the Sequence header
		                                                // and Extension headers. Useful when those headers are not 
                                                      // included in all GOPs. Can be NULL if the GOP to decode 
                                                      // contains the sequence header.
		unsigned long                 in_ulHeaderSize,  // Size of in_pucHeader.
		unsigned long                 in_ulIgnored      // IGNORED.
		) = 0;

	//
	// Summary:
	//    Called to get the description from a GOP (Group of pictures).
	//    Useful when those headers are not included in all GOPs.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if any pointer is invalid. 
	//    - MV_E_INVALID_PARAMETER, if any of the Flex surface parameters are invalid according to
	//      the type of operation. 
	//    - MV_E_INVALID_GOP, if any problems occurred when scanning the GOP. 
	// Remarks:
	//    - This call is synchronous. 
	virtual HRESULT __stdcall CreateGroupOfPicturesDescriptionWithHeader
		(
		IMvGroupOfPicturesDescriptor  ** io_ppIMvSrcGroupOfPicturesDescriptor,  // Pointer to a location that will 
                                                                              // contain a compressed GOP data 
                                                                              // descriptor pointer when the method 
                                                                              // returns.
		IMvSurface            * in_pIMvSrcGroupOfPictures, // Pointer to a source Flex surface containing the 
		                                                   // compressed GOP data.
		SMvMpeg2SeqHeaderInfo * in_psMvPreviousSeqHeaderInfo,    // Pointer to the previous the sequence header info. 
                                                               // Can be NULL.
		SMvMpeg2SeqHeaderInfo * out_psMvCurrentSeqHeaderInfo,    // Pointer to a location that will contain the current 
                                                               // sequence header info structure descriptor pointer.
		unsigned long           in_ulIgnored // IGNORED.
		) = 0;

	//
	// Summary:
	//    Decompresses frame information from a Group of Pictures (GOP).
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_MODULE_BUSY, if thread re-entrance is detected. 
	//    - MV_E_INVALID_POINTER, if any pointer is invalid. 
	//    - MV_E_AVCONTENT_IN_USE, if the source surface is not ready to read. 
	//    - MV_E_OPEN_GOP_NOT_SUPPORTED, if the flag Close_GOP in the GOP header is equal to 0. 
	//    - MV_E_INVALID_PARAMETER, if any of the Flex surface parameters are invalid according to 
	//      the type of operation. 
	// Return value:
	//    - This call is asynchronous but the initialization (validation of parameters) is done in
	//      the calling thread. 
	virtual HRESULT __stdcall DecompressFrameFromGroupOfPictures
		(
		IMvSurface                   * in_pIMvSrcGroupOfPictures,   // Pointer to a source Flex surface containing the 
                                                                  // compressed GOP data.
		IMvGroupOfPicturesDescriptor * in_pIMvSrcGroupOfPicturesDescriptor,  // Pointer to a compressed
		                                                                     // GOP data descriptor. It must match the 
		                                                                     //  GOP it wascreated for.
		IMvSurface                   * in_pIMvSrcOpenGOP,  // Pointer to a source Flex surface containing 
		                                                   // the compressed GOP data. This is the GOP preceding 
		                                                   // pIMvSrcGroupOfPictures. It can be NULL if the 
		                                                   // current GOP is a closed GOP. There's no penalty for 
		                                                   // always passing the previous GOP.
		IMvGroupOfPicturesDescriptor * in_pIMvReferenceDescForOpenGOP, // Pointer to a compressed GOP
		                                                               // data descriptor. It must match the GOP it was 
		                                                               // created for, i.e. in_pIMvSrcOpenGOPReference. It 
		                                                               // can be NULL if the current GOP is a closed GOP. 
		                                                               // There's no penalty for always passing the 
		                                                               // previous GOP descriptor.
		unsigned long                  in_ulFramePosition, // Index of the frame to decompress from the 
		                                                   // group of pictures. This parameter is based on the 
		                                                   // Display order of the frame from 0 to 
		                                                   // ulTotalNumberOfFrames. This value must be set back 
		                                                   // to 0 at the beginning of each GOP.
		IMvSurface                   * in_pIMvSurfaceDst,  // Pointer to a destination Flex surface 
		                                                   // that will receive the decompressed data.
		unsigned long                  in_ulIgnored        // IGNORED
		) = 0;

	//
	// Summary:
	//    Decompresses field information from a Group of Pictures (GOP).
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_MODULE_BUSY, if thread re-entrance is detected. 
	//    - MV_E_INVALID_POINTER, if any pointer is invalid. 
	//    - MV_E_AVCONTENT_IN_USE, if the source surface is not ready to read. 
	//    - MV_E_OPEN_GOP_NOT_SUPPORTED, if the flag Close_GOP in the GOP header is equal to 0. 
	//    - MV_E_INVALID_PARAMETER, if any of the Flex surface parameters are invalid according 
	//      to the type of operation. 
	// Remarks:
	//    - This call is asynchronous but the initialization (validation of parameters) is done in
	//      the calling thread. 
	virtual HRESULT __stdcall DecompressFieldsFromGroupOfPictures
		(
		IMvSurface                   * in_pIMvSrcGroupOfPictures,   // Pointer to a source Flex surface containing the
                                                            		// compressed GOP data.
		IMvGroupOfPicturesDescriptor * in_pIMvSrcGroupOfPicturesDescriptor,  // Pointer to a compressed GOP data
		                                                                     // descriptor. It must match the  GOP it was
		                                                                     // created for.
		IMvSurface                   * in_pIMvSrcOpenGOP,  // Pointer to a source Flex surface containing the compressed
		                                                   // GOP data. This is the GOP preceding pIMvSrcGroupOfPictures. 
                                                         // It can be NULL if  the current GOP is a closed GOP. 
                                                         // There's no penalty for always passing the previous GOP.   
		IMvGroupOfPicturesDescriptor * in_pIMvReferenceDescForOpenGOP, // Pointer to a compressed GOP data descriptor. 
                                                                     // It must match the GOP it was created for, i.e.
                                                                     // in_pIMvSrcOpenGOPReference. It can be NULL
		                                                               // if the current GOP is a closed GOP. Theres no 
		                                                               // penalty for always passing the previous GOP
		                                                               // descriptor.
		unsigned long                  in_ulFramePosition, // Index of the frame to decompress from the group of 
                                                         // pictures.  This parameter is based on the display order 
                                                         // of the frame from 0 to ulTotalNumberOfFrames. This value 
                                                         // must be set back to 0 at the beginning of each GOP.
		IMvSurface                   * in_pIMvSurfaceDst,  // Pointer to a destination Flex surface that will receive 
                                                         // the decompressed data for the first field.
		IMvSurface                   * in_pIMvSurfaceDst2, // Pointer to a destination Flex surface that will receive 
                                                         // the decompressed data for the second field.
		unsigned long                  in_ulIgnored        // IGNORED
		) = 0;

	//
	// Summary:
	//    This method receives one YUV 8-bit frame-based video buffer, one YUV 8-bit frame-based VBI 
	//    buffer, and compresses them using the codec specified by the destination buffer surface format. 
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_MODULE_BUSY, if thread re-entrance is detected. 
	//    - MV_E_INVALID_POINTER, if any pointer is invalid. 
	//    - MV_E_AVCONTENT_IN_USE, if the source surface is not ready to read. 
	//    - MV_E_INVALID_PARAMETER, if any of the Flex surface parameters are invalid according to 
	//      the type of operation. 
	// Remarks:
	//    - This call is asynchronous but the initialization (validation of parameters) is performed 
	//      in the calling thread. 
	virtual HRESULT __stdcall CompressFrameVideoAndVbi
		(
		IMvSurface  * in_pIVideoSrc,  // Pointer to the source Flex video surface.
		IMvSurface  * in_pIVBISrc,    // Pointer to the source Flex VBI surface.
		IMvSurface  * io_pIDest,      // Pointer to the destination Flex surface.
		unsigned long in_ulIgnored    // IGNORED
		) = 0;

	//
	// Summary:
	//    Decodes the data in the source buffer into one YUV 8-bit frame-based video buffer and one 
	//    YUV 8-bit frame-based VBI buffer.  The decoder used is specified by the source buffer surface format.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_MODULE_BUSY, if thread re-entrance is detected. 
	//    - MV_E_INVALID_POINTER, if any pointer is invalid. 
	//    - MV_E_AVCONTENT_IN_USE, if the source surface is not ready to read. 
	//    - MV_E_INVALID_PARAMETER, if any of the Flex surface parameters are invalid according to 
	//      the type of operation. 
	// Remarks:
	//    - This call is asynchronous but the initialization (validation of parameters) is done in
	//      the calling thread. 
	virtual HRESULT __stdcall DecompressFrameVideoAndVbi
		(
		IMvSurface  * in_pISource,    // Pointer to the source Flex surface.
		IMvSurface  * io_pIVideoDest, // Pointer to the video destination Flex surface.
		IMvSurface  * io_pIVBIDest,   // Pointer to the VBI destination Flex surface.
		unsigned long in_ulIgnored    // IGNORED.
		) = 0;

	//
	// Summary:
	//    This method receives two YUV 8-bit field-based video buffers, two YUV 8-bit field-based VBI 
	//    buffers, and compresses them using the codec specified by the surface format of the 
	//    destination buffer.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_MODULE_BUSY, if thread re-entrance is detected. 
	//    - MV_E_INVALID_POINTER, if any pointer is invalid. 
	//    - MV_E_AVCONTENT_IN_USE, if the source surface is not ready to read. 
	//    - MV_E_INVALID_PARAMETER, if any of the Flex surface parameters are invalid according to 
	//      the type of operation. 
	// Remarks:
	//    - This call is asynchronous but the initialization (validation of parameters) is performed
	//      in the calling thread. 
	virtual HRESULT __stdcall CompressFieldsVideoAndVbi
		(
		IMvSurface  * in_pIVideoSrc,  // Pointer to the source Flex video surface.
		IMvSurface  * in_pIVBISrc,    // Pointer to the source Flex VBI surface.
		IMvSurface  * in_pIVideoSrc2, // Pointer to the source Flex video surface.
		IMvSurface  * in_pIVBISrc2,   // Pointer to the source Flex VBI surface.
		IMvSurface  * io_pIDest,      // Pointer to the destination Flex surface.
		unsigned long in_ulIgnored    // IGNORED
		) = 0;

	//
	// Summary:
	//    Decodes the data in the source buffer into two YUV 8-bit field-based video buffers and two
	//    YUV 8-bit field-based VBI buffers. The decoder used is specified by the source buffer surface format. 
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_MODULE_BUSY, if thread re-entrance is detected. 
	//    - MV_E_INVALID_POINTER, if any pointer is invalid. 
	//    - MV_E_AVCONTENT_IN_USE, if the source surface is not ready to read. 
	//    - MV_E_INVALID_PARAMETER, if any of the Flex surface parameters are invalid according to 
	//      the type of operation. 
	// Remarks:
	//    - This call is asynchronous but the initialization (validation of parameters) is done in 
	//      the calling thread. 
	virtual HRESULT __stdcall DecompressFieldsVideoAndVbi
		(
		IMvSurface  * in_pISource,       // Pointer to the source Flex surface.
		IMvSurface  * io_pIVideoDest,    // Pointer to the video destination Flex surface.
		IMvSurface  * io_pIVBIDest,      // Pointer to the VBI destination Flex surface.
		IMvSurface  * io_pIVideoDest2,   // Pointer to the video destination Flex surface.
		IMvSurface  * io_pIVBIDest2,     // Pointer to the VBI destination Flex surface.
		unsigned long in_ulIgnored       // IGNORED
		) = 0;

	//
	// Summary:
	//    Decompresses frame and VBI information from a Group of Pictures (GOP).
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_MODULE_BUSY, if thread re-entrance is detected. 
	//    - MV_E_INVALID_POINTER, if any pointer is invalid. 
	//    - MV_E_AVCONTENT_IN_USE, if the source surface is not ready to read. 
	//    - MV_E_OPEN_GOP_NOT_SUPPORTED, if the flag "Close_GOP" in the GOP header is equal to 0. 
	//    - MV_E_INVALID_PARAMETER, if any of the Flex surface parameters are invalid, according to 
	//      the type of operation. 
	// Return value:
	//    - This call is asynchronous, but the initialization (validation of parameters) is performed in
	//      the calling thread. 
	virtual HRESULT __stdcall DecompressFrameAndVBIFromGroupOfPictures
		(
		IMvSurface                   * in_pIMvSrcGroupOfPictures,   // Pointer to a source Flex surface containing the 
                                                                  // compressed GOP data.
		IMvGroupOfPicturesDescriptor * in_pIMvSrcGroupOfPicturesDescriptor,  // Pointer to a compressed GOP data 
                                                                           // descriptor. The descriptor must match the 
                                                                           // GOP for which it was created.
		IMvSurface                   * in_pIMvSrcOpenGOP,  // Pointer to a source Flex surface containing the compressed 
                                                         // GOP data. This is the GOP that precedes 
		                                                   // pIMvSrcGroupOfPictures. It can be NULL if the 
		                                                   // current GOP is a closed GOP. There's no penalty for 
		                                                   // always passing the previous GOP.
		IMvGroupOfPicturesDescriptor * in_pIMvReferenceDescForOpenGOP, // Pointer to a compressed GOP data descriptor. 
                                                                     // The descriptor must match the GOP for which it 
		                                                               // was created, in_pIMvSrcOpenGOPReference for 
                                                                     // example. It can be NULL if the current GOP is 
                                                                     // a closed GOP. There's no penalty for always 
                                                                     // passing the previous GOP descriptor.
		unsigned long                  in_ulFramePosition, // Index of the frame to decompress from the GOP. This 
                                                         // parameter is based on the displayed order of the frames 
                                                         // from 0 to ulTotalNumberOfFrames. This value must be set 
                                                         // back to 0 at the beginning of each GOP.
		IMvSurface                   * in_pIMvSurfaceDst,  // Pointer to a destination Flex surface that will receive 
                                                         // the decompressed video data.
		IMvSurface                   * in_pIMvVBISurfaceDst,  // Pointer to a destination Flex surface that will receive 
                                                            // the decompressed VBI data.
		unsigned long                  in_ulIgnored        // IGNORED.
		) = 0;

	//
	// Summary:
	//    Decompresses field and VBI information from a Group of Pictures (GOP).
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_MODULE_BUSY, if thread re-entrance is detected. 
	//    - MV_E_INVALID_POINTER, if any pointer is invalid. 
	//    - MV_E_AVCONTENT_IN_USE, if the source surface is not ready to read. 
	//    - MV_E_OPEN_GOP_NOT_SUPPORTED, if the flag "Close_GOP" in the GOP header is equal to 0. 
	//    - MV_E_INVALID_PARAMETER, if any of the Flex surface parameters are invalid, according 
	//      to the type of operation. 
	// Remarks:
	//    - This call is asynchronous but the initialization (validation of parameters) is done in
	//      the calling thread. 
	virtual HRESULT __stdcall DecompressFieldsAndVBIFromGroupOfPictures
		(
		IMvSurface                   * in_pIMvSrcGroupOfPictures,   // Pointer to a source Flex surface containing the 
                                                                  // compressed GOP data.
		IMvGroupOfPicturesDescriptor * in_pIMvSrcGroupOfPicturesDescriptor,  // Pointer to a  compressed GOP data 
                                                                           // descriptor. The descriptor must match the 
		                                                                     // GOP for which it was created.
		IMvSurface                   * in_pIMvSrcOpenGOP,  // Pointer to a source Flex surface 
		                                                   // containing the compressed GOP data. This is the GOP 
		                                                   // that precedes pIMvSrcGroupOfPictures. It can be NULL if 
		                                                   // the current GOP is a closed GOP. There's no penalty 
		                                                   // for always passing the previous GOP.   
		IMvGroupOfPicturesDescriptor * in_pIMvReferenceDescForOpenGOP, // Pointer to a compressed GOP data descriptor. 
                                                                     // It must match the GOP for which it was created,
		                                                               // in_pIMvSrcOpenGOPReference for example. It can 
                                                                     // be NULL if the current GOP is a closed GOP. 
                                                                     // There's no penalty for always passing the 
                                                                     // previous GOP descriptor.
		unsigned long                  in_ulFramePosition, // Index of the frame to decompress from the GOP.  This 
                                                         // parameter is based on the displayed order of the frames 
                                                         // from 0 to ulTotalNumberOfFrames. This value must be set back 
		                                                   // to 0 at the beginning of each GOP.
		IMvSurface                   * in_pIMvSurfaceDst,  // Pointer to a destination Flex surface that will receive 
                                                         // the decompressed video data for the first field.
		IMvSurface                   * in_pIMvSurfaceDst2, // Pointer to a destination Flex surface that will receive 
                                                         // the decompressed video data for the second field.
		IMvSurface                   * in_pIMvVBISurfaceDst,  // Pointer to a destination Flex surface that will receive 
                                                            // the decompressed VBI data for the first field.
		IMvSurface                   * in_pIMvVBISurfaceDst2, // Pointer to a destination Flex surface that will receive 
                                                            // the decompressed VBI data for the second field.
		unsigned long                  in_ulIgnored        // IGNORED
		) = 0;
};

//DOM-IGNORE-BEGIN
//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Allows the user to use the codec to decompress data and apply a color correction effect.
// Remarks:
//    - This interface will be phased out of the Flex architecture on future release.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvEmbeddedCodec
: public IMvCodec
{
	//
	// Summary:
	//    This method decodes the data in the source buffer into one YUV 8-bit frame-based buffer 
	//    and applies a color correction effect.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_MODULE_BUSY, if thread re-entrance is detected. 
	//    - MV_E_INVALID_POINTER, if any pointer is invalid. 
	//    - MV_E_AVCONTENT_IN_USE, if the source surface is not ready to read. 
	//    - MV_E_INVALID_PARAMETER, if any of the Flex surface parameter is invalid according to the 
	//      type of operation. 
	// Remarks:
	//    - This call is asynchronous but the initialization (validation of parameters) is done in 
	//      the calling thread. 
	//    - The decoder used is specified by the surface format of the source buffer.
	virtual HRESULT __stdcall DecompressFrameFx
		(
		IMvSurface        * in_pIMvSurfaceSrc, // Pointer to the source Flex surface.
		IMvSurface        * in_pIMvSurfaceDst, // Pointer to the destination Flex surface.
		IMvEffectSettings * in_pIFxSettings,   // Pointer to the effect setting.
		unsigned long       in_ulIgnored       // IGNORED
		) = 0;

	//
	// Summary:
	//    This method decodes the data in the source buffer into two YUV 8-bit field-based buffers
	//    and applies a color correction effect (one different effect setting is applied to each 
	//    field).
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_MODULE_BUSY, if thread re-entrance is detected. 
	//    - MV_E_INVALID_POINTER, if any pointer is invalid. 
	//    - MV_E_AVCONTENT_IN_USE, if the source surface is not ready to read. 
	//    - MV_E_INVALID_PARAMETER, if any of the Flex surface parameters are invalid according to 
	//      the type of operation. 
	// Remarks:
	//    - The decoder used is specified by the surface format of the source buffer.
	//    - This call is asynchronous but the initialization (validation of parameters) is done in 
	//      the calling thread. 
	virtual HRESULT __stdcall DecompressFieldsFx
		(
		IMvSurface        * in_pIMvSurfaceSrc,    // Pointer to the source Flex surface.
		IMvSurface        * in_pIMvSurfaceDst,    // Pointer to the destination Flex surface first field.
		IMvSurface        * in_pIMvSurfaceDst2,   // Pointer to the destination Flex surface second field.
		IMvEffectSettings * in_pIFxSettings,      // Pointer to the effect setting first field.
		IMvEffectSettings * in_pIFxSettings2,     // Pointer to the effect setting second field.
		unsigned long       in_ulIgnored          // Thread pool identification.
		) = 0;

	virtual HRESULT __stdcall DecompressFrameFromGroupOfPicturesFX
		(
		IMvSurface                   * in_pIMvSrcGroupOfPictures,             
		IMvGroupOfPicturesDescriptor * in_pIMvSrcGroupOfPicturesDescriptor,   
		IMvSurface                   * in_pIMvSrcOpenGOP,                     
		IMvGroupOfPicturesDescriptor * in_pIMvReferenceDescForOpenGOP,    // previous GOP that contains reference frame 
                                                                        // for in_pIMvSrcGroupOfPicturesDescriptor
		unsigned long                  in_ulFramePosition,                    
		IMvSurface                   * in_pIMvSurfaceDst,                     
		IMvEffectSettings            * in_pIFxSettings,                       
		unsigned long                  in_ulIgnored                          
		) = 0;

	virtual HRESULT __stdcall DecompressFieldsFromGroupOfPicturesFX
		(
		IMvSurface                   * in_pIMvSrcGroupOfPictures,             
		IMvGroupOfPicturesDescriptor * in_pIMvSrcGroupOfPicturesDescriptor,   
		IMvSurface                   * in_pIMvSrcOpenGOP,                     
		IMvGroupOfPicturesDescriptor * in_pIMvReferenceDescForOpenGOP,    // previous GOP that contains reference frame 
                                                                        // for in_pIMvSrcGroupOfPicturesDescriptor
		unsigned long                  in_ulFramePosition,                    
		IMvSurface                   * in_pIMvSurfaceDst,                     
		IMvSurface                   * in_pIMvSurfaceDst2,                    
		IMvEffectSettings            * in_pIFxSettings,                       
		IMvEffectSettings            * in_pIFxSettings2,                      
		unsigned long                  in_ulIgnored                          
		) = 0;

};
//DOM-IGNORE-END

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Controls the composition of layers.
// Remarks:
//    - This interface supports the following QueryInterface: IID_IMvEffectSettingsPool; used to 
//      retrieve free effect settings. 
//
//////////////////////////////////////////////////////////////////////////
interface IMvCompositor
: public IUnknown
{
	//
	// Summary:
	//    This method generates the composition of layers. There is no background.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if one of the pointer's parameters is NULL. 
	//    - MV_E_FAIL, if failed. 
	// Remarks:
	//    - All sources, mattes, and destination surfaces must be in the same memory location. 
	//    - The compositor works with host, user data, or video memory. 
	//    - The layers in the parameter array in_apIInpustSurfaceArray are composed in an index of 
	//      increasing order. Index 0 is the bottom layer; index 1 is the layer to compose over 0;
	//      index 2 is the layer to compose over the results of the composition between layer 0 
	//      and 1. 
	//    - When in debug mode, the compositor will insure that all the surfaces are in the same 
	//      memory location. 
	virtual HRESULT __stdcall UpstreamCompose
		(
		IMvSurface           *io_pIOutputSurface,          // The output surface on which to render.
		unsigned long         in_ulLayerCount,             // The number of input surfaces passed in the
		                                                   // array to render the effect.
		IMvSurface           *in_apIInputSurfaceArray[],   // Array of input surfaces to compose.  The
		                                                   // array has in_ulLayerCount entries.
		IMvEffectSettings    *in_apICompositorSettings[],  // Array of compositor settings to use on each
		                                                   // layer. The array has in_ulLayerCount entries.
		unsigned long         in_ulIgnored
		) = 0;

	//
	// Summary:
	//    This method generates the composition of layers over a background. The background can be 
	//    another surface, or a color used to clear the output. The alpha channel output is opaque.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if one of the pointer's parameters is NULL. 
	//    - MV_E_FAIL, if failed. 
	// Remarks:
	//    - All sources, mattes, and destination surfaces must be in the same memory location. 
	//    - The compositor works with host, user data, or video memory. 
	//    - The layers in the parameter array in_apIInpustSurfaceArray are composed in an index of
	//      increasing order. Index 0 is the bottom layer; index 1 is the layer to compose over 0;
	//      index 2 is the layer to compose over the results of the composition between layer 0 and 1. 
	//    - When in debug mode, the compositor will insure that all the surfaces are in the same memory
	//      location. 
	virtual HRESULT __stdcall DownstreamCompose
		(
		IMvSurface           *io_pIOutputSurface,          // The output surface on which to render.
		unsigned long         in_ulLayerCount,             // The number of input surfaces passed in the
		                                                   // array to render the effect.
		IMvSurface           *in_apIInputSurfaceArray[],   // Array of input surfaces to compose.  The 
		                                                   // array has in_ulLayerCount entries.
		IMvEffectSettings    *in_apICompositorSettings[],  // Array of compositor settings to use on each
		                                                   // layer. The array has in_ulLayerCount entries.
		IMvSurface           *in_pIBackgroundSurface,      // The background surface to put in the output
		                                                   // surface (if requested).
		EMvColor              in_eColor,                   // Color used to clear the output surface (if requested).
		EMvBackgroundHandling in_eBackgroundHandling,      // Determines what to do with the background surface.
		unsigned long         in_ulIgnored                 // Ignored.
		) = 0;

};

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Allows calls to the the slow motion effect using field (frame) blending.
//
//////////////////////////////////////////////////////////////////////////
interface IMvSlowMotion
: public IUnknown
{
	//
	// Summary:
	//    Performs Slow Motion effect using Fields (Frame) Blending.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_MODULE_BUSY, if a call to SlowMotionBlend is made before the return from a current call.
	//    - MV_E_FAIL, if SlowMotionBlend cannot do the processing.
	//    - MV_E_NOT_READY_FOR_READ, if any of the sources are not ready for read.
	//    - MV_E_INVALID_POINTER, if a pointer is invalid.
	//    - MV_E_POINTER_NOT_ALIGNED, if any of the passed pointers are not aligned.
	//    - MV_E_INVALID_PARAMETER, if a parameter is not valid.
	// Remarks:
	//    - In all modes, all surfaces (sources and destination) must be of the same format.
	//    - In all modes, surfaces have the same full resolution.
	//    - In progressive mode, all surfaces have the same polarity: keMvPolarityInterlacedFieldsInAFrame
	//      or keMvPolarityProgressiveFrame
	//    - In none-progressive mode, all surfaces are different from progressive mode polarities.
	virtual HRESULT __stdcall SlowMotionBlend
		(
		IMvSurface *in_pSurface1In,         // Pointer to an IMvSurface, first field (frame) temporally.
		IMvSurface *in_pSurface2In,         // Pointer to an IMvSurface, second field (frame) temporally.
		IMvSurface *io_pSurfaceOut,         // Pointer to an IMvSurface, destination field (frame).
		float       in_fSlowMotionFactor,   // float value of the blending, between 1 and 0.
		unsigned long in_ulIgnored          // IGNORED
		) = 0;
};

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    DV Audio Deshuffle Context interface
//
//////////////////////////////////////////////////////////////////////////
interface IMvDVAudioDeshuffleContext 
: public IUnknown
{
	//
	// Summary:
	//    Resets the context to its initial state. You should reset the context when there are 
	//    discontinuities in the DV stream such as stop/pause, fast forward, etc.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_FAIL, if the call failed. 
	//
	virtual HRESULT __stdcall ResetContext() = 0;
};


//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Extracts audio from a DV frame and inserts audio channels into a video DV frame. The  
//    insertion function is useful when printing to a DV-1394 device.
// Remarks:
//    - When extracting (de-shuffling) audio channels, you need to get a context by calling 
//      GetDeshuffleContext(). Pass the context when you call Deshuffling(). 
//    - You can call ExtractChannelsSampleSize() before doing an extraction, 
//      for information about the audio in the DV source.
//    - ExtractChannelsSampleSize() needs a context as well, but you CANNOT use the same context as 
//      the one used for Deshuffling(); you must create a new one. Do not create it for each DV frame; use one 
//      context per device, or two if you call Deshuffling() only. 
//    - Use two contexts if you call ExtractChannelsSampleSize() and Deshuffling(). 
//    - Audio insertion does not need a context. 
//
//////////////////////////////////////////////////////////////////////////
interface IMvDVAudio
: public IUnknown
{
	//
	// Summary:
	//    Extracts the requested audio streams from an input DV frame and writes them to the output
	//    stereo buffers.
	// Description:
	//    This method can extract up to 4 stereo streams if they are present in the DV frame. The data
	//    returned is always 48 kHz, 16 bits. If the source is 32 kHz, it will be upsampled to 48 kHz,
	//    and if the audio is not locked (not genlocked), samples will be skipped or repeated to return
	//    the proper amount of audio samples to keep sync with video. Output buffers for channels not
	//    containing data WILL NOT be modified. 
	// 
	//    The output surfaces should have their size already set. Use ExtractChannelsSampleSize() to 
	//    know the number of samples that each channel is containing. This routine will not set the size
	//    on the output surfaces. This behavior was selected because the output surfaces will be re-used
	//    as inputs for other request (DirectShow oriented), usually before the actual execution is 
	//    completed, in which case the surface size must is already known and set.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_FAIL, if failed.  
	// Remarks:
	//    - Do not use the same context for ExtractChannelsSampleSize() and Deshuffle(), allocate a 
	//      different one for each of them (see GetDeshuffleContext()). 
	//    - The calls to Deshuffle() must be serialized in order to get proper re-sampling and re-locking
	//      of the audio material. You should call it with the DV frames in the proper order. The call for
	//      one frame should be completed before you call it for the next frame. This way the context will
	//     update properly between frames. 
	//
	virtual HRESULT __stdcall Deshuffle
		(
		IMvSurface                 * in_pSurface1In,          // Pointer to the interface of a compressed DV surface.
		IMvAudioSamples           ** pAudioSurface,           // Pointer to an array of 4 stereo audio samples buffer 
                                                            // interface. Pass a null surface if you don't want to 
                                                            // have the audio of this channel.
		IMvDVAudioDeshuffleContext * io_pIDeshuffleContext,   // Pointer to an interface of a deshuffle context. The 
                                                            // context content will be taken into account for the 
                                                            // processing of the current frame, and will be updated for 
                                                            // the next frame.
		unsigned long                in_ulIgnored             // Ignored
		) = 0;

	//
	// Summary:
	//    Retrieves the number of samples for each stereo audio channel of a DV frame (up to four).
	// Description:
	//    If the sample rate of the data in the DV frame is 32kHz, the routine will calculate the amount
	//    of samples after 48kHz re-sampling. If the data is not locked, the routine will apply 
	//    "locking out" rules and return the amount of locked samples that would be returned.
	//
	//    The number of samples returned are the same as the ones that the Deshuffle() method would 
	//    extract and return from the same DV frame, given the same initial context (io_pIDeshuffleContext).
	//    If a stereo channel does not contain any data, the number returned will be zero (0).
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_FAIL, if failed.  
	// Remarks:
	//    - Do not use the same context for ExtractChannelsSampleSize() and Deshuffle(), allocate a 
	//      different one for each of them (see GetDeshuffleContext()). 
	//    - The calls to ExtractChannelsSampleSize() must be serialized in order to get proper re-sampling
	//      and re-locking of the audio material. You should call it with the DV frames in the proper order.
	//      The call for one frame should be completed before you call it for the next frame. This way the 
	//      context will update properly between frames. 
	//
	virtual HRESULT __stdcall ExtractChannelsSampleSize
		(
		IMvSurface                 * pDVSurface,              // Pointer to the interface of a compressed DV surface.
		OUT ULONG                 ** ppChannelSize,           // Pointer to an array of 4 ULONG.
		IMvDVAudioDeshuffleContext * io_pIDeshuffleContext,   // Pointer to an interface of a deshuffle context. The 
                                                            // context content will be taken into account for the 
                                                            // processing of the current frame and will be updated
		                                                      // for the next frame. 
		unsigned long                in_ulIgnored             // Ignored.
		)=0;

	//
	// Summary:
	//    Retrieves a context to use with Deshuffle() or ExtractChannelsSampleSize().
	// Description:
	//    You should get two contexts for every DV stream you process, one for Deshuffle and one for
	//    ExtractChannelsSampleSize. This call allocates a new context object and returns the interface 
	//    of that context. It is the responsibility of the caller to release (pIContext->Release) the 
	//    object when it is not needed anymore. 
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_FAIL, if failed. 
	// Remarks:
	//    - The calling routine is responsible for releasing the context (pIContext->Release) when it
	//      is no longer needed. 
	//
	virtual HRESULT __stdcall GetDeshuffleContext
		(
		IMvDVAudioDeshuffleContext ** out_ppIDeshuffleContext,   // Pointer to a pointer of an interface
		                                                         // of a deshuffle context. 
		unsigned long                 in_ulIgnored               // Ignored
		) = 0;

	//
	// Summary:
	//    Resets the context to its initial state.
	// Description:
	//    You should reset the context when there are discontinuities in the DV stream such as stop/pause,
	//    fast forward, etc. You can also use the context interface directly (IMvDVAudioDeshuffleContext)
	//    with the ResetContext() method.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_FAIL, if failed.   
	//
	virtual HRESULT __stdcall ResetDeshuffleContext
		(
		IMvDVAudioDeshuffleContext * in_pIDeshuffleContext,   // Pointer to an interface of a deshuffle context.
		unsigned long                in_ulIgnored             // Ignored.
		) = 0;

	//
	// Summary:
	//    Inserts one or more audio channels into a DV frame.
	// Description:
	//    The number of audio samples must follow the lock sequence in NTSC, and 1920 samples in PAL.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_FAIL, frame rate is not supported.  
	// Remarks:
	//    - The frame rate of the video surface determines how to do the insertion (NTSC or PAL). 
	//
	virtual HRESULT __stdcall InsertAudio   
		(
		IMvSurface      * in_pVideo,     // Pointer to a video ImvSurface where the audio need be inserted. 
		IMvAudioSamples * in_apAudio[4],	// Array of audio surface. Each of the four channels contains two fields. If 
                                       // a channel is not used, the pointer must be null for both fields.
		IMvSurface      * out_pVideo,    // Pointer to the video ImvSurface that will receive data with audio in it.
		unsigned long	   in_ulIgnored   // Ignored.
		) = 0;
};


//////////////////////////////////////////////////////////////////////////
// DOM-IGNORE-BEGIN
// Use this service to set/get extra information for a surface
//
interface IMvFrameProperties : public IUnknown
{
	// Set extra information for the surface
	virtual HRESULT __stdcall Set3_2Pulldown(
		IMvSurface *            in_pISurface, 
		SMvFrameExtraInfo&      in_refsFrameProperties,
		unsigned long	         in_ulIgnored
		) = 0;

	// Get extra information for the surface
	virtual HRESULT __stdcall Get3_2Pulldown(
		IMvSurface *            in_pISurface, 
		SMvFrameExtraInfo *     io_prefsFrameProperties,
		unsigned long	         in_ulIgnored
		) = 0;

	// Set Aspect Ratio
	virtual HRESULT __stdcall SetAspectRatio(
		IMvSurface *            in_pISurface, 
		EMvAspectRatio          in_eAspectRatio,
		unsigned long	         in_ulIgnored
		) = 0;

	// Get Aspect Ratio, returns Invalid if there's no information in the frame
	virtual HRESULT __stdcall GetAspectRatio(
		IMvSurface *            in_pISurface, 
		EMvAspectRatio *        out_peAspectRatio,
		unsigned long	         in_ulIgnored
		) = 0;
};
// DOM-IGNORE-END

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Controls the rendering of an effect.
// Remarks:
//    This interface supports the following QueryInterfaces:
//       - IID_IMvEffectSettingsPool:To retrieve a free effect settings. 
//       - IID_IMvGFXSurfaceEnumerator:To Enumerate GFX surfaces required by the effect. 
//
//////////////////////////////////////////////////////////////////////////
interface IMvEffect
: public IUnknown
{
	//
	// Summary:
	//    Requests the effect to perform an upstream filter operation.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if one of the pointer's parameters is NULL. 
	//    - MV_E_FAIL, if failed. 
	//    - MV_E_NO_GFX_PROVIDED, if the effect did not receive a valid pointer in the in_pIEffectPattern
	//      parameters. 
	// Remarks:
	//    - When in debug mode, the effect's abstraction layer will ensure that all the surfaces are in
	//      the same memory location. 
	//
	virtual HRESULT __stdcall UpstreamFilter
		(
		IMvSurface        * io_pIOutputSurface,         // The output surface on which to render.
		unsigned long       in_ulInputSurfaceCount,     // The number of input surfaces passed in the
		                                                // array to render the effect.
		IMvSurface        * in_apIInputSurfaceArray[],  // The array pointer in which to retrieve the input surface.  
                                                      // The array has in_ulInputSurfaceCount entries.
		IMvEffectSettings * in_pIEffectSettings,        // Pointer to the effect settings necessary to render the effect.
		IMvContainer      * in_pIEffectPattern,         // Pointer to complementary data that the effect needs.
		unsigned long       in_ulThreadPoolIndex        // Determines which thread pool to use.
		) = 0;


	//
	// Summary:
	//    Requests the effect to perform an upstream transition operation.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if one of the pointer's parameters is NULL. 
	//    - MV_E_FAIL,  if failed. 
	//    - MV_E_NO_GFX_PROVIDED, if the effect did not receive a valid pointer in the in_pIEffectPattern 
	//      parameters. 
	// Remarks:
	//    - When in debug mode, the effect's abstraction layer will insure that all the surfaces are in
	//      the same memory location. 
	//
	virtual HRESULT __stdcall UpstreamTransition
		(
		IMvSurface        * io_pIOutputSurface,   // The output surface on which to render.
		IMvSurface        * in_pISurfaceA,        // The outgoing surface used as an input image in the transition.
		IMvSurface        * in_pISurfaceB,        // The incoming surface used as an input image in the transition.
		IMvEffectSettings * in_pIEffectSettings,  // Pointer to the effect settings necessary to render the effect.
		IMvContainer      * in_pIEffectPattern,   // Pointer to complementary data that the effect needs.
		unsigned long       in_ulThreadPoolIndex  // Determines which thread pool to use.
		) = 0;

	//
	// Summary:
	//    Requests the effect to perform a downstream filter operation.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if one of the pointer's parameters is NULL. 
	//    - MV_E_FAIL, if failed. 
	//    - MV_E_NO_GFX_PROVIDED, if the effect did not receive a valid pointer in the in_pIEffectPattern
	//      parameters. 
	// Remarks:
	//    - When in debug mode, the effect's abstraction layer will insure that all the surfaces are in 
	//      the same memory location. 
	virtual HRESULT __stdcall DownstreamFilter
		(
		IMvSurface          * io_pIOutputSurface,          // The output surface on which to render.
		unsigned long         in_ulInputSurfaceCount,      // The number of input surfaces passed in
		                                                   // the array to render the effect.
		IMvSurface          * in_apIInputSurfaceArray[],   // The array pointer from which to retrieve the input surface.
                                                         // The array has in_ulInputSurfaceCount entries.
		IMvEffectSettings   * in_pIEffectSettings,         // Pointer to the effect settings necessary
		                                                   // to render the effect.
		IMvContainer        * in_pIEffectPattern,          // Pointer to complementary data that the effect needs.
		IMvSurface          * in_pIBackgroundSurface,      // The background surface to put in the
		                                                   // output surface (if requested).
		EMvColor              in_eColor,                   // Color used to clear the output surface (if requested).
		EMvBackgroundHandling in_eBackgroundHandling,      // Determines what to do with the background surface.
		IMvEffectSettings   * in_pICompositorSettings,     // Compositor settings to use when blending over the background.
		unsigned long         in_ulThreadPoolIndex         // Determines which thread pool to use.
		) = 0;

	//
	// Summary:
	//    Requests the effect to perform a downstream transition operation.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if one of the pointer's parameters is NULL. 
	//    - MV_E_FAIL, if failed. 
	//    - MV_E_NO_GFX_PROVIDED, if the effect did not receive a valid pointer in the in_pIEffectPattern
	//      parameters. 
	// Remarks:
	//    - When in debug mode, the effect abstraction layer will insure that all the surfaces are in
	//      the same memory location. 
	virtual HRESULT __stdcall DownstreamTransition
		(
		IMvSurface          * io_pIOutputSurface,       // The output surface in which to render.
		IMvSurface          * in_pISurfaceA,            // The outgoing surface used as an input image in the transition.
		IMvSurface          * in_pISurfaceB,            // The incoming surface used as an input image in the transition.
		IMvEffectSettings   * in_pIEffectSettings,      // Pointer to the effect settings necessary to render the effect.
		IMvContainer        * in_pIEffectPattern,       // Pointer to complementary data that the effect needs.
		IMvSurface          * in_pIBackgroundSurface,   // The background surface to put in the output
		                                                // surface (if requested).
		EMvColor              in_eColor,                // Color used to clear the output surface (if requested).
		EMvBackgroundHandling in_eBackgroundHandling,   // Determines what to do with the background surface.
		IMvEffectSettings   * in_pICompositorSettings,  // Compositor settings to use when blending over the background.
		unsigned long         in_ulThreadPoolIndex      // Determines which thread pool to use.
		) = 0;

	//
	// Summary:
	//    Generates the GFX effect data that is ready to be written into a file.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER,if one of the pointer's parameters is NULL. 
	//    - MV_E_FAIL, if failed. 
	// Remarks:
	//    - The objects returned in the output container must be destroyed/released by the caller when 
	//      it has finished processing the output data. 
	virtual HRESULT __stdcall PreprocessEffectPattern
		(
		IMvContainer  * in_pInData,   // The container of input data.
		IMvContainer ** out_ppOutData // The container of output data.
		) = 0;

	//
	// Summary:
	//    Returns the effect capabilities.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if one of the pointer's parameters is NULL. 
	//    - MV_E_INVALID_STRUCTURE_SIZE, if the size of the structure is invalid. 
	virtual HRESULT __stdcall GetCapabilities
		(
		SMvEffectCapabilities * io_pCapabilities  // Pointer to an effect capabilities structure.
		) = 0;

};

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Controls all the parameters and services of the X.scaler converter module.
// Remarks:
//    To have access to all the functionality of this interface, the input and output standard must
//    be set first. 
//
//////////////////////////////////////////////////////////////////////////
interface IMvXScalerHD : public IUnknown
{
	//
	// Summary:
	//    Validates and sets the input and output standards of the X.scaler converter module.
	// Return value:
	//    - Returns an error if the standards are invalid or not supported.
	// Remarks:
	//    - This method will program the X.scaler hardware and it requires a stable source clock 
	//      (genlock or input). It should be called at least one second after the source have been 
	//      programmed. If in_eSynchronizationSource is set to genlock, it means 
	//      IMvInputOutputIndependant::ControlGenlockResolution(), IMvGenlockControl::ControlGenlockSource()
	//      and IMvGenlockControl::ControlGenlock(). If in_eSynchronizationSource is set to video 
	//      input, it means IMvInputOutputIndependant::ControlVideoCaptureResolution().
	//    - This method has internal wait time required for the X.scaler hardware clocks to stabilize.
	//      It blocks the calling thread for at least 300 milliseconds before returning. You should 
	//      not call the IMvXScalerHD::Transcode() method until it is completed.
	virtual HRESULT __stdcall SetStandards(
		SMvResolutionInfo       *in_psInputStandard,       // Input standard.
		SMvResolutionInfo       *in_psOutputStandard,      // Output standard.
		EMvSynchronizationSource in_eSynchronizationSource // Selects the synchronization source of the
		                                                   // X.scaler hardware. Usually, you must
		                                                   // select keSynchronizationSourceGenlock
		                                                   // if the video source is a file and 
		                                                   // keSynchronizationSourceVideoInputChannelA
		                                                   // or keSynchronizationSourceVideoInputChannelB
		                                                   // if the video source is a video input.
		) = 0;

	//
	// Summary:
	//    Retrieves the preroll needed before the first buffer is programmed into the X.scaler converter module.
	// Return value:
	//    - An error is returned if the input/output standard has not been set yet
	virtual HRESULT __stdcall GetPreroll(
		uint64_t *out_pui64PrerollNano   // The preroll is returned in nanotime based on the input standard.
		) = 0;

	//
	// Summary:
	//    Retrieves the propagation delay needed before a buffer passes through the entire X.scaler chipset.
	// Return value:
	//    - An error is returned if the input/output standard has not been set yet.
	virtual HRESULT __stdcall GetPropagationDelay(
		uint64_t *out_pui64PropagationDelayNano   // The propagation delay is returned in nanotime 
		                                          // based on the input standard.
		) = 0;

	//
	// Summary:
	//    Cancels all input/output buffers that have not been processed yet.
	// Return value:
	//    - Returns an error if the command failed.
	virtual HRESULT __stdcall CancelAll() = 0;

	//
	// Summary:
	//    Scales the data of the input rectangle from the input surface to the output rectangle of 
	//    the output surface using the X.scaler. 
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters. 
	virtual HRESULT __stdcall Transcode(
		IMvSurface         * in_pIInputVideoSurface,    // Input buffer to send to the X.scaler.
		IMvSurface         * in_pIOutputVideoSurface,   // Output buffer that is the resulting scaled buffer.
		SMvRect            * in_psInputRect,            // Rectangle corresponding to the portion of 
		                                                // the active input video to be processed.
		SMvRect            * in_psOutputRect,           // Rectangle corresponding to the portion of the active output 
                                                      // video used to display the scaled video.
		SMvBackgroundColor * in_psBackgroundColor       // Background color to fill the portion of the active output 
                                                      // video that is outside the output rectangle
		) = 0;

	//
	// Summary:
	//    Sets the X.scaler processing parameters. 
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	// Remarks:
	//    - This method should be called after the  IMvXScalerHD::SetStandards() method, which resets 
	//      processing parameters to default.
	//    - The default value for ulNoiseReduction is 0 (disabled).
	//    - The default value for ulDetailEnh is 0 (disabled).
	//    - The default value for eFilterSelect is keMvFilterSelectNormal.
	virtual HRESULT __stdcall SetXScalerParameters(
		SMvXScalerParameters *in_psXScalerParameters    // Specifies the processing parameters.
		) = 0;
};

// DOM-IGNORE-BEGIN
interface IMvLQScaler
: public IUnknown
{
};
// DOM-IGNORE-END

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Controls a video capture device. 
// Remarks:
//    - This interface can be obtained from the IMvInputOutputIndependent or IMvInputOutput
//      interface, and is only available after the resolution is determined.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvVideoCaptureControl : public IUnknown
{
	//
	// Summary:
	//    Provides information about the I/O device that the IMvVideoCaptureControl interface is
	//    controlling.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetIODeviceRelation
		(
		unsigned int* out_puiIODeviceIndex  // Returns the IODevice index from which the capture comes.
		) = 0;

	//
	// Summary:
	//    Captures a video surface from a live input.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall CaptureBuffer
		(
		IMvSurface* io_pICaptureSurface  // The surface to capture into.
		) = 0;

	//
	// Summary:
	//    Captures a video surface and a vertical blanking interval (VBI) surface from a live input.
	// Return value:
	//    Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall CaptureVideoAndVbiBuffers
		(
		IMvSurface* io_pICaptureVideoSurface,  // The video surface to capture into.
		IMvSurface* io_pICaptureVBISurface     // The Vbi surface to capture into.
		) = 0;

	//
	// Summary:
	//    Set the vbi parameters at the input before Vbi is being captured.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall SetVbiSettings
		(
		SMvVbiSettings* in_psVbiSettings  
		) = 0;

	//
	// Summary:
	//    Cancels, signals, and flushes all previously queued video surfaces from the waiting queues.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall CancelAll() = 0;

	//
	// Summary:
	//    Retrieves the capture preroll time.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetPreroll
		(
		uint64_t* out_pui64Preroll   // Returns the preroll in nanotime (100ns).
		) = 0;

	//
	// Summary:
	//    Controls the hardware video capture procamps.
	// Remarks:
	//    This method is supported only for X.mio2.	
	// Description:
	//    <table>
	//    Parameter  Valid range           Granularity    Default value  Dependency 
	//    ---------  --------------------  -------------  -------------  ----------
	//    %PAR0%     [-92.5, +92.5] IRE    0.0963542      0.0            None 
	//    %PAR1%     [0.0, +2.0[           0.0009765625   1.0            None 
	//    %PAR2%     [0.0, +360.0] degree  1.0            0.0            None 
	//    %PAR3%     [0.0, +2.0[           0.0009765625   1.0            None 
	//    </table>
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall SetCaptureProcamps
		(
		double in_dBrightness,  // Relative offset to the luminance component of the incoming video. 
		double in_dLumaGain,    // Gain on the luminance component of the incoming video.
		double in_dHue,         // Color shift on the chrominance component of the incoming video.
		double in_dSaturation   // Gain on the chrominance component of the incoming video.
		) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Controls a video playback device. 
// Remarks:
//    - This interface is obtained from the IMvInputOutput or IMvInputOutputIndependent interface, 
//      and is only available after that the resolution is determined.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvVideoPlaybackControl : public IUnknown
{
	//
	// Summary:
	//    Provides information about the I/O device that the IMvVideoPlaybackControl interface is 
	//    controlling.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetIODeviceRelation
		(
		unsigned int* out_puiIODeviceIndex  // Returns the I/O device index from which the capture comes.
		) = 0;

	//
	// Summary:
	//    Displays a video field at the requested time.
	// Description:
	//    The video surface is put in a queue until it is ready to be displayed.
	//    - A RegisterForRead operation is performed on the surface to determine when it is ready to read.
	//    - A CompleteReadOperation is performed when the image is no longer displayed.
	//    - A video surface with an error cannot be displayed.
	//    - The video surface is allocated in local memory.
	//    - If the surface is ready after its display time, it is put in error mode and released. 
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	//
	virtual HRESULT __stdcall PlayBuffer
		(
		IMvSurface* io_pIPlaybackSurface    // Pointer to the IMvSurface interface containing the surface from which to play back.
		) = 0;

	//
	// Summary:
	//    Displays a video field at the requested time.
	// Description:
	//    The video and VBI surfaces are put in a queue until they are ready to be displayed.
	//    - A RegisterForRead operation is performed on the surface to determine when it is ready to read.
	//    - A CompleteReadOperation is performed when the image is no longer displayed.
	//    - A video surface with an error cannot be displayed.
	//    - The video surface is allocated in local memory.
	//    - If the surface is ready after its display time, it is put in error mode and released. 
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall PlayVideoAndVbiBuffers
		(
		IMvSurface* io_pIPlaybackVideoSurface, // Pointer to the IMvSurface interface containing the video surface to play back.
		IMvSurface* io_pIPlaybackVBISurface    // Pointer to the IMvSurface interface containing the VBI surface to play back.
		) = 0;

	//
	// Summary:
	//    Sets the VBI parameters at the output before VBI is being captured.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall SetVbiSettings
		(
		SMvVbiSettings* in_psVbiSettings    // Pointer to the SMvVbiSettings structure, which returns the value of the VBI starting line
                                          // and the total number of lines for both fields.
		) = 0;

	//
	// Summary:
	//    Releases all the images that have been previously queued for display. 
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
   // Remarks:
   //    - All the video surfaces will receive a read completion confirmation with an error. 
   //    - The video output is blacked out.
	virtual HRESULT __stdcall CancelAll() = 0;

	//
	// Summary:
	//    Retrieves the playback preroll time.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters. 
	virtual HRESULT __stdcall GetPreroll
		(
		uint64_t* out_pui64Preroll    // Returns the preroll in nanotime.
		) = 0;

	//
	// Summary:
	//    Cancels all the pending video surfaces from the requested time. 
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
   // Remarks:
   //    - The last video surface displayed is repeated following the still mode.
	virtual HRESULT __stdcall CancelFrom
		(
		uint64_t in_ui64Time    // Specifies the time in nanotime (100ns) to start canceling queued
		// video surfaces.
		) = 0;

	//
	// Summary:
	//    Sets the still mode of the output module.
	// Description:
	//    The still mode can be field-based or frame-based. <p> If it is field-based, the last images are 
	//    repeated in both output fields. The last video surface is not released until another image
	//    is sent to the output or until a full cancel (CanelAll()) is received. <p> If it is frame-based,
	//    the last two images are repeated, one for each field. The last surfaces are not released 
	//    until another image is sent to the output or until a full cancel (CanelAll()) is received.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall SetStillMode
		(
		EMvStillMode in_eStillMode,   // Specifies if the output should repeat one field (valid if the resolution is 
                                    // interlaced) or both fields / the entire frame (valid if the resolution is 
                                    // progressive or interlaced).
		uint64_t     in_ui64Time      // Specifies the time in nanotime (100ns) at which the command is to be executed. 
		                              // 0 means immediate. When passing a time > 0 the time should be either present or
                                      // future, else an error is returned.
		) = 0;

	//
	// Summary:
	//    Returns the notification events supplied by the video play back.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.

	virtual HRESULT __stdcall GetNotificationEvents
		(
		SMvVideoPlaybackNotifications *io_psNotifications  // Specifies the notification to monitor in order to observe 
                                                         // the behavior of the video output engine.
		) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Controls a serial playback device. 
// Remarks:
//    - This interface is obtained from the IMvInputOutputIndependent interface, 
//      and is only available after that the resolution is determined.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSerialPlaybackControl : public IUnknown
{
	//
	// Summary:
	//    Provides information about the I/O device that the IMvSerialPlaybackControl interface is 
	//    controlling.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetIODeviceRelation
		(
		unsigned int* out_puiIODeviceIndex  // Returns the IODevice index from which the playback comes.
		) = 0;

	//
	// Summary:
	//    Play a data buffer at the requested time.
	// Description:
	//    The data surface is put in a queue until it is ready to be played.
	//    - A RegisterForRead operation is performed on the surface to determine when it is ready to read.
	//    - A CompleteReadOperation is performed when the buffer is no longer displayed.
	//    - A data surface with an error cannot be played.
	//    - The data surface is allocated in local memory.
	//    - If the surface is ready after its display time, it is put in error mode and released. 
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	//
	virtual HRESULT __stdcall PlayBuffer
		(
		IMvSurface* io_pIPlaybackSurface,   // The surface from which to play back.
		uint64_t    in_ui64BufferDuration   // Specifies the duration on which the transmission of the buffer must be
                                          // spread out in nanotime
		) = 0;

	//
	// Summary:
	//    Releases all the buffers that have been previously queued for play out. All the data 
	//    surfaces will receive a read completion confirmation with an error. The serial video output 
	//    transmits NULL characters.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall CancelAll() = 0;

	//
	// Summary:
	//    Retrieves the playback preroll time.
	// Return value:
	//    - Returns an error if the command failed or if the parameters are incorrect. 
	virtual HRESULT __stdcall GetPreroll
		(
		uint64_t* out_pui64Preroll    // Returns the preroll in nanotime.
		) = 0;

};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Controls an audio capture device.
// Remarks:
//    This interface can be obtained from the IMvInputOutputIndependent or IMvInputOutput interface,
//    and is only available after the resolution is determined. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvAudioCaptureControl : public IUnknown
{
	//
	// Summary:
	//    Provides information about the I/O device that the IMvAudioCaptureControl interface is 
	//    controlling.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters. 
	virtual HRESULT __stdcall GetIODeviceRelation
		(
		unsigned int* out_puiIODeviceIndex  // Returns the IODevice index from which the capture comes.
		) = 0;

	//
	// Summary:
	//    Captures an audio sample buffer at a specific time (time stamp mode) or as soon at possible 
	//    (immediate mode).
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters. 
	virtual HRESULT __stdcall CaptureBuffer
		(
		IMvAudioSamples* io_pICaptureSample    // The buffer to capture to.
		) = 0;

	//
	// Summary:
	//    Cancels a capture that's already started. All previously queued audio sample buffers are 
	//    canceled, signaled, and flushed from the waiting queues.
	// Return value:
	//    - Returns an error if the command failed. 
	virtual HRESULT __stdcall CancelAll() = 0;

	//
	// Summary:
	//    Retrieves the capture preroll time.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters. 
	virtual HRESULT __stdcall GetPreroll
		(
		uint64_t* out_pui64Preroll    // Returns the preroll in nanotime.
		) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Controls an audio playback device.
// Remarks:
//    - This interface is obtained from the IMvInputOutputIndependent or IMvInputOutput interface, 
//      and is only available after that the resolution is determined. 
//    - There are no methods to make the relation with an I/O device for the audio play back since 
//      all playback channels are routed in every I/O device. 
//////////////////////////////////////////////////////////////////////////////////
interface IMvAudioPlaybackControl : public IUnknown
{
	//
	// Summary:
	//    Adds an audio sample buffer to play at the requested time (time stamp mode) or to play as 
	//    soon as possible (immediate mode). 
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters. 
	virtual HRESULT __stdcall PlayBuffer
		(
		IMvAudioSamples* io_pIPlaybackSample   // The audio sample buffer to play from.
		) = 0;

	//
	// Summary:
	//    Cancels a playback and releases all the audio sample buffers that have been previously 
	//    queued to play.
	// Return value:
	//    - Returns an error if the command failed. 
	virtual HRESULT __stdcall CancelAll() = 0;

	//
	// Summary:
	//    Retrieves the playback preroll time.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters. 
	virtual HRESULT __stdcall GetPreroll
		(
		uint64_t* out_pui64Preroll    // Returns the preroll in nanotime.
		) = 0;

	//
	// Summary:
	//    Cancels all the pending audio sample buffers FROM the requested time.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters. 
	virtual HRESULT __stdcall CancelFrom
		(
		uint64_t in_ui64Time    // Specifies the time in nanotime (100ns) to start canceling queued 
		                        // audio sample buffers.
		) = 0;

	//
	// Summary:
	//    Returns the notifications events supplied by the audio playback.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters. 
	virtual HRESULT __stdcall GetSilenceNotificationEvents
		(
		SMvAudioPlaybackNotifications *io_psNotifications  // Specifies the notification event to monitor in order to 
                                                         // observe the behavior of the audio output engine.
		) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Responsible for initializating, enumerating, and defining the resolution of audio and 
//    video input/output services. 
// Remarks:
//    - For the legacy X.io card only.
//    - This interface must be initialized before it is used. The initialization is not public, 
//      meaning that the interface must be obtained from the IMvFlexEngine interface.
//    - A call must be made to the ControlResolutions() method before the user application can 
//      access and use the following methods: GetGenlockInterface(), GetIODeviceInterface(), 
//      GetVideoCaptureInterface(), GetVideoPlaybackInterface(), GetAudioCaptureInterface(), 
//      GetAudioPlaybackInterface(). 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvInputOutput : public IUnknown
{
	//
	// Summary:
	//    Retrieves all input/output devices. This enumerated information is used by other methods to
	//    get specific controls. The structure that's passed must be allocated and initialized by the 
	//    caller. It is then filled by the call.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetDeviceCount
		(
		SMvDeviceCount* io_psDeviceCount // Returns all needed information on audio and video input and output devices.
		) = 0;

	//
	// Summary:
	//    Retrieves all available audio and video channels. This enumerated information is used by 
	//    other methods to get specific controls. The parameters must be allocated by the caller using
	//    the GetDeviceCount() method.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetAudioVideoChannels
		(
		EMvVideoIOChannel*			io_peVideoCaptureChannel,        // An array to contain all video capture channels. 
                                                                  // The array must be allocated by the user. 
		unsigned int 					in_uiVideoCaptureChannelCount,   // Specifies the count of the structures in the array 
                                                                  // of the previous parameter.
		EMvVideoIOChannel*			io_peVideoPlaybackChannel,       // An array to contain all video playback channels. 
                                                                  // The array must be allocated by the user.
		unsigned int 					in_uiVideoPlaybackChannelCount,  // Specifies the count of structures in the array of 
                                                                  // the previous parameter.
		EMvAudioCaptureChannel*		io_peAudioCaptureChannel,        // An array to contain all audio capture channels. 
                                                                  // The array must be allocated by the user.
		unsigned int 					in_uiAudioCaptureChannelCount,   // Specifies the count of structures in the array of 
                                                                  // the previous parameter.
		EMvAudioPlaybackChannel*	io_peAudioPlaybackChannel,       // An array to contain all audio playback channels. 
                                                                  // The array must be allocated by the user.
		unsigned int 					in_uiAudioPlaybackChannelCount   // Specifies the count of structures in the array of 
                                                                  // the previous parameter.
		) = 0;

	//
	// Summary:
	//    Validates a combination of resolutions and determines whether the low-level drivers can be 
	//    changed without having to release them and the IMvInputOutput interface.
	// Return value:
	//    - Returns success if the passed resolutions are valid and if the drivers can be changed. 
	//    - Returns unsuccessful if one of the parameters above are not valid.
	virtual HRESULT __stdcall CanSetResolutions
		(
		SMvInputOutputResolutions  in_asInputOutputResolutions[],      // An array of resolutions to validate to set all 
		                                                               // input/output devices.
		unsigned int               in_uiInputOutputResolutionsCount,   // Specifies the count of structures in the array 
		                                                               // of the first parameter.
		SMvResolutionInfo*         in_psGenlockResolution,             // Specifies the genlock resolution to validate.
		unsigned int               in_uiGenlockMasterIODeviceIndex,    // Specifies which IODevice is the genlock master 
                                                                     // (zero based index).
		unsigned int               in_uiAudioCaptureIODeviceIndex,     // Specifies from which IODevice the audio is 
                                                                     // captured (zero based index).
		unsigned int               in_uiAudioSyncSourceIODeviceIndex   // Specifies which IODevice is the source for 
                                                                     // synchronizing the audio capture (zero based index).
		) = 0;

	//
	// Summary:
	//    Controls the input and output resolutions of all the IODevices connected to the the system.
	//    The user application must validate the resolution combinations by calling the 
	//    CanSetResolutions() method before changing the default or current resolutions.
	// Return value:
	//    - Returns success if the passed resolutions are valid and if the drivers can be changed. 
	//    - Returns unsuccessful if one of the parameters above are not valid.
	virtual HRESULT __stdcall ControlResolutions
		(
		EMvIOCommand               in_eIOCommand,                      // Specifies the command that describes what to 
                                                                     // do with the parameters. The keIOCommandGetRange 
                                                                     // parameter is not supported for this call.
		SMvInputOutputResolutions  io_asInputOutputResolutions[],      // An array of resolutions to set all input/output 
		                                                               // devices. The array must be allocated and 
                                                                     // initialized by the user application.
		                                                               // On a set command the information is extracted 
		                                                               // from the array and on a get command the 
                                                                     // information is inserted into the array.
		unsigned int               in_uiInputOutputResolutionsCount,   // Specifies the count of  structures in the array
		                                                               // of the second parameter.
		SMvResolutionInfo*         io_psGenlockResolution,             // Specifies the genlock resolution.
		unsigned int*              io_puiGenlockMasterIODeviceIndex,   // Specifies which IODevice is the genlock master 
                                                                     // (zero based index).
		unsigned int*              io_puiAudioCaptureIODeviceIndex,    // Specifies from which IODevice the audio is 
                                                                     // captured (zero based index).
		unsigned int*              io_puiAudioSyncSourceIODeviceIndex  // Specifies which IODevice is the source for 
                                                                     // synchronizing the audio capture (zero based 
                                                                     // index).
		) = 0;

	//
	// Summary:
	//    Returns descriptions for the passed IODevice index in order to determine what resolutions
	//    are available on the IODevice.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetIODeviceDescription
		(
		unsigned int    in_uiIODeviceIndex,          // The IODevice zero based index from which to get the description.
		char          * out_szIODeviceDescription,   // Returns a string describing the IODevice.
		EMvIODeviceID * out_eIODeviceId              // Returns an enumeration that is the IODevice ID.
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvGenlockControl interface.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetGenlockInterface
		(
		IMvGenlockControl** out_ppIGenlockControl // Returns a pointer to the IMvGenlockControl (master genlock control) 
                                                // interface. See the IMvInputOutput::ControlResolutions method for 
		                                          // information on setting the master genlock.
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvIODeviceControl interface.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetIODeviceInterface
		(
		unsigned int in_uiIODeviceIndex,          // Gives the IODevice zero based index from which to get the interface.
		IMvIODeviceControl** out_ppIIODeviceControl  // Returns a pointer to the IMvIODeviceControl interface.
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvVideoCaptureControl interface.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetVideoCaptureInterface
		(
		unsigned int             in_uiVideoCaptureDeviceIndex,   // Gives the video capture zero based 
		                                                         // index from which to get the interface.
		IMvVideoCaptureControl** out_ppIVideoCaptureControl      // Returns a pointer to the 
                                                         		// IMvVideoCaptureControl interface.
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvAudioPlaybackControl interface.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetVideoPlaybackInterface
		(
		unsigned int               in_uiVideoPlaybackDeviceIndex,   // Gives the audio playback zero based index from 
                                                                  // which to get the interface.
		IMvVideoPlaybackControl ** out_ppIVideoPlaybackControl      // Returns a pointer to the IMvAudioPlaybackControl 
                                                                  // interface.
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvAudioCaptureControl interface.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetAudioCaptureInterface
		(
		unsigned int              in_uiAudioCaptureDeviceIndex,  // Gives the audio capture zero based index from which 
                                                               // to get interface.
		IMvAudioCaptureControl ** out_ppIAudioCaptureControl     // Returns a pointer to IMvAudioCaptureControl interface.
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvVideoPlaybackControl interface.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetAudioPlaybackInterface
		(
		unsigned int              in_uiAudioPlaybackDeviceIndex, // Gives the video playback zero based
		                                                         // index from which to get the interface.
		IMvAudioPlaybackControl** out_ppIAudioPlaybackControl    // Returns a pointer to the
		                                                         // IMvVideoPlaybackControl interface.
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvAudioVoiceOverMixer interface.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetAudioVoiceOverMixerInterface
		(
		unsigned int                     in_uiAudioVoiceOverMixerDeviceIndex,   // Gives the audio voice over mixer zero 
                                                                              // based index from which to get interface.
		IMvAudioVoiceOverMixerControl ** out_ppIAudioVoiceOverMixerControl      // Returns a pointer to the
		                                                                        // IMvAudioVoiceOverMixerControl interface.
		) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Responsible for initializating, enumerating, and defining the resolution of audio and 
//    video input/output services for a DSX card.
// Description:
//    This interface is different from the IMvInputOutput interface (used for the legacy X.io card) 
//    in that it provides services to independently control the resolution of the input and output channels.
// Remarks:
//    - This interface must be initialized before it is used. The initialization is not public, 
//      meaning that the interface must be obtained from the IMvFlexEngine interface. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvInputOutputIndependent : public IUnknown
{
	//
	// Summary:
	//    This enumerated information is used by other methods to get specific controls. The 
	//    structure that's passed must be allocated and initialized by the caller. It is then filled
	//    by the call.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetDeviceCount
		(
		SMvDeviceCount* io_psDeviceCount // Returns required information about the audio and video input
		                                 // and output devices.
		) = 0;

	//
	// Summary:
	//    Retrieves all available audio and video channels. This enumerated information is used by 
	//    other methods to get specific controls. The parameters must be allocated by the caller using
	//    the GetDeviceCount() method.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetAudioVideoChannels
		(
		EMvVideoIOChannel*			io_peVideoCaptureChannel,        // An array to contain all video capture channels. 
                                                                  // The array must be allocated by the user. 
		unsigned int 					in_uiVideoCaptureChannelCount,   // Specifies the count of the structures in the array 
                                                                  // of the previous parameter.
		EMvVideoIOChannel*			io_peVideoPlaybackChannel,       // An array to contain all video playback channels. 
                                                                  // The array must be allocated by the user.
		unsigned int 					in_uiVideoPlaybackChannelCount,  // Specifies the count of structures in the array of 
                                                                  // the previous parameter.
		EMvAudioCaptureChannel*		io_peAudioCaptureChannel,        // An array to contain all audio capture channels. 
                                                                  // The array must be allocated by the user.
		unsigned int 					in_uiAudioCaptureChannelCount,   // Specifies the count of structures in the array of 
                                                                  // the previous parameter.
		EMvAudioPlaybackChannel*	io_peAudioPlaybackChannel,       // An array to contain all audio playback channels. 
                                                                  // The array must be allocated by the user.
		unsigned int 					in_uiAudioPlaybackChannelCount   // Specifies the count of structures in the array of 
                                                                  // the previous parameter.
		) = 0;

	//
	// Summary:
	//    Controls the genlock resolution.
	// Return value:
	//    - Returns success if the passed resolutions are valid and if the drivers can be changed.
	//    - Return unsuccessful if one of the above are not valid.
	virtual HRESULT __stdcall ControlGenlockResolution
		(
      EMvIOCommand			in_eIOCommand,	     // Specifies the command that describes what to do with the parameters. 
      // The keIOCommandGetRange is not supported for this call.
		SMvResolutionInfo* 	io_psResolution     // Specifies the genlock resolution.
		) = 0;

	//
	// Summary:
	//    Controls the resolution of a specific video capture channel.
	// Return value:
	//    - Returns success if the passed resolutions are valid and if the drivers can be changed. 
	//    - Returns unsuccessful if one of the parameters above are not valid.
	virtual HRESULT __stdcall ControlVideoCaptureResolution
		(
		EMvIOCommand			in_eIOCommand,	// Specifies the command that describes what to do with the parameters. The 
                                          // keIOCommandGetRange is not supported for this call.
		SMvResolutionInfo*	io_psResolution,  // Specifies the video capture resolution.
		EMvVideoIOChannel		in_eChannel       // Specifies the video capture channel that controls the resolution.
		) = 0;

	//
	// Summary:
	//    Controls the resolution of a specific video playback channel.
	// Return value:
	//    - Returns success if the passed resolutions are valid and if the drivers can be changed. 
	//    - Return unsuccessful if one of the above are not valid.
	virtual HRESULT __stdcall ControlVideoPlaybackResolution
		(
		EMvIOCommand			in_eIOCommand,	// Specifies the command that describes what to do with the parameters.
		                                    // The keIOCommandGetRange is not supported for this call.
		SMvResolutionInfo*	io_psResolution,    // Specifies the video playback resolution.
		EMvVideoIOChannel	in_eChannel            // Specifies the video playback channel that controls the resolution.
		) = 0;

	//
	// Summary:
	//    Controls the audio capture configuration.
	// Return value:
	//    - Returns success if the passed configuration is valid and if the drivers can be changed.
	//    - Returns unsuccessful if one of the above are not valid.
	virtual HRESULT __stdcall ControlAudioCaptureConfiguration
		(
		EMvIOCommand					   in_eIOCommand,    // Specifies the command that describes what to do with the 
                                                      // parameters. The keIOCommandGetRange parameter is not 
		                                                // supported for this call.
		EMvAudioCaptureConfiguration  in_eConfig,       // Specifies what to configure in the audio capture module. 
		void*			                  io_pConfig,       // Contains a pointer to a variable containing the value that 
                                                      // will be taken by the configured parameter.
		unsigned int                  in_uiConfigSize,  // Size of the parameter passed in io_pConfig.
		EMvAudioCaptureChannel	      in_eAudioChannel  // Specifies which audio capture channel is used for captured.
		) = 0;

	//
	// Summary:
	//    Controls the audio playback configuration. It determines from which hardware video playback
	//    output a specific audio playback output will be related.
	// Return value:
	//    - Returns success if the passed configuration is valid and if the drivers can be changed. 
	//    - Returns unsuccessful if one of the parameters above are not valid.
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall ControlAudioPlaybackConfiguration
		(
		EMvIOCommand					   in_eIOCommand,    // Specifies the command that describes what to do with the 
                                                      // parameters. The keIOCommandGetRange parameter is not
		                                                // supported for this call.
		EMvAudioPlaybackConfiguration in_eConfig,       // Specifies what to configure in the audio playback module. Only 
                                                      // the keAudioPlaybackConfigurationSyncMaster value is supported 
                                                      // for now.
		void*			                  io_pConfig,       // Contains a pointer to a variable containing the value that 
                                                      // will be taken by the configured parameter. For the sync master,
		                                                // this must be a value of type EMvVideoIOChannel.
		unsigned int                  in_uiConfigSize,  // Size of the parameter passed in io_pConfig.
		EMvAudioPlaybackChannel       in_eAudioChannel  // Specifies which audio playback channel to use for play back.
		) = 0;

	//
	// Summary:
	//    Returns descriptions for the passed IODevice index in order to determine what resolutions 
	//    are available on the IODevice.
	virtual HRESULT __stdcall GetIODeviceDescription
		(
		unsigned int	in_uiIODeviceIndex,        // The IODevice zero based index from which to get the description.
		char*				out_szIODeviceDescription, // Returns a string describing the IODevice.
		EMvIODeviceID* out_eIODeviceId            // Returns an enumeration that is the IODevice id.
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvGenlockControl interface.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetGenlockInterface
		(
		IMvGenlockControl** out_ppIGenlockControl // Returns a pointer to the IMvGenlockControl (master genlock control) 
                                                // interface. See the ControlResolutions() method for information 
		                                          // about setting the master genlock.
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvIODeviceControl interface.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetIODeviceInterface
		(
		unsigned int			in_uiIODeviceIndex,     // Gives the IODevice zero based index from which to get the interface.
		IMvIODeviceControl** out_ppIIODeviceControl  // Returns a pointer to the IMvIODeviceControl interface.
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvVideoCaptureControl interface.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetVideoCaptureInterface
		(
		EMvVideoIOChannel in_eChannel,                      // Provides the video capture channel that provides the interface.
		IMvVideoCaptureControl** out_ppIVideoCaptureControl // Returns a pointer to the IMvVideoCaptureControl interface.
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvVideoPlaybackControl interface.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetVideoPlaybackInterface
		(
		EMvVideoIOChannel in_eChannel,                        // Provides the video playback channel that provides the interface.
		IMvVideoPlaybackControl** out_ppIVideoPlaybackControl // Returns a pointer to the IMvVideoPlaybackControl interface.
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvAudioCaptureControl interface.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetAudioCaptureInterface
		(
		EMvAudioCaptureChannel   in_eChannel,               // Gives the audio capture channel that provides the interface.
		IMvAudioCaptureControl** out_ppIAudioCaptureControl // Returns a pointer to the IMvAudioCaptureControl interface.
		) = 0;

	//
	// Summary:
	//    Method to use to get the audio playback control interface.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetAudioPlaybackInterface
		(
		EMvAudioPlaybackChannel   in_eChannel,                  // Gives the audio playback channel to get interface from.
		IMvAudioPlaybackControl** out_ppIAudioPlaybackControl   // Returns a pointer to Audio playback control interface.
		) = 0;

	//
	// Summary:
	//    Retrieves the IMvSerialPlaybackControl interface.
	// Return value:
	//    - Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetSerialPlaybackInterface
		(
		EMvVideoIOChannel				in_eChannel,                 // Provides the serial playback channel that provides the interface.
		IMvSerialPlaybackControl** out_ppISerialPlaybackControl // Returns a pointer to the IMvSerialPlaybackControl interface.
		) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This interface is used to control the Flex File Writer module.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvFlexWriter : public IUnknown
{

	//
	// Summary:
	//    Provides an uncompressed video and/or audio and/or VBI frame of data.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_FILE_NOT_OPENED, if IMvFlexWriter::OpenFile has not already been successfully performed. 
	//    - MV_E_INVALID_PIPELINE_SIZE, if IMvFlexWriter::SetPipelineSize has not already been
	//      successfully performed. 
	//    - MV_E_NOT_ENOUGH_INPUT_SURFACES, if there is an insufficient amount of surfaces in the video
	//      or VBI arrays to process the capture. 
	//    - MV_E_NOT_ENOUGH_INPUT_SAMPLES, if there is an insufficient number of sample buffers in the 
	//      audio samples array to process the capture. 
	//    - MV_E_INVALID_POINTER, if any of the input surfaces/samples array pointers expected to be
	//      valid is NULL. 
	//    - MV_E_INVALID_PARAMETER, if the specified array sizes do not match the 
	//      IMvFlexWriter::OpenFile resolution. 
	//    - MV_E_OUT_OF_MEMORY, if all the Flex File Writer surfaces/samples are outside of its pools,
	//      none are currently available. 
	// Remarks:
	//    - Prior to calling this method you must have properly initialized the Flex File Writer. To 
	//      process this method, the Flex File Writer must capture specific information provided in 
	//      IMvFlexWriter::OpenFile and a pipeline size must be provided in IMvFlexWriter::SetPipelineSize. 
	//    - This method always returns a frame of uncompressed video and/or audio and/or VBI data. 
	//      If the user chooses to capture in a compressed format, the Flex File Writer compresses the 
	//      data asynchronously. This asynchronous processing is transparent to the caller. 
	//    - The returned video/audio/VBI surfaces/samples have had their synchronization objects 
	//      prepared so that as soon as the caller is done processing them, all asynchronous 
	//      processing is automatically performed by the Flex File Writer (compression and/or write to disk). 
	//    - The returned video/audio/VBI surfaces/samples are the property of the Flex File Writer. 
	//    - The Flex File Writer has a limited number of video/audio/VBI surfaces/samples. The caller
	//      needs to consume the retrieved buffers in order for them to become reusable by the Flex File
	//      Writer. 
	//    - When the in_bWait waiting flag is set to True, and if the Flex File Writer runs out of buffers
	//      to process the current GetBuffer() call, the Flex File Writer will wait indefinitely for a 
	//      buffer to become available. If, on the other hand, the in_bWait flag is set to False, an 
	//      error code will be returned immediately allowing the caller to react by freeing up buffers. 
	//    - The in_aulNumberOfSamplesPerBuffer parameter represents the audio sequence and is 
	//      determined by the caller. 
	//    - The in_ui64TimeStamp parameter is obtained by the caller through the IMvClock interface,
	//      which in turn is obtained through the Flex Engine. This time stamp can be used by the
	//      caller to prioritize the GetBuffer operations, especially if multiple readers/writers are 
	//      running concurrently. 
	virtual HRESULT __stdcall GetBuffer
		(
		IMvSurface*       out_apIVideoSurfaces[],             // IMvSurface* video surfaces array that receives any of 
                                                            // the video surfaces to be captured.
		unsigned long*    io_pulVideoSurfacesArraySize,       // Video surfaces array size specifying how many video 
                                                            // surfaces the caller expects [in], and how many video 
		                                                      // surfaces the Flex File Writer returned [out].
		IMvAudioSamples*  out_apIAudioSamples[],              // IMvAudioSamples* audio samples array that receives any 
                                                            // of the audio samples to be captured.
		unsigned long*    io_pulAudioSamplesArraySize,        // Audio samples array size specifying how many audio 
                                                            // sample buffers the caller expects [in], and how many
		                                                      // audio sample buffers the Flex File Writer returned [out].
		unsigned long     in_aulNumberOfSamplesPerBuffer[],   // Number of audio samples the caller expects per 
                                                            // IMvAudioSamples buffer [in]. This is the caller-supplied 
		                                                      // audio sequence. 
		IMvSurface*       out_apIVBISurfaces[],               // IMvSurface* VBI surface array that receives any of the 
                                                            // VBI surfaces to be captured.
		unsigned long*    io_pulVBISurfacesArraySize,         // VBI surface array size specifying how many VBI surfaces 
                                                            // the caller expects [in], and how many VBI surfaces the 
                                                            // Flex File Writer returned [out].
		uint64_t          in_ui64TimeStampInNanoTime,         // Time stamp, in nanotime, to be used internally by the 
                                                            // Flex Writer for asynchronous buffering sequencing.
		bool              in_bWait                            // If true, indicates how the Flex File Reader should behave 
		                                                      // if it runs out of internal buffers to process GetBuffer().
		) = 0;

	// Summary:
	//    Retrieves a memory buffer for the encoding process.
	// Remarks:   
	//    - When the in_bWait waiting flag is set to True, and if the Flex File Writer runs out of buffers
	//      to process the current GetBuffer() call, the Flex File Writer will wait indefinitely for a 
	//      buffer to become available. If, on the other hand, the in_bWait flag is set to False, an 
	//      error code will be returned immediately allowing the caller to react by freeing up buffers. 
	//                                                                                                                                                                                                                   
	virtual HRESULT __stdcall GetBufferWithSize
		(
		IMvSurface*       out_apIVideoSurfaces[],             // Receives the video surfaces to be captured.
		unsigned long*    io_pulVideoSurfacesArraySize,       //  Specifies the number of video surfaces the caller 
                                                            // expects [in], and the number of video surfaces the Flex 
                                                            // File Writer returns [out].                                                           
		IMvAudioSamples*  out_apIAudioSamples[],              //  Receives the audio samples to be captured.                                                             
		unsigned long*    io_pulAudioSamplesArraySize,        //  Specifies the number of audio samples the caller expects 
                                                            // [in], and the number of audio sample buffers the Flex 
                                                            // File Writer returns [out].
		unsigned long     in_aulNumberOfSamplesPerBuffer[],   //  Specifies the number of audio samples the caller 
                                                            // expects per IMvAudioSamples buffer. This is the 
                                                            // caller-supplied audio sequence. 
		IMvSurface*       out_apIVBISurfaces[],               // Receives the VBI surfaces to be captured.                                                               
		unsigned long*    io_pulVBISurfacesArraySize,         //  Specifies the number of VBI surfaces the caller expects 
                                                            // [in], and the number of VBI surfaces the Flex File 
                                                            // Writer returns [out].
		uint64_t          in_ui64TimeStampInNanoTime,         //  Specifies the time stamp, in nanotime, to be used
		                                                      // internally by the Flex File Writer for
		                                                      // asynchronous buffering sequencing                                                               
		bool              in_bWait,                           //  If true, indicates how the Flex File Writer should behave
		                                                      // if it runs out of internal buffers to process GetBuffer()
		                                                      // (see remarks).
		unsigned long     in_ulSizeInBytes                    // Specifies the buffer size, in bytes, that should be 
		                                                      // returned in the GetBuffer() surface.
		                                                      // Used mostly in consolidation.
		) = 0;

		//
	// Summary:
	//    Opens a capture session and initializes the Flex File Writer with specific capture parameters.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_PIPELINE_SIZE, if IMvFlexWriter::SetPipelineSize has not already been successfully 
	//      performed. 
	//    - MV_E_FILE_ALREADY_OPENED, if IMvFlexWriter::OpenFile has already been performed. 
	//    - MV_E_INVALID_POINTER, if one of the supplied pointers that is expected to be valid is NULL. 
	//    - MV_E_INVALID_START_POSITION, if the specified start position is not valid. 
	//    - MV_E_INVALID_CAPTURE_TYPE, if the specified capture type is not supported. 
	//    - MV_E_INVALID_FILE_OPEN_MODE, if the specified file open mode is not supported. 
	//    - MV_E_STRUCTURE_SIZE_MISMATCH, if the size of one of the input structure parameters is 
	//      invalid (could be the result of a static linking versioning issue). 
	//    - MV_E_UNSUPPORTED_SURFACE_FORMAT, if the surface format specified in the video capture 
	//      parameters is not supported. 
	//    - MV_E_UNSUPPORTED_ENCODER_RESOLUTION, if the codec does not support the specified video 
	//      resolution. 
	//    - MV_E_UNSUPPORTED_VBI_RESOLUTION, if the specified VBI resolution is not supported. 
	//    - MV_E_UNSUPPORTED_COMPONENT_BIT_COUNT, if the specified resolution component bit count
	//      is not supported. 
	//    - MV_E_TDIR_NOT_SUPPORTED, specifying this type of capture is not supported yet. 
	//    - MV_E_CUSTOMIO_NOT_SUPPORTED, specifying this type of capture is not supported yet. 
	//    - MV_E_UNSUPPORTED_SCAN_MODE, if the specified resolution scan mode is not supported. 
	//    - MV_E_UNSUPPORTED_FRAME_RATE, if the specified resolution frame rate is not supported. 
	//    - MV_E_UNSUPPORTED_ASPECT_RATIO, if the specified resolution aspect ratio is not supported. 
	//    - MV_E_INVALID_PARAMETER, if the specified array sizes do not match the 
	//      IMvFlexWriter::OpenFile resolution. 
	// Remarks:
	//    - This method initializes the capture process and allocates all resources that will be used 
	//      during the capture. 
	//    - If this method fails, it will call CloseFile() internally, so that the caller doesn't 
	//      need to do so manually. 
	virtual HRESULT __stdcall OpenFile
		(
		wchar_t*                 in_pSZFilename,               // File to be the capture target.
		EMvFlexWriterCaptureType in_eCaptureType,              // A combination of video/audio/VBI flags specifying 
                                                             // what type of data you're capturing inside
		                                                       // the specified file.
		SMvResolutionInfo*       in_pSResolution,              // Resolution of the file to be captured.
		unsigned long            in_ulStartPositionInsideFile, // Position, at which to start the capture inside the
                                                             // specified file, if the file already exists.
		SMvFlexWriterVideoParameters* in_pSVideoParameters,    // Video-specific capture parameters.
		SMvFlexWriterAudioParameters* in_pSAudioParameters,    // Audio-specific capture parameters.
		unsigned long            in_ulVBIHeightInLines,        // Number of lines to be used if a VBI capture type is 
                                                             // specified.
		bool                     in_bTDIR,                     // If true, indicates a TDIR (time delay instant replay)
                                                             // capture.
		double                   in_dTDIRFlushFrequency,       // Specifies the flush frequency in case of a TDIR 
                                                             // (time delay instant replay) capture.
		const CLSID*             in_pclsidFlexAVClip,          // Specifies the desired Flex clip writer to be used in
                                                             // the capture process. Used in specific scenarios such
                                                             // as Quicktime proxy captures. Set to NULL by default.
		wchar_t*                 in_pSZReferenceFileName=NULL  // Reference File Name For TDIR MOV, for other the 
                                                             // default will be null
		) = 0;

   //
   // Summary:
   //    Same as OpenFile but can indicate which type of memory management to use.
   virtual HRESULT __stdcall OpenFileEx
      (
      SMvFlexWriterOpenParameters* in_psFlexWriterOpenParameters  // capture parameters.
      ) = 0;

	//
	// Summary:
	//    Closes a capture session and frees resources used in the capture.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	// Remarks:
	//    - This method always succeeds. 
	//    - With the exception of MPEG2-IBP captures, the method waits up to two seconds for all the
	//      buffers to be either written to disk or cancelled. When capturing MPEG2-IBP the method
	//      will wait until the codec has completed encoding all the frames before returning.
	//      Internally the method verifies that the codec is still active, and waits until it 
	//      becomes inactive. 
	//    - The method frees all the resources used in the capture process, allowing the Flex Writer
	//      to be reused for another capture. 
	virtual HRESULT __stdcall CloseFile() = 0;

	//
	// Summary:
	//    Controls the amount of buffering to sustain.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_FILE_ALREADY_OPENED, if a call to IMvFlexWriter::SetPipeLineSize must be performed
	//      prior to IMvFlexWriter::OpenFile. 
	//    - MV_E_INVALID_PIPELINE_SIZE, if the specified pipeline size is equal to zero. 
	// Remarks:
	//    - This method is used to balance file writing efficiency and memory consumption. 
	//      Increasing the pipeline size in frames can improve reliability at the expense of a 
	//      higher memory footprint. 
	virtual HRESULT __stdcall SetPipelineSize
		(
		unsigned long in_ulPipelineSizeInFrames   // Maximum number of positions, in frames, to be 
		                                          // buffered by the Flex File Writer.
		) = 0;

	//
	// Summary:
	//    Allows the caller direct control over the capture codec option interface that is used to 
	//    adjust codec-specific parameters.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if the supplied value pointer is NULL. 
	//    - MV_E_FAIL, if the current capture process does not warrant use of a codec (uncompressed). 
	virtual HRESULT __stdcall SetCodecOption
		(
		unsigned char* in_pmvchOptionValue, // Value to set in the specified option.
		EMvCodecOption in_eCodecOption      // Option to set the specified value to. 
		) = 0;

	//
	// Summary:
	//    Allows the caller access to the codec options supported by the specific codec used in the capture.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if the supplied value pointer is NULL. 
	//    - MV_E_FAIL, if the current capture process does not warrant the use of a codec (uncompressed). 
	virtual HRESULT __stdcall GetCodecOption
		(
		unsigned char* out_pmvchOptionValue,   // Value to get in the specified option.
		EMvCodecOption in_eCodecOption         // Option to set the specified value to.
		) = 0;

	//
	// Summary:
	//    Allows the caller access to the codec options supported by the specific codec used in the capture.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, if the supplied value pointer is NULL. 
	//    - MV_E_FAIL, if current capture process does not warrant the use of a codec (uncompressed). 
	virtual HRESULT __stdcall IsCodecOptionSupported
		(
		EMvCodecOption in_eCodecOption,     // Option to query if supported.
		bool*          out_pbSupported      // Flag specifying if the option is supported or not.
		) = 0;

	//
	// Summary:
	//    Gets a specific option from the clip writer.
	// Remarks:
	//    - The file must be open before calling this method.
	//
	virtual HRESULT __stdcall GetClipOption
		( 
		void*         io_pvOptionValue,     // Pointer to a clip option value.
		unsigned long in_ulOptionSize,      // Size, in bytes, of the address in io_pvOptionValue.
		const GUID * in_pkguidOptionGuid    // Option specific to the clip writer.
		) = 0;

	//
	// Summary:
	//    Sets a specific option from the clip writer.
	// Remarks:
	//    - The file must be open before calling this method.
	//
	virtual HRESULT __stdcall SetClipOption
		( 
      void*         in_pvOptionValue,     // Pointer to a clip option value.
      unsigned long in_ulOptionSize,      // Size, in bytes, of the address in in_pvOptionValue.
      const GUID * in_pkguidOptionGuid    // Option specific to the clip writer.
		) = 0;

	//
	// Summary:
	//    Indicates if the current clip writer supports a specific option.
	// Remarks:
	//    - The file must be open before calling this method.
	//
	virtual HRESULT __stdcall IsClipOptionSupported
		( 
		const GUID * in_pkguidOptionGuid,   // Option specific to the clip writer.
		bool*         out_pbSupported       // If true, the option is supported.
		) = 0;

	//
	// Summary:
	//    Gets a specific option from the clip writer.
	// Remarks:
	//    - The file is not opened yet.
	//
	virtual HRESULT __stdcall GetClipOption
		(
		const GUID *  in_pguidClip,         // Clip writer GUID identifier.
		void *        io_pvOptionValue,     // Pointer to a clip option value.
		unsigned long in_ulOptionSize,      // Size, in bytes, of the address in io_pvOptionValue.
		const GUID * in_pkguidOptionGuid    // Option specific to the clip writer.
		) = 0;

	//
	// Summary:
	//    Indicates if the current clip writer supports a specific option.
	// Remarks:
	//    - The file is not opened yet.
	//
	virtual HRESULT __stdcall IsClipOptionSupported
		(
		const GUID *  in_pguidClip,         // Clip writer GUID identifier.
		const GUID * in_pkguidOptionGuid,   // Option specific to the clip writer.
		bool *        out_pbSupported       // If true, the option is supported.
		) = 0;


	//
	// Summary:
	//    Allows the caller to switch the target capture file as required on the fly.
	// Remarks:
	//    - Not all file formats support this functionality.
	//
   virtual HRESULT __stdcall SwitchToNewFile(
      wchar_t* in_pwchFilename,                 // New target file name.
      uint64_t in_ui64SwitchAtFrame,            // Time in video frames at which to switch to the new target file.
      wchar_t* in_pwchReferenceFilename = NULL  // Indicates the new reference file name. This is required for TDIR
                                                // capture and playback functionality.
      ) = 0;

   //
   // Summary:
   //    Allows the caller direct control over the Flex File Writer option interface that is used to 
   //    adjust capture-specific parameters.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the supplied value pointer is NULL. 
   //    - MV_E_NOT_SUPPORTED, if current Flex File Writer does not support the specific option. 
   virtual HRESULT __stdcall SetWriterOption
      (
       void*         in_pvOptionValue,    // Pointer to a Flex File Writer option value.
       const GUID * in_pkguidOptionGuid   // Option specific to the Flex File Writer.
      ) = 0;

   //
   // Summary:
   //    Allows the caller access to the Flex File Writer options supported by the specific option used in the capture.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the supplied value pointer is NULL. 
   //    - MV_E_FAIL, if the current capture process does not warrant the use of a codec (uncompressed). 
   virtual HRESULT __stdcall GetWriterOption
      (
      void* out_pvOptionValue,            // Value to get in the specified option.
      unsigned long in_ulOptionSize,      // Size of the specific option value.
      const GUID * in_pkguidOptionGuid    // Option specific to the Flex File Writer.
      ) = 0;

   //
   // Summary:
   //    Allows the caller access to the Flex File Writer to see if the specific option is supported in the capture.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the supplied value pointer is NULL. 
   //    - MV_E_FAIL, if the current capture process does not support the specific option. 
   virtual HRESULT __stdcall IsWriterOptionSupported
      (
      const GUID * in_pkguidOptionGuid,   // Option specific to the Flex File Writer.
      bool*         out_pbSupported       // If true, the option is supported.
      ) = 0;

};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This interface is used to extend the control of the mvFlexWriter module.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvFlexWriter2 : public IMvFlexWriter
{
public:
   //
   // Summary:
   //    Compresses an uncompressed video and/or audio and/or VBI frame of data.
   //    Basically, the caller supplies the uncompressed buffers to the Flex File Writer.
   //    This is presently supported only when the compression format is H.264 video with AAC audio. 
   //    All other types of compression will be rejected.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_FILE_NOT_OPENED, if IMvFlexWriter::OpenFile has not already been successfully performed. 
   //    - MV_E_INVALID_PIPELINE_SIZE, if IMvFlexWriter::SetPipelineSize has not already been
   //      successfully performed. 
   //    - MV_E_NOT_ENOUGH_INPUT_SURFACES, if there is an insufficient amount of surfaces in the video
   //      or VBI arrays to process the capture. 
   //    - MV_E_NOT_ENOUGH_INPUT_SAMPLES, if there is an insufficient number of sample buffers in the 
   //      audio samples array to process the capture. 
   //    - MV_E_INVALID_POINTER, if any of the input surfaces/samples array pointers expected to be
   //      valid are NULL. 
   //    - MV_E_NOT_SUPPORTED, if the specified audio and/or video compression type is not supported. 
   //    - MV_E_OUT_OF_MEMORY, if all the Flex File Writer surfaces/samples are outside of its pools,
   //      none are currently available. 
   //    - MV_E_INVALID_MEMORY_LOCATION, if the video/VBI surfaces or audio sample buffers are not from the proper
   //      location (video surfaces must be located in I/O memory, and VBI surfaces and audio sample buffers must be 
   //      located in host or user memory).
   //    - MV_E_UNSUPPORTED_AUDIO_CHANNEL_TYPE, if the audio sample channel type doesn't match what was specified
   //      during the OpenFile call.
   //    - MV_E_UNSUPPORTED_AUDIO_DATA_TYPE, if the audio sample data type doesn't match what was specified
   //      during the OpenFile call.
   //    - MV_E_UNSUPPORTED_AUDIO_SAMPLES_PER_SECOND, if the audio samples per second is not 48000.
   //    - MV_E_INVALID_VIDEO_STANDARD, if the A/V contents description is incorrect.
   // Remarks:
   //    - Prior to calling this method you must properly initialize the Flex File Writer. To 
   //      process this method, the Flex File Writer must capture specific information provided in 
   //      IMvFlexWriter::OpenFile, and a pipeline size must be provided in IMvFlexWriter::SetPipelineSize.
   //      For this specific case, the pipeline size must be set to 1 frame.
   //    - The supplied video/VBI surfaces and audio sample buffers must have their synchronization objects 
   //      prepared so that as soon as the caller is done processing them, all asynchronous 
   //      processing is automatically performed by the Flex File Writer (compression and/or write to disk). 
   //    - The in_ui64TimeStamp parameter is obtained by the caller through the IMvClock interface,
   //      which in turn is obtained through the Flex Engine. This time stamp can be used by the
   //      caller to prioritize the GetBuffer operations, especially if multiple readers/writers are 
   //      running concurrently. 
   //      If a synchronous or asynchronous error occurs, all synchronization objects will be properly signaled to
   //      avoid unsignaled A/V contents.
   virtual HRESULT __stdcall WriteBuffer
      (
      IMvSurface*       in_apIVideoSurfaces[], 
      unsigned long     in_ulVideoSurfacesArraySize, 
      IMvAudioSamples*  in_apIAudioSamples[], 
      unsigned long     in_ulAudioSamplesArraySize, 
      IMvSurface*       in_apIVBISurfaces[], 
      unsigned long     in_ulVBISurfacesArraySize,
      uint64_t          in_ui64TimeStampInNanoTime       // Time stamp, in nanotime, to be used. 
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This interface is used to be notified by the Flex File Writer that a state has changed or an asynchronous error
//    has occurred.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvFlexWriterStateObserver : public IUnknown
{
public:
   //
   // Summary:
   //    Notifies the user application that the state of the Flex File Writer has changed or that an asynchronous
   //    error has occurred.
   // Return value:
   //    - MV_NOERROR if completed successfully
   virtual HRESULT __stdcall NotifyState
      (
      HRESULT in_hrValue 
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Sets a state observer on the Flex File Writer.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvFlexWriterState : public IUnknown
{
public:
   //
   // Summary:
   //    Provides a callback to notify the user application that the state of the Flex File Writer has changed or an
   //    asynchronous error has occurred.
   // Return value:
   //    - MV_NOERROR if completed successfully
   virtual HRESULT __stdcall SetStateObserver
      (
      IMvFlexWriterStateObserver * in_pIMvFlexWriterStateObserver 
      ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Returns an asynchronous error in the Flex File Writer.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvFlexAsynchronousErrorNotification : public IUnknown
{
	//
	// Summary:
	//    Indicate an asynchronous error.
	virtual HRESULT __stdcall SetLastError
		(
		HRESULT in_hAsynchronousError
		) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This interface is used to control the mvFlexReader playlist reader module.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvFlexReader : public IUnknown
{
	//
	// Summary:
	//    Retrieves a video and/or audio and/or VBI frame of data, along with its position in the playlist.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_PLAYLIST_NOT_SET, if the Flex File Reader doesn't have a playlist to work with. 
	//    - MV_E_PIPELINE_SIZE_NOT_SET, if the pipeline size has not been set yet. 
	//    - MV_E_POSITION_PARAMETER_NOT_SET, if the out_pdPositionInsidePlayListInFrames parameter is NULL. 
	//    - MV_E_NOT_ENOUGH_INPUT_SURFACES, if the video and/or VBI array size is zero. 
	//    - MV_E_VIDEO_SURFACES_PARAMETER_NOT_SET, if the video and/or VBI surfaces array parameter is NULL. 
	//    - MV_E_TOO_MANY_INPUT_SAMPLES, if the audio array size is larger than two. 
	//    - MV_E_AUDIO_SAMPLES_PARAMETER_NOT_SET, if the input audio samples array pointer is NULL. 
	//    - MV_E_OUT_OF_RANGE, if the current GetBuffer() position is negative, or is larger than the 
	//      playlist duration. 
	//    - MV_E_ELEMENT_IN_USE, if the Flex File Reader was unable to access the playlist element because
	//      it is locked. 
	//    - MV_E_FAILED_TO_RETRIEVE_POSITION_FROM_DISK, if the Flex File Reader expected the position
	//      but it hasn't been read from the disk yet (most likely to occur if in_bWait is set to false). 
	// Remarks:
	//    - Prior to calling this method, you should have properly initialized the Flex File Reader.
	//      To process this method, the Flex File Reader needs a playlist, a pipeline size, a shuttle
	//      rate, and a position to seek or play from. 
	//    - This method always returns a frame of uncompressed video and/or audio and/or VBI data. If 
	//      a compressed element is being retrieved, the Flex File Reader decompresses it 
	//      asynchronously. If the element requires a slow motion blending operation, the Flex File 
	//      Reader performs the blending asynchronously. If the audio requires patching with silence,
	//      the Flex File Reader performs the patching asynchronously. This asynchronous processing 
	//      is transparent to the caller. 
	//    - The returned video/audio/VBI surfaces/samples have had their synchronization objects 
	//      prepared so that as soon as all asynchronous processing is done they will be ready for
	//      the read operation. 
	//    - The returned video/audio/VBI surfaces/samples are the property of the Flex File Reader 
	//      and should only be used as read sources. 
	//    - The Flex File Reader has a limited number of video/audio/VBI surfaces/samples. The caller
	//      needs to consume the retrieved buffers in order for them to become available again for
	//      reuse by the Flex File Reader. 
	//    - When the in_bWait waiting flag is set to true, if the Flex reader runs out of buffers 
	//      to process the current GetBuffer() call, it will wait for 10 seconds before returning 
	//      an error code. This is to avoid an infinite timeout in the Flex File Reader. This 
	//      timeout period is not customizable. If the in_bWait flag is set to false, an error code 
	//      will be returned immediately if this scenario occurs. 
	//    - If the Flex File Reader reaches an area of the playlist where there is no element to 
	//      play, and that area is within the playlist length, then the Flex File Reader will adjust 
	//      the arrays' sizes to zero, and the arrays will have their contents set to NULL. This
	//      scenario is called a NULL element. The caller will get a MV_NOERROR return code as it is
	//      expected that a playlist can contain NULL elements. The returned position will continue 
	//      to increment as if an element was present. 
	//    - Audio can be retrieved one frame at a time, or two fields at a time. There is no 
	//      resolution for audio, so it is up to the user application to determine its preferred
	//      behavior. 
	//    - The in_aulNumberOfSamplesparameter represents the audio sequence and is determined by
	//      the caller. The sequence can represent frames or fields processing. Flex File Reader does
	//      its best to fill in the sequence with audio data. If not enough audio data is available 
	//      it will patch with silence (for example, end of a file). 
	//    - The in_ui64TimeStampInNanoTime parameter is obtained by the caller through the IMvClock
	//      interface, which in turn is obtained through the Flex Engine. This time stamp can be used
	//      by the caller to prioritize the GetBuffer() operations, specially if multiple 
	//      readers/writers are running concurrently. 
	//    - The out_pdPositionInsidePlayListInFrames parameter is expressed as a double to provide
	//      sufficient precision for shuttling purposes. For example when playing in slow or fast 
	//      motion, it may be useful for the caller to know at which increment within the specified
	//      frame the position belongs to (ex: 1.1, 1.2, 1.3 ...). 
	//    - Graphics are handled as YUAYVA 4:2:2:4 video. The caller should use the video parameters. 
	//    - VBI can be handled either through the video parameters as if uncompressed video, or 
	//      through the VBI parameter, both are supported by the Flex File Reader. 
	virtual HRESULT __stdcall GetBuffer
		(
		IMvSurface*       out_apIVideoSurfaces[],       // IMvSurface* video surfaces array that
		                                                // receives any of the video surfaces
		                                                // corresponding to out_pdPositionInsidePlayListInFrames.
		unsigned long*    io_pulVideoSurfacesArraySize, // Video surfaces array size specifying how many  video surfaces
		                                                // the caller expects [in],  and how many video surfaces the
		                                                // Flex File Reader returned [out].
		IMvAudioSamples*  out_apIAudioSamples[],        // IMvAudioSamples* audio samples array that receives any of the 
                                                      // audio samples corresponding to
		                                                // out_pdPositionInsidePlayListInFrames.
		unsigned long*    io_pulAudioSamplesArraySize,  // Audio samples array size specifying how many audio samples 
                                                      // buffers the caller expect[in], and how many audio samples 
                                                      // buffers the Flex File Reader returned [out].
		unsigned long     in_aulNumberOfSamplesPerBuffer[],   // Number of audio samples the caller expects per 
                                                            // IMvAudioSamples buffer [in].
		IMvSurface*       out_apIVBISurfaces[],         // IMvSurface* VBI surfaces array that receives any of the VBI 
                                                      // surfaces corresponding to out_pdPositionInsidePlayListInFrames.
		unsigned long*    io_pulVBISurfacesArraySize,   // VBI surfaces array size specifying how many VBI surfaces the 
                                                      // caller expects [in], and how many VBI surfaces the Flex File 
		                                                // Reader returned [out].
		double*           out_pdPositionInsidePlayListInFrames,  // Position inside the cutlist, in frames, corresponding 
                                                               // to the returned buffer(s).
		uint64_t          in_ui64TimeStampInNanoTime,   // Time stamp, in nanotime, to be used internally by the Flex 
                                                      // File Reader for asynchronous buffering sequencing.
		bool              in_bWait    // If true, indicates how the Flex File Reader should behave if it runs 
		                              // out of internal buffers to process GetBuffer().
		) = 0;

	//
	// Summary:
	//    Specifies the playlist to be read.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_PLAYLIST_TYPE, if the playlist type is not supported. 
	//    - MV_E_OUT_OF_MEMORY, if there is no more memory available for allocation, or an error
	//      occurred while allocating the memory. 
	//    - MV_E_OUT_OF_POOL_MEMORY, if no more pool memory is available, or an error occurred during
	//      pool allocations. 
	//    - MV_E_INVALID_PARAMETER, the structure size is unexpected, possibly due to a compilation issue. 
	// Remarks:
	//    - The IMvPlayList interface is the base interface for all the Flex File Reader processing
	//      operations. 
	//    - IMvPlayList is created by the Flex Engine. 
	//    - Setting a NULL playlist frees the resources currently in use by the Flex File Reader. 
	//    - The playlist can be modified by the caller even if it has been set on the Flex File Reader. 
	//    - The playlist configuration structure informs the Flex File Reader of the element type it
	//      should look for (video, audio, AV, etc.). It also helps the Flex File Reader to allocate 
	//      its internal memory pools by specifying the maximum resolution used inside the playlist 
	//      at any given time, as well as if alpha is present in at least one element. 
	virtual HRESULT __stdcall SetPlayList
		(
		IMvPlayList*               in_pIPlayList,             // Pointer to the IMvPlayList interface
		                                                      // to be read by the Flex File Reader.
		SMvPlaylistConfiguration*  in_psPlayListConfiguration // Pointer to a configuration structure used by the Flex 
                                                            // File Reader to determine how it should process data.
		) = 0;

	//
	// Summary:
	//    Retrieves the playlist currently in use.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_PLAYLIST_NOT_SET, if the Flex File Reader does not hold a playlist. 
	virtual HRESULT __stdcall GetPlayList
		(
		IMvPlayList** out_ppIPlayList    // Pointer to the address of the IMvPlayList interface.
		) = 0;

	//
	// Summary:
	//    Controls the amount of buffering to sustain.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_OUT_OF_MEMORY, if there is no more memory available for allocation, or an error
	//      occurred while allocating the memory. 
	//    - MV_E_OUT_OF_POOL_MEMORY, if no more pool memory is available, or an error occurred 
	//      during pool allocations. 
	//    - MV_E_INVALID_PIPELINE_SIZE, if the pipeline size in frames is zero. 
	// Remarks:
	//    - This method is used to balance file reading efficiency and performance. 
	//    - Increasing the pipeline size can improve file reading reliability at the expense of a 
	//      larger memory footprint. 
	virtual HRESULT __stdcall SetPipelineSize
		(
		unsigned long in_ulPipelineSizeInFrames   // Maximum number of positions, in frames, to be
		                                          // buffered by the Flex File Reader.
		) = 0;

	//
	// Summary:
	//    Controls the amount of buffering to sustain.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_OUT_OF_MEMORY, if there is no more memory available for allocation, or an error
	//      occurred while allocating the memory. 
	//    - MV_E_OUT_OF_POOL_MEMORY, if no more pool memory is available, or an error occurred 
	//      during pool allocations. 
	//    - MV_E_INVALID_PIPELINE_SIZE, if the pipeline size in frames is zero. 
	//    - MV_E_UNSUPPORTED_MEMORY_LOCATION if the specified memory location is not one of keMvMemoryLocationHost
	//      or keMvMemoryLocationIOBoard.
	// Remarks:
	//    - This method is used to balance file reading efficiency and performance. 
	//    - Increasing the pipeline size can improve file reading reliability at the expense of a 
	//      larger memory footprint. 
	//    - This method is used on products that support a hardware codec. It allows the user application
	//      to control how much of the local on-board memory the Flex File Reader is allowed to consume. 
	//    - This method does not need to be called on Matrox hardware profiles that do not implement a hardware codec.
	//    - This method can be called with either keMvMemoryLocationHost or keMvMemoryLocationIOBoard any other
	//      memory location parameter will cause it to return an error.
	//    - If keMvMemoryLocationIOBoard is specified then the Flex File Reader can automatically reserve the specified
   //      number of frames in local I/O memory.
	//    - Passing keMvMemoryLocationHost is the equivalent of calling the regular SetPipelineSize.
	//    - The user application can call SetPipelineSize for the host memory location and SetPipelineSizeWithLocation
	//      for the local I/O memory location, or use SetPipelineSizeWithLocation for both host and I/O memory locations.
	virtual HRESULT __stdcall SetPipelineSizeWithLocation
		(
		EMvMemoryLocation in_eMemoryLocation,        // The memory location related to the pipeline size parameter.
		unsigned long     in_ulPipelineSizeInFrames  // Maximum number of positions, in frames, to be
		                                             // buffered by the Flex File Reader in the specified memory location.
		) = 0;

	//
	// Summary:
	//    Specifies the playlist to be read.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, the provided pointer is NULL. 
	virtual HRESULT __stdcall GetPipelineSize
		(
		unsigned long* out_pulPipelineSizeInFrames   // Maximum number of positions, in frames,
		                                             // buffered by the Flex File Reader.
		) = 0;

	//
	// Summary:
	//    Specifies the playlist to be read.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_POINTER, the provided pointer is NULL. 
	virtual HRESULT __stdcall GetPipelineSizeWithLocation
		(
		EMvMemoryLocation in_eMemoryLocation,        // The memory location related to the pipeline size parameter.
		unsigned long* out_pulPipelineSizeInFrames   // Maximum number of positions, in frames,
		                                             // buffered by the Flex File Reader.
		) = 0;

	//
	// Summary:
	//    Specifies the next GetBuffer position and specifies Seek behavior.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_OUT_OF_RANGE, if the specified position is outside the playlist range. 
	// Remarks:
	//    - MV_E_OUT_OF_RANGE is validated against the playlist duration.
	virtual HRESULT __stdcall Seek
		(
		uint64_t in_ui64PositionInsidePlayListInFrames  // Position to seek to inside the playlist, in frames.
		) = 0;

	//
	// Summary:
	//    Specifies the next GetBuffer position and Play behavior.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_OUT_OF_RANGE, if the specified position is outside the playlist range. 
	// Remarks:
	//    - MV_E_OUT_OF_RANGE is validated against the playlist duration. 
	//    - The caller can ask Play() to wait until the desired position is back from the disk before
	//      returning. This guarantees that the next IMvFlexReader::GetBuffer() call will not incur
	//      a disk I/O penalty. 
	virtual HRESULT __stdcall Play
		(
		uint64_t in_ui64PositionInsidePlayListInFrames, // Position inside the playlist, in frames, to start the play from.
		bool     in_bWaitUntilFrameIsReady              // If true, the play blocks until 
		                                                // in_ui64PositionInsidePlayListInFrames is back from disk.
		) = 0;

	//
	// Summary:
	//    Specifies the next GetBuffer position and Step behavior.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_OUT_OF_RANGE, if the specified position is outside the playlist range. 
	// Remarks:
	//    - MV_E_OUT_OF_RANGE is validated against the playlist duration. 
	//    - The caller can ask Step() to wait until the desired position is back from the disk before
	//      returning. This guarantees that the next IMvFlexReader::GetBuffer() call will not incur
	//      a disk I/O penalty. 
	//    - Stepping is used on Matrox hardware profiles that implement a hardware codec. Its use is
	//      to allow the user application to configure the hardware codec in Step mode.
	//    - Stepping is similar to Playing and internally the file I/O buffering is identical to a playback. 
	//    - On a Matrox hardware profile that doesn't implement a hardware codec, this method will put the Flex File Reader
	//      in playback mode.
	virtual HRESULT __stdcall Step
		(
		uint64_t in_ui64PositionInsidePlayListInFrames, // Position inside the playlist, in frames, to start the play from.
		bool     in_bWaitUntilFrameIsReady              // If true, the play blocks until 
		                                                // in_ui64PositionInsidePlayListInFrames is back from disk.
		) = 0;

	//
	// Summary:
	//    Specifies to the Flex File Reader that it should not expect to be called with GetBuffer.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	// Remarks:
	//    - The Flex File Reader will forward this information to internal modules that need to know whether they 
   //      should be streaming or not.
	//    - This method applies to the latest codec generation only such as the AVC codec. If the user application's
   //      playlist includes AVC elements it should make sure to pause the Flex Reader when appropriate (usually based 
   //      on the user interacting with the application).
	//    - Pausing the Flex Reader is not required on other codec platforms.
	//    - The Pause will take effect immediately. All positions already returned in GetBuffer calls remain valid until
   //      they are consumed.
	//    - The user application should not call IMvFlexReader::Play to resume from a paused state since this would
   //      temporarily negatively affect disk IO performance.
	//    - To resume from a paused state the user application only needs to resume calling GetBuffer.
	virtual HRESULT __stdcall Pause() = 0;

	//
	// Summary:
	//    Specifies that the application wants all Flex File Reader activities to stop.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	// Remarks:
	//    - This will cause the Flex File Reader to free any internal buffering it currently holds.
	//    - This is the equivalent to calling IMvFlexReader::Seek( n ) where n is a position outside the playlist range.
	//    - The Flex Reader will release all cached playlist elements. The user application can safely modify the
   //      playlist following a Stop.
	//    - The Stop will take effect immediately. All positions already returned in GetBuffer calls remain valid until
   //      they are consumed.
	//    - To resume from a stopped state the user application needs to call IMvFlexReader::Play or IMvFlexReader::Seek.
	virtual HRESULT __stdcall Stop() = 0;

	//
	// Summary:
	//    Specifies the increment between each GetBuffer() call.
	// Return value:
	//    - MV_NOERROR. This method always succeeds. 
	// Remarks:
	//    - Setting a shuttle rate of 1.0 implies a standard playback scenario. 
	//    - Rate is limited by the application and can be negative, zero, or positive. 

	virtual HRESULT __stdcall Shuttle
		(
		double in_dShuttleRate  // Increment applied by the Flex File Reader to determine the position
		                        // to retrieve between each GetBuffer() call.
		) = 0;

	//
	// Summary:
	//    Retrieves the configured shuttle rate.
	// Return value:
	//    - MV_NOERROR. This method always succeeds. 
	virtual HRESULT __stdcall GetShuttleRate
		(
		double* out_pdShuttleRate  // Increment currently applied by the Flex File Reader to determine
		                           // the position to retrieve between each GetBuffer() call.
		) = 0;

	//
	// Summary:
	//    Sets the value of one of the codec options.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_SUPPORTED, if the option is not supported by the codec. 
	//    - MV_E_INVALID_PARAMETER, if the option value is invalid. 
	// Remarks:
	//    - Because some options are shared by more than one codec, the user must supply the corresponding codec's CLSID.
	//    - The codec CLSIDs are publicly available.
	virtual HRESULT __stdcall SetCodecOption
		(
		const CLSID*   in_pclsidCodec,         // Identifies the codec to which the option applies.
		unsigned char* in_pmvchOptionValue,    // Pointer to the value of the option.
		EMvCodecOption in_eCodecOption         // Enumerator that specifies which option you want to set.
		) = 0;

	//
	// Summary:
	//    Retrieves the value of one of the codec options.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_SUPPORTED, if the option is not supported by the codec. 
	// Remarks:
	//    - Because some options are shared by more than one codec, the user must supply the corresponding codec's CLSID.
	//    - The codec CLSIDs are publicly available.
	virtual HRESULT __stdcall GetCodecOption
		(
		const CLSID*   in_pclsidCodec,            // Identifies the codec to which the option applies.
		unsigned char* out_pmvchOptionValue,      // Pointer to the value of the option.
		EMvCodecOption in_eCodecOption            // Enumerator that specifies which option you want to query.
		) = 0;

	//
	// Summary:
	//    Checks if a certain option is supported by the codec.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	// Remarks:
	//    - Because some options are shared by more than one codec, the user must supply the corresponding codec's CLSID.
	//    - The codec CLSIDs are publicly available.
	virtual HRESULT __stdcall IsCodecOptionSupported
		(
		const CLSID*   in_pclsidCodec,      // Identifies the codec to which the option applies.
		EMvCodecOption in_eCodecOption,     // Enumerator that specifies which option you want to validate.
		bool*          out_pbSupported      // Pointer to bool that validates support.
		) = 0;

	//
	// Summary:
	//    Specifies if the codec(s) should expand the compressed video data to its native size.
	//
	// Remarks:
	//    - In certain resolutions HDV data is horizontally scaled from 1920 to 1440. If the ExpandHDV option is selected
	//      it will tell the Flex File Reader to pass full resolution buffers to the codec's outputs so it can expand
   //      the video to its native resolution.
	virtual HRESULT __stdcall ExpandHDV
		(
		bool in_bExpand      // If true, the Flex File Reader expands any horizontally scaled compressed video.
		) = 0;

   //
   // Summary:
   //    Allows the caller direct control over the Flex File reader interface option that is used to 
   //    adjust play-specific parameters.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_INVALID_POINTER, if the supplied value pointer is NULL. 
   //    - MV_E_NOT_SUPPORTED, if current Flex File Reader does not support the specific option.   
   virtual HRESULT __stdcall SetReaderOption
      (
      void*         in_pvOptionValue,    // Pointer to a Flex File Reader option value.
      const GUID * in_pkguidOptionGuid   // Option specific to the Flex File Reader.
      ) = 0;

};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to extend the mvFlexReader playlist reader module by configuring and monitoring the status
//    of the reader.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvFlexReader2 : public IMvFlexReader
{
   //
   // Summary:
   //    Gets the current status of the Flex Reader.
   // Returns 
   //    - MV_NOERROR, if the structure was filled correctly.
   //    - MV_E_INVALID_POINTER, if io_psFlexReaderStatus is NULL.
   //    - MV_E_INVALID_STRUCTURE_SIZE, if the structure size is invalid.
   //    - MV_E_WRONG_STATE, if the current state of the Flex Reader is not Playing or Stepping.
   virtual HRESULT __stdcall GetStatus
      (
      SMvFlexReaderStatus  *io_psFlexReaderStatus	// Pointer to the Flex Reader status structure.
      ) = 0;

   //
   // Summary:
   //    Sets the current values for the read ahead algorithm.
   // Returns 
   //    - MV_NOERROR, if the structure was filled correctly.
   virtual HRESULT __stdcall SetReadAheadConfiguration
      (
      uint32_t in_ui32MaximumNumberOfPositionsToReadAheadInFrames,   // Indicates the maximum number of positions (in
                                                                     // frames) that are read ahead in the playlist.
      uint32_t in_ui32ThresoldInFramesToActivateReadAhead   // Indicates the threshold (in frames) that is used to 
                                                            // activate the read ahead in the playlist. <p>
																	         // If the number of prepared positions is less
                                                            // than or equal to in_ui32ThresoldInFramesToActivateReadAhead,
                                                            // more positions will be added.
      ) = 0;

   //
   // Summary:
   //    Gets the current values for the read ahead algorithm.
   // Returns 
   //    - MV_NOERROR, if the structure was filled correctly.
   //    - MV_E_INVALID_POINTER, if out_pui32MaximumNumberOfPositionsToReadAheadInFrames or 
   //      out_pui32ThresoldInFramesToActivateReadAhead is NULL.
   virtual HRESULT __stdcall GetReadAheadConfiguration
      (
      uint32_t *out_pui32MaximumNumberOfPositionsToReadAheadInFrames,   // Pointer to the maximum number of positions 
                                                                        // (in frames) that are read ahead in the
                                                                        // playlist.
      uint32_t *out_pui32ThresoldInFramesToActivateReadAhead   // Pointer to the threshold (in frames) that is used to
                                                               // activate the read ahead in the playlist. <p>
                                                               // If the number of prepared positions is less than or 
                                                               // equal to *out_pui32ThresoldInFramesToActivateReadAhead,
                                                               // more positions will be added.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides synchronous operations performed by the synchronous host buffer engine. 
//    This interface can only be obtained publicly through the Host Effect based-class derivation.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSyncBufferEngine : public IUnknown
{
	//
	// Summary:
	//    Performs synchronous copy operations between two video surface.
	// Description:
	//    Performs synchronous copy operations on the content of the source surfac,e bounded by the
	//    source rectangle, to the destination surface at the destination point. Color conversion will
	//    be performed if necessary. De-interlacing or interlacing will be performed if necessary
	//    accordingly to polarities of the surfaces.
	// Return value:
	//    - MV_NOERROR if completed successfully.
	//    - MV_E_MODULE_BUSY if a call to IMvSyncBufferEngine operations is made before return from
	//      current call.
	//    - MV_E_NOT_READY_FOR_READ if any of the sources is not ready for a read operation.
	//    - MV_E_INVALID_POINTER if any of the passed pointers is invalid.
	//    - MV_E_COPY_RECTANGLES_MISMATCH if there's a mismatch between the source and destination rectangle parameters
	//    - MV_E_COPY_FORMATS_COMBINATION_NOT_SUPPORTED if the source and destination formats 
	//      combination is not supported by the SyncCopySurface() method.
	//    - MV_E_POINTER_NOT_ALIGNED if any of the passed pointers is not aligned.
	// Remarks:
	//    - The synchronous copy surface does not signal any events during processing. It is the 
	//      caller's responsibility to make sure that the passed surfaces are ready for read and write operations.
	virtual HRESULT __stdcall SyncCopySurface
		(
		IMvSurface*    in_pIMvSurfaceSrc,   // Address of the IMvSurface interface that is the source of the copy operation.
		SMvRect*       in_prcSrc,           // Address of a SMvRect structure that defines the upper left and lower right 
                                          // points of the rectangle on the source surface to copy from. If NULL, the 
                                          // entire source is used.
		IMvSurface*    in_pIMvSurfaceDst,   // Address of the IMvSurface interface that is the
		                                    // destination of the copy operation.
		SMvRect*       in_prcDst,           // Address of a SMvRect structure that defines the upper left and lower right 
                                          // points of the rectangle on the destination surface to copy to. If NULL, 
                                          // the entire source is used. 
		EMvFilterMode  in_eFilterMode       // FilterMode defines the desired filtering that is to be used if the 2 
                                          // rectangles are not the same size. 
		) = 0;

	//
	// Summary:
	//    Sets the values for the different quality options used in the synchronous buffer engine
	//    processing.
	// Return value:
	//    - MV_NOERROR. This method always returns MV_NOERROR.
	virtual HRESULT __stdcall SetSyncConversionOptions
		(
		SMvConversionOptions *io_psConversionOptions // Pointer to a structure that specifies the 
		                                             // conversion quality desired.
		) = 0;

	//
	// Summary:
	//    Clears Flex surface synchronously with the specified color and alpha
	// Return value:
	//    - MV_NOERROR if completed successfully.
	//    - MV_E_MODULE_BUSY if a call to IMvSyncBufferEngine operations is made before return from
	//      current call.
	//    - MV_E_INVALID_POINTER if the passed pointer is invalid.
	//    - MV_E_INVALID_PARAMETER if one of the passed values is invalid.
	//    - MV_E_NOT_SUPPORTED if the operation is not supported for the surface format or type.
	//    - MV_E_POINTER_NOT_ALIGNED if the destination surface is of YUV format and is not aligned.
	virtual HRESULT __stdcall SyncClearSurface(
		IMvSurface*   in_pIMvSurfaceDst,    // Pointer to the surface to clear.
		EMvColor		in_eColor,              // Color to use when clearing the surface.
		float			in_fAlphaValue) = 0;    // Alpha value to use when clearing the surface.
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Controls the audio voice-over mixer parameters.
// Remarks:
//    - This interface can be obtained via the IMvInputOutputIndependent or IMvInputOutput interface,  
//      and is only available after the resolution has been determined. 
//////////////////////////////////////////////////////////////////////////////////
interface IMvAudioVoiceOverMixerControl : public IUnknown
{
	//
	// Summary:
	//    Selects the capture channel that will use the voice-over mixer. You can choose to capture
	//    the input, or the input and playback mix independently on the left and right side, respectively.
	// Return value:
	//    - Returns an error if the command fails or if there are incorrect parameters. 
	virtual HRESULT __stdcall ControlVoiceOverAudioInput(
		EMvIOCommand            in_eIOCommand,             // Specifies the control command to set or get.
		                                                   // keIOCommandGetRange is not supported in this case.
		EMvAudioCaptureChannel  in_eAudioCaptureChannel,   // Specifies the capture channel index.
		EMvAudioIOChannel       in_eAudioIOChannel,		   // Specifies the channel index to which the voice-over applies. 
		void*                   io_pParam,                 // Pointer to a parameter that contains the values to set or 
                                                         // to get. Can be either an enum of type of EMvOnOff.
		unsigned	long           in_ulSizeOfParam           // Specifies the size of the passed parameter.
		) = 0;

	//
	// Summary:
	//    Controls the voice-over on the playback channel. You can choose to output the playback, or
	//    the playback and input mix independently on the left and right side, respectively.
	// Return value:
	//    - Returns an error if the command failed or if there are incorrect parameters. 
	virtual HRESULT __stdcall ControlVoiceOverAudioOutput(
		EMvIOCommand            in_eIOCommand,             // Specifies the control command to set or get. 
                                                         // keIOCommandGetRange is not supported in this case.
		EMvAudioPlaybackChannel in_eAudioPlaybackChannel,  // Specifies the playback channel index.
		EMvAudioIOChannel       in_eAudioIOChannel,		   // Specifies the channel index that voice over is applied on.
		void*                   io_pParam,                 // Pointer to a parameter that contains values to set or to 
                                                         // get. Can be an enum of EMvOnOff.
		unsigned	long           in_ulSizeOfParam           // Specifies the size of the passed parameter.
		) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Creates the different playlist types.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvPlayListCreator : public IUnknown
{
	//
	// Summary:
	//    Creates a playlist that contains video elements only.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if a pointer is NULL.
	//    - MV_E_OUT_OF_MEMORY, if there is no more memory available for allocation.
	virtual HRESULT __stdcall CreateVideoPlayList
		(
		IMvPlayList ** out_ppIPLayList   // Pointer that receives the new playlist interface pointer.
		) = 0;

	//
	// Summary:
	//    Creates a playlist that contains audio elements only.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_POINTER, if a pointer is NULL.
	//    - MV_E_OUT_OF_MEMORY, if there is no memory available for allocation.
	virtual HRESULT __stdcall CreateAudioPlayList
		(
		IMvPlayList ** out_ppIPLayList   // Pointer that receives the new playlist interface pointer.
		) = 0;

	//
	// Summary:
	//    Creates a playlist that contains audio and video interleaved (AVI) elements only.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if a pointer is NULL.
	//    - MV_E_OUT_OF_MEMORY, if there is no more memory available for allocation.
	// Remarks:
	//    Only audio and video elements corresponding to the playlist video resolution and audio 
	//    channel type are accepted.
	virtual HRESULT __stdcall CreateAVInterleavedPlayList
		(
		IMvPlayList ** out_ppIPLayList   // Pointer that receives the new playlist interface pointer.
		) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This interface is used to set up a playlist.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvPlayList : public IUnknown
{
public:
	//
	// Summary:
	//    Retrieves the total playlist duration.
	// Return value:
	//    - Length of the playlist in frames.

	virtual uint64_t __stdcall GetDuration(void) = 0;

	//
	// Summary:
	//    Returns a playlist element according to a specified frame number.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if a pointers is NULL.
	//    - MV_E_ELEMENT_FOUND, if there is no element at the specified frame number.
	// Remarks:
	//    - The returned element reference count is incremented by one.

	virtual HRESULT  __stdcall GetSpecifiedElement
		(
		uint64_t              in_ui64FramePos,    // Frame position of the required element.
		IMvPlayListElement ** out_ppIElement      // Pointer that receives the element corresponding to the frame number.
		) = 0;

	//
	// Summary:
	//    Returns the playlist type (audio, AVI, graphic, or video).
	// Return value:
	//    - Returns the playlist type. 
	virtual EMvPlayListType __stdcall GetPlayListType(void) = 0;

	//
	// Summary:
	//    Indicates whether or not the seamless looping playlist property is enabled.
	// Return value:
	//    - TRUE, if seamless looping is desired.
	//    - FALSE, if seamless looping is not desired.
	// Remarks:
	//    - This property is implemented in the Flex Reader.
	virtual bool     __stdcall IsSeamlessLoopingEnabled(void) = 0;

	//
	// Summary:
	//    Enables or disables the seamless looping playlist property of the playlist. 
	// Remarks:
	//    This property is implemented in the Flex Reader.
	virtual void     __stdcall EnableSeamlessLooping
		(
		bool in_bEnable   // If true, seamless looping is required.
		) = 0;

	//
	// Summary:
	//    Inserts an element in the playlist at a specified frame number.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if a pointer is NULL.
	//    - MV_E_ALREADY_IN_USE, if the file reader is accessing the element.
	//    - MV_E_ELEMENT_FOUND, if there already is an element at the specified location in the playlist.
	//    - MV_E_INVALID_ELEMENT_TYPE, if the element is not of the right type for the playlist.
	virtual HRESULT  __stdcall InsertElement
		(
		IMvPlayListElement * in_pElement,      // Element to add to the playlist.
		uint64_t             in_ui64FramePos   // Frame position of the element in the playlist.
		) = 0;

	//
	// Summary:
	//    Appends an element to the end of the playlist.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_ALREADY_IN_USE, if the file reader is accessing the element.
	//    - MV_E_INVALID_ELEMENT_TYPE, if the element type is incorrect for the playlist.
	virtual HRESULT  __stdcall AppendElement
		(
		IMvPlayListElement * in_pElement // Inserts an element at the end of the playlist.
		) = 0;

	//
	// Summary:
	//    Removes an element from the playlist.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if a pointer is NULL.
	//    - MV_E_ALREADY_IN_USE, if the file reader is accessing the element.
	//    - MV_E_ELEMENT_NOT_FOUND, if the element is not in the playlist.
	virtual HRESULT  __stdcall RemoveElement(
		IMvPlayListElement * in_poElement   // Element to remove.
		) = 0;

	//
	// Summary:
	//    Removes all elements from the playlist.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	// Remarks:
	//    - The element used by the reader is cached so it is used until a new element is needed.
	virtual HRESULT  __stdcall RemoveAllElements(void) = 0;

	//
	// Summary:
	//    Moves an element from its current position to a new position.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_POINTER, if a pointer is NULL.
	//    - MV_E_ALREADY_IN_USE, if the file reader is accessing the element.
	//    - MV_E_ELEMENT_FOUND, if there already is an element at the specified location in the playlist.
	//    - MV_E_ELEMENT_LOST, an error occurred and the element is no longer in the playlist.
	virtual HRESULT  __stdcall MoveElement
		(
		IMvPlayListElement * in_poElement,        // Element to move.
		uint64_t             in_ui64NewPosition   // New position of the element.
		) = 0;

	//
	// Summary:
	//    Retrieves the next element of the playlist.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if a pointer is NULL.
	//    - MV_E_ELEMENT_NOT_FOUND, if there is no element in the playlist.
	// Remarks:
	//    - The returned element reference count is incremented by one.
	virtual HRESULT  __stdcall GetNextElement
		(
		IMvPlayListElement *  in_pIFromElement,   // Pointer to the interface of the element preceding
		                                          // to the required one.
		IMvPlayListElement ** out_ppINextElement  // Pointer to the required element interface.
		) = 0;

	//
	// Summary:
	//    Retrieves the previous element of the playlist.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if a pointer is NULL.
	//    - MV_E_ELEMENT_NOT_FOUND, if there is no element in the playlist.
	// Remarks:
	//    - The returned element reference count is incremented by 1.
	//    - If the in_pPrevElement parameter is NULL, the last element of the play list is returned.
	virtual HRESULT  __stdcall GetPreviousElement
		(
		IMvPlayListElement *  in_pIFromElement,   // Pointer to the interface of the element next to
		                                          // the required one.
		IMvPlayListElement ** out_ppIPrevElement  // Pointer to the required element interface.
		) = 0;

	//
	// Summary:
	//    Sets the time in playlist frames before the next played element in the playlist is opened. 
	// Return value:
	//    - MV_NOERROR, if completed successfully
	// Remarks:
	//		- A preroll of at least 2 seconds is recommended.
	//    - A higher preroll will ensure a smooth transition between two elements of the playlist,
	//		  preventing dropped frames between elements.
	//		- It will be impossible to change the next playlist element if it is already opened, so the higher
	//		  the preroll, the more time in advance is needed to make changes to the next playlist element.
	//    - An infinite preroll will open the next element as soon as possible after playback
	//		  of the current element has begun.
	//	   - A preroll of 0 will open the next playlist element only when the reader is ready to read from that element.
	virtual HRESULT  __stdcall SetNextElementOpeningPreroll
		(
		uint64_t in_ui64PrerollInFrames	// Number of frames before the next played element in the playlist is opened
                                       // (default = 0)
		) = 0;

	//
	// Summary:
	//    Returns the currently set time in playlist frames before the next played element in the playlist is opened. 
	// Return value:
	//    - Currently set time in playlist frames before the next played element in the playlist is opened.
	virtual uint64_t  __stdcall GetNextElementOpeningPreroll() = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Inserts a new playlist into an existing playlist.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvPlayList2 : public IMvPlayList
{
public:
	//
	// Summary:
	//    Inserts new elements into an existing playlist at a specified frame position.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_POSITION_INVALID, if a pointer is NULL.
	//    - MV_E_INVALID_ELEMENT_TYPE, if the new playlist doesn't match the playlist type of the existing playlist.
	virtual HRESULT  __stdcall InsertPlayList
		(
		IMvPlayList * in_pIPlayList,    // New playlist to be inserted.
		uint64_t      in_ui64FramePos,  // Frame position of the insertion.
		bool          in_bOverwrite     // If true, the playlist overwrites any elements it overlaps.
		) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Sets up a video playlist.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvVideoPlayList : public IUnknown
{
public:
	//
	// Summary:
	//    Creates a video playlist element.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if a pointer is NULL.
	//    - MV_E_OUT_OF_MEMORY, if there's no memory available for allocation.
	//    - MV_E_INVALID_PATH_SIZE, if the file name is bigger then MAX_PATH.
	// Remarks:
	//    - Only video playlists can create video elements.
	virtual HRESULT  __stdcall CreateElement
		(
		wchar_t                   * in_pwszFileName, // File name associated with the element.
		SMvVideoElementProperties * in_pProperties,  // Pointer to the properties of the created element.
		IMvPlayListElement       ** out_ppNewElement // Pointer to the newly created element interface.
		) = 0;

	//
	// Summary:
	//    Creates a video playlist element with index.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if a pointer is NULL.
	//    - MV_E_OUT_OF_MEMORY, if there's no memory available for allocation.
	//    - MV_E_INVALID_PATH_SIZE, if the file name is bigger then MAX_PATH.
	// Remarks:
	//    - Only video playlists can create video elements.
	virtual HRESULT  __stdcall CreateElementWithIndex
		(
		wchar_t                   * in_pwszFileName,       // File name associated with the element.
		wchar_t                   * in_pwszFileNameIndex,  // File name associated with the element's video index.
		SMvVideoElementProperties * in_pProperties,        // Pointer to the properties of the created element.
		IMvPlayListElement       ** out_ppNewElement       // Pointer to the newly created element interface.
		) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Sets up an audio playlist.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvAudioPlayList : public IUnknown
{
public:
	//
	// Summary:
	//    Creates an audio playlist element.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_POINTER, if a pointer is NULL.
	//    - MV_E_OUT_OF_MEMORY, if there is no memory available for allocation.
	//    - MV_E_INVALID_PATH_SIZE, if the file name is bigger than MAX_PATH.
	// Remarks:
	//    - Only audio playlists can create audio elements. 
	virtual HRESULT  __stdcall CreateElement
		(
		wchar_t                   * in_pwszFileName, // File name associated with the element.
		SMvAudioElementProperties * in_pProperties,  // Pointer to the properties of the element to create.
		IMvPlayListElement       ** out_ppNewElement // Pointer to the newly created element interface.
		) = 0;

	//
	// Summary:
	//    Creates an audio playlist element with index.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_POINTER, if a pointer is NULL.
	//    - MV_E_OUT_OF_MEMORY, if there is no memory available for allocation.
	//    - MV_E_INVALID_PATH_SIZE, if the file name is bigger than MAX_PATH.
	// Remarks:
	//    - Only audio playlists can create audio elements. 
	virtual HRESULT  __stdcall CreateElementWithIndex
		(
		wchar_t                   * in_pwszFileName,       // File name associated with the element.
		wchar_t                   * in_pwszFileNameIndex,  // File name associated with the element's audio.
		SMvAudioElementProperties * in_pProperties,        // Pointer to the properties of the element to create.
		IMvPlayListElement       ** out_ppNewElement       // Pointer to the newly created element interface.
		) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Sets up an AVI (audio/video interleaved) playlist.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvAVInterleavedPlayList : public IUnknown
{
public:
	//
	// Summary:
	//    Creates an AVI (audio/video interleaved) playlist element.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if a pointer is NULL.
	//    - MV_E_OUT_OF_MEMORY, if there is no memory available for allocation.
	//    - MV_E_INVALID_PATH_SIZE, if the filename is bigger then MAX_PATH.
	// Remarks:
	//    - Only AVI playlist can create AVI elements.
	virtual HRESULT  __stdcall CreateElement
		(
		wchar_t                           * in_pwszFileName,  // File name associated with the element.
		SMvAVInterleavedElementProperties * in_pProperties,   // Pointer to the properties of the element to create.
		IMvPlayListElement               ** out_ppNewElement  // Pointer to the newly created element interface.
		) = 0;

	//
	// Summary:
	//    Creates an AVI (audio/video interleaved) playlist element with index.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if a pointer is NULL.
	//    - MV_E_OUT_OF_MEMORY, if there is no memory available for allocation.
	//    - MV_E_INVALID_PATH_SIZE, if the filename is bigger then MAX_PATH.
	// Remarks:
	//    - Only AVI playlist can create AVI elements.
	virtual HRESULT  __stdcall CreateElementWithIndex
		(
      wchar_t             * in_pwszFileName,                // File name associated with the element.
      wchar_t             * in_pwszFileNameVideoIndex,      // File name associated with the element's video index.
      wchar_t             * in_pwszFileNameAudioIndex,      // File name associated with the element's audio index.
      SMvAVInterleavedElementProperties * in_pProperties,   // Pointer to the properties of the element to create.
      IMvPlayListElement ** out_ppNewElement                // Pointer to the newly created element interface.
		) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Initializes the common parameters of an element.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvPlayListElement : public IUnknown
{
public:    
	//
	// Summary:
	//    Retrieves the file name associated with the element.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if a pointer is NULL.
	// Remarks:
	//    - The size of the parameter can have a maximum of MAX_PATH characters.
	virtual HRESULT  __stdcall GetFileName
		(
		wchar_t * out_pwszFileName    // Pointer to a string that receives the file name.
		) = 0;

	//
	// Summary:
	//    Retrieves the custom file I/O interface used to access the file of the element.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if a pointer is NULL.
	// Remarks:
	//    - The file reader uses this interface to access the file of the element.  If the parameter 
	//      is NULL, the Win32 unbuffered I/O methods are used.
	virtual HRESULT  __stdcall GetCustomFileIO
		(
		IMvCustomFileSystemIO ** out_ppIFileSystemIO // Pointer that receives the custom I/O interface pointer.
		) = 0;

	//
	// Summary:
	//    Indicates that the file is being written to by another process.
	// Return value:
	//    - True, if the file is incomplete and there is another process writing to it. 
	//    - False, if the file is complete and no other process is writing to it.
	// Remarks:
	//    - This option indicates to the file reader that the file header is changing and that it 
	//      must be re-read at regular intervals.
	virtual bool __stdcall IsRemoteTimeDelay(void) = 0;

	//
	// Summary:
	//    Returns the element start position in the playlist.
	// Return value:
	//    - Frame position in the playlist.
	virtual uint64_t __stdcall GetStartPosition(void) = 0;

	//
	// Summary:
	//    Retrieves the number of play frames of the element.
	// Return value:
	//    - Number of frames that the file reader returns for this element.
	// Remarks:
	//    - The frame count is for interlaced or progressive files.
	virtual uint64_t __stdcall GetDuration(void) = 0;

	//
	// Summary:
	//    Sets the frame duration of the element.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_ALREADY_IN_USE, if the file reader is accessing the element.
	//    - MV_E_ELEMENT_FOUND, if there already is an element at the specified location in the playlist.
	// Remarks:
	//    - When changing the duration of an element, the application must ensure that there is enough
	//     space in the playlist.
	virtual HRESULT  __stdcall SetDuration
		(
		uint64_t in_ui64FrameDuration // Frame count.
		) = 0;

	//
	// Summary:
	//    Retrieves the element start frame inside the file.
	// Return value:
	//    - Trim-in frame position in the file.
	virtual uint64_t __stdcall GetTrimInPosition(void) = 0;

	//
	// Summary:
	//    Sets the element start frame inside the file.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_ALREADY_IN_USE, if the file reader is accessing the element. 
	// Remarks:
	//    - When the Trim-in position is greater than the Trim-out position, the file is accessed in
	//      reverse.
	//    - The Trim-out position can be past the end of the file.
	virtual HRESULT  __stdcall SetTrimInPosition
		(
		uint64_t in_ui64FramerTrimIn  // Frame number.
		) = 0;

	//
	// Summary:
	//    Retrieves the element's end frame inside the file.
	// Return value:
	//    - Trim-out frame position in the file.
	virtual uint64_t __stdcall GetTrimOutPosition(void) = 0;

	//
	// Summary:
	//    Sets the element's end frame inside the file.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_ALREADY_IN_USE, if the file reader is accessing the element.
	// Remarks:
	//    - When the Trim-out position is less than the Trim-in position, the file is accessed in
	//      reverse.
	//    - The Trim-out position can be past the end of the file.
	virtual HRESULT  __stdcall SetTrimOutPosition
		(
		uint64_t in_ui64FramerTrimOut // Frame number.
		) = 0;

	//
	// Summary:
	//    Prevents modifications to the element.
	// Return value:
	//       - MV_NOERROR, if completed successfully.
	// - MV_E_ALREADY_IN_USE, if the Flex File Reader is accessing the element.
	// Remarks:
	//    - This method prevents the Flex File Reader, or any other thread to access the element until a
	//      call to IMvPlayListElement::ReleaseLock is made.
	//    - If the file reader tries to access the element that is being modified, it returns the 
	//      MV_E_ELEMENT_IN_USE error.
	virtual HRESULT  __stdcall AcquireLock(void) = 0;

	//
	// Summary:
	//    Releases the lock so that the element can be modified.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_ELEMENT_NOT_LOCKED, if the element is not in the modification state.
	virtual HRESULT  __stdcall ReleaseLock(void) = 0;

	//
	// Summary:
	//    Retrieves the Flex clip reader CLSID if it exists.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	virtual HRESULT  __stdcall GetCLSID
		(
		CLSID * out_pclsid   // Pointer that receives the value of the CLSID.
		) = 0;

	//
	// Summary:
	//    Retrieves the file name associated with the video index file.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if a pointer is NULL.
	// Remarks:
	//    - The size of the parameter can have a maximum of MAX_PATH characters.
	virtual HRESULT  __stdcall GetFileNameVideoIndex
		(
		wchar_t * out_pwszFileName    // Pointer to a string that receives the file name.
		) = 0;

	//
	// Summary:
	//    Retrieves the file name associated with the audio index file.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if a pointer is NULL.
	// Remarks:
	//    - The size of the parameter can have a maximum of MAX_PATH characters.
	virtual HRESULT  __stdcall GetFileNameAudioIndex
		(
		wchar_t * out_pwszFileName    // Pointer to a string that receives the file name.
		) = 0;

	//
	// Summary:
	//    Tells the Flex File Reader which codec should be used to decompressed the media.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	// Remarks:
	//    - This method allows the user application to choose which codec should be used to decompress the media and is 
	//       used only when more than one codecs are available for a specific compression format.
	//    - For example, if the profile supports an H.264 hardware codec you could use this method to choose between 
   //      the hardware and software H.264 implementation.
	virtual HRESULT __stdcall SetVideoDecompressionCodec( const CLSID* in_pclsidCodec ) = 0;
	virtual HRESULT __stdcall SetAudioDecompressionCodec( const CLSID* in_pclsidCodec ) = 0;

	//
	// Summary:
	//    Retrieves the codec that will be used to decompress the media.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	// Remarks:
	//    - This will return the value programmed by SetDecompressionCodec.
	//    - Internally the CLSID will be set to GUID_NULL if SetDecompressionCodec was not previously called.
	virtual HRESULT __stdcall GetVideoDecompressionCodec( CLSID* out_pclsidCodec ) = 0;
	virtual HRESULT __stdcall GetAudioDecompressionCodec( CLSID* out_pclsidCodec ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Sets up a video-only playlist element.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvVideoPlayListElement : public IUnknown
{
public:
	//
	// Summary:
	//    Sets the type of algorithm to use when doing slow motion.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_ALREADY_IN_USE, if the file reader is accessing the element.
	// Remarks:
	//    - The file reader does slow motion when the frame duration of an element is smaller than
	//      the frame count indicated by the Trim-in and Trim-out attributes of the element.
	virtual HRESULT __stdcall SetSlowMotionType
		(
		EMvSlowMotionType in_eType // Indicates what type of slow motion algorithm is used by the file reader.
		) = 0;

	//
	// Summary:
	//    Retrieves the type of algorithm to use when doing slow motion.
	// Return value:
	//    - The slow motion type to be used.
	// Remarks:
	//    - See the remarks for IMvVideoPlayListElement::SetSlowMotionType().
	virtual EMvSlowMotionType __stdcall GetSlowMotionType(void) = 0;

	//
	// Summary:
	//    Sets the output position of the video surface.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if a pointers is NULL.
	//    - MV_E_ALREADY_IN_USE, if the file reader is accessing the element.
	// Remarks:
	//    - The file reader calls the IMvSurface::SetGraphicPosition() method with a position, so
	//      that the surface returned has the position properly set.
	virtual HRESULT __stdcall SetOutputPosition
		(
		SMvPointF * in_psPosition  // Pointer to the position structure.
		) = 0;

	//
	// Summary:
	//    Retrieves the output position of the video surface.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if a pointer is NULL.
	//    - MV_E_ALREADY_IN_USE, if the file reader is accessing the element.
	// Remarks:
	//    - See the remarks for IMvVideoPlayListElement::SetOutputPosition().
	virtual HRESULT __stdcall GetOutputPosition
		(
		SMvPointF * out_psPosition // Pointer to the position structure.
		) = 0;

	//
	// Summary:
	//    Retrieves the zero-based stream ID to read - in the case of multiple stream files.
	// Return value:
	//    - ID of the stream to read.
	virtual unsigned long __stdcall GetVideoStreamToRead() = 0;

	//
	// Summary:
	//    Determines whether or not to apply aspect ratio compensation.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	// Remarks:
	virtual HRESULT  __stdcall SetAspectRatioCompensation
		(
		bool in_bSet      // If true, applies an aspect ratio compensation.
	   ) = 0;

	//
	// Summary:
	//    Gets the setting for whether or not aspect ratio compensation is to be applied.
	// Return value:
	//    - True, if aspect ratio compensation is to be applied.
	//    - False, if aspect ratio compensation is not to be applied.
	// Remarks:
	//    - The size of the parameter can have a maximum of MAX_PATH characters.
	virtual bool  __stdcall GetAspectRatioCompensation(void) = 0;

   //
   // Summary:
   //    Sets the location of the time code.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_NOT_IMPLEMENTED, if in_eTimeCodeLocation >= keMvTimecodeLocationLast.
   virtual HRESULT __stdcall SetTimeCodeLocation
      (
      EMvTimecodeLocation in_eTimeCodeLocation // Indicates where to find the time code.
      ) = 0;

   //
   // Summary:
   //    Gets the location of the time code.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   virtual HRESULT __stdcall GetTimeCodeLocation
	   (
	   EMvTimecodeLocation *out_peTimeCodeLocation // Pointer to the location of the time code.
	   ) = 0;


   //
   // Summary:
   //    Sets the location of the time code.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_NOT_IMPLEMENTED, if in_eVancLocation >= keMvVancLocationLast.
   virtual HRESULT __stdcall SetVANCLocation
      (
      EMvVANCLocation in_eVancLocation // Indicates where to find the time code.
      ) = 0;

   //
   // Summary:
   //    Gets the location of the time code.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   virtual HRESULT __stdcall GetVANCLocation
	   (
	   EMvVANCLocation *out_peVancLocation // Pointer to the location of the time code.
	   ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Initializes optional parameters of a playlist element.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvPlayListElementOptions : public IUnknown
{
public:
   //
   // Summary:
   //    Enables an optimized search for the Random Index Pack (RIP) in an MXF file. 
   // Return value:
   //    - MV_NOERROR, if completed successfully
   // Note:
   //    - Most MXF files terminate with an optional RIP. Trying to determine whether or not
	//      a file contains this may take time in a corrupted file unless this search is enabled.
   //
   virtual HRESULT __stdcall EnableMXFFooterSearchOptimization
      (
      bool in_bEnable // If true, enables searching for the RIP in a corrupted MXF file. The default is false.
      ) = 0;

};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Sets up an audio-only playlist element.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvAudioPlayListElement : public IUnknown
{
public:
	//
	// Summary:
	//    Enables or disables the modification of the audio sample buffer fade-in attribute.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_ALREADY_IN_USE, if the file reader is accessing the element. 
	// Remarks:
	//    - The first audio sample buffer of the element has the fade-in attribute enabled.
	virtual HRESULT __stdcall EnableFadeIn
		(
		bool in_bEnable    // If true, enables the fade-in attribute.
		) = 0;

	//
	// Summary:
	//    Indicates whether fade-in attribute modification is applied.
	// Return value:
	//    - True, if fade-in modification is applied. 
	//    - False, if fade-in modification is not applied.
	// Remarks:
	//    - See the remarks for IMvAudioPlayListElement::EnableFadeIn.
	virtual bool __stdcall HasFadeIn(void) = 0;

	//
	// Summary:
	//    Enables or disables the modification of the audio sample buffer fade-out attribute.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_ALREADY_IN_USE, if the file reader is accessing the element. 
	// Remarks:
	//    - The last audio sample buffer of the element has the fade-out attribute enabled.
	virtual HRESULT __stdcall EnableFadeOut
		(
		bool in_bEnable   // If true, enables the fade-out attribute.
		) = 0;

	//
	// Summary:
	//    Indicates whether fade-out attribute modification is applied.
	// Return value:
	//    - True, if fade-out modification is applied. 
	//    - False, if fade-out modification is not applied.
	// Remarks:
	//    - See the remarks for IMvAudioPlayListElement::EnableFadeOut.
	virtual bool __stdcall HasFadeOut(void) = 0;

	//
	// Summary:
	//    Retrieves the zero-based stream ID to read - in the case of multiple stream files.
	// Return value:
	//    - ID of the stream to read.
	virtual unsigned long __stdcall GetAudioStreamToRead() = 0;

   //
   // Summary:
   //    Sets the audio stream identifier index value and which audio streams to play back.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_NOT_IMPLEMENTED, if in_ui32Index > 0. 
   // Remarks:
   //    - At present, the number of audio streams must be less than or equal to 64. Therefore, in_ui32Index must be set to 0.
   //    - Each stream can contain 1, 2, 4, 8, or 16 channels.
   //    - The number of channels per stream must be the same for all audio streams in the file.
   //    - The minimum selection is one stream. You cannot play back specific channels from a stream.
   //    - The total number of channels that can be played back is 2, 4, 8, or 16.
   // Example:
   //    To play back streams 0, 1, 2, and 4, call SetAudioStreamIdentifier(0,0x00000017). <p> <b> Note: </b> The hexadecimal value 0x00000017 corresponds to the binary value 10111.
   virtual HRESULT __stdcall SetAudioStreamIdentifier
      ( 
      uint32_t in_ui32Index,                    // Index value for the group of audio streams. <p>
												// <b> Note: </b> Streams are indexed in groups of 64. This means that in_ui32Index is 0 for streams 0 to 63, 1 for streams 64 to 127, and so on. 
      uint64_t in_ui64AudioStreamIdentifier     // Specifies the particular streams to be played back.
      ) = 0;

   //
   // Summary:
   //    Gets the total number of audio stream identifiers.
   // Return value:
   //	 - uint32_t, the total number of audio stream identifiers. 
   // Remarks:
   //	 - At present, returns 1 only.
   //    - Not fully implemented yet.
   virtual uint32_t __stdcall GetNumberOfAudioStreamIdentifiers() = 0;

   //
   // Summary:
   //    Gets the audio stream identifier.
   // Return value:
   //    - At present, returns index 0 only.
   // Remarks:
   //    - Not fully implemented yet.
   virtual uint64_t __stdcall GetAudioStreamIdentifier
	   ( 
	   uint32_t in_ui32Index	// Index value for the group of audio streams.
	   ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Sets up an AVI playlist element.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvAVInterleavedPlayListElement : public IUnknown
{
public:
	//
	// Summary:
	//    Sets the type of algorithm to use when doing slow motion.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_ALREADY_IN_USE, if the file reader is accessing the element.
	// Remarks:
	//    - The file reader does slow motion when the frame duration of an element is smaller than 
	//      the frame count indicated by the Trim-in and Trim-out attributes of the element.
	virtual HRESULT __stdcall SetSlowMotionType
		(
		EMvSlowMotionType in_eType // Indicates what type of slow motion algorithm is being used by the file reader.
		) = 0;

	//
	// Summary:
	//    Retrieves the type of algorithm to use when doing slow motion.
	// Return value:
	//    - The type of slow motion that is being requested.
	// Remarks:
	//    - See the remarks for IMvAVInterleavedPlayListElement::SetSlowMotionType().
	virtual EMvSlowMotionType __stdcall GetSlowMotionType(void) = 0;

	//
	// Summary:
	//    Sets the image position of the video surface.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if a pointers is NULL.
	//    - MV_E_ALREADY_IN_USE, if the file reader is accessing the element.
	// Remarks:
	//    - The file reader calls the IMvSurface::SetGraphicPosition() method with the position, so 
	//      that the surface returned is set to the proper position.
	virtual HRESULT __stdcall SetOutputPosition
		(
		SMvPointF * in_psPosition  // Pointer to the position structure.
		) = 0;

	//
	// Summary:
	//    Retrieves the image position of the video surfaces.
	// Return value:
	//    - MV_NOERROR, if completed successfully
	//    - MV_E_INVALID_POINTER, if a pointer is NULL.
	//    - MV_E_ALREADY_IN_USE, if the file reader is accessing the element.
	// Remarks:
	//    - See the remarks for IMvAVInterleavedPlayListElement::SetOutputPosition.
	virtual HRESULT __stdcall GetOutputPosition
		(
		SMvPointF * out_psPosition // Pointer to the position structure.
		) = 0;

	//
	// Summary:
	//    Enables/disables the modification of the audio sample buffer fade-in attribute.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_ALREADY_IN_USE, if the file reader is accessing the element. 
	// Remarks:
	//    - The first audio sample buffer of the element has the fade-in attribute enabled.
	virtual HRESULT __stdcall EnableFadeIn
		(
		bool in_bEnable   // If true, enables the fade-in attribute.
		) = 0;

	//
	// Summary:
	//    Indicates whether fade-in attribute modification is applied.
	// Return value:
	//    - True, if the fade-in modification is applied. 
	//    - False, if the fade-in modification is not applied.
	// Remarks:
	//    - See the remarks for IMvAudioPlayListElement::EnableFadeIn.
	virtual bool __stdcall HasFadeIn(void) = 0;

	//
	// Summary:
	//    Enables/disables the modification of the audio sample buffer fade-out attribute.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_ALREADY_IN_USE, if the file reader is accessing the element. 
	// Remarks:
	//    - The last audio sample buffer of the element has the fade-out attribute enabled.
	virtual HRESULT __stdcall EnableFadeOut
		(
		bool in_bEnable   // If true, enables the fade-out attribute.
		) = 0;

	//
	// Summary:
	//    Indicates whether fade-out attribute modification is applied.
	// Return value:
	//    - True, if fade-out modification is applied. 
	//    - False, if fade-out modification is not applied.
	// Remarks:
	//    - See the remarks for IMvAudioPlayListElement::EnableFadeOut.
	virtual bool    __stdcall HasFadeOut(void) = 0;

	//
	// Summary:
	//    Gets the zero-based stream ID to read - in the case of multiple stream files.
	// Return value:
	//    - Returns the ID of the stream to read.
	virtual unsigned long __stdcall GetVideoStreamToRead() = 0;

	//
	// Summary:
	//    Gets the zero-based stream ID to read - in the case of multiple stream files.
	// Return value:
	//    - Returns the ID of the stream to read.
	virtual unsigned long __stdcall GetAudioStreamToRead() = 0;

	//
	// Summary:
	//    Sets whether or not to apply aspect ratio compensation.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	// Remarks:
	virtual HRESULT  __stdcall SetAspectRatioCompensation
		(
		bool in_bSet      // If true, applies an aspect ratio compensation.
		) = 0;

	//
	// Summary:
	//    Gets the setting for whether or not to apply aspect ratio compensation.
	// Return value:
	//    - True, if aspect ratio compensation is to be applied.
	//    - False, if aspect ratio compensation is not to be applied.
	// Remarks:
	//    - The size of the parameter can have a maximum of MAX_PATH characters.
	virtual bool  __stdcall GetAspectRatioCompensation(void) = 0;

   //
   // Summary:
   //    Sets the audio stream identifier index value and which audio streams to play back.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_NOT_IMPLEMENTED, if in_ui32Index > 0. 
   // Remarks:
   //    - At present, the number of audio streams must be less than 64. Therefore, in_ui32Index must be set to 0.
   //    - Each stream represents one audio track, and can contain 1, 2, 4, 8, or 16 channels.
   //    - The number of channels per stream must be the same for all audio streams in the file.
   //    - The minimum selection is one stream. You cannot play back specific channels from a stream.
   //    - The total number of channels that can be played back is 2, 4, 8, or 16.
   // Example:
   //    To play back streams 0, 1, 2, and 4, call SetAudioStreamIdentifier(0,0x00000017). <p> <b> Note: </b> The hexadecimal value 0x00000017 corresponds to the binary value 10111.
   virtual HRESULT __stdcall SetAudioStreamIdentifier
      ( 
      uint32_t in_ui32Index,                    // Index value for the group of audio streams.<p>
												// <b> Note: </b> Streams are indexed in groups of 64. This means that in_ui32Index is 0 for streams 0 to 63, 1 for streams 64 to 127, and so on. 
      uint64_t in_ui64AudioStreamIdentifier     // Specifies the particular streams to be played back.
      ) = 0;

   //
   // Summary:
   //    Gets the total number of audio stream identifiers.
   // Return value:
   //	 - uint32_t, the total number of audio stream identifiers. 
   // Remarks:
   //    - At present, returns 1 only.
   //    - Not fully implemented yet.
   virtual uint32_t __stdcall GetNumberOfAudioStreamIdentifiers() = 0;

   //
   // Summary:
   //    Gets the audio stream identifier.
   // Return value:
   //    - At present, returns index 0 only.
   // Remarks:
   //    - Not fully implemented yet.
   virtual uint64_t __stdcall GetAudioStreamIdentifier
	   ( 
	   uint32_t in_ui32Index	// Index value for the group of audio streams.
	   ) = 0;

   //
   // Summary:
   //    Sets the location of the time code.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_NOT_IMPLEMENTED, if in_eTimeCodeLocation >= keMvTimecodeLocationLast.
   // Remarks:
   //    - 
   virtual HRESULT __stdcall SetTimeCodeLocation
      (
      EMvTimecodeLocation in_eTimeCodeLocation // Indicates where to find the time code.
      ) = 0;

   //
   // Summary:
   //    Gets the location of the time code.
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   virtual HRESULT __stdcall GetTimeCodeLocation
	   (
	   EMvTimecodeLocation *out_peTimeCodeLocation // Pointer to the location of the time code.
	   ) = 0;


   //
   // Summary:
   //    Sets the location of the VANC data.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_NOT_IMPLEMENTED, if in_eVancLocation >= keMvVancLocationLast.
   virtual HRESULT __stdcall SetVANCLocation
      (
      EMvVANCLocation in_eVancLocation // Indicates where to find the VANC data.
      ) = 0;

   //
   // Summary:
   //    Gets the location of the VANC data.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   virtual HRESULT __stdcall GetVANCLocation
	   (
	   EMvVANCLocation *out_peVancLocation // Pointer to the location of the VANC data.
	   ) = 0;
};

// DOM-IGNORE-BEGIN
struct SMvFileInfo;
// DOM-IGNORE-END

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Retrieves file information on any type of audio, video, MGF, or
//    GFX file.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvFlexFileInformation: public IUnknown
{
public:
	//
	// Summary:
	//    Retrieves the file header information.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_STRUCTURE_SIZE, if the size field of the structure does not match the expected size.
	//    - MV_E_INVALID_POINTER, if one of the pointer parameters is NULL.
	//    - MV_E_FILE_NOT_FOUND, if the file does not exist.
	virtual HRESULT __stdcall GetFileInformation
		(
		const wchar_t     * in_pkwszFileName,  // Name of the file to retrieve information from.
		SMvFileInfo       * io_psInfo          // Structure that will be filled with the file information.
		                                       // The size field must be initialized properly.
		) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This interface is an extension of IMvFlexFileInformation. It behaves the same, but with additional support 
//	  for a CLSID to be passed in a parameter to allow the interface to support Flex Custom Clip Readers. 
//	  Callers can use this interface to retrieve the file information of any custom Flex Clip Reader module.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvFlexFileInformation2: public IUnknown
{
public:
	//
	// Summary:
	//    Retrieves the file header information.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_STRUCTURE_SIZE, if the size field of the structure does not match the expected size.
	//    - MV_E_INVALID_POINTER, if one of the pointer parameters is NULL.
	//    - MV_E_FILE_NOT_FOUND, if the file does not exist.
	virtual HRESULT __stdcall GetFileInformation
		(
		const wchar_t     * in_pkwszFileName,   // Name of the file to retrieve information from.
		SMvFileInfo       * io_psInfo,         // Structure that will be filled with the file information. The size field must
                                             // be initialized properly.
		const CLSID       * in_pclsidFlexClip  // Optional: Class identifier of the Flex Clip Reader component to get the file
                                             // information from.
		) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This interface is an extension of IMvFlexFileInformation. It is primarily used to 
//    open an MPEG-2 IBP file with an associated index file. The GetFileInformation 
//    method for this interface includes additional arguments for support of audio and video MPEG-2 IBP index files, 
//    as well as an additional output argument to indicate the preferred Flex Clip Reader for <I>.mov</I> files.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvFlexFileInformation3: public IUnknown
{
public:
	//
	// Summary:
	//    Retrieves the file header information.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_STRUCTURE_SIZE, if the size field of the structure does not match the expected size.
	//    - MV_E_INVALID_POINTER, if one of the pointer parameters is NULL.
	//    - MV_E_FILE_NOT_FOUND, if the file does not exist.
	virtual HRESULT __stdcall GetFileInformation
		(
		const wchar_t     * in_pkwszFileName,           // Name of the file to retrieve information from.
		const wchar_t     * in_pkwszFileNameIndexVideo, // Optional: Video index to retrieve information from.
		const wchar_t     * in_pkwszFileNameIndexAudio, // Optional: Audio index to retrieve information from.
		SMvFileInfo       * io_psInfo,                  // Structure that will be filled with the file information. The size 
                                                      // field must be initialized properly.
		const CLSID       * in_pclsidFlexClip,          // Optional: Class identifier of the Flex Clip Reader component to get
                                                      // the file information from.
		CLSID             * out_pclsidPreferredClipReader     // Optional: If more than one Flex Clip Reader can read the specified
                                                            // file, this will specify the most efficient reader's CLSID
		) = 0;


	//
	// Summary:
	//    Obtains the nearest possible truncation point in a file - mostly used for GOP based material.
	// Return value:
	//    - MV_TRUE, if suggested position is a good truncation point
	//    - MV_FALSE, if suggested position is not a good truncation point, the returning parameters 1 and 2 will
   //      contain the previous and next possible truncation points
	//    - MV_E_INVALID_STRUCTURE_SIZE, if the size field of the structure does not match the expected size.
	//    - MV_E_INVALID_POINTER, if one of the pointer parameters is NULL.
	//    - MV_E_FILE_NOT_FOUND, if the file does not exist.
	virtual HRESULT __stdcall CheckInPointForTruncation
		(
		const wchar_t           * in_pkwszFileName,     // Name of the file to retrieve information from.
		SMvFlexPositionsInquiry * in_pInquiringPosition // Structure that is filled with the inquiring position and the
                                                      // returning positions. The two returning positions are for
                                                      // previous and next possible truncation points respectively.
		) = 0;



};

interface IMvDescriptiveMetadata;
//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This interface is an extension of the IMvFlexFileInformation3 interface, and provides methods to open and close 
//    the IMvDescriptiveMetadata interface.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvFlexFileInformation4: public IMvFlexFileInformation3
{
public:

   
   //
   // Summary:
   //    Opens a file to access descriptive metadata interfaces.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_NO_RESOURCE_FOUND, if the previous file is still open.
   // Remarks:
	//    - When you are done accessing descriptive metadata, access to the descriptive metadata must be closed using
   //      the method CloseFileForDescriptiveMetadata() in order to free resources.
   virtual HRESULT __stdcall OpenFileForDescriptiveMetadata
   (
		const wchar_t           * in_pszFileName,                // Pointer to the string containing the name of the
                                                               // descriptive metadata file.
      IMvDescriptiveMetadata ** out_ppIMvDescriptiveMetadata   // Pointer that receives the descriptive metadata
                                                               // interface.
   ) = 0;

   //
   // Summary:
   //    Closes access to the descriptive metadata of a file.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CloseFileForDescriptiveMetadata() = 0;


};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This interface is used by the mvMpegStream codec module to abstract a caller-allocated memory buffer.
// Description:
//    The GOP buffer memory layout is as follow:
// <code>
// \+--------+ --\> gop start alignment
// | header |
// \+--------+ --\> gop start + header size
// |        |
// |  gop0  |
// |        |
// \+--------+ --\> gop start + header size + gop size
// |padding |
// \+--------+ --\> Align( gop start + header size + gop size )
// </code>
//
// Remarks:
//    - The alignment and header size parameters can be used to ensure that the compressed MPEG 
//      stream respects caller-specific memory organization requirements. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvMpegStreamBuffer : public IUnknown
{
	//
	// Summary:
	//    A caller-implemented method that retrieves the GOP start alignment requirement inside the stream. 
	// Return value:
	//    - Returns the alignment value; 
	//    - Returns zero if no alignment is specified.
	// Remarks:
	//    - If you do not require any GOP start boundary alignments, this method can be implemented 
	//      to return zero.
	virtual unsigned long __stdcall GetGopStartAlignment() = 0;

	//
	// Summary:
	//    This caller-implemented method retrieves the GOP size alignment requirement inside the stream. 
	// Return value:
	//    - Returns the alignment value.
	//    - Zero, if no alignment is specified.
	// Remarks:
	//    - If you do not require any GOP size boundary alignments, this method can be implemented 
	//      to return zero.
	virtual unsigned long __stdcall GetGopSizeAlignment() = 0;

	//
	// Summary:
	//    This caller-implemented method retrieves the GOP header size requirement inside the stream. 
	// Return value:
	//    - Returns the size value.
	//    - Returns zero if no header size is required.
	// Remarks:
	//    - If you do not require any GOP header size, this method can be implemented to return zero. 
	//    - mvMpegStream skips the specified number of bytes at the beginning of each GOP encoding 
	//      session, so you can write a GOP header if desired.
	virtual unsigned long __stdcall GetGopHeaderSize() = 0;

	//
	// Summary:
	//    Retrieves the total memory size abstracted by the buffer object, in bytes. 
	// Return value:
	//    - MV_NOERROR, the method succeeded.
	// Remarks:
	//    - It is critical that this method succeeds. Each IMvMpegStreamBuffer should contain a 
	//      memory buffer area. 
	virtual HRESULT __stdcall GetBuffer
		(
		unsigned char** out_ppucBuffer   // Address of a pointer corresponding to the memory buffer's first byte. 
		) = 0;

	//
	// Summary:
	//    Retrieves the total memory size abstracted by the buffer object, in bytes. 
	// Return value:
	//    Returns the size value in bytes.
	// Remarks:
	//    - Returns the total number of bytes available in the memory buffer object.
	virtual unsigned long __stdcall GetSize() = 0;

	//
	// Summary:
	//    Sets the number of bytes used by the streaming module.  This is for the caller's 
	//    convenience.
	virtual void __stdcall SetUsedSize
		(
		unsigned long in_ulSize    // Size in bytes consumed by the memory buffer.
		) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This interface is used by the mvMpegStream codec module to obtain memory buffers from the caller.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvMpegStreamMemoryProvider : public IUnknown
{
	//
	// Summary:
	//    This caller-implemented method retrieves a memory buffer to be used by the encoding process. 
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	// Remarks:
	//    - It is critical for the mvMpegStream's encoding process that this method succeeds. 
	//    - This method should return as fast as possible since it's holding down the encoding threads. 
	//    - The in_ulSizeInBytes is the <B>minimum</B> buffer size needed by mvMpegStream to successfully 
	//      encode. If SMvMpegStreamInitialize::bOneGopPerBuffer is set to false then mvMpegStream 
	//      will gradually consume this memory buffer until it can no longer provide a large enough 
	//      memory block. For example, if in_ulSizeInBytes is 1MB, you can allocate a 100MB buffer 
	//      and pass it in out_ppIBuffer. This buffer will be filled by mvMpegStream, and its memory 
	//      area will contain GOPs ~100MB in total size. 
	//    - This interface allows you to provide contiguous memory buffers to mvMpegStream that can
	//      be directly written to disk, streamed, etc. without the need for further memory copying, 
	//      since all the alignment and padding requirements are covered by mvMpegStream. Alignment 
	//      and padding requirements are specified by the caller-implemented IMvMpegStreamMemoryBuffer 
	//      interface.
	//    - This method is implemented by the caller.
	virtual HRESULT __stdcall GetBufferWithSize
		( 
		unsigned long          in_ulSizeInBytes,  // Minimum buffer size required by mvMpegStream to
		                                          // pursue the encoding process.
		IMvMpegStreamBuffer ** out_ppIBuffer      // Pointer to the address of the IMvMpegStreamBuffer interface that 
                                                // receives the memory buffer abstractor object. 
		) = 0;

	//
	// Summary:
	//    Confirms that a GOP is done encoding so that the memory provider can adjust its contiguous memory.
	// Remarks:
	//    - This method is implemented by the caller.
	virtual HRESULT __stdcall GopEncodeCompleted
		(
		IMvMpegStreamGop * in_pIGop   
		) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This interface is used by the mvMpegStream codec module to abstract a group of pictures.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvMpegStreamGop : public IUnknown
{
	//
	// Summary:
	//    Retrieves the total GOP size in bytes. 
	// Return value:
	//    Returns the size value in bytes.
	// Remarks:
	//    - Returns the total number of bytes in the GOP.
	//    - Accessed by the caller.
	virtual unsigned long __stdcall GetSizeInBytes() = 0;

	// Summary:
	//    Retrieves the GOP buffer's address pointer. 
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_MPS_GOP_LOCKED, if the GOP is currently being written to by the encoder.
	//    - MV_E_MPS_GOP_MEMORY_NOT_ASSIGNED, if no buffer has been assigned by the encoder yet.
	//    - MV_E_INVALID_PARAMETER, if the input parameter is NULL.
	// Remarks:
	//    - A GOP buffer is accessible once it has been fully encoded by mvMpegStream. 
	//    - Accessed by caller and mvMpegStream's CMvMpegStreamEncoderBuffer.
	virtual HRESULT __stdcall GetBuffer
		(
		unsigned char ** out_ppucBuffer,    // Address of a pointer corresponding to the first byte of the GOP buffer.  
		unsigned long  * out_pulSizeinBytes // GOP buffer size in bytes. 
		) = 0;

	//
	// Summary:
	//    Retrieves the GOP write completion event. 
	// Return value:
	//    - MV_NOERROR, the method succeeded.
	//    - MV_E_INVALID_PARAMETER, if the input parameter is NULL.
	// Remarks:
	//    - The event is signaled by mvMpegStream when the GOP encoding is completed.
	//    - The caller waits on this event to write the GOP to disk.  The event is signaled when all 
	//      the GOP encoding are done.
	virtual HRESULT __stdcall GetWriteCompletionEvent
		(
		HANDLE * out_phCompletion  // GOP write completion event address.
		) = 0;

	//
	// Summary:
	//    Retrieves a specific frame inside the GOP buffer. 
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_MPS_GOP_LOCKED, if the GOP is currently being written to by the encoder.
	//    - MV_E_MPS_FRAME_NOT_FOUND, if the specified frame is not inside this GOP.
	//    - MV_E_INVALID_PARAMETER, if the input parameter is NULL.
	// Remarks:
	//    - in_ulFrameDisplayOrder is GOP-based, zero representing the first frame of the GOP. To 
	//      obtain the stream position the caller needs to add the GOP's display position. 
	//    - Accessed by the caller
	virtual HRESULT __stdcall GetCompressedFrame
		(
		unsigned long        in_ulFrameDisplayOrder, // GOP-based index of the frame to retrieve.  
		SMvMpegStreamFrame * io_psFrame              // Frame metadata. 
		) = 0;

	//
	// Summary:
	//     Retrieves the GOP display position inside the stream. 
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_MPS_GOP_MEMORY_NOT_ASSIGNED, if the GOP has not been encoded yet.
	virtual HRESULT __stdcall GetDisplayPositionInFrames
		(
		uint64_t* out_pui64Position   // Address of a variable that receives the GOP position.
		) = 0;

	//
	// Summary:
	//    Retrieves the GOP duration inside the stream. 
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_MPS_GOP_MEMORY_NOT_ASSIGNED, if the GOP has not been encoded yet.
	virtual HRESULT __stdcall GetDurationInFrames
		(
		unsigned long* out_pulDuration   // duration of the GOP in frames.
		) = 0;

	//
	// Summary:
	//    Retrieves the GOP mvMpegStream relative index, which identifies the GOP retrieval order.
	// Return value:
	//    GOP index.
	// Remarks:
	//    - The index is used by mvMpegStream to sort the outgoing GOPs. 
	//    - The index is zero-based and is incremented by one for every GOP.
	virtual uint64_t __stdcall GetIndex() = 0;

	//
	// Summary:  
	//    Retrieves the GOP current error code.
	// Return value:
	//    - MV_NOERROR, by default if no error occurred.
	//    - MV_E_MPS_GOP_CANCELLED, if the GOP has been discarded by mvMpegStream.
	// Remarks:
	//    - The index is zero-based and is incremented by one for every GOP.
	virtual HRESULT __stdcall GetLastError() = 0;

	//
	// Summary:
	//    Checks if the GOP write completion event is signaled.  
	// Return value:
	//    - True, if ready. 
	//    - False, if not ready.
	// Remarks:
	//    - A GOP is ready for a read operation once it is completely encoded by mvMpegStream.
	virtual bool __stdcall IsReadyForRead() = 0;

	//
	// Summary:
	//    Retrieves the GOP time stamp in nanotime. 
	// Return value:
	//    Returns the GOP nanotime time stamp.
	// Remarks:
	//    - The time stamp corresponds to the first time stamp of the GOP surface, as received in 
	//      IMvMpegStream::CompressFrame().
	virtual uint64_t __stdcall GetTimeStampInfo() = 0;

	// 
	// Summary:
	//    Retrieves the performance timing.
	//
	virtual uint64_t __stdcall GetElapsedTime() = 0;

	// 
	// Summary:
	//    Gets the memory interface that manages the GOP's buffer.
	//
	virtual HRESULT __stdcall GetBufferInterface
		(
		IMvMpegStreamBuffer** out_ppIBuffer    // Memory interface that manages the GOP's buffer.
		) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This interface is used to control the mvMpegStream codec module.
// Remarks:
//    - This is the main control interface for the mvMpegStream codec. For other interfaces that are 
//      also managed by the codec, see IMvMpegStreamGop, IMvMpegStreamMemoryProvider, 
//      IMvMpegStreamBuffer. 
//////////////////////////////////////////////////////////////////////////////////
interface IMvMpegStream : public IUnknown
{
	//
	// Summary:
	//    Initializes the mvMpegStream module with the specified parameters.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_STRUCTURE_SIZE, if the SMvMpegStreamInitialize structure has an invalid size.
	//    - MV_E_MPS_NO_MEMORY_PROVIDER, if the SMvMpegStreamInitialize::IMvMpegStreaMemoryProvider 
	//      interface member is NULL.
	//    - MV_E_MPS_WIDTH_NOT_SUPPORTED, if the specified width is not supported.
	//    - MV_E_MPS_HEIGHT_NOT_SUPPORTED, if the specified height is not supported.
	//    - MV_E_MPS_ASPECT_RATIO_NOT_SUPPORTED, if the specified aspect ratio is not supported.
	//    - MV_E_MPS_FRAME_RATE_NOT_SUPPORTED, if the specified frame rate not supported.
	//    - MV_E_MPS_SCAN_MODE_NOT_SUPPORTED, if the specified scan mode is not supported.
	//    - MV_E_MPS_BIT_COUNT_NOT_SUPPORTED, if the specified bit count is not supported.
	//    - MV_E_MPS_LEVEL_DOES_NOT_MATCH_RESOLUTION, if HD resolution needs high level.
	//    - MV_E_MPS_MQUANT_VALUE_NOT_ACCEPTED, if you specified an mquant value that conflicts with
	//      the usage of min and max VBR data rates. The mquant value is exclusive with regards to 
	//      VBR min and max data rate.
	//    - MV_E_MPS_QFACTOR_NOT_SUPPORTED, if the value has to be between 0 and 31 inclusive.
	//    - MV_E_MPS_INVALID_GOP_SIZE, if the value has to be between 1 and 128 inclusive.
	//    - MV_E_MPS_INVALID_NUMBER_OF_B_FRAMES, if the value has to be between 1 and 8 inclusive.
	//    - MV_E_MPS_INVALID_GOP_SIZE, if the GOP size has to be a multiple of the number of B frames.
	//    - MV_E_MPS_TIMECODE_EXCEEDS_MAXIMUM_VALUE, if the time code parameter has to be between 0 
	//      and 5399999 inclusive.
	//    - MV_E_OUT_OF_MEMORY, if unexpected error occurs: unable to allocate internal object pools.
	//    - MV_E_INVALID_POINTER, if the in_psInitialize pointer is NULL.
	// Remarks:
	//    - The SMvMpegStreamInitialize::IMvMpegStreamMemoryProvider interface pointer is consumed by 
	//      mvMpegStream. IMvMpegStream::Open() caches the interface pointer, release it, and resets 
	//      the structure parameter to NULL. 
	//    - From within IMvMpegStream::Open thread, the IMvMpegStreamMemoryProvider interface is 
	//      called to retrieve a memory buffer. The caller has to be ready to provide the 
	//      mvMpegStream module with a memory buffer before opening the codec. 
	//    - The IMvMpegStream::Open() call is a synchronous operation. 
	//    - Following an IMvMpegStream::Open() operation, you can ask the mvMpegStream codec to 
	//      compress frames and provide GOPs.
	virtual HRESULT __stdcall Open
		(
		SMvMpegStreamInitialize* in_psInitialize, // Initialization structure specifying the encoding parameters.
		unsigned long            in_ulThreadID    // Thread ID specifying the codec pool to use; set 
		                                          // to zero if only one pool is used. 
		) = 0;

	//
	// Summary:
	//    Closes the mvMpegStream module signaling the end of the encoding process.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_MPS_ENCODER_CLOSE_FAILED, if an unexpected error occurs, mvMpegStream failed to close 
	//      the encoding threads.
	// Remarks:
	//    - IMvMpegStream::Close() is an asynchronous call. It is serialized against 
	//      IMvMpegStream::CompressFrame() calls. 
	//    - In_hOptionalCloseNotification can be used by the caller to synchronize the Close operation
	//      with its remaining processing tasks. 
	//    - In_hOptionalCloseNotification is optional and can be set to NULL if the caller does not 
	//      wish to be notified of the Close operation completion. 
	//    - In_hOptionalCloseNotification is created and initialized by the caller. The mvMpegStream 
	//      module will only do a SetEvent on the specified handle. If not NULL, the handle has to be 
	//      a valid event handle created with CreateEvent(). The event's validity is not checked by
	//      mvMpegStream. 
	//    - The Close operation waits for all GOPs to be encoded before returning. All surfaces sent 
	//      to IMvMpegStream::CompressFrame() will be encoded. Depending on the encoder resolution 
	//      and pipeline state, this operation last from a few microseconds to hundreds of milliseconds or
	//      more. 
	//    - The Close operation releases the IMvMpegStreamMemoryProvider interface that was passed in
	//      the IMvMpegStream::Open() call. It also releases the currently cached IMvMpegStreamBuffer
	//      interface, if any. 
	//    - Following the Close call, the caller becomes the owner of any outstanding 
	//      IMvMpegStreamGop interfaces he had previously retrieved.
	virtual HRESULT __stdcall Close
		(
		HANDLE        in_hOptionalCloseNotification, // Optional close done on event notification handle.
		unsigned long in_ulThreadID                  // Thread ID specifying which codec pool to 
		                                             // use, specify zero if only one pool is used.
		) = 0;

	//
	// Summary:
	//    Retrieves a group of pictures object from mvMpegStream.
	// Description:
	//    The GOP belong to a pool in mvMpegStream module. The caller can create any number of them.
	//    The caller should cycle between two or more GOP's, and maintain buffer contiguousness by 
	//    signaling read event only when previous GOP is done.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_MPS_ENCODER_CLOSED, if the encoder is closed. A call to IMvMpegStream::Open() needs to 
	//      be successfully completed before any GOPs can be retrieved.
	//    - MV_E_MPS_UNABLE_TO_RETRIEVE_GOP, if an unexpected error occurs: unable to retrieve a GOP
	//      interface.
	//    - MV_E_INVALID_POINTER, if out_ppIGop is NULL.
	// Remarks:
	//    - IMvMpegStream::GetGop() is a synchronous call. 
	//    - The retrieved GOP is processed asynchronously and may be ready or not, depending on the
	//      encoding progression.  
	//    - IMvMpegStreamGop is the compressed result of a number of IMvMpegStream::CompressFrame calls. 
	//    - IMvMpegStream::GetGop() is asymmetric with IMvMpegStream::CompressFrame(). mvMpegStream
	//      fills IMvMpegStreamGop objects. These GOPs could have been already retrieved by the
	//      caller. Once a GOPp is completed, mvMpegStream signals its write completion event so it 
	//      can be processed by the caller when needed. 
	//    - The number of IMvMpegStreamGop objects is not explicitly limited. 
	//    - If the caller retrieved GOPs that were not used by the encoding process (a close occurred),
	//      they will be signaled with a MV_E_MPS_GOP_CANCELLED error.
	virtual HRESULT __stdcall GetGop
		(
		IMvMpegStreamGop** out_ppIGop,   // IMvMpegStreamGop interface used to retrieve the GOP.
		unsigned long      in_ulThreadID // Thread ID specifying which codec pool to use; zero is specified
		                                 // if only one pool is used. 
		) = 0;

	//
	// Summary:
	//    Provides mvMpegStream with an uncompressed frame of video to be encoded.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_POINTER, if in_pIFrame is NULL.
	//    - MV_E_MPS_ENCODER_CLOSED, if the encoder is closed. A call to IMvMpegStream::Open() needs 
	//      to be successfully completed before any GOPs can be retrieved. 
	//    - MV_E_MPS_PUTFRAME_SYNCHRONOUS_ERROR, if an unexpected error occurs: failed to encode the
	//      specified frame.
	// Remarks:
	//    - IMvMpegStream::CompressFrame() is an asynchronous call. It is serialized against other 
	//      IMvMpegStream::CompressFrame() and IMvMpegStream::Close() calls. 
	//    - The results of the CompressFrame operation are returned to the caller using 
	//      IMvMpegStreamGop objects.
	virtual HRESULT __stdcall CompressFrame
		(
		IMvSurface*   in_pIFrame,     // Pointer to an uncompressed frame.
		unsigned long in_ulThreadID   // Thread ID specifying the codec pool to use; set to zero if
		                              // only one pool is used . 
		) = 0;

	//
	// Summary:
	//    Provides mvMpegStream with an uncompressed frame of video and audio to be encoded.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_POINTER, if in_pIFrame is NULL.
	//    - MV_E_MPS_ENCODER_CLOSED, if the encoder is closed. A call to IMvMpegStream::Open() needs 
	//      to be successfully completed before any GOPs can be retrieved. 
	//    - MV_E_MPS_PUTFRAME_SYNCHRONOUS_ERROR, if an unexpected error occurs: failed to encode the
	//      specified frame.
	// Remarks:
	//    - IMvMpegStream::CompressFrame() is an asynchronous call. It is serialized against other 
	//      IMvMpegStream::CompressFrame() and IMvMpegStream::Close() calls. 
	//    - The results of the CompressFrame operation are returned to the caller using 
	//      IMvMpegStreamGop objects.
	virtual HRESULT __stdcall CompressFrame
		(
		IMvSurface*       in_pIFrame,    // Pointer to an uncompressed frame.
		IMvAudioSamples*  in_pISamples,  // Pointer to an audio samples buffer representing a frame
		unsigned long     in_ulThreadID  // Thread ID specifying the codec pool to use; set to zero if
		                                 // only one pool is used. 
		) = 0;

	//
	// Summary:
	//    Provides mvMpegStream with uncompressed frames of video and VBI to be encoded.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_POINTER, if in_pIVideoSurface or in_pIVBISurface is NULL.
	//    - MV_E_MPS_ENCODER_CLOSED, if the encoder is closed. A call to IMvMpegStream::Open() needs 
	//      to be successfully completed before any GOPs can be retrieved. 
	//    - MV_E_MPS_PUTFRAME_SYNCHRONOUS_ERROR, if an unexpected error occurs: failed to encode the
	//      specified frame.
	// Remarks:
	//    - IMvMpegStream::CompressFrameWithVBI() is an asynchronous call. It is serialized against other 
	//      IMvMpegStream::CompressFrameWithVBI() and IMvMpegStream::Close() calls. 
	//    - The results of the CompressFrameWithVBI operation are returned to the caller using 
	//      IMvMpegStreamGop objects.
	virtual HRESULT __stdcall CompressFrameWithVBI
		(
		IMvSurface*       in_pIVideoSurface,   // Pointer to an uncompressed video frame.
		IMvSurface*       in_pIVBISurface,     // Pointer to an uncompressed VBI frame.
		unsigned long     in_ulThreadID        // Thread ID specifying the codec pool to use; set to zero if
                                             // only one pool is used. 
		) = 0;

	//
	// Summary:
	//    Provides mvMpegStream with an uncompressed frame of video, VBI and and audio to be encoded.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_POINTER, if in_pIFrame is NULL.
	//    - MV_E_MPS_ENCODER_CLOSED, if the encoder is closed. A call to IMvMpegStream::Open() needs 
	//      to be successfully completed before any GOPs can be retrieved. 
	//    - MV_E_MPS_PUTFRAME_SYNCHRONOUS_ERROR, if an unexpected error occurs: failed to encode the
	//      specified frame.
	// Remarks:
	//    - IMvMpegStream::CompressFrameWithVBI() is an asynchronous call. It is serialized against other 
	//      IMvMpegStream::CompressFrameWithVBI() and IMvMpegStream::Close() calls. 
	//    - The results of the CompressFrameWithVBI operation are returned to the caller using 
	//      IMvMpegStreamGop objects.
	virtual HRESULT __stdcall CompressFrameWithVBI
		(
		IMvSurface*       in_pIVideoSurface,   // Pointer to an uncompressed video frame.
		IMvSurface*       in_pIVBISurface,     // Pointer to an uncompressed VBI frame.
		IMvAudioSamples*  in_pISamples,        // Pointer to an audio samples buffer representing a frame
		unsigned long     in_ulThreadID        // Thread ID specifying the codec pool to use; set to zero if
                                             // only one pool is used. 
		) = 0;

   //Summary:
   //       Set the resource manager pointer to mvMpegStream so as it can notify the Flex File Writer when an error has occurred.
   //Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if in_pIMvdResourceManager is NULL
   virtual HRESULT __stdcall SetResourceManager
      (
      IMvdResourceManager * in_pIMvdResourceManager, 
      unsigned long         in_ulThreadID
      ) = 0;
   
};

//////////////////////////////////////////////////////////////////////////////////
// 
// Summary:
//    Controls the Matrox 1394 recording engine (writing module)
// Remarks:
//    - Inherits from IUnknown.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvFlex1394Writer : public IUnknown
{
	//
	// Summary:
	//    Provides video and/or audio data to be recorded onto the device's tape.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if IMvFlex1394Writer::SetOptions has not been set. 
	//    - MV_M_EC_COMPLETE, when the print-to-tape operation reaches the specified Out point. 
	// Remarks:
	//    - Prior to calling this method you should have properly initialized the writer module.
	//      To process this method you must use IMvFlex1394Writer::SetOptions to set the edit resolution 
	//      and surface format. 
	//    - This method always returns a frame of compressed video and/or uncompressed audio. If the user 
	//      chooses to record with audio, the writer module multiplexes the data asynchronously. 
	//    - The writer module has a limited number of video/audio surfaces/samples. The caller needs to
	//      consume the retrieved buffers in order for them to become reusable by the writer module. 
	//    - When the in_bWait flag is set to true, and if the writer module runs out of buffers to process 
	//      the current GetBuffer() call, the writer module will wait indefinitely for a buffer to become available.
	//      If, on the other hand, the in_bWait flag is set to false, an error code will be returned immediately 
	//      to allow the caller to react by freeing up buffers. 
	//    - The in_aulNumberOfSamplesPerBuffer parameter represents the audio sequence and is determined by the
	//      caller. 
	//    - The in_ui64TimeStampInNanoTime parameter is obtained by the caller through the IMvClock interface,
	//      which in turn is obtained through the Flex Engine. This time stamp can be used by the caller to
	//      prioritize the GetBuffer operations. 
	//
	virtual HRESULT __stdcall GetBuffer
		(  
		IMvSurface**      out_ppIVideoSurfaces,      // Video surfaces array that receives any 
		                                             // of the video surfaces to be recorded onto tape.
		IMvAudioSamples** out_ppIAudioSamplesPair1,  // Audio samples array that receives the first 
		                                             // pair of audio samples to be recorded onto tape.
		IMvAudioSamples** out_ppIAudioSamplesPair2,  // Audio samples array that receives the second
                                             		// pair of audio samples to be recorded onto tape.
		unsigned long     in_ulNumberOfSamplesPerBuffer,   // Number of audio samples the caller expects
		                                                   // per IMvAudioSamples buffer [in]. This is 
		                                                   // the caller-supplied audio sequence.
		uint64_t          in_ui64TimeStampInNanoTime,   // Time stamp, in nanotime, to be used 
		                                                // internally by the writer module for
		                                                // asynchronous buffering sequencing
		bool              in_bWait    // If true, indicates how the writer module should behave if it runs out of 
		                              // internal buffers to process GetBuffer().
		) = 0;

	//
	// Summary:
	//    Sets the options for the data to be recorded onto tape.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_PARAMETER, if the size of the structure is invalid. 
	//    - MV_E_SURFACE_FORMAT_NOT_SUPPORTED, if the given surface format is not DV compliant. 
	//    - MV_E_OUT_OF_MEMORY, if the system can't allocate the memory for the pool of surfaces. 
	//
	virtual HRESULT __stdcall SetOptions
		(
		SMvFlex1394WriterOptions * in_pOptions // Value to set in the specified option.
		) = 0;

	//
	// Summary:
	//    Set properties for the print-to-tape operation.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	// Remarks:
	//    - This method always succeeds. 
	//
	virtual HRESULT __stdcall SetDeviceRecordParameters
		(
		uint64_t in_ui64RecordDelayInNanoTime, // Specifies when to start recording for each specific DV-1394 device.
		uint64_t in_ui64StopDelayInNanoTime,   // Specifies when to stop recording for each specific DV-1394 device.
		int      in_iSeekPrerollInFrame,       // Specifies an offset to correct the difference between the Mark In 
                                             // point position specified by the user and the actual point where the 
                                             // device will start recording on the tape.
		bool     in_bDropFrame = true          // If true, indicates the format that matches the time code format on your 
                                             // DV tape. If you have an NTSC system, you will need to set this 
                                             // parameter. By default, in_bDropFrame is set to true.
		) = 0;

	//
	// Summary:
	//    Seeks to an exact position on the device's tape.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the writer module is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a GoTo command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state which it can receive a GoTo command. 
	// Remarks:
	//    - This method waits for the device's tape to be positioned properly. 
	//    - The device goes into a pause state after receiving a GoTo command. 
	//
	virtual HRESULT __stdcall GoTo
		(
		unsigned long in_ulTimecode   // Specifies the time code to seek to.
		) = 0;

	//
	// Summary:
	//    Puts the device in record mode.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the writer module is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a Record
	//      command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state in which it can receive a Record
	//      command. 
	// Remarks:
	//    - The Record command also sends the buffer's contents to the device. 
	//
	virtual HRESULT __stdcall Record() = 0;

	//
	// Summary:
	//    Cues the device to a specific position and prepares the device for a print-to-tape operation.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the writer module is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a Cue
	//      command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state in which it can receive a Cue
	//      command. 
	//	 - MV_E_DEVICE_IN_WRONG_STATE, during the course of cuing, the device is in a stop state for some reason. For example, 
	//      if the user stops the device manually during cuing, then we have to abort the seek and return this error.  
	//	 - MV_E_FAIL, if in the middle of cuing, the user cancels the cuing operation by calling Stop
	//	 - MV_E_IN_POINT_NOT_REACHED, if the In point of print-to-tape is not reached. 
	// Remarks:
	//    - This method is called before the Record command to prepare the device for the print-to-tape operation.
	//    - If a print-to-tape region is set, this method will move the tape to the In point before 
	//      putting the device in record mode. 
	//    - Once this function is successful, the Record command should immediately be called. 
	//
	virtual HRESULT __stdcall RecordPreparation() = 0;

	//
	// Summary:
	//    Puts the device in play mode.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the writer module is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a Play command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state in which it can receive a Play command. 
	//
	virtual HRESULT __stdcall Play() = 0;

	//
	// Summary:
	//    Puts the device in pause mode.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the writer module is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a Pause command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state in which it can receive a Pause command. 
	//
	virtual HRESULT __stdcall Pause() = 0;

	//
	// Summary:
	//    Puts the device in record-pause mode.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the writer is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a Record-Pause command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state in which it can receive a Record-Pause command. 
	// Remarks:
	//    - This method waits for the device to be set to record-pause mode. 
	//
	virtual HRESULT __stdcall RecordPause() = 0;

	//
	// Summary:
	//    Puts the device in stop mode.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the writer module is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a Stop command. 
	//
	virtual HRESULT __stdcall Stop() = 0;

	//
	// Summary:
	//    Puts the device in forward mode.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the writer module is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a Forward command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state in which it can receive a Forward command. 
	//
	virtual HRESULT __stdcall Forward() = 0;

	//
	// Summary:
	//    Puts the device in reverse mode.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the writer module is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a Reverse command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state in which it can receive a Reverse command. 
	//
	virtual HRESULT __stdcall Reverse() = 0;

	//
	// Summary:
	//    Advances the device by one frame position.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the writer is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a FrameForward command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state in which it can receive a FrameForward command. 
	// Remarks:
	//    - This method waits for the device to advance one frame. 
	virtual HRESULT __stdcall FrameForward() = 0;

	//
	// Summary:
	//    Rewinds the device by one frame position.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the writer module is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a FrameReverse command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state in which it can receive a FrameReverse command. 
	// Remarks:
	//    - This method waits for the device to reverse one frame. 
	//
	virtual HRESULT __stdcall FrameReverse() = 0;

	//
	// Summary:
	//    Sets the region on the device's tape that will be recorded.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_PARAMETER, if the In point is greater than the Out point. 
	// Remarks:
	//    - To set the print to tape region to none, the SetPrintToTape function must be called with an
	//      In point equal to the Out point. 
	//    - This method will stop the device if its state is invalid. 
	//
	virtual HRESULT __stdcall SetPrintToTapeRegion
		(
		long in_lInPoint,    // Time code of the In point.
		long in_lOutPoint    // Time code of the Out point.
		) = 0;

	//
	// Summary:
	//    Gets the current time code in frames from the device.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the reader module is not initialized correctly. 
	//    - HRESULT error code returned by IAMTimecodeReader::GetTimeCode. 
	virtual HRESULT __stdcall GetTimeCode
		(
		long * io_plTimeCode // The current time code of the 1394 device.
		) = 0;

	//
	// Summary:
	//    Seeks to a specific position on the device's tape (may not be frame accurate).
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the writer module is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a GoTo command.
	//    - MV_E_STATE_MISMATCH, if the device is not in a state in which it can receive a GoTo command. 
	// Description:
	//    Seeks to a specific position on the device's tape. This method is available for DV devices only. 
	//    It is faster than the GoTo command, but is not frame-accurate. 
	// Remarks:
	//    - This method waits for the device's tape to be positioned properly. 
	//    - The device goes into a pause state after completing a GoTo command. 
	//    - If the call to FastGoTo succeeds, the writer's internal state will be changed to Pause. 
	//    - If MV_E_STATE_MISMATCH is received, the device will be stopped and the  reader's internal
	//      state will be changed to Stop. 
	virtual HRESULT __stdcall FastGoTo(unsigned long in_ulTimecode) =0;  

	//
	// Summary:
	//    Puts the device in play forward mode (with video preview on the the device's LCD).
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the writer module is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a PlayForward command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state in which it can receive a PlayForward command. 
	// Remarks:
	//    - If the call to PlayForward succeeds, the writer's internal state will be changed to PlayForward. 
	//    - If MV_E_STATE_MISMATCH is received, the device will be stopped and the reader's internal
	//      state will be changed to Stop. 
	//    
	virtual HRESULT __stdcall PlayForward() = 0;

	//
	// Summary:
	//    Puts the device in play reverse mode (with video preview on the device's LCD).
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the reader module is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a PlayReverse
	//      command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state in which it can receive a PlayReverse
	//      command. 
	// Remarks:
	//    - If the call to PlayReverse succeeds, the writer's internal state will be changed to PLayReverse. 
	//    - If MV_E_STATE_MISMATCH is received, the device will be stopped and the writer's internal 
	//      state will be changed to Stop. 
	virtual HRESULT __stdcall PlayReverse() = 0;

	//
	// Summary:
	//    Retrieve the device information (device ID, device description, device type (DV/HDV), tape status
   //    (present/notpresent)).
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER, if the input parameter size is not initialized properly.
	// Remarks:
	virtual HRESULT __stdcall GetDeviceInfo(SMv1394DeviceInformation* out_psDeviceInfo) =  0;

	//
	// Summary:
	//    Retrieves the device's physical state (stop/play/reverse/forward/pause, etc)
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - HRESULT error code returned by IAMExtTransport::get_Mode. 
	// Remarks:
	virtual HRESULT __stdcall GetDeviceState(EMv1394DeviceState* out_peDeviceState) = 0;

	//
	// Summary:
	//    Retrieves the current time code in frames from the device.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the writer module is not initialized correctly. 
	//    - HRESULT error code returned by IAMTimeCodeReader::GetTimeCode. 
	virtual HRESULT __stdcall GetTimeCodeInFrames(unsigned long* io_pulTimeCode) = 0;

	//
	// Summary:
	//    Retrieves the current record parameters from the device.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_PARAMETER if the input parameter size is not initialized properly.
	virtual HRESULT __stdcall GetDeviceRecordParameters(SMv1394RecordParameters* out_psRecordParameters) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This interface is used to control the Matrox 1394 capture engine (reader module).
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvFlex1394Reader : public IUnknown
{
	//
	// Summary:
	//    Provides video and/or audio data to be written to a file.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_PARAMETER, if out_ppIVideoSurface has not been initialized properly. or if
	//      out_ppIAudioSamplesPair1 and out_ppIAudioSamplesPair2 have not been initialized when 
	//      capturing both video and audio. 
	//    - MV_E_NO_INPUT_SURFACE, if there are no more surfaces before the capture reaches the Out
	//      point. 
	//    - MV_E_NOT_AVAILABLE, if the reader module does not have enough data to return to the
	//      application. An example might be the delay between when a user gives a command and the
	//      device actually starts operating. If the application asks for buffer contents before the
	//      device starts sending data, this error message will be returned. 
	//    - MV_E_DROPPED_SAMPLE, if the reader module drops frames. 
	//    - MV_E_DEVICE_AUTO_STOP, if the device is stopped by itself for some reason. 
	//    - MV_E_LOST_VIDEO_INPUT, if input is lost. For example, if the 1394 cable is disconnected. 
	//    - MV_E_DEVICE_IN_WRONG_STATE, if the device is not in a proper state. This error will occur
	//      when the reader module is in a Play state, but the device is in stop mode. The possible
	//      causes of this error: end of tape, the device is stopped by the user while it is playing,
	//      or the device is in local mode instead of remote mode. 
	//    - MV_E_STATE_MISMATCH, if the reader module is not in the proper state to conduct this
	//      operation. 
	//    - MV_M_EC_COMPLETE, if the capture reaches the Out point. 
	// Remarks:
	//    - The reader module has a limited number of video/audio surfaces/samples. The caller 
	//      needs to consume the retrieved buffers in order for them to become reusable by the
	//      reader. 
	//    - When the in_bWait flag is set to true, and if the reader runs out of buffers
	//      to process the current GetBuffer() call, the reader will wait indefinitely for a 
	//      buffer to become available. If, on the other hand, the in_bWait flag is set to false,
	//      an error code will be returned immediately allowing the caller to react by freeing up
	//      buffers. 
	//    - The in_aulNumberOfSamplesPerBuffer parameter represents the audio sequence and is 
	//      determined by the caller. 
	//    - The in_ui64TimeStampInNanoTime parameter is obtained by the caller through the IMvClock
	//      interface, which in turn is obtained through the Flex Engine. This time stamp can be 
	//      used by the caller to prioritize the GetBuffer operations. 
	virtual HRESULT __stdcall GetBuffer (
		IMvSurface**      out_ppIVideoSurfaces,            // IMvSurface** video surfaces array that receives any of the 
                                                         // video surfaces to be written to a file.
		IMvAudioSamples** out_ppIAudioSamplesPair1,        // IMvAudioSamples** audio samples array that receives the 
                                                         // first pair of audio samples to be written to a file.
		IMvAudioSamples** out_ppIAudioSamplesPair2,        // IMvAudioSamples** audio samples array that receives the 
                                                         // second pair of audio samples to be written to a file.
		unsigned long     in_ulNumberOfSamplesPerBuffer,   // Number of audio samples the caller expects per 
                                                         // IMvAudioSamples buffer [in]. This is the caller-supplied 
		                                                   // audio sequence.
		uint64_t          in_ui64TimeStampInNanoTime,      // Time stamp, in nanotime, to be used internally by the 
                                                         // reader module for asynchronous buffering sequencing.
		bool              in_bWait                         // If true, indicates how the reader module should behave if 
                                                         // it runs out of internal buffers to process GetBuffer().
		) = 0;

	//
	// Summary:
	//    Cues the device to be ready for capture.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the reader module is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a Cue command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state in which it can receive a Cue command. 
	// Remarks:
	//    - This method waits for the device's tape to be properly positioned. 
	//    - The device goes into a Pause state after completing a Cue command. 
	//    - If the call to Cue succeeds, the reader's internal state would be changed to Pause.
	//    - If MV_E_STATE_MISMATCH is received, the device will be stopped and the reader's internal
	//      state will be changed to Stop. 
	virtual HRESULT __stdcall Cue() = 0;

	//
	// Summary:
	//    Seeks to an exact position on the device's tape.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the reader module is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a GoTo command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state in which it can receive a GoTo command. 
	// Remarks:
	//    - This method waits for the device's tape to be positioned properly. 
	//    - The device goes into a pause state after completing a GoTo command. 
	//    - If the call to GoTo succeeds, the reader's internal state will be changed to Pause.
	//    - If MV_E_STATE_MISMATCH is received, the device will be stopped and the reader's internal
	//      state will be changed to Stop. 
	virtual HRESULT __stdcall GoTo
		(
		unsigned long in_ulTimecode   // Specifies the time code to seek to.
		) = 0;

	//
	// Summary:
	//    Puts the device in play mode.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the reader module is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a Play command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state in which it can receive a Play command. 
	// Remarks:
	//    - If the call to Play succeeds, the reader's internal state will be changed to Play. 
	//    - If MV_E_STATE_MISMATCH is received, the device will be stopped and the reader's internal 
	//      state will be changed to Stop. 
	virtual HRESULT __stdcall Play() = 0;

	//
	// Summary:
	//    Puts the device in pause mode.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the reader module is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a Pause command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state in which it can receive a Pause command. 
	// Remarks:
	//    - If the call to Pause succeeds, the reader's internal state will be changed to Pause. 
	//    - If MV_E_STATE_MISMATCH is received, the device will be stopped and the reader's internal
	//      state will be changed to Stop. 
	virtual HRESULT __stdcall Pause() = 0;

	//
	// Summary:
	//    Puts the device in stop mode.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the reader module is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a Stop command. 
	virtual HRESULT __stdcall Stop() = 0;

	//
	// Summary:
	//    Puts the device in forward mode.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the reader is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a Forward command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state in which it can receive a Forward command. 
	// Remarks:
	//    - If MV_E_STATE_MISMATCH is received, the device will be stopped and the reader's 
	//      internal state will be changed to Stop. 
	//    - If the call to forward succeeds, the reader's internal state will be changed to Forward. 
	virtual HRESULT __stdcall Forward() = 0;

	//
	// Summary:
	//    Puts the device in reverse mode.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the reader module is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a Reverse
	//      command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state in which it can receive a Reverse
	//      command. 
	// Remarks:
	//    - If the call to Reverse succeeds, the reader's internal state will be changed to Reverse. 
	//    - If MV_E_STATE_MISMATCH is received, the device will be stopped and the reader's internal 
	//      state will be changed to Stop. 
	virtual HRESULT __stdcall Reverse() = 0;

	//
	// Summary:
	//    Advances the device by one frame position.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the reader module is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a FrameForward
	//      command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state in which it can receive a FrameForward
	//      command. 
	// Remarks:
	//    - This method waits one second for the device to advance one frame. 
	//    - If the call to FrameForward succeeds, the reader's internal state will be changed to Pause. 
	//    - If MV_E_STATE_MISMATCH is received, the device will be stopped and the reader's internal
	//      state will be changed to Stop. 
	virtual HRESULT __stdcall FrameForward() = 0;

	//
	// Summary:
	//    Rewinds the device one frame position.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the reader module is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a FrameReverse
	//      command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state state in which it can receive a 
	//      FrameReverse command. 
	// Remarks:
	//    - This method waits one second for the device to reverse one frame. 
	//    - If the call to FrameReverse succeeds, the reader's internal state will be changed to Pause. 
	//    - If MV_E_STATE_MISMATCH is received, the device will be stopped and the reader's internal
	//      state will be changed to Stop. 
	virtual HRESULT __stdcall FrameReverse() = 0;

	//
	// Summary:
	//    Specifies the In and Out points of the capture.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_PARAMETER, if the In point is greater than the Out point. 
	//    - MV_E_STATE_MISMATCH, if the reader module is not in the proper state to conduct this
	//      operation. 
	// Remarks:
	//    - To set the capture region to none, this function must be called with an In point equal 
	//      to the Out point. 
	//    - If MV_E_STATE_MISMATCH is received, the device will be stopped and the reader's internal
	//      state will be changed to Stop. 
	//
	virtual HRESULT __stdcall SetPlayRegion
		(
		long in_lInPoint, // In point time code.
		long in_lOutPoint // Out point time code.
		) = 0;

	//
	// Summary:
	//    Gets the current time code from the device.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the reader module is not initialized correctly. 
	//    - HRESULT error code returned by IAMTimecodeReader::GetTimeCode. 
	virtual HRESULT __stdcall GetTimeCode
		(
		long* io_plTimeCode  // The current time code of the 1394 device.
		) = 0;

	//
	// Summary:
	//    Sets the capture properties.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_PARAMETER, if the in_pOptions parameter is not initialized properly. 
	virtual HRESULT __stdcall SetOptions
		(
		SMvFlex1394ReaderOptions *in_pOptions  // Capture properties. This includes the number of audio pairs to capture
		// (on or two for DV50, one for the other formats).
		) = 0;

	//
	// Summary:
	//    Seeks to a specific position on the device's tape (may not be frame accurate).
	// Description:
	//    This method is available for DV devices only. It is faster than the GoTo command, but it is not frame-accurate. 
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the reader is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a GoTo command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state in which it can receive a GoTo command. 
	// Remarks:
	//    - This method waits for the device's tape to be positioned properly. 
	//    - The device goes into a pause state after completing a GoTo command. 
	//    - If the call to FastGoTo succeeds, the reader's internal state will be changed to Pause. 
	//    - If MV_E_STATE_MISMATCH is received, the device will be stopped and the reader's internal
	//      state will be changed to Stop. 
	virtual HRESULT __stdcall FastGoTo(unsigned long in_ulTimecode) =0;  

	//
	// Summary:
	//    Puts the device in play forward mode (with video preview on the device's LCD).
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the reader module is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a PlayForward command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state in which it can receive a PlayForward command. 
	// Remarks:
	//    - If the call to PlayForwards succeeds, the reader's internal state will be changed to PlayForward. 
	//    - If MV_E_STATE_MISMATCH is received, the device will be stopped and the reader's internal 
	//      state will be changed to Stop.
	virtual HRESULT __stdcall PlayForward() = 0;

	//
	// Summary:
	//    Puts the device in play reverse mode (with video preview in the device's LCD).
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the reader is not initialized correctly. 
	//    - MV_E_WRONG_STATE, if the module is not in a state in which it can receive a PlayReverse
	//      command. 
	//    - MV_E_STATE_MISMATCH, if the device is not in a state in which it can receive a PlayReverse
	//      command. 
	// Remarks:
	//    - If the call to PlayReverse succeeds, the  reader's internal state will be changed to PlayReverse. 
	//    - If MV_E_STATE_MISMATCH is received, the device will be stopped and the  reader's internal
	//      state will be changed to Stop. 
	virtual HRESULT __stdcall PlayReverse() = 0;

	//
	// Summary:
	//    Gets the device's information (device ID, device description, device type (DV/HDV), tape status
   //    (present/notpresent)).
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_INVALID_PARAMETER, if the input parameter size is not initialized properly.
	virtual HRESULT __stdcall GetDeviceInfo(SMv1394DeviceInformation* out_psDeviceInfo) =  0;

	//
	// Summary:
	//    Gets the device's physical state (stop/play/reverse/forward/pause, etc).
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - HRESULT error code returned by IAMExtTransport::get_Mode. 
	virtual HRESULT __stdcall GetDeviceState(EMv1394DeviceState* out_peDeviceState) = 0;

	//
	// Summary:
	//    Retrieves the current time code in frames from the device.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_INITIALIZED, if the reader module is not initialized correctly. 
	//    - HRESULT error code returned by IAMTimecodeReader::GetTimeCode. 
	virtual HRESULT __stdcall GetTimeCodeInFrames(unsigned long* io_pulTimeCode) = 0;
};



interface IMvFlex1394Enumerator: public IUnknown
{
	//
	// Summary:
	//    Gets the next available 1394 device connected to the system.
	// Description:
	//	  The field bAvailable of SMv1394DeviceDescription indicates whether or not the device is available.
	// Return value:
	//    - MV_NOERROR, if properly filled. 
	//    - MV_E_END_OF_ENUM, if there is no more device information to enumerate. 
	//    - MV_E_INVALID_PARAMETER, if an out_ps1394Info or out_pul1394InfoFetched parameter is not initialized properly. 
	//    - MV_E_INVALID_STRUCTURE_SIZE, if the structure size of pInfo array is not initialized properly. 
	//      
	// 
	virtual HRESULT __stdcall Next
		( 
		unsigned long             in_ulNb1394InfoRequested,   // Number of entries in the device information array.
		SMv1394DeviceDescription  *out_ps1394Info,            // Pointer to the array of structures describing the 1394
                                                            // devices.
		unsigned long             *out_pul1394InfoFetched     // Pointer to the number of entries that have been filled 
                                                            // in the array of structures.
		) = 0;

	//
	// Summary:
	//    Resets the internal counter to the first device found on the system. 
	// Description:
	//    The internal pointer is reset so that the next call to IMvFlex1394Enumerator::Next returns the first device 
   //    found on the system.
	// Return value:
	//    - Always returns MV_NOERROR. 
	virtual HRESULT __stdcall Reset () = 0;

	//
	// Summary:
	//    Skips a given number of 1394 devices.
	// Description:
	//    The internal pointer is changed so that the next call to IMvFlex1394Enumerator::Next skips a given number of
   //    devices in the internal list.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_FAIL, if the number of elements to skip was not in_ulCount. 
	virtual HRESULT __stdcall Skip
		(
		unsigned long in_ulCount   //Number of devices to skip.
		) = 0;
};

//
// Summary:
//    This is a private interface used to control the MXO in presentation mode.
// Remarks:   
//    This interface is available from IMvMXOControl.
//
interface IMvMXOControlPrivatePresentation : public IUnknown
{
public:
	//
	// Summary:
	//    Specifies the external DVI when connected to a DVI port of something 
	//    other than the PC.  
	// Remarks:
	//    You must be in presentation mode with external DVI for the call to work.
	//
	virtual HRESULT SetExternalDVISourceResolution
      (
		uint32_t in_ui32ResolutionX,  // 
		uint32_t in_ui32ResolutionY   //
		) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Returns IMvImagingMXOControl to get control of the MXO.
// Description:
//	   This interface returns IMvImagingMXOControl to get control of the MXO. 
// Note:
//    This interface should be in the mvflexapi.h
////////////////////////////////////////////////////////////////////////////////
interface IMvImagingMXOControl: public IUnknown
{
public:

	// Summary:
	//     Sets the input and output resolutions
	//		 
	// Description:
	//	  Sets the input and output resolutions for the Imaging MXO product
	//
	// Parameters:
	//    in_eDVIInputResolution :  DVI input resolution
	//    in_eDVIOutputResolution : DVI output resolution
	//    in_eOutputResolution :    SDI/analog output resolution
	//		in_bReserved :				  Reserved parameter : Value must be false
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
	//    - MV_E_INVALID_PARAMETER, if a specified resolution is invalid or if in_bReserved is something else than false
	//		- MV_E_NOT_SUPPORTED, if a resolution combination is not supported
	virtual HRESULT SetInputOutputResolutions
		(
		EMvDVIResolution in_eDVIInputResolution,
		EMvDVIResolution in_eDVIOutputResolution,
		EMvMXOOutputResolution in_eOutputResolution,
		bool in_bReserved
		) = 0;

	// Summary:
	//    Set indicator overlay on DVI output of the MXO 
	//		 
	// Description:
	//	   Set indicator overlay by its index, state(ON/OFF) and  color 
	// Parameters:
	//	   in_eIndicatorIndex : indicator index
	//	   in_ui8Y            : value of Y component
	//	   in_ui8U            : value of U component
	//	   in_ui8V            : value of V component
	//    in_ui16Delay       : Delay time in frames 
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
	//    - MV_E_INVALID_PARAMETER, if in_eIndicatorIndex is invalid
	virtual HRESULT ControlIndicator
		(
		EMvImagingMXOIndicator in_eIndicatorIndex,
		uint8_t in_ui8Y,       
		uint8_t in_ui8U,       
		uint8_t in_ui8V,
		uint16_t in_ui16Delay
		) = 0;

	// Summary:
	//     Freeze and transfer still HD image
	//		 
	// Description:
	//     Freeze image on the DVI output of the MXO for a specific elapse time
	//     simultaneous with the beginning of that freeze,send this HD still image over the SDI output.
	// Parameters:
	//     in_ui16Delay : duration of freeze and transfer in frame time 
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
	//    - MV_E_INVALID_PARAMETER, if in_ui16Delay is too short(< 6 frames)
	virtual HRESULT FreezeAndTransfer
		(
		uint16_t in_ui16Delay
		) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This interface is used to control the MXO, and is returned to the user by IMvMXOControlFactory.
// Remarks:
//		- IMvMXOControl::Lock must be called before any of the other calls can be executed.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvMXOControl : public IUnknown
{
public:

	// Summary:
	//    Locks the MXO driver so it can be used.
	// Description:
	//		 Locks the MXO driver so it can be used and needed system resources can be accessed.
	//		 This must be called before any other calls can be successful. This call is synchronous and the thread 
	//		 will be blocked until a lock is established.  
	// Return value:
	//    - MV_NOERROR, if the lock is established.
	//    - MV_E_NOT_LOCKED, if a lock is not established.
	//    - MV_E_FAIL, if an unexpected error occurs. In this case, the driver is probably not locked.
	virtual HRESULT Lock() = 0;

	// Summary:
	//    Unlocks the MXO driver so it can be locked by another call to IMvMXOControl::Lock.   
	// Return value:
	//    - MV_NOERROR, if the driver is successfully unlocked.
	//    - MV_E_NOT_LOCKED, if the driver was not locked.
	//    - MV_E_FAIL, if an unexpected error occurs. In this case, the driver is probably locked.   
	virtual HRESULT Unlock() = 0;

	// Summary:
	//    Initializes MXO Presentation mode.
	// Description:
	//		 Initializes MXO Presentation mode. Initializing occurs at startup and when a user changes settings 
	//		 in the <b>MXO Configuration Application</b> dialog box.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_NOT_LOCKED, if the MXO driver has not been locked.
	//    - MV_E_FAIL, if an unexpected error occurs.  
	virtual HRESULT InitializePresentationMode
		(
      EMvMXOOutputResolution in_eOutputResolution,		// Specifies the output video standard of MXO.
      EMvGenlockSource       in_eGenlockSource,			// Specifies whether to set MXO to use an internal 
                                                      // or external genlock source. You can choose to genlock 
                                                      // to MXO's internal reference signal, or genlock to 
                                                      // an external sync generator connected to REF IN on the MXO. 
      EMvMXOOutputResolution in_eGenlockStandard,     // Specifies the genlock source's video standard (for an 
                                                      // external genlock source only).
      bool     in_bFlickerFreeEnable,     // If true, enables the anti-flicker filter.
      bool     in_bUseCompositeAndYCOut,  // If true, sets the analog video output connector to composite and Y/C.
                                          // Otherwise, if false, sets the analog video output connector to component.
      bool     in_b75IRE,                 // If true, sets the NTSC analog setup to 7.5 IRE.
                                          // Otherwise, if false, sets the NTSC analog setup to 0 IRE.
      bool     in_bEnableAudioPassthrough,   // If true, enables audio passthrough. This routes the computer's audio to 
                                             // the speakers via the MXO's RCA connectors, and embeds the audio in the 
                                             // SDI output signalof MXO.
      bool     in_bEnableAudioPair0,			// If true, enables the audio pass through on pair 0.
      bool     in_bEnableAudioPair1,			// If true, enables the audio pass through on pair 1.
      bool     in_bEnableAudioPair2,			// If true, enables the audio pass through on pair 2.
      bool     in_bEnableAudioPair3,			// If true, enables the audio pass through on pair 3.
      bool     in_bIsOverScan,               // If true, determines if the monitor overscan is faked (mostly for dvi 
                                             // monitor).
      int32_t  in_i32GenHorizontalTimOffset, // Determines the amount of horizontal timming offset (in pixels) for the 
                                             // genlock. 
      int32_t  in_i32GenVerticalTimOffset,	// Determines the amount of vertical timming offset (in pixels) for the 
                                             // genlock.
      bool     in_bOptimizeInit,             // If true, determines if the full initialization procedure is needed
                                             // (full initialization, fpga reset...).
      EMvConvertDVIScalingMethod	 in_eScalingMode,       // Determine the scaling algorithm used.
      SMvRect*			in_pScaledOutputRect,               // Determine the output rectangle in the case of not a centered output, NULL otherwise.
      bool				in_bApplySquareInputCompensation,   // If true, determines if the source square pixel compensation is applied.
      EMvAspectRatio in_eARCompensation,                 // Determines if square pixel compensation for 4:3 or 16:9 output is applied.
      bool				in_bAllowSuperWhiteSuperBlack,      // If true, determines if super white and super black in border color is allowed.
      uint32_t			in_ui32BorderColor                  // Determines the border color. Set to black by default.
      ) = 0;

   // Summary:
	//    Returns a unique ID that identifies the MXO based on its serial number.
	// Description:
	//		 Returns a unique ID that identifies the MXO based on its serial number. 
	//		 This unique ID is needed to get control of the desired MXO using 
	//		 IMvMXOControlFactory::GetMXOControlFromMXOUniqueID.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_NOT_LOCKED, if the MXO driver has not been locked.
	//    - MV_E_FAIL, if an unexpected error occurs.  
	virtual HRESULT GetUniqueID
		(
		uint32_t& io_refui32UniqueID // Specifies the unique ID of the MXO.	
		) = 0;

	// Summary:
	//    Returns the DVI connections identifiers that allows to specify where the MXO is connected on the computer.
	// Description:
	//		 Returns the DVI connections identifiers that allows to specify where the MXO is connected on the computer.
	//     The returned SMvDVIConnectionsIdentifiers is composed of the GDI display device index, the GDI monitor index
	//     and the control panel monitor identifier. The Control panel monitor identifier is needed to get control of the 
	//     desired MXO using IMvMXOControlFactory::GetMXOControlFromControlPanelMonitorID  
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_NOT_LOCKED, if the MXO driver has not been locked.
	//    - MV_E_FAIL, if an unexpected error occurs.  
	virtual HRESULT GetDVIConnectionsIdentifiers
		(
		SMvDVIConnectionsIdentifiers& io_rsDVIConnectionsIdentifiers // Returns the DVI connections identifiers
		) = 0;

	// Summary:
	//    Enables or disables the anti-flicker filter in MXO Presentation mode.
	// Description:
	//		 Enables or disables the anti-flicker filter in MXO Presentation mode. 
	//		 Enabling will prevent flickering when previewing interlaced video. 
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_NOT_LOCKED, if the MXO driver has not been locked.
	//    - MV_E_FAIL, if an unexpected error occurs.  
	virtual HRESULT EnableFlickerFreeMode
		(
		bool in_bEnableFlickerFreeMode  // If true, enables the anti-flicker filter.
		) = 0;

	// Summary:
	//    Indicates if the MXO is genlocked to an internal or external genlock source, 
	//		 or not genlocked at all.
	// Description:
	//		 Indicates if the MXO is genlocked to an internal or external genlock source, 
	//		 or not genlocked at all. Although the MXO is always considered genlocked when 
	//		 an internal source is selected, it is considered not genlocked if it is set to an 
	//		 external genlock source, but there is no external sync generator connected to REF IN 
	//		 on the MXO. 
	// Return value:
	//    - MV_TRUE,  if the call is successful and the MXO is genlocked.
	//    - MV_FALSE, if the call is successful and the MXO is not genlocked.
	//    - MV_E_FAIL, if an unexpected error occurs.  
	virtual HRESULT IsGenlocked
		(
		bool & io_refbAnalogSignalPresent,  // If true, indicates that an analog signal is detected from an external sync 
		                                    // generator connected to REF IN on the MXO.
		bool & io_refbIsInternalGenlocked   // If true, indicates that MXO is genlocked to the internal reference signal.
		) = 0;

	// Summary:
	//    Initializes MXO Presentation mode with cropping controls.
	// Description:
	//		 Initializes MXO Presentation mode with cropping controls. Initializing occurs at startup and when a user changes settings 
	//		 in the <b>MXO Configuration Application</b> dialog box.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_NOT_LOCKED, if the MXO driver has not been locked.
	//    - MV_E_FAIL, if an unexpected error occurs.  
	virtual HRESULT InitializePresentationModeWithCropping
		(
      EMvMXOOutputResolution in_eOutputResolution,    // Output resolution of the MXO.
      EMvGenlockSource       in_eGenlockSource,       // Genlock source (internal or external).
      EMvMXOOutputResolution in_eGenlockStandard,     // Genlock resolution.
      bool     in_bFlickerFreeEnable,        // If true, enables the flicker removal mode.
      bool     in_bUseCompositeAndYCOut,     // If true, sets the analog video output connector to composite and Y/C. 
                                             // Otherwise, if false, sets the analog video output connector to component.
      bool     in_b75IRE,                    // If true, sets the NTSC analog setup to 7.5 IRE.
                                             // Otherwise, if false, sets the NTSC analog setup to 0 IRE.
      bool     in_bEnableAudioPassthrough,   // If true, enables the audio pass through.
      bool     in_bEnableAudioPair0,         // If true, enables the audio pass through on pair 0.
      bool     in_bEnableAudioPair1,         // If true, enables the audio pass through on pair 1.
      bool     in_bEnableAudioPair2,         // If true, enables the audio pass through on pair 2.
      bool     in_bEnableAudioPair3,         // If true, enables the audio pass through on pair 3.
      uint32_t in_ui32CropLeftAmount,        // Determines the amount of pixels to crop on left side.  
      uint32_t in_ui32CropRightAmount,       // Determines the amount of pixels to crop on right side.   
      uint32_t in_ui32CropTopAmount,         // Determines the amount of pixels to crop on top.     
      uint32_t in_ui32CropBottomAmount,      // Determines the amount of pixels to crop on bottom.
		bool     in_bIsOverScan,               // If true, determines if the monitor overscan is faked (mostly for dvi
                                             // monitor).
		int32_t  in_i32GenHorizontalTimOffset,	// Determines the amount of horizontal timming offset (in pixels) for the
                                             // genlock. 
		int32_t  in_i32GenVerticalTimOffset,	// Determines the amount of vertical timming offset (in pixels) for the
                                             // genlock.
		bool     in_bOptimizeInit,             // If true, determines if the full initialization procedure is required
                                             // (full initialization, fpga reset...).
		EMvConvertDVIScalingMethod in_eScalingMode,        // Determine the scaling algorithm used
		SMvRect*			in_pScaledOutputRect,               // Determine the output rectangle in the case of not a 
                                                         // centered output, NULL otherwise
		bool				in_bApplySquareInputCompensation,   // If true, determines if the source square pixel compensation
                                                         // is applied.
		EMvAspectRatio	in_eARCompensation,				      // Determines if a square pixel compensation for 4:3 or 16:9
                                                         // output is applied.
		bool				in_bAllowSuperWhiteSuperBlack,      // If true, determines if super white and super black in
                                                         // border color is allowed.
		uint32_t			in_ui32BorderColor                  // Determines the border color. Set to black by default.
		) = 0;

	// Summary:
	//	  Set the genlock
	// Description:
	//	  Set the genlock source, resolution, horizontal and vertical timmings
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.  
	virtual HRESULT SetGenlock
		(
			EMvGenlockSource in_eGenlockSource,
			EMvMXOOutputResolution in_eGenlockStandard,
			int32_t in_i32HorizontalTimmings,
			int32_t in_i32VerticalTimmings
		) = 0;

	// Summary:
	//        Retrieve the genlock timmings(preload)
	// Description:
	//		 Retrieve the genlock horizontal and vertical timmings(preload)default depending on the genlock resolution
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.  
	virtual HRESULT GetGenlockTimmingsValues
		(
		EMvMXOOutputResolution in_eVideoOutStandard, // Output resolution
		EMvMXOOutputResolution in_eGenlockStandard,  // Genlock resolution.
		int32_t& out_i32HorizontalTimmings,          // Horizontal timmings(preload)
		int32_t& out_i32VerticalTimmings             // Vertical timmings(preload)
		) = 0;

	// Summary:
	//        Freeze or unfreeze the DVI output
	// Description:
	//		 Freeze or unfreeze the DVI output without delay to unfreeze
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.  
	virtual HRESULT FreezeOutput
		(
		bool in_bFreeze // If true, enables the DVI output to be frozen.
		) = 0;

	// Summary:
	//	  Set the auto input detection feature on or off
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
	virtual HRESULT SetInputDetection
		(
		bool in_bEnableInputDetection // If true, enable auto input detection
		) = 0;

	// Summary:
	//	  Set the auto input detection feature output pixel aspect ratio
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
	virtual HRESULT SetInputDetectionRatio
		(
		EMvAspectRatio in_eARCompensation
		) = 0;

	// Summary:
	//	  Set the auto input detection feature output mode (Best Fit or Anamorphic)
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
	virtual HRESULT SetInputDetectionKeepAspectRatio
		(
		bool in_bKeepAspectRatio
		) = 0;

	// Summary:
	//        Freezes or unfreezes the sdi/component output.
	// Description:
	//		 Freezes or unfreezes the sdi/component output.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.  
	virtual HRESULT FreezeVideoOutput
		(
		bool in_bFreeze // If true, enables the sdi/component output to be frozen.
		) = 0;

	// Summary:
	//        Set the border color of the video out
	// Description:
	//		 Set the border color of the video out in yuv format
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.  
	virtual HRESULT SetBorderColor
		(
		uint32_t in_ui32ColorRGB,
		EMvMXOOutputResolution in_eOutputResolution,
		bool in_bAllowSWSB
		) = 0;

	// Summary:
	//        Program the stand alone mode
	// Description:
	//		 Program the stand alone box with the correct registry values
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.  
	virtual HRESULT SetStandAloneMode() = 0;

	// Summary:
    //	  Program default stand alone settings
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
    virtual HRESULT ProgramDefaultStandAlone(bool in_bOverwrite) = 0;

	// Summary:
    //	  Program default stand alone input detection settings
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
    virtual HRESULT ProgramDefaultInputDetection() = 0;

	// Summary:
	//        Retrieve the programmed stand alone values
	// Description:
	//		 Retrieve the currently programmed stand alone values to inform of it's current state
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.  
	virtual HRESULT GetStandAloneSettings
		(
		uint32_t& out_refui32MonitorHeight,
		uint32_t& out_refui32MonitorWidth,
		EMvMXOOutputResolution& out_eOutputVideoFormat,
		bool&	 out_refbIs7_5IRE,
		bool&	 out_refbIsFlickerFree,
		bool&	 out_refbIsComponentOutput,
		EMvGenlockSource& out_eGenlockSource,
		EMvMXOOutputResolution& out_eGenlockVideoFormat,
		int32_t&  out_refi32GenlockHorizontal,
		int32_t&  out_refi32GenlockVertical,
	   bool&	  out_refbInputDetection,
	   bool&	  out_refbInputDetectionKeepAR,
	   EMvAspectRatio& out_refeInputDetectionRatio
		) = 0;

	// Summary:
	//        Retrieve the DVI In active resolution
	// Description:
	//		 Retrieve the real DVI In active resolution we received from the graphic card
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.  
	virtual HRESULT GetDVIInActiveResolution
		(
		uint32_t& out_ui32Width, // The real width send by the graphic card
		uint32_t& out_ui32Height // The real height send by the graphic card
		) = 0;

	// Summary:
	//        Get the active video output rectangle
	// Description:
	//		 Get the active video output rectangle
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.  
	virtual HRESULT GetActiveVideoOutputRect
		(
		SMvRect &out_sActiveVideoOutRect // rectangle of the active video output
		) = 0;

	// Summary:
	//		 Get the rectangle of the input canvas after cropping
	// Description:
	//		 Get the rectangle of the input canvas after cropping, the one this is visible at the output
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.  
	virtual HRESULT GetRealInputRect
		(
		SMvRect& out_sInputRect,
		EMvMXOOutputResolution in_eOutputResolution
		) = 0;

	// Summary:
	//		 Checks if all the input is represented on the output or if cropping is involved.
	// Description:
	//		 Checks if all the input is represented on the output or if cropping is involved.
	// Return value:
	//    - true if there is cropping applied to the input canvas.
	//    - false if there is no cropping applied to the input canvas.  
	virtual bool IsInputCanvasCropped
		(
		SMvRect& in_rectInputCanvas,
		EMvMXOOutputResolution in_eOutputResolution
		) = 0;

	// Summary:
	//        Set the video output parameters
	// Description:
	//		 Set the video output parameters for cropping, scaling and border
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
	virtual HRESULT SetVideoOutput
		(
		uint32_t						in_ui32TransportResolutionWidth,  // DVI Input Width
		uint32_t						in_ui32TransportResolutionHeight, // DVI Input Height
		EMvMXOOutputResolution	in_eOutputResolution,	   // Video Output Resolution
		uint32_t						in_ui32CropLeftAmount,     // Determines the amount of pixels to crop on left side.  
		uint32_t						in_ui32CropRightAmount,    // Determines the amount of pixels to crop on right side.   
		uint32_t						in_ui32CropTopAmount,      // Determines the amount of pixels to crop on top.     
		uint32_t						in_ui32CropBottomAmount,   // Determines the amount of pixels to crop on bottom.
		bool							in_bIsOverScan,			   // If true, determines if the monitor overscan is faked
                                                         // (mostly for dvi monitor).
		EMvConvertDVIScalingMethod in_eScalingMode,		   // Determine the scaling algorithm used
		SMvRect*						in_pScaledOutputRect,	   // Determine the output rectangle in the case of not a
                                                         // centered output, NULL otherwise
		bool							in_bApplySquareInputCompensation,   // If true, determines if the source square pixel
                                                                  // compensation is applied.
		EMvAspectRatio				in_eARCompensation         // Determines if the square pixel compensation for 4:3 or 16:9
                                                         // output is applied.
		) = 0;

	// Summary:
	// Set the position of the video output
	// Description:
	//		 Set the video output position depending on the top-left coordinate of the desired output
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
	virtual HRESULT SetVideoOutputPosition
		(
		EMvScanMode in_eOutputScanMode,  // scan mode of the output
		EMvMXOOutputResolution eOutputResolution, // resolution of the output
		uint32_t in_ui32Left,            // Left-most position of the output
		uint32_t in_ui32Top              // Top-most position of the output
		) = 0;

	// Summary:
	// Calculate the size of the output
	// Description:
	//		 This function calculate the size of the resulting video output depending on the scaling method and the input
   //     size.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
	virtual HRESULT CalculateOutputSize
		(
		uint32_t&	   io_ui32GraphicInputWidth,	// DVI Input Width
		uint32_t&	   io_ui32GraphicInputHeight,	// DVI Input Height
		uint32_t		   in_ui32FullOutputWidth,		// Full Output Width
		uint32_t		   in_ui32FullOutputHeight,	// Full Output Height
		EMvMXOOutputResolution in_eOutputResolution,   // Video Output Resolution
		uint32_t		   in_ui32CropLeftAmount,		// Determines the amount of pixels to crop on left side.
		uint32_t		   in_ui32CropRightAmount,		// Determines the amount of pixels to crop on right side.
		uint32_t		   in_ui32CropTopAmount,		// Determines the amount of pixels to crop on top.
		uint32_t		   in_ui32CropBottomAmount,	// Determines the amount of pixels to crop on bottom.
		bool			   in_bIsOverScan,				// If true, determines if the monitor overscan is faked (mostly for dvi
                                                // monitor).
		EMvConvertDVIScalingMethod in_eScalingMode,        // Determines the scaling algorithm used.
		bool			   in_bApplySquareInputCompensation,   // If true, determines if the source square pixel compensation
                                                         // is applied.
		EMvAspectRatio	in_eARCompensation,			// Determines if the square pixel compensation for 4:3 or 16:9 output
                                                // is applied.
		bool				in_bRespectScalingLimits,	// If true, determines if scaling limits are applied.
		SMvRect*			in_pScaledOutputRect,		// Determines the custom output rectangle.
		uint32_t&		out_ui32ActiveOutputWidth,	// Indicates the resulting output width.
		uint32_t&		out_ui32ActiveOutputHeight	// Indicates the resulting output height.
		) = 0;

	// Summary:
	//        Set the audio delay
	// Description:
	//		 Set the audio delay parameters
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
	virtual HRESULT SetAudioDelay
		(
		EMvMXOOutputResolution in_eOutputResolution,    // Output resolution to calculate samples
		uint32_t in_ui32AudioDelay                      // number of frame to delay
		) = 0;


	// Summary:
	//        Set the active procamp parameters
	// Description:
	//		 Set the active procamp parameters (Hue, Chroma, Brightness, Contrast)
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.  
	virtual HRESULT SetProcAmpCurrentValues
		(
		EMvMXOOutputResolution in_eOutputResolution,
		int32_t &in_i32Hue,			// procamp hue parameters
		int32_t &in_i32Chroma,		// procamp chroma parameters
		int32_t &in_i32Brightness,	// procamp brightness parameters
		int32_t &in_i32Contrast		// procamp contrast parameters
		) = 0;

	// Summary:
	//       Get the scaler limits
	// Description:
	//		 Get the scaler horizontal/vertical minimum and maximum scaling factor
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.  
	virtual HRESULT GetScalerLimits
		(
		uint32_t in_ui32InputWidth,
		uint32_t in_ui32InputHeight,
		uint32_t in_ui32OutputWidth,
		uint32_t in_ui32OutputHeight,
		EMvMXOOutputResolution in_eOutputRes,
		uint32_t in_ui32InputPixelCount,
		double& out_dMinHorizontal,
		double& out_dMaxHorizontal,
		double& out_dMinVertical,
		double& out_dMaxVertical
		) = 0;

	// Summary:
	//     Determines if it is a Convert DVI or Convert DVI+.
	// Description:
	//	   Checks the USBID and determines if it's a Convert DVI or Convert DVI+.
	// Return value:
	//    - true if it's a Convert DVI+.
	//    - false if it's a Convert DVI.
	virtual bool IsConvertDVIPlus() = 0;
   
   // Summary:
	//     Get the maximum audio frames delay
	// Description:
	//	   Get the maximum audio frames delay we can get depending on
	//	   the output resolution (delay is in samples)
	// Return value:
	//    - uint32_t value representing the maximum audio delay in frames
	virtual uint32_t GetMaxAudioDelayFrames
		(
		EMvMXOOutputResolution in_eOutputResolution
		) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Enumerates all MXO devices in the system and is returned to the user by IMvMXOControlFactory.
// Description:
//  This interface used to enumerate MXO devices in system.  
////////////////////////////////////////////////////////////////////////////////////
interface IMvEnumMXOControl : public IUnknown
{
public:
	//Skips over the next specified number of elements in the enumeration sequence.   
	virtual HRESULT GetCount(unsigned long &out_refulCount) = 0;

	//Skips over the next specified number of elements in the enumeration sequence.   
	virtual HRESULT Skip(unsigned long in_ulElementsToSkip) = 0;

	//Resets the enumeration to the beginning.   
	virtual HRESULT Reset() = 0;

	//The Next method retrieves a specified number of items in the enumeration sequence.
	virtual HRESULT Next
      (
      unsigned long in_ulElements,
      IMvMXOControl** out_ppIMvMXOControl,
      unsigned long& out_refulElementsReturned
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Returns IMvMXOControl to get control of the MXO.
// Description:
//		This interface returns IMvMXOControl to get control of the MXO. 
//		This interface is supported on a COM object created with CLSID_MvMXOControlFactory.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvMXOControlFactory: public IUnknown
{
public:

	// Summary:
	//     Retrieves MXO control by identifying the MXO by its DVI connection to the 
	//		 computer's display card (as specified in Windows control panel)
	// Description:
	//		 Retrieves MXO control by identifying the MXO by its DVI connection to the 
	//		 computer's diplay card. This method uses the same device index that Windows 
	//		 uses to identify multiple monitors. Users can go to the <b>Settings</b> tab 
	//		 of the <b>Display Properties</b> dialog box, and then click <b>Identify</b> 
	//		 to show the primary (1) and secondary (2) displays that are connected to the system.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
	virtual HRESULT GetMXOControlFromControlPanelMonitorID
		(
		uint32_t        in_ui32ControlPanelMonitorID,   // Specifies the control panel monitor identifier where the MXO
                                                      // is connected.
		IMvMXOControl** out_ppIMvMXOControl             // Pointer that receives the IMvMXOControl interface.
		) = 0;

	// Summary:
	//    Retrieves MXO control from a unique ID based on the MXO serial number. 
	//		 The unique ID is needed to identify the desired MXO.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
	virtual HRESULT GetMXOControlFromMXOUniqueID
		(
		uint32_t        in_ui32MXOUniqueID,    // Specifies the MXO unique ID.
		IMvMXOControl** out_ppIMvMXOControl    // Pointer that receives the IMvMXOControl interface.
		) = 0;

	// Summary:
	//    Retrieves MXO control from an SMvHardwareProfileInfo structure. 
	// Return value:
	//    - MV_E_NOT_IMPLEMENTED, if the operation has not been implemented.
	//    - MV_E_FAIL, if an unexpected error occurs.   
	virtual HRESULT GetMXOControlFromHardwareProfile
		(
		SMvHardwareProfileInfo& in_refsHWProfileInfo, // Describes the hardware profile.
		IMvMXOControl** out_ppIMvMXOControl           // Pointer that receives the IMvMXOControl interface.
		) = 0;

	// Summary:
	//    Converts an MXO unique ID to a serial number.
	// Description:
	//		 This method converts an MXO unique ID to a serial number 
	//		 that identifies the MXO. The unique ID is needed to get control 
	//		 of the desired MXO using IMvMXOControlFactory::GetMXOControlFromMXOUniqueID.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
	virtual HRESULT ConvertMXOUniqueIDToMXOSerialNumberString
		(
		uint32_t  in_ui32MXOUniqueID,                // Specifies the unique ID to be converted.
		char*     io_pszSerialNumberString,          // Specifies the pre-allocated buffer where the serial number string 
		                                             // will be stored.
		uint32_t& io_refui32SerialNumberStringSize   // This parameter must be initialized with the size of the
                                                   // pre-allocated buffer, and then the size of the serial number 
                                                   // string. After the call, the pre-allocated buffer will only 
                                                   // contain the size used by the serial number string.    
		) = 0;

	// Summary:
	//    Converts an MXO serial number to a unique ID.
	// Description:
	//		 This method converts an MXO serial number to a unique ID that 
	//		 identifies the MXO. The unique ID is needed to get control of the 
	//		 desired MXO using IMvMXOControlFactory::GetMXOControlFromMXOUniqueID.  
	//	Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
	virtual HRESULT ConvertMXOSerialNumberStringToMXOUniqueID
		(
		char*     in_pszSerialNumberString,    // Specifies the serial number to be converted.
		uint32_t& out_refui32MXOUniqueID       // Specifies the MXO unique ID.
		) = 0;

	// Summary:
	//    Returns a handle to an event that will occur when a new MXO is connected 
	//		 using the USB connector and power cord.
	// Description:
	//		 Returns a handle to an event that will occur when a new MXO is connected 
	//		 using the USB connector and power cord. The MXO will be detected by the 
	//		 computer only when both the USB connector and power cord are connected.         
	//	Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
	// Remarks:
	//  	 - Only one thread can wait on the event.
	//  	 - Caller must close the handle when finished using the event.
	virtual HRESULT GetNewMXODetectedEvent
		(
		HANDLE & out_refhEvent  // Returns the event. 
		) = 0;

	// Summary:
	//    Returns a handle to an event that will occur when the USB connector or power cord 
	//		 is disconnected from the MXO.   
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
	// Remarks
	//  	 - Only one thread can wait on the event.
	//  	 - Caller must close the handle when finished using the event. 
	virtual HRESULT GetMXODisconnectedEvent
		(
		HANDLE & out_refhEvent  // Returns the event. 
		) = 0;

	// Summary:
	//    Returns a handle to an event that will occur when a DVI monitor is connected to the 
	//		 DVI OUT on MXO.   
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
	// Remarks:
	//  	 - Only one thread can wait on the event.
	//  	 - Caller must close the handle when finished using the event.
	virtual HRESULT GetMonitorConnectedEvent
		(
		HANDLE & out_refhEvent  // Returns the event. 
		) = 0;

	// Summary:
	//    Returns a handle to an event that will occur when a DVI monitor is disconnected from
	//		 the DVI OUT on MXO.  
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
	// Remarks:
	//  	 - Only one thread can wait on the event.
	//  	 - Caller must close the handle when finished using the event.
	virtual HRESULT GetMonitorDisconnectedEvent
		(
		HANDLE & out_refhEvent  // Returns the event. 
		) = 0;

	// Summary:
	//    Returns a handle to an event that will occur when the DVI cable from the computer is 
	//		 connected to the DVI IN connector on the MXO.  
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
	// Remarks:
	//  	 - Only one thread can wait on the event.
	//  	 - Caller must close the handle when finished using the event.
	virtual HRESULT GetDVICableConnectedEvent
		(
		HANDLE & out_refhEvent  // Returns the event.
		) = 0;

	// Summary:
	//    Returns a handle to an event that will occur when the DVI cable from the computer is 
	//		 disconnected from the DVI IN connector on the MXO. 
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
	// Remarks:
	//  	 - Only one thread can wait on the event.
	//  	 - Caller must close the handle when finished using the event.
	virtual HRESULT GetDVICableDisconnectedEvent
		(
		HANDLE & out_refhEvent  // Returns the event. 
		) = 0;

	// Summary:
	//    Returns a handle to an event that will occur when the MXO genlock settings are changed.     
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an unexpected error occurs.
	// Remarks:
	//  	 - Only one thread can wait on the event.
	//  	 - Caller must close the handle when finished using the event.
	virtual HRESULT GetGenlockStatusChangeEvent
		(
		HANDLE & out_refhEvent  // Returns the event. 
		) = 0;

	// Summary:
	//    Notify the factory that an event have been signaled
	// Remark:
	//    It is now the responsability of the owner of the factory
	//    to notify that an even was signal
	// Return value:
	//    - MV_NOERROR, if operation succeeded.
	//    - MV_E_FAIL, if an unexpected error happened.
	virtual HRESULT Notify
		(
		const int in_kiEventID // Event id notified
		) = 0;

	// Summary:
	//    Resets the enumeration to the beginning.
	// Remark:
	//    Resets the enumeration to the beginning.
	// Return value:
	//    - MV_NOERROR, if operation succeeded.
	//    - MV_E_FAIL, if an unexpected error happened.
	virtual HRESULT Reset() = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Enables or disables the output on a connected card.
// Remarks:
//    - This interface is only supported in MXO devices and the X.DVI module.
//    - That interface is available from the IMvInputOutputIndependent interface, 
//       and is exposed by Flex Input and Output.
//////////////////////////////////////////////////////////////////////////////////
interface IMvOutputControl: public IUnknown
{
public:
	// Summary:
	//    Enables output on the card.
	// Return value:
	//    - MV_NOERROR, if operation succeeded.
	//    - MV_E_FAIL, if an error occurs.
	virtual HRESULT EnableOutput() = 0;

	// Summary:
	//    Disables output on the card.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_FAIL, if an error occurs.
	virtual HRESULT DisableOutput() = 0;

	// Summary:
	//    Indicates whether the output is enabled or not.
	// Return value:
	//    - MV_TRUE, if the output is enabled.
	//    - MV_FALSE, if the output is disabled.
	virtual HRESULT IsOutputEnabled() = 0;
};

///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that allows to control the output through DVI ports on graphics
//    cards.
//
///////////////////////////////////////////////////////////////////////////////
interface IMvDisplayManager: public IUnknown
{
public:

	//
	// Summary:
	//	   This method will list the number of DVI heads connected to devices on the 
	//    current board profile.
	// Return value:
	//	   Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetDVIDeviceCount
		(
		unsigned int* out_puiNbHeads     // Returns the number of DVI ports that can be used for playback
		) = 0;

	//
	// Summary:
	//    Retrieves available playback channels.
	//    This enumerated information is used by other methods to get specific controls.
	//    The parameters must be allocated by the caller using the GetDVIDeviceCount() method
	// Return value:
	//	   Returns an error if the command failed or if the parameters are invalid.
	virtual HRESULT __stdcall GetPlaybackChannels
		(
		unsigned int                       in_uiDVIPlaybackChannelCount,     // Specifies the count of the structures in 
                                                                           // the array.
		SMvDVIPlaybackChannelDescription * io_psPlaybackChannelDescription   // An array of channel struct available for 
                                                                           // playback.

		) = 0;

	//
	// Summary:
	//	   Controls the resolution of the Display Manager.
	// Return value:
	//	   Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall ControlVideoPlaybackResolution
		(
		const EMvIOCommand in_eIOCommand,       // Specifies the command that describes what to do with the parameters. 
                                              // The keIOCommandRange is not supported for this call.
		SMvResolutionInfo* io_psResolutionInfo, // Specifies the video playback resolution.
		                                        // It must be allocated by the user.
		const SMvDVIPlaybackChannelDescription& in_rsDVIPlaybackChannelDescription // Provides the video playback channel 
		                                                                           // that provides the interface
		) = 0;

	//
	// Summary:
	//	   Retrieves an IMvVideoPlaybackControl interface
	// Return value:
	//	   Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetVideoPlaybackInterface
		(
		const SMvDVIPlaybackChannelDescription & in_rsDVIPlaybackChannelDescription,  // Provides the video playback 
                                                                                    // channel that provides the 
                                                                                    // interface.
		IMvVideoPlaybackControl**                 out_ppIVideoPlaybackControl         // Returns a pointer to the 
		                                                                              // IMvVideoPlaybackControl interface.
		) = 0;
};

///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that allows control of codec options.
//
///////////////////////////////////////////////////////////////////////////////
interface IMvCodecOption : public IUnknown
{
public:
	//
	// Summary:
	//	   Retrieves the codec option specified by the EMvCodecOption enumerator.
	// Return value:
	//	   Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetCodecOption
		(
		MVCHANDLE      io_pmvchOptionValue,    // Pointer to the requested codec option. This must
		                                       // be cast to its proper type.
		EMvCodecOption in_eCodecOption         // Specifies the type of codec option requested.
		) = 0;

	//
	// Summary:
	//	   Sets the codec option specified by the EMvCodecOption enumerator.
	// Return value:
	//	   Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall SetCodecOption
		(
		MVCHANDLE      in_pmvchOptionValue,    // Pointer to the codec option being set.
		EMvCodecOption in_eCodecOption         // Specifies the type of codec option to be set.
		) = 0;

	//
	// Summary:
	//	   Queries whether the codec option specified by the EMvCodecOption enumerator is supported by the codec.
	// Return value:
	//	   Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall IsCodecOptionSupported
		(
		EMvCodecOption in_eCodecOption,     // Specifies the type of codec option being queried.
		bool*          out_pbSupported      // If true, the codec option is supported.
		) = 0;
};

///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that defines the base compression and decompression
//    methods for an audio codec.
//
///////////////////////////////////////////////////////////////////////////////
interface IMvAudioCodec : public IMvCodecOption
{
public:

	//
	// Summary:
	//    Provides compressed audio samples for the codec to decompress. 
	//    Also provides media positions for each audio sample to keep track of the sample's position in the stream.
	// Return value:
	//    Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall PutCompressedAudioSamples
		(
		IMvAudioSamples*  io_pIMvAudioSamplesIn,        // Pointer to the input audio sample buffer.
		unsigned long     in_ulMediaPositionInSamples   // Media position of the first audio sample in the buffer.
		) = 0;

	//
	// Summary:
	//    Requests uncompressed audio samples from the codec starting at a specific
	//    media position.
	// Return value:
	//    Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetUncompressedAudioSamples
		(
		IMvAudioSamples*  io_pIMvAudioSamplesOut,       // Pointer to the output audio sample buffer.
		unsigned long     in_ulMediaPositionInSamples   //  Media position of the first requested audio sample in the buffer.
		) = 0;

	//
	// Summary:
	//    Provides uncompressed audio samples for the codec to compress.
	// Return value:
	//    Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall PutUncompressedAudioSamples
		(
		IMvAudioSamples* io_pIMvAudioSamplesIn       // Pointer to the input audio sample buffer.
		) = 0;

	//
	// Summary:
	//    Requests the next set of compressed audio samples from the codec.
	// Return value:
	//    Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetCompressedAudioSamples
		(
		IMvAudioSamples* io_pIMvAudioSamplesOut      // Pointer to the output audio sample buffer.
		) = 0;

};


///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that defines the base compression and decompression
//    methods of a video codec.
//    
///////////////////////////////////////////////////////////////////////////////
interface IMvVideoCodec : public IMvCodecOption
{
public:
	//
	// Summary:
	//    Provides a compressed surface for the codec to decompress, as well as the surface's media position.
	//    "Put" operations are performed based on the order the frames within the stream are encoded, but the media 
   //    position is based on the order the frames are displayed (presentation order). 
	//    For example, a stream of "I, B, B, P, B, B" frames may be encoded in the order "0, 1, 2, 3, 4, 5" but
   //    displayed in the order "2, 0, 1, 5, 3, 4".
	// Return value:
	//    Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall PutCompressedSurface
		(
		IMvSurface*       io_pIMvSurfaceIn,             // Pointer to the input compressed surface.
		unsigned long     in_ulMediaPosition            // Specifies the media position of the surface.
		) = 0;

	//
	// Summary:
	//    Requests an uncompressed surface from the codec starting at a specific
	//    media position.
	// Return value:
	//    Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetUncompressedSurface
		(
		IMvSurface*       io_pIMvSurfaceOut,             // Pointer to the output uncompressed surface.
		unsigned long     in_ulMediaPosition             // Specifies the media position of the surface.
		) = 0;

	//
	// Summary:
	//    Provides an uncompressed surface for the codec to compress.
	// Return value:
	//    Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall PutUncompressedSurface
		(
		IMvSurface* io_pIMvSurfaceIn       // Pointer to the input uncompressed surface.
		) = 0;

	//
	// Summary:
	//    Requests the next set of compressed surfaces from the codec.
	// Return value:
	//    Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall GetCompressedSurface
		(
		IMvSurface* io_pIMvSurfaceOut      // Pointer to the output compressed surface.
		) = 0;
};


///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//   Interface that defines the base methods of a streaming codec.
//   This interface is not derived from IUnknown in order to avoid having duplicate copies of IUnknown in the
//   bundle interfaces IMvVideoStreamingCodec and IMvAudioStreamingCodec.
//
///////////////////////////////////////////////////////////////////////////////
interface IMvStreamingCodec 
{
public:
#ifdef LINUX_PLATFORM
	// virtual destructor for Linux warning
	virtual ~IMvStreamingCodec(){};
#endif


	//
	// Summary:
	//    Informs the codec that data is about to be sent for
	//    decompression.
	// Return value:
	//    Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall OpenDecompressionStream
		(
		MVCHANDLE      in_pmvchOptionValue, // Pointer to the codec options used to initialize the codec for decompression.
		EMvCodecOption in_eCodecOption      // Specifies the codec options being provided.
		) = 0;

	//
	// Summary:
	//    Informs the codec that decompression commands have completed queuing.
	// Return value:
	//    Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall CloseDecompressionStream(void) = 0;

	//
	// Summary:
	//    Informs the codec that data is about to be sent for
	//    compression.
	// Return value:
	//    Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall OpenCompressionStream
		(
		MVCHANDLE      in_pmvchOptionValue, // Pointer to the codec options used to initialize the codec for compression.
		EMvCodecOption in_eCodecOption      // Specifies the codec options being provided.
		) = 0;

	//
	// Summary:
	//    Informs the codec that compression commands have completed queuing.
	// Return value:
	//    Returns an error if the command failed or if there are invalid parameters.
	virtual HRESULT __stdcall CloseCompressionStream(void) = 0;

};

///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//   Interface that defines the base methods of a streaming hardware codec, and includes transport commands and states.
//   This interface is not derived from IUnknown in order to avoid having duplicate copies of IUnknown in the bundle
//    interface IMvVideoHWStreamingCodec.
//
///////////////////////////////////////////////////////////////////////////////
interface IMvCodecState 
{
public:
#ifdef LINUX_PLATFORM
	// virtual destructor for Linux warning
	virtual ~IMvCodecState(){};
#endif

	//
	// Summary:
	//    Informs the codec that the stream is about to go into a Play state.
	// Return value:
	//    Returns an error if the command failed.
	virtual HRESULT __stdcall Play() = 0;

	//
	// Summary:
	//    Informs the codec that the stream is about to go into a Pause state.
	// Return value:
	//    Returns an error if the command failed.
	virtual HRESULT __stdcall Pause() = 0;

	//
	// Summary:
	//    Informs the codec that the stream is about to go into a Stop state.
	//    This method must be called when all "put" and "get" operations for a given stream have been performed.
	// Return value:
	//    Returns an error if the command failed.
	virtual HRESULT __stdcall Stop() = 0;

	//
	// Summary:
	//    Informs the codec that the stream is about to go into a Seek state.
	// Return value:
	//    Returns an error if the command failed.
	virtual HRESULT __stdcall Seek() = 0;

	//
	// Summary:
	//    Informs the codec that the stream is about to go into a Step state.
	// Return value:
	//    Returns an error if the command failed.
	virtual HRESULT __stdcall Step() = 0;

	//
	// Summary:
	//    Informs the codec that the stream is about to go into a Shuttle state.
	// Return value:
	//    Returns an error if the command failed.
	virtual HRESULT __stdcall Shuttle
		(
		double in_dblSpeed,  // Specifies the shuttling speed.
		double* out_pdblReturnSpeed
		) = 0;

	//
	// Summary:
	//    Informs the codec that all data for a given stream has been sent.
	//    This method must be called when all "put" operations for a given stream have been performed.  
	// Return value:
	//    Returns an error if the command failed.
	virtual HRESULT __stdcall EndOfStream() = 0;
};


///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that combines the IMvAudioCodec and IMvStreamingCodec
//    interfaces to define the base interface for streaming audio codecs.
//
///////////////////////////////////////////////////////////////////////////////
interface IMvAudioStreamingCodec : public IMvAudioCodec, public IMvStreamingCodec
{
};

///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Bundle interface for a streaming video codec that combines the IMvVideoCodec and IMvStreamingCodec
//    interfaces to define the base interface for streaming video codecs.
//
///////////////////////////////////////////////////////////////////////////////
interface IMvVideoStreamingCodec : public IMvVideoCodec, public IMvStreamingCodec
{
};


///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Bundle interface for streaming video codecs that includes the codec state (Play, Seek, Step, etc)
//    interfaces to define the base interface for streaming video codecs.
//
///////////////////////////////////////////////////////////////////////////////
interface IMvVideoStreamingCodecWithState : public IMvVideoStreamingCodec, public IMvCodecState
{

};

///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Bundle interface for a streaming hardware video codec.
//    This interface combines the IMvVideoStreamingCodec and IMvCodecState
//    interfaces to define the base interface for streaming hardware video codecs.
//
///////////////////////////////////////////////////////////////////////////////
#define IMvVideoHWStreamingCodec IMvVideoStreamingCodecWithState


///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates audio codecs installed on the system.
//    This interface can be obtained from the IMvFlexEngine interface.
//
///////////////////////////////////////////////////////////////////////////////
interface IMvAudioCodecEnumerator : public IUnknown
{
	//
	// Summary:
	//    Gets the next available audio codec installed on the system.
	// Description:
	//    The next audio codec installed on the system is retrieved from the internal list of audio codecs.
	// Return value:
	//    - MV_NOERROR, if properly filled. 
	//    - MV_E_END_OF_ENUM, if there is no more audio codec information to enumerate. 
	//    - MV_E_INVALID_STRUCTURE_SIZE, if the structure size of out_psCodecInfo is not initialized properly.
	virtual HRESULT __stdcall Next 
		( 
		unsigned long       in_ulNbCodecInfoRequested,  // Number of entries in the audio codec information structure.
		SMvAudioCodecInfo * out_psCodecInfo,            // Pointer to the array of structures describing the audio codec
                                                      // information.
		unsigned long *     out_pulCodecInfoFetched     // Pointer to the number of entries that have been filled in the 
                                                      // array of structures.
		) = 0;

	//
	// Summary:
	//    Resets the internal counter to the first audio codec found on the system.
	// Description:
	//    The internal pointer is reset so that the next call to IMvAudioCodecEnumerator::Next returns the first audio
   //    codec found on the system.
	// Return value:
	//    - Always returns MV_NOERROR. 
	virtual HRESULT __stdcall Reset () = 0;

	//
	// Summary:
	//    Skips a given number of audio codecs.
	// Description:
	//    The internal pointer is changed so that the next call to IMvAudioCodecEnumerator::Next skips a given number 
   //    of audio codecs in the internal list.
	// Return value:
	//    - Always returns MV_NOERROR. 
	virtual HRESULT __stdcall Skip
		(
		unsigned long in_ulCount   // Number of audio codecs to skip.
		) = 0;
};


///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates all video codecs installed on
//    the system. This interface can be obtained from the IMvFlexEngine interface.
// Remarks:
//    - The IMvCodecEnumerator interface can still be used for non-streaming codecs only, whereas the
//      IMvVideoCodecEnumerator interface works for all video codecs: streaming and non-streaming.
//
///////////////////////////////////////////////////////////////////////////////
interface IMvVideoCodecEnumerator : public IUnknown
{
	//
	// Summary:
	//    Gets the next available video codec installed on the system.
	// Description:
	// The next video codec installed on the system is retrieved from the internal list of video codecs.
	// Return value:
	//    - MV_NOERROR, if properly filled. 
	//    - MV_E_END_OF_ENUM, if there is no further video codec information to enumerate. 
	//    - MV_E_INVALID_STRUCTURE_SIZE, if the structure size of out_psCodecInfo is not initialized properly.
	virtual HRESULT __stdcall Next 
		( 
		unsigned long        in_ulNbCodecInfoRequested,    // Number of entries in the video codec information structure.
		SMvVideoCodecInfo  * out_psCodecInfo,              // Pointer to the array of structures describing the video
                                                         // codec information structure.
		unsigned long *      out_pulCodecInfoFetched       // Pointer to the number of entries that have been filled in
                                                         // the array of structures.
		) = 0;

	//
	// Summary:
	//    Resets the internal counter to the first video codec found on the system.
	// Description:
	//    The internal pointer is reset so that the next call to IMvVideoCodecEnumerator::Next returns the first video
   //    codec found on the system.
	// Return value:
	//    - Always returns MV_NOERROR. 
	virtual HRESULT __stdcall Reset () = 0;

	//
	// Summary:
	//    Skips a given number of video codecs.
	// Description:
	//    The internal pointer is reset so that the next call to IMvVideoCodecEnumerator::Next skips a given number of 
   //   video codecs in the internal list.
	// Return value:
	//    - Always returns MV_NOERROR. 
	virtual HRESULT __stdcall Skip
		(
		unsigned long in_ulCount   // Number of video codecs to skip.
		) = 0;
};
///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates all H264 Decoder installed on
//    the system. This interface can be obtained from the IMvFlexEngine interface.
//
///////////////////////////////////////////////////////////////////////////////
interface IMvH264DecoderEnumerator : public IUnknown
{
   //
   // Summary:
   //    Get the total count of H264 Decoder.
   // Return value:
   //    - Always returns MV_NOERROR. 
   virtual HRESULT __stdcall GetCount
      (
      uint8_t *out_pui8Count   // Number of H264 Decoder 
      ) = 0;
   //
   // Summary:
   //    Gets t H264 Decoder CLSID according to the Index
   // Description:
   // To retrieve the next AVC Decoder class ID installed on the system 
   // Return value:
   //    - MV_NOERROR, if properly filled. 
   //    - MV_E_END_OF_ENUM, if there is no further video codec information to enumerate. 
   virtual HRESULT __stdcall GetInfo
      (
         uint8_t               in_ui8Index,                              // Index for AVC decoder CLSID
         CLSID                 * out_pCLSIDH264DecoderCLSID              // Pointer to CLSID of the AVC decoder           
      ) = 0;

  

};

///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that exposes functions to "get" and "set" codec configuration data, such as
//    an ADIF header or MPEG-4 AudioSpecificConfig element.
//
///////////////////////////////////////////////////////////////////////////////
interface IMvAACCodecConfigDataAccess : public IUnknown
{
	//
	// Summary:
	//    Sets the current AudioSpecificConfig data.
	// Return value:
	//    - MV_NOERROR               If completed successfully.
	//    - MV_E_INVALID_POINTER     If the SMvAACConfigDataStream pointer is NULL.
	virtual HRESULT __stdcall SetConfigData
		(
		SMvAACConfigDataStream    * in_psAudioSpecificConfig       // Provides input stream information.
		) = 0;

	//
	// Summary:
	//    Gets the current AudioSpecificConfig data.
	// Return value:
	//    - MV_NOERROR               If completed successfully.
	//    - MV_E_INVALID_POINTER     If the SMvAACConfigDataStream pointer is NULL.
	//    - MV_E_NOT_INITIALIZED     If not initialized by a SetConfigData or a Configure call.
	virtual HRESULT __stdcall GetConfigData
		(
		SMvAACConfigDataStream    * out_psAudioSpecificConfig      // Provides output stream information.
		) = 0;
};


///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Generic notification interface on an IMvAVContent.
//
///////////////////////////////////////////////////////////////////////////////
interface IMvCompletionCallback : public IUnknown
{
	//
	// Summary:
	//    Notifies that something is completed on the given IMvAVContent.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_POINTER, if the in_pIAvContent pointer is NULL.
	virtual HRESULT __stdcall Notify
		( 
		IMvAVContent* in_pIAvContent // Notified IMvAVContent.
		) = 0;
};

///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Generic notification interface on any object.
//
///////////////////////////////////////////////////////////////////////////////
interface IMvCompletionObserver : public IUnknown
{
	//
	// Summary:
	//    Notifies that something is completed.
	// Return value:
	//    - MV_NOERROR, if completed successfully.
	//    - MV_E_INVALID_POINTER, if the given pointer is NULL.
	virtual HRESULT __stdcall NotifyCompletion
		( 
		IUnknown* in_pIUnknown 
		) = 0;
};

///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Exposes functions that help generate AudioSpecificConfig
//    data for AAC audio streams.
//
///////////////////////////////////////////////////////////////////////////////
interface IMvAACAudioSpecificConfigHelper : public IMvAACCodecConfigDataAccess
{
	//
	// Summary:
	//    Provides the object with stream information that will allow it to
	//    generate AudioSpecificConfig data.
	// Return value:
	//    - MV_NOERROR,if completed successfully.
	//    - MV_E_INVALID_POINTER, if the SMvAACConfigurationInfo pointer is NULL.
	virtual HRESULT __stdcall ConfigureWithStreamInfo
		(
		SMvAACConfigurationInfo * in_psAACConfigInfo      // Provides AAC configuration information.
		) = 0;
};

interface IMvInformationCallback : public IUnknown
{
	//
	// Summary:
	//   Notifies the user application that something has changed.
   //    The HRESULT value is ignored.
	virtual HRESULT __stdcall NotifyProgress
		( 
		uint32_t in_ui32ProgressInPerCent
		) = 0;

   //
   // Summary:
   //    Notifies the user application of any changes to the current status of the indexing.
   //    If the user application returns an error code instead of returning MV_NOERROR, the indexing will be cancelled.
	virtual HRESULT __stdcall NotifyInformation
		(
		HRESULT      in_hr,
		EMvInfoType  in_eMvInfoType,
		wchar_t     *in_pwszNotificationString
		) = 0;
};

interface IMvIPInput : public IUnknown
{
	//
	// Summary:
	//    Opens an input session using the Input session structure.
	virtual HRESULT __stdcall OpenSession
		( 
		SMvIPInputSession *in_psSessionConfiguration
		) = 0;

	//
	// Summary:
	//    Closes an already opened session.
	virtual HRESULT __stdcall CloseSession
		(
		) = 0;

	//
	// Summary:
	//    Captures a video surface from a networked I/O.
	virtual HRESULT __stdcall CaptureSurface
		(
		IMvSurface* io_pICaptureSurface    // The surface to capture to.
		) = 0;

	//
	// Summary:
	//    Captures an audio sample from a networked I/O.
	virtual HRESULT __stdcall CaptureAudioSamples
		(
		IMvAudioSamples* io_pICaptureAudioSamples    // The audio samples to capture to.
		) = 0;
};

interface IMvIPOutput : public IUnknown
{
	//
	// Summary:
	//    Opens a input session using the Output session structure.
   virtual HRESULT __stdcall OpenSession
      ( 
      SMvIPOutputSession   *in_psSessionConfiguration,
      void                 *in_psStreamInformation,
      unsigned long         in_ulInfoSize
      ) = 0;

	//
	// Summary:
	//    Closes an already opened session.
	virtual HRESULT __stdcall CloseSession
		(
		) = 0;

	//
	// Summary:
	//    Plays out a video surface to a networked I/O.
	virtual HRESULT __stdcall PlaySurface
		(
		IMvSurface* io_pIPlaybackSurface    // The surface to play back.
		) = 0;

	//
	// Summary:
	//    Plays out an audio samples buffer to a networked I/O.
	virtual HRESULT __stdcall PlayAudioSamples
		(
		IMvAudioSamples* io_pIPlaybackAudioSamples    // The audio samples buffer to play back.
		) = 0;

   // Methods to use if the user wants to create a SDP file. To be used after the OpenSession call.
   virtual HRESULT __stdcall GetSDPDescriptionLength
      (
      unsigned long *out_pulSDPDescriptionLength          // Does not include the '\0'.
      ) = 0;

   virtual HRESULT __stdcall GetSDPDescription
      (
      char          *out_pszSDDescription,
      unsigned long  in_ulSDPDescriptionLength            // Length must include space for '\0'.
      ) = 0;
};

interface IMvIPInputOutput : public IUnknown
{
	//
	// Summary:
	//    Creates a Server session.
	virtual HRESULT __stdcall CreateIPOutputSession
		(
		SMvResolutionInfo	   * in_psVideoResolution,
		EMvSurfaceFormat	     in_eVideoFormat,
		SMvaWaveFormatInfo   * in_psWavFormatInfo,
		IMvIPOutput **	        out_ppIMvIPOutput
		) = 0;

	//
	// Summary:
	//    Creates a Client session.
	virtual HRESULT __stdcall CreateIPInputSession
		(
		SMvResolutionInfo	   * in_psVideoResolution,
		EMvSurfaceFormat	     in_eVideoFormat,
		SMvaWaveFormatInfo   * in_psWavFormatInfo,
		IMvIPInput **	        out_ppIMvIPInput
		) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
// 
//Summary:
//This interface is used to represent any generic VANC packets that are
//inserted into or extracted from a VANC surface.
// 
//////////////////////////////////////////////////////////////////////////////////
interface IMvGenericVancPacket : public virtual IUnknown 
{
public:
	//This method allows the user to retrieve the generic packet structure
	//that describes the VANC packet type and data.
	virtual HRESULT __stdcall GetGenericPacket(SMvGenericVancPacket& io_rsGenericPacket) = 0;

	//This method allows the user to modify the generic packet structure
	//that describes the VANC packet type and data.
	virtual HRESULT __stdcall SetGenericPacket(SMvGenericVancPacket& in_rsGenericPacket) = 0;

	//This method informs the user of the type of VANC packet being used,
	//as long as the type is defined in the EMvVANCPacketType
	//enumeration.
	virtual EMvVANCPacketType __stdcall GetPacketType() = 0;

	//This method allows the user to ensure the validity of the parity and checksum
	//of packets extracted from a VANC surface. It also ensures
	//that the VANC packet protocol is respected (for example, that marker bits are present
	//in the right places). This method always returns MV_NOERROR 
	//for packets that are not extracted from a surface.
	virtual HRESULT __stdcall GetExtractionError() = 0;

	//This method allows the user to specify if a packet should
	//overwrite another packet of the same type when inserted.
	//This method is only useful on a packet insertion operation.
	virtual HRESULT __stdcall EnableOverwrite(bool in_bEnableOverwrite) = 0;

   //This method allows the user to validate the current status of the packet.
   virtual HRESULT __stdcall ValidatePacket
      (
      bool* out_pbIsPacketValid,
      bool* out_pbIsParityValid,
      bool* out_pbIsChecksumValid
      ) = 0;

   //This method computes the UDW parity bits of the packet and adds them to it.
   virtual HRESULT __stdcall ComputeUDWParity() = 0;

   //This method informs the user of the line index where the packet was found. This index is zero-based.
   //The return value of this method is undefined if the packet was not
   //extracted from a surface.
   virtual unsigned long __stdcall GetAbsoluteLineNumber() = 0;

   //This method allows the user to set the line where the packet 
   //is to be inserted. This index is zero-based.
   //This method is only useful on a packet insertion operation.
   virtual HRESULT __stdcall SetAbsoluteLineNumber(unsigned long in_ulLine) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
// 
//Summary:
//This interface represents AFD and bar data VANC packets that are either
//inserted into or extracted from a VANC surface (SMPTE 2016-3 specification).
// 
//////////////////////////////////////////////////////////////////////////////////
interface IMvAFDAndBarDataVancPacket : public virtual IMvGenericVancPacket 
{
public:
	//This method retrieves the descriptive data contained in
	//a specific AFD and bar data VANC packet.
	virtual HRESULT __stdcall GetAFDAndBarDataPacket(SMvAFDAndBarDataVancPacket& io_rsAFDAndBarDataPacket) = 0;

	//This method modifies the data of a specific AFD and bar data
	//VANC packet using a specific descriptor.
	virtual HRESULT __stdcall SetAFDAndBarDataPacket(SMvAFDAndBarDataVancPacket& in_rsAFDAndBarDataPacket) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
// 
//Summary:
//This interface represents a CDP (Caption Data Packet) VANC packet that is either
//inserted into or extracted from a VANC surface (SMPTE 334-2 specification).
//This may include closed caption data.
// 
//////////////////////////////////////////////////////////////////////////////////
interface IMvCaptionDistributionVancPacket : public virtual IMvGenericVancPacket 
{
	// This method modifies the data of a CDP VANC packet using a specific descriptor.
	virtual HRESULT __stdcall SetCaptionDistributionPacket
      (
      SMvCaptionDistributionPacket & in_refsCaptionDistributionPacket
      ) = 0;

	// This method retrieves the descriptive data contained in a specific CDP VANC packet.
	virtual HRESULT __stdcall GetCaptionDistributionPacket
      (
      SMvCaptionDistributionPacket & io_refsCaptionDistributionPacket
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
// 
//Summary:
// Interface that groups one or more IMvGenericVancPacket interfaces
// for easier management of multiple packets.
// 
//////////////////////////////////////////////////////////////////////////////////
interface IMvVancPacketsContainer : public IUnknown
{
   //
   // Summary:
   //    Adds a packet to the container.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // 
   virtual HRESULT __stdcall AddPacket
	   (
	   IMvGenericVancPacket * in_pIPacket  // Pointer to the packet interface to add to the list of VANC packets
                                          // managed by the container.
	   ) = 0;

   // Summary:
   //    Gets the number of packets in the container.
   // Return value:
   //    - unsigned long: Returns the number of packets in the container. 
   // 
   virtual unsigned long __stdcall GetPacketsCount() = 0;

   // Summary:
   //    Gets the packet corresponding to the index passed as parameter.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Use GetPacketsCount to find out how many packets are in the container.
   // 
   virtual HRESULT __stdcall GetPacket
      (
      unsigned long 			   in_ulIndex,    // Zero based index that indicates which packet to retrieve.
      IMvGenericVancPacket ** out_ppIPacket  // Pointer that receives the packet interface indicated in in_ulIndex.
      ) = 0;

   // Summary:
   //    Empties the container.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall EmptyContainer() = 0;
};


//////////////////////////////////////////////////////////////////////////////////
// 
//Summary:
//This interface is used by an IMvVancPacketExtractor implementing object to
//return the VANC packets, using a callback, when the extraction is performed.
// 
//////////////////////////////////////////////////////////////////////////////////
interface IMvVancPacketExtractorObserver : public IUnknown 
{
public:
   // This method is a callback used by an IMvVancPacketExtractor implementing object 
   // to return the VANC packets when the extraction is complete.
	virtual void __stdcall OnVancPacketExtraction(
		IMvSurface*             in_pISourceSurface, 
		IMvGenericVancPacket**  in_apIGenericPacketArray, 
		unsigned long           in_ulArraySize) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
// 
//Summary:
//This interface is used to extract VANC packets from a VANC buffer using a simple
//descriptor that represents the data inside the packet.
// 
//////////////////////////////////////////////////////////////////////////////////
interface IMvVancPacketExtractor : public IUnknown 
{
public:
   // This method queues a VANC packet extraction on the specified source
   // surface. When extracted, the packets are passed to
   // an IMvVancPacketExtractorObserver implementing object by a callback.
   // The parameter in_iVancPacketType is a combination of EMvVANCPacketType enumerators representing
   // the packet types the user is interested in receiving.
	virtual HRESULT __stdcall ExtractVancPackets(
		IMvSurface*                      in_pIVancSurface, 
		IMvVancPacketExtractorObserver*  in_pIVancPacketObserver, 
		int                              in_iVancPacketType, 
		unsigned long                    in_ulIgnored) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
// 
//Summary:
//This interface is used to insert VANC packets into a VANC buffer using a simple
//descriptor that represents the data inside the packet.
// 
//////////////////////////////////////////////////////////////////////////////////
interface IMvVancPacketInserter : public IUnknown 
{
public:
	// This method is used to insert VANC packets into a VANC surface using a simple
	// descriptor that represents the data inside the packet.
	virtual HRESULT __stdcall InsertGenericVancPackets(
		IMvSurface*                in_pISrcSurface, 
		IMvGenericVancPacket**     in_apIGenericPacketArray, 
		unsigned long              in_ulArraySize, 
		IMvSurface*                io_pIDestSurface,
		unsigned long              in_ulIgnored) = 0;

   // This method is used to insert VANC packets into a VANC surface using a simple
   // descriptor that represents the data inside the packet.
   virtual HRESULT __stdcall InsertGenericVancPacketsFromContainer(
      IMvSurface*                in_pISrcSurface, 
      IMvVancPacketsContainer*   in_pIGenericPacketsContainer,
      IMvSurface*                io_pIDestSurface,
      unsigned long              in_ulIgnored) = 0;

	// This method is used to give the user an empty generic VANC packet
	// to fill with data, which will then be inserted into a VANC surface using
	// the InsertGenericVancPackets method.
	virtual HRESULT __stdcall GetEmptyGenericVancPacket
      (
      IMvGenericVancPacket ** out_ppIGenericVancPacket,
      unsigned long           in_ulIgnored
      ) = 0;

	// This method is used to give the user an empty AFD and bar data VANC packet
	// to fill with data, which will then be inserted into a VANC surface using
	// the InsertGenericVancPackets method.
	virtual HRESULT __stdcall GetEmptyAFDAndBarDataVancPacket
      (
      IMvAFDAndBarDataVancPacket ** out_ppIAFDAndBarDataPacket,
      unsigned long                 in_ulIgnored
      ) = 0;

	// This method is used to give the user an empty Caption Distribution VANC packet
	// to fill with data, which will then be inserted into a VANC surface using
	// the InsertGenericVancPackets method.
	virtual HRESULT __stdcall GetEmptyCaptionDistributionVancPacket
      (
      IMvCaptionDistributionVancPacket ** out_ppICaptionDistribuationPacket,
      unsigned long in_ulIgnored
      ) = 0;

   // This method is used to give the user an empty VANC packets container to fill
   // with VANC packets, which can then be used to insert all those VANC packets in
   // a VANC surface using the InsertGenericVancPacketsFromContainer method.
   virtual HRESULT __stdcall GetEmptyVancPacketsContainer(
      IMvVancPacketsContainer ** out_ppIVancPacketsContainer,
      unsigned long in_ulIgnored
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
// 
// Summary:
// This interface is used to convert VANC packets from one standard/resolution to another.
// Remarks:
// - Calling GetNbOfSurfacesNeededForClosedCaptioningConversion() will return an error if the desired conversion is not supported.
// 
//////////////////////////////////////////////////////////////////////////////////
interface IMvVancConverter : public IUnknown 
{
public:
   // Summary:
   // Converts closed caption information from one video standard to another.
   // Remarks:
   // - Supported specifications are CEA 608 (NTSC closed caption information) and SMPTE 334 (all standards, including NTSC). 
   // - Certain frame rate conversions are not compatible with this method (for example, 25 fps cannot be converted to 59.94 fps). 
   // 
	virtual HRESULT __stdcall ConvertClosedCaptioning(
		IMvSurface*       in_apIInputVANCSurfaces[],	// Pointer to the array containing VANC surfaces on which to perform the conversion. 
		unsigned long     in_ulNbInputVANCSurfaces,		// Indicates the number of VANC surfaces to be converted.
		SMvResolutionInfo&in_rsInputResolution,			// Indicates the input resolution.
		EMvCCFormat       in_eInputCCFormat,			// Indicates the format of the input closed captioning.
		IMvSurface*       io_apIOutputVANCSurfaces[],	// Pointer to the array containing VANC surfaces that have been converted.
		unsigned long     in_ulNbOutputVANCSurfaces,	// Indicates the number of VANC surfaces that have been converted.
		SMvResolutionInfo&in_rsOutputResolution,		// Indicates the output resolution.
		EMvCCFormat       in_eOutputCCFormat,			// Indicates the format of the output closed captioning.
		unsigned long     in_ulTargetLineFromStartOfSurface,	// Target line. This parameter is optional. Used to override the default 
																// target line specified by the closed caption format's specification.
		uint16_t          in_ui16SequenceIndex,			// Indicates the sequence index (if required).            
		unsigned long     in_ulIgnored					// Ignored.				
		) = 0;

   // Summary:
   // Returns the number of input and output surfaces needed for the desired conversion.
   // Remarks:
   // - The caller is informed if a sequence index is needed to process the conversion.
   // - An error will be returned if the conversion is not supported. 
   //
	virtual HRESULT __stdcall GetNbOfSurfacesNeededForClosedCaptioningConversion(
		SMvResolutionInfo&in_rsInputResolution,				// Indicates the input resolution.
		EMvCCFormat       in_eInputCCFormat,				// Indicates the format of the input closed captioning.
		unsigned long&    out_rulNbInputSurfacesNeeded,		// Indicates the number of input surfaces needed for the closed caption conversion.
		SMvResolutionInfo&in_rsOutputResolution,			// Indicates the output resolution.
		EMvCCFormat       in_eOutputCCFormat,				// Indicates the format of the output closed captioning.
		unsigned long&    out_rulNbOutputSurfacesNeeded,	// Indicates the number of output surfaces needed for the closed caption conversion.
		bool&             out_rbIsSequenceIndexNeeded,		// If true, a sequence index is required.          
		unsigned long     in_ulIgnored						// Ignored.
		) = 0;

   // Summary:
   // Converts digital to analog vertical interval time code (VITC) by inserting analog VITC bytes 
   // in a specific Vertical Blanking Intertval (VBI) line for SD resolutions (NTSC or PAL).
   // Remarks:
   // - This method can insert several time code values in different VBI lines.
   // - The digital VITC is a 64-bit value that is obtained from SMvIOExtraInfo.
   // - Inserting linear time code (LTC) values is not supported.
   //
   virtual HRESULT __stdcall InsertAnalogVITCIntoVBISurface(
      IMvSurface*          in_pISrcVBISurface,      // Input VANC buffer source. This parameter is optional. 
													// If provided, it is copied to the destination buffer prior to inserting the time code values.
      uint64_t             in_aui64Timecodes[],     // Array containing the time code values to insert.
      uint32_t             in_aui32LineNumbers[],   // Array containg the VBI line numbers corresponding to the time code values. The VBI line number 
	                                                // must be relative to each frame. For example, to insert a time code on line 14 in field one and on line 277,  
                                                    // which is the corresponding line in field two, only line 14 needs to be passed for each field. <p> <b>Note:</b> 
													// The caller must respect the SMPTE 12M-1 specification for restrictions on which lines to insert the time code signal. 
													// Otherwise, an error will be returned.
      uint32_t             in_ui32TimecodeCount,    // The amount of time code elements to insert. 
      IMvSurface*          out_pIDestVBISurface     // Pointer to the destination buffer.
      ) = 0;

   // Summary:
   // Converts VANC data with a PsF resolution to progressive, or vice-versa. 
   //Remarks:
   // The resolutions of the two surfaces must be the same, except for the scan mode (one is PsF and the other is progressive).
   // This method supports YUV 4:2:2 10-bit and Matrox ancillary data VANC formats.
   virtual HRESULT __stdcall ConvertVancSurfacesPtoPsf_or_PsftoP(
      IMvSurface*       in_pISrcVANCSurface,    // Pointer to the video surface containing the VANC data to convert.
      SMvResolutionInfo&in_rsInputResolution,   // Structure containing the input resolution of the VANC data.
      IMvSurface*       in_pIDestVANCSurface,   // Pointer to the video surface containing the converted VANC data. 
      SMvResolutionInfo&in_rsOutputResolution   // Structure containing the output resolution of the VANC data.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Main interface used to control the Flex Media Reader module.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvMediaReader : public IUnknown
{
	//
	// Summary:
	//    Opens the file for reading. 
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_FILE_ALREADY_OPENED, the current file must be closed.
	//    - MV_E_INVALID_POINTER, the in_pwchFileName parameter is NULL.
	//    - MV_E_FILEACCESS_OPENFILE_FAILED, an error occurred while trying to open the specified file.
	// Remarks:
	//    - This will open the file for reading, and prevent further external writing or delete access 
	//      on this file until CloseFile is called.
	//
	virtual HRESULT __stdcall OpenFile
		( 
		const wchar_t* in_pwchFileName // Name of the file to be played.
		) = 0;

	//
	// Summary:
	//    Sets optional reading properties.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_SUPPORTED, the specified property is not supported. The call has no effect.
	//    - MV_E_BUFFER_SIZE_MISMATCH, unexpected property size for the specified property.
	//    - MV_E_INVALID_POINTER, the in_pclsidPropertyID parameter is NULL.
	//    - MV_E_INVALID_POINTER, the out_pvProperty parameter is NULL.
	// Remarks:
	//    - A CLSID is used to uniquely identify the property type.
	//    - A buffer size mismatch error can happen if the user compiles with a different version of the property's
   //      prototype, or if the user
	//      sends an incorrect property type.
	//    - The property type must be known at compile time by both the caller application and the media reader module.
	//
	virtual HRESULT __stdcall SetProperty
		( 
		const CLSID*   in_pclsidPropertyID, // Unique identifier specifying the property to be set.
		LPVOID         in_pvProperty,       // Address of the property's value.
		const uint32_t in_ui32PropertySize  // Size in bytes of the property to set.
		) = 0;


	//
	// Summary:
	//    Gets optional reading properties.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_SUPPORTED, the specified property is not supported. The call has no effect.
	//    - MV_E_BUFFER_SIZE_MISMATCH, unexpected property size for the specified property.
	//    - MV_E_INVALID_POINTER, the in_pclsidPropertyID parameter is NULL.
	//    - MV_E_INVALID_POINTER, the out_pvProperty parameter is NULL.
	// Remarks:
	//    - A CLSID is used to uniquely identify the property type.
	//    - A buffer size mismatch error can happen if the user compiles with a different version of the property's
   //      prototype.
	//    - The property type must be known at compile time by both the caller application and the media reader module.
	//
	virtual HRESULT __stdcall GetProperty
		( 
		const CLSID*   in_pclsidPropertyID, // Unique identifier specifying the property to get.
		LPVOID         out_pvProperty,      // Address of the property's value.
		const uint32_t in_ui32PropertySize  // Size in bytes of the property to get.
		) = 0;


	//
	// Summary:
	//    Sets the video media frame range to read from the specified track inside the file.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_FILE_NOT_OPENED, the user must first successfully call OpenFile.
	//    - MV_E_OUT_OF_RANGE, the specified positions are outside the media's range.
	//    - MV_E_INVALID_TRACK, the specified track can't be accessed.
	// Remarks:
	//    - This method is frame-based. 
	//    - This method allows the caller to set a media range, in frames, to read from the disk. The user application
	//       can set the entire track range if desired.
	//    - The user application can obtain the media range by calling GetVideoTrackInfo
	//    - The media reader will optimize the file access based on all ganged SetVideo/AudioBuffers calls.
	//    - File I/O will be triggered by the next GetVideoBuffer.
	//    - This will reset the file I/O mechanism and cancel any pending GetVideoBuffer calls.
	//
	virtual HRESULT __stdcall SetVideoBuffers
		( 
		const uint32_t in_ui32VideoTrackID,             // Zero-based index of the track to read. Track indexes are
                                                      // obtained in GetVideoTrackCount.
		const uint64_t in_ui64ReadStartPosition,        // Position in frame to be read from the file.
		const uint64_t in_ui64ReadEndPositionInclusive  // Position of the last frame to be read from the file. This end
                                                      // position is inclusive.
		) = 0;


	//
	// Summary:
	//    Gets a video media frame from the specified track inside the file.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_FILE_NOT_OPENED, the user must first successfully call OpenFile.
	//    - MV_E_OUT_OF_RANGE, the current position is outside the SetVideoBuffers range (all frames have been read, or
   //      no SetVideoBuffers calls were done).
	//    - MV_E_INVALID_POINTER, the out_ppISurface parameter is NULL.
	//    - MV_E_INVALID_TRACK, the specified track can't be accessed.
	// Remarks:
	//    - This method is frame-based. If the content is interlaced, two fields will be interlaced in the surface.
	//    - This allows the user application to retrieve frame positions asked for by SetVideoBuffers one frame at a time.
	//    - Each new call to GetVideoBuffer increments the internal position. When the internal position overflows the 
   //      SetVideoBuffers positions, the media reader will return MV_E_OUT_OF_RANGE.
	//    - For temporal compression formats, the user may receive extra pre-roll surfaces prior to the requested data
   //      surfaces. The pre-roll surface is to help decoding subsequent positions. The pre-roll surface will have the
   //      frame position 0xFFFFFFFFFFFFFFFF. For examples, the pre-roll data for MPEG-2 data would be the previous GOP
   //      in case of opened gop encoding, or the last IDR in the case of H264. 
	//      The media reader will always return all frame positions needed for the caller to decompress the specified
   //      SetVideoBuffers range.
	//    - This method will trigger the file I/O read process as needed.
	//    - If a fatal error occurs while reading from the file, this method will return it as a synchronous error and 
	//      the execution will be stopped.
	//
	virtual HRESULT __stdcall GetVideoBuffer
		( 
		const uint32_t in_ui32VideoTrackID,    // Zero-based index of the track to read. Track indexes are obtained in 
                                             // GetVideoTrackCount.
		uint64_t*      out_pui64Position,      // Position in frames inside the file of out_ppISurface. This is not
                                             // always equal to the display position which can be accessed in IMvSurface.
		IMvSurface**   out_ppISurface          // The media data read from the disk. The media data is ready to be 
                                             // accessed. There's one surface per frame.
		) = 0;


	//
	// Summary:
	//    Sets the audio media samples range to read from the specified track inside the file.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_FILE_NOT_OPENED, the user must first successfully call OpenFile.
	//    - MV_E_OUT_OF_RANGE, the specified positions are outside the media's range.
	//    - MV_E_INVALID_TRACK, the specified track can't be accessed.
	//    - MV_E_INVALID_PARAMETER, the start position is greater than the end position.
	// Remarks:
	//    - This method is sample-based. 
	//    - This method allows the caller to set a media range, in audio samples, to read from the disk. The user
   //      application can set the entire track range if desired.
	//    - The user application can obtain the media range by calling GetAudioTrackInfo.
	//    - The media reader will optimize the file access based on all pending SetAudioBuffers calls.
	//    - File I/O will be triggered by the next GetAudioBuffer call.
	//    - This will reset the file I/O mechanism and cancel any pending GetAudioBuffer calls.
	//
	virtual HRESULT __stdcall SetAudioBuffers
		( 
		const uint32_t in_ui32AudioTrackID,                      // Zero-based index of the track to read. Track indexes
                                                               // are obtained in GetAudioTrackCount.
		const uint64_t in_ui64ReadStartPositionInSamples,        // Position in audio samples to be read from the file.
		const uint64_t in_ui64ReadEndPositionInSamplesInclusive  // Position of the last audio samples to be read from 
                                                               // the file. This end position is inclusive.
		) = 0;


	//
	// Summary:
	//    Gets an audio media sample range from the specified track inside the file.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_FILE_NOT_OPENED, the user must first successfully call OpenFile.
	//    - MV_E_OUT_OF_RANGE, the specified position or duration is outside the media's range.
	//    - MV_E_INVALID_POINTER, the out_ppIAudio parameter is NULL.
	//    - MV_E_INVALID_TRACK, the specified track can't be accessed.
	// Remarks:
	//    - The user application can obtain the media range by calling GetAudioTrackInfo.
	//    - The user specifies how many samples to retrieve from the media reader. 
	//    - The number of samples to retrieve should be limited to one second.
	//    - This method will trigger the file I/O read process as needed.
	//    - If a fatal error occurs while reading from the file this method will return it as a synchronous error and 
	//       the execution will be stopped.
	//
	virtual HRESULT __stdcall GetAudioBuffer
		( 
		const uint32_t    in_ui32AudioTrackID,          // Zero-based track index to read from the file. Track indexes
                                                      // are obtained in GetAudioTrackCount.
		const uint64_t    in_ui64SamplesCount,          // Duration in audio samples of the audio media to read.
		uint64_t*         out_pui64SamplesCountRead,    // Duration in audio samples of the audio media returned in
                                                      // out_ppIAudio. May differ from in_ui64SamplesCount.
		uint64_t*         out_pui64SamplesPosition,     // Position in samples of out_ppIAudio inside the file. The 
                                                      // position is also available in IMvAudioSamples.
		IMvAudioSamples** out_ppIAudio                  // The media data read from the disk. The media data is ready to
                                                      // be accessed right away.
		) = 0;


	//
	// Summary:
	//    Closes the file reading module.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	// Remarks:
	//    - This will close the file.
	//    - Once a file is closed no further operations can be made on the media reader
	//       until a new file is opened. 
	//    - If the user still holds one or more buffers the CloseFile call will wait indefinitely for them to be returned.
	//       This mechanism is used to make sure all memory is accounted for between reading of different
	//       files.
	//
	virtual HRESULT __stdcall CloseFile() = 0;


	//
	// Summary:
	//    Returns the number of video tracks available to read in the file.
	// Return value:
	//    - uint32_t, the number of video tracks found.
	// Remarks:
	//    - The media reader only reports video tracks that it's able to read.
	//    - It returns a zero-based index that can then be used in the GetVideoBuffer and GetVideoTrackInfo commands.
	//       The first video track is at index 0.
	//
	virtual uint32_t __stdcall GetVideoTrackCount() = 0;


	//
	// Summary:
	//    Returns the number of audio tracks available to read in the file.
	// Return value:
	//    - uint32_t, the number of audio tracks found.
	// Remarks:
	//    - The media reader only reports audio tracks that it's able to read.
	//    - It returns a zero-based index that can then be used in the GetAudioBuffer and GetAudioTrackInfo commands.
	//       The first audio track is at index 0. If there's one video track and one audio track inside the file then
	//       there will be a video track 0 and an audio track 0.
	//
	virtual uint32_t __stdcall GetAudioTrackCount() = 0;


	//
	// Summary:
	//    Returns the information associated with the specified video track if available.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_FILE_NOT_OPENED, the user must first successfully call OpenFile.
	//    - MV_E_INVALID_POINTER, the out_psTrackInfo parameter is NULL.
	//    - MV_E_INVALID_TRACK, the specified track can't be accessed.
	// Remarks:
	//    - This is used by the application to extract information specific to each individual
	//       track present in the file.
	//
	virtual HRESULT __stdcall GetVideoTrackInfo
		( 
		const uint32_t          in_ui32VideoTrackID,    // Zero-based track index to read from the file. Track indexes
                                                      // are obtained in GetVideoTrackCount.
		SMvMediaClipTrackInfo*  out_psTrackInfo         // Track information structure.
		) = 0;


	//
	// Summary:
	//    Returns the information associated with the specified audio track if available.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_FILE_NOT_OPENED, the user must first successfully call OpenFile.
	//    - MV_E_INVALID_POINTER, the out_psTrackInfo parameter is NULL.
	//    - MV_E_INVALID_TRACK, the specified track can't be accessed.
	// Remarks:
	//    - This is used by the application to extract information specific to each individual
	//       track present in the file.
	//
	virtual HRESULT __stdcall GetAudioTrackInfo
		( 
		const uint32_t          in_ui32AudioTrackID, // Zero-based track index to read from the file. Track indexes 
                                                   // are obtained in GetAudioTrackCount.
		SMvMediaClipTrackInfo*  out_psTrackInfo      // Track information structure.
		) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Main interface used to control the Flex Media Writer module.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvMediaWriter : public IUnknown
{
	//
	// Summary:
	//    Opens the file for writing, and prepares the media writer module resources based on the information provided
   //    in parameters.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_WRONG_STATE, the current file must be closed first.
	//    - MV_E_INVALID_POINTER, the in_pwchFileName parameter is NULL.
	//    - MV_E_FILEACCESS_OPENFILE_FAILED, an error occurred while trying to open the specified file.
	// Remarks:
	//    - This will open the file for writing, and prevent further external writing or delete access 
	//       on this file until CloseFile is called.
	//
	virtual HRESULT __stdcall OpenFile
		( 
		const wchar_t* in_pwchFileName,        // Name of the file to be played.
		const uint32_t in_ui32VideoTrackCount, // Number of video tracks to capture.
		const uint32_t in_ui32AudioTrackCount  // Number of audio tracks to capture.
		) = 0;


	//
	// Summary:
	//    Sets the information associated with the specified video track.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_WRONG_STATE, the user must first successfully call OpenFile. The user must not have started retrieving
   //      buffers.
	//    - MV_E_INVALID_POINTER, the in_psTrackInfo parameter is NULL.
	//    - MV_E_INVALID_TRACK, the specified track can't be accessed.
	// Remarks:
	//    - This is used by the application to program information specific to each individual
	//       track present in the file.
	//    - The track indexes are zero-based per media type. Video track IDs are 0 to n, Audio track IDs are also 0 to n.
	//    - SetAudio/VideoTrackInfo essentially "adds" a track in the file. 
	//
	virtual HRESULT __stdcall SetVideoTrackInfo
		( 
		const uint32_t          in_ui32VideoTrackID, // Zero-based track index to write to the file.
		SMvMediaClipTrackInfo*  in_psTrackInfo       // Track information structure.
		) = 0;


	//
	// Summary:
	//    Sets the information associated with the specified audio track.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_WRONG_STATE, the user must first successfully call OpenFile. The user must not have started retrieving
   //      buffers.
	//    - MV_E_INVALID_POINTER, the in_psTrackInfo parameter is NULL.
	//    - MV_E_INVALID_TRACK, the specified track can't be accessed.
	// Remarks:
	//    - This is used by the application to extract information specific to each individual
	//       track present in the file.
	//    - The track indexes are zero-based per media type. Video track IDs are 0 to n, Audio track IDs are also 0 to n.
	//    - SetAudio/VideoTrackInfo essentially "adds" a track in the file. 
	//
	virtual HRESULT __stdcall SetAudioTrackInfo
		( 
		const uint32_t          in_ui32AudioTrackID, // Zero-based track index to write to the file. 
		SMvMediaClipTrackInfo*  in_psTrackInfo       // Track information structure.
		) = 0;


	//
	// Summary:
	//    Returns the information associated with the specified video track if available.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_FILE_NOT_OPENED, the user must first successfully call OpenFile.
	//    - MV_E_INVALID_POINTER, the out_psTrackInfo parameter is NULL.
	//    - MV_E_INVALID_TRACK, the specified track can't be accessed.
	// Remarks:
	//    - This method allows the caller to retrieve parameters it previously set in SetVideoTrackInfo.
	//    - This is used by the application to extract information specific to each individual
	//       track present in the file.
	//
	virtual HRESULT __stdcall GetVideoTrackInfo
		( 
		const uint32_t          in_ui32VideoTrackID, // Zero-based track index to write to the file.
		SMvMediaClipTrackInfo*  out_psTrackInfo      // Track information structure.
		) = 0;


	//
	// Summary:
	//    Returns the information associated with the specified audio track if available.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_FILE_NOT_OPENED, the user must first successfully call OpenFile.
	//    - MV_E_INVALID_POINTER, the out_psTrackInfo parameter is NULL.
	//    - MV_E_INVALID_TRACK, the specified track can't be accessed.
	// Remarks:
	//    - This method allows the caller to retrieve parameters it previously set in SetAudioTrackInfo.
	//    - This is used by the application to extract information specific to each individual
	//       track present in the file.
	//
	virtual HRESULT __stdcall GetAudioTrackInfo
		( 
		const uint32_t          in_ui32AudioTrackID, // Zero-based track index to write to the file.
		SMvMediaClipTrackInfo*  out_psTrackInfo      // Track information structure.
		) = 0;


	//
	// Summary:
	//    Sets optional writing properties.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_WRONG_STATE, the user must first successfully call OpenFile and must not have started retrieving
   //      buffers through GetAudio/VideoBuffer.
	//    - MV_E_NOT_SUPPORTED, the specified property is not supported. The call has no effect. This is not a fatal error.
	//    - MV_E_BUFFER_SIZE_MISMATCH, unexpected property size for the specified property.
	//    - MV_E_INVALID_POINTER, the in_pclsidPropertyID parameter is NULL.
	//    - MV_E_INVALID_POINTER, the out_pvProperty parameter is NULL.
	// Remarks:
	//    - A CLSID is used to uniquely identify the property type.
	//    - A buffer size mismatch error can happen if the user compiles with a different version of the property's 
   //      prototype, or if the user sends an incorrect property type.
	//    - The property type must be known at compile time by both the caller application and the media writer module.
	//
	virtual HRESULT __stdcall SetProperty
		( 
		const CLSID*   in_pclsidPropertyID, // Unique identifier specifying the property to be set.
		LPVOID         in_pvProperty,       // Address of the property's value.
		const uint32_t in_ui32PropertySize  // Size in bytes of the property to set.
		) = 0;


	//
	// Summary:
	//    Gets optional writing properties.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_NOT_SUPPORTED, the specified property is not supported. The call has no effect.
	//    - MV_E_BUFFER_SIZE_MISMATCH, unexpected property size for the specified property.
	//    - MV_E_INVALID_POINTER, the in_pclsidPropertyID parameter is NULL.
	//    - MV_E_INVALID_POINTER, the out_pvProperty parameter is NULL.
	//    - MV_E_NOT_INITIALIZED, the requested property has not been set yet. The caller must first set the property
   //      before retrieving it.
	// Remarks:
	//    - This is used in conjunction with the SetProperty method. It allows the user to retrieve properties it
   //      already set. 
	//    - A CLSID is used to uniquely identify the property type.
	//    - A buffer size mismatch error can happen if the user compiles with a different version of the property's
   //      prototype, or if the user sends an incorrect property type.
	//    - The property type must be known at compile time by both the caller application and the media writer module.
	//
	virtual HRESULT __stdcall GetProperty
		( 
		const CLSID*   in_pclsidPropertyID, // Unique identifier specifying the property to get.
		LPVOID         out_pvProperty,      // Address of the property's value.
		const uint32_t in_ui32PropertySize  // Size in bytes of the property to get.
		) = 0;


	//
	// Summary:
	//    Gets a video media frame buffer to be stored inside the file's specified track.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_WRONG_STATE, the user must first successfully call OpenFile.
	//    - MV_E_INVALID_POINTER, the out_ppIVideo parameter is NULL.
	//    - MV_E_INVALID_TRACK, the specified track can't be accessed.
	//    - MV_E_DESTINATION_BUFFER_TOO_SMALL, the requested buffer size is larger than the max buffer size that was 
   //      specified in OpenFile.
	//    - MV_E_MISSING_TRACK_INFOS, not all track infos have been received.
	// Remarks:
	//    - If a fatal error occurs while writing to the file this method will return it as a synchronous error and 
	//       the execution will be stopped.
	//
	virtual HRESULT __stdcall GetVideoBuffer
		(
		const uint32_t in_ui32VideoTrackID,             // Zero-based index of the track to write to. Track indexes are
                                                      // set in SetVideoTrackInfo.
		const uint32_t in_ui32VideoBufferSizeInBytes,   // Size in bytes of the requested buffer.
		uint64_t*      out_pui64FrameStreamPosition,    // Stream position inside the file of the returned buffer. This
                                                      // is a stream position not always equal to the display position.
                                                      // The position is also present in IMvSurface::GetMediaDescription.
		IMvSurface**   out_ppIVideo                     // The media data to be written to disk. There's one surface per
                                                      // frame.
		) = 0;


	//
	// Summary:
	//    Gets an audio media sample range to write to the file.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_WRONG_STATE, the user must first successfully call OpenFile.
	//    - MV_E_INVALID_POINTER, the out_ppIAudio parameter is NULL.
	//    - MV_E_INVALID_TRACK, the specified track can't be accessed.
	//    - MV_E_DESTINATION_BUFFER_TOO_SMALL, the requested buffer size is larger than the max buffer size that was
   //      specified in OpenFile.
	// Remarks:
	//    - The user application can decide to write an arbitrary number of audio samples on each GetAudioBuffer call. It
	//       doesn't need to keep a specific audio sequence on a frame-by-frame basis.
	//    - The user application should accumulate the audio samples in half-second packets.
	//    - As a good practice the total audio sample count written to the track should match the associated video
   //      track's duration, in frames, if any. The user application can use the Matrox audio time conversion routines
   //      to ensure that the total sample count matches the video duration.
	//    - The media writer will buffer the media data internally and write it to the file I/O in blocks large enough
   //      to satisfy the optimal file access transfer size in bytes property as specified by the user application.
	//    - The user application needs to know the buffer size before requesting a buffer from the media writer.
	//    - If a fatal error occurs while writing to the file, this method will return it as a synchronous error and 
	//       the execution will be stopped.
	//
	virtual HRESULT __stdcall GetAudioBuffer
		( 
		const uint32_t    in_ui32AudioTrackID,                   // Zero-based track index to written to the file. Track
                                                               // indexes are set in SetAudioTrackInfo.
		const uint32_t    in_ui32AudioBufferSizeInBytes,         // Size of the requested buffer.
		uint64_t*         out_pui64AudioSamplesStreamPosition,   // Stream position inside the file of the returned
                                                               // buffer. This is a position in audio samples. The 
                                                               // position is also present in IMvAudioSamples.
		IMvAudioSamples** out_ppIAudio                           // The media data to be written the disk. 
		) = 0;


	//
	// Summary:
	//    Closes the file writing module.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_WRONG_STATE, the file must be opened.
	// Remarks:
	//    - This will close the file.
	//    - Once a file is closed no further operations can be performed on the media writer
	//       until a new file is created. 
	//    - This will wait for all file I/O to be completed before returning. Once the CloseFile returns, the file can 
	//       be accessed in read or write by the user application.
	//
	virtual HRESULT __stdcall CloseFile() = 0;
};

///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Controls the Matrox MPEG-2 Transport Stream Muxer notification. 
// Remarks:
//    - This interface will be notified each time an MPEG-2 transport stream surface is filled and ready to be played back.
//
///////////////////////////////////////////////////////////////////////////////
interface IMvMPEG2TSMuxerNotification : public IUnknown
{
	//
	// Summary:
	//    Provides the duration of an MPEG-2 transport stream surface once the Matrox MPEG-2 Transport Stream Muxer has
   //    finished with the output buffer.
	// Return value:
	//    MV_NOERROR.
	//
	virtual HRESULT __stdcall NotifySurfaceDuration
		(
		IMvSurface * in_pIMPEG2TSSurface,         // Pointer to the IMvSurface interface that contains the transport stream data.
		uint64_t     in_ui64DurationInNanoTime    // Duration (in nanotime) of the surface specified by in_pIMPEG2TSSurface.
		) = 0;
};

///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Controls the Matrox MPEG-2 Transport Stream Muxer.
//
///////////////////////////////////////////////////////////////////////////////
interface IMvMPEG2TSMuxer : public IUnknown
{	
	//
	// Summary:
	//    Opens the muxer with settings.	
	// Return value:
	//    - Returns an error if the command failed or there are invalid parameters.
	virtual HRESULT __stdcall Open
		(
		SMvMPEG2TSMuxerSettings		in_sMPEG2TSMuxerSettings,       // Describes the Matrox MPEG-2 Transport Stream Muxer
        IMvMPEG2TSMuxerNotification *in_pIMPEG2TSMuxerNotification  // Pointer to the IMvMPEG2TSMuxerNotification interface 
                                                                    // that will be notified each time an MPEG-2 transport
                                                                    // stream surface is filled and ready to be played back.
		) = 0;

	//
	// Summary:
	//    Closes the muxer.
	// Return value:
	//    - Returns an error if the command failed or there are invalid parameters.
	virtual HRESULT __stdcall Close() = 0;

	//
	// Summary:
	//    Provides a video surface containing video essence to the muxer.	
	// Return value:
	//    - Returns an error if the command failed or there are invalid parameters.
	virtual HRESULT __stdcall PutSurface
		(
		IMvSurface* in_pIVideoSurface // Pointer to the IMvSurface interface that contains the video surface.
		) = 0;

	//
	// Summary:
	//    Provides audio samples containing audio essence to the muxer.	
	// Return value:
	//    - Returns an error if the command failed or there are invalid parameters.
	virtual HRESULT __stdcall PutAudioSamples
		(
		IMvAudioSamples* in_pIAudioSamples  // Pointer to the audio samples interface.
		) = 0;

   //
   // Summary:
   //    Provides a VANC surface to the muxer.
   // Return value:
   //    - Returns an error if the command failed or there are invalid parameters.
   virtual HRESULT __stdcall PutVancSurface
      (
      IMvSurface* in_pIVancSurface  // Pointer to the IMvSurface interface containing VANC data.
      ) = 0;

	//
	// Summary:
	//    Signals the end of the video stream.	
	// Return value:
	//    - Returns an error if the command failed or there are invalid parameters.
	virtual HRESULT __stdcall PutEOSVideo()=0;

	//
	// Summary:
	//    Signals the end of the audio stream.	
	// Return value:
	//    - Returns an error if the command failed or there are invalid parameters.
	virtual HRESULT __stdcall PutEOSAudio()=0;

   //
   // Summary:
   //    Signals the end of the VANC stream. 
   // Return value:
   //    - Returns an error if the command failed or there are invalid parameters.
   // Remarks:
   //    - The end of the VANC stream is directly related to the end of the video stream.
   virtual HRESULT __stdcall PutEOSVanc() = 0;

	//
	// Summary:
	//    Provides empty MPEG-2 transport stream packets that will be filled by the muxer.
	// Return value:
	//    - Returns an error if the command failed or there are invalid parameters.
	virtual HRESULT __stdcall GetMuxedSurface
		(
		IMvSurface* in_pIMPEG2TSSurface  // Pointer to the IMvSurface interface that contains the MPEG-2 transport stream surface.
		) = 0;

};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Main interface used to control the Flex Transport Stream Encoder module.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvTSEncoder : public IUnknown
{
	//
	// Summary:
	//    Prepares the Flex Transport Stream Encoder module's resources based on the information provided in parameters.
	// Return value:
	//    - Returns an error if the command failed or there are invalid parameters.
	//
	virtual HRESULT __stdcall Open
		(	
		EMvCodecOption					       in_eVideoCodecOption,           // Indicates the video codec option.
		MVCHANDLE						       in_pmvchVideoOptionSettings,    // Pointer to the video option setting.
		EMvCodecOption					       in_eAudioCodecOption,           // Indicates the audio codec option.
		MVCHANDLE						       in_pmvchAudioOptionSettings,    // Pointer to the audio option setting.
		bool							          in_bIsVBIPresent,               // If true, VBI data is present.
		SMvTSEncoderMuxerOptionSettings * in_pIMvTSEncoderOptionSettings, // Pointer to the Matrox MPEG-2 Transport Stream Muxer option settings structure.
		IMvMPEG2TSMuxerNotification	  * in_pIMvMPEG2TSMuxerNotification // Pointer to the Matrox MPEG-2 Transport Stream Muxer notification interface. 
		) = 0;

	//
	// Summary:
	//    Provides an uncompressed video surface for the codec to compress.
	// Return value:
	//    - Returns an error if the command failed or there are invalid parameters.
	//
	virtual HRESULT __stdcall PutUncompressedVideoSurface
		( 
		IMvSurface * io_pSurfaceIn  // Pointer to the IMvSurface interface that contains the video surface. <p> The video surface can be field-based or frame-based.
		) = 0;

	//
	// Summary:
	//    Provides an uncompressed VBI surface for the codec to compress.
	// Return value:
	//    - Returns an error if the command failed or there are invalid parameters.
	//
	virtual HRESULT __stdcall PutUncompressedVBISurface
		( 
		IMvSurface * io_pSurfaceIn  // Pointer to the IMvSurface interface that contains the VBI surface. <p> The VBI surface can be field-based or frame-based.
		) = 0;

	//
	// Summary:
	//    Provides uncompressed audio samples for the codec to compress.
	// Return value:
	//    - Returns an error if the command failed or there are invalid parameters.
	//
	virtual HRESULT __stdcall PutUncompressedAudioSamples
		( 
		IMvAudioSamples * io_pAudioSamplesIn // Pointer to the audio samples interface. <p> Audio samples can be field-based or frame-based.
		) = 0;

	//
	// Summary:
	//    Requests the next set of transport stream muxed surfaces from the muxer.
	// Return value:
	//    - Returns an error if the command failed or there are invalid parameters.
	virtual HRESULT __stdcall GetTSMuxedSurface
		( 
		IMvSurface * io_pTSMuxedSurfaceOut     // Pointer to the IMvSurface interface that contains the transport stream muxed surfaces.
		) = 0;

	//
	// Summary:
	//    Informs the Flex Transport Stream Encoder that all video data for a given stream has been sent.
	// Return value:
	//    - Returns an error if the command failed.
   //    - MV_E_PROCESSING_JOB_NOT_COMPLETED, if the last <b> <i> Put() </i> </b> has a polarity of keMvPolarityFirstField.
   // Remarks:
	//    - This method must be called after all video <b> <i> Put() </i> </b> operations for a given stream have been performed. 
	//
	virtual HRESULT __stdcall EndOfStreamVideo( ) = 0;

	//
	// Summary:
	//    Informs the Flex Transport Stream Encoder that all VBI data for a given stream has been sent.
	// Return value:
	//    - Returns an error if the command failed.
   //    - MV_E_PROCESSING_JOB_NOT_COMPLETED, if the last <b> <i> Put() </i> </b> has a polarity of keMvPolarityFirstField.
   // Remarks:
	//    - This method must be called after all VBI <b> <i> Put() </i> </b> operations for a given stream have been performed. 
   //
	virtual HRESULT __stdcall EndOfStreamVBI( ) = 0;

	//
	// Summary:
	//    Informs the Flex Transport Stream Encoder that all audio data for a given stream has been sent.
	// Return value:
	//    - Returns an error if the command failed.
   //    - MV_E_PROCESSING_JOB_NOT_COMPLETED, if the last <b> <i> Put() </i> </b> has a polarity of keMvPolarityFirstField.
	// Remarks:
   //    - This method must be called after all audio <b> <i> Put() </i> </b> operations for a given stream have been performed.
   //    
	virtual HRESULT __stdcall EndOfStreamAudio( ) = 0;

	//
	// Summary:
	//    Informs the Flex Transport Stream Encoder that compression commands have finished queuing.
	// Return value:
	//    - Returns MV_NOERROR, if completed successfully.
   //
	virtual HRESULT __stdcall Close() = 0;

   //
   // Summary:
   //    Extends the IMvTSEncoder::Open() method by defining the encoding options for the Matrox MPEG-2 Transport Stream.
   // Return value:
   //    - Returns an error if the command failed or there are invalid parameters.
   //
   virtual HRESULT __stdcall OpenEx
      (
      SMvTSEncoderOptions              *in_psTSEncoderOptions,             // Pointer to the transport stream encoder options structure.
      SMvTSEncoderMuxerOptionSettings  *in_psTSEncoderOptionSettings,      // Pointer to the muxer option settings structure required by the Flex Transport Stream Encoder.
      IMvMPEG2TSMuxerNotification      *in_pIMvMPEG2TSMuxerNotification    // Pointer to the MPEG-2 Transport Stream Muxer notification interface.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides the callback notification of the video connector. 
//    This interface passes notification information to the object implementing it.
// Remarks:
//    - Use the IMvVideoConnectorNotification interface to register and unregister the
//      IMvVideoConnectorNotificationCallback interface.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvVideoConnectorNotificationCallback : public IUnknown
{
   //
   // Summary:
   //    Receives the new video connector status.
   // Return value:
   //    - MV_NOERROR. 
   //
   virtual HRESULT __stdcall Notify
      (
      EMvVideoConnectorLabel in_eVideoConnectorLabel, // Indicates which video connector label status has changed.
      SMvVideoConnectorStatus& in_rsVideoConnectorStatus    // Structure of the new video connector status.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides the callback notification of the AES/EBU audio pair connectors. 
//    This interface passes notification information to the object implementing it.
// Remarks:
//    - Use the IMvAesEbuAudioConnectorsNotification interface to register and unregister the
//      IMvAesEbuAudioConnectorsNotificationCallback interface.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvAesEbuAudioConnectorsNotificationCallback : public IUnknown
{
   //
   // Summary:
   //    Receives the new AES/EBU connector status.
   // Return value:
   //    - MV_NOERROR. 
   //
   virtual HRESULT __stdcall Notify
      (
      SMvAudioPairStatus& in_rsAesEbuPairStatus // Structure of the new AES/EBU audio pair connector status.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides the callback notification of the embedded SDI audio connector. 
//    This interface passes notification information to the object implementing it.
// Remarks:
//    - Use the IMvSdiEmbeddedAudioConnectorNotification interface to register and unregister the
//      IMvSdiEmbeddedAudioConnectorNotificationCallback interface.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSdiEmbeddedAudioConnectorNotificationCallback : public IUnknown
{
   //
   // Summary:
   //    Receives the new embedded SDI audio connector status.
   // Return value:
   //    - MV_NOERROR. 
   //
   virtual HRESULT __stdcall Notify
      (
      EMvVideoConnectorLabel in_eSdiConnectorLabel,   // Video connector label of the embedded SDI audio connector
                                                      // that has changed status.
      SMvAudioPairStatus in_asEmbeddedPairStatus[],   // Pointer to the array of structures of embedded SDI audio
                                                      // connector pairs whose status has changed.
      uint32_t in_ui32NbOfAudioPairs                  // Number of embedded SDI audio connector pairs in the preceding
                                                      // array.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides the callback notification of the genlock. 
//    This interface passes notification information to the object implementing it.
// Remarks:
//    - Use the IMvGenlockNotification interface to register and unregister the
//      IMvGenlockNotificationCallback interface.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvGenlockNotificationCallback : public IUnknown
{
   //
   // Summary:
   //    Receives the new genlock status.
   // Return value:
   //    - MV_NOERROR. 
   //
   virtual HRESULT __stdcall Notify
      (
      SMvGenlockInputStatus& in_rsGenlockStatus   // Structure of the new genlock status.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides the callback notification for asynchronous errors related to card streams. 
//    This interface passes asynchronous errors to the object implementing it.
// Remarks:
//    - Use the IMvErrorNotification interface to register and unregister the
//      IMvErrorNotificationCallback interface.
// Note:
//    - Card streams refer to any stream that interacts with a card node and uses hardware processing.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvErrorNotificationCallback : public IUnknown
{
   //
   // Summary:
   //    Receives the new asynchronous error.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Notify
      (
         HRESULT in_hrError  // Indicates the asynchronous error code.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides the callback notification of the SfpIp. 
//    This interface passes notification information to the object implementing it.
// Remarks:
//    - Use the IMvSfpIp interface to register and unregister the
//      IMvSfpIpNotificationCallback interface.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSfpIpNotificationCallback : public IUnknown
{
   //
   // Summary:
   //    Receives the new SfpIp status.
   // Return value:
   //    - MV_NOERROR. 
   //
   virtual HRESULT __stdcall Notify
      (
      IMvSfpIp * in_pISfpIp,              // Pointer to the SfpIp interface.
      const SMvSfpIpStatus & in_krsStatus // Structure of the new SfpIp status.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides the callback notification for asynchronous events (for topology-based hardware only). 
//    This interface passes notification information to the object implementing it.
// Remarks:
//    - Use the IMvEventNotification interface to register and unregister the
//      IMvEventNotificationCallback interface.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvEventNotificationCallback : public IUnknown
{
   //
   // Summary:
   //    Receives the new asynchronous event.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Notify
      (
      const SMvEventReportInfo& in_krsEventInfo  // Structure describing the asynchronous event.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides the callback notification of the temperature sensors if a temperature sensor on the card overheats. 
//    This interface passes notification information to the object implementing it.
// Remarks:
//    - Use the IMvTemperatureNotification interface to register and unregister the
//      IMvTemperatureNotificationCallback interface.
// Note:
//    - Also used to provide the callback notification when the fan on the card malfunctions (for X.mio3 and some DSX LE4 models).
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvTemperatureNotificationCallback : public IUnknown
{
   //
   // Summary:
   //    Notifies that a temperaure sensor on the card is overheating.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Notify
      (
      const SMvTemperatureInformation* in_psSensorsInformation,   // Pointer to an array of structures containing
                                                                  // temperature sensor information. Each structure 
                                                                  // contains information for one of the temperature 
                                                                  // sensors on the card.
      uint32_t in_ui32SensorCount                                 // Number of temperature sensors in the array.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Base interface for all notification interfaces. Used to get the related notification event.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvNotification : public IUnknown
{
   //
   // Summary:
   //    Gets the source notification event for the corresponding child class notification object.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall GetNotificationEvent
	   (
	   HANDLE& out_rhNotificationEvent	// Receives the notification event of the notification object.
	   ) = 0;

   //
   // Summary:
   //    Release the notification event for the corresponding child class notification object.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall ReleaseNotificationEvent
      (
        HANDLE in_hNotificationEvent	// Specifies the notification event of the notification object.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Registers and unregisters the IMvVideoConnectorNotificationCallback interface for the video connector.
// Remarks:
//    - The application creates an object that implements the IMvVideoConnectorNotificationCallback interface
//		that will be passed to the RegisterCallbackForNotification and UnregisterCallbackForNotification methods.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvVideoConnectorNotification : public IMvNotification
{
   //
   // Summary:
   //    Registers a callback notification for the video connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::AddRef method of the in_pIVideoConnectorNotificationCallback parameter is called when the
   //      notification is registered to prevent the object implementing the IMvVideoConnectorNotificationCallback 
   //      interface from being destroyed.
   //
   virtual HRESULT __stdcall RegisterCallbackForNotification
      (
      IMvVideoConnectorNotificationCallback* in_pIVideoConnectorNotificationCallback  // Pointer to the video connector
                                                                                       // notification callback interface.
      ) = 0;

   //
   // Summary:
   //    Unregisters a callback notification for the video connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::Release method of the in_pIVideoConnectorNotificationCallback parameter is called when the
   //      notification is unregistered to remove the reference count added by 
   //      IMvVideoConnectorNotification::RegisterCallbackForNotification.
   //
   virtual HRESULT __stdcall UnregisterCallbackForNotification
      (
      IMvVideoConnectorNotificationCallback* in_pIVideoConnectorNotificationCallback  // Pointer to the video connector
                                                                                      // notification callback interface.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Registers and unregisters the IMvAesEbuAudioConnectorsNotificationCallback interface
//    for the AES/EBU audio pair connectors.
// Remarks:
//    - The application creates an object that implements the IMvAesEbuAudioConnectorsNotificationCallback interface
//		that will be passed to the RegisterCallbackForNotification and UnregisterCallbackForNotification methods.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvAesEbuAudioConnectorsNotification : public IMvNotification
{
   //
   // Summary:
   //    Registers a callback notification for the AES/EBU audio pair connectors.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::AddRef method of the in_pIAesEbuAudioConnectorsNotificationCallback parameter is called when
   //      the notification is registered to prevent the object implementing the 
   //      IMvAesEbuAudioConnectorsNotificationCallback interface from being destroyed.
   //
   virtual HRESULT __stdcall RegisterCallbackForNotification
      (
      IMvAesEbuAudioConnectorsNotificationCallback* in_pINotificationCallback // Pointer to the AES/EBU audio connectors 
                                                                              // notification callback interface.
      ) = 0;

   //
   // Summary:
   //    Unregisters a callback notification for the AES/EBU audio pair connectors.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::Release method of the in_pIAesEbuAudioConnectorsNotificationCallback parameter is called when
   //      the notification is unregistered to remove the reference count added by
   //      IMvAesEbuAudioConnectorsNotification::RegisterCallbackForNotification.
   //
   virtual HRESULT __stdcall UnregisterCallbackForNotification
      (
      IMvAesEbuAudioConnectorsNotificationCallback* in_pINotificationCallback // Pointer to the AES/EBU audio connectors
                                                                              // notification callback interface.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Registers and unregisters the IMvSdiEmbeddedAudioConnectorNotificationCallback  
//    interface for the embedded SDI audio connector.
// Remarks:
//    - The application creates an object that implements the IMvSdiEmbeddedAudioConnectorNotificationCallback interface
//		that will be passed to the RegisterCallbackForNotification and UnregisterCallbackForNotification methods.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSdiEmbeddedAudioConnectorNotification : public IMvNotification
{
   //
   // Summary:
   //    Registers a callback notification for the embedded SDI audio connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - The IUnknown::AddRef method of the in_pISdiEmbeddedAudioConnectorNotificationCallback parameter is called
   //      when the notification is registered to prevent the object implementing the
   //      IMvSdiEmbeddedAudioConnectorNotificationCallback interface from being destroyed.
   //
   virtual HRESULT __stdcall RegisterCallbackForNotification
      (
      IMvSdiEmbeddedAudioConnectorNotificationCallback* in_pINotificationCallback // Pointer to the embedded SDI audio 
                                                                                 // connector notification callback
                                                                                 // interface.
      ) = 0;

   //
   // Summary:
   //    Unregisters a callback notification for the embedded SDI audio connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::Release method of the in_pISdiEmbeddedAudioConnectorNotificationCallback parameter is called 
   //      when the notification is unregistered to remove the reference count added by
   //      IMvSdiEmbeddedAudioConnectorNotification::RegisterCallbackForNotification.
   //
   virtual HRESULT __stdcall UnregisterCallbackForNotification
      (
      IMvSdiEmbeddedAudioConnectorNotificationCallback* in_pINotificationCallback // Pointer to the embedded SDI audio
                                                                                  // connector notification callback
                                                                                  // interface.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Registers and unregisters the IMvGenlockNotificationCallback interface for the card's genlock. 
// Remarks:
//    - The application creates an object that implements the IMvGenlockNotificationCallback interface
//		that will be passed to the RegisterCallbackForNotification and UnregisterCallbackForNotification methods.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvGenlockNotification : public IMvNotification
{
   //
   // Summary:
   //    Registers a callback notification for the card's genlock.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::AddRef method of the in_pIGenlockNotificationCallback parameter is called when the
   //      notification is registered to prevent the object implementing the IMvGenlockNotificationCallback
   //      interface from being destroyed.
   //
   virtual HRESULT __stdcall RegisterCallbackForNotification
      (
      IMvGenlockNotificationCallback* in_pIGenlockNotificationCallback  // Pointer to the genlock notification callback
                                                                        // interface.
      ) = 0;

   //
   // Summary:
   //    Unregisters a callback notification for the card's genlock.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::Release method of the in_pIGenlockNotificationCallback parameter is called when the
   //      notification is unregistered to remove the reference count added by
   //      IMvGenlockNotification::RegisterCallbackForNotification.
   //
   virtual HRESULT __stdcall UnregisterCallbackForNotification
      (
      IMvGenlockNotificationCallback* in_pIGenlockNotificationCallback  // Pointer to the genlock notification callback
                                                                        // interface.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Registers and unregisters the IMvErrorNotificationCallback interface for asynchronous errors related to card streams. 
// Remarks:
//    - The application creates an object that implements the IMvErrorNotificationCallback interface
//		that will be passed to the RegisterCallbackForNotification and UnregisterCallbackForNotification methods.
// Note:
//    - Card streams refer to any stream that interacts with a card node and uses hardware processing.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvErrorNotification : public IUnknown
{
   //
   // Summary:
   //    Registers a callback notification for an asynchronous error.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::AddRef method of the in_pIErrorNotificationCallback parameter is called when the notification
   //      is registered to prevent the object implementing the IMvErrorNotificationCallback interface from being
   //      destroyed.
   //
   virtual HRESULT __stdcall RegisterCallbackForNotification
      (
      IMvErrorNotificationCallback* in_pIErrorNotificationCallback   // Pointer to the error notification callback
                                                                     // interface.
      ) = 0;

   //
   // Summary:
   //    Unregisters a callback notification for an asynchronous error.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - The IUnknown::Release method of the in_pIErrorNotificationCallback parameter is called when the notification
   //      is unregistered to remove the reference count added by 
   //      IMvErrorNotification::RegisterCallbackForNotification.
   //
   virtual HRESULT __stdcall UnregisterCallbackForNotification
      (
      IMvErrorNotificationCallback* in_pIErrorNotificationCallback   // Pointer to the error notification callback
                                                                     // interface.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Registers and unregisters the IMvEventNotificationCallback interface for asynchronous events (for topology-based
//    hardware only). 
// Remarks:
//    - The application creates an object that implements the IMvEventNotificationCallback interface
//		that will be passed to the RegisterCallbackForNotification and UnregisterCallbackForNotification methods.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvEventNotification : public IUnknown
{
   //
   // Summary:
   //    Registers a callback notification for an asynchronous event.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - The IUnknown::AddRef method of the in_pIEventNotificationCallback parameter is called when the notification
   //      is registered to prevent the object implementing the IMvEventNotificationCallback interface from being 
   //      destroyed.
   //
   virtual HRESULT __stdcall RegisterCallbackForNotification
      (
      IMvEventNotificationCallback* in_pIEventNotificationCallback   // Pointer to the event notification callback
                                                                     // interface.
      ) = 0;

   //
   // Summary:
   //    Unregisters a callback notification for an asynchronous event.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::Release method of the in_pIEventNotificationCallback parameter is called when the notification
   //      is unregistered to remove the reference count added by 
   //      IMvEventNotification::RegisterCallbackForNotification.
   //
   virtual HRESULT __stdcall UnregisterCallbackForNotification
      (
      IMvEventNotificationCallback* in_pIEventNotificationCallback   // Pointer to the event notification callback
                                                                     // interface.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Registers and unregisters the IMvTemperatureNotificationCallback interface if a temperature sensor on the card
//    overheats. 
// Remarks:
//    - The application creates an object that implements the IMvTemperatureNotificationCallback interface
//		that will be passed to the RegisterCallbackForNotification and UnregisterCallbackForNotification methods.
// Note:
//    - Also used for fan malfunction notification (for X.mio3 and some DSX LE4 models).
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvTemperatureNotification : public IUnknown
{
   //
   // Summary:
   //    Registers a callback notification for the temperature sensors if a temperature sensor on the card overheats.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::AddRef method of the in_pITemperatureNotificationCallback parameter is called when the
   //      notification is registered to prevent the object implementing the IMvTemperatureNotificationCallback
   //      interface from being destroyed.
   //
   virtual HRESULT __stdcall RegisterCallbackForNotification
      (
      IMvTemperatureNotificationCallback* in_pITemperatureNotificationCallback   // Pointer to the temperature sensors
                                                                                 // notification callback interface.
      ) = 0;

   //
   // Summary:
   //    Unregisters a callback notification for the temperature sensors.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::Release method of the in_pITemperatureNotificationCallback parameter is called when the
   //      notification is unregistered to remove the reference count added by
   //      IMvTemperatureNotification::RegisterCallbackForNotification.
   //
   virtual HRESULT __stdcall UnregisterCallbackForNotification
      (
      IMvTemperatureNotificationCallback* in_pITemperatureNotificationCallback   // Pointer to the temperature sensors
                                                                                 // notification callback interface.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Base interface for all connector types. 
// Remarks:
//    - This interface provides general information about a physical connector.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvConnector : public IUnknown
{
   //
   // Summary:
   //    Indicates whether or not the connector is an audio connector. 
   // Return value:
   //    - bool: If true, the connector is an audio connector.
   // Remarks:
   //    - Implements the IMvAudioInputConnector or IMvAudioOutputConnector interface.
   //
   virtual bool __stdcall IsAudioConnector() = 0;

   //
   // Summary:
   //    Indicates whether or not the connector is a video connector.
   // Return value:
   //    - bool: If true, the connector is a video connector. 
   // Remarks:
   //    - Implements the IMvVideoInputConnector or IMvVideoOutputConnector interface.
   //
   virtual bool __stdcall IsVideoConnector() = 0;

   //
   // Summary:
   //    Indicates whether or not the connector is an input connector. 
   // Return value:
   //    - bool: If true, the connector is an input connector. 
   // Remarks:
   //    - Implements the IMvAudioInputConnector or IMvVideoInputConnector interface.
   //
   virtual bool __stdcall IsInputConnector() = 0;

   //
   // Summary:
   //    Indicates whether or not the connector is an output connector. 
   // Return value:
   //    - bool: If true, the connector is an output connector. 
   // Remarks:
   //    - Implements the IMvAudioOutputConnector or IMvVideoOutputConnector interface.
   //
   virtual bool __stdcall IsOutputConnector() = 0;

   //
   // Summary:
   //    Indicates whether or not the connector is available.
   // Return value:
   //    - bool: If true, the connector is available.
   //
   virtual bool __stdcall IsAvailable() = 0;

   //
   // Summary:
   //    Retrieves the IMvCardConfiguration interface associated with the connector.
   // Return value:
   //    - Pointer to the interface.  There is no AddRef call on this interface.
   //
   virtual IMvCardConfiguration * __stdcall GetCardConfigurationInterface() = 0;

   //
   // Summary:
   //    Retrieves the type of the connector.
   // Return value
   //    - EMvConnectorType: The connector type.    
   //
   virtual EMvConnectorType __stdcall GetConnectorType() = 0;

};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Base interface for all audio input connector types. 
// Remarks:
//    - This interface can be queried for the audio input connector type, such as whether it is an AES/EBU pair or SDI
//      embedded audio. 
//    - This interface can also be used for input stream configuration.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvAudioInputConnector : public IMvConnector
{
   //
   // Summary:
   //    Gets the audio type (such as AES/EBU pair or SDI embedded audio) of the
   //    connector.
   // Return value:
   //    - EMvAudioType: Describes the type of audio connector.
   //
   virtual EMvAudioType __stdcall GetAudioType() = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Base interface for all audio output connector types. 
// Remarks:
//    - This interface can be queried for the audio output connector type, such as whether it is an AES/EBU pair or
//      SDI embedded audio. 
//    - This interface can also be used for output stream configuration.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvAudioOutputConnector : public IMvConnector
{
   //
   // Summary:
   //    Gets the audio type (such as AES/EBU pair or SDI embedded audio) of the
   //    connector.
   // Return value:
   //    - EMvAudioType: Describes the type of audio connector.
   //
   virtual EMvAudioType __stdcall GetAudioType() = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Base interface for all video input connector types. 
// Remarks:
//    - This interface can be queried for the physical details of the video connector.
//    - This interface can also be used to configure the input stream.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvVideoInputConnector : public IMvConnector
{
   //
   // Summary:
   //    Gets the video input connector label.
   // Return value:
   //    - EMvVideoConnectorLabel: Video input connector label. 
   //
   virtual EMvVideoConnectorLabel __stdcall GetVideoInputConnectorLabel() = 0;

   //
   // Summary:
   //    Gets the signal type of the video input connector, such as whether it is an SDI video input signal.
   // Return value:
   //    - EMvVideoSignal: Video input signal type of the connector.
   //
   virtual EMvVideoSignal __stdcall GetVideoInputSignalType() = 0;

   //
   // Summary:
   //    Gets the current status of the video input connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetVideoConnectorStatus
      (
      SMvVideoConnectorStatus& io_rsVideoConnectorStatus // Structure that receives the current status of the video
                                                         // input connector.
      ) = 0;

   //
   // Summary:
   //    Gets the notification interface of the video input connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetVideoConnectorNotification
      (
      IMvVideoConnectorNotification** out_ppIVideoConnectorNotification // Pointer that receives the notification
                                                                        // interface of the video input connector.
      ) = 0;

   //
   // Summary:
   //    Gets the connector interface of the connector that will capture the alpha values.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetAssociatedAlphaConnector
      (
      IMvVideoInputConnector** out_ppIAlphaConnector  // Pointer that receives the connector interface of the 
                                                      // connector that will capture the alpha values.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Base interface for all video output connector types. 
// Remarks:
//    - This interface can be queried for the physical details of the video connector.
//    - This interface can also be used to configure the output stream.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvVideoOutputConnector : public IMvConnector
{
   //
   // Summary:
   //    Gets the video output connector label.
   // Return value:
   //    - EMvVideoConnectorLabel: Video output connector label.
   //
   virtual EMvVideoConnectorLabel __stdcall GetVideoOutputConnectorLabel() = 0;

   //
   // Summary:
   //    Gets the signal type of the video output connector, such as whether it is an SDI video output signal.
   // Return value:
   //    - EMvVideoSignal: Video output signal type of the connector.
   //
   virtual EMvVideoSignal __stdcall GetVideoOutputSignalType() = 0;

   //
   // Summary:
   //    Gets the connector interface of the connector that will output the alpha values.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetAssociatedAlphaConnector
      (
      IMvVideoOutputConnector** out_ppIAlphaConnector // Pointer that receives the connector interface of the 
                                                      // connector that will output the alpha values.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents an AES/EBU audio input pair connector. 
// Remarks:
//    - This interface can be queried for the physical details of the AES/EBU audio input pair connector.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvAesEbuAudioInputPairConnector : public IMvAudioInputConnector
{
   //
   // Summary:
   //    Gets a pair identifier from a group of AES/EBU audio input pair connectors.
   // Return value:
   //    - EMvAudioPair: Identifier from a group of AES/EBU audio input pair connectors.
   //
   virtual EMvAudioPair __stdcall GetAesEbuAudioInputPairConnectorIdentifier() = 0;

   //
   // Summary:
   //    Gets a group of AES/EBU audio input pair connectors.
   // Return value:
   //    - EMvAesEbuGroup: AES/EBU audio input pair connector group.
   //
   virtual EMvAesEbuGroup __stdcall GetAesEbuAudioInputPairConnectorGroup() = 0;

   //
   // Summary:
   //    Gets the current status of an AES/EBU audio input connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetAesEbuAudioInputConnectorsStatus
      (
      SMvAudioPairStatus& io_rsAudioPairStatus	// Structure that receives the status of the AES/EBU audio input pair connector.
      ) = 0;

   //
   // Summary:
   //    Gets the notification interface of an AES/EBU audio input connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetAesEbuAudioInputConnectorsNotification
      (
      IMvAesEbuAudioConnectorsNotification** out_ppIAesEbuAudioNotification   // Pointer that receives the notification 
                                                                              // interface of an AES/EBU audio input
                                                                              // connector.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents an AES/EBU audio output pair connector. 
// Remarks:
//    - This interface can be queried for the physical details of the AES/EBU audio output pair connector.
//    - This interface can also be used to query or change a connector's current settings.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvAesEbuAudioOutputPairConnector : public IMvAudioOutputConnector
{
   //
   // Summary:
   //    Gets a pair identifier from a group of AES/EBU audio output pair connectors.
   // Return value:
   //    - EMvAudioPair: Identifier from a group of AES/EBU audio input pair connectors.
   //
   virtual EMvAudioPair __stdcall GetAesEbuAudioOutputPairConnectorIdentifier() = 0;

   //
   // Summary:
   //    Gets a group of AES/EBU audio output pair connectors.
   // Return value:
   //    - EMvAesEbuGroup: AES/EBU audio output pair connector group.
   //
   virtual EMvAesEbuGroup __stdcall GetAesEbuAudioOutputPairConnectorGroup() = 0;

   //
   // Summary:
   //    Gets the current settings of an AES/EBU audio output pair connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetAesEbuAudioOutputPairConnectorSettings
      (
      SMvAesEbuAudioOutputPairConnectorSettings& io_rsAesEbuAudioOutputPairConnectorSettings // Structure that receives
                                                                                             // the AES/EBU audio output
                                                                                             // pair connector settings.
      ) = 0;

   //
   // Summary:
   //    Modifies the current settings of an AES/EBU audio output pair connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetAesEbuAudioOutputPairConnectorSettings
      (
      SMvAesEbuAudioOutputPairConnectorSettings& in_rsAesEbuAudioOutputPairConnectorSettings // Structure of the AES/EBU
                                                                                             // audio output pair
                                                                                             // connector settings.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents an embedded SDI audio input virtual pair connector.
// Remarks:
//    - This interface is used to configure the audio input.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSdiEmbeddedAudioInputPairConnector : public IMvAudioInputConnector
{
   //
   // Summary:
   //    Gets the pair identifier for the corresponding audio pair.
   // Return value:
   //    - EMvAudioPair: Pair identifier.
   //
   virtual EMvAudioPair __stdcall GetPairIdentifier() = 0;

};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents an embedded SDI audio output virtual pair connector.
// Remarks:
//    - This interface is used to configure the audio output.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSdiEmbeddedAudioOutputPairConnector : public IMvAudioOutputConnector
{
   //
   // Summary:
   //    Gets the pair identifier for the corresponding audio pair.
   // Return value:
   //    - EMvAudioPair: Pair identifier.
   //
   virtual EMvAudioPair __stdcall GetPairIdentifier() = 0;

};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates the embedded SDI audio input pair connectors. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSdiEmbeddedAudioInputPairConnectorsEnumerator : public IUnknown
{
   //
   // Summary:
   //    Updates and resets the internal list of interfaces.
   // Description:
   //    The internal list of embedded SDI audio input pair connector interfaces is updated with the most recent 
   //    values on the card and the internal pointer is reset so that the next call to
   //    IMvSdiEmbeddedAudioInputPairConnectorsEnumerator::Next returns the first embedded SDI audio input pair 
   //    connector interface in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Reset() = 0;

   //
   // Summary:
   //   Gets the next interface.
   // Description:
   //	  The next embedded SDI audio input pair connector interface is retrieved from the internal list of embedded SDI
   //   audio input pair connector interfaces.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Next
      (
      IMvSdiEmbeddedAudioInputPairConnector** out_ppISdiEmbeddedAudioInputPairConnector   // Pointer that receives the
                                                                                          // next embedded SDI audio
                                                                                          // input pair connector 
                                                                                          // interface.
      ) = 0;

   //
   // Summary:
   //    Skips a given number of interfaces.
   // Description:
   //    The internal pointer is changed so that the next call to IMvSdiEmbeddedAudioInputPairConnectorsEnumerator::Next 
   //    skips a given number of embedded SDI audio input pair connector interfaces in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Skip
      (
      uint32_t in_ui32Count   // Number of embedded SDI audio input pair connector interfaces to skip.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates the embedded SDI audio output pair connectors. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSdiEmbeddedAudioOutputPairConnectorsEnumerator : public IUnknown
{
   //
   // Summary:
   //    Updates and resets the internal list of interfaces.
   // Description:
   //    The internal list of embedded SDI audio output pair connector interfaces is updated with the most recent
   //    values on the card and the internal pointer is reset so that the next call to
   //    IMvSdiEmbeddedAudioOutputPairConnectorsEnumerator::Next returns the first embedded SDI audio output pair
   //    connector interface in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Reset() = 0;

   //
   // Summary:
   //    Gets the next interface.
   // Description:
   //	   The next embedded SDI audio output pair connector interface is retrieved from the internal list of embedded SDI
   //    audio output pair connector interfaces.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Next
      (
      IMvSdiEmbeddedAudioOutputPairConnector** out_ppISdiEmbeddedAudioOutputPairConnector // Pointer that receives the
                                                                                          // next embedded SDI audio 
                                                                                          // output pair connector
                                                                                          // interface.
      ) = 0;

   //
   // Summary:
   //    Skips a given number of interfaces.
   // Description:
   //    The internal pointer is changed so that the next call to IMvSdiEmbeddedAudioOutputPairConnectorsEnumerator::Next
   //    skips a given number of embedded SDI audio output pair connector interfaces in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Skip
      (
      uint32_t in_ui32Count   // Number of embedded SDI audio output pair connector interfaces to skip.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents an SDI video input connector. 
// Remarks:
//    - This interface can be queried for the physical details of the SDI video input connector.
//    - This interface can also be used to query or change a connector's current settings.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSdiVideoInputConnector : public IMvVideoInputConnector
{
   //
   // Summary:
   //    Creates the enumerator for the embedded SDI audio input pair connector for the corresponding SDI video input
   //    connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateSdiEmbeddedAudioInputPairConnectorsEnumerator
      (
      IMvSdiEmbeddedAudioInputPairConnectorsEnumerator** out_ppIConnectorsEnumerator // Pointer that receives the 
                                                                                     // embedded SDI audio input pair 
                                                                                     // connector enumerator for the
                                                                                     // corresponding SDI video input
                                                                                     // connector.
      ) = 0;

   //
   // Summary:
   //    Gets the embedded SDI audio input pair connector using the pair ID.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetSdiEmbeddedConnector
      (
      uint32_t in_ui32Pair, // Connector identifier.
      IMvSdiEmbeddedAudioInputPairConnector** out_ppISdiEmbeddedAudioInputPairConnector // Pointer that receives the 
                                                                                        // embedded SDI audio input
                                                                                        // pair connector interface.
      ) = 0;

   //
   // Summary:
   //    Gets the current audio and video settings of the SDI input connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetSdiInputConnectorSettings
      (
      SMvSdiInputConnectorSettings& io_rsSdiInputConnectorSettings // Structure that receives the current SDI input 
                                                                   // connector settings. 
      ) = 0;

   //
   // Summary:
   //    Modifies the current audio and video settings of the SDI input connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetSdiInputConnectorSettings
      (
      SMvSdiInputConnectorSettings& in_rsSdiInputConnectorSettings // Structure of the new SDI input settings.
      ) = 0;

   //
   // Summary:
   //    Gets the notification interface of the embedded SDI audio input connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetSdiEmbeddedAudioInputConnectorNotification
      (
      IMvSdiEmbeddedAudioConnectorNotification** out_ppISdiEmbeddedAudioConnectorNotification // Pointer that receives 
                                                                                              // the notification 
                                                                                              // interface of an embedded
                                                                                              // SDI audio input connector.
      ) = 0;

   //
   // Summary:
   //    Gets the number of embedded SDI audio input pair connectors.
   // Return value:
   //    - uint32_t: Number of embedded SDI audio input pair connectors. 
   //
   virtual uint32_t __stdcall GetSdiEmbeddedAudioInputConnectorCount
      (
      ) = 0;

   //
   // Summary:
   //    Gets the current status of the embedded SDI audio input connectors.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetSdiEmbeddedAudioInputPairConnectorsStatuses
      (
      SMvAudioPairStatus out_asAudioPairStatus[],  // Pointer to the array of structures that receives the status of the
                                                   // embedded SDI audio input pair connectors.
      uint32_t in_ui32ArrayCount                   // The number of elements in the array.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents an SDI video output connector. 
// Remarks:
//    - This interface can be queried for the physical details of the SDI video output connector.
//    - This interface can also be used to query or change a connector's current settings.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSdiVideoOutputConnector : public IMvVideoOutputConnector
{
   //
   // Summary:
   //    Creates the enumerator for the embedded SDI audio output connector for the corresponding SDI video output connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateSdiEmbeddedAudioOutputPairConnectorsEnumerator
      (
      IMvSdiEmbeddedAudioOutputPairConnectorsEnumerator** out_ppIConnectorsEnumerator // Pointer that receives the 
                                                                                      // embedded SDI audio output pair 
                                                                                      // connector enumerator for the 
                                                                                      // corresponding SDI video output
                                                                                      // connector.
      ) = 0;

   //
   // Summary:
   //    Gets the current SDI output connector settings.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetSdiOutputConnectorSettings
      (
      SMvSdiOutputConnectorSettings& io_rsSdiOutputConnectorSettings // Structure that receives the SDI output 
                                                                     // connector settings.
      ) = 0;

   //
   // Summary:
   //    Modifies the current SDI output connector settings.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetSdiOutputConnectorSettings
      (
      SMvSdiOutputConnectorSettings& in_rsSdiOutputConnectorSettings  // Structure of the SDI output connector settings.
      ) = 0;

   //
   // Summary:
   //    Modifies the current output stream source and audio pairs.    
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetSourceOutputStreamAndAudioPairs
      (
      IMvOutputStream* in_pIOutputStream, // Pointer to the output stream interface.
      EMvAudioPair in_aeAudioPairs[],	   // Pointer to the array of the audio pairs output stream for the embedded SDI
                                          // audio pair connector.
      uint32_t in_ui32NbAudioPairs		   // Indicates the number of output audio pairs in in_aeAudioPairs.
      ) = 0;

   //
   // Summary:
   //    Gets the current output stream source and audio pairs.    
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetSourceOutputStreamAndAudioPairs
      (
      IMvOutputStream** out_ppIOutputStream, // Pointer that receives the output stream interface.
      EMvAudioPair out_aeAudioPairs[],		   // Pointer to the array that receives the audio pairs output stream for the
                                             // embedded SDI audio pair connector.
      uint32_t in_ui32NbAudioPairs		      // Indicates the number of output audio pairs in out_aeAudioPairs.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates the AES/EBU audio input pair connectors. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvAesEbuAudioInputPairConnectorsEnumerator : public IUnknown
{
   //
   // Summary:
   //    Updates and resets the internal list of interfaces.
   // Description:
   //    The internal list of AES/EBU audio input pair connector interfaces is updated with the most recent values on
   //    the card and the internal pointer is reset so that the next call to IMvAesEbuAudioInputPairConnectorsEnumerator::Next
   //    returns the first AES/EBU audio input pair connector interface in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Reset() = 0;

   //
   // Summary:
   //    Gets the next interface.
   // Description:
   //	 The next AES/EBU audio input pair connector interface is retrieved from the internal list of AES/EBU audio input
   //  pair connector interfaces.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Next
      (
      IMvAesEbuAudioInputPairConnector** out_ppIAesEbuAudioInputPairConnector // Pointer that receives the next
                                                                              // AES/EBU audio input pair connector 
                                                                              // interface.
      ) = 0;

   //
   // Summary:
   //    Skips a given number of interfaces.
   // Description:
   //	 The internal pointer is changed so that the next call to IMvAesEbuAudioInputPairConnectorsEnumerator::Next skips
   //  a given number of AES/EBU audio input pair connector interfaces in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Skip
      (
      uint32_t in_ui32Count   // Number of AES/EBU audio input pair connector interfaces to skip.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates the AES/EBU audio output pair connectors. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvAesEbuAudioOutputPairConnectorsEnumerator : public IUnknown
{
   //
   // Summary:
   //    Updates and resets the internal list of interfaces.
   // Description:
   //    The internal list of AES/EBU audio output pair connector interfaces is updated with the most recent values on
   //    the card and the internal pointer is reset so that the next call to IMvAesEbuAudioOutputPairConnectorsEnumerator::Next
   //    returns the first AES/EBU audio output pair connector interface in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Reset() = 0;

   //
   // Summary:
   //    Gets the next interface.
   // Description:
   //	   The next AES/EBU audio output pair connector interface is retrieved from the internal list of AES/EBU audio
   //    output pair connector interfaces.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Next
      (
      IMvAesEbuAudioOutputPairConnector** out_ppIAesEbuAudioOutputPairConnector  // Pointer that receives the next
                                                                                 // AES/EBU audio output pair connector
                                                                                 // interface.
      ) = 0;

   //
   // Summary:
   //    Skips a given number of interfaces.
   // Description:
   //	   The internal pointer is changed so that the next call to IMvAesEbuAudioOutputPairConnectorsEnumerator::Next 
   //    skips a given number of AES/EBU audio output pair connector interfaces in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Skip
      (
      uint32_t in_ui32Count   // Number of AES/EBU audio output pair connector interfaces to skip.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates the SDI video input connectors. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSdiVideoInputConnectorsEnumerator : public IUnknown
{
   //
   // Summary:
   //    Updates and resets the internal list of interfaces.
   // Description:
   //    The internal list of SDI video input connector interfaces is updated with the most recent values on the card
   //    and the internal pointer is reset so that the next call to IMvSdiVideoInputConnectorsEnumerator::Next returns
   //    the first SDI video input connector interface in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Reset() = 0;

   //
   // Summary:
   //    Gets the next interface.
   // Description:
   //	   The next SDI video input connector interface is retrieved from the internal list of SDI video input connector
   //    interfaces.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Next
      (
      IMvSdiVideoInputConnector** out_ppISdiVideoInputConnector  // Pointer that receives the next SDI video input
                                                                 // connector interface.
      ) = 0;

   //
   // Summary:
   //    Skips a given number of interfaces.
   // Description:
   //	   The internal pointer is changed so that the next call to IMvSdiVideoInputConnectorsEnumerator::Next skips a
   //    given number of SDI video input connector interfaces in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Skip
      (
      uint32_t in_ui32Count   // Number of SDI video input connector interfaces to skip.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates the SDI video output connectors. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSdiVideoOutputConnectorsEnumerator : public IUnknown
{
   //
   // Summary:
   //    Updates and resets the internal list of interfaces.
   // Description:
   //    The internal list of SDI video output connector interfaces is updated with the most recent values on the card
   //    and the internal pointer is reset so that the next call to IMvSdiVideoOutputConnectorsEnumerator::Next returns
   //    the first SDI video output connector interface in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Reset() = 0;

   //
   // Summary:
   //    Gets the next interface.
   // Description:
   //	   The next SDI video output connector interface is retrieved from the internal list of SDI video output connector
   //    interfaces.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Next
      (
      IMvSdiVideoOutputConnector** out_ppISdiVideoOutputConnector // Pointer that receives the next SDI video output
                                                                  // connector interface.
      ) = 0;

   //
   // Summary:
   //    Skips a given number of interfaces.
   // Description:
   //	   The internal pointer is changed so that the next call to IMvSdiVideoOutputConnectorsEnumerator::Next skips a 
   //    given number of SDI video output connector interfaces in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Skip
      (
      uint32_t in_ui32Count   // Number of SDI video output connector interfaces to skip.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates the watchdogs on the card (for topology-based hardware only).
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvWatchdogsEnumerator : public IUnknown
{
   //
   // Summary:
   //    Updates and resets the internal list of interfaces.
   // Description:
   //    The internal list of watchdog interfaces is updated with the most recent values on the card and the 
   //    internal pointer is reset so that the next call to IMvWatchdogsEnumerator::Next returns the first
   //    watchdog interface in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Reset() = 0;

   //
   // Summary:
   //    Gets the next watchdog interface.
   // Description:
   //	   The next watchdog interface is retrieved from the internal list of watchdog interfaces.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Next
      (
      IMvWatchdog** out_ppIWatchdog // Pointer that receives the next watchdog interface.
      ) = 0;

   //
   // Summary:
   //    Skips a given number of watchdog interfaces.
   // Description:
   //    The internal pointer is changed so that the next call to IMvWatchdogsEnumerator::Next skips a
   //    given number of watchdog interfaces in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Skip
      (
      uint32_t in_ui32Count   // Number of watchdog interfaces to skip.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to configure and query the genlock.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvGenlockConfiguration : public IUnknown
{
   //
   // Summary:
   //    Gets the current genlock settings.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetGenlockSettings
      (
      SMvGenlockSettings& io_rsSettings     // Structure that receives the genlock settings.
      ) = 0;

   //
   // Summary:
   //    Modifies the current genlock settings.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetGenlockSettings
      (
      SMvGenlockSettings& in_rsSettings  // Structure of the genlock settings.
      ) = 0;

   //
   // Summary:
   //    Creates the notification interface of the genlock.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateGenlockNotification
      (
      IMvGenlockNotification** out_ppIGenlockNotification   // Pointer that receives the notification interface of the
                                                            // genlock.
      ) = 0;

   //
   // Summary:
   //    Gets the current genlock status.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetGenlockStatus
      (
      SMvGenlockInputStatus& io_rsGenlockStatus   // Structure that receives the genlock input status.
      ) = 0;

   //
   // Summary:
   //    Gets the current blackburst status (status coming from the blackburst reference connector).
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_NOT_SUPPORTED, if the functionnality is not supported on the card. 
   //
   virtual HRESULT __stdcall GetBlackburstStatus
      (
      SMvBlackburstStatus& io_rsBlackburstkStatus   // Structure that receives the blackburst input status.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to configure and query the time code.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvTimeCodeConfiguration : public IUnknown
{
   //
   // Summary:
   //    Gets the current time code settings.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetTimeCodeSettings
      (
      SMvTimeCodeSettings& io_rsSettings     // Structure that receives the time code settings.
      ) = 0;

   //
   // Summary:
   //    Modifies the current time code settings.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetTimeCodeSettings
      (
      SMvTimeCodeSettings& in_rsSettings  // Structure of the time code settings.
      ) = 0;

   //
   // Summary:
   //    Gets the current time code information for the requested time stamp.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_NOT_FOUND, if no time code was found for the requested time stamp.
   //
   virtual HRESULT __stdcall GetTimeCodeInformation
      (
      SMvTimeCodeInformation& io_rsTimeCodeInfo   // Structure that receives the time code information.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to configure and query the analog linear time code.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvALTCConfiguration : public IUnknown
{
   //
   // Summary:
   //    Gets the current analog linear time code settings.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetALTCSettings
      (
      SMvALTCSettings& io_rsSettings   // Structure that receives the analog linear time code settings.
      ) = 0;

   //
   // Summary:
   //    Modifies the current analog linear time code settings.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetALTCSettings
      (
      const SMvALTCSettings& in_rsSettings  // Structure of the analog linear time code settings.
      ) = 0;

   //
   // Summary:
   //    Gets the current analog linear time code information for the requested time stamp.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //    - MV_E_NOT_FOUND, if no time code was found for the requested time stamp.
   //
   virtual HRESULT __stdcall GetALTCInformation
      (
      SMvTimeCodeInformation& io_rsTimeCodeInfo   // Structure that receives the time code information.
      ) = 0;

   //
   // Summary:
   //    Gets the input system clock associated with the analog linear time code input.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetAssociatedInputClock
      (
      IMvSystemClock ** out_ppIInputClock   // Pointer that receives the input system clock interface.
                                            // If no input clock is present, it will return a NULL value.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents a node in a workflow topology. 
// Remarks:
//    - This interface is used as the source or destination of a stream.
//    - The node's contents, such as video and audio data, can be queried or modified by the host for every frame.
//    - Nodes enforce a configurable write-to-read delay in clock ticks that defaults to one frame.
//    - Nodes have a configurable depth in frames allowing the host to have a certain time to access past node data.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvNode : public IUnknown
{
   //
   // Summary:
   //    Indicates whether or not the node still exists on the card.
   // Return value:
   //    - bool: If true, the node still exists on the card.
   //
   virtual bool __stdcall StillExists() = 0;

   //
   // Summary:
   //    Destroys a node in the topology on the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - The node interface becomes non-functional after this method is called.
   //
   virtual HRESULT __stdcall DestroyNode() = 0;

   //
   // Summary:
   //    Gets the node contents from a certain frame time stamp in a field-based workflow.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If the node does not contain audio and/or VANC data, the pointer(s) to that data must be null.
   //    - If you do not want to receive all the data contained in the node, pass valid pointers for the node content 
   //      data that you would like to obtain and set the other pointers to NULL. For example, if the node contains 
   //      video, audio, and VANC data, but you only want video data, pass valid pointers for io_pIVideoF0 and io_pIVideoF1, 
   //      and set the other pointers to NULL.
   //
   virtual HRESULT __stdcall GetNodeContentFields
      (
      IMvSurface* io_pIVideoF0,        // Pointer to the IMvSurface interface that receives the first video field.
      IMvSurface* io_pIVideoF1,        // Pointer to the IMvSurface interface that receives the second video field.
      IMvAudioSamples* io_pIAudioF0,   // Pointer to the IMvAudioSamples interface that receives the audio associated
                                       // with the first video field.
      IMvAudioSamples* io_pIAudioF1,   // Pointer to the IMvAudioSamples interface that receives the audio associated
                                       // with the second video field.
      IMvSurface* io_pIVancF0,         // Pointer to the IMvSurface interface that receives the VANC data associated
                                       // with the first video field.
      IMvSurface* io_pIVancF1          // Pointer to the IMvSurface interface that receives the VANC data associated
                                       // with the second video field.
      ) = 0;

   //
   // Summary:
   //    Gets the node contents from a certain field time stamp in a field-based workflow.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - If the node does not contain audio and/or VANC data, the pointer(s) to that data must be null.
   //    - If you do not want to receive all the data contained in the node, pass valid pointers for the node content 
   //      data that you would like to obtain and set the other pointers to NULL. For example, if the node contains 
   //      video, audio, and VANC data, but you only want video data, pass a valid pointer for io_pIVideo,  
   //      and set the other pointers to NULL.
   //
   virtual HRESULT __stdcall GetNodeContentField
      (
      IMvSurface* io_pIVideo,       // Pointer to the IMvSurface interface that receives the video field.
      IMvAudioSamples* io_pIAudio,  // Pointer to the IMvAudioSamples interface that receives the audio associated
                                    // with the video field.
      IMvSurface* io_pIVanc         // Pointer to the IMvSurface interface that receives the VANC data associated with
                                    // the video field.
      ) = 0;   

   //
   // Summary:
   //    Gets the node contents from a certain frame time stamp in a frame-based workflow.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - If the node does not contain audio and/or VANC data, the pointer(s) to that data must be null.
   //    - If you do not want to receive all the data contained in the node, pass valid pointers for the node content 
   //      data that you would like to obtain and set the other pointers to NULL. For example, if the node contains 
   //      video, audio, and VANC data, but you only want video data, pass a valid pointer for io_pIVideo,  
   //      and set the other pointers to NULL.
   //
   virtual HRESULT __stdcall GetNodeContentFrame
      (
      IMvSurface* io_pIVideo,       // Pointer to the IMvSurface interface that receives the video frame.
      IMvAudioSamples* io_pIAudio,  // Pointer to the IMvAudioSamples interface that receives the audio associated
                                    // with the video frame.
      IMvSurface* io_pIVanc         // Pointer to the IMvSurface interface that receives the VANC data associated with
                                    // the video frame.
      ) = 0;   

   //
   // Summary:
   //    Modifies the node contents for a certain frame time stamp in a field-based workflow.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If the node does not contain audio and/or VANC data, the pointer(s) to that data must be null.
   //    - If you do not want to modify all the data contained in the node, pass valid pointers for the node content 
   //      data that you would like to modify and set the other pointers to NULL. For example, if the node contains 
   //      video, audio, and VANC data, but you only want to modify the video data, pass valid pointers for io_pIVideoF0  
   //      and io_pIVideoF1, and set the other pointers to NULL.
   //
   virtual HRESULT __stdcall SetNodeContentFields
      (
      IMvSurface* in_pIVideoF0,        // Pointer to the IMvSurface interface of the first video field.
      IMvSurface* in_pIVideoF1,        // Pointer to the IMvSurface interface of the second video field.
      IMvAudioSamples* in_pIAudioF0,   // Pointer to the IMvAudioSamples interface of the audio associated with the
                                       // first video field.
      IMvAudioSamples* in_pIAudioF1,   // Pointer to the IMvAudioSamples interface of the audio associated with the 
                                       // second video field.
      IMvSurface* in_pIVancF0,         // Pointer to the IMvSurface interface of the VANC data associated with the
                                       // first video field.
      IMvSurface* in_pIVancF1          // Pointer to the IMvSurface interface of the VANC data associated with the 
                                       // second video field.
      ) = 0;

   //
   // Summary:
   //    Modifies the node contents for a certain field time stamp in a field-based workflow.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - If the node does not contain audio and/or VANC data, the pointer(s) to that data must be null.
   //    - If you do not want to modify all the data contained in the node, pass valid pointers for the node content 
   //      data that you would like to modify and set the other pointers to NULL. For example, if the node contains 
   //      video, audio, and VANC data, but you only want to modify the video data, pass a valid pointer for io_pIVideo,  
   //      and set the other pointers to NULL.
   //
   virtual HRESULT __stdcall SetNodeContentField
      (
      IMvSurface* in_pIVideo,       // Pointer to the IMvSurface interface of the video field.
      IMvAudioSamples* in_pIAudio,  // Pointer to the IMvAudioSamples interface of the audio associated with the video field.
      IMvSurface* in_pIVanc         // Pointer to the IMvSurface interface of the VANC data associated with the video field.
      ) = 0;

   //
   // Summary:
   //    Modifies the node contents for a certain frame time stamp in a frame-based workflow.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - If the node does not contain audio and/or VANC data, the pointer(s) to that data must be null.
   //    - If you do not want to modify all the data contained in the node, pass valid pointers for the node content 
   //      data that you would like to modify and set the other pointers to NULL. For example, if the node contains 
   //      video, audio, and VANC data, but you only want to modify the video data, pass a valid pointer for io_pIVideo,  
   //      and set the other pointers to NULL.
   //
   virtual HRESULT __stdcall SetNodeContentFrame
      (
      IMvSurface* in_pIVideo,       // Pointer to the IMvSurface interface of the video frame.
      IMvAudioSamples* in_pIAudio,  // Pointer to the IMvAudioSamples interface of the audio associated with the video frame.
      IMvSurface* in_pIVanc         // Pointer to the IMvSurface interface of the VANC data associated with the video frame.
      ) = 0;

   //
   // Summary:
   //    Gets the name of the node (for debugging purposes).
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetName
      (
      char* io_szName,  // An array of characters that will receive the name of the node.
      uint32_t in_ui32NbOfDestCharacters  // Indicates the number of characters in io_szName.
      ) = 0;

   //
   // Summary:
   //    Gets the write-to-read delay (in nanotime) of the node.
   // Return value:
   //    - uint64_t: Write-to-read delay in nanotime.
   // Remarks:
   //    - Provides the user application with a way to synchronize processing branches that do not have the same
   //      number of operations.
   //    - The write-to-read delay is set when the node is created using IMvTopology::CreateNode.
   //
   virtual uint64_t __stdcall GetWriteToReadDelayInNanoTime() = 0; 

   //
   // Summary:
   //    Gets the depth (in frames) of the node. 
   // Return value:
   //    - uint32_t: Depth in frames of the node.
   // Remarks:
   //    - This value represents the number of previous frames kept in the node. This allows the host to access a
   //      certain number of frames up to the current system time.
   //
   virtual uint32_t __stdcall GetNodeDepthInFrames() = 0;

   //
   // Summary:
   //    Gets the type of contents that will be included in the node (video, video and audio, or video, audio, and VANC).
   // Return value:
   //    - EMvNodeContent: Type of contents in the node. 
   //
   virtual EMvNodeContent __stdcall GetNodeContentType() = 0;

   //
   // Summary:
   //    Gets the settings used to create the node.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetNodeDescription
      (
      SMvNodeSettingsVideo* io_psVideoSettings,		// Pointer to the SMvNodeSettingsVideo structure that receives the
                                                   // video settings to create the node.
      SMvNodeSettingsAudio* io_psAudioSettings,		// Pointer to the SMvNodeSettingsAudio structure that receives the
                                                   // audio settings to create the node.
      SMvNodeSettingsVanc* io_psVancSettings		   // Pointer to the SMvNodeSettingsVanc structure that receives the
                                                   // VANC settings to create the node.
      ) = 0;

   //
   // Summary:
   //    Retrieves the IMvCardConfiguration interface associated with the connector.
   // Return value:
   //    - Pointer to the interface.  There is no AddRef call on this interface.
   //
   virtual IMvCardConfiguration * __stdcall GetCardConfigurationInterface() = 0;

   //
   // Summary:
   //    Gets the type of node (such as card node, host node, or compressed host node).
   //
   // Description:
   //    The type of node returned by this method is used to query a node's specific interface, such as IMvHostNode, 
   //    IMvCompressedHostNode, IMvTextureGpuNode, or IMvRenderingTargetGpuNode.
   //
   // Return value:
   //    - EMvNodeType: Type of node. 
   //
   virtual EMvNodeType __stdcall GetNodeType() = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates the nodes in the topology. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvNodesEnumerator : public IUnknown
{
   //
   // Summary:
   //    Updates and resets the internal list of node interfaces.
   // Description:
   //    The internal list of node interfaces is updated with the most recent values on the card
   //    and the internal pointer is reset so that the next call to IMvNodesEnumerator::Next returns the
   //    first node interface in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Reset() = 0;

   //
   // Summary:
   //    Gets the next node interface.
   // Description:
   //	 The next node interface is retrieved from the internal list of node interfaces.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Next
      (
      IMvNode** out_ppINode   // Pointer that receives the next node interface.
      ) = 0;

   //
   // Summary:
   //    Skips a given number of node interfaces.
   // Description:
   //    The internal pointer is changed so that the next call to IMvNodesEnumerator::Next skips a
   //    given number of node interfaces in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Skip
      (
      uint32_t in_ui32Count   // Number of node interfaces to skip.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Base interface for all types of streams. 
// Remarks:
//    - Streams perform operations on video, audio, and VANC data.
//    - Depending on the type of stream, the inputs and outputs are either nodes or connectors.
//    - This interface can be queried for general information about a stream or can be used to destroy a stream.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvStream : public IUnknown
{
   //
   // Summary:
   //    Indicates whether or not the stream still exists on the card.
   // Return value:
   //    - bool: If true, the stream still exists on the card.
   //
   virtual bool __stdcall StillExists() = 0;

   //
   // Summary:
   //    Destroys a stream on the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The stream interface (and all child interfaces) becomes non-functional after this method is called.
   //
   virtual HRESULT __stdcall DestroyStream() = 0;

   //
   // Summary:
   //    Gets the stream type (input, output, transform, or mixer stream).
   // Return value:
   //    - EMvStreamType: Type of stream.
   //
   virtual EMvStreamType __stdcall GetStreamType() = 0;

   //
   // Summary:
   //    Gets the name of the stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetName
      (
      char* io_szName,                    // An array of characters that will receive the name of the stream.
      uint32_t in_ui32NbOfDestCharacters  // Indicates the number of characters in io_szName.
      ) = 0;

   //
   // Summary:
   //    Retrieves the IMvCardConfiguration interface associated with the stream.
   // Return value:
   //    - Pointer to the interface.  There is no AddRef call on this interface.
   //
   virtual IMvCardConfiguration * __stdcall GetCardConfigurationInterface() = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents an input stream in a workflow topology. 
// Remarks:
//    - This interface is used to configure a capture from video and audio connectors.
//    - The results of this stream are put in a node buffer.
//    - This interface can be used to configure the input stream or can be queried for specific information about
//      the input stream.
//    - Each input stream is physically bound to a DMA channel on the Matrox hardware, and is therefore a limited
//      resource.
// Note:
//    Since video and audio connectors are also physically bound to a DMA channel, the only way to change the input
//    is between different input types, such as between SDI connector A and AES/EBU connector 1/2.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvInputStream : public IMvStream
{
   //
   // Summary:
   //    Gets the current settings of the input stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetInputStreamSettings
      (
      SMvInputStreamSettings& io_rsInputStreamSettings   // Structure that receives the input stream settings.
      ) = 0;

   //
   // Summary:
   //    Modifies the current settings of the input stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetInputStreamSettings
      (
      const SMvInputStreamSettings& in_rsInputStreamSettings   // Structure of the input stream settings.
      ) = 0;
   
   //
   // Summary:
   //    Gets the video connectors listing the video inputs currently bound to the input stream.
   //    Returns an IMvConnector interface
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetVideoConnectors
      (
      IMvConnector * out_apIConnectors[],    // Pointer that receives the array of video input stream
                                             // connector interfaces.
      uint32_t & io_ui32Count                // Indicates the number of connectors returned in
                                             // out_apIConnectors.
      ) = 0;

   //
   // Summary:
   //    Gets the video input connector currently bound to the input stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetVideoInputConnector
      (
      IMvVideoInputConnector** out_ppIVideoInputConnector   // Pointer that receives the video input stream connector
                                                            // interface.
      ) = 0;

   //
   // Summary:
   //    Gets the video input connectors listing the video inputs currently bound to the input stream.
   //    Returns an IMvVideoInputConnector interface
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT  __stdcall GetVideoInputConnectors
      (
      IMvVideoInputConnector* out_apIVideoInputConnector[], // Pointer that receives the array of video input stream
                                                            // connector interfaces.
      uint32_t & io_ui32Count                               // Indicates the number of connectors returned in
                                                            // out_apIVideoInputConnector.
      )=0;

   //
   // Summary:
   //    Gets the audio connectors listing the audio inputs currently bound to the input stream.
   //    Returns an IMvConnector interface
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetAudioConnectors
      (
      IMvConnector * out_apIConnectors[],    // Pointer that receives the array of audio input stream
                                             // connector interfaces.
      uint32_t & io_ui32Count                // Indicates the number of connectors returned in
                                             // out_apIConnectors
      ) = 0;

   //
   // Summary:
   //    Gets the audio input connectors listing the audio inputs bound to the input stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetAudioInputConnectors
      (
      IMvAudioInputConnector* out_apIAudioInputConnectors[],   // Pointer that receives the array of audio input stream
                                                               // connector interfaces.
      uint32_t in_ui32Count                                    // Indicates the number of connectors to get.
      ) = 0;

   //
   // Summary:
   //    Gets the audio input connectors count listing the audio inputs bound to the input stream.
   // Return value:
   //    - uint32_t: Number of audio input connectors managed by the input stream. 
   //
   virtual uint32_t __stdcall GetAudioInputConnectorsCount
      (
      ) = 0;

   //
   // Summary:
   //    Gets the Alpha connectors listing the Alpha inputs currently bound to the input stream.
   //    This method is for future usage.
   // Return value:
   //    - MV_E_NOT_SUPPORTED
   //
   virtual HRESULT __stdcall GetAlphaConnectors
      (
      IMvConnector * out_apIConnectors[],    // Pointer that receives the array of alpha input stream
                                             // connector interfaces.
      uint32_t & io_ui32Count                // Indicates the number of connectors returned in
                                             // out_apIConnectors
      ) = 0;

   //
   // Summary:
   //    Modifies the video input connector currently set to the input stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetVideoInputConnector
      (
      IMvVideoInputConnector* in_pIVideoInputConnector   // Pointer to the new video input connector interface.
      ) = 0;

   //
   // Summary:
   //    Modifies the audio connectors currently set to the input stream.
   //    Uses IMvConnector Interface for the connectors
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetAudioConnectors
      (
      IMvConnector * in_apIConnectors[],        // Pointer that contains the array of new Audio input stream
                                                // connector interfaces.
      uint32_t in_ui32Count                     // Indicates the number of connectors in in_apIConnectors
      ) = 0;

   //
   // Summary:
   //    Modifies the audio input connector(s) currently set to the input stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetAudioInputConnectors
      (
      IMvAudioInputConnector* in_apIAudioInputConnectors[], // Pointer to the array of new audio input connector
                                                            // interfaces.
      uint32_t in_ui32Count                                 // Indicates the number of audio input connectors in 
                                                            // in_apIAudioInputConnectors.
      ) = 0;

   //
   // Summary:
   //    Gets the output node currently bound to the input stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetOutputNode
      (
      uint64_t& out_rui64Timestamp, // Indicates the time that the output node was activated.
      IMvNode** out_ppIOutputNode   // Pointer that receives the output node interface.
      ) = 0;

   //
   // Summary:
   //    Modifies the output node currently bound to the input stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //
   virtual HRESULT __stdcall SetOutputNode
      (
      uint64_t in_ui64Timestamp,    // Indicates the time that the modifications are to be made.
      IMvNode* in_pIOutputNode      // Pointer to the new output node interface. The pointer will be used at the time
                                    // specified in in_ui64Timestamp. This parameter can be NULL.
      ) = 0;

   //
   // Summary:
   //    Gets the resolution of the input stream.
   //
   virtual void __stdcall GetResolution
      (
      SMvResolutionInfo& out_rsResInfo    // Structure that receives the resolution information of the input stream.
      ) = 0;

   //
   // Summary:
   //    Gets the time code from the input stream.
   //
   virtual HRESULT __stdcall GetInputTimecode
      (
      uint64_t in_ui64Timestamp,								         // Indicates the time stamp of the time code.
      SMvInputTimeCodeInformation& io_rsTimecodeInformation		// Structure that receives the time code information 
                                                               // from the input stream.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents an output stream in a workflow topology. 
// Remarks:
//    - This interface is used to configure a playback from video and audio connectors.
//    - The source of this stream comes from a node buffer.
//    - This interface can be used to configure the output stream or can be queried for specific information about the
//      output stream.
//    - Each output stream is physically bound to a DMA channel on the Matrox hardware, and is therefore a limited
//      resource.
//    - The DMA output can be simultaneously output to any and all the different connectors it is connected to.
// Note:
//  Since video and audio connectors are also physically bound to a DMA channel, the only way to change the output is
//  between different output types, such as between SDI connector A and AES/EBU connector 1/2.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvOutputStream : public IMvStream
{
   //
   // Summary:
   //    Gets the current settings of the output stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetOutputStreamSettings
      (
      SMvOutputStreamSettings& io_rsOutputStreamSettings // Structure that receives the output stream settings.
      ) = 0;

   //
   // Summary:
   //    Modifies the current settings of the output stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetOutputStreamSettings
      (
      const SMvOutputStreamSettings& in_rsOutputStreamSettings // Structure of the output stream settings.`
      ) = 0;

   //
   // Summary:
   //    Gets the input node currently bound to the output stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetInputNode
      (
      uint64_t& out_rui64Timestamp, // Indicates the time that the input node was activated.
      IMvNode** out_ppIInputNode    // Pointer that receives the input node interface.
      ) = 0;

   //
   // Summary:
   //    Modifies the input node currently bound to the output stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //
   virtual HRESULT __stdcall SetInputNode
      (
      uint64_t in_ui64Timestamp,    // Indicates the time that the modifications are to be made.
      IMvNode* in_pIInputNode       // Pointer to the new input node interface. The pointer will be used at the time
                                    // specified in in_ui64Timestamp. This parameter can be NULL.
      ) = 0;

   //
   // Summary:
   //    Gets the resolution of the output stream.
   //
   virtual void __stdcall GetResolution
      (
      SMvResolutionInfo& out_rsResInfo    // Structure that receives the resolution information of the output stream.
      ) = 0;

   //
   // Summary:
   //    Gets the video connectors listing the video outputs currently bound to the output stream.
   //    Returns an IMvConnector interface
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetVideoConnectors
      (
      IMvConnector * out_apIConnectors[],    // Pointer that receives the array of video output stream
                                             // connector interfaces.
      uint32_t & io_ui32Count                // Indicates the number of connectors returned in
                                             // out_apIConnectors.
      ) = 0;

   //
   // Summary:
   //    Gets the SDI video output connectors of the output stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetVideoOutputConnectors
      (
      IMvSdiVideoOutputConnector*  out_apIConnectors[],  // Pointer that receives the array of video output stream
                                                         // connector interfaces.
      uint32_t& io_rui32ConnectorsCount                  // Indicates the number of connectors returned in
                                                         // out_apIConnectors.
      ) = 0;

   //
   // Summary:
   //    Gets the Alpha connectors listing the Alpha outputs currently bound to the output stream.
   //    Returns an IMvConnector interface
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetAlphaConnectors
      (
      IMvConnector * out_apIConnectors[],    // Pointer that receives the array of alpha output stream
                                             // connector interfaces.
      uint32_t & io_ui32Count                // Indicates the number of connectors returned in
                                             // out_apIConnectors
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents a transform stream in a workflow topology. 
// Remarks:
//    - This interface is used for video scaling, audio repackaging, and VANC converting.
//    - Both the input and output of this stream are nodes.
//    - This interface can be configured using keyframes based on a time stamp or can be queried for specific 
//      information about the transform stream.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvTransformStream : public IMvStream
{
   //
   // Summary:
   //    Gets the current settings of the transform stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetTransformStreamSettings
      (
      uint64_t& out_rui64Timestamp,                            // Indicates the time that the transform stream settings
                                                               // were activated.    
      SMvTransformStreamSettings& io_rsTransformStreamSettings // Structure that receives the transform stream settings. 
      ) = 0;

   //
   // Summary:
   //    Modifies the current settings of the transform stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //
   virtual HRESULT __stdcall SetTransformStreamSettings
      (
      uint64_t in_ui64Timestamp,										// Indicates the time that the modifications are to be made.
      const SMvTransformStreamSettings& in_rsTransformStreamSettings	// Structure of the transform stream settings. 
      ) = 0;

   //
   // Summary:
   //    Gets the input node currently bound to the transform stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetInputNode
      (
      uint64_t& out_rui64Timestamp, // Indicates the time that the node was activated.
      IMvNode** out_ppIInputNode    // Pointer that receives the input node interface. 
      ) = 0;

   //
   // Summary:
   //    Modifies the input node currently bound to the transform stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //    - The new input node must have the same frame rate and the same scan mode as the old input node.
   //
   virtual HRESULT __stdcall SetInputNode
      (
      uint64_t in_ui64Timestamp, // Indicates the time that the modifications are to be made.
      IMvNode* in_pIInputNode    // Pointer to the new input node interface. The pointer will be used at the time
                                 // specified in in_ui64Timestamp.
      ) = 0;

   //
   // Summary:
   //    Gets the output node currently bound to the transform stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetOutputNode
      (
      uint64_t& out_rui64Timestamp, // Indicates the time that the node was activated.
      IMvNode** out_ppIOutputNode   // Pointer that receives the output node interface. 
      ) = 0;

   //
   // Summary:
   //    Modifies the output node currently bound to the transform stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //    - The new output node must have the same frame rate and the same scan mode as the old output node.
   //
   virtual HRESULT __stdcall SetOutputNode
      (
      uint64_t in_ui64Timestamp, // Indicates the time that the modification are to be made.
      IMvNode* in_pIOutputNode   // Pointer to the new output node interface. The pointer will be used at the time
                                 // specified in in_ui64Timestamp. This parameter can be NULL.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents a de-interlacer stream in a workflow topology. 
// Remarks:
//    - This interface is used for converting interlaced video data into progressive video data.
//    - Audio and VANC data can be copied from the input card node to the output card node containing progressive video data.
//    - Both the input and output of this stream are nodes.
//    - For supported video input and output card node formats, see the <i> Matrox DSX Topology API User Guide</i>.
//    - Only supported on hardware that supports the software MCE.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvDeInterlacerStream : public IMvStream
{
   //
   // Summary:
   //    Gets the current settings of the de-interlacer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetDeInterlacerStreamSettings
      (
      uint64_t& out_rui64Timestamp,                                  // Indicates the time that the de-interlacer
                                                                     // stream settings were activated.    
      SMvDeInterlacerStreamSettings& io_rsDeInterlacerStreamSettings // Structure that receives the de-interlacer
                                                                     // stream settings. 
      ) = 0;

   //
   // Summary:
   //    Modifies the current settings of the de-interlacer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //
   virtual HRESULT __stdcall SetDeInterlacerStreamSettings
      (
      uint64_t in_ui64Timestamp,                                        // Indicates the time that the modifications
                                                                        // are to be made.
      const SMvDeInterlacerStreamSettings& in_rsTransformStreamSettings	// Structure of the de-interlacer stream settings. 
      ) = 0;

   //
   // Summary:
   //    Gets the input node currently bound to the de-interlacer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetInputNode
      (
      uint64_t& out_rui64Timestamp, // Indicates the time that the node was activated.
      IMvNode** out_ppIInputNode    // Pointer that receives the input node interface. 
      ) = 0;

   //
   // Summary:
   //    Modifies the input node currently bound to the de-interlacer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //    - The new input node must have the same resolution and same memory location as the old input node.
   //
   virtual HRESULT __stdcall SetInputNode
      (
      uint64_t in_ui64Timestamp, // Indicates the time that the modifications are to be made.
      IMvNode* in_pIInputNode    // Pointer to the new input node interface. The pointer will be used at the time
                                 // specified in in_ui64Timestamp.
      ) = 0;

   //
   // Summary:
   //    Gets the output node currently bound to the de-interlacer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetOutputNode
      (
      uint64_t& out_rui64Timestamp, // Indicates the time that the node was activated.
      IMvNode** out_ppIOutputNode   // Pointer that receives the output node interface. 
      ) = 0;

   //
   // Summary:
   //    Modifies the output node currently bound to the de-interlacer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //    - The new output node must have the same resolution and same memory location as the old output node.
   //
   virtual HRESULT __stdcall SetOutputNode
      (
      uint64_t in_ui64Timestamp, // Indicates the time that the modification are to be made.
      IMvNode* in_pIOutputNode   // Pointer to the new output node interface. The pointer will be used at the time
                                 // specified in in_ui64Timestamp. This parameter can be NULL.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents a mixer stream in a workflow topology. 
// Remarks:
//    - This interface is used for video compositing and for audio and VANC selection.
//    - Both the input and output of this stream are nodes.
//    - The mixer stream can have multiple input nodes.
//    - This interface can be configured using keyframes based on a time stamp or can be queried for specific
//      information about the mixer stream.
//    - The mixer stream has a maximum of 62 layers.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvMixerStream : public IMvStream
{
   //
   // Summary:
   //    Gets the current settings of the mixer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //
   virtual HRESULT __stdcall GetMixerStreamSettings
      (
      uint64_t& out_rui64Timestamp,                     // Indicates the time that the mixer stream settings were activated.
      SMvMixerStreamSettings& io_rsMixerStreamSettings  // Structure that receives the mixer stream settings. 
      ) = 0;

   //
   // Summary:
   //    Modifies the current settings of the mixer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //
   virtual HRESULT __stdcall SetMixerStreamSettings
      (
      uint64_t in_ui64Timestamp,                               // Indicates the time that the modifications are to be made.
      const SMvMixerStreamSettings& in_krsMixerStreamSettings  // Structure of the mixer stream settings.
      ) = 0;

   //
   // Summary:
   //    Gets the input node(s) currently bound to the mixer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //    - The mixer stream has a maximum of 62 layers.
   //
   virtual HRESULT __stdcall GetInputNodes
      (
      uint64_t& out_rui64Timestamp,  // Indicates the time that the node was activated.
      IMvNode*  out_apIInputNodes[], // Pointer that receives the array of the input node interfaces.
      uint32_t& io_rui32NodesCount   // Indicates the number of input node interfaces returned in out_apIInputNodes.
      ) = 0;

   //
   // Summary:
   //    Modifies the input node(s) currently bound to the mixer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //    - The mixer stream has a maximum of 62 layers.
   //
   virtual HRESULT __stdcall SetInputNodes
      (
      uint64_t	in_ui64Timestamp,          // Indicates the time that the modifications are to be made.
      IMvNode* in_apIInputNodes[],        // Pointer to the array of the new input node interfaces. The pointer will
                                          // be used at the time specified in in_ui64Timestamp.
      uint32_t	in_ui32NodesCount          // Indicates the number of input node interfaces in in_apIInputNodes.
      ) = 0;

   //
   // Summary:
   //    Gets the settings for the input node(s) currently bound to the mixer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //    - The mixer stream has a maximum of 62 layers.
   //
   virtual HRESULT __stdcall GetInputNodesSettings
      (
      uint64_t& out_rui64Timestamp,								// Indicates the time that the node was activated.
      SMvMixerStreamNodeSettings out_asInputNodesSettings[],	// Pointer to the array of structures that receives the
                                                               // input node(s) settings.
      uint32_t& io_rui32NodesCount								// Indicates the number of input node settings returned in
                                                         // out_asInputNodesSettings.
      ) = 0;

   //
   // Summary:
   //    Modifies the current settings of the input node(s) bound to the mixer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //    - The mixer stream has a maximum of 62 layers.
   //
   virtual HRESULT __stdcall SetInputNodesSettings
      (
      uint64_t in_ui64Timestamp,                                     // Indicates the time that the modifications are
                                                                     // to be made.
      const SMvMixerStreamNodeSettings in_asInputNodesSettings[],    // Pointer to the array of structures of the new 
                                                                     // input node(s) settings.
      uint32_t in_ui32NodesCount                                     // Indicates the number of input node settings in
                                                                     // in_asInputNodesSettings.
      ) = 0;

   //
   // Summary:
   //    Gets the output node currently bound to the mixer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //
   virtual HRESULT __stdcall GetOutputNode
      (
      uint64_t& out_rui64Timestamp, // Indicates the time that the node was activated.
      IMvNode** out_ppIOutputNode   // Pointer that receives the output node interface. 
      ) = 0;

   //
   // Summary:
   //    Modifies the output node currently bound to the mixer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //
   virtual HRESULT __stdcall SetOutputNode
      (
      uint64_t in_ui64Timestamp,    // Indicates the time that the modifications are to be made.
      IMvNode* in_pIOutputNode      // Pointer to the new output node interface. The pointer will be used at the
                                    // time specified in in_ui64Timestamp. This parameter can be NULL.
      ) = 0;

   //
   // Summary:
   //    Gets the background node currently bound to the mixer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //
   virtual HRESULT __stdcall GetBackgroundNode
      (
      uint64_t& out_rui64Timestamp,   // Indicates the time that the node was activated.
      IMvNode** out_ppIBackgroundNode // Pointer that receives the background node interface. 
      ) = 0;

   //
   // Summary:
   //    Modifies the background node currently bound to the mixer stream.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - This value is changed on a keyframe basis.
   //
   virtual HRESULT __stdcall SetBackgroundNode
      (
      uint64_t in_ui64Timestamp,       // Indicates the time that the modifications are to be made.
      IMvNode* in_pIBackgroundNode     // Pointer to the new background node interface. The pointer will be used at 
                                       // the time specified in in_ui64Timestamp.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates the streams in the topology. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvStreamsEnumerator : public IUnknown
{
   //
   // Summary:
   //    Updates and resets the internal list of stream interfaces.
   // Description:
   //    The internal list of stream interfaces is updated with the most recent values on the card
   //    and the internal pointer is reset so that the next call to IMvStreamsEnumerator::Next returns the
   //    first stream interface in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Reset() = 0;

   //
   // Summary:
   //    Gets the next stream interface.
   // Description:
   //	 The next stream interface is retrieved from the internal list of stream interfaces.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Next
      (
      IMvStream** out_ppIStream  // Pointer that receives the next stream interface.
      ) = 0;

   //
   // Summary:
   //    Skips a given number of stream interfaces.
   // Description:
   //    The internal pointer is changed so that the next call to IMvStreamsEnumerator::Next skips a
   //    given number of stream interfaces in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Skip
      (
      uint32_t in_ui32Count   // Number of stream interfaces to skip.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents a card topology and is used to interact with a card's watchdog and default state. 
// Remarks:
//    - It only contains card nodes and hardware items, such as input streams, output streams, de-interlacer
//      streams, transform streams, and mixer streams.
//    - To obtain access to a card topology, the user application can query the system topology interface (IMvSystemTopology)
//      for IID_IMvTopology using the IUnknown::QueryInterface() method to obtain the IMvTopology interface.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvTopology : public IUnknown
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
   //    Creates an input stream in the topology on the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateInputStream
      (
      const char in_szName[32],                             // Indicates the name of the input stream to create.
      IMvVideoInputConnector* in_pIVideoInputConnector,     // Pointer to the video input connector interface.
      IMvAudioInputConnector* in_apIAudioInputConnectors[], // Pointer to the array of audio input connector interfaces.
      uint32_t in_ui32AudioInputConnectorsCount,            // Indicates the number of audio input connectors.
      IMvNode* in_pIOutputNode,                             // Pointer to the node interface that receives the audio,
                                                            // video, and VANC data. This parameter can be NULL.
      const SMvResolutionInfo& in_krsResInfo,               // Structure of the resolution settings of the input stream. 
      const SMvInputStreamSettings& in_krsStreamSettings,   // Structure of the input stream settings.
      IMvInputStream **out_ppIInputStream                   // Pointer that receives the created input stream
                                                            // interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates an input stream using SdiIp connector(s) in the topology on the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateInputStreamSdiIp
      (
      const char * in_kszName,                              // Indicates the name of the input stream to create.
      IMvConnector* in_pISdiIpInputConnectors[],            // Pointer to the array of SdiIp video input connector interfaces.
      IMvConnector* in_pISdiIpAlphaInputConnectors[],       // For future usage. For now, always send NULL.
      uint32_t in_ui32ConnectorsCount,                      // Indicates the number of SdiIp video input connectors.
      IMvConnector* in_apIAudioInputConnectors[],           // Pointer to the array of audio input connector interfaces.
      uint32_t in_ui32AudioInputConnectorsCount,            // Indicates the number of audio input connectors.
      IMvNode* in_pIOutputNode,                             // Pointer to the node interface that receives the audio,
                                                            // video, and VANC data. This parameter can be NULL.
      const SMvResolutionInfo & in_krsResolution,           // Structure of the resolution settings of the input stream. 
      const SMvInputStreamSettings& in_krsStreamSettings,   // Structure of the input stream settings.
      IMvInputStream **out_ppIInputStream                   // Pointer that receives the created input stream
                                                            // interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates an input stream in the topology of a card with the added ability of passing multiple
   //    input connectors to support UHD resolutions.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateInputStreamEx
      (
      const char * in_kszName,                              // Indicates the name of the input stream to create.
      IMvVideoInputConnector* in_pIVideoInputConnectors[],  // Pointer to the array of video input connector interfaces.
      uint32_t in_ui32VideoConnectorsCount,                 // Indicates the number of video input connectors.
      IMvAudioInputConnector* in_apIAudioInputConnectors[], // Pointer to the array of audio input connector interfaces.
      uint32_t in_ui32AudioInputConnectorsCount,            // Indicates the number of audio input connectors.
      IMvNode* in_pIOutputNode,                             // Pointer to the node interface that receives the audio,
                                                            // video, and VANC data. This parameter can be NULL.
      const SMvResolutionInfo& in_krsResInfo,               // Structure of the resolution settings of the input stream.
      const SMvInputStreamSettings& in_krsStreamSettings,   // Structure of the input stream settings.
      IMvInputStream **out_ppIInputStream                   // Pointer that receives the created input stream
                                                            // interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates an output stream in the topology on the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //   
   virtual HRESULT __stdcall CreateOutputStream
      (
      const char in_szName[32],                             // Indicates the name of the output stream to create.
      IMvNode* in_pIInputNode,                              // Pointer to the input node interface of the output stream.
                                                            // This parameter can be NULL.
      const SMvResolutionInfo& in_krsResInfo,               // Structure of the resolution settings of the output stream.
      const SMvOutputStreamSettings& in_krsStreamSettings,  //  Structure of the output stream settings.
      IMvVideoOutputConnector* in_pIVideoOutputConnector,   // Pointer to video output connector interface.
      IMvOutputStream **out_ppIOutputStream                 // Pointer that receives the created output stream
                                                            // interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates an output stream using Sdi connector(s) in the topology on the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //   
   virtual HRESULT __stdcall CreateOutputStreamSdi
      (
      const char * in_kszName,                              // Indicates the name of the output stream to create.
      IMvNode    * in_pIInputNode,                          // Pointer to the input node interface of the output stream.
                                                            // This parameter can be NULL.
      const SMvResolutionInfo & in_krsResolution,           // Structure of the resolution settings of the output stream.
      const SMvOutputStreamSettings & in_krsStreamSettings, // Structure of the output stream settings.
      IMvConnector * in_pISdiOutputConnectors[],            // Pointer to the array of Sdi video Output connector interfaces.
      IMvConnector * in_pAlphaOutputConnectors[],           // Pointer to the array of Sdi alpha Output connector interfaces.
                                                            // Use IMvVideoOutputConnector::GetAssociatedAlphaConnector()
                                                            // with the connectors of in_pISdiOutputConnectors to
                                                            // determine the connector to use in this parameter.
      uint32_t in_ui32ConnectorsCount,                      // Indicates the number of Sdi video output connectors.
      IMvOutputStream ** out_ppIOutputStream                // Pointer that receives the created output stream
                                                            // interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates an output stream using SdiIp connector(s) in the topology on the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //   
   virtual HRESULT __stdcall CreateOutputStreamSdiIp
      (
      const char * in_kszName,                              // Indicates the name of the output stream to create.
      IMvNode    * in_pIInputNode,                          // Pointer to the input node interface of the output stream.
                                                            // This parameter can be NULL.
      const SMvResolutionInfo & in_krsResolution,           // Structure of the resolution settings of the output stream.
      const SMvOutputStreamSettings & in_krsStreamSettings, // Structure of the output stream settings.
      IMvConnector * in_pISdiIpOutputConnectors[],          // Pointer to the array of SdiIp video Output connector interfaces.
      IMvConnector * in_pSdiIpAlphaOutputConnectors[],      // Pointer to the array of SdiIp alpha Output connector interfaces.
                                                            // Use IMvSdiIpOutputConnector::GetAssociatedAlphaConnector() 
                                                            // with the connectors of in_pISdiIpOutputConnectors to
                                                            // determine the connector to use in this parameter.
      uint32_t in_ui32ConnectorsCount,                      // Indicates the number of SdiIp video output connectors.
      IMvOutputStream ** out_ppIOutputStream                // Pointer that receives the created output stream
                                                            // interface, if the method is completed successfully.
      ) = 0;
   
   //
   // Summary:
   //    Creates a transform stream in the topology on the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - On buffer-based hardware, such as X.mio2 or DSX LE3, frame rate changes in transform streams that require
   //      3:2 pulldown or reverse 3:2 pulldown are not supported.
   //    - On buffer-based hardware, the transform stream will copy the VANC packets from the input node to the output
   //      node if both nodes have the same resolution.
   //
   virtual HRESULT __stdcall CreateTransformStream
      (
      const char in_szName[32],                                   // Indicates the name of the transform stream to create.
      IMvNode* in_pIInputNode,                                    // Pointer to the input node interface of the
                                                                  // transform stream.
      IMvNode* in_pIOutputNode,                                   // Pointer to the output node interface of the 
                                                                  // transform stream. This parameter can be NULL.
      const SMvTransformStreamSettings& in_rsTransformStreamSettings,   // Structure of the transform stream settings.
      IMvTransformStream** out_ppIStream                          // Pointer that receives the created transform 
                                                                  // stream interface, if the method is completed
                                                                  // successfully.
      ) = 0;

   //
   // Summary:
   //    Creates an output stream in the topology of a card with the added ability of passing multiple
   //    output connectors to support UHD resolutions.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //   
   virtual HRESULT __stdcall CreateOutputStreamEx
      (
      const char * in_kszName,                                 // Indicates the name of the output stream to create.
      IMvNode* in_pIInputNode,                                 // Pointer to the input node interface of the output stream.
                                                               // This parameter can be NULL.
      const SMvResolutionInfo& in_krsResInfo,                  // Structure of the resolution settings of the output stream.
      const SMvOutputStreamSettings& in_krsStreamSettings,     // Structure of the output stream settings.
      IMvVideoOutputConnector* in_pIVideoOutputConnectors[],   // Pointer to the array of video output connector interfaces.
      uint32_t in_ui32VideoConnectorsCount,                    // Indicates the number of video output connectors.
      IMvOutputStream **out_ppIOutputStream                    // Pointer that receives the created output stream
                                                               // interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates a mixer stream in the topology on the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateMixerStream
      (
      const char in_szName[32],                                // Indicates the name of the mixer stream to create. 
      IMvNode* in_apIInputNodes[],                             // Pointer to the array of input node interfaces of the
                                                               // mixer stream. This parameter can be NULL
      const SMvMixerStreamNodeSettings in_asMixerNodesSettings[],    // Array of settings for the input nodes of the
                                                               // mixer stream.
      uint32_t in_ui32InputNodesCount,                         // Indicates the number of elements in in_apIInputNodes 
                                                               // and in_asMixerNodesSettings of the mixer stream.
      IMvNode* in_pIOutputNode,                                // Pointer to the output node interface of the mixer stream.
                                                               // This parameter can be NULL.
      IMvNode* in_pIBackgroundNode,                            // Pointer to the background node interface of the mixer stream.
                                                               // This parameter can be NULL.
      const SMvMixerStreamSettings& in_rsMixerStreamSettings,        // Structure of the mixer stream settings.
      IMvMixerStream** out_ppIStream                           // Pointer that receives the created mixer stream
                                                               // interface, if the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates a de-interlacer stream in the topology on the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - Supported on hardware using the software MCE.
   //
   virtual HRESULT __stdcall CreateDeInterlacerStream
      (
      const char in_szName[32],              // Indicates the name of the de-interlacer stream to create.
      IMvNode* in_pIInputNode,               // Pointer to the input node interface of the de-interlacer stream.
      IMvNode* in_pIOutputNode,              // Pointer to the output node interface of the de-interlacer stream.
                                             // This parameter can be NULL.
      const SMvDeInterlacerStreamSettings& in_rsDeInterlacerStreamSettings,// Structure of the de-interlacer stream settings.
      IMvDeInterlacerStream** out_ppIStream  // Pointer that receives the created de-interlacer stream interface, if
                                             // the method is completed successfully.
      ) = 0;

   //
   // Summary:
   //    Creates a node in the topology on the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The maximum number of nodes that can be allocated in all topologies on a card is 64.
   //
   virtual HRESULT __stdcall CreateNode
      (
      const SMvNodeSettings& in_rsNodeSettings,       // Structure of the permanent node settings.
      const SMvNodeSettingsVideo* in_psVideoSettings, // Pointer to the permanent node video settings.
      const SMvNodeSettingsAudio* in_psAudioSettings, // Pointer to the permanent node audio settings.
      const SMvNodeSettingsVanc* in_psVancSettings,   // Pointer to the permanent node VANC settings.
      IMvNode** out_ppINode                           // Pointer that receives the created node interface, if the
                                                      // method is completed successfully.
      ) = 0;
      
   //
   // Summary:
   //    Creates an alias node in the topology on the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The maximum number of nodes that can be allocated in all topologies on a card is 64.
   //
   virtual HRESULT __stdcall CreateAliasNode
      (
      const char   in_kszName[32],             // Indicate the name of the node to create.
      IMvNode*     in_pIReferenceNode,         // Pointer to the reference node.
      IMvNode**    out_ppINode                 // Pointer that receives the created node interface, if the
                                               // method is completed successfully.
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
                                                      // currently in the topology.
      ) = 0;

   //
   // Summary:
   //    Creates an enumerator listing all nodes in the topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateNodesEnumerator
      (
      IMvNodesEnumerator** out_ppINodesEnumerator  // Pointer that receives an enumerator listing all nodes in the topology.
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
   //    Gets the current topology name.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetName
      (
      char* io_szName,                    // An array of characters that will receive the name of the topology.
      uint32_t in_ui32NbOfDestCharacters  // Indicates the number of characters in io_szName.
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
   //      topology exists before calling any method from it.
   //	   Otherwise, if the topology no longer exists, an error message will be returned.
   //
   virtual bool __stdcall StillExists() = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates the topologies on the card. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvTopologiesEnumerator : public IUnknown
{
   //
   // Summary:
   //    Updates and resets the internal list of topology interfaces.
   // Description:
   //    The internal list of topology interfaces is updated with the most recent values on the card
   //    and the internal pointer is reset so that the next call to IMvTopologiesEnumerator::Next returns the
   //    first topology interface in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Reset() = 0;

   //
   // Summary:
   //    Gets the next topology interface.
   // Description:
   //	 The next topology interface is retrieved from the internal list of topology interfaces.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Next
      (
      IMvTopology** out_ppITopology // Pointer that receives the next topology interface.
      ) = 0;

   //
   // Summary:
   //    Skips a given number of topology interfaces.
   // Description:
   //    The internal pointer is changed so that the next call to IMvTopologiesEnumerator::Next skips a
   //    given number of topology interfaces in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Skip
      (
      uint32_t in_ui32Count   // Number of topology interfaces to skip.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to configure all settings related to a specific Matrox hardware profile. 
// Remarks:
//    - This interface is provided by the IMvSystemConfiguration interface. 
//    - This interface can be used to enumerate or acquire the different input and output streams available for this
//      hardware profile and to manage the stored topologies.
// Note:
//    <sup>*</sup> Not supported on the Matrox DSX LE3 card.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvCardConfiguration : public IUnknown
{


   //
   // Summary:
   //    Creates an enumerator listing all SDI video input connectors for the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateSdiVideoInputConnectorsEnumerator
      (
      IMvSdiVideoInputConnectorsEnumerator** out_ppISdiVideoInputConnectorsEnumerator  // Pointer that receives the SDI
                                                                                       // video input connectors
                                                                                       // enumerator interface.
      ) = 0;

   //
   // Summary:
   //    Creates an enumerator listing all SDI video output connectors for the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateSdiVideoOutputConnectorsEnumerator
      (
      IMvSdiVideoOutputConnectorsEnumerator** out_ppISdiVideoOutputConnectorsEnumerator   // Pointer that receives the
                                                                                          // SDI video output connectors
                                                                                          // enumerator interface.
      ) = 0;

   //
   // Summary:
   //    Creates an enumerator listing all topologies for the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateTopologiesEnumerator
      (
      IMvTopologiesEnumerator** out_ppITopologiesEnumerator // Pointer that receives the topology enumerator interface.
      ) = 0;

   //
   // Summary:
   //    Creates an enumerator listing all AES/EBU audio input pairs for the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateAesEbuAudioInputPairConnectorsEnumerator
      (
      IMvAesEbuAudioInputPairConnectorsEnumerator** out_ppIConnectorsEnumerator  // Pointer that receives the AES/EBU
                                                                                 // audio input pair connectors
                                                                                 // enumerator interface.
      ) = 0;

   //
   // Summary:
   //    Creates an enumerator listing all AES/EBU audio output pairs for the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateAesEbuAudioOutputPairConnectorsEnumerator
      (
      IMvAesEbuAudioOutputPairConnectorsEnumerator** out_ppIConnectorsEnumerator // Pointer that receives the AES/EBU
                                                                                 // audio output pair connector
                                                                                 // enumerator interface.
      ) = 0;

   //
   // Summary:
   //    Creates an enumerator listing all the system clocks for the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateSystemClockEnumerator
      (
      IMvSystemClockEnumerator ** out_ppIEnumerator   // Pointer that receives the clock enumerator interface.
      ) = 0;

   //
   // Summary:
   //    Creates a new rendering system clock for the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateRenderingClock
      (
      const char      * in_kszName,                // Pointer to the name of the newly created rendering system clock.
      uint32_t          in_ui32ClockSpeed,         // Target speed of the rendering clock. The value cannot be zero. 
                                                   // The accepted values are 1, 2, 4, and 8 times the speed of the genlock clock.
      IMvSystemClock ** out_ppINewRenderingClock   // Pointer that receives the rendering system clock interface.
      ) = 0;

   //
   // Summary:
   //    Creates a new topology for the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The maximum number of nodes that can be allocated in all topologies on a card is 64.
   //
   virtual HRESULT __stdcall CreateTopology
      (
      const char* in_kszName,       // Pointer to the name of the newly created topology.
      IMvTopology** out_ppITopology // Pointer that receives the topology interface for the card.
      ) = 0;

   //
   // Summary:
   //    Adds a topology to the card's default state.<sup>*</sup>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Note:
   //    <sup>*</sup> Not supported on the Matrox DSX LE3 card.
   //
   virtual HRESULT __stdcall AddTopologyToDefaultState
      (
      IMvTopology* in_pITopology // Pointer to the topology interface to add a topology to the card's default state.
      ) = 0;

   //
   // Summary:
   //    Removes a topology from the card's default state.<sup>*</sup>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Note:
   //    <sup>*</sup> Not supported on the Matrox DSX LE3 card.
   //
   virtual HRESULT __stdcall RemoveTopologyFromDefaultState
      (
      IMvTopology* in_pITopology // Pointer to the topology interface that allows a topology to be removed from the
                                 // card's default state.
      ) = 0;

   //
   // Summary:
   //    Gets the genlock configuration for the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetGenlockConfiguration
      (
      IMvGenlockConfiguration** out_ppIGenlockConfiguration // Pointer that receives the genlock configuration
                                                            // interface for the card.
      ) = 0;

   //
   // Summary:
   //    Creates a watchdog for the card.<sup>*</sup>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Note:
   //    <sup>*</sup> Not supported on the Matrox DSX LE3 card.
   //
   virtual HRESULT __stdcall CreateWatchdog
      (
      const char* in_kszName,       // Pointer to the name of the newly created watchdog.
      IMvWatchdog** out_ppIWatchdog // Pointer that receives the watchdog interface for the card.
      ) = 0;

   //
   // Summary:
   //    Adds a watchdog to the card's default state.<sup>*</sup>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Note:
   //    <sup>*</sup> Not supported on the Matrox DSX LE3 card.
   //
   virtual HRESULT __stdcall AddWatchdogToDefaultState
      (
      IMvWatchdog* in_pIWatchdog // Pointer to the watchdog interface to add a watchdog to the card's default state.
      ) = 0;

   //
   // Summary:
   //    Removes a watchdog from the card's default state.<sup>*</sup>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Note:
   //    <sup>*</sup> Not supported on the Matrox DSX LE3 card.
   //
   virtual HRESULT __stdcall RemoveWatchdogFromDefaultState
      (
      IMvWatchdog* in_pIWatchdog // Pointer to the watchdog interface that allows a watchdog to be removed from the
                                 // card's default state.
      ) = 0;

   //
   // Summary:
   //    Creates an enumerator listing all watchdogs for the card.<sup>*</sup>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Note:
   //    <sup>*</sup> Not supported on the Matrox DSX LE3 card.
   //
   virtual HRESULT __stdcall CreateWatchdogsEnumerator
      (
      IMvWatchdogsEnumerator** out_ppIWatchdogsEnumerator // Pointer that receives the watchdog enumerator interface.
      ) = 0;

   //
   // Summary:
   //    Saves a node's content to the card's permanent memory.<sup>*</sup>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Note:
   //    <sup>*</sup> Not supported on the Matrox DSX LE3 card.
   //
   virtual HRESULT __stdcall SaveNodeContentToPermanentMemory
      (
      IMvNode* in_pINode,              // Pointer to the node interface that allows node content to be saved to the
                                       // card's permanent memory.
      SMvNodeContent& in_rsNodeContent	// Structure of the node content that allows an image from a node to be saved to
                                       // the card's permanent memory.
      ) = 0;

   //
   // Summary:
   //    Removes a node's content from the card's permanent memory.<sup>*</sup>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Note:
   //    <sup>*</sup> Not supported on the Matrox DSX LE3 card.
   //
   virtual HRESULT __stdcall RemoveNodeContentFromPermanentMemory
      (
      IMvNode* in_pINode   // Pointer to the node interface that allows the node content to be removed from the card's
                           // permanent memory.
      ) = 0;

   //
   // Summary:
   //    Saves all changes to the card's permanent memory.<sup>*</sup>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Note:
   //    <sup>*</sup> Not supported on the Matrox DSX LE3 card.
   //
   virtual HRESULT __stdcall SaveDefaultsToPermanentMemory
      (
      ) = 0;

   //
   // Summary:
   //    Clears the elements from the card's default state and the card's permanent memory.<sup>*</sup>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Note:
   //    <sup>*</sup> Not supported on the Matrox DSX LE3 card.
   //
   virtual HRESULT __stdcall ClearDefaultsAndPermanentMemory
      (
      ) = 0;

   //
   // Summary:
   //    Gets the error notification for the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetErrorNotification
      (
      IMvErrorNotification** out_ppIErrorNotification // Pointer that receives the error notification interface for
                                                      // the card.
      ) = 0;

   //
   // Summary:
   //    Gets the event notification for the card.<sup>*</sup>
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Note:
   //    <sup>*</sup> Not supported on the Matrox DSX LE3 card.
   //
   virtual HRESULT __stdcall GetEventNotification
      (
      IMvEventNotification** out_ppIEventNotification // Pointer that receives the event notification interface for
                                                      // the card.
      ) = 0;

   //
   // Summary:
   //    Gets the temperature sensor notification for the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The notification indicates that a temperature sensor on the card is overheating.
   //      As a precaution, the application allows a cooling period for the card.
   //
   virtual HRESULT __stdcall GetTemperatureNotification
      (
      IMvTemperatureNotification** out_ppITemperatureNotification // Pointer that receives the temperature sensor 
                                                                  // notification interface for the card.
      ) = 0;

   //
   // Summary:
   //    Gets the number of temperature sensors on the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // 
   virtual HRESULT __stdcall GetTemperatureSensorCount
	   (
	   uint32_t& out_rui32Count // Receives the number of temperature sensors on the card.
	   ) = 0;

   //
   // Summary:
   //    Gets the card's temperature sensor information.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // 
   virtual HRESULT __stdcall GetTemperatureSensorInfo
      (
      SMvTemperatureInformation out_asTempSensorInfo[],  // Array containing information about the card's temperature sensor.
      uint32_t in_ui32Count      // Number of elements in the array pointed to by out_asTempSensorInfo.
      ) = 0;

   //
   // Summary:
   //    Gets the number of hardware modules to upgrade on the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // 
   virtual HRESULT __stdcall GetCardInformationCount
      (
      uint32_t& out_rui32Count // Receives the number of hardware modules to upgrade.
      ) = 0;

   //
   // Summary:
   //    Gets a hardware module's general information so that it can be upgraded.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // 
   virtual HRESULT __stdcall GetCardInformation
      (
      SMvGeneralHardwareInformation* io_psGeneralHardwareInformation, // Pointer to the structure that receives the 
                                                                      // module's general hardware information to 
                                                                      // upgrade on the card.
      uint32_t                       in_ui32Index  // Index of the hardware module to upgrade. The in_ui32Index
                                                   // parameter is a zero-based index with a maximum value of
                                                   // (out_rui32Count - 1). The value of the out_rui32Count parameter
                                                   // is obtained from IMvCardConfiguration::GetCardInformationCount().
      ) = 0;

   //
   // Summary:
   //    Retrieves the interface used to upgrade a card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // 
   virtual HRESULT __stdcall GetCardUpgradeInterface
      (
      IMvCardUpgrade** out_ppICardUpgrade, // Pointer that will be initialized with the IMvCardUpgrade interface pointer.
      uint32_t        in_ui32Index         // Index of the hardware module to upgrade. The in_ui32Index parameter is a 
                                           // zero-based index with a maximum value of (out_rui32Count - 1). The value 
                                           // of the out_rui32Count parameter is obtained from 
                                           // IMvCardConfiguration::GetCardInformationCount.
      ) = 0;

   //
   // Summary:
   //    Gets the time code configuration for the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetTimeCodeConfiguration
      (
      IMvTimeCodeConfiguration** out_ppITimeCodeConfiguration  // Pointer that receives the time code configuration 
                                                               // interface for the card.
      ) = 0;

   //
   // Summary:
   //    Creates an enumerator listing all SfpIp for the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateSfpIpEnumerator
      (
      IMvSfpIpEnumerator ** out_ppIEnum                        // Pointer that receives the
                                                               // SfpIp enumerator interface.
      ) = 0;

   //
   // Summary:
   //    Creates an enumerator listing all SdiIp video input connectors for the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateSdiIpInputConnectorsEnumerator
      (
      IMvSdiIpInputConnectorsEnumerator** out_ppISdiIpInputConnectorsEnumerator     // Pointer that receives the
                                                                                    // SdiIp input connectors
                                                                                    // enumerator interface.
      ) = 0;

   //
   // Summary:
   //    Creates an enumerator listing all SdiIp video output connectors for the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateSdiIpOutputConnectorsEnumerator
      (
      IMvSdiIpOutputConnectorsEnumerator** out_ppISdiIpOutputConnectorsEnumerator   // Pointer that receives the
                                                                                    // SdiIp output connectors
                                                                                    // enumerator interface.
      ) = 0;
      
   //
   // Summary:
   //    Gets the number of analog linear time code configurations.
   // Return value:
   //    - Number of available analog linear time code configurations.
   // 
   virtual uint32_t __stdcall GetALTCConfigurationCount() = 0;

   //
   // Summary:
   //    Gets an analog linear time code configuration.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetALTCConfiguration
      (
      uint32_t               in_ui32Index,             // Index of analog linear time code configurations. 
                                                       // The in_ui32Index parameter is a zero-based index. 
                                                       // The maximum index value is (count - 1), where 
                                                       // "count" is the value returned by 
                                                       // IMvCardConfiguration::GetALTCConfigurationCount().
      IMvALTCConfiguration** out_ppIALTCConfiguration  // Pointer that receives an analog linear time code 
                                                       // configuration interface.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary: 
//    Interface that gives access to the different card upgrade functions.
//    
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvCardUpgrade : public IUnknown
{
   //
   // Summary:
   //    Generates a Matrox Dongle Information File (.MDIF) that can be used to generate a Matrox Dongle Upgrade
   //    File (.MDUF). For Xmio2 Plus and DSX LE3 only.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // 
   virtual HRESULT __stdcall GenerateMDIF
      (
      wchar_t* in_pswzDirectory,          // Specifies the directory where the .MDIF is to be stored.
      wchar_t* out_pswzFilename,          // Provides the filename for the .MDIF.
      size_t   in_szFilenameSizeInWords   // Expresses the size of the .MDIF in terms of the number of characters in 
                                          // the filename.
      ) = 0;

   //
   // Summary:
   //    Upgrades the card using a Matrox Dongle Upgrade File (.MDUF). For Xmio2 Plus and DSX LE3 only.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Before performing the upgrade, the card must be set to its original factory default settings using 
   //      IMvCardUpgrade::ResetDongleToFactoryDefault().
   // 
   virtual HRESULT __stdcall UpgradeMDUF
      (
      wchar_t* in_pswzFilename   // Specifies the filename and directory where the .MDUF is located on the user's
                                 // hard drive.
      ) = 0;

   //
   // Summary:
   //    Resets the dongle to the factory default settings. For Xmio2 Plus and DSX LE3 only.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // 
   virtual HRESULT __stdcall ResetDongleToFactoryDefault() = 0;


   //
   // Summary:
   //    Gets the list size of the card upgrade. Supported only on cards with flash memory, such as X.mio3 and DSX LE4.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // 
   virtual HRESULT __stdcall GetProductUpgradesListSize
      (
      uint32_t *out_ui32UpgradeListSize   // Indicates the size of the list.
      ) = 0;

   //
   // Summary:
   //    Retrieves the strings corresponding to the card upgrade. Supported only on cards with flash memory, such as X.mio3 and DSX LE4.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // 
   virtual HRESULT __stdcall GetProductUpgradeElement
      (
      uint32_t in_ui32Index,              // Indicates the index of the card upgrade.
      char *out_pcProductUpgradeString    // Pointer to the card upgrade string.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary: 
//    Interface that controls the watchdogs on the card.
// Remarks:
//    - The watchdog feature is not supported on DSX LE3.    
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvWatchdog : public IUnknown
{
   //
   // Summary:
   //    Indicates whether or not a watchdog is still active on the card.
   // Return value:
   //    - bool: If true, the watchdog is still active on the card.
   //
   virtual bool __stdcall StillExists() = 0;

   //
   // Summary:
   //    Destroys a watchdog on the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall DestroyWatchdog() = 0;

   //
   // Summary:
   //    Sets a watchdog's settings.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetWatchdogSettings
      (
      SMvWatchdogSettings& in_rsSettings  // Structure of the watchdog settings.
      ) = 0;

   //
   // Summary:
   //    Gets a watchdog's settings.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetWatchdogSettings
      (
      SMvWatchdogSettings& io_rsSettings  // Structure that receives the current watchdog settings.
      ) = 0;

   //
   // Summary:
   //    Sets a watchdog's topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetWatchdogTopology
      (
      IMvTopology* in_pITopology // Pointer to the topology interface.
      ) = 0;

   //
   // Summary:
   //    Gets a watchdog's topology.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetWatchdogTopology
      (
      IMvTopology** out_ppITopology // Pointer that receives the topology interface.
      ) = 0;

   //
   // Summary:
   //    Creates a watchdog event on the card.
   // Remarks:
   //    - The recommended method to use is IMvWatchdog::SignalWatchdogPulseEvent() because it is cross-platform.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Note:
   //    - This method does not work in Linux.
   //
   virtual HRESULT __stdcall AcquireWatchdogPulseEvent(HANDLE& out_rhEvent) = 0;

   //
   // Summary:
   //    Deletes a watchdog event from the card.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall ReleaseWatchdogPulseEvent() = 0;

   //
   // Summary:
   //    Gets the name of a watchdog (for debugging purposes).
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetName
      (
      char* io_szName,  // An array of characters that will receive the name of the watchdog.
      uint32_t in_ui32NbOfDestCharacters  // Indicates the number of characters in io_szName.
      ) = 0;

   //
   // Summary:
   //    Signals a watchdog event on the card to prevent triggering a timeout.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // 
   virtual HRESULT __stdcall SignalWatchdogPulseEvent() = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides the callback notification of the DSX system clock. 
// Remarks:
//    - Use the IMvSystemClock interface to register and unregister the
//      IMvSystemClockNotificationCallback interface.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSystemClockNotificationCallback : public IUnknown
{
   //
   // Summary:
   //    Receives the DSX system clock notification.
   //
   virtual void __stdcall NotifyClock() = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary: 
//    Base interface used to interact with the different types of system clocks.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSystemClock : public IUnknown
{
   //
   // Summary:
   //    Gets the DSX system clock name.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //
   virtual HRESULT __stdcall GetName
      (
      char   * out_szName,                // An array of characters that will receive the name of the DSX system clock.
      uint32_t in_ui32NbOfDestCharacters  // Indicates the number of characters in out_szName.
      ) = 0;

   //
   // Summary:
   //    Destroys a system clock.
   // Remarks:
   //    - This method can only be used on a rendering or host clocks (including the Universal Clock).
   // 
   virtual HRESULT __stdcall Destroy() = 0;  

   //
   // Summary:
   //    Gets the type of DSX system clock.
   //
   virtual EMvSystemClockType __stdcall GetClockType() = 0;

   //
   // Summary:
   //    Gets a 64-bit system time value that is expressed in nanotime unites.
   // Remarks:
   //    - 1 nanotime unit is equivalent to 100 ns.
   // Return value:
   //    - System time.
   virtual uint64_t __stdcall GetTime() = 0;

   //
   // Summary:
   //    Registers the IMvSystemClockNotificationCallback interface to be called once at the specified 64-bit system time stamp value.    
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if a parameter is invalid.
   // Remarks:
   //    - The IUnknown::AddRef method of the in_pICallback parameter is called when the notification is registered to prevent 
   //      the object implementing the IMvSystemClockNotificationCallback interface from being destroyed. It is released automatically
   //      after the IMvSystemClockNotificationCallback interface is called.
   //
   virtual HRESULT __stdcall RegisterForNotification
      (
      uint64_t in_ui64NotificationTime,                     // Specifies the time at which the interface will be called. If the time has 
                                                            // already elapsed, the interface will be called at the earliest possible time.
      IMvSystemClockNotificationCallback * in_pICallback    // Pointer to the system clock notification callback interface.
      ) = 0;

   //
   // Summary:
   //    Registers the IMvSystemClockNotificationCallback interface to be called starting at the specified 64-bit system time stamp value, 
   //    and periodically at each video unit of the specified video resolution.    
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if a parameter is invalid.
   // Remarks:
   //    - The IUnknown::AddRef method of the in_pICallback parameter is called when the notification is registered to prevent 
   //      the object implementing the IMvSystemClockNotificationCallback interface from being destroyed. 
   //
   virtual HRESULT  __stdcall RegisterForPeriodicNotification
      (
      uint64_t in_ui64NotificationStartTime,       // Specifies the time at which the notification will start.
                                                   // If the time has already elapsed, the notification starts at the earliest
                                                   // possible time.
      const SMvResolutionInfo & in_rsMvResolution, // Specifies the video unit frequency at which in_pICallback is 
                                                   // called.  If this parameter is NULL, in_pICallback is called 
                                                   // at each clock tick (which is approximately a quarter of a video unit).
      IMvSystemClockNotificationCallback * in_pICallback // Pointer to the system clock notification callback interface that will be called periodically.
      ) = 0;

   //
   // Summary:
   //    Unregisters a previously registered IMvSystemClockNotificationCallback interface from being called periodically.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_PARAMETER, if the parameter is invalid.
   // Remarks:
   //    - The IUnknown::Release method of the in_pICallback parameter is called when the notification is unregistered to remove 
   //      the reference count added by IMvSystemClock::RegisterForPeriodicNotification. 
   //
   virtual HRESULT  __stdcall UnRegisterForPeriodicNotification
      (
      IMvSystemClockNotificationCallback * in_pICallback // Specifies the system clock notification callback interface to stop calling periodically.
      ) = 0;

};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary: 
//    Provides the user application with the method to access the card configuration interface associated with the genlock system clock.
//   
//////////////////////////////////////////////////////////////////////////////////
interface IMvSystemClockGenlock : public IUnknown
{
   //
   // Summary:
   //    Gets the card configuration interface associated with the genlock system clock.
   // Return value:
   //    - MV_E_INVALID_POINTER, if the pointer out_ppCardConfiguration is NULL.
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetCardConfig
      (
      IMvCardConfiguration ** out_ppCardConfiguration   // Pointer that receives the card configuration interface associated with the genlock system clock.
      ) = 0;

   //
   // Summary:
   //    Gets a 64-bit precision system time value that is expressed in nanotime unites.
   //    Available on X.mio3 and DSX.LE4. Please use this with care since it can affect 
   //    system performance. For example, do not use in a busy-loop.
   // Remarks:
   //    - 1 nanotime unit is equivalent to 100 ns.
   // Return value:
   //    - System time.
   virtual uint64_t __stdcall GetPrecisionTime() = 0;

};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary: 
//    Provides the user application with the method to access the input connector interface associated with the input system clock.
//   
//////////////////////////////////////////////////////////////////////////////////
interface IMvSystemClockInput : public IUnknown
{
   //
   // Summary:
   //    Gets the input connector interface associated with the input system clock.
   // Return value:
   //    - MV_E_INVALID_POINTER, if the pointer out_ppInputConnector is NULL.
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetConnector
      (
      IMvSdiVideoInputConnector ** out_ppInputConnector  // Pointer that receives the input connector interface associated with the input system clock.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary: 
//    Provides the user application with the methods to access the parameters of the rendering system clock.
//   
//////////////////////////////////////////////////////////////////////////////////
interface IMvSystemClockRendering : public IUnknown
{
   //
   // Summary:
   //    Gets the rendering system clock maximum tick frequency.
   // Return value:
   //    - Maximum tick frequency of the rendering system clock. 
   //
   virtual uint32_t __stdcall GetClockSpeed() = 0;

   //
   // Summary:
   //    Gets the card configuration interface associated with the rendering system clock.
   // Return value:
   //    - MV_E_INVALID_POINTER, if the pointer out_ppCardConfiguration is NULL.
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetCardConfig
      (
      IMvCardConfiguration ** out_ppCardConfiguration   // Pointer that receives the card configuration interface associated with the rendering system clock.
      ) = 0;
};  

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates the different DSX system clocks. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSystemClockEnumerator : public IUnknown
{
   //
   // Summary:
   //    Updates and resets the internal list of DSX system clock interfaces.
   // Description:
   //    The internal list of DSX system clock interfaces is updated with the most recent values in the system
   //    and the internal pointer is reset so that the next call to IMvSystemClockEnumerator::Next returns the
   //    first DSX system clock interface in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Reset() = 0;

   //
   // Summary:
   //    Gets the next DSX system clock interface.
   // Description:
   //	 The next DSX system clock interface is retrieved from the internal list of DSX system clock interfaces.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Next
      (
      IMvSystemClock ** out_ppIClock   // Pointer that receives the next DSX system clock interface.
      ) = 0;

   //
   // Summary:
   //    Skips a given number of DSX system clock interfaces.
   // Description:
   //    The internal pointer is changed so that the next call to IMvSystemClockEnumerator::Next skips a
   //    given number of DSX system clock interfaces in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Skip
      (
      uint32_t in_ui32Count   // Number of DSX system clock interfaces to skip.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary: 
//    Interface that implements the Flex Tunnel to DirectShow Manager.
// Remarks:
//	  Use this interface to create Flex tunnels and get existing Flex tunnels for the current DSX hardware profile.
//   
//////////////////////////////////////////////////////////////////////////////////
interface IMvFlexTunnelToDirectShowManager : public IUnknown
{
	//
	// Summary:
	//    Gets the number of Flex tunnels that exist for the current DSX hardware profile.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//
	virtual HRESULT __stdcall GetNumberofFlexTunnelsToDirectShow
		(
		unsigned long * out_pulNumberOfTunnelsToDirectShow // Pointer to the number of Flex tunnels that exist within 
                                                         // the current DSX hardware profile.
		) = 0;

	//
	// Summary:
	//    Gets the tunnel information of each Flex tunnel that exists for the current DSX hardware profile.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_OUT_OF_RANGE, if the index passed is greater than (out_pulNumberOfTunnelsToDirectShow - 1).
	//
	virtual HRESULT __stdcall GetFlexTunnelToDirectShowInfo
		(
		unsigned long in_ulIndex,  // Index of the Flex tunnel. <p>
                                 // The in_ulIndex parameter is a zero-based index with a maximum value
                                 // of (out_pulNumberOfTunnelsToDirectShow - 1).
                                 // The value of out_pulNumberOfTunnelsToDirectShow is obtained from 
                                 // IMvFlexTunnelToDirectShowManager::GetNumberofFlexTunnelsToDirectShow().
		SMvFlexTunnelToDirectShowDescription * out_psFlexTunnelToDirectShowDesc	// Pointer to the Flex Tunnel to
                                                                              // DirectShow structure describing the
                                                                              // Flex tunnel.
  		) = 0;

	//
	// Summary:
	//    Creates a Flex tunnel for the current DSX hardware profile.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_MAX_VALUE_REACHED, if the number of Flex tunnels exceeds 16 for the current DSX hardware profile.
	//    - MV_E_TUNNEL_ALREADY_EXISTS, if the Flex tunnel being created already exists.
	//    - MV_E_TUNNEL_LENGTH_TOO_SHORT, if the Flex tunnel length is too short.
	//    - MV_E_UNSUPPORTED_SURFACE_TYPE, if the surface type is not keMvSurfaceFormatYUYV422.
	//    - MV_E_UNSUPPORTED_COMPONENT_BIT_COUNT, if the resolution component bit count is not 8.
	//    - MV_E_UNSUPPORTED_AUDIO_CHANNEL_TYPE, if the audio channel type is not keChannelTypeStereo.
	// Remarks:
	//		
	virtual HRESULT __stdcall  CreateFlexTunnelToDirectshow
		(
		SMvFlexTunnelToDirectShowDescription * in_psFlexTunnelToDirectShowDesc,    // Pointer to the Flex Tunnel to
                                                                                 // DirectShow structure describing 
                                                                                 // the Flex tunnel to create.
		IMvFlexTunnelToDirectShow**    out_ppITunnel // Pointer that receives the Flex Tunnel to DirectShow
                                                   // interface created.
		) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary: 
//    Interface that implements the Flex Tunnel to DirectShow module.
// Description:
//	  The Flex Tunnel to DirectShow module provides video surfaces and audio sample buffers. Unlike other DSX buffers,
//	  Flex tunnel buffers become available again once they have been used and their time stamps have expired. A Flex
//   tunnel buffer expires when the current Flex system time is greater than or equal to the time stamp of the buffer
//   plus the tunnel length.
//	  That is,<p>
//	  Flex system time >= buffer time stamp + tunnel length <p>
//   For example, if the tunnel length is 30 and the current Flex system time is 1000, the first 30 consecutive calls to
//   GetBuffersFrame() with time stamps 1000, 1001, 1002, ... , 1029 will return immediately because all buffers are available.
//   The next call to GetBuffersFrame() for time stamp 1030 must wait for the buffer with time stamp 1000 to be
//	  returned to the Flex tunnel pool and for the time stamp to expire before it can be used at time stamp 1030.
//	  This causes GetBuffersFrame() to behave as a blocking method by blocking the return of frames until the buffers are
//	  available or until a timeout has occured. The same is true for GetBuffersFields().
// Remarks:
//    - Consecutive calls to GetBuffersFrame() or GetBuffersFields() must have consecutive time stamps.
//    - The time stamps of the buffers are given as parameters to the GetBuffersFrame() or GetBuffersFields() method.
//    - To stream properly, the time stamp used for the first call to GetBuffersFrame() or GetBuffersFields() must be
//      the current Flex system time.
//    - All subsequent calls must increment the time stamp by one frame.
//    - Buffers that have been used are returned to the Flex tunnel pool so that they can be used again.
//	
//////////////////////////////////////////////////////////////////////////////////
interface IMvFlexTunnelToDirectShow : public IUnknown
{
	//
	// Summary:
	//    Gets a video frame and the associated audio from the Flex tunnel.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_TIME_OUT, if the timeout elapsed while waiting for video surfaces and audio sample buffers.
	// Remarks:
	//    - Used for frame-based scan mode Flex tunnels.
	//    - Time stamp must be valid and close to the current Flex system time.   
	virtual HRESULT __stdcall GetBuffersFrame
		(
		uint64_t			     in_ui64TimeStamp,  // Time stamp of the video frame obtained from the Flex tunnel.               
		IMvSurface**       out_ppVideoBuffer,  // Pointer that receives the video frame.
		IMvAudioSamples**  out_ppAudioBuffer,  // Pointer that receives the audio associated to the video frame.
		unsigned long      in_ulNumberOfSamplesPerBuffer, // Number of audio samples in the buffer.
		unsigned long           in_ulTimeout   // Maximum time (in milliseconds) to wait for video surfaces and
                                             // audio sample buffers.
		) = 0;

	//
	// Summary:
	//    Gets two video fields and the associated audio from the Flex tunnel.
	// Return value:
	//    - MV_NOERROR, if completed successfully. 
	//    - MV_E_TIME_OUT, if the timeout elapsed while waiting for video surfaces and audio sample buffers.
	//    - MV_E_TUNNEL_SCANMODE_IS_FRAME_BASED, if the scan mode is frame-based instead of field-based.
	// Remarks:
	//    - Used for field-based scan mode Flex tunnels.
	//    - Time stamp must be valid and close to the current Flex system time. 
	virtual HRESULT __stdcall GetBuffersFields
		(
		uint64_t			       in_ui64TimeStamp, // Time stamp of the first field obtained from the Flex tunnel.
		IMvSurface**       out_ppVideoBufferF1, // Pointer that receives the first video field.
		IMvSurface**       out_ppVideoBufferF2, // Pointer that receives the second video field.
		IMvAudioSamples**  out_ppAudioBufferF1, // Pointer that receives the audio associated with the first video field.
		unsigned long      in_ulNumberOfSamplesForBufferF1,   // Number of audio samples in the buffer associated with 
                                                            // the first video field.
		IMvAudioSamples**  out_ppAudioBufferF2,   // Pointer that receives the audio associated with the second video field.
		unsigned long      in_ulNumberOfSamplesForBufferF2,   // Number of audio samples in the buffer associated with 
                                                            // the second video field.
		unsigned long             in_ulTimeout    // Maximum time (in milliseconds) to wait for video surfaces and audio 
                                                // sample buffers.
		) = 0;
};

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used by the Memory Manager to notify the user application that it requires a response.
// Remarks:
//    - This interface must be implemented by the user application.
//////////////////////////////////////////////////////////////////////////
interface IMvAsyncMemoryManagerObserver : public IUnknown
{

   //
   // Summary:
   //    Configures a target for the maximum amount of memory that the Memory Manager
   //    will allocate. 
   // Remarks:
   //    - This target may be surpassed in certain cases.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall AsyncMemoryMemoryNotify
      (
      SMvMemoryManagerNotification *in_pMMNotification   // Pointer to the structure that provides the action required by the Memory Manager.
      ) = 0;

};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary: 
//    Interface that configures the Memory Manager and retrieves its status.
//    
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvAsyncMemoryManagerConfigurator : public IUnknown
{

   //
   // Summary:
   //    Configures a target for the maximum amount of memory that the Memory Manager
   //    will allocate.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall ConfigureMemoryManager
      (
      SMvMemoryManagerConfiguration *in_pMMConfig  // Pointer to the structure containing the settings used to configure the Memory Manager.
      ) = 0;

   //
   // Summary:
   //    Configures the Memory Manager to call back in case of a problem.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetObserver
      (
      IMvAsyncMemoryManagerObserver *in_pIObserver // Pointer to the IMvAsyncMemoryManagerObserver interface.
      ) = 0;

   //
   // Summary:
   //    Gets the status of the Memory Manager (for debugging purposes).
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetAsyncMemoryManagerStatus
      (
      SMvMemoryManagerStatus *out_psMvMemoryManagerStatus   // Structure that receives the status of the Memory Manager.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary: 
//    Implemented by a module to allow an external observer to receive notifications each time 
//    a video surface or audio sample buffer (A/V content) is returned to an internal 
//    pool manager, such as the A/V Contents Pool Manager contained in the 
//    Flex File Reader or Flex File Writer.
//    
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvAVContentCompletionSubject : public IUnknown
{

   //////////////////////////////////////////////////////////////////////////
   //
   // Summary:
   //    Adds an IMvAVContentCompletionObserver on the A/V Content Pool Managers used by the subject, 
   //	 or by some of its components. This object will be notified each time A/V content 
   //    returns to the pool.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_FAIL, if an error occurred.
   //
   //////////////////////////////////////////////////////////////////////////
   virtual HRESULT __stdcall AddAvContentCompletionObserver
      (
      IMvAVContentCompletionObserver *in_pAvContentCompletionObserver
      ) = 0;

   //////////////////////////////////////////////////////////////////////////
   //
   // Summary:
   //    Removes an IMvAVContentCompletionObserver on the A/V Content Pool
   //    Managers used by the subject, or by some of its components. The removed 
   //    object must have been previously added using the
   //    AddAVContentCompletionObserver() method.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_FAIL, if an error occurred.
   //
   //////////////////////////////////////////////////////////////////////////
   virtual HRESULT __stdcall RemoveAvContentCompletionObserver
      (
      IMvAVContentCompletionObserver *in_pAvContentCompletionObserverToRemove
      ) = 0;
};


// Summary:
//    Interface used to transfer video data between DSX host memory surfaces and a display card's
//    memory.                                                                                    
interface IMvGpuTransfer : public IUnknown
{
   //
   // Summary:
   //    Creates an OpenGL texture that can receive video data from host memory.
   // Return value:
   //    - MV_NOERROR, if the texture was created successfully.
   //    - MV_E_UNSUPPORTED_SURFACE_FORMAT, if in_eTextureData contains an unsupported value.
   //    - MV_E_INVALID_POINTER, if the pointer out_pui64Texture is NULL.
   //    - MV_E_CREATESURFACE_FAILED, if the OpenGL texture creation failed.
   // Remarks:
   //    - To destroy the texture use IMvGpuTransfer::DestroyOpenGLTexture().
   //    - After calling this method the texture is bound to the current OpenGL context.
   //
  virtual HRESULT __stdcall CreateOpenGLTexture
      (
      EMvSurfaceFormat in_eTextureData,   // Indicates the type of data that will be used in the texture.  
                                             // <p>Only keMvSurfaceFormatYUYV422 8-bit, keMvSurfaceFormatYUAYVA4224 8-bit,  
                                             // and keMvSurfaceFormatARGBGraphic 8-bit can be used for the texture data.
      uint64_t       * out_pui64Texture   // Pointer that receives the OpenGL ID of the created texture. 
      ) = 0;

   //
   // Summary:
   //    Destroys an OpenGL texture that was created with IMvGpuTransfer::CreateOpenGLTexture().
   // Return value:
   //    - MV_NOERROR, if the texture was destroyed successfully.
   //    - MV_E_INVALID_GPU_TEXTURE, if the texture was not create with IMvGpuTransfer::CreateOpenGLTexture().
   //
  virtual HRESULT __stdcall DestroyOpenGLTexture
      (
      uint64_t in_ui64Texture    // Indicates the OpenGL ID of the texture to destroy.
      ) = 0;

   //
   // Summary:
   //    Creates a host surface pool manager that will be used to transfer video data between the host and the graphic
   //     card's texture.
   // Return value:
   //    - MV_NOERROR, if the pool and it's surfaces have been properly allocated.
   // Remarks:
   //    - The attributes of the surfaces to allocate are obtained from the resolution that was specified in 
   //      IMvFlexEngine::CreateGpuTransferInterface().
   //
  virtual HRESULT __stdcall CreateSurfacePool
      (
      const wchar_t *  in_wszPoolName,          // Pointer to the string that contains the name of the pool.
      unsigned long    in_ulThreadPoolPriority, // Priority of the pool manager waiting thread (used for internal processing).
      uint32_t         in_ui32InitialSize,      // Indicates the number of surfaces to allocate immediately.
      EMvSurfaceFormat in_eSurfaceFormat,       // Indicates the format of the surface to allocate. 
                                                   // <p>Only keMvSurfaceFormatYUYV422, keMvSurfaceFormatYUAYVA4224, 
                                                   // and keMvSurfaceFormatARGBGraphic can be used.
      IMvAVContentCompletionObserver * in_pICompletionObserver,   // Pointer to the IMvAVContentCompletionObserver 
                                                                     // interface.<p>Set this parameter to NULL if error
                                                                     // notification is not needed.<p>The object 
                                                                     // implementing the IMvAVContentCompletionObserver 
                                                                     // interface must not keep a reference on the pool 
                                                                     // object because it creates a circular dependency 
                                                                     // in COM resulting in memory leaks.  
      IMvAVContentPoolManager ** out_ppIAVContentPoolManager   // Pointer that receives the IMvAVContentPoolManager interface.
      ) = 0;

   //
   // Summary:
   //    Indicates whether or not a texture is ready to be used for OpenGL or Direct3D rendering.
   // Return value:
   //    - MV_NOERROR, if the texture is ready for rendering.
   //    - MV_E_NOT_READY_FOR_READ, if the texture is not ready for rendering.
   //
   virtual HRESULT __stdcall IsTextureReadyForRendering
      (
      uint64_t in_ui64Texture    // Indicates the OpenGL or Direct3D ID of the texture to check.
      ) = 0;

   //
   // Summary:
   //    Waits for a texture to be ready for OpenGL or Direct3D rendering.
   // Return value:
   //    - MV_NOERROR, if the texture is ready for rendering.
   //    - MV_E_TIMEOUT, if the texture is not ready after in_ui32Timeout expires.
   // Remarks:
   //    - The thread calling this method will sleep until the texture is ready.
   // 
   virtual HRESULT __stdcall WaitForTextureReadyForRendering
      (
      uint32_t in_ui32Timeout,   // Indicates the amount of time (in milliseconds) to wait for the texture to be ready
                                    // for OpenGL or Direct3D rendering.
      uint64_t in_ui64Texture    // Indicates the OpenGL or Direct3D ID of the texture to check.
      ) = 0;

   //
   // Summary:
   //    Delays the OpenGL or Direct3D rendering until the end of the host-to-GPU transfer.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_NOT_READY_FOR_READ, if the texture is not ready for rendering.
   //    - MV_E_INVALID_GPU_TEXTURE, if the texture has not been allocated in the GPU transfer module 
   //      (IMvGpuTransfer::CreateOpenGLTexture() or IMvGpuTransfer::CreateD3DTexture()).
   // Remarks:
   //    - Synchronizes the beginning of the rendering.
   //    - Call this method after the texture is ready for rendering (IMvGpuTransfer::IsTextureReadyForRendering()).
   //    - Call this method before ::glBegin().
   // 
   virtual HRESULT __stdcall AcquireTextureRenderingGate
      (
      uint64_t in_ui64Texture    // Indicates the OpenGL or Direct3D ID of the texture to synchronize.
      ) = 0;

   //
   // Summary:
   //    Delays the GPU-to-host transfer until the end of the OpenGL or Direct3D rendering.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_GPU_TEXTURE, if the texture has not been allocated in the GPU transfer module
   //      (IMvGpuTransfer::CreateOpenGLTexture() or IMvGpuTransfer::CreateD3DTexture()).
   // Remarks:
   //    - Synchronizes the end of the rendering.
   //    - Call this method after ::glEnd().
   //    - Call this method before IMvGpuTransfer::CopyOpenGLTextureToSurface() or IMvGpuTransfer::Copy3D3TextureToSurface().
   // 
   virtual HRESULT __stdcall ReleaseTextureRenderingGate
      (
      uint64_t in_ui64Texture    // Indicates the OpenGL or Direct3D ID of the texture to synchronize.
      ) = 0;

   //
   // Summary:
   //    Copies a video surface to an OpenGL texture.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_GPU_TEXTURE, if the texture has not been allocated in the GPU transfer module
   //      (IMvGpuTransfer::CreateOpenGLTexture()).
   //    - MV_E_INVALID_GPU_SURFACE, if the video surface has not been allocated in the GPU transfer module
   //      (IMvGpuTransfer::CreateOpenGLTexture()).
   // 
   virtual HRESULT __stdcall CopySurfaceToOpenGLTexture
      (
      IMvSurface * in_pBuffer,       // Pointer to the IMvSurface interface of the video surface to copy.
      uint64_t     in_ui64Texture    // Indicates the OpenGL ID of the texture to update.
      ) = 0;

   //
   // Summary:
   //    Copies an OpenGL texture to a video surface.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   //    - MV_E_INVALID_GPU_TEXTURE, if the texture has not been allocated in the GPU transfer module
   //      (IMvGpuTransfer::CreateOpenGLTexture()).
   //    - MV_E_INVALID_GPU_SURFACE, if the video surface has not been allocated in the GPU transfer module
   //      (IMvGpuTransfer::CreateOpenGLTexture()).
   // 
  virtual HRESULT __stdcall CopyOpenGLTextureToSurface
      (
      uint64_t     in_ui64Texture,  // Indicates the OpenGL ID of the texture to copy.
      IMvSurface * in_pBuffer       // Pointer to the IMvSurface interface of the video surface to update.
      ) = 0;

  //
  // Summary:
  //    Indicates whether the display card used for the Flex GPU Transfer module uses GPUDirect.
  // Return value:
  //    - GPUDirect mode or default mode.
  virtual EMvGPUTransferMode __stdcall GetGPUTransferMode() = 0;
  
  //
  // Summary:
  //    Indicates which rendering API is used to 3D rendering. 
  // Return value:
  //    - 3D rendering API.
  virtual EMvGPUTransferRenderingMode __stdcall GetGpuRenderingMode() = 0;

  //
  // Summary:
  //    Indicates the YUYV mapping in the ARGB texture to use. The first luma can be found in the red or the blue 
  //    component.
  // Return value:
  //    - Where is the firs luma value in the ARGB mapping.
  virtual EMvComponentSelection __stdcall GetComponentSelection() = 0;

  //
  // Summary:
  //    Creates a Direct3D texture that can receive video data from host memory. 
  // Return value:
  //    - MV_NOERROR, if the texture was created successfully.
  //    - MV_E_INVALID_POINTER, if the pointer out_ppD3DTexture is NULL.
  //    - MV_E_CREATESURFACE_FAILED, if the Direct3D texture creation failed.
  // Remarks:
  //    - The interface of the texture is ID3D11Texture2D.
  //    - To destroy the texture use IMvGpuTransfer::DestroyD3DTexture().
  //    - After calling this method the texture is bound to the current Direct3D device.
  //
  virtual HRESULT __stdcall CreateD3DTexture
     (
     EMvSurfaceFormat in_eTextureData,       // Indicates the type of data that will be used in the texture.  
                                             // <p>Only keMvSurfaceFormatYUYV422 8-bit, keMvSurfaceFormatYUAYVA4224 8-bit,  
                                             // and keMvSurfaceFormatARGBGraphic 8-bit can be used for the texture data.
     EMvD3DTextureBindFlags in_eBindFlags,   // Indicates the bind flags of the Direct3D texture.
     void** out_ppD3DTexture                 // Pointer that receives the created texture.
     ) = 0;

  //
  // Summary:
  //    Destroys a Direct3D texture that was created with IMvGpuTransfer::CreateD3DTexture().
  // Return value:
  //    - MV_NOERROR, if the texture was destroyed successfully.
  //    - MV_E_INVALID_GPU_TEXTURE, if the texture was not create with IMvGpuTransfer::CreateD3DTexture().
  //
  virtual HRESULT __stdcall DestroyD3DTexture
     (
     void* in_pD3DTexture // Indicates the pointer of the texture to destroy.
     ) = 0;

  //
  // Summary:
  //    Copies a video surface to a Direct3D texture.
  // Return value:
  //    - MV_NOERROR, if completed successfully.
  //    - MV_E_INVALID_GPU_TEXTURE, if the texture has not been allocated in the GPU transfer module
  //      (IMvGpuTransfer::CreateD3DTexture()).
  //    - MV_E_INVALID_GPU_SURFACE, if the video surface has not been allocated in the GPU transfer module
  //      (IMvGpuTransfer::CreateD3DTexture()).
  // 
  virtual HRESULT __stdcall CopySurfaceToD3DTexture
     (
     IMvSurface * in_pISurface, // Pointer to the IMvSurface interface of the video surface to copy.
     void* in_pD3DTexture       // Indicates the Direct3D texture to update.
     ) = 0;

  //
  // Summary:
  //    Copies a Direct3D texture to a video surface.
  // Return value:
  //    - MV_NOERROR, if completed successfully.
  //    - MV_E_INVALID_GPU_TEXTURE, if the texture has not been allocated in the GPU transfer module
  //      (IMvGpuTransfer::CreateD3DTexture()).
  //    - MV_E_INVALID_GPU_SURFACE, if the video surface has not been allocated in the GPU transfer module
  //      (IMvGpuTransfer::CreateD3DTexture()).
  // 
  virtual HRESULT __stdcall CopyD3DTextureToSurface
     (
     void* in_pD3DTexture,       // Indicates the Direct3D texture to copy.
     IMvSurface * in_pISurface   // Pointer to the IMvSurface interface of the video surface to update.
     ) = 0;
};

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to notify the user application that a file has been opened or will be closed and that the file
//    handle can be accessed.
// Remarks:
//    - This interface must be implemented by the user application.
//////////////////////////////////////////////////////////////////////////
interface IMvFlexFileHandleObserver : public IUnknown
{
    //
    // Summary:
    //	Notifies that the streaming file has been opened.
    // Return value:
    //   - MV_NOERROR, if completed successfully.
	//   - MV_E_INVALID_POINTER, if the pointer wszPath is NULL.
	//   - MV_E_FAIL, if an unexpected error occurs.
	// 
   virtual HRESULT __stdcall NotifyStreamingFileOpened
      (
      const wchar_t* wszPath,	// Pointer to the string that contains the path of the streaming file that has been opened.
      HANDLE hFile,				// Handle to the streaming file that has been opened.
      DWORD dwDesiredAccess		// Access mode to the streaming file.
      ) = 0;
	
    //
    // Summary:
    //	Notifies that the streaming file will be closed.
    // Return value:
    //   - MV_NOERROR, if completed successfully.
	//   - MV_E_FAIL, if an unexpected error occurs.
	// 
   virtual HRESULT __stdcall NotifyStreamingFileClosed
      (
      HANDLE hFile			// Handle to the streaming file that will be closed.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary: 
//    Interface used to configure the Flex file handle observer interface (IMvFlexFileHandleObserver).
//    
//////////////////////////////////////////////////////////////////////////////////
interface IMvFlexFileHandleConfigurator : public IUnknown
{
   //
   // Summary:
   //    Modifies the current settings of the Flex file handle observer.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetFileObserver
      (
      IMvFlexFileHandleObserver *in_pIFlexFileHandleObserver	// Pointer to the Flex file handle observer interface.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary: 
//    Interface used to get a notification when the Flex File Reader takes a long time to retrieve a position from disk.
//    
//////////////////////////////////////////////////////////////////////////////////
interface IMvPositionNotReadyObserver : public IUnknown
{
   //
   // Summary:
   //    Notifies when the Flex File Reader takes a long time to retrieve a position from disk.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall PositionNotReadyNotify
      (
         uint32_t                   in_ui32ID,                          // Supplied by the user application (see
                                                                        // IMvPositionNotReadySubject).
         uint64_t                   in_ui64PlaylistPositionInFrames,    // Position relative to the beginning of the 
                                                                        // playlist. If INFINITE, the position is 
                                                                        // unknown.
         uint64_t                   in_ui64MediaPositionInFrames,       // Position relative to the beginning of the 
                                                                        // file. If INFINITE, the position is unknown.
         uint32_t                   in_ui32TimeElapsedInMilliseconds,   // Time elapsed since waiting for this position.
         EMvPositionNotReadyAction *out_pePositionNotReadyAction        // Action to be taken by the Flex File Reader.
      ) = 0;

};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary: 
//    Interface used to configure the Flex File Reader in order to be notified when a position takes a long time to 
//    be retrieved.
//    
//////////////////////////////////////////////////////////////////////////////////
interface IMvPositionNotReadySubject : public IUnknown
{
   //
   // Summary:
   //    Adds an observer to be notified when a position takes a long time to be retrieved from disk.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetPositionNotReadyObserver
      (
         uint32_t                      in_ui32ID,  // Supplied by the user application to identify the caller when 
                                                   // IMvPositionNotReadyObserver::PositionNotReadyNotify is called.
         IMvPositionNotReadyObserver  *in_pIMvObserver,                    // The observer provided. 
         uint32_t                      in_ui32InitialTimeOutInMilliseconds,// The initial waiting period for the 
                                                                           // notification, which can be between 0
                                                                           // and 1000 milliseconds.
         uint32_t                      in_ui32NextTimeOutInMilliseconds,   // The duration for each subsequent waiting 
                                                                           // period. A notification will occur every
                                                                           // in_ui32NextTimeOutInMilliseconds, and 
                                                                           // can be between 250 and 1000 milliseconds.
                                                                           // The recommended value is 250 milliseconds.
         uint32_t                      in_ui32GlobalTimeOutInMilliseconds  // The duration after which the Flex File
                                                                           // Reader will automatically return
                                                                           // MV_E_FAILED_TO_RETRIEVE_POSITION_FROM_DISK;
                                                                           // in_ui32GlobalTimeOutInMilliseconds must 
                                                                           // be greater than or equal to
                                                                           // in_ui32NextTimeOutInMilliseconds +
                                                                           // in_ui32InitialTimeOutInMilliseconds. The
                                                                           // recommended value is 10000 milliseconds.
      ) = 0;

};



//////////////////////////////////////////////////////////////////////////////////
//
// Summary: 
//    Abstract base interface for the different AS-11 descriptive metadata framework interfaces.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvMXFDMFramework: public IUnknown
{
   //
   // Summary:
   //    Gets a descriptive metadata framework interface.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
	virtual EMvDMType __stdcall GetFrameworkType() = 0;

   //
   // Summary:
   //    Sets a descriptive metadata framework plug-in ID. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
	virtual HRESULT __stdcall SetLinkedDMFrameWorkPluginID
      (
         unsigned char in_aupackUID[32]   // Array containing the descriptive metadata framework plug-in ID.
      ) = 0;

   //
   // Summary:
   //    Gets a descriptive metadata framework plug-in ID. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetLinkedDMFrameWorkPluginID
      (
         unsigned char * out_packUID[32]  // Pointer to the array containing the descriptive metadata framework plug-in ID.
      ) = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary: 
//    Interface used to get and set descriptive metadata framework interfaces (IMvDMFramework_AS11_Core,
//    IMvDMFramework_AS11_Segmentation, and IMvDMFramework_AS11_UK_DPP) for the Flex File Writer using the 
//    IMvMXFDMFramework abstract base interface.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvDescriptiveMetadata : public IUnknown
{
   // Summary:
   //    Gets the number and types of descriptive metadata framework schemes in a file.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - If out_peDMTypes is NULL, the total number of descriptive metadata framework schemes is returned, including
   //      unsupported schemes.
   //    - If out_peDMTypes is other than NULL, only supported descriptive metadata framework schemes are returned.
   //
   virtual HRESULT __stdcall GetDMTypesAndCount
   (
      uint32_t    * out_pui32DMCount,  // Pointer to the number of descriptive metadata framework schemes in a file.
      EMvDMType   * out_peDMTypes      // Pointer to EMvDMType listing all the available descriptive metadata framework
                                       // types.
   ) = 0;


   //
   // Summary:
   //    Initializes a descriptive metadata framework interface.  
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
	virtual HRESULT __stdcall GetMXFDMFramework
   (
      EMvDMType in_eWantedDMFramework,          // Descriptive metadata framework that you would like to use.
      IMvMXFDMFramework ** out_ppIDMFrameWork   // Pointer that receives the abstract base interface (IMvMXFDMFramework).
   ) = 0;

   //
   // Summary:
   //    Sets the initialized descriptive metadata framework interface for the Flex File Writer.
   //    
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
	virtual HRESULT __stdcall SetMXFDMFramework
   (
      IMvMXFDMFramework * in_pIDMFrameWork // Pointer to the abstract base interface (IMvMXFDMFramework).
   ) = 0;

};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to get and set the AS-11 core metadata framework elements. 
// Remarks:
//    - The AS-11 Core scheme defines the required metadata that is included in all AS-11 files.
//    
//////////////////////////////////////////////////////////////////////////////////
interface IMvDMFramework_AS11_Core : public IMvMXFDMFramework
{
   //
   // Summary:
   //    Sets the series title string.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
	virtual HRESULT __stdcall SetSeries_Title
		(
		wchar_t * in_pwszSeriesTitle  // Pointer to the string containing the series title.
		) = 0;

   //
   // Summary:
   //    Sets the programme title string.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetProgramme_Title
      (
      wchar_t * in_pwszProgramme_Title   // Pointer to the string containing the programme title.
      ) = 0;

   //
   // Summary:
   //    Sets the episode title number string.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetEpisode_Title_Number
      (
      wchar_t * in_pwszEpisode_Title_Number   // Pointer to the string containing the episode title number.
      ) = 0;

   //
   // Summary:
   //    Sets the shim name string.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The shim name is the name of the AS-11 shim specification to which the associated <i>.mxf</i> file conforms.
   //
   virtual HRESULT __stdcall SetShim_Name
      (
      wchar_t * in_pwszShim_Name   // Pointer to the string containing the shim name.
      ) = 0;

   //
   // Summary:
   //    Sets the audio track layout in accordance with EBU R 123 (HD) and R 48 (SD).
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Must have 16 tracks (4 for SD) and be aligned with tape specification definitions. 
   //    - Valid silence must be included.  
   //
   virtual HRESULT __stdcall SetAudio_Track_Layout
      (
      uint8_t in_ui8Audio_Track_Layout // Value of the audio track layout.
      ) = 0;

   //
   // Summary:
   //    Sets the primary audio language string.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Uses the ISO 639.2 values.
   //
   virtual HRESULT __stdcall SetPrimary_Audio_Language
      (
      wchar_t * in_pwszPrimary_Audio_Language  // Pointer to the string containing the primary audio language.
      ) = 0;

   //
   // Summary:
   //    Sets whether or not closed captions are present.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetClosed_Captions_Present
      (
      bool in_bClosed_Captions_Present  // If true, closed captions are present.
      ) = 0;

   //
   // Summary:
   //    Sets the type of closed captions to be used.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetClosed_Captions_Type
      (
      uint8_t in_ui8Closed_Captions_Type // Value corresponding to the type of closed captions used.
      ) = 0;

   //
   // Summary:
   //    Sets the closed captions language used.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetCaption_Language
      (
      wchar_t * in_pwszCaption_Language // Pointer to the string containing the caption language.
      ) = 0;




   //
   // Summary:
   //    Gets the series title. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If you call the method with a NULL string pointer, the pointer to the buffer size (io_p32BufferSize) returns
   //      the required buffer size (in bytes) for the string.
   //
	virtual HRESULT __stdcall GetSeries_Title
      (
      wchar_t * out_pwszSeriesTitle,   // Pointer to the string containing the series title.
      uint32_t * io_p32BufferSize      // Pointer to the buffer size (in bytes) for the string.
      ) = 0;

   //
   // Summary:
   //    Gets the programme title.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If you call the method with a NULL string pointer, the pointer to the buffer size (io_p32BufferSize) returns
   //      the required buffer size (in bytes) for the string.
   //
   virtual HRESULT __stdcall GetProgramme_Title
      (
      wchar_t * out_pwszProgramme_Title, // Pointer to the string containing the programme title.
      uint32_t * io_p32BufferSize        // Pointer to the buffer size (in bytes) for the string.
      ) = 0;

   //
   // Summary:
   //    Gets the episode title number.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - If you call the method with a NULL string pointer, the pointer to the buffer size (io_p32BufferSize) 
   //      returns the required buffer size (in bytes) for the string.
   //
   virtual HRESULT __stdcall GetEpisode_Title_Number
      (
      wchar_t * out_pwszEpisode_Title_Number, // Pointer to the string containing the episode title number.
      uint32_t * io_p32BufferSize             // Pointer to the buffer size (in bytes) for the string.
      ) = 0;

   //
   // Summary:
   //    Gets the shim name.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - The shim name is the name of the AS-11 shim specification to which the associated <i>.mxf</i> file conforms.
   //    - If you call the method with a NULL string pointer, the pointer to the buffer size (io_p32BufferSize) returns
   //      the required buffer size (in bytes) for the string.
   //
   virtual HRESULT __stdcall GetShim_Name
      (
      wchar_t * out_pwszShim_Name,  // Pointer to the string containing the shim name.
      uint32_t * io_p32BufferSize   // Pointer to the buffer size (in bytes) for the string.
      ) = 0;

   //
   // Summary:
   //    Gets the primary audio language.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Uses the ISO 639.2 values.
   //    - If you call the method with a NULL string pointer, the pointer to the buffer size (io_p32BufferSize) returns
   //      the required buffer size (in bytes) for the string.
   //
   virtual HRESULT __stdcall GetPrimary_Audio_Language
      (
      wchar_t * out_pwszPrimary_Audio_Language,  // Pointer to the string containing the primary audio language.
      uint32_t * io_p32BufferSize                // Pointer to the buffer size (in bytes) for the string.
      ) = 0;

   //
   // Summary:
   //    Gets the audio track layout in accordance with EBU R 123 (HD) and R 48 (SD).
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - Must have 16 tracks (4 for SD) and be aligned with tape specification definitions. 
   //    - Valid silence must be included. 
   //
   virtual HRESULT __stdcall GetAudio_Track_Layout
      (
      uint8_t * out_pui8Audio_Track_Layout // Pointer to the audio track layout value.
      ) = 0;

   //
   // Summary:
   //    Gets whether or not closed captions are present.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetClosed_Captions_Present
      (
      bool * out_pbClosed_Captions_Present  // Pointer to the bool indicating whether or not closed captions are present.
      ) = 0;

   //
   // Summary:
   //    Gets the type of closed captions used.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetClosed_Captions_Type
      (
      uint8_t * out_pui8Closed_Captions_Type  // Pointer to the value corresponding to the type of closed captions used.
      ) = 0;

   //
   // Summary:
   //    Gets the closed captions language used.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - If you call the method with a NULL string pointer, the pointer to the buffer size (io_p32BufferSize) returns
   //      the required buffer size (in bytes) for the string.
   //
   virtual HRESULT __stdcall GetCaption_Language
      (
      wchar_t * out_pwszCaption_Language,  // Pointer to the string containing the caption language.
      uint32_t * io_p32BufferSize          // Pointer to the buffer size (in bytes) for the string.
      ) = 0;

};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to get and set the AS-11 segmentation metadata framework elements. 
// Remarks:
//    - The AS-11 Segmentation scheme defines the metadata that describes individual program parts on a segmentation
//      track.
//    
//////////////////////////////////////////////////////////////////////////////////
interface  IMvDMFramework_AS11_Segmentation : public IMvMXFDMFramework 
{
   
   //
   // Summary:
   //    Gets the total number of segmentation elements, including fillers.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual uint16_t  __stdcall  Get_Elements_Total() = 0;

   //
   // Summary:
   //    Gets the total number of segmentation program parts. 
   // Return value:
   //    - Total program parts. 
   //
   virtual uint16_t  __stdcall  Get_Program_Parts_Total() = 0;

   //
   // Summary:
   //    Sets the properties of a segmentation element.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall  Set_Element_Property
   (
      uint64_t in_uiStart, 			   // Indicates the start of the element.
      uint64_t in_uiDuration, 		   // Indicates the duration of the element.
      bool     bIsProgram,             // If true, the element is part of a program.
      uint16_t ui16ProgramPartNumber = 0  // Indicates the part number of the program. <p><b>Note</b>: Use zero for fillers.
   ) = 0;

   //
   // Summary:
   //    Gets the properties of a segmentation element, including the index.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall  Get_Element_Property
   (
      uint32_t in_ui32Element,               // Indicates the zero-based element index. <p><b>Note</b>: An element can
                                             // be either a filler or a program part.
      uint64_t * out_puiStart,               // Pointer to the start of the element.
      uint64_t * out_puiDuration,            // Pointer to the duration of the element.
      bool     * out_bIsProgram,             // Pointer to the bool indicating whether or not the element is part of a program.
      uint16_t * out_ui16ProgramPartNumber   // Pointer to the part number of the program. <p><b>Note</b>: Uses zero for fillers.
   ) = 0;

};




//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface used to get and set the AS-11 UK Digital Production Partnership (DPP) metadata framework elements. 
// Remarks:
//    - The AS-11 UK DPP scheme defines an additional metadata set that may be optionally specified by shims.
//    
//////////////////////////////////////////////////////////////////////////////////
interface IMvDMFramework_AS11_UK_DPP : public IMvMXFDMFramework
{
   //
   // Summary:
   //    Sets the production number string.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
	virtual HRESULT __stdcall Set_Production_Number
      (
      wchar_t * in_pwszProductionNumber // Pointer to the string containing the production number.
      ) = 0;


   //
   // Summary:
   //    Gets the production number.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If you call the method with a NULL string pointer, the pointer to the buffer size (io_p32BufferSize) returns
   //      the required buffer size (in bytes) for the string.
   //
   virtual HRESULT __stdcall Get_Production_Number
      (
      wchar_t * out_pwszProductionNumber,  // Pointer to the string containing the production number.
      uint32_t * io_p32BufferSize          // Pointer to the buffer size (in bytes) for the string.
      ) = 0;


   //
   // Summary:
   //    Sets the synopsis string.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
	virtual HRESULT __stdcall Set_Synopsis
      (
      wchar_t * in_pwszSynopsis // Pointer to the string containing the synopsis.
      ) = 0;


   //
   // Summary:
   //    Gets the synopsis.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If you call the method with a NULL string pointer, the pointer to the buffer size (io_p32BufferSize) returns
   //      the required buffer size (in bytes) for the string.
   //
   virtual HRESULT __stdcall Get_Synopsis
      (
      wchar_t * out_pwszSynopsis,  // Pointer to the string containing the synopsis.
      uint32_t * io_p32BufferSize  // Pointer to the buffer size (in bytes) for the string.
      ) = 0;


   //
   // Summary:
   //    Sets the originator string.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
	virtual HRESULT __stdcall Set_Originator
      (
      wchar_t * in_pwszOriginator // Pointer to the string containing the originator.
      ) = 0;


   //
   // Summary:
   //    Gets the originator.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If you call the method with a NULL string pointer, the pointer to the buffer size (io_p32BufferSize) returns 
   //      the required buffer size (in bytes) for the string.
   //
   virtual HRESULT __stdcall Get_Originator
      (
      wchar_t * out_pwszOriginator,  // Pointer to the string containing the originator.
      uint32_t * io_p32BufferSize    // Pointer to the buffer size (in bytes) for the string.
      ) = 0;


   //
   // Summary:
   //    Sets the other identifier string. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_Other_Identifier
      (
      wchar_t * in_pwszOtherIdentifier // Pointer to the string containing the other identifier.
      ) = 0;


   //
   // Summary:
   //    Gets the other identifier.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If you call the method with a NULL string pointer, the pointer to the buffer size (io_p32BufferSize) returns
   //      the required buffer size (in bytes) for the string.
   //
   virtual HRESULT __stdcall Get_Other_Identifier
      (
      wchar_t * out_pwszOtherIdentifier,  // Pointer to the string containing the other identifier.
      uint32_t * io_p32BufferSize         // Pointer to the buffer size (in bytes) for the string.
      ) = 0;



   //
   // Summary:
   //    Sets the other identifier type string.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_Other_Identifiertype
      (
      wchar_t * in_pwszOtherIdentifiertype // Pointer to the string containing the other identifier type.
      ) = 0;


   //
   // Summary:
   //    Gets the other identifier type.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If you call the method with a NULL string pointer, the pointer to the buffer size (io_p32BufferSize) returns
   //      the required buffer size (in bytes) for the string.
   //
   virtual HRESULT __stdcall Get_Other_Identifiertype
      (
      wchar_t * out_pwszOtherIdentifiertype,  // Pointer to the string containing the other identifier type.
      uint32_t * io_p32BufferSize             // Pointer to the buffer size (in bytes) for the string.
      ) = 0;

   //
   // Summary:
   //    Sets the genre string.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_Genre
      (
      wchar_t * in_pwszGenre // Pointer to the string containing the genre.
      ) = 0;


   //
   // Summary:
   //    Gets the genre.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If you call the method with a NULL string pointer, the pointer to the buffer size (io_p32BufferSize) returns
   //      the required buffer size (in bytes) for the string. 
   //
   virtual HRESULT __stdcall Get_Genre
      (
      wchar_t * out_pwszGenre,      // Pointer to the string containing the genre.
      uint32_t * io_p32BufferSize   // Pointer to the buffer size (in bytes) for the string.
      ) = 0;

   //
   // Summary:
   //    Sets the distributor string.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_Distributor
      (
      wchar_t * in_pwszDistributor // Pointer to the string containing the distributor.
      ) = 0;


   //
   // Summary:
   //    Gets the distributor.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If you call the method with a NULL string pointer, the pointer to the buffer size (io_p32BufferSize) returns
   //      the required buffer size (in bytes) for the string.
   //
   virtual HRESULT __stdcall Get_Distributor
      (
      wchar_t * out_pwszDistributor,  // Pointer to the string containing the distributor.
      uint32_t * io_p32BufferSize     // Pointer to the buffer size (in bytes) for the string.
      ) = 0;

   //
   // Summary:
   //    Sets the FPA manufacturer string.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_FPA_Manufacturer
      (
      wchar_t * in_pwszFPAManufacturer // Pointer to the string containing the FPA manufacturer.
      ) = 0;


   //
   // Summary:
   //    Gets the FPA manufacturer.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - If you call the method with a NULL string pointer, the pointer to the buffer size (io_p32BufferSize) returns
   //      the required buffer size (in bytes) for the string.
   //
   virtual HRESULT __stdcall Get_FPA_Manufacturer
      (
      wchar_t * out_pwszFPAManufacturer,  // Pointer to the string containing the FPA manufacturer.
      uint32_t * io_p32BufferSize         // Pointer to the buffer size (in bytes) for the string.
      ) = 0;

   //
   // Summary:
   //    Sets the FPA version string.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_FPA_Version
      (
      wchar_t * in_pwszFPAVersion // Pointer to the string containing the FPA version.
      ) = 0;


   //
   // Summary:
   //    Gets the FPA version.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If you call the method with a NULL string pointer, the pointer to the buffer size (io_p32BufferSize) returns
   //      the required buffer size (in bytes) for the string.
   //
   virtual HRESULT __stdcall Get_FPA_Version
      (
      wchar_t * out_pwszFPAVersion,  // Pointer to the string containing the FPA version.
      uint32_t * io_p32BufferSize    // Pointer to the buffer size (in bytes) for the string.
      ) = 0;

   //
   // Summary:
   //    Sets the video comments string.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_Video_Comments
      (
      wchar_t * in_pwszVideoComments // Pointer to the string containing the video comments.
      ) = 0;


   //
   // Summary:
   //    Gets the video comments.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If you call the method with a NULL string pointer, the pointer to the buffer size (io_p32BufferSize) returns
   //      THe required buffer size (in bytes) for the string.
   //
   virtual HRESULT __stdcall Get_Video_Comments
      (
      wchar_t * out_pwszVideoComments,  // Pointer to the string containing the video comments.
      uint32_t * io_p32BufferSize       // Pointer to the buffer size (in bytes) for the string.
      ) = 0;

   //
   // Summary:
   //    Sets the secondary audio language string.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_Secondary_Audio_Language
      (
      wchar_t * in_pwszSecondaryAudioLanguage // Pointer to the string containing the secondary audio language.
      ) = 0;


   //
   // Summary:
   //    Gets the secondary audio language.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If you call the method with a NULL string pointer, the pointer to the buffer size (io_p32BufferSize) returns
   //      the required buffer size (in bytes) for the string. 
   //
   virtual HRESULT __stdcall Get_Secondary_Audio_Language
      (
      wchar_t * out_pwszSecondaryAudioLanguage,  // Pointer to the string containing the secondary audio language.
      uint32_t * io_p32BufferSize                // Pointer to the buffer size (in bytes) for the string.
      ) = 0;

   //
   // Summary:
   //    Sets the tertiary audio language string.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_Tertiary_Audio_Language
      (
      wchar_t * in_pwszTertiaryAudioLanguage // Pointer to the string containing the tertiary audio language.
      ) = 0;


   //
   // Summary:
   //    Gets the tertiary audio language.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If you call the method with a NULL string pointer, the pointer to the buffer size (io_p32BufferSize) returns
   //      the required buffer size (in bytes) for the string.
   //
   virtual HRESULT __stdcall Get_Tertiary_Audio_Language
      (
      wchar_t * out_pwszTertiaryAudioLanguage,  // Pointer to the string containing the tertiary audio language.
      uint32_t * io_p32BufferSize               // Pointer to the buffer size (in bytes) for the string.
      ) = 0;


   //
   // Summary:
   //    Gets the audio comments.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If you call the method with a NULL string pointer, the pointer to the buffer size (io_p32BufferSize) returns
   //      the required buffer size (in bytes) for the string.
   //
   virtual HRESULT __stdcall Get_Audio_Comments
      (
      wchar_t * out_pwszAudioComments,  // Pointer to the string containing the audio comments.
      uint32_t * io_p32BufferSize       // Pointer to the buffer size (in bytes) for the string.
      ) = 0;

   //
   // Summary:
   //    Sets the audio comments string.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_Audio_Comments
      (
      wchar_t * in_pwszAudioComments // Pointer to the string containing the audio comments.
      ) = 0;


   //
   // Summary:
   //    Gets the programme text language.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If you call the method with a NULL string pointer, the pointer to the buffer size (io_p32BufferSize) returns
   //      the required buffer size (in bytes) for the string.
   //
   virtual HRESULT __stdcall Get_Programme_Text_Language
      (
      wchar_t * out_pwszProgrammeTextLanguage,  // Pointer to the string containing the programme text language.
      uint32_t * io_p32BufferSize               // Pointer to the buffer size (in bytes) for the string.
      ) = 0;

   //
   // Summary:
   //    Sets the programme text language string.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_Programme_Text_Language
      (
      wchar_t * in_pwszProgrammeTextLanguage // Pointer to the string containing the programme text language.
      ) = 0;


   //
   // Summary:
   //    Gets the contact email.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If you call the method with a NULL string pointer, the pointer to the buffer size (io_p32BufferSize) returns
   //      the required buffer size (in bytes) for the string.
   //
   virtual HRESULT __stdcall Get_Contact_Email
      (
      wchar_t * out_pwszContactEmail,  // Pointer to the string containing the contact email.
      uint32_t * io_p32BufferSize      // Pointer to the buffer size (in bytes) for the string.
      ) = 0;

   //
   // Summary:
   //    Sets the contact email string.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_Contact_Email
      (
      wchar_t * in_pwszContactEmail // Pointer to the string containing the contact email.
      ) = 0;


   //
   // Summary:
   //    Gets the contact telephone number.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - If you call the method with a NULL string pointer, the pointer to the buffer size (io_p32BufferSize) returns
   //      the required buffer size (in bytes) for the string. 
   //
   virtual HRESULT __stdcall Get_Contact_Telephone_No
      (
      wchar_t * out_pwszContactTelephoneNo,  // Pointer to the string containing the contact telephone number.
      uint32_t * io_p32BufferSize            // Pointer to the buffer size (in bytes) for the string.
      ) = 0;

   //
   // Summary:
   //    Sets the contact telephone number string.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_Contact_Telephone_No
      (
      wchar_t * in_pwszContactTelephoneNo // Pointer to the string containing the contact telephone number.
      ) = 0;


   //
   // Summary:
   //    Sets the copyright year.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_Copyright_Year
      (
      uint16_t in_ui16CopyrightYear // Indicates the copyright year.
      ) = 0;


   //
   // Summary:
   //    Gets the copyright year.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Get_Copyright_Year
      (
      uint16_t * out_ui16CopyrightYear // Pointer to the copyright year.
      ) = 0;



   //
   // Summary:
   //    Sets the total number of parts.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_Total_Number_Of_Parts
      (
      uint16_t in_ui16TotalNumberOfParts // Indicates the total number of parts.
      ) = 0;


   //
   // Summary:
   //    Gets the total number of parts.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Get_Total_Number_Of_Parts
      (
      uint16_t * out_ui16TotalNumberOfParts // Pointer to the total number of parts.
      ) = 0;




   //
   // Summary:
   //    Sets the picture ratio.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_Picture_Ratio
      (
      uint32_t in_ui32Numerator,  // Indicates the picture ratio numerator.
      uint32_t in_ui32denominator // Indicates the picture ratio denominator.
      ) = 0;


   //
   // Summary:
   //    Gets the picture ratio.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Get_Picture_Ratio
      (
      uint32_t * out_pui32Numerator,  // Pointer to the picture ratio numerator.
      uint32_t * out_pui32denominator // Pointer to the picture ratio denominator.
      ) = 0;



   //
   // Summary:
   //    Sets whether or not open captions are present.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_Open_Captions_Present
      (
      bool in_bOpenCaptionsPresent // If true, open captions are present.
      ) = 0;


   //
   // Summary:
   //    Gets whether or not open captions are present.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Get_Open_Captions_Present
      (
      bool * out_pbOpenCaptionsPresent // Pointer to the bool indicating whether or not open captions are present.
      ) = 0;



   //
   // Summary:
   //    Sets whether or not the material is 3D.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_3D
      (
      bool in_b3D // If true, 3D is used.
      ) = 0;


   //
   // Summary:
   //    Gets whether or not the material is 3D.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Get_3D
      (
      bool * out_pb3D // Pointer to the bool indicating whether or not the material is 3D.
      ) = 0;



   //
   // Summary:
   //    Sets whether or not the content contains product placement.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_Product_Placement
      (
      bool in_bProductPlacement // If true, the content contains product placement.
      ) = 0;


   //
   // Summary:
   //    Gets whether or not the content contains product placement.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Get_Product_Placement
      (
      bool * out_pbProductPlacement // Pointer to the bool indicating whether or not the content contains product placement.
      ) = 0;


   //
   // Summary:
   //    Sets whether or not the audio description is present.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_Audio_Description_Present
      (
      bool in_bAudioDescriptionPresent // If true, the audio description is present.
      ) = 0;


   //
   // Summary:
   //    Gets whether or not the audio description is present.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Get_Audio_Description_Present
      (
      bool * out_pbAudioDescriptionPresent // Pointer to the bool indicating whether or not the audio description is present.
      ) = 0;



   //
   // Summary:
   //    Sets whether or not textless elements exist.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_Textless_Elements_Exist
      (
      bool in_bTextlessElementsExist // If true, textless elements exist.
      ) = 0;


   //
   // Summary:
   //    Gets whether or not textless elements exist.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Get_Textless_Elements_Exist
      (
      bool * out_pbTextlessElementsExist // Pointer to the bool indicating whether or not textless elements exist.
      ) = 0;



   //
   // Summary:
   //    Sets whether or not the programme has text.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_Programme_Has_Text
      (
      bool in_bProgrammeHasText // If true, the programme has text.
      ) = 0;


   //
   // Summary:
   //    Gets whether or not the programme has text.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Get_Programme_Has_Text
      (
      bool * out_pbProgrammeHasText // Pointer to the bool indicating whether or not the programme has text.
      ) = 0;



   //
   // Summary:
   //    Sets the type of 3D used.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - Refer to the AMWA AS-11 Specification for details on the defined values.
   //
   virtual HRESULT __stdcall Set_3DType
      (
      uint8_t in_ui8e3DType // Indicates the 3D type value.
      ) = 0;


   //
   // Summary:
   //    Gets the type of 3D used.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Refer to the AMWA AS-11 Specification for details on the defined values.
   //
   virtual HRESULT __stdcall Get_3DType
      (
      uint8_t * out_pui8e3DType // Pointer to the bool indicating the 3D type value.
      ) = 0;




   //
   // Summary:
   //    Sets the FPA pass. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Refer to the AMWA AS-11 Specification for details on the defined values.
   //
   virtual HRESULT __stdcall Set_FPA_Pass
      (
      uint8_t in_ui8FPAPass // Indicates the FPA pass value.
      ) = 0;


   //
   // Summary:
   //    Gets the FPA pass.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Refer to the AMWA AS-11 Specification for details on the defined values.
   //
   virtual HRESULT __stdcall Get_FPA_Pass
      (
      uint8_t * out_pui8FPAPass // Pointer to the FPA pass value.
      ) = 0;

   //
   // Summary:
   //    Sets the compliant audio standard. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Refer to the AMWA AS-11 Specification for details on the defined values. 
   //
   virtual HRESULT __stdcall Set_Compliant_Audio_Standard
      (
      uint8_t in_ui8CompliantAudioStandard // Indicates the compliant audio standard value.
      ) = 0;


   //
   // Summary:
   //    Gets the compliant audio standard.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Refer to the AMWA AS-11 Specification for details on the defined values.
   //
   virtual HRESULT __stdcall Get_Compliant_Audio_Standard
      (
      uint8_t * out_pui8CompliantAudioStandard // Pointer to the compliant audio standard value.
      ) = 0;

   //
   // Summary:
   //    Sets the audio description type. 
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - Refer to the AMWA AS-11 Specification for details on the defined values.
   //
   virtual HRESULT __stdcall Set_Audio_Description_Type
      (
      uint8_t in_ui8AudioDescriptionType // Indicates the audio description type value.
      ) = 0;


   //
   // Summary:
   //    Gets the audio description type.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - Refer to the AMWA AS-11 Specification for details on the defined values. 
   //
   virtual HRESULT __stdcall Get_Audio_Description_Type
      (
      uint8_t * out_pui8AudioDescriptionType // Pointer to the audio description type value.
      ) = 0;

   //
   // Summary:
   //    Sets the open captions type. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Refer to the AMWA AS-11 Specification for details on the defined values. 
   //
   virtual HRESULT __stdcall Set_Open_Captions_Type
      (
      uint8_t in_ui8OpenCaptionsType // Indicates the open captions type value. 
      ) = 0;


   //
   // Summary:
   //    Gets the open captions type. 
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - Refer to the AMWA AS-11 Specification for details on the defined values. 
   //
   virtual HRESULT __stdcall Get_Open_Captions_Type
      (
      uint8_t * out_pui8OpenCaptionsType  // Pointer to the open captions type value.
      ) = 0;

   //
   // Summary:
   //    Sets the open captions language. 
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - Refer to the AMWA AS-11 Specification for details on the defined values. 
   //
   virtual HRESULT __stdcall Set_Open_Captions_Language
      (
      uint8_t in_ui8OpenCaptionsLanguage // Indicates the open captions language value.
      ) = 0;


   //
   // Summary:
   //    Gets the open captions language. 
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - Refer to the AMWA AS-11 Specification for details on the defined values. 
   //
   virtual HRESULT __stdcall Get_Open_Captions_Language
      (
      uint8_t * out_pui8OpenCaptionsLanguage // Pointer to the open captions language value.
      ) = 0;

   //
   // Summary:
   //    Sets the signing present value. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Refer to the AMWA AS-11 Specification for details on the defined values.
   //
   virtual HRESULT __stdcall Set_Signing_Present
      (
      uint8_t in_ui8SigningPresent // Indicates the signing present value.
      ) = 0;


   //
   // Summary:
   //    Gets the signing present value. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Refer to the AMWA AS-11 Specification for details on the defined values. 
   //
   virtual HRESULT __stdcall Get_Signing_Present
      (
      uint8_t * out_pui8SigningPresent // Pointer to the signing present value.
      ) = 0;


   //
   // Summary:
   //    Sets the sign language value. 
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - Refer to the AMWA AS-11 Specification for details on the defined values. 
   //
   virtual HRESULT __stdcall Set_Sign_Language
      (
      uint8_t in_ui8SignLanguage // Indicates the sign language value.
      ) = 0;


   //
   // Summary:
   //    Gets the sign language value. 
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - Refer to the AMWA AS-11 Specification for details on the defined values.
   //
   virtual HRESULT __stdcall Get_Sign_Language
      (
      uint8_t * out_pui8SignLanguage // Pointer to the sign language value.
      ) = 0;

   //
   // Summary:
   //    Sets the line up start value.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_Line_Up_Start
      (
      uint64_t in_ui64LineUpStart // Indicates the line up start value.
      ) = 0;


   //
   // Summary:
   //    Gets the line up start value.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Get_Line_Up_Start
      (
      uint64_t * out_pui64LineUpStart // Pointer to the line up start value.
      ) = 0;



   //
   // Summary:
   //    Sets the ident clock start value.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_Ident_Clock_Start
      (
      uint64_t in_ui64IdentClockStart // Indicates the ident clock start value.
      ) = 0;


   //
   // Summary:
   //    Gets the ident clock start value.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Get_Ident_Clock_Start
      (
      uint64_t * out_pui64IdentClockStart // Pointer to the ident clock start value.
      ) = 0;




   //
   // Summary:
   //    Sets the total programme duration.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Set_Total_Programme_Duration
      (
      uint64_t in_ui64TotalProgrammeDuration // Indicates the total programme duration value.
      ) = 0;


   //
   // Summary:
   //    Gets the total programme duration.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Get_Total_Programme_Duration
      (
      uint64_t * out_pui64TotalProgrammeDuration // Pointer to the total programme duration value.
      ) = 0;


   //
   // Summary:
   //    Sets the completion date.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - The SMPTE ST 377-1 time stamp format is used. 
   //
   virtual HRESULT __stdcall Set_Completion_Date
      (
      unsigned char * in_ucCompletionDate // Indicates the completion date value as an 8-byte array.
      ) = 0;



   //
   // Summary:
   //    Gets the completion date.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The SMPTE ST 377-1 time stamp format is used.
   //
   virtual HRESULT __stdcall Get_Completion_Date
      (
      unsigned char * out_pucCompletionDate // Pointer to the completion date value (defined as an 8-byte array).
      ) = 0;

};

///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Controls the Matrox MPEG-2 Transport Stream Demuxer notification. 
// Remarks:
//    - This interface will be notified each time the demuxing operation is completed on an MPEG-2 transport stream muxed buffer.
//
///////////////////////////////////////////////////////////////////////////////
interface IMvMPEG2TSDemuxerNotification : public IUnknown
{
   //
   // Summary:
   //    Provides the demuxed video buffer to the caller.
   // Return value:
   //    MV_NOERROR.
   //
   virtual HRESULT __stdcall NotifyVideoBuffer
      (
      IMvSurface * in_pIVideoBuffer       // Pointer to the IMvSurface containing the video stream.
      ) = 0;

   //
   // Summary:
   //    Provides the demuxed audio samples to the caller.
   // Return value:
   //    MV_NOERROR.
   //
   virtual HRESULT __stdcall NotifyAudioSamples
      (
      IMvAudioSamples * in_pIAudioSamples,            // Pointer to the IMvAudioSamples interface containing the audio streams.
      uint64_t          in_ui64OffsetFromActualStart  // Offset used to synchronize the video on the audio stream.
      ) = 0;

   //
   // Summary:
   //    Provides the demuxed VANC buffer to the caller.
   // Return value:
   //    MV_NOERROR.
   //
   virtual HRESULT __stdcall NotifyVANCBuffer
   (
   IMvSurface * in_pIVANCBuffer          // Pointer to the IMvSurface containing the VANC stream.
   ) = 0;

   //
   // Summary:
   //    Provides the caller with information regarding setup data for AAC audio, if present in the audio stream.
   // Remarks:
   // - This method is called before calling IMvMPEG2TSDemuxerNotification::NotifyAudioSamples().
   // Return value:
   //    MV_NOERROR.
   //
   virtual HRESULT __stdcall NotifyData
      (
      IID         in_IIDInterface,  // GUID of the data the user is interested in.
      IUnknown*   in_pIUnk          // Pointer to the interface of the GUID.
      ) = 0;

   //
   // Summary:
   //    Notifies the caller that the demuxer processing is finished and the demuxer is closed.
   // Return value:
   //    MV_NOERROR.
   //
   virtual HRESULT __stdcall NotifyDemuxerClosed () = 0;

};

///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Controls the Matrox MPEG-2 Transport Stream Demuxer.
//
///////////////////////////////////////////////////////////////////////////////
interface IMvMPEG2TSDemuxer : public IUnknown
{	
   //
   // Summary:
   //    Initializes the transport stream demuxer with a pointer to the IMvMPEG2TSDemuxerNotification interface.
   // Return value:
   //    - Returns an error if the command failed or the input parameter is NULL.
   virtual HRESULT __stdcall Open
      (
      IMvMPEG2TSDemuxerNotification *in_pIMPEG2TSDemuxerNotification	// Pointer to the IMvMPEG2TSDemuxerNotification interface
																		// that will be notified each time an MPEG-2 transport
																		// stream buffer is demuxed into video, audio, and VANC (if present) streams.
      ) = 0;                                                           
                                                                     

   //
   // Summary:
   //    Closes the transport stream demuxer.
   // Return value:
   //    - Returns an error if the command failed or there are invalid parameters.
   virtual HRESULT __stdcall Close() = 0;

   //
   // Summary:
   //    Provides a transport stream muxed buffer containing video, audio, and VANC (if present) streams.
   // Return value:
   //    - Returns an error if the command failed or there are invalid parameters.
   virtual HRESULT __stdcall PutTSMuxedSurface
      (
      IMvSurface* in_pITSMuxedBuffer      // Pointer to the IMvSurface interface that contains the transport stream muxed surface.
      ) = 0;
      
   //
   // Summary:
   //    Signals the end of the MPEG-2 transport stream buffer.	
   // Return value:
   //    - Returns an error if the command failed or there are invalid parameters.
   virtual HRESULT __stdcall PutEOSTSMuxedSurface()=0;

};

///////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Supplied to the user application via the IMvMPEG2TSDemuxerNotification::NotifyData method.
//
///////////////////////////////////////////////////////////////////////////////
interface IMvMPEG2TSDemuxerStreamInfo : public IUnknown
{	
   //
   // Summary:
   //    Used to retrieve the information found in the TS stream.
   // Return value:
   //    - Returns an error if the command failed or an input parameter is not initialized properly.
   virtual HRESULT __stdcall GetTSStreamInfo
      (
      SMvResolutionInfo &io_rsResInfo, // size has to be initialized
      EMvSurfaceFormat  &io_reSurfaceFormat,
      SMvaWaveFormatInfo &io_rsWavFormatInfo // size has to be initialized
      ) = 0;                                                           

};

/////////////////////////////////////////////////////////////////////////////////////
// Summary: 
//   Helper interface used to attach an AVC-Intra header.
//////////////////////////////////////////////////////////////////////////////////////
interface IMvAVCIntraHelper : public IUnknown
{
   // Gets the pointer to the header.
   virtual HRESULT __stdcall GetHeader(unsigned char *out_pHeader) = 0;
   // Gets the size of the header in bytes.
   virtual HRESULT __stdcall GetHeaderSize(int32_t *out_i32Size) = 0;
   // Updates the header by loading data from a buffer.
   virtual HRESULT __stdcall LoadHeader(unsigned char *in_pHeader, unsigned long in_ulSize) = 0;

   // Verifies the validity of the header.
   virtual HRESULT __stdcall IsHeaderValid(bool *out_pIsValid) = 0;

   virtual HRESULT __stdcall ValidateData(unsigned char *in_pucHeader, bool *out_pIsValid) = 0;

   //Sets the resolution info and surface format info(class 50 or class 100) to AVCIntraHelper in order to add SPS/PPS header when it is missing in the file.
   virtual HRESULT __stdcall SetResolutionAndSurfaceFormat(SMvResolutionInfo *in_pSResolution, EMvSurfaceFormat in_eSurfaceFormat) = 0;

   virtual HRESULT __stdcall GetSetupData(uint8_t** out_ppui8Buffer, uint32_t* out_pui32BufferSize) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface to control a video encoder.
// Remarks:
//    
//    Currently for the H.264 software encoder 2 and the M264 hardware encoder.
//    
//////////////////////////////////////////////////////////////////////////////////
interface IMvEncoderVideo : public IUnknown
{
   //
   // Summary:
   //    Initializes the encoder.
   //    The encoder's compression settings structure is given via the in_pmvchOptionValue
   //    parameter and must match the in_eCodecOption value expected for each encoder.
   // Return value:
   //    - Returns an error if any parameters are invalid or if the compression 
   //    settings are invalid.
   virtual HRESULT __stdcall Open(
      MVCHANDLE      in_pmvchOptionValue,    // pointer the expected compression settings structure
      EMvCodecOption in_eCodecOption) = 0;   // value specifying the type of the compression structure

   //
   // Summary:
   //    Tells the encoder to stop encoding as soon as possible.
   //    The encoder will call the IMvCompletionCallback::Notify (if the encoder supports this option)
   //    with NULL when it has finished encoding.  The IMvCompletionCallback interface should have been
   //    specified with SetOption below before the first Open call in order to receive this notification.
   //    There must be a Close after a successful Open.
   // Return value:
   //    - Returns an error if problems occurred while stopping the encoder.
   virtual HRESULT __stdcall Close() = 0;

   //
   // Summary:
   //    Give uncompressed video surfaces and VANC surfaces to be encoded.
   // Return value:
   //    - Returns an error if any parameters are invalid.
   //    - May return MV_E_MODULE_BUSY if there are too many pending buffers in the encoder 
   virtual HRESULT __stdcall PutUncompressedVideoAndVANC(
      IMvSurface*    in_pIVideoSurface,      // video surface containing uncompressed video to encode
      IMvSurface*    in_pIVANCSurface) = 0;  // VANC surface to encode, can be NULL

   //
   // Summary:
   //    Give an empty user buffer surface which will eventually be filled with compressed data.
   //    The size of the empty surface should be set to the value obtained from GetOption with 
   //    in_eCodecOption keMvCodecOptionMaxCompressedFrameSizeByBytes_ui32 from encoders that 
   //    support this option.
   //    Once the surface has been written to, the IMvSurface::SignalWriteCompletion will be done and the size of
   //    the surface will be changed to the amount of data written.
   //    The IMvCompletionCallback::Notify (if the encoder supports this option) will also be
   //    called with the pointer to this surface when the write has completed.  
   //    The IMvCompletionCallback interface should have been specified with SetOption below 
   //    in order to receive this notification.
   // Return value:
   //    - Returns an error if any parameters are invalid.
   //    - May return MV_E_MODULE_BUSY if there are too many pending buffers in the encoder 
   virtual HRESULT __stdcall GetCompressedSurface(
      IMvSurface*    in_pISurface) = 0;      // empty surface which will eventually hold compressed data 

   //
   // Summary:
   //    Get information from the encoder.
   //    The type of information requested is specified with the in_eCodecOption value.
   //    The information will be returned in out_pmvchOptionValue if the option is supported.
   // Return value:
   //    - Returns an error if the parameters are invalid or if the option is not supported by this encoder.
   virtual HRESULT __stdcall GetOption(
      MVCHANDLE      out_pmvchOptionValue,   // value specifying the type of information requested
      EMvCodecOption in_eCodecOption) = 0;   // pointer to the appropriate data that will be filled with the requested information

   //
   // Summary:
   //    Give information to the encoder.
   //    The type of information to be provided is specified with the in_eCodecOption value.
   //    The information provided is given via the in_pmvchOptionValue.
   // Return value:
   //    - Returns an error if the parameters are invalid or if the option is not supported by this encoder.
   virtual HRESULT __stdcall SetOption(
      MVCHANDLE      in_pmvchOptionValue,    // value specifying the type of information being provided
      EMvCodecOption in_eCodecOption) = 0 ;  // pointer to the data containing the appropriate information
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface to control a video decoder.
// Remarks:
//    
//    Currently for the H.264 M264 hardware decoder.
//    
//////////////////////////////////////////////////////////////////////////////////
interface IMvDecoderVideo : public IUnknown
{
   //
   // Summary:
   //    Initializes the decoder.
   //    The decoder's decompression settings structure is given via the in_pmvchOptionValue
   //    parameter and must match the in_eCodecOption value expected for each decoder.
   // Return value:
   //    - Returns an error if any parameters are invalid or if the decompression 
   //    settings are invalid.
   virtual HRESULT __stdcall Open(
      MVCHANDLE      in_pmvchOptionValue,
      EMvCodecOption in_eCodecOption) = 0;

   //
   // Summary:
   //    Waits for the decoder to finish decoding all provided data.
   //    There must be a Close after a successful Open.
   // Return value:
   //    - Returns an error if problems occurred while stopping the decoder.
   virtual HRESULT __stdcall Close() = 0;

   //
   // Summary:
   //    Give compressed video surfaces to be decoded. The video data does not need to
   //    be on frame/field boundaries it can be any size.  
   //    In general, providing buffers that are too small will reduce performance.
   // Return value:
   //    - Returns an error if any parameters are invalid or if the decoder is in the wrong state.
   virtual HRESULT __stdcall PutCompressedSurface(
      IMvSurface*    in_pISurface) = 0;

   //
   // Summary:
   //    Give an empty user buffer surface which will eventually be filled with decompressed data.
   //    This call is asynchronous, the provided surface will be signalled once the data is ready.
   // Return value:
   //    - Returns an error if any parameters are invalid or if the decoder is in the wrong state.
   virtual HRESULT __stdcall GetUncompressedVideoAndVANCSurface(
      IMvSurface*    in_pISurfaceVideo,
      IMvSurface*    in_pISurfaceVANC) = 0;

   //
   // Summary:
   //    Get information from the decoder.
   //    The type of information requested is specified with the in_eCodecOption value.
   //    The information will be returned in out_pmvchOptionValue if the option is supported.
   // Return value:
   //    - Returns an error if the parameters are invalid or if the option is not supported by this decoder.
   virtual HRESULT __stdcall GetOption(
      MVCHANDLE      io_pmvchOptionValue,
      EMvCodecOption in_eCodecOption) = 0;

   //
   // Summary:
   //    Give information to the decoder.
   //    The type of information to be provided is specified with the in_eCodecOption value.
   //    The information provided is given via the in_pmvchOptionValue.
   // Return value:
   //    - Returns an error if the parameters are invalid or if the option is not supported by this decoder.
   virtual HRESULT __stdcall SetOption(
      MVCHANDLE      in_pmvchOptionValue,
      EMvCodecOption in_eCodecOption) = 0 ;

   //
   // Summary:
   //    Tells the decoder that no more compressed data will be sent.  The application should
   //    continue calling GetUncompressedVideoAndVANCSurface() until it receives the call 
   //    IMvCompletionObserver::NotifyCompletion with NULL indicating that all data has been decoded.
   //    The IMvCompletionObserver interface should have been specified with SetOption 
   //    in order to receive this notification.
   // Return value:
   //    - Returns an error if problems occurred while flushing.
   virtual HRESULT __stdcall Flush() = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates connectors. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvConnectorsEnumerator : public IUnknown
{
   //
   // Summary:
   //    Gets the next available connector installed on the system.
   // Description:
   // The next connector installed on the system is retrieved from the internal list of connectors.
   // Return value:
   //    - MV_NOERROR, if properly filled. 
   //    - MV_E_END_OF_ENUM, if there is no further connectors to enumerate. 
   virtual HRESULT __stdcall Next
      (
      IMvConnector ** out_ppIConnector
      ) = 0;

   //
   // Summary:
   //    Resets the internal counter to the first connectors found on the system.
   // Description:
   //    The internal pointer is reset so that the next call to IMvConnectorsEnumerator::Next returns the first 
   //    connector found on the system.
   // Return value:
   //    - Always returns MV_NOERROR.
   virtual HRESULT __stdcall Reset() = 0;

   //
   // Summary:
   //    Skips a given number of connectors.
   // Description:
   //    The internal pointer is reset so that the next call to IMvConnectorsEnumerator::Next skips a given number of 
   //   connectors in the internal list.
   // Return value:
   //    - Always returns MV_NOERROR. 
   virtual HRESULT __stdcall Skip
      (
      uint32_t in_ui32Count   // Number of connectors to skip.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates the SfpIp. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSfpIpEnumerator : public IUnknown
{
   //
   // Summary:
   //    Resets the internal counter to the first SfpIp found on the system.
   // Description:
   //    The internal pointer is reset so that the next call to IMvSfpIpEnumerator::Next returns the first 
   //    SfpIp found on the system.
   // Return value:
   //    - Always returns MV_NOERROR.
   virtual HRESULT __stdcall Reset() = 0;

   //
   // Summary:
   //    Gets the next available SfpIp installed on the system.
   // Description:
   // The next SfpIp installed on the system is retrieved from the internal list of SfpIp.
   // Return value:
   //    - MV_NOERROR, if properly filled. 
   //    - MV_E_END_OF_ENUM, if there is no further SfpIp to enumerate. 
   virtual HRESULT __stdcall Next
      (
      IMvSfpIp** out_ppISfpIp    // Pointer that receives the next SfpIp interface.
      ) = 0;

   //
   // Summary:
   //    Skips a given number of SfpIp.
   // Description:
   //    The internal pointer is reset so that the next call to IMvSfpIpEnumerator::Next skips a given number of 
   //   SfpIp in the internal list.
   // Return value:
   //    - Always returns MV_NOERROR. 
   virtual HRESULT __stdcall Skip
      (
      uint32_t in_ui32Count      // Number of SfpIp to skip.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents an SdiIp audio output virtual pair connector.
// Remarks:
//    - This interface is used to configure the audio output.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSdiIpAudioOutputPairConnector : public IMvConnector
{
   //
   // Summary:
   //    Gets the pair identifier for the corresponding audio pair.
   // Return value:
   //    - EMvAudioPair: Pair identifier.
   //
   virtual EMvAudioPair __stdcall GetPairIdentifier() = 0;
};


//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents an SdiIp audio input virtual pair connector.
// Remarks:
//    - This interface is used to configure the audio input.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSdiIpAudioInputPairConnector : public IMvConnector
{
   //
   // Summary:
   //    Gets the pair identifier for the corresponding audio pair.
   // Return value:
   //    - EMvAudioPair: Pair identifier.
   //
   virtual EMvAudioPair __stdcall GetPairIdentifier() = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates the SdiIp audio input pair connectors. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSdiIpAudioInputPairConnectorsEnumerator : public IUnknown
{
   //
   // Summary:
   //    Updates and resets the internal list of interfaces.
   // Description:
   //    The internal list of SdiIp audio input pair connector interfaces is updated with the most recent 
   //    values on the card and the internal pointer is reset so that the next call to
   //    IMvSdiIpAudioInputPairConnectorsEnumerator::Next returns the first SdiIp audio input pair 
   //    connector interface in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Reset() = 0;

   //
   // Summary:
   //   Gets the next interface.
   // Description:
   //	  The next SdiIp audio input pair connector interface is retrieved from the internal list of SdiIp
   //   audio input pair connector interfaces.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Next
      (
      IMvSdiIpAudioInputPairConnector ** out_ppIConnector   // Pointer that receives the next SdiIp audio
                                                            // input pair connector interface.
      ) = 0;

   //
   // Summary:
   //    Skips a given number of interfaces.
   // Description:
   //    The internal pointer is changed so that the next call to IMvSdiIpAudioInputPairConnectorsEnumerator::Next 
   //    skips a given number of SdiIp audio input pair connector interfaces in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Skip
      (
      uint32_t in_ui32Count   // Number of SdiIp audio input pair connector interfaces to skip.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates the SdiIp audio output pair connectors. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSdiIpAudioOutputPairConnectorsEnumerator : public IUnknown
{
   //
   // Summary:
   //    Updates and resets the internal list of interfaces.
   // Description:
   //    The internal list of SdiIp audio output pair connector interfaces is updated with the most recent
   //    values on the card and the internal pointer is reset so that the next call to
   //    IMvSdiIpAudioOutputPairConnectorsEnumerator::Next returns the first SdiIp audio output pair
   //    connector interface in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //   
   virtual HRESULT __stdcall Reset() = 0;

   //
   // Summary:
   //    Gets the next interface.
   // Description:
   //	   The next SdiIp audio output pair connector interface is retrieved from the internal list of SdiIp
   //    audio output pair connector interfaces.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Next
      (
      IMvSdiIpAudioOutputPairConnector ** out_ppIConnector  // Pointer that receives the next SdiIp audio 
                                                            // output pair connector interface.
      ) = 0;

   //
   // Summary:
   //    Skips a given number of interfaces.
   // Description:
   //    The internal pointer is changed so that the next call to IMvSdiIpAudioOutputPairConnectorsEnumerator::Next
   //    skips a given number of SdiIp audio output pair connector interfaces in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Skip
      (
      uint32_t in_ui32Count   // Number of SdiIp audio output pair connector interfaces to skip.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides the callback notification of the SdiIp video input connector. 
//    This interface passes notification information to the object implementing it.
// Remarks:
//    - Use the IMvSdiIpInputConnector interface to register and unregister the
//      IMvSdiIpConnectorNotificationCallback interface.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSdiIpConnectorNotificationCallback : public IUnknown
{
   //
   // Summary:
   //    Receives the new video connector status.
   // Return value:
   //    - MV_NOERROR. 
   //
   virtual HRESULT __stdcall Notify
      (
      EMvSfpLabel in_eCage,                      // Indicates at which SfpIp belongs the SdiIp video connector.
      EMvVideoConnectorLabel in_eConnectorLabel, // Indicates which SdiIp video connector label status has changed.
      const SMvSdiIpConnectorStatus & in_krsVideoConnectorStatus // Structure of the new SdiIp video connector status.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Provides the callback notification of the SdiIp audio input connector. 
//    This interface passes notification information to the object implementing it.
// Remarks:
//    - Use the IMvSdiIpInputConnector interface to register and unregister the
//      IMvSdiIpAudioConnectorNotificationCallback interface.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSdiIpAudioConnectorNotificationCallback : public IUnknown
{
   virtual HRESULT __stdcall Notify
      (
      EMvSfpLabel in_eCage,                        // Indicates at which SfpIp belongs the SdiIp audio connector.
      EMvVideoConnectorLabel in_eConnectorLabel,   // Connector label of the SdiIp audio connector
                                                   // that has changed status. 
      const SMvAudioPairStatus in_asStatus[],      // Pointer to the array of structures of SdiIp audio
                                                   // connector pairs whose status has changed.
      uint32_t in_ui32NbOfAudioPairs) = 0;         // Number of SdiIp audio connector pairs in the preceding
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents an SdiIp input connector. 
// Remarks:
//    - This interface can be queried for the physical details of the SdiIp input connector.
//    - This interface can also be used to query or change a connector's current settings.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSdiIpInputConnector : public IMvConnector
{
   //
   // Summary:
   //    Gets the SdiIp input connector label.
   // Return value:
   //    - EMvVideoConnectorLabel: SdiIp input connector label. 
   //
   virtual EMvVideoConnectorLabel __stdcall GetConnectorLabel() = 0;

   //
   // Summary:
   //    Gets the current video status of the SdiIp input connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetSdiIpConnectorStatus
      (
      SMvSdiIpConnectorStatus & io_rsStatus  // Structure that receives the current video status of the SdiIp 
                                             // input connector.
      ) = 0;

   //
   // Summary:
   //    Registers a video callback notification for the SdiIp input connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::AddRef method of the in_pICallback parameter is called when the
   //      notification is registered to prevent the object implementing the IMvSdiIpConnectorNotificationCallback 
   //      interface from being destroyed.
   //
   virtual HRESULT __stdcall RegisterVideoCallbackForNotification
      (
      IMvSdiIpConnectorNotificationCallback * in_pICallback    // Pointer to the SdiIp video connector
                                                               // notification callback interface.
      ) = 0;

   //
   // Summary:
   //    Unregisters a video callback notification for the SdiIp input connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::Release method of the in_pICallback parameter is called when the
   //      notification is unregistered to remove the reference count added by 
   //      IMvSdiIpInputConnector::RegisterVideoCallbackForNotification.
   //
   virtual HRESULT __stdcall UnregisterVideoCallbackForNotification
      (
      IMvSdiIpConnectorNotificationCallback * in_pICallback    // Pointer to the SdiIp video connector
                                                               // notification callback interface.
      ) = 0;

   //
   // Summary:
   //    Gets the SfpIp of the SdiIp input connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetAssociatedSfpIp
      (
      IMvSfpIp ** out_ppISfpIp      // Pointer that receives the SfpIp interface.
      ) = 0;

   //
   // Summary:
   //    Gets the current settings of the SdiIp input connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetConnectorSettings
      (
      SMvSdiIpInputConnectorSettings & io_rsSettings  // Structure that receives the current SdiIp input 
                                                      // connector settings.
      ) = 0;

   //
   // Summary:
   //    Modifies the current settings of the SdiIp input connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetConnectorSettings
      (
      const SMvSdiIpInputConnectorSettings & in_rsSettings  // Structure of the new SdiIp input settings.
      ) = 0;

   //
   // Summary:
   //    Creates the enumerator for the SdiIp audio input pair connector for the corresponding SdiIp input
   //    connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateAudioConnectorsEnumerator
      (
      IMvSdiIpAudioInputPairConnectorsEnumerator ** out_ppIEnumerator   // Pointer that receives the SdiIp audio input pair 
                                                                        // connector enumerator for the corresponding SdiIp 
                                                                        // input connector.
      ) = 0;

   //
   // Summary:
   //    Gets the SdiIp audio input pair connector using the pair ID.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetAudioPairConnector
      (
      uint32_t in_ui32Pair,      // Connector identifier.
      IMvSdiIpAudioInputPairConnector ** out_ppIConnector   // Pointer that receives the SdiIp audio input pair 
                                                            // connector interface.
      ) = 0;

   //
   // Summary:
   //    Gets the number of SdiIp audio input pair connectors.
   // Return value:
   //    - uint32_t: Number of SdiIp audio input pair connectors. 
   //
   virtual uint32_t __stdcall GetAudioConnectorCount() = 0;

   //
   // Summary:
   //    Registers an audio callback notification for the SdiIp input connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    - The IUnknown::AddRef method of the in_pICallback parameter is called
   //      when the notification is registered to prevent the object implementing the
   //      IMvSdiIpAudioConnectorNotificationCallback interface from being destroyed.
   //
   virtual HRESULT __stdcall RegisterAudioCallbackForNotification
      (
      IMvSdiIpAudioConnectorNotificationCallback * in_pICallback     // Pointer to the SdiIp audio connector 
                                                                     // notification callback interface.
      ) = 0;

   //
   // Summary:
   //    Unregisters an audio callback notification for the SdiIp input connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::Release method of the in_pICallback parameter is called 
   //      when the notification is unregistered to remove the reference count added by
   //      IMvSdiIpInputConnector::RegisterAudioCallbackForNotification.
   //
   virtual HRESULT __stdcall UnregisterAudioCallbackForNotification
      (
      IMvSdiIpAudioConnectorNotificationCallback * in_pICallback     // Pointer to the SdiIp audio connector 
                                                                     // notification callback interface.
      ) = 0;

   //
   // Summary:
   //    Gets the current audio status of the SdiIp input connectors.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetAudioStatus
      (
      SMvAudioPairStatus out_asAudioPairStatus[],  // Pointer to the array of structures that receives the status of the
                                                   // SdiIp audio input pair connectors.
      uint32_t in_ui32ArrayCount                   // The number of elements in the array.
      ) = 0;

   //
   // Summary:
   //    Gets the connector interface of the connector that will capture the alpha values.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetAssociatedAlphaConnector
      (
      IMvSdiIpInputConnector** out_ppIAlphaConnector // Pointer that receives the connector interface of the connector 
                                                     // that will capture the alpha values.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates the SdiIp input connectors. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSdiIpInputConnectorsEnumerator : public IUnknown
{
   //
   // Summary:
   //    Updates and resets the internal list of interfaces.
   // Description:
   //    The internal list of SdiIp input connector interfaces is updated with the most recent values on the card
   //    and the internal pointer is reset so that the next call to IMvSdiIpInputConnectorsEnumerator::Next returns
   //    the first SdiIp input connector interface in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Reset() = 0;

   //
   // Summary:
   //    Gets the next interface.
   // Description:
   //	   The next SdiIp input connector interface is retrieved from the internal list of SdiIp input connector
   //    interfaces.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Next
      (
      IMvSdiIpInputConnector** out_ppISdiIpInputConnector   // Pointer that receives the next SdiIp input
                                                            // connector interface.
      ) = 0;

   //
   // Summary:
   //    Skips a given number of interfaces.
   // Description:
   //	   The internal pointer is changed so that the next call to IMvSdiIpInputConnectorsEnumerator::Next skips a
   //    given number of SdiIp input connector interfaces in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Skip
      (
      uint32_t in_ui32Count      // Number of SdiIp input connector interfaces to skip.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents an SdiIp output connector. 
// Remarks:
//    - This interface can be queried for the physical details of the SdiIp output connector.
//    - This interface can also be used to query or change a connector's current settings.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSdiIpOutputConnector : public IMvConnector
{
   //
   // Summary:
   //    Gets the SdiIp output connector label.
   // Return value:
   //    - EMvVideoConnectorLabel: SdiIp output connector label. 
   //
   virtual EMvVideoConnectorLabel __stdcall GetConnectorLabel() = 0;


   //
   // Summary:
   //    Creates the enumerator for the SdiIp audio output connector for the corresponding SdiIp output connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall CreateAudioConnectorsEnumerator
      (
      IMvSdiIpAudioOutputPairConnectorsEnumerator ** out_ppIEnumerator     // Pointer that receives the SdiIp audio 
                                                                           // output pair connector enumerator for the 
                                                                           // corresponding SdiIp output connector.
      ) = 0;

   //
   // Summary:
   //    Gets the SdiIp audio output pair connector using the pair ID.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetAudioPairConnector
      (
      uint32_t in_ui32Pair,        // Connector identifier.
      IMvSdiIpAudioOutputPairConnector ** out_ppIConnector     // Pointer that receives the SdiIp audio output pair 
                                                               // connector interface.
      ) = 0;

   //
   // Summary:
   //    Gets the number of SdiIp audio output pair connectors.
   // Return value:
   //    - uint32_t: Number of SdiIp audio output pair connectors. 
   //
   virtual uint32_t __stdcall GetAudioConnectorCount() = 0;


   //
   // Summary:
   //    Gets the SfpIp of the SdiIp output connector.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetAssociatedSfpIp
      (
      IMvSfpIp ** out_ppISfpIp      // Pointer that receives the SfpIp interface.
      ) = 0;

   //
   // Summary:
   //    Gets the current SdiIp output connector settings.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetConnectorSettings
      (
      SMvSdiIpOutputConnectorSettings & io_rsSettings    // Structure that receives the SdiIp output 
                                                         // connector settings.
      ) = 0;

   //
   // Summary:
   //    Modifies the current SdiIp output connector settings.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetConnectorSettings
      (
      const SMvSdiIpOutputConnectorSettings & in_rsSettings   // Structure of the SdiIp output connector settings.
      ) = 0;

   //
   // Summary:
   //    Modifies the current output stream source and audio pairs.    
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetSourceOutputStreamAndAudioPairs
      (
      IMvOutputStream * in_pIOutputStream,   // Pointer to the output stream interface.
      EMvAudioPair in_aeAudioPairs[],        // Pointer to the array of the audio pairs output stream for the SDiIp
                                             // audio pair connector.
      uint32_t in_ui32NbAudioPairs           // Indicates the number of output audio pairs in in_aeAudioPairs.
      ) = 0;

   //
   // Summary:
   //    Gets the current output stream source and audio pairs.    
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetSourceOutputStreamAndAudioPairs
      (
      IMvOutputStream ** out_ppIOutputStream,   // Pointer that receives the output stream interface.
      EMvAudioPair out_aeAudioPairs[],          // Pointer to the array that receives the audio pairs output stream for the
                                                // SdiIp audio pair connector.
      uint32_t in_ui32NbAudioPairs              // Indicates the number of output audio pairs in out_aeAudioPairs.
      ) = 0;

   //
   // Summary:
   //    Gets the connector interface of the connector that will output the alpha values.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetAssociatedAlphaConnector
      (
      IMvSdiIpOutputConnector** out_ppIAlphaConnector // Pointer that receives the connector interface of the connector 
                                                      // that will output the alpha values.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that enumerates the SdiIp output connectors. 
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSdiIpOutputConnectorsEnumerator : public IUnknown
{
   //
   // Summary:
   //    Updates and resets the internal list of interfaces.
   // Description:
   //    The internal list of SdiIp output connector interfaces is updated with the most recent values on the card
   //    and the internal pointer is reset so that the next call to IMvSdiIpOutputConnectorsEnumerator::Next returns
   //    the first SdiIp output connector interface in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Reset() = 0;
   
   //
   // Summary:
   //    Gets the next interface.
   // Description:
   //	   The next SdiIp output connector interface is retrieved from the internal list of SdiIp output connector
   //    interfaces.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall Next
      (
      IMvSdiIpOutputConnector** out_ppISdiIpOutputConnector    // Pointer that receives the next SdiIp output
                                                               // connector interface.
      ) = 0;
   
   //
   // Summary:
   //    Skips a given number of interfaces.
   // Description:
   //	   The internal pointer is changed so that the next call to IMvSdiIpOutputConnectorsEnumerator::Next skips a 
   //    given number of SdiIp output connector interfaces in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //   
   virtual HRESULT __stdcall Skip
      (
      uint32_t in_ui32Count   // Number of SdiIp output connector interfaces to skip.
      ) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents an SfpIp. 
// Remarks:
//    - This interface can be queried for the physical details of the SfpIp.
//    - This interface can also be used to query or change a SfpIp's current settings.
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvSfpIp : public IUnknown
{
   //
   // Summary:
   //    Gets the SfpIp label.
   // Return value:
   //    - EMvSfpLabel: SfpIp label. 
   //
   virtual EMvSfpLabel __stdcall GetLabel() = 0;


   //
   // Summary:
   //    Gets the current SfpIp settings.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetSettings
      (
      SMvSfpIpSettings & out_rsSettings   // Structure that receives the SfpIp settings.
      ) = 0;

   //
   // Summary:
   //    Modifies the current SfpIp settings.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall SetSettings
      (
      const SMvSfpIpSettings & in_rsSettings    // Structure of the SfpIp settings.
      ) = 0;

   //
   // Summary:
   //    Gets the current status of the SfpIp.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetStatus
      (
      SMvSfpIpStatus & out_rsSettings   // Structure that receives the current status of the SfpIp.
      ) = 0;

   //
   // Summary:
   //    Registers a callback notification for the SfpIp.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::AddRef method of the in_pICallback parameter is called when the
   //      notification is registered to prevent the object implementing the IMvSfpIpNotificationCallback 
   //      interface from being destroyed.
   //
   virtual HRESULT __stdcall RegisterCallbackForNotification
      (
      IMvSfpIpNotificationCallback * in_pICallback  // Pointer to the SfpIp notification callback interface.
      ) = 0;

   //
   // Summary:
   //    Unregisters a callback notification for the SfpIp.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    - The IUnknown::Release method of the in_pICallback parameter is called when the
   //      notification is unregistered to remove the reference count added by 
   //      IMvSfpIp::RegisterCallbackForNotification.
   //
   virtual HRESULT __stdcall UnregisterCallbackForNotification
      (
      IMvSfpIpNotificationCallback * in_pICallback  // Pointer to the SfpIp notification callback interface.
      ) = 0;

   //
   // Summary:
   //    Gets the capabilities of the SfpIp.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall GetCapabilities
      (
      SMvSfpIpCapabilities & out_rsCaps  // Structure that receives the capabilities of the SfpIp.
      ) = 0;


   
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    TBD
//    
// Remarks:
//    
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvDSXCORENotificationCallback : public IUnknown
{
   //
   // Summary:
   //    Receives the new asynchronous error for the DSX Core
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   //
   virtual HRESULT __stdcall NotifyAsyncCoreEvent(const SMvDSXCORENotification & in_krsNotification) = 0;
};

//////////////////////////////////////////////////////////////////////////////////
//
// Summary:
//    Interface that represents a DSX Core license manager. 
// Remarks:
//    - This interface is used to access information about the DSX Core seats.
//    - This interface can be used to help manage the seats available in your network
//
//////////////////////////////////////////////////////////////////////////////////
interface IMvfDSXCoreLicenseManager : public IUnknown
{
   //
   // Summary:
   //    Updates and resets the internal list of available seats on the network.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // Remarks:
   //    
   virtual HRESULT __stdcall Reset
      (
      bool bAvailableOnly,   // Discover only the seats that are available to use ( the one in use or reserved will not be discovered) 
      bool bLocalOnly        // Discover the local seats only
      ) = 0;

   //
   // Summary:
   //    The next call to Next will return the first seat present in the list,
   //    created by the call to reset().
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // 
   virtual HRESULT __stdcall Next
      (
      SMvSeatInfoPublic*     out_pwsSiegeSN //Structure that receives the seat description
      ) = 0;

   //
   // Summary:
   //    The internal pointer is changed so that the next call to IMvfDSXCoreLicenseManager::Next skips a given number
   //    of seats in the internal list.
   // Return value:
   //    - MV_NOERROR, if completed successfully. 
   // 
   virtual HRESULT __stdcall Skip
      (
      uint32_t in_ui32Count   //Number of seats to skip
      ) = 0;

   //
   // Summary:
   //    Update a Matrox DSX Core usb key using a file of type *.WibuCmRaU
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   // 
   virtual HRESULT __stdcall UpdateKeyWithRaUFile
      (
      const char* in_kacFilePath //path to the *.WibuCmRaU file
      ) = 0;
   
   //
   // Summary:
   //    This will configure the DSX Core servers list.
   //    The server list should be provided using the ipv4 ip addresses of the servers.
   //    Multiple entries should be comma separated. 
   //    e.g. "192.168.10.11"
   //    e.g. "192.168.10.11,192.168.10.12"
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   // 
   virtual HRESULT __stdcall SetServerList
      (
      char* in_IPList  //Pointer to the string of ipv4 addresses
      ) = 0;

   //
   // Summary:
   //    This will clear the server list.    
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   //
   virtual HRESULT __stdcall ClearServerList() = 0;
   

   //
   // Summary:
   //    Updates and resets the internal list of currently configured DSXCore server.     
   // Return value:
   //    - uint32_t, the number of server configured in the server list.   
   //  
   virtual uint32_t __stdcall GetServerCount() = 0;


   //
   // Summary:
   //    This will get the ipv4 address of the server at a given index. 
   // Return value:
   //    - MV_NOERROR, if completed successfully.  
   // Remarks:
   //    IMvfDSXCoreLicenseManager::GetServerCount() should be called first 
   virtual HRESULT __stdcall GetServerAt
      (
      int iIndex,                         // Index of the server 
      uint8_t  out_pucServerIp[4]     // An array of 4 unsigned int to receive the ip address
      ) = 0;
   //
   // Summary:
   //    This will allow the applications to register themselves to receive notifications about the state of the handle
   // Return Value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    You should unregister when you've received all the notifications that you require.
   virtual HRESULT __stdcall RegisterCallbackForNotification
      (
      IMvDSXCORENotificationCallback * in_pINotificationCallback    // Pointer to the callback interface that receives on clock events
      ) = 0;

   //
   // Summary:
   //    This will allow the applications to un register themselves from receiving further updates pertaining to the state of the connection
   // Return Value:
   //    - MV_NOERROR, if completed successfully.
   // Remarks:
   //    Must have called a RegisterCallbackForNotification first.
   virtual HRESULT __stdcall UnregisterCallbackForNotification
      (
      IMvDSXCORENotificationCallback * in_pINotificationCallback    // Pointer to the callback interface that receives on clock events
      ) = 0;
};
