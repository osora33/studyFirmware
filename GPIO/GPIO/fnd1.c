
/*
 * fnd1.c
 *
 * Created: 2022-06-17 오후 4:21:36
 *  Author: PKNU
 */ 
#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>

int main(){
	DDRD = 0X00;
	DDRA = 0XFF;
	int num = 0;
	int tmp = 0;
	
	int arr[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F};
	
	while(1){
		while(tmp == 0){
			PORTA = 0X00;
			tmp = PIND;
		}
		while(tmp >= 2){
			tmp /= 2;
			num++;
		}
		num += tmp;
		
		PORTA = arr[num - 1];
		tmp = num = 0;
	}
	
	return 0;
}