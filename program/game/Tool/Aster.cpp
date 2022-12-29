//#include "../Character/Enemy.h"
//#include "Aster.h"
//#include"Map.h"
//
////int Map::maze[MEIRO_HEIGHT][MEIRO_WIDTH];
////
////
////Aster::Aster()
////{
////	map_ = std::make_shared<Map>();
////	nodes = map_->maze;
////}
////
////Aster::~Aster()
////{
////}
////
////
////bool isEnableMapPos(Point pos, Node** _nodes)
////{
////	//上限判定
////	if (pos.x < 0)return false;
////	if (pos.y < 0)return false;
////	if (pos.x > Map::MEIRO_WIDTH)return false;
////	if (pos.y > Map::MEIRO_HEIGHT)return false;
////	if (S == _nodes[pos.y][pos.x].status)return false;
////	if (N == _nodes[pos.y][pos.x].status)return true;
////	if (G == _nodes[pos.y][pos.x].status)return true;
////	return false;//それ以外
////}
////
////Node* getSmallScoreNode(Node** _nodes)
////{
////	Node* p = nullptr;
////	for (int i = 0; i < Map::MEIRO_HEIGHT; ++i) {
////		for (int k = 0; k < Map::MEIRO_WIDTH; ++k) {
////
////			if (OPEN != _nodes[k][i].status)continue;//マップの座標がOPENじゃなかったら続行
////			if (nullptr == p)p = &_nodes[k][i];//Node* pがnullptrならpに現在の座標のアドレスをいれる
////			if (p->score > _nodes[k][i].score) p = &_nodes[k][i];//pのscoreが現在のscoreより大きかったらpに現在の座標のアドレスをいれる
////			else if (p->score == _nodes[k][i].score) {//pのscoreが現在のscoreと同じで
////				if (p->cost_real > _nodes[k][i].cost_real) p = &_nodes[k][i];//pの実コストが現在の実コストより大きいならpに現在の座標のアドレスをいれる
////			}
////		}
////	}
////	return p;
////}
////
////
////
////bool aster(Node** _nodes, Node* _now, std::vector<Node*>* _route)
////{
////	nodes = Map::maze[MEIRO_HEIGHT][MEIRO_WIDTH];
////	//nodes = new Node[Map::MEIRO_HEIGHT][Map::MEIRO_WIDTH];
////	// スタート地点のスコア計算
////	if (S == _now->status) {
////		_now->score = _now->cost_real + _now->cost_guess;
////	}
////
////	// ４方向の座標
////	Point dir[4] = { Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0) };
////
////
////	//周囲4方向を調べて可能ならOPEN
////	for (int i = 0; i < 4; ++i) {
////		Point next = _now->pos + dir[i];
////
////		//調べ先がOPEN可能かどうか
////		if (!isEnableMapPos(next, _nodes))continue;
////
////		//OPEN予定先がゴールならば
////		if (G == _nodes[next.y][next.x].status) {
////			//ゴールを保存
////			(*_route).push_back(&_nodes[next.y][next.x]);
////
////			//ゴール一歩手前から自身の親ノードを遡って記録
////			//この記録が最短距離になる
////			Node* p = _now;
////			//pがnullptr出ない限り*_routeにpをいれ続ける
////			while (nullptr != p) {
////				(*_route).push_back(p);
////				p = p->parent;
////			}
////
////			//ゴールが見つかったらtrue
////			return true;
////
////		}
////		
////
////		//4方向のノードに対するOPENとScoreの計算処理
////		_nodes[next.y][next.x].status = OPEN;
////		_nodes[next.y][next.x].parent = _now;
////		_nodes[next.y][next.x].cost_real = _now->cost_real + 1;
////		_nodes[next.y][next.x].score = _nodes[next.y][next.x].cost_real + _nodes[next.y][next.x].cost_guess;
////
////	}
////	// 周りのオープンが終わったので自分はクローズ
////	if (S != _now->status) {
////		_now->status = CLOSED;
////	}
////
////	// 現在オープンしているノードで一番スコアの小さいものが基準ノード
////	Node* node = getSmallScoreNode(_nodes);
////
////	// ノードが見つからなければ到達不能
////	if (nullptr == node) return false;
////
////	// 再帰的に調べていく
////	return aster(_nodes, node, _route);
////
////}
////int main() {
////	Point g;
////	Point s;
////
////	//スタートとゴールの取得(ゴールをマップの座標にするかプレイヤーにするか)
////	for (int i = 0; i < Map::MEIRO_HEIGHT; ++i) {
////		for (int k = 0; k < Map::MEIRO_WIDTH; ++k) {
////			//goal
////			//goalから離れた場所にstart
////		}
////	}
////
////	//ノードデータの初期設定
////	for (int i = 0; i < Map::MEIRO_HEIGHT; ++i) {
////		for (int k = 0; k < Map::MEIRO_WIDTH; ++k) {
////			nodes[i][k].pos = Point(k, i);
////			nodes[i][k].status = Map::maze[i][k];
////			if (k == 4) {
////				int a = 4;
////				a++;
////			}
////
////			nodes[i][k].cost_guess = abs(g.x - k) + abs(g.y - i);
////		}
////	}
////	//二次元配列を引数に渡すための用意
////	Node* tmp_nodes[Map::MEIRO_HEIGHT];
////	for (int i = 0; i < Map::MEIRO_HEIGHT; ++i) {
////		tmp_nodes[i] = nodes[i];
////	}
////
////	// 経路探索実行
////	std::vector<Node*> route;
////	bool is_success = aster(tmp_nodes, &nodes[s.y][s.x], &route);
////
////	// false が帰ってきたら到達不能
////	if (!is_success) {
////		printf("到達不能\n");
////		return 0;
////	}
////}
////
////
//
//
//#define KEY(X,Y) ((X) * 100 + (Y))
//#define KEYDATA(X, Y, N) pair<int, anode>(KEY(X,Y), N)
//
//
//using namespace std;
//
//
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
//// マンハッタン距離を斜め移動ありを考慮して求める
//int Aster::GetDistance(int from_x, int from_y, int to_x, int to_y)
//{
//	
//	int cx = from_x - to_x;
//	int cy = from_y - to_y;
//
//	if (cx < 0) cx *= -1;
//	if (cy < 0) cy *= -1;
//
//	// 推定移動コストを計算
//	if (cx < cy) {
//		return (cx + (cy - cx));
//	}
//	else {
//		return (cy + (cx - cy));
//	}
//}
//
//anode* SetNode(anode* n, int nx, int ny, int npx, int npy, int ncost)
//{
//	// ノード情報を一度にセットする
//	n->x = nx;
//	n->y = ny;
//	n->px = npx;
//	n->py = npy;
//	n->cost = ncost;
//
//	return n;
//}
//
//// 指定した地点からスタート地点までの距離を求める
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
//// A*で経路探査する
//int Aster::Search(int count)
//{
//	// openリストが空なら終了
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
//	//Openリストから最小のコストを持つノードを取り出す
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
//	// OpenリストからCloseリストへ移動
//	mapClose.insert(KEYDATA(n.x, n.y, n));
//	mapOpen.erase(KEY(n.x, n.y));
//
//	// 最小コストのノードからスタートまでの移動コスト
//	BackCost = BackTrace(n.x, n.y);
//
//	for (int i = 0; i < 8; i++) {
//		// 隣接するマスの座標を計算
//		int cx = n.x + way[i][0];
//		int cy = n.y + way[i][1];
//
//		if (cx < 0) continue;
//		if (cy < 0) continue;
//
//		if (cx >= WIDTH) continue;
//		if (cy >= HEIGHT) continue;
//
//		// 通れない所をよける
//		if (mapdata[cy][cx] == -1) continue;
//
//		SetNode(
//			&nodes[i],
//			cx, cy,
//			n.x, n.y,
//			BackCost + GetDistance(cx, cy, GX, GY) + 1	// 推定移動コスト
//		);
//
//		//Openリストにこの座標と同じノードがあるか確認
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
//		//Closeリストにこの座標と同じノードがあるか確認
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
//		// 見つからなければ新規としてOpenリストへ追加
//		mapOpen.insert(KEYDATA(nodes[i].x, nodes[i].y, nodes[i]));
//	}
//
//	//見つかったら探索終了
//	if (n.x == GX && n.y == GY) return -1;
//
//	return Search(count + 1);
//}
//// 最短ルートをマップデータに書き出す
//void Aster::TraceRoute(int x, int y)
//{
//	if (x == SX && y == SY) {
//		printf("開始ノード>");
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
//		if (x == GX && y == GY) {
//			printf("ゴール\n");
//			return;
//		}
//		else {
//			printf("(%d,%d)>", x, y);
//		}
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
//		printf("見つかった！\n");
//	}
//	TraceRoute(GX, GY);
//
//	//out(mapdata);
//
//	return 0;
//}
