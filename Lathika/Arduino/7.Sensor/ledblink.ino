const byte red_pin = A1;
const byte green_pin = A2;
const byte blue_pin = A3;


void setup() {
Serial.begin(9600);

//sensor
pinMode(red_pin,OUTPUT);
pinMode(green_pin,OUTPUT);
pinMode(blue_pin,OUTPUT);
pinMode(A0,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
{int r=0,g=0,b=0,Rv=0,Gv=0,Bv=0;
 Serial.println("Wait....");
  for (int i =0 ; i < 3; i++)
  {
    digitalWrite(red_pin,HIGH);
    delay(100);
    Rv=analogRead(A0); 
    Serial.println(1023-Rv);
    r+=Rv;
    digitalWrite(red_pin,LOW);
    delay(100);
    
    digitalWrite(green_pin,HIGH);
    delay(100);
    Gv=analogRead(A0);
    Serial.println(1023-Gv);
    g+=Gv;
    digitalWrite(green_pin,LOW);
    delay(100);
    
    digitalWrite(blue_pin,HIGH);
    delay(100);
    Bv=analogRead(A0);
    Serial.println(1023-Bv);
    b+=Bv;
  
    digitalWrite(blue_pin,LOW);
    delay(100);
  }
  r=round(r/3.0);g=round(g/3.0);b=round(b/3.0);
      Serial.println(1023-r);
      Serial.println(1023-g);
      Serial.println(1023-b);
      delay(10000);
}}
