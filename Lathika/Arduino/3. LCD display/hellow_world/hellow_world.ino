#include <LiquidCrystal.h>;

// initialize the library
LiquidCrystal lcd(9, 8, 7, 6, 5, 4);


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // put your main code here, to run repeatedly:

}
