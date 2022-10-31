/*
 * pwm test2.c
 *
 * Created: 5/29/2021 7:42:20 PM
 * Author : lakshan rathnayake
 */ 


#include <avr/io.h>
#include <util/delay.h>
void pwm_init()
{
	// initialize TCCR0 as per requirement, say as follows
	TCCR0 |= (1<<WGM00)|(1<<COM01)|(1<<WGM01)|(1<<CS00);
	
	// make sure to make OC0 pin (pin PB3 for atmega32) as output pin
	DDRB |= (1<<PORTB3)|(1<<PORTB4);
	PORTB = (1<<PORTB4);
}

void main()
{
	uint8_t duty;
	duty = 255;       // duty cycle = 45% of 255 = 114.75 = 115
	
	// initialize timer in PWM mode
	pwm_init();
	
	// run forever
	while(1)
	{
		OCR0 = 1;
		
	}
}
