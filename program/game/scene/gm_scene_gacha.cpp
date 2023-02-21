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
}

SceneGacha::~SceneGacha()
{
}

void SceneGacha::initialzie()
{
}

void SceneGacha::update(float delta_time)
{
	gachagacha_->Update();
	if(tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		frag_tre_move = false;
		tim = false;
		

	}
	if(!tim){
		cnt_ ++;
	}
	if(cnt_ > 0.5){
		if(frag_up_down){
			cnt_img_tresure_box_y1 -= vy_;
			cnt_img_tresure_box_y2 -= vy_;
		}
 		else if(!frag_up_down){
			cnt_img_tresure_box_y1 += vy_;
			cnt_img_tresure_box_y2 += vy_;
		}
		if(frag_right_left){
			cnt_img_tresure_box_x1 -= vx_;
			cnt_img_tresure_box_x2 += vx_;
		}
		else if(!frag_right_left){
			cnt_img_tresure_box_x1 += vx_;
			cnt_img_tresure_box_x2 -= vx_;
		}
		if(cnt_img_tresure_box_y1 < 264){
			frag_right_left = false;
		}
		else if(cnt_img_tresure_box_y1 > 304){
			frag_right_left = true;
		}
		if(cnt_img_tresure_box_y1 < 250){
			frag_up_down = false;
		}
		else if(cnt_img_tresure_box_y1 > 350){
			cnt_bounce_++;
			frag_up_down = true;
		}
		if (cnt_bounce_ >= 3 && cnt_img_tresure_box_y1 <= 284) {
			tim = true;
		}
		cnt_ = 0;
}
	/*
	if (!frag_tre_move) {
		if (cnt_img_tresure_box_y1 <= 314 && frag_up_down) {
			cnt_img_tresure_box_y1 += vy_;
			cnt_img_tresure_box_y2 += vy_;
			frag_up_down = false;
		}
	    if (cnt_img_tresure_box_y1 > 314 && !frag_up_down) {
			 cnt_img_tresure_box_y1 -= vy_;
			 cnt_img_tresure_box_y2 -= vy_;
			 frag_up_down = true;
		}
			
	}*/
}

void SceneGacha::render()
{
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 0.7, 0, img_guild, true);
	DrawExtendGraph(cnt_img_tresure_box_x1, cnt_img_tresure_box_y1, cnt_img_tresure_box_x2, cnt_img_tresure_box_y2, img_tresure_box,true);
	//DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 0.7, 0, img_tresure_box, true);
	gachagacha_->GachaAnima(0.01666);
}

void SceneGacha::playsound()
{
}
