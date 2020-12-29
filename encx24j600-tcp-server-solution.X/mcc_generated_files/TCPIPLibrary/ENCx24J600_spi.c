/**
  ENCx24J600 SPI Driver File
	
  Company:
    Microchip Technology Inc.

  File Name:
    ENCx24J600_spi.c

  Summary:
    This is the SPI interface driver for ENCx24J600 family devices.

  Description:
    This file provides the SPI Interface Ethernet driver API implementation for
    the ENCx24J600 family devices.

 */

/*

©  [2015] Microchip Technology Inc. and its subsidiaries.  You may use this software 
and any derivatives exclusively with Microchip products. 
  
THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER EXPRESS, 
IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF 
NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE, OR ITS 
INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE 
IN ANY APPLICATION. 

IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL 
OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED 
TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY 
OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S 
TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED 
THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE TERMS. 

*/


#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "../mcc.h"
#include "ENCx24J600_types.h"
#include "ENCx24J600_spi.h"
#include "ethernet_driver.h"

sfr_bank_t last_bank;

uint16_t TXPacketSize;

static void ENCx24_BankselSPI(encX24J600_registers_t);

/**
 * Bank Select
 * @param a
 */
static void ENCx24_BankselSPI(encX24J600_registers_t a)
{
    uint8_t bank;
    bank = a & BANK_MASK;
    if( bank != last_bank && bank!=UNBANKED)
    {
        last_bank = bank;
        ETH_NCS_LOW();
        switch(bank)
        {
            case SFR_BANK0:
                ETH_WRITE8(b0sel_inst);
                break;
            case SFR_BANK1:
                ETH_WRITE8(b1sel_inst);
                break;
            case SFR_BANK2:
                ETH_WRITE8(b2sel_inst);
                break;
            case SFR_BANK3:
                ETH_WRITE8(b3sel_inst);
                break;
            case SFR_COMMON:
                break;
        }
        ETH_NCS_HIGH();
    }
}

/**
 * Read from SFRs
 * @param a
 * @return
 */
uint16_t ENCx24_Read(encX24J600_registers_t a)
{
  uint16_t v;
  uint8_t bank;

  bank = a & BANK_MASK;
  if(bank != UNBANKED)
  {
    ENCx24_BankselSPI(a);
    ETH_NCS_LOW();
    ETH_WRITE8(rcr_inst| (a & SFR_MASK));
  }
  else
  {
      ETH_NCS_LOW();
      ETH_WRITE8(rcru_inst);
      ETH_WRITE8(a);
  }
    ((uint8_t*)&v)[0] = ETH_READ8();
    ((uint8_t*)&v)[1] = ETH_READ8();
    ETH_NCS_HIGH();
  return v;
}

/**
 * Write to SFRs
 * @param a
 * @param data
 */
void ENCx24_Write(encX24J600_registers_t a, uint16_t data)
{
    uint8_t bank;
    bank = a & BANK_MASK;
    if(bank != UNBANKED)
    {
        ENCx24_BankselSPI(a);
        ETH_NCS_LOW();
        a &= SFR_MASK;
        ETH_WRITE8(wcr_inst | (a));
    }
    else
    {
        ETH_NCS_LOW();
        ETH_WRITE8(wcru_inst);
        ETH_WRITE8(a);
    }
    ETH_WRITE8(((uint8_t*) &data)[0]);
    ETH_WRITE8(((uint8_t*) &data)[1]);
    ETH_NCS_HIGH();
}

/**
 * SFR Bit Field Set
 * @param a
 * @param bitMask
 */
void ENCx24_BFS(encX24J600_registers_t a, uint16_t bitMask)
{
    uint8_t bank;
    bank = a & BANK_MASK;
    if(bank != UNBANKED)
    {
        ENCx24_BankselSPI(a);
        ETH_NCS_LOW();
        ETH_WRITE8(bfs_inst | (a & SFR_MASK));
    }
    else
    {
        ETH_NCS_LOW();
        ETH_WRITE8(bfsu_inst);
        ETH_WRITE8(a);
    }
    ETH_WRITE8(bitMask); //1s are set, 0s unaffected :logical OR
    ETH_WRITE8(bitMask>>8);
    ETH_NCS_HIGH();
}

/**
 * SFR Bit Field Clear
 * @param a
 * @param bitMask
 */
void ENCx24_BFC(encX24J600_registers_t a, uint16_t bitMask)
{
    uint8_t bank;
    bank = a & BANK_MASK;
    if(bank != UNBANKED)
    {
        ENCx24_BankselSPI(a);
        ETH_NCS_LOW();
        ETH_WRITE8(bfc_inst | (a & SFR_MASK));
    }
    else
    {
        ETH_NCS_LOW();
        ETH_WRITE8(bfcu_inst);
        ETH_WRITE8(a);
    }
    ETH_WRITE8(bitMask); ////1s are cleared, 0s unaffected :logical AND
    ETH_WRITE8(bitMask>>8);
    ETH_NCS_HIGH();
}

/**
 * Read PHY register
 * @param a
 * @return
 */
uint16_t ENCx24_PhyRead(encX24J600_phy_registers_t a)
{
    ENCx24_Write(XJ600_MIREGADRL,0x0100|a);
    ENCx24_BFS(XJ600_MICMDL,0x0001);//set the read flag
    while(ENCx24_Read(XJ600_MISTATL)& 0x0001); //wait for the busy flag to clear
    ENCx24_BFC(XJ600_MICMDL,0x0001);//clear the read flag
    return ENCx24_Read(XJ600_MIRDL);
}

/**
 * Write PHY register
 * @param a
 * @param data
 */
void ENCx24_PHYWrite(encX24J600_phy_registers_t a, uint16_t data)
{
    ENCx24_Write(XJ600_MIREGADRL, 0x0100|a);
    ENCx24_Write(XJ600_MIWRL, data);
    while(ENCx24_Read(XJ600_MISTATL)& 0x0001); //wait for the busy flag to clear
}

/**
 * Read 1 byte of data from the RX Buffer
 * @return
 */
uint8_t ETH_Read8(void)
{
    uint8_t ret;
    if(rxPacketStatusVector.byteCount >= sizeof(ret))
    {
        ETH_NCS_LOW();
        ETH_WRITE8(rrxdata_inst);
        ret = ETH_READ8();
        ETH_NCS_HIGH();
        rxPacketStatusVector.byteCount -= sizeof(ret);
        ethData.error = 0;
        return ret;
    }
    else
    {
        ethData.error = 1;
        return 0;
    }
}

/**
 * Read 2 bytes of data from the RX Buffer
 * @return
 */
uint16_t ETH_Read16(void)
{
    uint16_t ret;
    if(rxPacketStatusVector.byteCount >= sizeof(ret))
    {
        ETH_NCS_LOW();
        ETH_WRITE8(rrxdata_inst);
        ((uint8_t *)&ret)[1] = ETH_READ8();
        ((uint8_t *)&ret)[0] = ETH_READ8();
        ETH_NCS_HIGH();
        rxPacketStatusVector.byteCount -= sizeof(ret);
        ethData.error = 0;
        return ret;
    }
    else
    {
        ethData.error = 1;
        return 0;
    }
}

/**
 * Read 4 bytes of data from the RX Buffer
 * @return
 */
uint32_t ETH_Read32(void)
{
    uint32_t ret;
    if(rxPacketStatusVector.byteCount >= sizeof(ret))
    {
        ETH_NCS_LOW();
        ETH_WRITE8(rrxdata_inst);
        ((uint8_t *)&ret)[3] = ETH_READ8();
        ((uint8_t *)&ret)[2] = ETH_READ8();
        ((uint8_t *)&ret)[1] = ETH_READ8();
        ((uint8_t *)&ret)[0] = ETH_READ8();
        ETH_NCS_HIGH();
        rxPacketStatusVector.byteCount -= sizeof(ret);
        ethData.error = 0;
        return ret;
    }
    else
    {
        ethData.error = 1;
        return 0;
    }
}
/**
 * Reads block of data from the RX Buffer
 * @param data
 * @param length
 * @return
 */
uint16_t ETH_ReadBlock(void* data, uint16_t length)
{
    uint16_t len = length;
    char *p = data;
    if(rxPacketStatusVector.byteCount)
    {
        if(length > rxPacketStatusVector.byteCount)
        {
            len = rxPacketStatusVector.byteCount;
        }
        rxPacketStatusVector.byteCount -= len;
        ETH_NCS_LOW();
        ETH_WRITE8(rrxdata_inst);
        while(len--) *p++=ETH_READ8();
        ETH_NCS_HIGH();
        ethData.error=0;
        return length;
    }
    else
    {
        ethData.error= 1;
        return 0;
    }
}

/**
 * Write 1 byte of data to buffer
 * @param data
 */
void ETH_Write8(uint8_t data)
{
    ETH_NCS_LOW();
    TXPacketSize += 1;
    ETH_WRITE8(wgpdata_inst);
    ETH_WRITE8(data);
    ETH_NCS_HIGH();
}

/**
 * Write 2 bytes of data to buffer
 * @param data
 */
void ETH_Write16(uint16_t data)
{
    ETH_NCS_LOW();
    TXPacketSize += 2;
    ETH_WRITE8(wgpdata_inst);
    ETH_WRITE8(((uint8_t*) &data)[1]);
    ETH_WRITE8(((uint8_t*) &data)[0]);
    ETH_NCS_HIGH();
}

/**
 * Writes the 3 bytes of data to the TX buffer
 * @param data
 */
void ETH_Write24(uint32_t data)
{
    ETH_NCS_LOW();
    TXPacketSize += 3;
    ETH_WRITE8(wgpdata_inst);
    ETH_WRITE8(((uint8_t*) &data)[2]);
    ETH_WRITE8(((uint8_t*) &data)[1]);
    ETH_WRITE8(((uint8_t*) &data)[0]);
    ETH_NCS_HIGH();
}

/**
 * Write 4 bytes of data to buffer
 * @param data
 */
void ETH_Write32(uint32_t data)
{
    ETH_NCS_LOW();
    TXPacketSize += 4;
    ETH_WRITE8(wgpdata_inst);
    ETH_WRITE8(((uint8_t*) &data)[3]);
    ETH_WRITE8(((uint8_t*) &data)[2]);
    ETH_WRITE8(((uint8_t*) &data)[1]);
    ETH_WRITE8(((uint8_t*) &data)[0]);
    ETH_NCS_HIGH();
}

uint16_t ETH_WriteString(const char *string)
{
    uint16_t length = 0;
    
    ETH_NCS_LOW();
    ETH_WRITE8(wgpdata_inst);
    while(*string)
    {
        ETH_WRITE8(*string++);
        length ++;
    }    
    ETH_NCS_HIGH();
    TXPacketSize += length;
    
    return length;
}

/**
 * Write a block of data to buffer
 * @param data
 * @param len
 */
uint16_t ETH_WriteBlock(const char* data, uint16_t len)   // jira:M8TS-608
{
    const char *p = data;            // jira:M8TS-608
    
    ETH_NCS_LOW();
    TXPacketSize += len;
    ETH_WRITE8(wgpdata_inst);
    while(len--)
    {
        ETH_WRITE8(*p++);
    }
    ETH_NCS_HIGH();

    return len;
}

/**
 * Insert data in between of the TX Buffer
 * @param data
 * @param len
 * @param offset
 */
// go back and add some data... good for inserting the checksum late
void ETH_Insert(char *data, uint16_t len, uint16_t offset)
{
    uint16_t current_tx_pointer = 0;

    current_tx_pointer = ENCx24_Read(XJ600_EGPWRPTL);
    ENCx24_Write(XJ600_EGPWRPTL, offset);

    ETH_NCS_LOW();
    ETH_WRITE8(wgpdata_inst);
    while(len--)
        ETH_WRITE8(*data++);
    ETH_NCS_HIGH();

    ENCx24_Write(XJ600_EGPWRPTL, current_tx_pointer);
}

/**
 *Packet Transmission Request
 */
void ETH_Set_TXRTS(void)
{
    ETH_NCS_LOW();
    ETH_WRITE8(settxrts_inst);
    ETH_NCS_HIGH();
}

/**
 * Packet count decrement
 */
void ETH_SetPktDec(void)
{
    //Packet decrement
    ETH_NCS_LOW();
    ETH_WRITE8(setpktdec_inst);
    ETH_NCS_HIGH();
}

/**
 * RX packet Read pointer
 */
void ETH_SetRXptr(uint16_t address)
{
    //Packet decrement
    ETH_NCS_LOW();
    ETH_WRITE8(wrxrdpt_inst);
    ETH_WRITE8(((uint8_t*) &address)[0]);
    ETH_WRITE8(((uint8_t*) &address)[1]);    
    ETH_NCS_HIGH();
}


uint8_t ETH_EdataRead(encX24J600_registers_t a)
{
    uint8_t v =0;
    ETH_NCS_LOW();
    ETH_WRITE8(0x2C);

    ETH_WRITE8(a);

    v = ETH_READ8();

    ETH_NCS_HIGH();

    return v;
}

void ETH_MACWrite8(encX24J600_registers_t a, uint8_t data)
{
    uint8_t bank;
    bank = a & BANK_MASK;
    if(bank != UNBANKED)
    {
        ENCx24_BankselSPI(a);
        ETH_NCS_LOW();
        a &= SFR_MASK;
        ETH_WRITE8(wcr_inst | (a));
    }
    else
    {
        ETH_NCS_LOW();
        ETH_WRITE8(wcru_inst);
        ETH_WRITE8(a);
    }
    ETH_WRITE8(data);

    ETH_NCS_HIGH();
}

uint8_t ETH_MACRead8(encX24J600_registers_t a)
{
  uint8_t v;
  uint8_t bank;

  bank = a & BANK_MASK;
  if(bank != UNBANKED)
  {
    ENCx24_BankselSPI(a);
    ETH_NCS_LOW();
    ETH_WRITE8(rcr_inst| (a & SFR_MASK));
  }
  else
  {
      ETH_NCS_LOW();
      ETH_WRITE8(rcru_inst);
      ETH_WRITE8(a);
  }
    v = ETH_READ8();
    ETH_NCS_HIGH();

  return v;
}
