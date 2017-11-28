#pragma once
#include <SFML\Audio.hpp>
#include <vector>
#include <iostream>
#include "BehandlData.h"


class LiveRecorder : public sf::SoundRecorder
{
public:
	LiveRecorder();
	LiveRecorder(int);
	virtual bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount);
	bool dtmfDiscovered();
	//virtual void onStop();
	~LiveRecorder();

private:
	int j = 0;
	std::vector<float> sampleBuffer;
	bool foundDtmf = false;
};

