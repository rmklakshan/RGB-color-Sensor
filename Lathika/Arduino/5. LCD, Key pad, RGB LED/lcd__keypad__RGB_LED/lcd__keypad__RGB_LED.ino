#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 LiquidCrystal_I2C screen(0x21,16,2);

 #include <Keypad.h>

 const byte ROWS = 4;
 const byte COLS = 4;

char keys[ROWS][COLS] = { 
  {'7' ,'8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'C','0','=','+'}
  };

// '/' R
// '*' G
// '-' B
// '+' backspace
// '=' enter
// 'C' clear

byte rowPins[ROWS] ={12,8,7,6};
byte colPins[COLS] = {5,4,3,2};

Keypad customKeypad = Keypad(makeKeymap(keys),rowPins, colPins,ROWS, COLS);

String R,G,B, num;
int R_,G_,B_;
String choice= "R";

void setup() {
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);

  screen.begin(16,2);

  screen.setCursor(0,0);
  screen.print("R:");
  screen.setCursor(8,0);
  screen.print("G:");
  screen.setCursor(5,1);
  screen.print("B:");
}

void loop() {
  char key = customKeypad.getKey();

  if (key!= NO_KEY && ((key== '/')||(key== '*')||(key== '-'))){
    num= "";
    if (key=='/'){
      choice ="R";
      int l_1= R.length();
      screen.setCursor(2+l_1,0);
      }
    else if (key=='*'){
      choice ="G";
      int l_2= G.length();
      screen.setCursor(10+l_2,0);
      }
    else if (key=='-'){
      choice ="B";
      int l_3= B.length();
      screen.setCursor(7+l_3,1);
      }
    }
  else if (key!= NO_KEY &&(key == '1' || key == '2'|| key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9'||key=='0'||(key == '+' ))){
    if (key!='+'){
    num=num+key;}
    if (num.toInt()<=255){
    int l= num.length();
    if (key!=NO_KEY && key == '+' && l>0){
    num = num.substring(0,l-1);
   } 
    if (choice=="R"){
      R=num;
      screen.setCursor(2,0);
      screen.print(R);

    }
   else if (choice=="G"){
      G=num;
      screen.setCursor(10,0);
      screen.print(G);
 
      }
    else if (choice=="B"){
      B=num;
      screen.setCursor(7,1);
      screen.print(B);

      }
    }
      }

  else if (key!=NO_KEY && key=='='){
    analogWrite(11, R.toInt());
    analogWrite(10, G.toInt());
    analogWrite(9, B.toInt());
    }
  else if (key!=NO_KEY && key=='C'){
    screen.clear();
    num="";
    R="";
    G="";
    B="";
    screen.setCursor(0,0);
    screen.print("R:");
    screen.setCursor(8,0);
    screen.print("G:");
    screen.setCursor(5,1);
    screen.print("B:");
    choice="R";
    }
int l= num.length();


}
