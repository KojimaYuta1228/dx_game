#pragma once
#include<vector>
#include<memory>
#include"CharacterBase.h"
#include "../../dxlib_ext/dxlib_ext.h"


class CharacterBase;
class ScenePlay;
class Map;
class Node;

class Enemy : public CharacterBase{
public:
	Enemy(tnl::Vector3& startEnPos);
	~Enemy();	

	void initialzie() override;
	void Update(float delta_time)override;
	void Render(float delta_time)override;
	float CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)override;
	void SetAster(float delta_time);//Asterに組み込む
	void EnemyMove();
	std::shared_ptr<Map> map_ = nullptr;

	float search_time_count_ = 0;//Asterの更新頻度
	tnl::Vector3 move_target_pos_;//ターゲットのpos
	std::vector<Node*> route_player_;//playerの通った道
	int sx;//ワールド座標でのスタートx
	int sy;//ワールド座標でのスタートy
	int gx;//ワールド座標でのゴールx
	int gy;//ワールド座標でのゴールy

	float x;//初期座標X
	float z;//初期座標Z
	bool is_success;//asterの成功かどうかの判定
	tnl::Vector3 move_n;
		
};