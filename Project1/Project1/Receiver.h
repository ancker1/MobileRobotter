#pragma once
#include <iostream>
#include <string>

using namespace std;

class Receiver
{
public:
	Receiver(string cw, string c);
	string getCodeword();
	string getCrc();
	string getSyndrome();
	string checkForError();
	~Receiver();
protected:
	string codeword;
	string crc;
};

