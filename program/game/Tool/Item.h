#pragma once
#include"../Character/CharacterBase.h"

class SceneBase;
class CharacterBase;
class ScenePlay;
class Player;
class Map;
class GachaGacha;

class Animation;

class Item : public CharacterBase
{
public:
	Item(){}
	Item(int id,int type, SceneBase* scene_base );
	~Item();
	void initialzie() override;
	void Update(float delta_time)override;
	void Render(float delta_time)override;
	float CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)override;
	void SwithItemMove(int item_num);//アイテムごとの動き
	void ItemProcess(float delta_time); //アイテムごとの細かい処理
	void ItemAnim(float delta_time);//アイテムのアニメーション
	int id_;
	int type_;
	float angle_ = 0;
	bool is_alive_ = true;
	std::list<dxe::Mesh*> item_boxs_;
	std::list<Animation*> liveAnim;
	dxe::Mesh* item_mesh;
	ScenePlay* scene_play_ = nullptr;	
	SceneBase* ref_scene_ = nullptr ;	
	Animation* i_anim_ = nullptr;
	
private:

	int random = 0;
	float cnt_player_speed_up = 3;
	float cnt_enemy_speed_down = 3;
	bool frag_player_speed_up = true;
	bool frag_enemy_speed_down = true;
	std::shared_ptr<Map> i_map_;
	std::shared_ptr<Player> i_player_;
	std::shared_ptr<ScenePlay> i_scene_play_;
	std::shared_ptr<GachaGacha> i_gacha_ = nullptr;
};


