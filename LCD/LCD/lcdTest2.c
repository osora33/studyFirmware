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
	Byte str1[15];
	DDRA = 0xff;
	DDRG = 0x0f;
	
	Lcd_Init();
	_delay_ms(1000);
	Lcd_Clear();
	_delay_ms(100);
	
    while (1) 
    {
		for(int i = 2; i<=9; i++){
			for(int j = 1; j<=9; j++){
				Lcd_Pos(0, 0);
				sprintf(str1, "%d * %d = %d", i, j, i*j);
				Lcd_STR(str1);
				_delay_ms(1000);
			}
		}
    }
	
	return 0;
}

