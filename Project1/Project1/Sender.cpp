#include "Sender.h"

Sender::Sender()
{
}

Sender::Sender(string d)
{
	setMessage(d);
}

void Sender::setMessage(string d)
{
	data = d;
	konverterStringTilBitString();

	heleDataTilString.clear();
}

void Sender::konverterStringTilBitString()
{
	char charData;
	string dataTilString;
	for (int i = 0; i < data.size(); i++)//kører alle pladserne af string data indtastet
	{
		charData = data[i];//ligger tegn på plads indeks over i charData
		int dataTilInt = (int)charData;//tager ascii værdien af char og ligger de ind i dataTilInt
		dataTilString = bitset<8>(dataTilInt).to_string();//konvertere helt om til 8 bits til en string
		heleDataTilString += dataTilString;//ligger det konverterede til heleDataTilString
	}
}

string Sender::makeRemainder()
{
	// get data
	string encoded = heleDataTilString;

	// add zeroes to dataword
	for (int i = 0; i < crc.length() - 1; i++)
	{
		encoded += '0';
	}

	// loop
	for (int i = 0; i < encoded.length(); i++)
	{
		if (10 < encoded.length() - i || stoi(crc, nullptr, 2) <= stoi(encoded, nullptr, 2))
		{
			if (encoded[i] != '0')
			{
				for (int j = 0; j < crc.length(); j++) // loop as long as CRC
				{
					encoded[i + j] = encoded[i + j] == crc[j] ? '0' : '1'; // XOR if encoded == crc => 0 else 1
				}
				for (int a = 0; a < i; a++) {
					//cout << " ";
				}
			}
		}
		else break;
	}

	return (encoded.substr(encoded.size() - crc.length() + 1));
}

string Sender::makeCodeword()
{
	// data + remainder
	return heleDataTilString + makeRemainder();
}

int Sender::getTrailer()
{
	// string to int
	string str = makeRemainder();
	int myInt = stoi(str, nullptr, 2);

	return myInt;
}

int Sender::makeHeader()
{
	//framen længden sidste 7 bits i header
	header = 4 + data.size();
	if (header > 127)//hvis headeren er større end 7 bits gør f.eks. fragmentation
	{
		return -1;
	}
	else
	{
		if (header < 5)//beskeden er for kort.
		{
			return -1;
		}
	}

	//frame når første bit i header
	if (ackTal == 1)//er det et ulige tal?
	{
		header + 128;//svare til 1 i MSB
	}
	//ellers lad hver med at ligge noget til svare til 0 i MSB

	return header;
}

vector <int> Sender::makeFrame()
{
	header = 4 + data.size();

	frame.push_back(flag);//indsætter startflag
	frame.push_back(header);//indsætter header (længden af teksten)
	for (int i = 0; i < data.size(); i++)//lægger hver enkelt char af data i en vektor.
	{
		frame.push_back(data[i]);
	}
	frame.push_back(getTrailer());//indsætter trailer
	frame.push_back(flag);//indsætter slutflag

	for (int i = 0; i < frame.size(); i++)
		//cout << frame[i] << " ";

	return frame;
}

int Sender::makeHandshake()//synkronisere optagelse længden inden framen sendes.
{
	return makeFrame().size(); // Antal DTMF-toner der sendes
}

int Sender::getHeader()
{
	makeFrame();
	return header;
}

void Sender::frameNo(int ackNo)
{
	switch (ackNo)
	{
	case 0:
		ackTal = 0;
		break;
	case 1:
		ackTal = 1;
		break;
	default:
		break;
	}

	// acknowledgment
	if (data[0] == '\X06')  // ACK0
	{
		ackTal = 0;
	}
	if (data[0] == '\X07')	// ACK1
	{
		ackTal = 1;
	}
}

Sender::~Sender()
{
}
