#include "Receiver.h"



Receiver::Receiver(string d)
{
	frame = d;
}

void Receiver::konverterStringTilBitString()
{
	char charData;
	string dataTilString;

	for (int i = 0; i < frame.size(); i++)//k�rer alle pladserne af string data indtastet
	{
		dataTilString = bitset<8>((int)frame[i]).to_string();//konvertere helt om til 8 bits til en string
		heleDataTilString += dataTilString;//ligger det konverterede til heleDataTilString
	}
}

string Receiver::getSyndrome()
{
	// get codeword
	string encoded;

	for (int i = 16; i < heleDataTilString.length() - 8; i++)//smider flag, header og flag v�k
	{
		encoded += heleDataTilString[i];
	}

	

	// same princip as sender
	for (int i = 0; i < encoded.length(); ) //k�rer codeword l�ngde igennem og l�gger f�rst i++ til i while
	{
		for (int j = 0; j < crc.length(); j++) //k�rer hele crc l�ngde igennem p� codeword. j resetes for hver LOOP ovenover. 
		{
			encoded[i + j] = (encoded[i + j] == crc[j] ? '0' : '1'); //hvis codeword plads er lig med crc plads s� returner 0 eller 1 dvs en XOR operation og l�g ind p� plads.
		}
		while ((i < encoded.length()) && (encoded[i] == '0')) //rykker hen til n�ste gang '1' optr�der i codeword.
		{
			i++;
		}
	}

	return (encoded.substr(encoded.length() - crc.length()));

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

		if (heleDataTilString[8] == '1')// hvis det modtaget framenummer er 1 s� send ACK0
		{
			ackReakkefoelge++;
			return '\X15'; // 'NACK'
		}
		if (heleDataTilString[8] == '0')
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
		for (int i = 16; i < heleDataTilString.length() - 16; i++)//smider flag, header, trailer og flag v�k
		{
			message += heleDataTilString[i];
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
		return frame[0];//retunere l�ngden af framen for herefter at oprette optagelse l�ngden af den frame som snart bliver modtaget
	}
	return 0;
}

Receiver::~Receiver()
{
}

