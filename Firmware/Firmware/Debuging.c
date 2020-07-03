/*
 * Debuging.c
 *
 * Created: 2020-06-15 오후 12:06:58
 *  Author: user
 */ 
#include <avr/io.h>
#include <util/delay.h>

unsigned char data = 0x01;
int main()
{
	unsigned long i;
	DDRA = 0xFF;
	PORTA = 0x00;
	while(1){
		PORTA = data;
		data <<= 1;
		for(i = 0; i < 1000; i++){
			if(data == 0x00) data = 0x01;	
		}
	}
}