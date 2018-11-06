#include <TFT.h>
#include "Arduino.h"
#include "DebouncedButton.h"
#include "RepeatButton.h"
#include "Screen.h"
#include "ClickButton.h"
#include "Menu.h"

#
/*
 Name:		IC_Test.ino
 Created:	24.10.2018 12:43:21
 Author:	mohr_s
*/

#pragma region buttonSetup 

#define ButtonCount 4
#define Up 0
#define UpPort 2
#define Right 1
#define RightPort 3
#define Down 2
#define DownPort 4
#define Left 3
#define LeftPort 5

AbstractDebouncedButton* buttons[ButtonCount];

void setupButtons() {
	buttons[Up] = new RepeatButton(UpPort);
	buttons[Right] = new ClickButton(RightPort);
	buttons[Down] = new RepeatButton(DownPort);
	buttons[Left] = new ClickButton(LeftPort);
}
void handleButtons() {
	for (int i = 0; i < ButtonCount; i++) {
		buttons[i]->handleButton();
	}
}
#pragma endregion
#pragma region screenSetup 

#define CS   10
#define DC   9
#define RESET 8 
Screen* screen = (Screen*)NULL;
void setupScreen() {
	screen = new Screen(CS,DC,RESET);
}
#pragma endregion
#pragma region menuSetup 

char* mainMenuItems[] = { "Automatische Erkennung","Auswahl"};
char* autoDetectItems[] = { "Bitte IC einsetzen und bestätigen." };
char* directTestItems[] = { "IC 1", "IC2" };



#pragma endregion
int zaehler = 0;
int lasthit = 0;
// the setup function runs once when you press reset or power the board
void setup() {

	Serial.begin(9600);
	setupButtons();
	setupScreen();
}
int count1 = 0;
int count2 = 0;

// the loop function runs over and over again until power down or reset
void loop() {
	handleButtons();
}
