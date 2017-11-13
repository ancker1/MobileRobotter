#include "SFMLarray.h"

SFMLarray::SFMLarray() {
	addTone(941, 1633);
}

void SFMLarray::addTone(double f1, double f2) {
	double x1n = 0.;
	double x2n = 0.;

	for (unsigned n = 0; n < SAMPLES_PER_TONE; n++) {
		x.push_back(10000 * (sin(2 * PI * x1n) + sin(2 * PI * x2n)) * (0.5 * (1 - cos((2 * PI * n) / (SAMPLES_PER_TONE - 1)))));
		x1n += f1 / SAMPLE_RATE;
		x2n += f2 / SAMPLE_RATE;
	}

	if (SAMPLES_PER_TONE < x.size()) {
		for (unsigned n = 0; n < PAUSE_SAMPLES; n++)
			x.push_back(0);
	}
	else {
		for (unsigned n = 0; n < FIRST_PAUSE; n++)
			x.push_back(0);
	}
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