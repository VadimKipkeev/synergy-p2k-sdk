/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * Standart C library SDK
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef SDK_STDLIB_H
#define SDK_STDLIB_H

#include <typedefs.h>
#include <time_date.h>
#include <stdargs.h>

/* --------------------------------------------------------------------------------------------------------------------------------
 *                      ---- Minimum and maximum macros ----
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef __max
	#define __max(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef __min
	#define __min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
	#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
	#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef abs
	#define abs(i) ((i) < 0 ? -(i) : (i))
#endif

#ifdef __cplusplus
extern "C" {
#endif

	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- ANSI strings routines ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	/* WARNING!
	 * in standard limited functions with "dst" record is not safety
	 * because, if "src" string length greater that "n", then in "dst" will be written end of string character "\0"
	 */
	size_t strlen(const char *str);              // String legth

	char *strcat(char *dst, const char *src);    // Strings concatenation

	char *strchr(const char *str, int s);        // Searching character in a string

	int strcmp(const char *s1, const char *s2);  // Strings compare

	int stricmp(const char *s1, const char *s2); // Strings compare

	#define strcasecmp stricmp
	
	char *strcpy(char *dst, const char *src); // String copy

	// Limited strings concatenation
	char *strncat(
		char       *dst,
		const char *src,
		size_t     n
	);

	// Limited strings compare
	int strncmp(
		const char *s1,
		const char *s2,
		size_t     n
	);

	// Limited strings compare
	int strincmp(
		const char *s1,
		const char *s2,
		size_t     n
	);

	// Limited string copy
	char *strncpy(
		char       *dst,
		const char *src,
		size_t     n
	);

	char *strstr(const char *str, const char *srch); // Searching substring

	char *strrchr(const char *str, int s);           // Reverse searching for a character in a string

	char *strtok(char *, const char *);              // Searching for tokens in a string

	int toupper(int c);                              // Convert character to UPPER REGISTER

	int tolower(int c);                              // Convert character to lower register

	size_t strcspn(const char *str1, const char *str2); // Returns the index of the character in "str1" which is compare to one of the characters in "str2"

	size_t strspn(const char *str1, const char *str2);  // Returns the index of the character in "str1" which is not compare to one of the characters in "str2"

	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Unicode strings routines ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	size_t u_strlen(const WCHAR *str);

	WCHAR *u_strcat(WCHAR *dst, const WCHAR *str);

	// Add "n" characters from "src" to "dst" string
	WCHAR *u_strncat(
		WCHAR       *dst,
		const WCHAR *src,
		UINT32      n
	);

	INT32 u_strcmp(const WCHAR *s1, const WCHAR *s2);

	WCHAR *u_strcpy(WCHAR *dst, const WCHAR *src);

	INT32 u_strncmp(
		const WCHAR *s1,
		const WCHAR *s2,
		size_t      count
	);

	WCHAR *u_strncpy(
		WCHAR       *dst,
		const WCHAR *src,
		size_t      count
	);

	// Searching in "str" first entry of "chr" character
	WCHAR *u_strchr(const WCHAR *src, WCHAR chr);

	// Searching in "str" last entry of "chr" character
	WCHAR *u_strrchr(const WCHAR *src, WCHAR chr);

	// Searching in "src" with register
	WCHAR *u_strstr(const WCHAR *src, const WCHAR *search);

	// Searching in "src" without register
	WCHAR *u_stristr(const WCHAR *src, const WCHAR *search);

	// Deleting part of string "n" length from "pos" position
	INT32 u_strcut(
		WCHAR  *str,
		UINT16 len_str,
		UINT16 pos,
		int    n
	);

	WCHAR *u_strmakeupper(WCHAR *str); // Convert Unicode character to UPPER REGISTER

	WCHAR *u_strmakelower(WCHAR *str); // Convert Unicode character to lower register

	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Convert functions ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	// ANSI string to Unicode
	WCHAR *u_atou(const char *src, WCHAR *dst);

	// Unicode string to ANSI (valid only for ASCII-range symbols)
	char *u_utoa(const WCHAR *src, char *dst);

	// Unicode to UTF-8
	UINT16 DL_Char_convUCS2toUTF8String(
		const WCHAR *src_ptr,
		UINT16      src_len,
		UINT8       *trg_ptr,
		UINT16      trg_len
	);

	// UTF-8 to Unicode
	UINT16 DL_Char_convUTF8toUCS2String(
		const UINT8 *src_ptr,
		UINT16      src_len,
		WCHAR       *trg_ptr,
		UINT16      trg_len
	);

	// CP-1251 to Unicode
	UINT16 DL_Char_convCP1251toUCS2String(
		const UINT8 *src_ptr,
		UINT16      src_len,
		WCHAR       *trg_ptr,
		UINT16      trg_len
	);

	// KOI8-R to Unicode
	UINT16 DL_Char_convKOI8RtoUCS2String(
		const UINT8 *src_ptr,
		UINT16      src_len,
		WCHAR       *trg_ptr,
		UINT16      trg_len
	);

	/* Converting STRING <-> NUMBER
	 * str - pointer to string
	 * end - return pointer to string in place, where conversion is complete
	 * base, radix - base of converted value, if == 0, using smart definition - "0x..." (HEX), rest in DEC
	 */

	// Converting string to long number (INT32)
	long strtol(
		const char *str,
		char       **end,
		int        base
	);

	// Converting string to unsigned long number (UINT32)
	unsigned long strtoul(
		const char *str,
		char       **end,
		int        base
	);

	// Converting number to string
	char *_itoa(
		int  value,
		char *string,
		int  radix
	);

	#define itoa(v, s, r) _itoa(v, s, r)

	// Number to Unicode string
	WCHAR *u_ltou(long number, WCHAR *str);

	// Unicode string to unsigned long number (UINT32)
	long u_atol(const WCHAR *str);

	// Convert number from DEC to HEX
	WCHAR *u_itoh(int value, WCHAR *dst);

	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Other functions ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	void *bsearch(
		const void *key,
		const void *buf,
		size_t     num,
		size_t     size,
		int        (*compare)(const void *, const void *)
	);

	void qsort(
		void   *buf,
		size_t num,
		size_t size,
		int    (*compare)(const void *, const void *)
	);

	int rand(void);

	void srand(unsigned int seed);

	#define randomize() srand((UINT32)suPalReadTime())
	#define rand_init() srand((UINT32)suPalReadTime())
	#define random(num) (rand() % (num))

	int abs_0(int);

	#ifndef EMUELF
		int sprintf(char *str, const char *format, ...);

		int snprintf(char *str, size_t maxlen, const char *format, ...);

		int vsprintf(
			char       *buffer,
			const char *format,
			va_list    arglist
		);

		int vsnprintf(
			char       *buffer,
			size_t     maxlen,
			const char *format,
			va_list    arglist
		);

	#ifndef WIN32
		#define printf(format, ...) PFprintf(format, ##__VA_ARGS__)
		#define sscanf(buffer, format, ...) Nsscanf(buffer, format, ##__VA_ARGS__)
	#endif

	#endif

	void PFprintf(const char *format, ...); // %d %x %s, a-la printf

	int Nsscanf(const char *buffer, const char *format, ...); // Arguments

	void suLogData(UINT32 *phandle, UINT32 msgid, UINT32 num_pairs, ...);

	#define LOG(format, ...)                                                        \
		do                                                                          \
		{                                                                           \
			UtilLogStringData("%s:%d: " format, __func__, __LINE__, ##__VA_ARGS__); \
			PFprintf("%s:%d: " format, __func__, __LINE__, ##__VA_ARGS__);          \
		} while (0);

	#if !defined(DEBUG)
		#define D(format, ...)
		#define P()
	#else
		#define D(format, ...)                                                      \

		do                                                                          \
		{                                                                           \
			UtilLogStringData("%s:%d: " format, __func__, __LINE__, ##__VA_ARGS__); \
			PFprintf("%s:%d: " format, __func__, __LINE__, ##__VA_ARGS__);          \
		} while (0);

		#define P() D("%s\n", "Debug Line!")
	#endif

#ifdef __cplusplus
}
#endif

#endif // SDK_STDLIB_H

/* EOF */