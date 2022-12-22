#include "gm_scene_base.h"
#include <iostream>
#include<vector>
#include<memory>



class GameOver :public SceneBase {
public:
	GameOver();
	~GameOver();
	
	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
	void playsound();
	int img_gameover = 0;
	int img_shadow = 0;
	double img_exrate = 0.1;
	float img_posX = DXE_WINDOW_WIDTH / 2;
	float img_posY = DXE_WINDOW_HEIGHT / 2;
	int cnt_timer = 8;
	bool string_enter_frag = true;
	bool change_title_frag = true;
	bool timer_frag = true;
	bool img_frag = true;
	float timer = 0;
	float t;
	const int screenMidleX = DXE_WINDOW_WIDTH / 2;
	const int screenMidleY = DXE_WINDOW_HEIGHT / 2;
};