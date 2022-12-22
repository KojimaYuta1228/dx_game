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
		timer_frag = false;
		change_title_frag = false;
	}
	if (timer_frag == false) {
		cnt_timer -= delta_time;
		if (cnt_timer % 7 == 1 || cnt_timer % 5 == 1 || cnt_timer % 3 == 1 || cnt_timer % 1 == 1) {
			if (change_title_frag == false)string_enter_frag = false;
		}
		else {
			string_enter_frag = true;
		}
	}
	if (cnt_timer <= 0 && change_title_frag == false) {
		change_title_frag = true;
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
	DrawStringEx(screenMidleX-400, screenMidleY, -1, "���Ȃ��͖��{����ɂ����c");
	if (string_enter_frag == true) {
		DrawStringEx(screenMidleX - 350, screenMidleY + 50, -1, "�ETITLE:Press to Enter");
	}
}

void SceneResult::playsound()
{
	SoundManager::GetInstance()->SoundBgm(SoundManager::BGM::RESULT);
	//sound->SoundBgm(static_cast<uint32_t>(SoundManager::BGM::RESULT));
}