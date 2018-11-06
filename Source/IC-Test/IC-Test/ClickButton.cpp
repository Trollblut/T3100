#include "ClickButton.h"



ClickButton::ClickButton(byte port): AbstractDebouncedButton(port)
{
}


ClickButton::~ClickButton()
{
}

void ClickButton::handleButton()
{
	bool before = debouncedState;
	handleDebounce();
	if (before && !debouncedState) {
		click = true;
	}
}
