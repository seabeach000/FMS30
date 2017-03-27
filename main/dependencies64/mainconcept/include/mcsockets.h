/**
@file mcsockets.h
@brief Declaration of CMCSockets class for posix sockets functions
@verbatim
 File: mcsockets.h

 Desc: Declaration of CMCSockets class for posix sockets functions

 Copyright (c) 2015 MainConcept GmbH or its affiliates.  All rights reserved.
 MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.
 This software is protected by copyright law and international treaties.  Unauthorized
 reproduction or distribution of any portion is prohibited by law.
@endverbatim
*/

/* ====================================================================
 * Copyright (c) 1998-2011 The OpenSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit. (http://www.openssl.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    openssl-core@openssl.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.openssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * This product includes cryptographic software written by Eric Young
 * (eay@cryptsoft.com).  This product includes software written by Tim
 * Hudson (tjh@cryptsoft.com).
 *
 */


/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 *
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 *
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 *
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */

#if !defined (__MCSOCKETS_H__)
#define __MCSOCKETS_H__

#include "net_common.h"

#define MAX_UDP_NETWORK_PACKET_SIZE 0x80000
#define MAX_TCP_NETWORK_PACKET_SIZE 0x80000

#if !defined (INET_ADDRSTRLEN)
	#define INET_ADDRSTRLEN		22
#endif

#if !defined (INET6_ADDRSTRLEN)
	#define INET6_ADDRSTRLEN	65
#endif

/**
* @brief CMCSockets work mode
**/
typedef enum _tagSocketWorkMode {

	ClientMode,						/**< Socket will be used to send data */
	ServerMode						/**< Socket will be used to receive connections or data */
} SOCKETWORKMODE;

/**
* @brief CMCSockets select query type
**/
typedef enum _tagSocketCheckingLevel {

	CheckRead,						/**< Query socket for pending data or connections */
	CheckWrite,						/**< Query socket for outgoing buffer availability or connection completion */
	CheckBoth						/**< Query socket for both @ref CheckRead and @ref CheckWrite */
} SOCKETCHECKINGLEVEL;

/**
* @brief CMCSockets calls errors
**/
typedef enum _tagMCSocketsErrors {

	ReceiveFailure,					/**< Receive failed */
	SendFailure,					/**< Send failed */
	DNSLookupFailure,				/**< Failed to resolve name */
	ConnectFailure,					/**< Failed to connect */
	OpenFailure,					/**< Failed to open socket */
	ListenFailure,					/**< Failed to listen socket */
	AcceptFailure,					/**< Failed to accept client */
	WSAStartUpNotCalled,			/**< Socket service not initialized, see @ref StartSocketService */
	MulticastAddMemberShipFailure,	/**< Failed to join multicast group */
	BindFailure,					/**< Failed to bind socket */
	NotImplemented,					/**< Method not implemented */
	Success,						/**< Operation succeeded */
	TimeOuted,						/**< Operation timed out */
	AlreadyClosed,					/**< Operation attempted on a closed socket */
	Failure,						/**< Generic failure */
	PortAlreadyInUse,				/**< Port already in use */
	WSAStartupFailure,				/**< Failed to start socket service */
	WSACloseFailure,				/**< Failed to stop socket service */
	RequestNotFinished,				/**< Operation cannot be finished immediately */
	BufferIsTooSmall,				/**< Buffer is too small to hold complete packet */
    ConnectionRefused,              /**< Connection refused (peers TCP backlog is full, etc...)*/
	isUnkownError = 0xffff			/**< Unknown error */
} MCSOCKETSERRORS;

/**
* @brief CMCSockets state
**/
typedef enum _tagMCSocketState {

	isReceiving,					/**< Socket is receiving data */
	isSending,						/**< Socket is sending data */
	isConnected,					/**< Socket is connected */
	isShutDown,						/**< Socket is closed */
	isIdle,							/**< Reserved */
	isOpened,						/**< Socket is opened or assigned */
	isBinded,						/**< Socket is bound */
	isUnknownState = 0xffff			/**< Socket not initialized */
} MCSOCKETSTATE;

/**
* @brief CMCSockets connection type
**/
typedef enum _tagMCConnectionType {

	isMulticastConnection,				/**< IPv4 Multicast connection */
	isUnicastConnection,				/**< IPv4 Unicast connection */
	IsBroadcastConnection,				/**< IPv4 Broadcast connection */
	isMulticastConnectionIPv6,			/**< IPv6 Multicast connection */
	isUnicastConnectionIPv6,			/**< IPv6 Unicast connection */
	isAnycastConnectionIPv6,			/**< IPv6 Anycast connection */
	isUnknownConnectionType = 0xffff	/**< Socket not initialized  */
} MCCONNECTIONTYPE;

typedef enum _tagMCSocketShutdownType {

    MCSocketShutdownRecv = 0,
    MCSocketShutdownSend = 1,
    MCSocketShutdownBoth = 2
} MCSocketShutdownType;

/**
    @brief Describes network host
*/
typedef struct _tagHostsInfo
{                                           
    int8_t *pHostName;                  /**< Host name  */     
    int32_t iRoundTripValueInMSecs;     /**< Round trip value in mSec  */
} HOSTINFO;

/**
    @brief forward declaration for OpenSSL context
*/
struct ssl_st;

/**
    @brief Offers platform-independent Berkley's socket interface
*/
class CMCSockets
{
public:
	/**
    * @brief Release instance and free used memory
    * 
    * @return None
    **/
	virtual void Release();

public:
	CMCSockets( void *(MC_EXPORT_API *get_rc)(const char*) );
	virtual ~CMCSockets();

	void * operator new(size_t block_size, void* (*lalloc)(size_t)) throw();
	void operator delete(void *);
	void operator delete(void *p, void* (*)(size_t)) { delete (CMCSockets*)p; };

public:

	/** 
    * @brief Creates socket handle and initializes internal structures.
	*
	* For unicast addresses or multicast addresses with bAutoCreationMode set to false, socket handle will
	* be created and local and remote addresses resolved and set. Socket is ready to use with Bind, Connect, Listen and Accept calls.
	* For multicast addresses when bAutoCreationMode set to true, socket will be automatically bound and reuse address/port option is set. For ClientMode
	* socket will be joined to multicast group, and for ServerMode appropriate outgoing multicast interface will be selected.
	* Socket state is set to isOpened after successful call.
    * 
    * @param[in]	aServerName			Address of server to connect to, can be NULL if working in ServerMode
	* @param[in]	aPort				Port of server to connect to, can be 0 if working in ServerMode
	* @param[in]	aNIC				Local address to bind to, can be NULL if working in ClientMode
	* @param[in]	aLocalPort			Local port to bind to, can be 0 if working in ClientMode
	* @param[in]	bAutoCreationMode	Used with multicast addresses. Set to true to automatically bind socket, join it to multicast group (for client) or set outgoing multicast interface (for server), and set reuse address option. Also see @ref Close.
	* @param[in]	aWorkMode			Set work mode: use ClientMode for sockets that will initiate connections, set to ServerMode for sockets that will accept connections or send multicast data
	* @param[in]	aProto				Socket protocol, use IPPROTO_UDP for UDP and IPPROTO_TCP for TCP
	* @param[in]	aConnectionType		Socket type, use SOCK_DGRAM for UDP and SOCK_STREAM for TCP
	* @param[in]	aIsSSL              true for SSL Sockets, false for regular
	*
    * @return		Success if all operations succeeded, error code otherwise
    **/
	virtual MCSOCKETSERRORS Open( const char *aServerName, int32_t aPort, const char *aNIC = NULL, int32_t aLocalPort = 0,
						  bool bAutoCreationMode = true, SOCKETWORKMODE aWorkMode = ClientMode, int32_t aProto = IPPROTO_UDP, int32_t aConnectionType = SOCK_DGRAM, bool aIsSSL = false );

	/** 
    * @brief Assigns existing socket handle to CMCSockets instance
	*
	* Can be used to handle new handles returned by Accept call.
	* Socket state is set to isOpened after successful call.
    * 
	* @param[in]	aSocket				Valid socket handle
    * @param[in]	pLocalInfo			Local socket address structure
	* @param[in]	LocalInfoSize		Local socket address length
	* @param[in]	pRemoteInfo			Remote socket address structure
	* @param[in]	RemoteInfoSize		Remote socket address length
	* @param[in]	bAutoCreationMode	Not used
	* @param[in]	aWorkMode			Set work mode: use ClientMode for sockets that will initiate connections, set to ServerMode for sockets that will accept connections or send multicast data
	* @param[in]	aProto				Socket protocol, use IPPROTO_UDP for UDP and IPPROTO_TCP for TCP
	* @param[in]	aConnectionType		Socket type, use SOCK_DGRAM for UDP and SOCK_STREAM for TCP
	*
    * @return		Success if assignment succeeded, error code otherwise
    **/
	virtual MCSOCKETSERRORS Assign( SOCKET aSocket, const sockaddr_storage *pLocalInfo, int32_t LocalInfoSize, const sockaddr_storage *pRemoteInfo, int32_t RemoteInfoSize,
						  bool bAutoCreationMode = true, SOCKETWORKMODE aWorkMode = ClientMode, int32_t aProto = IPPROTO_UDP, int32_t aConnectionType = SOCK_DGRAM );

	/** 
    * @brief Assigns handle of socket which was shared with another process to CMCSockets instance
	*
	* All socket parameters are retrieved from passed handle.
	* 
	* @param[in]	aSocket				Valid socket handle
	*
	* @return		Success if assignment succeeded, error code otherwise
	**/
	virtual MCSOCKETSERRORS AssignShared( SOCKET aSocket );

	/** 
    * @brief Closes socket handle
    * 
	* Socket will also drop membership of multicast group when multicast connection is used and bAutoCreationMode was specified in Open call.
	* Socket state is set to isShutDown after successful call.
	*
    * @return		Success if socket close succeeded, error code otherwise
    **/
	virtual MCSOCKETSERRORS	Close();

	/** 
    * @brief Shutdown socket handle
	*
	* Disables receive operations on socket handle.

    * @param[in] shutdown_type  specifies type of shutdown @ref MCSocketShutdownType
    * 
    * @return		Success if socket shutdown succeeded, error code otherwise
    **/
    virtual MCSOCKETSERRORS	Shutdown(MCSocketShutdownType shutdown_type = MCSocketShutdownSend);

	/** 
    * @brief Connect socket
	*
	* Call connect on socket handle with address and port specified in @ref Open call. If socket was previously set to non-blocking mode, this call
	* may return immediately with RequestNotFinished. Use Select with CheckWrite to wait for connection completion.
	*
	* @param[in]	aPort				Set to non-zero value to override port specified in @ref Open call.
    * 
    * @return		Success if connection succeeded, error code otherwise
    **/
	virtual MCSOCKETSERRORS Connect( uint16_t aPort = 0 );

    virtual MCSOCKETSERRORS InitSSL();

	/** 
    * @brief Receive data from network
	*
	* When working with UDP packets and aRecvBuff is too small to receive complete packet,
	* BufferIsTooSmall may be returned and buffer is filled with received data up to aLen.
	* Remaining data in packet will be lost.
	* Method can return RequestNotFinished when socket is in non-blocking mode and no data available.
	*
	* @param[in]	aRecvBuff			Buffer to hold received data
	* @param[in]	aLen				Size of buffer
	* @param[out]	aReaded				Pointer to int that will receive count of bytes placed into buffer
	* @param[in]	uiFlags				Flags to pass to recv function
    * 
    * @return		Success if receive succeeded, error code otherwise
    **/
	virtual MCSOCKETSERRORS Receive( uint8_t *aRecvBuff, int32_t aLen, int32_t *aReaded, uint32_t uiFlags = 0 );

	/** 
    * @brief Receive data from network and fetch remote socket address
	*
	* When working with UDP packets and aRecvBuff is too small to receive complete packet,
	* BufferIsTooSmall may be returned and buffer is filled with received data up to aLen.
	* Remaining data in packet will be lost.
	* Method can return RequestNotFinished when socket is in non-blocking mode and no data available.
	*
	* @param[in]	aRecvBuff			Buffer to hold received data
	* @param[in]	aLen				Size of buffer
	* @param[out]	aReaded				Pointer to int that will receive count of bytes placed into buffer
	* @param[in]	uiFlags				Flags to pass to recv function
	* @param[out]	aFrom				Pointer to sockaddr_storage that will receive remote socket address
    * 
    * @return		Success if receive succeeded, error code otherwise
    **/
	virtual MCSOCKETSERRORS ReceiveFrom( uint8_t *aRecvBuff, int32_t aLen, int32_t *aReaded, uint32_t uiFlags = 0, sockaddr_storage *aFrom = NULL );

	/** 
    * @brief Query socket for incoming data or outgoing buffer availability
	*
	* By default, Select will wait up to timeout + 1ms, where timeout is time in seconds set via SetTimeOut.
	* Even if timeout is set to 0, 1ms is a minimal wait time. To avoid waiting at all - set bNoWait to true.
	*
	* @param[in]	aLevel				Type of query
	* @param[in]	bNoWait				Don't wait, return immediately
    * 
    * @return		Success if select succeeded, error code otherwise
    **/
	virtual MCSOCKETSERRORS Select( SOCKETCHECKINGLEVEL aLevel = CheckRead, bool bNoWait = false );

	/** 
    * @brief Send data to network
	*
	* Method can return RequestNotFinished when socket is in non-blocking mode and aSendBuff is too big to fit into system's outgoing network buffer.
	*
	* @param[in]	aSendBuff			Buffer to send
	* @param[in]	aLen				Size of buffer
	* @param[out]	pSent				Pointer to int that will receive count of bytes sent
    * 
    * @return		Success if send succeeded, error code otherwise
    **/
	virtual MCSOCKETSERRORS	Send( const uint8_t *aSendBuff, int32_t aLen, int32_t *pSent = NULL );

	/** 
    * @brief Send data to specified socket address
	*
	* Method can return RequestNotFinished when socket is in non-blocking mode and aSendBuff is too big to fit into system's outgoing network buffer.
	*
	* @param[in]	aSendBuff			Buffer to send
	* @param[in]	aLen				Size of buffer
	* @param[in]	aRecepient			Destination address, when set to NULL - server address from Open or Assign calls is used
    * 
    * @return		Success if send succeeded, error code otherwise
    **/
	virtual MCSOCKETSERRORS	SendTo( const uint8_t *aSendBuff, int32_t aLen, sockaddr_storage *aRecepient = NULL );

	/** 
    * @brief Send data, splitting it into smaller packets if needed
	*
	* If aChunkSize < aLen, then aLen will be split and sent in multiple packets.
	* Method can return RequestNotFinished if timeout occurred.
	*
	* @param[in]	aSendBuff			Buffer to send
	* @param[in]	aLen				Size of buffer
	* @param[in]	aChunkSize			Size of packet
	* @param[out]	pSent				Pointer to int that will receive count of bytes sent
    * 
    * @return		Success if send succeeded, error code otherwise
    **/
	virtual MCSOCKETSERRORS	SendAll( const uint8_t *aSendBuff, int32_t aLen, int32_t aChunkSize, int32_t *pSent = NULL );

	/** 
    * @brief Accept incoming connection
	*
	* Socket must be prepared with Listen call priror to calling this method.
	* Error can be returned when socket is in non-blocking mode and no connections are present.
	*
	* @param[out]	pLocalInfo				Local socket address
	* @param[out]	LocalInfoSize			Size of local socket address
	* @param[out]	pReceiverInfo			Remote socket address
	* @param[out]	ReceiverInfoSize		Size of remote socket address
    * 
    * @return		Socket handle on success, SOCKET_ERROR on error
    **/
	virtual SOCKET Accept( sockaddr_storage *pLocalInfo, int32_t *LocalInfoSize, sockaddr_storage *pReceiverInfo, int32_t *ReceiverInfoSize );

	/** 
    * @brief Setup socket to accept incoming connections
	*
	* @param[in]	uiMaxClientsCount		Maximum count of pending connections
	*
    * @return		Success if call succeeded, error code otherwise
    **/
	virtual MCSOCKETSERRORS	Listen( uint32_t uiMaxClientsCount = 1 );

	/** 
    * @brief Bind socket
	*
	* Socket address specified in Open or Assign call will be used.
	*
    * @return		Success if bind succeeded, error code otherwise
    **/
	virtual MCSOCKETSERRORS	Bind();

	/** 
    * @brief Join socket to multicast group
	*
	* @param[in]	pMulticastGroup		Address of multicast group to join to, set to NULL to join to server address specified in Open call
	* @param[in]	pInterface			Address of local interface to join on, set to NULL to join on local address specified in Open call
	*
    * @return		Success if join succeeded, error code otherwise
    **/
	virtual MCSOCKETSERRORS JoinToMulticastGroup( const char *pMulticastGroup = NULL, const char *pInterface = NULL );

	/** 
    * @brief Remove socket from multicast group
	*
	* @param[in]	pMulticastGroup		Address of multicast group to leave, set to NULL to leave server address specified in Open call
	* @param[in]	pInterface			Address of local interface to leave from, set to NULL to leave from local address specified in Open call
	*
    * @return		Success if leave succeeded, error code otherwise
    **/
	virtual MCSOCKETSERRORS LeaveMulticastGroup( const char *pMulticastGroup = NULL, const char *pInterface = NULL );

	/** 
    * @brief Set socket option
	*
	* @param[in]	aLevel			Level of the option
	* @param[in]	aOptName		Identifier of the option
	* @param[in]	aOptVal			Value of the option
	* @param[in]	aOptLen			Length of the option value
	*
    * @return		Success if option is set successfully, error code otherwise
    **/
	virtual MCSOCKETSERRORS	SetOpt( int32_t aLevel, int32_t aOptName, int32_t aOptVal, int32_t aOptLen );

	/** 
    * @brief Get socket option value
	*
	* @param[in]	aLevel			Level of the option
	* @param[in]	aOptName		Identifier of the option
	* @param[out]	aOptVal			Value of the option
	* @param[out]	aOptLen			Length of the option value
	*
    * @return		Success if option value received successfully, error code otherwise
    **/
	virtual MCSOCKETSERRORS	GetOpt( int32_t aLevel, int32_t aOptName, int8_t *aOptVal, int32_t *aOptLen );

	/** 
    * @brief Control socket I/O mode
	*
	* @param[in]	cmd			Command to perform
	* @param[in]	argp		Command parameter
	*
    * @return		Success if call successful, error code otherwise
    **/
	virtual MCSOCKETSERRORS	SocketCtl( int32_t cmd, uint32_t argp );

	/** 
    * @brief Set socket's incoming buffer size
	*
	* @param[in]	aBuffSize			Incoming buffer size in bytes
	*
    * @return		Success if call successful, error code otherwise
    **/
	virtual MCSOCKETSERRORS SetReceiverMaxPacketSize( int32_t aBuffSize );

	/** 
    * @brief Set socket's outgoing buffer size
	*
	* @param[in]	aBuffSize			Outgoing buffer size in bytes
	*
    * @return		Success if call successful, error code otherwise
    **/
	virtual MCSOCKETSERRORS SetSenderMaxPacketSize( int32_t aBuffSize );

	/** 
    * @brief Set reuse address option for socket
	*
	* Note that for multicast receiving, OS X may also require
	* setting reuse port option.
	*
    * @return		Success if call successful, error code otherwise
    **/
	virtual MCSOCKETSERRORS SetReuseAddressOpt();

	/** 
    * @brief Enable or disable non-blocking mode for socket
	*
	* @param[in]	bNonBlocking			Set to true to switch socket to non-blocking mode, false - to use blocking socket mode
	*
    * @return		Success if call successful, error code otherwise
    **/
	virtual MCSOCKETSERRORS SetNonBlockingMode( bool bNonBlocking = true );

	/** 
    * @brief Get socket state
	*
    * @return		Socket state
    **/
	virtual MCSOCKETSTATE GetSocketState() const { return m_SocketState; }

	/** 
    * @brief Set socket timeout
	*
	* Timeout value is used by Select, Connect and SendAll calls.
	*
	* @param[in]	aTimeOut	Timeout value in seconds
	*
    * @return		None
    **/
	virtual void SetTimeOut( int32_t aTimeOut );

	virtual operator SOCKET () {
		return m_Socket;
	}

    virtual operator SOCKET () const {
        return m_Socket;
    }

	/** 
    * @brief Determines whether socket is shared with another process
	*
    * @return		True if socket is shared or False if not
    **/	
	virtual bool IsShared() { return m_bShared; }

	/** 
    * @brief Get local socket address
	*
    * @return		Local socket address
    **/
	virtual const sockaddr_storage * GetLocalInfo() { return &m_LocalSockAddr; }

	/** 
    * @brief Get remote socket address
	*
    * @return		Remote socket address
    **/
	virtual const sockaddr_storage * GetRemoteInfo() { return &m_RemoteSockAddr; }

	/** 
    * @brief Advise socket address family
	*
	* You may use this function to explicitly set socket address family before calling Open to avoid automatic detection
	*
	* @param[in]	uiFamily	Socket address family
	*
    * @return		None
    **/
	virtual void ManualSetIpFamily( uint32_t uiFamily );

private:
    MCCONNECTIONTYPE	InternalGetConnectionType(const sockaddr_storage *aServerIP = NULL);
    MCSOCKETSERRORS		InternalSetupRemoteInformation(const sockaddr_storage *aRemote, int32_t aPort);
	MCSOCKETSERRORS		InternalSetupLocalInterfaceInformation( const char *aNIC, int32_t aPort = 0, bool bIsLo = false, int32_t iAddressFamily = PF_UNSPEC );
	MCSOCKETSERRORS		CreateSocketInstance( int32_t aConnectionType, int32_t aProto, int32_t iAddressFamily = AF_INET );
	MCSOCKETSERRORS		InternalSetupConnection();
	MCSOCKETSERRORS		InternalPrepareForMuliticast();
	uint32_t			InternalGetInterfaceInfo( const sockaddr *pSource );
	bool				IsLoopBackConnection();

	inline MCSOCKETSERRORS SetMulticastIF();

private:
	SOCKETWORKMODE		m_WorkMode;
	SOCKET				m_Socket;
	sockaddr_storage	m_LocalSockAddr;
	sockaddr_storage	m_RemoteSockAddr;
	int32_t				m_iTimeOut;
	ip_mreq				m_MulticastAddress;

	MCCONNECTIONTYPE	m_ConnectionType;
	MCSOCKETSTATE		m_SocketState;

	int32_t				m_iCurrentProto;

	bool				m_bShared;

	bool				m_bAutoMode;
	uint32_t			m_uiFamily;

	// IPv6 multicast structure
	ipv6_mreq			m_IPv6MulticastAddress;

	bool				m_bNonBlockingMode;
	bool                m_bIsSSL;

	ssl_st            * m_SSLContext;

protected:
	void* (*lalloc)(size_t);
	void  (*lfree)(void*);
	void *(*lget_rc)(const char*);
};

#if defined (__cplusplus)
extern "C" {
#endif

	/**
    * @brief Retrieves new CMCSockets instance
    * 
    * @param[in] get_rc            Pointer to get_rc memory manager implementation or NULL to use standard allocators
	*
    * @return                      valid pointer to CMCSockets instance
    **/
	CMCSockets * NET_API_CALL GetSocketInstance( void *(MC_EXPORT_API *get_rc)(const char*) );

	/**
    * @brief Platform-specific networking service initialization
    * 
    * @return                      Success when initialization is completed, WSAStartupFailure if errors occurred
    **/
	MCSOCKETSERRORS NET_API_CALL StartSocketService();

	/**
    * @brief Platform-specific networking service shutdown
    * 
    * @return                      Success when shutdown is completed, WSACloseFailure if errors occurred
    **/
	MCSOCKETSERRORS NET_API_CALL StopSocketService();
	
#if defined (__cplusplus)
}
#endif

#endif // __MCSOCKETS_H__

