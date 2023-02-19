#include "gm_soundmanager.h"

SoundManager* SoundManager::instance_ = nullptr;
SoundManager::SoundManager()
{	
	LoadSound();	
}

SoundManager::~SoundManager()
{

}

SoundManager* SoundManager::GetInstance()
{
	if (!instance_) {
		instance_ = new SoundManager();
	}
	return instance_;
}

void SoundManager::Destory()
{
	if (instance_) {
		delete instance_;
		instance_ = nullptr;
	}
}

void SoundManager::LoadSound()
{
	bgm_title = LoadSoundMem("sound/bgm/title.mp3");
	bgm_play = LoadSoundMem("sound/bgm/play.mp3");
	bgm_result = LoadSoundMem("sound/bgm/result.mp3");
	bgm_gameover = LoadSoundMem("sound/bgm/gameover.mp3");

	bgm.emplace_back(bgm_title);
	bgm.emplace_back(bgm_play);
	bgm.emplace_back(bgm_result);
	bgm.emplace_back(bgm_gameover);

	se_press_space = LoadSoundMem("sound/se/press_space.mp3");
	se_get_start = LoadSoundMem("sound/se/get_start.mp3");
	se_get_goal = LoadSoundMem("sound/se/get_goal.mp3");
	se_player_walk = LoadSoundMem("sound/se/player_walk.mp3");
	se_insect = LoadSoundMem("sound/se/insect.mp3");
	se_scream = LoadSoundMem("sound/se/scream.mp3");
	se_enemy_ghost = LoadSoundMem("sound/se/enemy_ghost.mp3");
	se_enemy_laugh = LoadSoundMem("sound/se/enemy_laugh.mp3");
	se_get_item = LoadSoundMem("sound/se/get_item.mp3");
	se_select_item = LoadSoundMem("sound/se/select_item.mp3");
	se_decision_item = LoadSoundMem("sound/se/decision_item.mp3");
	se_speed_up = LoadSoundMem("sound/se/speed_up.mp3");
	se_speed_down = LoadSoundMem("sound/se/speed_down.mp3");
	se_strong_time = LoadSoundMem("sound/se/strong_time.mp3");
	se_use_key = LoadSoundMem("sound/se/key_open.mp3");
	se_use_coin = LoadSoundMem("sound/se/coin.mp3");
	
	se.emplace_back(se_press_space);
	se.emplace_back(se_get_start);
	se.emplace_back(se_get_goal);
	se.emplace_back(se_player_walk);
	se.emplace_back(se_insect);
	se.emplace_back(se_scream);
	se.emplace_back(se_enemy_ghost);
	se.emplace_back(se_enemy_laugh);
	se.emplace_back(se_get_item);
	se.emplace_back(se_select_item);
	se.emplace_back(se_decision_item);
	se.emplace_back(se_speed_up);
	se.emplace_back(se_speed_down);
	se.emplace_back(se_strong_time);
	se.emplace_back(se_use_key);
	se.emplace_back(se_use_coin);
}


void SoundManager::SoundBgm(BGM num)
{
	if (bgm[static_cast<uint32_t>(num)] == nowPlayBGM)return;
	PlaySoundMem(bgm[static_cast<uint32_t>(num)], DX_PLAYTYPE_LOOP);
	nowPlayBGM = bgm[static_cast<uint32_t>(num)];
}

void SoundManager::SoundSe(SE num)
{
	//SoundPlay()
	PlaySoundMem(se[static_cast<uint32_t>(num)], DX_PLAYTYPE_BACK);
}

void SoundManager::StopBgm()
{
	int buf = StopSoundMem(nowPlayBGM);
	nowPlayBGM = 0;
	if (buf == -1) {
		int hoge = 0;
	}
}
