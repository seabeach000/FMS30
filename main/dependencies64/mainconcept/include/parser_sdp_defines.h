/**
@file  parser_sdp_defines.h
@brief Macros and typedefs for SDP Parser

@verbatim
File: parser_sdp_defines.h
Desc: Macros and typedefs for SDP Parser

Copyright (c) 2015 MainConcept GmbH or its affiliates.  All rights reserved.

MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.  
This software is protected by copyright law and international treaties.  Unauthorized 
reproduction or distribution of any portion is prohibited by law.
@endverbatim
**/

#if !defined (__MC_PARSER_SDP_DEFINES_H__)
#define __MC_PARSER_SDP_DEFINES_H__

#include "net_common.h"
/**
* namespace MainConcept
* @brief Global SDK namespace
**/
namespace MainConcept {

    /**
    * namespace NetworkStreaming
    * @brief Network streaming specific namespace
    **/
    namespace NetworkStreaming {

        /**
        * @brief Predefined media payload type
        **/
        typedef enum _tagStreamType {

            isPCMU                 = 0,                             /**< PCMU */
            // 1-2 RESERVED                                         
            isGSM                  = 3,                             /**< GSM */
            isG723                 = 4,                             /**< G.723 */
            isDVI4                 = 5,                             /**< DVI4 */
            isDVI4_16Khz           = 6,                             /**< DVI4 16 KHz */
            isLPC                  = 7,                             /**< LPC */
            isPCMA                 = 8,                             /**< PCMA */
            isG722                 = 9,                             /**< G.722 */
            isL16                  = 10,                            /**< L16 */
            isL16_Mono             = 11,                            /**< L16 Mono */
            isQCELP                = 12,                            /**< QCELP */
            isCN                   = 13,                            /**< CN */
            isMPEG1_2_Audio        = 14,                            /**< MPEG Audio, MPEG2 Audio */
            isG728                 = 15,                            /**< G.728 */
            isDVI4_11Khz           = 16,                            /**< DVI4 11KHz */
            isDVI4_22Khz           = 17,                            /**< DVI4 22KHz */
            isG729                 = 18,                            /**< G.729 */
            // 19 RESERVED                                          
            // 20-24 UNASSIGNED                                     
            isCELB                 = 25,                            /**< CELB */
            isJPEG                 = 26,                            /**< JPEG */
            // 27 UNASSIGNED                                         
            isNV                   = 28,                            /**< NV */
            // 29-30 UNASSIGNED                                   
            isH261                 = 31,                            /**< H.261 */
            isMPEG1_2_Video        = 32,                            /**< MPEG Video, MPEG2 Video */
            isMPEG2TransportStream = 33,                            /**< MPEG2 Transport Stream */
            isH263                 = 34,                            /**< H.263 */
            // 35-71 UNASSIGNED                                 
            // 72-76 RESERVED                                   
            // 77-95 UNASSIGNED                                 
            // 96-127 DYNAMIC                                   
            isH264                 = 96,                            /**< H.264 */
            isH264_SVC             = 97,                            /**< H.264 Scalable Video Coding */
            isH264_MVC             = 98,                            /**< H.264 Multiview Video Coding */
            isAAC                  = 99,                            /**< Advanced Audio Codec */
            isLATM                 = 100,                           /**< LATM */
            isTelephoneEvent       = 101,                           /**< Telephone Event */
            isMPEG1SystemStream    = 102,                           /**< MPEG1 System stream */
            isMPEG2ProgramStream   = 103,                           /**< MPEG1 Program stream */
            isOGG                  = 104,                           /**< OGG */
            isVC1                  = 105,                           /**< VC1 */
            isMPEG4                = 106,                           /**< MPEG4 */
            isAMR                  = 107,                           /**< AMR */
            isAMR_WB               = 108,                           /**< AMR WB */
            isSpeex                = 109,                           /**< SPEEX */
            isL8                   = 110,                           /**< L8 */
            isILBC                 = 111,                           /**< ILBC */
            isAC3                  = 112,                           /**< AC3 */
            isJ2K                  = 113,                           /**< J2K */
            isMP3                  = 114,                           /**< MP3 */
            isH263_1998            = 115,                           /**< H.263 1998 */
            isH263_2000            = 116,                           /**< H.263 2000 */
            isWMA                  = 117,                           /**< Windows Media Audio */
            isWMV                  = 118,                           /**< Windows Media Video */
            isASF                  = 119,                           /**< Advanced Streaming Format */
            isAVI                  = 120,                           /**< AVI */
            isMKV                  = 121,                           /**< MKV */
            isMP4                  = 122,                           /**< MP4 */
            isFLV                  = 123,                           /**< Flash Video */
            isQT                   = 124,                           /**< QuickTime */
            isHEVC                 = 125,                           /**< HEVC/H265 */
            isRAWdata              = 127,                           /**< RAW data, user content */
            isT140                 = 128,                           /**< T.140, text over IP */
            isVP6                  = 129,                           /**< VP6 */
            isFSV1                 = 130,                           /**< Flash Screen Video */
            isFSV2                 = 131,                           /**< Flash Screen Video v2*/
            isNellymoser           = 132,
            isUNKNOWN              = 0xff                           /**< Stub type */
        } STREAMTYPE;

        /**
        * @brief RTP transport profile type
        **/
        typedef enum _tagNetProfileType {

            ProfileAVP,                                             /**< A/V Profile */
            ProfileH2221,                                           /**< H.222.1 Profile (MPEG over ATM), @see ITU-T H.222.1 */
            ProfileRAW,                                             /**< RAW data */
            ProfileDVBC,                                            /**< DVB-C Profile (DVB over cable), @see "Digital Video Broadcasting: 
                                                                        Framing Structure, Channel Coding and 
                                                                        Modulation ForCable Systems", EN 300 429
                                                                    **/
            NetProfileUndefined = 0xffff                            /**< Undefined profile */
        } NETPROFILETYPE;

        /**
        * @brief RTP lower transport
        **/
        typedef enum _tagLowerTransportType {

            isUDP,                                                  /**< RTP over UDP */
            isTCP,                                                  /**< RTP over TCP */
            isAAL5_PVC,                                             /**< MP2T over AAL5-PVC */
            isAAL5_SVC,                                             /**< MP2T over AAL5-SVC    */
            isASI,                                                  /**< MP2T over ASI */
            isQAM,                                                  /**< MP2T over QAM */
            isLowerTransportUndefined = 0xffff                      /**< Lower transport is not defined */
        } LOWERTRANSPORTTYPE;

        /**
        * @brief Describes transport parameter mode
        **/
        typedef enum _tagTransportMode {

            TransportModePlay,                                      /**< transport parameter mode="PLAY", session will be played */
            TransportModeRecord,                                    /**< transport parameter mode="RECORD", session will be recorded */
            TransportModeUndefined = 0xffff                         /**< transport parameter mode undefined    */
        } TRANSPORTMODE;                        

        /**                                        
        * @brief Type of media transmission from peer    
        **/                                    
        typedef enum _tagDeliveryType {            

            isUnicast,                                              /**< unicast connection */
            isMulticast,                                            /**< multicast connection */
            isBroadcast                                             /**< broadcast connection */
        } DELIVERYTYPE;

        /**
        * @brief Predefined media transport protocols
        **/ 
        typedef enum _tProtocol {

            protocolRtpAvp    = 0x0,                                /**< RTP  */
            protocolUdp       = 0x1,                                /**< UDP  */
            protocolTcp       = 0x2,                                /**< TCP  */
            protocolRtcp      = 0x3,                                /**< RTCP */
            protocolMP2T      = 0x4,                                /**< MPEG 2 TS over UDP */
            protocolRAW       = 0x5,                                /**< RAW  */
            protocolUndefined = 0xffff
        } PROTOCOL;

        /**
        * @brief Predefined bandwidth modifier
        **/
        typedef enum _tBandwidthModifier {

            bandwidthModifierNONE = 0x0,                            /**< Bandwidth modifier is not specified */
            bandwidthModifierCT   = 0x1,                            /**< CT, Conference Total */
            bandwidthModifierAS   = 0x2,                            /**< AS, Application-Specific Maximum */
            bandwidthModifierRS   = 0x3,                            /**< RS */
            bandwidthModifierRR   = 0x4,                            /**< RR */
            bandwidthModifierEX   = 0x5                             /**< X-, user defined extension */
        } BANDWIDTHMODIFIER;

        /**
        * @brief Predefined network types
        **/
        typedef enum _tNetworkType {

            networkInternet,                                        /**< IN specificator, Internet */
            networkTypeNotPresent                                   /**< Network type is not present */
        } NETWORKTYPE;

        /**
        * @brief Predefined Address types
        **/
        typedef enum _tAddressType {

            addressTypeIP4,                                         /**< IPv4 */
            addressTypeIP6,                                         /**< IPv6 */
            addressTypeNotPresent                                   /**< Address type is not present */
        } ADDRESSTYPE;

        /**
        * @brief Predefined methods obtaining encryption key
        **/
        typedef enum _tEncryptionMethod {

            encryptionMethodClear,                                  /**< clear : key is present in key field as is */
            encryptionMethodBase64,                                 /**< base64 : key is encoded in Base64 */
            encryptionMethodUri,                                    /**< uri : key may be obtain from specified URI */
            encryptionMethodPrompt                                  /**< prompt : no key is include in sdp description, user should be prompted */
        } ENCRYPTIONMETHOD;
    };
};

#endif // __MC_PARSER_SDP_DEFINES_H__
