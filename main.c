/*
 * File:   newmain.c
 * Author: Никита
 *Часы на pic16f73  и PCF8583
 * Created on 3 января 2020 г., 20:00
 */
#include "newmain.h"
#include "lcd.h"
#include "string.h"
#include "stdio.h"
#include	<ctype.h>
#include	<stdlib.h>
#include	<stdarg.h>
#include	<conio.h>
#include	<sys.h>
#include	<math.h>
#include	<float.h>
//------------------------------------------------
  //char str01[30]={'\0'};
  //char str03[7]={'\0'};
//------------------------------------------------------------------------------
void PCF8583init (void){//инициализация микросхемы
        __delay_ms(200);
      unsigned char control_3; 
      /*i2c_start();//отправка посылки СТАРТ
      I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись
      I2C_SendByte (0b00000010);//вызов регистра секунд
      i2c_stop ();//отправка посылки СТОП 
      i2c_start ();//отправка посылки СТАРТ
      I2C_SendByte (dev_addrr);//адрес часовой микросхемы - чтение
      control_3 = I2C_ReadByte_last();//чтение регистра 
      i2c_stop ();//
      if (0b10000000 & control_3 ){  
        
        
    i2c_start ();//отправка посылки СТАРТ
    I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись
    I2C_SendByte (0b00000010);//вызов регистра секунд
    I2C_SendByte (0b01000000);//установка секунд 40
    I2C_SendByte (0b00000000);//установка минут 00
    I2C_SendByte (0b11000000);//установка часов 00
    I2C_SendByte (0b00000001);//установка числа месяца 15
    I2C_SendByte (0b00000001);//установка дня недели 1
    I2C_SendByte (0b00000001);//установка месяца 1
    I2C_SendByte (0b00100001);//установка года 21
    I2C_SendByte (0b00000001);//установка будильника минуты 1
    I2C_SendByte (0b00000000);//установка будильника часы 0
    I2C_SendByte (0b00000000);//отключение будильника по дню недели 7 бит в единицу
    I2C_SendByte (0b00000000);//отключение будильника по неделе 7 бит в единицу
   // i2c_stop (); 
    //i2c_start ();//отправка посылки СТАРТ
   // I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись 
    //I2C_SendByte (0b00001101);//вызов регистра clock out
    I2C_SendByte (0b00000011);//включение делителя частоты 1Hz
    i2c_stop ();
      }*/ 
}
//------------------------------------------------------------------------------
  unsigned char str01[8]={
                0b00011110,
                0b00011110,
                0b00011000,
                0b00011000,
                0b00011000,
                0b00011000,
                0b00011000,
                0b00011000
  };
  unsigned char str02[8]={
                0b00011110,
                0b00011110,
                0b00000110,
                0b00000110,
                0b00000110,
                0b00000110,
                0b00000110,
                0b00000110
  };
  unsigned char str03[8]={
                0b00011000,
                0b00011000,
                0b00011000,
                0b00011000,
                0b00011000,
                0b00011000,
                0b00011110,
                0b00011110
  };
  unsigned char str04[8]={
                0b00000110,
                0b00000110,
                0b00000110,
                0b00000110,
                0b00000110,
                0b00000110,
                0b00011110,
                0b00011110
  };
  unsigned char str05[8]={
                0b00011110,
                0b00011110,
                0b00000110,
                0b00000110,
                0b00000110,
                0b00000110,
                0b00011110,
                0b00011110
  };
  unsigned char str06[8]={
                0b00011111,
                0b00011111,
                0b00011000,
                0b00011000,
                0b00011000,
                0b00011000,
                0b00011111,
                0b00011111
  };
  unsigned char str07[8]={
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00011110,
                0b00001110
  };
  unsigned char str08[8]={
                0b00001111,
                0b00001111,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000,
                0b00000000
  };
//--------------------------------------------------------------
  unsigned int TIM0_count=0;// глобальная переменная для сёта 
  //вхождений в обработчик прерываний
  unsigned char a;
  unsigned char y;
  unsigned char t;
  unsigned char ut=0;
  #define rs RC6 //
  #define e RC7 //
//----------------------------------------------------
void delay() //
{
int i;
for(i=0;i<19;i++);
}

void sendbytee(unsigned char c, unsigned char mode) //
{
PORTB = c; //
if(mode==0) rs=1;
else rs=0;
e=0;
__delay_ms(5);
e=1;
}
//--------------------------------------------------
void digit_out (unsigned char digit, unsigned char str1, unsigned char str2)
{
switch (digit){
    case 0:
LCD_SetPos(str1,0);
sendbytee(0b00000000,0);//0
sendbytee(0b00000001,0);
LCD_SetPos(str2,1);
sendbytee(0b00000010,0);//0
sendbytee(0b00000011,0);
        break;
    case 1:
LCD_SetPos(str1,0);
sendbytee(0b00000001,0);//1
sendbytee(0b00100000,0);
LCD_SetPos(str2,1);
sendbytee(0b00000011,0);//1
sendbytee(0b00000110,0);
        break;
    case 2:
LCD_SetPos(str1,0);
sendbytee(0b00000111,0);//2
sendbytee(0b00000100,0);
LCD_SetPos(str2,1);
sendbytee(0b00000101,0);//2
sendbytee(0b00000110,0);
        break;
    case 3:
LCD_SetPos(str1,0);
sendbytee(0b00000111,0);//3
sendbytee(0b00000100,0);
LCD_SetPos(str2,1);
sendbytee(0b00000110,0);//3
sendbytee(0b00000011,0);
        break;
    case 4:
LCD_SetPos(str1,0);
sendbytee(0b00000010,0);//4
sendbytee(0b00000011,0);
LCD_SetPos(str2,1);
sendbytee(0b00100000,0);//4
sendbytee(0b00000001,0);
        break;
    case 5:
LCD_SetPos(str1,0);
sendbytee(0b00000101,0);//5
sendbytee(0b00000111,0);
LCD_SetPos(str2,1);
sendbytee(0b00000110,0);//5
sendbytee(0b00000100,0);
        break;
    case 6:
LCD_SetPos(str1,0);
sendbytee(0b00000000,0);//6
sendbytee(0b00100000,0);
LCD_SetPos(str2,1);
sendbytee(0b00000101,0);//6
sendbytee(0b00000100,0);
        break;
    case 7:
LCD_SetPos(str1,0);
sendbytee(0b00000111,0);//7
sendbytee(0b00000001,0);
LCD_SetPos(str2,1);
sendbytee(0b00100000,0);//7
sendbytee(0b00000001,0);
        break;
    case 8:
LCD_SetPos(str1,0);
sendbytee(0b00000101,0);//8
sendbytee(0b00000100,0);
LCD_SetPos(str2,1);
sendbytee(0b00000010,0);//8
sendbytee(0b00000011,0);        
        break;
    case 9:
LCD_SetPos(str1,0);
sendbytee(0b00000101,0);//9
sendbytee(0b00000100,0);//
LCD_SetPos(str2,1);
sendbytee(0b00000110,0);//9
sendbytee(0b00000011,0);
        break;        
}  
}
//--------------------------------------------------
void main() // 
{
//unsigned char ch = 0;
TRISA = 0b00000111;// 
PORTA = 0x00;
TRISC=0b00000011;
TRISB=0X00;
ADCS0 = 1;//Fosc/32 частота преобразования
ADCS1 = 0;//Fosc/32 частота преобразования
//OPTION_REG=0x07;// включаем предделитель таймера 1:256
//INTCON=0xA0;// включаем глобальные прерывания
TMR0=0;// заносим 0 в регистр счёта таймера - включается счёт
PCFG2 = 1;//0100 AN7:AN1 ?????, AN0 ??????, ??????? = Vdd, ?????- = Vss
PCFG1 = 0;
PCFG0 = 0;//1

ADON = 1;//ADC On
  sendbyte(0b01000000,0);//sets CGRAM address
  for (unsigned char x = 0;x<=7;x++){
    sendbyte(str01[x],1);
      __delay_us(40);
}
   // __delay_us(40);
    for (unsigned char x=0;x<=7;x++){
    sendbyte(str02[x],1);
      __delay_us(40);
}
   // __delay_us(40);
    for (unsigned char x=0;x<=7;x++){
    sendbyte(str03[x],1);
      __delay_us(40);
}
   // __delay_us(40);
    for (unsigned char x=0;x<=7;x++){
    sendbyte(str04[x],1);
      __delay_us(40);
}
   // __delay_us(40);
    for (unsigned char x=0;x<=7;x++){
    sendbyte(str05[x],1);
      __delay_us(40);
}
   // __delay_us(40);
    for (unsigned char x=0;x<=7;x++){
    sendbyte(str06[x],1);
      __delay_us(40);
}
   // __delay_us(40);
    for (unsigned char x=0;x<=7;x++){
    sendbyte(str07[x],1);
      __delay_us(40);
}
   // __delay_us(40);
    for (unsigned char x=0;x<=7;x++){
    sendbyte(str08[x],1);
      __delay_us(40);
}
   __delay_ms(100);
LCD_Init();
delay();


//------------------------------------------
/*unsigned int l;
LCD_SetPos(6,0);
for(l=0;l<9;l++)
{
    sendbytee(str02[l],0);
    __delay_ms(1);
}
LCD_SetPos(0,1);
for(l=9;l<25;l++)
{
    sendbytee(str02[l],0);
    __delay_ms(1000);
}
sendbytee(0b00000001,1);//очистка дисплея*/
//----------------------------------------
    unsigned char digit;
    unsigned char digit2 = 0;
while(1)
{
digit_out(0, 0, 0);
digit_out(1, 2, 2);
LCD_SetPos(4,0);
sendbytee(0b00101110,0);
LCD_SetPos(4,1);
sendbytee(0b11011111,0);
digit_out(2, 5, 5);
digit_out(3, 7, 7);
LCD_SetPos(9,0);
sendbytee(0b00101110,0);
LCD_SetPos(9,1);
sendbytee(0b11011111,0);
digit_out(4, 10, 10);
digit_out(5, 12, 12);
__delay_ms(5000);
digit_out(6, 0, 0);
digit_out(7, 2, 2);
LCD_SetPos(4,0);
sendbytee(0b00101110,0);
LCD_SetPos(4,1);
sendbytee(0b11011111,0);
digit_out(8, 5, 5);
digit_out(9, 7, 7);
LCD_SetPos(9,0);
sendbytee(0b00101110,0);
LCD_SetPos(9,1);
sendbytee(0b11011111,0);
digit_out(0, 10, 10);
digit_out(1, 12, 12);
__delay_ms(5000);
/*
digit_out(4, 9, 9);    
digit_out(5, 11, 11); 
digit_out(6, 13, 13);
digit_out(7, 15, 15);*/
/*    
for (digit = 0; digit <= 9; digit++){    
    digit_out(digit, 3, 3);
__delay_ms(1000);
}
digit2++;
digit_out(digit2, 1, 1);
if (digit2 == 9) digit2 = 0;
*/


}
}

 
 