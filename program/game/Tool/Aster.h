#pragma once

//class Map;
//
//// マップステータス
//enum {
//	OPEN,
//	CLOSED,
//	B,      // 壁
//	N,      // 空間
//	S,      // スタート
//	G       // ゴール
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
//	Point(int _x,int _y) :x(_x),y(_y){}//コピーコンストラクタ
//	int x;
//	int y;
//
//	//自身の持っているx,yと渡されたpのx,yを足す
//	Point operator +(Point p) {
//		return Point(x + p.x, y + p.y);
//	}
//
//	bool operator == (Point p) {
//		if (x == p.x && y == p.y) return true;
//		return false;//それ以外なら
//	}
//	
//
//};
//
////経路探索用ノード
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
//	Point pos;         // 2次元配列上の座標
//	int status;        // OPEN やら CLOSED やら
//	int cost_real;     // 実コスト
//	int cost_guess;    // 推定コスト
//	int score;         // スコア
//	Node* parent;      // 親ノード( 最後にゴールから辿るため )
//
//	bool operator < (const Node& node) const {
//		return score > node.score;
//	}
//};
//
////マップのノードデータ
////ノード情報を作成して経路探索に渡す
////ノード型配列をコンストラクタで宣言する
////Node** nodes[Map::MEIRO_HEIGHT][Map::MEIRO_WIDTH];
////Node** nodes;
//Node** nodes;
//
////指定座標がOPEN可能なマップ位置かどうか判定
//bool isEnableMapPos(Point pos, Node** _nodes);
//
////現在OPENしているノードの中で一番スコアが小さなものを取得
////既にOPENしているノードのみ調べる
//Node* getSmallScoreNode(Node** _nodes);
//
////経路探索A*
//bool aster(Node** _nodes, Node* _now, std::vector<Node*> _route);
//
