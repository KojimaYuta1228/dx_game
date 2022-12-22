#include "Animation.h"

Animation::Animation(std::string ghPass, int sumNum, int widthNum, int heightNum, int width, int height, float x, float y)
{
	LoadDivGraph(ghPass.c_str(), sumNum, widthNum, heightNum, width, height, gh);
	sumAnimNum = sumNum;

	drawPos.x = x;
	drawPos.y = y;
}

Animation::~Animation()
{
}

bool Animation::UpdateAnimation(const float deltatime)
{

	if (anim_frame == (sumAnimNum - 1)) {
		//�Ō�̂P�񂾂�
		isLive = false;
		return true;
	}

	gfx_timer += deltatime;

	if (gfx_timer > 0.1f) {
		gfx_timer = 0;
		//�z��𓥂݊O���Ȃ��悤�Ɂi�ی��j
		anim_frame = (anim_frame + 1) % sumAnimNum;
	}
	return false;
}

void Animation::DrawAnimation(const float deltatime)
{
	if (!isLive)return;
	DrawRotaGraph(drawPos.x, drawPos.y, 1.0f, 0, gh[anim_frame], true);
}
