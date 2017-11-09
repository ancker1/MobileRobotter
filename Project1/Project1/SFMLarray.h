#pragma once
#include <SFML\Audio.hpp>
#include <vector>

using std::vector;

class SFMLarray
{
public:
	SFMLarray();

	void addTone(double, double);
	void readySound();
	void play();

	~SFMLarray();

private:
	const unsigned SAMPLE_RATE = 44100;
	const unsigned AMPLITUDE = 1000;
	const double PI = 3.14159;
	const unsigned SAMPLES_PER_TONE = 11025;
	const unsigned PAUSE_SAMPLES = 0;

	unsigned n;
	vector<sf::Int16> x;
	sf::SoundBuffer buffer;
	sf::Sound sound;
};

