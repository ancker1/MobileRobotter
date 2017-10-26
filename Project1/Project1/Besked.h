#pragma once
#include <string>
#include "DTMF.h"
using namespace std;
class Besked
{
public:
	Besked(string);
	char nextChar();
	void createDTMFS(char);
	char checkDTMF(int);
	void playMessage();
	//isMoreChars - skal tjekke om der er flere chars i stringen
	~Besked();

private:
	string message;
	int index;
	DTMF currentHighDTMF;
	DTMF currentLowDTMF;
};

