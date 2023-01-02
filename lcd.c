#include "lcd.h"
#define _XTAL_FREQ 4000000
//--------------------------------------------------------------
#define rs RC6 //
#define e RC7 //
//--------------------------------------------------------------
void LCD_delay() //
{
int i;
for(i=0;i<19;i++);
}
void sendbyte(unsigned char c, unsigned char mode) //
{
PORTB=c; //
if(mode==0)rs=0;
else rs=1;
e=0;
LCD_delay();
e=1;
//c=0;
}
//--------------------------------------------------------------
void LCD_Init() //
{
 __delay_ms(50); 
sendbyte(0b00110000,0);//on
__delay_ms(50); 

sendbyte(0b00110000,0);//on
__delay_us(40); 

sendbyte(0b00110000,0);//on 
    __delay_us(40);
    
   
  sendbyte(0b00111100,0);//Function set: 8-bit bus mode,0b00111100,0
  //2-line display mode is set (2004 - 4-line), 5x7 dots format
  __delay_us(40);
  
  //sendbyte(0b00000000,0);//
  sendbyte(0b00001100,0);//display on, cursor on, blink on
  __delay_us(40);
  
 //sendbyte(0b00000000,0);//
  sendbyte(0b00000001,0);//
  __delay_ms(2);
  
  
  //sendbyte(0b00000000,0);//
  sendbyte(0b00000111,0);// increment mode, entire shift on
  __delay_us(40);
  
 sendbyte(0b00010100,0);// display shift (cursor shift), right shift
  __delay_us(40);
  
   sendbyte(0b00000010,0);//
   __delay_us(40);
 
   
   sendbyte(0b01000000,0);//sets CGRAM address
   __delay_us(40);
   
   sendbyte(0X06,0);//direction left to right
  
  sendbyte(0b10000000,0);//SET POS LINE 0
}
/*//--------------------------------------------------------------
void LCD_Clear(void)
{
  sendbyte(0x01, 0);
  __delay_us(1500);
}*/
//--------------------------------------------------------------
void LCD_SetPos(unsigned char x, unsigned char y)//
{
switch(y) //
{
case 0:
sendbyte((unsigned char)(x|0x80),0);//
break;
case 1:
sendbyte((unsigned char)((0x40+x)|0x80),0);
break;
}
}
//--------------------------------------------------------------
void LCD_String(char* st)//
{
unsigned char i=0;
while(st[i]!=0) //
{
sendbyte(st[i],1); //
i++;
}
}
//--------------------------------------------------------------