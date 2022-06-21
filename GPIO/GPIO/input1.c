
/*
 * input1.c
 *
 * Created: 2022-06-17 오후 3:20:03
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>

int main(){
	DDRD = 0X00;	//포트 D 입력으로 설정
	DDRA = 0XFF;	//포트 A 출력으로 설정
	while(1){
		PORTA = PIND;
		//if(PIND == 0X01){
			 //PORTA = 0X01;		//포트 D 입력값이 0X01이면 포트 A의 0번비트를 출력
			 //_delay_ms(300);
			 //PORTA = 0X00;
		//}
	}
	
	return 0;
}