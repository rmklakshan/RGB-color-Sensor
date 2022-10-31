#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C disp(0x20,16,2);

// key pad
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] ={
  {7 ,'8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'A','0','=','+'}
  };

  byte rowPins[ROWS] = {9,8,7,6};
  byte colPins[COLS] = {5,4,3,2};

  Keypad customKeypad = Keypad(makeKeymap(hexaKeys),rowPins, colPins, ROWS, COLS);

String n1, n2;
int answer;
char oparation;
boolean choice= false;


void setup() {
  disp.begin(16,2);

}

void loop() {
  char key = customKeypad.getKey();

  if (key!= NO_KEY && (key == '1' || key == '2'|| key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9'||key=='0')){
    if (choice == false){
      disp.setCursor(0,0);
      n1= n1 + key;
      disp.print(n1);}
    else {
      n2= n2 + key;
      int nlen= n1.length();
      if (nlen<17){
      disp.setCursor(nlen+1,0);}
      else{
      disp.setCursor(nlen-15,1);}
      disp.print(n2);}}
    else if ((key!= NO_KEY)&& (choice== false) && (key== '*'|| key=='+'|| key == '-'|| key =='/')){
      choice= true;
      oparation = key;
      int nlen= n1.length();
      if (nlen<17){
      disp.setCursor(nlen,0);}
      else{
      disp.setCursor(nlen-16,1);}
      disp.print(oparation);}
    else if ((key!=  NO_KEY)&& (key =='=')&&(choice == true)){
      
      int n_1= n1.toInt();
      int n_2= n2.toInt();
      if (oparation=='+'){
        answer= n_1 + n_2;}
      else if (oparation=='-'){
        answer= n_1 - n_2;}
      else if (oparation=='*'){
        answer= n_1*n_2;}
      else if (oparation=='/'){
        answer= n_1 / n_2;}
        
       disp.clear();
       disp.setCursor(0,0);
       disp.print(answer);
      }
    else if ((key!=  NO_KEY)&& (key =='A')&&(choice == true)){
      choice= false;
      disp.clear();
      disp.setCursor(0,0);
      n1="";
      n2="";
      oparation="";
      answer=0;
      }
    
    }

