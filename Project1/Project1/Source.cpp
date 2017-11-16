#include "BehandlData.h"
#include "AudioRecord.h"
#include "Besked.h"
#include <iostream>
#include "Sender.h"
#include "Receiver.h"

//for at afspille besked
//(1) Besked test("this is a test");
//(2) test.createDTMFS();
//(3) test.getDTMFs().play();

//for at genkende DTMF tone
//(1) AudioRecord test(1);
//(2) test.record();
//(3) BehandlData testData(test.getAudioVector());
//(4) testData.recognizeDTMF();

//for at modtage sætning
//(1) Besked receive;
//(2) receive.modtagFrame();

int main()
{
	Besked lalTe("Ohana betyder familie.");
	lalTe.sendFrame();



	return 0;
}