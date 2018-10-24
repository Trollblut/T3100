/*
 Name:		IC_Test.ino
 Created:	24.10.2018 12:43:21
 Author:	mohr_s
*/

#define button1 45
#define button2 6

int zaehler = 0;
int lasthit = 0;
// the setup function runs once when you press reset or power the board
void setup() {

	Serial.begin(9600);
	pinMode(button1, INPUT);
	pinMode(button2, INPUT);
	
}

// the loop function runs over and over again until power down or reset
void loop() {
	int blub = digitalRead(button1);
	int blub2 = digitalRead(button2);
	
	if (blub == 1 && lasthit + 500 < millis())
	{
		zaehler++;
		lasthit = millis();
		Serial.println(zaehler);
	}

}
