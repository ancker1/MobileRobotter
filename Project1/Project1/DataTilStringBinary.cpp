#include "DataTilStringBinary.h"



DataTilStringBinary::DataTilStringBinary()
{
}


DataTilStringBinary::~DataTilStringBinary()
{
}

DataTilStringBinary::DataTilStringBinary(char d)//tager en enkelt char som input
{
	charData = d;
}

DataTilStringBinary::DataTilStringBinary(string da)//tager en hel string som input
{
	stringData = da;
}

string DataTilStringBinary::konverterCharTilBitString()//omdanner en enkelt char til en string af bits
{
	dataTilInt = (int)charData;//tager ascii værdien af char og ligger de ind i dataTilInt
	dataTilString = bitset<8>(dataTilInt).to_string();//konvertere helt om til 8 bits til en string
	return dataTilString;
}

string DataTilStringBinary::konverterStringTilBitString()//omdanner en helt string af bogstaver om til en string af bits
{
	indeks = 0;//pegepind til bostav indeks
	string heleDataTilString;
	for (int i = 0; i < stringData.size(); i++)//kører alle pladserne af string data indtastet
	{
		charData = stringData[indeks];//ligger tegn på plads indeks over i charData
		konverterCharTilBitString();//konvertere det enkelte char
		heleDataTilString += dataTilString;//ligger det konverterede til heleDataTilString
		indeks++;//tæller indeks en op
	}
	return heleDataTilString;
}
