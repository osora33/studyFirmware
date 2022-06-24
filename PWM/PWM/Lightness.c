/*
 * PWM.c
 *
 * Created: 2022-06-22 오후 4:24:30
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    unsigned char Light = 0;
	
	DDRB = 0x10;
	
	TCCR0 = (1 << WGM00) | (1<< COM01) | (1 << COM00) | (1 << CS02) | (1 << CS01);
	TCNT0 = 0x00;
	
    while (1) 
    {
	    for(Light = 0; Light < 255; Light++){
			OCR0 = Light;
			_delay_ms(10);
		}
		for(Light = 255; 0 < Light; Light--){
			OCR0 = Light;
			_delay_ms(10);
		}
    }
	
	return 0;
}

