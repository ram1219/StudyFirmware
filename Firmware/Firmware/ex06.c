/*
 * ex06.c
 *
 * Created: 2020-06-15 오전 10:49:46
 *  Author: user
 */ 
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	// 디지털 숫자 0 ~ 8까지를 배열로 저장
	unsigned char FND_DATA_TBL[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F,
			0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x80};
	// 배열 원소 출력을 위한 카운터 변수
	unsigned char cnt = 0;
	// 포트 A를 전체 출력으로 설정
	DDRA = 0xFF;		
	
	while(1){
		PORTA = FND_DATA_TBL[cnt];
		cnt++;
		
		// 배열의 범위 지정
		if(cnt > 16){ 
			cnt = 0;
		}
				
		_delay_ms(1000);		
	}
}
