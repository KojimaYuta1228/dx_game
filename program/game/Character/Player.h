#pragma once
#include<vector>
#include<memory>
#include "../../dxlib_ext/dxlib_ext.h"
#include"CharacterBase.h"

class ScenePlay;
class Map;
class CharacterBase;
class Animation;

class Player :public CharacterBase{
public :
	Player(tnl::Vector3& startPos, tnl::Vector3& teleportationPos);
	~Player();

	void initialzie() override;
	void Update(float delta_time)override;
	void PlayerAnim(float delta_time);//Playerのアニメーション
	void PlayerInput(float delta_time);//Playerの入力
	void Render(float delta_time)override;
	
	float CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)override;

	std::shared_ptr<Map> map_ = nullptr; 
	std::list<Animation*> liveAnim;
	Animation* i_anim_ = nullptr;

	//mapの座標
	int maze_pos_x_ = 0 ;
	int maze_pos_z_ = 0;
	
	bool frag_input_ = true;//入力を受け付けるかどうかを判定するためのフラグ
	bool frag_move_posY_ = true;//ゴール時のPlayerの動きをいじるためのフラグ
	bool frag_play_se_ = true;//seを鳴らすためのフラグ
	bool frag_tp = true;//TPするためのフラグ
	bool frag_chant_tp = true;//詠唱完了か判別するためのフラグ

	float cnt_frag_tp = 5;//次の詠唱開始までの時間
	float cnt_chant_tp = 0;//TPまでの詠唱時間ようカウント

	
	tnl::Vector3 move_v;//速度を加算減算するためのVector3
	tnl::Vector3 start_pos_;//スタート地点
	tnl::Vector3 telePos;//テレポート地点
	float move_speed = 1.1;//ダッシュ速度	
	int anim_pos_;//アニメスプライトの設定用
	int max_staminum = 350;//スタミナ最大値
	int emp_stam_ber = 0;//画像ハンドル
	int bar_width = 3500; // バーの初期幅
	int bar_height = 20; // バーの高さ
	int bar_x = 0; // バーのX座標
	int bar_y = 100; // バーのY座標
	int decrease_amount = 2; // 減少量
	int increase_amount = 1; // 増加量
};