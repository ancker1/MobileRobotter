#include "BehandlData.h"
#include "Besked.h"
#include "DTMF.h"
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

	Besked test("Wubba dub a dub dub");
	test.playMessage();

	return 0;
}