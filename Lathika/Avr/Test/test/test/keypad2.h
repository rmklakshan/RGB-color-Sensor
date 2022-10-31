/*
 * keypad2.h
 *
 * Created: 5/26/2021 10:14:55 PM
 *  Author: Lathika
 */ 


#ifndef KEYPAD2_H_
#define KEYPAD2_H_

char key()
{
	char keypad[4][4]= {{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};

	DDRA &= 0Xf0; //0-3 input, 4-7 input
	PORTA |= 0X0f; // powered up the pull up res in inputs (col)
	DDRB |= 0X0f; //0-3  output
	PORTB |= 0X0f; //   rows (outputs) set to high ,

	for (int r=0; r<4; r++){ //changing r th row value to 0 in PORTB
		PORTB &= ~(1<<r);
		
		for (int c=0; c<4; c++){ //checking columns
			if (~(PINA) & (1<<c)){return keypad[r][c];} 
		}
		PORTB |= 0X0f; //reset PORTB
	}

}



#endif /* KEYPAD2_H_ */