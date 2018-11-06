#include "Screen.h"
#include "TFT.h"



Screen::Screen(byte cs, byte dc, byte reset)
{
	screen = new TFT(cs, dc, reset);
	screen->begin();
	screen->background(0, 0, 0);  // clear the screen with black
	screen->stroke(255, 255, 255);
}


Screen::~Screen()
{
}
