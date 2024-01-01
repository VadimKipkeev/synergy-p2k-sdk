/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * J2ME SDK
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef JAVA_SDK_H
#define JAVA_SDK_H

#include <typedefs.h>

#ifdef __cplusplus
extern "C" {
#endif

	// Suspend Midlet
	UINT32 JavaSuspendApp(void);

	// Resume Midlet
	UINT32 JavaResumeApp(void);

	// Check JVM is running
	UINT32 JavaAppRunning(void);

	#define JAVA_APP_ID UINT32

	/* Rules of setup Midlet number
	 * file number << 8 | 0x20001
	 */
	#define DL_FS_MID_T_to_JAVA_APP_ID(fs_mid, java_app) \
	{ \
		java_app = fs_mid << 8 | 0x20001 \
	}

	UINT32 JavaStartApp(
		JAVA_APP_ID java_id,
		WCHAR     *str,      // Unknown
		UINT64    unk1,      // == 0
		UINT32    arg_0,     // == 0
		SU_PORT_T port
	);

	// Reserved function
	// UINT32 JavaNotifyAlarm(WCHAR *title)

	JAVA_APP_ID JavaGetMidletSuite(JAVA_APP_ID java_id);

	JAVA_APP_ID JavaGetMIDletID(
		WCHAR *suite_name,
		WCHAR *midlet_name,
		WCHAR *vendor_name
	);

	// Text output in JVM
	extern WCHAR jsapi_marquee_text[];

	UINT32 JavaStartMarquee(const WCHAR *text);

	UINT32 JavaStopMarquee(const WCHAR *text);  // text = jsapi_marquee_text

#ifdef __cplusplus
}
#endif

#endif // JAVA_SDK_H

/* EOF */