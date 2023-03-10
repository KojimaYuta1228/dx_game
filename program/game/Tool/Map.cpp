#include "Map.h"
#include "../scene/gm_scene_play.h"
#include "../gm_manager.h"
#include "../../dxlib_ext/dxlib_ext.h"


#define NONE static_cast<int>(MAZESTATE::NONE)
#define WALL static_cast<int>(MAZESTATE::WALL)
#define ROOT static_cast<int>(MAZESTATE::ROOT)
#define GOAL static_cast<int>(MAZESTATE::GOAL)
#define ASTART static_cast<int>(MAZESTATE::ASTART)

int Map::maze[MEIRO_HEIGHT][MEIRO_WIDTH];

Map::Map()
{
	mgr = GameManager::GetInstance();
	SceneBase* scene_base = mgr->getCurrentScene();
	ScenePlay* scene_play = dynamic_cast<ScenePlay*>(scene_base);
	if (scene_play) {
		camera_ = scene_play->GetCamera();
	}
	for (int i = 0; i < MEIRO_HEIGHT; i++) {
		for (int k = 0; k < MEIRO_WIDTH; k++) {
			map_chips_[i][k] = nullptr;
		}
	}
}

Map::~Map()
{
	for (int i = 0; i < MEIRO_HEIGHT; i++) {
		for (int k = 0; k < MEIRO_WIDTH; k++) {
			maze[i][k] = NONE;
			if (map_chips_[i][k]) {
				delete map_chips_[i][k];
				map_chips_[i][k] = nullptr;
			}
		}
	}

}

void Map::initialzie()
{
	// 使用するテクスチャを事前ロード
	Shared<dxe::Texture> texs[3];
	texs[0] = dxe::Texture::CreateFromFile("graphics/red1.bmp");//RootTexture
	texs[1] = dxe::Texture::CreateFromFile("graphics/Resouce/image/item/green_blook.jpg");//WallTexture
	texs[2] = dxe::Texture::CreateFromFile("graphics/Resouce/image/img_goal.jpg");//GoalTexture
	createMaze();
	/*-----------Boxのクローンの作成とステージの初期化-----------*/
	//Boxをあらかじめ作成
	// ボックス３種類をあらかじめ作成
	dxe::Mesh* origin_boxs[3];
	for (int i = 0; i < 3; ++i) {
		if (i == 2) {
			origin_boxs[i] =
				dxe::Mesh::CreateDiskMV(25);
			origin_boxs[i]->rot_q_ = tnl::Quaternion::RotationAxis({ 0, 1, 0 }, tnl::ToRadian(90));
		}
		else {
			origin_boxs[i] = dxe::Mesh::CreateBoxMV(50);
		}
		origin_boxs[i]->setTexture(texs[i]);
	}
	// ボックスをクローンして生成することで生成速度アップ
	//マップチップにクローンをいれる
	for (int i = 0; i < MEIRO_HEIGHT; ++i) {
		for (int k = 0; k < MEIRO_WIDTH; ++k) {
			if (maze[i][k] == ROOT)map_chips_[i][k] = origin_boxs[0]->createClone();
			if (maze[i][k] == WALL)map_chips_[i][k] = origin_boxs[1]->createClone();
			if (maze[i][k] == GOAL) {
				map_chips_[i][k] = origin_boxs[2]->createClone();
			}
			if (map_chips_[i][k]) {
				map_chips_[i][k]->pos_ = { (float)(-(12 * 50) + (k * 50)), 0, (float)((12 * 50) - (i * 50)) };
				field_boxs_.emplace_back(map_chips_[i][k]);//クローンしたマップをリストに追加
			}
		}
	}
}

void Map::Rander()
{
	printMaze(MEIRO_WIDTH, MEIRO_HEIGHT);
}

int Map::SelectStartPoint(int MAXSIZE)
{
	//マップのどこかの奇数番の数字を返す
	int reStart = std::rand() % MAXSIZE;
	//余りが1ではない==奇数なら調整する
	if (reStart % 2 != 1) {
		//最大数より1低い数字以外なら1を足す(配列の範囲外エラー対策)
		if (reStart <= (MAXSIZE - 1)) {
			reStart++;
		}
		else {
			//0なら引き算したくないのでそのまま返す
			if (reStart == 0)return reStart;
			reStart--;
		}
	}
	return reStart;
}

void Map::createMaze()
{
	createWall(MEIRO_WIDTH, MEIRO_HEIGHT);	
	//----------------------始点の生成------------------------//
	int startX, startY, startEnX, startEnY;
	//スタート地点を乱数で取得する
	startX = SelectStartPoint(MEIRO_WIDTH);
	startY = SelectStartPoint(MEIRO_HEIGHT);
	dis_x = startX;
	dis_y = startY;
	startEnX = SelectStartPoint(MEIRO_WIDTH);
	startEnY = SelectStartPoint(MEIRO_WIDTH);
	while (startX == startEnX || startY == startEnY)
	{
		startEnX = SelectStartPoint(MEIRO_WIDTH);
		startEnY = SelectStartPoint(MEIRO_WIDTH);
		if (startX != startEnX && startY != startEnY)break;
	}
	start_en_pos = { static_cast<float>(startEnX) ,0,static_cast<float>(startEnY) };
	dis_en_x = startEnX;
	dis_en_y = startEnY;	
	//移動先の座標を保存する
	SetPath(startX, startY);
	Cell c = Dig(startX, startY);
	SetGoal(c.x, c.y);

}

void Map::printMaze(int w, int h)
{
	for (int i = 0; i < h; i++) {
		for (int k = 0; k < w; k++) {
			if (maze[i][k] == WALL) {
				map_chips_[i][k]->render(camera_);
			}
			if (maze[i][k] == GOAL) {
				map_chips_[i][k]->render(camera_);
			}
		}
	}
}

void Map::createWall(int w, int h)
{
	//j->x i->yになる
	int i, k;
	for (i = 0; i < h; i++) {
		for (k = 0; k < w; k++) {
			maze[k][i] = WALL;
		}
	}
}

std::shared_ptr<Cell> Map::GetStartCell()
{
	if (StartCells.size() == 0) return nullptr;//StartCells内のチェック	
	auto index = GetRand(StartCells.size() - 1);//配列番号の決定→戻った時にランダムに開始座標を取得する
	auto cell = StartCells[index];//cellの取り出し
	std::vector<std::shared_ptr<Cell>>::iterator itr = StartCells.begin();//shared_ptrとイテレータを使いStartCells内の指定した配列内の添え字を消す
	for (int i = 0; i < index - 1; ++i) {
		itr++;
	}
	StartCells.erase(itr);
	return cell;//cellを返す
}

Cell Map::Dig(int startX, int startY)
{	//座標の保存
	int bufX = startX;int bufY = startY;
	while (1) {
		//if文による壁の判定→配列の末尾に登録
		//up
		if (bufY > 1) {
			if (maze[bufY - 1][bufX] == WALL && maze[bufY - 2][bufX] == WALL) {
				directions.emplace_back(DIRECTION::UP);
			}
		}
		//right
		if (bufX < MEIRO_WIDTH - 2)
			if (maze[bufY][bufX + 1] == WALL && maze[bufY][bufX + 2] == WALL) {
				directions.emplace_back(DIRECTION::RIGHT);
			}
		//down
		if (bufY < MEIRO_HEIGHT - 2) {
			if (maze[bufY + 2][bufX] == WALL && maze[bufY + 1][bufX] == WALL) {
				directions.emplace_back(DIRECTION::DOWN);
			}
		}
		//left
		if (bufX > 1) {
			if (maze[bufY][bufX - 1] == WALL && maze[bufY][bufX - 2] == WALL) {
				directions.emplace_back(DIRECTION::LEFT);
			}
		}
		//配列内が空だった場合while文を抜ける
		if (directions.size() == 0) {
			break;
		}
		//directions配列内の添え字をランダムに取得
		auto index = GetRand(directions.size() - 1);
		switch (directions[index])
		{
		case DIRECTION::UP:
		{
			if (bufY <= 1)break;
			SetPath(bufX, --bufY);
			SetPath(bufX, --bufY);
			break;
		}
		case DIRECTION::RIGHT:
		{
			if (bufX >= MEIRO_WIDTH - 2)break;
			SetPath(++bufX, bufY);
			SetPath(++bufX, bufY);
			break;
		}
		case DIRECTION::DOWN:
		{
			if (bufY >= MEIRO_HEIGHT - 2)break;
			SetPath(bufX, ++bufY);
			SetPath(bufX, ++bufY);
			break;
		}
		case DIRECTION::LEFT:
		{
			if (bufX <= 1)break;
			SetPath(--bufX, bufY);
			SetPath(--bufX, bufY);
			break;
		}

		default:
			break;
		}
		//配列内を空にする
		directions.clear();
	}
	//どこにも掘り進められない場合、穴掘り開始候補座標から掘りなおし
	//候補座標が存在しないとき、穴掘り完了
	auto cell = GetStartCell();
	if (cell != nullptr)
	{
		Dig(cell->x, cell->y);
	}
	return Cell(bufX, bufY);
}

void Map::SetPath(int setX, int setY)
{
	maze[setY][setX] = ROOT;//二次元配列上のx,yをRootに	
	Root_holder_.emplace_back( MyVec2i(setX,setY) );//Rootになった二次元座標での配列を保存
	//奇数番の場合はスタート地点の候補の配列に入れる
	if (setX % 2 == 1 && setY % 2 == 1)
	{	//穴掘り候補座標
		auto thisCell = std::make_shared<Cell>(setX, setY);
		StartCells.emplace_back(thisCell);
	}
}

void Map::GetMapChipList(std::list<dxe::Mesh*> mc_list)
{
	mc_list = field_boxs_;
}

void Map::SetGoal(int goalX, int goalY)
{
	maze[goalX][goalY] = GOAL;
}

tnl::Vector3 Map::GetRandomRoot()
{
	auto X = 0;auto Y = 0;
	while (true) {
		X = SelectStartPoint(MEIRO_WIDTH);
		Y = SelectStartPoint(MEIRO_HEIGHT);
		if (X > 11 || Y > 11 )continue;
		if (maze[X][Y] == ROOT )break; 
	}
	return tnl::Vector3(X,0,Y);
}


Cell::Cell(int setX, int setY)
{	//cellに代入
	x = setX;
	y = setY;
}
