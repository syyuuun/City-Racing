#include "Sound.h"
Sound* Sound::pInst = nullptr;

Sound::Sound()
{

}

void Sound::initialize()
{
	FMOD_System_Create(&soundSystem);
	FMOD_System_Init(soundSystem, CHANNEL_COUNT, FMOD_INIT_NORMAL, NULL);

	FMOD_System_CreateSound(soundSystem, "Resources/Sound/bgm.mp3", FMOD_DEFAULT, 0, &bgmSound);
}

void Sound::play(SoundType type)
{
	switch (type)
	{
	case Sound::SoundType::BGM:
		FMOD_System_PlaySound(soundSystem, bgmSound, NULL, 0, &channel[0]);
		FMOD_Channel_SetVolume(channel[0], 15);
		break;
	case Sound::SoundType::START_UP:
		break;
	case Sound::SoundType::ACCELRATION:
		break;
	case Sound::SoundType::COLLISION:
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
