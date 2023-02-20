#pragma once
#include<vector>
#include<memory>
#include "../../dxlib_ext/dxlib_ext.h"
#include"CharacterBase.h"

class ScenePlay;
class Map;
class CharacterBase;
class Animation;

class Player :public CharacterBase{
public :
	Player(tnl::Vector3& startPos, tnl::Vector3& teleportationPos);
	~Player();

	void initialzie() override;
	void Update(float delta_time)override;
	void PlayerAnim(float delta_time);//Player�̃A�j���[�V����
	void PlayerInput(float delta_time);//Player�̓���
	void Render(float delta_time)override;
	
	float CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)override;

	std::shared_ptr<Map> map_ = nullptr; 
	std::list<Animation*> liveAnim;
	Animation* i_anim_ = nullptr;

	//map�̍��W
	int maze_pos_x_ = 0 ;
	int maze_pos_z_ = 0;
	
	bool frag_input_ = true;//���͂��󂯕t���邩�ǂ����𔻒肷�邽�߂̃t���O
	bool frag_move_posY_ = true;//�S�[������Player�̓����������邽�߂̃t���O
	bool frag_play_se_ = true;//se��炷���߂̃t���O
	bool frag_tp = true;//TP���邽�߂̃t���O
	bool frag_chant_tp = true;//�r�����������ʂ��邽�߂̃t���O

	float cnt_frag_tp = 5;//���̉r���J�n�܂ł̎���
	float cnt_chant_tp = 0;//TP�܂ł̉r�����Ԃ悤�J�E���g

	
	tnl::Vector3 move_v;//���x�����Z���Z���邽�߂�Vector3
	tnl::Vector3 start_pos_;//�X�^�[�g�n�_
	tnl::Vector3 telePos;//�e���|�[�g�n�_
	float move_speed = 1.1;//�_�b�V�����x	
	int anim_pos_;//�A�j���X�v���C�g�̐ݒ�p
	int max_staminum = 350;//�X�^�~�i�ő�l
	int emp_stam_ber = 0;//�摜�n���h��
	int bar_width = 3500; // �o�[�̏�����
	int bar_height = 20; // �o�[�̍���
	int bar_x = 0; // �o�[��X���W
	int bar_y = 100; // �o�[��Y���W
	int decrease_amount = 2; // ������
	int increase_amount = 1; // ������
};