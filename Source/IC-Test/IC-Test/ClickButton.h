#pragma once
#include "DebouncedButton.h"
class ClickButton :
	public AbstractDebouncedButton
{
public:
	ClickButton(byte port);
	~ClickButton();
	void handleButton();
};

