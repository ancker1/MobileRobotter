#include "BehandlData.h"
#include <math.h>


BehandlData::BehandlData()
{
}

float BehandlData::goertzelFilter(int numSamples, int TARGET_FREQUENCY, int SAMPLING_RATE, float* data)
{
	double M_PI = 3.14159265358979323846264338327950288;
	int     k, i;
	float   floatnumSamples;
	float   omega, sine, cosine, coeff, q0, q1, q2, magnitude, real, imag;

	float   scalingFactor = numSamples / 2.0;

	floatnumSamples = (float)numSamples;
	k = (int)(0.5 + ((floatnumSamples * TARGET_FREQUENCY) / SAMPLING_RATE));
	omega = (2.0 * M_PI * k) / floatnumSamples;
	sine = sin(omega);
	cosine = cos(omega);
	coeff = 2.0 * cosine;
	q0 = 0;
	q1 = 0;
	q2 = 0;

	for (i = 0; i<numSamples; i++)
	{
		q0 = coeff * q1 - q2 + data[i];
		q2 = q1;
		q1 = q0;
	}

	// calculate the real and imaginary results
	// scaling appropriately
	real = (q1 - q2 * cosine) / scalingFactor;
	imag = (q2 * sine) / scalingFactor;

	magnitude = sqrtf(real*real + imag*imag);
	return magnitude;
}

void BehandlData::hammingWindow(int numSamples, float* data)
{
double M_PI = 3.14159265358979323846264338327950288;
	for (int i = 0; i < numSamples; i++)
	{
		data[i] = data[i] * (0.54 - 0.46 * cos((2 * M_PI * i) / (numSamples - 1)));
	}
}


BehandlData::~BehandlData()
{
}
