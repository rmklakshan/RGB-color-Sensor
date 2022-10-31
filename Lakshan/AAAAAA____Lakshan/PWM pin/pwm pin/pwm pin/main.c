/*
 * pwm pin.c
 *
 * Created: 5/29/2021 3:39:09 PM
 * Author : lakshan rathnayake
 */ 

#include "pwm/AnalogWrite_setColor.h"

int main(void)
{
    /* Replace with your application code */
	
	
	
	pwm_init();
	
	
	
	
    while (1) 
    {
		setColor(255,255,255);
		
		//for (b = 0; b<255; b++)
		//{
			//OCR2 =  b ;
			//_delay_ms(10);
		//}
		//b=0;
	} 
	}

