/*******************************************************************************
 PIC32 Memory Management

  Company:
    Microchip Technology Inc.

  File Name:
    MemoryManager.h

  Summary:
    Contains the PIC32 Memory Management

  Description:
    This file contains the PIC32 Memory Management
*******************************************************************************/

/*******************************************************************************
Copyright (c) 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/


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

