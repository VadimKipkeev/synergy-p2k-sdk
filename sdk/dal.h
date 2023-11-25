/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * Display Abstract Layer API
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef __DAL_H__
#define __DAL_H__

#include <typedefs.h>
#include "ati.h"
#include "canvas.h"

#define DISPLAY_WIDTH  176
#define DISPLAY_HEIGHT 220

// Macros fo convert RGB 8 bits color components to 565 format
#define ATI_565RGB(r, g, b) (UINT32)((r & 0xf8) << 8 | (g & 0xFC) << 3 | (b & 0xf8) >> 3)

enum DISPLAY_TYPE_ENUM {

	DISPLAY_MAIN = 0,
	DISPLAY_CLI,
	DISPLAY_EXTERNAL,
	DISPLAY_MAIN_AND_CLI,
	DISPLAY_NONE

};
typedef UINT8 DISPLAY_TYPE_T;

enum {

	UIS_ONLY,              // Normal mode
	UIS_AND_MME,           // Free out of screen surface
	UIS_AND_KJAVA,
	TCMD_ONLY,             // Free maximum memory, display surface too
	MME_CAPTURE_MODE_ONLY,
	PARTIAL_DISPLAY_MODE,
	YUV_MODE_ONLY,
	YUV_AND_UIS_MODE,
	ATI_MEM_MODE_NONE

};
typedef UINT8 ATIDEVMEMCONFIG_T;

#ifdef __cplusplus
extern "C" {
#endif

	AHISURFACE_T DAL_ATISurfAlloc(
		AHIDEVCONTEXT_T devCtx,
		UINT32          size,
		AHIPIXFMT_T     pixFmt
	);

	BOOL DAL_ATISurfFree(AHIDEVCONTEXT_T devCtx, AHISURFACE_T surf);

	// Return old system content, not recomended to change
	AHIDEVCONTEXT_T DAL_GetDeviceContext(DISPLAY_TYPE_T display);

	// Return current system drawing surface
	AHISURFACE_T DAL_GetDrawingSurface(DISPLAY_TYPE_T display);

	// Draw bitmap 444 on screen
	BOOL DAL_WriteDisplayRegion(
		GRAPHIC_REGION_T *upd_region,
		UINT16           *src_buf,      // RGB444
		DISPLAY_TYPE_T   display,       // Display type
		BOOL             check_mask
	);

	// Get pixel address
	UINT16 *DAL_GetDisplayPixelAddress(
		UINT8           buf_type,         // buf_type = NULL
		GRAPHIC_POINT_T pixel_coordinate,
		DISPLAY_TYPE_T  display
	);

	// Change video-memory configuration on selected
	void DAL_ATIDevMemConfiguration(ATIDEVMEMCONFIG_T devMemConfig);

	// Return current video-memory configuration number
	ATIDEVMEMCONFIG_T DAL_GetActiveATIDevMemConfiguration(void);

	// Free UIS screen cache
	void DAL_FreeCache(void);

	// Disable display
	void DAL_DisableDisplay(UINT32 p1); // p1 = 0

	// Enable display
	void DAL_EnableDisplay(UINT32 p1);  // p1 = 0

	/* Return UIS screen cache surface
	 * always better requesting size from DAL_GetCacheSize function
	 */
	AHISURFACE_T DAL_GetCachedSurface(AHIPOINT_T temp_surf_size);

	// Get UIS screen cache size
	AHIPOINT_T DAL_GetCacheSize(void);

	/* EXL:
	 * Pointer to structure or class DAL in memory
	 */
	extern UINT8 *Class_dal;

	/* EXL:
	 * Rasterizator draw current wallpaper on canvas
	 * use for V600
	 */
	extern UINT32 theWallpaper;

	BOOL flushWallpaperOnScreen(
		UINT32           *Wallpaper_class_address,
		GRAPHIC_REGION_T wallpaper_region,
		DISPLAY_TYPE_T   display_type
	);

#ifdef __cplusplus
}
#endif

#endif //__DAL_H__

/* EOF */