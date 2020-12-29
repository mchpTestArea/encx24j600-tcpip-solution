/**
  Descriptive File Name
	
  Company:
    Microchip Technology Inc.

  File Name:
    encX24J600_psp.c

  Summary:
    This is the Parallel interface for ENCX24J600 family devices.

  Description:
    This file provides the Parallel Interface Ethernet driver API implementation for
    the ENCX24J600 family devices.

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

#include "io_manager.h"
#include "encX24J600_types.h"
#include "encX24J600_psp.h"
#include "main.h"
#include "ethernet_driver.h"

static uint16_t lastAdd;


mac48Address_t eth_MAC;

static uint8_t read_PSP8(encX24J600_registers_t);
static void write_PSP8(encX24J600_registers_t, uint8_t);

static uint8_t read_PSP8(encX24J600_registers_t addr)
{
    uint8_t val;
    if(addr != lastAdd)
    {
        READ_DISABLE();
        ETH_NCS_HIGH();
        TO_ADDRESS_MODE();
        if (addr>>8 == 1)ETH_PSP_HI_ADD_SET();
        else ETH_PSP_HI_ADD_CLR();
        ADDRESS_LO8 = addr & 0xFF;
        ETH_PSP_AL_HI();
        NOP(); //wait minimum 6.5ns - AL assertion time
        NOP();
        ETH_PSP_AL_LO();
        lastAdd=addr;
    }
    READ_ENABLE();
    TO_READ_DATA_MODE();
    ETH_PSP_EN();
    NOP(); // WE may not need the NOPs in the read
    val = READ_DATA;
    NOP();
    NOP();
    ETH_PSP_DIS();
    //READ_DISABLE();
    return val;
}

static void write_PSP8(encX24J600_registers_t addr, uint8_t data)
{

    if(addr != lastAdd)
    {
        WRITE_DISABLE();
        ETH_NCS_HIGH();
        TO_ADDRESS_MODE();
        if (addr>>8 == 1)ETH_PSP_HI_ADD_SET();
        else ETH_PSP_HI_ADD_CLR();
        ADDRESS_LO8 = addr & 0xFF;
        ETH_PSP_AL_HI();
        NOP();        //wait minimum 6.5ns - AL assertion time
         NOP();
        ETH_PSP_AL_LO();
        lastAdd=addr;
    }
    WRITE_ENABLE();
    TO_WRITE_DATA_MODE();
    WRITE_DATA = data;
    ETH_PSP_EN();
    NOP();
     NOP();
    ETH_PSP_DIS();
}

uint16_t encX24_read(encX24J600_registers_t addr)
{
    return(read_PSP8(addr)| read_PSP8(addr+1)<<8);
}

void encX24_read_block(encX24J600_phy_registers_t addr, uint8_t *data, uint16_t len)
{
 static uint16_t lastAdd;
    uint16_t val,x;
    if(addr != lastAdd)
    {
        READ_DISABLE();
        ETH_NCS_HIGH();
        TO_ADDRESS_MODE();
        if (addr>>8 == 1)ETH_PSP_HI_ADD_SET();
        else ETH_PSP_HI_ADD_CLR();
        ADDRESS_LO8 = addr<<8;
        ETH_PSP_AL_HI();
        ETH_PSP_AL_LO();
        lastAdd=addr;
    }
    READ_ENABLE();
    TO_READ_DATA_MODE();
    for (x=0; x<=len; x++)
    {
        ETH_PSP_EN();
        NOP();
        data[x] = READ_DATA;
        NOP();
        ETH_PSP_DIS();
    }
    READ_DISABLE();
}

void encX24_write(encX24J600_registers_t addr, uint16_t data)
{
    write_PSP8(addr, data);
    write_PSP8(addr+1, data>>8);
}

void encX24_write_block(encX24J600_phy_registers_t addr, void *d, uint16_t len)
{
    uint16_t x;
    uint8_t *data = (uint8_t *)d;
    if(addr != lastAdd)
    {
        WRITE_DISABLE();
        ETH_NCS_HIGH();
        TO_ADDRESS_MODE();
        if (addr>>8 == 1)ETH_PSP_HI_ADD_SET();
        else ETH_PSP_HI_ADD_CLR();
        ADDRESS_LO8 = addr<<8;
        ETH_PSP_AL_HI();
        ETH_PSP_AL_LO();
        lastAdd=addr;
    }
    WRITE_ENABLE();
    TO_WRITE_DATA_MODE();
    for (x=0; x<=len; x++)
    {
        WRITE_DATA = data[x];
        ETH_PSP_EN();
        NOP();
        ETH_PSP_DIS();
    }
    WRITE_DISABLE();
}

void encX24_bfs(encX24J600_registers_t a, uint8_t bitMask)
{
    write_PSP8(a+BITSET,bitMask); //PHY and MAC registers dont include
}

void encX24_bfc(encX24J600_registers_t a, uint8_t bitMask)
{
    write_PSP8(a+BITCLR,bitMask);// PHY and Mac Registers don't include
}

//TODO Showing similarity
uint16_t encX24_phy_read(encX24J600_phy_registers_t a)
{
    encX24_write(MIREGADRL,0x0010|a);
    write_PSP8(MICMDL,0x01);//set the read flag
    while(encX24_read(MISTATL) & 0x01);//wait fotr the busy flag
    write_PSP8(MICMDL,0x00);//clear the read flag
    return encX24_read(MIRDL);
}

void encX24_phy_write(encX24J600_phy_registers_t a, uint16_t data)
{
    encX24_write(MIREGADRL, 0x0010|a);
    encX24_write(MIWRL, data);
    while(encX24_read(MISTATL) & 0x01);//wait fotr the busy flag
}

uint8_t ETH_Read8(void)
{
    uint8_t ret;
    if(rxPacketStatusVector.ByteCount >= sizeof(ret))
    {
        ret=encX24_read(ERXDATA);
        rxPacketStatusVector.ByteCount -= sizeof(ret);
        ethData.error = 0;
        return ret;
    }
    else
    {
        ethData.error = 1;
        return 0;
    }
}

uint16_t ETH_Read16(void)
{
    uint16_t ret;
    if(rxPacketStatusVector.ByteCount >= sizeof(ret))
    {
        ((uint8_t *)&ret)[1]=encX24_read(ERXDATA);
        ((uint8_t *)&ret)[0]=encX24_read(ERXDATA);
        rxPacketStatusVector.ByteCount -= sizeof(ret);
        ethData.error = 0;
        return ret;
    }
    else
    {
        ethData.error = 1;
        return 0;
    }
}

uint32_t ETH_Read32(void)
{
    uint32_t ret;
    if(rxPacketStatusVector.ByteCount >= sizeof(ret))
    {
        ((uint8_t *)&ret)[3]=encX24_read(ERXDATA);
        ((uint8_t *)&ret)[2]=encX24_read(ERXDATA);
        ((uint8_t *)&ret)[1]=encX24_read(ERXDATA);
        ((uint8_t *)&ret)[0]=encX24_read(ERXDATA);
        rxPacketStatusVector.ByteCount -= sizeof(ret);
        ethData.error = 0;
        return ret;
    }
    else
    {
        ethData.error = 1;
        return 0;
    }
}

uint16_t ETH_ReadBlock(uint8_t* data, uint16_t length)
{
    uint16_t x,len;
    if(rxPacketStatusVector.ByteCount)
    {
        if(length > rxPacketStatusVector.ByteCount)
        {
            len = rxPacketStatusVector.ByteCount;
        }
        rxPacketStatusVector.ByteCount -= len;
        encX24_read_block(ERXDATA, data, len);
        ethData.error = 0;
        return length;
    }
    else
    {
        ethData.error = 1;
        return 0;
    }
}

/* Ethernet Write Functions */
/* The ethernet system needs a variety of ways to write to the MAC */
/* By making separate functions at the driver level, the upper layers get smaller */

/**
 * start a packet.
 * If the ethernet transmitter is idle, then start a packet.  Return is true if the packet was started.
 * @return true if packet started.  false if transmitter is busy
 * */

uint16_t TXPacketSize;

void ETH_Write8(uint8_t data)
{
    TXPacketSize += 1;
    encX24_write(EGPDATA,data);
}
void ETH_Write16(uint16_t data)
{
    TXPacketSize += 2;
    encX24_write(EGPDATA,((uint8_t*) &data)[1]);
    encX24_write(EGPDATA,((uint8_t*) &data)[0]);
}

void ETH_Write24(uint24_t data)
{
    TXPacketSize += 3;
    encX24_write(EGPDATA,((uint8_t*) &data)[2]);
    encX24_write(EGPDATA,((uint8_t*) &data)[1]);
    encX24_write(EGPDATA,((uint8_t*) &data)[0]);
}

void ETH_Write32(uint32_t data)
{
    TXPacketSize += 4;
    encX24_write(EGPDATA,((uint8_t*) &data)[3]);
    encX24_write(EGPDATA,((uint8_t*) &data)[2]);
    encX24_write(EGPDATA,((uint8_t*) &data)[1]);
    encX24_write(EGPDATA,((uint8_t*) &data)[0]);
}

uint16_t ETH_WriteBlock(const void* data, uint16_t len)
{
    uint16_t x;
    TXPacketSize += len;
    encX24_write_block(EGPDATA,data,len);
    return len;
}



void eth_set_txrts(void)
{
    encX24_bfs(ECON1L,ECON1_TXRTS);
}

void eth_set_pktdec(void)
{
    //Packet decrement
    encX24_bfs(ECON1L,ECON1_PKTDEC);
}

//// go back and add some data... good for inserting the checksum late
void ETH_Insert(char *data, uint16_t len, uint16_t offset)
{
    uint16_t current_tx_pointer = 0;
    //current_tx_pointer = readSFR(EGPWRPTL);
    current_tx_pointer = encX24_read(EGPWRPTL);
//    printf("Current Pointer:%x  ",encX24_read(EGPWRPTL));
    encX24_write(EGPWRPTL, offset);
//    printf("EGPWRPTL:%x\r\n",encX24_read(EGPWRPTL));
    ETH_NCS_LOW();
    ETH_Write8(wgpdata_inst);
    while(len--)
        ETH_Write8(*data++);
    ETH_NCS_HIGH();

    encX24_write(EGPWRPTL, current_tx_pointer);
//    writeSFR(EGPWRPTL, current_tx_pointer);
//    printf("Post:Current Pointer:%x  ",readSFR(EGPWRPTL));
}
