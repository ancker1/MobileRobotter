#include "BehandlData.h"
#include "Besked.h"
#include "DTMF.h"
#include "Receiver.h"
#include "Sender.h"
#include "DataTilStringBinary.h"
#include <iostream>

//for at afspille besked
//(1) besked test("this is a test");
//(2) test.playMessage();

int main()
{
	/*char buttons[16] = {'1', '2', '3', 'A',
						'4', '5', '6', 'B',
						'7', '8', '9', 'C',
						'*', '0', '#', 'D' };

	for (int i = 0; i < sizeof(buttons); i++) {
		cout << "Playing " << buttons[i] << endl;
		DTMF tone(buttons[i]);
		tone.getTone().play(1);
	}*/

	//Besked test("Wubba dub a dub dub");
	//test.playMessage();

	// TEST CRC

	//Test DataTilStringBinary
	DataTilStringBinary testChar(' ');
	cout << testChar.konverterCharTilBitString() << endl;
	DataTilStringBinary testString("j");
	cout << "Binary text string: " << testString.konverterStringTilBitString() << endl;
	cout << endl;

	// TEST sender
	Sender testS(testString.konverterStringTilBitString(), "1011");
	cout << "The message: " << testS.getMessage() << endl;
	cout << "The CRC generator polynomial: " << testS.getCrc() << endl;
	cout << "The codeword: " << testS.makeCodeword() << endl;
	cout << endl;

	// TEST receiver
	Receiver testR(testS.makeCodeword(), testS.getCrc());
	cout << "The codeword: " << testR.getCodeword() << endl;
	cout << "The CRC generator polynomial: " << testR.getCrc() << endl;
	cout << "The syndrome: " << testR.getSyndrome() << endl;
	cout << "Check for error: " << testR.checkForError() << endl;



	return 0;
}