#include "Enemy.h"
#include "../gm_manager.h"
#include "../scene/gm_scene_play.h"
#include "../model/gm_anim_sprite3d.h"
#include "../../dxlib_ext/dxlib_ext.h"

Enemy::Enemy()
{
	GameManager* mgr = GameManager::GetInstance();
	SceneBase* scene_base = mgr->getCurrentScene();
	ScenePlay* scene_play = dynamic_cast<ScenePlay*>(scene_base);
	if (scene_play) {
		camera_ = scene_play->GetCamera();
	}
	enSprite_ = new AnimSprite3D(camera_);
	enSprite_->regist(30, 32, "en1_walk_front", "graphics/Resouce/image/enemy/obake_back.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	enSprite_->regist(30, 32, "en1_walk_back", "graphics/Resouce/image/enemy/obake_front.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	enSprite_->regist(30, 32, "en1_walk_left", "graphics/Resouce/image/enemy/obake_left.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
	enSprite_->regist(30, 32, "en1_walk_right", "graphics/Resouce/image/enemy/obake_right.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);

	enSprite_->setCurrentAnim("en1_walk_front");
	pos_ = {0,20,0};
}

Enemy::~Enemy(){
	delete enSprite_;
}

void Enemy::initialzie()
{
}

void Enemy::Update(float delta_time)
{
	EnemyMove();
	distance_ = CameraDis(pos_, camera_->pos_);
	enSprite_->update(delta_time);
	
}

void Enemy::Render()
{
	enSprite_->pos_ = pos_;
	enSprite_->render(camera_);
	//DrawOBB(camera_, enSprite_->pos_, enSprite_->rot_, { 30,32,32 });
}

float Enemy::CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)
{
	return std::sqrtf(((camera_pos2.x - pos1.x) * (camera_pos2.x - pos1.x)) + ((camera_pos2.y - pos1.y) * (camera_pos2.y - pos1.y)) + ((camera_pos2.z - pos1.z) * (camera_pos2.z - pos1.z)));
}

void Enemy::EnemyMove()
{
	//ˆÚ“®§Œä
	enemy_status_ = tnl::GetXzRegionPointAndOBB(
		camera_->pos_,
		enSprite_->pos_,
		{30,32,32},
		enSprite_->rot_
	);

	std::string anim_names[4] = {
		"en1_walk_back","en1_walk_right","en1_walk_front","en1_walk_left"
	};
	enSprite_->setCurrentAnim(anim_names[enemy_status_]);

	tnl::Vector3 move = { 0,0,0 };
	tnl::Vector3 dir[4] = {
		camera_->front().xz(),
		camera_->right().xz(),
		camera_->back().xz(),
		camera_->left().xz(),
	};
	//Œü‚¢‚Ä‚¢‚é•ûŒü‚É‘Î‚µ‚Äsprite‚ðŒü‚¯‚é
	tnl::Input::RunIndexKeyDown([&](uint32_t idx) {
	move += dir[idx];
	}, eKeys::KB_UP, eKeys::KB_RIGHT, eKeys::KB_DOWN, eKeys::KB_LEFT);
	
	
		
	 prev_pos_ = pos_;
	 enSprite_->rot_.slerp(tnl::Quaternion::LookAtAxisY(pos_, pos_ + move), 0.3f);
	
	 /*if (tnl::Input::IsKeyDown(eKeys::KB_UP, eKeys::KB_RIGHT, eKeys::KB_DOWN, eKeys::KB_LEFT)) {
		 move.normalize();
		 enSprite_->rot_.slerp(tnl::Quaternion::LookAtAxisY(enPos_, enPos_ + move), 0.3f);
		 enPos_ += move * 2.0f;
	 }*/
	 //enPos_ += move * 2.0f;
}
