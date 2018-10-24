void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

}

void loop() {

digitalWrite(0,1);
digitalWrite(1,0);
digitalWrite(2,1);
digitalWrite(3,1);
digitalWrite(4,1);

delay(500);
int a = digitalRead(5);
Serial.println(a);



}
