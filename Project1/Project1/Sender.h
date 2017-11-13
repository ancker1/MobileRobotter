#pragma once
#include <iostream>
#include <string>
#include <bitset>
#include <vector>

using namespace std;

class Sender
{
public:
	Sender();
	Sender(string d);

	// Konverter til bit streng
	string konverterStringTilBitString();

	// CRC
	string getCrc();
	string makeRemainder();
	string makeCodeword();
	int getTrailer();

	// Frame
	int makeHeader();
	int getHeader();
	vector <int> makeFrame();

	// Handshake
	int makeHandshake();
	int makeHandshakeLength();

	~Sender();
protected:
	string data;

	// Acknowledgment
	int ackTal;

	// Konverter til bit string
	char charData;
	string dataTilString;

	// Frame
	int flag;
	vector <int> frame;
	int header;
};

