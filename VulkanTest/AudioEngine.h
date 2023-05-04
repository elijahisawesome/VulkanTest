#ifndef AUDIOENGINE
#define AUDIOENGINE


#include "soloud.h"
#include "soloud_speech.h"
#include "soloud_wav.h"
#include "soloud_noise.h"
#include "soloud_biquadresonantfilter.h"
#include "soloud_echofilter.h"
#include <string>


class AudioEngine {
	private:
		SoLoud::Soloud soloud;  // SoLoud engine core
		SoLoud::Speech speech;  // A sound source (speech, in this case) 
		SoLoud::Wav chime;
		SoLoud::Wav tireThump;
		SoLoud::Wav ambientWind;
		SoLoud::Wav Music;
		SoLoud::Noise roadNoise;
		SoLoud::BiquadResonantFilter roadFilter;
		SoLoud::BiquadResonantFilter roadFilter2;
		SoLoud::BiquadResonantFilter roadFilter3;
		SoLoud::EchoFilter delayFilter;
		int chimeHandle = NULL;
		void setRoadNoise();
		float soundTriggerRandomTimer();
		float musicLevel = 0;
	public:
		AudioEngine();
		void play();
		void enqueue(std::string file);
		void destroy();
};

#endif