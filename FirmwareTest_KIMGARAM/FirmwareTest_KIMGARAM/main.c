/*
 * FirmwareTest_KIMGARAM.c
 *
 * Created: 2020-06-18 오전 10:19:27
 * Author : user
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

unsigned int DoReMi[8] = {523, 587, 659, 698, 783, 880, 987, 1046};

volatile unsigned char Move_Flag = 0;

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
	
	return data;							
}

void LED();
void PIANO();
void Moter();

int main()
{
	unsigned char Rx_data = 0;					// 키보드 입력을 저장하는 변수
	unsigned char Cds[30];
	unsigned char text[] =
	"\r\n ++++ Menu ++++ \r\nL : LED\r\nC : CDS\r\nP : PIANO(0~7)\r\nS : Step Motor\r\npush button0 : stop\r\n";
	unsigned char input[] = "\r\nInput >> ";
	unsigned int ADC_data = 0;
	int i = 0;
	
	// 부저(멜로디)
	DDRE = 0x0E;								// Rx(입력 0), Tx(출력, 1)
	DDRB = 0x80;	
		
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
	
	i = 0;
	while(text[i] != '\0') putch(text[i++]);
	
	sei();
	
	while(1)
	{			
		Move_Flag = 0;
		i = 0;
		while(input[i] != '\0') putch(input[i++]);
		Rx_data = getch();
		putch(Rx_data);
		
		// PIANO
		if((Rx_data >= '0') && (Rx_data <= '7' ))
		{					
			ICR1 = 7372800 / DoReMi[Rx_data - '0'];
			OCR1C = ICR1 / 10;
					
			_delay_ms(500);
					
			TCCR1A |= 0x0A;
			ICR1 = 10;
			OCR1C = ICR1/10;
		}
		// CDS
		else if((Rx_data == 'c') || (Rx_data == 'C'))
		{		
			CDS();	
		}
		// Moter
		else if((Rx_data == 'S') || (Rx_data == 's'))
		{
			Moter();
		}
		// LED
		else if((Rx_data == 'l') || (Rx_data == 'L'))
		{
			LED();
		}
	}
	return 0;
}

void LED()
{
	unsigned char LED_data;
	int i;
	
	DDRD = 0x00;				// Interrupt
	DDRC = 0xFF;				// LED
	
	EICRA = 0x03;
	EIMSK = 0x01;
	EIFR = 0x01;
	
	sei();

	while(1){
		LED_data = 0x01;
		if(Move_Flag == 0)
		{
			for(i = 0; i < 7; i++){
				PORTC = LED_data;
				LED_data <<= 1;
				_delay_ms(500);
			}
		}
		else{
			LED_data = 0x00;
			PORTC = LED_data;
			break;
		}
		
		if(Move_Flag == 0)
		{
			for(i = 0; i <= 7; i++){
				PORTC = LED_data;
				LED_data >>= 1;
				_delay_ms(500);
			}
		}
		else{
			LED_data = 0x00;
			PORTC = LED_data;
			break;
		}
	}
}

void Moter()
{
	unsigned char Rx_data = 0;
	unsigned char M_Menu[] = "\r\n right : f, left : r \n";
	
	DDRD = 0x20;
	DDRA = 0xF0;
	
	EICRA = 0x03;
	EIMSK = 0x01;
	EIFR = 0x01;

	PORTD &= ~0x20;
	
	int i = 0;
	
	sei();
	while(M_Menu[i] != '\0') putch(M_Menu[i++]);
			
	Rx_data = getch();
			
	if((Rx_data == 'F') || (Rx_data == 'f')){
		while(1){
			if(Move_Flag == 0){
				PORTA = 0x80;
				_delay_ms(10);
				PORTA = 0x40;
				_delay_ms(10);
				PORTA = 0x20;
				_delay_ms(10);
				PORTA = 0x10;
				_delay_ms(10);
			}
			else{
				Move_Flag = 0;
				break;
			}					
		}
	}
	else if((Rx_data == 'R') || (Rx_data == 'r'))
	{
		while(1){
			if(Move_Flag == 0){
				PORTA = 0x10;
				_delay_ms(10);
				PORTA = 0x20;
				_delay_ms(10);
				PORTA = 0x40;
				_delay_ms(10);
				PORTA = 0x80;
				_delay_ms(10);
			}
			else{
				Move_Flag = 0;
				break;
			}
		}
	}	
}

void CDS()
{
	unsigned int AdData = 0;
	char cds[16];
	int i;
	
	DDRA = 0XFF;
	DDRF = (1 << DDRF1);   //DDRF1번 출력 나머지 입력 바꿔줌
	ADMUX = 0X00;
	ADCSRA = (1 << ADEN)|(1 << ADPS2)|(1 << ADPS1);      //64분주비
	
	EICRA = 0x03;
	EIMSK = 0x01;
	EIFR = 0x01;
	
	sei();
	
	while(1)
	{
		if(Move_Flag == 0)
		{
			PORTF = (1 << PORTF1);                  
			ADCSRA |= (1 << ADSC);                  
			
			while((ADCSRA & 0x10)==0x00);           
			AdData = ADC;                        
			
			sprintf(cds, "Data : %d \r\n", AdData);
			i = 0;
			while(cds[i] != '\0') putch(cds[i++]);
			_delay_ms(1000);
		}
		else{
			Move_Flag = 0;
			break;
		}
	}
}

// LED, Moter, CDS 동작 정지
SIGNAL(INT0_vect)
{
	cli();
	if(Move_Flag == 0) Move_Flag = 1;
	sei();
}
