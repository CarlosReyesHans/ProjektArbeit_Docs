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
 
This ReadMe file explains the LAN9252 SDK sample folder structure.

This sample SDK source requires Slave Stack Code 5.11 from EtherCAT.org to work.
Please refer to the Application note "Integrating Microchip's LAN9252 SDK with Beckhoff's EtherCAT® SSC" for 
integrating the LAN9252 SDK with the EtherCAT® Slave stack code from Beckhoff.

Project directory structure:
============================

SSC ---> (Main folder)
	|
	|
	|--->Common: 
	|	|
	|	|--->9252_HW.c
	|	|
	|	|--->9252_HW.h
	|	|
	|	|--->pic32_mchp_gpio_sample_app.c
	|	|
	|	|--->pic32_mchp_gpio_sample_app.h
	|	|
	|	|--->pic32_mchp_gpio_sample_appObjects.h
	|	|
	|--->PIC32: 
	|	|
	|	|--->build:
	|	|
	|	|--->Common:
	|	|	|
	|	|	|--->ErrorCodes.h
	|	|	|
	|	|	|--->SystemCSR.h
	|	|	|
	|	|	|--->UserDataTypes.h
	|	|
	|	|--->debug:
	|	|
	|	|--->dist:
	|	|
	|	|--->MemoryManager:
	|	|	|
	|	|	|--->MemoryManager.c
	|	|	|
	|	|	|--->MemoryManager.h
	|	|
	|	|--->nbproject:
	|	|	|
	|	|	|--->private:
	|	|	|
	|	|	|--->.cvsignore
	|	|	|
	|	|	|--->configurations.xml
	|	|	|
	|	|	|--->Makefile-genesis.properties
	|	|	|
	|	|	|--->Makefile-HBI_INDEXED_8BIT_XC32_PIC32MX795F512L.mk
	|	|	|
	|	|	|--->Makefile-HBI_INDEXED_16BIT_XC32_PIC32MX795F512L.mk
	|	|	|
	|	|	|--->Makefile-HBI_MDP_8BIT_XC32_PIC32MX795F512L.mk
	|	|	|
	|	|	|--->Makefile-HBI_MDP_16BIT_XC32_PIC32MX795F512L.mk
	|	|	|
	|	|	|--->Makefile-HBI_MSP_8BIT_XC32_PIC32MX795F512L.mk
	|	|	|
	|	|	|--->Makefile-HBI_MSP_16BIT_XC32_PIC32MX795F512L.mk
	|	|	|
	|	|	|--->Makefile-impl.mk
	|	|	|
	|	|	|--->Makefile-local-HBI_INDEXED_8BIT_XC32_PIC32MX795F512L.mk
	|	|	|
	|	|	|--->Makefile-local-HBI_INDEXED_16BIT_XC32_PIC32MX795F512L.mk
	|	|	|
	|	|	|--->Makefile-local-HBI_MDP_8BIT_XC32_PIC32MX795F512L.mk
	|	|	|
	|	|	|--->Makefile-local-HBI_MSP_8BIT_XC32_PIC32MX795F512L.mk
	|	|	|
	|	|	|--->Makefile-local-HBI_MSP_16BIT_XC32_PIC32MX795F512L.mk
	|	|	|
	|	|	|--->Makefile-variables.mk
	|	|	|
	|	|	|--->Package-HBI_INDEXED_8BIT_XC32_PIC32MX795F512L.bash
	|	|	|
	|	|	|--->Package-HBI_INDEXED_16BIT_XC32_PIC32MX795F512L.bash
	|	|	|
	|	|	|--->Package-HBI_MDP_8BIT_XC32_PIC32MX795F512L.bash
	|	|	|
	|	|	|--->Package-HBI_MDP_16BIT_XC32_PIC32MX795F512L.bash
	|	|	|
	|	|	|--->Package-HBI_MSP_8BIT_XC32_PIC32MX795F512L.bash
	|	|	|
	|	|	|--->Package-HBI_MSP_16BIT_XC32_PIC32MX795F512L.bash
	|	|	|
	|	|	|--->project.properties
	|	|	|
	|	|	|--->project.xml
	|	|
	|	|--->PMPDriver:
	|	|	|
	|	|	|--->PMPDriver.c
	|	|	|
	|	|	|--->PMPDriver.h
	|	|
	|	|--->configuration_bits.c
	|	|
	|	|--->exceptions.c
	|	|
	|	|--->getting_started.txt
	|	|
	|	|--->interrupts.c
	|	|
	|	|--->legal_disclaimer.txt
	|	|
	|	|--->main.c
	|	|
	|	|--->MakeFile
	|	|
	|	|--->project_information.txt
	|	|
	|	|--->Scheduler.c
	|	|
	|	|--->Scheduler.h
	|	|
	|	|--->system.c
	|	|
	|	|--->system.h
	|	|
	|	|--->user.c
	|	|
	|	|--->user.h
	|
	|--->PIC32-SPI: 
	|	|
	|	|--->build:
	|	|
	|	|--->Common:
	|	|	|
	|	|	|--->ErrorCodes.h
	|	|	|
	|	|	|--->SystemCSR.h
	|	|	|
	|	|	|--->UserDataTypes.h
	|	|
	|	|--->debug:
	|	|
	|	|--->dist:
	|	|
	|	|--->MemoryManager:
	|	|	|
	|	|	|--->MemoryManager.c
	|	|	|
	|	|	|--->MemoryManager.h
	|	|
	|	|--->nbproject:
	|	|	|
	|	|	|--->private:
	|	|	|
	|	|	|--->.cvsignore
	|	|	|
	|	|	|--->configurations.xml
	|	|	|
	|	|	|--->Makefile-genesis.properties
	|	|	|
	|	|	|--->Makefile-impl.mk
	|	|	|
	|	|	|--->Makefile-local-SPI_XC32_PIC32MX795F512L.mk
	|	|	|
	|	|	|--->Makefile-SPI_XC32_PIC32MX795F512L.mk
	|	|	|
	|	|	|--->Makefile-variables.mk
	|	|	|
	|	|	|--->Package-SPI_XC32_PIC32MX795F512L.bash
	|	|	|
	|	|	|--->project.properties
	|	|	|
	|	|	|--->project.xml
	|	|
	|	|--->SPIDriver:
	|	|	|
	|	|	|--->SPIDriver.c
	|	|	|
	|	|	|--->SPIDriver.h
	|	|
	|	|--->configuration_bits.c
	|	|
	|	|--->exceptions.c
	|	|
	|	|--->getting_started.txt
	|	|
	|	|--->interrupts.c
	|	|
	|	|--->legal_disclaimer.txt
	|	|
	|	|--->main.c
	|	|
	|	|--->MakeFile
	|	|
	|	|--->project_information.txt
	|	|
	|	|--->Scheduler.c
	|	|
	|	|--->Scheduler.h
	|	|
	|	|--->system.c
	|	|
	|	|--->system.h
	|	|
	|	|--->user.c
	|	|
	|	|--->user.h
	|
	|--->Readme.txt

	

	
	
