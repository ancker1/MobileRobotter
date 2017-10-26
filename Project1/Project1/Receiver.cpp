#include "Receiver.h"



Receiver::Receiver(string cw, string c)
{
	codeword = cw;
	crc = c;
}

string Receiver::getCodeword()
{
	return codeword;
}

string Receiver::getCrc()
{
	return crc;
}

string Receiver::getSyndrome()
{
	// same princip as sender
	for (int i = 0; i < (codeword.length() - crc.length()); )
	{
		for (int j = 0; j < crc.length(); j++)
		{
			codeword[i + j] = codeword[i + j] == crc[j] ? '0' : '1';
		}
		while ((i < codeword.length()) && (codeword[i] != '1'))
		{
			i++;
		}
	}

	return (codeword.substr(codeword.length() - crc.length()));
}

string Receiver::checkForError()
{
	// convert to int
	string str = getSyndrome();
	int myInt = stoi(str);

	// ask if one
	if (myInt == 0)
	{
		return "DON'T EVEN TRIP DAWG, WUBBA LUBBA DUB DUB!";
	}
	else
	{
		return "And that's why I always say: shum-shum-schlippety-drop!";
	}
}

Receiver::~Receiver()
{
}
