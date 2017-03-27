/**
 @file  enc_aac.h
 @brief AAC Encoder API

 @verbatim
 File: enc_aac.h

 Desc: AAC Encoder API

 Copyright (c) 2015 MainConcept GmbH or its affiliates.  All rights reserved.

 MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.  
 This software is protected by copyright law and international treaties.  Unauthorized 
 reproduction or distribution of any portion is prohibited by law.
 @endverbatim
 **/

#if !defined (__ENC_AAC_API_INCLUDED__)
#define __ENC_AAC_API_INCLUDED__

#include "bufstrm.h"
#include "mcdefs.h"
#include "mcprofile.h"
#include "mcapiext.h"

/////////////////////////////////////////////////////////////////////////////
// API structures
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief encoder instance type
 */
typedef struct aac_a_encoder aacaenc_tt;

#ifdef __GNUC__
#pragma pack(push,1)
#else
#pragma pack(push)
#pragma pack(1)
#endif

/**
 * @brief These parameters are used to configure the encoder.
 */
struct aac_a_settings
{
	uint32_t input_channels;			///<@brief Number of audio channels at the input
	uint32_t mpeg_version;				///<@brief MPEG version
	uint32_t aac_object_type;			///<@brief AAC audio object type
	uint32_t audio_bitrate_index;		///<@brief Audio bitrate
	uint32_t header_type;				///<@brief Type of the header
	uint32_t hf_cutoff;					///<@brief Cut-off frequency value in Hertz
	uint32_t vbr;						/**<@brief Specifies if vbr (variable bitrate) mode is used instead of cbr (constant bitrate) mode, and if
										 * used, the target quality level for variable bitrate */
	uint32_t he;						///<@brief Specifies if High Efficiency AAC encoding is used
	uint32_t bits_per_sample;			///<@brief Number of bits per one PCM sample
	uint32_t protect_adts_stream;		///<@brief Specifies if audio stream contains CRC protection
	uint32_t tns;						///<@brief Specifies if Temporal Noise Shaping (TNS) algorithm will be used
    int64_t pts_offset;					///<@brief Time stamp offset (starting value)
    int32_t pts_units;					///<@brief Units for the time stamp offset
    uint32_t ch_mode;                   ///<@brief Channel mode (one of the AAC_CH_MODE_* values)
    uint32_t LFE_filtering;              ///<@brief Enable/Disable LFE filtering flag (LFE filtering is enabled by default)
    int64_t  restart_interval;          ///<@brief Time stamp restart interval (measured in pts)

	uint32_t reserved[46];
};


/**
 * @brief This structure is used to get the audio specific configuration (ASC) from the encoder via @ref aacOutGetAudioSpecificConfig function.
 */
typedef struct aac_ascbuf_s
{
    int32_t nbits;           ///<@brief The length of the ASC in bits
    uint8_t buffer[128];     ///<@brief An array containing the ASC
} aac_ascbuf;

#pragma pack(pop)

/////////////////////////////////////////////////////////////////////////////
// API functions
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Call this function to fill an @ref aac_a_settings structure with
 * default values based on a profile type.
 *
 * @param[in] set a pointer to a @ref aac_a_settings structure to be initialized
 * @param[in] profile one of the preset values for profile. This field specifies
 * which default values will be used. It should be one of the following defines:
 *
 * <table>
 * <tr><th>value</th><th>meaning</th></tr>
 * <tr><td>@ref MCPROFILE_DEFAULT</td><td>default settings</td></tr>
 * <tr><td>@ref MCPROFILE_PSP</td><td>settings compatible with PlayStation Portable by Sony</td></tr>
 * <tr><td>@ref MCPROFILE_IPOD</td><td>settings compatible with iPod by Apple</td></tr>
 * <tr><td>@ref MCPROFILE_3GPP</td><td>settings compatible with 3GPP specification</td></tr>
 * <tr><td>@ref MCPROFILE_3GPP2</td><td>settings compatible with 3GPP2 specification</td></tr>
 * <tr><td>@ref MCPROFILE_ISMA</td><td>settings compatible with ISMA specification</td></tr>
 * <tr><td>@ref MCPROFILE_FLASH_LOWRES</td><td>settings for Adobe Flash (Low Resolution WebContent)</td></tr>
 * <tr><td>@ref MCPROFILE_FLASH_HIGHRES</td><td>settings for Adobe Flash (High Resolution Web Content) </td></tr>
 * <tr><td>@ref MCPROFILE_SILVERLIGHT</td><td>Microsoft Silverlight compatible settings</td></tr>
 * <tr><td>@ref MCPROFILE_IIS_SMOOTHSTREAMING</td><td>fMP4 IIS Smooth Streaming compatible settings </td></tr>
 * <tr><td>@ref MCPROFILE_DPS</td><td>DivX Plus Streaming compatible settings </td></tr>
 * <tr><td>@ref MCPROFILE_DPS_A_51C</td><td>DivX Plus Streaming 5.1 compatible settings</td></tr>
 * </table>
 *
 * @param[out] set modified aac_a_settings structure
 * @return short description if the ID is valid
 * @return NULL if not
 */
char* MC_EXPORT_API aacOutAudioDefaults(struct aac_a_settings *set, int32_t profile);


/** @brief Call this function to create an @ref aacaenc_tt audio encoding object
 * which is used in other AAC audio encoding calls.
 *
 * @param[in] get_rc pointer to a get resource function
 * @param[in] set pointer to a filled in @ref aac_a_settings structure
 * @param[in] options reserved, set to 0
 * @param[in] CPU set to 0xFFFFFFFF for autodetect (reserved for CPU-flags)
 * @param[in] sampleRate sample rate of the input audio, must be:
 *			   8, 11.025, 12, 16, 22.05, 24, 32, 44.1, 48, 64, 88.2, 96 kHz
 * @return pointer to a @ref aacaenc_tt object if succesful
 * @return NULL if unsuccesful
 */
aacaenc_tt* MC_EXPORT_API aacOutAudioNew( void *(MC_EXPORT_API *get_rc)(const char* name),const struct aac_a_settings *set,int32_t options,int32_t CPU,int32_t sampleRate);


/** @brief Call this function to free an @ref aacaenc_tt object
 *
 * @param[in] instance a pointer to a @ref aacaenc_tt object
 */
void MC_EXPORT_API aacOutAudioFree(aacaenc_tt* instance);


/** @brief Call this function to initialize the AAC encoder for an encoding session.
 *
 * An existing bufstream object must be passed to this function, the AAC encoder
 * will output the encoded data to the bufstream object.
 *
 * @param[in] instance a pointer to a @ref aacaenc_tt object
 * @param[in] audiobs a pointer to a @ref bufstream_tt object for the compressed
 * data output stream
 * @return @ref aacOutErrNone if successful
 * @return @ref aacOutError if not
 */
int32_t MC_EXPORT_API aacOutAudioInit(aacaenc_tt *instance, bufstream_tt *audiobs);


/** @brief Call this function to encode a buffer of audio, which must contain 8-bit,
 * 16-bit and 24-bit PCM audio data.
 *
 * The input_channels field of the @ref aac_a_settings structure passed to the @ref
 * aacOutAudioNew function must match the type of audio data in the buffer. In addition,
 * the sampling rate passed to the @ref aacOutAudioNew function must match the sampling
 * rate of the audio data in the buffer.
 *
 * @param[in] instance a pointer to a @ref aacaenc_tt object
 * @param[in] audioBuffer a pointer to an audio buffer containing 8-bit, 16-bit and
 * 24-bit PCM audio data
 * @param[in] numAudioBytes the number of bytes in the audio buffer
 * @return @ref aacOutErrNone if successful
 * @return @ref aacOutError if not
 */
int32_t MC_EXPORT_API aacOutAudioPutBytes(aacaenc_tt *instance, uint8_t *audioBuffer, uint32_t numAudioBytes);


/** @brief Call to finish an AAC audio encoding session, set the abort flag
 * to a non-zero if audio encoding is being aborted.
 *
 * @param[in] instance a pointer to a @ref aacaenc_tt object
 * @param[in] abort flag, set to a non-zero value to abort encoding
 * @return @ref aacOutErrNone if successful
 * @return @ref aacOutError if not
 */
int32_t MC_EXPORT_API aacOutAudioDone(aacaenc_tt *instance, int32_t abort);


/// add this flag to options arg to signal that settings can be corrected
#define AACENC_CORRECT_SETTINGS		0x0001000

/** @brief Call this function to check whether the audio settings are valid.
 *
 * If the get_rc parameter is non-NULL, any error messages are sent to the err_printf function.
 * If the options parameter does contain @ref AACENC_CORRECT_SETTINGS, the function corrects
 * user settings (despite it is passed with const qualifier for compatibility reason) and
 * does not fail unless invalid sample rate or channel configuration are specified. If the
 * options parameter does not contain @ref CHECK_ALL, the function returns when the first non
 * compliant value is found (the remainder of the settings are not checked). If the options
 * parameter does contain @ref CHECK_ALL, all the checks are performed, an error message is
 * sent to the err_printf callback for every error found and the error code of the first error
 * found is returned. To fully check the audio settings, the mpeg type (supports values are
 * @ref MPEG_MPEG1 .. @ref MPEG_LAST_MPEG_TYPE) and audio frequency is needed. If the sample_rate
 * parameter is not a valid MPEG audio frequency, this call will fail.
 *
 * @param[in] get_rc a pointer to a get_rc function
 * @param[in] set a pointer to a filled in aac_a_settings structure
 * @param[in] mpeg_type one of the MPEG_* defines, used for the VCD/SVCD/DVD/DVB/MicroMV/DVHS checks (see @ref mcdefs.h)
 * @param[in] sample_rate the audio frequency, either 8000, 11025, 12000, 16000, 22050, 24000,
 * 32000, 44100, 48000, 64000, 88200 or 96000
 * @param[in] options @ref CHECK_MPEG_ONLY and/or @ref CHECK_ALL
 * @param[in] app reserved, set to NULL
 * @return @ref aacOutErrNone if settings are valid
 * @return one of the INV_* error codes if an error is found (see @ref mcdefs.h)
 */
int32_t MC_EXPORT_API aacOutAudioChkSettings(void *(MC_EXPORT_API *get_rc)(const char* name), const struct aac_a_settings *set, int32_t mpeg_type, int32_t sample_rate, uint32_t options, void *app);


/** @brief Call this function to get the audio specific configuration (ASC).
 *
 * The function can be called in any time between @ref aacOutAudioInit() and @ref aacOutAudioDone() functions.
 *
 * @param[in] instance a pointer to a @ref aacaenc_tt object
 * @param[out] ascbuf a pointer to a @ref aac_ascbuf structure
 * @return @ref aacOutErrNone if successful
 * @return @ref aacOutError if not
 */
int32_t MC_EXPORT_API aacOutGetAudioSpecificConfig(const aacaenc_tt *instance, aac_ascbuf *ascbuf);


APIEXTFUNC MC_EXPORT_API aacOutAudioGetAPIExt(uint32_t func);

#ifdef __cplusplus
}
#endif

//--------------------------------------------------------------------------

#endif // #if !defined (__ENC_AAC_API_INCLUDED__)

