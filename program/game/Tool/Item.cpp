#include "Item.h"
#include"Map.h"
#include"../scene/gm_scene_play.h"
#include"DxLib.h"

//extern ScenePlay* scene_play_;
tnl::Vector3 item_spawn;

Item::Item(int id, int type, SceneBase* scene_base)
{
	//srand(time(0));
	random = rand() % 10;

	ref_scene_ = scene_base;
	ScenePlay* sptr_play = static_cast<ScenePlay*>(ref_scene_);

	if (sptr_play) {
		i_map_ = sptr_play->map_;
	}


   //scene_play_->map_->Root_holder_[random];
	id_ = id; type_ = type;
	// 使用するテクスチャを事前ロード
	Shared<dxe::Texture> texs[5];

	texs[0] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/speed_up.jpg");//速度上昇
	texs[1] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/speed_down.jpg");//速度減少
	texs[2] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/strong_time.jpg");//無敵
	texs[3] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/key.jpg");//鍵
	texs[4] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/coin.jpg");//コイン

	//Itemのクローンの作成
	dxe::Mesh* item_box_[9];//クローンしたアイテムをいれておく箱
	for (int i = 0; i < 9; ++i) {
		if (i < 2) {
			item_box_[i] = dxe::Mesh::CreateBarrelMV(10, 13, 25);//半径、膨らみ、高さ
			item_box_[i]->setTexture(texs[0]);
			item_ = item_box_[i]->createClone();
			type_ = 0;
		}
		if (i >= 2 && i < 4) {
			item_box_[i] = dxe::Mesh::CreateBarrelMV(10, 13, 25);//半径、膨らみ、高さ
			item_box_[i]->setTexture(texs[1]);
			item_ = item_box_[i]->createClone();
			type_ = 1;
		}
		if (i == 5) {
			item_box_[i] = dxe::Mesh::CreateTorusMV(10, 8);
			item_box_[i]->setTexture(texs[2]);
			item_ = item_box_[i]->createClone();
		}
		if (i == 6) {
			item_box_[i] = dxe::Mesh::CreateTorusMV(10, 8);
			item_box_[i]->setTexture(texs[3]);
			item_ = item_box_[i]->createClone();
		}
		else {
			item_box_[i] = dxe::Mesh::CreateDiskMV(50);
			item_box_[i]->setTexture(texs[4]);
			item_ = item_box_[i]->createClone();
		}

	}
	MyVec2i v = i_map_->Root_holder_[random];

	item_spawn = { (float)v.x_ * 50,0,(float)v.y_ * 50 };
	printfDx("x = %d, y = %d", v.x_, v.y_, true);

}

Item::~Item()
{
}



void Item::SwithItemMove()
{
	switch (type_)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}
}

void Item::initialzie()
{


	
}

void Item::Update(float delta_time)
{

}

void Item::Render()
{
	item_->pos_ = item_spawn;
	item_->render(camera_);
}

float Item::CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)
{
	return 0.0f;
}


