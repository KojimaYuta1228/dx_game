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
//	//上限判定
//	if (pos.x < 0)return false;
//	if (pos.y < 0)return false;
//	if (pos.x > Map::MEIRO_WIDTH)return false;
//	if (pos.y > Map::MEIRO_HEIGHT)return false;
//	if (S == _nodes[pos.y][pos.x].status)return false;
//	if (N == _nodes[pos.y][pos.x].status)return true;
//	if (G == _nodes[pos.y][pos.x].status)return true;
//	return false;//それ以外
//}
//
//Node* getSmallScoreNode(Node** _nodes)
//{
//	Node* p = nullptr;
//	for (int i = 0; i < Map::MEIRO_HEIGHT; ++i) {
//		for (int k = 0; k < Map::MEIRO_WIDTH; ++k) {
//
//			if (OPEN != _nodes[k][i].status)continue;//マップの座標がOPENじゃなかったら続行
//			if (nullptr == p)p = &_nodes[k][i];//Node* pがnullptrならpに現在の座標のアドレスをいれる
//			if (p->score > _nodes[k][i].score) p = &_nodes[k][i];//pのscoreが現在のscoreより大きかったらpに現在の座標のアドレスをいれる
//			else if (p->score == _nodes[k][i].score) {//pのscoreが現在のscoreと同じで
//				if (p->cost_real > _nodes[k][i].cost_real) p = &_nodes[k][i];//pの実コストが現在の実コストより大きいならpに現在の座標のアドレスをいれる
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
//	// スタート地点のスコア計算
//	if (S == _now->status) {
//		_now->score = _now->cost_real + _now->cost_guess;
//	}
//
//	// ４方向の座標
//	Point dir[4] = { Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0) };
//
//
//	//周囲4方向を調べて可能ならOPEN
//	for (int i = 0; i < 4; ++i) {
//		Point next = _now->pos + dir[i];
//
//		//調べ先がOPEN可能かどうか
//		if (!isEnableMapPos(next, _nodes))continue;
//
//		//OPEN予定先がゴールならば
//		if (G == _nodes[next.y][next.x].status) {
//			//ゴールを保存
//			(*_route).push_back(&_nodes[next.y][next.x]);
//
//			//ゴール一歩手前から自身の親ノードを遡って記録
//			//この記録が最短距離になる
//			Node* p = _now;
//			//pがnullptr出ない限り*_routeにpをいれ続ける
//			while (nullptr != p) {
//				(*_route).push_back(p);
//				p = p->parent;
//			}
//
//			//ゴールが見つかったらtrue
//			return true;
//
//		}
//		
//
//		//4方向のノードに対するOPENとScoreの計算処理
//		_nodes[next.y][next.x].status = OPEN;
//		_nodes[next.y][next.x].parent = _now;
//		_nodes[next.y][next.x].cost_real = _now->cost_real + 1;
//		_nodes[next.y][next.x].score = _nodes[next.y][next.x].cost_real + _nodes[next.y][next.x].cost_guess;
//
//	}
//	// 周りのオープンが終わったので自分はクローズ
//	if (S != _now->status) {
//		_now->status = CLOSED;
//	}
//
//	// 現在オープンしているノードで一番スコアの小さいものが基準ノード
//	Node* node = getSmallScoreNode(_nodes);
//
//	// ノードが見つからなければ到達不能
//	if (nullptr == node) return false;
//
//	// 再帰的に調べていく
//	return aster(_nodes, node, _route);
//
//}
//int main() {
//	Point g;
//	Point s;
//
//	//スタートとゴールの取得(ゴールをマップの座標にするかプレイヤーにするか)
//	for (int i = 0; i < Map::MEIRO_HEIGHT; ++i) {
//		for (int k = 0; k < Map::MEIRO_WIDTH; ++k) {
//			//goal
//			//goalから離れた場所にstart
//		}
//	}
//
//	//ノードデータの初期設定
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
//	//二次元配列を引数に渡すための用意
//	Node* tmp_nodes[Map::MEIRO_HEIGHT];
//	for (int i = 0; i < Map::MEIRO_HEIGHT; ++i) {
//		tmp_nodes[i] = nodes[i];
//	}
//
//	// 経路探索実行
//	std::vector<Node*> route;
//	bool is_success = aster(tmp_nodes, &nodes[s.y][s.x], &route);
//
//	// false が帰ってきたら到達不能
//	if (!is_success) {
//		printf("到達不能\n");
//		return 0;
//	}
//}
//
//
