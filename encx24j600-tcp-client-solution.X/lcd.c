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


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lcd.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/mcc.h"


/* 
Function: 
void WriteIOExpd (uint8_t reg, uint8_t data)

Description: 
 * Function used to write a byte to the IO expander
  */
void WriteIOExpd (uint8_t reg, uint8_t data)
{
          LCD_CHIP_SELECT_SetLow();
          SPI1_ExchangeByte(IO_EXPD_ADDR);
          SPI1_ExchangeByte(reg);           // Select the required register
          SPI1_ExchangeByte(data);          // Write the data
          LCD_CHIP_SELECT_SetHigh(); 
}



/* 
Function: 
void WriteLcdCommand(uint8_t cmd)

Description: 
 * Function used to write a command to the LCD screen
  */
void WriteLcdCommand(uint8_t cmd)
{
          WriteIOExpd(GPIO_A,0x60);    //RS LOW -- E HIGH -- LCD Enabled 

          WriteIOExpd(GPIO_B,cmd);     // Write the command on PORT B

          WriteIOExpd(GPIO_A,0x20);    //RS LOW -- E LOW -- LCD Enabled
}



/* 
Function: 
void WriteLcdByte(uint8_t data)

Description: 
 * Function used to write a byte on the LCD screen
  */
void WriteLcdByte(uint8_t data)
{
          WriteIOExpd(GPIO_A,0xE0);    //RS HIGH -- E HIGH -- LCD Enabled --> This is to choose the data register on the LCD

          WriteIOExpd(GPIO_B,data);    //Write the byte on PORT B

          WriteIOExpd(GPIO_A,0xA0);    //RS HIGH -- E LOW -- LCD enabled --> This is to latch the data on the LCD
}



/* 
Function: 
void WriteLcdString(char *data)

Description: 
 * Function used to write a string on the LCD screen
  */
void WriteLcdString(char *data)
{
    uint8_t i=0;
    while(data[i])
    {
        WriteLcdByte(data[i++]);
    }
}



/* 
Function: 
void LcdClear (void)

Description: 
 * Function used to clear the LCD screen
  */
void LcdClear(void)
{
    WriteLcdCommand(0x01);            // 0x01 is the command to clear the LCD Display
    LcdGoto(0,0);
}



/* 
Function: 
void LcdGoto (uint8_t row, uint8_t column)

Description: 
 * Function used to move the LCD cursor
  */
void LcdGoto(uint8_t row, uint8_t column)
{
    if (row<2)
        {
        uint8_t pos = (row == 0) ? (0x80 | column) : (0xC0 | column);       // 0x80 is the start address of Line 1 and 0xC0 for Line 2
        WriteLcdCommand(pos);
        }

}



/* 
Function: 
void LCDInitialization (void)

Description: 
 * Function used to initialize the LCD
  */
void LcdInitialization (void)
{
          WriteIOExpd(IO_DIR_A,0x00);   // Make PORT A as output
          WriteIOExpd(IO_DIR_B,0x00);   // Make PORT B as output

          WriteIOExpd(GPIO_A,0x20);     // Enable VDD for the LCD panel

          __delay_ms(10);      // delay required to correctly initialize the LCD

          WriteLcdCommand(0x3C);

          __delay_ms(10);

          WriteLcdCommand(0x0C);

          __delay_ms(10);

           WriteLcdCommand(0x01); // Clear the display

          __delay_ms(10);

          WriteLcdCommand(0x0C);

          __delay_ms(50);  __delay_ms(50); __delay_ms(30);  // Delay required to let the LCD initialize correctly

          WriteLcdCommand(0x80);

          __delay_ms(1);

          LcdClear();
}