/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * Device Layer SDK
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef __SDK_DL_H__
#define __SDK_DL_H__

#include <typedefs.h>
#include <time_date.h>
#include <dl_keypad.h>

#ifdef __cplusplus
extern "C" {
#endif
	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Battery control ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	#define HAPI_BATTERY_ROM_BYTE_SIZE      128
	#define HAPI_BATTERY_ROM_UNIQUE_ID_SIZE 6

	enum {

		HAPI_BATTERY_ROM_NONE = 0,
		HAPI_BATTERY_ROM_W_DATA,
		HAPI_BATTERY_ROM_WO_DATA,
		HAPI_BATTERY_ROM_INVALID

	};
	typedef UINT8 HAPI_BATTERY_ROM_T;

	HAPI_BATTERY_ROM_T HAPI_BATTERY_ROM_read(UINT8 *dest_address);

	void HAPI_BATTERY_ROM_get_unique_id(UINT8 *unique_id);
	
	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Light control ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	/* Display backlight levels control
	 * E398 only
	 */
	void HAPI_LP393X_disp_backlight_intensity(UINT32 light); // light = 0 - 100

	/* Side leds and flashlight
	 * E398 only
	 */
	void HAPI_LP393X_set_tri_color_led(
		UINT32 type, // 0 - side leds, 1 - flashlight
		UINT32 val   // 0xRGB (0x000 - 0xFFF), for example: 0x00F - blue
	);

	typedef struct {

		unsigned int *addr;
		unsigned int data;
		unsigned int mask;
		UINT8        rw;
		UINT8        reg;

	} HAPI_CAP_ACCESS;

	// Keypad backlight
	void HAPI_PCAP_transceive(HAPI_CAP_ACCESS *);

	/* Start funlight at number fl_id
	 * E398 only
	 */
	UINT32 DL_AudStartFunlight(
		UINT8  fl_id,
		UINT32 p2,    // p2 = 1
		UINT32 p3     // p3 = 0
	);

	/* Stop funlight at number fl_id
	 * E398 only
	 */
	UINT32 DL_AudStopFunlight(UINT8 fl_id);

	// Ambient light sensor control
	UINT8 HAPI_ATOD_convert_ambient_light_sensor(void);

	// Keypad backlight update
	void DL_KeyUpdateKeypadBacklight(UINT8 P1); // P1 = 1 lighting; P2 = 0

	// Set display backlight intensity
	UINT32 UIS_SetBacklightWithIntensity(
		UINT8 color,    // == 255
	    UINT8 intensity // == 0 - 6
	);

	#define FL_MAX_REGIONS      8
	#define FL_REGION1_MASK     0x01
	#define FL_REGION2_MASK     0x02
	#define FL_REGION3_MASK     0x04
	#define FL_REGION4_MASK     0x08
	#define FL_REGION5_MASK     0x10
	#define FL_REGION6_MASK     0x20
	#define FL_REGION7_MASK     0x40
	#define FL_REGION8_MASK     0x80
	#define FL_ALL_REGIONS_MASK 0xff

	/* Request control / clear regions :
	 * prior - needed priority, 0 - lowest, 3 - hightest
	 * mask -  sum of region masks, indicate those that we want to manage,
	 * others will be free
	 * returns the sum of the masks of the regions over which control was gained,
	 * for examole: DL_LED_FL_set_control(3, 0x03); display and keypad
	 */
	UINT8 DL_LED_FL_set_control(UINT8 prior, UINT8 mask);

	/* Set regions value:
	 * prior - set same too that DL_LED_FL_set_control
	 * count - region/value pairs number
	 * ... -   here we write in pairs the numbers of regions and their meanings,
	 * returns the sum of the masks of those regions that have been updated
	 * for example: DL_LED_FL_update(3, 2, 1, 5, 2, 0); display set 5 level, keypad disable
	 */
	UINT8 DL_LED_FL_update(UINT8 prior, UINT8 count, ...);
	
	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Data base feature ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	#define ID_KEYPAD_LOCK_79   0x86A
	#define ID_KEYPAD_LOCK_49   0x7F3
	#define ID_WORKING_TABLE_49 0x7F8

	// Reading
	UINT8 DL_DbFeatureGetCurrentState(UINT16 fstate_ID, UINT8 *state);

	// Writing
	UINT8 DL_DbFeatureStoreState(UINT16 fstate_ID, UINT8 state);

	UINT8 DL_DbFeatureGetValue(UINT16 feature_id, UINT32 *feature_value);

	UINT8 DL_DbFeatureGetValueString(UINT32 feature_id, WCHAR *feature_string);

	UINT32 APP_UtilGetDataVolume(UINT16 feature_id, UINT64 *data_vol);

	// Last call time
	#define C_TM S_TM - 3

	typedef struct {

		UINT16 hours;
		UINT8  minutes;
		UINT8  seconds;

	} CALL_TIME_T;

	UINT8 DL_DbFeatureGetBlock(UINT16 feature_id, void *data_ptr);

	// Firmware version
	#ifdef PATCH
		extern char product_version[];
	#else
		extern char product_version[];
	#endif
	
	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- SEEM's control ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	typedef struct {

		UINT16 seem_element_id;
		UINT16 seem_record_number;
		UINT32 seem_offset;
		UINT32 seem_size;

	} SEEM_ELEMENT_DATA_CONTROL_T;

	// Read data from SEEM
	UINT16 SEEM_ELEMENT_DATA_read(
		SEEM_ELEMENT_DATA_CONTROL_T *data_ctrl_ptr,        // Pointer to data structure, contains information about request
		UINT8                       *data_buf,             // Pointer to data buffer
		BOOL                        read_zero_byte_allowed // If true, then avaliable small SEEM's, lenght < 255 bytes
	);

	// SEEM write
	UINT16 SEEM_ELEMENT_DATA_write(
		SEEM_ELEMENT_DATA_CONTROL_T *data_ctrl_ptr,
		UINT8                       *seem_data_ptr  // Pointer to buffer with recordable data
	);

	// Return SEEM size
	UINT32 SEEM_GET_ADDRESS_LENGTH_element_length(UINT16 seem_element_id);

	// Return SEEM records count
	UINT16 SEEM_MAX_RECORD_get_max_record(UINT16 seem_element_id);

	/* Read record in buffer "seem_data" "count" byte of SEEM
	 * before reading needed allocate count byte memory
	 */
	UINT32 SEEM_FDI_OUTSIDE_SEEM_ACCESS_read(
		UINT32 seem,
		UINT32 record,
		void   *seem_data,
		UINT32 count
	);

	// Write from buffer "seem_data" "count" byte in SEEM
	#define SEEM_WRITE_METHOD_ADD    0
	#define SEEM_WRITE_METHOD_UPDATE 1

	UINT32 SEEM_FDI_OUTSIDE_SEEM_ACCESS_write(
		UINT32 method,
		UINT32 seem,
		UINT32 record,
		void   *seem_data,
		UINT32 count
	);
	
	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Power control ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	// Reboot function
	void HAPI_WATCHDOG_soft_reset(void);

	// Powerdown function
	void pu_main_powerdown(UINT32 r0);
	
	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Sound volime control ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	// Sound volime types:
	enum {

		BASE = 0,            // Ringtone gain
		PHONE,               // Keypad sound signal gain
		VOICE,               // Multimedia volime LTE
		MICROPHONE,          // Microphone volime
		MULTIMEDIA,          // Multimedia volime LTE2 and V3i
		PTT_TONES,
		MUTABLE_MAX,
		IMMUTABLE_MAX,
		MAX = IMMUTABLE_MAX

	};

	// Set volime level
	void DL_AudSetVolumeSetting(UINT8 volume_type, UINT8 volume);

	// Get volime level
	void DL_AudGetVolumeSetting(UINT8 volume_type, UINT8 *volume);

	extern const UINT32 *GAIN_TABLE;

	#define GAIN_TABLE_BIN ((UINT32 *)*GAIN_TABLE)

	extern const UINT32 *PARAM_TABLE;

	#define PARAM_TABLE_BIN ((UINT32 *)*PARAM_TABLE)
	
	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Calls control ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	#define MAX_CALLS 7

	typedef struct {

		UINT16 call_id;
		UINT8  call_state;

	} CALL_ID_T;

	typedef struct {

		UINT8     number_of_calls;
		UINT8     overall_call_state;
		CALL_ID_T call_state_info[MAX_CALLS];

	} CALL_STATES_T;

	// If number_of_calls == 0, then no calls
	void DL_SigCallGetCallStates(CALL_STATES_T *call_states);

	// TRUE - incoming/outgoing call
	BOOL APP_MMC_Util_IsVoiceCall(void); // If FALSE, then no calls

	BOOL AlmclkReminderUtilCallInProgress(void); // If FALSE, then no active call
	
	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- HAPI read and write signals ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 * ioctl analogue and etc...
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */	

	typedef UINT16 HAPI_SIGNAL_T;

	typedef UINT32 HAPI_DATA_T;

	void hPortWrite(HAPI_SIGNAL_T hapi_signal, HAPI_DATA_T write_data);

	HAPI_DATA_T hPortRead(HAPI_SIGNAL_T hapi_signal);
	
	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Other functions ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	// Location area identification
	typedef struct {

		UINT16 mcc; // Mobile Country Code
		UINT8  mnc; // Mobile Network Code
		UINT16 lac; // Location Area Code

	} SIG_REG_LAI_T;

	void DL_SigRegGetLAI(SIG_REG_LAI_T *lai);

	// Get IMSI
	UINT32 DL_DbSigNamGetTrueIMSI(
		UINT8 unk, // == 0, 1, 2...
		WCHAR *imsi
	);

	/* Write on flash, before writing needed erase block
	 * from address 0x10000000, for example: 0x0 = 0x10000000
	 */
	UINT32 FlashDevWrite(
		UINT8  *buf,
		UINT32 addr,
		UINT32 size
	);

	// Clear block in 128 Kb (write 0xFF)
	UINT32 FlashDevEraseBlock(UINT32 adr);

	// Play tone, return seq_num
	UINT32 DL_AudPlayTone(UINT32 tone, UINT8 volume); // Current volume = 0xFF

	// Stop playing tone
	void DL_AudStopTone(UINT32 tone, UINT32 seq_num);

	// Get security codes
	UINT32 DL_DbSigNamGetSecurityCode(WCHAR *);

	UINT32 DL_DbSigNamGetUnlockCode(WCHAR *);

	// PIN status
	enum {

		SIMPIN_STATUS_SECURED = 2, // Same too without SIM
		SIMPIN_STATUS_NO_PIN,
		SIMPIN_STATUS_INVALID

	};
	UINT8 DL_SimMgrGetPinStatus(UINT8 card);

	// Signal strength
	typedef struct {

		UINT8 percent;
		INT8  dbm;

	} SIGNAL_STRENGTH_T;

	void DL_SigRegQuerySignalStrength(SIGNAL_STRENGTH_T *signal_strength);

	// Cell Id
	void DL_SigRegGetCellID(UINT16 *cell_id);

	// Get battery percents
	UINT8 DL_PwrGetActiveBatteryPercent(void);

	// TRUE - headset avaliable
	BOOL DL_AccIsHeadsetAvailable(void);

	// TRUE - external power is plugin (USB cale too)
	BOOL DL_AccIsExternalPowerActive(void);

	// Display buffer can copy in this address
	extern UINT32 display_source_buffer;

	UINT32 suDisableAllInt(void); // Disable interrupts

	void suSetInt(UINT32 mask);	  // Enable interrupts, return with suDisableAllInt function

#ifdef __cplusplus
}
#endif

#endif // __SDK_DL_H__

/* EOF */
