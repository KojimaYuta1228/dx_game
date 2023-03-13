#include "../scene/gm_scene_base.h"
#include "../scene/gm_scene_play.h"
#include"ItemManager.h"
#include"Item.h"
#include "../gm_manager.h"
#include"../Tool/Map.h"
#include "../Tool/gm_soundmanager.h"

ItemManager::ItemManager(SceneBase* scene_base)
{
	// 3D�p�̉摜
	texs[0] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/speed_up.png");//���x�㏸
	texs[1] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/speed_down.png");//���x����
	texs[2] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/strong.png");//���G
	texs[3] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/key.png");//��
	texs[4] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/coin.png");//�R�C��

	// 2D�p�̉摜
	img_hd[0] = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/speed_up.png");
	img_hd[1] = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/speed_down.png");
	img_hd[2] = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/strong.png");
	img_hd[3] = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/key.png");
	img_hd[4] = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/coin.png");

	load_item_csv = tnl::LoadCsv("csv/Item.csv");
	
	for (int i = 0; i < 9; i++) {
		if (i < 2) {
			item_box_[i] = dxe::Mesh::CreateSphereMV(FIFTY/2);//���a�A�����A�c���
			item_box_[i]->setTexture(texs[0]);
		}
		else if (i >= 2 && i < 4) {
			item_box_[i] = dxe::Mesh::CreateSphereMV(FIFTY/2);
			item_box_[i]->setTexture(texs[1]);
		}
		else if (i == 4) {
			item_box_[i] = dxe::Mesh::CreateDiskMV(FIFTY/2);
			item_box_[i]->setTexture(texs[2]);
		}
		else if (i == 5) {
			item_box_[i] = dxe::Mesh::CreateDiskMV(FIFTY/2);
			item_box_[i]->setTexture(texs[3]);
		}
		else {
			item_box_[i] = dxe::Mesh::CreateDiskMV(FIFTY/2);
			item_box_[i]->setTexture(texs[4]);
		}
	}

	ref_scene_ = scene_base;
	for (int i = 1; i < load_item_csv.size(); i++) {
		id_ = std::atoi(load_item_csv[i][0].c_str());
		type_ = std::atoi(load_item_csv[i][1].c_str());
		CreateItem(id_, type_);
	}
	get_Item_vec.resize(5);

	select_item_img = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/select_item.png");
	wood_freme_img = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/wood_frame.png");
	
}

ItemManager::~ItemManager()
{
}

void ItemManager::CreateItem(int id, int type)
{	
	item = std::make_shared<Item>(id, type, ref_scene_);//Item��new
	spawn_Item_list.emplace_back(item);//list�ɒǉ�
	item->item_mesh = item_box_[id]->createClone();//�N���[����
	ScenePlay* sptr_play = static_cast<ScenePlay*>(ref_scene_);
	//�񎟌��z����W�������_�����I
	auto random = rand() % sptr_play->map_->Root_holder_.size();
	MyVec2i v = sptr_play->map_->Root_holder_[random];	
	if (v.x_ == save_v.x_ || v.y_ == save_v.y_) {
		random = rand() % sptr_play->map_->Root_holder_.size();
		v = sptr_play->map_->Root_holder_[random];
	}
	save_v = v;
	//���[���h���W�ɕϊ�
	item->item_mesh->pos_.x = (save_v.x_ * FIFTY) - (12.5f * FIFTY) + FIFTY/2;
	item->item_mesh->pos_.z = (-save_v.y_ * FIFTY) + (12.5f * FIFTY) - FIFTY/2;
	//�����蔻��p�̍��W�̎擾
	item->pos_.x = item->item_mesh->pos_.x;
	item->pos_.z = item->item_mesh->pos_.z;
}

void ItemManager::Update(float delta_time)
{
	for (auto itembox : spawn_Item_list) {
		itembox->Update(delta_time);
	}
	CheckItemIsAlive();
	UseHaveItem();
}
//List�ɂ���A�C�e���̍폜
void ItemManager::CheckItemIsAlive()
{
	auto it = spawn_Item_list.begin();
	while (it != spawn_Item_list.end()) {
		if (!(*it)->is_alive_) {
			SoundManager::GetInstance()->SoundSe(SoundManager::SE::GET_ITEM);
			auto item = *it;	//item��it�̃A�h���X����
			get_item_frag[item->type_] = true;	//get_item_frag��item��type�Ԗڂ�true��
			get_Item_vec[item->type_] = item;	//get_item_vec��item��type�Ԗڂ�item����
			it = spawn_Item_list.erase(it);
			continue;
		}
		it++;
	}
}
void ItemManager::UseHaveItem()
{
	if (tnl::Input::IsPadDownTrigger(ePad::KEY_LEFT)) {
		SoundManager::GetInstance()->SoundSe(SoundManager::SE::SELECT_ITEM);
	    arrow_pos -= 70;
	    cnt_pos_--;
	}
	else if (tnl::Input::IsPadDownTrigger(ePad::KEY_RIGHT)) {
		SoundManager::GetInstance()->SoundSe(SoundManager::SE::SELECT_ITEM);
		arrow_pos += 70;
		cnt_pos_++;
	}
	
	if (cnt_pos_ > cnt_max) {
		arrow_pos = cnt_min;
		cnt_pos_ = 0;
	}
	else if (cnt_pos_ < cnt_min) {
		arrow_pos = 280;
		cnt_pos_ = cnt_max;
	}
	if (!get_item_frag[cnt_pos_]) return;
	else {
		if (tnl::Input::IsPadDown(ePad::KEY_2)) {
			SoundManager::GetInstance()->SoundSe(SoundManager::SE::DECISION_ITEM);
			// Item�̓����������ŌĂяo��
			auto gacha_check = gacha.lock();
			if (gacha_check == nullptr)return;
			item->SwithItemMove(cnt_pos_, gacha_check);
			get_item_frag[cnt_pos_] = false;
			auto erace_item = get_Item_vec.at(cnt_pos_);
			get_Item_vec[cnt_pos_] = nullptr;
		}
	}
}

void ItemManager::Render()
{
	// �}�b�v�ɂ���A�C�e���̕`��
	for (auto item : spawn_Item_list) {
		item->Render(1.0);
	}
	for (int i = 0; i < IMG_NUM; i++) {
		DrawRotaGraph(FIFTY + i * 70, FIFTY, 0.17, 0, wood_freme_img, true);
	}
	// �l�������A�C�e���̕`��
	for (int i = 0; i < IMG_NUM; i++) {
		if (get_item_frag[i]) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);//alpha�l�̍Đݒ�
			DrawRotaGraph(FIFTY + i * 70, FIFTY, 0.2, 0, img_hd[i], true);
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);//alpha�l�̐ݒ�
			DrawRotaGraph(FIFTY + i * 70, FIFTY, 0.2, 0, img_hd[i], true);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);//alpha�l�̍Đݒ�
		}
	}
	if (get_item_frag[cnt_pos_]) {
		DrawRotaGraph(FIFTY + cnt_pos_ * 70, FIFTY, 0.25, 0, img_hd[cnt_pos_], true);
	}
	DrawRotaGraph(FIFTY + arrow_pos , FIFTY, 0.21, 0, select_item_img, true);
	DrawBox(0, 100, 360, 120, -1, true);
	if (cnt_pos_ == cnt_min) {
		DrawStringEx(0,100,0,"�������̊Ԏ��g�̑��x�サ�傤��");
	}else if (cnt_pos_ == 1) {
		DrawStringEx(0, 100, 0, "�������̊ԓG�̑��x�����傤��");
	}
	else if (cnt_pos_ == 2) {
		DrawStringEx(0, 100, 0, "�������̊ԂނĂ���");
	}
	else if (cnt_pos_ == 3) {
		DrawStringEx(0, 100, 0, "���܂ق�����̂�����");
	}
	else if (cnt_pos_ == cnt_max) {
		DrawStringEx(0, 100, 0, "���R�C����");
	}
}
