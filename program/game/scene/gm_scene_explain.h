#pragma once
#include "gm_scene_base.h"
#include<vector>
#include<memory>

class SceneExplain :public SceneBase {
public:
	SceneExplain();
	~SceneExplain();
	
	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
	void playsound() override;


	const int screenMidleX = DXE_WINDOW_WIDTH / 2;
	const int screenMidleY = DXE_WINDOW_HEIGHT / 2;

	//�J�E���g
	int cnt_timer_player_ = 8;
	//�摜�n���h��
	int img_explain_ = 0;
	//�ύX
	int chang_col_red_ = 0;
	//�t���O
	bool frag_draw_enter_ = true;
	bool frag_change_title_ = true;
	bool frag_cnt_timer_ = true;
};
