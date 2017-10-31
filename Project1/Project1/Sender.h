#pragma once
#include "DataTilStringBinary.h"
#include <iostream>
#include <string>
#include <bitset>

using namespace std;

class Sender
{
public:
	Sender();
	Sender(DataTilStringBinary(message), string c);
	string getMessage();
	string getCrc();
	string makeRemainder();
	string makeCodeword();
	int makeTrailer();
	~Sender();
protected:
	DataTilStringBinary msg;
	string crc;
	string encoded;
};

