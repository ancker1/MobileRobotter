#pragma once
#include <vector>
#include "Besked.h"
#include <math.h>
#include <thread>
#include <chrono>
#include <fstream>
#include <iostream>
using namespace std;
class BehandlData
{
public:
	BehandlData();
	BehandlData(vector<float> data);
	float goertzelFilter(int TARGET_FREQUENCY, int SAMPLE_COUNT, vector<float> data);
	void hanningWindow(vector<float>& data);
	void printToFile();
	void nextTone(int WAIT_SAMPLES);
	int recognizeDTMF(vector<float> data, int threshold);
	void setWindowSize(int sampleCount);
	void findFnM(vector<float> data, int& mag, int& freq, bool findLow);
	void slideFirst(); //VIRKER 
	void slideSecond(); //VIRKER
	void slideThird();
	void slideFourth();
	void slide(int& firstToneAt, int& mSum, int& fSum, int slideNumber);
	void slideMultiple();
	vector<float> getfrequencySumVector();
	~BehandlData();
protected:
	vector<float> recordData;
	vector<float> frequencySumVector;
	int windowSize = 2205;
	int stepSize = 50;
	int numSamples;
	int toneCount = 0;
	int firstToneAt = 0;
	int FIRST_firstToneAt = 0;
	int FIRST_mSum = 0;
	int FIRST_fSum = 0;
	int SECOND_firstToneAt = 0;
	int SECOND_mSum = 0;
	int SECOND_fSum = 0;
	int THIRD_firstToneAt = 0;
	int THIRD_mSum = 0;
	int THIRD_fSum = 0;
	int FOURTH_firstToneAt = 0;
	int FOURTH_mSum = 0;
	int FOURTH_fSum = 0;
};

