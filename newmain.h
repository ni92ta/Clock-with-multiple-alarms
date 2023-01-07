#ifndef MAIN_H
#define MAIN_H
//--------------------------------------------------------------
#define _XTAL_FREQ 3579000
#include <xc.h>
// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config CP = OFF         // FLASH Program Memory Code Protection bit (Code protection off)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)

//--------------------------------------------------------------
#include "lcd.h"
#include "I2C.h"
//--------------------------------------------------------------
#endif /* MAIN_H */