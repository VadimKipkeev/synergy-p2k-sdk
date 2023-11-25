/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * ZLib SDK
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef SDK_ZLIB_H
#define SDK_ZLIB_H

#include <typedefs.h>

struct internal_state;

typedef struct { // z_stream_s

	BYTE                  *next_in;     // Next input byte
	UINT32                avail_in;     // Number of bytes available at next_in
	UINT32                total_in;     // Total nb of input bytes read so far

	BYTE                  *next_out;    // Next output byte should be put there
	UINT32                avail_out;    // Remaining free space at next_out
	UINT32                total_out;    // Total nb of bytes output so far

	char                  *msg;         // Last error message, NULL if no error
	struct internal_state *state;       // Not visible by applications

	void                  *zalloc_func; // Used to allocate the internal state
	void                  *zfree_func;  // Used to free the internal state
	void                  *opaque_func; // Private data object passed to zalloc and zfree

	int                   data_type;    // Best guess about the data type: binary or text
	UINT32                adler;        // adler32 value of the uncompressed data
	UINT32                reserved;     // Reserved for future use

} z_stream;

#ifdef __cplusplus
extern "C" {
#endif

	int inflate(z_stream *strm, int flush);

	int inflateEnd(z_stream *strm);

	int inflateInit2_(
		z_stream   *strm,
		int        windowBits,
		const char *version,
		int        stream_size
	);

	int inflateReset(z_stream *strm);

#ifdef __cplusplus
}
#endif

#if !defined(FTR_V600)
	#define inflateInit2(strm, windowBits) inflateInit2_(strm, windowBits, "1.2.1", sizeof(z_stream))
#else
	#define inflateInit2(strm, windowBits) inflateInit2_(strm, windowBits, "1.1.3", sizeof(z_stream))
#endif

#ifndef MAX_WBITS
	#define MAX_WBITS 15
#endif

#define Z_SYNC_FLUSH 2

#define Z_OK            0
#define Z_STREAM_END    1
#define Z_NEED_DICT     2
#define Z_ERRNO         (-1)
#define Z_STREAM_ERROR  (-2)
#define Z_DATA_ERROR    (-3)
#define Z_MEM_ERROR     (-4)
#define Z_BUF_ERROR     (-5)
#define Z_VERSION_ERROR (-6)

#endif // SDK_UTIL_H

/* EOF */