/*******************************************************************************
  EtherCAT demo interrupts

  Company:
    Microchip Technology Inc.

  File Name:
    interrupts.c

  Summary:
    Contains the functional implementation of interrupt file of EtherCAT demo.

  Description:
    This file contains the functional implementation of ISR file of EtherCAT demo.
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
#ifdef __XC32
    #include <xc.h>          /* Defines special funciton registers, CP0 regs  */
#endif

#include <plib.h>            /* Include to use PIC32 peripheral libraries     */
#include <sys/attribs.h>     /* For __ISR definition                          */
#include <stdint.h>          /* For uint32_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */
#include "system.h"
#include "Common/SystemCSR.h"
#include "PMPDriver/PMPDriver.h"

/******************************************************************************/
/* Interrupt Vector Options                                                   */
/******************************************************************************/
/*                                                                            */
/* VECTOR NAMES:                                                              */
/*                                                                            */
/* _CORE_TIMER_VECTOR          _COMPARATOR_2_VECTOR                           */
/* _CORE_SOFTWARE_0_VECTOR     _UART_2A_VECTOR                                */
/* _CORE_SOFTWARE_1_VECTOR     _I2C_2A_VECTOR                                 */
/* _EXTERNAL_0_VECTOR          _SPI_2_VECTOR                                  */
/* _TIMER_1_VECTOR             _SPI_2A_VECTOR                                 */
/* _INPUT_CAPTURE_1_VECTOR     _I2C_4_VECTOR                                  */
/* _OUTPUT_COMPARE_1_VECTOR    _UART_3_VECTOR                                 */
/* _EXTERNAL_1_VECTOR          _UART_2_VECTOR                                 */
/* _TIMER_2_VECTOR             _SPI_3A_VECTOR                                 */
/* _INPUT_CAPTURE_2_VECTOR     _I2C_3A_VECTOR                                 */
/* _OUTPUT_COMPARE_2_VECTOR    _UART_3A_VECTOR                                */
/* _EXTERNAL_2_VECTOR          _SPI_4_VECTOR                                  */
/* _TIMER_3_VECTOR             _I2C_5_VECTOR                                  */
/* _INPUT_CAPTURE_3_VECTOR     _I2C_2_VECTOR                                  */
/* _OUTPUT_COMPARE_3_VECTOR    _FAIL_SAFE_MONITOR_VECTOR                      */
/* _EXTERNAL_3_VECTOR          _RTCC_VECTOR                                   */
/* _TIMER_4_VECTOR             _DMA_0_VECTOR                                  */
/* _INPUT_CAPTURE_4_VECTOR     _DMA_1_VECTOR                                  */
/* _OUTPUT_COMPARE_4_VECTOR    _DMA_2_VECTOR                                  */
/* _EXTERNAL_4_VECTOR          _DMA_3_VECTOR                                  */
/* _TIMER_5_VECTOR             _DMA_4_VECTOR                                  */
/* _INPUT_CAPTURE_5_VECTOR     _DMA_5_VECTOR                                  */
/* _OUTPUT_COMPARE_5_VECTOR    _DMA_6_VECTOR                                  */
/* _SPI_1_VECTOR               _DMA_7_VECTOR                                  */
/* _I2C_3_VECTOR               _FCE_VECTOR                                    */
/* _UART_1A_VECTOR             _USB_1_VECTOR                                  */
/* _UART_1_VECTOR              _CAN_1_VECTOR                                  */
/* _SPI_1A_VECTOR              _CAN_2_VECTOR                                  */
/* _I2C_1A_VECTOR              _ETH_VECTOR                                    */
/* _SPI_3_VECTOR               _UART_4_VECTOR                                 */
/* _I2C_1_VECTOR               _UART_1B_VECTOR                                */
/* _CHANGE_NOTICE_VECTOR       _UART_6_VECTOR                                 */
/* _ADC_VECTOR                 _UART_2B_VECTOR                                */
/* _PMP_VECTOR                 _UART_5_VECTOR                                 */
/* _COMPARATOR_1_VECTOR        _UART_3B_VECTOR                                */
/*                                                                            */
/* Refer to the device specific .h file in the C32 Compiler                   */
/* pic32mx\include\proc directory for a complete Vector and IRQ mnemonic      */
/* listings for the PIC32 device.                                             */
/*                                                                            */
/* PRIORITY OPTIONS:                                                          */
/*                                                                            */
/* (default) IPL0AUTO, IPL1, IPL2, ... IPL7 (highest)                         */
/*                                                                            */
/* Example Shorthand Syntax                                                   */
/*                                                                            */
/* void __ISR(<Vector Name>,<PRIORITY>) user_interrupt_routine_name(void)     */
/* {                                                                          */
/*     <Clear Interrupt Flag>                                                 */
/* }                                                                          */
/*                                                                            */
/* For more interrupt macro examples refer to the C compiler User Guide in    */
/* the C compiler /doc directory.                                             */
/*                                                                            */
/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* TODO: check interrupt priorities */

void __ISR(_CORE_TIMER_VECTOR, ipl2) CoreTimerHandler(void)
{
    tenMSTicker++;
    
    /* Clear the interrupt flag */
    //INTClearFlag(INT_CT);

    /* Update the period */
    UpdateCoreTimer(CORE_TICK_RATE);
}
