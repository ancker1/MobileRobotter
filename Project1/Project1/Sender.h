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
	string konverterStringTilBitString();
	string getCrc();
	string makeRemainder();
	string makeCodeword();
	int getTrailer();
	int makeHeader();
	vector <int> makeFrame();
	int getHeader();
	~Sender();
protected:
	int ackTal = 0;
	string data;
	char charData;
	string dataTilString;
	int flag;
	vector <int> frame;
	int header;
	int ackNul = 0b00010101;
	int ackEt = 0b00000110;
};

