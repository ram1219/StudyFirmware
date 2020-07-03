/*
 * _16bit_ex04.c
 *
 * Created: 2020-06-17 오전 9:33:48
 *  Author: user
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char FND_DATA_TBL[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x67,
								0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x08, 0x80};
								
volatile unsigned char time_s = 0;
volatile unsigned char FND_falg = 0, edge_flag = 0;

int main()
{
	DDRA = 0xFF;												// 포트 A를 출력 포트로 설정
	DDRE = 0x00;												// 포트 E를 입력 포트로 설정
	
	TCCR3A = 0x00;												// normal
	TCCR3B = (1 << CS30) | (1 << CS32) | (1 << ICES3);			// 0x45, 프리스케일러 1024, 상승엣지
	ETIMSK = 1 << TICIE3;										// 0x20, 입력으로 인터럽트3 활성화
	ETIFR |= 1 << ICF3;
	
	sei();
	
	PORTA = FND_DATA_TBL[0];
	while(1)
	{
		if(FND_falg){											// 인터럽트가 발생한 경우(인터럽트 동작 활성화)
			if(time_s > 15) time_s = 15;						// 배열 범위 설정
			PORTA = FND_DATA_TBL[time_s];						// 버튼이 눌러진 시간 출력
			FND_falg = 0;										// 인터럽트 동작 비활성화
		}
	}
	return 0;
}

SIGNAL(TIMER3_CAPT_vect)
{
	cli();
	
	unsigned int count_check;
	
	// 버튼이 눌러진 시간 측정을 위한 if~else문 
	// 상승엣지에서 하강엣지까지의 시간을 계산
	
	if(edge_flag == 0){
		TCCR3B = (1 << CS30) | (1 << CS32);			// 하강 엣지일 경우 캡처, 1024로 설정
		TCNT3 = 0;									// 16비트 카운터 값을 저장. 자동으로 증가 
		ICR3 = 0;									// ICR:입력캡처 레지스터, TCNT의 카운터 값을 저장.
		edge_flag = 1;
	}
	else{
		TCCR3B = (1 << CS30) | (1 << CS32) | (1 << ICES3);	// 상승 엣지일 경우 캡처, 1024
		count_check = ICR3;									// 눌러진 동안의 시간을 count_check에 저장
		
															// 7372800 / 1024 = 7200 (1초)
		time_s = count_check / 720;							// 0.1초 단위로 변경
		
		FND_falg = 1;										// main문에서 값 출력
		edge_flag = 0;									
	}
	
	sei();
}