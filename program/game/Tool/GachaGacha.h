#pragma once
#include<vector>
#include<memory>
#include"../../dxlib_ext/dxlib_ext.h"
class GachaItem;
class GmCamera;

class GachaGacha {
public:
	GachaGacha();
	~GachaGacha();
	void Update(float delta_time);
	void UseGacha(float delta_time);
	void GachaAnima(float delta_time);
	void CreateGachaItem(int id_, int type_);
	void CheckGachaItemAlive();
	void Render();
	void GetgachaCoin(int get_coin);
	

	std::vector<std::vector<std::string>>load_gacha_item_csv;
	int img_gacha_item[5];//load下画像を保存するための配列
	int img_black = 0;
	int id_;
	int type_;
	std::list<std::shared_ptr<GachaItem>> spawn_gacha_Item_list;//newしたItemを格納するList
	std::vector<std::shared_ptr<GachaItem>> get_gacha_Item_vec;//獲得したItemを格納するList
	std::shared_ptr<GachaItem> i_gacha_item_ = nullptr;
	int cnt_can_gacha = 3;
	int have_coin = 10;
	float cnt_center_render = 0;
	bool frag_can_gacha = true;
	bool get_gacha_item_frag[5] = { true,true,true,true,true };//獲得したItemの描画を切り替えるfrag
	bool frag_next_render = true;
	bool frag_open_draw = true;
	bool frag_cnt_center_render = true;
};
