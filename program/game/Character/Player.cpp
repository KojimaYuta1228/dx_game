#include "Player.h"
#include"CharacterBase.h"
#include "../gm_manager.h"
#include "../scene/gm_scene_play.h"
#include "../model/gm_anim_sprite3d.h"
#include "../../dxlib_ext/dxlib_ext.h"
#include"../Tool/gm_soundmanager.h"
#include "../Tool/Map.h"

tnl::Vector3 telePos;
Player::Player(tnl::Vector3& startPos, tnl::Vector3& teleportationPos)
{
	GameManager* mgr = GameManager::GetInstance();
	SceneBase* scene_base = mgr->getCurrentScene();
	ScenePlay* scene_play = dynamic_cast<ScenePlay*>(scene_base);
	if (scene_play) {
		camera_ = scene_play->GetCamera();
	}

	sprite_ = new AnimSprite3D(camera_);

	sprite_->regist(32, 48, "walk_front", "graphics/c1_anim_up.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 4, 48, 0);
	sprite_->regist(32, 48, "walk_back", "graphics/c1_anim_down.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 4, 48, 0);	
	sprite_->regist(32, 48, "walk_left", "graphics/c1_anim_left.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 4, 48, 0);
	sprite_->regist(32, 48, "walk_right", "graphics/c1_anim_right.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 4, 48, 0);
	sprite_->setCurrentAnim("walk_front");

	/*----Playerの初期座標----*/
	auto x = startPos.x * 50;
	auto z = startPos.z * 50;
	pos_ = tnl::Vector3(x,0,z);
	start_pos_ = pos_;
	auto x1 = teleportationPos.x * 50;
	auto z1 = teleportationPos.z * 50;
	telePos = tnl::Vector3(x1, 0, z1);
	
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
	PlayerAnim();
	PlayerInput();
	//-----------------------------------------------
	//マップの座標の補正
	map_->goal_maze_pos_x = (pos_.x - (-12.5f * 50.0f)) / 50;
	map_->goal_maze_pos_y = 25 - (pos_.z - (-12.5f * 50.0f)) / 50;

	distance_ = CameraDis(pos_, camera_->pos_);
	sprite_->update(delta_time);
}

void Player::PlayerAnim()
{
	anim_pos_ = tnl::GetXzRegionPointAndOBB(
		camera_->pos_
		, sprite_->pos_
		, { 32, 48, 32 }
	, sprite_->rot_);

	std::string anim_names[4] = {
		"walk_back" , "walk_right","walk_front", "walk_left"
	};
	sprite_->setCurrentAnim(anim_names[anim_pos_]);
}

void Player::PlayerInput()
{
	tnl::Vector3 dir[4] = {
		camera_->front().xz(),
		camera_->right().xz(),
		camera_->back().xz(),
		camera_->left().xz(),
	};
	//----------------------移動----------------------//
	//左スティックによる移動
	move_v = tnl::Input::GetLeftStick();
	if (move_v.length() > 0.5f) {
		prev_pos_ = pos_;
		sprite_->rot_.slerp(tnl::Quaternion::LookAtAxisY(pos_, pos_ + move_v), 0.3f);
		pos_ += move_v;
	}
	//キー入力による移動
	tnl::Input::RunIndexKeyDown([&](uint32_t idx) {
		move_v += dir[idx];
		}, eKeys::KB_UP, eKeys::KB_RIGHT, eKeys::KB_DOWN, eKeys::KB_LEFT);

	
	//加速
	if (tnl::Input::IsPadDown(ePad::KEY_1) && move_v.length() > 0.5f) {
		pos_ += move_v * 10;
	}
	//瞬間移動
	if (tnl::Input::IsPadDownTrigger(ePad::KEY_4) && teleportation_cnt > 0) {
		teleportation_cnt--;
		pos_ = start_pos_;
	}
	if (tnl::Input::IsPadDownTrigger(ePad::KEY_5) && teleportation_cnt > 0) {
		teleportation_cnt--;
		pos_ = telePos;
	}

	/*----------------------------key----------------------------------*/
	if (tnl::Input::IsKeyDown(eKeys::KB_UP, eKeys::KB_RIGHT, eKeys::KB_DOWN, eKeys::KB_LEFT) && frag_input_ == true) {
		move_v.normalize();
		sprite_->rot_.slerp(tnl::Quaternion::LookAtAxisY(pos_, pos_ + move_v), 0.3f);
		frag_play_se_ = false;
		pos_ += move_v * 2.0f;
	}
	if (tnl::Input::IsKeyReleaseTrigger(eKeys::KB_UP, eKeys::KB_RIGHT, eKeys::KB_DOWN, eKeys::KB_LEFT)) {
		frag_play_se_ = true;
	}
	//加速
	if (tnl::Input::IsKeyDown(eKeys::KB_1)) {
		pos_ += move_v * 10;
	}
	
}

void Player::Render()
{
	sprite_->pos_ = pos_;
	sprite_->render(camera_);
}

float Player::CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)
{
	return std::sqrtf(((camera_pos2.x - pos1.x) * (camera_pos2.x - pos1.x)) + ((camera_pos2.y - pos1.y) * (camera_pos2.y - pos1.y)) + ((camera_pos2.z - pos1.z) * (camera_pos2.z - pos1.z)));
}
