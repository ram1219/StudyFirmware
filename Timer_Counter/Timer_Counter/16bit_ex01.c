/*
 * _16bit_01.c
 *
 * Created: 2020-06-16 오전 11:30:16
 *  Author: user
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x00;
unsigned char timer1Cnt = 0;

int main()
{
	DDRA = 0xFF;
	
	TCCR1A = 0;
	TCCR1B = 1 << CS10;				// 클럭소스 존재 (프리스케일링이 없음)
	
	TCNT1 = 0;
	TIMSK = 1 << TOIE1;				// 타이머1의 오버플로우 인터럽트를 개별적으로 Enable
	TIFR |= 1 << TOV1;
	
	sei();
	
	while(1)
	{
		PORTA = LED_Data;
	}
	return 0;
}

SIGNAL(TIMER1_OVF_vect)
{
	cli();
	
	timer1Cnt++;
	
	// 65536 / 7372800 = 0.00888888888888888889
	// 1/0.008888888888888889 = 112.4999999999999999 
	// 7372800 / 65536 = 112.4999999999999990
	if(timer1Cnt == 112){
		LED_Data++;	
		if(LED_Data > 0xFF) LED_Data = 0;
		
		timer1Cnt = 0;
	}
	sei();
}