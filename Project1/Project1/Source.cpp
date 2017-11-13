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
	
	//Besked test("Wubba lubba dub dub");
	//test.playMessage();
	/*
	Besked testBesked("");
	string x;

		int firstSum = testBesked.modtagFrequencySum();
		int secondSum = testBesked.modtagFrequencySum();
		cout << "Modtaget besked: " << testBesked.frequenciesToChar(firstSum, secondSum) << endl;

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

	
	AudioRecord record;
	record.setSecondsToRecord(7);
	string x;
	cin >> x;
	cout << "Start" << endl;
	record.record();
	BehandlData objectTest(record.getAudioVector());
	cout << "Stop" << endl;
	//record.printToFile();

	objectTest.slidingWindow();
	for (int i = 0; i < 100; i++)
	{
		objectTest.nextTone(50);
	}
	objectTest.printText();
	//objectTest.printTo1File();


	return 0;
}