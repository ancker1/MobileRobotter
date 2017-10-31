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
	Frame(int d, Sender(m));
	int getCount();
	int makeHeader();
	int getData();
	int getTrailer();
	void makeFrame();
	~Frame();
protected:
	int data;
	int count;
	int flag;
	int header;
	Sender msg;
};

