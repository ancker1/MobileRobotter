#include "BehandlData.h"
#include "AudioRecord.h"
#include "Sender.h"
#include "DataTilStringBinary.h"
#include "Frame.h"
#include <iostream>

//for at afspille besked
//(1) besked test("this is a test");
//(2) test.playMessage();

//for at genkende DTMF tone
//(1) AudioRecord test(1);
//(2) test.record();
//(3) BehandlData testData(test.getAudioVector());
//(4) testData.recognizeDTMF();

int main()
{
	/*
	//Besked test("Wubba dub a dub dub");
	//test.playMessage();
	AudioRecord test(1);

	cout << "Start." << endl;

		test.record();
		BehandlData testData(test.getAudioVector());
		testData.recognizeDTMF();

	cout << "Stop." << endl;
	*/

	// TEST frame
	Sender test(DataTilStringBinary("j"), "100000111");
	cout << test.getMessage() << endl;
	cout << test.makeRemainder() << endl;
	cout << test.makeTrailer() << endl;
	cout << test.makeCodeword() << endl;

	return 0;
}