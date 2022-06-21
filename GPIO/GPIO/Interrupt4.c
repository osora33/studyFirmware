//#define F_CPU 7372800UL
//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include <util/delay.h>
//
//volatile unsigned char Shift_flag = 1;
//
//SIGNAL(INT5_vect){
	//cli();
	//Shift_flag = 1;
	//sei();
//}
//
//SIGNAL(INT6_vect){
	//cli();
	//Shift_flag = 2;
	//sei();
//}
//
//int main(void){
	//unsigned char LED_Data = 0x01;
	//
	//DDRA = 0xff;
	//DDRE = 0x00;
	//
	//EIMSK = 0x60;	//인터럽트 5, 6을 허용
	//EICRB = 0x3c;	//인터럽트 5, 6을 하강엣지에서 동작하도록 설정
	////EIFR = 0x60;	//인터럽트 5, 6 플래그를 클리어
	//
	//sei();
	//
	//while(1){
		////포트C로 변수 LED_Data에 있는 데이타를 출력
		//PORTA = LED_Data;
		//if(Shift_flag == 1){			//LED0 ~ LED3으로 이동
			//if(LED_Data == 0x80) LED_Data = 0x01;
			//else LED_Data <<= 1;		//LED_Data값을 왼쪽으로 쉬프트
		//}else if(Shift_flag == 2){		//LED3 ~ LED0으로 이동
			//if(LED_Data == 0x01) LED_Data = 0x80;
			//else LED_Data >>= 1;		//LED_Data값을 오른쪽으로 쉬프트
		//}
		//_delay_ms(1000);
	//}
//}