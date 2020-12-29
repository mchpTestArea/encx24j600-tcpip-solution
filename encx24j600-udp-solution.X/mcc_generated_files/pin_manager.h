/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.5
        Device            :  PIC18F87K22
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.20 and above
        MPLAB 	          :  MPLAB X 5.40	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set LCD_CHIP_SELECT aliases
#define LCD_CHIP_SELECT_TRIS                 TRISAbits.TRISA2
#define LCD_CHIP_SELECT_LAT                  LATAbits.LATA2
#define LCD_CHIP_SELECT_PORT                 PORTAbits.RA2
#define LCD_CHIP_SELECT_ANS                  ANCON0bits.ANSEL2
#define LCD_CHIP_SELECT_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define LCD_CHIP_SELECT_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define LCD_CHIP_SELECT_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define LCD_CHIP_SELECT_GetValue()           PORTAbits.RA2
#define LCD_CHIP_SELECT_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define LCD_CHIP_SELECT_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define LCD_CHIP_SELECT_SetAnalogMode()      do { ANCON0bits.ANSEL2 = 1; } while(0)
#define LCD_CHIP_SELECT_SetDigitalMode()     do { ANCON0bits.ANSEL2 = 0; } while(0)

// get/set RA6 procedures
#define RA6_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define RA6_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define RA6_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define RA6_GetValue()              PORTAbits.RA6
#define RA6_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define RA6_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)

// get/set SWITCH_S1 aliases
#define SWITCH_S1_TRIS                 TRISBbits.TRISB0
#define SWITCH_S1_LAT                  LATBbits.LATB0
#define SWITCH_S1_PORT                 PORTBbits.RB0
#define SWITCH_S1_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define SWITCH_S1_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define SWITCH_S1_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define SWITCH_S1_GetValue()           PORTBbits.RB0
#define SWITCH_S1_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define SWITCH_S1_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)

// get/set RB3 procedures
#define RB3_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define RB3_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define RB3_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define RB3_GetValue()              PORTBbits.RB3
#define RB3_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define RB3_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)

// get/set LED_D1 aliases
#define LED_D1_TRIS                 TRISDbits.TRISD0
#define LED_D1_LAT                  LATDbits.LATD0
#define LED_D1_PORT                 PORTDbits.RD0
#define LED_D1_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define LED_D1_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define LED_D1_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define LED_D1_GetValue()           PORTDbits.RD0
#define LED_D1_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define LED_D1_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)

// get/set LED_D2 aliases
#define LED_D2_TRIS                 TRISDbits.TRISD1
#define LED_D2_LAT                  LATDbits.LATD1
#define LED_D2_PORT                 PORTDbits.RD1
#define LED_D2_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define LED_D2_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define LED_D2_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define LED_D2_GetValue()           PORTDbits.RD1
#define LED_D2_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define LED_D2_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)

// get/set LED_D3 aliases
#define LED_D3_TRIS                 TRISDbits.TRISD2
#define LED_D3_LAT                  LATDbits.LATD2
#define LED_D3_PORT                 PORTDbits.RD2
#define LED_D3_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define LED_D3_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define LED_D3_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define LED_D3_GetValue()           PORTDbits.RD2
#define LED_D3_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define LED_D3_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)

// get/set LED_D4 aliases
#define LED_D4_TRIS                 TRISDbits.TRISD3
#define LED_D4_LAT                  LATDbits.LATD3
#define LED_D4_PORT                 PORTDbits.RD3
#define LED_D4_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define LED_D4_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define LED_D4_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define LED_D4_GetValue()           PORTDbits.RD3
#define LED_D4_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define LED_D4_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/