#pragma once
#include"../Character/CharacterBase.h"

class CharacterBase;

class Item : public CharacterBase
{
public:
	Item(int id,int type);
	~Item();

	int id_;
	int type_;
	bool is_alive_ = true;

	void initialzie() override;
	void Update(float delta_time)override;
	void Render()override;
	float CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)override;
	void SwithItemMove();

private:

};


