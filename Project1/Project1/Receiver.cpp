#include "Receiver.h"



Receiver::Receiver(string d)
{
	frame = d;
}

string Receiver::konverterStringTilBitString()
{
	string heleDataTilString;
	int indeks = 0;//pegepind til bostav indeks
	for (int i = 0; i < frame.size(); i++)//k�rer alle pladserne af string data indtastet
	{
		charData = frame[indeks];//ligger tegn p� plads indeks over i charData
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
	// get codeword
	string encoded;
	for (int i = 16; i < konverterStringTilBitString().length() - 8; i++)//smider flag, header og flag v�k
	{
		encoded += konverterStringTilBitString()[i];
	}

	// same princip as sender
	for (int i = 0; i < encoded.length(); ) //k�rer codeword l�ngde igennem og l�gger f�rst i++ til i while
	{
		for (int j = 0; j < getCrc().length(); j++) //k�rer hele crc l�ngde igennem p� codeword. j resetes for hver LOOP ovenover. 
		{
			encoded[i + j] = encoded[i + j] == getCrc()[j] ? '0' : '1'; //hvis codeword plads er lig med crc plads s� returner 0 eller 1 dvs en XOR operation og l�g ind p� plads.
		}
		while ((i < encoded.length()) && (encoded[i] == '0')) //rykker hen til n�ste gang '1' optr�der i codeword.
		{
			i++;
		}
	}

	return (encoded.substr(encoded.length() - getCrc().length()));
}

bool Receiver::checkForErrorCRC()
{
	// convert to int
	string str = getSyndrome();
	int myInt = stoi(str);

	// ask if one
	if (myInt == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Receiver::acknowledgment()
{
	if (checkForErrorCRC())//hvis der er ingen fejl
	{

		if (konverterStringTilBitString()[8] == '1')// hvis det modtaget framenummer er 1 s� send ACK0
		{
			ackReakkefoelge++;
			return 0b00010101;
		}
		if (konverterStringTilBitString()[8] == '0')
		{
			ackReakkefoelge--;
			return 0b00000110;//hvis det modtaget framenummer er 0 s� send ACK1
		}
	}

	if (ackReakkefoelge >= 2 || ackReakkefoelge <= -1)//hvis der er modtaget dubletter af framen
	{
		cout << "dubletter" << endl;
		return 0;
	}
	
	if (!checkForErrorCRC())//hvis der er fejl i crc
	{
		cout << "Fejl" << endl;
		return 0;
	}
	
}

string Receiver::udpakFrame()
{
	for (int i = 16; i < konverterStringTilBitString().length() - 16; i++)//smider flag, header, trailer og flag v�k
	{
		message += konverterStringTilBitString()[i];
	}
	return message;
}

Receiver::~Receiver()
{
}
