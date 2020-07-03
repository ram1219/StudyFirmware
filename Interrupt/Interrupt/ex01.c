/*
 * ex01.c
 *
 * Created: 2020-06-15 오후 2:12:58
 * Author : user
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char Time_STOP = 0;

int main()
{
    unsigned char LED_data = 0x01;
	DDRA = 0xFF;
	DDRE = 0x00;
	
	EICRB = 0x03;										// 인터럽트4를 상승엣지에서 동작하도록 설정
	EIMSK = 0x10;										// 인터럽트4를 허용
	EIFR = 0x10;										// 인터럽트4 플래그를 클리어
	sei();												// 전체 인터럽트 혀용
	
	while(1){
		PORTA = LED_data;								// 0x01을 출력
		if(Time_STOP == 0){								
			if(LED_data == 0x80) LED_data = 0x01;
			else LED_data <<= 1;						
		}
		_delay_ms(100);
	} 
}

SIGNAL(INT4_vect){
	cli();												// 전체 인터럽트를 금지
	if(Time_STOP == 0) Time_STOP = 1;
	else Time_STOP = 0;
	sei();												// 전체 인터럽트 허용
}
