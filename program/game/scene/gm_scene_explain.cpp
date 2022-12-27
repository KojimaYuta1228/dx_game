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
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		frag_timer_ = false;
		frag_change_title_ = false;
	}
	if (frag_timer_ == false) {
		cnt_timer -= delta_time;
		if (cnt_timer % 7 == 1 || cnt_timer % 5 == 1 || cnt_timer % 3 == 1 || cnt_timer % 1 == 1) {
			if (frag_change_title_ == false)frag_draw_enter_ = false;
		}
		else {
			frag_draw_enter_ = true;
		}
	}
	if (cnt_timer <= 0 && frag_change_title_ == false) {
		frag_change_title_ = true;
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
	DrawStringEx(screenMidleX - 220, screenMidleY - 170, 0, "reward: everything you want");
	DrawStringEx(screenMidleX - 180, screenMidleY - 130, 0, "camera rotate: A and D");
	DrawStringEx(screenMidleX + 43, screenMidleY - 130, GetColor(255 + 255 * sin(tnl::ToRadian(chang_col_red_)),0,0), " A     D");
	DrawStringEx(screenMidleX - 180, screenMidleY -100, 0, "player move: ArrowKey");
	DrawStringEx(screenMidleX + 8, screenMidleY - 100, GetColor(255 + 255 * sin(tnl::ToRadian(chang_col_red_)), 0, 0), " ArrowKey");
	SetFontSize(40);
	DrawStringEx(screenMidleX - 200, screenMidleY -50  , 0, "======Warning======");
	DrawStringEx(screenMidleX - 180, screenMidleY , 0, "Frequent accidents ");
	DrawStringEx(screenMidleX - 30 , screenMidleY + 45, 0, "in");
	DrawStringEx(screenMidleX - 150, screenMidleY + 90, 0, " the labyrinth");
	DrawStringEx(screenMidleX - 180, screenMidleY + 140, 0, "CAUSE : UNKNOWN");
	SetFontSize(30);
	if (frag_draw_enter_ == true) {
		
		DrawStringEx(screenMidleX - 250, screenMidleY + 210, 0, "ETITLE:Press to Enter");
	}
}

void SceneExplain::playsound()
{
	SoundManager::GetInstance()->SoundBgm(SoundManager::BGM::TITLE);
}
