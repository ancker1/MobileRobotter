#include "Receiver.h"



Receiver::Receiver(string d)
{
	frame = d;
}

string Receiver::konverterStringTilBitString()
{
	string heleDataTilString;
	int indeks = 0;//pegepind til bostav indeks
	for (int i = 0; i < frame.size(); i++)//kører alle pladserne af string data indtastet
	{
		charData = frame[indeks];//ligger tegn på plads indeks over i charData
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
	// get codeword
	string encoded;
	for (int i = 16; i < konverterStringTilBitString().length() - 8; i++)//smider flag, header og flag væk
	{
		encoded += konverterStringTilBitString()[i];
	}

	// same princip as sender
	for (int i = 0; i < encoded.length(); ) //kører codeword længde igennem og lægger først i++ til i while
	{
		for (int j = 0; j < getCrc().length(); j++) //kører hele crc længde igennem på codeword. j resetes for hver LOOP ovenover. 
		{
			encoded[i + j] = encoded[i + j] == getCrc()[j] ? '0' : '1'; //hvis codeword plads er lig med crc plads så returner 0 eller 1 dvs en XOR operation og læg ind på plads.
		}
		while ((i < encoded.length()) && (encoded[i] == '0')) //rykker hen til næste gang '1' optræder i codeword.
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
		return false;
	}
	else
	{
		return true;
	}
}

int Receiver::acknowledgment()
{
	if (!checkForErrorCRC())//hvis der er ingen fejl
	{

		if (konverterStringTilBitString()[8] == '1')// hvis det modtaget framenummer er 1 så send ACK0
		{
			ackReakkefoelge++;
			return '\X15'; // 'NACK'
		}
		if (konverterStringTilBitString()[8] == '0')
		{
			ackReakkefoelge--;
			return '\X06'; // 'ACK'
		}
	}

	if (ackReakkefoelge >= 2 || ackReakkefoelge <= -1)//hvis der er modtaget dubletter af framen
	{
		cout << "dubletter" << endl;
		return 0;
	}
	
	if (checkForErrorCRC())//hvis der er fejl i crc
	{
		cout << "Fejl" << endl;
		return 0;
	}
	
}

string Receiver::udpakFrame()
{
	if (!checkForErrorCRC())
	{
		for (int i = 16; i < konverterStringTilBitString().length() - 16; i++)//smider flag, header, trailer og flag væk
		{
			message += konverterStringTilBitString()[i];
		}
		return message;
	}
	return "";
}

bool Receiver::checkHandshake()
{
	if (frame[0] == '\X16') // '\X16' = 0b00010110 = 'SYN'
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Receiver::checkHandshakeLength()
{
	if (checkHandshake())
	{
		return frame[0];//retunere længden af framen for herefter at oprette optagelse længden af den frame som snart bliver modtaget
	}
	return 0;
}

Receiver::~Receiver()
{
}

