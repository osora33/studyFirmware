/*
 * enterLightness.c
 *
 * Created: 2022-06-22 오후 5:04:16
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int Light = 0;
volatile unsigned char Light_flag = 1;

SIGNAL(INT4_vect){
	cli();
	Light = 0;
	Light_flag = 1;
	sei();
}

SIGNAL(INT5_vect){
	cli();
	Light -= 51;
	if(Light < 0){
		Light = 0;
	}
	Light_flag = 1;
	
	sei();
}

SIGNAL(INT6_vect){
	cli();
	Light += 51;
	if(Light > 255){
		Light = 255;
	}
	Light_flag = 1;
	sei();
}

SIGNAL(INT7_vect){
	cli();
	Light = 255;
	Light_flag = 1;
	sei();
}

int main(){
	DDRB = 0x80;
	DDRE = 0x00;
	
	TCCR2 = 0x62;
	TCNT2 = 0x00;
	EICRB = 0xff;
	EIMSK = 0xf0;
	EIFR = 0xf0;
	
	sei();
	
	while(1){
		if(Light_flag){
			OCR2 = Light;
			Light_flag = 0;
		}
	}
}