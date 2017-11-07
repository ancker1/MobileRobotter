#pragma once
#include <SFML\Audio.hpp>
#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

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
	const unsigned PAUSE_SAMPLES = 44100;

	unsigned n;
	vector<sf::Int16> x;
	sf::SoundBuffer buffer;
	sf::Sound sound;
};

