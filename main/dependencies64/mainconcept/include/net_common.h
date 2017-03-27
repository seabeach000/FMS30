/**
@file  net_common.h
@brief Common declaration for network components

@verbatim
File: net_common.h
Desc: Common declaration for network components

Copyright (c) 2015 MainConcept GmbH or its affiliates.  All rights reserved.

MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.  
This software is protected by copyright law and international treaties.  Unauthorized 
reproduction or distribution of any portion is prohibited by law.
@endverbatim
**/

#if !defined (__MC_NET_COMMON_H__)
#define __MC_NET_COMMON_H__

/**
* @def NET_API_CALL
* @brief Calling convention
**/
#if defined(WIN32)
#define NET_API_CALL __cdecl
#else
#define NET_API_CALL
#endif

/**
* @brief Converts 100-nanosec units to milliseconds
**/
#define MC_NET_NANOSECONDS_TO_MILLISECONDS(x) ((x)/10000LL)

/**
* @brief Converts millisecond to 100-nanosec units
**/
#define MC_NET_MILLISECONDS_TO_NANOSECONDS(x) ((x)*10000LL)

class CMCSockets;

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
        * @brief Predefined media types
        **/
        typedef enum _tMediaType {

            mediaAudio        = 0x0,                                /**< audio */
            mediaVideo        = 0x1,                                /**< video */
            mediaApplication  = 0x2,                                /**< application, playlists */
            mediaData         = 0x3,                                /**< data, text */
            mediaControl      = 0x4,                                /**< control */
            mediaImage        = 0x5,                                /**< image */
            mediaUndefined    = 0xffff                              /**< undefined data */
        } MEDIATYPE;

		/**
            @brief Common MIME Types
        */
		#define MIME_TYPE_PLAIN				"text/plain"            /**< "text/plain"          */
		#define MIME_TYPE_HTML				"text/html"             /**< "text/html"           */
		#define MIME_TYPE_XML				"text/xml"              /**< "text/xml"            */
		#define MIME_TYPE_BINARY			"binary/octet-stream"   /**< "binary/octet-stream" */
                                                                
		#define MIME_TYPE_JPEG				"image/jpeg"            /**< "image/jpeg"          */
		#define MIME_TYPE_GIF				"image/gif"             /**< "image/gif"           */
		#define MIME_TYPE_PNG				"image/png"             /**< "image/png"           */
                                                               
		#define MIME_TYPE_AVI				"video/avi"             /**< "video/avi"           */
		#define MIME_TYPE_MPEG_VIDEO		"video/mpeg"            /**< "video/mpeg"          */
		#define MIME_TYPE_MPEG_SYSTEM		"video/MP1S"            /**< "video/MP1S"          */
		#define MIME_TYPE_MPEG_PROGRAM		"video/MP2P"            /**< "video/MP2P"          */
		#define MIME_TYPE_MPEG_TRANSPORT	"video/MP2T"            /**< "video/MP2T"          */
		#define MIME_TYPE_MPEG4_VIDEO		"video/mp4"             /**< "video/mp4"           */
		//#define MIME_TYPE_MKV				"video/x-matroska"      /**< "video/x-matroska"    */
		#define MIME_TYPE_MKV				"video/x-mkv"           /**< "video/x-mkv"         */
		#define MIME_TYPE_3GP				"video/3gpp"            /**< "video/3gpp"          */
		#define MIME_TYPE_QUICKTIME			"video/quicktime"       /**< "video/quicktime"     */
		#define MIME_TYPE_ASF				"video/x-ms-asf"        /**< "video/x-ms-asf"      */
		#define MIME_TYPE_WMV				"video/x-ms-wmv"        /**< "video/x-ms-wmv"      */
		#define MIME_TYPE_MPEG_AUDIO		"audio/mpeg"            /**< "audio/mpeg"          */
		#define MIME_TYPE_MPEG1_AUDIO		"audio/MPA"             /**< "audio/MPA"           */
		#define MIME_TYPE_MPEG4_AUDIO		"audio/mpeg4-generic"   /**< "audio/mpeg4-generic" */
		#define MIME_TYPE_AC3				"audio/ac3"             /**< "audio/ac3"           */
		#define MIME_TYPE_WAV				"audio/wav"             /**< "audio/wav"           */
		#define MIME_TYPE_WMA				"audio/x-ms-wma"        /**< "audio/x-ms-wma"      */
        #define MIME_TYPE_M3U8				"audio/x-mpegurl"       /**<   */
        #define MIME_TYPE_M3U				"audio/mpegurl"         /**<   */
        #define MIME_TYPE_M3U_APPLE	    	"application/vnd.apple.mpegurl"             /**<           */
        #define MIME_TYPE_WPL				"application/vnd.ms-wpl" /**<   */
        #define MIME_TYPE_SMIL				"application/smil"       /**<   */
        #define MIME_TYPE_DASH_MPD			"application/dash+xml"   /**<   */
        #define MIME_TYPE_APP_XML           "application/xml"
        #define MIME_TYPE_SDP               "application/sdp"
                                                                     
        /**
        * @brief Common network components result codes
        **/
        typedef enum _tagMCNetResult {
            MCNetResultOK                          = 0,             /**< Operation completed successfully */
            MCNetResultFailed                      = 1,             /**< Operation failed */
            MCNetResultInvalidArgument             = 2,             /**< Invalid argument provided */
            MCNetResultInvalidState                = 3,             /**< Invalid command state */
            MCNetResultOutOfMemory                 = 4,             /**< Memory allocation failed */
            MCNetResultNotSupportedEncryptMethod   = 5,             /**< Specified encryption method is not supported */
            MCNetResultRequestedAuthorization      = 6,             /**< Operation requires authorization */
            MCNetResultDNSNameLookupFailed         = 7,             /**< DNS resolving failed */
            MCNetResultConnectFailed               = 8,             /**< Connection could not be established */
            MCNetResultReceiveFailed               = 9,             /**< Response was not received successfully */
            MCNetResultSendFailed                  = 10,            /**< Send operation failed */
            MCNetResultNoData                      = 11,            /**< Data is not available */
            MCNetResultTimedOut                    = 12,            /**< Time limit has been reached */
            MCNetResultNotConnected                = 13,            /**< Operation requires active connection */
            MCNetResultNotImplemented              = 14,            /**< Not implemented yet */
            MCNetResultServerDoesNotSupport        = 15,            /**< Parameter is not compatible with current mode of engine */
            MCNetResultRestricted                  = 16,            /**< Don't have permission to complete operation */
            MCNetResultRequestedProxyAuthorization = 17,            /**< Proxy server requires authorization */
            MCNetResultBindFailed                  = 18,            /**< Bind socket failed */
            MCNetResultRequestedRedirect           = 19,            /**< Received redirect request */
            MCNetResultUnsupportedProtocol         = 20,            /**< Protocol is not supported */
            MCNetResultUnsupportedParameter        = 21,            /**< Parameter is not supported */
            MCNetResultNotAvailable                = 22,            /**< Requested action is not available at the moment */
			MCNetResultSubRequestFailed			   = 23,			/**< Initial request succeeded (i.e. playlist loaded), but actual stream request failed */
            MCNetResultBufferTooSmall              = 24,            /**< Buffer is too small */
            MCNetResultDisconnected                = 25,            /**< Disconnected */
            MCNetResultManifestNotDetected         = 26,            /**< Manifest type is not recognized */
            MCNetResultManifestParseFailed         = 27,            /**< Manifest failed to parse */
            MCNetResultConnectionRefused           = 28,            /**< Connection refused by the peer */
            MCNetResultUnknownError                = 0x7FFFFFFF     /**< Unknown Critical Error */
        } MCNETRESULT;

        /**
        * @brief Common network engine work states
        **/
        typedef enum _tagMCNetEngineStatus {
            MCNetEngineStatusStopped    = 0,                        /**< Engine is stopped */
            MCNetEngineStatusPlaying    = 1,                        /**< Engine is playing */
            MCNetEngineStatusRewinded   = 2,                        /**< Engine is rewinding */
            MCNetEngineStatusReady      = 3,                        /**< Engine is ready */
            MCNetEngineStatusStopping   = 4,                        /**< Engine is stopping */
            MCNetEngineStatusTrans2Play = 5,                        /**< Engine is transition to play state */
            MCNetEngineStatusPaused     = 6,                        /**< Engine is paused */
            MCNetEngineStatusResume     = 7,                        /**< Engine is resuming after pause */
            MCNetEngineStatusNotDefined = 0xffff                    /**< State is not defined */
        } MCNETENGINESTATUS;

		/**
        * @brief RTCP packet types
        **/
		typedef enum _tagRtcpPacketType {

			RtcpPacketTypeSR   = 200,								/**< Sender Report */
			RtcpPacketTypeRR   = 201,								/**< Receiver Report */
			RtcpPacketTypeSDES = 202,								/**< Source Description */
			RtcpPacketTypeBYE  = 203,								/**< Bye */
			RtcpPacketTypeAPP  = 204,								/**< Application-defined */
			RtcpPacketTypeEMPTY = 0									/**< Reserved */
		} RTCPPACKETTYPE;
		
        /**
        * @brief Counter of references
        **/
        class INetRefCounted
        {
        public:
            virtual ~INetRefCounted() {};

            /**
            * @brief Increment reference counter
            * 
            * @return count of references
            **/
            virtual int32_t AddRef()  = 0;

            /**
            * @brief Decrement reference counter and delete object when it reaches zero
            * 
            * @return current count of references
            **/
            virtual int32_t Release() = 0;
        };

        /**
        * @brief Declares abstract data reader interface
        **/
		class IDataSource : public INetRefCounted
		{
		public:
			virtual ~IDataSource() {}

			/**
            * @brief Seeks in stream to a given units offset
            * 
            * @param[in] i64Units        absolute position in stream
            * @return                    true when seek successful, false otherwise
            **/
			virtual bool Seek( int64_t i64Units ) = 0;

			/**
            * @brief Returns current position in stream
            * 
            * @param[out] i64Units       current position in stream; pointer must be valid
            * @return                    true when position has been retrieved successfully, false otherwise
            **/
			virtual bool GetPosition( int64_t *i64Units ) const = 0;

			/**
            * @brief Returns stream name
            * 
            * @return                    null terminated string with stream name or NULL if not available
            **/
			virtual const char * GetStreamName() const = 0;

			/**
            * @brief Returns complete stream length
            * 
            * @return                    stream length or -1 if not available
            **/
			virtual	int64_t GetLength() const = 0;

			/**
            * @brief Reads requested data size
            * 
            * @param[out] pBuff pre-allocated data buffer
			* @param[in] RequestLen data length to read
			* @param[out] pReadActual must be a valid pointer; represents actual amount of read data
            * @return                    true when read operation succeeded, false otherwise
            **/
			virtual	bool Read( uint8_t *pBuff, int32_t RequestLen, int32_t *pReadActual ) = 0;

			/**
            * @brief Indicates stream status
            * 
            * @return                    true when stream has been opened, false otherwise
            **/
			virtual bool IsReady() = 0;

			/**
            * @brief Retrieves last file modification time as UNIX timestamp
            * 
            * @return                    file time
            **/
			virtual int64_t GetFileLastModificationTime() = 0;

			/**
            * @brief Retrieves mime type for the given file
            * 
            * @param[in] bForceMimeTypeDetectionByExt when this argument set to true, mime type will be returned always for the knonw types; when this argument is set to false mime type will returned for the static objects only
            * @return                    null terminated mime string when success, otherwise NULL
            **/
			virtual const char * GetMimeType( bool bForceMimeTypeDetectionByExt = false ) = 0;
		};

        class IMCAttributeEnumerator : public INetRefCounted
        {
        public:
            virtual ~IMCAttributeEnumerator() {}

            /**
			* @brief Get count of custom attributes for this quality item
			* 
			* @return	Count of custom attributes
			**/
			virtual int32_t GetAttributeCount() const = 0;

            /**
			* @brief Get attribute value by index
			* 
			* @param[in] uiIndex	Index of attribute
			* @param[out] pName		Pointer that will receive attribute name. Can be NULL
			* @return	Attribute value string or NULL if index is out of bounds
			**/
			virtual const char *EnumAttributes( uint32_t uiIndex, const char **pName ) const = 0;

			/**
			* @brief Get attribute value by name
			* 
			* @param[in] pName	Name of attribute
			* @return	Attribute value string or NULL if not found
			**/
			virtual const char *GetAttributeValue( const char *pName ) const = 0;
        };

        class IMCResourceLocation
        {
        public:
            virtual ~IMCResourceLocation(){};
            virtual const char *GetURI(  ) const = 0;
            virtual const uint64_t GetStartRange( ) const = 0;
            virtual const uint64_t GetEndRange( ) const = 0;
        };

        /**
        * @brief Contains process specific information, required for sharing sockets
        **/
        class ISharedSocketInfo : public MainConcept::NetworkStreaming::INetRefCounted
        {
        public:
            virtual ~ISharedSocketInfo() {};

            /**
            * @brief Performs object instance serialization. 
            * 
            * @param[out] uiSize size of serialized object
            * @return            memory buffer with serialized object, which could be used for storing information out of process
            **/
            virtual const uint8_t * Serialize(uint32_t * uiSize) const = 0;
        };


        /**
        * @brief Receive remote sockets from another component or process
        **/
        class ISharedSocketReceiver : public MainConcept::NetworkStreaming::INetRefCounted
        {
        public:
            virtual ~ISharedSocketReceiver() {}

            /**
            * @brief Returns socket from remote component. Nonblocking call, you should use own thread function for repeating receiving until socket unavailable.
            * 
            * @param[out] ppSocket Socket instance from remote sender, could be NULL when socket is unavailable yet.
            * @return                    MainConcept::NetworkStreaming::MCNETRESULT
            **/
            virtual MainConcept::NetworkStreaming::MCNETRESULT Receive(CMCSockets** ppSocket) = 0;
        }; 

        /**
        * @brief Sends socket to another component or process
        **/
        class ISharedSocketSender : public MainConcept::NetworkStreaming::INetRefCounted
        {
        public:
            virtual ~ISharedSocketSender(){}

            /**
            * @brief Retrieves mime type for the given file
            * 
            * @param[in] pSocket  socket instance for sending
            * @param[in] pDest   pointer to ISharedSocketInfo, which have been got from remote component(from another process through Serialization operation)
            * @return                    MCNetResultOK on success, error code on fail.
            **/
            virtual MainConcept::NetworkStreaming::MCNETRESULT Send(const CMCSockets* pSocket, const ISharedSocketInfo* pDest) = 0;
        };
    };
};

#endif //__MC_NET_COMMON_H__
