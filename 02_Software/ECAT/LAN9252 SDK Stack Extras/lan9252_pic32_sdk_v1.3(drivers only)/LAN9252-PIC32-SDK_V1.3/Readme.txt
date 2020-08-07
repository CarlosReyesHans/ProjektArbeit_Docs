/*******************************************************************************
 Copyright (c) 2015 released Microchip Technology Inc.  All rights reserved.

 Microchip licenses to you the right to use, modify, copy and distribute
 Software only when embedded on a Microchip microcontroller or digital signal
 controller that is integrated into your product or third party product
 (pursuant to the sublicense terms in the accompanying license agreement).

 You should refer to the license agreement accompanying this Software for
 additional information regarding your rights and obligations.

 SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
 MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
 IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
 CONTRACT, NEGLiPMPCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
 OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
 INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
 CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
 SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
 (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
 
This ReadMe file explains the LAN9252-PIC32 SDK folder structure.

This sample SDK source requires Slave Stack Code 5.11 from EtherCAT.org to work.
Please refer to the Application note "Integrating Microchip's LAN9252 SDK with Beckhoff's EtherCAT® SSC" for 
integrating the LAN9252 SDK with the EtherCAT® Slave stack code from Beckhoff.

Project directory structure:
============================

LAN9252-PIC32-SDK ---> (Main folder)
	|
	|
	|--->9252_HW.c
	|
	|--->9252_HW.h
	|
	|	|--->SPIDriver:
	|	|
	|	|--->SPIDriver.c
	|	|
	|	|--->SPIDriver.h
	|	|
	|	|--->PIC32MX795F512L: (Platform(SOC) and EVB Specifc files)
	|	|
	|	|	|--->PIC32SPIDriver.c
	|	|
	|	|	|--->PIC32SPIDriver.h
	|	|
	|--->PMPDriver:
	|	|
	|	|--->PMPDriver.c
	|	|
	|	|--->PMPDriver.h
	|	|
	|	|--->PIC32MX795F512L: (Platform(SOC) and EVB Specifc files)
	|	|
	|	|	|--->PIC32PMPDriver.c
	|	|	|
	|	|	|--->PIC32PMPDriver.h
	|	|
	|	|--->Microchip_LAN9252_SSC_Config.xml
	|	|
	|--->PIC32MX795F512L: (Platform(SOC) and EVB Specifc files)
	|	|
	|	|--->PICHW.c
	|	|
	|--->Readme.txt
	
File description:
===============
9252_HW.c and .h- This is the interface to hardware abstraction layer. This is platform independent.
These files require generating SSC code using "Microchip_LAN9252_SSC_Config.xml"

-----------------------------------------------------------------------------------
===============
SPI Driver: 
===============
SPIDriver.c and .h - This file has the SPI routines to access LAN9252. It is platform independent.
-----------------------------------------------------------------------------------

===============
PIC32SPIDriver - This folder is specific to SPI module of PIC32MX795F512L. If another variant of PIC is used,
                  please modify accoringly.
The functions to be modified for other SOCs are given below.
		/*******************************************************************************
		Function:
			void SPIOpen(void)
		Summary:
			This function configures the SPI module of SOC.
			
		Description:
			This function configures the SPI module of SOC.

		/*******************************************************************************
		Function:
			void SPIRead(void)
		Summary:
			This function read one byte.
	
		/*******************************************************************************
		Function:
			void SPIOpen(void)
		Summary:
			This function configures the SPI module of SOC.
-----------------------------------------------------------------------------------
===============
HBI Driver:
===============
PMPDriver.c and .h - This file has the HBI routines to access LAN9252.It is platform independent.

The functions to be modified for other SOCs are given below.
===============
PIC32PMPDriver- This folder is unique to HBI (PMP) module of PIC32MX795F512L.If another variant of PIC is used,
                 please modify accoringly.
		/*******************************************************************************
		Function:
			void PMPOpen(PMPMode pmpmode, RWType rwtype, Polarity pl)
		Summary:
			This function configures the PMP(Host Bus Interface) module of SOC.
			
		/*******************************************************************************
		Function:
			UINT32 PMPReadDWord (UINT16 Address)
		 Summary:
			This function readS 4 bytes of data from LAN9252 CSR register    

		/*******************************************************************************
		Function:
			void PMPWriteDWord (UINT16 Address, UINT32 Val)
		Summary:
			This function writes 4 bytes of data to the corresponding address of LAN9252 CSR register    			
-----------------------------------------------------------------------------------

===============
PICHW.c: IRQ, SYNC0, SYNC1 and Timer interrupt routines and specific function calls to configure 
and control the interrupts. This file is specific to PIC32MX795F512L and LAN9252 EVBs.
The functions to be modified for other SOCs are given below.

		/*******************************************************************************
		Function:
			void PDI_Init_SYNC_Interrupts(void)

		Description:
			The function configure and enable SYNC0 and SYNC1 interrupt. It is platform dependent. 
			INIT_SYNCx_INT is a macro which will configure the external interrupt and ENABLE_SYNCx_INT 
			macro for enabling interrupt for the particular lines.

		/*******************************************************************************
		Function:
			void PDI_Restore_Global_Interrupt(UINT32 Int_sts)
			
		Description:
		This routine restores the core to the previous interrupt handling state.

		Parameters:
		Int_sts      - the state of the previous interrupt handling state.

		Example:
		<code>
		unsigned int intStatus;

		intStatus = PDI_Disable_Global_Interrupt();

		// ... application code

		PDI_Restore_Global_Interrupt(intStatus);
		</code>

		/*******************************************************************************
		Function:
		 void PDI_Enable_Global_interrupt(void)

		Description:
		This routine enables the core to handle any pending interrupt requests.

		Precondition:
		Need to configure system using interrupt (IRQ, SYNC0 and SYNC1- if they are using)
		
		/*****************************************************************************
		Function:
		UINT16 PDI_GetTimer(void)

		Summary:
		Get the 1ms current timer value
		Description:
		This routine gets the 1ms current timer value.

		/*******************************************************************************
		Function:
		void PDI_ClearTimer(void)

		Description:
		This routine clears the 1ms current timer value.
		
		/*******************************************************************************
		Function:
		void PDI_Timer_Interrupt(void)
			
		Description:
		This function configure and enable the TIMER interrupt for 1ms
		
		/*******************************************************************************
		Function:
		void PDI_IRQ_Interrupt(void)

		Description:
		This function configure and enable the interrupt for IRQ
	
		/*******************************************************************************
		Function:
		void HW_SetLed(UINT8 RunLed,UINT8 ErrLed)

		Description:
		LAN9252 does not support error LED. So this feature has to be enabled by PDI SOC if it is needed.

		Parameters:
		RunLed  - It is not used. This will be set by LAN9252.    
		ErrLed      -  1- ON, 0-0FF.
	
		/*******************************************************************************
		Function:
		void __ISR(_EXTERNAL_0_VECTOR, ipl7srs) ExtInterruptHandler(void)

		Summary:
		Interrupt service routine for the PDI interrupt from the EtherCAT Slave Controller

		/*******************************************************************************
		Function:
		void __ISR(_EXTERNAL_1_VECTOR, ipl5) Sync0Isr(void)

		Summary:
		Interrupt service routine for the interrupts from SYNC0

		/*******************************************************************************
		Function:
		void __ISR(_EXTERNAL_2_VECTOR, ipl4) Sync1Isr(void)


		Summary:
		Interrupt service routine for the interrupts from SYNC1

		/*******************************************************************************
		Function:
		void __ISR(_TIMER_5_VECTOR,IPL3AUTO) _TIMER5_HANDLER(void)

		Summary:
		Interrupt service routine for the interrupts from TIMER5
-----------------------------------------------------------------------------------
===============
Microchip_LAN9252_SSC_Config.xml - Input xml file to SSC tool. It has LAN9252 specifics, and it 
is platform independent.
-----------------------------------------------------------------------------------
===============
The complete sample project with PIC32MX is present at "Demo and Eval Board" section.

Note:  All functions(which described above) in the platform dependent files have to be created according to the 
SOC selected by the user.

