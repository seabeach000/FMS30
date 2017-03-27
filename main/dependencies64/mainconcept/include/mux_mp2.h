/* ----------------------------------------------------------------------------
 * File: mux_mp2.h
 *
 * Desc: MPEG Muxer API
 *
 * Copyright (c) 2014 MainConcept GmbH or its affiliates.  All rights reserved.
 *
 * MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.
 * This software is protected by copyright law and international treaties.  Unauthorized
 * reproduction or distribution of any portion is prohibited by law.
 * ----------------------------------------------------------------------------
 */

/*! @file /mux_mp2.h
 */

#if !defined (__MUX_MP2_API_INCLUDED__)
#define __MUX_MP2_API_INCLUDED__

#include "bufstrm.h"
#include "mcdefs.h"
#include "mcprofile.h"
#include "mcmediatypes.h"
#include "mcapiext.h"


typedef struct MP2Muxer mp2muxer_tt;   //!< Muxer object

//! @name Feature Flags
//! @brief flags used with \ref  mp2muxer_set_struct.feature_flags field
//! @{
#define MUX_FEATURE_TS_ATS            0x00000001  /*!< @brief add 4-byte arrival time stamp prefix to all transport stream packets
                                                   only the lower 30 bits of the 4 bytes are used
                                                   only the lower 30 bits of the 4 bytes are used
                                                   the upper 2 bits are set to 0*/
#define MUX_FEATURE_TS_NO_PSI         0x00000002  /*!< @brief no transport stream Program Specific Information (PAT, PMT, etc.)
                                                   is placed in the transport stream */
#define MUX_FEATURE_TS_AU_INFO        0x00000004  /*!< @brief AU_information private data as defined by ETSI TS 101 154 V1.7.1
                                                   is placed in the transport stream */
#define MUX_FEATURE_TS_PCR_IFRAMES    0x00000008  /*!< @brief  PCR is placed in transport stream packets that contain the start
                                                   of an I or IDR frame */
#define MUX_FEATURE_TS_PCR_ALL_FRAMES 0x00000010  /*!< @brief  PCR is placed in transport stream packets that contain the start
                                                    of any frame */
#define MUX_FEATURE_DISABLE_THREADING 0x00000020  /*!< @brief  do not create a thread for muxing, muxing is done on input stream threads */
#define MUX_FEATURE_SPLIT_ON_I_FRAMES 0x00000040  /*!< @brief  split output at an I frame of the primary video stream */
#define MUX_FEATURE_SPLIT_START_PSI   0x00000080  /*!< @brief  start split segment with PSI information */
//!@}


//! @name Flags
//! @brief flags used with \ref mp2mux_stream_set_struct.flags field
//! @{
#define STREAM_FLAG_STILL_PICTURES    0x00000001  /*!< @brief video stream contains still images, I frames only! */
#define STREAM_FLAG_VCD_VBV_UPDATE    0x00000002  /*!< @brief  only use with a single I frame, STREAM_FLAG_STILL_PICTURES
                                                   must also be present. The Muxer will update the VBV in the
                                                   seq hdr to the length of the pic rounded up to a multiple
                                                   of 2048 bytes (as well as the P-STD buffer).*/
#define STREAM_FLAG_SVCD_STILL_OFFSET 0x00000004  /*!< @brief  put a SVCD scan offset in the still picture
                                                   STREAM_FLAG_STILL_PICTURES must also be present*/
#define STREAM_FLAG_SUBPIC_WITH_PTS   0x00000008  /*!< @brief  each subpic is prefixed by an 8 byte (int64_t) PTS value, file mux only!*/
#define STREAM_FLAG_H264_AU_DELIMITER 0x00000010  /*!< @brief  put an AU delimiter before each H.264 frame*/
#define STREAM_FLAG_STOP_AT_EOF       0x00000020  /*!< @brief  stop muxing when this file ends, file muxing only, video or audio only*/
#define STREAM_FLAG_HDMV_SECONDARY    0x00000040  /*!< @brief  stream is a secondary stream for BluRay or HDMV profiles*/
#define STREAM_FLAG_HDMV_LONG_GOP     0x00000080  /*!< @brief  stream contains long GOP's (> 1s), for BluRay profiles*/
#define STREAM_FLAG_H264_RX_BD_STYLE  0x00000100  /*!< @brief  no longer used, this flag is ignored*/
#define STREAM_FLAG_ASSOCIATED_AUDIO  0x00000200  /*!< @brief  this audio stream is associated with another audio stream in a program*/
#define STREAM_FLAG_WAIT_FOR_DATA     0x00000400  /*!< @brief  if this flag is not set the muxer will consider the stream intermittent and 
                                                   will not wait for data if other streams are ready to mux.*/
//!@}


//! @name Generic stream types
//! @brief if possible specify the actual media type in mp2mux_stream_set_struct.format_struct
//! if not possible these can still be used instead
//! @{
#define STREAM_FLAG_VIDEO_STREAM      0x00010000  //!< stream is a video stream
#define STREAM_FLAG_AUDIO_STREAM      0x00020000  //!< stream is an audio stream
#define STREAM_FLAG_SUBPIC_STREAM     0x00040000  //!< stream is a subpicture stream
//!@}

//! @name Extended Flags
//! @brief flags for the mp2mux_ext_set_struct.flags field
//! if not possible these can still be used instead
//! @{
#define EXT_FLAG_EMPTY_SECTORS        0x00000001  //!< make empty sectors instead of padding sectors, VCD only
#define EXT_OUTPUT_DATA_FOR_XML       0x00000002  //!< output video_seq_info_xml and video_au_info_xml data
#define EXT_USE_PROGRAM_NUMBER        0x00000010  //!< obsolete. Use mp2mux_ts_program_set_struct.program_number
#define EXT_USE_NETWORK_ID            0x00000020  //!< obsolete. Set the network_ID to 0 to calculate it automatically, otherwise it's considered as valid value
#define EXT_USE_TRANSPORT_ID          0x00000040  //!< obsolete. Set the transport_ID to 0 to calculate it automatically, otherwise it's considered as valid value
#define EXT_PAD_PES_EXTENSION         0x00000080  /*!< @brief add 3 PES padding bytes to reserve space for a PES
                                                    extension in the first packet of each stream in a VOBU
                                                    mplex_type must be one of the DVD types! */
#define EXT_AUDIO_NO_SPAN_VOBU        0x00000100  /*!< @brief  do not let an audio frame span a VOBU
                                                   boundary. mplex_type must be one of the DVD types */
#define EXT_PTS_START_OFFSETS         0x00000200  /*!< @brief  streaming input PTS's start with offset,
                                                   adjust SCR start accordingly, leave audio PTS untouched*/
#define EXT_WARN_ON_LOW_MUXRATE       0x00000400  /*!< @brief  call wrn_printf (instead of calling inf_printf,
                                                   if the user mux rate is computed to be too low*/
#define EXT_ERR_ON_LOW_MUXRATE        0x00000800  /*!< @brief  call err_printf and abort (instead of calling inf_printf and continuing),
                                                   if the user mux rate is computed to be too low*/
#define EXT_PRESERVE_TIMESTAMPS       0x00001000  /*!< @brief  obsolete flag, incoming timestamps are used by default*/
//!@}


//! @name Error Codes
//! @{
#define MUX_OK           0
#define MUX_NOVID        1
#define MUX_NOAUD1       2
#define MUX_NOAUD2       4
#define MUX_NOTHINGTODO  8
#define MUX_ERR         16
#define MUX_NOSP        32
#define MUX_NOTIMP      64
//!@}


#ifdef __GNUC__
  #pragma pack(push,1)
#else
  #pragma pack(push)
  #pragma pack(1)
#endif


struct dash_vr_set_struct
{
    uint8_t dci_cci_ss;
    uint8_t dci;
    uint8_t cci;
    uint8_t mnf_id[32];
    uint8_t mnfi_dt[1944];
};

//! @brief This structure is used to commit any SI table changes
//! @details This structure is used to commit any SI table changes made since the last commit. If all SI table
//! changes are to start at the same time, they can all be done and then applied with a single commit call.
struct si_commit_struct
{
    int64_t target_time_PCR;          //!< the PCR time at which SI config should be applied. In 27 MHz units.
                                      /*!< @details The PCR time (in 27 MHz units) when the new SI data should be
                                      applied. If this field is set to 0 the new SI data is applied immediately.*/
    uint8_t no_version_update;        //!< set to 1 so the table version number does not increment

    uint8_t reserved[127];            //!< Reserved for future use
};

//! @brief availabe values for \ref si_descriptor_struct.target_loop
typedef enum
{
    eOuter_descriptor_loop = 0,       //!< descriptor loop of a PSI section
    eInner_descriptor_loop = 1        //!< descriptor loop of entries
} loop_level_enum;


//! @brief  SI descriptor to be placed in a table or entry
//! @details This structure is used to load descriptors into the SI tables for Transport Stream profiles, use it with the
//! ::mpegOutMP2MuxLoadDescriptor function. The user is responsible for the syntax of the descriptor, including the
// \ref si_descriptor_struct.descriptor_tag and \ref si_descriptor_struct.descriptor_length.
struct si_descriptor_struct
{
    int32_t target_table_id;          //!< target table id for the descriptor
    int32_t target_table_id_ext;      //!< target table id extension
                                      /*!< @details
                                       It's excessive for such tables as PAT, since table_id = 0x0
                                       is enough for distinguishing of this table;
                                       But if many tables can exist with the same table_id (PMT for ex.),
                                       we need to distinguish between tables using \ref target_table_id_ext.
                                       Example: for NIT the \ref target_table_id_ext represents network_id.
                                       For PMT specify the program_number as the \ref target_table_id_ext.*/
    int32_t target_table_type;        //!< target table type. Set to -1 if it's not required

    loop_level_enum target_loop;      //!< specify the target descriptor loop for the descriptor to be loaded. Use \ref loop_level_enum.

    // only used for inner loop
    int32_t target_entry_id;          //!< target entry id, only for inner loop
                                      /*!< @details
                                      Use this field to specify the target entry ID for the descriptor to be loaded.
                                      This field is only used when the target_loop value is set \ref eInner_descriptor_loop.
                                      For example, in a PMT table the  elementary_PID plays the role of \ref target_entry_id.*/

    int32_t target_entry_id_ext;      //!< target entry id extension, set to -1 if not required
                                      /*!< @details
                                       it's excessive for most entries, such as PMT entry. But
                                       NIT entry is identified by two id's - transport_id and orig_network_id*/
    uint8_t descriptor_tag;           //!< specify the tag of the descriptor.
    uint8_t descriptor_length;        //!< the number of bytes pointed to by the \ref pbData pointer
    uint8_t* pbData;                  //!< @brief  pointer to the data.
                                      //!< @details It is copied to the Muxer's internal memory
                                      //!< and can be freed after the load descriptor call
    uint8_t replace_existing;         //!< set to '1' to replace any existing descriptor in the entry with the same \ref descriptor_tag

    uint8_t reserved[32];             //!< Reserved for future use
};


//! @brief complete SI entry to be placed in a table
//! @details This structure is used to load entries into the SI tables for Transport Stream profiles, use it with the
//! ::mpegOutMP2MuxLoadEntry function. The user is responsible for the syntax of the entry.
struct si_entry_struct
{
    int32_t target_table_id;          //!< target table to which the entry should be loaded.
    int32_t target_table_id_ext;      //!< target table id extension. Set to -1 if it's not required
    int32_t target_table_type;        //!< target table type. Set to -1 if it's not required

    int32_t entry_length;             //!< the number of bytes pointed to by the \ref pbData pointer
    uint8_t* pbData;                  //!< @brief pointer to the data.
                                      //!< @details It is copied to the Muxer's internal memory
                                      //!< and can be freed after the load entry call

    int32_t target_entry_id;          //!< @brief target entry id
                                      //!< @details Use this field to specify the target entry ID for the entry to be loaded.
                                      //!< For example, for an EIT0 table the event_id plays the role of \ref target_entry_id
    int32_t target_entry_id_ext;      //!< @brief target entry id extension
                                      //!< @details Use this field to specify the target entry ID extension for an entry to be
                                      //!< loaded. Set to -1 if not needed.

    uint8_t replace_existing;         //!< set to '1' to replace any existing entry with the same \ref target_entry_id and \ref target_entry_id_ext

    uint8_t reserved[32];             //!< Reserved for future use
};


//! @brief  complete SI section to be placed in a table
//! @details This structure is used to load sections into the SI tables for Transport Stream profiles, use it with the
//! ::mpegOutMP2MuxLoadSection function. The user is responsible for the syntax of the section.
struct si_section_struct
{
    int32_t target_table_id;          //!< target table of the section.
    int32_t target_table_id_ext;      //!< target table id extension. Set to -1 if it's not required
    int32_t target_table_type;        //!< target table type. Set to -1 if it's not required

    uint32_t section_length;          //!< the number of bytes pointed to by the \ref pbData pointer
    uint8_t* pbData;                  //!< @brief pointer to the data.
                                      //!< @details It is copied to the Muxer's internal memory
                                      //!< and can be freed after the load section call

    uint8_t reserved[32];             //!< Reserved for future use
};

//! @brief  Add an SI table
//! @details This structure is used to add an SI table for Transport Stream profiles, use it with the
//! ::mpegOutMP2MuxAddTable function. The user is responsible for the syntax of the section in the table.
struct si_table_struct
{
    uint16_t PID;                     //!< PID for the table
    uint8_t table_id;                 //!< the table ID
    uint32_t repetition_rate;         //!< repetition rate in milliseconds, set to 0 for on demand

    int32_t parent_program_number;    //!< the program number of the program that owns this stream
                                      /*!< @details If set to -1, the PID is not listed in any PMT. */
    uint8_t stream_type;              //!< stream type for PMT descriptor if parent_program_number is >= 0

    uint8_t reserved[32];             //!< Reserved for future use
};

//! @brief provide information to the Muxer about a stream
//! @details structure is used to provide information to the Muxer about a
//! stream when calling the ::mpegOutMP2MuxAddStream or ::mpegOutMP2MuxAddFile functions.
struct mp2mux_stream_set_struct
{
    mc_stream_format_t format_struct; //!< mc_mediatype and format structure: video, audio or user-defined private
                                      /*!< @details This field is a basic \ref mc_stream_format_t structure, which is aimed
                                      at providing the most important info about the stream's format and settings.
                                      The format_struct has a major type (PES / ES) and media type (AAC, H.264,
                                      VC-1, etc.) definitions. The format_struct.pFormat can be cast to the
                                      pointers to mc_video_format, mc_audio_format or mc_subtitle_format structures.
                                      These structures provide such info as bit rate, frame rate, picture
                                      width/height, etc. for video; sample rate, number of channels,
                                      quantization etc. for audio. Refer to \ref mcmediatypes.h for the details.
                                      @note An application is responsible for memory allocating / deallocating of the pFormat.*/

    int32_t stream_fifo_size;         //!< @brief the size of the FIFO in bytes being used for this stream,
                                      /*!< @details This field specifies the size in bytes of the FIFO being
                                      passed to the Muxer. If the FIFO size is passed, the Muxer can compute
                                      a sufficiently large enough and more efficient internal FIFO. If the
                                      input FIFO size is larger than 1.5MB, it is recommended to set this value
                                      to the FIFO size, set to 0 to have the Muxer use a default value.
                                      This field is only used when passed to the ::mpegOutMP2MuxAddStream function.*/

    int32_t stream_rate_bps;          //!< @brief Optional field. Sets the bitrate of the stream.
                                      /*!< @details If the input media type is private or doesn't contain any headers
                                           (i.e. PCM, subpicture),
                                         the bitrate must be specified by this parameter. It also effective for
                                         'parse-able' video / audio: this parameter is applied with higher priority than
                                       the bitrate specified in the bit stream.*/

    int32_t delay_ms;                 //!< stream delay relative to other streams, 0 = automatically computed
    int32_t id;                       //!< PES stream ID, 0 = automatically computed
                                      /*!< @details This field specifies the MPEG stream ID of this stream
                                      placed in the PES packet headers. Set to 0 to have the Muxer assign a value,
                                      it assigns values starting with the lowest available stream number for
                                      the given stream type (video streams = 0xE0, MPEG audio = 0xC0). For
                                      non-MPEG streams (LPCM, AC-3 or subpicture) this value must be set to 0xBD if it
                                      is non-zero.*/
    int32_t PES_length;               //!< specifies the size of a program stream PES packet
                                      /*!< @details This option is only available for Transport Stream.
                                      If this parameter is enabled, the multiplexer writes a
                                      certain value of video PES packet length, instead of writing zero value.
                                      this field is ignored if the \ref mp2muxer_set_struct.sector_size field is > 0*/
    int32_t parent_program_PID;       //!< optional, PID of program that contains this stream
                                      /*!< @details The PID of the program to which the stream belongs to.
                                      The fields value must match the value in
                                      \ref  mp2mux_ts_program_set_struct.program_PID field   passed to the multiplexer.*/
    int32_t flags;                    //!< flags, one or more of the STREAM_FLAGS_ defines
                                      /*!< @details The best way to specify the media type is to use the format_struct.
                                       If it's not possible or format_struct is not filled at all, this parameter
                                       MUST contain one and only one of: STREAM_FLAG_VIDEO_STREAM, STREAM_FLAG_AUDIO_STREAM or STREAM_FLAG_SUBPIC_STREAM
                                       */

    int32_t still_picture_duration;   //!< @brief duration of still pictures
                                      //!< @details  duration of still pictures if the STREAM_FLAG_STILL_PICTURES flags
                                      //!< is present. The value is the number of frames to display each picture

    int32_t PID;                      //!< PID, 0 = automatically computed, TS stream only
                                      /*!< @details The PID value as defined in 2.4.3.7 of ISO 13818-1. For the profiles
                                      which restrict the values of PID (e.g. AVCHD, Blu-ray), this value is assigned
                                      internally by the multiplexer to fit the profile requirements. For such profiles,
                                      any wrong specified value is replaced with the value regulated by the profile.
                                      For the profiles which allows free PID assignment, the default value is 0x3E9
                                      for the first input stream, increasing by 1 for each next stream. Set to 0 to have
                                      the Muxer compute a value.*/

    int32_t PSTD_buffer_size;         //!< P-STD buffer size, PS stream only
                                      //!< @details This field specifies the P-STD buffer size of the stream in KB,
                                      //!<  set to 0 to have the Muxer compute a value.
    int32_t sub_id;                   //!< substream ID
                                      /*!< @details This field specifies the substream ID of this stream, the ID of
                                           an MPEG PRIVATE stream PES packet. Set to 0 to have the Muxer assign a value,
                                           it assigns values starting with the lowest available stream
                                            number for the given stream type (LPCM = 0xA0, AC3 = 0x80 and subpicture = 0x20).*/

    uint8_t shared_mpts_stream_flag;  //!< set to 1 to indicate the stream is shared among all the programs being multiplexed
    int32_t cpb_size_bits;            //!< specify the VBV/CPB size of the input stream
                                      //!< @details Use to indicate the CPB/VBV size (in bits) of a stream if known, this will override any detected size

    uint8_t align_in_flag;            //!< set to 1 to indicate the access units for this stream will come in as complete units
    uint8_t opt_packing_flag;         //!< @brief set to 1 to enable packing multiple access units in a single PES packet in transport streams
                                      //!< or program streams with fixed size packets
    uint8_t enhanced_parsing_flag;    //!< set to 1 to enable parsing of input stream data when new data has a valid time stamp

    int32_t max_stream_delay;         //!< specify the maximum PTS/sys clock difference (in ms) for this stream, 0 = automatically computed
                                      /*!< @details Use this field to specify the maximum delay (in ms) between the PCR/SCR and the
                                      PTS/DTS of the stream.
                                      The default max delay for audio streams is usually <= 250ms, the default for video streams other than
                                      AVC is 1s. The default value for other stream types is 1s.
                                      The default for AVC streams depends on the CPB size/bitrate ratio, if the CPB size = (max or cbr)
                                      bitrate the max delay will be 1s. If CPB size is 2x the bitrate the max delay will be 2s, etc up to a
                                      maximum of 10s.
                                      Set to 0 to have the Muxer compute a value. Note that if the value is too low, there may be underflows
                                      in the stream while muxing.
                                      See the "AVC in MPEG-2 Transport Streams" section below for more information.
                                      */
    uint8_t aes_frame_rate_code;      //!< specify the frame rate code for AES-302M audio streams, 0 = use detected value from video stream
                                      /*!< @details If a video stream is not being muxed, or the Muxer cannot determine a frame rate value
                                      for the video stream a value must be specified in this field. One of the FRAMERATE_ defines in
                                      \ref mcdefs.h.*/
    int32_t au_queue_size;            //!< specify the parsed access unit queue size, 0 = automatically computed
                                      /*!< @details If the stream will have many small access units it may be necessary to increase this value (start at a
                                         value of 1000 and increase from that as needed).*/
    int32_t overflow_timeout;         //!< specify how long an input stream will block when overflowing waiting for data from other streams
                                      /*!< @details -1 = do not block, return an error, 0 = use computed value, else the number of seconds to wait*/

    uint8_t stream_type;              //!< the stream_type that is placed in the PMT or PSM, 0 = use computed value

    uint8_t wrap_field_in_pes;        //!< set to 1 to have each video field placed in its own PES packet, 0 = entire video frame is placed in a pes packet
                                      /*!< @details only AVC streams are currently supported, not used if the align_in_flag setting is enabled*/

	uint8_t dd_mainid;                //!< mainid value placed in the Dolby Digital or Dolby Digital Plus audio descriptors
                                      /*!< @details Only used with Dolby Digital audio streams. If multiple DD main service audio streams are
									     present in a program each should be given a unique value (0..7). If this stream is an associated audio stream
										 (flags field contains STREAM_FLAG_ASSOCIATED_AUDIO), then this field is used to specify the mainid of the
										 main service audio stream this stream is associated with.
									  */

    uint8_t reserved[41];             //!< Reserved for future use
};


//! @brief available service types according to ATSC Table 6.7 a_65b for \ref mp2mux_ts_program_set_struct.atsc_service_type
typedef enum atsc_service_type_enum
{
    atsc_service_type_reserved0 = 0,
    atsc_service_type_analog_television = 1,
    atsc_service_type_digital_television = 2,
    atsc_service_type_audio = 3,
    atsc_service_type_data_only_service = 4,
    atsc_service_type_reserved

} atsc_service_type_enum_t;

//! @brief available modulation modes according to ATSC Table 6.5 a_65b for \ref mp2mux_ts_program_set_struct.atsc_modulation_mode
typedef enum atsc_modulation_mode_enum
{
    atsc_modulation_mode_reserved0 = 0,
    atsc_modulation_mode_analog = 1,
    atsc_modulation_mode_SCTE_1 = 2,
    atsc_modulation_mode_SCTE_2 = 3,
    atsc_modulation_mode_ATSC_8VSB = 4,
    atsc_modulation_mode_ATSC_16VSB = 5,
    atsc_modulation_mode_reserved

} atsc_modulation_mode_enum_t;

//! @brief describe Multi-Program Transport Stream
//! @details The mp2mux_ts_program_set_struct structure is used for Transport Stream profiles only. Use it
//! with mpegOutMP2MuxAddProgram function to multiplex Multi-Program Transport Stream.
struct mp2mux_ts_program_set_struct
{
    int32_t PCR_PID;                  //!< specifies the transport stream PID which carries the PCR timestamps for the program
                                      /*!< @details This field specifies the transport stream PID which carries the PCR timestamps for the program. Only
                                      the PIDs of streams which belong to the program are allowed. Set to 0 to have the Muxer compute a
                                      value.*/
    int32_t independent_PCR_PID;      //!< use to share a PCR PID between programs
                                      /*!< @details This parameter makes it possible to share a PCR PID between programs in
                                      Multi-Program Transport Stream. In addition to specifying the PID of a stream belonging
                                      to this program, this field can also be used to specify a PID from a stream in other
                                      programs in the multiplex, or any desired user-defined PID which is dedicated to carry the PCR.
                                      The independent_PCR_PID_flag field must be set to 1 for this field to be used.

                                      Valid range is 1 .. 65535, but not PIDs used for SI tables.
                                      */
    int32_t independent_PCR_PID_flag; //!< '1' indicates the field \ref independent_PCR_PID is valid
    int32_t program_number;           //!< specifies the program_number as defined in ISO 13818-1, 2.4.4.5
                                      /*!< @details This field specifies the program_number of this program as defined in ISO 13818-1,
                                           2.4.4.5. Set to 0 to have the Muxer compute a value.*/
    int32_t program_PID;              //!< specifies the PID of the Program Map Table (PMT) for this program
                                      /*!< @details This field specifies the PID of the Program Map Table (PMT) for this program
                                      in the Transport Stream. Set to 0 to have the Muxer compute a value.*/
    uint16_t atsc_source_id;          //!< specify the ATSC programming source associated with the virtual channel
                                      /*!< @details
                                      This field can be used to specify the ATSC programming source associated with the virtual channel. In
                                      this context, a source is one specific source of video, text, data, or audio programming. Source ID
                                      value zero is reserved. Source ID values in the range 0x0001 to 0x0FFF shall be unique within the
                                      Transport Stream that carries the VCT, while values 0x1000 to 0xFFFF shall be unique at the regional
                                      level. Values for source_ids 0x1000 and above shall be issued and administered by a Registration
                                      Authority designated by the ATSC.*/
    uint8_t atsc_major_channel;       //!< specify the ATSC major channel for this program
                                      /*!< @details
                                      Use this field to specify the ATSC major channel for this program. The valid range is 0 .. 99, if 0 is
                                      used a default value of 1 will be used.*/
    uint8_t atsc_minor_channel;       //!< specify the ATSC minor channel for this program
                                      /*!< @details
                                      Use this field to specify the ATSC minor channel for this program. The valid range is 0 .. 99, if 0 is
                                      used a default value of 1 will be used.*/
    uint8_t atsc_service_type;        //!< specify the ATSC service type for this program, use \ref atsc_service_type_enum_t values to assign this parameter
    uint8_t atsc_modulation_mode;     //!< specify the ATSC modulation mode for this program use the \ref atsc_modulation_mode_enum_t values to assign this parameter


    uint8_t DVB_num_of_extra_EITs;    //!< Number of extra DVB 'actual TS, event schedule information' EIT tables to be added
                                      /*!< @details Number of actual TS, event schedule information EIT tables (table_id's 0x50-0x5F) to add
                                      to the mux for this program. The maximum value is 16, larger values will be clamped to 16. Note that the
                                      'actual TS, present/following event information' table (table_id 0x4E) is automatically added to the mux.*/

    uint8_t reserved5[57];            //!< Reserved for future use
};

//! @brief provide additional Muxer settings to the Muxer
//! @details structure is used to provide additional Muxer settings to the Muxer
//! when calling the ::mpegOutMP2MuxInitStream or ::mpegOutMP2MuxInitFile functions.
struct mp2mux_ext_set_struct
{
    uint32_t flags;                   //!< flags, one or more of the EXT_FLAG_ defines

    int32_t NIT_PID;                  //!< network information section PID
                                      /*!< @details This field specifies the network information section
                                          PID, set to 0 to have the Muxer compute a value. The value is
                                          assigned accordingly to the mp2muxer_set_struct.mplex_type */
    int32_t SDT_PID;                  //!< service description section PID
                                      /*!< @details This field specifies the service description section
                                          PID, set to 0 to have the Muxer compute a value. The value is
                                          assigned accordingly to the mp2muxer_set_struct.mplex_type */
    int32_t EIT_PID;                  //!< event information section PID
                                      /*!< @details This field specifies the event information section
                                          PID, set to 0 to have the Muxer compute a value. The value is
                                          assigned accordingly to the mp2muxer_set_struct.mplex_type */
    int32_t TDT_PID;                  //!< time and date section PID
                                      /*!< @details This field specifies the time and date section
                                          PID, set to 0 to have the Muxer compute a value. The value is
                                          assigned accordingly to the mp2muxer_set_struct.mplex_type */

    int32_t PSI_LIMIT;                //!< time (in ms) before the PAT and other tables are repeated
                                      /*!< @details This field specifies the maximum time interval (in ms)
                                      before the PSI other tables are repeated. Set to  0 to have the
                                      multiplexer compute a value. The specified value can be overwritten
                                      with the internally assigned value for the output profiles which
                                      have strict limitations of PSI repetition rate. */
    int32_t PCR_LIMIT;                //!< upper limit (in ms) of the PCR repeat rate
                                      /*!< @details This field specifies the maximum time interval
                                      (in ms) before a new PCR is written. Set to 0 to have the
                                      multiplexer compute a value. The specified value can be overwritten
                                       with the internally assigned value for the output profiles which
                                       have strict limitations of PCR repetition rate.*/

    int32_t network_id;               //!< transport stream network id
                                      /*!< @details This field specifies the transport stream network id,
                                      if set to 0 the Muxer will compute a value. It corresponds to the
                                      network_ID field in the Network Information Table (NIT).*/
    int32_t transport_id;             //!< transport stream id.
                                      /*!< @details  This field specifies the transport stream id, if set
                                      to 0 the Muxer will compute a value. It corresponds to the
                                      transport_stream_id field in the Program Association Table (PAT),
                                      being simply a number to identify the transport stream. Some formats
                                      may call for a specific value.*/
    struct dash_vr_settings *dvr_set; //!< DVD-VR settings
                                      /*!< @details This field contains an optional pointer to a \ref dash_vr_settings
                                      structure and is only used for DVD-VR multiplexing.*/

    uint16_t atsc_num_of_extra_EITs;  //!< Number of EXTRA EIT tables to be used
                                      /*!< @details Number of EXTRA EIT tables to be used (in addition to
                                      default 4 tables automatically generated by the multiplexer). The maximum value
                                      is 124 (128 - 4), a larger value will be clamped to 124. The PIDs of these EITs
                                      are derived as:
                                      @f[ EIT_PID + 4 + 1, EIT_PID + 4 + 2, ..., EIT_PID + 4 + atsc_num_of_extra_EITs @f]*/

    uint8_t reserved[38];             //!< Reserved for future use
};

//! @brief The multiplexer uses the \ref mp2muxer_set_struct structure to hold its settings
struct mp2muxer_set_struct
{
    int32_t mplex_type;              //!< type of program stream, one of the MPEG_ defines in \ref mcdefs.h
    int64_t sectors_delay;           //!< @brief time stamp of first MPEG pack in ms
                                     //!< @details specifies the starting value of the SCR/PCR in milliseconds, the default value is 0 meaning compute a value.
    int64_t video_delay_ms;          //!< @brief Depreciated, use the mp2mux_stream_set_struct.delay_ms instead.
                                     //!< @details time stamp of first video packet for all video streams, 0 = automatically computed
    int64_t audio_delay_ms;          //!< @brief Depreciated, use the mp2mux_stream_set_struct.delay_ms instead.
                                     //!< @details time stamp of first audio packet for all audio streams, 0 = automatically computed

    int32_t sector_size;             //!< @brief size of the output packets
                                     /*!< @details This field specifies the size in bytes of program stream packs or
                                          transport stream packets. For program streams, this size includes the PES packet,
                                          a PS pack header and any system headers.

                                          For transport streams the default value is 188 or 192 depending on the profile.
                                          For VCD, SVCD and DVD profiles, the default value is non-zero, for other program
                                          streams the default value is 0, meaning each access unit is wrapped in one or
                                          more PES packets depending on the size of the access unit. */
    int32_t packets_per_pack;        //!< depreciated, not used
    int32_t extra_padding_packs;     //!< @brief extra padding packets per second, TS only
                                     /*!< @details This field specifies the number of extra padding packets per second
                                          to add to a transport stream. The default value is 0.*/
    int32_t user_mux_rate_bps;       //!< @brief force a particular mux rate (in bps)
                                     /*!< @details This field specifies the required bitrate of the output multiplexed
                                          stream (in bits per second units). If this field is 0, the mux rate is
                                          determined depending on the bitrate values of the input streams. For some
                                          profiles the defaults for this field will have a value, for other profiles
                                          it will be 0.*/
    int32_t vcd_audio_pad;           //!< pad each vcd audio sector with 20 zeros
                                     /*!< @details     This field specifies whether VCD audio sectors are zero padded
                                          to 2324 bytes or left at 2304 bytes. Some VCD authoring software
                                          expects the padding to be present and some do not. If an authoring
                                          program does not accept files made with this option enabled, disable it and
                                          they should be accepted.
                                          <dl><dt> 0 </dt>  <dd>do not pad VCD audio sectors</dd></dl>
                                          <dl><dt> 1 </dt>  <dd>pad VCD audio sectors (default in the VCD profile)</dd></dl>*/
    int32_t align_sequence_headers;  //!< depreciated, not used
    int32_t put_private2;            //!< @brief put DVD private stream 2's instead of padding packets
                                     /*!< @details This field specifies whether the DVD navigation packs contain the
                                          DVD PCI and DSI information or whether they contain 2 padding packets.
                                          This field should be set to 1 for DVD compliant muxing, it is ignored when 
										  muxing MPEG-2 transport streams.
                                          <dl><dt> 0 </dt>  <dd>use padding packets (default in all non-DVD profiles)</dd></dl>
                                          <dl><dt> 1 </dt>  <dd>private 2 packets (default for the DVD profiles)</dd></dl>*/
    int32_t frame_timestamps;        //!< @brief which frames to be timestamped
                                     /*!< @details This field specifies which frames will have PTS/DTS timestamps.

                                          - \ref TIMESTAMPS_ALL (default for non-DVD profiles)
                                          - \ref TIMESTAMPS_IPONLY
                                          - \ref TIMESTAMPS_IONLY(default for DVD profiles)*/
    int32_t VBR_multiplex;           //!< @brief do VBR style multiplexing (enable / disable padding in both TS / PS)
                                     /*!< @details This field specifies whether the multiplexer operates in variable
                                          or constant mux rate mode. This parameter enables or disables the generation
                                          of 0x1FFF padding packets for TS and 0xBE padding packets for PS. In constant
                                          mux rate mode, padding packets are generated (if needed) to keep the mux rate
                                          constant, in variable mux rate mode no padding packets are generated.
                                          <dl><dt> 0 </dt>  <dd>constant mux rate</dd></dl>
                                          <dl><dt> 1 </dt>  <dd>variable mux rate</dd></dl>
                                          The default value is 0 for all profiles except for the SVCD, DVD,
                                          AVCHD and Blu-Ray profiles.

                                          @note Disabling of padding can affect the STD modelling by receiver.
                                          The streams generated in VBR mode will probably fail the STD verification
                                          procedure.*/

    int32_t mux_SVCD_scan_offsets;   //!< compute SVCD scan offsets
    int32_t max_file_size;           //!< @brief split the output every so many MB
                                     //!< @details Default is 0 in all profiles.
    uint32_t feature_flags;          //!< @brief one or more of the MUX_FEATURE_* defines
                                     //!< @details The bit mask of several feature flags
    int32_t reset_clocks;            //!< currently not implemented
    int32_t write_pec;               //!< @brief  write a program end code
                                     /*!< @details This field specifies whether a program end code is written
                                          at the end of the program stream. This field is ignored when muxing
                                          MPEG-2 transport streams.
                                          <dl><dt> 0 </dt>  <dd>do not write program end code (default in DVD and TS profiles)</dd></dl>
                                          <dl><dt> 1 </dt>  <dd>write program end code (default in all non DVD PS profiles)</dd></dl>
                                          */
    int32_t write_end_codes;         //!< currently not implemented
    int32_t set_broken_link;         //!< currently not implemented

    uint8_t ts_write_PSI_only_once;  //!< @brief Write the PSI (PAT, PMT, etc) only once in the beginning of the stream
                                     /*!< @details Set to "1" to force the multiplexer write PAT / PMT only once
                                          at the beginning of the stream. This option allows to save output bandwidth.
                                          Default is 0 in all profiles.*/
    uint8_t ts_set_disc_indicator;   //!< @brief Set the 'discontinuity_indicator' of the first TS packet to 1
                                     /*!< @details Sets discontinuity_indicator flag at the first TS packet of the generated stream.
                                          Valid for TS profiles only. Default is 0 in all profiles.*/
    uint8_t deny_missing_streams;    //!< @brief deny muxing if some input receives no data
                                     /*!< @details  do not allow muxing of data when the input buffer is full. This can be
                                          done if only EOS received in case if deny_missing_stream = 1

                                          Sets discontinuity_indicator flag at the first TS packet of the generated stream. Valid for TS profiles
                                          only. Default is 0 in all profiles.
                                          */

    uint32_t ts_discon_threshold;    /*!< @brief generate a discontinuity if the PCR/DTS difference for all streams is
                                         larger than this value (in ms).
                                         @details  Use this field to have the Muxer detect time discontinuities in the
                                         input streams. A discontinuity is created if the PCR/DTS difference for all
                                         streams is larger than this value (in ms). The default is 0 in all
                                         profiles meaning discontinuity checking is disabled. Otherwise the
                                         value must be > 10s (10000).*/

    uint32_t initial_delay;          //!< @brief the initial delay (in ms) between the first PCR/SCR and the lowest DTS/PTS
                                     //!< @brief default is 0 meaning the Muxer computes a value

    uint8_t ignore_std;              //!< @brief do not use P-STD or T-STD model
                                     /*!< @details Default is 0 in all profiles.
                                     @note Disabling the STD will affect the STD modelling by receiver. The streams
                                     generated in this mode will probably fail the STD verification procedure.
                                     */

    uint32_t max_file_duration;      //!< @brief split the output every so many seconds
                                     //!< @details Default is 0 in all profiles.

    uint8_t reserved[112];           //!< Reserved for future use
};

//! Flag indicates the mux rate information is provided
#define MP2MUX_RT_FLAG_BITRATE       0x00000001
//! @brief describes mux rate
struct mp2mux_rt_set
{
    int32_t user_mux_rate_bps;       //!< force a particular mux rate (in bps)
    int32_t VBR_multiplex;           //!< do VBR style multiplexing (enable / disable padding in both TS / PS)

    uint8_t reserved[64];            //!< Reserved for future use
};

#pragma pack(pop)


#ifdef __cplusplus
extern "C" {
#endif

//! Call this function to fill a \ref mp2muxer_set_struct structure with defaults values
//! based on one of the SDK profile ID's
//!
//! @param[in,out] set         pointer to a \ref mp2muxer_set_struct structure
//! @param[in]     profileID   one of the MCPROFILE_* or MPEG_* constants
//!
//! @return pointer to a profile string or NULL

char* MC_EXPORT_API mpegOutMP2MuxDefaults(struct mp2muxer_set_struct *set, int32_t profileID);


//! Call to create a MPEG Muxer object
//! the Ex version uses the get_rc_ex callbacks
//!
//! @param[in]      get_rc     pointer to a get resource function
//! @param[in]      set        pointer to a filled in \ref mp2muxer_set_struct structure
//! @return  pointer to a \ref mp2muxer_tt object if successful,\n
//!    NULL if unsuccessful
//!@{
mp2muxer_tt* MC_EXPORT_API mpegOutMP2MuxNew(void *(MC_EXPORT_API *get_rc)(const char* name), const struct mp2muxer_set_struct *set);
mp2muxer_tt* MC_EXPORT_API mpegOutMP2MuxNewEx(void *(MC_EXPORT_API *get_rc_ex)(void *rc_app_ptr, const char* name), void *rc_app_ptr, const struct mp2muxer_set_struct *set);
//!@}

//! Call to initialize the Muxer for a streaming mode muxing session,
//! the audio/video data comes from audio and video bufstream
//! objects passed to ::mpegOutMP2MuxAddStream. Must be called before
//! any ::mpegOutMP2MuxAddStream calls.
//!
//! An existing bufstream
//! object must be passed to this function for the muxed output. The multiplexer is called to do the
//! multiplexing through the methods of the audio and video bufstream objects.
//!
//! @param[in]      muxer      pointer to a MPEG Muxer object
//! @param[in]      ext_set    pointer to a \ref mp2mux_ext_set_struct structure, can be NULL
//! @param[in]      output     pointer to a \ref bufstream_tt object for the output muxed data
//! @return MUX_OK if successful \n
//! MUX_ERR if unsuccessful

int32_t MC_EXPORT_API  mpegOutMP2MuxInitStream(mp2muxer_tt *muxer, struct mp2mux_ext_set_struct *ext_set, bufstream_tt *output);


//! Call to add a video, audio or subpicture stream to the Muxer in streaming mode,
//!
//! @param[in]     muxer      pointer to a MPEG Muxer object
//! @param[in]     set        pointer to a \ref mp2mux_stream_set_struct structure
//! @param[in]     input      pointer to a \ref bufstream_tt object for the input data
//! @return    MUX_OK if successful \n
//!    MUX_ERR if unsuccessful

int32_t MC_EXPORT_API mpegOutMP2MuxAddStream(mp2muxer_tt *muxer, struct mp2mux_stream_set_struct *set, bufstream_tt *input);


//! Call to initialize the Muxer for a file mode muxing session,
//! the audio/video data comes from files added via ::mpegOutMuxAddFile
//! Must be called before any ::mpegOutMP2MuxAddFile calls.
//!
//! The flags field in the stream_settings parameter
//! must contain one of the STREAM_FLAG_ defines that specifies the type (video, audio or subpicture)
//! of the stream.
//!
//! @param[in]     muxer      pointer to a MPEG Muxer object
//! @param[in]     ext_set    pointer to a \ref mp2mux_ext_set_struct structure, can be NULL
//! @param[in]     output     pointer to an output file name or bufstream for the output muxed data (BS version)
//! @return    MUX_OK if successful \n
//!    MUX_ERR if unsuccessful
//!@{
int32_t MC_EXPORT_API mpegOutMP2MuxInitFile(mp2muxer_tt *muxer, struct mp2mux_ext_set_struct *ext_set, char *output);
int32_t MC_EXPORT_API mpegOutMP2MuxInitFileBS(mp2muxer_tt *muxer, struct mp2mux_ext_set_struct *ext_set, bufstream_tt *output);
//!@}

//! Call to add a video, audio or subpicture stream to the Muxer in file mode,
//!
//! @param[in]     muxer      pointer to a MPEG Muxer object
//! @param[in]     set        pointer to a mp2mux_stream_set_struct structure
//! @param[in] input     input      pointer to a file name for the input data
//! @param[in] input1    input bufstreams, same file opened twice
//! @param[in] input2    input bufstreams, same file opened twice
//! @param[in] video_bitrate  bitrate (in bits/sec) of the video stream, only needed for MPEG-1 VBR or H264 video
//!                    also used for AAC audio streams!
//!
//! @return    MUX_OK if successful \n
//!    MUX_ERR if unsuccessful
//!@{
int32_t MC_EXPORT_API mpegOutMP2MuxAddFile(mp2muxer_tt *muxer, struct mp2mux_stream_set_struct *set, char *input, int32_t video_bitrate);
int32_t MC_EXPORT_API mpegOutMP2MuxAddFileBS(mp2muxer_tt *muxer, struct mp2mux_stream_set_struct *set, bufstream_tt *input1, bufstream_tt *input2, int32_t video_bitrate);
//!@}


//! Call to do the multiplexing in file mode, call will not
//! return until muxing is complete. Same effect as calling
//! mpegOutMP2MuxRun in file mode
//!
//! @param[in]  muxer   pointer to a MPEG Muxer object
//!
//! @return     MUX_OK if successful \n
//!    MUX_ERR if unsuccessful

int32_t MC_EXPORT_API mpegOutMP2Mux(mp2muxer_tt *muxer);


//! Call to finish a muxing session, set abort non-zero if muxing is being aborted.
//!
//! @param[in]    muxer  pointer to a MPEG Muxer object
//! @param[in]    abort  set to 0 to finish any leftover muxing and clean up,
//!            else just clean up
//!
//!  @return    MUX_OK if successful \n
//!    MUX_ERR if unsuccessful

int32_t MC_EXPORT_API mpegOutMP2MuxDone(mp2muxer_tt *muxer, int32_t abort);


//! Call to free a MPEG Muxer object
//!
//! @param[in]    muxer  muxer object to free
//!
//! @return    none

void MC_EXPORT_API mpegOutMP2MuxFree(mp2muxer_tt *muxer);


/*!Call this function to check whether the multiplexer settings are valid. The general MPEG compliance
checks are done first and then the Format checks are done (if the MPEG type is one of those types).
Use the CHECK_MPEG_ONLY flag in the options parameter to turn off the Format compliance checks
(only do the general MPEG compliance checks). If the mplex_type field is set to MPEG_NONE, this
function will return MUX_OK.

If the get_rc parameter is non-NULL, any error messages are sent to the err_printf function.

If the options parameter does not contain CHECK_ALL, the function returns when the first non-compliant
value is found (the remainder of the settings are not checked). If the options parameter does
contain CHECK_ALL, all the checks are performed, an error message is sent to the err_printf callback
for every error found and the error code of the first error found is returned.

The Format conformance checks will return an error code less than INV_MPEG_ERROR and can be
ignored if desired. The settings may not produce a valid Format stream, but they will still produce a
valid MPEG stream and the Muxer will accept them. This can be useful for producing non-standard
Format streams.

There is also a mpegOutMP2MuxChkSettingEx function that does the same as this function but
uses a get_rc_ex callback instead of get_rc.
*/
//!
//!  @param[in]   get_rc  pointer to a get_rc function
//!  @param[in]   set  pointer to a \ref mp2muxer_set_struct structure
//!  @param[in]  options  check options, one or more of the CHECK_* defines in \ref mcdefs.h
//!  @param[in]  app  reserved
//!
//!  @return    MUX_OK if no errors found \n
//!    one of the INV_* error codes if an error is found
//!@{
int32_t MC_EXPORT_API mpegOutMP2MuxChkSettings(void *(MC_EXPORT_API *get_rc)(const char* name), const struct mp2muxer_set_struct *set, uint32_t options, void *app);
int32_t MC_EXPORT_API mpegOutMP2MuxChkSettingsEx(void *(MC_EXPORT_API *get_rc_ex)(void *rc_app_ptr, const char* name), void *rc_app_ptr, const struct mp2muxer_set_struct *set, uint32_t options, void *app);
//!@}

//! Call to send messages to the Muxer
//!
//! Currently these messages and usages are defined in auxinfo.h
//!
//! Call to send messages to the Muxer. Currently these messages and usages are defined in \ref auxinfo.h:
//! <table><tr><th>Offs</th><th>info_ID</th><th>info_ptr</th><th>info_size</th></tr>
//! <tr><td>0</td><td>DVD_SETUP_VOBIDN</td><td>\ref dvd_vobidn_info</td><td>sizeof(\ref dvd_vobidn_info)</td></tr>
//! <tr><td>new cell #</td><td>DVD_SETUP_CELLIDN</td><td>NULL</td><td>0</td></tr>
//! <tr><td>0</td><td>DVD_SET_HLI_INFO</td><td>HLI_PTR</td><td>sizeof(HLI_PTR)</td></tr>
//! <tr><td>0</td><td>SPLIT_OUTPUT</td><td>NULL</td><td>0</td></tr></table>
//! \c DVD_SETUP_VOBIDN changes the VOB IDN value at the next I frame. DVD muxing only. \n
//! \c DVD_SETUP_CELLIDN changes the cell number at the next I frame. DVD muxing only. \n
//! \c DVD_SET_HLI_INFO is used to have the Muxer place DVD HLI data in the NAV packets. DVD muxing only. \n
//! \c SPLIT_OUTPUT tells the Muxer to split the output file at the next I frame. The Muxer will then send
//! this message to the bufstream at the appropriate time
//!
//!  @param[in]   muxer      pointer to a MPEG Muxer object
//!  @param[in]   offs       value is dependent on the message
//!  @param[in]   info_ID    the message to process
//!  @param[in]   info_ptr   pointer, dependent on the message
//!  @param[in]   info_size  size of the structure pointed to by info_ptr
//!
//!  return    BS_OK or BS_ERROR

int32_t MC_EXPORT_API mpegOutMP2MuxAuxinfo(mp2muxer_tt *muxer, int32_t offs, int32_t info_ID, void *info_ptr, int32_t info_size);

//! Call to create a new TS program
//!
//!  @param[in]    muxer         pointer to a MPEG Muxer object
//!  @param[in]    program_set   pointer to the program's settings structure
//!  @return    MUX_OK if all is OK \n
//!    MUX_ERR if any error occurred

int32_t MC_EXPORT_API mpegOutMP2MuxAddProgram(mp2muxer_tt *muxer, struct mp2mux_ts_program_set_struct *program_set);


//! Call to load a descriptor into a SI entry or section
//!
//!  @param[in]    muxer  pointer to a MPEG Muxer object
//!  @param[in]    descriptor  pointer to the descriptor structure with all necessary info
//!  return    MUX_OK if success\n MUX_ERR otherwise

int32_t MC_EXPORT_API mpegOutMP2MuxLoadDescriptor(mp2muxer_tt* muxer, const struct si_descriptor_struct* descriptor);


//! Call to load an Entry into a SI section
//!
//!  @param[in]    muxer  pointer to a MPEG Muxer object
//!  @param[in]    entry  pointer to the entry structure with all necessary info
//!  @return    MUX_OK if success \n
//!  MUX_ERR otherwise

int32_t MC_EXPORT_API mpegOutMP2MuxLoadEntry(mp2muxer_tt* muxer, const struct si_entry_struct* entry);


//! Call to load a complete SI section
//!
//!  @param[in]    muxer  pointer to a MPEG Muxer object
//!  @param[in]    section  pointer to the section structure with all necessary info
//!  @return    MUX_OK if success \n
//!  MUX_ERR otherwise

int32_t MC_EXPORT_API mpegOutMP2MuxLoadSection(mp2muxer_tt* muxer, const struct si_section_struct* section);


//! Call to commit loading of the descriptors / entries / sections set
//!
//!  @param[in]    muxer  pointer to a MPEG Muxer object
//!  @param[in]    commit_struct  pointer to the si_commit_struct with timing parameters declaring the moment of the new PSI info applying
//!                    If target_time_PCR == -1, then parameters are applied immediately
//!  @return    MUX_OK if success \n
//! MUX_ERR otherwise

int32_t MC_EXPORT_API mpegOutMP2MuxCommitPSI(mp2muxer_tt* muxer, const struct si_commit_struct* commit_struct);


//! Call to add an SI table
//!
//!  @param[in]    muxer  pointer to a MPEG Muxer object
//!  @param[in]    table  pointer to the table structure with all necessary info
//!  @return    MUX_OK if success \n
//!  MUX_ERR otherwise

int32_t MC_EXPORT_API mpegOutMP2MuxAddTable(mp2muxer_tt* muxer, const struct si_table_struct* table);


//! Call to start muxing, if file mode the call will not return until muxing is complete
//! in streaming mode, the muxing thread is started if enabled
//!
//!  @param[in]   muxer  pointer to a MPEG Muxer object
//!  @return    MUX_OK if success \n
//!  MUX_ERR otherwise

int32_t MC_EXPORT_API mpegOutMP2MuxRun(mp2muxer_tt *muxer);


//! Call to fill a \ref mp2mux_ext_set_struct structure with defaults values
//! based on one of the SDK profile ID's
//!
//!  @param[in,out]      set  pointer to a \ref mp2mux_ext_set_struct structure to be modified
//!  @param[in]      profileID one of the MC profiles as defined in \ref mcprofiles.h
//!  @return    pointer to a profile string or NULL

char* MC_EXPORT_API mpegOutMP2MuxDefaultsExt(struct mp2mux_ext_set_struct *set, int32_t profileID);


//! Call to check whether the given stream is allowed for multiplexing into the specific profile
//! the Ex version uses the get_rc_ex callbacks
//!
//!  @param[in]     get_rc  pointer to a get_rc function
//!  @param[in]     pFormat  pointer to a mc_stream_format_t structure
//!  @param[in]     mplex_type one of the MPEG_xxx defines in \ref mcdefs.h
//!  @param[in]     pExt  reserved
//!  @return    MUX_OK if success \n
//!  MUX_ERR otherwise
//!@{
int32_t MC_EXPORT_API mpegOutMP2MuxCheckConnect(void *(MC_EXPORT_API *get_rc)(const char* name), mc_stream_format_t *pFormat, int32_t mplex_type, void* pExt);
int32_t MC_EXPORT_API mpegOutMP2MuxCheckConnectEx(void *(MC_EXPORT_API *get_rc_ex)(void *rc_app_ptr, const char* name), void *rc_app_ptr, mc_stream_format_t *pFormat, int32_t mplex_type, void* pExt);
//!@}

//! Call to change the parameters "on-the-fly"
//!
//!  @param[in]        muxer  pointer to a MPEG Muxer object
//!  @param[in]        set  pointer to a mp2mux_rt_set structure
//!  @param[in]        option_flags  one or more of the MP2MUX_RT_FLAG_xxx flags
//!  @return    MUX_OK if success \n
//!   MUX_ERR otherwise

int32_t MC_EXPORT_API mpegOutMP2MuxRuntimeConfig(mp2muxer_tt *muxer, const struct mp2mux_rt_set* set, const uint32_t option_flags);


//! Call to get extended API function
//!
//! @param[in]  func  function ID
//! @return    function pointer or NULL

APIEXTFUNC MC_EXPORT_API mpegOutMP2MuxGetAPIExt(uint32_t func);

#ifdef __cplusplus
}
#endif



//! @name depreciated items
//!@{
#define MAX_VIDEO_STREAMS   8
#define MAX_AUDIO_STREAMS   8
#define MAX_SUBPIC_STREAMS 32
//!@}

#endif // #if !defined (__MUX_MP2_API_INCLUDED__)

