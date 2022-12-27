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
	void playsound() override;
	
	float img_posX = DXE_WINDOW_WIDTH / 2;
	float img_posY = DXE_WINDOW_HEIGHT / 2;
	const int screenMidleX = DXE_WINDOW_WIDTH / 2;
	const int screenMidleY = DXE_WINDOW_HEIGHT / 2;
	
	//�摜�n���h��
	int img_gameover_ = 0;
	int img_shadow_ = 0;
	//�摜�̊g�嗦
	double exrate_img_ = 0.1;	
	//�J�E���g
	int cnt_move_title_ = 8;
	float cnt_exrate_ = 0;
	//�t���O
	bool frag_draw_enter_ = true;
	bool frag_move_title_ = true;
	bool frag_cnt_timer_ = true;
	//���W
	float move_pos_;
	
};