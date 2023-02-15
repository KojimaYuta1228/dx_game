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
	Player(tnl::Vector3& startPos, tnl::Vector3& teleportationPos);
	~Player();

	void initialzie() override;
	void Update(float delta_time)override;
	void PlayerAnim();
	void PlayerInput();
	void Render()override;
	float CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)override;

	std::shared_ptr<Map> map_ = nullptr;

	//mapÇÃç¿ïW
	int maze_pos_x_ = 0 ;
	int maze_pos_z_ = 0;

	int player_hp_cnt = 3;
	//ÉtÉâÉO
	bool frag_input_ = true;
	bool frag_move_posY_ = true;
	bool frag_play_se_ = true;

	int anim_pos_;
	int teleportation_cnt = 3;

	tnl::Vector3 move_v;
	tnl::Vector3 start_pos_;
};