#include "Receiver.h"



Receiver::Receiver(string d)
{
	data = d;
}

string Receiver::konverterStringTilBitString()
{
	string heleDataTilString;
	int indeks = 0;//pegepind til bostav indeks
	for (int i = 0; i < data.size(); i++)//k�rer alle pladserne af string data indtastet
	{
		charData = data[indeks];//ligger tegn p� plads indeks over i charData
		int dataTilInt = 0;
		dataTilInt = (int)charData;//tager ascii v�rdien af char og ligger de ind i dataTilInt
		dataTilString = bitset<8>(dataTilInt).to_string();//konvertere helt om til 8 bits til en string
		heleDataTilString += dataTilString;//ligger det konverterede til heleDataTilString
		indeks++;//t�ller indeks en op
	}
	return heleDataTilString;
}

string Receiver::getCrc()
{
	return "100000111"; // CRC - 8
}

string Receiver::getSyndrome()
{
	// get data
	string encoded = konverterStringTilBitString();
	string crc = getCrc();
	// same princip as sender
	for (int i = 0; i < (encoded.length()); ) //k�rer codeword l�ngde igennem og l�gger f�rst i++ til i while
	{
		for (int j = 0; j < crc.length(); j++) //k�rer hele crc l�ngde igennem p� codeword. j resetes for hver LOOP ovenover. 
		{
			encoded[i + j] = encoded[i + j] == crc[j] ? '0' : '1'; //hvis codeword plads er lig med crc plads s� returner 0 eller 1 dvs en XOR operation og l�g ind p� plads.
		}
		while ((i < encoded.length()) && (encoded[i] == '0')) //rykker hen til n�ste gang '1' optr�der i codeword.
		{
			i++;
		}
	}

	return (encoded.substr(encoded.length() - crc.length()));
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
