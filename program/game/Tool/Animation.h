#pragma once
#include<string>
#include"../../dxlib_ext/dxlib_ext.h"

class Animation
{
public:
	Animation(std::string ghPass, int sumNum, int widthNum, int heightNum, int width, int height,int anim_type, float x, float y);
	~Animation();

	//�A�j���[�V�����̍X�V�֐�
	bool UpdateAnimation(const float deltatime);
	//�A�j���[�V�����̕`��֐�
	void DrawAnimation(const float deltatime);

	void UseAnim(float delta_time);

	//�摜�̑�����
	int sumAnimNum = 0;

	//�����Ă������݂̃^�C�}�[
	float gfx_timer = 0;

	//�`�撆�̔z��ԍ�

	int anim_frame = 0;

	//�摜�n���h���z��
	int gh[10] = {};

	float anim_time_count = 0;
	//int anim_frame = 0;
	int anim_type = 0;
	int gfx_hdl[10][10] = { 0 };

	//Vector�R(���W���g���Ƃ�)��std::Vector(�z��̑傫�����킩��Ȃ��Ƃ�)�͈Ⴄ
	tnl::Vector3 drawPos = {};

	//�����t���O
	bool isLive = true;
private:

};



