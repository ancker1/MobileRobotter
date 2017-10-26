#include "SFMLtone.h"

SFMLtone::SFMLtone() {}

SFMLtone::SFMLtone(double f1, double f2) {
	this->f1 = f1;
	this->f2 = f2;
	setFrequencies(f1, f2);
}

void SFMLtone::setFrequencies(double f1, double f2) {
	double x1n = 0.;
	double x2n = 0.;
	for (int n = 0; n < SAMPLES; n++) {
		x[n] = AMPLITUDE * (sin(2 * PI * x1n) + sin(2 * PI * x2n));
		x1n += f1 / SAMPLE_RATE;
		x2n += f2 / SAMPLE_RATE;
	}

	Buffer.loadFromSamples(x, SAMPLES, 1, SAMPLE_RATE);
	Sound.setBuffer(Buffer);
	Sound.setLoop(true);
}

void SFMLtone::play(int seconds) {
	int time = 1000; //kan ændre på 'time' for at indstille 'wait-time'
	Sound.play();
	for (int i = 0; i < seconds; i++) {
		sf::sleep(sf::milliseconds(time)); 
	}
	Sound.stop();
}

SFMLtone::~SFMLtone()
{
}
