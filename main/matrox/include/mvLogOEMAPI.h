// $Archive: /VP/INTEGRATION/LIBS/MVIDEFINITIONS/inc/mvLogOEMAPI.h $
//==========================================================================;
//
// (c) Copyright Matrox Electronic Systems Ltd., 2003. All rights reserved.
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
//==========================================================================;
//                    mvLogOEMAPI.H
//==========================================================================;
// @module  Matrox Video Integration
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#ifndef MVLOGOEMAPI_H_H
#define MVLOGOEMAPI_H_H

#define MV_LOG_COMMIT(a) ;
#define MV_LOG_GET_ARRAY_OF_STORAGE(a,b,c,d,e,f) void* should_not_touch_this = 0; *((void**)(a)) = should_not_touch_this;
#define MV_LOG_TIMING(a,b,c,d,e) ;
#define MV_LOG_CRC(a,b,c,d,e,f) ;
#define MV_LOG_STRING(...) ;
#define MV_LOG_STRING_FORMAT(...) ;
#define MV_LOG_GET_ARRAY_OF_STORAGE(a,b,c,d,e,f) void* should_not_touch_this = 0; *((void**)(a)) = should_not_touch_this;
#define MV_LOG_VIRTUAL_MEMORY_AVAILABLE(...) ;
#define MV_LOG_IS_LOGGING_NEEDED(...) false
#define MV_LOG_IN_OUT_FUNCTION(...) ;
#define MV_LOG_IN_OUT_FUNCTION_WITH_THIS(...) ;

#endif //MVLOGOEMAPI_H_H
