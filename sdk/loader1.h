/* --------------------------------------------------------------------------------------------------------------------------------
 * ElfPack version 1.0 API for Motorola P2k OS
 * --------------------------------------------------------------------------------------------------------------------------------
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * Loader SDK
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef SDK_ELFLOADER_H
#define SDK_ELFLOADER_H

#include <typedefs.h>
#include <stdargs.h>

#ifdef __cplusplus
extern "C" {
#endif

    extern void *Lib;

    UINT32 LdrStartApp(EVENT_CODE_T ev_start);

    UINT32 LdrLoadELF(WCHAR *uri, WCHAR *params);

    UINT32 LdrUnloadELF(void *elf_ptr);

    const char *LdrGetPhoneName(void);

    const char *LdrGetPlatformName(void);

    const char *LdrGetFirmwareMajorVersion(void);

    const char *LdrGetFirmwareMinorVersion(void);

    void UtilLogStringData(const char *format, ...); // For P2K OS data loger

    // Quick compare strings
    UINT32 namecmp(const char *str1, const char *str2); // Returns 1, if equal

#ifdef __cplusplus
}
#endif

#endif // SDK_ELFLOADER_H

/* EOF */