#pragma once
#include<vector>
#include"../../dxlib_ext/dxlib_ext.h"
class SoundManager {
public:
	enum class BGM :uint32_t {
		TITLE,
		PLAY,
		RESULT,
		GAMEOVER,
		MAX
	};
	enum class SE :uint32_t {
		PRESS_SPACE,
		GET_START,
		GET_GOAL,
		PLAYER_WALK,
		SE_INSECT,
		SE_SCREAM,
		ENEMY_LAUGH,
		ENEMY_GHOST,
		MAX
	};
	static SoundManager* instance_;
	//SoundManager(BGM scene_id);
	SoundManager();
	~SoundManager();
	//�C���X�^���X���擾
	static SoundManager* GetInstance();
	//�j��
	static void Destory();
	std::vector<int>bgm;
	std::vector<int>se;

	//BGM
	int bgm_title = 0;
	int bgm_play = 0;
	int bgm_result = 0;
	int bgm_gameover = 0;

	//SE
	int se_press_space = 0;
	int se_get_start = 0;
	int se_get_goal = 0;
	int se_enemy_laugh = 0;
	int se_enemy_ghost = 0;
	int se_player_walk = 0;
	int se_scream = 0;
	int se_insect = 0;

	//������Ă���BGM
	int nowPlayBGM = 0;

	bool soundHd1 = false;
	void LoadSound();
	//void SoundPlay(BGM scene_id, SE SE_Id,int type=0);
	void SoundBgm(BGM num);
	void SoundSe(SE num);
	void StopBgm();
};
//SoundManager::BGM::TITLE