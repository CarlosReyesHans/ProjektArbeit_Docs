/*******************************************************************************
 LAN9252 Hardware Abtraction Layer - Implementation file

  Company:
    Microchip Technology Inc.

  File Name:
    PICHW.c

  Description:
    This file  cContains the functional implementation of PIC32 Hardware Abtraction Layer
	
  Change History:
    Version		Changes
	1.3			Initial version.
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

///////////////////////////////////////////////////////////////////////////////
// Included files


#include "9252_HW.h"
#include <sys/attribs.h>     /* For __ISR definition   */
#include "peripheral/pps.h" 
#include "peripheral/ports.h" 
#include <peripheral/timer.h>

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */
///////////////////////////////////////////////////////////////////////////////
// Global Interrupt setting
#ifndef PICTAIL_BOARD
    ///////////////////////////////////////////////////////////////////////////////
    // ESC Interrupt
    //0 - falling edge 1- raising edge
    #define    INIT_ESC_INT             ConfigINT0(EXT_INT_PRI_7 | FALLING_EDGE_INT | EXT_INT_ENABLE);
    #define    ESC_INT_REQ              (IFS0bits.INT0IF) //ESC Interrupt (INT0) state/flag
    #define    INT_EL                   (_RD0) //ESC Interrupt input port
    #define    EscIsr                   (_INT0Interrupt) // primary interrupt vector name
    #define    ACK_ESC_INT              {(ESC_INT_REQ)=0;}

    #define IS_ESC_INT_ACTIVE           ((INT_EL) == 0) //0 - fro active low; 1 for hactive high
    #define IRQ_INTERRUPT_VECTOR 		_EXTERNAL_0_VECTOR

#else //For PICTAIL board
    //////////////////////////////////////////////////////////////////////////////
    // ESC Interrupt
    //0 - falling edge 1- rising edge
    #define    INIT_ESC_INT           {(INTCONbits.INT4EP) = 0;(IPC4bits.INT4IP) = 7;} 
    #define    ESC_INT_REQ            (IFS0bits.INT4IF) //ESC Interrupt (INT4) state/flag
    #define    INT_EL                 (_RA15) //ESC Interrupt input port
    #define    EscIsr                 (_INT4Interrupt) // primary interrupt vector name
    #define    ACK_ESC_INT            {(ESC_INT_REQ)=0;}

    #define IS_ESC_INT_ACTIVE         ((INT_EL) == 0) //0 - fro active low; 1 for hactive high
    #define IRQ_INTERRUPT_VECTOR      _EXTERNAL_4_VECTOR
#endif


///////////////////////////////////////////////////////////////////////////////
// SYNC0 Interrupt


    #define    INIT_SYNC0_INT                  {(INTCONbits.INT1EP) = 0;(IPC1bits.INT1IP) = 5;}  
    #define    SYNC0_INT_REQ                   (IFS0bits.INT1IF) //(_INT3IF) //Sync0 Interrupt (INT1) state
    #define    INT_SYNC0                       (_RE8) //Sync1 Interrupt input port
    #define    Sync0Isr                        (_INT1Interrupt) // primary interrupt vector name
    #define    DISABLE_SYNC0_INT               {IEC0bits.INT1IE=0;}//{(_INT1IE)=0;}//disable interrupt source INT1
    #define    ENABLE_SYNC0_INT                {IEC0bits.INT1IE=1;} //enable interrupt source INT1
    #define    ACK_SYNC0_INT                   {(SYNC0_INT_REQ) = 0;}
    #define    SET_SYNC0_INT                   {(SYNC0_INT_REQ) = 1;}
    #define    SYNC0_INT_PORT_IS_ACTIVE        {(INT_EL) == 0;}
    #define    IS_SYNC0_INT_ACTIVE              ((INT_SYNC0) == 0) //0 - fro active low; 1 for hactive high

    #define    INIT_SYNC1_INT                   {(INTCONbits.INT2EP) = 0;(IPC2bits.INT2IP) = 4;}
    #define    SYNC1_INT_REQ                    (IFS0bits.INT2IF) //(_INT4IF) //Sync1 Interrupt (INT2) state
    #define    INT_SYNC1                        (_RE9) //Sync1 Interrupt input port
    #define    Sync1Isr                         (_INT2Interrupt) // primary interrupt vector name
    #define    DISABLE_SYNC1_INT                {IEC0bits.INT2IE=0;}//disable interrupt source INT2
    #define    ENABLE_SYNC1_INT                 {IEC0bits.INT2IE=1;} //enable interrupt source INT2
    #define    ACK_SYNC1_INT                    {(SYNC1_INT_REQ) = 0;}
    #define    SET_SYNC1_INT                    {(SYNC1_INT_REQ) = 1;}
    #define    SYNC1_INT_PORT_IS_ACTIVE         {(INT_EL) == 0;}
    #define    IS_SYNC1_INT_ACTIVE              ((INT_SYNC1) == 0) //0 - fro active low; 1 for hactive high


///////////////////////////////////////////////////////////////////////////////
// Hardware timer

#define STOP_ECAT_TIMER         {(T5CONbits.TON) = 0; /*disable timer*/}
#define INIT_ECAT_TIMER         { OpenTimer5(T5_ON | T5_IDLE_CON | T5_PS_1_256 | T5_SOURCE_INT,  ECAT_TIMER_INC_P_MS);\
                                   STOP_ECAT_TIMER\
                                   (TMR5) = 0;/*clear timer register*/ }

#define START_ECAT_TIMER         {(T5CONbits.TON) = 1; /*enable timer*/ }


/*-----------------------------------------------------------------------------------------
------
------    LED defines
------
-----------------------------------------------------------------------------------------*/

#define LED_ECATRED                    LATDbits.LATD1

/*  A brief description of a section can be given directly below the section
    banner.
 */


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

void PDI_Restore_Global_Interrupt(UINT32 Int_sts)
{
    INTRestoreInterrupts(Int_sts);
}

/*******************************************************************************
  Function:
     void PDI_Enable_Global_interrupt()

  Summary:
    Enables the platform to handle interrupts.

  Description:
    This routine enables the core to handle any pending interrupt requests.

  Precondition:
    Need to configure system using interrupt (IRQ, SYNC0 and SYNC1- if they are using)
 *****************************************************************************/
void PDI_Enable_Global_interrupt()
{
    INTEnableInterrupts();
}

/*******************************************************************************
  Function:
    UINT32 PDI_Disable_Global_Interrupt()

  Summary:
    Disables the platform from handling interrupts.

  Description:
    This routine disables the core from handling any pending interrupt requests.

  Returns:
    The previous state of the interrupt Status.  The PDI_Restore_Global_Interrupt
    function can be used in other routines to restore the system interrupt state.

  Example:
    <code>
    unsigned int intStatus;

    intStatus = PDI_Disable_Global_Interrupt();
    </code>

*****************************************************************************/
UINT32 PDI_Disable_Global_Interrupt()
{
    return(INTDisableInterrupts());
}

/*******************************************************************************
  Function:
    UINT16 PDI_GetTimer(void)

  Summary:
    Get the 1ms current timer value
  Description:
    This routine gets the 1ms current timer value.
*****************************************************************************/
UINT16 PDI_GetTimer()
{
    return(TMR5);
}

/*******************************************************************************
  Function:
    void PDI_ClearTimer(void)

  Summary:
    Clear the 1ms current timer value
  Description:
    This routine clears the 1ms current timer value.
*****************************************************************************/
void PDI_ClearTimer()
{
    TMR5 = 0;
}

/*******************************************************************************
  Function:
  void PDI_Timer_Interrupt(void)

  Summary:
   This function configure and enable the TIMER interrupt for 1ms
        
  Description:
  This function configure and enable the TIMER interrupt for 1ms
*****************************************************************************/
void PDI_Timer_Interrupt()
{
    INIT_ECAT_TIMER;
    ConfigIntTimer5(T5_INT_ON | T5_INT_PRIOR_3 );
    START_ECAT_TIMER;
}
/*******************************************************************************
  Function:
  void PDI_IRQ_Interrupt(void)

  Summary:
   This function configure and enable the interrupt for IRQ
        
  Description:
  This function configure and enable the interrupt for IRQ
*****************************************************************************/
void PDI_IRQ_Interrupt()
{
    INIT_ESC_INT;
}
/*******************************************************************************
  Function:
    void PDI_Init_SYNC_Interrupts(void)

  Summary:
    The function configure and enable SYNC0 and SYNC1 interrupt.
        
  Description:
	The function configure and enable SYNC0 and SYNC1 interrupt. It is platform dependent. INIT_SYNCx_INT is a macro which will configure the external interrupt and ENABLE_SYNCx_INT macro for enabling interrupt for the particular lines.
  *****************************************************************************/

void PDI_Init_SYNC_Interrupts()
{
    INIT_SYNC0_INT
    INIT_SYNC1_INT

    ENABLE_SYNC0_INT;
    ENABLE_SYNC1_INT;
}


/*******************************************************************************
  Function:
  void HW_SetLed(UINT8 RunLed,UINT8 ErrLed)

  Summary:
   This function set the Error LED if it is required.
        
  Description:
  LAN9252 does not support error LED. So this feature has to be enabled by PDI SOC if it is needed.

 Parameters:
 RunLed  - It is not used. This will be set by LAN9252.    
 ErrLed      -  1- ON, 0-0FF.
  *****************************************************************************/
void HW_SetLed(UINT8 RunLed,UINT8 ErrLed)
{
    /* Here RunLed is not used. Because on chip supported RUN Led is available*/    
    LED_ECATRED   = ErrLed;
}


/*******************************************************************************
  Function:
    void __ISR(_EXTERNAL_0_VECTOR, ipl7srs) ExtInterruptHandler(void)

  Summary:
    Interrupt service routine for the PDI interrupt from the EtherCAT Slave Controller

  *****************************************************************************/

void __ISR(IRQ_INTERRUPT_VECTOR, IPL7AUTO) ExtInterruptHandler(void)
{
   DISABLE_ESC_INT();

   PDI_Isr();

   /* reset the interrupt flag */
   ACK_ESC_INT;
   ENABLE_ESC_INT();
}


#ifdef DC_SUPPORTED
/*******************************************************************************
  Function:
    void __ISR(_EXTERNAL_1_VECTOR, ipl5) Sync0Isr(void)

  Summary:
    Interrupt service routine for the interrupts from SYNC0
  *****************************************************************************/

void __ISR(_EXTERNAL_1_VECTOR, IPL5AUTO) Sync0Isr(void)
{
    
    DISABLE_ESC_INT()
    
   Sync0_Isr();
   
   /* reset the interrupt flag */
   ACK_SYNC0_INT;
   ENABLE_ESC_INT();
}


/*******************************************************************************
  Function:
    void __ISR(_EXTERNAL_2_VECTOR, ipl4) Sync1Isr(void)


  Summary:
    Interrupt service routine for the interrupts from SYNC1
  *****************************************************************************/

void __ISR(_EXTERNAL_2_VECTOR, IPL4AUTO) Sync1Isr(void)
{

    DISABLE_ESC_INT();
    Sync1_Isr();

     /* reset the interrupt flag */
    ACK_SYNC1_INT;

    ENABLE_ESC_INT();

}
#endif //DC_SUPPORTED

/*******************************************************************************
  Function:
    void __ISR(_TIMER_5_VECTOR,IPL3AUTO) _TIMER5_HANDLER(void)


  Summary:
    Interrupt service routine for the interrupts from TIMER5
  *****************************************************************************/

void __ISR(_TIMER_5_VECTOR,IPL3AUTO) _TIMER5_HANDLER(void)
{
   ECAT_CheckTimer();
   mT5ClearIntFlag(); //clear flag
}


/* *****************************************************************************
 End of File
 */
