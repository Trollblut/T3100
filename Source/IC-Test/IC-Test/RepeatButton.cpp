#include "RepeatButton.h"

const unsigned long InitialRepeatWait = 2000;
const unsigned long MultiRepeatWait = 500;


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
		//Serial.println("Flanke Hoch");
		click = true;
		PressBegin = millis(); 
	}
	else if (debouncedState)
	{
		//Serial.println("Gedrueckt");
		if (millis() - PressBegin >= InitialRepeatWait) {
			PressBegin = millis() - ( InitialRepeatWait - MultiRepeatWait);
			click = true;
		}
	}



}
