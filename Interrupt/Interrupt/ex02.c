/*
 * ex02.c
 *
 * Created: 2020-06-15 오후 2:46:37
 *  Author: user
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char Shift_flag = 1;					// volatile -> 인터럽트를 가져올 변수

int main()
{
	unsigned char LED_data = 0x01;
	
	DDRA = 0xFF;
	DDRD = 0x00;
	DDRE = 0x00;
	
	EICRA = 0x02;				// 인터럽트 0을 하강엣지
	EICRB = 0x03;				// 인터럽트 4를 상승엣지
	
	EIMSK = 0x11;				// 인터럽트 0, 4 허용
	EIFR = 0x11;				// 인터럽트 0, 4 플래그 클리어
	
	sei();						// 전체 인터럽트 허용
	
	while(1){
		PORTA = LED_data;
		
		if(Shift_flag == 1){
			if(LED_data == 0x80) LED_data = 0x01;
			else LED_data <<= 1;
		}
		else if(Shift_flag == 2){
			if(LED_data == 0x01) LED_data = 0x80;
			else LED_data >>= 1;
		}
		_delay_ms(100);	
	}
}

SIGNAL(INT0_vect){
	cli();
	Shift_flag = 1;
	sei();
}

SIGNAL (INT4_vect){
	cli();
	Shift_flag = 2;
	sei();
}