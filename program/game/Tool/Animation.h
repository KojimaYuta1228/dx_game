#pragma once
#include<string>
#include"../../dxlib_ext/dxlib_ext.h"

class Animation
{
public:
	Animation(std::string ghPass, int sumNum, int widthNum, int heightNum, int width, int height, float x, float y);
	~Animation();

	//�A�j���[�V�����̍X�V�֐�
	bool UpdateAnimation(const float deltatime);
	//�A�j���[�V�����̕`��֐�
	void DrawAnimation(const float deltatime);

	//�摜�̑�����
	int sumAnimNum = 0;

	//�����Ă������݂̃^�C�}�[
	float gfx_timer = 0;

	//�`�撆�̔z��ԍ�

	int anim_frame = 0;

	//�摜�n���h���z��
	int gh[10] = {};

	//Vector�R(���W���g���Ƃ�)��std::Vector(�z��̑傫�����킩��Ȃ��Ƃ�)�͈Ⴄ
	tnl::Vector3 drawPos = {};

	//�����t���O
	bool isLive = true;
private:

};



