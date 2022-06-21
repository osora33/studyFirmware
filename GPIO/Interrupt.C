#define F_CPU 7432800UL
#include <avr/io.h>
#include <avr/interrupt.h>

int main(){
	DDRD = 0x00;
	DDRA = 0xff;
	EIMSK = 0x01;	//INTO È°¼ºÈ­
	EICRA = 0x03;	//0b 0000 0000
	
	return 0;
}