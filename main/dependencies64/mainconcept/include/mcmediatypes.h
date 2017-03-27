/**
 * @file	mcmediatypes.h
 * @brief mediatype defines used for connection between components
 *       and for specification of input mediatypes by user apps
 *
 * @verbatim
 * ----------------------------------------------------------------------------
 * File: mcmediatypes.h
 *
 * Desc: mediatype defines used for connection between components
 *       and for specification of input mediatypes by user apps
 *
 * Copyright (c) 2015 MainConcept GmbH or its affiliates.  All rights reserved.
 *
 * MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.  
 * This software is protected by copyright law and international treaties.  Unauthorized 
 * reproduction or distribution of any portion is prohibited by law.
 *
 * ----------------------------------------------------------------------------
 * @endverbatim
 **/

#if !defined (__MC_MEDIATYPES_INCLUDED__)
#define __MC_MEDIATYPES_INCLUDED__


// describes the major type of a stream or a container type
typedef enum mcmajortypes
{
    mcmjtElementary = 0,

    mcmjtPES = 1,
    mcmjtPVA = 2,
    mcmjtMPEG1System = 3,
    mcmjtMPEG2Program = 4,
    mcmjtMPEG2Transport = 5,

    mcmjtMXF = 6,

    mcmjtMP4 = 7,

    mcmjtAVI = 8,
    mcmjtMKV = 9,

    mcmjtASF = 10

} mcmajortypes_t;


// stream media types
typedef enum mcmediatypes
{
    mctUnknown = 0,
    mctMinVideoType = 1,

    mctMPEG1V = 2,
    mctMPEG2V = 3,
    mctMPEG4V = 4,
    mctH263 = 5,
    mctH264 = 10,
    mctMVCSub = 11,                    ///< single MVC substream
    mctMVCMux = 12,                    ///< MVC stream with base + all substreams
    mctHEVC = 13, 
    mctVC1 = 15,
    mctDV = 20,
    mctJ2K = 25,
    mctMotionJPEG = 26,
    mctVC3 = 30,

    mctDIV3 = 35,                      ///< Older DivX 3.11 and 4 codecs,
    mctDIV4 = 36,                      ///< not completely mpeg-4 compliant

    mctMPEG4V3 = 40,                   ///< Microsoft MPEG-4 version 3

    mctMaxVideoType = 128,

    mctMinAudioType = 130,

    mctMPEG1A = 131,                   ///< MPEG-1 audio, layer is indicated in
    mctMPEG2A = 132,                   ///< MPEG-2 audio, the mc_audio_format_t.profile field
    mctMPEG3A = 132,                   ///< do not use, this does not mean layer 3!

    mctAES3_337M_MPEG1A = 133,         ///< MPEG-1 audio in an AES3 SMPTE 337M stream
    mctAES3_337M_MPEG2A = 134,         ///< MPEG-2 audio in an AES3 SMPTE 337M stream

    mctAAC_Generic = 140,              ///< use this media type if you don't exactly know which kind of AAC is in the stream 
                                       ///< - RAW, ADTS or LATM, and parsing is needed
    mctAAC_RAW = 141,
    mctAAC_LATM = 142,
    mctAAC_ADTS = 143,

    mctAC3 = 150,
    mctAC3_DDPlus = 151,
    mctAES3_337M_AC3 = 152,            ///< Dolby Digital audio wrapped in an AES3 SMPTE 337M stream
    mctAES3_337M_DDPlus = 153,         ///< Dolby Digital Plus audio wrapped in an AES3 SMPTE 337M stream
    mctAES3_337M_DOLBYE = 154,         ///< Dolby E audio wrapped in an AES3 SMPTE 337M stream
    
    mctAMR = 160,

    mctWMA = 165,
    mctWMAPro = 166,
    mctWMALossless = 167,

    mctSDDS = 170,

    mctDTS = 172,

    mctMaxAudioType = 199,

    mctMinPCMType = 200,
    
    mctPCM = 201,
    mctDVD_LPCM = 202,
    mctHDMV_LPCM = 203,

    mctAES3_302M = 210,                 ///< LPCM audio in an AES3 SMPTE 302M stream
    mctAES3_332M = 211,
    mctAES3_382M = 212,
    mctAES3_331M = 213,
    mctBWF = 214,

    mctTWOS_LPCM = 230,
    mctQT_PCM = 231,                   ///< used for generic PCM in MOV, usually the same as mctPCM
    mctIntel_ADPCM = 232,              ///< WAVE format tag 17 type
    mctMS_ADPCM = 233,                 ///< WAVE format tag 2 type

    mctAIFF = 240,

    mctALAW = 241,
    mctULAW = 242,

    mctMaxPCMType = 259,

    mctMinPrivateType = 260,
    mctDVB_Teletext = 269,
    mctPrivateBinary = 270,            ///< private stream to be encapsulated into TS with stream type = 0x06 
    mctDVD_Subtitles = 280,
    mctDXSB_Subtitles = 281,
    mctUTF8_Subtitles = 282,
    mctSSA_Subtitles = 283,
    mctASS_Subtitles = 284,
    mctUSF_Subtitles = 285,
    mctBMP_Subtitles = 286,
    mctVSUB_Subtitles = 287,
    mctDVB_Subtitles = 288,
    mctCFF_ImgSubtitles = 289,
    mctCFF_TxtSubtitles = 290,
    mctDXSA_Subtitles = 291,

    mctVBI_Data = 300,                ///< SMPTE ST-436 VBI Frame Elements (used in MXF)
    mctANC_Data = 301,                ///< SMPTE ST-436 ANC Frame Elements (used in MXF)

    mctSCTE35_Data = 340,             ///< SCTE 35 Digital Program Insertion Cueing Message for Cable (used in MP2)

    mctAES3_337M_DATA = 350,          ///< other data in an AES3 SMPTE 337M stream

    mctMaxPrivateType = 512

} mcmediatypes_t;


#ifdef __GNUC__
#pragma pack(push,8)
#else
#pragma pack(push)
#pragma pack(8)
#endif

#define MC_AUDIO_FORMAT_FLAG_PCM_IS_FLOAT       0x00000001    ///< PCM samples are floating point samples
#define MC_AUDIO_FORMAT_FLAG_PCM_IS_BIG_ENDIAN  0x00000002    ///< PCM samples are big endian samples
#define MC_AUDIO_FORMAT_FLAG_PCM_IS_SIGNED      0x00000004    ///< PCM samples are signed integer samples
#define MC_AUDIO_FORMAT_FLAG_IS_DOLBY_HYBRID    0x00000008    ///< Dolby stream contains both DD and DD+ frames

/** \struct mc_audio_format_t
 *	describes an audio stream
 *  \param profile              The value is specific for each media type.
 *  \param channels             The number of channels.
 *  \param samples_per_sec      The sample rate.
 *  \param avg_bytes_per_sec    The average bytes per second.
 *  \param bits_per_sample      The number of bits per sample.
 *  \param emphasis             0 - off, 1 - on, DVD LPCM audio.
 *  \param mute_flag            0 - off, 1 - on, DVD LPCM audio.
 *  \param dynamic_range_control  The DVD LPCM audio.
 *  \param language             The language code.
 *  \param reserved             reserved for future use
 */
// describes an audio stream
typedef struct mc_audio_format
{ 
    uint16_t profile;                  ///< the value is specific for each mediatype
    uint16_t channels;                 ///< the number of channels
    uint32_t samples_per_sec;          ///< the sample rate
    uint32_t avg_bytes_per_sec;        ///< the average bytes per second
    uint32_t bits_per_sample;          ///< the number of bits per sample
    uint8_t  emphasis;                 ///< 0 - off, 1 - on, DVD LPCM audio
    uint8_t  mute_flag;                ///< 0 - off, 1 - on, DVD LPCM audio
    int16_t  dynamic_range_control;    ///< DVD LPCM audio
    uint16_t language[4];              ///< language code
    uint32_t flags;                    ///< any of the MC_AUDIO_FORMAT_FLAG_xxx defines
    int16_t  blockSize;                ///< blockSize if any, like nBlockAlign in WAVEFORMATEX
    uint16_t country_code[4];          ///< country code
    uint16_t media_desc[4];            ///< media description

    uint8_t  reserved[2];

} mc_audio_format_t;


#define PASS_TYPE_UNKNOWN        0
#define PASS_TYPE_ANALYZE        1
#define PASS_TYPE_ENCODE         2

/*! \def MC_VIDEO_FORMAT_FLAG_INTERLACED
    \brief The define interlaced flag
   
    if known, equivalent to progressive_sequence in mpeg2, frame_mbs_only_flag in AVC, etc.
*/
#define MC_VIDEO_FORMAT_FLAG_INTERLACED    0x00000001    ///< if known, equivalent to progressive_sequence in mpeg2, frame_mbs_only_flag in AVC, etc
/*! \def MC_VIDEO_FORMAT_FLAG_PROGRESSIVE
    \brief The define progressive flag
   
    if known, equivalent to progressive_sequence in mpeg2, frame_mbs_only_flag in AVC, etc.
*/
#define MC_VIDEO_FORMAT_FLAG_PROGRESSIVE   0x00000002    ///< if known, equivalent to progressive_sequence in mpeg2, frame_mbs_only_flag in AVC, etc

/*! \def MC_VIDEO_FORMAT_FLAG_HAS_PULLDOWN
    \brief The define pulldown flag
   
    pulldown is present in at least some parts of the stream.
*/
#define MC_VIDEO_FORMAT_FLAG_HAS_PULLDOWN  0x00000004    ///< pulldown is present in at least some parts of the stream

/*! \def MC_VIDEO_FORMAT_FLAG_TFF
    \brief The define top field first flag
   
    if known, top field first flag.
*/
#define MC_VIDEO_FORMAT_FLAG_TFF           0x00000010    ///< if known, top field first flag

/*! \def MC_VIDEO_FORMAT_FLAG_BFF
    \brief The define bottom field first flag
   
    if known, bottom field first flag.
*/
#define MC_VIDEO_FORMAT_FLAG_BFF           0x00000020    ///< if known, bottom field first flag

/** \struct mc_video_format_t
 *	describes a video stream
 *  \param profile  The value is specific for each media type.
 *  \param level    The field takes the same value as defined in the corresponding specs.
 *  \param avg_bitrate              The average bitrate in bits per second
 *  \param avg_time_per_frame       The average time per frame, in 100-nanosecond units.
 *  \param width                    The width in pixels
 *  \param height                   The height in pixels
 *  \param pictAspRatioX            The X dimension of picture aspect ratio. For example, 16 for a 16x9 display
 *  \param pictAspRatioY            The Y dimension of the same
 *  \param is_vbr                   1 - VBR, 0 - CBR
 *  \param pass_num                 current pass number
 *  \param pass_type                one of PASS_TYPE_... defined above

 *  \param flags;                   any of the MC_VIDEO_FORMAT_FLAG_xxx defines

 *  \param stated_time_per_frame    The stated time per frame in seq type hdr, in 100-nanosecond units.
                                    This may differ from avg_time_per_frame if pulldown is present
 *  \param nalu_len                 The H.264 NALU length field size

 *  \param reserved                 reserved for future use

 */
// describes a video stream
typedef struct mc_video_format
{ 
    uint16_t profile;                  ///< the value is specific for each mediatype
    uint16_t level;                    ///< this field takes the same value as defined in the corresponding specs
    uint32_t avg_bitrate;              ///< the average bitrate in bits per second
    int64_t  avg_time_per_frame;       ///< the average time per frame, in 100-nanosecond units.
    uint32_t width;                    ///< the width in pixels
    uint32_t height;                   ///< the height in pixels
    uint32_t pictAspRatioX;            ///< the X dimension of picture aspect ratio. For example, 16 for a 16x9 display
    uint32_t pictAspRatioY;            ///< the Y dimension of the same
    uint8_t  is_vbr;                   ///< 1 - VBR, 0 - CBR
    uint8_t  pass_num;                 ///< current pass number
    uint8_t  pass_type;                ///< one of PASS_TYPE_... defined above

    uint32_t flags;                    ///< any of the MC_VIDEO_FORMAT_FLAG_xxx defines

    int64_t  stated_time_per_frame;    ///< the stated time per frame in seq type hdr, in 100-nanosecond units.
                                       ///< this may differ from avg_time_per_frame if pulldown is present
    uint8_t  nalu_len;                 ///< H.264 NALU length field size

    int32_t comp_mode;                 ///< compression mode

    uint8_t  reserved[44];

} mc_video_format_t;


/** \struct mc_subtitle_format_t
 *	describes a subtitle stream
 *  \param profile              The value is specific for each media type.
 *  \param avg_time_per_frame   The average time per frame, in 100-nanosecond units.
 *  \param width                The width in pixels.
 *  \param height               The height in pixels.
 *  \param language             The language code.
 *  \param bit_depth            The bit depth of a bitmap type subtitle.
 *  \param bitmap_size          The size of a fixed size bitmap subtitle.
 *  \param reserved             reserved for future use
 */

// describes a subtitle stream
typedef struct mc_subtitle_format
{
    uint16_t profile;                  ///< the value is specific for each mediatype
    int64_t  avg_time_per_frame;       ///< the average time per frame, in 100-nanosecond units.
    uint32_t width;                    ///< the width in pixels
    uint32_t height;                   ///< the height in pixels
    uint16_t language[4];              ///< language code

    int16_t  bit_depth;                ///< bitmap bit depth
    uint32_t bitmap_size;              ///< bitmap size

    uint16_t country_code[4];          ///< country code

    uint8_t *xml_namespace;            ///< null-terminated C string in UTF-8
    uint8_t *xml_schema_location;      ///< null-terminated C string in UTF-8

    uint16_t media_desc[4];            ///< media description

    uint8_t  reserved[8];

} mc_subtitle_format_t;

/** \struct mc_private_format_t
 *	describes a private stream
 *  \param reserved              up to user how to use the structure
 */
// describes a private stream
typedef struct mc_private_format
{
    uint8_t  reserved[64];             ///< up to user how to use the structure

} mc_private_format_t;

/** \struct mc_stream_format_t
 *	describes the format of a stream
 *  \param stream_majortype     The major type, usually mcmjtElementary here.
 *  \param stream_mediatype     The media type.
 *  \param pFormat              The pointer to one of the media structures (mc_video_format_t, mc_audio_format_t and etc).
 *  \param reserved             The value reserved for future use.
 *  \param cbExtraBytes         The number of bytes in pbExtraData.
 *  \param pbExtraData          The can hold SPS for video, or any additional info needed.
 */

// describes the format of a stream
typedef struct mc_stream_format
{
    mcmajortypes_t  stream_majortype;  ///< the major type, usually mcmjtElementary here
    mcmediatypes_t  stream_mediatype;  ///< the media type

    void           *pFormat;           ///< pointer to one of the above structures

    uint8_t         reserved[32];

    uint16_t        cbExtraBytes;      ///< number of bytes in pbExtraData
    uint8_t        *pbExtraData;       ///< can hold SPS for video, or any additional info needed

} mc_stream_format_t;



// SCTE-35 structures and defines. Most structure fields represent the
// same named fields in the SCTE-35 spec

// specifies the time of a splice event
typedef struct mc_scte35_splice_time
{
    uint8_t time_specified_flag;            ///< valid flag for the pts_time field
    uint64_t pts_time;                      ///< splice time in 90 kHz units

} mc_scte35_splice_time_t;

// specifies the duration of a splice
typedef struct mc_scte35_break_duration
{
    uint8_t auto_return;                    ///< when set to 1 the duration is used as end of break
    uint64_t duration;                      ///< duration time in 90 kHz units

} mc_scte35_break_duration_t;


// command types, all other values are reserved
#define MC_SCTE35_SPLICE_NULL               0x00
#define MC_SCTE35_SPLICE_SCHEDULE           0x04
#define MC_SCTE35_SPLICE_INSERT             0x05
#define MC_SCTE35_TIME_SIGNAL               0x06
#define MC_SCTE35_BANDWIDTH_RESERVATION     0x07
#define MC_SCTE35_PRIVATE_COMMAND           0xFF


// private command, used when command type is MC_SCTE35_PRIVATE_COMMAND
typedef struct mc_scte35_private_command
{
    uint32_t identifier;                    ///< private identifier
    uint32_t private_data_length;           ///< length of data in pPrivateData
    uint8_t *pPrivateData;                  ///< pointer to private data

} mc_scte35_private_command_t;


// time signal command, used when command type is MC_SCTE35_TIME_SIGNAL
typedef struct mc_scte35_time_signal
{
    mc_scte35_splice_time_t splice_time;    ///< time of descriptors that follow

} mc_scte35_time_signal_t;


// splice insert component, specifies a splice time for a stream
typedef struct mc_scte35_splice_insert_component
{
    uint8_t component_tag;                  ///< stream component tag specified in PMT
    mc_scte35_splice_time_t splice_time;    ///< splice time for the stream,
                                            ///< valid if parent mc_splice_insert_t.splice_immediate_flag = 0

} mc_scte35_splice_insert_component_t;


// splice insert command, used when command type is MC_SCTE35_SPLICE_INSERT
typedef struct mc_scte35_splice_insert
{
    uint32_t splice_event_id;               ///< ID of the splice event
    uint8_t splice_event_cancel_indicator;  ///< if set to 1, signals that the splice event is being cancelled.
    
    // NOTE: the remainder of this structure is only valid if splice_event_cancel_indicator = 0
    uint8_t out_of_network_indicator;       ///< 0 = in point, 1 = out point
    uint8_t program_splice_flag;            ///< 0 = splice time specified for each component (stream)
                                            ///< 1 = splice time specified for all streams
    uint8_t duration_flag;                  ///< 1 = duration time is specified, 0 = no duration specified
    uint8_t splice_immediate_flag;          ///< 1 = splice immediately (or at nearest opportunity), no splice times are specified
                                            ///< 0 = splice times are specified

    mc_scte35_splice_time_t splice_time;    ///< program splice time, valid if program_splice_flag = 1 && splice_immediate_flag = 0

    uint8_t component_count;                ///< number of components in pComponents list, valid if program_splice_flag = 0
    mc_scte35_splice_insert_component_t *pComponents;   ///< component splice time, can be used as pComponents[idx]

    mc_scte35_break_duration_t break_duration;  ///< splice duration, valid if duration_flag = 1

    uint16_t unique_program_id;             ///< unique ID for the viewing event in the service
    uint8_t avail_num;                      ///< ID for a specific avail within one unique_program_id
    uint8_t avails_expected;                ///< count of the expected number of individual avails within the current viewing event

} mc_scte35_splice_insert_t;


// splice event component, defines a splice time for a stream
typedef struct mc_scte35_splice_event_component
{
    uint8_t component_tag;                  ///< stream component tag specified in PMT
    uint32_t utc_splice_time;               ///< UTC time (in seconds) of the splice event

} mc_scte35_splice_event_component_t;


// splice event, defines a splice event
typedef struct mc_scte35_splice_event
{
    uint32_t splice_event_id;               ///< ID of the splice event
    uint8_t splice_event_cancel_indicator;  ///< if set to 1, signals that the splice event is being cancelled.

    // NOTE: the remainder of this structure is only valid if splice_event_cancel_indicator = 0
    uint8_t out_of_network_indicator;       ///< 0 = in point, 1 = out point
    uint8_t program_splice_flag;            ///< 0 = splice time specified for each component (stream)
                                            ///< 1 = splice time specified for all streams
    uint8_t duration_flag;                  ///< 1 = duration time is specified, 0 = no duration specified

    uint32_t utc_splice_time;               ///< UTC time (in seconds) of the splice event, valid if program_splice_flag = 1

    uint8_t component_count;                ///< number of components in pComponents list, valid if program_splice_flag = 0
    mc_scte35_splice_event_component_t *pComponents;    ///< component splice time, can be used as pComponents[idx]

    mc_scte35_break_duration_t break_duration;  ///< splice duration, valid if duration_flag = 1

    uint16_t unique_program_id;             ///< unique ID for the viewing event in the service
    uint8_t avail_num;                      ///< ID for a specific avail within one unique_program_id
    uint8_t avails_expected;                ///< count of the expected number of individual avails within the current viewing event

} mc_scte35_splice_event_t;


// splice schedule command, used when command type is MC_SCTE35_SPLICE_SCHEDULE
typedef struct mc_scte35_splice_schedule
{
    uint8_t splice_count;                   ///< the number of splice events in the pEvents list
    mc_scte35_splice_event_t *pEvents;      ///< splice events, can be used as pEvents[idx]

} mc_scte35_splice_schedule_t;


// avail descriptor
typedef struct mc_scte35_avail_descriptor
{
    uint32_t provider_avail_id;             ///< provider information

} mc_scte35_avail_descriptor_t;


// DTMF descriptor
typedef struct mc_scte35_dtmf_descriptor
{
    uint8_t preroll;                        ///< the time the DTMF is presented to the analog output of the device in tenths of seconds
    uint8_t dtmf_count;                     ///< the length of the DTMF sequence in DTMF_char
    uint8_t DTMF_char[8];                   ///< the DTMF sequence

} mc_scte35_dtmf_descriptor_t;


// segmentation descriptor component
typedef struct mc_scte35_segmentation_component
{
    uint8_t component_tag;                  ///< stream component tag specified in PMT
    uint64_t pts_offset;                    ///< 90 kHz offset to be added to the pts_time in a time_signal() command

} mc_scte35_segmentation_component_t;


// segmentation descriptor UPID
typedef struct mc_scte35_segmentation_upid
{
    uint8_t segmentation_upid_type;         ///< UPID type
    uint32_t mpu_format_identifier;         ///< MPU() format identifier, valid if segmentation_upid_type = 12
    uint8_t length;                         ///< length of the UPID data
    uint8_t *pSegmentationUPID;             ///< UPID data

} mc_scte35_segmentation_upid_t;


// segmentation descriptor
typedef struct mc_scte35_segmentation_descriptor
{
    uint32_t segmentation_event_id;         ///< unique segmentation event identifier
    uint8_t segmentation_event_cancel_indicator;    ///< if set to 1, signals that the segmentation event is being cancelled.

    // NOTE: the remainder of this structure is only valid if segmentation_event_cancel_indicator = 0
    uint8_t program_segmentation_flag;      ///< 0 = segmentation specified for each component (stream)
                                            ///< 1 = segmentation specified for all streams
    uint8_t segmentation_duration_flag;     ///< 1 = duration time is specified, 0 = no duration specified
    uint8_t delivery_not_restricted_flag;   ///< 1 = restricted delivery, 0 = not restricted

    // these are valid if delivery_not_restricted_flag = 0
    uint8_t web_delivery_allowed_flag;      ///< 1 = no web restrictions, 0 = restrictions apply
    uint8_t no_regional_blackout_flag;      ///< 1 = no blackout restrictions, 0 = restrictions apply
    uint8_t archive_allowed_flag;           ///< 1 = no archive restrictions, 0 = restrictions apply
    uint8_t device_restrictions;            ///< group restriction flags

    uint8_t component_count;                ///< number of components in pComponents list, valid if program_segmentation_flag = 0
    mc_scte35_segmentation_component_t *pComponents;    ///< segmentation offsets, can be used as pComponents[idx]

    uint64_t segmentation_duration;         ///< segmentation duration in 90 kHz units, valid if segmentation_duration_flag = 1

    uint32_t segmentation_upid_count;       ///< number of UPID's in pUPIDs list
    mc_scte35_segmentation_upid_t *pUPIDs;  ///< UPID's, can be used as pUPIDs[idx]

    uint8_t segmentation_type_id;           ///< segmentation type ID
    uint8_t segment_num;                    ///< segment number in pSegmentationUPIDData
    uint8_t segments_expected;              ///< extecpted number of segments
 
} mc_scte35_segmentation_descriptor_t;


// time descriptor
typedef struct mc_scte35_time_descriptor
{
    uint64_t TAI_seconds;                   ///< TAI (International Atomic Time) seconds value
    uint32_t TAI_ns;                        ///< TAI nanoseconds value
    uint16_t UTC_offset;                    ///< used in the conversion from TAI time to UTC or NTP time

} mc_scte35_time_descriptor_t;


// other descriptors
typedef struct mc_scte35_unknown_descriptor
{
    uint8_t splice_descriptor_tag;          ///< descriptor tag

    uint32_t data_len;                      ///< length of data in pData
    uint8_t *pData;                         ///< unknown descriptor data

} mc_scte35_unknown_descriptor_t;


// splice information section
typedef struct mc_scte35_splice_info
{
    uint8_t  protocol_version;              ///< SCTE-35 protocol version
    uint8_t  encrypted_packet;              ///< 1 = data after tier field is encrypted, 0 = not encrypted
    uint8_t  encryption_algorithm;          ///< specifies the encryption algorithm
    uint64_t pts_adjustment;                ///< pts adjustment in 90 kHz units, added to pts or segment times
    uint8_t  cw_index;                      ///< control word (key) used for decryption
    uint16_t tier;                          ///< message authorization tiers

    uint8_t  splice_command_type;           ///< splice command, valid if encrypted_packet = 0
    void *pCommand;                         ///< valid if splice_command_type is one of:
                                            ///<      MC_SCTE35_SPLICE_SCHEDULE   - pointer to an mc_scte35_splice_schedule_t structure
                                            ///<      MC_SCTE35_SPLICE_INSERT     - pointer to an mc_scte35_splice_insert_t structure
                                            ///<      MC_SCTE35_TIME_SIGNAL       - pointer to an mc_scte35_time_signal_t structure
                                            ///<      MC_SCTE35_PRIVATE_COMMAND   - pointer to an mc_scte35_private_command_t structure

    uint8_t avail_descriptor_count;         ///< number of avail descriptors, valid if encrypted_packet = 0
    mc_scte35_avail_descriptor_t *pAvailDescriptors;

    uint8_t dtmf_descriptor_count;          ///< number of DTMF descriptors, valid if encrypted_packet = 0
    mc_scte35_dtmf_descriptor_t *pDTMFDescriptors;

    uint8_t segmentation_descriptor_count;  ///< number of segmentation descriptors, valid if encrypted_packet = 0
    mc_scte35_segmentation_descriptor_t *pSegmentationDescriptors;

    uint8_t time_descriptor_count;          ///< number of time descriptors, valid if encrypted_packet = 0
    mc_scte35_time_descriptor_t *pTimeDescriptors;

    uint8_t unknown_descriptor_count;       ///< number of unknown descriptors, valid if encrypted_packet = 0
    mc_scte35_unknown_descriptor_t *pUnknownDescriptors;

    uint32_t reserved[64];                  ///< reserved for future use

} mc_scte35_splice_info_t;

/**
 @brief structure describes binary serialization of SCTE-35 splice info section
 */

typedef struct mc_scte35_packet_t
{
    // bytes 0..4092 contain valid payload of SCTE-35 splice info (but usually,
    // less bytes are needed, so trailing bytes are just padding) followed by
    // CRC32 of entire section
    uint8_t data[4096]; //!< actual payload

    uint16_t length; //!< payload length
}
mc_scte35_packet;

/**
 * @brief structure describes encryption key used to encrypt SCTE-35 splice info section payload
 */
typedef struct mc_scte35_key_t
{
    const uint8_t * key; //!< actual key payload
    uint32_t length; //!< payload length
}
mc_scte35_key;

/**
 * @brief structure contains multiple encryption keys (e.g. for DES EDE3 CBC mode uses 3 keys)
 */
typedef struct mc_scte35_key_group_t
{
    const mc_scte35_key * keys; //!< keys to be used for encryption
    uint32_t count; //!< number of keys to be used
}
mc_scte35_key_group;

#pragma pack(pop)

#endif // #if !defined (__MC_MEDIATYPES_INCLUDED__)

