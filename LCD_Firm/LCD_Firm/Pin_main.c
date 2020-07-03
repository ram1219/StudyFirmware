/*
 * Pin_main.c
 *
 * Created: 2020-06-16 오후 3:32:16
 *  Author: user
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "Lcd.h"

int main()
{
	LcdInit_4bit();
	
	Byte str[16];
	Byte str1[16];
	
	unsigned char num = 0x00;
	unsigned int i = 1, mul_num = 2;
	
	DDRA = 0xFF;
	
	DDRE = 0x00;
//	DDRD = 0x00;
	
	while(1)
	{
		num = PINE;
		
		if((num == 0x01) || (num == 0x02) || (num == 0x04) || (num == 0x08) ||
		(num == 0x10) || (num == 0x20) || (num == 0x40) || (num == 0x80))
		{
			if(num == 0x01) mul_num = 2;
			else if(num == 0x02) mul_num = 3;
			else if(num == 0x04) mul_num = 4;
			else if(num == 0x08) mul_num = 5;
			else if(num == 0x10) mul_num = 6;
			else if(num == 0x20) mul_num = 7;
			else if(num == 0x40) mul_num = 8;
			else if(num == 0x80) mul_num = 9;
		}
		
		for(i = 1; i < 10; i++)
		{
			sprintf(str, "%d * %d = %2d", mul_num, i, mul_num*i);
			Lcd_Pos(0, 0);
			Lcd_STR(str);
			sprintf(str1, "%d th", mul_num);
			Lcd_Pos(1, 0);
			Lcd_STR(str1);
				
			_delay_ms(500);
			Lcd_Clear();
		}				
	}				
}
