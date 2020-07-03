/*
 * ex02.c
 *
 * Created: 2020-06-17 오후 3:48:01
 *  Author: user
 */ 
#include <avr/io.h>

void putch(unsigned char data)
{
	while((UCSR0A & 0x20) == 0);	// 전송 준비가 될 때까지 대기
	UDR0 = data;					// 수신된 데이터를 UDR0에 저장
	UCSR0A |= (1 << UDRE0);
}

unsigned char getch()
{
	unsigned char data;
	while((UCSR0A & 0x80)==0);
	data=UDR0;
	UCSR0A |= (1 << RXC0);
	return data;
}

int main(void)
{
	unsigned char text[] = "\r\nWelcome! edgeiLAB\r\n USART 0 Test Program.\r\n";
	
	unsigned char echo[] = "ECHO >> ";
	unsigned char i = 0;
	
	DDRE = 0xfe;   // Rx(입력 0), Tx(출력 1)
	
	UCSR0A = 0x00;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0); // Rx, Tx enable
	UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
	
	UBRR0H = 0X00;
	UBRR0L = 0X03;
	
	while(text[i]!='\0')
	{
		putch(text[i++]);
	}
	
	i=0;
	while(echo[i]!='\0')
	{
		putch(getch());
	}
}