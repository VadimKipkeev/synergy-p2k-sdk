/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * DSMA SDK
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef __SDK_DSMA_H__
#define __SDK_DSMA_H__

// Protocols
#define PROTOCOL_TCP 1
#define PROTOCOL_SSL 2
#define PROTOCOL_UDP 3
#define PROTOCOL_IP  4

#define USE_CSD      1
#define USE_GPRS     2

#define PROXY_NULL   0

typedef UINT32 CMD_NUM;

// Proxy state
enum {

	PROXY_STATE_ACTIVE,               // Enable
	PROXY_STATE_INACTIVE,             // Disable with state inactive
	PROXY_STATE_FAILED,               // Error
	PROXY_STATE_LINK_AVAILABLE,       // Matching datalink activated
	PROXY_STATE_DEFAULT_LINK_UPDATED, // Default link has being updated
	PROXY_STATE_LINK_ATTACH_COUNT,    // Number of clients using matching link changed
	PROXY_STATE_GPRS_SUSPEND,
	PROXY_STATE_GPRS_RESUME,
	PROXY_STATE_NONE = 0xff

};
typedef UINT8 PROXY_STATE_T;

// Buffer state
enum {

	BUFFER_STATE_XON,          // Data send is avaliable
	BUFFER_STATE_XOFF,         // Data send is not avaliable, needed waiting
	BUFFER_STATE_DATA,         // New data, needed calculating
	BUFFER_STATE_NONE = 0xff

};
typedef UINT8 BUFFER_STATE_T;

// Attributes
enum {

	DSMA_ATTR_NULL = 0,

	DSMA_ATTR_TRANS_PROT = 0x1000,
	DSMA_ATTR_LOCAL_PORT,
	DSMA_ATTR_REMOTE_PORT,
	DSMA_ATTR_PRIORITY,

	DSMA_ATTR_NET_PROT = 0x2000,
	DSMA_ATTR_LOCAL_IP,
	DSMA_ATTR_REMOTE_IP,

	DSMA_ATTR_LINK_PROT = 0x3000,
	DSMA_ATTR_USER_NAME,
	DSMA_ATTR_PW,
	DSMA_ATTR_AUTH_TYPE,
	DSMA_ATTR_DNS_1,
	DSMA_ATTR_DNS_2,

	DSMA_ATTR_PHYS_PROT = 0x4000,
	DSMA_ATTR_APN,

	DSMA_ATTR_LINK_IS_SHAREABLE = 0x4000 + 7,
	DSMA_ATTR_LINK_IS_DEFAULT,
	DSMA_ATTR_LINK_IS_PERSISTANT

};
typedef UINT16 DSMA_ATTR_T;

typedef struct {

	DSMA_ATTR_T attr;
	UINT32      link_desc_ind;
	void        *value;
	UINT32      size;
	UINT32      result;

} DSMA_ATTRIBUTE_T;

typedef struct {

	UINT8 source;
	UINT8 appCallCause;
	UINT8 dlSigCallCause;
	UINT8 networkCallCause;
	UINT8 gprsError;
	INT8  dfspError;
	UINT8 dsmaCause;

} DSMA_CAUSE_T;

typedef struct {

	UINT8 foregroundClients;
	UINT8 backgroundClientst;
	UINT8 listeningClients;

} DSMA_LINK_ATTACH_COUNT_T;

typedef struct {

	UINT8  unk1;
	UINT16 unk2;
	UINT8  unk3;

} DSMA_QOS_INFO_T;

typedef struct {

	UINT32                   proxy_id;    // Proxy identifier.
	UINT8                    status;      // Previous request status (RESULT_OK/RESULT_FAIL)
	CMD_NUM                  cmd;         // Unique number, can using for identifications
	SU_PORT_T                port;        // This port events listens
	PROXY_STATE_T            proxy_state; // Active, inactive, activate failed
	BUFFER_STATE_T           buf_state;
	UINT32                   attr_num;
	DSMA_ATTRIBUTE_T         *attr_list;
	UINT32                   lp_handle;
	DSMA_CAUSE_T             cause;
	DSMA_LINK_ATTACH_COUNT_T linkAttachCount;
	UINT32 handle;

	#if defined(FTR_L7E) || defined(FTR_L9)
		UINT8           sessionId;
		DSMA_QOS_INFO_T qosInfo;
		UINT8           localPortLength;
		UINT16          *localPortInfo;
		DSMA_QOS_INFO_T minReqQosInfo;
	#endif

} DSMA_DATA_T; // [72]

#ifdef __cplusplus
extern "C" {
#endif

	/* After every command save CMD_NUM and compare this with CMD_NUM from event attach for know, that this event is need
	 * create proxy, at next get EV_DSMA_PROXY_CREATE
	 */
	CMD_NUM DL_DSMA_ProxyCreate(SU_PORT_T port);

	// Clear DSMA proxy
	CMD_NUM DL_DSMA_ProxyDestroy(UINT32 proxy_id);

	// Set proxy attribute, return with EV_DSMA_PROXY_ATTR event
	CMD_NUM DL_DSMA_ProxyAttributeSet(
		UINT32           proxy_id,
		UINT32           attr_count,
		DSMA_ATTRIBUTE_T *attr_list
	);

	// Get proxy attribute, return with EV_DSMA_PROXY_ATTR event
	CMD_NUM DL_DSMA_ProxyAttributeGet(
		UINT32           proxy_id,
		UINT32           attr_count,
		DSMA_ATTRIBUTE_T *attr_list
	);

	// Activate proxy, create connection with configuration, return with EV_DSMA_PROXY_STATE event
	CMD_NUM DL_DSMA_ProxyActivate(UINT32 proxy_id);

	// Deactivate proxy, close sockets and destroy connection
	CMD_NUM DL_DSMA_ProxyDeactivate(UINT32 proxy_id);

	// Deactivate proxy, close sockets (connection is avaliable, can be activate again)
	CMD_NUM DL_DSMA_ProxyDeactivateSocket(UINT32 proxy_id);

	// Send data, return bites count
	UINT32 DL_DSMA_ProxyWrite(
		UINT32 proxy_id,
		BYTE   *buf,
		UINT32 size
	);

	// Read data, return bites count
	UINT32 DL_DSMA_ProxyRead(
		UINT32 proxy_id,
		BYTE   *buf,
		UINT32 size
	);

#ifdef __cplusplus
}
#endif

#endif // __SDK_DSMA_H__

/* EOF */