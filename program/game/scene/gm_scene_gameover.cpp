#include "../gm_manager.h"
#include "gm_scene_gameover.h"
#include "../Tool/gm_soundmanager.h"
#include "gm_scene_title.h"
#include"gm_scene_play.h"

GameOver::GameOver()
{
	
}

GameOver::~GameOver()
{
	
}

void GameOver::initialzie()
{
	img_gameover = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/gameover.jpg");
	img_shadow = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/enemy_shadow.png");
	playsound();
}

void GameOver::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		SoundManager::GetInstance()->SoundSe(SoundManager::SE::SE_INSECT);
		frag_timer_ = false;
		frag_change_title_ = false;
	}
	if (frag_timer_ == false) {
		cnt_timer -= delta_time;
		if (cnt_timer % 7 == 1 || cnt_timer % 5 == 1 || cnt_timer % 3 == 1 || cnt_timer % 1 == 1) {
			if (frag_change_title_ == false)frag_draw_enter_ = false;
			SoundManager::GetInstance()->SoundSe(SoundManager::SE::ENEMY_GHOST);
		}
		else {
			frag_draw_enter_ = true;
		}
	}
	if (cnt_timer <= 0 && frag_change_title_ == false) {
		frag_change_title_ = true;
		mgr->chengeScene(new SceneTitle());
	}
	

	timer += delta_time;
	t = 20.0 * sin(timer);

}

void GameOver::render()
{
	DrawRotaGraph(screenMidleX, screenMidleY, 1.0, 0, img_gameover, true);
	DrawRotaGraph(img_posX - t, screenMidleY + t, img_exrate * sin(timer), 0, img_shadow, true);
	
	SetFontSize(100);
	DrawStringEx(screenMidleX - 200, screenMidleY - 300, -1, "GAME OVER");
	SetFontSize(40);
	DrawStringEx(screenMidleX - 500, screenMidleY - 100, -1, "���{�Ɏ��c����Ă��܂���...");
	if (frag_draw_enter_ == true) {
		DrawStringEx(screenMidleX, screenMidleY + 150, -1, "TITLE:Press to Enter");
	}


}

void GameOver::playsound()
{
	SoundManager::GetInstance()->SoundBgm(SoundManager::BGM::GAMEOVER);
}

