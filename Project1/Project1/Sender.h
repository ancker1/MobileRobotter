#pragma once
#include <iostream>
#include <string>

using namespace std;

class Sender
{
public:
	Sender();
	Sender(string, string);
	string getMessage();
	string getCrc();
	string makeRemainder();
	string makeCodeword();
	int makeTrailer();
	~Sender();
protected:
	string msg;
	string crc;
	string encoded;
	int myInt;
};

