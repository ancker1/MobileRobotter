#include "DTMF.h"
#include <iostream>


DTMF::DTMF(int lowfrequency, int highfrequency)
{
	low_frequency = lowfrequency;
	high_frequency = highfrequency;

	double f1 = low_frequency;
	double f2 = high_frequency;
	tone.setFrequencies(f1, f2);
}

DTMF::DTMF(char dtmfChar)
{
	switch (dtmfChar)
	{
	case '1': case '2': case '3': case 'A':
		low_frequency = 697;
		break;
	case '4': case '5': case '6': case 'B':
		low_frequency = 770;
		break;
	case '7': case '8': case '9': case 'C':
		low_frequency = 852;
		break;
	case '*': case '0': case '#': case 'D':
		low_frequency = 941;
		break;
	default:
		break;
	}

	switch (dtmfChar)
	{
	case '1': case '4': case '7': case '*':
		high_frequency = 1209;
		break;
	case '2': case '5' : case '8': case '0':
		high_frequency = 1336;
		break;
	case '3': case '6': case '9': case '#':
		high_frequency = 1477;
		break;
	case 'A': case 'B': case 'C': case 'D':
		high_frequency = 1633;
		break;
	default:
		cout << "invalid character" << endl;
		break;
	}

	double f1 = low_frequency;
	double f2 = high_frequency;
	tone.setFrequencies(f1, f2);
}

string DTMF::checkDTMF()
{
	return "The low-tone frequency is: " + to_string(low_frequency) + ", The high-tone frequency is: " + to_string(high_frequency) + ".";
}

SFMLtone DTMF::getTone() {
	return tone;
}

int DTMF::getLow()
{
	return low_frequency;
}

int DTMF::getHigh()
{
	return high_frequency;
}

DTMF::~DTMF()
{
}
