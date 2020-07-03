/*
 * ex04.c
 *
 * Created: 2020-06-16 오전 9:14:23
 *  Author: user
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67, 0x77,
								0x7C, 0x39, 0x5E, 0x79, 0x71, 0x08, 0x80};

volatile unsigned char time_s = 0;
unsigned char timer0Cnt = 0;

int main()
{
	DDRA = 0xFF;
	
	TCCR0 = 0x07;						// 프리스케일러를 1024로 설정
	OCR0 = 72;							// 출력 비교 레지스터 --> 0번 핀에 출력 펄스
	TIMSK = 0x02;						// T/C 0번의 출력비교 인터럽트
	TIFR |= 1 << OCF0;					
	
	sei();
	
	while(1){
		PORTA = FND_DATA_TBL[time_s];
	}
	return 0;
} 

SIGNAL(TIMER0_COMP_vect){
	cli();
	OCR0 += 72;							// 7372800/1024 = 72 * 100 --> 0.01초 후에 인터럽트 발생
	timer0Cnt++;
	
	if(timer0Cnt == 100){
		// 배열 범위 설정
		if(time_s >= 16) time_s = 0;
		else time_s++;
		
		timer0Cnt = 0;
	}
	sei();
}