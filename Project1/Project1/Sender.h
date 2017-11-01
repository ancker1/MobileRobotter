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
	vector <int> makeFrame();
	int getHeader();
	~Sender();
protected:
	string data;
	char charData;
	string dataTilString;
	int flag;
	vector <int> frame;
	int header;
};

