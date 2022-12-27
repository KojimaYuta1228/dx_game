#include "gm_scene_base.h"
#include "../gm_camera.h"
#include"../Tool/Map.h"
#include<vector>
#include<memory>
#include<iostream>
#include<list>

/*------クラス------*/
class GmCamera;
class Player;
class Enemy;
class CharacterBase;
class Map;
class Cell;
class Animation;



class ScenePlay : public SceneBase {
public:
	ScenePlay();
	~ScenePlay();

	GmCamera* camera_ = nullptr;
	GmCamera* GetCamera();
	
	std::shared_ptr<Player> player_ = nullptr;
	std::shared_ptr<Enemy> enemy_ = nullptr;
	std::shared_ptr<Map> map_ = nullptr;
	dxe::Mesh* map_chips_[Map::MEIRO_WIDTH][Map::MEIRO_HEIGHT];
	std::list<dxe::Mesh*> map_chip_list_;
	dxe::Mesh* dome_ = nullptr;
	dxe::Mesh* floor_ = nullptr;
	dxe::Mesh* goal_ = nullptr;
	dxe::Mesh* sphare = nullptr;
	std::list<Animation*> liveAnim;
	void initialzie() override;
	void update(float delta_time) override;
	void render() override;
	void playsound()override;
	int floor_hndle = 0;
	const int screenMidleX = DXE_WINDOW_WIDTH / 2;
	const int screenMidleY = DXE_WINDOW_HEIGHT / 2;

	const float boxSize = 50;//boxの1辺の大きさ

	int cnt_timer = 100;
	int img_note = 0;
	int img_smoke = 0;
	int cnt_smoke = 0;
	bool cnt_frag = true;
	bool frag_timer_ = true;
	bool move_result_frag = true;
	bool note_frag = true;
	bool sphare_frag = true;
	bool snim_frag = true;
	float A = 0;
	float B = 0;
	float C = 0;
	float play_se_ghost_cnt = 0;
	float play_se_laugh_cnt = 0;
	float digrees_s = 0;
	float digrees_g = 90;

	float img_cnt_r = 0;


	//EnemyとPlayerにCharacterを基底クラスとして継承
	//基底クラスを素にカメラからのそれぞれのspriteを計算
	//Listに追加してソート遠い順から描画
	//std::list<CharacterBase*> hoge_;//Character型のList、Hoge
	std::list< std::shared_ptr<CharacterBase>> hoge1_;//Listの型変換


	//float CalcDistance(tnl::Vector3& pos1, tnl::Vector3& camera_pos2);

	inline void RenderSort();


};


