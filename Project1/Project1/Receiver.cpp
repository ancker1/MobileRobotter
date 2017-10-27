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
	for (size_t i = 0; i < (codeword.length()); ) //kører codeword længde igennem og lægger først i++ til i while
	{
		for (size_t j = 0; j < crc.length(); j++) //kører hele crc længde igennem på codeword. j resetes for hver LOOP ovenover. 
		{
			codeword[i + j] = codeword[i + j] == crc[j] ? '0' : '1'; //hvis codeword plads er lig med crc plads så returner 0 eller 1 dvs en XOR operation og læg ind på plads.
		}
		while ((i < codeword.length()) && (codeword[i] == '0')) //rykker hen til næste gang '1' optræder i codeword.
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
