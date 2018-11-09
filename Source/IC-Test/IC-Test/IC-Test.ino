#include <TFT.h>
#include "Arduino.h"
#include "PinStates.h"
#include "DebouncedButton.h"
#include "ClickButton.h"
#include "RepeatButton.h"
#include "Menu.h"
#include "Screen.h"

#pragma region socketSetup
void setupSocket() {
	SocketConfiguration::portMap[0] = A0;
	SocketConfiguration::portMap[1] = A1;
	SocketConfiguration::portMap[2] = A2;
	SocketConfiguration::portMap[3] = A3;
	SocketConfiguration::portMap[4] = A4;
	SocketConfiguration::portMap[5] = A5;
	SocketConfiguration::portMap[6] = A6;
	SocketConfiguration::portMap[7] = A7;
	SocketConfiguration::portMap[8] = A8;
	SocketConfiguration::portMap[9] = A9;
	SocketConfiguration::portMap[10] = A10;
	SocketConfiguration::portMap[11] = A11;
	SocketConfiguration::portMap[12] = A12;
	SocketConfiguration::portMap[13] = A13;
	SocketConfiguration::portMap[14] = A14;
	SocketConfiguration::portMap[15] = A15;

	SocketConfiguration::initialize();
}
#pragma endregion
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

// output: Arduino Output, IC Input
// input: Arduino Input, IC Output

const char* mainMenuItems[] = { "Automatische Erkennung","Auswahl","Manuell","CharMap"};
const char* autoDetectItems[] = { "Bitte IC einsetzen","und bestaetigen." };
const char* directTestItems[] = { "74LS00", "74LS02","74LS04", "74LS08","74LS10", "74LS14","74LS21", "74LS27","74LS32 ", "74LS51", "74LS194A"};
const char* manualPinMenuItems[SocketSize];

const int mainMenuItemCount = sizeof(mainMenuItems) / sizeof(char*);
const int autoDetectItemCount = sizeof(autoDetectItems) / sizeof(char*);
const int directTestItemCount = sizeof(directTestItems) / sizeof(char*);

Menu* mainMenu;
Menu* autoDetectMenu;
Menu* directTestMenu;
Menu* manualPinMenu;
Menu* currentMenu;

SocketConfiguration oldConfig;
SocketReading oldReading;

void handleMenus() {
	currentMenu->handleInput(buttons[0]->isPressed(), buttons[1]->isPressed(), buttons[2]->isPressed(), buttons[3]->isPressed());
	if (currentMenu == manualPinMenu) {
		for (int i = 0; i < SocketSize; i++) {
			auto line = toString(SocketConfiguration::get(i), SocketConfiguration::safeRead(i));
			if (line != manualPinMenuItems[i]) {
				manualPinMenuItems[i] = line;
				manualPinMenu->queueRepaint();
			}
		}
	}
}
void setupMenus() {
	for (int i = 0; i < SocketSize; i++) {
		manualPinMenuItems[i] = nullptr;
	}
	auto toMainMenu = [&](int index) { currentMenu = mainMenu; };
	mainMenu = new Menu(mainMenuItemCount, mainMenuItems, NULL, [&](int index) {
		switch (index) {
		case 0:
			currentMenu = autoDetectMenu;
			break;
		case 1:
			currentMenu = directTestMenu;
			break;
		case 2:
			currentMenu = manualPinMenu;
			break;
		default:
			break;
		}
	});
	autoDetectMenu = new Menu(autoDetectItemCount, autoDetectItems, toMainMenu, NULL);
	directTestMenu = new Menu(directTestItemCount, directTestItems, toMainMenu, NULL);
	manualPinMenu = new Menu(SocketSize, manualPinMenuItems, toMainMenu, [&](int index) {
		auto pinConfig = SocketConfiguration::get(index);
		SocketConfiguration::set(index, next(pinConfig));
	});
	currentMenu = mainMenu;
}

#pragma endregion

// the setup function runs once when you press reset or power the board
void setup() {

	Serial.begin(9600);
	setupSocket();
	setupButtons();
	setupMenus();
	setupScreen();
}

// the loop function runs over and over again until power down or reset
void loop() {
	handleButtons();
	handleMenus();
	screen->drawMenu(currentMenu);
}
