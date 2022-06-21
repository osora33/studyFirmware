/*
 * TimeCount.c
 *
 * Created: 2022-06-21 오후 3:31:34
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x00;
unsigned char timer0Cnt = 0 ;
SIGNAL(TIMER0_OVF_vect){
	cli();
	TCNT0 = 183;
	timer0Cnt++;
	if(timer0Cnt == 100){
		LED_Data++;
		if(LED_Data > 0xff) LED_Data = 0;
		timer0Cnt = 0;
	}
	sei();
}

int main(void)
{
    DDRC = 0xff;
	TCCR0 = 0x07;
	TCNT0 = 183;
	
	TIMSK = 0x01;
	TIFR |= 1 << TOV0;
	sei();
	
    while (1) 
    {
		PORTC = LED_Data;
    }
}

