#include "BehandlData.h"
#include <math.h>
//TEST
#include <thread>
#include <chrono>
#include <fstream>
#include <iostream>
//TEST


BehandlData::BehandlData()
{
}

BehandlData::BehandlData(vector<float> data)
{
	recordData = data;
	numSamples = data.size();
}

float BehandlData::goertzelFilter(int TARGET_FREQUENCY)
{
	int SAMPLING_RATE = 44100;
	double M_PI = 3.14159;
	int     k, i;
	float   omega, sine, cosine, coeff, q0, q1, q2, magnitude, real, imag;
	float   scalingFactor = numSamples / 2.0;

	float floatnumSamples = numSamples;
	k = (int)(0.5 + ((floatnumSamples * TARGET_FREQUENCY) / SAMPLING_RATE));
	omega = (2.0 * M_PI * k) / floatnumSamples;
	sine = sin(omega);
	cosine = cos(omega);
	coeff = 2.0 * cosine;
	q0 = 0;
	q1 = 0;
	q2 = 0;

	for (i = 0; i<numSamples; i++)
	{
		q0 = coeff * q1 - q2 + recordData[i];
		q2 = q1;
		q1 = q0;
	}

	// calculate the real and imaginary results
	// scaling appropriately
	real = (q1 - q2 * cosine) / scalingFactor;
	imag = (q2 * sine) / scalingFactor;

	magnitude = sqrtf(real*real + imag*imag);
	return magnitude;
}

void BehandlData::hammingWindow() //Virker som MATLAB's hamming window
{
	double M_PI = 3.14159;
	for (int n = 0; n < numSamples; n++)
	{
		recordData[n] = recordData[n] * (0.54 - 0.46 * cos((2 * M_PI * n) / (numSamples - 1)));
	}
}

void BehandlData::hanningWindow()
{
	double M_PI = 3.14159;
	for (int n = 0; n < numSamples; n++)
	{
		recordData[n] = recordData[n] * (0.5 * (1 - cos(( 2 * M_PI * n)/(numSamples - 1))));
	}
}

int BehandlData::recognizeDTMF()
{
	int dtmfFrequencies[8] = { 697, 770, 852, 941, 1209, 1336, 1477, 1633 };
	int highFrequency = 0;
	int highMagnitude = 0; //Eventuelt indstil threshold
	int lowFrequency = 0;
	int lowMagnitude = 0; //Eventuelt indstil threshold
	hammingWindow(); //Eventuelt anden vindue funktion
	for (int i = 0; i < 4; i++)
	{
		if (goertzelFilter(dtmfFrequencies[i]) > lowMagnitude)
		{
			lowFrequency = dtmfFrequencies[i];
			lowMagnitude = goertzelFilter(dtmfFrequencies[i]);
		}
	}
	for (int i = 4; i < 8; i++)
	{
		if (goertzelFilter(dtmfFrequencies[i]) > highMagnitude)
		{
			highFrequency = dtmfFrequencies[i];
			highMagnitude = goertzelFilter(dtmfFrequencies[i]);
		}
	}

	//GIV BOGSTAV


	//COUT RESULT
	cout << "Low frequency: " << lowFrequency << endl;
	cout << "High frequency: " << highFrequency << endl;

	// COUT TEST
	cout << " ________________________________________ " << endl;
	cout << "697:   " << goertzelFilter(697) << endl;
	cout << "770:   " << goertzelFilter(770) << endl;
	cout << "852:   " << goertzelFilter(852) << endl;
	cout << "941:   " << goertzelFilter(941) << endl;
	cout << "1209:  " << goertzelFilter(1209) << endl;
	cout << "1336:  " << goertzelFilter(1336) << endl;
	cout << "1477:  " << goertzelFilter(1477) << endl;
	cout << "1633:  " << goertzelFilter(1633) << endl;
	cout << "110:   " << goertzelFilter(110) << endl; //ingen DTMF frekvens på 110
	cout << "19500: " << goertzelFilter(19500) << endl; //ingen DTMF frekvens på 19500

	return lowFrequency + highFrequency;
}


void BehandlData::printToFile()
{
	ofstream audioData;
	audioData.open("AudioDataProcessed.txt");

	for (int i = 0; i < recordData.size(); i++)
	{
		audioData << recordData[i] << endl; 
	}

	audioData.close();
}

BehandlData::~BehandlData()
{
}
