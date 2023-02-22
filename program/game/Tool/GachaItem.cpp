#include "GachaItem.h"
#include"DxLib.h"
#include "../Tool/gm_soundmanager.h"
#include"../Tool/Animation.h"
#include "../gm_manager.h"

GachaItem::GachaItem()
{

}

GachaItem::GachaItem(int id, int type)
{
	//id_ = id; type_ = type; 
}

GachaItem::~GachaItem()
{
}

void GachaItem::Update(float delta_time)
{
	int a = 0;
	a++;
}

void GachaItem::SwitchGachaItem(int type_)
{
	
	switch (type_)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}

}

void GachaItem::WaitGacha(float delta_time)
{
	i_anim_ = new Animation("graphics/Resouce/image/use_efect/tresurebox2.png", 10, 10, 1, 188, 180, DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2);
	liveGachaAnim.emplace_back(i_anim_);
}

void GachaItem::DownArrow(float delta_time)
{
	i_anim_ = new Animation("graphics/Resouce/image/use_efect/speed_down.png", 10, 10, 1, 120, 120, DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2);
	liveGachaAnim.emplace_back(i_anim_);
}

void GachaItem::Render(float delta_time)
{
	for (auto anim : liveGachaAnim) {
		anim->DrawAnimation(delta_time);
	}
	GachaAnimation(delta_time);
}

void GachaItem::GachaAnimation(float delta_time)
{
	
	for (auto anim : liveGachaAnim) {
		anim->UpdateAnimation(delta_time);
	}
	//再生し終わったアニメーションがあったらリストから消してdeleteする
	auto itr = liveGachaAnim.begin();
	while (itr != liveGachaAnim.end()) {
		if ((*itr)->isLive == false) {
			delete (*itr);
			itr = liveGachaAnim.erase(itr);
		}
		else {
			itr++;
		}
	}
}

