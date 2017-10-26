#pragma once
#include <iostream>
#include <string>

using namespace std;

class Sender
{
public:
	Sender(string, string);
	string getMessage();
	string getCrc();
	string makeCodeword();
	~Sender();
protected:
	string msg;
	string crc;
	string encoded;
};

