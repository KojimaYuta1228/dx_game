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
	void Update();
	void UseGacha();
	void GachaAnima(float delta_time);
	void CreateGachaItem(int id_, int type_);
	void CheckGachaItemAlive();


	std::vector<std::vector<std::string>>load_gacha_item_csv;
	int img_hd[5];//load下画像を保存するための配列
	int id_;
	int type_;
	std::vector<GachaItem> my_gacha_item_vec;
	std::list<std::shared_ptr<GachaItem>> spawn_gacha_Item_list;//newしたItemを格納するList
	std::vector<std::shared_ptr<GachaItem>> get_gacha_Item_vec;//獲得したItemを格納するList
	std::shared_ptr<GachaItem> i_gacha_item_ = nullptr;
	int cnt_can_gacha = 3;
	int have_coin = 10;
	bool frag_can_gacha = true;
};
