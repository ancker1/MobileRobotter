#include "Receiver.h"



Receiver::Receiver(string d)
{
	frame = d;

	konverterStringTilBitString();
}

void Receiver::konverterStringTilBitString()
{
	char charData;
	string dataTilString;

	for (int i = 0; i < frame.size(); i++)//kører alle pladserne af string data indtastet
	{
		dataTilString = bitset<8>((int)frame[i]).to_string();//konvertere helt om til 8 bits til en string
		heleDataTilString += dataTilString;//ligger det konverterede til heleDataTilString
	}
}

string Receiver::getSyndrome()
{
	// dataword + remainder
	string codeword = "";

	for (int i = 16; i < heleDataTilString.length() - 8; i++)//smider flag, header og flag væk
	{
		codeword += heleDataTilString[i];
	}


	bool cont = false;

	// same princip as sender
	for (int i = 0; i < codeword.length(); i++) //kører codeword længde igennem og lægger først i++ til i while
	{
		if (10 < codeword.length() - i || stoi(crc, nullptr, 2) <= stoi(codeword, nullptr, 2))
		{
			if (codeword[i] != '0')
			{
				for (int j = 0; j < crc.length(); j++) //kører hele crc længde igennem på codeword. j resetes for hver LOOP ovenover. 
				{
					codeword[i + j] = (codeword[i + j] == crc[j] ? '0' : '1'); //hvis codeword plads er lig med crc plads så returner 0 eller 1 dvs en XOR operation og læg ind på plads.
				}
		
			}
		}
		else break;
	}

	return (codeword.substr(codeword.length() - crc.length()));

}

bool Receiver::hasErrorCRC()
{
	// convert to int
	string str = getSyndrome();
	int myInt = stoi(str);

	// ask if one
	if (myInt == 0)
	{
		return false; // No error
	}
	else
	{
		return true; // Has error
	}
}

int Receiver::acknowledgment()
{
	if (!hasErrorCRC())//hvis der er ingen fejl
	{

		if (heleDataTilString[8] == '1')// hvis det modtaget framenummer er 1 så send ACK0
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
	
	if (hasErrorCRC())//hvis der er fejl i crc
	{
		cout << "Fejl" << endl;
		return 0;
	}
	
}

void Receiver::udpakFrame()
{
	if (!hasErrorCRC())
	{
		cout << "CRC check is OKAY!" << endl;
		for (int i = 16; i < heleDataTilString.length() - 16; i++)//smider flag, header, trailer og flag væk
		{
			messageAsBits += heleDataTilString[i];
		}
	}
	else { cout << "Error in CRC check!" << endl; }
}

void Receiver::decodeMessage()
{
	string currentChar = "";
	for (int i = 0; i < messageAsBits.length(); i += 8)
	{
		currentChar = "";
		for (int j = 0; j < 8; j++)
		{
			currentChar += messageAsBits[i + j];
		}
		message += (char)stoi(currentChar, nullptr, 2);
	}
}

string Receiver::getMessage()
{
	return message;
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

