#include "BehandlData.h"
#include "AudioRecord.h"
#include "Besked.h"
#include <iostream>
#include "DataTilStringBinary.h"
#include "Sender.h"
#include "Frame.h"

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

	DataTilStringBinary test1("Hej med dig");
	cout << test1.konverterStringTilBitString() << endl;
	cout << endl;

	Sender test2(DataTilStringBinary("Hej med dig"), "100000111");
	cout << test2.makeRemainder() << endl;
	cout << test2.makeTrailer() << endl;
	cout << test2.makeCodeword() << endl; 
	cout << endl;

	Frame test3('j', Sender(DataTilStringBinary("Hej med dig"), "100000111"));
	cout << test3.getTrailer() << endl;
	test3.makeFrame();

	return 0;
}