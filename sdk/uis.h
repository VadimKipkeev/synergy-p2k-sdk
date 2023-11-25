/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * User Interface System API
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef UIS_H
#define UIS_H

#include <typedefs.h>
#include <resources.h>
#include <filesystem.h>
#include <time_date.h>
#include <dl.h>

#ifdef __cplusplus
extern "C" {
#endif

	enum {

		ACTION_OP_ADD = 0,
		ACTION_OP_DELETE,
		ACTION_OP_UPDATE

	};

	typedef struct {

		UINT8        operation;  // That action to ACTION_OP_*
		EVENT_CODE_T event;      // Event, created at selecting this action
		RESOURCE_ID  action_res; // Resource descript selected action (RES_ACTION_LIST_ITEM_T)

	} ACTION_ENTRY_T;

	typedef struct {

		EVENT_CODE_T event;      // Event, created at selecting this action
		RESOURCE_ID  action_res; // Resource descript selected action (RES_ACTION_LIST_ITEM_T)
	
	} CORE_ACTION_ENTRY_T;

	#define UIS_MAX_NUM_ACTION_LIST_ITEMS 16

	typedef struct {

		UINT8          count;                                 // Items count
		ACTION_ENTRY_T action[UIS_MAX_NUM_ACTION_LIST_ITEMS]; // Commands list for working with action list

	} ACTIONS_T;

	typedef struct UIS_TAG_AND_INDEX_T {

		INT32 index;
		INT32 tag;

	} UIS_TAG_AND_INDEX_T;

	typedef union {

		RESOURCE_ID         name;
		CLK_TIME_T          time;
		CLK_DATE_T          date;
		UINT32              number;
		WCHAR               *string;
		UINT8               status_ID;
		UIS_TAG_AND_INDEX_T list_entry_id;
		struct CONTENT_T    *content;
		FS_MID_T            file_id;

		UINT32              set_fill_percent; // Progress Bar - fill percentage
		WCHAR               *set_meter_value; // Progress Bar - Meter value string
		WCHAR               *set_object_name; // Progress Bar - Object Name string

	} UIS_VALUE_T; // 8 bytes

	#define UIS_FORMAT_SIZE    40
	#define UIS_MAX_NUM_VALUES 20

	typedef struct CONTENT_T {

		char        format[UIS_FORMAT_SIZE];    // == 40
		UINT32      count;                      // == 4
		UIS_VALUE_T values[UIS_MAX_NUM_VALUES]; // 8 * 20 = 160

	} CONTENT_T; // 204 bytes

	typedef enum {

		LIST_IMAGE_MEDIA_PATH_T = 0,
		LIST_IMAGE_RESOURCE_ID_T,
		LIST_IMAGE_DL_FS_MID_T,               // This used J2ME applications list
		LIST_IMAGE_MEDIA_PATH_WITH_OFFSET_T,
		LIST_IMAGE_POINTER

	} LIST_IMAGE_TYPE_T;

	typedef struct {

		WCHAR  *file_name; // File name
		UINT32 offset;     // Offset
		UINT32 size;       // Size
		UINT8  mime_type;  // Type

	} LIST_IMAGE_FILE_T;

	typedef struct {

		void   *file_name; // Pointer to image
		UINT32 image_size; // Size

	} LIST_IMAGE_POINTER_T;

	typedef union {

		LIST_IMAGE_FILE_T    image_file;
		LIST_IMAGE_POINTER_T image_ptr;
		FS_MID_T             file_id;
		WCHAR                *file_name;
		RESOURCE_ID          resource_id;

	} LIST_IMAGE_T;

	typedef struct {

		LIST_IMAGE_T      image;
		UINT16            image_index;
		LIST_IMAGE_TYPE_T image_type;

	} LIST_IMAGE_ELEMENT_T;

	typedef struct {

		RESOURCE_ID descr_res;           // 0x00 resource with FIELD_DESCR_T
		UIS_VALUE_T value;               // 0x04 current value (RESOURCE_ID/WCHAR*/CONTENT_T*/UINT32)
		BOOL        defined;             // 0x0c combobinary: blank/value
		BOOL        value_on;            // 0x0d combobinary: only defined == TRUE, OFF/value
		BOOL        app_control_editing; // 0x0e = 0

	} FIELD_T, UIS_FIELD_T;

	#define UIS_MAX_NUM_MARKS 2

	typedef struct {

		CONTENT_T   text;
		UINT32      number;                   // For numbered list only
		RESOURCE_ID marks[UIS_MAX_NUM_MARKS];

		#if !defined(FTR_V600)
			RESOURCE_ID unk3[2];
			RESOURCE_ID unk4[2];
			UINT8       unk5;
		#endif
			UINT8   formatting;

	} STATIC_LIST_ENTRY_T;

	typedef union {

		STATIC_LIST_ENTRY_T static_entry;   // Used, there editable == FALSE
		FIELD_T             editable_entry; // Used, there editable == TRUE

		#if !defined(FTR_V600)
			UINT8 pad[0xEC];
		#else
			UINT8 pad[0xE6];
		#endif

	} LIST_CONTENT_T;

	typedef struct {

		BOOL           editable;     // Possible to change content
		INT32          tag;
		LIST_CONTENT_T content;

		/* --------------------------------------------------------------------------------------------------------------------------------
		 * EXL:
		 * 02-Jul-2023: Fix LIST_ENTRY_T struct size
		 * 17-Aug-2023: Fix it again
		 * --------------------------------------------------------------------------------------------------------------------------------
		 * V600 sizeof:    244 (f4): 2928
		 * ROKR E1 sizeof: 248 (f8): 2976
		 * --------------------------------------------------------------------------------------------------------------------------------
		 */
		BOOL           selection_list; // If true, then action selectable and enabled
		UINT8          pad;
		BOOL           selectable;     // If false, then selected (cursor to skip this item)
		BOOL           enabled;        // If false, then draw another color

	} LIST_ENTRY_T;
	
	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Utils functions ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	// Create content from string
	UINT32 UIS_MakeContentFromString(const char *format, CONTENT_T *dst, ...);

	/* Description about format string:
	 * String contains from pointers to function arguments and align specifications pointers,
	 * formed as type and number function parameter
	 *	
	 * Possible types:
	 * a - animation
	 * d - date
	 * q - pointer to WCHAR string
	 * s - string resource
	 * i - INT type
	 * j - LIST_IMAGE_ELEMENT_T
	 * l - LONG type
	 * g - HEX INT
	 * p - picture resource
	 * r - CONTENT_T
	 * f - pointer to file
	 * t - time
	 *
	 * Align specifications pointers:
	 * N - new string
	 * S - text distribution
	 * C - text at center (horizontal align)
	 * L - cut string with "..." in ending, if string very long
	 * M - text at center (vertical align)
	 * T - text at top
	 * B - text at bottom
	 *
	 * For example: "MCq0p1" - Align at center and middle first parameter after dst as string, and second parameter as picture
	 */

	// Handle event of dialog
	UINT32 UIS_HandleEvent(UIS_DIALOG_T dialog, EVENT_STACK_T *ev_st);

	// Call full refresh UI
	UINT32 UIS_Refresh(void);

	// Same too, but force
	void UIS_ForceRefresh(void);

	// Delete dialog and set to NULL
	UINT32 APP_UtilUISDialogDelete(UIS_DIALOG_T *pdialog);

	UINT32 UIS_Delete(UIS_DIALOG_T dialog);

	// Set new action list
	UINT32 UIS_SetActionList(UIS_DIALOG_T dialog, ACTIONS_T *action_list);

	// Clear and set new action list
	UINT32 UIS_ClearAndSetActionList(UIS_DIALOG_T dialog, ACTIONS_T *action_list);

	// Set event cursor to center
	UINT32 UIS_SetCenterSelectAction(UIS_DIALOG_T dialog, EVENT_CODE_T center_select_action);

	// Set event to "C" button
	UINT32 UIS_SetClearKeyAction(UIS_DIALOG_T dialog, CORE_ACTION_ENTRY_T clear_action);

	#define DialogType_None             0x00 // None
	#define DialogType_Dialling         0x05 // Dial-up window
	#define DialogType_EnterName        0x08 // Input names
	#define DialogType_SetDate          0x0B // Set Date
	#define DialogType_SetTime          0x0D // Set-up time
	#define DialogType_Homescreen       0x0E // Desktop standby
	#define DialogType_List             0x10 // Item List
	#define DialogType_SelectionList    0x13 // Options
	#define DialogType_BatteryandMemory 0x15 // Power, memory usage information, such as window howed that the grid
	#define DialogType_JumpOut          0x17 // Pop-up window, such as "keyboard is locked, unlocked by XX", "please wait" category
	#define DialogType_MessageBox       0x1B // Information inbox
	#define DialogType_GameAni          0x1D // Games and applications when they enter the animation
	#define DialogType_WapMenu          0x1E // Wap browser-related menu
	#define DialogType_VideoCamera      0x25 // Camera viewfinder window
	#define DialogType_Password         0x26 // Password window
	#define DialogType_PB_SC_Other      0x28 // Phone book, shortcuts like, a lot of this state
	#define DialogType_Menu             0x2D // Main Menu
	#define DialogType_SecondLevelMenu  0x2E // 2 of the 3 menu and the menu
	#define DialogType_WriteText        0x32 // Input text
	#define DialogType_Brightness       0x37 // Settings: brightness - highlighted regulation
	#define DialogType_Picture          0x39 // Multimedia - picture

	/* Return type of top dialog, in firmware applications used for detected on desktop place
	 * if res value 0xE, then displayed on desktop, for standart list res have value 0x10, you must experimenting if you want
	 */
	
	UINT32 UIS_GetActiveDialogType(UINT8 *res);
	
	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Create dialog window functions ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	UIS_DIALOG_T UIS_CreateNullDialog(SU_PORT_T *port);

	// Type of Trancient Notice
	enum {

		NOTICE_TYPE_DEFAULT = 0,                    // With icon "Warning"
		NOTICE_TYPE_OK,                             // With icon "Green check"
		NOTICE_TYPE_FAIL,                           // With icon "Fail"
		NOTICE_TYPE_WAIT,
		NOTICE_TYPE_WAIT_NO_KEY = NOTICE_TYPE_WAIT, // Button is lock, to ending of content added points, application will be switch to another state
		                                            // with buttons can be exit only by call shortcut (application will be close)

		NOTICE_TYPE_WAIT_2,                         // No points, if any key press generate event EV_DIALOG_DONE
		NOTICE_TYPE_INFO_NO_KEY,                    // No action on keypress
		NOTICE_TYPE_INFO,
		NOTICE_TYPE_OK_2,

		NOTICE_TYPE_DELETED = 12,
		NOTICE_TYPE_NEW_MESSAGE,
		NOTICE_TYPE_SMS,
		NOTICE_TYPE_SEND,
		NOTICE_TYPE_SEND_CENTER,

		NOTICE_TYPE_WAIT_3 = 27,                    // With points, keys no locked
		NOTICE_TYPE_WAIT_4,                         // Text at left, with points, on red key press generate EV_DIALOG_DONE
		NOTICE_TYPE_INFO_LONG,
		NOTICE_TYPE_WAIT_FAST,                      // Waiting dialog on 0.5 second

		NOTICE_TYPE_WAIT_5 = 32,                    // Same too NOTICE_TYPE_WAIT_2

		NOTICE_TYPE_WAIT_6 = 37,                    // Text at center, with points, on any key press generate EV_DIALOG_DONE

		NOTICE_TYPE_CHAT = 45,
		NOTICE_TYPE_NEW_CHAT_MESSAGE

	};
	typedef UINT8 NOTICE_TYPE_T;

	enum {

		INCOMING_CALL_STATUS = 0,
		CALLING_STATUS,
		CONNECTED_STATUS,
		NO_STATUS

	};

	enum {

		EXTENDENT_NOTICE_GENERAL = 0,
		EXTENDENT_NOTICE_DELAY,
		EXTENDENT_NOTICE_TRANSIENT

	};
	typedef UINT8 EXTENDENT_NOTICE_TYPE_T;

	typedef struct {

		RESOURCE_ID icon1;
		RESOURCE_ID icon2;
		RESOURCE_ID animation_icon1;
		RESOURCE_ID animation_icon2;
		void        *key_translation_table;
		RESOURCE_ID title;
		UINT8       numberOfKeyTranslations;
		UINT8       numberOfResources;
		BOOL        isCritical;

	} NOTICE_PARAMETERS_T;

	// Create notice window: type = NOTICE_TYPE_
	UIS_DIALOG_T UIS_CreateTransientNotice(
		SU_PORT_T *port,
		CONTENT_T *content,
		UINT8     type
	);

	UIS_DIALOG_T UIS_CreateNotice(
		SU_PORT_T *port,
		CONTENT_T *content,
		UINT32    duration,
		UINT8     type,
		BOOL      critical,
		ACTIONS_T *actions
	);

	UIS_DIALOG_T UIS_CreateExtendedNotice(
		SU_PORT_T           *port,
		CONTENT_T           *content,
		UINT32              duration,    // Display time
		UINT8               type,
		UINT16              status,
		NOTICE_PARAMETERS_T parameters,
		ACTIONS_T           *actions
	);

	// Create confirmation dialog window
	UIS_DIALOG_T UIS_CreateConfirmation(SU_PORT_T *port, CONTENT_T *content);

	enum {

		UIS_LIST_VIEW_SUMMARY = 0,
		UIS_LIST_VIEW_DETAIL,
		UIS_LIST_VIEW_DEFAULT,
		UIS_LIST_VIEW_PAGEABLE_DETAIL,
		UIS_LIST_VIEW_DETAIL_BY_LINE,
		UIS_LIST_VIEW_DETAIL_SAVE_MEMORY,
		UIS_LIST_VIEW_PAGEABLE_SUMMARY,
		UIS_LIST_VIEW_SUMMARY_WITH_SUBTITLE

	};
	typedef UINT8 UIS_LIST_VIEW_T;

	// Create dialog window with list
	UIS_DIALOG_T UIS_CreateList(
		SU_PORT_T   *port,
		UINT32      param1,        // == 0 ID
		UINT32      count,         // Items count in list
		UINT32      marks,         // Checkboxes
		UINT32      *starting_num, // First selected item in list
		BOOL        reorder,	   // == 0
		UINT8       view,          // == 2
		ACTIONS_T   *actions,      // Actions list
		RESOURCE_ID caption        // Dialog caption
	);

	// Create dialog window with static list
	UIS_DIALOG_T UIS_CreateStaticList(
		SU_PORT_T    *port,
		UINT32       param1,   // == 0 ID
		UINT32       count,
		UINT32       marks,
		LIST_ENTRY_T *entries,
		BOOL         reorder,  // == 0
		UINT8        view,     // == 2
		ACTIONS_T    *actions,
		RESOURCE_ID  caption
	);

	UIS_DIALOG_T UIS_CreateSelectionEditor(
		SU_PORT_T   *app_env,
		UINT32      list_handle,
		UINT32      list_size,
		UINT32      current_position,
		UINT32      *num_entries_to_get,
		RESOURCE_ID possible_values,
		ACTIONS_T   *action_list,
		RESOURCE_ID dialog_resource_id
	);

	UIS_DIALOG_T UIS_CreateStaticSelectionEditor(
		SU_PORT_T    *app_env,
		UINT32       list_handle,
		UINT32       list_size,
		LIST_ENTRY_T *list_entries,
		UINT32       current_position,
		ACTIONS_T    *action_list,
		RESOURCE_ID  dialog_resource_id
	);

	// Create character editor with area for text typing
	UIS_DIALOG_T UIS_CreateCharacterEditor(
		SU_PORT_T   *port,
		WCHAR       *text,
		UINT8       edit_type,
		UINT32      maxlen,
		BOOL        masked,   // Text typing with stars, for example: hidden password typing
		ACTIONS_T   *actions,
		RESOURCE_ID dlgres
	);

	/* Value of edit_type:
	 * 0 -  Every Word With Big Letter
	 * 1 -  simple text
	 * 2 -  Every sentence Capitalized
	 * 3 -  same too for very long string
	 * 4 -  phone number
	 * 5 -  ALL LETTERS ARE BIGGEST
	 * 6 -  string as a sequence of numeric segments
	 * 7 -  simple text, without changing modes
	 * 8 -  same too, without detalized
	 * 9 -  as 4, without more menu
	 * 10 - same too, without detalized
	 * 11 - as 0, with possibility typing empty string
	 * 12 - as 1, with possibility typing empty string
	 * 23 - url
	 * 28 - string with attaches
	 * 29 - same too, but possible is empty
	 * 32 - only numbers
	 */

	// Create viewer dialog
	UIS_DIALOG_T UIS_CreateViewer(
		SU_PORT_T *port,
		CONTENT_T *contents,
		ACTIONS_T *actions
	);

	// Create list with pictures and text
	UIS_DIALOG_T UIS_CreatePictureAndTextList(
		SU_PORT_T   *port,
		UINT32      param1,
		UINT32      count,
		UINT32      *starting_num,
		UINT8       param4,        // == 2
		UINT8       param5,        // == 0
		UINT8       param6,        // == 1, try 0, 2, and etc...
		ACTIONS_T   *actions,
		RESOURCE_ID dlgres
	);

	// Create splash screen
	UIS_DIALOG_T UIS_CreateSplashScreenFs(
		SU_PORT_T *port,
		WCHAR     *uri,
		UINT32    unk     // unk = 0x7D0
	);

	// Same too, but from DRM
	UIS_DIALOG_T UIS_CreateSplashScreen(
		SU_PORT_T   *port,
		RESOURCE_ID img,
		UINT32      unk     // unk = 0xD3, 0x7D0
	);

	// Create progressbar
	UIS_DIALOG_T UIS_CreateProgressBar(
		SU_PORT_T   *port,
		RESOURCE_ID primary_icon,      // 0x12000055
		CONTENT_T   *content,
		const WCHAR *object_name,
		UINT32      fill_percentage,
		BOOL        arrovs,
		const WCHAR *meter_value,
		ACTIONS_T   *actions,
		RESOURCE_ID dlgres
	);
	
	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Skins API ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	// Get current used skin index value
	UINT16 UIS_GetCurrentSkinIndex(void);

	// Get default  skin index value
	UINT16 UIS_GetDefaultSkinIndex(void);

	// Get skin name by index
	WCHAR *UIS_GetSkinName(UINT16 skin_id);

	// Get numbers of skins
	UINT16 UIS_GetNumSkins(void);

	// Set skin by index
	void UIS_SetSkin(UINT16 skin_id);

	// Skin folder - string in unicode
	#if (defined(EP2) || defined(PATCH))
		extern const WCHAR SKIN_FOLDER[];
	#else
		extern const WCHAR *SKIN_FOLDER;
	#endif
	
	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Desktop elements control ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	#define BATTERY_STRENGTH_STATUS 0 // Battery: integer value from 0 to 3
	#define SIGNAL_STRENGTH_STATUS  3 // Signal strength: integer value from 0 to 5

	typedef union {

		INT32  integer;
		BOOL   boolean;
		WCHAR  *quoted_string;
		UINT64 unk;

	} STATUS_VALUE_T;

	// Set information to desktop
	UINT32 UIS_SetStatus(UINT8 status_id, STATUS_VALUE_T value);

	// Get information from desktop
	UINT32 UIS_GetCurrentStatusValue(UINT8 status_id, STATUS_VALUE_T *value);

	enum {

		WALLPAPER_LAYOUT_CURRENT = 0,
		WALLPAPER_LAYOUT_CENTERED,
		WALLPAPER_LAYOUT_TILED,
		WALLPAPER_LAYOUT_FIT_TO_SCREEN

	};
	typedef UINT8 WALLPAPER_LAYOUT_T;

	typedef struct {

		WCHAR              *url;
		WALLPAPER_LAYOUT_T layout;

	} SETWALLPAPER_SETTINGS_T;

	// Set desktop wallpaper
	UINT32 UIS_SetWallpaper(SETWALLPAPER_SETTINGS_T *);

	// Stop statusbar update
	extern char theStatusManager;

	void setCanvasControl__13StatusManagerFScPUs(void *, BOOL, void *);
	
	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Desktop elements control ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	// Clipboard (copy/paste in editor)
	#define CLIPBOARD_LEN 5120

	#if (defined(EP2) || defined(PATCH))
		extern WCHAR *clipboard_data_buf;
		#define clipboard (clipboard_data_buf)
	#else
		extern UINT32 *clipboard_data_buf;
		#define clipboard ((WCHAR *)*clipboard_data_buf)
	#endif

	#define ustr2cb(w) u_strcpy(clipboard, w)
	#define cb2ustr(w) u_strcpy(w, clipboard)

#ifdef __cplusplus
}
#endif

#endif // UIS_H

/* EOF */