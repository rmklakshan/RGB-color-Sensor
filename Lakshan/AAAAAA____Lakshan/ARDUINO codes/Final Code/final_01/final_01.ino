#include <Keypad.h>
#include <LiquidCrystal.h>

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {7, 4, 2, A5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = { A4, A3, A2, A1}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

int Red_max = 696;
int Green_max = 465;
int Blue_max = 224;
int red_pin = 3 ; 
int green_pin = 5 ; 
int blue_pin = 6 ;
char led;
int Sample_f_red,Sample_f_green,Sample_f_blue,value_ldr;
String num="";

void setup() 
{
Serial.begin(9600);
Serial.print("Select Mode\n Press 'A' for calibration\n Press 'B' for Sensor Mode \n Press 'C' for Light RGB bulb for given rgb values\n");
pinMode(red_pin,OUTPUT);
pinMode(green_pin,OUTPUT);
pinMode(blue_pin,OUTPUT);
}
void loop()
{   
   char key = customKeypad.getKey();
   if (key)
   {
    if (key == 'A') {calibration();}              // Mode-1  Calibration                           ******************************
    if (key == 'B'){Sensor();}                    // Mode-2  Sensoring                             ******************************
    if (key == 'C'){Light_RGB_Given_Values();}    // Mode-3  Light RGB bulb for given rgb values   ****************************** 
   }
   else{setColor(255,255,255);}
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(red_pin, redValue);
  analogWrite(green_pin, greenValue);
  analogWrite(blue_pin, blueValue);                        }

void calibration()
{ Serial.println("\nRED - press 'A' GREEN - for press 'B' BLUE - press 'C' Finish-press'D'" );
  while (1)
  {  
  char key = customKeypad.getKey();
  if (key) 
  { 
  if (key=='D'){Serial.print("\n\nSelect Mode\n Press 'A' for calibration\n Press 'B' for Sensor Mode \n Press 'C' for Light RGB bulb for given rgb values\n");
  break;}
  switch (key)
  {
    case 'A':
  Serial.print("Calibration for RED\n");
  delay(2000);
  setColor(0,255,255);
  delay(3000);
  Red_max = read_ldr_val();
  Serial.print("Red ldr value = "+String(Red_max));
  setColor(255,255,255);
  break;
    case 'B':
  Serial.print("\nCalibration for GREEN\n");
  delay(2000);
  setColor(255,0,255);
  delay(3000);
  Green_max = read_ldr_val();
  Serial.print("GREEN ldr value = "+String(Green_max)+"\n");
  setColor(255,255,255);
  break;
     case 'C':
  Serial.print("Calibration for BLUE\n");
  delay(2000);
  setColor(255,255,0);
  delay(3000);
  Blue_max = read_ldr_val();
  Serial.print("BLUE ldr value = "+String(Blue_max)+"\n");
  setColor(255,255,255);
  break;
  }}}}

void Sensor()
{
 Serial.print("\nR value = ");
 setColor(0, 255, 255); 
 delay(3000);
 int r1 = read_ldr_val();
 int r_f = mapping(r1,Red_max,358);
 Serial.print(r_f);
 
 Serial.print("\nG value = ");
 setColor(255, 0, 255); 
 delay(3000);
 int g1 = read_ldr_val();
 int g_f = mapping(g1,Green_max,276);
 Serial.print(g_f);
 
 Serial.print("\nB value = ");
 setColor(255, 255, 0); 
 delay(3000);
 int b1 = read_ldr_val();
 int b_f = mapping(b1,Blue_max,95);
 Serial.print(b_f);
 
 setColor(255, 255, 255);
 Serial.print("\n\nSelect Mode\n Press 'A' for calibration\n Press 'B' for Sensor Mode \n Press 'C' for Light RGB bulb for given rgb values\n");

}

int read_ldr_val()
{
  int sample_ldr_val = analogRead(A0);
  delay(1000);
  Serial.println(sample_ldr_val);
  return (sample_ldr_val);
}

int mapping(int Sample_ldr,int max_,int min_ )
{
    int Sample_f = map(Sample_ldr,min_,max_,0,255);
    if (Sample_f > 255) { Sample_f = 255; }
    if (Sample_f < 0)   { Sample_f = 0;   }
    return Sample_f;
}

void Light_RGB_Given_Values()
{
 Serial.print("\n R = ");
 int r = value();
 Serial.print(" G = ");
 int g = value();
 Serial.print(" B = ");
 int b = value();
 setColor(255-r, 255-g, 255-b);
 delay(10000);//using while loop and get a key to break 
 Serial.print("\n\nSelect Mode\n Press 'A' for calibration\n Press 'B' for Sensor Mode \n Press 'C' for Light RGB bulb for given rgb values\n");

}

int value()
{
  int val = 0;
  num="";
  while(1)
  {
  char key = customKeypad.getKey();
  if (key)
  { 
  if (key!= NO_KEY &&(key == '1' || key == '2'|| key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9'||key=='0')) 
    {  //lcd.print(key);
       Serial.print(key);
       num = num+key; }
  if (key == '#')
  {
    //lcd.clear();
    val = num.toInt();
    //lcd.print("value = ");
    return val;
  }}}}








