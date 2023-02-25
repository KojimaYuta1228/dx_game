#include "../gm_manager.h"
#include "gm_scene_gacha.h"
#include "gm_scene_title.h"
#include"../Tool/Animation.h"
#include"../Tool/GachaItem.h"
#include "../Tool/gm_soundmanager.h"
#include "../Tool/GachaGacha.h"

SceneGacha::SceneGacha()
{
	gachagacha_ = std::make_shared<GachaGacha>();
	img_guild = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/guild.jpg");
	img_tresure_box = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/tresure_box.png");
	img_frash = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/frash.png");
}

SceneGacha::~SceneGacha()
{
}

void SceneGacha::initialzie()
{
}

void SceneGacha::update(float delta_time)
{
	gachagacha_->Update(delta_time);

	angle+=delta_time;

	if(tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE) && gachagacha_->frag_can_gacha == false) {
		frag_tre_move = false;
		tim = false;
		frag_down_arrow = false;
	}	
	if (!frag_tre_move) {
		cnt_draw_gacha_item += delta_time;
		cnt_next_tre += delta_time;
	}
	if (cnt_next_tre > 10) {
		frag_can_render_tresureBox = true;
		gachagacha_->frag_cnt_center_render = true;
		gachagacha_->frag_next_render = true;
		cnt_next_tre = 0;
	}
	if (cnt_draw_gacha_item > 6.5) {
		gachagacha_->frag_open_draw = false;
		frag_render_frash = false;
		cnt_draw_gacha_item = 0;
		cnt_img_tresure_box_x1 = 414;
		cnt_img_tresure_box_x2 = 614;
		cnt_img_tresure_box_y1 = 284;
		cnt_img_tresure_box_y2 = 484;
	}
	DrawAnim(delta_time);
	if(!frag_start_gacha_anim){
		gachagacha_->i_gacha_item_->WaitGacha(delta_time);
		frag_start_gacha_anim = true;
	}
}

void SceneGacha::render()
{
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 0.7, 0, img_guild, true);
	if(frag_can_render_tresureBox){
		DrawExtendGraph(cnt_img_tresure_box_x1, cnt_img_tresure_box_y1, cnt_img_tresure_box_x2, cnt_img_tresure_box_y2, img_tresure_box, true);
	}
	if(!frag_render_frash && gachagacha_->frag_next_render == false){
		DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 0.7, angle, img_frash, true); 
	}
	gachagacha_->Render();
	gachagacha_->GachaAnima(0.01666);
}

void SceneGacha::playsound()
{
}

void SceneGacha::DrawAnim(float delta_time)
{
	if (frag_down_arrow && cnt_arow < 5) {
		cnt_ar += delta_time;
		if (cnt_ar > 1.5) {
			gachagacha_->i_gacha_item_->DownArrow(delta_time);
			cnt_arow++;
			cnt_ar = 0;
		}
		if (cnt_arow > 3) {
			cnt_arow = 0;
		}
	}

	if (!tim) {
		cnt_++;
	}
	if (cnt_ > 0.5) {
		if (frag_up_down) {
			cnt_img_tresure_box_y1 -= vy_;
			cnt_img_tresure_box_y2 -= vy_;
		}
		else if (!frag_up_down) {
			cnt_img_tresure_box_y1 += vy_;
			cnt_img_tresure_box_y2 += vy_;
		}
		if (frag_right_left) {
			cnt_img_tresure_box_x1 -= vx_;
			cnt_img_tresure_box_x2 += vx_;
		}
		else if (!frag_right_left) {
			cnt_img_tresure_box_x1 += vx_;
			cnt_img_tresure_box_x2 -= vx_;
		}
		if (cnt_img_tresure_box_y1 < 264) {
			frag_right_left = false;
		}
		else if (cnt_img_tresure_box_y1 > 304) {
			frag_right_left = true;
		}
		if (cnt_img_tresure_box_y1 < 250) {
			frag_up_down = false;
		}
		else if (cnt_img_tresure_box_y1 > 350) {
			cnt_bounce_++;
			frag_up_down = true;
		}
		if (cnt_bounce_ >= 3 && cnt_img_tresure_box_y1 <= 284) {
			tim = true;
			frag_start_gacha_anim = false;
			frag_can_render_tresureBox = false;
		}
		cnt_ = 0;
	}
}
