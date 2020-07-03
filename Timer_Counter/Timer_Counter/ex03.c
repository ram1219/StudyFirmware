/*
 * ex03.c
 *
 * Created: 2020-06-15 오후 5:16:37
 *  Author: user
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x00;
unsigned int timer0Cnt = 0;

SIGNAL(TIMER0_OVF_vect);

int main()
{
	DDRA = 0xFF;
	
	TCCR0 = 0x06;				// 프리스케일러 256
	TCNT0 = 184;				// T/C의 초기값 : 256 - 72  --> 184에서 72만큼 증가하면 255를 넘어가며 오버플로우가 발생
	TIMSK = 0x01;				// overflow 인터럽트 사용
	TIFR |= 1 << TOV0;
	
	sei();
	
	while(1){
		PORTA = LED_Data;
	}
	return 0;
}

SIGNAL(TIMER0_OVF_vect){
	cli();
	
	TCNT0 = 184;
	timer0Cnt++;
	
	// 7372800 / 256(프리스케일러) = 28800 = 72 * 400
	if(timer0Cnt == 400){
		LED_Data++;
		if(LED_Data > 0xFF) LED_Data = 0;
		timer0Cnt = 0;
	}
	
	sei();
}