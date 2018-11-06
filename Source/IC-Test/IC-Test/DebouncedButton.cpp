#include "DebouncedButton.h"
#include "Arduino.h"

const unsigned long debounceWait = 25;


DebouncedButton::DebouncedButton(byte port)
{
	this->port = port;
	debouncedState = false;
	pinMode(port, INPUT);
	transitionPhase = false;
}

DebouncedButton::~DebouncedButton()
{
}

bool DebouncedButton::isPressed()
{
	if (click) {
		click = false;
		return true;
	}
	return false;
}

void DebouncedButton::handleButton()
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
			if (!debouncedState) {
				click = true;

			}
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
