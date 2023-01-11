#include "../Character/Enemy.h"
#include"../Character/Player.h"
#include "Aster.h"
#include"Map.h"

bool isEnableMapPosition(Point pos, Node** _nodes)
{
	//上限下限判定
	if (pos.x < 0) return false;
	if (pos.y < 0) return false;
	if (pos.x >= Map::MEIRO_WIDTH) return false;
	if (pos.y >= Map::MEIRO_HEIGHT) return false;
	if (static_cast<int>(Map::MAZESTATE::ASTART) == _nodes[pos.y][pos.x].status) return false;//スタート位置の判定//EnemyのPos
	if (static_cast<int>(Map::MAZESTATE::ROOT) == _nodes[pos.y][pos.x].status) return true;//道の判定
	if (static_cast<int>(Map::MAZESTATE::AGOAL) == _nodes[pos.y][pos.x].status) return true;//ゴール位置の判定//PlayerのPos
	return false;//それ以外
}

Node* getSmallScoreNodeFromOpenNodes(Node** _nodes)
{
	Node* p = nullptr;
	for (int i = 0; i < Map::MEIRO_HEIGHT; ++i) {
		for (int k = 0; k < Map::MEIRO_WIDTH; ++k) {
			if (static_cast<int>(Map::MAZESTATE::OPEN) != _nodes[k][i].status) continue;//マップの座標がオープンじゃなかったら続行
			if (nullptr == p) p = &_nodes[k][i];//Node* pがnullptrならpに現在の座標のアドレスをいれる
			if (p->score > _nodes[k][i].score) p = &_nodes[k][i];//pのscoreが現在のscoreより大きかったらpに現在の座標のアドレスをいれる
			else if (p->score == _nodes[k][i].score) {//pのscoreが現在のscoreと同じで
				if (p->cost_real > _nodes[k][i].cost_real) p = &_nodes[k][i];//pの実コストが現在の実コストより大きいならpに現在の座標のアドレスをいれる
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

	// ４方向の座標
	Point dir[4] = { Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0) };

	// 周り４方向を調べて可能ならオープン
	for (int i = 0; i < 4; ++i) {
		Point next = _now->pos + dir[i];

		// 調べ先がオープン可能かどうか
		if (!isEnableMapPosition(next, _nodes)) continue;

		// オープン予定の座標がゴールだった
		if (static_cast<int>(Map::MAZESTATE::AGOAL) == _nodes[next.y][next.x].status) {

			// ゴールを保存して
			(*_route).push_back(&_nodes[next.y][next.x]);

			// ゴール一歩手前から自分の親ノードを遡って記録
			// この記録が最短経路となる
			Node* p = _now;
			while (nullptr != p) {
				(*_route).push_back(p);
				p = p->parent;
			}

			// ゴールが見つかったので true
			return true;
		}

		// ４方向のノードに対するオープンとスコア計算処理
		_nodes[next.y][next.x].status = static_cast<int>(Map::MAZESTATE::OPEN);
		_nodes[next.y][next.x].parent = _now;
		_nodes[next.y][next.x].cost_real = _now->cost_real + 1;
		_nodes[next.y][next.x].score = _nodes[next.y][next.x].cost_real + _nodes[next.y][next.x].cost_guess;
	}

	// 周りのオープンが終わったので自分はクローズ
	if (static_cast<int>(Map::MAZESTATE::ASTART) != _now->status) {
		_now->status = static_cast<int>(Map::MAZESTATE::CLOSED);
	}

	// 現在オープンしているノードで一番スコアの小さいものが基準ノード
	Node* node = getSmallScoreNodeFromOpenNodes(_nodes);

	// ノードが見つからなければ到達不能
	if (nullptr == node) return false;

	// 再帰的に調べていく
	return aster(_nodes, node, _route);
}

int update()
{
	Point g;
	Point s;


	// スタートとゴールの位置を取得
	for (int i = 0; i < Map::MEIRO_HEIGHT; ++i) {
		for (int k = 0; k < Map::MEIRO_WIDTH; ++k) {
			if (static_cast<int>(Map::MAZESTATE::AGOAL) == Map::maze[i][k]) g = Point(k, i);
			if (static_cast<int>(Map::MAZESTATE::ASTART) == Map::maze[i][k]) s = Point(k, i);
		}
	}

	// ノードデータの初期設定
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

	// 二次元配列のアドレスを引数に渡す為の準備
	Node* tmp_nodes[Map::MEIRO_HEIGHT];
	for (int i = 0; i < Map::MEIRO_HEIGHT; ++i) {
		tmp_nodes[i] = nodes[i];
	}

	// 経路探索実行
	std::vector<Node*> route;
	bool is_success = aster(tmp_nodes, &nodes[s.y][s.x], &route);

	// false が帰ってきたら到達不能
	if (!is_success) {
		printf("到達不能\n");
		return 0;
	}
}
