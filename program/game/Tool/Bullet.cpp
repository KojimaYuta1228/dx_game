#include <time.h>
#include <algorithm>
#include <list>
#include "../scene/gm_scene_play.h"
#include "../../dxlib_ext/dxlib_ext.h"
#include"../Character/CharacterBase.h"
#include "Bullet.h"


Bullet::Bullet(const tnl::Vector3& pos,tnl::Vector3 dir, float speed)
{
	
	bullet_ = dxe::Mesh::CreateSphere(5);	
	bullet_->setTexture(dxe::Texture::CreateFromFile("graphics/blue1.bmp"));
	pos_ = pos;
}

Bullet::~Bullet()
{
	DrawStringEx(0, 0, -1, "Delete");
}

void Bullet::initialzie()
{
}

void Bullet::Update(float delta_time)
{
	pos_.z += 5.0f;
	if (pos_.z > 300) is_alive_ = false;
	mesh->pos_ = pos_;
}
