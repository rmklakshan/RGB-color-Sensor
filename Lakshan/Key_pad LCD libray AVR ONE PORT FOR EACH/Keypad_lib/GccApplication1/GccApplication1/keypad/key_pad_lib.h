/*
 * key_pad_lib.h
 *
 * Created: 5/22/2021 12:19:02 AM
 *  Author: lakshan rathnayake
 */ 


#ifndef KEY_PAD_LIB_H_
#define KEY_PAD_LIB_H_

char key()
{
	//DDRA = 0x00;
	//DDRD = 0xff;
	
	DDRA = 0Xf0; //PA7-4 output, PA3-0 input
	
	PORTA = 0X10; //0001 0000 - PA4 high and inputs  //PORTD = 0X01; 
	
	if (PINA&(0X01)) 	     { return '7'; }
	else if (PINA&(0X02))	 { return '8'; }
	else if (PINA&(0X04)) 	 { return '9'; }
	else if (PINA&(0X08))	 { return '/'; }
	
	PORTA = 0X20; //PORTD = 0X02;
	
	if (PINA&(0X01))   	 { return '4'; }
	else if (PINA&(0X02))   { return '5'; }
	else if (PINA&(0X04)) 	 { return '6'; }
	else if (PINA&(0X08))	 { return '*'; }
	
	PORTA = 0X40; //PORTD = 0X04;
	if (PINA&(0X01)) 	     { return '1'; }
	else if (PINA&(0X02)) 	 { return '2'; }
	else if (PINA&(0X04))	 { return '3'; }
	else if (PINA&(0X08))	 { return '-'; }
	
	PORTA = 0X80; //PORTD = 0X08;
	if (PINA&(0X01)) 	     { return 'C'; }
	else if (PINA&(0X02))   { return '0'; }
	else if (PINA&(0X04))   { return '='; }
	else if (PINA&(0X08))	 { return '+'; }
}




#endif /* KEY_PAD_LIB_H_ */