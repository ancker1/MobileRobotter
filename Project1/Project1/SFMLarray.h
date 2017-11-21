#pragma once
#include <SFML\Audio.hpp>
#include <vector>

using std::vector;

class SFMLarray
{
public:
	SFMLarray();

	void addFirstTone();
	void addTone(double, double);
	void readySound();
	void play();
	void reset();

	~SFMLarray();

private:
	const unsigned SAMPLE_RATE = 44100;
	const unsigned AMPLITUDE = 7500;
	const double PI = 3.14159;
	const unsigned SAMPLES_PER_TONE = 2205;
	const unsigned FIRST_PAUSE = 44100;
	const unsigned PAUSE_SAMPLES = 50;

	unsigned n;
	vector<sf::Int16> x;
	sf::SoundBuffer buffer;
	sf::Sound sound;
};

