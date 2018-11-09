#include "PinStates.h"
#include "Arduino.h"

#define PortSwitchDelay 100

PinConfiguration socketState[SocketSize];


PinConfiguration next(PinConfiguration state)
{
	switch (state) {
	case PinConfiguration::LowOut:
		return PinConfiguration::HighOut;
	case PinConfiguration::HighOut:
		return PinConfiguration::Input;
	default:
		return PinConfiguration::LowOut;
	}
}
char* HighText = "High";
char* LowText = "Low";
char* UndefinedText = "Undefined";
char* InputText = "Input";
char* OutputText = "Output";

char* toString(PinConfiguration state) {
	switch (state) {
	case PinConfiguration::LowOut:
		return LowText;
	case PinConfiguration::HighOut:
		return HighText;
	case PinConfiguration::UndefinedOut:
		return UndefinedText;
	default:
		return InputText;
	}
}
char* toString(PinReading state) {
	switch (state) {
	case PinReading::LowIn:
		return LowText;
	case PinReading::HighIn:
		return HighText;
	default:
		return OutputText;
	}
}
char* TextLines[] = {
						"Low         Low",
						"Low         High",
						"Low         Output",
						"High        Low",
						"High        High",
						"High        Output",
						"Undefined   Low",
						"Undefined   High",
						"Undefined   Output",
						"Input       Low",
						"Input       High",
						"Input       Output" };
const int TextLineCount = sizeof(TextLines) / sizeof(char*);

char * toString(PinConfiguration config, PinReading reading)
{
	int index = config * 3 + reading;
	if (index < 0 || index > TextLineCount) {
		index = 0;
	}
	return TextLines[index];
}

SocketReading::SocketReading()
{
}

SocketReading::~SocketReading()
{
}

byte SocketConfiguration::portMap[SocketSize];

SocketConfiguration::SocketConfiguration()
{
	for (int i = 0; i < SocketSize; i++) {
		output[i] = PinConfiguration::LowOut;
	}
}

SocketConfiguration::SocketConfiguration(PinConfiguration initial)
{
	for (int i = 0; i < SocketSize; i++) {
		output[i] = initial;
	}
}

SocketConfiguration::~SocketConfiguration()
{
}

void SocketConfiguration::apply()
{
	for (int i = 0; i < SocketSize; i++) {
		set(portMap[i], output[i]);
	}
}

void SocketConfiguration::initialize()
{
	for (int i = 0; i < SocketSize; i++) {
		pinMode(portMap[i], OUTPUT);
		analogWrite(portMap[i],0);
		socketState[i] = PinConfiguration::LowOut;
	}
}

SocketConfiguration SocketConfiguration::getCurrentConfig()
{
	SocketConfiguration ret;
	for (int i = 0; i < SocketSize; i++) {
		ret.output[i] = socketState[i];
	}
	return ret;
}

PinConfiguration SocketConfiguration::get(byte port)
{
	return socketState[port];
}

void SocketConfiguration::set(byte port, PinConfiguration configuration)
{
	if (socketState[port] != configuration) {
		if (configuration == PinConfiguration::Input) {
			pinMode(portMap[port], INPUT);
		}
		else {
			pinMode(portMap[port], OUTPUT);
			analogWrite(portMap[port], configuration == PinConfiguration::HighOut ? 255 : 0);
		}
		socketState[port] = configuration;
	}
}

PinReading SocketConfiguration::safeRead(byte port)
{
	if (socketState[port] == PinConfiguration::Input) {
		return digitalRead(portMap[port]) ? PinReading::HighIn : PinReading::LowIn;
	}
	else {
		return PinReading::Output;
	}
}
SocketReading SocketConfiguration::safeReadAll()
{
	SocketReading ret;
	for (int i = 0; i < SocketSize; i++) {
		ret.input[i] = safeRead(i);
	}
	return ret;
}
PinReading SocketConfiguration::unsafeRead(byte port)
{
	PinConfiguration savedState = get(port);
	if (savedState != PinConfiguration::Input) {
		set(port, PinConfiguration::Input);
		delayMicroseconds(PortSwitchDelay);
		PinReading reading = digitalRead(portMap[port]) ? PinReading::HighIn : PinReading::LowIn;
		delayMicroseconds(PortSwitchDelay);
		set(port, savedState);
		return reading;
	}
	else {
		return digitalRead(portMap[port]) ? PinReading::HighIn : PinReading::LowIn;
	}
}

SocketReading SocketConfiguration::unsafeReadAll()
{
	SocketReading ret;
	for (int i = 0; i < SocketSize; i++) {
		ret.input[i] = unsafeRead(i);
	}
	return ret;
}

