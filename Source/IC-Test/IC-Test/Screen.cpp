#include "Screen.h"
#include "TFT.h"

#define LineCount 6
#define OffsetX 3
#define OffsetY 10
#define LineHight 19
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

char buffer[64];

char* getString(char *destination, int index, char* src) {
	buffer[0] = ' ';
	itoa(index, index < 10 ? buffer + 1 : buffer, 10);

	strcat(destination, ": ");
	strcat(destination, src);
	return destination;

}
void Screen::drawMenu(Menu * menu)
{
	int selectedItem = menu->getSelectedIndex();
	if (menu->requiresRepaint() || menu != paintedMenu || selectedItem / LineCount != paintedIndex / LineCount) {
		screen->background(0, 0, 0);
		int offset = (selectedItem / LineCount) * LineCount;
		int limit = min(menu->getItemCount() - offset, LineCount);
		int selectedLine = selectedItem % LineCount;
		for (int i = 0; i < limit; i++) {
			if (i == selectedLine) {
				screen->stroke(255, 255, 255);
			}
			else {
				screen->stroke(85, 85, 85);
			}
			screen->text(getString(buffer, offset + i + 1, menu->getItem(offset + i)), OffsetX, OffsetY + i * LineHight);
		}
		paintedMenu = menu;
		paintedIndex = selectedItem;
	}
	else if (paintedIndex != selectedItem) {
		screen->stroke(255, 255, 255);
		screen->text(getString(buffer, selectedItem + 1, menu->getItem(selectedItem)), OffsetX, OffsetY + (selectedItem % LineCount) * LineHight);
		screen->stroke(85, 85, 85);
		screen->text(getString(buffer, paintedIndex + 1, menu->getItem(paintedIndex)), OffsetX, OffsetY + (paintedIndex % LineCount) * LineHight);
		paintedIndex = selectedItem;
	}
}
