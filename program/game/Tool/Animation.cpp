#include "Animation.h"

Animation::Animation(std::string ghPass, int sumNum, int widthNum, int heightNum, int width, int height, int anim_type,float x, float y)
{
	LoadDivGraph(ghPass.c_str(), sumNum, widthNum, heightNum, width, height, gh);
	//LoadDivGraph(ghPass.c_str(), sumNum, widthNum, heightNum, width, height, &gh[anim_type]);
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
	//DrawRotaGraph(drawPos.x, drawPos.y, 1.0f, 0, gfx_hdl[anim_type][anim_frame], true);
	//DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 2.0f, 0, gfx_hdl[anim_type][anim_frame], true);
}

void Animation::UseAnim(float delta_time)
{
	anim_time_count += delta_time;
	if (0.25f < anim_time_count) {
		anim_time_count = 0;
		anim_frame++;
		anim_frame %= 10;
	}
}
