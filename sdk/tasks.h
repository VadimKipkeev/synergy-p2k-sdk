/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * suAPI tasks management for VRTXmc RTOS
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef TASKS_H
#define TASKS_H

#include "typedefs.h"

typedef void (*TASK_ENTRY_FN)(void *);

#ifdef __cplusplus
extern "C" {
#endif

    // Create task for application
    INT32 suCreateTask(
        TASK_ENTRY_FN entry,
        UINT32        stacksize,
        UINT8         priority
    );

    // Delete task
    INT32 suDeleteTask(int tid);

    void suSleep(UINT32 time, INT32 *result);

    typedef UINT32 SEMAPHORE_HANDLE_T;
    typedef UINT32 SEMAPHORE_STATE_T;

    #define SEMAPHORE_LOCKED   0
    #define SEMAPHORE_UNLOCKED 1

    #define SEMAPHORE_WAIT_FOREVER 0x7FFFFFFFL

    SEMAPHORE_HANDLE_T suCreateBSem(SEMAPHORE_STATE_T init_state, INT32 *err);

    SEMAPHORE_HANDLE_T suCreateCSem(
        SEMAPHORE_STATE_T init_count,
        SEMAPHORE_STATE_T bound,
        INT32             *err
    );

    SEMAPHORE_HANDLE_T suCreateMSem(SEMAPHORE_STATE_T init_state, INT32 *err);

    // Delete semaphore
    void suDeleteSem(SEMAPHORE_HANDLE_T handle, INT32 *err);

    INT32 suAcquireSem(
        SEMAPHORE_HANDLE_T handle,
        SU_TIME            timeout,
        INT32              *err
    );

    INT32 suReleaseSem(SEMAPHORE_HANDLE_T handle, INT32 *err);

#ifdef __cplusplus
}
#endif

#endif // TASKS_H

/* EOF */