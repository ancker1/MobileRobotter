#include "Frame.h"



Frame::Frame()
{
}

Frame::Frame(string d)
{
	data = d;

	// count data in bits
	/*
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

int Frame::getData()// ligger data ind i charTemp
{

}

int Frame::getTrailer() // get the CRC remainder for the hole string
{
	return data.makeTrailer();
}

void Frame::makeFrame()
{
	//Tager et tempChar og ligger ind i array = 1 byte pr plads i array
	flag = 0b00000001; // find ascii value to asgined to flag
	int indeks = 2;
	const int frameSize = 4 + data.size();
	int* frame;
	frame = new int[frameSize];

	for (int i = 0; i < data.size(); i++)//lægger hver enkelt char af data i et array.
	{
		frame[indeks] = data[i];
		indeks++;
	}
	frame[0] = flag;
	frame[1] = indeks + 2; //header størrelsen af hele framen

	/*
	int frame[] = {flag, makeHeader(), getData(), getTrailer(), flag};

	for (int i = 0; i < 5; i++)
	{
		cout << frame[i] << " ";
	}
	cout << endl;
	*/
}

Frame::~Frame()
{
}
