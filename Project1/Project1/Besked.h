#pragma once
#include <string>
#include "DTMF.h"
#include "SFMLarray.h"
#include "Sender.h"
#include "Receiver.h"
#include "DTMF.h"
#include "BehandlData.h"
#include "AudioRecord.h"
#include <iostream>
#include "LiveRecorder.h"
#include <thread>

using namespace std;
class Besked
{
public:
	Besked();
	Besked(string);
	void setTekst();

	void encapsulateMSG();

	void createSFMLarray(char input, SFMLarray& arraySFML);

	void createDTMFS();
	SFMLarray getDTMFs();
	char checkDTMF(int);

	char frequenciesToChar(int,int);

	void modtagHandshake();
	void sendHandshake();
	void sendFrame();
	void modtagFrame();
	void sendACK();

	void sendFrameACK(Receiver receiver, bool shouldNAK);
	bool modtagFrameACK();

	void modtagBesked();
	void sendBesked();

	void idleState();

	~Besked();

private:
	int RECORD_LENGTH = 0;
	int AMOUNT_TONE = 0;
	string message;
	string lastMSG;
	vector<int> encapsulatedMSG;
	DTMF currentHighDTMF;
	DTMF currentLowDTMF;
	SFMLarray allDTMFs;
};

