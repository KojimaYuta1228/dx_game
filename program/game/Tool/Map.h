#pragma once
#include<vector>
#include<memory>
#include "../../dxlib_ext/dxlib_ext.h"

class Cell;
class ScenePlay;
class GmCamera;
class GameManager;

//int Map::maze[MEIRO_HEIGHT][MEIRO_WIDTH];
class Map {
public:
	Map();
	~Map();
	//迷路の横のサイズ
	static const int MEIRO_WIDTH = 25;
    //迷路の縦のサイズ
    static const int MEIRO_HEIGHT = 25;
	
	//scene_play内にあるcameraを使う
	GmCamera* camera_ = nullptr;
	GameManager* mgr = nullptr;

	//迷路の各マスの情報を格納する配列
	static int maze[MEIRO_HEIGHT][MEIRO_WIDTH];

	dxe::Mesh* map_chips_[MEIRO_WIDTH][MEIRO_HEIGHT];

	void initialzie();

	void Update();

	void Rander();

	int SelectStartPoint(int MAXSIZE);

	int SelectGoalPoint();

	void createMaze();

	void printMaze(int w, int h);

	void createWall(int w, int h);

	Cell Dig(int startX, int startY);

	void SetPath(int setX, int setY);

	void GetMapChipList(std::list<dxe::Mesh*> mc_list);

	void SetGoal(int goalX, int goalY);

	tnl::Vector3 GetRandomRoot();
	std::shared_ptr<Cell>GetStartCell();
	dxe::Mesh* ctrl_box_ = nullptr;
	std::list<dxe::Mesh*> field_boxs_;//クローンしたBoxを入れるlist

	//unit32_t→データ型とbitの指定
	//MAXを書くことで後々for文で回しやすくする
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
	
	std::vector<DIRECTION>directions;
	std::vector<std::shared_ptr<Cell>>StartCells;

	int dis_x = 0;//startX座標を保存
	int dis_y = 0;//startY座標を保存
	int goal_x = 0;//startX座標を保存
	int goal_y = 0;//startY座標を保存

	int dis_en_x = 0;//startEnX座標を保存
	int dis_en_y = 0;//startEnY座標を保存
	const float boxSize = 50;//boxの1辺の大きさ
	tnl::Vector3 start_pos;
	tnl::Vector3 goal_pos_;

	tnl::Vector3 start_en_pos;

	//迷路の分岐回数
	const int MAXREPEAT = 100;
	//迷路の分岐のカウント
	int cnt_repeat_ = 0;

};

class Cell
{
public:
	Cell(int setX, int setY);
	~Cell();

	int x;
	int y;

private:

};

