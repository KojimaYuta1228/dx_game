#pragma once
#include<string>
#include"../../dxlib_ext/dxlib_ext.h"

class Animation
{
public:
	Animation(std::string ghPass, int sumNum, int widthNum, int heightNum, int width, int height,int anim_type, float x, float y);
	~Animation();

	//アニメーションの更新関数
	bool UpdateAnimation(const float deltatime);
	//アニメーションの描画関数
	void DrawAnimation(const float deltatime);

	void UseAnim(float delta_time);

	//画像の総枚数
	int sumAnimNum = 0;

	//足していく現在のタイマー
	float gfx_timer = 0;

	//描画中の配列番号

	int anim_frame = 0;

	//画像ハンドル配列
	int gh[10] = {};

	float anim_time_count = 0;
	//int anim_frame = 0;
	int anim_type = 0;
	int gfx_hdl[10][10] = { 0 };

	//Vector３(座標を使うとき)とstd::Vector(配列の大きさがわかんないとき)は違う
	tnl::Vector3 drawPos = {};

	//生存フラグ
	bool isLive = true;
private:

};



