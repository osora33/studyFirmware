#define F_CPU 7472800
#include <avr/io.h>
#include <util/delay.h>

int main(){
	DDRA = 0XFF;
	int num = 0XFE;
		
	while (1)
	{
		num = 0XFE;
		PORTA = num;
		_delay_ms(1000);
			
		for(int i = 0; i<8; i++){
			num = (num<<1)|0X01;
			PORTA = num;
			_delay_ms(1000);
		}
		//for(int i = 1; i <= 64; i=i*2){
			//PORTA = 0xFF - i;
			//_delay_ms(1000);
		//}
		
		//for(int i = 1; i<=128; i=i*2){
			//PORTA = i;
			//_delay_ms(1000);
		//}
	
		//PORTA = 0X01;
		//_delay_ms(1000);
		//PORTA = 0x02;
		//_delay_ms(1000);
		//PORTA = 0x04;
		//_delay_ms(1000);
		//PORTA = 0x08;
		//_delay_ms(1000);
	}
	
	return 0;
}