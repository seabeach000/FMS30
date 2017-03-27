//////////////////////////////////////////////////////////////////////////////////
//
//  (c) Copyright Matrox Electronic Systems Ltd., 2001. All rights reserved. 
//
//  This software code is subject to the terms and conditions outlined 
//  in the non-disclosure agreement between Matrox and your company. 
//  By accessing this code or using it in any way, you indicate your 
//  acceptance of such terms and conditions.
//
//  All code and information is provided "as is" without warranty of any kind, 
//  either expressed or implied, including but not limited to the implied 
//  warranties of merchantability and/or fitness for a particular purpose.
//
//  Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make 
//  changes in specifications and code at any time and without notice. 
//  No responsibility is assumed by Matrox Electronic Systems Ltd. for 
//  its use; nor for any infringements of patents or other rights of 
//  third parties resulting from its use. No license is granted under 
//  any patents or patent rights of Matrox Electronic Systems Ltd.
//
//////////////////////////////////////////////////////////////////////////////////
// mvStatus.h
// Anthony Malizia

#ifndef _MVKSTATUS_H
#define _MVKSTATUS_H

#include "mvTypes.h"

typedef int32_t mvkresult;

typedef int32_t mvkstatus;
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

//
// Define the customer severity codes (4 bits including the customer bit) 
//
const char kchStatusCustomerSeveritySuccess           = 1;  // Sev = 0, C = 1 --> 1
const char kchStatusCustomerSeverityInformational     = 3;  // Sev = 1, C = 1 --> 3
const char kchStatusCustomerSeverityWarning           = 5;  // Sev = 2, C = 1 --> 5
const char kchStatusCustomerSeverityError             = 7;  // Sev = 3, C = 1 --> 7

//
// Generic test for success on any status value (non-negative numbers
// indicate success).
//

#define MVK_SUCCESS(Status) ((mvkstatus)(Status) >= 0)

//
// Generic test for information on any status value.
//

#define MVK_INFORMATION(Status) ((uint32_t)(Status) >> 30 == 1)

//
// Generic test for warning on any status value.
//

#define MVK_WARNING(Status) ((uint32_t)(Status) >> 30 == 2)

//
// Generic test for error on any status value.
//

#define MVK_ERROR(Status) ((uint32_t)(Status) >> 30 == 3)

//
// Generic custom mvkstatus declaration
//
#define MAKE_MVKSTATUSVALUE(SevC, Facility, Code) \
   ((mvkstatus) (((uint32_t)(SevC)<<29) | ((uint32_t)(Facility)<<16) | ((uint32_t)(Code))) )

#define MAKE_MVKERROR(Facility, Code) MAKE_MVKSTATUSVALUE(kchStatusCustomerSeverityError, Facility, Code)
#define MAKE_MVKWARNING(Facility, Code) MAKE_MVKSTATUSVALUE(kchStatusCustomerSeverityWarning, Facility, Code)
#define MAKE_MVKSUCCESS(Facility, Code) MAKE_MVKSTATUSVALUE(kchStatusCustomerSeveritySuccess, Facility, Code)

//
// The success status codes 0 - 63 are reserved for wait completion status.
// FacilityCodes 0x5 - 0xF have been allocated by various drivers.
//
const mvkstatus kMvkStatusSuccess				   = ((mvkstatus)0x00000000L);   // ntsubauth

//
// MessageId: STATUS_INVALID_DEVICE_REQUEST
//
// MessageText:
//
//  The specified request is not a valid operation for the target device.
//
const mvkstatus kMvkStatusInvalidDeviceRequest	 = ((mvkstatus)0xC0000010L);

//
// MessageId: STATUS_INVALID_PARAMETER
//
// MessageText:
//
//  An invalid parameter was passed to a service or function.
//
const mvkstatus kMvkStatusInvalidParameter		= ((mvkstatus)0xC000000DL);

//
// MessageId: STATUS_INVALID_PARAMETER_1
//
// MessageText:
//
//  An invalid parameter was passed to a service or function as the first argument.
//

const mvkstatus kMvkStatusInvalidParameter1     = ((mvkstatus)0xC00000EFL);

//
// MessageId: STATUS_INVALID_PARAMETER_2
//
// MessageText:
//
//  An invalid parameter was passed to a service or function as the second argument.
//
const mvkstatus kMvkStatusInvalidParameter2      = ((mvkstatus)0xC00000F0L);

//
// MessageId: STATUS_INVALID_PARAMETER_3
//
// MessageText:
//
//  An invalid parameter was passed to a service or function as the third argument.
//
const mvkstatus kMvkStatusInvalidParameter3      = ((mvkstatus)0xC00000F1L);

//
// MessageId: STATUS_INVALID_PARAMETER_4
//
// MessageText:
//
//  An invalid parameter was passed to a service or function as the fourth argument.
//
const mvkstatus kMvkStatusInvalidParameter4      = ((mvkstatus)0xC00000F2L);

//
// MessageId: STATUS_INVALID_PARAMETER_5
//
// MessageText:
//
//  An invalid parameter was passed to a service or function as the fifth argument.
//
const mvkstatus kMvkStatusInvalidParameter5      = ((mvkstatus)0xC00000F3L);

//
// MessageId: STATUS_UNSUCCESSFUL
//
// MessageText:
//
//  {Operation Failed}
//  The requested operation was unsuccessful.
//
const mvkstatus kMvkStatusUnsuccessful			   = ((mvkstatus)0xC0000001L);

//
// MessageId: STATUS_PENDING
//
// MessageText:
//
//  The operation that was requested is pending completion.
//
const mvkstatus kMvkStatusPending				   = ((mvkstatus)0x00000103L);    // winnt

//
// MessageId: STATUS_INVALID_DEVICE_STATE
//
// MessageText:
//
//  The device is not in a valid state to perform this request.
//
const mvkstatus kMvkStatusInvalidDeviceState		= ((mvkstatus)0xC0000184L);

//
// MessageId: MVK_STATUS_NOT_SUPPORTED
//
// MessageText:
//
//  The request is not supported.
//
const mvkstatus kMvkStatusNotSupported          = ((mvkstatus)0xC00000BBL);
   
//
// MessageId: STATUS_NO_MEMORY
//
// MessageText:
//
//  {Not Enough Quota}

const mvkstatus kMvkStatusNoMemory				   = ((mvkstatus)0xC0000017L);

//
// MessageId: STATUS_NOT_IMPLEMENTED
//
// MessageText:
//
//  {Not Implemented}
//  The requested operation is not implemented.
//
const mvkstatus kMvkStatusNotImplemented        = ((mvkstatus)0xC0000002L);


//
// MessageId: STATUS_WORKING_SET_LIMIT_RANGE
//
// MessageText:
//
//  {Working Set Range Error}
//  An attempt was made to set the working set minimum or maximum to values which are outside of the allowable range.
//
const mvkstatus kMvkStatusWorkingSetLimitRange  = ((mvkstatus)0xC0000002L);

//
// MessageId: STATUS_INVALID_BUFFER_SIZE
//
// MessageText:
//
//  The size of the buffer is invalid for the specified operation.
//
const mvkstatus kMvkStatusInvalidBufferSize     = ((mvkstatus)0xC0000206L);

//
// MessageId: STATUS_IO_TIMEOUT
//
// MessageText:
//
//  The operation timed out.
//
const mvkstatus kMvkStatusIOTimeOut             = ((mvkstatus)0xC00000B5L);

#endif // _MVKSTATUS_H


