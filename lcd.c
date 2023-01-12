#include "lcd.h"
#define _XTAL_FREQ 3579000
//--------------------------------------------------------------
#define rs RB2//
#define e RB3//
//--------------------------------------------------------------
void LCD_delay()
{
int i;
for(i=0;i<19;i++);
}
void sendbyteHalf(unsigned char c)
{
c <<= 4;
PORTB &= 0b00001111;
PORTB |= c;
e = 0;
__delay_us(50);
e = 1;
__delay_us(50);
}
//--------------------------------------------------------------
void sendbyte(unsigned char c, unsigned char mode) //
{
unsigned char hc = 0;  
if(mode == 0) rs = 0;
else rs = 1;
hc = c >> 4;
sendbyteHalf(hc); 
sendbyteHalf(c);
}
//--------------------------------------------------------------
void LCD_Init()
{
__delay_ms(50);
  sendbyte(0b00010000, 0);//
  __delay_us(4500);
  sendbyte(0b00010000, 0);//
  __delay_us(4500);
 // sendbyte(0b00100000, 0);
 //__delay_us(200);
  sendbyte(0b00001000, 0);
  __delay_ms(1);

sendbyte(0b00001100,0);
//              ||+---1:Включение, 0:Отключение мигания позиции курсора
//              |+----1:Включение, 0:Отключение курсора
//              +-----1:Включение, 0:Отключение дисплея
__delay_us(37);

sendbyte(0b00000001,0);//очистка дисплея
__delay_ms(2);
sendbyte(0b00000110,0);//direction left to right
//               |+---1:Разрешить, 0:Запретить сдвиг дисплея, двигать курсор
//               +----1:Приращение, 0:Уменьшение курсора
__delay_ms(1);

sendbyte(0b00000111,0);// increment mode, entire shift on
__delay_us(37);
  
sendbyte(0b00010100,0);
//             |+-----1:Сдвиг вправо, 0:Сдвиг влево
//             +------1:Сдвиг дисплея, 0:Сдвиг курсора
__delay_us(37);

sendbyte(0b00000010,0);//Счётчик DDRAM в 0
__delay_ms(2);

sendbyte(0b00000010,0);//Счётчик DDRAM в 0
__delay_ms(2);

sendbyte(0b01000000,0);//Установить адрес CGRAM в 0
__delay_us(37);

}
//--------------------------------------------------------------
/*
void LCD_Init() //
{
__delay_ms(50); 


sendbyte(0b00110000,0);//on 
__delay_us(37);
       
sendbyte(0b00101000,0);
//            ||+-----1:Шрифт 5*10 точек, 0: 5*8 точек
//            |+------1:Две строки, 0:Одна строка
//            +-------1:Интерфейс 8 бит, 0:4 бита
__delay_us(37);
  
sendbyte(0b00001100,0);
//              ||+---1:Включение, 0:Отключение мигания позиции курсора
//              |+----1:Включение, 0:Отключение курсора
//              +-----1:Включение, 0:Отключение дисплея
__delay_us(37);

sendbyte(0b00000001,0);//очистка дисплея
//__delay_ms(2);
   
sendbyte(0b00000111,0);// increment mode, entire shift on
__delay_us(37);
  
sendbyte(0b00010100,0);
//             |+-----1:Сдвиг вправо, 0:Сдвиг влево
//             +------1:Сдвиг дисплея, 0:Сдвиг курсора
__delay_us(37);
  
sendbyte(0b00000110,0);//direction left to right
//               |+---1:Разрешить, 0:Запретить сдвиг дисплея, двигать курсор
//               +----1:Приращение, 0:Уменьшение курсора
__delay_us(37);

sendbyte(0b00000010,0);//Счётчик DDRAM в 0
__delay_ms(2);
  
sendbyte(0b01000000,0);//Установить адрес CGRAM в 0
__delay_us(37);
  
sendbyte(0b10000000,0);//Установить адрес DDRAM в 0
__delay_us(37);
}*/
//--------------------------------------------------------------
void LCD_Clear(void)
{
  sendbyte(0x01, 0);
  __delay_us(1500);
}
//--------------------------------------------------------------
void LCD_SetPos(unsigned char x, unsigned char y)//
{
switch(y) //
{
case 0:
sendbyte((unsigned char)(x | 0x80),0);//
break;
case 1:
sendbyte((unsigned char)((0x40 + x) | 0x80),0);
break;
}
}
//--------------------------------------------------------------
void LCD_String(char* st)//
{
unsigned char i = 0;
while(st[i] != 0) //
{
sendbyte(st[i],1); //
i++;
}
}
//--------------------------------------------------------------
/*
 void sendbyte(unsigned char c, unsigned char mode) //
{
PORTB = c; //
if(mode == 0) rs = 0;
else rs = 1;
e = 0;
LCD_delay();
e = 1;
//c=0;
}
//--------------------------------------------------------------
 */
