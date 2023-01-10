//#include "../Character/Enemy.h"
//#include "Aster.h"
//#include"Map.h"
//
//#define KEY(X,Y) ((X) * 100 + (Y))
//#define KEYDATA(X, Y, N) pair<int, anode>(KEY(X,Y), N)
//
//
//using namespace std;
//
//Aster::Aster()
//{
//	map_ = make_shared<Map>();
//	enemy_ = make_shared<Enemy>();
//}
//
//Aster::~Aster()
//{
//}
//
//// �}���n�b�^���������΂߈ړ�������l�����ċ��߂�
//int Aster::GetDistance(int from_x, int from_y, int to_x, int to_y)
//{
//	
//	int cx = from_x - to_x;
//	int cy = from_y - to_y;
//
//	if (cx < 0) cx *= -1;
//	if (cy < 0) cy *= -1;
//
//	// ����ړ��R�X�g���v�Z
//	if (cx < cy) {
//		return (cx + (cy - cx));
//	}
//	else {
//		return (cy + (cx - cy));
//	}
//}
//
//anode* Aster::SetNode(anode* n, int nx, int ny, int npx, int npy, int ncost)
//{
//	// �m�[�h������x�ɃZ�b�g����
//	n->x = nx;
//	n->y = ny;
//	n->px = npx;
//	n->py = npy;
//	n->cost = ncost;
//
//	return n;
//	
//}
//
//
//// �w�肵���n�_����X�^�[�g�n�_�܂ł̋��������߂�
//int BackTrace(int x, int y)
//{
//	if (x == SX && y == SY) {
//		return 1;
//	}
//
//	map<int, anode>::iterator tmp = mapClose.find(KEY(x, y));
//
//	if (tmp == mapClose.end()) return 0;
//
//	return BackTrace(tmp->second.px, tmp->second.py) + 1;
//}
//
//
//// A*�Ōo�H�T������
//int Aster::Search(int count)
//{
//	// open���X�g����Ȃ�I��
//	if (mapOpen.empty()) return -9;
//
//	anode nodes[8];
//
//	int way[8][2] = {
//		{ -1, -1},
//		{  0, -1},
//		{  1, -1},
//		{  1,  0},
//		{  1,  1},
//		{  0,  1},
//		{ -1,  1},
//		{ -1,  0},
//	};
//
//	map<int, anode>::iterator it;
//	map<int, anode>::iterator it_min;
//
//	anode n;
//
//	int cost_min = 9999;
//	int BackCost = 0;
//
//	//Open���X�g����ŏ��̃R�X�g�����m�[�h�����o��
//	it = mapOpen.begin();
//	while (it != mapOpen.end()) {
//		if (cost_min > GetDistance(it->second.x, it->second.y, GX, GY)) {
//			cost_min = GetDistance(it->second.x, it->second.y, GX, GY);
//			it_min = it;
//		}
//		it++;
//	}
//
//	SetNode(
//		&n,
//		it_min->second.x, it_min->second.y,
//		it_min->second.px, it_min->second.py,
//		it_min->second.cost
//	);
//
//	// Open���X�g����Close���X�g�ֈړ�
//	mapClose.insert(KEYDATA(n.x, n.y, n));
//	mapOpen.erase(KEY(n.x, n.y));
//
//	// �ŏ��R�X�g�̃m�[�h����X�^�[�g�܂ł̈ړ��R�X�g
//	BackCost = BackTrace(n.x, n.y);
//
//	for (int i = 0; i < 8; i++) {
//		// �אڂ���}�X�̍��W���v�Z
//		int cx = n.x + way[i][0];
//		int cy = n.y + way[i][1];
//
//		if (cx < 0) continue;
//		if (cy < 0) continue;
//
//		if (cx >= WIDTH) continue;
//		if (cy >= HEIGHT) continue;
//
//		// �ʂ�Ȃ������悯��
//		if (mapdata[cy][cx] == -1) continue;
//
//		SetNode(
//			&nodes[i],
//			cx, cy,
//			n.x, n.y,
//			BackCost + GetDistance(cx, cy, GX, GY) + 1	// ����ړ��R�X�g
//		);
//
//		//Open���X�g�ɂ��̍��W�Ɠ����m�[�h�����邩�m�F
//		if (mapOpen.find(KEY(cx, cy)) != mapOpen.end()) {
//			if (nodes[i].cost < mapOpen[KEY(cx, cy)].cost) {
//				mapOpen[KEY(cx, cy)].px = n.x;
//				mapOpen[KEY(cx, cy)].py = n.y;
//
//				mapOpen[KEY(cx, cy)].cost = nodes[i].cost;
//			}
//			continue;
//		}
//
//		//Close���X�g�ɂ��̍��W�Ɠ����m�[�h�����邩�m�F
//		if (mapClose.find(KEY(cx, cy)) != mapClose.end()) {
//			if (nodes[i].cost < mapClose[KEY(cx, cy)].cost) {
//				anode tmp;
//
//				SetNode(
//					&tmp,
//					cx, cy,
//					n.x, n.y,
//					nodes[i].cost
//				);
//
//				mapOpen.insert(KEYDATA(cx, cy, tmp));
//				mapClose.erase(KEY(cx, cy));
//			}
//			continue;
//		}
//
//		// ������Ȃ���ΐV�K�Ƃ���Open���X�g�֒ǉ�
//		mapOpen.insert(KEYDATA(nodes[i].x, nodes[i].y, nodes[i]));
//	}
//
//	//����������T���I��
//	if (n.x == GX && n.y == GY) return -1;
//
//	return Search(count + 1);
//}
//// �ŒZ���[�g���}�b�v�f�[�^�ɏ����o��
//void Aster::TraceRoute(int x, int y)
//{
//	if (x == SX && y == SY) {
//		printf("�J�n�m�[�h>");
//		return;
//	}
//
//	map<int, anode>::iterator node_it = mapClose.find(KEY(x, y));
//
//	if (node_it != mapClose.end()) {
//		mapdata[y][x] = 1;
//
//		TraceRoute(node_it->second.px, node_it->second.py);
//
//		
//	}
//
//	return;
//}
//
//int Aster::_tmain(int argc, _TCHAR* argv[])
//{
//	anode start;
//
//	SetNode(
//		&start,
//		SX, SY,
//		-1, -1,
//		0
//	);
//
//	mapOpen.insert(KEYDATA(SX, SY, start));
//
//	if (Search(0) == -1) {
//		printf("���������I\n");
//	}
//	TraceRoute(GX, GY);
//
//	//out(mapdata);
//
//	return 0;
//}
