/*
 * timerCount16_2.c
 *
 * Created: 2022-06-22 오전 11:38:54
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x00;

SIGNAL(TIMER3_OVF_vect){
	cli();
	
	TCNT3 = 58336;		// 65563(2의16승) - (7372800 / 1024(분주비)) -> 타이머 시작점 설정
	
	LED_Data++;
	if(LED_Data > 0x0f){
		LED_Data = 0;
	}
	sei();
}

int main(){
	DDRC = 0x0f;
	
	TCCR3A = 0x00;		//타이머 카운트를 0~2까지 동작모드를 설정(일반, CTC, PWM)
	TCCR3B = 1 << CS32 | 1 << CS30;		//분주비 1024
	
	TCNT3 = 58336;		// 65563(2의16승) - (7372800 / 1024(분주비)) -> 타이머 시작점 설정
	ETIMSK = 0x04;		//타이머/카운터 1,3이 발생하는 인터럽트를 개별적으로 허용하는 기능을 수행한다
	ETIFR |= 1 << TOV3;	//타이머 인터럽트 발생 여부 저장 레지스터
	
	sei();
	
	while(1){
		PORTC = LED_Data;
	}
	
	return 0;
}