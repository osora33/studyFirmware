/*
 * LCD.c
 *
 * Created: 2022-06-20 오후 2:55:06
 * Author : PKNU
 */ 

#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Lcd.h"

volatile int stop = 0;

SIGNAL(INT5_vect){
	stop = 1;
}

SIGNAL(INT6_vect){
	stop = 0;
}

int main(void)
{
	Byte str1[15];
	Byte errMsg[16];
	DDRA = 0xff;
	DDRG = 0x0f;
	DDRE = 0x00;
	
	EIMSK = 0x60;
	EICRB = 0x3C;
	sei();

	Lcd_Init();
	_delay_ms(1000);
	Lcd_Clear();

	int i = 2;
	
    while (1) 
    {
		while(i <= 9){
			int j = 1;
			while(j <= 9){
				Lcd_Pos(0, 0);
				if(stop == 0){
					Lcd_Clear();
					sprintf(str1, "gugu %d * %d = %d", i, j, i*j);
					Lcd_STR(str1);
					_delay_ms(1000);
					j++;
				}else{
					strcpy(errMsg, "Int Occurred");
					Lcd_STR(errMsg);
				}
			}
			i++;
		}
    }
	
	return 0;
}

