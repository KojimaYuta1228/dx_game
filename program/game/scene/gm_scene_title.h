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
	void playsound() override;//�{���Ȃ��SOUND��SceneBase�ɏ����Ă���

	std::shared_ptr<Player> player_sprite = nullptr;
	//�t�H���g�̃n���h��
	LPCSTR font_path;
	const int screenMidleX = DXE_WINDOW_WIDTH / 2;
	const int screenMidleY = DXE_WINDOW_HEIGHT / 2;
	//�摜�n���h��
	int img_title_ = 0;
	//�����J���[
	int col_txt_ = -1.0;
	int col_arrow_ = -1.0;
	//�J�E���g
	int cnt_pos_ = 0;
	int cnt_timer_ = 8;
	//arrow��pos
	int pos_arrow_ = DXE_WINDOW_HEIGHT / 2 +20;
	//frag
	bool frag_draw_enter_ = true;
	bool frag_draw_space_ = true;
	bool frag_timer_ = true;
	bool frag_change_title_ = true;
	bool frag_change_explain_ = true;
};

