#pragma once
#include <iostream>
#include <string>
#include <bitset>

using namespace std;

class Receiver
{
public:
	Receiver();
	Receiver(string msg);
	void setMessage(string msg);

	// Konverter til bit streng
	void konverterStringTilBitString();

	// CRC
	string getSyndrome();
	bool hasErrorCRC();

	// Acknowledgment
	int nextACK();

	// Frame
	void udpakFrame();
	void decodeMessage();
	string getMessage();

	// handshake
	bool checkForHandshake();
	int checkHandshakeLength();

	~Receiver();
protected:
	string frame;
	string crc = "100000111";

	// Acknowledgment
	int ackModtaget = 0; // optælling af ack
	int ack;

	// Frame
	string messageAsBits;
	string message;

	// Konverter til bit streng
	string heleDataTilString;

	//handshake
	int handshake = '\X16';
};

