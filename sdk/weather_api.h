/* --------------------------------------------------------------------------------------------------------------------------------
 * Weather Manager API for Motorola P2k OS
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2010 om2804. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef WEATHER_API_H
#define WEATHER_API_H

#include <typedefs.h>
#include <events.h>

/* Weather Manager
 * from https://www.gismeteo.ru
 */

#ifdef EP2
	#include <loader2.h>

	#define WeatherReqAPI(add_data) \
	AFW_CreateInternalQueuedEvAuxD(ldrGetConstVal(WEATHER_MGR_MAIN_REGISTER), &add_data, FBF_LEAVE, 0, NULL);
#else
	#define WeatherReqAPI(add_data) \
	AFW_CreateInternalQueuedEvAuxD(WEATHER_MGR_MAIN_REGISTER, &add_data, FBF_LEAVE, 0, NULL);
#endif

#ifdef __cplusplus
extern "C" {
#endif

	typedef UINT32 Weather_getForecast_f(WCHAR *buf, UINT8 num); // num = 1... 4 - not used

	typedef UINT32 Weather_getTemperature_f(WCHAR *buf, UINT8 num);

	typedef UINT32 Weather_getPhenomena_f(WCHAR *buf, UINT8 num);

	typedef UINT32 Weather_getWind_f(WCHAR *buf, UINT8 num);

#ifdef __cplusplus
}
#endif

#endif // WEATHER_API_H

/* EOF */