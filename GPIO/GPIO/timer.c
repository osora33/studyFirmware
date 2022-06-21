
/*
 * timer.c
 *
 * Created: 2022-06-17 오후 5:07:42
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int stop = 0;

SIGNAL(INT5_vect){
	if(stop == 1){
		stop = 0;
	}else{
		stop = 1;
	}
}

int main(){
	DDRA = 0XFF;
	DDRD = 0X10;
	DDRE = 0x00;
	int arr[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F, 0x6f};
	
	int time = 9999;
	int th;
	int hu;
	int te;
	int on;
	
	EIMSK = 1 << INT5;		//EIMSK = 0x01;		//INTO 활성화
	EICRB = (1 << ISC51) | (1 << ISC50);
	sei();
	
	while(time >= 0){
		for(int i = 25; i > 0; i--){
			th = time/1000;
			DDRD = 0X10;
			PORTA = arr[th];
			_delay_ms(1);
			
			hu = (time%1000)/100;
			DDRD = 0X20;
			PORTA = arr[hu];
			_delay_ms(1);
			
			te = (time%100)/10;
			DDRD = 0X40;
			PORTA = arr[te] | 0x80;
			_delay_ms(1);
			
			on = time%10;
			DDRD = 0X80;
			PORTA = arr[on];
			_delay_ms(1);
		}
		if(stop == 0){
			time--;
		}
	}
	
	//while(h != 0){
		//while(m != 0){
			//while(s != 0){
				//while(ms != 0){
					//DDRD = 0X10;
					//for(ms -= 1; ms < 0; ms--){
						//PORTA = arr[ms]; 
					//}
					//ms = 10;
				//}
			//}
		//}
		//PORTA = 0xBF;
	//}
	
	return 0;
}