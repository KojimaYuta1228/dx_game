#include "Enemy.h"
#include"CharacterBase.h"
#include "../gm_manager.h"
#include "../scene/gm_scene_play.h"
#include "../model/gm_anim_sprite3d.h"
#include "../../dxlib_ext/dxlib_ext.h"
#include"../Tool/gm_soundmanager.h"
#include "../Tool/Aster.h"


Enemy::Enemy(tnl::Vector3& startEnPos)
{
	GameManager* mgr = GameManager::GetInstance();
	SceneBase* scene_base = mgr->getCurrentScene();
	ScenePlay* scene_play = dynamic_cast<ScenePlay*>(scene_base);
	if (scene_play) {
		camera_ = scene_play->GetCamera();
	}



	for (int i = 0; i < 1; i++) {
		enSprite_[i] = new AnimSprite3D(camera_);
		
		enSprite_[i]->regist(30, 32, "en_walk_front", "graphics/Resouce/image/enemy/obake_back.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
		enSprite_[i]->regist(30, 32, "en_walk_back", "graphics/Resouce/image/enemy/obake_front.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
		enSprite_[i]->regist(30, 32, "en_walk_left", "graphics/Resouce/image/enemy/obake_left.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
		enSprite_[i]->regist(30, 32, "en_walk_right", "graphics/Resouce/image/enemy/obake_right.png", tnl::SeekUnit::ePlayMode::REPEAT, 1.0f, 3, 32, 0);
		enSprite_[i]->setCurrentAnim("en_walk_front");
	}	
	/*----Enemyの初期座標----*/
	 x = startEnPos.x * 50;
	 z = startEnPos.z * 50;
	pos_ = tnl::Vector3(x, 10, z);
	
	move_target_pos_ = pos_;
	base_move_speed = 1.0;
}

Enemy::~Enemy(){
	for (int i = 0; i < 1; i++) {
		delete enSprite_[i];
	}
}

void Enemy::initialzie()
{
}

void Enemy::Update(float delta_time)
{
	SetAster(delta_time);
	EnemyMove();
	distance_ = CameraDis(pos_, camera_->pos_);
	enSprite_[0]->update(delta_time);
}

void Enemy::Render()
{
	enSprite_[0]->pos_ = pos_;
	enSprite_[0]->render(camera_);
	//DrawOBB(camera_, enSprite_->pos_, enSprite_->rot_, { 30,32,32 });
}

float Enemy::CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)
{
	return std::sqrtf(((camera_pos2.x - pos1.x) * (camera_pos2.x - pos1.x)) + ((camera_pos2.y - pos1.y) * (camera_pos2.y - pos1.y)) + ((camera_pos2.z - pos1.z) * (camera_pos2.z - pos1.z)));
}

void Enemy::SetAster(float delta_time)
{
	search_time_count_ += delta_time;
	if (search_time_count_ > 0.25f) {

		Node nodes[Map::MEIRO_HEIGHT][Map::MEIRO_WIDTH];

		map_->start_maze_pos_x = (pos_.x - (-12.5f * 50.0f)) / 50;
		map_->start_maze_pos_y = 25 - (pos_.z - (-12.5f * 50.0f)) / 50;

		int sx = map_->start_maze_pos_x;
		int sy = map_->start_maze_pos_y;
		int gx = map_->goal_maze_pos_x;
		int gy = map_->goal_maze_pos_y;


		for (int y = 0; y < Map::MEIRO_HEIGHT; ++y) {
			for (int x = 0; x < Map::MEIRO_WIDTH; ++x) {
				nodes[y][x].pos.x = x;
				nodes[y][x].pos.y = y;

				nodes[y][x].status = map_->maze[y][x];
				if (nodes[y][x].status == (int)Map::MAZESTATE::GOAL) {
					nodes[y][x].status = (int)Map::MAZESTATE::ROOT;
				}
				if (nodes[y][x].status == (int)Map::MAZESTATE::START) {
					nodes[y][x].status = (int)Map::MAZESTATE::ROOT;
				}

				nodes[y][x].score = 0;
				nodes[y][x].cost_guess = abs(gx - x) + abs(gy - y);
				nodes[y][x].cost_real = 0;
				nodes[y][x].parent = nullptr;
			}
		}

		nodes[sy][sx].status = (int)Map::MAZESTATE::ASTART;
		nodes[gy][gx].status = (int)Map::MAZESTATE::AGOAL;

		// 二次元配列のアドレスを引数に渡す為の準備
		Node* tmp_nodes[Map::MEIRO_HEIGHT];
		for (int i = 0; i < Map::MEIRO_HEIGHT; ++i) {
			tmp_nodes[i] = nodes[i];
		}

		// 経路探索実行
		std::vector<Node*> route;
		bool is_success = aster(tmp_nodes, &nodes[sy][sx], &route);
		route_player_.resize(route.size());
		for (int i = route.size() - 1; i >= 0; --i) {
			route_player_[route.size() - 1 - i] = route[i];
		}

		if (route.size() > 1) {
			float fx = route_player_[1]->pos.x;
			float fy = route_player_[1]->pos.y;
			move_target_pos_.x = (fx * 50) - (12.5f * 50) + 25;
			move_target_pos_.z = (-fy * 50) + (12.5f * 50) - 25;
		}

		search_time_count_ = 0;
	}
}

void Enemy::EnemyMove()
{
	//移動制御
	//向いている方向に対してspriteを向ける
	int enemy_status_ = tnl::GetXzRegionPointAndOBB(
		camera_->pos_,
		enSprite_[0]->pos_,
		{30,32,32},
		enSprite_[0]->rot_
	);
	

	std::string anim_names[4] = {
		"en_walk_back","en_walk_right","en_walk_front","en_walk_left"
	};
	std::string anim_names01[4] = {
		"en2_walk_back","en2_walk_right","en2_walk_front","en2_walk_left"
	};

	tnl::Vector3 move = { 0,0,0 };
	tnl::Vector3 dir[4] = {
		camera_->front().xz(),
		camera_->right().xz(),
		camera_->back().xz(),
		camera_->left().xz(),
	};
	
	tnl::Vector3 move_n = tnl::Vector3::Normalize(move_target_pos_ - pos_);
	pos_ += move_n * base_move_speed;


	int t = tnl::GetXzRegionPointAndOBB(
		camera_->pos_
		, enSprite_[0]->pos_
		, { 32, 48, 32 }
	, enSprite_[0]->rot_);
	

	enSprite_[0]->setCurrentAnim(anim_names[t]);
	//enSprite_hone_->setCurrentAnim(anim_names01[t]);
	prev_pos_ = pos_;
	enSprite_[0]->rot_.slerp(tnl::Quaternion::LookAtAxisY(pos_, move_target_pos_), 0.3f);
	//enSprite_hone_->rot_.slerp(tnl::Quaternion::LookAtAxisY(pos_, move_target_pos_), 0.3f);
	

}
