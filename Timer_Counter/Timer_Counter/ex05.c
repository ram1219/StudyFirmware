/*
 * ex05.c
 *
 * Created: 2020-06-16 오전 10:16:30
 *  Author: user
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67, 0x77,
								0x7C, 0x39, 0x5E, 0x79, 0x71, 0x08, 0x80};

volatile unsigned char time_s = 0;
volatile unsigned char Time_Stop = 0;	

unsigned char timer0Cnt = 0;

int main()
{
	DDRA = 0xFF;
	DDRE = 0x00;
	
	// 내부 인터럽트 설정
	TCCR2 = 0x05;						// 프리스케일러 1024 사용
	OCR2 = 72;							// T/C 2의 출력 비교 인터럽트 사용
	TIMSK = 0x80;						// T/C 2의 출력 비교 인터럽트 Enable
	TIFR |1 << OCF2;
	
	// 외부 인터럽트 설정
	EICRB = 0x03;						// 외부 인터럽트4 를 상승에지 인터럽트로 사용
	EIMSK = 0x10;						// 4를 외부 인터럽트로 Enable
	EIFR = 0x10;
	
	sei();
	
	while(1)
	{
		PORTA = FND_DATA_TBL[time_s];
	}
	return 0;
}

// 내부 인터럽트
SIGNAL(TIMER2_COMP_vect)
{
	cli();
	OCR2 += 72;
	timer0Cnt++;
	
	if(timer0Cnt == 50){
		if(Time_Stop == 0){
			// 배열 범위 설정
			if(time_s == 16) time_s = 0;
			else time_s++;
		}
		timer0Cnt = 0;
	}
	sei();
}

// 외부 인터럽트
SIGNAL(INT4_vect)
{
	cli();
	
	if(Time_Stop == 0) Time_Stop = 1;
	else Time_Stop = 0;
	
	sei();
}