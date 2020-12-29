/*
 *  (c) 2020 Microchip Technology Inc. and its subsidiaries.
 *
 *  Subject to your compliance with these terms,you may use this software and
 *  any derivatives exclusively with Microchip products.It is your responsibility
 *  to comply with third party license terms applicable to your use of third party
 *  software (including open source software) that may accompany Microchip software.
 *
 *  THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
 *  EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
 *  WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
 *  PARTICULAR PURPOSE.
 *
 *  IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 *  INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 *  WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
 *  BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
 *  FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
 *  ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 *  THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 */
 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/TCPIPLibrary/udpv4.h"
#include "mcc_generated_files/TCPIPLibrary/ipv4.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/TCPIPLibrary/udpv4_port_handler_table.h"
#include "mcc_generated_files/TCPIPLibrary/tcpip_types.h"
#include "lcd.h"
#include "udp_demo.h"

/******************************************************************************************************/
                                          /* UDP Demo */
/******************************************************************************************************/



static uint32_t claim_dest_ip = 0;
static uint8_t claim = 0;
static uint8_t idle_pkt_received = 0;
static uint8_t  pot_init = 0;
static uint16_t pot_initial_adcResult;
static uint16_t temp_initial_adcResult;

#define COMMAND 'C'
#define POTENTIOMETER 'P'
#define LISTEN 'L'

#define MAKE_IPV4_ADDRESS(a,b,c,d) ((uint32_t)(((uint32_t)a << 24) | ((uint32_t)b<<16) | ((uint32_t)c << 8) | (uint32_t)d))

typedef struct {   
   char command;
   char action;
}type_cmd;

type_cmd data;
type_cmd idle_packet;

typedef struct
{
    inAddr_t dest_addr;
}UDP_DestIP_t;

UDP_DestIP_t DestIP;

void UDP_Demo_Recv(int length)
{    
    uint32_t dest_ip;    
    char str[32], str1[16], str2[16];
    uint8_t str_len;
    bool started = false;

    // Receive the UDP data
    /* 1. Read the UDP data   */

    UDP_ReadBlock(&data, sizeof(data));
   
    if(data.command== COMMAND)
    {
        switch(data.action){                              
                    /*  Case '1' represents to Toggles Led 1 (D1)  */
            case '1':               
                if(LED_D1_PORT == 0)
                {
                    
                    LED_D1_TRIS = 0;
                    LED_D1_LAT = 1;
                    //                                 LED_D0_PORT=1;
                }
                else
                {
                    LED_D1_TRIS = 0;
                    LED_D1_PORT=0;
                }                            
                break;                          
                
                /*  Case '2' represents to Toggles Led 2 (D2)  */
            case '2':       
                if(LED_D2_PORT == 0)
                {
                    LED_D2_TRIS = 0;
                    LED_D2_PORT=1;
                }
                else
                {
                    LED_D2_TRIS = 0;
                    LED_D2_PORT=0;
                }                        
                break;
                                
                /*  Case '3' represents to Toggles Led 1 (D3)  */
            case '3': 
                if(LED_D3_PORT == 0)
                {
                    LED_D3_TRIS = 0;
                    LED_D3_LAT=1;
                }
                else
                {
                    LED_D3_TRIS = 0;
                    LED_D3_LAT=0;
                }
                break;
                
                /*  Case '4' represents to Toggles Led 4 (D4)  */
            case '4':
                if(LED_D4_PORT == 0)
                {                                 
                    LED_D4_TRIS = 0;
                    LED_D4_LAT=1;
                }
                else
                {                                 
                    LED_D4_TRIS = 0;
                    LED_D4_LAT=0;
                }
                break;
            case 'D':
                LcdClear();
                memset(str,0,sizeof(str));
                memset(str1,0,sizeof(str1));
                memset(str2,0,sizeof(str2));
                dest_ip = UDP_GetDestIP();
                
                str_len = UDP_Read8();
                if(str_len > 16)
                {
                    UDP_ReadBlock(&str1,16);
                    __delay_ms(10);
                    LcdGoto(0,0);
                    WriteLcdString(str1);
                    str_len-= 16;
                    UDP_ReadBlock(&str2,str_len);
                    __delay_ms(10);   
                    LcdGoto(1,0);
                    WriteLcdString(str2);
                }
                else
                {
                    UDP_ReadBlock(&str,str_len);
                    __delay_ms(10);
                    LcdGoto(0,0);
                    WriteLcdString(str);
                }
                break;

         }
    }
}

void DEMO_UDP_Send()
{
    bool started = false;   
    char text[] = "Hello World";
    uint16_t DestPort;
    DestIP.dest_addr.s_addr = MAKE_IPV4_ADDRESS(192,168,0,38);
    DestPort = 65531;

    //Send UDP Packet
    /*     1. Start UDP packet                      */
    started = UDP_Start(DestIP.dest_addr.s_addr, 65531, DestPort);

    if(started==SUCCESS)
    {        
        /*     2. Write UDP packet                  */
        UDP_WriteBlock(&text, sizeof(text));
        
        /*     3. Send UDP packet                   */
        UDP_Send();
        
    }
}

int Button_Press()
{   
    static int8_t debounce = 100;
    static unsigned int buttonState = 0;
    static char buttonPressEnabled = 1;

    if(SWITCH_S1_GetValue() == 0)
    {       
        if(buttonState < debounce)
        {
            buttonState++;
        }
        else if(buttonPressEnabled)
        {
            buttonPressEnabled = 0;
            return 1;
        }
    }
    else if(buttonState > 0 )
    {
        buttonState--;
    }
    else
    {
        buttonPressEnabled = 1;
    }
    return 0;
}

