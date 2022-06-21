#define F_CPU 7432800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile int onoff = 0;
int mode = 0;

SIGNAL(INT4_vect){
	if(onoff == 1){
		onoff = 0;
		}else{
		onoff = 1;
	}
}

int main(){
	DDRE = 0x00;
	DDRA = 0xff;
	EIMSK = 1 << INT4;		//EIMSK = 0x01;		//INTO 활성화
	EICRB = 1 << ISC41;
	sei();
	
	while(1){
		if(onoff == 0){
			if(mode == 0){
				PORTA = (PORTA<<1) | 0x01;
				if(PORTA == 0xff) mode = 1;
			}else if(mode == 1){
				PORTA = (PORTA>>1);
				if(PORTA == 0x00) mode = 0;
			}
			_delay_ms(1000);
		}
	}
	return 0;
}