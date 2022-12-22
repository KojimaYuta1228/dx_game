#pragma once
#include "gm_scene_base.h"
#include<vector>
#include<memory>
//class SoundManager;
class SceneExplain :public SceneBase {
public:
	SceneExplain();
	~SceneExplain();
	//std::shared_ptr<SoundManager>sound = nullptr;
	const int screenMidleX = DXE_WINDOW_WIDTH / 2;
	const int screenMidleY = DXE_WINDOW_HEIGHT / 2;
	int cnt_timer = 8;
	bool string_enter_frag = true;
	bool change_title_frag = true;
	bool timer_frag = true;
	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
	void playsound();
	int img_explain = 0;
	int chang_col_red = 0;
};
