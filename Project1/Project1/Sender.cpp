#include "Sender.h"

Sender::Sender()
{
}

Sender::Sender(string d)
{
	data = d;
}

string Sender::konverterStringTilBitString()
{
	string heleDataTilString;
	int indeks = 0;//pegepind til bostav indeks
	for (int i = 0; i < data.size(); i++)//kører alle pladserne af string data indtastet
	{
		charData = data[indeks];//ligger tegn på plads indeks over i charData
		int dataTilInt = 0;
		dataTilInt = (int)charData;//tager ascii værdien af char og ligger de ind i dataTilInt
		dataTilString = bitset<8>(dataTilInt).to_string();//konvertere helt om til 8 bits til en string
		heleDataTilString += dataTilString;//ligger det konverterede til heleDataTilString
		indeks++;//tæller indeks en op
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

vector <int> Sender::makeFrame()
{
	flag = 0b00000001; // find ascii value to asgined to flag
	header = 4 + data.size();

	frame.push_back(flag);//indsætter startflag
	frame.push_back(header);//indsætter header (længden af teksten)
	for (int i = 0; i < data.size(); i++)//lægger hver enkelt char af data i en vektor.
	{
		frame.push_back(data[i]);
	}
	frame.push_back(getTrailer());//indsætter trailer
	frame.push_back(flag);//indsætter slutflag
	
	return frame;
}

int Sender::getHeader()
{
	makeFrame();
	return header;
}

Sender::~Sender()
{
}
