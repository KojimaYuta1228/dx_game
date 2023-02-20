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
	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
	void playsound()override;//BGM
	void Collision();//�����蔻��S��
	void PlayerState(float delta_time);//Player�̏󋵂ɉ���������
	void ScenePlaySound(float delta_time);//�X�e�[�W���œK�x�ɂȂ炵����SE�Ȃ�
	inline void RenderSort();//draw_character_���\�[�g���A�J�������牓�����ɕ`�悷�邽�߂̊֐�

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
	//Enemy��Player��Character�����N���X�Ƃ��Čp��
	//���N���X��f�ɃJ��������̂��ꂼ���sprite���v�Z
	//List�ɒǉ����ă\�[�g����������`��	
	std::list< std::shared_ptr<CharacterBase>> draw_character_;
	std::list<dxe::Mesh*> map_chip_list_;//�}�b�v�̏������Ƃ�Mesh�Ƃ���Render���邽�߂�List	

	const int SCREEN_MIDLE_X = DXE_WINDOW_WIDTH / 2;//��ʂ̒��SX
	const int SCREEN_MIDLE_Y = DXE_WINDOW_HEIGHT / 2;//��ʂ̒��SY
	const float BOX_SIZE = 50;//box��1�ӂ̑傫��
	
	bool frag_cnt_timer_player_ = true;//cnt_timer_player_��ύX����ۂ̃t���O
	bool frag_cnt_timer_ = true;//cnt_timer_player_��ύX����ۂ̃t���O
	bool frag_can_goal = true;//�����g�p�������ǂ������ʂ��邽�߂̃t���O
	bool frag_strong_time = true;//cnt_strong_time_��ύX����ۂ̃t���O

	//draw_character_�Ń\�[�g�����ёւ���Ƃ��Ɏg���v�Z�p�̕ϐ�
	float calc_A_ = 0;
	float calc_B_ = 0;
	float calc_C_ = 0;
	
	int cnt_timer_player_ = 100;//player���S�[������pos_.y�𓮂����Ƃ��Ɏg���J�E���g
	float cnt_play_se_ghost_ = 0;//se_ghost��炷�ۂɎg���J�E���g
	float cnt_play_se_laugh_ = 0;//se_laugh��炷�ۂɎg���J�E���g
	float cnt_strong_time_ = 3;//���G����

	

};


