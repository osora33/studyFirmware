﻿/*
 * timerCount16_3.c
 *
 * Created: 2022-06-22 오후 12:19:02
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x08, 0x80};
volatile unsigned char time_s = 0;
volatile unsigned char FND_flag = 0, edge_flag = 0;

SIGNAL(TIMER3_CAPT_vect){
	cli();
	
	unsigned int count_check;
	
	if(edge_flag == 0){
		TCCR3B = 0x05;
		TCNT3 = 0;
		ICR3 = 0;
		edge_flag = 1;
	}else{
		TCCR3B = 0x45;
		count_check = ICR3;
		
		time_s = count_check/7200;
		
		FND_flag = 1;
		edge_flag = 0;
	}
	sei();
}

int main(){
	DDRA = 0xff;
	DDRE = 0x00;
	
	TCCR3A = 0x00;
	TCCR3B = 1 << CS32 | 1 << CS30;		//분주비 1024
	ETIMSK = 0x20;
	ETIFR |= 1 << ICF3;
	
	sei();
	
	PORTA = FND_DATA_TBL[0];
	
	while(1){
		if(FND_flag){
			if(time_s > 15){
				time_s = 15;
			}
			
			PORTA = FND_DATA_TBL[time_s];
			FND_flag = 0;
		}
	}
	return 0;
}