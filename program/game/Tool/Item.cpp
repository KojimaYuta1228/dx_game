#include "Item.h"
#include"Map.h"
#include "../Character/Player.h"
#include"../Character/Enemy.h"
#include"../scene/gm_scene_play.h"
#include"DxLib.h"
#include "../Tool/gm_soundmanager.h"
#include"../Tool/Animation.h"

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
	LoadDivGraph("graphics/Resouce/image/use_efect/speed_up.png", 10, 10, 1, 120, 120, gh_speed_up);
	LoadDivGraph("graphics/Resouce/image/use_efect/speed_down.png", 10, 10, 1, 120, 120, gh_speed_down);

	/*i_anim_ = new Animation("graphics/Resouce/image/use_efect/speed_up.png", 10, 10, 1, 120, 120, DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2);
	liveAnim.emplace_back(i_anim_);
	i_anim_ = new Animation("graphics/Resouce/image/use_efect/speed_down.png", 10, 10, 1, 120, 120, DXE_WINDOW_WIDTH / 2, DXE_WINDOW_HEIGHT / 2);
	liveAnim.emplace_back(i_anim_);*/
}

Item::~Item()
{
}
void Item::SwithItemMove(int cnt_pos_)
{
	switch (cnt_pos_)
	{
	case 0:
		frag_player_speed_up = false;
		SoundManager::GetInstance()->SoundSe(SoundManager::SE::SPEED_UP);
		break;
	case 1:
		SoundManager::GetInstance()->SoundSe(SoundManager::SE::SPEED_DOWN);
		frag_enemy_speed_down = false;
		break;
	case 2:
		SoundManager::GetInstance()->SoundSe(SoundManager::SE::STRONG_TIME);
		scene_play_->frag_strong_time = false;
		break;
	case 3:
		SoundManager::GetInstance()->SoundSe(SoundManager::SE::USE_KEY);
		scene_play_->frag_can_goal = false;
		break;
	case 4:
		SoundManager::GetInstance()->SoundSe(SoundManager::SE::USE_COIN);
		break;
	default:
		break;
	}
}

void Item::ItemProcess(float delta_time)
{
	if (!frag_player_speed_up) {
		scene_play_->player_->base_move_speed = 3.0;
		cnt_player_speed_up -= delta_time;
		if (cnt_player_speed_up < 0) {
			scene_play_->player_->base_move_speed = 1.0;
			cnt_player_speed_up = 3.0;
			frag_player_speed_up = true;
		}
	}
	if (!frag_enemy_speed_down) {
		scene_play_->enemy_->base_move_speed = 0.1;
		cnt_enemy_speed_down -= delta_time;
		if (cnt_enemy_speed_down < 0) {
			scene_play_->enemy_->base_move_speed = 1.0;
			cnt_enemy_speed_down = 3.0;
			frag_enemy_speed_down = true;
		}
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
	//再生し終わったアニメーションがあったらリストから消してdeleteする
	//リストの一番最初の要素に矢印(イテレータ)を置く
	auto itr = liveAnim.begin();
	//リストのすべての要素に対して検索する
	for (int i = 0; i < liveAnim.size(); ++i) {
		//リストが空だったらfor文を抜ける
		if (liveAnim.empty())break;
		//もしイテレータが指しているアニメーションのisLiveがfalseなら(アニメーション再生が終わっていれば
		//中身のアニメーションのメモリを開放する
		//リストからそのアニメーションを排除してイテレータを次の要素に移す
		if ((*itr)->isLive == false) {
			delete (*itr);
			itr = liveAnim.erase(itr);
		}
		else {
			//もし生きているアニメーションを指していれば次の要素にイテレータを移す
			itr++;
		}
	}
}

void Item::Render(float delta_time)
{
	item_mesh->render(camera_);
	//アニメーションの描画
	for (auto anim : liveAnim) {
		anim->DrawAnimation(delta_time);
	}
	
}

float Item::CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)
{
	return std::sqrtf(((camera_pos2.x - pos1.x) * (camera_pos2.x - pos1.x)) + ((camera_pos2.y - pos1.y) * (camera_pos2.y - pos1.y)) + ((camera_pos2.z - pos1.z) * (camera_pos2.z - pos1.z)));
}


