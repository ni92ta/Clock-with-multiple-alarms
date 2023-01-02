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
  char str01[30]={'\0'};
  char str03[7]={'\0'};
  //int str02[25]={ 164, 164, 65 ,161, 80, 169, 164, 75, 65, 46, 46, 46,
  //46, 46, 46, 46,46,46,46,46,46,46,46,46,46};
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
PORTB=c; //
if(mode==0) rs=1;
else rs=0;
e=0;
__delay_ms(5);;
e=1;
}
//------------------------------------------------
 void segchar (unsigned int adc_data)
{ 
switch (adc_data)
  {ut=0;
    case 0:
      if(ut==0){
        PORTCbits.RC4 = 1;  
      }  
      else{
          PORTCbits.RC4 = 0;
      }
for(y=0;y<15;y++)
{
    LCD_SetPos(0+y,1);
      sendbytee(0b00100000,0);
}
      break;
    case 1:
        goto cas2;
        break;
    case 2:
        cas2:
        LCD_SetPos(0,1);
      sendbytee(0b11111111,0);
for(y=0;y<15;y++)
{
    LCD_SetPos(1+y,1);
      sendbytee(0b00100000,0);
}
      break;
    case 3:
        goto cas4;
        break;
    case 4:
        cas4:
        for(t=0;t<2;t++)
        {
            LCD_SetPos(0+t,1);
      sendbytee(0b11111111,0);
        }
for(y=0;y<15;y++)
{
    LCD_SetPos(2+y,1);
      sendbytee(0b00100000,0);
}
      break;
       case 5:
        goto cas6;
        break;
      case 6:
          cas6:
          for(t=0;t<3;t++)
        {
            LCD_SetPos(0+t,1);
      sendbytee(0b11111111,0);
        }
for(y=0;y<15;y++)
{
    LCD_SetPos(3+y,1);
      sendbytee(0b00100000,0);
} 
     break; 
      case 7:
        goto cas8;
        break;
    case 8:
        cas8:
         for(t=0;t<4;t++)
        {
            LCD_SetPos(0+t,1);
      sendbytee(0b11111111,0);
        }
for(y=0;y<15;y++)
{
    LCD_SetPos(4+y,1);
      sendbytee(0b00100000,0);
}
      break;
       case 9:
        goto cas10;
        break;
    case 10:
        cas10:
     for(t=0;t<5;t++)
        {
            LCD_SetPos(0+t,1);
      sendbytee(0b11111111,0);
        }
for(y=0;y<15;y++)
{
    LCD_SetPos(5+y,1);
      sendbytee(0b00100000,0);
}
      break;
       case 11:
        goto cas12;
        break;
      case 12:
          cas12:
       for(t=0;t<6;t++)
        {
            LCD_SetPos(0+t,1);
      sendbytee(0b11111111,0);
        }
for(y=0;y<15;y++)
{
    LCD_SetPos(6+y,1);
      sendbytee(0b00100000,0);
}
      break;
       case 13:
        goto cas14;
        break;
    case 14:
        cas14:
       for(t=0;t<7;t++)
        {
            LCD_SetPos(0+t,1);
      sendbytee(0b11111111,0);
        }
for(y=0;y<15;y++)
{
    LCD_SetPos(7+y,1);
      sendbytee(0b00100000,0);
}
      break;
    case 15:
      goto cas16;
        break;
    case 16:
        cas16:
           for(t=0;t<8;t++)
        {
            LCD_SetPos(0+t,1);
      sendbytee(0b11111111,0);
        }
for(y=0;y<15;y++)
{
    LCD_SetPos(8+y,1);
      sendbytee(0b00100000,0);
}
      break;
       case 17:
        goto cas18;
        break;
    case 18:
        cas18:
           for(t=0;t<9;t++)
        {
            LCD_SetPos(0+t,1);
      sendbytee(0b11111111,0);
        }
for(y=0;y<15;y++)
{
    LCD_SetPos(9+y,1);
      sendbytee(0b00100000,0);
}
      break;
       case 19:
        goto cas20;
        break;
    case 20:
        cas20:
             for(t=0;t<10;t++)
        {
            LCD_SetPos(0+t,1);
      sendbytee(0b11111111,0);
        }
for(y=0;y<15;y++)
{
    LCD_SetPos(10+y,1);
      sendbytee(0b00100000,0);
}
      break;
       case 21:
        goto cas22;
        break;
    case 22:
        cas22:
             for(t=0;t<11;t++)
        {
            LCD_SetPos(0+t,1);
      sendbytee(0b11111111,0);
        }
for(y=0;y<15;y++)
{
    LCD_SetPos(11+y,1);
      sendbytee(0b00100000,0);
}
      break;
       case 23:
        goto cas24;
        break;
    case 24:
        cas24:
                 for(t=0;t<12;t++)
        {
            LCD_SetPos(0+t,1);
      sendbytee(0b11111111,0);
        }
for(y=0;y<15;y++)
{
    LCD_SetPos(12+y,1);
      sendbytee(0b00100000,0);
}
      break;
       case 25:
        goto cas26;
        break;
    case 26:
        cas26:
                  for(t=0;t<13;t++)
        {
            LCD_SetPos(0+t,1);
      sendbytee(0b11111111,0);
        }
for(y=0;y<15;y++)
{
    LCD_SetPos(13+y,1);
      sendbytee(0b00100000,0);
}
      break;
       case 27:
        goto cas28;
        break;
    case 28:
        cas28:
                   for(t=0;t<14;t++)
        {
            LCD_SetPos(0+t,1);
      sendbytee(0b11111111,0);
        }
for(y=0;y<15;y++)
{
    LCD_SetPos(14+y,1);
      sendbytee(0b00100000,0);
}
      break;
      case 29:
        goto cas30;
        break;
    case 30:
        cas30:
                for(t=0;t<16;t++)
        {
            LCD_SetPos(0+t,1);
      sendbytee(0b11111111,0);
        }
      break;
}
 }
//--------------------------------------------------
void main() // 
{
int adc_data_raw = 0; //float adc_data_raw = .0f;
//int adc_data_raw1 = 0;
int adc_data = 0; //
int adc_data2 = 0;
unsigned char ch = 0;
TRISA = 0b00000111; // 
PORTA = 0x00;
TRISC=0X00;
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
while(1)
{//adc_data_raw=0;
   // unsigned int ch;
GO = 1; //
while(GO);
__delay_us(10);

adc_data_raw = (unsigned int)ADRES; //
adc_data = ((float)adc_data_raw * 500 / 255);//(int)adc_data_raw
//adc_data2 =((float)adc_data_raw * 5 / 255 );//(int)adc_data_raw
if (!ch)
{
    ch=0;
LCD_SetPos(0,0);
CHS0 = 1;//
CHS1 = 0;//
CHS2 = 0;//
//adc_data=adc_data2 - 273;
//sprintf(str01,"%.2f V",adc_data);
sendbytee((unsigned char) (adc_data/100)%10+0x30, 0);
sendbytee((unsigned char) (adc_data*10)%10+0x30, 0);
sendbytee((unsigned char)0b00101110 , 0);
sendbytee(((unsigned char) (adc_data*100)%10)+0x30, 0);//100
//sendbytee(((unsigned char) (adc_data*1000)%10)+0x30, 0);//1000
//sendbytee(((unsigned char) (adc_data*10000)%10)+0x30, 0);
sendbytee((unsigned char)0b01000010 , 0);
//segchar(adc_data);//вызов строки состояния напряжения
//__delay_ms(100);

/*
str01[0]= (((adc_data)/10)+0x30);
str01[1]=  ((unsigned char)((adc_data)%10)+0x30);
str01[2]= 0b00101110;// выводим десятичную точку 
str01[3]= (((unsigned char)((adc_data)*100)%10)+0x30);
str01[4]=0b01000010;
LCD_String(str01);
segchar(adc_data);//вызов строки состояния напряжения
//__delay_ms(100);
*/


}
else
{
  ch=0;
LCD_SetPos(7,0);
CHS0 = 0;//
CHS1 = 0;//
CHS2 = 0;//
str03[0]= ( ((adc_data2)/10)+0x30 );
str03[1]= 0b00101110;// выводим десятичную точку
str03[2]= ( ((adc_data2)%10)+0x30 );
str03[3]= ((char)  ((adc_data2)*100) %10+0x30 );
str03[4]=((char)  ((adc_data2)*1000)%10+0x30 );
str03[5]=0b01000001;//вывод буквы А
LCD_String(str03);//вывод значения в массиве в строку 
  //str01[0]=0;
 /// str01[1]=0;
  //str01[3]=0;
}

}
}

  


