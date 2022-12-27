#include "../gm_manager.h"
#include"../Tool/gm_soundmanager.h"
#include"gm_scene_gameover.h"
#include "gm_scene_result.h"
#include "gm_scene_title.h"
#include "../Tool/Animation.h"




SceneResult::SceneResult()
{
	

}

SceneResult::~SceneResult()
{
	
}

void SceneResult::initialzie() {
	img_gameclear = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/gameclear.png");
	img_efect = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/shineFix.png");
	playsound();
}

void SceneResult::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();
	

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		SoundManager::GetInstance()->SoundSe(SoundManager::SE::SE_INSECT);
		frag_cnt_timer_ = false;
		frag_change_title_ = false;
	}
	if (frag_cnt_timer_ == false) {
		cnt_timer_player_ -= delta_time;
		if (cnt_timer_player_ % 7 == 1 || cnt_timer_player_ % 5 == 1 || cnt_timer_player_ % 3 == 1 || cnt_timer_player_ % 1 == 1) {
			if (frag_change_title_ == false)frag_draw_enter_ = false;
		}
		else {
			frag_draw_enter_ = true;
		}
	}
	if (cnt_timer_player_ <= 0 && frag_change_title_ == false) {
		frag_change_title_ = true;
		mgr->chengeScene(new SceneTitle());
	}
	img_cnt++;
}

void SceneResult::render()
{ 
	DrawRotaGraph(screenMidleX, screenMidleY, 1.0, 0, img_gameclear, true);
	for (int i = 0; i < 3; i++) {
		DrawRotaGraph(screenMidleX + 100*i, screenMidleY  - i * 150, 2 + sin(tnl::ToRadian(img_cnt)), 0, img_efect, true);
		DrawRotaGraph(screenMidleX - 200*i, screenMidleY + i * 50,  sin(tnl::ToRadian(img_cnt)), 0, img_efect, true);
	}
	DrawRotaGraph(screenMidleX-250 , screenMidleY -300, 1 + sin(tnl::ToRadian(img_cnt)), 0, img_efect, true);
	DrawRotaGraph(screenMidleX+250 , screenMidleY +300, 1 + sin(tnl::ToRadian(img_cnt)), 0, img_efect, true);
	SetFontSize(100);
	DrawStringEx(screenMidleX-300, screenMidleY-300, -1, "Stage Clear");
	SetFontSize(40);
	DrawStringEx(screenMidleX-400, screenMidleY, -1, "あなたは迷宮を後にした…");
	if (frag_draw_enter_ == true) {
		DrawStringEx(screenMidleX - 350, screenMidleY + 50, -1, "・TITLE:Press to Enter");
	}
}

void SceneResult::playsound()
{
	SoundManager::GetInstance()->SoundBgm(SoundManager::BGM::RESULT);
	//sound->SoundBgm(static_cast<uint32_t>(SoundManager::BGM::RESULT));
}
