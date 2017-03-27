/**
@file  parser_sdp.h
@brief SDP decoder/encoder and media info API's

@verbatim
File: parser_sdp.h
Desc: SDP decoder/encoder and media info API's

Copyright (c) 2015 MainConcept GmbH or its affiliates.  All rights reserved.

MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.  
This software is protected by copyright law and international treaties.  Unauthorized 
reproduction or distribution of any portion is prohibited by law.
@endverbatim
**/

#if !defined (__SDP_INTERFACE_H__)
#define __SDP_INTERFACE_H__

#include "mctypes.h"
#include "mcapiext.h"
#include "parser_sdp_defines.h"
#include "net_common.h"

/**
* @def SDPPARSER_API
* @brief Defines calling convention
* @hideinitializer
**/
#if defined(WIN32)
    #define SDPPARSER_API __cdecl
#else
    #define SDPPARSER_API
#endif

/**
* @brief SDP current version (see RFC2327)
* @hideinitializer
**/
#define SDP_PROTO_VER_0 0

/**
* @brief Biggest supported SDP packet
* @hideinitializer
**/
#define MAX_SDP_LENTGTH		0x20000

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

        class ISdpMediaInfo;
       
        /**
        * @brief This interface could be used for SDP text data parsing.
        * 
        * Contains whole SDP document.
        **/
        class ISdpDecoder : public INetRefCounted
        {
        public:
            virtual ~ISdpDecoder() {}

            /**
            * @brief Reads and recognizes text SDP document
            *
            * @param[in] aBuffer string representation with SDP document
            * @param[in] aLength size of the input string
            * @return            true - operation is complete; false - parsing failed
            **/
            virtual bool ParseSdp( const char *aBuffer, uint32_t aLength ) = 0;

            /**
            * @brief Retrieves the version of the SDP protocol from document (supported version is 0)
            *
            * @return version of SDP protocol
            **/
            virtual int32_t GetSdpVersion() const = 0;

            /**
            * @brief Retrieves session creator(owner) name 
            * 
            * @return char string (UTF-8 encoding) contains creator(owner) name
            **/
            virtual const char* GetSessionCreatorName() const = 0;

            /**
            * @brief Retrieves session identifier
            * 
            * @return session identifier
            **/
            virtual int64_t GetSessionID() const = 0;

            /**
            * @brief Retrieves session version
            * 
            * @return session version
            **/
            virtual int64_t GetSessionVersion() const = 0;

            /**
            * @brief Retrieves the host address of the session owner 
            * 
            * @return string representation of host address
            **/
            virtual const char * GetOriginAddress() const = 0;

            /**
            * @brief Retrieves address type of session owner host 
            * 
            * @return Returns @ref ADDRESSTYPE 
            **/
            virtual ADDRESSTYPE GetOriginAddressType() const = 0;

            /**
            * @brief Retrieves type of session owner network 
            * 
            * @return Returns @ref NETWORKTYPE
            **/
            virtual NETWORKTYPE GetOriginNetType() const = 0;

            /**
            * @brief Retrieves session name
            * 
            * @return char string (UTF-8 encoding) representation session name
            **/
            virtual const char * GetSessionName() const = 0;

            /**
            * @brief Retrieves URI for additional session info
            * 
            * @return char string (UTF-8 encoding) representation of URI
            **/
            virtual const char * GetURI() const = 0;

            /**
            * @brief Retrieves session description
            * 
            * @return char string (UTF-8 encoding) representation session description
            **/
            virtual const char * GetInfo() const = 0;

            /**
            * @brief Retrieves extended bandwidth modifier(if present in document)
            * 
            * @return string representation of bandwidth modifier
            **/
            virtual const char * UserDefinedBandWidthModifier() const = 0;

            /**
            * @brief Retrieves bandwidth field value
            * 
            * @return bandwidth value in kilobits per seconds
            **/
            virtual uint32_t BandWidthValue() const = 0;

            /**
            * @brief Retrieves bandwidth modifier type
            * 
            * @return Return @ref BANDWIDTHMODIFIER
            **/
            virtual BANDWIDTHMODIFIER GetModifierType() const = 0;

            /**
            * @brief This method enumerates bandwidth field by index
            * 
            * @param[in]  uiIndex          index number of bandwidth filed in document
            * @param[out] aBandwidth       bandwidth value in kilobits per second
            * @param[out] aModifierType    predefined type of modifier
            * @param[out] aUserDefinedTerm custom modifier presents if @a aModifierType equal @ref bandwidthModifierEX
            * @return                      0 if success otherwise negative value  
            **/
            virtual int32_t EnumBandWidthField( uint32_t uiIndex, uint32_t *aBandwidth, BANDWIDTHMODIFIER *aModifierType, const char **aUserDefinedTerm ) const = 0;

            /**
            * @brief Retrieves start time for a conference session or repeat sequence
            * 
            * @return NPT representation of start time
            **/
            virtual int64_t GetStartTime() const = 0;

            /**
            * @brief Retrieves stop time for a conference session or repeat sequence
            * 
            * @return NPT representation of stop time
            **/
            virtual int64_t GetStopTime()  const = 0;

            /**
            * @brief Retrieves time zone adjustment
            * 
            * @param[in]  aIndex        index number of time field on document
            * @param[in]  aIndex2       index number of zone adjustment field for selected time field
            * @param[in]  aIndex3       index number of zone adjustment times
            * @param[out] imBaseTime    base time zone time
            * @param[out] imTimeShift   shift from base time
            * @param[out] imShiftedTime calculated shifted time
            * @return                   negative if failed otherwise 0
            **/
            virtual int32_t GetZoneAdjustments( uint32_t aIndex, uint32_t aIndex2, 
                uint32_t aIndex3, int64_t *imBaseTime, 
                int64_t *imTimeShift, int64_t *imShiftedTime 
                ) const = 0;

            /**
            * @brief Retrieves repeat times for a session
            * 
            * @param[in]  aIndex             index number of time field    in document
            * @param[in]  aIndex2            index number of repeat field for selected time field
            * @param[out] aCount             number of time offsets in repeat times field
            * @param[out] iActiveDuration    duration of each playback session
            * @param[out] iRepeatInterval    interval between group of playback session
            * @param[out] iTimeOffsetsMatrix list of time offsets from start session time  
            * @return                        negative if failed, otherwise 0
            **/
            virtual int32_t GetTimeRepeats( uint32_t aIndex, uint32_t aIndex2, 
                uint32_t *aCount, int64_t *iActiveDuration, 
                int64_t *iRepeatInterval, int64_t **iTimeOffsetsMatrix 
                ) const = 0;

            /**
            * @brief Retrieves remote server address
            * 
            * @return string representation remote server network address
            **/ 
            virtual const char* GetConnectionAddress() const = 0;

            /**
            * @brief Retrieves remote server address type
            * 
            * @return Return @ref ADDRESSTYPE
            **/
            virtual ADDRESSTYPE GetConnectionAddressType() const = 0;

            /**
            * @brief Retrieves remote server network type
            * 
            * @return Return @ref NETWORKTYPE
            **/
            virtual NETWORKTYPE GetConnectionNetType() const = 0;

            /**
            * @brief Retrieves count of connection field or addresses in global section of document
            * 
            * @return count of connection field or addresses (0 for error )
            **/
            virtual int32_t GetConnectionAddressCount() const = 0;

            /**
            * @brief Retrieves TTL value
            * 
            * @return TTL value( 0 for error )
            **/
            virtual int32_t GetConnectionTTLValue() const = 0;

            /**
            * @brief Retrieves count of media section in document
            * 
            * @return count of media section ( 0 for error )
            **/ 
            virtual int32_t GetMediaCount()    const = 0;

            /**
            * @brief Retrieves media section descriptor by unique id
            * 
            * @param[in] nID unique identifier of media section
            * @return               valid pointer to ISdpMediaInfo or NULL if failed
            **/
            virtual const ISdpMediaInfo * GetMediaInfoInterface( uint32_t nID ) const = 0;

            /**
            * @brief Retrieves media section descriptor by index
            * 
            * @param[in] nIndex index number of media section in document
            * @return           valid pointer to @ref ISdpMediaInfo or NULL if failed
            **/
            virtual const ISdpMediaInfo * EnumMediaInfoInterfaces( uint32_t nIndex ) const = 0;

            /**
            * @brief Retrieves e-mail address associated with session by index number
            * 
            * @param[in] index index number of e-mail in document ( if presents several ) 
            * @return          string representation of address or NULL
            **/
            virtual const char* GetEmailFields( uint32_t index = 0 ) const = 0;

            /**
            * @brief Retrieves phone number associated with session by index number
            * 
            * @param[in] index index number of phone number in document ( if presents several ) 
            * @return          string representation of phone number or NULL
            **/
            virtual const char* GetPhoneFields( uint32_t index = 0 ) const = 0;

            /**
            * @brief Retrieves global attribute by its index in document 
            * 
            * @param[in]  aIndex1 index number global attribute field in document
            * @param[in]  aIndex2 index number attribute in attribute field
            * @param[out] aAttr   name of attribute
            * @param[out] aValue  value of attribute
            * @return             0 if success otherwise negative
            **/
            virtual int32_t GetAttributesField( uint32_t aIndex1, uint32_t aIndex2, const char **aAttr, const char **aValue ) const = 0;

            /**
            * @brief Retrieves count of attributes at attribute field 
            * 
            * @param aIndex index number of global attribute field
            * @return count of attribute in attribute fields
            **/
            virtual int32_t GetCountOfAttributes( uint32_t aIndex )    const = 0;

            /**
            * @brief Retrieves attribute value by its name
            * 
            * @param[in] aAttrName attribute name
            * @return              attribute value or NULL 
            **/
            virtual const char * GetAttrValueByName( const char *aAttrName ) const = 0;

            /**
            * @brief Retrieves decryption key value or URI where key can be obtained 
            * 
            * @return string representation of key value or URI
            **/
            virtual const char * GetKey() const = 0;

            /**
            * @brief Retrieves encryption method
            * 
            * @return Return @ref ENCRYPTIONMETHOD
            **/
            virtual ENCRYPTIONMETHOD GetKeyEncryptionMethod() const = 0;

            /**
            * @brief SDP Document validation routine
            * 
            * @return true if document is correct otherwise false
            **/
            virtual bool IsValid() const = 0;

            /**
            * @brief Retrieves string representation of SDP document
            * 
            * @param[out] aDataLength size of document
            * @return                 string representation of document or NULL
            **/
            virtual const char * GetSdpBuffer( uint32_t *aDataLength ) const = 0;
        };

        /**
        * @brief Class describes descriptor of rtpmap SDP attribute
        **/
        class ISdpMediaRtpMap
        {
        public:
            virtual ~ISdpMediaRtpMap() {}

            /**
            * @brief Retrieves stream type from rtpmap attribute 
            * 
            * @return Return @ref STREAMTYPE
            **/
            virtual STREAMTYPE GetStreamType() const = 0;

            /**
            * @brief Retrieves value of payload type from rtpmap attribute
            * 
            * @return numeric representation of payload type
            **/
            virtual uint32_t GetPayloadType() const = 0;

            /**
            * @brief Retrieves media stream clock rate
            * 
            * @return clock rate
            **/
            virtual uint32_t GetClockRate() const = 0;

            /**
            * @brief Retrieves audio channel count
            * 
            * @return audio channels count
            **/
            virtual uint8_t GetChannelCount() const = 0;
        };

        /**
        * @brief SDP Media section parser interface
        **/
        class ISdpMediaInfo
        {
        public:
            virtual ~ISdpMediaInfo() {}

            /**
            * @brief Retrieves media type.
            * 
            * Represents "m=" field from SDP
            * @return Return @ref MEDIATYPE
            **/
            virtual MEDIATYPE GetMediaType() const = 0;

            /**
            * @brief Retrieves network transport protocol 
            * 
            * @return Return @ref PROTOCOL
            **/
            virtual PROTOCOL GetProtocol() const = 0;

            /**
            * @brief Retrieves network profile
            * 
            * @return Return @ref NETPROFILETYPE
            **/
            virtual NETPROFILETYPE GetProfile() const = 0;

            /**
            * @brief Retrieves lower transport protocol
            * 
            * @return @ref LOWERTRANSPORTTYPE
            **/
            virtual LOWERTRANSPORTTYPE GetLowTransport() const = 0;

            /**
            * @brief Retrieves media port
            *
            * @return media port
            **/
            virtual uint32_t GetPort() const = 0;

            /**
            * @brief Retrieves count of media ports
            * 
            * @return count of media port
            **/
            virtual uint32_t GetPortCount() const = 0;

            /**
            * @brief Retrieves numeric payload type
            * 
            * @return numeric representation on payload type
            **/
            virtual uint32_t GetPayloadType() const = 0;

            /**
            * @brief Retrieves custom protocol description ( if present )
            * 
            * @return string representation of protocol description
            **/
            virtual const char *GetProtocolEx() const = 0;

            /**
            * @brief This method enumerates rtpmap field by its index number 
            * 
            * @param[in] uiIndex index number of rtpmap field
            * @return            valid pointer to ISdpMediaRtpMap or NULL
            **/
            virtual const ISdpMediaRtpMap * EnumRtpMap( uint32_t uiIndex ) const = 0;

            /**
            * @brief This method enumerates stream type by its index number
            * 
            * @param[in] uiIndex index number of payload type in media field
            * @return            Return @ref STREAMTYPE
            **/
            virtual STREAMTYPE EnumPayloadType( uint32_t uiIndex ) const = 0;

            /**
            * @brief Retrieves unique media identifier
            * 
            * @return unique id
            **/
            virtual uint32_t GetID() const = 0;

            /**
            * @brief Retrieves media title or media description
            * 
            * @return char string (UTF-8 encoding) representation of title or description or NULL
            **/
            virtual const char * GetMediaTitle() const = 0;

            /**
            * @brief Retrieves media section specific key field
            * 
            * @param[in] aKey           value of decryption key or URI where can obtain key
            * @param[in] aEncryptMethod specified key or URI contains in field
            * @return                   0 if success otherwise negative
            **/ 
            virtual int32_t GetKeyField( const char **aKey, ENCRYPTIONMETHOD *aEncryptMethod ) const = 0;

            /**
            * Retrieves values from media specific bandwidth field.
            * 
            * Represents "b=" field
            * 
            * @param[out] aBandwidth       numeric representation of bandwidth in kilobits per seconds
            * @param[out] aModifierType    type of bandwidth value
            * @param[out] aUserDefinedTerm custom bandwidth type presents if @a aModifierType == @ref bandwidthModifierEX
            * @return                      0 for success otherwise negative
            **/
            virtual int32_t GetBandWidthField( uint32_t *aBandwidth, BANDWIDTHMODIFIER *aModifierType, const char **aUserDefinedTerm ) const = 0;

            /**
            * @brief This method enumerates media specific bandwidth fields
            * 
            * @param[in]  uiIndex          index number of field
            * @param[out] aBandwidth       value of bandwidth
            * @param[out] aModifierType    predefined type of bandwidth
            * @param[out] aUserDefinedTerm custom type of bandwidth
            * @return                      0 for success otherwise negative
            **/
            virtual int32_t EnumBandWidthField( uint32_t uiIndex, uint32_t *aBandwidth, BANDWIDTHMODIFIER *aModifierType, const char **aUserDefinedTerm ) const = 0;

            /**
            * @brief Retrieves count of media specific connection address
            * 
            * @return count of media specific connection address
            **/
            virtual int32_t GetNumOfAddress()  const = 0;

            /**
            * @brief Retrieves media specific TTL value
            * 
            * @return TTL value
            **/
            virtual int32_t GetTTLValue()       const = 0;

            /**
            * @brief Retrieves media specific connection address
            * 
            * @return network connection address or NULL
            **/
            virtual const char* GetAddress() const = 0;

            /**
            * @brief Retrieves connection address type
            * 
            * @return Return @ref ADDRESSTYPE
            **/
            virtual ADDRESSTYPE GetAddressType() const = 0;

            /**
            * @brief Retrieves network type of connection address
            * 
            * @return Return @ref NETWORKTYPE
            **/
            virtual NETWORKTYPE GetNetType()     const = 0;

            /**
            * @brief Retrieves media specific attribute value
            * 
            * @param[in]  aIndex          index number of attribute field in media section
            * @param[in]  aAttributeIndex index number of attribute in attribute field
            * @param[out] aAttr           string name of attribute
            * @param[out] aValue          value of attribute
            * @return                     0 for success otherwise negative
            **/
            virtual int32_t GetAttributeFields ( uint32_t aIndex, uint32_t aAttributeIndex, const char **aAttr, const char **aValue ) const = 0;

            /**
            * @brief Retrieves count of media specific attribute in attribute fields
            * 
            * @param[in] aIndex index number of attribute field
            * @return           count of attribute
            **/
            virtual int32_t GetAttributeCount( uint32_t aIndex )    const = 0;

            /**
            * @brief Retrieves media specific attribute value by name
            * 
            * @param[in] aAttrName string name of attribute
            * @return              value of attribute or NULL
            **/
            virtual const char * GetAttrValueByName( const char *aAttrName ) const = 0;

            /**
            * @brief Retrieves stream type of media
            * 
            * @return Return @ref STREAMTYPE
            **/
            virtual STREAMTYPE GetStreamType() const = 0;

            /**
            * @brief Retrieves entire stream type descriptor
            * 
            * @return stream type descriptor or NULL
            **/
            virtual const char * GetExtendedStreamType() const = 0;

            /**
            * Retrieves decoder specific config or sequence header
            * 
            * @param[out] ulLen size of config
            * @return           specific config, sequence header or NULL
            **/
            virtual const uint8_t *GetSequenceHeader(uint32_t *ulLen) const = 0;
        };

        /**
        * @brief SDP Media section producer interface
        **/ 
        class ISdpMediaInfoEncoder
        {
        public:
            virtual ~ISdpMediaInfoEncoder() {}

            /**
            * @brief Sets title media or description media.
            * 
            * Represents "i=" field
            * 
			* @param[in] aBuff	New value
			* @param[in] aLen	New value length
            * @return None
            **/
            virtual void SetMediaInformation( const char *aBuff, const int32_t aLen ) = 0;

            /**
            * @brief Sets type for media data
            * 
            * @param[in] aType type of media data
            * @return          None
            **/
            virtual void SetMediaType( MEDIATYPE aType ) = 0;

            /**
            * @brief Sets media specific network protocol
            * 
            * @param[in] aProto type of protocol
            * @return           None
            **/
            virtual void SetProtocol( PROTOCOL aProto ) = 0;

            /**
            * @brief Sets lower transport protocol
            * 
            * @param[in] aTransportType type of lower transport protocol
            * @return                   None
            **/
            virtual void SetLowTransport( LOWERTRANSPORTTYPE aTransportType ) = 0;

            /**
            * @brief Sets network profile
            * 
            * @param[in] aNetProfile profile
            * @return                None
            **/
            virtual void SetProfile( NETPROFILETYPE aNetProfile ) = 0;

            /**
            * @brief Sets custom user protocol
            * 
			* @param[in] aBuff	New value
			* @param[in] aLen	New value length
            * @return None
            **/
            virtual void SetUserDefinedProtocol( const char *aBuff, const int32_t aLen ) = 0;

            /**
            * @brief Sets media port
            * 
            * @param[in] aValue media port
            * @return           None
            **/
            virtual void SetPort( uint32_t aValue )      = 0;

            /**
            * @brief Sets range of using port
            * 
            * @param[in] aValue count of media port
            * @return           None
            **/
            virtual void SetPortCount( uint32_t aValue ) = 0;

            /**
            * @brief Sets stream type
            * 
            * @param[in] aValue numeric representation of stream type
            * @return           None
            **/
            virtual void SetPayloadType( uint32_t aValue ) = 0;

            /**
            * @brief This method defines way of transfer decryption key 
            * 
            * @param[in] aMethod kind of transfer key
            * @return            None
            **/
            virtual void SetKeyFieldEncryptionMethod( ENCRYPTIONMETHOD aMethod ) = 0;

            /**
            * @brief Sets decryption key value
            * 
			* @param[in] aBuff	New value
			* @param[in] aLen	New value length
            * @return None
            **/
            virtual void SetKeyFieldKey( const char *aBuff, const int32_t aLen ) = 0;

            /**
            * @brief Clears key field
            * 
            * @return None
            **/
            virtual void RemoveKeyField() = 0;

            /**
            * @brief Fills bandwidth( b= ) field 
            * 
			* @param[in] aNewName		Attribute name
			* @param[in] aNewValue		Attribute value
			* @param[in] aNewNameLen	Attribute name length
			* @param[in] aNewValueLen	Attribute value length
            * @return None
            **/
            virtual void SetBandWidthField( const char *aNewName, const char *aNewValue, const int32_t aNewNameLen, const int32_t aNewValueLen ) = 0;

            /**
            * @brief Sets bandwidth modifier (for single field)
            * 
			* @param[in] aBuff	New value
			* @param[in] aLen	New value length
            * @return None
            **/
            virtual void SetBandWidthModifier( const char *aBuff, const int32_t aLen ) = 0;

            /**
            * @brief Sets bandwidth value (for single field)
            * 
            * @param[in] aValue new bandwidth
            * @return           None
            **/
            virtual void SetBandWidthValue( uint32_t aValue ) = 0;

            /**
            * @brief Clears bandwidth field (for single field)
            * 
            * @return None
            **/
            virtual void RemoveBandWidthField() = 0;

            /**
            * @brief Clears bandwidth field (for multiple fields)
            * 
			* @param[in] aNewName		Attribute name
			* @param[in] aNewValue		Attribute value
			* @param[in] aNewNameLen	Attribute name length
			* @param[in] aNewValueLen	Attribute value length
            * @return None
            **/
            virtual void RemoveBandWidthField( const char *aNewName, const char *aNewValue, const int32_t aNewNameLen, const int32_t aNewValueLen ) = 0;

            /**
            * @brief Sets connection network type
            * 
            * @param[in] aType network type
            * @return          None
            **/
            virtual void SetConnectionFieldNetworkType( NETWORKTYPE aType ) = 0;

            /**
            * @brief Sets connection address type
            * 
            * @param[in] aType type of network address
            * @return          None
            **/
            virtual void SetConnectionFieldAddressType( ADDRESSTYPE aType ) = 0;

            /**
            * @brief Sets connection field with address
            * 
			* @param[in] aBuff	New value
			* @param[in] aLen	New value length 
            * @return None
            **/
            virtual void SetConnectionFieldAddress( const char *aBuff, const int32_t aLen ) = 0;

            /**
            * @brief Sets connection field TTL value 
            * 
            * @param[in] aValue new TTL value
            * @return           None
            **/
            virtual void SetConnectionFieldTTL( uint8_t aValue = 64 ) = 0;

            /**
            * @brief Sets range of connections address
            * 
            * @param[in] aValue count of consecutive network address
            * @return           None
            **/
            virtual void SetConnectionFieldAddressCount( uint8_t aValue = 0 ) = 0;

            /**
            * @brief Removes connection field
            * 
            * @return None
            **/
            virtual void RemoveConnectionField() = 0;

            /**
            * @brief Adds new attribute field to media section
            * 
			* @param[in] aNewName		Attribute name
			* @param[in] aNewValue		Attribute value
			* @param[in] aNewNameLen	Attribute name length
			* @param[in] aNewValueLen	Attribute value length
            * @return None
            **/
            virtual void SetNewAtrribute( const char *aNewName, const char *aNewValue, const int32_t aNewNameLen, const int32_t aNewValueLen ) = 0;

            /**
            * @brief Removes attribute field from media section
            * 
			* @param[in] aBuff	New value
			* @param[in] aLen	New value length
            * @return None
            **/
            virtual void RemoveAttribute( const char *aBuff, const int32_t aLen )           = 0;

            /**
            * @brief Retrieves complete media section decoder
            * 
            * @return valid pointer to @ref ISdpMediaInfo or NULL if failed
            **/
            virtual const ISdpMediaInfo* GetMediaInfo() = 0;
        };

        /**
        * @brief SDP document producer interface
        **/ 
        class ISdpEncoder : public INetRefCounted
        {
        public:
            virtual ~ISdpEncoder() {}

            /**
            * @brief Sets SDP version
            * 
            * @param[in] aValue SDP version (currently 0, see RFC 2327/4566)
            * @return           None
            **/
            virtual void SetSdpProtocolVersion( uint32_t aValue = 0 ) = 0;

            /**
            * @brief Sets session name (title)
            * 
			* @param[in] aBuff	New value
			* @param[in] aLen	New value length
            * @return None
            **/
            virtual void SetCurrentSessionName( const char *aBuff, const int32_t aLen ) = 0;

            /**
            * @brief Sets session additional description 
            * 
			* @param[in] aBuff	New value
			* @param[in] aLen	New value length
            * @return None
            **/
            virtual void SetCurrentSessionInfo( const char *aBuff, const int32_t aLen ) = 0;

            /**
            * @brief Sets URI to additional information about conference
            * 
			* @param[in] aBuff	New value
			* @param[in] aLen	New value length
            * @return None
            **/
            virtual void SetCurrentUri( const char *aBuff, const int32_t aLen ) = 0;

            /**
            * @brief Sets session creator name
            * 
			* @param[in] aBuff	New value
			* @param[in] aLen	New value length 
            * @return None
            **/
            virtual void SetOriginFieldCreatorName( const char *aBuff, const int32_t aLen ) = 0;

            /**
            * @brief Sets session identifier
            * 
            * @param[in] aValue session id value 
            * @return           None
            **/
            virtual void SetOriginFieldSessionID( int64_t aValue ) = 0;

            /**
            * @brief Sets session version
            * 
            * @param[in] aValue session version value 
            * @return           None
            **/
            virtual void SetOriginFieldSessionVersion( int64_t aValue ) = 0;

            /**
            * @brief Sets session creator network type
            * 
            * @param[in] aType network type
            * @return          None
            **/
            virtual void SetOriginFieldNetworkType( NETWORKTYPE aType ) = 0;

            /**
            * @brief Sets session creator address type
            * 
            * @param[in] aType address type
            * @return None
            **/
            virtual void SetOriginFieldAddressType( ADDRESSTYPE aType ) = 0;

            /**
            * @brief Sets session creator host address
            * 
			* @param[in] aBuff	New value
			* @param[in] aLen	New value length
            * @return None
            **/
            virtual void SetOriginFieldAddress( const char *aBuff, const int32_t aLen ) = 0;

            /**
            * @brief Sets network type of global connection address
            * 
            * @param[in] aType network type
            * @return          None
            **/
            virtual void SetConnectionFieldNetworkType( NETWORKTYPE aType ) = 0;

            /**
            * @brief Sets address type of global connection address
            * 
            * @param[in] aType address type
            * @return          None
            **/
            virtual void SetConnectionFieldAddressType( ADDRESSTYPE aType ) = 0;

            /**
            * @brief Sets global connection address 
            * 
			* @param[in] aBuff	New value
			* @param[in] aLen	New value length
            * @return None
            **/
            virtual void SetConnectionFieldAddress( const char *aBuff, const int32_t aLen ) = 0;

            /**
            * @brief Sets global TTL value
            * 
            * @param[in] aValue new TTL value
            * @return           None
            **/
            virtual void SetConnectionFieldTTL( uint8_t aValue = 64 ) = 0;

            /**
            * @brief Sets range of connection address
            * 
            * @param[in] aValue count of serial addresses 
            * @return           None
            **/
            virtual void SetConnectionFieldAddressCount( uint8_t aValue = 0 ) = 0;

            /**
            * @brief Sets kind of obtaining encryption key 
            *
            * @param[in] aMethod obtaining method
            * @return            None
            **/
            virtual void SetKeyFieldEncryptionMethod( ENCRYPTIONMETHOD aMethod ) = 0;

            /**
            * @brief Sets key value or URI of its placement
            * 
            * @see SetKeyFieldEncryptionMethod
			*
			* @param[in] aBuff	New value
			* @param[in] aLen	New value length
            * @return None
            **/
            virtual void SetKeyFieldKey( const char *aBuff, const int32_t aLen ) = 0;

            /**
            * @brief Sets e-mail associated with session
            * 
			* @param[in] aBuff	New value
			* @param[in] aLen	New value length
            * @return None
            **/
            virtual void SetEmailField( const char *aBuff, const int32_t aLen ) = 0;

            /**
            * @brief Sets phone number(as extra session information )
            * 
			* @param[in] aBuff	New value
			* @param[in] aLen	New value length
            * @return None
            **/
            virtual void SetPhoneField( const char *aBuff, const int32_t aLen ) = 0;

            /**
            * @brief Adds global section attribute (a=)
            * 
			* @param[in] aNewName		Attribute name
			* @param[in] aNewValue		Attribute value
			* @param[in] aNewNameLen	Attribute name length
			* @param[in] aNewValueLen	Attribute value length
            * @return None
            **/
            virtual void SetGlobalAttribute( const char *aNewName, const char *aNewValue, const int32_t aNewNameLen, const int32_t aNewValueLen ) = 0;

            /**
            * @brief Sets(or adds ) global bandwidth field
            * 
			* @param[in] aNewName		Attribute name
			* @param[in] aNewValue		Attribute value
			* @param[in] aNewNameLen	Attribute name length
			* @param[in] aNewValueLen	Attribute value length
            * @return None
            **/
            virtual void SetBandWidthField( const char *aNewName, const char *aNewValue, const int32_t aNewNameLen, const int32_t aNewValueLen ) = 0;

            /**
            * @brief Sets bandwidth modifier (for single field)
            * 
			* @param[in] aBuff	New value
			* @param[in] aLen	New value length
            * @return None
            **/
            virtual void SetBandWidthModifier( const char *aBuff, const int32_t aLen ) = 0;

            /**
            * @brief Sets bandwidth value (for single field)
            * 
            * @param[in] aValue new bandwidth value (in kilobits per seconds)
            * @return           None
            **/
            virtual void SetBandWidthValue( uint32_t aValue ) = 0;

            /**
            * @brief Retrieves new media section encoder
            * 
            * This method adds new empty media section to SDP document and return pointer to its encoder
            * 
            * @return valid pointer to @ref ISdpMediaInfoEncoder or NULL
            **/
            virtual ISdpMediaInfoEncoder * GetMediaInfoEncoderInterface() = 0;

            /**
            * @brief Sets start time of media session
            *
			* @param[in] aBuff	New value
			* @param[in] aLen	New value length 
            * @return None
            **/
            virtual void SetStartTime( const char *aBuff, const int32_t aLen ) = 0;

            /**
            * @brief Sets stop time of media session
            *
			* @param[in] aBuff	New value
			* @param[in] aLen	New value length
            * @return None
            **/
            virtual void SetStopTime( const char *aBuff, const int32_t aLen ) = 0;

            /**
            * @brief Removes global key field(k=)
            * 
            * @return None
            **/
            virtual void RemoveKeyField() = 0;

            /**
            * @brief Remove e-mail field
            * 
			* @param[in] aBuff	New value
			* @param[in] aLen	New value length
            * @return None
            **/
            virtual void RemoveEmailField( const char *aBuff, const int32_t aLen ) = 0;

            /**
            * @brief Removes phone number field
            * 
			* @param[in] aBuff	New value
			* @param[in] aLen	New value length
            * @return None
            **/
            virtual void RemovePhoneField( const char *aBuff, const int32_t aLen ) = 0;

            /**
            * @brief Removes global attribute field
            * 
			* @param[in] aBuff	New value
			* @param[in] aLen	New value length
            * @return None
            **/
            virtual void RemoveGlobalAttribute( const char *aBuff, const int32_t aLen ) = 0;

            /**
            * @brief Removes session information field
            * 
            * @return None
            **/
            virtual void RemoveInfo() = 0;

            /**
            * @brief Removes URI field
            * 
            * @return None
            **/
            virtual void RemoveUri()  = 0;

            /**
            * @brief Removes session name (title)
            * 
            * @return None
            **/
            virtual void RemoveSessionName() = 0;

            /**
            * @brief Removes bandwidth field (for single field in document)
            * 
            * @return None
            **/
            virtual void RemoveBandWidthField() = 0;

            /**
            * @brief Removes bandwidth field (for multiple fields in document)
            * 
			* @param[in] aNewName		Attribute name
			* @param[in] aNewValue		Attribute value
			* @param[in] aNewNameLen	Attribute name length
			* @param[in] aNewValueLen	Attribute value length
            * @return None
            **/
            virtual void RemoveBandWidthField( const char *aNewName, const char *aNewValue, const int32_t aNewNameLen, const int32_t aNewValueLen ) = 0;

            /**
            * @brief Removes entire media section 
            * 
            * @param[in] aSdpMediaDescriptor pointer to @ref ISdpMediaInfo for removing
            * @return None
            **/
            virtual void RemoveMediaField( ISdpMediaInfo *aSdpMediaDescriptor ) = 0;

            /**
            * @brief Retrieves complete SDP document
            * 
            * @return valid pointer to @ref ISdpDecoder
            **/
            virtual const ISdpDecoder* GetDocument()  = 0;
        };

#if defined (__cplusplus)
        extern "C" 
        {
#endif
            /**
            * @brief Creates instance of new SDP decoder object
            * 
            * @param[in]  get_rc Pointer to get_rc memory manager implementation or NULL to use standard allocators
            * @return            valid pointer to @ref ISdpDecoder or NULL
            **/
            ISdpDecoder* SDPPARSER_API GetSdpDecoderInterface( void *(MC_EXPORT_API *get_rc)(const char*) );

            /**
            * @brief Creates instance of new SDP encoder object
            * 
            * @param[in] get_rc Pointer to get_rc memory manager implementation or NULL to use standard allocators
            * @return           valid pointer to @ref ISdpEncoder or NULL
            **/
            ISdpEncoder* SDPPARSER_API GetSdpEncoderInterface( void *(MC_EXPORT_API *get_rc)(const char*) );

            /**
            * @brief Offers extended API to module
            * 
            * @param[in] func identifier of requested function
            * @return         valid pointer to function or NULL
            **/
            APIEXTFUNC SDPPARSER_API GetSdpGetAPIExt(uint32_t func);
#if defined (__cplusplus)
        }
#endif
    };
};

#endif // __SDP_INTERFACE_H__
