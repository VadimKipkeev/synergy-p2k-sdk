/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * Bluetooth API
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <typedefs.h>
#include <time_date.h>
#include <filesystem.h>

typedef struct {

	WCHAR                   name[FILEURI_MAX_LEN + 1]; // Real name of file
	WCHAR                   temp_name[80];             // Path to temporal file
	UINT8                   unk1;
	char                    *type;                     // Content type
	BOOL                    unk2;
	UINT32                  size;                      // Content size
	CLK_DATE_T              date_stamp;                // Date
	CLK_TIME_T              time_stamp;                // Time
	UINT8                   unk3;
	UINT32                  unk4[2];
	UINT32                  offset;                    // Content starting offset in temporal file
	FILE_HANDLE_REFERENCE_T file_reference;            // For EMS
	BOOL                    unk5;
	UINT32                  unk6[2];
	void                    *p_buffer;                 // Pointer to content
	INT32                   unk7;
	UINT8                   unk8[2];

} PREVIEW_RECORD_T;

#define OBEX_TRANSPORT_BT 0x01

#if defined(FTR_L7E) || defined(FTR_L9)
	#define OBEX_OBJECT_FILE 0x06
#else
	#define OBEX_OBJECT_FILE 0x05
#endif

#define OBEX_ACTION_COPY     0x00
#define OBEX_ACTION_MOVE     0x01
#define MIME_TYPE_STRING_LEN 50

typedef struct {

	UINT8  b_vobjectid;                             // OBEX_OBJECT_FILE
	UINT8  pad1[3];
	WCHAR  aw_filename[FS_MAX_URI_NAME_LENGTH + 1];
	char   ab_mimetype[MIME_TYPE_STRING_LEN + 1];
	UINT8  obex_action;                             // OBEX_ACTION_*
	UINT8  pad2[3];
	UINT16 selected_transport_type;                 // OBEX_TRANSPORT_BT
	UINT8  pad3[2];
	UINT32 transport_list_size;                     // == 0

} SEND_VIA_BT_ATTACH_LTE;

typedef struct {

	UINT8  b_vobjectid;                             // OBEX_OBJECT_FILE
	UINT8  pad1[3];
	WCHAR  aw_filename[FS_MAX_URI_NAME_LENGTH + 1];
	char   ab_mimetype[MIME_TYPE_STRING_LEN + 1];
	UINT8  obex_action;                             // OBEX_ACTION_*
	UINT8  pad2[3];
	UINT32 *p_file_ids;
	UINT32 num_file_ids;
	UINT8  pad3[2440 - 592];
	UINT16 selected_transport_type;                 // OBEX_TRANSPORT_BT
	UINT8  pad4[2];
	UINT32 transport_list_size;                     // == 0

} SEND_VIA_BT_ATTACH_LTE2;

typedef struct {

	UINT16 selected_transport_type;                 // OBEX_TRANSPORT_BT
	UINT8  pad4[2];
	UINT32 transport_list_size;                     // == 0
	UINT8  b_vobjectid;                             // OBEX_OBJECT_FILE
	UINT8  pad1[3];
	WCHAR  aw_filename[FS_MAX_URI_NAME_LENGTH + 1]; // 265 * 2 = 530
	char   ab_mimetype[MIME_TYPE_STRING_LEN + 1];   // == 51
	UINT8  obex_action;                             // OBEX_ACTION_*
	UINT8  pad2[3];
	UINT32 *p_file_ids;
	UINT32 num_file_ids;
	UINT8  pad3[2440 - 592];

} SEND_VIA_BT_ATTACH_NEW;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif // BLUETOOTH_H

/* EOF */