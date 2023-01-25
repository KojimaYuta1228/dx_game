#include "Item.h"
#include"Map.h"
#include"../scene/gm_scene_play.h"
#include"DxLib.h"

//extern ScenePlay* scene_play_;
tnl::Vector3 item_spawn;

Item::Item(int id, int type, SceneBase* scene_base)
{
	
	ref_scene_ = scene_base;
	ScenePlay* sptr_play = static_cast<ScenePlay*>(ref_scene_);

	if (sptr_play) {
		i_map_ = sptr_play->map_;
	}
	ScenePlay* scene_play = dynamic_cast<ScenePlay*>(scene_base);
	if (scene_play) {
		camera_ = scene_play->GetCamera();
	}

   //scene_play_->map_->Root_holder_[random];
	id_ = id; type_ = type;
	//// �g�p����e�N�X�`�������O���[�h
	//Shared<dxe::Texture> texs[5];

	//texs[0] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/speed_up.jpg");//���x�㏸
	//texs[1] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/speed_down.jpg");//���x����
	//texs[2] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/strong_time.jpg");//���G
	//texs[3] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/key.jpg");//��
	//texs[4] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/coin.jpg");//�R�C��

	//Item�̃N���[���̍쐬
	//dxe::Mesh* item_box_[9];//�N���[�������A�C�e��������Ă�����

	/*
	for (int i = 0; i < 9; ++i) {
		
		random = rand() % 25;
		if (i < 2) {
			//item_box_[i] = dxe::Mesh::CreateBarrelMV(10, 13, 25);//���a�A�c��݁A����
			//item_box_[i]->setTexture(texs[0]);
			MyVec2i v = i_map_->Root_holder_[random];
			item_spawn = { (float)v.x_ * 50,0,(float)v.y_ * 50 };
			//item_ = item_box_[i]->createClone();
			type_ = 0;
			printfDx("x = %d, y = %d", v.x_, v.y_, true);
		}
		if (i >= 2 && i < 4) {
			//item_box_[i] = dxe::Mesh::CreateBarrelMV(10, 13, 25);//���a�A�c��݁A����
			//item_box_[i]->setTexture(texs[1]);
			MyVec2i v = i_map_->Root_holder_[random];
			item_spawn = { (float)v.x_ * 10,0,(float)v.y_ * 10 };
			//item_ = item_box_[i]->createClone();
			printfDx("x = %d, y = %d", v.x_, v.y_, true);
			type_ = 1;
		}
		if (i == 5) {
			//item_box_[i] = dxe::Mesh::CreateTorusMV(10, 8);
			//item_box_[i]->setTexture(texs[2]);
			MyVec2i v = i_map_->Root_holder_[random];
			item_spawn = { (float)v.x_ * 10,0,(float)v.y_ * 10 };
			//item_ = item_box_[i]->createClone();
			type_ = 2;
			printfDx("x = %d, y = %d", v.x_, v.y_, true);
		}
		if (i == 6) {
			//item_box_[i] = dxe::Mesh::CreateTorusMV(10, 8);
			//item_box_[i]->setTexture(texs[3]);
			MyVec2i v = i_map_->Root_holder_[random];
			item_spawn = { (float)v.x_ * 10,0,(float)v.y_ * 10 };
			//item_ = item_box_[i]->createClone();
			type_ = 3;
			printfDx("x = %d, y = %d", v.x_, v.y_, true);
		}
		else {
			//item_box_[i] = dxe::Mesh::CreateDiskMV(50);
			//item_box_[i]->setTexture(texs[4]);
			MyVec2i v = i_map_->Root_holder_[random];
			item_spawn = { (float)v.x_ * 10,0,(float)v.y_ * 10 };
			//item_ = item_box_[i]->createClone();
			type_ = 4;
			printfDx("x = %d, y = %d", v.x_, v.y_, true);
		}
		
	}
	*/

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
	//item_->pos_ = item_spawn;
	item_->render(camera_);
}

float Item::CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)
{
	return 0.0f;
}


