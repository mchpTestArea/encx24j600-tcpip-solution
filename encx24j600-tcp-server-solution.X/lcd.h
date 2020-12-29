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


#ifndef LCD_H
#define	LCD_H

#include <stdint.h>

#define IO_EXPD_ADDR 0x40   // SPI address of the IO Expander
#define GPIO_A 0x12          // Address of the GPIOA register
#define GPIO_B 0x13          // Address of the GPIOB register
#define IO_DIR_A 0x00         // Address of the IODIRA register
#define IO_DIR_B 0x01         // Address of the IODIRB register


/* Function to write to the IO expander which in turn talks with the LCD */
void WriteIOExpd (uint8_t reg, uint8_t data);

/* Function to  write a command to the LCD display*/
void WriteLcdCommand(uint8_t cmd);

/* Function to Initialize the LCD display*/
void LcdInitialization (void);

/* Function to write a byte of data to the LCD display*/
void WriteLcdByte(uint8_t data);

/* Function to write a string to the LCD display*/
void WriteLcdString(char *data);

/* Function to move the cursor to a desired location*/
void LcdGoto(uint8_t row, uint8_t column);

/* Function to clear the LCD display*/
void LcdClear(void);

#endif	/* LCD_H */