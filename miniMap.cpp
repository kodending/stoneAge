#include "stdafx.h"
#include "miniMap.h"

HRESULT miniMap::init()
{
	IMAGEMANAGER->addImage("minimap_door", "image/minimap/minimap_door.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_enemy", "image/minimap/minimap_enemy.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_item", "image/minimap/minimap_item.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_obj_none", "image/minimap/minimap_obj_none.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_player", "image/minimap/minimap_player.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_shopkeeper", "image/minimap/minimap_shopkeeper.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_stair", "image/minimap/minimap_stair.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_trap", "image/minimap/minimap_trap.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_wall_basic", "image/minimap/minimap_wall_basic.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_wall_end", "image/minimap/minimap_wall_end.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_wall_gold", "image/minimap/minimap_wall_gold.bmp", 6, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minimap_wall_stone", "image/minimap/minimap_wall_stone.bmp", 6, 6, true, RGB(255, 0, 255));
	_miniMapBuffer = new image;
	_miniMapBuffer->init(0, 0);
	return S_OK;
}

void miniMap::release()
{

}

void miniMap::render(HDC hdc)
{
	_miniMapBuffer->render(hdc, WINSIZEX - _miniMapBuffer->getWidth() - 100, WINSIZEY - _miniMapBuffer->getHeight() - 100);
}

void miniMap::setupMiniMap(int sizeX, int sizeY)
{
	_mapSizeX = sizeX;
	_mapSizeY = sizeY;
	_miniMapBuffer->release();
	_miniMapBuffer->init(MINIMAP_TILE_SIZE * _mapSizeX, MINIMAP_TILE_SIZE * _mapSizeY, true, RGB(0, 0, 0));
	PatBlt(_miniMapBuffer->getMemDC(), 0, 0, _miniMapBuffer->getWidth(), _miniMapBuffer->getHeight(), BLACKNESS);
}

void miniMap::drawPlayer(int tileX, int tileY)
{
	IMAGEMANAGER->findImage("minimap_player")->render(_miniMapBuffer->getMemDC(), tileX * MINIMAP_TILE_SIZE, tileY * MINIMAP_TILE_SIZE);
	return;
}


