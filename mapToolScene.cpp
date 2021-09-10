#include "stdafx.h"
#include "mapToolScene.h"

mapToolScene::mapToolScene()
{
}

mapToolScene::~mapToolScene()
{
}

HRESULT mapToolScene::init()
{
	_mt = new mapTool;
	_mt->init();

	_UIM = new UIManager;

	return S_OK;
}

void mapToolScene::release()
{
}

void mapToolScene::update()
{
	_mt->update();
}

void mapToolScene::render()
{
	_mt->render();
}
