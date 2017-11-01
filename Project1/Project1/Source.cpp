#include "BehandlData.h"
#include "AudioRecord.h"
#include "Besked.h"
#include <iostream>
#include "Sender.h"
#include "Receiver.h"

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
	//Besked test("Wubba lubba dub dub");
	//test.playMessage();
	Besked testBesked("");
	string x;

	cin >> x;
		int firstSum = testBesked.modtagFrequencySum();
		cout << "Stop." << endl;
	cin >> x;
		int secondSum = testBesked.modtagFrequencySum();
		cout << "Stop." << endl;

		cout << "____________________________" << endl;
		cout << "Modtaget besked: " << testBesked.frequenciesToChar(firstSum, secondSum) << endl;
		cout << "____________________________" << endl;
		*/

	Sender test2("Hej med dig");
	cout << test2.konverterStringTilBitString() << endl;
	cout << test2.makeRemainder() << endl;
	cout << test2.makeCodeword() << endl;
	test2.makeFrame();
	cout << endl;

	Receiver test3("Hej med digP");
	cout << test3.konverterStringTilBitString() << endl;
	cout << test3.getSyndrome() << endl;


	return 0;
}