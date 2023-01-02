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
/*  int str02[8]={0b00001110,
                0b00011111,
                0b00010001,
                0b00010001,
                0b00010001,
                0b00011111,
                0b00011111,
                0b00011111
  };*/
  //--------------------------------------------------------------
  unsigned char str01[8]={
                0b00011111,
                0b00010001,
                0b00010001,
                0b00010001,
                0b00010001,
                0b00010001,
                0b00010001,
                0b00010001
  };
  unsigned char str02[8]={
                0b00010001,
                0b00010001,
                0b00010001,
                0b00010001,
                0b00010001,
                0b00010001,
                0b00010001,
                0b00011111
  };
  unsigned char str03[8]={
                0b00000001,
                0b00000001,
                0b00000001,
                0b00000001,
                0b00000001,
                0b00000001,
                0b00000001,
                0b00000001
  };
  unsigned char str04[8]={
                0b00011111,
                0b00000001,
                0b00000001,
                0b00000001,
                0b00000001,
                0b00000001,
                0b00000001,
                0b00000001
  };
  unsigned char str05[8]={
                0b00011111,
                0b00000001,
                0b00000001,
                0b00000001,
                0b00000001,
                0b00000001,
                0b00000001,
                0b00011111
  };
  unsigned char str06[8]={
                0b00000001,
                0b00000001,
                0b00000001,
                0b00000001,
                0b00000001,
                0b00000001,
                0b00000001,
                0b00011111
  };
  unsigned char str07[8]={
                0b00011111,
                0b00010000,
                0b00010000,
                0b00010000,
                0b00010000,
                0b00010000,
                0b00010000,
                0b00011111
  };
  unsigned char str08[8]={
                0b00011111,
                0b00010001,
                0b00010001,
                0b00010001,
                0b00010001,
                0b00010001,
                0b00010001,
                0b00011111
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
__delay_ms(5);;
e=1;
}
//--------------------------------------------------
void digit_out (unsigned char digit, unsigned char str1, unsigned char str2)
{
switch (digit){
    case 0:
LCD_SetPos(str1,0);
sendbytee(0b00000000,0);//0
LCD_SetPos(str2,1);
sendbytee(0b00000001,0);//0        
        break;
    case 1:
LCD_SetPos(str1,0);
sendbytee(0b00000010,0);//1
LCD_SetPos(str2,1);
sendbytee(0b00000010,0);//1        
        break;
    case 2:
LCD_SetPos(str1,0);
sendbytee(0b00000011,0);//2
LCD_SetPos(str2,1);
sendbytee(0b00000110,0);//2        
        break;
    case 3:
LCD_SetPos(str1,0);
sendbytee(0b00000011,0);//3
LCD_SetPos(str2,1);
sendbytee(0b00000100,0);//3        
        break;
    case 4:
LCD_SetPos(str1,0);
sendbytee(0b00000001,0);//4
LCD_SetPos(str2,1);
sendbytee(0b00000010,0);//4        
        break;
    case 5:
LCD_SetPos(str1,0);
sendbytee(0b00000110,0);//5
LCD_SetPos(str2,1);
sendbytee(0b00000101,0);//5        
        break;
    case 6:
LCD_SetPos(str1,0);
sendbytee(0b00000110,0);//6
LCD_SetPos(str2,1);
sendbytee(0b00000001,0);//6        
        break;
    case 7:
LCD_SetPos(str1,0);
sendbytee(0b00000011,0);//7
LCD_SetPos(str2,1);
sendbytee(0b00000010,0);//7        
        break;
    case 8:
LCD_SetPos(str1,0);
sendbytee(0b00000111,0);//8
LCD_SetPos(str2,1);
sendbytee(0b00000001,0);//8        
        break;
    case 9:
LCD_SetPos(str1,0);
sendbytee(0b00000111,0);//9
LCD_SetPos(str2,1);
sendbytee(0b00000101,0);//9        
        break;        
}  
}
//--------------------------------------------------
void main() // 
{
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
  sendbyte(0b01000000,0);//sets CGRAM address
  for (unsigned char x = 0;x<=7;x++){
    sendbyte(str01[x],1);
}
    for (unsigned char x=0;x<=7;x++){
    sendbyte(str02[x],1);
}
    for (unsigned char x=0;x<=7;x++){
    sendbyte(str03[x],1);
}
    for (unsigned char x=0;x<=7;x++){
    sendbyte(str04[x],1);
}
    for (unsigned char x=0;x<=7;x++){
    sendbyte(str05[x],1);
}
    for (unsigned char x=0;x<=7;x++){
    sendbyte(str06[x],1);
}
    for (unsigned char x=0;x<=7;x++){
    sendbyte(str07[x],1);
}
    for (unsigned char x=0;x<=7;x++){
    sendbyte(str08[x],1);
}
   __delay_us(40);
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

for (digit = 0; digit <= 9; digit++){    
    digit_out(digit, 3, 3);
__delay_ms(1000);
}
digit2++;
digit_out(digit2, 1, 1);
if (digit2 == 9) digit2 = 0;
}

    
    

}

  /*
   sendbytee(0b11111111,0);
sendbytee(0b00000000,0);//1
sendbytee(0b00000001,0);//2
sendbytee(0b00000010,0);//3
sendbytee(0b00000011,0);//4
sendbytee(0b00000100,0);//5
sendbytee(0b00000101,0);//6
sendbytee(0b00000110,0);//7
sendbytee(0b00000111,0);//8
sendbytee(0b11111111,0);
sendbytee(0b11110000,0);
sendbytee(0b11101101,0);*/

/*
 LCD_SetPos(0,0);
sendbytee(0b00000010,0);//1
LCD_SetPos(0,1);
sendbytee(0b00000010,0);//1

LCD_SetPos(2,0);
sendbytee(0b00000011,0);//2
LCD_SetPos(2,1);
sendbytee(0b00000110,0);//2

LCD_SetPos(4,0);
sendbytee(0b00000011,0);//3
LCD_SetPos(4,1);
sendbytee(0b00000100,0);//3

LCD_SetPos(6,0);
sendbytee(0b00000001,0);//4
LCD_SetPos(6,1);
sendbytee(0b00000010,0);//4

LCD_SetPos(7,0);
sendbytee(0b00101110,0);//.
LCD_SetPos(7,1);
sendbytee(0b00101110,0);//.

LCD_SetPos(8,0);
sendbytee(0b00000110,0);//5
LCD_SetPos(8,1);
sendbytee(0b00000101,0);//5

LCD_SetPos(10,0);
sendbytee(0b00000110,0);//6
LCD_SetPos(10,1);
sendbytee(0b00000001,0);//6

LCD_SetPos(11,0);
sendbytee(0b00000011,0);//7
LCD_SetPos(11,1);
sendbytee(0b00000010,0);//7

LCD_SetPos(12,0);
sendbytee(0b00000111,0);//8
LCD_SetPos(12,1);
sendbytee(0b00000001,0);//8

LCD_SetPos(13,0);
sendbytee(0b00000111,0);//9
LCD_SetPos(13,1);
sendbytee(0b00000101,0);//9

LCD_SetPos(15,0);
sendbytee(0b00000000,0);//0
LCD_SetPos(15,1);
sendbytee(0b00000001,0);//0
 */
