/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * Alarm SDK
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef __SDK_ALARM_H__
#define __SDK_ALARM_H__

#include <typedefs.h>
#include <time_date.h>

#define ALARM_RECORD_NAME_LEN 24

typedef struct {

	UINT8      index;
	WCHAR      name[ALARM_RECORD_NAME_LEN + 1];
	CLK_TIME_T time;
	UINT64     alert_tone;
	BOOL       is_alarm_enabled;
	UINT8      alarm_id;
	UINT8      ringer_volume;
	BOOL       is_wake_up_alarm;

} ALMCLK_RECORD_T;

#ifdef __cplusplus
extern "C" {
#endif

	#define EV_ALMCLK_CHANGE 0x822BA // Change alarms

	/* Register application for send update data message to application, if alarm is changed
	 * message get to EV_ALMCLK_CHANGE event
	 */
	UINT32 DL_DbAlmclkRegisterApplication(SU_PORT_T su_port);

	UINT32 DL_DbAlmclkUnregisterApplication(SU_PORT_T su_port);

	// Get alarm record
	UINT32 DL_DbAlmclkGetRecordByIndex(UINT8 index, ALMCLK_RECORD_T *record);

	// Create alarm record
	UINT32 DL_DbAlmclkCreateRecord(ALMCLK_RECORD_T *record);

	// Delete all alarm records
	UINT32 DL_DbAlmclkDeleteAllRecords(void);

	// Delete alarm record
	UINT32 DL_DbAlmclkDeleteRecordByIndex(UINT8 index);

#ifdef __cplusplus
}
#endif

#endif	// __SDK_ALARM_H__

/* EOF */