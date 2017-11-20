#include "LiveRecorder.h"
#include <iostream>
#include "BehandlData.h"


LiveRecorder::LiveRecorder()
{
}

LiveRecorder::LiveRecorder(int timeIn)
{
	setProcessingInterval(sf::milliseconds(timeIn));
}

bool LiveRecorder::onProcessSamples(const sf::Int16 * samples, std::size_t sampleCount)
{
	//std::cout << sampleCount << std::endl;
	sampleBuffer.clear();
	for (int i = 0; i < sampleCount; i++)
	{
		sampleBuffer.push_back(*(samples + i));
		//std::cout << *(samples + i) << std::endl;
	}
	//std::cout << j++ << std::endl;
	BehandlData analyzer(sampleBuffer);
	analyzer.setWindowSize(sampleCount); // Grundet ændring af windowSize kan sliding window ikke bruges herinde.
	int tone = analyzer.recognizeDTMF(sampleBuffer, 40);
	if (tone == 2574)
	{
		//std::cout << "Done" << std::endl;
		foundDtmf = true; //May need to change back before returning to waiting for next message.
		return false;
	}
	return true;
}

bool LiveRecorder::dfmtDiscovered()
{
	return foundDtmf;
}

void LiveRecorder::onStop()
{
	foundDtmf = true;
}


LiveRecorder::~LiveRecorder()
{
}
