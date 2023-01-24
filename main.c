/*
 * File:   newmain.c
 * Author: Никита
 *Часы на pic16f73  и DS1307
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
unsigned char alarm_1 = 0b00110000;
unsigned char alarm_2 = 0b00110000;
unsigned char alarm_3 = 0b00110000;
unsigned char alarm_4 = 0b00110001;
unsigned char t=0;//Флаг нажатия кнопки
unsigned char n;//Флаг очистки дисплея
unsigned char alarm_flag;//Флаг включения будильника
unsigned char alarm;
 unsigned char alarm_set;
  unsigned char alarm_number = 0b00110001;
 unsigned char DAY_1 = 0b10101000;//ПН
 unsigned char DAY_2 = 0b01001000;//ВТ
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
     unsigned char hour_alar;//часы будильника до преобразования
     unsigned char min_alar;//минуты будильника до преобразования
     unsigned char houre;//единицы часов после преобразования
     unsigned char hourd;//десятки часов после преобразования
     unsigned char houre_alar = 0b00110000;//единицы часов будильника после преобразования
     unsigned char hourd_alar = 0b00110000;//десятки часов будильника после преобразования     
     unsigned char minee;//переменная для настройки минут 
     unsigned char houree;//переменная для настройки часов
     //unsigned char minee_alar;//переменная для настройки минут 
     //unsigned char houree_alar;//переменная для настройки часов
     //unsigned char control_2;//переменная для настройки часов
     //unsigned char Days;//переменная числа до преобразования
     //unsigned char Daysset;//переменная для настройки числа
     unsigned char Weekdays;//переменная дня недели до преобразования
     unsigned char Weekdaysset;//переменная для настройки дня недели
     unsigned char Weekdays_pr;//переменная дня недели после преобразования
     /*unsigned char Months;//переменная месяца до преобразования
     unsigned char Monthsset;//переменная для настройки месяца
     unsigned char Years;//переменная года до преобразования
     unsigned char Yearsset;//переменная для настройки года
     unsigned char Days_pre;//переменная числа после преобразования(единицы)
     unsigned char Days_prd;//переменная числа после преобразования(десятки)
     
     unsigned char Months_pre;//переменная месяца после преобразования(единицы)
     unsigned char Months_prd;//переменная месяца после преобразования(десятки)
     //unsigned char Months_pr;//переменная месяца после преобразования
     unsigned char Years_pre;//переменная года после преобразования(единицы)
     unsigned char Years_prd;//переменная года после преобразования(десятки)*/
//------------------------------------------------
  //char str01[30]={'\0'};
  //char str03[7]={'\0'};
//------------------------------------------------------------------------------
void DS1307init (void){//инициализация микросхемы
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
    I2C_SendByte (0b01010101);//установка секунд 55
    I2C_SendByte (0b01011001);//установка минут 00
    I2C_SendByte (0b00100011);//установка часов 00  0b00100011
    I2C_SendByte (0b00000110);//установка дня ВС
    /*I2C_SendByte (0b00000001);//установка дня недели 1
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
unsigned char vyb_raz (unsigned char u){
    minee = u;
    minee ++; 
    if (u == 0b00001001) minee = 0b00010000;//если больше 9 записываем в переменную 10
    if (u == 0b00011001) minee = 0b00100000;//если больше 19 записываем в переменную 20
    if (u == 0b00101001) minee = 0b00110000;//если больше 29 записываем в переменную 30
    if (u == 0b00111001) minee = 0b01000000;//если больше 39 записываем в переменную 40
    if (u == 0b01001001) minee = 0b01010000;//если больше 49 записываем в переменную 50
    if (u == 0b01011001) minee = 0b00000000;//если больше 59 то обнуляем   
return minee;
}
//-----------------------переключение десятков часов----------------------------
unsigned char vyb_raz_h (unsigned char u){
    houree = u;
    houree ++;
    if (u == 0b00001001) houree = 0b00010000;//если больше 9 то записываем в переменную 10
    if (u == 0b00011001) houree = 0b00100000;//если больше 19 то записываем в переменную 20
    if (u == 0b00100011) houree = 0b00000000;//если больше 23 то обнуляем
return houree;
}
//-----------------------переключение дня недели----------------------------
/*unsigned char vyb_raz_DAY (unsigned char u){
    houree = u;
    houree ++;
    if (u == 0b00001001) houree = 0b00010000;//если больше 9 то записываем в переменную 10
    if (u == 0b00011001) houree = 0b00100000;//если больше 19 то записываем в переменную 20
    if (u == 0b00100011) houree = 0b00000000;//если больше 23 то обнуляем
return houree;
}*/
//-----------------------обработка нажатия кнопки (изменение значения)---------- 
void button (unsigned char u,unsigned char i){
  unsigned int butcount=0;
  while(!RA0)
  { 
    if(butcount < 4000)
    {
      butcount++;
    }
    else
    {
       
   if (i == 1){//настройка минут
    vyb_raz (u);
    i2c_start ();//отправка посылки СТАРТ
    I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись
    I2C_SendByte (0b00000001);//вызов регистра минут
    I2C_SendByte (minee);//установка минут
    i2c_stop (); 
    } 
    if (i == 2){//настройка часов
    vyb_raz_h (u);
    i2c_start ();//отправка посылки СТАРТ
    I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись
    I2C_SendByte (0b00000010);//вызов регистра часов
    I2C_SendByte (houree);//установка часов
    i2c_stop (); 
    }
       if (i == 3){//настройка дня недели
           //Weekdays = u;
           Weekdays ++;
          // if (Weekdays > 0b00000110) Weekdays = 0;
    i2c_start ();//отправка посылки СТАРТ
    I2C_SendByte (dev_addrw);//адрес часовой микросхемы - запись
    I2C_SendByte (0b00000011);//вызов регистра дня недели
    I2C_SendByte (Weekdays);//установка дня недели
    i2c_stop ();
    }
         if (i == 4){//настройка будильника - часы

             alarm_2 ++;
                if (alarm_1 == 0b00110010 && alarm_2 == 0b00110100){//если часы > 23, то равно 00 часов
                 alarm_1 = 0b00110000;
                 alarm_2 = 0b00110000; 
             }
                if (alarm_1 + alarm_2 > 0b01101010){//если часы > 19, то равно 20 часов
                 alarm_1 = 0b00110010;
                 alarm_2 = 0b00110000; 
             }

             if (alarm_2 > 0b00111001){//если часы > 09, то равно 10 часов
             alarm_1 = 0b00110001;
             alarm_2 = 0b00110000;
             } 
             //hour_alar = (alarm_1<<4) & alarm_2;
    } 
          if (i == 5){//настройка будильника - минуты
            alarm_4 ++;
            if (alarm_4 == 0b00111010) {
                alarm_4 = 0b00110000;
                alarm_3 ++;
            }
            if (alarm_3 > 0b00110101){
                alarm_4 = 0b00110000;
                alarm_3 = 0b00110000;//
            }
             //min_alar = (alarm_3<<4) & alarm_4;          
  
          }
   
   
 break;    
    }
  }
}
//--------------------------------------------------
void Day_Switch (void){
switch (Weekdays){
    case 0:
DAY_1 = 0b10101000;//П
DAY_2 = 0b01001000;//Н
        break;
    case 1:
DAY_1 = 0b01000010;//В
DAY_2 = 0b01010100;//Т
        break;
    case 2:
DAY_1 = 0b01000011;//С
DAY_2 = 0b01010000;//Р
        break;
    case 3:
DAY_1 = 0b10101011;//Ч
DAY_2 = 0b01010100;//Т
        break;
    case 4:
DAY_1 = 0b10101000;//П
DAY_2 = 0b01010100;//Т
        break;    
    case 5:
DAY_1 = 0b01000011;//С
DAY_2 = 0b10100000;//Б
        break;    
    case 6:
DAY_1 = 0b01000010;//В
DAY_2 = 0b01000011;//С
        break;
    Default:
DAY_1 = 0b11111111;//П
DAY_2 = 0b11111111;//Н
Weekdays = 0;
        break;        
}    
}
void lcd_mask (unsigned int o){
    sendbyte(0b10100000,1);//Б
sendbyte(0b01111001,1);//у
sendbyte(0b11100011,1);//д
sendbyte(0b10111000,1);//и
sendbyte(0b10111011,1);//л
sendbyte(0b11000100,1);//ь
sendbyte(0b10111101,1);//н
sendbyte(0b10111000,1);//и
sendbyte(0b10111010,1);//к
LCD_SetPos(14,0);
sendbyte(0b11101101,1);
sendbyte(o,1);
}
//-------------------Настройка времени будильника---
/*void alarm_clock (unsigned char time){
    
}*/
//--------------------------------------------------
void clk_out (void){//
    unsigned int butcount = 0;

 while(!RA1)
  { 
 if(butcount < 4000)
    {
      butcount++;
    }
    else
    {
      LCD_Clear();
  t++;
        if (t > 5) t = 0;//установка флага режима настройки
      break;     
    }
// break;    
    }    
//--------------Первое нажатие настройка минут------
     
    if (t == 1){
button(min,1);
digit_out(mind, 5, 5);
digit_out(mine, 7, 7);
LCD_SetPos(10,1);
sendbyte(0b01001101,1);//М
sendbyte(0b10111000,1);//и
sendbyte(0b10111101,1);//н
sendbyte(0b01111001,1);//у
sendbyte(0b10111111,1);//т
sendbyte(0b11000011,1);//ы
    }
//--------------Второе нажатие настройка часа-------
    if (t == 2){
        n = 0;
button(hour,2);
digit_out(hourd, 0, 0);//hourd
digit_out(houre, 2, 2);//houre
LCD_SetPos(5,1);
//sendbyte(0b11011111,1);
sendbyte(0b10101011,1);//Ч
sendbyte(0b01100001,1);//а
sendbyte(0b01100011,1);//с
sendbyte(0b11000011,1);//ы
    }
    //--------------Третье нажатие настройка дня недели-------
    if (t == 3){
button(Weekdays,3);
sendbyte(0b11100000,1);//Д
sendbyte(0b01100101,1);//е
sendbyte(0b10111101,1);//н
sendbyte(0b11000100,1);//ь
sendbyte(0b00100000,1);//_
sendbyte(0b10111101,1);//н
sendbyte(0b01100101,1);//е
sendbyte(0b11100011,1);//д
sendbyte(0b01100101,1);//е
sendbyte(0b10111011,1);//л
sendbyte(0b10111000,1);//и
Day_Switch ();
LCD_SetPos(14,1);
sendbyte(DAY_1,1);
sendbyte(DAY_2,1);
    }
//--------------Четвёртое нажатие настройка будильника , часы-------
    if (t == 4){
button(hour_alar,4);
        LCD_SetPos(0,0);
sendbyte(0b10100000,1);//Б
sendbyte(0b01111001,1);//у
sendbyte(0b11100011,1);//д
sendbyte(0b10111000,1);//и
sendbyte(0b10111011,1);//л
sendbyte(0b11000100,1);//ь
sendbyte(0b10111101,1);//н
sendbyte(0b10111000,1);//и
sendbyte(0b10111010,1);//к
LCD_SetPos(14,0);
sendbyte(0b11101101,1);
sendbyte(0b11111111,1);
        LCD_SetPos(0,1);
sendbyte(0b10101011,1);//Ч
sendbyte(0b01100001,1);//а
sendbyte(0b01100011,1);//с
sendbyte(0b11000011,1);//ы
        LCD_SetPos(5,1);
        sendbyte(alarm_1,1);
        sendbyte(alarm_2,1);
        
       
      
            
     }
//--------------Пятое нажатие настройка будильника №2-------
    if (t == 5){
        button(alarm_number,5);
        LCD_SetPos(0,0);  
sendbyte(0b10100000,1);//Б
sendbyte(0b01111001,1);//у
sendbyte(0b11100011,1);//д
sendbyte(0b10111000,1);//и
sendbyte(0b10111011,1);//л
sendbyte(0b11000100,1);//ь
sendbyte(0b10111101,1);//н
sendbyte(0b10111000,1);//и
sendbyte(0b10111010,1);//к
LCD_SetPos(14,0);
sendbyte(0b11101101,1);
sendbyte(0b11111111,1);
        LCD_SetPos(0,1);
sendbyte(0b01001101,1);//М
sendbyte(0b10111000,1);//и
sendbyte(0b10111101,1);//н
sendbyte(0b01111001,1);//у
sendbyte(0b10111111,1);//т
sendbyte(0b11000011,1);//ы
        LCD_SetPos(7,1);
        sendbyte(alarm_3,1);
        sendbyte(alarm_4,1);

    }/*
//--------------шестое нажатие настройка будильника №3-------
    if (t == 6){
        alarm_number = 0b00110011;
        lcd_mask (alarm_number);
RA3 = 1;
    }
//--------------Седьмое нажатие настройка будильника №4-------
    if (t == 7){
        alarm_number = 0b00110100;
        lcd_mask (alarm_number);

    }
//--------------Восьмое нажатие настройка будильника №5-------
    if (t == 8){
        alarm_number = 0b00110101;
        lcd_mask (alarm_number);
        RA3 = 0;
    }*/  

//--------------Вывод на дисплей--------------------
if (t == 0){
    Day_Switch ();
    if (Weekdays > 0b00000110) Weekdays = 0;
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
sendbyte(alarm_number,1);
LCD_SetPos(14,1);
sendbyte(DAY_1,1);//
sendbyte(DAY_2,1);//
}
}
//--------------------------------------------------
void main() // 
{
TRISA = 0b00000111;//вход на кнопки
//PORTA = 0b00000000;
TRISC=0b00000011;//линия I2C
TRISB=0b00000000;//линия управления LCD
ADON = 0;//ADC OFF
PCFG2 = 1;//0100 AN7:AN1 ?????, AN0 ??????, ??????? = Vdd, ?????- = Vss
PCFG1 = 1;
PCFG0 = 0;//1



DS1307init();
__delay_us(40);
LCD_Init();
__delay_us(40);
unsigned char x;
  sendbyte(0b01000000,0);//sets CGRAM address
  for (x = 0; x <= 7; x++){
    sendbyte(str01[x],1);
}
   //__delay_us(40);
    for (x = 0; x <= 7; x++){
    sendbyte(str02[x],1);
}
   //__delay_us(40);
    for (x = 0; x <= 7; x++){
    sendbyte(str03[x],1);
}
   //__delay_us(40);
    for (x = 0; x<= 7; x++){
    sendbyte(str04[x],1);
}
   //__delay_us(40);
    for (x = 0; x<= 7; x++){
    sendbyte(str05[x],1);
}
   //__delay_us(40);
    for (x = 0; x<= 7; x++){
    sendbyte(str06[x],1);
}
   //__delay_us(40);
    for (x = 0; x<= 7; x++){
    sendbyte(str07[x],1);
}
   //__delay_us(40);
    for (x = 0; x<= 7; x++){
    sendbyte(str08[x],1);
}

sendbyte(0b00000001,0);//очистка дисплея*/
//----------------------------------------
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
      hour = I2C_ReadByte();//чтение часов
      Weekdays = I2C_ReadByte_last();//чтение дня недели
      i2c_stop (); 
//--------------перевод значения времени в десятичный формат--------------------     
      sece = RTC_ConvertFromDec(sec);
      secd = RTC_ConvertFromDecd(sec,0);
      mine = RTC_ConvertFromDec(min);
      mind = RTC_ConvertFromDecd(min,0);
      houre = RTC_ConvertFromDec(hour);
      hourd = RTC_ConvertFromDecd(hour,1);
      Weekdays = RTC_ConvertFromDec(Weekdays);
      hourd_alar = RTC_ConvertFromDec(hour_alar);
      houre_alar = RTC_ConvertFromDecd(hour_alar,1);

if (Weekdays > 0b00000110) Weekdays = 0;
if (hour == 0 && min == 0 && sec == 0b00000010) alarm_flag = 0;
hour_alar = (((alarm_1 << 4) & 0b00110000)) | (alarm_2 & 0b00001111);// & alarm_2;

min_alar = (((alarm_3 << 4) & 0b00110000)) | (alarm_4 & 0b00001111);// & alarm_2;
     

clk_out ();
if (hour_alar == hour && alarm_flag == 0){
    if (min_alar == min) RA3 = 1;
}
if (!RA2){
    RA3 = 0;
    alarm_flag = 1;
}
}
}

