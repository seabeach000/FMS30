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

// Forward declarations
interface IMvReaderStreamElement;
interface IMvTransferStream;
interface IMvEncoderStream;
interface IMvDecoderStream;
interface IMvMuxerStream;
interface IMvRTPSenderStream;
interface IMvCompressedWriterStream;
interface IMvEchoStream;
interface IMvCompressedHostNode;
interface IMvRTPReceiverStream;
interface IMvNodeNotificationCallback;
interface IMvSystemClockUniversal;

//
// Summary:
//    Describes the state information of a video or audio sample buffer (IMvSurface or IMvAudioSamples).
//
struct SMvPoolBufferState
{
   uint32_t ui32Size;               // Indicates the structure size in bytes.
   wchar_t  wszName[80];            // Indicates the name of the buffer.
   uint32_t ui32ReferenceCount;     // Indicates the COM reference count used to manage the object's lifetime.
   uint32_t ui32ReadCount;          // Indicates the number of read operations that are to be completed on a buffer after the write operations
                                    // on the buffer have been completed. This is usually one or two read operations.
   uint32_t ui32WriteCount;         // Indicates the number of write operations that are to be completed on a buffer before it is ready to be read
                                    // by one or more read operations.
   bool     bIsWriteCompleted;      // If true, the write operations on the buffer are completed.
   bool     bIsReadCompleted;       // If true, the read operations on the buffer are completed.
   HRESULT  hrReadError;            // Indicates the first read operation error that occurred.
   HRESULT  hrWriteError;           // Indicates the first write operation error that occurred.
};


//
// Summary:
//    Describes the transfer stream settings.
//
struct SMvTransferStreamSettings
{
   uint32_t ui32Size;                    // Indicates the structure size in bytes.
   uint64_t ui64AdvancedDelayInNanoTime; // Indicates the delay (in nanotime) that will be applied to a transfer stream's
                                         // input. The value must be frame aligned. The advanced delay must be less 
                                         // than the node depth minus the node's write-to-read delay minus three frames.
                                         // That is, <p>
                                         // <i> Advance delay < node depth - node's write-to-read delay - 3 frames </i>
   EMvNodeContent eNodeContentToProcess; // Indicates the type of data in the stream to process. For example, video data only, VANC data only, or 
                                         // any other data combination.
};


//
// Summary:
//    Describes the demuxer stream settings.
//
struct SMvDemuxerStreamSettings
{
   uint32_t ui32Size; // Indicates the structure size in bytes.
};


//
// Summary:
//    Describes the parameters of the node notification callback.
// Remarks:
//    - When this structure is registered with IMvHostNode::RegisterCallbackForWrite(),
//      the user application can set the time code parameters.
//
struct SMvNodeNotificationCallbackParameters
{
   uint32_t         ui32Size;                // Indicates the structure size in bytes.
   IMvNode*         pINode;                  // Pointer to the node that generated the notification.
   uint64_t         ui64Timestamp;           // Indicates the time at which the data is valid.
   uint64_t         ui64UseBefore;           // Indicates the time at which the data pointed by pVideoBuffer, 
                                             // pAudioBuffer, pAncBuffer and the time code parameters will no longer be usable by
                                             // the user application. Past this time the node content may not be the expected data.
   uint32_t         ui32Width;               // Usable width of the video and ancillary buffers in pixels.
   uint32_t         ui32VideoHeight;         // Usable height of the video data in lines.
   uint32_t         ui32VideoRowPitchInBytes;// Indicates the size (in bytes) of one video line including padding.
   EMvSurfaceFormat eVideoFormat;            // Indicates the data organization of the video data.
   uint8_t*         pVideoBuffer;            // Pointer to the start of the video data buffer.
   uint32_t         ui32AudioSize;           // Indicates the size (in bytes) of the audio data. 
   uint8_t*         pAudioBuffer;            // Pointer to the start of the audio data buffer.
   uint32_t         ui32AncHeight;           // Usable height of the ancillary data in lines.
   uint32_t         ui32AncRowPitchInBytes;  // Indicates the size (in bytes) of one YUYV 4:2:2 VANC line including padding.
   EMvSurfaceFormat eAncFormat;              // Indicates the data organization of the ancillary data.
   uint8_t*         pAncBuffer;              // Pointer to the start of the ancillary data.
   
   bool*            pbVITCPresent;           // If true, vertical interval time code (VITC) is present.
   uint64_t*        pui64VITCValue;          // Pointer to the start of the VITC value.
   bool*            pbLTCPresent;            // If true, linear time code (LTC) is present.
   uint64_t*        pui64LTCValue;           // Pointer to the start of the LTC value.
   bool*            pbAnalogLTCPresent;      // If true, analog LTC is present.
   uint64_t*        pui64AnalogLTCValue;     // Pointer to the start of the analog LTC value.
};


//
// Summary:
//    Describes the host node callback notification settings.
//
struct SMvHostNodeRegistrationInfo
{
   uint32_t                      ui32Size;            // Indicates the structure size in bytes.
   IMvNodeNotificationCallback * pICallback;          // Pointer to the node notification callback interface.
   EMvNodeContent                eContentToProcess;   // Indicates the type of data that will be provided to or received by the host node callback notification. 
};

//
// Summary:
//    Describes the encoder stream settings.
//
struct SMvEncoderStreamSettings
{
   uint32_t ui32Size;                    // Indicates the structure size in bytes.
   uint64_t ui64AdvancedDelayInNanoTime; // Indicates the delay (in nanotime) that will be applied to an encoder stream's
                                         // input. The value must be frame aligned. The advanced delay must be less 
                                         // than the node depth minus the node's write-to-read delay minus three frames.
                                         // That is, <p>
                                         // <i> Advance delay < node depth - node's write-to-read delay - 3 frames </i>
   bool bProcessVanc;                    // If true, VANC data is sent to the encoder stream for processing.
};


//
// Summary:
//    Describes the muxer stream settings.
//
struct SMvMuxerStreamSettings
{
   uint32_t                         ui32Size;                        // Indicates the structure size in bytes.
   uint16_t                         ui16ProgramPID;                  // Specifies the packet ID of the unique program contained in the stream.
   uint16_t                         ui16VideoPID;                    // Specifies the packet ID of the video elementary stream.
   uint16_t                         ui16AudioPID;                    // Specifies the packet ID of the audio elementary stream.
   uint16_t                         ui16VancPID;                     // Specifies the packet ID of the VANC elementary stream.
   uint16_t                         ui16PCRPID;                      // Specifies the packet ID of the Program Clock Reference (PCR) elementary stream.
   EMvMPEG2MuxerBitRateOption       eMPEG2MuxerBitRateOption;        // Specifies the bit rate encoding option of the stream. The recommended option for streaming is variable bit rate (VBR).
   EMvMPEG2MuxerVancProcessingType  eMPEG2MuxerVancProcessingType;   // Specifies the type of the elements to process in the VANC. Currently, only SCTE 35 streams are supported.
};                                                                            


//
// Summary:
//    Describes the compression settings of the Matrox MPEG-2 IBP encoder.
//
struct SMvMPEG2IBPCompressionOptions
{
   uint32_t                                ui32Size;             // Indicates the structure size in bytes.
   SMvMpegStreamEncoderSettings            sIbpSettings;          // Indicates video encoding parameters specific to 
                                                                  // the MPEG-1 and MPEG-2 IBP format.
   SMvMpegStreamAudioEncoderSettings       sIbpAudioSettings;     // Indicates audio encoding parameters specific to 
                                                                  // the MPEG-1 and MPEG-2 IBP format.
   SMvMpegStreamMultiplexerEncoderSettings sIbpMultiplexSettings; // Indicates multiplexer encoding parameters specific 
                                                                  // to the MPEG-1 and MPEG-2 IBP format.
};

//
// Summary:
//    Describes the compression settings of the DV100 encoder.
//
struct SMvDV100CompressionOptions
{
   uint32_t                               ui32Size;          // Indicates the structure size in bytes.
   SMvResolutionInfo                      sResInfo;          // Indicates the encoding resolution.
};


//
// Summary:
//    Specifies the writer stream event that occurred.
//
enum EMvWriterStreamEvent
{
   keMvWriterStreamEventInvalid,    // Invalid value.
   keMvWriterStreamEventStarted,    // The writer stream started writing to a file.
   keMvWriterStreamEventStopped,    // The writer stream stopped writing to a file.
   keMvWriterStreamEventFileOpened, // The writer stream opened a file for writing.
   keMvWriterStreamEventFileClosed, // The writer stream closed a file for writing.
   keMvWriterStreamEventErrorCode,  // The writer stream encountered an internal error. For example,
                                    // a warning  whose error code constant starts with MV_W_xxx.
   keMvWriterStreamEventRecorded,   // The writer stream captured a frame in the file.
   keMvWriterStreamEventLast        // End of list indicator.
};


//
// Summary:
//    Specifies whether the writer stream opened or closed the file.
//
struct SMvWriterStreamEventFile
{
   wchar_t wszFilepath[MAX_PATH];   // Indicates the file name and path of the writer stream event.
   HANDLE hFileHandle;              // Handle to the file of the writer stream event.
};


//
// Summary:
//    Specifies when the writer stream started or stopped capturing to the file.
//
struct SMvWriterStreamEventOperation
{
   wchar_t  wszFilepath[MAX_PATH];     // Indicates the file name and path of the writer stream event.
   uint64_t ui64Timestamp;             // Indicates the time (in nanotime) that the operation occurred.
   uint64_t ui64FrameCount;            // Indicates the frame count corresponding to when the operation occurred.
};


//
// Summary:
//    Specifies how many frames the writer stream captured to the file.
//
struct SMvWriterStreamEventRecorded
{
   wchar_t  wszFilepath[MAX_PATH];     // Indicates the file name and path of the writer stream event.
   uint64_t ui64FrameCount;            // Indicates the frame count corresponding to the number of frames that were captured to the file.
};


//
// Summary:
//    Specifies the error code the writer stream encountered.
//
struct SMvWriterStreamEventError
{
   wchar_t wszFilepath[MAX_PATH];      // Indicates the file name and path of the writer stream event.
   HRESULT hrErrorCode;                // Indicates the error code that occurred.
   uint64_t ui64FrameCount;            // Indicates the frame count corresponding to when the error was encountered.
};


//
// Summary:
//    Provides details of the writer stream event notification.
//
struct SMvWriterStreamEvent
{
   uint32_t ui32Size;            // Structure size in bytes.
   EMvWriterStreamEvent eEvent;  // Indicates the writer stream event that occurred. The user application can then use the 
                                 // appropriate structure for more details.
   union
   {
      SMvWriterStreamEventOperation sEventStart;         // Indicates when the writer stream started the event.
      SMvWriterStreamEventOperation sEventStop;          // Indicates when the writer stream stopped the event.
      SMvWriterStreamEventFile      sEventFileOpened;    // Indicates when the writer stream opened the file.
      SMvWriterStreamEventFile      sEventFileClosed;    // Indicates when the writer stream closed the file.
      SMvWriterStreamEventRecorded  sEventRecorded;      // Indicates how many frames the writer stream captured.
      SMvWriterStreamEventError     sEventError;         // Indicates the error code of the event.
   };
};


//
// Summary:
//    Describes the generic writer stream's settings.
// Remarks:
//    - At least bRecordVideo or bRecordAudio must be set to true. However, if the writer stream supports both
//      video and audio, both bRecordVideo and bRecordAudio can be set to true.
//
struct SMvWriterStreamSettings
{
   uint32_t    ui32Size;                                    // Structure size in bytes.
   bool        bRecordVideo;                                // If true, video data is captured.
   bool        bRecordAncillaryData;                        // If true, VANC data is captured. Applicable only if bRecordVideo is set to true.
   bool        bOverrideTimeCode;                           // If true, the time code value indicated in this structure is used as the initial time code.
   uint32_t    ui32TimeCodeHour;                            // Hour value of the time code.
   uint32_t    ui32TimeCodeMinute;                          // Minute value of the time code.
   uint32_t    ui32TimeCodeSecond;                          // Second value of the time code.
   uint32_t    ui32TimeCodeFrame;                           // Frame value of the time code.
   bool        bRecordAudio;                                // If true, audio data is captured.
   bool        bTDIR;                                       // If true, time delay instant replay (TDIR) is applied.
   double      dTDIRFlushFrequencyInSeconds;                // If bTDIR is set to true, indicates the flush frequency in seconds.
   uint64_t    ui64ReserveSpaceForEndOfDiskCheckInBytes;    // Indicates the amount of disk space to reserve before the writer stream determines that the end of the disk has been reached.
};

//
// Summary:
//    Describes the writer stream settings when capturing to an MOV file.
//
struct SMvMOVWriterStreamSettings
{
   uint32_t                         ui32Size;               // Structure size in bytes.
   bool                             bSaveAudioAsStereo;     // If true, audio data is saved as stereo. Otherwise, it is saved as mono.
   uint32_t                         fourCCBrand;            // Four character code identifier.
   uint64_t                         ui64PresetFileDuration; // Indicates the preset file duration.
   bool                             bIncludeClapAtom;       // If true, CLAP atoms are included in the MOV files.
   EMvVANCLocation                  eVANCLocation;          // Indicates where to save the VANC data.
   EMvClipOptionMOVVANCTrackOption  eCCType;                // Indicates whether the closed caption information is saved to a CEA-608 or CEA-708 track.
   bool                             bOptimizeMOVAudioPackaging; // If true, allows optimizing the type of audio packaging for native MOV recording.
};

//
// Summary:
//    Describes the writer stream settings when capturing to an MP4 file.
//
struct SMvMP4WriterStreamSettings
{
   uint32_t ui32Size;               // Structure size in bytes.
   uint64_t ui64PresetFileDuration; // Indicates the preset file duration.
   uint32_t fourCCBrand;            // Four character code identifier.
};


//
// Summary:
//    Describes the writer stream settings when capturing to an MXF file.
//
struct SMvMXFWriterStreamSettings
{
   uint32_t                   ui32Size;         // Structure size in bytes.
   EMvVANCLocation            eVANCLocation;    // Indicates where to save the VANC data.
   EMvClipOptionMxfFillLabel  eMvFillLabel;     // Indicates which fill label to use when generating an MXF file.
   bool                       bTDIRTmpFile;     // If true, RIP files are saved to TMP files.
};

//
// Summary:
//    Describes the options that will be used for the Pulse-code modulation (PCM) audio.
//
struct SMvPCMCompressionOptions
{
   uint32_t    ui32Size;               // Structure size in bytes.
   uint32_t    ui32BitsPerSample;      // Bits per sample for the format type. This value represents the container size.
   uint32_t    ui32ValidBitsPerSample; // This field must be greater than or equal to ui32ValidBitsPerSample.
};


//
// Summary:
//    Describes the generic compressed writer stream's settings.
//
struct SMvCompressedWriterStreamSettings
{
   uint32_t    ui32Size;                                    // Structure size in bytes.
   uint64_t    ui64ReserveSpaceForEndOfDiskCheckInBytes;    // Indicates the amount of disk space to reserve before the compressed writer stream determines that the end of the disk has been reached.
};

//
// Summary:
//    Describes the video information about the video file to be used by the reader stream.
// Remarks:
//    - The resolution of the file to stream does not need to be the same as the resolution of the host node.
//      Only the frame rate must be the same. For example, if the host node resolution is 1080i @ 25 fps, the reader
//      stream can stream a file whose resolution is PAL (576p @ 25 fps).
//    - If the host node resolution is smaller than the file resoultion, the reader stream will crop the file to fit it in 
//      the host node's resolution. However, if the host node resolution is larger than the file resolution, the reader stream 
//      will fit the file in the host node's resolution and fill the extra pixels with black to match the host node's resolution. 
//      In the case where the file resolution is 1440x1080 and the host node resolution is 1920x1080 (with the same frame rate), the 
//      reader stream will upscale the file to 1920x1080. 
//
struct SMvReaderStreamVideoInformation
{
   uint32_t                   ui32Size;               // Structure size in bytes.
   wchar_t                    wszFilepath[MAX_PATH];  // Specifies the file name and path of the file to read.
   wchar_t                    wszVideoIndexFileName[MAX_PATH];  // If present, indicates the file name of the video index.
   CLSID                      clsidClipGuid;          // Specifies the GUID of the clip used to read the file.  This is usually provided by 
                                                      // the file information module. <p><b>Note</b>: If a GUID is not used, use CLSID_NULL.
   uint64_t                   ui64InPoint;            // Specifies the first frame to read in the file.
   uint64_t                   ui64OutPoint;           // Specifies the last frame of the element in the file. <p> This value is exclusive, 
                                                      // meaning that a trim from 0 to 200 will play frame 0 to 199.
   uint64_t                   ui64Duration;           // Specifies the number of frames to output.
   bool                       bTDIR;                  // If true, time delay instant replay (TDIR) is applied.
   EMvSlowMotionType          eSlowMotionType;        // Specifies the type of slow-motion interpolation algorithm selected.
   EMvNTSCClosedCaptionFormat eCCFormat;              // Specifies the NTSC closed captioning format used.
   bool                       bIsSingleFrame;         // If true, the in-point (ui64InPoint) is repeated for the entire duration.
   bool                       bRepeatLastFrame;       // If true, the reader stream repeats the last decompressed frame at the output. Otherwise, black is output. 
   uint64_t                   ui64StreamIdentifier;   // Specifies which stream to decode.
   CLSID                      clsidH264Decoder;       // Specifies the CLSID of H264 Decoder to decode the H.264 file. This can be set by app. For non H.264 file, it should be GUID_NULL.
};

//
// Summary:
//    Describes the audio information about the audio file to be used by the reader stream.
// Remarks:
//    - At present, the number of audio streams must be less than or equal to 64. 
//    - Each stream can contain 1, 2, 4, 8, or 16 channels.
//    - The number of channels per stream must be the same for all audio streams in the file.
//    - The minimum selection is one stream. You cannot play back specific channels from a stream.
//    - The total number of channels that can be played back is 2, 4, 8, or 16.
//    - If an audio file is longer than the video file, the reader stream will play the audio file 
//      up to the duration of the video file.
//    - If an audio file is shorter than the video file, the reader stream will play silence once 
//      it reaches the end of the audio file.
// Example:
//    To play back streams 0, 1, 2, and 4, set ui64StreamIdentifier to 0x00000017. <p> <b> Note: </b> The hexadecimal value 0x00000017 corresponds to the binary value 10111.
//
struct SMvReaderStreamAudioInformation
{
   uint32_t                   ui32Size;               // Structure size in bytes.
   wchar_t                    wszFilepath[MAX_PATH];  // Specifies the file name and path of the file to read.
   wchar_t                    wszAudioIndexFileName[MAX_PATH];  // If present, indicates the file name of the audio index.
   CLSID                      clsidClipGuid;          // Specifies the GUID of the clip used to read the file. This is usually provided by 
                                                      // the file information module. <p><b>Note</b>: If a GUID is not used, use CLSID_NULL.
   uint64_t                   ui64InPoint;            // Specifies the first frame to read in the file.
   uint64_t                   ui64Duration;           // Specifies the number of frames to read in the file.
   bool                       bTDIR;                  // If true, time delay instant replay (TDIR) is applied.
   bool                       bHasFadeIn;             // If true, enables the fade-in attribute of the first audio sample buffer of the element.
   bool                       bHasFadeOut;            // If true, enables the fade-out attribute of the last audio sample buffer of the element.
   uint64_t                   ui64StreamIdentifier;   // Specifies the particular streams to play back. 
};



//
// Summary:
//    Defines audio tracks arrangement.
//
enum EMvAudioTrackIdentifier
{
   keMvAudioTrackIdentifierInvalid,          // Invalid value.
   keMvAudioTrackIdentifier1  = 0x00000001,  // Specifies the identifier of the first audio track of an audio sample.
   keMvAudioTrackIdentifier2  = keMvAudioTrackIdentifier1 << 1,  // Specifies the identifier of the second audio track of an audio sample.
   keMvAudioTrackIdentifier3  = keMvAudioTrackIdentifier2 << 1,  // Specifies the identifier of the third audio track of an audio sample.
   keMvAudioTrackIdentifier4  = keMvAudioTrackIdentifier3 << 1,  // Specifies the identifier of the fourth audio track of an audio sample.
   keMvAudioTrackIdentifier5  = keMvAudioTrackIdentifier4 << 1,  // Specifies the identifier of the fifth audio track of an audio sample.
   keMvAudioTrackIdentifier6  = keMvAudioTrackIdentifier5 << 1,  // Specifies the identifier of the sixth audio track of an audio sample.
   keMvAudioTrackIdentifier7  = keMvAudioTrackIdentifier6 << 1,  // Specifies the identifier of the seventh audio track of an audio sample.
   keMvAudioTrackIdentifier8  = keMvAudioTrackIdentifier7 << 1,  // Specifies the identifier of the eighth audio track of an audio sample.
   keMvAudioTrackIdentifier9  = keMvAudioTrackIdentifier8 << 1,  // Specifies the identifier of the ninth audio track of an audio sample.
   keMvAudioTrackIdentifier10 = keMvAudioTrackIdentifier9 << 1,  // Specifies the identifier of the tenth audio track of an audio sample.
   keMvAudioTrackIdentifier11 = keMvAudioTrackIdentifier10 << 1,  // Specifies the identifier of the eleventh audio track of an audio sample.
   keMvAudioTrackIdentifier12 = keMvAudioTrackIdentifier11 << 1,  // Specifies the identifier of the twelfth audio track of an audio sample.
   keMvAudioTrackIdentifier13 = keMvAudioTrackIdentifier12 << 1,  // Specifies the identifier of the thirteenth audio track of an audio sample.
   keMvAudioTrackIdentifier14 = keMvAudioTrackIdentifier13 << 1,  // Specifies the identifier of the fourteenth audio track of an audio sample.
   keMvAudioTrackIdentifier15 = keMvAudioTrackIdentifier14 << 1,  // Specifies the identifier of the fifteenth audio track of an audio sample.
   keMvAudioTrackIdentifier16 = keMvAudioTrackIdentifier15 << 1,  // Specifies the identifier of the sixteenth audio track of an audio sample.
   keMvAudioTrackIdentifierPair1   = keMvAudioTrackIdentifier1  | keMvAudioTrackIdentifier2,    // Specifies the identifier of the first audio pair of an audio sample.
   keMvAudioTrackIdentifierPair2   = keMvAudioTrackIdentifier3  | keMvAudioTrackIdentifier4,    // Specifies the identifier of the second audio pair of an audio sample.
   keMvAudioTrackIdentifierPair3   = keMvAudioTrackIdentifier5  | keMvAudioTrackIdentifier6,    // Specifies the identifier of the third audio pair of an audio sample.
   keMvAudioTrackIdentifierPair4   = keMvAudioTrackIdentifier7  | keMvAudioTrackIdentifier8,    // Specifies the identifier of the fourth audio pair of an audio sample.
   keMvAudioTrackIdentifierPair5   = keMvAudioTrackIdentifier9  | keMvAudioTrackIdentifier10,   // Specifies the identifier of the fifth audio pair of an audio sample.
   keMvAudioTrackIdentifierPair6   = keMvAudioTrackIdentifier11 | keMvAudioTrackIdentifier12,   // Specifies the identifier of the sixth audio pair of an audio sample.
   keMvAudioTrackIdentifierPair7   = keMvAudioTrackIdentifier13 | keMvAudioTrackIdentifier14,   // Specifies the identifier of the seventh audio pair of an audio sample.
   keMvAudioTrackIdentifierPair8   = keMvAudioTrackIdentifier15 | keMvAudioTrackIdentifier16,   // Specifies the identifier of the eighth audio pair of an audio sample.
   keMvAudioTrackIdentifierMono    = keMvAudioTrackIdentifier1,                                 // Specifies the identifier of a mono audio sample.
   keMvAudioTrackIdentifierStereo  = keMvAudioTrackIdentifier1 | keMvAudioTrackIdentifier2,     // Specifies the identifier of a stereo audio sample.
   keMvAudioTrackIdentifier4Tracks = keMvAudioTrackIdentifier1 | keMvAudioTrackIdentifier2 |    // Specifies the identifier of a four tracks audio sample.
                                     keMvAudioTrackIdentifier3 | keMvAudioTrackIdentifier4,
   keMvAudioTrackIdentifier8Tracks  = 0x000000FF,                                               // Specifies the identifier of an eight tracks audio sample.
   keMvAudioTrackIdentifier16Tracks = 0x0000FFFF,                                               // Specifies the identifier of a sixteen tracks audio sample.
   keMvAudioTrackIdentifierLast     // End of list indicator.
};


//
// Summary:
//    Describes the reader stream's settings.
//
struct SMvReaderStreamSettings
{
   uint32_t ui32Size;                        // Structure size in bytes.
   uint32_t ui32ReadAheadSizeInFrames;       // Indicates the maximum number frames that can be read ahead of time. This value cannot be zero.
   uint32_t ui32ReadAheadThresholdInFrames;  // Indicates the number of frames that signals the reader stream to get more frames from the file. 
                                             // If the value is set to zero, the reader stream uses ui32ReadAheadSizeInFrames/2 instead. 
   uint32_t ui32CuePrerollInFrames;          // Indicates the minimum number of frames before the next element is cued.<p>
                                             // The recommended value is four seconds (in frames). <p> <b>Note</b>: If this value is too small, 
                                             // frames may be skipped as a result.
   bool     bProcessAudioOnSeek;             // If true, the audio contained in the file is returned when seeking. Otherwise, silence is returned.  
   bool     bProcessAncillaryDataOnSeek;     // If true, the ancillary data of the file is returned when seeking. Otherwise, it is not returned.
   EMvNodeContent eNodeContentToProcess;     // Indicates the type of data in the stream to process. For example, video data only, VANC data only, or 
                                             // any other data combination.
};


//
// Summary:
//    Specifies the reader stream event that occurred.
//
enum EMvReaderStreamEvent
{
   keMvReaderStreamEventInvalid,          // Invalid value.   
   keMvReaderStreamEventPlaying,          // The reader stream started playing an element.
   keMvReaderStreamEventSeek,             // The reader stream sought a specific frame in an element.
   keMvReaderStreamEventPaused,           // The reader stream paused the playback of the current element.
   keMvReaderStreamEventStopped,          // The reader stream stopped the playback of the current element.
   keMvReaderStreamEventElementReleased,  // The reader stream released the IMvReaderStreamEventCallback interface.
   keMvReaderStreamEventFileOpened,       // The reader stream opened a file it needs to read.
   keMvReaderStreamEventFileClosed,       // The reader stream closed a file it no longer needs to read.
   keMvReaderStreamEventErrorCode,        // The reader stream encountered an internal error. For example,
                                          // a warning  whose error code constant starts with MV_W_xxx or MV_M_xxx.
   keMvReaderStreamEventLast              // End of list indicator.
};


//
// Summary:
//    Specifies when the reader stream started playing, started seeking, paused, or stopped the event.
//
struct SMvReaderStreamEventPosition
{
   uint64_t                 ui64Timestamp;         // Indicates the time (in nanotime) at which the event occurred.
   IMvReaderStreamElement * pIElement;             // Indicates the reader stream element that triggered the event.
   uint64_t                 ui64ElementPosition;   // Indicates the position in the file (in frames) of the specified reader stream element.
};


//
// Summary:
//    Specifies whether the reader stream opened or closed the file.
//
struct SMvReaderStreamEventFile
{
   IMvReaderStreamElement * pIElement;    // Indicates the reader stream element that triggered the event.
   wchar_t    wszFilepath[MAX_PATH];      // Indicates the file name and path of the reader stream event.
   HANDLE     hFileHandle;                // Indicates the handle to the file of reader stream element.
};


//
// Summary:
//    Specifies the reader stream element that release the event.
//
struct SMvReaderStreamEventElement
{
   IMvReaderStreamElement * pIElement;  // Indicates the reader stream element that triggered the event.
};


//
// Summary:
//    Specifies the error code the reader stream encountered.
//
struct SMvReaderStreamEventError
{
   IMvReaderStreamElement * pIElement;             // Indicates the reader stream element that triggered the event.
   uint64_t                 ui64ElementPosition;   // Indicates the position in the file (in frames) of the specified reader stream element.
   HRESULT                  hrErrorCode;           // Indicates the error code that occurred.
};


//
// Summary:
//    Provides details of the reader stream event notification.
//
struct SMvReaderStreamEvent
{
   uint32_t             ui32Size;   // Structure size in bytes.
   EMvReaderStreamEvent eEvent;     // Indicates the reader stream event that occurred. The user application can then use the 
                                    // appropriate structure for more details.
   union
   {
      SMvReaderStreamEventPosition sEventPlay;           // Indicates when the reader stream started playing the event.
      SMvReaderStreamEventPosition sEventPause;          // Indicates when the reader stream paused the event.
      SMvReaderStreamEventPosition sEventStop;           // Indicates when the reader stream stopped the event.
      SMvReaderStreamEventPosition sEventSeek;           // Indicates when the reader stream started seeking the event.
      SMvReaderStreamEventFile     sEventFileOpened;     // Indicates when the reader stream opened the file event.
      SMvReaderStreamEventFile     sEventFileClosed;     // Indicates when the reader stream closed the file event.
      SMvReaderStreamEventElement  sEventElementRelease; // Indicates the reader stream element that released the event.
      SMvReaderStreamEventError    sEventError;          // Indicates the error code of the event.
   };
};


//
// Summary:
//    Defines a data transfer direction.
//
enum EMvTransferDirection
{
   keMvTransferDirectionInvalid,    // Invalid value. 
   keMvTransferDirectionCardToHost, // Specifies that data will be transferred from the card memory to the host memory.
   keMvTransferDirectionHostToCard, // Specifies that data will be transferred from the host memory to the card memory.
   keMvTransferDirectionLast        // End of list indicator.
};


#define MV_TRANSFER_DIRECTION_ENUM_TO_STRING(eValue) \
   ((eValue == keMvTransferDirectionInvalid)    ? "Invalid"      : \
    (eValue == keMvTransferDirectionCardToHost) ? "card-to-host" : \
    (eValue == keMvTransferDirectionHostToCard) ? "host-to-card" : \
    (eValue == keMvTransferDirectionLast)       ? "Last"         : \
    ("???"))

//
// Summary:
//    Specifies where the asynchronous error occurred.
//
enum EMvAsyncErrorType
{
   keMvAsyncErrorTypeNode,                   // Indicates that the asynchronous error occurred in the node.
   keMvAsyncErrorTypeTransferStream,         // Indicates that the asynchronous error occurred in the transfer stream.
   keMvAsyncErrorTypeEncoderStream,          // Indicates that the asynchronous error occurred in the encoder stream.
   keMvAsyncErrorTypeMuxerStream,            // Indicates that the asynchronous error occurred in the muxer stream.
   keMvAsyncErrorTypeRTPSenderStream,        // Indicates that the asynchronous error occurred in the RTP sender stream.
   keMvAsyncErrorTypeHostTransformStream,    // Indicates that the asynchronous error occurred in the host transform stream.
   keMvAsyncErrorTypeCompressedWriterStream, // Indicates that the asynchronous error occurred in the compressed writer stream.
   keMvAsyncErrorTypeEchoStream,             // Indicates that the asynchronous error occurred in the echo stream.
   keMvAsyncErrorTypeCompressedHostNode,     // Indicates that the asynchronous error occurred in the compressed host node.
   keMvAsyncErrorTypeDecoderStream,          // Indicates that the asynchronous error occurred in  the decoder stream.
   keMvAsyncErrorTypeRTPReceiverStream,      // Indicates that the asynchronous error occurred in  RTP receiver stream.
	keMvAsyncErrorTypeUniversalClock,			// Indicates that the asynchronous error occurred in  Universal Clock.
   keMvAsyncErrorTypeLast,                   // End of list indicator.
};

#define MV_ASYNC_ERROR_TYPE_ENUM_TO_STRING(eValue) \
   ((eValue == keMvAsyncErrorTypeNode)           ? "Node"            : \
    (eValue == keMvAsyncErrorTypeTransferStream) ? "Transfer stream" : \
    (eValue == keMvAsyncErrorTypeEncoderStream)  ? "Encoder stream" : \
    (eValue == keMvAsyncErrorTypeMuxerStream)    ? "Muxer stream" : \
    (eValue == keMvAsyncErrorTypeRTPSenderStream)? "RTP sender stream" : \
    (eValue == keMvAsyncErrorTypeHostTransformStream)? "Host transform stream" : \
    (eValue == keMvAsyncErrorTypeCompressedWriterStream)? "CompressedWriterStream" : \
    (eValue == keMvAsyncErrorTypeEchoStream)? "EchoStream" : \
    (eValue == keMvAsyncErrorTypeCompressedHostNode)? "CompressedHostNode" : \
    (eValue == keMvAsyncErrorTypeDecoderStream)  ? "Decoder stream" : \
	 (eValue == keMvAsyncErrorTypeUniversalClock)  ? "Universal Clock" : \
    (eValue == keMvAsyncErrorTypeLast)           ? "Last"            : \
    ("???"))


//
// Summary:
//    Specifies the node in which the asynchronous error occurred.
//
struct SMvAsyncErrorInformationNode
{
   IMvNode* pINode; // Pointer to the node in which the asynchronous error occurred.
};

//
// Summary:
//    Specifies the transfer stream in which the asynchronous error occurred.
//
struct SMvAsyncErrorInformationTransfer
{
   IMvTransferStream* pITransferStream; // Pointer to the transfer stream in which the asynchronous error occurred.
};

//
// Summary:
//    Specifies the encoder stream in which the asynchronous error occurred.
//
struct SMvAsyncErrorInformationEncoder
{
   IMvEncoderStream * pIEncoderStream; // Pointer to the encoder stream in which the asynchronous error occurred.
};

//
// Summary:
//    Specifies the muxer stream in which the asynchronous error occurred.
//
struct SMvAsyncErrorInformationMuxer
{
   IMvMuxerStream * pIMuxerStream; // Pointer to the muxer stream in which the asynchronous error occurred.
};

//
// Summary:
//    Specifies the echo stream in which the asynchronous error occurred.
//
struct SMvAsyncErrorInformationEcho
{
   IMvEchoStream * pIEchoStream; // Pointer to the echo stream in which the asynchronous error occurred.
};

//
// Summary:
//    Specifies the RTP sender stream in which the asynchronous error occurred.
//
struct SMvAsyncErrorInformationRTPSender
{
   IMvRTPSenderStream* pIRTPSenderStream; // Pointer to the RTP sender stream in which the asynchronous error occurred.
};

//
// Summary:
//    Specifies the host-based transform stream in which the asynchronous error occurred.
//
struct SMvAsyncErrorInformationHostTransform
{
   IMvTransformStream* pITransformStream; // Pointer to the host-based transform stream in which the asynchronous error occurred.
};

//
// Summary:
//    Specifies the compressed writer stream in which the asynchronous error occurred.
//
struct SMvAsyncErrorInformationCompressedWriterStream
{
   IMvCompressedWriterStream* pICompressedWriterStream; // Pointer to the compressed writer stream in which the asynchronous error occurred.
};

//
// Summary:
//    Specifies the compressed host node in which the asynchronous error occurred.
//
struct SMvAsyncErrorInformationCompressedHostNode
{
   IMvCompressedHostNode* pICompressedHostNode; // Pointer to the compressed host node in which the asynchronous error occurred.
};

//
// Summary:
//    Specifies the decoder stream in which the asynchronous error occurred.
//
struct SMvAsyncErrorInformationDecoder
{
   IMvDecoderStream * pIDecoderStream; // Pointer to the decoder stream in which the asynchronous error occurred.
};

//
// Summary:
//    Specifies the RTP receiver stream in which the asynchronous error occurred.
//
struct SMvAsyncErrorInformationRTPReceiver
{
   IMvRTPReceiverStream * pIRTPReceiverStream;  // Pointer to the RTP receiver stream in which the asynchronous error occurred.
};

//
// Summary:
//    Describes the asynchronous error that occurred.
//
struct SMvAsyncErrorInformation
{	
   uint32_t          ui32Size;      // Structure size in bytes.
   uint64_t          ui64Timestamp; // Indicates the time at which the asynchronous error occurred (in nanotime).
   uint64_t          ui64Duration;  // Indicates the duration of the asynchronous error (in nanotime).
   HRESULT           hError;        // Indicates the error code.
   EMvAsyncErrorType eType;         // Indicates where the asynchronous error occurred so that the appropriate union structure is accessed.
   union UMvAsyncErrorInformation
   {
      SMvAsyncErrorInformationNode                    sNode;                   // Indicates the node in which the asynchronous error occurred.
      SMvAsyncErrorInformationTransfer                sTransfer;               // Indicates the transfer stream in which the asynchronous error occurred.
      SMvAsyncErrorInformationEncoder                 sEncoder;                // Indicates the encoder stream in which the asynchronous error occurred.
      SMvAsyncErrorInformationMuxer                   sMuxer;                  // Indicates the muxer stream in which the asynchronous error occurred.
      SMvAsyncErrorInformationRTPSender               sRTPSender;              // Indicates the RTP sender stream in which the asynchronous error occurred.
      SMvAsyncErrorInformationHostTransform           sHostTransform;          // Indicates the host-based transform stream in which the asynchronous error occurred.
      SMvAsyncErrorInformationCompressedWriterStream  sCompressedWriterStream; // Indicates the compressed writer stream in which the asynchronous error occurred.
      SMvAsyncErrorInformationCompressedHostNode      sCompressedHostNode;     // Indicates the compressed host node in which the asynchronous error occurred.
      SMvAsyncErrorInformationEcho                    sEcho;                   // Indicates the echo stream in which the asynchronous error occurred.
      SMvAsyncErrorInformationDecoder                 sDecoder;                // Indicates the decoder stream in which the asynchronous error occurred.
      SMvAsyncErrorInformationRTPReceiver             sRTPReceiver;            // Indicates the RTP receiver stream in which the asynchronous error occurred.

   } uInfo;
};

//
// Summary:
//    Specifies the status of the Time Server Dependant clock
//
enum EMvTimeServerStatus
{
   keMvTimeServerStatusInvalid,              // Invalid value.
   keMvTimeServerStatusLocked,               // Indicates that our Time Server Dependant clock is locked/synchronized.
   keMvTimeServerStatusUnlocked,             // Indicates that our Time Server Dependant clock is unlocked/not synchronized (server not reachable)
   keMvTimeServerStatusFreeRunning,          // Indicates that our Time Server Dependant clock is unlocked and will never be.
   keMvTimeServerStatusLast                  // End of list indicator.
};

//
// Summary:
//    Describes the Time server synchronization status.
//
struct SMvUniversalClockStatus
{
   uint32_t                ui32Size;                  // Structure size in bytes.
   EMvTimeServerStatus     eStatus;                   // Status of the connection.
};

//
// Summary:
//    Describes the time correction applied to the clock.
//
struct SMvTimeServerCorrection
{
   uint32_t                ui32Size;                  // Structure size in bytes.
   int64_t                 i64TimeCorrection;         // Indicate the value of the correction made in nanotimes.
};

//
// Summary:
//    Describes the kind of notification coming from the universal clock.
//
enum EMvUniversalClockNotificationType
{
   keMvUniversalClockNotificationTypeInvalid,         // Invalid value.
   keMvUniversalClockNotificationTypeStatus,          // The notification describes a status, use SMvUniversalClockNotification::uData.sStatus.
   keMvUniversalClockNotificationTypeTimeCorrection,  // The notification describes a time correction, use SMvUniversalClockNotification::uData.sTimeCorrection.
   keMvUniversalClockNotificationTypeLast             // End of list indicator.
};

//
// Summary:
//    Describes the asynchronous event that occurred.
//
struct SMvUniversalClockNotification 
{
   uint32_t                               ui32Size;            // Structure size in bytes.
   uint64_t                               ui64Timestamp;       // Indicate the time at which the notification occurred (in nanotime).
   EMvUniversalClockNotificationType      eNotificationType;   // Indicate the type of notification.
   union UMvUniversalClockNotification
   {
      SMvUniversalClockStatus             sStatus;
      SMvTimeServerCorrection             sTimeCorrection;
   } uData;
};

//
// Summary:
//    Specifies the IP protocol for streaming.
//
enum EMvIPProtocol
{
   keMvIPProtocolInvalid,  // Invalid value.
   keMvIPProtocolUDP,      // Indicates the IP protocol is User Datagram Protocol (UDP).
   keMvIPProtocolTCP,      // Indicates the IP protocol is Transmission Control Protocol (TCP).
   keMvIPProtocolLast      // End of list indicator.
};

//
// Summary:
//    Describes the settings for initiating a network connection.
//
struct SMvNetworkInterfaceSettings
{
   uint32_t          ui32Size;                        // Structure size in bytes.
   char              szNetworkInterfaceIPAddress[33]; // Indicates the IP address (IPV4 or IPV6) configured on the network card, which is used for Real-time Transport Protocol (RTP) transmission.
   char              szRemoteIPAddress[33];           // Indicates the IP address to or from which data will be streamed. Can use a multicast address.
                                                      // However, a multicast address will only stream content to the systems within the same subnet as the source system.
   uint16_t          ui16SourcePort;                  // Indicates the IP port to use on source side. This value must be an even number.
   uint16_t          ui16DestinationPort;             // Indicates the IP port to use on destination side. This value must be an even number.
   uint16_t          ui16MTU;                         // Indicates the Maximum Transmission Unit (MTU) to use for connection. The maximum value is 1500.
   uint8_t           ui8TTL;                          // Indicates the time in which RTP packets can be used. The maximum value is 255.
};

//
// Summary:
//    Describes the settings of an RTP (Real-time Transport Protocol) sender stream.
//
struct SMvRTPSenderStreamSettings
{
   uint32_t          ui32Size;                           // Structure size in bytes.
   EMvSurfaceFormat  eSurfaceFormat;                     // Indicates the format of the data to send. Currently only keMvSurfaceFormatMpeg2Transport is supported.
   EMvIPProtocol     eProtocol;                          // Indicates the IP protocol for streaming. Currently only keMvIPProtocolUDP is supported.
   SMvNetworkInterfaceSettings sNetworkInterfaceSettings;// Indicates the settings for initiating a network connection.
};

//
// Summary:
//    Describes the settings of a compressed host node.
// Remarks:
//    - A compressed host node can contain only one type of data. For example, it can contain only compressed video data.
//
struct SMvCompressedHostNodeSettings
{
   uint32_t          ui32Size;         // Structure size in bytes.
   char              szName[32];       // Indicates the name that will be given to the node.
   EMvNodeContent    eNodeContent;     // Indicates the type of data contained in the node. <p> <b>Note</b>: Only keMvNodeContentVideo, keMvNodeContentAudio, keMvNodeContentVanc, and keMvNodeContentMPEG2_TS are supported.
   SMvResolutionInfo sResInfo;         // Indicates the resolution information of the node.
};

//
// Summary:
//    Specifies the echo direction.
//
enum EMvEchoDirection
{
   keMvEchoDirectionInvalid,           // Invalid value. 
   keMvEchoDirectionHostToCompressed,  // Specifies that the data will be copied from a host node to a compressed host node.
   keMvEchoDirectionCompressedToHost,  // Specifies that the data will be copied from a compressed host node to a host node.
   keMvEchoDirectionLast               // End of list indicator.
};

//
// Summary:
//    Describes the echo stream settings.
//
struct SMvEchoStreamSettings
{
   uint32_t          ui32Size;         // Indicates the structure size in bytes.
   EMvEchoDirection  eEchoDirection;   // Indicates the direction of the echo stream. The direction can be from a host node to a compressed host node, or vice-versa.
};

// 
// Summary:
//    Specifies the type of compressed data contained in the compressed node.
//
enum EMvNodeNotificationDataType
{
   keMvNodeNotificationDataTypeInvalid,   // Invalid value.
   keMvNodeNotificationDataTypeH264,      // Indicates that H.264 data is contained in the compressed host node.
   keMvNodeNotificationDataTypeAAC,       // Indicates that AAC audio data is contained in the compressed host node.
   keMvNodeNotificationDataTypeMPEG2TS,   // Indicates that MPEG-2 transport stream (TS) data is contained in the compressed host node.
   keMvNodeNotificationDataTypeLast       // End of list indicator.
};

//
// Summary:
//    Describes the data of the compressed node notification callback.
// Remarks:
//    - This structure is the base structure for the compressed host node callback notification interfaces 
//      for reading or writing, and is used in conjunction with SMvCompressedNodeNotificationAudioData or 
//      SMvCompressedNodeNotificationH264Data, if required.
//
struct SMvCompressedNodeNotificationData
{
   uint32_t                      ui32Size;               // Structure size in bytes.
   EMvNodeNotificationDataType   eCompressedDataType;    // Indicates the type of compressed data that will be provided to or 
                                                         // received by the compressed host node callback notification.
   void*                         pBuffer;                // Pointer to the buffer containing the compressed data.
   uint32_t                      ui32BufferSize;         // Indicates the size (in bytes) of the buffer.
   uint64_t                      ui64Timestamp;          // Indicates the time at which the buffer is compressed or the compressed buffer is processed.
   EMvPolarity                   eBufferPolarity;        // Indicates the polarity of the buffer.
};

//
// Summary:
//    Describes the H.264 data of the compressed node notification callback.
// Remarks:
//    - This structure is used in conjunction with SMvCompressedNodeNotificationData, if H.264 data is used.
//
struct SMvCompressedNodeNotificationH264Data : public SMvCompressedNodeNotificationData
{
   uint32_t                ui32Size;         // Structure size in bytes.
   SMvGroupOfPicturesFrame sH264FrameInfo;   // Specifies the H.264 data format.
};


//
// Summary:
//    Describes the AAC audio data of the compressed node notification callback.
// Remarks:
//    - This structure is used in conjunction with SMvCompressedNodeNotificationData, if AAC audio data is used.
//
struct SMvCompressedNodeNotificationAudioData : public SMvCompressedNodeNotificationData
{
   uint32_t                ui32Size;            // Structure size in bytes.
   SMvaWaveFormatInfo      sWaveFormatInfo;     // Specifies the AAC audio data format.
};

//
// Summary:
//    Specifies the source of the Session Description Protocol (SDP) data.
//
enum EMvSdpSource
{
   keMvSdpSourceInvalid,                     // Invalid value.
   keMvSdpSourceStringDescription,           // Indicates that the SDP data is provided in a raw format. For example, from a file. 
                                             // To be used with a call to IMvRTPReceiverStream::ConnectWithSdpStringDescription().
   keMvSdpSourceSAP,                         // Indicates that the SDP data is obtained from the Session Announcement Protocol (SAP) data. 
                                             // To be used with a call to IMvRTPReceiverStream::ConnectWithSAP().
   keMvSdpSourceNetworkInterfaceSettings,    // Indicates that the SDP data is obtained from the SMvNetworkInterfaceSettings structure.
                                             // To be used with a call to IMvRTPReceiverStream::ConnectWithNetworkInterfaceSettings().
   keMvSdpSourceLast                         // End of list indicator.
};


//
// Summary:
//    Describes the settings of an RTP receiver stream.
//
struct SMvRTPReceiverStreamSettings
{
   uint32_t          ui32Size;         // Structure size in bytes.
   EMvSurfaceFormat  eSurfaceFormat;   // Indicates the format of the multiplexed Transport Stream (TS) data which can be received. 
                                       // Currently only keMvSurfaceFormatMpeg2Transport can be received.
};

struct SMvRTPReceiverStreamNetworkSettings
{
   uint32_t ui32Size;
   char szNIC[50];
   char szIPAddress[50];
   uint16_t ui16Port;
   EMvIPProtocol eIPProtocol;
};

//
// Summary:
//    Creates a new univeral clock or loads a previously created universal clock.
//
struct SMvUniversalClockInfo
{
   int                  size;
   const char *         szClockName;
   const char *         szNtpServerNameOrIP;
   SMvResolutionInfo    sMvResolutionInfo;
};

//
// Summary:
//    Information about a program stream contained into an MPEG-2 transport stream.
//
struct SMvDemuxerElementaryStreamInfo
{
   uint32_t  ui32size;              // Structure size in bytes.
   uint32_t  ui32PID;               // Elementary stream PID.
   uint8_t   ui8ID;                 // Elementary stream ID.
   uint8_t   ui8StreamType;         // Stream type as specified in the PMT or PSM. If the PMT or PSM is not present this field may be 0.
                                    // (See specification ISO/IEC 13818-1 "Stream type assignments").
   uint32_t  ui32DescriptorLength;  // Length in bytes of the field pui8Descriptor.
   uint8_t * pui8Descriptor;        // Descriptor present in the PMT or PSM for this stream.
};

//
// Summary:
//    Information about an elementary stream contained into a program stream that is contained in an MPEG-2 transport 
//    stream.
//
struct SMvDemuxerProgramStreamInfo
{
   uint32_t  ui32size;              // Structure size in bytes.
   uint32_t  ui32ProgramNumber;     // Program number as specified in the PMT.
   uint32_t  ui32PID;               // Network PID if program_number is 0, else program map PID.
   uint32_t  ui32PCR_PID;           // PID that carries the PCR for this program.
   uint32_t  ui32StreamCount;       // Number of elementary streams in this program.
   uint32_t  ui32DescriptorLength;  // Length in bytes of the field pui8Descriptor.
   uint8_t * pui8Descriptor;        // Descriptor present in the PMT or PSM.
};

//
// Summary:
//    Information about a node that is attached to a specific elementary stream of a program stream that is contained 
//    in an MPEG-2 transport stream.
//
struct SMvDemuxerAttachedNode
{
   uint32_t ui32Size;
   IMvCompressedHostNode * pNode;
   uint32_t ui32ProgramStreamIndex;
   uint32_t ui32ElementaryStreamIndex;
};

