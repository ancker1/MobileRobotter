#include "BehandlData.h"
#include "AudioRecord.h"
#include "Besked.h"
#include <iostream>
#include "Sender.h"
#include "Receiver.h"
#include "LiveRecorder.h"
#include <chrono>
#include <thread>

//for at genkende DTMF tone
//(1) AudioRecord test(1);
//(2) test.record();
//(3) BehandlData testData(test.getAudioVector());
//(4) testData.recognizeDTMF();

//for at afspille besked
//(1) Besked test("Ohana betyder familie.");
//(2) test.sendBesked();

//for at modtage sætning
//(1) Besked receive;
//(2) receive.modtagBesked();

int main()
{

	Besked* test = new Besked;
	thread idleThread(&Besked::setTekst, test); //T
	idleThread.detach();
	while (true)
	{
		test->idleState();
	}

	

	return 0;
}