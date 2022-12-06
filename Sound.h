#pragma once
#include "pch.h"
#include <fmod.h>

class Sound {
public:
	enum class SoundType{BGM, START_UP, ACCELRATION, COLLISION};
	enum{SOUND_COUNT = 1,EFFECT_COUNT = 3,CHANNEL_COUNT = 4};
private:
	static Sound* pInst;
	FMOD_SYSTEM* soundSystem;
	FMOD_SOUND* bgmSound;
	FMOD_SOUND* effectSound[EFFECT_COUNT];
	FMOD_CHANNEL* channel[CHANNEL_COUNT];
private:
	Sound();
public:
	void initialize();
	
	void play(SoundType type);

	static Sound* getInstance();
};