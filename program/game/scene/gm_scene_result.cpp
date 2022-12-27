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
	img_gameclear_ = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/gameclear.png");
	img_efect_ = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/shineFix.png");
	playsound();
}

void SceneResult::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();
	

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		SoundManager::GetInstance()->SoundSe(SoundManager::SE::SE_INSECT);
		frag_cnt_timer_ = false;
		frag_move_title_ = false;
	}
	if (frag_cnt_timer_ == false) {
		cnt_down_move_title_ -= delta_time;
		if (cnt_down_move_title_ % 7 == 1 || cnt_down_move_title_ % 5 == 1 || cnt_down_move_title_ % 3 == 1 || cnt_down_move_title_ % 1 == 1) {
			if (frag_move_title_ == false)frag_draw_enter_ = false;
		}
		else {
			frag_draw_enter_ = true;
		}
	}
	if (cnt_down_move_title_ <= 0 && frag_move_title_ == false) {
		frag_move_title_ = true;
		mgr->chengeScene(new SceneTitle());
	}
	cnt_img_++;
}

void SceneResult::render()
{ 
	DrawRotaGraph(screenMidleX, screenMidleY, 1.0, 0, img_gameclear_, true);
	for (int i = 0; i < 3; i++) {
		DrawRotaGraph(screenMidleX + 100*i, screenMidleY  - i * 150, 2 + sin(tnl::ToRadian(cnt_img_)), 0, img_efect_, true);
		DrawRotaGraph(screenMidleX - 200*i, screenMidleY + i * 50,  sin(tnl::ToRadian(cnt_img_)), 0, img_efect_, true);
	}
	DrawRotaGraph(screenMidleX-250 , screenMidleY -300, 1 + sin(tnl::ToRadian(cnt_img_)), 0, img_efect_, true);
	DrawRotaGraph(screenMidleX+250 , screenMidleY +300, 1 + sin(tnl::ToRadian(cnt_img_)), 0, img_efect_, true);
	SetFontSize(100);
	DrawStringEx(screenMidleX-300, screenMidleY-300, -1, "Stage Clear");
	SetFontSize(40);
	DrawStringEx(screenMidleX-400, screenMidleY, -1, "‚ ‚È‚½‚Í–À‹{‚ðŒã‚É‚µ‚½c");
	if (frag_draw_enter_ == true) {
		DrawStringEx(screenMidleX - 350, screenMidleY + 50, -1, "ETITLE:Press to Enter");
	}
}

void SceneResult::playsound()
{
	SoundManager::GetInstance()->SoundBgm(SoundManager::BGM::RESULT);
	//sound->SoundBgm(static_cast<uint32_t>(SoundManager::BGM::RESULT));
}
