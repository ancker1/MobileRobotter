#pragma once
#include <SFML\Audio.hpp>
#include <vector>
using namespace std;
class AudioRecord
{
public:
	AudioRecord();
	AudioRecord(int secs);
	void record();
	void printToFile();
	void setSecondsToRecord(int secs);
	vector<float> getAudioVector();
	~AudioRecord();
protected:
	int secondsToRecord;
	sf::SoundBufferRecorder recorder;
	vector<float> audioVector;
};

