/*******************************************************************************
 PIC32 Memory Management

  Company:
    Microchip Technology Inc.

  File Name:
    MemoryManager.c

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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "MemoryManager.h"
#include <stdlib.h>

Memory_Header MemoryHeaders[NO_OF_MEMORY_HEADERS];

void InitMemoryManager()
{
    int i;
    for(i = 0; i < NO_OF_MEMORY_HEADERS; i++)
    {
        MemoryHeaders[i].Memory = NULL;
        MemoryHeaders[i].Memory_16 = NULL;
        MemoryHeaders[i].Memory_32 = NULL;
        MemoryHeaders[i].Allocated = FALSE;
        MemoryHeaders[i].Free = TRUE;
        MemoryHeaders[i].Count = 0;
    }
}

void RunMemoryCleaner()
{
    int i;
    for(i = 0; i < NO_OF_MEMORY_HEADERS; i++)
    {
        if ((MemoryHeaders[i].Allocated == TRUE) && (MemoryHeaders[i].Free == TRUE))
        {
            myfree(&MemoryHeaders[i]);
        }
    }
}

void myfree(Memory_Header* mh)
{
    if ((mh != NULL) && (mh->Memory != NULL))
    {
        free(mh->Memory);
        mh->Allocated = FALSE;
        mh->Free = TRUE;
        mh->Count = 0;
        mh->Memory = NULL;
        mh->Memory_16 = NULL;
        mh->Memory_32 = NULL;
    }
}

Memory_Header* mymalloc(UINT16 Size)
{
    int i;
    Memory_Header *ptr = 0;

    for(i = 0; i < NO_OF_MEMORY_HEADERS; i++)
    {
        if (MemoryHeaders[i].Free && (MemoryHeaders[i].Allocated == FALSE))
        {
            ptr = &(MemoryHeaders[i]);
            MemoryHeaders[i].Memory = (UINT8 *)malloc(Size);
            MemoryHeaders[i].Memory_16 = (UINT16 *)MemoryHeaders[i].Memory;
            MemoryHeaders[i].Memory_32 = (UINT32 *)MemoryHeaders[i].Memory;
            MemoryHeaders[i].Allocated = TRUE;
            MemoryHeaders[i].Free = FALSE;
            MemoryHeaders[i].Count = Size;
            break;
        }
    }

    return ptr;
}
