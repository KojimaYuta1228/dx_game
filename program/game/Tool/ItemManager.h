#pragma once
#include <list>  
#include<vector>
#include<string>
#include"../../dxlib_ext/dxlib_ext.h"

class Item;
class GmCamera;

class ItemManager {
public:
	ItemManager(){}
	ItemManager( SceneBase* scene_base );
	~ItemManager();
	void CreateItem(int id, int type);
	void Update(float delta_time);
	void CheckItemIsAlive();
	void UseHaveItem();
	void Render();
	std::list<std::shared_ptr<Item>> spawn_Item_list;//newしたItemを格納するList
	std::vector<std::shared_ptr<Item>> get_Item_vec;//獲得したItemを格納するList
	SceneBase* ref_scene_ = nullptr;
	// 使用するテクスチャを事前ロード
	Shared<dxe::Texture> texs[5];
	dxe::Mesh* item_box_[9];//アイテム用のオリジナルの箱
	std::shared_ptr<Item> item;
	
	//画像ハンドル
	const int IMG_NUM = 5;
	int img_hd[5];
	bool get_item_frag[5] = { false,false,false,false,false };//獲得したItemの描画を切り替えるfrag
	int cnt_pos_ = 0;
	int arrow_pos = 0;
	float angle_ = 0;
	tnl::Vector3 move_p;
	int select_item_img = 0;

	MyVec2i save_v;
private:
	std::vector<std::vector<std::string>>load_item_csv;
	int id_;
	int type_;
	bool is_alive_ = true;
};
