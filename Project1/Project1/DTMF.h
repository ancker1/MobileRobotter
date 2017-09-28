#pragma once
#include <string>
using namespace std;
class DTMF
{
public:
	DTMF(int ,int);
	DTMF(char dtmfChar);
	string checkDTMF();
	//playdtmf
	int getLow();
	int getHigh();
	~DTMF();
private:
	int low_frequency;
	int high_frequency;
};

