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

void row1()
{
	PORTB = 0X01;
	if (PINA ==0X01)
	{
		lcd_data ('7');
		command (0X06);
	}
	else if (PINA == 0X02)
	{
		lcd_data ('8');
		command (0X06);
	}
	else if (PINA == 0X04)
	{
		lcd_data ('9');
		command (0X06);
	}
	else if (PINA == 0X08)
	{
		lcd_data ('/');
		command (0X06);
	}
}

void row2()
{
	PORTB = 0X02;
	if (PINA == 0X01)
	{
		lcd_data ('4');
		command (0X06);
	}
	else if (PINA == 0X02)
	{
		lcd_data ('5');
		command (0X06);
	}
	else if (PINA == 0X04)
	{
		lcd_data ('6');
		command (0X06);
	}
	else if (PINA == 0X08)
	{
		lcd_data ('*');
		command (0X06);
	}
}

void row3()
{
	PORTB = 0X04;
	if (PINA == 0X01)
	{
		lcd_data ('1');
		command (0X06);
	}
	else if (PINA == 0X02)
	{
		lcd_data ('2');
		command (0X06);
	}
	else if (PINA == 0X04)
	{
		lcd_data ('3');
		command (0X06);
	}
	else if (PINA == 0X08)
	{
		lcd_data ('-');
		command (0X06);
	}
}

void row4()
{
	PORTB = 0X08;
	if (PINA == 0X01)
	{
		lcd_data ('C');
		command (0X06);
	}
	else if (PINA == 0X02)
	{
		lcd_data ('0');
		command (0X06);
	}
	else if (PINA == 0X04)
	{
		lcd_data ('=');
		command (0X06);
	}
	else if (PINA == 0X08)
	{
		lcd_data ('+');
		command (0X06);
	}
}

void key()
{	
	DDRA = 0X00;
	DDRB = 0XFF;
	
	 row1();	 
	 row2();	
	 row3();	 
	 row4();
}








int main(void)
{
    /* Replace with your application code */
	DDRA = 0X00;
	DDRB = 0XFF;
	DDRC = 0XFF;
	DDRD = 0xFF;
	
	command (0x38);
	command (0x0f);
	command (0x01);
	command (0X80);

		
    while (1) 
    {
	key();
	}
}

