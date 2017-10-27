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
	for (size_t i = 0; i < (codeword.length()); ) //k�rer codeword l�ngde igennem og l�gger f�rst i++ til i while
	{
		for (size_t j = 0; j < crc.length(); j++) //k�rer hele crc l�ngde igennem p� codeword. j resetes for hver LOOP ovenover. 
		{
			codeword[i + j] = codeword[i + j] == crc[j] ? '0' : '1'; //hvis codeword plads er lig med crc plads s� returner 0 eller 1 dvs en XOR operation og l�g ind p� plads.
		}
		while ((i < codeword.length()) && (codeword[i] == '0')) //rykker hen til n�ste gang '1' optr�der i codeword.
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
