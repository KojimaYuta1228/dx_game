#pragma once
#include "../Character/CharacterBase.h"
#include "../../dxlib_ext/dxlib_ext.h"

class CharacterBase;

class Bullet : public CharacterBase {
public:
	Bullet(const tnl::Vector3& pos,tnl::Vector3 dir,float speed);
	virtual ~Bullet();
	dxe::Mesh* bullet_ = nullptr;
	std::shared_ptr<dxe::Mesh>mesh = nullptr;
	
	
	void initialzie()override;
	void Update(float delta_time)override;
	bool frag_bullet = false;
};

