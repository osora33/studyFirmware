/*
 * doorLock.c
 *
 * Created: 2022-06-24 오전 9:38:57
 *  Author: PKNU
 */ 
#define F_CPU 7372800UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include "Lcd.h"

unsigned int DoReMi[8] = {523,587,659,698,783,880,987,1046};
void bell();
bool keyMode = true;
char str[50] = "Insert PW : ";
char password[5] = "1122";
int i = 0;


SIGNAL(INT4_vect){
	cli();
	if(keyMode == true){
		keyMode = false;
	}
	else if(keyMode == false){
		keyMode = true;
		init_keypad();
	}
	_delay_ms(50);
	i = 0;
	bell(0);
	sei();
}

void init_keypad()
{
	DDRC = 0xF8; //0b 1111 1000
	PORTC = 0x07; //0b 0000 0111
}

unsigned char keyscan()
{
	PORTC = 0x08; //0b 0000 1000
	_delay_ms(1);
	if((PINC & 0x07) == 0x01) return '1';
	else if((PINC & 0x07) == 0x02) return '2';
	else if((PINC & 0x07) == 0x04) return '3';
	_delay_ms(10);
	
	PORTC = 0x10;		// 0x10
	_delay_ms(1);
	if((PINC & 0x07) == 0x01) return '4';
	else if((PINC & 0x07) == 0x02) return '5';
	else if((PINC & 0x07) == 0x04) return '6';
	_delay_ms(10);
	
	PORTC = 0x20;		// 0x20
	_delay_ms(1);
	if((PINC & 0x07) == 0x01) return '7';
	else if((PINC & 0x07) == 0x02) return '8';
	else if((PINC & 0x07) == 0x04) return '9';
	_delay_ms(10);
	
	PORTC = 0x40;		// 0x40
	_delay_ms(1);
	if((PINC & 0x07) == 0x01) return '*';
	else if((PINC & 0x07) == 0x02) return '0';
	else if((PINC & 0x07) == 0x04) return '#';
	_delay_ms(10);
	
	return 0;
}

bool str_cmp(char* s1, char* s2){
	bool flag = true;
	for(int i = 0; i < 4; i++){
		if(s1[i] != s2[i]){
			flag = false;
			break;
		}
	}
	
	return flag;
}

void printLcd(char* str){
	Lcd_Clear();
	Lcd_Pos(0, 0);
	Lcd_STR(str);
}

void bell(int i){
	ICR3 = 7372800/DoReMi[i]/16;
	TCCR3A = 1 << COM3A0;
	_delay_ms(150);
	TCCR3A = 0x00;
}

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

void proc_keyMode(){
	unsigned char key;
	char input[5];
	
	key = keyscan();
	
	if(key == 0){
		printLcd(str);
	}else{
		input[i] = key;
		//한번 누른 키가 while문을 한번 돌아도 계속 남아있으므로 초기화해주기
		init_keypad();
		
		if(!str_cmp(str, "Insert PW : ")){
			strcpy(str, "Insert PW : ");
		}
		
		unsigned char tmp[2] = {key, '\0'};
		strcat(str, tmp);
		bell(4);
			
		i++;
			
		//4자리 숫자를 모두 입력했을 때
		if(i >= 4){
			i = 0;
			if(str_cmp(input, password)){
				//패스워드가 일치할 경우
				//LCD출력
				_delay_ms(250);
				strcpy(str, "OPEN DOOR");
					
				//PIEZO출력
				for(int j = 3; j < 6; j++){
					bell(j);
				}
					
				//모터 회전
				for(int j = 0; j< 12; j++){
					PORTD = 0x30;
					_delay_ms(10);
					PORTD = 0x90;
					_delay_ms(10);
					PORTD = 0xC0;
					_delay_ms(10);
					PORTD = 0x60;
					_delay_ms(10);
				}
			}else{
				//패스워드가 일치하지 않을 경우
				strcpy(str, "Retry!!");
				for(int j = 0; j < 5; j++){
					bell(0);
				}
				for(int j = 0; j < 5; j++){
					input[j] = '\0';
				}
			}
		}
		_delay_ms(50);
	}
}

void proc_UARTMode(){
	char input[5];
	
	puts("\n\rInsert PW : ");
	
	while(i < 4){
		char tmp = getch();
		putch(tmp);
		input[i] = tmp;
		i++;
	}
	
	i = 0;
	
	if(str_cmp(password, input)){
		puts("\r\nOPEN DOOR");
		
		//PIEZO출력
		for(int j = 3; j < 6; j++){
			bell(j);
		}
		
		//모터 회전
		for(int j = 0; j< 12; j++){
			PORTD = 0x30;
			_delay_ms(10);
			PORTD = 0x90;
			_delay_ms(10);
			PORTD = 0xC0;
			_delay_ms(10);
			PORTD = 0x60;
			_delay_ms(10);
		}
	}else{
		puts("\n\rTry Again");
		for(int j = 0; j < 5; j++){
			bell(0);
		}
		for(int j = 0; j < 5; j++){
			input[j] = '\0';
		}
	}
	
}

int main()
{
	//LCD 설정
	Lcd_Init();
	_delay_ms(1000);
	Lcd_Clear();
	
	//키패드 설정
	DDRA = 0xff;
	DDRG = 0x0f;
	init_keypad();
	
	//PIEZO 설정
	DDRE = 0x28;		//모터 2, piezo 8
	
	TCCR3B = 1 << WGM33 | 1 << WGM32 | 1 << CS30;
	TCCR3C = 0x00;
	TCNT3 = 0x0000;
	
	//모터 설정
	DDRD = 0xf0;
	PORTE &= ~0x20;
	
	//인터럽트 설정
	EICRB = 0x02;
	EIMSK = 0x10;
	EIFR = 0x10;
	sei();
	
	//UART 설정
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	
	UBRR0H = 0x00;
	UBRR0L = 3;
	
	init_keypad();
	
	while(1){
		if(keyMode){
		//keyPad모드
			proc_keyMode();
		}else{
		//UART모드
			proc_UARTMode();
		}
	}
	return 0;
}