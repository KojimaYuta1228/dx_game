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
//
