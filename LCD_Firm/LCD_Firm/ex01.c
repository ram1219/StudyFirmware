/*
 * ex01.c
 *
 * Created: 2020-06-16 오후 4:53:24
 *  Author: user
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "Lcd.h"

int main()
{
	unsigned int AdData = 0;
	Byte str[16];
	
	DDRA = 0xFF;
	DDRF = 1 << DDRF1;						// F의 1번 핀을 출력 포트로 설정
	
	ADMUX = 0x00;							// ADC0 선택 (Analog Digita Converter)  --> 아날로그를 디지털로 변환
	ADCSRA = 0x87;							// 10000111 ADC 허가, 128
	
	LcdInit_4bit();							// LCD 초기화
			
	while(1)
	{
		Lcd_Clear();
		
		PORTF = (1 << PORTF);						// 전력 출력
		ADCSRA |= (1 << ADSC);						// ADSC AD 개시(Start)
		
		while((ADCSRA & (1 << ADIF)) == 0x00);		// 아날로그 값을 다 읽어올때까지 기다림
		AdData = ADC;								// 전압이 디지털로 변환된 값 읽어오기
		
		sprintf(str, "Data : %d", AdData);
		Lcd_Clear();
		Lcd_Pos(0, 0);
		Lcd_STR(str);
		_delay_ms(300);
	}
}