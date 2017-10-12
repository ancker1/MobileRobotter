#include <stdio.h>
#include <math.h>
#include "portaudio.h"
#include "Besked.h"
#include "DTMF.h"
#include <iostream>

/*
* sine.c
*
* Demonstrates real-time audio output (sine wave)
*/

double PI = 3.14159265;
double FREQUENCY = 1477;
double LOW_FREQUENCY = 852;
int SAMPLE_RATE = 44100;
const int TABLE_SIZE = 44100;
double NUM_SECONDS = 0.4;
int FRAMES_PER_BUFFER = 256;

typedef struct _testData {
	float sine[TABLE_SIZE];
	int phase;
} TestData;


/* callback function prototype */
static int paCallback(const void *inputBuffer,
	void *outputBuffer, unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags, void *userData);

int main(void)
{

	/* user data */
	TestData data;

	PaStream *stream;
	PaStreamParameters outputParameters;
	PaError err;

	int i;
	double t;

	/* Generate table with sine values at given frequency */
	for (i = 0; i < TABLE_SIZE; i++) {
		t = (double)i / (double)SAMPLE_RATE;
		data.sine[i] = (0.5 * sin(2 * PI * FREQUENCY * t) + 0.5 * sin(2* PI * LOW_FREQUENCY * t));
	}

	/* Initialize user data */
	data.phase = 0;

	/* Initialize PortAudio */
	Pa_Initialize();

	/* Set output stream parameters */
	outputParameters.device = Pa_GetDefaultOutputDevice();
	outputParameters.channelCount = 2;
	outputParameters.sampleFormat = paFloat32;
	outputParameters.suggestedLatency =
	Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;

	/* Open audio stream */
	err = Pa_OpenStream(&stream, NULL /* no input */,
		&outputParameters,
		SAMPLE_RATE, FRAMES_PER_BUFFER, paNoFlag,
		paCallback, &data);

	if (err != paNoError) {
		printf("PortAudio error: open stream: %s\n", Pa_GetErrorText(err));
	}

	/* Start audio stream */
	err = Pa_StartStream(stream);
	if (err != paNoError) {
		printf("PortAudio error: start stream: %s\n", Pa_GetErrorText(err));
	}

	/*Sov i specificeret tid*/
	printf("Play for %d seconds.\n", NUM_SECONDS);
	Pa_Sleep(NUM_SECONDS * 1000);

	// test -----------------------------------------------------------------------------//|
	for (i = 0; i < TABLE_SIZE; i++) {													 //|
		t = (double)i / (double)SAMPLE_RATE;											 //|
		data.sine[i] = (0.5 * sin(2 * PI * 1209 * t) + 0.5 * sin(2 * PI * 852 * t));     //|
	}																					 //|
																						 //|
	/* Start audio stream */															 //|
	err = Pa_StartStream(stream);														 //|
	if (err != paNoError) {																 //|
		printf("PortAudio error: start stream: %s\n", Pa_GetErrorText(err));             //|
	}																					 //|
																						 //|
	/*Sov i specificeret tid*/															 //|
	printf("Play for %d seconds.\n", NUM_SECONDS);                                       //|
	Pa_Sleep(NUM_SECONDS * 1000);														 //|
	//test slut -------------------------------------------------------------------------//|

	/* Stop audio stream */
	if (err != paNoError) {
		printf("PortAudio error: stop stream: %s\n", Pa_GetErrorText(err));
	}
	/* Close audio stream */
	err = Pa_CloseStream(stream);
	if (err != paNoError) {
		printf("PortAudio error: close stream: %s\n", Pa_GetErrorText(err));
	}
	/* Terminate audio stream */
	err = Pa_Terminate();
	if (err != paNoError) {
		printf("PortAudio error: terminate: %s\n", Pa_GetErrorText(err));
	}

	return 0;
}


static int paCallback(const void *inputBuffer,
	void *outputBuffer, unsigned long framesPerBuffer,
	const PaStreamCallbackTimeInfo* timeInfo,
	PaStreamCallbackFlags statusFlags, void *userData)
{
	TestData *data = (TestData*)userData;
	float *out = (float*)outputBuffer;
	float sample;
	int i;

	for (i = 0; i < framesPerBuffer; i++) {
		sample = data->sine[data->phase++];
		*out++ = sample; /* left */
		*out++ = sample; /* right */
		if (data->phase >= TABLE_SIZE)
			data->phase -= TABLE_SIZE;
	}
	return paContinue;
}