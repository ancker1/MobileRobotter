#pragma once
#include <string>

using namespace std;
class DTMF
{
public:
	DTMF();
	DTMF(int, int);
	DTMF(char dtmfChar);
	void setFrequenciesFromChar(char Char);
	int getLow();
	int getHigh();
	~DTMF();
private:
	int low_frequency;
	int high_frequency;
};

