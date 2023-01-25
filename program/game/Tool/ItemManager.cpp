#include "../scene/gm_scene_base.h"
#include"ItemManager.h"
#include"Item.h"
#include"../Tool/Map.h"

ItemManager::ItemManager(SceneBase* scene_base)
{
	ref_scene_ = scene_base;
	load_item_csv = tnl::LoadCsv("csv/Item.csv");
	for (int i = 1; i < load_item_csv.size(); i++) {
		id_ = std::atoi(load_item_csv[i][0].c_str());
		type_ = std::atoi(load_item_csv[i][1].c_str());

	}
	CreateItem(id_, type_);
}

ItemManager::~ItemManager()
{
}

void ItemManager::CreateItem(int id, int type)
{
	
	for (int y = 0; y < Map::MEIRO_HEIGHT; y++) {
		for (int x = 0; x < Map::MEIRO_WIDTH; x++) {
			if (Map::maze[y][x] == static_cast<int>(Map::MAZESTATE::ROOT)) {
				item_ = std::make_shared<Item>(id, type, ref_scene_);
				spawn_Item_list.emplace_back(item_);
				
				return;
			}
		}
	}
}

void ItemManager::Update(float delta_time)
{
	CheckItemIsAlive();
	item_->Update(delta_time);
}
//List‚É‚ ‚éƒAƒCƒeƒ€‚Ìíœ
void ItemManager::CheckItemIsAlive()
{
	auto it = spawn_Item_list.begin();
	while (it != spawn_Item_list.end()) {
		if (!(*it)->is_alive_) {
			it = spawn_Item_list.erase(it);
			continue;
		}
		it++;
	}
}
void ItemManager::Render() {
	item_->Render();
}
