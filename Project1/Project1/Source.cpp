#include "BehandlData.h"
#include "AudioRecord.h"
#include "Besked.h"
#include <iostream>
#include "Sender.h"
#include "Receiver.h"

//for at afspille besked
//(1) Besked test("this is a test");
//(2) test.createDTMFS();
//(3) test.getDTMFs().play();

//for at genkende DTMF tone
//(1) AudioRecord test(1);
//(2) test.record();
//(3) BehandlData testData(test.getAudioVector());
//(4) testData.recognizeDTMF();

//for at modtage sætning
//(1) AudioRecord test(7);
//(2) test.record();
//(3) BehandlData objectTest(test.getAudioVector());
//(4) objectTest.slideTWO();		//ELLER objectTest.slidingWindow();
//(5) for (int i = 0; i < 100; i++) { objectTest.nextTone(50); }
//(6) objectTest.printText();

int main()
{
	 Besked test("this is a test");
	 test.createDTMFS();
	 test.getDTMFs().play();


	AudioRecord record;
	record.setSecondsToRecord(12);
	string x;
	cin >> x;
	cout << "Start" << endl;
	record.record();
	BehandlData objectTest(record.getAudioVector());
	cout << "Stop" << endl;

	//objectTest.slidingWindow();
	objectTest.slideTWO();
	
	for (int i = 0; i < 100; i++)
	{
		objectTest.nextTone(50);
	}
	objectTest.printText();
	


	return 0;
}