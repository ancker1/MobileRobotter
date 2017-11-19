#include "BehandlData.h"
#include "Besked.h"
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

float BehandlData::goertzelFilter(int TARGET_FREQUENCY, int SAMPLE_COUNT, vector<float> data)
{
	int SAMPLING_RATE = 44100;
	double M_PI = 3.14159;
	int     k, i;
	float   omega, sine, cosine, coeff, q0, q1, q2, magnitude, real, imag;
	float   scalingFactor = SAMPLE_COUNT / 2.0;

	float floatnumSamples = SAMPLE_COUNT;
	k = (int)(0.5 + ((floatnumSamples * TARGET_FREQUENCY) / SAMPLING_RATE));
	omega = (2.0 * M_PI * k) / floatnumSamples;
	sine = sin(omega);
	cosine = cos(omega);
	coeff = 2.0 * cosine;
	q0 = 0;
	q1 = 0;
	q2 = 0;

	for (i = 0; i<SAMPLE_COUNT; i++)
	{
		q0 = coeff * q1 - q2 + data[i];
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

vector<float> BehandlData::hanningWindow(vector<float> data)
{
	double M_PI = 3.14159;
	for (int n = 0; n < data.size(); n++)
	{
		data[n] = data[n] * (0.5 * (1 - cos(( 2 * M_PI * n)/(data.size() - 1))));
	}
	return data;
}

int BehandlData::recognizeDTMF(vector<float> data)
{

	for (int i = 0; i < 500; i++)
	{
		data.insert(data.begin(), 0);
		data.push_back(0);
	}
	int dtmfFrequencies[8] = { 697, 770, 852, 941, 1209, 1336, 1477, 1633 };
	int highFrequency = 0;
	int highMagnitude = 0; //Eventuelt indstil threshold
	int lowFrequency = 0;
	int lowMagnitude = 0; //Eventuelt indstil threshold
	data = hanningWindow(data); //Eventuelt anden vindue funktion

	findFnM(data, lowMagnitude, lowFrequency, true);
	findFnM(data, highMagnitude, highFrequency, false);
	/*								KAN FJERNES, HVIS DET VIRKER
	for (int i = 0; i < 4; i++)
	{
		int currentMagnitude = goertzelFilter(dtmfFrequencies[i], data.size(), data);
		if (currentMagnitude > lowMagnitude)
		{
			lowFrequency = dtmfFrequencies[i];
			lowMagnitude = currentMagnitude;
		}
	}
	for (int i = 4; i < 8; i++)
	{
		int currentMagnitude = goertzelFilter(dtmfFrequencies[i], data.size(), data);
		if (currentMagnitude > highMagnitude)
		{
			highFrequency = dtmfFrequencies[i];
			highMagnitude = currentMagnitude;
		}
	}
	*/

/*
	//COUT RESULT
	cout << "Low frequency: " << lowFrequency << endl;
	cout << "High frequency: " << highFrequency << endl;

	// COUT TEST
	cout << " ________________________________________ " << endl;
	cout << "697:   " << goertzelFilter(697, data.size(), data) << endl;
	cout << "770:   " << goertzelFilter(770, data.size(), data) << endl;
	cout << "852:   " << goertzelFilter(852, data.size(), data) << endl;
	cout << "941:   " << goertzelFilter(941, data.size(), data) << endl;
	cout << "1209:  " << goertzelFilter(1209, data.size(), data) << endl;
	cout << "1336:  " << goertzelFilter(1336, data.size(), data) << endl;
	cout << "1477:  " << goertzelFilter(1477, data.size(), data) << endl;
	cout << "1633:  " << goertzelFilter(1633, data.size(), data) << endl;
	*/
	return lowFrequency + highFrequency;
}

void BehandlData::findFnM(vector<float> data, int& magnitude, int& frequency, bool findLow)
{
	int dtmfFrequencies[8] = { 697, 770, 852, 941, 1209, 1336, 1477, 1633 };
	if (findLow)
	{
		for (int i = 0; i < 4; i++)
		{
			int currentMagnitude = goertzelFilter(dtmfFrequencies[i], windowSize, data);
			if (currentMagnitude > magnitude)
			{
				frequency = dtmfFrequencies[i];
				magnitude = currentMagnitude;
			}
		}
	}
	else
	{
		for (int i = 4; i < 8; i++)
		{
			int currentMagnitude = goertzelFilter(dtmfFrequencies[i], windowSize, data);
			if (currentMagnitude > magnitude)
			{
				frequency = dtmfFrequencies[i];
				magnitude = currentMagnitude;
			}
		}
	}
}

/*
void BehandlData::slideFirst()
{
	vector<float> tempData = recordData;
	tempData.erase(tempData.begin() + 44100, tempData.end()); // Resulterer i tempData.size() = 44100.
	int highFrequency = 0;
	int highMagnitude = 0; //Eventuelt indstil threshold
	int lowFrequency = 0;
	int lowMagnitude = 0; //Eventuelt indstil threshold
	vector<float> currentTempData;


	for (int i = 0; i < (22050 - windowSize) / stepSize; i++) //HARDCODED til 44 SKAL ændres i forhold til SAMPLE_RATE
	{
		currentTempData = tempData;
		currentTempData.erase(currentTempData.begin(), currentTempData.begin() + i * stepSize);
		currentTempData.erase(currentTempData.begin() + windowSize, currentTempData.end());
		currentTempData = hanningWindow(currentTempData);

		findFnM(currentTempData, lowMagnitude, lowFrequency, true);
		findFnM(currentTempData, highMagnitude, highFrequency, false);
		if ((lowMagnitude + highMagnitude) > FIRST_mSum)
		{
			FIRST_mSum = lowMagnitude + highMagnitude;
			FIRST_fSum = lowFrequency + highFrequency;
			FIRST_firstToneAt = i * stepSize;
		}
	}

}

void BehandlData::slideSecond()
{
	vector<float> tempData = recordData;
	tempData.erase(tempData.begin() + 44100, tempData.end()); // Resulterer i tempData.size() = 44100.
	int highFrequency = 0;
	int highMagnitude = 0; //Eventuelt indstil threshold
	int lowFrequency = 0;
	int lowMagnitude = 0; //Eventuelt indstil threshold
	vector<float> currentTempData;


	for (int i = 0; i < (22050 - windowSize) / stepSize; i++) //HARDCODED til 44 SKAL ændres i forhold til SAMPLE_RATE
	{
		currentTempData = tempData;
		currentTempData.erase(currentTempData.begin(), currentTempData.begin() + 22050);
		currentTempData.erase(currentTempData.begin(), currentTempData.begin() + i * stepSize);
		currentTempData.erase(currentTempData.begin() + windowSize, currentTempData.end());
		currentTempData = hanningWindow(currentTempData);

		findFnM(currentTempData, lowMagnitude, lowFrequency, true);
		findFnM(currentTempData, highMagnitude, highFrequency, false);

		if ((lowMagnitude + highMagnitude) > SECOND_mSum)
		{
			SECOND_mSum = lowMagnitude + highMagnitude;
			SECOND_fSum = lowFrequency + highFrequency;
			SECOND_firstToneAt = i * stepSize + 22050;
		}
	}
}
*/
void BehandlData::slideFirst()
{
	slide(FIRST_firstToneAt, FIRST_mSum, FIRST_fSum, 1);
}

void BehandlData::slideSecond()
{
	slide(SECOND_firstToneAt, SECOND_mSum, SECOND_fSum, 2);
}

void BehandlData::slideThird()
{
	slide(THIRD_firstToneAt, THIRD_mSum, THIRD_fSum, 3);
}

void BehandlData::slideFourth()
{
	slide(FOURTH_firstToneAt, FOURTH_mSum, FOURTH_fSum, 4);
}

void BehandlData::slide(int& tone_AT, int& m_Sum, int& f_Sum, int slide_Number)
{
	vector<float> tempData = recordData;
	tempData.erase(tempData.begin() + 44100, tempData.end()); // Resulterer i tempData.size() = 44100.
	int highFrequency = 0;
	int highMagnitude = 0; //Eventuelt indstil threshold
	int lowFrequency = 0;
	int lowMagnitude = 0; //Eventuelt indstil threshold
	vector<float> currentTempData;


	for (int i = 0; i < (11050 - windowSize) / stepSize - 1; i++) //EVENTUELT: ændr således vinduerne kører over i hinanden.
	{
		currentTempData = tempData;
		if (slide_Number > 1)
			currentTempData.erase(currentTempData.begin(), currentTempData.begin() + 11050 * (slide_Number - 1));
		currentTempData.erase(currentTempData.begin(), currentTempData.begin() + i * stepSize);
		currentTempData.erase(currentTempData.begin() + windowSize, currentTempData.end());
		currentTempData = hanningWindow(currentTempData);

		findFnM(currentTempData, lowMagnitude, lowFrequency, true);
		findFnM(currentTempData, highMagnitude, highFrequency, false);

		if ((lowMagnitude + highMagnitude) > m_Sum)
		{
			m_Sum = lowMagnitude + highMagnitude;
			f_Sum = lowFrequency + highFrequency;
			tone_AT = i * stepSize + 11050 * (slide_Number - 1);
		}
	}
}

void BehandlData::slideTWO()
{
	cout << "START - WINDOW with 4 threads" << endl;
	auto start = std::chrono::steady_clock::now();		//AFLÆS CLOCK - TIDSTAGNING
	thread slidefirst([this] {slideFirst(); });
	thread slidesecond([this] {slideSecond(); });
	thread slidethird([this] {slideThird(); });
	thread slidefourth([this] {slideFourth(); });

	slidefirst.join();
	slidesecond.join();
	slidethird.join();
	slidefourth.join();

	if ((FIRST_mSum >= SECOND_mSum) && (FIRST_mSum >= THIRD_mSum) && (FIRST_mSum >= FOURTH_mSum))
	{
		firstToneAt = FIRST_firstToneAt;
	}
	else if ((SECOND_mSum >= FIRST_mSum) && (SECOND_mSum >= THIRD_mSum) && (SECOND_mSum >= FOURTH_mSum)) { firstToneAt = SECOND_firstToneAt; }
	else if ((THIRD_mSum >= FIRST_mSum) && (THIRD_mSum >= SECOND_mSum) && (THIRD_mSum >= FOURTH_mSum)) { firstToneAt = THIRD_firstToneAt; }
	else { firstToneAt = FOURTH_firstToneAt; }
	toneCount++;
	auto finish = std::chrono::steady_clock::now();		//AFLÆS CLOCK - TIDSTAGNING
	double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double> >(finish - start).count();		//ANTAL SEKUNDER I DOUBLE
	cout << "STOP.... Time spent: " << elapsed_seconds << endl;
	cout << firstToneAt << endl;
}


void BehandlData::slidingWindow()
{
	cout << "START - WINDOW with 1 threads" << endl;
	auto start = std::chrono::steady_clock::now();		//AFLÆS CLOCK - TIDSTAGNING
	vector<float> tempData = recordData;
	tempData.erase(tempData.begin() + 44100, tempData.end()); // Resulterer i tempData.size() = 44100.
	int dtmfFrequencies[8] = { 697, 770, 852, 941, 1209, 1336, 1477, 1633 };
	float highFrequency = 0;
	int highMagnitude = 0; //Eventuelt indstil threshold
	float lowFrequency = 0;
	int lowMagnitude = 0; //Eventuelt indstil threshold
	int magnitudeSum = 0;
	int frequencySum = 0;
	vector<float> currentTempData;


	for (int i = 0; i < (44100 - windowSize) / stepSize; i++) //HARDCODED til 44 SKAL ændres i forhold til SAMPLE_RATE
	{
		currentTempData = tempData;
		currentTempData.erase(currentTempData.begin(), currentTempData.begin() + i * stepSize);
		currentTempData.erase(currentTempData.begin() + windowSize, currentTempData.end());
		currentTempData = hanningWindow(currentTempData);

		for (int i = 0; i < 4; i++)
		{
			int currentMagnitude = goertzelFilter(dtmfFrequencies[i], windowSize, currentTempData);
			if (currentMagnitude > lowMagnitude)
			{
				lowFrequency = dtmfFrequencies[i];
				lowMagnitude = currentMagnitude;
			}
		}
		for (int i = 4; i < 8; i++)
		{
			int currentMagnitude = goertzelFilter(dtmfFrequencies[i], windowSize, currentTempData);
			if (currentMagnitude > highMagnitude)
			{
				highFrequency = dtmfFrequencies[i];
				highMagnitude = currentMagnitude;
			}
		}
		if ((lowMagnitude + highMagnitude) > magnitudeSum)
		{
			magnitudeSum = lowMagnitude + highMagnitude;
			frequencySum = lowFrequency + highFrequency;
			firstToneAt = i * stepSize;
		}
	}
	toneCount++;
	auto finish = std::chrono::steady_clock::now();		//AFLÆS CLOCK - TIDSTAGNING
	double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double> >(finish - start).count();		//ANTAL SEKUNDER I DOUBLE
	cout << "STOP.... Time spent: " << elapsed_seconds << endl;

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


void BehandlData::findFirstTone() // OUTDATED
{
	vector<float> toneVector;
	for (int i = 0; i < recordData.size(); i++)
	{
		if (recordData[i] > 500 || recordData[i] < -500) // Ikke verdens bedste løsning
		{
			firstToneAt = i;
			cout << recordData[firstToneAt] << endl;
			break;
		}
	}

	for (int i = 0; i < 44100; i++)
	{
		toneVector.push_back(recordData[firstToneAt + i]);
	}
	cout << "First tone: " << endl;
	frequencySumVector.push_back(recognizeDTMF(toneVector));
	toneCount++;

}

void BehandlData::nextTone(int WAIT_SAMPLES) // samme som nextTone() - dog med mulighed for at tilføje wait mellem hver tone
{
	int toneSize = 2205;
	//cout << firstToneAt << endl; // TEST
	vector<float> toneVector;
	int currentlyAt = firstToneAt + toneCount * toneSize + WAIT_SAMPLES * (toneCount - 1) + 44100; //WAIT_SAMPLES er længere for første tone
	//cout << currentlyAt << endl; //TEST
	if (currentlyAt + toneSize < recordData.size())
	{
		for (int i = 0; i < toneSize; i++)
		{
			toneVector.push_back(recordData[currentlyAt + i]);
		}
		//cout << "Tone: " << toneCount << endl;
		frequencySumVector.push_back(recognizeDTMF(toneVector)); //Tilføjer frekvens summen til vektor
		toneCount++;
	}

}

void BehandlData::printText()
{
	Besked testBesked("");
	string text = "";
	for (int i = 0; i < 62; i++) //MAX er: frequencySumVector.size() - 1
	{
		text += testBesked.frequenciesToChar(frequencySumVector[i++], frequencySumVector[i]);
	}
	cout << text << endl;
}

vector<float> BehandlData::getfrequencySumVector()
{
	return frequencySumVector;
}

BehandlData::~BehandlData()
{
}
