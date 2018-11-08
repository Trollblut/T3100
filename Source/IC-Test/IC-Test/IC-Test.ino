#include <TFT.h>
#include "Arduino.h"
#include "DebouncedButton.h"
#include "RepeatButton.h"
#include "Screen.h"
#include "ClickButton.h"
#include "Menu.h"

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

const char* mainMenuItems[] = { "Automatische Erkennung","Auswahl"};
const int mainMenuItemCount = sizeof(mainMenuItems) / sizeof(char*);
const char* autoDetectItems[] = { "Bitte IC einsetzen","und bestaetigen." };
const int autoDetectItemCount = sizeof(autoDetectItems) / sizeof(char*);
const char* directTestItems[] = { "IC 1", "IC 2","IC 3", "IC 4","IC 5", "IC 6","IC 7", "IC 8","IC 9", "IC 10" };
const int directTestItemCount = sizeof(directTestItems) / sizeof(char*);

Menu* mainMenu;
Menu* autoDetectMenu;
Menu* directTestMenu;
Menu* currentMenu;

void setupMenus() {
	auto toMainMenu = [&](int index) { currentMenu = mainMenu; };
	mainMenu = new Menu(mainMenuItemCount, mainMenuItems, NULL, [&](int index) {
		switch (index) {
		case 0:
			currentMenu = autoDetectMenu;
			break;
		case 1:
			currentMenu = directTestMenu;
			break;
		default:
			break;
		}
	});
	autoDetectMenu = new Menu(autoDetectItemCount, autoDetectItems, toMainMenu, NULL);
	directTestMenu = new Menu(directTestItemCount, directTestItems, toMainMenu, NULL);
	currentMenu = mainMenu;
}

#pragma endregion

// the setup function runs once when you press reset or power the board
void setup() {

	Serial.begin(9600);
	setupButtons();
	setupMenus();
	setupScreen();
}

// the loop function runs over and over again until power down or reset
void loop() {
	handleButtons();
	currentMenu->handleInput(buttons[0]->isPressed(), buttons[1]->isPressed(), buttons[2]->isPressed(), buttons[3]->isPressed());
	screen->drawMenu(currentMenu);
}
