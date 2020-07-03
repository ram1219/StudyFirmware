/*
 * ex02.c
 *
 * Created: 2020-06-12 오후 4:23:24
 *  Author: user
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(){
	unsigned char LED_Data = 0x00;
	DDRC = 0x0F;						// 0000 1111
	
	while(1){
		PORTC = LED_Data;		
		LED_Data++;						// 0000 0001 -> 0000 0010 -> 0000 0011 ...
		
		if(LED_Data > 0x0F)				// LED_Data -> 0000 1111
			LED_Data = 0;				// LED_Data -> 0000 0000
		_delay_ms(1000);
	}
}