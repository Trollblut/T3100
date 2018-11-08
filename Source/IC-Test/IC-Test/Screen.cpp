#include "Screen.h"
#include "TFT.h"

#define LineCount 4
#define OffsetX 10
#define OffsetY 10
#define LineHight 20
#define ActiveColor 0xFFFF
#define InactiveColor 0x8888

Screen::Screen(byte cs, byte dc, byte reset)
{
	screen = new TFT(cs, dc, reset);
	screen->begin();
	screen->background(0, 0, 0);  // clear the screen with black
	screen->stroke(255, 255, 255);

	paintedMenu = nullptr;
	paintedIndex = 0;
}


Screen::~Screen()
{
}

void Screen::drawMenu(Menu * menu)
{
	int selectedItem = menu->getSelectedIndex();
	if (menu != paintedMenu || selectedItem / LineCount != paintedIndex / LineCount) {
		Serial.println("Print new");
		screen->background(0, 0, 0);
		int offset = (selectedItem / LineCount) * LineCount;
		int limit = min(menu->getItemCount() - offset, LineCount);
		int selectedLine = selectedItem % LineCount;
		Serial.println(limit);
		for (int i = 0; i < limit; i++) {
			Serial.println(i);
			if (i == selectedLine) {
				Serial.println("Active");
				screen->stroke(255, 255, 255);
			}
			else {
				Serial.println("Inctive");
				screen->stroke(85, 85, 85);
			}
			screen->text(menu->getItem(offset + i), OffsetX, OffsetY + i * LineHight);
			Serial.println(menu->getItem(offset + i));
		}
		paintedMenu = menu;
		paintedIndex = selectedItem;
	}
	else if (paintedIndex != selectedItem) {
		Serial.println("Adapt selection");
		screen->stroke(255, 255, 255);
		screen->text(menu->getItem(selectedItem), OffsetX, OffsetY + (selectedItem % LineCount) * LineHight);
		screen->stroke(85, 85, 85);
		screen->text(menu->getItem(paintedIndex), OffsetX, OffsetY + (paintedIndex % LineCount) * LineHight);
		paintedIndex = selectedItem;
	}
}
