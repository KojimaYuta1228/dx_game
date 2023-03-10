#pragma once
#include "../dxlib_ext/dxlib_ext_camera.h"

class GmCamera : public dxe::Camera {
public :
	GmCamera() : dxe::Camera(DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT) {}
	~GmCamera(){}
	tnl::Vector3 free_look_angle_xy_ = { tnl::ToRadian(40), 0, 0 };//カメラの初期角度
	float target_distance_ = 200;

	enum {
		CAMERA_TARGET,
		CAMERA_FREE_LOOK
	};

	void update();

	int camF = 0;
	tnl::Quaternion c_rot;//3D空間での回転を促しているもの
};

