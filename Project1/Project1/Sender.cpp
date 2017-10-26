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
	int m = msg.length();
	int n = crc.length();
	encoded = msg;

	// add zeroes to dataword
	for (int i = 1; i < n; i++)
	{
		encoded += '0';
	}
	int e = encoded.length();

	// loop
	for (int i = 0; i < m; ) //
	{
		for (int j = 0; j < n; j++) // loop as long as CRC
		{
			encoded[i + j] = encoded[i + j] == crc[j] ? '0' : '1'; // XOR if encoded == crc => 0 else 1
		}
		while ((i < e) && (encoded[i] != '1')) // increment i as long as encoded = 0
		{
			i++;
		}
	}

	return getMessage() + (encoded.substr(e - n + 1));
}

Sender::~Sender()
{
}
