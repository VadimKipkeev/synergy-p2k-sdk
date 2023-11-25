/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * ATI video driver API
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef ATI_H
#define ATI_H

#include <typedefs.h>

typedef UINT32 AHIDEVCONTEXT_T;
typedef UINT32 AHISURFACE_T;
typedef UINT32 AHIDEVICE_T;

enum AHIPIXFMT_ENUM {

    AHIFMT_1BPP = 0,
    AHIFMT_4BPP,
    AHIFMT_8BPP,
    AHIFMT_16BPP_444,
    AHIFMT_16BPP_555,
    AHIFMT_16BPP_565

};
typedef UINT32 AHIPIXFMT_T;

typedef struct {

    INT32 x;
    INT32 y;

} AHIPOINT_T;

typedef struct {

    INT32 x1;
    INT32 y1;
    INT32 x2;
    INT32 y2;

} AHIRECT_T;

enum AHICMP_ENUM {

    AHICMP_ALWAYS = 0,
    AHICMP_NEVER,
    AHICMP_EQUAL,
    AHICMP_NOTEQUAL

};
typedef UINT32 AHICMP_T;

typedef struct {

    UINT32   key;
    UINT32   mask;
    AHICMP_T cmp;

} AHICOLOROP_T;

typedef struct {

    UINT8 stridex;
    UINT8 stridey;
    UINT8 w;
    UINT8 h;
    void  *image;

} AHICHAR_T;

typedef struct {

    UINT32      width;
    UINT32      height;
    void        *image;
    INT32       stride;
    AHIPIXFMT_T format;

} AHIBITMAP_T;

typedef struct {

    UINT32      width;
    UINT32      height;
    UINT32      offset;
    INT32       stride;
    UINT32      byteSize;
    AHIPIXFMT_T pixFormat;
    UINT32      numPlanes;

} AHISURFINFO_T;

typedef enum {

    AHIROT_0 = 0,
    AHIROT_90,
    AHIROT_180,
    AHIROT_270,

    AHIROT_DUMMY = 0x7FFFFFFF

} AHIROTATE_T;

typedef enum {

    AHIBLEND_SRC_PLUS_DST = 0,
    AHIBLEND_SRC_MINUS_DST,
    AHIBLEND_DST_MINUS_SRC,
    AHIBLEND_SRC_MINUS_ALPHA,
    AHIBLEND_SRC_SHR1,
    AHIBLEND_DST_PLUS_SRC_DIV2

} AHIBLEND_T;

typedef enum {

    AHIMIRR_NO = 0,
    AHIMIRR_VERTICAL,
    AHIMIRR_HORIZONTAL,
    AHIMIRR_VER_HOR,

    AHIMIRR_DUMMY = 0x7FFFFFFF

} AHIMIRROR_T;

typedef struct {

    char   drvName[80]; // Driver name
    char   drvVer[80];  // Driver version
    UINT32 swRevision;
    UINT32 chipId;
    UINT32 revisionId;
    UINT32 totalMemory;
    UINT32 cpuBusInterfaceMode;
    UINT32 internalMemSize;
    UINT32 externalMemSize;
    UINT32 caps1;
    UINT32 caps2;
    UINT8  pad[136];

} AHIDRVINFO_T; // sizeof(AHIDRVINFO_T) == 0x14C

typedef struct {

    UINT32    size;
    BOOL      sync;
    AHIRECT_T rect;

} AHIUPDATEPARAMS_T;

typedef struct {

    AHIPOINT_T  size;
    AHIPIXFMT_T pixel_format;
    UINT32      frequency;
    AHIROTATE_T rotation;
    AHIMIRROR_T mirror;

} AHIDISPMODE_T;

typedef enum {

    DISPLAY_OFF,
    DISPLAY_ON

} AHIDISPSTATE_T;

#ifdef __cplusplus
extern "C" {
#endif

    /* --------------------------------------------------------------------------------------------------------------------------------
     *                      ---- Work with contexts ----
     * --------------------------------------------------------------------------------------------------------------------------------
     */

    // Return information about AHI-device with number index
    UINT32 AhiDevEnum(
        AHIDEVICE_T  *dev,      // Result
        AHIDRVINFO_T *drvInfo,  // Result
        UINT32       index
    );

    // Create new context for selected device
    UINT32 AhiDevOpen(
        AHIDEVCONTEXT_T *devCx,     // Result
        AHIDEVICE_T     dev,        // Param, returned AhiDevEnum
        const char      *caller,    // String identificator context user
        UINT32          flags
    );

    // Close context
    UINT32 AhiDevClose(AHIDEVCONTEXT_T devCx);

    /* --------------------------------------------------------------------------------------------------------------------------------
     *                      ---- Work with surfaces ----
     * --------------------------------------------------------------------------------------------------------------------------------
     */

    // Return size of biggest surface, that can be selected, in pixels
    UINT32 AhiSurfGetLargestFreeBlockSize(
        AHIDEVCONTEXT_T devCx,
        AHIPIXFMT_T     pixFormat,
        UINT32          *size,     // Result
        UINT32          *align,    // Result
        UINT32          flags
    );

    // Allocate surface from video-RAM
    UINT32 AhiSurfAlloc(
        AHIDEVCONTEXT_T devCx,
        AHISURFACE_T    *surf,      // Result
        AHIPOINT_T      *size,      // Needed surface size
        AHIPIXFMT_T     pixFormat,
        UINT32          flags       // If == 2, then the format will be used the same as that of the displayed surface 
    );

    #define AHIFLAG_DISPLAYPIXFMT 0x00000002
    #define AHIFLAG_SYSMEMORY     0x00000008
    #define AHIFLAG_EXTMEMORY     0x00000020
    #define AHIFLAG_INTMEMORY     0x00000040

    // Free allocated surface
    UINT32 AhiSurfFree(AHIDEVCONTEXT_T devCx, AHISURFACE_T surf);

    // Relocated selected surface or change params
    UINT32 AhiSurfReuse(
        AHIDEVCONTEXT_T devCx,
        AHISURFACE_T    *surf,
        AHISURFACE_T    surfReuse,
        AHIPOINT_T      *size,
        AHIPIXFMT_T     pixFormat,
        UINT32          flags
    );

    // Return information about surface
    UINT32 AhiSurfInfo(
        AHIDEVCONTEXT_T devCx,
        AHISURFACE_T    surf,
        AHISURFINFO_T   *info
    );

    // Return current display surface
    UINT32 AhiDispSurfGet(AHIDEVCONTEXT_T devCx, AHISURFACE_T *surf);  // Result

    // Set current display surface
    UINT32 AhiDispSurfSet(
        AHIDEVCONTEXT_T devCx,
        AHISURFACE_T    surf,
        UINT32          flags
    );

    // Copy surface content from and to system-RAM
    UINT32 AhiSurfCopy(
        AHIDEVCONTEXT_T devCx,
        AHISURFACE_T    surf,
        AHIBITMAP_T     *bitmap,
        AHIRECT_T       *dstRect,
        AHIPOINT_T      *srcPt,
        UINT32          param5,
        UINT32          flags     // If == 1, then copy from surface to bitmap
    );

    // IDK, but seems it working
    #define AHIFLAG_COPYTO   0x00000000
    #define AHIFLAG_COPYFROM 0x00000001

    /* --------------------------------------------------------------------------------------------------------------------------------
     *                      ---- Set drawing params ----
     * --------------------------------------------------------------------------------------------------------------------------------
     */

    // Set current color foreground plane (for bitmask)
    UINT32 AhiDrawFgColorSet(AHIDEVCONTEXT_T devCx, UINT32 color);  // RGB565 for E398

    // Set current color background plane (for bitmask)
    UINT32 AhiDrawBgColorSet(AHIDEVCONTEXT_T devCx, UINT32 color);

    // Set current color foreground plane brush
    UINT32 AhiDrawBrushFgColorSet(AHIDEVCONTEXT_T devCx, UINT32 color);

    // Set current color background plane brush
    UINT32 AhiDrawBrushBgColorSet(AHIDEVCONTEXT_T devCx, UINT32 color);

    // Set current brush params
    UINT32 AhiDrawBrushSet(
        AHIDEVCONTEXT_T devCx,
        AHIBITMAP_T     *pattern,   // Pointer to brush template (or NULL)
        AHIPOINT_T      *srcPt,     // Offset in template
        UINT32          param3,
        UINT32          flags
    );

    #define AHIFLAG_BRUSH_TRANSPARENT 1
    #define AHIFLAG_BRUSH_SOLID       2

    // Set current surface-source
    UINT32 AhiDrawSurfSrcSet(
        AHIDEVCONTEXT_T devCx,
        AHISURFACE_T    surf,
        UINT32          flags
    );

    // Set current surface-destination
    UINT32 AhiDrawSurfDstSet(
        AHIDEVCONTEXT_T devCx,
        AHISURFACE_T    surf,
        UINT32          flags
    );

    /* Set clip rect for surface-source
     * if clipRect == NULL, then clip rect reset for full display
     */
    UINT32 AhiDrawClipSrcSet(AHIDEVCONTEXT_T devCx, AHIRECT_T *clipRect);

    // Set clip rect for surface-destination
    UINT32 AhiDrawClipDstSet(AHIDEVCONTEXT_T devCx, AHIRECT_T *clipRect);

    /* Set raster operation (ROP), use macros AHIROP3 for param forming
     * for ROP description, go by links:
     * http://msdn.microsoft.com/en-us/library/dd145130(VS.85).aspx
     * http://www.svgopen.org/2003/papers/RasterOperationsUsingFilterElements/index.html
     */
    UINT32 AhiDrawRopSet(AHIDEVCONTEXT_T devCx, UINT32 rop);

    #define AHIROP_BLACKNESS   0x00
    #define AHIROP_NOTSRCERASE 0x11
    #define AHIROP_NOTSRCCOPY  0x33
    #define AHIROP_SRCERASE    0x44
    #define AHIROP_DSTINVERT   0x55
    #define AHIROP_PATINVERT   0x5A
    #define AHIROP_SRCINVERT   0x66
    #define AHIROP_SRCAND      0x88
    #define AHIROP_MERGEPAINT  0xBB
    #define AHIROP_MERGECOPY   0xC0
    #define AHIROP_SRCCOPY     0xCC
    #define AHIROP_SRCPAINT    0xEE
    #define AHIROP_PATCOPY     0xF0
    #define AHIROP_PATPAINT    0xFB
    #define AHIROP_WHITENESS   0xFF

    #define AHIROP3(_rop) ((_rop) | ((_rop) << 8))

    // Set global level of transparent for AhiDrawAlphaBlt
    UINT32 AhiDrawAlphaSet(AHIDEVCONTEXT_T devCx, UINT32 alpha); // alpha set by colors, RGB888

    #define AHIALPHA(_level) ((_level) | ((_level) << 8) | ((_level) << 16))

    /* --------------------------------------------------------------------------------------------------------------------------------
     *                      ---- Drawing functions ----
     * --------------------------------------------------------------------------------------------------------------------------------
     */

    /* Draw lines array
     * if flags == 0, then build lines array, connecting all points,
     * if flags == 1, then array set begin and ending points for each lines
     */
    UINT32 AhiDrawLines(
        AHIDEVCONTEXT_T devCx,
        AHIPOINT_T      *pointArr,  // Pointer to array
        UINT32          count,      // Points count (must be even)
        UINT32          flags
    );

    #define AHIFLAG_LINE_STRIP    0
    #define AHIFLAG_LINE_SEPARATE 1

    // Draw rect spans array
    UINT32 AhiDrawSpans(
        AHIDEVCONTEXT_T devCx,
        AHIRECT_T       *rectArr,
        UINT32          count,
        UINT32          flags
    );

    // Copy image from surface-source to surface-destination, with ROP
    UINT32 AhiDrawBitBlt(
        AHIDEVCONTEXT_T devCx,
        AHIRECT_T       *dstRect,
        AHIPOINT_T      *srcPt
    );

    // Same, that AhiDrawBitBlt, only with rects array
    UINT32 AhiDrawBitBltMulti(
        AHIDEVCONTEXT_T devCx,
        AHIRECT_T       *dstRectArr,
        AHIPOINT_T      *srcPtArr,
        UINT32          count
    );

    // Copy image from system-RAM to surface-destination
    UINT32 AhiDrawBitmapBlt(
        AHIDEVCONTEXT_T devCx,
        AHIRECT_T       *dstRect,
        AHIPOINT_T      *srcPt,
        AHIBITMAP_T     *bitmap,
        void            *palette,   // Palette pointer
        UINT32          flags       // If == 1, then bitmap image "0" (background) will be transparent, if == 2, then transparent color will be "1"
    );

    // Copy image from surface-source to surface-destination with using bitmask
    UINT32 AhiDrawMaskBlt(
        AHIDEVCONTEXT_T devCx,
        AHIRECT_T       *dstRect,
        AHIPOINT_T      *srcPt,
        AHIPOINT_T      *maskPt,    // Begin point on mask
        void            *mask,      // Mask data (1bpp)
        UINT32          maskStride  // Bytes count in mask line
    );

    // Copy image with rotate and reflecting
    UINT32 AhiDrawRotateBlt(
        AHIDEVCONTEXT_T devCx,
        AHIRECT_T       *dstRect,
        AHIPOINT_T      *srcPt,
        AHIROTATE_T     rotation,
        AHIMIRROR_T     mirroring,
        UINT32          flags
    );

    /* Copy image with using color compare
     * code example for AHICOLOROP_T: if(cmp(color & mask, key)) draw();
     */
    UINT32 AhiDrawTransBlt(
        AHIDEVCONTEXT_T devCx,
        AHIRECT_T       *dstRect,
        AHIPOINT_T      *srcPt,
        AHICOLOROP_T    *dstCop,
        AHICOLOROP_T    *srcCop
    );

    // This function unite possibilities AhiDrawRotateBlt and AhiDrawTransBlt
    UINT32 AhiDrawSpriteBlt(
        AHIDEVCONTEXT_T devCx,
        AHIRECT_T       *dstRect,
        AHIPOINT_T      *srcPt,
        AHICOLOROP_T    *dstCop,
        AHICOLOROP_T    *srcCop,
        AHIROTATE_T     rotation,
        AHIMIRROR_T     mirroring,
        UINT32          flags
    );

    // Copy image from surface-source to surface-destination with alpha-blending
    UINT32 AhiDrawAlphaBlt(
        AHIDEVCONTEXT_T devCx,
        AHIRECT_T       *dstRect,
        AHIPOINT_T      *srcPt,
        AHIPOINT_T      *bmpPt,
        AHIBITMAP_T     *bitmap,    // Set transparent map (4bpp)
        UINT32          flags       // If == 1, then will be used transparent value, setup AhiDrawAlphaSet
    );

    #define AHIFLAG_ALPHA_SOLID 1

    // Copy image with streching
    UINT32 AhiDrawStretchBlt(
        AHIDEVCONTEXT_T devCx,
        AHIRECT_T       *dstRect,
        AHIRECT_T       *srcRect,
        UINT32          flags      // If == 1..4, quality control
    );

    #define AHIFLAG_STRETCHFAST     0x00000001
    #define AHIFLAG_STRETCHPIXEXACT 0x00000002
    #define AHIFLAG_STRETCHSMOOTH   0x00000004

    // Copy image with blending
    UINT32 AhiDrawBlendBlt(
        AHIDEVCONTEXT_T devCx,
        AHIRECT_T       *dstRect,
        AHIPOINT_T      *srcPt,
        AHIBLEND_T      blendOp,
        UINT32          flags
    );

    // Copy image with tiling
    UINT32 AhiDrawTileBlt(
        AHIDEVCONTEXT_T devCx,
        AHIRECT_T       *dstRect,
        AHIPOINT_T      *srcPt,      // Align
        UINT32          flags
    );

    // Draw symbols array from charArr, count things
    UINT32 AhiDrawChar(
        AHIDEVCONTEXT_T devCx,
        AHIPOINT_T      *dstPt,
        AHICHAR_T       *charsArr,
        UINT32          count,
        UINT32          flags
    );

    // Draw symbols array, AhiDrawChar analogue
    UINT32 AhiDrawGlyph(
        AHIDEVCONTEXT_T devCx,
        AHIPOINT_T      *dstPt,
        AHIBITMAP_T     *charsArr,
        UINT32          count,
        UINT32          flags
    );

    /* --------------------------------------------------------------------------------------------------------------------------------
     *                      ---- Others functions ----
     * --------------------------------------------------------------------------------------------------------------------------------
     */

    // Wait VBlank display status
    UINT32 AhiDispWaitVBlank(AHIDEVCONTEXT_T devCx, UINT32 flags);

    // Update CSTN-display on devices such as Motorola L6 and others
    UINT32 AhiDispUpdate(AHIDEVCONTEXT_T context, AHIUPDATEPARAMS_T *update_params);

    // Wait execute ending for current queues of commands
    UINT32 AhiDrawIdle(AHIDEVCONTEXT_T devCx, UINT32 flags);

    // Check rects on collisions plus collision result
    BOOL AhiIntersect(
        AHIRECT_T *prc1,
        AHIRECT_T *prc2,
        AHIRECT_T *prcResult
    );

    // Get list avaliabled video-modes
    UINT32 AhiDispModeEnum(
        AHIDEVCONTEXT_T context,
        AHIDISPMODE_T   *pMode,
        UINT32          index
    );

    // Get current video-mode
    UINT32 AhiDispModeGet(AHIDEVCONTEXT_T context, AHIDISPMODE_T *pMode);

    // Set video-mode
    UINT32 AhiDispModeSet(
        AHIDEVCONTEXT_T context,
        AHIDISPMODE_T   *pMode,
        UINT32          flags
    );

    // Off and on display power, restart display
    UINT32 AhiDispState(
        AHIDEVCONTEXT_T context,
        AHIDISPSTATE_T  state,
        UINT32          flags
    );

#ifdef __cplusplus
}
#endif

#endif // ATI_H

/* EOF */