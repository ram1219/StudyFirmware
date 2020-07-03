/*
 * ex03.c
 *
 * Created: 2020-06-12 오후 4:44:17
 *  Author: user
 */ 
#include <avr/io.h>
#include <util/delay.h>

int main(){
	unsigned char LED_data = 0x01, i;
	DDRC = 0x0F;							// 0000 1111 : 1->출력
	LED_data = 0x01;
	while(1){
				
		for(i = 0; i < 3; i++){
			PORTC = LED_data;				// LED_data 값 출력	= 0000 0001(i=0) -> 0000 0010(1) -> 0000 0100(2)
			LED_data <<= 1;					
			_delay_ms(1000);				
		}
											// LED_data = 0000 1000
		for(i = 0; i < 3; i++){
			PORTC = LED_data;				// LED_data = 0000 1000(i=0) -> 0000 0100(1) -> 0000 0010(2)
			LED_data >>= 1;					
			_delay_ms(1000);
		}
											// LED_data = 0000 0001
	}
}