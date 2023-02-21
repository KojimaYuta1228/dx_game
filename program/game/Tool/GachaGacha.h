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
	int img_hd[4];//load‰º‰æ‘œ‚ð•Û‘¶‚·‚é‚½‚ß‚Ì”z—ñ
	int id_;
	int type_;
	std::vector<GachaItem> my_gacha_item_vec;
	std::shared_ptr<GachaItem> i_gacha_item_;
	std::list<std::shared_ptr<GachaItem>> spawn_gacha_Item_list;//new‚µ‚½Item‚ðŠi”[‚·‚éList
	std::vector<std::shared_ptr<GachaItem>> get_gacha_Item_vec;//Šl“¾‚µ‚½Item‚ðŠi”[‚·‚éList

	int cnt_can_gacha = 3;
	int have_coin = 10;
	bool frag_can_gacha = true;
};
