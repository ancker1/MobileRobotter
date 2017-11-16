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
	void findFirstTone();
	void nextTone(int WAIT_SAMPLES);
	int recognizeDTMF(vector<float> data);
	void findFnM(vector<float> data, int& mag, int& freq, bool findLow);
	void slidingWindow();
	void slideFirstHalf(); //VIRKER 
	void slideSecondHalf(); //VIRKER
	void slideTWO();
	vector<float> getfrequencySumVector();
	void printText();
	~BehandlData();
protected:
	vector<float> recordData;
	vector<float> frequencySumVector;
	int numSamples;
	int toneCount = 0;
	int firstToneAt = 0;
	int FIRST_firstToneAt = 0;
	int SECOND_firstToneAt = 0;
	int FIRST_mSum = 0;
	int SECOND_mSum = 0;
	int FIRST_fSum = 0;
	int SECOND_fSum = 0;
};

