/*
 * _16bit_ex02.c
 *
 * Created: 2020-06-16 오후 12:17:16
 *  Author: user
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x00;

int main(void)
{
	DDRA = 0xFF;
	
	TCCR3A = 0x00;
	TCCR3B = (1 << CS32) | (1 << CS30);			// 프리스케일링 1024
	
	// 65536 - (7372800 / 1024) = 58336
	TCNT3 = 58336;
	ETIMSK |= 1 << TOIE3;						// 타이머3의 오버플로우 인터럽트를 Enable
	ETIFR |= 1 << TOV3;
	
	sei();
	
	while(1)
	{
		PORTA = LED_Data;
	}
	return 0;
}

SIGNAL(TIMER3_OVF_vect)
{
	cli();
	
	TCNT3 = 58336;
	LED_Data++;
	
	if(LED_Data > 0xFF) 
		LED_Data = 0;
	
	sei();
}