#include "Map.h"
#include "../scene/gm_scene_play.h"
#include "../gm_manager.h"
#include "../../dxlib_ext/dxlib_ext.h"


#define NONE static_cast<int>(MAZESTATE::NONE)
#define WALL static_cast<int>(MAZESTATE::WALL)
#define ROOT static_cast<int>(MAZESTATE::ROOT)
#define GOAL static_cast<int>(MAZESTATE::GOAL)


int Map::maze[MEIRO_HEIGHT][MEIRO_WIDTH];


Map::Map()
{
	mgr = GameManager::GetInstance();
	SceneBase* scene_base = mgr->getCurrentScene();
	ScenePlay* scene_play = dynamic_cast<ScenePlay*>(scene_base);
	/*path = mgr->ImgHandle("graphics/red1.bmp");
	wall = mgr->ImgHandle("graphics/Resouce/image/item/green_blook.jpg");
	goal = mgr->ImgHandle("graphics/graphics/Resouce/image/img_goal.png");*/
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

	// �g�p����e�N�X�`�������O���[�h
	Shared<dxe::Texture> texs[3];

	texs[0] = dxe::Texture::CreateFromFile("graphics/red1.bmp");//RootTexture
	texs[1] = dxe::Texture::CreateFromFile("graphics/Resouce/image/item/green_blook.jpg");//WallTexture
	texs[2] = dxe::Texture::CreateFromFile("graphics/Resouce/image/img_goal.jpg");//GoalTexture

	createMaze();

	/*-----------Box�̃N���[���̍쐬�ƃX�e�[�W�̏�����-----------*/
	//Box�����炩���ߍ쐬
	// �{�b�N�X�R��ނ����炩���ߍ쐬
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
	// �{�b�N�X���N���[�����Đ������邱�ƂŐ������x�A�b�v
	//�}�b�v�`�b�v�ɃN���[���������
	std::shared_ptr<dxe::Texture> tex = nullptr;
	for (int i = 0; i < MEIRO_HEIGHT; ++i) {
		for (int k = 0; k < MEIRO_WIDTH; ++k) {
			//map_chips_[i][k] = origin_boxs[i]->createClone();
			if (maze[i][k] == ROOT)map_chips_[i][k] = origin_boxs[0]->createClone();
			if (maze[i][k] == WALL)map_chips_[i][k] = origin_boxs[1]->createClone();
			if (maze[i][k] == GOAL) {
				map_chips_[i][k] = origin_boxs[2]->createClone();
			}

			if (map_chips_[i][k]) {
				map_chips_[i][k]->pos_ = { (float)(-(12 * 50) + (k * 50)), 0, (float)((12 * 50) - (i * 50)) };
				field_boxs_.emplace_back(map_chips_[i][k]);//�N���[�������}�b�v�����X�g�ɒǉ�
			}
		}
	}


}

void Map::Update()
{

}

void Map::Rander()
{
	printMaze(MEIRO_WIDTH, MEIRO_HEIGHT);
}

int Map::SelectStartPoint(int MAXSIZE)
{
	//�}�b�v�̂ǂ����̊�Ԃ̐�����Ԃ�
	int reStart = std::rand() % MAXSIZE;

	//�]�肪1�ł͂Ȃ�==��Ȃ璲������
	if (reStart % 2 != 1) {
		//�ő吔���1�Ⴂ�����ȊO�Ȃ�1�𑫂�(�z��͈̔͊O�G���[�΍�)
		if (reStart <= (MAXSIZE - 1)) {
			reStart++;
		}
		else {
			//0�Ȃ�����Z�������Ȃ��̂ł��̂܂ܕԂ�
			if (reStart == 0)return reStart;
			reStart--;
		}
	}

	return reStart;
}

int Map::SelectGoalPoint()
{
	return 0;
}

void Map::createMaze()
{
	createWall(MEIRO_WIDTH, MEIRO_HEIGHT);	//�ǂ̐���

	//�n�_�̐���

	float startX, startY;

	//�X�^�[�g�n�_�𗐐��Ŏ擾����

	startX = SelectStartPoint(MEIRO_WIDTH);
	startY = SelectStartPoint(MEIRO_HEIGHT);
	start_pos = { startX,0,startY };
	dis_x = startX;
	dis_y = startY;

	//Enemy�p�̃X�^�[�g�n�_���擾����


	//Debug�K�{
	std::string hoge = "(startX=" + std::to_string(startX) + ",startY=" + std::to_string(startY) + ")";
	tnl::DebugTrace(hoge.c_str());
	tnl::DebugTrace("\n");

	//�ړ���̍��W��ۑ�����
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
	//j->x i->y�ɂȂ�
	int i, k;
	//�֐�����static��t����ƂP�x�Ă΂��ƍēx�Ă΂�Ȃ��Ȃ�
	//���ׂĂ̕ǂŖ��߂�
	{
		for (i = 0; i < h; i++) {
			for (k = 0; k < w; k++) {
				maze[k][i] = WALL;
			}
		}
	}
}

std::shared_ptr<Cell> Map::GetStartCell()
{
	//StartCells���̃`�F�b�N
	if (StartCells.size() == 0) return nullptr;

	//�z��ԍ��̌��聨�߂������Ƀ����_���ɊJ�n���W���擾����
	auto index = GetRand(StartCells.size() - 1);

	//cell�̎��o��
	auto cell = StartCells[index];

	//shared_ptr�ƃC�e���[�^���g��StartCells���̎w�肵���z����̓Y����������
	std::vector<std::shared_ptr<Cell>>::iterator itr = StartCells.begin();
	for (int i = 0; i < index - 1; ++i) {
		itr++;
	}
	StartCells.erase(itr);

	//cell��Ԃ�
	return cell;
}

Cell Map::Dig(int startX, int startY)
{
	//���W�̕ۑ�
	int bufX = startX;
	int bufY = startY;

	//while
	while (1) {

		/*std::string point = "(" + std::to_string(bufX) + "," + std::to_string(bufY) + ")";
		tnl::DebugTrace(point.c_str());
		tnl::DebugTrace("\n");*/

		//if���ɂ��ǂ̔��聨�z��̖����ɓo�^
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
			if (maze[bufY + 2][bufX] == WALL && maze[bufY + 2][bufX] == WALL) {
				directions.emplace_back(DIRECTION::DOWN);
			}
		}

		//left
		if (bufX > 1) {
			if (maze[bufY][bufX - 1] == WALL && maze[bufY][bufX - 2] == WALL) {
				directions.emplace_back(DIRECTION::LEFT);
			}
		}
		/*if (directions.size() == 1) {
			SetGoal(bufX, bufY);
		}*/

		//�z������󂾂����ꍇwhile���𔲂���
		if (directions.size() == 0) {
			break;
		}

		//directions�z����̓Y�����������_���Ɏ擾
		auto index = GetRand(directions.size() - 1);

		//�擾�����Y������f��switch�����񂷁��������
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
		//�z�������ɂ���
		directions.clear();
	}
	//�@��i�߂Ȃ��Ȃ��������̒n�_���S�[���Ƃ��ĕۑ�
	/*if (repeatCount >= MAXREPEAT) {

		SetGoal(bufX,bufY);
		return;
	}*/
	//�ǂ��ɂ��@��i�߂��Ȃ��ꍇ�A���@��J�n�����W����@��Ȃ���
	//�����W�����݂��Ȃ��Ƃ��A���@�芮��
	cnt_repeat_++;
	auto cell = GetStartCell();
	if (cell != nullptr)
	{
		Dig(cell->x, cell->y);
	}

	return Cell(bufX, bufY);

}

void Map::SetPath(int setX, int setY)
{
	maze[setY][setX] = ROOT;

	//��Ԃ̏ꍇ�̓X�^�[�g�n�_�̌��̔z��ɓ����

	if (setX % 2 == 1 && setY % 2 == 1)
	{
		// ���@������W
		auto thisCell = std::make_shared<Cell>(setX, setY);
		StartCells.emplace_back(thisCell);
	}

	//�@��i�߂Ȃ��Ȃ��������̒n�_���S�[���Ƃ��ĕۑ�
	/*if (repeatCount == MAXREPEAT) {

		int a = 0;
		a++;

		maze[setY][setX] = GOAL;
	}*/
}

void Map::GetMapChipList(std::list<dxe::Mesh*> mc_list)
{
	mc_list = field_boxs_;
}

void Map::SetGoal(int goalX, int goalY)
{
	maze[goalX][goalY] = GOAL;
	tnl::DebugTrace("\n x:%d  y:%d", goalX, goalY);
}

tnl::Vector3 Map::GetRandomRoot()
{
	auto X = 0;
	auto Y = 0;
	while (true) {
		X = SelectStartPoint(MEIRO_WIDTH);
		Y = SelectStartPoint(MEIRO_HEIGHT);
		if (X > 11 || Y > 11)continue;
		if (maze[X][Y] == ROOT)break;

	}
	return tnl::Vector3(X,0,Y);
}


Cell::Cell(int setX, int setY)
{
	//cell�ɑ��
	x = setX;
	y = setY;
}

Cell::~Cell()
{
}
