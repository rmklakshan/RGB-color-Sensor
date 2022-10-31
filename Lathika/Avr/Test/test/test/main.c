/*
 * test.c
 *
 * Created: 5/30/2021 12:05:46 AM
 * Author : Lathika
 */ 


#define F_CPU 8000000UL			/* Define CPU Frequency e.g. here 8MHz */
#include <avr/io.h>			/* Include AVR std. library file */
#include <util/delay.h>			/* Include Delay header file */
#include "keypad2.h"


int main(void)
{ DDRC=0xff;
	PORTC= 0;
	char k;
    
    while (1) {
		k = key();
		if (k== '5' ){PORTC = 2; _delay_ms(100); PORTC = 0;}
		if (k =='6'){PORTC = 1; _delay_ms(100); PORTC = 0;}
		if (k=='*'){PORTC = 3; _delay_ms(100); PORTC = 0;}
		/*if (k=='9'){PORTC = 1; _delay_ms(100);PORTC = 0;}
		if (k=='/'){PORTC = 1;_delay_ms(10); PORTC = 0;}*/
		//if (k=='5'){PORTC = 3;}
		
		}
}

