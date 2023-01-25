#include "../scene/gm_scene_base.h"
#include "../scene/gm_scene_play.h"
#include"ItemManager.h"
#include"Item.h"
#include"../Tool/Map.h"

ItemManager::ItemManager(SceneBase* scene_base)
{
	
	texs[0] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/speed_up.jpg");//速度上昇
	texs[1] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/speed_down.jpg");//速度減少
	texs[2] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/strong_time.jpg");//無敵
	texs[3] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/key.jpg");//鍵
	texs[4] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/coin.jpg");//コイン

	for (int i = 0; i < 9; i++) {
		if (i < 2) {
			item_box_[i] = dxe::Mesh::CreateBarrelMV(10, 13, 25);//半径、膨らみ、高さ
			item_box_[i]->setTexture(texs[0]);
		}
		if (i >= 2 && i < 4) {
			item_box_[i] = dxe::Mesh::CreateBarrelMV(10, 13, 25);//半径、膨らみ、高さ
			item_box_[i]->setTexture(texs[1]);
		}
		if (i == 5) {
			item_box_[i] = dxe::Mesh::CreateTorusMV(10, 8);
			item_box_[i]->setTexture(texs[2]);
		}
		if (i == 6) {
			item_box_[i] = dxe::Mesh::CreateTorusMV(10, 8);
			item_box_[i]->setTexture(texs[3]);
		}
		else {
			item_box_[i] = dxe::Mesh::CreateDiskMV(50);
			item_box_[i]->setTexture(texs[4]);
		}
	}


	ref_scene_ = scene_base;
	load_item_csv = tnl::LoadCsv("csv/Item.csv");
	for (int i = 1; i < load_item_csv.size(); i++) {
		id_ = std::atoi(load_item_csv[i][0].c_str());
		type_ = std::atoi(load_item_csv[i][1].c_str());
		CreateItem(id_, type_);
	}
}

ItemManager::~ItemManager()
{
}

void ItemManager::CreateItem(int id, int type)
{	
	std::shared_ptr<Item> item = std::make_shared<Item>(id, type, ref_scene_);
	spawn_Item_list.emplace_back(item);
	item->item_ = item_box_[id]->createClone();

	ScenePlay* sptr_play = static_cast<ScenePlay*>(ref_scene_);

	auto random = rand() % sptr_play->map_->Root_holder_.size();
	MyVec2i v = sptr_play->map_->Root_holder_[random];

	item->item_->pos_.x = (v.x_ * 50) - (12.5f * 50) + 25;
	item->item_->pos_.z = (-v.y_ * 50) + (12.5f * 50) - 25;


}

void ItemManager::Update(float delta_time)
{
	CheckItemIsAlive();
}
//Listにあるアイテムの削除
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
	for (auto item : spawn_Item_list) {
		item->Render();
	}
}
