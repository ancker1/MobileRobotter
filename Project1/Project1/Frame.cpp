#include "Frame.h"



Frame::Frame()
{
}

Frame::Frame(int d)
{
	data = d;

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
	return data;
}

int Frame::getTrailer() // get the CRC remainder for the hole string
{
	return trailer.makeTrailer();
}

void Frame::makeFrame()
{
	flag = 0b00000001; // find ascii value to asgined to flag

	int frame[] = {flag, data, getTrailer(), flag};

	for (int i = 0; i < 4; i++)
	{
		cout << frame[i] << " ";
	}
	cout << endl;
}

Frame::~Frame()
{
}
