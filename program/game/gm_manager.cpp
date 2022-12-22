#include "gm_manager.h"
#include "scene/gm_scene_base.h"
#include "scene/gm_scene_title.h"
#include"Tool/gm_soundmanager.h"

GameManager* GameManager::instance_ = nullptr;

//-----------------------------------------------------------------------------------------
// �R���X�g���N�^
GameManager::GameManager() {
	save_img = 0;
	scene_now_ = new SceneTitle();
	img_black_ = LoadGraph("graphics/black.bmp");
	SetBackgroundColor(32, 32, 32);
}

//-----------------------------------------------------------------------------------------
// �f�X�g���N�^
GameManager::~GameManager() {
	if (scene_now_) delete scene_now_;
	if (scene_next_) delete scene_next_;
	
}


//-----------------------------------------------------------------------------------------
// �V���O���g���̃C���X�^���X�擾
GameManager* GameManager::GetInstance() {
	if (!instance_) {
		instance_ = new GameManager();
	}
	return instance_;
}

//-----------------------------------------------------------------------------------------
// �j��
void GameManager::Destroy() {
	if (instance_) {
		delete instance_;
		instance_ = nullptr;
	}
}


//-----------------------------------------------------------------------------------------
void GameManager::chengeScene(SceneBase* next) {
	scene_next_ = next;
	sequence_.change(&GameManager::seqSceneOutTransition);
}

int GameManager::ImgHandle(std::string img_pass)
{
	auto it = imghandle.find(img_pass);        // iterator �ɘA�z�z������� find
	// end �܂Ŗ��������� if����ʂ�
	if (it == imghandle.end()) {
		save_img = LoadGraph(img_pass.c_str()); // save_img �� LoadGraph(string �� char�^�ɕϊ�) ����B
		imghandle.insert(std::make_pair(img_pass, save_img)); // insert �Ő擪�ɗv�f��ǉ�
	}
	else { save_img = it->second; }

	return save_img;
}

//std::string back_ground = "graphics/sample";
//ImgHandle(back_ground);
//-----------------------------------------------------------------------------------------
bool GameManager::seqSceneInTransition(const float delta_time)
{
	if (sequence_.isStart()) {
		scene_transition_time_ = 0;
	}
	scene_transition_time_ += delta_time;

	scene_transition_alpha_ = 1.0f - (scene_transition_time_ / SCENE_TRANSITION_FIX_TIME);

	if (scene_transition_time_ > SCENE_TRANSITION_FIX_TIME) {
		sequence_.change(&GameManager::seqGameProcess);
	}
	return true;


}

//-----------------------------------------------------------------------------------------
bool GameManager::seqGameProcess(const float delta_time)
{
	scene_now_->update(delta_time);
	return true;
}

//-----------------------------------------------------------------------------------------
bool GameManager::seqSceneOutTransition(const float delta_time)
{
	if (sequence_.isStart()) {
		scene_transition_time_ = 0;
	}
	scene_transition_time_ += delta_time;
	scene_transition_alpha_ = (scene_transition_time_ / SCENE_TRANSITION_FIX_TIME);

	if (scene_transition_time_ > SCENE_TRANSITION_FIX_TIME) {
		delete scene_now_;
		SoundManager::GetInstance()->StopBgm();
		scene_now_ = scene_next_;
		scene_now_->initialzie();
		scene_next_ = nullptr;
		sequence_.change(&GameManager::seqSceneInTransition);
	}
	return true;
}

//-----------------------------------------------------------------------------------------
void GameManager::update(float delta_time) {

	if (!init) {
		scene_now_->initialzie();
		init = true;
	}

	sequence_.update(delta_time);
	scene_now_->render();

	int col = static_cast<int>(255.0f * scene_transition_alpha_);
	if (0 >= col) return;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, col);
	DrawExtendGraph(0, 0, DXE_WINDOW_WIDTH, DXE_WINDOW_HEIGHT, img_black_, false);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}









