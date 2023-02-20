#include "Player.h"
#include"CharacterBase.h"
#include "../gm_manager.h"
#include "../scene/gm_scene_play.h"
#include "../model/gm_anim_sprite3d.h"
#include "../../dxlib_ext/dxlib_ext.h"
#include"../Tool/gm_soundmanager.h"
#include "../Tool/Map.h"
#include"../Tool/Animation.h"

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
	emp_stam_ber = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/emp_stam_ber.png");
	/*----Playerの初期座標----*/
	auto x = startPos.x * 50;
	auto z = startPos.z * 50;
	pos_ = tnl::Vector3(x,0,z);
	start_pos_ = pos_;
	auto x1 = teleportationPos.x * 50;
	auto z1 = teleportationPos.z * 50;
	telePos = tnl::Vector3(x1, 0, z1);
	base_move_speed = 1.0;
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
	if (pos_.y > 50) {
		i_anim_ = new Animation("graphics/Resouce/image/use_efect/wing.png", 10, 10, 1, 188, 150, DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2);
		liveAnim.emplace_back(i_anim_);
	}
	PlayerAnim(delta_time);
	PlayerInput(delta_time);	
	//-----------------------------------------------
	//マップの座標の補正
	map_->goal_maze_pos_x = (pos_.x - (-12.5f * 50.0f)) / 50;
	map_->goal_maze_pos_y = 25 - (pos_.z - (-12.5f * 50.0f)) / 50;

	distance_ = CameraDis(pos_, camera_->pos_);
	sprite_->update(delta_time);

}

void Player::PlayerAnim(float delta_time)
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
	//アニメーションの更新
	for (auto anim : liveAnim) {
		//アニメーションが終わっていれば
		anim->UpdateAnimation(delta_time);
	}
	//再生し終わったアニメーションがあったらリストから消してdeleteする
	auto itr = liveAnim.begin();
	while (itr != liveAnim.end()) {
		if ((*itr)->isLive == false) {
			delete (*itr);
			itr = liveAnim.erase(itr);
		}
		else {
			itr++;
		}
	}
}

void Player::PlayerInput(float delta_time)
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
		pos_ += move_v * base_move_speed;
	}
	//キー入力による移動
	tnl::Input::RunIndexKeyDown([&](uint32_t idx) {
		move_v += dir[idx];
		}, eKeys::KB_UP, eKeys::KB_RIGHT, eKeys::KB_DOWN, eKeys::KB_LEFT);

	
	//加速//コントローラーB
	if (tnl::Input::IsPadDown(ePad::KEY_1) && move_v.length() > 0.5f && bar_width > 0) {
		bar_width -= decrease_amount; //バーの幅を減らす
		pos_ += move_v * move_speed;
	}
    if (max_staminum > bar_width && !tnl::Input::IsPadDown(ePad::KEY_1) && move_v.length() < 0.5f) {
		bar_width += decrease_amount;
	}
	//瞬間移動
	//コントローラーY
	if (tnl::Input::IsPadDown(ePad::KEY_3) && frag_chant_tp) {
		cnt_chant_tp += delta_time;
	}
	if (cnt_chant_tp < 3 && cnt_chant_tp > 2.5) {
		i_anim_ = new Animation("graphics/Resouce/image/use_efect/shineFix.png", 10, 10, 1, 192, 192, DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2);
		liveAnim.emplace_back(i_anim_);
	}
	if (cnt_chant_tp > 3) {
		frag_chant_tp = false;
	}

	if (!frag_chant_tp) {
		if (tnl::Input::IsPadDownTrigger(ePad::KEY_4) && frag_tp ) {
			SoundManager::GetInstance()->SoundSe(SoundManager::SE::TELEPORT);
			pos_ = start_pos_;
			frag_tp = false;
		}
		if (tnl::Input::IsPadDownTrigger(ePad::KEY_5) && frag_tp) {
			SoundManager::GetInstance()->SoundSe(SoundManager::SE::TELEPORT);
			pos_ = telePos;
			frag_tp = false;
		}
	}
	if (!frag_tp) {
		cnt_frag_tp -= delta_time;
		if (cnt_frag_tp < 0) {
			frag_tp = true;
			frag_chant_tp = true;
			cnt_chant_tp = 0;
			cnt_frag_tp = 5;
		}
	}
	if (tnl::Input::IsPadDownTrigger(ePad::KEY_3)) {
		SoundManager::GetInstance()->SoundSe(SoundManager::SE::CHARGE);
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
	if (tnl::Input::IsKeyDown(eKeys::KB_1) ) {
		pos_ += move_v * 10;
	}
	
}

void Player::Render(float delta_time)
{
	for (auto anim : liveAnim) {
		anim->DrawAnimation(delta_time);
	}
	sprite_->pos_ = pos_;
	sprite_->render(camera_);
	
	SetFontSize(25);
	if (tnl::Input::IsPadDown(ePad::KEY_3) && cnt_chant_tp <= 3) {
		DrawStringEx(0, 130, -1.0, "スキルチャージ中");
	}
	else if (frag_tp && cnt_chant_tp > 3) {
		DrawStringEx(0, 130, -1.0, "スキルチャージ済");
	}
    else if (!frag_tp ) {
		DrawStringEx(0, 130, -1.0, "スキルクールダウン中");
	}
	else if (frag_tp && !tnl::Input::IsPadDown(ePad::KEY_3)) {
		DrawStringEx(0, 130, -1.0, "スキルチャージ可能");
	}

	DrawExtendGraph(bar_x, bar_y, bar_x + 350, bar_y + bar_height, emp_stam_ber, true);
	DrawBox(bar_x, bar_y, bar_x + bar_width, bar_y + bar_height, GetColor(255, 165, 0), TRUE); // バーを描画する		
	SetFontSize(20);
	DrawStringEx(5, bar_y, 0, "スタミナ");
}


float Player::CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)
{
	return std::sqrtf(((camera_pos2.x - pos1.x) * (camera_pos2.x - pos1.x)) + ((camera_pos2.y - pos1.y) * (camera_pos2.y - pos1.y)) + ((camera_pos2.z - pos1.z) * (camera_pos2.z - pos1.z)));
}
