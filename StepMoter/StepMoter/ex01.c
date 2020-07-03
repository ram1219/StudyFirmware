/*
 * ex01.c
 *
 * Created: 2020-06-18 오전 9:32:35
 * Author : user
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRB = 0x20;
	DDRD = 0x0F;
	PORTB &= ~0x20;					// 0x20이 아닐 때, 모터 정지
	while(1)
	{
		PORTD = 0x01;
		_delay_ms(10);
		PORTD = 0x02;
		_delay_ms(10);
		PORTD = 0x04;
		_delay_ms(10);
		PORTD = 0x08;
		_delay_ms(10);
	}
}