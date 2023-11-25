/* --------------------------------------------------------------------------------------------------------------------------------
 * ElfPack version 2.0 API for Motorola P2k OS
 * --------------------------------------------------------------------------------------------------------------------------------
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * Loader SDK
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef LOADER_H
#define LOADER_H

#include <typedefs.h>
#include <stdargs.h>
#include <events.h>
#include <apps.h>
#include <ATI.h>

typedef struct {

	INT16 x1;
	INT16 y1;
	INT16 x2;
	INT16 y2;

} RECT_T;

// Elfloader functions
typedef struct tagldrElf {

	char             *name;  // Name of the ELF
	UINT32           evbase; // Event code base (was in Register before)
	APPLICATION_T    *app;   // APPLICATION_T pointer
	void             *addr;  // Address of ELF image in the memory
	UINT32           size;   // Size of the ELF image
	UINT32           link;   // Linked libraries
	WCHAR            *dir;   // Working dir
	struct tagldrElf *next;  // List pointer

} ldrElf;

#define LIBPATHCNT 3

typedef struct {

	BOOL   EnableConsole;
	BOOL   AutoShowConsole;
	BOOL   DebugMode;
	BOOL   SkipAutorun;
	BOOL   ShowLogo;
	WCHAR  *AutorunPath;
	WCHAR  *FastRunElf;
	UINT32 FastRunEvent;
	WCHAR  *DefLibraryPath;
	WCHAR  *LibsPaths[LIBPATHCNT];

} LDR_CONFIG_T;

#define DEFLIB_VERSION_LEN  7
#define DEFLIB_FIRMWARE_LEN 23

typedef struct {

	UINT32 magic;
	char   version[DEFLIB_VERSION_LEN + 1];
	char   firmware[DEFLIB_FIRMWARE_LEN + 1];
	UINT32 symCnt;
	UINT32 strTabSz;
	UINT32 strTabOff;
	UINT32 constCnt;
	UINT32 constOff;

} LDR_DEFLIB_HEADER_T; // 56 = 0x38

#ifdef __cplusplus
extern "C" {
#endif

	ldrElf *ldrGetElfsList(UINT32 *count);

	ldrElf *ldrFindElf(const char *name);

	BOOL ldrIsLoaded(const char *app_name);

	UINT32 ldrRequestEventBase(void);

	UINT32 ldrSendEvent(UINT32 evcode);

	UINT32 ldrSendEventToApp(
		AFW_ID_T        afwid,
		UINT32          evcode,
		void            *attachment,
		UINT32          att_size,
		FREE_BUF_FLAG_T fbf
	);

	UINT32 ldrSendEventToAppEmpty(AFW_ID_T afwid, UINT32 evcode);

	UINT32 ldrUnloadElf(void);

	UINT32 ldrLoadElf(WCHAR *uri, WCHAR *params);

	UINT32 ldrUnloadElfByAddr(void *addr);

	// Constants
	UINT32 ldrGetConstVal(UINT16 constID);

	UINT32 ldrInitEventHandlersTbl(EVENT_HANDLER_ENTRY_T *tbl, UINT32 base);

	UINT32 ldrFindEventHandlerTbl(const EVENT_HANDLER_ENTRY_T *tbl, EVENT_HANDLER_T *hfn);

	// Access to ATI driver
	const AHIDRVINFO_T *ldrGetAhiDrvInfo(void);

	AHIDEVICE_T ldrGetAhiDevice(void);

	// ElfPack version 2.0 config
	void ldrSetDefaultConfig(void);

	const LDR_CONFIG_T *ldrGetConfig(void);

	UINT32 ldrLoadConfig(void);

	UINT32 ldrSetConfig(const LDR_CONFIG_T *cfg);

	UINT32 ldrCopyConfig(LDR_CONFIG_T *cfg);

	UINT32 ldrFreeConfig(LDR_CONFIG_T *cfg);

	// Reload library
	UINT32 ldrLoadDefLibrary(void);

	void UtilLogStringData(const char *format, ...);

	// Console
	void cprint(const char *);

	void cprintf(const char *format, ...);

	void ldrToggleConsole(void);

	BOOL ldrEnableConsole(BOOL new_state);

	// Display callbacks
	typedef void (*dispCbk)(RECT_T *);

	BOOL ldrDisplayCbkReg(
		dispCbk cbk,
		RECT_T *target,
		BOOL postflush
	);

	BOOL ldrDisplayCbkUnReg(dispCbk cbk);

	const char *ldrGetPhoneName(void);

	const char *ldrGetPlatformName(void);

	const char *ldrGetFirmwareVersion(void);

	// Dynamic libraries
	typedef UINT32 DLHANDLE;

	enum DL_MODE_ENUM {

		RTLD_NOW = 0,
		RTLD_LAZY = 1,
		RTLD_LOCAL = 0,
		RTLD_GLOBAL = 2

	};

	DLHANDLE dlopen(const WCHAR *file, int mode);

	UINT32 dlclose(DLHANDLE handle);

	void *dlsym(DLHANDLE handle, const char *name);

	UINT32 dlerror(void);

#ifdef __cplusplus
}
#endif

#endif // LOADER_H

/* EOF */