/*******************************************************************************
  EtherCAT demo main

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    Contains the functional implementation of main file of EtherCAT demo.

  Description:
    This file contains the functional implementation of main file of EtherCAT demo.
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
/* Standard Includes */
#include <stdint.h>                 /* For uint32_t definition */
#include <stdbool.h>                /* For true/false definition */

/* PIC32 related includes */
#include <plib.h>                   /* Include to use PIC32 peripheral libraries */
#ifdef __XC32
    #include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#endif

#include <plib.h>           /* Include to use PIC32 peripheral libraries      */
#include <stdint.h>         /* For uint32_t definition                        */
#include <stdbool.h>        /* For true/false definition                      */

#include "system.h"         /* System funct/params, like osc/periph config    */
#include "user.h"           /* User funct/params, such as InitApp             */

#include "SPIDriver/SPIDriver.h"

#include "Common/UserDataTypes.h"
#include "Common/ErrorCodes.h"
#include "MemoryManager/MemoryManager.h"
#include "Scheduler.h"

/**
\addtogroup 9252_PIC32appl EL9800 application
@{
*/

/**
\file 9252_PIC32appl.c
\author EthercatSSC@beckhoff.com
\brief Implementation

\version 5.10

<br>Changes to version V5.01:<br>
V5.10 ECAT6: Add "USE_DEFAULT_MAIN" to enable or disable the main function<br>
<br>Changes to version V5.0:<br>
V5.01 EL9800 2: Add TxPdo Parameter object 0x1802<br>
<br>Changes to version V4.30:<br>
V4.50 ECAT2: Create generic application interface functions. Documentation in Application Note ET9300.<br>
V4.50 COE2: Handle invalid PDO assign values.<br>
V4.30 : create file
*/


/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include "ecat_def.h"
#include "ecatslv.h"
#include "ecatappl.h"
#include "objdef.h"
#include "9252_HW.h"
#include "SPIDriver/SPIDriver.h"
#define _EVALBOARD_
//TODO:    #include "cia402appl.h"
    #include "pic32_mchp_gpio_sample_app.h"
#undef _EVALBOARD_


#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

/* i.e. uint32_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

/*ECA*/



int32_t main(void)
{
    UINT pbclk;
   
#ifndef PIC32_STARTER_KIT
    /*The JTAG is on by default on POR.  A PIC32 Starter Kit uses the JTAG, but
    for other debug tool use, like ICD 3 and Real ICE, the JTAG should be off
    to free up the JTAG I/O */
    DDPCONbits.JTAGEN = 0;
#endif

    /*Refer to the C32 peripheral library documentation for more
    information on the SYTEMConfig function.
    
    This function sets the PB divider, the Flash Wait States, and the DRM
    /wait states to the optimum value.  It also enables the cacheability for
    the K0 segment.  It could has side effects of possibly alter the pre-fetch
    buffer and cache.  It sets the RAM wait states to 0.  Other than
    the SYS_FREQ, this takes these parameters.  The top 3 may be '|'ed
    together:
    
    SYS_CFG_WAIT_STATES (configures flash wait states from system clock)
    SYS_CFG_PB_BUS (configures the PB bus from the system clock)
    SYS_CFG_PCACHE (configures the pCache if used)
    SYS_CFG_ALL (configures the flash wait states, PB bus, and pCache)*/

    /* TODO Add user clock/system configuration code if appropriate.  */
    pbclk = SYSTEMConfig(SYS_FREQ, SYS_CFG_ALL);
  //  InitI2C(pbclk);
    /*Configure Multivector Interrupt Mode.  Using Single Vector Mode
    is expensive SPI1BUFfrom a timing perspective, so most applications
    should probably not use a Single Vector Mode*/

    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);


    /* <INSERT USER APPLICATION CODE HERE> */
    SPIOpen();
    /* initialize the Hardware and the EtherCAT Slave Controller */
    HW_Init();

    INTEnableInterrupts();
    MainInit();

    /*Initialize Axes structures*/
//TODO:    CiA402_Init();

    /*Create basic mapping*/
    APPL_GenerateMapping(&nPdInputSize,&nPdOutputSize);

    bRunApplication = TRUE;
    do
    {
        MainLoop();

    } while (bRunApplication == TRUE);

//TODO:    CiA402_DeallocateAxis();

    HW_Release();

    return 0;
}
