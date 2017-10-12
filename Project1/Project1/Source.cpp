#include "BehandlData.h"
#include "Besked.h"
#include "DTMF.h"
#include <iostream>
#include "DTMFtone.h"

int main()
{
	DTMFtone tone(697., 1209.);
	tone.play(4);

	return 0;
}