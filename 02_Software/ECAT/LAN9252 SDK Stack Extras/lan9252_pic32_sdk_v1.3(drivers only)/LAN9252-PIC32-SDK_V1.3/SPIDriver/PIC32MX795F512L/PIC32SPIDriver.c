/*******************************************************************************
 PIC32 SPI Interface Driver

  Company:
    Microchip Technology Inc.

  File Name:
    SPIDriver.c

  Summary:
    Contains the functional implementation of PIC32 SPI Interface Driver

  Description:
    This file contains the functional implementation of PIC32 SPI Interface Driver
	
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
 

#include "PIC32SPIDriver.h"
#include "9252_HW.h"


void SPIPut(UINT8 data)
{
    // Wait for free buffer
    while(!SPI4STATbits.SPITBE);
    SPI4BUF = data;

    // Wait for data UINT8
    while(!SPI4STATbits.SPIRBF);
}
/*******************************************************************************
  Function:
   void SPIWrite(UINT8 data)
  Summary:
    This function write one byte.
        
  Description:
    This function write one byte.

*****************************************************************************/ 
void SPIWrite(UINT8 data)
{
    SPIPut(data);
    SPIGet();
}
/*******************************************************************************
  Function:
   void SPIRead(void)
  Summary:
    This function read one byte.
        
  Description:
    This function read one byte.

*****************************************************************************/  
UINT8 SPIRead()
{
    UINT8 data;
    SPIPut(0);
    data = (UINT8)SPIGet();
    return (data);
}
/*******************************************************************************
  Function:
   void SPIOpen(void)
  Summary:
    This function configures the SPI module of SOC.
        
  Description:
    This function configures the SPI module of SOC.

*****************************************************************************/  
void SPIOpen()
{
    //Initialize to zero
    SPI4STAT = 0;
    SPI4CON = 0;
    SPI4BRG = 0;
    //Enable master as SPI4
    SPI4CONbits.MSTEN = 1;
    SPI4CONbits.CKP = 0;
    SPI4CONbits.CKE = 1;
    SPI4CONbits.SMP = 1;
    //Set clock speed 20Mhz
    SPI4BRG = SPI_CLK_DIV(20);
    //Enable SPI
    SPI4CONbits.ON = 1;

    //Configure CS line as GPIO output
    TRISFbits.TRISF12 = 0;
    // Set CS high/Deassert CS
    LATFbits.LATF12 = 1;
    //PinMUX Clock
    TRISFbits.TRISF13 = 0;
    //PinMUX SDO
    TRISFbits.TRISF5 = 0;
}

