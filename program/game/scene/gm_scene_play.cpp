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
#include"../Tool/Bullet.h"
#include "../gm_main.h"
#include"../gm_manager.h"
#include"../Tool/ItemManager.h"
#include "../Tool/Item.h"
#include<algorithm>


ScenePlay::ScenePlay() {
}

ScenePlay::~ScenePlay() {	
	delete camera_;
}


void ScenePlay::initialzie() {
	playsound();

	camera_ = GetCamera();
	camera_->camF = GmCamera::CAMERA_FREE_LOOK;
	camera_->pos_ = { 0, 150, -300 };
	map_ = std::make_shared<Map>();
	map_->initialzie();
	
	auto startPos = map_->GetRandomRoot();
	auto teleportationPos = map_->GetRandomRoot();
	auto startEnPos = map_->GetRandomRoot();

	enemy_ = std::make_shared<Enemy>(startEnPos);
	enemy_->map_ = map_;
	player_ = std::make_shared<Player>(startPos,teleportationPos);
	player_->map_ = map_;
	//Listのhoge_にそれぞれのクラスの追加
	draw_character_.emplace_back(enemy_);
	draw_character_.emplace_back(player_);
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

	item_mgr = std::make_shared<ItemManager>( this );
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
	//三人称
		//tnl::Vector3 rot[2] = {
		//	{ 0, tnl::ToRadian(1.0), 0 },//各速度
		//	{ 0, -tnl::ToRadian(1.0), 0 },
		//};
		//tnl::Input::RunIndexPadDown([&](uint32_t idx) {
		//	frag_camera_rotate_ = false;
		//	//camera_->free_look_angle_xy_ += rot[idx];//三人称
		//	}, ePad::KEY_6, ePad::KEY_7);
		//tnl::Input::RunIndexKeyDown([&](uint32_t idx) {
		//	frag_camera_rotate_ = false;
		//	//camera_->free_look_angle_xy_ += rot[idx];//三人称
		//}, eKeys::KB_D, eKeys::KB_A);
	
	
	camera_->target_ = player_->sprite_->pos_;

	// 移動制御
	player_->Update(delta_time);
	enemy_->Update(delta_time);
	item_mgr->Update(delta_time);
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene(new SceneResult());
	}	
	Collision();
	RenderSort();	
	PlayerGoaled(delta_time);
	cnt_play_se_ghost_ += delta_time;
	cnt_play_se_laugh_ += delta_time;
	if (cnt_play_se_ghost_ >= 3) {
		SoundManager::GetInstance()->SoundSe(SoundManager::SE::ENEMY_GHOST);
		cnt_play_se_ghost_ = 0;
	}
	if (cnt_play_se_laugh_ >= 5) {
		SoundManager::GetInstance()->SoundSe(SoundManager::SE::ENEMY_LAUGH);
		cnt_play_se_laugh_ = 0;
	}
	if (player_->pos_.y == 450) {
		mgr->chengeScene(new SceneResult());
	}
	
	if (frag_strong_time) {
		if (tnl::IsIntersectAABB(player_->pos_, { 32,48,32 }, enemy_->pos_, { 30,32,32 })) {
			//mgr->chengeScene(new GameOver());
			SoundManager::GetInstance()->SoundSe(SoundManager::SE::SE_SCREAM);
		}
	}else if (!frag_strong_time) {
		cnt_strong_time -= delta_time;
	}
	if (cnt_strong_time < 0) {
		frag_strong_time = true;
		cnt_strong_time = 3;
	}
}

void ScenePlay::render()
{
	
	camera_->update();
	map_->Rander();
	floor_->render(camera_);
	dome_->render(camera_);
	for (auto& hoge : draw_character_) {
		hoge->Render(0.01666);
		item_mgr->Render();
	}
	//SetFontSize(20);
	/*DrawStringEx(60, 150, 0, "move_speed:%f",player_->move_speed);
	if (frag_can_goal) {
		DrawStringEx(60, 170, 0, "can_gosl_frag:true");
	}else{ DrawStringEx(60, 170, 0, "can_gosl_frag:false"); }*/
	//DrawRotaGraph(500 + 500 * sin(tnl::ToRadian(cnt_smoke)), 500 + 500 * sin(tnl::ToRadian(cnt_smoke)), 1.7 + 1.7 * sin(tnl::ToRadian(cnt_smoke)), 0, img_smoke,true);
	/*DrawStringEx(10, 20, 0, "MAXE_X :%d", static_cast<int>(player_->pos_.x));
	DrawStringEx(10, 40, 0, "MAXE_Z :%d", static_cast<int>(player_->pos_.z));
	DrawStringEx(10, 60, 0, "MASU STATUS :%d", map_->maze[player_->maze_pos_x_][player_->maze_pos_z_]);*///Playerのマップチップの座標
	//DrawStringEx(10, 60, -1, "MASU STATUS :%d", map_->maze[static_cast<int>(player_->pos_.x)][static_cast<int>(player_->pos_.z)]);
}

void ScenePlay::playsound()
{
	SoundManager::GetInstance()->SoundBgm(SoundManager::BGM::PLAY);	
}

void ScenePlay::Collision()
{
	//壁とプレイヤーとの当たり判定
	//壁とエネミーとの当たり判定
	//listでmap_chip_を管理
	for (int i = 0; i < Map::MEIRO_HEIGHT; i++) {
		for (int k = 0; k < Map::MEIRO_WIDTH; k++) {
			if (Map::maze[i][k] == static_cast<int>(Map::MAZESTATE::WALL)) {
				tnl::Vector3 box_pos = map_->map_chips_[i][k]->pos_;
				/*if (tnl::IsIntersectAABB(player_->pos_, { 32, 48, 32 }, box_pos, { boxSize, boxSize, boxSize })) {
					tnl::GetCorrectPositionIntersectAABB(player_->prev_pos_, { 32, 48, 32 }, box_pos, { boxSize, boxSize, boxSize }, player_->pos_);
				}*/
				if (tnl::IsIntersectAABB(enemy_->pos_, { 30,32,32 }, box_pos, { boxSize, boxSize, boxSize })) {
					tnl::GetCorrectPositionIntersectAABB(enemy_->pos_, { 30,32,32 }, box_pos, { boxSize, boxSize, boxSize }, enemy_->pos_);
				}
			}
			else if (Map::maze[i][k] == static_cast<int>(Map::MAZESTATE::GOAL)) {
				tnl::Vector3 goal_pos = map_->map_chips_[i][k]->pos_;
				if (tnl::IsIntersectAABB(player_->pos_, { 32, 48, 32 }, goal_pos, { boxSize, boxSize, boxSize })) {
					if (!frag_can_goal) {
						frag_cnt_timer_ = false;
						player_->frag_input_ = false;
						player_->frag_move_posY_ = false;
						SoundManager::GetInstance()->SoundSe(SoundManager::SE::GET_GOAL);
					}
				}
			}
		}
	}
	//プレイヤーとエネミーと当たり判定

	
	// アイテムマネージャーのリストを総チェック
	for (auto items : item_mgr->spawn_Item_list) {
		// Item と Player との当たり判定
		if (tnl::IsIntersectAABB(player_->pos_, { 32,48,32 }, items->pos_, { 30,32,32 })) {
			items->is_alive_ = false;	// アイテムを消す
		}
	}
}

void ScenePlay::PlayerGoaled(float delta_time)
{
	if (frag_cnt_timer_ == false) {
		if (player_->pos_.y < 80) {
			player_->pos_.y += 1;
		}
		if (player_->pos_.y >= 80 && player_->frag_move_posY_ == false) {
			player_->pos_.y += 0;
			player_->frag_move_posY_ = true;
			frag_cnt_timer_player_ = false;
		}
		if (frag_cnt_timer_player_ == false) {
			cnt_timer_player_ -= delta_time;
		}
		if (player_->pos_.y >= 80 && player_->frag_move_posY_ == true && cnt_timer_player_ <= 0) {
			player_->pos_.y += 10;
		}
	}
	
}

inline void ScenePlay::RenderSort()
{
	//List内の全てを計算しソートする
	draw_character_.sort([&](std::shared_ptr<CharacterBase> a, std::shared_ptr<CharacterBase> b) {
		return a->distance_ > b->distance_;
		});
}


