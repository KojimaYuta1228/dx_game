#pragma once
#include"../Character/CharacterBase.h"

class SceneBase;
class CharacterBase;
class Player;
class Map;

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
	void Render()override;
	float CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)override;
	void SwithItemMove();
	std::list<dxe::Mesh*> item_boxs_;
	dxe::Mesh* item_mesh;
	SceneBase* ref_scene_ = nullptr ;
private:

	int random = 0;
	std::shared_ptr<Map> i_map_;

};


