#include "../Tool/gm_soundmanager.h"
#include "gm_scene_title.h"
#include "gm_scene_explain.h"
#include "../gm_manager.h"


SceneExplain::SceneExplain()
{	
	img_explain_ = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/item/explain.png");		
}

SceneExplain::~SceneExplain()
{
	SoundManager::GetInstance()->SoundSe(SoundManager::SE::SE_INSECT);
}

void SceneExplain::initialzie()
{
	playsound();
}

void SceneExplain::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();
	if (tnl::Input::IsPadDownTrigger(ePad::KEY_1)) {
		frag_cnt_timer_ = false;
		frag_move_title_ = false;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		frag_cnt_timer_ = false;
		frag_move_title_ = false;
	}
	if (frag_cnt_timer_ == false) {
		cnt_timer_player_ -= delta_time;
		if (cnt_timer_player_ % 7 == 1 || cnt_timer_player_ % 5 == 1 || cnt_timer_player_ % 3 == 1 || cnt_timer_player_ % 1 == 1) {
			if (frag_move_title_ == false)frag_draw_enter_ = false;
		}
		else {
			frag_draw_enter_ = true;
		}
	}
	if (cnt_timer_player_ <= 0 && frag_move_title_ == false) {
		frag_move_title_ = true;
		mgr->chengeScene(new SceneTitle());
	}
	chang_col_red_ ++;

}

void SceneExplain::render()
{
	DrawRotaGraph(screenMidleX, screenMidleY , 1.0, 0, img_explain_, true);
	SetFontSize(50);
	DrawStringEx(screenMidleX - 190 , screenMidleY - 350, 0, "``Explain``");
	SetFontSize(30);
	DrawStringEx(screenMidleX - 250, screenMidleY - 270, 0, "mission: Dive into the dungeon  ");
	DrawStringEx(screenMidleX - 40, screenMidleY - 240, 0, "and");
	DrawStringEx(screenMidleX - 150, screenMidleY - 210, 0, "get the treasure");
	DrawStringEx(screenMidleX - 220, screenMidleY - 170, 0, "reward: everything you want");SetFontSize(40);
	DrawStringEx(screenMidleX - 200, screenMidleY -50  , 0, "======Warning======");
	DrawStringEx(screenMidleX - 180, screenMidleY , 0, "Frequent accidents ");
	DrawStringEx(screenMidleX - 30 , screenMidleY + 45, 0, "in");
	DrawStringEx(screenMidleX - 150, screenMidleY + 90, 0, " the labyrinth");
	DrawStringEx(screenMidleX - 180, screenMidleY + 140, 0, "CAUSE : UNKNOWN");
	SetFontSize(30);
	if (frag_draw_enter_ == true) {
		
		DrawStringEx(screenMidleX - 250, screenMidleY + 210, 0, "ETITLE:Press to B button");
	}
}

void SceneExplain::playsound()
{
	SoundManager::GetInstance()->SoundBgm(SoundManager::BGM::TITLE);
}
