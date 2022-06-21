#define F_CPU 7432800UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int onoff;

SIGNAL(INT4_vect){
	if(onoff == 0xff){
		onoff = 0x00;
	}else{
		onoff = 0xff;
	}
}

int main(){
	DDRE = 0x00;
	DDRA = 0xff;
	EIMSK = 1 << INT4;		//EIMSK = 0x01;		//INTO 활성화
	EICRB = 1 << ISC41;
	sei();
	
	while(1){
		PORTA = onoff;
	}
	return 0;
}