#include "../gm_manager.h"
#include "../Tool/gm_soundmanager.h"
#include "gm_scene_title.h"
#include "gm_scene_play.h"
#include"gm_scene_explain.h"
#include"gm_scene_gacha.h"



SceneTitle::SceneTitle()
{
	
}

SceneTitle::~SceneTitle()
{	
	SoundManager::GetInstance()->SoundSe(SoundManager::SE::SE_INSECT);
}

void SceneTitle::initialzie()
{
//	font_path = "graphics/Resouce/font/doc/g_comichorrorR_freeR.ttf";
	playsound();
	img_title_ = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/maintitle.png");
}


void SceneTitle::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();
	/*-------------------------------------------PAD--------------------------------------------*/
	//ここで言うところのB=KEY_1,X=KEY_2
	if (tnl::Input::IsPadDownTrigger(ePad::KEY_1) && pos_arrow_ == screenMidleY + 20) {
		frag_cnt_timer_ = false;
		frag_move_title_ = false;
	}
	if (tnl::Input::IsPadDownTrigger(ePad::KEY_1) && pos_arrow_ == screenMidleY + 70) {
		frag_cnt_timer_ = false;
		frag_change_explain_ = false;
	}
	if (tnl::Input::IsPadDownTrigger(ePad::KEY_DOWN) && cnt_pos_ == 0) {
		pos_arrow_ += 50;
		cnt_pos_++;
	}
	else if (tnl::Input::IsPadDownTrigger(ePad::KEY_DOWN) && cnt_pos_ == 1) {
		pos_arrow_ -= 50;
		cnt_pos_--;
	}
	if (tnl::Input::IsPadDownTrigger(ePad::KEY_UP) && cnt_pos_ == 1) {
		pos_arrow_ -= 50;
		cnt_pos_--;
	}
	else if (tnl::Input::IsPadDownTrigger(ePad::KEY_UP) && cnt_pos_ == 0) {
		pos_arrow_ += 50;
		cnt_pos_++;
	}
	/*********************************************************************************************/
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)&& pos_arrow_ == screenMidleY + 20) {
		frag_cnt_timer_ = false;
		frag_move_title_ = false;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)&& pos_arrow_ == screenMidleY +70) {
		frag_cnt_timer_ = false;
		frag_change_explain_ = false;	
	}
	
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_S) && cnt_pos_ == 0) {
		pos_arrow_ += 50;
		cnt_pos_++;
	}else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_S) && cnt_pos_ == 1) {
		pos_arrow_ -= 50;
		cnt_pos_--;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_W) && cnt_pos_ == 1) {
		pos_arrow_ -= 50;
		cnt_pos_--;
	}else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_W) && cnt_pos_ == 0) {
		pos_arrow_ += 50;
		cnt_pos_++;
	}
	
	

	if (frag_cnt_timer_ == false) {
		cnt_timer_move_scene_ -= delta_time;
		if (cnt_timer_move_scene_ % 7 == 1 || cnt_timer_move_scene_ % 5 == 1 || cnt_timer_move_scene_ % 3 == 1 || cnt_timer_move_scene_ % 1 == 1) {
			if(frag_move_title_ == false)frag_draw_enter_ = false;
			if(frag_change_explain_ == false)frag_draw_space_ = false;
		}else {
			frag_draw_enter_ = true;
			frag_draw_space_ = true;
		}
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_0)) {
		mgr->chengeScene(new SceneGacha());
	}
	if (cnt_timer_move_scene_ <= 0 && frag_move_title_ == false) {
		frag_move_title_ = true;
		mgr->chengeScene(new ScenePlay());
	}
	if (cnt_timer_move_scene_ <= 0 && frag_change_explain_ == false) {
		frag_change_explain_ == true;
		mgr->chengeScene(new SceneExplain());
	}
	col_txt_ ++ ;
	col_arrow_ += 5;
	
}
void SceneTitle::render()
{
	
	SetFontSize(100);
	DrawRotaGraph(screenMidleX, screenMidleY-100, 1.7, 0, img_title_, true);
	DrawStringEx(screenMidleX-300, screenMidleY-200, -1.0, "Maze In Abys");
	DrawStringEx(screenMidleX + 310, screenMidleY-200, GetColor(127+ 127*sin(tnl::ToRadian(col_txt_)),127+ 127 * sin(tnl::ToRadian(col_txt_)),127+ 127 * sin(tnl::ToRadian(col_txt_))), "s");

	SetFontSize(30);
	if (frag_draw_enter_ == true) {
		DrawStringEx(screenMidleX -70 , screenMidleY +20, -1.0, " Start");
	}
	if (frag_draw_space_ == true) {
		DrawStringEx(screenMidleX  -70, screenMidleY + 70,-1.0, " Explain");
	}
	DrawStringEx(screenMidleX - 90, pos_arrow_, GetColor(127 + 127 * sin(tnl::ToRadian(col_arrow_)), 127 + 127 * sin(tnl::ToRadian(col_arrow_)), 127 + 127 * sin(tnl::ToRadian(col_arrow_))), "→");
	SetFontSize(50);
	DrawStringEx(screenMidleX -180, screenMidleY + 200, -1.0, "Press to B button");
	
}

void SceneTitle::playsound()
{	
	SoundManager::GetInstance()->SoundBgm(SoundManager::BGM::TITLE);
}

