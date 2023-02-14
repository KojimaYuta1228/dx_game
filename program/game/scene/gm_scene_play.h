#pragma once
#include "gm_scene_base.h"
#include "../gm_camera.h"
#include"../Tool/Map.h"
#include<vector>
#include<memory>
#include<iostream>
#include<list>

/*------�N���X------*/
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

	GmCamera* camera_ = nullptr;
	GmCamera* GetCamera();
	
	std::shared_ptr<Player> player_ = nullptr;
	std::shared_ptr<Enemy> enemy_ = nullptr;
	std::shared_ptr<Map> map_ = nullptr;
	std::shared_ptr<ItemManager> item_mgr = nullptr;
	std::list<dxe::Mesh*> map_chip_list_;

	dxe::Mesh* map_chips_[Map::MEIRO_WIDTH][Map::MEIRO_HEIGHT];
	dxe::Mesh* dome_ = nullptr;
	dxe::Mesh* floor_ = nullptr;
	dxe::Mesh* goal_ = nullptr;
	dxe::Mesh* sphare = nullptr;
	

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
	void playsound()override;
	void Collision();
	void PlayerGoaled(float delta_time);
	
	

	const int screenMidleX = DXE_WINDOW_WIDTH / 2;
	const int screenMidleY = DXE_WINDOW_HEIGHT / 2;
	const float boxSize = 50;//box��1�ӂ̑傫��

	//�摜�n���h��
	int img_note = 0;
	//�t���O
	bool frag_cnt_timer_player_ = true;
	bool frag_cnt_timer_ = true;
	bool frag_move_result_ = true;
	bool frag_draw_note_ = true;
	bool frag_camera_rotate_ = true;
	//�v�Z�p
	float calc_A_ = 0;
	float calc_B_ = 0;
	float calc_C_ = 0;
	//�J�E���g
	int cnt_timer_player_ = 100;
	float cnt_play_se_ghost_ = 0;
	float cnt_play_se_laugh_ = 0;
	float cnt_camera_rotate_ = 0;

	float cam_rot_x = 1.0;
	
	
	//Enemy��Player��Character�����N���X�Ƃ��Čp��
	//���N���X��f�ɃJ��������̂��ꂼ���sprite���v�Z
	//List�ɒǉ����ă\�[�g����������`��	
	std::list< std::shared_ptr<CharacterBase>> draw_character_;//List�̌^�ϊ�
		
	inline void RenderSort();


};


