#pragma once
#include "gm_scene_base.h"
#include<vector>
#include<memory>
#include <algorithm>
class GachaItem;
class GmCamera;

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
	void CreateGachaItem(int id_, int type_);
	void CheckGachaItemAlive();

	
	std::vector<std::vector<std::string>>load_gacha_item_csv;
	int img_hd[4];//load���摜��ۑ����邽�߂̔z��
	int id_;
	int type_;
	std::vector<GachaItem> my_gacha_item_vec;
	std::shared_ptr<GachaItem> i_gacha_item_;
	std::list<std::shared_ptr<GachaItem>> spawn_gacha_Item_list;//new����Item���i�[����List
	std::vector<std::shared_ptr<GachaItem>> get_gacha_Item_vec;//�l������Item���i�[����List

	int cnt_can_gacha = 3;
	int have_coin = 10;
	bool frag_can_gacha = true;
};