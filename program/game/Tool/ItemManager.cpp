#include "../scene/gm_scene_base.h"
#include "../scene/gm_scene_play.h"
#include"ItemManager.h"
#include"Item.h"
#include"../Tool/Map.h"

ItemManager::ItemManager(SceneBase* scene_base)
{
	
	texs[0] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/speed_up.jpg");//���x�㏸
	texs[1] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/speed_down.jpg");//���x����
	texs[2] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/strong_time.jpg");//���G
	texs[3] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/key.jpg");//��
	texs[4] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/coin.jpg");//�R�C��

	load_item_csv = tnl::LoadCsv("csv/Item.csv");
	
	for (int i = 0; i < 9; i++) {
		if (i < 2) {
			item_box_[i] = dxe::Mesh::CreateBarrelMV(5, 50, 5);//���a�A�����A�c���
			item_box_[i]->setTexture(texs[0]);
		}
		else if (i >= 2 && i < 4) {
			item_box_[i] = dxe::Mesh::CreateBarrelMV(5, 50, 5);
			item_box_[i]->setTexture(texs[1]);
		}
		else if (i == 5) {
			item_box_[i] = dxe::Mesh::CreateTorusMV(15, 10);
			item_box_[i]->setTexture(texs[2]);
		}
		else if (i == 6) {
			item_box_[i] = dxe::Mesh::CreateTorusMV(15, 10);
			item_box_[i]->setTexture(texs[3]);
		}
		else {
			item_box_[i] = dxe::Mesh::CreateDiskMV(25);
			item_box_[i]->setTexture(texs[4]);
		}
	}


	ref_scene_ = scene_base;
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
	item = std::make_shared<Item>(id, type, ref_scene_);//Item��new
	spawn_Item_list.emplace_back(item);//list�ɒǉ�
	item->item_mesh = item_box_[id]->createClone();//�N���[����

	ScenePlay* sptr_play = static_cast<ScenePlay*>(ref_scene_);
	//�񎟌��z����W�������_�����I
	auto random = rand() % sptr_play->map_->Root_holder_.size();
	MyVec2i v = sptr_play->map_->Root_holder_[random];
	//���[���h���W�ɕϊ�
	item->item_mesh->pos_.x = (v.x_ * 50) - (12.5f * 50) + 25;
	item->item_mesh->pos_.z = (-v.y_ * 50) + (12.5f * 50) - 25;


}

void ItemManager::Update(float delta_time)
{
	CheckItemIsAlive();
}
//List�ɂ���A�C�e���̍폜
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
