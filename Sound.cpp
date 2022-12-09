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
	FMOD_System_CreateSound(soundSystem, "Resources/Sound/select.mp3", FMOD_DEFAULT, 0, &effectSound[0]);
	FMOD_System_CreateSound(soundSystem, "Resources/Sound/accel.mp3", FMOD_DEFAULT, 0, &effectSound[1]);
	FMOD_System_CreateSound(soundSystem, "Resources/Sound/decel.mp3", FMOD_DEFAULT, 0, &effectSound[2]);
	FMOD_System_CreateSound(soundSystem, "Resources/Sound/collision.mp3", FMOD_DEFAULT, 0, &effectSound[3]);
}

void Sound::play(SoundType type)
{
	switch (type)
	{
	case Sound::SoundType::BGM:
	//	FMOD_System_PlaySound(soundSystem, bgmSound, NULL, 0, &channel[0]);
	//	FMOD_Channel_SetVolume(channel[0], 1);
		break;
	case Sound::SoundType::START_UP:
		FMOD_System_PlaySound(soundSystem, effectSound[0], NULL, 0, &channel[1]);
		FMOD_Channel_SetVolume(channel[1], 15);
		break;
	case Sound::SoundType::ACCELRATION:
		break;
	case Sound::SoundType::COLLISION:
		FMOD_System_PlaySound(soundSystem, effectSound[3], NULL, 0, &channel[3]);
		FMOD_Channel_SetVolume(channel[3], 15);
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
