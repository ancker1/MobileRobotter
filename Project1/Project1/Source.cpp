#include "BehandlData.h"
#include "AudioRecord.h"
#include "Besked.h"
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
	return 0;
}