#include <Wire.h>;
#include <LiquidCrystal_I2C.h>;
LiquidCrystal_I2C disp(0x27,16,2);

#include <Keypad.h>;

const byte Rows = 4;
const byte Cols = 4;

char Keys[Rows][Cols] = { 
  {'7' ,'8','9','/'},
  {'4','5','6','*'},
  {'1','2','3','-'},
  {'C','0','=','+'}
  };

// '/' R
// '*' G
// '-' B
// '+' backspace
// 'C'  mode selector
// '=' Enter

byte rowPins[Rows] = {12,8,7,6};
byte colPins[Cols] = {5,4,3,2};

Keypad customKeypad = Keypad(makeKeymap(Keys),rowPins,colPins, Rows, Cols);

// this code is only for 4x3 key pad
// with 'C' and '='

String R="0",G="0",B="0", num="";
int mode_num=0 , enter_num=0 ;
int R_=0 ,G_=0, B_=0;
int S_C =0;  // sensor or calibration
int Rv=0, Gv=0, Bv=0;  // for ldr outputs

int RedArr[] = {120,130}; // arrays to store ldr inputs valuse with corresponding RGB values in the next array
int RedRGB[] = {200,240}; // Always input numbers with 3 digits
int GreenArr[] = {120,130};
int GreenRGB[] = {200,240};
int BlueArr[] = {120,130};
int BlueRGB[] = {200,240};

int lR,lG,lB; // lengths of arrays

void setup() {
  // RGB LED
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);

  // SENSOR
  pinMode(A0,INPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  Serial.begin(9600);

  // DISPLAY
  disp.begin(16,2);
  
  disp.setCursor(0,0);
  disp.print("R:");
  disp.setCursor(8,0);
  disp.print("G:");
  disp.setCursor(0,1);
  disp.print("B:");
  disp.setCursor(15,1);
  disp.print("SEN");

}

void loop() {
  char key = customKeypad.getKey();
Serial.println(key);
// MODE SELECTING KEY (mode_num = (0- sensor)(1- calibration)(2- RGB LED))
  if (key!= NO_KEY && key== 'C'){
    mode_num= mode_num + 1;
    enter_num =0;
    num="";
    if (mode_num==3){mode_num=0;}
    Serial.println("mode"+String(mode_num));
    }



// KEYPAD VALUES
  else if (key!=NO_KEY && (key== '1'||key == '2'|| key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9'||key=='0')){
    num = num + key;
    }

// RGB LED

  if (mode_num==2){
    disp.clear();
    disp.setCursor(0,0);
    disp.print("R: "+R);
    disp.setCursor(8,0);
    disp.print("G: "+G);
    disp.setCursor(0,1);
    disp.print("B: "+B);
    disp.setCursor(13,1);
    disp.print("LED");


    if (key!= NO_KEY && key== '=' ){
      enter_num = enter_num +1;
      if (enter_num==3){
        enter_num=0;
        }
      num="";
      }
    
    if (enter_num==0){  //Red
      if ( num.length() >0){
      R = num;
      R_ = R.toInt();}
      }
    else if (enter_num==1){  //Green
      if ( num.length() >0){
      G = num;
      G_ = G.toInt();}
      }
    else if (enter_num==2){  //Blue
      if ( num.length() >0){
      B = num;
      B_ = B.toInt();}
      }


    analogWrite(11, R_);
    analogWrite(10, G_);
    analogWrite(9, B_);
      }
// Sensor & calib
  else if (mode_num==0 || mode_num ==1){
    digitalWrite(A1,HIGH);
    delay(100);
    Rv = analogRead(A0);
    delay(100);
    digitalWrite(A1,LOW);
    delay(100);
    digitalWrite(A2,HIGH);
    delay(100);
    Gv = analogRead(A0);
    delay(100);
    digitalWrite(A2,LOW);
    delay(100);
    digitalWrite(A3,HIGH);
    delay(100);
    Bv = analogRead(A0);
    delay(100);
    digitalWrite(A3,LOW);
    delay(100);

    Serial.print("values");
    Serial.println("R "+String(Rv));
    Serial.println("G "+String(Gv));
    Serial.println("B "+String(Bv));

// SENSOR
    if (mode_num==0){
      
      // red
      int R_val=0;
      int R_ind =0;
      for (int ind= 0; ind < (sizeof(RedRGB)/(sizeof(RedRGB[0])));ind++){  // to get index we have used RGB array, because we can always give 3 numbers for them
        if (ind==0){
          R_val= abs(Rv - RedArr[0]);}
        else if (R_val> abs(Rv - RedArr[ind])){
          R_val=abs(Rv - RedArr[ind]);
          R_ind=ind;}
         }
      R_= RedRGB[R_ind];

      // green
      int G_val=0;
      int G_ind =0;
      for (int ind= 0; ind < (sizeof(GreenRGB)/sizeof(GreenRGB[0]));ind++){  // to get index we have used RGB array, because we can always give 3 numbers for them
        if (ind==0){
          G_val= abs(Gv - GreenArr[0]);}
        else if (G_val> abs(Gv - GreenArr[ind])){
          G_val=abs(Gv - GreenArr[ind]);
          G_ind=ind;}
         }
      G_= GreenRGB[G_ind];

      //blue
      int B_val=0;
      int B_ind =0;
      for (int ind= 0; ind < (sizeof(BlueRGB)/sizeof(BlueRGB[0]));ind++){  // to get index we have used RGB array, because we can always give 3 numbers for them
        if (ind==0){
          B_val= abs(Bv - BlueArr[0]);}
        else if (B_val> abs(Bv - BlueArr[ind])){
          B_val=abs(Bv - BlueArr[ind]);
          B_ind=ind;}
         }
      B_= BlueRGB[B_ind];

    disp.clear();
    disp.setCursor(0,0);
    disp.print("R: "+ String(R_));
    disp.setCursor(8,0);
    disp.print("G: "+String(G_));
    disp.setCursor(0,1);
    disp.print("B: "+String(B_));
    disp.setCursor(13,1);
    disp.print("SEN");
  

    analogWrite(11, R_);
    analogWrite(10, G_);
    analogWrite(9, B_);
    

      }
// CALIBRATE
    if (mode_num==1){
    disp.clear();
    disp.setCursor(0,0);
    disp.print("R: 0");
    disp.setCursor(8,0);
    disp.print("G: 0");
    disp.setCursor(0,1);
    disp.print("B: 0");
    disp.setCursor(13,1);
    disp.print("CAL");

    if (key!= NO_KEY && key== '=' ){
      enter_num = enter_num +1;
      if (enter_num==3){
      int ind= (sizeof(BlueRGB)/sizeof(BlueRGB[0]));
      if (B.length()==1){
        B="00"+B;}
      else if (B.length()==2){
        B="0"+B;}
        BlueRGB[ind]= B.toInt();
        BlueArr[ind] = Bv;
        enter_num=0;
        }
      num="";
      }
    
    if (enter_num==0){  //Red
      R = num;
      disp.setCursor(3,0);
      disp.print(R);
      if ( num.length() >0){
      R_ = R.toInt();}
      }
    else if (enter_num==1){  //Green
      int ind= (sizeof(RedRGB)/(sizeof(RedRGB[0])));
      if (R.length()==1){
        R="00"+R;}
      else if (R.length()==2){
        R="0"+R;}
        RedRGB[ind]= R.toInt();
        RedArr[ind] = Rv;
      G = num;
      disp.setCursor(11,0);
      disp.print(G);
      if ( num.length() >0){
      G_ = G.toInt();}
      }
    else if (enter_num==2){  //Blue
      int ind= (sizeof(GreenRGB)/sizeof(GreenRGB[0]));
      if (G.length()==1){
        G="00"+G;}
      else if (G.length()==2){
        G="0"+G;}
        GreenRGB[ind]= G.toInt();
        GreenArr[ind] = Gv;
      B = num;
      disp.setCursor(3,1);
      disp.print(B);
      if ( num.length() >0){
      B_ = B.toInt();}
      }

    analogWrite(11, R_);
    analogWrite(10, G_);
    analogWrite(9, B_);
    
      }


    } 
}
