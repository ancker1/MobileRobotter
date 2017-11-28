#include "BehandlData.h"
#include "AudioRecord.h"
#include "Besked.h"
#include <iostream>
#include "Sender.h"
#include "Receiver.h"
#include "LiveRecorder.h"
#include <chrono>
#include <thread>


int main()
{

	Besked* test = new Besked;
	thread idleThread(&Besked::setTekst, test); //T
	idleThread.detach();
	while (true)
		test->idleState();

	

	return 0;
}