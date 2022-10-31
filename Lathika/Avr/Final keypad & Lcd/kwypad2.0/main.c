/*
 * kwypad2.0.c
 *
 * Created: 5/26/2021 9:24:24 PM
 * Author : Lathika
 */ 
#define F_CPU 8000000UL			/* Define CPU Frequency e.g. here 8MHz */
#include <avr/io.h>			    /* Include AVR std. library file */
#include <util/delay.h>			/* Include Delay header file */

#include "lcd/lcd.h"
#include "Keypad2/keypad2.h"



int main(void)
{	LCD_Init();
	LCD_String("type");
    /* Replace with your application code */
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
				 if (k == 'A'){LCD_String("A");_delay_ms(50);}
				 if (k == 'B'){LCD_String("B");_delay_ms(50);}
				 if (k == 'C'){LCD_String("C");_delay_ms(50);}
				 if (k == 'D'){LCD_String("D");_delay_ms(50);}
				 if (k == '*'){LCD_String("*");_delay_ms(50);}
				 if (k == '#'){LCD_String("#");_delay_ms(50);}
				 // LCD_Clear();

    }
}

