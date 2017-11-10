#pragma once
#include <iostream>
#include <string>
#include <bitset>

using namespace std;

class Receiver
{
public:
	Receiver(string msg);
	string konverterStringTilBitString();
	string getCrc();
	string getSyndrome();
	bool checkForErrorCRC();
	int acknowledgment();
	string udpakFrame();
	~Receiver();
protected:
	int ackReakkefoelge = 0;
	string message;
	string frame;
	char charData;
	string dataTilString;
};

