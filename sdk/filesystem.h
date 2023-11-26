/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * File system driver API
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <typedefs.h>

#define FS_MAX_URI_NAME_LENGTH                   264 // file://b/a.txt, please, use FILEURI_MAX_LEN + 1
#define FS_MAX_PATH_NAME_LENGTH                  258 // file://b/a.txt, analoque constant
#define FS_MAX_FILE_NAME_LENGTH                  255 // file://a.txt, analogue constant

#define FILENAME_MAX_LEN FS_MAX_FILE_NAME_LENGTH
#define FILEURI_MAX_LEN FS_MAX_URI_NAME_LENGTH
#define FILEPATH_MAX_LEN FS_MAX_PATH_NAME_LENGTH

#define FS_HANDLE_INVALID                        0xFFFF
#define FILE_HANDLE_INVALID FS_HANDLE_INVALID
#define FILE_INVALID FS_HANDLE_INVALID

typedef UINT16 FS_HANDLE_T;
typedef FS_HANDLE_T FILE_HANDLE_T;

#ifndef WIN32
	typedef FS_HANDLE_T FILE;
#endif

typedef UINT64 FS_MID_T;        // Phisical ID of file

typedef UINT32 FS_COUNT_T;      //Count for writing, reading, inserting, and removing file data
typedef UINT8 FS_PERCENT_T;     //Percent complete of an operation (0 - 100)
typedef UINT16 FS_SEARCH_NUM_T; //Number of files matching search criteria
typedef INT32 FS_SEEK_OFFSET_T; //Seek offset value
typedef UINT32 FS_SIZE_T;
typedef UINT8 FS_RESULT_T;      // 0 - OK, 1 - FAIL

typedef struct {

	UINT32        offset;
	UINT32        size;
	FILE_HANDLE_T file_handle;

} FILE_HANDLE_REFERENCE_T;

/* Not known params set as 0 */

/* For mode in DL_FsOpenFile,
 * look standart function in C library stdio.h
 */
enum {

	FILE_READ_MODE = 0,         // Open for reading
	FILE_WRITE_MODE,            // Open for writing
	FILE_WRITE_EXIST_MODE,      // Write file, if this file not exist
	FILE_APPEND_MODE,           // Write to end of file
	FILE_READ_PLUS_MODE,        // Open for reading and writing
	FILE_WRITE_PLUS_MODE,       // Create for reading and writing
	FILE_WRITE_EXIST_PLUS_MODE, // Create for reading and writing, if this file not exist
	FILE_APPEND_PLUS_MODE       // Open or create file for reading or writing to end of file

};

// For whence in DL_FsSeekFile
enum {

	SEEK_WHENCE_SET = 0,
	SEEK_WHENCE_CUR,
	SEEK_WHENCE_END

};

#define FS_ATTR_DEFAULT   0x0000
#define FS_ATTR_READONLY  0x0001
#define FS_ATTR_HIDDEN    0x0002
#define FS_ATTR_SYSTEM    0x0004
#define FS_ATTR_VOLUME    0x0008
#define FS_ATTR_DIRECTORY 0x0010
#define FS_ATTR_ARCHIVE   0x0020

// Search flags
#define FS_SEARCH_EXCLUDE            0x80
#define FS_SEARCH_COMBINED           0x40 // Search in combined places (maybe)
#define FS_SEARCH_SORT_CHRONOLOGICAL 0x20 // Sort by time of file creating or writing (maybe)
#define FS_SEARCH_DIR_LISTING        0x10 // Return directories list (maybe)
#define FS_SEARCH_PATH_START         0x08 // Names of files in result have content full path
#define FS_SEARCH_SORT_ALPHANUMERIC  0x04 // Sort by names of file, by alphanumeric
#define FS_SEARCH_OWNER_MATCH        0x02 // Check file owner (maybe)
#define FS_SEARCH_RECURSIVE          0x01 // Recursive search, can search in subfolders

// For utilities
#define FS_SEARCH_START_PATH                 0x08
#define FS_SEARCH_FOLDERS                    0x10
#define FS_SEARCH_SORT_BY_NAME               0x04
#define FS_SEARCH_RECURSIVE_AND_SORT_BY_NAME 0x0D
#define FS_SEARCH_RECURSIVE_AND_SORT_BY_TIME 0x29

// Special characters for search
#define FS_VOLUME_NULL      0x0000
#define FS_VOLUME_SEPARATOR 0xFFFE

#define FS_MATCH_NULL                          0x0000
#define FS_MATCH_SEPARATOR                     0xFFFE
#define FS_MATCH_PATH_SEPARATOR                0xFFFD
#define FS_MATCH_PATH_NONREC_SEPARATOR         0xFFFC
#define FS_MATCH_PATH_EXCLUDE_SEPARATOR        0xFFFB
#define FS_MATCH_PATH_NONREC_EXCLUDE_SEPARATOR 0xFFFA

typedef struct {

	#if defined(FTR_L7E) || defined(FTR_L9)
		UINT32 flags;
	#else
		UINT8  flags;
	#endif

	UINT16 attrib; // Result contains file, if his attribute &mask == attrib
	UINT16 mask;

} FS_SEARCH_PARAMS_T;

typedef struct {

	WCHAR  name[FILEPATH_MAX_LEN + 1]; // Full name of file with path
	UINT16 attrib;
	UINT16 owner;

} FS_SEARCH_RESULT_T;

typedef UINT8 FS_SEARCH_HANDLE_T;

// VOLUME_DESCR_T.device
typedef enum {

	FS_DEVICE_NONE = 0x0000,
	FS_DEVICE_FLASH = 0x0001,
	FS_DEVICE_MMC_INTERNAL = 0x0002,
	FS_DEVICE_MMC = 0x0004,
	FS_DEVICE_MMC_EXTERNAL = FS_DEVICE_MMC,
	FS_DEVICE_SDC = 0x0008,
	FS_DEVICE_NETWORK = 0x0010,
	FS_DEVICE_FLASH_NONUSER = 0x0020,
	FS_DEVICE_TFR = 0x0040,
	FS_DEVICE_MMC_RAMDISK = 0x0100,
	FS_DEVICE_ALL = 0x7FFF,
	FS_DEVICE_UNSUPPORTED = 0x8000,
	FS_DEVICE_INVALID = FS_DEVICE_UNSUPPORTED

} FS_DEVICE_T;

// Volime properties
typedef struct {

	WCHAR  volume[3];    // +0
	WCHAR  vol_name[12]; // +6
	UINT32 free;         // +32 in bytes
	UINT32 capacity;     // +36 in bytes
	UINT16 vol_attr;     // +40
	UINT8  device_id;    // +42 0x01
	UINT16 device;       // +44
	UINT32 serial_num;   // +48

} VOLUME_DESCR_T;

enum FS_REMOVE_T_ENUM_ {

	FS_REMOVE_DEFAULT = 0,
	FS_REMOVE_FORCE = 1

};
typedef UINT8 FS_REMOVE_T;

#ifdef __cplusplus
extern "C" {
#endif

	// Not known params set as 0
	FILE_HANDLE_T DL_FsOpenFile(
		const WCHAR *uri,
		UINT8       mode,
		UINT16      owner
	);

	UINT8 DL_FsCloseFile(FILE_HANDLE_T handle);

	UINT8 DL_FsReadFile(
		void          *buffer,
		UINT32        size,
		UINT32        count,
		FILE_HANDLE_T handle,
		UINT32        *read
	);

	UINT8 DL_FsWriteFile(
		void          *buffer,
		UINT32        size,
		UINT32        count,
		FILE_HANDLE_T handle,
		UINT32        *written
	);

	UINT8 DL_FsFSeekFile(
		FILE_HANDLE_T handle,
		INT32         off,
		UINT8         whence
	);

	UINT32 DL_FsGetFileSize(FILE_HANDLE_T handle);

	UINT32 DL_FsSGetFileSize(const WCHAR *uri, UINT16 owner);

	WCHAR *DL_FsSGetFileName(const WCHAR *file_uri, WCHAR name[]);

	WCHAR *DL_FsSGetPath(const WCHAR *file_uri, WCHAR path[]);

	WCHAR *DL_FsSGetVolume(const WCHAR *file_uri, WCHAR vol_uri[]);

	BOOL DL_FsDirExist(const WCHAR *uri);

	BOOL DL_FsFFileExist(const WCHAR *uri);

	UINT32 DL_FsFGetPosition(FILE_HANDLE_T handle);

	UINT8 DL_FsRenameFile(FILE_HANDLE_T handle, const WCHAR *new_name);

	UINT8 DL_FsSRenameFile(
		const WCHAR *old_uri,
		const WCHAR *new_name,
		UINT16      owner
	);

	UINT8 DL_FsDeleteFile(const WCHAR *uri, UINT16 param1);

	UINT8 DL_FsFMoveFile(
		const WCHAR *src_uri,
		const WCHAR *dst_uri,
		UINT16      owner
	);

	UINT8 DL_FsMkDir(const WCHAR *uri, UINT16 owner);

	UINT8 DL_FsRmDir(
		const WCHAR *uri,
		UINT16      owner,
		FS_REMOVE_T rmtype
	);

	UINT8 DL_FsFSetAttr(FILE_HANDLE_T handle, UINT16 attrib);

	UINT8 DL_FsSSetAttr(
		const WCHAR *uri,
		UINT16      owner,
		UINT16      attrib
	);

	UINT16 DL_FsGetAttr(FILE_HANDLE_T handle);

	UINT16 DL_FsSGetAttr(const WCHAR *uri, UINT16 owner);

	void DL_FsFlush(void);

	// Get phisical ID of file
	UINT32 DL_FsGetIDFromURI(const WCHAR *uri, FS_MID_T *id);

	// Get file path by ID
	WCHAR *DL_FsGetURIFromID(const FS_MID_T *id, WCHAR *uri);

	// Get volumes enumeration
	WCHAR *DL_FsVolumeEnum(WCHAR *result); // result = L{'/', 'a', 0xfffe, '/', ...}

	// Get volume description
	VOLUME_DESCR_T *DL_FsGetVolumeDescr(WCHAR *volume, VOLUME_DESCR_T *vd);

	BOOL DL_FsIsCardInserted(const WCHAR *vol_uri);

	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Files search ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	#define DIRECTORY_FILTER_ATTRIBUTE 0x12
	#define EV_FILE_SEARCH_COMPLETED   0x8213D

	typedef W_CHAR *(*FS_URI_FNCT_PTR)(UINT16, W_CHAR *);

	typedef struct {

		FS_SEARCH_HANDLE_T search_handle;
		FS_SEARCH_NUM_T    search_total;
		FS_SEARCH_RESULT_T search_result;

	} FS_SEARCH_COMPLETED_INDEX_T;

	typedef struct {

		FS_SEARCH_PARAMS_T search;
		FS_SEARCH_NUM_T    num;
		WCHAR              search_string[FS_MAX_URI_NAME_LENGTH + 1];
		UINT16             file_id[1500 + 50 + 43];
		UINT16             vol_attr;
		FS_SEARCH_HANDLE_T shandle;
		UINT16             owner_id;
		BOOL               abort_pending;

	} FS_SEARCH_INFO_T;

	/* Syncronical search of file function
	 * search_string formed from URI folder, where search is running, then separator - 0xFFFE, next patterns,
	 * for example: "file://b/Elf/\xFFFE*.elf"
	 */
	UINT16 DL_FsSSearch(
		FS_SEARCH_PARAMS_T params,
		const WCHAR        *search_string,
		FS_SEARCH_HANDLE_T *handle,        // Out
		UINT16             *res_count,     // Out
		UINT16             owner
	);

	// Alternative function syncronical search of files
	UINT16 DL_FsSearch(
		const FS_SEARCH_PARAMS_T search,
		const WCHAR              *match_names,
		FS_SEARCH_INFO_T         **search_info,
		FS_URI_FNCT_PTR          *fnct_ptr,
		const UINT16             owner_id
	);

	// Asyncronical function search of files, search result return by event EV_FILE_SEARCH_COMPLETED
	UINT16 DL_FsISearch(
		const IFACE_DATA_T       *iface,
		const FS_SEARCH_PARAMS_T params,
		const W_CHAR             *match_names,
		const UINT16             owner_id
	);

	// Get part of search files result function
	UINT16 DL_FsSearchResults(
		FS_SEARCH_HANDLE_T handle,
		UINT16             start_index, // 0 based
		UINT16             *count,      // In and out
		FS_SEARCH_RESULT_T *results
	);

	UINT16 DL_FsSearchClose(FS_SEARCH_HANDLE_T handle);

	UINT32 URINameValid(WCHAR *uri);

#ifdef __cplusplus
}
#endif

#endif // FILESYSTEM_H

/* EOF */