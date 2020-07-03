/*
 * Timer_Counter_test.c
 *
 * Created: 2020-06-15 오후 6:22:00
 *  Author: user
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_data = 0x00;
unsigned int timer0Cnt = 0;

SIGNAL(TIMER0_OVF_vect);

int main()
{
	DDRA = 0xFF;
	TCCR0 = 0x06;
	
	TCNT0 = 184;
	TIMSK = 0x01;			// 타이머카운트 0 오버플로우 인터럽트
	TIFR |= 1 << TOV0;
	
	sei();
	
	while(1){
		PORTA = LED_data;
	}
	return 0;
}

SIGNAL(TIMER0_OVF_vect)
{
	cli();
	
	TCNT0 = 184;
	timer0Cnt++;				// 256 - 72 = 184 
	
	if(timer0Cnt == 400){
		LED_data = 0xFF;
		timer0Cnt = 0;
	}
	else {
		LED_data = 0x00;		
	}
	
	sei();
}