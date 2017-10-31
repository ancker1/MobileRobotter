#include "Frame.h"



Frame::Frame()
{
}

Frame::Frame(string d)
{
	data = d;

	/*
	// count data in bits
	int oldData = data;
	count = 0;
	while (oldData != 0)
	{
		oldData = oldData >> 1;
		count++;
	}
	while (count % 8 != 0)
	{
		count++;
	}
	*/

}

int Frame::getCount()
{
	// check if data only is one byte
	if (count > 8)
	{
		cout << "Your data is corrupted!" << endl;
	}

	return count;
}

int Frame::makeHeader() // get the size of the hole text string
{
	return 0;
}

int Frame::getData()
{
	return 0;
}

int Frame::getTrailer() // get the CRC remainder for the hole string
{
	return Sender(data, "100000111").makeTrailer();
}

void Frame::makeFrame()
{
	//Tager et tempChar og ligger ind i array = 1 byte pr plads i array
	flag = 0b00000001; // find ascii value to asgined to flag
	int indeks = 2;
	const int frameSize = 4 + data.size();

	int* frame;
	frame = new int[frameSize];

	for (int i = 0; i < frameSize; i++)//s�tter 0 ind p� alle pladser i array.
	{
		frame[i] = 0;
	}

	for (int i = 0; i < data.size(); i++)//l�gger hver enkelt char af data i et array.
	{
		frame[indeks] = data[i];
		indeks++;
	}
	//inds�tter startFlag, header, trailer og slutfalg
	frame[0] = flag;// s�tter start flag ind
	frame[1] = indeks + 2;// header st�rrelsen af hele framen
	frame[indeks] = getTrailer();// s�tter vores trailer ind
	frame[indeks + 1] = flag;// s�tter slutflag ind
	
	//udskriver framen
	for (int i = 0; i < frameSize; i++)
	{
		cout << frame[i] << " ";
	}
}

Frame::~Frame()
{
}
