#pragma once
#include <TFT.h>
#include "Menu.h"

class Screen
{
public:
	Screen(byte cs, byte dc, byte reset);
	~Screen();
	void drawMenu(Menu* menu);

private:
	TFT* screen;
	Menu* paintedMenu;
	int paintedIndex;
};

