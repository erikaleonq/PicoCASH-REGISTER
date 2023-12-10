// Avoid duplication in code
#ifndef _LCD_H_
#define _LCD_H_


// Standard libraries
#include "pico/stdlib.h"
#include "stdio.h"
#include <math.h>

//LCD COMANDS
#define LCD_INIT 0x30
#define LCD_SET 0x28
#define LCD_CLR 0x01             // DB0: clear display
#define LCD_ENTRY_MODE 0x06      // DB2: set entry 
#define LCD_SHOW 0x08         // DB3: turn lcd/cursor on
#define LCD_BLINK 0x0F
#define LCD_CHG_LINE 0xC0 //Cambiar de linea comando SET DDRAM

#define LCD_RS_CMD 0
#define LCD_RS_DATA 1

#define MSB 0
#define LSB 1

void LCDInit();
void LCDconfig();
void PulseEnable();
void ChgLine();
void ClearScreen();
void Write4Bits(uint8_t data, int nibble, int isComand);

void WriteInt(int value);
void WriteStr(char (*array), int len);
void writeInfo(char *info1, int len1, char *info2, int len2);

#endif