#include "GachaGacha.h"
#include"../Tool/Animation.h"
#include"../Tool/GachaItem.h"
#include "../Tool/gm_soundmanager.h"
#include "../gm_manager.h"

GachaGacha::GachaGacha()
{
	GameManager* mgr = GameManager::GetInstance();	
	img_gacha_item[0] = mgr->ImgHandle("graphics/Resouce/image/color/gacha_item_n.png");
	img_gacha_item[1] = mgr->ImgHandle("graphics/Resouce/image/color/gacha_item_r.png");
	img_gacha_item[2] = mgr->ImgHandle("graphics/Resouce/image/color/gacha_item_sr.png");
	img_gacha_item[3] = mgr->ImgHandle("graphics/Resouce/image/color/gacha_item_ur.png");
	img_gacha_item[4] = mgr->ImgHandle("graphics/Resouce/image/color/tresurebox2.png");

	img_black = GameManager::GetInstance()->ImgHandle("graphics/Resouce/image/color/black_frame.png");

	load_gacha_item_csv = tnl::LoadCsv("csv/gacha_item.csv");

	for (int i = 1; i < load_gacha_item_csv.size(); i++) {
		id_ = std::atoi(load_gacha_item_csv[i][0].c_str());
		type_ = std::atoi(load_gacha_item_csv[i][1].c_str());
		CreateGachaItem(id_, type_);
	}

	get_gacha_Item_vec.resize(5);
}

GachaGacha::~GachaGacha()
{
}

void GachaGacha::Update(float delta_time)
{
	if (have_coin < 3) {
		return;
	}
	if(tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE) && have_coin >= 3){
		have_coin -= cnt_can_gacha;
		frag_can_gacha = false;
	}
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE))have_coin;
	
	UseGacha(delta_time);
	CheckGachaItemAlive();
}

void GachaGacha::UseGacha(float delta_time)
{

	if (!frag_can_gacha) {
		auto random = rand() % spawn_gacha_Item_list.size();
		if (random < 4) { type_ = 0; }
		else if (random >= 4 && random < 7) { type_ = 1; }
		else if (random >= 7 && random < 9) { type_ = 2; }
		else if (random == 10) { type_ = 3; }
		i_gacha_item_->SwitchGachaItem(type_);
		if (!frag_open_draw)
		{
			get_gacha_item_frag[type_] = true;
			frag_can_gacha = true;
			frag_next_render = false;
			frag_cnt_center_render = false;			
		}
		
	}
}

void GachaGacha::GachaAnima(float delta_time)
{
	i_gacha_item_->Render(0.01666);
}

void GachaGacha::CreateGachaItem(int id_, int type_)
{
	i_gacha_item_ = std::make_shared<GachaItem>(id_, type_);
	spawn_gacha_Item_list.emplace_back(i_gacha_item_);
}

void GachaGacha::CheckGachaItemAlive()
{
	auto it = spawn_gacha_Item_list.begin();
	while(it != spawn_gacha_Item_list.end()){
		if (!(*it)->is_alive_) {
			auto gacha_item = *it;	//itemにitのアドレスを代入
			get_gacha_item_frag[gacha_item->type_] = true;	//get_item_fragのitemのtype番目をtrueに
			get_gacha_Item_vec[i_gacha_item_->type_] = gacha_item;	//get_item_vecのitemのtype番目にitemを代入
			it = spawn_gacha_Item_list.erase(it);
			continue;
		}
		it++;
	}
}

void GachaGacha::Render()
{
	for (int i = 0; i < 4; i++) {

		DrawRotaGraph(50 + i * 100, 50, 3, 0, img_black, true);
		if (get_gacha_item_frag[i]) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);//alpha値の再設定
			DrawRotaGraph(50 + i * 100, 50, 3, 0, img_gacha_item[i], true);
		}
		else {
			DrawRotaGraph(50 + i * 100, 50, 3, 0, img_black, true);
		}
		if(get_gacha_item_frag[i] && !frag_next_render){
			DrawRotaGraph(DXE_WINDOW_WIDTH/2 , DXE_WINDOW_HEIGHT/2, 7, 0, img_gacha_item[i], true);
		}
	}
}

void GachaGacha::GetgachaCoin(int get_coin)
{
	have_coin = get_coin;

}


