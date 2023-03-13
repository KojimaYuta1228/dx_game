#pragma once
#include <list>  
#include<vector>
#include<string>
#include"../../dxlib_ext/dxlib_ext.h"


class Item;
class GmCamera;
class GachaGacha;

class ItemManager {
public:
	ItemManager(){}
	ItemManager( SceneBase* scene_base );
	~ItemManager();
	void CreateItem(int id, int type);
	void Update(float delta_time);
	void CheckItemIsAlive();//�A�C�e���̐����m�Ffalse�Ȃ�΃f���[�g����
	void UseHaveItem();//�A�C�e���̎g�p�g�����A�C�e���̃t���O��܂�AItem�N���X��type��n��
	void Render();

	std::list<std::shared_ptr<Item>> spawn_Item_list;//new����Item���i�[����List
	std::vector<std::shared_ptr<Item>> get_Item_vec;//�l������Item���i�[����List
	SceneBase* ref_scene_ = nullptr;
	Shared<dxe::Texture> texs[5];//�g�p����e�N�X�`�������O���[�h����ۂɕۑ����邽�߂̔z��
	dxe::Mesh* item_box_[9];//�A�C�e���p�̃I���W�i���̔�
	std::shared_ptr<Item> item;
	std::weak_ptr<GachaGacha> gacha;
	bool get_item_frag[5] = { false,false,false,false,false };//�l������Item�̕`���؂�ւ���frag
	MyVec2i save_v;//�}�b�v��ɃA�C�e�����X�|�[�������邽�߂̃��[�J�����W��ۑ�����ϐ�
private:
	std::vector<std::vector<std::string>>load_item_csv;
	int id_;
	int type_;
	int cnt_max = 4;
	int cnt_min = 0;
	int select_item_img = 0;//�摜�n���h��
	int wood_freme_img = 0;//�摜�n���h��
	const int IMG_NUM = 5;//for���̍ő吔
	const int FIFTY = 50;
	int img_hd[5];//load���摜��ۑ����邽�߂̔z��
	int cnt_pos_ = 0;//�I�𒆂̃J�[�\����Pos�̏�����������̂��߂̃J�E���g
	int arrow_pos = 0;//�I�𒆂̃J�[�\����Pos

};
