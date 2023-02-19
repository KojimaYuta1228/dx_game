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
	void PlayerInput(float delta_time);
	void Render(float delta_time)override;
	float CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)override;

	std::shared_ptr<Map> map_ = nullptr;

	//map�̍��W
	int maze_pos_x_ = 0 ;
	int maze_pos_z_ = 0;

	int player_hp_cnt = 3;
	//�t���O
	bool frag_input_ = true;
	bool frag_move_posY_ = true;
	bool frag_play_se_ = true;
	bool frag_tp = true;
	bool frag_chant_tp = true;
	bool frag_tp_start = true;
	bool frag_tp_else = true;
	bool frag_cnt_tp = true;

	float cnt_preparation_time = 2;
	float cnt_frag_tp = 5;
	float cnt_chant_tp = 0;

	int anim_pos_;
	int teleportation_cnt = 3;

	tnl::Vector3 move_v;
	tnl::Vector3 start_pos_;
	float move_speed = 1.1;
	
	int staminum = 350;
	int max_staminum = 350;
    
	int emp_stam_ber = 0;

	int bar_width = 350; // �o�[�̏�����
	int bar_height = 20; // �o�[�̍���
	int bar_x = 0; // �o�[��X���W
	int bar_y = 100; // �o�[��Y���W
	int decrease_amount = 2; // ������
	int increase_amount = 1; // ������
};