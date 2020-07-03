/*
 * Timer_Counter_test3.c
 *
 * Created: 2020-06-15 오후 7:21:13
 *  Author: user
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char LED_data = 0x00;
unsigned int timer0Cnt = 0;
volatile unsigned int C_LED = 0;

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
		if(C_LED == 0)	LED_data = 0xFF;
		else LED_data = 0x00;
	
		PORTA = LED_data;
	}
	return 0;
}

SIGNAL(TIMER0_OVF_vect)
{
	cli();
	
	TCNT0 = 184;
	timer0Cnt++;
	
	if(timer0Cnt == 400){
		if(C_LED == 0) C_LED = 1;
		else C_LED = 0;
		
		timer0Cnt = 0;
	}
	
	sei();
}