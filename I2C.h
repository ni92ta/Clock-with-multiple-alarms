/* PCF8583
 * File:   I2C.h
 * Author: Никита
 *
 * Created on 4 января 2023 г., 20:03
 */

#ifndef I2C_H
#define	I2C_H
#define SCL TRISC1//
#define SDA TRISC0 //TRISC4
#define SCL_IN RC1 
#define SDA_IN RC0
#define _XTAL_FREQ 3579000
#define dev_addrw 0b10100000 //запись 0b10100000
#define dev_addrr 0b10100001 //чтение 0b10100001
//----------------------------------------
void i2c_start(void);
void i2c_stop (void);
void I2C_SendByte (unsigned char d);
int I2C_ReadByte (void);
int I2C_ReadByte_last (void);

#endif	/* I2C_H */


