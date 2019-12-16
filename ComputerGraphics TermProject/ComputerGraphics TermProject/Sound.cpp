#include "Sound.h"


Fmod_snd::Fmod_snd()
{
	FMOD::System_Create(&pSystem);
	pSystem->init(
		CHANNEL_NUM
		, FMOD_INIT_NORMAL
		, nullptr
	);

	for (auto& p : pSound) p = nullptr;
	Add_sound();

	pChannel[(int)WHOSE_SOUND::BACK]->setVolume(0.5f);
}


Fmod_snd::~Fmod_snd()
{
	for (int i = 0; i < SOUND_NUM; ++i)
	{
		pSound[i]->release();
	}


	pSystem->release();
	pSystem->close();
}


void Fmod_snd::Add_sound()
{
	pSystem->createSound(
		"resource/sound/bomb.wav"
		, FMOD_DEFAULT | FMOD_LOOP_OFF
		, nullptr
		, &pSound[(int)WHAT_SOUND::BULLET_SOUND]
	);
	pSystem->createSound(
		"resource/sound/Spacious.mp3"
		, FMOD_LOOP_NORMAL | FMOD_2D
		, nullptr
		, &pSound[(int)WHAT_SOUND::TITLE_BGM]
	);

}

void Fmod_snd::Play_bgm(WHAT_SOUND type)
{
	bool bPlaying;
	pChannel[(int)WHOSE_SOUND::BACK]->isPlaying(&bPlaying);

	if (!bPlaying)
	{
		pSystem->update();
		pSystem->playSound(FMOD_CHANNEL_FREE, pSound[(int)type], false, &pChannel[(int)WHOSE_SOUND::BACK]);
	}
}

void Fmod_snd::Play_effect(WHAT_SOUND type, WHOSE_SOUND type2)
{
	//pSystem->update();
	pSystem->playSound(FMOD_CHANNEL_REUSE, pSound[(int)type]
		, false, &pChannel[(int)type2]);

}

void Fmod_snd::Stop_bgm(WHOSE_SOUND type)
{
	bool bPlaying;
	pChannel[(int)type]->isPlaying(&bPlaying);
	if (bPlaying)
		pChannel[(int)type]->stop();
}
