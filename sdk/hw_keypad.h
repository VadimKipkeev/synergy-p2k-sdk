/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * Hardware keypad driver API
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef HW_KEYPAD_H
#define HW_KEYPAD_H

#include <typedefs.h>

#define KEYPAD_DATA_MASK 0xFC00

#define HAPI_KEYPAD_get_keycode() (((kpp.kpdr) | KEYPAD_DATA_MASK))
#define HAPI_KEYPAD_detect_key()  ((kpp.kpsr & 0x1) ? TRUE : FALSE)

// Keypad port module register struct
typedef struct {

	UINT16 kpcr; // Keypad Control Register
	UINT16 kpsr; // Keypad Status Register
	UINT16 kddr; // Keypad Data Direction Register
	UINT16 kpdr; // Keypad Data Register

} KPP_T;

extern volatile KPP_T kpp;

enum {

	RTIME_MAINT_KEYCODE_NO_KEY = 0xFFFF,
	RTIME_MAINT_KEYCODE_1 = 0xFE7F,      // Key "1"
	RTIME_MAINT_KEYCODE_2 = 0xFEF7,      // Key "2"
	RTIME_MAINT_KEYCODE_3 = 0xFD7F,      // Key "3"
	RTIME_MAINT_KEYCODE_4 = 0xFDF7,      // Key "4"
	RTIME_MAINT_KEYCODE_5 = 0xFF7E,      // Key "5"
	RTIME_MAINT_KEYCODE_6 = 0xFFF6,      // Key "6"
	RTIME_MAINT_KEYCODE_7 = 0xFFF3,      // Key "7"
	RTIME_MAINT_KEYCODE_8 = 0xFFF5,      // Key "8"
	RTIME_MAINT_KEYCODE_9 = 0xFFEB,      // Key "9"
	RTIME_MAINT_KEYCODE_10 = 0xFF7D,     // Key "*"
	RTIME_MAINT_KEYCODE_11 = 0xFEBF,     // Key "0"
	RTIME_MAINT_KEYCODE_12 = 0xFDBF,     // Key "#"
	RTIME_MAINT_KEYCODE_13 = 0xFEDF,     // Green key

	RTIME_MAINT_KEYCODE_15 = 0xFFBB,     // Soft right key
	RTIME_MAINT_KEYCODE_16 = 0xFFBD,     // Soft left key
	RTIME_MAINT_KEYCODE_17 = 0xFEEF,
	RTIME_MAINT_KEYCODE_18 = 0xFF7B,     // Menu key
	RTIME_MAINT_KEYCODE_19 = 0xFFED,
	RTIME_MAINT_KEYCODE_20 = 0xFDDF,     // Volime up key
	RTIME_MAINT_KEYCODE_21 = 0xFFDE,     // Volime down key
	RTIME_MAINT_KEYCODE_22 = 0xFFDD,     // Smart key
	RTIME_MAINT_KEYCODE_23 = 0xFFDB,     // Camera key
	RTIME_MAINT_KEYCODE_24 = 0xFFFF,
	RTIME_MAINT_KEYCODE_25 = 0xFFFF,
	RTIME_MAINT_KEYCODE_26 = 0xFFFF,
	RTIME_MAINT_KEYCODE_27 = 0xFFEE,     // Navigation right key
	RTIME_MAINT_KEYCODE_28 = 0xFDEF,     // Navigation left key
	RTIME_MAINT_KEYCODE_29 = 0xFFBE,

	RTIME_MAINT_KEYCODE_31 = 0xFF3F,
	RTIME_MAINT_KEYCODE_32 = 0xFF9F

};
typedef UINT16 RTIME_MAINT_KEYCODE_T;

#define RTM_KEY_0          RTIME_MAINT_KEYCODE_11
#define RTM_KEY_1          RTIME_MAINT_KEYCODE_1
#define RTM_KEY_2          RTIME_MAINT_KEYCODE_2
#define RTM_KEY_3          RTIME_MAINT_KEYCODE_3
#define RTM_KEY_4          RTIME_MAINT_KEYCODE_4
#define RTM_KEY_5          RTIME_MAINT_KEYCODE_5
#define RTM_KEY_6          RTIME_MAINT_KEYCODE_6
#define RTM_KEY_7          RTIME_MAINT_KEYCODE_7
#define RTM_KEY_8          RTIME_MAINT_KEYCODE_8
#define RTM_KEY_9          RTIME_MAINT_KEYCODE_9
#define RTM_KEY_STAR       RTIME_MAINT_KEYCODE_10
#define RTM_KEY_POUND      RTIME_MAINT_KEYCODE_12

#define RTM_KEY_SMART      RTIME_MAINT_KEYCODE_22
#define RTM_KEY_CAM        RTIME_MAINT_KEYCODE_23

#define RTM_KEY_UP         RTIME_MAINT_KEYCODE_24 // Not test
#define RTM_KEY_DOWN       RTIME_MAINT_KEYCODE_25 // Not test
#define RTM_KEY_LEFT       RTIME_MAINT_KEYCODE_28
#define RTM_KEY_RIGHT      RTIME_MAINT_KEYCODE_27
#define RTM_KEY_JOY_OK     RTIME_MAINT_KEYCODE_26 // Not test

#define RTM_KEY_GREEN      RTIME_MAINT_KEYCODE_13

#define RTM_KEY_SOFT_LEFT  RTIME_MAINT_KEYCODE_16
#define RTM_KEY_SOFT_RIGHT RTIME_MAINT_KEYCODE_17

#define RTM_KEY_MENU       RTIME_MAINT_KEYCODE_18
#define RTM_KEY_ITUNES     RTIME_MAINT_KEYCODE_22 // iTunes key for E1 and others

#define RTM_KEY_VOL_UP     RTIME_MAINT_KEYCODE_20
#define RTM_KEY_VOL_DOWN   RTIME_MAINT_KEYCODE_21

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif // HW_KEYPAD_H

/* EOF */