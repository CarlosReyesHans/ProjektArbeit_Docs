/*******************************************************************************
 PIC32 Host Bus Interface Driver

  Company:
    Microchip Technology Inc.

  File Name:
    PMPDriver.c

  Summary:
    Contains the functional implementation of PIC32 Host Bus Interface Driver

  Description:
    This file contains the functional implementation of PIC32 Host Bus Interface Driver
	
  Change History:
    Version		Changes
	0.1			Initial version.
	0.2			-
	0.3			-	
	0.4			-
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

#include "PMPDriver.h"
#include "../Common/UserDataTypes.h"

PMPMode CurrPMPMode;
Polarity gpl;

void Delay(UINT16 Count)
{
    do
    {
        asm volatile ("nop");
        
    } while (Count--);
}

void PMPOpen(PMPMode pmpmode, RWType rwtype, Polarity pl)
{
    PMCON = 0;
    PMMODE = 0;
    PMADDR = 0;
    PMAEN = 0;
    gpl = pl;
    
    if (pl.ALE_QUAL)
    {
        PMAENSET = 0x8003;      // Allocate PMA15 for CS2, PMA1,0 for ALEHI, ALELO or PMA<1:0>
        PMADDRbits.CS2 = 1;
    }
    else
    {
        PMAENSET = 0x0003;      // Allocate PMA1,0 for ALEHI, ALELO or PMA<1:0>
    }
    
    PMCONSET = 0x0300;          // Enable RD/WR strobes

    if (pl.ALE_QUAL)
    {
        PMCONSET = 0x0040;      // PMCS2 as Chip Select
    }
    
    if (pl.ALE)
    {
        PMCONSET = 0x0020;      // ALE polarity high
    }

    if (pl.CS)
    {
        PMCONSET = 0x0010;      // Chip select polarity high
    }

    if (pl.WRENB)
    {
        PMCONSET = 0x0002;      // Write strobe polarity high
    }

    if (pl.RDWR)
    {
        PMCONSET = 0x0001;      // Read strobe polarity high
    }

    switch(rwtype)
    {
        case MM2:
        default:
            PMMODESET = 0x0289;     // Read and Write on separate pins
            break;

        case MM1:
            PMMODESET = 0x0389;     // RW/WR and Enable
            break;
    }
     
    switch(pmpmode)
    {
        case INDEXED_8BIT:
            PMAENSET = 0x003C;      // Allocate PMA5,4,3,2 for PMA<4:2>
            break;
            
        case INDEXED_16BIT:
            PMMODESET = 0x0400;     // 16 bit mode
            PMAENSET = 0x003C;      // Allocate PMA5,4,3,2 for PMA<4:2>
            break;

        case MDP_8BIT:
            PMCONSET = 0x1000;      // All 16 bits of address are multiplexed on PMD<7:0> pin
            break;

        case MDP_16BIT:
            PMCONSET = 0x1000;      // All 16 bits of address are multiplexed on PMD<7:0> pin
            PMMODESET = 0x0400;     // 16 bit mode
            break;
            
        case MSP_16BIT:
            PMCONSET = 0x1800;      // All 16 bits of address are multiplexed on PMD<15:0> pins
            PMMODESET = 0x0400;     // 16 bit mode
            break;
    }

    PMCONSET = 0x8000;
    CurrPMPMode = pmpmode;

    UINT32 dummy;
    #ifdef HBI_INDEXED_MODE
        PMPWriteDWord (0,0x64);
        dummy = PMPReadDWord (4);
    #else
        dummy = PMPReadDWord(0x64);
    #endif 
    
}

void PMPReadByte(UINT16 Address, UINT8 *Buffer, UINT16 Count)
{
    UINT16 itr = 0, dummy;

    PMPWaitForNoBusy();
    PMADDRbits.ADDR = Address;
    if (gpl.CS)
    {
        PMCONSET = 0x0010;
    }
    else
    {
        PMCONCLR = 0x0010;
    }
    do
    {
        if (itr > Count)
            break;

        PMPWaitForNoBusy();

        if (itr == Count)
        {
            if (gpl.CS)
            {
                PMCONCLR = 0x0010;
            }
            else
            {
                PMCONSET = 0x0010;
            }
            Buffer[itr-1] = PMDIN;
            PMCONINV = 0x0010;
        }
        else if (itr > 0)
        {
            Buffer[itr-1] = PMDIN;
        }
        else
        {
            dummy = PMDIN;
        }

        PMADDRbits.ADDR = ++Address;

    } while (++itr);
}

void PMPReadWord (UINT16 Address, UINT16 *Buffer, UINT16 Count)
{
    UINT16 itr = 0, dummy;

    if (CurrPMPMode != INDEXED_16BIT)
    {
        // Write the addr
        Address >>= 1;
    }

    PMPWaitForNoBusy();
    PMADDRbits.ADDR = Address;

    do
    {
        if (itr > Count)
            break;

        PMPWaitForNoBusy();

        if (itr == Count)
        {
            PMCONINV = 0x0010;
            Buffer[itr-1] = PMDIN;
            PMCONINV = 0x0010;
        }
        else if (itr > 0)
        {
            Buffer[itr-1] = PMDIN;
        }
        else
        {
            dummy = PMDIN;
        }

        if (CurrPMPMode != INDEXED_16BIT)
        {
            PMADDRbits.ADDR = ++Address;
        }
        else
        {
            ++Address;
            PMADDRbits.ADDR = ++Address;
        }

    } while (++itr);
}

UINT32 PMPReadDWord (UINT16 Address)
{
    UINT16 itr = 0, dummy, loops;
    UINT32_VAL res;

    res.Val = 0;
    
    if (CurrPMPMode & 0x01)
    {
        if (CurrPMPMode != INDEXED_16BIT)
        {
            // Write the addr
            Address >>= 1;
        }

        loops = 2;
    }
    else
    {
        loops = 4;
    }

    PMPWaitForNoBusy();
    PMADDRbits.ADDR = Address;

    if (gpl.CS)
    {
        PMCONSET = 0x0010;
    }
    else
    {
        PMCONCLR = 0x0010;
    }

    do
    {
        if (itr > loops)
            break;

        PMPWaitForNoBusy();

        switch(itr)
        {
            case 0:
                dummy = PMDIN;
                break;
                
            case 1:
                if (CurrPMPMode & 0x01)
                {
                    res.word.LW = PMDIN;
                }
                else
                {
                    res.byte.LB = PMDIN;
                }
                break;
                
            case 2:
                if (CurrPMPMode & 0x01)
                {
    
                    if (gpl.CS)
                    {
                        PMCONCLR = 0x0010;
                    }
                    else
                    {
                        PMCONSET = 0x0010;
                    }
                    res.word.HW = PMDIN;

                }
                else
                {
                    res.byte.HB = PMDIN;
                }
                break;

            case 3:
                res.byte.UB = PMDIN;
                break;

            case 4:

                if (gpl.CS)
                {
                    PMCONCLR = 0x0010;
                }
                else
                {
                    PMCONSET = 0x0010;
                }
                res.byte.MB = PMDIN;
                
                break;
        }

        if (CurrPMPMode != INDEXED_16BIT)
        {
            PMADDRbits.ADDR = ++Address;
        }
        else
        {
            ++Address;
            PMADDRbits.ADDR = ++Address;
        }

    } while (++itr);

    return res.Val;
}

void PMPWriteByte (UINT16 Address, UINT8 *Buffer, UINT16 Count)
{
    UINT16 itr = 0;

    PMPWaitForNoBusy();
    PMADDRbits.ADDR = Address;

    do
    {
        if (itr == Count)
            break;

        PMDIN = Buffer[itr];
        PMPWaitForNoBusy();

        PMADDRbits.ADDR = ++Address;

    } while (++itr);
}

#ifdef FIFODUMP_SUPPORT
    FIFODATA FIFOData;
    UINT16 FIFODataIdx = 0;
#endif

void PMPWriteWord (UINT16 Address, UINT16 *Buffer, UINT16 Count)
{
    UINT16 itr = 0;

    if (CurrPMPMode != INDEXED_16BIT)
    {
        // Write the addr
        Address >>= 1;
    }

    PMPWaitForNoBusy();
    PMADDRbits.ADDR = Address;

    do
    {
        if (itr == Count)
            break;
        
#ifdef FIFODUMP_SUPPORT
        FIFOData.FIFOData_16[FIFODataIdx++] = Buffer[itr];
#endif

        PMDIN = Buffer[itr];
        PMPWaitForNoBusy();

        if (CurrPMPMode != INDEXED_16BIT)
        {
            PMADDRbits.ADDR = ++Address;
        }
        else
        {
            ++Address;
            PMADDRbits.ADDR = ++Address;
        }

    } while (++itr);
}

void PMPWriteDWord (UINT16 Address, UINT32 Val)
{
    UINT16 itr = 0, loops;
    UINT32_VAL str;

    str.Val = Val;

    if (CurrPMPMode & 0x01)
    {
        if (CurrPMPMode != INDEXED_16BIT)
        {
            // Write the addr
            Address >>= 1;
        }
        loops = 2;
    }
    else
    {
        loops = 4;
    }

    PMPWaitForNoBusy();
    PMADDRbits.ADDR = Address;
    if (gpl.CS)
    {
        PMCONSET = 0x0010;
    }
    else
    {
        PMCONCLR = 0x0010;
    }

    do
    {
        if (itr == loops)
            break;

        switch(itr)
        {
            case 0:
                if (CurrPMPMode & 0x01)
                {
                    #ifdef FIFODUMP_SUPPORT
                        FIFOData.FIFOData_16[FIFODataIdx++] = str.word.LW;
                    #endif
                    PMDIN = str.word.LW;
                }
                else
                {
                    PMDIN = str.byte.LB;
                }
                break;

            case 1:
                if (CurrPMPMode & 0x01)
                {
                    #ifdef FIFODUMP_SUPPORT
                        FIFOData.FIFOData_16[FIFODataIdx++] = str.word.HW;
                    #endif
                    PMDIN = str.word.HW;
                }
                else
                {
                    PMDIN = str.byte.HB;
                }
                break;

            case 2:
                PMDIN = str.byte.UB;
                break;

            case 3:
                PMDIN = str.byte.MB;
                break;
        }
        
        PMPWaitForNoBusy();

        if (CurrPMPMode != INDEXED_16BIT)
        {
            PMADDRbits.ADDR = ++Address;
        }
        else
        {
            ++Address;
            PMADDRbits.ADDR = ++Address;
        }
        
    } while (++itr);
}
void PMPReadDRegister(UINT8 *ReadBuffer, UINT16 Address, UINT8 Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0;

    param32_1.w[0] = Address;
    param32_1.v[2] = Count;
    param32_1.v[3] = 0xC0;
#ifdef HBI_INDEXED_MODE
    PMPWriteDWord (0,0x304);
    PMPWriteDWord (4,param32_1.Val);
#else
    PMPWriteDWord (0x304, param32_1.Val);
#endif

    do
    {
#ifdef HBI_INDEXED_MODE
        param32_1.Val = PMPReadDWord (4);
#else
        param32_1.Val = PMPReadDWord (0x304);
#endif
    }while(param32_1.v[3] &0x80);

#ifdef HBI_INDEXED_MODE
    PMPWriteDWord (0,0x300);
    param32_1.Val = PMPReadDWord (4);
#else
    param32_1.Val = PMPReadDWord (0x300);
#endif
    
     for(i=0;i<Count;i++)
         ReadBuffer[i] = param32_1.v[i];
   
    return;
}
void PMPWriteRegister( UINT8 *WriteBuffer, UINT16 Address, UINT8 Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0;

    for(i=0;i<Count;i++)
         param32_1.v[i] = WriteBuffer[i];

#ifdef HBI_INDEXED_MODE
    PMPWriteDWord (0,0x300);
    PMPWriteDWord (4,param32_1.Val);
#else
    PMPWriteDWord (0x300, param32_1.Val);
#endif

    param32_1.w[0] = Address;
    param32_1.v[2] = Count;
    param32_1.v[3] = 0x80;

#ifdef HBI_INDEXED_MODE
    PMPWriteDWord (0,0x304);
    PMPWriteDWord (4,param32_1.Val);
#else
    PMPWriteDWord (0x304, param32_1.Val);
#endif

    do
    {

#ifdef HBI_INDEXED_MODE
        param32_1.Val = PMPReadDWord (4);
#else
        param32_1.Val = PMPReadDWord (0x304);
#endif
    }while(param32_1.v[3] &0x80);

    return;
}

void PMPReadPDRamRegister(UINT8 *ReadBuffer, UINT16 Address, UINT16 Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0,nlength, nBytePosition;

    /*Reset/Abort any previous commands.*/
    param32_1.Val = 0x40000000;                                                 /*TODO:replace with #defines*/

    
#ifdef HBI_INDEXED_MODE
    /*Set index register 8 for 0x30c.*/
    PMPWriteDWord (0x08,0x30c);
    PMPWriteDWord (0x0C,param32_1.Val);
#else
    PMPWriteDWord (0x30c, param32_1.Val);
#endif

    /*The host should not modify this field unless the PRAM Read Busy
    (PRAM_READ_BUSY) bit is a 0.*/
    do
    {

#ifdef HBI_INDEXED_MODE
      //  PMPWriteDWord (0,0x30c);
        param32_1.Val = PMPReadDWord (0x0C);
#else
        param32_1.Val = PMPReadDWord (0x30C);
#endif
    }while((param32_1.v[3] &0x80));

    /*Write address and length in the EtherCAT Process RAM Read Address and
     * Length Register (ECAT_PRAM_RD_ADDR_LEN)*/
    param32_1.w[0] = Address;
    param32_1.w[1] = Count;

    

#ifdef HBI_INDEXED_MODE
    /*Set index register 0x10 for 0x308*/
    PMPWriteDWord (0x10,0x308);
    PMPWriteDWord (0x14,param32_1.Val);
#else
    PMPWriteDWord (0x308, param32_1.Val);
#endif

    param32_1.Val = PMPReadDWord (0x14);
    /*Set PRAM Read Busy (PRAM_READ_BUSY) bit(-EtherCAT Process RAM Read Command Register)
     *  to start read operatrion*/

    param32_1.Val = 0x80000000; /*TODO:replace with #defines*/
  
#ifdef HBI_INDEXED_MODE
   // PMPWriteDWord (0,0x30c);
    PMPWriteDWord (0x0C,param32_1.Val);
#else
    PMPWriteDWord (0x30c, param32_1.Val);
#endif

    /*Read PRAM Read Data Available (PRAM_READ_AVAIL) bit is set*/
    do
    {
#ifdef HBI_INDEXED_MODE
        param32_1.Val = PMPReadDWord (0x0C);
#else
        param32_1.Val = PMPReadDWord (0x30C);
#endif
    }while(!(param32_1.v[0] &0x01));


    /*Read data register(FIFO) */
#ifdef HBI_INDEXED_MODE
    /*Set index register 0 for Read FIFO register 0*/
    PMPWriteDWord (0,0x0);
#endif

    /*Fifo registers are aliased address. In indexed it will read indexed data reg 0x04, but it will point to reg 0
     In other modes read 0x04 FIFO register since all registers are aliased*/

    /*get the byte lenth for first read*/
    param32_1.Val = PMPReadDWord (4);
    nBytePosition = (Address & 0x03);
    nlength = (4-nBytePosition) > Count ? Count:(4-nBytePosition);
    memcpy(ReadBuffer ,&param32_1.v[nBytePosition],nlength);
    Count-=nlength;
    i=nlength;
    
    while(Count)
    {
        param32_1.Val = PMPReadDWord (4);
       
        nlength = Count > 4 ? 4: Count;
        memcpy((ReadBuffer+i) ,&param32_1,nlength);

        i+=nlength;
        Count-=nlength;
    }
   
    return;
}

void PMPWritePDRamRegister(UINT8 *WriteBuffer, UINT16 Address, UINT16 Count)
{
    UINT32_VAL param32_1 = {0};
    UINT8 i = 0,nlength, nBytePosition,nWrtSpcAvlCount,test;

    /*Reset or Abort any previous commands.*/
    param32_1.Val = 0x40000000;                                                 /*TODO:replace with #defines*/
#ifdef HBI_INDEXED_MODE
    /*Set index register 0x8 and 0xc for 0x314*/
    PMPWriteDWord (8,0x314);
    PMPWriteDWord (4,param32_1.Val);
#else
    PMPWriteDWord (0x314, param32_1.Val);
#endif

    /*Make sure there is no previous write is pending
    (PRAM Write Busy) bit is a 0 */
    do
    {

#ifdef HBI_INDEXED_MODE
        param32_1.Val = PMPReadDWord (0x0c);
#else
        param32_1.Val = PMPReadDWord (0x314);
#endif
    }while((param32_1.v[3] &0x80));
    
    /*Write Address and Length Register (ECAT_PRAM_WR_ADDR_LEN) with the
    starting byte address and length)*/
    param32_1.w[0] = Address;
    param32_1.w[1] = Count;

#ifdef HBI_INDEXED_MODE
    /*Set index register 0x10 and 0x14 for 0x310*/
    PMPWriteDWord (0x10,0x310);
    PMPWriteDWord (0x14,param32_1.Val);
#else
    PMPWriteDWord (0x310, param32_1.Val);
#endif

    /*write to the EtherCAT Process RAM Write Command Register (ECAT_PRAM_WR_CMD) with the  PRAM Write Busy
    (PRAM_WRITE_BUSY) bit set*/

    param32_1.Val = 0x80000000; /*TODO:replace with #defines*/

#ifdef HBI_INDEXED_MODE
    PMPWriteDWord (0x0C,param32_1.Val);
#else
    PMPWriteDWord (0x314, param32_1.Val);
#endif

    /*Read PRAM write Data Available (PRAM_READ_AVAIL) bit is set*/
    do
    {
#ifdef HBI_INDEXED_MODE
        param32_1.Val = PMPReadDWord (0x0C);
#else
        param32_1.Val = PMPReadDWord (0x314);
#endif
    }while(!(param32_1.v[0] &0x01));

    /*Check write data available count*/
    nWrtSpcAvlCount = param32_1.v[1];

    /*Write data to Write FIFO) */ 
    /*get the byte lenth for first read*/
    nBytePosition = (Address & 0x03);

    nlength = (4-nBytePosition) > Count ? Count:(4-nBytePosition);

    param32_1.Val = 0;
    memcpy(&param32_1.v[nBytePosition],WriteBuffer, nlength);

#ifdef HBI_INDEXED_MODE
    /*Set index register 0 for fifo write register 0x20*/
    PMPWriteDWord (0,0x20);
    PMPWriteDWord (0x4,param32_1.Val);
#else
    PMPWriteDWord (0x20,param32_1.Val);
#endif

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
        #ifdef HBI_INDEXED_MOD
                param32_1.Val = PMPReadDWord (0x0C);
        #else
                param32_1.Val = PMPReadDWord (0x314);
        #endif
            }while(!(param32_1.v[0] &0x01));

            /*Check write data available count*/
            nWrtSpcAvlCount = param32_1.v[1];

        }
#endif
               
        nlength = Count > 4 ? 4: Count;
        memcpy(&param32_1, (WriteBuffer+i), nlength);

    #ifdef HBI_INDEXED_MODE
        PMPWriteDWord (4,param32_1.Val);
    #else
        PMPWriteDWord (0x20,param32_1.Val);
    #endif

        i+=nlength;
        Count-=nlength;
        nWrtSpcAvlCount--;
    }

    return;
}
