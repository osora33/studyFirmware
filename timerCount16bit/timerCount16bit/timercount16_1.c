/*
 * timerCount16bit.c
 *
 * Created: 2022-06-22 오전 10:15:27
 * Author : PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x00;

SIGNAL(TIMER1_OVF_vect){
	cli();
	
	LED_Data++;
	
	if(LED_Data > 0x0f){
		LED_Data = 0;
	}
	TCNT1 = 36736;				// 65563(2의16승) - (7372800 / 256(분주비)) -> 타이머 시작점 설정
	sei();
}

int main(void)
{
    DDRC = 0x0f;
	
	TCCR1A = 0x00;				//타이머 카운트를 0~2까지 동작모드를 설정(일반, CTC, PWM)
	TCCR1B |= 1 << CS12;		//분주비 256로 설정
	
	TCNT1 = 36736;				// 65563(2의16승) - (7372800 / 256(분주비)) -> 타이머 시작점 설정
	TIMSK |= 1 << TOIE1;		//타이머/카운터0~2가 발생하는 인터럽트를 개별적으로 허용하는 기능을 수행하는 레지스터
	TIFR |= 1 << TOV1;			//타이머 인터럽트 발생 여부 저장 레지스터
	
	sei();
    while (1) 
    {
		PORTC = LED_Data;
    }
	return 0;
}

