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
	char keypad[4][4]= {{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'C','0','=','+'}};

	DDRA = 0Xf0; //0-3 output, 4-7 input
	PORTA = 0Xff; // rows (outputs) set to high , powered up the pull up res in inputs (col)
	
	for (int r=0; r<4; r++){ //changing i+4 th row value to 0
		PORTA &= ~(1<<(r+4));
		for (int c=0; c<4; c++){ //checking columns
			if (PINA & (1<<c)){}
			else {return keypad[r][c];}
		}
		PORTA = 0Xff;
	}

}



#endif /* KEYPAD2_H_ */