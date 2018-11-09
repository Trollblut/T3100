#pragma once
#include "Arduino.h"

#define SocketSize 16

enum PinConfiguration {
	LowOut,
	HighOut,
	UndefinedOut,
	Input
};

enum PinReading {
	LowIn,
	HighIn,
	Output
};

PinConfiguration next(PinConfiguration state);
char* toString(PinConfiguration state);
char* toString(PinReading state);
char* toString(PinConfiguration config, PinReading reading);

struct SocketReading {
	SocketReading();
	~SocketReading();
	PinReading input[SocketSize];
};
struct SocketConfiguration {
	PinConfiguration output[SocketSize];

	SocketConfiguration();
	SocketConfiguration(PinConfiguration initial);
	~SocketConfiguration();

	void apply();
	static byte portMap[SocketSize];
	static void initialize();
	static SocketConfiguration getCurrentConfig();
	static PinConfiguration get(byte port);
	static void set(byte port, PinConfiguration configuration);
	static PinReading safeRead(byte port);
	static SocketReading safeReadAll();
	static PinReading unsafeRead(byte port);
	static SocketReading unsafeReadAll();
};