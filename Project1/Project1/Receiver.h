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
	string checkForError();
	~Receiver();
protected:
	string message;
	string data;
	char charData;
	string dataTilString;
};

