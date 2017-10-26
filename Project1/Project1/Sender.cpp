#include "Sender.h"



Sender::Sender(string message, string c)
{
	msg = message;
	crc = c;
	encoded = "";
}

string Sender::getMessage()
{
	return msg;
}

string Sender::getCrc()
{
	return crc;
}

string Sender::makeRemainder()
{
	// data
	int m = msg.length();
	int n = crc.length();
	encoded = msg;

	// add zeroes to dataword (one less the length of CRC)
	for (int i = 1; i < n; i++)
	{
		encoded += '0';
	}

	// loop
	for (int i = 0; i < msg.length(); )
	{
		for (int j = 0; j < n; j++) // loop as long as CRC
		{
			encoded[i + j] = encoded[i + j] == crc[j] ? '0' : '1'; // XOR if encoded == crc => 0 else 1
		}
		while ((i < encoded.length()) && (encoded[i] != '1')) // if [i] == 0 => next character
		{
			i++;
		}
	}

	return (encoded.substr(encoded.length() - n + 1));
}

string Sender::makeCodeword()
{
	return msg + makeRemainder();
}

Sender::~Sender()
{
}
