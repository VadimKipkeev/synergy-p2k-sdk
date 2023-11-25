/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * Event codes for ElfPack version 1.0
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef EV_CODES_H
	#define EV_CODES_H

	// USB cable plugin
	#define EV_DEVICE_ATTACH   0x1000
	#define EV_DEVICE_DETACH   0x1001

// Animation
#if !defined(FTR_V600)
	#define EV_FRAME_COMPLETED     0x20F1 // Frame is completed
	#define EV_CYCLE_COMPLETED     0x20F2 // Cycle (5 frames) is completed
	#define EV_ANIMATION_COMPLETED 0x20F3 // Animation (15 frames) is completed
#else
	#define EV_FRAME_COMPLETED     0x20F0 // Frame is completed
	#define EV_CYCLE_COMPLETED     0x20F1 // Cycle (5 frames) is completed
	#define EV_ANIMATION_COMPLETED 0x20F2 // Animation (15 frames) is completed
#endif

#define EV_GRANT_TOKEN         30
#define EV_REVOKE_TOKEN        31

#define EV_KEY_PRESS           500 // key_pressed
#define EV_KEY_RELEASE         501 // key_pressed

#define UIS_EV_INK_KEY_PRESS   0x2034
#define UIS_EV_INK_KEY_RELEASE (UIS_EV_INK_KEY_PRESS + 1)
#define CANVAS_EV_KEY_PRESS    UIS_EV_INK_KEY_PRESS
#define CANVAS_EV_KEY_RELEASE  UIS_EV_INK_KEY_RELEASE
#define EV_INK_KEY_PRESS       UIS_EV_INK_KEY_PRESS
#define EV_INK_KEY_RELEASE     UIS_EV_INK_KEY_RELEASE

// Volime control dialog call event
#if !defined(FTR_V600)
	#define EV_VOL_CHANGE_REQUEST 0x20CA
#else
	#define EV_VOL_CHANGE_REQUEST 0x20C9
#endif

// Call if dialog window is done
#define EV_DIALOG_DONE 0x201C

// Call if "Back" button is pressed
#define EV_DONE        0x2020

#if !defined(FTR_V600)

	// Call is navigate joystick to up and down in list window
	#define EV_LIST_NAVIGATE 0x2043 // index

	// Call if joystick or "Select" button is pressed in list window
	#define EV_SELECT        0x2058 // index
#else

	// Call is navigate joystick to up and down in list window
	#define EV_LIST_NAVIGATE 0x2042 // index

	// Call if joystick or "Select" button is pressed in list window
	#define EV_SELECT         0x2057 // index
#endif

// Send as lists, that get another piece of data
#define EV_REQUEST_LIST_ITEMS 0x202C // list_items_req

#if !defined(FTR_V600)
	
	// Send as request
	#define EV_NO  0x2046
	#define EV_YES 0x2079
#else

	// Send as request
	#define EV_NO  0x2045
	#define EV_YES 0x2078
#endif

// Cancel event
#define EV_CANCEL        0x2008

// Data is getting
#define EV_DATA          0x200F // EVENT_T::attachment

#define EV_BROWSE        0x2006

// Call at changing user any field
#define EV_DATA_CHANGE   0x2011 // index

// Requesting data
#define EV_REQUEST_DATA  0x202B // data_req

// Timer expired event
#define EV_TIMER_EXPIRED 0x8205A // Return with (DL_TIMER_DATA_T*)EVENT_T::attachment

// Gain focus event
#define EV_GAIN_FOCUS    20

// Lose focus event
#define EV_LOSE_FOCUS    21

#define EV_RENDER        25

// Close screensaver
#define EV_USER_ACTIVITY 0x7F1

// Network register
#define EV_REG_NETWORK   0x8200B

// Power down
#define EV_POWER_DOWN    0x11

// Calling from APP_DONE
#define EV_APP_DONE      0x0C

#if defined(FTR_L7E)
	#define EV_CREATE_SHORTCUT 0x20C9 // Menu key pressed
#elif defined(FTR_V600)
	#define EV_CREATE_SHORTCUT 0x20C4 // Menu key pressed
#else
	#define EV_CREATE_SHORTCUT 0x20C5 // Menu key pressed
#endif

#define WS_EVENT                0x82143 // In attach WS_EVENT_T event
#define EV_MSG_READ             0x82068 // In attach MSG_READ_T event

#define EV_SS_OPERATION         0x82028
#define EV_SS_USSD_NOTIFY       0x82039
#define EV_SS_USSD_REQUEST      0x8203A
#define EV_SS_USSD_COMPLETE     0x8203B

#define EV_DSMA_PROXY_CREATE    0x821B1
#define EV_DSMA_PROXY_STATE     0x821B2
#define EV_DSMA_BUFF_STATE      0x821B3
#define EV_DSMA_PROXY_ATTR      0x821B4

#define EV_DBK_ASYNC_OPERATION  0x8206A
#define EV_DBK_ADD_EVENT        0x8206B
#define EV_DBK_DATABASE_QUERY   0x8206C // Answer on request
#define EV_DBK_DATABASE_SLOT    0x8206D
#define EV_DBK_DATABASE_ALTERED 0x8206E // Changes in database
#define EV_DBK_DATABASE_ALARM   0x8206F
#define EV_DBK_NUM_OF_EVENTS    0x82070
#define EV_DBK_DATABASE_IDLE    0x820D5 // Database is idle mode
#define EV_DBK_WEEK_VIEW        0x82126 // Answer on request week view
#define EV_DBK_MONTH_VIEW       0x822CF // Answer on request month view

// missed call
#ifdef PATCH
	extern const UINT32 EV_MISSEDCALLS;
	#define EV_MISSED_CALLS (EV_MISSEDCALLS)
#else
	extern const UINT32 *EV_MISSEDCALLS;
	#define EV_MISSED_CALLS (*EV_MISSEDCALLS)
#endif

// Desktop gain focus
#ifdef PATCH
	extern const UINT32 EV_IDLE_GAIN_FOCUS;
	#define EV_IDLE_FOCUS (EV_IDLE_GAIN_FOCUS)
#else
	extern const UINT32 *EV_IDLE_GAIN_FOCUS;
	#define EV_IDLE_FOCUS (*EV_IDLE_GAIN_FOCUS)
#endif

/* Incoming call
 * phone number in attach
 */
#ifdef PATCH
	extern const UINT32 CALL_ALERT;
	#define EV_CALL_ALERT (CALL_ALERT)
#else
	extern const UINT32 *CALL_ALERT;
	#define EV_CALL_ALERT (*CALL_ALERT)
#endif

/* Alarm is reminder start
 * alarm number in attach
 */
#ifdef PATCH
	extern const UINT16 ALMCLK_REMINDER_START;
	#define EV_ALMCLK_REMINDER_START (ALMCLK_REMINDER_START)
#else
	extern const UINT16 *ALMCLK_REMINDER_START;
	#define EV_ALMCLK_REMINDER_START (*ALMCLK_REMINDER_START)
#endif

// Calendar event
#ifdef PATCH
	extern const UINT32 DATEBOOK_REMINDER;
	#define EV_DATEBOOK_REMINDER (DATEBOOK_REMINDER)
#else
	extern const UINT32 *DATEBOOK_REMINDER;
	#define EV_DATEBOOK_REMINDER (*DATEBOOK_REMINDER)
#endif

// Disable display activity
#ifdef PATCH
	extern const UINT32 EV_DisplayTimeout;
	#define EV_DISPLAY_NO_ACTIVE (EV_DisplayTimeout)
#else
	extern const UINT32 *EV_DisplayTimeout;
	#define EV_DISPLAY_NO_ACTIVE (*EV_DisplayTimeout)
#endif

// Enable display activity
#ifdef PATCH
	extern const UINT32 EV_DisplayActivity;
	#define EV_DISPLAY_ACTIVE (EV_DisplayActivity)
#else
	extern const UINT32 *EV_DisplayActivity;
	#define EV_DISPLAY_ACTIVE (*EV_DisplayActivity)
#endif

// Locking keypad event
#ifdef PATCH
	extern const UINT32 EV_LOC_KPAD;
	#define EV_KEYPAD_LOCK (EV_LOC_KPAD)
#else
	extern const UINT32 *EV_LOC_KPAD;
	#define EV_KEYPAD_LOCK (*EV_LOC_KPAD)
#endif

// Unlocking keypad event
#ifdef PATCH
	extern const UINT32 EV_UNLOC_KPAD;
	#define EV_KEYPAD_UNLOCK (EV_UNLOC_KPAD)
#else
	extern const UINT32 *EV_UNLOC_KPAD;
	#define EV_KEYPAD_UNLOCK (*EV_UNLOC_KPAD)
#endif

// Send file by Bluetooth
#ifdef PATCH
	extern const UINT32 EVENT_BT;
	#define EV_BT_SEND (EVENT_BT)
#else
	extern const UINT32 *EVENT_BT;
	#define EV_BT_SEND (*EVENT_BT)
#endif

/* Starting preview at bluetooth on WAP file sending
 * name of file and name with path of temporary file in attach
 */
#ifdef PATCH
	extern const UINT32 EV_PREVIEW_START;
	#define EV_START_PREVIEW (EV_PREVIEW_START)
#else
	extern const UINT32 *EV_PREVIEW_START;
	#define EV_START_PREVIEW (*EV_PREVIEW_START)
#endif

#ifdef PATCH
	extern const UINT32 EV_UIS_REFRESH;
	#define EV_REQUEST_RENDER (EV_UIS_REFRESH)
#else
	extern const UINT32 *EV_UIS_REFRESH;
	#define EV_REQUEST_RENDER (*EV_UIS_REFRESH)
#endif

// IMEI SEEM offset
#ifdef PATCH
	extern const UINT32 SEEM_IMEI;
	#define DB_FEATURE_IMEI (SEEM_IMEI)
#else
	extern const UINT32 *SEEM_IMEI;
	#define DB_FEATURE_IMEI (*SEEM_IMEI)
#endif

// IMSI SEEM offset
#ifdef PATCH
	extern const UINT32 SEEM_IMSI;
	#define DB_FEATURE_IMSI (SEEM_IMSI)
#else
	extern const UINT32 *SEEM_IMSI;
	#define DB_FEATURE_IMSI (*SEEM_IMSI)
#endif

// Keypad lock status: 1 - locked, 0 - unlocked
#ifdef PATCH
	extern const UINT32 KEYPAD_STATE;
	#define DB_FEATURE_KEYPAD_STATE (KEYPAD_STATE)
#else
	extern const UINT32 *KEYPAD_STATE;
	#define DB_FEATURE_KEYPAD_STATE (*KEYPAD_STATE)
#endif

#if defined(FTR_V600)
	#define EV_USER_ACTIVITY_TIMEOUT 0x074F
	#define EV_SCREENSAVER_TIMEOUT   0x0751
	#define EV_DISPLAY_TIMEOUT       0x0752
	#define EV_BACKLIGHT_TIMEOUT     0x0753
	#define EV_INACTIVITY_TIMEOUT    0x0754
#else
	#define EV_USER_ACTIVITY_TIMEOUT 0x07EE
	#define EV_SCREENSAVER_TIMEOUT   0x07F0
	#define EV_DISPLAY_TIMEOUT       0x07F1
	#define EV_BACKLIGHT_TIMEOUT     0x07F2
	#define EV_INACTIVITY_TIMEOUT    0x07F3
#endif

#define EV_ADD_MISSED_CALL       0x8201B
#define EV_REMOVE_MISSED_CALL    0x0398

#define EV_FLIP_CLOSED           0x20BE
#define EV_FLIP_OPENED           0x20BF

#endif // EV_CODES_H

/* EOF */