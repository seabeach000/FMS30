/**
@file   net_renderer.h
@brief  NetRenderer/RTSP Server API 

@verbatim
File: net_renderer.h
Desc: NetRenderer/RTSP Server API

Copyright (c) 2014 MainConcept GmbH or its affiliates.  All rights reserved.

MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.  
This software is protected by copyright law and international treaties.  Unauthorized 
reproduction or distribution of any portion is prohibited by law.
@endverbatim
**/

#if !defined (__NETRENDERER_API_H__)
#define __NETRENDERER_API_H__

#include "parser_sdp.h"
#include "mctypes.h"
#include "net_common.h"

#include "mcapiext.h"
 
/**
 * @name Used data packet sizes
 * @{
 **/

/**
 * @brief MAX TCP header size
 * @hideinitializer
 **/
#define MTU_REDUCE 60

/**
 * @brief Default data packet size, common for TCP and UDP according standard MTU size
 * @hideinitializer
 **/
#define PACKET_SIZE_DEFAULT_VALUE 1500 - MTU_REDUCE

/**
 * @brief Maximum data packet size
 * @hideinitializer
 **/
#define MAX_PACKET_SIZE 0xFFFF - MTU_REDUCE

/**
 * @brief Minimum data packet size
 * @hideinitializer
 **/
#define MIN_PACKET_SIZE 0x1F4 - MTU_REDUCE

/**
 * @brief Maximum data sample size
 * @hideinitializer
 **/
#define MAX_SAMPLE_SIZE 0xFFFF
/** @} */

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
        * @brief Describes RTSP transport properties
        **/
        typedef struct _tagTransportInfo {

            PROTOCOL            _ProtocolMode;                      /**< Protocol of data delivery */
            NETPROFILETYPE      _TransportProfiles;                 /**< RTP profile */
            LOWERTRANSPORTTYPE  _LowerTransport;                    /**< Lower transport protocol */
            TRANSPORTMODE       _TransportMode;                     /**< Mode of playback media */
            DELIVERYTYPE        _DeliveryType;                      /**< Type of data transmission */
            int8_t              _aDestination[1024];                /**< Address of data destination */
            int8_t              _aSourceAddress[1024];              /**< Address of data source */
            uint32_t            _uiLayers;                          /**< The number of multicast layers to be used for this media
                                                                            stream. The layers are sent to consecutive addresses starting
                                                                            at the destination address. */
            bool                _bAppend;                           /**< If the mode parameter includes RECORD, the append parameter
                                                                            indicates that the media data should append to the existing
                                                                            resource rather than overwrite it. */
            bool                _bIsInterleaved;                    /**< Interleaving data and RTSP commands (see RCF 2326) */
            uint32_t            _uiTTL;                             /**< Time to live value */

            uint32_t            _uiClientRtpPort;                   /**< Client's port for media data */
            uint32_t            _uiClientRtcpPort;                  /**< Client's port for RTCP notifies */

            uint32_t            _uiServerRtpPort;                   /**< Server's port for media data */
            uint32_t            _uiServerRtcpPort;                  /**< Server's port for RTCP notifies */

            uint32_t            _uiSsrc;                            /**< RTP SSRC: The source of a stream of RTP packets,
                                                                        identified by a 32-bit numeric SSRC identifier carried in the
                                                                        RTP header so as not to be dependent upon the network address. */
        } TRANSPORTINFO;

        /**
        * @brief Describes available RTP sender's parameters
        **/
        typedef enum _tagSenderParamsId {

            ESvcQualityId           = 0x00,                         /**< type = uint32_t value of max QualityID     */
            ESvcDependencyId        = 0x01,                         /**< type = uint32_t value of max DependencyID */
            ERTCPSendInterval       = 0x02,                         /**< type = uint32_t, value is in mili seconds */
            EBurstnessValue         = 0x03,                         /**< type = uint32_t, value is in mili seconds (0..1000) */
            ERtpInfo                = 0x04,                         /**< type = INTERNALRTPINFO pointer, uiParamSize = sizeof INTERNALRTPINFO */
            ESourcePort             = 0x05,                         /**< type = uint32_t, value of local port number */
            EDestinationPort        = 0x06,                         /**< type = uint32_t, value of remote port number */
            EDecoderConfig          = 0x07,                         /**< type = uint8_t *, value is binary data representing decoder cofing (for avc: SPS/PPS/[SEI]); data format depends on stream format: for annexB 0x00000001; for mp4nalu nalu size field with length similar to other slices in the stream */
            ESharedSocketInfo       = 0x08,                         /**< type = ISharedSocketInfo*, valid pointer to ISharedSocketInfo instance which contains information got from NetSource that want to receive data from the socket which renderer uses for sending, NetSource should be ready for Shared Socket Exchange*/
            ESenderParamMaxId       = 0x7FFFFFFF                    /**< Stub parameter value */
        } SENDERPARAMSID;

        /**
        * @brief Describes redirect address
        **/
        typedef struct _tagRtspRedirectParams {

            int64_t         client_id;                              /**< Unique client identifier, which accords redirected client */
            const char*   pServerAddr;                            /**< new server address */
            int32_t         iAddrLen;                               /**< size of new server address */
        } RtspRedirectParams;

		/**
        * @brief Describes universal sender settings
        **/
		typedef enum _tagNetUniversalSenderParamsId {

			EUniversalSenderParamMaxPacketSize = 0,					/**< set max packet size */
			EUniversalSenderParamAddRtcpSender = 1,					/**< add IRtcpServerSender to list */
			EUniversalSenderParamRemoveRtcpSender = 2,				/**< remove IRtcpServerSender from list */
			EUniversalSenderParamMaxId   = 0x7FFFFFFF               /**< Stub ParameterID */
		} NETUNIVERSALSENDERPARAMSID;

		/**
        * @brief Describes server RTCP sender settings
        **/
		typedef enum _tagNetServerRtcpSenderParamsId {

			EServerRtcpCountOfRtpPackets = 0,						/**< Set count of sent rtp packets for Sender Report */
			EServerRtcpOctetsCountInRtpPackets = 1,					/**< Set count of bytes sent for Sender Report */
			EServerRtcpClocksResolutionCoeff = 2,					/**< Set RTP timestamp clock resolution in Hz */
			EServerRtcpInitialTimeShift = 3,						/**< Set initial RTP timestamp for Sender Report */
			EServerRtcpSSRC = 4,									/**< Set SSRC for Sender Report */
			EServerRtcpParamMaxId   = 0x7FFFFFFF                    /**< Stub ParameterID */
		} NETSERVERRTCPSENDERPARAMSID;

        /**
        * @brief Describes server settings or stream events
        **/
        typedef enum _tagRtspServerParamsId {

            ERtspMaxClientsCount    = 0x00,                         /**< Maximum count of active client on server */
            ERtspMediaStoragePath   = 0x01,                         /**< Path to media files */
            ERtspClientTimeOut      = 0x02,                         /**< RTSP channel activity timeout, set to 0 to disable */
            ERtspForceESStreaming   = 0x03,                         /**< Force demuxing media containers  */
            ERtspPasswdFilename     = 0x04,                         /**< Path to passwd file, contains list of allowed users  */
            ERtspMCAccessFilename   = 0x05,                         /**< Name of mcaccess file, contains rules of access to media */
            ERtspRealmName          = 0x06,                         /**< Realm name for server, used for autorization */
            ERtspEOS                = 0x07,                         /**< End of stream occured */
            ERtspRedirect           = 0x08,                         /**< Force client redirect to new server */
            ERtspEOSNotification    = 0x09,                         /**< Enable/Disable client notification on End of Stream, bool value: true/false; default:false */
            ERtspServerParamMaxId   = 0x7FFFFFFF                    /**< Stub ParameterID */
        } RTSPSERVERPARAMSID;

        /**
        * @brief Describes result code of network renderer component
        **/
        typedef enum _tagNetRendererErrors {

            NwrOk                       =  0,                       /**< Operation complete successful */
            NwrNotEnoughData            =  1,                       /**< Not enoung data to continue to work, repeat with new chunk of data  */
            NwrDataChunkNotRecognized   =  2,                       /**< Unknown data received, try other data chunk */
            NwrSdpDamaged               = -1,                       /**< SDP document is incorrect or corrupted  */
            NwrNotImplemented           = -2,                       /**< Operation is not implemented */
            NwrParamNotFound            = -3,                       /**< Unknown parameter */
            NwrBadParamValue            = -4,                       /**< Type of parameter value doesn't match with parameter id or corrupted */
            NwrError                    = -5,                       /**< Operation failed */
            NwrWrongState               = -6                        /**< Operation requested at wrong server state, try other operation */
        } NETRENDERERERRORS;

        /**
        * @brief Describes RTSP specific result codes
        **/
        typedef enum _tagRtspServerErrors {

            RtspOk                  = 0x00,                         /**< Operation complete successful */
            RtspPlayFailed,                                         /**< Play request failed */
            RtspPauseFailed,                                        /**< Pause request failed */
            RtspTeerdownFailed,                                     /**< Teardown failed */
            RtspOptionsFailed,                                      /**< Options request failed */
            RtspDescribeFailed,                                     /**< Describe request failed */
            RtspSetupFailed,                                        /**< Setup request failed */
            RtspInitPortBusyError,                                  /**< Socket port is busy, try other */
            RtspInitSocketsError,                                   /**< Socket init error */
            RtspListenError,                                        /**< Socket listen error */
            RtspBindError,                                          /**< Socket bind error */
            RtspNotImplemented,                                     /**< Operation is not implemented */
            RtspError,                                              /**< Operation failed */
            RtspMovedPermanently,                                   /**< Resource moved permanently to redirect server */
            RtspMovedTemporarily                                    /**< Resource moved temporarily to redirect server */
        } RTSPSERVERERRORS;

        /**
        * @brief Solid memory block description
        **/
        typedef struct _tagBufferInfo {

            uint8_t*    pBuff;                                      /**< Pointer to active part of memory block(shifted for internal prefix) */
            uint8_t*    pSrcBuff;                                   /**< Pointer to start of memory block */
            uint32_t    uiActualBufferLen;                          /**< Size of actual data in block */
            uint32_t    uiMaxBufferLen;                             /**< Maximum available size of block */
        } BUFFERINFO;

        /**
        * @brief Media Sample information
        **/
        typedef struct _tagSampleInfo {

            BUFFERINFO  bufferInfo;                                 /**< Sample data  */
            uint32_t    uiStartTimeMcs;                             /**< Start timestamp */
        } SAMPLEINFO;

        /**
        * @brief Describes SAP packet type
        **/
        typedef enum _tagSapPacketType {

            SapAnnounce = 0x00,                                     /**< SAP announce packet */ 
            SapDeletion = 0x01                                      /**< SAP deletion packet */
        } SAPPACKETTYPE;

        /**
        * @brief AVC bytestream NALU delimiter format
        **/
        typedef enum _tagAvcPayloadType {

            annexB  = 0x00,                                         /**< Start code is present in bytestream */
            naluMP4                                                 /**< NALU size present */
        } AVCPAYLOADTYPE;

        /**
        * @brief HEVC bytestream NALU delimiter format
        **/
        typedef enum _tagHevcPayloadType {

            HevcAnnexB  = 0x00,                                     /**< Start code is present in bytestream */
        } HEVCPAYLOADTYPE;

        /**
        * @brief JPEG RTP sender properties
        **/
        typedef struct _tagJpegInfo {

            uint32_t uiWidth;                                       /**< Width frame in pixels */
            uint32_t uiHeight;                                      /**< Height frame in pixels */
        } JPEGINFO;

        /** 
        * @brief Uncompressed audio RTP sender properties
        **/
        typedef struct _tagRawAudioInfo {

            uint16_t usChannelsCount;                               /**< audio channels count */
        } RAWAUDIOINFO;

        /**
        *  @brief AMR audio RTP sender properties
        **/
        typedef struct _tagAmrRtpInfo {

            uint16_t usChannelsCount;                               /**< audio channels count */
        } AMRRTPINFO;

        /**
        * @brief HEVC RTP sender properties
        **/
        typedef struct _tagHEVCRtpInfo {

            bool            bRemoveParamSetPackets;                 /**< enable removing VPS/SPS/PPS NALU from video stream */
            uint32_t        uiNaluLenHeaderSize;                    /**< NALU header(or start code) size in bytes*/
            HEVCPAYLOADTYPE hevcPayloadType;                        /**< format HEVC NALU */
        } HEVCRTPINFO;

        /**
        * @brief AVC RTP sender properties
        **/
        typedef struct _tagAVCRtpInfo {

            bool            bRemoveParamSetPackets;                 /**< enable removing SPS/PPS NALU from video stream */
            uint32_t        uiNaluLenHeaderSize;                    /**< NALU header(or start code) size in bytes*/
            AVCPAYLOADTYPE  avcPayloadType;                         /**< format AVC NALU */
        } AVCRTPINFO;

        /**
        * @brief SVC(Scalable Video Coding) RTP sender properties
        **/
        typedef struct _tagSVC_AVCRtpInfo {

            bool            bRemoveParamSetPackets;                 /**< enable removing SPS/PPS NALU from video stream */
            uint32_t        uiNaluLenHeaderSize;                    /**< NALU header(or start code) size in bytes*/
            AVCPAYLOADTYPE  avcPayloadType;                         /**< format AVC NALU */
            uint32_t        uiMaxDependencyId;                      /**< Maximum dependency id(resolution) */
            uint32_t        uiMaxQualityId;                         /**< Maximum quality id(bitrate layer) */
        } SVC_AVCRTPINFO;

        /**
        * @brief MVC(Multiview Video Coding) RTP sender properties
        **/
        typedef struct _tagMVC_AVCRtpInfo {

            bool            bRemoveParamSetPackets;                 /**< enable removing SPS/PPS NALU from video stream */
            uint32_t        uiNaluLenHeaderSize;                    /**< NALU header(or start code) size in bytes*/
            AVCPAYLOADTYPE  avcPayloadType;                         /**< format AVC NALU */
        } MVC_AVCRTPINFO;

        /**
        * @brief AAC RTP sender properties
        **/
        typedef struct _tagAACRtpInfo {

            long indexLength;                                       /**< number of bits on which the AU-index field is encoded in the AU-header */
            long indexDeltaLength;                                  /**< number of bits on which the AU-index-delta field is encoded in the non-first AU-header */
            long sizeLength;                                        /**< number of bits on which the AU-size field is encoded in the AU-header */
        } AACRTPINFO;

        /**
        * @brief WMA(Windows Media Audio elementary stream) RTP sender properties
        **/
        typedef struct _tagWMARtpInfo {

        } WMARTPINFO;

        /**
        * @brief WMV(Windows Media Video elementary stream) RTP sender properties
        **/
        typedef struct _tagWMVRtpInfo {

        } WMVRTPINFO;

        /**
        * @brief LATM RTP sender properties
        **/
        typedef struct _tagLATMRtpInfo {

            void*   pStreamMuxConfig;                               /**< LATM decoder config */
            int32_t iStreamMuxConfigLen;                            /**< size of decoder config */
        } LATMRTPINFO;

        class IRtcpNotifier;
        class ISenderNotifier;

        /**
        * @brief Base RTP sender initial configuration
        **/
        typedef struct _tagSenderConnectionInitParams {

            ISenderNotifier*    pSenderNotifier;                    /**< Catches sender's notifies: what amount of data sent, what timestamp sent, etc... */
            IRtcpNotifier*      pRtcpNotifier;                      /**< Catches RTCP notifies */
            uint8_t             ucPayloadType;                      /**< Media stream type */
            char*               aNIC;                               /**< Local network interface */
            char*               aRemoteName;                        /**< Remote address */
            uint32_t            aDstPort;                           /**< Remote network port */
            uint32_t            aSrcPort;                           /**< Local network port */
            int32_t             iProtocol;                          /**< Transport layer protocol, type: IPPROTO from Berkley sockets defines */
            int32_t             iMtu;                               /**< Network MTU */
            int32_t             iTtl;                               /**< Time to live value */
            bool                bIsRawMode;                         /**< Toggles RTP enabled/disables( make sense for UDP ) */
            uint32_t            uiBurstnessValue;                   /**< Time for undelayed sending data */
        } SENDERCONNECTIONPARAMS;

        /**
        * @brief Media specific RTP sender parameters
        **/
        typedef struct _tagSenderInfo {

            MEDIATYPE   mediaType;                                  /**< Media data type */
            uint32_t    uiSampleRate;                               /**< Data sample rate (samples per second) */
            PROTOCOL    aConnectionType;                            /**< Network protocol */
            STREAMTYPE  aStreamType;                                /**< Media stream type */
            uint32_t    cbDescriptor;                               /**< Size of media specific descriptor */
            void*       pDescriptor;                                /**< Media specific RTP info: AACRTPINFO, AVCRTPINFO, etc */
        } SENDERINFO;

        /**
        * @brief RTP packet header info
        **/
        typedef struct _tagInternalRtpInfo {

            uint32_t _ID;                                           /**< Identifier of data stream */
            uint32_t _SSRC;                                         /**< RTP SSRC */
            uint32_t _TS;                                           /**< RTP packet timestamp */
            uint16_t _SeqNum;                                       /**< RTP Sequence number */
        } INTERNALRTPINFO;

		/**
		* @brief RTSP End-of-Stream notification data
		*/
		typedef struct _tagRtspEosInfo {

			int64_t ClientID;										/**< Unique identifier of client that received notification  */
			INTERNALRTPINFO* pRtpInfo;								/**< Pointer to array of INTERNALRTPINFO structures for each last RTP packet in the stream */
			uint32_t iRtpInfoCount;									/**< Size of array of INTERNALRTPINFO structures */
		} RTPEOSINFO;

        /**
        * @brief RTCP Quality Information type
        **/
        typedef enum _tagQualityInfoType {

            EMCExtendedQualityInfo  = 0x00,                         /**< Extended quiality info */
            EUndefinedQualityInfo   = 0x7FFFFFF                     /**< Stubs value */
        } QUALITYINFOTYPE;

        /**
        * @brief Content of extended quality info
        **/
        typedef struct _tagMCExtQualityInfo {

            int8_t  _ClientIP[1024];                                /**< Receiver IP address */
        } MCEXTQUTALITYINFO;

        /**
        * @brief Describes content of RTCP notifies
        **/
        typedef struct _tagQualityInfo {

            int32_t         _iJitter;                               /**< Jitter */
            int32_t         _iDropCount;                            /**< Count of dropped data */
            uint32_t        _uiSSRC;                                /**< RTP SSRC */
            void*           _pAdditionalInfo;                       /**< Extended quality info */
            QUALITYINFOTYPE _AdditionalInfoType;                    /**< Type of extended info */
        } QUALITYINFO;

        /**
        * @brief Provides interface for providing reference clock to LL engine
        **/
        class IClockProvider
        {
        public:
            virtual ~IClockProvider() {}

            /**
            * @brief Retrieves reference time
            * 
            * @return   current reference time( system time or graph time or other )
            **/
            virtual int64_t GetWallclockTime() const = 0;
        };

        /**
        *  @brief Interface which should be used for send rate control
        **/
        class ISenderNotifier
        {
        public:
            virtual ~ISenderNotifier() {}

            /**
            * @brief Called on stream decoder config changed 
            * 
            * @param[in] pData      new decoder config
            * @param[in] uiDataLen  size of decoder config
            * @return               None
            **/
            virtual void OnConfigChanged( void *pData, uint32_t *uiDataLen ) = 0;

            /**
            * @brief Called on each sent data packet
            * 
            * @param[in] bMarker        RTP marker of end of frame
            * @param[in] aBytesSent     count of sent data
            * @param[in] i64TimeStamp   timestamp of last sent packet
            * @param[in] uiSamplesCount count of sent samples
            * @return                    None
            **/
            virtual void OnPacketSend( bool bMarker, uint32_t aBytesSent, int64_t i64TimeStamp, uint32_t uiSamplesCount ) = 0;
        };

        /**
        * @brief RTCP notifier interface
        **/
        class IRtcpNotifier
        {
        public:
            virtual ~IRtcpNotifier() {}

            /**
            * @brief Called on RTCP quality packet receiving
            * 
            * @param[in] pStat describes quality of streaming
            * @return          None
            **/
            virtual void OnQualityInfo( const QUALITYINFO * const pStat ) = 0;
        };

	    /**
        * @brief RTCP handler/sender interface. Implementation of that interface should apply: client's RTCP reports analyzing; generating and delivering server's RTCP reports.
        **/
		class IRtcpServerSender
		{
		public:
			virtual ~IRtcpServerSender() {}

			/**
            * @brief Reset internal state/variables/etc for RTCP sender
            * 
            * @return               None
            **/
			virtual void Reset() = 0;

			/**
            * @brief Called on stream decoder config changed 
            * 
            * @return               ID for given RTCP sender (in case of interleaving ID should be equal to valid interleaving RTCP channel value)
            **/
			virtual uint8_t GetID() = 0;

			/**
            * @brief This method should be used to start listening/handling RTCP messages
            * 
            * @return              Return @ref NETRENDERERERRORS
            **/
			virtual NETRENDERERERRORS Start() = 0;

			/**
            * @brief This method should be used to stop listening/handling RTCP messages
            * 
            * @return              Return @ref NETRENDERERERRORS
            **/
			virtual NETRENDERERERRORS Stop() = 0;

			/**
            * @brief This is method is used for sending RTCP messages to client
            * 
            * @param[in] aPacketType        type of the RTCP message (see rfc3550)
            * @param[in] CSRC_count			count of reports in current RTCP message (see rfc3550)
            * @return                       Return @ref NETRENDERERERRORS
            **/
			virtual NETRENDERERERRORS SendPacket( RTCPPACKETTYPE aPacketType, uint32_t CSRC_count ) = 0;


			/**
            * @brief This method should be used for processing incoming RTCP messages
            * 
            * @param[in] pBuff              valid pointer on buffer with RTCP message. First byte of the buffer should point on the first byte of RTCP message body (RTCP packet type).
            * @param[in] uiBuffLen			RTCP message buffer size in bytes
            * @return                       Return @ref NETRENDERERERRORS
            **/
			virtual NETRENDERERERRORS ProcessIncomingRtcpPacket( uint8_t *pBuff, uint32_t uiBuffLen ) = 0;

			/**
            * @brief Allows to change sender's property
            * 
            * @param[in] aType              type of the notify NETSERVERRTCPENDERPARAMSID
            * @param[in] pData				valid pointer on parameter data
            * @param[in] uiDataSize         size in bytes of the parameter
            * @return                       Return @ref NETRENDERERERRORS
            **/
            virtual NETRENDERERERRORS SetParameter( NETSERVERRTCPSENDERPARAMSID aType, void *pData, uint32_t uiDataSize ) = 0;
		};

        /**
        * @brief Universal data sender for external or interleaved sending data
        **/
        class IUniversalDataSender : public INetRefCounted
        {
        public:
            virtual ~IUniversalDataSender() {}

            /**
            * @brief Initializes sender instance 
            * 
            * @param[in] pInitData custom initialization data
            * @param[in] uiSize    size of initialization data
            * @return              Return @ref NETRENDERERERRORS
            **/
            virtual NETRENDERERERRORS Init( void *pInitData, uint32_t uiSize = 0 ) = 0;

            /**
            * @brief Calls on each ready for sending data chunk
            * 
            * @param[in] pData              block of media data chunk
            * @param[in] uiDataLen          size of media data chunk
            * @param[in] uiID               identifier of data sender
            * @param[in] pUserDefinedParams additional information about data chunk
            * @param[in] iUserParamsSize    size of additional info
            * @return                       Return @ref NETRENDERERERRORS
            **/
            virtual NETRENDERERERRORS OnData( uint8_t *pData, uint32_t uiDataLen, uint32_t uiID, void* pUserDefinedParams = NULL, int32_t iUserParamsSize = 0 ) = 0;

			/**
            * @brief Allows to change sender's property
            * 
            * @param[in] aType              type of the notify @ref NETUNIVERSALSENDERPARAMSID
            * @param[in] pData				valid pointer on parameter data
            * @param[in] uiDataSize         size in bytes of the parameter
            * @return                       Return @ref NETRENDERERERRORS
            **/
            virtual NETRENDERERERRORS SetParameter( NETUNIVERSALSENDERPARAMSID aType, void *pData, uint32_t uiDataSize ) = 0;
        };

        /**
        * @brief Interface for network media data sender 
        **/
        class IBaseSender : public INetRefCounted
        {
        public:
            virtual ~IBaseSender() {}

            /**
            * @brief Sends media sample
            * 
            * @param[in]  pSample          pointer to media data memory block
            * @param[in]  uiSampleLen      size of media sample 
            * @param[out] cbConsumed       count of data consumed by sender
            * @param[in]  i64TimeStampNSec sample timestamp in 100 nanosecond units
            * @param[in]  bIsForceSend     to force send data immediately. It has meaning only for data without described packet size: 
                                            H263, MJPEG, VC1, MPEG1 Video Elemantary stream, MPEG2 Video Elementary Stream. RAW data send 
                                            immediately anyway, other types require buffering to detect boundaries. 
                                            Application may reduce network overhead by collecting small RAW data chunks by itself.
            * @return                      Return @ref NETRENDERERERRORS
            **/
            virtual NETRENDERERERRORS SendPacket( const uint8_t *pSample, uint32_t uiSampleLen, uint32_t *cbConsumed, int64_t i64TimeStampNSec, bool bIsForceSend = false ) = 0;

            /**
            * @brief Initializes Base RTP sender
            *                         
            * @param[in] pSenderInitParams Sender initialization setting
            * @return                      Return @ref NETRENDERERERRORS 
            **/
            virtual NETRENDERERERRORS Init( SENDERCONNECTIONPARAMS *pSenderInitParams ) = 0;

            /**
            * @brief Replaces internal RTP media sender on external interleaved sender
            * 
            * @param[in] pConsumer  valid pointer to IUniversalDataSender 
            * @return               Return @ref NETRENDERERERRORS
            **/
            virtual NETRENDERERERRORS SetInterleavedDataConsumer( IUniversalDataSender *pConsumer ) = 0;

            /**
            * @brief Replaces internal RTP media sender on external data consumer
            * 
            * @param[in] pConsumer valid pointer to external data consumer
            * @return              Return @ref NETRENDERERERRORS 
            **/
            virtual NETRENDERERERRORS SetExternalDataConsumer( IUniversalDataSender *pConsumer ) = 0;

            /**
            * @brief Configures a sender instance
            * 
            * @param[in] uiParamId   identifies sender's parameter
            * @param[in] pParam      value of parameter
            * @param[in] uiParamSize size of parameter value 
            * @return                Return @ref NETRENDERERERRORS
            **/
            virtual NETRENDERERERRORS SetParameter( SENDERPARAMSID uiParamId, const void *pParam, uint32_t uiParamSize ) = 0;

            /**
            * @brief Retrieves internal settings
            * 
            * @param[in]  uiParamId   identifies internal parameter
            * @param[out] pParam      current value of parameter
            * @param[out] uiParamSize size of value
            * @return                 Return @ref NETRENDERERERRORS
            **/
            virtual NETRENDERERERRORS GetParameter( SENDERPARAMSID uiParamId, void *pParam, uint32_t *uiParamSize ) = 0;

            /**
            * @brief Notifies sender on discontinuity state
            * 
            * @return   None
            **/
            virtual void SetDiscontinuity() = 0;

            /**
            * @brief Flushes stored data from sender away, not sending it to the network
            *                    
            * It is called on Seek operation to reset sender internal state, not called on Pause to avoid packet lose due gap on RTP sequence number. 
            * 
            * @return   None
            **/
            virtual void Flush() = 0;

            /**
            * @brief Stops sending data
			*
			* Last remaining packet is marked and sent. Should be called before Flush to avoid loosing last sample.
            * 
            * @return None
            **/
            virtual void Stop()  = 0;
        };

        /**
        * @brief Main Network renderer engine interface
        **/
        class INetRendererEngine : public INetRefCounted
        {
        public:
            virtual ~INetRendererEngine() {}

            /**
            * @brief Prepares engine to sending SAP announce with SDP document 
            * 
            * @param[in] pSdpDocument SDP for sending
            * @param[in] aRemoteName  Remote address for sending
			* @param[in] aTTL		  TTL value for the SAP packets
            * @return                 Return @ref NETRENDERERERRORS
            **/
            virtual MainConcept::NetworkStreaming::NETRENDERERERRORS PrepareAnnounce( const MainConcept::NetworkStreaming::ISdpDecoder *pSdpDocument, const char *aRemoteName = NULL, uint32_t aTTL = 255 ) = 0;

            /**
            * @brief Sends single SAP announce 
            * 
            * @param[in] aSapPacketType SAP packet type
            * @return                   Return @ref NETRENDERERERRORS 
            **/
            virtual NETRENDERERERRORS SendAnnounce( SAPPACKETTYPE aSapPacketType = SapAnnounce ) = 0;

            /**
            * @brief Creates media specific sender instance
            * 
            * @param[in] aSenderInfo media sender configuration
            * @return                valid pointer to @ref IBaseSender or NULL if media is not supported
            **/
            virtual IBaseSender * CreateSenderInstance( SENDERINFO *aSenderInfo ) = 0;
        };

        /**
        * @brief RTSP server engine (RFC2326 compatible)
        **/ 
        class IRtspServerEngine : public INetRefCounted
        {
        public:
            virtual ~IRtspServerEngine() {}

            /**
            * @brief Initialized engine instance
            * 
            * @param[in] aPort        used server port
            * @param[in] aNIC         local network interface for server (NULL or "0.0.0.0" for any available interface)
            * @param[in] pMediaFolder specifies location of media files
            * @param[in] bIsForceES   indicates stream status: multiplexed (MPEG-2 TS, MPEG-2 PS, MPEG-1 SS) or elementary
            * @return                 Return @ref RTSPSERVERERRORS 
            **/
            virtual RTSPSERVERERRORS Init( int32_t aPort, const char *aNIC, const char *pMediaFolder = ".", bool bIsForceES = false ) = 0;

            /**
            * @brief Starts listening for incoming RTSP connections
            * 
            * @return   Return @ref RTSPSERVERERRORS
            **/
            virtual RTSPSERVERERRORS Start() = 0;

            /**
            * @brief Could be used for additional server engine initialization
            * 
            * @param[in] uiParamId    server parameter identifier
            * @param[in] pParam value of parameter
            * @param[in] uiParamSize  size of parameter value
            * @return                 Return @ref RTSPSERVERERRORS
            **/
            virtual RTSPSERVERERRORS SetParameter( RTSPSERVERPARAMSID uiParamId, const void *pParam, uint32_t uiParamSize ) = 0;

            /**
            * @brief Force disconnection of specified client
            * 
            * @param[in] ID unique client identifier 
            * @return None
            **/
            virtual void ForceKillClient( int64_t ID ) = 0;
        };

        /**
        * @brief Media graph builder interface.
        * 
        * Used for control media playback, delivering data to sender, additional checking of clients request 
        **/
        class IRtspMediaGraphController : public INetRefCounted
        {
        public:
            virtual ~IRtspMediaGraphController() {}

            /**
            * @brief Used for building media graph on requested file path
            * 
            * @param[in] pMediaFullPath full file path
            * @param[in] bIsForceES     notifies about primarily demultiplexing
            * @param[out] pSdpDocument  SDP document specifies requested media file
            * @return                   Return @ref RTSPSERVERERRORS 
            **/
            virtual RTSPSERVERERRORS OnDescribe( const char *pMediaFullPath, bool bIsForceES, const ISdpDecoder **pSdpDocument ) = 0;

            /**
            * @brief Adjusts sender parameter based on client requests (RTSP SETUP command, see RFC 2326)
            * 
            * @param[in] TrackID			identifier of media stream as index number in SDP document returned by OnDescribe(), it is started from 1
            * @param[in,out] pInfo			specifies transport parameters
            * @param[in] pInterleavedSender data sender for interleaving mode
            * @return						Return @ref RTSPSERVERERRORS
            **/
            virtual RTSPSERVERERRORS OnSetup( int32_t TrackID, TRANSPORTINFO *pInfo, IUniversalDataSender *pInterleavedSender ) = 0;

            /**
            * @brief Pauses playback
            * 
            * @param[out] i64CurrentPos current position of playback
            * @return                   Return @ref RTSPSERVERERRORS
            **/
            virtual RTSPSERVERERRORS OnPause( int64_t *i64CurrentPos ) = 0;

            /**
            * @brief Starts playback with updating of RTP specific parameters
            * 
            * @param[in,out] pRtpInfo   pointer to array of INTERNALRTPINFO for each media stream
            * @param[out]    aDuration  duration of stream
            * @param[in,out]     aStartTime start position (application should return real position after seek)
            * @param[in,out]     aStopTime  stop playing position (application should return real position after seek)
            * @param[in]     aRate      stream rate control
            * @return                   Return @ref RTSPSERVERERRORS
            **/
            virtual RTSPSERVERERRORS OnPlay( INTERNALRTPINFO *pRtpInfo, int64_t *aDuration, int64_t *aStartTime, int64_t *aStopTime, float aRate = 1.f ) = 0;

            /**
            * @brief Stops playback on disconnect
            * 
            * @return Return @ref RTSPSERVERERRORS
            **/
            virtual RTSPSERVERERRORS OnClose() = 0;

            /**
            * @brief Called on RTSP GET_PARAMETER request, allows to put to the answer application dependent parameters
            * 
            * @param[in]  pParamName name of requested parameter
            * @param[in]  iParamLen  length of parameter name
            * @param[out] pValue     parameter value 
            * @param[out] iValueLen  length of value
            * @return                Return @ref RTSPSERVERERRORS 
            **/
            virtual RTSPSERVERERRORS OnGetParameter( const char* pParamName, int32_t iParamLen, char* pValue, int32_t* iValueLen ) = 0;

            /**
            * @brief Notifies application about client's RTSP command request has been handled (allows to avoid of media data sending between client's request and server's answer)
            * 
            * @param[in] answerCode result code of response
            * @return               Return @ref RTSPSERVERERRORS 
            **/
            virtual RTSPSERVERERRORS OnResponseSent( int32_t answerCode ) = 0;

            /**
            * @brief Notifies application about client request, and allows to generate for example application dependent REDIRECT answer
            * 
            * @param[in]  pCommandName      string with client's RTSP command request
            * @param[in]  pControlUri       string with requested URI
            * @param[in]  iMaxHeaderLen     max available length of additional headers
            * @param[out] pAdditionalHeader pointer to space for any user-defined additional RTSP header 
            * @return                       Return @ref RTSPSERVERERRORS
            **/
            virtual RTSPSERVERERRORS OnCommand( const char* pCommandName, const char* pControlUri, int32_t iMaxHeaderLen, char* pAdditionalHeader ) = 0;
        };

        /**
        * @brief Observer for application level (for logging and etc..)
        * 
        * Observes events with clients connection
        **/
        class IRtspClientsObserver
        {
        public:
            virtual ~IRtspClientsObserver() {}

            /**
            * @brief Notifies application that client max count has been reached
            * 
            * @return None
            **/
            virtual void OnClientsCountOverflow() = 0;

            /**
            * @brief Notifies application about new client connection
            * 
            * @param[in] ID              unique identifier of new client
            * @param[in] pClientsAddress client network address
            * @return                    None
            **/
            virtual void OnNewClientConnection( int64_t ID, const char *pClientsAddress ) = 0;

            /**
            * @brief Called on any client disconnect or at loss connection with
            * 
            * @param[in] ID client identifier which lost connection
            * @return       None
            **/
            virtual void OnClientDisconnect( int64_t ID ) = 0;

            /**
            * @brief Notifies application with any RTSP command data
            * 
            * @param[in] ID                peer for data
            * @param[in] pBuff             passed data
            * @param[in] iLen              size of passed data
            * @param[in] bIsServerResponse indicates data direction, true - from server to client, false - otherwise
            * @return                      None
            **/
            virtual void OnData( int64_t ID, const char *pBuff, int32_t iLen, bool bIsServerResponse ) = 0;
        };

        /**
        * @brief Listener observer (application level)
        * 
        * Observes engine events
        **/
        class IRtspServerObserver
        {
        public:
            virtual ~IRtspServerObserver() {}

            /**
            * @brief Notifies application that server engine has been started successfully
            * 
            * @return None
            **/
            virtual void OnServerStartup() = 0;

            /**
            * @brief Notifies application that server engine has been stopped
            * 
            * @return None
            **/
            virtual void OnServerClose()   = 0;

            /**
            * @brief Requests media graph controller for new arrived client
            * 
            * @param[in]  ID                     unique client id
            * @param[out] ppMediaGraphController pointer to pointer to implementation of IRtspMediaGraphController
            * @return                            None
            **/
            virtual void RequestMediaGraphControllerInterface( int64_t ID, const IRtspMediaGraphController **ppMediaGraphController ) = 0;
        };

#if defined (__cplusplus)
        extern "C" {
#endif
            /**
            * @brief Discard RTP sender parameters to uninitialized state
            * 
            * @param[in,out] pSenderConnectionParams valid pointer to sender settings
            * @return                                None
            **/
            void NET_API_CALL ResetSenderConnectionParams( SENDERCONNECTIONPARAMS *pSenderConnectionParams );

            /**
            * @brief Retrieves new RTP Network Renderer component instance
            * 
            * @param[in] get_rc Pointer to get_rc memory manager implementation or NULL to use standard allocators
            * @return           valid pointer to new instance of network renderer component or NULL
            **/
            INetRendererEngine* NET_API_CALL GetRtpRendererInterface( void *(MC_EXPORT_API *get_rc)(const char*) );

            /**
            * @brief Retrieves new RTSP server engine instance
            * 
            * @param[in] get_rc            Pointer to get_rc memory manager implementation or NULL to use standard allocators
            * @param[in] pListenerObserver pointer to main server observer
            * @param[in] pObserver         pointer to clients connection observer
            * @return                      valid pointer to server engine
            **/
            IRtspServerEngine* NET_API_CALL GetRtspRendererInterface( void *(MC_EXPORT_API *get_rc)(const char*), IRtspServerObserver *pListenerObserver, IRtspClientsObserver *pObserver = NULL );

            /**
            * @brief Provides access to extended module API
            * 
            * @param[in] func identifier of module extended function
            * @return         pointer to requested function or NULL
            **/
            APIEXTFUNC NET_API_CALL NetRendererGetAPIExt(uint32_t func);
#if defined (__cplusplus)
        }
#endif
    };
};

#endif //__NETRENDERER_API_H__
