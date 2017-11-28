#include "Besked.h"

using namespace std;

Besked::Besked()
{
	// On startup (programmerne skal startes 'samtidig')
	ofstream writeACK("ACKnr.txt");
	writeACK << 0;
	writeACK.close();

	ofstream writeFrame("Framenr.txt");
	writeFrame << 0;
	writeFrame.close();
}

Besked::Besked(string tekst)
{
	message = tekst;
}

void Besked::setTekst()
{
	string x;
	while (true)
	{
		getline(cin, x);
		message = x;
		x.clear();
	}
}

void Besked::encapsulateMSG()
{
	Sender createOBJ(message);
	encapsulatedMSG = createOBJ.makeFrame();
}

void Besked::createSFMLarray(char byte, SFMLarray& arraySFML)
{
	int lower_nibble = byte & 0b00001111;
	int higher_nibble = byte & 0b11110000;
	higher_nibble = higher_nibble >> 4;
	currentHighDTMF.setFrequenciesFromChar(checkDTMF(higher_nibble));
	currentLowDTMF.setFrequenciesFromChar(checkDTMF(lower_nibble));
	arraySFML.addTone(currentHighDTMF.getHigh(), currentHighDTMF.getLow());
	arraySFML.addTone(currentLowDTMF.getHigh(), currentLowDTMF.getLow());
}


void Besked::createDTMFS()
{
	encapsulateMSG();
	for (int i = 0; i < encapsulatedMSG.size(); i++) 
		createSFMLarray(encapsulatedMSG[i], allDTMFs);
	allDTMFs.readySound();
}

SFMLarray Besked::getDTMFs() 
{
	return allDTMFs;
}

char Besked::checkDTMF(int intIn)
{
	switch (intIn)
	{
	case 0b0001:
		return '1';
	case 0b0010:
		return '2';
	case 0b0011:
		return '3';
	case 0b0100:
		return '4';
	case 0b0101:
		return '5';
	case 0b0110:
		return '6';
	case 0b0111:
		return '7';
	case 0b1000:
		return '8';
	case 0b1001:
		return '9';
	case 0b1010:
		return '0';
	case 0b1011:
		return '*';
	case 0b1100:
		return '#';
	case 0b1101:
		return 'A';
	case 0b1110:
		return 'B';
	case 0b1111:
		return 'C';
	case 0b0000:
		return 'D';
	default:
		break;
	}
}

char Besked::frequenciesToChar(int first_FrequencySum, int second_FrequencySum)
{
	int highNibble;
	int lowNibble;
	int msgByte;
	switch (first_FrequencySum)
	{
	case 1906:
		highNibble = 0b0001;
		break;
	case 2033:
		highNibble = 0b0010;
		break;
	case 2174:
		highNibble = 0b0011;
		break;
	case 1979:
		highNibble = 0b0100;
		break;
	case 2106:
		highNibble = 0b0101;
		break;
	case 2247:
		highNibble = 0b0110;
		break;
	case 2061:
		highNibble = 0b0111;
		break;
	case 2188:
		highNibble = 0b1000;
		break;
	case 2329:
		highNibble = 0b1001;
		break;
	case 2277:
		highNibble = 0b1010;
		break;
	case 2150:
		highNibble = 0b1011;
		break;
	case 2418:
		highNibble = 0b1100;
		break;
	case 2330:
		highNibble = 0b1101;
		break;
	case 2403:
		highNibble = 0b1110;
		break;
	case 2485:
		highNibble = 0b1111;
		break;
	case 2574:
		highNibble = 0b0000;
		break;
	default:
		highNibble = 0;
		break;
	}
	switch (second_FrequencySum)
	{
	case 1906:
		lowNibble = 0b0001;
		break;
	case 2033:
		lowNibble = 0b0010;
		break;
	case 2174:
		lowNibble = 0b0011;
		break;
	case 1979:
		lowNibble = 0b0100;
		break;
	case 2106:
		lowNibble = 0b0101;
		break;
	case 2247:
		lowNibble = 0b0110;
		break;
	case 2061:
		lowNibble = 0b0111;
		break;
	case 2188:
		lowNibble = 0b1000;
		break;
	case 2329:
		lowNibble = 0b1001;
		break;
	case 2277:
		lowNibble = 0b1010;
		break;
	case 2150:
		lowNibble = 0b1011;
		break;
	case 2418:
		lowNibble = 0b1100;
		break;
	case 2330:
		lowNibble = 0b1101;
		break;
	case 2403:
		lowNibble = 0b1110;
		break;
	case 2485:
		lowNibble = 0b1111;
		break;
	case 2574:
		lowNibble = 0b0000;
		break;
	default:
		lowNibble = 0;
		break;
	}
	highNibble = highNibble << 4;
	msgByte = highNibble + lowNibble;
	if ((msgByte >= 0 && msgByte <= 255))
		return (char)msgByte;
	return ' ';
}

void Besked::modtagHandshake()
{
	AudioRecord record;
	record.setSecondsToRecord(2); //RECORD_LENGTH
	record.record();
	BehandlData objectTest(record.getAudioVector());
	objectTest.slideMultiple();
	for (int i = 0; i < 2; i++) //AMOUNT_TONE
		objectTest.nextTone(50);
	vector<float> freqSumVec = objectTest.getfrequencySumVector();
	char length = frequenciesToChar(freqSumVec[0], freqSumVec[1]); //Antal characters
	if (length >= 128)
		length = length - 0b10000000;
	AMOUNT_TONE = (int)length * 2; //Antal toner
	if (AMOUNT_TONE < 5)
		AMOUNT_TONE = 5;
}

void Besked::sendHandshake()
{
	Sender createOBJ(message);
	SFMLarray handshakeDTMFs;
	createSFMLarray(createOBJ.makeHandshake(), handshakeDTMFs);
	handshakeDTMFs.readySound();
	handshakeDTMFs.play();
}

void Besked::sendFrame()
{
	createDTMFS();
	getDTMFs().play();
	LiveRecorder dtmfTest(50);
	dtmfTest.start(); //MODTAG ACK
	while (!dtmfTest.dtmfDiscovered())
	{}
	dtmfTest.stop();
}

void Besked::modtagFrame()
{
	AudioRecord record;
	int recordLength = (2255 * AMOUNT_TONE + 3 * 44100) / 44100;
	//cout << "Antal sekunder til optagelse: " << recordLength << endl;
	record.setSecondsToRecord(recordLength); //RECORD_LENGTH
	//cout << "Start" << endl;
	record.record();
	BehandlData* objectTesta = new BehandlData(record.getAudioVector());
	//cout << "Stop" << endl;
	objectTesta->slideMultiple();
	for (int i = 0; i < AMOUNT_TONE; i++) //AMOUNT_TONE - SKAL VÆRE 52 FOR "OHANA BETYDER FAMILIE."
		objectTesta->nextTone(50);
	vector<float> freqSumVec = objectTesta->getfrequencySumVector();
	string text;
	for (int i = 0; i < freqSumVec.size()-1; i++) //MAX er: frequencySumVector.size() - 1
		text += frequenciesToChar(freqSumVec[i++], freqSumVec[i]);
	delete objectTesta;
	Receiver receiveOBJ(text);
	//cout << "AMOUNT_TONE: " << AMOUNT_TONE << endl;
	if (receiveOBJ.isLengthOK(AMOUNT_TONE))
	{
		receiveOBJ.udpakFrame();
		receiveOBJ.decodeMessage();
		cout << receiveOBJ.getMessage() << endl;
		sendFrameACK(receiveOBJ, false);
	}
	else
		sendFrameACK(receiveOBJ, true);
}

void Besked::sendACK()
{
	SFMLarray ackDTMF;
	ackDTMF.readySound();
	ackDTMF.play();
}

void Besked::sendFrameACK(Receiver receiver, bool shouldNACK)
{
		SFMLarray sendD;		
		sendD.readySound();		
		sendD.play();			
		this_thread::sleep_for(0.5s);	
		SFMLarray ackFrameDTMF;
		if (shouldNACK)
			createSFMLarray(char(15), ackFrameDTMF);
		else
			createSFMLarray(receiver.nextACK(), ackFrameDTMF);
		ackFrameDTMF.readySound();
		ackFrameDTMF.play();
}

bool Besked::modtagFrameACK()
{
	AudioRecord record;
	record.setSecondsToRecord(2);
	record.record();
	BehandlData objectTest(record.getAudioVector());
	objectTest.slideMultiple();
	for (int i = 0; i < 2; i++)
		objectTest.nextTone(50);
	vector<float> freqSumVec = objectTest.getfrequencySumVector();
	char receivedNr = frequenciesToChar(freqSumVec[0], freqSumVec[1]);
	ifstream readFramenr("Framenr.txt");
	int frameNr = readFramenr.get() - '0';
	readFramenr.close();
	if ((receivedNr == 6 && frameNr == 1) || (receivedNr == 7 && frameNr == 0))
	{
		frameNr = frameNr ^ 1;
		ofstream writeFramenr("Framenr.txt");
		writeFramenr << frameNr;
		writeFramenr.close();
		return true;
	}
	else
		return false;
}

void Besked::modtagBesked()
{
	modtagHandshake();
	sendACK();				//SEND ACK
	modtagFrame();
	encapsulatedMSG.clear();
}

void Besked::sendBesked()
{
	LiveRecorder rTest(50);
	SFMLarray sendD;	
	sendD.readySound();	
	sendD.play();			
	this_thread::sleep_for(0.5s);	
	sendHandshake();
	rTest.start(); //MODTAG ACK
	while (!rTest.dtmfDiscovered())
	{}
	rTest.stop();
	sendFrame();
	if (!modtagFrameACK())
		lastMSG = message;
	message.clear();
	allDTMFs.reset();
}

void Besked::idleState()
{
	bool shouldReceive = true;
	LiveRecorder iTest(50);
	iTest.start();
	while (!iTest.dtmfDiscovered() && shouldReceive)
	{
		if (lastMSG != "")
		{
			message = lastMSG;
			lastMSG = "";
		} 

		if (message != "")
			shouldReceive = false;
	}
	iTest.stop();
	if (shouldReceive)
		modtagBesked();
	else
		sendBesked();
}



Besked::~Besked()
{
}
