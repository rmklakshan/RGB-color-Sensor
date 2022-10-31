#include <LiquidCrystal.h>;

// initialize the library
LiquidCrystal lcd(9, 8, 7, 6, 5, 4);

byte customChar[8] = {
  0b00000,
  0b01110,
  0b01110,
  0b00100,
  0b11111,
  0b10101,
  0b00100,
  0b01010
};

void setup() 
{
  // create a new custom character
  lcd.createChar(0, customChar);

  // set up number of columns and rows
  lcd.begin(16, 2);

  // print the custom char to the lcd
  // why typecast? see: http://arduino.cc/forum/index.php?topic=74666.0
  lcd.write((uint8_t)0);
}

void loop()
{

}
