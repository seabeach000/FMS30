/* ----------------------------------------------------------------------------
 * File: enc_pcm.h
 *
 * Desc: PCM Encoder API
 *
 * Copyright (c) 2014 MainConcept GmbH or its affiliates.  All rights reserved.
 *
 * MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.
 * This software is protected by copyright law and international treaties.  Unauthorized
 * reproduction or distribution of any portion is prohibited by law.
 * ----------------------------------------------------------------------------
 */

/*! @file /enc_pcm.h
 */

#if !defined (__ENC_PCM_API_INCLUDED__)
#define __ENC_PCM_API_INCLUDED__

#include "bufstrm.h"
#include "mcdefs.h"
#include "mcprofile.h"
#include "mcapiext.h"

typedef struct pcm_a_encoder pcmaenc_tt;  //!< PCM audio encoder object

//! @name Option Flags
//! @brief Use these with the option parameter in the \ref  pcmOutAudioNew function
//! @{
#define LPCM_SAMPLES      0x00000001  /*!< @brief Depreciated, use OPT_LPCM_SAMPLES instead */
#define OPT_LPCM_SAMPLES  0x00000001  /*!< @brief Use if the audio samples being input to the encoder are already 
                                      big endian (LPCM) samples instead of normal little endian PCM samples. */
//!@}


#ifdef __GNUC__
#pragma pack(push,1)
#else
#pragma pack(push)
#pragma pack(1)
#endif

//! @brief The PCM audio encoder settings structure
struct pcm_a_settings 
{
    int32_t pcm_channels;               //!< @brief Depreciated, use the num_channels field instead
    int32_t audio_layer;                //!< @brief Specifies the type of PCM audio to output
                                        /*!< @details Set this to one of the following audio type defines from mcdefs.h:
                                            DVD_LPCM_AUDIO  - for MP2 Program Stream container
                                            AES3_302M_AUDIO - for MP2 Transport Stream container
                                            AES3_331M_AUDIO - for MXF container
                                            AES3_382M_AUDIO - for MXF container
                                            HDMV_LPCM_AUDIO - for MP2 BluRay and AVCHD Transport Stream container
                                            STD_LPCM_AUDIO  - for MP4 and MP2 containers
                                        */
    int32_t pcm_emphasis;               //!< @brief Specifies the state of the DVD LPCM 'audio_emphasis_flag'
                                        /*!< @details 0 - off, 1 - on (48 kHz audio only), DVD only */
    int32_t pcm_mute_flag;              //!< @brief Specifies the state of the DVD LPCM 'audio_mute_flag'
                                        /*!< @details 0 - off, 1 - on, DVD only */
    int32_t pcm_quantization;           //!< @brief Specifies the bit depth of the input audio
                                        /*!< @details One of the PCM_??BITS defines in mcdefs.h */
    int32_t pcm_dynamic_range_control;  //!< @brief Specifies the state of the DVD LPCM 'dynamic_range_control'
                                        /*!< @details 8 bit value, 0x80 (default) = no range control (gain)
                                            X = bits 7..5, Y = bits 4..0 where
                                            gain (dB) = 24.082 - 6.0206*X - 0.2007*Y, DVD only
                                        */

    int64_t pts_offset;                 //!< @brief Specifies the timestamp of the start of the stream
    int32_t pts_units;                  //!< @brief Specifies the units of the pts_offset field
                                        /*!< @details 10000000 = 10MHz, 27000000 = 27Mhz, etc
                                        a value <= 0 will be treated as 27MHz */

    uint16_t num_channels;              //!< @brief Use to specify the number of input channels.
                                        /*!< @details If set to 0, the pcm_channels field is used instead */
    
    int16_t reserved0;                  //!< Reserved for future use
    int32_t reserved[1014];             //!< Reserved for future use
};
#pragma pack(pop)


/////////////////////////////////////////////////////////////////////////////
// audio routines in enc_pcm.dll
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

//! Call to fill a \ref pcm_a_settings-structure with defaults values
//! based on a profile ID
//! 
//! @param[in,out]  set         pointer to a \ref pcm_a_settings structure
//! @param[in]      profileID   one of the MCPROFILE_* or MPEG_* constants
//!
//! @return pointer to a profile string or NULL

char * MC_EXPORT_API pcmOutAudioDefaults(struct pcm_a_settings *set, int32_t profileID);


//! Call to create a pcm audio encoder object
//!
//! @param[in]  get_rc          pointer to a get resource function 
//! @param[in]  set             pointer to a filled \ref pcm_a_settings structure
//! @param[in]  options         one or more of the OPT_ defines above
//! @param[in]  frameRateCode   one of FRAMERATE defines in mcdefs.h, required for
//!                             AES3 audio types, not used for other PCM types
//! @param[in]  sampleRate      sample rate of the input audio, must be 48000 or 96000
//!
//! @return pointer to a \ref pcmaenc_tt object if successful, NULL if unsuccessful

pcmaenc_tt * MC_EXPORT_API pcmOutAudioNew(void                        *(MC_EXPORT_API *get_rc)(const char* name),
                                          const struct pcm_a_settings *set,
                                          int32_t                      options,
                                          int32_t                      frameRateCode,
                                          int32_t                      sampleRate);


//! Call to free a pcm audio encoder object
//!
//! @param[in]  instance        pointer to a pcm encoder object
//!
//! @return none

void MC_EXPORT_API pcmOutAudioFree(pcmaenc_tt *instance);


//! Call to initialize the pcm encoder for an encoding session, this 
//! function must be called before the PutBytes function is called
//!
//! @param[in]  instance        pointer to a pcm encoder object
//! @param[in]  audiobs         pointer to a bufstream_tt object for the compressed data
//!
//! @return 0 if successful, non-zero if not

int32_t MC_EXPORT_API pcmOutAudioInit(pcmaenc_tt *instance, bufstream_tt *audiobs);


//! Call to process some audio samples
//!
//! @param[in]  instance        pointer to a pcm encoder object
//! @param[in]  audioBuffer     pointer to a buffer of PCM audio samples
//! @param[in]  numAudioBytes   number of bytes of data in the audio buffer  
//!
//! @return 0 if successful, non-zero if not

int32_t MC_EXPORT_API pcmOutAudioPutBytes(pcmaenc_tt *instance, uint8_t *audioBuffer, uint32_t numAudioBytes);


//! Call to process some audio samples with a timestamp
//!
//! @param[in]  instance        pointer to a pcm encoder object
//! @param[in]  audioBuffer     pointer to a buffer of PCM audio samples
//! @param[in]  numAudioBytes   number of bytes of data in the audio buffer  
//! @param[in]  timestamp       the timestamp (PTS) of the first sample in the buffer
//! @param[in]  ts_units        the units of the timestamp field
//!                             10000000 = 10MHz, 27000000 = 27Mhz, etc
//!                             a value <= 0 will be treated as 27MHz
//!
//! @return 0 if successful, non-zero if not

int32_t MC_EXPORT_API pcmOutAudioPutBytesEx(pcmaenc_tt *instance, uint8_t *audioBuffer, uint32_t numAudioBytes, uint64_t timestamp, int32_t ts_units);


//! Call to finish encoding session, set abort non-zero if encoding is being
//! aborted.
//!
//! @param[in]  instance        pointer to a pcm encoder object
//! @param[in]  abort           set to 0 to finish any leftover audio and clean up,
//!                             else just clean up
//!
//! @return 0 if successful, non-zero if not

int32_t MC_EXPORT_API pcmOutAudioDone(pcmaenc_tt *instance, int32_t abort);


//! Call to get the setting errors/warnings in a pcm_a_settings structure
//! use the get_rc callback to provide an err_printf callback to get error
//! messages that can be localized
//!
//! @param[in]  get_rc          pointer to a get resource function 
//! @param[in]  set             pointer to a filled \ref pcm_a_settings structure
//! @param[in]  mpeg_type       one of the MCPROFILE_* or MPEG_* constants to check for format
//!                             compliance, use 0 for no format compliance checks
//! @param[in]  sample_rate     sampling rate to check
//! @param[in]  options         check options, one or more of the CHECK_* defines in mcdefs.h
//! @param[in]  app             reserved
//!
//! @return mpegOutErrNone if no errors found, one of the INV_* error codes if an error is found

int32_t MC_EXPORT_API pcmOutAudioChkSettings(void                        *(MC_EXPORT_API *get_rc)(const char* name),
                                             const struct pcm_a_settings *set,
                                             int32_t                      mpeg_type,
                                             int32_t                      sample_rate,
                                             uint32_t                     options,
                                             void                        *app);


//! Call to get extended API function
//!
//! @param[in]  func            function ID
//! 
//! @return function pointer or NULL

APIEXTFUNC MC_EXPORT_API pcmOutAudioGetAPIExt(uint32_t func);


#ifdef __cplusplus
}
#endif

//--------------------------------------------------------------------------

#endif // #if !defined (__ENC_PCM_API_INCLUDED__)

