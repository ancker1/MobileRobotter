#pragma once
#include <SFML\Audio.hpp>
#include <iostream>

class DTMFtone
{
public:
	DTMFtone(double, double);

	void play(int);

	~DTMFtone();
protected:
	const unsigned SAMPLE_RATE = 44100;
	const unsigned SAMPLES = 44100;
	const unsigned AMPLITUDE = 1000;
	const double PI = 3.14159;

	double f1;
	double f2;
	sf::Int16 x[44100];
	sf::SoundBuffer Buffer;
	sf::Sound Sound;
};

