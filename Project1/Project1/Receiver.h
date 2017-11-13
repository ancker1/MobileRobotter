#pragma once
#include <iostream>
#include <string>
#include <bitset>

using namespace std;

class Receiver
{
public:
	Receiver(string msg);

	// Konverter til bit streng
	string konverterStringTilBitString();

	// CRC
	string getCrc();
	string getSyndrome();
	bool checkForErrorCRC();

	// Acknowledgment
	int acknowledgment();

	// Frame
	string udpakFrame();

	// handshake
	bool checkHandshake();
	int checkHandshakeLength();

	~Receiver();
protected:
	string frame;

	// Acknowledgment
	int ackReakkefoelge = 0;

	// Frame
	string message;

	// Konverter til bit streng
	char charData;
	string dataTilString;
};

