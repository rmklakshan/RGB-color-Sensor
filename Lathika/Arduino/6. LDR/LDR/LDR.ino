const int ldr = A0;


void setup() {
  Serial.begin(9600);

  pinMode(ldr,INPUT);
  pinMode(13,OUTPUT);
}

void loop() {
  int rd = analogRead(ldr);
  if (rd>500){
    digitalWrite(13,HIGH);}
   else{
    digitalWrite(13,LOW);}
  Serial.println(rd);
  delay(1000);

}
