#pragma once
#include "IIntegratedCircuit.h"
#include "Arduino.h"

class ICNot :
	public IIntegratedCircuit
{
public:
	ICNot();
	~ICNot();

	byte GetPowerPin();
	byte GetGroundPin();
	byte GetInputCount();
	byte* GetInputs();
	byte GetOutputCount();
	byte* GetOutputs();
	Score GetScore(byte* data, unsigned int input, unsigned int output);

};

