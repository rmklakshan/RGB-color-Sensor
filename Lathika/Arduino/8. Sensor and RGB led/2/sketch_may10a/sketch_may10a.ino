#include <Wire.h>;
#include <LiquidCrystal_I2C.h>;
LiquidCrystal_I2C disp(0x27,16,2);  //check I2C address before upload or simulate

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
// '+' sensor lights
// 'C'  mode selector
// '=' Enter

byte rowPins[Rows] = {12,8,7,6};
byte colPins[Cols] = {5,4,3,2};

Keypad customKeypad = Keypad(makeKeymap(Keys),rowPins,colPins, Rows, Cols);


// with 'C' and '=' and '+'

String R="0",G="0",B="0", num="";
int mode_num=0 , enter_num=0 ;
int R_=0 ,G_=0, B_=0;
int Rv=0, Gv=0, Bv=0;  // for ldr outputs
int sensorOn=0 , turn_S_on=0;  //checking sensor has used or not.  turn_S_on=0 : automatic sensor when it hasn't used
int RBG_R=0, RGB_G=0, RGB_B=0 , RGB_Bl=0, RGB_W=0; 


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
  disp.print("CAL");


}

void loop() {
  char key = customKeypad.getKey();

// MODE SELECTING KEY (mode_num = (0- calibration)(1- sensor)(2- RGB LED))
  if (key!= NO_KEY && key== 'C'){
    mode_num= mode_num + 1;
    enter_num =0;
    sensorOn=0;
    num="";
    if (mode_num==3){mode_num=0;}
    Serial.println("mode"+String(mode_num));
    }

//SENSOR input
  if ((key!= NO_KEY && key == '+')||turn_S_on==1){
    disp.clear();
    disp.setCursor(5,0);
    disp.print("SCANING");
    Rv=0;
    Gv=0;
    Bv=0;
    for (int i =0; i<4; i++){
      digitalWrite(A1,HIGH);
      delay(100);
      Rv = Rv + analogRead(A0);
      digitalWrite(A1,LOW);
      digitalWrite(A2,HIGH);
      delay(100);
      Gv = Gv + analogRead(A0);
      digitalWrite(A2,LOW);
      digitalWrite(A3,HIGH);
      delay(100);
      Bv = Bv + analogRead(A0);
      digitalWrite(A3,LOW);
    }
    Rv= round(Rv/4.0);
    Gv= round(Gv/4.0);
    Bv= round(Bv/4.0);
    disp.clear();
    
    sensorOn=1; // sensor has been used in this mode
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
    disp.print("RGB");

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
    lightRGB(R_,G_,B_);
    }

// SENSOR
    if (mode_num==1){
      if (sensorOn ==0){turn_S_on=1;}
      else {
        turn_S_on=0;

        R_ = 5+ Rv;  // function for red RGB value (should include the given RGB values in cal mode)
        G_ = 6+ Gv;  // function for green RGB value
        B_ = 7+ Bv;  // function for blue RGB value

        disp.clear();
        disp.setCursor(0,0);
        disp.print("R: "+ String(R_));
        disp.setCursor(8,0);
        disp.print("G: "+String(G_));
        disp.setCursor(0,1);
        disp.print("B: "+String(B_));
        disp.setCursor(13,1);
        disp.print("SEN");

        lightRGB(R_,G_,B_);
        }
      }

// CALIBRATE
    if (mode_num==0){
      if (sensorOn ==0){turn_S_on=1;}
      else {
        turn_S_on=0;
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
        enter_num=0;}
      num="";}
    
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
    }}

}
void lightRGB(int R_, int G_, int B_){

    analogWrite(11, R_);
    analogWrite(10, G_);
    analogWrite(9, B_);
  }


