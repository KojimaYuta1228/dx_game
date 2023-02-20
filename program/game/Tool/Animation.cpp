#include "Animation.h"

Animation::Animation(std::string ghPass, int sumNum, int widthNum, int heightNum, int width, int height,float x, float y)
{
	LoadDivGraph(ghPass.c_str(), sumNum, widthNum, heightNum, width, height, gh);
	sumAnimNum = sumNum;
	drawPos.x = x;
	drawPos.y = y;
}

Animation::~Animation()
{
}

bool Animation::UpdateAnimation(const float delta_time)
{

	if (anim_frame == (sumAnimNum - 1)) {
		//最後の１回だけ
		isLive = false;
		return true;
	}
	gfx_timer += delta_time;
	if (gfx_timer > 0.1f) {
		gfx_timer = 0;
		//配列を踏み外さないように（保険）
		anim_frame = (anim_frame + 1) % sumAnimNum;
	}
	return false;
}

void Animation::DrawAnimation(const float delta_time)
{
	if (!isLive)return;
	DrawRotaGraph(drawPos.x, drawPos.y, 1.0f, 0, gh[anim_frame], true);
}

