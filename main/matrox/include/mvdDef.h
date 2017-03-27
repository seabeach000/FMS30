
//==========================================================================;
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
//--------------------------------------------------------------------------;

//----------------------------------------------------------------
//                    mvdDef.h 
//----------------------------------------------------------------
// @module  Matrox Direct Show PUBLIC definitions.
//
//----------------------------------------------------------------
//   Birth Date:       April 2003
//   Operating System: WinXP
//   Author:           DirectShow team
//----------------------------------------------------------------
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada 
//----------------------------------------------------------------

#ifndef _MVDDEF_H
#define _MVDDEF_H
#include "mvDefinitions.h"
#include "MvFlexDefinitions.h" 

#include "MvFlexDefinitionsPublicSDK.h"
#ifndef LINUX_PLATFORM
   #include "mvSubjectContext.h"
#endif


////////////////////////////////////////////////////////////////////////////////
//
// FORWARD DECLARATION
//
interface IMvTreeNode;
interface IMvCustomFileSystemIO;



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// START OF MACROS
//


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// START OF DEFINES
//
// 


////////////////////////////////////////////////////////////////////////////////
//  T E M P L A T E   T O   D O C UM E N T   E N U M S
/**
* Descriptions of the number, give a one line description here
*
*
* <H3>Enumerators:</H3>
*  <VAR>member1</VAR>:      One line descript of Member one  <BR><BR>
*  <VAR>member2</VAR>:      One line descript of Member two  <BR><BR>
* ...
*/

/**
*  
* <H3>Enumerators:</H3>
* <VAR></VAR>:      <BR><BR>
* <VAR></VAR>:      <BR><BR>
* @enum
*/

/**
* Position constants
*
* kui64MvInvalidPosition: Can be used to initialize a position variable.
* kui64MvCurrentPosition: Used to indicate that the current position of the graph should be used.  
*/
const uint64_t kui64MvInvalidPosition    = 0xffffffffffffffff;
const uint64_t kui64MvCurrentPosition    = 0xfffffffffffffffe;

/**
* CutListID Constant
*
* kulMvInvalidCutListID: Can be used to initialize a CutListID variable.
*/
const unsigned long kulMvInvalidCutListID = 0xFFFFFFFF;


/**
* Device control Constants 
*
*/
const unsigned long MQ_ED_MODE_SEEK     =     0x2000L+0L;
const unsigned long MQ_ED_MODE_UNTHREAD =     0x2000L+1L;
const unsigned long MQ_ED_MODE_OTHER    =     0x2000L+2L;
const unsigned long MQ_ED_MODE_JOG      =     0x2000L+3L;
const unsigned long MQ_ED_MODE_STANDBY  =     0x2000L+4L;  


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// START OF ENUMS
//
/* Definitions of Data Structures */     

/**
*  Defines frame-based or field-based output display selections. 
* <H3>Enumerators:</H3>
* <VAR>keMvOutputDisplayModeInvalid</VAR>: Not used.                         <BR><BR>
* <VAR>keMvOutputDisplayModeField0 </VAR>: Output Display Mode Field 0.      <BR><BR>
* <VAR>keMvOutputDisplayModeField1 </VAR>: Output Display Mode Field 1.      <BR><BR>
* <VAR>keMvOutputDisplayModeFrame  </VAR>: Output Display Mode Frame.        <BR><BR>
* <VAR>keMvOutputDisplayModeLast   </VAR>: Not used.                         <BR><BR>
* @enum
*/
enum EMvOutputDisplayMode
{
   keMvOutputDisplayModeInvalid = 0,
   keMvOutputDisplayModeField0,
   keMvOutputDisplayModeField1,
   keMvOutputDisplayModeFrame,
   keMvOutputDisplayModeLast
};




/**
* Defines the types of tree nodes used for node connection rules.
* <H3>Enumerators:</H3>                                          
* <VAR>keMvTreeNodeTypeInvalid            </VAR>: Not used.                  <BR><BR>
* <VAR>keMvTreeNodeTypeRoot               </VAR>: Root Node.                 <BR><BR>
* <VAR>keMvTreeNodeTypeConfidencePreview  </VAR>: Confidence Preview Node.   <BR><BR>
* <VAR>keMvTreeNodeTypeVideoOutputRenderer</VAR>: Video Output Renderer Node.<BR><BR>
* <VAR>keMvTreeNodeTypeVideoOutputSink    </VAR>: Video Output Sink Node.    <BR><BR>
* <VAR>keMvTreeNodeTypeVideoPushing       </VAR>: Video Pushing Node.        <BR><BR>
* <VAR>keMvTreeNodeTypeVideoCompositor    </VAR>: Video Compositor Node.     <BR><BR>
* <VAR>keMvTreeNodeTypeVideoEffect        </VAR>: Video Effect Node.         <BR><BR>
* <VAR>keMvTreeNodeTypeVideoInput         </VAR>: Video Input Node.          <BR><BR>
* <VAR>keMvTreeNodeTypeVideoCache         </VAR>: Video Cache Node.          <BR><BR>
* <VAR>keMvTreeNodeTypeAudioOutputStereo  </VAR>: Audio Output Stereo Node.  <BR><BR>
* <VAR>keMvTreeNodeTypeAudioOutputMono    </VAR>: Audio Output Mono Node.    <BR><BR>
* <VAR>keMvTreeNodeTypeAudioMixer         </VAR>: Audio Mixer Node.          <BR><BR>
* <VAR>keMvTreeNodeTypeAudioInputStereo   </VAR>: Audio Input Stereo Node.   <BR><BR>
* <VAR>keMvTreeNodeTypeAudioInputMono     </VAR>: Audio Input Mono Node.     <BR><BR>
* <VAR>keMvTreeNodeTypeAudioStereoToMono  </VAR>: Audio Stereo To Mono Node. <BR><BR>
* <VAR>keMvTreeNodeTypeAudioMonoToStereo  </VAR>: Audio Mono To Stereo Node. <BR><BR>
* <VAR>keMvTreeNodeTypeAudioOneMonoToStereo</VAR>: Audio One Mono To Stereo Node. <BR><BR>
* <VAR>keMvTreeNodeTypeAudioCache         </VAR>: Audio Cache Node.          <BR><BR>
* <VAR>keMvTreeNodeTypeInternal           </VAR>: Internal Node.             <BR><BR>
* <VAR>keMvTreeNodeTypeLast               </VAR>: Not used.                  <BR><BR>

* @enum
*/
enum EMvTreeNodeType
{
   keMvTreeNodeTypeInvalid = 0,
   keMvTreeNodeTypeRoot,
   keMvTreeNodeTypeConfidencePreview,
   keMvTreeNodeTypeVideoOutputRenderer,
   keMvTreeNodeTypeVideoOutputSink,
   keMvTreeNodeTypeVideoPushing,   
   keMvTreeNodeTypeVideoCompositor,
   keMvTreeNodeTypeVideoEffect,
   keMvTreeNodeTypeVideoInput,
   keMvTreeNodeTypeVideoCache,
   keMvTreeNodeTypeAudioOutputStereo,
   keMvTreeNodeTypeAudioOutputMono,
   keMvTreeNodeTypeAudioMixer,   
   keMvTreeNodeTypeAudioInputStereo,
   keMvTreeNodeTypeAudioInputMono,
   keMvTreeNodeTypeAudioStereoToMono,
   keMvTreeNodeTypeAudioMonoToStereo,
   keMvTreeNodeTypeAudioOneMonoToStereo,
   keMvTreeNodeTypeAudioCache,
   keMvTreeNodeTypeInternal ,  
   keMvTreeNodeTypeAudioMuxer8Tracks,
   keMvTreeNodeTypeAudioOutput8Tracks,
   keMvTreeNodeTypeLast
};




/**
* Defines the sub-types of the tree nodes used for specific node implementations.
* <H3>Enumerators:</H3>
* <VAR>keMvTreeNodeSubTypeInvalid                  </VAR>: Not used.                     <BR><BR>
* <VAR>keMvTreeNodeSubTypeSymbolicRoot             </VAR>: Symbolic Root Node.           <BR><BR>
* <VAR>keMvTreeNodeSubTypeConfidencePreview        </VAR>: Confidence Preview.           <BR><BR>
* <VAR>keMvTreeNodeSubTypeOutputVideoRenderer      </VAR>: Output Video Renderer.        <BR><BR>
* <VAR>keMvTreeNodeSubTypeOutputVideoSink          </VAR>: Output Video Sink.            <BR><BR>
* <VAR>keMvTreeNodeSubTypeOutputVideoPushing       </VAR>: Output Video Pushing.         <BR><BR>
* <VAR>keMvTreeNodeSubTypeInputVideoSource         </VAR>: Input Video Source.           <BR><BR>
* <VAR>keMvTreeNodeSubTypeInputVideoGenerated      </VAR>: Input Video Generated.        <BR><BR>
* <VAR>keMvTreeNodeSubTypeInputVideoPulling        </VAR>: Input Video Pulling.          <BR><BR>
* <VAR>keMvTreeNodeSubTypeInputVideoCutListElement </VAR>: Input Video CutList Element.  <BR><BR>
* <VAR>keMvTreeNodeSubTypeUpstreamCompositor       </VAR>: Upstream Compositor.          <BR><BR>
* <VAR>keMvTreeNodeSubTypeDownstreamCompositor     </VAR>: Downstream Compositor.        <BR><BR>
* <VAR>keMvTreeNodeSubTypeVideoEffectTransition    </VAR>: Video Effect Transition.      <BR><BR>
* <VAR>keMvTreeNodeSubTypeVideoEffectFilter        </VAR>: Video Effect Filter.          <BR><BR>
* <VAR>keMvTreeNodeSubTypeOutputAudioRenderer      </VAR>: Output Audio Renderer.        <BR><BR>
* <VAR>keMvTreeNodeSubTypeOutputAudioSinkMono      </VAR>: Output Audio Sink Mono.       <BR><BR>
* <VAR>keMvTreeNodeSubTypeOutputAudioSinkStereo    </VAR>: Output Audio Sink Stereo.     <BR><BR>
* <VAR>keMvTreeNodeSubTypeOutputAudioPushingMono   </VAR>: Output Audio Pushing Mono.    <BR><BR>
* <VAR>keMvTreeNodeSubTypeOutputAudioPushingStereo </VAR>: Output Audio Pushing Stereo.  <BR><BR>
* <VAR>keMvTreeNodeSubTypeInputAudioSourceMono     </VAR>: Input Audio Source Mono.      <BR><BR>
* <VAR>keMvTreeNodeSubTypeInputAudioSourceStereo   </VAR>: Input Audio Source Stereo.    <BR><BR>
* <VAR>keMvTreeNodeSubTypeInputAudioGeneratedMono  </VAR>: Input Audio Generated Mono.   <BR><BR>
* <VAR>keMvTreeNodeSubTypeInputAudioGeneratedStereo</VAR>: Input Audio Generated Stereo. <BR><BR>
* <VAR>keMvTreeNodeSubTypeInputAudioPulling        </VAR>: Input Audio Pulling.          <BR><BR>
* <VAR>keMvTreeNodeSubTypeInputAudioMonoPulling    </VAR>: Input Audio Pulling Mono.     <BR><BR>
* <VAR>keMvTreeNodeSubTypeAudioMixer               </VAR>: Audio Mixer.                  <BR><BR>
* <VAR>keMvTreeNodeSubTypeStereoToMono             </VAR>: Stereo To Mono.               <BR><BR>
* <VAR>keMvTreeNodeSubTypeMonoToStereo             </VAR>: Mono To Stereo.               <BR><BR>
* <VAR>keMvTreeNodeSubTypeOneMonoToStereo          </VAR>: One Mono To Stereo.           <BR><BR>
* <VAR>keMvTreeNodeSubTypeInternal                 </VAR>: Internal.                     <BR><BR>
* <VAR>keMvTreeNodeSubTypeLast                     </VAR>: Not used.                     <BR><BR>
* @enum                                                    
*/                                                         
enum EMvTreeNodeSubType                                    
{                                                          
   keMvTreeNodeSubTypeInvalid = 0,                         
   keMvTreeNodeSubTypeSymbolicRoot,                        
   keMvTreeNodeSubTypeConfidencePreview,                   
   keMvTreeNodeSubTypeOutputVideoRenderer,                 
   keMvTreeNodeSubTypeOutputVideoSink,                     
   keMvTreeNodeSubTypeOutputVideoPushing,                  
   keMvTreeNodeSubTypeInputVideoSource,                    
   keMvTreeNodeSubTypeInputVideoGenerated,                 
   keMvTreeNodeSubTypeInputVideoPulling,                   
   keMvTreeNodeSubTypeUpstreamCompositor,
   keMvTreeNodeSubTypeDownstreamCompositor,
   keMvTreeNodeSubTypeVideoEffectTransition,
   keMvTreeNodeSubTypeVideoEffectFilter,
   keMvTreeNodeSubTypeOutputAudioRenderer,
   keMvTreeNodeSubTypeOutputAudioSinkMono,
   keMvTreeNodeSubTypeOutputAudioSinkStereo,
   keMvTreeNodeSubTypeOutputAudioPushingMono,
   keMvTreeNodeSubTypeOutputAudioPushingStereo,
   keMvTreeNodeSubTypeInputAudioSourceMono,
   keMvTreeNodeSubTypeInputAudioSourceStereo,
   keMvTreeNodeSubTypeInputAudioGeneratedMono,
   keMvTreeNodeSubTypeInputAudioGeneratedStereo,
   keMvTreeNodeSubTypeInputAudioPulling,
   keMvTreeNodeSubTypeInputAudioMonoPulling,
   keMvTreeNodeSubTypeAudioMixer,
   keMvTreeNodeSubTypeStereoToMono,
   keMvTreeNodeSubTypeMonoToStereo,
   keMvTreeNodeSubTypeOneMonoToStereo,
   keMvTreeNodeSubTypeInternal,
   keMvTreeNodeSubTypeInputVideoCutListElement,
   keMvTreeNodeSubTypeInputAudioCutListElementMono,
   keMvTreeNodeSubTypeInputAudioCutListElementStereo,
   keMvTreeNodeSubTypeAudioMuxer8Tracks,
   keMvTreeNodeSubTypeOutputAudioRenderer8Tracks,
   keMvTreeNodeSubTypeOutputDirectSoundRenderer,
   keMvTreeNodeSubTypeLast
};




/**
* Defines the child usage type.
* <H3>Enumerators:</H3>
* <VAR>kemvChildUsageInvalid            </VAR>: Not used.                                                          <BR><BR>
* <VAR>kemvChildUsageDontCare           </VAR>: The child of the node does not need any specification on its usage.<BR><BR>
* <VAR>kemvChildUsageBackground         </VAR>: The child is the background of a downstream compositor.            <BR><BR>
* <VAR>kemvChildUsageSource             </VAR>: The child is the source of a compositor or a filter.               <BR><BR>
* <VAR>kemvChildUsageGFX                </VAR>: The child is the GFX layer of an effect that needs GFX.            <BR><BR>
* <VAR>kemvChildUsageLeftChannel        </VAR>: The child is the AUDIO left channel of a mono to stereo node.      <BR><BR>
* <VAR>kemvChildUsageRightChannel       </VAR>: The child is the AUDIO right channel of a mono to stereo node.     <BR><BR>
* <VAR>kemvChildUsageTransitionIncoming </VAR>: The child is the source of the transition that will "wipe" on the TransitionOutGoing source. It is only used for children of the transition effect node.  <BR><BR>
* <VAR>kemvChildUsageTransitionOutgoing </VAR>: The child is the source of the transition that will be "wiped out" by the TransitionInGoing source. It is only used for children of the transition effect node.  <BR><BR>
* <VAR>kemvChildUsageLast               </VAR>: Not used.                                                          <BR><BR>
* @enum                                   
*/                                   
enum EMvChildUsage 
{                                   
   kemvChildUsageInvalid = 0,
   kemvChildUsageDontCare,
   kemvChildUsageBackground, 
   kemvChildUsageSource,
   kemvChildUsageGFX, 
   kemvChildUsageLeftChannel, 
   kemvChildUsageRightChannel, 
   kemvChildUsageTransitionIncoming, 
   kemvChildUsageTransitionOutgoing,
   kemvChildUsageLast
};



/**
* Defines the tree processing type (audio or video).
* <H3>Enumerators:</H3>
* <VAR>keMvTreeProcessingTypeInvalid </VAR>: Not used.            <BR><BR>
* <VAR>keMvTreeProcessingTypeAudio   </VAR>: Audio processing type.<BR><BR>
* <VAR>keMvTreeProcessingTypeVideo   </VAR>: Video processing type.<BR><BR>
* <VAR>keMvTreeProcessingTypeLast    </VAR>: Not used.            <BR><BR>
* @enum
*/
enum EMvTreeProcessingType
{
   keMvTreeProcessingTypeInvalid = 0,
   keMvTreeProcessingTypeAudio,
   keMvTreeProcessingTypeVideo,
   keMvTreeProcessingTypeLast
};




/**
* Defines tree processing formats used to enforce a type of processing.
*
* <H3>Enumerators:</H3>
* <VAR>keMvTreeProcessingFormatInvalid    </VAR> :Not used.                       <BR><BR>
* <VAR>keMvTreeProcessingFormat8bits      </VAR>: 8-bit processing format.      <BR><BR>
* <VAR>keMvTreeProcessingFormat10bits     </VAR>: 10-bit processing format.      <BR><BR>
* <VAR>keMvTreeProcessingFormat16bits     </VAR>: 16-bit processing format.      <BR><BR>
* <VAR>keMvTreeProcessingFormat24bitsIn32 </VAR>: 24-bit in 32-bit processing format.<BR><BR>
* <VAR>keMvTreeProcessingFormat32float    </VAR>: 32 float processing format.     <BR><BR>
* <VAR>keMvTreeProcessingFormatLast       </VAR>: Not used.                       <BR><BR>
* @enum
*/
enum EMvTreeProcessingFormat
{
   keMvTreeProcessingFormatInvalid = 0,
   keMvTreeProcessingFormat8bits,
   keMvTreeProcessingFormat10bits,
   keMvTreeProcessingFormat16bits,
   keMvTreeProcessingFormat24bitsIn32,
   keMvTreeProcessingFormat32float,
   keMvTreeProcessingFormatLast
};





/**
* Defines pushing node operation modes.
*
* <H3>Enumerators:</H3>
* <VAR>keMvPushingModeInvalid                     </VAR>: Not used.                                    <BR><BR>
* <VAR>keMvPushingModeUndefinedFormat             </VAR>: Undefined format mode: Host application will receive the resulting Flex surface of the child node linked to this pushing node. The obtained result can be of any format.<BR><BR>
* <VAR>keMvPushingModeDefinedFormat               </VAR>: Defined format mode: Host application will receive the resulting Flex surface of the child node linked to this pushing node. The obtained result should be a Flex surface that has a specific format.<BR><BR>
* <VAR>keMvPushingModeDefinedFormatWithDestination</VAR>: Defined format "with destination" mode: Host application will receive a copy of the resulting Flex surface of the child node linked to this pushing node. The copy will be created in a Flex surface provided by the host application. The host application will force the format.<BR><BR>
* <VAR>keMvPushingModeLast                        </VAR>: Not used.                                    <BR><BR>
* @enum
*/
enum EMvPushingMode
{
   keMvPushingModeInvalid = 0,
   keMvPushingModeUndefinedFormat,
   keMvPushingModeDefinedFormat,
   keMvPushingModeDefinedFormatWithDestination,
   keMvPushingModeLast
};




/**
* Defines the audio channel for mono stream manipulations.
*
* <H3>Enumerators:</H3>
* <VAR>keMvAudioChannelLeft    </VAR>: Left audio channel. <BR><BR>
* <VAR>keMvAudioChannelRight   </VAR>: Right audio channel.<BR><BR>
* <VAR>keMvAudioChannelInvalid </VAR>: Not used.           <BR><BR>
* <VAR>keMvAudioChannelLast    </VAR>: Not used.           <BR><BR>
* @enum
*/
enum EMvAudioChannel
{
   keMvAudioChannelLeft = 0,
   keMvAudioChannelRight,
   keMvAudioChannelLast,
   keMvAudioChannelInvalid 
};



/**
*
* Indicates the operation mode of the graph.
*
* <H3>Enumerators:</H3>
* <VAR>keMvGraphModeInvalid         </VAR>: Not used.                   <BR><BR>
* <VAR>keMvGraphModeNone            </VAR>: Graph Mode None.            <BR><BR>
* <VAR>keMvGraphModePlayback        </VAR>: Graph Mode Playback.        <BR><BR>
* <VAR>keMvGraphModeShuttle         </VAR>: Graph Mode Shuttle.         <BR><BR>
* <VAR>keMvGraphModeSeeking         </VAR>: Graph Mode Seeking.         <BR><BR>
* <VAR>keMvGraphModeCapture         </VAR>: Graph Mode Capture.         <BR><BR>
* <VAR>keMvGraphModeCompile         </VAR>: Graph Mode Compile.         <BR><BR>
* <VAR>keMvGraphModeRealtimeCompile </VAR>: Graph Mode Realtime Compile.<BR><BR>
* <VAR>keMvGraphModeLast            </VAR>: Not used.                   <BR><BR>
* @enum
*/
enum EMvGraphMode
{
   keMvGraphModeInvalid = 0,
   keMvGraphModeNone,
   keMvGraphModePlayback,
   keMvGraphModeShuttle,
   keMvGraphModeSeeking,
   keMvGraphModeCapture,
   keMvGraphModeCompile,
   keMvGraphModeRealtimeCompile,
   keMvGraphModeLast
};




/*********************************************************************************
*
* Specifies the graph state.
*
* <H3>Enumerators:</H3>
* <VAR>  keMvGraphStateInvalid        </VAR>: Graph State Invalid.     <BR><BR>
* <VAR>  keMvGraphStateIntermediate   </VAR>: Graph State Intermediate.<BR><BR>
* <VAR>  keMvGraphStateStopped        </VAR>: Graph State Stopped.     <BR><BR>
* <VAR>  keMvGraphStateRunning        </VAR>: Graph State Running.     <BR><BR>
* <VAR>  keMvGraphStatePaused         </VAR>: Graph State Paused.      <BR><BR>
* <VAR>  keMvGraphStateLast           </VAR>: Not used.                <BR><BR>
* @enum
*/
enum EMvGraphState
{
   keMvGraphStateInvalid = 0,
   keMvGraphStateIntermediate,
   keMvGraphStateStopped,
   keMvGraphStateRunning,
   keMvGraphStatePaused,
   keMvGraphStateLast
};


/** Specifies the type of input devices that are enumerated from the UIF filter. 
*
* <H3>Enumerators:</H3>
* <VAR>keMvInputDeviceTypeInvalid      </VAR>: Invalid Input Device Type.     <BR><BR>
* <VAR>keMvInputDeviceTypeXlink        </VAR>: DSX Xlink Input Device Type.<BR><BR>
* <VAR>keMvInputDeviceTypeXlinkHD      </VAR>: DSX Xlink HD Input Device Type.<BR><BR>
* <VAR>keMvInputDeviceType1394         </VAR>: DV-1394 Input Device Type.     <BR><BR>
* <VAR>keMvInputDeviceTypeLast         </VAR>: Not used.                      <BR><BR>
* @enum
*/
enum EMvInputDeviceType
{
   keMvInputDeviceTypeInvalid =0,
   keMvInputDeviceTypeXlink,
   keMvInputDeviceTypeXlinkHD,
   keMvInputDeviceType1394,
   keMvInputDeviceTypeOnBoardIO,
   keMvInputDeviceTypeMXO2,
   keMvInputDeviceTypeLast
};

/** Specifies the types of ouput devices that can be enumerated. 
*
* <H3>Enumerators:</H3>
* <VAR>EMvOutputDeviceTypeTypeInvalid        </VAR>: Invalid Output Device Type.     <BR><BR>
* <VAR>EMvOutputDeviceTypeXlink              </VAR>: DSX Xlink Output Device Type.<BR><BR>
* <VAR>EMvOutputDeviceTypeXlinkHD            </VAR>: DSX Xlink HD Output Device Type.<BR><BR>
* <VAR>EMvOutputDeviceType1394               </VAR>: DV-1394 Output Device Type.     <BR><BR>
* <VAR>EMvOutputDeviceTypeLast               </VAR>: Not used.                       <BR><BR>
* @enum
*/
enum EMvOutputDeviceType
{
   EMvOutputDeviceTypeTypeInvalid =0,
   EMvOutputDeviceTypeXlink,
   EMvOutputDeviceTypeXlinkHD,
   EMvOutputDeviceType1394,
   EMvOutputDeviceTypeLast
};

/** Specifies the type of 1394 input devices from the UIF filter. 
*
* <H3>Enumerators:</H3>
* <VAR>keMv1394InputDeviceTypeInvalid      </VAR>: Invalid Input Device Type.     <BR><BR>
* <VAR>keMv1394InputDeviceTypeDV        </VAR>: 1394 DV Input Device Type.<BR><BR>
* <VAR>keMv1394InputDeviceTypeHDV      </VAR>: 1394 HDV Input Device Type.<BR><BR>
* <VAR>keMv1394InputDeviceTypeLast         </VAR>: Not used.                      <BR><BR>
* @enum
*/
enum EMv1394InputDeviceType
{
   keMv1394InputDeviceTypeInvalid =0,
   keMv1394InputDeviceTypeDV,
   keMv1394InputDeviceTypeHDV,
   keMv1394InputDeviceTypeLast
};



/**
* Specifies video bit depth (8 bits or 10 bits). 
*
* <H3>Enumerators:</H3>
* <VAR>keVideoBitDepthInvalid </VAR>: Not used.         <BR><BR>
* <VAR>keVideoBitDepth_8bit   </VAR>: Bit depth is 8-bit.  <BR><BR>
* <VAR>keVideoBitDepth_10bit  </VAR>: Bit depth is 10-bit. <BR><BR>
* <VAR>keVideoBitDepthLast    </VAR>: Not used.         <BR><BR>
* @enum
*/
enum EMvVideoBitDepth{
   keVideoBitDepthInvalid=0,
   keVideoBitDepth_8bit=8,
   keVideoBitDepth_10bit=10,
   keVideoBitDepthLast,
};


/**
* Specifies generated audio input nodes.
*
* <H3>Enumerators:</H3>
* <VAR>keMvGeneratedSoundInvalid </VAR>: Not Used.              <BR><BR>
* <VAR>keMvGeneratedSoundSilence </VAR>: GeneratedSoundSilence. <BR><BR>
* <VAR>keMvGeneratedSoundLast    </VAR>: Not Used.              <BR><BR>
* @enum
*/
enum EMvGeneratedSound
{
   keMvGeneratedSoundInvalid = 0,
   keMvGeneratedSoundSilence,
   keMvGeneratedSound1khzTone,
   keMvGeneratedSoundLast
};

/**
* Specifies different DV encoding methods.
*
* <H3>Enumerators:</H3>
* <VAR>keMvDVTypeInvalid   </VAR>: Not Used.                            <BR><BR>
* <VAR>keMvDVTypeDVSD      </VAR>: DV data as defined in Part 3 of the Specification of Consumer-use Digital VCRs. <BR><BR>
* <VAR>keMvDVTypeDV25      </VAR>: SMPTE 314M 25Mb/s compressed format. <BR><BR>
* <VAR>keMvDVTypeDV50      </VAR>: SMPTE 314M 50Mb/s compressed format. <BR><BR>
* <VAR>keMvDVTypeNative1394</VAR>: This is used to indicate that we don't want any decompression/recompression on 1394 acquisition. <BR><BR>
* <VAR>keMvDVTypeLast      </VAR>: Not Used.                            <BR><BR>
* @enum
*/
enum EMvDVType
{
   keMvDVTypeInvalid = 0 ,
   keMvDVTypeDVSD ,
   keMvDVTypeDV25 ,
   keMvDVTypeDV50 ,
   keMvDVTypeDV100 ,
   keMvDVTypeNative1394 ,
   keMvDVTypeLast 
};

/**
* Specifies different MPEG-2 profiles.
*
* <H3>Enumerators:</H3>
* <VAR>keMvMPEG2ProfileInvalid               </VAR>: Not used.                   <BR><BR>
* <VAR>keMvMPEG2Profile_Simple               </VAR>: Simple Profile.             <BR><BR>
* <VAR>keMvMPEG2Profile_Main                 </VAR>: Main Profile.               <BR><BR>
* <VAR>keMvMPEG2Profile_SNRScalable          </VAR>: SNR Scalable Profile.       <BR><BR>
* <VAR>keMvMPEG2Profile_SpatiallyScalable    </VAR>: Spatially Scalable Profile. <BR><BR>
* <VAR>keMvMPEG2Profile_High                 </VAR>: High Profile.               <BR><BR>
* <VAR>keMvMPEG2Profile_422                  </VAR>: 422 Profile.                <BR><BR>
* <VAR>keMvMPEG2Profile_Last                 </VAR>: Not used.                   <BR><BR>
* @enum
*/

//
// Since Flex needs to use this enum, this definition has been moved to the 
// MvFlexDefinitionsPublicSDK.h file
//
// enum EMvMPEG2Profile
// {
//    keMvMPEG2ProfileInvalid = 0 ,
//    keMvMPEG2Profile_Simple ,
//    keMvMPEG2Profile_Main ,
//    keMvMPEG2Profile_SNRScalable ,
//    keMvMPEG2Profile_SpatiallyScalable ,
//    keMvMPEG2Profile_High ,
//    keMvMPEG2Profile_422 ,
//    keMvMPEG2Profile_Last
// };


/**
* Specifies different MPEG-2 levels.
*
* <H3>Enumerators:</H3>
* <VAR>keMvMPEG2LevelInvalid     </VAR>: Not used.       <BR><BR>
* <VAR>keMvMPEG2Level_Low        </VAR>: Low Level.      <BR><BR>
* <VAR>keMvMPEG2Level_Main       </VAR>: Main Level.     <BR><BR>
* <VAR>keMvMPEG2Level_High1440   </VAR>: High 1440 Level. <BR><BR>
* <VAR>keMvMPEG2Level_High       </VAR>: High Level.     <BR><BR>
* <VAR>keMvMPEG2Level_Last       </VAR>: Not used.       <BR><BR>
* @enum
*/

//
// Since Flex needs to use this enum, this definition has been moved to the
// MvFlexDefinitionsPublicSDK.h file.
//
// enum EMvMPEG2Level
// {
//    keMvMPEG2LevelInvalid = 0 ,
//    keMvMPEG2Level_Low ,
//    keMvMPEG2Level_Main ,
//    keMvMPEG2Level_High1440 ,
//    keMvMPEG2Level_High ,
//    keMvMPEG2Level_Last
// };

//
// Summary:
// Specifies different multiplexing options.
//
enum EMvMuxingType
{
   keMvMuxingTypeInvalid = 0 ,				// Invalid value.
   keMvMuxingTypeVideoOnly ,				// Video only, no muxing.
   keMvMuxingTypeAudioOnly ,				// Audio only, no muxing.
   keMvMuxingTypeMXFAtomVideo ,				// MXF muxing type (for OP1a only).
   keMvMuxingTypeMXFAtomAudio_1_Mono ,		// MXF Atom video or audio.
   keMvMuxingTypeDVDIF ,					// DV DIF embeded audio muxing type.
   keMvMuxingTypeAVIInterleaved ,			// AVI A/V interleaved muxing type.
   keMvMuxingTypeMPG ,						// MPG muxing type (not supported).
   keMvMuxingTypeMXFOP1A_1_Audio,			// (for OP1a only).
   keMvMuxingTypeMXFOP1A_2_Audio,			// (for OP1a only).
   keMvMuxingTypeMXFOP1A_3_Audio,			// (for OP1a only).
   keMvMuxingTypeMXFOP1A_4_Audio,			// (for OP1a only).
   keMvMuxingTypeMXFOP1A_6_Audio,			// (for OP1a only).
   keMvMuxingTypeMXFOP1A_8_Audio,			// Can be mono or stereo (for OP1a only).
   keMvMuxingTypeLast						// End of list indicator.
}; 

/**
* Specifies a selected profile priority relative to other profiles active in the system.
*
* <H3>Enumerators:</H3>
* <VAR>keMvProfilePriorityInvalid   </VAR>: Not used.           <BR><BR>
* <VAR>keMvProfilePriorityLow       </VAR>: Low priority.       <BR><BR>
* <VAR>keMvProfilePriorityNormal    </VAR>: Normal priority.    <BR><BR>
* <VAR>keMvProfilePriorityHigh      </VAR>: High priority.      <BR><BR>
* <VAR>keMvProfilePriorityLast      </VAR>: Not used.           <BR><BR>
* @enum
*/
enum EMvProfilePriorityLevel
{
   keMvProfilePriorityInvalid = 0 ,
   keMvProfilePriorityLow,
   keMvProfilePriorityNormal, 
   keMvProfilePriorityHigh,   
   keMvProfilePriorityLast
};


/**
* Specifies the type of Flex object that a parametric effect represents. <br>
* 
* <H3>Enumerators:</H3>
* 
* <VAR>keMvParamFxFlexObjTypeInvalid                          </VAR>: Not used. <BR><BR>
* <VAR>keMvParamFxFlexObjTypeVideoCompositor                  </VAR>: The parametric effect represents a Video Compositor.<BR><BR>
* <VAR>keMvParamFxFlexObjTypeVideoEffectFilter                </VAR>: The parametric effect represents a Video Filter effect.<BR><BR>
* <VAR>keMvParamFxFlexObjTypeVideoEffectTransition            </VAR>: The parametric effect represents a Video Transition effect.<BR><BR>
* <VAR>keMvParamFxFlexObjTypeVideoEffectFilterAndTransition   </VAR>: The parametric effect represents both a Video Filter and a Video Transition effect.<BR><BR>
* <VAR>keMvParamFxFlexObjTypeAudioMixer                       </VAR>: The parametric effect represents an Audio Mixer.<BR><BR>
* <VAR>keMvParamFxFlexObjTypeLast							  </VAR>: Not used. <BR><BR>
* @enum
*/
enum EMvParamFxFlexObjectType
{
   
   keMvParamFxFlexObjTypeInvalid                          = 0,
   keMvParamFxFlexObjTypeVideoCompositor                  = 1,
   keMvParamFxFlexObjTypeVideoEffectFilter                = 2,
   keMvParamFxFlexObjTypeVideoEffectTransition            = 4,
   keMvParamFxFlexObjTypeVideoEffectFilterAndTransition   = (keMvParamFxFlexObjTypeVideoEffectFilter | keMvParamFxFlexObjTypeVideoEffectTransition),
   keMvParamFxFlexObjTypeAudioMixer                       = 8,
   keMvParamFxFlexObjTypeLast
};

// Note: Because the numerical value of the EMvParamFxFlexObjectType enums can be serialized, do NOT change them!


/**
* Specifies the proper behavior to adopt when rounding of a value is required. <br>
* 
* <H3>Enumerators:</H3>
* 
* <VAR>keMvRoundingTypeInvalid</VAR>: Not used.                                    <BR><BR>
* <VAR>keMvRoundingTypeNone   </VAR>: No rounding will be done (the value is left as is).<BR><BR>
* <VAR>keMvRoundingTypeLowest </VAR>: The value is set to the lowest proximal integer (2.2 and 2.9 would both round to 2.0).                   <BR><BR>
* <VAR>keMvRoundingTypeHighest</VAR>: The value is set to the highest proximal integer (2.2 and 2.9 would both round to 3.0).                  <BR><BR>
* <VAR>keMvRoundingTypeNearest</VAR>: The value is set to the nearest integer (below 2.5 would round to 2.0; 2.5 and above would round to 3.0).<BR><BR>
* <VAR>keMvRoundingTypeLast   </VAR>: Not used.                                    <BR><BR>
* @enum
*/
enum EMvRoundingType
{
   keMvRoundingTypeInvalid = 0,
   keMvRoundingTypeNone,
   keMvRoundingTypeLowest,
   keMvRoundingTypeHighest,
   keMvRoundingTypeNearest,
   keMvRoundingTypeLast
};


/**
* Specifies a profile priority in relation to other profiles active in the system.
*
* <H3>Enumerators:</H3>
*  <VAR>keMvIOStateInvalid       </VAR>: Not used.                         <BR><BR>
*  <VAR>keMvIOStateNoAction      </VAR>: No command is currently executed. <BR><BR>
*  <VAR>keMvIOStateReading       </VAR>: Executing a reading command.      <BR><BR>
*  <VAR>keMvIOStateWriting       </VAR>: Executing a writing command.      <BR><BR>
*  <VAR>keMvIOStateReadComplete  </VAR>: A read command was completed.     <BR><BR>
*  <VAR>keMvIOStateWriteComplete </VAR>: A write command was completed.    <BR><BR>
*  <VAR>keMvIOStateReadFailed    </VAR>: A read command failed.            <BR><BR>
*  <VAR>keMvIOStateWriteFailed   </VAR>: A write command failed.           <BR><BR>
*  <VAR>keMvIOStateGeneralFailure</VAR>: General failure.                  <BR><BR>
*  <VAR>keMvIOStateLast          </VAR>: Not used.                         <BR><BR>
*
* @enum
*/
enum EMvIOState
{
   keMvIOStateInvalid = 0,    
   keMvIOStateNoAction,       
   keMvIOStateReading,        
   keMvIOStateWriting,        
   keMvIOStateReadComplete,   
   keMvIOStateWriteComplete,  
   keMvIOStateReadFailed,     
   keMvIOStateWriteFailed,    
   keMvIOStateGeneralFailure, 
   keMvIOStateLast
};


//
// Summary:
//    Specifies the GFX element type.
//
enum EMvGFXElementType                                  
{                                                       
   keMvGFXElementTypeInvalid = 0,            // Invalid value.
   keMvGFXElementTypeMaterialFrontDiffuse,   // GFX Element Type Material Front Diffuse.
   keMvGFXElementTypeMaterialTopDiffuse,     // GFX Element Type Material Top Diffuse.
   keMvGFXElementTypeMaterialBottomDiffuse,  // GFX Element Type Material Bottom Diffuse.
   keMvGFXElementTypeMaterialLeftDiffuse,    // GFX Element Type Material Left Diffuse.
   keMvGFXElementTypeMaterialRightDiffuse,   // GFX Element Type Material Right Diffuse.
   keMvGFXElementTypeMaterialFrontNormal,    // GFX Element Type Material Front Normal.
   keMvGFXElementTypeMaterialTopNormal,      // GFX Element Type Material Top Normal.
   keMvGFXElementTypeMaterialBottomNormal,   // GFX Element Type Material Bottom Normal.
   keMvGFXElementTypeMaterialLeftNormal,     // GFX Element Type Material Left Normal.
   keMvGFXElementTypeMaterialRightNormal,    // GFX Element Type Material Right Normal.
   keMvGFXElementTypeSpecularLight,          // GFX Element Type Specular Light.
   keMvGFXElementTypeMask,                   // GFX Element Type Mask.
   keMvGFXElementTypeOrganicWipe,            // GFX Element Type Organic Wipe.
   keMvGFXElementTypeGlareTexture,           // GFX Element Type Glare Texture.
   keMvGFXElementTypeGradient,               // GFX Element Type Gradient.
   keMvGFXElementTypeLensFlare,              // GFX Element Type Lens Flare.
   keMvGFXElementTypeGradient4Floats,        // GFX Element Type Gradient (4 floats).
   keMvGFXElementTypeNoise,                  // GFX Element Type Noise.
   keMvGFXElementTypeUVMap,                  // GFX Element Type UV Map.
   keMvGFXElementTypeDust,                   // GFX Element Type Dust.
   keMvGFXElementTypeStreak,                 // GFX Element Type Streak.
   keMvGFXElementTypeBrush,                  // GFX Element Type Brush.
   keMvGFXElementTypeExplosionBuffer,        // GFX Element Explosion Alpha Buffer.
   keMvGFXElementTypeExplosionInfo,          // GFX Element Explosion Particles Info.
   keMvGFXElementTypeLast,                   // End of list indicator.
};

//
// Summary:
// Specifies the file type.
//                                                
enum EMvFileInfo                                  
{                                                 
   keMvFileInfoInvalid = 0,		// Invalid value.                    
	keMvFileInfoAV,				// AV file type.                             
	keMvFileInfoMGF,			// MGF file type.                 
	keMvFileInfoGFX,			// GFX file type.
	keMvFileInfoLast			// End of list indicator.               
};                                                
                                                  
/**
*  Need description for enumerator VCRINFO.

* <H3>Enumerators:</H3>
* <VAR>VCR_INFO_CANRECORD			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_DEVICECUE			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_OVERRUN				</VAR>: Need Descriptions <BR><BR>
* <VAR>VCR_INFO_STARTDELAY			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_EDITDELAY			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_EDITOFFDELAY		</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_TIMEFORMAT			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_BUMPPLAYPLUSFACTOR	</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_BUMPPLAYMINUSFACTOR	</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_CANINSERT			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_CANASSEMBLE			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_CANEJECT			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_AUDIOTRACKS			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_LTCTRACK			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_ACCURACY			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_NEEDCALIB			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_HASTBC				</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_HASTIMECODE			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_HASUSERBITS			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_HASVARIABLE			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_VARMAX				</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_VARNEG				</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_MEDIATYPE			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_JOGFACTOR			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_INFO_BUMPMETHOD			</VAR>: Need Descriptions <BR><BR>                                    
* @enum
*/
enum VCRINFO
{
   VCR_INFO_CANRECORD = 0,
   VCR_INFO_DEVICECUE,
   VCR_INFO_OVERRUN,
   VCR_INFO_STARTDELAY,
   VCR_INFO_EDITDELAY,
   VCR_INFO_EDITOFFDELAY,
   VCR_INFO_TIMEFORMAT,
   VCR_INFO_BUMPPLAYPLUSFACTOR,
   VCR_INFO_BUMPPLAYMINUSFACTOR,
   VCR_INFO_CANINSERT,
   VCR_INFO_CANASSEMBLE,
   VCR_INFO_CANEJECT,
   VCR_INFO_AUDIOTRACKS,
   VCR_INFO_LTCTRACK,
   VCR_INFO_ACCURACY,
   VCR_INFO_NEEDCALIB,
   VCR_INFO_HASTBC,
   VCR_INFO_HASTIMECODE,
   VCR_INFO_HASUSERBITS,
   VCR_INFO_HASVARIABLE,
   VCR_INFO_VARMAX,
   VCR_INFO_VARNEG,
   VCR_INFO_MEDIATYPE,
   VCR_INFO_JOGFACTOR,
   VCR_INFO_BUMPMETHOD
};

/**
*  Need description for enumerator DEVICEINFO
*
* <H3>Enumerators:</H3>
* <VAR>DEVICE_INFO_PORT					</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>DEVICE_INFO_BAUDRATE				</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>DEVICE_INFO_PARITY				</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>DEVICE_INFO_DATABITS				</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>DEVICE_INFO_STOPBITS				</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>DEVICE_INFO_NODE					</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>DEVICE_INFO_PREROLL				</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>DEVICE_INFO_USEDEVICECUE			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>DEVICE_INFO_CUETHRESHOLD			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>DEVICE_INFO_ACCURACY				</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>DEVICE_INFO_BESTPOSSIBLEACCURACY </VAR>: Need Descriptions <BR><BR>                                    
* <VAR>DEVICE_INFO_EDITDELAY			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>DEVICE_INFO_EDITOFFDELAY			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>DEVICE_INFO_CHECKCOLORFRAMELOCK	</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>DEVICE_INFO_INHIBITRECORDING		</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>DEVICE_INFO_READTIMECODE			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>DEVICE_INFO_TIMECODETYPE			</VAR>: Need Descriptions <BR><BR>                                    
*
* @enum
*/
enum DEVICEINFO
{
   DEVICE_INFO_PORT = 0,
   DEVICE_INFO_BAUDRATE,
   DEVICE_INFO_PARITY,
   DEVICE_INFO_DATABITS,
   DEVICE_INFO_STOPBITS,
   DEVICE_INFO_NODE,
   DEVICE_INFO_PREROLL,
   DEVICE_INFO_USEDEVICECUE,
   DEVICE_INFO_CUETHRESHOLD,
   DEVICE_INFO_ACCURACY,
   DEVICE_INFO_BESTPOSSIBLEACCURACY,
   DEVICE_INFO_EDITDELAY,
   DEVICE_INFO_EDITOFFDELAY,
   DEVICE_INFO_CHECKCOLORFRAMELOCK,
   DEVICE_INFO_INHIBITRECORDING,
   DEVICE_INFO_READTIMECODE,
   DEVICE_INFO_TIMECODETYPE
};

/**
*  Need description for enumerator PROTOCOLINFO.
*
* <H3>Enumerators:</H3>
* <VAR>PROTOCOL_INFO_BAUDRATE </VAR>: Need Descriptions <BR><BR>                                    
* <VAR>PROTOCOL_INFO_PARITY   </VAR>: Need Descriptions <BR><BR>                                    
* <VAR>PROTOCOL_INFO_DATABITS </VAR>: Need Descriptions <BR><BR>                                    
* <VAR>PROTOCOL_INFO_STOPBITS </VAR>: Need Descriptions <BR><BR>                                    
* @enum
*/
enum PROTOCOLINFO
{
   PROTOCOL_INFO_BAUDRATE = 0,
   PROTOCOL_INFO_PARITY,
   PROTOCOL_INFO_DATABITS,
   PROTOCOL_INFO_STOPBITS
};
                                                  

/**
*  Need description for enumerator VCRCOMMAND.
*
* <H3>Enumerators:</H3>
* <VAR>VCR_COMMAND_OTHER		</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_OPEN			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_CLOSE		</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_STOP			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_PLAY			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_PAUSE		</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_RECORD		</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_FORWARD		</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_REWIND		</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_SHUTTLE		</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_VAR			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_JOG			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_SEEK			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_CUE			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_CUECTL		</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_PERFORM		</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_EXITPERFORM	</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_STRIPE		</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_STEP			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_CALIBRATE	</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_EE			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_PB			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_GOTO			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_GETDEVCAPS	</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_INFO			</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_BUMPPLUS		</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_BUMPMINUS	</VAR>: Need Descriptions <BR><BR>                                    
* <VAR>VCR_COMMAND_STANDBY		</VAR>: Need Descriptions <BR><BR>                                    
*
* @enum
*/
enum VCRCOMMAND
{
   VCR_COMMAND_OTHER = 0,
   VCR_COMMAND_OPEN,
   VCR_COMMAND_CLOSE,
   VCR_COMMAND_STOP,
   VCR_COMMAND_PLAY,
   VCR_COMMAND_PAUSE,
   VCR_COMMAND_RECORD,
   VCR_COMMAND_FORWARD,
   VCR_COMMAND_REWIND,
   VCR_COMMAND_SHUTTLE,
   VCR_COMMAND_VAR,
   VCR_COMMAND_JOG,
   VCR_COMMAND_SEEK,
   VCR_COMMAND_CUE,
   VCR_COMMAND_CUECTL,
   VCR_COMMAND_PERFORM,
   VCR_COMMAND_EXITPERFORM,
   VCR_COMMAND_STRIPE,
   VCR_COMMAND_STEP,
   VCR_COMMAND_CALIBRATE,
   VCR_COMMAND_EE,
   VCR_COMMAND_PB,
   VCR_COMMAND_GOTO,
   VCR_COMMAND_GETDEVCAPS,
   VCR_COMMAND_INFO,
   VCR_COMMAND_BUMPPLUS,
   VCR_COMMAND_BUMPMINUS,
   VCR_COMMAND_STANDBY
};


/**
* EMvPlaybackSpeed: Tape speed information.
*
* kePlaybackSpeedInvalid  
* kePlaybackSpeedValid                The speed is indicated with a value.
* kePlaybackSpeedUnknown              The speed is unknown.
* kePlaybackSpeedLowerThan1_16th      The speed is less than 1/16X.
* kePlaybackSpeedEqualOrHigherThan60  The speed is equal or higher than 60X.
* kePlaybackSpeedLast
*/
enum EMvPlaybackSpeed
{
   kePlaybackSpeedInvalid = 0, 
   kePlaybackSpeedValid, 
   kePlaybackSpeedUnknown,
   kePlaybackSpeedLowerThan1_16th,
   kePlaybackSpeedEqualOrHigherThan60,
   kePlaybackSpeedLast
};

// Used for XDCAM EX and Z1U pulldown. 
enum EMvdPulldownType
{
   PullDownTypeNone = 0,
   PullDownType2_3,
   PullDownType3_2,
   PullDownType1_1,
   PullDownType2_2,
   PullDownType2_3_3_2,
   PullDownType24_25,
   PullDownTypeOther,
   PullDownTypeLast
};

// Used for reporting the maker of the encoded codec of the file.
enum EMvdEncoderID
{
   EncoderIDUnknown = 0,
   EncoderIDMatroxSW,
   EncoderIDMatroxHW,
   EncoderIDApple,
   EncoderIDSony,
   EncoderIDTypeLast
};

// Used for reporting the file origin for MP4 files, but could be used for other file types (such as MXF) when needed.
enum EMvdFileCreatorID
{
   FileCreatorIDUnknown = 0,
   FileCreatorIDMatrox,
   FileCreatorIDMS,
   FileCreatorIDApple,
   FileCreatorIDSony,
   FileCreatorIDPanasonic,
   FileCreatorIDOmneon,
   FileCreatorIDAVID,
   FileCreatorIDTypeLast
};

enum EMvMXFFileType
{
   MXFFileTypeNone = 0,
   MXFFileTypeAtomAudio,
   MXFFileTypeP2Video,
   MXFFileTypeXdcamD10,
   MXFFileTypeXdcamDvCam,
   MXFFileTypeXdcamDvCPro,
   MXFFileTypeXdcamHD420,
   MXFFileTypeXdcamHD422,
   MXFFileTypeGenericMpeg2,
   MXFFileTypeGenericMpeg2SparseIndex,
   MXFFileType_GC,
   MXFFileTypeOP1B,        // external essence
   MXFFileTypeAS02VBIType,
   MXFFileTypeAS03Type,
   MXFFileTypeAS11Type,
   MXFFileTypeOP1BInternal,
   MXFFileTypeAVCULongG,
   MXFFileTypeXAVCIntra,
   MXFFileTypeXAVCLongGOP,
   MXFFileTypeLast
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// START OF STRUCTURES
//


/**
* Provides media information.
* @struct
*/
struct SMvMediaInfo
{
   /** Structure size in bytes. */
   uint32_t               size; 
   /** Number of video streams. */
   unsigned long     ulNumOfVideoStreams;

   /**
   * Number of graphic streams. 
   */
   unsigned long     ulNumOfGraphicStreams;

   /**
   * Number of GFX streams. 
   */
   unsigned long     ulNumOfGFXStreams;

   /**
   * Number of audio streams. 
   */
   unsigned long       ulNumOfAudioStreams;

   /**
   * Channel type.
   */
   EMvChannelType      eChannelType;      
};

/**
* Provides the media type.
* @struct
*/
struct SMvMediaType
{
   /** Structure size in bytes. */
   uint32_t         size;

   /**
   * GUID of the media subtype. 
   */
   GUID           guidSubType;         
   /** Media info structure.*/
   SMvMediaInfo   sMediaInfo;
};

/**
* Provides the performance factor of all the available processor engines.
* @struct
*/
struct SMvEnginePerformanceFactors
{
   uint32_t   size;
   float    fCpuEngine;
   float    fIoDmaEngine;
   float    fFxDmaInputEngine;
   float    fFxDmaOutputEngine;
   float    fFx3DEngine;
   float    fLQScaler;
   float    fDisk;
   float    fDx3DEngine;
};

/**
* Rate description in number of elements per sequence.
* A value of 1/5 means use one element every 5 elements.
* @struct
*/
struct SMvRateDescription
{
   /** Structure size in bytes. */
   uint32_t        size;
   /** Number of elements per sequence (fraction numerator). */
   unsigned long ulElements;
   /** Sequence length (fraction denominator). */
   unsigned long ulSequenceLenght;
};

/**
* Defines all the parameters the sink switcher should use to load a file
* for native captures.
* @struct
*/
struct SMvSinkSwitcherLoadInfo
{
   /** Structure size in bytes. */
   uint32_t        size; 
   /** Name of file to capture. */
   wchar_t  *pwszFileName;
   /** Duration of file to capture. */
   uint64_t ui64DurationInFrames;
   /** Is the file in TimeDelay/InstantReplay Mode. */
   bool  bIsTDIR;
   /** If TDIR, the flush frequency in seconds.*/
   double dFlushFrequencyInSeconds;
   /** Custom file system IO interface to use. Use NULL for default. */
   IMvCustomFileSystemIO   *pIMvCustomFileIO;
   /** Custom file system CLSID. If IMvCustomFileSystemIO is set, this value will be ignored.*/
   CLSID clsidFileSystem;
   /** specifies at which frame AVI file should be truncated. */
   unsigned long ulTruncAtFrIx;
   /** This is to slow down the rate of writing to disk - useful for turbo compile on SAN.*/
   unsigned long ulDelayInMilliSeconds;
};

//
// Summary:
//    Describes the MPEG-specific file information used by the mvfFileInformation module.
//
struct SMvMpegFileInfo
{
   uint32_t size;                               // Indicates the structure size in bytes.
   double dBitRate;                             // Indicates the bit rate.
   uint32_t ui32NumberOfFramesBetweenI;         // Indicates the number of frames inside a group of pictures (GOP).
   uint32_t ui32NumberOfFramesBetweenIandP;     // Indicates the number of frames between consecutive I and P frames, or between two consecutive P frames.
   uint32_t ui32VBVBufferSize;                  // Indicates the Video Buffering Verifier (VBV) buffer size.
   EMvMPEG2Profile eProfile;                    // Indicates the MPEG-2 profile.
   EMvMPEG2Level eLevel;                        // Indicates the MPEG-2 level.
   bool bTopFieldFirst;                         // If true, the first field contains the top line (for example, PAL video).
   bool bConcealmentMotionVectors;              // If true, concealment motion vectors are present.
   bool bProgressiveFrame;                      // If true, the file contains progressive frames.
   double dSampleAspectRatio;                   // Indicates the aspect ratio of the video stream.
};

//
// Summary:
//    Describes the AVC-specific file information used by the mvfFileInformation module.
//
struct SMvAVCFileInfo
{
   uint32_t             size;                                  // Structure size in bytes.
   uint32_t             ui32GOPSizeInFrames;                   // Indicates the group of pictures (GOP) size of the given stream.
   uint32_t             ui32DistanceBetweenReferencesInFrames; // Indicates the distance between references in the given stream.
   uint32_t             ui32Profile;                           // Indicates the AVC profile.
   uint32_t             ui32Level;                             // Indicates the AVC level.
   uint32_t             ui32AverageBitRateInBitsPerSec;        // Indicates the average bit rate in bits per seconds of the stream.
   EMvGOPStructureType  eGOPStructureType;                     // Indicates the GOP structure type of the stream.   
};

//
// Summary:
//    Describes the Apple ProRes file information.
//
struct SMvProResFileInfo
{
   uint32_t             size;                                     // Structure size in bytes.
   uint32_t             ui32Profile;                              // Indicates the Apple ProRes profile (422, HQ, LT, Proxy, or 4444).
   EMvSurfaceFormat     eDecodingFormat;                          // Indicates the decoding format. 
   bool                 bHasAlpha;                                // If true, alpha is present. Otherwise, false.
};

//
// Summary:
//    Describes the VC-3 or DNxHD file information.
//
struct SMvDNxHDFileInfo
{
   uint32_t             size;          // Structure size in bytes.
   uint32_t             ui32Profile;   // Indicates the DNxHD or VC-3 profile (36, 145, 220, or 220x).
};

//
// Summary:
//    Describes the Matrox MPEG-4 Simple Studio Profile (SStP) file information.
//
struct SMvMPEG4SStPFileInfo
{
   uint32_t             size;                // Structure size in bytes.
   uint32_t             ui32Profile;         // Indicates the MPEG-4 SStP profile (422LT, 422SQ, 444SQ, or 444HQ).
   uint32_t             uiComponentBitCount; // Indicates the number of bits per component of a pixel.
};

//Describes the Sony XAVC file information.
struct SMvXAVCFileInfo
{
   uint32_t             size;                   // Structure size in bytes.
   uint32_t             ui32XAVCProfile;        // Indicates the Sony XAVC profile to use. For example, Sony XAVC LongGOP 25, 35, 50, or
                                                // Sony XAVC HD Intra Class 100, etc.
};


//
// Summary:
//    Contains the audio track information of a mov/mp4 file. 
//
struct SMvMovAudioTrackInfo
{
    uint32_t   ui32OffsetInSamples;             // offset in the MOV audio EDIT atom in the unit of samples
    uint32_t   ui32TrackChannelsCount;          // Number of channels with the offset.
};

//
// Summary:
//    Contains the audio and video specific information of a mov/mp4 file. 
//
struct SMvMOVSpecificFileInfo
{
   uint32_t size;
   uint64_t ui64VideoFrameCountFromMediaHeader;       // The number of video frame which gets from media header.
   uint64_t ui64VideoFrameCountFromTrackHeader;       // The number of video frame which gets from video track header.
   uint32_t ui32CountOfAudioTrackInfo;                     // Number of audio tracks info filled.
   SMvMovAudioTrackInfo  sMovAudioTrackInfo[16];      // An array of SMvMovAudioTrackInfo
};

//
// Summary:
//    Contains the audio and video information of a media file. 
//
struct SMvAudioVideoFileInfo
{
   uint32_t             size;                   // Structure size in bytes.
   unsigned long        ulVersion;              // Specifies the version information.
   unsigned long        ulNumVideoStreams;      // Specifies the number of video streams.
   unsigned long        ulAudioStreams;         // Specifies the number of audio streams. If a file contains multiple audio channel types, This value will be set to the total number of audio channels in the file, and the sWaveInfo.eChannelType will be set to keChannelTypeMono.
   EMvSurfaceFormat     eSurfaceFormat;         // Specifies the surface format enumerator. 
   SMvResolutionInfo    sResInfo;               // Specifies the resolution information. 
   EMvPolarity          ePolarity;              // Specifies the polarity. 
   SMvaWaveFormatInfo   sWaveInfo;              // Specifies the audio format information. 
   uint64_t             ui64VideoFrameCount;    // Specifies the number of frames in the file. 
                                                // This value does not include broken B frames 
                                                // or the start offset resulting from the time code. 
                                                // See the uiActualVideoFrameCount parameter to get 
                                                // all the frames physically stored in the file.
   uint64_t             ui64AudioSampleCount;   // Specifies the number of audio samples in the file. 
                                                // In case of multiple audio streams that have different 
                                                // durations, use the one with the shortest duration. See 
                                                // the uiActualAudioSampleCount parameter to get the sample 
                                                // count physically stored in the file.
   unsigned long        ulDataRate;             // Specifies the data rate in bits-per-second.
   uint64_t             ui64FileSize;           // Specifies the file size in bytes. 
   unsigned long        ulPitch;                // Specifies the pitch size of the surface. 
   bool                 bIsAligned;             // Specifies whether or not the start address of the data in the file is aligned to a boundary of 128 bytes.
   uint64_t             ui64ActualVideoFrameCount;    // Specifies the actual number of frames in the file. This value is greater than or equal to 
                                                // ui64VideoFrameCount because it takes into account broken Open GOPs at the beginning of 
                                                // the file, or is offset to the highest time code suggested in the file.
   uint64_t             ui64ActualAudioSampleCount;   // Specifies the actual number of audio samples in the file. This value is greater than or equal 
                                                // to ui64AudioSampleCount because it takes into account broken Open GOPs at the beginning of 
                                                // the file, or is offset to the highest time code suggested in the file.
   uint64_t             ui64OffsetFromActualStart;    // Specifies the amount that the read positions can be safely offset from the beginning (zero). 
                                                // This FrontOffset value, if specified, means that the ui64ActualVideoFrameCount value is 
                                                // larger than the ui64VideoFrameCount.
   bool                 bEmbeddedAudio;         // Specifies whether or not the audio is embedded.
   EMvColorimetry       eColorimetry;           // Specifies the colorimetry standard of the surface. Audio duration is in the unit of frames.

   EMvdEncoderID        eEncoderID;             // Enumerator used for reporting the maker of the encoded codec of the file.  

   EMvdPulldownType     ePullDownType;          // Type of pull down can be applied (ie material is 24 over 60).

   EMvdFileCreatorID    eFileCreatorID;         // Enumerator used for reporting the file origin for MP4, but it can also be used for other files (for example <I>.mxf</I>) if needed.

   bool                 bIsMpegFileInfoValid;   // Specifies if data in sMpegFileInfo is valid.

   SMvMpegFileInfo      sMpegFileInfo;          // File information specific to MPEG file types.

   bool                 bIsAVCFileInfoValid;    // Specifies if data in sAVCFileInfo is valid.

   SMvAVCFileInfo       sAVCFileInfo;           // File information specific to AVC file types.

   bool                 bIsProResFileInfoValid; // Specifies if data in sProResFileInfo is valid.
   SMvProResFileInfo    sProResFileInfo;        // 

   bool                 bIsDNxHDFileInfoValid;  // Specifies if data in sDNxHDFileInfo is valid.
   SMvDNxHDFileInfo     sDNxHDFileInfo;         // File information specific to VC-3 or DNxHD file types.

   bool                 bIsMPEG4SStPFileInfoValid;  // Specifies if data in sMPEG4SStPFileInfo is valid.
   SMvMPEG4SStPFileInfo sMPEG4SStPFileInfo;         // File information specific to MPEG-4 SStP file types.

   bool                 bIsXAVCFileInfoValid;   // Specifies if data in sXAVCFileInfo is valid.
   SMvXAVCFileInfo      sXAVCFileInfo;          // File information specific to XAVC file types.

   EMvMXFFileType       eMXFFileType;           // Specifies the MXF file types.
   unsigned long        ulVbiStreams;           // Specifies the number of VBI streams.
   unsigned long        ulANCStreams;           // Specifies the number of ANC streams.
   unsigned long        ulTCStreams;            // Specifies the number of TC streams.
   
   bool                 bSequentialAccess;      // Indicates whether or not a file is accessed sequentially. 
                                                // Due to the sequential nature of these files, seeking and trimming 
                                                // is much slower than random accessing. The time it takes to sequentially 
                                                // seek/trim-in is proportional to how much data needs to be parsed linearly in the file. 
                                                // Take care not to seek or trim-in too far into a new area by large steps, and 
                                                // instead seek or trim-in in small increments only.

   uint32_t             ui32PhysicalAudioTracksCount;  // The physical audio tracks count found in the file.

   uint32_t             ui32NumberOfAudioTypes;       // The number of audio types found in the file.
   
   SMvMOVSpecificFileInfo sMOVSpecificFileInfo;    //Specific file information for MOV file.
};

//
// Summary:
//    Contains the MGF file information.
//
struct SMvMGFFileInfo
{
   uint32_t            size;             // Structure size in bytes.
   unsigned long     ulVersion;        // Version of the file format.
   GUID              guidMGFType;      // Type of MGF file. Currently, it's GUID_MGF.
   EMvSurfaceFormat  eSurfaceFormat;   // Enum of the surface format. 
   SMvResolutionInfo sResInfo;         // Resolution information.
   unsigned long     ulPitch;          // Pitch size of the surface. 
};

//
// Summary:
//    Contains GFX file element descriptions.
//
struct SMvGFXElementDescription
{
   unsigned int      size;                // Structure size in bytes.
   EMvGFXElementType eType;               // Type of the element.
   unsigned long     ulElementNo;         // Element index.
   unsigned long     ulElementSize;       // Element size in bytes. 
   unsigned long     ulWidth;             // Width of the surface associated with the element. 
   unsigned long     ulHeight;            // Height of the surface associated with the element. 
   unsigned long     ulDepth;             // Number of bits per pixel. 
   EMvPolarity       ePolarity;           // Polarity of the surface associated with element. 
   unsigned long     ulRowPitchInBytes;   // Pitch size of the surface associated with the element. 
   unsigned long     ulSlicePitchInBytes; // Element slice pitch size. 
   unsigned long     ulComponentBitCount; // Element component bit count, can be 8 or 10. 
   EMvMemoryLocation eLocation;           // Element memory location, on board or host.  
   EMvSurfaceFormat  eFormat;             // Element surface format. 
   EMvColorimetry    eColorimetry;        // Element colorimetry. 
};



//
// Summary:
//    Contains GFX file element information.
//
struct SMvGFXElementInfo 
{
   uint64_t                   ui64Offset;       // The file offset of the GFX element in bytes.
   SMvGFXElementDescription   sGFXElementDesc;  // Element description. 
};

//
// Summary:
//    Contains information about the resolution in which the GFX has been created.
//
//
struct SMvGFXResolutionInfo
{
   unsigned int   size;                         // Structure size in bytes.
   bool           bSpecificWidth;               // If width is dependent. Width of some GFX files are
   // dependent on editing resolution.
   unsigned long  ulWidth;                      // Width of the GFX file. Ignored if bSpecificWidth is FALSE. 
   bool           bSpecificHeight;              // If height is dependent. Height of some GFX files are
   // dependent on editing resolution.
   unsigned long  ulHeight;                     // Height of the GFX file. Ignored if bSpecificHeight is FALSE. 
   bool           bSpecificComponentBitCount;   // If component bit count is dependent. Component bit
   // count of some GFX files are dependent on editing 
   // resolution.
   unsigned long  ulComponentBitCount;          // Component bit count of the GFX file. Ignored if 
   // bSpecificComponent is FALSE. 
   bool           bSpecificAspectRatio;         // If aspect ratio is dependent. Aspect ratio of some
   // GFX files are dependent on editing resolution.
   EMvAspectRatio eAspectRatio;                 // Aspect ratio of the GFX file, Ignored if 
   // bSpecificAspectRatio is FALSE. 
   bool           bSpecificScanMode;            // If scan mode is dependent. Scan mode of some
   // GFX files are dependent on editing resolution.
   EMvScanMode    eScanMode;                    // Scan mode of the GFX file. Ignored if bSpecificScanMode
   // is FALSE. 
   bool           bSpecificFrameRate;           // If frame rate is dependent. Frame rate of some GFX
   // files are dependent on editing resolution.
   EMvFrameRate   eFrameRate;                   // Frame rate of the GFX file. Ignored if 
   // bSpecificFrameRate is FALSE. 
};


//
// Summary:
//    Contains GFX file information.  This is the second revision of the structure.
// Remarks:
// - It is not the latest revision of the structure.
//
struct SMvGFXFileInfoV2
{
   unsigned int         size;                // Structure size in bytes.
   GUID                 guidFileType;        // GUID associated with the file. It must be CLSID_MvGFXFile.
   unsigned long        ulFileVersion;       // File version.
   GUID                 guidGFXType;         // GUID associated with the data type in the file.
   unsigned long        ulTypeVersion;       // Version of the type in the file. 
   unsigned long        ulHeaderSize;        // Size of the header.
   SMvGFXResolutionInfo sResInfo;            // Resolution info.
   unsigned long        ulNumberOfElements;  // Number of GFX elements in the file.
   unsigned long        ulNumberOfPicons;    // Number of GFX picons in the file.
};

//
// Summary:
//    Contains GFX file information. This is the third revision of the structure.
// Remarks:
// - This is the latest revision of the structure.  It is also defined as SMvGFXFileInfo.
//
struct SMvGFXFileInfoV3
{
   unsigned int         size;                // Structure size in bytes.
   GUID                 guidFileType;        // Specifies the UID associated with the file. It must be CLSID_MvGFXFile.
   unsigned long        ulFileVersion;       // Specifies the file version.
   GUID                 guidGFXType;         // Specifies the GUID associated with the data type in the file.
   unsigned long        ulTypeVersion;       // Specifies the version of the file type. 
   unsigned long        ulHeaderSize;        // Specifies the size of the header.
   SMvGFXResolutionInfo sResInfo;            // Specifies the resolution information.
   unsigned long        ulNumberOfElements;  // Specifies the number of GFX elements in the file.
   unsigned long        ulNumberOfPicons;    // Specifies the number of GFX picons in the file.
   unsigned long        ulNumberOfLinkedGFX; // Specifies the number of linked GFX files in the file.
};

//
// Summary:
//    Redefinition of the latest GFX file info structure.
typedef SMvGFXFileInfoV3 SMvGFXFileInfo;

/**
* Contains linked GFX information.
* @struct
*/
struct SMvLinkedGFXInfo
{
   /**
   * GFX name.
   */
   wchar_t wszGFXName[MAX_PATH];
   /**
   * Type of the GFX.
   */
   CLSID   sGFXType;
};



//
// Summary:
//    Contains GFX picon information.
//
struct SMvGFXPiconInfo
{
   unsigned long     ulPiconID;           // Picon ID.
   unsigned long     ulBitmapSizeInBytes; // Bitmap size.
#ifndef LINUX_PLATFORM
   BITMAPINFOHEADER  sBitmapInfoHeader;   // Bitmap info header.
#endif   
};


/**
* Structure used for node enumeration.
* @struct
*/
struct SMvTreeNodeInfo
{
   /** Structure size in bytes. */
   uint32_t               size; 
   /** Node type. */
   EMvTreeNodeType      eMvTreeNodeType;
   /** Node sub-type. */
   EMvTreeNodeSubType   eMvTreeNodeSubType;   
   /** Node index from connection link owner. */
   unsigned long        ulIndexInCurrentNode;
   /** Node index in node connected to. */
   unsigned long        ulIndexInNodeConnectedTo;
   /** Node interface. */
   IMvTreeNode*         pIMvTreeNode;
};

/**
* Structure for DV capture properties.
* @struct
*/
struct SMvDVCaptureProperties
{
   /**
   * Structure size in bytes.
   */
   uint32_t size ;

   /**
   * Version of this structure. 
   */
   int    iVersion ;

   /**
   * Resolution of the capture. 
   */
   SMvResolutionInfo smvRes ;

   /**
   * Type of DV derivations.
   */
   EMvDVType eDVType ;

   /**
   * Recreate incrementing time code in DV frames.
   */
   bool bRecreateIncrementingTimecode;

};

/** 
* Describes AVC capture properties.
* @struct
*/
struct SMvAVCCaptureProperties
{
   /**
   * Structure size in bytes. 
   */
   uint32_t size ;

   /**
   * Version of this structure definition. 
   */
   int    iVersion ;

   /**
   * Resolution information. 
   */
   SMvResolutionInfo smvResolution ;

   /**
   * H.264 profile.
   */
   EMvH264Profile       eProfile;

   /**
   * H.264 level. 
   */
   EMvH264Level         eLevel; 

   /**
   *   Requested average bit rate. 
   */
   uint32_t             ui32AverageBitRateInBitsPerSec; 

   /**
   *   Bit rate model to use. 
   */
   EMvBitRateModel      eBitRateMode; 

   /**
   *   Indicates the GOP structure type.  
   */
  
   EMvGOPStructureType  eGOPStructureType;   

   /**
   *   Indicates floating frame rate 10, 12, 12.5, 15...
   */
  
   float fFrameRate;   

   /**
   *   Indicates capturing GOP structure
   */
  
   SMvAVCCompressionGOPStructureOption  smvAVCGOPStructure;
};


/** 
* Describes H264SWEncoder2 capture properties.
* @struct
*/
struct SMvH264CaptureProperties
{
   /**
   * Structure size in bytes. 
   */
   uint32_t size ;

   /**
   * Version of this structure definition. 
   */
   int    iVersion ;

   /**
   * Resolution information. 
   */
   SMvResolutionInfo smvResolution ;

   /**
   * H.264/AVC software Preset.
   */
   EMvH264SWCodecPreset ePreset;

   /**
   *   Requested average bit rate. 
   */
   uint32_t  ui32AverageBitRateInBitsPerSec; 

   /**
   *   Bit rate model to use. 
   */
   EMvBitRateModel eBitRateMode; 

   /**
   *   Indicates is it Intra.  
   */
   EMvXAVCProfile  eXAVCProfile;   
};

//
// Summary:
// Describes the Apple ProRes capture properties.
//
struct SMvProResCaptureProperties
{
   uint32_t size;								// Structure size in bytes.
   int    iVersion;								// Indicates the version of this structure definition. 
   SMvResolutionInfo smvResolution;				// Indicates the resolution information. 
   EMvProResProfile  eProfile;					// Indicates the ProRes profile.
   EMvEncodingScanMode  eScanMode;				// Indicates the scan mode.
   uint32_t  ui32TargetCompressedFrameSize;		// Indicates the target compressed frame size.
};

//
// Summary:
// Describes the Matrox AVC-Intra capture properties.
//
struct SMvAVCIntraCaptureProperties
{
   uint32_t size;						// Structure size in bytes.
   int    iVersion;						// Indicates the version of this structure definition.
   SMvResolutionInfo smvResolution;		// Indicates the resolution information.
   EMvAVCIntraProfile       eProfile;	// Indicates the Matrox AVC-Intra profile.
};

//
// Summary:
//  Describes the Avid DNxHD capture properties.
//
struct SMvDNxHDCaptureProperties
{
   uint32_t size;						// Structure size in bytes.
   int    iVersion;						// Indicates the version of this structure definition.
   SMvResolutionInfo smvResolution;		// Indicates the resolution information.
   EMvDNxHDProfile  eProfile;			// Indicates the Avid DNxHD profile.
};

//
// Summary:
//  Describes the Matrox MPEG-4 Simple Studio Profile (SStP) capture properties.
//
struct SMvMPEG4SStPCaptureProperties
{
   uint32_t size;						      // Structure size in bytes.
   int    iVersion;						   // Indicates the version of this structure definition.
   SMvResolutionInfo smvResolution;		// Indicates the resolution information.
   EMvMPEG4SStPProfile eProfile;			// Indicates the MPEG-4 SStP Profile.
   uint32_t ulComponentBitCount;       // Indicates the component bit count to capture to the file.
};

/** 
* Describes MPEG-2 capture properties.
* @struct
*/
struct SMvMPEG2CaptureProperties
{
   /**
   * Structure size in bytes.
   */
   uint32_t size ;

   /**
   * Version of this structure definition. 
   */
   int    iVersion ;

   /**
   * Resolution information. 
   */
   SMvResolutionInfo smvRes ;

   /**
   * Initial starting time code in the bitstream. 
   */
   ULONG  ulStartTimeCode ;

   /**
   * MPEG-2 Profile. 
   */
   EMvMPEG2Profile emvProfile ;

   /**
   * MPEG-2 Level. 
   */
   EMvMPEG2Level   emvLevel ;

   /**
   * Bits per seconds. 
   */
   ULONG  ulDataRate ;

   /**
   *	Codec uses this to know how to encode data.
   */
   EMvMpeg2ZigZagType eMpeg2ZigZag;

   /**
   *	Codec uses this to know how to encode data.
   */
   EMvMpeg2RoundingType eRounding;

   /**
   *	Codec uses this to know how to encode data.
   */
   EMvMpeg2DCPrecision eDCPrecision;

   /**
   *	Codec uses this to know how to encode data.
   */
   bool bForceDCTFrame;

   /**
   *	Set to true if it is for HDV, and only the smvRes is needed to be initialized.
   */
   bool bIsHDV;

   /*
   * True if IBP is encoded.
   */
   bool bLongGOP;

   /*
   * True if it has opened B frames.
   */
   bool bOpenGOP;

   /*
   * If it is long GOP, state the maximum GOP size. 
   */
   unsigned long ulMaxGOP; 

   /*
   * Number of B frames in between reference frames. For example, XDCAM HD and HDV use two B frames.
   */ 
   unsigned long ulBPictureCount;

};
/**
* Describes D10 capture properties.
* @struct
*/
struct SMvD10CaptureProperties
{
   /**
   * Structure size in bytes.
   */
   uint32_t size ;

   /**
   * Version of this structure. 
   */
   int    iVersion ;

   /**
   * Resolution infomation. 
   */
   SMvResolutionInfo smvRes ;

   /**
   * Initial time code meta data.
   */
   ULONG  ulStartTimeCode ;


   /**
   * D10 data rate settings. Only 30, 40, and 50 are valid. It's in units of megabits per second.
   */
   ULONG  ulDataRate ; 
};


/**
* Describes HD-offline capture properties.
* @struct
*/
struct SMvHDOfflineCaptureProperties
{
   /**
   * Structure size in bytes.
   */
   uint32_t size ;

   /**
   * Version of this structure. 
   */
   int    iVersion ;

   /**
   * Resolution of the capture. 
   */
   SMvResolutionInfo smvRes ;

   /**
   * Initial time code meta data.
   * Not supported - must be 0.
   */
   ULONG  ulStartTimeCode ;
};


/**
* Structure for uncompressed capture.
* @struct
*/
struct SMvUncompressedCaptureProperties
{
   /**
   * Structure size in bytes.
   */
   uint32_t size ;

   /**
   * Version of this structure. 
   */
   int    iVersion ;

   /**
   * Initial time code metadata. 
   */
   ULONG  ulStartTimeCode ;

   /**
   * Resolution information. 
   */
   SMvResolutionInfo smvRes ;


   /**
   * Polarity of the frame. 
   * If the scan mode is interlaced, it should be keMvPolarityBackToBackFieldsInAFrame. 
   * If the scan mode is progressive, it should be keMvPolarityProgressiveFrame. 
   */
   EMvPolarity ePolarity ;

};



//
// Summary:
//    Used for file reading/writing. Same as the Win32 overlapped structure.
//
struct SMvOverlapped
{
   unsigned long  Internal;      // Internal usage.
   unsigned long  InternalHigh;  // Internal usage highpart. 
   unsigned long  Offset;        // Offset in byte.
   unsigned long  OffsetHigh;    // The high part of the offset to address 64-bit locations.
   HANDLE         hEvent;        // Event for completions. 
};


/**
* Describes the output types.
* @struct
*/
struct SMvOutputInfo
{
   /**  
    * Device ID.
    */
   unsigned long ulDeviceID;
   /**  
    * Output type.
    */
   EMvOutputDeviceType eOutputType;
   /**  
    * Output name.
    */
   char szOutputFriendlyName[256];
   /**  
    * Is is available.
    */
   bool bAvailable;
};

#ifndef LINUX_PLATFORM
/**
* Structure defining a ModifiedRegion notification. This notification is sent
* by a Parameters Provider to its observers when it is modified.
* The notification contains the in and out points of the modified region.
* It is a structure for convenience (no methods are needed) but it derives
* from the CMvSubjectContext class to travel in the Observer mechanism.
* @struct
*/
struct SMvParamProvModifiedRegionNotification : public CMvSubjectContext
{
   /**
   * Structure size in bytes. 
   */
   uint32_t size ;

   /**
   * In point (included) of the Parameters Provider's modified region. 
   */
   uint64_t ui64InPointInFrames;

   /**
   * Out point (excluded) of the Parameters Provider's modified region. 
   */
   uint64_t ui64OutPointInFrames;

};
#endif
/**
* Structure for parametric effect registration information.
* @struct
*/
struct SMvParamFxRegistrationInfo
{
   /**
   * Structure size in bytes.
   */
   uint32_t Size;

   /**
   * Name of the parametric effect.
   */
   wchar_t* wszParamFxName;

   /**
   * The GUID of the previous version of the parametric effect. 
   * If GUID_NULL, it indicates the parametric effect is the latest version.
   */
   GUID guidParamFxPreviousVersion;

   /**
   * Type of the Flex object represented by the parametric effect.
   * (This includes Video Compositor, Video Effects (filters and/or transitions), and Audio Mixer).
   */
   EMvParamFxFlexObjectType  eRepresentedFlexObjectType;

   /**
   * GUID of the Flex object represented by the ParamFx.
   */
   GUID guidRepresentedFlexObjectGUID;

   /**
   * If the ParamFx represents a Video Filter Effect, the number of sources required by that filter.
   * Otherwise, 0.
   */
   unsigned long ulNumOfVideoFilterSources;
};

/**
* Structure for additional external device information.
* @struct
*/
struct SMvAdditionalExtDeviceInfo
{
   /**
   * Structure size in bytes.
   */
   uint32_t Size;

   /**
   * Additional Matrox information.
   */
   wchar_t* wszAdditionalMatroxInfo;
};


/**
* Structure for device control description.
* @struct
*/
struct SMvDeviceControlDescriptor
{
   /**
   * Structure size in bytes. 
   */
   uint32_t Size;

   /**
   * If there are multiple devices of the same types in a system, this is the index of the particular device being refered to.
   */
   long lIndex;

   /**
   * A device should be listed even if its currently in use. When a device descriptor is returned, it indicates that the device exists (attached to the system), but this flag needs to be checked to verify if it the device is currently available.
   * 
   * Note: The device could become unavailable between enumerating devices, and actually setting the desired device.
   */
   bool bAvailable;

   /**
   * CLSID of the device. This value may be invalid if bAvailable is false.
   */
   CLSID clsidDeviceID;
   /*
    *	Description of the manufacture of the device
    */
   char lpszDeviceName[256];
};   

/**
* Structure for device control command (internal use, from old device control code).
* @struct
*/
struct SMvProtocolCommand
{
   /**
   * Command in protocol of 9-Pin RS-422 connector format.
   */
   char acInBuffer[20];

   /**
   * Size, in bytes, of the acInBuffer.
   */
   unsigned long ulBytesToSend;

   /**
   * Response data in protocol of 9-Pin RS-422 connector format.
   */
   char acOutBuffer[20];

   /**
   * Size, in bytes, of the acOutBuffer.
   */
   unsigned long ulBytesReturned;
};


/**
* Structure for device control synchronization (internal use, from old device control code).
* @struct
*/
struct SMvDigiVTRSynchro
{
   /**
   * Time code in current time format.
   */
   unsigned long	ulTimecode;

   /**
   * System clock value.
   */
   uint64_t	ui64SystemClock;

   /**
   * System clock value in Nano time
   */
	uint64_t	ui64SystemClockInNano;

   /**
   * Non-zero when VTR is playing and servo locked.
   */
   bool	bServoLocked;
};

//
// Summary:
//    Structure of exported MGF version 2 file information for writer utility.
//
struct SMvMGF2ImageInfo 
{
   uint32_t            Size;                // Structure size in bytes.
   unsigned long     ulTotalWidth;        // Width of the file in pixels.
   unsigned long     ulTotalHeight;       // Height of the file in lines.
   unsigned long     ulPitch;             // Line pitch of the file in bytes.
   unsigned long     ulComponentBitCount; // Components Y,U,V,A size (8 or 10 bits).
   EMvSurfaceFormat  eSurfaceFormat;      // Surface data format (YUAYVA 4224, or YUV 422).
   EMvPixelRatio     ePixelRatio;         // Pixel aspect ratio.
   EMvImageOrigin    eImageOrigin;        // Origin of the file.
};

//
// Summary:
//    Contains the information for an exported MGF version 2 file for the reader utility.
//
struct SMvMGF2FileInfo
{
   uint32_t            Size;                // Structure size in bytes.
   GUID              guidFileTypeID;      // Specifies the MGF file GUID.
   DWORD             dwVersionID;         // Specifies the MGF file version.
   DWORD             dwPrivateDataSize;   // Specifies the size of the private data in bytes.
   unsigned long     ulWidth;             // Specifies the width of the file in pixels.
   unsigned long     ulHeight;            // Specifies the height of the file in pixels.
   unsigned long     ulPitch;             // Specifies the pitch size of the surface.
   unsigned long     ulComponentBitCount; // Specifies the component YUVA bit count (8 or 10-bit).
   EMvSurfaceFormat  eSurfaceFormat;      // Specifies the surface format (YUVA 4:2:2:4 or YUV 4:2:2).
   EMvPixelRatio     ePixelRatio;         // Specifies the pixel aspect ratio.
   EMvImageOrigin    eImageOrigin;        // Specifies the origin of the file.  
};

//
// Summary:
//    Super structure that contains information for various file types, including audio and/or video files, MGF files, and GFX files. 
//
struct SMvFileInfo
{
   uint32_t      size;                      // Structure size in bytes.
   EMvFileInfo eFileInfo;                 // File type.
   union UNFileInfo 
   {
      SMvAudioVideoFileInfo   sAVInfo;    // Audio and/or video file information.
      SMvMGF2FileInfo         sMGF2Info;  // MGF file information.
      SMvGFXFileInfo          sGFXInfo;   // GFX file information.
   } unInfo;                              // Information container depending on the file type. It 
                                             // could be any of the types below.

};


//Definition of type MTXTC.
typedef long unsigned int MTXTC;
#ifndef LINUX_PLATFORM
typedef MTXTC near * PMTXTC;
typedef MTXTC far * LPMTXTC;
#else
typedef MTXTC * PMTXTC;
typedef MTXTC * LPMTXTC;
#endif

/**
* Need description for MTX_EDIT_POINT.
* @struct
*/
struct MTX_EDIT_POINT_PARMS
{
   /**
   * Need Description
   */
   DWORD   dwTrack;

   /**
   * Need Description
   */
   MTXTC   mtxtcLocation;

   /**
   * Need Description
   */
   MTXTC   mtxtcDuration;

   /**
   * Need Description
   */
   DWORD   dwPrecision;

   /**
   * Need Description
   */
   int     nVideoDelay;

};
typedef MTX_EDIT_POINT_PARMS  *LPMTX_EDIT_POINT_PARMS;

/**
* Need description for ProtocolCommand.
* @struct
*/
struct MXVCR_PROTOCOLCOMMAND
{
   /**
   * Need Description
   */
   BYTE  InBuffer[20];

   /**
   * Need Description
   */
   ULONG ulBytesToSend;

   /**
   * Need Description
   */
   BYTE  OutBuffer[20];

   /**
   * Need Description
   */
   ULONG ulBytesReturned;

};
typedef MXVCR_PROTOCOLCOMMAND *PMXVCR_PROTOCOLCOMMAND;

/**
* Need description for Synchro.
* @struct
*/
struct MXVCR_SYNCHRO
{
   /**
   * Need Description
   */
   ULONG ulTimecode;

   /**
   * Need Description
   */
   uint64_t ui64SystemClock;

	uint64_t ui64SystemClockInNano;

   /**
   * Need Description
   */
   BOOL  bServoLocked;

};
typedef MXVCR_SYNCHRO *PMXVCR_SYNCHRO;


/**
* Structure to be used with the IMvRIFFChunkIO interface.
* @struct
*/
struct SMvRIFFChunksInLIST
{
   /**
   * The 4CC of the chunk.
   */
   unsigned long ulChunkFourCC;

   /**
   * Size of the chunk pointer. 
   */
   unsigned long ulChunkSize;

   /**
   * Data in the chunk.
   */
   char * pChunkBuffer;

};

/**
* Information retrieved from the source device (camera or tape) for a frame.
*/
struct SMvSourceDeviceFrameInfo
{
   uint32_t               size;                      // Size for versioning validation.

   bool                 bTimeCodeFound;            // Indicates if time code is valid.
   unsigned long        ulTimeCodeInFrames;        // Time code in absolute frames.
   unsigned long        ulTimeCodeBCD;             // Time code in BCD HH:MM:SS:FF.
   unsigned long        ulLastTimeCodeInFrames;    // Time code in absolute frames that this frame is valid upto. To handle 24p in 60p syntax and 25p in 50p syntax.
   unsigned long        ulLastTimeCodeBCD;         // Time code in BCD HH:MM:SS:FF that this frame is valid upto. To handle 24p in 60p syntax and 25p in 50p syntax.

   bool                 bRecordTimeFound;          // Indicates if record time (DV frame) is valid. 
   unsigned long        ulRecordTimeInFrames;      // Record time in absolute frames.
   unsigned long        ulRecordTimeBCD;           // Record time in BCD HH:MM:SS:FF.

   bool                 bRecordDateFound;          // Indicates if record date (DV frame) is valid.
   unsigned long        ulRecordDateBCD;           // Record date in BDC TZ:DD:MM:YY.

   bool                 bRecordStartPoint;         // Indicates if record start point (DV frame) is set. 
   bool                 bRecordEndPoint;           // Indicates if record end point (DV frame) is set.

   bool                 bPlaybackDirectionForward; // Indicates if the tape plays back in a forward direction.
   EMvPlaybackSpeed     eSpeedInfo;                // Speed information.
   float                fPlaybackSpeed;            // Speed of the tape (if eSpeedInfo == EPlaybackSpeedValid).

   bool                 bPullDownSeqValid;         // Indicates if the pulldown sequence is valid.
   EMvPullDownSequence  ePullDownSeq;              // Type of pulldown sequence (such as 3:2 or advanced).
   bool                 bFrameOfSeqValid;          // Frame of sequence is valid.
   EMvFrameOfSequence   eFrameOfSeq;               // Frame of sequence (such as A, B, C, X or D).

   bool                 bInputIsLost;              // The input stream is lost.
   bool                 bBlackOrSilence;           // This buffer is black or silence.
   bool                 bRepeatedBuffer;           // This buffer is a repeated buffer because there is no valid data at the input.
   bool                 bDontWriteToFileStreamLost;// Don't write this buffer to file because the stream is lost. 

   bool                 bFrameChangedFlag;         // Frame change flag from DV frame 0-same as previous, 1-different picture.
   
   bool                 bIsDropFrame;              // Drop frame or non-drop frame.

   EMvSurfaceFormat     eSurfaceFormat;            // format of the surface: DV25, DV50...

   SMvResolutionInfo    sResolutionInfo;

   bool                 b720pCaptureFlagsValid;
   bool                 b720pCaptureFlag_Capture1stFrame;
   bool                 b720pCaptureFlag_Capture2ndFrame;
   unsigned long        ul720pCaptureShootingFrameRate;

};

struct SMvUIFStreamingInfo 
{
   uint32_t               size;                      // Size for versioning validation.
   EMvPolarity ePolarityToUseForUpscale;
};


struct SMvFileVideoDurationInfo 
{
   uint32_t       size;                 // Size for versioning validation.
   uint64_t       ui64Duration;         // Duration for consolidation
   uint64_t       ui64Origin;           // Origin
   bool           bSetStartTimecode;    // the flag to adjust TC in Clip's metadata 
   bool           bTrimmed;             // Is trimmed-in or -out during this consolidation
};

/**
* AV Type
*/
enum EMvMessageInfoAVType
{
   keMvMessageInfoAVTypeInvalid = 0,
   keMvMessageInfoAVTypeVideo,
   keMvMessageInfoAVTypeAudio,
   keMvMessageInfoAVTypeAudioVideo,
   keMvMessageInfoAVTypeLast
};

/**
* Outputs Scaling Type.
*/
enum EMvScalingMode
{
   keMvScalingModeInvalid = 0,
   keMvScalingModeLetterBox,
   keMvScalingModeAnamorphic,
   keMvScalingModeCenterCut,
   keMvScalingModeLast
};


// DOM-IGNORE-BEGIN

/// copy of edevdefs.h to prevent the need to install Win plat for OEM (needed by VC8)
#ifndef ED_BASE
#define ED_BASE                     0x1000L

// this is used to tell the device communications object which
// physical communications port to use.
#define DEV_PORT_SIM    1
#define DEV_PORT_COM1   2   // standard serial ports.
#define DEV_PORT_COM2   3
#define DEV_PORT_COM3   4
#define DEV_PORT_COM4   5
#define DEV_PORT_DIAQ   6   // Diaquest driver.
#define DEV_PORT_ARTI   7   // ARTI driver.
#define DEV_PORT_1394   8   // IEEE 1394 Bus.
#define DEV_PORT_USB    9   // Universal Serial Bus.
#define DEV_PORT_MIN    DEV_PORT_SIM
#define DEV_PORT_MAX    DEV_PORT_USB


//  IAMExtDevice Capability Items:  unless otherwise specified, these items return 
//     OATRUE or OAFALSE.  All return values are in pdwValue unless otherwise specified:
#define ED_DEVCAP_CAN_RECORD            ED_BASE+1L
#define ED_DEVCAP_CAN_RECORD_STROBE     ED_BASE+2L  // for multitrack devices: 
// switches currently recording tracks off 
// and selected non-recording tracks into record
#define ED_DEVCAP_HAS_AUDIO         ED_BASE+3L
#define ED_DEVCAP_HAS_VIDEO         ED_BASE+4L
#define ED_DEVCAP_USES_FILES        ED_BASE+5L
#define ED_DEVCAP_CAN_SAVE          ED_BASE+6L

#define ED_DEVCAP_DEVICE_TYPE       ED_BASE+7L      // returns one of the following:
#define ED_DEVTYPE_VCR              ED_BASE+8L
#define ED_DEVTYPE_LASERDISK        ED_BASE+9L
#define ED_DEVTYPE_ATR              ED_BASE+10L
#define ED_DEVTYPE_DDR              ED_BASE+11L
#define ED_DEVTYPE_ROUTER           ED_BASE+12L
#define ED_DEVTYPE_KEYER            ED_BASE+13L
#define ED_DEVTYPE_MIXER_VIDEO      ED_BASE+14L
#define ED_DEVTYPE_DVE              ED_BASE+15L
#define ED_DEVTYPE_WIPEGEN          ED_BASE+16L
#define ED_DEVTYPE_MIXER_AUDIO      ED_BASE+17L
#define ED_DEVTYPE_CG               ED_BASE+18L
#define ED_DEVTYPE_TBC              ED_BASE+19L
#define ED_DEVTYPE_TCG              ED_BASE+20L
#define ED_DEVTYPE_GPI              ED_BASE+21L
#define ED_DEVTYPE_JOYSTICK         ED_BASE+22L
#define ED_DEVTYPE_KEYBOARD         ED_BASE+23L

// returns mfr-specific ID from external device.
#define ED_DEVCAP_EXTERNAL_DEVICE_ID    ED_BASE+24L

#define ED_DEVCAP_TIMECODE_READ     ED_BASE+25L
#define ED_DEVCAP_TIMECODE_WRITE    ED_BASE+26L
//  used for seekable non-timecode enabled devices
#define ED_DEVCAP_CTLTRK_READ       ED_BASE+27L
//  used for seekable non-timecode enabled devices
#define ED_DEVCAP_INDEX_READ        ED_BASE+28L

// returns device preroll time in current time format
#define ED_DEVCAP_PREROLL           ED_BASE+29L
// returns device postroll time in current time format
#define ED_DEVCAP_POSTROLL          ED_BASE+30L

// returns indication of device's synchronization accuracy.
#define ED_DEVCAP_SYNC_ACCURACY     ED_BASE+31L // returns one of the following:
#define ED_SYNCACC_PRECISE          ED_BASE+32L
#define ED_SYNCACC_FRAME            ED_BASE+33L
#define ED_SYNCACC_ROUGH            ED_BASE+34L

// returns device's normal framerate.
#define ED_DEVCAP_NORMAL_RATE   ED_BASE+35L // returns one of the following:
#define ED_RATE_24              ED_BASE+36L
#define ED_RATE_25              ED_BASE+37L
#define ED_RATE_2997            ED_BASE+38L
#define ED_RATE_30              ED_BASE+39L

#define ED_DEVCAP_CAN_PREVIEW   ED_BASE+40L
#define ED_DEVCAP_CAN_MONITOR_SOURCES   ED_BASE+41L

// indicates implementation allows testing of methods/parameters by
// setting the hi bit of a parm that makes sense - see individual methods
// for details.
#define ED_DEVCAP_CAN_TEST          ED_BASE+42L

// indicates device accepts video as an input.
#define ED_DEVCAP_VIDEO_INPUTS      ED_BASE+43L

// indicates device accepts audio as an input.
#define ED_DEVCAP_AUDIO_INPUTS      ED_BASE+44L

#define ED_DEVCAP_NEEDS_CALIBRATING ED_BASE+45L

#define ED_DEVCAP_SEEK_TYPE         ED_BASE+46L // returns one of the following:
#define ED_SEEK_PERFECT             ED_BASE+47L // indicates device can execute seek 
// within 1 video frames without signal 
//  break (like a DDR)
#define ED_SEEK_FAST                ED_BASE+48L // indicates device can move pretty quick 
//  with short break in signal
#define ED_SEEK_SLOW                ED_BASE+49L // seeks like a tape transport

#define ED_POWER_ON                 ED_BASE+50L
#define ED_POWER_OFF                ED_BASE+51L
#define ED_POWER_STANDBY            ED_BASE+52L

#define ED_ACTIVE                   ED_BASE+53L
#define ED_INACTIVE                 ED_BASE+54L
#define ED_ALL                      ED_BASE+55L
#define ED_TEST                     ED_BASE+56L

//  IAMExtTransport Capability Items:  unless otherwise specified, these items return 
//     OATRUE or OAFALSE.  All return values are in pdwValue unless otherwise specified:

#define ED_TRANSCAP_CAN_EJECT           ED_BASE+100L
#define ED_TRANSCAP_CAN_BUMP_PLAY       ED_BASE+101L    // variable speed for synchronizing.
#define ED_TRANSCAP_CAN_PLAY_BACKWARDS  ED_BASE+102L    // servo locked for use during an edit.
#define ED_TRANSCAP_CAN_SET_EE          ED_BASE+103L    // shows device's input on its output.
#define ED_TRANSCAP_CAN_SET_PB          ED_BASE+104L    // shows media playback on device's output.
#define ED_TRANSCAP_CAN_DELAY_VIDEO_IN  ED_BASE+105L    // transport can do delayed-in video edits.
#define ED_TRANSCAP_CAN_DELAY_VIDEO_OUT ED_BASE+106L    // transport can do delayed-out video edits.
#define ED_TRANSCAP_CAN_DELAY_AUDIO_IN  ED_BASE+107L    // transport can do delayed-in audio edits.
#define ED_TRANSCAP_CAN_DELAY_AUDIO_OUT ED_BASE+108L    // transport can do delayed-out audio edits.
#define ED_TRANSCAP_FWD_VARIABLE_MAX    ED_BASE+109L    // max forward speed (multiple of play speed) 
//  in pdblValue.
#define ED_TRANSCAP_FWD_VARIABLE_MIN    ED_BASE+800L    // min forward speed (multiple of play speed) 
//  in pdblValue.
#define ED_TRANSCAP_REV_VARIABLE_MAX    ED_BASE+110L    // max reverse speed (multiple of play speed) in
//  pdblValue.
#define ED_TRANSCAP_REV_VARIABLE_MIN    ED_BASE+801L    // min reverse speed (multiple of play speed)
//  in pdblValue.
#define ED_TRANSCAP_FWD_SHUTTLE_MAX     ED_BASE+802L    // max forward speed in Shuttle mode (multiple
//  of play speed) in pdblValue.
#define ED_TRANSCAP_FWD_SHUTTLE_MIN     ED_BASE+803L    // min forward speed in Shuttle mode (multiple
//  of play speed) in pdblValue.
#define ED_TRANSCAP_REV_SHUTTLE_MAX     ED_BASE+804L    // max reverse speed in Shuttle mode (multiple
//  of play speed) in pdblValue.
#define ED_TRANSCAP_REV_SHUTTLE_MIN     ED_BASE+805L    // min reverse speed in Shuttle mode (multiple
//  of play speed) in pdblValue.
#define ED_TRANSCAP_NUM_AUDIO_TRACKS    ED_BASE+111L    // returns number of audio tracks
#define ED_TRANSCAP_LTC_TRACK           ED_BASE+112L    // returns track number of LTC timecode track
//  ED_ALL means no dedicated timecode track.
#define ED_TRANSCAP_NEEDS_TBC           ED_BASE+113L    // device's output not stable
#define ED_TRANSCAP_NEEDS_CUEING        ED_BASE+114L    // device must be cued prior to performing edit.
#define ED_TRANSCAP_CAN_INSERT          ED_BASE+115L
#define ED_TRANSCAP_CAN_ASSEMBLE        ED_BASE+116L
#define ED_TRANSCAP_FIELD_STEP          ED_BASE+117L    // device responds to Frame Advance command by 
//  advancing one field.
#define ED_TRANSCAP_CLOCK_INC_RATE      ED_BASE+118L    // VISCA command - keep for compatibility.
#define ED_TRANSCAP_CAN_DETECT_LENGTH   ED_BASE+119L
#define ED_TRANSCAP_CAN_FREEZE          ED_BASE+120L
#define ED_TRANSCAP_HAS_TUNER           ED_BASE+121L
#define ED_TRANSCAP_HAS_TIMER           ED_BASE+122L
#define ED_TRANSCAP_HAS_CLOCK           ED_BASE+123L
#define ED_TRANSCAP_MULTIPLE_EDITS      ED_BASE+806L    // OATRUE means device/filter can support
//  multiple edit events.
#define ED_TRANSCAP_IS_MASTER           ED_BASE+807L    // OATRUE means device is the master clock
//  for synchronizing (this sets timecode-to-
//  reference clock offset for editing).
#define ED_TRANSCAP_HAS_DT              ED_BASE+814L    // OATRUE means device has Dynamic Tracking

//  IAMExtTransport Media States
#define ED_MEDIA_SPIN_UP            ED_BASE+130L
#define ED_MEDIA_SPIN_DOWN          ED_BASE+131L
#define ED_MEDIA_UNLOAD             ED_BASE+132L

//  IAMExtTransport Modes
#define ED_MODE_PLAY                ED_BASE+200L
#define ED_MODE_STOP                ED_BASE+201L
#define ED_MODE_FREEZE              ED_BASE+202L    // really "pause"
#define ED_MODE_THAW                ED_BASE+203L
#define ED_MODE_FF                  ED_BASE+204L
#define ED_MODE_REW                 ED_BASE+205L
#define ED_MODE_RECORD              ED_BASE+206L
#define ED_MODE_RECORD_STROBE       ED_BASE+207L
#define ED_MODE_RECORD_FREEZE       ED_BASE+808L    // never "put", only "get"
#define ED_MODE_STEP                ED_BASE+208L    // same as "jog"
#define ED_MODE_STEP_FWD            ED_BASE+208L    // same as ED_MODE_STEP
#define ED_MODE_STEP_REV            ED_BASE+809L
#define ED_MODE_SHUTTLE             ED_BASE+209L
#define ED_MODE_EDIT_CUE            ED_BASE+210L
#define ED_MODE_VAR_SPEED           ED_BASE+211L
#define ED_MODE_PERFORM             ED_BASE+212L    // returned status only
#define ED_MODE_LINK_ON             ED_BASE+280L
#define ED_MODE_LINK_OFF            ED_BASE+281L
#define ED_MODE_NOTIFY_ENABLE       ED_BASE+810L
#define ED_MODE_NOTIFY_DISABLE      ED_BASE+811L
#define ED_MODE_SHOT_SEARCH         ED_BASE+812L

//  IAMTimecodeReader/Generator/Display defines
//
// Timecode Generator Mode params and values:
//
#define ED_TCG_TIMECODE_TYPE        ED_BASE+400L    // can be one of the following:
#define ED_TCG_SMPTE_LTC            ED_BASE+401L
#define ED_TCG_SMPTE_VITC           ED_BASE+402L
#define ED_TCG_MIDI_QF              ED_BASE+403L
#define ED_TCG_MIDI_FULL            ED_BASE+404L

#define ED_TCG_FRAMERATE            ED_BASE+405L    // can be one of the following:
#define ED_FORMAT_SMPTE_30          ED_BASE+406L
#define ED_FORMAT_SMPTE_30DROP      ED_BASE+407L
#define ED_FORMAT_SMPTE_25          ED_BASE+408L
#define ED_FORMAT_SMPTE_24          ED_BASE+409L

#define ED_TCG_SYNC_SOURCE          ED_BASE+410L    // can be one of the following:
#define ED_TCG_VIDEO                ED_BASE+411L
#define ED_TCG_READER               ED_BASE+412L
#define ED_TCG_FREE                 ED_BASE+413L

#define ED_TCG_REFERENCE_SOURCE     ED_BASE+414L    // can have one these values:
//  ED_TCG_FREE || ED_TCG_READER 
//  (for regen/jamsync)

// TimeCodeReader Mode params and values:
#define ED_TCR_SOURCE           ED_BASE+416L    // can be one of the following:
// ED_TCG (already defined)
#define ED_TCR_LTC              ED_BASE+417L
#define ED_TCR_VITC             ED_BASE+418L
#define ED_TCR_CT               ED_BASE+419L    // Control Track
#define ED_TCR_FTC              ED_BASE+420L    // File TimeCode - for file-based devices
//  that wish they were transports
// ED_MODE_NOTIFY_ENABLE can be OATRUE or OAFALSE (defined in transport mode
//  section of this file).  
#define ED_TCR_LAST_VALUE       ED_BASE+421L    // for notification mode - 
//  successive calls to GetTimecode
//  return the last read value
// TimeCode Display Mode params and values:
//
#define ED_TCD_SOURCE           ED_BASE+422L    // can be one of the following:
#define ED_TCR                  ED_BASE+423L
#define ED_TCG                  ED_BASE+424L

#define ED_TCD_SIZE             ED_BASE+425L    // can be one of the following:
#define ED_SMALL                ED_BASE+426L
#define ED_MED                  ED_BASE+427L
#define ED_LARGE                ED_BASE+428L

#define ED_TCD_POSITION         ED_BASE+429L    // can be one of the following:
#define ED_TOP                  0x0001
#define ED_MIDDLE               0x0002
#define ED_BOTTOM               0x0004          // OR'd with
#define ED_LEFT                 0x0100
#define ED_CENTER               0x0200
#define ED_RIGHT                0x0400

#define ED_TCD_INTENSITY        ED_BASE+436L    // can be one of the following:
#define ED_HIGH                 ED_BASE+437L
#define ED_LOW                  ED_BASE+438L

#define ED_TCD_TRANSPARENCY     ED_BASE+439L    // 0-4, 0 is opaque

#define ED_TCD_INVERT           ED_BASE+440L    // OATRUE=black on white
// OAFALSE=white on black
//  IAMExtTransport defines
//
// Transport status, params and values
//

// IAMExtTransport Status items and and values:
#define ED_MODE                 ED_BASE+500L    // see ED_MODE_xxx values above
#define ED_ERROR                ED_BASE+501L
#define ED_LOCAL                ED_BASE+502L
#define ED_RECORD_INHIBIT       ED_BASE+503L
#define ED_SERVO_LOCK           ED_BASE+504L
#define ED_MEDIA_PRESENT        ED_BASE+505L
#define ED_MEDIA_LENGTH         ED_BASE+506L
#define ED_MEDIA_SIZE           ED_BASE+507L
#define ED_MEDIA_TRACK_COUNT    ED_BASE+508L
#define ED_MEDIA_TRACK_LENGTH   ED_BASE+509L
#define ED_MEDIA_SIDE           ED_BASE+510L

#define ED_MEDIA_TYPE           ED_BASE+511L    // can be one of the following:
#define ED_MEDIA_VHS            ED_BASE+512L
#define ED_MEDIA_SVHS           ED_BASE+513L
#define ED_MEDIA_HI8            ED_BASE+514L
#define ED_MEDIA_UMATIC         ED_BASE+515L
#define ED_MEDIA_DVC            ED_BASE+516L
#define ED_MEDIA_1_INCH         ED_BASE+517L
#define ED_MEDIA_D1             ED_BASE+518L
#define ED_MEDIA_D2             ED_BASE+519L
#define ED_MEDIA_D3             ED_BASE+520L
#define ED_MEDIA_D5             ED_BASE+521L
#define ED_MEDIA_DBETA          ED_BASE+522L
#define ED_MEDIA_BETA           ED_BASE+523L
#define ED_MEDIA_8MM            ED_BASE+524L
#define ED_MEDIA_DDR            ED_BASE+525L
#define ED_MEDIA_SX             ED_BASE+813L
#define ED_MEDIA_OTHER          ED_BASE+526L
#define ED_MEDIA_CLV            ED_BASE+527L
#define ED_MEDIA_CAV            ED_BASE+528L
#define ED_MEDIA_POSITION       ED_BASE+529L

#define ED_LINK_MODE            ED_BASE+530L    // OATRUE if transport controls
// are linked to graph's RUN, 
// STOP, and PAUSE methods

// IAMExtTransport Basic Parms
#define ED_TRANSBASIC_TIME_FORMAT   ED_BASE+540L    // can be one of the following:
#define ED_FORMAT_MILLISECONDS      ED_BASE+541L
#define ED_FORMAT_FRAMES            ED_BASE+542L
#define ED_FORMAT_REFERENCE_TIME    ED_BASE+543L

#define ED_FORMAT_HMSF              ED_BASE+547L
#define ED_FORMAT_TMSF              ED_BASE+548L

#define ED_TRANSBASIC_TIME_REFERENCE    ED_BASE+549L    // can be one of the following:
#define ED_TIMEREF_TIMECODE         ED_BASE+550L
#define ED_TIMEREF_CONTROL_TRACK    ED_BASE+551L
#define ED_TIMEREF_INDEX            ED_BASE+552L

#define ED_TRANSBASIC_SUPERIMPOSE       ED_BASE+553L    // enable/disable onscreen display
#define ED_TRANSBASIC_END_STOP_ACTION   ED_BASE+554L    // can be one of: ED_MODE_STOP |
//  ED_MODE_REWIND | ED_MODE_FREEZE
#define ED_TRANSBASIC_RECORD_FORMAT ED_BASE+555L    // can be one of the following:
#define ED_RECORD_FORMAT_SP         ED_BASE+556L
#define ED_RECORD_FORMAT_LP         ED_BASE+557L
#define ED_RECORD_FORMAT_EP         ED_BASE+558L

#define ED_TRANSBASIC_STEP_COUNT    ED_BASE+559L
#define ED_TRANSBASIC_STEP_UNIT     ED_BASE+560L    // can be one of the following:
#define ED_STEP_FIELD               ED_BASE+561L
#define ED_STEP_FRAME               ED_BASE+562L
#define ED_STEP_3_2                 ED_BASE+563L

#define ED_TRANSBASIC_PREROLL       ED_BASE+564L
#define ED_TRANSBASIC_RECPREROLL    ED_BASE+565L
#define ED_TRANSBASIC_POSTROLL      ED_BASE+566L
#define ED_TRANSBASIC_EDIT_DELAY    ED_BASE+567L
#define ED_TRANSBASIC_PLAYTC_DELAY  ED_BASE+568L
#define ED_TRANSBASIC_RECTC_DELAY   ED_BASE+569L
#define ED_TRANSBASIC_EDIT_FIELD    ED_BASE+570L
#define ED_TRANSBASIC_FRAME_SERVO   ED_BASE+571L
#define ED_TRANSBASIC_CF_SERVO      ED_BASE+572L
#define ED_TRANSBASIC_SERVO_REF     ED_BASE+573L    // can be one of the following:
#define ED_REF_EXTERNAL             ED_BASE+574L
#define ED_REF_INPUT                ED_BASE+575L
#define ED_REF_INTERNAL             ED_BASE+576L
#define ED_REF_AUTO                 ED_BASE+577L

#define ED_TRANSBASIC_WARN_GL       ED_BASE+578L
#define ED_TRANSBASIC_SET_TRACKING  ED_BASE+579L    // can be one of the following:
#define ED_TRACKING_PLUS            ED_BASE+580L
#define ED_TRACKING_MINUS           ED_BASE+581L
#define ED_TRACKING_RESET           ED_BASE+582L

#define ED_TRANSBASIC_SET_FREEZE_TIMEOUT    ED_BASE+583L
#define ED_TRANSBASIC_VOLUME_NAME       ED_BASE+584L
#define ED_TRANSBASIC_BALLISTIC_1       ED_BASE+585L    // space for proprietary data
#define ED_TRANSBASIC_BALLISTIC_2       ED_BASE+586L
#define ED_TRANSBASIC_BALLISTIC_3       ED_BASE+587L
#define ED_TRANSBASIC_BALLISTIC_4       ED_BASE+588L
#define ED_TRANSBASIC_BALLISTIC_5       ED_BASE+589L
#define ED_TRANSBASIC_BALLISTIC_6       ED_BASE+590L
#define ED_TRANSBASIC_BALLISTIC_7       ED_BASE+591L
#define ED_TRANSBASIC_BALLISTIC_8       ED_BASE+592L
#define ED_TRANSBASIC_BALLISTIC_9       ED_BASE+593L
#define ED_TRANSBASIC_BALLISTIC_10      ED_BASE+594L
#define ED_TRANSBASIC_BALLISTIC_11      ED_BASE+595L
#define ED_TRANSBASIC_BALLISTIC_12      ED_BASE+596L
#define ED_TRANSBASIC_BALLISTIC_13      ED_BASE+597L
#define ED_TRANSBASIC_BALLISTIC_14      ED_BASE+598L
#define ED_TRANSBASIC_BALLISTIC_15      ED_BASE+599L
#define ED_TRANSBASIC_BALLISTIC_16      ED_BASE+600L
#define ED_TRANSBASIC_BALLISTIC_17      ED_BASE+601L
#define ED_TRANSBASIC_BALLISTIC_18      ED_BASE+602L
#define ED_TRANSBASIC_BALLISTIC_19      ED_BASE+603L
#define ED_TRANSBASIC_BALLISTIC_20      ED_BASE+604L

// consumer VCR items
#define ED_TRANSBASIC_SETCLOCK          ED_BASE+605L
#define ED_TRANSBASIC_SET_COUNTER_FORMAT    ED_BASE+606L    // uses time format flags
#define ED_TRANSBASIC_SET_COUNTER_VALUE ED_BASE+607L

#define ED_TRANSBASIC_SETTUNER_CH_UP    ED_BASE+608L
#define ED_TRANSBASIC_SETTUNER_CH_DN    ED_BASE+609L
#define ED_TRANSBASIC_SETTUNER_SK_UP    ED_BASE+610L
#define ED_TRANSBASIC_SETTUNER_SK_DN    ED_BASE+611L
#define ED_TRANSBASIC_SETTUNER_CH       ED_BASE+612L
#define ED_TRANSBASIC_SETTUNER_NUM      ED_BASE+613L

#define ED_TRANSBASIC_SETTIMER_EVENT    ED_BASE+614L
#define ED_TRANSBASIC_SETTIMER_STARTDAY ED_BASE+615L
#define ED_TRANSBASIC_SETTIMER_STARTTIME    ED_BASE+616L
#define ED_TRANSBASIC_SETTIMER_STOPDAY  ED_BASE+617L
#define ED_TRANSBASIC_SETTIMER_STOPTIME ED_BASE+618L

// IAMExtTransport video parameters
#define ED_TRANSVIDEO_SET_OUTPUT    ED_BASE+630L    // can be one of the following:
#define ED_E2E                      ED_BASE+631L
#define ED_PLAYBACK                 ED_BASE+632L
#define ED_OFF                      ED_BASE+633L

#define ED_TRANSVIDEO_SET_SOURCE    ED_BASE+634L

// IAMExtTransport audio parameters
#define ED_TRANSAUDIO_ENABLE_OUTPUT ED_BASE+640L    // can be the following:
#define ED_AUDIO_ALL                0x10000000      //  or any of the following OR'd together
#define ED_AUDIO_1                  0x0000001L
#define ED_AUDIO_2                  0x0000002L
#define ED_AUDIO_3                  0x0000004L
#define ED_AUDIO_4                  0x0000008L
#define ED_AUDIO_5                  0x0000010L
#define ED_AUDIO_6                  0x0000020L
#define ED_AUDIO_7                  0x0000040L
#define ED_AUDIO_8                  0x0000080L
#define ED_AUDIO_9                  0x0000100L
#define ED_AUDIO_10                 0x0000200L
#define ED_AUDIO_11                 0x0000400L
#define ED_AUDIO_12                 0x0000800L
#define ED_AUDIO_13                 0x0001000L
#define ED_AUDIO_14                 0x0002000L
#define ED_AUDIO_15                 0x0004000L
#define ED_AUDIO_16                 0x0008000L
#define ED_AUDIO_17                 0x0010000L
#define ED_AUDIO_18                 0x0020000L
#define ED_AUDIO_19                 0x0040000L
#define ED_AUDIO_20                 0x0080000L
#define ED_AUDIO_21                 0x0100000L
#define ED_AUDIO_22                 0x0200000L
#define ED_AUDIO_23                 0x0400000L
#define ED_AUDIO_24                 0x0800000L
#define ED_VIDEO                    0x2000000L  // for Edit props below

#define ED_TRANSAUDIO_ENABLE_RECORD     ED_BASE+642L
#define ED_TRANSAUDIO_ENABLE_SELSYNC    ED_BASE+643L
#define ED_TRANSAUDIO_SET_SOURCE        ED_BASE+644L
#define ED_TRANSAUDIO_SET_MONITOR       ED_BASE+645L


// Edit Property Set-related defs

// The following values reflect (and control) the state of an 
// edit property set
#define ED_INVALID      ED_BASE+652L
#define ED_EXECUTING    ED_BASE+653L
#define ED_REGISTER     ED_BASE+654L
#define ED_DELETE       ED_BASE+655L

// Edit property set parameters and values
#define ED_EDIT_HEVENT  ED_BASE+656L    // event handle to signal event 
// completion
#define ED_EDIT_TEST    ED_BASE+657L    // returns OAFALSE if filter thinks
//  edit can be done, OATRUE if not
#define ED_EDIT_IMMEDIATE   ED_BASE+658L    // OATRUE means start put the 
// device into edit mode (editing
// "on the fly") immediately upon
//  execution of Mode(ED_MODE_EDIT_CUE)
#define ED_EDIT_MODE    ED_BASE+659L
// can be one of the following values:
#define ED_EDIT_MODE_ASSEMBLE       ED_BASE+660L
#define ED_EDIT_MODE_INSERT         ED_BASE+661L
#define ED_EDIT_MODE_CRASH_RECORD   ED_BASE+662L
#define ED_EDIT_MODE_BOOKMARK_TIME  ED_BASE+663L        // these two are for
#define ED_EDIT_MODE_BOOKMARK_CHAPTER   ED_BASE+664L    // laserdisks

#define ED_EDIT_MASTER  ED_BASE+666L    // OATRUE causes device 
//  not to synchronize

#define ED_EDIT_TRACK       ED_BASE+667L
// can be one of the following possible OR'd values:
//  ED_VIDEO, ED_AUDIO_1 thru ED_AUDIO_24 (or ED_AUDIO_ALL)

#define ED_EDIT_SRC_INPOINT     ED_BASE+668L    // in current time format
#define ED_EDIT_SRC_OUTPOINT    ED_BASE+669L    // in current time format
#define ED_EDIT_REC_INPOINT     ED_BASE+670L    // in current time format
#define ED_EDIT_REC_OUTPOINT    ED_BASE+671L    // in current time format

#define ED_EDIT_REHEARSE_MODE   ED_BASE+672L
// can be one of the following possible values:
#define ED_EDIT_BVB     ED_BASE+673L    // means rehearse the edit with 
//  "black-video-black"
#define ED_EDIT_VBV     ED_BASE+674L
#define ED_EDIT_VVV     ED_BASE+675L
#define ED_EDIT_PERFORM ED_BASE+676L    // means perform the edit with no 
//  rehearsal.

// Set this property to OATRUE to kill the edit if in progress
#define ED_EDIT_ABORT   ED_BASE+677L
// how long to wait for edit to complete
#define ED_EDIT_TIMEOUT ED_BASE+678L        // in current time format

// This property causes the device to seek to a point specified by
// ED_EDIT_SEEK_MODE (see below).  NOTE: Only one event at a time can seek.
#define ED_EDIT_SEEK        ED_BASE+679L    // OATRUE means do it now.  
#define ED_EDIT_SEEK_MODE   ED_BASE+680L
//possible values:
#define ED_EDIT_SEEK_EDIT_IN    ED_BASE+681L    // seek to edit's inpoint
#define ED_EDIT_SEEK_EDIT_OUT   ED_BASE+682L    // seek to edit's outpoint
#define ED_EDIT_SEEK_PREROLL    ED_BASE+683L    // seek to edit's 
//  inpoint-preroll
#define ED_EDIT_SEEK_PREROLL_CT ED_BASE+684L    // seek to preroll point 
// using control track (used for tapes with 
// discontinuoustimecode before edit point: seek
// to inpoint using timecode, then backup to 
// preroll point using control track)
#define ED_EDIT_SEEK_BOOKMARK   ED_BASE+685L    // seek to bookmark (just like 
//  timecode search)
// This property is used for multiple-VCR systems where each machine must
//  cue to a different location relative to the graph's reference clock.  The
//  basic idea is that an edit event is setup with an ED_EDIT_OFFSET property
//  that tells the VCR what offset to maintain between it's timecode (converted
//  to reference clock units) and the reference clock.
#define ED_EDIT_OFFSET  ED_BASE+686L        // in current time format

#define ED_EDIT_PREREAD ED_BASE+815L        // OATRUE means device supports
//  pre-read (recorder can also be
//  player

//
// Some error codes:
// 
// device could be in local mode
#define ED_ERR_DEVICE_NOT_READY     ED_BASE+700L

#define ED_MODE_PLAY_FASTEST_FWD       ED_BASE+933L
#define ED_MODE_PLAY_SLOWEST_FWD       ED_BASE+934L
#define ED_MODE_PLAY_FASTEST_REV       ED_BASE+935L
#define ED_MODE_PLAY_SLOWEST_REV       ED_BASE+936L


#endif // #ifndef ED_BASE
// DOM-IGNORE-END

// Edit functions supported by device for print to tape.  If the device doesn't support edits, a Record command
// must be sent to device.  A large mark in offset is usually required in this case.  A different mark out offset is
// probably needed in this case also.  In auto edit mode, we set the mark in, mark out and preroll values on the device
// and the device should take care of the edit.  In this case mark in and mark out should be accurate and we don't need any
// offset.  In basic edit mode, we play the device and send an edit on and an edit off when we reach the mark in and mark out.
// In this case a start and end offset could be required, but should have the same values.
enum EMvDeviceEditFunctionality
{
   keMvDeviceEditFunctionalityNone,
   keMvDeviceEditFunctionalityAuto,
   keMvDeviceEditFunctionalityBasic
};

#define ED_TRANSBASIC_EDIT_OFF_DELAY    ED_BASE+800L  // Custom parameter so we can adjust the mark out timecode offset.


typedef DWORD_PTR HEVENT;

#ifndef LINUX_PLATFORM
/// We don't want to require DXSDK in VC8.
#ifndef __IAMExtTransport_INTERFACE_DEFINED__
#define __IAMExtTransport_INTERFACE_DEFINED__

EXTERN_C const IID IID_IAMExtTransport;

MIDL_INTERFACE("A03CD5F0-3045-11cf-8C44-00AA006B6814")
IAMExtTransport : public IUnknown
{
public:
   virtual HRESULT STDMETHODCALLTYPE GetCapability( 
      /* [in] */ long Capability,
      /* [out] */ long *pValue,
      /* [out] */ double *pdblValue) = 0;

      virtual HRESULT STDMETHODCALLTYPE put_MediaState( 
      /* [in] */ long State) = 0;

      virtual HRESULT STDMETHODCALLTYPE get_MediaState( 
      /* [out] */ long *pState) = 0;

      virtual HRESULT STDMETHODCALLTYPE put_LocalControl( 
      /* [in] */ long State) = 0;

      virtual HRESULT STDMETHODCALLTYPE get_LocalControl( 
      /* [out] */ long *pState) = 0;

      virtual HRESULT STDMETHODCALLTYPE GetStatus( 
      /* [in] */ long StatusItem,
      /* [out] */ long *pValue) = 0;

      virtual HRESULT STDMETHODCALLTYPE GetTransportBasicParameters( 
      /* [in] */ long Param,
      /* [out] */ long *pValue,
      /* [out] */ LPOLESTR *ppszData) = 0;

      virtual HRESULT STDMETHODCALLTYPE SetTransportBasicParameters( 
      /* [in] */ long Param,
      /* [in] */ long Value,
      /* [in] */ LPCOLESTR pszData) = 0;

      virtual HRESULT STDMETHODCALLTYPE GetTransportVideoParameters( 
      /* [in] */ long Param,
      /* [out] */ long *pValue) = 0;

      virtual HRESULT STDMETHODCALLTYPE SetTransportVideoParameters( 
      /* [in] */ long Param,
      /* [in] */ long Value) = 0;

      virtual HRESULT STDMETHODCALLTYPE GetTransportAudioParameters( 
      /* [in] */ long Param,
      /* [out] */ long *pValue) = 0;

      virtual HRESULT STDMETHODCALLTYPE SetTransportAudioParameters( 
      /* [in] */ long Param,
      /* [in] */ long Value) = 0;

      virtual HRESULT STDMETHODCALLTYPE put_Mode( 
      /* [in] */ long Mode) = 0;

      virtual HRESULT STDMETHODCALLTYPE get_Mode( 
      /* [out] */ long *pMode) = 0;

      virtual HRESULT STDMETHODCALLTYPE put_Rate( 
      /* [in] */ double dblRate) = 0;

      virtual HRESULT STDMETHODCALLTYPE get_Rate( 
      /* [out] */ double *pdblRate) = 0;

      virtual HRESULT STDMETHODCALLTYPE GetChase( 
      /* [out] */ long *pEnabled,
      /* [out] */ long *pOffset,
      /* [out] */ HEVENT *phEvent) = 0;

      virtual HRESULT STDMETHODCALLTYPE SetChase( 
      /* [in] */ long Enable,
      /* [in] */ long Offset,
      /* [in] */ HEVENT hEvent) = 0;

      virtual HRESULT STDMETHODCALLTYPE GetBump( 
      /* [out] */ long *pSpeed,
      /* [out] */ long *pDuration) = 0;

      virtual HRESULT STDMETHODCALLTYPE SetBump( 
      /* [in] */ long Speed,
      /* [in] */ long Duration) = 0;

      virtual HRESULT STDMETHODCALLTYPE get_AntiClogControl( 
      /* [out] */ long *pEnabled) = 0;

      virtual HRESULT STDMETHODCALLTYPE put_AntiClogControl( 
      /* [in] */ long Enable) = 0;

      virtual HRESULT STDMETHODCALLTYPE GetEditPropertySet( 
      /* [in] */ long EditID,
      /* [out] */ long *pState) = 0;

      virtual HRESULT STDMETHODCALLTYPE SetEditPropertySet( 
      /* [out][in] */ long *pEditID,
      /* [in] */ long State) = 0;

      virtual HRESULT STDMETHODCALLTYPE GetEditProperty( 
      /* [in] */ long EditID,
      /* [in] */ long Param,
      /* [out] */ long *pValue) = 0;

      virtual HRESULT STDMETHODCALLTYPE SetEditProperty( 
      /* [in] */ long EditID,
      /* [in] */ long Param,
      /* [in] */ long Value) = 0;

      virtual HRESULT STDMETHODCALLTYPE get_EditStart( 
      /* [out] */ long *pValue) = 0;

      virtual HRESULT STDMETHODCALLTYPE put_EditStart( 
      /* [in] */ long Value) = 0;

};

#endif 	/* __IAMExtTransport_INTERFACE_DEFINED__ */
#endif // ! LINUX_PLATFORM
#endif // _MVDDEF_H
// END OF INCLUDE
