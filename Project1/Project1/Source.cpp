#include "BehandlData.h"
#include "Besked.h"
#include "DTMF.h"
#include <iostream>

int main()
{
	char buttons[16] = {'1', '2', '3', 'A',
						'4', '5', '6', 'B',
						'7', '8', '9', 'C',
						'*', '0', '#', 'D' };

	for (int i = 0; i < sizeof(buttons); i++) {
		cout << "Playing " << buttons[i] << endl;
		DTMF tone(buttons[i]);
		tone.getTone().play(1);
	}

	return 0;
}