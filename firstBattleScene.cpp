#include "stdafx.h"
#include "firstBattleScene.h"

firstBattleScene::firstBattleScene()
{
}

firstBattleScene::~firstBattleScene()
{
}

HRESULT firstBattleScene::init()
{
	_isMusic = false;
	_isWriteInidata = false;

	_player = new player;
	_player->init();

	_bm = new battleMap;
	_bm->setPlayerMemoryAddressLink(_player);
	_bm->init();
	writeInidata();

	return S_OK;
}

void firstBattleScene::release()
{
	SOUNDMANAGER->stop("battle1_bg");
	SOUNDMANAGER->stop("battle2_bg");
}

void firstBattleScene::update()
{
	if (_isMusic == false)
	{
		int bgmSelect = RND->getFromIntTo(1, 3);
		if (bgmSelect == 1) SOUNDMANAGER->play("battle1_bg", 0.4f);
		if (bgmSelect == 2) SOUNDMANAGER->play("battle2_bg", 0.4f);
		_isMusic = true;
	}
	_bm->update();
	_player->update();
}

void firstBattleScene::render()
{
	_bm->render("dungeon1_map");
	_player->render();
}

void firstBattleScene::writeInidata()
{

}

void firstBattleScene::firstBattleNotice()
{
}
