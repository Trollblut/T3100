#include "ICNot.h"
#include "Arduino.h"


byte Inputs[] = { 0,2,4,10,12,14 };
byte Outputs[] = { 1,3,5,9,11,13 };

ICNot::ICNot()
{
}

ICNot::~ICNot()
{
}

byte ICNot::GetPowerPin() {
	return 15;
}

byte ICNot::GetGroundPin() {
	return 6;
}

byte ICNot::GetInputCount() {
	return sizeof(Inputs) / sizeof(Inputs[0]);
}

byte* ICNot::GetInputs() {
	byte* ret = &Inputs[0];
}

byte ICNot::GetOutputCount() {
	return sizeof(Outputs) / sizeof(Outputs[0]);
}

byte* ICNot::GetOutputs() {
	byte* ret = &Outputs[0];
}

Score ICNot::GetScore(byte* data, unsigned int input, unsigned int output) {
	if (input & (1 << GetPowerPin()) || !(input & 1 << GetGroundPin())) {

	}
}