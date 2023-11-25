/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * USSD requests SDK
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef __SDK_USSD_H__
#define __SDK_USSD_H__

#include "typedefs.h"

#define DL_SIG_CALL_SS_USSD_STRING_MAX_LENGTH             200
#define DL_SIG_CALL_SS_MAX_BCD_NUM_LEN                    20
#define DL_SIG_CALL_SS_RETURN_RESULT_MAX_LENGTH           256
#define DL_SIG_CALL_MAX_NUMBER_LENGTH                     41
#define DL_SIG_CALL_MAX_NUMBER_ARRAY_LENGTH               (DL_SIG_CALL_MAX_NUMBER_LENGTH + 1)
#define DL_SIG_CALL_SS_RETURN_DATA_ARRAY_SIZE             1
#define DL_SIG_CALL_SS_MAX_FORWARD_TO_NUMBER_LENGTH       36
#define DL_SIG_CALL_SS_MAX_FORWARD_TO_NUMBER_ARRAY_LENGTH (DL_SIG_CALL_SS_MAX_FORWARD_TO_NUMBER_LENGTH + 2)

typedef UINT16 DL_SIG_CALL_ID_T;
typedef UINT16 DL_SIG_CALL_SS_ID_T;

#define DL_SIG_CALL_SS_INVALID_SS_ID 0xFFFF

enum {

	DL_SIG_CALL_TON_INTERNATIONAL,
	DL_SIG_CALL_TON_UNKNOWN,
	DL_SIG_CALL_TON_NOT_SPECIFIED = 0xFF

};
typedef UINT8 DL_SIG_CALL_TYPE_OF_NUMBER_T;

enum {

	DL_SIG_CALL_NUMBER_PLAN_UNKNOWN = 1,
	DL_SIG_CALL_NUMBER_PLAN_NOT_SPECIFIED = 0xFF

};
typedef UINT8 DL_SIG_CALL_NUMBER_PLAN_IDENTIFIER_T;

enum {

	DL_SIG_CALL_STK_TYPE_NORMAL,
	DL_SIG_CALL_STK_TYPE_CC_MODIFIED,
	DL_SIG_CALL_STK_TYPE_PROACTIVE

};
typedef UINT8 DL_SIG_CALL_STK_TYPE_T;

enum {

	DL_SIG_CALL_RESULT_SUCCESS,
	DL_SIG_CALL_RESULT_FAIL,
	DL_SIG_CALL_RESULT_PLACED,
	DL_SIG_CALL_RESULT_NOT_PLACED,
	DL_SIG_CALL_RESULT_ACCEPTED,
	DL_SIG_CALL_RESULT_NOT_ACCEPTED,
	DL_SIG_CALL_RESULT_CALL_ANSWERED,
	DL_SIG_CALL_RESULT_CALL_NOT_ANSWERED

};
typedef UINT8 DL_SIG_CALL_RESULT_T;

enum {

	DL_SIG_CALL_CAUSE_NO_CAUSE,
	DL_SIG_CALL_CAUSE_CC_BUSY,
	DL_SIG_CALL_CAUSE_NORMAL = 6,
	DL_SIG_CALL_CAUSE_NO_SERVICE = 9,
	DL_SIG_CALL_CAUSE_NO_ANSWER = 22,
	DL_SIG_CALL_CAUSE_CALL_REJECTED = 23,
	DL_SIG_CALL_CAUSE_SIGNALING_ERROR = 26,
	DL_SIG_CALL_CAUSE_NETWORK_ERROR = 27,
	DL_SIG_CALL_CAUSE_NETWORK_BUSY = 28,
	DL_SIG_CALL_CAUSE_SERVICE_UNAVAILABLE = 31,
	DL_SIG_CALL_CAUSE_SERVICE_NOT_SUPPORTED = 32,
	DL_SIG_CALL_CAUSE_ACCESS_DENIED = 43,
	DL_SIG_CALL_CAUSE_SIGNALING_TIMEOUT = 47,
	DL_SIG_CALL_CAUSE_ILLEGAL_SS_OPERATION = 52,
	DL_SIG_CALL_CAUSE_SS_INCOMPATIBILITY,
	DL_SIG_CALL_CAUSE_SS_NOT_AVAILABLE,
	DL_SIG_CALL_CAUSE_SS_SUBSCRIPTION_VIOLATION,
	DL_SIG_CALL_CAUSE_INCORRECT_PASSWORD = 56,
	DL_SIG_CALL_CAUSE_USSD_BUSY = 63,
	DL_SIG_CALL_CAUSE_USSD_CANCELED = 69,
	DL_SIG_CALL_CAUSE_POWER_DOWN = 75

};
typedef UINT8 DL_SIG_CALL_CAUSE_T;

enum {

	DL_SIG_CALL_SS_OPERATION_REGISTER,
	DL_SIG_CALL_SS_OPERATION_ERASE,
	DL_SIG_CALL_SS_OPERATION_ACTIVATE,
	DL_SIG_CALL_SS_OPERATION_DEACTIVATE,
	DL_SIG_CALL_SS_OPERATION_INTERROGATE,
	DL_SIG_CALL_SS_OPERATION_PASSWD_CHANGE,
	DL_SIG_CALL_SS_OPERATION_USSD,
	DL_SIG_CALL_SS_OPERATION_INVALID = 0xFF

};
typedef UINT8 DL_SIG_CALL_SS_OPERATION_T;

enum {

	DL_SIG_CALL_SS_CODE_ALL_SS,
	DL_SIG_CALL_SS_CODE_INVALID = 0xff

};
typedef UINT8 DL_SIG_CALL_SS_CODE_T;

typedef UINT8 DL_SIG_CALL_SS_BASIC_SERVICE_CODE_T;

enum {

	DL_SIG_CALL_SS_BASIC_SERVICE_TYPE_NOT_SPECIFIED,
	DL_SIG_CALL_SS_BASIC_SERVICE_TYPE_BEARER,
	DL_SIG_CALL_SS_BASIC_SERVICE_TYPE_TELE,
	DL_SIG_CALL_SS_BASIC_SERVICE_TYPE_ALL_BEARER_TELE

};
typedef UINT8 DL_SIG_CALL_SS_BASIC_SERVICE_TYPE_T;

typedef struct {

	DL_SIG_CALL_SS_BASIC_SERVICE_TYPE_T service_type;
	DL_SIG_CALL_SS_BASIC_SERVICE_CODE_T service_code;

} DL_SIG_CALL_SS_BASIC_SERVICE_STRUCT_T;

typedef UINT8 DL_SIG_CALL_SS_FWD_NO_REPLY_TIME_T;

#define DL_SIG_CALL_SS_FWD_NO_REPLY_TIME_DEFAULT       0
#define DL_SIG_CALL_SS_FWD_NO_REPLY_TIME_MIN           5
#define DL_SIG_CALL_SS_FWD_NO_REPLY_TIME_MAX           30
#define DL_SIG_CALL_SS_FWD_NO_REPLY_TIME_NOT_SPECIFIED 0xff

enum {

	DL_SIG_CALL_SS_RETURN_DATA_TYPE_NO_DATA = 0,
	DL_SIG_CALL_SS_RETURN_DATA_TYPE_SS_STATUS = 1,
	DL_SIG_CALL_SS_RETURN_DATA_TYPE_USSD_STRING = 7

};
typedef UINT8 DL_SIG_CALL_SS_RETURN_DATA_TYPE_T;

enum {

	DL_SIG_CALL_SS_STATUS_NOT_SUBSCRIBED,
	DL_SIG_CALL_SS_STATUS_NOT_ACTIVE,
	DL_SIG_CALL_SS_STATUS_ACTIVE_CONFLICT,
	DL_SIG_CALL_SS_STATUS_ACTIVE_NO_CONFLICT,
	DL_SIG_CALL_SS_STATUS_ACTIVE_UNKNOWN,
	DL_SIG_CALL_SS_STATUS_UNKNOWN

};
typedef UINT8 DL_SIG_CALL_SS_STATUS_T;

enum {

	DL_SIG_CALL_SS_SUB_OPTION_NOT_SPECIFIED = 0

};
typedef UINT8 DL_SIG_CALL_SS_SUBSCRIPTION_OPTION_T;

typedef struct {

	BOOL                                  valid;
	DL_SIG_CALL_SS_BASIC_SERVICE_STRUCT_T basic_service;
	DL_SIG_CALL_SS_STATUS_T               ss_status;
	UINT8                                 number[DL_SIG_CALL_SS_MAX_BCD_NUM_LEN];
	DL_SIG_CALL_SS_FWD_NO_REPLY_TIME_T    no_reply_time;
	DL_SIG_CALL_TYPE_OF_NUMBER_T          type_of_number;

} DL_SIG_CALL_SS_BCD_FORWARDING_INFO_T;

typedef struct {

	BOOL                                  valid;
	DL_SIG_CALL_SS_BASIC_SERVICE_STRUCT_T basic_service;
	DL_SIG_CALL_SS_STATUS_T               ss_status;

} DL_SIG_CALL_SS_BARRING_INFO_STRUCT_T;

typedef struct {

	DL_SIG_CALL_SS_STATUS_T               ss_status;
	DL_SIG_CALL_SS_SUBSCRIPTION_OPTION_T  subscription_option;
	DL_SIG_CALL_SS_BASIC_SERVICE_STRUCT_T basic_service_list[DL_SIG_CALL_SS_RETURN_DATA_ARRAY_SIZE];

} DL_SIG_CALL_SS_GENERIC_INFO_STRUCT_T;

typedef struct {

	DL_SIG_CALL_TYPE_OF_NUMBER_T         type_of_number;
	DL_SIG_CALL_NUMBER_PLAN_IDENTIFIER_T number_plan_identifier;
	W_CHAR                               number[DL_SIG_CALL_SS_MAX_FORWARD_TO_NUMBER_ARRAY_LENGTH];

} DL_SIG_CALL_SS_FORWARD_TO_NUMBER_STRUCT_T;

typedef struct {

	W_CHAR string[DL_SIG_CALL_SS_USSD_STRING_MAX_LENGTH];

} DL_SIG_CALL_SS_USSD_STRING_STRUCT_T;

typedef union {

	DL_SIG_CALL_SS_STATUS_T                   ss_status;
	DL_SIG_CALL_SS_BCD_FORWARDING_INFO_T      forwarding_info[DL_SIG_CALL_SS_RETURN_DATA_ARRAY_SIZE];
	DL_SIG_CALL_SS_BARRING_INFO_STRUCT_T      barring_info[DL_SIG_CALL_SS_RETURN_DATA_ARRAY_SIZE];
	DL_SIG_CALL_SS_GENERIC_INFO_STRUCT_T      generic_info;
	DL_SIG_CALL_SS_FORWARD_TO_NUMBER_STRUCT_T forward_to_number;
	DL_SIG_CALL_SS_BASIC_SERVICE_STRUCT_T     basic_service_list[DL_SIG_CALL_SS_RETURN_DATA_ARRAY_SIZE];
	DL_SIG_CALL_SS_USSD_STRING_STRUCT_T       ussd_string;

} DL_SIG_CALL_SS_RETURN_DATA_T;

typedef struct {

	DL_SIG_CALL_TYPE_OF_NUMBER_T         type_of_number;
	DL_SIG_CALL_NUMBER_PLAN_IDENTIFIER_T number_plan_identifier;
	W_CHAR                               number[DL_SIG_CALL_MAX_NUMBER_ARRAY_LENGTH];

} DL_SIG_CALL_SIM_MODIFIED_INFO_T;

typedef struct {

	DL_SIG_CALL_SS_ID_T                 ss_id;
	DL_SIG_CALL_SS_USSD_STRING_STRUCT_T ussd_string;

} DL_SIG_CALL_SS_USSD_REQUEST_IND_T;

typedef struct {

	DL_SIG_CALL_SS_ID_T                 ss_id;
	DL_SIG_CALL_SS_USSD_STRING_STRUCT_T ussd_string;

} DL_SIG_CALL_SS_USSD_NOTIFY_IND_T;

typedef struct {

	DL_SIG_CALL_SS_ID_T                 ss_id;
	DL_SIG_CALL_RESULT_T                result;
	DL_SIG_CALL_CAUSE_T                 cause;
	DL_SIG_CALL_SS_USSD_STRING_STRUCT_T ussd_string;

} DL_SIG_CALL_SS_USSD_COMPLETE_IND_T;

typedef struct {

	W_CHAR                               ss_string[DL_SIG_CALL_SS_USSD_STRING_MAX_LENGTH];
	DL_SIG_CALL_TYPE_OF_NUMBER_T         ton;
	DL_SIG_CALL_NUMBER_PLAN_IDENTIFIER_T npi;

} DL_SIG_CALL_SS_STRING_STRUCT_T;

typedef struct {

	DL_SIG_CALL_SS_ID_T                   ss_id;
	DL_SIG_CALL_RESULT_T                  result;
	DL_SIG_CALL_CAUSE_T                   cause;
	DL_SIG_CALL_SS_OPERATION_T            operation;
	DL_SIG_CALL_SS_CODE_T                 ss_code;
	DL_SIG_CALL_SS_BASIC_SERVICE_STRUCT_T basic_service;
	DL_SIG_CALL_SS_FWD_NO_REPLY_TIME_T    no_reply_time;
	DL_SIG_CALL_SS_RETURN_DATA_TYPE_T     return_data_type;
	DL_SIG_CALL_SS_RETURN_DATA_T          return_data;
	UINT8                                 ss_return_result[DL_SIG_CALL_SS_RETURN_RESULT_MAX_LENGTH];
	DL_SIG_CALL_SIM_MODIFIED_INFO_T       sim_modified_info;

} DL_SIG_CALL_SS_OPERATION_CNF_T;

typedef struct {

	W_CHAR number[DL_SIG_CALL_MAX_NUMBER_ARRAY_LENGTH];

} DL_SIG_CALL_NUMBER_STRING_STRUCT_T;

typedef struct {

	DL_SIG_CALL_SS_ID_T  ss_id;
	DL_SIG_CALL_RESULT_T result;
	DL_SIG_CALL_CAUSE_T  cause;

} DL_SIG_CALL_SS_OPERATION_STATUS_IND_T;

#ifdef __cplusplus
extern "C" {
#endif

	/* DL_SigCallSSOperationReq
	 * Create USSD request
	 */
	DL_SIG_CALL_SS_ID_T DL_SigCallSSOperationReq(
		IFACE_DATA_T                   *iface_data,
		DL_SIG_CALL_SS_STRING_STRUCT_T *ss_string,
		DL_SIG_CALL_STK_TYPE_T         stk_type
	);

	/* DL_SigCallSSAbortUSSDReq
	 * Cancel operation ss_id
	 */
	void DL_SigCallSSAbortUSSDReq(DL_SIG_CALL_SS_ID_T ss_id);

	/* DL_SigCallSSSendUSSDResponseReq
	 * Send answer on USSD request ss_id,
	 * return with DL_SIG_CALL_SS_USSD_COMPLETE_IND_ID event
	 */
	void DL_SigCallSSSendUSSDResponseReq(
		IFACE_DATA_T                        *iface_data,
		DL_SIG_CALL_SS_ID_T                 ss_id,
		DL_SIG_CALL_SS_USSD_STRING_STRUCT_T *ussd_string
	);

#ifdef __cplusplus
}
#endif

#endif // __SDK_USSD_H__

/* EOF */