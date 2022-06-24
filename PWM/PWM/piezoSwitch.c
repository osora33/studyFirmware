/*
 * piezoSwitch.c
 *
 * Created: 2022-06-23 오전 10:11:06
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int DoReMi[8] = {523,587,659,698,783,880,987,1046};
volatile unsigned char sound_flag = 1;

SIGNAL(INT0_vect){
	cli();
	
	ICR3 = 7372800/DoReMi[0]/2;
	TCCR3A = 1 << COM3A0;
	sound_flag = 1;
	
	sei();
}

SIGNAL(INT1_vect){
	cli();
	ICR3 = 7372800/DoReMi[1]/2;
	TCCR3A = 1 << COM3A0;
	sound_flag = 1;
	
	sei();
}

SIGNAL(INT2_vect){
	cli();
	ICR3 = 7372800/DoReMi[2]/2;
	TCCR3A = 1 << COM3A0;
	sound_flag = 1;
	
	sei();
}

SIGNAL(INT3_vect){
	cli();
	ICR3 = 7372800/DoReMi[3]/2;
	TCCR3A = 1 << COM3A0;
	sound_flag = 1;
	
	sei();
}

SIGNAL(INT4_vect){
	cli();
	
	ICR3 = 7372800/DoReMi[4]/2;
	TCCR3A = 1 << COM3A0;
	sound_flag = 1;
	
	sei();
}

SIGNAL(INT5_vect){
	cli();
	ICR3 = 7372800/DoReMi[5]/2;
	TCCR3A = 1 << COM3A0;
	sound_flag = 1;
	
	sei();
}

SIGNAL(INT6_vect){
	cli();
	ICR3 = 7372800/DoReMi[6]/2;
	TCCR3A = 1 << COM3A0;
	sound_flag = 1;
	
	sei();
}

SIGNAL(INT7_vect){
	cli();
	ICR3 = 7372800/DoReMi[7]/2;
	TCCR3A = 1 << COM3A0;
	sound_flag = 1;
	
	sei();
}

int main(){
	DDRE = 0x08;
	DDRD = 0x00;
	
	TCCR3A = 0x00;
	TCCR3B = 1 << WGM33 | 1 << WGM32 | 1 << CS30;
	TCCR3C = 0x00;
	TCNT3 = 0x0000;
	
	EICRA = 0xff;
	EICRB = 0xff;
	EIMSK = 0xff;
	EIFR = 0xff;
	
	sei();
	
	while(1){
		if(sound_flag){
			_delay_ms(500);
			TCCR3A = 0x00;
			sound_flag = 0;
		}
	}
}