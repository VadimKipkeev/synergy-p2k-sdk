/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * Send standart arguments to ADS and GCC compilators
 * --------------------------------------------------------------------------------------------------------------------------------
 */

// ADS (ElfPack version 1.0)
#if defined(__arm)
	#include <stdarg1.h>

// GCC (ElfPack version 2.0)
#elif defined(__GNUC__)
	#include <stdarg2.h>

// Windows (EmuElf)
#elif defined(WIN32)
	#include <stdarg.h>
#endif // STDARGS_H

/* EOF */