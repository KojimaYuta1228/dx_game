#pragma once
#include<vector>
#include<memory>
#include "../../dxlib_ext/dxlib_ext.h"
#include"CharacterBase.h"

class ScenePlay;
class Map;
class CharacterBase;

class Player :public CharacterBase{
public :
	Player(tnl::Vector3& startPos);
	~Player();

	

	//tnl::Vector3 prev_pos_;		// 前回座標
	//tnl::Vector3 pos_;	// 当たり判定用の座標

	void initialzie() override;

	void Update(float delta_time)override;
	void Render()override;

	float CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)override;

	float player_hp_ = 100;//プレイヤーのHP

	float player_exp_ = 0;//プレイヤーの経験値

	int player_lv_ = 1;//プレイヤーのLv
	std::shared_ptr<Map> map_ = nullptr;
	int maze_pos_x_ = 0 ;
	int maze_pos_z_ = 0;
	bool input_frag = true;
	bool move_posY_frag = true;
	bool play_se_frag = true;


};