/*
 * IORegister.c
 *
 * Created: 2020-06-12 오후 3:55:32
 *  Author: user
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(){
	
	while(1){
		DDRC = 0x03;	// 0000 0011	(0 -> 입력, 1 -> 출력)
		PORTC = 0x0F;	// 0000 1111
		_delay_ms(500);
		
		PORTC = 0x00;
		_delay_ms(500);
		
		DDRC = 0x0C;	// 0000 1100
		PORTC = 0x0F;	// 0000 1111
		_delay_ms(500);
		
		PORTC = 0x00;
		_delay_ms(500);
	}
}