/*
 Name:    IC_Test.ino
 Created: 24.10.2018 12:43:21
 Author:  mohr_s
*/
#include <TFT.h>
#include <SPI.h>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define SCLK 52
#define MOSI 51
#define CS   10
#define DC   9
#define RESET 8 

int checkedMenuItem;

int ItemsProSide = 8;
int firstItem = 0;
int aktivesMenu = 0;

TFT myScreen = TFT(CS, DC, RESET);

struct menu
{
	char* Name;
	int XPosition;
	int YPosition;
	bool checked;
};


//Sturkur der Taster
struct button
{
	bool zeichenwiederholung;
	bool direction;
	int port;
	int pressedMillis;
	int pressed;
	void checkButton() {
		pressed = digitalRead(port);
		
		Serial.println("Mein digitaler wert ist  ");
		Serial.print(pressed);

		if (pressed)
		{
			pressedMillis = millis();
		}
		Serial.println(" und mein wert ist ");
		Serial.print(pressed);
	}
};

menu Menu1[11];
menu Menu0[11];
button Buttons[4];
int buttonCount = sizeof(Buttons) / sizeof(button);

void initMenu0() {
	Menu0[0].Name = "Automatisch";
	Menu0[0].XPosition = 10;
	Menu0[0].YPosition = 10;
	Menu0[0].checked = 1;
		
	Menu0[1].Name = "Manuelle Auswahl";
	Menu0[1].XPosition = 10;
	Menu0[1].YPosition = 25;
	Menu0[1].checked = 0;
}

void initMenu1() {
	Menu1[0].Name = "74LS00";
	Menu1[0].XPosition = 10;
	Menu1[0].YPosition = 10;
	Menu1[0].checked = 1;

	Menu1[1].Name = "74LS02";
	Menu1[1].XPosition = 10;
	Menu1[1].YPosition = 25;
	Menu1[1].checked = 0;

	Menu1[2].Name = "74LS04";
	Menu1[2].XPosition = 10;
	Menu1[2].YPosition = 40;
	Menu1[2].checked = 0;

	Menu1[3].Name = "74LS08";
	Menu1[3].XPosition = 10;
	Menu1[3].YPosition = 55;
	Menu1[3].checked = 0;

	Menu1[4].Name = "74LS10";
	Menu1[4].XPosition = 10;
	Menu1[4].YPosition = 70;
	Menu1[4].checked = 0;

	Menu1[5].Name = "74LS14";
	Menu1[5].XPosition = 10;
	Menu1[5].YPosition = 85;
	Menu1[5].checked = 0;

	Menu1[6].Name = "74LS21";
	Menu1[6].XPosition = 10;
	Menu1[6].YPosition = 100;
	Menu1[6].checked = 0;


	Menu1[7].Name = "74LS27";
	Menu1[7].XPosition = 10;
	Menu1[7].YPosition = 115;
	Menu1[7].checked = 0;

	Menu1[8].Name = "74LS32"; 
	Menu1[8].XPosition = 10;
	Menu1[8].YPosition = 130;
	Menu1[8].checked = 0;

	Menu1[9].Name = "74LS51";
	Menu1[9].XPosition = 10;
	Menu1[9].YPosition = 145;
	Menu1[9].checked = 0;

	Menu1[10].Name = "74LS194A";
	Menu1[10].XPosition = 10;
	Menu1[10].YPosition = 160;
	Menu1[10].checked = 0;
}

void initButtons()
{
	//Button zum zurückspringen im Menü
	Buttons[LEFT].zeichenwiederholung = false;
	//1 heißt links
	Buttons[LEFT].direction = 1;
	Buttons[LEFT].port = 22;
	Buttons[LEFT].pressed = 0;


	//Button um Menüpunkt zu wählen 
	Buttons[RIGHT].zeichenwiederholung = false;
	//0 heißt rechts
	Buttons[RIGHT].direction = 0;
	Buttons[RIGHT].port = 24;
	Buttons[RIGHT].pressed = 0;

	//Button um im Menü weiter nach oben zu gehen
	Buttons[UP].zeichenwiederholung = true;
	//1 heißt hoch
	Buttons[UP].direction = 1;
	Buttons[UP].port = 26;
	Buttons[UP].pressed = 0;

	//Button um im Menü weiter nach unten zu gehen
	Buttons[DOWN].zeichenwiederholung = true;
	//0 heipt runter
	Buttons[DOWN].direction = 0;
	Buttons[DOWN].port = 28;
	Buttons[DOWN].pressed = 0;
}


void checkButtons() {
	for (int i = 0; i < buttonCount; i++)
	{
		Buttons[i].checkButton();

		Serial.println("Hallo ich bin Button ");
		Serial.print( i);
	}
}
void guiActions() {
	int directionLeftRight = (Buttons[LEFT].pressed - Buttons[RIGHT].pressed);
	if (directionLeftRight)
	{
		//gehe von Menu0 zu Menu1 bzw wähle Bautein aus
		if (aktivesMenu = 0)
		{
			printMenu1();
		}
		else
		{
			//check vorgegebenen Baustein -> BAstiiiii 
		}
	}
	else
	{
		//wenn in menu0 dann gar nichts, sonst zurück zu menu0

		if (aktivesMenu = 1)
		{
			printMenu0();
		}

	}

	int directionTopDown = ( Buttons[DOWN].pressed-Buttons[UP].pressed);
	if (directionTopDown)
	{
		shiftdirectionTopDown(directionTopDown);
	}
}


void shiftdirectionTopDown(int direction)
{
	Menu1[checkedMenuItem].checked = false;
	if (checkedMenuItem < (firstItem + ItemsProSide) && checkedMenuItem > firstItem)
	{
		checkedMenuItem = checkedMenuItem + direction;
		Menu1[checkedMenuItem].checked = true;
	}
	else
	{
		Serial.println("Jetzt sind wir am Arsch");
	}
}


void printMenu1()
{
	for (int i = 0; i < 8; i++)
	{

		//Wenn Index checked dann blau, sonst weiß
		if (Menu1[i].checked == 1)
		{
			Serial.print("Ich werde blau");
			Serial.print(i);
			checkedMenuItem = i;
			myScreen.stroke(255, 10, 20);
		}
		else
		{
			Serial.print("Ich werde weiß");
			Serial.print(i);
			myScreen.stroke(255, 255, 255);
		}
		//Text in jeweiliger Farbe ausgeben
		myScreen.text(Menu1[i].Name, int(Menu1[i].XPosition), int(Menu1[i].YPosition));
	}
}

void printMenu0()
{
	for (int i = 0; i < 8; i++)
	{

		//Wenn Index checked dann blau, sonst weiß
		if (Menu1[i].checked == 1)
		{
			Serial.print("Ich werde blau");
			Serial.print(i);
			checkedMenuItem = i;
			myScreen.stroke(255, 20, 20);
		}
		else
		{
			Serial.print("Ich werde weiß");
			Serial.print(i);
			myScreen.stroke(255, 255, 255);
		}
		//Text in jeweiliger Farbe ausgeben
		myScreen.text(Menu0[i].Name, int(Menu0[i].XPosition), int(Menu0[i].YPosition));
	}
}




// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	initMenu1();
	initMenu0();
	myScreen.begin();
	myScreen.background(0, 0, 0);  // clear the screen with black
	myScreen.stroke(255, 255, 255);
	myScreen.setTextSize(1.7);
}

// the loop function runs over and over again until power down or reset
void loop() {
	int i = 1;
	//printMenu1();
	printMenu0();
	checkButtons();
	guiActions();

	delay(8000);

}
