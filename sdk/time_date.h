/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * Time and date SDK
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef __SDK_TIME_DATE_H__
#define __SDK_TIME_DATE_H__

#include <typedefs.h>

typedef struct {

	UINT8  day;
	UINT8  month;
	UINT16 year;

} CLK_DATE_T;

typedef struct {

	UINT8 hour;
	UINT8 minute;
	UINT8 second;

} CLK_TIME_T;

typedef struct {

	CLK_TIME_T time;
	CLK_DATE_T date;
	UINT32     unk;

} DL_ALARM_DATA_T;

typedef struct {

	UINT32 time;
	UINT32 ID;

} DL_TIMER_DATA_T;

#ifdef __cplusplus
extern "C" {
#endif

	// Get system time in ticks (suAPI - native RTOS timer)
	UINT64 suPalReadTime(void);

	// Translate ticks time to milliseconds (suAPI - native RTOS timer)
	UINT64 suPalTicksToMsec(UINT64 ticks);

	// Get system date
	BOOL DL_ClkGetDate(CLK_DATE_T *date);

	// Set system date
	BOOL DL_ClkSetDate(CLK_DATE_T date);

	// Get system time
	BOOL DL_ClkGetTime(CLK_TIME_T *time);

	// Set system time
	BOOL DL_ClkSetTime(CLK_TIME_T time);

	typedef UINT32 CLK_CLOCK_T; // Milliseconds count from Jan. 1, 1970, GMT

	UINT8 DL_ClkGetClock(CLK_CLOCK_T *clock);

	UINT8 DL_ClkSetClock(CLK_CLOCK_T clock);

	// Set time to wakeup
	UINT8 DL_ClkSetWakeupEvent(CLK_CLOCK_T wakeup_time);
	
	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Alarm functions ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	// Alarm is done
	#define EV_ALARM_EXPIRED 0x82059 // (CLK_ALARM_DATA_T*)EVENT_T::attachment

	// Set alarm event
	BOOL DL_ClkStoreIndividualEvent(IFACE_DATA_T *data, DL_ALARM_DATA_T alarm_data);

	// Delete alarm event
	BOOL DL_ClkDeleteIndividualEvent(
		IFACE_DATA_T    *data,
		DL_ALARM_DATA_T alarm_data,
		UINT8           mask        // 1 - time, 2 - date... 63 - total delete
	);
	
	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Timer functions ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	/* When the timer fires, it creates an EV_TIMER_EXPIRED event whose attachment points to DL_TIMER_DATA_T
	 * run a timer, whose works from time in milliseconds
	 */
	UINT32 APP_UtilStartTimer(
		UINT32        time,
		UINT32        ID,   // ID inside DL_TIMER_DATA_T at event handler
		APPLICATION_T *app
	);

	// Run a timer that will go off every time in milliseconds
	UINT32 APP_UtilStartCyclicalTimer(
		UINT32        time,
		UINT32        ID,
		APPLICATION_T *app
	);

	// Stop timer
	UINT32 APP_UtilStopTimer(APPLICATION_T *app);

	UINT32 DL_ClkStartTimer(
		IFACE_DATA_T *iface,
		UINT32       period,
		UINT32       id
	);

	UINT32 DL_ClkStartCyclicalTimer(
		IFACE_DATA_T *iface,
		UINT32       period,
		UINT32       id
	);

	UINT32 DL_ClkStopTimer(IFACE_DATA_T *iface);

#ifdef __cplusplus
}
#endif

#endif // __SDK_TIME_DATE_H__

/* EOF */