#include "Receiver.h"



Receiver::Receiver()
{
}

Receiver::Receiver(string msg)
{
	frame = msg;
	konverterStringTilBitString();
}

void Receiver::setMessage(string msg)
{
	message.clear();
	messageAsBits.clear();
	heleDataTilString.clear();

	frame = msg;
	konverterStringTilBitString();
}

bool Receiver::isLengthOK(int handshakeLength)
{
	cout << "FIRST: "<< int(frame[1]) * 2 << endl;
	cout << "SECOND: " << (int(frame[1])-128) *2<< endl;
	if (((int(frame[1]) - 128) * 2 == handshakeLength) || (int(frame[1]) * 2 == handshakeLength))
		return true;

	return false;

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

char Receiver::nextACK()
{
	ifstream readACK("ACKnr.txt");
	int ACKnr = readACK.get();
	ACKnr = ACKnr - '0';
	readACK.close();
	cout << "ACKnr: " << ACKnr << endl;
	if (!hasErrorCRC())
	{
		if ((int(heleDataTilString[8]) - '0') == ACKnr && ACKnr == 1)
		{
			ack = '\X06'; // ACK for modtaget frame nr. 1
			ACKnr = 0;
		}
		else if ((int(heleDataTilString[8]) - '0') == ACKnr && ACKnr == 0)
		{
			ack = '\X07'; // ACK for modtaget frame nr. 0
			ACKnr = 1;
		}
		else
		{
			ack = '\X15'; // Hex for NAK
			cout << "Dubletter" << endl;
		}
	}

	if (ack != '\X15') 
	{
		cout << "ACKnr: " << ACKnr << endl;
		ofstream writeACK("ACKnr.txt");
		writeACK << ACKnr;
		writeACK.close();
	}

	/*if (!hasErrorCRC())// hvis der er ingen fejl
	{
		if (heleDataTilString[8] == '1')// hvis det modtaget framenummer er 1, så send ACK0.
		{
			ack = '\X06'; 
			ackModtaget++;
		}
		if (heleDataTilString[8] == '0') // hvis det modtager framenumemr er 0, så send om ACK1.
		{
			ack = '\X07'; 
			ackModtaget--;
		}
	}*/

	return ack;
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
		return frame[0];//retunere længden af framen for herefter at oprette optagelse længden af den frame som snart bliver modtaget
	}
	return 0;
}

Receiver::~Receiver()
{
}

