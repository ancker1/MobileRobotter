#include "BehandlData.h"

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
	double PI = 3.14159;
	float  singleside_scaling = 2.0 / SAMPLE_COUNT;
	int k = (int)(0.5 + (SAMPLE_COUNT * TARGET_FREQUENCY) / SAMPLING_RATE); //0.5 adderes for at runde til nærmeste int
	float cos_part = cos((2.0 * PI * k) / SAMPLE_COUNT);
	float v0 = 0;
	float v1 = 0;
	float v2 = 0;
	data[SAMPLE_COUNT - 1] = 0;
	for (int i = 0; i < SAMPLE_COUNT; i++)
	{
		v2 = v1;
		v1 = v0;
		v0 = 2.0 * cos_part * v1 - v2 + data[i];
	}
	//MODIFICERET GOERTZEL - Enkelt sidet
	float mag = sqrt((v0*v0) + (v1*v1) - (2 * cos_part*v0*v1)) * singleside_scaling;
	return mag;
}

void BehandlData::hanningWindow(vector<float>& data)
{
	double PI = 3.14159;
	for (int n = 0; n < data.size(); n++)
		data[n] = data[n] * (0.5 * (1 - cos(( 2 * PI * n)/(data.size() - 1))));
}

int BehandlData::recognizeDTMF(vector<float> data, int threshold = 0)
{
	for (int i = 0; i < 500; i++)
	{
		data.insert(data.begin(), 0);
		data.push_back(0);
	}
	int highFrequency = 0;
	int highMagnitude = threshold; //Eventuelt indstil threshold
	int lowFrequency = 0;
	int lowMagnitude = threshold; //Eventuelt indstil threshold
	hanningWindow(data); //Eventuelt anden vindue funktion
	findFnM(data, lowMagnitude, lowFrequency, true);
	findFnM(data, highMagnitude, highFrequency, false);
	/*
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

void BehandlData::setWindowSize(int sampleCount)
{
	windowSize = sampleCount;
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
	int slideLength;

	if (slide_Number != 4)
		slideLength = (11050 + 2205 - windowSize) / stepSize - 1;
	else
		slideLength = (11050 - windowSize) / stepSize - 1;

	for (int i = 0; i < slideLength; i++) //EVENTUELT: ændr således vinduerne kører over i hinanden.
	{
		currentTempData = tempData;
		if (slide_Number > 1)
			currentTempData.erase(currentTempData.begin(), currentTempData.begin() + 11050 * (slide_Number - 1));
		currentTempData.erase(currentTempData.begin(), currentTempData.begin() + i * stepSize);
		currentTempData.erase(currentTempData.begin() + windowSize, currentTempData.end());
		hanningWindow(currentTempData);
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

void BehandlData::slideMultiple()
{
	//cout << "START - WINDOW with 4 threads" << endl;
	//auto start = std::chrono::steady_clock::now();		//AFLÆS CLOCK - TIDSTAGNING
	thread slidefirst(&BehandlData::slideFirst, this);
	thread slidesecond(&BehandlData::slideSecond, this);
	thread slidethird(&BehandlData::slideThird, this);
	thread slidefourth(&BehandlData::slideFourth, this);

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
	//auto finish = std::chrono::steady_clock::now();		//AFLÆS CLOCK - TIDSTAGNING
	//double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double> >(finish - start).count();		//ANTAL SEKUNDER I DOUBLE
	//cout << "STOP.... Time spent: " << elapsed_seconds << endl;
	//cout << firstToneAt << endl;
}



void BehandlData::printToFile()
{
	ofstream audioData;
	audioData.open("AudioDataProcessed.txt");
	for (int i = 0; i < recordData.size(); i++)
		audioData << recordData[i] << endl; 
	audioData.close();
}



void BehandlData::nextTone(int WAIT_SAMPLES) // samme som nextTone() - dog med mulighed for at tilføje wait mellem hver tone
{
	int toneSize = 2205;
	//cout << firstToneAt << endl; // TEST
	vector<float> toneVector;
	int currentlyAt = firstToneAt + toneCount * toneSize + WAIT_SAMPLES * (toneCount - 1) + 44100; //WAIT_SAMPLES er længere for første tone
	//cout << "Currently at: " << currentlyAt << endl; //TEST
	if (currentlyAt + toneSize < recordData.size())
	{
		for (int i = 0; i < toneSize; i++)
			toneVector.push_back(recordData[currentlyAt + i]);
		//cout << "Tone: " << toneCount << endl;
		frequencySumVector.push_back(recognizeDTMF(toneVector)); //Tilføjer frekvens summen til vektor
		toneCount++;
	}
}

vector<float> BehandlData::getfrequencySumVector()
{
	return frequencySumVector;
}

BehandlData::~BehandlData()
{
}
