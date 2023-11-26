/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * Shortcuts SDK additional functions
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef SC_H
#define SC_H

#include <typedefs.h>
#include <events.h>

#ifdef __cplusplus
extern "C" {
#endif

    #define SC_TYPE_URL 5
    #define SC_TYPE_APP 6

    typedef UINT8 SC_TYPE_T;

    // Sending by event attach at call with shortcut
    typedef struct {

        UINT8  seem_rec;    // seem_rec-1                        /*+00*/
        UINT8  type;        // Shortcut type                     /*+01*/ 
        UINT8  index;       // Number in list, starting from 1   /*+02*/
        UINT8  unk1;        // 0xFE                              /*+03*/
        UINT32 ev_code;                                          /*+04*/
        UINT32 list1_index; // ID of selected list item          /*+08*/
        UINT32 param1;                                           /*+12*/    
        UINT32 list2_index; // ID of list item                   /*+16*/
        UINT32 param2;                                           /*+20*/
        UINT32 data;                                             /*+24*/
        UINT32 lang_text;   // RESOURCE_ID                       /*+28*/
        WCHAR  text[17];    // Shortcut name - 34                /*+32*/
        UINT8  state;       // State number on shortcut creation /*+66*/

    } SEEM_0002_T; // == 68

    #define SHORTCUT_RECORD_T SEEM_0002_T

    /* Sending in attach with event
     * #define EV_HANDLE_SHORTCUT 0x20C5
     */
    typedef struct {

        UINT8  type;                     /*+00*/
        UINT32 param1;                   /*+04*/
        UINT32 list1_index;              /*+08*/
        UINT32 param2;                   /*+0C*/	
        UINT32 list2_index;              /*+10*/
        WCHAR  text[17];    // 0x22 = 34 /*+14*/
        UINT32 lang_text;                /*+38*/

    } SHORTCUT_CREATE_T; // 0x3c = 60

    // Formed sc_data based on "ev_code", "state", "data", and attach data SHORTCUT_CREATE_T, parameters 
    UINT32 APP_UtilShortcutBuildRecord(
        EVENT_STACK_T     *ev_st,
        SHORTCUT_RECORD_T *sc_data,
        UINT32            ev_code,
        UINT32            state,
        UINT32            data
    );

    // Copy attach SHORTCUT_RECORD_T in app->sc_data - allocate memory
    UINT32 APP_UtilShortcutCopyRecordFromEv(EVENT_STACK_T *ev_st, void *app);

    /* Call shortcut creation standart dialog window
     * formed record, based on "ev_code", "state", and attach data, parameters:
     * ev_code - event, called by shortcut;
     * state - application state;
     * data - additional shortcut data
     */
    UINT32 APP_UtilShortcutAcceptCreate(
        EVENT_STACK_T *ev_st,
        void          *app,
        UINT32        ev_code,
        UINT32        state,
        UINT32        data
    );

    /* Call create shortcut standart dialog window
     * formed record, based on "ev_code" and attach data, parameters:
     * ev_code - event, called by shortcut
     * 
     * SHORTCUT_RECORD_T.type = SC_TYPE_APP
     * SHORTCUT_RECORD_T.state = 0xFF
     */
    UINT32 APP_UtilShortcutCreateAppShortcut(
        EVENT_STACK_T *ev_st,
        void          *app,
        UINT32        ev_code
    );

    // Get shortcut record type (not equal SHORTCUT_RECORD_T.type)
    UINT32 APP_UtilShortcutGetShortcutType(UINT32 t); // SC_RECORD_T.type

    /* Show notification about shortcut calling interdict
     * data getting from app->sc_data, or from event attach
     */
    UINT32 APP_UtilShortcutRejectInvoke(EVENT_STACK_T *ev_st, void *app);

    // If event != EV_HANDLE_SHORTCUT, then return RESULT_FAIL, else show notification about shortcut creation interdict
    UINT32 APP_UtilShortcutRejectCreate(EVENT_STACK_T *ev_st, void *app);

    /* Not approved */

    // At shortcut reading
    #define EV_SHORTCUT_READ_RECORD 0x820F7 // In attach of SHORTCUT_READ_RECORD_T

    // At shortcut URL reading
    #define EV_SHORTCUT_READ_URL    0x82112 // In attach of SHORTCUT_READ_URL_T

    typedef struct {

        UINT8       result; // 0 if success
        UINT8       unk0;
        SEEM_0002_T *record;

    } SHORTCUT_READ_RECORD_T;

    typedef struct {

        UINT8  result; 
        UINT16 url_strlen;
        UINT8  url[100];

    } SHORTCUT_READ_URL_T;

    // Create new shortcut record								
    UINT8 DL_DbShortcutCreateRecord(IFACE_DATA_T *data, SEEM_0002_T record);

    // Update shortcut record
    UINT8 DL_DbShortcutUpdateRecord(IFACE_DATA_T *data, SEEM_0002_T record);

    // Delete shortcut
    UINT8 DL_DbShortcutDeleteRecord(IFACE_DATA_T *data, UINT8 seem_rec);

    /* Get shortcut, function is async, sending with EV_SHORTCUT_READ_RECORD event,
     * in attachment contains SHORTCUT_READ_RECORD_T
     */
    UINT8 DL_DbShortcutGetRecordByRecordId(IFACE_DATA_T *data, UINT8 seem_rec);

    // Get avaliable shortcuts records number
    UINT16 DL_DbShortcutGetNumOfRecordsAvailable(void); 

    // Get used shortcuts records number
    UINT16 DL_DbShortcutGetNumOfRecordsUsed(BOOL voice_shortcut);

    // Get first shortcut record avaliable number
    UINT8 DL_DbGetFirstAvailableNumber(void); 

    // Get used URL records number
    UINT16 DL_DbShortcutGetNumOfURLRecordsUsed(void);

    // Get avaliable URL records number
    UINT16 DL_DbShortcutGetNumOfURLRecordsAvailable(void);

    // Get URL from record, function is async, sending with EV_SHORTCUT_READ_URL event
    UINT32 DL_DbShortcutGetURLByURLId(IFACE_DATA_T *data, UINT32 URLId);

    // Get shortcut record type
    SC_TYPE_T DL_DbShortcutGetshortcutType(UINT8 index);

#ifdef __cplusplus
}
#endif

#endif // SC_H

/* EOF */