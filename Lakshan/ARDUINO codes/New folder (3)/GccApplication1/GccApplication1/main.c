/*
 * GccApplication1.c
 *
 * Created: 5/17/2021 4:35:35 PM
 * Author : lakshan rathnayake
 */ 

#define F_CPU  16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>


void command (unsigned char cmd)
{
	PORTC = 0x02;
	PORTD = cmd;
	PORTC = 0x00;
	_delay_ms (15);	
}

void lcd_data (unsigned char data)
{
	PORTC = 0x03;
	PORTD = data;
	PORTC = 0x01;
	_delay_ms(15);
}

void lcd_print (char *p)
{
	while (*p)
	{
		lcd_data(*p++);
		
	}
	
}










int main(void)
{
    /* Replace with your application code */
	
	DDRC = 0xff;
	DDRD = 0xff;
	
	command (0x38);
	command (0x0f);
	command (0x01);

		
    while (1) 
    {
		command (0x80);
		lcd_print("Lakshan");
		_delay_ms(100);
		command (0XC0);
		lcd_print ("Rathnayake");
		_delay_ms(100);
		command (0x01);
		_delay_ms(100);
    }
}

