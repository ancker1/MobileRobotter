#include "BehandlData.h"
#include "Besked.h"
#include "DTMF.h"
#include "Sender.h"
#include "Receiver.h"
#include "AudioRecord.h"
#include <iostream>

//for at afspille besked
//(1) besked test("this is a test");
//(2) test.playMessage();

int main()
{

	//Besked test("Wubba dub a dub dub");
	//test.playMessage();
	AudioRecord test(1);

	cout << "Start." << endl;

		test.record();
		BehandlData testData(test.getAudioVector());
		testData.recognizeDTMF();

	cout << "Stop." << endl;

	return 0;
}