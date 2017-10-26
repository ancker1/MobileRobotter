#include "Besked.h"
#include "DTMF.h"
#include <iostream>
using namespace std;


Besked::Besked(string tekst)
{
	index = 0;
	message = tekst;
}

char Besked::nextChar()
{
	if (message.length() == index)
		index = 0;
	return message[index++];
}

void Besked::createDTMFS(char charIn)
{
	int test = charIn;
	int lower_nibble = test & 0b00001111;
	int higher_nibble = test & 0b11110000;
	higher_nibble = higher_nibble >> 4;

	//DTMF higher_dtmf(checkDTMF(higher_nibble));
	//DTMF lower_dtmf(checkDTMF(lower_nibble));

	currentHighDTMF.setFrequenciesFromChar(checkDTMF(higher_nibble));
	currentLowDTMF.setFrequenciesFromChar(checkDTMF(lower_nibble));

	cout << "Character is: " << charIn << endl;
	cout << "----------High DTMF---------|" << endl;
	cout << "High freq.: " << currentHighDTMF.getHigh()  << endl << "Low Freq.: " << currentHighDTMF.getLow() << endl;
	cout << "----------Low DTMF----------|" << endl;
	cout << "High freq.: " << currentLowDTMF.getHigh() << endl << "Low Freq.: " << currentLowDTMF.getLow() <<  endl;
}

void Besked::playMessage()
{
	for (int i = 0; i < message.length(); i++)
	{
		createDTMFS(nextChar());
		currentHighDTMF.getTone().play(1);
		currentLowDTMF.getTone().play(1);
	}
	
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


Besked::~Besked()
{
}
