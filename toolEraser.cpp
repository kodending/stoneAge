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
#include "toolWallBasic.h"
#include "toolWallDungeon.h"
#include "toolNpc.h"
#include "toolEraser.h"
#include "toolTileType.h"
#include "toolSave.h"
#include "gameNode.h"

toolType * toolEraser::inputHandle(mapTool * mapTool)
{
	//나가기 버튼을 눌렀을때 비우기 위한
	if (PtInRect(&mapTool->_popUp.exitButtonRc,
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolEraser(false);
		SOUNDMANAGER->play("window_down", 0.4f);
		return new toolEmpty();
	}

	//메뉴툴바에서 건축물 메뉴를 클릭했을때
	if (PtInRect(&mapTool->getStructureRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolEraser(false);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolStructure();
	}

	//메뉴툴바에서 타일 메뉴를 클릭했을때
	if (PtInRect(&mapTool->getTileRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolEraser(false);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolTile();
	}

	//메뉴툴바에서 구조물 메뉴를 클릭했을때
	if (PtInRect(&mapTool->getObjectRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolEraser(false);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolObject();
	}

	//메뉴툴바에서 NPC 메뉴를 클릭했을때
	if (PtInRect(&mapTool->getNpcRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolEraser(false);
		mapTool->setIsToolGate(false);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolNpc();
	}

	//메뉴툴바에서 세이브 메뉴를 클릭했을때
	if (PtInRect(&mapTool->getSaveRc(),
		PointMake(_ptMouse.x + mapTool->getCameraBufferX(), _ptMouse.y + mapTool->getCameraBufferY())))
	{
		mapTool->setIsToolEraser(false);
		mapTool->setIsToolGate(false);
		SOUNDMANAGER->play("window_up", 0.4f);
		return new toolSave();
	}

	return nullptr;
}

void toolEraser::update(mapTool * mapTool)
{
	mapTool->_popUp.PopUpRc = RectMake(CAMERAMANAGER->getCameraRIGHT() + mapTool->_popUp.img->getWidth(),
		CAMERAMANAGER->getCameraBOTTOM() + mapTool->_popUp.img->getHeight() - 24,
		mapTool->_popUp.img->getWidth(), mapTool->_popUp.img->getHeight());

	mapTool->_popUp.exitButtonRc = RectMake(CAMERAMANAGER->getCameraRIGHT() + 146, CAMERAMANAGER->getCameraBOTTOM() + 73,
		124, 27);

	mapTool->_popUp.leftButtonRc = RectMake(CAMERAMANAGER->getCameraRIGHT() + 616, CAMERAMANAGER->getCameraBOTTOM() + 336 - 24,
		32, 32);

	mapTool->_popUp.upButtonRc = RectMake(CAMERAMANAGER->getCameraRIGHT() + 336, CAMERAMANAGER->getCameraBOTTOM() + 582 - 24,
		32, 32);

	mapTool->_popUp.rightButtonRc = RectMake(CAMERAMANAGER->getCameraRIGHT() + 54, CAMERAMANAGER->getCameraBOTTOM() + 336 - 24,
		32, 32);

	mapTool->_popUp.downButtonRc = RectMake(CAMERAMANAGER->getCameraRIGHT() + 336, CAMERAMANAGER->getCameraBOTTOM() + 54 - 24,
		32, 32);

	mapTool->_sampleTile.rcTile = RectMake(CAMERAMANAGER->getCameraRIGHT() + 353, CAMERAMANAGER->getCameraBOTTOM() + 344 - 24,
		64, 47);

	mapTool->_toolName.rc = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 320, CAMERAMANAGER->getCameraBOTTOM() + 610 - 24,
		200, 45);

	mapTool->_leftButton.rc = RectMake(CAMERAMANAGER->getCameraRIGHT() + 516, CAMERAMANAGER->getCameraBOTTOM() + 624 - 24,
		32, 32);

	mapTool->_rightButton.rc = RectMake(CAMERAMANAGER->getCameraRIGHT() + 164, CAMERAMANAGER->getCameraBOTTOM() + 624 - 24,
		32, 32);

	//saveButton 이미지 및 rc 비활성화
	mapTool->_saveInput.saveRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 164, CAMERAMANAGER->getCameraBOTTOM() + 624 - 24, 97, 31);
	mapTool->_saveInput.saveButtonRect = RectMake(CAMERAMANAGER->getCameraRIGHT() + 164, CAMERAMANAGER->getCameraBOTTOM() + 624 - 24, 97, 31);
	mapTool->_saveInput.cancelButtonRect = RectMake(CAMERAMANAGER->getCameraRIGHT() + 164, CAMERAMANAGER->getCameraBOTTOM() + 624 - 24, 97, 31);
	mapTool->_saveInput.textInputRect = RectMakeCenter(CAMERAMANAGER->getCameraRIGHT() + 164, CAMERAMANAGER->getCameraBOTTOM() + 624 - 24, 97, 31);
}

void toolEraser::enter(mapTool * mapTool)
{
	mapTool->setIsExitButton(true);
	mapTool->setIsToolEraser(true);
}

void toolEraser::render(mapTool * mapTool)
{
	IMAGEMANAGER->alphaRender("eraser", getMemDC(), _ptMouse.x + mapTool->getCameraBufferX() - 20, _ptMouse.y + mapTool->getCameraBufferY() - 25, 200);
}

void toolEraser::exit(mapTool * mapTool)
{
}
