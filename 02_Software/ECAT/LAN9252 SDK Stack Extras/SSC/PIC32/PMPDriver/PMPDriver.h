/*******************************************************************************
 PIC32 Host Bus Interface Driver

  Company:
    Microchip Technology Inc.

  File Name:
    PMPDriver.h

  Summary:
    Contains the Header File of PIC32 Host Bus Interface Driver

  Description:
    This file contains the Header File of PIC32 Host Bus Interface Driver

  Change History:
    Version		Changes
	0.1			Initial version.
	0.2			-
	0.3			-	
	0.4 		-
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

#include "plib.h"

#ifndef PMPDRIVER_H
#define	PMPDRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum {INDEXED_8BIT, INDEXED_16BIT, MDP_8BIT, MDP_16BIT, MSP_8BIT, MSP_16BIT} PMPMode;
    
    typedef union
    {
        struct
        {
            UINT8 RDWR:1;
            UINT8 WRENB:1;
            UINT8 ALE:1;
            UINT8 CS:1;
            UINT8 ALE_QUAL:1;
        };
        
        UINT8 Val;
        
    } Polarity;
    
    typedef enum {LGY, ESM, MM2, MM1} RWType;

    #define PMPWaitForNoBusy() {while (PMMODEbits.BUSY);}

    /*Define HBI_MODE - Valid values are INDEXED_8BIT, INDEXED_16BIT, MDP_8BIT, MDP_16BIT, MSP_8BIT, MSP_16BIT*/
   

#ifdef HBI_INDEXED_8BIT
    #define HBI_MODE INDEXED_8BIT
    #define HBI_INDEXED_MODE
#elif HBI_INDEXED_16BIT
    #define HBI_MODE INDEXED_16BIT
    #define HBI_INDEXED_MODE
#elif HBI_MDP_8BIT
    #define HBI_MODE MDP_8BIT
#elif HBI_MDP_16BIT
    #define HBI_MODE MDP_16BIT
#elif HBI_MSP_8BIT
    #define HBI_MODE MSP_8BIT
#elif HBI_MSP_16BIT
    #define HBI_MODE MSP_16BIT
#else
    #error "Set one of the HBI modes in project setting"
#endif

    void    PMPOpen         (PMPMode pmpmode, RWType rwtype, Polarity pl);
    void    PMPReadByte     (UINT16 Address, UINT8 *Buffer, UINT16 Count);
    void    PMPWriteByte    (UINT16 Address, UINT8 *Buffer, UINT16 Count);
    void    PMPReadWord     (UINT16 Address, UINT16 *Buffer, UINT16 Count);
    void    PMPWriteWord    (UINT16 Address, UINT16 *Buffer, UINT16 Count);
    void    PMPWriteWord    (UINT16 Address, UINT16 *Buffer, UINT16 Count);
    UINT32  PMPReadDWord    (UINT16 Address);
    void PMPReadDRegister(UINT8 *ReadBuffer, UINT16 Address, UINT8 Count);
    void PMPWriteRegister( UINT8 *WriteBuffer, UINT16 Address, UINT8 Count);
    void PMPReadPDRamRegister(UINT8 *ReadBuffer, UINT16 Address, UINT16 Count);
    void PMPWritePDRamRegister(UINT8 *WriteBuffer, UINT16 Address, UINT16 Count);
    
#ifdef	__cplusplus
}
#endif

#endif	/* PMPDRIVER_H */

