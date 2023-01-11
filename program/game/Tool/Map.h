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
	//���H�̉��̃T�C�Y
	static const int MEIRO_WIDTH = 25;
    //���H�̏c�̃T�C�Y
    static const int MEIRO_HEIGHT = 25;
	
	//scene_play���ɂ���camera���g��
	GmCamera* camera_ = nullptr;
	GameManager* mgr = nullptr;

	//���H�̊e�}�X�̏����i�[����z��
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
	std::list<dxe::Mesh*> field_boxs_;//�N���[������Box������list

	//unit32_t���f�[�^�^��bit�̎w��
	//MAX���������ƂŌ�Xfor���ŉ񂵂₷������
	enum class DIRECTION :uint32_t {
		UP,
		RIGHT,
		DOWN,
		LEFT,
		MAX
	};	

	//�}�b�v�̃X�e�[�^�X
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

	int dis_x = 0;//startX���W��ۑ�
	int dis_y = 0;//startY���W��ۑ�
	int goal_x = 0;//startX���W��ۑ�
	int goal_y = 0;//startY���W��ۑ�

	int dis_en_x = 0;//startEnX���W��ۑ�
	int dis_en_y = 0;//startEnY���W��ۑ�
	const float boxSize = 50;//box��1�ӂ̑傫��
	tnl::Vector3 start_pos;
	tnl::Vector3 goal_pos_;

	tnl::Vector3 start_en_pos;

	//���H�̕����
	const int MAXREPEAT = 100;
	//���H�̕���̃J�E���g
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

