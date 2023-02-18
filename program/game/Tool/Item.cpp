#include "Item.h"
#include"Map.h"
#include "../Character/Player.h"
#include"../scene/gm_scene_play.h"
#include"DxLib.h"

//extern ScenePlay* scene_play_;
//tnl::Vector3 item_spawn;
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
	id_ = id; type_ = type;
	//i_player_ = std::make_shared<Player>();
}

Item::~Item()
{
}



void Item::SwithItemMove(int item_num)
{
	ScenePlay* scene_play_ = static_cast<ScenePlay*>(ref_scene_);;
	switch (type_)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		scene_play_->frag_can_goal = false;
		break;
	case 4:
		scene_play_->player_->move_speed = 0.1;
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
	item_mesh->rot_q_ = tnl::Quaternion::RotationAxis({ 0,1,0 }, tnl::ToRadian(angle_));
	angle_++;
}

void Item::Render()
{
	item_mesh->render(camera_);
}

float Item::CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)
{
	return 0.0f;
}


