/*
 * test1.c
 *
 * Created: 2022-06-17 오전 11:46:06
 *  Author: PKNU
 */
#define F_CPU 7372800
#include <avr/io.h>
#include <util/delay.h>

int main(){
	DDRA = 0xFF;		//portA를 출력으로 설정
	DDRB = 0xFF;		//portB를 출력으로 설정
	DDRC = 0xFF;		//portC를 출력으로 설정
	DDRD = 0xFF;		//portD를 출력으로 설정
	DDRE = 0xFF;		//portE를 출력으로 설정
	DDRF = 0xFF;		//portF를 출력으로 설정
	DDRG = 0xFF;		//portG를 출력으로 설정
	
	while(1){
		PORTA = 0xFF;	//portA의 각 비트에 5V 출력
		PORTB = 0xFF;	//portB의 각 비트에 5V 출력
		PORTC = 0xFF;	//portC의 각 비트에 5V 출력
		PORTD = 0xFF;	//portD의 각 비트에 5V 출력
		PORTE = 0xFF;	//portE의 각 비트에 5V 출력
		PORTF = 0xFF;	//portF의 각 비트에 5V 출력
		PORTG = 0xFF;	//portG의 각 비트에 5V 출력
		
		_delay_ms(1000);
		
		PORTA = 0x00;	//portA의 각 비트에 5V 출력
		PORTB = 0x00;	//portB의 각 비트에 5V 출력
		PORTC = 0x00;	//portC의 각 비트에 5V 출력
		PORTD = 0x00;	//portD의 각 비트에 5V 출력
		PORTE = 0x00;	//portE의 각 비트에 5V 출력
		PORTF = 0x00;	//portF의 각 비트에 5V 출력
		PORTG = 0x00;	//portG의 각 비트에 5V 출력
		
		_delay_ms(1000);
	}
	return 0;
}