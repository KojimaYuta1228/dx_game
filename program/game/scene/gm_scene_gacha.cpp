#include "../gm_manager.h"
#include "gm_scene_gacha.h"
#include "gm_scene_title.h"
#include"../Tool/Animation.h"
#include"../Tool/GachaItem.h"
#include "../Tool/gm_soundmanager.h"

SceneGacha::SceneGacha()
{
	img_hd[0] = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/speed_up.png");
	img_hd[1] = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/speed_up.png");
	img_hd[2] = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/speed_up.png");
	img_hd[3] = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/speed_up.png"); 
	
	load_gacha_item_csv = tnl::LoadCsv("csv/gacha_item.csv");

	for (int i = 1; i < load_gacha_item_csv.size(); i++) {
		id_ = std::atoi(load_gacha_item_csv[i][0].c_str());
		type_ = std::atoi(load_gacha_item_csv[i][1].c_str());
		CreateGachaItem(id_, type_);
	}

	get_gacha_Item_vec.resize(5);
}

SceneGacha::~SceneGacha()
{
}

void SceneGacha::initialzie()
{
}

void SceneGacha::update(float delta_time)
{
	if (have_coin < 3) {
		return;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_1) && have_coin >= 3) {
		have_coin -= cnt_can_gacha;
		frag_can_gacha = false;
	}
	UseGacha();

}

void SceneGacha::render()
{
	i_gacha_item_->Render(0.01666);
}

void SceneGacha::playsound()
{
}

void SceneGacha::UseGacha()
{
	if (!frag_can_gacha) {
		auto random = rand() % spawn_gacha_Item_list.size();
		if (random < 4) { type_ = 0; }
		else if (random >= 4 && random < 7) { type_ = 1; }
		else if (random >= 7 && random < 9) { type_ = 2; }
		else if (random == 10) { type_ = 3; }
		i_gacha_item_->SwitchGachaItem(type_);
		frag_can_gacha = true;
	}
}

void SceneGacha::GachaAnima(float delta_time)
{
}

void SceneGacha::CreateGachaItem(int id_, int type_)
{
	i_gacha_item_ = std::make_shared<GachaItem>(id_, type_);
	spawn_gacha_Item_list.emplace_back(i_gacha_item_);

}

void SceneGacha::CheckGachaItemAlive()
{
	auto it = spawn_gacha_Item_list.begin();
	while (it != spawn_gacha_Item_list.end()) {
		if (!(*it)->is_alive_) {
			auto gacha_item = *it;	//item‚Éit‚ÌƒAƒhƒŒƒX‚ð‘ã“ü
			//get_item_frag[item->type_] = true;	//get_item_frag‚Ìitem‚Ìtype”Ô–Ú‚ðtrue‚É
			get_gacha_Item_vec[i_gacha_item_->type_] = gacha_item;	//get_item_vec‚Ìitem‚Ìtype”Ô–Ú‚Éitem‚ð‘ã“ü
			it = spawn_gacha_Item_list.erase(it);
			continue;
		}
		it++;
	}
}
