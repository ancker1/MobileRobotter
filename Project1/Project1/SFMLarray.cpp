#include "SFMLarray.h"

SFMLarray::SFMLarray() {}

void SFMLarray::addTone(double f1, double f2) {
	double x1n = 0.;
	double x2n = 0.;

	for (unsigned n = 0; n < SAMPLE_RATE; n++) {
		x.push_back(AMPLITUDE * (sin(2 * PI * x1n) + sin(2 * PI * x2n)));
		x1n += f1 / SAMPLE_RATE;
		x2n += f2 / SAMPLE_RATE;
	}

	for (unsigned n = 0; n < PAUSE_SAMPLES; n++)
		x.push_back(0);
}

void SFMLarray::readySound() {
	for (unsigned n = 0; n < PAUSE_SAMPLES; n++)
		x.pop_back();

	buffer.loadFromSamples(x.data(), x.size(), 1, SAMPLE_RATE);
	sound.setBuffer(buffer);
}

void SFMLarray::play() {
	sound.play();
	for (unsigned i = 0; i < x.size() / 441; i++)
		sf::sleep(sf::milliseconds(10));
	sound.stop();
}

SFMLarray::~SFMLarray() {}