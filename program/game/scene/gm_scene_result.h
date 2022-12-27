#include "gm_scene_base.h"



class SceneResult : public SceneBase {
public:
	SceneResult();
	~SceneResult();

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
	void playsound() override;

	const int screenMidleX = DXE_WINDOW_WIDTH / 2;
	const int screenMidleY = DXE_WINDOW_HEIGHT / 2;
	//画像ハンドル
	int img_gameclear_ = 0;
	int img_efect_ = 0;
	//カウント
	int cnt_down_move_title_ = 8;
	int cnt_img_ = 0;
	//フラグ
	bool frag_draw_enter_ = true;
	bool frag_move_title_ = true;
	bool frag_cnt_timer_ = true;
	

};
