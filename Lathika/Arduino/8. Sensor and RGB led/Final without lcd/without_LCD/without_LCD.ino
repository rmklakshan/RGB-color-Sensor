#include <Keypad.h>
/*#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20,16,2);*/


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {12,8,7,6};//connect to the row pinouts of the keypad
byte colPins[COLS] = {5,4,3,2};//connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// pines for led in sensor
const byte red_pin = A1;
const byte green_pin = A2;
const byte blue_pin = A3;

int Red_max = 328;
int Green_max = 95;
int Blue_max = 112;

// pines for RGB led
int red_pin_RGB = 11 ; 
int green_pin_RGB= 10 ; 
int blue_pin_RGB = 9;
char led;  //??
int Sample_f_red,Sample_f_green,Sample_f_blue,value_ldr; //????
String num="";

// arrays
int r_ar[30]; // for R value of RGB values
int rv_ar[30]; // for corresponding voltage value
int g_ar[30];
int gv_ar[30];
int b_ar[30];
int bv_ar[30];

//sensor & calib output variables
int R,G,B,r,g,b;

void setup() 
{
Serial.begin(9600);
Serial.print("Select Mode\n Press 'A' for calibration\n Press 'B' for Sensor Mode \n Press 'C' for Light RGB bulb for given rgb values\n");
//sensor
pinMode(red_pin,OUTPUT);
pinMode(green_pin,OUTPUT);
pinMode(blue_pin,OUTPUT);
pinMode(A0,INPUT);
//RGB LED
pinMode(red_pin_RGB,OUTPUT);
pinMode(green_pin_RGB,OUTPUT);
pinMode(blue_pin_RGB,OUTPUT);

 /* 
 // lcd initialize 
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("CAL:-'A'");
  lcd.setCursor(8,0);
  lcd.print("SEN:-'B'");
  lcd.setCursor(0,1);
  lcd.print("RGB:-'C'");
  lcd.setCursor(8,1);
  lcd.print("Menu:-'D'");*/

}

void loop()
{    
   char key = customKeypad.getKey();
   if (key)
   {
    Serial.println(key);
    if (key == 'A') {calibration();}              // Mode-1  Calibration                           ******************************
    if (key == 'B'){Sensor();}                    // Mode-2  Sensoring                             ******************************
    if (key == 'C'){Light_RGB_Given_Values();}    // Mode-3  Light RGB bulb for given rgb values   ****************************** 
    if (key == 'D'){Menu();} 
   }
   else{setColor(0,0,0);}
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(red_pin_RGB, redValue);
  analogWrite(green_pin_RGB, greenValue);
  analogWrite(blue_pin_RGB, blueValue);
}

void calibration()
{ Serial.println("\nRED - press 'A' GREEN - for press 'B' BLUE - press 'C' Finish-press'D'\n CAL" );
 /* normal_lcd(); //defined below
  lcd.print("CAL");*/
  while (1)
  {  
  char key = customKeypad.getKey();
  if (key=='D'){/*lcd.clear(); lcd.setCursor(0,0);lcd.print("Calibaration over");*/ break;} // finishing calib
  switch (key)
  { 
    case 'A':
  Serial.print("Calibration for RED\n");
  Getvalues();  
 /* normal_lcd(); 
  lcd.print("CAL");
  lcd.setCursor(11,1);
  lcd.print("R");*/
  rv_ar[0]=R;
  gv_ar[0]=G;
  bv_ar[0]=B;    
  Serial.print("\n R = ");
  r = value(1);  
  g = value(2);
  b = value(3);
  r_ar[0]=r;
  g_ar[0]=g;
  b_ar[0]=b;
  break;
  
    case 'B':
  Serial.print("\nCalibration for GREEN\n");
   Getvalues();
  /*normal_lcd(); 
  lcd.print("CAL");
  lcd.setCursor(11,1);
  lcd.print("G");*/
  rv_ar[1]=R;
  gv_ar[1]=G;
  bv_ar[1]=B;    
  Serial.print("\n G = ");
  r = value(1);
  g = value(2);
  b = value(3);
  r_ar[1]=r;
  g_ar[1]=g;
  b_ar[1]=b;
  break;
  
     case 'C':
  Serial.print("\nCalibration for BLUE\n");
   Getvalues();
  /*normal_lcd(); 
  lcd.print("CAL");
  lcd.setCursor(11,1);
  lcd.print("B");*/
  rv_ar[2]=R;
  gv_ar[2]=G;
  bv_ar[2]=B;    
  Serial.print("\n B = ");
  r = value(1);
  g = value(2);
  b = value(3);
  r_ar[2]=r;
  g_ar[2]=g;
  b_ar[2]=b;
  break;
  }}}


void Sensor()
{

 Getvalues();

 
 Serial.print("\nR value = ");   
 int r_f = mapping(R,Red_max);
 Serial.print(r_f);
 
 Serial.print("\nG value = ");
 int g_f = mapping(G,Green_max);
 Serial.print(g_f);
 
 Serial.print("\nB value = ");
 int b_f = mapping(B,Blue_max);
 Serial.print(b_f);

 //display in lcd
/* lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("R: "+ String(r_f));
 lcd.setCursor(8,0);
 lcd.print("G: "+String(g_f));
 lcd.setCursor(0,1);
 lcd.print("B: "+String(b_f));
 lcd.setCursor(13,1);
 lcd.print("SEN");*/

}

// for sensor
void Getvalues()
{int Rv=0;int Gv=0;int Bv=0; 
/* lcd.clear();
 lcd.print("Wait...");*/
 Serial.println("Wait....");
  for (int i =0 ; i < 3; i++)
  {
    digitalWrite(red_pin,HIGH);
    delay(100);
    Rv+=analogRead(A0); 
    Serial.println(Rv);
    digitalWrite(red_pin,LOW);
    delay(100);
    
    digitalWrite(green_pin,HIGH);
    delay(100);
    Gv+=analogRead(A0);
    Serial.println(Gv);
    digitalWrite(green_pin,LOW);
    delay(100);
    
    digitalWrite(blue_pin,HIGH);
    delay(100);
    Bv+=analogRead(A0);
    Serial.println(Bv);
    digitalWrite(blue_pin,LOW);
    delay(100);
  }
  R=round(1023-Rv/3);G=round(1023-Gv/3);B=round(1023-Bv/3);
  Serial.println(R); Serial.println(G); Serial.println(B);
  ;
}


int mapping(int Sample_ldr,int max_ )
{   
    int Sample_f = map(Sample_ldr,0,max_,0,255);
    if (Sample_f > 255) { Sample_f = 255; }
    if (Sample_f < 0)   { Sample_f = 0;   }
    return Sample_f;
}

void Light_RGB_Given_Values()
{ //lcd
  /* normal_lcd();
   lcd.print("RGB");*/
   
  Serial.print("\n R = ");
  int check = value(1);
  if (check == 10000){return;}
  int r = check;
  Serial.print(" G = ");
  check = value(2);
  if (check == 10000){return;}
  int g = check;
  Serial.print(" B = ");
  check = value(3);
  if (check == 10000){return;}
  int b = check;
  setColor(r, g, b); //for common cathode
  delay(5000);
  
}

int value(int color) //1-Red 2- Green 3- Blue   // when press 'D' , the main mode should return to the menu (we have to code this)
{
  int val = 0;
  num="";
  while(1)
  { int k=0;
  char key = customKeypad.getKey();
  if (key)
  { if (key!= NO_KEY && key =='D'){ return 10000;}
  else if (key!= NO_KEY &&(key == '1' || key == '2'|| key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9'||key=='0')) 
    {  
       num = num+key;
       Serial.println(num);
       //condition for printing value near color
       if (color == 1)
        Serial.print("R");
        /*lcd.setCursor(3,0);
        lcd.print(num);*/}
       else if (color ==2){
        Serial.print("G");
        /*lcd.setCursor(11,0);
        lcd.print(num);*/}
       else if (color ==3){
        Serial.print("B");
        /*lcd.setCursor(3,1);
        lcd.print(num);*/}
       }
  else if (key == '#')
  {
    val = num.toInt();
    Serial.println(num);
    return val;
  }
}}

int looping()
{ 
  int average = 0 ;
  for (int i = 0; i<5 ;i++){average += analogRead(A0);
  delay(50);}
  return average/5;
}

/*void normal_lcd()
{   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("R: ");
   lcd.setCursor(8,0);
   lcd.print("G: ");
   lcd.setCursor(0,1);
   lcd.print("B: ");
   lcd.setCursor(13,1);
}*/

void Menu(){
  /*lcd.setCursor(0,0);
  lcd.print("CAL:-'A'");
  lcd.setCursor(8,0);
  lcd.print("SEN:-'B'");
  lcd.setCursor(0,1);
  lcd.print("RGB:-'C'");
  lcd.setCursor(8,1);
  lcd.print("Menu:-'D'");  */
  Serial.print("Select Mode\n Press 'A' for calibration\n Press 'B' for Sensor Mode \n Press 'C' for Light RGB bulb for given rgb values\n");
  loop();
  }
