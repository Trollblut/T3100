#include "Util.h"

int Bits[] = { 0,1,1,2,
			  1,2,2,3,
			  1,2,2,3,
			  2,3,3,4 };
int CountBits(byte* data, int length)
{
	int sum = 0;
	for (int i = 0; i < length; i++) {
		sum += Bits[*data & 0xF];
		sum += Bits[*data >> 4];
		data++;
	}
}

void SetBit(byte * data, int index)
{
	data += index >> 3;
	*data |= 1 << (index & 7);
}

void UnsetBit(byte * data, int index)
{
	data += index >> 3;
	*data &=  ~(1 << (index & 7));
}

void ToggleBit(byte * data, int index)
{
	data += index >> 3;
	*data ^= 1 << (index & 7);
}
