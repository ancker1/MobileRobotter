#include "Receiver.h"



Receiver::Receiver(string d)
{
	data = d;
}

string Receiver::konverterStringTilBitString()
{
	string heleDataTilString;
	int indeks = 0;//pegepind til bostav indeks
	for (int i = 0; i < data.size(); i++)//kører alle pladserne af string data indtastet
	{
		charData = data[indeks];//ligger tegn på plads indeks over i charData
		int dataTilInt = 0;
		dataTilInt = (int)charData;//tager ascii værdien af char og ligger de ind i dataTilInt
		dataTilString = bitset<8>(dataTilInt).to_string();//konvertere helt om til 8 bits til en string
		heleDataTilString += dataTilString;//ligger det konverterede til heleDataTilString
		indeks++;//tæller indeks en op
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
	for (int i = 0; i < (encoded.length()); ) //kører codeword længde igennem og lægger først i++ til i while
	{
		for (int j = 0; j < crc.length(); j++) //kører hele crc længde igennem på codeword. j resetes for hver LOOP ovenover. 
		{
			encoded[i + j] = encoded[i + j] == crc[j] ? '0' : '1'; //hvis codeword plads er lig med crc plads så returner 0 eller 1 dvs en XOR operation og læg ind på plads.
		}
		while ((i < encoded.length()) && (encoded[i] == '0')) //rykker hen til næste gang '1' optræder i codeword.
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
