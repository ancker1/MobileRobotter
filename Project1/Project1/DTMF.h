#pragma once
#include <string>
#include "SFMLtone.h"
using namespace std;
class DTMF
{
public:
	DTMF();
	DTMF(int, int);
	DTMF(char dtmfChar);
	string checkDTMF();
	SFMLtone getTone();
	void setFrequenciesFromChar(char Char);
	int getLow();
	int getHigh();
	~DTMF();
private:
	int low_frequency;
	int high_frequency;
	SFMLtone tone;
};

