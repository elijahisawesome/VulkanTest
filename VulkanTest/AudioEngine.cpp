#include "soloud.h"
#include "AudioEngine.h"
#include "soloud_speech.h"
#include "soloud_thread.h"
#include "soloud_wav.h"
#include "soloud_noise.h"
#include "soloud_biquadresonantfilter.h"
#include <iostream>
#include <string>
#include <math.h>


AudioEngine::AudioEngine() {
	soloud.init();
	chime.load("C:/Users/chees/source/repos/VulkanTest/VulkanTest/Resources/Audio/Ambient/chime.wav");
	tireThump.load("C:/Users/chees/source/repos/VulkanTest/VulkanTest/Resources/Audio/Ambient/tireThump.wav");
	ambientWind.load("C:/Users/chees/source/repos/VulkanTest/VulkanTest/Resources/Audio/Ambient/windAmbient.wav");
	Music.load("C:/Users/chees/source/repos/VulkanTest/VulkanTest/Resources/Audio/Music/Vanishes.wav");
	setRoadNoise();
}
void AudioEngine::setRoadNoise() {
	//setup filters
	roadFilter.setParams(SoLoud::BiquadResonantFilter::LOWPASS, 400, 3);
	roadFilter2.setParams(SoLoud::BiquadResonantFilter::LOWPASS, 1000, 3);
	roadFilter3.setParams(SoLoud::BiquadResonantFilter::LOWPASS, 2000, 3);
	delayFilter.setParams(.2, .93);

	roadNoise.setType(SoLoud::Noise::BROWNISH);
	roadNoise.setVolume(.3f);
	roadNoise.setFilter(0,&roadFilter);




	ambientWind.mChannels=2;
	ambientWind.setFilter(0, &delayFilter);
	ambientWind.setFilter(1, &roadFilter2);
	ambientWind.setVolume(.2);
	ambientWind.setLooping(true);

	Music.setVolume(musicLevel);
	Music.setFilter(0,&roadFilter3);

	soloud.play(roadNoise);
	soloud.play(ambientWind);
	int m =soloud.play(Music);

	soloud.fadeVolume(m, .5, 10);

}


void AudioEngine::play() {
	if (soloud.getActiveVoiceCount() > 3) {
		return;
	}


	chimeHandle = soloud.play(chime);

	float rate = soloud.getSamplerate(chimeHandle);
	soloud.setSamplerate(chimeHandle, (rate*soundTriggerRandomTimer()));
	
}
void AudioEngine::enqueue(std::string file) {
	
}
void AudioEngine::destroy() {
	// Clean up SoLoud
	soloud.deinit();
}

//TODO actually use this
float AudioEngine::soundTriggerRandomTimer() {
	float num = .7;
	std::srand(std::time(0));
	float randomValue = std::rand()%10 * .05;
	num+=randomValue;
	std::cout << randomValue;
	return num;
}