/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * User Interface System - Canvas API
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef CANVAS_H
#define CANVAS_H

#include <typedefs.h>
#include <utilities.h>
#include <mme.h>
#include <resources.h>
#include <uis.h>

#ifdef __cplusplus
extern "C" {
#endif

	// Anchor point for text and images - vertical
	#define ANCHOR_BASELINE 64 // Only text
	#define ANCHOR_BOTTOM   32
	#define ANCHOR_TOP      16
	#define ANCHOR_VCENTER  2  // Only image

	// Anchor point for text and images - horizontal
	#define ANCHOR_RIGHT    8
	#define ANCHOR_LEFT     4
	#define ANCHOR_HCENTER  1

	/* Use "OR" symbol, for example: ANCHOR_LEFT | ANCHOR_TOP */

	// Font style
	#if (defined(FTR_L7E) || defined(FTR_L9))

		// For vector fonts
		#define FONT_STYLE_PLAIN         0
		#define FONT_STYLE_ITALIC        0x02
		#define FONT_STYLE_BOLD          0x01
		#define FONT_STYLE_BOLD_ITALIC   (FONT_STYLE_ITALIC | FONT_STYLE_BOLD)
		#define FONT_STYLE_UNDERLINE     0x04
		#define FONT_STYLE_STRIKETHROUGH 0x08
		#define FONT_STYLE_REVERSEVIDEO  0x10
		#define FONT_STYLE_NORMALVIDEO   0x20
	#else

		// For raster fonts
		#define FONT_STYLE_PLAIN         0xFF
		#define FONT_STYLE_ITALIC        0x01
		#define FONT_STYLE_BOLD          0x02
		#define FONT_STYLE_BOLD_ITALIC   (FONT_STYLE_ITALIC | FONT_STYLE_BOLD)
	#endif

	typedef struct {

		UINT8  font_id;
		UINT8  font_style;
		UINT16 point_size;
		UINT16 frac_point_size;

	} FONT_ATTRIB_T; // For vector fonts

	typedef struct {

		UINT8  *buf; // Buffer for drawing, must be NULL
		UINT16 w;    // Width
		UINT16 h;    // Height

	} DRAWING_BUFFER_T;

	typedef struct {

		UINT8 red;
		UINT8 green;
		UINT8 blue;
		UINT8 transparent; // Transparent

	} COLOR_T;

	#define COLOR_RED         (COLOR_T)(0xFF000000)
	#define COLOR_GREEN       (COLOR_T)(0x00FF0000)
	#define COLOR_BLUE        (COLOR_T)(0x0000FF00)
	#define COLOR_BLACK       (COLOR_T)(0x00000000)
	#define COLOR_TRANSPARENT (COLOR_T)(0x000000FF)

	#ifdef WIN32
		#ifdef RGB
			#undef RGB
		#endif
	#endif

	#define RGB(r, g, b)     (COLOR_T)((BYTE)(r) << 24 | (BYTE)(g) << 16 | (BYTE)(b) << 8)
	#define RGBT(r, g, b, t) (COLOR_T)((BYTE)(r) << 24 | (BYTE)(g) << 16 | (BYTE)(b) << 8 | (BYTE)(t))
	#define RGB_getr(c)      (BYTE)((UINT32)(c) >> 24 & 0xFF)                                          // RED
	#define RGB_getg(c)      (BYTE)((UINT32)(c) >> 16 & 0xFF)                                          // GREEN
	#define RGB_getb(c)      (BYTE)((UINT32)(c) >> 8 & 0xFF)                                           // BLUE
	#define RGB_gett(c)      (BYTE)((UINT32)(c)&0xFF)                                                  // TRANSPARENT

	typedef struct {

		INT16 x; // Horizontal coordinate x
		INT16 y; // Vertical coordinate y

	} GRAPHIC_POINT_T;

	typedef struct {
	
		GRAPHIC_POINT_T ulc; // Top left angle
		GRAPHIC_POINT_T lrc; // Bottom right angle

	} GRAPHIC_REGION_T;

	#ifdef EMUELF
		#define AlphaBlend EMUAlphaBlend
	#endif

	// drawOp
	enum {

		AlphaBlend, // Transparent white color
		Copy,
		NotUsed1,
		Invert,
		NotCopy,
		Resize,
		Xor,
		NotUsed2,
		Move

	};

	// Picture type
	enum {

		DRM_PICTURE_TYPE,
		IMAGE_PATH_TYPE,
		STORED_IN_MEMORY_TYPE,
		FILE_HANDLE_TYPE,
		IMAGE_PATH_WITH_OFFSET

	};

	typedef WCHAR *IMAGE_PATH_T; // Path to image

	typedef struct {

		const void *resourcePicturePointerValue; // Pointer memory place
		UINT32     imageSize;                    // Image size

	} PICTURE_POINTER_T;

	typedef struct {

		FILE_HANDLE_T fileHandle;
		UINT32        imageOffset;
		UINT32        imageSize;

	} UIS_FILE_HANDLE_T;

	typedef struct {

		IMAGE_PATH_T PathValue;
		MIME_TYPE_T  mimeFormat;  // Image type
		UINT32       imageOffset;
		UINT32       imageSize;

	} FILE_PATH_WITH_OFFSET_T;

	typedef union {

		RESOURCE_ID             DrmValue;
		IMAGE_PATH_T            PathValue;
		PICTURE_POINTER_T       PointerValue;
		UIS_FILE_HANDLE_T       FileHandleValue;
		FILE_PATH_WITH_OFFSET_T PathWithOffsetValue;

	} PICTURE_TYPE_UNION_T;

	typedef UINT8 CANVAS_IMAGE_HANDLE_T;

	typedef struct {

		UINT16 height;
		UINT16 width;

	} GRAPHIC_METRIC_T;

	typedef struct {

		GRAPHIC_REGION_T offset_region;
		UINT8            *background_buffer;
		UINT16           width;
		UINT16           height;

	} IMAGE_BACKGROUND_BUFFER;

	typedef struct {

		COLOR_T begin_color;
		COLOR_T end_color;

	} GRADIENT_T;

	typedef enum {

		IA_NO_ATTRIBUTES = 0,                     // Without attributes
		IA_FRAME_COMPLETED,                       // Call event by frame is completed
		IA_CYCLE_COMPLETED,                       // Call event by cycle is completed
		IA_ANIMATION_COMPLETED,                   // Call event by animation is completed 
		IA_STILL_IMAGE,                           // First frame of animation
		IA_BACKGROUND_TRANSPARENT_IMAGE,          // IMAGE_BACKGROUND_BUFFER
		IA_BACKGROUND_TRANSPARENT_COLOR,          // COLOR_T
		IA_BACKGROUND_TRANSPARENT_GRADIENT,       // GRADIENT_T

		IA_BACKGROUND_TRANSPARENT_TILED_IMAGE,
		IA_BACKGROUND_WALLPAPER_NEEDED,

		IA_START_ANIMATION = 10,                   // Animation will be starting from first frame
		IA_BACKGROUND_EXCLUDING_IMAGE,             // COLOR_T

		IA_NO_PAINT_WHITE = 13,                    // Not white color draw
		IA_NO_PAINT_WHITE_WITH_CROSS,
		IA_PAINT_WHITE_AND_PAINT_WHITE_WITH_CROSS,
		IA_NO_OF_CYCLES_OF_ANIMATION,              // UINT8 cycle animation number
		IA_DECODE_WALLPAPER_GRAYSCALE,
		IA_PRESERVE_BACKGROUND_GRAYSCALE,

		IA_OBEY_TRANSPARENCY = 23                  // With transparency

	} IMAGE_ATTRIBUTE_TYPE_T;

	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Create canvas dialog ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	// Create color canvas
	UIS_DIALOG_T UIS_CreateColorCanvas(
		SU_PORT_T        *port,
		DRAWING_BUFFER_T *drawing_buffer,
		BOOL             status_line_area // true - not show status bar, false - show status bar
	);

	/* Colors by default:
	 * BackgroundColor - white
	 * FillColor - white
	 * ForegroundColor - blue
	 */

	// Create color canvas with image
	UIS_DIALOG_T UIS_CreateColorCanvasWithWallpaper(
		SU_PORT_T        *port,
		DRAWING_BUFFER_T *drawing_buffer,
		BOOL             use_status_line_area,
		BOOL             wallpaper_flag
	);
	
	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Draw graphical primitives ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	// Draw pixel (maybe works)
	void UIS_CanvasDrawPixel(GRAPHIC_POINT_T point, UIS_DIALOG_T handle);

	// Draw line
	void UIS_CanvasDrawLine(
		GRAPHIC_POINT_T begin,
		GRAPHIC_POINT_T end,
		UIS_DIALOG_T    handle
	);

	// Draw fill color rectangle
	void UIS_CanvasFillRect(GRAPHIC_REGION_T region, UIS_DIALOG_T handle);

	// Draw rectangle
	void UIS_CanvasDrawRect(
		GRAPHIC_REGION_T region,
		BOOL             fill,    // Fill status
		UIS_DIALOG_T     handle
	);

	// Draw round rectangle
	void UIS_CanvasDrawRoundRect(
		GRAPHIC_REGION_T region,
		UINT16           arcW,   // Horizontal round diameter
		UINT16           arcH,   // Vertical round diameter
		BOOL             fill,
		UIS_DIALOG_T     handle
	);

	// Draw arc of circle
	void UIS_CanvasDrawArc(
		GRAPHIC_REGION_T region,
		UINT16           startAngle,  // Starting angle
		UINT16           arcAngle,    // Ending angle
		BOOL             fill,
		UIS_DIALOG_T     handle
	);

	// Draw polygon
	void UIS_CanvasDrawPoly(
		UINT16          number_of_vertices,
		GRAPHIC_POINT_T *array,
		BOOL            fill,
		UIS_DIALOG_T    handle
	);

	// Draw pixel
	void UIS_CanvasDrawPixel(GRAPHIC_POINT_T position, UIS_DIALOG_T handle);
	
	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Draw text ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	// Draw color text string
	void UIS_CanvasDrawColorText(
		WCHAR           *str,
		UINT16          offset,
		UINT16          str_len,      // String length
		GRAPHIC_POINT_T anchor_point, // Anchor point coordinates
		UINT16          anchor_value, // Anchor point value, for example: ANCHOR_LEFT | ANCHOR_TOP
		UIS_DIALOG_T    handle
	);

	UINT32 UIS_CanvasDrawText(
		UINT8            *draw_buf,
		WCHAR            *str,
		GRAPHIC_REGION_T region,
		UINT8            font_id,
		BOOL             unk1,
		COLOR_T          color,
		void             *unk2
	);

	#if (defined(FTR_L7E) || defined(FTR_L9))

		// Set font type for vector fonts
		UINT32 UIS_CanvasSetFontAttrib(FONT_ATTRIB_T fontattrib, UIS_DIALOG_T handle);
	#endif

	#if (defined(FTR_L7E) || defined(FTR_L9))

		// Get current font function, for vector fonts
		UINT32 UIS_CanvasGetCurrentFonts(FONT_ATTRIB_T *working_font, FONT_ATTRIB_T *softkey_font);
	#else

		// Get current font function, for raster fonts
		UINT32 UIS_CanvasGetCurrentFonts(UINT8 *working_font, UINT8 *softkey_font);
	#endif

	// Return font style
	UINT8 UIS_CanvasGetFontStyle(UIS_DIALOG_T handle);

	UINT8 UIS_CanvasGetFontId(UIS_DIALOG_T dialog);

	// Set font style
	UINT32 UIS_CanvasSetFontStyle(UINT8 font_style, UIS_DIALOG_T handle);

	// Set font for canvas, font_id can get from langpack (CG4), value 0x01 - standart font
	UINT32 UIS_CanvasSetFont(UINT8 font_id, UIS_DIALOG_T handle);

	#if (defined(FTR_L7E) || defined(FTR_L9))

		// Get font character size, for vector fonts
		UINT32 UIS_CanvasGetCharacterSize(
			WCHAR            *str,
			UINT8            position,
			GRAPHIC_METRIC_T *char_size,
			FONT_ATTRIB_T    font_id
		);
	#else

		// Get font character size, for raster fonts
		UINT32 UIS_CanvasGetCharacterSize(
			WCHAR            *str,
			UINT8            position,
			GRAPHIC_METRIC_T *char_size,
			UINT8            font_id
		);
	#endif

	#if (defined(FTR_L7E) || defined(FTR_L9))

		// Return string size, for vector fonts
		UINT32 UIS_CanvasGetStringSize(
			WCHAR            *str,
			GRAPHIC_METRIC_T *string_size, // String size
			FONT_ATTRIB_T    font_id
		);
	#else

		// Return string size, for raster fonts
		UINT32 UIS_CanvasGetStringSize(
			WCHAR            *str,
			GRAPHIC_METRIC_T *string_size, // String size
			UINT8            font_id
		);
	#endif

	// Get font size for vector and raster fonts
	#if (defined(FTR_L7E) || defined(FTR_L9))
		UINT32 UIS_CanvasGetFontSize(FONT_ATTRIB_T font_id, GRAPHIC_METRIC_T *font_size);
	#else
		UINT32 UIS_CanvasGetFontSize(UINT8 font_id, GRAPHIC_METRIC_T *font_size);
	#endif
	
	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Draw images ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	// Draw image
	UINT32 UIS_CanvasDrawImage(
		UINT8                picture_type, // Type image source: DRM, file
		PICTURE_TYPE_UNION_T picture_data,
		GRAPHIC_POINT_T      anchor_point,
		UINT16               anchor_value,
		UINT8                drawOp,
		UIS_DIALOG_T         handle
	);

	UINT32 UIS_CanvasDrawWallpaper(
		CANVAS_IMAGE_HANDLE_T image_handle,
		GRAPHIC_REGION_T      src_area,
		GRAPHIC_REGION_T      dest_region,
		UINT8                 drawOp,
		WALLPAPER_LAYOUT_T    layout,
		UIS_DIALOG_T          handle
	);

	BOOL UIS_CanvasGetWallpaperFlag(UIS_DIALOG_T dialog);

	void UIS_CanvasSetWallpaperFlag(UIS_DIALOG_T handle, BOOL wallpaperFlag);

	UINT32 UIS_CanvasDrawColorBitmap(
		void            *picture_bytes,   // First byte - width, second byte - height, others 8-bpp(RGB332) or 16-bpp(RGB565)
		GRAPHIC_POINT_T ulc_anchor_point,
		UIS_DIALOG_T    handle
	);

	// Draw picture from DRM
	UINT32 UIS_CanvasDrawPicture(
		UINT8            *draw_buf,
		RESOURCE_ID      picture,
		GRAPHIC_REGION_T region,
		BOOL             unk0,
		COLOR_T          foreground,
		COLOR_T          fill
	);

	UINT32 UIS_CanvasDrawBitmap(
		UINT8            *p_buf,
		const BYTE       *p_bitmap,
		GRAPHIC_REGION_T region,
		BOOL             b_reverse
	);

	UINT32 UIS_CanvasFillRegion(
		UINT8            *p_buf, // UIS_DRAWING_BUFFER_T::p_buf
		GRAPHIC_REGION_T region,
		UINT32           unk_0   // == 0
	);

	// Open image
	CANVAS_IMAGE_HANDLE_T UIS_CanvasOpenImage(UINT8 picture_type, PICTURE_TYPE_UNION_T picture_data);

	// Open image and get image size
	CANVAS_IMAGE_HANDLE_T UIS_CanvasOpenImageAndGetSize(
		UINT8                picture_type,
		PICTURE_TYPE_UNION_T picture_data,
		GRAPHIC_POINT_T      *attributes
	);

	// Close image
	UINT32 UIS_CanvasCloseImage(CANVAS_IMAGE_HANDLE_T image_handle);

	// Change image size
	UINT32 UIS_CanvasResizeImage(
		CANVAS_IMAGE_HANDLE_T image_handle,
		UINT16                percent,      // Zoom image in percents
		GRAPHIC_REGION_T      src_area,     // Initual image size
		GRAPHIC_REGION_T      dest_region,  // New image size
		UINT8                 drawOp,
		UIS_DIALOG_T          handle
	);

	// Return image size
	GRAPHIC_POINT_T UIS_CanvasGetImageSize(UINT8 picture_type, PICTURE_TYPE_UNION_T picture_data);
	
	// Return picture size from DRM
	UINT32 UIS_CanvasGetPictureSize(RESOURCE_ID picture, GRAPHIC_METRIC_T *pic_size);

	// Set image attribute
	UINT32 UIS_CanvasSetImageAttribute(
		CANVAS_IMAGE_HANDLE_T  image_handle,
		IMAGE_ATTRIBUTE_TYPE_T attribute_type,
		void                   *attribute_value
	);

	// Get image attribute
	UINT32 UIS_CanvasGetImageAttribute(
		CANVAS_IMAGE_HANDLE_T  image_handle,
		IMAGE_ATTRIBUTE_TYPE_T attribute_type,
		void                   *attribute_value
	);

	// Insert image to buffer
	UINT32 UIS_CanvasRenderImageToBuffer(
		CANVAS_IMAGE_HANDLE_T image_handle,
		GRAPHIC_POINT_T       image_size,
		GRAPHIC_POINT_T       anchorpoint,
		UINT16                anchor_value,
		GRAPHIC_REGION_T      *image_region,
		UINT8                 drawOp,
		UIS_DIALOG_T          handle
	);

	// Decode image to buffer pointer
	UINT32 UIS_CanvasDecodeImageToPointer(CANVAS_IMAGE_HANDLE_T image_handle, void *pointer);

	// Insert buffer pointer
	UINT32 UIS_CanvasInsert(
		UIS_DIALOG_T    handle,
		void            *pointer,
		GRAPHIC_POINT_T point
	);

	// Move image region
	UINT32 UIS_CanvasMoveRegion(
		GRAPHIC_REGION_T source_region,
		GRAPHIC_REGION_T dest_region,
		UIS_DIALOG_T     handle
	);

	// Starting animation
	BOOL UIS_CanvasIsImageAnimated(CANVAS_IMAGE_HANDLE_T image_handle);

	// Pause animation
	BOOL UIS_CanvasPauseAnimation(CANVAS_IMAGE_HANDLE_T image_handle);
	
	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Standart GUI ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	// Draw titlebar
	void UIS_CanvasDrawTitleBar(
		WCHAR        *str,
		BOOL         unk0,           // == false
		UINT8        type_titlebar,  // Not different
		BOOL         left_icon,      // Icon draw at left side
		BOOL         right_icon,     // Icon draw at right side
		UIS_DIALOG_T handle
	);

	// Draw titlebar with icon
	void UIS_CanvasDrawTitleBarWithIcon(
		WCHAR        *str,
		RESOURCE_ID  picture,
		BOOL         unk0,           // == false
		UINT8        type_titlebar,  // 0 - standart, 1 - advanced, 2 - editor
		BOOL         left_icon,      // Icon draw at left side
		BOOL         right_icon,     // Icon draw at right side
		UIS_DIALOG_T handle,
		UINT16       slide,          // Slide number, 0 by default
		UINT16       slides          // Slides count
	);

	// Draw softkeys
	void UIS_CanvasDrawColorSoftkey(
		WCHAR        *str,
		UINT8        type_softkey, // 0 - menu, 1 - left, 2 - right
		BOOL         pressed,
		BOOL         unk0,         // == false
		UIS_DIALOG_T handle
	);

	// Draw scrollbar
	void UIS_CanvasDrawColorScrollBar(
		UINT16       count_items,        // Items count
		UINT16       visible,            // Visble status
		UINT16       count_items_passes, // Already scrolled
		BOOL         unk0,               // == false
		UIS_DIALOG_T handle
	);

	// Get softkeys display area
	GRAPHIC_REGION_T UIS_CanvasGetMainDisplaySoftkeyArea(void);

	UINT8 UIS_CanvasGetSoftkeyRegion(
		GRAPHIC_REGION_T *region,
		UINT8            type_softkey,
		BOOL             use_soft_icon_area
	);

	UINT8 UIS_CanvasGetSoftkeyTextRegion(
		GRAPHIC_REGION_T *region,
		UINT8            type_softkey,
		BOOL             use_soft_icon_area
	);
	
	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Others API ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	// Set fill color
	void UIS_CanvasSetFillColor(COLOR_T color);

	// Get fill color
	COLOR_T UIS_CanvasGetFillColor(void);

	// Set foreground color for lines, rectangles, text and etc...
	void UIS_CanvasSetForegroundColor(COLOR_T color);

	// Get foreground color for lines, rectangles, text and etc...
	COLOR_T UIS_CanvasGetForegroundColor(void);

	// Set background color
	void UIS_CanvasSetBackgroundColor(COLOR_T color);

	COLOR_T UIS_CanvasGetBackgroundColor(void);

	// Line width
	void UIS_CanvasSetLineWidth(UINT16 width);

	UINT16 UIS_CanvasGetLineWidth(void);

	// Display update
	void UIS_CanvasRefreshDisplayRegion(UIS_DIALOG_T handle, GRAPHIC_REGION_T region);

	void UIS_CanvasRefreshDisplayBuffer(UIS_DIALOG_T handle);

	// Set default display buffer
	void UIS_CanvasSetDefaultDisplayBuffer(UINT8 *new_draw_buf, UIS_DIALOG_T handle);

	// Get default display buffer
	UINT8 *UIS_CanvasGetDefaultDisplayBuffer(UIS_DIALOG_T handle);

	// Get possibility color depth in bits
	UINT32 UIS_CanvasGetColorDepth(void);

	// Get display size
	GRAPHIC_POINT_T UIS_CanvasGetDisplaySize(void);

	// Enable and disable display backlight
	UINT32 UIS_CanvasSetBackLight(BOOL state);

	enum {

		WHOLE_DISPLAY_AREA,
		NORMAL_DISPLAY_AREA,
		COMMON_DISPLAY_AREA,
		SOFTKEY_AREA,
		STATUS_LINE_AREA,
		TITLE_BAR_AREA

	};
	typedef UINT32 WORKING_AREA_T;

	// Get working area
	UINT8 UIS_CanvasGetWorkingArea(
		GRAPHIC_REGION_T *working_area,
		UINT8            *count_lines,
		UINT8            *chars_on_line,
		WORKING_AREA_T   areas,
		BOOL             use_status_line_area,
		UINT8            font_id
	);

	// Get resource size - image from DRM
	void utility_get_image_size(
		RESOURCE_ID res_id,
		UINT16      *width,
		UINT16      *height
	);

	// Draw image on desktop, GIF or bitmap
	UINT32 utility_draw_image(
		RESOURCE_ID      res_id,
		GRAPHIC_REGION_T region,
		void             *p_attr, // == NULL
		void             *drawBuf // == NULL
	);

#ifdef __cplusplus
}
#endif

#endif // CANVAS_H

/* EOF */
