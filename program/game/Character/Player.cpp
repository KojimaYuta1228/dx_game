#include "Player.h"
#include"CharacterBase.h"
#include "../gm_manager.h"
#include "../scene/gm_scene_play.h"
#include "../model/gm_anim_sprite3d.h"
#include "../../dxlib_ext/dxlib_ext.h"
#include"../Tool/gm_soundmanager.h"


Player::Player(tnl::Vector3& startPos)
{
	GameManager* mgr = GameManager::GetInstance();
	SceneBase* scene_base = mgr->getCurrentScene();
	ScenePlay* scene_play = dynamic_cast<ScenePlay*>(scene_base);
	map_ = std::make_shared<Map>();
	if (scene_play) {
		camera_ = scene_play->GetCamera();
	}

	sprite_ = new AnimSprite3D(camera_);
	sprite_->regist(32, 48, "walk_front", "graphics/c1_anim_up.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 4, 48, 0);
	sprite_->regist(32, 48, "walk_back", "graphics/c1_anim_down.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 4, 48, 0);
	
	sprite_->regist(32, 48, "walk_left", "graphics/c1_anim_left.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 4, 48, 0);
	sprite_->regist(32, 48, "walk_right", "graphics/c1_anim_right.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 4, 48, 0);

	sprite_->setCurrentAnim("walk_front");

	auto x = startPos.x * 50;
	auto z = startPos.z * 50;

	pos_ = tnl::Vector3(x,0,z);
	//pos_ = { (-(12 * 50)) + startPos.x,0,(12 * 50) - startPos.z };
	//pos_ += {50, 0, 50};
	//pos_ += {1250,0,1250};

}

Player::~Player()
{
	delete sprite_;
}

void Player::initialzie()
{
}

void Player::Update(float delta_time)
{

	// ˆÚ“®§Œä

	int t = tnl::GetXzRegionPointAndOBB(
		camera_->pos_
		, sprite_->pos_
		, { 32, 48, 32 }
	, sprite_->rot_);

	std::string anim_names[4] = {
		"walk_back" , "walk_right","walk_front", "walk_left"
	};
	sprite_->setCurrentAnim(anim_names[t]);

	tnl::Vector3 move_v = { 0,0,0 };
	tnl::Vector3 dir[4] = {
		camera_->front().xz(),
		camera_->right().xz(),
		camera_->back().xz(),
		camera_->left().xz(),
	};
	tnl::Input::RunIndexKeyDown([&](uint32_t idx) {
		move_v += dir[idx];
		},  eKeys::KB_UP, eKeys::KB_RIGHT, eKeys::KB_DOWN, eKeys::KB_LEFT);

	prev_pos_ = pos_;
	//ˆÚ“®
	if (tnl::Input::IsKeyDown(eKeys::KB_UP, eKeys::KB_RIGHT, eKeys::KB_DOWN, eKeys::KB_LEFT) && input_frag == true) {
		move_v.normalize();
		sprite_->rot_.slerp(tnl::Quaternion::LookAtAxisY(pos_, pos_ + move_v), 0.3f);
		play_se_frag = false;
		pos_ += move_v * 2.0f;
	}
	if (tnl::Input::IsKeyReleaseTrigger(eKeys::KB_UP, eKeys::KB_RIGHT, eKeys::KB_DOWN, eKeys::KB_LEFT)) {
		play_se_frag = true;
	}

	//‰Á‘¬
	if (tnl::Input::IsKeyDown(eKeys::KB_1)) {
		pos_ += move_v * 10;
	}
	

	maze_pos_x_ = (pos_.x - (-12.5f * 50.0f)) / 50;
	maze_pos_z_ = 25 - (pos_.z - (-12.5f * 50.0f)) / 50;

	distance_ = CameraDis(pos_, camera_->pos_);
	sprite_->update(delta_time);


}

void Player::Render()
{
	sprite_->pos_ = pos_;
	sprite_->render(camera_);
	//DrawOBB(camera_, sprite_->pos_, sprite_->rot_, { 32, 48, 32 });
}

float Player::CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)
{
	return std::sqrtf(((camera_pos2.x - pos1.x) * (camera_pos2.x - pos1.x)) + ((camera_pos2.y - pos1.y) * (camera_pos2.y - pos1.y)) + ((camera_pos2.z - pos1.z) * (camera_pos2.z - pos1.z)));
}
