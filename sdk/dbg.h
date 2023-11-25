/* --------------------------------------------------------------------------------------------------------------------------------
 * Debugger API for Motorola P2k OS
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2008 G-XaD. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * Debugger API
 * --------------------------------------------------------------------------------------------------------------------------------
 */

/* --------------------------------------------------------------------------------------------------------------------------------
 *  Debugger/Отладчик
 * --------------------------------------------------------------------------------------------------------------------------------
 * Description on Russian
 * --------------------------------------------------------------------------------------------------------------------------------
 * Использование:
 * 1) Подлинковать "dbg.o"
 * 2) Подключить этот файл (в оригинале "dbg.h") после других #include
 * 3) Использовать в коде программы макросы
 * 4) Чтобы включить вывод простых отладочных сообщений добавте строку "#define DEBUG" перед блоком #include
 * 5) Чтобы включить вывод отладочных сообщений обращения к менеджеру памяти добавте строку "#definde DEBUG_MEMORY"
 *    перед блоком #include
 * 
 * Если оба вида отладчиков будут выключены, то обьектый файл "dbg.o" никак не будет влиять на размер конечного приложения
 *
 * Макросы:
 * 1) void warn(const char *format, ...) - форматированный вывод сообщений со пометкой "warn" (Внимание!) в midway
 * 2) void dbg(const char *format, ...) - форматированный вывод сообщений со пометкой "dbg" (Отладка) в midway
 * 3) void err(const char *format, ...) - форматированный вывод сообщений со пометкой "err" (Ошибка) в midway,
 *    используйте при неожиданных выходах из программы
 * 4) void *malloc(size_t size) - запрос к менеджеру памяти на выделение size байт оперативной памяти
 * 5) void free(void *mem) - сообщение к менеджеру памяти о том, что выделенная ранее память уже не используется
 * 6) void ddbg(const void *data, size_t size) - вывод в midway блока данных размером size, который расположен по адрессу data
 * 7) void udbg(const char *format, const WCHAR *ustr) - форматированный вывод сообщения в midway с одной юникод строкой
 * 8) DEBUG_TIME
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef APP_DEBUGGER
#define APP_DEBUGGER

#include <typedefs.h>
#include <mem.h>
#include <utilities.h>
#include <time_date.h>

// Application name get from global value
extern const char app_name[];

/* --------------------------------------------------------------------------------------------------------------------------------
 *                      ---- Some constant, notes about message types ----
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#define TRACE_ERR_STR      "err: "
#define TRACE_WARN_STR     "warn: "
#define TRACE_DBG_STR      "dbg: "
#define TRACE_U_STR        "udbg: "

#define TRACE(format, ...) PFprintf(format, ##__VA_ARGS__)
#define TRACE_STRING(str)  PFprintf(str)

/* --------------------------------------------------------------------------------------------------------------------------------
 *                      ---- Realisation message debugger to memory manager ----
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifdef DEBUG_MEMORY
	#define dmalloc(sz) \
		dbg_malloc(app_name, sz, __FILE__, __LINE__)

	#define dfree(mb) \
		dbg_free(app_name, mb, __FILE__, __LINE__)
#else // DEBUG_MEMORY
	#define dmalloc(sz) \
		malloc(sz)

	#define dfree(mb) \
		mfree(mb)
#endif

/* --------------------------------------------------------------------------------------------------------------------------------
 *                      ---- Realisation simple debugger ----
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifdef DEBUG
	#define err(format, ...) \
		TRACE("%s: " TRACE_ERR_STR "\"%s\"@%d: " format "\n", app_name, __FILE__, __LINE__, ##__VA_ARGS__)

	#define warn(format, ...) \
		TRACE("%s: " TRACE_WARN_STR "\"%s\"@%d: " format "\n", app_name, __FILE__, __LINE__, ##__VA_ARGS__)

	#define dbg(format) \
		TRACE("%s: " TRACE_DBG_STR "@%d: " format "\n", app_name, __LINE__)

	#define dbgf(format, ...) \
		TRACE("%s: " TRACE_DBG_STR "@%d: " format "\n", app_name, __LINE__, ##__VA_ARGS__)

	#define ddbg(d, sz) \
		dbg_data(app_name, d, sz, __FILE__, __LINE__)

	#define udbg(format, ustr) \
		dbg_unicode(app_name, "%s: " TRACE_U_STR "@%d: " format "\n", ustr, __FILE__, __LINE__)
#else // DEBUG
	#define err(format, ...)
	#define warn(format, ...)
	#define dbg(format)
	#define dbgf(format, ...)
	#define ddbg(d, sz)
	#define udbg(format, ustr)
#endif

/* --------------------------------------------------------------------------------------------------------------------------------
 *                      ---- Runtime debugger ----
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifdef DEBUG_TIME
	#define dtime_init()            \
		unsigned int dbg_timer_var; \
		dbg_timer_init(app_name, __FILE__, __LINE__, &dbg_timer_var)

	#define dtime() \
		dbg_time(app_name, __FILE__, __LINE__, dbg_timer_var)
#else
	#define dtime_init()
	#define dtime()
#endif

#ifdef __cplusplus
extern "C" {
#endif
	
	/* --------------------------------------------------------------------------------------------------------------------------------
	 *                      ---- Service functions, not use in applications ----
	 * --------------------------------------------------------------------------------------------------------------------------------
	 */

	void *dbg_malloc(const char *, size_t, const char *, int);

	void dbg_free(const char *, void *, const char *, int);

	void dbg_data(const char *, const void *, UINT16, const char *, int);

	void dbg_unicode(const char *, const char *, const WCHAR *, const char *, int);

	extern void dbg_timer_init(const char *, const char *, int, unsigned int *);

	extern void dbg_time(const char *, const char *, int, unsigned int);

#ifdef __cplusplus
}
#endif

#endif // APP_DEBUGGER

/* EOF */