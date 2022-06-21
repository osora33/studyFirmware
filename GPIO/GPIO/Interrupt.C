#define F_CPU 7432800UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char count;

SIGNAL(INT0_vect){
	count++;
	PORTA = count;
}

int main(){
	DDRD = 0x00;
	DDRA = 0xff;
	EIMSK = 1 << INT0;		//EIMSK = 0x01;		//INTO È°¼ºÈ­
	EICRA = (1 << ISC01) | (1 << ISC00);	//EICRA = 0x03;		//0b 0000 0000
	sei();
	
	while(1){}
	return 0;
}