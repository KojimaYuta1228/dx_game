#pragma once
#include "../dxlib_ext/dxlib_ext.h"

class SceneBase;
class CharacterBase;
//class Player;

class GameManager {
private:
	GameManager();
	~GameManager();


	
	int img_black_ = 0;
	//�������t���O
	bool init = false;

	static GameManager* instance_;

	// ��ʑJ�ډ��o�̎���
	const float SCENE_TRANSITION_FIX_TIME = 0.5f;
	float scene_transition_time_ = 0;
	float scene_transition_alpha_ = 1.0f;

	tnl::Sequence<GameManager> sequence_ =
		tnl::Sequence<GameManager>(this, &GameManager::seqSceneInTransition);

	// ��ʑJ��( �t�F�[�h�C���v���Z�X )
	bool seqSceneInTransition(const float delta_time);

	// �Q�[���v���Z�X�Ƃ́H�H
	bool seqGameProcess(const float delta_time);

	// ��ʑJ��( �t�F�[�h�A�E�g�v���Z�X )
	bool seqSceneOutTransition(const float delta_time);

	// ���݂̃V�[��
	SceneBase* scene_now_ = nullptr;
	// �\��V�[��
	SceneBase* scene_next_ = nullptr;

public:

	// �C���X�^���X�̎擾
	static GameManager* GetInstance();

	// �j��
	static void Destroy();

	// �X�V
	void update(float delta_time);

	// �V�[���̕ύX
	// arg1... SceneBase ���p�������N���X�C���X�^���X
	void chengeScene(SceneBase* next);

	SceneBase* getCurrentScene() { return scene_now_; }

public:

	// �Q�[���S�̂ŎQ�Ƃ������ϐ��͂����ŗp��

	//�L�������Ƃ̎Q�Ƃ��Ƃ邽�߂̍\����
	//��������ƂɃJ��������̋������v�Z
	/*struct CharaStatus {
		float camera_distance;
		CharacterBase* chara_base;
	};*/
	std::unordered_map<std::string, int> imghandle;
	//std::shared_ptr<Player> player_ = nullptr;
	int ImgHandle(std::string img_pass);
	int save_img = 0;//�摜��ۑ�����ϐ�

};





