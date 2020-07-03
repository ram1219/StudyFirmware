/*
 * Timer_Counter_test2.c
 *
 * Created: 2020-06-15 오후 7:02:29
 *  Author: user
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned char Time_Stop = 0;

int main(){
	unsigned char LED_data = 0x01;
	DDRA = 0xFF;
	DDRE = 0x00;
	
	EICRB = 0xC0;
	
	EIMSK = 0x80;
	EIFR = 0x80;
	
	sei();
	
	while(1){
		PORTA = LED_data;
		
		if(Time_Stop == 0) LED_data = 0xFF;
		else LED_data = 0x00;
	}
	//_delay_ms(100);
}

SIGNAL(INT7_vect){
	cli();
	if(Time_Stop == 0) Time_Stop = 1;
	else Time_Stop = 0;
	
	sei();
}