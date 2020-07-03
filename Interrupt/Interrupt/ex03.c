/*
 * ex03.c
 *
 * Created: 2020-06-15 오후 3:22:59
 *  Author: user
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char Time_Stop = 0;

int main()
{
	unsigned char FND_DATA_TBL [] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67,
			0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x08, 0x80};
	unsigned char cnt = 0;
	DDRA = 0xFF;
	DDRE = 0x00;
	
	EICRB = 0xC0;
	EIMSK = 0x80;
	EIFR = 0x80;
	
	sei();
	
	while(1){
		PORTA = FND_DATA_TBL[cnt];
		if(Time_Stop == 0){
			cnt++;
			if(cnt >17) cnt = 0;
		}
		_delay_ms(200);
	}
}

SIGNAL(INT7_vect){
	cli();
	if(Time_Stop == 0) Time_Stop = 1;
	else Time_Stop = 0;
	sei();
}