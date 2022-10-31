#include <Keypad.h>
#include <LiquidCrystal.h>
const int rs=13, en = 12, d4=11, d5=10 ,d6=1, d7 =0;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS]= {
  {'7','8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'c','0','=','+'}
};
byte rowPins[ROWS]= {2,3,4,5};
byte colPins[COLS]= {6,7,8,9};
int i=0; 
char arr[10];
Keypad keypad = Keypad(makeKeymap(keys) , rowPins, colPins, ROWS, COLS);

void setup() {
  // put your setup code here, to run once:
lcd.begin(16,2); //16 col, 2 rows

}

void loop() {
  // put your main code here, to run repeatedly:
char key = keypad.getKey();
if (key){
  lcd.setCursor(1,1);
  lcd.print("I'm Lathika");
  lcd.display();
  lcd.scrollDisplayRight();
  }
}
