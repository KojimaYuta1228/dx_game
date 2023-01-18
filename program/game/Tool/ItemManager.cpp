#include"ItemManager.h"

ItemManager::ItemManager()
{
	load_item_csv = tnl::LoadCsv("csv/Item.csv");
	for (int i = 1; i < load_item_csv.size(); i++) {
		id_ = std::atoi(load_item_csv[i][0].c_str());
		type_ = std::atoi(load_item_csv[i][1].c_str());

		CreateItem(id_,type_);
	}
}

ItemManager::~ItemManager()
{
}

void ItemManager::CreateItem(int id, int type)
{
	item_ = std::make_shared<Item>(id, type);
	Item_holder.emplace_back(item_);
}

void ItemManager::Update()
{

}
