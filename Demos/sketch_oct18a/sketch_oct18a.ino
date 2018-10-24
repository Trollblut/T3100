void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

}

void loop() {

analogWrite(2,128);
digitalWrite(3,LOW);
digitalWrite(4,HIGH);
digitalWrite(5,LOW);
digitalWrite(6,HIGH);

analogWrite(A0,0);

delay(500);
int a = digitalRead(7);
Serial.println(a);



}
