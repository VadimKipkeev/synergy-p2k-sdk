/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * Shortcuts SDK
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef __SDK_SC_H__
#define __SDK_SC_H__

#include <typedefs.h>

#define SC_TYPE_URL       5
#define SC_TYPE_APP       6

#define SC_TEXT_LEN       16
#define SC_MAX_NUMBER     100
#define SC_ALL_RECORD     0xFE
#define SC_INVALID_RECORD 0xFF

typedef UINT8 SC_TYPE_T;

typedef struct {

	UINT8     seem_rec;              // seem_rec - 1
	SC_TYPE_T type;                  // Shortcut type
	UINT8     index;                 // Number of list, starting from 1
	UINT8     unk1;                  // == 0xFE
	UINT32    ev_code;
	UINT32    list1_index;           // Selected item ID in list
	UINT32    param1;
	UINT32    list2_index;           // Last index
	UINT32    param2;
	INT32     data;                  // Used for data pointer, for example data pointer for AIX, not Windows compatible 
	UINT32    lang_text;             // RESOURCE_ID
	WCHAR     text[SC_TEXT_LEN + 1]; // Shortcut memory
	UINT16    unk2;                  // == 0xffbd

} SEEM_0002_T;

typedef struct {

	UINT8  type;
	UINT32 param1;
	UINT32 list1_index;
	UINT32 param2;
	UINT32 list2_index;
	WCHAR  text[SC_TEXT_LEN + 1]; // 0x22 = 34
	UINT32 lang_text;

} SHORTCUT_CREATE_T;              // 0x3c = 60

typedef struct {

	UINT8       result; // 0 if successful
	UINT8       unk0;
	SEEM_0002_T *record;

} SHORTCUT_READ_RECORD_T;

typedef struct {

	UINT8  esult;
	UINT16 url_strlen;
	UINT8  url[100];

} SHORTCUT_READ_URL_T;

#ifdef __cplusplus
extern "C" {
#endif

	// Create shortcut record
	UINT8 DL_DbShortcutCreateRecord(IFACE_DATA_T *data, SEEM_0002_T record);

	// Update shortcut record
	UINT8 DL_DbShortcutUpdateRecord(IFACE_DATA_T *data, SEEM_0002_T record);

	// Delete shortcut record
	UINT8 DL_DbShortcutDeleteRecord(IFACE_DATA_T *data, UINT8 seem_rec);

	// Get shortcut, async function, send to EV_SHORTCUT_READ_RECORD event, in attachment content SHORTCUT_READ_RECORD_T
	UINT8 DL_DbShortcutGetRecordByRecordId(IFACE_DATA_T *data, UINT8 seem_rec);

	// Get avaliable records count
	UINT16 DL_DbShortcutGetNumOfRecordsAvailable(void);

	// Get used records count
	UINT16 DL_DbShortcutGetNumOfRecordsUsed(BOOL voice_shortcut);

	/* DL_DbShortcutIsNumberAvailable
	 * first avaliable number
	 */
	UINT8 DL_DbGetFirstAvailableNumber(void);

	// Get URL, used records count
	UINT16 DL_DbShortcutGetNumOfURLRecordsUsed(void);

	// Get URL avaliable records count
	UINT16 DL_DbShortcutGetNumOfURLRecordsAvailable(void);

	// Get URL, async function, send EV_SHORTCUT_READ_URL event
	UINT32 DL_DbShortcutGetURLByURLId(IFACE_DATA_T *data, UINT32 URLId);

	// Get record type
	SC_TYPE_T DL_DbShortcutGetshortcutType(UINT8 index);

	// Create shortcut
	UINT32 APP_UtilShortcutCreateAppShortcut(
		EVENT_STACK_T *ev_st,
		void          *app,
		UINT32        event_code
	);

#ifdef __cplusplus
}
#endif

#endif // __SDK_SC_H__

/* EOF */