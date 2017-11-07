#pragma once
#include <string>
#include "DTMF.h"
#include "SFMLarray.h"

using namespace std;
class Besked
{
public:
	Besked();
	Besked(string);

	void createDTMFS();
	SFMLarray getDTMFs();
	char checkDTMF(int);

	char frequenciesToChar(int,int);
	int modtagFrequencySum();

	~Besked();

private:
	string message;
	int index;
	DTMF currentHighDTMF;
	DTMF currentLowDTMF;
	SFMLarray allDTMFs;
};

