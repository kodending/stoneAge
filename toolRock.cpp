#include "stdafx.h"
#include "mapTool.h"
#include "toolEmpty.h"
#include "toolTile.h"
#include "toolStructure.h"
#include "toolObject.h"
#include "toolFence.h"
#include "toolGate.h"
#include "toolDisplay.h"
#include "toolPlants.h"
#include "toolRock.h"
#include "toolWallBasic.h"
#include "toolWallDungeon.h"
#include "toolNpc.h"
#include "toolEraser.h"
#include "toolTileType.h"
#include "toolSave.h"
#include "gameNode.h"

toolType * toolRock::inputHandle(mapTool * mapTool)
{
	//나가기 버튼을 눌렀을때 비우기 위한
	if (PtInRect(&mapTool->_popUp.exitButtonRc,
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolRock(false);
		SOUNDMANAGER->play("window_down", 0.4f);
		return new toolEmpty();
	}

	//메뉴툴바에서 타일 메뉴를 클릭했을때
	if (PtInRect(&mapTool->getTileRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolRock(false);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolTile();
	}

	//메뉴툴바에서 건축물 메뉴를 클릭했을때
	if (PtInRect(&mapTool->getStructureRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolRock(false);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolStructure();
	}

	//메뉴툴바에서 NPC 메뉴를 클릭했을때
	if (PtInRect(&mapTool->getNpcRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolRock(false);
		mapTool->setIsToolGate(false);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolNpc();
	}

	//메뉴툴바에서 지우개 메뉴를 클릭했을때
	if (PtInRect(&mapTool->getEraserRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolRock(false);
		SOUNDMANAGER->play("window_down", 0.4f);
		return new toolEraser();
	}

	//메뉴툴바에서 세이브 메뉴를 클릭했을때
	if (PtInRect(&mapTool->getSaveRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolRock(false);
		mapTool->setIsToolGate(false);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolSave();
	}

	//팝업창에서 왼쪽버튼을 눌렀을때
	if (PtInRect(&mapTool->_leftButton.rc,
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolRock(false);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolPlants();
	}

	//팝업창에서 오른쪽버튼을 눌렀을때
	if (PtInRect(&mapTool->_rightButton.rc,
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolRock(false);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolWallBasic();
	}

	return nullptr;
}

void toolRock::update(mapTool * mapTool)
{
	mapTool->_popUp.PopUpRc = RectMake(CAMERAMANAGER->getCameraRIGHT() - mapTool->_popUp.img->getWidth(),
		CAMERAMANAGER->getCameraBOTTOM() - mapTool->_popUp.img->getHeight() - 24,
		mapTool->_popUp.img->getWidth(), mapTool->_popUp.img->getHeight());

	mapTool->_popUp.exitButtonRc = RectMake(CAMERAMANAGER->getCameraRIGHT() - 146, CAMERAMANAGER->getCameraBOTTOM() - 73,
		124, 27);

	mapTool->_popUp.leftButtonRc = RectMake(CAMERAMANAGER->getCameraRIGHT() - 616, CAMERAMANAGER->getCameraBOTTOM() - 336 - 24,
		32, 32);

	mapTool->_popUp.upButtonRc = RectMake(CAMERAMANAGER->getCameraRIGHT() - 336, CAMERAMANAGER->getCameraBOTTOM() - 582 - 24,
		32, 32);

	mapTool->_popUp.rightButtonRc = RectMake(CAMERAMANAGER->getCameraRIGHT() - 54, CAMERAMANAGER->getCameraBOTTOM() - 336 - 24,
		32, 32);

	mapTool->_popUp.downButtonRc = RectMake(CAMERAMANAGER->getCameraRIGHT() - 336, CAMERAMANAGER->getCameraBOTTOM() - 54 - 24,
		32, 32);

	mapTool->_sampleTile.rcTile = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 310, CAMERAMANAGER->getCameraBOTTOM() - 310 - 24,
		100, 100);

	mapTool->_toolName.rc = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() - 320, CAMERAMANAGER->getCameraBOTTOM() - 610 - 24,
		200, 45);

	mapTool->_leftButton.rc = RectMake(CAMERAMANAGER->getCameraRIGHT() - 516, CAMERAMANAGER->getCameraBOTTOM() - 624 - 24,
		32, 32);

	mapTool->_rightButton.rc = RectMake(CAMERAMANAGER->getCameraRIGHT() - 164, CAMERAMANAGER->getCameraBOTTOM() - 624 - 24,
		32, 32);

	//saveButton 이미지 및 rc 비활성화
	mapTool->_saveInput.saveRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 164, CAMERAMANAGER->getCameraBOTTOM() + 624 - 24, 97, 31);
	mapTool->_saveInput.saveButtonRect = RectMake(CAMERAMANAGER->getCameraRIGHT() + 164, CAMERAMANAGER->getCameraBOTTOM() + 624 - 24, 97, 31);
	mapTool->_saveInput.cancelButtonRect = RectMake(CAMERAMANAGER->getCameraRIGHT() + 164, CAMERAMANAGER->getCameraBOTTOM() + 624 - 24, 97, 31);
	mapTool->_saveInput.textInputRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 164, CAMERAMANAGER->getCameraBOTTOM() + 624 - 24, 97, 31);
}

void toolRock::enter(mapTool * mapTool)
{
	mapTool->_popUp.img = IMAGEMANAGER->findImage("popUp");
	mapTool->_sampleTile.img = IMAGEMANAGER->findImage("rock");
	mapTool->_currentTile.img = IMAGEMANAGER->findImage("rock");
	mapTool->_toolName.img = IMAGEMANAGER->findImage("toolName");
	mapTool->_leftButton.img = IMAGEMANAGER->findImage("leftButton");
	mapTool->_rightButton.img = IMAGEMANAGER->findImage("rightButton");
	mapTool->setIsExitButton(true);
	mapTool->setIsToolRock(true);

	mapTool->_sampleTile.terrainFrameX = 0;
	mapTool->_sampleTile.terrainFrameY = 0;

	mapTool->_toolName.currentFrameX = 7;
	mapTool->_toolName.currentFrameY = 0;
}

void toolRock::render(mapTool * mapTool)
{
	mapTool->_popUp.img->render(getMemDC(), mapTool->_popUp.PopUpRc.left, mapTool->_popUp.PopUpRc.top);

	mapTool->_sampleTile.img->frameRender(getMemDC(), mapTool->_sampleTile.rcTile.left, mapTool->_sampleTile.rcTile.top,
		mapTool->_sampleTile.terrainFrameX, mapTool->_sampleTile.terrainFrameY);

	mapTool->_toolName.img->frameRender(getMemDC(), mapTool->_toolName.rc.left, mapTool->_toolName.rc.top,
		mapTool->_toolName.currentFrameX, mapTool->_toolName.currentFrameY);

	mapTool->_leftButton.img->frameRender(getMemDC(), mapTool->_leftButton.rc.left, mapTool->_leftButton.rc.top,
		mapTool->_leftButton.currentFrameX, mapTool->_leftButton.currentFrameY);

	mapTool->_rightButton.img->frameRender(getMemDC(), mapTool->_rightButton.rc.left, mapTool->_rightButton.rc.top,
		mapTool->_rightButton.currentFrameX, mapTool->_rightButton.currentFrameY);
}

void toolRock::exit(mapTool * mapTool)
{

}
