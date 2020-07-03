/*
 * ex04.c
 *
 * Created: 2020-06-15 오전 10:08:21
 *  Author: user
 */ 
#include <avr/io.h>
#include <util/delay.h>

int main(){
	DDRA = 0xFF;						// A포트의 전체 핀 출력
	DDRE = 0x00;						// E포트의 전체 핀 입력
	
	while(1){
		if(PINE == 0x01)				// PIN(E) --> E포트가 입력 받는 값
			PORTA = 0x01;				// 스위치를 누르면 1, 누르지 않으면 0
		else if(PINE == 0x02) PORTA = 0x02;
		else if(PINE == 0x03) PORTA = 0x03;
	}
}