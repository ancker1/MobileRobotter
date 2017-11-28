#pragma once
#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <fstream>

using namespace std;

class Sender
{
public:
	Sender();
	Sender(string d);
	void setMessage(string d);

	// Konverter til bit streng
	void konverterStringTilBitString();

	// CRC
	string makeRemainder();
	string makeCodeword();
	int getTrailer();

	// Frame
	int makeHeader();
	int getHeader();
	vector <int> makeFrame();

	// Handshake
	int makeHandshake();

	~Sender();
protected:
	string data;
	string crc = "100000111"; // CRC-8

	// Acknowledgment
	int ackTal = 0; // starter i nul

	// Konverter til bit string
	string heleDataTilString;

	// Frame
	int flag = 0b00000001;
	vector <int> frame;
	int header;
};

