#include "Besked.h"
#include "DTMF.h"
#include "BehandlData.h"
#include "AudioRecord.h"
#include "Sender.h"
#include "Receiver.h"
#include <iostream>
using namespace std;

Besked::Besked()
{

}

Besked::Besked(string tekst)
{
	index = 0;
	message = tekst;
}

void Besked::encapsulateMSG()
{
	Sender createOBJ(message);
	encapsulatedMSG = createOBJ.makeFrame();
}


void Besked::createDTMFS()
{
	encapsulateMSG();
	for (int i = 0; i < encapsulatedMSG.size(); i++) {
		int test = encapsulatedMSG[i];
		int lower_nibble = test & 0b00001111;
		int higher_nibble = test & 0b11110000;
		higher_nibble = higher_nibble >> 4;

		currentHighDTMF.setFrequenciesFromChar(checkDTMF(higher_nibble));
		currentLowDTMF.setFrequenciesFromChar(checkDTMF(lower_nibble));

		allDTMFs.addTone(currentHighDTMF.getHigh(), currentHighDTMF.getLow());
		allDTMFs.addTone(currentLowDTMF.getHigh(), currentLowDTMF.getLow());

		cout << "Character is: " << (char)encapsulatedMSG[i] << endl;
		cout << i * 2		<< ":	" << currentHighDTMF.getLow() << ", " << currentHighDTMF.getHigh() << endl;
		cout << i * 2 + 1	<< ":	" << currentLowDTMF.getLow() << ", " << currentLowDTMF.getHigh() <<  endl;
	}

	allDTMFs.readySound();
}

SFMLarray Besked::getDTMFs() {
	return allDTMFs;
}

char Besked::checkDTMF(int intIn)
{
	switch (intIn)
	{
	case 0b0001:
		return '1';
	case 0b0010:
		return '2';
	case 0b0011:
		return '3';
	case 0b0100:
		return '4';
	case 0b0101:
		return '5';
	case 0b0110:
		return '6';
	case 0b0111:
		return '7';
	case 0b1000:
		return '8';
	case 0b1001:
		return '9';
	case 0b1010:
		return '0';
	case 0b1011:
		return '*';
	case 0b1100:
		return '#';
	case 0b1101:
		return 'A';
	case 0b1110:
		return 'B';
	case 0b1111:
		return 'C';
	case 0b0000:
		return 'D';
	default:
		break;
	}
}

char Besked::frequenciesToChar(int first_FrequencySum, int second_FrequencySum)
{
	int highNibble;
	int lowNibble;
	int msgByte;
	switch (first_FrequencySum)
	{
	case 1906:
		highNibble = 0b0001;
		break;
	case 2033:
		highNibble = 0b0010;
		break;
	case 2174:
		highNibble = 0b0011;
		break;
	case 1979:
		highNibble = 0b0100;
		break;
	case 2106:
		highNibble = 0b0101;
		break;
	case 2247:
		highNibble = 0b0110;
		break;
	case 2061:
		highNibble = 0b0111;
		break;
	case 2188:
		highNibble = 0b1000;
		break;
	case 2329:
		highNibble = 0b1001;
		break;
	case 2277:
		highNibble = 0b1010;
		break;
	case 2150:
		highNibble = 0b1011;
		break;
	case 2418:
		highNibble = 0b1100;
		break;
	case 2330:
		highNibble = 0b1101;
		break;
	case 2403:
		highNibble = 0b1110;
		break;
	case 2485:
		highNibble = 0b1111;
		break;
	case 2574:
		highNibble = 0b0000;
		break;
	default:
		highNibble = 0b0000; // TEST
		break;
	}
	switch (second_FrequencySum)
	{
	case 1906:
		lowNibble = 0b0001;
		break;
	case 2033:
		lowNibble = 0b0010;
		break;
	case 2174:
		lowNibble = 0b0011;
		break;
	case 1979:
		lowNibble = 0b0100;
		break;
	case 2106:
		lowNibble = 0b0101;
		break;
	case 2247:
		lowNibble = 0b0110;
		break;
	case 2061:
		lowNibble = 0b0111;
		break;
	case 2188:
		lowNibble = 0b1000;
		break;
	case 2329:
		lowNibble = 0b1001;
		break;
	case 2277:
		lowNibble = 0b1010;
		break;
	case 2150:
		lowNibble = 0b1011;
		break;
	case 2418:
		lowNibble = 0b1100;
		break;
	case 2330:
		lowNibble = 0b1101;
		break;
	case 2403:
		lowNibble = 0b1110;
		break;
	case 2485:
		lowNibble = 0b1111;
		break;
	case 2574:
		lowNibble = 0b0000;
		break;
	default:
		lowNibble = 0b0000; // TEST
		break;
	}
	highNibble = highNibble << 4;
	msgByte = highNibble + lowNibble;
	if ((msgByte >= 0 && msgByte <= 255))
	{
		return (char)msgByte;
	}
	return ' ';
}

int Besked::modtagFrequencySum()
{
	AudioRecord test(1);
	cout << "Start." << endl;
	test.record();
	cout << test.getAudioVector().size() << endl;
	BehandlData testData(test.getAudioVector());
	//return testData.recognizeDTMF();
	return 0;
}

void Besked::modtagHandshake()
{

	//AMOUNT_TONE = ?
	//RECORD_LENGTH = ?
}

void Besked::modtagFrame()
{
	AudioRecord record;
	record.setSecondsToRecord(7); //RECORD_LENGTH
	cout << "Start" << endl;
	record.record();
	BehandlData objectTest(record.getAudioVector());
	cout << "Stop" << endl;
	objectTest.slideTWO();
	for (int i = 0; i < 52; i++) //AMOUNT_TONE
	{
		objectTest.nextTone(50);
	}
	vector<float> freqSumVec = objectTest.getfrequencySumVector();
	string text;
	for (int i = 0; i < freqSumVec.size()-1; i++) //MAX er: frequencySumVector.size() - 1
	{
		text += frequenciesToChar(freqSumVec[i++], freqSumVec[i]);
	}
	Receiver recieveOBJ(text);
	text = recieveOBJ.udpakFrame();
	cout << text << endl;
}

Besked::~Besked()
{
}
