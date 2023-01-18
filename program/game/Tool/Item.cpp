#include "Item.h"

Item::Item(int id, int type)
{
	id_ = id; type_ = type;
}

Item::~Item()
{
}



void Item::SwithItemMove()
{
	switch (type_)
	{
	case 0 :
		break;
	case 1 :
		break;
	case 2:
		break;
	default:
		break;
	}
}

void Item::initialzie()
{
}

void Item::Update(float delta_time)
{
}

void Item::Render()
{
}

float Item::CameraDis(tnl::Vector3& pos1, tnl::Vector3& camera_pos2)
{
	return 0.0f;
}


