#include "Scheduler.h"
#include "MemoryManager/MemoryManager.h"

#define NO_OF_TASKS 2

UINT8 LastTaskIndex = 0xFF;

TaskStore Tasks[NO_OF_TASKS] = {
                               // {"TM", RunTestManager},
                                {"MC", RunMemoryCleaner}
                               };

UINT8 GetNextTaskIndex()
{
    if (LastTaskIndex == (NO_OF_TASKS - 1))
        LastTaskIndex = 0xFF;
    
    return ++LastTaskIndex;

}

void Scheduler()
{
    UINT8 idx;
    
    for (;;)
    {
        idx = GetNextTaskIndex();
        Tasks[idx].Run();
    }
}