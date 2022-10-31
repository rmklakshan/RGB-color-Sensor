int R = 11;
int G = 10;
int B = 9 ;

void setup() {
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);

}

void loop() {
  analogWrite(R,150);
  analogWrite(G,0);
  analogWrite(B,200);
  

}
