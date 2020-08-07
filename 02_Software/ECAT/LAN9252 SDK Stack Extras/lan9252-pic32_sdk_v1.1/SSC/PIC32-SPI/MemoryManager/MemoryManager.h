/* 
 * File:   MemoryManager.h
 * Author: I21417
 *
 * Created on July 11, 2013, 2:05 PM
 */

#ifndef MEMORYMANAGER_H
#define	MEMORYMANAGER_H

#include <GenericTypeDefs.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 *          Free        Allocated       Description
 *          false       false           Not possible
 *          false       true            contains valid data, awaiting to be used
 *          true        false           buffer pointer is available for use (allocation needed)
 *          true        true            contains expired data, needs deallocation
 */
    typedef struct
    {
        BOOL Free;
        BOOL Allocated;
        UINT8 *Memory;
        UINT16 *Memory_16;
        UINT32 *Memory_32;
        UINT16 Count;

    } Memory_Header;

#define NO_OF_MEMORY_HEADERS 10

    void InitMemoryManager();
    Memory_Header* mymalloc(UINT16 Size);
    void RunMemoryCleaner();
    void myfree(Memory_Header* mh);


#ifdef	__cplusplus
}
#endif

#endif	/* MEMORYMANAGER_H */

