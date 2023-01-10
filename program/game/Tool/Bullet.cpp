#include <time.h>
#include <algorithm>
#include <list>
#include "../scene/gm_scene_play.h"
#include "../../dxlib_ext/dxlib_ext.h"
#include "Bullet.h"
//dxe::Camera* camera = nullptr;
//class GameObj {
//public:
//	virtual ~GameObj() {}
//	virtual void update() {}
//};
//
//
////bool init = false;
////void gameMain(float delta_time) {
////	if (!init) {
////		camera = new dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT);
////		camera->pos_ = { 0,100,-300 };
////		player = new Player();
////		objects.emplace_back(player);
////		init = true;
////	}
//
////	camera->update();
//	for (auto obj : objects) {
//		obj->update();
//	}
//	auto it = objects.begin();
//	while (it != objects.end()) {
//		if (!(*it)->is_alive_) {
//			delete (*it);
//			it = objects.erase(it);
//			continue;
//		}
//		it++;
//	}
//	DrawGridGround(50, 20);
////}
//
//	Bullet::Bullet(const tnl::Vector3& pos)
//	{
//		mesh = dxe::Mesh::CreateSphere(5);
//		mesh->setTexture("graphics/resouce/image/bullet/pink.png");
//		obj_pos_ = pos;
//	}
//
//	Bullet::~Bullet()
//	{
//		DrawStringEx(0, 0, -1, "Delete");
//	}
//
//	void Bullet::update()
//	{
//		obj_pos_.z += 5.0f;
//		if (obj_pos_.z > 300) is_alive_ = false;
//		mesh->pos_ = obj_pos_;
//		mesh->render(camera);
//
//		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_Z)) {
//				objects.emplace_back(new Bullet(player->pos_));
//			}
//	}

Bullet::Bullet(const tnl::Vector3& pos)
{
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
}
