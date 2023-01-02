#ifndef LCD_H
#define LCD_H
//--------------------------------------------------------------
#include <xc.h>
//--------------------------------------------------------------
void LCD_PORT_init();
void LCD_Init();
void LCD_String(char* st);
void LCD_SetPos(unsigned char x, unsigned char y);
//--------------------------------------------------------------
#endif /* LCD_H */