void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);  
 pinMode(3, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2, LOW);
  delay(100);
bool a = digitalRead(3);
delay(100);
Serial.println(a);
digitalWrite(2, LOW);
delay(100);
 a = digitalRead(3);
 
  Serial.println(a);
  delay(800);
}
