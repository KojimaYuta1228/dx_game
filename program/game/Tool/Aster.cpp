#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include "../Character/Enemy.h"
#include "Aster.h"
#include"Map.h"

//int Map::maze[MEIRO_HEIGHT][MEIRO_WIDTH];
//
//
//Aster::Aster()
//{
//	map_ = std::make_shared<Map>();
//	nodes = map_->maze;
//}
//
//Aster::~Aster()
//{
//}
//
//
//bool isEnableMapPos(Point pos, Node** _nodes)
//{
//	//�������
//	if (pos.x < 0)return false;
//	if (pos.y < 0)return false;
//	if (pos.x > Map::MEIRO_WIDTH)return false;
//	if (pos.y > Map::MEIRO_HEIGHT)return false;
//	if (S == _nodes[pos.y][pos.x].status)return false;
//	if (N == _nodes[pos.y][pos.x].status)return true;
//	if (G == _nodes[pos.y][pos.x].status)return true;
//	return false;//����ȊO
//}
//
//Node* getSmallScoreNode(Node** _nodes)
//{
//	Node* p = nullptr;
//	for (int i = 0; i < Map::MEIRO_HEIGHT; ++i) {
//		for (int k = 0; k < Map::MEIRO_WIDTH; ++k) {
//
//			if (OPEN != _nodes[k][i].status)continue;//�}�b�v�̍��W��OPEN����Ȃ������瑱�s
//			if (nullptr == p)p = &_nodes[k][i];//Node* p��nullptr�Ȃ�p�Ɍ��݂̍��W�̃A�h���X�������
//			if (p->score > _nodes[k][i].score) p = &_nodes[k][i];//p��score�����݂�score���傫��������p�Ɍ��݂̍��W�̃A�h���X�������
//			else if (p->score == _nodes[k][i].score) {//p��score�����݂�score�Ɠ�����
//				if (p->cost_real > _nodes[k][i].cost_real) p = &_nodes[k][i];//p�̎��R�X�g�����݂̎��R�X�g���傫���Ȃ�p�Ɍ��݂̍��W�̃A�h���X�������
//			}
//		}
//	}
//	return p;
//}
//
//
//
//bool aster(Node** _nodes, Node* _now, std::vector<Node*>* _route)
//{
//	nodes = Map::maze[MEIRO_HEIGHT][MEIRO_WIDTH];
//	//nodes = new Node[Map::MEIRO_HEIGHT][Map::MEIRO_WIDTH];
//	// �X�^�[�g�n�_�̃X�R�A�v�Z
//	if (S == _now->status) {
//		_now->score = _now->cost_real + _now->cost_guess;
//	}
//
//	// �S�����̍��W
//	Point dir[4] = { Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0) };
//
//
//	//����4�����𒲂ׂĉ\�Ȃ�OPEN
//	for (int i = 0; i < 4; ++i) {
//		Point next = _now->pos + dir[i];
//
//		//���א悪OPEN�\���ǂ���
//		if (!isEnableMapPos(next, _nodes))continue;
//
//		//OPEN�\��悪�S�[���Ȃ��
//		if (G == _nodes[next.y][next.x].status) {
//			//�S�[����ۑ�
//			(*_route).push_back(&_nodes[next.y][next.x]);
//
//			//�S�[�������O���玩�g�̐e�m�[�h��k���ċL�^
//			//���̋L�^���ŒZ�����ɂȂ�
//			Node* p = _now;
//			//p��nullptr�o�Ȃ�����*_route��p�����ꑱ����
//			while (nullptr != p) {
//				(*_route).push_back(p);
//				p = p->parent;
//			}
//
//			//�S�[��������������true
//			return true;
//
//		}
//		
//
//		//4�����̃m�[�h�ɑ΂���OPEN��Score�̌v�Z����
//		_nodes[next.y][next.x].status = OPEN;
//		_nodes[next.y][next.x].parent = _now;
//		_nodes[next.y][next.x].cost_real = _now->cost_real + 1;
//		_nodes[next.y][next.x].score = _nodes[next.y][next.x].cost_real + _nodes[next.y][next.x].cost_guess;
//
//	}
//	// ����̃I�[�v�����I������̂Ŏ����̓N���[�Y
//	if (S != _now->status) {
//		_now->status = CLOSED;
//	}
//
//	// ���݃I�[�v�����Ă���m�[�h�ň�ԃX�R�A�̏��������̂���m�[�h
//	Node* node = getSmallScoreNode(_nodes);
//
//	// �m�[�h��������Ȃ���Γ��B�s�\
//	if (nullptr == node) return false;
//
//	// �ċA�I�ɒ��ׂĂ���
//	return aster(_nodes, node, _route);
//
//}
//int main() {
//	Point g;
//	Point s;
//
//	//�X�^�[�g�ƃS�[���̎擾(�S�[�����}�b�v�̍��W�ɂ��邩�v���C���[�ɂ��邩)
//	for (int i = 0; i < Map::MEIRO_HEIGHT; ++i) {
//		for (int k = 0; k < Map::MEIRO_WIDTH; ++k) {
//			//goal
//			//goal���痣�ꂽ�ꏊ��start
//		}
//	}
//
//	//�m�[�h�f�[�^�̏����ݒ�
//	for (int i = 0; i < Map::MEIRO_HEIGHT; ++i) {
//		for (int k = 0; k < Map::MEIRO_WIDTH; ++k) {
//			nodes[i][k].pos = Point(k, i);
//			nodes[i][k].status = Map::maze[i][k];
//			if (k == 4) {
//				int a = 4;
//				a++;
//			}
//
//			nodes[i][k].cost_guess = abs(g.x - k) + abs(g.y - i);
//		}
//	}
//	//�񎟌��z��������ɓn�����߂̗p��
//	Node* tmp_nodes[Map::MEIRO_HEIGHT];
//	for (int i = 0; i < Map::MEIRO_HEIGHT; ++i) {
//		tmp_nodes[i] = nodes[i];
//	}
//
//	// �o�H�T�����s
//	std::vector<Node*> route;
//	bool is_success = aster(tmp_nodes, &nodes[s.y][s.x], &route);
//
//	// false ���A���Ă����瓞�B�s�\
//	if (!is_success) {
//		printf("���B�s�\\n");
//		return 0;
//	}
//}
//
//
