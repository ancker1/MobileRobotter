#pragma once
#include <string>
#include <iostream>
#include <bitset>
using namespace std;
class DataTilStringBinary
{
public:
	DataTilStringBinary();
	DataTilStringBinary(char d);
	DataTilStringBinary(string da);
	string konverterCharTilBitString();
	string konverterStringTilBitString();
	~DataTilStringBinary();

protected:
	int indeks;
	char charData;
	string stringData;
	int dataTilInt;
	string dataTilString;
};

