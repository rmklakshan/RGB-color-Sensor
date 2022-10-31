/*
 * AnalogWrite_setColor.h
 *
 * Created: 5/31/2021 2:19:02 PM
 *  Author: lakshan rathnayake
 */ 


#ifndef ANALOGWRITE_SETCOLOR_H_
#define ANALOGWRITE_SETCOLOR_H_

#define	F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void pwm_init()
{
	DDRD   |= (1<<PORTD7)|(1<<PORTD5)|(1<<PORTD4);
	TCCR2  |= (1<<WGM21) |(1<<WGM20) | (1<<COM21)  | (1<<CS20);
	TCCR1A = (1<<WGM10) | (1<<COM1A1)|(1<<COM1B1)   ;
	TCCR1B = (1<<WGM12)  | (1<<CS10);
}
void setColor(int redValue, int greenValue, int blueValue)

{
	OCR2 =  redValue ; //pin portD7
	OCR1A = greenValue ;  //pin portD5
	OCR1B = blueValue ; //pin portD4
}



#endif /* ANALOGWRITE_SETCOLOR_H_ */