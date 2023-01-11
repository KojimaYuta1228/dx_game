#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include"Map.h"

class Map;
class CharacterBase;
class Player;
class Enemy;

// Map::maze[MEIRO_HEIGHT][MEIRO_WIDTH];

// XY���ЂƂ܂Ƃ߂Ɉ�������
class Point {
public:
	Point() : x(0), y(0) {}
	Point(int _x, int _y) : x(_x), y(_y) {}
	int x;
	int y;

	Point operator + (Point p) {
		return Point(x + p.x, y + p.y);
	}
	bool operator == (Point p) {
		if (x == p.x && y == p.y) return true;
		return false;
	}
};


// �o�H�T���p�m�[�h
class Node {
public:
	Node() :
		status(static_cast<int>(Map::MAZESTATE::ROOT)),
		cost_real(0),
		cost_guess(0),
		score(0),
		parent(nullptr)
	{}

	Point pos;         // 2�����z���̍��W
	int status;        // OPEN ��� CLOSED ���
	int cost_real;     // ���R�X�g
	int cost_guess;    // ����R�X�g
	int score;         // �X�R�A
	Node* parent;      // �e�m�[�h( �Ō�ɃS�[������H�邽�� )

	bool operator < (const Node& node) const {
		return score > node.score;
	}

};

// �}�b�v�̃m�[�h�f�[�^
// ���2�����z�񂩂炱��
// �m�[�h�����쐬���Čo�H�T���ɓn��
Node nodes[Map::MEIRO_HEIGHT][Map::MEIRO_WIDTH];


// �w����W���L����( OPEN �\�� )�}�b�v�ʒu���ǂ�������
bool isEnableMapPosition(Point pos, Node** _nodes);

// [ ���݃I�[�v���ɂȂ��Ă���m�[�h�ň�ԃX�R�A�̏��������̂��擾 ]
// �T���v���̕�����Ղ��D��Ȃ̂őS�m�[�h�𒲂ׂ�`�ɂ��Ă��邪�A
// �����͗ǂ��Ȃ��̂Ń��C�u���������鎞�ɂł� ���ɃI�[�v�����Ă���
// �m�[�h�������ׂ�悤�Ɍ�������}���������悢
Node* getSmallScoreNodeFromOpenNodes(Node** _nodes);

// �o�H�T�� A*
bool aster(Node** _nodes, Node* _now, std::vector<Node*>* _route);

int update();
