#include "gm_scene_base.h"
#include<vector>
#include<memory>
#include<iostream>


class Player;

class SceneTitle : public SceneBase {
public:
	SceneTitle();
	~SceneTitle();

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
	void playsound();//ñ{óàÇ»ÇÁÇŒSOUNDÇ‡SceneBaseÇ…èëÇ¢ÇƒÇ®Ç≠

	std::shared_ptr<Player> player_sprite = nullptr;
	LPCSTR font_path;
	const int screenMidleX = DXE_WINDOW_WIDTH / 2;
	const int screenMidleY = DXE_WINDOW_HEIGHT / 2;
	int titleImage = 0;
	int cnt = 0;
	int textCol = -1.0;
	int arrowCol = -1.0;
	int cnt_pos = 0;
	int cnt_timer = 8;
	int cnt_timer_2 = 10;
	int arrow_pos_ = 384+20;
	float t = 0;
	bool s_frag = true;
	bool string_enter_frag = true;
	bool string_space_frag = true;
	bool timer_frag = true;
	bool change_title_frag = true;
	bool change_explain_frag = true;
};

