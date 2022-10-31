/*
 *Edited for two ports
 *
 * Created: 5/22/2021 8:41:42 PM
 * Author : lakshan rathnayake
 */ 

#ifndef LCD_H_
#define LCD_H_


#define F_CPU 8000000UL			/* Define CPU Frequency e.g. here 8MHz */
#include <avr/io.h>			    /* Include AVR std. library file */
#include <util/delay.h>			/* Include Delay header file */

#define LCD_Dir1  DDRC			/* Define LCD RS/EN directory */
#define LCD_Port1 PORTC			/* Define LCD RS/EN port */
#define LCD_Dir2  DDRD			/* Define LCD data port direction */
#define LCD_Port2 PORTD			/* Define LCD data port */
/*This code considers first 4 pines in Dir2 as data outputs*/
#define RS PC0				    /* Define Register Select pin */
#define EN PC1 				    /* Define Enable signal pin */


void LCD_Command( unsigned char cmnd )
{
	LCD_Port2 = (LCD_Port2 & 0xF0) | ((cmnd & 0xF0)>>4); /* sending upper nibble */
	LCD_Port1 &= ~ (1<<RS);		                  /* RS=0, command reg. */
	LCD_Port1 |= (1<<EN);	               	      /* Enable pulse */
	_delay_us(1);
	LCD_Port1 &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port2 = (LCD_Port2 & 0xF0) | (cmnd & 0x0F);  /* sending lower nibble */
	LCD_Port1 |= (1<<EN);
	_delay_us(1);
	LCD_Port1 &= ~ (1<<EN);
	_delay_ms(2);
}


void LCD_Char( unsigned char data )
{
	LCD_Port2 = (LCD_Port2 & 0xF0) | ((data & 0xF0)>>4);  /* sending upper nibble */
	LCD_Port1 |= (1<<RS);		                   /* RS=1, data reg. */
	LCD_Port1 |= (1<<EN);
	_delay_us(1); 
	LCD_Port1 &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port2 = (LCD_Port2 & 0xF0) | (data & 0x0F);     /* sending lower nibble */
	LCD_Port1 |= (1<<EN);
	_delay_us(1);
	LCD_Port1 &= ~ (1<<EN);
	_delay_ms(2);
}

void LCD_Init (void)			   /* LCD Initialize function */
{
	LCD_Dir1 |= (1<<EN)|(1<<RS);	/* Make LCD port EN/RS pin direction as o/p */
	LCD_Dir2 |= 0x0F;				/* Make LCD port data pin(first 4 pins in dir2) direction as o/p */
	_delay_ms(20);			       /* LCD Power ON delay always >15ms */
	
	LCD_Command(0x02);       /* send for 4 bit initialization of LCD ,(this can be also done by 0x32 / 0x33 */ 
	LCD_Command(0x28);             /* 2 line, 5*7 matrix in 4-bit mode */
	LCD_Command(0x0c);             /* Display on cursor off*/
	LCD_Command(0x06);             /* Increment cursor (shift cursor to right)*/
	LCD_Command(0x01);             /* Clear display screen*/
	_delay_ms(2);
}


void LCD_String (char *str)		   /* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		   /* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
	}
}

void LCD_String_xy (char row, char pos, char *str)	/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	LCD_Command((pos & 0x0F)|0x80);	       /* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	LCD_Command((pos & 0x0F)|0xC0);	       /* Command of first row and required position<16 */
	LCD_String(str);		               /* Call LCD string function */
}

void LCD_Clear()
{
	LCD_Command (0x01);		/* Clear display */
	_delay_ms(2);
	LCD_Command (0x80);		/* Cursor at home position */
}







#endif /* LCD_H_ */