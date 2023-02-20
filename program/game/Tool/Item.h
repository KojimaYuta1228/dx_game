#pragma once
#include"../Character/CharacterBase.h"

class SceneBase;
class CharacterBase;
class ScenePlay;
class Player;
class Map;
class Animation;

class Item : public CharacterBase
{
public:
	Item(){}
	Item(int id,int type, SceneBase* scene_base );
	~Item();

	int id_;
	int type_;
	bool is_alive_ = true;

	void initialzie() override;
	void Update(float delta_time)override;
	void Render(float delta_time)override;
	float CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)override;
	void SwithItemMove(int item_num);
	void ItemProcess(float delta_time);
	std::list<dxe::Mesh*> item_boxs_;
	dxe::Mesh* item_mesh;
	ScenePlay* scene_play_ = nullptr;
	float angle_ = 0;
	SceneBase* ref_scene_ = nullptr ;
	std::list<Animation*> liveAnim;
	Animation* i_anim_ = nullptr;
	float anim_time_count = 0;
	int anim_frame = 0;
	int anim_type = 0;
	int gfx_hdl[3][10] = { 0 };
	
	int gh_speed_up[10] = {};
	int gh_speed_down[10] = {};
private:

	int random = 0;
	float cnt_player_speed_up = 3;
	float cnt_enemy_speed_down = 3;
	bool frag_player_speed_up = true;
	bool frag_enemy_speed_down = true;
	std::shared_ptr<Map> i_map_;
	std::shared_ptr<Player> i_player_;
	std::shared_ptr<ScenePlay> i_scene_play_;
};


