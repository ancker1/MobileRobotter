#pragma once
#include <vector>
using namespace std;
class BehandlData
{
public:
	BehandlData();
	BehandlData(vector<float> data);
	float goertzelFilter(int);
	void hammingWindow(); //Virker som MATLABs hamming window
	void hanningWindow();
	void printToFile();
	int recognizeDTMF();
	~BehandlData();
protected:
	vector<float> recordData;
	int numSamples;
};

