#include "AudioRecord.h"
#include <thread>
#include <chrono>
#include <fstream>
#include <iostream>

using namespace std;

AudioRecord::AudioRecord()
{
	secondsToRecord = 1;
}

AudioRecord::AudioRecord(int seconds)
{
	secondsToRecord = seconds;
}

void AudioRecord::setSecondsToRecord(int seconds)
{
	secondsToRecord = seconds;
	//Skal senere agere ud fra størrelsen på pakken der modtages (størrelsen på pakken er i headeren).
}

void AudioRecord::record()
{
	recorder.start(44100);
	this_thread::sleep_for(chrono::seconds(secondsToRecord));
	recorder.stop();
	const sf::Int16 * samplesPointer = recorder.getBuffer().getSamples();
	for (int i = 0; i < recorder.getBuffer().getSampleCount(); i++) //recorder.getBuffer().getsamles() returnerer adresse til første element
	{
		audioVector.push_back(*(samplesPointer + i));
	}
}

vector<float> AudioRecord::getAudioVector()
{
	return audioVector;
}

void AudioRecord::printToFile()
{
	ofstream audioData;
	audioData.open("AudioData.txt");

	for (int i = 0; i < audioVector.size(); i++)
	{
		audioData << audioVector[i] << endl; //Hvad er audioVector[1, i]?
	}

	audioData.close();
}

AudioRecord::~AudioRecord()
{
}
