#pragma once
#include <list>  
#include<vector>
#include<string>
#include"../../dxlib_ext/dxlib_ext.h"

class Item;
class GmCamera;

class ItemManager {
public:
	ItemManager(){}
	ItemManager( SceneBase* scene_base );
	~ItemManager();
	void CreateItem(int id, int type);
	void Update(float delta_time);
	void CheckItemIsAlive();
	void Render();
	std::list<std::shared_ptr<Item>> spawn_Item_list;//new����Item���i�[����List
	std::vector<std::shared_ptr<Item>> get_Item_vec;//�l������Item���i�[����List
	SceneBase* ref_scene_ = nullptr;
	// �g�p����e�N�X�`�������O���[�h
	Shared<dxe::Texture> texs[5];
	dxe::Mesh* item_box_[9];//�A�C�e���p�̃I���W�i���̔�
	std::shared_ptr<Item> item;
	//�摜�n���h��
	const int IMG_NUM = 5;
	int img_hd[5];
	bool get_item_frag[5] = { false,false,false,false,false };
	int cnt_pos_ = 0;
	int arrow_pos = 100;
private:
	std::vector<std::vector<std::string>>load_item_csv;
	int id_;
	int type_;
	bool is_alive_ = true;
};
