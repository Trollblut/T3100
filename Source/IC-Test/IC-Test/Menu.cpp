#include "Menu.h"
#include "Arduino.h"



Menu::Menu(int itemCount, char ** itemList, void back(int index), void forward(int index))
{
	this->itemCount = itemCount;
	this->itemList = itemList;
	this->back = back;
	this->forward = forward;
	selectedIndex = 0;
	repaint = false;
}

Menu::~Menu()
{
}

void Menu::handleInput(bool up, bool right, bool down, bool left)
{
	if (up) {
		if (selectedIndex == 0) {
			selectedIndex = itemCount;
		}
		selectedIndex--;
	}
	if (down) {
		selectedIndex++;
		if (selectedIndex == itemCount) {
			selectedIndex = 0;
		}
	}
	if (right && forward) {
		forward(selectedIndex);
	}
	if (left && back) {
		back(selectedIndex);
	}
}

int Menu::getSelectedIndex()
{
	return selectedIndex;
}

char * Menu::getItem(int index)
{
	if (index < 0 || index >= itemCount) {
		return (char*)NULL;
	}
	return itemList[index];
}

int Menu::getItemCount()
{
	return itemCount;
}

void Menu::queueRepaint()
{
	repaint = true;
}

bool Menu::requiresRepaint()
{
	if (repaint) {
		repaint = false;
		return true;
	}
	return false;
}
