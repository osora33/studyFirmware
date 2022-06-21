/*
 * LCD.c
 *
 * Created: 2022-06-20 오후 2:55:06
 * Author : PKNU
 */ 

#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>
#include "Lcd.h"

int main(void)
{
	Byte *str1 = "LCD TEST";
	Byte *str2 = "ATmega 128A";
	DDRA = 0xff;
	DDRG = 0x0f;
	
	Lcd_Init();
	_delay_ms(500);
	Lcd_Clear();
	
    while (1) 
    {
		Lcd_Pos(0, 0);
		Lcd_STR(str1);
		Lcd_Pos(1, 0);
		Lcd_STR(str2);
    }
	
	return 0;
}

