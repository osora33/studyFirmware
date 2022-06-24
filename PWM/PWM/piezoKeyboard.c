/*
 * uart3.c
 *
 * Created: 2022-06-21 오전 11:46:07
 *  Author: PKNU
 */
#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>

unsigned int DoReMi[8] = {523,587,659,698,783,880,987,1046};
	
void putch(unsigned char data){
	while((UCSR0A & 0x20) == 0);
	UDR0 = data;
	UCSR0A |= 0x20;
}

unsigned char getch(){
	unsigned char data;
	while((UCSR0A & 0x80) == 0);
	data = UDR0;
	UCSR0A |= 0x80;
	return data;
}

void puts(char *str){
	int i = 0;
	
	while(str[i] != '\0'){
		putch(str[i++]);
	}
}

int main(){
	DDRE = 0x08;
	
	TCCR3B = 1 << WGM33 | 1 << WGM32 | 1 << CS30;
	TCCR3C = 0x00;
	TCNT3 = 0x0000;
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	
	UBRR0H = 0x00;
	UBRR0L = 3;
	
	while(1){
		char input = '\0';
		int inputi = 0;
		
		while(!(inputi >= 1 && inputi <= 8)){
			input = getch();
			inputi = input  - 0x30;
		}
		putch(input);
		
		ICR3 = 7372800/DoReMi[inputi-1]/16;
		TCCR3A = 1 << COM3A0;
		_delay_ms(100);
		TCCR3A = 0x00;
	}
	
	return 0;
}