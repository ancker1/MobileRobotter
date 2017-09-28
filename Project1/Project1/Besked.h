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
	//playDTMFS her skal hele stringen loopes igennem, hvor der char's laves til DTMF objekter og herefter afspilles en efter en.
	~Besked();

private:
	string message;
	int index;
};

