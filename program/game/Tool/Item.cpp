#include "Item.h"
#include"Map.h"
#include "../Character/Player.h"
#include"../Character/Enemy.h"
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
	scene_play_ = static_cast<ScenePlay*>(ref_scene_);
}

Item::~Item()
{
}



void Item::SwithItemMove(int cnt_pos_)
{
	switch (cnt_pos_)
	{
	case 0:
		scene_play_->player_->base_move_speed = 2.0;
		break;
	case 1:
		frag_enemy_speed_down = false;
		break;
	case 2:
		scene_play_->frag_strong_time = false;
		break;
	case 3:
		scene_play_->frag_can_goal = false;
		break;
	case 4:
		break;
	default:
		break;
	}
}

void Item::ItemProcess(float delta_time)
{
	if (!frag_enemy_speed_down) {
		scene_play_->enemy_->base_move_speed = 0.1;
		cnt_enemy_speed_down -= delta_time;
	}
	if(cnt_enemy_speed_down < 0) {
		scene_play_->enemy_->base_move_speed = 1.0;
		cnt_enemy_speed_down = 3.0;
		frag_enemy_speed_down = true;
	}
}

void Item::initialzie()
{	
}

void Item::Update(float delta_time)
{
	item_mesh->rot_q_ = tnl::Quaternion::RotationAxis({ 0,1,0 }, tnl::ToRadian(angle_));
	angle_++;
	ItemProcess(delta_time);
}

void Item::Render()
{
	item_mesh->render(camera_);
}

float Item::CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)
{
	return 0.0f;
}


