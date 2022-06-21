﻿/*
 * timerCount2.c
 *
 * Created: 2022-06-21 오후 3:58:44
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL	
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x01;
unsigned char timer2Cnt = 0, Shift_Flag = 0;

SIGNAL(TIMER2_OVF_vect){
	cli();
	TCNT2 = 184;
	timer2Cnt++;
	
	if(timer2Cnt == 50){
		if(Shift_Flag == 0){
			LED_Data <<= 1;
			if(LED_Data == 0x80){
				Shift_Flag = 1;
			}
		}else{
			LED_Data >>= 1;
			if(LED_Data == 0x01){
				Shift_Flag = 0;
			}
		}
		timer2Cnt = 0;
	}
	sei();
}

int main(){
	DDRC = 0xff;
	TCCR2 = 0x05;
	
	TCNT0 = 184;
	TIMSK = 0x40;
	TIFR |= 1 << TOV2;
	
	sei();
	
	while(1){
		PORTC = LED_Data;
	}
	
	return 0;
}