/*
 * pwm pin.c
 *
 * Created: 5/29/2021 3:39:09 PM
 * Author : lakshan rathnayake
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void pwm_init()
{
	DDRD   |= (1<<PORTD7)|(1<<PORTD5)|(1<<PORTD4);
	TCCR2  |= (1<<WGM21) |(1<<WGM20) | (1<<COM21)  | (1<<CS20);
	TCCR1A = (1<<WGM10) | (1<<COM1A1)|(1<<COM1B1)   ;
	TCCR1B = (1<<WGM12)  | (1<<CS10);
	//TCCR1A |= (1<<WGM12) |(1<<WGM10) | (1<<COM1B1) | (1<<CS10);
	
	
	
}


int main(void)
{
    /* Replace with your application code */
	
	uint8_t b;
	
	pwm_init();
	
	
	
	
    while (1) 
    {
		OCR2 = 255;//red
		OCR1A =255;//green
		OCR1B = 255;//blue
		
		/*for (b = 0; b<255; b++)
		{
			OCR2 =  b ; 
			_delay_ms(10); 		
        }
	    b=0;*/
	} 
	}

