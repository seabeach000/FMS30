/* ----------------------------------------------------------------------------
 * File: config_avc_def.h
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

#if !defined (__AVC_CONFIG_DEF_API_INCLUDED__)
#define __AVC_CONFIG_DEF_API_INCLUDED__


#define AVC_PAGES_BASIC               0x00000001  /**< display the basic settings page */
#define AVC_PAGES_ADVANCED            0x00000002  /**< display the advanced settings page */
#define AVC_PAGES_MISC                0x00000004  /**< display the miscellaneous page */
#define AVC_PAGES_ALL                 0x00000007  /**< display all of the above pages */

#define AVC_PAGES_LOADSAVE            0x00000010  /**< display the load/save buttons */
#define AVC_PAGES_NOINITCHECK         0x00000020  /**< do not check the validity of the setting at function start */
#define AVC_PAGES_REDWARNINGS         0x00000040  /**< display any validation warnings & errors */

#define AVC_PAGES_BANNER_OFF          0x00001000  /**< do not display codec banner */
#define AVC_PAGES_DISABLE_PRESET      0x00002000  /**< disable preset list (used e.g. in Encoder Application) */
#define AVC_PAGES_DISABLE_FRAMESIZE   0x00004000  /**< disable framesize list (used e.g. in Encoder Application) */
#define AVC_PAGES_DISABLE_FRAMERATE   0x00008000  /**< disable framerate list (used e.g. in Encoder Application) */
#define AVC_PAGES_DISABLE_PIXELASPECT 0x00010000  /**< disable pixel aspect ratio */
#define AVC_PAGES_DISABLE_PROFILE     0x00020000  /**< disable profile changes */
#define AVC_PAGES_DISABLE_LEVEL       0x00040000  /**< disable level changes */
#define AVC_PAGES_DISABLE_NUMVIEWS    0x00080000  /**< disable number of views/layers changes */
#define AVC_PAGES_DISABLE_NUMLAYERS   0x00080000  /**< disable number of views/layers changes */

#define AVC_PAGES_QT_APPLICATION      0x10000000  /**< caller application is QT (not MFC) */
#define AVC_PAGES_USE_DLG_SET_STRUCT  0x20000000  /**< pass @ref avc_dialog_set via @ref opt_ptr parameter in @ref showAVCEncoderPages function */

#endif // __AVC_CONFIG_DEF_API_INCLUDED__
