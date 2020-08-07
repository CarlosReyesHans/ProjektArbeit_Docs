/*******************************************************************************
 PIC32 Host Bus Interface Driver

  Company:
    Microchip Technology Inc.

  File Name:
    PIC32PMPDriver.c

  Summary:
    Contains the functional implementation of PIC32 Host Bus Interface Driver

  Description:
    This file contains the functional implementation of PIC32 Host Bus Interface Driver
	
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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "PIC32PMPDriver.h"
#include "9252_HW.h"


PMPMode CurrPMPMode;
Polarity gpl;

/*******************************************************************************
  Function:
   void PMPOpen(PMPMode pmpmode, RWType rwtype, Polarity pl)
  Summary:
    This function configures the PMP(Host Bus Interface) module of SOC.
        
  Description:
    This function configures the PMP(Host bus Interface) module of SOC. Refer HBI section of LAN9252 datasheet for more information.

   Parameters:
	pmpmode- Different modes(INDEXED_8BIT, INDEXED_16BIT, MDP_8BIT, MDP_16BIT, MSP_8BIT, MSP_16BIT)
	rwtype - Read and Write on separate pins(MM2) or same pin(MM1)
	pl - Different polarities.
*****************************************************************************/
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
   
}
/*******************************************************************************
  Function:
   UINT32 PMPReadDWord (UINT16 Address)
  Summary:
    This function readS 4 bytes of data from LAN9252 CSR register        
  Description:
    This function readS 4 bytes of data from LAN9252 CSR register( not ESC register). 
	Refer HBI section of LAN9252 datasheet for more information.

  Parameters:
	Address      - Address of LAN9252 CSR register( not ESC register).
*****************************************************************************/

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
/*******************************************************************************
  Function:
   void PMPWriteDWord (UINT16 Address, UINT32 Val)
  Summary:
    This function writes 4 bytes of data to the corresponding address of LAN9252 CSR register        
  Description:
    This function writes 4 bytes of data to the corresponding address of LAN9252 CSR register ( not ESC register). Refer HBI section of LAN9252 datasheet for more information.

   Parameters:
	Address     - Address of LAN9252 CSR register( not ESC register).
	Val			- 4 byte value.
*****************************************************************************/
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
