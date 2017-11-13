#pragma once
#include <vector>
using namespace std;
class BehandlData
{
public:
	BehandlData();
	BehandlData(vector<float> data);
	float goertzelFilter(int TARGET_FREQUENCY, int SAMPLE_COUNT, vector<float> data);
	void hammingWindow(); //Virker som MATLABs hamming window
	vector<float> hanningWindow(vector<float> data);
	void printToFile();
	void printTo1File();
	void findFirstTone();
	//void nextTone();
	void nextTone(int WAIT_SAMPLES);
	int recognizeDTMF(vector<float> data);
	void slidingWindow();
	void printText();
	~BehandlData();
protected:
	vector<float> recordData;
	vector<float> frequencySumVector;
	vector<float> printThis; //TEST
	vector<float> printThis2; //TEST
	int numSamples;
	int toneCount = 0;
	int firstToneAt = 0;
};

