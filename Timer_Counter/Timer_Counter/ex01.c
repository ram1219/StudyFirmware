/*
 * Timer_Counter.c
 *
 * Created: 2020-06-15 오후 4:46:21
 * Author : user
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char LED_Data = 0x00;
unsigned char timer0Cnt = 0;
SIGNAL(TIMER_OVF_vect);

int main()
{
    DDRA = 0xFF;
	TCCR0 = 0x07;
	TCNT0 = 184;					// 256 - 72 = 184  --> 0.01초마다 인터럽트 발생
	
	TIMSK = 0x01;
	TIFR |= 1 << TOV0;
	sei();
	
	while(1){
		PORTA = LED_Data;
	}
}

SIGNAL(TIMER0_OVF_vect){
	cli();
	TCNT0 = 184;
	timer0Cnt++;
	
	if(timer0Cnt == 100){
		LED_Data++;
		if(LED_Data > 0xFF) LED_Data = 0;
		timer0Cnt = 0;
	}
	sei();
}
