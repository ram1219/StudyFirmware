/*
 * Lcd_4bit.c
 *
 * Created: 2017-07-09 ���� 10:44:06
 *  Author: CastleKing
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "Lcd.h"

void LcdCmd_4bit(Byte ch)
{
	/* ���� 4bit ���� */
	LCD_CTRL &= ~(1 << LCD_RS); // RS == 0 : Instruction
	LCD_CTRL &= ~(1 << LCD_RW);	// RW == 0 : Write
	LCD_INSTWR = (ch & 0xf0) | (1 << LCD_EN);
	_delay_us(50);
	LCD_CTRL &= ~(1 << LCD_EN);
	/* ���� 4bit ���� */
	LCD_CTRL &= ~(1 << LCD_RS); // RS == 0
	LCD_CTRL &= ~(1 << LCD_RW);	// RW == 0
	LCD_INSTWR = ((ch << 4) & 0xf0)	| (1 << LCD_EN);
	_delay_us(50);
	LCD_CTRL &= ~(1 << LCD_EN);
}

void LcdData_4bit(Byte ch)
{
	LCD_CTRL &= ~(1 << LCD_RW); // RW == 0
	LCD_DATAWR = (ch & 0xf0) | (1 << LCD_RS) | (1 << LCD_EN);
	_delay_us(50);				// BF = 0 �� �� �ڿ� ��������� �� �� �ִ�. ���� delay�� �ش�.
	LCD_CTRL &= ~(1 << LCD_EN);	// Lcd Disable
	
	LCD_CTRL &= ~(1 << LCD_RW); // RW == 0
	LCD_DATAWR = ((ch << 4) & 0xf0) | (1 << LCD_RS) | (1 << LCD_EN);
	_delay_us(50);				// BF = 0 �� �� �ڿ� ��������� �� �� �ִ�. ���� delay�� �ش�.
	LCD_CTRL &= ~(1 << LCD_EN);	// Lcd Disable
}

void Lcd_CHAR(Byte c)			//������� �Լ�
{
	LcdData_4bit(c);
	_delay_ms(1);
}

void Lcd_STR(Byte *str)			//���ڿ� ��� �Լ�
{
	while(*str != 0){
		Lcd_CHAR(*str);
		str++;
	}
}

void Lcd_Pos(Byte col, Byte row)	//��ġ���� �Լ�
{
	LcdCmd_4bit(0x80 | (row + col * 0x40));
}

void Lcd_Clear(void)			//ȭ�� ���� �Լ�
{
	LcdCmd_4bit(0x01);
	_delay_ms(2);
}

void Lcd_Shift(Byte p)			//�̵� �Լ�
{
	if(p == RIGHT){
		LcdCmd_4bit(0x1c);
		_delay_ms(1);
		}else if(p == LEFT){
		LcdCmd_4bit(0x18);
		_delay_ms(1);
	}
}

void LcdInit_4bit(void)
{
	LcdCmd_4bit(0x02);	//cursor Home
	_delay_ms(2);		//��ɾ IR�� ������ 37us �Ǵ� 1.52ms�� ��ٸ�.
	LcdCmd_4bit(0x28);	//��� �缳��
	_delay_us(37);
	LcdCmd_4bit(0x0c);	//LCD ON, Ŀ�� ������ ����
	_delay_us(37);
	LcdCmd_4bit(0x06);	//��Ʈ��:��� �̵�
	_delay_us(37);
	Lcd_Clear();
}