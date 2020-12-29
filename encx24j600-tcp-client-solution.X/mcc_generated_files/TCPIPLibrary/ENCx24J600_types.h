/**
  ENCx24J600 Ethernet controller Header File
	
  Company:
    Microchip Technology Inc.

  File Name:
    ENCx24J600_types.h

  Summary:
    Driver implementation for ENCx24J600 family devices.

  Description:
    This file provides the Ethernet driver API implementation for 
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

#ifndef ENCx24J600_TYPES_H
#define	ENCx24J600_TYPES_H

#include "ethernet_driver.h"

// Controller Options

// ENC424J600 config
#define RAMSIZE         		0x6000ul
#define TXSTART                 0x0000ul    // Transmit buffer start
#define TXEND                   0x15FFul
#define RXSTART                 0x1600ul	// Receive buffer start (should be an even memory address)
#define RXEND                 	(RAMSIZE-2)

#define ETH_HEADER_SIZE         14
#define IP_PROTOCOL_POS         23

//ESTAT helpers
#define ESTAT_PHYLINK           0x0100
#define ESTAT_RSTDONE           0x0800
#define ESTAT_PHYDPX            0x0400
#define ESTAT_PHYRDY            0x0200
#define ESTAT_PKTCNT            0x00FF
#define ESTAT_RXBUSY            0x2000
#define ESTAT_CLKRDY            0x1000

//MACON2 helpers
#define MACON2_FULDPX_ON        0x0001
#define MACON2_FULDPX_OFF       0xFFFE



//some EIR helpers
#define EIR_CRYPTEN             0x8000
#define EIR_LINKIF              0x0800
#define EIR_TXIF                0x0008
#define EIR_PKTIF               0x0040
#define EIR_RXABTIF             0x0002
#define EIR_PCFULIF             0x0001

// some ECON1 helpers

#define ECON1_RXEN              0x0001
#define ECON1_TXRTS             0x0002
#define ECON1_DMANOCS           0x0004
#define ECON1_DMACSSD           0x0008
#define ECON1_DMACPY            0x0010
#define ECON1_DMAST             0x0020
#define ECON1_PKTDEC            0x0100
#define ECON1_AESST             0x0800
#define ECON1_HASHLST           0x1000
#define ECON1_HASHOP            0x2000
#define ECON1_HASHEN            0x4000
#define ECON1_MODEXST           0x8000


// some PHCON1 helpers
#define PHCON1_PSLEEP           0x0800 //MASK
#define PHCON1_PWAKE            0xF7FF //MASK


// some ECON2 helpers
#define ECON2_ETHEN             0x8000
#define ECON2_AUTOFC            0x0080
#define ECON2_STRCH             0x4000
#define ECON2_ETHRST            0x0010
#define ECON2_RXRST             0x0020

typedef enum
{
    PHCON1 =  0x00,
    PHSTAT1 = 0x01,
    PHANA   = 0x04,
    PHANLPA = 0x05,
    PHANE   = 0x06,
    PHCON2  = 0x11,
    PHSTAT2 = 0x1B,
    PHSTAT3 = 0x1F
}encX24J600_phy_registers_t;

// Receive Status Vector bit fields
receiveStatusVector_t rxPacketStatusVector;

#endif	/* ENCx24J600_TYPES_H */

