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

// XYをひとまとめに扱うため
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


// 経路探索用ノード
class Node {
public:
	Node() :
		status(static_cast<int>(Map::MAZESTATE::ROOT)),
		cost_real(0),
		cost_guess(0),
		score(0),
		parent(nullptr)
	{}

	Point pos;         // 2次元配列上の座標
	int status;        // OPEN やら CLOSED やら
	int cost_real;     // 実コスト
	int cost_guess;    // 推定コスト
	int score;         // スコア
	Node* parent;      // 親ノード( 最後にゴールから辿るため )

	bool operator < (const Node& node) const {
		return score > node.score;
	}

};

// マップのノードデータ
// 上の2次元配列からこの
// ノード情報を作成して経路探索に渡す
Node nodes[Map::MEIRO_HEIGHT][Map::MEIRO_WIDTH];


// 指定座標が有効な( OPEN 可能な )マップ位置かどうか判定
bool isEnableMapPosition(Point pos, Node** _nodes);

// [ 現在オープンになっているノードで一番スコアの小さいものを取得 ]
// サンプルの分かり易さ優先なので全ノードを調べる形にしているが、
// 効率は良くないのでライブラリ化する時にでも 既にオープンしている
// ノードだけ調べるように効率化を図った方がよい
Node* getSmallScoreNodeFromOpenNodes(Node** _nodes);

// 経路探索 A*
bool aster(Node** _nodes, Node* _now, std::vector<Node*>* _route);

int update();
