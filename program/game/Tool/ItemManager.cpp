#include "../scene/gm_scene_base.h"
#include "../scene/gm_scene_play.h"
#include"ItemManager.h"
#include"Item.h"
#include "../gm_manager.h"
#include"../Tool/Map.h"

ItemManager::ItemManager(SceneBase* scene_base)
{
	// 3D用の画像
	texs[0] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/speed_up.jpg");//速度上昇
	texs[1] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/speed_down.jpg");//速度減少
	texs[2] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/strong_time.jpg");//無敵
	texs[3] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/key.jpg");//鍵
	texs[4] = dxe::Texture::CreateFromFile("graphics/Resouce/image/color/coin.jpg");//コイン

	// 2D用の画像
	img_hd[0] = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/speed_up.jpg");
	img_hd[1] = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/speed_down.jpg");
	img_hd[2] = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/strong_time.jpg");
	img_hd[3] = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/key.jpg");
	img_hd[4] = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/coin.jpg");

	load_item_csv = tnl::LoadCsv("csv/Item.csv");
	
	for (int i = 0; i < 9; i++) {
		if (i < 2) {
			item_box_[i] = dxe::Mesh::CreateBarrelMV(5, 50, 5);//半径、高さ、膨らみ
			item_box_[i]->setTexture(texs[0]);
		}
		else if (i >= 2 && i < 4) {
			item_box_[i] = dxe::Mesh::CreateBarrelMV(5, 50, 5);
			item_box_[i]->setTexture(texs[1]);
		}
		else if (i == 5) {
			item_box_[i] = dxe::Mesh::CreateTorusMV(15, 10);
			item_box_[i]->setTexture(texs[2]);
		}
		else if (i == 6) {
			item_box_[i] = dxe::Mesh::CreateTorusMV(15, 10);
			item_box_[i]->setTexture(texs[3]);
		}
		else {
			item_box_[i] = dxe::Mesh::CreateDiskMV(25);
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

}

ItemManager::~ItemManager()
{
}

void ItemManager::CreateItem(int id, int type)
{	
	item = std::make_shared<Item>(id, type, ref_scene_);//Itemをnew
	spawn_Item_list.emplace_back(item);//listに追加
	item->item_mesh = item_box_[id]->createClone();//クローン化

	ScenePlay* sptr_play = static_cast<ScenePlay*>(ref_scene_);
	//二次元配列座標をランダム抽選
	auto random = rand() % sptr_play->map_->Root_holder_.size();
	MyVec2i v = sptr_play->map_->Root_holder_[random];
	//ワールド座標に変換
	item->item_mesh->pos_.x = (v.x_ * 50) - (12.5f * 50) + 25;
	item->item_mesh->pos_.z = (-v.y_ * 50) + (12.5f * 50) - 25;

	item->pos_.x = item->item_mesh->pos_.x;
	item->pos_.z = item->item_mesh->pos_.z;

}

void ItemManager::Update(float delta_time)
{
	if (tnl::Input::IsPadDown(ePad::KEY_7) && cnt_pos_ == 0) {
		arrow_pos += 50;
		cnt_pos_++;
	}
	else if (tnl::Input::IsPadDown(ePad::KEY_6) && cnt_pos_ == 1) {
		arrow_pos -= 50;
		cnt_pos_--;
	}
	

		if (!get_item_frag[cnt_pos_]) return;
		else {
				if (tnl::Input::IsPadDown(ePad::KEY_5)) {
					
				
				// Itemの動きをここで呼び出す

				get_item_frag[cnt_pos_] = false;
				auto erace_item = get_Item_vec.at(cnt_pos_);
				get_Item_vec[cnt_pos_] = nullptr ;
			}
		}

		//item->SwithItemMove(cnt_pos_);
	CheckItemIsAlive();
}
//Listにあるアイテムの削除
void ItemManager::CheckItemIsAlive()
{
	auto it = spawn_Item_list.begin();
	while (it != spawn_Item_list.end()) {
		if (!(*it)->is_alive_) {
			auto item = *it;	
			get_item_frag[item->type_] = true;
			get_Item_vec[item->type_] = item;

			//it = spawn_Item_list.erase(it);
			//get_Item_vec.insert(get_Item_vec.end(), item);
			continue;
		}
		it++;
	}
}
void ItemManager::Render() {

	// マップにあるアイテムの描画
	for (auto item : spawn_Item_list) {
		item->Render();
	}


	// 獲得したアイテムの描画
	for (int i = 0; i < IMG_NUM; i++) {

		if (get_item_frag[i]) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);//alpha値の再設定
			DrawRotaGraph(100 + i * 100, 100, 0.1, 0, img_hd[i], true);
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);//alpha値の設定
			DrawRotaGraph(100 + i * 100, 100, 0.1, 0, img_hd[i], true);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);//alpha値の再設定
		}

	}
	SetFontSize(200);
	DrawStringEx( 100 + arrow_pos ,100, 0, "@");

}
