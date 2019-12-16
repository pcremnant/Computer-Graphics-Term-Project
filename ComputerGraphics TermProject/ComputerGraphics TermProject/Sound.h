#include "FMOD\fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")
#define SOUND_NUM 5
#define CHANNEL_NUM 100

using namespace FMOD;
enum WHAT_SOUND{
	BULLET_SOUND,
	HIT_SOUND,
	DEATH_SOUND,
	TITLE_BGM
};

enum WHOSE_SOUND {
	BULLET,
	HIT,
	DEATH,
	BACK
};

class Fmod_snd
{
public:
	Fmod_snd();
	~Fmod_snd();

private:
	System * pSystem;
	Sound * pSound[SOUND_NUM];
	Channel * pChannel[CHANNEL_NUM];
	void Add_sound();

public:
	void Play_bgm(WHAT_SOUND type);
	void Play_effect(WHAT_SOUND type, WHOSE_SOUND type2);
	void Stop_bgm(WHOSE_SOUND type);
};

