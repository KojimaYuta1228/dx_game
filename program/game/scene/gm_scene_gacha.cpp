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
}

void SceneGacha::render()
{
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 0.7, 0, img_guild, true);
	DrawRotaGraph(DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2, 0.7, 0, img_tresure_box, true);
	gachagacha_->GachaAnima(0.01666);
}

void SceneGacha::playsound()
{
}
