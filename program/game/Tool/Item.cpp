#include "Item.h"
#include"../scene/gm_scene_play.h"

extern ScenePlay* scene_play_;

Item::Item(int id, int type)
{
	id_ = id; type_ = type;
	// 使用するテクスチャを事前ロード
	Shared<dxe::Texture> texs[5];

	texs[0] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/speed_up.jpg");
	texs[1] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/speed_down.jpg");
	texs[2] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/strong_time.jpg");
	texs[3] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/key.jpg");
	texs[4] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/coin.jpg");
	
}

Item::~Item()
{
}



void Item::SwithItemMove()
{
	switch (type_)
	{
	case 0 :
		break;
	case 1 :
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
}

float Item::CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)
{
	return 0.0f;
}


