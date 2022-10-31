void setup() {
  // put your setup code here, to run once:
pinMode(4,INPUT_PULLUP);
pinMode(7,OUTPUT); //LED
}

void loop() {
if(digitalRead(4)==LOW){// Reading the switch to be on
 digitalWrite(7,HIGH);} // light the LED
 
else{
  digitalWrite(7,LOW);} //LED off
}
  // put your main code here, to run repeatedly:


