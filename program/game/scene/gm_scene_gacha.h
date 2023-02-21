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
	
	std::shared_ptr<GachaGacha> gachagacha_ = nullptr;
	int img_guild = 0;
	int img_tresure_box = 0;
};