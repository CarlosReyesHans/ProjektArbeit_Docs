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
 
#include "SPIDriver.h"
#include "../Common/UserDataTypes.h"

void Delay(UINT16 Count)
{
    do
    {
        asm volatile ("nop");
        
    } while (Count--);
}

void SPIPut(UINT8 data)
{
    // Wait for free buffer
    while(!SPI4STATbits.SPITBE);
    SPI4BUF = data;

    // Wait for data UINT8
    while(!SPI4STATbits.SPIRBF);
}
void SPIWrite(UINT8 data)
{
    SPIPut(data);
    SPIGet();
}
UINT8 SPIRead()
{
    UINT8 data;
    SPIPut(0);
    data = (UINT8)SPIGet();
    return (data);
}
  
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


UINT32 SPIReadDWord (UINT16 Address)
{
    UINT32_VAL dwResult;
    UINT16_VAL wAddr;

    wAddr.Val  = Address;
    //Assert CS line
    CSLOW();
    //Write Command
    SPIWriteByte(CMD_SERIAL_READ);
    //Write Address
    SPIWriteByte(wAddr.byte.HB);
    SPIWriteByte(wAddr.byte.LB);
    //Read Bytes
    dwResult.byte.LB = SPIReadByte();
    dwResult.byte.HB = SPIReadByte();
    dwResult.byte.UB = SPIReadByte();
    dwResult.byte.MB = SPIReadByte();
    //De-Assert CS line
    CSHIGH();
   
    return dwResult.Val;
}


void SPIWriteDWord (UINT16 Address, UINT32 Val)
{
    UINT32_VAL dwData;
    UINT16_VAL wAddr;

    wAddr.Val  = Address;
    dwData.Val = Val;
    //Assert CS line
    CSLOW();
    //Write Command
    SPIWriteByte(CMD_SERIAL_WRITE);
    //Write Address
    SPIWriteByte(wAddr.byte.HB);
    SPIWriteByte(wAddr.byte.LB);
    //Write Bytes
    SPIWriteByte(dwData.byte.LB);
    SPIWriteByte(dwData.byte.HB);
    SPIWriteByte(dwData.byte.UB);
    SPIWriteByte(dwData.byte.MB);

    //De-Assert CS line
    CSHIGH();
}
void SPIReadDRegister(UINT8 *ReadBuffer, UINT16 Address, UINT8 Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0;
    UINT16_VAL wAddr;
    wAddr.Val = Address;

    param32_1.v[0] = wAddr.byte.LB;
    param32_1.v[1] = wAddr.byte.HB;
    param32_1.v[2] = Count;
    param32_1.v[3] = ESC_READ_BYTE;

    SPIWriteDWord (ESC_CSR_CMD_REG, param32_1.Val);

    do
    {
	param32_1.Val = SPIReadDWord (ESC_CSR_CMD_REG);
		
    }while(param32_1.v[3] & ESC_CSR_BUSY);

    param32_1.Val = SPIReadDWord (ESC_CSR_DATA_REG);

    
    for(i=0;i<Count;i++)
         ReadBuffer[i] = param32_1.v[i];
   
    return;
}
void SPIWriteRegister( UINT8 *WriteBuffer, UINT16 Address, UINT8 Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0;
    UINT16_VAL wAddr;

    for(i=0;i<Count;i++)
         param32_1.v[i] = WriteBuffer[i];

    SPIWriteDWord (ESC_CSR_DATA_REG, param32_1.Val);


    wAddr.Val = Address;

    param32_1.v[0] = wAddr.byte.LB;
    param32_1.v[1] = wAddr.byte.HB;
    param32_1.v[2] = Count;
    param32_1.v[3] = ESC_WRITE_BYTE;

    SPIWriteDWord (0x304, param32_1.Val);
    do
    {
	param32_1.Val = SPIReadDWord (0x304);

    }while(param32_1.v[3] & ESC_CSR_BUSY);

    return;
}

void SPIReadPDRamRegister(UINT8 *ReadBuffer, UINT16 Address, UINT16 Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0,nlength, nUINT8Position;

    /*Reset/Abort any previous commands.*/
    param32_1.Val = 0x40000000;     /*TODO:replace with #defines*/

    SPIWriteDWord (0x30c, param32_1.Val);

    /*The host should not modify this field unless the PRAM Read Busy
    (PRAM_READ_BUSY) bit is a 0.*/
    do
    {
        param32_1.Val = SPIReadDWord (0x30C);

    }while((param32_1.v[3] &0x80));

    /*Write address and length in the EtherCAT Process RAM Read Address and
     * Length Register (ECAT_PRAM_RD_ADDR_LEN)*/
    param32_1.w[0] = Address;
    param32_1.w[1] = Count;

    SPIWriteDWord (0x308, param32_1.Val);

    param32_1.Val = SPIReadDWord (0x14);
    /*Set PRAM Read Busy (PRAM_READ_BUSY) bit(-EtherCAT Process RAM Read Command Register)
     *  to start read operatrion*/

    param32_1.Val = 0x80000000; /*TODO:replace with #defines*/
 
    SPIWriteDWord (0x30c, param32_1.Val);

    /*Read PRAM Read Data Available (PRAM_READ_AVAIL) bit is set*/
    do
    {
        param32_1.Val = SPIReadDWord (0x30C);

    }while(!(param32_1.v[0] &0x01));


    /*Fifo registers are aliased address. In indexed it will read indexed data reg 0x04, but it will point to reg 0
     In other modes read 0x04 FIFO register since all registers are aliased*/

    /*get the UINT8 lenth for first read*/
    param32_1.Val = SPIReadDWord (4);
    nUINT8Position = (Address & 0x03);
    nlength = (4-nUINT8Position) > Count ? Count:(4-nUINT8Position);
    memcpy(ReadBuffer ,&param32_1.v[nUINT8Position],nlength);
    Count-=nlength;
    i=nlength;
    
    while(Count)
    {
        param32_1.Val = SPIReadDWord (4);
       
        nlength = Count > 4 ? 4: Count;
        memcpy((ReadBuffer+i) ,&param32_1,nlength);

        i+=nlength;
        Count-=nlength;
    }
   
    return;
}

void SPIWritePDRamRegister(UINT8 *WriteBuffer, UINT16 Address, UINT16 Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0,nlength, nUINT8Position,nWrtSpcAvlCount,test;

    /*Reset or Abort any previous commands.*/
    param32_1.Val = 0x40000000;                                                 /*TODO:replace with #defines*/

    SPIWriteDWord (0x314, param32_1.Val);

    /*Make sure there is no previous write is pending
    (PRAM Write Busy) bit is a 0 */
    do
    {
        param32_1.Val = SPIReadDWord (0x314);

    }while((param32_1.v[3] &0x80));
    
    /*Write Address and Length Register (ECAT_PRAM_WR_ADDR_LEN) with the
    starting UINT8 address and length)*/
    param32_1.w[0] = Address;
    param32_1.w[1] = Count;

    SPIWriteDWord (0x310, param32_1.Val);

    /*write to the EtherCAT Process RAM Write Command Register (ECAT_PRAM_WR_CMD) with the  PRAM Write Busy
    (PRAM_WRITE_BUSY) bit set*/

    param32_1.Val = 0x80000000; /*TODO:replace with #defines*/

    SPIWriteDWord (0x314, param32_1.Val);

    /*Read PRAM write Data Available (PRAM_READ_AVAIL) bit is set*/
    do
    {
       param32_1.Val = SPIReadDWord (0x314);

    }while(!(param32_1.v[0] &0x01));

    /*Check write data available count*/
    nWrtSpcAvlCount = param32_1.v[1];

    /*Write data to Write FIFO) */ 
    /*get the UINT8 lenth for first read*/
    nUINT8Position = (Address & 0x03);

    nlength = (4-nUINT8Position) > Count ? Count:(4-nUINT8Position);

    param32_1.Val = 0;
    memcpy(&param32_1.v[nUINT8Position],WriteBuffer, nlength);

    SPIWriteDWord (0x20,param32_1.Val);

    Count-=nlength;
    i=nlength;
    nWrtSpcAvlCount--;

    while(Count)
    {
#if 0
                                                                                /*TODO: Check this code is needed.*/
        while(0 == nWrtSpcAvlCount)
        {
            /*Wait till space is available*/
            do
            {

				param32_1.Val = SPIReadDWord (0x314);
       
            }while(!(param32_1.v[0] &0x01));

            /*Check write data available count*/
            nWrtSpcAvlCount = param32_1.v[1];

        }
#endif
               
        nlength = Count > 4 ? 4: Count;
        memcpy(&param32_1, (WriteBuffer+i), nlength);

        SPIWriteDWord (0x20,param32_1.Val);
   
        i+=nlength;
        Count-=nlength;
        nWrtSpcAvlCount--;
    }

    return;
}