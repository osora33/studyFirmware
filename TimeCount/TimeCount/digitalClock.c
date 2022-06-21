/*
 * digitalClock.c
 *
 * Created: 2022-06-21 오후 4:13:53
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7c,0x39,0x5e,0x79,0x71,0x08,0x80};
volatile unsigned char time_s = 0;
unsigned char timer0Cnt = 0;

SIGNAL(TIMER0_COMP_vect){
	cli();
	OCR0 += 72;
	timer0Cnt++;
	
	if(timer0Cnt == 100){
		if(time_s >= 16){
			time_s = 0;
		}else{
			time_s++;
			
		}
		timer0Cnt = 0;
	}
}

int main(){
	DDRC = 0xff;
	
	TCCR0 = 0x07;
	OCR0 = 72;
	TIMSK = 0x02;
	TIFR |= 1 << OCF0;
	
	sei();
	
	while(1){
		PORTC = FND_DATA_TBL[time_s];
	}
	
	return 0;
}