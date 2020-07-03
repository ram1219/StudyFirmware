/*
 * ex05.c
 *
 * Created: 2020-06-15 오전 10:21:29
 *  Author: user
 */ 
#include <avr/io.h>
#include <util/delay.h>

int main(){
	unsigned char Switch_flag = 0, Switch_flag_pre = 0x01;
	
	DDRA = 0x0F;				// 포트 A의 0 ~ 3 핀을 출력모드
	DDRE = 0x00;				// 포트 E의 모든 핀을 입력모드
	PORTA = 0x00;				// PORTA 초기화 (LED의 0 ~ 3을 OFF한 채 프로그램 시작)
	
	while(1){
		// 입력받은 값이 포트 D의 상위 4비트로 나타남 1000 0000
		// 우측으로 4비트 쉬프트 -> 0000 1000 한 값을 Switch_flag에 저장
		Switch_flag = PINE >> 4;	// PIN(E) -> E포트로 입력 받은 값
		
		// 스위치 0~4중 하나만 누른 경우
		if((Switch_flag == 0x01) || (Switch_flag == 0x02) || (Switch_flag == 0x04) || (Switch_flag == 0x08))
			Switch_flag_pre = Switch_flag;
		
		// ^ 는 Exclusive OR 
		// 0000 0000 + 0000 1111 -> 0000 1111 + 0000 1111 -> 0000 0000 + 0000 1111 -> 0000 1111
		// LED불이 꺼졌다가 켜졌다를 동작하게 함.
		PORTA ^= 0x0F;
		
		if(Switch_flag_pre == 0x01) _delay_ms(250);
		else if(Switch_flag_pre == 0x02) _delay_ms(500);
		else if(Switch_flag_pre == 0x04) _delay_ms(750);
		else if(Switch_flag_pre == 0x08) _delay_ms(1000);
	}
}