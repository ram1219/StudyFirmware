/*
 * ex01.c
 *
 * Created: 2020-06-17 오전 10:38:43
 * Author : user
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main()
{
	unsigned char Light = 0;
	
	DDRB = 0x10;
	
	// 0x77, PWM모드, 1024
	TCCR0 = (1 << CS20) | (1 << CS21) | (1 << CS22) | (1 << COM00) | (1 << COM01) | (1 << WGM00);
	TCNT0 = 0x00;
	
	while(1)
	{
		for(Light = 0; Light < 255; Light++)
		{
			OCR0 = Light;
			_delay_ms(50);
		}
		for(Light = 255; 0 < Light; Light--)
		{
			OCR0 = Light;
			_delay_ms(50);
		}
	}
}
