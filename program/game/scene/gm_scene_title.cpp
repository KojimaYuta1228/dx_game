#include "../gm_manager.h"
#include "../Tool/gm_soundmanager.h"
#include "gm_scene_title.h"
#include "gm_scene_play.h"
#include"gm_scene_explain.h"



SceneTitle::SceneTitle()
{
	
}

SceneTitle::~SceneTitle()
{	
	SoundManager::GetInstance()->SoundSe(SoundManager::SE::SE_INSECT);
}

void SceneTitle::initialzie()
{
	font_path = "graphics/Resouce/font/doc/g_comichorrorR_freeR.ttf";
	playsound();
	titleImage = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/maintitle.png");
}


void SceneTitle::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();
	

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)&& arrow_pos_ == screenMidleY + 20) {
		timer_frag = false;
		change_title_frag = false;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)&& arrow_pos_ == screenMidleY +70) {
		timer_frag = false;
		change_explain_frag = false;	
	}
	
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_S) && cnt_pos == 0) {
		arrow_pos_ += 50;
		cnt_pos++;
	}else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_S) && cnt_pos == 1) {
		arrow_pos_ -= 50;
		cnt_pos--;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_W) && cnt_pos == 1) {
		arrow_pos_ -= 50;
		cnt_pos--;
	}else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_W) && cnt_pos == 0) {
		arrow_pos_ += 50;
		cnt_pos++;
	}
	
	

	if (timer_frag == false) {
		cnt_timer -= delta_time;
		if (cnt_timer % 7 == 1 || cnt_timer % 5 == 1 || cnt_timer % 3 == 1 || cnt_timer % 1 == 1) {
			if(change_title_frag == false)string_enter_frag = false;
			if(change_explain_frag == false)string_space_frag = false;
		}else {
			string_enter_frag = true;
			string_space_frag = true;
		}
	}
	if (cnt_timer <= 0 && change_title_frag == false) {
		change_title_frag = true;
		mgr->chengeScene(new ScenePlay());
	}
	if (cnt_timer <= 0 && change_explain_frag == false) {
		change_explain_frag == true;
		mgr->chengeScene(new SceneExplain());
	}
	textCol ++ ;
	arrowCol += 5;
	
}
void SceneTitle::render()
{
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}
	
	ChangeFont("g_コミックホラー恐怖-教漢", DX_CHARSET_DEFAULT);
	SetFontSize(100);
	DrawRotaGraph(screenMidleX, screenMidleY-100, 1.7, 0, titleImage, true);
	DrawStringEx(screenMidleX-300, screenMidleY-200, -1.0, "Maze In Abys");
	DrawStringEx(screenMidleX + 310, screenMidleY-200, GetColor(127+ 127*sin(tnl::ToRadian(textCol)),127+ 127 * sin(tnl::ToRadian(textCol)),127+ 127 * sin(tnl::ToRadian(textCol))), "s");

	SetFontSize(30);
	if (string_enter_frag == true) {
		DrawStringEx(screenMidleX -70 , screenMidleY +20, -1.0, " Start");
	}
	if (string_space_frag == true) {
		DrawStringEx(screenMidleX  -70, screenMidleY + 70,-1.0, " Explain");
	}
	DrawStringEx(screenMidleX - 90, arrow_pos_, GetColor(127 + 127 * sin(tnl::ToRadian(arrowCol)), 127 + 127 * sin(tnl::ToRadian(arrowCol)), 127 + 127 * sin(tnl::ToRadian(arrowCol))), "→");
	SetFontSize(50);
	DrawStringEx(screenMidleX -180, screenMidleY + 200, -1.0, "Press to Enter");
	
}

void SceneTitle::playsound()
{	
	SoundManager::GetInstance()->SoundBgm(SoundManager::BGM::TITLE);
}

