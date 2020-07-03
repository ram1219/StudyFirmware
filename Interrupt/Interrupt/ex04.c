/*
 * ex04.c
 *
 * Created: 2020-06-15 오후 3:43:21
 *  Author: user
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char Time_Stop = 0;
volatile unsigned char cnt = 0;

int main()
{
	unsigned char FND_DATA_TBL[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67, 0x77, 0x7C,
			0x39, 0x5E, 0x79, 0x71, 0x08, 0x80};
			
	DDRA = 0xFF;
	DDRD = 0x00;
	
	EICRA = 0xC2;						// 인터럽트 0은 하강, 3은 상승엣지
	EIMSK = 0x09;						// 인터럽트 0, 3 허용
	EIFR = 0x09;
	sei();
	
	while(1){
		PORTA = FND_DATA_TBL[cnt];
		if(Time_Stop == 0){
			cnt++;	
			if(cnt > 17) cnt = 0;
		}
		_delay_ms(200);
	}
}

// 인터럽트 0 (버튼 0)
SIGNAL(INT0_vect){
	cli();
	
	Time_Stop = 1;		// 정지
	cnt = 0;			// 0으로 초기화
	
	sei();
}

SIGNAL(INT3_vect){
	cli();
	Time_Stop = 0;		// 동작
	sei();
}