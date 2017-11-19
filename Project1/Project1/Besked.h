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
	void encapsulateMSG();

	void createSFMLarray(char input, SFMLarray& arraySFML);

	void createDTMFS();
	SFMLarray getDTMFs();
	char checkDTMF(int);

	char frequenciesToChar(int,int);
	int modtagFrequencySum();

	void modtagHandshake();
	void sendHandshake();
	void sendFrame();
	void modtagFrame();

	void modtagBesked();
	void sendBesked();

	~Besked();

private:
	int RECORD_LENGTH = 0;
	int AMOUNT_TONE = 0;
	string message;
	vector<int> encapsulatedMSG;
	int index;
	DTMF currentHighDTMF;
	DTMF currentLowDTMF;
	SFMLarray allDTMFs;
};

