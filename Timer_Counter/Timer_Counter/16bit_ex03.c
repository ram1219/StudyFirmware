/*
 * _16bit_ex03.c
 *
 * Created: 2020-06-17 오전 9:15:12
 *  Author: user
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67, 0x77,
								0x7C, 0x39, 0x5E, 0x79, 0x71, 0x08, 0x80};
								
volatile unsigned char time_s = 0;

int main()
{
	DDRA = 0xFF;									// 포트A를 출력으로 설정
	
	TCCR1A = 0x00;									// 포트 동작을 normal로 설정
	TCCR1B = (1 << CS10) | (1 << CS12);				// 프리스케일러를 1024로 지정
	
	OCR1A = 7200;									// 출력 비교 레지스터 -> 두 레지스터의 값이 일치했을 때 A핀을 통하여 설정된 값 출력
	TIMSK = 1 << OCIE1A;							// 출력 비교로 T/C가 발생하는 레지스터 A를 개별적으로 enable 
	TIFR |= 1 << OCF1A;
	
	sei();
	
	while(1)
	{
		PORTA = FND_DATA_TBL[time_s];
	}
	return 0;
}

SIGNAL(TIMER1_COMPA_vect)
{
	cli();
	
	OCR1A += 7200;									// 1초마다 인터럽트 발생
	if(time_s == 17) time_s = 0;
	else time_s++;
	
	sei();
}