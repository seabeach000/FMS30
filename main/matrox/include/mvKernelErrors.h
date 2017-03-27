/*

(c) Copyright Matrox Electronic Systems Ltd., 2003. All rights reserved. 

This code and information is provided "as is" without warranty of any kind, 
either expressed or implied, including but not limited to the implied 
warranties of merchantability and/or fitness for a particular purpose.

Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make 
changes in specifications and code at any time and without notice. 
No responsibility is assumed by Matrox Electronic Systems Ltd. for 
its use; nor for any infringements of patents or other rights of 
third parties resulting from its use. No license is granted under 
any patents or patent rights of Matrox Electronic Systems Ltd.

*/

#ifndef MVKERNELERRORS_H
#define MVKERNELERRORS_H
//#include "_MvkTypes.h"
/////////////////////////////////////////////////////////////////////////////////
//
// Custom errors

//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//

#include "mvStatus.h"


/*
*	IMPORTANT: 
*	When editing this file, please follow the format below:
*	1. define the facility as an unsigned constant. The constant starts with 'KU (lower case)'. There is one space before and after assignment ('='). 
*	2. define the error code. Error code starts with 'kMvk'.Use macro, NO spaces between macro and the left parentheses.
*	3. add comments right after the code definition. Starts with double slash, and ends with a new line charactor.
*/	



//
// Generic driver errors
//

const unsigned int kuiGenericFacility = 0xfac;

const mvkstatus kMvkStatusIONotSupported                                MAKE_MVKERROR(kuiGenericFacility, 0x9000);   // Generic driver error: I/O is not supported
const mvkstatus kMvkStatusInvalidSurfacePolarity                        MAKE_MVKERROR(kuiGenericFacility, 0x9001);   // Generic driver error: Invalid surface polarity
const mvkstatus kMvkStatusInvalidSurfaceFormat                          MAKE_MVKERROR(kuiGenericFacility, 0x9002);   // Generic driver error: Invalid surface format
const mvkstatus kMvkStatusInvalidSurfaceBitCount                        MAKE_MVKERROR(kuiGenericFacility, 0x9003);   // Generic driver error: Invalid surface bit count
const mvkstatus kMvkStatusInvalidSurface                                MAKE_MVKERROR(kuiGenericFacility, 0x9004);   // Generic driver error: Invalid surface
const mvkstatus kMvkStatusBufferInError                                 MAKE_MVKERROR(kuiGenericFacility, 0x9005);   // Generic driver error: Buffer error
const mvkstatus kMvkStatusInvalidMemLocation                            MAKE_MVKERROR(kuiGenericFacility, 0x9006);   // Generic driver error: Invalid memory location
const mvkstatus kMvkStatusCustomResourcesError                          MAKE_MVKERROR(kuiGenericFacility, 0x9007);   // Generic driver error: Custom Resources Error
const mvkstatus kMvkStatusInvalidInterruptVector                        MAKE_MVKERROR(kuiGenericFacility, 0x9008);   // Generic driver error: Invalid interrupt vector value
const mvkstatus kMvkStatusQueryBusInterfaceFailure                      MAKE_MVKERROR(kuiGenericFacility, 0x9009);   // Generic driver error: Query Bus interface failure
const mvkstatus kMvkStatusQueryInterstackInterfaceFailure               MAKE_MVKERROR(kuiGenericFacility, 0x900A);   // Generic driver error: Query interstack interface failure
const mvkstatus kMvkStatusInvalidInterfacePointer                       MAKE_MVKERROR(kuiGenericFacility, 0x900B);   // Generic driver error: Invalid interface pointer
const mvkstatus kMvkStatusInvalidAudioSamplesSize                       MAKE_MVKERROR(kuiGenericFacility, 0x900C);   // Generic driver error: The audio samples size is not modulo the number of tracks
const mvkstatus kMvkStatusInvalidParameterSize                          MAKE_MVKERROR(kuiGenericFacility, 0x900D);   // Generic driver error: The size of one of the passed parameter(s) is invalid
const mvkstatus kMvkStatusSourceSynchroInError                          MAKE_MVKERROR(kuiGenericFacility, 0x900E);   // Generic driver error: Source Synchro In Error
const mvkstatus kMvkStatusDestinationSynchroInError                     MAKE_MVKERROR(kuiGenericFacility, 0x900F);   // Generic driver error: Destination Synchro In Error
const mvkstatus kMvkStatusVbiNotSupported                               MAKE_MVKERROR(kuiGenericFacility, 0x9010);   // Generic driver error: Vbi is not supported
const mvkstatus kMvkStatusNotQueued                                     MAKE_MVKERROR(kuiGenericFacility, 0x9011);   // Generic driver error: Element was not queued
const mvkstatus kMvkStatusHardwareMalfunction                           MAKE_MVKERROR(kuiGenericFacility, 0x9012);   // Generic driver error: Hardware seems to be in error
const mvkstatus kMvkStatusCommunicationMalfunction                      MAKE_MVKERROR(kuiGenericFacility, 0x9013);   // Generic driver error: Communication channel not functioning on hardware
const mvkstatus kMvkStatusHardwareScalerMalfunction                     MAKE_MVKERROR(kuiGenericFacility, 0x9014);   // Generic driver error: Hardware Scaler engine seems to be in error
const mvkstatus kMvkStatusHardwareCompositorMalfunction                 MAKE_MVKERROR(kuiGenericFacility, 0x9015);   // Generic driver error: Hardware Compositor engine seems to be in error
const mvkstatus kMvkStatusHardwareTransferMalfunction                   MAKE_MVKERROR(kuiGenericFacility, 0x9016);   // Generic driver error: Hardware Transfer engine seems to be in error
const mvkstatus kMvkStatusHardwareCopyMalfunction                       MAKE_MVKERROR(kuiGenericFacility, 0x9017);   // Generic driver error: Hardware Copy engine seems to be in error
const mvkstatus kMvkStatusHardwareClearMalfunction                      MAKE_MVKERROR(kuiGenericFacility, 0x9018);   // Generic driver error: Hardware Clear engine seems to be in error
const mvkstatus kMvkStatusHardwareTargetMalfunction                     MAKE_MVKERROR(kuiGenericFacility, 0x9019);   // Generic driver error: Hardware Target engine seems to be in error
const mvkstatus kMvkStatusHardwareDeInterlacerMalfunction               MAKE_MVKERROR(kuiGenericFacility, 0x901A);   // Generic driver error: Hardware DeInterlacer engine seems to be in error
const mvkstatus kMvkStatusOperationUnsuccessful                         MAKE_MVKERROR(kuiGenericFacility, 0x901B);   // Generic driver error: The requested operation was unsuccessful.
const mvkstatus kMvkStatusOperationInvalidParameter                     MAKE_MVKERROR(kuiGenericFacility, 0x9020);   // Generic driver error: Invalid parameter.
const mvkstatus kMvkStatusHardwareScalerCompletionProblem               MAKE_MVKERROR(kuiGenericFacility, 0x9021);   // Generic driver error: Hardware Scaler completion in Error
const mvkstatus kMvkStatusHardwareCompositorCompletionProblem           MAKE_MVKERROR(kuiGenericFacility, 0x9022);   // Generic driver error: Hardware Compositor completion in Error
const mvkstatus kMvkStatusHardwareTransferCompletionProblem             MAKE_MVKERROR(kuiGenericFacility, 0x9023);   // Generic driver error: Hardware Transfer completion in Error
const mvkstatus kMvkStatusHardwareCopyCompletionProblem                 MAKE_MVKERROR(kuiGenericFacility, 0x9024);   // Generic driver error: Hardware Copy completion in Error
const mvkstatus kMvkStatusHardwareClearCompletionProblem                MAKE_MVKERROR(kuiGenericFacility, 0x9025);   // Generic driver error: Hardware Clear completion in Error
const mvkstatus kMvkStatusHardwareDeInterlacerCompletionProblem         MAKE_MVKERROR(kuiGenericFacility, 0x9026);   // Generic driver error: Hardware DeInterlacer completion in Error
const mvkstatus kMvkStatusOperationIOTimeOut                            MAKE_MVKERROR(kuiGenericFacility, 0x9027);   // Generic driver error: The operation timed out
const mvkstatus kMvkStatusOperationInvalidDeviceState                   MAKE_MVKERROR(kuiGenericFacility, 0x9028);   // Generic driver error: The device is not in a valid state to perform this request
const mvkstatus kMvkStatusOperationNoMemory                             MAKE_MVKERROR(kuiGenericFacility, 0x9029);   // Generic driver error: The device has not enough memory to perform the operation
const mvkstatus kMvkStatusOperationMixerSettingsLate                    MAKE_MVKERROR(kuiGenericFacility, 0x902A);   // Generic driver error: Mixer settings were late when they were received
const mvkstatus kMvkStatusOperationTransformSettingsLate                MAKE_MVKERROR(kuiGenericFacility, 0x902B);   // Generic driver error: Transform settings were late when they were received
const mvkstatus kMvkStatusOperationInputNodeConnectionLate              MAKE_MVKERROR(kuiGenericFacility, 0x902C);   // Generic driver error: Input Node connection is late when it is received
const mvkstatus kMvkStatusOperationOutputNodeConnectionLate             MAKE_MVKERROR(kuiGenericFacility, 0x902D);   // Generic driver error: Output Node connection is late when it is received
const mvkstatus kMvkStatusHardwareScalerMaxProcessingPowerReached       MAKE_MVKERROR(kuiGenericFacility, 0x902E);   // Generic driver error: Hardware Scaler maximum processing power reached.
const mvkstatus kMvkStatusHardwareDeInterlacerMaxProcessingPowerReached MAKE_MVKERROR(kuiGenericFacility, 0x902F);   // Generic driver error: Hardware DeInterlacer maximum processing power reached.
const mvkstatus kMvkStatusOperationDeInterlacerSettingsLate             MAKE_MVKERROR(kuiGenericFacility, 0x9030);   // Generic driver error: DeInterlacer settings were late when they were received
const mvkstatus kMvkStatusCardFlashMismatch                             MAKE_MVKERROR(kuiGenericFacility, 0x9031);   // Generic driver error: Card Flash Content Mismatch
const mvkstatus kMvkStatusHardwareMixerMaxProcessingPowerReached        MAKE_MVKERROR(kuiGenericFacility, 0x9032);   // Generic driver error: Hardware Mixer maximum processing power reached.
const mvkstatus kMvkStatusVancProcessingMalfunction                     MAKE_MVKERROR(kuiGenericFacility, 0x9033);   // Generic driver error: Vanc processing seems to be in error
const mvkstatus kMvkStatusMatroxAncillaryDataNotSupported               MAKE_MVKERROR(kuiGenericFacility, 0x9034);   // Generic driver error: MAD is not supported
const mvkstatus kMvkStatusDPCLate                                       MAKE_MVKERROR(kuiGenericFacility, 0x9035);   // Generic driver error: DPC late

//
// Abob errors
//

const unsigned int kuiABOBFacility = 0xb0b;

const mvkstatus kMvkStatusIOParamOutOfRange                    MAKE_MVKERROR(kuiABOBFacility, 0x9000);	// ABOB error: I/O Parameter out of range
const mvkstatus kMvkStatusIOCalculationError                   MAKE_MVKERROR(kuiABOBFacility, 0x9001);	// ABOB error: I/O calculation error
const mvkstatus kMvkStatusIOBobInternalError                   MAKE_MVKERROR(kuiABOBFacility, 0x9002);	// ABOB error: BOB internal error
const mvkstatus kMvkStatusIOInvalidIOCardId                    MAKE_MVKERROR(kuiABOBFacility, 0x9003);	// ABOB error: Invalid IO card ID
const mvkstatus kMvkStatusIOInavlidNotification                MAKE_MVKERROR(kuiABOBFacility, 0x9004);	// ABOB error: Invalid IO notification

//
// HDBob errors
//

const unsigned int kuiHDBobFacility = 0x30f;

const mvkstatus kMvkStatusParamOutOfRange                      MAKE_MVKERROR(kuiHDBobFacility, 0x9000);	// HDBOB error: parameter out of range
const mvkstatus kMvkStatusCalculationError                     MAKE_MVKERROR(kuiHDBobFacility, 0x9001);	// HDBOB error: calculation error
const mvkstatus kMvkStatusUnsupportedGenlockResolution         MAKE_MVKERROR(kuiHDBobFacility, 0x9002);  // HDBOB error: unsupported genlock resolution
const mvkstatus kMvkStatusUnsupportedInputResolution           MAKE_MVKERROR(kuiHDBobFacility, 0x9003);	// HDBOB error: unsupported input resolution

//
// HQScaler errors
//

const unsigned int kuiHQScalerFacility = 0x400;

const mvkstatus kMvkStatusNoCurrentResolution                  MAKE_MVKERROR(kuiHQScalerFacility, 0xF000);	// HQScaler error: no current resolutin
const mvkstatus kMvkStatusNoIOResolution                       MAKE_MVKERROR(kuiHQScalerFacility, 0xF001);	// HQScaler error: no IO resolution
const mvkstatus kMvkStatusSurfaceResolutionMismatch            MAKE_MVKERROR(kuiHQScalerFacility, 0xF002);	// HQScaler error: surface resolution mismatches
const mvkstatus kMvkStatusSurfaceNULL                          MAKE_MVKERROR(kuiHQScalerFacility, 0xF003);	// HQScaler error: null surface
const mvkstatus kMvkStatusInvalidInputRectangle                MAKE_MVKERROR(kuiHQScalerFacility, 0xF004);	// HQScaler error: invalid input rectangle
const mvkstatus kMvkStatusInvalidOutputRectangle               MAKE_MVKERROR(kuiHQScalerFacility, 0xF005);	// HQScaler error: invalid output rectangle
const mvkstatus kMvkStatusInvalid32Sequence                    MAKE_MVKERROR(kuiHQScalerFacility, 0xF006);	// HQScaler error: invalid 32 sequence
const mvkstatus kMvkStatusBufferAlreadyQueued                  MAKE_MVKERROR(kuiHQScalerFacility, 0xF007);	// HQScaler error: buffer already queued

//
// Input errors
//

const unsigned int kuiInputFacility = 0x30C;

const mvkstatus kMvkStatusSetCallbackFailed                    MAKE_MVKERROR(kuiInputFacility, 0x1000); // Input error: set callback failed
const mvkstatus kMvkStatusPrerollNotRespected                  MAKE_MVKERROR(kuiInputFacility, 0x1001); // Input error: preroll not respected
const mvkstatus kMvkStatusInvalidStartTime                     MAKE_MVKERROR(kuiInputFacility, 0x1002); // Input error: invalid start time
const mvkstatus kMvkStatusInvalidVbiTime                       MAKE_MVKERROR(kuiInputFacility, 0x1003); // Input error: The time of the vbi surface must match the video surface
const mvkstatus kMvkStatusInvalidVbiSettings                   MAKE_MVKERROR(kuiInputFacility, 0x1004); // Input error: The software setting of vbi must match the hardware setting of Vbi.

//
// LQ Scaler errors
//

const unsigned int kuiLQScalerFacility = 0x312;

const mvkstatus kMvkStatusInvalidRectangle                     MAKE_MVKERROR(kuiLQScalerFacility, 0xA000); // LQ Scaler error: invalid rectangle
const mvkstatus kMvkStatusInvalidHzScalingFactor               MAKE_MVKERROR(kuiLQScalerFacility, 0xA001); // LQ Scaler error: invalid horizontal scaling factor
const mvkstatus kMvkStatusInvalidVtScalingFactor               MAKE_MVKERROR(kuiLQScalerFacility, 0xA002); // LQ Scaler error: invalid vertical scaling factor
const mvkstatus kMvkStatusNoDestinationPitchSupported          MAKE_MVKERROR(kuiLQScalerFacility, 0xA003); // LQ Scaler error: no destination pitch is supported
const mvkstatus kMvkStatusInvalidSourceSurfacePolarity         MAKE_MVKERROR(kuiLQScalerFacility, 0xA004); // LQ Scaler error: invalid source surface polarity
const mvkstatus kMvkStatusInvalidDestinationSurfacePolarity    MAKE_MVKERROR(kuiLQScalerFacility, 0xA005); // LQ Scaler error: invalid destination surface polarity
const mvkstatus kMvkStatusInvalidStatusValue                   MAKE_MVKERROR(kuiLQScalerFacility, 0xA006); // LQ Scaler error: Invalid Status Value
const mvkstatus kMvkStatusScalingNotSupported                  MAKE_MVKERROR(kuiLQScalerFacility, 0xA007); // LQ Scaler error: Scaling not supported
const mvkstatus kMvkStatusDeinterlacingNotSupported            MAKE_MVKERROR(kuiLQScalerFacility, 0xA008); // LQ Scaler error: Denterlacing not supported
const mvkstatus kMvkStatusVFilterPositionNotSupported          MAKE_MVKERROR(kuiLQScalerFacility, 0xA009); // LQ Scaler error: Vertical filter position not supported
const mvkstatus kMvkStatusVFilterSharpnessNotSupported         MAKE_MVKERROR(kuiLQScalerFacility, 0xA00A); // LQ Scaler error: Vertical filter sharpness not supported

//
// Memory manager errors
//

const unsigned int kuiMemMngrFacility = 0x313;

const mvkstatus kMvkStatusInvalidHwID                             MAKE_MVKERROR(kuiMemMngrFacility, 0xF001); // Memory manager error: invalid hardware ID
const mvkstatus kMvkStatusInvalidParameters                       MAKE_MVKERROR(kuiMemMngrFacility, 0xF002); // Memory manager error: invalid parameters
const mvkstatus kMvkStatusNoOnBoardMemory                         MAKE_MVKERROR(kuiMemMngrFacility, 0xF003); // Memory manager error: no on board memory
const mvkstatus kMvkStatusInvalidStructSize                       MAKE_MVKERROR(kuiMemMngrFacility, 0xF004); // Memory manager error: invalid struct size
const mvkstatus kMvkStatusInvalidStructVersion                    MAKE_MVKERROR(kuiMemMngrFacility, 0xF005); // Memory manager error: invalid struct version
const mvkstatus kMvkStatusInvalidBitCount                         MAKE_MVKERROR(kuiMemMngrFacility, 0xF006); // Memory manager error: invalid bit count
const mvkstatus kMvkStatusMemoryFreeFailure                       MAKE_MVKERROR(kuiMemMngrFacility, 0xF007); // Memory manager error: free memory failed
const mvkstatus kMvkStatusAvailableFnCallFailure                  MAKE_MVKERROR(kuiMemMngrFacility, 0xF008); // Memory manager error: available function call failed 
const mvkstatus kMvkStatusInvalidWidth                            MAKE_MVKERROR(kuiMemMngrFacility, 0xF009); // Memory manager error: invalid width
const mvkstatus kMvkStatusNewDescriptionSizeTooBig                MAKE_MVKERROR(kuiMemMngrFacility, 0xF00A); // Memory manager error: New surface description size is bigger then the already allocated buffer size.
const mvkstatus kMvkStatusAliasRegionRowPitchTooBig               MAKE_MVKERROR(kuiMemMngrFacility, 0xF00B); // Memory manager error: Computed row pitch with new alias region is bigger than reference surface pitch.
const mvkstatus kMvkStatusAliasRegionNonZeroHorizontalOffsetForIO MAKE_MVKERROR(kuiMemMngrFacility, 0xF00C); // Memory manager error: SetAliasRegion was called on an IO surface alias with a nonzero origin horizontal coordinate. 
const mvkstatus kMvkStatusAliasRegionOffsetNotAligned             MAKE_MVKERROR(kuiMemMngrFacility, 0xF00D); // Memory manager error: Origin specified in SetAliasRegion does not respect hardware specific alignment.

//
// Misc errors
//

const unsigned int kuiMiscFacility = 0x306;

const mvkstatus kMvkStatusInvalidCurrentThreadPriority         MAKE_MVKERROR(kuiMiscFacility, 0x0000); // Misc error: Invalid Current Thread Priority
const mvkstatus kMvkStatusInvalidNewThreadPriority             MAKE_MVKERROR(kuiMiscFacility, 0x0001); // Misc error: Invalid New Thread Priority
const mvkstatus kMvkStatusUnableAllocateMemoryDescriptor       MAKE_MVKERROR(kuiMiscFacility, 0x0002); // Misc error: Unable Allocate Memory Descriptor

const mvkstatus kMvkStatusAddListItemError                     MAKE_MVKERROR(kuiMiscFacility, 0x0003); // Misc error: Add List Item Error
const mvkstatus kMvkStatusRemoveListItemError                  MAKE_MVKERROR(kuiMiscFacility, 0x0004); // Misc error: Remove List Item Error
const mvkstatus kMvkStatusCantFindListItem                     MAKE_MVKERROR(kuiMiscFacility, 0x0005); // Misc error: Can't Find List Item
const mvkstatus kMvkStatusObjectCreationFailed                 MAKE_MVKERROR(kuiMiscFacility, 0x0006); // Misc error: Object Creation Failed
const mvkstatus kMvkStatusMemoryMappingError                   MAKE_MVKERROR(kuiMiscFacility, 0x0007); // Misc error: Memory Mapping Error
const mvkstatus kMvkStatusReadDoneCountNotNull                 MAKE_MVKERROR(kuiMiscFacility, 0x0008); // Misc error: Read Done Count Not Null
const mvkstatus kMvkStatusWriteDoneCountNotNull                MAKE_MVKERROR(kuiMiscFacility, 0x0009); // Misc error: Write Done Count Not Null
const mvkstatus kMvkStatusSynchroObjStillReferenced            MAKE_MVKERROR(kuiMiscFacility, 0x000A); // Misc error: Synchro Object Still Referenced
const mvkstatus kMvkStatusValueAlreadySet                      MAKE_MVKERROR(kuiMiscFacility, 0x000B); // Misc error: Value Already Set
const mvkstatus kMvkStatusNotLastTransfer                      MAKE_MVKERROR(kuiMiscFacility, 0x000C); // Misc error: Not Last Transfer
const mvkstatus kMvkStatusReadDoneCountError                   MAKE_MVKERROR(kuiMiscFacility, 0x000D); // Misc error: Read Done Count Error
const mvkstatus kMvkStatusWriteDoneCountError                  MAKE_MVKERROR(kuiMiscFacility, 0x000E); // Misc error: Write Done Count Error
const mvkstatus kMvkStatusNoMoreSynchroAvailable               MAKE_MVKERROR(kuiMiscFacility, 0x000F); // Misc error: No More Synchro Available

const mvkstatus kMvkStatusNotAKernelEvent                      MAKE_MVKERROR(kuiMiscFacility, 0x0010); // Misc error: The event's handle is not a kernel event.

//
//  Synchronization status codes declarations
//

const unsigned int kuiFacilitySynchro  = 0x306; //same as kuiMiscFacility but the error parsing lib requires a number

const int32_t kMvSynchroStatusNoError                                   = 0;// Sync: no error (this MUST absolutly be zero to match ring 3 no error)

const mvkstatus kMvSynchroStatusCancelled                            MAKE_MVKERROR(kuiFacilitySynchro, 0xF000);// Sync: Output dropped a buffer, cancelled
const mvkstatus kMvSynchroStatusHwFailure                            MAKE_MVKERROR(kuiFacilitySynchro, 0xF001);// Sync: HW failure
const mvkstatus kMvSynchroStatusPlayedLate                           MAKE_MVKWARNING(kuiFacilitySynchro, 0xF002);// Sync: Output dropped a buffer, played late
const mvkstatus kMvSynchroStatusCancelledLate                        MAKE_MVKWARNING(kuiFacilitySynchro, 0xF003);// Sync: Output dropped a buffer, cancelled late
const mvkstatus kMvSynchroStatusRepeatedFrame                        MAKE_MVKWARNING(kuiFacilitySynchro, 0xF004);// Sync: Output repeated a buffer
const mvkstatus kMvSynchroStatusReadCntError                         MAKE_MVKERROR(kuiFacilitySynchro, 0xF005);// Sync: Read count error
const mvkstatus kMvSynchroStatusWriteCntError                        MAKE_MVKERROR(kuiFacilitySynchro, 0xF006);// Sync: Write count error
const mvkstatus kMvSynchroStatusInvalidDeviceState                   MAKE_MVKERROR(kuiFacilitySynchro, 0xF007);// Sync: Invalid device state
const mvkstatus kMvSynchroStatusInvalidBuffer                        MAKE_MVKERROR(kuiFacilitySynchro, 0xF008);// Sync: Invalid buffer
const mvkstatus kMvSynchroStatusQueueBufferFull                      MAKE_MVKERROR(kuiFacilitySynchro, 0xF009); // Sync: Buffer queue is full
const mvkstatus kMvSynchroStatusInvalidBufferUnstableInputSignal     MAKE_MVKWARNING(kuiFacilitySynchro, 0xF00A);// Sync: The input signal has been unstable during buffer usage into the hardware, it is (or could be) invalid
const mvkstatus kMvSynchroStatusInvalidBufferUnstableGenlockSignal   MAKE_MVKWARNING(kuiFacilitySynchro, 0xF00B);// Sync: The genlock signal has been unstable during buffer usage into the hardware, it is (or could be) invalid
const mvkstatus kMvSynchroStatusInvalidBufferTime                    MAKE_MVKWARNING(kuiFacilitySynchro, 0xF00C);// Sync: Invalid buffer time (late or not respect the preroll)
const mvkstatus kMvSynchroStatusDeviceNotReady                       MAKE_MVKWARNING(kuiFacilitySynchro, 0xF00D);// Sync: Device cannot accept buffer because it is busy
const mvkstatus kMvSynchroStatusInvalidBufferNoInputSignal           MAKE_MVKWARNING(kuiFacilitySynchro, 0xF00E);// Sync: The input signal has not been detected during buffer usage into the hardware, it is mostly black
const mvkstatus kMvSynchroStatusInterruptDropped                     MAKE_MVKWARNING(kuiFacilitySynchro, 0xF00F);// Sync: An interrupt was missed. The delay between two Isr was too long.
const mvkstatus kMvSynchroStatusOutOfBuffer                          MAKE_MVKWARNING(kuiFacilitySynchro, 0xF010);// Sync: The input does not have any other buffers to capture.
const mvkstatus kMvSynchroStatusInvalidBufferSize                    MAKE_MVKERROR(kuiFacilitySynchro, 0xF011);// Sync: Invalid buffer size = 0
const mvkstatus kMvSynchroStatusInvalidBufferFormat                  MAKE_MVKERROR(kuiFacilitySynchro, 0xF012);// Sync: Invalid buffer format
const mvkstatus kMvSynchroStatusInvalidBufferPointer                 MAKE_MVKERROR(kuiFacilitySynchro, 0xF013);// Sync: Invalid buffer pointer
const mvkstatus kMvSynchroStatusInvalidBufferForRead                 MAKE_MVKERROR(kuiFacilitySynchro, 0xF014);// Sync: Invalid buffer for read (not ready for read)
const mvkstatus kMvSynchroStatusCancelledLateFirmware                MAKE_MVKWARNING(kuiFacilitySynchro, 0xF015);// Sync: Output dropped a buffer, cancelled late by the Firmware
                                                                     
//
// Mmgd errors
//

const unsigned int kuiMmgdFacility = 0x315;

const mvkstatus kMvkStatusErrorNestedEffect                    MAKE_MVKERROR(kuiMmgdFacility, 0x0000); // Mmgd error: Nested Effect
const mvkstatus kMvkStatusErrorEffectInputInError              MAKE_MVKERROR(kuiMmgdFacility, 0x0001); // Mmgd error: Effect Input In Error
const mvkstatus kMvkStatusErrorEffectOutputInError             MAKE_MVKERROR(kuiMmgdFacility, 0x0002); // Mmgd error: Effect Output In Error
const mvkstatus kMvkStatusErrorTooManyEffectsInQueue           MAKE_MVKERROR(kuiMmgdFacility, 0x0003); // Mmgd error: Too Many Effects In Queue
const mvkstatus kMvkStatusErrorUnexpectedEndSynchronizedAccess MAKE_MVKERROR(kuiMmgdFacility, 0x0004); // Mmgd error: Unexpected End Synchronized Access
const mvkstatus kMvkStatusErrorUnexpectedNotificationReceived  MAKE_MVKERROR(kuiMmgdFacility, 0x0005); // Mmgd error: Unexpected Notification Received
const mvkstatus kMvkStatusErrorFlushingAllPendingData          MAKE_MVKERROR(kuiMmgdFacility, 0x0006); // Mmgd error: Flushing All Pending Data
const mvkstatus kMvkStatusErrorTooManyInputSurfaces            MAKE_MVKERROR(kuiMmgdFacility, 0x0007); // Mmgd error: Too Many Input Surfaces
const mvkstatus kMvkStatusErrorOutOfBusMasteringBuffers        MAKE_MVKERROR(kuiMmgdFacility, 0x0008); // Mmgd error: Out Of Bus Mastering Buffers

//
// Neptune errors
//

const unsigned int kuiNeptuneFacility = 0x31A;

const mvkstatus kMvkStatusInvalidSynchroObject                 MAKE_MVKERROR(kuiNeptuneFacility, 0xA000); // Neptune error: Invalid Synchro Object
const mvkstatus kMvkStatusInvalidStructureSize                 MAKE_MVKERROR(kuiNeptuneFacility, 0xA001); // Neptune error: Invalid Structure Size
const mvkstatus kMvkStatusInvalidSurfaceSize                   MAKE_MVKERROR(kuiNeptuneFacility, 0xA002); // Neptune error: Invalid Surface Size
const mvkstatus kMvkStatusInvalidTransferObject                MAKE_MVKERROR(kuiNeptuneFacility, 0xA003); // Neptune error: Invalid Transfer Object
const mvkstatus kMvkStatusInvalidDestinationSurfaceSize        MAKE_MVKERROR(kuiNeptuneFacility, 0xA004); // Neptune error: Invalid Destination Surface Size
const mvkstatus kMvkStatusDestinationBiggerThanEres            MAKE_MVKERROR(kuiNeptuneFacility, 0xA005); // Neptune error: Destination Bigger Than Eres
const mvkstatus kMvkStatusAddToWaitingListFailed               MAKE_MVKERROR(kuiNeptuneFacility, 0xA006); // Neptune error: Add To Waiting List Failed
const mvkstatus kMvkStatusInvalidSurfaceDimension              MAKE_MVKERROR(kuiNeptuneFacility, 0xA007); // Neptune error: Invalid Surface Dimension
const mvkstatus kMvkStatusInvalidShapeAttributeForInputTx      MAKE_MVKERROR(kuiNeptuneFacility, 0xA008); // Neptune error: Invalid shape combination for input transfer
const mvkstatus kMvkStatusInvalidShapeAttributeForOutputTx     MAKE_MVKERROR(kuiNeptuneFacility, 0xA009); // Neptune error: Invalid shape combination for output transfer


//
// OnBoard IO Errors
//
const unsigned int kuiOnBoardIOFacility = 0x31E;

//Error codes definitions
const mvkstatus kMvkStatusInvalidBoardId                       MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF001); // OnBoardIO error: Invalid Board ID
const mvkstatus kMvkStatusUnsupportedInterruptVector           MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF002); // OnBoardIO error: Unsupported interrupt vector
const mvkstatus kMvkStatusUnsupportedInterruptStatus           MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF003); // OnBoardIO error: Unsupported interrupt status
const mvkstatus kMvkStatusUnsupportedControlParameter          MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF004); // OnBoardIO error: Unsupported parameter
const mvkstatus kMvkStatusCommandNotSupported                  MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF005); // OnBoardIO error: Command (SetDefault, GetDefault, SetCurrent, ...) not supported
const mvkstatus kMvkStatusUnsupportedVInChannel                MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF006); // OnBoardIO error: Unsupported video input channel
const mvkstatus kMvkStatusUnsupportedVOutChannel               MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF007); // OnBoardIO error: Unsupported video output channel
const mvkstatus kMvkStatusUnsupportedVInSource                 MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF008); // OnBoardIO error: Unsupported video input source
const mvkstatus kMvkStatusUnsupportedGenlockSource             MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF009); // OnBoardIO error: Unsupported genlock input source
const mvkstatus kMvkStatusParameterOutOfRange                  MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF00A); // OnBoardIO error: Parameter out of range
const mvkstatus kMvkStatusInvalidVideoChannelForParam          MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF00B); // OnBoardIO error: Invalid video channel for the specified paramater
const mvkstatus kMvkStatusComputationError                     MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF00C); // OnBoardIO error: Computation error
const mvkstatus kMvkStatusInvalidGenlockRes                    MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF00D); // OnBoardIO error: Genlock resolution invalid
const mvkstatus kMvkStatusInvalidInOutRes                      MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF00E); // OnBoardIO error: Input/Output resolution invalid
const mvkstatus kMvkStatusInvalidGenlockStatus                 MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF00F); // OnBoardIO error: Invalid genlock status combination
const mvkstatus kMvkStatusInterfacePtrNotFound                 MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF010); // OnBoardIO error: The interface pointer was not found in the IF Container list.
const mvkstatus kMvkStatusUnsupportedEAInChannel               MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF011); // OnBoardIO error: Unsupported embedded audio input channel
const mvkstatus kMvkStatusUnsupportedEAOutChannel              MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF012); // OnBoardIO error: Unsupported embedded audio output channel
const mvkstatus kMvkStatusUnsupportedAudioCaptureChannel       MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF013); // OnBoardIO error: Unsupported audio capture channel
const mvkstatus kMvkStatusUnsupportedAudioPlaybackChannel      MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF014); // OnBoardIO error: Unsupported audio playback channel
const mvkstatus kMvkStatusUnsupportedCaptureAudioSource        MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF015); // OnBoardIO error: Unsupported capture audio source
const mvkstatus kMvkStatusUnsupportedAesEbuInputChannel        MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF016); // OnBoardIO error: Unsupported AES/EBU input channel
const mvkstatus kMvkStatusUnsupportedAesEbuOutputChannel       MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF017); // OnBoardIO error: Unsupported AES/EBU output channel
const mvkstatus kMvkStatusUnsupportedAudioCaptureClkSrc        MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF018); // OnBoardIO error: Unsupported audio capture clock source
const mvkstatus kMvkStatusPowerPCTimeOut                       MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF019); // OnBoardIO error: Timeout expired while waiting for the PPC
const mvkstatus kMvkStatusPowerPCReturnedError                 MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF01A); // OnBoardIO error: An error command was returned by the Power PC unit.
const mvkstatus kMvkStatusPowerPCWrongAnswer                   MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF01B); // OnBoardIO error: The PowerPC did not answer with the right command.
const mvkstatus kMvkStatusPowerPCInvalidCommand                MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF01C); // OnBoardIO error: The returned command does not exist.
const mvkstatus kMvkStatusPowerPCInvalidCommandSize            MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF01D); // OnBoardIO error: The returned size of the specified command is not right.
const mvkstatus kMvkStatusPowerPCInvalidPageCntAndSize         MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF01E); // OnBoardIO error: The dongle EEPROM page size or count is invalid
const mvkstatus kMvkStatusPowerPCWrongDongleMemoryPage         MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF01F); // OnBoardIO error: Wrong dongle memory page returned.
const mvkstatus kMvkStatusPowerPCWrongPageOffset               MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF020); // OnBoardIO error: The page offset is not the one asked for.
const mvkstatus kMvkStatusPowerPCWrongPagePartSize             MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF021); // OnBoardIO error: The page size is not the one asked for.
const mvkstatus kMvkStatusPowerPCInitializationFailed          MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF022); // OnBoardIO error: The initialization of the Power PC controller object has failed.
const mvkstatus kMvkStatusInvalidVideoSignalType               MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF023); // OnBoardIO error: Invalid video signal type
const mvkstatus kMvkStatusDongleWrongInitialCRC                MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF024); // OnBoardIO error: The dongle content has a wrong CRC before the operation
const mvkstatus kMvkStatusDataWrongCRC                         MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF025); // OnBoardIO error: The data provided has wrong CRC
const mvkstatus kMvkStatusDongleDataCheckFailed                MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF026); // OnBoardIO error: The dongle content after the operation is not the expected one
const mvkstatus kMvkStatusDongleReturnedError                  MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF027); // OnBoardIO error: The dongle returned an error
const mvkstatus kMvkStatusUnsupportedEDIDVersion               MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF028); // OnBoardIO error: The version of the EDID structure contained in the monitor's EEPROM is not supported by this driver.
const mvkstatus kMvkStatusEDIDChecksumError                    MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF029); // OnBoardIO error: Checksum error in the EDID data of DVI monitor
const mvkstatus kMvkStatusInformationUnavailable               MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF02A); // OnBoardIO error: The require information cannot be found and in therefore not available.
const mvkstatus kMvkStatusUnsupportedAnalogAudioInputChannel   MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF02B); // OnBoardIO error: Unsupported Analog Audio input channel
const mvkstatus kMvkStatusUnsupportedCodecMemorySize           MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF02C); // OnBoardIO error: Unsupported codec memory size
const mvkstatus kMvkStatusUnsupportedVOutSource                MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF02D); // OnBoardIO error: Unsupported video Output source
const mvkstatus kMvkStatusInvalidDongleSelection               MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF02E); // OnBoardIO error: The dongle selection is invalid
const mvkstatus kMvkStatusUnsupportedHWFeature                 MAKE_MVKERROR(kuiOnBoardIOFacility, 0xF02F); // OnBoardIO error: The Hardware Feature is Not Enabled

//
// Output errors
//

const unsigned int kuiOutputFacility = 0x30D;

const mvkstatus kMvkStatusOutputBufferLate                     MAKE_MVKSUCCESS(kuiOutputFacility, 0x0000); // mvkOutput error: OutputBufferLate

//Error codes definitions

const mvkstatus kMvkStatusInitializationFailed                 MAKE_MVKERROR(kuiOutputFacility, 0xF002); // Output error: Initialization Failed
const mvkstatus kMvkStatusSourceBufferInError                  MAKE_MVKERROR(kuiOutputFacility, 0xF003); // Output error: Source Buffer In Error

const mvkstatus kMvkStatusCantGetClockPtr                      MAKE_MVKERROR(kuiOutputFacility, 0xF005); // Output error: Can't Get Clock Ptr
const mvkstatus kMvkStatusSetCallbackError                     MAKE_MVKERROR(kuiOutputFacility, 0xF006); // Output error: Set Callback Error
const mvkstatus kMvkStatusClearCallbackError                   MAKE_MVKERROR(kuiOutputFacility, 0xF007); // Output error: Clear Callback Error
const mvkstatus kMvkStatusInterfaceNotAvailable                MAKE_MVKERROR(kuiOutputFacility, 0xF008); // Output error: Interface is Not Available
const mvkstatus kMvkStatusCantGetResolutions                   MAKE_MVKERROR(kuiOutputFacility, 0xF009); // Output error: Can't Get Resolutions
const mvkstatus kMvkStatusEventsNotCreated                     MAKE_MVKERROR(kuiOutputFacility, 0xF00A); // Output error: Events is Not Created

const mvkstatus kMvkStatusSetStillModeTooLate                  MAKE_MVKERROR(kuiOutputFacility, 0xF00C); // Output error: Set Still Mode Too Late
const mvkstatus kMvkStatusQueueItemError                       MAKE_MVKERROR(kuiOutputFacility, 0xF00D); // Output error: Queue Item Error
const mvkstatus kMvkStatusQueueError                           MAKE_MVKERROR(kuiOutputFacility, 0xF00E); // Output error: Queue Error
const mvkstatus kMvkStatusUnQueueError                         MAKE_MVKERROR(kuiOutputFacility, 0xF00F); // Output error: UnQueue Error
const mvkstatus kMvkStatusSynchroInError                       MAKE_MVKERROR(kuiOutputFacility, 0xF010); // Output error: Synchro In Error
const mvkstatus kMvkStatusRegisterForReadFailed                MAKE_MVKERROR(kuiOutputFacility, 0xF011); // Output error: Register For Read Failed
const mvkstatus kMvkStatusOutputBufferLateError                MAKE_MVKERROR(kuiOutputFacility, 0xF012); // Output error: Output Buffer Late Error
const mvkstatus kMvkStatusBufferTimeAlreadyQueued              MAKE_MVKERROR(kuiOutputFacility, 0xF013); // Output error: Buffer Time Already Queued
const mvkstatus kMvkStatusPolarityMismatch                     MAKE_MVKERROR(kuiOutputFacility, 0xF014); // Output error: Polarity Mismatches
const mvkstatus kMvkStatusBufferOutOfOrder                     MAKE_MVKERROR(kuiOutputFacility, 0xF015); // Output error: Buffer is Out Of Order
const mvkstatus kMvkStatusRequestLate                          MAKE_MVKERROR(kuiOutputFacility, 0xF016); // Output error: Request is Late
const mvkstatus kMvkStatusInvalidVBISize                       MAKE_MVKERROR(kuiOutputFacility, 0xF017); // Output error: VBI size is invalid for the output resoluiton 

//IoCtl ORed error status codes
const mvkstatus kMvkStatusAddBufferFailed                      MAKE_MVKERROR(kuiOutputFacility, 0x0100); // Output IoCtl ORed error: Add Buffer Failed
const mvkstatus kMvkStatusSetStillModeFailed                   MAKE_MVKERROR(kuiOutputFacility, 0x0200); // Output IoCtl ORed error: Set Still Mode Failed
const mvkstatus kMvkStatusCancelAllFailed                      MAKE_MVKERROR(kuiOutputFacility, 0x0300); // Output IoCtl ORed error: Cancel All Failed
const mvkstatus kMvkStatusCancelFromFailed                     MAKE_MVKERROR(kuiOutputFacility, 0x0400); // Output IoCtl ORed error: Cancel From Failed
const mvkstatus kMvkStatusGetPrerollFailed                     MAKE_MVKERROR(kuiOutputFacility, 0x0500); // Output IoCtl ORed error: Get Preroll Failed
const mvkstatus kMvkStatusGetNotifEventsFailed                 MAKE_MVKERROR(kuiOutputFacility, 0x0600); // Output IoCtl ORed error: Get Notif Events Failed

//
// System clock errors
//
const unsigned int kuiClockFacility = 0x300;

const mvkstatus kMvkStatusInvalidPointer                       MAKE_MVKERROR(kuiClockFacility, 0x0000); // System clock error: Invalid Pointer
const mvkstatus kMvkStatusInvalidSystemClockResolution         MAKE_MVKERROR(kuiClockFacility, 0x0001); // System clock error: Invalid system clock resolution Resolution

//
// Transfer errors
//

const unsigned int kuiTransferFacility = 0x314;

const mvkstatus kMvkStatusInvalidBoardID                       MAKE_MVKERROR(kuiTransferFacility, 0xF000); // Transfer error: Invalid Board ID
const mvkstatus kMvkStatusInvalidMemLocationParams             MAKE_MVKERROR(kuiTransferFacility, 0xF001); // Transfer error: Invalid Memory Location Params
const mvkstatus kMvkStatusSGBufferError                        MAKE_MVKERROR(kuiTransferFacility, 0xF002); // Transfer error: SG Buffer Error
const mvkstatus kMvkStatusSGListGenerateError                  MAKE_MVKERROR(kuiTransferFacility, 0xF003); // Transfer error: SG List Generate Error
const mvkstatus kMvkStatusInvalidTxStatusValue                 MAKE_MVKERROR(kuiTransferFacility, 0xF004); // Transfer error: Invalid Tx Status Value
const mvkstatus kMvkStatusInvalidTransferSize                  MAKE_MVKERROR(kuiTransferFacility, 0xF005); // Transfer error: Invalid video transfer size
const mvkstatus kMvkStatusInvalidHostBuffer                    MAKE_MVKERROR(kuiTransferFacility, 0xF006); // Transfer error: Invalid parameter(s) in host memory buffer
const mvkstatus kMvkStatusInvalidLocalBuffer                   MAKE_MVKERROR(kuiTransferFacility, 0xF007); // Transfer error: Invalid parameter(s) in local memory buffer
const mvkstatus kMvkStatusHostBufferNotQuadWordAligned         MAKE_MVKERROR(kuiTransferFacility, 0xF008); // Transfer error: The received host buffer is not quadword aligned
const mvkstatus kMvkStatusSynchroUsageProblem                  MAKE_MVKERROR(kuiTransferFacility, 0xF009); // Transfer error: Problem using synchro of buffer
const mvkstatus kMvkStatusAudioSizesNotEqual                   MAKE_MVKERROR(kuiTransferFacility, 0xF00A); // Transfer error: The local and host memory buffers must have the same size 
const mvkstatus kMvkStatusAudioNumberOfTracksNotEqual          MAKE_MVKERROR(kuiTransferFacility, 0xF00B); // Transfer error: The local and host memory buffers must have the same number of tracks 
const mvkstatus kMvkStatusComponentBitCountNotEqual            MAKE_MVKERROR(kuiTransferFacility, 0xF00C); // Transfer error: The local and host memory buffers must have the same component bit count
const mvkstatus kMvkStatusAudioBitsPerSampleNotEqual           MAKE_MVKERROR(kuiTransferFacility, 0xF00D); // Transfer error: The local and host audio buffers must have the same number of valid bits per sample
const mvkstatus kMvkStatusInvalidVideoBufferSize               MAKE_MVKERROR(kuiTransferFacility, 0xF00E); // Transfer error: Invalid Host Video buffer size
const mvkstatus kMvkStatusInvalidAudioBufferSize               MAKE_MVKERROR(kuiTransferFacility, 0xF00F); // Transfer error: Invalid Host Audio buffer size
const mvkstatus kMvkStatusInvalidVancBufferSize                MAKE_MVKERROR(kuiTransferFacility, 0xF010); // Transfer error: Invalid Host Vanc buffer size

//
// Audio input errors
//

const unsigned int kuiAudioInputFacility = 0x31F;

const mvkstatus kMvkStatusInvalidAudioSamplesCount               MAKE_MVKERROR(kuiAudioInputFacility, 0x0000); // Audio input error: The audio samples count is not supported vs the input resolution
const mvkstatus kMvkStatusInvalidAudioSamplesPolarity            MAKE_MVKERROR(kuiAudioInputFacility, 0x0001); // Audio input error: The audio samples polarity is not supported vs the input resolution
const mvkstatus kMvkStatusAudioInputBufferInvalidDataType        MAKE_MVKERROR(kuiAudioInputFacility, 0x0002); // Audio input error: Buffer data type not matching the channel data type 
const mvkstatus kMvkStatusAudioInputBufferInvalidNumberOfTracks  MAKE_MVKERROR(kuiAudioInputFacility, 0x0003);// Audio input error: Buffer data has invalid number of tracks 

//
// Audio output errors
//

const unsigned int kuiAudioOutputFacility = 0x320;

const mvkstatus kMvkStatusAudioOutputBufferLate                  MAKE_MVKERROR(kuiAudioOutputFacility, 0x0000);  // Audio output error: BufferLate
const mvkstatus kMvkStatusAudioOutputBufferInvalidDataType       MAKE_MVKERROR(kuiAudioOutputFacility, 0x0001);  // Audio output error: Buffer data type not matching the channel data type 
const mvkstatus kMvkStatusAudioOutputBufferInvalidNumberOfTracks MAKE_MVKERROR(kuiAudioOutputFacility, 0x0002);// Audio output error: Buffer data has invalid number of tracks 

//
// Bus errors
//

const uint32_t kulBusFacility = 0xBAD;

const mvkstatus kMvkStatusMasterInterruptError                 MAKE_MVKERROR(kulBusFacility, 0x3000); // Bus error: Master Interrupt Error
const mvkstatus kMvkStatusInvalidRegisterLUT                   MAKE_MVKERROR(kulBusFacility, 0x3001); // Bus error: Invalid Register LUT
const mvkstatus kMvkStatusPciDmaAddressError                   MAKE_MVKERROR(kulBusFacility, 0x3002); // Bus error: Pci Dma Address Error
const mvkstatus kMvkStatusDwnldBobFpgaTimeOut                  MAKE_MVKERROR(kulBusFacility, 0x3003); // Bus error: Download Bob Fpga TimeOut
const mvkstatus kMvkStatusBobDetectionFailed                   MAKE_MVKERROR(kulBusFacility, 0x3004); // Bus error: Bob Detection Failed
const mvkstatus kMvkStatusInvalidIntDescriptor                 MAKE_MVKERROR(kulBusFacility, 0x3005); // Bus error: Invalid Int Descriptor
const mvkstatus kMvkStatusInvalidGennumStandards               MAKE_MVKERROR(kulBusFacility, 0x3006); // Bus error: Invalid Gennum Standards
const mvkstatus kMvkStatusInvalidInterruptSource               MAKE_MVKERROR(kulBusFacility, 0x3007); // Bus error: Invalid interrupt source
const mvkstatus kMvkStatusBadSriCall                           MAKE_MVKERROR(kulBusFacility, 0x3008); // Bus error: SRI bus cannot work at execution level > keDeferedInterruptExecutionLevel
const mvkstatus kMvkStatusSriTimeout                           MAKE_MVKERROR(kulBusFacility, 0x3009); // Bus error: A timeout has happen while using the SRI bus
const mvkstatus kMvkStatusSriInvalidAddress                    MAKE_MVKERROR(kulBusFacility, 0x300a); // Bus error: Error acknowledging the address on the SRI bus 
const mvkstatus kMvkStatusSriHpDataAlreadyValid                MAKE_MVKERROR(kulBusFacility, 0x300b); // Bus error: SRI bus state error
const mvkstatus kMvkStatusFPGANotLoaded                        MAKE_MVKERROR(kulBusFacility, 0x300c); // Bus error: A FPGA is not loaded properly

//
// Audio Bus input and output errors
//
const uint32_t kulAudioBusIOFacility = 0x307;

const mvkstatus kMvkStatusAudioInputBufferInvalidSize          MAKE_MVKERROR(kulAudioBusIOFacility, 0x0000); // Audio intput error: Buffer size =0
const mvkstatus kMvkStatusAudioInputBufferInvalidFormat        MAKE_MVKERROR(kulAudioBusIOFacility, 0x0001); // Audio input error: Buffer format != 32 bits
const mvkstatus kMvkStatusAudioInputBufferInvalidChannel       MAKE_MVKERROR(kulAudioBusIOFacility, 0x0002); // Audio input error: Buffer channel != 2 (stereo)
const mvkstatus kMvkStatusAudioInputInvalidStartTime           MAKE_MVKERROR(kulAudioBusIOFacility, 0x0003); // Audio input error: Start time invalid (not respect preroll)
const mvkstatus kMvkStatusAudioInputBufferInvalidMemory        MAKE_MVKERROR(kulAudioBusIOFacility, 0x0004); // Audio input error: Buffer host memory invalid
const mvkstatus kMvkStatusAudioInputQueueFull                  MAKE_MVKERROR(kulAudioBusIOFacility, 0x0005); // Audio input error: Buffer queue overflow
const mvkstatus kMvkStatusAudioInputBufferInvalidTime          MAKE_MVKERROR(kulAudioBusIOFacility, 0x0006); // Audio input error: Buffer with invalid time
const mvkstatus kMvkStatusAudioInputDeviceNotReady             MAKE_MVKERROR(kulAudioBusIOFacility, 0x0007); // Audio input error: input DMA not ready then can't start
const mvkstatus kMvkStatusAudioOutputBufferInvalidSize         MAKE_MVKERROR(kulAudioBusIOFacility, 0x0008); // Audio output error: Buffer size =0
const mvkstatus kMvkStatusAudioOutputBufferInvalidFormat       MAKE_MVKERROR(kulAudioBusIOFacility, 0x0009); // Audio output error: Buffer format != 32 bits
const mvkstatus kMvkStatusAudioOutputBufferInvalidChannel      MAKE_MVKERROR(kulAudioBusIOFacility, 0x000a); // Audio output error: Buffer channel != 2 (stereo)
const mvkstatus kMvkStatusAudioOutputInvalidStartTime          MAKE_MVKERROR(kulAudioBusIOFacility, 0x000b); // Audio output error: Start time invalid (not respect preroll)
const mvkstatus kMvkStatusAudioOutputBufferInvalidMemory       MAKE_MVKERROR(kulAudioBusIOFacility, 0x000c); // Audio output error: Buffer host memory invalid
const mvkstatus kMvkStatusAudioOutputQueueFull                 MAKE_MVKERROR(kulAudioBusIOFacility, 0x000d); // Audio output error: Buffer queue overflow
const mvkstatus kMvkStatusAudioOutputBufferInvalidTime         MAKE_MVKERROR(kulAudioBusIOFacility, 0x000e); // Audio output error: Buffer with invalid time


//
// MXO State errors
//
const uint32_t kulMxoStateFacility = 0x337;

const mvkstatus kMvkStatusMxoStateAlreadyLocked                 MAKE_MVKERROR(kulMxoStateFacility, 0x0000); // The MXO State is already Locked by another process or thread.
const mvkstatus kMvkStatusMxoStateNotLocked                     MAKE_MVKERROR(kulMxoStateFacility, 0x0001); // The MXO State is not locked by any process.
const mvkstatus kMvkStatusMxoStateAlreadyLockedByAnotherProcess MAKE_MVKERROR(kulMxoStateFacility, 0x0002); // The MXO State is already locked by another process.
const mvkstatus kMvkStatusMxoNotReadyYet                        MAKE_MVKERROR(kulMxoStateFacility, 0x0003); // The MXO box is not yet ready to be lock.
const mvkstatus kMvkStatusMxoStateAlreadyLockedByAnotherThreadInSameProcess  MAKE_MVKERROR(kulMxoStateFacility, 0x0004); // The MXO State is already locked by another thread in the same process.
const mvkstatus kMvkStatusMxoStateBeingUnplugged                MAKE_MVKERROR(kulMxoStateFacility, 0x0005); // The MXO is unplugged, so the driver is shutting down



//
// AVCIO CODEC errors
//
const uint32_t kulAvcioCodecFacility = 0x264;

//Parameter's validation errors
const mvkstatus kMvkStatusAvcioCodecInvalidParameter              MAKE_MVKERROR(kulAvcioCodecFacility, 0x0000); // AVCIO Codec Error: An invalid parameter has been passed to an API function.
const mvkstatus kMvkStatusAvcioCodecInvalidSurface                MAKE_MVKERROR(kulAvcioCodecFacility, 0x0001); // AVCIO Codec Error: The incoming surface is invalid.
const mvkstatus kMvkStatusAvcioCodecInvalidState                  MAKE_MVKERROR(kulAvcioCodecFacility, 0x0002); // AVCIO Codec Error: Wrong State, the current operation cannot be performed.
const mvkstatus kMvkStatusAvcioCodecInvalidMode                   MAKE_MVKERROR(kulAvcioCodecFacility, 0x0003); // AVCIO Codec Error: Wrong Mode, the current operation cannot be performed with this configuration.
const mvkstatus kMvkStatusAvcioCodecStateError                    MAKE_MVKERROR(kulAvcioCodecFacility, 0x0004); // AVCIO Codec Error: Codec is in error State, the current operation cannot be performed.

//MicroCode loading's errors
const mvkstatus kMvkStatusAvcioCodecMicroCodeAlreadyLoaded        MAKE_MVKERROR(kulAvcioCodecFacility, 0x1000); // AVCIO Codec Error: The MicroCode is already loaded and functionnal.
const mvkstatus kMvkStatusAvcioCodecFailedToResetMicroCode        MAKE_MVKERROR(kulAvcioCodecFacility, 0x1001); // AVCIO Codec Error: The driver failed to reset the MicroCode.
const mvkstatus kMvkStatusAvcioCodecFailedToGetMicroCodeLocation  MAKE_MVKERROR(kulAvcioCodecFacility, 0x1002); // AVCIO Codec Error: The driver failed to get the MicroCode local address.

//Flash Memory's errors and warnings
const mvkstatus kMvkStatusAvcioCodecFlashMemoryAllocationFailed   MAKE_MVKERROR(kulAvcioCodecFacility, 0x2000); // AVCIO Codec Error: The Flash memory manager failed to allocate memory.

//Codec' errors
const mvkstatus kMvkStatusAvcioCodecFailedToUpdateSurface         MAKE_MVKERROR(kulAvcioCodecFacility, 0x3000); // AVCIO Codec Error: The Codec failed to update the surface.
const mvkstatus kMvkStatusAvcioCodecFailedToQueueACommand         MAKE_MVKERROR(kulAvcioCodecFacility, 0x3001); // AVCIO Codec Error: The Codec MicroCode failed to queue a command or buffer.
const mvkstatus kMvkStatusAvcioCodecInvalidResolution             MAKE_MVKERROR(kulAvcioCodecFacility, 0x3002); // AVCIO Codec Error: The Codec has been passed an invalid resolution.

//Codec Device State's Errors
//Initialize Microcode
const mvkstatus kMvkAvcioCodecLastErrorA2StopFailed                        MAKE_MVKERROR(kulAvcioCodecFacility, 0x4000); // AVCIO Codec Error: The Stop command returned an error.
const mvkstatus kMvkAvcioCodecLastErrorFlushCodecSurfaceListFailed         MAKE_MVKERROR(kulAvcioCodecFacility, 0x4001); // AVCIO Codec Error: A problem occured in the Flush Codec Surface List.
const mvkstatus kMvkAvcioCodecLastErrorFlushDmaSurfaceListFailed           MAKE_MVKERROR(kulAvcioCodecFacility, 0x4002); // AVCIO Codec Error: A problem occured in the Flush DMA Surface List.
const mvkstatus kMvkAvcioCodecLastErrorSetCodecUsageFailed                 MAKE_MVKERROR(kulAvcioCodecFacility, 0x4003); // AVCIO Codec Error: Failed to set the Codec Usage for input DMA sharing.
const mvkstatus kMvkAvcioCodecLastErrorInvalidInputResolution              MAKE_MVKERROR(kulAvcioCodecFacility, 0x4004); // AVCIO Codec Error: Invalid Input Resolution parameter.
const mvkstatus kMvkAvcioCodecLastErrorInvalidOutputResolution             MAKE_MVKERROR(kulAvcioCodecFacility, 0x4005); // AVCIO Codec Error: Invalid Output Resolution parameter.
const mvkstatus kMvkAvcioCodecLastErrorResetMicroCodeFailed                MAKE_MVKERROR(kulAvcioCodecFacility, 0x4006); // AVCIO Codec Error: Could not reset Codec chip.
const mvkstatus kMvkAvcioCodecLastErrorSetDmaResolutionFailed              MAKE_MVKERROR(kulAvcioCodecFacility, 0x4007); // AVCIO Codec Error: Set DMA resolution failed.
const mvkstatus kMvkAvcioCodecLastErrorSetA2InputParamFailed               MAKE_MVKERROR(kulAvcioCodecFacility, 0x4008); // AVCIO Codec Error: Set Codec Input resolution failed.
const mvkstatus kMvkAvcioCodecLastErrorSetA2OutputParamFailed              MAKE_MVKERROR(kulAvcioCodecFacility, 0x4009); // AVCIO Codec Error: Set Codec Output resolution failed.
const mvkstatus kMvkAvcioCodecLastErrorSetA2EncoderParamFailed             MAKE_MVKERROR(kulAvcioCodecFacility, 0x400a); // AVCIO Codec Error: Set Codec Encoder Parameters failed.
const mvkstatus kMvkAvcioCodecLastErrorSetA2DecoderParamFailed             MAKE_MVKERROR(kulAvcioCodecFacility, 0x400b); // AVCIO Codec Error: Set Codec Decoder Parameters failed.
const mvkstatus kMvkAvcioCodecLastErrorProgramCodecInDmaResolutionFailed   MAKE_MVKERROR(kulAvcioCodecFacility, 0x400c); // AVCIO Codec Error: Program Codec In DMA resolution failed.
const mvkstatus kMvkAvcioCodecLastErrorProgramCodecOutDmaResolutionFailed  MAKE_MVKERROR(kulAvcioCodecFacility, 0x400d); // AVCIO Codec Error: Program Codec Out DMA resolution failed.
const mvkstatus kMvkAvcioCodecLastErrorA2InitFailed                        MAKE_MVKERROR(kulAvcioCodecFacility, 0x400e); // AVCIO Codec Error: Codec Init command failed.
const mvkstatus kMvkAvcioCodecLastErrorSetA2SystemClockFailed              MAKE_MVKERROR(kulAvcioCodecFacility, 0x400f); // AVCIO Codec Error: Set Codec System Clock command failed.
const mvkstatus kMvkAvcioCodecLastErrorSetA2PlaySpeedFailed                MAKE_MVKERROR(kulAvcioCodecFacility, 0x4010); // AVCIO Codec Error: Set Codec PlaySpeed command failed.
const mvkstatus kMvkAvcioCodecLastErrorSetA2StartParamFailed               MAKE_MVKERROR(kulAvcioCodecFacility, 0x4011); // AVCIO Codec Error: Set Codec start parameters failed.
//GetSurface & PutSurface
const mvkstatus kMvkAvcioCodecLastErrorInvalidParam                        MAKE_MVKERROR(kulAvcioCodecFacility, 0x4012); // AVCIO Codec Error: An invalid parameter have been passed to the GetSurface or PutSurface.
const mvkstatus kMvkAvcioCodecLastErrorInvalidSynchro                      MAKE_MVKERROR(kulAvcioCodecFacility, 0x4013); // AVCIO Codec Error: An invalid synchro have been passed to the GetSurface or PutSurface.
const mvkstatus kMvkAvcioCodecLastErrorSynchroInError                      MAKE_MVKERROR(kulAvcioCodecFacility, 0x4014); // AVCIO Codec Error: A synchro in error have been passed to the GetSurface or PutSurface.
const mvkstatus kMvkAvcioCodecLastErrorAddSurfaceToCodecBufferListFailed   MAKE_MVKERROR(kulAvcioCodecFacility, 0x4015); // AVCIO Codec Error: Failled to add the surface to the Codec buffer list.
const mvkstatus kMvkAvcioCodecLastErrorAddSurfaceToDmaBufferListFailed     MAKE_MVKERROR(kulAvcioCodecFacility, 0x4016); // AVCIO Codec Error: Failled to add the surface to the DMA buffer list.
//AssignSurface
const mvkstatus kMvkAvcioCodecLastErrorIOMemoryAllocationFailed            MAKE_MVKERROR(kulAvcioCodecFacility, 0x4017); // AVCIO Codec Error: IO memory allocation failed.
const mvkstatus kMvkAvcioCodecLastErrorIOMemoryBufferTooBig                MAKE_MVKERROR(kulAvcioCodecFacility, 0x4018); // AVCIO Codec Error: IO memory allocation size is too big.
const mvkstatus kMvkAvcioCodecLastErrorCommandNotValidInEncodeMode         MAKE_MVKERROR(kulAvcioCodecFacility, 0x4019); // AVCIO Codec Error: Command not valid in Encode mode.
const mvkstatus kMvkAvcioCodecLastErrorAddCommandToCodecSurfaceListFailed  MAKE_MVKERROR(kulAvcioCodecFacility, 0x401a); // AVCIO Codec Error: Failed to add a command to the Codec buffer list.
//Stop
const mvkstatus kMvkAvcioCodecLastErrorA2StopCommandFailed                 MAKE_MVKERROR(kulAvcioCodecFacility, 0x401b); // AVCIO Codec Error: Codec Stop command failed.
const mvkstatus kMvkAvcioCodecLastErrorA2RecoveryInStopFailed              MAKE_MVKERROR(kulAvcioCodecFacility, 0x401c); // AVCIO Codec Error: Codec recovery in Stop failed.
//Pause & Resume
const mvkstatus kMvkAvcioCodecLastErrorA2PauseCommandFailed                MAKE_MVKERROR(kulAvcioCodecFacility, 0x401d); // AVCIO Codec Error: Codec Pause command failed.
const mvkstatus kMvkAvcioCodecLastErrorA2ResumeCommandFailed               MAKE_MVKERROR(kulAvcioCodecFacility, 0x401e); // AVCIO Codec Error: Codec Resume command failed.
//UpdateSurface & FreeSurface
const mvkstatus kMvkAvcioCodecLastErrorCommandNotValidInDecodeMode         MAKE_MVKERROR(kulAvcioCodecFacility, 0x4020); // AVCIO Codec Error: An invalid command in Decode mode have been received.
const mvkstatus kMvkAvcioCodecLastErrorCouldNotFindSurfaceToUpdate         MAKE_MVKERROR(kulAvcioCodecFacility, 0x4021); // AVCIO Codec Error: Could not find surface to update.
const mvkstatus kMvkAvcioCodecLastErrorFailedToFreeSurface                 MAKE_MVKERROR(kulAvcioCodecFacility, 0x4022); // AVCIO Codec Error: Failed to free Surface.
//DPC processing
const mvkstatus kMvkAvcioCodecLastErrorA2StartCommandFailed                MAKE_MVKERROR(kulAvcioCodecFacility, 0x4023); // AVCIO Codec Error: Codec Decode Start command failed.
const mvkstatus kMvkAvcioCodecLastErrorA2StepCommandFailed                 MAKE_MVKERROR(kulAvcioCodecFacility, 0x4024); // AVCIO Codec Error: Codec Step command failed.
const mvkstatus kMvkAvcioCodecLastErrorProcessDmaSurfaceInError            MAKE_MVKERROR(kulAvcioCodecFacility, 0x4025); // AVCIO Codec Error: Process DMA surface returned an error.
const mvkstatus kMvkAvcioCodecLastErrorA2DidNotStartEncoding               MAKE_MVKERROR(kulAvcioCodecFacility, 0x4026); // AVCIO Codec Error: Codec did not start Encoding.
const mvkstatus kMvkAvcioCodecLastErrorA2DidNotStartDecoding               MAKE_MVKERROR(kulAvcioCodecFacility, 0x4027); // AVCIO Codec Error: Codec did not start Decoding.
const mvkstatus kMvkAvcioCodecLastErrorA2StoppedWhileEncoding              MAKE_MVKERROR(kulAvcioCodecFacility, 0x4028); // AVCIO Codec Error: Codec Stopped while Encoding.
const mvkstatus kMvkAvcioCodecLastErrorA2StoppedWhileDecoding              MAKE_MVKERROR(kulAvcioCodecFacility, 0x4029); // AVCIO Codec Error: Codec Stopped while Decoding.
const mvkstatus kMvkAvcioCodecLastErrorSaveDataReadyFailed                 MAKE_MVKERROR(kulAvcioCodecFacility, 0x402a); // AVCIO Codec Error: Could not save encoded data.
const mvkstatus kMvkAvcioCodecLastErrorA2ReportsIlligalVideoSignal         MAKE_MVKERROR(kulAvcioCodecFacility, 0x402b); // AVCIO Codec Error: Codec reports an illigal video signal.
const mvkstatus kMvkAvcioCodecLastErrorA2ReportsVDSPTaskLost               MAKE_MVKERROR(kulAvcioCodecFacility, 0x402c); // AVCIO Codec Error: Codec encoding interrupt lost.
const mvkstatus kMvkAvcioCodecLastErrorA2ReportsVoutTaskLost               MAKE_MVKERROR(kulAvcioCodecFacility, 0x402d); // AVCIO Codec Error: Codec decoding interrupt lost.
const mvkstatus kMvkAvcioCodecLastErrorA2ReportsEncodeBufferOverrun        MAKE_MVKERROR(kulAvcioCodecFacility, 0x402e); // AVCIO Codec Error: Codec encoding circular buffer overrun.
const mvkstatus kMvkAvcioCodecLastErrorProcessDecodeBufferFailed           MAKE_MVKERROR(kulAvcioCodecFacility, 0x402f); // AVCIO Codec Error: Process Codec Decode buffer failed.
//WARNINGs
//GetSurface & PutSurface
const mvkstatus kMvkAvcioCodecWarningBufferListFull                        MAKE_MVKERROR(kulAvcioCodecFacility, 0x4100); // AVCIO Codec Warning: Buffer list is FULL.


//
// Topology driver errors
//

const unsigned int kuiTopologyFacility = 0xddd;

const mvkstatus kMvkStatusTopologyNotSupported                             MAKE_MVKERROR(kuiTopologyFacility, 0x8000);   // Topology driver error: unsupported
const mvkstatus kMvkStatusTopologyIncompatibleWithGenlockResolution        MAKE_MVKERROR(kuiTopologyFacility, 0x8001);   // Topology driver error: Invalid with current genlock resolution
const mvkstatus kMvkStatusTopologyConnectorInUse                           MAKE_MVKERROR(kuiTopologyFacility, 0x8002);   // Topology driver error: Connector specified already in use
const mvkstatus kMvkStatusTopologyObjectNotFoundInList                     MAKE_MVKERROR(kuiTopologyFacility, 0x8003);   // Topology driver error: The object identified is not found in list
const mvkstatus kMvkStatusTopologyInternalListProcessingError              MAKE_MVKERROR(kuiTopologyFacility, 0x8004);   // Topology driver error: internal list management error
const mvkstatus kMvkStatusTopologyUserProcessManagement                    MAKE_MVKERROR(kuiTopologyFacility, 0x8005);   // Topology driver error: user process management error
const mvkstatus kMvkStatusTopologyInvalidTopology                          MAKE_MVKERROR(kuiTopologyFacility, 0x8006);   // Topology driver error: invalid topology
const mvkstatus kMvkStatusTopologyInUse                                    MAKE_MVKERROR(kuiTopologyFacility, 0x8007);   // Topology driver error: Topology specified already in use by another application
const mvkstatus kMvkStatusTopologyWatchdogInUse                            MAKE_MVKERROR(kuiTopologyFacility, 0x8008);   // Topology driver error: Watchdog specified already in use by another application
const mvkstatus kMvkStatusTopologyWriteAccessFailed                        MAKE_MVKERROR(kuiTopologyFacility, 0x8009);   // Topology driver error: Write access on the flash failed
const mvkstatus kMvkStatusTopologyEraseAccessFailed                        MAKE_MVKERROR(kuiTopologyFacility, 0x800A);   // Topology driver error: Erase access on the flash failed
const mvkstatus kMvkStatusTopologyAddImageToFlashInProcess                 MAKE_MVKERROR(kuiTopologyFacility, 0x800B);   // Topology driver error: Add Image to Flash already in process
const mvkstatus kMvkStatusTopologyMaxWatchdogsReached                      MAKE_MVKERROR(kuiTopologyFacility, 0x800C);   // Topology driver error: Maximum number of Watchdogs reached for the card
const mvkstatus kMvkStatusTopologyMaxResourceReached                       MAKE_MVKERROR(kuiTopologyFacility, 0x800D);   // Topology driver error: Maximum number of resources in usage reached for the card
const mvkstatus kMvkStatusTopologyNoOnBoardMemory                          MAKE_MVKERROR(kuiTopologyFacility, 0x800E);   // Topology driver error: No on board memory
const mvkstatus kMvkStatusTopologyGenlockInUse                             MAKE_MVKERROR(kuiTopologyFacility, 0x800F);   // Topology driver error: The genlock clock is being used by one of the topologies.
const mvkstatus kMvkStatusTopologyIncompatibleAlphaConnector               MAKE_MVKERROR(kuiTopologyFacility, 0x8010);   // Topology driver error: Video and Alpha connector incompatible.

#endif // MVKERNELERRORS_H

