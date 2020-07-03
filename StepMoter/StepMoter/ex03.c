/*
 * ex03.c
 *
 * Created: 2020-06-18 오전 10:04:56
 *  Author: user
 */ 
#include <avr/io.h>
#include <util/delay.h>

unsigned char Step[8] = {0x90, 0x80, 0xC0, 0x40, 0x60, 0x20, 0x30, 0x10};

int main()
{
	unsigned char i, t = 0;
	
	DDRA = 0x20;						// 0010 0000	
	DDRD = 0xF0;						// 1111 0000	포트D의 4,5,6,7 번을 모터의 출력으로 설정
	PORTA &= ~0x20;						// 1101 1111
	
	while(1)
	{
		for(i = 0; i < 24; i++)
		{
			PORTD = Step[t];
			t++;
			if(t > 7) t = 0;
			_delay_ms(10);
		}
		_delay_ms(1000);
	}
}