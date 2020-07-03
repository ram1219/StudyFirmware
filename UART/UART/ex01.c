/*
 * ex01.c
 *
 * Created: 2020-06-17 오후 3:03:51
 * Author : user
 */ 

#include <avr/io.h>

void putch(unsigned char data)
{
	while((UCSR0A & 0x20) == 0);
	UDR0 = data;
	UCSR0A |= 0x20;
}

int main()
{
    unsigned char text[] = "Hello! World!! \r\n";
	unsigned char i = 0;
	
	DDRE = 0xFE;
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	
	UBRR0H = 0x00;
	UBRR0L = 0x03;
	
    while (text[i] != '\0') putch(text[i++]); 
}

