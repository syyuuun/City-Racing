#include "Sound.h"
Sound* Sound::pInst = nullptr;

Sound::Sound()
{
}

Sound::~Sound()
{
	release();	
}

void Sound::initialize()
{
	FMOD_System_Create(&soundSystem);
	FMOD_System_Init(soundSystem, CHANNEL_COUNT, FMOD_INIT_NORMAL, NULL);

	FMOD_System_CreateSound(soundSystem, "Resources/Sound/mainBGM.mp3", FMOD_LOOP_NORMAL, 0, &bgmSound);
	FMOD_System_CreateSound(soundSystem, "Resources/Sound/select.mp3", FMOD_DEFAULT, 0, &effectSound[0]);
	FMOD_System_CreateSound(soundSystem, "Resources/Sound/accel.mp3", FMOD_DEFAULT, 0, &effectSound[1]);
	FMOD_System_CreateSound(soundSystem, "Resources/Sound/decel.mp3", FMOD_DEFAULT, 0, &effectSound[2]);
	FMOD_System_CreateSound(soundSystem, "Resources/Sound/collision.mp3", FMOD_DEFAULT, 0, &effectSound[3]);
	FMOD_System_CreateSound(soundSystem, "Resources/Sound/jump.wav", FMOD_DEFAULT, 0, &effectSound[4]);
}

void Sound::release()
{
	FMOD_Sound_Release(bgmSound);
	for (int i = 0; i < EFFECT_COUNT; ++i) {
		FMOD_Sound_Release(effectSound[i]);
	}
	FMOD_System_Release(soundSystem);

	if (nullptr != pInst) {
		delete pInst;
		pInst = nullptr;
	}
}

void Sound::play(SoundType type)
{
	switch (type)
	{
	case Sound::SoundType::BGM:
		FMOD_System_PlaySound(soundSystem, bgmSound, NULL, FALSE, &channel[0]);
		FMOD_Channel_SetVolume(channel[0], 1);
		break;
	case Sound::SoundType::START_UP:
		FMOD_System_PlaySound(soundSystem, effectSound[0], NULL, FALSE, &channel[1]);
		FMOD_Channel_SetVolume(channel[1], 15);
		break;
	case Sound::SoundType::ACCELRATION:
		break;
	case Sound::SoundType::COLLISION:
		FMOD_System_PlaySound(soundSystem, effectSound[3], NULL, 0, &channel[3]);
		FMOD_Channel_SetVolume(channel[3], 15);
		break;
	case Sound::SoundType::JUMP:
		FMOD_System_PlaySound(soundSystem, effectSound[4], NULL, 0, &channel[4]);
		FMOD_Channel_SetVolume(channel[4], 15);
		break;
	default:
		break;
	}
}

Sound* Sound::getInstance()
{
	if (nullptr == pInst)
		pInst = new Sound;

	return pInst;
}
