/*
 * File:   newmain.c
 * Author: Никита
 *Часы на pic16f73  и PCF8583
 * Created on 3 января 2020 г., 20:00
 */
#include <xc.h>
#include "newmain.h"
#include "lcd.h"
#include "I2C.h"
//#include "string.h"
//#include "stdio.h"
//#include	<ctype.h>
//#include	<stdlib.h>
//#include	<stdarg.h>
//#include	<conio.h>
//#include	<sys.h>
//#include	<math.h>
//#include	<float.h>

#define _XTAL_FREQ 3579000
#define dev_addrw 0b11010000 //запись 0b10100000
#define dev_addrr 0b11010001 //чтение 0b10100001

 #define rs RB2//
 #define e RB3//

unsigned char t=0;//Флаг нажатия кнопки
 unsigned char alrm;
     unsigned char sece;//единицы секунд
     unsigned char secd;//десятки секунд
     unsigned char sec;//секунды до преобразования
     unsigned char min;//минуты до преобразования
     //unsigned char min_alar;//минуты будильника до преобразования
     unsigned char mine;//единицы минут после преобразования
     unsigned char mind;//десятки минут после преобразования
     //unsigned char mine_alar;//единицы минут будильника после преобразования
     //unsigned char mind_alar;//десятки минут будильника после преобразования     
     unsigned char hour;//часы до преобразования
     //unsigned char hour_alar;//часы будильника до преобразования
     unsigned char houre;//единицы часов после преобразования
     unsigned char hourd;//десятки часов после преобразования
     //unsigned char houre_alar;//единицы часов будильника после преобразования
     //unsigned char hourd_alar;//десятки часов будильника после преобразования     
     unsigned char minee;//переменная для настройки минут 
     //unsigned char houree;//переменная для настройки часов
     //unsigned char minee_alar;//переменная для настройки минут 
     //unsigned char houree_alar;//переменная для настройки часов
     //unsigned char control_2;//переменная для настройки часов
     /*unsigned char Days;//переменная числа до преобразования
     unsigned char Daysset;//переменная для настройки числа
     unsigned char Weekdays;//переменная дня недели до преобразования
     //unsigned char Weekdaysset;//переменная для настройки дня недели
     unsigned char Months;//переменная месяца до преобразования
     unsigned char Monthsset;//переменная для настройки месяца
     unsigned char Years;//переменная года до преобразования
     unsigned char Yearsset;//переменная для настройки года
     unsigned char Days_pre;//переменная числа после преобразования(единицы)
     unsigned char Days_prd;//переменная числа после преобразования(десятки)
     unsigned char Weekdays_pr;//переменная дня недели после преобразования
     unsigned char Months_pre;//переменная месяца после преобразования(единицы)
     unsigned char Months_prd;//переменная месяца после преобразования(десятки)
     //unsigned char Months_pr;//переменная месяца после преобразования
     unsigned char Years_pre;//переменная года после преобразования(единицы)
     unsigned char Years_prd;//переменная года после преобразования(десятки)*/
//------------------------------------------------
  //char str01[30]={'\0'};
  //char str03[7]={'\0'};
//------------------------------------------------------------------------------
void PCF8583init (void){//инициализация микросхемы
        __delay_ms(10);
   // unsigned char control_3; 
     /*   i2c_start();//отправка посылки СТАРТ
      I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись
      I2C_SendByte (0b00000010);//вызов регистра секунд
      i2c_stop ();//отправка посылки СТОП 
      i2c_start ();//отправка посылки СТАРТ
      I2C_SendByte (dev_addrr);//адрес часовой микросхемы - чтение
      control_3 = I2C_ReadByte_last();//чтение регистра 
      i2c_stop ();//
      if (0b10000000 & control_3 ){  
        */
        
    i2c_start ();//отправка посылки СТАРТ
    I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись
    I2C_SendByte (0b00000000);//вызов регистра секунд (0b00000010)
    I2C_SendByte (0b01000000);//установка секунд 40
    I2C_SendByte (0b00000000);//установка минут 00
    I2C_SendByte (0b11000000);//установка часов 00
    /*I2C_SendByte (0b00000001);//установка числа месяца 15
    I2C_SendByte (0b00000001);//установка дня недели 1
    I2C_SendByte (0b00000001);//установка месяца 1
    I2C_SendByte (0b00100001);//установка года 21
    I2C_SendByte (0b00000001);//установка будильника минуты 1
    I2C_SendByte (0b00000000);//установка будильника часы 0
    I2C_SendByte (0b00000000);//отключение будильника по дню недели 7 бит в единицу
    I2C_SendByte (0b00000000);//отключение будильника по неделе 7 бит в единицу*/
    i2c_stop ();
    
    
    i2c_start ();//отправка посылки СТАРТ
    I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись 
    I2C_SendByte (0b00000111);//вызов регистра clock out
    I2C_SendByte (0b00010000);//включение делителя частоты 1Hz
    i2c_stop ();
     // }
}
//------------------------------------------------------------------------------
unsigned char RTC_ConvertFromDecd(unsigned char c,unsigned char v){//
    unsigned char ch;
    if (v == 1){
      c = c>>4;
       ch = (0b00000011&c);   
    }
    if (v == 0){
    ch = (c >> 4);     
    }
    if (v==2){
          c = c>>4;
       ch = (0b00000001&c);  
    }
    
   /* switch (v){
        case 0:
          ch = (c>>4);  
            break;
                    case 1:
                  c = c>>4;
       ch = (0b00000011&c); 
            break;
                    case 2:
          ch = (0b00001111&c); ;  
            break;
    }
    if (v==1) {
        c = c>>4;
       ch = (0b00000011&c);
    }
    if (v==0){
       ch = (c>>4);  
    }
    if (v==2){
       ch = (0b00001111&c);  
    }*/
    return ch; 
}
//--------------------перевод из двоичного в единицы минут и часов--------------
unsigned char RTC_ConvertFromDec(unsigned char c){//
    unsigned char ch = (0b00001111&c);
    return ch;
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
                0b00001110,
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
//----------------------------------------------------
void delay() //
{
int i;
for(i=0;i<19;i++);
}
//--------------------------------------------------
void digit_out (unsigned char digit, unsigned char str1, unsigned char str2)
{
switch (digit){
    case 0:
LCD_SetPos(str1,0);
sendbyte(0b00000000,1);//0
sendbyte(0b00000001,1);
LCD_SetPos(str2,1);
sendbyte(0b00000010,1);//0
sendbyte(0b00000011,1);
        break;
    case 1:
LCD_SetPos(str1,0);
sendbyte(0b00000001,1);//1
sendbyte(0b00100000,1);
LCD_SetPos(str2,1);
sendbyte(0b00000011,1);//1
sendbyte(0b00000110,1);
        break;
    case 2:
LCD_SetPos(str1,0);
sendbyte(0b00000111,1);//2
sendbyte(0b00000100,1);
LCD_SetPos(str2,1);
sendbyte(0b00000101,1);//2
sendbyte(0b00000110,1);
        break;
    case 3:
LCD_SetPos(str1,0);
sendbyte(0b00000111,1);//3
sendbyte(0b00000100,1);
LCD_SetPos(str2,1);
sendbyte(0b00000110,1);//3
sendbyte(0b00000011,1);
        break;
    case 4:
LCD_SetPos(str1,0);
sendbyte(0b00000010,1);//4
sendbyte(0b00000011,1);
LCD_SetPos(str2,1);
sendbyte(0b00100000,1);//4
sendbyte(0b00000001,1);
        break;
    case 5:
LCD_SetPos(str1,0);
sendbyte(0b00000101,1);//5
sendbyte(0b00000111,1);
LCD_SetPos(str2,1);
sendbyte(0b00000110,1);//5
sendbyte(0b00000100,1);
        break;
    case 6:
LCD_SetPos(str1,0);
sendbyte(0b00000000,1);//6
sendbyte(0b00100000,1);
LCD_SetPos(str2,1);
sendbyte(0b00000101,1);//6
sendbyte(0b00000100,1);
        break;
    case 7:
LCD_SetPos(str1,0);
sendbyte(0b00000111,1);//7
sendbyte(0b00000001,1);
LCD_SetPos(str2,1);
sendbyte(0b00100000,1);//7
sendbyte(0b00000001,1);
        break;
    case 8:
LCD_SetPos(str1,0);
sendbyte(0b00000101,1);//8
sendbyte(0b00000100,1);
LCD_SetPos(str2,1);
sendbyte(0b00000010,1);//8
sendbyte(0b00000011,1);        
        break;
    case 9:
LCD_SetPos(str1,0);
sendbyte(0b00000101,1);//9
sendbyte(0b00000100,1);//
LCD_SetPos(str2,1);
sendbyte(0b00000110,1);//9
sendbyte(0b00000011,1);
        break;        
}  
}
//-----------------------переключение десятков минут----------------------------
/*unsigned char vyb_raz (unsigned char u){
    minee = u;
    minee ++; 
    if (u == 0b00001001) minee = 0b00010000;//если больше 9 записываем в переменную 10
    if (u == 0b00011001) minee = 0b00100000;//если больше 19 записываем в переменную 20
    if (u == 0b00101001) minee = 0b00110000;//если больше 29 записываем в переменную 30
    if (u == 0b00111001) minee = 0b01000000;//если больше 39 записываем в переменную 40
    if (u == 0b01001001) minee = 0b01010000;//если больше 49 записываем в переменную 50
    if (u == 0b01011001) minee = 0b00000000;//если больше 59 то обнуляем   
return minee;
}*/
//-----------------------обработка нажатия кнопки (изменение значения)---------- 
/*void button (unsigned char u,unsigned char i){
  unsigned int butcount=0;
  
  while(!RA0)
  { 
    if(butcount < 400)
    {
      butcount++;
    }
    else
    {
   if (i==1){//настройка минут
    vyb_raz (u);
    i2c_start ();//отправка посылки СТАРТ
    I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись
    I2C_SendByte (0b00000001);//вызов регистра минут
    I2C_SendByte (minee);//установка минут
    i2c_stop (); 
    } 
 break;    
    }
  }
}*/
//--------------------------------------------------
void main() // 
{
//unsigned char ch = 0;
TRISA = 0b00000011;// 
//PORTA = 0b00000000;
TRISC=0b00000011;
TRISB=0b00000000;
ADON = 0;//ADC OFF
PCFG2 = 1;//0100 AN7:AN1 ?????, AN0 ??????, ??????? = Vdd, ?????- = Vss
PCFG1 = 1;
PCFG0 = 0;//1

/*
sendbyte(0b01000000,0);//sets CGRAM address
for (unsigned char x = 0; x <= 7; x++){
    sendbyte(str01[x],1);
      //__delay_us(40);
}
*/
PCF8583init();
LCD_Init();
__delay_us(40);
unsigned char x;
  sendbyte(0b01000000,0);//sets CGRAM address
  for (x = 0; x<= 7; x++){
    sendbyte(str01[x],1);
      //__delay_us(40);
}
   //__delay_us(40);
    for (x = 0; x <= 7; x++){
    sendbyte(str02[x],1);
   //__delay_us(40);
}
   //__delay_us(40);
    for (x = 0; x<= 7; x++){
    sendbyte(str03[x],1);
      //__delay_us(40);
}
   //__delay_us(40);
    for (x = 0; x<= 7; x++){
    sendbyte(str04[x],1);
      //__delay_us(40);
}
   //__delay_us(40);
    for (x = 0; x<= 7; x++){
    sendbyte(str05[x],1);
      //__delay_us(40);
}
   //__delay_us(40);
    for (x = 0; x<= 7; x++){
    sendbyte(str06[x],1);
      //__delay_us(40);
}
   //__delay_us(40);
    for (x = 0; x<= 7; x++){
    sendbyte(str07[x],1);
      //__delay_us(40);
}
   //__delay_us(40);
    for (x = 0; x<= 7; x++){
    sendbyte(str08[x],1);
      //__delay_us(40);
}
   //__delay_ms(10);
//LCD_Init();
//delay();
//__delay_ms(10);
 //PCF8583init();
//__delay_ms(10);
//LCD_Init();
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
  
  i2c_start();//отправка посылки СТАРТ
      I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись
      I2C_SendByte (0b00000000);//вызов регистра секунд (0b00000010)
      i2c_stop ();//отправка посылки СТОП 
      i2c_start ();//отправка посылки СТАРТ
      I2C_SendByte (dev_addrr);//адрес часовой микросхемы - чтение
      sec = I2C_ReadByte();//чтение секунд
      min = I2C_ReadByte();//чтение минут
      hour = I2C_ReadByte_last();//чтение часов
      /*Days = I2C_ReadByte();//чтение числа
      Weekdays = I2C_ReadByte();//чтение дня недели
      Months = I2C_ReadByte();//чтение месяца
      Years = I2C_ReadByte();//чтение года
      min_alar = I2C_ReadByte();//чтение минут будильника
      hour_alar = I2C_ReadByte_last();//чтение часов будильника*/
      i2c_stop (); 
//--------------перевод значения времени в десятичный формат--------------------     
      sece = RTC_ConvertFromDec(sec);
      secd = RTC_ConvertFromDecd(sec,0);
      mine = RTC_ConvertFromDec(min);
      mind = RTC_ConvertFromDecd(min,0);
      houre = RTC_ConvertFromDec(hour);
      hourd = RTC_ConvertFromDecd(hour,1); 
     /* mine_alar = RTC_ConvertFromDec(min_alar);
      mind_alar = RTC_ConvertFromDecd(min_alar,0);
      houre_alar = RTC_ConvertFromDec(hour_alar);
      hourd_alar = RTC_ConvertFromDecd(hour_alar,0);   
      Days_pre = RTC_ConvertFromDec(Days);
      Days_prd = RTC_ConvertFromDecd(Days,1);
      Weekdays_pr = RTC_ConvertFromDec(Weekdays);
      Months_pre = RTC_ConvertFromDec(Months);
      Months_prd = RTC_ConvertFromDecd(Months,2);
      Years_pre = RTC_ConvertFromDec(Years);
      Years_prd = RTC_ConvertFromDecd(Years,0);   */
    
    
   

digit_out(hourd, 0, 0);//hourd
digit_out(houre, 2, 2);//houre
LCD_SetPos(4,0);
sendbyte(0b00101110,1);
LCD_SetPos(4,1);
sendbyte(0b11011111,1);
digit_out(mind, 5, 5);
digit_out(mine, 7, 7);
LCD_SetPos(9,0);
sendbyte(0b00101110,1);
LCD_SetPos(9,1);
sendbyte(0b11011111,1);
digit_out(secd, 10, 10);
digit_out(sece, 12, 12);
LCD_SetPos(14,0);
sendbyte(0b11101101,1);
sendbyte(0b00110101,1);
LCD_SetPos(14,1);
sendbyte(0b01000011,1);
sendbyte(0b10100000,1);
     
//__delay_ms(400);
/*__delay_ms(5000);
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
digit_out(1, 12, 12);*/
//__delay_ms(5000);
/*
digit_out(4, 9, 9);    
digit_out(5, 11, 11); 
digit_out(6, 13, 13);
digit_out(7, 15, 15);*/
  
  /*  LCD_SetPos(4,0);
sendbyte(0b11011111,1);
    __delay_ms(1000);
     LCD_SetPos(5,1);
sendbyte(0b11011111,1);  
__delay_ms(1000);
     LCD_SetPos(5,0);
sendbyte(0b10100000,1);  
__delay_ms(1000);
*/

}
}

/*
 
 * for (digit = 0; digit <= 9; digit++){    
    digit_out(3, 2, 3);
__delay_ms(1000);
}
digit2++;
digit_out(5, 1, 1);
if (digit2 == 9) digit2 = 0;
 
 */
 