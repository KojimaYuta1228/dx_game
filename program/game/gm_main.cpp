#include <time.h>
#include "gm_main.h"
#include "gm_manager.h"

bool init = false;



void gameMain(float delta_time) {
	GameManager* mgr = GameManager::GetInstance();
	mgr->update(delta_time);

	if (!init) {
		std::srand(std::time(NULL));	//乱数の初期化
		init = true;
	}

}

void gameEnd() {
	GameManager* mgr = GameManager::GetInstance();
	mgr->Destroy();
}
