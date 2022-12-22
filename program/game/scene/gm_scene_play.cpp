#include "../gm_manager.h"
#include "../Tool/gm_soundmanager.h"
#include "../model/gm_anim_sprite3d.h"
#include "gm_scene_play.h"
#include"gm_scene_title.h"
#include"gm_scene_gameover.h"
#include "gm_scene_result.h"
#include "../Character/Player.h"
#include "../Character/Enemy.h"
#include"../Character/CharacterBase.h"
#include"../Tool/Map.h"
#include"../gm_camera.h"
#include"../Tool/Animation.h"
#include<algorithm>


ScenePlay::ScenePlay() {
	
}

ScenePlay::~ScenePlay() {	
	delete camera_;
}


void ScenePlay::initialzie() {
	playsound();
	camera_ = GetCamera();
	//camera_->camF = GmCamera::CAMERA_TARGET;
	camera_->camF = GmCamera::CAMERA_FREE_LOOK;
	camera_->pos_ = { 0, 150, -300 };
	map_ = std::make_shared<Map>();
	map_->initialzie();
	enemy_ = std::make_shared<Enemy>();

	//auto startPos = map_->start_pos;
	auto startPos = map_->GetRandomRoot();

	player_ = std::make_shared<Player>(startPos);
	//Listのhoge_にそれぞれのクラスの追加
	hoge1_.emplace_back(enemy_);
	hoge1_.emplace_back(player_);
	//天井
	dome_ = dxe::Mesh::CreateSphere(1000);
	dome_->pos_ = { 0,0,0 };
	dome_->setTexture(dxe::Texture::CreateFromFile("graphics/Resouce/image/dangeon01.jpg"));
	//床の貼り付け
	floor_ = dxe::Mesh::CreatePlane({ 1800,1800,0 });
	floor_->rot_q_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	floor_->pos_ = { 0,-25,0 };
	floor_->setTexture(dxe::Texture::CreateFromFile("graphics/Resouce/image/dangeon_floor01.jpg"));

	img_note = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/old_later3.png");
	img_smoke = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/smoke.png");
	SoundManager::GetInstance()->SoundSe(SoundManager::SE::GET_START);
}

GmCamera* ScenePlay::GetCamera()
{
	if (!camera_) {
		camera_ = new GmCamera();
	}
	return camera_;
}


void ScenePlay::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();
	Animation* newAnim = nullptr;
	
	// カメラ制御
	//tnl::Vector3 mv = tnl::Input::GetMouseVelocity();
	//float length = mv.length();//マウスを動かしたときの距離をとる
	//mv.normalize();//正規化
	//if (length > 2.0f) {
	//	tnl::Vector3 v = { mv.x, -mv.y, mv.z };
	//	tnl::Vector3 front = camera_->front();
	//	tnl::Vector3 v_scr = tnl::Vector3::TransformCoord(v, camera_->c_rot);
	//	tnl::Vector3 axis = tnl::Vector3::Cross(front, v_scr);
	//	tnl::Vector3 front_xz = front.xz();
	//	float angle = front_xz.angle(front);
	//	bool is_look_up = (front.y > 0) ? true : false;
	//	bool is_mouse_up = (mv.y < 0) ? true : false;
	//	if ((is_look_up && is_mouse_up) || (!is_look_up && !is_mouse_up)) {
	//		if (tnl::ToDegree(angle) < 70) {
	//			camera_->c_rot = tnl::Quaternion::RotationAxis(axis, tnl::ToRadian(length * 0.1f));
	//		}
	//	}
	//	else {
	//		camera_->c_rot = tnl::Quaternion::RotationAxis(axis, tnl::ToRadian(length * 0.1f));
	//	}
	//}
	//tnl::Vector3 move_v = { 0,0,0 };
	//tnl::Vector3 dir[4] = {
	//	camera_->left().xz(),
	//	camera_->right().xz(),
	//	camera_->front().xz(),	
	//	camera_->back().xz(),
	//	
	//};
	
	//三人称
	
		tnl::Vector3 rot[4] = {

				{ 0, tnl::ToRadian(90), 0 },
				{ 0, -tnl::ToRadian(90), 0 },
				/*{ tnl::ToRadian(1.0f), 0, 0 },
				{ -tnl::ToRadian(1.0f), 0, 0 } */
		};
		tnl::Input::RunIndexKeyDownTrigger([&](uint32_t idx) {
			//move_v += dir[idx];
			camera_->free_look_angle_xy_ += rot[idx];
			//camera_->free_look_angle_xy_ += rot[idx];//三人称
			}, eKeys::KB_A, eKeys::KB_D);
	
	/*if (tnl::Input::IsKeyDown(eKeys::KB_Z)) {
		camera_->target_distance_ += 1.0f;
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_X)) {
		camera_->target_distance_ -= 1.0f;
	}*/
	camera_->target_ = player_->sprite_->pos_;

	// 移動制御
	player_->Update(delta_time);
	enemy_->Update(delta_time);
	//Debug必須
	//std::string hoge = "(target_distance=" + std::to_string(camera_->target_distance_)+")";
	//tnl::DebugTrace(hoge.c_str());
	//tnl::DebugTrace("\n");


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene(new SceneResult());
	}

	//壁とプレイヤーとの当たり判定
	//壁とエネミーとの当たり判定
	//listでmap_chip_を管理
	for (int i = 0; i < Map::MEIRO_HEIGHT; i++) {
		for (int k = 0; k < Map::MEIRO_WIDTH; k++) {
			if (Map::maze[i][k] == static_cast<int>(Map::MAZESTATE::WALL)) {
				tnl::Vector3 box_pos = map_->map_chips_[i][k]->pos_;

				if (tnl::IsIntersectAABB(player_->pos_, { 32, 48, 32 }, box_pos, { boxSize, boxSize, boxSize })) {
					tnl::GetCorrectPositionIntersectAABB(player_->prev_pos_, { 32, 48, 32 }, box_pos, { boxSize, boxSize, boxSize }, player_->pos_);
				}
				/*if (tnl::IsIntersectAABB(enemy_->enPos_, { 30,32,32 }, box_pos, { boxSize, boxSize, boxSize })) {
					tnl::GetCorrectPositionIntersectAABB(enemy_->enPos_, { 30,32,32 }, box_pos, { boxSize, boxSize, boxSize }, enemy_->enPos_);
				}*/
			}
			else if (Map::maze[i][k] == static_cast<int>(Map::MAZESTATE::GOAL)) {
				tnl::Vector3 goal_pos = map_->map_chips_[i][k]->pos_;
				if (tnl::IsIntersectAABB(player_->pos_, { 32, 48, 32 }, goal_pos, { boxSize, boxSize, boxSize })) {
					//tnl::GetCorrectPositionIntersectAABB(player_->prev_pos_, { 32, 48, 32 }, goal_pos, { 10, boxSize, 10 }, player_->pos_);
					timer_frag = false;
					sphare_frag = false;
					player_->input_frag = false;
					player_->move_posY_frag = false;
					SoundManager::GetInstance()->SoundSe(SoundManager::SE::GET_GOAL);
				}
			}
		}
	}
	//プレイヤーとエネミーと当たり判定
	if (tnl::IsIntersectAABB(player_->pos_, { 32,48,32 }, enemy_->pos_, { 30,32,32 })) {
		mgr->chengeScene(new GameOver());
		SoundManager::GetInstance()->SoundSe(SoundManager::SE::SE_SCREAM);
	}


	RenderSort();
	 A = player_->pos_.x - enemy_->pos_.x;
	 B = player_->pos_.z - enemy_->pos_.z;
	 C = sqrt(A * A + B * B);
	enemy_->pos_.x += (A / C) * 0.5f;
	enemy_->pos_.z += (B / C) * 0.5f;

	

	if (timer_frag == false) {
		if (player_->pos_.y < 80) {
			player_->pos_.y += 1;
		}
		if (player_->pos_.y >= 80 && player_->move_posY_frag == false) {
			player_->pos_.y += 0;
			player_->move_posY_frag = true;
			cnt_frag = false;
		}
		if (cnt_frag == false) {
			cnt_timer -= delta_time;
		}
		if (player_->pos_.y >= 80 && player_->move_posY_frag == true && cnt_timer <= 0) {
			player_->pos_.y += 10;
		}
	}
	if (player_->pos_.y == 450) {
		mgr->chengeScene(new SceneResult());
	}
	if (tnl::Input::IsKeyDown(eKeys::KB_Q) ) {
		img_note = false;
	}
	play_se_ghost_cnt += delta_time;
	play_se_laugh_cnt += delta_time;
	if (play_se_ghost_cnt >= 3) {
		SoundManager::GetInstance()->SoundSe(SoundManager::SE::ENEMY_GHOST);
		play_se_ghost_cnt = 0;
	}
	if (play_se_laugh_cnt >= 5) {
		SoundManager::GetInstance()->SoundSe(SoundManager::SE::ENEMY_LAUGH);
		play_se_laugh_cnt = 0;
	}
	cnt_smoke ++;

}

void ScenePlay::render()
{
	camera_->update();

	map_->Rander();
	floor_->render(camera_);
	dome_->render(camera_);

	//プレイヤーの描画
	/*if (CalcDistance(enemy_->enPos_, camera_->pos_) > CalcDistance(player_->pos_, camera_->pos_)) {

			enemy_->Render(); player_->Render();
	}
	else if (CalcDistance(enemy_->enPos_, camera_->pos_) < CalcDistance(player_->pos_, camera_->pos_)) {\
			player_->Render(); enemy_->Render();
	}*/
	//for文でitr
	/*for (auto itr = hoge1_.begin(); itr != hoge1_.end();itr++) {
		(*itr)->Render();
	}*/

	for (auto& hoge : hoge1_) {
		hoge->Render();
	}
	
	SetFontSize(20);
	if (img_note) {
		DrawRotaGraph(120, 90, 0.4, 0, img_note, true);
		DrawStringEx(60, 150, 0, "Q:CLOSE");
	}
	//DrawRotaGraph(500 + 500 * sin(tnl::ToRadian(cnt_smoke)), 500 + 500 * sin(tnl::ToRadian(cnt_smoke)), 1.7 + 1.7 * sin(tnl::ToRadian(cnt_smoke)), 0, img_smoke,true);
	
	/*DrawStringEx(10, 20, 0, "MAXE_X :%d", static_cast<int>(player_->pos_.x));
	DrawStringEx(10, 40, 0, "MAXE_Z :%d", static_cast<int>(player_->pos_.z));
	DrawStringEx(10, 60, 0, "MASU STATUS :%d", map_->maze[player_->maze_pos_x_][player_->maze_pos_z_]);*/
	//DrawStringEx(10, 60, -1, "MASU STATUS :%d", map_->maze[static_cast<int>(player_->pos_.x)][static_cast<int>(player_->pos_.z)]);

}

void ScenePlay::playsound()
{
	SoundManager::GetInstance()->SoundBgm(SoundManager::BGM::PLAY);
	
}

inline void ScenePlay::RenderSort()
{
	//List内の全てを計算しソートする
	hoge1_.sort([&](std::shared_ptr<CharacterBase> a, std::shared_ptr<CharacterBase> b) {
		return a->distance_ > b->distance_;
		});

}


