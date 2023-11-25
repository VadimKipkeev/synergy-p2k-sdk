/* --------------------------------------------------------------------------------------------------------------------------------
 * Motorola Synergy P2k OS Native Development Kit - NDK
 * --------------------------------------------------------------------------------------------------------------------------------
 * Copyright: © 2004 Motorola Inc. All rights reserved
 * ElfPack version 1.0 copyright: © 2007 Andy51, Exebyte, om2804, Vilko, Last, AzT59, ds3v. All rights reserved
 * ElfPack version 2.0 copyright: © 2009 Andy51, tim apple. All rights reserved
 * --------------------------------------------------------------------------------------------------------------------------------
 * MIT License
 * --------------------------------------------------------------------------------------------------------------------------------
 * Memory Manager SDK - Motorola suAPI for VRTXmc RTOS
 * --------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef SDK_MEMORY_H
#define SDK_MEMORY_H

#include <typedefs.h>

#ifdef __cplusplus
extern "C" {
#endif

    /* Allocate memory,
     * if allocating is failed, then in err contains error code,
     * if second parameter == NULL, then at failed will be reboot
     */
    void *suAllocMem(size_t size, INT32 *err);

    #ifdef EP2_INTERNAL
        void *malloc(size_t size);
    #else
        #define malloc(sz) suAllocMem(sz, NULL)
    #endif

    // Free memory function
    void suFreeMem(void *ptr);

    #ifdef EP2_INTERNAL
        void mfree(void *ptr);
    #else
        #define mfree(p) suFreeMem(p)
    #endif

    // Write "0" to memory block
    void __rt_memclr(void *, size_t);

    #ifdef EP2_INTERNAL
        void memclr(void *, size_t);
    #else
        #define memclr(m, sz) __rt_memclr(m, sz)
    #endif

    // Copy memory block
    void *__rt_memcpy(void *, const void *, size_t);

    #ifdef EP2_INTERNAL
        void *memcpy(void *, const void *, size_t);
    #else
        #define memcpy(dst, src, sz) __rt_memcpy((void *)dst, (void *)src, (size_t)sz)
    #endif

    // Write selected byte to memory block
    void *__rt_memset(void *, int, size_t);

    #ifdef EP2_INTERNAL
        void *memset(void *, int, size_t);
    #else
        #define memset(m, byte, sz) __rt_memset((void *)m, (int)byte, (size_t)sz)
    #endif

    void *__rt_memmove(void *, const void *, size_t);

    #ifdef EP2_INTERNAL
        void *memmove(void *, const void *, size_t);
    #else
        #define memmove(dst, src, sz) __rt_memmove((void *)dst, (void *)src, (size_t)sz)
    #endif

    // JVM RAM allocator
    void *AmMemAlloc(size_t size);

    void AmMemFree(void *ptr);

    /* Better, them su*Mem, but slow;
     * for big size of memory blocks use su*Mem, for small - uis*Mem;
     * more memory avaliable;
     * after allocating clear memory, because is slow;
     * if is failed no rebooted
     */
    void *device_Alloc_mem(UINT32 count, size_t sz);

    void device_Free_mem_fn(void *ptr);

    typedef UINT32 UIS_PARTITION_BLOCK_SIZE_T;
    typedef INT32 UIS_ALLOCATION_ERROR_T;      // 0 - OK, else - ERROR

    void *uisAllocateMemory(UIS_PARTITION_BLOCK_SIZE_T nbytes, UIS_ALLOCATION_ERROR_T *status);

    void uisFreeMemory(void *address);

    void *uisReAllocMemory(
        void                       *address,
        UIS_PARTITION_BLOCK_SIZE_T new_size,
        UIS_ALLOCATION_ERROR_T     *status
    );

    /* EXL, 24-Apr-2023:
     * Functions, that used JVM for RAM allocating in Java Heap (800 KB at default)
     * if device support CORElet's, functions works at once,
     * else before using needed run any J2ME-application and suspend this
     */
    void *AmMemAllocPointer(int size);

    void AmMemFreePointer(void *ptr);

#ifdef __cplusplus
}
#endif

#endif // SDK_MEMORY_H

/* EOF */