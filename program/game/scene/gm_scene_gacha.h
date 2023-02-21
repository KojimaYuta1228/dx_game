#pragma once
#include "gm_scene_base.h"
#include<vector>
#include<memory>

class SceneGacha :public SceneBase {
public:
	SceneGacha();
	~SceneGacha();

	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
	void playsound() override;
	void UseGacha();
	void GachaAnima(float delta_time);
};