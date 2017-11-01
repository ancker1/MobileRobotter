#pragma once
#include <iostream>
#include <string>
#include <bitset>
#include <array>

using namespace std;

class Sender
{
public:
	Sender();
	Sender(string d);
	string konverterStringTilBitString();
	string getCrc();
	string makeRemainder();
	string makeCodeword();
	int getTrailer();
	void makeFrame();
	~Sender();
protected:
	string data;
	char charData;
	string dataTilString;
	int flag;
	int* frame;
};

