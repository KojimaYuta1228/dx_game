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
	delete newAnim;
}


void ScenePlay::initialzie() {
	playsound();
	camera_ = GetCamera();
	SetObj();
	SoundManager::GetInstance()->SoundSe(SoundManager::SE::GET_START);
	mgr = GameManager::GetInstance();
	img_old_paper_ = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/old_paper_frame.png");
	img_controller = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/controller.png");
	if (mgr->i_gacha == nullptr) {
		mgr->i_gacha = std::make_shared<GachaGacha>();
	}
	item_mgr->gacha = mgr->i_gacha;
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
	camera_->target_ = player_->sprite_->pos_;
	player_->Update(delta_time);
	enemy_->Update(delta_time);
	item_mgr->Update(delta_time);
	Collision();
	RenderSort();
	PlayerState(delta_time);
	ScenePlaySound(delta_time);
	if (tnl::Input::IsPadDownTrigger(ePad::KEY_0)) {
		if (draw_controller_frag)draw_controller_frag = false;
		else draw_controller_frag = true;
	}
}

void ScenePlay::render()
{
	camera_->update();
	floor_->render(camera_);
	dome_->render(camera_);
	map_->Rander();
	for (auto& d_chara : draw_character_) {
		d_chara->Render(0.01666);
		item_mgr->Render();
	}
	/*if (enemy_->pos_.x < player_->pos_.x && enemy_->pos_.z < player_->pos_.z) {
		DrawTriangle(DXE_WINDOW_WIDTH / 2 - 10, DXE_WINDOW_HEIGHT / 2 - 100, DXE_WINDOW_WIDTH / 2 - 10, DXE_WINDOW_HEIGHT / 2 - 70, DXE_WINDOW_WIDTH / 2 + 10, DXE_WINDOW_HEIGHT / 2 - 100, 50, -1);
	}
	else if (enemy_->pos_.x < player_->pos_.x && enemy_->pos_.z > player_->pos_.z) {
		DrawTriangle(DXE_WINDOW_WIDTH / 2 - 10, DXE_WINDOW_HEIGHT / 2 - 100, DXE_WINDOW_WIDTH / 2 - 10, DXE_WINDOW_HEIGHT / 2 - 70, DXE_WINDOW_WIDTH / 2 + 10, DXE_WINDOW_HEIGHT / 2 - 70, 50, -1);
	}
	else if (enemy_->pos_.x > player_->pos_.x && enemy_->pos_.z > player_->pos_.z) {
		DrawTriangle(DXE_WINDOW_WIDTH / 2 - 10, DXE_WINDOW_HEIGHT / 2 - 70, DXE_WINDOW_WIDTH / 2 - 10, DXE_WINDOW_HEIGHT / 2 - 100, DXE_WINDOW_WIDTH / 2 + 10, DXE_WINDOW_HEIGHT / 2 - 70, 50, -1);
	}
	else if (enemy_->pos_.x > player_->pos_.x && enemy_->pos_.z < player_->pos_.z){
		DrawTriangle(DXE_WINDOW_WIDTH / 2 - 10, DXE_WINDOW_HEIGHT / 2 - 100, DXE_WINDOW_WIDTH / 2 + 10, DXE_WINDOW_HEIGHT / 2 - 70, DXE_WINDOW_WIDTH / 2 + 10, DXE_WINDOW_HEIGHT / 2 - 100, 50, -1);

}*/
	//DrawTriangle(DXE_WINDOW_WIDTH / 2 -10, DXE_WINDOW_HEIGHT / 2-70, DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2 -100, DXE_WINDOW_WIDTH / 2+10, DXE_WINDOW_HEIGHT / 2-70, 50,-1);
	//DrawTriangle(DXE_WINDOW_WIDTH / 2 - 10, DXE_WINDOW_HEIGHT / 2 - 70, enemy_->pos_.x-player_->pos_.x, enemy_->pos_.y-player_->pos_.y, DXE_WINDOW_WIDTH / 2 + 10, DXE_WINDOW_HEIGHT / 2 - 70, 50, -1);

	if (draw_controller_frag) {
		DrawRotaGraph(DXE_WINDOW_WIDTH / 2 + 230, DXE_WINDOW_HEIGHT / 2 + 200, 0.23, 0, img_controller, true);
		DrawStringEx(0, 200, -1, "Aボタン：そうさせつめいとじる");
		SetFontSize(15);
		DrawStringEx(DXE_WINDOW_WIDTH / 2 - 50, DXE_WINDOW_HEIGHT / 2 + 60, -1, "L1:スキル1");
		DrawStringEx(DXE_WINDOW_WIDTH / 2 + 300, DXE_WINDOW_HEIGHT / 2 + 70, -1, "R1:スキル2");
		DrawStringEx(DXE_WINDOW_WIDTH / 2 + 125, DXE_WINDOW_HEIGHT / 2 + 100, -1, "アイテムせんたく");
		DrawStringEx(DXE_WINDOW_WIDTH / 2 + 365, DXE_WINDOW_HEIGHT / 2 + 120, -1, "スキルチャージ");
		DrawStringEx(DXE_WINDOW_WIDTH / 2 + 380, DXE_WINDOW_HEIGHT / 2 + 230, -1, "アイテム使用");
		DrawStringEx(DXE_WINDOW_WIDTH / 2 + 380, DXE_WINDOW_HEIGHT / 2 + 160, -1, "ダッシュ");
		DrawStringEx(DXE_WINDOW_WIDTH / 2 + 80, DXE_WINDOW_HEIGHT / 2 + 330, -1, "移動");
	}
	else {
		DrawStringEx(0, 200, -1, "Aボタン：そうさせつめいひらく");
	}
	DrawBox(DXE_WINDOW_WIDTH / 2 , 20, DXE_WINDOW_WIDTH / 2 + 500, 50, -1, true);
	DrawStringEx(DXE_WINDOW_WIDTH / 2, 20, 0, "鍵を手に入れてゴールを目指せ");
}

void ScenePlay::playsound()
{
	SoundManager::GetInstance()->SoundBgm(SoundManager::BGM::PLAY);	
}

void ScenePlay::SetObj()
{
	camera_->camF = GmCamera::CAMERA_FREE_LOOK;
	camera_->pos_ = { 0, 150, -300 };
	map_ = std::make_shared<Map>();
	map_->initialzie();
	auto startPos = map_->GetRandomRoot();
	auto teleportationPos = map_->GetRandomRoot();
	auto startEnPos = map_->GetRandomRoot();
	enemy_ = std::make_shared<Enemy>(startEnPos);
	player_ = std::make_shared<Player>(startPos, teleportationPos);
	item_mgr = std::make_shared<ItemManager>(this);
	enemy_->map_ = map_;
	player_->map_ = map_;
	draw_character_.emplace_back(enemy_);
	draw_character_.emplace_back(player_);
	dome_ = dxe::Mesh::CreateSphere(1000);
	floor_ = dxe::Mesh::CreatePlane({ 1800,1800,0 });
	floor_->rot_q_ = tnl::Quaternion::RotationAxis({ 1, 0, 0 }, tnl::ToRadian(90));
	dome_->setTexture(dxe::Texture::CreateFromFile("graphics/Resouce/image/dangeon01.jpg"));
	floor_->setTexture(dxe::Texture::CreateFromFile("graphics/Resouce/image/dangeon_floor01.jpg"));
	dome_->pos_ = { 0,0,0 };
	floor_->pos_ = { 0,-25,0 };
}

void ScenePlay::Collision()
{
	for (int i = 0; i < Map::MEIRO_HEIGHT; i++) {
		for (int k = 0; k < Map::MEIRO_WIDTH; k++) {
			if (Map::maze[i][k] == static_cast<int>(Map::MAZESTATE::WALL)) {
				tnl::Vector3 box_pos = map_->map_chips_[i][k]->pos_;
				if (tnl::IsIntersectAABB(player_->pos_, { 32, 48, 32 }, box_pos, { BOX_SIZE, BOX_SIZE, BOX_SIZE })) {
					tnl::GetCorrectPositionIntersectAABB(player_->prev_pos_, { 32, 48, 32 }, box_pos, { BOX_SIZE, BOX_SIZE, BOX_SIZE }, player_->pos_);
				}
				if (tnl::IsIntersectAABB(enemy_->pos_, { 30,32,32 }, box_pos, { BOX_SIZE, BOX_SIZE, BOX_SIZE })) {
					tnl::GetCorrectPositionIntersectAABB(enemy_->pos_, { 30,32,32 }, box_pos, { BOX_SIZE, BOX_SIZE, BOX_SIZE }, enemy_->pos_);
				}
			}
			else if (Map::maze[i][k] == static_cast<int>(Map::MAZESTATE::GOAL)) {
				tnl::Vector3 goal_pos = map_->map_chips_[i][k]->pos_;
				if (tnl::IsIntersectAABB(player_->pos_, { 32, 48, 32 }, goal_pos, { BOX_SIZE, BOX_SIZE, BOX_SIZE })) {
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
	if (frag_strong_time) {
		if (tnl::IsIntersectAABB(player_->pos_, { 32,48,32 }, enemy_->pos_, { 30,32,32 })) {
			mgr->chengeScene(new GameOver());
			SoundManager::GetInstance()->SoundSe(SoundManager::SE::SE_SCREAM);
		}
	}
	for (auto items : item_mgr->spawn_Item_list) {
		if (tnl::IsIntersectAABB(player_->pos_, { 32,48,32 }, items->pos_, { 30,32,32 })) {
			items->is_alive_ = false;	
		}
	}
}

void ScenePlay::PlayerState(float delta_time)
{
	if (!frag_strong_time) {
		cnt_strong_time_ -= delta_time;
	}
	if (cnt_strong_time_ < 0){
		frag_strong_time = true;
		cnt_strong_time_ = 3;
	}
	if (player_->pos_.y == 450) {
		mgr->chengeScene(new SceneResult());
	}
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

void ScenePlay::ScenePlaySound(float delta_time)
{
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
}

inline void ScenePlay::RenderSort()
{
	draw_character_.sort([&](std::shared_ptr<CharacterBase> a, std::shared_ptr<CharacterBase> b) {
		return a->distance_ > b->distance_;
		});
}


