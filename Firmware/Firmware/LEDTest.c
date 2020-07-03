/*
 * LEDTest.c
 *
 * Created: 2020-06-12 오후 3:39:48
 *  Author: user
 */ 
#include <avr/io.h>

void main(){
	DDRA = 0xFF;
	
	while(1){
		PORTA = 0xFF;	
	}
}