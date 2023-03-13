#pragma once
#include<vector>
#include<memory>
#include"CharacterBase.h"
#include "../../dxlib_ext/dxlib_ext.h"


class CharacterBase;
class ScenePlay;
class Map;
class Node;

class Enemy : public CharacterBase{
public:
	Enemy(tnl::Vector3& startEnPos);
	~Enemy();	

	void initialzie() override;
	void Update(float delta_time)override;
	void Render(float delta_time)override;
	float CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)override;
	void SetAster(float delta_time);//Aster�ɑg�ݍ���
	void SetPos(tnl::Vector3& startEnPos);
	void EnemyMove();
	void SetSprite()override;
	std::shared_ptr<Map> map_ = nullptr;

	
private:
	float search_time_count_ = 0;//Aster�̍X�V�p�x
	tnl::Vector3 move_target_pos_;//�^�[�Q�b�g��pos
	std::vector<Node*> route_player_;//player�̒ʂ�����
	int sx;//���[���h���W�ł̃X�^�[�gx
	int sy;//���[���h���W�ł̃X�^�[�gy
	int gx;//���[���h���W�ł̃S�[��x
	int gy;//���[���h���W�ł̃S�[��y
	float aster_interval = 0.5;
	float ready_enemy = 0;
	float start_enemy = 3.0;
	float x;//�������WX
	float z;//�������WZ
	bool is_success;//aster�̐������ǂ����̔���
	tnl::Vector3 move_n;
		
};