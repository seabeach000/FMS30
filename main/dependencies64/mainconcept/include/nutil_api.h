/**
@file nutil_api.h
@brief Network utilities API
@verbatim
 File: nutil_api.h
 
 Desc: Network utilities API
 
 Copyright (c) 2015 MainConcept GmbH or its affiliates.  All rights reserved.

 MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.
 This software is protected by copyright law and international treaties.  Unauthorized
 reproduction or distribution of any portion is prohibited by law.
@endverbatim
 */

#if !defined(__NUTIL_API_H__)
#define __NUTIL_API_H__

#include "mctypes.h"
#include "mcapiext.h"
#include "net_common.h"

#if defined(WIN32)
	#define MC_NET_UTILS_API __cdecl
#else
	#define MC_NET_UTILS_API
#endif

// nutil API is not supported for NaCl
#if !defined(__native_client__)

/**
* @brief Network interface info
**/
typedef struct _AddressInfo
{
	uint32_t iAdapterIndex;                 /**< Adapter index*/
	union {
		sockaddr Address;                   /**< Address info*/
		sockaddr_in AddressIPv4;            /**< IPv4 Address info*/
		sockaddr_in6 AddressIPv6;           /**< IPv6 Address info*/
	};
	uint32_t uiMask;                        /**< Mask*/
} AddressInfo;

#if defined (UNDER_CE)
	typedef struct _IP_ADAPTER_ADDRESSES IP_ADAPTER_ADDRESSES;
	typedef struct _IP_ADAPTER_ANYCAST_ADDRESS IP_ADAPTER_ANYCAST_ADDRESS;
	typedef struct _IP_ADAPTER_MULTICAST_ADDRESS IP_ADAPTER_MULTICAST_ADDRESS;
	typedef struct _IP_ADAPTER_UNICAST_ADDRESS IP_ADAPTER_UNICAST_ADDRESS;
	typedef struct _IP_ADAPTER_DNS_SERVER_ADDRESS IP_ADAPTER_DNS_SERVER_ADDRESS;
	typedef struct _IP_ADAPTER_PREFIX IP_ADAPTER_PREFIX;
#endif

/**
* @brief Cache range
**/
typedef struct _tagCacheRange {

	int64_t i64Start;       /**< Start position*/
	int64_t i64End;         /**< End position*/
} CACHERANGE;

/**
* @brief Network interface info enumerator
**/
class IEnumNetworkInterfaces : public MainConcept::NetworkStreaming::INetRefCounted
{
public:
	virtual ~IEnumNetworkInterfaces() {}

	/** 
	* @brief Clear interface list
	* 
	* @return		None
	**/
	virtual void Reset() = 0;
	
	/** 
	* @brief Retrieve count of network interfaces
	*
	* @return		Network interface count
	**/
	virtual uint32_t GetInterfacesCount() const = 0;

#if defined (UNDER_CE)
	virtual const IP_ADAPTER_ADDRESSES* GetInterfaceInfo(uint32_t index) const = 0;
	virtual HRESULT Update() = 0;
	virtual uint32_t  GetProtocolsCount() const = 0;
	virtual const WSAPROTOCOL_INFO* GetProtocolInfo(uint32_t index) const = 0;
#else
	
	/** 
	* @brief Update network interface list
	* 
	* @param[in]	bEnableLoopback		Allow loopback interface in list
	*
	* @return		None
	**/
	virtual void Update(bool bEnableLoopback = false) = 0;
	
	/** 
	* @brief Find network interface index by it's socket address
	* 
	* @param[in]	p		Socket address to get index for
	*
	* @return		Interface index, or 0xFFFFFFFF on error
	**/
	virtual uint32_t GetCurrentInterfaceIndex( sockaddr *p ) = 0;
	
	/** 
	* @brief Retrieve info for network interface at specified index
	* 
	* @param[in]	index		Index of network interface
	*
	* @return		Network interface info, or NULL if index is out of bounds
	**/
	virtual const AddressInfo *GetInterfaceInfo( uint32_t index = 0 ) const = 0;
#endif
};

/**
* @brief Cache file handler
**/
class ICacheFile : public MainConcept::NetworkStreaming::INetRefCounted
{
public:
	virtual ~ICacheFile() {}
	    
    /** 
    * @brief Open cache file
    * 
    * @param[in]	pFilePath		Path to cache file
    * @param[in]	pIndexPath		Path to saved cache index table file
    *
    * @return		MCNetResultOK on success or error code on failure
    **/
    virtual MainConcept::NetworkStreaming::MCNETRESULT Open( const char *pFilePath, const char *pIndexPath = NULL ) = 0;

	/** 
	* @brief Save cache file index
	* 
	* @param[in]	pIndexPath		Path to cache index table file
	*
	* @return		MCNetResultOK on success or error code on failure
	**/
	virtual MainConcept::NetworkStreaming::MCNETRESULT SaveIndex( const char *pIndexPath ) = 0;
	
	/** 
	* @brief Close cache file and clear cache index table
	*
	* @return		None
	**/
	virtual void Close() = 0;
	
	/** 
	* @brief Write data to cache file and update cache index table
	* 
	* @param[in]	pBuffer			Data to write
	* @param[in]	iBufferSize		Data size
	* @param[in]	i64Position		Position in cache file to write data to
	*
	* @return		MCNetResultOK on success or error code on failure
	**/
	virtual MainConcept::NetworkStreaming::MCNETRESULT Write( const uint8_t *pBuffer, int32_t iBufferSize, int64_t i64Position = -1 ) = 0;
	
	/** 
	* @brief Read data from cache file
	*
	* This method does not check if requested is present in cache table.
	* Use @ref IsRangeCached to check if data has been cached.
	*
	* @param[in]	pBuffer			Buffer to hold read data
	* @param[in]	iBufferSize		Count of bytes to read
	* @param[in]	i64Position		Position in cache file to read from
	* @param[in]	pReadBytes		Pointer to int which will hold count of bytes read
	*
	* @return		MCNetResultOK on success or error code on failure
	**/
	virtual MainConcept::NetworkStreaming::MCNETRESULT Read( const uint8_t *pBuffer, int32_t iBufferSize, int64_t i64Position = -1, int32_t *pReadBytes = NULL ) = 0;
	
	/** 
	* @brief Check if range was cached
	* 
	* Pass non-NULL pNextEmptyRange to get not cached range between i64Start and i64End if such exists.
	* Can be called with i64Start=0 and i64End=TotalDataSize in loop to get and fill all gaps in cached data.
	*
	* @param[in]	i64Start			Start of requested range
	* @param[in]	i64End				End of requested range
	* @param[in]	pNextEmptyRange		Receives next empty range inside requested range
	*
	* @return		true if requested range is present in cache file, false if it's fully or partially absent
	**/
	virtual bool IsRangeCached( int64_t i64Start, int64_t i64End, CACHERANGE *pNextEmptyRange = NULL ) = 0;
	
	/** 
	* @brief Retrieve summary size of cached data
	*
	* @return		Size of cached data in bytes
	**/
	virtual int64_t GetCachedSize() = 0;
};

#if defined (__cplusplus)
extern "C" {
#endif

	/**
    * @brief Retrieves new network interface enumerator instance
    * 
    * @param[in] get_rc            Pointer to get_rc memory manager implementation or NULL to use standard allocators
	*
    * @return                      valid pointer to network interface enumerator or NULL on error
    **/
	IEnumNetworkInterfaces * MC_NET_UTILS_API GetEnumeratorInterface( void *(MC_EXPORT_API *get_rc)(const char*) );

	/**
    * @brief Retrieves new cache file instance
    * 
    * @param[in] get_rc            Pointer to get_rc memory manager implementation or NULL to use standard allocators
	*
    * @return                      valid pointer to cache file or NULL on error
    **/
	ICacheFile * MC_NET_UTILS_API GetCacheFileInstance( void *(MC_EXPORT_API *get_rc)(const char*) );

    /**
    * @brief Retrieves new Shared Socket Information instance.
    * 
    * This object contains information for Inter Process Communication. It may be created as is and store information about current process 
    * or it could be created from serialized data of another instance.
    * 
    * @param[in] get_rc            Pointer to get_rc memory manager implementation or NULL to use standard allocators
    * @param[in] pData             Memory buffer that contains serialized instance of SharedSocketInfo
    * @param[in] uiSize            Length of serialized instance
    * 
    * @return                      valid pointer to object or NULL on error
    **/
    MainConcept::NetworkStreaming::ISharedSocketInfo * MC_NET_UTILS_API CreateSharedSocketInfo(void *(MC_EXPORT_API *get_rc)(const char*), const uint8_t *pData = NULL, uint32_t uiSize = 0);

    /**
    * @brief Retrieves new object ISharedSocketReceiver.
    * 
    * It used for receiving socket from another component even from another process
    * 
    * @param[in] get_rc            Pointer to get_rc memory manager implementation or NULL to use standard allocators
    * @param[in] pInfo             Stores information about remote end-point for receiving, sockets would be received from there
	*
    * @return                      valid pointer to object or NULL on error
    **/
    MainConcept::NetworkStreaming::ISharedSocketReceiver * MC_NET_UTILS_API CreateSharedSocketReceiver( void *(MC_EXPORT_API *get_rc)(const char*), MainConcept::NetworkStreaming::ISharedSocketInfo *pInfo );

    /**
    * @brief Retrieves new ISharedSocketSender instance.
    * 
    * It used for sending sockets to another component(even to another process)
    * 
    * @param[in] get_rc            Pointer to get_rc memory manager implementation or NULL to use standard allocators
	*
    * @return                      valid pointer to object or NULL on error
    **/
    MainConcept::NetworkStreaming::ISharedSocketSender * MC_NET_UTILS_API CreateSharedSocketSender( void *(MC_EXPORT_API *get_rc)(const char*) );

	/**
    * @brief Retrieves new asynchronous file reader instance
    * 
    * @param[in] get_rc				Pointer to get_rc memory manager implementation or NULL to use standard allocators
	* @param[in] pURI				File path
	* @param[in] uiCacheSize		Cache size in bytes
	*
    * @return						valid pointer to asynchronous file reader or NULL on error
    **/
	MainConcept::NetworkStreaming::IDataSource * MC_NET_UTILS_API CreateAsyncFileReader( void *(MC_EXPORT_API *get_rc)(const char*), const char *pURI, uint32_t uiCacheSize );

	/**
    * @brief Retrieves extended API function
    * 
    * @param[in] func				Extended API function identified
	*
    * @return						valid pointer to extended API function or NULL on error
    **/
	APIEXTFUNC   MC_NET_UTILS_API NetToolsGetAPIExt(uint32_t func);
#if defined (__cplusplus)
}
#endif

#endif // !defined(__native_client__)

#endif //__NUTIL_API_H__
