#pragma once
#include "Score.h"
#include "Arduino.h"

class IIntegratedCircuit
{
public:
	IIntegratedCircuit();
	~IIntegratedCircuit();
	virtual byte GetPowerPin() const = 0;
	virtual byte GetGroundPin() const = 0;
	virtual byte GetInputCount() const = 0;
	virtual byte* GetInputs() const = 0;
	virtual byte GetOutputCount() const = 0;
	virtual byte* GetOutputs() const = 0;

	virtual Score GetScore(byte* data, unsigned int input, unsigned int output) const = 0;
};

