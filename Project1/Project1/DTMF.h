#pragma once
#include <string>
#include "SFMLtone.h"
using namespace std;
class DTMF
{
public:
	DTMF(int, int);
	DTMF(char dtmfChar);
	string checkDTMF();
	SFMLtone getTone();
	int getLow();
	int getHigh();
	~DTMF();
private:
	int low_frequency;
	int high_frequency;
	SFMLtone tone;
};

