/* --------------------------------------------------------------------------------------------------------------------------------
 * Cryptography SDK for Motorola P2k OS
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2023 EXL. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef SDK_CRYPT_H
#define SDK_CRYPT_H

#include <typedefs.h>

#define HASH_MD5_DATA_LENGTH 16

typedef struct {

	BYTE data[HASH_MD5_DATA_LENGTH];

} HASH_MD5_T;

#ifdef __cplusplus
extern "C" {
#endif

	void MD5(
		HASH_MD5_T *dst,
		const void *src,
		size_t     src_length
	);

#ifdef __cplusplus
}
#endif

#endif // SDK_CRYPT_H

/* EOF */