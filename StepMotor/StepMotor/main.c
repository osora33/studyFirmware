/*
 * StepMotor.c
 *
 * Created: 2022-06-23 오후 3:06:35
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    unsigned char i;
	
	DDRB = 0x20;
	DDRD = 0xf0;
	PORTB &= ~0x20;
	
    while (1) 
    {
		for(i = 0; i< 12; i++){
			PORTD = 0x30;
			_delay_ms(10);
			PORTD = 0x90;
			_delay_ms(10);
			PORTD = 0xC0;
			_delay_ms(10);
			PORTD = 0x60;
			_delay_ms(10);
		}
		_delay_ms(1000);
    }
	return 0;
}

