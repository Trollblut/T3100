#pragma once
#include "Arduino.h"
class DebouncedButton
{
public:
	DebouncedButton(byte port);
	~DebouncedButton();

	bool isPressed();
	void handleButton(); 

private: 
	byte port; 
	bool debouncedState;
	bool transitionPhase; 
	bool click;

	unsigned long transitionBegin ;

};

