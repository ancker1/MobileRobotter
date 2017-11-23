#include "Receiver.h"



Receiver::Receiver()
{
}

Receiver::Receiver(string msg)
{
	setMessage(msg);
}

void Receiver::setMessage(string msg)
{
	message.clear();
	messageAsBits.clear();
	heleDataTilString.clear();

	frame = msg;
	konverterStringTilBitString();
	//cout << frame << endl;
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
	// dataword + remainder
	string codeword = "";

	for (int i = 16; i < heleDataTilString.length() - 8; i++)//smider flag, header og flag v�k
	{
		codeword += heleDataTilString[i];
	}


	bool cont = false;

	// same princip as sender
	for (int i = 0; i < codeword.length(); i++) //k�rer codeword l�ngde igennem og l�gger f�rst i++ til i while
	{
		if (10 < codeword.length() - i || stoi(crc, nullptr, 2) <= stoi(codeword, nullptr, 2))
		{
			if (codeword[i] != '0')
			{
				for (int j = 0; j < crc.length(); j++) //k�rer hele crc l�ngde igennem p� codeword. j resetes for hver LOOP ovenover. 
				{
					codeword[i + j] = (codeword[i + j] == crc[j] ? '0' : '1'); //hvis codeword plads er lig med crc plads s� returner 0 eller 1 dvs en XOR operation og l�g ind p� plads.
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

int Receiver::nextACK()
{
	if (!hasErrorCRC())// hvis der er ingen fejl
	{
		if (heleDataTilString[8] == '1')// hvis det modtaget framenummer er 1, s� send ACK0.
		{
			ack = '\X06'; 
			ackModtaget++;
		}
		if (heleDataTilString[8] == '0') // hvis det modtager framenumemr er 0, s� send om ACK1.
		{
			ack = '\X07'; 
			ackModtaget--;
		}
	}
	if (ackModtaget >= 2 || ackModtaget <= -1) // hvis der er modtaget dubletter af framen
		cout << "dubletter" << endl;
	
	if (hasErrorCRC()) // hvis der er fejl i crc
		cout << "Fejl" << endl;
	return ack;
}

void Receiver::udpakFrame()
{
	if (!hasErrorCRC())
	{
		cout << "CRC check is OKAY!" << endl;
		for (int i = 16; i < heleDataTilString.length() - 16; i++)//smider flag, header, trailer og flag v�k
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

bool Receiver::checkForHandshake()
{
	if (frame[0] == handshake) // '\X16' = 0b00010110 = 'SYN'
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
	if (checkForHandshake())
	{
		return frame[0];//retunere l�ngden af framen for herefter at oprette optagelse l�ngden af den frame som snart bliver modtaget
	}
	return 0;
}

Receiver::~Receiver()
{
}

