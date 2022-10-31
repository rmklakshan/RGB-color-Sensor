/*
 * anlogread.c
 *
 * Created: 6/1/2021 11:48:25 PM
 * Author : lakshan rathnayake
 */ 
#define F_CPU  8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd/lcd.h"


void adc_init()
{
	// AREF = AVcc
	ADMUX = (1<<REFS0)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0);
	
	//64 PRESCCALER
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1);
}

uint16_t adc_read()
{
	// select the corresponding channel 0~7
	//ch &= 0b00000111;  //PINA7 OXO8
	ADMUX = (ADMUX & 0xF8)|0b00000111; // clears the bottom 3 bits before ORing
	
	// start single convertion
	// write ’1? to ADSC
	ADCSRA |= (1<<ADSC);
	
	// wait for conversion to complete
	// ADSC becomes ’0? again
	// till then, run loop continuously
	while(ADCSRA & (1<<ADSC));
	
	return (ADC);
}



int main(void)
{
	uint16_t  adc_result7;
	char int_buffer[10];  
	
	adc_init();
	LCD_Init ();
	
	_delay_ms(50);
    /* Replace with your application code */
    while (1) 
    {
		
		adc_result7 = adc_read();
		itoa(adc_result7, int_buffer, 10);
		LCD_String (int_buffer);
		_delay_ms(50);
		LCD_Clear();
    }
}

