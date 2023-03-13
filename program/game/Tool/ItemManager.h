#pragma once
#include <list>  
#include<vector>
#include<string>
#include"../../dxlib_ext/dxlib_ext.h"


class Item;
class GmCamera;
class GachaGacha;

class ItemManager {
public:
	ItemManager(){}
	ItemManager( SceneBase* scene_base );
	~ItemManager();
	void CreateItem(int id, int type);
	void Update(float delta_time);
	void CheckItemIsAlive();//アイテムの生存確認falseならばデリートする
	void UseHaveItem();//アイテムの使用使ったアイテムのフラグを折り、Itemクラスにtypeを渡す
	void Render();

	std::list<std::shared_ptr<Item>> spawn_Item_list;//newしたItemを格納するList
	std::vector<std::shared_ptr<Item>> get_Item_vec;//獲得したItemを格納するList
	SceneBase* ref_scene_ = nullptr;
	Shared<dxe::Texture> texs[5];//使用するテクスチャを事前ロードする際に保存するための配列
	dxe::Mesh* item_box_[9];//アイテム用のオリジナルの箱
	std::shared_ptr<Item> item;
	std::weak_ptr<GachaGacha> gacha;
	bool get_item_frag[5] = { false,false,false,false,false };//獲得したItemの描画を切り替えるfrag
	MyVec2i save_v;//マップ上にアイテムをスポーンさせるためのローカル座標を保存する変数
private:
	std::vector<std::vector<std::string>>load_item_csv;
	int id_;
	int type_;
	int cnt_max = 4;
	int cnt_min = 0;
	int select_item_img = 0;//画像ハンドル
	int wood_freme_img = 0;//画像ハンドル
	const int IMG_NUM = 5;//for文の最大数
	const int FIFTY = 50;
	int img_hd[5];//load下画像を保存するための配列
	int cnt_pos_ = 0;//選択中のカーソルのPosの上限下限処理のためのカウント
	int arrow_pos = 0;//選択中のカーソルのPos

};
