#include "Arduino.h"
#include "DebouncedButton.h"
#include "RepeatButton.h"
#include "ClickButton.h"

/*
 Name:		IC_Test.ino
 Created:	24.10.2018 12:43:21
 Author:	mohr_s
*/

#define button1 45
#define button2 6


AbstractDebouncedButton* buttons[4];
int zaehler = 0;
int lasthit = 0;
// the setup function runs once when you press reset or power the board
void setup() {

	Serial.begin(9600);
	buttons[0] = new ClickButton(10);
	buttons[1] = new RepeatButton(11);
	
}
int count1 = 0;
int count2 = 0;

// the loop function runs over and over again until power down or reset
void loop() {
	buttons[0]->handleButton();
	buttons[1]->handleButton();

	if (buttons[0]->isPressed()) {
		Serial.println("Boo1!");
		Serial.println(++count1);

	}
	if (buttons[1]->isPressed()) {
		Serial.println("Boo2!");
		Serial.println(++count2);

	}
}
