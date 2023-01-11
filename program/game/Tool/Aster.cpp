#include "../Character/Enemy.h"
#include"../Character/Player.h"
#include "Aster.h"
#include"Map.h"

bool isEnableMapPosition(Point pos, Node** _nodes)
{
	//�����������
	if (pos.x < 0) return false;
	if (pos.y < 0) return false;
	if (pos.x >= Map::MEIRO_WIDTH) return false;
	if (pos.y >= Map::MEIRO_HEIGHT) return false;
	if (static_cast<int>(Map::MAZESTATE::ASTART) == _nodes[pos.y][pos.x].status) return false;//�X�^�[�g�ʒu�̔���//Enemy��Pos
	if (static_cast<int>(Map::MAZESTATE::ROOT) == _nodes[pos.y][pos.x].status) return true;//���̔���
	if (static_cast<int>(Map::MAZESTATE::AGOAL) == _nodes[pos.y][pos.x].status) return true;//�S�[���ʒu�̔���//Player��Pos
	return false;//����ȊO
}

Node* getSmallScoreNodeFromOpenNodes(Node** _nodes)
{
	Node* p = nullptr;
	for (int i = 0; i < Map::MEIRO_HEIGHT; ++i) {
		for (int k = 0; k < Map::MEIRO_WIDTH; ++k) {
			if (static_cast<int>(Map::MAZESTATE::OPEN) != _nodes[k][i].status) continue;//�}�b�v�̍��W���I�[�v������Ȃ������瑱�s
			if (nullptr == p) p = &_nodes[k][i];//Node* p��nullptr�Ȃ�p�Ɍ��݂̍��W�̃A�h���X�������
			if (p->score > _nodes[k][i].score) p = &_nodes[k][i];//p��score�����݂�score���傫��������p�Ɍ��݂̍��W�̃A�h���X�������
			else if (p->score == _nodes[k][i].score) {//p��score�����݂�score�Ɠ�����
				if (p->cost_real > _nodes[k][i].cost_real) p = &_nodes[k][i];//p�̎��R�X�g�����݂̎��R�X�g���傫���Ȃ�p�Ɍ��݂̍��W�̃A�h���X�������
			}
		}
	}
	return p;
}

bool aster(Node** _nodes, Node* _now, std::vector<Node*>* _route)
{
	if (static_cast<int>(Map::MAZESTATE::ASTART) == _now->status) {
		_now->score = _now->cost_real + _now->cost_guess;
	}

	// �S�����̍��W
	Point dir[4] = { Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0) };

	// ����S�����𒲂ׂĉ\�Ȃ�I�[�v��
	for (int i = 0; i < 4; ++i) {
		Point next = _now->pos + dir[i];

		// ���א悪�I�[�v���\���ǂ���
		if (!isEnableMapPosition(next, _nodes)) continue;

		// �I�[�v���\��̍��W���S�[��������
		if (static_cast<int>(Map::MAZESTATE::AGOAL) == _nodes[next.y][next.x].status) {

			// �S�[����ۑ�����
			(*_route).push_back(&_nodes[next.y][next.x]);

			// �S�[�������O���玩���̐e�m�[�h��k���ċL�^
			// ���̋L�^���ŒZ�o�H�ƂȂ�
			Node* p = _now;
			while (nullptr != p) {
				(*_route).push_back(p);
				p = p->parent;
			}

			// �S�[�������������̂� true
			return true;
		}

		// �S�����̃m�[�h�ɑ΂���I�[�v���ƃX�R�A�v�Z����
		_nodes[next.y][next.x].status = static_cast<int>(Map::MAZESTATE::OPEN);
		_nodes[next.y][next.x].parent = _now;
		_nodes[next.y][next.x].cost_real = _now->cost_real + 1;
		_nodes[next.y][next.x].score = _nodes[next.y][next.x].cost_real + _nodes[next.y][next.x].cost_guess;
	}

	// ����̃I�[�v�����I������̂Ŏ����̓N���[�Y
	if (static_cast<int>(Map::MAZESTATE::ASTART) != _now->status) {
		_now->status = static_cast<int>(Map::MAZESTATE::CLOSED);
	}

	// ���݃I�[�v�����Ă���m�[�h�ň�ԃX�R�A�̏��������̂���m�[�h
	Node* node = getSmallScoreNodeFromOpenNodes(_nodes);

	// �m�[�h��������Ȃ���Γ��B�s�\
	if (nullptr == node) return false;

	// �ċA�I�ɒ��ׂĂ���
	return aster(_nodes, node, _route);
}

int update()
{
	Point g;
	Point s;


	// �X�^�[�g�ƃS�[���̈ʒu���擾
	for (int i = 0; i < Map::MEIRO_HEIGHT; ++i) {
		for (int k = 0; k < Map::MEIRO_WIDTH; ++k) {
			if (static_cast<int>(Map::MAZESTATE::AGOAL) == Map::maze[i][k]) g = Point(k, i);
			if (static_cast<int>(Map::MAZESTATE::ASTART) == Map::maze[i][k]) s = Point(k, i);
		}
	}

	// �m�[�h�f�[�^�̏����ݒ�
	for (int i = 0; i < Map::MEIRO_HEIGHT; ++i) {
		for (int k = 0; k < Map::MEIRO_WIDTH; ++k) {
			nodes[i][k].pos = Point(k, i);
			nodes[i][k].status = Map::maze[i][k];
			if (k == 4) {
				int a = 0;
				a++;
			}
			nodes[i][k].cost_guess = abs(g.x - k) + abs(g.y - i);
		}
	}

	// �񎟌��z��̃A�h���X�������ɓn���ׂ̏���
	Node* tmp_nodes[Map::MEIRO_HEIGHT];
	for (int i = 0; i < Map::MEIRO_HEIGHT; ++i) {
		tmp_nodes[i] = nodes[i];
	}

	// �o�H�T�����s
	std::vector<Node*> route;
	bool is_success = aster(tmp_nodes, &nodes[s.y][s.x], &route);

	// false ���A���Ă����瓞�B�s�\
	if (!is_success) {
		printf("���B�s�\\n");
		return 0;
	}
}
