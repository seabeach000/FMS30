/**
@file tools.h
@brief Declaration of internal utils
@verbatim
  File: tools.h
 
  Desc: Declaration of internal utils
 
  Copyright (c) 2015 MainConcept GmbH or its affiliates.  All rights reserved.

  MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.
  This software is protected by copyright law and international treaties.  Unauthorized
  reproduction or distribution of any portion is prohibited by law.
@endverbatim
 */

#if !defined (__MC_TOOLS_H__)
#define __MC_TOOLS_H__

#include <time.h>

#if defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#endif

#include "nutil_api.h"
#include "mcsockets.h"

#define BASE64_FLAG_NOPAD	1
#define BASE64_FLAG_NOCRLF  2

#if defined (__cplusplus)
extern "C" {
#endif

    MCCONNECTIONTYPE MC_NET_UTILS_API GetConnectionTypeFromAddress(const sockaddr_storage *res_addr_info);

    /**
    * @brief Matches a list of extensions to the given URL
    *
    * @param[in]	pUrl		    null terminated URL string for examination
    * @param[in]	pExtensions		array of null terminated strings with extensions
    *
    * @return		true when given URL has any of specified extensions
    **/
    bool MC_NET_UTILS_API UrlHasExtension(const char *pUrl, const char **pExtensions);

	/** 
	* @brief Convert IP address string to socket address
	* 
	* @param[in]	af		Address family
	* @param[in]	src		IP address string
	* @param[out]	dst		Buffer to hold socket address, must be big enough to hold socket address for specified address family
	* @param[out]	scope	Pointer to int that will hold IPv6 scope id if address family is set to AF_INET6, can be NULL
	*
	* @return		1 on success and 0 on error
	**/
	int32_t MC_NET_UTILS_API InetPtoN(int32_t af, const char *src, void *dst, uint32_t *scope = NULL);

	/** 
	* @brief Convert socket address to IP address string
	* 
	* @param[in]	af		Address family
	* @param[in]	src		Socket address
	* @param[out]	dst		Buffer to hold IP address string, should be big enough to contain address string and terminating NULL character
	* @param[out]	size	Size of dst buffer
	*
	* @return		1 on success and 0 on error
	**/
	const char * MC_NET_UTILS_API InetNtoP(int32_t af, const void *src, char *dst, size_t size);

	/** 
	* @brief Convert string with IP address and port to socket address
	*
	* @param[in]	pAddress		String with IP address and port (optional) in format address:port
	* @param[in]	iAddressLen		Length of address string
	* @param[out]	pSockaddr		Pointer to socket address structure that will receive result
	* @param[in]	iDefaultPort	Port number to use if IP address string does not contain port
	* @param[in]	lalloc			Pointer to memory allocation function, can be NULL to use standard allocation function
	* @param[in]	lfree			Pointer to memory freeing function, can be NULL to use standard freeing function
	*
	* @return		0 on success, -1 on error
	**/
	int32_t MC_NET_UTILS_API ParseAddressWithPort(const char *pAddress, int32_t iAddressLen, sockaddr_storage *pSockaddr, int32_t iDefaultPort, void* (*lalloc)(size_t), void (*lfree)(void*));

	/** 
	* @brief Split URL to individual parts
	*
	* URL should be in format "proto://user:password@address:port/uri". Optional fields are: user, password, port.
	* Caller is responsible for releasing returned strings.
	*
	* @param[in]	pURI			URL to parse
	* @param[out]	szPath			URI part of the URL, including leading slashes
	* @param[out]	uiPort			Port number, if present in URL
	* @param[out]	szServerName	Server address
	* @param[out]	pUserName		Username, if present in URL
	* @param[out]	pPassword		Password, if present in URL
	* @param[in]	lalloc			Pointer to memory allocation function, can be NULL to use standard allocation function
	* @param[in]	lfree			Pointer to memory freeing function, can be NULL to use standard freeing function
	*
	* @return		0 on success, -1 on error
	**/
	int32_t MC_NET_UTILS_API ParseFullUrl( const char *pURI, char **szPath, uint16_t &uiPort, char **szServerName, char **pUserName, char **pPassword, void* (*lalloc)(size_t), void  (*lfree)(void*) );


	/** 
	* @brief Check if IPv4 address is a multicast address
	* 
	* @param[in]	dwIP		IPv4 address in network byte order
	*
	* @return		true if address is a multicast address, false otherwise
	**/
	bool MC_NET_UTILS_API IsMulticastIP ( int32_t dwIP /*network order*/ );

	/** 
	* @brief Check if IPv4 address is an unicast address
	* 
	* @param[in]	dwIP		IPv4 address in network byte order
	*
	* @return		true if address is a unicast address, false otherwise
	**/
	bool MC_NET_UTILS_API IsUnicastIP ( int32_t dwIP /*network order*/ );


	/** 
	* @brief Check if string represents IPv4 or IPv6 address
	*
	* This call does not make any validity checks and should only be used to distinguish IP address from DNS host name.
	*
	* @param[in]	aIP		IP address string
	*
	* @return		1 if string contains IP address, 0 otherwise
	**/
	int MC_NET_UTILS_API isIPAddress( const char *aIP );

	/** 
	* @brief Convert byte array to hex string
	* 
	* @param[in]	aBuffer		Source byte array
	* @param[in]	SrcLen		Count of bytes in source array (excluding trailing NULL character in case of C string)
	* @param[out]	aDstBuffer	Buffer to hold resulting hex string, must be at least SrcLen*2+1 bytes to hold hex string and terminating NULL character
	* @param[in]	DstLen		Length of destination buffer
	*
	* @return		Length of hex string excluding NULL character, or -1 on error
	**/
	int MC_NET_UTILS_API ConvertValueToHexString( unsigned char *aBuffer, int SrcLen, char *aDstBuffer, int DstLen );

	/** 
	* @brief Encode byte array using base64 algorithm
	* 
	* @param[in]		pbSrcData	Source byte array
	* @param[in]		nSrcLen		Count of bytes in source array
	* @param[in]		szDest		Buffer to hold resulting hex string, must be at least SrcLen*2+1 bytes to hold hex string and terminating NULL character
	* @param[in,out]	pnDestLen	Length of destination buffer, use @ref Base64EncodeGetRequiredLength to determine required length. Will contain result data length on successful run.
	* @param[in]		dwFlags		A set of flags to control output. Use BASE64_FLAG_NOPAD to avoid padding at the end and BASE64_FLAG_NOCRLF to avoid splitting result into multiple lines
	*
	* @return		true if conversion was successful, false on error
	**/
	bool MC_NET_UTILS_API Base64Encode(const unsigned char *pbSrcData, int nSrcLen, char *szDest, int *pnDestLen, unsigned long dwFlags = BASE64_FLAG_NOCRLF);

	/** 
	* @brief Calculate buffer size, required to hold base64-encoded data for specified count of bytes
	* 
	* @param[in]	nSrcLen		Count of bytes to encode
	* @param[in]	dwFlags		A set of flags to control output. See @ref Base64Encode
	*
	* @return		Length in bytes of base64 encoded buffer
	**/
	int MC_NET_UTILS_API  Base64EncodeGetRequiredLength(int nSrcLen, unsigned long dwFlags=BASE64_FLAG_NOCRLF);

	/** 
	* @brief Get byte value of base64 char
	* 
	* @param[in]	ch		Base64 character
	*
	* @return		Byte value on success, or -1 if input character is not a valid base64 character
	**/
	int MC_NET_UTILS_API DecoderForBase64Char( unsigned int ch );

	/** 
	* @brief Decode base64 string into byte array
	* 
	* @param[in]		szSrc		Base64-encoded string
	* @param[in]		nSrcLen		Length of source string
	* @param[out]		pbDest		Destination buffer
	* @param[in,out]	pnDestLen	Length of destination buffer, will contain resulting length on successful run
	*
	* @return		true if conversion was successful, false on error
	**/
	bool MC_NET_UTILS_API Base64Decoder( const char *szSrc, int nSrcLen, unsigned char *pbDest, int *pnDestLen );

	/** 
	* @brief Convert hex string to byte array
	* 
	* @param[in]	aBuffer		Source hex string
	* @param[in]	SrcLen		Length of hex string
	* @param[out]	aDstBuffer	Buffer to hold resulting byte array, must be at least SrcLen/2 bytes to hold result
	* @param[in]	DstLen		Length of destination buffer
	*
	* @return		Count of bytes written into destination buffer
	**/
	int MC_NET_UTILS_API ConvertHexStringToValue( const char *aBuffer, int SrcLen, unsigned char *&aDstBuffer, int DstLen );


	/** 
	* @brief Make random identifier
	* 
	* @param[in]	iSeed		User-defined seed value, used as additional source of data for hash generator.
	*
	* @return		Random identifier
	**/
	int64_t MC_NET_UTILS_API GetNewSessionVersion( int64_t iSeed );


	/** 
	* @brief Check if port can be bound
	* 
	* @param[in]	aPort		Port number to check
	* @param[in]	pNIC		Address to bind to
	* @param[in]	aProto		Protocol type
	*
	* @return		Success if port can be bound, PortAlreadyInUse if port is in use, or error code otherwise
	**/
	MCSOCKETSERRORS MC_NET_UTILS_API IsPortBusy( int32_t aPort, const char *pNIC, int32_t aProto = IPPROTO_UDP );

	/** 
	* @brief Get connection type for IP address or host name
	* 
	* @param[in]	aServerIP		IP address or host name
	*
	* @return		Connection type for address, or isUnknownConnectionType on error
	**/
	MCCONNECTIONTYPE MC_NET_UTILS_API GetConnectionType( const char *aServerIP );

	/** 
	* @brief Get IP address for host name
	*
	* @param[in]		aServerName			Host name to be resolved. IP address string is also accepted
	* @param[in]		aResolvedName		IP address string for specified host name
	* @param[in,out]	aResolvedNameLen	Length of destination buffer, will be set to IP address string length on successful run. Set to 0 on error
	* @param[in]		aAddressFamily		Address family to search for when resolving. Can be AF_UNSPEC.
	*
	* @return		true when dns was resolved gracefully; false otherwise
	**/
    bool MC_NET_UTILS_API DNSResolve(const char *aServerName, sockaddr_storage *aResolvedName, uint32_t aAddressFamily = PF_UNSPEC);

	/** 
	* @brief Check if string represents IPv6 address
	*
	* Can also accept host name - in this case first resolved address is checked.
	*
	* @param[in]	aAddress		String with address or host name
	*
	* @return		true if IPv6 address found, false otherwise
	**/
	bool MC_NET_UTILS_API IsIPv6( const char *aAddress );


	/** 
	* @brief Resolves two addresses and finds address family, acceptable by both addresses
	*
	* Can be used to find suitable address family for host names that can be resolved to both IPv4 and IPv6 addresses.
	* 
	* @param[in]	pAddress1		First string with address or host name
	* @param[in]	pAddress2		Second string with address or host name
	*
	* @return		Detected address family, or AF_UNSPEC if not found suitable address family
	**/
	int32_t MC_NET_UTILS_API DetectSuitableAddressFamily( const char *pAddress1, const char *pAddress2 );

	/** 
	* @brief Checks IP address string if it contains zero address (i.e. INADDR_ANY or in6addr_any)
	* 
	* @param[in]	aAddress		IP address string
	*
	* @return		true if specified address is zero address, false otherwise
	**/
	bool MC_NET_UTILS_API IsZeroAddress( const char *aAddress );

	/** 
	* @brief Return absolute URL for resource
	*
	* @param[in]	pURI			String with URL to resource, can be relative or absolute, with or without server address
	* @param[in]	pAbsURI			String with current full URL to which pURI is relative, if NULL then returned string will be equal to pURI
    * @param[in]    bFileURI        Signals about URI type: directory or single file
	* @param[in]	lalloc			Pointer to memory allocation function, can be NULL to use standard allocation function
	* @param[in]	lfree			Pointer to memory freeing function, can be NULL to use standard freeing function
	*
	* @return		Concatenated URI that should be freed by user or NULL on error
	**/
    char* MC_NET_UTILS_API ConcatenateURI( const char *pURI, const char *pAbsURI, bool bFileURI, void* (*lalloc)(size_t), void (*lfree)(void*) );

    /**
    * @brief Convert time point from the ISO8601 string representation (e.g. from DASH MPD) into tm value
    *
    * @param[in]	isoDate			String with time point in ISO8601 format
    *
    * @return		time point
    **/
    struct tm MC_NET_UTILS_API ISO8601ToTM(const char * isoDate);

    /**
    * @brief Convert time duration from the ISO8601 string representation (e.g. from DASH MPD) into double value, for instance "PT30S" will result into 30.0
    *
    * @param[in]	isoDate			String with time duration in ISO8601 format
    *
    * @return		duration in seconds
    **/
    double MC_NET_UTILS_API ISO8601ToSec(const char * isoDate);

#if defined (__cplusplus)
}
#endif

#endif //__MC_TOOLS_H__
