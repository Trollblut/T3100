#pragma once
#include "Arduino.h"
class AbstractDebouncedButton
{
public:
	AbstractDebouncedButton(byte port);
	~AbstractDebouncedButton();

	bool isPressed();
	virtual void handleButton() = 0; 

protected:
	void handleDebounce();
	bool debouncedState;
	bool click;

private: 
	byte port; 
	bool transitionPhase; 

	unsigned long transitionBegin ;

};

