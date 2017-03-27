/**
 @file  enc_mpa.h
 @brief MPEG Audio (Layer 1/2) Encoder API

 @verbatim
 File: enc_mpa.h

 Desc: MPEG Audio (Layer 1/2) Encoder API

 Copyright (c) 2015 MainConcept GmbH or its affiliates.  All rights reserved.

 MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.  
 This software is protected by copyright law and international treaties.  Unauthorized 
 reproduction or distribution of any portion is prohibited by law.
 @endverbatim
 **/

#if !defined (__ENC_MPA_API_INCLUDED__)
#define __ENC_MPA_API_INCLUDED__

#include "bufstrm.h"
#include "mcdefs.h"
#include "mcprofile.h"
#include "mcapiext.h"

typedef struct mpeg_a_encoder mpegaenc_tt;  ///< audio encoder object

#ifdef __GNUC__
#pragma pack(push,1)
#else
#pragma pack(push)
#pragma pack(1)
#endif

/**
 * @brief These parameters are used to configure the encoder.
 */
struct mpeg_a_settings
{
  int32_t audio_mode;       ///< type of audio encoding
  int32_t audio_layer;      ///< MPEG audio layer
  int32_t psych_model;      ///< MPEG psychoacoustic model
  int32_t audio_bitrate;    ///< code (range 1..14) that defines the audio bitrate (not the bitrate itself)
  int32_t emphasis;         ///< type of de-emphasis
  int32_t extension;        ///< state of the private bit in the audio sync headers
  int32_t error_protection; ///< turns the embedded CRC error protection information on/off
  int32_t copyright;        ///< state of the copyright bit in the audio sync headers
  int32_t original;         ///< state of the original bit in the audio sync headers
  int64_t pts_offset;       ///< pts of the start of the stream
  int32_t pts_units;        ///< the units of the pts_offset field

  int32_t reserved[1012];
};

#pragma pack(pop)


/////////////////////////////////////////////////////////////////////////////
// audio routines in mpgaout.dll
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Call this function to fill an @ref mpeg_a_settings structure with default values
 * based on an audio type.
 *
 * @param[in] set a pointer to a @ref mpeg_a_settings structure to be initialized
 * @param[in] profileID one of the preset values for profile. This field specifies
 * which default values will be used. It should be one of the following defines:
 *
 * <table>
 * <tr><th>value</th><th>meaning</th></tr>
 * <tr><td>@ref MCPROFILE_DEFAULT</td><td>default settings</td></tr>
 * <tr><td>@ref MPEG_MPEG1</td><td>generic ISO/IEC 11172-1/2</td></tr>
 * <tr><td>@ref MPEG_MPEG2</td><td>generic ISO/IEC 13818-1/2</td></tr>
 * <tr><td>@ref MPEG_VCD<br>@ref MCPROFILE_VCD</td><td>settings compatible with MPEG-1 VideoCD</td></tr>
 * <tr><td>@ref MPEG_SVCD<br>@ref MCPROFILE_SVCD</td><td>settings compatible with  MPEG-2 SuperVCD</td></tr>
 * <tr><td>@ref MPEG_DVD<br>@ref MCPROFILE_DVD</td><td>settings compatible with MPEG-2 DVD-Video</td></tr>
 * <tr><td>@ref MPEG_DVD_MPEG1<br>@ref MCPROFILE_DVD_MPEG1</td><td>settings compatible with MPEG-1 DVD-Video</td></tr>
 * <tr><td>@ref MPEG_DVD_DVR<br>@ref MCPROFILE_DVD_DVR</td><td>settings compatible with MPEG-2 DVD-VR</td></tr>
 * <tr><td>@ref MPEG_DVR_MPEG1<br>@ref MCPROFILE_DVD_DVR_MPEG1</td><td>settings compatible with MPEG-1 DVD-VR</td></tr>
 * <tr><td>@ref MPEG_DVB<br>@ref MCPROFILE_DVB</td><td>settings compatible with DVB</td></tr>
 * <tr><td>@ref MPEG_DVHS<br>@ref MCPROFILE_DVHS</td><td>settings compatible with DVHS</td></tr>
 * <tr><td>@ref MPEG_MMV<br>@ref MCPROFILE_MMV</td><td>settings compatible with MPEG-2 MICROMV</td></tr>
 * <tr><td>@ref MPEG_HDV_HD1<br>@ref MCPROFILE_HDV_HD1</td><td>settings compatible with MPEG-2 HDV HD1</td></tr>
 * <tr><td>@ref MPEG_HDV_HD2<br>@ref MCPROFILE_HDV_HD2</td><td>settings compatible with MPEG-2 HDV HD2</td></tr>
 * </table>
 * <br><br>
 * @param[out] set modified mpeg_a_settings structure
 * @return short description if the ID is valid
 * @return NULL if not
 */
char * MC_EXPORT_API mpegOutAudioDefaults(struct mpeg_a_settings *set, int32_t profileID);


/** @brief Call this function to create an @ref mpegaenc_tt audio encoding object which is used in other MPEG audio
 * encoding calls.
 *
 * This is also where the sampling rate is specified, note that MPEG only supports audio sampling
 * rates of 16kHz, 22.05kHz, 24kHz, 32kHz, 44.1kHz and 48kHz.
 *
 * @param[in] get_rc pointer to a get resource function
 * @param[in] set pointer to a filled in @ref mpeg_a_settings structure
 * @param[in] options reserved, set to 0
 * @param[in] CPU set to 0xFFFFFFFF for autodetect (reserved for CPU-flags)
 * @param[in] sampleRate sample rate of the input audio, must be:
 *			   16000, 22050, 24000, 32000, 44100 or 48000 Hz
 * @return pointer to a @ref mpegaenc_tt object if succesful
 * @return NULL if unsuccesful
 */
mpegaenc_tt * MC_EXPORT_API mpegOutAudioNew(void                         *(MC_EXPORT_API *get_rc)(const char* name),
                                            const struct mpeg_a_settings *set,
                                            int32_t                       options,
                                            int32_t                       reserved,
                                            int32_t sampleRate);



/** @brief Call this function to free an @ref mpegaenc_tt object
 *
 * @param[in] instance a pointer to a @ref mpegaenc_tt object
 */
void MC_EXPORT_API mpegOutAudioFree(mpegaenc_tt *a_enc);


/** @brief Call this function to initialize the MPEG audio encoder for an encoding
 * session.
 *
 * An existing bufstream object must be passed to this function, the MPEG audio
 * encoder will output the encoded data to the bufstream object.
 *
 * @param[in] instance a pointer to a @ref mpegaenc_tt object
 * @param[in] audiobs a pointer to a @ref bufstream_tt object for the compressed
 * data output stream
 * @return mpegOutErrNone if successful
 * @return mpegOutCancel if not
 */
int32_t MC_EXPORT_API mpegOutAudioInit(mpegaenc_tt *a_enc, bufstream_tt *audiobs);


/** @brief Call this function to encode a buffer of audio, which must contain 16-bit PCM audio data.
 *
 * The @ref audio_mode field of the @ref mpeg_a_settings structure passed to the @ref mpegOutAudioNew
 * function must match the type of audio data (stereo or mono) in the buffer. In addition the sampling rate
 * passed to the @ref mpegOutAudioNew function must match the sampling rate of the audio data in the buffer.
 *
 * @param[in] instance a pointer to a @ref mpegaenc_tt object
 * @param[in] audioBuffer a pointer to an audio buffer containing 16-bit PCM audio data
 * @param[in] numAudioBytes the number of bytes in the audio buffer
 * @return @ref mpegOutErrNone if successful
 * @return @ref mpegOutCancel if not
 */
int32_t MC_EXPORT_API mpegOutAudioPutBytes(mpegaenc_tt *a_enc, uint8_t *audioBuffer, uint32_t numAudioBytes);


/** @brief Call to finish an MPEG audio encoding session, set the abort flag
 * to a non-zero if audio encoding is being aborted.
 *
 * @param[in] instance a pointer to a @ref mpegaenc_tt object
 * @param[in] abort flag, set to a non-zero value to abort encoding
 * @return @ref mpegOutErrNone if successful
 * @return @ref mpegOutCancel if not
 */
int32_t MC_EXPORT_API mpegOutAudioDone(mpegaenc_tt *a_enc, int32_t abort);


/** @brief Call this function to check whether the audio settings are valid.
 *
 * The general MPEG compliance checks are done first and then the Format checks are done (if the mpeg type is one of
 * those types). Use the @ref CHECK_MPEG_ONLY flag in the options parameter to turn off the Format compliance checks
 * (only do the general MPEG compliance checks).
 *
 * If the get_rc parameter is non-NULL, any error messages are sent to the err_printf function.
 *
 * If the options parameter does not contain @ref CHECK_ALL, the function returns when the first non compliant value
 * is found (the remainder of the settings are not checked). If the options parameter does contain @ref CHECK_ALL,
 * all the checks are performed, an error message is sent to the err_printf callback for every error found and the
 * error code of the first error found is returned.
 *
 * The Format conformance checks will return an error code less than @ref INV_MPEG_ERROR and can be ignored if desired. The
 * settings may not produce a valid Format stream, but they will still produce a valid MPEG stream and the encoder will
 * accept them. This can be useful for producing non-standard Format streams.
 *
 * To fully check the audio settings, the mpeg type (one of the MPEG_* defines) and audio frequency is needed. If the
 * @ref sample_rate parameter is not a valid MPEG audio frequency, this call will fail.
 *
 * @param[in] get_rc a pointer to a get_rc function
 * @param[in] set a pointer to a filled in mpeg_a_settings structure
 * @param[in] mpeg_type one of the MPEG_* constants to check for VCD/SVCD/DVD audio conformance, use 0 for no
 *						VCD/SVCD/DVD conformance checks (see @ref mcdefs.h)
 * @param[in] sample_rate the audio frequency, either 32000, 44100 or 48000
 * @param[in] options @ref CHECK_MPEG_ONLY and/or @ref CHECK_ALL
 * @param[in] app reserved, set to NULL
 * @return @ref mpegOutErrNone if settings are valid
 * @return one of the INV_* error codes if an error is found (see @ref mcdefs.h)
 */
int32_t MC_EXPORT_API mpegOutAudioChkSettings(void                         *(MC_EXPORT_API *get_rc)(const char* name),
                                              const struct mpeg_a_settings *set,
                                              int32_t                       mpeg_type,
                                              int32_t                       sample_rate,
                                              uint32_t                      options,
                                              void                         *app);


/** @brief Call this function to get extended API function.
 * @param[in] func function ID
 * @return function pointer or NULL
 */

APIEXTFUNC MC_EXPORT_API mpegOutAudioGetAPIExt(uint32_t func);

#ifdef __cplusplus
}
#endif

//--------------------------------------------------------------------------

#endif // #if !defined (__ENC_MPA_API_INCLUDED__)


