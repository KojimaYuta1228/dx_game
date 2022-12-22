#pragma once
#include<vector>
#include<memory>
#include"CharacterBase.h"
#include "../../dxlib_ext/dxlib_ext.h"


class CharacterBase;
class ScenePlay;

class Enemy : public CharacterBase{
public:
	Enemy();
	~Enemy();

	

	void initialzie() override;
	void Update(float delta_time)override;
	void Render()override;
	float CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)override;

	void EnemyMove();
	int enemy_status_;
};