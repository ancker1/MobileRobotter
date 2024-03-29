#include "Sender.h"

Sender::Sender()
{
}

Sender::Sender(string d)
{
	data = d;
	konverterStringTilBitString();
}

void Sender::setMessage(string d)
{
	data = d;
	konverterStringTilBitString();

//	heleDataTilString.clear();
//	frame.clear();
}

void Sender::konverterStringTilBitString()
{
	char charData;
	string dataTilString;
	for (int i = 0; i < data.size(); i++)//k�rer alle pladserne af string data indtastet
	{
		charData = data[i];//ligger tegn p� plads indeks over i charData
		int dataTilInt = (int)charData;//tager ascii v�rdien af char og ligger de ind i dataTilInt
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
		encoded += '0';

	// loop
	for (int i = 0; i < encoded.length(); i++)
	{
		if (10 < encoded.length() - i || stoi(crc, nullptr, 2) <= stoi(encoded, nullptr, 2))
		{
			if (encoded[i] != '0')
			{
				for (int j = 0; j < crc.length(); j++) // loop as long as CRC
					encoded[i + j] = encoded[i + j] == crc[j] ? '0' : '1'; // XOR if encoded == crc => 0 else 1
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
	return stoi(makeRemainder(), nullptr, 2);
}

int Sender::makeHeader()
{
	ifstream readFrame("Framenr.txt");
	int Framenr = readFrame.get();
	Framenr = Framenr - '0';
	readFrame.close();

	//cout << "Framenr: " << Framenr << endl;

	//framen l�ngden sidste 7 bits i header
	header = 4 + data.size();

	//frame n�r f�rste bit i header
	if (Framenr == 1)//er det et ulige tal?
		header += 128;//svare til 1 i MSB

	//ellers lad hver med at ligge noget til svare til 0 i MSB
	
	//cout << "Header: " << int(header) << endl;

	return header;
}

vector <int> Sender::makeFrame()
{
	frame.push_back(flag);//inds�tter startflag
	frame.push_back(makeHeader());//inds�tter header (l�ngden af teksten)
	for (int i = 0; i < data.size(); i++)//l�gger hver enkelt char af data i en vektor.
		frame.push_back(data[i]);
	frame.push_back(getTrailer());//inds�tter trailer
	frame.push_back(flag);//inds�tter slutflag

	return frame;
}

int Sender::makeHandshake()//synkronisere optagelse l�ngden inden framen sendes.
{
	return makeFrame().size(); // Antal DTMF-toner der sendes
}

int Sender::getHeader()
{
	makeFrame();
	return header;
}

Sender::~Sender()
{
}
