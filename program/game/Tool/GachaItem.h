#pragma once
#include "../../dxlib_ext/dxlib_ext.h"
class Animation;

class GachaItem {
public:
	GachaItem();
	GachaItem(int id, int type);
	~GachaItem();

	void Update(float delta_time);
	void Render(float delta_time);
	void GachaAnimation(float delta_time);
	void SwitchGachaItem(int type_);

	int id_;
	int type_;
	int random_num_;
	bool is_alive_ = true;
	Animation* i_anim_ = nullptr;
	std::list<Animation*> liveGachaAnim;
};