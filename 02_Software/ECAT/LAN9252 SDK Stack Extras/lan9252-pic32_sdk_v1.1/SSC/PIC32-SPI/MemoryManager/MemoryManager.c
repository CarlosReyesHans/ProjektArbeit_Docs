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
