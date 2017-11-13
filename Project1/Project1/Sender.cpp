#include "Sender.h"

Sender::Sender()
{
}

Sender::Sender(string d)
{
	data = d;

	// acknowledgment
	if (data[0] == '\X06')
	{
		ackTal = 0;
	}
	if (data[0] == '\X15')
	{
		ackTal = 1;
	}
}

string Sender::konverterStringTilBitString()
{
	string heleDataTilString;
	int indeks = 0;//pegepind til bostav indeks
	for (int i = 0; i < data.size(); i++)//k�rer alle pladserne af string data indtastet
	{
		charData = data[indeks];//ligger tegn p� plads indeks over i charData
		int dataTilInt = 0;
		dataTilInt = (int)charData;//tager ascii v�rdien af char og ligger de ind i dataTilInt
		dataTilString = bitset<8>(dataTilInt).to_string();//konvertere helt om til 8 bits til en string
		heleDataTilString += dataTilString;//ligger det konverterede til heleDataTilString
		indeks++;//t�ller indeks en op
	}
	return heleDataTilString;
}

string Sender::getCrc()
{
	return "100000111"; // CRC-8
}

string Sender::makeRemainder()
{
	// get data
	string encoded = konverterStringTilBitString();
	string crc = getCrc();

	// add zeroes to dataword
	for (int i = 1; i < crc.length(); i++)
	{
		encoded += '0';
	}

	// loop
	for (int i = 0; i < konverterStringTilBitString().length(); )
	{
		for (int j = 0; j < crc.length(); j++) // loop as long as CRC
		{
			encoded[i + j] = encoded[i + j] == crc[j] ? '0' : '1'; // XOR if encoded == crc => 0 else 1
		}
		while ((i < encoded.length()) && (encoded[i] != '1')) // increment i as long as encoded = 0
		{
			i++;
		}
	}

	return (encoded.substr(encoded.size() - crc.length() + 1));
}

string Sender::makeCodeword()
{
	// data + remainder
	return konverterStringTilBitString() + makeRemainder();
}

int Sender::getTrailer()
{
	// string to int
	string str = makeRemainder();
	int myInt = stoi(str);

	return bitset<8>(myInt).to_ulong();
}

int Sender::makeHeader()
{
	//framen l�ngden sidste 7 bits i header
	header = 4 + data.size();
	if (header > 127)//hvis headeren er st�rre end 7 bits g�r f.eks. fragmentation
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

	//frame n�r f�rste bit i header
	if (ackTal == 1)//er det et ulige tal?
	{
		header + 128;//svare til 1 i MSB
	}
	//ellers lad hver med at ligge noget til svare til 0 i MSB

	return header;
}

vector <int> Sender::makeFrame()
{
	flag = 0b00000001; // find ascii value to asgined to flag
	header = 4 + data.size();

	frame.push_back(flag);//inds�tter startflag
	frame.push_back(header);//inds�tter header (l�ngden af teksten)
	for (int i = 0; i < data.size(); i++)//l�gger hver enkelt char af data i en vektor.
	{
		frame.push_back(data[i]);
	}
	frame.push_back(getTrailer());//inds�tter trailer
	frame.push_back(flag);//inds�tter slutflag

	return frame;
}

int Sender::makeHandshake()//synkronisere optagelse med sendingen
{
	return 0b00000000; // DTMF tone => DD
}

int Sender::makeHandshakeLength()//synkronisere optagelse l�ngden inden framen sendes.
{
	return makeFrame().size();
}

int Sender::getHeader()
{
	makeFrame();
	return header;
}

Sender::~Sender()
{
}
