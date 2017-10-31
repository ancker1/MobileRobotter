#pragma once
#include "Sender.h"
#include <iostream>
#include <string>
#include <array>

using namespace std;

class Frame
{
public:
	Frame();
	Frame(string d);
	int getCount();
	int makeHeader();
	int getData();
	int getTrailer();
	void makeFrame();
	~Frame();
protected:
	string data;
	int count;
	int flag;
	int header;
};

