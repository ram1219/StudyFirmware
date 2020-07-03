/*
 * Melody_UART.c
 *
 * Created: 2020-06-17 오후 4:07:49
 *  Author: user
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int DoReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};

void putch(unsigned char data)
{
	while((UCSR0A & 0x20) == 0);			// 전송 준비가 될 때까지 대기(송신)
	UDR0 = data;							// 데이터를 UDR0에 쓰면 전송
	UCSR0A |= 0x20;							
}

unsigned char getch()
{
	unsigned char data;
	while((UCSR0A & 0x80) == 0);			// 데이터를 받을때까지 대기(수신)
	data = UDR0;							// 수신된 데이터는 UDR0에 저장
	UCSR0A |= 0x80;
	
	return data;							// 읽어온 문자를 반환한다.
}

int main()
{
	unsigned char Rx_data = 0;	
	unsigned char Input[] = "Input >> ";	
	int i = 0;	
	
	DDRE = 0x0E;							// Rx(입력 0), Tx(출력, 1)
	DDRB = 0x80;							// 포트B의 PB7을 출력포트로 설정 
	
	TCCR1A |= 0x0A;							// 0000 1010 (1<<WGM11) | (1<<COM1C1)
	TCCR1B |= 0x19;							// 0001 1001 (1<<WGM13) | (1<<WGM12) | (1<<CS10)
	TCCR1C |= 0x00;							// PWM에선 C 안 씀
	TCNT1 = 0x0000; 
	
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	
	UBRR0H = 0x00;
	UBRR0L = 0x03;							// 115200 bps
	
	ICR1 = 10;
	OCR1C = ICR1/10;

	
	while(1)
	{
		Rx_data = getch();
		
		if((Rx_data >= '0') && (Rx_data <= '7' ))
		{
			while(Input[i] != '\0') putch(Input[i++]);
			putch(Rx_data);
			
			ICR1 = 7372800 / DoReMi[Rx_data - '0'];
			OCR1C = ICR1 / 10;
			
			_delay_ms(500);
			
			TCCR1A |= 0x0A;
			ICR1 = 10;
			OCR1C = ICR1/10;
		}
		else continue;
	}
}
	