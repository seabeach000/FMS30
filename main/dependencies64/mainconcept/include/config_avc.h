/* ----------------------------------------------------------------------------
 * File: config_avc.h
 *
 * Desc: AVC/H.264 Encoder Configuration API
 *
 * Copyright (c) 2015 MainConcept GmbH or its affiliates.  All rights reserved.
 *
 * MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.  
 * This software is protected by copyright law and international treaties.  Unauthorized 
 * reproduction or distribution of any portion is prohibited by law.
 * ----------------------------------------------------------------------------
 */

#if !defined (__AVC_CONFIG_API_INCLUDED__)
#define __AVC_CONFIG_API_INCLUDED__

#include "mcapiext.h"

#include "config_avc_def.h"

#include "enc_avc.h"

struct avc_param_set
{
  struct  h264_v_settings params;
  char    enc_lib_name[64];

  int32_t reserved[1024-64];
};

struct avc_dialog_set
{
    uint32_t options;
    void *parent_ptr; // HWND handle or pointer to QApplication
    char *title;
    char *banner_filename;

    int32_t reserved_int[400 - 1];
    void *reserved_ptr[112 - 3];
};

#ifdef __cplusplus
extern "C" {
#endif


APIEXTFUNC MC_EXPORT_API AVCConfigGetAPIExt(uint32_t func);

#ifdef __cplusplus
}
#endif

#endif // __AVC_CONFIG_API_INCLUDED__
