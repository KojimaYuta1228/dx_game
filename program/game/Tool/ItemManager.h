#pragma once
#include <list>  
#include<vector>
#include<string>
#include"../../dxlib_ext/dxlib_ext.h"

class Item;

class ItemManager {
public:
	ItemManager();
	~ItemManager();

	void CreateItem(int id, int type);
	void Update();
	std::shared_ptr<Item>item_ = nullptr;
	std::list<std::shared_ptr<Item>> Item_holder;
private:
	std::vector<std::vector<std::string>>load_item_csv;
	int id_;
	int type_;
};
