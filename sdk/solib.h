/* --------------------------------------------------------------------------------------------------------------------------------
 * ElfPack version 2.0 API for Motorola P2k OS
 * --------------------------------------------------------------------------------------------------------------------------------
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * Dynamic link libraries SDK - Shared Object format
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef __SDK_SO_LIB_H__
#define __SDK_SO_LIB_H__

#if (defined(EP2) && defined(SHARED_LIB) && defined(__GNUC__))
	#define SO_PUBLIC __attribute__((visibility("default")))
	#define SO_LOCAL  __attribute__((visibility("hidden")))
#else
	#define SO_PUBLIC
	#define SO_LOCAL
#endif

#endif // __SDK_SO_LIB_H__

/* EOF */