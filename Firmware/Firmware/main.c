/*
 * Project.c
 *
 * Created: 2020-06-12 오후 2:11:28
 * Author : user
 */ 

#include <avr/io.h>

int main()
{
	DDRA = 0xFF;			// 포트 A를 출력으로 설정
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	DDRE = 0xFF;
	DDRF = 0xFF;
	DDRG = 0xFF;
	while(1){
		PORTA = 0xFF;		// 포트 A의 0 ~ 7 번(A 포트는 8개)에 해당하는 모든 pin들이 5v를 출력
		PORTB = 0xFF;
		PORTC = 0xFF;
		PORTD = 0xFF;
		PORTE = 0xFF;
		PORTF = 0xFF;
		PORTG = 0xFF;
	}
	return 0;
}

