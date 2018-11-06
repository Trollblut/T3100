#include "DebouncedButton.h"
#include "Arduino.h"

const unsigned long debounceWait = 25;


AbstractDebouncedButton::AbstractDebouncedButton(byte port)
{
	this->port = port;
	debouncedState = false;
	click = false;
	pinMode(port, INPUT);
	transitionPhase = false;
}

AbstractDebouncedButton::~AbstractDebouncedButton()
{
}

bool AbstractDebouncedButton::isPressed()
{
	if (click) {
		click = false;
		return true;
	}
	return false;
}

void AbstractDebouncedButton::handleDebounce()
{
	bool state = digitalRead(port);

	if (transitionPhase)
	{
		if (state == debouncedState) {
			transitionPhase = false;
		}
		else if (millis() - transitionBegin >= debounceWait) {
			debouncedState = !debouncedState;
			transitionPhase = false;
		}
	}
	else
	{
		if (state != debouncedState) {
			transitionPhase = true;
			transitionBegin = millis();

		}
	}
}
