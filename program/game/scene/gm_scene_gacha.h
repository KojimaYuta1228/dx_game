#pragma once
#include "gm_scene_base.h"
#include<vector>
#include<memory>
#include <algorithm>
class GachaGacha;
class GmCamera;

class SceneGacha :public SceneBase {
public:
	SceneGacha();
	~SceneGacha();

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
	void playsound() override;
	void DrawAnim(float delta_time);
	
	std::shared_ptr<GachaGacha> gachagacha_ = nullptr;
	int img_guild = 0;
	int img_tresure_box = 0;
	int img_frash = 0;
	float angle = 0;
	int cnt_img_tresure_box_x1 = 414;
	int cnt_img_tresure_box_x2 = 614;
	int cnt_img_tresure_box_y1 = 284;
	int cnt_img_tresure_box_y2 = 484;
	int vx_ = 2;
	int vy_ = 2;
	int cnt_bounce_ = 0;
	int cnt_arow = 0;
	float cnt_ar = 0;
	float cnt_ = 0;
	float cnt_next_tre = 0;
	float cnt_draw_gacha_item = 0;
	bool tim = true;
	bool frag_tre_move = true;
	bool frag_up_down = true;
	bool frag_right_left = true;
	bool frag_start_gacha_anim = true;
	bool frag_can_render_tresureBox = true;
	bool frag_render_frash = true;
	bool frag_down_arrow = true;
};