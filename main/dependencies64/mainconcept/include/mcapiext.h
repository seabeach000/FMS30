/** 
\file	mcapiext.h
\brief	Global API extension

@verbatim
* File: mcapiext.h
 *
 * Desc: global API extension
 *
 * Copyright (c) 2015 MainConcept GmbH or its affiliates.  All rights reserved.
 *
 * MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.  
 * This software is protected by copyright law and international treaties.  Unauthorized 
 * reproduction or distribution of any portion is prohibited by law.
 *
 @endverbatim
 **/

#if !defined (__MC_API_EXTENSION_INCLUDED__)
#define __MC_API_EXTENSION_INCLUDED__

#include "mctypes.h"

/**
 * @name API Function Prototype
 * Defines a prototype for function return.
 * @{
 */
typedef int32_t (MC_EXPORT_API *APIEXTFUNC) ();
/** @} */

/**
 * @name API Function Identifiers
 * These defines are used to access the different API functions.
 * @{
 */
 
/**
 * @brief GetModuleInfo retrieves useful information about the module.
 * @code 
 * int32_t GetModuleInfo  (uint32_t infoID, void *info);
 * @encode
 * @param[in]  infoID   the info identifier.
 * @param[out] info     pointer to the module information.
 * @return              returns 0 if succeeded.
 *
 * @code
 * int32_t type;
 * char    name[128];
 * char    version[128];
 *
 * GetModuleInfo(MCAPI_MODULE_TYPE, &type);
 * GetModuleInfo(MCAPI_MODULE_NAME, &name);
 * GetModuleInfo(MCAPI_MODULE_VERSION, &version);
 * @endcode
 */
#define MCAPI_GetModuleInfo       0x00000001

/**
 * @brief GetParamInfo retrieves useful information about a parameter.
 * @code 
 * int32_t GetParamInfo  (void *instance, uint32_t paramID, uint32_t infoID, void *info);
 * @encode
 * @param[in]  instance the encoder instance. Needs to be created using VideoNew before.
 * @param[in]  paramID  the parameter identifier (e.g. ENC_MP2V_PARAM_FRAME_RATE).
 * @param[in]  infoID   the info identifier.
 * @param[out] info     pointer to the parameter information.
 * @return              returns 0 if succeeded.
 *
 * @code
 * char name[128];
 * char type[128];
 * int32_t dim;
 *
 * GetParamInfo(instance, ENC_MP2V_PARAM_FRAME_RATE, PARAM_INFO_NAME, &name);
 * GetParamInfo(instance, ENC_MP2V_PARAM_FRAME_RATE, PARAM_INFO_TYPE, &type);
 * GetParamInfo(instance, ENC_MP2V_PARAM_FRAME_RATE, PARAM_INFO_DIM,  &dim);
 * @endcode
 */
#define MCAPI_GetParamInfo       0x00001001

/**
 * @brief GetParam retrieves the committed value of a parameter.
 * @code
 * int32_t GetParam      (void *instance, uint32_t paramID, void *paramData);
 * @endcode
 * @param[in]  instance  the encoder instance. Needs to be created using VideoNew before.
 * @param[in]  paramID   the parameter identifier (e.g. ENC_MP2V_PARAM_FRAME_RATE).
 * @param[out] paramData pointer to the parameter's value or data.
 * @return               returns 0 if succeeded.
 *
 * @code
 * double frame_rate;
 *
 * GetParam(instance, ENC_MP2V_PARAM_FRAME_RATE, &frame_rate);
 * @endcode
 */
#define MCAPI_GetParam           0x00001002

/**
 * @brief SetParam assigns a new value to a parameter.
 * @code
 * int32_t SetParam      (void *instance, uint32_t paramID, void *paramData);
 * @endcode
 * @param[in] instance  the encoder instance. Needs to be created using VideoNew before.
 * @param[in] paramID   parameter identifier (e.g. ENC_MP2V_PARAM_FRAME_RATE).
 * @param[in] paramData pointer to the new value or data.
 * @return              returns 0 if succeeded.
 *
 * @code
 * double frame_rate;
 *
 * SetParam(instance, ENC_MP2V_PARAM_FRAME_RATE, &frame_rate);
 * @endcode
 */
#define MCAPI_SetParam           0x00001003

/**
 * @brief SetParamSet sets profile dependent video defaults.
 * @code
 * int32_t SetParamSet   (void *instance, uint32_t preset, uint32_t mode);
 * @endcode
 * @param[in] instance    the encoder instance. Needs to be created using VideoNew before.
 * @param[in] preset      could be the preferred video type (e.g. MPEG_D10_50 or MCPROFILE_D10_50).
 * @param[in] mode        could be the preferred video standard (e.g. 0 = NTSC or 1 = PAL).
 * @return                returns 0 if succeeded.
 * @note SetParamSet directly commits all parameters, so there is no need of an extra CommitParamSet call.
 *
 * @code
 * SetParamSet(instance, MCPROFILE_D10_50, 1);
 * @endcode
 */
#define MCAPI_SetParamSet        0x00001004

/**
 * @brief CommitParamSet verifies and commits changed parameters, if they are valid.
 * @code
 * int32_t CommitParamSet(void *instance);
 * @endcode
 * @param[in] instance the encoder instance. Needs to be created using VideoNew before.
 * @return             returns 0 if succeeded.
 */
#define MCAPI_CommitParamSet     0x00001005

/**
 * @brief LoadParamSet loads parameters from some file.
 * @code
 * int32_t LoadParamSet  (void *param_set, const char *file_name);
 * @endcode
 * @param[in] param_set the parameter set that is to be filled (defined in the component API).
 * @param[in] filename  the name of the config file.
 * @return              returns MCAPI_NOERROR if succeeded.
 * @note LoadParamSet can load parameters from either config file or raw MPEG data.
 */
#define MCAPI_LoadParamSet       0x00002001

/**
 * @brief SaveParamSet stores parameters in some file.
 * @code
 * int32_t SaveParamSet  (void *param_set, const char *file_name);
 * @endcode
 * @param[in] param_set the parameter set that is to be stored (defined in the component API).
 * @param[in] filename  the name of the config file.
 * @return              returns MCAPI_NOERROR if succeeded.
 */
#define MCAPI_SaveParamSet       0x00002002

/**
 * @brief ShowPages displays settings dialog
 * @code
 * int32_t ShowPages  (void *param_set, uint32_t options, void *opt_ptr);
 * @endcode
 * @param[in] param_set the parameter set that is to be edited.
 * @param[in] options   option flags (defined in the component API).
 * @param[in] opt_ptr   extended info pointer (e.g. to specify MFC application pointer)
 * @return returns one of following values
 *    \li \ref MCAPI_ERROR    - general error, missing necessary libraries.
 *    \li \ref MCAPI_ACCEPTED - settings change accepted (e.g. after OK button click)
 *    \li \ref MCAPI_REJECTED - settings change rejected (e.g. after CANCEL button click)
 */
#define MCAPI_ShowPages          0x00002008

/**
 * @brief GetParamSet stores parameters in some buffer.
 * @code
 * int32_t GetParamSet  (void *param_set, char *buffer);
 * @endcode
 * @param[in] param_set the parameter set that is to be stored (defined in the component API).
 * @param[in] buffer    the buffer to store config.
 * @return              returns MCAPI_NOERROR if succeeded.
 */
#define MCAPI_GetParamSet       0x00002010


#define MCAPI_GetLicensedFeatures 0x00002011




/** @} */


/**
 * @name API Function Types
 * These defines types for each function identitifier.
 * @{
 */
typedef int32_t (MC_EXPORT_API *APIEXTFUNC_GETMODULEINFO) (uint32_t infoID, void *infoData);
typedef int32_t (MC_EXPORT_API *APIEXTFUNC_GETPARAMINFO)  (void *instance, uint32_t paramID, uint32_t infoID, void *infoData);
typedef int32_t (MC_EXPORT_API *APIEXTFUNC_GETPARAM)      (void *instance, uint32_t paramID, void *paramData);
typedef int32_t (MC_EXPORT_API *APIEXTFUNC_SETPARAM)      (void *instance, uint32_t paramID, void *paramData);
typedef int32_t (MC_EXPORT_API *APIEXTFUNC_SETPARAMSET)   (void *instance, uint32_t preset, uint32_t mode);
typedef int32_t (MC_EXPORT_API *APIEXTFUNC_COMMITPARAMSET)(void *instance);
typedef int32_t (MC_EXPORT_API *APIEXTFUNC_LOADPARAMSET)  (void *param_set, const char *file_name);
typedef int32_t (MC_EXPORT_API *APIEXTFUNC_SAVEPARAMSET)  (void *param_set, const char *file_name);
typedef int32_t (MC_EXPORT_API *APIEXTFUNC_GETPARAMSET)   (void *param_set, const char *buffer, int32_t *actual_length);
typedef int32_t (MC_EXPORT_API *APIEXTFUNC_SHOWPAGES)     (void *param_set, uint32_t options, void *opt_ptr);
/** @} */


/**
 * @name Module Info Identifiers
 * These defines are used to access specific module information.
 * @{
 */
#define MCAPI_MODULE_NAME           0x00000001 /**< char *module_name */
#define MCAPI_MODULE_TYPE           0x00000002 /**< uint32_t module_type */
#define MCAPI_MODULE_BUILD_ID       0x00000003 /**< uint32_t module_build_id */
#define MCAPI_MODULE_VERSION        0x00000004 /**< char *module_version */
#define MCAPI_MODULE_ARCHITECTURE   0x00000005 /**< char *module_architecture */
/** @} */

/**
 * @name Module Types
 * These defines describe possible module types.
 * @{
 */
#define MCAPI_MODULE_TYPE_UNKNOWN          0x00000000
#define MCAPI_MODULE_TYPE_DECODER_VIDEO    0x00000001
#define MCAPI_MODULE_TYPE_DECODER_AUDIO    0x00000002
#define MCAPI_MODULE_TYPE_DEMULTIPLEXER    0x00000003
#define MCAPI_MODULE_TYPE_ENCODER_VIDEO    0x00000004
#define MCAPI_MODULE_TYPE_ENCODER_AUDIO    0x00000005
#define MCAPI_MODULE_TYPE_MULTIPLEXER      0x00000006
/** @} */

/**
 * @name Module Versions
 * These defines describe possible module versions
 * @{
 */
#define MCAPI_MODULE_VERSION_UNKNOWN 0x00000000
#define MCAPI_MODULE_VERSION_FULL    0x00000001
#define MCAPI_MODULE_VERSION_DEMO    0x00000002
/** @} */

/**
 * @name Codec-independent error codes
 * @{
 */
#define MCAPI_NOERROR             0    /**< success */
#define MCAPI_ERROR               1    /**< general error, might be caused by missing libraries */
// add more specific error codes here
#define MCAPI_ACCEPTED         1000    /**< settings change accepted (e.g. after OK button click) */
#define MCAPI_REJECTED         1001    /**< settings change rejected (e.g. after CANCEL button click) */
// add more specific error codes here

/////////////////////////////////////////////////////////////////

// every codec must expose its own XYZGetAPIExt interface,
// e.g. mpegOutVideoGetAPIExt, h264OutVideoGetAPIExt, etc.
// a global function pointer would inhibit static libraries

//#ifdef __cplusplus
//extern "C" {
//#endif
/**
 * @brief XYZGetAPIExt returns appropriate API function pointer.
 * @param[in] func   one of the above defined API function identifiers.
 * @return           returns API function pointer or NULL if undefined.
 */
//void * XYZGetAPIExt(uint32_t func);
//
//#ifdef __cplusplus
//}
//#endif
/** @} */


/////////////////////////////////////////////////////////////////


#endif // #if !defined (__MC_API_EXTENSION_INCLUDED__)

