//#pragma once
//#include <stdlib.h>
//#include <iostream>
//#include <stdio.h>
//#include <vector>
//#include<map>
//#include <tchar.h>
//
//class Map;
//class CharacterBase;
//class Enemy;
//
//
//typedef struct {
//	int x;
//	int y;
//	int px;
//	int py;
//	int cost;
//} anode;
//
//
//map <int, anode> mapOpen;
//map <int, anode> mapClose;
//
//
//class Aster {
//public:
//	Aster();
//	~Aster();
//
//	void initialzie();
//
//	int GetDistance(int from_x, int from_y, int to_x, int to_y);
//
//	anode* SetNode(anode* n, int nx, int ny, int npx, int npy, int ncost);
//
//	// �w�肵���n�_����X�^�[�g�n�_�܂ł̋��������߂�
//	int BackTrace(int x, int y);
//
//	int Search(int count);
//
//	void TraceRoute(int x, int y);
//
//	int _tmain(int argc, _TCHAR* argv[]);
//
//	std::shared_ptr<Map> map_ = nullptr;
//	std::shared_ptr<Enemy>enemy_ = nullptr;
//
//};

//class Map;
//
//// �}�b�v�X�e�[�^�X
//enum {
//	OPEN,
//	CLOSED,
//	B,      // ��
//	N,      // ���
//	S,      // �X�^�[�g
//	G       // �S�[��
//};
//
//class Aster {
//public:
//	Aster();
//	~Aster();
//
//	std::shared_ptr<Map> map_ = nullptr;
//	
//};
//class Point {
//public:
//	Point() : x(0),y(0){}
//	Point(int _x,int _y) :x(_x),y(_y){}//�R�s�[�R���X�g���N�^
//	int x;
//	int y;
//
//	//���g�̎����Ă���x,y�Ɠn���ꂽp��x,y�𑫂�
//	Point operator +(Point p) {
//		return Point(x + p.x, y + p.y);
//	}
//
//	bool operator == (Point p) {
//		if (x == p.x && y == p.y) return true;
//		return false;//����ȊO�Ȃ�
//	}
//	
//
//};
//
////�o�H�T���p�m�[�h
//class Node {
//public:
//	Node() :
//		status(N),
//		cost_real(0),
//		cost_guess(0),
//		score(0),
//		parent(nullptr)
//	{}
//
//	Point pos;         // 2�����z���̍��W
//	int status;        // OPEN ��� CLOSED ���
//	int cost_real;     // ���R�X�g
//	int cost_guess;    // ����R�X�g
//	int score;         // �X�R�A
//	Node* parent;      // �e�m�[�h( �Ō�ɃS�[������H�邽�� )
//
//	bool operator < (const Node& node) const {
//		return score > node.score;
//	}
//};
//
////�}�b�v�̃m�[�h�f�[�^
////�m�[�h�����쐬���Čo�H�T���ɓn��
////�m�[�h�^�z����R���X�g���N�^�Ő錾����
////Node** nodes[Map::MEIRO_HEIGHT][Map::MEIRO_WIDTH];
////Node** nodes;
//Node** nodes;
//
////�w����W��OPEN�\�ȃ}�b�v�ʒu���ǂ�������
//bool isEnableMapPos(Point pos, Node** _nodes);
//
////����OPEN���Ă���m�[�h�̒��ň�ԃX�R�A�������Ȃ��̂��擾
////����OPEN���Ă���m�[�h�̂ݒ��ׂ�
//Node* getSmallScoreNode(Node** _nodes);
//
////�o�H�T��A*
//bool aster(Node** _nodes, Node* _now, std::vector<Node*> _route);
//
