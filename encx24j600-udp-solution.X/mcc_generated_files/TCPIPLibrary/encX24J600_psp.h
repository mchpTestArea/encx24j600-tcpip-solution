/**
  Descriptive File Name
	
  Company:
    Microchip Technology Inc.

  File Name:
  encX24J600_psp.h

  Summary:
    This is the header file for encX24J600_psp.c

  Description:
    This header file provides the Parallel Interface API for the encX24J600 devices.

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



#ifndef ENCX24J600_PSP_H
#define	ENCX24J600_PSP_H

#include "encX24J600_types.h"

//SFR addresses for the ENCX24J600 PSP Mode
typedef enum
{
    /* Register map */
/* These are all 8-bit mode */
    ETXSTL 		=0x7e00,
    ETXSTH 		=0x7e01,
    ETXLENL             =0x7e02,
    ETXLENH		=0x7e03,
    ERXSTL		=0x7e04,
    ERXSTH		=0x7e05,
    ERXTAILL            =0x7e06,
    ERXTAILH            =0x7e07,
    ERXHEADL            =0x7e08,
    ERXHEADH            =0x7e09,
    EDMASTL		=0x7e0a,
    EDMASTH		=0x7e0b,
    EDMALENL            =0x7e0c,
    EDMALENH            =0x7e0d,
    EDMADSTL            =0x7e0e,
    EDMADSTH            =0x7e0f,
    EDMACSL		=0x7e10,
    EDMACSH		=0x7e11,
    ETXSTATL            =0x7e12,
    ETXSTATH            =0x7e13,
    ETXWIREL            =0x7e14,
    ETXWIREH            =0x7e15,
    EUDASTL		=0x7e16,
    EUDASTH		=0x7e17,
    EUDANDL		=0x7e18,
    EUDANDH		=0x7e19,
    ESTATL		=0x7e1a,
    ESTATH		=0x7e1b,
    EIRL		=0x7e1c,
    EIRH		=0x7e1d,
    ECON1L		=0x7e1e,
    ECON1H		=0x7e1f,
    /* bank 2 */
    EHT1L		=0x7e20,
    EHT1H		=0x7e21,
    EHT2L		=0x7e22,
    EHT2H		=0x7e23,
    EHT3L		=0x7e24,
    EHT3H		=0x7e25,
    EHT4L		=0x7e26,
    EHT4H		=0x7e27,
    EPMM1L		=0x7e28,
    EPMM1H		=0x7e29,
    EPMM2L		=0x7e2a,
    EPPM2H		=0x7e2b,
    EPMM3L		=0x7e2c,
    EPMM3H		=0x7e2d,
    EPMM4L		=0x7e2e,
    EPMM4H		=0x7e2f,
    EPMCSL		=0x7e30,
    EPMCSH		=0x7e31,
    EPMOL		=0x7e32,
    EPMOH		=0x7e33,
    ERXFCONL            =0x7e34,
    ERXFCONH            =0x7e35,
    /* =0x7e36 - =0x7e3f is dupe of =0x7e16 - =0x7e1f */
    /* bank 3 */
    MACON1L             =0x7e40,
    MACON1H		=0x7e41,
    MACON2L		=0x7e42,
    MACON2H		=0x7e43,
    MABBIPGL            =0x7e44,
    MABBIPGH            =0x7e45,
    MAIPGL		=0x7e46,
    MAIPGH		=0x7e47,
    MACLCONL            =0x7e48,
    MACLCONH            =0x7e49,
    MAMXFLL		=0x7e4a,
    MAMXFLH		=0x7e4b,
    /* =0x7e4c - =0x7e51 reserved */
    MICMDL		=0x7e52,
    MICMDH		=0x7e53,
    MIREGADRL           =0x7e54,
    MIREGADRH           =0x7e55,
    /* =0x7e56 - =0x7e5f is dupe id =0x7e16 - =0x7e1f */
    /* bank 4 */
    MAADR3L		=0x7e60,
    MAADR3H		=0x7e61,
    MAADR2L		=0x7e62,
    MAADR2H		=0x7e63,
    MAADR1L		=0x7e64,
    MAADR1H		=0x7e65,
    MIWRL		=0x7e66,
    MIWRH		=0x7e67,
    MIRDL		=0x7e68,
    MIRDH		=0x7e69,
    MISTATL		=0x7e6a,
    MISTATH		=0x7e6b,
    EPAUSL		=0x7e6c,
    EPAUSH		=0x7e6d,
    ECON2L		=0x7e6e,
    ECON2H		=0x7e6f,
    ERXWML		=0x7e70,
    ERXWMH		=0x7e71,
    EIEL		=0x7e72,
    EIEH		=0x7e73,
    EIDLEDL		=0x7e74,
    EIDLEDH		=0x7e75,
    /* =0x7e76 - =0x7e7f is dupe of =0x7e16 - =0x7e1f ;*/
    /* bank 5 */
    EGPDATA		=0x7e80,
    /* =0x7e81 reserved */
    ERXDATA		=0x7e82,
    /* =0x7e83 reserved */
    EUDADATA            =0x7e84,
    /* =0x7e85 reserved */
    EGPRDPTL            =0x7e86,
    EGPRDPTH            =0x7e87,
    EGPWRPTL            =0x7e88,
    EGPWRPTH            =0x7e89,
    ERXRDPTL            =0x7e8a,
    ERXRDPTH            =0x7e8b,
    ERXWRPTL            =0x7e8c,
    ERXWRPTH            =0x7e8d,
    EUDARDPTL           =0x7e8e,
    EUDARDPTH           =0x7e8f,
    EUDAWRPTL           =0x7e90,
    EUDAWRPTH           =0x7e91,
    /* =0x7e92 - =0x7e9d reserved */
    /* =0x7e9e - =0x7e9f undefined */

    /* offset for a bitset write */
    BITSET		=0x100,
    BITCLR		=0x180
} encX24J600_registers_t;

typedef enum
{
    //SRAM
    rgpdata_inst  = 0b00101000, // SRAM data EGPDATA read
    rrxdata_inst  = 0b00101100, // SRAM data RXDATA read
    rudadata_inst = 0b00110000, // SRAM data UDADATA read
    wgpdata_inst  = 0b00101010, // SRAM writes
    wrxdata_inst  = 0b00101110, //SRAM data write from ERXDATA
    wudadata_inst = 0b00110010  //SRAM data write from EUDADATA
} encX24J600_N_byte_instructions_t;

void encX24_write(encX24J600_registers_t, uint16_t);
uint16_t encX24_read(encX24J600_registers_t);
void encX24_bfs(encX24J600_registers_t, uint8_t);
void encX24_bfc(encX24J600_registers_t, uint8_t);
uint16_t encX24_phy_read(encX24J600_phy_registers_t);
void encX24_phy_write(encX24J600_phy_registers_t, uint16_t);

#endif	/* ENCX24J600_PSP_H */
