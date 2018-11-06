#pragma once
#include "DebouncedButton.h"
class RepeatButton :
	public AbstractDebouncedButton
{
public:
	RepeatButton(byte port);
	~RepeatButton();
	void handleButton();

private: 
	unsigned long PressBegin;

};

