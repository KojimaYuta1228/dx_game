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
	void Render();
	std::shared_ptr<Item>item_ = nullptr;
	std::list<std::shared_ptr<Item>> spawn_Item_list;//new‚µ‚½Item‚ðŠi”[‚·‚éList
	SceneBase* ref_scene_ = nullptr;
private:
	std::vector<std::vector<std::string>>load_item_csv;
	int id_;
	int type_;
	bool is_alive_ = true;
};
