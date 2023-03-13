#pragma once
#include<vector>
#include<memory>
#include "../../dxlib_ext/dxlib_ext.h"

class Cell;
class ScenePlay;
class GmCamera;
class GameManager;

class MyVec2i {
public:
	MyVec2i() {}
	MyVec2i(const int x, const int y) : x_(x), y_(y) {}
	int x_;
	int y_;
};

class Map {
public:
	Map();
	~Map();

	void initialzie();
	void Rander();
	int SelectStartPoint(int MAXSIZE);//スタート地点を取得
	void createMaze();//Updateの用のもの
	void printMaze(int w, int h);//描画
	void createWall(int w, int h);//マップの状態を全てWALLにする
	Cell Dig(int startX, int startY);//穴を掘る部分DIRECTIONで方向をランダムで決め２マスずつ掘れるか判定し掘る
	void SetPath(int setX, int setY);//Rootの作成と保存
	void GetMapChipList(std::list<dxe::Mesh*> mc_list);//クローンした箱などを追加
	void SetGoal(int goalX, int goalY);//ローカル座標でのゴールを設定
	tnl::Vector3 GetRandomRoot();//ランダム抽選でローカル座標を取得する
	std::shared_ptr<Cell>GetStartCell();
	enum class DIRECTION :uint32_t {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		MAX
	};

	//マップのステータス
	enum class MAZESTATE :uint32_t {
		ROOT,
		WALL,
		NONE,
		OPEN,
		CLOSED,
		START,
		GOAL,
		ASTART,
		AGOAL,
		MAX
	};
	static const int MEIRO_WIDTH = 25;//迷路の横のサイズ
    static const int MEIRO_HEIGHT = 25;//迷路の縦のサイズ
	static int maze[MEIRO_HEIGHT][MEIRO_WIDTH];//迷路の各マスの情報を格納する配列
	
	GmCamera* camera_ = nullptr;//scene_play内にあるcameraを使う
	GameManager* mgr = nullptr;
	dxe::Mesh* map_chips_[MEIRO_WIDTH][MEIRO_HEIGHT];
	std::vector<MyVec2i> Root_holder_;//スタート地点やTP用のローカル座標を保存しとくためのvector
	std::vector<DIRECTION>directions;
	std::vector<std::shared_ptr<Cell>>StartCells;
	dxe::Mesh* ctrl_box_ = nullptr;
	std::list<dxe::Mesh*> field_boxs_;//クローンしたBoxを入れるlist
	std::shared_ptr<dxe::Texture> tex = nullptr;
		

	int dis_x = 0;//startX座標を保存
	int dis_y = 0;//startY座標を保存
	int goal_x = 0;//goal_x座標を保存
	int goal_y = 0;//goal_y座標を保存

	int dis_en_x = 0;//startEnX座標を保存
	int dis_en_y = 0;//startEnY座標を保存

	int start_maze_pos_x = 0;
	int start_maze_pos_y = 0;
	int goal_maze_pos_x = 0;
	int goal_maze_pos_y = 0;

	tnl::Vector3 start_en_pos;
};

class Cell
{
public:
	Cell(int setX, int setY);

	int x;
	int y;
};


