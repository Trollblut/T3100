#include "RepeatButton.h"

const unsigned long InitialRepeatWait = 800;
const unsigned long MultiRepeatWait = 300;


RepeatButton::RepeatButton(byte port) : AbstractDebouncedButton(port)
{
	
}


RepeatButton::~RepeatButton()
{
}

void RepeatButton::handleButton()
{
	bool before = debouncedState;
	handleDebounce();
	if (!before && debouncedState) {
		click = true;
		PressBegin = millis(); 
	}
	else if (debouncedState)
	{
		if (millis() - PressBegin >= InitialRepeatWait) {
			PressBegin = millis() - ( InitialRepeatWait - MultiRepeatWait);
			click = true;
		}
	}



}
