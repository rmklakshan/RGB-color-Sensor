#include <Keypad_I2C.h>
#include <Keypad.h>
#include <Wire.h>
#define I2CADDR 0x20

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
// Digitran keypad, bit numbers of PCF8574 i/o port
byte rowPins[ROWS] = {0, 1, 2, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 6}; //connect to the column pinouts of the keypad

Keypad_I2C kpd( makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8575 );

// toggle LED on PCF8575 bit 7 (P07, IC pin 11)
word portState;
const word ledPin = 0b0000000010000000;

// use byte-size definitions if using PCF8574
// byte portState;
// const byte ledPin = 0b10000000;

void toggleLEDpin( ) {
  portState = kpd.pinState_set( );  // save current state of all pins
  if( portState & ledPin ) {
    portState &= ~ledPin;
  } else {
    portState |= ledPin;
  }
  kpd.port_write( portState );  // write modified state to port
} // toggleLEDpin( )

void setup(){
  Wire.begin( );
  kpd.begin( makeKeymap(keys) );
  Serial.begin(9600);
  Serial.println( "start" );
}
void loop(){
  
  char key = kpd.getKey();
  
  if (key){
    Serial.println(key);
    if( key == '*' ) toggleLEDpin( );
  }
}
