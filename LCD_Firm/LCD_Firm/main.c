/*
 * LCD_Firm.c
 *
 * Created: 2020-06-16 오후 1:53:12
 * Author : user
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "Lcd.h"

volatile unsigned char num = 2;
unsigned int i = 1;

int main()
{	
	Byte str[11];
	Byte str1[5];
	
	DDRA = 0xFF;
	DDRE = 0x00;				// 4 ~ 7 외부 인터럽트
	DDRC = 0x00;				// 0 ~ 3 외부 인터럽트
	
	EICRA = 0xFF;				
	EICRB = 0xFF;
	
	EIMSK = 0xFF;				// 0 ~ 7 외부 인터럽트 모두 사용
	EIFR = 0xFF;
	
	sei();
	
	LcdInit_4bit();							// LCD 초기화
	
	while(1)
	{	
		sprintf(str1, "%dth", num);
		sprintf(str, "%d * %d = %d", num, i, num*i);
		
		Lcd_Pos(0, 0);
		Lcd_STR(str);
		Lcd_Pos(1, 0);
		Lcd_STR(str1);
		_delay_ms(1500);
		Lcd_Clear();
		
		if(i == 9) i = 0;
		i++;
	}	
	return 0;
}

SIGNAL(INT0_vect){
	cli();
	num = 2;
	i = 0;
	sei();
}

SIGNAL(INT1_vect){
	cli();
	num = 3;
	i = 0;
	sei();
}

SIGNAL(INT2_vect){
	cli();
	num = 4;
	i = 0;
	sei();
}

SIGNAL(INT3_vect){
	cli();
	num = 5;
	i = 0;
	sei();
}

SIGNAL(INT4_vect){
	cli();
	num = 6;
	i = 0;
	sei();
}

SIGNAL(INT5_vect){
	cli();
	num = 7;
	i = 0;
	sei();
}

SIGNAL(INT6_vect){
	cli();
	num = 8;
	i = 0;
	sei();
}

SIGNAL(INT7_vect){
	cli();	
	num = 9;
	i = 0;
	sei();
}

