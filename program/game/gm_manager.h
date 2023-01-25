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
	//初期化フラグ
	bool init = false;

	static GameManager* instance_;

	// 画面遷移演出の時間
	const float SCENE_TRANSITION_FIX_TIME = 0.5f;
	float scene_transition_time_ = 0;
	float scene_transition_alpha_ = 1.0f;

	tnl::Sequence<GameManager> sequence_ =
		tnl::Sequence<GameManager>(this, &GameManager::seqSceneInTransition);

	// 画面遷移( フェードインプロセス )
	bool seqSceneInTransition(const float delta_time);

	// ゲームプロセスとは？？
	bool seqGameProcess(const float delta_time);

	// 画面遷移( フェードアウトプロセス )
	bool seqSceneOutTransition(const float delta_time);

	// 現在のシーン
	SceneBase* scene_now_ = nullptr;
	// 予約シーン
	SceneBase* scene_next_ = nullptr;

public:

	// インスタンスの取得
	static GameManager* GetInstance();

	// 破棄
	static void Destroy();

	// 更新
	void update(float delta_time);

	// シーンの変更
	// arg1... SceneBase を継承したクラスインスタンス
	void chengeScene(SceneBase* next);

	SceneBase* getCurrentScene() { return scene_now_; }

public:

	// ゲーム全体で参照したい変数はここで用意

	//キャラごとの参照をとるための構造体
	//これをもとにカメラからの距離を計算
	/*struct CharaStatus {
		float camera_distance;
		CharacterBase* chara_base;
	};*/
	std::unordered_map<std::string, int> imghandle;
	//std::shared_ptr<Player> player_ = nullptr;
	int ImgHandle(std::string img_pass);
	int save_img = 0;//画像を保存する変数

};





