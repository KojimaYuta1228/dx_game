#pragma once
#include <memory>

class SceneBase {
public :
	SceneBase(){}
	virtual ~SceneBase(){}
	//ƒˆ‰¼‘zŠÖ”
	virtual void initialzie() = 0;
	virtual void update( float delta_time ) {}
	virtual void render(){}
	virtual void playsound(){}
};

