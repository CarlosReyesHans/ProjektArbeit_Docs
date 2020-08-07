/* 
 * File:   ErrorCodes.h
 * Author: kthiagarajan
 *
 * Created on May 20, 2013, 8:47 PM
 */

#ifndef ERRORCODES_H
#define	ERRORCODES_H

#ifdef	__cplusplus
extern "C" {
#endif

    /* generic error codes */
#define     NO_ERROR            (0x00)
#define     TIMED_OUT           (0x01)
#define     HEAP_SHORTAGE       (0x03)

    /* FIFO related error codes */
#define     TX_FIFO_SHORTAGE    (0xF0)


#ifdef	__cplusplus
}
#endif

#endif	/* ERRORCODES_H */

