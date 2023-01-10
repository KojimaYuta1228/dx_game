#pragma once
#include <time.h>
#include <algorithm>
#include <list>
#include "../../dxlib_ext/dxlib_ext.h"
class GameObj {
public:
	 GameObj();
	virtual ~GameObj();

	bool is_alive_ = true;//生存フラグ
	tnl::Vector3 pos_;

	virtual void update();
};