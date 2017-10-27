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

string Sender::makeCodeword()
{
	// data
	encoded = msg;

	// add zeroes to dataword
	for (size_t i = 1; i < crc.length(); i++)
	{
		encoded += '0';
	}

	// loop
	for (size_t i = 0; i < msg.length(); ) //
	{
		for (size_t j = 0; j < crc.length(); j++) // loop as long as CRC
		{
			encoded[i + j] = encoded[i + j] == crc[j] ? '0' : '1'; // XOR if encoded == crc => 0 else 1
		}
		while ((i < encoded.length()) && (encoded[i] != '1')) // increment i as long as encoded = 0
		{
			i++;
		}
	}

	return getMessage() + (encoded.substr(encoded.length() - crc.length() + 1));
}

Sender::~Sender()
{
}
