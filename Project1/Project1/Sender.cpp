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

void Sender::makeFrame()
{
	//Tager et tempChar og ligger ind i array = 1 byte pr plads i array
	flag = 0b00000001; // find ascii value to asgined to flag
	int indeks = 2;
	const int frameSize = 4 + data.size();

	frame = new int[frameSize];

	for (int i = 0; i < frameSize; i++)//sætter 0 ind på alle pladser i array.
	{
		frame[i] = 0;
	}

	for (int i = 0; i < data.size(); i++)//lægger hver enkelt char af data i et array.
	{
		frame[indeks] = data[i];
		indeks++;
	}

	//indsætter startFlag, header, trailer og slutfalg
	frame[0] = flag;// sætter start flag ind
	frame[1] = indeks + 2;// header størrelsen af hele framen
	frame[indeks] = getTrailer();// sætter vores trailer ind
	frame[indeks + 1] = flag;// sætter slutflag ind

							 //udskriver framen
	for (int i = 0; i < frameSize; i++)
	{
		cout << frame[i] << " ";
	}
}

Sender::~Sender()
{
}
