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
		GET_ITEM,
		SELECT_ITEM,
		DECISION_ITEM,
		SPEED_UP,
		SPEED_DOWN,
		STRONG_TIME,
		USE_KEY,
		USE_COIN,
		CHARGE,
		TELEPORT,
		MAX
	};
	static SoundManager* instance_;
	//SoundManager(BGM scene_id);
	SoundManager();
	~SoundManager();
	//インスタンスを取得
	static SoundManager* GetInstance();
	//破棄
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
	int se_get_item = 0;
	int se_select_item = 0;
	int se_decision_item = 0;
	int se_speed_up = 0;
	int se_speed_down = 0;
	int se_strong_time = 0;
	int se_use_key = 0;
	int se_use_coin = 0;
	int se_charge_skill = 0;
	int se_teleport = 0;

	//今流れているBGM
	int nowPlayBGM = 0;

	bool soundHd1 = false;
	void LoadSound();
	//void SoundPlay(BGM scene_id, SE SE_Id,int type=0);
	void SoundBgm(BGM num);
	void SoundSe(SE num);
	void StopBgm();
};
