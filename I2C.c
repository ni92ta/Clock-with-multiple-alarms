/*PCF8583
 * File:   I2C.c
 * Author: Никита
 *
 * Created on 4 января 2023 г., 20:01
 */
#include <xc.h>
#include "I2C.h"
#define _XTAL_FREQ 3579000
//int result = 0;
//-------------------------------------------------------
void i2c_start(void)
{
SCL = 1;
SDA = 1;
__delay_us(20);
SDA = 0;
__delay_us(20);
SCL = 0;  
}
//-------------------------------------------------------
void i2c_stop (void)
{
SDA = 0;
__delay_us(20);
SCL = 1;
__delay_us(20);
SDA = 1;
__delay_us(20);
}
//-------------------------------------------------------
void I2C_SendByte (unsigned char d)
{
char x;
//unsigned char b;
for (x = 0; x < 8; x ++) { //передача 8 бит данных
__delay_us(20);
if (d&0x80) SDA = 1;//логический 0
else SDA = 0;//логическая 1
__delay_us(20);
SCL = 1;
d <<= 1;
__delay_us(20);
SCL = 0; }
__delay_us(20);
__delay_us(20);
SDA = 1; //готовимся получить ACK бит
SCL = 1;
__delay_us(20);
//b = SDA_IN; //получаем ACK бит
SCL = 0;
SDA = 0;
//return result; //Возвращаем значение бита ACK через функцию  
}
//-------------------------------------------------------
int I2C_ReadByte (void)
{   
char i;
int result = 0;
SDA = 1;
for (i=0; i<8; i++) { //передача 8 бит данных 
   result<<=1;
__delay_us(20);
SCL = 1;
__delay_us(20);
if (SDA_IN) result |= 1;
//else result |= 0;
SCL = 0;
}
SDA = 0;
__delay_us(20);
SCL = 1;
__delay_us(20);
SCL = 0;
__delay_us(20);
return result; //Возвращаем значение бита ACK через функцию 
}
//-------------------------------------------------------
int I2C_ReadByte_last (void)
{
char i;
int result = 0;
SDA = 1;
for (i=0; i<8; i++) { //передача 8 бит данных
    result<<=1;
__delay_us(20);
SCL = 1;
__delay_us(20);
if (SDA_IN) result |=1;
//else result |= 0;
SCL = 0;
}
SDA = 1;
__delay_us(20);
SCL = 1;
__delay_us(20);
SCL = 0;
__delay_us(20);
return result; //Возвращаем значение бита ACK через функцию 
}
//-------------------------------------------------------

