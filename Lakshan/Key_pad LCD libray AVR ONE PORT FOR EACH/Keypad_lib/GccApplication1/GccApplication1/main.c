/*
 * GccApplication1.c
 *
 * Created: 5/21/2021 11:23:25 PM
 * Author : lakshan rathnayake
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "keypad/key_pad_lib.h"
#include "lcd/lcd.h"

int main(void)
{
	DDRC = 0xff;
	PORTC = 0x00;
	LCD_Init();
	LCD_String("laka");
    while (1) 
    {
		 char k = key();
		 if (k == '1'){LCD_String("1");_delay_ms(50);}
		 if (k == '2'){LCD_String("2");_delay_ms(50);}	 
		 if (k == '3'){LCD_String("3");_delay_ms(50);}
		 if (k == '4'){LCD_String("4");_delay_ms(50);}
		 if (k == '5'){LCD_String("5");_delay_ms(50);}
		 if (k == '6'){LCD_String("6");_delay_ms(50);}
		 if (k == '7'){LCD_String("7");_delay_ms(50);}
		 if (k == '8'){LCD_String("8");_delay_ms(50);}
		 if (k == '9'){LCD_String("9");_delay_ms(50);}
		 if (k == '0'){LCD_String("0");_delay_ms(50);}
		 if (k == '#'){LCD_String("#");_delay_ms(50);}
		 if (k == '/'){LCD_String("/");_delay_ms(50);}
		 if (k == '+'){LCD_String("+");_delay_ms(50);}
		 if (k == '*'){LCD_String("*");_delay_ms(50);}
		 if (k == 'C'){LCD_String("C");_delay_ms(50);}
		 if (k == '='){LCD_String("=");_delay_ms(50);}
			// LCD_Clear();

    }
}

