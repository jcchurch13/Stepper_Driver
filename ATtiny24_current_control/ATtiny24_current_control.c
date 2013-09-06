/*
 * L298Board.c
 *
 * Created: 8/25/2013 4:34:47 PM
 *  Author: jcchurch
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

/******************************
* Pin and Setting Definitions *
******************************/

void initADC()
{
	ADMUX = (1<<REFS1) | //VCC is used as AREF
			(0<<REFS0) |
			(0<<MUX5) |  // ADC0, Single-Ended
			(0<<MUX4) |
			(0<<MUX3) |
			(0<<MUX2) |
			(0<<MUX1) |
			(0<<MUX0);
			
			
	ADCSRA |= (1<<ADEN) | (0<<ADPS2) | (0<<ADPS1) | (1<<ADPS0); 
	ADCSRB |= (0<<ADLAR);

}


int main(void)
{   
	initADC();
	DDRA = 0b11111110;
	DDRB = 0b00000000;
	PORTA = 0b00000000;
	PORTB = 0b00000000;
	
    while(1)
    {
		//PORTA |= 0b00000100;     //Timing Calibration pulse
		//PORTA &= 0b11111011;
		ADCSRA |= (1<<ADSC);
		while (ADCSRA & (1 <<ADSC));
		if (ADC > 0b0000000001011110)
		{
			PORTA &= 0b11111101;
		}
		else
		{
			PORTA |= 0b00000010;
		}
		
       
    }
	 return 0;
}
