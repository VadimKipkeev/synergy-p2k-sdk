/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * Phonebook SDK
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef __SDK_PHONEBOOK_H__
#define __SDK_PHONEBOOK_H__

#include <typedefs.h>

typedef struct {

	UINT8 result;      // Operation result, 0 if successful
	UINT8 list_type;   // List type
	UINT8 sort_type;   // Sorting type
	UINT8 count_items; // Records count in buf
	UINT8 buf[0x4000]; // Record data

} PHONEBOOK_READ_RECORD_T;

#define PB_RECORD_NAME_LEN   24
#define PB_RECORD_NUMBER_LEN 50

// Phonebook record
typedef struct {

	UINT16 index;                            // Record index
	WCHAR  name[PB_RECORD_NAME_LEN + 1];     // Name
	WCHAR  number[PB_RECORD_NUMBER_LEN + 1]; // Number
	UINT8  pad[383];

} PHONEBOOK_RECORD_T; // == 0x21C

// Category record
typedef struct {

	WCHAR name[PB_RECORD_NAME_LEN + 1];
	UINT8 id;
	UINT8 index;
	UINT8 pad[6];

} PHONEBOOK_CATEGORY_RECORD_T; // == 0x3A

typedef enum {

	PHONEBOOK_DEVICE_PHONE,
	PHONEBOOK_DEVICE_SIM,
	PHONEBOOK_DEVICE_ALL

} PHONEBOOK_DEVICE_T;

#ifdef __cplusplus
extern "C" {
#endif

	// Read record from phonebook, sending EV_PHONEBOOK_READ_RECORD event
	UINT32 DL_DbPhoneBookGetRecordByIndex(
		IFACE_DATA_T *data,
		UINT8        list_type,   // 0 - phonebook
		UINT16       index,       // Record index
		UINT8        count_items,
		UINT8        sort_type
	);

	// Search record by name
	UINT32 DL_DbPhoneBookFindRecordByName(
		UINT8  list_type,
		WCHAR  *name,
		UINT8  sort_type,
		UINT16 *index
	);

	// Search record by tel_number, sending EV_PHONEBOOK_READ_RECORD event
	UINT32 DL_DbPhoneBookFindRecordByTelno(
		IFACE_DATA_T *data,
		UINT8        list_type,
		WCHAR        *tel_number,
		UINT8        sort_type
	);

	// Get possible phonebook records count
	UINT32 DL_DbPhoneBookGetNumberRecords(
		UINT8              list_type,
		PHONEBOOK_DEVICE_T device,
		UINT16             *count_numbers
	);

	// Get used phonebook records count
	UINT32 DL_DbPhoneBookGetUsedRecords(
		UINT8              list_type,
		PHONEBOOK_DEVICE_T device,
		UINT16             *count_numbers,
		UINT8              sort_type
	);

	// Get avaliable records count
	UINT32 DL_DbPhoneBookGetAvailableRecords(
		UINT8              list_type,
		PHONEBOOK_DEVICE_T device,
		UINT16             *count_numbers
	);

	// Delete record
	UINT32 DL_DbPhoneBookDeleteRecordByIndex(
		IFACE_DATA_T *iface_data,
		UINT8        list_type,
		UINT16       index,
		UINT8        sort_type
	);

	// Delete all records
	UINT32 DL_DbPhoneBookDeleteAllRecords(IFACE_DATA_T *iface_data, UINT8 list_type);

	// Update record
	UINT32 DL_DbPhoneBookUpdateRecord(
		IFACE_DATA_T *iface_data,
		UINT8        list_type,
		void         *record,
		UINT8        sort_type
	);

	// Store new record
	UINT32 DL_DbPhoneBookStoreRecord(
		IFACE_DATA_T *iface_data,
		UINT8        list_type,
		void         *record,
		UINT8        sort_type
	);

	// Return categories count
	UINT32 DL_DbPhoneBookGetNumberofCategories(
		UINT8              list_type,
		PHONEBOOK_DEVICE_T device,
		UINT16             *count_categories
	);

	// Get category, sending EV_PHONEBOOK_READ_RECORD event
	UINT32 DL_DbPhoneBookGetCategoryRecordByIndex(
		IFACE_DATA_T       *data,
		UINT8              list_type,
		PHONEBOOK_DEVICE_T device,
		UINT8              category_index
	);

	// Store selected category
	UINT32 DL_DbPhoneBookStoreCategoryRecord(
		IFACE_DATA_T       *data,
		UINT8              list_type,
		PHONEBOOK_DEVICE_T device,
		void               *category_record, // PHONEBOOK_CATEGORY_RECORD_T
		UINT8              *unk              // Maybe NULL
	);

	// Delete category
	UINT32 DL_DbPhoneBookDeleteCategoryRecord(
		IFACE_DATA_T       *data,
		UINT8              list_type,
		PHONEBOOK_DEVICE_T device,
		UINT8              category_id
	);

#ifdef __cplusplus
}
#endif

#endif // __SDK_PHONEBOOK_H__

/* EOF */