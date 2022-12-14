#pragma once
#include "pch.h"

class Sound {
public:
	enum class SoundType{BGM, START_UP, ACCELRATION, COLLISION, JUMP};
	enum{ EFFECT_COUNT = 10,CHANNEL_COUNT = 10};
private:
	static Sound* pInst;
	FMOD_SYSTEM* soundSystem;
	FMOD_SOUND* bgmSound;
	FMOD_SOUND* effectSound[EFFECT_COUNT];
	FMOD_CHANNEL* channel[CHANNEL_COUNT];
private:
	Sound();
public:
	~Sound();


	void initialize();

	void release();
	
	void play(SoundType type);

	static Sound* getInstance();
};