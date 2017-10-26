#include "BehandlData.h"
#include "Besked.h"
#include "DTMF.h"
#include "Receiver.h"
#include "Sender.h"
#include <iostream>

int main()
{
	cout << "test" << endl;

	// CRC TEST
	Sender testS("101010101", "100000111");
	cout << "The message: " << testS.getMessage() << endl;
	cout << "The CRC generator polynomial: " << testS.getCrc() << endl;
	cout << "The remainder: " << testS.makeRemainder() << endl;
	cout << "The codeword: " << testS.makeCodeword() << endl;
	cout << endl;

	Receiver testR(testS.makeCodeword(), testS.getCrc());
	cout << "The codeword: " << testR.getCodeword() << endl;
	cout << "The CRC generator polynomial: " << testR.getCrc() << endl;
	cout << "The syndrome: " << testR.getSyndrome() << endl;
	cout << "Check for error: " << testR.checkForError() << endl;

	return 0;
}