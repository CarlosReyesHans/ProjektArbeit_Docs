/* 
 * File:   Scheduler.h
 * Author: kthiagarajan
 *
 * Created on June 7, 2013, 12:57 PM
 *
 * This manages the co-operative scheduling of the tasks.
 */

#ifndef SCHEDULER_H
#define	SCHEDULER_H

#include "Common/UserDataTypes.h"

#ifdef	__cplusplus
extern "C" {
#endif

    UINT8 GetNextTaskIndex();
    
    typedef struct
    {
        char Taskname[10];
        void (*Run)(void);
        
    } TaskStore;

    void Scheduler();
    
#ifdef	__cplusplus
}
#endif

#endif	/* SCHEDULER_H */

