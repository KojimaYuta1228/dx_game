#pragma once
#include "gm_scene_base.h"
#include "../gm_camera.h"
#include"../Tool/Map.h"
#include<vector>
#include<memory>
#include<iostream>
#include<list>

/*------クラス------*/
class GmCamera;
class Player;
class Enemy;
class CharacterBase;
class Map;
class Cell;
class Animation;
class ItemManager;



class ScenePlay : public SceneBase {
public:
	ScenePlay();
	~ScenePlay();
	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
	void playsound()override;//BGM
	void Collision();//当たり判定全般
	void PlayerState(float delta_time);//Playerの状況に応じた処理
	void ScenePlaySound(float delta_time);//ステージ内で適度にならしたいSEなど
	inline void RenderSort();//draw_character_をソートし、カメラから遠い順に描画するための関数

	GmCamera* camera_ = nullptr;
	GameManager* mgr = nullptr;	
	Animation* newAnim = nullptr;
	std::shared_ptr<Player> player_ = nullptr;
	std::shared_ptr<Enemy> enemy_ = nullptr;
	std::shared_ptr<Map> map_ = nullptr;
	std::shared_ptr<ItemManager> item_mgr = nullptr;
	dxe::Mesh* dome_ = nullptr;
	dxe::Mesh* floor_ = nullptr;
	dxe::Mesh* goal_ = nullptr;
	dxe::Mesh* sphare = nullptr;
	dxe::Mesh* map_chips_[Map::MEIRO_WIDTH][Map::MEIRO_HEIGHT];
	GmCamera* GetCamera();	
	//EnemyとPlayerにCharacterを基底クラスとして継承
	//基底クラスを素にカメラからのそれぞれのspriteを計算
	//Listに追加してソート遠い順から描画	
	std::list< std::shared_ptr<CharacterBase>> draw_character_;
	std::list<dxe::Mesh*> map_chip_list_;//マップの情報をもとにMeshとしてRenderするためのList	

	const int SCREEN_MIDLE_X = DXE_WINDOW_WIDTH / 2;//画面の中心X
	const int SCREEN_MIDLE_Y = DXE_WINDOW_HEIGHT / 2;//画面の中心Y
	const float BOX_SIZE = 50;//boxの1辺の大きさ
	
	bool frag_cnt_timer_player_ = true;//cnt_timer_player_を変更する際のフラグ
	bool frag_cnt_timer_ = true;//cnt_timer_player_を変更する際のフラグ
	bool frag_can_goal = true;//鍵を使用したかどうか判別するためのフラグ
	bool frag_strong_time = true;//cnt_strong_time_を変更する際のフラグ

	//draw_character_でソートし並び替えるときに使う計算用の変数
	float calc_A_ = 0;
	float calc_B_ = 0;
	float calc_C_ = 0;
	
	int cnt_timer_player_ = 100;//playerがゴール時にpos_.yを動かすときに使うカウント
	float cnt_play_se_ghost_ = 0;//se_ghostを鳴らす際に使うカウント
	float cnt_play_se_laugh_ = 0;//se_laughを鳴らす際に使うカウント
	float cnt_strong_time_ = 3;//無敵時間

	

};


