#pragma once
#include "GameObj.h"

class GameObj;

class Bullet : public GameObj {
public:
	Bullet(const tnl::Vector3& pos);
	virtual ~Bullet();
	dxe::Mesh* mesh = nullptr;
	void update()override;
	
};

std::list<GameObj*> objects;