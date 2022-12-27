#include "gm_scene_base.h"



class SceneResult : public SceneBase {
public:
	SceneResult();
	~SceneResult();
	//std::shared_ptr<SoundManager> sound = nullptr;
	//SoundManager* sound = nullptr;
	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
	void playsound() override;
	int img_gameclear = 0;
	int img_efect = 0;
	int cnt_timer = 8;
	int img_cnt = 0;
	bool frag_draw_enter_ = true;
	bool frag_change_title_ = true;
	bool frag_timer_ = true;
	const int screenMidleX = DXE_WINDOW_WIDTH / 2;
	const int screenMidleY = DXE_WINDOW_HEIGHT / 2;

};
