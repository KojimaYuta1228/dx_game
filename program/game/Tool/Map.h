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
	int SelectStartPoint(int MAXSIZE);//�X�^�[�g�n�_���擾
	void createMaze();//Update�̗p�̂���
	void printMaze(int w, int h);//�`��
	void createWall(int w, int h);//�}�b�v�̏�Ԃ�S��WALL�ɂ���
	Cell Dig(int startX, int startY);//�����@�镔��DIRECTION�ŕ����������_���Ō��߂Q�}�X���@��邩���肵�@��
	void SetPath(int setX, int setY);//Root�̍쐬�ƕۑ�
	void GetMapChipList(std::list<dxe::Mesh*> mc_list);//�N���[���������Ȃǂ�ǉ�
	void SetGoal(int goalX, int goalY);//���[�J�����W�ł̃S�[����ݒ�
	tnl::Vector3 GetRandomRoot();//�����_�����I�Ń��[�J�����W���擾����
	std::shared_ptr<Cell>GetStartCell();
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
	static const int MEIRO_WIDTH = 25;//���H�̉��̃T�C�Y
    static const int MEIRO_HEIGHT = 25;//���H�̏c�̃T�C�Y
	static int maze[MEIRO_HEIGHT][MEIRO_WIDTH];//���H�̊e�}�X�̏����i�[����z��
	
	GmCamera* camera_ = nullptr;//scene_play���ɂ���camera���g��
	GameManager* mgr = nullptr;
	dxe::Mesh* map_chips_[MEIRO_WIDTH][MEIRO_HEIGHT];
	std::vector<MyVec2i> Root_holder_;//�X�^�[�g�n�_��TP�p�̃��[�J�����W��ۑ����Ƃ����߂�vector
	std::vector<DIRECTION>directions;
	std::vector<std::shared_ptr<Cell>>StartCells;
	dxe::Mesh* ctrl_box_ = nullptr;
	std::list<dxe::Mesh*> field_boxs_;//�N���[������Box������list
	std::shared_ptr<dxe::Texture> tex = nullptr;
		

	int dis_x = 0;//startX���W��ۑ�
	int dis_y = 0;//startY���W��ۑ�
	int goal_x = 0;//goal_x���W��ۑ�
	int goal_y = 0;//goal_y���W��ۑ�

	int dis_en_x = 0;//startEnX���W��ۑ�
	int dis_en_y = 0;//startEnY���W��ۑ�

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


