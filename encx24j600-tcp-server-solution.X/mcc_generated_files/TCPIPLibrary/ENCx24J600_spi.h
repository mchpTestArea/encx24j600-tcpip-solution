/**
  ENCx24J600_spi Header File

  Company:
    Microchip Technology Inc.

  File Name:
  ENCx24J600_spi.h

  Summary:
    This is the header file for ENCx24J600_spi.c

  Description:
    This header file provides the Serial Interface API for the ENCx24J600 devices.

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


#ifndef ENCx24J600_SPI_H
#define	ENCx24J600_SPI_H

#include "ENCx24J600_types.h"
#include "../drivers/spi_master.h"
#include "../spi1.h"

#define ETH_NCS_HIGH() do{LATB3 = 1;} while(0)  //Use the Ethernet Chip select as per your hardware specification here
#define ETH_NCS_LOW()  do{LATB3 = 0;} while(0)  //Use the Ethernet Chip select as per your hardware specification here
          

#define ETH_READ8()   SPI1_ExchangeByte(0)
#define ETH_WRITE8(a) SPI1_ExchangeByte(a)

#define SFR_BANK0   0x00
#define SFR_BANK1   0x20
#define SFR_BANK2   0x40
#define SFR_BANK3   0x60
#define UNBANKED    0X80
#define SFR_COMMON  0xE0
#define BANK_MASK   0xE0
#define SFR_MASK    0x1F

typedef enum
{
    sfr_bank0 = SFR_BANK0,
    sfr_bank1 = SFR_BANK1,
    sfr_bank2 = SFR_BANK2,
    sfr_bank3 = SFR_BANK3,
    sfr_common = SFR_COMMON
}sfr_bank_t;

//SFR addresses for the ENCx24J600 SPI mode
typedef enum
{
    // Bank 0
    XJ600_ETXSTL      = (SFR_BANK0 | 0x00),
    XJ600_ETXLENL     = (SFR_BANK0 | 0x02),
    XJ600_ERXSTL      = (SFR_BANK0 | 0x04),
    XJ600_ERXTAILL    = (SFR_BANK0 | 0x06),
    XJ600_ERXHEADL    = (SFR_BANK0 | 0x08),
    XJ600_EDMASTL     = (SFR_BANK0 | 0x0A),
    XJ600_EDMALENL    = (SFR_BANK0 | 0x0C),
    XJ600_EDMADSTL    = (SFR_BANK0 | 0x0E),
    XJ600_EDMACSL     = (SFR_BANK0 | 0x10),
    XJ600_ETXSTATL    = (SFR_BANK0 | 0x12),
    XJ600_ETXWIREL    = (SFR_BANK0 | 0x14),

    // Bank 1
    XJ600_EHT1L       = (SFR_BANK1 | 0x00),
    XJ600_EHT2L       = (SFR_BANK1 | 0x02),
    XJ600_EHT3L       = (SFR_BANK1 | 0x04),
    XJ600_EHT4L       = (SFR_BANK1 | 0x06),
    XJ600_EPMM1L      = (SFR_BANK1 | 0x08),
    XJ600_EPMM2L      = (SFR_BANK1 | 0x0A),
    XJ600_EPMM3L      = (SFR_BANK1 | 0x0C),
    XJ600_EPMM4L      = (SFR_BANK1 | 0x0E),
    XJ600_EPMCSL      = (SFR_BANK1 | 0x10),
    XJ600_EPMOL       = (SFR_BANK1 | 0x12),
    XJ600_ERXFCONL    = (SFR_BANK1 | 0x14),

    //Bank 2
    XJ600_MACON1L     = (SFR_BANK2 | 0x00),
    XJ600_MACON2L     = (SFR_BANK2 | 0x02),
    XJ600_MABBIPGL    = (SFR_BANK2 | 0x04),
    XJ600_MAIPGL      = (SFR_BANK2 | 0x06),
    XJ600_MACLCONL    = (SFR_BANK2 | 0x08),
    XJ600_MAMXFLL     = (SFR_BANK2 | 0x0A),
    XJ600_MICMDL      = (SFR_BANK2 | 0x12),
    XJ600_MIREGADRL   = (SFR_BANK2 | 0x14),

    //Bank 3
    XJ600_MAADR3L     = (SFR_BANK3 | 0x00),
    XJ600_MAADR3H     = (SFR_BANK3 | 0x01),
    XJ600_MAADR2L     = (SFR_BANK3 | 0x02),
    XJ600_MAADR2H     = (SFR_BANK3 | 0x03),
    XJ600_MAADR1L     = (SFR_BANK3 | 0x04),
    XJ600_MAADR1H     = (SFR_BANK3 | 0x05),
    XJ600_MIWRL       = (SFR_BANK3 | 0x06),
    XJ600_MIRDL       = (SFR_BANK3 | 0x08),
    XJ600_MISTATL     = (SFR_BANK3 | 0x0A),
    XJ600_EPAUSL      = (SFR_BANK3 | 0x0C),
    XJ600_ECON2L      = (SFR_BANK3 | 0x0E),
    XJ600_ERXWML      = (SFR_BANK3 | 0x10),
    XJ600_EIEL        = (SFR_BANK3 | 0x12),
    XJ600_EIDLEDL     = (SFR_BANK3 | 0x14),

    // unbanked
    XJ600_EGPDATAL     = (UNBANKED | 0x00), // Use the SRAM Instructions
    XJ600_ERXDATAL     = (UNBANKED | 0x02), // Use the SRAM Instructions
    XJ600_EUDADATAL    = (UNBANKED | 0x04), // Use the SRAM Instructions
    XJ600_EGPRDPTL     = (UNBANKED | 0x06),
    XJ600_EGPWRPTL     = (UNBANKED | 0x08),
    XJ600_ERXRDPTL     = (UNBANKED | 0x0A),
    XJ600_ERXWRPTL     = (UNBANKED | 0x0C),
    XJ600_EUDARDPTL    = (UNBANKED | 0x0E),
    XJ600_EUDAWRPTL    = (UNBANKED | 0x10),

    //Following registers are common to all the banks
    XJ600_EUDASTL     = (SFR_COMMON | 0x16),
    XJ600_EUDANDL     = (SFR_COMMON | 0x18),
    XJ600_ESTATL      = (SFR_COMMON | 0x1A),
    XJ600_EIRL        = (SFR_COMMON | 0x1C),
    XJ600_ECON1L      = (SFR_COMMON | 0x1E)
} encX24J600_registers_t;

// spi instruction definitions
// single byte instructions
typedef enum
{
    b0sel_inst     = 0b11000000,
    b1sel_inst     = 0b11000010,
    b2sel_inst     = 0b11000100,
    b3sel_inst     = 0b11000110,
    setethrst_inst = 0b11001010,
    fcdisable_inst = 0b11100000,
    fcsingle_inst  = 0b11100010,
    fcmultiple_inst= 0b11100100,
    fcclear_inst   = 0b11100110,
    setpktdec_inst = 0b11001100,
    dmastop_inst   = 0b11010010,
    dmacksum_inst  = 0b11011000,
    dmacksums_inst = 0b11011010,
    dmacopy_inst   = 0b11011100,
    dmacopys_inst  = 0b11011110,
    settxrts_inst  = 0b11010100,
    enablerx_inst  = 0b11101000,
    disablerx_inst = 0b11101010,
    seteie_inst    = 0b11101100,
    clreie_inst    = 0b11101110
} encX24J600_1_byte_instructions_t;

typedef enum
{
    rbsel_inst = 0b11001000
} encX24J600_2_byte_instructions_t;

typedef enum
{
    rgprdpt_inst  = 0b01100010,
    rrxrdpt_inst  = 0b01100110,
    rgpwrpt_inst  = 0b01101110,
    rrxwrpt_inst  = 0b01110010,
    rudawrpt_inst = 0b01110110,
    wgprdpt_inst  = 0b01100000,
    wrxrdpt_inst  = 0b01100100,
    wgpwrpt_inst  = 0b01101100,
    wrxwrpt_inst  = 0b01110000,
    wudawrpt_inst = 0b01110100
}encX24J600_3_byte_instructions_t;

typedef enum
{

    //banked commands
    rcr_inst      = 0b00000000, // banked register read
    wcr_inst      = 0b01000000, // banked register write

    bfs_inst      = 0b10000000, // banked bit set
    bfc_inst      = 0b10100000, // banked bit clear
    //Unbanked commands
    rcru_inst     = 0b00100000, // unbanked SFR operation
    wcru_inst     = 0b00100010, // unbanked SFR writes
    bfsu_inst     = 0b00100100, //unbaked bit set
    bfcu_inst     = 0b00100110, //unbanked bit clear
    //SRAM
    rgpdata_inst  = 0b00101000, // SRAM data EGPDATA read
    rrxdata_inst  = 0b00101100, // SRAM data RXDATA read
    rudadata_inst = 0b00110000, // SRAM data UDADATA read
    wgpdata_inst  = 0b00101010, // SRAM writes
    wrxdata_inst  = 0b00101110, //SRAM data write from ERXDATA
    wudadata_inst = 0b00110010  //SRAM data write from EUDADATA
} encX24J600_N_byte_instructions_t;


uint16_t ENCx24_Read(encX24J600_registers_t);

uint8_t ETH_EdataRead(encX24J600_registers_t a);

void encX24_read_block(encX24J600_registers_t , uint8_t*, uint8_t);

void ENCx24_Write(encX24J600_registers_t, uint16_t);

void encX24_write_block(encX24J600_registers_t, uint8_t* , uint8_t);

void ENCx24_BFS(encX24J600_registers_t , uint16_t);

void ENCx24_BFC(encX24J600_registers_t , uint16_t);

uint16_t ENCx24_PhyRead(encX24J600_phy_registers_t);

void ENCx24_PHYWrite(encX24J600_phy_registers_t , uint16_t);

uint16_t readSFR(encX24J600_registers_t);

uint8_t ETH_MACRead8(encX24J600_registers_t);

void ETH_MACWrite8(encX24J600_registers_t, uint8_t);

void writeSFR(encX24J600_registers_t, uint16_t);

void ETH_SetPktDec(void);

void ETH_SetRXptr(uint16_t address);

void ETH_Set_TXRTS(void);


#endif	/* ENCx24J600_SPI_H */
