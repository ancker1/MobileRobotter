#include "Receiver.h"



Receiver::Receiver()
{
}

Receiver::Receiver(string msg)
{
	frame = msg;
	cout << frame << endl;
	konverterStringTilBitString();
}

void Receiver::setMessage(string msg)
{
//	message.clear();
//	messageAsBits.clear();
//	heleDataTilString.clear();

	frame = msg;
	konverterStringTilBitString();
}

bool Receiver::isLengthOK(int handshakeLength)
{
	unsigned char unsignedFrame1 = frame[1];
	if (((int(unsignedFrame1) - 128) * 2 == handshakeLength) || (int(unsignedFrame1) * 2 == handshakeLength))
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
	string codeword = "";
	for (int i = 16; i < heleDataTilString.length() - 8; i++)//smider flag, header og flag væk
		codeword += heleDataTilString[i];

	for (int i = 0; i < codeword.length(); i++) //kører codeword længde igennem og lægger først i++ til i while
	{
		if (10 < codeword.length() - i || stoi(crc, nullptr, 2) <= stoi(codeword, nullptr, 2))
		{
			if (codeword[i] != '0')
			{
				for (int j = 0; j < crc.length(); j++) //kører hele crc længde igennem på codeword. j resetes for hver LOOP ovenover. 
					codeword[i + j] = (codeword[i + j] == crc[j] ? '0' : '1'); //hvis codeword plads er lig med crc plads så returner 0 eller 1 dvs en XOR operation og læg ind på plads.
			}
		}
		else break;
	}
	return (codeword.substr(codeword.length() - crc.length()));
}

bool Receiver::hasErrorCRC()
{
	if (stoi(getSyndrome()) == 0)
		return false; // No error
	else
		return true; // Has error
}

char Receiver::nextACK()
{
	ifstream readACK("ACKnr.txt");
	int ACKnr = readACK.get() - '0';
	readACK.close();
	//cout << "ACKnr: " << ACKnr << endl;
	if (!hasErrorCRC())
	{
		if ((int(heleDataTilString[8]) - '0') == ACKnr && ACKnr == 1)
		{
			ack = char(6); // ACK for modtaget frame nr. 1
			ACKnr = 0;
		}
		else if ((int(heleDataTilString[8]) - '0') == ACKnr && ACKnr == 0)
		{
			ack = char(7); // ACK for modtaget frame nr. 0
			ACKnr = 1;
		}
		else if ((int(heleDataTilString[8]) - '0') == 0 && ACKnr == 1)
		{
			ack = char(7); // ACK for modtaget frame nr. 0 igen
			//cout << "Dubletter" << endl;
		}
		else if ((int(heleDataTilString[8]) - '0') == 1 && ACKnr == 0)
		{
			ack = char(6); // ACK for modtaget frame nr. 1 igen
			//cout << "Dubletter" << endl;
		}
		else
		{
			ack = char(15); // Hex for NAK
			//cout << "Fejl" << endl;
		}
	}

	if (ack != char(15)) 
	{
		//cout << "ACKnr: " << ACKnr << endl;
		ofstream writeACK("ACKnr.txt");
		writeACK << ACKnr;
		writeACK.close();
	}
	return ack;
}

void Receiver::udpakFrame()
{
	if (!hasErrorCRC())
	{
		//cout << "CRC check is OKAY!" << endl;
		for (int i = 16; i < heleDataTilString.length() - 16; i++)//smider flag, header, trailer og flag væk
			messageAsBits += heleDataTilString[i];
	}
	//else { cout << "Error in CRC check!" << endl; }
}

void Receiver::decodeMessage()
{
	string currentChar = "";
	for (int i = 0; i < messageAsBits.length(); i += 8)
	{
		currentChar = "";
		for (int j = 0; j < 8; j++)
			currentChar += messageAsBits[i + j];
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
		return true;
	else
		return false;
}

int Receiver::checkHandshakeLength()
{
	if (checkForHandshake())
		return frame[0];//retunere længden af framen for herefter at oprette optagelse længden af den frame som snart bliver modtaget
	return 0;
}

Receiver::~Receiver()
{
}

