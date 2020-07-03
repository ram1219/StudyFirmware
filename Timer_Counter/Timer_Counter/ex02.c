/*
 * ex02.c
 *
 * Created: 2020-06-15 오후 5:04:42
 *  Author: user
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x01;
unsigned char timer2Cnt = 0, Shift_flag = 0;

SIGNAL(TIMER2_OVF_vect);

int main()
{
	DDRA = 0xFF;
	
	TCCR2 = 0x05;				// 프리스케일러 1024로 설정
	TCNT2 = 184;				// 256 - 72 = 184
	TIMSK = 0x40;
	TIFR |= 1 << TOV2;
	
	sei();
	
	while(1){
		PORTA = LED_Data;
	}
	return 0;
}

SIGNAL(TIMER2_OVF_vect){
	cli();
	TCNT2 = 184;				// 0.01초마다 인터럽트 발생
	timer2Cnt++;
	
	// 0.5초를 얻는 카운트 횟수
	if(timer2Cnt == 50){
		if(Shift_flag == 0){
			LED_Data <<= 1;
			// LED 8 까지 이동한 경우 Shift_flag를 1로 변경
			if(LED_Data == 0x80) Shift_flag = 1;	
		}
		else{
			LED_Data >>= 1;
			if(LED_Data == 0x01) Shift_flag = 0;
		}
		timer2Cnt = 0;
	}
	sei();
}