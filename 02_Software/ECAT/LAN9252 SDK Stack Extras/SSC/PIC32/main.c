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
    #include <xc.h>                 /* Defines special funciton registers, CP0 regs */
#endif

/* Application related includes */
#include "system.h"                 /* System funct/params, like osc/periph config */
#include "user.h"                   /* User funct/params, such as InitApp */
#include "PMPDriver/PMPDriver.h"
#include "Common/UserDataTypes.h"
#include "Common/ErrorCodes.h"
#include "MemoryManager/MemoryManager.h"
#include "Scheduler.h"


/* EtherCAT Slave Stack related includes */
#include "ecat_def.h"
#include "ecatslv.h"
#include "ecatappl.h"
#include "objdef.h"
#include "9252_HW.h"
#define _EVALBOARD_
//TODO:    #include "cia402appl.h"
    #include "pic32_mchp_gpio_sample_app.h"
#undef _EVALBOARD_

// *****************************************************************************
// *****************************************************************************
// Section: Configuration Bit Settings
// *****************************************************************************
// *****************************************************************************
#pragma config FSOSCEN = OFF    /* Disable secondary oscillator */
#pragma config FWDTEN = OFF     /* Disable watchdog timer */
#pragma config POSCMOD=HS       /* High speed crystal mode */
#pragma config FNOSC=PRIPLL     /* Use Primary Oscillator with PLL (XT, HS, or EC) */
#pragma config FPLLIDIV=DIV_2   /* Divide 8MHz to between 4-5MHz before PLL (now 4MHz) */
#pragma config FPLLMUL=MUL_20   /* Multiply with PLL (now 80MHz) */
#pragma config FPLLODIV=DIV_1   /* Divide After PLL (now 80 MHz) */
#pragma config FPBDIV = DIV_4   /* pheripheral clock = sys clk */

extern BOOL bEscInterrupt;
extern BOOL bSync0Interrupt;
extern BOOL bSync1Interrupt;
extern BOOL bTimer5Interrupt;

unsigned int counter_int_occ  =0;
int32_t main(void)
{
    UINT pbclk, value;
    Polarity pl = {0};
    
#ifndef PIC32_STARTER_KIT
    /**********************************************************
     * The JTAG is on by default on POR.  A PIC32 Starter Kit uses the JTAG, but
     * for other debug tool use, like ICD 3 and Real ICE, the JTAG should be off
     * to free up the JTAG I/O
     ***********************************************************/
    DDPCONbits.JTAGEN = 0;
#endif
    
    value = SYSTEMConfigWaitStatesAndPB( SYS_FREQ );

    /* Enable the cache for the best performance */
    CheKseg0CacheOn();

    INTEnableSystemMultiVectoredInt();

    value = OSCCON;
    
    while (!(value & 0x00000020))
    {
            value = OSCCON;    /* Wait for PLL lock to stabilize */
    }

    pbclk = SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

    /**********************************************************
     * Refer to the C32 peripheral library documentation for more
     * information on the SYTEMConfig function.
     *
     * This function sets the PB divider, the Flash Wait States, and the DRM
     * wait states to the optimum value.  It also enables the cacheability for
     * the K0 segment.  It could has side effects of possibly alter the pre-fetch
     * buffer and cache.  It sets the RAM wait states to 0.  Other than
     * the SYS_FREQ, this takes these parameters.  The top 3 may be '|'ed
     * together:
     ***********************************************************/    
//    SYS_CFG_WAIT_STATES (configures flash wait states from system clock)
//    SYS_CFG_PB_BUS (configures the PB bus from the system clock)
//    SYS_CFG_PCACHE (configures the pCache if used)
//    SYS_CFG_ALL (configures the flash wait states, PB bus, and pCache)

    /* TODO Add user clock/system configuration code if appropriate.  */
//    pbclk = SYSTEMConfig(SYS_FREQ, SYS_CFG_ALL);
//    InitI2C(pbclk);
    
    /**********************************************************
     * Configure Multivector Interrupt Mode.  Using Single Vector Mode
     * is expensive from a timing perspective, so most applications
     * should probably not use a Single Vector Mode
     ***********************************************************/    
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);

    INTDisableInterrupts();
    /* PMP port is kept open throught the session */
    pl.ALE_QUAL = pl.ALE = 1;

    /* TODO - Make it support all modes */
    PMPOpen(HBI_MODE, MM2, pl); 

    /* Initialize I/O and Peripherals for application */
    InitApp();

    InitMemoryManager();

    /* <INSERT USER APPLICATION CODE HERE> */

    /* Initialize the Hardware and the EtherCAT Slave Controller */
    HW_Init();

    INTEnableInterrupts();
    
    MainInit();

    /*Initialize Axes structures*/
//TODO:    CiA402_Init();

    /*Create basic mapping*/
   APPL_GenerateMapping(&nPdInputSize,&nPdOutputSize);

    bRunApplication = TRUE;
	
	/*Configure the GPIO*/
    /*RD3 Input*/
    /*RD2 Output*/
    TRISD = 0x08;
    LATD = 0x00;
    do
    {
        MainLoop();


    } while (bRunApplication == TRUE);

//TODO:    CiA402_DeallocateAxis();

    HW_Release();

    return 0;
}
