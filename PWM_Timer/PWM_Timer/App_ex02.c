/*
 * App_ex02.c
 *
 * Created: 2020-06-17 오후 1:51:06
 *  Author: user
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int DoReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};
volatile unsigned char sound_flag = 1;

int main()
{
	unsigned char piano = 0;
	
	DDRE = 0x08;
	DDRD = 0x00;
	
	TCCR3A = 0x00;
	TCCR3B = (1 << CS30) | (1 << WGM32) | (1 << WGM33);
	TCCR3C = 0x00;
	TCNT3 = 0x0000;
	
	// 외부 인터럽트
	EICRB = 0xFF;
	EICRA = 0xFF;
	EIMSK = 0xFF;
	EIFR = 0xFF;
	
	sei();
	
	while(1)
	{
		if(sound_flag)
		{
			_delay_ms(2000);
			TCCR3A = 0x00;
			sound_flag = 0;
		}
	}
}

SIGNAL(INT0_vect)
{
	cli();
	ICR3 = (7372800 / DoReMi[0]) / 10;
	TCCR3A = 1 << COM3A0;
	sound_flag = 1;
	sei();
	
}

SIGNAL(INT1_vect)
{
	cli();
	ICR3 = (7372800 / DoReMi[1]) / 10;
	TCCR3A = 1 << COM3A0;
	sound_flag = 1;
	sei();
	
}

SIGNAL(INT2_vect)
{
	cli();
	ICR3 = (7372800 / DoReMi[2]) / 10;
	TCCR3A = 1 << COM3A0;
	sound_flag = 1;
	sei();
	
}

SIGNAL(INT3_vect)
{
	cli();	
	ICR3 = (7372800 / DoReMi[3]) / 10;
	TCCR3A = 1 << COM3A0;
	sound_flag = 1;
	sei();
	
}

SIGNAL(INT4_vect)
{
	cli();
	ICR3 = (7372800 / DoReMi[4]) / 10;
	TCCR3A = 1 << COM3A0;
	sound_flag = 1;
	sei();
	
}

SIGNAL(INT5_vect)
{
	cli();
	ICR3 = (7372800 / DoReMi[5]) / 10;
	TCCR3A = 1 << COM3A0;
	sound_flag = 1;
	sei();
}

SIGNAL(INT6_vect)
{
	cli();
	ICR3 = (7372800 / DoReMi[6]) / 10;
	TCCR3A = 1 << COM3A0;
	sound_flag = 1;
	sei();
	
}

SIGNAL(INT7_vect)
{
	cli();
	ICR3 = (7372800 / DoReMi[7]) / 10;
	TCCR3A = 1 << COM3A0;
	sound_flag = 1;
	sei();
	
}