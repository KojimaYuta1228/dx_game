#pragma once
#include "../../dxlib_ext/dxlib_ext.h"

class AnimSprite3D;
class GmCamera;

class CharacterBase {
public:
	CharacterBase(){};
	virtual ~CharacterBase() {}
	virtual void initialzie() = 0;
	virtual void Update(float delta_time) {}
	virtual void Render(float delta_time) {}

	tnl::Vector3 prev_pos_;//前回座標
	tnl::Vector3 pos_;//当たり判定用座標

	AnimSprite3D* sprite_ = nullptr;
	AnimSprite3D* enSprite_[2] = {nullptr, nullptr};
	//AnimSprite3D* enSprite_hone_ = nullptr;
	GmCamera* camera_ = nullptr;
	static std::list<std::shared_ptr<CharacterBase>> objects;//弾を保存するための箱
	bool is_alive_ = true;//生存フラグ
	float distance_;
	float base_move_speed;
	
	virtual float CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2){
		return std::sqrtf(((camera_pos2.x - pos1.x) * (camera_pos2.x - pos1.x)) + ((camera_pos2.y - pos1.y) * (camera_pos2.y - pos1.y)) + ((camera_pos2.z - pos1.z) * (camera_pos2.z - pos1.z)));
	}
};
